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
 * @file    osal.h
 * @brief   OSAL module header.
 *
 * @addtogroup OSAL
 * @{
 */

#ifndef _OSAL_H_
#define _OSAL_H_

#include "irq.h"
#include "osal_cfg.h"
#include "systimer.h"
#if (OSAL_FREERTOS_ENABLE == TRUE)
#include "FreeRTOS.h"
#include "task.h"
#endif /* (OSAL_FREERTOS_ENABLE == FALSE) */

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

#if (OSAL_SYSTIMER_ENABLE == TRUE)
/**
 * @brief   System Timer (PIT channel 0) IRQ handler.
 * @note    PIT channel 0 is allocated permanently for system tick
 *          generation.
 */
#if !defined(OSAL_SYSTIMER_IRQ_HANDLER) || defined(__DOXYGEN__)
#define OSAL_SYSTIMER_IRQ_HANDLER           SPC5_SYSTIMER_IRQ_HANDLER
#endif

/**
 * @brief   Backward compatibility macro's enabling.
 * @note    If set as TRUE some old macro's are defined to garantee backward
 *          compatibility.
 */
#if !defined(OSAL_BACKWARD_COMPATIBILITY) || defined(__DOXYGEN__)
#define OSAL_BACKWARD_COMPATIBILITY         TRUE
#endif
#endif /* (OSAL_SYSTIMER_ENABLE == TRUE) */

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

#if (OSAL_SYSTIMER_ENABLE == TRUE)
/**
 * @brief   Type of system time counter.
 */
typedef uint32_t osalsystime_t;
#endif /* (OSAL_SYSTIMER_ENABLE == TRUE) */

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

#if (OSAL_SYSTIMER_ENABLE == TRUE)
#if (OSAL_BACKWARD_COMPATIBILITY == TRUE)
/**
 * @brief   Delays for the specified number of seconds.
 */
#define sysWaitSeconds(sec) osalThreadDelaySeconds(sec)

/**
 * @brief   Delays for the specified number of milliseconds.
 */
#define sysWaitMilliseconds(msec) osalThreadDelayMilliseconds(msec)

/**
 * @brief   Delays for the specified number of microseconds.
 */
#define sysWaitMicroseconds(usec) osalThreadDelayMicroseconds(usec)

/**
 * @brief   Returns the system time in seconds.
 *
 */
#define sysGetSeconds() osalThreadGetSeconds()


/**
 * @brief   Returns the system time in milliseconds.
 *
 */
#define sysGetMilliseconds() osalThreadGetMilliseconds()

/**
 * @brief   Returns the system time in microseconds.
 *
 */
#define sysGetMicroseconds() osalThreadGetMicroseconds()

#endif /* OSAL_BACKWARD_COMPATIBILITY */
#endif /* OSAL_SYSTIMER_ENABLE */

/*===========================================================================*/
/* Inline functions.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* IRQ Handlers                                                              */
/*===========================================================================*/
#if ((OSAL_OS_ENABLE == FALSE) && (OSAL_SYSTIMER_ENABLE == TRUE))
IRQ_HANDLER(OSAL_SYSTIMER_IRQ_HANDLER);
#endif /* ((OSAL_OS_ENABLE == FALSE) && (OSAL_SYSTIMER_ENABLE == TRUE)) */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/
#ifdef __cplusplus
extern "C" {
#endif
  void osalInit(void);
#if (OSAL_SYSTIMER_ENABLE == TRUE)
  void osalSysTimeSetup(uint32_t ticks_per_sec);
  void osalSysTimeReset(void);
  void osalThreadDelaySeconds(uint32_t sec);
  void osalThreadDelayMilliseconds(uint32_t msec);
  void osalThreadDelayMicroseconds(uint32_t usec);
  uint32_t osalThreadGetSeconds(void);
  uint32_t osalThreadGetMilliseconds(void);
  uint32_t osalThreadGetMicroseconds(void);
#endif /* (OSAL_SYSTIMER_ENABLE == TRUE) */
  void osalEnterCritical(void);
  void osalExitCritical(void);
  void osalEnterCriticalFromISR(void);
  void osalExitCriticalFromISR(void);
#ifdef __cplusplus
}
#endif
#endif /* _OSAL_H_ */

/** @} */
