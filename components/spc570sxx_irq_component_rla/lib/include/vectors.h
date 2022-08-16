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
 * @file    vectors.h
 * @brief   ISR vector module header.
 *
 * @addtogroup VECTORS
 * @{
 */

#ifndef _VECTORS_H_
#define _VECTORS_H_

#include "platform.h"

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/**
 * @brief   Number of ISR vectors available.
 */
#define VECTORS_NUMBER                      1024

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

#if !defined(__DOXYGEN__)
extern uint32_t _vectors[VECTORS_NUMBER];
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void _unhandled_irq(void);
#ifdef __cplusplus
}
#endif

#endif /* !defined(_FROM_ASM_) */

#endif /* _VECTORS_H_ */

/** @} */
