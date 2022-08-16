/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : E100_LDC                                                    **
**  Filename  : Rte_Utils.c                                                 **
**  Version   : -.- (PCB : )                                                **
**  Date      : 2019.09.05                                                  **
**                                                                          **
******************************************************************************
**                                                                          **
**  (c) 2019 YOUNG HWA TECH Co., Ltd. All Rights Reserved                   **
**                                                                          **
**                       YOUNG HWA TECH Co., Ltd.                           **
******************************************************************************

VERSION HISTORY:
----------------

Version     : -.-
Date        : ----.--.--
Revised by  : Im, Hong Kyun
Description : Original version.

*/

#define RTE_VARIABLE_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "Rte_Variable.h"
#include "../BSW/flexcan_BSW.h"
#include "../BSW/u_BSW.h"
#include "Asw_DiagAdc.h"
#include "spc570_hal_pwm.h"

/****************************************************************************/
/**                                                                        **/
/**                      DEFINITIONS AND MACROS                            **/
/**                                                                        **/
/****************************************************************************/
#define TEST_FAILURE 			( 1U )

#define BATT_NORMAL  			( 0U )
#define BATT_NORMAL_DLY  	( 1U )
#define BATT_ERROR_DLY		( 2U )
#define BATT_ERROR				( 3U )

#define POLYNOMINAL		    ( 0x1DU )
#define INIT_VALUE		    ( 0xFFU )
#define XOR_VALUE			    ( 0xFFU )

/****************************************************************************/
/**                                                                        **/
/**                      TYPEDEFS AND STRUCTURES                           **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                      PROTOTYPES OF LOCAL FUNCTIONS                     **/
/**                                                                        **/
/****************************************************************************/
static uint16_t UTILS_ADC2REAL( uint16_t AverAdc, uint16_t adcTable[ 19 ], uint16_t realTable[ 19 ] );
static uint16_t UTILS_VOUTREF_INV( uint16_t Ref, uint16_t AdcValue[ 19 ], uint16_t realValue[ 19 ] );
static void RTE_SET_CAN_TIMEOUT_COUNT( uint16_t val);
static void RTE_ADD_CAN_TIMEOUT_COUNT( void );
static void RTE_SET_IGN3_STS( uint8_t val );
static void RTE_SET_CMD_ENABLE_LDC( uint8_t val );
static void RTE_SET_CMD_TARGET_VOLT( uint16_t val );
static uint16_t RTE_GET_CAN_TIMEOUT_COUNT( void );
static uint16_t RTE_GET_ADC_REAL_IOUT(void);
static uint16_t RTE_GET_ADC_REAL_IIN( void );
static uint16_t RTE_GET_ADC_REAL_VIN( void );
static uint16_t RTE_GET_ADC_REAL_VOUT( void );
static int16_t RTE_GET_ADC_REAL_TEMP( void );
static int16_t RTE_GET_ADC_REAL_SUB_TEMP( void );
static uint16_t RTE_GET_ADC_REAL_KEYIN( void );
static uint16_t RTE_GET_ADC_REAL_12VBAT( void );
static void Batt_normal ( void );
static void Batt_normal_dly ( void );
static void Batt_error_dly ( void );
static void Batt_error ( void );
static uint8_t CRC8_Calc ( uint8_t *u8p_Data, uint32_t u32_Size );
static void Crc8TableGenerator ( uint8_t u8_Polynomial, uint8_t u8_CrcTable[ 256 ] );
static uint8_t CalculateCRC8 ( uint8_t u8_CrcTable[ 256 ], const uint8_t *u8p_Crc_DataPtr, uint32_t u32_Crc_Len, uint8_t u8_Crc_InitialValue, uint8_t u8_Crc_XorValue );

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/
#if ( OPEN_LOOP_IN_USE )
uint32_t testPhaseVal = 0;
#endif

#if ( LDC_TEST_VALUES )
uint16_t testInCurr = 0;
uint16_t testInVolt = 3000;
uint16_t testOutCurr = 0;
uint16_t testOutVolt = 140;
int16_t testTemp = 35;
int16_t testTempSub = 35;
uint16_t testKeyIn = 2000;
uint16_t testBplus = 140;
#endif

uint8_t rteCanBusOffCnt = 0U;
uint8_t rteCanRxPathDisable = 0U;
uint16_t rteVcuCmdLdcTargetVolt = 0U; /* Low Votage(12V) Output LDC Target voltage */
uint16_t u16g_StartPwmOn_cnt = 0U;
uint16_t u16g_StartSrOn_cnt = 0U;
AdcRealValuesType rteAdcRealResult = { 0U, };

/****************************************************************************/
/**                                                                        **/
/**                      GLOBAL VARIABLES                                  **/
/**                                                                        **/
/****************************************************************************/
/* CAN diagnosis */
static uint8_t rteCanBusOff = 1U; /* default : 1 */
static uint16_t rteCanTimeoutCnt = 0U;

static uint16_t rtePhaseShiftVal = 0U;
static uint32_t rtePwrLatchCounter = 0U; /* power latch count */
static uint8_t rteVcuIgn3Sts = 0U;
static uint8_t rteVcuCmdEnLdc = 0U; 			/* LDC Enable */

/* LDC mode state - Normal, Warning, fault... */
static LDC_MODE_DEF rteLdcMode = 0U; /* shutdown */

/* LDC Run state - Standby, Power on */
static LDC_RUN_DEF rteLdcRun = 0U;

/* LDC Áø´Ü flag */
static LdcDiagnosisType rteStrLdcDiagnosisFlag = { 0U, };

/* ADC */
static ADC_results_t rteAdcRawResult = { 0U, };

/*MCU?*/
static LDC_DERATING_STAT rteDeratingStatus = 0;

static uint16_t AdcVout[ 19 ] = {0,191,379,566,755,944,1137,1323,1514,1709,1896,2085,2278,2445,2670,2804,3027,3394,3726};
static uint16_t Vout[ 19 ] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,180,200};

static uint8_t u8s_BattLvlSts = BATT_NORMAL;
static uint8_t u8s_BattNormalStsCnt = 0U;
static uint8_t u8s_BattErrorStsCnt = 0U;
static uint16_t u16s_BattLvl;

static uint8_t u8s_Counter_3A0 = 0U;
static uint8_t u8s_MsgAlive_cnt = 254U;

static uint8_t u8s_CrcTable8bit[ 256 ];

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
uint8_t RTE_GET_CAN_BUS_OFF_STATE( void )
{
	return rteCanBusOff; /* 1 : ok / 0 : false */
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void RTE_SET_CAN_BUS_OFF_STATE( uint8_t val )
{
	rteCanBusOff =  val;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
uint16_t RTE_GET_PHASE_SHIFT_VAL( void )
{
#if ( OPEN_LOOP_IN_USE )
	return testPhaseVal;
#else
	return rtePhaseShiftVal;
#endif
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
uint32_t RTE_GET_POWER_LATCH_COUNTER_VAL( void )
{
	return rtePwrLatchCounter;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void RTE_ADD_POWER_LATCH_COUNTER_VAL( void )
{
	rtePwrLatchCounter++;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void RTE_CLEAR_POWER_LATCH_COUNTER_VAL( void )
{
	rtePwrLatchCounter = 0;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
uint8_t RTE_SOFT_STOP( uint16_t u16_rteshift )
{
	uint8_t u8_Ret = 0U;
	uint16_t u16_shift = 0U;

	RTE_PSFB_OUTPUT_SR_DISABLE(); /* Turn off secondary side PWM */

	if( u16_rteshift > 2U )
	{
		u16_shift = u16_rteshift - 2U;
		RTE_SET_PHASE_SHIFT_VAL( u16_shift );
	}
	else
	{
		RTE_SET_PHASE_SHIFT_VAL( u16_shift );
		RTE_PSFB_OUTPUT_DISABLE(); /* Turn off primary side PWM */
		u8_Ret = 1U;
	}

	return ( u8_Ret );
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void RTE_SET_PHASE_SHIFT_VAL( uint16_t val )
{
	if( val > PHASE_SHIFT_MAX_VAL ){ rtePhaseShiftVal = PHASE_SHIFT_MAX_VAL; }
	else{ rtePhaseShiftVal = val; }
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
uint8_t RTE_GET_IGN3_STS( void )
{
	return rteVcuIgn3Sts;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
uint8_t RTE_GET_CMD_ENABLE_LDC( void )
{
	return rteVcuCmdEnLdc;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
uint32_t RTE_GET_CMD_TARGET_VOLT( void )
{
	return ( ( uint32_t )UTILS_VOUTREF_INV( rteVcuCmdLdcTargetVolt, AdcVout, Vout) << 5U );
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
uint32_t RTE_GET_DERATING_TARGET_VOLT( uint16_t deratingVolt )
{
	uint32_t u32_Ret;

	u32_Ret = ( ( uint32_t )UTILS_VOUTREF_INV( deratingVolt, AdcVout, Vout) << 5U );

	return ( u32_Ret );
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
LDC_MODE_DEF RTE_GET_LDC_MODE_STATUS( void )
{
	return rteLdcMode;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void RTE_SET_LDC_MODE_STATUS( LDC_MODE_DEF val )
{
	rteLdcMode = val;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
LdcDiagnosisType* RTE_GET_LDC_DIAGNOSIS_STATUS(void)
{
	return &rteStrLdcDiagnosisFlag;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void RTE_SET_LDC_DIAGNOSIS_STATUS( const LdcDiagnosisType* val )
{
	if( val != (void* )0 )
	{
		utils_memcpy( &rteStrLdcDiagnosisFlag, val, ( uint32_t )sizeof( LdcDiagnosisType ) );
	}
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
LDC_RUN_DEF RTE_GET_LDC_RUN_STATUS( void )
{
	return rteLdcRun;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void RTE_SET_LDC_RUN_STATUS( LDC_RUN_DEF val )
{
	rteLdcRun = val;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
ADC_results_t* RTE_GET_ADC_RAW_RESULT( void )
{
	return &rteAdcRawResult;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void RTE_SET_ADC_RAW_RESULT( const ADC_results_t* val )
{
	if( val != (void* ) 0 )
	{
		utils_memcpy( &rteAdcRawResult, val, ( uint32_t )sizeof( ADC_results_t ) );

		/* update real values */
#if ( !LDC_TEST_VALUES )
		rteAdcRealResult.realBatteryVoltage = RTE_GET_ADC_REAL_12VBAT();
		rteAdcRealResult.realInputCurrent = RTE_GET_ADC_REAL_IIN();
		rteAdcRealResult.realInputVoltage = RTE_GET_ADC_REAL_VIN();
		rteAdcRealResult.realKeyInVoltage = RTE_GET_ADC_REAL_KEYIN();
		rteAdcRealResult.realOutputCurrent = RTE_GET_ADC_REAL_IOUT();
		rteAdcRealResult.realOutputVoltage = RTE_GET_ADC_REAL_VOUT();
		rteAdcRealResult.realTemperature = RTE_GET_ADC_REAL_TEMP();
		rteAdcRealResult.realTemperatureSub = RTE_GET_ADC_REAL_SUB_TEMP();
#else
		rteAdcRealResult.realInputCurrent = testInCurr;
		rteAdcRealResult.realInputVoltage = testInVolt;
		rteAdcRealResult.realOutputCurrent = testOutCurr;
		rteAdcRealResult.realOutputVoltage = testOutVolt;
		rteAdcRealResult.realTemperature = testTemp;
		rteAdcRealResult.realTemperatureSub = testTempSub;
		rteAdcRealResult.realKeyInVoltage = testKeyIn;
		rteAdcRealResult.realBatteryVoltage = testBplus;
#endif
	}
	else
	{
		/* nothing to update */
	}
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
AdcRealValuesType* RTE_GET_ADC_REAL_RESULT( void )
{
	return &rteAdcRealResult;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void RTE_SET_ADC_REAL_RESULT( const AdcRealValuesType* val )
{
	if( val != ( void* ) 0 )
	{
		utils_memcpy( &rteAdcRealResult, val, ( uint32_t )sizeof( AdcRealValuesType ) );
	}
	else
	{
		/* nothing to update */
	}
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
uint16_t RTE_GET_ADC_RAW_VOUT( void )
{
	return ( uint16_t )rteAdcRawResult.OutputVoltage;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
uint16_t RTE_GET_ADC_RAW_IOUT( void )
{
	uint16_t rtv = 0U;

	if( rteAdcRawResult.OutputCurrent >= 401U )
	{
		rtv = ( uint16_t )rteAdcRawResult.OutputCurrent - 401U;
	}

	return rtv;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
LDC_DERATING_STAT RTE_GET_DERATING_STAT( void )
{
	return rteDeratingStatus;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void RTE_SET_DERATING_STAT( LDC_DERATING_STAT val )
{
	rteDeratingStatus = val;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void RTE_CAN_IL_TASK ( void )
{
	BSW_CAN_Il_TASK ();
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void RTE_CAN_Diag_TASK ( void )
{
	BSW_CAN_Diag_TASK ();
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void RTE_UPDATE_CAN_RX(void)
{
	static uint16_t u16s_CanTimeOutCnt = 0U;

	if( ! ( IlGetVCU_ReadyRxTimeout() ) ) /* if CAN Rx Timeout has no problem */
	{
		RTE_SET_CAN_TIMEOUT_COUNT( 0U );
		clrReg32Bits( u32g_LDC_ERR_Sts, DTC_U1102 );

		if( rteCanRxPathDisable == 0U )
		{
			RTE_SET_CMD_TARGET_VOLT( IlGetRxVCU_CMD_LDC_TARGT_VOLT() );
			RTE_SET_IGN3_STS( ( uint8_t )IlGetRxVCU_IGN3_STS() );
			RTE_SET_CMD_ENABLE_LDC( ( uint8_t )IlGetRxVCU_CMD_EN_LDC() );
		}
	}
	else
	{
		if( RTE_GET_CAN_TIMEOUT_COUNT() >= CAN_TIME_OUT_ERR_CNT ){ setReg32Bits( u32g_LDC_ERR_Sts, DTC_U1102 ); }
		else{ RTE_ADD_CAN_TIMEOUT_COUNT(); }
	}
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void RTE_UPDATE_CAN_TX( void )
{
	uint8_t u8_Checksum_3A0_Data[ 7 ];
	uint8_t u8_Checksum_3A0_Ret;
	uint8_t u8_Emergency = 0U;
	uint8_t u8_ServiceWarning = 0U;
	const AdcRealValuesType* ldcAdcRealValues = RTE_GET_ADC_REAL_RESULT();
	const LdcDiagnosisType* pDiagFlags = RTE_GET_LDC_DIAGNOSIS_STATUS();
	LDC_MODE_DEF ldcMode = RTE_GET_LDC_MODE_STATUS();
	LDC_RUN_DEF ldcRun = RTE_GET_LDC_RUN_STATUS();
	uint8_t flagInputOverVolt = yFALSE;
	uint8_t flagInputUnderVolt = yFALSE;

	uint8_t canTxTemperature = ( uint8_t )ldcAdcRealValues->realTemperature + 40U;
	uint8_t canTxInputCurr = ( uint8_t )ldcAdcRealValues->realInputCurrent;
	uint16_t canTxOutputCurr = ( uint16_t )ldcAdcRealValues->realOutputCurrent;
	uint16_t canTxInputVolt = ( uint16_t )ldcAdcRealValues->realInputVoltage;
	uint8_t canTxOutputVolt = ( uint8_t )ldcAdcRealValues->realOutputVoltage;
	uint8_t canTxSupplyVolt = ( uint8_t )ldcAdcRealValues->realBatteryVoltage;

	LDC_MODE_DEF canTxLdcModeStatus = RTE_GET_LDC_MODE_STATUS();

	if( RTE_GET_CAN_BUS_OFF_STATE() == yTRUE )
	{
		if( ldcAdcRealValues->realOutputCurrent != DIAG_FAIL_VALUE )
		{
			IlPutTxLDC_STS_CURR_OUT( ( uint16_t )ldcAdcRealValues->realOutputCurrent );
			IlPutTxLDC_STS_Power_OUT( ( ( ( uint16_t )ldcAdcRealValues->realOutputCurrent * ( uint16_t )ldcAdcRealValues->realOutputVoltage ) / 100U ) );
		}
		else
		{
			IlPutTxLDC_STS_CURR_OUT( 0U );
			IlPutTxLDC_STS_Power_OUT( 0U );
		}

		if( ldcAdcRealValues->realTemperature != DIAG_TEMP_FAIL_VALUE )
		{
			IlPutTxLDC_STS_TEMP( canTxTemperature ); /* LDC temperature : value '40' is offset to remove negertive value */
		}
		else
		{
			IlPutTxLDC_STS_TEMP( 0U + 40U); /* LDC temperature : value '40' is offset to remove negertive value */
		}

		/* LDC_3A1h */
		if( ldcAdcRealValues->realInputCurrent != DIAG_FAIL_VALUE )
		{
			IlPutTxLDC_STS_CURR_IN( canTxInputCurr );
		}
		else
		{
			IlPutTxLDC_STS_CURR_IN( 0U );
		}

		if( ldcAdcRealValues->realOutputCurrent != DIAG_FAIL_VALUE )
		{
			IlPutTxLDC_STS_CURR_OUT( canTxOutputCurr );
		}
		else
		{
			IlPutTxLDC_STS_CURR_OUT( 0U );
		}

		if( ldcAdcRealValues->realInputVoltage != DIAG_FAIL_VALUE )
		{
			IlPutTxLDC_STS_VOLT_IN( canTxInputVolt );
		}
		else
		{
			IlPutTxLDC_STS_VOLT_IN( 0U );
		}

		if( ldcAdcRealValues->realOutputVoltage != DIAG_FAIL_VALUE )
		{
			IlPutTxLDC_STS_VOLT_OUT( canTxOutputVolt );
		}
		else
		{
			IlPutTxLDC_STS_VOLT_OUT( 0U );
		}

		switch( canTxLdcModeStatus )
		{
		case LDC_MODE_READY :
			IlPutTxLDC_STS_MODE( 0x0U ); /* Normal */
			IlPutTxLDC_STS_Ready( 0x0U ); /* LDC not ready */
			break;

		case LDC_MODE_NORMAL :
			IlPutTxLDC_STS_MODE( 0x0U );
			IlPutTxLDC_STS_Ready( 0x1U ); /* LDC ready */
			IlPutTxLDC_Out_Mode( 0x0U );
			break;

		case LDC_MODE_FAILURE :
			IlPutTxLDC_STS_MODE( 0x2U );
			IlPutTxLDC_STS_Ready( 0x0U ); /* LDC not ready */
			break;

		case LDC_MODE_FAULT :
			IlPutTxLDC_STS_MODE( 0x1U );
			IlPutTxLDC_STS_Ready( 0x0U ); /* LDC not ready */
			break;

		case LDC_MODE_DERATING :
			IlPutTxLDC_STS_MODE( 0x3U);
			IlPutTxLDC_STS_Ready( 0x1U ); /* LDC ready */
			IlPutTxLDC_Out_Mode( 0x1U );
			break;

		default :
			IlPutTxLDC_STS_MODE( 0x0U ); /* warning */
			IlPutTxLDC_STS_Ready( 0x1U ); /* LDC ready */
			break;
		}

		if( RTE_GET_CMD_ENABLE_LDC() == 1 )
		{
			if( canTxLdcModeStatus == LDC_MODE_FAULT ){ u8_Emergency = 1U; }
			if( canTxLdcModeStatus == LDC_MODE_FAILURE ){ u8_ServiceWarning = 1U; }
		}

		IlPutTxLDC_Out_Emergency( u8_Emergency );
		IlPutTxLDC_Service_WRN_IND( u8_ServiceWarning );

		/* 3A0 */
		IlPutTxCounter_3A0h ( u8s_Counter_3A0 );

		u8_Checksum_3A0_Data[ 0 ] = LDC_3A0h._c[ 0 ];
		u8_Checksum_3A0_Data[ 1 ] = LDC_3A0h._c[ 1 ];
		u8_Checksum_3A0_Data[ 2 ] = LDC_3A0h._c[ 2 ];
		u8_Checksum_3A0_Data[ 3 ] = LDC_3A0h._c[ 3 ];
		u8_Checksum_3A0_Data[ 4 ] = LDC_3A0h._c[ 4 ];
		u8_Checksum_3A0_Data[ 5 ] = LDC_3A0h._c[ 5 ];
		u8_Checksum_3A0_Data[ 6 ] = LDC_3A0h._c[ 6 ];

		u8_Checksum_3A0_Ret = CRC8_Calc ( u8_Checksum_3A0_Data, 7U );
		IlPutTxChecksum_3A0h ( u8_Checksum_3A0_Ret );

		/* LDC PCAN STS */
		IlPutTxCMXVersion_LDC_PCAN ( CMX_VER );
		IlPutTxSupplyVoltage_LDC_PCAN ( canTxSupplyVolt );
		IlPutTxMsgAliveCnt_LDC_PCAN ( u8s_MsgAlive_cnt );
		IlPutTxRxErrCnt_LDC_PCAN ( CanRxActualErrorCounter () );
		IlPutTxTxErrCnt_LDC_PCAN ( CanTxActualErrorCounter () );
		IlPutTxBusOffCnt_LDC_PCAN ( rteCanBusOffCnt );
	}
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
uint16_t UTILS_VOUTREF_INV( uint16_t Ref, uint16_t AdcValue[ 19 ], uint16_t realValue[ 19 ] )
{
	uint8_t u8_Idx;
	uint16_t tmp_1;
	uint16_t tmp_2;
	uint16_t tmp_3;
	uint16_t temp;

	if( Ref < realValue[ 1 ] ){ u8_Idx = 0U; }
	else if( ( Ref >= realValue[ 1 ] ) && ( Ref < realValue[ 2 ] ) ){ u8_Idx = 1U; }
	else if( ( Ref >= realValue[ 2 ] ) && ( Ref < realValue[ 3 ] ) ){ u8_Idx = 2U; }
	else if( ( Ref >= realValue[ 3 ] ) && ( Ref < realValue[ 4 ] ) ){ u8_Idx = 3U; }
	else if( ( Ref >= realValue[ 4 ] ) && ( Ref < realValue[ 5 ] ) ){ u8_Idx = 4U; }
	else if( ( Ref >= realValue[ 5 ] ) && ( Ref < realValue[ 6 ] ) ){ u8_Idx = 5U; }
	else if( ( Ref >= realValue[ 6 ] ) && ( Ref < realValue[ 7 ] ) ){ u8_Idx = 6U; }
	else if( ( Ref >= realValue[ 7 ] ) && ( Ref < realValue[ 8 ] ) ){ u8_Idx = 7U; }
	else if( ( Ref >= realValue[ 8 ] ) && ( Ref < realValue[ 9 ] ) ){ u8_Idx = 8U; }
	else if( ( Ref >= realValue[ 9 ] ) && ( Ref < realValue[ 10 ] ) ){ u8_Idx = 9U; }
	else if( ( Ref >= realValue[ 10 ] ) && ( Ref < realValue[ 11 ] ) ){ u8_Idx = 10U; }
	else if( ( Ref >= realValue[ 11 ] ) && ( Ref < realValue[ 12 ] ) ){ u8_Idx = 11U; }
	else if( ( Ref >= realValue[ 12 ] ) && ( Ref < realValue[ 13 ] ) ){ u8_Idx = 12U; }
	else if( ( Ref >= realValue[ 13 ] ) && ( Ref < realValue[ 14 ] ) ){ u8_Idx = 13U; }
	else if( ( Ref >= realValue[ 14 ] ) && ( Ref < realValue[ 15 ] ) ){ u8_Idx = 14U; }
	else if( ( Ref >= realValue[ 15 ] ) && ( Ref < realValue[ 16 ] ) ){ u8_Idx = 15U; }
	else if( ( Ref >= realValue[ 16 ] ) && ( Ref < realValue[ 17 ] ) ){ u8_Idx = 16U; }
	else if( ( Ref >= realValue[ 17 ] ) && ( Ref < realValue[ 18 ] ) ){ u8_Idx = 17U; }
	else{ u8_Idx = 18U; }

	if( u8_Idx <= 17U )
	{
		tmp_1 = ( AdcValue[ u8_Idx + 1U ] - AdcValue[ u8_Idx ] ) * ( Ref - realValue[ u8_Idx ] );
		tmp_2 = realValue[ u8_Idx + 1U ] - realValue[ u8_Idx ];
		tmp_3 = tmp_1 / tmp_2;
		temp = AdcValue[ u8_Idx ] + tmp_3;
	}
	else
	{
		temp = AdcValue[ 18 ];
	}

	return ( temp );
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
uint16_t UTILS_ADC2REAL( uint16_t AverAdc, uint16_t adcTable[ 19 ], uint16_t realTable[ 19 ] )
{
	uint8_t u8_Idx;
	uint16_t tmp_1;
	uint16_t tmp_2;
	uint16_t tmp_3;
	uint16_t temp;

	if( AverAdc < adcTable[ 0 ] )
	{
		temp = 0U;
	}
	else
	{
		if( ( AverAdc >= adcTable[ 0 ]) && ( AverAdc < adcTable[ 1 ] ) ){ u8_Idx = 0U; }
		else if( ( AverAdc >= adcTable[ 1 ] ) && ( AverAdc < adcTable[ 2 ] ) ){ u8_Idx = 1U; }
		else if( ( AverAdc >= adcTable[ 2 ] ) && ( AverAdc < adcTable[ 3 ] ) ){ u8_Idx = 2U; }
		else if( ( AverAdc >= adcTable[ 3 ] ) && ( AverAdc < adcTable[ 4 ] ) ){ u8_Idx = 3U; }
		else if( ( AverAdc >= adcTable[ 4 ] ) && ( AverAdc < adcTable[ 5 ] ) ){ u8_Idx = 4U; }
		else if( ( AverAdc >= adcTable[ 5 ] ) && ( AverAdc < adcTable[ 6 ] ) ){ u8_Idx = 5U; }
		else if( ( AverAdc >= adcTable[ 6 ] ) && ( AverAdc < adcTable[ 7 ] ) ){ u8_Idx = 6U; }
		else if( ( AverAdc >= adcTable[ 7 ] ) && ( AverAdc < adcTable[ 8 ] ) ){ u8_Idx = 7U; }
		else if( ( AverAdc >= adcTable[ 8 ] ) && ( AverAdc < adcTable[ 9 ] ) ){ u8_Idx = 8U; }
		else if( ( AverAdc >= adcTable[ 9 ] ) && ( AverAdc < adcTable[ 10 ] ) ){ u8_Idx = 9U; }
		else if( ( AverAdc >= adcTable[ 10 ] ) && ( AverAdc < adcTable[ 11 ] ) ){ u8_Idx = 10U; }
		else if( ( AverAdc >= adcTable[ 11 ] ) && ( AverAdc < adcTable[ 12 ] ) ){ u8_Idx = 11U; }
		else if( ( AverAdc >= adcTable[ 12 ] ) && ( AverAdc < adcTable[ 13 ] ) ){ u8_Idx = 12U; }
		else if( ( AverAdc >= adcTable[ 13 ] ) && ( AverAdc < adcTable[ 14 ] ) ){ u8_Idx = 13U; }
		else if( ( AverAdc >= adcTable[ 14 ] ) && ( AverAdc < adcTable[ 15 ] ) ){ u8_Idx = 14U; }
		else if( ( AverAdc >= adcTable[ 15 ] ) && ( AverAdc < adcTable[ 16 ] ) ){ u8_Idx = 15U; }
		else if( ( AverAdc >= adcTable[ 16 ] ) && ( AverAdc < adcTable[ 17 ] ) ){ u8_Idx = 16U; }
		else if( ( AverAdc >= adcTable[ 17 ] ) && ( AverAdc < adcTable[ 18 ] ) ){ u8_Idx = 17U; }
		else{ u8_Idx = 18U; }

		if( u8_Idx <= 17U )
		{
			tmp_1 = ( realTable[ u8_Idx + 1U ] - realTable[ u8_Idx ] ) * ( AverAdc - adcTable[ u8_Idx ] );
			tmp_2 = adcTable[ u8_Idx + 1U ] - adcTable[ u8_Idx ];
			tmp_3 = tmp_1 / tmp_2;
			temp = realTable[ u8_Idx ] + tmp_3;
		}
		else
		{
			temp = realTable[ 18 ];
		}
	}

	return ( temp );
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void RTE_BattLvl_Check ( void )
{
	u16s_BattLvl = RTE_GET_ADC_REAL_12VBAT();

	switch( u8s_BattLvlSts )
	{
		case BATT_NORMAL:
			Batt_normal ();
			break;
		case BATT_NORMAL_DLY:
			Batt_normal_dly ();
			break;
		case BATT_ERROR_DLY:
			Batt_error_dly ();
			break;
		case BATT_ERROR:
			Batt_error ();
			break;
		default:
			u8s_BattLvlSts = BATT_NORMAL;
			break;
	}

	return;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void ApplCounter_3A0hSigConfirmation( void )
{
	u8s_Counter_3A0++;
	if( u8s_Counter_3A0 > 15 ){ u8s_Counter_3A0 = 0U; }

	return;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void ApplMsgAliveCnt_LDC_PCANSigConfirmation( void )
{
	u8s_MsgAlive_cnt++;
	if( u8s_MsgAlive_cnt > 254 ){ u8s_MsgAlive_cnt = 0U; }

	return;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void CRC8_Init ( void )
{
	Crc8TableGenerator ( POLYNOMINAL, u8s_CrcTable8bit );
}

/****************************************************************************/
/**                                                                        **/
/**                      LOCAL FUNCTIONS                                   **/
/**                                                                        **/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void RTE_SET_CMD_TARGET_VOLT( uint16_t val )
{
	if( val > CMD_TARGET_VOLT_MAX ){ rteVcuCmdLdcTargetVolt = CMD_TARGET_VOLT_MAX; }
	else{	rteVcuCmdLdcTargetVolt = val; }
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void RTE_ADD_CAN_TIMEOUT_COUNT(void)
{
	rteCanTimeoutCnt++;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void RTE_SET_CAN_TIMEOUT_COUNT( uint16_t val)
{
	rteCanTimeoutCnt = val;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static uint16_t RTE_GET_CAN_TIMEOUT_COUNT( void )
{
	return rteCanTimeoutCnt;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void RTE_SET_IGN3_STS( uint8_t val )
{
	rteVcuIgn3Sts = 0U;

	if( val == 1U ){ rteVcuIgn3Sts = 1U; }
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void RTE_SET_CMD_ENABLE_LDC( uint8_t val )
{
	if( val > 1U ){ rteVcuCmdEnLdc = 1U; }
	else{ rteVcuCmdEnLdc = val; }
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static uint16_t RTE_GET_ADC_REAL_IOUT( void )
{
	static uint16_t AdcIout[ 19 ] = {423,582,746,908,1074,1232,1400,1562,1736,1898,2066,2228,2388,2468,2548,2628,2708,2869,3674};
	static uint16_t Iout[ 19 ] = {0,100,200,300,400,500,600,700,800,900,1000,1100,1200,1250,1300,1350,1400,1500,2000};
	static uint16_t u16s_IoutFailureCnt = 0U;
	static uint8_t u8s_IoutFailureTime = 0U;
	static uint8_t u8s_IoutReadyCnt = 0U;
	uint16_t realVal = 0U;

	if( rteAdcRawResult.OutputCurrent > ADC_FAILURE_IOUT )
	{
		u16s_IoutFailureCnt = 0U;
		u8s_IoutReadyCnt = 1U;
		realVal = UTILS_ADC2REAL( rteAdcRawResult.OutputCurrent , AdcIout, Iout );
		clrReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1105 ) );
	}
	else
	{
		if( u16s_IoutFailureCnt >= SENSOR_ERR_CNT )
		{
			realVal = DIAG_FAIL_VALUE;
			setReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1105 ) );
			if( u8s_IoutReadyCnt == 1U )
			{
				u8s_IoutFailureTime++;
				u8s_IoutReadyCnt = 0U;
			}
		}
		else
		{
			u16s_IoutFailureCnt++;
		}
	}

	if( u8s_IoutFailureTime >= 3U ) /* 3times */
	{
		setReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1105 ) );
	}

	return realVal;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static uint16_t RTE_GET_ADC_REAL_IIN( void )
{
	static uint16_t u16s_IinFailureCnt = 0U;
	static uint8_t u8s_IinFailureTime = 0U;
	static uint8_t u8s_IinReadyCnt = 0U;
	uint16_t rtv = 0;
	uint16_t realVal = 0U;

	if( rteAdcRawResult.InputCurrent > ADC_FAILURE_IIN )
	{
		if(rteAdcRawResult.InputCurrent >= 411)
		{
			rtv = rteAdcRawResult.InputCurrent - 411;
		}

		u16s_IinFailureCnt = 0U;
		u8s_IinReadyCnt = 1U;
		realVal = UTILS_IIN_INV( rtv );
		clrReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1104 ) );

	}
	else
	{
		if( u16s_IinFailureCnt >= SENSOR_ERR_CNT )
		{
			realVal = DIAG_FAIL_VALUE;
			setReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1104 ) );
			if( u8s_IinReadyCnt == 1U )
			{
				u8s_IinFailureTime++;
				u8s_IinReadyCnt = 0U;
			}
		}
		else
		{
			u16s_IinFailureCnt++;
		}
	}

	if( u8s_IinFailureTime >= 3U ) /* 3 times 0*/
	{
		setReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1104 ) );
	}

	return realVal;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static uint16_t RTE_GET_ADC_REAL_VIN( void )
{
	static uint16_t AdcVin[ 19 ] = {568,642,687,779,825,869,961,1051,1095,1143,1234,1373,1508,1643,1780,1918,2053,2188,2284};
	static uint16_t Vin[ 19 ] = {0,0,1500,1700,1800,1900,2100,2300,2400,2500,2700,3000,3300,3600,3900,4200,4500,4800,5000};
	uint16_t realVal = DIAG_FAIL_VALUE;

	if( rteAdcRawResult.InputVoltage > ADC_FAILURE_VIN )
	{
		realVal = UTILS_ADC2REAL( rteAdcRawResult.InputVoltage, AdcVin, Vin );
	}

	return realVal;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static uint16_t RTE_GET_ADC_REAL_VOUT( void )
{
	uint16_t realVal = DIAG_FAIL_VALUE;

	if( rteAdcRawResult.OutputVoltage > ADC_FAILURE_VOUT )
	{
		realVal = UTILS_ADC2REAL( rteAdcRawResult.OutputVoltage, AdcVout, Vout );
	}

	return realVal;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static int16_t RTE_GET_ADC_REAL_TEMP( void )
{
	int16_t realVal = 0;
	static uint16_t u16s_TempShortCnt = 0U;
	static uint16_t u16s_TempOpenCnt = 0U;
	static uint8_t u8s_TempFailureTime = 0U;
	static uint8_t u8s_TempReadyCnt = 0U;

	if( rteAdcRawResult.Temperature < ADC_FAILURE_TEMP_SHORT )
	{
		if( u16s_TempShortCnt >= TEMP_SENSOR_SHORT_ERR_CNT )
		{
			realVal = DIAG_TEMP_FAIL_VALUE;
			setReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1106 ) );

			if( u8s_TempReadyCnt == 1U )
			{
				u8s_TempFailureTime++;
				u8s_TempReadyCnt = 0U;
			}
		}
		else
		{
			u16s_TempShortCnt++;
		}
	}
	else if( ( rteAdcRawResult.Temperature >= ADC_FAILURE_TEMP_SHORT) && ( rteAdcRawResult.Temperature < ADC_FAILURE_TEMP_OPEN ) )
	{
		u16s_TempShortCnt = 0U;
		u16s_TempOpenCnt = 0U;
		u8s_TempReadyCnt = 1U;
		realVal = UTILS_TEMP_INV( ( int16_t )rteAdcRawResult.Temperature );
		clrReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1106 ) );
	}
	else
	{
		if( u16s_TempOpenCnt >= TEMP_SENSOR_OPEN_ERR_CNT )
		{
			realVal = DIAG_TEMP_FAIL_VALUE;
			setReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1106 ) );
			if( u8s_TempReadyCnt == 1U )
			{
				u8s_TempFailureTime++;
				u8s_TempReadyCnt = 0U;
			}
		}
		else
		{
			u16s_TempOpenCnt++;
		}
	}

	if( u8s_TempFailureTime >= 3U ) /* 3 times */
	{
		setReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1106 ) );
	}

	return realVal;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static int16_t RTE_GET_ADC_REAL_SUB_TEMP( void )
{
	return UTILS_TEMP_INV( ( int16_t )rteAdcRawResult.TemperatureSub );
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static uint16_t RTE_GET_ADC_REAL_KEYIN( void )
{
	static uint16_t AdcKeyIn[ 19 ] = {3,195,376,574,764,954,1142,1318,1524,1720,1913,2100,2287,2484,2674,2863,3048,3404,3702};
	static uint16_t KeyIn[ 19 ] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,180,200};
	uint16_t u16_Ret;

	u16_Ret = UTILS_ADC2REAL( rteAdcRawResult.KeyInVoltage, AdcKeyIn, KeyIn );

	return ( u16_Ret );
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static uint16_t RTE_GET_ADC_REAL_12VBAT( void )
{
	uint16_t u16_Ret;

	static uint16_t AdcBplus[ 19 ] = {1,190,377,565,752,944,1129,1323,1513,1700,1890,2077,2269,2455,2642,2837,3014,3376,3695};
	static uint16_t Bplus[ 19 ] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,180,200};

	u16_Ret = UTILS_ADC2REAL( rteAdcRawResult.BatteryVoltage, AdcBplus, Bplus );

	return ( u16_Ret );
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Batt_normal ( void )
{
	u8s_BattLvlSts = BATT_NORMAL;

	if( ( u16s_BattLvl > 180 ) || ( u16s_BattLvl < 70 ) )
	{
		u8s_BattErrorStsCnt = 0U;
		u8s_BattLvlSts = BATT_ERROR_DLY;
	}

	return;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Batt_normal_dly ( void )
{
	u8s_BattLvlSts = BATT_NORMAL_DLY;

	if( ( u16s_BattLvl <= 180 ) && ( u16s_BattLvl >= 70 ) )
	{
		u8s_BattNormalStsCnt++;
		if( u8s_BattNormalStsCnt >= 20 )
		{
			CanPartOnline ( C_SEND_GRP_APPL );
			u8s_BattLvlSts = BATT_NORMAL;
		}
	}
	else
	{
		u8s_BattLvlSts = BATT_ERROR;
	}

	return;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Batt_error_dly ( void )
{
	u8s_BattLvlSts = BATT_ERROR_DLY;

	if( ( u16s_BattLvl > 180 ) || ( u16s_BattLvl < 70 ) )
	{
		u8s_BattErrorStsCnt++;
		if( u8s_BattErrorStsCnt >= 45 )
		{
			CanPartOffline ( C_SEND_GRP_APPL );
			u8s_BattLvlSts = BATT_ERROR;
		}
	}
	else
	{
		u8s_BattLvlSts = BATT_NORMAL;
	}

	return;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Batt_error ( void )
{
	u8s_BattLvlSts = BATT_ERROR;

	if( ( u16s_BattLvl <= 180 ) && ( u16s_BattLvl >= 70 ) )
	{
		u8s_BattNormalStsCnt = 0U;
		u8s_BattLvlSts = BATT_NORMAL_DLY;
	}

	return;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static uint8_t CRC8_Calc ( uint8_t *u8p_Data, uint32_t u32_Size )
{
	uint8_t u8_CalcRet;

	/* CRC8 (SAE-J1850) */
	u8_CalcRet = CalculateCRC8 ( u8s_CrcTable8bit, u8p_Data, u32_Size, INIT_VALUE, XOR_VALUE );

	return ( u8_CalcRet );
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Crc8TableGenerator ( uint8_t u8_Polynomial, uint8_t u8_CrcTable[ 256 ] )
{
	uint8_t u8_Remainder;
	uint8_t u8_TopBit = 0x80;
	uint8_t u8_Bit;
	uint32_t u32_Dividend;

	for( u32_Dividend = 0; u32_Dividend < 256; u32_Dividend++ )
	{
		u8_Remainder = ( uint8_t )u32_Dividend;

		for( u8_Bit = 0; u8_Bit < 8; u8_Bit++ )
		{
			if( ( u8_Remainder & u8_TopBit ) == 0 )
			{
				u8_Remainder <<= 1;
			}
			else
			{
				u8_Remainder = ( u8_Remainder << 1 ) ^ u8_Polynomial;
			}
		}

		u8_CrcTable[ u32_Dividend ] = u8_Remainder;
	}

	return;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static uint8_t CalculateCRC8 ( uint8_t u8_CrcTable[ 256 ], const uint8_t *u8p_Crc_DataPtr, uint32_t u32_Crc_Len, uint8_t u8_Crc_InitialValue, uint8_t u8_Crc_XorValue )
{
	uint8_t u8_Temp;
	uint8_t u8_Crc = u8_Crc_InitialValue;
	uint32_t u32_Counter;

	for( u32_Counter = 0U; u32_Counter < u32_Crc_Len; u32_Counter++ )
	{
		u8_Temp = *u8p_Crc_DataPtr;

		u8_Crc = u8_Crc ^ u8_Temp;
		u8_Crc = u8_CrcTable[ u8_Crc ];
		u8p_Crc_DataPtr++;
	}

	u8_Crc ^= u8_Crc_XorValue;

	return ( u8_Crc );
}

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
