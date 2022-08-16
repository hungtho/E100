/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : E100_LDC                                                    **
**  Filename  : Asw_CtrlLdcMode.c                                           **
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

#define ASW_CTRLLDCMODE_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "Asw_CtrlLdcMode.h"
#include "Rte_Cal.h"

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
static uint8_t IsChangeModeNormal( const LdcDiagnosisType* FaultDetectedFlag );
static uint8_t IsChangeModeFailure( const LdcDiagnosisType* FaultDetectedFlag, LDC_MODE_DEF ldcModeStatus, const AdcRealValuesType* adcValues );
static uint8_t IsChangeModeFault( const LdcDiagnosisType* FaultDetectedFlag, LDC_MODE_DEF ldcModeStatus, LDC_RUN_DEF ldcRunStatus, const AdcRealValuesType* adcValues );
static uint8_t IsChangeModeDerating( const LdcDiagnosisType* FaultDetectedFlag, const AdcRealValuesType* adcValues );
static void CurrDeratingMng( LDC_DERATING_STAT deratingStat );
static void ResetModeTimers( void );

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/
uint8_t ldcFaultCount = 0U;
uint8_t ldcFailureCount = 0U;

/****************************************************************************/
/**                                                                        **/
/**                      GLOBAL VARIABLES                                  **/
/**                                                                        **/
/****************************************************************************/
static uint32_t ldcFailureTimer = 0U;
static uint32_t ldcFaultTimer = 0U;
static uint32_t currDeratingLv01Timer = 0U;
static uint32_t currDeratingLv02Timer = 0U;

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
void CtrlLdcMode_UpdateLdcMode( const LdcDiagnosisType* faultDetectedResult, const AdcRealValuesType* adcValues )
{
	LDC_MODE_DEF ldcModeState = RTE_GET_LDC_MODE_STATUS(); /* 모드 변경 전 현재 LDC 모드 값 */
	LDC_RUN_DEF ldcRunState = RTE_GET_LDC_RUN_STATUS(); /* 현재 LDC 출력상태 */

	if( ( ldcModeState == LDC_MODE_NORMAL ) || ( ldcModeState == LDC_MODE_WARNING ) )
	{
		if( IsChangeModeNormal( faultDetectedResult ) == yTRUE )
		{
			RTE_SET_LDC_MODE_STATUS( LDC_MODE_NORMAL );

			ResetModeTimers();
		}
#if ( FAILURE_IN_USE )
		else if( IsChangeModeFailure( faultDetectedResult, ldcModeState, adcValues) == yTRUE )
		{
			ldcFailureTimer += TASK_PRD_1MS;
			if( ldcFailureTimer >= MODE_ENTRY_TIME )
			{
				RTE_SET_LDC_MODE_STATUS( LDC_MODE_FAILURE );
				ldcFailureCount++;
				ldcFailureTimer = 0;
			}
			else
			{
				RTE_SET_LDC_MODE_STATUS( LDC_MODE_WARNING );
			}
		}
#endif
#if ( FAULT_IN_USE )
		else if( IsChangeModeFault( faultDetectedResult, ldcModeState, ldcRunState, adcValues ) == yTRUE )
		{
			ldcFaultTimer += TASK_PRD_1MS;
			if( ldcFaultTimer >= MODE_ENTRY_TIME )
			{
				RTE_SET_LDC_MODE_STATUS( LDC_MODE_FAULT );
				ldcFaultCount++;
				ldcFaultTimer = 0;
			}
			else
			{
				RTE_SET_LDC_MODE_STATUS( LDC_MODE_WARNING );
			}
		}
#endif /* end of FAULT_IN_USE */
#if ( DERATING_IN_USE ) /* need to define mode De-rating */
		else if( IsChangeModeDerating( faultDetectedResult, adcValues ) == yTRUE )
		{
			RTE_SET_LDC_MODE_STATUS( LDC_MODE_DERATING );
			ResetModeTimers();
		}
#endif /* end of DERATING_IN_USE */
		else
		{
			RTE_SET_LDC_MODE_STATUS( LDC_MODE_WARNING );
			ResetModeTimers();
		}
	}
#if ( FAILURE_IN_USE )
	else if( ldcModeState == LDC_MODE_FAILURE )
	{
		if( ldcFailureCount >= MODE_FAILURE_MAX )
		{
			RTE_SET_LDC_MODE_STATUS( LDC_MODE_FAILURE );
		}
		else
		{
			if( IsChangeModeFailure( faultDetectedResult, ldcModeState, adcValues) == yTRUE )
			{
				RTE_SET_LDC_MODE_STATUS( LDC_MODE_FAILURE );  /* stay to mode Failure */
			}
			else if( IsChangeModeNormal( faultDetectedResult ) == yTRUE )
			{
				RTE_SET_LDC_MODE_STATUS( LDC_MODE_NORMAL ); /* move to mode Normal */
			}
			else
			{
				RTE_SET_LDC_MODE_STATUS( LDC_MODE_WARNING );
			}
		}
	}
#endif
#if ( FAULT_IN_USE )
	else if( ldcModeState == LDC_MODE_FAULT )
	{
		if( ldcFaultCount >= MODE_FAULT_MAX )  /* Normal->Fault */
		{
			RTE_SET_LDC_MODE_STATUS( LDC_MODE_FAULT ); /* stay to mode Fault */
		}
		else
		{
			if( IsChangeModeFailure( faultDetectedResult, ldcModeState, adcValues ) == yTRUE )
			{
				RTE_SET_LDC_MODE_STATUS( LDC_MODE_FAILURE );
			}
			else if( IsChangeModeFault( faultDetectedResult, ldcModeState, ldcRunState, adcValues) == yTRUE )
			{
				RTE_SET_LDC_MODE_STATUS( LDC_MODE_FAULT );  /* stay to mode Fault */
			}
			else if( IsChangeModeNormal( faultDetectedResult ) == yTRUE)
			{
				RTE_SET_LDC_MODE_STATUS( LDC_MODE_NORMAL ); /* move to mode Normal */
			}
			else
			{
				RTE_SET_LDC_MODE_STATUS( LDC_MODE_WARNING );
			}
		}
	}
#endif
#if ( DERATING_IN_USE )
	else if( ldcModeState == LDC_MODE_DERATING )
	{
		LDC_DERATING_STAT ldcDeratingStat =  RTE_GET_DERATING_STAT();

		if( IsChangeModeFault( faultDetectedResult, ldcModeState, ldcRunState, adcValues) == yTRUE )
		{
			RTE_SET_LDC_MODE_STATUS( LDC_MODE_FAULT );  /* stay to mode Fault */
			RTE_SET_DERATING_STAT( DERARING_NOT_USE );
			currDeratingLv01Timer = 0U;
			currDeratingLv02Timer = 0U;
		}
		else if( IsChangeModeDerating( faultDetectedResult, adcValues ) == yTRUE)
		{
			RTE_SET_LDC_MODE_STATUS( LDC_MODE_DERATING );
		}
		else if( IsChangeModeNormal( faultDetectedResult) == yTRUE )
		{
			RTE_SET_LDC_MODE_STATUS( LDC_MODE_NORMAL );
		}
		else
		{
			RTE_SET_LDC_MODE_STATUS( LDC_MODE_WARNING );
		}

		if( RTE_GET_LDC_MODE_STATUS() != LDC_MODE_DERATING )
		{
			RTE_SET_DERATING_STAT( DERARING_NOT_USE ); /* break mode de-rating */
		}
	}
#endif /* end of DERATING_IN_USE */
	else
	{
		RTE_SET_LDC_MODE_STATUS( LDC_MODE_WARNING );
	}
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static uint8_t IsChangeModeNormal( const LdcDiagnosisType* FaultDetectedFlag )
{
	uint8_t rtnVal = yFALSE;

	if( ( FaultDetectedFlag->Diag_HV_I == yTRUE )
	 && ( FaultDetectedFlag->Diag_HV_V == yTRUE )
   && ( FaultDetectedFlag->Diag_LV_I == yTRUE )
	 && ( FaultDetectedFlag->Diag_LV_V == yTRUE )
	 && ( FaultDetectedFlag->Diag_LdcTemp == yTRUE )
   && ( FaultDetectedFlag->Diag_LdcTempSub == yTRUE )
	 && ( FaultDetectedFlag->Diag_CanBusOffSts == yTRUE )
#if ( DIAG_CURR_PEAK_ON )
	 && ( FaultDetectedFlag->Diag_LV_PeakCurr == yTRUE )
#endif
	 && ( FaultDetectedFlag->Diag_dtc_P1107 == yTRUE )
	 && ( FaultDetectedFlag->Diag_dtc_P1109 == yTRUE ))
	{
		rtnVal = yTRUE;
	}

	return ( rtnVal );
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static uint8_t IsChangeModeDerating( const LdcDiagnosisType* FaultDetectedFlag, const AdcRealValuesType* adcValues )
{
	uint8_t rtnVal = yTRUE;
	int16_t adcRealTemp = adcValues->realTemperature;
	uint16_t adcRealOutputCurr = adcValues->realOutputCurrent;
	uint16_t adcRealInputVolt = adcValues->realInputVoltage;
	LDC_DERATING_STAT ldcDeratingStat =  RTE_GET_DERATING_STAT();

	if(
#if ( DIAG_TEMP_ON )
			( FaultDetectedFlag->Diag_LdcTemp == yFALSE )
#endif
#if ( DIAG_OUT_CURR_ON )
	 || ( FaultDetectedFlag->Diag_LV_I == yFALSE )
#endif
#if ( DIAG_IN_VOLT_ON )
	 || ( FaultDetectedFlag->Diag_HV_V == yFALSE )
#endif
	 || ( ldcDeratingStat != DERARING_NOT_USE ) )
	{
		/* derating */
		if( ( ( adcRealOutputCurr > OUT_CURR_NOR_PWO_MAX ) && ( adcRealOutputCurr <= OUT_CURR_WAR_PWO_MAX ) )
		 || ( ( ldcDeratingStat == DERARING_CURR_LV01 ) || ( ldcDeratingStat == DERARING_CURR_LV02 ) ) )
		{
			if( ( currDeratingLv01Timer > 0U ) || ( currDeratingLv02Timer > 0U )
				|| ( ldcDeratingStat == DERARING_CURR_LV02 )
					)
			{
				CurrDeratingMng(ldcDeratingStat);
			}
			else
			{
				RTE_SET_DERATING_STAT( DERARING_CURR_LV01 ); /* over current 128A */
				CurrDeratingMng( DERARING_CURR_LV01 );
			}
		}
		else if( ( adcRealTemp > TEMP_NOR_MAX ) || ( ldcDeratingStat == DERARING_TEMP_LV01 )
				  || ( ldcDeratingStat == DERARING_TEMP_LV02 ) || ( ldcDeratingStat == DERARING_TEMP_LV03 ) )
		{
			if( ( adcRealTemp > TEMP_DRT_LV1_MIN ) && ( adcRealTemp <= TEMP_DRT_LV2_MIN ) )
			{
				if( ( ldcDeratingStat != DERARING_TEMP_LV02 ) && ( ldcDeratingStat != DERARING_TEMP_LV03 ) )
				{
					RTE_SET_DERATING_STAT( DERARING_TEMP_LV01 );
				}
				else
				{
					RTE_SET_DERATING_STAT( ldcDeratingStat );
				}
			}
			else if( ( adcRealTemp > TEMP_DRT_LV2_MIN ) && ( adcRealTemp <= TEMP_DRT_LV3_MIN ) )
			{
				if( ldcDeratingStat != DERARING_TEMP_LV03 )
				{
					RTE_SET_DERATING_STAT( DERARING_TEMP_LV02 );
				}
				else
				{
					RTE_SET_DERATING_STAT( ldcDeratingStat );
				}
			}
			else if( ( adcRealTemp > TEMP_DRT_LV3_MIN ) && ( adcRealTemp <= TEMP_FLT_MIN ) )
			{
				RTE_SET_DERATING_STAT( DERARING_TEMP_LV03 );
			}
			else
			{
				if( adcRealTemp <= TEMP_FLT_TO_NOR_MIN )
				{
					RTE_SET_DERATING_STAT( DERARING_NOT_USE );
					rtnVal = yFALSE; /* move to other mode */
				}
				else
				{
					RTE_SET_DERATING_STAT( ldcDeratingStat );
				}
			}
		}
		else if( ( adcRealInputVolt > IN_VOLT_DRT_TO_NOR_MAX ) || ( adcRealInputVolt < IN_VOLT_DRT_TO_NOR_MIN ) )
		{
			RTE_SET_DERATING_STAT( DERARING_VOLT );
		}
		else
		{
			RTE_SET_DERATING_STAT( DERARING_NOT_USE );
			rtnVal = yFALSE; /* move to other mode */
		}
	}
	else
	{
		RTE_SET_DERATING_STAT( DERARING_NOT_USE );
		rtnVal = yFALSE; /* move to other mode */
	}

	return rtnVal;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static uint8_t IsChangeModeFault( const LdcDiagnosisType* FaultDetectedFlag, LDC_MODE_DEF ldcModeStatus, LDC_RUN_DEF ldcRunStatus, const AdcRealValuesType* adcValues )
{
	uint16_t checkHvCurr = adcValues->realInputCurrent;
	uint16_t checkHvVolt = adcValues->realInputVoltage;
	uint16_t checkLvCurr = adcValues->realOutputCurrent;
	uint16_t checkLvVolt = adcValues->realOutputVoltage;
	int16_t checkTemp = adcValues->realTemperature;
	int16_t checkTempSub = adcValues->realTemperatureSub;
	uint8_t rtnVal = 0;

	if(
#if ( DIAG_TEMP_ON )
			( FaultDetectedFlag->Diag_LdcTemp == yFALSE )
#endif
#if ( DIAG_TEMP_SUB_ON )
   || ( FaultDetectedFlag->Diag_LdcTempSub == yFALSE )
#endif
#if ( DIAG_IN_CURR_ON )
	 || (FaultDetectedFlag->Diag_HV_I == yFALSE)
#endif
#if ( DIAG_IN_VOLT_ON )
	 || ( FaultDetectedFlag->Diag_HV_V == yFALSE )
#endif
#if ( DIAG_OUT_VOLT_ON )
	 || ( FaultDetectedFlag->Diag_LV_V == yFALSE )
#endif
#if ( DIAG_OUT_CURR_ON )
	 || ( FaultDetectedFlag->Diag_LV_I == yFALSE )
#endif
	 || ( FaultDetectedFlag->Diag_dtc_P1107 == yFALSE )
	 || ( FaultDetectedFlag->Diag_dtc_P1109 == yFALSE ) )
	{
		if( ldcModeStatus == LDC_MODE_FAULT )
		{
			rtnVal = yTRUE; /* Stay to mode fault */
		}
		else /* Fault */
		{
			if( ldcRunStatus == LDC_RUN_STANDBY )
			{
				if(
#if ( DIAG_TEMP_ON )
						( u8g_checkTemp_Flag == yTRUE )
#endif
#if ( DIAG_TEMP_SUB_ON )
			 	 || ( checkTempSub > TEMP_FLT_MIN )
#endif
#if ( DIAG_IN_CURR_ON )
				 || ( checkHvCurr >= IN_CURR_FLT_LOW_STB_MAX )
#endif
#if ( DIAG_IN_VOLT_ON )
				 || ( checkHvVolt <= IN_VOLT_FLT_LOW_MAX )
				 || ( checkHvVolt > IN_VOLT_FLT_HIGH_MIN )
#endif
#if ( DIAG_OUT_CURR_ON )
				 || ( checkLvCurr > OUT_CURR_FLT_LOW_MIN )
#endif
#if ( DIAG_OUT_VOLT_ON )
				 || ( checkLvVolt <= OUT_VOLT_FLT_LOW_STB_MIN )
				 || ( checkLvVolt >= OUT_VOLT_FLT_HIGH_STB_MAX )
#endif
				 || ( FaultDetectedFlag->Diag_dtc_P1107 == yFALSE )
				 || ( FaultDetectedFlag->Diag_dtc_P1109 == yFALSE ) )
				{
					rtnVal = yTRUE; /* entry to mode fault */
				}
				else
				{
					rtnVal = yFALSE; /* move to other */
				}
			}
			else /* LDC_RUN_POWERON  */
			{
				if(
#if ( DIAG_TEMP_ON )
						( u8g_checkTemp_Flag == yTRUE )
#endif
#if ( DIAG_TEMP_SUB_ON )
				 || ( checkTempSub >= TEMP_FLT_MIN )
#endif
#if ( DIAG_IN_VOLT_ON )
				 || ( checkHvVolt <= IN_VOLT_FLT_LOW_MAX )
				 || ( checkHvVolt >= IN_VOLT_FLT_HIGH_MIN )
#endif
#if ( DIAG_OUT_CURR_ON )
				 || ( checkLvCurr > OUT_CURR_FLT_LOW_MIN )
#endif
#if ( DIAG_OUT_VOLT_ON )
				 || ( checkLvVolt <= OUT_VOLT_FLT_LOW_PWO_MIN )
				 || ( checkLvVolt >= OUT_VOLT_FLT_HIGH_PWO_MAX )
#endif
#if ( DIAG_IN_CURR_ON )
				 || ( checkHvCurr > IN_CURR_FLT_HIGH_PWO_MIN )
#endif
				 || ( FaultDetectedFlag->Diag_dtc_P1107 == yFALSE )
				 || ( FaultDetectedFlag->Diag_dtc_P1109 == yFALSE ) )
				{
					rtnVal = yTRUE;
				}
				else
				{
					rtnVal = yFALSE;
				}
			}
		}
	}
	else
	{
		rtnVal = yFALSE; /* move to other mode */
	}

	return rtnVal;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static uint8_t IsChangeModeFailure( const LdcDiagnosisType* FaultDetectedFlag, LDC_MODE_DEF ldcModeStatus, const AdcRealValuesType* adcValues )
{
	uint16_t checkHvCurr = adcValues->realInputCurrent;
	uint16_t checkHvVolt = adcValues->realInputVoltage;
	uint16_t checkLvCurr = adcValues->realOutputCurrent;
	uint16_t checkLvVolt = adcValues->realOutputVoltage;
	int16_t checkTemp = adcValues->realTemperature;
	int16_t checkTempSub = adcValues->realTemperatureSub;
	uint8_t rtnVal = 0;

	if(
#if ( DIAG_TEMP_ON )
			( FaultDetectedFlag->Diag_LdcTemp == yFALSE )
#endif
#if ( DIAG_TEMP_SUB_ON )
	 || ( FaultDetectedFlag->Diag_LdcTempSub == yFALSE )
#endif
#if ( DIAG_IN_CURR_ON )
	 || ( FaultDetectedFlag->Diag_HV_I == yFALSE )
#endif
#if ( DIAG_IN_VOLT_ON )
	 || ( FaultDetectedFlag->Diag_HV_V == yFALSE )
#endif
#if ( DIAG_OUT_VOLT_ON )
	 || ( FaultDetectedFlag->Diag_LV_V == yFALSE )
#endif
#if ( DIAG_OUT_CURR_ON )
	 || ( FaultDetectedFlag->Diag_LV_I == yFALSE )
#endif
		)
	{
		if( ldcModeStatus == LDC_MODE_FAILURE )
		{
			rtnVal = yTRUE; /* Stay to mode Failure */
		}
		else
		{
			if(
#if ( DIAG_TEMP_ON )
					( checkTemp == DIAG_TEMP_FAIL_VALUE )
#endif
#if ( DIAG_TEMP_SUB_ON )
			 || ( checkTempSub == DIAG_TEMP_FAIL_VALUE )
#endif
#if ( DIAG_IN_CURR_ON )
			 || ( checkHvCurr == DIAG_FAIL_VALUE )
#endif
#if ( DIAG_IN_VOLT_ON )
			 || ( checkHvVolt == DIAG_FAIL_VALUE )
#endif
#if ( DIAG_OUT_CURR_ON )
			 || ( checkLvCurr == DIAG_FAIL_VALUE )
#endif
#if ( DIAG_OUT_VOLT_ON )
			 || ( checkLvVolt == DIAG_FAIL_VALUE )
#endif
				)
			{
				rtnVal = yTRUE; /* entry to mode Failure */
			}
			else
			{
				rtnVal = yFALSE; /* move to other */
			}
		}
	}
	else
	{
		rtnVal = yFALSE; /* move to other mode */
	}

	return rtnVal;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void ResetModeTimers( void )
{
	ldcFailureTimer = 0U;
	ldcFaultTimer = 0U;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void CurrDeratingMng( LDC_DERATING_STAT deratingStat )
{
	if( deratingStat == DERARING_CURR_LV01 )
	{
		currDeratingLv01Timer++;
		if( ( currDeratingLv01Timer * TASK_PRD_1MS ) >= ( 1U * 1000U ) )
		{
			RTE_SET_DERATING_STAT( DERARING_CURR_LV02 );
			currDeratingLv01Timer = 0U;
		}
	}
	else /* DERARING_CURR_LV02 */
	{
		currDeratingLv02Timer++;
		if( ( currDeratingLv02Timer * TASK_PRD_1MS ) >= ( 5U * 1000U ) )
		{
			RTE_SET_DERATING_STAT( DERARING_NOT_USE );
			currDeratingLv02Timer = 0U;
		}
	}
}

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
