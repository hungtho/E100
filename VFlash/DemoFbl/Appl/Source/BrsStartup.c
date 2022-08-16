
/**********************************************************************************************************************
  COPYRIGHT
-----------------------------------------------------------------------------------------------------------------------
  \par      copyright
  \verbatim
  Copyright (c) 2018 by Vector Informatik GmbH.                                                  All rights reserved.

                This software is copyright protected and proprietary to Vector Informatik GmbH.
                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
                All other rights remain with Vector Informatik GmbH.
  \endverbatim
-----------------------------------------------------------------------------------------------------------------------
  FILE DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
  \file  File:  BrsStartup.c
      Project:  Vector Basic Runtime System
       Module:  BrsHw for platform Freescale/ST Mpc57xx

  \brief Description:  This file contains the StartUpCode.

  \attention Please note:
    The demo and example programs only show special aspects of the software. With regard to the fact
    that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
    expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
**********************************************************************************************************************/

/**********************************************************************************************************************
  AUTHOR IDENTITY
 ----------------------------------------------------------------------------------------------------------------------
  Name                          Initials      Company
  ----------------------------  ------------  -------------------------------------------------------------------------
  Benjamin Walter               visbwa        Vector Informatik GmbH
  Stefan Schorer                vissns        Vector Informatik GmbH
  Timo Mueller                  vistir        Vector Informatik GmbH
  Andreas Hahn                  vishan        Vector Informatik GmbH
  Steffen Frank                 visfsn        Vector Informatik GmbH
  Wolfgang Lienhart             viswlt        Vector Informatik GmbH
  Bjoern Eisenkrammer           visebj        Vector Informatik GmbH
  Sascha Mauser                 vismaa        Vector Informatik GmbH
  Maximilian Hempe              virmnh        Vector Informatik GmbH
  Ivo Georgiev                  visivg        Vector Informatik GmbH
  Muhammad Suliman              vismun        Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
 ----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Description
  --------  ----------  ------  ---------------------------------------------------------------------------------------
  01.00.00  2015-05-05  vissns  New creation, based on zBrs_Mpc@root[3.09.04],
                                according to template for BrsHw Codestyle 2.0
            2015-07-20  visbwa  Review
  01.00.01  2015-08-12  vistir  Added support or BRSHW_INTERRUPT_TABLE_GROUP_G
  01.00.02  2015-09-07  visbwa  Added symbol _start_c1 for 2nd Core startup (experimental status)
  01.00.03  2015-09-25  vishan  Added multicore OS support (startup, stacks)
                                Hold slave cores in single core use case
                                Disabled Watchdog
  01.00.04  2015-09-29  visfsn  Added MPC5746B
  01.00.05  2015-10-08  vishan  Added BRS_CPU_STARTUP_ID check
  01.00.06  2015-10-12  visbwa  Fixed BRS_CPU_STARTUP_ID check
  01.00.07  2015-12-10  visbwa  Added RCHW of SPC574Kxx and SPC574Sx
  01.00.08  2016-02-18  viswlt  Fixed GNU support @ VLE
  01.00.09  2016-03-31  visbwa  Renamed foreverloop for unintended Core blocking within MultiCore support
  01.00.10  2016-07-01  visbwa  Sample code hint added, to fit with Brs_Template 2.00.02
  01.01.00  2016-07-12  visbwa  Added usage of variable _RAM_START_ADDR within INIT RAM section
  01.01.01  2016-07-28  visebj  Fixed RCHW of SPC574Kxx and introduced BRSHW_RCHW_GROUP_A and _B
  01.01.02  2016-10-21  vismaa  Fixed support for PC582101/Quasar2e
  01.01.03  2017-02-07  visbwa  Fixed BRSASR_ENABLE_MULTICORESUPPORT into proper BRSASR_ENABLE_OS_MULTICORESUPPORT,
                                fixed start symbols for StartUpCore=1
  01.01.04  2017-02-07  virmnh  Changes StackPointer initialization for Multicore UseCase (removed usage of r3)
  01.01.05  2017-03-14  visbwa  Fixed BRSASR_ENABLE_MULTICORESUPPORT to proper BRSASR_ENABLE_OS_MULTICORESUPPORT
  01.01.06  2017-08-11  vismaa  Added Resetword for BRS_CPU_STARTUP_ID = 1
  01.02.00  2017-08-28  visivg  Adapted file for GnuGCC support, deleted unused address parameters,
                                fixed SDA and SP initialization for GNU compilers
  01.02.01  2017-12-12  vismaa  Added _VECTORTABLE_START_ADDR symbol for IVPR init
  01.02.02  2018-02-14  vismun  Moved assembler command redefinition to BrsHw.h
  01.02.03  2018-03-22  vismaa  Added ".global _start" for HIGHTEC and GNUGCC compiler
  01.02.04  2018-04-04  visbwa  Added dummy jump to intvect_CoreExceptions_used (-Xremove-unused-sections)
  01.02.05  2018-04-10  vismaa  Added flags for resetword (HIGHTEC, GNUGCC)
**********************************************************************************************************************/

/**********************************************************************************************************************
*  EXAMPLE CODE ONLY
*  -------------------------------------------------------------------------------------------------------------------
*  This Example Code is only intended for illustrating an example of a possible BSW integration and BSW configuration.
*  The Example Code has not passed any quality control measures and may be incomplete. The Example Code is neither
*  intended nor qualified for use in series production. The Example Code as well as any of its modifications and/or
*  implementations must be tested with diligent care and must comply with all quality requirements which are necessary
*  according to the state of the art before their use.
*********************************************************************************************************************/

/* FILE structure:
 * (A) COMPILER ABSTRACTION
 * (B) COMPILER SPECIFIC START OF CODE
 * (C) DERIVATIVE SPECIFIC PREPARATION
 * (D) INIT RAM
 * (E) COPY INITIALIZED DATA FROM FLASH TO RAM
 * (F) INIT INTERRUPT VECTOR BASE REGISTER
 * (G) COMPILER SPECIFIC INIT
 * (H) CALL MAIN
 * (I) SET RESET WORD (entry point after HW reset)
 * (J) COMPILER SPECIFIC END OF CODE
 * (K) END OF FILE (everything below will be deleted later!)
 */

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
/*
 * Description: The BrsHw header provides all the necessary interfaces to
 *              the microcontroller hardware features like ports, timers, LEDs, ...
 */
#include "BrsHw.h"

/*****************************************************************************
 * COMPILER SPECIFIC START OF CODE
 *****************************************************************************/

#if defined (BRS_COMP_GHS)
# if defined(__ALTIVEC__) || defined(__SPE__)
    #define StackOff       16
    #define StackOffLog2   4
# else
#   define StackOff       8
#   define StackOffLog2   3
# endif
# pragma asm
  #if defined (BRSHW_INSTRUCTION_SET_VLE)
  .vle
  #endif
  .global _start
# if defined (BRSASR_ENABLE_OS_MULTICORESUPPORT)
  .global _start_c0
  .global _start_c1
  .global _start_c2
# endif
  .section ".startup", "vax"
#endif /*BRS_COMP_GHS*/

___asm(_start:)
___asm(__start:)
#if !defined (BRS_CPU_STARTUP_ID)
  #error "Please set CPU_STARTUP_ID for your Derivative in Makefile.derivative.settings!"
#endif
#if defined (BRSASR_ENABLE_OS_MULTICORESUPPORT)
# if (BRS_CPU_STARTUP_ID == 0)
___asm(_start_c0:)
___asm(__start_c0:)

# elif (BRS_CPU_STARTUP_ID == 1)
___asm(_start_c1:)
___asm(__start_c1:)

# elif (BRS_CPU_STARTUP_ID == 2)
___asm(_start_c2:)
___asm(__start_c2:)
# else
  #error "The configured CPU_STARTUP_ID is not yet supported by this StartUpCode."
# endif /*BRS_CPU_STARTUP_ID*/ 
#endif /*BRSASR_ENABLE_OS_MULTICORESUPPORT*/

___asm(;/*****************************************************************************/)
___asm(;/* (C) DERIVATIVE SPECIFIC PREPARATION                                       */)
___asm(;/*****************************************************************************/)
#if defined(BRS_DERIVATIVE_MPC5746M)
___asm(;/* currently it seems that only CPU2 must be used for communication */)
___asm(;/* disable watchdog and do some other stuff */)
__as1(e_lis      r4,0xFC058000@h)
__as1(e_or2i     r4, 0xFC058000@l)
__as1(e_li       r3, 0xC520)
__as1(e_stw      r3, 0x10(r4))
__as1(e_li       r3, 0xD928)
__as1(e_stw      r3, 0x10(r4))
__as1(e_lis      r3, 0xFF00010A@h)
__as1(e_or2i     r3, 0xFF00010A@l)
__as1(e_stw      r3, 0(r4))
__as1(e_lis      r4, 0xFC054000@h)
__as1(e_or2i     r4, 0xFC054000@l)
__as1(e_li       r3, 0xC520)
__as1(e_stw      r3, 0x10(r4))
__as1(e_li       r3, 0xD928)
__as1(e_stw      r3, 0x10(r4))
__as1(e_lis      r3, 0xFF00010A@h)
__as1(e_or2i     r3, 0xFF00010A@l)
__as1(e_stw      r3, 0(r4))
__as1(e_lis      r4, 0xFC050000@h)
__as1(e_or2i     r4, 0xFC050000@l)
__as1(e_li       r3, 0xC520)
__as1(e_stw      r3, 0x10(r4))
__as1(e_li       r3, 0xD928)
__as1(e_stw      r3, 0x10(r4))
__as1(e_lis      r3, 0xFF00010A@h)
__as1(e_or2i     r3, 0xFF00010A@l)
__as1(e_stw      r3, 0(r4))
#endif

#if defined (BRSASR_ENABLE_OS_MULTICORESUPPORT)
# if (BRS_CPU_STARTUP_ID == 0)
___asm(_start_c1:)
___asm(__start_c1:)
___asm(_start_c2:)
___asm(__start_c2:)

# elif (BRS_CPU_STARTUP_ID == 1)
___asm(_start_c0:)
___asm(__start_c0:)
___asm(_start_c2:)
___asm(__start_c2:)

# elif (BRS_CPU_STARTUP_ID == 2)
___asm(_start_c0:)
___asm(__start_c0:)
___asm(_start_c1:)
___asm(__start_c1:)
# endif /*BRS_CPU_STARTUP_ID*/

#else /*BRSASR_ENABLE_OS_MULTICORESUPPORT*/
___asm(;/* catch and hold slave cores in case of unintended startup */)
__as1(mfspr     r3, PIR;               /* read out CPU ID PIR */)
__as1(se_cmpi   r3, BRS_CPU_STARTUP_ID;/* if current CPU is startup core? */)
___asm(se_beq   _startupCorrectCore;   /* proceed for correct/intended Core with section D (INIT) */)
___asm(_blockUnintendedSlaveCore:)
___asm(e_bl _blockUnintendedSlaveCore; /* hold unintended slave cores */)
___asm(_startupCorrectCore:)
#endif /*BRSASR_ENABLE_OS_MULTICORESUPPORT*/

___asm(;/*****************************************************************************/)
___asm(;/* (D) INIT RAM                                                              */)
___asm(;/*****************************************************************************/)
__as1(e_lis  r11, _RAM_START_ADDR@h;       /* highbytes - r11 holds start address of the RAM */)
#if defined (BRSHW_INSTRUCTION_SET_VLE)
  __as1(e_or2i  r11, _RAM_START_ADDR@l;    /* lowbytes  - r11 holds start address of the RAM */)
#else
  __as2(e_ori  r11,r11, _RAM_START_ADDR@l; /* lowbytes  - r11 holds start address of the RAM */)
#endif
__as1(e_lis  r16,0x0000  ;/* init pattern */)
__as1(e_lis  r17,0x0000  ;/* init pattern */)
__as1(e_lis  r18,0x0000  ;/* init pattern */)
__as1(e_lis  r19,0x0000  ;/* init pattern */)
__as1(e_lis  r20,0x0000  ;/* init pattern */)
__as1(e_lis  r21,0x0000  ;/* init pattern */)
__as1(e_lis  r22,0x0000  ;/* init pattern */)
__as1(e_lis  r23,0x0000  ;/* init pattern */)
__as1(e_lis  r24,0x0000  ;/* init pattern */)
__as1(e_lis  r25,0x0000  ;/* init pattern */)
__as1(e_lis  r26,0x0000  ;/* init pattern */)
__as1(e_lis  r27,0x0000  ;/* init pattern */)
__as1(e_lis  r28,0x0000  ;/* init pattern */)
__as1(e_lis  r29,0x0000  ;/* init pattern */)
__as1(e_lis  r30,0x0000  ;/* init pattern */)
__as1(e_lis  r31,0x0000  ;/* init pattern */)

#if defined(BRSASR_ENABLE_OS_MULTICORESUPPORT)
___asm(;/* skip RAM init for slave cores */)
__as1(mfspr     r3, PIR         ;/* read out CPU ID PIR                 */)
__as1(se_cmpi   r3, BRS_CPU_STARTUP_ID     ;/* if current CPU is NOT startup core?   */)
___asm(se_bne   _startupF       ;/* proceed with section F              */)
#endif

___asm(_init_l2ram:)
__as1(e_li r12,BRSHW_CPU_MAX_RAM)
__as2(e_slwi r12,r12,4;/* *r12 = *r12<<4 (Standard Singlecore implementation)*/)
___asm(;/*__as2(e_slwi r12,r12,3) -> Dualcore bugfix! */)

___asm(mtctr r12 ;/* set IP to r12*/)

___asm(_init_l2ram_loop:)
__as1(e_stmw    r16,0(r11))
__as2(e_addi    r11,r11,64)
___asm(;/* if you get a reset here try to use the "Dualcore bugfix" instead of the "Standard Singlecore implementation" above */)
___asm(e_bdnz    _init_l2ram_loop)

___asm(;/*****************************************************************************/)
___asm(;/* (E) COPY INITIALIZED DATA FROM FLASH TO RAM                               */)
___asm(;/*****************************************************************************/)
__as1(e_li r5, 0 ;/* Clear r5 */)
__as1(e_lis     r5, RC_SDATA_SIZE@h;)
#if defined (BRSHW_INSTRUCTION_SET_VLE)
  __as1(e_or2i    r5, RC_SDATA_SIZE@l;)
#else
  __as2(e_ori    r5,r5, RC_SDATA_SIZE@l;)
#endif
__as2(or.       r5, r5, r5;)
___asm(e_beq     data_copy2;)
___asm(se_mtctr  r5;)
__as1(e_lis     r8, RC_SDATA_SRC@h;)
#if defined (BRSHW_INSTRUCTION_SET_VLE)
  __as1(e_or2i    r8, RC_SDATA_SRC@l;)
#else
  __as2(e_ori    r8,r8, RC_SDATA_SRC@l;)
#endif
__as2(e_subi    r8,r8,4;)
__as1(e_lis     r9, RC_SDATA_DEST@h;)
#if defined (BRSHW_INSTRUCTION_SET_VLE)
  __as1(e_or2i    r9, RC_SDATA_DEST@l;)
#else
  __as2(e_ori    r9,r9, RC_SDATA_DEST@l;)
#endif
__as2(e_subi    r9,r9,4;)
___asm(data_copy_loop2:)
__as1(e_lwzu    r10,4(r8);)
__as1(e_stwu    r10,4(r9);)
___asm(e_bdnz    data_copy_loop2;)
___asm(data_copy2:)

___asm(;/*****************************************************************************/)
___asm(;/* (F) INIT INTERRUPT VECTOR BASE REGISTER                                   */)
___asm(;/*****************************************************************************/)
#if defined(BRSASR_ENABLE_OS_MULTICORESUPPORT)
___asm(_startupF:)
#endif

  __as1(e_li     r0, 0        ;/* Clear r0 */)
#if !defined (BRS_DERIVATIVE_PC582101)
  __as1(e_lis    r0,_VECTORTABLE_START_ADDR@h    ;/* r11 holds base address of the L2SRAM 64-bit word aligned*/)
# if defined (BRSHW_INSTRUCTION_SET_VLE)
  __as1(e_or2i    r0,_VECTORTABLE_START_ADDR@l ;)
# else
  __as2(e_ori    r0,r0,_VECTORTABLE_START_ADDR@l;)
# endif
#endif
  __as1(mtspr    63, r0       ;/* set IVPR */)

___asm(;/*****************************************************************************/)
___asm(;/* (G) COMPILER SPECIFIC INIT                                                */)
___asm(;/*****************************************************************************/)
#if defined (BRSASR_ENABLE_OS_MULTICORESUPPORT)
___asm(.extern  oskStackTop_SYS_c0)
___asm(.extern  oskStackTop_SYS_c1)
___asm(.extern  oskStackTop_SYS_c2)
___asm(;/* init core specific stack pointers            */)
__as1(mfspr      r3, PIR      ;/* read out CPU ID PIR   */)
__as1(se_cmpi    r3, 0        ;/* is current CPU core0? */)
___asm(se_beq    _startupG_c0 ;/* init core0            */)
__as1(se_cmpi    r3, 1        ;/* is current CPU core1? */)
___asm(se_beq    _startupG_c1 ;/* init core1            */)
__as1(se_cmpi    r3, 2        ;/* is current CPU core2? */)
___asm(se_beq    _startupG_c2 ;/* init core2            */)
___asm(;/*init core0                                    */)
___asm(_startupG_c0:)
__as1(e_lis       sp,%hiadj(oskStackTop_SYS_c0);          )
__as2(e_add16i    sp,sp,%lo(oskStackTop_SYS_c0);/* sp = oskStackTop_SYS_c0 - update compared to initial*/)
___asm(se_b      _startupG    ;/* skip other cases      */)
___asm(;/*init core1                                    */)
___asm(_startupG_c1:)
__as1(e_lis       sp,%hiadj(oskStackTop_SYS_c1);          )
__as2(e_add16i    sp,sp,%lo(oskStackTop_SYS_c1);/* sp = oskStackTop_SYS_c0 - update compared to initial*/)
___asm(se_b      _startupG    ;/* skip other cases      */)
___asm(;/*init core2                                    */)
___asm(_startupG_c2:)
__as1(e_lis       sp,%hiadj(oskStackTop_SYS_c2);          )
__as2(e_add16i    sp,sp,%lo(oskStackTop_SYS_c2);/* sp = oskStackTop_SYS_c2 - update compared to initial*/)
___asm(;/*core specific section G finished              */)
___asm(_startupG:)
# if defined (BRS_COMP_GHS)
  __as1(e_lis       r13,%hiadj(_SDA_BASE_);/* Initialize SDA (short data access for RAM) base register - value provided by linker*/)
  __as2(e_add16i    r13,r13,%lo(_SDA_BASE_); )
  __as1(e_lis       r2,%hiadj(_SDA2_BASE_);/* Initialize SDA2 (short data access for ROM) base register - value provided by linker*/)
  __as2(e_add16i    r2,r2,%lo(_SDA2_BASE_); )
# endif

#else /*BRSASR_ENABLE_OS_MULTICORESUPPORT*/
# if defined (BRS_COMP_GHS)
  __as1(e_lis       sp,%hiadj(__ghs_stackend-StackOff)  ;/* Initialize stack pointer (r11) - value defined in linker command file*/)
  __as2(e_add16i    sp,sp,%lo(__ghs_stackend-StackOff)  ; )
  __as1(e_lis       r13,%hiadj(_SDA_BASE_)              ;/* Initialize SDA (short data access for RAM) base register - value provided by linker*/)
  __as2(e_add16i    r13,r13,%lo(_SDA_BASE_)             ; )
  __as1(e_lis       r2,%hiadj(_SDA2_BASE_)              ;/* Initialize SDA2 (short data access for ROM) base register - value provided by linker*/)
  __as2(e_add16i    r2,r2,%lo(_SDA2_BASE_)              ; )
# endif

#endif /*BRSASR_ENABLE_OS_MULTICORESUPPORT*/

___asm(;/*****************************************************************************/)
___asm(;/* (H) CALL MAIN                                                             */)
___asm(;/*****************************************************************************/)
  ___asm(e_bl main; /*call main*/)

___asm(;/*****************************************************************************/)
___asm(;/* (I) SET RESET WORD (entry point after HW reset)                           */)
___asm(;/*****************************************************************************/)

#if defined (BRS_COMP_GHS)
# if defined (BRSHW_INSTRUCTION_SET_VLE)
  ___asm(.vle)
# endif
  __as1(.section ".resetword","vax")
#endif

#if defined (BRSHW_RCHW_GROUP_A)
  ___asm(;/*  # boot header (0x005A) with Boot CPU selection: */)
  ___asm(;/*  # Bit28 (0x08): CPU_1 (if not available: Reserved for future use) */)
  ___asm(;/*  # Bit29 (0x04): CPU_C (if not available: Reserved for future use) */)
  ___asm(;/*  # Bit30 (0x02): CPU_0 (if not available: Reserved for future use) */)
  ___asm(;/*  # Bit31 (0x01): CPU_2 (if not available: Reserved for future use) */)
# if (BRS_CPU_STARTUP_ID == 2)
  ___asm(.long 0x005A0001; /* Start from Core 2 */)
# elif (BRS_CPU_STARTUP_ID == 1)
  ___asm(.long 0x005A0008; /* Start from Core 1 */)
# elif (BRS_CPU_STARTUP_ID == 0)
  ___asm(.long 0x005A0002; /* Start from Core 0 */)
# endif
# if defined (BRSASR_ENABLE_OS_MULTICORESUPPORT)
  ___asm(;/*  # CPU_2 reset vector (if not available: Reserved for future use) */)
  ___asm(.long _start_c2)
  ___asm(;/*  # configuration bits */)
  ___asm(.long 0xAFFEAFFE)
  ___asm(.long 0xAFFEAFFE)
  ___asm(;/*  # CPU_0 reset vector (if not available: Reserved for future use) */)
  ___asm(.long _start_c0)
  ___asm(;/*  # CPU_1 reset vector (if not available: Reserved for future use) */)
  ___asm(.long _start_c1)
  ___asm(;/*  # CPU_C reset vector (checker core) (if not available: Reserved for future use) */)
  ___asm(.long 0x00000000)

# else
  ___asm(;/*  # CPU_2 reset vector (if not available: Reserved for future use) */)
  ___asm(.long __start)
  ___asm(;/*  # configuration bits */)
  ___asm(.long 0xAFFEAFFE)
  ___asm(.long 0xAFFEAFFE)
  ___asm(;/*  # CPU_0 reset vector (if not available: Reserved for future use) */)
  ___asm(.long __start)
  ___asm(;/*  # CPU_1 reset vector (if not available: Reserved for future use) */)
  ___asm(.long __start)
  ___asm(;/*  # CPU_C reset vector (checker core) (if not available: Reserved for future use) */)
  ___asm(.long 0x00000000)
# endif /*else BRSASR_ENABLE_OS_MULTICORESUPPORT*/
#else
# if defined (BRSHW_RCHW_GROUP_B)
  ___asm(.long 0x005A0000;/* Reset configuration half word*/)

# else
#  if defined (BRSHW_INSTRUCTION_SET_VLE)
#   if defined (BRSHW_WATCHDOG_GROUP_A)
  ___asm(.long 0x095A0000;/* Reset configuration half word with VLE*/)
#   else
  ___asm(.long 0x015A0000;/* Reset configuration half word with VLE*/)
#   endif

#  else
#   if defined (BRSHW_WATCHDOG_GROUP_A)
  ___asm(.long 0x085A0000;/* Reset configuration half word*/)
#   else
  ___asm(.long 0x005A0000;/* Reset configuration half word*/)
#   endif
#  endif

# endif /*else BRSHW_RCHW_GROUP_B*/
  ___asm(.long _start    ;/* Start address of startup code*/)
#endif /*else BRSHW_RCHW_GROUP_A*/

___asm(;/*****************************************************************************/)
___asm(;/* (J) COMPILER SPECIFIC END OF CODE                                         */)
___asm(;/*****************************************************************************/)
#if defined (BRS_COMP_GHS)
# if defined (__ELF)
  ___asm(.fsize  StackOff)
  ___asm(.scall  __dotsyscall)
  ___asm(.scall  __ghs_ind_crt0)
  __as1(.type   _start,@function)
  __as1(.section ".secinfo","a")
# else
  __as1(.section ".secinfo",.text)
# endif
  #pragma endasm
#endif /*BRS_COMP_GHS*/

/*****************************************************************************
 * (K) END OF FILE (everything below will be deleted later!)
 *****************************************************************************/
