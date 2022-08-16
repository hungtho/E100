/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : E100_LDC                                                    **
**  Filename  : Asw_PiController.h                                          **
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

#ifndef ASW_PICONTROLLER_INCLUDED
#define ASW_PICONTROLLER_INCLUDED

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "../RTE/Rte_AswBswLink.h"
#include "Rte_typedef.h"

/****************************************************************************/
/**                                                                        **/
/**                      DEFINITIONS AND MACROS                            **/
/**                                                                        **/
/****************************************************************************/
#define KpVoltage     _IQ13( 0.451 ) 	/* PI controller proportional gain */
#define KiVoltage     _IQ13( 0.00303 ) 	/* PI controller integral gain */
#define KdVoltage			_IQ13( 0.8 ) 		/* PI controller derivative gain */

#define KpCurrent     _IQ12( 0.2 ) /* PI controller proportional gain */
#define KiCurrent     _IQ12( 0.035 ) /* PI controller integral gain */
#define KdCurrent			_IQ12( 0.24 )

#define duty_max      _IQ17( 0.95 )

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

# ifndef ASW_PICONTROLLER_C_SRC
# endif

extern uint8_t u8g_softstart_end;

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
extern void PiCtrl_PIController_Init( void );
extern uint16_t PiCtrl_DigitalCompensator( uint32_t VReferenceIQ, uint32_t IReferenceIQ );

#endif

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
