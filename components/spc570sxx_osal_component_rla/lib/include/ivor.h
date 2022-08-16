/****************************************************************************
*
* Copyright © 2018-2019 STMicroelectronics - All Rights Reserved
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
 * @file    ivor.h
 * @brief   Interrupt Handler Macros.
 *
 * @addtogroup PPC_CORE
 * @{
 */

#define _FROM_ASM_
#include "core.h"

#if !defined(__DOXYGEN__)

 /* Context save.*/
.macro SAVE_CONTEXT
        e_stwu      sp, -80(sp)             /* Size of the extctx structure.*/
        e_stmvsrrw  8(sp)                   /* Saves PC, MSR (SRR0, SRR1).  */
        e_stmvsprw  16(sp)                  /* Saves CR, LR, CTR, XER.      */
        e_stmvgprw  32(sp)                  /* Saves GPR0, GPR3...GPR12.    */
.endm

/* Context restore.*/
.macro RESTORE_CONTEXT
        e_lmvgprw   32(sp)                  /* Restores GPR0, GPR3...GPR12.  */
        e_lmvsprw   16(sp)                  /* Restores CR, LR, CTR, XER.    */
        e_lmvsrrw   8(sp)                   /* Restores PC, MSR (SRR0, SRR1).*/
        e_addi      sp, sp, 80              /* Back to the previous frame.   */
.endm

/* Context save for critical class interrupt.*/
.macro SAVE_CONTEXT_CRITICAL
        e_stwu      sp, -80(sp)             /* Size of the extctx structure.*/
        e_stmvcsrrw  8(sp)                  /* Saves PC, MSR (CSRR0, CSRR1).*/
        e_stmvsprw  16(sp)                  /* Saves CR, LR, CTR, XER.      */
        e_stmvgprw  32(sp)                  /* Saves GPR0, GPR3...GPR12.    */
.endm

/* Context restore for critical class interrupt.*/
.macro RESTORE_CONTEXT_CRITICAL
        e_lmvgprw   32(sp)                  /* Restores GPR0, GPR3...GPR12.    */
        e_lmvsprw   16(sp)                  /* Restores CR, LR, CTR, XER.      */
        e_lmvcsrrw   8(sp)                  /* Restores PC, MSR (CSRR0, CSRR1).*/
        e_addi      sp, sp, 80              /* Back to the previous frame.     */
.endm

/* Context save for Machine Check class interrupt.*/
.macro SAVE_CONTEXT_MACHINE_CHECK
        e_stwu			sp, -80(sp)			/* Size of the extctx structure.*/
        e_stmvmcsrrw	8(sp)				/* Saves PC, MSR (MCSRR0, MCSRR1).*/
        e_stmvsprw		16(sp)				/* Saves CR, LR, CTR, XER.      */
        e_stmvgprw		32(sp)				/* Saves GPR0, GPR3...GPR12.    */
.endm

/* Context restore for Machine Check class interrupt.*/
.macro RESTORE_MACHINE_CHECK
        e_lmvgprw		32(sp)				/* Restores GPR0, GPR3...GPR12.    */
        e_lmvsprw		16(sp)				/* Restores CR, LR, CTR, XER.      */
        e_lmvmcsrrw		8(sp)				/* Restores PC, MSR (MCSRR0, MCSRR1).*/
        e_addi			sp, sp, 80			/* Back to the previous frame.     */
.endm

/*
 * Prepare SRR0 and SRR1 registers as callback's parameters, moreover do some stuff
 * to calculate the returning address after handling IVOR exceptions, to avoid the
 * exception is raised again. The returning address is the next instruction of SRR0.
 */
.macro LOAD_SSR0_SSR1_PLUS
		mfspr 		%r5,26				/* Load SRR0 -> r5 */
		se_mr		%r3,%r5				/* Prepare 1st parameter (SRR0) for the callback. */
		mfspr		%r4,27				/* Prepare 2nd parameter (SRR1) for the callback. */
        se_lhz 		%r6,0(%r5)			/* Determine opcode @ SRR0 */
        e_andi. 	%r7,%r6,0x9000
        e_cmpli 	0x0,%r7,0x1000		/* Check bit 31,28 only */

		se_bc		0x1,0x0,0x4			/* Skip next instruction if CR is true. */
        se_addi 	%r5,2				/* 0xx1 => 32 bit */

        se_addi 	%r5,2				/* All others just 16 bit long */

        e_stw       %r5, 8(sp)			/* Override the SRR0 previously saved in stack with the new one */
.endm

/*
 * Prepare SRR0 and SRR1 registers as callback's parameters.
 */
.macro LOAD_SSR0_SSR1
		mfspr 		%r3,26				/* Prepare 1st parameter (SRR0) for the callback. */
		mfspr		%r4,27				/* Prepare 2nd parameter (SRR1) for the callback. */
.endm

 /*
 * Prepare CSRR0 and CSRR1 registers as callback's parameters.
 */
.macro LOAD_CSSR0_CSSR1
		mfspr 		%r3,58				/* Prepare 1st parameter (CSRR0) for the callback. */
		mfspr		%r4,59				/* Prepare 2nd parameter (CSRR1) for the callback. */
.endm

/*
 * Prepare MCSRR0 and MCSRR1 registers as callback's parameters, moreover do some stuff
 * to calculate the returning address after handling IVOR1 exception, to avoid the
 * exception is raised again. The returning address is the next instruction of MCSRR0.
 */
.macro LOAD_MCSSR0_MCSSR1
		mfspr 		%r5,570				/* Load MCSRR0 -> r5 */
		se_mr		%r3,%r5				/* Prepare 1st parameter (MCSRR0) for the callback. */
		mfspr		%r4,571				/* Prepare 2nd parameter (MCSRR1) for the callback. */
        se_lhz 		%r6,0(%r5)			/* Determine opcode @ MCSRR0 */
        e_andi. 	%r7,%r6,0x9000
        e_cmpli 	0x0,%r7,0x1000		/* Check bit 31,28 only */

		se_bc		0x1,0x0,0x4			/* Skip next instruction if CR is true. */
        se_addi 	%r5,2				/* 0xx1 => 32 bit */

        se_addi 	%r5,2				/* All others just 16 bit long */

        e_stw       %r5, 8(sp)			/* Override the MCSRR0 previously saved in stack with the new one */
.endm

/*
 * Prepare DSRR0 and DSRR1 registers as callback's parameters, moreover do some stuff
 * to calculate the returning address after handling IVOR9 exception, to avoid the
 * exception is raised again. The returning address is the next instruction of MCSRR0.
 */
.macro LOAD_DSSR0_DSSR1
		mfspr 		%r5,574				/* Load DSRR0 -> r5 */
		se_mr		%r3,%r5				/* Prepare 1st parameter (DSRR0) for the callback. */
		mfspr		%r4,575				/* Prepare 2nd parameter (DSRR1) for the callback. */
        se_lhz 		%r6,0(%r5)			/* Determine opcode @ DSRR0 */
        e_andi. 	%r7,%r6,0x9000
        e_cmpli 	0x0,%r7,0x1000		/* Check bit 31,28 only */

		se_bc		0x1,0x0,0x4			/* Skip next instruction if CR is true. */
        se_addi 	%r5,2				/* 0xx1 => 32 bit */

        se_addi 	%r5,2				/* All others just 16 bit long */

        e_stw       %r5, 8(sp)			/* Override the DSRR0 previously saved in stack with the new one */
.endm



#endif /* !defined(__DOXYGEN__) */

#if (CORE_VARIANT == 0)
#include "ivor_z0.h"
#endif

#if (CORE_VARIANT == 2)
#include "ivor_z2.h"
#endif

#if (CORE_VARIANT == 3)
#include "ivor_z3.h"
#endif

#if (CORE_VARIANT == 4)
#include "ivor_z4.h"
#endif

 /** @} */
