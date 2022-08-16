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
 * @file    eirq_cfg.h
 * @brief   External Interrupt configuration and management.
 *
 * @addtogroup EIRQ
 * @{
 */ 
 
#ifndef _EIRQ_CFG_H_
#define _EIRQ_CFG_H_

#include "eirq.h"

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

extern const eirq_config eirqconf[];

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

#define SPC5_EIRQ_0_IRQ_PRIORITY            INTC_PSR_ENABLE(INTC_PSR_MAINCORE,8)
#define SPC5_EIRQ_1_IRQ_PRIORITY            INTC_PSR_ENABLE(INTC_PSR_MAINCORE,8)
#define SPC5_EIRQ_2_IRQ_PRIORITY            INTC_PSR_ENABLE(INTC_PSR_MAINCORE,8)
#define SPC5_EIRQ_3_5_IRQ_PRIORITY          INTC_PSR_ENABLE(INTC_PSR_MAINCORE,8)

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/
#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif

#endif /* _EIRQ_CFG_H_ */

/** @} */
