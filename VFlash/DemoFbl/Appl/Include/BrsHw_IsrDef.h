
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
  \file  File:  BrsHw_IsrDef.h
      Project:  Vector Basic Runtime System
       Module:  BrsHw for platform Freescale/ST Mpc57xx

  \brief Description:  This header file contains the abstraction of ISRs to row within Interrupt Vector Table.
                       It should only be included by BrsIntTb.c and BrsHw.c.

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
  Michael Tiran                 vismin        Vector Informatik GmbH
  Viet Duc Nguyen               visvnn        Vector Informatik GmbH
  Ivo Georgiev                  visivg        Vector Informatik GmbH
  Sascha Mauser                 vismaa        Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
 ----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Description
  --------  ----------  ------  ---------------------------------------------------------------------------------------
  01.00.00  2015-05-05  vissns  New creation, based on zBrs_Mpc@root[3.09.04],
                                according to template for BrsHw Codestyle 2.0
            2015-07-09  vishan  Reworked Flexcan single irq mapping for BRSHW_INTERRUPT_TABLE_GROUP_D
            2015-07-20  visbwa  Review
  01.00.01  2015-08-12  vistir  Added support for MPC5746R - BRSHW_INTERRUPT_TABLE_GROUP_G
  01.00.02  2015-09-15  visntr  Added missing compatibility defines for CAN interrupts
  01.00.03  2015-11-19  visbwa  Fixed DrvCan-CBD support (additional wrapper for different define namings)
  01.00.04  2015-12-09  vislnn  Introduced TTCAN for INTERRUPT_TABLE_GROUP_C and MCAN0
  01.00.05  2015-12-09  vismin  Added C_ENABLE_MB64TO95 to Interrupt Group A
  01.00.06  2015-12-23  visvnn  Fixed Timer ISR for SPC574K
  01.00.07  2016-03-23  visbwa  Fixed Can-ISRs for BRSHW_INTERRUPT_TABLE_GROUP_D
  01.00.08  2017-06-20  visivg  Added wrapper for _MCAN0_LINE0_Interrupt
  01.00.09  2017-08-14  visivg  Encapsulated Wakeup-ISR parts with BRS_ENABLE_EXTERNAL_WAKEUPS
  01.00.10  2017-08-28  visivg  Added support for GnuGcc compiler, renamed BRS_COMP_GNU into BRS_COMP_HIGHTEC
  01.00.11  2017-10-27  vismin  Added support for IndividualPolling for BRSHW_INTERRUPT_TABLE_GROUP_D
  01.00.12  2017-11-14  vismaa  Introduced BRSHW_USED_CANCELL_DEFAULT and BRSHW_USED_CANCELL_MCAN for the use of 2 CAN
                                cells in parallel, renamed BRSHW_USED_CANCELL_FLEXCAN to BRSHW_USED_CANCELL_DEFAULT
  01.00.13  2017-11-21  visbwa  Added usage of C_ENABLE_SINGLE_ISR_API for CAN ISRs and BRSHW_INTERRUPT_TABLE_GROUP_D
**********************************************************************************************************************/

#ifndef _BRSHW_ISRDEF_H_
#define _BRSHW_ISRDEF_H_

/* compatibility defines */
#ifdef VGEN_ENABLE_IF_ASRIFCAN
# if (CAN_TX_PROCESSING == CAN_INTERRUPT) || (CAN_RX_PROCESSING == CAN_INTERRUPT)
  #define C_ENABLE_CAN_INTERRUPT
# endif
# if (CAN_BUSOFF_PROCESSING == CAN_POLLING)
  #define C_ENABLE_ERROR_POLLING
# endif
#else
# if defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL)
  #define C_ENABLE_CAN_INTERRUPT
# endif
#endif

#if defined (BRSHW_INTERRUPT_TABLE_GROUP_A)
/*------------------------------------------------------------------------------------|
 |                                                                                    |
 |                          Interrupt Group A                                         |
 |                                                                                    |
 |------------------------------------------------------------------------------------|*/
# if defined(BRS_COMP_GHS) 
  #define INTERRUPT_ALIGNMENT 2
# endif

  /**********************************************************************************
   *                                 FlexCan                                        *
   **********************************************************************************/
# if defined (VGEN_ENABLE_CAN_DRV) 
#  if defined (kCanPhysToLogChannelIndex_0)
#   if defined (C_ENABLE_CAN_BUSOFF_INTERRUPT)
  #define BrsHwDummyInterrupt521 _FlexCANA_ErrorInterrupt
#   endif
#   if defined (C_ENABLE_CAN_RXTX_INTERRUPT)
  #define BrsHwDummyInterrupt522 _FlexCANA_RxFifoInterrupt
  #define BrsHwDummyInterrupt523 _FlexCANA_RxFifoInterrupt
  #define BrsHwDummyInterrupt524 _FlexCANA_MB8To63Interrupt
  #define BrsHwDummyInterrupt525 _FlexCANA_MB8To63Interrupt
  #define BrsHwDummyInterrupt526 _FlexCANA_MB8To63Interrupt
  #define BrsHwDummyInterrupt527 _FlexCANA_MB8To63Interrupt
  #define BrsHwDummyInterrupt528 _FlexCANA_MB8To63Interrupt
  #define BrsHwDummyInterrupt529 _FlexCANA_MB8To63Interrupt
  #define BrsHwDummyInterrupt530 _FlexCANA_MB8To63Interrupt
#    if defined (C_ENABLE_MB64TO95)
   #define BrsHwDummyInterrupt531 _FlexCANA_MB64To95Interrupt
#    endif
#   endif
#  endif /*kCanPhysToLogChannelIndex_0*/
#  if defined (kCanPhysToLogChannelIndex_1)
#   if defined (C_ENABLE_CAN_BUSOFF_INTERRUPT)
  #define BrsHwDummyInterrupt534 _FlexCANB_ErrorInterrupt
#   endif
#   if defined (C_ENABLE_CAN_RXTX_INTERRUPT)
  #define BrsHwDummyInterrupt535 _FlexCANB_RxFifoInterrupt
  #define BrsHwDummyInterrupt536 _FlexCANB_RxFifoInterrupt
  #define BrsHwDummyInterrupt537 _FlexCANB_MB8To63Interrupt
  #define BrsHwDummyInterrupt538 _FlexCANB_MB8To63Interrupt
  #define BrsHwDummyInterrupt539 _FlexCANB_MB8To63Interrupt
  #define BrsHwDummyInterrupt540 _FlexCANB_MB8To63Interrupt
  #define BrsHwDummyInterrupt541 _FlexCANB_MB8To63Interrupt
  #define BrsHwDummyInterrupt542 _FlexCANB_MB8To63Interrupt
  #define BrsHwDummyInterrupt543 _FlexCANB_MB8To63Interrupt
#   endif
#  endif /*kCanPhysToLogChannelIndex_1*/
#  if defined (kCanPhysToLogChannelIndex_2)
#   if defined (C_ENABLE_CAN_BUSOFF_INTERRUPT)
  #define BrsHwDummyInterrupt547 _FlexCANC_ErrorInterrupt
#   endif
#   if defined (C_ENABLE_CAN_RXTX_INTERRUPT)
  #define BrsHwDummyInterrupt548 _FlexCANC_RxFifoInterrupt
  #define BrsHwDummyInterrupt549 _FlexCANC_RxFifoInterrupt
  #define BrsHwDummyInterrupt550 _FlexCANC_MB8To63Interrupt
  #define BrsHwDummyInterrupt551 _FlexCANC_MB8To63Interrupt
  #define BrsHwDummyInterrupt552 _FlexCANC_MB8To63Interrupt
  #define BrsHwDummyInterrupt553 _FlexCANC_MB8To63Interrupt
  #define BrsHwDummyInterrupt554 _FlexCANC_MB8To63Interrupt
  #define BrsHwDummyInterrupt555 _FlexCANC_MB8To63Interrupt
  #define BrsHwDummyInterrupt556 _FlexCANC_MB8To63Interrupt
#    if defined (C_ENABLE_MB64TO95)
   #define BrsHwDummyInterrupt557 _FlexCANA_MB64To95Interrupt
#    endif
#   endif
#  endif /*kCanPhysToLogChannelIndex_2*/

  /**********************************************************************************
   *                                 MCAN                                           *
   **********************************************************************************/
#  if defined (C_ENABLE_CAN_RXTX_INTERRUPT)
#   if defined (BRSHW_USED_CANCELL_MCAN)
#    if defined (kCan_30_McanPhysToLogChannelIndex_0) /* M_CAN_0 */
  #define BrsHwDummyInterrupt557  _MCAN0_Interrupt
#    endif
#    if defined (kCan_30_McanPhysToLogChannelIndex_1) /* M_CAN_1 */
  #define BrsHwDummyInterrupt558  _MCAN1_Interrupt
#    endif
#   endif /*BRSHW_USED_CANCELL_MCAN*/
#  endif /*C_ENABLE_CAN_RXTX_INTERRUPT*/
# endif /*VGEN_ENABLE_CAN_DRV*/

  /**********************************************************************************
   *                                      LIN                                       *
   **********************************************************************************/
# if defined (VGEN_ENABLE_LIN_DRV)
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
  #define BrsHwDummyInterrupt376 _LINFLEX_LinIsr_RXI_0  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt377 _LINFLEX_LinIsr_TXI_0  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt378 _LINFLEX_LinIsr_ERR_0  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
  #define BrsHwDummyInterrupt380 _LINFLEX_LinIsr_RXI_1  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt381 _LINFLEX_LinIsr_TXI_1  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt382 _LINFLEX_LinIsr_ERR_1  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_2)
  #define BrsHwDummyInterrupt384 _LINFLEX_LinIsr_RXI_2  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt385 _LINFLEX_LinIsr_TXI_2  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt386 _LINFLEX_LinIsr_ERR_2  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_3)
  #define BrsHwDummyInterrupt388 _LINFLEX_LinIsr_RXI_3  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt389 _LINFLEX_LinIsr_TXI_3  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt390 _LINFLEX_LinIsr_ERR_3  /* LINFlex_ERR */
#  endif
# endif /*VGEN_ENABLE_LIN_DRV*/

  /**********************************************************************************
   *                           FlexRay                                              *
   **********************************************************************************/
# if defined (VGEN_ENABLE_DRVFR__BASEASR)
  #define BrsHwDummyInterrupt458 _BrsHwFlexRayProtInterrupt  /* Flexray PRIF */ 
# endif

  /**********************************************************************************
   *                                  Timer                                         *
   **********************************************************************************/
  #define BrsHwDummyInterrupt226 _BrsHwTimeBaseInterrupt
#endif /*BRSHW_INTERRUPT_TABLE_GROUP_A*/

#if defined (BRSHW_INTERRUPT_TABLE_GROUP_B)
/*------------------------------------------------------------------------------------|
 |                                                                                    |
 |                          Interrupt Group B                                         |
 |                                                                                    |
 |------------------------------------------------------------------------------------|*/
# if defined(BRS_COMP_GHS) 
  #define INTERRUPT_ALIGNMENT 4
# endif

# if defined (VGEN_ENABLE_CAN_DRV)
#  if defined (BRSHW_USED_CANCELL_DEFAULT)
  /**********************************************************************************
   *                            FlexCAN                                             *
   **********************************************************************************/
#   if defined (kCanPhysToLogChannelIndex_0)
#    if defined (C_ENABLE_CAN_BUSOFF_INTERRUPT)
  #define BrsHwDummyInterrupt152 _FlexCANA_ErrorInterrupt
#    endif
#    if defined (C_ENABLE_CAN_RXTX_INTERRUPT)
  #define BrsHwDummyInterrupt155  _FlexCANA_RxFifoInterrupt
  #define BrsHwDummyInterrupt156  _FlexCANA_RxFifoInterrupt
  #define BrsHwDummyInterrupt157  _FlexCANA_RxFifoInterrupt
  #define BrsHwDummyInterrupt158  _FlexCANA_RxFifoInterrupt
  #define BrsHwDummyInterrupt159  _FlexCANA_RxFifoInterrupt
  #define BrsHwDummyInterrupt160  _FlexCANA_RxFifoInterrupt
  #define BrsHwDummyInterrupt161  _FlexCANA_RxFifoInterrupt
  #define BrsHwDummyInterrupt162  _FlexCANA_RxFifoInterrupt
  #define BrsHwDummyInterrupt163  _FlexCANA_MB8To63Interrupt
  #define BrsHwDummyInterrupt164  _FlexCANA_MB8To63Interrupt
  #define BrsHwDummyInterrupt165  _FlexCANA_MB8To63Interrupt
  #define BrsHwDummyInterrupt166  _FlexCANA_MB8To63Interrupt
  #define BrsHwDummyInterrupt167  _FlexCANA_MB8To63Interrupt
  #define BrsHwDummyInterrupt168  _FlexCANA_MB8To63Interrupt
  #define BrsHwDummyInterrupt169  _FlexCANA_MB8To63Interrupt
  #define BrsHwDummyInterrupt170  _FlexCANA_MB8To63Interrupt
  #define BrsHwDummyInterrupt171  _FlexCANA_MB8To63Interrupt
  #define BrsHwDummyInterrupt172  _FlexCANA_MB8To63Interrupt
#    endif
#   endif /*kCanPhysToLogChannelIndex_0*/
#   if defined (kCanPhysToLogChannelIndex_1)
#    if defined (C_ENABLE_CAN_BUSOFF_INTERRUPT)
  #define BrsHwDummyInterrupt280 _FlexCANB_ErrorInterrupt
#    endif
#    if defined (C_ENABLE_CAN_RXTX_INTERRUPT)
  #define BrsHwDummyInterrupt283  _FlexCANB_RxFifoInterrupt
  #define BrsHwDummyInterrupt284  _FlexCANB_RxFifoInterrupt
  #define BrsHwDummyInterrupt285  _FlexCANB_RxFifoInterrupt
  #define BrsHwDummyInterrupt286  _FlexCANB_RxFifoInterrupt
  #define BrsHwDummyInterrupt287  _FlexCANB_RxFifoInterrupt
  #define BrsHwDummyInterrupt288  _FlexCANB_RxFifoInterrupt
  #define BrsHwDummyInterrupt289  _FlexCANB_RxFifoInterrupt
  #define BrsHwDummyInterrupt290  _FlexCANB_RxFifoInterrupt
  #define BrsHwDummyInterrupt291  _FlexCANB_MB8To63Interrupt
  #define BrsHwDummyInterrupt292  _FlexCANB_MB8To63Interrupt
  #define BrsHwDummyInterrupt293  _FlexCANB_MB8To63Interrupt
  #define BrsHwDummyInterrupt294  _FlexCANB_MB8To63Interrupt
  #define BrsHwDummyInterrupt295  _FlexCANB_MB8To63Interrupt
  #define BrsHwDummyInterrupt296  _FlexCANB_MB8To63Interrupt
  #define BrsHwDummyInterrupt297  _FlexCANB_MB8To63Interrupt
  #define BrsHwDummyInterrupt298  _FlexCANB_MB8To63Interrupt
  #define BrsHwDummyInterrupt299  _FlexCANB_MB8To63Interrupt
  #define BrsHwDummyInterrupt300  _FlexCANB_MB8To63Interrupt
#    endif
#   endif /*kCanPhysToLogChannelIndex_1*/
#   if defined (kCanPhysToLogChannelIndex_2)
#    if defined (C_ENABLE_CAN_BUSOFF_INTERRUPT)
  #define BrsHwDummyInterrupt173 _FlexCANC_ErrorInterrupt
#    endif
#    if defined (C_ENABLE_CAN_RXTX_INTERRUPT)
  #define BrsHwDummyInterrupt176  _FlexCANC_RxFifoInterrupt
  #define BrsHwDummyInterrupt177  _FlexCANC_RxFifoInterrupt
  #define BrsHwDummyInterrupt178  _FlexCANC_RxFifoInterrupt
  #define BrsHwDummyInterrupt179  _FlexCANC_RxFifoInterrupt
  #define BrsHwDummyInterrupt180  _FlexCANC_RxFifoInterrupt
  #define BrsHwDummyInterrupt181  _FlexCANC_RxFifoInterrupt
  #define BrsHwDummyInterrupt182  _FlexCANC_RxFifoInterrupt
  #define BrsHwDummyInterrupt183  _FlexCANC_RxFifoInterrupt
  #define BrsHwDummyInterrupt184  _FlexCANC_MB8To63Interrupt
  #define BrsHwDummyInterrupt185  _FlexCANC_MB8To63Interrupt
  #define BrsHwDummyInterrupt186  _FlexCANC_MB8To63Interrupt
  #define BrsHwDummyInterrupt187  _FlexCANC_MB8To63Interrupt
  #define BrsHwDummyInterrupt188  _FlexCANC_MB8To63Interrupt
  #define BrsHwDummyInterrupt189  _FlexCANC_MB8To63Interrupt
  #define BrsHwDummyInterrupt190  _FlexCANC_MB8To63Interrupt
  #define BrsHwDummyInterrupt191  _FlexCANC_MB8To63Interrupt
  #define BrsHwDummyInterrupt192  _FlexCANC_MB8To63Interrupt
  #define BrsHwDummyInterrupt193  _FlexCANC_MB8To63Interrupt
#    endif
#   endif /*kCanPhysToLogChannelIndex_2*/
#   if defined (kCanPhysToLogChannelIndex_3)
#    if defined (C_ENABLE_CAN_BUSOFF_INTERRUPT)
  #define BrsHwDummyInterrupt308 _FlexCAND_ErrorInterrupt
#    endif
#if defined (C_ENABLE_CAN_RXTX_INTERRUPT)
  #define BrsHwDummyInterrupt311  _FlexCAND_RxFifoInterrupt
  #define BrsHwDummyInterrupt312  _FlexCAND_RxFifoInterrupt
  #define BrsHwDummyInterrupt313  _FlexCAND_RxFifoInterrupt
  #define BrsHwDummyInterrupt314  _FlexCAND_RxFifoInterrupt
  #define BrsHwDummyInterrupt315  _FlexCAND_RxFifoInterrupt
  #define BrsHwDummyInterrupt316  _FlexCAND_RxFifoInterrupt
  #define BrsHwDummyInterrupt317  _FlexCAND_RxFifoInterrupt
  #define BrsHwDummyInterrupt318  _FlexCAND_RxFifoInterrupt
  #define BrsHwDummyInterrupt319  _FlexCAND_MB8To63Interrupt
  #define BrsHwDummyInterrupt320  _FlexCAND_MB8To63Interrupt
  #define BrsHwDummyInterrupt321  _FlexCAND_MB8To63Interrupt
  #define BrsHwDummyInterrupt322  _FlexCAND_MB8To63Interrupt
  #define BrsHwDummyInterrupt323  _FlexCAND_MB8To63Interrupt
  #define BrsHwDummyInterrupt324  _FlexCAND_MB8To63Interrupt
  #define BrsHwDummyInterrupt325  _FlexCAND_MB8To63Interrupt
  #define BrsHwDummyInterrupt326  _FlexCAND_MB8To63Interrupt
  #define BrsHwDummyInterrupt327  _FlexCAND_MB8To63Interrupt
  #define BrsHwDummyInterrupt328  _FlexCAND_MB8To63Interrupt
#    endif
#   endif /*kCanPhysToLogChannelIndex_3*/
#  endif /*BRSHW_USED_CANCELL_DEFAULT*/

  /**********************************************************************************
   *                              MCAN                                              *
   **********************************************************************************/
#  if defined (BRSHW_USED_CANCELL_MCAN)
#   if defined (kCan_30_McanPhysToLogChannelIndex_0) /* M_CAN_0 */
  #define BrsHwDummyInterrupt348  _MCAN0_Interrupt
#   endif
#   if defined (kCan_30_McanPhysToLogChannelIndex_1) /* M_CAN_1 */
  #define BrsHwDummyInterrupt348  _MCAN1_Interrupt
#   endif
#  endif /*BRSHW_USED_CANCELL_MCAN*/
# endif /*VGEN_ENABLE_CAN_DRV*/

  /**********************************************************************************
   *                                                                                *
   *                                      LIN SCI                                   *
   *                                                                                *
   **********************************************************************************/
# if defined (VGEN_ENABLE_LIN_DRV)
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
  #define BrsHwDummyInterrupt146 _LINSCI_LinIsr_0
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
  #define BrsHwDummyInterrupt149 _LINSCI_LinIsr_1
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_2)
  #define BrsHwDummyInterrupt473 _LINSCI_LinIsr_2
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_3)
  #define BrsHwDummyInterrupt474 _LINSCI_LinIsr_3
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_4)
  #define BrsHwDummyInterrupt475 _LINSCI_LinIsr_4
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_5)
  #define BrsHwDummyInterrupt505 _LINSCI_LinIsr_5
#  endif
# endif /*VGEN_ENABLE_LIN_DRV*/

  /**********************************************************************************
   *                           FlexRay                                              *
   **********************************************************************************/
# if defined (VGEN_ENABLE_DRVFR__BASEASR)
  /* Flexray PRIF  */
  #define BrsHwDummyInterrupt351 _BrsHwFlexRayProtInterrupt
# endif

  /**********************************************************************************
   *                                  Timer                                         *
   **********************************************************************************/
  #define BrsHwDummyInterrupt301 _BrsHwTimeBaseInterrupt /* Pit channel_0 */

  /**********************************************************************************
   *                                  Wakeup                                        *
   **********************************************************************************/
# if defined (BRS_ENABLE_EXTERNAL_WAKEUP)
  #define BrsHwDummyInterrupt46 _BrsHwWakeUpIsr_0     /* External Interrupt 0 */
  #define BrsHwDummyInterrupt47 _BrsHwWakeUpIsr_1     /* External Interrupt 1 */
  #define BrsHwDummyInterrupt48 _BrsHwWakeUpIsr_2     /* External Interrupt 2 */
  #define BrsHwDummyInterrupt49 _BrsHwWakeUpIsr_3     /* External Interrupt 3 */
  #define BrsHwDummyInterrupt50 _BrsHwWakeUpIsr_4to15 /* External Interrupt 4-15 */
# endif
#endif /*BRSHW_INTERRUPT_TABLE_GROUP_B*/

#if defined(BRSHW_INTERRUPT_TABLE_GROUP_C)
/*------------------------------------------------------------------------------------|
 |                                                                                    |
 |                          Interrupt Group C                                         |
 |                                                                                    |
 |------------------------------------------------------------------------------------|*/
# if defined(BRS_COMP_GHS) 
  #define INTERRUPT_ALIGNMENT 2
# endif

  /**********************************************************************************
   *                                 FlexCan                                        *
   **********************************************************************************/
# if defined (VGEN_ENABLE_CAN_DRV)
#  if defined (kCanPhysToLogChannelIndex_0)
#   if (BRSHW_INTERRUPT_TABLE_GROUP_C == TTCAN)
  #define BrsHwDummyInterrupt677 _TTCAN1_LINE0_Interrupt
  #define BrsHwDummyInterrupt678 _TTCAN1_LINE0_Interrupt
#   else
  #define BrsHwDummyInterrupt686 _MCAN0_LINE0_Interrupt
  #define BrsHwDummyInterrupt687 _MCAN0_LINE0_Interrupt
#   endif
#  endif
#  if defined (kCanPhysToLogChannelIndex_1)
  #define BrsHwDummyInterrupt688 _MCAN1_LINE0_Interrupt
  #define BrsHwDummyInterrupt689 _MCAN1_LINE0_Interrupt
#  endif
  #if defined (kCanPhysToLogChannelIndex_2)
  #define BrsHwDummyInterrupt690 _MCAN2_LINE0_Interrupt
  #define BrsHwDummyInterrupt691 _MCAN2_LINE0_Interrupt
#  endif
#  if defined (kCanPhysToLogChannelIndex_3)
  #define BrsHwDummyInterrupt692 _MCAN3_LINE0_Interrupt
  #define BrsHwDummyInterrupt693 _MCAN3_LINE0_Interrupt
#  endif
#  if defined (kCanPhysToLogChannelIndex_4)
  #define BrsHwDummyInterrupt694 _MCAN4_LINE0_Interrupt
  #define BrsHwDummyInterrupt695 _MCAN4_LINE0_Interrupt
#  endif
# endif /*VGEN_ENABLE_CAN_DRV*/

  /**********************************************************************************
   *                                      LIN                                       *
   **********************************************************************************/
# if defined (VGEN_ENABLE_LIN_DRV)
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
  #define BrsHwDummyInterrupt376 _LINFLEX_LinIsr_RXI_0  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt377 _LINFLEX_LinIsr_TXI_0  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt378 _LINFLEX_LinIsr_ERR_0  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
  #define BrsHwDummyInterrupt380 _LINFLEX_LinIsr_RXI_1  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt381 _LINFLEX_LinIsr_TXI_1  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt382 _LINFLEX_LinIsr_ERR_1  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_2)
  #define BrsHwDummyInterrupt384 _LINFLEX_LinIsr_RXI_2  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt385 _LINFLEX_LinIsr_TXI_2  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt386 _LINFLEX_LinIsr_ERR_2  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_14)
  #define BrsHwDummyInterrupt432 _LINFLEX_LinIsr_RXI_14  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt433 _LINFLEX_LinIsr_TXI_14  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt434 _LINFLEX_LinIsr_ERR_14  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_15)
  #define BrsHwDummyInterrupt436 _LINFLEX_LinIsr_RXI_15  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt437 _LINFLEX_LinIsr_TXI_15  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt438 _LINFLEX_LinIsr_ERR_15  /* LINFlex_ERR */
#  endif
# endif /*VGEN_ENABLE_LIN_DRV*/

  /**********************************************************************************
   *                           FlexRay                                              *
   **********************************************************************************/
# if defined (VGEN_ENABLE_DRVFR__BASEASR)
  #define BrsHwDummyInterrupt458 _BrsHwFlexRayProtInterrupt /* Flexray PRIF*/
# endif

  /**********************************************************************************
   *                                  Timer                                         *
   **********************************************************************************/
# if defined (BRSHW_TIMER_GROUP_A)
#  if defined (BRS_DERIVATIVE_SPC574Kxx)
  #define BrsHwDummyInterrupt240 _BrsHwTimeBaseInterrupt
#  else
  #define BrsHwDummyInterrupt226 _BrsHwTimeBaseInterrupt
#  endif
# endif
#endif /*BRSHW_INTERRUPT_TABLE_GROUP_C*/

#if defined (BRSHW_INTERRUPT_TABLE_GROUP_D)
/*------------------------------------------------------------------------------------|
 |                                                                                    |
 |                          Interrupt Group D                                         |
 |                                                                                    |
 |------------------------------------------------------------------------------------|*/
# if defined(BRS_COMP_GHS) 
  #define INTERRUPT_ALIGNMENT 2
# endif

/**********************************************************************************
 *                                 FlexCan                                        *
 **********************************************************************************/
# if defined (VGEN_ENABLE_CAN_DRV)
#  if defined (kCanPhysToLogChannelIndex_0)
#   if !defined (C_ENABLE_ERROR_POLLING)
  #define BrsHwDummyInterrupt52 _FlexCANA_ErrorInterrupt
#   endif
#   if defined (C_ENABLE_CAN_INTERRUPT)
#    if defined (C_ENABLE_SINGLE_ISR_API)
  #define BrsHwDummyInterrupt57  _FlexCANA_Interrupt
  #define BrsHwDummyInterrupt58  _FlexCANA_Interrupt
  #define BrsHwDummyInterrupt59  _FlexCANA_Interrupt
  #define BrsHwDummyInterrupt60  _FlexCANA_Interrupt
  #define BrsHwDummyInterrupt61  _FlexCANA_Interrupt
  #define BrsHwDummyInterrupt62  _FlexCANA_Interrupt
  #define BrsHwDummyInterrupt63  _FlexCANA_Interrupt
  #define BrsHwDummyInterrupt64  _FlexCANA_Interrupt
  #define BrsHwDummyInterrupt65  _FlexCANA_Interrupt
  #define BrsHwDummyInterrupt66  _FlexCANA_Interrupt
  #define BrsHwDummyInterrupt67  _FlexCANA_Interrupt
  #define BrsHwDummyInterrupt68  _FlexCANA_Interrupt
  #define BrsHwDummyInterrupt69  _FlexCANA_Interrupt
  #define BrsHwDummyInterrupt70  _FlexCANA_Interrupt
  #define BrsHwDummyInterrupt71  _FlexCANA_Interrupt
  #define BrsHwDummyInterrupt72  _FlexCANA_Interrupt
  #define BrsHwDummyInterrupt73  _FlexCANA_Interrupt
  #define BrsHwDummyInterrupt74  _FlexCANA_Interrupt
#     if defined (C_ENABLE_MB64TO95)
  #define BrsHwDummyInterrupt287  _FlexCANA_Interrupt
#     endif
#     if defined (C_ENABLE_MB96TO127)
  #define BrsHwDummyInterrupt288  _FlexCANA_Interrupt
#     endif

#    else /*C_ENABLE_SINGLE_ISR_API*/
  #define BrsHwDummyInterrupt57  _FlexCANA_MB0Interrupt
  #define BrsHwDummyInterrupt58  _FlexCANA_MB1Interrupt
  #define BrsHwDummyInterrupt59  _FlexCANA_MB2Interrupt
  #define BrsHwDummyInterrupt60  _FlexCANA_MB3Interrupt
  #define BrsHwDummyInterrupt61  _FlexCANA_MB4Interrupt
  #define BrsHwDummyInterrupt62  _FlexCANA_MB5Interrupt
  #define BrsHwDummyInterrupt63  _FlexCANA_MB6Interrupt
  #define BrsHwDummyInterrupt64  _FlexCANA_MB7Interrupt
  #define BrsHwDummyInterrupt65  _FlexCANA_MB8Interrupt
  #define BrsHwDummyInterrupt66  _FlexCANA_MB9Interrupt
  #define BrsHwDummyInterrupt67  _FlexCANA_MB10Interrupt
  #define BrsHwDummyInterrupt68  _FlexCANA_MB11Interrupt
  #define BrsHwDummyInterrupt69  _FlexCANA_MB12Interrupt
  #define BrsHwDummyInterrupt70  _FlexCANA_MB13Interrupt
  #define BrsHwDummyInterrupt71  _FlexCANA_MB14Interrupt
  #define BrsHwDummyInterrupt72  _FlexCANA_MB15Interrupt
  #define BrsHwDummyInterrupt73  _FlexCANA_MB16To31Interrupt
  #define BrsHwDummyInterrupt74  _FlexCANA_MB32To63Interrupt
#     if defined (C_ENABLE_MB64TO95)
  #define BrsHwDummyInterrupt287  _FlexCANA_MB64To95Interrupt
#     endif
#     if defined (C_ENABLE_MB96TO127)
  #define BrsHwDummyInterrupt288  _FlexCANA_MB96To127Interrupt
#     endif
#    endif /*else C_ENABLE_SINGLE_ISR_API*/
#   endif /*C_ENABLE_CAN_INTERRUPT*/
#  endif /*kCanPhysToLogChannelIndex_0*/

#  if defined (kCanPhysToLogChannelIndex_1)
#   if !defined (C_ENABLE_ERROR_POLLING)
  #define BrsHwDummyInterrupt75 _FlexCANB_ErrorInterrupt
#   endif
#   if defined (C_ENABLE_CAN_INTERRUPT)
#    if defined (C_ENABLE_SINGLE_ISR_API)
  #define BrsHwDummyInterrupt80  _FlexCANB_Interrupt
  #define BrsHwDummyInterrupt81  _FlexCANB_Interrupt
  #define BrsHwDummyInterrupt82  _FlexCANB_Interrupt
  #define BrsHwDummyInterrupt83  _FlexCANB_Interrupt
  #define BrsHwDummyInterrupt84  _FlexCANB_Interrupt
  #define BrsHwDummyInterrupt85  _FlexCANB_Interrupt
  #define BrsHwDummyInterrupt86  _FlexCANB_Interrupt
  #define BrsHwDummyInterrupt87  _FlexCANB_Interrupt
  #define BrsHwDummyInterrupt88  _FlexCANB_Interrupt
  #define BrsHwDummyInterrupt89  _FlexCANB_Interrupt
  #define BrsHwDummyInterrupt90  _FlexCANB_Interrupt
  #define BrsHwDummyInterrupt91  _FlexCANB_Interrupt
  #define BrsHwDummyInterrupt92  _FlexCANB_Interrupt
  #define BrsHwDummyInterrupt93  _FlexCANB_Interrupt
  #define BrsHwDummyInterrupt94  _FlexCANB_Interrupt
  #define BrsHwDummyInterrupt95  _FlexCANB_Interrupt
  #define BrsHwDummyInterrupt96  _FlexCANB_Interrupt
  #define BrsHwDummyInterrupt97  _FlexCANB_Interrupt
#     if defined (C_ENABLE_MB64TO95)
  #define BrsHwDummyInterrupt289  _FlexCANB_Interrupt
#     endif
#     if defined (C_ENABLE_MB96TO127)
  #define BrsHwDummyInterrupt290  _FlexCANB_Interrupt
#     endif

#    else /*C_ENABLE_SINGLE_ISR_API*/
  #define BrsHwDummyInterrupt80  _FlexCANB_MB0Interrupt
  #define BrsHwDummyInterrupt81  _FlexCANB_MB1Interrupt
  #define BrsHwDummyInterrupt82  _FlexCANB_MB2Interrupt
  #define BrsHwDummyInterrupt83  _FlexCANB_MB3Interrupt
  #define BrsHwDummyInterrupt84  _FlexCANB_MB4Interrupt
  #define BrsHwDummyInterrupt85  _FlexCANB_MB5Interrupt
  #define BrsHwDummyInterrupt86  _FlexCANB_MB6Interrupt
  #define BrsHwDummyInterrupt87  _FlexCANB_MB7Interrupt
  #define BrsHwDummyInterrupt88  _FlexCANB_MB8Interrupt
  #define BrsHwDummyInterrupt89  _FlexCANB_MB9Interrupt
  #define BrsHwDummyInterrupt90  _FlexCANB_MB10Interrupt
  #define BrsHwDummyInterrupt91  _FlexCANB_MB11Interrupt
  #define BrsHwDummyInterrupt92  _FlexCANB_MB12Interrupt
  #define BrsHwDummyInterrupt93  _FlexCANB_MB13Interrupt
  #define BrsHwDummyInterrupt94  _FlexCANB_MB14Interrupt
  #define BrsHwDummyInterrupt95  _FlexCANB_MB15Interrupt
  #define BrsHwDummyInterrupt96  _FlexCANB_MB16To31Interrupt
  #define BrsHwDummyInterrupt97  _FlexCANB_MB32To63Interrupt
#     if defined (C_ENABLE_MB64TO95)
  #define BrsHwDummyInterrupt289  _FlexCANB_MB64To95Interrupt
#     endif
#     if defined (C_ENABLE_MB96TO127)
  #define BrsHwDummyInterrupt290  _FlexCANB_MB96To127Interrupt
#     endif
#    endif /*else C_ENABLE_SINGLE_ISR_API*/
#   endif /*C_ENABLE_CAN_INTERRUPT*/
#  endif /*kCanPhysToLogChannelIndex_1*/

#  if defined (kCanPhysToLogChannelIndex_2)
#   if !defined (C_ENABLE_ERROR_POLLING)
  #define BrsHwDummyInterrupt239 _FlexCANC_ErrorInterrupt
#   endif
#   if defined (C_ENABLE_CAN_INTERRUPT)
#    if defined (C_ENABLE_SINGLE_ISR_API)
  #define BrsHwDummyInterrupt244  _FlexCANC_Interrupt
  #define BrsHwDummyInterrupt245  _FlexCANC_Interrupt
  #define BrsHwDummyInterrupt246  _FlexCANC_Interrupt
  #define BrsHwDummyInterrupt247  _FlexCANC_Interrupt
  #define BrsHwDummyInterrupt248  _FlexCANC_Interrupt
  #define BrsHwDummyInterrupt249  _FlexCANC_Interrupt
  #define BrsHwDummyInterrupt250  _FlexCANC_Interrupt
  #define BrsHwDummyInterrupt251  _FlexCANC_Interrupt
  #define BrsHwDummyInterrupt252  _FlexCANC_Interrupt
  #define BrsHwDummyInterrupt253  _FlexCANC_Interrupt
  #define BrsHwDummyInterrupt254  _FlexCANC_Interrupt
  #define BrsHwDummyInterrupt255  _FlexCANC_Interrupt
  #define BrsHwDummyInterrupt256  _FlexCANC_Interrupt
  #define BrsHwDummyInterrupt257  _FlexCANC_Interrupt
  #define BrsHwDummyInterrupt258  _FlexCANC_Interrupt
  #define BrsHwDummyInterrupt259  _FlexCANC_Interrupt
  #define BrsHwDummyInterrupt260  _FlexCANC_Interrupt
  #define BrsHwDummyInterrupt261  _FlexCANC_Interrupt
#    if defined (C_ENABLE_MB64TO95)
  #define BrsHwDummyInterrupt291  _FlexCANC_Interrupt
#    endif
#    if defined (C_ENABLE_MB96TO127)
  #define BrsHwDummyInterrupt292  _FlexCANC_Interrupt
#    endif

#    else /*C_ENABLE_SINGLE_ISR_API*/
  #define BrsHwDummyInterrupt244  _FlexCANC_MB0Interrupt
  #define BrsHwDummyInterrupt245  _FlexCANC_MB1Interrupt
  #define BrsHwDummyInterrupt246  _FlexCANC_MB2Interrupt
  #define BrsHwDummyInterrupt247  _FlexCANC_MB3Interrupt
  #define BrsHwDummyInterrupt248  _FlexCANC_MB4Interrupt
  #define BrsHwDummyInterrupt249  _FlexCANC_MB5Interrupt
  #define BrsHwDummyInterrupt250  _FlexCANC_MB6Interrupt
  #define BrsHwDummyInterrupt251  _FlexCANC_MB7Interrupt
  #define BrsHwDummyInterrupt252  _FlexCANC_MB8Interrupt
  #define BrsHwDummyInterrupt253  _FlexCANC_MB9Interrupt
  #define BrsHwDummyInterrupt254  _FlexCANC_MB10Interrupt
  #define BrsHwDummyInterrupt255  _FlexCANC_MB11Interrupt
  #define BrsHwDummyInterrupt256  _FlexCANC_MB12Interrupt
  #define BrsHwDummyInterrupt257  _FlexCANC_MB13Interrupt
  #define BrsHwDummyInterrupt258  _FlexCANC_MB14Interrupt
  #define BrsHwDummyInterrupt259  _FlexCANC_MB15Interrupt
  #define BrsHwDummyInterrupt260  _FlexCANC_MB16To31Interrupt
  #define BrsHwDummyInterrupt261  _FlexCANC_MB32To63Interrupt
#     if defined (C_ENABLE_MB64TO95)
  #define BrsHwDummyInterrupt291  _FlexCANC_MB64To95Interrupt
#     endif
#     if defined (C_ENABLE_MB96TO127)
  #define BrsHwDummyInterrupt292  _FlexCANC_MB96To127Interrupt
#     endif
#    endif /*else C_ENABLE_SINGLE_ISR_API*/
#   endif /*C_ENABLE_CAN_INTERRUPT*/
#  endif /*kCanPhysToLogChannelIndex_2*/
# endif /*VGEN_ENABLE_CAN_DRV*/

  /**********************************************************************************
   *                                      LIN                                       *
   **********************************************************************************/
# if defined (VGEN_ENABLE_LIN_DRV)
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
  #define BrsHwDummyInterrupt262 _LINFLEX_LinIsr_RXI_0
  #define BrsHwDummyInterrupt263 _LINFLEX_LinIsr_TXI_0
  #define BrsHwDummyInterrupt264 _LINFLEX_LinIsr_ERR_0
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
  #define BrsHwDummyInterrupt265 _LINFLEX_LinIsr_RXI_1
  #define BrsHwDummyInterrupt266 _LINFLEX_LinIsr_TXI_1
  #define BrsHwDummyInterrupt267 _LINFLEX_LinIsr_ERR_1
#  endif
# endif /*VGEN_ENABLE_LIN_DRV*/

  /**********************************************************************************
   *                           FlexRay                                              *
   **********************************************************************************/
# if defined (VGEN_ENABLE_DRVFR__BASEASR)
  #define BrsHwDummyInterrupt99 _BrsHwFlexRayProtInterrupt /* Flexray PRIF*/
# endif

  /**********************************************************************************
   *                                  Timer                                         *
   **********************************************************************************/
  #define BrsHwDummyInterrupt16 _BrsHwTimeBaseInterrupt
#endif /*BRSHW_INTERRUPT_TABLE_GROUP_D*/

#if defined(BRSHW_INTERRUPT_TABLE_GROUP_E)
/*------------------------------------------------------------------------------------|
 |                                                                                    |
 |                          Interrupt Group E                                         |
 |                                                                                    |
 |------------------------------------------------------------------------------------|*/
# if defined(BRS_COMP_GHS) 
  #define INTERRUPT_ALIGNMENT 2
# endif

  /**********************************************************************************
   *                                 FlexCan                                        *
   **********************************************************************************/
# if defined (VGEN_ENABLE_CAN_DRV)
#  if defined (kCanPhysToLogChannelIndex_0)
#   if defined (C_ENABLE_CAN_BUSOFF_INTERRUPT)
  #define BrsHwDummyInterrupt567 _FlexCANA_ErrorInterrupt
#   endif
#  if defined (C_ENABLE_CAN_RXTX_INTERRUPT)
  #define BrsHwDummyInterrupt568 _FlexCANA_RxFifoInterrupt
  #define BrsHwDummyInterrupt569 _FlexCANA_RxFifoInterrupt
  #define BrsHwDummyInterrupt570 _FlexCANA_MB8To63Interrupt
  #define BrsHwDummyInterrupt571 _FlexCANA_MB8To63Interrupt
  #define BrsHwDummyInterrupt572 _FlexCANA_MB8To63Interrupt
  #define BrsHwDummyInterrupt573 _FlexCANA_MB8To63Interrupt
#    if defined (C_CAN_MAX_BUFFER_96)
  #define BrsHwDummyInterrupt574 _FlexCANA_MB64To95Interrupt
#    endif
#   endif
#  endif /*kCanPhysToLogChannelIndex_0*/
#  if defined (kCanPhysToLogChannelIndex_1)
#   if defined (C_ENABLE_CAN_BUSOFF_INTERRUPT)
  #define BrsHwDummyInterrupt579 _FlexCANB_ErrorInterrupt
#   endif
#   if defined (C_ENABLE_CAN_RXTX_INTERRUPT)
  #define BrsHwDummyInterrupt580 _FlexCANB_RxFifoInterrupt
  #define BrsHwDummyInterrupt581 _FlexCANB_RxFifoInterrupt
  #define BrsHwDummyInterrupt582 _FlexCANB_MB8To63Interrupt
  #define BrsHwDummyInterrupt583 _FlexCANB_MB8To63Interrupt
  #define BrsHwDummyInterrupt584 _FlexCANB_MB8To63Interrupt
  #define BrsHwDummyInterrupt585 _FlexCANB_MB8To63Interrupt
#    if defined (C_CAN_MAX_BUFFER_96)
  #define BrsHwDummyInterrupt586 _FlexCANB_MB64To95Interrupt
#    endif
#   endif
#  endif /*kCanPhysToLogChannelIndex_1*/
#  if defined (kCanPhysToLogChannelIndex_2)
#   if defined (C_ENABLE_CAN_BUSOFF_INTERRUPT)
  #define BrsHwDummyInterrupt591 _FlexCANC_ErrorInterrupt
#   endif
#   if defined (C_ENABLE_CAN_RXTX_INTERRUPT)
  #define BrsHwDummyInterrupt592 _FlexCANC_RxFifoInterrupt
  #define BrsHwDummyInterrupt593 _FlexCANC_RxFifoInterrupt
  #define BrsHwDummyInterrupt594 _FlexCANC_MB8To63Interrupt
  #define BrsHwDummyInterrupt595 _FlexCANC_MB8To63Interrupt
  #define BrsHwDummyInterrupt596 _FlexCANC_MB8To63Interrupt
  #define BrsHwDummyInterrupt597 _FlexCANC_MB8To63Interrupt
#    if defined (C_CAN_MAX_BUFFER_96)
  #define BrsHwDummyInterrupt598 _FlexCANC_MB64To95Interrupt
#    endif
#   endif
#  endif /*kCanPhysToLogChannelIndex_2*/
#  if defined (kCanPhysToLogChannelIndex_3)
#   if defined (C_ENABLE_CAN_BUSOFF_INTERRUPT)
  #define BrsHwDummyInterrupt603 _FlexCAND_ErrorInterrupt
#   endif
#   if defined (C_ENABLE_CAN_RXTX_INTERRUPT)
  #define BrsHwDummyInterrupt604 _FlexCAND_RxFifoInterrupt
  #define BrsHwDummyInterrupt605 _FlexCAND_RxFifoInterrupt
  #define BrsHwDummyInterrupt606 _FlexCAND_MB8To63Interrupt
  #define BrsHwDummyInterrupt607 _FlexCAND_MB8To63Interrupt
  #define BrsHwDummyInterrupt608 _FlexCAND_MB8To63Interrupt
  #define BrsHwDummyInterrupt609 _FlexCAND_MB8To63Interrupt
#    if defined (C_CAN_MAX_BUFFER_96)
  #define BrsHwDummyInterrupt610 _FlexCAND_MB64To95Interrupt
#    endif
#   endif
#  endif /*kCanPhysToLogChannelIndex_3*/
#  if defined (kCanPhysToLogChannelIndex_4)
#   if defined (C_ENABLE_CAN_BUSOFF_INTERRUPT)
  #define BrsHwDummyInterrupt615 _FlexCANE_ErrorInterrupt
#   endif
#   if defined (C_ENABLE_CAN_RXTX_INTERRUPT)
  #define BrsHwDummyInterrupt616 _FlexCANE_RxFifoInterrupt
  #define BrsHwDummyInterrupt617 _FlexCANE_RxFifoInterrupt
  #define BrsHwDummyInterrupt618 _FlexCANE_MB8To63Interrupt
  #define BrsHwDummyInterrupt619 _FlexCANE_MB8To63Interrupt
  #define BrsHwDummyInterrupt620 _FlexCANE_MB8To63Interrupt
  #define BrsHwDummyInterrupt621 _FlexCANE_MB8To63Interrupt
#    if defined (C_CAN_MAX_BUFFER_96)
  #define BrsHwDummyInterrupt622 _FlexCANE_MB64To95Interrupt
#    endif
#   endif
#  endif /*kCanPhysToLogChannelIndex_4*/
#  if defined (kCanPhysToLogChannelIndex_5)
#   if defined (C_ENABLE_CAN_BUSOFF_INTERRUPT)
  #define BrsHwDummyInterrupt627 _FlexCANF_ErrorInterrupt
#   endif
#   if defined (C_ENABLE_CAN_RXTX_INTERRUPT)
  #define BrsHwDummyInterrupt628 _FlexCANF_RxFifoInterrupt
  #define BrsHwDummyInterrupt629 _FlexCANF_RxFifoInterrupt
  #define BrsHwDummyInterrupt630 _FlexCANF_MB8To63Interrupt
  #define BrsHwDummyInterrupt631 _FlexCANF_MB8To63Interrupt
  #define BrsHwDummyInterrupt632 _FlexCANF_MB8To63Interrupt
  #define BrsHwDummyInterrupt633 _FlexCANF_MB8To63Interrupt
#    if defined (C_CAN_MAX_BUFFER_96)
  #define BrsHwDummyInterrupt634 _FlexCANF_MB64To95Interrupt
#    endif
#   endif
#  endif /*kCanPhysToLogChannelIndex_5*/
#  if defined (kCanPhysToLogChannelIndex_6)
#   if defined (C_ENABLE_CAN_BUSOFF_INTERRUPT)
  #define BrsHwDummyInterrupt639 _FlexCANG_ErrorInterrupt
#   endif
#   if defined (C_ENABLE_CAN_RXTX_INTERRUPT)
  #define BrsHwDummyInterrupt640 _FlexCANG_RxFifoInterrupt
  #define BrsHwDummyInterrupt641 _FlexCANG_RxFifoInterrupt
  #define BrsHwDummyInterrupt642 _FlexCANG_MB8To63Interrupt
  #define BrsHwDummyInterrupt643 _FlexCANG_MB8To63Interrupt
  #define BrsHwDummyInterrupt644 _FlexCANG_MB8To63Interrupt
  #define BrsHwDummyInterrupt645 _FlexCANG_MB8To63Interrupt
#    if defined (C_CAN_MAX_BUFFER_96)
  #define BrsHwDummyInterrupt646 _FlexCANG_MB64To95Interrupt
#    endif
#   endif
#  endif /*kCanPhysToLogChannelIndex_6*/
#  if defined (kCanPhysToLogChannelIndex_7)
#   if defined (C_ENABLE_CAN_BUSOFF_INTERRUPT)
  #define BrsHwDummyInterrupt651 _FlexCANH_ErrorInterrupt
#   endif
#   if defined (C_ENABLE_CAN_RXTX_INTERRUPT)
  #define BrsHwDummyInterrupt652 _FlexCANH_RxFifoInterrupt
  #define BrsHwDummyInterrupt653 _FlexCANH_RxFifoInterrupt
  #define BrsHwDummyInterrupt654 _FlexCANH_MB8To63Interrupt
  #define BrsHwDummyInterrupt655 _FlexCANH_MB8To63Interrupt
  #define BrsHwDummyInterrupt656 _FlexCANH_MB8To63Interrupt
  #define BrsHwDummyInterrupt657 _FlexCANH_MB8To63Interrupt
#    if defined (C_CAN_MAX_BUFFER_96)
  #define BrsHwDummyInterrupt658 _FlexCANH_MB64To95Interrupt
#    endif
#   endif
#  endif /*kCanPhysToLogChannelIndex_7*/
# endif /*VGEN_ENABLE_CAN_DRV*/

  /**********************************************************************************
   *                                      LIN                                       *
   **********************************************************************************/
# if defined (VGEN_ENABLE_LIN_DRV)
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
  #define BrsHwDummyInterrupt376 _LINFLEX_LinIsr_RXI_0  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt377 _LINFLEX_LinIsr_TXI_0  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt378 _LINFLEX_LinIsr_ERR_0  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
  #define BrsHwDummyInterrupt379 _LINFLEX_LinIsr_RXI_1  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt380 _LINFLEX_LinIsr_TXI_1  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt381 _LINFLEX_LinIsr_ERR_1  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_2)
  #define BrsHwDummyInterrupt382 _LINFLEX_LinIsr_RXI_2  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt383 _LINFLEX_LinIsr_TXI_2  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt384 _LINFLEX_LinIsr_ERR_2  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_3)
  #define BrsHwDummyInterrupt385 _LINFLEX_LinIsr_RXI_3  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt386 _LINFLEX_LinIsr_TXI_3  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt387 _LINFLEX_LinIsr_ERR_3  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_4)
  #define BrsHwDummyInterrupt388 _LINFLEX_LinIsr_RXI_4  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt389 _LINFLEX_LinIsr_TXI_4  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt390 _LINFLEX_LinIsr_ERR_4  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_5)
  #define BrsHwDummyInterrupt391 _LINFLEX_LinIsr_RXI_5  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt392 _LINFLEX_LinIsr_TXI_5  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt393 _LINFLEX_LinIsr_ERR_5  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_6)
  #define BrsHwDummyInterrupt394 _LINFLEX_LinIsr_RXI_6  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt395 _LINFLEX_LinIsr_TXI_6  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt396 _LINFLEX_LinIsr_ERR_6  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_7)
  #define BrsHwDummyInterrupt397 _LINFLEX_LinIsr_RXI_7  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt398 _LINFLEX_LinIsr_TXI_7  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt399 _LINFLEX_LinIsr_ERR_7  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_8)
  #define BrsHwDummyInterrupt400 _LINFLEX_LinIsr_RXI_8  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt401 _LINFLEX_LinIsr_TXI_8  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt402 _LINFLEX_LinIsr_ERR_8  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_9)
  #define BrsHwDummyInterrupt403 _LINFLEX_LinIsr_RXI_9  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt404 _LINFLEX_LinIsr_TXI_9  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt405 _LINFLEX_LinIsr_ERR_9  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_10)
  #define BrsHwDummyInterrupt406 _LINFLEX_LinIsr_RXI_10  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt407 _LINFLEX_LinIsr_TXI_10  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt408 _LINFLEX_LinIsr_ERR_10  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_11)
  #define BrsHwDummyInterrupt409 _LINFLEX_LinIsr_RXI_11  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt410 _LINFLEX_LinIsr_TXI_11  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt411 _LINFLEX_LinIsr_ERR_11  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_12)
  #define BrsHwDummyInterrupt412 _LINFLEX_LinIsr_RXI_12  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt413 _LINFLEX_LinIsr_TXI_12  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt414 _LINFLEX_LinIsr_ERR_12  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_13)
  #define BrsHwDummyInterrupt415 _LINFLEX_LinIsr_RXI_13  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt416 _LINFLEX_LinIsr_TXI_13  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt417 _LINFLEX_LinIsr_ERR_13  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_14)
  #define BrsHwDummyInterrupt418 _LINFLEX_LinIsr_RXI_14  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt419 _LINFLEX_LinIsr_TXI_14  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt420 _LINFLEX_LinIsr_ERR_14  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_15)
  #define BrsHwDummyInterrupt421 _LINFLEX_LinIsr_RXI_15  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt422 _LINFLEX_LinIsr_TXI_15  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt423 _LINFLEX_LinIsr_ERR_15  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_16)
  #define BrsHwDummyInterrupt424 _LINFLEX_LinIsr_RXI_16  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt425 _LINFLEX_LinIsr_TXI_16  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt426 _LINFLEX_LinIsr_ERR_16  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_17)
  #define BrsHwDummyInterrupt427 _LINFLEX_LinIsr_RXI_17  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt428 _LINFLEX_LinIsr_TXI_17  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt429 _LINFLEX_LinIsr_ERR_17  /* LINFlex_ERR */
#  endif
# endif /*VGEN_ENABLE_LIN_DRV*/

  /**********************************************************************************
   *                           FlexRay                                              *
   **********************************************************************************/
# if defined (VGEN_ENABLE_DRVFR__BASEASR)
  #define BrsHwDummyInterrupt458 _BrsHwFlexRayProtInterrupt /* Flexray PRIF*/ 
# endif

  /**********************************************************************************
   *                           Ethernet                                             *
   **********************************************************************************/
# if defined (VGEN_ENABLE_DRVETH__BASEASR)
      #define BrsHwDummyInterrupt211 _EthIsr_Rx /* ENET Interrupt Group1 */
      #define BrsHwDummyInterrupt212 _EthIsr_Tx /* ENET Interrupt Group2 */
# endif

  /**********************************************************************************
   *                                  Timer                                         *
   **********************************************************************************/
# if defined (BRSHW_TIMER_GROUP_A)
  #define BrsHwDummyInterrupt226 _BrsHwTimeBaseInterrupt
# endif
#endif /*BRSHW_INTERRUPT_TABLE_GROUP_E*/

#if defined (BRSHW_INTERRUPT_TABLE_GROUP_F)
/*------------------------------------------------------------------------------------|
 |                                                                                    |
 |                             Interrupt Group F                                      |
 |                                                                                    |
 |------------------------------------------------------------------------------------|*/
# if defined(BRS_COMP_GHS) 
  #define INTERRUPT_ALIGNMENT 2
# endif

  /**********************************************************************************
   *                                 FlexCan                                        *
   **********************************************************************************/
# if defined (VGEN_ENABLE_CAN_DRV)
#  if defined (kCanPhysToLogChannelIndex_0)
  #define BrsHwDummyInterrupt677 _FlexCANA_MB0To3Interrupt
  #define BrsHwDummyInterrupt678 _FlexCANA_MB4To7Interrupt
  #define BrsHwDummyInterrupt679 _FlexCANA_MB8To11Interrupt
  #define BrsHwDummyInterrupt680 _FlexCANA_MB12To15Interrupt
  #define BrsHwDummyInterrupt681 _FlexCANA_MB16To31Interrupt

  #define BrsHwDummyInterrupt687 _FlexCANA_Interrupt      /* Error IRQ */
  #define BrsHwDummyInterrupt688 _FlexCANA_ErrorInterrupt /* Bus Off IRQ */
#  endif /*kCanPhysToLogChannelIndex_0*/
#  if defined (kCanPhysToLogChannelIndex_1)
  #define BrsHwDummyInterrupt690 _FlexCANB_MB0To3Interrupt
  #define BrsHwDummyInterrupt691 _FlexCANB_MB4To7Interrupt
  #define BrsHwDummyInterrupt692 _FlexCANB_MB8To11Interrupt
  #define BrsHwDummyInterrupt693 _FlexCANB_MB12To15Interrupt
  #define BrsHwDummyInterrupt694 _FlexCANB_MB16To31Interrupt

  #define BrsHwDummyInterrupt700 _FlexCANB_Interrupt      /* Error IRQ */
  #define BrsHwDummyInterrupt701 _FlexCANB_ErrorInterrupt /* Bus Off IRQ */
#  endif /*kCanPhysToLogChannelIndex_1*/
# endif /*VGEN_ENABLE_CAN_DRV*/

  /**********************************************************************************
   *                                      LIN                                       *
   **********************************************************************************/
# if defined (VGEN_ENABLE_LIN_DRV)
  #error "LIN interrupts not yet supported"
# endif

  /**********************************************************************************
   *                                  Timer                                         *
   **********************************************************************************/
  #define BrsHwDummyInterrupt226 BrsHwTimeBaseInterrupt
#endif /*BRSHW_INTERRUPT_TABLE_GROUP_F*/

#if defined (BRSHW_INTERRUPT_TABLE_GROUP_G)
/*------------------------------------------------------------------------------------|
 |                                                                                    |
 |                          Interrupt Group G                                         |
 |                                                                                    |
 |------------------------------------------------------------------------------------|*/
# if defined(BRS_COMP_GHS) 
  #define INTERRUPT_ALIGNMENT 2
# endif

  /**********************************************************************************
   *                                 FlexCan                                        *
   **********************************************************************************/
# if defined (VGEN_ENABLE_CAN_DRV)
#  if defined (kCanPhysToLogChannelIndex_0)
#   if defined (C_ENABLE_CAN_BUSOFF_INTERRUPT)
  #define BrsHwDummyInterrupt677 _FlexCANA_ErrorInterrupt
#   endif
#   if defined (C_ENABLE_CAN_RXTX_INTERRUPT)
  #define BrsHwDummyInterrupt678 BrsHwDummyInterrupt678 /* Unused! */
  #define BrsHwDummyInterrupt679 _FlexCANA_RxFifoInterrupt
  #define BrsHwDummyInterrupt680 _FlexCANA_MB8To63Interrupt
  #define BrsHwDummyInterrupt681 _FlexCANA_MB8To63Interrupt
#    if defined (C_CAN_MAX_BUFFER_96)
  #define BrsHwDummyInterrupt682 _FlexCANA_MB64To95Interrupt
#    endif
#   endif
#  endif /*kCanPhysToLogChannelIndex_0*/
#  if defined (kCanPhysToLogChannelIndex_1)
#   if defined (C_ENABLE_CAN_BUSOFF_INTERRUPT)
  #define BrsHwDummyInterrupt683 _FlexCANB_ErrorInterrupt
#   endif
#   if defined (C_ENABLE_CAN_RXTX_INTERRUPT)
  #define BrsHwDummyInterrupt684 BrsHwDummyInterrupt684 /* Unused! */
  #define BrsHwDummyInterrupt685 _FlexCANB_RxFifoInterrupt
  #define BrsHwDummyInterrupt686 _FlexCANB_MB8To63Interrupt
  #define BrsHwDummyInterrupt687 _FlexCANB_MB8To63Interrupt
#    if defined (C_CAN_MAX_BUFFER_96)
  #define BrsHwDummyInterrupt688 _FlexCANB_MB64To95Interrupt
#    endif
#   endif
#  endif /*kCanPhysToLogChannelIndex_1*/
#  if defined (kCanPhysToLogChannelIndex_2)
#   if defined (C_ENABLE_CAN_BUSOFF_INTERRUPT)
  #define BrsHwDummyInterrupt689 _FlexCANC_ErrorInterrupt
#   endif
#   if defined (C_ENABLE_CAN_RXTX_INTERRUPT)
  #define BrsHwDummyInterrupt690 BrsHwDummyInterrupt690 /* Unused! */
  #define BrsHwDummyInterrupt691 _FlexCANC_RxFifoInterrupt
  #define BrsHwDummyInterrupt692 _FlexCANC_MB8To63Interrupt
  #define BrsHwDummyInterrupt693 _FlexCANC_MB8To63Interrupt
#    if defined (C_CAN_MAX_BUFFER_96)
  #define BrsHwDummyInterrupt694 _FlexCANC_MB64To95Interrupt
#    endif
#   endif
#  endif /*kCanPhysToLogChannelIndex_2*/
#  if defined (kCanPhysToLogChannelIndex_3)
#   if defined (C_ENABLE_CAN_BUSOFF_INTERRUPT)
  #define BrsHwDummyInterrupt695 _FlexCAND_ErrorInterrupt
#   endif
#   if defined (C_ENABLE_CAN_RXTX_INTERRUPT)
  #define BrsHwDummyInterrupt696 BrsHwDummyInterrupt696 /* Unused! */
  #define BrsHwDummyInterrupt697 _FlexCAND_RxFifoInterrupt
  #define BrsHwDummyInterrupt698 _FlexCAND_MB8To63Interrupt
  #define BrsHwDummyInterrupt699 _FlexCAND_MB8To63Interrupt
#    if defined (C_CAN_MAX_BUFFER_96)
  #define BrsHwDummyInterrupt700 _FlexCAND_MB64To95Interrupt
#    endif
#   endif
#  endif /*kCanPhysToLogChannelIndex_3*/
# endif /*VGEN_ENABLE_CAN_DRV*/

  /**********************************************************************************
   *                                      LIN                                       *
   **********************************************************************************/
# if defined (VGEN_ENABLE_LIN_DRV)
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
  #define BrsHwDummyInterrupt376 _LINFLEX_LinIsr_RXI_0  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt377 _LINFLEX_LinIsr_TXI_0  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt378 _LINFLEX_LinIsr_ERR_0  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
  #define BrsHwDummyInterrupt380 _LINFLEX_LinIsr_RXI_1  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt381 _LINFLEX_LinIsr_TXI_1  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt382 _LINFLEX_LinIsr_ERR_1  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_2)
  #define BrsHwDummyInterrupt384 _LINFLEX_LinIsr_RXI_2  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt385 _LINFLEX_LinIsr_TXI_2  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt386 _LINFLEX_LinIsr_ERR_2  /* LINFlex_ERR */
#  endif
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_3)
  #define BrsHwDummyInterrupt432 _LINFLEX_LinIsr_RXI_3  /* LINFlex_RXI */
  #define BrsHwDummyInterrupt433 _LINFLEX_LinIsr_TXI_3  /* LINFlex_TXI */
  #define BrsHwDummyInterrupt434 _LINFLEX_LinIsr_ERR_3  /* LINFlex_ERR */
#  endif
# endif

  /**********************************************************************************
   *                                  Timer                                         *
   **********************************************************************************/
  #define BrsHwDummyInterrupt226 _BrsHwTimeBaseInterrupt
#endif /*BRSHW_INTERRUPT_TABLE_GROUP_G*/

#if defined (VGEN_ENABLE_CAN_DRV)
/* Different versions of the DrvCan use different naming for the ISRs */
/* This wrapper has to fit for ASR+CBD drivers */
# if defined (DRVCAN_IMXFLEXCAN3ASR_VERSION)
  #define DRVCAN_IMXFLEXCAN3HLL_VERSION DRVCAN_IMXFLEXCAN3ASR_VERSION
# endif
# if defined (DRVCAN_IMXFLEXCAN3HLL_VERSION)
#  if (DRVCAN_IMXFLEXCAN3HLL_VERSION >= 0x0200u)
#   if defined (kCanPhysToLogChannelIndex_0)
  #define CanMB0Isr_0 CanMailboxIsr_0
  #define CanMB1Isr_0 CanMailboxIsr_0
  #define CanMB2Isr_0 CanMailboxIsr_0
  #define CanMB3Isr_0 CanMailboxIsr_0
  #define CanMB4Isr_0 CanMailboxIsr_0
  #define CanMB5Isr_0 CanMailboxIsr_0
  #define CanMB6Isr_0 CanMailboxIsr_0
  #define CanMB7Isr_0 CanMailboxIsr_0
  #define CanMB8Isr_0 CanMailboxIsr_0
  #define CanMB9Isr_0 CanMailboxIsr_0
  #define CanMB10Isr_0 CanMailboxIsr_0
  #define CanMB11Isr_0 CanMailboxIsr_0
  #define CanMB12Isr_0 CanMailboxIsr_0
  #define CanMB13Isr_0 CanMailboxIsr_0
  #define CanMB14Isr_0 CanMailboxIsr_0
  #define CanMB15Isr_0 CanMailboxIsr_0
  #define CanMB16To31Isr_0 CanMailboxIsr_0
  #define CanMB32To63Isr_0 CanMailboxIsr_0
  #define CanMB64To95Isr_0 CanMailboxIsr_0
  #define CanMB96To127Isr_0 CanMailboxIsr_0
  #define CanRxFifoIsr_0 CanMailboxIsr_0
  #define CanMB8To63Isr_0 CanMailboxIsr_0
#   endif /*kCanPhysToLogChannelIndex_0*/
#   if defined (kCanPhysToLogChannelIndex_1)
  #define CanMB0Isr_1 CanMailboxIsr_1
  #define CanMB1Isr_1 CanMailboxIsr_1
  #define CanMB2Isr_1 CanMailboxIsr_1
  #define CanMB3Isr_1 CanMailboxIsr_1
  #define CanMB4Isr_1 CanMailboxIsr_1
  #define CanMB5Isr_1 CanMailboxIsr_1
  #define CanMB6Isr_1 CanMailboxIsr_1
  #define CanMB7Isr_1 CanMailboxIsr_1
  #define CanMB8Isr_1 CanMailboxIsr_1
  #define CanMB9Isr_1 CanMailboxIsr_1
  #define CanMB10Isr_1 CanMailboxIsr_1
  #define CanMB11Isr_1 CanMailboxIsr_1
  #define CanMB12Isr_1 CanMailboxIsr_1
  #define CanMB13Isr_1 CanMailboxIsr_1
  #define CanMB14Isr_1 CanMailboxIsr_1
  #define CanMB15Isr_1 CanMailboxIsr_1
  #define CanMB16To31Isr_1 CanMailboxIsr_1
  #define CanMB32To63Isr_1 CanMailboxIsr_1
  #define CanMB64To95Isr_1 CanMailboxIsr_1
  #define CanMB96To127Isr_1 CanMailboxIsr_1
  #define CanRxFifoIsr_1 CanMailboxIsr_1
  #define CanMB8To63Isr_1 CanMailboxIsr_1
#   endif /*kCanPhysToLogChannelIndex_1*/
#   if defined (kCanPhysToLogChannelIndex_2)
  #define CanMB0Isr_2 CanMailboxIsr_2
  #define CanMB1Isr_2 CanMailboxIsr_2
  #define CanMB2Isr_2 CanMailboxIsr_2
  #define CanMB3Isr_2 CanMailboxIsr_2
  #define CanMB4Isr_2 CanMailboxIsr_2
  #define CanMB5Isr_2 CanMailboxIsr_2
  #define CanMB6Isr_2 CanMailboxIsr_2
  #define CanMB7Isr_2 CanMailboxIsr_2
  #define CanMB8Isr_2 CanMailboxIsr_2
  #define CanMB9Isr_2 CanMailboxIsr_2
  #define CanMB10Isr_2 CanMailboxIsr_2
  #define CanMB11Isr_2 CanMailboxIsr_2
  #define CanMB12Isr_2 CanMailboxIsr_2
  #define CanMB13Isr_2 CanMailboxIsr_2
  #define CanMB14Isr_2 CanMailboxIsr_2
  #define CanMB15Isr_2 CanMailboxIsr_2
  #define CanMB16To31Isr_2 CanMailboxIsr_2
  #define CanMB32To63Isr_2 CanMailboxIsr_2
  #define CanMB64To95Isr_2 CanMailboxIsr_2
  #define CanMB96To127Isr_2 CanMailboxIsr_2
  #define CanRxFifoIsr_2 CanMailboxIsr_2
  #define CanMB8To63Isr_2 CanMailboxIsr_2
#   endif /*kCanPhysToLogChannelIndex_2*/
#  endif /*DRVCAN_IMXFLEXCAN3HLL_VERSION >= 0x0200u*/
# endif /*DRVCAN_IMXFLEXCAN3HLL_VERSION*/
#endif /*VGEN_ENABLE_CAN_DRV*/

/******************************************************************************
* Start of interrupt name redefinition for Software Vector Mode (SW dispatching)
******************************************************************************/
 /* Description: The names of the ISR handlers for the Hardware Vector Mode
 *       are different to the ISR handler names of the Software Vector Mode.
 *       Therefore the ISR Handler names are redefined again here! */
#if defined (BRSHW_ENABLE_ISR_SW_DISPATCHING)
  #define _FlexCANA_Interrupt          CanIsr_0
  #define _FlexCANA_ErrorInterrupt     CanBusOffIsr_0
  #define _FlexCANA_MB0Interrupt       CanMB0Isr_0
  #define _FlexCANA_MB1Interrupt       CanMB1Isr_0
  #define _FlexCANA_MB2Interrupt       CanMB2Isr_0
  #define _FlexCANA_MB3Interrupt       CanMB3Isr_0
  #define _FlexCANA_MB4Interrupt       CanMB4Isr_0
  #define _FlexCANA_MB5Interrupt       CanMB5Isr_0
  #define _FlexCANA_MB6Interrupt       CanMB6Isr_0
  #define _FlexCANA_MB7Interrupt       CanMB7Isr_0
  #define _FlexCANA_MB8Interrupt       CanMB8Isr_0
  #define _FlexCANA_MB9Interrupt       CanMB9Isr_0
  #define _FlexCANA_MB10Interrupt      CanMB10Isr_0
  #define _FlexCANA_MB11Interrupt      CanMB11Isr_0
  #define _FlexCANA_MB12Interrupt      CanMB12Isr_0
  #define _FlexCANA_MB13Interrupt      CanMB13Isr_0
  #define _FlexCANA_MB14Interrupt      CanMB14Isr_0
  #define _FlexCANA_MB15Interrupt      CanMB15Isr_0
  #define _FlexCANA_MB0To3Interrupt    CanMB0To3Isr_0
  #define _FlexCANA_MB4To7Interrupt    CanMB4To7Isr_0
  #define _FlexCANA_MB8To11Interrupt   CanMB8To11Isr_0
  #define _FlexCANA_MB12To15Interrupt  CanMB12To15Isr_0
  #define _FlexCANA_MB16To31Interrupt  CanMB16To31Isr_0
  #define _FlexCANA_MB32To63Interrupt  CanMB32To63Isr_0
  #define _FlexCANB_Interrupt          CanIsr_1
  #define _FlexCANB_ErrorInterrupt     CanBusOffIsr_1
  #define _FlexCANB_MB0Interrupt       CanMB0Isr_1
  #define _FlexCANB_MB1Interrupt       CanMB1Isr_1
  #define _FlexCANB_MB2Interrupt       CanMB2Isr_1
  #define _FlexCANB_MB3Interrupt       CanMB3Isr_1
  #define _FlexCANB_MB4Interrupt       CanMB4Isr_1
  #define _FlexCANB_MB5Interrupt       CanMB5Isr_1
  #define _FlexCANB_MB6Interrupt       CanMB6Isr_1
  #define _FlexCANB_MB7Interrupt       CanMB7Isr_1
  #define _FlexCANB_MB8Interrupt       CanMB8Isr_1
  #define _FlexCANB_MB9Interrupt       CanMB9Isr_1
  #define _FlexCANB_MB10Interrupt      CanMB10Isr_1
  #define _FlexCANB_MB11Interrupt      CanMB11Isr_1
  #define _FlexCANB_MB12Interrupt      CanMB12Isr_1
  #define _FlexCANB_MB13Interrupt      CanMB13Isr_1
  #define _FlexCANB_MB14Interrupt      CanMB14Isr_1
  #define _FlexCANB_MB15Interrupt      CanMB15Isr_1
  #define _FlexCANB_MB0To3Interrupt    CanMB0To3Isr_1
  #define _FlexCANB_MB4To7Interrupt    CanMB4To7Isr_1
  #define _FlexCANB_MB8To11Interrupt   CanMB8To11Isr_1
  #define _FlexCANB_MB12To15Interrupt  CanMB12To15Isr_1
  #define _FlexCANB_MB16To31Interrupt  CanMB16To31Isr_1
  #define _FlexCANB_MB32To63Interrupt  CanMB32To63Isr_1
  #define _FlexCANC_Interrupt          CanIsr_2
  #define _FlexCANC_ErrorInterrupt     CanBusOffIsr_2
  #define _FlexCANC_MB0Interrupt       CanMB0Isr_2
  #define _FlexCANC_MB1Interrupt       CanMB1Isr_2
  #define _FlexCANC_MB2Interrupt       CanMB2Isr_2
  #define _FlexCANC_MB3Interrupt       CanMB3Isr_2
  #define _FlexCANC_MB4Interrupt       CanMB4Isr_2
  #define _FlexCANC_MB5Interrupt       CanMB5Isr_2
  #define _FlexCANC_MB6Interrupt       CanMB6Isr_2
  #define _FlexCANC_MB7Interrupt       CanMB7Isr_2
  #define _FlexCANC_MB8Interrupt       CanMB8Isr_2
  #define _FlexCANC_MB9Interrupt       CanMB9Isr_2
  #define _FlexCANC_MB10Interrupt      CanMB10Isr_2
  #define _FlexCANC_MB11Interrupt      CanMB11Isr_2
  #define _FlexCANC_MB12Interrupt      CanMB12Isr_2
  #define _FlexCANC_MB13Interrupt      CanMB13Isr_2
  #define _FlexCANC_MB14Interrupt      CanMB14Isr_2
  #define _FlexCANC_MB15Interrupt      CanMB15Isr_2
  #define _FlexCANC_MB0To3Interrupt    CanMB0To3Isr_2
  #define _FlexCANC_MB4To7Interrupt    CanMB4To7Isr_2
  #define _FlexCANC_MB8To11Interrupt   CanMB8To11Isr_2
  #define _FlexCANC_MB12To15Interrupt  CanMB12To15Isr_2
  #define _FlexCANC_MB16To31Interrupt  CanMB16To31Isr_2
  #define _FlexCANC_MB32To63Interrupt  CanMB32To63Isr_2
  #define _FlexCAND_Interrupt          CanIsr_3
  #define _FlexCAND_ErrorInterrupt     CanBusOffIsr_3
  #define _FlexCAND_MB0Interrupt       CanMB0Isr_3
  #define _FlexCAND_MB1Interrupt       CanMB1Isr_3
  #define _FlexCAND_MB2Interrupt       CanMB2Isr_3
  #define _FlexCAND_MB3Interrupt       CanMB3Isr_3
  #define _FlexCAND_MB4Interrupt       CanMB4Isr_3
  #define _FlexCAND_MB5Interrupt       CanMB5Isr_3
  #define _FlexCAND_MB6Interrupt       CanMB6Isr_3
  #define _FlexCAND_MB7Interrupt       CanMB7Isr_3
  #define _FlexCAND_MB8Interrupt       CanMB8Isr_3
  #define _FlexCAND_MB9Interrupt       CanMB9Isr_3
  #define _FlexCAND_MB10Interrupt      CanMB10Isr_3
  #define _FlexCAND_MB11Interrupt      CanMB11Isr_3
  #define _FlexCAND_MB12Interrupt      CanMB12Isr_3
  #define _FlexCAND_MB13Interrupt      CanMB13Isr_3
  #define _FlexCAND_MB14Interrupt      CanMB14Isr_3
  #define _FlexCAND_MB15Interrupt      CanMB15Isr_3
  #define _FlexCAND_MB0To3Interrupt    CanMB0To3Isr_3
  #define _FlexCAND_MB4To7Interrupt    CanMB4To7Isr_3
  #define _FlexCAND_MB8To11Interrupt   CanMB8To11Isr_3
  #define _FlexCAND_MB12To15Interrupt  CanMB12To15Isr_3
  #define _FlexCAND_MB16To31Interrupt  CanMB16To31Isr_3
  #define _FlexCAND_MB32To63Interrupt  CanMB32To63Isr_3
  #define _FlexCANE_Interrupt          CanIsr_4
  #define _FlexCANE_ErrorInterrupt     CanBusOffIsr_4
  #define _FlexCANE_MB0Interrupt       CanMB0Isr_4
  #define _FlexCANE_MB1Interrupt       CanMB1Isr_4
  #define _FlexCANE_MB2Interrupt       CanMB2Isr_4
  #define _FlexCANE_MB3Interrupt       CanMB3Isr_4
  #define _FlexCANE_MB4Interrupt       CanMB4Isr_4
  #define _FlexCANE_MB5Interrupt       CanMB5Isr_4
  #define _FlexCANE_MB6Interrupt       CanMB6Isr_4
  #define _FlexCANE_MB7Interrupt       CanMB7Isr_4
  #define _FlexCANE_MB8Interrupt       CanMB8Isr_4
  #define _FlexCANE_MB9Interrupt       CanMB9Isr_4
  #define _FlexCANE_MB10Interrupt      CanMB10Isr_4
  #define _FlexCANE_MB11Interrupt      CanMB11Isr_4
  #define _FlexCANE_MB12Interrupt      CanMB12Isr_4
  #define _FlexCANE_MB13Interrupt      CanMB13Isr_4
  #define _FlexCANE_MB14Interrupt      CanMB14Isr_4
  #define _FlexCANE_MB15Interrupt      CanMB15Isr_4
  #define _FlexCANE_MB0To3Interrupt    CanMB0To3Isr_4
  #define _FlexCANE_MB4To7Interrupt    CanMB4To7Isr_4
  #define _FlexCANE_MB8To11Interrupt   CanMB8To11Isr_4
  #define _FlexCANE_MB12To15Interrupt  CanMB12To15Isr_4
  #define _FlexCANE_MB16To31Interrupt  CanMB16To31Isr_4
  #define _FlexCANE_MB32To63Interrupt  CanMB32To63Isr_4
  #define _FlexCANF_Interrupt          CanIsr_5
  #define _FlexCANF_ErrorInterrupt     CanBusOffIsr_5
  #define _FlexCANF_MB0Interrupt       CanMB0Isr_5
  #define _FlexCANF_MB1Interrupt       CanMB1Isr_5
  #define _FlexCANF_MB2Interrupt       CanMB2Isr_5
  #define _FlexCANF_MB3Interrupt       CanMB3Isr_5
  #define _FlexCANF_MB4Interrupt       CanMB4Isr_5
  #define _FlexCANF_MB5Interrupt       CanMB5Isr_5
  #define _FlexCANF_MB6Interrupt       CanMB6Isr_5
  #define _FlexCANF_MB7Interrupt       CanMB7Isr_5
  #define _FlexCANF_MB8Interrupt       CanMB8Isr_5
  #define _FlexCANF_MB9Interrupt       CanMB9Isr_5
  #define _FlexCANF_MB10Interrupt      CanMB10Isr_5
  #define _FlexCANF_MB11Interrupt      CanMB11Isr_5
  #define _FlexCANF_MB12Interrupt      CanMB12Isr_5
  #define _FlexCANF_MB13Interrupt      CanMB13Isr_5
  #define _FlexCANF_MB14Interrupt      CanMB14Isr_5
  #define _FlexCANF_MB15Interrupt      CanMB15Isr_5
  #define _FlexCANF_MB0To3Interrupt    CanMB0To3Isr_5
  #define _FlexCANF_MB4To7Interrupt    CanMB4To7Isr_5
  #define _FlexCANF_MB8To11Interrupt   CanMB8To11Isr_5
  #define _FlexCANF_MB12To15Interrupt  CanMB12To15Isr_5
  #define _FlexCANF_MB16To31Interrupt  CanMB16To31Isr_5
  #define _FlexCANF_MB32To63Interrupt  CanMB32To63Isr_5
  #define _FlexCANG_Interrupt          CanIsr_6
  #define _FlexCANG_ErrorInterrupt     CanBusOffIsr_6
  #define _FlexCANG_MB0Interrupt       CanMB0Isr_6
  #define _FlexCANG_MB1Interrupt       CanMB1Isr_6
  #define _FlexCANG_MB2Interrupt       CanMB2Isr_6
  #define _FlexCANG_MB3Interrupt       CanMB3Isr_6
  #define _FlexCANG_MB4Interrupt       CanMB4Isr_6
  #define _FlexCANG_MB5Interrupt       CanMB5Isr_6
  #define _FlexCANG_MB6Interrupt       CanMB6Isr_6
  #define _FlexCANG_MB7Interrupt       CanMB7Isr_6
  #define _FlexCANG_MB8Interrupt       CanMB8Isr_6
  #define _FlexCANG_MB9Interrupt       CanMB9Isr_6
  #define _FlexCANG_MB10Interrupt      CanMB10Isr_6
  #define _FlexCANG_MB11Interrupt      CanMB11Isr_6
  #define _FlexCANG_MB12Interrupt      CanMB12Isr_6
  #define _FlexCANG_MB13Interrupt      CanMB13Isr_6
  #define _FlexCANG_MB14Interrupt      CanMB14Isr_6
  #define _FlexCANG_MB15Interrupt      CanMB15Isr_6
  #define _FlexCANG_MB0To3Interrupt    CanMB0To3Isr_6
  #define _FlexCANG_MB4To7Interrupt    CanMB4To7Isr_6
  #define _FlexCANG_MB8To11Interrupt   CanMB8To11Isr_6
  #define _FlexCANG_MB12To15Interrupt  CanMB12To15Isr_6
  #define _FlexCANG_MB16To31Interrupt  CanMB16To31Isr_6
  #define _FlexCANG_MB32To63Interrupt  CanMB32To63Isr_6
  #define _TTCAN1_LINE0_Interrupt      CanIsr_0
  #define _MCAN0_LINE0_Interrupt       CanIsr_0
  #define _MCAN1_LINE0_Interrupt       CanIsr_1
  #define _MCAN2_LINE0_Interrupt       CanIsr_2
  #define _MCAN3_LINE0_Interrupt       CanIsr_3
  #define _MCAN4_LINE0_Interrupt       CanIsr_4

  #define _LINSCI_LinIsr_0             LinIsr_0
  #define _LINSCI_LinIsr_1             LinIsr_1
  #define _LINSCI_LinIsr_2             LinIsr_2
  #define _LINFLEX_LinIsr_RXI_0        LinIsr_RXI_0
  #define _LINFLEX_LinIsr_TXI_0        LinIsr_TXI_0
  #define _LINFLEX_LinIsr_ERR_0        LinIsr_ERR_0
  #define _LINFLEX_LinIsr_RXI_1        LinIsr_RXI_1
  #define _LINFLEX_LinIsr_TXI_1        LinIsr_TXI_1
  #define _LINFLEX_LinIsr_ERR_1        LinIsr_ERR_1
  #define _LINFLEX_LinIsr_RXI_2        LinIsr_RXI_2
  #define _LINFLEX_LinIsr_TXI_2        LinIsr_TXI_2
  #define _LINFLEX_LinIsr_ERR_2        LinIsr_ERR_2
  #define _LINFLEX_LinIsr_RXI_3        LinIsr_RXI_3
  #define _LINFLEX_LinIsr_TXI_3        LinIsr_TXI_3
  #define _LINFLEX_LinIsr_ERR_3        LinIsr_ERR_3
  #define _LINFLEX_LinIsr_RXI_4        LinIsr_RXI_4
  #define _LINFLEX_LinIsr_TXI_4        LinIsr_TXI_4
  #define _LINFLEX_LinIsr_ERR_4        LinIsr_ERR_4
  #define _LINFLEX_LinIsr_RXI_5        LinIsr_RXI_5
  #define _LINFLEX_LinIsr_TXI_5        LinIsr_TXI_5
  #define _LINFLEX_LinIsr_ERR_5        LinIsr_ERR_5
  #define _LINFLEX_LinIsr_RXI_6        LinIsr_RXI_6
  #define _LINFLEX_LinIsr_TXI_6        LinIsr_TXI_6
  #define _LINFLEX_LinIsr_ERR_6        LinIsr_ERR_6
  #define _LINFLEX_LinIsr_RXI_7        LinIsr_RXI_7
  #define _LINFLEX_LinIsr_TXI_7        LinIsr_TXI_7
  #define _LINFLEX_LinIsr_ERR_7        LinIsr_ERR_7
  #define _LINFLEX_LinIsr_RXI_8        LinIsr_RXI_8
  #define _LINFLEX_LinIsr_TXI_8        LinIsr_TXI_8
  #define _LINFLEX_LinIsr_ERR_8        LinIsr_ERR_8
  #define _LINFLEX_LinIsr_RXI_9        LinIsr_RXI_9
  #define _LINFLEX_LinIsr_TXI_9        LinIsr_TXI_9
  #define _LINFLEX_LinIsr_ERR_9        LinIsr_ERR_9

  #define _BrsHwFlexRayProtInterrupt   Fr_IrqProtocol

  #define _BrsHwTimeBaseInterrupt      BrsHwTimeBaseInterrupt

  #define _BrsHwWakeUpIsr_0            BrsHwWakeUpIsr_0
  #define _BrsHwWakeUpIsr_1            BrsHwWakeUpIsr_1
  #define _BrsHwWakeUpIsr_2            BrsHwWakeUpIsr_2
  #define _BrsHwWakeUpIsr_3            BrsHwWakeUpIsr_3
  #define _BrsHwWakeUpIsr_4to15        BrsHwWakeUpIsr_4to15
  #define _BrsHwWakeUpIsr_0to7         BrsHwWakeUpIsr_0to7
  #define _BrsHwWakeUpIsr_8to15        BrsHwWakeUpIsr_8to15
#endif /*BRSHW_ENABLE_ISR_SW_DISPATCHING*/

#if defined (C_FLEXCAN_ISR_GROUP_B) || defined (C_FLEXCAN_ISR_GROUP_C)
  #define CanMB0Isr_0       CanMB0To15Isr_0
  #define CanMB1Isr_0       CanMB0To15Isr_0
  #define CanMB2Isr_0       CanMB0To15Isr_0
  #define CanMB3Isr_0       CanMB0To15Isr_0
  #define CanMB4Isr_0       CanMB0To15Isr_0
  #define CanMB5Isr_0       CanMB0To15Isr_0
  #define CanMB6Isr_0       CanMB0To15Isr_0
  #define CanMB7Isr_0       CanMB0To15Isr_0
  #define CanMB8Isr_0       CanMB0To15Isr_0
  #define CanMB9Isr_0       CanMB0To15Isr_0
  #define CanMB10Isr_0      CanMB0To15Isr_0
  #define CanMB11Isr_0      CanMB0To15Isr_0
  #define CanMB12Isr_0      CanMB0To15Isr_0
  #define CanMB13Isr_0      CanMB0To15Isr_0
  #define CanMB14Isr_0      CanMB0To15Isr_0
  #define CanMB15Isr_0      CanMB0To15Isr_0
  #define CanMB0Isr_1       CanMB0To15Isr_1
  #define CanMB1Isr_1       CanMB0To15Isr_1
  #define CanMB2Isr_1       CanMB0To15Isr_1
  #define CanMB3Isr_1       CanMB0To15Isr_1
  #define CanMB4Isr_1       CanMB0To15Isr_1
  #define CanMB5Isr_1       CanMB0To15Isr_1
  #define CanMB6Isr_1       CanMB0To15Isr_1
  #define CanMB7Isr_1       CanMB0To15Isr_1
  #define CanMB8Isr_1       CanMB0To15Isr_1
  #define CanMB9Isr_1       CanMB0To15Isr_1
  #define CanMB10Isr_1      CanMB0To15Isr_1
  #define CanMB11Isr_1      CanMB0To15Isr_1
  #define CanMB12Isr_1      CanMB0To15Isr_1
  #define CanMB13Isr_1      CanMB0To15Isr_1
  #define CanMB14Isr_1      CanMB0To15Isr_1
  #define CanMB15Isr_1      CanMB0To15Isr_1
  #define CanMB0Isr_2       CanMB0To15Isr_2
  #define CanMB1Isr_2       CanMB0To15Isr_2
  #define CanMB2Isr_2       CanMB0To15Isr_2
  #define CanMB3Isr_2       CanMB0To15Isr_2
  #define CanMB4Isr_2       CanMB0To15Isr_2
  #define CanMB5Isr_2       CanMB0To15Isr_2
  #define CanMB6Isr_2       CanMB0To15Isr_2
  #define CanMB7Isr_2       CanMB0To15Isr_2
  #define CanMB8Isr_2       CanMB0To15Isr_2
  #define CanMB9Isr_2       CanMB0To15Isr_2
  #define CanMB10Isr_2      CanMB0To15Isr_2
  #define CanMB11Isr_2      CanMB0To15Isr_2
  #define CanMB12Isr_2      CanMB0To15Isr_2
  #define CanMB13Isr_2      CanMB0To15Isr_2
  #define CanMB14Isr_2      CanMB0To15Isr_2
  #define CanMB15Isr_2      CanMB0To15Isr_2
  #define CanMB0Isr_3       CanMB0To15Isr_3
  #define CanMB1Isr_3       CanMB0To15Isr_3
  #define CanMB2Isr_3       CanMB0To15Isr_3
  #define CanMB3Isr_3       CanMB0To15Isr_3
  #define CanMB4Isr_3       CanMB0To15Isr_3
  #define CanMB5Isr_3       CanMB0To15Isr_3
  #define CanMB6Isr_3       CanMB0To15Isr_3
  #define CanMB7Isr_3       CanMB0To15Isr_3
  #define CanMB8Isr_3       CanMB0To15Isr_3
  #define CanMB9Isr_3       CanMB0To15Isr_3
  #define CanMB10Isr_3      CanMB0To15Isr_3
  #define CanMB11Isr_3      CanMB0To15Isr_3
  #define CanMB12Isr_3      CanMB0To15Isr_3
  #define CanMB13Isr_3      CanMB0To15Isr_3
  #define CanMB14Isr_3      CanMB0To15Isr_3
  #define CanMB15Isr_3      CanMB0To15Isr_3
  #define CanMB0Isr_4       CanMB0To15Isr_4
  #define CanMB1Isr_4       CanMB0To15Isr_4
  #define CanMB2Isr_4       CanMB0To15Isr_4
  #define CanMB3Isr_4       CanMB0To15Isr_4
  #define CanMB4Isr_4       CanMB0To15Isr_4
  #define CanMB5Isr_4       CanMB0To15Isr_4
  #define CanMB6Isr_4       CanMB0To15Isr_4
  #define CanMB7Isr_4       CanMB0To15Isr_4
  #define CanMB8Isr_4       CanMB0To15Isr_4
  #define CanMB9Isr_4       CanMB0To15Isr_4
  #define CanMB10Isr_4      CanMB0To15Isr_4
  #define CanMB11Isr_4      CanMB0To15Isr_4
  #define CanMB12Isr_4      CanMB0To15Isr_4
  #define CanMB13Isr_4      CanMB0To15Isr_4
  #define CanMB14Isr_4      CanMB0To15Isr_4
  #define CanMB15Isr_4      CanMB0To15Isr_4
  #define CanMB0Isr_5       CanMB0To15Isr_5
  #define CanMB1Isr_5       CanMB0To15Isr_5
  #define CanMB2Isr_5       CanMB0To15Isr_5
  #define CanMB3Isr_5       CanMB0To15Isr_5
  #define CanMB4Isr_5       CanMB0To15Isr_5
  #define CanMB5Isr_5       CanMB0To15Isr_5
  #define CanMB6Isr_5       CanMB0To15Isr_5
  #define CanMB7Isr_5       CanMB0To15Isr_5
  #define CanMB8Isr_5       CanMB0To15Isr_5
  #define CanMB9Isr_5       CanMB0To15Isr_5
  #define CanMB10Isr_5      CanMB0To15Isr_5
  #define CanMB11Isr_5      CanMB0To15Isr_5
  #define CanMB12Isr_5      CanMB0To15Isr_5
  #define CanMB13Isr_5      CanMB0To15Isr_5
  #define CanMB14Isr_5      CanMB0To15Isr_5
  #define CanMB15Isr_5      CanMB0To15Isr_5
  #define CanMB0Isr_6       CanMB0To15Isr_6
  #define CanMB1Isr_6       CanMB0To15Isr_6
  #define CanMB2Isr_6       CanMB0To15Isr_6
  #define CanMB3Isr_6       CanMB0To15Isr_6
  #define CanMB4Isr_6       CanMB0To15Isr_6
  #define CanMB5Isr_6       CanMB0To15Isr_6
  #define CanMB6Isr_6       CanMB0To15Isr_6
  #define CanMB7Isr_6       CanMB0To15Isr_6
  #define CanMB8Isr_6       CanMB0To15Isr_6
  #define CanMB9Isr_6       CanMB0To15Isr_6
  #define CanMB10Isr_6      CanMB0To15Isr_6
  #define CanMB11Isr_6      CanMB0To15Isr_6
  #define CanMB12Isr_6      CanMB0To15Isr_6
  #define CanMB13Isr_6      CanMB0To15Isr_6
  #define CanMB14Isr_6      CanMB0To15Isr_6
  #define CanMB15Isr_6      CanMB0To15Isr_6
  #define CanMB0To3Isr_0    CanMB0To15Isr_0
  #define CanMB4To7Isr_0    CanMB0To15Isr_0
  #define CanMB8To11Isr_0   CanMB0To15Isr_0
  #define CanMB12To15Isr_0  CanMB0To15Isr_0
  #define CanMB0To3Isr_1    CanMB0To15Isr_1
  #define CanMB4To7Isr_1    CanMB0To15Isr_1
  #define CanMB8To11Isr_1   CanMB0To15Isr_1
  #define CanMB12To15Isr_1  CanMB0To15Isr_1
  #define CanMB0To3Isr_2    CanMB0To15Isr_2
  #define CanMB4To7Isr_2    CanMB0To15Isr_2
  #define CanMB8To11Isr_2   CanMB0To15Isr_2
  #define CanMB12To15Isr_2  CanMB0To15Isr_2
  #define CanMB0To3Isr_3    CanMB0To15Isr_3
  #define CanMB4To7Isr_3    CanMB0To15Isr_3
  #define CanMB8To11Isr_3   CanMB0To15Isr_3
  #define CanMB12To15Isr_3  CanMB0To15Isr_3
  #define CanMB0To3Isr_4    CanMB0To15Isr_4
  #define CanMB4To7Isr_4    CanMB0To15Isr_4
  #define CanMB8To11Isr_4   CanMB0To15Isr_4
  #define CanMB12To15Isr_4  CanMB0To15Isr_4
  #define CanMB0To3Isr_5    CanMB0To15Isr_5
  #define CanMB4To7Isr_5    CanMB0To15Isr_5
  #define CanMB8To11Isr_5   CanMB0To15Isr_5
  #define CanMB12To15Isr_5  CanMB0To15Isr_5
  #define CanMB0To3Isr_6    CanMB0To15Isr_6
  #define CanMB4To7Isr_6    CanMB0To15Isr_6
  #define CanMB8To11Isr_6   CanMB0To15Isr_6
  #define CanMB12To15Isr_6  CanMB0To15Isr_6
#endif /*C_FLEXCAN_ISR_GROUP_B || C_FLEXCAN_ISR_GROUP_C*/

#endif /*_BRSHW_ISRDEF_H_*/
