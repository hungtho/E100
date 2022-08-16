/****************************************************************************
*
* Copyright © 2017-2019 STMicroelectronics - All Rights Reserved
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
 * @file    ivor_cfg.h
 * @brief   IVOR Handling configuration.
 *
 * @addtogroup IVOR
 * @{
 */

#ifndef _IVOR_CFG_H_
#define _IVOR_CFG_H_

#include "osal_cfg.h"

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module IVOR Handling settings.                                            */
/*===========================================================================*/

#if (OSAL_OS_ENABLE == FALSE)

/**
 * @brief   IVOR0 Critical Input Interrupt Handler.
 * @details It is set to @p TRUE, IVOR0 interrupt will be handled calling the
 * relative callback (i.e. ivor0_callback), passing CSRR0 and CSRR1 registers
 * as parameter (containing respectively, the address of next instruction to
 * be executed and Machine State Register at the time of interrupt).
 */
 
#define IVOR0_HANDLER						FALSE

/**
 * @brief   IVOR1 Machine Check Interrupt Handler.
 * @details It is set to @p TRUE, IVOR1 interrupt will be handled calling the
 * relative callback (i.e. ivor1_callback), passing MCSRR0 and MCSRR1 or 
 * CSRR0 and CSRR1 registers as parameter (containing respectively, an instruction
 * address, as closely as possible, set to the effective address of an instruction
 * that  was  executing or about to be executed when the Machine Check exception occurred,
 * and Machine State Register at the time of interrupt).
 * The set of the registers depends by the MCU.
 */
#define IVOR1_HANDLER						FALSE

/**
 * @brief   IVOR2 Data Storage Interrupt Handler.
 * @details It is set to @p TRUE, IVOR2 interrupt will be handled calling the
 * relative callback (i.e. ivor2_callback), passing SRR0 and SRR1 registers
 * as parameter (containing respectively, the instruction's address causing
 * Data Storage interrupt and the Machine State Register at the time of
 * interrupt).
 */
#define IVOR2_HANDLER						FALSE

/**
 * @brief   IVOR3 Instruction Storage Interrupt Handler.
 * @details It is set to @p TRUE, IVOR3 interrupt will be handled calling the
 * relative callback (i.e. ivor3_callback), passing SRR0 and SRR1 registers
 * as parameter (containing respectively, the instruction's address causing
 * Instruction Storage interrupt and the Machine State Register at the time of
 * interrupt).
 */
#define IVOR3_HANDLER						FALSE

/**
 * @brief   IVOR5 Alignment Interrupt Handler.
 * @details It is set to @p TRUE, IVOR5 interrupt will be handled calling the
 * relative callback (i.e. ivor5_callback), passing SRR0 and SRR1 registers
 * as parameter (containing respectively, the instruction's address causing
 * Alignment interrupt and the Machine State Register at the time of
 * interrupt).
 */
#define IVOR5_HANDLER						FALSE

/**
 * @brief   IVOR6 Program Interrupt Handler.
 * @details It is set to @p TRUE, IVOR6 interrupt will be handled calling the
 * relative callback (i.e. ivor6_callback), passing SRR0 and SRR1 registers
 * as parameter (containing respectively, the instruction's address causing
 * Program interrupt and the Machine State Register at the time of
 * interrupt).
 */
#define IVOR6_HANDLER						FALSE

/**
 * @brief   IVOR7 Floating-point unavailable Interrupt Handler.
 * @details It is set to @p TRUE, IVOR7 interrupt will be handled calling the
 * relative callback (i.e. ivor7_callback), passing SRR0 and SRR1 registers
 * as parameter (containing respectively, the instruction's address causing
 * Floating-point unavailable interrupt and the Machine State Register at the
 * time of interrupt).
 */
#define IVOR7_HANDLER						FALSE

/**
 * @brief   IVOR8 System Call Interrupt Handler.
 * @details It is set to @p TRUE, IVOR8 interrupt will be handled calling the
 * relative callback (i.e. ivor8_callback), passing SRR0 and SRR1 registers
 * as parameter (containing respectively, the instruction's address after the
 * sc instruction and the Machine State Register at the time of interrupt).
 */
#define IVOR8_HANDLER						FALSE

/**
 * @brief   IVOR9 Auxiliary Processor Unavailable or Debug Interrupt Handler.
 * @details It is set to @p TRUE, IVOR9 interrupt will be handled calling the
 * relative callback (i.e. ivor9_callback), passing SRR0 and SRR1 or 
 * DDSR0 and DDSR1 registers as parameter (containing respectively,
 * the instruction's address causing Auxiliary Processor Unavailable or Debug
 * interrupt and the Machine State Register at the time of interrupt).
 */
#define IVOR9_HANDLER						FALSE

/**
 * @brief   IVOR11 Fixed Interval Timer Interrupt Handler.
 * @details It is set to @p TRUE, IVOR11 interrupt will be handled calling the
 * relative callback (i.e. ivor11_callback), passing SRR0 and SRR1 registers
 * as parameter (containing respectively, the effective address of the next
 * instruction to be executed and the Machine State Register at the time of
 * interrupt).
 */
#define IVOR11_HANDLER						FALSE

/**
 * @brief   IVOR12 Watchdog Timer Interrupt Handler.
 * @details It is set to @p TRUE, IVOR12 interrupt will be handled calling the
 * relative callback (i.e. ivor12_callback), passing SRR0 and SRR1 registers
 * as parameter (containing respectively, the effective address of the next
 * instruction to be executed and the Machine State Register at the time of
 * interrupt).
 */
#define IVOR12_HANDLER						FALSE

/**
 * @brief   IVOR13 Data TLB Error Interrupt Handler.
 * @details It is set to @p TRUE, IVOR13 interrupt will be handled calling the
 * relative callback (i.e. ivor13_callback), passing SRR0 and SRR1 registers
 * as parameter (containing respectively, the instruction's address causing
 * Data TLB Error interrupt and the Machine State Register at the time of
 * interrupt).
 */
#define IVOR13_HANDLER						FALSE

/**
 * @brief   IVOR14 Instruction TLB Error Interrupt Handler.
 * @details It is set to @p TRUE, IVOR14 interrupt will be handled calling the
 * relative callback (i.e. ivor14_callback), passing SRR0 and SRR1 registers
 * as parameter (containing respectively, the instruction's address causing
 * Instruction TLB Error interrupt and the Machine State Register at the time
 * of interrupt).
 */
#define IVOR14_HANDLER						FALSE

/**
 * @brief   IVOR15 Debug Interrupt Handler for SPC56 MCU Family
 * @details It is set to @p TRUE, IVOR15 interrupt will be handled calling the
 * relative callback (i.e. ivor15_callback), passing CSRR0 and CSRR1 registers
 * as parameter (containing respectively, the instruction's address and the
 * Machine Status register when the IVOR15 interrupt has been raised).
 */
#define IVOR15_HANDLER						FALSE

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

#endif /* _IVOR_CFG_H_ */

/** @} */
