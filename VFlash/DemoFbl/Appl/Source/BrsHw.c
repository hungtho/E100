
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
  \file  File:  BrsHw.c
      Project:  Vector Basic Runtime System
       Module:  BrsHw for platform Freescale/ST Mpc57xx
     Template:  This file is reviewed according to zBrs_Template@root[2.02.02]

  \brief Description:  This is the hardware specific code file for Vector Basic Runtime System (BRS).
                       This file supports: see BrsHw_DerivativeList.h

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
  Nam Trinh                     visntr        Vector Informatik GmbH
  Nguyen Le                     vislnn        Vector Informatik GmbH
  Jens Haerer                   visjhr        Vector Informatik GmbH
  Viet Duc Nguyen               visvnn        Vector Informatik GmbH
  Volker Kaiser                 viskvr        Vector Informatik GmbH
  Yves Plaindoux                vispys        Vector Informatik GmbH
  Michael Tiran                 vismin        Vector Informatik GmbH
  Mohammed Seblani              vissmd        Vector Informatik GmbH
  Roland Reinl                  virrro        Vector Informatik GmbH
  Sascha Mauser                 vismaa        Vector Informatik GmbH
  Cyrille Wamba                 viswca        Vector Informatik GmbH
  Derick Beng Yuh               visydg        Vector Informatik GmbH
  Ivo Georgiev                  visivg        Vector Informatik GmbH
  Michael Tiran                 vismin        Vector Informatik GmbH
  Muhammad Suliman              vismun        Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
 ----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Description
  --------  ----------  ------  ---------------------------------------------------------------------------------------
  01.00.00  2015-05-05  vissns  New creation, based on zBrs_Mpc@root[3.09.04],
                                according to template for BrsHw Codestyle 2.0
            2015-07-09  vishan  Added support for Quasar2 and McKinley Cut2
                                Added support for Evalboard VEBN01387
            2015-07-20  visbwa  Review
  01.00.01  2015-08-05  vistir  Added support for MPC5746C
  01.00.02  2015-08-12  vistir  Added support for MPC5746R
  01.00.03  2015-09-15  visntr  Fixed PllInit for MPC5746R (no aux-clock 7), removed include of BrsHw_IsrDef.h
  01.00.04  2015-09-29  visfsn  Added BRSHW_USERMODE_ACCESS_GROUP_B for MPC5746B
  01.00.05  2015-12-09  vislnn  Added SIU_GROUP_H and SIU_GROUP_I (empty, as HW not available yet)
  01.00.06  2015-12-09  visjhr  Added support for PC580020/Quasar2 and VEN01473 (LED + CAN), fixed typo in BrsHw.h,
                                fixed prescaler value for emiosA system timer
  01.00.07  2015-12-14  visjhr  Fixed CAN1,2,3 port config for SIU_GROUP_A, added CAN port config for S32R274
  01.00.08  2015-12-23  visjhr  Finalized S32R support
                        visvnn  Addded support for SPC574K
                        visbwa  Review
  01.00.09  2016-01-14  visvnn  Reworked CAN-pins for SPC574K
  01.00.10  2016-02-23  viskvr  Fixed define-statement for BRSHW_INTERRUPT_TABLE_GROUP_B
  01.00.11  2016-02-29  viskvr  Removed C_ENABLE_CAN_INTERRUPT within BRSHW_INTERRUPT_TABLE_GROUP_B
  01.00.12  2016-03-14  vispys  Fixed wrapper for old DrvCan/DrvLin versions @ SafeContext
  01.00.13  2016-03-22  visbwa  Removed wrong Reset Generation Module (RGM) register definitions,
                                fixed Fr/Lin clock init for BRSHW_FMPLL_GROUP_A_2,
                                fixed PLL0-init within BRSHW_FMPLL_GROUP_A with BRSHW_OPMODES_GROUP_NONE
  01.00.14  2016-03-22  vismin  Added support for PC580000/Quasar0 and VEBN01655
  01.00.15  2016-03-30  visbwa  Fixed DrvCan Pin settings for BRSHW_SIU_GROUP_A (IMUX)
  01.00.16  2016-03-31  vismin  Finalized VEBN01655 support and fixed TIMER_GROUP_B ISR priority
  01.00.17  2016-04-07  visbwa  Fixed CAN Interrupt initialization for BRSHW_INTERRUPT_TABLE_GROUP_D
  01.00.18  2016-04-19  visbwa  Fixed PBRIDGE0_BASE address of BRSHW_USERMODE_ACCESS_GROUP_A
  01.00.19  2016-04-27  visbwa  Added SIU_IMCR for BRSHW_SIU_GROUP_A, added BRSHW_USERMODE_ACCESS_GROUP_C
  01.00.20  2016-04-27  vissmd  FlexRay pins for BRSHW_SIU_GROUP_A verified
  01.01.00  2016-07-01  visbwa  Review according to Brs_Template 2.00.02
  01.01.01  2016-07-04  virrro  Introduced BRSHW_USERMODE_ACCESS_GROUP_A1 (S32R)
  01.01.02  2016-10-21  vismaa  Added support for PC582101/Quasar2e and blinking LED support for HSR165
  01.01.03  2016-11-11  visbwa  Added PortPins for DrvLin ch.6 to ch.9 within BRSHW_SIU_GROUP_E
  01.01.04  2016-11-15  visbwa  Fixed port initialization (SIU_MSCR instead of outdates SIU_PCR)
  01.02.00  2016-12-21  viswca  Introduced TCM support and BrsHw_Ports.h
            2017-01-20  visbwa  Review
  01.02.01  2017-02-01  visbwa  Fixed BrsHwSwitchRunMode() to enter RESET mode if HW booted in SAFE mode
  01.02.02  2017-02-08  visbwa  Added Os_CoreGen7 support (check within header file)
  01.02.03  2017-03-14  visydg  Fixed PLL initialization for MPC5777M within FMPLL_GROUP_A_1,
                                added DrvFr pin configuration for BRSHW_SIU_GROUP_C
  01.02.04  2017-05-12  visbwa  Removed limitation of i within BrsHwConfigureInterruptsAtPowerOn()
  01.03.00  2017-07-07  visivg  Started BrsHw_Ports.h concept according to Brs_Template 2.01.00,
                                fixed support for SPC574Sx
            2017-07-07  visbwa  Review
  01.03.01  2017-07-11  visivg  Fixed BrsHwInitPortConfig()
  01.03.02  2017-07-12  visivg  Reworked embracements within Port helper functions to solve runtime issues
  01.03.03  2017-07-17  visivg  Fixed macro names for port pins and defined BRSHW_PORT_ETH0_MDIO as Input/Output pin
  01.03.04  2017-08-11  vismaa  Added MPC5745R support
  01.03.05  2017-08-14  visivg  Defined BrsHwInitPortConfig() for SIU Group B
  01.04.00  2017-08-28  visivg  Added support for GnuGcc compiler, renamed BRS_COMP_GNU into BRS_COMP_HIGHTEC,
                                enabled Software Vector Mode for IRQ Table Group E
  01.04.01  2017-09-14  virrro  Added BRSHW_USERMODE_ACCESS_GROUP_D
  01.04.02  2017-10-09  virrro  Moved SWT0 + STM OPACR registers into BRSHW_USERMODE_ACCESS_GROUP_A/A1
  01.04.03  2017-10-27  vismin  Fixed PLL Init for BRSHW_SIU_GROUP_B (MPC5777C)
  01.04.04  2017-10-25  vismaa  Enabled all cores for S32R274 in RUN0
  01.04.05  2017-11-14  vismaa  Added new CAN include for use of 2 CAN cells
  01.04.06  2017-11-17  vismaa  Added MCAN support in BrsHwConfigureInterruptsAtPowerOn()
            2017-11-22  visbwa  Review, added configuration check for MCAN configuration
  01.04.07  2018-01-30  visbwa  Removed buggy setting of CGM_AC2_SC and CGM_AC2_DC0 for BRSHW_FMPLL_GROUP_A_3
  01.04.08  2018-02-14  vismun  Moved assembler command redefinition from BrsStartup.c and BrsIntTb.c to BrsHw.h
  01.05.00  2018-03-20  vismaa  Added FBL support (Brs_Template 2.02.01), implemented BrsHwSoftwareResetECU() from FBL
  01.05.01  2018-04-04  visbwa  Fixed MemMap encapsulation of BrsHwPort_SetLevel(),
                                added while-loop to BrsHwSoftwareResetECU()
  01.05.02  2018-04-10  vismaa  Added __eabi() definition for GnuGCC
            2018-07-12  virrro  Added OPACR register setting for BRSHW_USERMODE_ACCESS_GROUP_D and LIN channel 0
  01.05.03  2018-07-25  virrro  Added OPACR register setting for BRSHW_USERMODE_ACCESS_GROUP_D and CAN channel 2
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
  #error "Could not detect DrvMCan channel configuration automatically. Please define here manually, which channel is used within your configuration."
  /*#define kCan_30_McanPhysToLogChannelIndex_0*/
  /*#define kCan_30_McanPhysToLogChannelIndex_1*/
#   endif
#  endif /*BRSHW_USED_CANCELL_MCAN*/
#  if defined (BRSASR_ENABLE_SAFECTXSUPPORT)
  /* Necessary for WRAPPER FOR OLD DRVCAN IMPLEMENTATIONS (previous to MSR4 R11) */
  #include "CanIf_Cfg.h"
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
# if !defined (FR_CHANNEL_A_USED) && !defined (FR_CHANNEL_B_USED)
  #error "Could not detect DrvFr channel configuration automatically. Please define here manually, which channel is used within your configuration."*/
  /*#define FR_CHANNEL_A_USED STD_ON*/
  /*#define FR_CHANNEL_B_USED STD_ON*/
# endif
#endif

#if defined (VGEN_ENABLE_DRVETH__BASEASR)
  #include "Eth.h"
#endif

#if defined (BRS_OS_USECASE_BRS) && !defined (BRS_ENABLE_FBL_SUPPORT)
/*
 * Description: The BrsMain header provides all the necessary interfaces to
 *              the BRS main file (BrsMainExceptionHandler, gbBrsMainIsrMilliSecondFlag).
 *              This file is part of the BRS.
 */
  #include "BrsMain.h"

  /* All ISR function definitions are set within this separate header */
  /*visbwa: do not use this include here. Otherwise, DummyInterrupt mechanism will not work properly */
  /*#include "BrsHw_IsrDef.h"*/
#endif

#if !defined (VGEN_ENABLE_DRVPORT)
  #include "BrsHw_Ports.h"
#endif

#if defined (VGEN_ENABLE_DRVDIO)
# if defined (BRS_ENABLE_SUPPORT_LEDS)          || \
     defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN) || \
     defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  #include "Dio.h"
#  if defined (VGEN_ENABLE_DRVPORT)
  #define BRSHW_PORT_LOGIC_HIGH STD_HIGH
  #define BRSHW_PORT_LOGIC_LOW STD_LOW
#  else
  #error "LED alive mechanism and MCAL does only work proper if DrvPort and DrvDio are used together!"
#  endif
# endif /*BRS_ENABLE_SUPPORT_LEDS||BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN||BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN*/
#else
# if defined (VGEN_ENABLE_DRVPORT)
#  if defined (BRS_ENABLE_SUPPORT_LEDS)          || \
      defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN) || \
      defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  #error "LED alive mechanism and MCAL does only work proper if DrvPort and DrvDio are used together!"
#  endif
# endif /*VGEN_ENABLE_DRVPORT*/
#endif /*VGEN_ENABLE_DRVDIO*/

/**********************************************************************************************************************
  VERSION CHECK
**********************************************************************************************************************/
#if (BRSHW_VERSION != 0x0105u)
  #error "Header and source file are inconsistent!"
#endif
#if (BRSHW_BUGFIX_VERSION != 0x03u)
  #error "Different versions of bugfix in Header and Source used!"
#endif

/**********************************************************************************************************************
  CONFIGURATION CHECK
**********************************************************************************************************************/
#if defined (BRS_COMP_GHS)     

#else
  #error "Unknown compiler specified!"
#endif

/**********************************************************************************************************************
  DEFINITION + MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL VARIABLES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL CONST VARIABLES
**********************************************************************************************************************/
/*
 * Description: These constants are used to propagate the Versions over
 *              module boundaries.The version numbers are BCD coded. E.g. a sub
 *              version of 23 is coded with 0x23, a bug fix version of 9 is
 *              coded 0x09.
 */
uint8 const kBrsHwMainVersion   = (uint8)(BRSHW_VERSION >> 8);
uint8 const kBrsHwSubVersion    = (uint8)(BRSHW_VERSION & 0xFF);
uint8 const kBrsHwBugfixVersion = (uint8)(BRSHW_BUGFIX_VERSION);

/**********************************************************************************************************************
  LOCAL VARIABLES AND LOCAL HW REGISTERS
**********************************************************************************************************************/
/*
 * Description: This counter is used to count the number of nested calls to
 *              disable and restore the state of the global INT enable bit.
 *              Please note: This variable is used only in this file.
 * Values     : 0 if no BrsHwDisableInterrupt is called and INT is allowed by the
 *              BRS. Value > 0 if INT is locked by the BRS interrupt control API.
 */
static uint8 bBrsHwIntDiCounter;

#if defined (BRSHW_ENABLE_ISR_SW_DISPATCHING)
  extern void (*intvect_ExtExceptions[])();
#endif

/**********************************************************************************************************************
  CONTROLLER CONFIGURATION REGISTERS
**********************************************************************************************************************/
/***********************************************/
/* PLL / CGM / RGM registers                   */
/***********************************************/
#if defined (BRSHW_FMPLL_GROUP_A) || defined (BRSHW_FMPLL_GROUP_A_1) || defined (BRSHW_FMPLL_GROUP_A_2) || defined (BRSHW_FMPLL_GROUP_A_3)
# if defined (BRSHW_FMPLL_GROUP_A_1)
  #define BRSHW_FMPLL_GROUP_A BRSHW_FMPLL_GROUP_A_1
# endif
# if defined (BRSHW_FMPLL_GROUP_A_2)
  #define BRSHW_FMPLL_GROUP_A BRSHW_FMPLL_GROUP_A_2
# endif
# if defined (BRSHW_FMPLL_GROUP_A_3)
  #define BRSHW_FMPLL_GROUP_A BRSHW_FMPLL_GROUP_A_3
# endif

  #define FMPLL_BASE_ADDR BRSHW_FMPLL_GROUP_A

  #define PLL0CR   BRSHW_IOS(uint32, FMPLL_BASE_ADDR + 0x00) /* PLL0 Control Register */
  #define PLL0SR   BRSHW_IOS(uint32, FMPLL_BASE_ADDR + 0x04) /* PLL0 Status Register */
  #define PLL0DV   BRSHW_IOS(uint32, FMPLL_BASE_ADDR + 0x08) /* PLL0 Divider Register */
  #define PLL1CR   BRSHW_IOS(uint32, FMPLL_BASE_ADDR + 0x20) /* PLL1 Control Register */
  #define PLL1SR   BRSHW_IOS(uint32, FMPLL_BASE_ADDR + 0x24) /* PLL1 Status Register */
  #define PLL1DV   BRSHW_IOS(uint32, FMPLL_BASE_ADDR + 0x28) /* PLL1 Divider Register */

# if defined (BRSHW_OPMODES_GROUP_A)
  /* Clock Generation Module (CGM) */
#  if defined (BRS_DERIVATIVE_PC580000x) || defined (BRS_DERIVATIVE_PC580002x) || defined (BRS_DERIVATIVE_PC580003x) || defined (BRS_DERIVATIVE_PC582101) 
  #define CGM_BASE_ADDR 0xFFFF0000
#  else
  #define CGM_BASE_ADDR 0xFFFB0000
#  endif

  #define CGM_AC0_SC   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0800)  /* Auxiliary Clock 0 Select Control Register */
  #define CGM_AC0_SS   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0804)  /* Auxiliary Clock 0 Select Status Register */
  #define CGM_AC0_DC0  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0808)  /* Auxiliary Clock 0 Divider 0 Configuration Register */
  #define CGM_AC0_DC1  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x080C)  /* Auxiliary Clock 0 Divider 1 Configuration Register */
  #define CGM_AC0_DC2  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0810)  /* Auxiliary Clock 0 Divider 2 Configuration Register */
  #define CGM_AC0_DC3  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0814)  /* Auxiliary Clock 0 Divider 3 Configuration Register */
  #define CGM_AC0_DC4  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0818)  /* Auxiliary Clock 0 Divider 4 Configuration Register */
  #define CGM_AC0_DC5  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x081C)  /* Auxiliary Clock 0 Divider 5 Configuration Register */

  #define CGM_AC1_SC   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0820)  /* Auxiliary Clock 1 Select Control Register */
  #define CGM_AC1_SS   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0824)  /* Auxiliary Clock 1 Select Status Register */
  #define CGM_AC1_DC0  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0828)  /* Auxiliary Clock 1 Divider 0 Configuration */
  #define CGM_AC1_DC1  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x082C)  /* Auxiliary Clock 1 Divider 1 Configuration */

  #define CGM_AC2_SC   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0840)  /* Auxiliary Clock 2 Select Control Register */
  #define CGM_AC2_SS   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0844)  /* Auxiliary Clock 2 Select Status Register */
  #define CGM_AC2_DC0  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0848)  /* Auxiliary Clock 2 Divider Control Register */

  #define CGM_AC3_SC   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0860)  /* Auxiliary Clock 3 Select Control Register */
  #define CGM_AC3_SS   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0864)  /* Auxiliary Clock 3 Select Status Register */

  #define CGM_AC4_SC   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0880)  /* Auxiliary Clock 4 Select Control Register */
  #define CGM_AC5_SC   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x08A0)  /* Auxiliary Clock 5 Select Control Register */
  #define CGM_AC6_SC   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x08C0)  /* Auxiliary Clock 6 Select Control Register */
  #define CGM_AC6_DC0  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x08C8)  /* Auxiliary Clock 6 Divider Configuration Register */
  #define CGM_AC7_SC   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x08E0)  /* Auxiliary Clock 7 Select Control Register */
  #define CGM_AC7_DC0  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x08E8)  /* Auxiliary Clock 7 Divider Configuration Register */
  #define CGM_AC8_SC   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0900)  /* Auxiliary Clock 8 Select Control Register */
  #define CGM_AC8_DC0  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0908)  /* Auxiliary Clock 8 Divider Configuration Register */
  #define CGM_AC9_SC   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0920)  /* Auxiliary Clock 9 Select Control Register */
  #define CGM_AC9_DC0  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0928)  /* Auxiliary Clock 9 Divider Configuration Register */
  #define CGM_AC15_SC  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x09E0)  /* Auxiliary Clock 15 Select Control Register */
  #define CGM_AC15_DC0 BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x09E8)  /* Auxiliary Clock 15 Divider Configuration Register */

  #define CGM_SC_SS    BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x07E4)  /* System Clock Select Status Register */
  #define CGM_SC_DC0   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x07E8)  /* System Clock Divider 0 Configuration Register */
  #define CGM_SC_DC1   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x07EC)  /* System Clock Divider 1 Configuration Register */
  #define CGM_SC_DC2   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x07F0)  /* Core2 System Clock Divider Configuration Register */
  #define CGM_SC_DC3   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x07F4)
  #define CGM_SC_DC4   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x07F8)

  #define CGM_SC_DIV_RC     BRSHW_IOS(uint32, CGM_BASE_ADDR+0x7D0)
  #define CGM_DIV_UPD_TYPE  BRSHW_IOS(uint32, CGM_BASE_ADDR+0x7D4)
  #define CGM_DIV_UPD_TRIG  BRSHW_IOS(uint32, CGM_BASE_ADDR+0x7D8)
  #define CGM_DIV_UPD_STAT  BRSHW_IOS(uint32, CGM_BASE_ADDR+0x7DC)
# endif /*BRSHW_OPMODES_GROUP_A*/

#  if defined (BRSHW_OPMODES_GROUP_B)
  /* Clock Generation Module (CGM) */
  #define CGM_BASE_ADDR 0xFFFB0600

  #define CGM_AC0_SC   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0200)  /* Auxiliary Clock 0 Select Control Register */
  #define CGM_AC0_SS   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0204)  /* Auxiliary Clock 0 Select Status Register */
  #define CGM_AC0_DC0  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0208)  /* Auxiliary Clock 0 Divider 0 Configuration Register */
  #define CGM_AC0_DC1  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x020C)  /* Auxiliary Clock 0 Divider 1 Configuration Register */
  #define CGM_AC0_DC2  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0210)  /* Auxiliary Clock 0 Divider 2 Configuration Register */
  #define CGM_AC0_DC3  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0214)  /* Auxiliary Clock 0 Divider 3 Configuration Register */
  #define CGM_AC0_DC4  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0218)  /* Auxiliary Clock 0 Divider 4 Configuration Register */

  #define CGM_AC1_SC   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0220)  /* Auxiliary Clock 1 Select Control Register */
  #define CGM_AC1_SS   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0224)  /* Auxiliary Clock 1 Select Status Register */
  #define CGM_AC1_DC0  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0228)  /* Auxiliary Clock 1 Divider 0 Configuration */

  #define CGM_AC2_DC0  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0248)  /* Auxiliary Clock 2 Divider 0 Control Register */
  #define CGM_AC2_DC1  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x024C)  /* Auxiliary Clock 2 Divider 1 Control Register */

  #define CGM_AC3_SC   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0260)  /* Auxiliary Clock 3 Select Control Register */
  #define CGM_AC3_SS   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0264)  /* Auxiliary Clock 3 Select Status Register */

  #define CGM_AC4_SC   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0280)  /* Auxiliary Clock 4 Select Control Register */
  #define CGM_AC4_SS   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0284)  /* Auxiliary Clock 4 Select Control Register */

  #define CGM_AC5_DC0  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x02A8)  /* Auxiliary Clock 5 Divider 0 Control Register */
  #define CGM_AC5_DC1  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x02AC)  /* Auxiliary Clock 5 Divider 1 Control Register */
  #define CGM_AC5_DC2  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x02B0)  /* Auxiliary Clock 5 Divider 2 Control Register */

  #define CGM_AC6_SC   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x02C0)  /* Auxiliary Clock 6 Select Control Register */
  #define CGM_AC6_SS   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x02C4)  /* Auxiliary Clock 6 Select Status Register */
  #define CGM_AC6_DC0  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x02C8)  /* Auxiliary Clock 6 Divider Configuration Register */

  #define CGM_AC7_SC   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x02E0)  /* Auxiliary Clock 7 Select Control Register */
  #define CGM_AC7_SS   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x02E4)  /* Auxiliary Clock 7 Select Status Register */
  #define CGM_AC7_DC0  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x02E8)  /* Auxiliary Clock 7 Divider Configuration Register */

  #define CGM_AC8_SC   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0300)  /* Auxiliary Clock 8 Select Control Register */
  #define CGM_AC8_SS   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0304)  /* Auxiliary Clock 8 Select Status Register */
  #define CGM_AC8_DC0  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0308)  /* Auxiliary Clock 8 Divider Configuration Register */

  #define CGM_AC9_SC   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0320)  /* Auxiliary Clock 9 Select Control Register */
  #define CGM_AC9_SS   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0324)  /* Auxiliary Clock 9 Select Status Register */
  #define CGM_AC9_DC0  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0328)  /* Auxiliary Clock 9 Divider Configuration Register */

  #define CGM_AC10_SC  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0340)  /* Auxiliary Clock 10 Select Control Register */
  #define CGM_AC10_SS  BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0344)  /* Auxiliary Clock 10 Select Status Register */
  #define CGM_AC10_DC0 BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x0348)  /* Auxiliary Clock 10 Divider Configuration Register */

  #define CGM_SC_SS    BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x01E4)  /* System Clock Select Status Register */
  #define CGM_SC_DC0   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x01E8)  /* System Clock Divider 0 Configuration Register */
  #define CGM_SC_DC1   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x01EC)  /* System Clock Divider 1 Configuration Register */
  #define CGM_SC_DC2   BRSHW_IOS(uint32, CGM_BASE_ADDR + 0x01F0)  /* System Clock Divider 2 Configuration Register */

  #define CGM_SC_DIV_RC     BRSHW_IOS(uint32, CGM_BASE_ADDR+0x1D0)
  #define CGM_DIV_UPD_TYPE  BRSHW_IOS(uint32, CGM_BASE_ADDR+0x1D4)
  #define CGM_DIV_UPD_TRIG  BRSHW_IOS(uint32, CGM_BASE_ADDR+0x1D8)
  #define CGM_DIV_UPD_STAT  BRSHW_IOS(uint32, CGM_BASE_ADDR+0x1DC)
# endif /*BRSHW_OPMODES_GROUP_B*/

#elif defined (BRSHW_FMPLL_GROUP_B)
  #define FMPLL_BASE_ADDR BRSHW_FMPLL_GROUP_B
  #define PLL0CR   BRSHW_IOS(uint32, FMPLL_BASE_ADDR+0x20) /* PLL0 Control Register */
  #define PLL0DV   BRSHW_IOS(uint32, FMPLL_BASE_ADDR+0x28) /* PLL0 Divider Register */
  #define PLLCAL3  BRSHW_IOS(uint32, FMPLL_BASE_ADDR+0x18)
  #define PLLFD    BRSHW_IOS(uint32, FMPLL_BASE_ADDR+0x30)

# if defined (BRSHW_OPMODES_GROUP_A)
  /* Clock Generation Module */
  #define CGM_BASE_ADDR   0xFFFB0000
  #define CGM_SC_DC       BRSHW_IOS(uint32, CGM_BASE_ADDR+0x7E8)   /* System Clock Divider Configuration Register */
  #define CGM_SC_DC2      BRSHW_IOS(uint32, CGM_BASE_ADDR+0x7F0)   /* Core2 System Clock Divider Configuration Register */
  #define CGM_AC0_SC      BRSHW_IOS(uint32, CGM_BASE_ADDR+0x800)   /* Auxiliary Clock 0 Select Control Register */
  #define CGM_AC0_DC0     BRSHW_IOS(uint32, CGM_BASE_ADDR+0x808)   /* Auxiliary Clock 0 Divider Control Register */
  #define CGM_AC0_DC4     BRSHW_IOS(uint32, CGM_BASE_ADDR+0x818)   /* Auxiliary Clock 0 Divider 4 Control Register */
  #define CGM_AC3_SC      BRSHW_IOS(uint32, CGM_BASE_ADDR+0x860)   /* Auxiliary Clock 3 Select Control Register */
  #define CGM_AC4_SC      BRSHW_IOS(uint32, CGM_BASE_ADDR+0x880)   /* Auxiliary Clock 4 Select Control Register */

#  if (MPC5748G_CUT == 1)
  #define CGM_AC5_SC      BRSHW_IOS(uint32, CGM_BASE_ADDR+0x8A0)   /* Auxiliary Clock 5 Select Control Register MPC5748G Cut1 */
#  else
  #define CGM_AC5_SC      BRSHW_IOS(uint32, CGM_BASE_ADDR+0x1C0)   /* Auxiliary Clock 5 Select Control Register */
#  endif

  #define CGM_AC6_SC      BRSHW_IOS(uint32, CGM_BASE_ADDR+0x8C0)   /* Auxiliary Clock 6 Select Control Register */
  #define CGM_AC7_SC      BRSHW_IOS(uint32, CGM_BASE_ADDR+0x8E0)   /* Auxiliary Clock 7 Select Control Register */
  #define CGM_AC8_SC      BRSHW_IOS(uint32, CGM_BASE_ADDR+0x900)   /* Auxiliary Clock 7 Select Control Register */
  #define CGM_AC8_DC0     BRSHW_IOS(uint32, CGM_BASE_ADDR+0x908)   /* Auxiliary Clock 7 Select Control Register */
# endif /*BRSHW_OPMODES_GROUP_A*/

#elif defined (BRSHW_FMPLL_GROUP_NONE)

#else
  #error "Unknown PLL Group. Please check your derivative settings within BrsHw_DerivativeList.h."
#endif

/***********************************************/
/* SIU registers                               */
/***********************************************/
#if defined (BRSHW_SIU_GROUP_A)
  #define SIU_BASE_ADDR BRSHW_SIU_GROUP_A
#elif defined (BRSHW_SIU_GROUP_B)
  #define SIU_BASE_ADDR BRSHW_SIU_GROUP_B
#elif defined (BRSHW_SIU_GROUP_C)
  #define SIU_BASE_ADDR BRSHW_SIU_GROUP_C
#elif defined (BRSHW_SIU_GROUP_D_1)
  #define SIU_BASE_ADDR BRSHW_SIU_GROUP_D_1
#elif defined (BRSHW_SIU_GROUP_E)
  #define SIU_BASE_ADDR BRSHW_SIU_GROUP_E
#elif defined (BRSHW_SIU_GROUP_F)
  #define SIU_BASE_ADDR BRSHW_SIU_GROUP_F
#elif defined (BRSHW_SIU_GROUP_G)
  #define SIU_BASE_ADDR BRSHW_SIU_GROUP_G
#elif defined (BRSHW_SIU_GROUP_H)
  #define SIU_BASE_ADDR BRSHW_SIU_GROUP_H
#elif defined (BRSHW_SIU_GROUP_I)
  #define SIU_BASE_ADDR BRSHW_SIU_GROUP_I
#else
  #error "Unknown SIU Group. Please check your derivative settings within BrsHw_DerivativeList.h."
#endif

#if defined (BRSHW_SIU_GROUP_B)
  #define BRSHW_MSCR_SOURCE_SIGNAL_SELECT_1      0x0400
  #define BRSHW_MSCR_SOURCE_SIGNAL_SELECT_2      0x0800
  #define BRSHW_MSCR_SOURCE_SIGNAL_SELECT_3      0x0C00
  #define BRSHW_MSCR_SOURCE_SIGNAL_SELECT_4      0x1000
  #define BRSHW_PCR_PIN_ASSIGNMENT_GPIO_INPUT    0x0100
  #define BRSHW_PCR_PIN_ASSIGNMENT_GPIO_OUTPUT   0x0200
  #define BRSHW_PCR_USE_WEAK_PULLUP              0x0003
  #define BRSHW_PCR_USE_WEAK_PULLDOWN            0x0002

  #define SIU_MSCR(x) BRSHW_IOS(uint16, SIU_BASE_ADDR + 0x40 + (x*2))    /* Pad Configuration Register */
  #define SIU_GPDO(x) BRSHW_IOS(uint8,  SIU_BASE_ADDR + 0x600 + x)       /* General Purpose Data Output Register */
  #define SIU_GPDI(x) BRSHW_IOS(uint8,  SIU_BASE_ADDR + 0x800 + x)       /* General Purpose Data Input Register */
  #define SIU_PSMI(x) BRSHW_IOS(uint8, SIU_BASE_ADDR + 0x500 + x)        /* Pad selection for multiplexed Inputs */
  #define SIU_RSR     BRSHW_IOS(uint32, SIU_BASE_ADDR + 0x0C)            /* Reset Status Register */
  #define SIU_SRCR    BRSHW_IOS(uint32, SIU_BASE_ADDR + 0x10)            /* System Reset Control Register */
  #define SIU_EISR    BRSHW_IOS(uint32, SIU_BASE_ADDR + 0x14)            /* ext. IRQ status register */
  #define SIU_DIRER   BRSHW_IOS(uint32, SIU_BASE_ADDR + 0x18)            /* ext. IRQ enable register */
  #define SIU_IFEER   BRSHW_IOS(uint32, SIU_BASE_ADDR + 0x2c)            /* ext. IRQ: falling edge enable register */
  #define SIU_SYSCLK  BRSHW_IOS(uint32, SIU_BASE_ADDR + 0x9A0)           /* System Clock Register */
  #define SIU_IMUX(x) BRSHW_IOS(uint32, SIU_BASE_ADDR + 0x1200 + (4*x))  /* Input Multiplexing Registers */

#else /*BRSHW_SIU_GROUP_B*/
  #define BRSHW_PCR_PIN_ASSIGNMENT_GPIO_INPUT    0x00080000
# if (MPC5748G_CUT == 1)
  #define BRSHW_PCR_PIN_ASSIGNMENT_GPIO_OUTPUT   0x02000000
# else
  #define BRSHW_PCR_PIN_ASSIGNMENT_GPIO_OUTPUT   0x32000000 /* Output Impedance - very strong */
# endif
  #define BRSHW_MSCR_SOURCE_SIGNAL_SELECT_0      0x00000000
  #define BRSHW_MSCR_SOURCE_SIGNAL_SELECT_1      0x00000001
  #define BRSHW_MSCR_SOURCE_SIGNAL_SELECT_2      0x00000002
  #define BRSHW_MSCR_SOURCE_SIGNAL_SELECT_3      0x00000003
  #define BRSHW_MSCR_SOURCE_SIGNAL_SELECT_4      0x00000004
  #define BRSHW_MSCR_SOURCE_SIGNAL_SELECT_5      0x00000005
  #define BRSHW_MSCR_SOURCE_SIGNAL_SELECT_8      0x00000008
  #define BRSHW_MSCR_SOURCE_SIGNAL_SELECT_9      0x00000009

  #define SIU_MSCR(x)  BRSHW_IOS(uint32, SIU_BASE_ADDR + 0x240 + (4*x))  /* SIUL2 Multiplexed Singnal Configuration Register */
# if defined (BRSHW_SIU_GROUP_A)
  #define SIU_IMCR(x)  BRSHW_IOS(uint32, SIU_BASE_ADDR + 0xA40 + (4*x))  /* SIUL2 Input Multiplexed Singnal Configuration Register*/
# endif
  #define SIU_GPDO(x)  BRSHW_IOS(uint8, SIU_BASE_ADDR + 0x1300 + x)      /* SIUL2 GPIO Pad Data Out */
  #define SIU_GPDI(x)  BRSHW_IOS(uint8, SIU_BASE_ADDR + 0x1500 + x)      /* SIUL2 GPIO Pad Data In */
  #define SIU_EISR     BRSHW_IOS(uint32, SIU_BASE_ADDR + 0x10)           /* ext. IRQ status register */
  #define SIU_DIRER    BRSHW_IOS(uint32, SIU_BASE_ADDR + 0x18)           /* ext. IRQ enable register */
  #define SIU_IFEER    BRSHW_IOS(uint32, SIU_BASE_ADDR + 0x30)           /* ext. IRQ: falling edge enable register */
  #define SIU_MIDR1    BRSHW_IOS(uint32, SIU_BASE_ADDR + 0x04)
# if defined (BRSHW_SIU_GROUP_D_2)
  #define SIU_B_MSCR(x)  BRSHW_IOS(uint32, BRSHW_SIU_GROUP_D_2 + 0x240 + (4*x))  /* SIUL2 Multiplexed Single Configuration */
  #define SIU_B_GPDO(x)  BRSHW_IOS(uint8,  BRSHW_SIU_GROUP_D_2 + 0x1300 + x)     /* SIUL2 GPIO Pad Data Out */
  #define SIU_B_GPDI(x)  BRSHW_IOS(uint8,  BRSHW_SIU_GROUP_D_2 + 0x1500 + x)     /* SIUL2 GPIO Pad Data In */
# endif
#endif /*else BRSHW_SIU_GROUP_B*/

/***********************************************/
/* Mode Entry Module registers (MC_ME)         */
/***********************************************/
#if defined (BRSHW_OPMODES_GROUP_A) || defined (BRSHW_OPMODES_GROUP_B)
# if defined (BRSHW_OPMODES_GROUP_A)
  #define ME_BASE_ADDR      BRSHW_OPMODES_GROUP_A
# elif defined (BRSHW_OPMODES_GROUP_B)
  #define ME_BASE_ADDR      BRSHW_OPMODES_GROUP_B
# endif

  #define ME_GS         BRSHW_IOS(uint32, ME_BASE_ADDR + 0x00)          /* Global Status Register */
  #define ME_MCTL       BRSHW_IOS(uint32, ME_BASE_ADDR + 0x004)         /* Mode Control Register */
  #define ME_ME         BRSHW_IOS(uint32, ME_BASE_ADDR + 0x008)         /* Mode Enable Register */
  #define ME_IS         BRSHW_IOS(uint32, ME_BASE_ADDR + 0x00C)         /* Interrupt Status Register */
  #define ME_DRUN_MC    BRSHW_IOS(uint32, ME_BASE_ADDR + 0x02C)         /* DRUN Mode Configuration Registers */
  #define ME_RUN_MC(x)  BRSHW_IOS(uint32, ME_BASE_ADDR + 0x030 + 4*x)   /* RUN0..x Mode Configuration Registers */
  #define ME_RUN_PC(x)  BRSHW_IOS(uint32, ME_BASE_ADDR + 0x080 + 4*x)   /* Run Peripheral Configuration Register 0..x */
  #define ME_LP_PC(x)   BRSHW_IOS(uint32, ME_BASE_ADDR + 0x0A0 + 4*x)   /* Low-Power Peripheral Configuration Register 1 */
  #define ME_PCTL(x)    BRSHW_IOS(uint8, (ME_BASE_ADDR + 0x0C0 + x))    /* Peripheral Control Registers */
  #define ME_CCTL(x)    BRSHW_IOS(uint16, (ME_BASE_ADDR + 0x1C4 + 2*x)) /* Core Control Register */

#elif defined (BRSHW_OPMODES_GROUP_NONE)

#else
  #error "Unknown Operation Mode Group. Please check your derivative settings within BrsHw_DerivativeList.h."
#endif

#if defined (BRSHW_ENABLE_TIMER_INTERRUPT)
/***********************************************/
/*  Timer registers                            */
/***********************************************/
# if defined (BRSHW_TIMER_GROUP_A)
  /* PIT */
  #define PIT_BASE_ADDR BRSHW_TIMER_GROUP_A
  #define PIT_MCR    BRSHW_IOS(uint32, PIT_BASE_ADDR + 0x0000 ) /* PIT Module Control Register   */
  #define PIT_LDVAL0 BRSHW_IOS(uint32, PIT_BASE_ADDR + 0x0100 ) /* Timer0 Load Value Register    */
  #define PIT_CVAL0  BRSHW_IOS(uint32, PIT_BASE_ADDR + 0x0104 ) /* Current Timer0 Value Register */
  #define PIT_TCTRL0 BRSHW_IOS(uint32, PIT_BASE_ADDR + 0x0108 ) /* Timer0 Control Register       */
  #define PIT_TFLG0  BRSHW_IOS(uint32, PIT_BASE_ADDR + 0x010C ) /* Timer0 Flag Register          */

# elif defined (BRSHW_TIMER_GROUP_B)
  /* eMIOS_A (Channel 16) */
  #define EMIOS_BASE_ADDR BRSHW_TIMER_GROUP_B
  #define EMIOS_MCR    BRSHW_IOS(uint32, EMIOS_BASE_ADDR + 0x0000 ) /* eMIOS_A Module Configuration Register */
  #define EMIOS_CADR0  BRSHW_IOS(uint32, EMIOS_BASE_ADDR + 0x0220 ) /* eMIOS_A Channel 16 Data Register A */
  #define EMIOS_CCNTR0 BRSHW_IOS(uint32, EMIOS_BASE_ADDR + 0x0228 ) /* eMIOS_A Channel 16 Counter Register */
  #define EMIOS_CCR0   BRSHW_IOS(uint32, EMIOS_BASE_ADDR + 0x022C ) /* eMIOS_A Channel 16 Control Register */
  #define EMIOS_CSR0   BRSHW_IOS(uint32, EMIOS_BASE_ADDR + 0x0230 ) /* eMIOS_A Channel 16 Status Register */

# elif defined (BRSHW_TIMER_GROUP_NONE)

# else
  #error "Unknown Timer Group. Please check your derivative settings within BrsHw_DerivativeList.h."
# endif /*BRSHW_TIMER_GROUP_x*/
#endif /*BRSHW_ENABLE_TIMER_INTERRUPT*/

/***********************************************/
/* Watchdog registers                          */
/***********************************************/
#if defined (BRSHW_WATCHDOG_GROUP_A)
  #define SWT_BASE_ADDR  BRSHW_WATCHDOG_GROUP_A
  #define SWT_CR         BRSHW_IOS(uint32, SWT_BASE_ADDR + 0x00 )          /* SWT Control Register */
  #define SWT_SR         BRSHW_IOS(uint32, SWT_BASE_ADDR + 0x10 )          /* SWT Service Register */

#elif defined (BRSHW_WATCHDOG_GROUP_B)
  #define SWT_BASE_ADDR  BRSHW_WATCHDOG_GROUP_B
  #define SWT_CR         BRSHW_IOS(uint32, SWT_BASE_ADDR + 0x00 )          /* SWT1 Control Register */
  #define SWT_SR         BRSHW_IOS(uint32, SWT_BASE_ADDR + 0x10 )          /* SWT1 Service Register */
  #define SWT2_CR        BRSHW_IOS(uint32, SWT_BASE_ADDR + 0x4000 + 0x00 ) /* SWT2 Control Register */
  #define SWT2_SR        BRSHW_IOS(uint32, SWT_BASE_ADDR + 0x4000 + 0x10 ) /* SWT2 Service Register */

#elif defined (BRSHW_WATCHDOG_GROUP_C)
  #define SWT_BASE_ADDR  BRSHW_WATCHDOG_GROUP_C
  #define SWT_CR         BRSHW_IOS(uint32, SWT_BASE_ADDR + 0x00 )          /* SWT0 Control Register */
  #define SWT_SR         BRSHW_IOS(uint32, SWT_BASE_ADDR + 0x10 )          /* SWT0 Service Register */
  #define SWT2_CR        BRSHW_IOS(uint32, SWT_BASE_ADDR + 0x8000 + 0x00 ) /* SWT2 Control Register */
  #define SWT2_SR        BRSHW_IOS(uint32, SWT_BASE_ADDR + 0x8000 + 0x10 ) /* SWT2 Service Register */

  #define SWT3_CR        BRSHW_IOS(uint32, SWT_BASE_ADDR + 0xC000 + 0x00 ) /* SWT3 Control Register */
  #define SWT3_SR        BRSHW_IOS(uint32, SWT_BASE_ADDR + 0xC000 + 0x10 ) /* SWT3 Service Register */

#elif defined (BRSHW_WATCHDOG_GROUP_NONE)

#else
  #error "Unknown Watchdog Group. Please check your derivative settings within BrsHw_DerivativeList.h."
#endif /*BRSHW_WATCHDOG_GROUP_x*/

#if defined (BRS_OS_USECASE_BRS)
/***********************************************/
/*  Interrupt Controller registers (INTC)      */
/***********************************************/
# if defined (BRSHW_INTERRUPT_TABLE_GROUP_A) || defined (BRSHW_INTERRUPT_TABLE_GROUP_C) || defined (BRSHW_INTERRUPT_TABLE_GROUP_E) || defined (BRSHW_INTERRUPT_TABLE_GROUP_F) || defined (BRSHW_INTERRUPT_TABLE_GROUP_G)
  #define INTC_BASE_ADDR    0xFC040000
# elif defined (BRSHW_INTERRUPT_TABLE_GROUP_B)
  #define INTC_BASE_ADDR    0xFFF48000
# elif defined (BRSHW_INTERRUPT_TABLE_GROUP_D)
  #define INTC_BASE_ADDR    0xFFF08000

# else
  #error "Unknown Interrupt Table Group. Please check your derivative settings within BrsHw_DerivativeList.h."
# endif

# if defined (BRSHW_INTERRUPT_TABLE_GROUP_A) || defined (BRSHW_INTERRUPT_TABLE_GROUP_C) || defined (BRSHW_INTERRUPT_TABLE_GROUP_D) || defined (BRSHW_INTERRUPT_TABLE_GROUP_E) || defined (BRSHW_INTERRUPT_TABLE_GROUP_G) 
  #define INTC_MCR          BRSHW_IOS(uint32, INTC_BASE_ADDR)
  #define INTC_CPR_0        BRSHW_IOS(uint32, INTC_BASE_ADDR + 0x10 )       /* Current Priority Register for Processor0 */
  #define INTC_CPR_1        BRSHW_IOS(uint32, INTC_BASE_ADDR + 0x14 )       /* Current Priority Register for Processor1 */
  #define INTC_CPR_2        BRSHW_IOS(uint32, INTC_BASE_ADDR + 0x18 )       /* Current Priority Register for Processor2 */
  #define INTC_CPR_3        BRSHW_IOS(uint32, INTC_BASE_ADDR + 0x1C )       /* Current Priority Register for Processor3 */
  #define INTC_ACKR_0       BRSHW_IOS(uint32, INTC_BASE_ADDR + 0x20)        /* Interrupt Acknowledge Register for Processor0 */
  #define INTC_ACKR_1       BRSHW_IOS(uint32, INTC_BASE_ADDR + 0x24)        /* Interrupt Acknowledge Register for Processor1 */
  #define INTC_ACKR_2       BRSHW_IOS(uint32, INTC_BASE_ADDR + 0x28)        /* Interrupt Acknowledge Register for Processor2 */
  #define INTC_PSR(x)       BRSHW_IOS(uint16, INTC_BASE_ADDR + 0x60 + 2*x) /* Priority Select Register */
# endif

# if defined (BRSHW_INTERRUPT_TABLE_GROUP_B)
  #define INTC_MCR          BRSHW_IOS(uint32, INTC_BASE_ADDR + 0x00 )     /* INTC Module Configuration Register */
  #define INTC_CPR_0        BRSHW_IOS(uint32, INTC_BASE_ADDR + 0x08 )     /* INTC Current Priority Register for processor0 */
  #define INTC_CPR_1        BRSHW_IOS(uint32, INTC_BASE_ADDR + 0x0C )     /* INTC Current Priority Register for processor1 */
  #define INTC_PSR(x)       BRSHW_IOS(uint8, INTC_BASE_ADDR + 0x0040 + x) /* Priority Select Register */
# endif

# if defined (BRSHW_INTERRUPT_TABLE_GROUP_F)
  #define INTC_MCR          BRSHW_IOS(uint32, INTC_BASE_ADDR)
  #define INTC_CPR_0        BRSHW_IOS(uint32, INTC_BASE_ADDR + 0x10)        /* Current Priority Register for Processor0 */
  #define INTC_CPR_1        BRSHW_IOS(uint32, INTC_BASE_ADDR + 0x14)        /* Current Priority Register for Processor1 */
  #define INTC_CPR_2        BRSHW_IOS(uint32, INTC_BASE_ADDR + 0x18)        /* Current Priority Register for Processor2 */
  #define INTC_CPR_3        BRSHW_IOS(uint32, INTC_BASE_ADDR + 0x1C)        /* Current Priority Register for Processor3 */
  #define INTC_ACKR_0       BRSHW_IOS(uint32, INTC_BASE_ADDR + 0x20)        /* Interrupt Acknowledge Register for Processor0 */
  #define INTC_ACKR_1       BRSHW_IOS(uint32, INTC_BASE_ADDR + 0x24)        /* Interrupt Acknowledge Register for Processor1 */
  #define INTC_ACKR_2       BRSHW_IOS(uint32, INTC_BASE_ADDR + 0x28)        /* Interrupt Acknowledge Register for Processor2 */
  #define INTC_ACKR_3       BRSHW_IOS(uint32, INTC_BASE_ADDR + 0x2C)        /* Interrupt Acknowledge Register for Processor3 */
  #define INTC_PSR(x)       BRSHW_IOS(uint16, INTC_BASE_ADDR + 0x60 + 2*x)  /* Priority Select Register */
# endif
#endif /*BRS_OS_USECASE_BRS*/

/****************************************************/
/*  Reset Genration Module  */
/****************************************************/
#define MC_RGM_BASE 0xFFFA8000
# define RGM_FRET   BRSHW_IOS(uint8, MC_RGM_BASE + 0x604)            /* Functional Reset Escalation Threshold Register */

#if !defined (BRS_OS_USECASE_BRS)
# if defined (BRSASR_ENABLE_SAFECTXSUPPORT)
/****************************************************/
/*  UserMode Access Group (UAA-Bit + PACR + OPACR)  */
/****************************************************/
#  if defined (BRSHW_USERMODE_ACCESS_GROUP_A) || defined (BRSHW_USERMODE_ACCESS_GROUP_A1)
  /***************************************************************/
  /* Platform / Off-platform peripheral access control registers */
  /***************************************************************/
  #define PBRIDGE0_BASE 0xFC000000
  #define PBRIDGE1_BASE 0xF8000000

  /* PBRIDGE0 OPACR15 SIUL */
  #define O_PACR_REGISTER_SIUL_ADDR      BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x144)
  #define O_PACR_REGISTER_SIUL_VALUE     0xFFFFFFF0
  /* PBRIDGE0 OPACR30 PIT */
  #define O_PACR_REGISTER_PIT_ADDR       BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x14C)
  #define O_PACR_REGISTER_PIT_VALUE      0xFFFFFF0F

  /* PBRIDGE0 PACR26/PACR27/PACR28 - STM */
  #define O_PACR_REGISTER_STM_ADDR       BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x10C)
  #define O_PACR_REGISTER_STM_VALUE      0xFF000FFF /* Enable STM0, STM1 and STM 2 */

  /* PBRIDGE0 OPACR36 - DMAMUX_0 */
  #define O_PACR_REGISTER_DMA_MUX_0_ADDR   BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x150)
  #define O_PACR_REGISTER_DMA_MUX_0_VALUE  0xFFFF0FFF

  /* PBRIDGE0 OPACR146 - DMAMUX_1 */
  #define O_PACR_REGISTER_DMA_MUX_1_ADDR   BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x188)
  #define O_PACR_REGISTER_DMA_MUX_1_VALUE  0xFF0FFFFF

  /* *******************CAN****************** */
  /* PBRIDGE0 OPACR79 - FlexCan0 */
  #define O_PACR_REGISTER_CAN0_ADDR      BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x164)
  #define O_PACR_REGISTER_CAN0_VALUE     0xFFFFFFF0
  /* PBRIDGE0 OPACR78 - FlexCan1 */
  #define O_PACR_REGISTER_CAN1_ADDR      BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x164)
  #define O_PACR_REGISTER_CAN1_VALUE     0xFFFFFF0F
  /* PBRIDGE0 OPACR77 - FlexCan2 */
  #define O_PACR_REGISTER_CAN2_ADDR      BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x164)
  #define O_PACR_REGISTER_CAN2_VALUE     0xFFFFF0FF

  /* *******************LIN****************** */
  /* PBRIDGE1 OPACR94 - LinFlex0 */
  #define O_PACR_REGISTER_LIN0_ADDR      BRSHW_IOS(uint32, PBRIDGE1_BASE + 0x16c)
  #define O_PACR_REGISTER_LIN0_VALUE     0xFFFFFF0F
  /* PBRIDGE0 OPACR91 - LinFlex1 */
  #define O_PACR_REGISTER_LIN1_ADDR      BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x16c)
  #define O_PACR_REGISTER_LIN1_VALUE     0xFFF0FFFF

  /* *******************FLEXRAY****************** */
  /* PBRIDGE0 OPACR107 - FlexRay */
  #define O_PACR_REGISTER_FLEXRAY0_ADDR  BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x174)
  #define O_PACR_REGISTER_FLEXRAY0_VALUE 0xFFF0FFFF

  /* *******************ETHERNET****************** */
  /* PBRIDGE0 OPACR12 - Ethernet */
  #define O_PACR_REGISTER_ETHERNET0_ADDR  BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x144)
  #define O_PACR_REGISTER_ETHERNET0_VALUE 0xFFFF0FFF

  /* *******************FLASH****************** */
  /* PBRIDGE0 OPACR7 - Flash */
  #define O_PACR_REGISTER_FLASH0_ADDR    BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x140)
  #define O_PACR_REGISTER_FLASH0_VALUE   0xFFFFFFF0

  /* *******************DSPI****************** */
  /* PBRIDGE0 OPACR99 - DSPI0 */
  #define O_PACR_REGISTER_DSPI0_ADDR     BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x170)
  #define O_PACR_REGISTER_DSPI0_VALUE    0xFFF0FFFF
  /* PBRIDGE0 OPACR98 - DSPI1 */
  #define O_PACR_REGISTER_DSPI1_ADDR     BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x170)
  #define O_PACR_REGISTER_DSPI1_VALUE    0xFF0FFFFF
  /* PBRIDGE1 OPACR99 - DSPI2 */
  #define O_PACR_REGISTER_DSPI2_ADDR     BRSHW_IOS(uint32, PBRIDGE1_BASE + 0x170)
  #define O_PACR_REGISTER_DSPI2_VALUE    0xFFF0FFFF
  /* PBRIDGE1 OPACR98 - DSPI3 */
  #define O_PACR_REGISTER_DSPI3_ADDR     BRSHW_IOS(uint32, PBRIDGE1_BASE + 0x170)
  #define O_PACR_REGISTER_DSPI3_VALUE    0xFF0FFFFF

  /* *******************WDG****************** */
  /* PBRIDGE0 PACR20 - SWT0 */
  #define O_PACR_REGISTER_SWT0_ADDR    BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x108)
  #define O_PACR_REGISTER_SWT0_VALUE   0xFFFF0FFF

#   if defined (BRSHW_USERMODE_ACCESS_GROUP_A1)
  /* PBRIDGE0 PACR40 - eDMA */
  #define O_PACR_REGISTER_EDMA_ADDR      BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x114)
  #define O_PACR_REGISTER_EDMA_VALUE     0x0FFFFFFF

  /* *******************WDG****************** */
  /* PBRIDGE0 PACR21 - SWT1 */
  #define O_PACR_REGISTER_SWT1_ADDR    BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x108)
  #define O_PACR_REGISTER_SWT1_VALUE   0xFFFFF0FF

  /* **************CROSSBAR SWITCH************* */
  #define O_PACR_REGISTER_XBAR_0_ADDR     BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x100)
  #define O_PACR_REGISTER_XBAR_0_VALUE    (0xF0FFFFFF)
  #define O_PACR_REGISTER_XBAR_1_ADDR     BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x100)
  #define O_PACR_REGISTER_XBAR_1_VALUE    (0xFF0FFFFF)
#   endif /*BRSHW_USERMODE_ACCESS_GROUP_A1*/

/* Additional base addresses for UAA bit setting */

  /* *****************ETHERNET***************** */
  #define ENET_BASE                     0xFC0B0000
  #define ENET_EIR                      BRSHW_IOS(uint32, ENET_BASE + 0x0004)

  /* *******************DSPI****************** */
#   if defined (BRSHW_USERMODE_ACCESS_GROUP_A)
  #define DSPI0_BASE 0xFFE70000
  #define DSPI3_BASE 0xFBE74000
#   endif
  #define DSPI1_BASE 0xFFE74000
  #define DSPI2_BASE 0xFBE70000

  /* *******************FLASH****************** */
  /* Base address of the flash module, used by DrvFls */
  /* This can be Dataflash or Codeflash, depending to the derivative */
  #define FLASH0_BASE 0xFFFE0000

  /* **************DMA MULTIPLEXER************* */
  #define DMAMUX_0_BASE                 0xFFF6C000
  #define DMAMUX_1_BASE                 0xFBF6C000

#  elif defined (BRSHW_USERMODE_ACCESS_GROUP_B) || defined (BRSHW_USERMODE_ACCESS_GROUP_C)
  /***************************************************************/
  /* Platform / Off-platform peripheral access control registers */
  /***************************************************************/
  /* PACR/OPACR only */  
  #define PBRIDGE0_BASE 0xFC000000
  #define PBRIDGE1_BASE 0xF8000000

  /* PBRIDGE0 OPACR15 SIUL */
  #define O_PACR_REGISTER_SIUL_ADDR      BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x144)
  #define O_PACR_REGISTER_SIUL_VALUE     0xFFFFFFF0
  /* PBRIDGE0 OPACR30 PIT */
  #define O_PACR_REGISTER_PIT_ADDR       BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x14C)
  #define O_PACR_REGISTER_PIT_VALUE      0xFFFFFF0F
  /* PBRIDGE0 PACR26 - STM */
  #define O_PACR_REGISTER_STM_ADDR       BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x10C)
  #define O_PACR_REGISTER_STM_VALUE      0xFF0FFFFF

  /* *******************CAN****************** */
  /* PBRIDGE0 OPACR79 - FlexCan0 */
  #define O_PACR_REGISTER_CAN0_ADDR      BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x164)
  #define O_PACR_REGISTER_CAN0_VALUE     0xFFFFFFF0

#   if defined (BRSHW_USERMODE_ACCESS_GROUP_B)
  /* PBRIDGE0 OPACR78 - FlexCan2 */
  #define O_PACR_REGISTER_CAN2_ADDR      BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x164)
  #define O_PACR_REGISTER_CAN2_VALUE     0xFFFFFF0F
  /* PBRIDGE0 OPACR77 - FlexCan4 */
  #define O_PACR_REGISTER_CAN4_ADDR      BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x164)
  #define O_PACR_REGISTER_CAN4_VALUE     0xFFFFF0FF
  /* PBRIDGE0 OPACR76 - FlexCan6 */
  #define O_PACR_REGISTER_CAN6_ADDR      BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x164)
  #define O_PACR_REGISTER_CAN6_VALUE     0xFFFF0FFF

  /* PBRIDGE1 OPACR79 - FlexCan1 */
  #define O_PACR_REGISTER_CAN1_ADDR      BRSHW_IOS(uint32, PBRIDGE1_BASE + 0x164)
  #define O_PACR_REGISTER_CAN1_VALUE     0xFFFFFFF0
  /* PBRIDGE1 OPACR78 - FlexCan3 */
  #define O_PACR_REGISTER_CAN3_ADDR      BRSHW_IOS(uint32, PBRIDGE1_BASE + 0x164)
  #define O_PACR_REGISTER_CAN3_VALUE     0xFFFFFF0F
  /* PBRIDGE1 OPACR77 - FlexCan5 */
  #define O_PACR_REGISTER_CAN5_ADDR      BRSHW_IOS(uint32, PBRIDGE1_BASE + 0x164)
  #define O_PACR_REGISTER_CAN5_VALUE     0xFFFFF0FF
  /* PBRIDGE1 OPACR76 - FlexCan7 */
  #define O_PACR_REGISTER_CAN7_ADDR      BRSHW_IOS(uint32, PBRIDGE1_BASE + 0x164)
  #define O_PACR_REGISTER_CAN7_VALUE     0xFFFF0FFF
#   endif /*BRSHW_USERMODE_ACCESS_GROUP_B*/

#   if defined (BRSHW_USERMODE_ACCESS_GROUP_C)
  /* PBRIDGE0 OPACR78 - FlexCan1 */
  #define O_PACR_REGISTER_CAN1_ADDR      BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x164)
  #define O_PACR_REGISTER_CAN1_VALUE     0xFFFFFF0F

  /* PBRIDGE1 OPACR77 - FlexCan2 */
  #define O_PACR_REGISTER_CAN2_ADDR      BRSHW_IOS(uint32, PBRIDGE1_BASE + 0x164)
  #define O_PACR_REGISTER_CAN2_VALUE     0xFFFFF0FF
  /* PBRIDGE1 OPACR76 - FlexCan3 */
  #define O_PACR_REGISTER_CAN3_ADDR      BRSHW_IOS(uint32, PBRIDGE1_BASE + 0x164)
  #define O_PACR_REGISTER_CAN3_VALUE     0xFFFF0FFF
#   endif /*BRSHW_USERMODE_ACCESS_GROUP_C*/

  /* *******************LIN****************** */
  /* PBRIDGE0 OPACR92 - LinFlex0 */
  #define O_PACR_REGISTER_LIN0_ADDR      BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x16c)
  #define O_PACR_REGISTER_LIN0_VALUE     0xFFFF0FFF

#   if defined (BRSHW_USERMODE_ACCESS_GROUP_B)
  /* PBRIDGE0 OPACR91 - LinFlex2 */
  #define O_PACR_REGISTER_LIN2_ADDR      BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x16c)
  #define O_PACR_REGISTER_LIN2_VALUE     0xFFF0FFFF
  /* PBRIDGE0 OPACR90 - LinFlex4 */
  #define O_PACR_REGISTER_LIN4_ADDR      BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x16c)
  #define O_PACR_REGISTER_LIN4_VALUE     0xFF0FFFFF
  /* PBRIDGE0 OPACR89 - LinFlex6 */
  #define O_PACR_REGISTER_LIN6_ADDR      BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x16c)
  #define O_PACR_REGISTER_LIN6_VALUE     0xF0FFFFFF
  /* PBRIDGE0 OPACR88 - LinFlex8 */
  #define O_PACR_REGISTER_LIN8_ADDR      BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x16c)
  #define O_PACR_REGISTER_LIN8_VALUE     0x0FFFFFFF
  /* PBRIDGE0 OPACR87 - LinFlex10 */
  #define O_PACR_REGISTER_LIN10_ADDR     BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x168)
  #define O_PACR_REGISTER_LIN10_VALUE    0xFFFFFFF0
  /* PBRIDGE0 OPACR86 - LinFlex12 */
  #define O_PACR_REGISTER_LIN12_ADDR     BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x168)
  #define O_PACR_REGISTER_LIN12_VALUE    0xFFFFFF0F
  /* PBRIDGE0 OPACR85 - LinFlex14 */
  #define O_PACR_REGISTER_LIN14_ADDR     BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x168)
  #define O_PACR_REGISTER_LIN14_VALUE    0xFFFFF0FF

  /* PBRIDGE1 OPACR92 - LinFlex1 */
  #define O_PACR_REGISTER_LIN1_ADDR      BRSHW_IOS(uint32, PBRIDGE1_BASE + 0x16c)
  #define O_PACR_REGISTER_LIN1_VALUE     0xFFFF0FFF
  /* PBRIDGE1 OPACR91 - LinFlex3 */
  #define O_PACR_REGISTER_LIN3_ADDR      BRSHW_IOS(uint32, PBRIDGE1_BASE + 0x16c)
  #define O_PACR_REGISTER_LIN3_VALUE     0xFFF0FFFF
  /* PBRIDGE1 OPACR90 - LinFlex5 */
  #define O_PACR_REGISTER_LIN5_ADDR      BRSHW_IOS(uint32, PBRIDGE1_BASE + 0x16c)
  #define O_PACR_REGISTER_LIN5_VALUE     0xFF0FFFFF
  /* PBRIDGE1 OPACR89 - LinFlex7 */
  #define O_PACR_REGISTER_LIN7_ADDR      BRSHW_IOS(uint32, PBRIDGE1_BASE + 0x16c)
  #define O_PACR_REGISTER_LIN7_VALUE     0xF0FFFFFF
  /* PBRIDGE1 OPACR88 - LinFlex9 */
  #define O_PACR_REGISTER_LIN9_ADDR      BRSHW_IOS(uint32, PBRIDGE1_BASE + 0x16c)
  #define O_PACR_REGISTER_LIN9_VALUE     0x0FFFFFFF
  /* PBRIDGE1 OPACR87 - LinFlex11 */
  #define O_PACR_REGISTER_LIN11_ADDR     BRSHW_IOS(uint32, PBRIDGE1_BASE + 0x168)
  #define O_PACR_REGISTER_LIN11_VALUE    0xFFFFFFF0
  /* PBRIDGE1 OPACR86 - LinFlex13 */
  #define O_PACR_REGISTER_LIN13_ADDR     BRSHW_IOS(uint32, PBRIDGE1_BASE + 0x168)
  #define O_PACR_REGISTER_LIN13_VALUE    0xFFFFFF0F
  /* PBRIDGE1 OPACR85 - LinFlex15 */
  #define O_PACR_REGISTER_LIN15_ADDR     BRSHW_IOS(uint32, PBRIDGE1_BASE + 0x168)
  #define O_PACR_REGISTER_LIN15_VALUE    0xFFFFF0FF
#   endif /*BRSHW_USERMODE_ACCESS_GROUP_B*/

#   if defined (BRSHW_USERMODE_ACCESS_GROUP_C)
  /* PBRIDGE0 OPACR91 - LinFlex1 */
  #define O_PACR_REGISTER_LIN1_ADDR      BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x16c)
  #define O_PACR_REGISTER_LIN1_VALUE     0xFFF0FFFF
  /* PBRIDGE0 OPACR92 - LinFlex3 */
  #define O_PACR_REGISTER_LIN3_ADDR      BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x16c)
  #define O_PACR_REGISTER_LIN3_VALUE     0xFF0FFFFF

  /* PBRIDGE1 OPACR92 - LinFlex2 */
  #define O_PACR_REGISTER_LIN2_ADDR      BRSHW_IOS(uint32, PBRIDGE1_BASE + 0x16c)
  #define O_PACR_REGISTER_LIN2_VALUE     0xFFFF0FFF
#   endif /*BRSHW_USERMODE_ACCESS_GROUP_C*/

  /* *******************FLEXRAY****************** */
  /* PBRIDGE0 OPACR107 - FlexRay */
  #define O_PACR_REGISTER_FLEXRAY0_ADDR  BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x174)
  #define O_PACR_REGISTER_FLEXRAY0_VALUE 0xFFF0FFFF

  /* *******************ETHERNET****************** */
#   if defined (BRSHW_USERMODE_ACCESS_GROUP_B)
  /* PBRIDGE0 OPACR206 - Ethernet */
  #define O_PACR_REGISTER_ETHERNET0_ADDR  BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x1A4)
  #define O_PACR_REGISTER_ETHERNET0_VALUE 0xFFFFFF0F
#   endif /*BRSHW_USERMODE_ACCESS_GROUP_B*/

#   if defined (BRSHW_USERMODE_ACCESS_GROUP_C)
  /* PBRIDGE0 PACR44 - Ethernet */
  #define O_PACR_REGISTER_ETHERNET0_ADDR  BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x114)
  #define O_PACR_REGISTER_ETHERNET0_VALUE 0xFFFF0FFF
#   endif /*BRSHW_USERMODE_ACCESS_GROUP_C*/

  /* *******************FLASH****************** */
  /* PBRIDGE0 OPACR7 - Flash */
  #define O_PACR_REGISTER_FLASH0_ADDR    BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x140)
  #define O_PACR_REGISTER_FLASH0_VALUE   0xFFFFFFF0

  /* *******************DSPI****************** */
  /* PBRIDGE0 OPACR99 - DSPI0 */
  #define O_PACR_REGISTER_DSPI0_ADDR    BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x170)
  #define O_PACR_REGISTER_DSPI0_VALUE   0xFFF0FFFF
  /* PBRIDGE0 OPACR98 - DSPI2 */
  #define O_PACR_REGISTER_DSPI2_ADDR    BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x170)
  #define O_PACR_REGISTER_DSPI2_VALUE   0xFF0FFFFF

  /* PBRIDGE1 OPACR99 - DSPI1 */
  #define O_PACR_REGISTER_DSPI1_ADDR    BRSHW_IOS(uint32, PBRIDGE1_BASE + 0x170)
  #define O_PACR_REGISTER_DSPI1_VALUE   0xFFF0FFFF
  /* PBRIDGE1 OPACR98 - DSPI3 */
  #define O_PACR_REGISTER_DSPI3_ADDR    BRSHW_IOS(uint32, PBRIDGE1_BASE + 0x170)
  #define O_PACR_REGISTER_DSPI3_VALUE   0xFF0FFFFF

  /* *******************WDG****************** */
  /* PBRIDGE0 PACR20/21 - SWT0/1 */
  #define O_PACR_REGISTER_SWT0_ADDR    BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x108)
  #define O_PACR_REGISTER_SWT0_VALUE   0xFFFF0FFF
  #define O_PACR_REGISTER_SWT1_ADDR    BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x108)
  #define O_PACR_REGISTER_SWT1_VALUE   0xFFFFF0FF
#   if defined (BRSHW_USERMODE_ACCESS_GROUP_C)
  /* PBRIDGE0 PACR22 - SWT2 */
  #define O_PACR_REGISTER_SWT2_ADDR    BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x108)
  #define O_PACR_REGISTER_SWT2_VALUE   0xFFFFFF0F
#   endif /*BRSHW_USERMODE_ACCESS_GROUP_C*/

  /* *******************eMIOS****************** */
#   if defined (BRSHW_USERMODE_ACCESS_GROUP_C)
  /* PBRIDGE0 OPACR241 - eMIOS_0/1 */
  #define O_PACR_REGISTER_EMIOS0_ADDR    BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x1B8)
  #define O_PACR_REGISTER_EMIOS0_VALUE   0xF0FFFFFF
  #define O_PACR_REGISTER_EMIOS1_ADDR    BRSHW_IOS(uint32, PBRIDGE1_BASE + 0x1B8)
  #define O_PACR_REGISTER_EMIOS1_VALUE   0xF0FFFFFF
#   endif /*BRSHW_USERMODE_ACCESS_GROUP_C*/

  /***************************************************************/
  /* Additional base addresses for UAA bit setting */
  /***************************************************************/
  /* Calypso family seems to have the UAA bit only for the MC_ME module */

  /* *******************MC_ME****************** */
  #define MC_ME_BASE 0xFFFB8000

#   if defined (BRSHW_USERMODE_ACCESS_GROUP_C)
  /* *******************DSPI****************** */
  #define DSPI0_BASE 0xFFE70000
  #define DSPI1_BASE 0xFFE74000
  #define DSPI2_BASE 0xFBE70000
  #define DSPI3_BASE 0xFBE74000

  /* *******************FLASH****************** */
  /* Base address of the flash module, used by DrvFls */
  /* This can be Dataflash or Codeflash, depending to the derivative */
  #define FLASH0_BASE 0xFFFE0000
#   endif /*BRSHW_USERMODE_ACCESS_GROUP_C*/

#  elif defined (BRSHW_USERMODE_ACCESS_GROUP_D)
  /***************************************************************/
  /* Platform / Off-platform peripheral access control registers */
  /***************************************************************/
  /* PACR/OPACR only */
  #define PBRIDGE0_BASE 0xFC000000 /* Peripheral bridge A */
  #define PBRIDGE1_BASE 0xF8000000 /* Peripheral bridge B */

  #define O_PACR_REGISTER_CAN0_ADDR   BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x168)
  #define O_PACR_REGISTER_CAN0_VALUE  0xFFF0FFFF

  #define O_PACR_REGISTER_CAN2_ADDR   BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x168)
  #define O_PACR_REGISTER_CAN2_VALUE  0xF0FFFFFF

  #define O_PACR_REGISTER_LIN0_ADDR   BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x16c)
  #define O_PACR_REGISTER_LIN0_VALUE  0xFFFF0FFF

  #define O_PACR_REGISTER_DATA_FLASH_ADDR   BRSHW_IOS(uint32, PBRIDGE0_BASE + 0x140)
  #define O_PACR_REGISTER_DATA_FLASH_VALUE  0xFFFFFFF0

#  else
  #error: "Your Derivative is currently not analyzed and categorized to a UserMode_Access_Group"
#  endif /*BRSHW_USERMODE_ACCESS_GROUP_x*/
# endif /*BRSASR_ENABLE_SAFECTXSUPPORT*/
#endif /*!BRS_OS_USECASE_BRS*/

/**********************************************************************************************************************
  LOCAL VARIABLES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL CONST VARIABLES
**********************************************************************************************************************/
  #define BRSHWNOP10() asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop")

/**********************************************************************************************************************
  PROTOTYPES OF LOCAL FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
  FUNCTION DEFINITIONS
**********************************************************************************************************************/

/*****************************************************************************/
/**
 * @brief      This function has to be used to initialize the Watchdog.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from main@BrsMain or EcuM at power on initialization
 */
/*****************************************************************************/
void BrsHwWatchdogInitPowerOn(void)
{
#if !defined (VGEN_ENABLE_DRVWD)
# if defined (BRSHW_WATCHDOG_GROUP_A) || defined (BRSHW_WATCHDOG_GROUP_B) || defined (BRSHW_WATCHDOG_GROUP_C)
  SWT_SR = (uint32)0x0000C520;
  SWT_SR = (uint32)0x0000D928; /* clear softlockbit */
  SWT_CR = (uint32)0x80000102; /* FRZ=1 SWT counter is stopped in debug mode */
                               /* RIA=1 Invalid access to the SWT causes a system reset */

#  if defined (BRSHW_WATCHDOG_GROUP_B) || defined (BRSHW_WATCHDOG_GROUP_C)
  /*Watchdog Timer2 is enabled by default --> disable watchdog */
  SWT2_SR = 0x0000C520;
  SWT2_SR = 0x0000D928; /* clear softlockbit */
  SWT2_CR = 0x80000102; /* FRZ=1 SWT counter is stopped in debug mode */
                        /* RIA=1 Invalid access to the SWT causes a system reset */

#   if defined (BRSHW_WATCHDOG_GROUP_C)
  SWT3_SR = 0x0000C520;
  SWT3_SR = 0x0000D928; /* clear softlockbit */
  SWT3_CR = 0x80000102; /* FRZ=1 SWT counter is stopped in debug mode */
#   endif /*BRSHW_WATCHDOG_GROUP_C*/
#  endif /*BRSHW_WATCHDOG_GROUP_B || BRSHW_WATCHDOG_GROUP_C*/
# endif /*BRSHW_WATCHDOG_GROUP_A || BRSHW_WATCHDOG_GROUP_B || BRSHW_WATCHDOG_GROUP_C*/
#endif /*!VGEN_ENABLE_DRVWD*/
}

/*****************************************************************************/
/**
 * @brief      This function has to be used to initialize the PLL.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from main@BrsMain or EcuM at power on initialization
 */
/*****************************************************************************/
void BrsHwPllInitPowerOn(void)
{
#if !defined (VGEN_ENABLE_DRVMCU)
# if (BRS_TIMEBASE_CLOCK > BRSHW_CPU_MAX_FREQUENCY)
  #error "The selected derivative does not support frequencies above BRSHW_CPU_MAX_FREQUENCY (please find the defined value within BrsHw_DerivativeList.h)!"
# endif

# if defined (BRSHW_FMPLL_GROUP_A)
  /* Route XOSC to the PLLs - IRC is default */
#  if defined (BRSHW_OPMODES_GROUP_A)
#   if defined (BRSHW_FMPLL_GROUP_A_1)
  CGM_AC3_SC = (uint32)0x01000000;  /* set auxiliary clock 3 (PLL0 reference clock) source: 8-40 MHz crystal osc. */
  if ((((SIU_MIDR1) >> 16) == 0x5777) && (((SIU_MIDR1) & 0xff) != 0))
  {
    /* Matterhorn Cut2 */
    CGM_SC_DIV_RC = 0x00000001; /* System clock divider ratios will change with next update. */
    CGM_DIV_UPD_TYPE = 0x80000000; /* System clock divider ratios updated on writing MC_CGM.DIV_UPD_TRIG. */
    CGM_SC_DC0 = (uint32)0x80010000; /* DC0 = /3 */
    CGM_SC_DC1 = (uint32)0x80010000; /* DC1 = /6 */
    CGM_SC_DC2 = (uint32)0x80030000; /* set PBRIDGE_CLK DC2 = /12 */
    CGM_SC_DC3 = (uint32)0x80010000; /* DC3 = /2 */
    CGM_SC_DC4 = (uint32)0x80030000; /* DC4 = /4 */
    CGM_DIV_UPD_TRIG = 0xfeedface;
    while (CGM_DIV_UPD_STAT == 1)
    {
      asm("nop");
    }

    CGM_AC0_SC  = (uint32)0x02000000;  /* set auxiliary clock 0 to source: PLL0 */
    CGM_AC0_DC0 = (uint32)0x80030000;  /* set PER_CLK divider (used by PIT, etc. ) = PLL0/4 ; Reason: this is the max. frequency! */
    CGM_AC0_DC4 = (uint32)0x80030000;  /* set LIN_CLK divider (used by LIN, etc. ) = PLL0/8 = 160/4 = 40Mhz */
    CGM_AC2_DC0 = (uint32)0x80010000;  /* set FR_CLK divider = PLL0/2 = 80 MHz *//*Manual says max Freq is 40 Mhz, so this should not work...but it does...*/
    CGM_AC3_SC  = (uint32)0x01000000;  /* set auxiliary clock 3 (PLL0 reference clock) source: external crystal osc. (8-40 MHz) */
    CGM_AC6_SC  = (uint32)0x02000000;  /* set auxiliary clock 6 (SYS_CLK0) source: PLL0 */
    CGM_AC6_DC0 = (uint32)0x80010000;  /* set SYS_CLK0 divider = PLL0/2 = 80 Mhz */
    CGM_AC7_SC  = (uint32)0x02000000;  /* set auxiliary clock 7 (SYS_CLK1) source: PLL0 */
    CGM_AC7_DC0 = (uint32)0x80010000;  /* set SYS_CLK1 divider = PLL0/2 = 80 Mhz */
    CGM_AC8_SC  = (uint32)0x01000000;  /* set auxiliary clock 8 (CAN_CLK)  source: XOSC */
    CGM_AC8_DC0 = (uint32)0x80000000;  /* set auxiliary clock 8 divider to 2 (devider AC8 seems to be necessary otherwise MCAN doesn't get a clock) */
    CGM_AC9_SC  = (uint32)0x01000000;  /* set auxiliary clock 9 (RTI_CLK)  source: XOSC */
    CGM_AC9_DC0 = (uint32)0x80010000;  /* set auxiliary clock 9 divider to 2 */
  }
  else if ((((SIU_MIDR1) >> 16) == 0x5746) && (((SIU_MIDR1) & 0x10) == 0x10))
  {
    /* McKinley Cut2: not documented in data sheet, but token from sample program "skeletonProject" */
    CGM_SC_DIV_RC = 0x00000001; /* System clock divider ratios will change with next update. */
    CGM_DIV_UPD_TYPE = 0x80000000; /* System clock divider ratios updated on writing MC_CGM.DIV_UPD_TRIG. */
    /* Configure System clock dividers */
    CGM_SC_DC0    = (uint32)0x80000000; /* DC0 = /1 fast XBAR clock  */
    CGM_SC_DC1    = (uint32)0x80010000; /* DC1 = /2 slow XBAR clock */
    CGM_SC_DC2    = (uint32)0x80030000; /* set PBRIDGE_CLK DC2 = /4 -> STM timer */

    CGM_AC0_SC = (uint32)0x02000000;  /* set auxiliary clock 0 (PER_CLK)  source: PLL0 */
    CGM_AC0_DC0= (uint32)0x80030000;  /* set PER_CLK (used by PIT, etc. ) = SYS_CLK/4 ; Reason: this is the max. frequency! */
    CGM_AC0_DC4= (uint32)0x80010000;    /* set LIN_CLK (used by LIN, etc. ) = SYS_CLK/2 */
    CGM_AC2_DC0 = (uint32)0x80010000;
    CGM_AC6_SC = (uint32)0x02000000;  /* set auxiliary clock 6 (SYS_CLK0) source: PLL0 */
#    if !(defined (BRS_DERIVATIVE_MPC5746R) || defined (BRS_DERIVATIVE_MPC5745R))
    CGM_AC7_SC = (uint32)0x02000000;  /* set auxiliary clock 7 (SYS_CLK1) source: PLL0 */
#    endif
    CGM_AC8_SC = (uint32)0x01000000;  /* set auxiliary clock 8 (CAN_CLK)  source: XOSC */
    CGM_AC8_DC0= (uint32)0x80000000;  /* set auxiliary clock 8 divider to 1 (devider AC8 seems to be necessary otherwise MCAN doesn't get a clock) */

    CGM_AC9_SC = (uint32)0x01000000;  /* set auxiliary clock 9 (RTI_CLK)  source: XOSC */
    CGM_AC9_DC0 = (uint32)0x80010000;

    CGM_AC6_DC0 = (uint32) 0x80000000; /*divide PLL0 by 1*/
#    if !(defined (BRS_DERIVATIVE_MPC5746R) || defined (BRS_DERIVATIVE_MPC5745R))
    CGM_AC7_DC0 = (uint32) 0x80000000; /*divide PLL1 by 1*/
#    endif

    CGM_DIV_UPD_TRIG = 0xfeedface; /* System clock divider ratio updates triggered. */
    while (CGM_DIV_UPD_STAT == 1)  /* Wait for System Clock Divider Update Status == 0. */
    {
      asm("nop");
    }
  }
  else
  {
    CGM_SC_DC2  = (uint32)0x80030000; /* set PBRIDGE_CLK (used by ? etc. ) = SYS_CLK/4 ; Reason: this is the max. frequency! */
    CGM_AC0_SC  = (uint32)0x02000000; /* set auxiliary clock 0 (PER_CLK)  source: PLL0 */
    CGM_AC0_DC0 = (uint32)0x80030000; /* set PER_CLK (used by PIT, etc. ) = SYS_CLK/4 ; Reason: this is the max. frequency! */
    CGM_AC0_DC4 = (uint32)0x80010000; /* set LIN_CLK (used by LIN, etc. ) = SYS_CLK/2 */
    CGM_AC2_DC0 = (uint32)0x80010000; /* divide by 2 */
    CGM_AC6_SC  = (uint32)0x02000000; /* set auxiliary clock 6 (SYS_CLK0) source: PLL0 */
#    if !(defined (BRS_DERIVATIVE_MPC5746R) || defined (BRS_DERIVATIVE_MPC5745R))
    /* Rainier does not have AuxClk7 */
    CGM_AC7_SC  = (uint32)0x02000000; /* set auxiliary clock 7 (SYS_CLK1) source: PLL0 */
#    endif
    CGM_AC8_SC  = (uint32)0x01000000; /* set auxiliary clock 8 (CAN_CLK)  source: XOSC */
    CGM_AC8_DC0 = (uint32)0x80000000; /* set auxiliary clock 8 divider to 1 (devider AC8 seems to be necessary otherwise MCAN doesn't get a clock) */
    CGM_AC9_SC  = (uint32)0x01000000; /* set auxiliary clock 9 (RTI_CLK)  source: XOSC */
    CGM_AC9_DC0 = (uint32)0x80010000;
  }

#   elif defined (BRSHW_FMPLL_GROUP_A_2)
  CGM_AC4_SC = (uint32)0x01000000; /* set XOSC as clock source for PLL0*/
  /* If the Pll is wrong, check the CGM_AC4_SC Register if the value was written */
#    if defined (VGEN_ENABLE_DRVFR__BASEASR)
#     if (BRS_TIMEBASE_CLOCK%80 != 0)
  #error Flexray needs an 80 MHz clock. Please adjust PLL0 (TIMEBASE_CLOCK) and CGM_AC2_DC0 divider accordingly.
#     else
  CGM_AC2_DC0 =
    (0x1                       <<31U) | /* Bit 0:     DE - Divider Enable */
    ((BRS_TIMEBASE_CLOCK/80-1) <<16U);  /* Bit 12-15: DIV - Divider Division Value Divider. The resultant FlexRay clock has a period 'DIV + 1' times that of auxiliary clock 2. */
                                        /* The source of AC2 is PLL0 by default */
#     endif
#    endif /*VGEN_ENABLE_DRVFR__BASEASR*/
#    if defined (VGEN_ENABLE_LIN_DRV)
  CGM_AC8_SC  = (uint32)0x02000000; /* set Auxiliary Clock 8 Source Control to PLL0_PHI */
  CGM_AC8_DC0 = (uint32)0x80020000; /* enable LIN -> LIN baud rate clock 80MHz */
#     endif

#   elif defined (BRSHW_FMPLL_GROUP_A_3)
  CGM_AC2_SC  = 0x01000000; /* Select PLL0 input = XOSC */
  CGM_AC3_SC  = 0x01000000; /* Select PLL1 input = XOSC */
  CGM_SC_DC0  = 0x80000000; /* System clock divider enabled, System clock = System clock source / 1 */
  CGM_SC_DC1  = 0x80000000; /* IPS divider enabled, IPS clock = System clock source / 1 */

  CGM_AC0_SC  = 0x02000000; /* Select peripheral clock source = PLL0 (PIT, LINflex, etc.) */
  CGM_AC0_DC0 = 0x80030000; /* PIT clock divider enabled, peripheral clock / 4 */

  CGM_AC1_SC  = 0x02000000; /* Select CAN clock source = PLL0 */
  CGM_AC1_DC0 = 0x80000000; /* CAN divider enabled, CAN clock = PLL0 / 1 */

#   else
  CGM_AC3_SC = (uint32)0x01000000;  /* set auxiliary clock 3 (PLL0 reference clock) source: 8-40 MHz crystal osc. */
  CGM_SC_DC0 = (uint32)0x80030000;  /* set PBRIDGE_CLK (used by PIT, CAN, LIN, FR, etc. ) = SYS_CLK/4 ; Reason: this is the max. frequency! */
#    if defined (BRS_DERIVATIVE_MPC5775K)
  CGM_AC15_SC  = (uint32)0x02000000;  /*set auxilary clock 15 to PLL0_PHI_CLK*/
  CGM_AC15_DC0 = (uint32)0x80030000;  /*enable auxilary clock 15 and set divider to 4 --> Pll0_PHI_CLK/4 used for MCAN*/
#    endif
#    if defined (BRSASR_ENABLE_OS_MULTICORESUPPORT)
     CGM_SC_DC1 = (uint32)0x80010000; /* Core1_CLK divider: 2 (same divider than Core0_CLK) */
     CGM_SC_DC2 = (uint32)0x80010000; /* Core2_CLK divider: 2 (same divider than Core0_CLK) */
#    endif
#   endif /*BRSHW_FMPLL_GROUP_A_x*/
#  endif /*BRSHW_OPMODES_GROUP_A*/

#  if defined (BRSHW_OPMODES_GROUP_B)
  CGM_AC3_SC  = 0x01000000; /* Select PLL0 input = XOSC */
  CGM_AC4_SC  = 0x01000000; /* Select PLL1 input = XOSC */
  CGM_SC_DC0  = 0x80000000; /* System clock divider enabled, System clock = System clock source / 1 */
  CGM_SC_DC1  = 0x80010000; /* Peripheral Core 2 divider enabled, clock = System clock source / 2 */
  CGM_SC_DC2  = 0x80030000; /* PBRIDGE clock, clock = System clock source / 4 */

  CGM_AC0_SC  = 0x02000000; /* Select peripheral clock source = PLL0 (PIT, LINflex, etc.) */
  CGM_AC0_DC0 = 0x80030000; /* PIT clock divider enabled, peripheral clock / 4 */

  CGM_AC8_SC  = 0x01000000; /* Select FlexCAN clock source = PLL0 */
  CGM_AC2_DC0 = 0x00000000; /* FLEXRAY */
#  endif /*BRSHW_OPMODES_GROUP_B*/

#  if ((BRS_OSC_CLK < 8) || (BRS_OSC_CLK > 56) || ((BRS_OSC_CLK%8 != 0) && (BRS_OSC_CLK%10 != 0)))
  #error "The current PLL implementation only supports quartz frequencies which are multiples of 8 or 10 MHz and the quartz must be in the range of 8 - 56 MHz! PLL will have an undefined frequency!"
#  endif
#  if ((BRS_TIMEBASE_CLOCK < 75) || (BRS_TIMEBASE_CLOCK > 310) || (BRS_TIMEBASE_CLOCK%5 != 0)) && (BRS_OSC_CLK%10 == 0)
  #error "With the used quartz (divisible by 10MHz) the current PLL implementation only supports CPU frequencies in the range 75 - 310 MHz and which are multiples of 5 MHz! PLL will have an undefined frequency!"
#  elif (((BRS_TIMEBASE_CLOCK < 75) || ((BRS_TIMEBASE_CLOCK > 127) && (BRS_TIMEBASE_CLOCK < 150)) || (BRS_TIMEBASE_CLOCK > 254) || ((BRS_TIMEBASE_CLOCK >= 150) && (BRS_TIMEBASE_CLOCK <= 254) && (BRS_TIMEBASE_CLOCK%2 != 0))) && (BRS_OSC_CLK%8 == 0) && (BRS_OSC_CLK%10 != 0))
  #error "With the used quartz (divisible of 8MHz) the current PLL implementation only supports CPU frequencies in the range 75 - 127/150 - 254 MHz and which are multiples of 1/2 MHz! PLL will have an undefined frequency!"
#  endif

  /* CPU_FREQUENCY = (QUARTZ_FREQUENCY*MFD) / (PREDIV * (RFDPHI*2)) */
#  if (BRS_TIMEBASE_CLOCK >= 75) && (BRS_TIMEBASE_CLOCK < 150) && (BRS_OSC_CLK%10 == 0)
  #define PREDIV  BRS_OSC_CLK/10
  #define MFD     BRS_TIMEBASE_CLOCK*8/10
  #define RFDPHI  4*2
#  elif (BRS_TIMEBASE_CLOCK >= 150) && (BRS_TIMEBASE_CLOCK <= 310) && (BRS_OSC_CLK%10 == 0)
  #define PREDIV  BRS_OSC_CLK/10
  #define MFD     BRS_TIMEBASE_CLOCK*4/10
  #define RFDPHI  2*2
#  elif (BRS_TIMEBASE_CLOCK >= 75) && (BRS_TIMEBASE_CLOCK <= 127) && (BRS_OSC_CLK%8 == 0)
  #define PREDIV  BRS_OSC_CLK/8
  #define MFD     BRS_TIMEBASE_CLOCK
  #define RFDPHI  4*2
#  elif (BRS_TIMEBASE_CLOCK >= 150) && (BRS_TIMEBASE_CLOCK <= 254) && (BRS_OSC_CLK%8 == 0)
  #define PREDIV  BRS_OSC_CLK/8
  #define MFD     BRS_TIMEBASE_CLOCK/2
  #define RFDPHI  2*2
#  endif

  PLL0DV =
    (0x4    <<27U) | /* Bit 1-4: RFDPHI1: 0x4 = Divider for PHI1 output clock (not used but 0x0 is not allowed!) */
    (RFDPHI <<16U) | /* Bit 10-15: Divider for PHI output clock (0x00 -> invalid,0x1 ->2,0x2->4,0x3->6,...,0x3f->126) */
    (PREDIV <<12U) | /* Bit 17-19: Input clock pre-divider (0x0-> Clock inhibit,0x1->1,...,0x7->7) */
    (MFD    <<0U);   /* Bit 25-31: Loop multiplication factor divider (0x00-0x07->invalid ,0x08 -> 8,0x09 -> 9,...,0x7f ->127 */

#  if defined (BRSHW_SIU_GROUP_B)
  PLL0CR |= 0x00000300; /* Set CLKCFG to 11b -> PLL in normal mode */
  while (!(SIU_RSR & 0x00000080UL)){}; /* Confirm that XOSC clock is stable */
  /* (Mandatory for MPC5777C) */
  /* Bit 0-7:   SYSDIV unlocked (0), PLL0 input = XOSC (0), PLL1 input = XOSC (0), PERCLKSEL = SYSCLK (0)*/
  /* Bit 10-11: FMPERDIV = Divide_by_4 (bug->0b00, 0b01???) (FM_PER_CLK has to be lower than 100MHz! -> ATTENTION: bug description see below!) */
  /* Bit 14-15: PERDIV = Divide_by_4 (0b01) (has to be Sys_clk/4 for PIT timer calculation)*/
  /* Bit 16:    MCAN = XOSC (0)*/
  /* Bit 18-19: SYSCLKSEL = PLL0 (0b11) */
  /* Bit 23-31: eTPUDiv = Divide_by_2 (0), SysClkDiv = Divide_by_1 (0b100), ProgressiveClockSwitch = disabled (0) */
  SIU_SYSCLK = 0x00013010;  /* ATTENTION: MPC5777C works only correct with FMPERDIV = 0b00 (Divide_by_2 -> FM_PER_CLK > 100MHz ?) !!!   */
                            /* But according to the manual the prescaler has to be at least FMPERDIV = 0b01 (Divide_by_4) -> 0x00113010 */
#  endif /*BRSHW_SIU_GROUP_B*/
#  if defined (BRSHW_OPMODES_GROUP_NONE)
  /* PLL0 mode changes are handled threw CLKCFG-field of PLL0CR, and not threw MC_ME mode entry module */
  //PLL0CR &= 0xFFFFFCFF; /* Set CLKCFG to 00b -> PLL off; power down pulse */
  while (!(PLL0SR & 0x00000004UL)){}; /* Confirm that PLL0 clock is stable */
#  endif /*BRSHW_OPMODES_GROUP_NONE*/
# endif /*BRSHW_FMPLL_GROUP_A*/

# if defined (BRSHW_FMPLL_GROUP_B)
  /* Route XOSC to the PLL's - IRC is default */
  CGM_AC5_SC = (uint32)0x01000000;  /* set auxiliary clock 5 (PLL reference clock) source: 8-40 MHz external crystal osc. (FXOSC) */
#  if (BRS_TIMEBASE_CLOCK != 160)
  #error "According to the MPC5748G Datasheet Rev. 2 the PLL must have the output frequency 160MHz!"
#  endif

#  if ((BRS_OSC_CLK < 8) || (BRS_OSC_CLK > 56) || ((BRS_OSC_CLK%8 != 0) && (BRS_OSC_CLK%10 != 0)))
  #error "The current PLL implementation only supports quartz frequencies which are multiples of 8 or 10 MHz and the quartz must be in the range of 8 - 56 MHz! PLL will have an undefined frequency!"
#  endif
#  if ((BRS_TIMEBASE_CLOCK < 75) || (BRS_TIMEBASE_CLOCK > 310) || (BRS_TIMEBASE_CLOCK%5 != 0)) && (BRS_OSC_CLK%10 == 0)
  #error "With the used quartz (divisible by 10MHz) the current PLL implementation only supports CPU frequencies in the range 75 - 310 MHz and which are multiples of 5 MHz! PLL will have an undefined frequency!"
#  elif (((BRS_TIMEBASE_CLOCK < 75) || ((BRS_TIMEBASE_CLOCK > 127) && (BRS_TIMEBASE_CLOCK < 150)) || (BRS_TIMEBASE_CLOCK > 254) || ((BRS_TIMEBASE_CLOCK >= 150) && (BRS_TIMEBASE_CLOCK <= 254) && (BRS_TIMEBASE_CLOCK%2 != 0))) && (BRS_OSC_CLK%8 == 0) && (BRS_OSC_CLK%10 != 0))
  #error "With the used quartz (divisible of 8MHz) the current PLL implementation only supports CPU frequencies in the range 75 - 127/150 - 254 MHz and which are multiples of 1/2 MHz! PLL will have an undefined frequency!"
#  endif

  /* CPU_FREQUENCY = (QUARTZ_FREQUENCY*MFD) / (PREDIV * (2^(RFDPHI-1)) *4) */
  /* Don't trust the datasheet.... the Out Divider is 4*(2^(RFDPHI-1)) */
#  if (BRS_OSC_CLK%10 == 0)
  #define PREDIV  BRS_OSC_CLK/10
  #define MFD     BRS_TIMEBASE_CLOCK*4*1/10
  #define RFDPHI  1                              /* /4*1 */
#  elif (BRS_OSC_CLK%8 == 0)
  #define PREDIV  BRS_OSC_CLK/8
  #define MFD     BRS_TIMEBASE_CLOCK
  #define RFDPHI  2                              /* /4*2 */
#  endif

  PLL0DV =
  (0x4    <<27U) | /* Bit 1-4: RFDPHI1: 0x4 = Divider for PHI1 output clock (not used but 0x0 is not allowed!) */
  (RFDPHI <<16U) | /* Bit 10-15: Divider for PHI output clock (0x00 -> invalid,0x1 ->2,0x2->4,0x3->6,...,0x3f->126) */
  (PREDIV <<12U) | /* Bit 17-19: Input clock pre-divider (0x0-> Clock inhibit,0x1->1,...,0x7->7) */
  (MFD    <<0U);   /* Bit 25-31: Loop multiplication factor divider (0x00-0x07->invalid ,0x08 -> 8,0x09 -> 9,...,0x7f ->127 */

  PLLCAL3 = 0x09c3c000;
  PLLFD = 0x40000000; /* SMDEN=1 (to disable SDM...) */
# endif /*BRSHW_FMPLL_GROUP_B*/

  BrsHwSwitchRunMode();
#endif /*!VGEN_ENABLE_DRVMCU*/
}

#if !defined (VGEN_ENABLE_DRVPORT)
/*******************************************************************************
  Port Pin initialization helper functions for usage of BrsHw_Ports.h
********************************************************************************/
/*****************************************************************************/
/**
 * @brief      This function configures a port pin as input pin.
 * @pre        Port pin configuartions available within BrsHw_Ports.h and
 *             no DrvPort used for port pin initialization.
 * @param[in]  p - brsHw_Port_PortType, to be initialized.
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsHwPortInitPowerOn() and
 *             BrsHwEvaBoardInitPowerOn() locally.
 */
/*****************************************************************************/
void BrsHwInitPortInput(brsHw_Port_PortType p, brsHw_Port_MultiplexedType m)
{
#if defined (BRSHW_SIU_GROUP_B)
  SIU_MSCR((p.muxMSCRValue)) |= BRSHW_PCR_PIN_ASSIGNMENT_GPIO_INPUT; /* Very Strong drive, Push-pull */
  if ((m.muxIMUXValue) <= 12)
  {
    switch(m.muxMUXSEL)
    {
      case BRSHW_PORT_SIUL_MUXSEL_0:
        SIU_IMUX((m.muxIMUXValue)) &= (0xFFFFFFFC);
        SIU_IMUX((m.muxIMUXValue)) |=  ((m.muxMultiplexedAlternative) << 0);
        break;
      case BRSHW_PORT_SIUL_MUXSEL_1:
        SIU_IMUX((m.muxIMUXValue)) &= (0xFFFFFFF3);
        SIU_IMUX((m.muxIMUXValue)) |=  ((m.muxMultiplexedAlternative) << 2);
        break;
      case BRSHW_PORT_SIUL_MUXSEL_2:
        SIU_IMUX((m.muxIMUXValue)) &= (0xFFFFFFCF);
        SIU_IMUX((m.muxIMUXValue)) |=  ((m.muxMultiplexedAlternative) << 4);
        break;
      case BRSHW_PORT_SIUL_MUXSEL_3:
        SIU_IMUX((m.muxIMUXValue)) &= (0xFFFFFF3F);
        SIU_IMUX((m.muxIMUXValue)) |=  ((m.muxMultiplexedAlternative) << 6);
        break;
      case BRSHW_PORT_SIUL_MUXSEL_4:
        SIU_IMUX((m.muxIMUXValue)) &= (0xFFFFFCFF);
        SIU_IMUX((m.muxIMUXValue)) |=  ((m.muxMultiplexedAlternative) << 8);
      case BRSHW_PORT_SIUL_MUXSEL_5:
        SIU_IMUX((m.muxIMUXValue)) &= (0xFFFFF3FF);
        SIU_IMUX((m.muxIMUXValue)) |=  ((m.muxMultiplexedAlternative) << 10);
        break;
      case BRSHW_PORT_SIUL_MUXSEL_6:
        SIU_IMUX((m.muxIMUXValue)) &= (0xFFFFCFFF);
        SIU_IMUX((m.muxIMUXValue)) |=  ((m.muxMultiplexedAlternative) << 12);
        break;
      case BRSHW_PORT_SIUL_MUXSEL_7:
        SIU_IMUX((m.muxIMUXValue)) &= (0xFFFF3FFF);
        SIU_IMUX((m.muxIMUXValue)) |=  ((m.muxMultiplexedAlternative) << 14);
        break;
      case BRSHW_PORT_SIUL_MUXSEL_8:
        SIU_IMUX((m.muxIMUXValue)) &= (0xFFFCFFFF);
        SIU_IMUX((m.muxIMUXValue)) |=  ((m.muxMultiplexedAlternative) << 16);
        break;
      case BRSHW_PORT_SIUL_MUXSEL_9:
        SIU_IMUX((m.muxIMUXValue)) &= (0xFFF3FFFF);
        SIU_IMUX((m.muxIMUXValue)) |=  ((m.muxMultiplexedAlternative) << 18);
        break;          
      case BRSHW_PORT_SIUL_MUXSEL_10:
        SIU_IMUX((m.muxIMUXValue)) &= (0xFFCFFFFF);
        SIU_IMUX((m.muxIMUXValue)) |=  ((m.muxMultiplexedAlternative) << 20);
        break;          
      case BRSHW_PORT_SIUL_MUXSEL_11:
        SIU_IMUX((m.muxIMUXValue)) &= (0xFF3FFFFF);
        SIU_IMUX((m.muxIMUXValue)) |=  ((m.muxMultiplexedAlternative) << 22);
        break;
      case BRSHW_PORT_SIUL_MUXSEL_12:
        SIU_IMUX((m.muxIMUXValue)) &= (0xFCFFFFFF);
        SIU_IMUX((m.muxIMUXValue)) |=  ((m.muxMultiplexedAlternative) << 24);
        break;
      case BRSHW_PORT_SIUL_MUXSEL_13:
        SIU_IMUX((m.muxIMUXValue)) &= (0xF3FFFFFF);
        SIU_IMUX((m.muxIMUXValue)) |=  ((m.muxMultiplexedAlternative) << 26);
        break;          
      case BRSHW_PORT_SIUL_MUXSEL_14:
        SIU_IMUX((m.muxIMUXValue)) &= (0xCFFFFFFF);
        SIU_IMUX((m.muxIMUXValue)) |=  ((m.muxMultiplexedAlternative) << 28);
        break;
      case BRSHW_PORT_SIUL_MUXSEL_15:
        SIU_IMUX((m.muxIMUXValue)) &= (0x3FFFFFFF);
        SIU_IMUX((m.muxIMUXValue)) |=  ((m.muxMultiplexedAlternative) << 30);
        break;
    }
  }

#elif defined (BRSHW_SIU_GROUP_D_2)
  if((p.portSIUL) == BRSHW_PORT_SIUL_A)
  {
    SIU_MSCR((p.muxMSCRValue)) |= BRSHW_PCR_PIN_ASSIGNMENT_GPIO_INPUT; /* Very Strong drive, Push-pull */
    SIU_MSCR((m.muxMSCRValue)) |= (m.muxMultiplexedAlternative); /* Source Signal Select */
  }
  else
  {
    SIU_B_MSCR((p.muxMSCRValue)) |= BRSHW_PCR_PIN_ASSIGNMENT_GPIO_INPUT; /* Very Strong drive, Push-pull */
    SIU_B_MSCR((m.muxMSCRValue)) |= (m.muxMultiplexedAlternative); /* Source Signal Select */
  }

#else
  SIU_MSCR((p.portGroup * 16 + p.portNumber)) |= BRSHW_PCR_PIN_ASSIGNMENT_GPIO_INPUT; /* Enables the input buffer */
# if defined (BRSHW_SIU_GROUP_A)
  SIU_IMCR((m.muxIMCRValue)) |= (m.muxMultiplexedAlternative);
# else
  SIU_MSCR((m.muxMSCRValue)) |= (m.muxMultiplexedAlternative);
# endif
#endif /*BRSHW_SIU_GROUP_x*/
}

/*****************************************************************************/
/**
 * @brief      This function configures a port pin as output pin.
 * @pre        Port pin configuartions available within BrsHw_Ports.h and
 *             no DrvPort used for port pin initialization.
 * @param[in]  p - brsHw_Port_PortType, to be initialized.
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsHwPortInitPowerOn() and
 *             BrsHwEvaBoardInitPowerOn() locally.
 */
/*****************************************************************************/
void BrsHwInitPortOutput(brsHw_Port_PortType p)
{
#if defined (BRSHW_SIU_GROUP_B)
  SIU_MSCR((p.muxMSCRValue)) |= BRSHW_PCR_PIN_ASSIGNMENT_GPIO_OUTPUT; /* Very Strong drive, Push-pull*/
  SIU_MSCR((p.muxMSCRValue)) |= (p.muxMultiplexedAlternative); /* Source Signal Select */

#elif defined (BRSHW_SIU_GROUP_D_2)
  if((p.portSIUL) == BRSHW_PORT_SIUL_A)
  {
    SIU_MSCR((p.muxMSCRValue)) |= BRSHW_PCR_PIN_ASSIGNMENT_GPIO_OUTPUT; /* Very Strong drive, Push-pull */
    SIU_MSCR((p.muxMSCRValue)) |= (p.muxMultiplexedAlternative); /* Source Signal Select */
  }
  else
  {
    SIU_B_MSCR((p.muxMSCRValue)) |= BRSHW_PCR_PIN_ASSIGNMENT_GPIO_OUTPUT; /* Very Strong drive, Push-pull */
    SIU_B_MSCR((p.muxMSCRValue)) |= (p.muxMultiplexedAlternative); /* Source Signal Select */
  }

#else
  SIU_MSCR((p.portGroup * 16 + p.portNumber)) |= BRSHW_PCR_PIN_ASSIGNMENT_GPIO_OUTPUT; /* Very Strong drive, Push-pull */
  SIU_MSCR((p.portGroup * 16 + p.portNumber)) |= (p.portAlternative); /* Source Signal Select */
#endif /*BRSHW_SIU_GROUP_x*/
}

/*****************************************************************************/
/**
 * @brief      This function configures the port pin configuration registers
 *             (pull-up, pull-down)
 * @pre        Port pin configuartions available within BrsHw_Ports.h and
 *             no DrvPort used for port pin initialization.
 * @param[in]  p - brsHw_Port_PortType, to be initialized,
 *             n - brsHw_Port_ConfType, for port pin configuration
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsHwPortInitPowerOn() and
 *             BrsHwEvaBoardInitPowerOn() locally.
 */
/*****************************************************************************/
void BrsHwInitPortConfig(brsHw_Port_PortType p, brsHw_Port_ConfType n)
{
#if defined (BRSHW_SIU_GROUP_B)
  if ((n.PortPullOption) == PORT_PULL_UP_ENABLED)
  {
    SIU_MSCR((p.muxMSCRValue)) &= (0xFFFCFFFF);
    SIU_MSCR((p.muxMSCRValue)) |= (3 << 16);
  }
  else if ((n.PortPullOption) == PORT_PULL_DOWN_ENABLED)
  {
    SIU_MSCR((p.muxMSCRValue)) &= (0xFFFCFFFF);
    SIU_MSCR((p.muxMSCRValue)) |= (1 << 16);
  }
  else
  {
    SIU_MSCR((p.muxMSCRValue)) &= (0xFFFCFFFF);
  }
#endif
}

# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_START_SEC_RAM_CODE
  #include "Brs_MemMap.h"   /* PRQA S 5087 *//* MD_MSR_19.1 */
# endif
/*****************************************************************************/
/**
 * @brief      This function sets the output level of a port pin.
 * @pre        Port pin configuartions available within BrsHw_Ports.h,
 *             no DrvPort used for port pin initialization and
 *             transferred port pin has to be initialized as output pin with
 *             GPIO functionality.
 * @param[in]  p     - brsHw_Port_PortType, to be set,
 *             Level - level, port pin has to be set to
 *                     (BRSHW_PORT_LOGIC_LOW or BRSHW_PORT_LOGIC_HIGH).
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsHwPortInitPowerOn(),
 *             BrsHwEvaBoardInitPowerOn(), BrsHw_WriteDio_TCM_SDA_OUT() and
 *             BrsHw_WriteDio_TCM_CLK_OUT() locally.
 */
/*****************************************************************************/
void BrsHwPort_SetLevel(brsHw_Port_PortType p, uint8 Level)
{
  if (Level != BRSHW_PORT_LOGIC_LOW)
  {
#if defined (BRSHW_SIU_GROUP_B) || defined (BRSHW_SIU_GROUP_D_2)
    SIU_GPDO((p.muxMSCRValue)) = BRSHW_PORT_LOGIC_HIGH; /* set port-pin-level to logic high */
#else
    SIU_GPDO((p.portGroup * 16 + p.portNumber)) = BRSHW_PORT_LOGIC_HIGH; /* set port-pin-level to logic high */
#endif
  }
  else
  {
#if defined (BRSHW_SIU_GROUP_B) || defined (BRSHW_SIU_GROUP_D_2)
    SIU_GPDO((p.muxMSCRValue)) = BRSHW_PORT_LOGIC_LOW; /* set port-pin-level to logic low */
#else
    SIU_GPDO((p.portGroup * 16 + p.portNumber)) = BRSHW_PORT_LOGIC_LOW; /* set port-pin-level to logic low */
#endif
  }
}
# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_STOP_SEC_RAM_CODE
  #include "Brs_MemMap.h"   /* PRQA S 5087 *//* MD_MSR_19.1 */
# endif

/*****************************************************************************/
/**
 * @brief      This function reads the input level of a port pin.
 * @pre        Port pin configuartions available within BrsHw_Ports.h,
 *             no DrvPort used for port pin initialization and
 *             transferred port pin has to be initialized as input pin with
 *             GPIO functionality.
 * @param[in]  p - brsHw_Port_PortType, to be read.
 * @param[out] -
 * @return     Level, read from port pin
 *             (BRSHW_PORT_LOGIC_LOW or BRSHW_PORT_LOGIC_HIGH).
 * @context    Function is called from BrsHw_WriteDio_TCM_SDA_OUT() and
 *             BrsHw_WriteDio_TCM_CLK_OUT() locally.
 */
/*****************************************************************************/
uint8 BrsHwPort_GetLevel(brsHw_Port_PortType p)
{
  uint32 temp;
#if defined (BRSHW_SIU_GROUP_B) || defined (BRSHW_SIU_GROUP_D_2)
  temp = SIU_GPDI((p.muxMSCRValue));
#else
  temp = SIU_GPDI((p.portGroup*16 + p.portNumber));
#endif

  if(temp != 0x00000000)
  {
    return BRSHW_PORT_LOGIC_HIGH;
  }
  else
  {
    return BRSHW_PORT_LOGIC_LOW;
  }
}

# if defined (BRS_ENABLE_TCM_SUPPORT)
/*******************************************************************************
  TCM Write Functions
********************************************************************************/
void BrsHw_WriteDio_TCM_SDA_OUT(uint8 Level)
{
  BrsHwPort_SetLevel(BRSHW_PORT_TCM_SDA_OUT, Level);
}

void BrsHw_WriteDio_TCM_CLK_OUT(uint8 Level)
{
  BrsHwPort_SetLevel(BRSHW_PORT_TCM_CLK_OUT, Level);
}

/*******************************************************************************
  TCM Read Functions
********************************************************************************/
uint8 BrsHw_ReadDio_TCM_SDA_IN(void)
{
  return BrsHwPort_GetLevel(BRSHW_PORT_TCM_SDA_IN);
}

uint8 BrsHw_ReadDio_TCM_CLK_IN(void)
{
  return BrsHwPort_GetLevel(BRSHW_PORT_TCM_CLK_IN);
}
# endif /*BRS_ENABLE_TCM_SUPPORT*/
#endif /*!VGEN_ENABLE_DRVPORT*/

/*****************************************************************************/
/**
 * @brief      This function has to be used to initialize the used ports.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from main@BrsMain or EcuM at power on initialization
 */
/*****************************************************************************/
void BrsHwPortInitPowerOn(void)
{
#if defined (VGEN_ENABLE_DRVPORT)
# if defined (BRS_ENABLE_SUPPORT_LEDS)          || \
     defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN) || \
     defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  #error "Configure the valid toggle pins within your DrvPort config. Or disable the depending BRS mechanism."*/
# endif

#else
# if defined (BRS_ENABLE_SUPPORT_LEDS)
  BrsHwInitPortOutput(BRSHW_PORT_LED);

  /* Set LED on EVB demo board to show the system is alive */
  BrsHwTogglePin(BRSHW_TOGGLEPIN_LED);
# endif /*BRS_ENABLE_SUPPORT_LEDS*/

# if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
  BrsHwInitPortOutput(BRSHW_PORT_TOGGLE_WD);
# endif

# if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  BrsHwInitPortOutput(BRSHW_PORT_TOGGLE_CUSTOM);
# endif

# if defined (BRS_ENABLE_TCM_SUPPORT)
  BrsHwInitPortOutput(BRSHW_PORT_TCM_CLK_OUT);
  BrsHwInitPortOutput(BRSHW_PORT_TCM_SDA_OUT);
  BrsHwInitPortInput(BRSHW_PORT_TCM_SDA_IN, BRSHW_PORT_MUX_TCM_SDA_IN);
  BrsHwInitPortInput(BRSHW_PORT_TCM_CLK_IN, BRSHW_PORT_MUX_TCM_CLK_IN);
#  if defined (BRSHW_USE_TCM_EXT_IRQ)
  BrsHwInitPortInput(BRSHW_PORT_TCM_INTA_IN, BRSHW_PORT_MUX_TCM_INTA_IN);
  BrsHwInitPortInput(BRSHW_PORT_TCM_INTB_IN, BRSHW_PORT_MUX_TCM_INTB_IN);
#  endif
# endif /*BRS_ENABLE_TCM_SUPPORT*/

/*******************************************************************************
  CAN driver
********************************************************************************/
# if defined (VGEN_ENABLE_CAN_DRV)
#  if defined (_BRSHW_PORT_CAN_WAKEUP_IRQ_0)
  BrsHwInitPortInput(BRSHW_PORT_CAN_WAKEUP_IRQ_0, BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_0);
#  endif
#  if defined (_BRSHW_PORT_CAN_WAKEUP_IRQ_1)
  BrsHwInitPortInput(BRSHW_PORT_CAN_WAKEUP_IRQ_1, BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_1);
#  endif
#  if defined (_BRSHW_PORT_CAN_WAKEUP_IRQ_2)
  BrsHwInitPortInput(BRSHW_PORT_CAN_WAKEUP_IRQ_2, BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_2);
#  endif
#  if defined (_BRSHW_PORT_CAN_WAKEUP_IRQ_3)
  BrsHwInitPortInput(BRSHW_PORT_CAN_WAKEUP_IRQ_3, BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_3);
#  endif
#  if defined (_BRSHW_PORT_CAN_WAKEUP_IRQ_4)
  BrsHwInitPortInput(BRSHW_PORT_CAN_WAKEUP_IRQ_4, BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_4);
#  endif
#  if defined (_BRSHW_PORT_CAN_WAKEUP_IRQ_5)
  BrsHwInitPortInput(BRSHW_PORT_CAN_WAKEUP_IRQ_5, BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_5);
#  endif
#  if defined (_BRSHW_PORT_CAN_WAKEUP_IRQ_6)
  BrsHwInitPortInput(BRSHW_PORT_CAN_WAKEUP_IRQ_6, BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_6);
#  endif
#  if defined (_BRSHW_PORT_CAN_WAKEUP_IRQ_7)
  BrsHwInitPortInput(BRSHW_PORT_CAN_WAKEUP_IRQ_7, BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_7);
#  endif
#  if defined (_BRSHW_PORT_CAN_WAKEUP_IRQ_8)
  BrsHwInitPortInput(BRSHW_PORT_CAN_WAKEUP_IRQ_8, BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_8);
#  endif
#  if defined (_BRSHW_PORT_CAN_WAKEUP_IRQ_9)
  BrsHwInitPortInput(BRSHW_PORT_CAN_WAKEUP_IRQ_9, BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_9);
#  endif
#  if defined (_BRSHW_PORT_CAN_WAKEUP_IRQ_10)
  BrsHwInitPortInput(BRSHW_PORT_CAN_WAKEUP_IRQ_10, BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_10);
#  endif
#  if defined (_BRSHW_PORT_CAN_WAKEUP_IRQ_11)
  BrsHwInitPortInput(BRSHW_PORT_CAN_WAKEUP_IRQ_11, BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_11);
#  endif
#  if defined (_BRSHW_PORT_CAN_WAKEUP_IRQ_12)
  BrsHwInitPortInput(BRSHW_PORT_CAN_WAKEUP_IRQ_12, BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_12);
#  endif
#  if defined (_BRSHW_PORT_CAN_WAKEUP_IRQ_13)
  BrsHwInitPortInput(BRSHW_PORT_CAN_WAKEUP_IRQ_13, BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_13);
#  endif
#  if defined (_BRSHW_PORT_CAN_WAKEUP_IRQ_14)
  BrsHwInitPortInput(BRSHW_PORT_CAN_WAKEUP_IRQ_14, BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_14);
#  endif
#  if defined (_BRSHW_PORT_CAN_WAKEUP_IRQ_15)
  BrsHwInitPortInput(BRSHW_PORT_CAN_WAKEUP_IRQ_15, BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_15);
#  endif

#  if defined (kCanPhysToLogChannelIndex_0)
  BrsHwInitPortOutput(BRSHW_PORT_CAN0_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN0_RX, BRSHW_PORT_MUX_CAN0_RX);
#   if defined(_BRSHW_PORT_CAN0_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN0_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN0_TRCV_STB, BRSHW_PORT_LOGIC_LOW);
#   endif
#   if defined (_BRSHW_PORT_CAN0_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN0_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN0_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#   endif
#  endif /*kCanPhysToLogChannelIndex_0*/

#  if defined (kCanPhysToLogChannelIndex_1)
  BrsHwInitPortOutput(BRSHW_PORT_CAN1_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN1_RX, BRSHW_PORT_MUX_CAN1_RX);
#   if defined(_BRSHW_PORT_CAN1_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN1_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN1_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#   endif
#   if defined (_BRSHW_PORT_CAN1_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN1_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN1_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#   endif
#  endif /*kCanPhysToLogChannelIndex_1*/

#  if defined (kCanPhysToLogChannelIndex_2)
  BrsHwInitPortOutput(BRSHW_PORT_CAN2_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN2_RX, BRSHW_PORT_MUX_CAN2_RX);
#   if defined(_BRSHW_PORT_CAN2_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN2_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN2_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#   endif
#   if defined (_BRSHW_PORT_CAN2_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN2_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN2_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#   endif
#  endif /*kCanPhysToLogChannelIndex_2*/

#  if defined (kCanPhysToLogChannelIndex_3)
  BrsHwInitPortOutput(BRSHW_PORT_CAN3_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN3_RX, BRSHW_PORT_MUX_CAN3_RX);
#   if defined(_BRSHW_PORT_CAN3_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN3_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN3_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#   endif
#   if defined (_BRSHW_PORT_CAN3_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN3_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN3_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#   endif
#  endif /*kCanPhysToLogChannelIndex_3*/

#  if defined (kCanPhysToLogChannelIndex_4)
  BrsHwInitPortOutput(BRSHW_PORT_CAN4_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN4_RX, BRSHW_PORT_MUX_CAN4_RX);
#   if defined(_BRSHW_PORT_CAN4_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN4_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN4_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#   endif
#    if defined (_BRSHW_PORT_CAN4_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN4_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN4_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#    endif
#  endif /*kCanPhysToLogChannelIndex_4*/

#  if defined (kCanPhysToLogChannelIndex_5)
  BrsHwInitPortOutput(BRSHW_PORT_CAN5_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN5_RX, BRSHW_PORT_MUX_CAN5_RX);
#   if defined(_BRSHW_PORT_CAN5_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN5_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN5_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#   endif
#    if defined (_BRSHW_PORT_CAN5_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN5_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN5_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#    endif
#  endif /*kCanPhysToLogChannelIndex_5*/

#  if defined (kCanPhysToLogChannelIndex_6)
  BrsHwInitPortOutput(BRSHW_PORT_CAN6_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN6_RX, BRSHW_PORT_MUX_CAN6_RX);
#   if defined(_BRSHW_PORT_CAN6_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN6_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN6_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#   endif
#   if defined (_BRSHW_PORT_CAN6_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN6_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN6_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#   endif
#  endif /*kCanPhysToLogChannelIndex_6*/

#  if defined (kCanPhysToLogChannelIndex_7)
  BrsHwInitPortOutput(BRSHW_PORT_CAN7_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN7_RX, BRSHW_PORT_MUX_CAN7_RX);
#   if defined(_BRSHW_PORT_CAN7_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN7_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN7_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#   endif
#   if defined (_BRSHW_PORT_CAN7_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN7_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN7_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#   endif
#  endif /*kCanPhysToLogChannelIndex_7*/

#  if defined (kCan_30_McanPhysToLogChannelIndex_0)
  BrsHwInitPortOutput(BRSHW_PORT_CAN0_SECOND_CANCELL_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN0_SECOND_CANCELL_RX, BRSHW_PORT_MUX_CAN0_SECOND_CANCELL_RX);
#   if defined(_BRSHW_PORT_CAN0_TRCV_SECOND_CANCELL_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN0_TRCV_SECOND_CANCELL_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN0_TRCV_SECOND_CANCELL_STB, BRSHW_PORT_LOGIC_HIGH);
#   endif
#   if defined (_BRSHW_PORT_CAN0_TRCV_SECOND_CANCELL_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN0_TRCV_SECOND_CANCELL_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN0_TRCV_SECOND_CANCELL_EN, BRSHW_PORT_LOGIC_HIGH);
#   endif
#  endif /*kCan_30_McanPhysToLogChannelIndex_0*/

#  if defined (kCan_30_McanPhysToLogChannelIndex_1)
  BrsHwInitPortOutput(BRSHW_PORT_CAN1_SECOND_CANCELL_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN1_SECOND_CANCELL_RX, BRSHW_PORT_MUX_CAN1_SECOND_CANCELL_RX);
#   if defined(_BRSHW_PORT_CAN1_TRCV_SECOND_CANCELL_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN1_TRCV_SECOND_CANCELL_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN1_TRCV_SECOND_CANCELL_STB, BRSHW_PORT_LOGIC_HIGH);
#   endif
#   if defined (_BRSHW_PORT_CAN1_TRCV_SECOND_CANCELL_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN1_TRCV_SECOND_CANCELL_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN1_TRCV_SECOND_CANCELL_EN, BRSHW_PORT_LOGIC_HIGH);
#   endif
#  endif /*kCan_30_McanPhysToLogChannelIndex_0*/
# endif /*VGEN_ENABLE_CAN_DRV*/

/*******************************************************************************
  LIN driver
********************************************************************************/
# if defined (VGEN_ENABLE_LIN_DRV)
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
  BrsHwInitPortOutput(BRSHW_PORT_LIN0_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN0_RX, BRSHW_PORT_MUX_LIN0_RX);
#   if defined(_BRSHW_PORT_CONF_LIN)
  BrsHwInitPortConfig(BRSHW_PORT_LIN0_RX, BRSHW_PORT_CONF_LIN);
#   endif
#   if defined(_BRSHW_PORT_LIN0_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_LIN0_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_LIN0_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#   endif
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_0*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
  BrsHwInitPortOutput(BRSHW_PORT_LIN1_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN1_RX, BRSHW_PORT_MUX_LIN1_RX);
#   if defined(_BRSHW_PORT_CONF_LIN)
  BrsHwInitPortConfig(BRSHW_PORT_LIN1_RX, BRSHW_PORT_CONF_LIN);
#   endif
#   if defined(_BRSHW_PORT_LIN1_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_LIN1_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_LIN1_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#   endif
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_1*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_2)
  BrsHwInitPortOutput(BRSHW_PORT_LIN2_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN2_RX, BRSHW_PORT_MUX_LIN2_RX);
#   if defined(_BRSHW_PORT_CONF_LIN)
  BrsHwInitPortConfig(BRSHW_PORT_LIN2_RX, BRSHW_PORT_CONF_LIN);
#   endif
#   if defined(_BRSHW_PORT_LIN2_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_LIN2_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_LIN2_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#   endif
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_2*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_3)
  BrsHwInitPortOutput(BRSHW_PORT_LIN3_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN3_RX, BRSHW_PORT_MUX_LIN3_RX);
#   if defined(_BRSHW_PORT_CONF_LIN)
  BrsHwInitPortConfig(BRSHW_PORT_LIN3_RX, BRSHW_PORT_CONF_LIN);
#   endif
#   if defined(_BRSHW_PORT_LIN3_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_LIN3_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_LIN3_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#   endif
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_3*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_4)
  BrsHwInitPortOutput(BRSHW_PORT_LIN4_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN4_RX, BRSHW_PORT_MUX_LIN4_RX);
#   if defined(_BRSHW_PORT_CONF_LIN)
  BrsHwInitPortConfig(BRSHW_PORT_LIN4_RX, BRSHW_PORT_CONF_LIN);
#   endif
#   if defined(_BRSHW_PORT_LIN4_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_LIN4_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_LIN4_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#   endif
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_4*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_5)
  BrsHwInitPortOutput(BRSHW_PORT_LIN5_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN5_RX, BRSHW_PORT_MUX_LIN5_RX);
#   if defined(_BRSHW_PORT_CONF_LIN)
  BrsHwInitPortConfig(BRSHW_PORT_LIN5_RX, BRSHW_PORT_CONF_LIN);
#   endif
#   if defined(_BRSHW_PORT_LIN5_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_LIN5_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_LIN5_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#   endif
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_5*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_6)
  BrsHwInitPortOutput(BRSHW_PORT_LIN6_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN6_RX, BRSHW_PORT_MUX_LIN6_RX);
#   if defined(_BRSHW_PORT_CONF_LIN)
  BrsHwInitPortConfig(BRSHW_PORT_LIN6_RX, BRSHW_PORT_CONF_LIN);
#   endif
#   if defined(_BRSHW_PORT_LIN6_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_LIN6_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_LIN6_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#   endif
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_6*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_7)
  BrsHwInitPortOutput(BRSHW_PORT_LIN7_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN7_RX, BRSHW_PORT_MUX_LIN7_RX);
#   if defined(_BRSHW_PORT_CONF_LIN)
  BrsHwInitPortConfig(BRSHW_PORT_LIN7_RX, BRSHW_PORT_CONF_LIN);
#   endif
#   if defined(_BRSHW_PORT_LIN7_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_LIN7_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_LIN7_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#   endif
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_7*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_8)
  BrsHwInitPortOutput(BRSHW_PORT_LIN8_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN8_RX, BRSHW_PORT_MUX_LIN8_RX);
#   if defined(_BRSHW_PORT_CONF_LIN)
  BrsHwInitPortConfig(BRSHW_PORT_LIN8_RX, BRSHW_PORT_CONF_LIN);
#   endif
#   if defined(_BRSHW_PORT_LIN8_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_LIN8_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_LIN8_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#   endif
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_8*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_9)
  BrsHwInitPortOutput(BRSHW_PORT_LIN9_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN9_RX, BRSHW_PORT_MUX_LIN9_RX);
#   if defined(_BRSHW_PORT_CONF_LIN)
  BrsHwInitPortConfig(BRSHW_PORT_LIN9_RX, BRSHW_PORT_CONF_LIN);
#   endif
#   if defined(_BRSHW_PORT_LIN9_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_LIN9_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_LIN9_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#   endif
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_9*/
# endif /*VGEN_ENABLE_LIN_DRV*/

/*******************************************************************************
  FLEXRAY driver
********************************************************************************/
# if defined (VGEN_ENABLE_DRVFR__BASEASR)
#  if (FR_CHANNEL_A_USED == STD_ON)
  BrsHwInitPortOutput(BRSHW_PORT_FR0A_TX);
  BrsHwInitPortInput(BRSHW_PORT_FR0A_RX, BRSHW_PORT_MUX_FR0A_RX);
  BrsHwInitPortOutput(BRSHW_PORT_FR0A_TXEN);
  /*BrsHwInitPortInput(BRSHW_PORT_FR0A_ERRNA); ERRNA-Pin not necessary on this platform*/
#   if defined(_BRSHW_PORT_FR0A_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_FR0A_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_FR0A_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#   endif
#   if defined (_BRSHW_PORT_FR0A_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_FR0A_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_FR0A_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#   endif
#  endif /*FR_CHANNEL_A_USED*/

#  if (FR_CHANNEL_B_USED == STD_ON)
  BrsHwInitPortOutput(BRSHW_PORT_FR0B_TX);
  BrsHwInitPortInput(BRSHW_PORT_FR0B_RX, BRSHW_PORT_MUX_FR0B_RX);
  BrsHwInitPortOutput(BRSHW_PORT_FR0B_TXEN);
  /*BrsHwInitPortInput(BRSHW_PORT_FR0B_ERRNA); ERRNA-Pin not necessary on this platform */
#   if defined(_BRSHW_PORT_FR0B_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_FR0B_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_FR0B_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#   endif
#   if defined (_BRSHW_PORT_FR0B_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_FR0B_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_FR0B_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#   endif
#  endif /*FR_CHANNEL_B_USED*/
# endif /*VGEN_ENABLE_DRVFR__BASEASR*/

/*******************************************************************************
  ETHERNET driver
********************************************************************************/
# if defined (VGEN_ENABLE_DRVETH__BASEASR)
  /* -- Transmitter signals -- */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_REFCLK, BRSHW_PORT_MUX_ETH0_REFCLK);
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD0);
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD1);
#  if defined (_BRSHW_PORT_ETH0_TXD2)
  /* Transmit signal 2 is obsolete within RMII */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD2);
#  endif
#  if defined (_BRSHW_PORT_ETH0_TXD3)
  /* Transmit signal 3 is obsolete within RMII */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXD3);
#  endif
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXEN);
#  if defined (_BRSHW_PORT_ETH0_TXER)
  /* Transmit Error signal is only optional within MII and obsolete within RMII */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_TXER);
#  endif
#  if defined (_BRSHW_PORT_ETH0_RXER)
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXER, BRSHW_PORT_MUX_ETH0_RXER);
#  endif

  /* -- Receiver signals -- */
#  if defined (_BRSHW_PORT_ETH0_RXCLK)
  /* Receive clock signal is obsolete within RMII */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXCLK, BRSHW_PORT_MUX_ETH0_RXCLK);
#  endif
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD0, BRSHW_PORT_MUX_ETH0_RXD0);
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD1, BRSHW_PORT_MUX_ETH0_RXD1);
#  if defined (_BRSHW_PORT_ETH0_RXD2)
  /* Receive signal 2 is obsolete within RMII */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD2, BRSHW_PORT_MUX_ETH0_RXD2);
#  endif
#  if defined (_BRSHW_PORT_ETH0_RXD3)
  /* Receive signal 3 is obsolete within RMII */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXD3, BRSHW_PORT_MUX_ETH0_RXD3);
#  endif
#  if defined (BRSHW_SIU_GROUP_E)
  BrsHwInitPortInput(BRSHW_PORT_ETH0_CRS, BRSHW_PORT_MUX_ETH0_CRS);
  BrsHwInitPortInput(BRSHW_PORT_ETH0_RXDV, BRSHW_PORT_MUX_ETH0_RXDV);
  BrsHwInitPortInput(BRSHW_PORT_ETH0_COL, BRSHW_PORT_MUX_ETH0_COL);
#  else
BrsHwInitPortInput(BRSHW_PORT_ETH0_CRSDV, BRSHW_PORT_MUX_ETH0_CRSDV);
#  endif
  /* -- Management signals -- */
  BrsHwInitPortInput(BRSHW_PORT_ETH0_MDIO, BRSHW_PORT_MUX_ETH0_MDIO);
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_MDIO);
#  if defined (_BRSHW_PORT_ETH0_MDC)
  /* Management data clock not always needed */
  BrsHwInitPortOutput(BRSHW_PORT_ETH0_MDC);
#  endif

#  if defined (_BRSHW_PORT_ETH0_TRCV_EN)
  BrsHwInitPortInput(BRSHW_PORT_ETH0_TRCV_EN, BRSHW_PORT_MUX_ETH0_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_ETH0_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#  endif
# endif /*VGEN_ENABLE_DRVETH__BASEASR*/

#endif /*!VGEN_ENABLE_DRVPORT*/
}

#if defined (BRSHW_ENABLE_TIMER_INTERRUPT)
/*****************************************************************************/
/**
 * @brief      Programmable Interrupt Timer, Timer initialization for 'FakeOS'
 *             1ms time base generation
 * @pre        Interrupt vector must be correct configured and the ISR
 *             function itself should exist.
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from main@BrsMain at power on initialization.
 */
/*****************************************************************************/
void BrsHwTimeBaseInitPowerOn(void)
{
#if defined (BRSHW_TIMER_GROUP_A)
  PIT_MCR   = (uint32)0x01;  /* Enable the clock for timer0, timer is stopped in debug mode. */
# if defined (BRSHW_FMPLL_GROUP_A) || defined (BRSHW_FMPLL_GROUP_B)
  PIT_LDVAL0 = (uint32) (BRS_TIMEBASE_CLOCK * 1000/4); /* Timer0 load value register (1/{x}Mhz * {x}*1000 = 1ms) Hint: With this PLL the PIT is counting with CPU-Frequency/4! */
# else
  PIT_LDVAL0 = (uint32) (BRS_TIMEBASE_CLOCK * 1000);   /* Timer0 load value register (1/{x}Mhz * {x}*1000 = 1ms) */
# endif
  PIT_TFLG0  = 0x1; /* Clear the timer0 interrupt */
  PIT_TCTRL0 = 0x3; /* Timer0 interrupt and Timer enabled */
#endif

#if defined (BRSHW_TIMER_GROUP_B)
  EMIOS_MCR = 0x1400F900;          /* Global prescaler=250 -> reg value = 249 */
  EMIOS_CADR0 =BRS_TIMEBASE_CLOCK; /* Formula: Compare Value = (CPU_FREQUENCY * 1ms / Prescaler) !!internal compare registers are 16 Bit -> max. compareval.=0xFFFF!! visagh: /2 Clock Prescaler available and can not be disabled! -> visjhr: /4 prescaler on hardware implemented for emiosA/B -> manual is wrong */
  EMIOS_CCR0 = 0x020202D4;         /* Modulos up/down counter buffered mode, prescaler=1  */
#endif
}

/*****************************************************************************/
/**
 * @brief      Timer interrupt for the 'FakeOS' 1ms time base generation.
 *             This ISR function is not necessary if an OS is used!
 * @pre        Interrupt vector must be correct configured and the ISR
 *             function itself should exist.
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from interrupt vector table if the assigned
 *             timer has set its interrupt flag.
 */
/*****************************************************************************/
void BrsHwTimeBaseInterrupt(void)
{
  /* clear Interrupt of timer0 */
# if defined (BRSHW_TIMER_GROUP_A)
  PIT_TFLG0 = 0x1;
# endif

# if defined (BRSHW_TIMER_GROUP_B)
  EMIOS_CSR0 = 0x1;
# endif

  gbBrsMainIsrMilliSecondFlag++;
}
#else
/* BrsHwTimeBaseInitPowerOn() and BrsHwTimeBaseInterrupt() removed by Organi, because of ALM attributes of project */
#endif /*BRSHW_ENABLE_TIMER_INTERRUPT*/

/*****************************************************************************/
/**
 * @brief      Disable the global system interrupt and initialize the INT
 *             lock handler variables.
 * @pre        Must be the first function call in main@BrsMain
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from main@BrsMain at power on initialization
 */
/*****************************************************************************/
void BrsHwDisableInterruptAtPowerOn(void)
{
  bBrsHwIntDiCounter = 0;

  asm(" wrteei 0"); /* Disable external interrupts */
}

/*****************************************************************************/
/**
 * @brief      Enable the global system interrupt the first time
 * @pre        Must be called after all initializations are done
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from main@BrsMain at power on initialization
 */
/*****************************************************************************/
void BrsHwEnableInterruptAtPowerOn(void)
{
#if defined (BRS_OS_USECASE_BRS) && !defined (BRS_ENABLE_FBL_SUPPORT)
  BrsHwConfigureInterruptsAtPowerOn();
#else
  /* With OsGen7, OS-APIs have to be used for this */
  /*BrsHwConfigureInterruptsAtPowerOn();*/
#endif

  asm(" wrteei 1");
}

#if defined (BRS_OS_USECASE_BRS) && !defined (BRS_ENABLE_FBL_SUPPORT)
/*****************************************************************************/
/**
 * @brief      This function has to be used to initialize the used interrupts.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsHwEnableInterruptAtPowerOn or EcuM-DriverInitThree
 */
/*****************************************************************************/
void BrsHwConfigureInterruptsAtPowerOn(void)
{
  uint16 i = 0;

  /* dummy to prevent compiler warnings */
  i=i;

# if defined (BRSHW_INTERRUPT_TABLE_GROUP_A)
  #define BRSHW_ISR_REQUEST_SENT_TO_CPU0 0x8000
  INTC_MCR = 0x1;      /* Hardware Vector enable */
  INTC_CPR_0 = 0x0;    /* Ensure CPU 0 INTC's current priority is 0 */

#  if defined (BRSHW_TIMER_GROUP_A)
  INTC_PSR(226) = 0x32 | BRSHW_ISR_REQUEST_SENT_TO_CPU0; /* cyclic timer interrupt on processor 2 */
#  endif

#  if defined (VGEN_ENABLE_CAN_DRV)
#   if defined (BRSHW_USED_CANCELL_DEFAULT)
#    if defined (kCanPhysToLogChannelIndex_0)
  for (i=520; i<=530; i++)
  {
    INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  }
#    endif
#    if defined (kCanPhysToLogChannelIndex_1)
  for (i=533; i<=543; i++)
  {
    INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  }
#    endif
#    if defined (kCanPhysToLogChannelIndex_2)
  for (i=546; i<=556; i++)
  {
    INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  }
#    endif
#   endif /*BRSHW_USED_CANCELL_DEFAULT*/
#   if defined (BRSHW_USED_CANCELL_MCAN)
#    if defined (kCan_30_McanPhysToLogChannelIndex_0)
    INTC_PSR(557) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#    endif
#    if defined (kCan_30_McanPhysToLogChannelIndex_0)
    INTC_PSR(558) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#    endif
#   endif /*BRSHW_USED_CANCELL_MCAN*/
#  endif /*VGEN_ENABLE_CAN_DRV*/

#  if defined (VGEN_ENABLE_LIN_DRV)
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
  INTC_PSR(376) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(377) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(378) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
  INTC_PSR(380) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(381) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(382) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_2)
  INTC_PSR(384) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(385) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(386) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_3)
  INTC_PSR(388) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(389) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(390) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#   endif
#  endif /*VGEN_ENABLE_LIN_DRV*/
  
#  if defined (VGEN_ENABLE_DRVFR__BASEASR)
  for (i=453; i<=462; i++)
  {
    #error "currently not tested!"
    INTC_PSR(i) = 0x4 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  }
#  endif
# endif /*BRSHW_INTERRUPT_TABLE_GROUP_A*/

# if defined (BRSHW_INTERRUPT_TABLE_GROUP_B)
  #define BRSHW_ISR_REQUEST_SENT_TO_CPU0 0x00
  #define BRSHW_ISR_REQUEST_SENT_TO_CPU1 0xC0
  INTC_MCR = 0x1;   /* Hardwar Vector enable */
  INTC_CPR_0 = 0x0; /* Ensure CPU 0 INTC's current priority is 0 */
  INTC_CPR_1 = 0x0; /* Ensure CPU 1 INTC's current priority is 0 */

  INTC_PSR(46) = 0x04; /* Set external wakeup Priority = 0x4 */
  INTC_PSR(47) = 0x04; /* Set external wakeup Priority = 0x4 */
  INTC_PSR(48) = 0x04; /* Set external wakeup Priority = 0x4 */
  INTC_PSR(49) = 0x04; /* Set external wakeup Priority = 0x4 */
  INTC_PSR(50) = 0x04; /* Set external wakeup Priority = 0x4 */

  /* Pit channel_0 */
  INTC_PSR(301) = 0x05;

#  if defined (VGEN_ENABLE_CAN_DRV)
#   if defined (BRSHW_USED_CANCELL_DEFAULT)
#    if defined (kCanPhysToLogChannelIndex_0)
  for ( i=152; i<=172; i++)
  {
    INTC_PSR(i) = 0x02;
  }
#    endif
#    if defined (kCanPhysToLogChannelIndex_1)
  for (i=280; i<=300; i++)
  {
    INTC_PSR(i) = 0x02;
  }
#    endif
#    if defined (kCanPhysToLogChannelIndex_2)
  for (i=173; i<=193; i++)
  {
    INTC_PSR(i) = 0x02;
  }
#    endif
#    if defined (kCanPhysToLogChannelIndex_3)
  for (i=308; i<=328; i++)
  {
    INTC_PSR(i) = 0x02;
  }
#    endif
#    if defined (kCanPhysToLogChannelIndex_4)
  for (i=329; i<=349; i++)
  {
    INTC_PSR(i) = 0x02;
  }
#    endif
#   endif /*BRSHW_USED_CANCELL_DEFAULT*/
#   if defined (BRSHW_USED_CANCELL_MCAN)
#    if defined ( kCan_30_McanPhysToLogChannelIndex_0 ) || defined ( kCan_30_McanPhysToLogChannelIndex_1 ) /* M_CAN_0 + M_CAN_1 */
  INTC_PSR(348) = 0x2;
#    endif
#   endif /*RSHW_USED_CANCELL_MCAN*/
#  endif /*VGEN_ENABLE_CAN_DRV*/

#  if defined (VGEN_ENABLE_LIN_DRV)
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
  INTC_PSR(146) = 0x02; /* Set eSCI 0 Interupt Priority = 0x2 */
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
  INTC_PSR(149) = 0x02; /* Set eSCI 1 Interupt Priority = 0x2 */
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_2)
  INTC_PSR(473) = 0x02; /* Set eSCI 2 Interupt Priority = 0x2 */
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_3)
  INTC_PSR(474) = 0x2; /* Set eSCI 3 Interupt Priority = 0x2 */
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_4)
  INTC_PSR(475) = 0x2; /* Set eSCI 4 Interupt Priority = 0x2 */
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_5)
  INTC_PSR(505) = 0x2; /* Set eSCI 5 Interupt Priority = 0x2 */
#   endif
#  endif /*VGEN_ENABLE_LIN_DRV*/

#  if defined (VGEN_ENABLE_DRVFR__BASEASR)
  /* FlexRay Interrupt init */
  for (i=350; i<=357; i++)
  {
   INTC_PSR(i) = 0x03; /* Set FlexRay Interrupt Priority = 0x3 */ /* all interrupts */
  }
#  endif /*VGEN_ENABLE_DRVFR__BASEASR*/
  
#  if defined (VGEN_ENABLE_DRVETH__BASEASR)
  #error "Ethernet IRQ not yet supported!"
#  endif
# endif /*BRSHW_INTERRUPT_TABLE_GROUP_B*/

# if defined (BRSHW_INTERRUPT_TABLE_GROUP_C)
#  if defined (BRS_DERIVATIVE_SPC574Sx)
   #define BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU 0x8000
    INTC_MCR = 0x001;
    INTC_CPR_0 = 0x0;
#  else
  #define BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU 0x2000 /* !!!CPU2!!! */
  INTC_MCR = 0x100; /* Hardware Vector enable (for CPU2!) */
  INTC_CPR_0 = 0x0; /* Ensure CPU 0 INTC's current priority is 0 */
#   if !defined (BRS_DERIVATIVE_SPC574Kxx)
  /* SPC574K only has a passive checker-core as Core1. This core has no own interrupt controller */
  INTC_CPR_1 = 0x0; /* Ensure CPU 1 INTC's current priority is 0 */
#   endif
  INTC_CPR_2 = 0x0;    /* Ensure CPU 2 INTC's current priority is 0 */
#  endif /*else BRS_DERIVATIVE_SPC574Sx*/

#  if defined (BRSHW_TIMER_GROUP_A)
#   if defined (BRS_DERIVATIVE_SPC574Kxx)
  INTC_PSR(240) = 0x32 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU; /* cyclic timer interrupt on processor 2 */
#   else
  /* for MPC5746M the datasheets seems to be wrong. Use 226 instead of 240 for timer interrupt */
  INTC_PSR(226) = 0x32 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU; /* cyclic timer interrupt on processor 2 */
#   endif
#  endif

#  if defined (VGEN_ENABLE_CAN_DRV)
#   if defined (kCanPhysToLogChannelIndex_0)
  INTC_PSR(676) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU; /* MCAN0/TTCAN Line0 combined interrupt on processor 0 */
  INTC_PSR(677) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU; /* MCAN0/TTCAN Line1 combined interrupt on processor 0 */
#   endif
#   if defined (kCanPhysToLogChannelIndex_1)
  INTC_PSR(688) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU; /* MCAN1 Line0 combined interrupt on processor 0 */
  INTC_PSR(689) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU; /* MCAN1 Line1 combined interrupt on processor 0 */
#   endif
#   if defined (kCanPhysToLogChannelIndex_2)
  INTC_PSR(690) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU; /* MCAN2 Line0 combined interrupt on processor 0 */
  INTC_PSR(691) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU; /* MCAN2 Line1 combined interrupt on processor 0 */
#   endif
#   if defined (kCanPhysToLogChannelIndex_3)
  INTC_PSR(692) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU; /* MCAN3 Line0 combined interrupt on processor 0 */
  INTC_PSR(693) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU; /* MCAN3 Line1 combined interrupt on processor 0 */
#   endif
#   if defined (kCanPhysToLogChannelIndex_4)
  INTC_PSR(694) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU; /* MCAN3 Line0 combined interrupt on processor 0 */
  INTC_PSR(695) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU; /* MCAN3 Line1 combined interrupt on processor 0 */
#   endif
#  endif /*VGEN_ENABLE_CAN_DRV*/

#  if defined (VGEN_ENABLE_LIN_DRV)
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
  INTC_PSR(376) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU;
  INTC_PSR(377) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU;
  INTC_PSR(378) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
  INTC_PSR(380) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU;
  INTC_PSR(381) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU;
  INTC_PSR(382) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_2)
  INTC_PSR(384) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU;
  INTC_PSR(385) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU;
  INTC_PSR(386) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_3)
  INTC_PSR(388) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU;
  INTC_PSR(389) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU;
  INTC_PSR(390) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_14)
  INTC_PSR(432) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU;
  INTC_PSR(433) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU;
  INTC_PSR(434) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_15)
  INTC_PSR(436) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU;
  INTC_PSR(437) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU;
  INTC_PSR(438) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU;
#   endif
#  endif /*VGEN_ENABLE_LIN_DRV*/

#  if defined (VGEN_ENABLE_DRVFR__BASEASR)
  for (i=453; i<=462; i++)
  {
    #error "currently not tested!"
    INTC_PSR(i) = 0x4 | BRSHW_ISR_REQUEST_SENT_TO_RUNNING_CPU;
  }
#  endif
# endif /*BRSHW_INTERRUPT_TABLE_GROUP_C*/

# if defined (BRSHW_INTERRUPT_TABLE_GROUP_D)
  #define BRSHW_ISR_REQUEST_SENT_TO_CPU0 0x8000
  INTC_MCR = 0x1;   /* Hardware Vector enable */
  INTC_CPR_0 = 0x0; /* Ensure CPU 0 INTC's current priority is 0 */
#  if !defined (BRS_DERIVATIVE_PC580000x)
  INTC_CPR_1 = 0x0; /* Ensure CPU 1 INTC's current priority is 0 */
#  endif

#  if defined (BRSHW_TIMER_GROUP_B)
  INTC_PSR(16) = 0xF | BRSHW_ISR_REQUEST_SENT_TO_CPU0; /* cyclic timer interrupt on processor 0 */
#  endif

#  if defined (VGEN_ENABLE_CAN_DRV)
#   if defined (kCanPhysToLogChannelIndex_0)
      for (i=52; i<=74; i++)
  {
    INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  }
#     if defined (C_ENABLE_MB64TO95)
      INTC_PSR(287) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#     endif
#     if defined (C_ENABLE_MB96TO127)
      INTC_PSR(288) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#     endif
#   endif
#   if defined (kCanPhysToLogChannelIndex_1)
  for (i=75; i<=97; i++)
  {
    INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  } 
#     if defined (C_ENABLE_MB64TO95)
      INTC_PSR(289) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#     endif
#     if defined (C_ENABLE_MB96TO127)
      INTC_PSR(290) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#     endif
#   endif
#    if defined (kCanPhysToLogChannelIndex_2)
      for (i=239; i<=261; i++)
      {
        INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
      }
#     if defined (C_ENABLE_MB64TO95)
      INTC_PSR(291) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#     endif
#     if defined (C_ENABLE_MB96TO127)
      INTC_PSR(292) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#     endif
#   endif
#  endif /*VGEN_ENABLE_CAN_DRV*/

#  if defined (VGEN_ENABLE_LIN_DRV)
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
#    if defined (BRS_DERIVATIVE_PC580000x) || defined (BRS_DERIVATIVE_PC580002x)
      INTC_PSR(51) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0; /* SCI LIN*/
#    elif defined (BRS_DERIVATIVE_PC580003x)
      for (i=262; i<=264; i++)
      {
        INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
      }
#    endif
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
#    if defined (BRS_DERIVATIVE_PC580003x)
      for (i=265; i<=267; i++)
      {
        INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
      }
#    endif
#   endif
#  endif
#  if defined (VGEN_ENABLE_DRVFR__BASEASR)
  for (i=98; i<=108; i++)
  {
    INTC_PSR(i) = 0x4 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  }
#  endif
# endif /*BRSHW_INTERRUPT_TABLE_GROUP_D*/

# if defined (BRSHW_INTERRUPT_TABLE_GROUP_E)
  #define BRSHW_ISR_REQUEST_SENT_TO_CPU0 0x8000
  #define BRSHW_ISR_REQUEST_SENT_TO_CPU1 0x4000
  INTC_MCR = 0x1;      /* Hardware Vector enable */
  INTC_CPR_0 = 0x0;    /* Ensure CPU 0 INTC's current priority is 0 */

  INTC_PSR(243) = 0x04 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;    /* Set external wakeup Priority = 0x4, processor 0 */
  INTC_PSR(244) = 0x04 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;    /* Set external wakeup Priority = 0x4, processor 0 */

#  if defined (BRSHW_TIMER_GROUP_A)
  INTC_PSR(226) = 0x32 | BRSHW_ISR_REQUEST_SENT_TO_CPU0; /* cyclic timer interrupt on processor 0 */
#  endif

#  if defined (VGEN_ENABLE_CAN_DRV)
#   if defined (kCanPhysToLogChannelIndex_0)
#    if (MPC5748G_CUT == 1) || (!C_CAN_MAX_BUFFER_96)
  for (i=565; i<=573; i++)
#    else
  for (i=565; i<=574; i++)
#    endif
  {
    INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  }
#   endif
#   if defined (kCanPhysToLogChannelIndex_1)
#    if (MPC5748G_CUT == 1) || (!C_CAN_MAX_BUFFER_96)
  for (i=578; i<=585; i++)
#    else
  for (i=578; i<=586; i++)
#    endif
  {
    INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  }
#   endif
#   if defined (kCanPhysToLogChannelIndex_2)
#    if (MPC5748G_CUT == 1) || (!C_CAN_MAX_BUFFER_96)
  for (i=590; i<=597; i++)
#    else
  for (i=590; i<=598; i++)
#    endif
  {
    INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  }
#   endif
#   if defined (kCanPhysToLogChannelIndex_3)
#    if (MPC5748G_CUT == 1) || (!C_CAN_MAX_BUFFER_96)
  for (i=602; i<=609; i++)
#    else
  for (i=602; i<=610; i++)
#    endif
  {
    INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  }
#   endif
#   if defined (kCanPhysToLogChannelIndex_4)
#    if (MPC5748G_CUT == 1) || (!C_CAN_MAX_BUFFER_96)
  for (i=614; i<=621; i++)
#    else
  for (i=614; i<=622; i++)
#    endif
  {
    INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  }
#   endif
#   if defined (kCanPhysToLogChannelIndex_5)
#    if (MPC5748G_CUT == 1) || (!C_CAN_MAX_BUFFER_96)
  for (i=626; i<=633; i++)
#    else
  for (i=626; i<=634; i++)
#    endif
  {
    INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  }
#   endif
#   if defined (kCanPhysToLogChannelIndex_6)
#    if (MPC5748G_CUT == 1) || (!C_CAN_MAX_BUFFER_96)
  for (i=638; i<=645; i++)
#    else
  for (i=638; i<=646; i++)
#    endif
  {
    INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  }
#   endif
#   if defined (kCanPhysToLogChannelIndex_7)
#    if (MPC5748G_CUT == 1) || (!C_CAN_MAX_BUFFER_96)
  for (i=650; i<=657; i++)
#    else
  for (i=650; i<=658; i++)
#    endif
  {
    INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  }
#   endif
#  endif /*VGEN_ENABLE_CAN_DRV*/

#  if defined (VGEN_ENABLE_LIN_DRV)
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
  INTC_PSR(376) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(377) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(378) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
  INTC_PSR(379) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(380) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(381) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_2)
  INTC_PSR(382) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(383) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(384) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_3)
  INTC_PSR(385) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(386) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(387) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_4)
  INTC_PSR(388) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(389) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(390) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_5)
  INTC_PSR(391) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(392) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(393) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_6)
  INTC_PSR(394) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(395) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(396) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_7)
  INTC_PSR(397) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(398) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(399) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_8)
  INTC_PSR(400) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(401) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(402) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_9)
  INTC_PSR(403) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(404) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(405) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_10)
  INTC_PSR(406) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(407) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(408) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_11)
  INTC_PSR(409) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(410) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(411) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_12)
  INTC_PSR(412) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(413) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(414) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_13)
  INTC_PSR(415) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(416) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(417) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_14)
  INTC_PSR(418) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(419) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(420) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_15)
  INTC_PSR(421) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(422) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(423) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_16)
  INTC_PSR(424) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(425) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(426) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_17)
  INTC_PSR(427) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(428) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  INTC_PSR(429) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
#   endif
#  endif /*VGEN_ENABLE_LIN_DRV*/
  
#  if defined (VGEN_ENABLE_DRVFR__BASEASR)
  for (i=453; i<=462; i++)
  {
    INTC_PSR(i) = 0x4 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  }
#  endif
  
#  if defined (VGEN_ENABLE_DRVETH__BASEASR)
#   if (MPC5748G_CUT == 1)
  /* CUT1 has no "ENET Interrupt Group3" Interrupt */
  for (i=210; i<=212; i++)
  {
    INTC_PSR(i) = 0x1 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  }
  for (i=214; i<=218; i++)
  {
    INTC_PSR(i) = 0x1 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  }
#   else
  for (i=210; i<=218; i++)
  {
    INTC_PSR(i) = 0x1 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;
  }
#   endif /*CUT1*/
#  endif /*VGEN_ENABLE_DRVETH__BASEASR*/
# endif /*BRSHW_INTERRUPT_TABLE_GROUP_E*/

# if defined (BRSHW_INTERRUPT_TABLE_GROUP_F)
  #define BRSHW_ISR_REQUEST_SENT_TO_CPU0 0x8000
  INTC_MCR   = 0x1; /* Hardware Vector enable */
  INTC_CPR_0 = 0x0; /* Ensure CPU 0 INTC's current priority is 0 */

#  if defined (BRSHW_TIMER_GROUP_A)
  INTC_PSR(226) = 0x32 | BRSHW_ISR_REQUEST_SENT_TO_CPU0; /* PIT0 IRQ */
#  endif

#  if defined (VGEN_ENABLE_CAN_DRV)
#   if defined (kCanPhysToLogChannelIndex_0)
  INTC_PSR(677) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;  /* FlexCAN_0_MB0_3    */
  INTC_PSR(678) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;  /* FlexCAN_0_MB4_7    */
  INTC_PSR(679) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;  /* FlexCAN_0_MB8_11   */
  INTC_PSR(680) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;  /* FlexCAN_0_MB12_15  */
  INTC_PSR(681) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;  /* FlexCAN_0_MB16_31  */

  INTC_PSR(687) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;  /* FlexCAN_0_ERR      */
  INTC_PSR(688) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;  /* FlexCAN_0_BOFF     */
#   endif
#   if defined (kCanPhysToLogChannelIndex_1)
  INTC_PSR(690) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;  /* FlexCAN_1_MB0_3    */
  INTC_PSR(691) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;  /* FlexCAN_1_MB4_7    */
  INTC_PSR(692) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;  /* FlexCAN_1_MB8_11   */
  INTC_PSR(693) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;  /* FlexCAN_1_MB12_15  */
  INTC_PSR(694) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;  /* FlexCAN_1_MB16_31  */

  INTC_PSR(700) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;  /* FlexCAN_1_ERR      */
  INTC_PSR(701) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU0;  /* FlexCAN_1_BOFF     */
#   endif
#  endif /*VGEN_ENABLE_CAN_DRV*/

#   if defined (VGEN_ENABLE_LIN_DRV)
  #error "LIN IRQ Priority not yet implemented!"
#   endif

#   if defined (VGEN_ENABLE_DRVFR__BASEASR)
  #error "FlexRay IRQ Priority not yet implemented!"
#   endif /*VGEN_ENABLE_DRVFR__BASEASR*/

#   if defined (VGEN_ENABLE_DRVETH__BASEASR)
  #error "Ethernet IRQ Priority not yet implemented!"
#   endif
# endif /*BRSHW_INTERRUPT_TABLE_GROUP_F*/

# if defined (BRSHW_INTERRUPT_TABLE_GROUP_G)
  #define BRSHW_ISR_REQUEST_SENT_TO_CPU0 0x8000
  #define BRSHW_ISR_REQUEST_SENT_TO_CPU1 0x4000
  INTC_MCR &= ~(0x00001101);
  INTC_MCR |=   0x00000010;
  INTC_CPR_0 = 0x0;    /* Ensure CPU 0 INTC's current priority is 0 */
  INTC_CPR_1 = 0x0;    /* Ensure CPU 1 INTC's current priority is 0 */

  INTC_PSR(243) = 0x04 | BRSHW_ISR_REQUEST_SENT_TO_CPU1;    /* Set external wakeup Priority = 0x4, processor 1 */
  INTC_PSR(244) = 0x04 | BRSHW_ISR_REQUEST_SENT_TO_CPU1;    /* Set external wakeup Priority = 0x4, processor 1 */

#  if defined (BRSHW_TIMER_GROUP_A)
  INTC_PSR(226) = 0x32 | BRSHW_ISR_REQUEST_SENT_TO_CPU1; /* cyclic timer interrupt on processor 1 */
#  endif

#  if defined (VGEN_ENABLE_CAN_DRV)
#   if defined (kCanPhysToLogChannelIndex_0)
  for (i=677; i<=682; i++)
  {
    INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU1;
  }
#   endif
#   if defined (kCanPhysToLogChannelIndex_1)
  for (i=683; i<=688; i++)
  {
    INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU1;
  }
#   endif
#   if defined (kCanPhysToLogChannelIndex_2)
  for (i=689; i<=694; i++)
  {
    INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU1;
  }
#   endif
#   if defined (kCanPhysToLogChannelIndex_3)
  for (i=695; i<=700; i++)
  {
    INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU1;
  }
#   endif
#  endif /*VGEN_ENABLE_CAN_DRV*/
  
#  if defined (VGEN_ENABLE_LIN_DRV)
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
  for (i=376; i<=378; i++)
  {
    INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU1;
  }
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
  for (i=380; i<=382; i++)
  {
    INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU1;
  }
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_2)
  for (i=384; i<=386; i++)
  {
    INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU1;
  }
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_3)
  for (i=388; i<=390; i++)
  {
    INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU1;
  }
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_4)
  for (i=392; i<=394; i++)
  {
    INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU1;
  }
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_5)
  for (i=396; i<=398; i++)
  {
    INTC_PSR(i) = 0x3 | BRSHW_ISR_REQUEST_SENT_TO_CPU1;
  }
#   endif
#  endif /*VGEN_ENABLE_LIN_DRV*/
  
#  if defined (VGEN_ENABLE_DRVETH__BASEASR)
  for (i=218; i<=220; i++)
  {
    INTC_PSR(i) = 0x1 | BRSHW_ISR_REQUEST_SENT_TO_CPU1;
  }
#  endif /*VGEN_ENABLE_DRVETH__BASEASR*/
# endif /*BRSHW_INTERRUPT_TABLE_GROUP_G*/

  /***********************************************************
   * Software Vector Mode configuration (SW Dispatching)
   ***********************************************************/
  /* Description: For those derivatives which use SW dispatching, the below code
   *              overwrites the default hardware vector configuration!
   */
# if defined (BRSHW_ENABLE_ISR_SW_DISPATCHING)
#  if defined (BRSHW_INTERRUPT_TABLE_GROUP_C)
  /* Used for MPCMPC5746M and MPC5777M */
  INTC_MCR    = 0x0;                   /* Software Vector mode enabled */
  INTC_ACKR_2 = (uint32)Intvecttable;  /* Configure the vector table base address */

#  elif defined (BRSHW_INTERRUPT_TABLE_GROUP_E)
  INTC_MCR    = 0x0;                   /* Software Vector Mode enabled */
  INTC_ACKR_0 = (uint32)Intvecttable;  /* Configure the vector table base address for CPU0 */

#  elif defined (BRSHW_INTERRUPT_TABLE_GROUP_F)
  INTC_MCR    = 0x0;                   /* Software Vector Mode enabled */
  INTC_ACKR_0 = (uint32)Intvecttable;  /* Configure the vector table base address for CPU0 */

#  else
  #error " Software Vector Mode not yet supported for this IRQ Table Group"
#  endif /*BRSHW_INTERRUPT_TABLE_GROUP_x*/
# endif /*BRSHW_ENABLE_ISR_SW_DISPATCHING*/
}
#endif /*BRS_OS_USECASE_BRS&&!BRS_ENABLE_FBL_SUPPORT*/

/*****************************************************************************/
/**
 * @brief      Disables the global interrupt of the micro. This is done in a
 *             "save way" to allow also nested calls of BrsHwDisableInterrupt
 *             and BrsHwRestoreInterrupt. The first call of BrsHwDisableInterrupt
 *             stores the current state of the global INT flag and the last
 *             call to BrsHwRestoreInterrupt restores the state.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from all modules to disable the global interrupt
 */
/*****************************************************************************/
void BrsHwDisableInterrupt(void)
{
  /* No check for "overrun" of nested INT lock counter is performed, due to more
  *  than 255 nested calls to BrsHwDisableInterrupt are very unlikely. */
  if (bBrsHwIntDiCounter == 0)
  {
    asm(" wrteei 0"); /* Disable external interrupts */
  }

  bBrsHwIntDiCounter++;
}

/*****************************************************************************/
/**
 * @brief      Restores the state of the global interrupt of the micro. This
 *             is done in a "save way" to allow also nested calls of
 *             BrsHwDisableInterrupt and BrsHwRestoreInterrupt. The first call
 *             of BrsHwDisableInterrupt stores the current state of the global
 *             INT flag and the last call to BrsHwRestoreInterrupt restores the
 *             state.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from all modules to enable the global interrupt
 */
/*****************************************************************************/
void BrsHwRestoreInterrupt(void)
{
  /* Check for illegal call of BrsHwRestoreInterrupt. If this function is called
   *  too often, the INT lock works incorrect. */
  if (bBrsHwIntDiCounter == 0)
  {
#if defined (BRS_OS_USECASE_BRS) && !defined (BRS_ENABLE_FBL_SUPPORT)
    BrsMainExceptionHandler( kBrsIllegalInterruptRestoration, BRSERROR_MODULE_BRSHW, (uint16)(__LINE__) );
#else
    /* Check is only performed, if no OS and no FBL are used */
#endif
  }

  bBrsHwIntDiCounter--;
  if (bBrsHwIntDiCounter == 0)
  {
    asm(" wrteei 1");
  }
}

/*****************************************************************************/
/**
 * @brief      restart ECU (issue a software reset or jump to startup code)
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from e.g. ECU state handling
 */
/*****************************************************************************/
void BrsHwSoftwareResetECU(void)
{
  BrsHwDisableInterrupt();

#if defined (BRSHW_SIU_GROUP_B)
  /* Derivatives, which do not contain Mode Entry Module for generating a reset, could generate an interanl system reaset via System Reset Control Register */
  SIU_SRCR |= 0x80000000;
#else
  /* Reset the functional reset escalation threshold register */
  RGM_FRET = RGM_FRET;

  /* Sequence that mode transition are mannaged by hardware */
  ME_MCTL = 0x00005AF0UL; /* Key access 1st step */
  ME_MCTL = 0x0000A50FUL; /* Key access 2nd step */
#endif

  while (1)
  {
    /* Wait until watchdog reset occurs */
  }
}

#if defined (BRS_ENABLE_SUPPORT_LEDS)          || \
    defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN) || \
    defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_START_SEC_RAM_CODE
  #include "Brs_MemMap.h"   /* PRQA S 5087 *//* MD_MSR_19.1 */
# endif
/*****************************************************************************/
/**
 * @brief      This API is used to toggle a PortPin.
 *             Per default, the following parameters are available:
 *               BRSHW_TOGGLEPIN_LED
 *               BRSHW_TOGGLEPIN_WD
 *               BRSHW_TOGGLEPIN_CUSTOM
 *             Depending pins have to be configured within BrsHw_Ports.h.
 * @pre        -
 * @param[in]  Pin has to configure the depending pin to be toggled
 * @param[out] -
 * @return     -
 * @context    Function is called from all modules to set or clear a PortPin
 */
/*****************************************************************************/
void BrsHwTogglePin(brsHw_TogglePin Pin)
{
#if defined (VGEN_ENABLE_DRVDIO)
  #error "Configure the valid DioChannel for the toggle pins within your DrvDio config and set it as value for BrsHw_Dio_ToggleX_Channel. Or disable the depending BRS mechanism."*/
# if defined (BRS_ENABLE_SUPPORT_LEDS)
  Dio_ChannelType BrsHw_Dio_ToggleLED_Channel = DioConf_DioChannel_DioChannel_LED;
# endif
# if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
  Dio_ChannelType BrsHw_Dio_ToggleWD_Channel = DioConf_DioChannel_DioChannel_WD;
# endif
# if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  Dio_ChannelType BrsHw_Dio_ToggleCUSTOM_Channel = DioConf_DioChannel_DioChannel_CUSTOM;
# endif
#endif /*VGEN_ENABLE_DRVDIO*/

#if defined (BRS_ENABLE_SUPPORT_LEDS)
  static uint8 BrsHw_ToggleSwitch_LED = BRSHW_PORT_LOGIC_HIGH;
#endif
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
  static uint8 BrsHw_ToggleSwitch_WD = BRSHW_PORT_LOGIC_HIGH;
#endif
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  static uint8 BrsHw_ToggleSwitch_CUSTOM = BRSHW_PORT_LOGIC_HIGH;
#endif

  switch (Pin)
  {
#if defined (BRS_ENABLE_SUPPORT_LEDS)
    case BRSHW_TOGGLEPIN_LED:
# if defined (VGEN_ENABLE_DRVDIO)
      Dio_WriteChannel(BrsHw_Dio_ToggleLED_Channel, BrsHw_ToggleSwitch_LED & 0x01);
# else
      BrsHwPort_SetLevel(BRSHW_PORT_LED, BrsHw_ToggleSwitch_LED & 0x01);
# endif
      BrsHw_ToggleSwitch_LED++;
      break;
#endif /*BRS_ENABLE_SUPPORT_LEDS*/
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
    case BRSHW_TOGGLEPIN_WD:
# if defined (VGEN_ENABLE_DRVDIO)
      Dio_WriteChannel(BrsHw_Dio_ToggleWD_Channel, BrsHw_ToggleSwitch_WD & 0x01);
# else
      BrsHwPort_SetLevel(BRSHW_PORT_TOGGLE_WD, BrsHw_ToggleSwitch_WD & 0x01);
# endif
      BrsHw_ToggleSwitch_WD++;
      break;
#endif /*BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN*/
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
    case BRSHW_TOGGLEPIN_CUSTOM:
# if defined (VGEN_ENABLE_DRVDIO)
      Dio_WriteChannel(BrsHw_Dio_ToggleCUSTOM_Channel, BrsHw_ToggleSwitch_CUSTOM & 0x01);
# else
      BrsHwPort_SetLevel(BRSHW_PORT_TOGGLE_CUSTOM, BrsHw_ToggleSwitch_CUSTOM & 0x01);
# endif
      BrsHw_ToggleSwitch_CUSTOM++;
      break;
#endif /*BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN*/
    default:
#if defined (BRS_OS_USECASE_BRS) && !defined (BRS_ENABLE_FBL_SUPPORT)
      BrsMainExceptionHandler(kBrsIllegalParameter, BRSERROR_MODULE_BRSHW, (uint16)(__LINE__));
#endif
      break;
  }
}
# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_STOP_SEC_RAM_CODE
  #include "Brs_MemMap.h"   /* PRQA S 5087 *//* MD_MSR_19.1 */
# endif
#endif /*BRS_ENABLE_SUPPORT_LEDS||BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN||BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN*/

/*****************************************************************************/
/**
 * @brief      This API is used for the BRS time measurement support to get a
 *             default time value for all measurements with this platform to
 *             be able to compare time measurements on different dates based
 *             on this time result.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from TimeMeasurement
 */
/*****************************************************************************/
void BrsHwTime100NOP(void)
{
  BrsHwDisableInterrupt();

  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();

  BrsHwRestoreInterrupt();
}

#if !defined (BRS_OS_USECASE_BRS)
# if defined (BRSASR_ENABLE_SAFECTXSUPPORT)
/*****************************************************************/
/* WRAPPER FOR OLD DRVLIN IMPLEMENTATIONS (previous to MSR4 R11) */
/*****************************************************************/
# if defined (VGEN_ENABLE_LIN_DRV)
#  if !defined (Lin_GetHardwareBaseAdressOfChannelConfig)
  #define Lin_GetChannelConfigIdxOfChannelHw(ch) ch
  #define Lin_GetHardwareBaseAdressOfChannelConfig(ch) (uint32*)Lin_HardwareBaseAdress[ch]
#  endif
# endif
/*****************************************************************/
/* WRAPPER FOR OLD DRVCAN IMPLEMENTATIONS (previous to MSR4 R11) */
/*****************************************************************/
# if defined (VGEN_ENABLE_CAN_DRV)
#  if !defined (Can_HwChannelData)
  #define Can_HwChannelData CanHwChannelData
  #define BaseAddressOfHwChannelData CanBaseAddress
#  endif
# endif

/*****************************************************************************/
/**
 * @brief      This API is used to enable hardware access in untrusted mode
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from BrsAsrInitBsw
 */
/*****************************************************************************/
void BrsHw_EnableHwAccess(void)
{
# if defined (BRSHW_USERMODE_ACCESS_GROUP_A) || defined (BRSHW_USERMODE_ACCESS_GROUP_A1) || defined (BRSHW_USERMODE_ACCESS_GROUP_C)
  /* **************************************************** */
  /* UAA Bits of peripherals, to allow access in UserMode */
  /* **************************************************** */
  *((volatile uint32*)(SIU_BASE_ADDR + 0x3FFC)) = 0x00800000;   /* set UAA for Port to enable write to GPDO (SIUL) registers in UserMode */

#  if defined (BRSHW_TIMER_GROUP_A)
  *((volatile uint32*)(BRSHW_TIMER_GROUP_A + 0x3FFC)) = 0x00800000;   /* set UAA-bit for PIT to enable write in usermode */
#  elif defined (BRSHW_TIMER_GROUP_B)
  *((volatile uint32*)(EMIOS_BASE_ADDR + 0x3FFC)) = 0x00800000; /* set UAA-bit for eMIOS to enable write in usermode */
#  endif

#  if defined (VGEN_ENABLE_CAN_DRV)
#   if defined (kCanPhysToLogChannelIndex_0)
  *((volatile uint32*)(Can_HwChannelData[kCanPhysToLogChannelIndex_0].BaseAddressOfHwChannelData + 0x3FFC)) = 0x00800000; /* set UAA-bit for FlexCan channel 0 to enable write in usermode */
#   endif
#   if defined (kCanPhysToLogChannelIndex_1)
  *((volatile uint32*)(Can_HwChannelData[kCanPhysToLogChannelIndex_1].BaseAddressOfHwChannelData + 0x3FFC)) = 0x00800000; /* set UAA-bit for FlexCan channel 1 to enable write in usermode */
#   endif
#   if defined (kCanPhysToLogChannelIndex_2)
  *((volatile uint32*)(Can_HwChannelData[kCanPhysToLogChannelIndex_2].BaseAddressOfHwChannelData + 0x3FFC)) = 0x00800000; /* set UAA-bit for FlexCan channel 2 to enable write in usermode */
#   endif
#   if defined (kCanPhysToLogChannelIndex_3)
  *((volatile uint32*)(Can_HwChannelData[kCanPhysToLogChannelIndex_3].BaseAddressOfHwChannelData + 0x3FFC)) = 0x00800000; /* set UAA-bit for FlexCan channel 3 to enable write in usermode */
#   endif
#  endif /*VGEN_ENABLE_CAN_DRV*/

#  if defined (VGEN_ENABLE_LIN_DRV)
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
  *((volatile uint32*)(Lin_GetHardwareBaseAdressOfChannelConfig(Lin_GetChannelConfigIdxOfChannelHw(0)) + 0x3FFC)) = 0x00800000; /* set UAA-bit for LinFlex0 to enable write in usermode */
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
  *((volatile uint32*)(Lin_GetHardwareBaseAdressOfChannelConfig(Lin_GetChannelConfigIdxOfChannelHw(1)) + 0x3FFC)) = 0x00800000; /* set UAA-bit for LinFlex1 to enable write in usermode */
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_2)
  *((volatile uint32*)(Lin_GetHardwareBaseAdressOfChannelConfig(Lin_GetChannelConfigIdxOfChannelHw(2)) + 0x3FFC)) = 0x00800000; /* set UAA-bit for LinFlex2 to enable write in usermode */
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_3)
  *((volatile uint32*)(Lin_GetHardwareBaseAdressOfChannelConfig(Lin_GetChannelConfigIdxOfChannelHw(3)) + 0x3FFC)) = 0x00800000; /* set UAA-bit for LinFlex3 to enable write in usermode */
#   endif
#  endif /*VGEN_ENABLE_LIN_DRV*/

#  if defined (VGEN_ENABLE_DRVFR__BASEASR)
  *((volatile uint32*)(FR_VCC_REG_START_ADDR + 0x3FFC)) = 0x00800000; /* set UAA-bit for FlexRay to enable write in usermode */
#  endif /*VGEN_ENABLE_DRVFR__BASEASR*/

#  if defined (VGEN_ENABLE_DRVETH__BASEASR)
  {
    /* ENET seems to require at least one supervisor mode access before accessing registers in user mode */
    volatile uint32 ENET_EIR_VALUE = ENET_EIR;
  }
  *((volatile uint32*)(ENET_BASE + 0x3FFC)) = 0x00800000; /* set UAA-bit for ENET to enable write in user mode */
#  endif /*VGEN_ENABLE_DRVETH__BASEASR*/

#  if defined (VGEN_ENABLE_DRVFLS)
  *((volatile uint32*)(FLASH0_BASE + 0x3FFC)) = 0x00800000; /* set UAA-bit for Flash0 to enable write in usermode */
#  endif /*VGEN_ENABLE_DRVFLS*/

#  if defined (VGEN_ENABLE_DRVSPI)
#   if defined (DSPI0_BASE)
  *((volatile uint32*)(DSPI0_BASE + 0x3FFC)) = 0x00800000; /* set UAA-bit for DSPI0 to enable write in usermode */
#   endif
  *((volatile uint32*)(DSPI1_BASE + 0x3FFC)) = 0x00800000; /* set UAA-bit for DSPI1 to enable write in usermode */
  *((volatile uint32*)(DSPI2_BASE + 0x3FFC)) = 0x00800000; /* set UAA-bit for DSPI2 to enable write in usermode */
#   if defined (DSPI3_BASE)
  *((volatile uint32*)(DSPI3_BASE + 0x3FFC)) = 0x00800000; /* set UAA-bit for DSPI3 to enable write in usermode */
#   endif
#  endif /*VGEN_ENABLE_DRVSPI*/

#  if defined (DMAMUX_0_BASE)
  *((volatile uint32*)(DMAMUX_0_BASE + 0x3FFC)) = 0x00800000; /* set UAA-bit for DMAMUX_0 to enable write in usermode */
#  endif
#  if defined (DMAMUX_1_BASE)
  *((volatile uint32*)(DMAMUX_1_BASE + 0x3FFC)) = 0x00800000; /* set UAA-bit for DMAMUX_1 to enable write in usermode */
#  endif

# endif /*BRSHW_USERMODE_ACCESS_GROUP_A/A1/C*/

# if defined (BRSHW_USERMODE_ACCESS_GROUP_B) || defined (BRSHW_USERMODE_ACCESS_GROUP_C)
  /* **************************************************** */
  /* UAA Bits of peripherals, to allow access in UserMode */
  /* **************************************************** */
#  if defined (VGEN_ENABLE_DRVMCU)
  *((volatile uint32*)(MC_ME_BASE + 0x3FFC)) = 0x00800000; /* set UAA-bit for MC_ME to enable write in usermode */
#  endif /*VGEN_ENABLE_DRVMCU*/
# endif /*BRSHW_USERMODE_ACCESS_GROUP_B/C*/

# if defined (BRSHW_USERMODE_ACCESS_GROUP_A) || defined (BRSHW_USERMODE_ACCESS_GROUP_A1) || defined (BRSHW_USERMODE_ACCESS_GROUP_B) || defined (BRSHW_USERMODE_ACCESS_GROUP_C)
  /* *************************************************************** */
  /* PACR/OPACR Register of peripherals, to allow access in UserMode */
  /* *************************************************************** */
  O_PACR_REGISTER_SIUL_ADDR &= O_PACR_REGISTER_SIUL_VALUE; /* set OPACR-Register to enable read/write access to SIUL in usermode */
  O_PACR_REGISTER_PIT_ADDR  &= O_PACR_REGISTER_PIT_VALUE;  /* set OPACR-Register to enable read/write access to PIT in usermode */
  O_PACR_REGISTER_STM_ADDR  &= O_PACR_REGISTER_STM_VALUE;  /* set PACR-Register to enable read/write access to STM Timer in usermode */

#  if defined (O_PACR_REGISTER_EDMA_ADDR)
  O_PACR_REGISTER_EDMA_ADDR &= O_PACR_REGISTER_EDMA_VALUE;
#  endif

#  if defined (O_PACR_REGISTER_DMA_MUX_0_ADDR)
  O_PACR_REGISTER_DMA_MUX_0_ADDR &= O_PACR_REGISTER_DMA_MUX_0_VALUE;
#  endif
#  if defined (O_PACR_REGISTER_DMA_MUX_1_ADDR)
  O_PACR_REGISTER_DMA_MUX_1_ADDR &= O_PACR_REGISTER_DMA_MUX_1_VALUE;
#  endif

#  if defined (VGEN_ENABLE_CAN_DRV)
#   if defined (kCanPhysToLogChannelIndex_0)
  O_PACR_REGISTER_CAN0_ADDR &= O_PACR_REGISTER_CAN0_VALUE; /* set OPACR-Register to enable read/write access to FlexCAN0 in usermode */
#   endif
#   if defined (kCanPhysToLogChannelIndex_1)
  O_PACR_REGISTER_CAN1_ADDR &= O_PACR_REGISTER_CAN1_VALUE; /* set OPACR-Register to enable read/write access to FlexCAN1 in usermode */
#   endif
#   if defined (kCanPhysToLogChannelIndex_2)
  O_PACR_REGISTER_CAN2_ADDR &= O_PACR_REGISTER_CAN2_VALUE; /* set OPACR-Register to enable read/write access to FlexCAN2 in usermode */
#   endif
#   if defined (kCanPhysToLogChannelIndex_3)
  O_PACR_REGISTER_CAN3_ADDR &= O_PACR_REGISTER_CAN3_VALUE; /* set OPACR-Register to enable read/write access to FlexCAN3 in usermode */
#   endif
#  endif /*VGEN_ENABLE_CAN_DRV*/

#  if defined (VGEN_ENABLE_LIN_DRV)
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
  O_PACR_REGISTER_LIN0_ADDR &= O_PACR_REGISTER_LIN0_VALUE; /* set OPACR-Register to enable read/write access to LinFlex0 in usermode */
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
  O_PACR_REGISTER_LIN1_ADDR &= O_PACR_REGISTER_LIN1_VALUE; /* set OPACR-Register to enable read/write access to LinFlex1 in usermode */
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_2)
  O_PACR_REGISTER_LIN2_ADDR &= O_PACR_REGISTER_LIN2_VALUE; /* set OPACR-Register to enable read/write access to LinFlex2 in usermode */
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_3)
  O_PACR_REGISTER_LIN3_ADDR &= O_PACR_REGISTER_LIN3_VALUE; /* set OPACR-Register to enable read/write access to LinFlex3 in usermode */
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_4)
  O_PACR_REGISTER_LIN4_ADDR &= O_PACR_REGISTER_LIN4_VALUE; /* set OPACR-Register to enable read/write access to LinFlex4 in usermode */
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_5)
  O_PACR_REGISTER_LIN5_ADDR &= O_PACR_REGISTER_LIN5_VALUE; /* set OPACR-Register to enable read/write access to LinFlex5 in usermode */
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_6)
  O_PACR_REGISTER_LIN6_ADDR &= O_PACR_REGISTER_LIN6_VALUE; /* set OPACR-Register to enable read/write access to LinFlex6 in usermode */
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_7)
  O_PACR_REGISTER_LIN7_ADDR &= O_PACR_REGISTER_LIN7_VALUE; /* set OPACR-Register to enable read/write access to LinFlex7 in usermode */
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_8)
  O_PACR_REGISTER_LIN8_ADDR &= O_PACR_REGISTER_LIN8_VALUE; /* set OPACR-Register to enable read/write access to LinFlex8 in usermode */
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_9)
  O_PACR_REGISTER_LIN9_ADDR &= O_PACR_REGISTER_LIN9_VALUE; /* set OPACR-Register to enable read/write access to LinFlex9 in usermode */
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_10)
  O_PACR_REGISTER_LIN10_ADDR &= O_PACR_REGISTER_LIN10_VALUE; /* set OPACR-Register to enable read/write access to LinFlex10 in usermode */
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_11)
  O_PACR_REGISTER_LIN11_ADDR &= O_PACR_REGISTER_LIN11_VALUE; /* set OPACR-Register to enable read/write access to LinFlex11 in usermode */
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_12)
  O_PACR_REGISTER_LIN12_ADDR &= O_PACR_REGISTER_LIN12_VALUE; /* set OPACR-Register to enable read/write access to LinFlex12 in usermode */
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_13)
  O_PACR_REGISTER_LIN13_ADDR &= O_PACR_REGISTER_LIN13_VALUE; /* set OPACR-Register to enable read/write access to LinFlex13 in usermode */
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_14)
  O_PACR_REGISTER_LIN14_ADDR &= O_PACR_REGISTER_LIN14_VALUE; /* set OPACR-Register to enable read/write access to LinFlex14 in usermode */
#   endif
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_15)
  O_PACR_REGISTER_LIN15_ADDR &= O_PACR_REGISTER_LIN15_VALUE; /* set OPACR-Register to enable read/write access to LinFlex15 in usermode */
#   endif
#  endif /*VGEN_ENABLE_LIN_DRV*/

#  if defined (VGEN_ENABLE_DRVFR__BASEASR)
  O_PACR_REGISTER_FLEXRAY0_ADDR &= O_PACR_REGISTER_FLEXRAY0_VALUE; /* set OPACR-Register to enable read/write access to FlexRay0 controller in usermode */
#  endif /*VGEN_ENABLE_DRVFR__BASEASR*/

#  if defined (VGEN_ENABLE_DRVETH__BASEASR)
  O_PACR_REGISTER_ETHERNET0_ADDR &= O_PACR_REGISTER_ETHERNET0_VALUE; /* set OPACR-Register to enable read/write access to Ethernet0 controller in usermode */
#  endif /*VGEN_ENABLE_DRVETH__BASEASR*/

#  if defined (VGEN_ENABLE_DRVFLS)
  O_PACR_REGISTER_FLASH0_ADDR &= O_PACR_REGISTER_FLASH0_VALUE; /* set OPACR-Register to enable read/write access to Flash0 in usermode */
#  endif /*VGEN_ENABLE_DRVFLS*/

#  if defined (VGEN_ENABLE_DRVSPI)
  O_PACR_REGISTER_DSPI0_ADDR &= O_PACR_REGISTER_DSPI0_VALUE; /* set OPACR-Register to enable read/write access to DSPI0 in usermode */
  O_PACR_REGISTER_DSPI1_ADDR &= O_PACR_REGISTER_DSPI1_VALUE; /* set OPACR-Register to enable read/write access to DSPI1 in usermode */
  O_PACR_REGISTER_DSPI2_ADDR &= O_PACR_REGISTER_DSPI2_VALUE; /* set OPACR-Register to enable read/write access to DSPI2 in usermode */
#   if defined (O_PACR_REGISTER_DSPI3_ADDR)
  O_PACR_REGISTER_DSPI3_ADDR &= O_PACR_REGISTER_DSPI3_VALUE; /* set OPACR-Register to enable read/write access to DSPI3 in usermode */
#   endif
#  endif /*VGEN_ENABLE_DRVSPI*/

#  if defined (VGEN_ENABLE_DRVWD)
#   if defined (O_PACR_REGISTER_SWT0_ADDR)
  O_PACR_REGISTER_SWT0_ADDR &= O_PACR_REGISTER_SWT0_VALUE; /* set OPACR-Register to enable read/write access to SWT0 in usermode */
#   endif
#   if defined (O_PACR_REGISTER_SWT1_ADDR)
  O_PACR_REGISTER_SWT1_ADDR &= O_PACR_REGISTER_SWT1_VALUE; /* set OPACR-Register to enable read/write access to SWT1 in usermode */
#   endif
#   if defined (O_PACR_REGISTER_SWT2_ADDR)
  O_PACR_REGISTER_SWT2_ADDR &= O_PACR_REGISTER_SWT2_VALUE; /* set OPACR-Register to enable read/write access to SWT2 in usermode */
#   endif
#  endif  /* VGEN_ENABLE_DRVWD */
#  if defined (VGEN_ENABLE_DRVGPT)
#   if defined (O_PACR_REGISTER_EMIOS0_ADDR)
  O_PACR_REGISTER_EMIOS0_ADDR &= O_PACR_REGISTER_EMIOS0_VALUE; /* set OPACR-Register to enable read/write access to EMIOS0 in usermode */
#   endif
#   if defined (O_PACR_REGISTER_EMIOS1_ADDR)
  O_PACR_REGISTER_EMIOS1_ADDR &= O_PACR_REGISTER_EMIOS1_VALUE; /* set OPACR-Register to enable read/write access to EMIOS1 in usermode */
#   endif
#  endif /* VGEN_ENABLE_DRVGPT */

#  if defined (O_PACR_REGISTER_XBAR_0_ADDR)
  O_PACR_REGISTER_XBAR_0_ADDR &= O_PACR_REGISTER_XBAR_0_VALUE;
#  endif
#  if defined (O_PACR_REGISTER_XBAR_1_ADDR)
  O_PACR_REGISTER_XBAR_1_ADDR &= O_PACR_REGISTER_XBAR_1_VALUE;
#  endif
# endif /*BRSHW_USERMODE_ACCESS_GROUP_A/A1/B/C*/

# if defined (BRSHW_USERMODE_ACCESS_GROUP_D)
  O_PACR_REGISTER_DATA_FLASH_ADDR &= O_PACR_REGISTER_DATA_FLASH_VALUE;

#  if defined (VGEN_ENABLE_CAN_DRV)
#   if defined (kCanPhysToLogChannelIndex_0)
  O_PACR_REGISTER_CAN0_ADDR &= O_PACR_REGISTER_CAN0_VALUE; /* set OPACR-Register to enable read/write access to FlexCAN0 in usermode */
#   endif

#   if defined (kCanPhysToLogChannelIndex_2)
  O_PACR_REGISTER_CAN2_ADDR &= O_PACR_REGISTER_CAN2_VALUE; /* set OPACR-Register to enable read/write access to FlexCAN2 in usermode */
#   endif

#   if defined (kCanPhysToLogChannelIndex_1) || defined (kCanPhysToLogChannelIndex_3)
  #error "The configured CAN channel depending OPACR registers are not yet configured!"
#   endif
#  endif /*VGEN_ENABLE_CAN_DRV*/

#  if defined (VGEN_ENABLE_LIN_DRV)
#   if defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
  O_PACR_REGISTER_LIN0_ADDR &= O_PACR_REGISTER_LIN0_VALUE; /* set OPACR-Register to enable read/write access to LinFlex0 in usermode */
#   endif
#  endif
# endif /*BRSHW_USERMODE_ACCESS_GROUP_D*/
}
# else
  /* BrsHw_EnableHwAccess() removed by Organi, because of ALM attributes of project */
# endif /*BRSASR_ENABLE_SAFECTXSUPPORT*/
#endif /*!BRS_OS_USECASE_BRS*/

/**********************************************************************************************************************
  Interrupt handler function protoytpes
**********************************************************************************************************************/
#if defined (BRS_OS_USECASE_BRS) && !defined (BRS_ENABLE_FBL_SUPPORT)
/*****************************************************************************/
/**
 * @brief      This error interrupt handler is used for all platform specific
 *             core exceptions.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called by core exception entries in the
 *             interrupt vector table.
 */
/*****************************************************************************/
void BrsHw_core_exception_handler(void)
{
  BrsMainExceptionHandler(kBrsInterruptHandlerNotInstalled, BRSERROR_MODULE_BRSHW, (uint16)0);
}

/*****************************************************************************/
/**
 * @brief      The dummy interrupt handler has to be used to fill up the
*              interrupt vector table and to catch illegal interrupts in the
*              BRS exception handler.
 * @pre        A wrong IRQ setting or an other malfunction has been occured
*              and an undefined interrupt has been triggered.
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called by unused entries in the interrupt vector table
 */
/*****************************************************************************/
/*
 * Description: Define for Interrupt Service Routine for not expected interrupts.
 *              This define is used to shorten the implementation effort of all interrupt service
 *              routines, which may not happen during normal operation.
 */
#define BRS_DUMMY_INT(inta) \
  void BrsHwDummyInterrupt##inta(void) \
  { \
    BrsMainExceptionHandler(kBrsInterruptHandlerNotInstalled, BRSERROR_MODULE_BRSHW, (uint16)(__LINE__)); \
  }

/* Interrupt Sources 0..15 are CoreExceptions and handled separately */
BRS_DUMMY_INT(16)
BRS_DUMMY_INT(17)
BRS_DUMMY_INT(18)
BRS_DUMMY_INT(19)
BRS_DUMMY_INT(20)
BRS_DUMMY_INT(21)
BRS_DUMMY_INT(22)
BRS_DUMMY_INT(23)
BRS_DUMMY_INT(24)
BRS_DUMMY_INT(25)
BRS_DUMMY_INT(26)
BRS_DUMMY_INT(27)
BRS_DUMMY_INT(28)
BRS_DUMMY_INT(29)
BRS_DUMMY_INT(30)
BRS_DUMMY_INT(31)
BRS_DUMMY_INT(32)
BRS_DUMMY_INT(33)
BRS_DUMMY_INT(34)
BRS_DUMMY_INT(35)
BRS_DUMMY_INT(36)
BRS_DUMMY_INT(37)
BRS_DUMMY_INT(38)
BRS_DUMMY_INT(39)
BRS_DUMMY_INT(40)
BRS_DUMMY_INT(41)
BRS_DUMMY_INT(42)
BRS_DUMMY_INT(43)
BRS_DUMMY_INT(44)
BRS_DUMMY_INT(45)
BRS_DUMMY_INT(46)
BRS_DUMMY_INT(47)
BRS_DUMMY_INT(48)
BRS_DUMMY_INT(49)
BRS_DUMMY_INT(50)
BRS_DUMMY_INT(51)
BRS_DUMMY_INT(52)
BRS_DUMMY_INT(53)
BRS_DUMMY_INT(54)
BRS_DUMMY_INT(55)
BRS_DUMMY_INT(56)
BRS_DUMMY_INT(57)
BRS_DUMMY_INT(58)
BRS_DUMMY_INT(59)
BRS_DUMMY_INT(60)
BRS_DUMMY_INT(61)
BRS_DUMMY_INT(62)
BRS_DUMMY_INT(63)
BRS_DUMMY_INT(64)
BRS_DUMMY_INT(65)
BRS_DUMMY_INT(66)
BRS_DUMMY_INT(67)
BRS_DUMMY_INT(68)
BRS_DUMMY_INT(69)
BRS_DUMMY_INT(70)
BRS_DUMMY_INT(71)
BRS_DUMMY_INT(72)
BRS_DUMMY_INT(73)
BRS_DUMMY_INT(74)
BRS_DUMMY_INT(75)
BRS_DUMMY_INT(76)
BRS_DUMMY_INT(77)
BRS_DUMMY_INT(78)
BRS_DUMMY_INT(79)
BRS_DUMMY_INT(80)
BRS_DUMMY_INT(81)
BRS_DUMMY_INT(82)
BRS_DUMMY_INT(83)
BRS_DUMMY_INT(84)
BRS_DUMMY_INT(85)
BRS_DUMMY_INT(86)
BRS_DUMMY_INT(87)
BRS_DUMMY_INT(88)
BRS_DUMMY_INT(89)
BRS_DUMMY_INT(90)
BRS_DUMMY_INT(91)
BRS_DUMMY_INT(92)
BRS_DUMMY_INT(93)
BRS_DUMMY_INT(94)
BRS_DUMMY_INT(95)
BRS_DUMMY_INT(96)
BRS_DUMMY_INT(97)
BRS_DUMMY_INT(98)
BRS_DUMMY_INT(99)
BRS_DUMMY_INT(100)
BRS_DUMMY_INT(101)
BRS_DUMMY_INT(102)
BRS_DUMMY_INT(103)
BRS_DUMMY_INT(104)
BRS_DUMMY_INT(105)
BRS_DUMMY_INT(106)
BRS_DUMMY_INT(107)
BRS_DUMMY_INT(108)
BRS_DUMMY_INT(109)
BRS_DUMMY_INT(110)
BRS_DUMMY_INT(111)
BRS_DUMMY_INT(112)
BRS_DUMMY_INT(113)
BRS_DUMMY_INT(114)
BRS_DUMMY_INT(115)
BRS_DUMMY_INT(116)
BRS_DUMMY_INT(117)
BRS_DUMMY_INT(118)
BRS_DUMMY_INT(119)
BRS_DUMMY_INT(120)
BRS_DUMMY_INT(121)
BRS_DUMMY_INT(122)
BRS_DUMMY_INT(123)
BRS_DUMMY_INT(124)
BRS_DUMMY_INT(125)
BRS_DUMMY_INT(126)
BRS_DUMMY_INT(127)
BRS_DUMMY_INT(128)
BRS_DUMMY_INT(129)
BRS_DUMMY_INT(130)
BRS_DUMMY_INT(131)
BRS_DUMMY_INT(132)
BRS_DUMMY_INT(133)
BRS_DUMMY_INT(134)
BRS_DUMMY_INT(135)
BRS_DUMMY_INT(136)
BRS_DUMMY_INT(137)
BRS_DUMMY_INT(138)
BRS_DUMMY_INT(139)
BRS_DUMMY_INT(140)
BRS_DUMMY_INT(141)
BRS_DUMMY_INT(142)
BRS_DUMMY_INT(143)
BRS_DUMMY_INT(144)
BRS_DUMMY_INT(145)
BRS_DUMMY_INT(146)
BRS_DUMMY_INT(147)
BRS_DUMMY_INT(148)
BRS_DUMMY_INT(149)
BRS_DUMMY_INT(150)
BRS_DUMMY_INT(151)
BRS_DUMMY_INT(152)
BRS_DUMMY_INT(153)
BRS_DUMMY_INT(154)
BRS_DUMMY_INT(155)
BRS_DUMMY_INT(156)
BRS_DUMMY_INT(157)
BRS_DUMMY_INT(158)
BRS_DUMMY_INT(159)
BRS_DUMMY_INT(160)
BRS_DUMMY_INT(161)
BRS_DUMMY_INT(162)
BRS_DUMMY_INT(163)
BRS_DUMMY_INT(164)
BRS_DUMMY_INT(165)
BRS_DUMMY_INT(166)
BRS_DUMMY_INT(167)
BRS_DUMMY_INT(168)
BRS_DUMMY_INT(169)
BRS_DUMMY_INT(170)
BRS_DUMMY_INT(171)
BRS_DUMMY_INT(172)
BRS_DUMMY_INT(173)
BRS_DUMMY_INT(174)
BRS_DUMMY_INT(175)
BRS_DUMMY_INT(176)
BRS_DUMMY_INT(177)
BRS_DUMMY_INT(178)
BRS_DUMMY_INT(179)
BRS_DUMMY_INT(180)
BRS_DUMMY_INT(181)
BRS_DUMMY_INT(182)
BRS_DUMMY_INT(183)
BRS_DUMMY_INT(184)
BRS_DUMMY_INT(185)
BRS_DUMMY_INT(186)
BRS_DUMMY_INT(187)
BRS_DUMMY_INT(188)
BRS_DUMMY_INT(189)
BRS_DUMMY_INT(190)
BRS_DUMMY_INT(191)
BRS_DUMMY_INT(192)
BRS_DUMMY_INT(193)
BRS_DUMMY_INT(194)
BRS_DUMMY_INT(195)
BRS_DUMMY_INT(196)
BRS_DUMMY_INT(197)
BRS_DUMMY_INT(198)
BRS_DUMMY_INT(199)
BRS_DUMMY_INT(200)
BRS_DUMMY_INT(201)
BRS_DUMMY_INT(202)
BRS_DUMMY_INT(203)
BRS_DUMMY_INT(204)
BRS_DUMMY_INT(205)
BRS_DUMMY_INT(206)
BRS_DUMMY_INT(207)
BRS_DUMMY_INT(208)
BRS_DUMMY_INT(209)
BRS_DUMMY_INT(210)
BRS_DUMMY_INT(211)
BRS_DUMMY_INT(212)
BRS_DUMMY_INT(213)
BRS_DUMMY_INT(214)
BRS_DUMMY_INT(215)
BRS_DUMMY_INT(216)
BRS_DUMMY_INT(217)
BRS_DUMMY_INT(218)
BRS_DUMMY_INT(219)
BRS_DUMMY_INT(220)
BRS_DUMMY_INT(221)
BRS_DUMMY_INT(222)
BRS_DUMMY_INT(223)
BRS_DUMMY_INT(224)
BRS_DUMMY_INT(225)
BRS_DUMMY_INT(226)
BRS_DUMMY_INT(227)
BRS_DUMMY_INT(228)
BRS_DUMMY_INT(229)
BRS_DUMMY_INT(230)
BRS_DUMMY_INT(231)
BRS_DUMMY_INT(232)
BRS_DUMMY_INT(233)
BRS_DUMMY_INT(234)
BRS_DUMMY_INT(235)
BRS_DUMMY_INT(236)
BRS_DUMMY_INT(237)
BRS_DUMMY_INT(238)
BRS_DUMMY_INT(239)
BRS_DUMMY_INT(240)
BRS_DUMMY_INT(241)
BRS_DUMMY_INT(242)
BRS_DUMMY_INT(243)
BRS_DUMMY_INT(244)
BRS_DUMMY_INT(245)
BRS_DUMMY_INT(246)
BRS_DUMMY_INT(247)
BRS_DUMMY_INT(248)
BRS_DUMMY_INT(249)
BRS_DUMMY_INT(250)
BRS_DUMMY_INT(251)
BRS_DUMMY_INT(252)
BRS_DUMMY_INT(253)
BRS_DUMMY_INT(254)
BRS_DUMMY_INT(255)
BRS_DUMMY_INT(256)
BRS_DUMMY_INT(257)
BRS_DUMMY_INT(258)
BRS_DUMMY_INT(259)
BRS_DUMMY_INT(260)
BRS_DUMMY_INT(261)
BRS_DUMMY_INT(262)
BRS_DUMMY_INT(263)
BRS_DUMMY_INT(264)
BRS_DUMMY_INT(265)
BRS_DUMMY_INT(266)
BRS_DUMMY_INT(267)
BRS_DUMMY_INT(268)
BRS_DUMMY_INT(269)
BRS_DUMMY_INT(270)
BRS_DUMMY_INT(271)
BRS_DUMMY_INT(272)
BRS_DUMMY_INT(273)
BRS_DUMMY_INT(274)
BRS_DUMMY_INT(275)
BRS_DUMMY_INT(276)
BRS_DUMMY_INT(277)
BRS_DUMMY_INT(278)
BRS_DUMMY_INT(279)
BRS_DUMMY_INT(280)
BRS_DUMMY_INT(281)
BRS_DUMMY_INT(282)
BRS_DUMMY_INT(283)
BRS_DUMMY_INT(284)
BRS_DUMMY_INT(285)
BRS_DUMMY_INT(286)
BRS_DUMMY_INT(287)
BRS_DUMMY_INT(288)
BRS_DUMMY_INT(289)
BRS_DUMMY_INT(290)
BRS_DUMMY_INT(291)
BRS_DUMMY_INT(292)
BRS_DUMMY_INT(293)
BRS_DUMMY_INT(294)
BRS_DUMMY_INT(295)
BRS_DUMMY_INT(296)
BRS_DUMMY_INT(297)
BRS_DUMMY_INT(298)
BRS_DUMMY_INT(299)
BRS_DUMMY_INT(300)
BRS_DUMMY_INT(301)
BRS_DUMMY_INT(302)
BRS_DUMMY_INT(303)
BRS_DUMMY_INT(304)
BRS_DUMMY_INT(305)
BRS_DUMMY_INT(306)
BRS_DUMMY_INT(307)
BRS_DUMMY_INT(308)
BRS_DUMMY_INT(309)
BRS_DUMMY_INT(310)
BRS_DUMMY_INT(311)
BRS_DUMMY_INT(312)
BRS_DUMMY_INT(313)
BRS_DUMMY_INT(314)
BRS_DUMMY_INT(315)
BRS_DUMMY_INT(316)
BRS_DUMMY_INT(317)
BRS_DUMMY_INT(318)
BRS_DUMMY_INT(319)
BRS_DUMMY_INT(320)
BRS_DUMMY_INT(321)
BRS_DUMMY_INT(322)
BRS_DUMMY_INT(323)
BRS_DUMMY_INT(324)
BRS_DUMMY_INT(325)
BRS_DUMMY_INT(326)
BRS_DUMMY_INT(327)
BRS_DUMMY_INT(328)
BRS_DUMMY_INT(329)
BRS_DUMMY_INT(330)
BRS_DUMMY_INT(331)
BRS_DUMMY_INT(332)
BRS_DUMMY_INT(333)
BRS_DUMMY_INT(334)
BRS_DUMMY_INT(335)
BRS_DUMMY_INT(336)
BRS_DUMMY_INT(337)
BRS_DUMMY_INT(338)
BRS_DUMMY_INT(339)
BRS_DUMMY_INT(340)
BRS_DUMMY_INT(341)
BRS_DUMMY_INT(342)
BRS_DUMMY_INT(343)
BRS_DUMMY_INT(344)
BRS_DUMMY_INT(345)
BRS_DUMMY_INT(346)
BRS_DUMMY_INT(347)
BRS_DUMMY_INT(348)
BRS_DUMMY_INT(349)
BRS_DUMMY_INT(350)
BRS_DUMMY_INT(351)
BRS_DUMMY_INT(352)
BRS_DUMMY_INT(353)
BRS_DUMMY_INT(354)
BRS_DUMMY_INT(355)
BRS_DUMMY_INT(356)
BRS_DUMMY_INT(357)
BRS_DUMMY_INT(358)
BRS_DUMMY_INT(359)
BRS_DUMMY_INT(360)
BRS_DUMMY_INT(361)
BRS_DUMMY_INT(362)
BRS_DUMMY_INT(363)
BRS_DUMMY_INT(364)
BRS_DUMMY_INT(365)
BRS_DUMMY_INT(366)
BRS_DUMMY_INT(367)
BRS_DUMMY_INT(368)
BRS_DUMMY_INT(369)
BRS_DUMMY_INT(370)
BRS_DUMMY_INT(371)
BRS_DUMMY_INT(372)
BRS_DUMMY_INT(373)
BRS_DUMMY_INT(374)
BRS_DUMMY_INT(375)
BRS_DUMMY_INT(376)
BRS_DUMMY_INT(377)
BRS_DUMMY_INT(378)
BRS_DUMMY_INT(379)
BRS_DUMMY_INT(380)
BRS_DUMMY_INT(381)
BRS_DUMMY_INT(382)
BRS_DUMMY_INT(383)
BRS_DUMMY_INT(384)
BRS_DUMMY_INT(385)
BRS_DUMMY_INT(386)
BRS_DUMMY_INT(387)
BRS_DUMMY_INT(388)
BRS_DUMMY_INT(389)
BRS_DUMMY_INT(390)
BRS_DUMMY_INT(391)
BRS_DUMMY_INT(392)
BRS_DUMMY_INT(393)
BRS_DUMMY_INT(394)
BRS_DUMMY_INT(395)
BRS_DUMMY_INT(396)
BRS_DUMMY_INT(397)
BRS_DUMMY_INT(398)
BRS_DUMMY_INT(399)
BRS_DUMMY_INT(400)
BRS_DUMMY_INT(401)
BRS_DUMMY_INT(402)
BRS_DUMMY_INT(403)
BRS_DUMMY_INT(404)
BRS_DUMMY_INT(405)
BRS_DUMMY_INT(406)
BRS_DUMMY_INT(407)
BRS_DUMMY_INT(408)
BRS_DUMMY_INT(409)
BRS_DUMMY_INT(410)
BRS_DUMMY_INT(411)
BRS_DUMMY_INT(412)
BRS_DUMMY_INT(413)
BRS_DUMMY_INT(414)
BRS_DUMMY_INT(415)
BRS_DUMMY_INT(416)
BRS_DUMMY_INT(417)
BRS_DUMMY_INT(418)
BRS_DUMMY_INT(419)
BRS_DUMMY_INT(420)
BRS_DUMMY_INT(421)
BRS_DUMMY_INT(422)
BRS_DUMMY_INT(423)
BRS_DUMMY_INT(424)
BRS_DUMMY_INT(425)
BRS_DUMMY_INT(426)
BRS_DUMMY_INT(427)
BRS_DUMMY_INT(428)
BRS_DUMMY_INT(429)
BRS_DUMMY_INT(430)
BRS_DUMMY_INT(431)
BRS_DUMMY_INT(432)
BRS_DUMMY_INT(433)
BRS_DUMMY_INT(434)
BRS_DUMMY_INT(435)
BRS_DUMMY_INT(436)
BRS_DUMMY_INT(437)
BRS_DUMMY_INT(438)
BRS_DUMMY_INT(439)
BRS_DUMMY_INT(440)
BRS_DUMMY_INT(441)
BRS_DUMMY_INT(442)
BRS_DUMMY_INT(443)
BRS_DUMMY_INT(444)
BRS_DUMMY_INT(445)
BRS_DUMMY_INT(446)
BRS_DUMMY_INT(447)
BRS_DUMMY_INT(448)
BRS_DUMMY_INT(449)
BRS_DUMMY_INT(450)
BRS_DUMMY_INT(451)
BRS_DUMMY_INT(452)
BRS_DUMMY_INT(453)
BRS_DUMMY_INT(454)
BRS_DUMMY_INT(455)
BRS_DUMMY_INT(456)
BRS_DUMMY_INT(457)
BRS_DUMMY_INT(458)
BRS_DUMMY_INT(459)
BRS_DUMMY_INT(460)
BRS_DUMMY_INT(461)
BRS_DUMMY_INT(462)
BRS_DUMMY_INT(463)
BRS_DUMMY_INT(464)
BRS_DUMMY_INT(465)
BRS_DUMMY_INT(466)
BRS_DUMMY_INT(467)
BRS_DUMMY_INT(468)
BRS_DUMMY_INT(469)
BRS_DUMMY_INT(470)
BRS_DUMMY_INT(471)
BRS_DUMMY_INT(472)
BRS_DUMMY_INT(473)
BRS_DUMMY_INT(474)
BRS_DUMMY_INT(475)
BRS_DUMMY_INT(476)
BRS_DUMMY_INT(477)
BRS_DUMMY_INT(478)
BRS_DUMMY_INT(479)
BRS_DUMMY_INT(480)
BRS_DUMMY_INT(481)
BRS_DUMMY_INT(482)
BRS_DUMMY_INT(483)
BRS_DUMMY_INT(484)
BRS_DUMMY_INT(485)
BRS_DUMMY_INT(486)
BRS_DUMMY_INT(487)
BRS_DUMMY_INT(488)
BRS_DUMMY_INT(489)
BRS_DUMMY_INT(490)
BRS_DUMMY_INT(491)
BRS_DUMMY_INT(492)
BRS_DUMMY_INT(493)
BRS_DUMMY_INT(494)
BRS_DUMMY_INT(495)
BRS_DUMMY_INT(496)
BRS_DUMMY_INT(497)
BRS_DUMMY_INT(498)
BRS_DUMMY_INT(499)
BRS_DUMMY_INT(500)
BRS_DUMMY_INT(501)
BRS_DUMMY_INT(502)
BRS_DUMMY_INT(503)
BRS_DUMMY_INT(504)
BRS_DUMMY_INT(505)
BRS_DUMMY_INT(506)
BRS_DUMMY_INT(507)
BRS_DUMMY_INT(508)
BRS_DUMMY_INT(509)
BRS_DUMMY_INT(510)
BRS_DUMMY_INT(511)
BRS_DUMMY_INT(512)
BRS_DUMMY_INT(513)
BRS_DUMMY_INT(514)
BRS_DUMMY_INT(515)
BRS_DUMMY_INT(516)
BRS_DUMMY_INT(517)
BRS_DUMMY_INT(518)
BRS_DUMMY_INT(519)
BRS_DUMMY_INT(520)
BRS_DUMMY_INT(521)
BRS_DUMMY_INT(522)
BRS_DUMMY_INT(523)
BRS_DUMMY_INT(524)
BRS_DUMMY_INT(525)
BRS_DUMMY_INT(526)
BRS_DUMMY_INT(527)
BRS_DUMMY_INT(528)
BRS_DUMMY_INT(529)
BRS_DUMMY_INT(530)
BRS_DUMMY_INT(531)
BRS_DUMMY_INT(532)
BRS_DUMMY_INT(533)
BRS_DUMMY_INT(534)
BRS_DUMMY_INT(535)
BRS_DUMMY_INT(536)
BRS_DUMMY_INT(537)
BRS_DUMMY_INT(538)
BRS_DUMMY_INT(539)
BRS_DUMMY_INT(540)
BRS_DUMMY_INT(541)
BRS_DUMMY_INT(542)
BRS_DUMMY_INT(543)
BRS_DUMMY_INT(544)
BRS_DUMMY_INT(545)
BRS_DUMMY_INT(546)
BRS_DUMMY_INT(547)
BRS_DUMMY_INT(548)
BRS_DUMMY_INT(549)
BRS_DUMMY_INT(550)
BRS_DUMMY_INT(551)
BRS_DUMMY_INT(552)
BRS_DUMMY_INT(553)
BRS_DUMMY_INT(554)
BRS_DUMMY_INT(555)
BRS_DUMMY_INT(556)
BRS_DUMMY_INT(557)
BRS_DUMMY_INT(558)
BRS_DUMMY_INT(559)
BRS_DUMMY_INT(560)
BRS_DUMMY_INT(561)
BRS_DUMMY_INT(562)
BRS_DUMMY_INT(563)
BRS_DUMMY_INT(564)
BRS_DUMMY_INT(565)
BRS_DUMMY_INT(566)
BRS_DUMMY_INT(567)
BRS_DUMMY_INT(568)
BRS_DUMMY_INT(569)
BRS_DUMMY_INT(570)
BRS_DUMMY_INT(571)
BRS_DUMMY_INT(572)
BRS_DUMMY_INT(573)
BRS_DUMMY_INT(574)
BRS_DUMMY_INT(575)
BRS_DUMMY_INT(576)
BRS_DUMMY_INT(577)
BRS_DUMMY_INT(578)
BRS_DUMMY_INT(579)
BRS_DUMMY_INT(580)
BRS_DUMMY_INT(581)
BRS_DUMMY_INT(582)
BRS_DUMMY_INT(583)
BRS_DUMMY_INT(584)
BRS_DUMMY_INT(585)
BRS_DUMMY_INT(586)
BRS_DUMMY_INT(587)
BRS_DUMMY_INT(588)
BRS_DUMMY_INT(589)
BRS_DUMMY_INT(590)
BRS_DUMMY_INT(591)
BRS_DUMMY_INT(592)
BRS_DUMMY_INT(593)
BRS_DUMMY_INT(594)
BRS_DUMMY_INT(595)
BRS_DUMMY_INT(596)
BRS_DUMMY_INT(597)
BRS_DUMMY_INT(598)
BRS_DUMMY_INT(599)
BRS_DUMMY_INT(600)
BRS_DUMMY_INT(601)
BRS_DUMMY_INT(602)
BRS_DUMMY_INT(603)
BRS_DUMMY_INT(604)
BRS_DUMMY_INT(605)
BRS_DUMMY_INT(606)
BRS_DUMMY_INT(607)
BRS_DUMMY_INT(608)
BRS_DUMMY_INT(609)
BRS_DUMMY_INT(610)
BRS_DUMMY_INT(611)
BRS_DUMMY_INT(612)
BRS_DUMMY_INT(613)
BRS_DUMMY_INT(614)
BRS_DUMMY_INT(615)
BRS_DUMMY_INT(616)
BRS_DUMMY_INT(617)
BRS_DUMMY_INT(618)
BRS_DUMMY_INT(619)
BRS_DUMMY_INT(620)
BRS_DUMMY_INT(621)
BRS_DUMMY_INT(622)
BRS_DUMMY_INT(623)
BRS_DUMMY_INT(624)
BRS_DUMMY_INT(625)
BRS_DUMMY_INT(626)
BRS_DUMMY_INT(627)
BRS_DUMMY_INT(628)
BRS_DUMMY_INT(629)
BRS_DUMMY_INT(630)
BRS_DUMMY_INT(631)
BRS_DUMMY_INT(632)
BRS_DUMMY_INT(633)
BRS_DUMMY_INT(634)
BRS_DUMMY_INT(635)
BRS_DUMMY_INT(636)
BRS_DUMMY_INT(637)
BRS_DUMMY_INT(638)
BRS_DUMMY_INT(639)
BRS_DUMMY_INT(640)
BRS_DUMMY_INT(641)
BRS_DUMMY_INT(642)
BRS_DUMMY_INT(643)
BRS_DUMMY_INT(644)
BRS_DUMMY_INT(645)
BRS_DUMMY_INT(646)
BRS_DUMMY_INT(647)
BRS_DUMMY_INT(648)
BRS_DUMMY_INT(649)
BRS_DUMMY_INT(650)
BRS_DUMMY_INT(651)
BRS_DUMMY_INT(652)
BRS_DUMMY_INT(653)
BRS_DUMMY_INT(654)
BRS_DUMMY_INT(655)
BRS_DUMMY_INT(656)
BRS_DUMMY_INT(657)
BRS_DUMMY_INT(658)
BRS_DUMMY_INT(659)
BRS_DUMMY_INT(660)
BRS_DUMMY_INT(661)
BRS_DUMMY_INT(662)
BRS_DUMMY_INT(663)
BRS_DUMMY_INT(664)
BRS_DUMMY_INT(665)
BRS_DUMMY_INT(666)
BRS_DUMMY_INT(667)
BRS_DUMMY_INT(668)
BRS_DUMMY_INT(669)
BRS_DUMMY_INT(670)
BRS_DUMMY_INT(671)
BRS_DUMMY_INT(672)
BRS_DUMMY_INT(673)
BRS_DUMMY_INT(674)
BRS_DUMMY_INT(675)
BRS_DUMMY_INT(676)
BRS_DUMMY_INT(677)
BRS_DUMMY_INT(678)
BRS_DUMMY_INT(679)
BRS_DUMMY_INT(680)
BRS_DUMMY_INT(681)
BRS_DUMMY_INT(682)
BRS_DUMMY_INT(683)
BRS_DUMMY_INT(684)
BRS_DUMMY_INT(685)
BRS_DUMMY_INT(686)
BRS_DUMMY_INT(687)
BRS_DUMMY_INT(688)
BRS_DUMMY_INT(689)
BRS_DUMMY_INT(690)
BRS_DUMMY_INT(691)
BRS_DUMMY_INT(692)
BRS_DUMMY_INT(693)
BRS_DUMMY_INT(694)
BRS_DUMMY_INT(695)
BRS_DUMMY_INT(696)
BRS_DUMMY_INT(697)
BRS_DUMMY_INT(698)
BRS_DUMMY_INT(699)
BRS_DUMMY_INT(700)
BRS_DUMMY_INT(701)
BRS_DUMMY_INT(702)
BRS_DUMMY_INT(703)
BRS_DUMMY_INT(704)
BRS_DUMMY_INT(705)
BRS_DUMMY_INT(706)
BRS_DUMMY_INT(707)
BRS_DUMMY_INT(708)
BRS_DUMMY_INT(709)
BRS_DUMMY_INT(710)
BRS_DUMMY_INT(711)
BRS_DUMMY_INT(712)
BRS_DUMMY_INT(713)
BRS_DUMMY_INT(714)
BRS_DUMMY_INT(715)
BRS_DUMMY_INT(716)
BRS_DUMMY_INT(717)
BRS_DUMMY_INT(718)
BRS_DUMMY_INT(719)
BRS_DUMMY_INT(720)
BRS_DUMMY_INT(721)
BRS_DUMMY_INT(722)
BRS_DUMMY_INT(723)
BRS_DUMMY_INT(724)
BRS_DUMMY_INT(725)
BRS_DUMMY_INT(726)
BRS_DUMMY_INT(727)
BRS_DUMMY_INT(728)
BRS_DUMMY_INT(729)
BRS_DUMMY_INT(730)
BRS_DUMMY_INT(731)
BRS_DUMMY_INT(732)
BRS_DUMMY_INT(733)
BRS_DUMMY_INT(734)
BRS_DUMMY_INT(735)
BRS_DUMMY_INT(736)
BRS_DUMMY_INT(737)
BRS_DUMMY_INT(738)
BRS_DUMMY_INT(739)
BRS_DUMMY_INT(740)
BRS_DUMMY_INT(741)
BRS_DUMMY_INT(742)
BRS_DUMMY_INT(743)
BRS_DUMMY_INT(744)
BRS_DUMMY_INT(745)
BRS_DUMMY_INT(746)
BRS_DUMMY_INT(747)
BRS_DUMMY_INT(748)
BRS_DUMMY_INT(749)
BRS_DUMMY_INT(750)
BRS_DUMMY_INT(751)
BRS_DUMMY_INT(752)
BRS_DUMMY_INT(753)
BRS_DUMMY_INT(754)
BRS_DUMMY_INT(755)
BRS_DUMMY_INT(756)
BRS_DUMMY_INT(757)
BRS_DUMMY_INT(758)
BRS_DUMMY_INT(759)
BRS_DUMMY_INT(760)
BRS_DUMMY_INT(761)
BRS_DUMMY_INT(762)
BRS_DUMMY_INT(763)
BRS_DUMMY_INT(764)
BRS_DUMMY_INT(765)
BRS_DUMMY_INT(766)
BRS_DUMMY_INT(767)
BRS_DUMMY_INT(768)
BRS_DUMMY_INT(769)
BRS_DUMMY_INT(770)
BRS_DUMMY_INT(771)
BRS_DUMMY_INT(772)
BRS_DUMMY_INT(773)
BRS_DUMMY_INT(774)
BRS_DUMMY_INT(775)
BRS_DUMMY_INT(776)
BRS_DUMMY_INT(777)
BRS_DUMMY_INT(778)
BRS_DUMMY_INT(779)
BRS_DUMMY_INT(780)
BRS_DUMMY_INT(781)
BRS_DUMMY_INT(782)
BRS_DUMMY_INT(783)
BRS_DUMMY_INT(784)
BRS_DUMMY_INT(785)
BRS_DUMMY_INT(786)
BRS_DUMMY_INT(787)
BRS_DUMMY_INT(788)
BRS_DUMMY_INT(789)
BRS_DUMMY_INT(790)
BRS_DUMMY_INT(791)
BRS_DUMMY_INT(792)
BRS_DUMMY_INT(793)
BRS_DUMMY_INT(794)
BRS_DUMMY_INT(795)
BRS_DUMMY_INT(796)
BRS_DUMMY_INT(797)
BRS_DUMMY_INT(798)
BRS_DUMMY_INT(799)
BRS_DUMMY_INT(800)
BRS_DUMMY_INT(801)
BRS_DUMMY_INT(802)
BRS_DUMMY_INT(803)
BRS_DUMMY_INT(804)
BRS_DUMMY_INT(805)
BRS_DUMMY_INT(806)
BRS_DUMMY_INT(807)
BRS_DUMMY_INT(808)
BRS_DUMMY_INT(809)
BRS_DUMMY_INT(810)
BRS_DUMMY_INT(811)
BRS_DUMMY_INT(812)
BRS_DUMMY_INT(813)
BRS_DUMMY_INT(814)
BRS_DUMMY_INT(815)
BRS_DUMMY_INT(816)
BRS_DUMMY_INT(817)
BRS_DUMMY_INT(818)
BRS_DUMMY_INT(819)
BRS_DUMMY_INT(820)
BRS_DUMMY_INT(821)
BRS_DUMMY_INT(822)
BRS_DUMMY_INT(823)
BRS_DUMMY_INT(824)
BRS_DUMMY_INT(825)
BRS_DUMMY_INT(826)
BRS_DUMMY_INT(827)
BRS_DUMMY_INT(828)
BRS_DUMMY_INT(829)
BRS_DUMMY_INT(830)
BRS_DUMMY_INT(831)
BRS_DUMMY_INT(832)
BRS_DUMMY_INT(833)
BRS_DUMMY_INT(834)
BRS_DUMMY_INT(835)
BRS_DUMMY_INT(836)
BRS_DUMMY_INT(837)
BRS_DUMMY_INT(838)
BRS_DUMMY_INT(839)
BRS_DUMMY_INT(840)
BRS_DUMMY_INT(841)
BRS_DUMMY_INT(842)
BRS_DUMMY_INT(843)
BRS_DUMMY_INT(844)
BRS_DUMMY_INT(845)
BRS_DUMMY_INT(846)
BRS_DUMMY_INT(847)
BRS_DUMMY_INT(848)
BRS_DUMMY_INT(849)
BRS_DUMMY_INT(850)
BRS_DUMMY_INT(851)
BRS_DUMMY_INT(852)
BRS_DUMMY_INT(853)
BRS_DUMMY_INT(854)
BRS_DUMMY_INT(855)
BRS_DUMMY_INT(856)
BRS_DUMMY_INT(857)
BRS_DUMMY_INT(858)
BRS_DUMMY_INT(859)
BRS_DUMMY_INT(860)
BRS_DUMMY_INT(861)
BRS_DUMMY_INT(862)
BRS_DUMMY_INT(863)
BRS_DUMMY_INT(864)
BRS_DUMMY_INT(865)
BRS_DUMMY_INT(866)
BRS_DUMMY_INT(867)
BRS_DUMMY_INT(868)
BRS_DUMMY_INT(869)
BRS_DUMMY_INT(870)
BRS_DUMMY_INT(871)
BRS_DUMMY_INT(872)
BRS_DUMMY_INT(873)
BRS_DUMMY_INT(874)
BRS_DUMMY_INT(875)
BRS_DUMMY_INT(876)
BRS_DUMMY_INT(877)
BRS_DUMMY_INT(878)
BRS_DUMMY_INT(879)
BRS_DUMMY_INT(880)
BRS_DUMMY_INT(881)
BRS_DUMMY_INT(882)
BRS_DUMMY_INT(883)
BRS_DUMMY_INT(884)
BRS_DUMMY_INT(885)
BRS_DUMMY_INT(886)
BRS_DUMMY_INT(887)
BRS_DUMMY_INT(888)
BRS_DUMMY_INT(889)
BRS_DUMMY_INT(890)
BRS_DUMMY_INT(891)
BRS_DUMMY_INT(892)
BRS_DUMMY_INT(893)
BRS_DUMMY_INT(894)
BRS_DUMMY_INT(895)
BRS_DUMMY_INT(896)
BRS_DUMMY_INT(897)
BRS_DUMMY_INT(898)
BRS_DUMMY_INT(899)
BRS_DUMMY_INT(900)
BRS_DUMMY_INT(901)
BRS_DUMMY_INT(902)
BRS_DUMMY_INT(903)
BRS_DUMMY_INT(904)
BRS_DUMMY_INT(905)
BRS_DUMMY_INT(906)
BRS_DUMMY_INT(907)
BRS_DUMMY_INT(908)
BRS_DUMMY_INT(909)
BRS_DUMMY_INT(910)
BRS_DUMMY_INT(911)
BRS_DUMMY_INT(912)
BRS_DUMMY_INT(913)
BRS_DUMMY_INT(914)
BRS_DUMMY_INT(915)
BRS_DUMMY_INT(916)
BRS_DUMMY_INT(917)
BRS_DUMMY_INT(918)
BRS_DUMMY_INT(919)
BRS_DUMMY_INT(920)
BRS_DUMMY_INT(921)
BRS_DUMMY_INT(922)
BRS_DUMMY_INT(923)
BRS_DUMMY_INT(924)
BRS_DUMMY_INT(925)
BRS_DUMMY_INT(926)
BRS_DUMMY_INT(927)
BRS_DUMMY_INT(928)
BRS_DUMMY_INT(929)
BRS_DUMMY_INT(930)
BRS_DUMMY_INT(931)
BRS_DUMMY_INT(932)
BRS_DUMMY_INT(933)
BRS_DUMMY_INT(934)
BRS_DUMMY_INT(935)
BRS_DUMMY_INT(936)
BRS_DUMMY_INT(937)
BRS_DUMMY_INT(938)
BRS_DUMMY_INT(939)
BRS_DUMMY_INT(940)
BRS_DUMMY_INT(941)
BRS_DUMMY_INT(942)
BRS_DUMMY_INT(943)
BRS_DUMMY_INT(944)
BRS_DUMMY_INT(945)
BRS_DUMMY_INT(946)
BRS_DUMMY_INT(947)
BRS_DUMMY_INT(948)
BRS_DUMMY_INT(949)
BRS_DUMMY_INT(950)
BRS_DUMMY_INT(951)
BRS_DUMMY_INT(952)
BRS_DUMMY_INT(953)
BRS_DUMMY_INT(954)
BRS_DUMMY_INT(955)
BRS_DUMMY_INT(956)
BRS_DUMMY_INT(957)
BRS_DUMMY_INT(958)
BRS_DUMMY_INT(959)
BRS_DUMMY_INT(960)
BRS_DUMMY_INT(961)
BRS_DUMMY_INT(962)
BRS_DUMMY_INT(963)
BRS_DUMMY_INT(964)
BRS_DUMMY_INT(965)
BRS_DUMMY_INT(966)
BRS_DUMMY_INT(967)
BRS_DUMMY_INT(968)
BRS_DUMMY_INT(969)
BRS_DUMMY_INT(970)
BRS_DUMMY_INT(971)
BRS_DUMMY_INT(972)
BRS_DUMMY_INT(973)
BRS_DUMMY_INT(974)
BRS_DUMMY_INT(975)
BRS_DUMMY_INT(976)
BRS_DUMMY_INT(977)
BRS_DUMMY_INT(978)
BRS_DUMMY_INT(979)
BRS_DUMMY_INT(980)
BRS_DUMMY_INT(981)
BRS_DUMMY_INT(982)
BRS_DUMMY_INT(983)
BRS_DUMMY_INT(984)
BRS_DUMMY_INT(985)
BRS_DUMMY_INT(986)
BRS_DUMMY_INT(987)
BRS_DUMMY_INT(988)
BRS_DUMMY_INT(989)
BRS_DUMMY_INT(990)
BRS_DUMMY_INT(991)
BRS_DUMMY_INT(992)
BRS_DUMMY_INT(993)
BRS_DUMMY_INT(994)
BRS_DUMMY_INT(995)
BRS_DUMMY_INT(996)
BRS_DUMMY_INT(997)
BRS_DUMMY_INT(998)
BRS_DUMMY_INT(999)
BRS_DUMMY_INT(1000)
BRS_DUMMY_INT(1001)
BRS_DUMMY_INT(1002)
BRS_DUMMY_INT(1003)
BRS_DUMMY_INT(1004)
BRS_DUMMY_INT(1005)
BRS_DUMMY_INT(1006)
BRS_DUMMY_INT(1007)
BRS_DUMMY_INT(1008)
BRS_DUMMY_INT(1009)
BRS_DUMMY_INT(1010)
BRS_DUMMY_INT(1011)
BRS_DUMMY_INT(1012)
BRS_DUMMY_INT(1013)
BRS_DUMMY_INT(1014)
BRS_DUMMY_INT(1015)
BRS_DUMMY_INT(1016)
BRS_DUMMY_INT(1017)
BRS_DUMMY_INT(1018)
BRS_DUMMY_INT(1019)
BRS_DUMMY_INT(1020)
BRS_DUMMY_INT(1021)
BRS_DUMMY_INT(1022)
BRS_DUMMY_INT(1023)

#endif /*BRS_OS_USECASE_BRS&&!BRS_ENABLE_FBL_SUPPORT*/

/*****************************************************************************/
/**
 * @brief      Initialize run mode for CPU and peripheral
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    at the end of BrsHwPllInitPowerOn()
 */
/*****************************************************************************/
void BrsHwSwitchRunMode(void)
{
#if defined (BRSHW_OPMODES_GROUP_A) || defined (BRSHW_OPMODES_GROUP_B)
# if defined (BRS_DERIVATIVE_PC580000x) || defined (BRS_DERIVATIVE_PC580002x)|| defined (BRS_DERIVATIVE_PC580003x) || defined (BRS_DERIVATIVE_PC582101)
  ME_RUN_PC(0) = (uint32)0x0000001C;    /* allow all modes to use run peripheral configuration 0 */
# else
  ME_ME = (uint32)0x000005FF;           /* allow usage of all modes */
  ME_RUN_PC(0) = (uint32)0x000000FE;    /* allow all modes to use run peripheral configuration 0 */
  ME_LP_PC(0) = (uint32)0x00000500;     /* allow usage of peripherals in halt and stop mode */
# endif

  ME_RUN_MC(0) |= (uint32)(0x00000020); /* enable XOSC */
# if defined (BRSHW_FMPLL_GROUP_A)
  ME_RUN_MC(0) |= (uint32)(0x00000040); /* enable PLL0 */
  ME_RUN_MC(0) |= (uint32)(0x00000002); /* select system clock = PLL0 clock */
#  if defined (BRS_DERIVATIVE_MPC5775N) || defined (BRS_DERIVATIVE_MPC5773N) || defined (BRS_DERIVATIVE_SPC574Kxx)
  ME_CCTL(1) |= (uint16)0x0010; /* enable z4a clock during RUN0. !IMPORTANT! Do not even think about removing this line!!! */
#  elif defined (BRS_DERIVATIVE_S32R274)
  ME_CCTL(1) |= (uint16)0x0010; /* enable z4a clock during RUN0 */
#  if defined (BRSASR_ENABLE_OS_MULTICORESUPPORT)
  ME_CCTL(2) |= (uint16)0x0010; /* enable z7a clock during RUN0 */
  ME_CCTL(3) |= (uint16)0x0010; /* enable z7b clock during RUN0 */
#  endif
#  elif defined (BRS_DERIVATIVE_SPC574Sx)
  ME_CCTL(0) |= (uint16)0x0010;
#  endif
# elif defined (BRSHW_FMPLL_GROUP_B)
  ME_RUN_MC(0) |= (uint32)(0x00000080); /* enable IRC */
  ME_RUN_MC(0) |= (uint32)(0x00000040); /* enable PLL0 */
  ME_RUN_MC(0) |= (uint32)(0x00000002); /* select system clock = PLL0 clock */
# else
  #error "Your PLL is currently not supported in combination with BRSHW_OPMODES_GROUP_A/B!"
# endif
  
  /* There is no need to switch on any peripherals, because they are assigned to run peripheral configuration 0 by default! */
# if defined (BRS_DERIVATIVE_SPC574Kxx)
  /* Derivate SPC574kxx: Because of unknown reason, the value of this register is set to 2 which is unexpected! */
  /* This register should have value 0 since mode RUN0 is applied */
  ME_PCTL(15) = 0x00;
# endif
  if((ME_GS & (uint32)0xf0000000) == (uint32)0x20000000)
  {
    /* ATTENTION: If you reach this point, your ECU will never switch to the mode Run1! 
      To resolve this issue, a reset will be performed automatically. */
    ME_MCTL = (uint32)0x00005AF0; /* mode transition request to Reset */
    ME_MCTL = (uint32)0x0000A50F; /* mode transition request to Reset */
    while((ME_GS & (uint32)0x08000000) == (uint32)0x08000000)
    {
      ; /* wait for mode transition has completed */
    }
  }
  ME_MCTL = (uint32)0x40005AF0; /* mode transition request to run mode 0 */
  ME_MCTL = (uint32)0x4000A50F; /* mode transition request to run mode 0 */
  while((ME_GS & (uint32)0x08000000) == (uint32)0x08000000)
  {
    ; /* wait for mode transition has completed */
  }
# if !defined (BRS_DERIVATIVE_PC580000x) && !defined (BRS_DERIVATIVE_PC580002x) && !defined (BRS_DERIVATIVE_PC580003x) && !defined (BRS_DERIVATIVE_PC582101)
  while((ME_GS & (uint32)0x00000020) != (uint32)0x00000020)
  {
    ; /* wait for XOSC on */
  }
# endif
  while((ME_GS & (uint32)0x00000040) != (uint32)0x00000040)
  {
    ; /* wait for PLL0 on */
  }
  ME_IS = (uint32)0x3F;
#endif /*BRSHW_OPMODES_GROUP_A || BRSHW_OPMODES_GROUP_B*/
}

#if defined (BRSHW_ENABLE_INIT_RAM)
/*****************************************************************************/
/**
 * @brief      Copys data for initialized variables from ROM to RAM
 * @pre        Functions (and ISRs) that might require initialized global variables
 *             must not be executed before this function is done.
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Called by main() before any other initialization
 */
/*****************************************************************************/
void BrsHwInitRam(void)
{
  uint8 section_copy_counter;

# if defined (BRS_COMP_GHS)
  #define BRSHW_INIT_RAM_SECTION_COPY_COUNT 2
  #define BRSHW_INIT_RAM_COPY_MODE_DIRECT

  /*external definition of sections. will be resolved by the linker*/
  extern char __ghsbegin_romdata[], __ghsend_romdata[],__ghsbegin_data[], __ghsbegin_romsdata[], __ghsend_romsdata[],__ghsbegin_sdata[];
  char * p_start_src;
  char * p_start_dest;
  char * p_end_src;
  char * p_start_src_list[BRSHW_INIT_RAM_SECTION_COPY_COUNT];
  char * p_start_dest_list[BRSHW_INIT_RAM_SECTION_COPY_COUNT];
  char * p_end_src_list[BRSHW_INIT_RAM_SECTION_COPY_COUNT];

  /*copy romdata section to data section*/
  p_start_src_list[0] = __ghsbegin_romdata;/*pointer to start adress of romdata section*/
  p_end_src_list[0] = __ghsend_romdata;/*pointer to first adress #_behind_# romdata section*/
  p_start_dest_list[0] = __ghsbegin_data;
  /*copy romsdata section to sdata section ("small data", only used when activated via compiler option)*/
  p_start_src_list[1] = __ghsbegin_romsdata;/*pointer to start adress of romsdata section*/
  p_end_src_list[1] = __ghsend_romsdata;/*pointer to first adress #_behind_# romsdata section*/
  p_start_dest_list[1] = __ghsbegin_sdata;
# endif /*BRS_COMP_GHS*/



/* do the actual copying */
  for( section_copy_counter = 0; section_copy_counter < BRSHW_INIT_RAM_SECTION_COPY_COUNT; section_copy_counter++ )
  {
    p_start_src=p_start_src_list[section_copy_counter];
    p_start_dest=p_start_dest_list[section_copy_counter];
# if defined (BRSHW_INIT_RAM_COPY_MODE_DIRECT)
    p_end_src=p_end_src_list[section_copy_counter];
    while( p_start_src < p_end_src )
    {
      p_start_dest[0] = p_start_src[0];
      p_start_src++;
      p_start_dest++;
    }
# elif defined (BRSHW_INIT_RAM_COPY_MODE_INDEXED)
    copy_section_index=0;
    copy_section_size=copy_section_size_list[section_copy_counter];
    while( copy_section_index < copy_section_size )
    {
      p_start_dest[copy_section_index] = p_start_src[copy_section_index];
      copy_section_index++;
    }
# else
  #error "No copy mode selected."
# endif /*BRSHW_INIT_RAM_COPY_MODE_x*/
  }
}
#endif /*BRSHW_ENABLE_INIT_RAM*/
