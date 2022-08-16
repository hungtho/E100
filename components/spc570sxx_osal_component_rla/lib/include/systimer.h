/****************************************************************************
*
* Copyright © 2015-2019 STMicroelectronics - All Rights Reserved
*
* License terms: STMicroelectronics Proprietary in accordance with licensing
* terms SLA0089 at www.st.com.
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* EVALUATION ONLY – NOT FOR USE IN PRODUCTION
*****************************************************************************/

/**
 * @file    systimer.h
 * @brief   OSAL module header.
 *
 * @addtogroup OSAL
 * @{
 */

#ifndef _SYSTIMER_H_
#define _SYSTIMER_H_

#include "irq.h"
#include "clock.h"
#include "platform.h"

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/**
 * @brief   System Timer (PIT channel 0) IRQ handler.
 * @note    PIT channel 0 is allocated permanently for system tick
 *          generation.
 */
#if !defined(OSAL_SYSTIMER_IRQ_HANDLER) || defined(__DOXYGEN__)
#define SPC5_SYSTIMER_IRQ_HANDLER           SPC_PIT_CH0_HANDLER
#endif

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* Inline functions.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* IRQ Handlers                                                              */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/
#ifdef __cplusplus
extern "C" {
#endif
  void sysTimeSetup(uint32_t ticks_per_sec);
  void sysTimeReset(void);
#ifdef __cplusplus
}
#endif
#endif /* _SYSTIMER_H_ */

/** @} */
