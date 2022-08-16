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
* EVALUATION ONLY - NOT FOR USE IN PRODUCTION
*****************************************************************************/
/**
 * @file    crt0.s
 * @brief   Generic PowerPC startup file for GCC.
 *
 * @addtogroup PPC_STARTUP
 * @{
 */

#include "boot.h"
#include "toolchain.h"

#ifndef __CACHE_INIT
/* Caches not enabled or not present
 * Nop instruction.
 */
#define __CACHE_INIT	e_ori 0, 0, 0
#endif

#if !defined(__DOXYGEN__)

        .section    .crt0, "axv"
        .align		2
        .globl      _boot_address
        .type       _boot_address, @function
_VLE
_boot_address:
        /*
         * Stack setup.
         */
		e_lis       %r1, HI(__process_stack_end__)
        e_or2i      %r1, LO(__process_stack_end__)
        se_li       %r0, 0
        e_stwu      %r0, -8(%r1)
        /*
         * Small sections registers initialization.
         */
        e_lis       %r2,  HI(__sdata2_start__)
        e_or2i      %r2,  LO(__sdata2_start__)
        e_lis       %r13, HI(__sdata_start__)
        e_or2i      %r13, LO(__sdata_start__)
		/* 
		 * Cache initialization.
		 */
		__CACHE_INIT
        /*
         * Early initialization.
         */
        e_bl        __early_init
        /*
         * BSS clearing.
         */
        e_lis       %r4, HI(__bss_start__)
        e_or2i      %r4, LO(__bss_start__)
        e_lis       %r5, HI(__bss_end__)
        e_or2i      %r5, LO(__bss_end__)
        se_li       %r7, 0
.bssloop:
        cmpl        cr0, %r4, %r5
        se_bge      .bssend
        se_stw      %r7, 0(%r4)
        se_addi     %r4, 4
        se_b        .bssloop
.bssend:

#if !BOOT_LOAD_IN_RAM
        /*
         * DATA initialization.
         */
        e_lis       %r4, HI(__romdata_start__)
        e_or2i      %r4, LO(__romdata_start__)
        e_lis       %r5, HI(__data_start__)
        e_or2i      %r5, LO(__data_start__)
        e_lis       %r6, HI(__data_end__)
        e_or2i      %r6, LO(__data_end__)
.dataloop:
        cmpl        cr0, %r5, %r6
        se_bge      .dataend
        se_lwz      %r7, 0(%r4)
        se_addi     %r4, 4
        se_stw      %r7, 0(%r5)
        se_addi     %r5, 4
        se_b        .dataloop
.dataend:
#endif

        /*
         * Late initialization.
         */
        e_bl        __late_init
        /*
         * Main program invocation.
         */
        e_bl        main
        e_b         _main_exit_handler

        /*
         * Default main exit code, infinite loop.
         */
        .weak       _main_exit_handler
        .globl      _main_exit_handler
        .type       _main_exit_handler, @function
_main_exit_handler:
        e_b         _main_exit_handler

        /*
         * Default early initialization code, none.
         */
        .weak       __early_init
        .globl      __early_init
        .type       __early_init, @function
__early_init:
        se_blr

        /*
         * Default late initialization code, none.
         */
        .weak       __late_init
        .globl      __late_init
        .type       __late_init, @function
__late_init:
        se_blr

        /*
         * __eabi code, fix for freegcc 4.9.4.
         */
        .weak       __eabi
        .globl      __eabi
        .type       __eabi, @function
__eabi:
        se_blr

#if BOOT_CORE0
        .align		4
        .globl      _boot_address0
        .type       _boot_address0, @function
_VLE
_boot_address0:
        /*
         * Stack setup.
         */
		e_lis       %r1, HI(__core0_process_stack_end__)
        e_or2i      %r1, LO(__core0_process_stack_end__)
        se_li       %r0, 0
        e_stwu      %r0, -8(%r1)
        /*
         * Small sections registers initialization.
         */
        e_lis       %r2,  HI(__sdata2_start__)
        e_or2i      %r2,  LO(__sdata2_start__)
        e_lis       %r13, HI(__sdata_start__)
        e_or2i      %r13, LO(__sdata_start__)

        /*
         * Main program invocation.
         */
        e_bl        main_core0
#endif

#if BOOT_COREZ0
        .align		4
        .globl      _boot_address_z0
        .type       _boot_address_z0, @function
_VLE
_boot_address_z0:
        /*
         * Stack setup.
         */
		e_lis       %r1, HI(__core_z0_process_stack_end__)
        e_or2i      %r1, LO(__core_z0_process_stack_end__)
        se_li       %r0, 0
        e_stwu      %r0, -8(%r1)
        /*
         * Small sections registers initialization.
         */
        e_lis       %r2,  HI(__sdata2_start__)
        e_or2i      %r2,  LO(__sdata2_start__)
        e_lis       %r13, HI(__sdata_start__)
        e_or2i      %r13, LO(__sdata_start__)

        /*
         * Main program invocation.
         */
        e_bl        main_core_z0
#endif

#if BOOT_CORE1
        .align		4
        .globl      _boot_address1
        .type       _boot_address1, @function
_VLE
_boot_address1:
        /*
         * Stack setup.
         */
		e_lis       %r1, HI(__core1_process_stack_end__)
        e_or2i      %r1, LO(__core1_process_stack_end__)
        se_li       %r0, 0
        e_stwu      %r0, -8(%r1)
        /*
         * Small sections registers initialization.
         */
        e_lis       %r2,  HI(__sdata2_start__)
        e_or2i      %r2,  LO(__sdata2_start__)
        e_lis       %r13, HI(__sdata_start__)
        e_or2i      %r13, LO(__sdata_start__)

        /*
         * Main program invocation.
         */
        e_bl        main_core1
#endif

#endif /* !defined(__DOXYGEN__) */

/** @} */
