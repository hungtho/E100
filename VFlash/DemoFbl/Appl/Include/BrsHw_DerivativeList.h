
/**********************************************************************************************************************
  COPYRIGHT
-----------------------------------------------------------------------------------------------------------------------
  \par      copyright
  \verbatim
  Copyright (c) 2017 by Vector Informatik GmbH.                                                  All rights reserved.

                This software is copyright protected and proprietary to Vector Informatik GmbH.
                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
                All other rights remain with Vector Informatik GmbH.
  \endverbatim
-----------------------------------------------------------------------------------------------------------------------
  FILE DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
  \file  File:  BrsHw_DerivativeList.h
      Project:  Vector Basic Runtime System
       Module:  BrsHw for platform Freescale/ST Mpc57xx

  \brief Description:  This header file contains the information for the specific groups of the different derivatives,
                       supported by this Brs implementation.

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
  Steffen Frank                 visfsn        Vector Informatik GmbH
  Nguyen Le                     vislnn        Vector Informatik GmbH
  Michael Tiran                 vismin        Vector Informatik GmbH
  Viet Duc Nguyen               visvnn        Vector Informatik GmbH
  Mohammed Seblani              vissmd        Vector Informatik GmbH
  Roland Reinl                  virrro        Vector Informatik GmbH
  Bjoern Eisenkrammer           visebj        Vector Informatik GmbH
  Wolfgang Lienhart             viswlt        Vector Informatik GmbH
  Ivo Georgiev                  visivg        Vector Informatik GmbH
  Sascha Mauser                 vismaa        Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
 ----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Description
  --------  ----------  ------  ---------------------------------------------------------------------------------------
  01.00.00  2015-05-05  vissns  New creation, based on zBrs_Mpc@root[3.09.04],
                                according to template for BrsHw Codestyle 2.0
            2015-07-09  vishan  Added support for BRS_DERIVATIVE_PC580002x (Quasar2)
                                with second SIU group for BRSHW_SIUL2_B
            2015-07-20  visbwa  Review
  01.00.01  2015-08-05  vistir  Added support for MPC5745B and MPC5746B
  01.00.02  2015-08-12  vistir  Added support for MPC5746R
  01.00.03  2015-09-29  visfsn  Added BRSHW_USERMODE_ACCESS_GROUP_B for MPC5746B
  01.00.04  2015-12-09  vislnn  Added support for SPC574Sx and SPC574Kxx, introduced TTCAN for INTERRUPT_TABLE_GROUP_C
  01.00.05  2015-12-09  vismin  Added support for S32R274
  01.00.06  2015-12-23  visvnn  Finalized support for SPC574K
  01.00.07  2016-03-22  vismin  Added support for PC580000/Quasar0
  01.00.08  2016-04-26  vissmd  Introduced BRSHW_USERMODE_ACCESS_GROUP_C for MPC5775K, MPC5773N and MPC5775N
  01.00.09  2016-07-01  visbwa  Added additional headline to fit with Brs_Template 2.00.02
  01.00.10  2016-07-04  virrro  Added BRSHW_USERMODE_ACCESS_GROUP_A1 to S32R
  01.00.11  2016-07-28  visebj  Introduced BRSHW_RCHW_GROUP_A and _B
  01.00.12  2016-07-21  viswlt  Added support for PC582101 (Quasar2e)
  01.00.13  2017-06-16  visivg  Fixed support for SPC574Sx
  01.00.14  2017-06-28  visivg  Fixed SIU Group of PC580000x
  01.00.15  2017-06-28  vismaa  Added MPC5745R
  01.00.16  2017-09-14  virrro  Added BRSHW_USERMODE_ACCESS_GROUP_D to MPC5746R
  01.00.17  2017-10-27  vismaa  Added support for MPC5771N
  01.00.18  2017-11-14  vismaa  introduced BRSHW_USED_CANCELL_DEFAULT for the use of 2 CAN cells
  01.00.19  2017-11-21  vismaa  Added error directive to derivatives with several CAN cells (configurable)
  01.00.20  2018-11-16  vismaa  Added CUT info for MPC5748G
**********************************************************************************************************************/

#ifndef _BRSHW_DERIVATIVELIST_H_
#define _BRSHW_DERIVATIVELIST_H_

/****************************************************
  SUPPORTED DERIVATIVES
*****************************************************/
#if defined (BRS_DERIVATIVE_MPC5744P)
  #define BRSHW_USED_CANCELL_DEFAULT /*FlexCan only*/
  #define BRSHW_CPU_MAX_FREQUENCY   180
  #define BRSHW_CPU_MAX_RAM         384
  #define BRSHW_CPU_MAX_ROM         2048

  #define BRSHW_INTERRUPT_TABLE_GROUP_A
  #define BRSHW_SIU_GROUP_A          0xFFFC0000
  #define BRSHW_FMPLL_GROUP_A        0xFFFB0100
  #define BRSHW_TIMER_GROUP_A        0xFFF84000
  #define BRSHW_WATCHDOG_GROUP_A     0xFC050000
  #define BRSHW_OPMODES_GROUP_A      0xFFFB8000
  #define BRSHW_USERMODE_ACCESS_GROUP_A
  #define BRSHW_LED_PORT_NUMBER      0

#elif defined (BRS_DERIVATIVE_MPC5745B)
  #define BRSHW_USED_CANCELL_DEFAULT /*FlexCan only*/
  #define BRSHW_CPU_MAX_FREQUENCY   160
  #define BRSHW_CPU_MAX_RAM         256
  #define BRSHW_CPU_MAX_ROM         2048

  #define BRSHW_INTERRUPT_TABLE_GROUP_E  0xFC040000
  #define BRSHW_SIU_GROUP_E              0xFFFC0000
  #define BRSHW_FMPLL_GROUP_B            0xFFFB0080
  #define BRSHW_TIMER_GROUP_A            0xFFF84000
  #define BRSHW_WATCHDOG_GROUP_A         0xFC050000
  #define BRSHW_OPMODES_GROUP_A          0xFFFB8000
  #define BRSHW_LED_PORT_NUMBER          98

#elif defined (BRS_DERIVATIVE_MPC5745R)
  #define BRSHW_USED_CANCELL_DEFAULT /*FlexCan only*/
  #define BRSHW_CPU_MAX_FREQUENCY   150
  #define BRSHW_CPU_MAX_RAM         192
  #define BRSHW_CPU_MAX_ROM         3248

  #define BRSHW_RCHW_GROUP_A
  #define BRSHW_INTERRUPT_TABLE_GROUP_G  0xFC040000
  #define BRSHW_SIU_GROUP_G              0xFFFC0000
  #define BRSHW_FMPLL_GROUP_A_1          0xFFFB0100
  #define BRSHW_TIMER_GROUP_A            0xFFF84000
  #define BRSHW_WATCHDOG_GROUP_B         0xFC050000
  #define BRSHW_OPMODES_GROUP_A          0xFFFB8000
  #define BRSHW_LED_PORT_NUMBER          0
  
#elif defined (BRS_DERIVATIVE_MPC5746B)
  #define BRSHW_USED_CANCELL_DEFAULT /*FlexCan only*/
  #define BRSHW_CPU_MAX_FREQUENCY   160
  #define BRSHW_CPU_MAX_RAM         384
  #define BRSHW_CPU_MAX_ROM         3072

  #define BRSHW_RCHW_GROUP_A
  #define BRSHW_INTERRUPT_TABLE_GROUP_E  0xFC040000
  #define BRSHW_SIU_GROUP_E              0xFFFC0000
  #define BRSHW_FMPLL_GROUP_B            0xFFFB0080
  #define BRSHW_TIMER_GROUP_A            0xFFF84000
  #define BRSHW_WATCHDOG_GROUP_A         0xFC050000
  #define BRSHW_OPMODES_GROUP_A          0xFFFB8000
  #define BRSHW_LED_PORT_NUMBER          98
  #define BRSHW_USERMODE_ACCESS_GROUP_B

#elif defined (BRS_DERIVATIVE_MPC5746C)
  #define BRSHW_USED_CANCELL_DEFAULT /*FlexCan only*/
  #define BRSHW_CPU_MAX_FREQUENCY   160
  #define BRSHW_CPU_MAX_RAM         384
  #define BRSHW_CPU_MAX_ROM         3072

  #define BRSHW_RCHW_GROUP_A
  #define BRSHW_INTERRUPT_TABLE_GROUP_E  0xFC040000
  #define BRSHW_SIU_GROUP_E              0xFFFC0000
  #define BRSHW_FMPLL_GROUP_B            0xFFFB0080
  #define BRSHW_TIMER_GROUP_A            0xFFF84000
  #define BRSHW_WATCHDOG_GROUP_A         0xFC050000
  #define BRSHW_OPMODES_GROUP_A          0xFFFB8000
  #define BRSHW_LED_PORT_NUMBER          98

#elif defined (BRS_DERIVATIVE_MPC5746M)
  #define BRSHW_USED_CANCELL_DEFAULT /*TTCAN/MCAN only */
  #define BRSHW_CPU_MAX_FREQUENCY   200
  #define BRSHW_CPU_MAX_RAM         64
  #define BRSHW_CPU_MAX_ROM         3584

  #define BRSHW_RCHW_GROUP_A
  #define BRSHW_INTERRUPT_TABLE_GROUP_C TTCAN
  #define BRSHW_SIU_GROUP_C          0xFFFC0000
  #define BRSHW_FMPLL_GROUP_A_1      0xFFFB0100
  #define BRSHW_TIMER_GROUP_A        0xFFF84000
  #define BRSHW_WATCHDOG_GROUP_A     0xFC050000
  #define BRSHW_OPMODES_GROUP_A      0xFFFB8000
  #define BRSHW_LED_PORT_NUMBER      0
  #define BRSHW_ENABLE_ISR_SW_DISPATCHING

#elif defined (BRS_DERIVATIVE_MPC5746R)
  #define BRSHW_USED_CANCELL_DEFAULT /*FlexCan only*/
  #define BRSHW_CPU_MAX_FREQUENCY   200
  #define BRSHW_CPU_MAX_RAM         256
  #define BRSHW_CPU_MAX_ROM         4272

  #define BRSHW_RCHW_GROUP_A
  #define BRSHW_INTERRUPT_TABLE_GROUP_G  0xFC040000
  #define BRSHW_SIU_GROUP_G              0xFFFC0000
  #define BRSHW_FMPLL_GROUP_A_1          0xFFFB0100
  #define BRSHW_TIMER_GROUP_A            0xFFF84000
  #define BRSHW_WATCHDOG_GROUP_B         0xFC050000
  #define BRSHW_OPMODES_GROUP_A          0xFFFB8000
  #define BRSHW_LED_PORT_NUMBER          0
  #define BRSHW_USERMODE_ACCESS_GROUP_D

#elif defined (BRS_DERIVATIVE_MPC5747C)
  #define BRSHW_USED_CANCELL_DEFAULT /*FlexCan only*/
  /* Attention: The MPC5747C is the same as MPC5748G Cut2! */
  #define MPC5748G_CUT              2
  #define BRSHW_CPU_MAX_FREQUENCY   160
  #define BRSHW_CPU_MAX_RAM         768
  #define BRSHW_CPU_MAX_ROM         5632

  #define BRSHW_RCHW_GROUP_A
  #define BRSHW_INTERRUPT_TABLE_GROUP_E  0xFC040000
  #define BRSHW_SIU_GROUP_E              0xFFFC0000
  #define BRSHW_FMPLL_GROUP_B            0xFFFB0080
  #define BRSHW_TIMER_GROUP_A            0xFFF84000
  #define BRSHW_WATCHDOG_GROUP_A         0xFC050000
  #define BRSHW_OPMODES_GROUP_A          0xFFFB8000
  #define BRSHW_LED_PORT_NUMBER          98
  /*#define C_CAN_MAX_BUFFER_96        no Cut2 DrvCan with 96 mailboxes available, if available, choose 96*/

#elif defined (BRS_DERIVATIVE_MPC5748G)
  #define BRSHW_USED_CANCELL_DEFAULT /*FlexCan only*/

/* Attention: The PLL of the MPC5748G Cut2 is different from Cut1 and differs by factor 1.28 from the manual!
 *            --> MPC5748G Datasheet Rev. 3
 *            The clocksource register address of the PLL, Pin function of mscr94, PCR setting for output pins and
 *            some Interrupts are different.
 */
  #error "There are differences in the Interrupt and PLL configuration between Cut1 and Cut2 of the MPC5748G. Define the used Cut here"*/
  /*CUT info                                               */
  /*CUT1 Mask ID = 0N65H                                   */
  /*CUT2 Mask ID = 1N81M                                   */
  /*CUT3 Mask ID = 0N78S could be used with MPC5748G_CUT 2 */
  
  #define MPC5748G_CUT              2

  #define BRSHW_CPU_MAX_FREQUENCY   160
  #define BRSHW_CPU_MAX_RAM         768
  #define BRSHW_CPU_MAX_ROM         5632

  #define BRSHW_RCHW_GROUP_A
  #define BRSHW_INTERRUPT_TABLE_GROUP_E  0xFC040000
  #define BRSHW_SIU_GROUP_E              0xFFFC0000
  #define BRSHW_FMPLL_GROUP_B            0xFFFB0080
  #define BRSHW_TIMER_GROUP_A            0xFFF84000
  #define BRSHW_WATCHDOG_GROUP_A         0xFC050000
  #define BRSHW_OPMODES_GROUP_A          0xFFFB8000
  # if defined (BRS_EVA_BOARD_DEFAULT)
  #define BRSHW_LED_PORT_NUMBER          98
  #endif
  /*#define C_CAN_MAX_BUFFER_96        no Cut2 DrvCan with 96 mailboxes available, if available, choose 96*/

#elif defined (BRS_DERIVATIVE_MPC5775K)
/* Attention: This derivative has two different types of CAN cells!
 *            Please configure here, which CAN cell should be used within your project.
 *            Also the usage of both CAN cells in parallel could be possible!
 *            Uncomment the define of the CAN cell not to be used.
 */
  #error "The configured derivative supports two different CANcells. Please configure here, which cell should be used."*/
  #define BRSHW_USED_CANCELL_DEFAULT /*FlexCan(default)*/
  /*#define BRSHW_USED_CANCELL_MCAN*/   /*Additional MCAN cell*/
  
  #define BRSHW_CPU_MAX_FREQUENCY   266
  #define BRSHW_CPU_MAX_RAM         1536
  #define BRSHW_CPU_MAX_ROM         4096

  #define BRSHW_INTERRUPT_TABLE_GROUP_A
  #define BRSHW_SIU_GROUP_A          0xFFFC0000
  #define BRSHW_FMPLL_GROUP_A        0xFFFB0100
  #define BRSHW_TIMER_GROUP_A        0xFFF84000
  #define BRSHW_WATCHDOG_GROUP_A     0xFC050000
  #define BRSHW_OPMODES_GROUP_A      0xFFFB8000
  #define BRSHW_LED_PORT_NUMBER      92
  #define BRSHW_USERMODE_ACCESS_GROUP_C

#elif defined (BRS_DERIVATIVE_MPC5771N)
  #define BRSHW_USED_CANCELL_DEFAULT /*FlexCan only*/
  #define BRSHW_CPU_MAX_FREQUENCY   266
  #define BRSHW_CPU_MAX_RAM         800
  #define BRSHW_CPU_MAX_ROM         1280

  #define BRSHW_INTERRUPT_TABLE_GROUP_A
  #define BRSHW_SIU_GROUP_A          0xFFFC0000
  #define BRSHW_FMPLL_GROUP_A        0xFFFB0100
  #define BRSHW_TIMER_GROUP_A        0xFFF84000
  #define BRSHW_WATCHDOG_GROUP_A     0xFC050000
  #define BRSHW_OPMODES_GROUP_A      0xFFFB8000
  #define BRSHW_LED_PORT_NUMBER      92
  #define BRSHW_USERMODE_ACCESS_GROUP_C

#elif defined (BRS_DERIVATIVE_MPC5773N)
  #define BRSHW_USED_CANCELL_DEFAULT /*FlexCan only*/
  #define BRSHW_CPU_MAX_FREQUENCY   266
  #define BRSHW_CPU_MAX_RAM         1280
  #define BRSHW_CPU_MAX_ROM         2048

  #define BRSHW_INTERRUPT_TABLE_GROUP_A
  #define BRSHW_SIU_GROUP_A          0xFFFC0000
  #define BRSHW_FMPLL_GROUP_A        0xFFFB0100
  #define BRSHW_TIMER_GROUP_A        0xFFF84000
  #define BRSHW_WATCHDOG_GROUP_A     0xFC050000
  #define BRSHW_OPMODES_GROUP_A      0xFFFB8000
  #define BRSHW_LED_PORT_NUMBER      92
  #define BRSHW_USERMODE_ACCESS_GROUP_C

#elif defined (BRS_DERIVATIVE_MPC5775N)
  #define BRSHW_USED_CANCELL_DEFAULT /*FlexCan only*/
  #define BRSHW_CPU_MAX_FREQUENCY   266
  #define BRSHW_CPU_MAX_RAM         1536
  #define BRSHW_CPU_MAX_ROM         3584

  #define BRSHW_INTERRUPT_TABLE_GROUP_A
  #define BRSHW_SIU_GROUP_A          0xFFFC0000
  #define BRSHW_FMPLL_GROUP_A        0xFFFB0100
  #define BRSHW_TIMER_GROUP_A        0xFFF84000
  #define BRSHW_WATCHDOG_GROUP_A     0xFC050000
  #define BRSHW_OPMODES_GROUP_A      0xFFFB8000
  #define BRSHW_LED_PORT_NUMBER      92
  #define BRSHW_USERMODE_ACCESS_GROUP_C

#elif defined (BRS_DERIVATIVE_MPC5777M)
  #define BRSHW_USED_CANCELL_DEFAULT    /*TTCAN Revison2.0 (default), MCAN Revision3.0*/

  #define BRSHW_CPU_MAX_FREQUENCY   300
  #define BRSHW_CPU_MAX_RAM         384
  #define BRSHW_CPU_MAX_ROM         7680

  #define BRSHW_RCHW_GROUP_A
  #define BRSHW_INTERRUPT_TABLE_GROUP_C TTCAN
  #define BRSHW_SIU_GROUP_C          0xFFFC0000
  #define BRSHW_FMPLL_GROUP_A_1      0xFFFB0100
  #define BRSHW_TIMER_GROUP_A        0xFFF84000
  #define BRSHW_WATCHDOG_GROUP_A     0xFC050000
  #define BRSHW_OPMODES_GROUP_A      0xFFFB8000
  #define BRSHW_LED_PORT_NUMBER      0
  #define BRSHW_ENABLE_ISR_SW_DISPATCHING

#elif defined (BRS_DERIVATIVE_MPC5777C)
/* Attention: This derivative has two different types of CAN cells!
 *            Please configure here, which CAN cell should be used within your project.
 *            Also the usage of both CAN cells in parallel could be possible!
 *            Uncomment the define of the CAN cell not to be used.
 */
  #error "The configured derivative supports two different CANcells. Please configure here, which cell should be used."*/
  #define BRSHW_USED_CANCELL_DEFAULT /*FlexCan(default)*/
  /*#define BRSHW_USED_CANCELL_MCAN*/   /*Additional MCAN cell*/

  #define BRSHW_CPU_MAX_FREQUENCY   264
  #define BRSHW_CPU_MAX_RAM         512
  #define BRSHW_CPU_MAX_ROM         8192

  #define BRSHW_INTERRUPT_TABLE_GROUP_B
  #define BRSHW_SIU_GROUP_B          0xC3F90000UL
  #define BRSHW_FMPLL_GROUP_A        0xFFE74000UL
  #define BRSHW_TIMER_GROUP_A        0xC3FF0000UL
  #define BRSHW_WATCHDOG_GROUP_A     0xFFF38000UL
  #define BRSHW_OPMODES_GROUP_NONE
  #define BRSHW_LED_PORT_NUMBER      114

#elif defined (BRS_DERIVATIVE_SPC570S50)
  #define BRSHW_USED_CANCELL_DEFAULT /*FlexCan only*/
  #define BRSHW_CPU_MAX_FREQUENCY   80
  #define BRSHW_CPU_MAX_RAM         48
  #define BRSHW_CPU_MAX_ROM         512

  #define BRSHW_RCHW_GROUP_B
  #define BRSHW_INTERRUPT_TABLE_GROUP_F
  #define BRSHW_SIU_GROUP_F         0xFFFC0000
  #define BRSHW_FMPLL_GROUP_A_3     0xFFFB0100
  #define BRSHW_TIMER_GROUP_A       0xFFF84000
  #define BRSHW_WATCHDOG_GROUP_A    0xFC058000
  #define BRSHW_OPMODES_GROUP_A     0xFFFB8000
  #define BRSHW_LED_PORT_NUMBER     8
  #define BRSHW_ENABLE_ISR_SW_DISPATCHING

#elif defined (BRS_DERIVATIVE_SPC574Kxx)
  #define BRSHW_USED_CANCELL_DEFAULT /*MCAN Revision3.0(default), TTCAN Revison2.0 */
  #define BRSHW_CPU_MAX_FREQUENCY   160
  #define BRSHW_CPU_MAX_RAM         64
  #define BRSHW_CPU_MAX_ROM         2560

  #define BRSHW_RCHW_GROUP_A
  #define BRSHW_INTERRUPT_TABLE_GROUP_C MCAN
  #define BRSHW_SIU_GROUP_H         0xFFFC0000
  #define BRSHW_FMPLL_GROUP_A_3     0xFFFB0100
  #define BRSHW_TIMER_GROUP_A       0xFFF80000
  #define BRSHW_WATCHDOG_GROUP_A    0xFC058000
  #define BRSHW_OPMODES_GROUP_B     0xFFFB8000
  #define BRSHW_LED_PORT_NUMBER     1

#elif defined (BRS_DERIVATIVE_SPC574Sx)
  #define BRSHW_USED_CANCELL_DEFAULT /*MCAN only*/
  #define BRSHW_CPU_MAX_FREQUENCY   140
  #define BRSHW_CPU_MAX_RAM         32
  #define BRSHW_CPU_MAX_ROM         1024

  #define BRSHW_RCHW_GROUP_B
  #define BRSHW_INTERRUPT_TABLE_GROUP_C MCAN
  #define BRSHW_SIU_GROUP_H         0xFFFC0000
  #define BRSHW_FMPLL_GROUP_A_3     0xFFFB0100
  #define BRSHW_TIMER_GROUP_A       0xFFF84000
  #define BRSHW_WATCHDOG_GROUP_A    0xFC058000
  #define BRSHW_OPMODES_GROUP_A     0xFFFB8000
  #define BRSHW_LED_PORT_NUMBER     0

#elif defined (BRS_DERIVATIVE_PC580000x)
  #define BRSHW_USED_CANCELL_DEFAULT /*FlexCan only*/
  #define BRSHW_CPU_MAX_FREQUENCY   160
  #define BRSHW_CPU_MAX_RAM         128
  #define BRSHW_CPU_MAX_ROM         2048

  #define BRSHW_INTERRUPT_TABLE_GROUP_D
  #define BRSHW_SIU_GROUP_D_1       0xFFFA4000 /*SIUL2_A*/
  #define BRSHW_SIU_GROUP_D_2       0xFFFD4000 /*SIUL2_B*/
  #define BRSHW_FMPLL_GROUP_A_2     0xFFFF0100
  #define BRSHW_TIMER_GROUP_B       0xFFFAC000
  #define BRSHW_WATCHDOG_GROUP_NONE
  #define BRSHW_OPMODES_GROUP_A     0xFFFEC000
  #define BRSHW_LED_PORT_NUMBER     0

#elif defined (BRS_DERIVATIVE_PC580002x)
  #define BRSHW_USED_CANCELL_DEFAULT /*FlexCan only*/
  #define BRSHW_CPU_MAX_FREQUENCY   160
  #define BRSHW_CPU_MAX_RAM         256
  #define BRSHW_CPU_MAX_ROM         4096

  #define BRSHW_INTERRUPT_TABLE_GROUP_D
  #define BRSHW_SIU_GROUP_D_1       0xFFFA4000 /*SIUL2_A*/
  #define BRSHW_SIU_GROUP_D_2       0xFFFD4000 /*SIUL2_B*/
  #define BRSHW_FMPLL_GROUP_A_2     0xFFFF0100
  #define BRSHW_TIMER_GROUP_B       0xFFFAC000
  #define BRSHW_WATCHDOG_GROUP_NONE
  #define BRSHW_OPMODES_GROUP_A     0xFFFEC000
  #define BRSHW_LED_PORT_NUMBER     0

#elif defined (BRS_DERIVATIVE_PC582101)
  #define BRSHW_USED_CANCELL_DEFAULT /*FlexCan only*/
  #define BRSHW_CPU_MAX_FREQUENCY   160
  #define BRSHW_CPU_MAX_RAM         256
  #define BRSHW_CPU_MAX_ROM         4096

  #define BRSHW_INTERRUPT_TABLE_GROUP_D
  #define BRSHW_SIU_GROUP_D_1       0xFFFA4000 /*SIUL2_A*/
  #define BRSHW_SIU_GROUP_D_2       0xFFFD4000 /*SIUL2_B*/
  #define BRSHW_FMPLL_GROUP_A_2     0xFFFF0100
  #define BRSHW_TIMER_GROUP_B       0xFFFAC000
  #define BRSHW_WATCHDOG_GROUP_NONE
  #define BRSHW_OPMODES_GROUP_A     0xFFFEC000
  #define BRSHW_LED_PORT_NUMBER     0

#elif defined (BRS_DERIVATIVE_PC580003x)
  #define BRSHW_USED_CANCELL_DEFAULT /*FlexCan only*/
  #define BRSHW_CPU_MAX_FREQUENCY   266
  #define BRSHW_CPU_MAX_RAM         512
  #define BRSHW_CPU_MAX_ROM         8736

  #define BRSHW_INTERRUPT_TABLE_GROUP_D
  #define BRSHW_SIU_GROUP_D_1       0xFFFA4000 /*SIUL2_A*/
  #define BRSHW_SIU_GROUP_D_2       0xFFFD4000 /*SIUL2_B*/
  #define BRSHW_FMPLL_GROUP_A_2     0xFFFF0100
  #define BRSHW_TIMER_GROUP_B       0xFFFAC000
  #define BRSHW_WATCHDOG_GROUP_NONE
  #define BRSHW_OPMODES_GROUP_A     0xFFFEC000
  #define BRSHW_LED_PORT_NUMBER     0

#elif defined (BRS_DERIVATIVE_S32R274)
  #define BRSHW_USED_CANCELL_DEFAULT /*FlexCan only*/
  #define BRSHW_CPU_MAX_FREQUENCY   240
  #define BRSHW_CPU_MAX_RAM         1536
  #define BRSHW_CPU_MAX_ROM         2048

  #define BRSHW_INTERRUPT_TABLE_GROUP_A
  #define BRSHW_SIU_GROUP_A          0xFFFC0000
  #define BRSHW_FMPLL_GROUP_A        0xFFFB0100
  #define BRSHW_TIMER_GROUP_A        0xFFF84000
  #define BRSHW_WATCHDOG_GROUP_A     0xFC050000
  #define BRSHW_OPMODES_GROUP_A      0xFFFB8000
  #define BRSHW_LED_PORT_NUMBER      2
  #define BRSHW_USERMODE_ACCESS_GROUP_A1

#else
  #error "Configured derivative (Makefile.config) not yet supported"
#endif /*BRS_DERIVATIVE_x*/

#endif /*_BRSHW_DERIVATIVELIST_H_*/
