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
 * @file    osal_cfg.h
 * @brief   OSAL configuration macros and structures.
 *
 * @addtogroup OSAL
 * @{
 */

#ifndef _OSAL_CFG_H_
#define _OSAL_CFG_H_

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @brief   FreeRTOS Operating System enable switch.
 * @details If set to @p TRUE the support for FreeRTOS Operating System is 
 *          included.
 */
#define OSAL_FREERTOS_ENABLE                FALSE

/**
 * @brief   Operating System enable switch.
 * @details It is set to @p TRUE if one of the supported Operating System is 
 *          included.
 */
#if (OSAL_FREERTOS_ENABLE == TRUE)
#define OSAL_OS_ENABLE                      TRUE
#else
#define OSAL_OS_ENABLE                      FALSE
#endif

/**
 * @brief   IRQ preemption enable switch.
 * @details If set to @p TRUE the IRQ preemption is enabled.
 */
#if !defined(OSAL_ENABLE_IRQ_PREEMPTION)
#define OSAL_ENABLE_IRQ_PREEMPTION          TRUE
#endif

/**
 * @brief   System Timer enable.
 * @details If set to @p TRUE the System Timer is enabled.
 */
#if !defined(OSAL_SYSTIMER_ENABLE) || defined(__DOXYGEN__)
#define OSAL_SYSTIMER_ENABLE                FALSE
#endif

/**
 * @brief   System timer tick frequency [Hz].
 * @details Number of system timer ticks in a second.
 */
#if !defined(OSAL_SYSTIMER_TICK_FREQ_HZ) || defined(__DOXYGEN__)
#define OSAL_SYSTIMER_TICK_FREQ_HZ          1000
#endif

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
/* External declarations.                                                    */
/*===========================================================================*/

#endif /* _OSAL_CFG_H_ */

/** @} */
