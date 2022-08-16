
/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : E100                                                        **
**  Filename  : main.c                                                      **
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
/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "../RTE/Rte_AswBswLink.h"
#include "v_inc.h"
#include "il_inc.h"
#include "desc.h"
#include "applfbl.h"

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
#pragma ghs section rodata=".APPLHEADER"
static const tApplInfoHeader V_MEMROM2 ApplInfoHeader =
{
    {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}   /* DID F187h, 10bytes ASCII: SYMC Part NUmber */
   ,{'9', '9' }                                          /* DID F189h, 2bytes ASCII: SYMC Software Version */
   ,{'0', '1', '2', '3', '4'}                            /* DID F18Ah, 5bytes ASCII: System Supplier Code */
   ,{0x00u, 0x00u, 0x01u}                                /* Supplier software version */
   ,kApplNumberHwCompatibilityEntries                    /* Number of compative harware versions */
   ,{0x00u, 0x11u, 0x00u, 0x12u, 0x00, 0x13u}            /* Compatible hardware versions (3 * 2 bytes) */
};
#pragma ghs section rodata=default

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
int main( void )
{
	static volatile uint8_t sw_ver;
	uint8_t checkBreak = 0U;

	irqIsrDisable();

	sw_ver = ApplInfoHeader.kApplSupplierSoftwareVersion[ 2 ];

	RTE_BSW_Init();

	RTE_ASW_Init();

	CRC8_Init ();

	irqIsrEnable();

	pal_clearpad ( PORT_A, INH_PIN ); /* Enable Watchdog */

	IlTxStart();
	IlRxStart();

#if ( LDC_READY_CHECK )
	do
	{
		while( u8g_task_flag_1m != 1U ){}
		u8g_task_flag_1m = FALSE;

		pal_setpad ( PORT_A, WTD_PWM ); /* set Watchdog */
		if( RTE_TASK_LDC_READY_CHECK() == yTRUE ){ checkBreak = yTRUE; }
		pal_clearpad ( PORT_A, WTD_PWM ); /* clear Watchdog */

# if ( POWER_LATCH_ON )
		RTE_CHECK_POWER_LATCH(); /* checking IGN OFF is in processing */
# endif

		/* -------------------------------------------------------------------*/
		/*   Time Task Management for TT1: 10ms																*/
		/* -------------------------------------------------------------------*/
		if( --u8g_task_10m_cnt == 0U )
		{
			u8g_task_10m_cnt = 10U;
			RTE_TASK_10ms(); /* Execution periodic time task TT1 */
		}

		/* -------------------------------------------------------------------*/
		/*   Time Task Management for TT1: 100ms															*/
		/* -------------------------------------------------------------------*/
		if( --u8g_task_100m_cnt == 0U )
		{
			u8g_task_100m_cnt = 100U;
			RTE_TASK_100ms(); /* Execution periodic time task TT2 */
		}

		/* -------------------------------------------------------------------*/
		/*   Time Task Management for TT1: 100ms															*/
		/* -------------------------------------------------------------------*/
		if( --u16g_task_7s_cnt == 0U )
		{
			u16g_task_7s_cnt = 7000U;
			checkBreak = yTRUE;
		}
	}while( checkBreak == yFALSE );
#endif

	while(1)
	{
		/* Execution periodic time task: 1ms */
		while( u8g_task_flag_1m != 1U ){}
		u8g_task_flag_1m = FALSE;

		/* -------------------------------------------------------------------*/
		/*   Time Task Management for TT0: 1ms															  */
		/*   Execution time: 635us																						*/
		/* -------------------------------------------------------------------*/
#if ( POWER_LATCH_ON )
		RTE_CHECK_POWER_LATCH(); /*  checking IGN OFF is in processing */
#endif

		RTE_TASK_1ms();
		if( u8g_ReqReset!= 1U ){ pal_togglepad ( PORT_A, WTD_PWM );	}

		/* -------------------------------------------------------------------*/
		/*   Time Task Management for TT1: 10ms																*/
		/*   Execution time: 145us																						*/
		/* -------------------------------------------------------------------*/
		if( --u8g_task_10m_cnt == 0U )
		{
			u8g_task_10m_cnt = 10U;
			RTE_TASK_10ms(); /* Execution periodic time task TT1 */
		}

		/* -------------------------------------------------------------------*/
		/*   Time Task Management for TT1: 100ms															*/
		/*   Execution time: 100us																						*/
		/* -------------------------------------------------------------------*/
		if( --u8g_task_100m_cnt == 0U )
		{
			u8g_task_100m_cnt = 100U;
			RTE_TASK_100ms(); /* Execution periodic time task TT2 */
		}
	}
	/* return 0; */ /* [CS_IGNORE=MISRA_C_2012.MISRA_C_2012_02_01;IGN OFF 확정 시 상위 반복문 종료 후 수행 예정 ] */
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
