/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : E100_LDC                                                    **
**  Filename  : Asw_DiagAdc.c                                               **
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

#define ASW_DIAGADC_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "Asw_DiagAdc.h"
#include "Asw_PiController.h"
#include "Asw_Sequence.h"
#include "Asw_CtrlLdcMode.h"

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
static void DiagAdc_DiagTemp( LdcDiagnosisType* pDiagFlags, LDC_MODE_DEF ldcModeStatus, LDC_RUN_DEF ldcRunStatus, int16_t adcRealTemp );
static void DiagAdc_DiagTempSub( LdcDiagnosisType* pDiagFlags, LDC_MODE_DEF ldcModeStatus, LDC_RUN_DEF ldcRunStatus, int16_t adcRealTemp );
static void DiagAdc_DiagInputV( LdcDiagnosisType* pDiagFlags, LDC_MODE_DEF ldcModeStatus, uint16_t adcRealInputV );
static void DiagAdc_DiagInputI( LdcDiagnosisType* pDiagFlags, LDC_MODE_DEF ldcModeStatus, LDC_RUN_DEF ldcRunStat, uint16_t adcRealinputI );
static void DiagAdc_DiagOutputV( LdcDiagnosisType* pDiagFlags, LDC_MODE_DEF ldcModeStatus, LDC_RUN_DEF ldcRunStat, uint16_t adcRealOutputV );
static void DiagAdc_DiagOutputI( LdcDiagnosisType* pDiagFlags, LDC_MODE_DEF ldcModeStatus, LDC_RUN_DEF ldcRunStat, uint16_t adcRealOutputI );
static void DiagAdc_DiagDTC_P1109( LdcDiagnosisType* pDiagFlags, LDC_MODE_DEF ldcModeStatus,LDC_RUN_DEF ldcRunStat, uint16_t adcRealVout_Ref , uint16_t adcRealVout_Fb );
static void DiagAdc_DiagDTC_P1107( LdcDiagnosisType* pDiagFlags, LDC_MODE_DEF ldcModeStatus, uint16_t adcRealVout , uint16_t adcRealBplus );

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
uint32_t u32g_LDC_ERR_Sts = 0U;
uint8_t u8g_Restart_Request = 0U;
uint16_t u16g_p1109Err_Cnt = 0U;
uint8_t u8g_P1109_FaultReadyCnt = 0U;
uint8_t u8g_checkTemp_Flag = 0U;
uint8_t u8g_p1109_FaultTime = 0U;
uint8_t u8g_p1107_FaultTime = 0U;

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void DiagAdc_DiagAdcValues( LdcDiagnosisType* pDiagFlags, LDC_MODE_DEF ldcModeStat, LDC_RUN_DEF ldcRunStat, const AdcRealValuesType* adcValues )
{
	uint16_t vOut = adcValues->realOutputVoltage;
	uint16_t iOut = adcValues->realOutputCurrent;
	uint16_t vIn = adcValues->realInputVoltage;
	uint16_t iIn = adcValues->realInputCurrent;
	int16_t temp = adcValues->realTemperature;
	int16_t tempSub = adcValues->realTemperatureSub;
	uint16_t batteryVolt = adcValues->realBatteryVoltage;

#if ( DIAG_TEMP_ON )
	DiagAdc_DiagTemp( pDiagFlags, ldcModeStat, ldcRunStat, temp ); /* Temperature Diagnosis (-10 ~ 105)*/
#endif

#if ( DIAG_TEMP_SUB_ON )
	DiagAdc_DiagTempSub(pDiagFlags, ldcModeStat, ldcRunStat, tempSub); /* Temperature Diagnosis (-10 ~ 105)*/
#endif

#if ( DIAG_IN_VOLT_ON )
	DiagAdc_DiagInputV(pDiagFlags, ldcModeStat, vIn); /* Input V Diagnosis(250 ~ 420) */
#endif

#if ( DIAG_IN_CURR_ON )
	DiagAdc_DiagInputI(pDiagFlags, ldcModeStat, ldcRunStat, iIn); /* Input I Diagnosis (0~1 or 0~20)*/
#endif

#if ( DIAG_OUT_VOLT_ON )
	DiagAdc_DiagOutputV(pDiagFlags, ldcModeStat, ldcRunStat, vOut); /* Output V Diagnosis */
#endif

#if ( DIAG_OUT_CURR_ON )
	DiagAdc_DiagOutputI(pDiagFlags, ldcModeStat, ldcRunStat, iOut); /* Output I Diagnosis(0~0.5 or 0~128) */
#endif

#if ( DIAG_FAIL_CTRL )
	DiagAdc_DiagDTC_P1109( pDiagFlags, ldcModeStat, ldcRunStat, rteVcuCmdLdcTargetVolt , vOut );
#endif

	DiagAdc_DiagDTC_P1107( pDiagFlags, ldcModeStat, vOut, batteryVolt );

#if ( !DIAG_TEMP_ON )
	pDiagFlags->Diag_LdcTemp = yTRUE;
#endif /* end of DIAG_TEMP_ON */
#if ( !DIAG_TEMP_SUB_ON )
	pDiagFlags->Diag_LdcTempSub = yTRUE;
#endif /* end of DIAG_TEMP_ON */
#if ( !DIAG_IN_VOLT_ON )
	pDiagFlags->Diag_HV_V = yTRUE;
#endif /* end of DIAG_IN_VOLT_ON */
#if ( !DIAG_IN_CURR_ON )
	pDiagFlags->Diag_HV_I = yTRUE;
#endif /* end of */
#if ( !DIAG_OUT_VOLT_ON )
	pDiagFlags->Diag_LV_V = yTRUE;
#endif /* end of DIAG_OUT_VOLT_ON */
#if ( !DIAG_OUT_CURR_ON )
	pDiagFlags->Diag_LV_I = yTRUE;
#endif /* end of DIAG_OUT_CURR_ON */
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
static void DiagAdc_DiagTemp( LdcDiagnosisType* pDiagFlags, LDC_MODE_DEF ldcModeStatus, LDC_RUN_DEF ldcRunStatus, int16_t adcRealTemp )
{
	static uint8_t u8s_TempFaultTime = 0U;
	static uint16_t u16s_TempFaultCnt = 0U;
	static uint8_t u8s_TempFaultReadyCnt = 0U;

	if( ( ldcModeStatus == LDC_MODE_NORMAL ) || ( ldcModeStatus == LDC_MODE_WARNING ) )
	{
		u8g_checkTemp_Flag = 0U;
		u16s_TempFaultCnt = 0U;
		u8s_TempFaultReadyCnt = 1U;
		clrReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1108 ) );

		if( ldcRunStatus == LDC_RUN_STANDBY )
		{
			if( ( TEMP_NOR_MIN <= adcRealTemp ) && ( adcRealTemp <= TEMP_NOR_MAX ) )  /* Mode Normal*/
			{
				pDiagFlags->Diag_LdcTemp = yTRUE; /* no problem */
			}
			else
			{
				pDiagFlags->Diag_LdcTemp = yFALSE; /* exist problem */
			}
		}
		else /* LDC_RUN_POWERON */
		{
			if( ( TEMP_NOR_MIN <= adcRealTemp ) && ( adcRealTemp <= TEMP_NOR_MAX ) )  /* Mode Normal*/
			{
				pDiagFlags->Diag_LdcTemp = yTRUE; /* no problem */
			}
			else
			{
				pDiagFlags->Diag_LdcTemp = yFALSE; /* exist problem */
			}
		}
	}
	else if( ( ldcModeStatus == LDC_MODE_FAULT ) || ( ldcModeStatus == LDC_MODE_DERATING ) )
	{
		if( ( adcRealTemp <= TEMP_FLT_TO_NOR_MIN ) && ( adcRealTemp != DIAG_TEMP_FAIL_VALUE ) ) /* Normal 복귀 조건 95도 미만 */
		{
			pDiagFlags->Diag_LdcTemp = yTRUE; /* no problem */
		}
		else
		{
			pDiagFlags->Diag_LdcTemp = yFALSE; /* exist problem */
		}
	}
	else /* LDC_MODE_FAILURE */
	{
		if( adcRealTemp != DIAG_TEMP_FAIL_VALUE )  /* Normal 복귀 조건 95도 이하 */
		{
			if( adcRealTemp <= TEMP_FLT_TO_NOR_MIN )
			{
				pDiagFlags->Diag_LdcTemp = yTRUE; /* no problem */
			}
			else
			{
				pDiagFlags->Diag_LdcTemp = yFALSE; /* exist problem */
			}
		}
		else
		{
			pDiagFlags->Diag_LdcTemp = yFALSE; /* exist problem */
		}
	}

	if( u8s_TempFaultTime >= 3U )	/* 3 times */
	{
		pDiagFlags->Diag_LdcTemp = yFALSE; /* exist problem */
		u8g_checkTemp_Flag = yTRUE;
		setReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1108 ) );
	}
	else
	{
		if( adcRealTemp >= TEMP_FLT_MIN )
		{
			if( u16s_TempFaultCnt > 5000U )
			{
				u8g_checkTemp_Flag = yTRUE;
				setReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1108 ) );

				if( u8s_TempFaultReadyCnt == 1U )
				{
					u8s_TempFaultTime++;
					u8s_TempFaultReadyCnt = 0U;
				}
			}
			else
			{
				u16s_TempFaultCnt++;
			}
		}
	}
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void DiagAdc_DiagTempSub( LdcDiagnosisType* pDiagFlags, LDC_MODE_DEF ldcModeStatus, LDC_RUN_DEF ldcRunStatus, int16_t adcRealTemp )
{
	if( ( ldcModeStatus == LDC_MODE_NORMAL ) || ( ldcModeStatus == LDC_MODE_WARNING ) )
	{
		if( ldcRunStatus == LDC_RUN_STANDBY )
		{
			if( ( TEMP_NOR_MIN <= adcRealTemp ) && ( adcRealTemp <= TEMP_NOR_MAX ) )  /* Mode Normal*/
			{
				pDiagFlags->Diag_LdcTempSub = yTRUE; /* no problem */
			}
			else
			{
				pDiagFlags->Diag_LdcTempSub = yFALSE; /* exist problem */
			}
		}
		else /* LDC_RUN_POWERON */
		{
			if( ( TEMP_NOR_MIN <= adcRealTemp ) && ( adcRealTemp <= TEMP_NOR_MAX ) )  /* Mode Normal*/
			{
				pDiagFlags->Diag_LdcTempSub = yTRUE; /* no problem */
			}
			else
			{
				pDiagFlags->Diag_LdcTempSub = yFALSE; /* exist problem */
			}
		}
	}
	else if( ( ldcModeStatus == LDC_MODE_FAULT ) || ( ldcModeStatus == LDC_MODE_DERATING ) )
	{
		if( ( adcRealTemp <= TEMP_FLT_TO_NOR_MIN ) && ( adcRealTemp != DIAG_TEMP_FAIL_VALUE ) ) /* Normal 복귀 조건 95도 미만 */
		{
			pDiagFlags->Diag_LdcTempSub = yTRUE; /* no problem */
		}
		else
		{
			pDiagFlags->Diag_LdcTempSub = yFALSE; /* exist problem */
		}
	}
	else /* LDC_MODE_FAILURE */
	{
		if( adcRealTemp != DIAG_TEMP_FAIL_VALUE )  /* Normal 복귀 조건 95도 이하 */
		{
			if( adcRealTemp <= TEMP_FLT_TO_NOR_MIN )
			{
				pDiagFlags->Diag_LdcTempSub = yTRUE; /* no problem */
			}
			else
			{
				pDiagFlags->Diag_LdcTempSub = yFALSE; /* exist problem */
			}
		}
		else
		{
			pDiagFlags->Diag_LdcTempSub = yFALSE; /* exist problem */
		}
	}
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void DiagAdc_DiagInputV( LdcDiagnosisType* pDiagFlags, LDC_MODE_DEF ldcModeStatus, uint16_t adcRealInputV )
{
	if( ( ldcModeStatus == LDC_MODE_NORMAL ) || ( ldcModeStatus == LDC_MODE_WARNING ) )
	{
		if( ( IN_VOLT_NOR_MIN <= adcRealInputV ) && ( adcRealInputV <= IN_VOLT_NOR_MAX ) )  /* Mode Normal - 250 ~ 420 */
		{
			pDiagFlags->Diag_HV_V = yTRUE; /* no problem */
		}
		else
		{
			pDiagFlags->Diag_HV_V = yFALSE; /* exist problem */
		}
	}
	else if( ( ldcModeStatus == LDC_MODE_FAULT ) )
	{
		if( ( IN_VOLT_FLT_TO_NOR_MIN <= adcRealInputV ) && ( adcRealInputV <= IN_VOLT_FLT_TO_NOR_MAX ) ) /* Mode Normal - 270 ~ 415 */
		{
			pDiagFlags->Diag_HV_V = yTRUE; /* no problem */
		}
		else
		{
			pDiagFlags->Diag_HV_V = yFALSE; /* exist problem */
		}
	}
	else if( (ldcModeStatus == LDC_MODE_DERATING) )
	{
		if( ( IN_VOLT_DRT_TO_NOR_MIN <= adcRealInputV ) && ( adcRealInputV <= IN_VOLT_DRT_TO_NOR_MAX ) ) /* Mode Normal - 270 ~ 415 */
		{
			pDiagFlags->Diag_HV_V = yTRUE; /* no problem */
		}
		else
		{
			pDiagFlags->Diag_HV_V = yFALSE; /* exist problem */
		}
	}
	else /* LDC_MODE_FAILURE */
	{
		if( adcRealInputV != DIAG_FAIL_VALUE )/* Mode Normal - 270 ~ 415 */
		{
			if( ( IN_VOLT_NOR_MIN <= adcRealInputV ) && ( adcRealInputV <= IN_VOLT_NOR_MAX ) )
			{
				pDiagFlags->Diag_HV_V = yTRUE; /* no problem */
			}
			else
			{
				pDiagFlags->Diag_HV_V = yFALSE; /* exist problem */
			}
		}
		else
		{
			pDiagFlags->Diag_HV_V = yFALSE; /* exist problem */
		}
	}
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void DiagAdc_DiagInputI( LdcDiagnosisType* pDiagFlags, LDC_MODE_DEF ldcModeStatus, LDC_RUN_DEF ldcRunStat, uint16_t adcRealinputI )
{
	static uint8_t u8s_IinFaultTime = 0U;
	static uint8_t u8s_IinFault_ReadyCnt = 0U;

	if( ( ldcModeStatus == LDC_MODE_NORMAL ) || ( ldcModeStatus == LDC_MODE_WARNING ) || ( ldcModeStatus == LDC_MODE_DERATING ) )
	{
		if( ldcRunStat == LDC_RUN_STANDBY )
		{
			if( adcRealinputI <= IN_CURR_NOR_STB_MAX )
			{
				pDiagFlags->Diag_HV_I = yTRUE; /* no problem */
				u8s_IinFault_ReadyCnt = 1U;
				clrReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1103 ) );
			}
			else
			{
				pDiagFlags->Diag_HV_I = yFALSE; /* exist problem */
			}
		}
		else /* ldcRunStat == LDC_RUN_POWERON */
		{
			if( adcRealinputI <= IN_CURR_NOR_PWO_MAX )
			{
				pDiagFlags->Diag_HV_I = yTRUE; /* no problem */
				clrReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1103 ) );
				u8s_IinFault_ReadyCnt = 1U;
			}
			else
			{
				pDiagFlags->Diag_HV_I = yFALSE; /* exist problem */
				setReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1103 ) );
				if( u8s_IinFault_ReadyCnt == 1U )
				{
					u8s_IinFaultTime++;
					u8s_IinFault_ReadyCnt = 0;
				}
			}
		}
	}
	else if( ldcModeStatus == LDC_MODE_FAULT )
	{
		if( u8s_IinFaultTime >= 3U )
		{
			setReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1103 ) );
		}

		if( ldcRunStat == LDC_RUN_STANDBY )
		{
			if( adcRealinputI < IN_CURR_FLT_TO_NOR_STB_MAX )
			{
				pDiagFlags->Diag_HV_I = yTRUE; /* no problem */
			}
			else
			{
				pDiagFlags->Diag_HV_I = yFALSE; /* exist problem */
			}
		}
		else /* ldcRunStat == LDC_RUN_POWERON */
		{
			if( adcRealinputI <= IN_CURR_FLT_TO_NOR_PWO_MAX ) /* fault 모드 내 8A 이하 유지 시 */
			{
				pDiagFlags->Diag_HV_I = yTRUE; /* no problem */
			}
			else
			{
				pDiagFlags->Diag_HV_I = yFALSE; /* exist problem */
			}
		}
	}
	else /* LDC_MODE_FAILURE */
	{
		if( ldcRunStat == LDC_RUN_STANDBY )
		{
			if( ( adcRealinputI != DIAG_FAIL_VALUE ) && ( adcRealinputI < IN_CURR_FLT_TO_NOR_STB_MAX ) )
			{
				pDiagFlags->Diag_HV_I = yTRUE; /* no problem */
			}
			else
			{
				pDiagFlags->Diag_HV_I = yFALSE; /* exist problem */
			}
		}
		else /* ldcRunStat == LDC_RUN_POWERON */
		{
			if( ( adcRealinputI != DIAG_FAIL_VALUE) && (adcRealinputI <= IN_CURR_FLT_TO_NOR_PWO_MAX) ) /* failure 모드 내 8A 이하 유지 시 */
			{
				pDiagFlags->Diag_HV_I = yTRUE; /* no problem */
			}
			else
			{
				pDiagFlags->Diag_HV_I = yFALSE; /* exist problem */
			}
		}
	}
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void DiagAdc_DiagOutputV( LdcDiagnosisType* pDiagFlags, LDC_MODE_DEF ldcModeStatus, LDC_RUN_DEF ldcRunStat, uint16_t adcRealOutputV )
{
	static uint8_t u8s_VoutFaultTime = 0U;
	static uint8_t u8s_VoutReadyCnt = 0U;

	if( ( ldcModeStatus == LDC_MODE_NORMAL ) || ( ldcModeStatus == LDC_MODE_WARNING ) || (ldcModeStatus == LDC_MODE_DERATING ) )
	{
		u8s_VoutReadyCnt = 1U;

		if( ldcRunStat == LDC_RUN_STANDBY )
		{
			if( ( OUT_VOLT_NOR_STB_MIN <= adcRealOutputV ) && ( adcRealOutputV <= OUT_VOLT_NOR_STB_MAX ) )
			{
				pDiagFlags->Diag_LV_V = yTRUE; /* no problem */
			}
			else
			{
				pDiagFlags->Diag_LV_V = yFALSE; /* exist problem */
			}
		}
		else /* LDC_RUN_POWERON */
		{
			if( ( OUT_VOLT_NOR_PWO_MIN <= adcRealOutputV ) && ( adcRealOutputV <= OUT_VOLT_NOR_PWO_MAX ) )
			{
				pDiagFlags->Diag_LV_V = yTRUE; /* no problem */
				clrReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1102 ) );
			}
			else if( ( OUT_VOLT_NOR_PWO_MAX <= adcRealOutputV ) && ( adcRealOutputV <= OUT_VOLT_NOR_PWO_MAX_SHUT_DOWN ) )
			{
				pDiagFlags->Diag_LV_V = yFALSE; /* exist problem */
			}
			else
			{
				setReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1102 ) );
				pDiagFlags->Diag_LV_V = yFALSE; /* exist problem */
			}
		}
	}
	else if( ldcModeStatus == LDC_MODE_FAULT )
	{
		if( u8s_VoutFaultTime >= 3U )
		{
			setReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1102 ) );
		}
		else
		{
			if( adcRealOutputV >= OUT_VOLT_NOR_PWO_MAX_SHUT_DOWN )
			{
				if( u8s_VoutReadyCnt == 1U)
				{
					setReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1102 ) );
					u8s_VoutFaultTime++;
					u8s_VoutReadyCnt = 0U;
				}
			}
		}

		if( ( OUT_VOLT_FLT_TO_NOR_MIN <= adcRealOutputV ) && ( adcRealOutputV <= OUT_VOLT_FLT_TO_NOR_MAX ) )
		{
			pDiagFlags->Diag_LV_V = yTRUE; /* no problem */
		}
		else
		{
			pDiagFlags->Diag_LV_V = yFALSE; /* exist problem */
		}
	}
	else /* LDC_MODE_FAILURE */
	{
		if( adcRealOutputV != DIAG_FAIL_VALUE )
		{
			if( ( OUT_VOLT_FLT_TO_NOR_MIN <= adcRealOutputV ) && ( adcRealOutputV <= OUT_VOLT_FLT_TO_NOR_MAX ) )
			{
				pDiagFlags->Diag_LV_V = yTRUE; /* no problem */
			}
			else
			{
				pDiagFlags->Diag_LV_V = yFALSE; /* exist problem */
			}
		}
		else
		{
			pDiagFlags->Diag_LV_V = yFALSE; /* exist problem */
		}
	}
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void DiagAdc_DiagOutputI( LdcDiagnosisType* pDiagFlags, LDC_MODE_DEF ldcModeStatus, LDC_RUN_DEF ldcRunStat, uint16_t adcRealOutputI )
{
	if( ( ldcModeStatus == LDC_MODE_NORMAL ) || ( ldcModeStatus == LDC_MODE_WARNING ) )
	{
		if( ldcRunStat == LDC_RUN_STANDBY )
		{
			if( adcRealOutputI <= OUT_CURR_NOR_STB_MAX )
			{
				pDiagFlags->Diag_LV_I = yTRUE; /* no problem */
			}
			else
			{
				pDiagFlags->Diag_LV_I = yFALSE; /* exist problem */
			}
		}
		else /* ldcRunStat == LDC_RUN_POWERON */
		{
			if( adcRealOutputI <= OUT_CURR_NOR_PWO_MAX )
			{
				pDiagFlags->Diag_LV_I = yTRUE; /* no problem */
			}
			else
			{
				pDiagFlags->Diag_LV_I = yFALSE; /* exist problem */
			}
		}
	}
	else if( ( ldcModeStatus == LDC_MODE_DERATING ) || ( ldcModeStatus == LDC_MODE_FAULT ) )
	{
		if( adcRealOutputI <= OUT_CURR_FLT_TO_NOR_MAX )
		{
			pDiagFlags->Diag_LV_I = yTRUE; /* no problem */
		}
		else
		{
			pDiagFlags->Diag_LV_I = yFALSE; /* exist problem */
		}
	}
	else /* mode faiure */
	{
		if( adcRealOutputI != DIAG_FAIL_VALUE )
		{
			if( adcRealOutputI <= OUT_CURR_FLT_TO_NOR_MAX )
			{
				pDiagFlags->Diag_LV_I = yTRUE; /* no problem */
			}
			else
			{
				pDiagFlags->Diag_LV_I = yFALSE; /* exist problem */
			}
		}
		else
		{
			pDiagFlags->Diag_LV_I = yFALSE; /* exist problem */
		}
	}
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void DiagAdc_DiagDTC_P1109( LdcDiagnosisType* pDiagFlags, LDC_MODE_DEF ldcModeStatus, LDC_RUN_DEF ldcRunStat, uint16_t adcRealVout_Ref , uint16_t adcRealVout_Fb )
{
	int32_t s32_VoutErr = 0;

	s32_VoutErr = ( ( int32_t )adcRealVout_Ref - ( int32_t )adcRealVout_Fb );

	if( u8g_p1109_FaultTime >= 3U ) /* 3 times */
	{
		pDiagFlags->Diag_dtc_P1109 = yFALSE;
		setReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1109 ) );
	}
	else
	{
		if( ( ldcModeStatus == LDC_MODE_NORMAL )
		 || ( ldcModeStatus == LDC_MODE_DERATING )
		 || ( ldcModeStatus == LDC_MODE_WARNING ) )
		{
			if( ( ldcRunStat == LDC_RUN_POWERON ) && ( u8g_softstart_end == 1U ) )
			{
				if( ( s32_VoutErr < -10 ) || ( s32_VoutErr > 10 ) ) /* ( Vref - Vout )>< 1V */
				{
					if( u16g_p1109Err_Cnt >= OUTPUT_FAIL_ERR_ERR_CNT ){
						setReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1109 ) );
						u8g_Restart_Request = 1U;
						if( u8g_P1109_FaultReadyCnt == 1U )
						{
							u8g_p1109_FaultTime++;
							u8g_P1109_FaultReadyCnt = 0U;
						}
					}
					else
					{
						u16g_p1109Err_Cnt++;
					}
				}
				else
				{
					u16g_p1109Err_Cnt = 0U;
					clrReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1109 ) );
				}
			}
		}

		pDiagFlags->Diag_dtc_P1109 = yTRUE;
	}
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void DiagAdc_DiagDTC_P1107( LdcDiagnosisType* pDiagFlags, LDC_MODE_DEF ldcModeStatus, uint16_t adcRealVout , uint16_t adcRealBplus )
{
	static uint16_t u16s_p1107_FaultCnt = 0U ;
	static uint8_t u8s_p1107_ReadyCnt = 0U;
	int32_t s16_Delta = 0;

	s16_Delta = ( ( int32_t )adcRealVout - ( int32_t )adcRealBplus );

	if( u8g_p1107_FaultTime >= 3U ) /* 3 times*/
	{
		setReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1107 ) );
		pDiagFlags->Diag_dtc_P1107 = yFALSE;
	}
	else
	{
		if( ( s16_Delta >= 80 ) || ( s16_Delta <= -80 ) )  /* ( Vout - VBplus ) >< 8V */
		{
			if( u16s_p1107_FaultCnt >= SENSOR_ERR_CNT )
			{
				pDiagFlags->Diag_dtc_P1107 = yFALSE;
				setReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1107 ) );
				if( u8s_p1107_ReadyCnt == 1U )
				{
					u8g_p1107_FaultTime++;
					u8s_p1107_ReadyCnt = 0U;
				}
			}
			else
			{
				u16s_p1107_FaultCnt++;
			}
		}
		else
		{
			pDiagFlags->Diag_dtc_P1107 = yTRUE;
			clrReg32Bits( ( u32g_LDC_ERR_Sts ), ( DTC_P1107 ) );
			u16s_p1107_FaultCnt = 0U;
			u8s_p1107_ReadyCnt = 1U;
		}
	}
}

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
