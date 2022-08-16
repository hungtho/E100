/*
                             *******************
******************************* C HEADER FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : E100_LDC                                                    **
**  Filename  : Rte_LdcConfig.h                                             **
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

#ifndef RTE_LDCCONFIG_INCLUDED
#define RTE_LDCCONFIG_INCLUDED

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "components.h"
#include "Rte_Typedef.h"
#include "Rte_Variable.h"
#include "Rte_Utils.h"
#include "Rte_Cal.h"
#include "spc570_hal_pit.h"
#include "GpFunc.h"

/****************************************************************************/
/**                                                                        **/
/**                      DEFINITIONS AND MACROS                            **/
/**                                                                        **/
/****************************************************************************/
/* Testing */
#define LDC_TEST_VALUES   	( 0U )
#define OPEN_LOOP_IN_USE		( 0U )

/* Functions */
#define LDC_READY_CHECK		( 1U )
#define POWER_LATCH_ON 		( 1U )

/* Protection */
#define FAILURE_IN_USE		( 1U )
#define FAULT_IN_USE 			( 1U )
#define DERATING_IN_USE 	( 1U )

#define DIAG_TEMP_ON				( 1U ) /* Do not turn off this!! it causes compile error */
#define DIAG_TEMP_SUB_ON		( 1U )
#define DIAG_OUT_VOLT_ON 		( 1U )
#define DIAG_OUT_CURR_ON 		( 1U )
#define DIAG_IN_VOLT_ON 		( 1U )
#define DIAG_IN_CURR_ON 		( 1U )
#define DIAG_SENSOR					( 1U )
#define DIAG_FAIL_CTRL			( 1U )
#define DIAG_CURR_PEAK_ON 	( 1U )

#define SW_VER_HIGH		( '0' )
#define SW_VER_LOW	 	( '6' )

#define CMX_VER		( 0x0110U )

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

# ifndef RTE_LDCCONFIG_C_SRC
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
