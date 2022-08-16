/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : E100_LDC                                                    **
**  Filename  : u_BSW.c                                                     **
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

#define U_BSW_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "u_BSW.h"
#include "il_inc.h"
#include "Asw_CtrlLdcMode.h"
#include "Asw_DiagAdc.h"
#include "desc.h"

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
#if( POWER_LATCH_ON )
static void BSW_POWER_LATCH_ON( void );
static void BSW_POWER_LATCH_OFF( void );
#endif

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
#if( POWER_LATCH_ON )
void power_latch( void )
{
	uint8_t IlGetSts;
	const ADC_results_t* pAdcData = RTE_GET_ADC_RAW_RESULT();

	IlGetSts = ( uint8_t )IlGetStatus();

	if(( pAdcData->KeyInVoltage >= 1000/*1474*/) || ( RTE_GET_IGN3_STS() == 1 ) )
	{
		if( ( IlGetSts & kIlIsTxRun ) == 0 ){ IlTxRelease(); }

		BSW_POWER_LATCH_ON();
		RTE_CLEAR_POWER_LATCH_COUNTER_VAL(); /* power_latch_count = 0; */
	}
	else
	{
		if( IlIsTxWait( IlGetSts ) == 0 ){ IlTxWait(); }

		RTE_ADD_POWER_LATCH_COUNTER_VAL(); /* power_latch_count++; */

		if( (RTE_GET_POWER_LATCH_COUNTER_VAL() * TASK_PRD_1MS) >= IGN_OFF_TIME ) /* 임시 - 5 sec 이상 유지 시 IGN Off 판단 */
		{
			Eeprom_Write();
			RTE_IGN_OFF();
			BSW_POWER_LATCH_OFF(); /* IGN OFF 후 수행 */
		}
		else
		{
			BSW_POWER_LATCH_ON();
			u16g_StartPwmOn_cnt = 0U;
			u16g_StartSrOn_cnt = 0U;
			ldcFaultCount = 0U;
			ldcFailureCount = 0U;
			u8g_p1109_FaultTime = 0U;
			u8g_p1107_FaultTime = 0U;
		}
	}
}
#endif /* end of POWER_LATCH_ON */

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void BSW_CAN_Il_TASK ( void )
{
	CanTask();
	IlRxTask();
	IlTxTask();
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void BSW_CAN_Diag_TASK ( void )
{
	TpTask();
	DescTask();
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void ApplVCU_CMD_LDC_TARGT_VOLTSigIndication(void){} /* [CS_IGNORE=MISRA_C_2012.MISRA_C_2012_08_02;Can not handle this fucntion. This function is generated automatically by Vector Embedded] */

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void ApplVCU_ReadyRxSigTimeout(void){}/* [CS_IGNORE=MISRA_C_2012.MISRA_C_2012_08_02;Can not handle this fucntion. This function is generated automatically by Vector Embedded] */

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void ApplVCU_CMMFunctionRxSigTimeout(void) {} /* [CS_IGNORE=MISRA_C_2012.MISRA_C_2012_08_02;Can not handle this fucntion. This function is generated automatically by Vector Embedded] */

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void ApplVCU_CMD_LDC_TARGT_VOLTRxSigTimeout(void) {} /* [CS_IGNORE=MISRA_C_2012.MISRA_C_2012_08_02;Can not handle this fucntion. This function is generated automatically by Vector Embedded] */

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void ApplVCU_LDC_HVCurrentLimRxSigTimeout(void){} /* [CS_IGNORE=MISRA_C_2012.MISRA_C_2012_08_02;Can not handle this fucntion. This function is generated automatically by Vector Embedded] */

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
#if ( POWER_LATCH_ON )
static void BSW_POWER_LATCH_ON(void)
{
	SIUL2.GPDO[3].R = 1; /* power latch ON */
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void BSW_POWER_LATCH_OFF(void)
{
	SIUL2.GPDO[3].R = 0; /* power latch OFF */
}
#endif

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
