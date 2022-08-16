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
 * @file    irq.h
 * @brief   IRQ module header.
 *
 * @addtogroup IRQ
 * @{
 */

#ifndef _IRQ_H_
#define _IRQ_H_

#include "vectors.h"
#include "irq_cfg.h"
#include "platform.h"

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/**
 * @brief   IRQ prologue code.
 * @details This macro must be inserted at the start of all IRQ handlers.
 */
#define IRQ_PROLOGUE()

/**
 * @brief   IRQ epilogue code.
 * @details This macro must be inserted at the end of all IRQ handlers.
 */
#define IRQ_EPILOGUE()

/**
 * @brief   IRQ handler function declaration.
 * @details This macro hides the details of an ISR function declaration.
 *
 * @param[in] id        a vector name as defined in @p vectors.s
 */
#define IRQ_HANDLER(id) void id(void)

/*===========================================================================*/
/* Inline functions.                                                            */
/*===========================================================================*/

/**
 * @brief   Globally enables interrupts.
 *
 * @special
 */
static inline
void irqIsrEnable(void) {

  asm volatile("wrteei  1" : : : "memory");
}

/**
 * @brief   Globally disables interrupts.
 *
 * @special
 */
static inline
void irqIsrDisable(void) {

  asm volatile ("wrteei  0" : : : "memory");
}

/**
 * @brief   Returns the value of the Machine State Register (MSR).
 *
 * @special
 */
static inline uint32_t irqGetMsr(void) {

  uint32_t msr = 0UL;

  asm volatile("mfmsr %0" : "=r" (msr) :);

  return msr;
}

/**
 * @brief   Returns the value of the External Interrupt Enable (MSR[EE]) bit.
 *
 * @special
 */
static inline
uint32_t irqGetExtIntEnable(void) {

  uint32_t msr;

  msr = irqGetMsr();

  return (0x1UL & (msr >> 15U));
}

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/
#ifdef __cplusplus
extern "C" {
#endif
  void irqInit(void);
  void irqSysHalt(void);
#ifdef __cplusplus
}
#endif

#endif /* _IRQ_H_ */

/** @} */
