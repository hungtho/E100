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
 * @file    irq_cfg.h
 * @brief   IRQ configuration macros and structures.
 *
 * @addtogroup IRQ
 * @{
 */

#ifndef _IRQ_CFG_H_
#define _IRQ_CFG_H_

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/**
 * @name    Common constants
 * @{
 */
#if !defined(FALSE) || defined(__DOXYGEN__)
#define FALSE                       0U
#endif

#if !defined(TRUE) || defined(__DOXYGEN__)
#define TRUE                        1U
#endif

/**
 * @name    ISR vectors identifiers
 * @{
 */
/** @} */

/**
 * @name    ISR vectors names overrides
 * @{
 */
/** @} */

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
/* External declarations.                                                    */
/*===========================================================================*/

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void irq_cfg_init(void);
#ifdef __cplusplus
}
#endif
#endif /* !defined(_FROM_ASM_) */

#endif /* _IRQ_CFG_H_ */

/** @} */
