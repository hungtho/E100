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
 * @file    eirq.h
 * @brief   SPC5xx EIRQ header.
 *
 * @addtogroup EIRQ
 * @{
 */

#ifndef _EIRQ_H_
#define _EIRQ_H_

#include <stddef.h>
#include "vectors.h"
#include "irq.h"
#include "platform.h"


/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/


//valori di default per macro non definite 


/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   EIRQ notification callback type.
 *
 */
typedef void (*eirqcallback_t)(void);

/**
 * @brief   Structure representing a PIT Channel configuration
 */
typedef struct {
  /**
   * @brief   eirq number.
   */  
  int8_t eirqNumber;
  /**
   * @brief   rising edge trigger event
   */
  uint8_t risingEdge;
  /**
   * @brief    falling edge trigger event
   */
  uint8_t fallingEdge;
  /**
   * @brief    Antiglitch filter enable on PIN
   */
  uint8_t filterEnable;
   /**
   * @brief   callback function.
   */
  eirqcallback_t callback;
}eirq_config;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/
/*===========================================================================*/
/* IRQ Handlers                                                              */
/*===========================================================================*/
#if defined (_SPC570Sxx_) || defined (_SPC574Sxx_)|| defined(__DOXYGEN__)
#if (SPC5_SIUL_EIRQ_HAS_0_HANDLER == TRUE)
IRQ_HANDLER(SPC5_SIUL_EIRQ_0_HANDLER);
#endif
#if (SPC5_SIUL_EIRQ_HAS_1_HANDLER == TRUE)
IRQ_HANDLER(SPC5_SIUL_EIRQ_1_HANDLER);
#endif
#if (SPC5_SIUL_EIRQ_HAS_2_HANDLER == TRUE)
IRQ_HANDLER(SPC5_SIUL_EIRQ_2_HANDLER);
#endif
#if (SPC5_SIUL_EIRQ_HAS_3_5_HANDLER == TRUE)
IRQ_HANDLER(SPC5_SIUL_EIRQ_3_5_HANDLER);
#endif
#elif defined (_SPC574Kxx_)|| defined(__DOXYGEN__)
#if (SPC5_SIUL_EIRQ_HAS_0_7_HANDLER == TRUE)
IRQ_HANDLER(SPC5_SIUL_EIRQ_0_7_HANDLER);
#endif
#if (SPC5_SIUL_EIRQ_HAS_8_15_HANDLER == TRUE)
IRQ_HANDLER(SPC5_SIUL_EIRQ_8_15_HANDLER);
#endif
#endif
#if defined (_SPC582Bxx_) || defined(_SPC584Bxx_) || defined (_SPC58ECxx_) || defined (_SPC58xGxx_) || defined (_SPC58xNxx_) || defined (_SPC572Lxx_) || defined(__DOXYGEN__)
#if (SPC5_SIUL_HAS_EXT_INT_0_HANDLER == TRUE)
IRQ_HANDLER(SPC5_SIUL_EXT_INT_0_HANDLER);
#endif
#if (SPC5_SIUL_HAS_EXT_INT_1_HANDLER == TRUE)
IRQ_HANDLER(SPC5_SIUL_EXT_INT_1_HANDLER);
#endif
#if (SPC5_SIUL_HAS_EXT_INT_2_HANDLER == TRUE)
IRQ_HANDLER(SPC5_SIUL_EXT_INT_2_HANDLER);
#endif
#if (SPC5_SIUL_HAS_EXT_INT_3_HANDLER == TRUE)
IRQ_HANDLER(SPC5_SIUL_EXT_INT_3_HANDLER);
#endif
#endif

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
void eirqInit(void);
#ifdef __cplusplus
}
#endif

#endif
/** @} */
