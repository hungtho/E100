/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : E100_LDC                                                    **
**  Filename  : spc570_hal_pwm.h                                            **
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

#ifndef SPC570_HAL_PWM_INCLUDED
#define SPC570_HAL_PWM_INCLUDED

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "components.h"
#include "Rte_typedef.h"

/****************************************************************************/
/**                                                                        **/
/**                      DEFINITIONS AND MACROS                            **/
/**                                                                        **/
/****************************************************************************/
#define SPC5_ETIMER3_TC3IR_NUMBER    ( 742U )
#define SPC5_ETIMER3_TC3IR_HANDLER   ( vector742 )
#define TIMER3										   ( ETIMER_3 )
#define PHASE_SHIFT_MAX_VAL				   ( 380U )

#define PWM_DUTY							( 50U )
#define PWM_DEAD_TIME					( 700U )	/* 700ns */
#define ETIMER_3_PERIOD				( ( ( uint32_t )SPC5_ETIMER_CLK / 100000 ) - 1U )
#define ETIMER_3_DUTY					( ( uint16_t )( ETIMER_3_PERIOD - ( ( ETIMER_3_PERIOD * PWM_DUTY ) / 100U ) ) )
#define ETIMER_3_DEAD_TIME		( ( uint16_t )( ( 2U * PWM_DEAD_TIME ) / 25U ) ) /* 1 Tick = 25ns */

/****************************************************************************/
/**                                                                        **/
/**                      TYPEDEFS AND STRUCTURES                           **/
/**                                                                        **/
/****************************************************************************/
/**
 * @brief Type of a structure representing an PIT driver.
 */
typedef struct ETIMERDriver eTIMERDriver;

/**
 * @brief   Structure representing a PIT driver.
 */
struct ETIMERDriver
{
  /**
   * @brief Pointer to the PIT registers block.
   */
  volatile struct ETIMER_tag  *etimer_tagp;
};

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/

# ifndef SPC570_HAL_PWM_C_SRC
# endif

extern eTIMERDriver ETIMER3;

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
extern void HAL_PSFB_Init( void );
extern void HAL_PSFB_OUTPUT_ENABLE( eTIMERDriver *etimerp );
extern void HAL_PSFB_OUTPUT_DISABLE( eTIMERDriver *etimerp );
extern void HAL_PSFB_SR_OUTPUT_ENABLE( eTIMERDriver *etimerp );
extern void HAL_PSFB_SR_OUTPUT_DISABLE( eTIMERDriver *etimerp );
extern void HAL_PSFB_SHIFT( uint16_t shift );
extern void HAL_PWM_SR_SET_DUTY( eTIMERDriver *etimerp, uint16_t duty );

#endif

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
