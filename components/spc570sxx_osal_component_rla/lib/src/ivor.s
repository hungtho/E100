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
 * @file    ivor.s
 * @brief   Kernel ISRs.
 *
 * @addtogroup PPC_CORE
 * @{
 */

/*
 * Imports the configuration headers.
 */
#define _FROM_ASM_
#include "platform.h"
#include "irq_cfg.h"
#include "osal_cfg.h"
#include "ivor_cfg.h"
#include "boot.h"
#include "ivor.h"

#if !defined(__DOXYGEN__)

#if (OSAL_OS_ENABLE == FALSE)

        .section    .handlers, "axv"
_VLE

        /*
         * _IVOR0 handler (Critical input Interrupt).
         */
#if IVOR0_HANDLER
        .align      4
        .globl      _IVOR0
        .type       _IVOR0, @function
_IVOR0:
        SAVE_CONTEXT_CRITICAL

        LOAD_CSSR0_CSSR1

        e_bl        _ivor0_callback     /* Branch to the proper callback*/

        RESTORE_CONTEXT_CRITICAL
        se_rfci
#endif

        /*
         * _IVOR1 handler (Machine Check Interrupt).
         */
#if IVOR1_HANDLER
        .align      4
        .globl      _IVOR1
        .type       _IVOR1, @function
_IVOR1:
       /* 
		* SAVE_CONTEXT_CRITICAL
        * LOAD_IVOR1_EXC_REG
        * e_bl        _ivor1_callback      Branch to the proper callback
        * RESTORE_CONTEXT_CRITICAL
        * RET_IVOR1
		*/

		e_stwu      sp, -80(sp)     /* Size of the extctx structure.*/
        e_stmvcsrrw  8(sp)          /* Saves PC, MSR (CSRR0, CSRR1).*/
        e_stmvsprw  16(sp)          /* Saves CR, LR, CTR, XER.      */
        e_stmvgprw  32(sp)          /* Saves GPR0, GPR3...GPR12.    */

        mfspr     %r3,570           /* Prepare 1st parameter (MCSRR0) for the callback. */
        mfspr     %r4,572           /* Prepare 2nd parameter (MCSR) for the callback. */

        mtspr     572,%r4           /* Clear MCSR. */

        e_bl _ivor1_callback        /* Branch to the proper callback */

        e_lmvgprw   32(sp)          /* Restores GPR0, GPR3...GPR12.    */
        e_lmvsprw   16(sp)          /* Restores CR, LR, CTR, XER.      */
        e_lmvcsrrw   8(sp)          /* Restores PC, MSR (CSRR0, CSRR1).*/
        e_addi      sp, sp, 80      /* Back to the previous frame.     */

        se_rfmci
#endif

        /*
         * _IVOR2 handler (Data Storage Interrupt).
         */
#if IVOR2_HANDLER
        .align      4
        .globl      _IVOR2
        .type       _IVOR2, @function
_IVOR2:
        SAVE_CONTEXT

        LOAD_SSR0_SSR1_PLUS

        e_bl        _ivor2_callback     /* Branch to the proper callback*/

        RESTORE_CONTEXT
        se_rfi
#endif

        /*
         * _IVOR3 handler (Instruction Storage Interrupt).
         */
#if IVOR3_HANDLER
        .align      4
        .globl      _IVOR3
        .type       _IVOR3, @function
_IVOR3:
        SAVE_CONTEXT

        LOAD_SSR0_SSR1_PLUS

        e_bl        _ivor3_callback     /* Branch to the proper callback*/

        RESTORE_CONTEXT
        se_rfi
#endif

#if (CORE_SUPPORTS_DECREMENTER == 1)
        /*
         * _IVOR10 handler (Book-E decrementer).
         */
        .align      4
        .globl      _IVOR10
        .type       _IVOR10, @function
_IVOR10:
#if (BOOT_CORE0 == 1)
_C0_IVOR10:
#endif
        SAVE_CONTEXT

        /* Reset DIE bit in TSR register.*/
        e_lis       %r3, 0x0800             /* DIS bit mask.                */
        mtspr       336, %r3                /* TSR register.                */

        /* Restoring pre-IRQ MSR register value.*/
        mfSRR1      %r0

        /* No preemption, keeping EE disabled.*/
        se_bclri    %r0, 16                 /* EE = bit 16.                 */
        mtMSR       %r0

        RESTORE_CONTEXT
        se_rfi
#endif /* CORE_SUPPORTS_DECREMENTER */

        /*
         * _IVOR4 handler (Book-E external interrupt).
         */
        .align      4
        .globl      _IVOR4
        .type       _IVOR4, @function
_IVOR4:
        SAVE_CONTEXT

        /* Software vector address from the INTC register.*/
        e_lis       %r3, HI(INTC_IACKR_BASE) /*IACKR register address.      */
        e_or2i      %r3, LO(INTC_IACKR_BASE)
        se_lwz      %r3, 0(%r3)             /* IACKR register value.        */
        se_lwz      %r3, 0(%r3)
        se_mtCTR    %r3                     /* Software handler address.    */

        /* Restoring pre-IRQ MSR register value.*/
        mfSRR1      %r0
        /* No preemption, keeping EE disabled.*/
        se_bclri    %r0, 16                 /* EE = bit 16.                 */
        mtMSR       %r0

#if (OSAL_ENABLE_IRQ_PREEMPTION == TRUE)
        /* Allows preemption while executing the software handler.*/
        wrteei      1
#endif /* OSAL_ENABLE_IRQ_PREEMPTION */

        /* Executes the software handler.*/
        se_bctrl

#if (OSAL_ENABLE_IRQ_PREEMPTION == TRUE)
        /* Prevents preemption again.*/
        wrteei      0
#endif /* OSAL_ENABLE_IRQ_PREEMPTION */

        /* Informs the INTC that the interrupt has been served.*/
        mbar        0
        e_lis       %r3, HI(INTC_EOIR_BASE)
        e_or2i      %r3, LO(INTC_EOIR_BASE)
        se_stw      %r3, 0(%r3)             /* Writing any value should do. */

        RESTORE_CONTEXT
        se_rfi

#if (BOOT_CORE0 == 1)
        /*
         * _C0_IVOR4 handler (Book-E external interrupt).
         */
        .align      4
        .globl      _C0_IVOR4
        .type       _C0_IVOR4, @function
_C0_IVOR4:
        SAVE_CONTEXT

        /* Software vector address from the INTC register.*/
        e_lis       %r3, HI(INTC_IACKR_BASE_0) /*IACKR register address.    */
        e_or2i      %r3, LO(INTC_IACKR_BASE_0)
        se_lwz      %r3, 0(%r3)             /* IACKR register value.        */
        se_lwz      %r3, 0(%r3)
        se_mtCTR    %r3                     /* Software handler address.    */

        /* Restoring pre-IRQ MSR register value.*/
        mfSRR1      %r0
        /* No preemption, keeping EE disabled.*/
        se_bclri    %r0, 16                 /* EE = bit 16.                 */
        mtMSR       %r0

#if (OSAL_ENABLE_IRQ_PREEMPTION == TRUE)
        /* Allows preemption while executing the software handler.*/
        wrteei      1
#endif /* OSAL_ENABLE_IRQ_PREEMPTION */

        /* Executes the software handler.*/
        se_bctrl

#if (OSAL_ENABLE_IRQ_PREEMPTION == TRUE)
        /* Prevents preemption again.*/
        wrteei      0
#endif /* OSAL_ENABLE_IRQ_PREEMPTION */

        /* Informs the INTC that the interrupt has been served.*/
        mbar        0
        e_lis       %r3, HI(INTC_EOIR_BASE_0)
        e_or2i      %r3, LO(INTC_EOIR_BASE_0)
        se_stw      %r3, 0(%r3)             /* Writing any value should do. */

        RESTORE_CONTEXT
        se_rfi
#endif /* BOOT_CORE0 */

#if (BOOT_CORE1 == 1 && !defined (_SPC56ELxx_))
        /*
         * _C1_IVOR4 handler
         */
        .align      4
        .globl      _C1_IVOR4
        .type       _C1_IVOR4, @function
_C1_IVOR4:
        SAVE_CONTEXT

        /* Software vector address from the INTC register.*/
        e_lis       %r3, HI(INTC_IACKR_BASE_1) /*IACKR register address.    */
        e_or2i      %r3, LO(INTC_IACKR_BASE_1)
        se_lwz      %r3, 0(%r3)             /* IACKR register value.        */
        se_lwz      %r3, 0(%r3)
        se_mtCTR    %r3                     /* Software handler address.    */

        /* Restoring pre-IRQ MSR register value.*/
        mfSRR1      %r0
        /* No preemption, keeping EE disabled.*/
        se_bclri    %r0, 16                 /* EE = bit 16.                 */
        mtMSR       %r0

#if (OSAL_ENABLE_IRQ_PREEMPTION == TRUE)
        /* Allows preemption while executing the software handler.*/
        wrteei      1
#endif /* OSAL_ENABLE_IRQ_PREEMPTION */

        /* Executes the software handler.*/
        se_bctrl

#if (OSAL_ENABLE_IRQ_PREEMPTION == TRUE)
        /* Prevents preemption again.*/
        wrteei      0
#endif /* OSAL_ENABLE_IRQ_PREEMPTION */

        /* Informs the INTC that the interrupt has been served.*/
        mbar        0
        e_lis       %r3, HI(INTC_EOIR_BASE_1)
        e_or2i      %r3, LO(INTC_EOIR_BASE_1)
        se_stw      %r3, 0(%r3)             /* Writing any value should do. */

        RESTORE_CONTEXT
        se_rfi
#endif /* BOOT_CORE1 */

        /*
         * _IVOR5 handler (Alignement Exception).
         */
#if IVOR5_HANDLER
        .align      4
        .globl      _IVOR5
        .type       _IVOR5, @function
_IVOR5:
        SAVE_CONTEXT

        LOAD_SSR0_SSR1_PLUS

        e_bl        _ivor5_callback     /* Branch to the proper callback */

        RESTORE_CONTEXT
        se_rfi
#endif

        /*
         * _IVOR6 handler (Program Interrupt Exception).
         */
#if IVOR6_HANDLER
        .align      4
        .globl      _IVOR6
        .type       _IVOR6, @function
_IVOR6:
        SAVE_CONTEXT

        LOAD_SSR0_SSR1_PLUS

        e_bl        _ivor6_callback     /* Branch to the proper callback */

        RESTORE_CONTEXT
        se_rfi
#endif

        /*
         * _IVOR7 handler (Floating-Point Interrupt Exception).
         */
#if IVOR7_HANDLER
        .align      4
        .globl      _IVOR7
        .type       _IVOR7, @function
_IVOR7:
        SAVE_CONTEXT

        LOAD_SSR0_SSR1_PLUS

        e_bl        _ivor7_callback     /* Branch to the proper callback */

        RESTORE_CONTEXT
        se_rfi
#endif

        /*
         * _IVOR8 handler (System Call Interrupt Exception).
         */
#if IVOR8_HANDLER
        .align      4
        .globl      _IVOR8
        .type       _IVOR8, @function
_IVOR8:
        SAVE_CONTEXT

        LOAD_SSR0_SSR1

        e_bl        _ivor8_callback     /* Branch to the proper callback */

        RESTORE_CONTEXT
        se_rfi
#endif

        /*
         * _IVOR9 handler (Auxiliary Processor Unavailable or Debug Interrupt Exception).
         */
#if IVOR9_HANDLER
        .align      4
        .globl      _IVOR9
        .type       _IVOR9, @function
_IVOR9:
        SAVE_CONTEXT

        LOAD_IVOR9_EXC_REG

        e_bl        _ivor9_callback     /* Branch to the proper callback */

        RESTORE_CONTEXT

        RET_IVOR9
#endif

        /*
         * _IVOR11 handler (Fixed Interval Timer Interrupt Exception).
         */
#if IVOR11_HANDLER
        .align      4
        .globl      _IVOR11
        .type       _IVOR11, @function
_IVOR11:
        SAVE_CONTEXT

        LOAD_SSR0_SSR1

        e_bl        _ivor11_callback    /* Branch to the proper callback */
#if 0
        /* Reset FIS bit in TSR register.*/
        e_lis       %r3, 0x0400             /* FIS bit mask.                */
        mtspr       336, %r3                /* TSR register.                */

        /* Restoring pre-IRQ MSR register value.*/
        mfSRR1      %r0

        /* No preemption, keeping EE disabled.*/
        se_bclri    %r0, 16                 /* EE = bit 16.                 */
        mtMSR       %r0
#endif
        RESTORE_CONTEXT
        se_rfi
#endif

        /*
         * _IVOR12 handler (Watchdog Timer Interrupt Exception).
         */
#if IVOR12_HANDLER
        .align      4
        .globl      _IVOR12
        .type       _IVOR12, @function
_IVOR12:
        SAVE_CONTEXT_CRITICAL

        LOAD_CSSR0_CSSR1

        e_bl        _ivor12_callback    /* Branch to the proper callback */

        RESTORE_CONTEXT_CRITICAL

        se_rfci
#endif

        /*
         * _IVOR13 handler (Data TLB Error Interrupt Exception).
         */
#if IVOR13_HANDLER
        .align      4
        .globl      _IVOR13
        .type       _IVOR13, @function
_IVOR13:
        SAVE_CONTEXT

        LOAD_SSR0_SSR1_PLUS

        e_bl        _ivor13_callback    /* Branch to the proper callback */

        RESTORE_CONTEXT
        se_rfi
#endif

        /*
         * _IVOR14 handler (Instruction TLB Error Interrupt Exception).
         */
#if IVOR14_HANDLER
        .align      4
        .globl      _IVOR14
        .type       _IVOR14, @function
_IVOR14:
        SAVE_CONTEXT

        LOAD_SSR0_SSR1_PLUS

        e_bl        _ivor14_callback    /* Branch to the proper callback */

        RESTORE_CONTEXT
        se_rfi
#endif

        /*
         * _IVOR15 handler (Debug Interrupt Exception).
         */
#if IVOR15_HANDLER
        .align      4
        .globl      _IVOR15
        .type       _IVOR15, @function
_IVOR15:
        SAVE_CONTEXT_CRITICAL

        LOAD_CSSR0_CSSR1

        e_bl        _ivor15_callback    /* Branch to the proper callback */

        RESTORE_CONTEXT_CRITICAL

        se_rfci
#endif

#if CORE_SUPPORTS_IVORS
        .align      4
        .globl      _spr_init
        .type       _spr_init, @function
_spr_init:

        e_lis       %r3, HI(_IVOR0)
        e_or2i      %r3, LO(_IVOR0)
        mtspr       400, %r3

        e_lis       %r3, HI(_IVOR1)
        e_or2i      %r3, LO(_IVOR1)
        mtspr       401, %r3

        e_lis       %r3, HI(_IVOR2)
        e_or2i      %r3, LO(_IVOR2)
        mtspr       402, %r3

        e_lis       %r3, HI(_IVOR3)
        e_or2i      %r3, LO(_IVOR3)
        mtspr       403, %r3

        e_lis       %r3, HI(_IVOR4)
        e_or2i      %r3, LO(_IVOR4)
        mtspr       404, %r3

        e_lis       %r3, HI(_IVOR5)
        e_or2i      %r3, LO(_IVOR5)
        mtspr       405, %r3

        e_lis       %r3, HI(_IVOR6)
        e_or2i      %r3, LO(_IVOR6)
        mtspr       406, %r3

        e_lis       %r3, HI(_IVOR7)
        e_or2i      %r3, LO(_IVOR7)
        mtspr       407, %r3

        e_lis       %r3, HI(_IVOR8)
        e_or2i      %r3, LO(_IVOR8)
        mtspr       408, %r3

        e_lis       %r3, HI(_IVOR9)
        e_or2i      %r3, LO(_IVOR9)
        mtspr       409, %r3

        e_lis       %r3, HI(_IVOR10)
        e_or2i      %r3, LO(_IVOR10)
        mtspr       410, %r3

        e_lis       %r3, HI(_IVOR11)
        e_or2i      %r3, LO(_IVOR11)
        mtspr       411, %r3

        e_lis       %r3, HI(_IVOR12)
        e_or2i      %r3, LO(_IVOR12)
        mtspr       412, %r3

        e_lis       %r3, HI(_IVOR13)
        e_or2i      %r3, LO(_IVOR13)
        mtspr       413, %r3

        e_lis       %r3, HI(_IVOR14)
        e_or2i      %r3, LO(_IVOR14)
        mtspr       414, %r3

        e_lis       %r3, HI(_IVOR15)
        e_or2i      %r3, LO(_IVOR15)
        mtspr       415, %r3

        e_lis       %r3, HI(_IVOR32)
        e_or2i      %r3, LO(_IVOR32)
        mtspr       528, %r3

        e_lis       %r3, HI(_IVOR33)
        e_or2i      %r3, LO(_IVOR33)
        mtspr       529, %r3

        e_lis       %r3, HI(_IVOR34)
        e_or2i      %r3, LO(_IVOR34)
        mtspr       530, %r3

        se_blr
#endif /* CORE_SUPPORTS_IVORS */

#endif /* !defined(__DOXYGEN__) */

#endif /* OSAL_OS_ENABLE */

/** @} */
