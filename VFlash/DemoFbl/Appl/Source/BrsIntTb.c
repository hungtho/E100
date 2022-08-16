
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
  \file  File:  BrsIntTb.c
      Project:  Vector Basic Runtime System
       Module:  BrsHw for platform Freescale/ST Mpc57xx

  \brief Description:  This file consists of the Interrupt Vector Table.

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
  Andreas Hahn                  vishan        Vector Informatik GmbH
  Timo Mueller                  vistir        Vector Informatik GmbH
  Nguyen Le                     vislnn        Vector Informatik GmbH
  Ivo Georgiev                  visivg        Vector Informatik GmbH
  Sascha Mauser                 vismaa        Vector Informatik GmbH
  Muhammad Suliman              vismun        Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
 ----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Description
  --------  ----------  ------  ---------------------------------------------------------------------------------------
  01.00.00  2015-05-06  vissns  New creation, based on zBrs_Mpc@root[3.09.04],
                                according to template for BrsHw Codestyle 2.0
            2015-07-09  vishan  Reworked Flexcan single irq mapping for BRSHW_INTERRUPT_TABLE_GROUP_D
            2015-07-20  visbwa  Review
  01.00.01  2015-08-12  vistir  Added support for MPC5746R
  01.00.02  2015-12-09  vislnn  Added MCAN0_LINE0_Interrupt
  01.00.03  2016-03-23  visbwa  Added 3rd Can channel ISRs for BRSHW_INTERRUPT_TABLE_GROUP_D
  01.00.04  2016-07-01  visbwa  Sample code hint added, to fit with Brs_Template 2.00.02
  01.00.05  2017-06-16  visivg  Fixed support for SPC574Sx
  01.00.06  2017-08-14  visivg  Added Wakeup-ISR
  01.01.00  2017-09-06  visivg  Added GnuGcc support and software dispatching for BRS_DERIVATIVE_MPC5748G,
                                added support for Hardware Vector Mode for GNU compilers
  01.01.08  2017-11-15  vismaa  Added support for usage of 2 CAN cells in parallel (additional ISRs for MCAN)
  01.01.09  2017-11-21  visbwa  Added support for new DrvMCan defines within BRSHW_INTERRUPT_TABLE_GROUP_C,
                                re-ordered BRSHW_INTERRUPT_TABLE_GROUP_x encapsulation for readability,
                                added configuration check for MCAN configuration
  01.02.00  2018-02-14  vismun  Introduced ISR_HANDLER_DEFINITION() to simplify interrupt handler implementation,
                                moved assembler command redefinition to BrsHw.h
  01.02.01  2018-03-08  visbwa  Fixed encapsulation for UseCase GHS (within asm pragmas no '\' allowed)
  01.03.00  2018-03-21  vismaa  Added Support for FBL according to Brs_Template 2.02.01,
                                deleted BrsHwAlignmentErrorInterrupt (replaced by BrsHw_core_exception_handler),
                                fix for GHS compiler (ISR_HANDLER_DEFINITION, pragma asm/endasm)
  01.03.01  2018-04-04  visbwa  Fixed include of Can_30_Mcan.h,
                                added usaeg of ISR_HANDLER_DEFINITION for BrsHwTimeBaseInterrupt,
                                added intvect_CoreExceptions_used (-Xremove-unused-sections)
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

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
/*
 * Description: The BrsHw header provides all the necessary interfaces to
 *              the microcontroller hardware features like ports, timers, LEDs, ...
 */
#include "BrsHw.h"

#if defined (VGEN_ENABLE_CAN_DRV)
# if defined (VGEN_ENABLE_IF_ASRIFCAN)
  /*Autosar component*/
#  if defined (BRSHW_USED_CANCELL_DEFAULT)
  /* #include "Can.h" */
#  endif
#  if defined (BRSHW_USED_CANCELL_MCAN)
  #include "Can_30_Mcan.h"
#   if !defined (kCan_30_McanPhysToLogChannelIndex_0) && !defined (kCan_30_McanPhysToLogChannelIndex_1)
  #error "Could not detect DrvMCan channel configuration automatically. Please define here manually, which channel is used within your configuration."*/
  /*#define kCan_30_McanPhysToLogChannelIndex_0*/
  /*#define kCan_30_McanPhysToLogChannelIndex_1*/
#   endif
#  endif
# else
  /*CANbedded component*/
  #include "can_inc.h"
# endif
#endif

#if defined (VGEN_ENABLE_LIN_DRV)
# if defined (VGEN_ENABLE_IF_ASRIFLIN)
  /*Autosar component*/
  #include "Lin.h"
# else
  /*CANbedded component*/
  #include "lin_api.h"
  #include "sio_par.h"
# endif
#endif

#if defined (VGEN_ENABLE_DRVFR__BASEASR)
  #include "Fr.h"
#endif

#if defined (VGEN_ENABLE_DRVETH__BASEASR)
  #include "Eth.h"
#endif

#if defined (BRS_OS_USECASE_BRS) && !defined (BRS_ENABLE_FBL_SUPPORT)
  /* All ISR function definitions are set within this separate header */
  #include "BrsHw_IsrDef.h"
#endif

/**********************************************************************************************************************
  VERSION CHECK
**********************************************************************************************************************/
/* No header, therefore no version check */

/**********************************************************************************************************************
  CONFIGURATION CHECK
**********************************************************************************************************************/
#if defined (VGEN_ENABLE_CAN_DRV)
# if defined (VGEN_ENABLE_IF_ASRIFCAN)
  /* Autosar is similar to RI1.5 (BRS view) */
# else
#  if !defined (C_VERSION_REF_IMPLEMENTATION) || (C_VERSION_REF_IMPLEMENTATION < 0x150u)
  /* defines necessary for DrvCan's <RI1.5 */
  #error "The Channel assignment is unclear. Please set used channels manually!"
#  endif
# endif
#endif /*VGEN_ENABLE_CAN_DRV*/

#if defined (BRS_ENABLE_FBL_SUPPORT)
# if defined (BRS_COMP_GHS)
  #pragma asm
# endif

  ___asm(.globl _start)

# if defined (BRS_COMP_GHS)
  #pragma endasm
# endif

  #define _BrsHw_core_exception_handler _start
  #define __isr_handler _start

  /*Interrupt alignment definition is included within BrsIsrDefiniton, for FBL Support this define is set here*/ 
# if defined (BRSHW_INTERRUPT_TABLE_GROUP_B)
#  if defined(BRS_COMP_GHS) 
  #define INTERRUPT_ALIGNMENT 2
#  endif
# else
#  if defined(BRS_COMP_GHS) 
  #define INTERRUPT_ALIGNMENT 2
#  endif
# endif
#endif /*BRS_ENABLE_FBL_SUPPORT*/

/**********************************************************************************************************************
  DEFINITION + MACROS
**********************************************************************************************************************/
/* Interrupt handler code definition */
#if defined (BRS_COMP_GHS)
#pragma asm
.macro ISR_HANDLER_DEFINITION isr_func;
  e_stwu sp, -80 (sp); /* Create stack frame and store back chain */) 
  e_stw r3, 36 (sp)  ; /* Save working register */) 
  mfsrr0 r3         ; /* Get SRR0 */) 
  e_stw r3, 12 (sp)  ; /* and save SRR0 */) 
  mfsrr1 r3         ; /* Get SRR1 */) 
  e_stw r3, 16 (sp)  ; /* and save SRR1 */) 
  wrteei 1          ; /* Set MSR[EE]=1 */) 
  mflr r3           ; /* Get LR */) 
  e_stw r3, 8 (sp)   ; /* and save LR */) 
  e_bl FinishSavingContext
  e_bl isr_func
  e_b RestoreContext
  .endm
#pragma endasm

#else
#define ISR_HANDLER_DEFINITION(isr_func) \
  __as1( e_stwu sp, -80 (sp); /* Create stack frame and store back chain */) \
  __as1( e_stw r3, 36 (sp)  ; /* Save working register */) \
  ___asm( mfsrr0 r3         ; /* Get SRR0 */) \
  __as1( e_stw r3, 12 (sp)  ; /* and save SRR0 */) \
  ___asm( mfsrr1 r3         ; /* Get SRR1 */) \
  __as1( e_stw r3, 16 (sp)  ; /* and save SRR1 */) \
  ___asm( wrteei 1          ; /* Set MSR[EE]=1 */) \
  ___asm( mflr r3           ; /* Get LR */) \
  __as1( e_stw r3, 8 (sp)   ; /* and save LR */) \
  ___asm( e_bl FinishSavingContext) \
  ___asm( e_bl isr_func) \
  ___asm( e_b RestoreContext)
#endif

/********************************************************************************************
 *                                                                                          *
 *                           Core Exceptions Table                                          *
 *                                                                                          *
 ********************************************************************************************/


#if defined (BRS_COMP_GHS)
  #pragma asm
# if defined (BRSHW_INSTRUCTION_SET_VLE)
  PREASM(.vle)
# endif
  __as1(.section ".intvect_CoreExceptions","vax")
#endif

#if defined (BRSHW_ENABLE_ISR_SW_DISPATCHING)
  ASM_COMMENT(/*==================================================================================*/)
  ASM_COMMENT(/* Setup handlers for core MPC5700 core exceptions                                  */)
  ASM_COMMENT(/*==================================================================================*/)
  ___asm(.align BRS_CORE_VECTOR_ALIGNMENT)
  ___asm( CI_ESR:)
  __as1(e_li r0, 0x0)
  ___asm(e_b _BrsHw_core_exception_handler)

  ___asm(.align BRS_CORE_VECTOR_ALIGNMENT)
  ___asm(MC_ESR:)
  __as1(e_li r0, 0x1)
  ___asm(e_b _BrsHw_core_exception_handler)

  ___asm(.align BRS_CORE_VECTOR_ALIGNMENT)
  ___asm(DS_ESR:)
  __as1(e_li r0, 0x2)
  ___asm(e_b _BrsHw_core_exception_handler)

  ___asm(.align BRS_CORE_VECTOR_ALIGNMENT)
  ___asm(IS_ESR:)
  __as1(e_li r0, 0x3)
  ___asm(e_b _BrsHw_core_exception_handler)

  ASM_COMMENT(/*==================================================================================*/)
  ASM_COMMENT(/* Setup software interrupt mode ISR dispatcher                                     */)
  ASM_COMMENT(/*==================================================================================*/)
  ___asm(.align BRS_CORE_VECTOR_ALIGNMENT)
  ___asm(EI_ESR:)
  ___asm(e_b __isr_handler)

  ___asm(.align BRS_CORE_VECTOR_ALIGNMENT)
  ___asm(Align_ESR:)
  __as1(e_li r0, 0x5)
  ___asm(e_b _BrsHw_core_exception_handler)

  ___asm(.align BRS_CORE_VECTOR_ALIGNMENT)
  ___asm(Program_ESR:)
  __as1(e_li r0, 0x6)
  ___asm(e_b _BrsHw_core_exception_handler)

  ___asm(.align BRS_CORE_VECTOR_ALIGNMENT)
  ___asm(FP_Unav_ESR:)
  __as1(e_li r0, 0x7)
  ___asm(e_b _BrsHw_core_exception_handler)

  ___asm(.align BRS_CORE_VECTOR_ALIGNMENT)
  ___asm(SC_ESR:)
  __as1(e_li r0, 0x8)
  ___asm(e_b _BrsHw_core_exception_handler)

  ___asm(.align BRS_CORE_VECTOR_ALIGNMENT)
  ___asm(AP_Unav_ESR:)
  __as1(e_li r0, 0x9)
  ___asm(e_b _BrsHw_core_exception_handler)

  ___asm(.align BRS_CORE_VECTOR_ALIGNMENT)
  ___asm(DEC_ESR:)
  __as1(e_li r0, 0xA)
  ___asm(e_b _BrsHw_core_exception_handler)

  ___asm(.align BRS_CORE_VECTOR_ALIGNMENT)
  ___asm(FIT_ESR:)
  __as1(e_li r0, 0xB)
  ___asm(e_b _BrsHw_core_exception_handler)

  ___asm(.align BRS_CORE_VECTOR_ALIGNMENT)
  ___asm(WDT_ESR:)
  __as1(e_li r0, 0xC)
  ___asm(e_b _BrsHw_core_exception_handler)

  ___asm(.align BRS_CORE_VECTOR_ALIGNMENT)
  ___asm(DTLB_error_ESR:)
  __as1(e_li r0, 0xD)
  ___asm(e_b _BrsHw_core_exception_handler)

  ___asm(.align BRS_CORE_VECTOR_ALIGNMENT)
  ___asm(ITLB_error_ESR:)
  __as1(e_li r0, 0xE)
  ___asm(e_b _BrsHw_core_exception_handler)

  ___asm(.align BRS_CORE_VECTOR_ALIGNMENT)
  ___asm(Debug_ESR:)
  __as1(e_li r0, 0xF)
  ___asm(e_b _BrsHw_core_exception_handler)

  ___asm(.align BRS_CORE_VECTOR_ALIGNMENT)
  ___asm(SPE_Unav_ESR:)
  __as1(e_li r0, 0x20)
  ___asm(e_b _BrsHw_core_exception_handler)

  ___asm(.align BRS_CORE_VECTOR_ALIGNMENT)
  ___asm(SPE_FPE_ESR:)
  __as1(e_li r0, 0x21)
  ___asm(e_b _BrsHw_core_exception_handler)

  ___asm(.align BRS_CORE_VECTOR_ALIGNMENT)
  ___asm(SPE_FPI_ESR:  )
  __as1(e_li r0, 0x22)
  ___asm(e_b _BrsHw_core_exception_handler)

#else /*!BRSHW_ENABLE_ISR_SW_DISPATCHING*/
  ASM_COMMENT(/*==================================================================================*/)
  ASM_COMMENT(/* Setup handlers for core MPC5700 core exceptions                                  */)
  ASM_COMMENT(/*==================================================================================*/)
  PREASM( JUMPASM _BrsHw_core_exception_handler)
  BRS_DUMMY_ISR_ALIGNMENT
  PREASM( JUMPASM _BrsHw_core_exception_handler)
  BRS_DUMMY_ISR_ALIGNMENT
  PREASM( JUMPASM _BrsHw_core_exception_handler)
  BRS_DUMMY_ISR_ALIGNMENT
  PREASM( JUMPASM _BrsHw_core_exception_handler)
  BRS_DUMMY_ISR_ALIGNMENT
  PREASM( JUMPASM _BrsHw_core_exception_handler)
  BRS_DUMMY_ISR_ALIGNMENT
  PREASM( JUMPASM _BrsHw_core_exception_handler)
  BRS_DUMMY_ISR_ALIGNMENT
  PREASM( JUMPASM _BrsHw_core_exception_handler)
  BRS_DUMMY_ISR_ALIGNMENT
  PREASM( JUMPASM _BrsHw_core_exception_handler)
  BRS_DUMMY_ISR_ALIGNMENT
  PREASM( JUMPASM _BrsHw_core_exception_handler)
  BRS_DUMMY_ISR_ALIGNMENT
  PREASM( JUMPASM _BrsHw_core_exception_handler)
  BRS_DUMMY_ISR_ALIGNMENT
  PREASM( JUMPASM _BrsHw_core_exception_handler)
  BRS_DUMMY_ISR_ALIGNMENT
  PREASM( JUMPASM _BrsHw_core_exception_handler)
  BRS_DUMMY_ISR_ALIGNMENT
  PREASM( JUMPASM _BrsHw_core_exception_handler)
  BRS_DUMMY_ISR_ALIGNMENT
  PREASM( JUMPASM _BrsHw_core_exception_handler)
  BRS_DUMMY_ISR_ALIGNMENT
  PREASM( JUMPASM _BrsHw_core_exception_handler)
  BRS_DUMMY_ISR_ALIGNMENT
  PREASM( JUMPASM _BrsHw_core_exception_handler)
  BRS_DUMMY_ISR_ALIGNMENT
#endif /*BRSHW_ENABLE_ISR_SW_DISPATCHING*/

#if defined (BRS_COMP_GHS)
  #pragma endasm
#endif

#if defined (BRS_OS_USECASE_BRS) && !defined (BRS_ENABLE_FBL_SUPPORT)
/********************************************************************************************
 *                                                                                          *
 *                  External/Peripheral Interrupts Vector Table                             *
 *                                                                                          *
 ********************************************************************************************/
# if defined (BRSHW_ENABLE_ISR_SW_DISPATCHING)



#  if defined (BRS_COMP_GHS)
  #pragma asm
  ___asm(.align 12)
#   if defined (BRSHW_INSTRUCTION_SET_VLE)
  PREASM(.vle)
#   endif
  __as1(.section ".intvect_ExtExceptions","vax")
  #pragma endasm
  void (*intvect_ExtExceptions[])() =
  {
#  endif /*BRS_COMP_GHS*/

# else /* BRSHW_ENABLE_ISR_SW_DISPATCHING: Hardware vector mode */
#  if defined (BRS_COMP_GHS)
  #pragma asm
#   if defined (BRSHW_INSTRUCTION_SET_VLE)
  PREASM(.vle)
#   endif
  __as1(.section ".intvect_ExtExceptions","vax")
#  endif


# endif /*BRSHW_ENABLE_ISR_SW_DISPATCHING*/

ASM_COMMENT(/* ... */)
PREASM( JUMPASM BrsHwDummyInterrupt16)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt17)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt18)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt19)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt20)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt21)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt22)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt23)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt24)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt25)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt26)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt27)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt28)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt29)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt30)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt31)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt32)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt33)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt34)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt35)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt36)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt37)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt38)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt39)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt40)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt41)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt42)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt43)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt44)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt45)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt46)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt47)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt48)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt49)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt50)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt51)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt52)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt53)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt54)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt55)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt56)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt57)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt58)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt59)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt60)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt61)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt62)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt63)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt64)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt65)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt66)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt67)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt68)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt69)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt70)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt71)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt72)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt73)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt74)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt75)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt76)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt77)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt78)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt79)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt80)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt81)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt82)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt83)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt84)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt85)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt86)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt87)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt88)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt89)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt90)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt91)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt92)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt93)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt94)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt95)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt96)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt97)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt98)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt99)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt100)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt101)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt102)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt103)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt104)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt105)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt106)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt107)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt108)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt109)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt110)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt111)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt112)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt113)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt114)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt115)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt116)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt117)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt118)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt119)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt120)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt121)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt122)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt123)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt124)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt125)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt126)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt127)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt128)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt129)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt130)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt131)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt132)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt133)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt134)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt135)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt136)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt137)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt138)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt139)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt140)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt141)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt142)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt143)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt144)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt145)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt146)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt147)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt148)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt149)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt150)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt151)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt152)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt153)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt154)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt155)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt156)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt157)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt158)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt159)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt160)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt161)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt162)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt163)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt164)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt165)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt166)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt167)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt168)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt169)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt170)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt171)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt172)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt173)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt174)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt175)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt176)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt177)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt178)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt179)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt180)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt181)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt182)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt183)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt184)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt185)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt186)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt187)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt188)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt189)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt190)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt191)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt192)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt193)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt194)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt195)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt196)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt197)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt198)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt199)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt200)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt201)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt202)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt203)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt204)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt205)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt206)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt207)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt208)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt209)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt210)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt211)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt212)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt213)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt214)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt215)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt216)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt217)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt218)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt219)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt220)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt221)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt222)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt223)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt224)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt225)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt226)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt227)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt228)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt229)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt230)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt231)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt232)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt233)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt234)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt235)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt236)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt237)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt238)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt239)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt240)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt241)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt242)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt243)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt244)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt245)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt246)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt247)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt248)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt249)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt250)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt251)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt252)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt253)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt254)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt255)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt256)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt257)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt258)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt259)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt260)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt261)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt262)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt263)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt264)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt265)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt266)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt267)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt268)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt269)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt270)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt271)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt272)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt273)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt274)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt275)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt276)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt277)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt278)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt279)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt280)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt281)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt282)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt283)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt284)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt285)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt286)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt287)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt288)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt289)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt290)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt291)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt292)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt293)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt294)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt295)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt296)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt297)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt298)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt299)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt300)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt301)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt302)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt303)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt304)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt305)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt306)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt307)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt308)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt309)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt310)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt311)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt312)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt313)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt314)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt315)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt316)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt317)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt318)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt319)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt320)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt321)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt322)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt323)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt324)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt325)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt326)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt327)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt328)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt329)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt330)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt331)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt332)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt333)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt334)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt335)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt336)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt337)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt338)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt339)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt340)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt341)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt342)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt343)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt344)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt345)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt346)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt347)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt348)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt349)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt350)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt351)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt352)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt353)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt354)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt355)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt356)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt357)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt358)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt359)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt360)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt361)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt362)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt363)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt364)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt365)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt366)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt367)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt368)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt369)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt370)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt371)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt372)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt373)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt374)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt375)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt376)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt377)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt378)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt379)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt380)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt381)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt382)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt383)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt384)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt385)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt386)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt387)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt388)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt389)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt390)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt391)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt392)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt393)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt394)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt395)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt396)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt397)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt398)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt399)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt400)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt401)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt402)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt403)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt404)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt405)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt406)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt407)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt408)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt409)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt410)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt411)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt412)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt413)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt414)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt415)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt416)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt417)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt418)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt419)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt420)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt421)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt422)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt423)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt424)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt425)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt426)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt427)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt428)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt429)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt430)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt431)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt432)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt433)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt434)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt435)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt436)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt437)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt438)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt439)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt440)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt441)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt442)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt443)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt444)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt445)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt446)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt447)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt448)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt449)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt450)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt451)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt452)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt453)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt454)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt455)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt456)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt457)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt458)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt459)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt460)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt461)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt462)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt463)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt464)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt465)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt466)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt467)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt468)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt469)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt470)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt471)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt472)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt473)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt474)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt475)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt476)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt477)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt478)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt479)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt480)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt481)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt482)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt483)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt484)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt485)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt486)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt487)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt488)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt489)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt490)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt491)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt492)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt493)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt494)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt495)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt496)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt497)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt498)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt499)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt500)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt501)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt502)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt503)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt504)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt505)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt506)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt507)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt508)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt509)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt510)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt511)
# if defined (BRSHW_INTERRUPT_TABLE_GROUP_A) || defined (BRSHW_INTERRUPT_TABLE_GROUP_C) || defined (BRSHW_INTERRUPT_TABLE_GROUP_E) || defined (BRSHW_INTERRUPT_TABLE_GROUP_F) || defined (BRSHW_INTERRUPT_TABLE_GROUP_G)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt512)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt513)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt514)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt515)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt516)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt517)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt518)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt519)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt520)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt521)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt522)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt523)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt524)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt525)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt526)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt527)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt528)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt529)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt530)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt531)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt532)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt533)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt534)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt535)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt536)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt537)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt538)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt539)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt540)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt541)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt542)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt543)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt544)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt545)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt546)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt547)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt548)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt549)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt550)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt551)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt552)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt553)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt554)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt555)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt556)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt557)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt558)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt559)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt560)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt561)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt562)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt563)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt564)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt565)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt566)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt567)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt568)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt569)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt570)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt571)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt572)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt573)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt574)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt575)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt576)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt577)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt578)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt579)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt580)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt581)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt582)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt583)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt584)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt585)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt586)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt587)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt588)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt589)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt590)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt591)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt592)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt593)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt594)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt595)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt596)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt597)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt598)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt599)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt600)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt601)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt602)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt603)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt604)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt605)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt606)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt607)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt608)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt609)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt610)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt611)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt612)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt613)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt614)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt615)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt616)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt617)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt618)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt619)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt620)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt621)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt622)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt623)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt624)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt625)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt626)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt627)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt628)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt629)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt630)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt631)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt632)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt633)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt634)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt635)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt636)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt637)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt638)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt639)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt640)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt641)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt642)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt643)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt644)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt645)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt646)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt647)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt648)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt649)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt650)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt651)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt652)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt653)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt654)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt655)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt656)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt657)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt658)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt659)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt660)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt661)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt662)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt663)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt664)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt665)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt666)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt667)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt668)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt669)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt670)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt671)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt672)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt673)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt674)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt675)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt676)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt677)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt678)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt679)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt680)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt681)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt682)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt683)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt684)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt685)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt686)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt687)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt688)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt689)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt690)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt691)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt692)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt693)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt694)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt695)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt696)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt697)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt698)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt699)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt700)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt701)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt702)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt703)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt704)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt705)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt706)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt707)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt708)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt709)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt710)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt711)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt712)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt713)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt714)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt715)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt716)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt717)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt718)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt719)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt720)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt721)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt722)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt723)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt724)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt725)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt726)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt727)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt728)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt729)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt730)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt731)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt732)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt733)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt734)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt735)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt736)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt737)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt738)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt739)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt740)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt741)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt742)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt743)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt744)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt745)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt746)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt747)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt748)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt749)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt750)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt751)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt752)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt753)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt754)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt755)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt756)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt757)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt758)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt759)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt760)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt761)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt762)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt763)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt764)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt765)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt766)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt767)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt768)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt769)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt770)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt771)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt772)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt773)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt774)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt775)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt776)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt777)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt778)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt779)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt780)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt781)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt782)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt783)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt784)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt785)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt786)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt787)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt788)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt789)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt790)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt791)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt792)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt793)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt794)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt795)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt796)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt797)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt798)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt799)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt800)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt801)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt802)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt803)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt804)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt805)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt806)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt807)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt808)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt809)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt810)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt811)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt812)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt813)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt814)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt815)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt816)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt817)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt818)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt819)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt820)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt821)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt822)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt823)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt824)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt825)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt826)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt827)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt828)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt829)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt830)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt831)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt832)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt833)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt834)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt835)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt836)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt837)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt838)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt839)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt840)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt841)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt842)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt843)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt844)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt845)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt846)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt847)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt848)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt849)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt850)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt851)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt852)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt853)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt854)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt855)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt856)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt857)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt858)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt859)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt860)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt861)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt862)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt863)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt864)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt865)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt866)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt867)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt868)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt869)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt870)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt871)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt872)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt873)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt874)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt875)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt876)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt877)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt878)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt879)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt880)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt881)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt882)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt883)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt884)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt885)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt886)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt887)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt888)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt889)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt890)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt891)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt892)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt893)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt894)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt895)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt896)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt897)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt898)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt899)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt900)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt901)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt902)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt903)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt904)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt905)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt906)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt907)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt908)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt909)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt910)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt911)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt912)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt913)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt914)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt915)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt916)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt917)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt918)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt919)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt920)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt921)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt922)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt923)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt924)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt925)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt926)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt927)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt928)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt929)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt930)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt931)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt932)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt933)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt934)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt935)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt936)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt937)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt938)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt939)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt940)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt941)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt942)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt943)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt944)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt945)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt946)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt947)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt948)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt949)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt950)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt951)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt952)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt953)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt954)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt955)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt956)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt957)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt958)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt959)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt960)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt961)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt962)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt963)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt964)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt965)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt966)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt967)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt968)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt969)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt970)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt971)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt972)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt973)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt974)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt975)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt976)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt977)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt978)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt979)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt980)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt981)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt982)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt983)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt984)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt985)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt986)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt987)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt988)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt989)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt990)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt991)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt992)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt993)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt994)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt995)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt996)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt997)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt998)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt999)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1000)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1001)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1002)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1003)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1004)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1005)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1006)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1007)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1008)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1009)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1010)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1011)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1012)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1013)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1014)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1015)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1016)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1017)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1018)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1019)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1020)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1021)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1022)
BRS_DUMMY_ISR_ALIGNMENT
PREASM( JUMPASM BrsHwDummyInterrupt1023)
#endif /*BRSHW_INTERRUPT_TABLE_GROUP_A, BRSHW_INTERRUPT_TABLE_GROUP_C, BRSHW_INTERRUPT_TABLE_GROUP_E, BRSHW_INTERRUPT_TABLE_GROUP_F*/

# if defined (BRSHW_ENABLE_ISR_SW_DISPATCHING)


#  if defined (BRS_COMP_GHS)
  };
  #pragma asm
#   if defined (BRSHW_INSTRUCTION_SET_VLE)
    PREASM(.vle)
#   endif
  __as1(.section ".intvect_ExtExceptionsCode" , "vax")
#  endif

# else /* BRSHW_ENABLE_ISR_SW_DISPATCHING: Hardware Vector Mode */
#  if defined (BRS_COMP_GHS)
#   if defined (BRSHW_INSTRUCTION_SET_VLE)
  PREASM(.vle)
#   endif
  __as1(.section ".intvect_ExtExceptionsCode" , "vax")
#  endif



# endif /*else BRSHW_ENABLE_ISR_SW_DISPATCHING*/

ASM_COMMENT(/********************************************************************************************/)
ASM_COMMENT(/*                                                                                          */)
ASM_COMMENT(/*                           ISR Handler Definition                                         */)
ASM_COMMENT(/*                                                                                          */)
ASM_COMMENT(/********************************************************************************************/)
# if defined (BRSHW_ENABLE_ISR_SW_DISPATCHING)
  ASM_COMMENT(/* Context saving is done in ISR SW Dispatcher! */)
  ASM_COMMENT(/*==================================================================================*/)
  ASM_COMMENT(/* Core exception handler                                                           */)
  ASM_COMMENT(/*==================================================================================*/)
  ___asm(.align BRS_CORE_VECTOR_ALIGNMENT)
  ___asm(_BrsHw_core_exception_handler:)
  ASM_COMMENT(/* do not return form this handler */)
  ___asm(nop)
  ___asm(e_b BrsHw_core_exception_handler)

  ASM_COMMENT(/*==================================================================================*/)
  ASM_COMMENT(/* Setup software ISR dispatcher for MPC5700                                        */)
  ASM_COMMENT(/*==================================================================================*/)
  ___asm(.align BRS_CORE_VECTOR_ALIGNMENT)

  ___asm( __isr_handler:  )
  __as1( e_stwu  r1, -0x50(r1) ; /* Create stack frame and store back chain*/)
  __as1( se_stw  r3,  0x28(r1) ; /* Store a working register */)
  ___asm( mfsrr0  r3           ; /* Store SRR0:1 (must be done before enabling EE) */)
  __as1( se_stw  r3,  0x0C(r1))
  ___asm( mfsrr1  r3)
  __as1( se_stw  r3,  0x10(r1))

#  if defined (BRS_DERIVATIVE_MPC5777M) || defined (BRS_DERIVATIVE_MPC5746M)
  __as1( e_lis   r3, 0xFC04     ; /* Read pointer to ISR Vector Table        */)
  __as1( e_lwz   r3, 0x0028(r3) ; /* from INTC_IACKR_2 register (0xFC040028) */)
#  elif defined (BRS_DERIVATIVE_SPC570S50) || defined (BRS_DERIVATIVE_MPC5748G)
  __as1( e_lis   r3, 0xFC04     ; /* Single core: Read pointer to corresponding Interrupt Vector Table entry */)
  __as1( e_lwz   r3, 0x0020(r3) ; /*              from INTC_IACKR_0 register (0xFC040020)                    */)
#  endif /*BRS_DERIVATIVE_x*/

  __as1( se_lwz  r3, 0x0(r3)    ; /* Read ISR address from Interrupt Vector Table using previously read pointer */)

  ___asm( wrteei  1             ; /* Set MSR[EE] = 1 wait a couple clocks after reading INTC_IACKR_n */)
  __as1( se_stw  r4,  0x2C(r1)  ; /* Store a second working register */)
  ___asm( se_mflr r4            ; /* Store LR (LR will be used for ISR Vector) */)
  __as1( se_stw  r4,  0x14(r1))
  ___asm( se_mtlr r3            ; /* Store ISR address to LR to use for branching later */)

  __as1( e_stw   r12, 0x4C(r1)  ; /* Store rest of gprs */)
  __as1( e_stw   r11, 0x48(r1))
  __as1( e_stw   r10, 0x44(r1))
  __as1( e_stw   r9,  0x40(r1))
  __as1( e_stw   r8,  0x3C(r1))
  __as1( se_stw  r7,  0x38(r1))
  __as1( se_stw  r6,  0x34(r1))
  __as1( se_stw  r5,  0x30(r1))
  __as1( se_stw  r0,  0x24(r1))
  ___asm( mfcr    r3            ; /* Store CR */)
  __as1( se_stw  r3,  0x20(r1))
  ___asm(mfxer   r3             ; /* Store XER */)
  __as1( se_stw  r3,  0x1C(r1))
  ___asm(se_mfctr   r3          ; /* Store CTR */)
  __as1( se_stw  r3,  0x18(r1))

  ___asm(se_blrl                ; /* Branch to ISR but return here */)

  __as1( se_lwz  r3,  0x14(r1)  ; /* Restore LR */)
  ___asm( se_mtlr r3)
  __as1( se_lwz  r3,  0x18(r1)  ; /* Restore CTR */)
  ___asm(se_mtctr r3)
  __as1( se_lwz  r3,  0x1C(r1)  ; /* Restore XER */)
  ___asm(mtxer   r3)
  __as1( se_lwz  r3,  0x20(r1)  ; /* Restore CR */)
  __as1( mtcrf   0xff, r3 )
  __as1( se_lwz  r0,  0x24(r1)  ; /* Restore other gprs except working registers */)
  __as1( se_lwz  r5,  0x30(r1))
  __as1( se_lwz  r6,  0x34(r1))
  __as1( se_lwz  r7,  0x38(r1))
  __as1( e_lwz   r8,  0x3C(r1))
  __as1( e_lwz   r9,  0x40(r1))
  __as1( e_lwz   r10, 0x44(r1))
  __as1( e_lwz   r11, 0x48(r1))
  __as1( e_lwz   r12, 0x4C(r1))

  ___asm( wrteei  0             ; /* Disable interrupts (MSR[EE]=0) for rest of handler */)
  ___asm(                       ; /* (moved up caused by problems in MPC57xxx INTC if INTC_EOIR is written while interrupts are enabled) */)
  ___asm( mbar    0             ; /* Ensure store to clear interrupt flag bit completed */)

#  if defined (BRS_DERIVATIVE_MPC5777M) || defined (BRS_DERIVATIVE_MPC5746M)
  __as1( e_lis   r3, 0xFC04     ; /* Single Core: Load upper half of INTC_EOIR_2 address to r3 */)
  __as1( se_li    r4, 0         ; /* Load 0 into register r4                                   */)
  __as1( e_stw   r4, 0x0038(r3) ; /* Write 0 to INTC_EOIR_2                                    */)
#  elif defined (BRS_DERIVATIVE_SPC570S50) || defined (BRS_DERIVATIVE_MPC5748G)
  __as1( e_lis   r3, 0xFC04     ; /* Single Core: Load upper half of INTC_EOIR_0 address to r3 */)
  __as1( se_li    r4, 0         ; /* Load 0 into register r4                                   */)
  __as1( e_stw   r4, 0x0030(r3) ; /* Single core: Write 0 to INTC_EOIR_0                       */)
#  endif /*BRS_DERIVATIVE_x*/

  __as1( se_lwz   r3,  0x0C(r1) ; /* Restore SRR0 */)
  ___asm( mtsrr0  r3)
  __as1( se_lwz  r3,  0x10(r1)  ; /* Restore SRR1 */)
  ___asm( mtsrr1  r3)
  __as1( se_lwz  r4,  0x2C(r1)  ; /* Restore working registers */)
  __as1( se_lwz  r3,  0x28(r1))
  __as2( e_add16i r1, r1, 0x50  ; /* Delete stack frame */)

  ___asm( se_rfi                ; /* End of Interrupt */)

# else /* BRSHW_ENABLE_ISR_SW_DISPATCHING: IRQ Handler for Hardware Vector Mode */

  ___asm(_BrsHw_core_exception_handler:)
  ASM_COMMENT(/* do not return form this handler */)
  ___asm(nop)
  ___asm(e_b BrsHw_core_exception_handler)

  ___asm( FinishSavingContext:)
  ___asm( ;/*  Save other registers to allow calling a c function */)
  ___asm( mfxer r3        ; /* Get XER */)
  __as1( e_stw r3, 20 (sp); /* and save XER */)
  __as1( mfspr r3, CTR    ; /* Get CTR */)
  __as1( e_stw r3, 24 (sp); /* and save CTR */)
  ___asm( mfcr r3         ; /* Get CR */)
  __as1( e_stw r3, 28 (sp); /* and save CR */)
  __as1( e_stw r0, 32 (sp); /* Save R0 */)
  __as1( e_stw r4, 40 (sp); /* Save R4 to R12 */)
  __as1( e_stw r5, 44 (sp) )
  __as1( e_stw r6, 48 (sp) )
  __as1( e_stw r7, 52 (sp) )
  __as1( e_stw r8, 56 (sp) )
  __as1( e_stw r9, 60 (sp) )
  __as1( e_stw r10, 64 (sp) )
  __as1( e_stw r11, 68 (sp) )
  __as1( e_stw r12, 72 (sp) )
  ___asm( se_blr                ; /* Return to interrupt routine */)

#  if defined (BRSHW_ENABLE_TIMER_INTERRUPT)
  ASM_COMMENT(/*Timer Interrupt*/)
  ___asm( _BrsHwTimeBaseInterrupt:)
  ISR_HANDLER_DEFINITION(BrsHwTimeBaseInterrupt)
#  endif

#  if defined (BRS_ENABLE_EXTERNAL_WAKEUP)
  ASM_COMMENT(/* Wakeup Interrupt 0 */)
  ___asm( _BrsHwWakeUpIsr_0:)
  ISR_HANDLER_DEFINITION(BrsHwWakeUpIsr_0)

  ASM_COMMENT(/* Wakeup Interrupt 1 */)
  ___asm( _BrsHwWakeUpIsr_1:)
  ISR_HANDLER_DEFINITION(BrsHwWakeUpIsr_1)

  ASM_COMMENT(/* Wakeup Interrupt 2 */)
  ___asm( _BrsHwWakeUpIsr_2:)
  ISR_HANDLER_DEFINITION(BrsHwWakeUpIsr_2)

  ASM_COMMENT(/* Wakeup Interrupt 3 */)
  ___asm( _BrsHwWakeUpIsr_3:)
  ISR_HANDLER_DEFINITION(BrsHwWakeUpIsr_3)

  ASM_COMMENT(/* Wakeup Interrupt 4to15 */)
  ___asm( _BrsHwWakeUpIsr_4to15:)
  ISR_HANDLER_DEFINITION(BrsHwWakeUpIsr_4to15)
#  endif /*BRS_ENABLE_EXTERNAL_WAKEUP*/

  ___asm( RestoreContext: )
#  if !defined (BRSHW_INTERRUPT_TABLE_GROUP_A)
  ___asm( wrteei 0 ; /* Disable interrupts until end of routine (moved up caused by problems in MPC57xxx INTC if EIOR is written while interrupts are enabled) */)
#  endif
  ___asm( mbar 0   ; /* Ensure interrupt flag has finished clearing before writing to INTC_EIOR */)
  __as1( e_li r3,0)

#  if defined (BRSHW_INTERRUPT_TABLE_GROUP_A) || defined (BRSHW_INTERRUPT_TABLE_GROUP_C) || defined (BRSHW_INTERRUPT_TABLE_GROUP_E) || defined (BRSHW_INTERRUPT_TABLE_GROUP_G)
  __as1( e_lis r4, 0xfc04       ; /* Load address of INTC_EOIR to r4 */)
#  elif defined (BRSHW_INTERRUPT_TABLE_GROUP_D)
  __as1( e_lis r4, 0xfff0       ; /* Load address of INTC_EOIR to r4 */)
#  else
  __as1( e_lis r4, 0xfff4       ; /* Load address of INTC_EOIR to r4 */)
#  endif

#  if defined (BRSHW_INTERRUPT_TABLE_GROUP_C)
#   if defined (BRSHW_INSTRUCTION_SET_VLE)
#    if defined (BRS_DERIVATIVE_SPC574Sx)
  __as1(e_or2i r4, 0x0030)
#    else
  __as1(e_or2i r4, 0x0038)
#    endif
#   else
  __as2(e_ori  r4, r4, 0x0038)
#   endif

#  elif defined (BRSHW_INTERRUPT_TABLE_GROUP_A) || defined (BRSHW_INTERRUPT_TABLE_GROUP_E)
#   if defined (BRSHW_INSTRUCTION_SET_VLE)
  __as1(e_or2i r4, 0x0030)
#   else
  __as2(e_ori  r4, r4, 0x0030)
#   endif

#  elif defined (BRSHW_INTERRUPT_TABLE_GROUP_D)
#   if defined (BRSHW_INSTRUCTION_SET_VLE)
  __as1(e_or2i r4, 0x8030)
#   else
  __as2(e_ori  r4, r4, 0x8030)
#   endif

#  elif defined (BRSHW_INTERRUPT_TABLE_GROUP_G)
#   if defined  (BRSHW_INSTRUCTION_SET_VLE)
  __as1(e_or2i r4, 0x0034) 
#   else
  __as2(e_ori  r4, r4, 0x0034)
#   endif

#  else
#   if defined (BRSHW_INSTRUCTION_SET_VLE)
  __as1(e_or2i r4, 0x8018)
#   else
  __as2(e_ori  r4, r4, 0x8018)
#   endif
#  endif /*BRSHW_INTERRUPT_TABLE_GROUP_x*/

  __as1( e_stw r3, 0(r4)        ; /* Write 0 to INTC_EOIR */)
#  if defined (BRSHW_INTERRUPT_TABLE_GROUP_A)
  __as1( e_stwu r3, 0(r4)       ; /* Write 0 to INTC_EOIR AGHAGH???? 2mal??? Evtl. auch für BRSHW_INTERRUPT_TABLE_GROUP_D?? */)
#  endif

  __as1( e_lwz r0, 32 (sp)      ; /* Restore gprs except R3 */)
  __as1( e_lwz r4, 40 (sp) )
  __as1( e_lwz r5, 44 (sp) )
  __as1( e_lwz r6, 48 (sp) )
  __as1( e_lwz r7, 52 (sp) )
  __as1( e_lwz r8, 56 (sp) )
  __as1( e_lwz r9, 60 (sp) )
  __as1( e_lwz r10, 64 (sp) )
  __as1( e_lwz r11, 68 (sp) )
  __as1( e_lwz r12, 72 (sp) )
  __as1( e_lwz r3, 20 (sp)      ; /* Get XER */)
  ___asm( mtxer r3              ; /* and restore XER */)
  __as1( e_lwz r3, 24 (sp)      ; /* Get CTR */)
  ___asm( mtctr r3              ; /* and restore CTR */)
  __as1( e_lwz r3, 28 (sp)      ; /* Get CR */)
  __as1( mtcrf 0xff, r3         ; /* and restore CR */)
  __as1( e_lwz r3, 8 (sp)       ; /* Get LR */)
  ___asm( mtlr r3               ; /* and restore LR */)
#  if defined (BRSHW_INTERRUPT_TABLE_GROUP_A)
  ___asm( wrteei 0              ; /* Disable interrupts until end of routine */)
#  endif
  __as1( e_lwz r3, 12 (sp)      ; /* Get SRR0 from stack */)
  ___asm( mtsrr0 r3             ; /* and restore SRR0 */)
  __as1( e_lwz r3, 16 (sp)      ; /* Get SRR1 from stack */)
  ___asm( mtsrr1 r3             ; /* and restore SRR1 */)
  __as1( e_lwz r3, 36 (sp)      ; /* Restore R3 */)
  __as2( e_add16i sp, sp, 80    ; /* Clean up stack STEP 7:  Return to Program */)
  ___asm( se_rfi                ; /* End of Interrupt */)

  ASM_COMMENT(/* Ethernet ISRs */)
#  if defined (VGEN_ENABLE_DRVETH__BASEASR)
  ASM_COMMENT(/* ENET Interrupt Group1 */)
  ___asm( _EthIsr_Rx: )
  ISR_HANDLER_DEFINITION(EthIsr_Rx)

  ASM_COMMENT(/* ENET Interrupt Group2 */)
  ___asm( _EthIsr_Tx: )
  ISR_HANDLER_DEFINITION(EthIsr_Tx)
#  endif

  ASM_COMMENT(/* FlexRay ISRs */)
#  if defined (VGEN_ENABLE_DRVFR__BASEASR)
  ___asm( _BrsHwFlexRayProtInterrupt: )
  ISR_HANDLER_DEFINITION(Fr_IrqProtocol)
#  endif

  ASM_COMMENT(/* LIN ISRs */)
#  if defined (VGEN_ENABLE_LIN_DRV)
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
#    if defined (BRSHW_INTERRUPT_TABLE_GROUP_B)
  ___asm( _LINSCI_LinIsr_0:)
  ISR_HANDLER_DEFINITION(LinIsr_0)

#    else
  ___asm( _LINFLEX_LinIsr_RXI_0:)
  ISR_HANDLER_DEFINITION(LinIsr_RXI_0)

  ___asm( _LINFLEX_LinIsr_TXI_0:)
  ISR_HANDLER_DEFINITION(LinIsr_TXI_0)

  ___asm( _LINFLEX_LinIsr_ERR_0:)
  ISR_HANDLER_DEFINITION(LinIsr_ERR_0)
#    endif /*BRSHW_INTERRUPT_TABLE_GROUP_x*/
#   endif /*LIN_ENABLE_HARDWARE_INTERFACE_0*/

#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
#    if defined (BRSHW_INTERRUPT_TABLE_GROUP_B)
  ___asm( _LINSCI_LinIsr_1:)
  ISR_HANDLER_DEFINITION(LinIsr_1)

#    else
  ___asm( _LINFLEX_LinIsr_RXI_1:)
  ISR_HANDLER_DEFINITION(LinIsr_RXI_1)

  ___asm( _LINFLEX_LinIsr_TXI_1:)
  ISR_HANDLER_DEFINITION(LinIsr_TXI_1)

  ___asm( _LINFLEX_LinIsr_ERR_1:)
  ISR_HANDLER_DEFINITION(LinIsr_ERR_1)
#    endif
#   endif /*LIN_ENABLE_HARDWARE_INTERFACE_1*/

#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_2)
#    if defined (BRSHW_INTERRUPT_TABLE_GROUP_B)
  ___asm( _LINSCI_LinIsr_2:)
  ISR_HANDLER_DEFINITION(LinIsr_2)

#    else
  ___asm( _LINFLEX_LinIsr_RXI_2:)
  ISR_HANDLER_DEFINITION(LinIsr_RXI_2)

  ___asm( _LINFLEX_LinIsr_TXI_2:)
  ISR_HANDLER_DEFINITION(LinIsr_TXI_2)

  ___asm( _LINFLEX_LinIsr_ERR_2:)
  ISR_HANDLER_DEFINITION(LinIsr_ERR_2)
#    endif
#   endif /*LIN_ENABLE_HARDWARE_INTERFACE_2*/

#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_3)
#    if defined (BRSHW_INTERRUPT_TABLE_GROUP_B)
  ___asm( _LINSCI_LinIsr_3:)
  ISR_HANDLER_DEFINITION(LinIsr_3)

#    else
  ___asm( _LINFLEX_LinIsr_RXI_3:)
  ISR_HANDLER_DEFINITION(LinIsr_RXI_3)

  ___asm( _LINFLEX_LinIsr_TXI_3:)
  ISR_HANDLER_DEFINITION(LinIsr_TXI_3)

  ___asm( _LINFLEX_LinIsr_ERR_3:)
  ISR_HANDLER_DEFINITION(LinIsr_ERR_3)
#    endif
#   endif /*LIN_ENABLE_HARDWARE_INTERFACE_3*/

#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_4)
#    if defined (BRSHW_INTERRUPT_TABLE_GROUP_B)
  ___asm( _LINSCI_LinIsr_4:)
  ISR_HANDLER_DEFINITION(LinIsr_4)

#    else
  ___asm( _LINFLEX_LinIsr_RXI_4:)
  ISR_HANDLER_DEFINITION(LinIsr_RXI_4)

  ___asm( _LINFLEX_LinIsr_TXI_4:)
  ISR_HANDLER_DEFINITION(LinIsr_TXI_4)

  ___asm( _LINFLEX_LinIsr_ERR_4:)
  ISR_HANDLER_DEFINITION(LinIsr_ERR_4)
#    endif
#   endif /*LIN_ENABLE_HARDWARE_INTERFACE_4*/

#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_5)
#    if defined (BRSHW_INTERRUPT_TABLE_GROUP_B)
  ___asm( _LINSCI_LinIsr_5:)
  ISR_HANDLER_DEFINITION(LinIsr_5)

#    else
  ___asm( _LINFLEX_LinIsr_RXI_5:)
  ISR_HANDLER_DEFINITION(LinIsr_RXI_5)

  ___asm( _LINFLEX_LinIsr_TXI_5:)
  ISR_HANDLER_DEFINITION(LinIsr_TXI_5)

  ___asm( _LINFLEX_LinIsr_ERR_5:)
  ISR_HANDLER_DEFINITION(LinIsr_ERR_5)
#    endif
#   endif /*LIN_ENABLE_HARDWARE_INTERFACE_5*/
#  endif /*VGEN_ENABLE_LIN_DRV*/

  ASM_COMMENT(/* Save context for CAN ISRs */)
#  if defined (VGEN_ENABLE_CAN_DRV)
#   if defined (BRSHW_INTERRUPT_TABLE_GROUP_C)
#    if defined (kCanPhysToLogChannelIndex_0) || defined (kCan_30_McanPhysToLogChannelIndex_0)
  ___asm( _TTCAN1_LINE0_Interrupt:)
  ___asm( _MCAN0_LINE0_Interrupt:)
  ISR_HANDLER_DEFINITION(CanIsr_0)
#    endif /*kCanPhysToLogChannelIndex_0*/

#    if defined (kCanPhysToLogChannelIndex_1) || defined (kCan_30_McanPhysToLogChannelIndex_1)
  ___asm( _MCAN1_LINE0_Interrupt:)
  ISR_HANDLER_DEFINITION(CanIsr_1)
#    endif /*kCanPhysToLogChannelIndex_1*/

#    if defined (kCanPhysToLogChannelIndex_2) || defined (kCan_30_McanPhysToLogChannelIndex_2)
  ___asm( _MCAN2_LINE0_Interrupt:)
  ISR_HANDLER_DEFINITION(CanIsr_2)
#    endif /*kCanPhysToLogChannelIndex_2*/

#    if defined (kCanPhysToLogChannelIndex_3) || defined (kCan_30_McanPhysToLogChannelIndex_3)
  ___asm( _MCAN3_LINE0_Interrupt:)
  ISR_HANDLER_DEFINITION(CanIsr_3)
#    endif /*kCanPhysToLogChannelIndex_3*/

#    if defined (kCanPhysToLogChannelIndex_4) || defined (kCan_30_McanPhysToLogChannelIndex_4)
  ___asm( _MCAN4_LINE0_Interrupt:)
  ISR_HANDLER_DEFINITION(CanIsr_4)
#    endif /*kCanPhysToLogChannelIndex_4*/
#   endif /*BRSHW_INTERRUPT_TABLE_GROUP_C*/

#   if defined (BRSHW_INTERRUPT_TABLE_GROUP_D)
#    if defined (kCanPhysToLogChannelIndex_0)
  ___asm( _FlexCANA_Interrupt:)
  ISR_HANDLER_DEFINITION(CanMailboxIsr_0)
#     if !defined (C_ENABLE_ERROR_POLLING)
  ___asm( _FlexCANA_ErrorInterrupt:)
  ISR_HANDLER_DEFINITION(CanBusOffIsr_0)
#     endif /*!C_ENABLE_ERROR_POLLING*/
#    endif /*kCanPhysToLogChannelIndex_0*/

#    if defined (kCanPhysToLogChannelIndex_1)
  ___asm( _FlexCANB_Interrupt:)
  ISR_HANDLER_DEFINITION(CanMailboxIsr_1)
#     if !defined (C_ENABLE_ERROR_POLLING)
  ___asm( _FlexCANB_ErrorInterrupt:)
  ISR_HANDLER_DEFINITION(CanBusOffIsr_1)
#     endif /*!C_ENABLE_ERROR_POLLING*/
#    endif /*kCanPhysToLogChannelIndex_1*/

#    if defined (kCanPhysToLogChannelIndex_2)
  ___asm( _FlexCANC_Interrupt:)
  ISR_HANDLER_DEFINITION(CanMailboxIsr_2)
#     if !defined (C_ENABLE_ERROR_POLLING)
  ___asm( _FlexCANC_ErrorInterrupt:)
  ISR_HANDLER_DEFINITION(CanBusOffIsr_2)
#     endif /*!C_ENABLE_ERROR_POLLING*/
#    endif /*kCanPhysToLogChannelIndex_2*/
#   endif /*BRSHW_INTERRUPT_TABLE_GROUP_D*/

#   if defined (BRSHW_INTERRUPT_TABLE_GROUP_A) || defined (BRSHW_INTERRUPT_TABLE_GROUP_B) || defined (BRSHW_INTERRUPT_TABLE_GROUP_E) || defined (BRSHW_INTERRUPT_TABLE_GROUP_F) || defined (BRSHW_INTERRUPT_TABLE_GROUP_G)
#    if defined (BRSHW_USED_CANCELL_DEFAULT)
  ASM_COMMENT(/* FlexCAN_A */)
#     if defined (kCanPhysToLogChannelIndex_0)
#      if defined (C_ENABLE_SINGLE_ISR_API)
  ___asm( _FlexCANA_Interrupt:)
  ISR_HANDLER_DEFINITION(CanIsr_0)

#      else
#       if !defined (C_ENABLE_ERROR_POLLING)
  ___asm( _FlexCANA_ErrorInterrupt:)
  ISR_HANDLER_DEFINITION(CanBusOffIsr_0)
#       endif /*!C_ENABLE_ERROR_POLLING*/

#       if defined (C_ENABLE_CAN_INTERRUPT)
#        if defined (BRSHW_INTERRUPT_TABLE_GROUP_A) || defined (BRSHW_INTERRUPT_TABLE_GROUP_E) || defined (BRSHW_INTERRUPT_TABLE_GROUP_G)
  ___asm( _FlexCANA_RxFifoInterrupt:)
  ISR_HANDLER_DEFINITION(CanRxFifoIsr_0)

  ___asm( _FlexCANA_MB8To63Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB8To63Isr_0)

#         if defined (C_CAN_MAX_BUFFER_96)
  ___asm( _FlexCANA_MB64To95Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB64To95Isr_0)
#         endif /*C_CAN_MAX_BUFFER_96*/

#        elif defined (BRSHW_INTERRUPT_TABLE_GROUP_B)
  ___asm( _FlexCANA_RxFifoInterrupt:)
  ISR_HANDLER_DEFINITION(CanRxFifoIsr_0)

  ___asm( _FlexCANA_MB8To63Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB8To63Isr_0)

#        else
  ___asm( _FlexCANA_MB0Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB0Isr_0)

  ___asm( _FlexCANA_MB1Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB1Isr_0)

  ___asm( _FlexCANA_MB2Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB2Isr_0)

  ___asm( _FlexCANA_MB3Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB3Isr_0)

  ___asm( _FlexCANA_MB4Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB4Isr_0)

  ___asm( _FlexCANA_MB5Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB5Isr_0)

  ___asm( _FlexCANA_MB6Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB6Isr_0)

  ___asm( _FlexCANA_MB7Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB7Isr_0)

  ___asm( _FlexCANA_MB8Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB8Isr_0)

  ___asm( _FlexCANA_MB9Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB9Isr_0)

  ___asm( _FlexCANA_MB10Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB10Isr_0)

  ___asm( _FlexCANA_MB11Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB11Isr_0)

  ___asm( _FlexCANA_MB12Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB12Isr_0)

  ___asm( _FlexCANA_MB13Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB13Isr_0)

  ___asm( _FlexCANA_MB14Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB14Isr_0)

  ___asm( _FlexCANA_MB15Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB15Isr_0)
#        endif /*BRSHW_INTERRUPT_TABLE_GROUP_A||BRSHW_INTERRUPT_TABLE_GROUP_E||BRSHW_INTERRUPT_TABLE_GROUP_G*/

#        if defined (BRSHW_INTERRUPT_TABLE_GROUP_F)
  ___asm( _FlexCANA_MB16To31Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB16To31Isr_0)

  ___asm( _FlexCANA_MB32To63Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB32To63Isr_0)

#         if defined (C_ENABLE_MB64TO95)
  ___asm( _FlexCANA_MB64To95Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB64To95Isr_0)
#         endif /*C_ENABLE_MB64TO95*/

#         if defined (C_ENABLE_MB96TO127)
  ___asm( _FlexCANA_MB96To127Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB96To127Isr_0)
#         endif /*C_ENABLE_MB96TO127*/
#        endif /*BRSHW_INTERRUPT_TABLE_GROUP_F*/
#       endif /*C_ENABLE_CAN_INTERRUPT*/
#      endif /*else C_ENABLE_SINGLE_ISR_API*/
#     endif /*kCanPhysToLogChannelIndex_0*/

  ASM_COMMENT(/* FlexCAN B */)
#     if defined (kCanPhysToLogChannelIndex_1)
#      if defined (C_ENABLE_SINGLE_ISR_API)
  ___asm( _FlexCANB_Interrupt:)
  ISR_HANDLER_DEFINITION(CanIsr_1)

#      else
#       if !defined (C_ENABLE_ERROR_POLLING)
  ___asm( _FlexCANB_ErrorInterrupt:)
  ISR_HANDLER_DEFINITION(CanBusOffIsr_1)
#       endif

#       if defined (C_ENABLE_CAN_INTERRUPT)
#        if defined (BRSHW_INTERRUPT_TABLE_GROUP_A) || defined (BRSHW_INTERRUPT_TABLE_GROUP_E) || defined (BRSHW_INTERRUPT_TABLE_GROUP_G)
  ___asm( _FlexCANB_RxFifoInterrupt:)
  ISR_HANDLER_DEFINITION(CanRxFifoIsr_1)

  ___asm( _FlexCANB_MB8To63Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB8To63Isr_1)

#         if defined (C_CAN_MAX_BUFFER_96)
  ___asm( _FlexCANB_MB64To95Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB64To95Isr_1)
#         endif /*C_CAN_MAX_BUFFER_96*/

#        elif defined (BRSHW_INTERRUPT_TABLE_GROUP_B)
  ___asm( _FlexCANB_RxFifoInterrupt:)
  ISR_HANDLER_DEFINITION(CanRxFifoIsr_1)

  ___asm( _FlexCANB_MB8To63Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB8To63Isr_1)

#        else
  ___asm( _FlexCANB_MB0Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB0Isr_1)

  ___asm( _FlexCANB_MB1Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB1Isr_1)

  ___asm( _FlexCANB_MB2Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB2Isr_1)

  ___asm( _FlexCANB_MB3Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB3Isr_1)

  ___asm( _FlexCANB_MB4Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB4Isr_1)

  ___asm( _FlexCANB_MB5Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB5Isr_1)

  ___asm( _FlexCANB_MB6Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB6Isr_1)

  ___asm( _FlexCANB_MB7Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB7Isr_1)

  ___asm( _FlexCANB_MB8Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB8Isr_1)

  ___asm( _FlexCANB_MB9Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB9Isr_1)

  ___asm( _FlexCANB_MB10Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB10Isr_1)

  ___asm( _FlexCANB_MB11Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB11Isr_1)

  ___asm( _FlexCANB_MB12Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB12Isr_1)

  ___asm( _FlexCANB_MB13Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB13Isr_1)

  ___asm( _FlexCANB_MB14Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB14Isr_1)

  ___asm( _FlexCANB_MB15Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB15Isr_1)
#        endif

#        if defined (BRSHW_INTERRUPT_TABLE_GROUP_F)
  ___asm( _FlexCANB_MB16To31Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB16To31Isr_1)

  ___asm( _FlexCANB_MB32To63Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB32To63Isr_1)

#         if defined (C_ENABLE_MB64TO95)
  ___asm( _FlexCANB_MB64To95Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB64To95Isr_1)
#         endif /*C_ENABLE_MB64TO95*/

#         if defined (C_ENABLE_MB96TO127)
  ___asm( _FlexCANB_MB96To127Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB96To127Isr_1)
#         endif /*C_ENABLE_MB96TO127*/
#        endif /*BRSHW_INTERRUPT_TABLE_GROUP_F*/
#       endif /*C_ENABLE_CAN_INTERRUPT*/
#      endif /*else C_ENABLE_SINGLE_ISR_API*/
#     endif /*kCanPhysToLogChannelIndex_1*/

 ASM_COMMENT(/* FlexCAN C */)
#     if defined (kCanPhysToLogChannelIndex_2)
#      if defined (C_ENABLE_SINGLE_ISR_API)
  ___asm( _FlexCANC_Interrupt:)
  ISR_HANDLER_DEFINITION(CanIsr_2)

#      else
#       if !defined (C_ENABLE_ERROR_POLLING)
  ___asm( _FlexCANC_ErrorInterrupt:)
  ISR_HANDLER_DEFINITION(CanBusOffIsr_2)
#       endif

#       if defined (C_ENABLE_CAN_INTERRUPT)
#        if defined (BRSHW_INTERRUPT_TABLE_GROUP_A) || defined (BRSHW_INTERRUPT_TABLE_GROUP_E) || defined (BRSHW_INTERRUPT_TABLE_GROUP_G)
  ___asm( _FlexCANC_RxFifoInterrupt:)
  ISR_HANDLER_DEFINITION(CanRxFifoIsr_2)

  ___asm( _FlexCANC_MB8To63Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB8To63Isr_2)

#         if defined (C_CAN_MAX_BUFFER_96)
  ___asm( _FlexCANC_MB64To95Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB64To95Isr_2)
#         endif /*C_CAN_MAX_BUFFER_96*/

#        elif defined (BRSHW_INTERRUPT_TABLE_GROUP_B)
  ___asm( _FlexCANC_RxFifoInterrupt:)
  ISR_HANDLER_DEFINITION(CanRxFifoIsr_2)

  ___asm( _FlexCANC_MB8To63Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB8To63Isr_2)

#        else
  ___asm( _FlexCANC_MB0Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB0Isr_2)

  ___asm( _FlexCANC_MB1Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB1Isr_2)

  ___asm( _FlexCANC_MB2Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB2Isr_2)

  ___asm( _FlexCANC_MB3Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB3Isr_2)

  ___asm( _FlexCANC_MB4Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB4Isr_2)

  ___asm( _FlexCANC_MB5Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB5Isr_2)

  ___asm( _FlexCANC_MB6Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB6Isr_2)

  ___asm( _FlexCANC_MB7Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB7Isr_2)

  ___asm( _FlexCANC_MB8Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB8Isr_2)

  ___asm( _FlexCANC_MB9Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB9Isr_2)

  ___asm( _FlexCANC_MB10Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB10Isr_2)

  ___asm( _FlexCANC_MB11Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB11Isr_2)

  ___asm( _FlexCANC_MB12Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB12Isr_2)

  ___asm( _FlexCANC_MB13Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB13Isr_2)

  ___asm( _FlexCANC_MB14Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB14Isr_2)

  ___asm( _FlexCANC_MB15Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB15Isr_2)
#        endif /*# else BRSHW_INTERRUPT_TABLE_GROUP_A || defined BRSHW_INTERRUPT_TABLE_GROUP_E || defined BRSHW_INTERRUPT_TABLE_GROUP_G*/

#        if defined (BRSHW_INTERRUPT_TABLE_GROUP_F)
  ___asm( _FlexCANC_MB16To31Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB16To31Isr_2)

  ___asm( _FlexCANC_MB32To63Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB32To63Isr_2)

#         if defined (C_ENABLE_MB64TO95)
  ___asm( _FlexCANC_MB64To95Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB64To95Isr_2)
#         endif /*C_ENABLE_MB64TO95*/

#         if defined (C_ENABLE_MB96TO127)
  ___asm( _FlexCANC_MB96To127Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB96To127Isr_2)
#         endif /*C_ENABLE_MB96TO127*/
#        endif /*BRSHW_INTERRUPT_TABLE_GROUP_F*/
#       endif /*C_ENABLE_CAN_INTERRUPT*/
#      endif /*else C_ENABLE_SINGLE_ISR_API*/
#     endif /*kCanPhysToLogChannelIndex_2*/

 ASM_COMMENT(/* FlexCAN D */)
#     if defined (kCanPhysToLogChannelIndex_3)
#      if defined (C_ENABLE_SINGLE_ISR_API)
  ___asm( _FlexCAND_Interrupt:)
  ISR_HANDLER_DEFINITION(CanIsr_3)

#      else
#       if !defined (C_ENABLE_ERROR_POLLING)
  ___asm( _FlexCAND_ErrorInterrupt:)
  ISR_HANDLER_DEFINITION(CanBusOffIsr_3)
#       endif

#       if defined (C_ENABLE_CAN_INTERRUPT)
#        if defined (BRSHW_INTERRUPT_TABLE_GROUP_A) || defined (BRSHW_INTERRUPT_TABLE_GROUP_E) || defined (BRSHW_INTERRUPT_TABLE_GROUP_G)
  ___asm( _FlexCAND_RxFifoInterrupt:)
  ISR_HANDLER_DEFINITION(CanRxFifoIsr_3)

  ___asm( _FlexCAND_MB8To63Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB8To63Isr_3)

#         if defined (C_CAN_MAX_BUFFER_96)
  ___asm( _FlexCAND_MB64To95Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB64To95Isr_3)
#         endif /*C_CAN_MAX_BUFFER_96*/

#        elif defined (BRSHW_INTERRUPT_TABLE_GROUP_B)
  ___asm( _FlexCAND_RxFifoInterrupt:)
  ISR_HANDLER_DEFINITION(CanRxFifoIsr_3)

  ___asm( _FlexCAND_MB8To63Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB8To63Isr_3)

#        else
  ___asm( _FlexCAND_MB0Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB0Isr_3)

  ___asm( _FlexCAND_MB1Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB1Isr_3)

  ___asm( _FlexCAND_MB2Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB2Isr_3)
 
  ___asm( _FlexCAND_MB3Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB3Isr_3)

  ___asm( _FlexCAND_MB4Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB4Isr_3)

  ___asm( _FlexCAND_MB5Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB5Isr_3)

  ___asm( _FlexCAND_MB6Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB6Isr_3)

  ___asm( _FlexCAND_MB7Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB7Isr_3)

  ___asm( _FlexCAND_MB8Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB8Isr_3)

  ___asm( _FlexCAND_MB9Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB9Isr_3)

  ___asm( _FlexCAND_MB10Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB10Isr_3)

  ___asm( _FlexCAND_MB11Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB11Isr_3)

  ___asm( _FlexCAND_MB12Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB12Isr_3)

  ___asm( _FlexCAND_MB13Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB13Isr_3)

  ___asm( _FlexCAND_MB14Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB14Isr_3)

  ___asm( _FlexCAND_MB15Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB15Isr_3)
#        endif /*# else BRSHW_INTERRUPT_TABLE_GROUP_A || BRSHW_INTERRUPT_TABLE_GROUP_E || BRSHW_INTERRUPT_TABLE_GROUP_G*/

#        if defined (BRSHW_INTERRUPT_TABLE_GROUP_F)
  ___asm( _FlexCAND_MB16To31Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB16To31Isr_3)

  ___asm( _FlexCAND_MB32To63Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB32To63Isr_3)
#        endif /*BRSHW_INTERRUPT_TABLE_GROUP_F*/
#       endif /*C_ENABLE_CAN_INTERRUPT*/
#      endif /*else C_ENABLE_SINGLE_ISR_API*/
#     endif /*kCanPhysToLogChannelIndex_3*/

 ASM_COMMENT(/* FlexCAN E */)
#     if defined (kCanPhysToLogChannelIndex_4)
#      if defined (C_ENABLE_SINGLE_ISR_API)
  ___asm( _FlexCANE_Interrupt:)
  ISR_HANDLER_DEFINITION(CanIsr_4)

#      else
#       if !defined (C_ENABLE_ERROR_POLLING)
  ___asm( _FlexCANE_ErrorInterrupt:)
  ISR_HANDLER_DEFINITION(CanBusOffIsr_4)
#       endif

#       if defined (C_ENABLE_CAN_INTERRUPT)
#        if defined (BRSHW_INTERRUPT_TABLE_GROUP_A) || defined (BRSHW_INTERRUPT_TABLE_GROUP_E) || defined (BRSHW_INTERRUPT_TABLE_GROUP_G)
  ___asm( _FlexCANE_RxFifoInterrupt:)
  ISR_HANDLER_DEFINITION(CanRxFifoIsr_4)

  ___asm( _FlexCANE_MB8To63Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB8To63Isr_4)

#         if defined (C_CAN_MAX_BUFFER_96)
  ___asm( _FlexCANE_MB64To95Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB64To95Isr_4)
#         endif /*C_CAN_MAX_BUFFER_96*/

#        else /*BRSHW_INTERRUPT_TABLE_GROUP_A || BRSHW_INTERRUPT_TABLE_GROUP_E*/
  ___asm( _FlexCANE_MB0Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB0Isr_4)

  ___asm( _FlexCANE_MB1Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB1Isr_4)

  ___asm( _FlexCANE_MB2Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB2Isr_4)

  ___asm( _FlexCANE_MB3Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB3Isr_4)

  ___asm( _FlexCANE_MB4Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB4Isr_4)

  ___asm( _FlexCANE_MB5Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB5Isr_4)

  ___asm( _FlexCANE_MB6Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB6Isr_4)

  ___asm( _FlexCANE_MB7Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB7Isr_4)

  ___asm( _FlexCANE_MB8Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB8Isr_4)
 
  ___asm( _FlexCANE_MB9Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB9Isr_4)

  ___asm( _FlexCANE_MB10Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB10Isr_4)

  ___asm( _FlexCANE_MB11Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB11Isr_4)

  ___asm( _FlexCANE_MB12Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB12Isr_4)

  ___asm( _FlexCANE_MB13Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB13Isr_4)

  ___asm( _FlexCANE_MB14Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB14Isr_4)

  ___asm( _FlexCANE_MB15Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB15Isr_4)
#        endif /*# else BRSHW_INTERRUPT_TABLE_GROUP_A || BRSHW_INTERRUPT_TABLE_GROUP_E || BRSHW_INTERRUPT_TABLE_GROUP_G*/

#        if defined (BRSHW_INTERRUPT_TABLE_GROUP_F)
  ___asm( _FlexCANE_MB16To31Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB16To31Isr_4)

  ___asm( _FlexCANE_MB32To63Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB32To63Isr_4)
#        endif /*BRSHW_INTERRUPT_TABLE_GROUP_F*/
#       endif /*C_ENABLE_CAN_INTERRUPT*/
#      endif /*else C_ENABLE_SINGLE_ISR_API*/
#     endif /*kCanPhysToLogChannelIndex_4*/

  ASM_COMMENT(/* FlexCAN F */)
#     if defined (kCanPhysToLogChannelIndex_5)
#      if defined (C_ENABLE_SINGLE_ISR_API)
    ___asm( _FlexCANF_Interrupt:)
    ISR_HANDLER_DEFINITION(CanIsr_5)

#      else
#       if !defined (C_ENABLE_ERROR_POLLING)
      ___asm( _FlexCANF_ErrorInterrupt:)
      ISR_HANDLER_DEFINITION(CanBusOffIsr_5)
#       endif

#       if defined (C_ENABLE_CAN_INTERRUPT)
#        if defined (BRSHW_INTERRUPT_TABLE_GROUP_A) || defined (BRSHW_INTERRUPT_TABLE_GROUP_E) || defined (BRSHW_INTERRUPT_TABLE_GROUP_G)
  ___asm( _FlexCANF_RxFifoInterrupt:)
  ISR_HANDLER_DEFINITION(CanRxFifoIsr_5)

  ___asm( _FlexCANF_MB8To63Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB8To63Isr_5)

#         if defined (C_CAN_MAX_BUFFER_96)
  ___asm( _FlexCANF_MB64To95Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB64To95Isr_5)
#         endif /*C_CAN_MAX_BUFFER_96*/

#        else /*BRSHW_INTERRUPT_TABLE_GROUP_A || BRSHW_INTERRUPT_TABLE_GROUP_E || BRSHW_INTERRUPT_TABLE_GROUP_G*/
  ___asm( _FlexCANF_MB0Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB0Isr_5)

  ___asm( _FlexCANF_MB1Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB1Isr_5)

  ___asm( _FlexCANF_MB2Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB2Isr_5)

  ___asm( _FlexCANF_MB3Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB3Isr_5)

  ___asm( _FlexCANF_MB4Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB4Isr_5)

  ___asm( _FlexCANF_MB5Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB5Isr_5)

  ___asm( _FlexCANF_MB6Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB6Isr_5)

  ___asm( _FlexCANF_MB7Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB7Isr_5)

  ___asm( _FlexCANF_MB8Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB8Isr_5)

  ___asm( _FlexCANF_MB9Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB9Isr_5)

  ___asm( _FlexCANF_MB10Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB10Isr_5)

  ___asm( _FlexCANF_MB11Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB11Isr_5)

  ___asm( _FlexCANF_MB12Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB12Isr_5)

  ___asm( _FlexCANF_MB13Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB13Isr_5)

  ___asm( _FlexCANF_MB14Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB14Isr_5)

  ___asm( _FlexCANF_MB15Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB15Isr_5)
#        endif /*# else BRSHW_INTERRUPT_TABLE_GROUP_A || BRSHW_INTERRUPT_TABLE_GROUP_E || BRSHW_INTERRUPT_TABLE_GROUP_G*/

#        if defined (BRSHW_INTERRUPT_TABLE_GROUP_F)
  ___asm( _FlexCANF_MB16To31Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB16To31Isr_5)

  ___asm( _FlexCANF_MB32To63Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB32To63Isr_5)
#        endif /*BRSHW_INTERRUPT_TABLE_GROUP_F*/
#       endif /*C_ENABLE_CAN_INTERRUPT*/
#      endif /*else C_ENABLE_SINGLE_ISR_API*/
#     endif /*kCanPhysToLogChannelIndex_5*/

  ASM_COMMENT(/* FlexCAN G */)
#     if defined (kCanPhysToLogChannelIndex_6)
#      if defined (C_ENABLE_SINGLE_ISR_API)
    ___asm( _FlexCANG_Interrupt:)
    ISR_HANDLER_DEFINITION(CanIsr_6)

#      else /*C_ENABLE_SINGLE_ISR_API*/
#       if !defined (C_ENABLE_ERROR_POLLING)
  ___asm( _FlexCANG_ErrorInterrupt:)
  ISR_HANDLER_DEFINITION(CanBusOffIsr_6)
#       endif

#       if defined (C_ENABLE_CAN_INTERRUPT)
#        if defined (BRSHW_INTERRUPT_TABLE_GROUP_A) || defined (BRSHW_INTERRUPT_TABLE_GROUP_E) || defined (BRSHW_INTERRUPT_TABLE_GROUP_G)
  ___asm( _FlexCANG_RxFifoInterrupt:)
  ISR_HANDLER_DEFINITION(CanRxFifoIsr_6)

  ___asm( _FlexCANG_MB8To63Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB8To63Isr_6)

#         if defined (C_CAN_MAX_BUFFER_96)
  ___asm( _FlexCANG_MB64To95Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB64To95Isr_6)
#         endif /*C_CAN_MAX_BUFFER_96*/

#        else /*BRSHW_INTERRUPT_TABLE_GROUP_A || BRSHW_INTERRUPT_TABLE_GROUP_E || BRSHW_INTERRUPT_TABLE_GROUP_G*/
  ___asm( _FlexCANG_MB0Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB0Isr_6)

  ___asm( _FlexCANG_MB1Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB1Isr_6)

  ___asm( _FlexCANG_MB2Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB2Isr_6)

  ___asm( _FlexCANG_MB3Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB3Isr_6)

  ___asm( _FlexCANG_MB4Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB4Isr_6)

  ___asm( _FlexCANG_MB5Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB5Isr_6)

  ___asm( _FlexCANG_MB6Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB6Isr_6)

  ___asm( _FlexCANG_MB7Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB7Isr_6)

  ___asm( _FlexCANG_MB8Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB8Isr_6)

  ___asm( _FlexCANG_MB9Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB9Isr_6)

  ___asm( _FlexCANG_MB10Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB10Isr_6)

  ___asm( _FlexCANG_MB11Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB11Isr_6)

  ___asm( _FlexCANG_MB12Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB12Isr_6)

  ___asm( _FlexCANG_MB13Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB13Isr_6)

  ___asm( _FlexCANG_MB14Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB14Isr_6)

  ___asm( _FlexCANG_MB15Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB15Isr_6)
#        endif /*# else BRSHW_INTERRUPT_TABLE_GROUP_A || BRSHW_INTERRUPT_TABLE_GROUP_E || BRSHW_INTERRUPT_TABLE_GROUP_G*/

#        if defined (BRSHW_INTERRUPT_TABLE_GROUP_F)
  ___asm( _FlexCANG_MB16To31Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB16To31Isr_6)

  ___asm( _FlexCANG_MB32To63Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB32To63Isr_6)
#        endif /*BRSHW_INTERRUPT_TABLE_GROUP_F*/
#       endif /*C_ENABLE_CAN_INTERRUPT*/
#      endif /*else C_ENABLE_SINGLE_ISR_API*/
#     endif /*kCanPhysToLogChannelIndex_6*/

  ASM_COMMENT(/* FlexCAN H */)
#     if defined (kCanPhysToLogChannelIndex_7)
#      if defined (C_ENABLE_SINGLE_ISR_API)
  ___asm( _FlexCANH_Interrupt:)
  ISR_HANDLER_DEFINITION(CanIsr_7)

#      else /*C_ENABLE_SINGLE_ISR_API*/
#       if !defined (C_ENABLE_ERROR_POLLING)
  ___asm( _FlexCANH_ErrorInterrupt:)
  ISR_HANDLER_DEFINITION(CanBusOffIsr_7)
#       endif

#       if defined (C_ENABLE_CAN_INTERRUPT)
#        if defined (BRSHW_INTERRUPT_TABLE_GROUP_A) || defined (BRSHW_INTERRUPT_TABLE_GROUP_E) || defined (BRSHW_INTERRUPT_TABLE_GROUP_G)
  ___asm( _FlexCANH_RxFifoInterrupt:)
  ISR_HANDLER_DEFINITION(CanRxFifoIsr_7)

  ___asm( _FlexCANH_MB8To63Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB8To63Isr_7)

#         if defined (C_CAN_MAX_BUFFER_96)
  ___asm( _FlexCANH_MB64To95Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB64To95Isr_7)
#         endif /*C_CAN_MAX_BUFFER_96*/

#        else /*BRSHW_INTERRUPT_TABLE_GROUP_A || BRSHW_INTERRUPT_TABLE_GROUP_E || BRSHW_INTERRUPT_TABLE_GROUP_G*/
  ___asm( _FlexCANH_MB0Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB0Isr_7)

  ___asm( _FlexCANH_MB1Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB1Isr_7)

  ___asm( _FlexCANH_MB2Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB2Isr_7)

  ___asm( _FlexCANH_MB3Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB3Isr_7)

  ___asm( _FlexCANH_MB4Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB4Isr_7)

  ___asm( _FlexCANH_MB5Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB5Isr_7)

  ___asm( _FlexCANH_MB6Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB6Isr_7)

  ___asm( _FlexCANH_MB7Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB7Isr_7)

  ___asm( _FlexCANH_MB8Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB8Isr_7)

  ___asm( _FlexCANH_MB9Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB9Isr_7)

  ___asm( _FlexCANH_MB10Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB10Isr_7)

  ___asm( _FlexCANH_MB11Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB11Isr_7)

  ___asm( _FlexCANH_MB12Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB12Isr_7)

  ___asm( _FlexCANH_MB13Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB13Isr_7)

  ___asm( _FlexCANH_MB14Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB14Isr_7)

  ___asm( _FlexCANH_MB15Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB15Isr_7)
#        endif /*# else BRSHW_INTERRUPT_TABLE_GROUP_A || BRSHW_INTERRUPT_TABLE_GROUP_E || BRSHW_INTERRUPT_TABLE_GROUP_G*/

#        if defined (BRSHW_INTERRUPT_TABLE_GROUP_F)
  ___asm( _FlexCANH_MB16To31Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB16To31Isr_7)

  ___asm( _FlexCANH_MB32To63Interrupt:)
  ISR_HANDLER_DEFINITION(CanMB32To63Isr_7)
#        endif /*BRSHW_INTERRUPT_TABLE_GROUP_F*/
#       endif /*C_ENABLE_CAN_INTERRUPT*/
#      endif /*else C_ENABLE_SINGLE_ISR_API*/
#     endif /*kCanPhysToLogChannelIndex_7*/
#    endif /*BRSHW_USED_CANCELL_DEFAULT*/

#    if defined (BRSHW_USED_CANCELL_MCAN)
#     if defined (kCan_30_McanPhysToLogChannelIndex_0)
  ___asm( _MCAN0_Interrupt:)
  ISR_HANDLER_DEFINITION(Can_30_Mcan_Isr_0)
#     endif /*kCan_30_McanPhysToLogChannelIndex_0*/

#     if defined (kCan_30_McanPhysToLogChannelIndex_1)
  ___asm( _MCAN1_Interrupt:)
  ISR_HANDLER_DEFINITION(Can_30_Mcan_Isr_1)
#     endif /*kCan_30_McanPhysToLogChannelIndex_1*/
#    endif /*BRSHW_USED_CANCELL_MCAN*/
#   endif /*BRSHW_INTERRUPT_TABLE_GROUP_A||BRSHW_INTERRUPT_TABLE_GROUP_B||BRSHW_INTERRUPT_TABLE_GROUP_E||BRSHW_INTERRUPT_TABLE_GROUP_F||BRSHW_INTERRUPT_TABLE_GROUP_G*/

#  endif /*VGEN_ENABLE_CAN_DRV*/

# endif /* Software/Hardware Vector Mode */

# if defined (BRS_COMP_GHS)
  #pragma endasm
# endif
#endif /*BRS_OS_USECASE_BRS&&!BRS_ENABLE_FBL_SUPPORT*/
