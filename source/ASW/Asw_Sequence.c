/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : E100_LDC                                                    **
**  Filename  : Asw_Sequence.c                                              **
**  Version   : -.- (PCB : )                                                **
**  Date      : 2019.08.01                                                  **
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
Revised by  : Tran Duc Hung
Description : Original version.

*/

#define ASW_SEQUENCE_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "Asw_Sequence.h"
#include "../RTE/Rte_AswBswLink.h"
#include "Asw_PiController.h"
#include "Asw_DiagAdc.h"

/****************************************************************************/
/**                                                                        **/
/**                      DEFINITIONS AND MACROS                            **/
/**                                                                        **/
/****************************************************************************/

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
static void Seq_RunNormal( uint8_t cmdLdcEnable, uint32_t cmdTargetVolt );
static void Seq_RunWarning( uint8_t cmdLdcEnable, uint32_t cmdTargetVolt );
static void Seq_RunFault( void );
static void Seq_RunFailure( void );
static void Seq_RunDerating( uint8_t cmdLdcEnable, uint32_t cmdTargetVolt, LDC_DERATING_STAT deratingStat );
static void Seq_Control_LdcRun( uint8_t cmdLdcEnable, uint32_t cmdTargetVolt, uint32_t cmdTargetCur );
static void Seq_StateStandby( void );
static void Seq_StatePowerOn( uint16_t phaseShifVal );

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                      GLOBAL VARIABLES                                  **/
/**                                                                        **/
/****************************************************************************/
/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
static uint8_t u8s_Wait_RS_cnt = 0U;

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void Seq_OperateLdc( void )
{
	LDC_MODE_DEF ldcModeState = RTE_GET_LDC_MODE_STATUS(); /* Updated LDC mode */
	LDC_DERATING_STAT ldcDeratingStat = RTE_GET_DERATING_STAT();

	uint8_t ldcEnableSig = RTE_GET_CMD_ENABLE_LDC(); /* LDC Enable signal*/
	uint32_t refVal = RTE_GET_CMD_TARGET_VOLT();

	switch( ldcModeState )
	{
	case LDC_MODE_NORMAL :
		Seq_RunNormal( ldcEnableSig, refVal );
		break;
	case LDC_MODE_DERATING :
		Seq_RunDerating( ldcEnableSig, refVal, ldcDeratingStat );
		break;
	case LDC_MODE_FAULT :
		Seq_RunFault();
		break;
	case LDC_MODE_FAILURE :
		Seq_RunFailure();
		break;
	default :
		Seq_RunWarning( ldcEnableSig, refVal );
		break;
	}
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Seq_RunNormal( uint8_t cmdLdcEnable, uint32_t cmdTargetVolt )
{
	if( cmdTargetVolt > 0U )
	{
		Seq_Control_LdcRun( cmdLdcEnable, cmdTargetVolt, ( uint32_t )SATURATION_CUR_160 );
	}
	else
	{
		Seq_Control_LdcRun( 0U, 0U, 0U );
	}
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Seq_RunWarning( uint8_t cmdLdcEnable, uint32_t cmdTargetVolt )
{
	if( cmdTargetVolt > 0U )
	{
		Seq_Control_LdcRun( cmdLdcEnable, cmdTargetVolt, ( uint32_t )SATURATION_CUR_160 );
	}
	else
	{
		Seq_Control_LdcRun( 0U, 0U, 0U );
	}
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Seq_RunDerating( uint8_t cmdLdcEnable, uint32_t cmdTargetVolt, LDC_DERATING_STAT deratingStat )
{
	uint32_t refVolt = cmdTargetVolt;
	uint32_t refVoltCurr = 0U;

	switch( deratingStat )
	{
	case DERARING_CURR_LV01 :
		refVoltCurr = ( uint32_t )SATURATION_CUR_160;
		break;
	case DERARING_CURR_LV02 :
		refVoltCurr = ( uint32_t )SATURATION_CUR_128;
		break;
	case DERARING_TEMP_LV01 :
		refVoltCurr = ( uint32_t )( ( SATURATION_CUR_128 * 80 ) / 100 ); /* reduce output current from 100% to 80% */
		break;
	case DERARING_TEMP_LV02 :
		refVoltCurr = ( uint32_t )( ( SATURATION_CUR_128 * 50 ) / 100 ); /* reduce output current from 100% to 50% */
		break;
	case DERARING_TEMP_LV03 :
		refVoltCurr = ( uint32_t )( ( SATURATION_CUR_128 * 20 ) / 100 ); /* reduce output current from 100% to 20% */
		break;
	case DERARING_VOLT:
		refVoltCurr = ( uint32_t )SATURATION_CUR_128;
		if( DERATING_REF_VOLT <= refVolt )
		{
			refVolt = RTE_GET_DERATING_TARGET_VOLT( DERATING_REF_VOLT );
		}
		break;
	default : /* normal */
		refVoltCurr = ( uint32_t )SATURATION_CUR_160;
		break;
	}

	Seq_Control_LdcRun( cmdLdcEnable, refVolt, refVoltCurr );
}


/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Seq_RunFault( void )
{
	Seq_Control_LdcRun( 0U, 0U, 0U );
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Seq_RunFailure( void )
{
	Seq_Control_LdcRun( 0U, 0U, 0U ); /* 0U is LDC_RUN_STANDBY */
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Seq_Control_LdcRun( uint8_t cmdLdcEnable, uint32_t cmdTargetVolt, uint32_t cmdTargetCur )
{
	uint16_t phaseShifVal = 0U;

	if( ( cmdLdcEnable == 1U ) && ( u8g_Restart_Request == 0U ) ) /* LDC_RUN_POWERON */
	{
		if( u16g_StartPwmOn_cnt >= 1500U )
		{
			phaseShifVal = PiCtrl_DigitalCompensator( cmdTargetVolt, cmdTargetCur );
			Seq_StatePowerOn( phaseShifVal );
			RTE_SET_LDC_RUN_STATUS( LDC_RUN_POWERON );
		}
		else
		{
			u16g_StartPwmOn_cnt++;
		}
	}
	else /* LDC_RUN_STANDBY */
	{
		u16g_StartPwmOn_cnt = 0U;
		u16g_StartSrOn_cnt = 0U;
		Seq_StateStandby();
		RTE_SET_LDC_RUN_STATUS( LDC_RUN_STANDBY );
	}
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Seq_StateStandby( void )
{
	if( RTE_SOFT_STOP( RTE_GET_PHASE_SHIFT_VAL() ) == 1U )
	{
		RTE_ASW_PI_CTRL_Init();
	}

	if( u8g_Restart_Request == 1U )
	{
		u16g_p1109Err_Cnt = 0;
		u8g_P1109_FaultReadyCnt = 1U;

		if( u8s_Wait_RS_cnt > 10U )
		{
			u8g_Restart_Request = 0U;
		}
		else
		{
			u8s_Wait_RS_cnt++;
		}
	}

	u8g_softstart_end = 0U;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Seq_StatePowerOn( uint16_t phaseShifVal )
{
	RTE_SET_PHASE_SHIFT_VAL( phaseShifVal );
	RTE_PSFB_OUTPUT_ENABLE();
	RTE_PSFB_SET_SR_OUTPUT_Ctrl(); /* secondary enable */
	u8s_Wait_RS_cnt = 0;
	u8g_P1109_FaultReadyCnt = 1U;
}

/****************************************************************************/
/**                                                                        **/
/**                      LOCAL FUNCTIONS                                   **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
