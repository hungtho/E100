/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : E100_LDC                                                    **
**  Filename  : u_ASW.c                                                     **
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

#define U_ASW_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "u_ASW.h"
#include "Asw_CtrlLdcMode.h"
#include "Asw_Sequence.h"
#include "Asw_PiController.h"
#include "Asw_DiagAdc.h"
#include "Asw_DiagCan.h"
#include "Asw_DiagMcu.h"
#include "flexcan_BSW.h"

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
/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void ASW_LDC_INIT(void)
{
	PiCtrl_PIController_Init();

	/* Read EEPROM Execution time : 55us */
	FindCurrentAdd();
	DTC_Eeprom_Read ( present_addr );
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
uint8_t ASW_LDC_READY_CHECK( void )
{
	static uint16_t u16s_CheckDiag_Cnt = 0U;
	LdcDiagnosisType ldcDiagFlags = { 0, };
	AdcRealValuesType* ldcAdcRealValues = RTE_GET_ADC_REAL_RESULT();
	uint8_t rtnVal = yFALSE;

	LDC_MODE_DEF ldcModeStatus = LDC_MODE_NORMAL; /* LDC ���� �� Normal ���� ���� Ȯ���� ���� ���� */
	LDC_RUN_DEF ldcRunStatus = LDC_RUN_STANDBY; /* ��� �� ���� Ȯ���� ���� ���� */

	DiagAdc_DiagAdcValues( &ldcDiagFlags, ldcModeStatus, ldcRunStatus, ldcAdcRealValues ); /* ADC ���� */
	DiagMcu_DiagMcuStatus( &ldcDiagFlags );
	DiagCan_DiagCanValues( &ldcDiagFlags ); /* CAN ����*/

	RTE_SET_LDC_DIAGNOSIS_STATUS( &ldcDiagFlags );

	if( ( ldcDiagFlags.Diag_LV_V == yTRUE )
	 && ( ldcDiagFlags.Diag_LdcTemp == yTRUE )
	 && ( ldcDiagFlags.Diag_LV_PeakCurr == yTRUE )
	 && ( ldcDiagFlags.Diag_CanBusOffSts == yTRUE ) )
	{
		if( u16s_CheckDiag_Cnt > 500U ){ rtnVal = yTRUE; }
		else{ u16s_CheckDiag_Cnt++; }
	}
	else
	{
		u16s_CheckDiag_Cnt = 0U;
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
void ASW_PI_CTRL_INIT( void )
{
	PiCtrl_PIController_Init();
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void ASW_TASK_1MS(void)
{
	LdcDiagnosisType ldcDiagFlags = { 0, };
	LDC_MODE_DEF ldcModeStatus = RTE_GET_LDC_MODE_STATUS();
	AdcRealValuesType* ldcAdcRealValues = RTE_GET_ADC_REAL_RESULT();
	LDC_RUN_DEF ldcRunStatus = RTE_GET_LDC_RUN_STATUS();
	uint8_t cmdLdcEnable = RTE_GET_CMD_ENABLE_LDC();

	DiagAdc_DiagAdcValues( &ldcDiagFlags, ldcModeStatus, ldcRunStatus, ldcAdcRealValues ); /* LDC mode �� Normal ���� ADC ���� */
	DiagMcu_DiagMcuStatus( &ldcDiagFlags );
	DiagCan_DiagCanValues( &ldcDiagFlags ); /* CAN ����*/

	RTE_SET_LDC_DIAGNOSIS_STATUS( &ldcDiagFlags ); /*1ms task ���ܰ�� ������Ʈ */

	if( u8_DtcControl == DTC_ENABLE ){ DTC_Eeprom_Update(); }
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void ASW_TASK_Operation( void )
{
	const LdcDiagnosisType* pDetectedResult = RTE_GET_LDC_DIAGNOSIS_STATUS();
	const AdcRealValuesType* ldcAdcRealValues = RTE_GET_ADC_REAL_RESULT();
	LdcDiagnosisType diagnosisResult = { 0, };

	utils_memcpy( &diagnosisResult, pDetectedResult, ( uint32_t)sizeof( LdcDiagnosisType ) );

	CtrlLdcMode_UpdateLdcMode( &diagnosisResult, ldcAdcRealValues );
	Seq_OperateLdc();	/* LDC Sequence control by LDC mode */
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void ASW_TASK_100MS( void )
{
	if( u8g_CAN_WaitTx == 0U )
	{
		RTE_UPDATE_CAN_TX();
	}
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
