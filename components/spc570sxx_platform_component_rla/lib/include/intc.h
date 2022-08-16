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
 * @file    intc.h
 * @brief   INTC module header.
 *
 * @addtogroup PLATFORM
 * @{
 */

#ifndef _INTC_H_
#define _INTC_H_

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/**
 * @brief   INTC base address.
 */
#define INTC_BASE                           0xFC040000U

/*lint -e9048 */
/* The following macros are include in assembler file. So suffixs 'U' or 'UL'
   are not allowed.*/
/**
 * @brief   Interrupt Acknowledge register base address.
 */
#define INTC_IACKR_BASE                     0xFC040020

/**
 * @brief   End of Interrupt register base address.
 */
#define INTC_EOIR_BASE                      0xFC040030
/*lint +e9048 */

/**
 * @brief   INTC PSR register definitions
 */
/* TODO    Some platforms support more than 16 priority levels.*/
#define INTC_PSR_PRIO_MASK                  0x000F

/**
 * @brief   Core selection macro for PSR register.
 */
#define INTC_PSR_CORE0                      0x8000

/**
 * @brief   Main Core selection macro for PSR register.
 */
#define INTC_PSR_MAINCORE                   INTC_PSR_CORE0

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

/**
 * @brief   INTC-related macros
 */
#define INTC_BCR                            (*((volatile uint32_t *)(INTC_BASE + 0U)))
#define INTC_CPR(n)                         (*((volatile uint32_t *)(INTC_BASE + 0x10U + ((uint8_t)(n) * sizeof (uint32_t)))))
#define INTC_IACKR(n)                       (*((volatile uint32_t *)(INTC_BASE + 0x20U + ((uint8_t)(n) * sizeof (uint32_t)))))
#define INTC_EOIR(n)                        (*((volatile uint32_t *)(INTC_BASE + 0x30U + ((uint8_t)(n) * sizeof (uint32_t)))))
#define INTC_PSR(n)                         (*((volatile uint16_t *)(INTC_BASE + 0x60U + ((uint16_t)(n) * sizeof (uint16_t)))))

/**
 * @brief   PSR register content helper
 */
#define INTC_PSR_ENABLE(cores, prio)        ((uint16_t)(cores) | (uint16_t)(prio))


/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

#endif /* _INTC_H_ */

/** @} */
