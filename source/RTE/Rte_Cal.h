/*
                             *******************
******************************* C HEADER FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : E100_LDC                                                    **
**  Filename  : Rte_Cal.h                                                   **
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

#ifndef RTE_CAL_INCLUDED
#define RTE_CAL_INCLUDED

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                      DEFINITIONS AND MACROS                            **/
/**                                                                        **/
/****************************************************************************/
#define TASK_PRD_1MS 							( 1U )
#define TASK_PRD_10MS 						( 10U )
#define TASK_PRD_100MS 						( 100U )

#define DIAG_FAULT_VALUE 					( 0U )
#define DIAG_FAIL_VALUE 					( 65535U )
#define DIAG_TEMP_FAIL_VALUE			( 32767 )

#define MODE_FAILURE_MAX 					( 3U )
#define MODE_FAULT_MAX 						( 3U )

#define PWR_LATCH_PERIOD 					( 0U )
#define MODE_ENTRY_TIME 					( 20U )

#define IGN_OFF_TIME   						( 5U * 1000U ) /* 5 sec  */
#define DERATING_REF_VOLT   			( 120U ) /* 12V */

#define CMD_TARGET_VOLT_MAX   		( 160U )

#define ADC_FAILURE_IOUT   				( 335U )
#define ADC_FAILURE_VOUT   				( 0U )
#define ADC_FAILURE_VIN   				( 30U )
#define ADC_FAILURE_IIN   				( 335U )
#define ADC_FAILURE_TEMP_OPEN   	( 4050U )
#define ADC_FAILURE_TEMP_SHORT   	( 10U )

#define TEMP_NOR_MIN   						( -40 )
#define TEMP_NOR_MAX   						( 110 )
#define TEMP_DRT_LV1_MIN   				( 110 )	/* DERATING LEVEL 1 ENTRY CONDITION*/
#define TEMP_DRT_LV2_MIN   				( 115 ) 	/* DERATING LEVEL 2 ENTRY CONDITION*/
#define TEMP_DRT_LV3_MIN   				( 118 ) 	/* DERATING LEVEL 3 ENTRY CONDITION*/

#define TEMP_FLT_MIN   						( 120 )
#define TEMP_FLT_TO_NOR_MIN   		( 95 )

#define IN_VOLT_NOR_MIN   				( 2500U )
#define IN_VOLT_NOR_MAX   				( 4200U )
#define IN_VOLT_FLT_TO_NOR_MIN  	( 2700U )
#define IN_VOLT_FLT_TO_NOR_MAX   	( 4200U )
#define IN_VOLT_DRT_TO_NOR_MIN   	( 2700U )
#define IN_VOLT_DRT_TO_NOR_MAX   	( 4150U )

#define IN_VOLT_FLT_LOW_MAX   		( 2300U )
#define IN_VOLT_FLT_HIGH_MIN   		( 4300U )

#define IN_CURR_NOR_STB_MIN   		( 0U )
#define IN_CURR_NOR_STB_MAX   		( 10U )
#define IN_CURR_NOR_PWO_MIN   		( 0U )
#define IN_CURR_NOR_PWO_MAX   		( 100U )
#define IN_CURR_FLT_TO_NOR_STB_MAX   ( 20U )
#define IN_CURR_FLT_TO_NOR_PWO_MAX   ( 80U )
#define IN_CURR_FLT_LOW_STB_MAX   	 ( 20U )
#define IN_CURR_FLT_HIGH_PWO_MIN   	 ( 100U )

#define OUT_VOLT_NOR_STB_MIN   		( 90U )
#define OUT_VOLT_NOR_STB_MAX   		( 160U )
#define OUT_VOLT_NOR_PWO_MIN   		( 100U )
#define OUT_VOLT_NOR_PWO_MAX   		( 160U )
#define OUT_VOLT_FLT_TO_NOR_MIN   ( 100U )
#define OUT_VOLT_FLT_TO_NOR_MAX   ( 150U )
#define OUT_VOLT_NOR_PWO_MAX_SHUT_DOWN   ( 220U )

#define OUT_VOLT_FLT_LOW_STB_MIN  ( 65U )
#define OUT_VOLT_FLT_HIGH_STB_MAX   ( 180U )
#define OUT_VOLT_FLT_LOW_PWO_MIN    ( 90U )
#define OUT_VOLT_FLT_HIGH_PWO_MAX   ( 180U )

#define OUT_CURR_NOR_STB_MIN   		( 0U )
#define OUT_CURR_NOR_STB_MAX   		( 5U )
#define OUT_CURR_NOR_PWO_MIN   		( 0U )
#define OUT_CURR_NOR_PWO_MAX   		( 1280U )
#define OUT_CURR_WAR_PWO_MAX   		( 1600U )
#define OUT_CURR_FLT_TO_NOR_MIN   ( 0U )
#define OUT_CURR_FLT_TO_NOR_MAX   ( 1100U )
#define OUT_CURR_FLT_LOW_MIN   		( 1600U )

/****************************************************************************/
/**                                                                        **/
/**                      TYPEDEFS AND STRUCTURES                           **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/

# ifndef RTE_CAL_C_SRC
# endif

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/

#endif

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
