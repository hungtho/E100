/*
                             *******************
******************************* C HEADER FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : E100_LDC                                                    **
**  Filename  : Rte_AswBswLink  .h                                          **
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

#ifndef RTE_ASWBSWLINK_INCLUDED
#define RTE_ASWBSWLINK_INCLUDED

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "Rte_LdcConfig.h"
#include "Asw_EEPROM.h"

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
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/

# ifndef RTE_ASWBSWLINK_C_SRC
# endif

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
extern void RTE_TASK_1ms( void );
extern void RTE_TASK_10ms( void );
extern void RTE_TASK_100ms( void );
extern uint8_t RTE_TASK_LDC_READY_CHECK( void );
extern void RTE_ASW_Init( void );
extern void RTE_ASW_PI_CTRL_Init( void );
extern void RTE_IGN_OFF( void );
extern void RTE_BSW_Init( void );
extern void RTE_PSFB_SET_SR_OUTPUT_Ctrl( void );
extern void RTE_CHECK_POWER_LATCH( void );
extern void RTE_PSFB_OUTPUT_ENABLE( void );
extern void RTE_PSFB_OUTPUT_DISABLE( void );
extern void RTE_PSFB_OUTPUT_SR_DISABLE( void );
extern uint8_t RTE_PEAK_CURR_ERR_STATUS( void );

#endif

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
