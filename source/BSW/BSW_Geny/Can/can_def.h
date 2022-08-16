/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Mpc5500Flexcan2Hll Erzeugungsgangnummer: 1 */

/* STARTSINGLE_OF_MULTIPLE */

#ifndef  CAN_HL_H
# define  CAN_HL_H


/*****************************************************************************
|    Project Name: CAN-DRIVER
|       File Name: CAN_DEF.H
|
|     Description: Application Interface of the CAN Driver
|
|     CPU and Compiler: See Technical Reference of the CAN Driver
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2018 by Vector Informatik GmbH. All rights reserved.
|
| This software is copyright protected and proprietary 
| to Vector Informatik GmbH. Vector Informatik GmbH 
| grants to you only those rights as set out in the 
| license conditions. All other rights remain with 
| Vector Informatik GmbH.
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     ------------------------------------
| Ht           Heike Honert              Vector Informatik GmbH
| Bir          Holger Birke              Vector Informatik GmbH
| Wr           Hans Waaser               Vector Informatik GmbH
| Ard          Thomas Arnold             Vector Informatik GmbH
| Ces          Senol Cendere             Vector Informatik GmbH
| FEV          Frank Voorburg            Vector CANtech, Inc.
| AMN          Ahmad Nasser              Vector CANtech, Inc.
| BWR          Brandon Root              Vector CANtech, Inc.
| TAC          Ty Clark                  Vector CANtech, Inc
| JMD          Jeff Didyk                Vector CANtech, Inc.
| RSE          Robert Schelkle           Vector Informatik GmbH
| Her          Peter Herrmann            Vector Informatik GmbH
| Rli          Roman Linder              Vector Informatik GmbH
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 24-Jan-01  0.02     Ht     derived for C16x V3.3 Template for CAN_LL.H
| 29-Aug-01  0.03     Ht     add comments
| 02-Oct-01  1.00     FEV    customization for MPC5XX-TouCAN
| 18-Dec-01  1.01     FEV    added MEMORY_BIT
| 12-Feb-02  1.02     FEV    only changes in source file
| 10-Jun-02  1.03     FEV    adaption to LI1.3
|                            support for extended id's
| 01-Jul-02  1.03.01  FEV    fixed OSEK OS support
| 29-Jul-02  1.04     AMN    added support to Green Hills Compiler
| 02-Oct-02  1.05     FEV    ESCAN00003869 default C_ENABLE_SLEEP_WAKEUP switch
| 04-Dec-02  1.05.01  FEV    ESCAN00003825 only changes in source file
| 22-Apr-03  1.06     BWR    ESCAN00000438 support for MCORE
|                            ESCAN00005428 only changes in source file
|                            ESCAN00004388 only changes in source file
|                            ESCAN00005712 only changes in source file
|                            ESCAN00005715 Fixed compiler error for
|                            CanRxGetActualIdRawHi macro
|                            ESCAN00005741 only changes in source file
| 08-Jul-03  1.07     BWR    ESCAN00006008 Messages lost due to data corruption issue
| 11-Aug-03  1.08     BWR    ESCAN00006337 Support for MAC710X
|                            ESCAN00005798 only changes in source file
|                            ESCAN00005939 Missing define CanStartFlagWriteSync() and
|                            CanEndFlagWriteSync()
|                            ESCAN00006967 only changes in source file
|                            ESCAN00006968 only changes in source file
|                            ESCAN00007125 Support for basicCAN polling mode
|                            ESCAN00007126 Low Priority extended ID is sent before high
|                            priority standard ID
| 06-Jan-04 1.09      BWR    ESCAN00007883 Add support for the MPC5554
|                     TAC    ESCAN00006338 Add support for the MCORE310
| 17-Nov-04 1.10      BWR    ESCAN00009916 only changes in source file
|                            ESCAN00010207 Naming Conventions
|                            ESCAN00010521 only changes in source file
| 06-Mar-05 1.11      BWR    ESCAN00010593 MB deactivation during bus off prevents arbitration
|                            ESCAN00011054 Buff Off, Error, and Wake Interrupts are not disabled during CanCanInterruptDisable( )
|                            ESCAN00011059 Support for HASH search
|                            ESCAN00011060 Support for multiple basic CAN objects
|                            ESCAN00011074 Sometimes a reception from own transmission is not ignored
|                            ESCAN00011075 CAN Interrupts are restored inside CanInit( ) 
|                            ESCAN00011076 Indication function is called twice for the reception of one CAN message
| 11-Jun-05 1.12      BWR    ESCAN00011694 Reduce basic CAN receive buffer lock time
|                            ESCAN00012505 Support for single CAN interrupt API
|                            ESCAN00012506 ISR routine split in two parts
|                            ESCAN00012676 only changes in source file
|                     Wr     ESCAN00013041 Support for Individual Polling Mode
|                            ESCAN00013297 Undefined behaviour when calling CanTxWriteActId, CanTxWriteActExtId or CanTxWriteActDLC macros
|                            ESCAN00013565 Adapt tCanMsgTransmitStruct
|                            ESCAN00014116 Automatic version scan comment corrected
| 03-Jan-06 1.12.01   Wr     No changes here. See can_drv.c
| 08-Mar-06 1.13      Wr     ESCAN00016689 Renamed CanLL_CopyToCan(dst, src, len) and CAnLL_CopyFromCan(dst, src, len)
|                            ESCAN00016688 Modified CanLL_SetTxDlc, CanLL_SetTxId and CanLL_TxSetIdType
|                            ESCAN00015030 FullCAN message is received incorrectly. Modified Rx handle adjustment.
|                            ESCAN00016670 Compiler error due to missing array canPollingTaskActive[ ] 
|                            ESCAN00015687 Inconsistency in ISR Split mode 
|                            ESCAN00016934 Modified return value of CanStop for loop abortion
| 21-Aug-06 1.14     BWR     ESCAN00017044 Add support for compiler Gaio
|                            ESCAN00017077 Extended IDs not received in muliple basic CAN mode
|                            ESCAN00017078 Use one common ISR function
|                            ESCAN00017228 Remove MISRA Warnings
|                            ESCAN00017345 Support feature to disable reception of self transmission
| 11-Nov-06 1.15     BWR     ESCAN00018343 Compiler error when -VLE option is used
| 02-Mar-07 1.16     BWR     ESCAN00019820 Resource Category Comments
| 09-Oct-07 1.17     BWR     ESCAN00021488 Out of bounds memory access in transmit confirmation
|                            ESCAN00022637 Missing definition of CanRxIdType[ ] in mixed ID mode
|                            ESCAN00022694 Resource Category incorrect for CanTxIdentityAssignment
| 24-Oct-07 1.18     Ces     ESCAN00022928 Support compiler Green Hills MULTI
|                            ESCAN00023383 Disable global interrupts during storing of receive messages
| 24-May-06 2.00      JMD    ESCAN00016485 Support of additional platform Mpc5500
|                     BWR    ESCAN00016486 Support of RI 1.5 features
| 02-Apr-07 2.01      BWR    ESCAN00018602 Support for MCORE34x
| 20-Jun-07 2.02      BWR    ESCAN00021026 FullCAN receive frame lost in polling mode
|                            ESCAN00021111 Out of bounds memory access in transmit confirmation
| 02-Jul-07 2.03      BWR    ESCAN00020164 Support for Coldfire
| 20-Nov-07 2.04      Ces    ESCAN00017168 ECU will not wakeup after entering sleep mode
|                            ESCAN00023425 Received messages have inconsistent ID, DLC or data.
|                            ESCAN00023384 Support AUTOSAR 2.1
| 27-Dec-07 2.05      BWR    ESCAN00017451 Return value of CanStop is kCanOk when the loop has been aborted
|                            ESCAN00022458 CanInterrupt( ) channel index handling for Multi ECU Config 
|                            ESCAN00023472 parameter of functions CanMsgTransmitSet... has to be pointer not struct
|                            ESCAN00023772 Support for Mpc5500(Flexcan) and Mpc5500(Flexcan2) platforms
|                            ESCAN00023797 Support for Common CAN
|                            ESCAN00023802 Errata 5164 FlexCAN: Freeze FlexCAN A to write RXIMR for FlexCAN C
|                            ESCAN00023803 Support for Greenhills compiler
|                            ESCAN00023897 Support for multiple interrupt API
|                            ESCAN00023896 Filtering reception of self sent frames improved
| 04-Feb-08 2.06      Ces    ESCAN00024363 Corrections for filtering of self sent frames
|                            ESCAN00024365 Support transmit bit queue
|                            ESCAN00024366 Support extended IDs for Autosar 2.1
|                     BWR    ESCAN00024485 Clear Interrupt Mask bit for unused CAN objects
| 20-Feb-08 2.07      Ces    ESCAN00024784 Changed workaround implementation for errata 5164
| 13-Mar-08 2.08      Ces    ESCAN00025346 Fixed configurations without SINGLE ISR API
| 04-Apr-08 2.09      Ces    ESCAN00025699 Support Low Level Message Transmit
| 14-Apr-08 2.10      Ces    ESCAN00026054 Support AUTOSAR 3.0
|                     Ces    ESCAN00027149 Support MCF52xx (ColdFire) with gentool GENy
| 04-Jul-08 2.11      Ces    ESCAN00028114 Interrupts are not enabled for some FullCAN receive objects
| 11-Jul-08 2.12      Ces    ESCAN00028334 Support highend features: Multiple BasicCAN, Rx queue and Individual polling
|                            ESCAN00028462 Redesign of ISRs and tasks for Rx and Tx handling
| 11-Aug-08 2.13      Ces    ESCAN00029155 Support MPC560xB and MPC560xC for CANbedded
|                            ESCAN00029665 Support Cancel in Hardware for MPC551x and MPC560x
|                            ESCAN00029666 Support Sleep and WakeUp for MPC560x
| 10-Sep-08 2.14      Ces    ESCAN00029156 Support MPC560xB and MPC560xC for Autosar
| 11-Nov-08 2.15      Ces    ESCAN00031364 Support IMX35 with Flexcan2
| 20-Feb-09 2.16      Ces    ESCAN00033283 MICROSAR: support individual polling and message frame rejection
|                            ESCAN00033288 Improve message frame rejection
|                            ESCAN00033683 Support organi filtering on CPU type little endian and big endian
|                            ESCAN00033684 Removed feature ISR split 
| 16-Mar-09 2.17      Ces    ESCAN00034120 Support IMX25 with Flexcan2 for MICROSAR
|                            ESCAN00034121 Provide mode switch into powerdown DOZE mode in function CanSleep()
|                            ESCAN00034122 Fixed start index of BasicCAN message objects in function CanMB32To63Interrupt
| 26-Mar-09 2.18      Ces    ESCAN00029893 Fixed wrong return values of low level function CanLL_CanSleep
|                            ESCAN00029894 Fixed CanLL_WakeupHandling not called if SINGLE ISR API is used
|                            ESCAN00030831 Fixed compiler error in function CanInterrupt if SINGLE ISR API is used
|                            ESCAN00034687 Fixed wrong base address generated by GENy for platform MAC7100
|                            ESCAN00035373 Support MPC5533 and MPC5534 with FlexCAN2
|                                          Support MPC5605, MPC5606 and MPC5607 with FlexCAN2
|                            ESCAN00035451 CanMsgTransmitSetStdId and CanMsgTransmitSetExtId do return the wrong ID
|                            ESCAN00035452 Extended ID macros do return the wrong ID
|                            ESCAN00035810 Fixed compiler error in function CanMB0To15Interrupt
| 01-Jun-09 2.19      Ces    ESCAN00035431 Support MCU group PC57170x with FlexCAN2
| 06-Jul-09 2.20      Ces    ESCAN00036169 Support MCU group MPC56xx with 32 and 64 mailbox selection
| 20-Jul-09 2.21      Ces    ESCAN00036219 Support compiler Freescale/Metrowerks CodeWarrior
| 2009-09-23  2.22.00  Ces   ESCAN00038620 MICROSAR: FullCAN receive objects stop index is calculated wrong
|                            ESCAN00038857 MICROSAR: Support compiler and memory abstraction
|                            ESCAN00038933 Improve receive and transmit handling in interrupt and polling mode
| 2009-11-26  2.23.00  Ces   ESCAN00039419 Support platform DSP56F8300
|                            ESCAN00039420 Support CommonCAN on platform DSP56F8300
| 2010-04-28  2.24.00  Ces   ESCAN00040029 Support Extended RAM check
|                            ESCAN00040856 Use FlexCAN ISR grouping for derivative configuration
|                            ESCAN00042598 Support compiler GNU
| 2010-07-09  2.25.00  Ces   ESCAN00043337 FullCAN messages are not received
|                            ESCAN00043341 Messages received in BasicCAN are indicated as FullCAN message
|                            ESCAN00043867 Do not lock global interrupts during CanLL_Stop, CanLL_Start and CanLL_Sleep
|                            ESCAN00043868 Support Multiple BasicCAN link time and post build configuration variant
|                            ESCAN00043925 Support platform IMX53 with Flexcan2
|                            ESCAN00044409 Support RxFIFO (only on platforms with Flexcan2)
| 2010-08-06  2.26.00  Ces   ESCAN00044532 Support Flexcan2 without individual receive masks
| 2010-09-27  2.27.00  Ces   ESCAN00045544 Support selectable BusOff recovery variant
|                            ESCAN00045728 Support CAN message retransmit feature for FBL driver
|                            ESCAN00046770 Support MPC5604D and SPC560D4 without individual receive mask registers
|                            ESCAN00045801 MICROSAR only: Compiler warning: "CanLL_WakeUpHandling" was declared but never referenced
| 2010-12-23  2.28.00  Rse   ESCAN00047773 Prevent Compiler warnings of unused variables iMask, index and iFlag
|                            ESCAN00047743 Only one transmission occurs and interrupt fires continuously
| 2011-01-18  2.29.00  Ces   ESCAN00047008 AUTOSAR only: Compiler reports warning or error because C_SECURITY_LEVEL is not defined
|                            ESCAN00047771 Disable FlexCAN before clock source selection according to hardware reference manual
|                            ESCAN00048134 CANbedded only: Compiler warnings due to CAN_ONE_CONTROLLER_OPTIMIZATION and STD_ON
| 2011-02-15  2.30.00  Rse   ESCAN00044745 AUTOSAR only: BasicCAN messages are not received in postbuild configurations
|                            ESCAN00048408 Baudrate settings are invalid after reinitialization, error frames occur continuously on the bus
|                            ESCAN00048435 FullCAN messages are not received after switch from STOP to START mode
|                            ESCAN00048752 MICROSAR only: Message ID 0x0 is sent to the bus instead of the origin FullCAN transmit message ID  
| 2011-03-09  2.31.00  Ces   ESCAN00048199 FullCAN messages are not correctly initialized and processed on MPC5604D
|                            ESCAN00048284 CANbedded only: Compiler reports warning because locRxHandle is set but never used
|                            ESCAN00049275 BasicCAN messages are not received after change to STOP and back to START mode
|                            ESCAN00049276 FullCAN messages are not received after change to STOP and back to START mode
|                            ESCAN00049340 The transmit task uses canTxIntMaskLo[] instead of canTxPollingMaskLo[]
|                            ESCAN00046511 MICROSAR only: Compiler reports error: "undefined identifier canTxIntMaskLo"
|                            ESCAN00049629 Platform specific selection of derivative features
| 2011-03-30  2.32.00  Rse   ESCAN00049653 Errata e4019PS: Wake-up interrupt may be generated without any recessive to dominant transition
|                            ESCAN00049636 Changed unlock of FullCAN and BasicCAN receive message buffers
|                            ESCAN00049671 Wakeup mask bit is not set during CAN initialization
|                            ESCAN00050034 Support compiler GAIO for FlexCAN2
| 2011-05-06  2.33.00  Rse   ESCAN00050721 MICROSAR only: Duplicated code segment is removed due to core update
| 2011-05-09  2.34.00  Rse   ESCAN00050784 FlexCAN1 only: Messages with extended ID pass the acceptance filter of BasicCANs that should be filtered out
| 2011-05-09  2.34.01  Rse   ESCAN00051020 Mixed MBs only: CPU throws interrupt because incorrect R/W access is done
| 2011-07-05  2.35.00  Rse   - Update HL-CBD 2.13.00 to support error-free CanRetransmit for FBL driver
| 2011-07-05  2.36.00  Rse   - Update HL-ASR 3.13.00 to support partial network (R12)
| 2011-09-13  2.37.00  Rse   ESCAN00053623 Support virtual addressing
| 2011-09-26  2.38.00  Rse   ESCAN00053861 Support access to CAN register in user mode
| 2011-10-20  2.39.00  Rse   ESCAN00053717 CAN Controller is not initialized into operational state
|                            - Some code corrections done which belongs to Support MCore341S Flexcan2 with gentool GENy (54294)
| 2011-11-25  2.40.00  Rse   ESCAN00054294 Support MCore341S Flexcan2 with gentool GENy
| 2011-12-28  2.41.00  Rse   ESCAN00055781 Support context switch (QNX) and QCC compiler for IMX
| 2012-03-20  2.41.01  Rse   ESCAN00057574 MICROSAR and MPC5602D only: FullCAN messages are not received due to wrong interrupt mask settings
|                            ESCAN00057678 MultiBasicCAN = 0 only: Compiler reports "the size of an array must be greater than zero"
| 2012-04-11  2.41.02  Rse   ESCAN00058250 MICROSAR and MPC5602D only: Compile error due to defective preprocessor directive
| 2012-03-21  3.00.00  Rse   ESCAN00056830 CANbedded only: Oscilloscope detects "form error" of transmitted frames due to dominant SRR bit in Extended Id messages
|                            ESCAN00057824 CANbedded only: Compile error: "pFlexCANLocal undeclared (first use in this function)"
|                            ESCAN00058602 Memory Protection Error while CAN initialization
|                            ESCAN00058438 Errata 5164 / e1964: Incorrect message data received
|                            ESCAN00058961 AutoSar only: Can_SetControllerMode(controller, CAN_T_STOP) returns CAN_OK instead of CAN_NOT_OK
|                            ESCAN00059171 Support MSR3 R14
|                            ESCAN00059598 CANbedded only: Compiler warning: missing prototype of function ApplCanCorruptRegisters
| 2012-07-18  3.01.00  Rse   ESCAN00060184 LL reworking: Diverse improvements for better runtime or simpler code
|                            ESCAN00060185 LL reworking: Interrupt and Polling masks should be generated
| 2012-10-19  3.01.01  Rse   - Update HL-ASR 4.03.01 for issue 61352 to prevent endless loop in ASR4.0 when ASR OS is used
| 2012-11-21  3.01.02  Rse   ESCAN00063199 MICROSAR only: infinite loop in Wakeup transition
| 2012-10-26  3.02.00  Rse   ESCAN00062034 MICROSAR and MPC5602D only: Det_ReportError kCanInvalidHwObjHandle or CAN_E_PARAM_HANDLE
|                            ESCAN00062237 MPC5602D only: Undesired CAN message is received and indicated to upper layer
|                            ESCAN00062263 MPC5602D only: FullCAN message is not received
|                            ESCAN00060564 AR3-2445: Perform SilentBSW module analysis for critical code parts
|                            ESCAN00063790 LL reworking: Improve mailbox initialization
| 2013-01-03  3.03.00  Rse   ESCAN00063900 CANbedded only: Support Common CAN for MPC5500 platform
| 2013-03-06  3.03.01  Rse   ESCAN00064571 CANbedded only: CAN messages will not be sent any more
| 2013-06-03  3.03.02  Rse   ESCAN00067362 CANbedded only: Compiler error: identifier "canCanInterruptCounter" is undefined
| 2013-06-12  3.03.03  Rse   - Update Kon-File of kernelbuilder to support ISRs for eight physical channels
| 2013-06-25  3.03.04  Rse   ESCAN00032346 BusOff notification is called twice for one single BusOff event
| 2014-05-07  3.03.05  Rse   ESCAN00075438 Corrupt mailbox is not deactivated
|                            ESCAN00075600 Mailbox RAM check is not suppressed
|                            ESCAN00075599 CAN Controller is active although register check fails
| 2014-05-19  3.03.06  Rse   ESCAN00075753 No messages are received when channel is enabled by CanEnableChannelCommunication API
| 2014-09-11  3.03.07  Her   ESCAN00078122 Extended ID message with dominant SRR-Bit is not received via BasicCAN
| 2014-10-14  3.03.08  Rse   ESCAN00076636 CAN clock settings are invalid after reinitialization, error frames occur continuously on the bus
| 2014-11-12  3.03.09  Rse   ESCAN00075454 Support new interface for Bus Mirroring
| 2015-03-05  3.03.10  Rse   ESCAN00081598 MPC5602D only: FullCAN message with Standard ID 0x400 or Extended ID 0x10000000 does not receive
| 2018-05-15  3.03.11  Rli   ESCAN00099410 Add support for Delayed Transmission of FullCAN for FlexCAN2
|***************************************************************************/
/* ***************************************************************************
|
|    ************    Version and change information of      **********        
|    ************    high level part only                   **********        
|
|    Please find the version number of the whole module in the previous 
|    File header.
|
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     ------------------------------------
| Ht           Heike Honert              Vector Informatik GmbH
| Pl           Georg Pfluegel            Vector Informatik GmbH
| Vg           Frank Voorburg            Vector CANtech, Inc.
| An           Ahmad Nasser              Vector CANtech, Inc.
| Ml           Patrick Markl             Vector Informatik GmbH
| Seu          Eugen Stripling           Vector Informatik GmbH
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------ -----------------------------------------------------
| ---------  ---  ------ -- --------------------------------------------------
| 24-Jan-01  0.02      Ht     - derived from C16x V3.3
| 18-Apr-01  1.00      Pl     - adaption for ARM7 TDMI
| 26-Apr-01  1.01      Ht     - adaption to LI 1.2
|                             - changed from code doupling to indexed
| 19-Jun-01            Ht     - define of CanSetActive/Passive changed
| 31-Oct-01  1.02      Ht     - support hash search
|                      Vg     - adaption for PowerPC
| 07-Nov-01  1.03      Ht     - remove some comments
| 12-Nov-01  1.04      Fz     - no changes
| 02-Jan-02  1.05      Ht     - ESCAN00002009: support of polling mode improved
| 12-Feb-02  1.06      Pl     - ESCAN00002279: - now it is possible to use only the error-task without the tx-task
|                                              - support of the makro  REENTRANT
|                                              - support of the makro C_HL_ENABLE_RX_INFO_STRUCT_PTR
|                                              - For better performance for the T89C51C there is a switch-case
|                                                instruction for direct call of the PreTransmitfunction
|                                              - insert Prototyp for CanErrorTask
| 18-Mai-02  1.07       Ht    - support Hash search with FullCAN controller
|                             - ESCAN00002707: Reception could went wrong if IL and Hash Search
|                             - ESCAN00002893: adaption to LI 1.3
| 29-Mai-02  1.08       Ht    - ESCAN00003028: Transmission could fail in Polling mode
|                             - ESCAN00003082: call Can_LL_TxEnd() in CanMsgTransmit()
|                             - ESCAN00003083: Hash search with extended ID
|                             - ESCAN00003084: Support C_COMP_METROWERKS_PPC
|                             - ESCAN00002164: Temporary vaiable "i" not defined in function CanBasicCanMsgReceived
|                             - ESCAN00003085: support C_HL_ENABLE_IDTYPE_IN_ID
| 25-Jun     1.08.01    Vg    - Declared localInterruptOldFlag in CanRxTask()
|                             - Corrected call to CanWakeUp for multichannel
| 11-Jul-02  1.08.02    Ht    - ESCAN00003203: Hash Search routine does not work will with extended IDs
|                             - ESCAN00003205: Support of ranges could went wrong on some platforms
| 08-Aug-02  1.08.03    Ht    - ESCAN00003447: Transmission without databuffer and pretransmit-function 
| 08-Aug-02  1.08.04    An      no changes
| 09-Sep-02  1.09       Ht    - ESCAN00003837: code optimication with KernelBuilder 
| 2002-12-12 1.10       Ht    -                support Dummy functions for indirect function call 
| 2003-02-04 1.11       Ht    -                optimization for polling mode
|                       Fz    - ESCAN00004600: Flags changed for V850 aFCAN only
| 2003-03-19 1.12       Ht    - ESCAN00005153: Wrong number of Indication bytes for V850 aFCAN only
|                             - ESCAN00005152: optimization of CanInit() in case of Direct Tx Objects
|                             - ESCAN00005143: CompilerWarning about function prototype 
|                                              CanHL_ReceivedRxHandle() and CanHL_IndRxHandle
|                             - ESCAN00005130: Wrong result of Heash Search on second or higher channel               
| 2003-05-12 1.13       Ht    - ESCAN00005624: support CantxMsgDestroyed for multichannel system
|                             - ESCAN00005209: Support confirmation and indication flags for EasyCAN4
|                             - ESCAN00004721: Change data type of Handle in CanRxInfoStruct
| 2003-06-18 1.20       Ht    - ESCAN00005908: support features of RI1.4
|                             - Support FJ16LX-Workaround for multichannel system
|                             - ESCAN00005671: Dynamic ID in extended ID system could fail
|                             - ESCAN00005863: Notification about cancelation failes in case of CanTxMsgDestroyed
| 2003-06-30 1.21       Ht   - ESCAN00006117: Common Confirmation Function: Write access to wrong memory location
|                            - ESCAN00006008: CanCanInterruptDisable in case of polling
|                            - ESCAN00006118: Optimization for Mixed ID and ID type in Own Register or ID type in ID Register
|                            - ESCAN00006063: Undesirable hardware dependency for 
|                                             CAN_HL (CanLL_RxBasicTxIdReceived)
| 2003-09-10 1.22       Ht   - ESCAN00006853: Support V_MEMROM0
|                            - ESCAN00006854: suppress some Compiler warnings
|                            - ESCAN00006856: support CanTask if only Wakeup in polling mode
|                            - ESCAN00006857: variable newDLC not defined in case of Variable DataLen
| 2003-10-14 1.23       Ht   - ESCAN00006858: support BrsTime for internal runtime measurement
|                            - ESCAN00006860: support Conditional Msg Receive
|                            - ESCAN00006865: support "Cancel in HW" with CanTask
|                            - ESCAN00006866: support Direct Tx Objects
|                            - ESCAN00007109: support new memory qualifier for const data and pointer to const
| 2004-01-05 1.24       Ml   - ESCAN00007206: no changes
|                       Ml   - ESCAN00007254: several changes
| 2004-02-06 1.25       Ml   - ESCAN00007281: no changes
|                       Ml   - removed compiler warnings
| 2004-02-21 1.26       Ml   - ESCAN00007670: CAN RAM check
|                       Ml   - ESCAN00007671: no changes
|                       Ml   - ESCAN00007764: no changes
|                       Ml   - ESCAN00007681: no changes
|                       Ml   - ESCAN00007272: no changes
|                       Ml   - ESCAN00008064: encapsulated CanRxHashId in case of array dimension == 0
| 2004-04-16 1.27       Ml   - ESCAN00008204: Optimized CanRxActualId for different ID modes
|                       Ml   - ESCAN00008160: encapsulated functions declared by tool in case of multichannel
|                       Ml   - ESCAN00008266: changed name of parameter of function CanTxGetActHandle
|                       Fz   - ESCAN00008272: Compiler error due to missing array canPollingTaskActive
| 2004-05-10 1.28       Fz   - ESCAN00008328: Compiler error if cancel in hardware is active
|                            - ESCAN00008363: Hole closed when TX in interrupt and cancel in HW is used
|                            - ESCAN00008365: Switch C_ENABLE_APPLCANPREWAKEUP_FCT added
|                            - ESCAN00008391: Wrong parameter macro used in call of 
|                                             CanLL_WakeUpHandling
| 2004-05-24 1.29       Ht   - ESCAN00008441: Interrupt not restored in case of internal error if TX Polling is used
| 2004-09-21 1.30       Ht   - ESCAN00008824: check of reference implementation version added
|                            - ESCAN00008825: No call of ApplCanMsgCancelNotification during CanInit()
|                            - ESCAN00008826: Support asssertions for "Conditional Message Received"  
|                       Ml   - ESCAN00008752: Added function qualifier macros
|                       Ht   - ESCAN00008823: compiler error due to array size 0
|                            - ESCAN00008977: label without instructions
|                            - ESCAN00009485: Message via Normal Tx Object will not be sent  
|                            - ESCAN00009497: support of CommonCAN and RX queue added
| 2004-09-28 1.31       Ht   - ESCAN00009703: unresolved functions CAN_POLLING_IRQ_DISABLE/RESTORE()
| 2004-11-25 1.32       Ht   - move fix for ESCAN00007671 to CAN-LL of DrvCan_MpcToucanHll
|                            - ESCAN00010350: Dynamic Tx messages are send always with Std. ID
|                            - ESCAN00010388: ApplCanMsgConfirmed will only be called if realy transmitted
|                       Ml   - ESCAN00009931: The HardwareLoopCheck should have a channelparameter in multichannel systems.
|                            - ESCAN00010093: lint warning: function type inconsistent "CanCheckMemory"
|                        Ht  - ESCAN00010811: remove Misra and compiler warnings
|                            - ESCAN00010812: support Multi ECU
|                            - ESCAN00010526: CAN interrupts will be disabled accidently
|                            - ESCAN00010584: ECU may crash or behave strange with Rx queue active
| 2005-01-20 1.33       Ht   - ESCAN00010877: ApplCanMsgTransmitConf() is called erronemous
| 2005-03-03 1.34       Ht   - ESCAN00011139: Improvement/Correction of C_ENABLE_MULTI_ECU_CONFIG
|                            - ESCAN00011511: avoid PC-Lint warnings
|                            - ESCAN00011512: copy DLC in case of variable Rx Datalen
|                            - ESCAN00010847: warning due to missing brakets in can_par.c at CanChannelObject
| 2005-05-23 1.35       Ht   - ESCAN00012445: compiler error "V_MEMROMO undefined"in case of multi ECU
|                            - ESCAN00012350: Compiler Error "Illegal token channel"
| 2005-07-06 1.36       Ht   - ESCAN00012153: Compile Error: missing declaration of variable i
|                            - ESCAN00012460: Confirmation of LowLevel message will run into assertion (C_ENABLE_MULTI_ECU_PHYS enabled)
|                            - support Testpoints for CanTestKit
| 2005-07-14 1.37       Ht   - ESCAN00012892: compile error due to missing logTxObjHandle
|                            - ESCAN00012998: Compile Error: missing declaration of txHandle in CanInit()
|                            - support Testpoints for CanTestKit for FullCAN controller
| 2005-10-05 1.38       Ht   - ESCAN00013597: Linker error: Undefined symbol 'CanHL_IndRxHandle'
| 2005-11-10 1.39.00    Ht   - ESCAN00014331: Compile error due to missing 'else' in function CanTransmit
| 2005-04-26 2.00.00    Ht   - ESCAN00016698: support RI1.5
|                            - ESCAN00014770: Cosmic compiler reports truncating assignement
|                            - ESCAN00016191: Compiler warning about unused variable in CanTxTask
| 2007-01-23 2.01.00    Ht   - ESCAN00017279: Usage of SingleGlobalInterruptDisable lead to assertion in OSEK
|                            - ESCAN00017148: Compile error in higher layer due to missing declaration of CanTxMsgHandleToChannel
| 2007-03-14 2.02.00   Ht    - ESCAN00019825: error directives added and misra changes
|                            - ESCAN00019827: adaption to never version of VStdLib.
|                            - ESCAN00019619: V_CALLBACK_1 and V_CALLBACK_2 not defined
|                            - ESCAN00019953: Handling of FullCAN reception in interrupt instead of polling or vice versa.
|                            - ESCAN00019958: CanDynTxObjSetId() or CanDynTxObjSetExtId() will run into assertion
| 2007-03-26 2.03.00  Ht     - ESCAN00019988: Compile warnings in can_drv.c
|                            - ESCAN00018831: polling mode: function prototype without function implemenation (CanRxFullCANTask + CanRxBasicCANTask)
| 2007-04-20 2.04.00  dH     - ESCAN00020299: user assertion fired irregularly due to unknown parameter (in case of CommonCAN)
| 2007-05-02 2.05.00  Ht     - ESCAN00021069: Handling of canStatus improved, usage of preprocessor defines unified
|                            - ESCAN00021070: support relocation of HW objects in case of Multiple configuration
|                            - ESCAN00021166: Compiler Warnings: canHwChannel & canReturnCode not used in CanGetStatus
|                            - ESCAN00021223: CanCanInterruptDisabled called during Sleepmode in CanWakeupTask
|                            - ESCAN00022048: Parameter of ApplCancorruptMailbox is hardware channel instead of logical channel - Error directive added
| 2007-11-12 2.06.00  Ht     - ESCAN00023188: support CAN Controller specific polling sequence for BasicCAN objects
|                            - ESCAN00023208: Compile issue about undefined variable kCanTxQueuePadBits in the CAN driver in Bit based Tx queue
| 2008-10-20 2.07.00  Ht     - ESCAN00023010: support disabled mailboxes in case of extended RAM check
|                            - ESCAN00025706: provide C_SUPPORTS_MULTI_ECU_PHYS
|                            - ESCAN00026120: compiler warnings found on DrvCan_V85xAfcanHll RI 1.5     ##Ht: reviewed 2008-09-03
|                            - ESCAN00026322: ApplCanMsgNotMatched not called in special configuration
|                            - ESCAN00026413: Add possibility to reject remote frames received by FullCAN message objects
|                            - ESCAN00028758: CAN HL must support QNX
|                            - ESCAN00029788: CommonCAN for Driver which support only one Tx object improved (CanInit()).
|                            - ESCAN00029889: Compiler warning about uninitialized variable canHwChannel in CanCanInterruptDisable/Restore()
|                            - ESCAN00029891: Compiler warning: variable "rxHandle" was set but never used
|                            - ESCAN00029929: Support Extended ID Masking for Tx Fullcan messages 
|                            - ESCAN00030371: Improvements (assertions, misra)
|                            - ESCAN00027931: Wrong check of "queueBitPos" size
| 2009-04-08 2.08.00  Ht     - ESCAN00034492: no automatic remove of CanCanInterruptDisable/Restore
|                            - ESCAN00031816: CANRANGExIDTYPE can be removed and direct expression used
|                            - ESCAN00032027: CanMsgTransmit shall support tCanMsgTransmitStruct pointer accesses to far RAM
|                            - ESCAN00034488: Postfix for unsigned const in perprocessor directives are not supported by all Compiler (ARM-Compiler 1.2)
| 2009-06-04 2.08.01  Ht     - ESCAN00035426: Compiler warning about truncation in CanGetStatus removed
| 2009-10-21 2.09.00  Ht     - ESCAN00036258: Compiler warning about "CanHL_ReceivedRxHandle" was declared but never referenced
|                            - ESCAN00038642: Support reentrant functions for compiler with own keyword
|                            - ESCAN00038645: support new switch C_ENABLE_UPDATE_BASE_ADDRESS
| 2010-02-01 2.10.00  Ht     - ESCAN00036260: Support configuartion without static Tx messages and only one channel (remove compiler warning)
|                            - ESCAN00040478: Handle update of virtual CanBaseAdress in accordance to QNX documentation
|                            - ESCAN00039235: Compiler Warning: Narrowing or Signed-to-Unsigned type conversion
| 2010-07-22 2.11.00  Ht     - ESCAN00044221: support Retransmit functionality for FBL
|                            - ESCAN00044222: internal changes: improve readability and
|                                             change CAN_CAN_INTERRUPT_... macros to avoid preprocessor errors for some compiler
|                            - ESCAN00044174: TxBitQueue only - compiler warning occurs about: condition is always true
| 2010-10-22 2.12.00  Ht - ESCAN00046326: support  C_COMP_KEIL_XC800 and  C_COMP_TI_TMS320
| 2011-05-17 2.13.00  Ht - ESCAN00048965: Add assertion check txMsgStruct for NULL-Pointer value in CanMsgTransmit() API
|                        - ESCAN00050948: support retransmit macro if kCanHwTxStartIndex != 0.
| 2012-04-23 2.14.00  Ht - ESCAN00053779: Linker error: CanBaseAddressRequest() and CanBaseAddressActivate() are not available
|                        - ESCAN00056617: remove brackets in macro CanInterruptDisable/Restore()
|                        - ESCAN00058520: support CommonCAN in combination with RAM check
|                        - ESCAN00058521: support C_COMP_KEIL_SLC8051_CCAN
|                        - ESCAN00058522: some  message will be not be received via BasicCAN if index search and multichannel are active
|                        - ESCAN00058104: compiler warning occurs about: comparison between signed and unsigned
| 2012-04-23 2.14.01  Ht - ESCAN00058636: some BasicCAN messages will not be received with linear search
| 2012-05-11 2.15.00  Seu - ESCAN00058891: Add switch C_HL_ENABLE_PRETRANSMIT_SWITCH_COMMENT
| 2012-07-02 2.15.01  Ht  - ESCAN00058586: Compiler warning: comparison is always true due to limited range of data type
|                         - ESCAN00059562: Compile error: Size of array CanRxMsgIndirection is zero if index search and no Rx FullCANs are used
|                         - ESCAN00059736: Compiler warning: pointless comparison of unsigned integer with zero
| 2012-10-30 2.15.02  Ht  - ESCAN00061829: Compiler error:  about(CAN_HL_HW_RX_BASIC/FULL_STARTINDEX(canHwChannel) == 0)
|                         - ESCAN00057831: Compiler warning: "canCanInterruptOldStatus" was declared but never referenced
|                         - ESCAN00057832: Compiler warning: "canCanInterruptCounter" was set but never referenced
|                         - ESCAN00062667: Verify Identity during CanOnline and Misra improvement

|    ************    Version and change information of      **********        
|    ************    high level part only                   **********        
|
|    Please find the version number of the whole module in the previous 
|    File header.
|
|************************************************************************** */


/* *********************************************************************** */
/* Version                  (abcd: Main version ab Sub Version cd )        */
/* *********************************************************************** */
/* ##V_CFG_MANAGEMENT ##CQProject : DrvCan_MAC7100FLEXCANHLL CQComponent : Implementation */
#define DRVCAN_MAC7100FLEXCANHLL_VERSION          0x0303u
#define DRVCAN_MAC7100FLEXCANHLL_RELEASE_VERSION  0x11u


/* ##V_CFG_MANAGEMENT ##CQProject : DrvCan__coreHll CQComponent : Implementation */
# define DRVCAN__COREHLL_VERSION                 0x0215
# define DRVCAN__COREHLL_RELEASE_VERSION         0x02

#define DRVCAN__HLLTXQUEUEBIT_VERSION 0x0106
#define DRVCAN__HLLTXQUEUEBIT_RELEASE_VERSION 0x04

/* *********************************************************************** */
/* Include                                                                 */
/* *********************************************************************** */

# include "v_def.h"

/* *********************************************************************** */
/* Defines                                                                 */
/* *********************************************************************** */

/* *********************************************************************** */
/* Default switches                                                        */
/* Automatic define settings, depending on user configuration in can_cfg.h */
/* *********************************************************************** */
# if defined( C_ENABLE_MULTICHANNEL_API )
#  define C_MULTIPLE_RECEIVE_CHANNEL
#  define MULTIPLE_RECEIVE_CHANNEL
# else
#  define C_SINGLE_RECEIVE_CHANNEL
# endif

# if ( kCanNumberOfTxObjects > 0 )
#  if !(defined( C_ENABLE_CAN_TRANSMIT ) || defined( C_DISABLE_CAN_TRANSMIT ))
#   define C_ENABLE_CAN_TRANSMIT
#  endif
# endif

# if !(defined( C_ENABLE_OFFLINE ) || defined( C_DISABLE_OFFLINE ))
#  define C_ENABLE_OFFLINE
# endif

# if !(defined( C_ENABLE_STOP ) || defined( C_DISABLE_STOP ))
#  define C_ENABLE_STOP
# endif

# if !(defined( C_ENABLE_CAN_CAN_INTERRUPT_CONTROL ) || defined( C_DISABLE_CAN_CAN_INTERRUPT_CONTROL ))
#  define C_ENABLE_CAN_CAN_INTERRUPT_CONTROL
# endif

# if !(defined( C_ENABLE_CAN_CANCEL_TRANSMIT ) || defined( C_DISABLE_CAN_CANCEL_TRANSMIT ))
#  if defined( C_ENABLE_CAN_TRANSMIT )
#   define C_ENABLE_CAN_CANCEL_TRANSMIT
#  endif
# endif

# if !defined( kCanNumberOfHwChannels )
/* compatibility for older tool versions */
#  define kCanNumberOfHwChannels                 kCanNumberOfChannels
# endif

#if defined (MISRA_CHECK)
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualIdType",              0488           /* MD_Can_0488_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxActualIdType",              0488           /* MD_Can_0488_LL */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualExtId",               0310           /* MD_Can_0310 */
# pragma PRQA_MACRO_MESSAGES_OFF "CanRxActualStdId",               0310           /* MD_Can_0310 */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxActualStdId",               0310           /* MD_Can_0310 */
# pragma PRQA_MACRO_MESSAGES_OFF "CanTxActualExtId",               0310           /* MD_Can_0310 */
#endif

#if defined( C_COMP_GHS_MPC55XX_FLEXCAN2 )        
# define C_ENABLE_INDIVIDUAL_BUFFER_MASKING
# if !defined( C_ENABLE_FLEXCAN_INDIV_RXMASK ) && !defined( C_DISABLE_FLEXCAN_INDIV_RXMASK )
#  define C_ENABLE_FLEXCAN_INDIV_RXMASK
# endif
# if !defined( C_ENABLE_FLEXCAN_INDIV_RXMASK ) && !defined( C_ENABLE_FLEXCAN_RXFIFO )
#  define C_ENABLE_FLEXCAN_RXFIFO /* FlexCAN Rx FIFO is required if individual receive masks are not available */
# endif
#endif


#define C_HL_DISABLE_OVERRUN_IN_STATUS
#define C_HL_DISABLE_HW_RANGES_FILTER
#define C_HL_DISABLE_DUMMY_FCT_CALL
#define C_HL_DISABLE_TX_MSG_DESTROYED
#define C_HL_DISABLE_HW_EXIT_TRANSMIT 
# define C_HL_DISABLE_LAST_INIT_OBJ
#define C_HL_DISABLE_REJECT_UNWANTED_IDTYPE
#define C_HL_DISABLE_REJECT_REMOTE_FRAME
#define C_HL_DISABLE_REJECT_REMOTE_FRAME_FULLCAN
#define C_HL_DISABLE_COPROCESSOR_SUPPORT

# define C_HL_ENABLE_IDTYPE_IN_DLC


#if defined( C_ENABLE_CANCEL_IN_HW )
# define C_HL_ENABLE_CANCEL_IN_HW_TASK
#else
# define C_HL_DISABLE_CANCEL_IN_HW_TASK
#endif


#if !( defined (C_DISABLE_DRIVER_STATUS))
# define C_DISABLE_DRIVER_STATUS
#endif


#if defined( C_PROCESSOR_MPC5602B ) || \
    defined( C_PROCESSOR_MPC5603B ) || \
    defined( C_PROCESSOR_MPC5604B ) || \
    defined( C_PROCESSOR_MPC5604 )
# if !defined( C_ENABLE_WORKAROUND_ERRATA_E4019PS ) && !defined( C_DISABLE_WORKAROUND_ERRATA_E4019PS )
#  define C_ENABLE_WORKAROUND_ERRATA_E4019PS
# endif
#endif


#if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
# if defined( C_ENABLE_FLEXCAN_INDIV_RXMASK )
#  if defined( C_ENABLE_MULTIPLE_BASICCAN )
#   if (kCanNumberOfMaxBasicCAN < 1)
#    define kCanNumberOfRxBasicMasks  1
#   else
#    define kCanNumberOfRxBasicMasks  kCanNumberOfMaxBasicCAN
#   endif
#  else
#   if !defined( kCanNumberOfRxBasicMasks )
#    if defined( C_ENABLE_MIXED_ID )
#     define kCanNumberOfRxBasicMasks   2
#    else
#     define kCanNumberOfRxBasicMasks   1
#    endif
#   endif
#  endif
#  if !defined( C_ENABLE_FLEXCAN_INDIV_RXMASK ) && (kCanNumberOfRxBasicMasks > 3)
#   error"invalid number of BasicCAN receive masks!"
#  endif
# else
#  define kCanNumberOfRxBasicMasks   3
# endif
#endif


#if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
# if defined( C_ENABLE_FLEXCAN_RXFIFO ) && !defined( C_ENABLE_FLEXCAN_INDIV_RXMASK )
#  define C_HL_ENABLE_ADJUST_RXHANDLE
# endif
#endif

#if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
# if !defined( C_ENABLE_CAN_ISR_LOCK ) && !defined( C_DISABLE_CAN_ISR_LOCK )
#  define C_DISABLE_CAN_ISR_LOCK
# endif
#endif


#if !defined( C_ENABLE_CAN_ISR_LOCK ) && !defined( C_DISABLE_CAN_ISR_LOCK )
# define C_ENABLE_CAN_ISR_LOCK
#endif

#if !defined( C_ENABLE_FLEXCAN_AUTO_RECOVERY ) && !defined( C_DISABLE_FLEXCAN_AUTO_RECOVERY )
# define C_DISABLE_FLEXCAN_AUTO_RECOVERY
#endif

#if defined( C_ENABLE_CAN_ISR_LOCK )
/* FlexCAN interrupts will be disabled during ISR process */
# define CanFlexCanInterruptDisable(x)   CanCanInterruptDisable(x)
# define CanFlexCanInterruptRestore(x)   CanCanInterruptRestore(x)
#else
/* FlexCAN interrupts stay enabled during ISR process */
# define CanFlexCanInterruptDisable(x)
# define CanFlexCanInterruptRestore(x)
#endif

#define C_HL_ENABLE_RETRANSMIT_CONF_ISR
#if !defined( C_HL_ENABLE_RETRANSMIT_FCT ) && !defined( C_HL_DISABLE_RETRANSMIT_FCT )
# define C_HL_DISABLE_RETRANSMIT_FCT
#endif

#if !defined( CANDRV_RETRANSMIT_RAM_SECTION_START ) 
# define CANDRV_RETRANSMIT_RAM_SECTION_START
#endif
#if !defined( CANDRV_RETRANSMIT_RAM_SECTION_END ) 
# define CANDRV_RETRANSMIT_RAM_SECTION_END
#endif

#if defined ( C_ENABLE_WORKAROUND_ERRATA_5164 ) && defined ( C_ENABLE_UPDATE_BASE_ADDRESS )
# error "The workaround for errata 5164 does not work combined with virtual addressing"
#endif

#define C_ENABLE_TX_ACTUAL_MACROS



# if defined( C_ENABLE_TX_POLLING )
#  if !(defined( C_ENABLE_ERROR_POLLING )  || defined( C_DISABLE_ERROR_POLLING ))
#   define C_ENABLE_ERROR_POLLING 
#  endif
# endif

# if !(defined( C_ENABLE_TASK_RECURSION_CHECK ) || defined( C_DISABLE_TASK_RECURSION_CHECK ))
#  define C_ENABLE_TASK_RECURSION_CHECK
# endif

# if defined( C_ENABLE_MULTI_ECU_PHYS )
#  define C_SUPPORTS_MULTI_ECU_PHYS
# endif

/* *********************************************************************** */
/* return values                                                           */
/* *********************************************************************** */

/* return values for precopy-routines */
# define kCanNoCopyData                          ((vuint8)0x00)
# define kCanCopyData                            ((vuint8)0x01)

/* Bitmask of return value of CanGetStatus() */
# define kCanTxOff                               ((vuint8)0x00)
# define kCanStatusInit                          ((vuint8)0x00)
# define kCanTxOn                                ((vuint8)0x01)
# define kCanTxNotOn                             ((vuint8)0xFE)              /* internal use only */
# define kCanHwIsStop                            ((vuint8)0x02)
# define kCanHwIsInit                            ((vuint8)0x04)
# define kCanHwIsInconsistent                    ((vuint8)0x08)              /* used of for common CAN */
# define kCanHwIsWarning                         ((vuint8)0x10)
# define kCanHwIsPassive                         ((vuint8)0x20)
# define kCanHwIsBusOff                          ((vuint8)0x40)
# define kCanHwIsSleep                           ((vuint8)0x80)

/* CanTransmit return values ----------------------------------------------- */
# define kCanTxFailed                            ((vuint8)0x00)  /* Tx path switched off or no sending possible */
# define kCanTxOk                                ((vuint8)0x01)  /* msg transmitted or in queue                 */
# define kCanTxPartOffline                       ((vuint8)0x02)  /* Tx path switched part off or           */
# define kCanCommunicationDisabled               ((vuint8)0x03)  /* if application has disabled com after memory check */

# if defined( C_DRV_INTERNAL )
#  define kCanTxNotify                           ((vuint8)0x05)  /* internal returncode only - not used for the API */
# endif

/* CanGetDynTxObj return values ----------------------------------------------- */
# define kCanNoTxDynObjAvailable                 ((CanTransmitHandle)0xFFFFFFFFU)

/* CanReleaseDynTxObj return values ------------------------------------------- */
# define kCanDynReleased                         ((vuint8)0x00)
# define kCanDynNotReleased                      ((vuint8)0x01)

/* generel return values */
# define kCanFailed                              ((vuint8)0x00)
# define kCanOk                                  ((vuint8)0x01)
# define kCanNotSupported                        ((vuint8)0x02)

# define kCanFalse                               ((vuint8)0x00)
# define kCanTrue                                ((vuint8)0x01)

/* results of CAN RAM check */
# define kCanRamCheckFailed                      ((vuint8)0x00)
# define kCanRamCheckOk                          ((vuint8)0x01)
# define kCanDisableCommunication                ((vuint8)0x00)
# define kCanEnableCommunication                 ((vuint8)0x01)


/* return values of CanRxActualIdType */
#define kCanDLC               (0x0Fu)
#define kCanIdTypeStd         (0x00u)
#define kCanIdTypeExt         (0x20u) /* Attention: The SRR bit has to be considered for the transmission of Extended CAN frames, but must be without any effect on the reception side !
                                         ********** In Extended format it must be set to '1' for transmission.
                                                    For the Rx side it will be stored with the value received on the CAN bus, either recessive or dominant. */
#define CAN_IDTYPE_STD        (vuint32)(0x00)
#define CAN_IDTYPE_EXT        (vuint32)(0x00200000)

/* return values of CanGetDriverStatus */
#define kCanDriverBusoff      (0x01u)   /* CAN driver is in recovery phase after bus off */ 
#define kCanDriverBusoffInit  (0x02u)   /* Driver finished recovery and needs to be initialized */
#define kCanDriverNormal      (0x03u)   /* Driver completed recovery and is in normal mode */ 

/* *********************************************************************** */
/* parameter values                                                        */
/* *********************************************************************** */
/* parameters for partial offline */
# define kCanTxPartInit                          ((vuint8)0x00)

/* paramater for assertions */
# define kCanAllChannels                         ((CanChannelHandle)0xFFU)
/* used for generated tables */
# define kCanChannelNotUsed                      ((CanChannelHandle)0xFFU)

/* canRxHandle does not contain a certain message handle or entry in table is not used */
# define kCanRxHandleNotUsed                     ((CanReceiveHandle)  0xFFFFFFFFU)
# define kCanTxHandleNotUsed                     ((CanTransmitHandle) 0xFFFFFFFFU)

# if defined( C_DRV_INTERNAL )
#  define kCanRxHandleRange0                     ((CanReceiveHandle)  0xFFFFFFF0U)
#  define kCanRxHandleRange1                     ((CanReceiveHandle)  0xFFFFFFF1U)
#  define kCanRxHandleRange2                     ((CanReceiveHandle)  0xFFFFFFF2U)
#  define kCanRxHandleRange3                     ((CanReceiveHandle)  0xFFFFFFF3U)

/* entries for generated table CanHwMsgTransmitIndex[], CanHwTxNormalIndex[] - unused in case of CommonCan */
/* table entry does not contain a HW object assignment */
#  define kCanObjectHandleNotUsed                ((CanObjectHandle)0xFFU)
# endif

/* status of transmit objects */
# define kCanBufferFree                         ((CanTransmitHandle)0xFFFFFFFFU)   /* mark a transmit object is free */
# define kCanBufferCancel                       ((CanTransmitHandle)0xFFFFFFFEU)   /* mark a transmit object as canceled */
# define kCanBufferMsgDestroyed                 ((CanTransmitHandle)0xFFFFFFFDU)   /* mark a transmit object as destroyed */
# define kCanBufferMsgTransmit                  ((CanTransmitHandle)0xFFFFFFFCU)   /* mark a transmit object as used by CanMsgTransmit */
# define kCanBufferRetransmit                   ((CanTransmitHandle)0xFFFFFFFBU)   /* mark a transmit object as used by CanRetransmit */
/* valid transmit message handle:   0x0 to kCanNumberOfTxObjects   */

/* parameter for ApplCanTimerStart(),-End(), -Loop() */
/* index has to start with 0, continues numbers have to be used. Gabs are not allowed! */
#define kCanLoopInit                ((vuint8)0x00)
#define kCanLoopRxBasicIrq          ((vuint8)0x01)
#define kCanLoopRxFullIrq           ((vuint8)0x02)
#define kCanLoopEnterFreezeModeInit ((vuint8)0x03)

#if defined( C_ENABLE_WORKAROUND_ERRATA_5164 )
#define kCanLoopSetDisable        ((vuint8)0x04)
#define kCanLoopSetFreeze         ((vuint8)0x05)
#define kCanLoopClearFreeze       ((vuint8)0x06)
#endif

#define kCanLoopEnterFreezeMode   ((vuint8)0x07)
#define kCanLoopEnterDisableMode  ((vuint8)0x08)
#define kCanLoopEnterNormalMode   ((vuint8)0x09)


/* *********************************************************************** */
/* macros                                                                  */
/* *********************************************************************** */

# if defined( C_SINGLE_RECEIVE_CHANNEL ) 
#  define CAN_CHANNEL_CANTYPE_ONLY               void                                 /* PRQA S 3460 */
#  define CAN_CHANNEL_CANTYPE_FIRST
#  define CAN_CHANNEL_CANTYPE_LOCAL         
#  define CAN_CHANNEL_CANPARA_ONLY
#  define CAN_CHANNEL_CANPARA_FIRST
#  define CAN_HW_CHANNEL_CANTYPE_ONLY            void                                 /* PRQA S 3460 */
#  define CAN_HW_CHANNEL_CANTYPE_FIRST
#  define CAN_HW_CHANNEL_CANTYPE_LOCAL
#  define CAN_HW_CHANNEL_CANPARA_ONLY
#  define CAN_HW_CHANNEL_CANPARA_FIRST
# else
#  define CAN_CHANNEL_CANTYPE_ONLY               CanChannelHandle channel
#  define CAN_CHANNEL_CANTYPE_FIRST              CanChannelHandle channel,
#  define CAN_CHANNEL_CANTYPE_LOCAL              CanChannelHandle channel;             /* PRQA S 3412 */
#  define CAN_CHANNEL_CANPARA_ONLY               channel
#  define CAN_CHANNEL_CANPARA_FIRST              channel,
#  define CAN_HW_CHANNEL_CANTYPE_ONLY            CanChannelHandle canHwChannel
#  define CAN_HW_CHANNEL_CANTYPE_FIRST           CanChannelHandle canHwChannel,
#  define CAN_HW_CHANNEL_CANTYPE_LOCAL           CanChannelHandle canHwChannel;        /* PRQA S 3412 */
#  define CAN_HW_CHANNEL_CANPARA_ONLY            canHwChannel
#  define CAN_HW_CHANNEL_CANPARA_FIRST           canHwChannel,
# endif

# if defined( C_DRV_INTERNAL )
/* macros to fill struct elements RangeMask and RangeCode of type tCanChannelObject - used by generation tool only */
#  if (kCanNumberOfUsedCanRxIdTables == 1)
#   define MK_RX_RANGE_MASK_IDSTD(i)             {MK_RX_RANGE_MASK_IDSTD0(i)}
#   define MK_RX_RANGE_CODE_IDSTD(i)             {MK_RX_RANGE_CODE_IDSTD0(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 2)
#   define MK_RX_RANGE_MASK_IDSTD(i)             {MK_RX_RANGE_MASK_IDSTD0(i), MK_RX_RANGE_MASK_IDSTD1(i)}
#   define MK_RX_RANGE_CODE_IDSTD(i)             {MK_RX_RANGE_CODE_IDSTD0(i), MK_RX_RANGE_CODE_IDSTD1(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 3)
#   define MK_RX_RANGE_MASK_IDSTD(i)             {MK_RX_RANGE_MASK_IDSTD0(i), MK_RX_RANGE_MASK_IDSTD1(i), MK_RX_RANGE_MASK_IDSTD2(i)}
#   define MK_RX_RANGE_CODE_IDSTD(i)             {MK_RX_RANGE_CODE_IDSTD0(i), MK_RX_RANGE_CODE_IDSTD1(i), MK_RX_RANGE_CODE_IDSTD2(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 4)
#   define MK_RX_RANGE_MASK_IDSTD(i)             {MK_RX_RANGE_MASK_IDSTD0(i), MK_RX_RANGE_MASK_IDSTD1(i), MK_RX_RANGE_MASK_IDSTD2(i), MK_RX_RANGE_MASK_IDSTD3(i)}
#   define MK_RX_RANGE_CODE_IDSTD(i)             {MK_RX_RANGE_CODE_IDSTD0(i), MK_RX_RANGE_CODE_IDSTD1(i), MK_RX_RANGE_CODE_IDSTD2(i), MK_RX_RANGE_CODE_IDSTD3(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 5)
#   define MK_RX_RANGE_MASK_IDSTD(i)             {MK_RX_RANGE_MASK_IDSTD0(i), MK_RX_RANGE_MASK_IDSTD1(i), MK_RX_RANGE_MASK_IDSTD2(i), MK_RX_RANGE_MASK_IDSTD3(i), MK_RX_RANGE_MASK_IDSTD4(i)}
#   define MK_RX_RANGE_CODE_IDSTD(i)             {MK_RX_RANGE_CODE_IDSTD0(i), MK_RX_RANGE_CODE_IDSTD1(i), MK_RX_RANGE_CODE_IDSTD2(i), MK_RX_RANGE_CODE_IDSTD3(i), MK_RX_RANGE_CODE_IDSTD4(i)}
#  endif

#  if (kCanNumberOfUsedCanRxIdTables == 1)
#   define MK_RX_RANGE_MASK_IDEXT(i)             {MK_RX_RANGE_MASK_IDEXT0(i)}
#   define MK_RX_RANGE_CODE_IDEXT(i)             {MK_RX_RANGE_CODE_IDEXT0(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 2)
#   define MK_RX_RANGE_MASK_IDEXT(i)             {MK_RX_RANGE_MASK_IDEXT0(i), MK_RX_RANGE_MASK_IDEXT1(i)}
#   define MK_RX_RANGE_CODE_IDEXT(i)             {MK_RX_RANGE_CODE_IDEXT0(i), MK_RX_RANGE_CODE_IDEXT1(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 3)
#   define MK_RX_RANGE_MASK_IDEXT(i)             {MK_RX_RANGE_MASK_IDEXT0(i), MK_RX_RANGE_MASK_IDEXT1(i), MK_RX_RANGE_MASK_IDEXT2(i)}
#   define MK_RX_RANGE_CODE_IDEXT(i)             {MK_RX_RANGE_CODE_IDEXT0(i), MK_RX_RANGE_CODE_IDEXT1(i), MK_RX_RANGE_CODE_IDEXT2(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 4)
#   define MK_RX_RANGE_MASK_IDEXT(i)             {MK_RX_RANGE_MASK_IDEXT0(i), MK_RX_RANGE_MASK_IDEXT1(i), MK_RX_RANGE_MASK_IDEXT2(i), MK_RX_RANGE_MASK_IDEXT3(i)}
#   define MK_RX_RANGE_CODE_IDEXT(i)             {MK_RX_RANGE_CODE_IDEXT0(i), MK_RX_RANGE_CODE_IDEXT1(i), MK_RX_RANGE_CODE_IDEXT2(i), MK_RX_RANGE_CODE_IDEXT3(i)}
#  endif
#  if (kCanNumberOfUsedCanRxIdTables == 5)
#   define MK_RX_RANGE_MASK_IDEXT(i)             {MK_RX_RANGE_MASK_IDEXT0(i), MK_RX_RANGE_MASK_IDEXT1(i), MK_RX_RANGE_MASK_IDEXT2(i), MK_RX_RANGE_MASK_IDEXT3(i), MK_RX_RANGE_MASK_IDEXT4(i)}
#   define MK_RX_RANGE_CODE_IDEXT(i)             {MK_RX_RANGE_CODE_IDEXT0(i), MK_RX_RANGE_CODE_IDEXT1(i), MK_RX_RANGE_CODE_IDEXT2(i), MK_RX_RANGE_CODE_IDEXT3(i), MK_RX_RANGE_CODE_IDEXT4(i)}
#  endif
# endif

/* calculate size of cond/ind-flags */
#  define kCanNumberOfConfBytes                  ((kCanNumberOfConfFlags + 7)/8)
# define kCanNumberOfConfWords                   ((kCanNumberOfConfFlags + 15)/16)
# define kCanNumberOfConfDWords                  ((kCanNumberOfConfFlags + 31)/32)
#  define kCanNumberOfIndBytes                   ((kCanNumberOfIndFlags + 7)/8)
# define kCanNumberOfIndWords                    ((kCanNumberOfIndFlags + 15)/16)
# define kCanNumberOfIndDWords                   ((kCanNumberOfIndFlags + 31)/32)

/* Macros for CAN message access within ApplCanMsgReceived() or PreCopy() function */

# if defined( C_ENABLE_EXTENDED_ID )
#  if defined( C_ENABLE_MIXED_ID )
#   define CanRxActualId(rxStruct)               ((CanRxActualIdType(rxStruct) == kCanIdTypeExt) ?      \
                                                 CanRxActualExtId(rxStruct) : ((vuint32)CanRxActualStdId(rxStruct)))      /* returns vuint32 */
#  else
#   define CanRxActualId(rxStruct)               (CanRxActualExtId(rxStruct))             /* returns vuint32 */
#  endif
# else
#  define CanRxActualId(rxStruct)                (CanRxActualStdId(rxStruct))             /* returns vuint16 */
# endif

/* Macros for CAN Status */
# define CanHwIsOk(state)                        (((state) & (kCanHwIsWarning |     \
                                                    kCanHwIsPassive |     \
                                                    kCanHwIsBusOff) )    ? 0 : 1)
# define CanHwIsWarning(state)                   (((state) & kCanHwIsWarning)      ? 1 : 0)
# define CanHwIsPassive(state)                   (((state) & kCanHwIsPassive)      ? 1 : 0)
# define CanHwIsBusOff(state)                    (((state) & kCanHwIsBusOff)       ? 1 : 0)
# define CanHwIsWakeup(state)                    (((state) & kCanHwIsSleep)        ? 0 : 1)
# define CanHwIsSleep(state)                     (((state) & kCanHwIsSleep)        ? 1 : 0)
# define CanHwIsStop(state)                      (((state) & kCanHwIsStop)         ? 1 : 0)
# define CanHwIsStart(state)                     (((state) & kCanHwIsStop)         ? 0 : 1)
# define CanIsOnline(state)                      (((state) & kCanTxOn)             ? 1 : 0)
# define CanIsOffline(state)                     (((state) & kCanTxOn)             ? 0 : 1)
# define CanHwIsInconsistent(state)              (((state) & kCanHwIsInconsistent) ? 1 : 0)



#  if defined( C_DRV_INTERNAL )
#   define CanGetTxId0(i)                        (CanTxId0[i])
#   define CanGetTxId1(i)                        (CanTxId1[i])
#   define CanGetTxId2(i)                        (CanTxId2[i])
#   define CanGetTxId3(i)                        (CanTxId3[i])
#   define CanGetTxId4(i)                        (CanTxId4[i])
#   if defined( C_ENABLE_EXTENDED_ID )
#    if defined( C_ENABLE_MIXED_ID )
#      if defined( C_HL_ENABLE_IDTYPE_IN_DLC )
#       define CanGetTxIdType(i)                 (CanTxDLC[i] & kCanIdTypeExt)
#      else
#       define CanGetTxIdType(i)                 (CanTxIdType[i] & kCanIdTypeExt)
#      endif
#    else
#     define CanGetTxIdType(i)                   (kCanIdTypeExt)
#    endif
#   else
#    define CanGetTxIdType(i)                    (kCanIdTypeStd)
#   endif
#  endif /* C_DRV_INTERNAL */

#  define CanGetTxDlc(i)                         (CanTxDLC[i])
#  define CanGetTxDataPtr(i)                     (CanTxDataPtr[i])
#  define CanGetConfirmationOffset(i)            (CanConfirmationOffset[i])
#  define CanGetConfirmationMask(i)              (CanConfirmationMask[i])
#   define CanGetTxHwObj(i)                      (CanTxHwObj[i])
#  define CanGetTxSendMask(i)                    (CanTxSendMask[i])
#  define CanGetApplPreTransmitPtr(i)            (CanTxApplPreTransmitPtr[i])
#  define CanGetApplConfirmationPtr(i)           (CanTxApplConfirmationPtr[i])
#  define CanGetChannelOfTxObj(i)                (CanTxMsgHandleToChannel[i])

#  if defined( C_DRV_INTERNAL )
#   define CanGetRxId0(i)                        (CanRxId0[i])
#   define CanGetRxId1(i)                        (CanRxId1[i])
#   define CanGetRxId2(i)                        (CanRxId2[i])
#   define CanGetRxId3(i)                        (CanRxId3[i])
#   define CanGetRxId4(i)                        (CanRxId4[i])
#   if defined( C_ENABLE_EXTENDED_ID )
#    if defined( C_ENABLE_MIXED_ID )
#      define CanGetRxIdType(i)                  (CanRxIdType[i] & kCanIdTypeExt)
#    else
#     define CanGetRxIdType(i)                   (kCanIdTypeExt)
#    endif
#   else
#    define CanGetRxIdType(i)                    (kCanIdTypeStd)
#   endif
#  endif /* C_DRV_INTERNAL */

#  define CanGetRxDataLen(i)                     (CanRxDataLen[i])
#  define CanGetRxMinDataLen(i)                  (CanRxMinDataLen[i])
#  define CanGetRxDataPtr(i)                     (CanRxDataPtr[i])
#  define CanGetIndicationOffset(i)              (CanIndicationOffset[i])
#  define CanGetIndicationMask(i)                (CanIndicationMask[i])
#  define CanGetApplPrecopyPtr(i)                (CanRxApplPrecopyPtr[i])
#  define CanGetApplIndicationPtr(i)             (CanRxApplIndicationPtr[i])

# if defined( C_ENABLE_CONFIRMATION_FCT ) && \
    defined( C_ENABLE_DYN_TX_OBJECTS )  && \
    defined( C_ENABLE_TRANSMIT_QUEUE )
  /* set confirmation active for CanReleaseDynTxObj() */
#  if defined( C_SINGLE_RECEIVE_CHANNEL ) 
#   define CanConfirmStart(txHandle)             {confirmHandle[0] = (txHandle);}                 /* PRQA S 3458 */
#   define CanConfirmEnd()                       {confirmHandle[0] = kCanTxHandleNotUsed;}        /* PRQA S 3458 */
#  else
#   define CanConfirmStart(channel, txHandle)    {confirmHandle[channel] = (txHandle);}           /* PRQA S 3458 */
#   define CanConfirmEnd(channel)                {confirmHandle[channel] = kCanTxHandleNotUsed;}  /* PRQA S 3458 */
#  endif
# endif

# if defined( C_ENABLE_PART_OFFLINE )
#  if defined( C_SINGLE_RECEIVE_CHANNEL ) 
#   define CanPartOffline(sendGroup)             (CanSetPartOffline( sendGroup))
#   define CanPartOnline(sendGroup)              (CanSetPartOnline( (vuint8)~(vuint8)(sendGroup)) )
#  else
#   define CanPartOffline(channel, sendGroup)    (CanSetPartOffline((channel), (sendGroup)))
#   define CanPartOnline(channel,  sendGroup)    (CanSetPartOnline((channel), (vuint8)~(vuint8)(sendGroup)) )
#  endif
# else
#  if defined( C_SINGLE_RECEIVE_CHANNEL ) 
#   define CanPartOffline(sendGroup)
#   define CanPartOnline(sendGroup)
#  else
#   define CanPartOffline(channel, sendGroup)
#   define CanPartOnline(channel, sendGroup)
#  endif
# endif

/* provide interface for interrupt disable and restore functions */
# define CanGlobalInterruptDisable               VStdSuspendAllInterrupts
# define CanGlobalInterruptRestore               VStdResumeAllInterrupts

# if ( C_SECURITY_LEVEL == 0 )
#  define CanDeclareGlobalInterruptOldStatus
#  define CanPutGlobalInterruptOldStatus(x)
#  define CanGetGlobalInterruptOldStatus(x)
#  define CanNestedGlobalInterruptDisable()
#  define CanNestedGlobalInterruptRestore()
# else  /* C_SECURITY_LEVEL == 0 */
#  define CanDeclareGlobalInterruptOldStatus     VStdDeclareGlobalInterruptOldStatus
#  define CanPutGlobalInterruptOldStatus(x)      VStdPutGlobalInterruptOldStatus(x)
#  define CanGetGlobalInterruptOldStatus(x)      VStdGetGlobalInterruptOldStatus(x)
#  if (VSTDLIB__COREHLL_VERSION  <  0x0216 )
#   define CanNestedGlobalInterruptDisable()      VStdNestedGlobalInterruptDisable()
#   define CanNestedGlobalInterruptRestore()      VStdNestedGlobalInterruptRestore()
#  else
#   define CanNestedGlobalInterruptDisable()      VStdGlobalInterruptDisable()
#   define CanNestedGlobalInterruptRestore()      VStdGlobalInterruptRestore()
#  endif
# endif /* C_SECURITY_LEVEL == 0 */


/* provide support for multiple callbacks */
#if !defined( APPL_CAN_GENERIC_PRECOPY )
# define APPL_CAN_GENERIC_PRECOPY                          ApplCanGenericPrecopy
#endif
#if !defined( APPL_CAN_TX_CONFIRMATION )
# define APPL_CAN_TX_CONFIRMATION                          ApplCanTxConfirmation
#endif
#if !defined( APPL_CAN_MSGTRANSMITCONF )
# define APPL_CAN_MSGTRANSMITCONF                          ApplCanMsgTransmitConf
#endif
#if !defined( APPL_CAN_MSGTRANSMITINIT )
# define APPL_CAN_MSGTRANSMITINIT                          ApplCanMsgTransmitInit
#endif
#if !defined( APPL_CAN_ONLINE )
# define APPL_CAN_ONLINE                                   ApplCanOnline
#endif
#if !defined( APPL_CAN_OFFLINE )
# define APPL_CAN_OFFLINE                                  ApplCanOffline
#endif
#if !defined( APPL_CAN_MSGRECEIVED )
# define APPL_CAN_MSGRECEIVED                              ApplCanMsgReceived
#endif
#if !defined( APPL_CAN_CANCELNOTIFICATION )
# define APPL_CAN_CANCELNOTIFICATION                       ApplCanCancelNotification
#endif
#if !defined( APPL_CAN_MSGCANCELNOTIFICATION )
# define APPL_CAN_MSGCANCELNOTIFICATION                    ApplCanMsgCancelNotification
#endif

#if defined( C_CPUTYPE_32BIT )
# define kCanTxQueueSize      ((kCanTxQueueBytes + 3) >> 2)
#endif


#if defined( C_ENABLE_VARIABLE_DLC )
/* mask to keep some bits unchanged in the DLC for use with variable DLC */
/*  - bit remaining unchanged should be masked with 1 e.g. id type or direction (difference between MK_TX_DLC and MK_TX_DLC_EXT?) */
#define CanLL_DlcMask   ((vuint16)0xFFF0)
#endif

# if defined( C_ENABLE_EXTENDED_ID ) 
#  define MK_STDID0(id)                 ((vuint32)(((vuint32)(id) & (vuint32)0x07FF) << 18))
# else
#  define MK_STDID0(id)                 ((vuint16)(((vuint16)(id) & (vuint16)0x07FF) << 2))
# endif
# define MK_EXTID0(id)                  ((vuint32)((vuint32)(id) & (vuint32)0x1FFFFFFF))
# define MK_STDID_HI(id)                ((vuint16)(((vuint16)(id) & (vuint16)0x07FF) << 2))
# define MK_STDID_LO(id)                ((vuint16)0x0000)
# define MK_EXTID_HI(id)                ((vuint16)(((vuint32)(id) & (vuint32)0x1FFF0000) >> 16))
# define MK_EXTID_LO(id)                ((vuint16)(((vuint32)(id) & (vuint32)0x0000FFFF)))
# define MK_RX_RANGE_MASK_IDSTD0(id)    ((vuint32)MK_STDID0(id))   
# define MK_RX_RANGE_CODE_IDSTD0(id)    ((vuint32)MK_STDID0(id))   
# define MK_RX_RANGE_MASK_IDEXT0(id)    ((vuint32)MK_EXTID0(id))   
# define MK_RX_RANGE_CODE_IDEXT0(id)    ((vuint32)MK_EXTID0(id))   

#define MK_DLC(dlc)     ((vuint32)((vuint32)(dlc) << 16))
#define MK_STDID(id)    ((vuint32)(((vuint32)(id) & (vuint32)0x07FF) << 18))
#define MK_EXTID(id)    ((vuint32)((vuint32)(id) & (vuint32)0x1FFFFFFF))

#define MK_TX_DLC(dlc)       ((vuint8)((vuint8)(dlc) & (vuint8)0x0F))
#define MK_TX_DLC_EXT(dlc)   ((vuint8)(((vuint8)(dlc) & (vuint8)0x0F) | (vuint8)0x60))
#define XT_TX_DLC(dlc)       ((vuint8)((vuint8)(dlc) & (vuint8)0x0F))

#if defined( C_SINGLE_RECEIVE_CHANNEL )
/* Bus-Off functions */
#  define CanResetBusOffStart(x)     (CanInit(x))
# define CanResetBusOffEnd(x)
/* Bus-Sleep functions */
# define CanResetBusSleep(x)         (CanInit(x))
#else
/* Bus-Off functions */
#  define CanResetBusOffStart(ch,x)  (CanInit((ch),(x)))
# define CanResetBusOffEnd(ch,x)  
/* Bus-Sleep functions */
# define CanResetBusSleep(ch,x)      (CanInit((ch),(x)))
#endif

/* Macros for CAN message access within ApplCanMsgReceived() or PreCopy() function */
/* The macros CanRxActualIdRawx() have to provide the same the macros MK_STDIDx() 
   for unused bits for standard identifier in mixed mode */
# if defined( C_ENABLE_EXTENDED_ID )
#  define CanRxActualIdRaw0(rxStruct)      ((vuint32)(*((CanChipMsgPtr32)((rxStruct)->pChipMsgObj + 4))))
# else
#  if defined( C_CPUTYPE_BIGENDIAN )  
#   define CanRxActualIdRaw0(rxStruct)     ((vuint16)(*((CanChipMsgPtr16)((rxStruct)->pChipMsgObj + 4)) & (vuint16)0x1FFF)) 
#  endif
# endif /* C_ENABLE_EXTENDED_ID */

#if defined( C_ENABLE_EXTENDED_ID )
# if defined( C_CPUTYPE_BIGENDIAN )  
#  define CanRxActualIdExtHi(rxStruct)        ((vuint8)(*((CanChipMsgPtr)((rxStruct)->pChipMsgObj + 4)) & (vuint8)0x1F))
#  define CanRxActualIdExtMidHi(rxStruct)     ((vuint8)(*((CanChipMsgPtr)((rxStruct)->pChipMsgObj + 5))))
#  define CanRxActualIdExtMidLo(rxStruct)     ((vuint8)(*((CanChipMsgPtr)((rxStruct)->pChipMsgObj + 6))))
#  define CanRxActualIdExtLo(rxStruct)        ((vuint8)(*((CanChipMsgPtr)((rxStruct)->pChipMsgObj + 7))))
# endif
#endif

# if defined( C_ENABLE_EXTENDED_ID ) 
#  define XT_ID(id)         ((vuint16)(((vuint32)(id) & (vuint32)0x1FFC0000) >> 18))
# else
#  define XT_ID(id)         ((vuint16)(((vuint16)(id) & 0x1FFC) >> 2))
# endif
# define XT_EXTID(id)       ((vuint32)((vuint32)(id) & (vuint32)0x1FFFFFFF))

#define CanRxActualExtId(rxStruct)        (XT_EXTID(CanRxActualIdRaw0(rxStruct)))
#define CanRxActualStdId(rxStruct)        (XT_ID(CanRxActualIdRaw0(rxStruct)))
#define CanRxActualData(rxStruct,i)       ((vuint8)*((CanChipDataPtr)((rxStruct)->pChipData + (i))))


#if defined( C_CPUTYPE_BIGENDIAN )  
# define CanRxActualDLC(rxStruct)         ((vuint8)((vuint8)*((CanChipMsgPtr)((rxStruct)->pChipMsgObj + 3)) & (vuint8)0x0F))
# define CanRxActualIdType(rxStruct)      (((vuint8)*((CanChipMsgPtr)((rxStruct)->pChipMsgObj + 3)) & (vuint8)kCanIdTypeExt))
#endif

/* tx actual macros */
#define CanTxActualStdId(x) CanRxActualStdId(x)
#define CanTxActualExtId(x) CanRxActualExtId(x)
#define CanTxActualDLC(txStruct)          ((vuint8)((vuint8)*((CanChipMsgPtr)((txStruct)->pChipMsgObj + 1)) & (vuint8)0x0F))
#define CanTxActualIdType(txStruct)       (((vuint8)*((CanChipMsgPtr)((txStruct)->pChipMsgObj + 1)) & (vuint8)kCanIdTypeExt))
#define CanTxActualData(txStruct,i)       CanRxActualData(txStruct,i)

# if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
#  define CanTxWriteActId(txStruct,id)       *((CanChipMsgPtr32)((txStruct).pChipMsgObj + 4)) = MK_STDID(id); \
                                             *((CanChipMsgPtr32)((txStruct).pChipMsgObj)) &= (vuint32)0x000F0000

#  define CanTxWriteActExtId(txStruct,id)    *((CanChipMsgPtr32)((txStruct).pChipMsgObj + 4)) = MK_EXTID(id); \
                                             *((CanChipMsgPtr32)((txStruct).pChipMsgObj)) |= (vuint32)0x00600000
                                             
#  define CanTxWriteActDLC(txStruct,dlc)     *((CanChipMsgPtr32)((txStruct).pChipMsgObj)) &= (vuint32)0x00600000; \
                                             *((CanChipMsgPtr32)((txStruct).pChipMsgObj)) |= MK_DLC(dlc)
# else
#  if defined( C_CPUTYPE_BIGENDIAN )
#   if defined( C_ENABLE_EXTENDED_ID )
#    define CanTxWriteActId(txStruct,id)      *((CanChipMsgPtr32)((txStruct).pChipMsgObj + 4)) = MK_STDID0(id); \
                                              *((CanChipMsgPtr)((txStruct).pChipMsgObj + 1)) &= (vuint8)0x0F
                                                                                        
#    define CanTxWriteActExtId(txStruct,id)   *((CanChipMsgPtr32)((txStruct).pChipMsgObj + 4)) = MK_EXTID0(id); \
                                              *((CanChipMsgPtr)((txStruct).pChipMsgObj + 1)) |= (vuint8)0x60                                            
#   else
#    define CanTxWriteActId(txStruct,id)      *((CanChipMsgPtr16)((txStruct).pChipMsgObj + 4)) = MK_STDID0(id); \
                                              *((CanChipMsgPtr)((txStruct).pChipMsgObj + 1)) &= (vuint8)0x0F
#   endif
#   define CanTxWriteActDLC(txStruct,dlc)     *((CanChipMsgPtr)((txStruct).pChipMsgObj + 1)) &= (vuint8)0x60; \
                                              *((CanChipMsgPtr)((txStruct).pChipMsgObj + 1)) |= ((vuint8)(dlc) & (vuint8)0x0F)
#  endif /* C_CPUTYPE_BIGENDIAN */
# endif

#if defined( C_ENABLE_MSG_TRANSMIT )

/* Macros to fill variables of the type tCanMsgTransmitStruct */
#   define CanMsgTransmitSetStdId(pCanMsgTransmitStruct, id)     (pCanMsgTransmitStruct)->IdRaw1 =  MK_STDID_HI(id); \
                                                                 (pCanMsgTransmitStruct)->DlcRaw &= (vuint16)0xFF0F
                                                                

#   define CanMsgTransmitSetExtId(pCanMsgTransmitStruct, id)     (pCanMsgTransmitStruct)->IdRaw1 = MK_EXTID_HI(id);  \
                                                                 (pCanMsgTransmitStruct)->IdRaw0 = MK_EXTID_LO(id);  \
                                                                 (pCanMsgTransmitStruct)->DlcRaw |= (vuint16)0x0060


#  define CanMsgTransmitSetDlc(pCanMsgTransmitStruct, dlc)       (pCanMsgTransmitStruct)->DlcRaw &= (vuint16)0xFF60; \
                                                                 (pCanMsgTransmitStruct)->DlcRaw |= ((vuint16)(dlc) & (vuint16)0x000F)
                                                                          
#  define CanMsgTransmitSetData(pCanMsgTransmitStruct, x, msgData) (pCanMsgTransmitStruct)->DataFld[(x)]=(msgData)

#endif  /* C_ENABLE_MSG_TRANSMIT */

/* macros for buffer access */
#define StartRxReadSync()             (VStdSuspendAllInterrupts())
#define EndRxReadSync()               (VStdResumeAllInterrupts())

#define StartRxWriteSync()            (VStdSuspendAllInterrupts())
#define EndRxWriteSync()              (VStdResumeAllInterrupts())

#define StartTxReadSync()
#define EndTxReadSync()

#define StartTxWriteSync()            (VStdSuspendAllInterrupts())
#define EndTxWriteSync()              (VStdResumeAllInterrupts())

#define StartRxWriteCANSync()
#define EndRxWriteCANSync()

#define StartRxReadCANSync()
#define EndRxReadCANSync()

#define StartRxFullCANReadSync(Obj)   (VStdSuspendAllInterrupts())
#define EndRxFullCANReadSync(Obj)     (VStdResumeAllInterrupts())

#define StartRxFullCANWriteSync(obj)  (VStdSuspendAllInterrupts())
#define EndRxFullCANWriteSync(obj)    (VStdResumeAllInterrupts())

#define CanStartFlagWriteSync()       (VStdSuspendAllInterrupts())
#define CanEndFlagWriteSync()         (VStdResumeAllInterrupts())


/* *********************************************************************** */
/* error codes                                                             */
/* *********************************************************************** */
/* error numbers for User Assertions 0x00-0x1f - hardware independed */
# define kErrorTxDlcTooLarge                     ((vuint8)0x01)
# define kErrorTxHdlTooLarge                     ((vuint8)0x02)
# define kErrorIntRestoreTooOften                ((vuint8)0x03)
# define kErrorIntDisableTooOften                ((vuint8)0x04)
# define kErrorChannelHdlTooLarge                ((vuint8)0x05)
# define kErrorInitObjectHdlTooLarge             ((vuint8)0x06)
# define kErrorTxHwHdlTooLarge                   ((vuint8)0x07)
# define kErrorHwObjNotInPolling                 ((vuint8)0x08)
# define kErrorHwHdlTooSmall                     ((vuint8)0x09)
# define kErrorHwHdlTooLarge                     ((vuint8)0x0A)

# define kErrorAccessedInvalidDynObj             ((vuint8)0x0B)
# define kErrorAccessedStatObjAsDyn              ((vuint8)0x0C)
# define kErrorDynObjReleased                    ((vuint8)0x0D)

# define kErrorPollingTaskRecursion              ((vuint8)0x0E)
# define kErrorDisabledChannel                   ((vuint8)0x0F)
# define kErrorDisabledTxMessage                 ((vuint8)0x10)
# define kErrorDisabledCanInt                    ((vuint8)0x11)

# define kErrorCanSleep                          ((vuint8)0x12)
# define kErrorCanOnline                         ((vuint8)0x13)
# define kErrorCanStop                           ((vuint8)0x14)
# define kErrorWrongMask                         ((vuint8)0x15)
# define kErrorWrongId                           ((vuint8)0x16)
# define kErrorNullPointerParameter              ((vuint8)0x17)
/* error numbers for User Assertions 0x20-0x3f - hardware depended */

/* error numbers for Gentool Assertions 0x40-0x5f */
# define kErrorTxROMDLCTooLarge                  ((vuint8)0x40)
# define kErrorWrongHwTxObjHandle                ((vuint8)0x41)
# define kErrorHwToLogTxObjCalculation           ((vuint8)0x42)

/* error numbers for Gentool Assertions 0x60-0x7f - hardware depended */
#define kErrorMaskExtIdConfig             ((vuint8)0x60)

/* error numbers for Hardware Assertions 0x80-0x9f */
# define kErrorTxBufferBusy                      ((vuint8)0x80)

/* error numbers for Hardware Assertions 0xa0-0xbf - hardware depended */

/* error numbers for Internal Assertions 0xc0-0xdf */
# define kErrorTxHandleWrong                     ((vuint8)0xC0)
# define kErrorInternalTxHdlTooLarge             ((vuint8)0xC1)
# define kErrorRxHandleWrong                     ((vuint8)0xC2)        
# define kErrorTxObjHandleWrong                  ((vuint8)0xC3)
# define kErrorReleasedUnusedDynObj              ((vuint8)0xC4)
# define kErrorTxQueueTooManyHandle              ((vuint8)0xC5)
# define kErrorInternalChannelHdlTooLarge        ((vuint8)0xC6)
# define kErrorInternalDisabledChannel           ((vuint8)0xC7)
# define kErrorInternalDisabledTxMessage         ((vuint8)0xC8)

/* error numbers for Internal Assertions 0xe0-0xff - hardware depended */
# define kErrorIllTxQueueCnt                     ((vuint8)0xE0)
# define kErrorTxIdNotFound                      ((vuint8)0xE1)
# define kErrorIllIrptNumber                     ((vuint8)0xE2)
# define kErrorIrqInPolling                      ((vuint8)0xE3)
# define kErrorIntPndMissing                     ((vuint8)0xE4)
# define kErrorRxFullCanIrq                      ((vuint8)0xE5)
# define kErrorInconsistentDynObjTable           ((vuint8)0xE6)
# define kErrorReleasedInvalidDynObj             ((vuint8)0xE7)
# define kErrorTransmittedInvalidDynObj          ((vuint8)0xE8)
# define kErrorIllObjectConfig                   ((vuint8)0xE9)
# define kCanInvalidHwObjHandle                  ((vuint8)0xEA)

/* *********************************************************************** */
/* DummyFunction                                                           */
/* *********************************************************************** */
# if defined( C_DRV_INTERNAL )
#  define CAN_RECEIVE_FCT_DUMMY                  ApplCanRxStructPtrDummy
#  define CAN_RANGE_FCT_DUMMY                    ApplCanRxStructPtrDummy
#  define CAN_BUSOFF_FCT_DUMMY                   ApplCanChannelDummy
#  if defined( C_HL_ENABLE_DUMMY_FCT_CALL )
#   define CAN_INDICATION_FCT_DUMMY              ApplCanRxHandleDummy
#   define CAN_PRECOPY_FCT_DUMMY                 ApplCanRxStructPtrDummy
#   define CAN_CONFIRMATION_FCT_DUMMY            ApplCanTxHandleDummy
#   define CAN_PRETRANSMIT_FCT_DUMMY             ApplCanTxStructDummy
#  else
#   define CAN_INDICATION_FCT_DUMMY              V_NULL
#   define CAN_PRECOPY_FCT_DUMMY                 V_NULL
#   define CAN_CONFIRMATION_FCT_DUMMY            V_NULL
#   define CAN_PRETRANSMIT_FCT_DUMMY             V_NULL
#  endif
# endif

# if defined( C_NO_COMPATIBILITY )
# else
/* *********************************************************************** */
/* compatibility defines                                                   */
/* *********************************************************************** */

#  define CAN_TX_DLC(i)                          (CanGetTxDlc(i))            
#  define CAN_TX_DATA_PTR(i)                     (CanGetTxDataPtr(i))         
#  define CAN_CONFIRMATION_OFFSET(i)             (CanGetConfirmationOffset(i))
#  define CAN_CONFIRMATION_MASK(i)               (CanGetConfirmationMask(i))

#  define CAN_RX_DATA_LEN(i)                     (CanGetRxDataLen(i))
#  define CAN_RX_DATA_PTR(i)                     (CanGetRxDataPtr(i))
#  define CAN_INDICATION_OFFSET(i)               (CanGetIndicationOffset(i))
#  define CAN_INDICATION_MASK(i)                 (CanGetIndicationMask(i))

#  define CanInterruptDisable()                  VStdSuspendAllInterrupts()
#  define CanInterruptRestore()                  VStdResumeAllInterrupts()

#  define ApplCanReceiveDummy0                   ApplCanRxStructPtrDummy
#  define ApplCanReceiveDummy1                   ApplCanChannelDummy

#  define CanGetTxDirectMsg                      (CanGetTxHwObj)

#  define canRxDlcRam                            (canVariableRxDataLen)

#  define CAN_START_INDEX_INIT_OBJ(i)            (CanInitObjectStartIndex[i])
#  define CAN_START_INDEX_TX_OBJ(i)              (CanTxStartIndex[i])
#  define CAN_START_INDEX_RX_OBJ(i)              (CanRxStartIndex[i])

#  if !defined( VGEN_GENY )
#   if defined( C_ENABLE_RANGE_EXTENDED_ID )
#    define MK_RX_RANGE_MASK0(id)                (MK_RX_RANGE_MASK_IDEXT0(id))
#    define MK_RX_RANGE_MASK1(id)                (MK_RX_RANGE_MASK_IDEXT1(id))
#    define MK_RX_RANGE_MASK2(id)                (MK_RX_RANGE_MASK_IDEXT2(id))
#    define MK_RX_RANGE_MASK3(id)                (MK_RX_RANGE_MASK_IDEXT3(id))
#    define MK_RX_RANGE_MASK4(id)                (MK_RX_RANGE_MASK_IDEXT4(id))

#    define MK_RX_RANGE_CODE0(id)                (MK_RX_RANGE_CODE_IDEXT0(id))
#    define MK_RX_RANGE_CODE1(id)                (MK_RX_RANGE_CODE_IDEXT1(id))
#    define MK_RX_RANGE_CODE2(id)                (MK_RX_RANGE_CODE_IDEXT2(id))
#    define MK_RX_RANGE_CODE3(id)                (MK_RX_RANGE_CODE_IDEXT3(id))
#    define MK_RX_RANGE_CODE4(id)                (MK_RX_RANGE_CODE_IDEXT4(id))
#   else
#    define MK_RX_RANGE_MASK0(id)                (MK_RX_RANGE_MASK_IDSTD0(id))
#    define MK_RX_RANGE_MASK1(id)                (MK_RX_RANGE_MASK_IDSTD1(id))
#    define MK_RX_RANGE_MASK2(id)                (MK_RX_RANGE_MASK_IDSTD2(id))
#    define MK_RX_RANGE_MASK3(id)                (MK_RX_RANGE_MASK_IDSTD3(id))
#    define MK_RX_RANGE_MASK4(id)                (MK_RX_RANGE_MASK_IDSTD4(id))

#    define MK_RX_RANGE_CODE0(id)                (MK_RX_RANGE_CODE_IDSTD0(id))
#    define MK_RX_RANGE_CODE1(id)                (MK_RX_RANGE_CODE_IDSTD1(id))
#    define MK_RX_RANGE_CODE2(id)                (MK_RX_RANGE_CODE_IDSTD2(id))
#    define MK_RX_RANGE_CODE3(id)                (MK_RX_RANGE_CODE_IDSTD3(id))
#    define MK_RX_RANGE_CODE4(id)                (MK_RX_RANGE_CODE_IDSTD4(id))
#   endif
#  endif

/* *********************************************************************** */
/* end of compatibility defines                                            */
/* *********************************************************************** */
# endif /* C_NO_COMPATIBILITY */

/* *********************************************************************** */
/* Memory qualifier                                                        */
/* *********************************************************************** */
/* memory qualifier for the CAN controller registers */
#define MEMORY_CAN       

/* *********************************************************************** */
/* data types                                                              */
/* *********************************************************************** */

/* declare data type for the queue */
#if defined( C_CPUTYPE_32BIT )
typedef vuint32 tCanQueueElementType;
#endif

#if !defined( tCanTxQueuePadBits )
# define tCanTxQueuePadBits vuint8
#endif

/* GROUP    CAN UNIT    INT SOURCES
   ---------------------------------
   A        FLEXCAN1    20
   B        FLEXCAN2    9 / 20
   C        FLEXCAN2    1
   D        FLEXCAN1    3
   --------------------------------- */

   
#if defined( C_COMP_GHS_MPC55XX_FLEXCAN2 )        
# if !defined( C_FLEXCAN_ISR_GROUP_B )
#  define C_FLEXCAN_ISR_GROUP_B
# endif    
#endif   

   

#if defined( C_PROCESSOR_PC57170X ) 
# if !defined( C_CAN_MAX_BUFFER_32 ) && \
     !defined( C_CAN_MAX_BUFFER_64 ) && \
     !defined( C_CAN_MAX_BUFFER_MIXED )
#  define C_CAN_MAX_BUFFER_MIXED
# endif
#endif

#if defined( C_PROCESSOR_MPC5604D ) || \
    defined( C_PROCESSOR_MPC5602D ) || \
    defined( C_PROCESSOR_MPC5604P ) || \
    defined( C_PROCESSOR_MPC5675K ) || \
    defined( C_PROCESSOR_MPC5643L )
# if !defined( C_CAN_MAX_BUFFER_32 ) && \
     !defined( C_CAN_MAX_BUFFER_64 ) && \
     !defined( C_CAN_MAX_BUFFER_MIXED )
#  define C_CAN_MAX_BUFFER_32
# endif
#endif



#if defined( C_COMP_GHS_MPC55XX_FLEXCAN2 )      
# if !defined( C_ENABLE_SLEEP_WAKEUP ) && !defined( C_DISABLE_SLEEP_WAKEUP ) 
#  define C_DISABLE_SLEEP_WAKEUP
# endif    
#endif

#if defined( C_COMP_GHS_MPC55XX_FLEXCAN2 )      
/* rejection of reception from self sent frames performed by hardware */
# define C_ENABLE_REJECT_SELF_RX_BY_HW
#endif


#if !defined( C_ENABLE_SINGLE_ISR_API ) && !defined( C_DISABLE_SINGLE_ISR_API )
/* Single ISR API enabled by default */
# define C_ENABLE_SINGLE_ISR_API
#endif




#if defined( C_COMP_GHS_MPC55XX_FLEXCAN2 )        
# if defined( C_CAN_MAX_BUFFER_32 ) || \
     defined( C_CAN_MAX_BUFFER_64 ) || \
     defined( C_CAN_MAX_BUFFER_MIXED )     
#  if defined( C_CAN_MAX_BUFFER_32 )
#   define kCanMaxMB            ((vuint16)32) /* number of message buffers per CAN module */    
#  endif
#  if defined( C_CAN_MAX_BUFFER_64 )
#   define kCanMaxMB            ((vuint16)64) /* number of message buffers per CAN module */    
#   define C_ENABLE_MAX_BUFFER_64
#  endif
#  if defined( C_CAN_MAX_BUFFER_MIXED )
#   define kCanMaxMB            ((vuint16)64) /* number of message buffers per CAN module */    
#   define C_ENABLE_MAX_BUFFER_64
#  endif
# else
#  define kCanMaxMB             ((vuint16)64) /* number of message buffers per CAN module */    
#  define C_ENABLE_MAX_BUFFER_64
# endif
#endif

#if defined( C_ENABLE_ERROR_POLLING )
# define C_DISABLE_CAN_BUSOFF_INTERRUPT
#else
# define C_ENABLE_CAN_BUSOFF_INTERRUPT
#endif

#if (defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && !defined( C_ENABLE_RX_BASICCAN_POLLING )) || \
    (defined( C_ENABLE_RX_FULLCAN_OBJECTS ) && !defined( C_ENABLE_RX_FULLCAN_POLLING ))   || \
    (!defined( C_ENABLE_TX_POLLING )) || (defined( C_ENABLE_INDIVIDUAL_POLLING ))
# define C_ENABLE_CAN_RXTX_INTERRUPT
#else
# define C_DISABLE_CAN_RXTX_INTERRUPT
#endif

#if defined( C_ENABLE_SLEEP_WAKEUP )
#  if defined( C_ENABLE_FLEXCAN_DOZE_MODE )
#   if defined( C_ENABLE_WAKEUP_POLLING )
#    define C_DISABLE_CAN_WAKEUP_INTERRUPT
#   else
#    define C_ENABLE_CAN_WAKEUP_INTERRUPT
#   endif
#  else
#   if defined( C_ENABLE_WAKEUP_POLLING )
#    error " FlexCAN wakeup polling only possible if DOZE mode is used!"
#   endif
#  endif
#endif

#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
    defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
    defined( C_ENABLE_WAKEUP_INTERRUPT )
# define C_HL_ENABLE_CAN_IRQ_DISABLE   
#else
# define C_HL_DISABLE_CAN_IRQ_DISABLE   
#endif

/* data types for driver function parameters */
/* the types of CanInitHandle, CanChannelHandle and CanObjectHandle depends
   on the compiler and controller - what generates effective code */
V_DEF_VAR_TYPE(V_NONE, vuint16) CanChannelHandle;
/* CanObjectHandle has to be unsigned! */
V_DEF_VAR_TYPE(V_NONE, vuint16) CanObjectHandle;
V_DEF_VAR_TYPE(V_NONE, vuint16) CanTransmitHandle;

V_DEF_VAR_TYPE(V_NONE, vuint16) CanInitHandle;
V_DEF_VAR_TYPE(V_NONE, vuint16) CanReceiveHandle;

/* define datatype of local signed variables for message handles */
V_DEF_VAR_TYPE(V_NONE, vsintx) CanSignedTxHandle;

V_DEF_VAR_TYPE(V_NONE, vuintx) CanSignedRxHandle;


V_DEF_P2SFR_CAN_TYPE(volatile, vuint8)   CanSfrDataPtr;

V_DEF_P2VAR_TYPE(V_NONE, void, V_NONE) CanChipVoidPtr;

/* Pointer to msg object and message data used in precopy functions */
V_DEF_P2SFR_CAN_TYPE(volatile, vuint8)  CanChipDataPtr;
V_DEF_P2SFR_CAN_TYPE(volatile, vuint8)  CanChipMsgPtr;
V_DEF_P2SFR_CAN_TYPE(volatile, vuint16) CanChipDataPtr16;
V_DEF_P2SFR_CAN_TYPE(volatile, vuint16) CanChipMsgPtr16;
V_DEF_P2SFR_CAN_TYPE(volatile, vuint32) CanChipDataPtr32;
V_DEF_P2SFR_CAN_TYPE(volatile, vuint32) CanChipMsgPtr32;

# if defined( C_ENABLE_EXTENDED_ID )
V_DEF_VAR_TYPE(V_NONE, vuint32) tCanTxId0;
# else
V_DEF_VAR_TYPE(V_NONE, vuint16) tCanTxId0;
# endif

V_DEF_VAR_TYPE(V_NONE, vuint8) tCanIdType;

# if defined C_ENABLE_EXTENDED_ID
V_DEF_VAR_TYPE(V_NONE, vuint32) tCanRxId0;
# else
V_DEF_VAR_TYPE(V_NONE, vuint16) tCanRxId0;
# endif


#if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )    
/* structure with entry for the generated initialisation array */
typedef struct 
{
  vuint8  CanInitCtrl0;   /* Control register 0 */
  vuint8  CanInitCtrl1;   /* Control register 1 */
  vuint8  CanInitCtrl2;   /* Control register 2 */
  vuint8  CanInitPrDiv;   /* Prescaler divider register */
}tCanInitObject;

typedef struct 
{
  vuint16 CanInitMaskHi;  /* Mask Register High */
  vuint16 CanInitMaskLo;  /* Mask Register Low */
  vuint16 CanInitCodeHi;  /* Code Register High */
  vuint16 CanInitCodeLo;  /* Code Register Low */
}tCanInitBasicCan;

typedef struct tCanHwChannelDataTag
{
  vuint32 CanBaseAddress;
  vuint32 CanInterruptMaskLo;
  #if defined( C_ENABLE_MAX_BUFFER_64 )
  vuint32 CanInterruptMaskHi;
  #endif
  #if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) 
  # if !defined( C_ENABLE_RX_FULLCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
  vuint32 CanRxFullInterruptMaskLo;
  #  if defined( C_ENABLE_MAX_BUFFER_64 )
  vuint32 CanRxFullInterruptMaskHi;
  #  endif
  # endif
  # if defined( C_ENABLE_RX_FULLCAN_POLLING )
  vuint32 CanRxFullPollingMaskLo;
  #  if defined( C_ENABLE_MAX_BUFFER_64 )
  vuint32 CanRxFullPollingMaskHi;
  #  endif
  # endif
  #endif
  #if defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && !defined( C_ENABLE_FLEXCAN_RXFIFO )
  # if !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
  vuint32 CanRxBasicInterruptMaskLo;
  #  if defined( C_ENABLE_MAX_BUFFER_64 )
  vuint32 CanRxBasicInterruptMaskHi;
  #  endif
  # endif
  # if defined ( C_ENABLE_RX_BASICCAN_POLLING )
  vuint32 CanRxBasicPollingMaskLo;
  #  if defined( C_ENABLE_MAX_BUFFER_64 )
  vuint32 CanRxBasicPollingMaskHi;
  #  endif
  # endif
  #endif
  #if !defined( C_ENABLE_TX_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
  vuint32 CanTxInterruptMaskLo;
  # if defined( C_ENABLE_MAX_BUFFER_64 )
  vuint32 CanTxInterruptMaskHi;
  # endif  
  #endif
  #if defined( C_ENABLE_TX_POLLING )
  vuint32 CanTxPollingMaskLo;
  # if defined( C_ENABLE_MAX_BUFFER_64 )
  vuint32 CanTxPollingMaskHi;
  # endif
  #endif
}tCanHwChannelData;
#endif

#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
    defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
    defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
typedef volatile struct
{
  #if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
  vuint32 lowerflags; 
  # if defined( C_ENABLE_MAX_BUFFER_64 )
  vuint32 upperflags;
  # endif
  #endif
  #if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )  
  vuint16 canctrl0;  
  #endif
  #if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT ) 
  vuint16 canmcr;
  #endif  
}tCanLLCanIntOld;
#endif


typedef volatile struct
{
  vuint32 control;   /* control, status and DLC */
  #if defined( C_CPUTYPE_BIGENDIAN )  
  vuint16 msgIDH;    /* ID extended/standard */      
  vuint16 msgIDL;    /* ID extended */      
  #endif  
  vuint8  data[8];   /* message data */
  vuint16 timestamp; /* time stamp */      
}tCanRxMsgBuffer;

typedef volatile struct
{
  vuint32 data[2];
}tCanTxMsgBuffer;

# if defined( C_ENABLE_MSG_TRANSMIT ) || defined( C_ENABLE_RX_QUEUE )
/* stucture of the CAN message object used by CanMsgTransmit() or RxQueue */
typedef volatile struct
{
  vuint32 DlcRaw;
  #if defined( C_CPUTYPE_BIGENDIAN )  
  vuint16 IdRaw1;  
  vuint16 IdRaw0;    
  #endif
  vuint8  DataFld[8];
  vuint16 TimeStamp;
}tCanMsgTransmitStruct;
# endif


#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
    defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
    defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )    
V_DEF_VAR_TYPE(V_NONE, tCanLLCanIntOld)              tCanIntOld;
V_DEF_P2VAR_TYPE(volatile, tCanLLCanIntOld, V_NONE)  tCanIntOldPtr;
#endif



# if defined( C_CPUTYPE_BIGENDIAN )
typedef volatile struct
{
  vuint16  control;   /* control, status and DLC */  
  vuint16  timestamp; /* time stamp */  
  vuint16  msgIDH;    /* ID extended/standard */  
  vuint16  msgIDL;    /* ID extended */  
  vuint8   data[8];   /* message data */
}tCanMsgObj;
typedef volatile struct
{
  vuint16  canmcr;         /* 00 Module Configuration Register */
  vuint16  canmaxmb;       /* 02 Maximum Message Buffer */
  vuint16  control1;       /* 04 CAN Control 1: PRESDIV, RJW, PSEG1 and PSEG2 */
  vuint16  control0;       /* 05 CAN Control 0: BOFF_MSK, ERR_MSK, CLK_SRC, LPB, TWRN_MSK, RWRN_MSK, SMP, BOFF_REC, T_SYNC, LBUF, LOM and PROPSEG */
  vuint16  rsv0;           /* 08 Reserved */
  vuint16  timer;          /* 0A Timer */
  vuint16  rsv1;           /* 0C Reserved */
  vuint16  rsv2;           /* 0E Reserved */
  vuint16  rxgmskhi;       /* 10 Rx Global Mask Hi */
  vuint16  rxgmsklo;       /* 12 Rx Global Mask Lo */
  vuint16  rx14mskhi;      /* 14 Rx 14 Mask Hi */
  vuint16  rx14msklo;      /* 16 Rx 14 Mask Lo */
  vuint16  rx15mskhi;      /* 18 Rx 15 Mask Hi */
  vuint16  rx15msklo;      /* 1A Rx 15 Mask Lo */
  vuint16  rsv3;           /* 1C Reserved */
  vuint8   rxectr;         /* 1E Rx Error Counter */
  vuint8   txectr;         /* 1F Tx Error Counter */
  vuint32  estat;          /* 20 Error / Status */
  vuint32  imask_hi;       /* 24 Interrupt Mask 2 (MB 32 - 63) */
  vuint32  imask_lo;       /* 28 Interrupt Mask 1 (MB  0 - 31) */
  vuint32  iflag_hi;       /* 2C Interrupt Flag 2 (MB 32 - 63) */
  vuint32  iflag_lo;       /* 30 Interrupt Flag 1 (MB  0 - 31) */
  vuint32  rsv4[19];       /* 34 - 80 reserve */
  tCanMsgObj canObject[kCanMaxMB];  /* Buffer for kCanMaxMB messages */
}tFlexCAN;
# endif

typedef volatile struct
{
  vuint32  control;   /* control, status and DLC */  
  vuint32  msgID;     /* message ID */  
  vuint32  data[2];   /* message data */
}tMSGOBJ;
typedef volatile struct 
{
  #if defined( C_CPUTYPE_BIGENDIAN )
  vuint16  canmcr;         /* 00 Module Configuration Register */
  vuint16  canmaxmb;       /* 02 Maximum Message Buffer */
  vuint16  control1;       /* 04 CAN Control 1: PRESDIV, RJW, PSEG1 and PSEG2 */
  vuint16  control0;       /* 05 CAN Control 0: BOFF_MSK, ERR_MSK, CLK_SRC, LPB, TWRN_MSK, RWRN_MSK, SMP, BOFF_REC, T_SYNC, LBUF, LOM and PROPSEG */
  #endif  
  vuint32  timer;          /* 08 Reserved */
  vuint32  canrsv0;        /* 0C Reserved */  
  vuint32  rxgmask;        /* 10 Rx Global Mask */
  vuint32  rx14mask;       /* 14 Rx 14 Mask */
  vuint32  rx15mask;       /* 18 Rx 15 Mask */
  vuint32  rxtxecr;        /* 1C Rx Tx Error Counter */
  vuint32  estat;          /* 20 Error / Status */
  vuint32  imask_hi;       /* 24 Interrupt Mask 2 (MB 32 - 63) */
  vuint32  imask_lo;       /* 28 Interrupt Mask 1 (MB  0 - 31) */
  vuint32  iflag_hi;       /* 2C Interrupt Flag 2 (MB 32 - 63) */
  vuint32  iflag_lo;       /* 30 Interrupt Flag 1 (MB  0 - 31) */
  vuint32  canrsv[19];     /* 34 - 80 reserve */  
  tMSGOBJ canObject[kCanMaxMB];     /* Buffer for kCanMaxMB messages */  
}tFLEXCAN;


V_DEF_P2SFR_CAN_TYPE(V_NONE, tFlexCAN) tFlexcanPtr;
V_DEF_P2SFR_CAN_TYPE(V_NONE, tFLEXCAN) tFLEXCANPtr;

#if defined( C_SINGLE_RECEIVE_CHANNEL )
# if defined( C_ENABLE_UPDATE_BASE_ADDRESS )
#  define pFlexCAN(x)     ((tFlexcanPtr)((vuint32)canLL_VirtualPtrField[0]))     /* PRQA S 3453 */ /* MD_Can_3453 */
#  define pFLEXCAN(x)     ((tFLEXCANPtr)((vuint32)canLL_VirtualPtrField[0]))     /* PRQA S 3453 */ /* MD_Can_3453 */
# else
#   define pFlexCAN(x)     ((tFlexcanPtr)((vuint32)(C_TOUCAN_BASIS)))            /* PRQA S 3453 */ /* MD_Can_3453 */
#   define pFLEXCAN(x)     ((tFLEXCANPtr)((vuint32)(C_TOUCAN_BASIS)))            /* PRQA S 3453 */ /* MD_Can_3453 */
# endif
#else
#  if defined( C_ENABLE_UPDATE_BASE_ADDRESS )
#   define pFlexCAN(x)     ((tFlexcanPtr)((vuint32)canLL_VirtualPtrField[(x)]))  /* PRQA S 3453 */ /* MD_Can_3453 */
#   define pFLEXCAN(x)     ((tFLEXCANPtr)((vuint32)canLL_VirtualPtrField[(x)]))  /* PRQA S 3453 */ /* MD_Can_3453 */
#  else
#   define pFlexCAN(x)    ((tFlexcanPtr)((vuint32)CanHwChannelData[(x)].CanBaseAddress)) /* PRQA S 3453 */ /* MD_Can_3453 */
#   define pFLEXCAN(x)    ((tFLEXCANPtr)((vuint32)CanHwChannelData[(x)].CanBaseAddress)) /* PRQA S 3453 */ /* MD_Can_3453 */
#  endif
#endif

#if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
# if defined( C_ENABLE_FLEXCAN_INDIV_RXMASK )
typedef volatile struct
{
  vuint32 indivRxMask[kCanMaxMB]; /* Individual Receive Masks */  
}tCanRxMask;
V_DEF_P2SFR_CAN_TYPE(V_NONE, tCanRxMask) tCanRxMaskPtr;
# endif

V_DEF_P2CONST_TYPE(V_NONE, tCanInitBasicCan, CONST) tCanInitBasicCanPtr;

# if defined( C_ENABLE_FLEXCAN_RXFIFO )
typedef volatile struct
{
  vuint32  rxCODE;
  vuint32  rxID;     
  vuint32  rxDATA[2];
  vuint32  rxRSVD[20];
  vuint32  rxIDTAB[8]; 
}tRXFIFO;
V_DEF_P2SFR_CAN_TYPE(V_NONE, tRXFIFO) tRXFIFOPtr;

#  if defined( C_SINGLE_RECEIVE_CHANNEL )
#   if defined( C_ENABLE_UPDATE_BASE_ADDRESS )
#    define pRXFIFO(x)     ((tRXFIFOPtr)((vuint32)(canLL_VirtualPtrField[0]) + (vuint32)0x0080))  /* PRQA S 3453 */ /* MD_Can_3453 */
#   else
#     define pRXFIFO(x)     ((tRXFIFOPtr)((vuint32)(C_TOUCAN_BASIS) + (vuint32)0x0080))           /* PRQA S 3453 */ /* MD_Can_3453 */
#   endif
#  else /* C_SINGLE_RECEIVE_CHANNEL */
#   if defined( C_ENABLE_UPDATE_BASE_ADDRESS )
#    define pRXFIFO(x)     ((tRXFIFOPtr)((vuint32)canLL_VirtualPtrField[(x)] + (vuint32)0x0080))  /* PRQA S 3453 */ /* MD_Can_3453 */
#   else
#    define pRXFIFO(x)     ((tRXFIFOPtr)((vuint32)CanHwChannelData[(x)].CanBaseAddress + (vuint32)0x0080))            /* PRQA S 3453 */ /* MD_Can_3453 */
#   endif
#  endif /* C_SINGLE_RECEIVE_CHANNEL */
# endif /* C_ENABLE_FLEXCAN_RXFIFO */
#endif /* C_ENABLE_INDIVIDUAL_BUFFER_MASKING */

#if defined ( C_SINGLE_RECEIVE_CHANNEL )
# if defined( C_ENABLE_UPDATE_BASE_ADDRESS )
#  define pCanRxMask(x)     ((tCanRxMaskPtr)((vuint32)(canLL_VirtualPtrField[0]) + (vuint32)0x0880))  /* PRQA S 3453 */ /* MD_Can_3453 */
# else
#   define pCanRxMask(x)     ((tCanRxMaskPtr)((vuint32)(C_TOUCAN_BASIS) + (vuint32)0x0880))           /* PRQA S 3453 */ /* MD_Can_3453 */
# endif
#else
# if defined( C_ENABLE_UPDATE_BASE_ADDRESS )
#  define pCanRxMask(x)     ((tCanRxMaskPtr)((vuint32)canLL_VirtualPtrField[(x)] + (vuint32)0x0880))  /* PRQA S 3453 */ /* MD_Can_3453 */
# else
#  define pCanRxMask(x)     ((tCanRxMaskPtr)((vuint32)CanHwChannelData[(x)].CanBaseAddress + (vuint32)0x0880))            /* PRQA S 3453 */ /* MD_Can_3453 */
# endif
#endif

#if defined ( C_SINGLE_RECEIVE_CHANNEL )

/* Interrupt Masks */
#define CAN_INT_MASK_LO(x) kCanInterruptMaskLo
#if defined( C_ENABLE_MAX_BUFFER_64 )
# define CAN_INT_MASK_HI(x) kCanInterruptMaskHi
#endif
/* Rx FullCAN Polling and Interrupt Masks */
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
# if defined( C_ENABLE_RX_FULLCAN_POLLING )
#  define CAN_RXFULL_POLL_MASK_LO(x) kCanRxFullPollingMaskLo
#  if defined( C_ENABLE_MAX_BUFFER_64 )
#   define CAN_RXFULL_POLL_MASK_HI(x) kCanRxFullPollingMaskHi
#  endif
# endif
# if !defined( C_ENABLE_RX_FULLCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
#  define CAN_RXFULL_INT_MASK_LO(x) kCanRxFullInterruptMaskLo
#  if defined( C_ENABLE_MAX_BUFFER_64 )
#   define CAN_RXFULL_INT_MASK_HI(x) kCanRxFullInterruptMaskHi
#  endif
# endif
#endif
/* Rx BasicCAN Polling and Interrupt Masks */
#if defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && !defined( C_ENABLE_FLEXCAN_RXFIFO )
# if defined( C_ENABLE_RX_BASICCAN_POLLING )
#  define CAN_RXBASIC_POLL_MASK_LO(x) kCanRxBasicPollingMaskLo
#  if defined( C_ENABLE_MAX_BUFFER_64 )
#   define CAN_RXBASIC_POLL_MASK_HI(x) kCanRxBasicPollingMaskHi
#  endif
# endif
# if !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
#  define CAN_RXBASIC_INT_MASK_LO(x) kCanRxBasicInterruptMaskLo
#  if defined( C_ENABLE_MAX_BUFFER_64 )
#   define CAN_RXBASIC_INT_MASK_HI(x) kCanRxBasicInterruptMaskHi
#  endif
# endif
#endif
/* Tx Polling and Interrupt Masks */
#if defined( C_ENABLE_TX_POLLING )
# define CAN_TX_POLL_MASK_LO(x) kCanTxPollingMaskLo
# if defined( C_ENABLE_MAX_BUFFER_64 )
# define CAN_TX_POLL_MASK_HI(x) kCanTxPollingMaskHi
# endif
#endif
#if !defined( C_ENABLE_TX_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
# define CAN_TX_INT_MASK_LO(x) kCanTxInterruptMaskLo
# if defined( C_ENABLE_MAX_BUFFER_64 )
# define CAN_TX_INT_MASK_HI(x) kCanTxInterruptMaskHi
# endif  
#endif


#else /* C_SINGLE_RECEIVE_CHANNEL */

/* Interrupt Masks */
#define CAN_INT_MASK_LO(x) CanHwChannelData[(x)].CanInterruptMaskLo
#if defined( C_ENABLE_MAX_BUFFER_64 )
# define CAN_INT_MASK_HI(x) CanHwChannelData[(x)].CanInterruptMaskHi
#endif
/* Rx FullCAN Polling and Interrupt Masks */
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
# if defined( C_ENABLE_RX_FULLCAN_POLLING )
#  define CAN_RXFULL_POLL_MASK_LO(x) CanHwChannelData[(x)].CanRxFullPollingMaskLo
#  if defined( C_ENABLE_MAX_BUFFER_64 )
#   define CAN_RXFULL_POLL_MASK_HI(x) CanHwChannelData[(x)].CanRxFullPollingMaskHi
#  endif
# endif
# if !defined( C_ENABLE_RX_FULLCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
#  define CAN_RXFULL_INT_MASK_LO(x) CanHwChannelData[(x)].CanRxFullInterruptMaskLo
#  if defined( C_ENABLE_MAX_BUFFER_64 )
#   define CAN_RXFULL_INT_MASK_HI(x) CanHwChannelData[(x)].CanRxFullInterruptMaskHi
#  endif
# endif
#endif
/* Rx BasicCAN Polling and Interrupt Masks */
#if defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && !defined( C_ENABLE_FLEXCAN_RXFIFO )
# if defined( C_ENABLE_RX_BASICCAN_POLLING )
#  define CAN_RXBASIC_POLL_MASK_LO(x) CanHwChannelData[(x)].CanRxBasicPollingMaskLo
#  if defined( C_ENABLE_MAX_BUFFER_64 )
#   define CAN_RXBASIC_POLL_MASK_HI(x) CanHwChannelData[(x)].CanRxBasicPollingMaskHi
#  endif
# endif
# if !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
#  define CAN_RXBASIC_INT_MASK_LO(x) CanHwChannelData[(x)].CanRxBasicInterruptMaskLo
#  if defined( C_ENABLE_MAX_BUFFER_64 )
#   define CAN_RXBASIC_INT_MASK_HI(x)CanHwChannelData[(x)].CanRxBasicInterruptMaskHi
#  endif
# endif
#endif
/* Tx Polling and Interrupt Masks */
#if defined( C_ENABLE_TX_POLLING )
# define CAN_TX_POLL_MASK_LO(x) CanHwChannelData[(x)].CanTxPollingMaskLo
# if defined( C_ENABLE_MAX_BUFFER_64 )
# define CAN_TX_POLL_MASK_HI(x) CanHwChannelData[(x)].CanTxPollingMaskHi
# endif
#endif
#if !defined( C_ENABLE_TX_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
# define CAN_TX_INT_MASK_LO(x) CanHwChannelData[(x)].CanTxInterruptMaskLo
# if defined( C_ENABLE_MAX_BUFFER_64 )
# define CAN_TX_INT_MASK_HI(x) CanHwChannelData[(x)].CanTxInterruptMaskHi
# endif  
#endif

#endif /* C_SINGLE_RECEIVE_CHANNEL */

/* support reading the error counters */
#if defined( C_SINGLE_RECEIVE_CHANNEL )
#  if defined( C_ENABLE_UPDATE_BASE_ADDRESS )
#   define CanRxActualErrorCounter()   ((vuint8)(((tFlexcanPtr)canLL_VirtualPtrField[0])->rxectr))
#   define CanTxActualErrorCounter()   ((vuint8)(((tFlexcanPtr)canLL_VirtualPtrField[0])->txectr))
#  else
#   define CanRxActualErrorCounter()   ((vuint8)(pFlexCAN(0)->rxectr))
#   define CanTxActualErrorCounter()   ((vuint8)(pFlexCAN(0)->txectr))
#  endif
#else
#   if defined( C_ENABLE_UPDATE_BASE_ADDRESS )
#    define CanRxActualErrorCounter(x)  ((vuint8)(((tFlexcanPtr)canLL_VirtualPtrField[(x)])->rxectr))
#    define CanTxActualErrorCounter(x)  ((vuint8)(((tFlexcanPtr)canLL_VirtualPtrField[(x)])->txectr))
#   else
#    define CanRxActualErrorCounter(x)  ((vuint8)(pFlexCAN(x)->rxectr))
#    define CanTxActualErrorCounter(x)  ((vuint8)(pFlexCAN(x)->txectr))
#   endif
#endif


# define CANSFR_TYPE        vuint32
# define CANSFR_CAST       (vuint32)

typedef struct 
{
  CanChipDataPtr     pChipData;
  CanTransmitHandle  Handle;
/* CPU-specific part */
  CanChipMsgPtr   pChipMsgObj;
} tCanTxInfoStruct;

/* ##RI-1.10 Common Callbackfunction in TxInterrupt */
typedef struct 
{
  CanChannelHandle   Channel;
  CanTransmitHandle  Handle;
/* CPU-specific part */
  CanChipDataPtr  pChipData;
  CanChipMsgPtr   pChipMsgObj;
} tCanTxConfInfoStruct;

typedef struct 
{
  CanChannelHandle  Channel;
  CanChipMsgPtr     pChipMsgObj;
  CanChipDataPtr    pChipData;
  CanReceiveHandle  Handle;
/* CPU-specific part */
} tCanRxInfoStruct;

typedef tCanRxInfoStruct          *CanRxInfoStructPtr;
typedef tCanTxInfoStruct          CanTxInfoStruct;
/* ##RI-1.10 Common Callbackfunction in TxInterrupt */
typedef tCanTxConfInfoStruct      *CanTxInfoStructPtr;

/* types of application functions called by driver --------------------------- */
typedef C_CALLBACK_1 vuint8   (C_CALLBACK_2 *ApplCanMsgRcvFct)    (CanRxInfoStructPtr rxStruct);
typedef C_CALLBACK_1 vuint8   (C_CALLBACK_2 *ApplRangeFct)        (CanRxInfoStructPtr rxStruct);
typedef C_CALLBACK_1 vuint8   (C_CALLBACK_2 *ApplPrecopyFct)      (CanRxInfoStructPtr rxStruct);
typedef C_CALLBACK_1 void     (C_CALLBACK_2 *ApplIndicationFct)   (CanReceiveHandle rxObject);
typedef C_CALLBACK_1 void     (C_CALLBACK_2 *ApplConfirmationFct) (CanTransmitHandle txObject);
typedef C_CALLBACK_1 vuint8   (C_CALLBACK_2 *ApplPreTransmitFct)  (CanTxInfoStruct txStruct);
typedef C_CALLBACK_1 void     (C_CALLBACK_2 *ApplChannelFct)      (CAN_CHANNEL_CANTYPE_ONLY);

typedef struct
{
  tCanRxId0           Id0;
# if (kCanNumberOfUsedCanRxIdTables > 1)
  tCanRxId1           Id1;
# endif
# if (kCanNumberOfUsedCanRxIdTables > 2)
  tCanRxId2           Id2;
# endif     
# if (kCanNumberOfUsedCanRxIdTables > 3)
  tCanRxId3           Id3;
# endif
# if (kCanNumberOfUsedCanRxIdTables > 4)
  tCanRxId4           Id4;
# endif
} tCanStructRxIdType;

# if defined( C_DRV_INTERNAL )
typedef struct
{
  ApplChannelFct      ApplCanWakeUpFct; 
  ApplCanMsgRcvFct    ApplCanMsgReceivedFct;
  ApplRangeFct        ApplCanRangeFct[4];
  ApplChannelFct      ApplCanBusOffFct;
  ApplConfirmationFct ApplCanCancelNotificationFct;
  ApplChannelFct      ApplCanMsgTransmitCancelNotifyFct;
  tCanStructRxIdType  RangeMask[4];
  tCanStructRxIdType  RangeCode[4];
  vuint16             RangeActiveFlag;
  tCanIdType          RangeIdType[4];
} tCanChannelObject;
# endif


/* datatypes for indication and confirmation flags */
# if defined( C_ENABLE_CONFIRMATION_FLAG )
union CanConfirmationBits                                 
{    /* PRQA S 0750 */
  vuint8         _c[kCanNumberOfConfBytes];
#  if defined( V_CPUTYPE_BITARRAY_32BIT )
#   if kCanNumberOfConfFlags > 16
  struct _c_bits32 w[kCanNumberOfConfDWords];
#   elif kCanNumberOfConfFlags > 8
  struct _c_bits16 w[kCanNumberOfConfWords];
#   else
  struct _c_bits8  w[1];
#   endif
#  else
#   if kCanNumberOfConfFlags > 8
  struct _c_bits16 w[kCanNumberOfConfWords];
#   else
  struct _c_bits8  w[1];
#   endif
#  endif
}; 
# endif


# if defined( C_ENABLE_INDICATION_FLAG )
union CanIndicationBits                                  
{    /* PRQA S 0750 */
  vuint8         _c[kCanNumberOfIndBytes];
#  if defined( V_CPUTYPE_BITARRAY_32BIT )
#   if kCanNumberOfIndFlags > 16
  struct _c_bits32 w[kCanNumberOfIndDWords];
#   elif kCanNumberOfIndFlags > 8
  struct _c_bits16 w[kCanNumberOfIndWords];
#   else
  struct _c_bits8  w[1];
#   endif
#  else
#   if kCanNumberOfIndFlags > 8
  struct _c_bits16 w[kCanNumberOfIndWords];
#   else
  struct _c_bits8 w[1];
#   endif
#  endif
};
# endif

# if defined( C_ENABLE_RX_QUEUE )
/* struct for receive-Queue. Should correspond to t_MsgObject */
typedef struct
{
  CanReceiveHandle      Handle;
  CanChannelHandle      Channel;
  tCanMsgTransmitStruct CanChipMsgObj;
}
tCanRxQueueObject;

/* the queue */
typedef struct 
{
  tCanRxQueueObject canRxQueueBuf[kCanRxQueueSize];  /* buffer for msg and handle */  
  volatile vuintx   canRxQueueWriteIndex;            /* index in canRxQueueBuf */
  volatile vuintx   canRxQueueReadIndex;             /* index in canRxQueueBuf */
  volatile vuintx   canRxQueueCount;                 /* count of messages in canRxQueueBuf  */   
}
tCanRxQueue;
# endif


/* *********************************************************************** */
/* External Declarations                                                   */
/* *********************************************************************** */

/*  CAN driver version */
/* ROM CATEGORY 4 START */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kCanMainVersion;
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kCanSubVersion;
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kCanBugFixVersion;
/* ROM CATEGORY 4 END */



# if defined( C_ENABLE_PRECOPY_FCT )
/* RAM CATEGORY 1 START */
extern volatile CanReceiveHandle canRxHandle[kCanNumberOfChannels];
/* RAM CATEGORY 1 END */
# endif

# if defined( C_ENABLE_CONFIRMATION_FLAG )
/* RAM CATEGORY 1 START */
V_MEMRAM0 extern volatile V_MEMRAM1_NEAR union CanConfirmationBits V_MEMRAM2_NEAR CanConfirmationFlags;              /* PRQA S 0759 */
/* RAM CATEGORY 1 END */
# endif

# if defined( C_ENABLE_INDICATION_FLAG )
/* RAM CATEGORY 1 START */
V_MEMRAM0 extern volatile V_MEMRAM1_NEAR union CanIndicationBits   V_MEMRAM2_NEAR CanIndicationFlags;                /* PRQA S 0759 */
/* RAM CATEGORY 1 END */
# endif


# if defined( C_ENABLE_CONFIRMATION_FCT ) && \
    defined( C_ENABLE_DYN_TX_OBJECTS )  && \
    defined( C_ENABLE_TRANSMIT_QUEUE )
/* RAM CATEGORY 3 START */
extern CanTransmitHandle          confirmHandle[kCanNumberOfChannels];
/* RAM CATEGORY 3 END */
# endif

/* ##RI1.4 - 3.31: Dynamic Receive DLC */
# if defined( C_ENABLE_VARIABLE_RX_DATALEN )
#  if ( kCanNumberOfRxObjects > 0 )
/* RAM CATEGORY 1 START */
extern volatile vuint8 canVariableRxDataLen[kCanNumberOfRxObjects];
/* RAM CATEGORY 1 END */
#  endif
# endif

/* RAM CATEGORY 1 START */
extern CanChipDataPtr canRDSRxPtr[kCanNumberOfChannels];
/* RAM CATEGORY 1 END */
/* RAM CATEGORY 1 START */
extern CanChipDataPtr canRDSTxPtr[kCanNumberOfUsedTxCANObjects];
/* RAM CATEGORY 1 END */



#if defined( C_CAN_MAX_BUFFER_MIXED )
/* ROM CATEGORY 1 START*/ 
V_DEF_CONST(extern, vuint8, CONST) CanMaxMB[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END*/ 
#endif
#if defined( C_SINGLE_RECEIVE_CHANNEL )
#else
/* ROM CATEGORY 1 START*/
V_DEF_CONST(extern, tCanHwChannelData, CONST_PBCFG) CanHwChannelData[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END*/ 
#endif
#if defined( C_ENABLE_UPDATE_BASE_ADDRESS )
/* RAM CATEGORY 1 START*/
V_DEF_P2VAR(extern, vuint32, VAR_NOINIT, REG_CANCELL) canLL_VirtualPtrField[kCanNumberOfHwChannels];
/* RAM CATEGORY 1 END*/
#endif

/* *********************************************************************** */
/* Data structures filled with data by parameter generating tool           */
/* *********************************************************************** */

# if defined( C_DRV_INTERNAL )
/* structures for init and common objects ----------------------- */
#  if defined( C_SINGLE_RECEIVE_CHANNEL )
#  else
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 tCanChannelObject   V_MEMROM2 CanChannelObject[kCanNumberOfChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 4 START */
V_MEMROM0 extern V_MEMROM1 vuint8              V_MEMROM2 CanInitObjectStartIndex[kCanNumberOfChannels+1];
/* ROM CATEGORY 4 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanTransmitHandle   V_MEMROM2 CanTxDynRomStartIndex[kCanNumberOfChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanTransmitHandle   V_MEMROM2 CanTxDynRamStartIndex[kCanNumberOfChannels+1];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle    V_MEMROM2 CanRxBasicStartIndex[kCanNumberOfChannels+1];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle    V_MEMROM2 CanRxFullStartIndex[kCanNumberOfHwChannels+1];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 2 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanLogHwTxStartIndex[kCanNumberOfHwChannels+1];
/* ROM CATEGORY 2 END */

/* ROM CATEGORY 2 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanHwTxStartIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 2 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanHwRxFullStartIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanHwRxBasicStartIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 4 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanHwUnusedStartIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 4 END */
/* ROM CATEGORY 2 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanHwTxStopIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 2 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanHwRxFullStopIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanHwRxBasicStopIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 4 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanHwUnusedStopIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 4 END */

/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanHwMsgTransmitIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanObjectHandle     V_MEMROM2 CanHwTxNormalIndex[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END */
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 vsintx              V_MEMROM2 CanTxOffsetHwToLog[kCanNumberOfHwChannels];
/* ROM CATEGORY 1 END */


#  endif  /* C_SINGLE_RECEIVE_CHANNEL */




#  if defined( C_ENABLE_INDIVIDUAL_POLLING )
/* ROM CATEGORY 1 START */
/* define first index to array CanHwObjIndivPolling[][] */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2     CanHwObjIndivPolling[kCanNumberOfHwChannels][kCanNumberOfHwObjIndivPolling];
/* ROM CATEGORY 1 END */
#  endif

# endif /* C_DRV_INTERNAL */

# if defined( C_SINGLE_RECEIVE_CHANNEL )
# else
/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 CanTransmitHandle   V_MEMROM2 CanTxStartIndex[kCanNumberOfChannels+1];
/* ROM CATEGORY 1 END */ 
/* ROM CATEGORY 2 START */ 
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle    V_MEMROM2 CanRxStartIndex[kCanNumberOfChannels+1];
/* ROM CATEGORY 2 END */
# endif

/* ROM generated */

# if ( kCanNumberOfTxObjects > 0 )
#   if defined( C_DRV_INTERNAL )
/* structures for transmit objects ----------------------- */
/* ROM CATEGORY 1 START */ 
V_MEMROM0 extern V_MEMROM1 tCanTxId0 V_MEMROM2       CanTxId0[kCanNumberOfTxObjects];  
#    if (kCanNumberOfUsedCanTxIdTables > 1)
V_MEMROM0 extern V_MEMROM1 tCanTxId1 V_MEMROM2       CanTxId1[kCanNumberOfTxObjects];  
#    endif
#    if (kCanNumberOfUsedCanTxIdTables > 2)
V_MEMROM0 extern V_MEMROM1 tCanTxId2 V_MEMROM2       CanTxId2[kCanNumberOfTxObjects];  
#    endif
#    if (kCanNumberOfUsedCanTxIdTables > 3)
V_MEMROM0 extern V_MEMROM1 tCanTxId3 V_MEMROM2       CanTxId3[kCanNumberOfTxObjects];  
#    endif
#    if (kCanNumberOfUsedCanTxIdTables > 4)
V_MEMROM0 extern V_MEMROM1 tCanTxId4 V_MEMROM2       CanTxId4[kCanNumberOfTxObjects];  
#    endif

#    if defined( C_ENABLE_MIXED_ID )
#    endif
/* ROM CATEGORY 1 END */
#   endif /* C_DRV_INTERNAL */

/* ROM CATEGORY 2 START */
#   if defined( C_ENABLE_PART_OFFLINE )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2          CanTxSendMask[kCanNumberOfTxObjects];
#   endif
/* ROM CATEGORY 2 END */

/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2          CanTxDLC[kCanNumberOfTxObjects];
V_MEMROM0 extern V_MEMROM1 TxDataPtr V_MEMROM2       CanTxDataPtr[kCanNumberOfTxObjects];

#   if defined( C_ENABLE_CONFIRMATION_FLAG )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2          CanConfirmationOffset[kCanNumberOfTxObjects];
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2          CanConfirmationMask[kCanNumberOfTxObjects];
#   endif
#   if defined( C_ENABLE_CONFIRMATION_FCT )
V_MEMROM0 extern V_MEMROM1 ApplConfirmationFct V_MEMROM2 CanTxApplConfirmationPtr[kCanNumberOfTxObjects];
#   endif
#   if defined( C_ENABLE_PRETRANSMIT_FCT )
V_MEMROM0 extern V_MEMROM1 ApplPreTransmitFct  V_MEMROM2 CanTxApplPreTransmitPtr[kCanNumberOfTxObjects];
#   endif
/* ROM CATEGORY 1 END */

#   if defined( C_ENABLE_TX_FULLCAN_OBJECTS )
/* ROM CATEGORY 2 START */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2          CanTxHwObj[kCanNumberOfTxObjects];
/* ROM CATEGORY 2 END */
#   endif

#   if defined( C_SINGLE_RECEIVE_CHANNEL )
#   else
#    if ( kCanNumberOfTxObjects > 0 )
/* ROM CATEGORY 2 START */
V_MEMROM0 extern V_MEMROM1 CanChannelHandle    V_MEMROM2 CanTxMsgHandleToChannel[kCanNumberOfTxObjects];
/* ROM CATEGORY 2 END */
#    endif
#   endif /* C_SINGLE_RECEIVE_CHANNEL */ 

#   if defined( C_ENABLE_MULTI_ECU_PHYS )
/* ROM CATEGORY 4 START */
V_MEMROM0 extern V_MEMROM1 tVIdentityMsk V_MEMROM2      CanTxIdentityAssignment[kCanNumberOfTxObjects];
/* ROM CATEGORY 4 END */
#   endif


#  if defined( C_ENABLE_TRANSMIT_QUEUE )
#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
/* ROM CATEGORY 1 START */
/* pad bits added before the current channel position */
V_MEMROM0 extern  V_MEMROM1 tCanTxQueuePadBits V_MEMROM2 CanTxQueuePadBits[kCanNumberOfChannels];

/* start / stop indices for the element search */
V_MEMROM0 extern V_MEMROM1 CanSignedTxHandle V_MEMROM2 CanTxQueueStartIndex[kCanNumberOfChannels + 1];
/* ROM CATEGORY 1 END */
#endif
#  endif

# endif /* ( kCanNumberOfTxObjects > 0 ) */

/* structures for basic and full can receive objects ----------------------- */

# if ( kCanNumberOfRxObjects > 0 )
#  if defined( C_DRV_INTERNAL )
/* ROM CATEGORY 1 START */
#   if defined( C_SEARCH_HASH ) ||\
      defined( C_SEARCH_INDEX )
#    if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
V_MEMROM0 extern V_MEMROM1 tCanRxId0 V_MEMROM2       CanRxId0[kCanNumberOfRxFullCANObjects];  
#     if (kCanNumberOfUsedCanRxIdTables > 1)
V_MEMROM0 extern V_MEMROM1 tCanRxId1 V_MEMROM2       CanRxId1[kCanNumberOfRxFullCANObjects];  
#     endif
#     if (kCanNumberOfUsedCanRxIdTables > 2)
V_MEMROM0 extern V_MEMROM1 tCanRxId2 V_MEMROM2       CanRxId2[kCanNumberOfRxFullCANObjects];  
#     endif
#     if (kCanNumberOfUsedCanRxIdTables > 3)
V_MEMROM0 extern V_MEMROM1 tCanRxId3 V_MEMROM2       CanRxId3[kCanNumberOfRxFullCANObjects];  
#     endif
#     if (kCanNumberOfUsedCanRxIdTables > 4)
V_MEMROM0 extern V_MEMROM1 tCanRxId4 V_MEMROM2       CanRxId4[kCanNumberOfRxFullCANObjects];  
#     endif

#     if defined( C_ENABLE_MIXED_ID )
V_MEMROM0 extern V_MEMROM1 tCanIdType V_MEMROM2      CanRxIdType[kCanNumberOfRxFullCANObjects];
#     endif
#    endif /* C_ENABLE_RX_FULLCAN_OBJECTS */
#   else   /* C_SEARCH_HASH */
V_MEMROM0 extern V_MEMROM1 tCanRxId0 V_MEMROM2       CanRxId0[kCanNumberOfRxObjects];  
#    if (kCanNumberOfUsedCanRxIdTables > 1)
V_MEMROM0 extern V_MEMROM1 tCanRxId1 V_MEMROM2       CanRxId1[kCanNumberOfRxObjects];  
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 2)
V_MEMROM0 extern V_MEMROM1 tCanRxId2 V_MEMROM2       CanRxId2[kCanNumberOfRxObjects];  
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 3)
V_MEMROM0 extern V_MEMROM1 tCanRxId3 V_MEMROM2       CanRxId3[kCanNumberOfRxObjects];  
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 4)
V_MEMROM0 extern V_MEMROM1 tCanRxId4 V_MEMROM2       CanRxId4[kCanNumberOfRxObjects];  
#    endif

#    if defined( C_ENABLE_MIXED_ID )
V_MEMROM0 extern V_MEMROM1 tCanIdType V_MEMROM2      CanRxIdType[kCanNumberOfRxObjects];
#    endif
#   endif  /* C_SEARCH_HASH */


#   if defined( C_SEARCH_HASH )
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle V_MEMROM2     CanRxMsgIndirection[kHashSearchListCount + kHashSearchListCountEx + kCanNumberOfRxFullCANObjects];
#   else
#    if defined( C_SEARCH_INDEX )
 /*  Size of array CanRxMsgIndirection is zero if index search and no Rx FullCANs are used; ESCAN00059562 */
#     if defined (C_ENABLE_RX_FULLCAN_OBJECTS)
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle V_MEMROM2     CanRxMsgIndirection[kCanNumberOfRxFullCANObjects];
#     endif
#    else
#     if defined( C_ENABLE_RX_MSG_INDIRECTION )
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle V_MEMROM2     CanRxMsgIndirection[kCanNumberOfRxObjects];
#     endif
#    endif
#   endif

#   if defined( C_SEARCH_HASH )
#    if defined( C_ENABLE_EXTENDED_ID )
#     if( kHashSearchListCountEx > 0)
V_MEMROM0 extern V_MEMROM1 vuint32 V_MEMROM2              CanRxHashIdEx[kHashSearchListCountEx];
#     endif /* (kHashSearchListCountEx > 0) */
#     if defined( C_ENABLE_MIXED_ID )
#      if( kHashSearchListCount > 0)
V_MEMROM0 extern V_MEMROM1 vuint16 V_MEMROM2              CanRxHashId[kHashSearchListCount];
#      endif
#     endif
#    else
#     if( kHashSearchListCount > 0)
V_MEMROM0 extern V_MEMROM1 vuint16 V_MEMROM2              CanRxHashId[kHashSearchListCount];
#     endif 
#    endif
#   endif

#   if defined( C_SEARCH_INDEX )
#    if defined( C_SINGLE_RECEIVE_CHANNEL )
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle V_MEMROM2     CanRxIndexTbl[2048];
#    else
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle V_MEMROM2     CanRxIndexTbl[kCanNumberOfChannels][2048];
#    endif
#   endif
#   if defined( C_ENABLE_MULTI_ECU_PHYS )
V_MEMROM0 extern V_MEMROM1 tVIdentityMsk V_MEMROM2           CanRxIdentityAssignment[kCanNumberOfRxObjects];
#   endif

#   if defined( C_ENABLE_RX_QUEUE_RANGE )
#    if defined( C_ENABLE_RANGE_0 )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2               CanRxQueueRange0[kCanNumberOfChannels];
#    endif
#    if defined( C_ENABLE_RANGE_1 )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2               CanRxQueueRange1[kCanNumberOfChannels];
#    endif
#    if defined( C_ENABLE_RANGE_2 )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2               CanRxQueueRange2[kCanNumberOfChannels];
#    endif
#    if defined( C_ENABLE_RANGE_3 )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2               CanRxQueueRange3[kCanNumberOfChannels];
#    endif
#   endif
/* ROM CATEGORY 1 END */

/* ROM CATEGORY 4 START */
#   if defined( C_ENABLE_MULTIPLE_BASICCAN ) && \
       defined( C_ENABLE_GEN_CHECK )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2               CanNumberOfBasicCAN[kCanNumberOfChannels];
#   endif
/* ROM CATEGORY 4 END */

#  endif /* C_DRV_INTERNAL */

/* ROM CATEGORY 1 START */
V_MEMROM0 extern V_MEMROM1 vuint8               V_MEMROM2 CanRxDataLen[kCanNumberOfRxObjects];
#   if defined( C_ENABLE_DLC_CHECK_MIN_DATALEN )
V_MEMROM0 extern V_MEMROM1 vuint8               V_MEMROM2 CanRxMinDataLen[kCanNumberOfRxObjects];
#   endif
V_MEMROM0 extern V_MEMROM1 RxDataPtr            V_MEMROM2 CanRxDataPtr[kCanNumberOfRxObjects];

#   if defined( C_ENABLE_PRECOPY_FCT )
V_MEMROM0 extern V_MEMROM1 ApplPrecopyFct       V_MEMROM2 CanRxApplPrecopyPtr[kCanNumberOfRxObjects];
#   endif
#   if defined( C_ENABLE_INDICATION_FLAG )
V_MEMROM0 extern V_MEMROM1 vuint8               V_MEMROM2 CanIndicationOffset[kCanNumberOfRxObjects];
V_MEMROM0 extern V_MEMROM1 vuint8               V_MEMROM2 CanIndicationMask[kCanNumberOfRxObjects];
#   endif
#   if defined( C_ENABLE_INDICATION_FCT )
V_MEMROM0 extern V_MEMROM1 ApplIndicationFct    V_MEMROM2 CanRxApplIndicationPtr[kCanNumberOfRxObjects];
#   endif
/* ROM CATEGORY 1 END */
# endif /* ( kCanNumberOfRxObjects > 0 ) */


/* structure used on initialization CAN chip -------------------------------*/
/* ROM CATEGORY 4 START*/
V_DEF_CONST(extern, tCanInitObject, CONST) CanInitObject[kCanNumberOfInitObjects];
/* ROM CATEGORY 4 END*/
#if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
/* ROM CATEGORY 4 START*/
V_DEF_CONST(extern, tCanInitBasicCan, CONST) CanInitBasicCan[kCanNumberOfInitObjects][kCanNumberOfRxBasicMasks];
/* ROM CATEGORY 4 END*/
#endif


/* *********************************************************************** */
/* Callback functions                                                      */
/* *********************************************************************** */

# if defined( C_ENABLE_INTCTRL_ADD_CAN_FCT )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanAddCanInterruptRestore(CanChannelHandle channel) C_API_3;
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanAddCanInterruptDisable(CanChannelHandle channel) C_API_3;
/* CODE CATEGORY 1 END */
# endif

# if defined( C_ENABLE_HARDWARE_CHECK ) || \
    defined( C_ENABLE_USER_CHECK )     || \
    defined( C_ENABLE_GEN_CHECK )      || \
    defined( C_ENABLE_INTERNAL_CHECK ) 
/* CODE CATEGORY 4 START */ 
C_CALLBACK_1 void C_CALLBACK_2 ApplCanFatalError(CAN_CHANNEL_CANTYPE_FIRST vuint8 errorNumber) C_API_3;
/* CODE CATEGORY 4 END */
# endif

# if defined( C_SINGLE_RECEIVE_CHANNEL )
/* these two functions are declared by the tool in case of multichannel */
/* CODE CATEGORY 4 START */ 
C_CALLBACK_1 void C_CALLBACK_2 ApplCanBusOff(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */ 
C_CALLBACK_1 void C_CALLBACK_2 ApplCanWakeUp(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
# endif
# if defined( C_ENABLE_APPLCANPREWAKEUP_FCT )
/* CODE CATEGORY 4 START */ 
C_CALLBACK_1 void C_CALLBACK_2 ApplCanPreWakeUp(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
# endif
# if defined( C_ENABLE_OVERRUN )
/* CODE CATEGORY 4 START */ 
C_CALLBACK_1 void C_CALLBACK_2 ApplCanOverrun ( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
# endif
# if defined( C_ENABLE_FULLCAN_OVERRUN )
/* CODE CATEGORY 4 START */ 
C_CALLBACK_1 void C_CALLBACK_2 ApplCanFullCanOverrun ( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
# endif

/* Range precopy/ generic precopy functions ****************************** */
# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  if defined( C_ENABLE_RANGE_0 )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanRange0Precopy( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
#  endif
#  if defined( C_ENABLE_RANGE_1 )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanRange1Precopy( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
#  endif
#  if defined( C_ENABLE_RANGE_2 )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanRange2Precopy( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
#  endif
#  if defined( C_ENABLE_RANGE_3 )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanRange3Precopy( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
#  endif
# endif

# if defined( C_ENABLE_COND_RECEIVE_FCT )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanMsgCondReceived  ( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
# endif

# if defined( C_ENABLE_CAN_RAM_CHECK )
#  if defined( C_ENABLE_NOTIFY_CORRUPT_MAILBOX )
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanCorruptMailbox(CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle hwObjHandle);
/* CODE CATEGORY 4 END */
#  endif  /* defined( C_ENABLE_NOTIFY_CORRUPT_MAILBOX ) */
/* CODE CATEGORY 4 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanMemCheckFailed(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
# endif  /* defined ( C_ENABLE_CAN_RAM_CHECK ) */

# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  if defined( C_ENABLE_RECEIVE_FCT )
/* in case of multiple CAN channels this function is declared by the tool */
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 APPL_CAN_MSGRECEIVED(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */
#  endif
# endif

/* ##RI1.4 - 2.7: Callbackfunction-DLC-Check */
# if defined( C_ENABLE_DLC_FAILED_FCT )
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanMsgDlcFailed( CanRxInfoStructPtr rxStruct ); 
/* CODE CATEGORY 4 END */ 
# endif  /* C_ENABLE_DLC_FAILED_FCT */

# if defined( C_ENABLE_GENERIC_PRECOPY )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 APPL_CAN_GENERIC_PRECOPY( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
# endif

# if defined( C_ENABLE_NOT_MATCHED_FCT )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanMsgNotMatched( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
# endif

# if defined( C_ENABLE_CAN_TX_CONF_FCT )
/* ##RI-1.10 Common Callbackfunction in TxInterrupt */
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 APPL_CAN_TX_CONFIRMATION(CanTxInfoStructPtr txStruct);
/* CODE CATEGORY 1 END */
# endif

# if defined( C_ENABLE_TX_OBSERVE )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanTxObjStart( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txHwObject );
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanTxObjConfirmed( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txHwObject );
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanInit( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txHwObjectFirstUsed, CanObjectHandle txHwObjectFirstUnused);
/* CODE CATEGORY 4 END */
# endif

# if defined( C_ENABLE_HW_LOOP_TIMER )
/* CODE CATEGORY 2 START */
C_CALLBACK_1 void     C_CALLBACK_2 ApplCanTimerStart(CAN_CHANNEL_CANTYPE_FIRST vuint8 source);
/* CODE CATEGORY 2 END */
/* CODE CATEGORY 2 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanTimerLoop (CAN_CHANNEL_CANTYPE_FIRST vuint8 source);
/* CODE CATEGORY 2 END */
/* CODE CATEGORY 2 START */
C_CALLBACK_1 void     C_CALLBACK_2 ApplCanTimerEnd  (CAN_CHANNEL_CANTYPE_FIRST vuint8 source);
/* CODE CATEGORY 2 END */
# endif

# if defined( C_ENABLE_MSG_TRANSMIT_CONF_FCT )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 APPL_CAN_MSGTRANSMITCONF(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 APPL_CAN_MSGTRANSMITINIT(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
# endif

# if defined( C_SINGLE_RECEIVE_CHANNEL )
/* in case of multichannel these two functions are declared by the tool */
#  if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
/* CODE CATEGORY 3 START */
C_CALLBACK_1 void C_CALLBACK_2 APPL_CAN_CANCELNOTIFICATION( CanTransmitHandle txHandle );
/* CODE CATEGORY 3 END */
#  endif
#  if defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
/* CODE CATEGORY 3 START */
C_CALLBACK_1 void C_CALLBACK_2 APPL_CAN_MSGCANCELNOTIFICATION( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 3 END */
#  endif
# endif

# if defined( C_ENABLE_RX_QUEUE )
#  if defined( C_ENABLE_APPLCANPRERXQUEUE )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanPreRxQueue( CanRxInfoStructPtr pCanRxInfoStruct );
/* CODE CATEGORY 1 END */
#  endif
#  if defined( C_ENABLE_RXQUEUE_OVERRUN_NOTIFY )
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanRxQueueOverrun( void );
/* CODE CATEGORY 4 END */
#  endif
# endif

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
/* CODE CATEGORY 3 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanChannelDummy( CanChannelHandle channel );
/* CODE CATEGORY 3 END */
# endif
# if defined( C_MULTIPLE_RECEIVE_CHANNEL ) || \
    defined( C_HL_ENABLE_DUMMY_FCT_CALL )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanTxHandleDummy( CanTransmitHandle txHandle );
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanRxStructPtrDummy( CanRxInfoStructPtr rxStruct );
/* CODE CATEGORY 1 END */
# endif
# if defined( C_HL_ENABLE_DUMMY_FCT_CALL )
/* CODE CATEGORY 1 START */
C_CALLBACK_1 void C_CALLBACK_2 ApplCanRxHandleDummy( CanReceiveHandle rxHandle );
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
C_CALLBACK_1 vuint8 C_CALLBACK_2 ApplCanTxStructDummy( CanTxInfoStruct txStruct );
/* CODE CATEGORY 1 END */
# endif
# if defined( C_ENABLE_ONLINE_OFFLINE_CALLBACK_FCT )
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 APPL_CAN_OFFLINE( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_CALLBACK_1 void C_CALLBACK_2 APPL_CAN_ONLINE( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
# endif

# if defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL) &&\
     defined (C_ENABLE_OSEK_CAN_INTCTRL)
/* CODE CATEGORY 1 START */
C_API_1 void C_API_2 OsCanCanInterruptDisable( CAN_HW_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
C_API_1 void C_API_2 OsCanCanInterruptRestore( CAN_HW_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 1 END */
# endif

#if defined( C_ENABLE_UPDATE_BASE_ADDRESS )
/* CODE CATEGORY 4 START*/
V_DEF_FUNC_CBK(V_NONE, void*, APPL_CODE) ApplCanPowerOnGetBaseAddress(vuint32 physAddr, vuint16 size);
/* CODE CATEGORY 4 END*/
/* CODE CATEGORY 4 START*/
V_DEF_FUNC_CBK(V_NONE, void*, APPL_CODE) ApplCanGetBaseAddress(vuint32 physAddr, vuint16 size);
/* CODE CATEGORY 4 END*/
#endif
#if defined ( C_ENABLE_USER_MODE_APPL )
/* CODE CATEGORY 4 START*/
V_DEF_FUNC_CBK(V_NONE, vuint16, APPL_CODE) ApplCanReadProtectedRegister(V_DEF_P2VAR_PARA(volatile, vuint16, AUTOMATIC, APPL_VAR) addr);
/* CODE CATEGORY 4 END*/
/* CODE CATEGORY 4 START*/
V_DEF_FUNC_CBK(V_NONE, void, APPL_CODE) ApplCanWriteProtectedRegister(V_DEF_P2VAR_PARA(volatile, vuint16, AUTOMATIC, APPL_VAR) addr, vuint16 mask, vuint16 val);
/* CODE CATEGORY 4 END*/
#endif
#if defined( C_ENABLE_SLEEP_WAKEUP )
# if defined( C_ENABLE_FLEXCAN_DOZE_MODE )
/* CODE CATEGORY 4 START */ 
V_DEF_FUNC_API(V_NONE, vuint8, APPL_CODE) Appl_CanSleep(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
# endif /* C_ENABLE_FLEXCAN_DOZE_MODE */
#endif /* C_ENABLE_SLEEP_WAKEUP */


/* *********************************************************************** */
/* function prototypes                                                     */
/* *********************************************************************** */

/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanInitPowerOn( void );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanInit( CAN_CHANNEL_CANTYPE_FIRST CanInitHandle initObject );
/* CODE CATEGORY 4 END */

# if defined( C_ENABLE_CAN_TRANSMIT )
/* CODE CATEGORY 2 START */
C_API_1 vuint8 C_API_2 CanTransmit(CanTransmitHandle txHandle) C_API_3;
/* CODE CATEGORY 2 END */
#  if defined( C_ENABLE_VARIABLE_DLC )
/* CODE CATEGORY 2 START */
C_API_1 vuint8 C_API_2 CanTransmitVarDLC( CanTransmitHandle txHandle, vuint8 dlc) C_API_3;
/* CODE CATEGORY 2 END */
#  endif
/* CODE CATEGORY 3 START */
C_API_1 void C_API_2 CanCancelTransmit( CanTransmitHandle txHandle );
/* CODE CATEGORY 3 END */
# endif

# if defined( C_ENABLE_MSG_TRANSMIT )
/* CODE CATEGORY 2 START */

# if defined ( V_ENABLE_USED_GLOBAL_VAR )
/* txMsgStruct is located in far memory */
C_API_1 vuint8 C_API_2 CanMsgTransmit( CAN_CHANNEL_CANTYPE_FIRST V_MEMRAM1_FAR tCanMsgTransmitStruct V_MEMRAM2_FAR V_MEMRAM3_FAR *txMsgStruct );
# else
C_API_1 vuint8 C_API_2 CanMsgTransmit( CAN_CHANNEL_CANTYPE_FIRST tCanMsgTransmitStruct *txMsgStruct);
# endif

/* CODE CATEGORY 2 END */
#  if defined( C_ENABLE_MSG_TRANSMIT_CONF_FCT )
/* CODE CATEGORY 3 START */
C_API_1 void C_API_2 CanCancelMsgTransmit( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 3 END */
#  endif
# endif

# if defined( C_ENABLE_OFFLINE )
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanOnline( CAN_CHANNEL_CANTYPE_ONLY );           /* switch CanStatus to On */
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanOffline( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 4 END */
# endif

# if defined( C_ENABLE_PART_OFFLINE )
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetPartOffline( CAN_CHANNEL_CANTYPE_FIRST vuint8 sendGroup);
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetPartOnline( CAN_CHANNEL_CANTYPE_FIRST vuint8 invSendGroup);
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanGetPartMode( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
# endif

/* CODE CATEGORY 3 START */
C_API_1 vuint8 C_API_2 CanGetStatus( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 3 END */

/* CanSleep functions */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanSleep( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanWakeUp( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */

# if defined( C_ENABLE_ECU_SWITCH_PASS )
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetActive(  CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetPassive( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
# else
#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
#   define    CanSetActive( channel )            /* remove calls to setActive/Passive */
#   define    CanSetPassive( channel )
#  else
#   define    CanSetActive( )                    /* remove calls to setActive/Passive */
#   define    CanSetPassive( )
#  endif
# endif

# if defined( C_ENABLE_STOP )
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanStart( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanStop( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 4 END */
# endif

# if defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL)
/* CODE CATEGORY 1 START */
C_API_1 void C_API_2 CanCanInterruptDisable( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
C_API_1 void C_API_2 CanCanInterruptRestore( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 1 END */
# endif

# if defined( C_ENABLE_TX_POLLING ) || \
    defined( C_ENABLE_RX_FULLCAN_POLLING )  || \
    defined( C_ENABLE_RX_BASICCAN_POLLING ) || \
    defined( C_ENABLE_ERROR_POLLING ) || \
    defined( C_ENABLE_WAKEUP_POLLING ) || \
    (defined( C_HL_ENABLE_CANCEL_IN_HW_TASK ) && defined( C_ENABLE_CANCEL_IN_HW ))
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanTask(void);
/* CODE CATEGORY 2 END */
# endif
# if defined( C_ENABLE_TX_POLLING ) || \
    (defined( C_HL_ENABLE_CANCEL_IN_HW_TASK )  && defined( C_ENABLE_CANCEL_IN_HW ))
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanTxTask( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 2 END */
# endif
# if defined( C_ENABLE_TX_POLLING ) && \
     defined( C_ENABLE_INDIVIDUAL_POLLING )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanTxObjTask(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle txObjHandle);
/* CODE CATEGORY 2 END */
# endif
# if defined( C_ENABLE_ERROR_POLLING )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanErrorTask( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 2 END */
# endif
# if defined( C_ENABLE_SLEEP_WAKEUP )
#  if defined( C_ENABLE_WAKEUP_POLLING )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanWakeUpTask(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 2 END */
#  endif
# endif
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) && \
    defined( C_ENABLE_RX_FULLCAN_POLLING )  
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxFullCANTask(CAN_CHANNEL_CANTYPE_ONLY) C_API_3;
/* CODE CATEGORY 2 END */
#  if defined( C_ENABLE_INDIVIDUAL_POLLING )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxFullCANObjTask(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle);
/* CODE CATEGORY 2 END */
#  endif
# endif
#if defined( C_ENABLE_RX_BASICCAN_POLLING ) && \
    defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxBasicCANTask(CAN_CHANNEL_CANTYPE_ONLY) C_API_3;
/* CODE CATEGORY 2 END */
#  if defined( C_ENABLE_INDIVIDUAL_POLLING )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxBasicCANObjTask(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle);
/* CODE CATEGORY 2 END */
#  endif
# endif


# if defined( C_ENABLE_DYN_TX_OBJECTS )
/* CODE CATEGORY 3 START */
C_API_1 CanTransmitHandle C_API_2 CanGetDynTxObj(CanTransmitHandle txHandle ) C_API_3;
/* CODE CATEGORY 3 END */
/* CODE CATEGORY 3 START */
C_API_1 vuint8          C_API_2 CanReleaseDynTxObj(CanTransmitHandle txHandle) C_API_3;
/* CODE CATEGORY 3 END */

#  if defined( C_ENABLE_DYN_TX_ID )
#   if !defined( C_ENABLE_EXTENDED_ID ) ||\
     defined( C_ENABLE_MIXED_ID )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetId(CanTransmitHandle txHandle, vuint16 id) C_API_3;
/* CODE CATEGORY 2 END */
#   endif
#   if defined( C_ENABLE_EXTENDED_ID )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetExtId(CanTransmitHandle txHandle, vuint16 idExtHi, vuint16 idExtLo) C_API_3;
/* CODE CATEGORY 2 END */
#   endif
#  endif
#  if defined( C_ENABLE_DYN_TX_DLC )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetDlc(CanTransmitHandle txHandle, vuint8 dlc) C_API_3;
/* CODE CATEGORY 2 END */
#  endif
#  if defined( C_ENABLE_DYN_TX_DATAPTR )
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetDataPtr(CanTransmitHandle txHandle, void* pData) C_API_3;
/* CODE CATEGORY 2 END */
#  endif


# endif /* defined( C_ENABLE_DYN_TX_OBJECTS ) */

# if defined( C_ENABLE_TX_MASK_EXT_ID )
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtHi( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtMidHi( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtMidLo( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask );
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtLo( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask );
/* CODE CATEGORY 4 END */
# endif

# if defined( C_ENABLE_TX_OBSERVE )
/* CODE CATEGORY 3 START */
C_API_1 CanTransmitHandle C_API_2 CanTxGetActHandle( CanObjectHandle logicalTxHdl ) C_API_3;
/* CODE CATEGORY 3 END */
# endif

# if defined( C_ENABLE_COND_RECEIVE_FCT )
/* CODE CATEGORY 3 START */
C_API_1 void     C_API_2 CanSetMsgReceivedCondition( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 3 END */
/* CODE CATEGORY 3 START */
C_API_1 void     C_API_2 CanResetMsgReceivedCondition( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 3 END */
/* CODE CATEGORY 3 START */
C_API_1 vuint8 C_API_2 CanGetMsgReceivedCondition( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 3 END */
# endif

# if defined( C_ENABLE_RX_QUEUE )
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanDeleteRxQueue(void);
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanHandleRxMsg(void);
/* CODE CATEGORY 2 END */
# endif

/* Additional API for QNX */
#if defined(C_ENABLE_UPDATE_BASE_ADDRESS)
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanBaseAddressRequest(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanBaseAddressActivate(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END */
#endif



#if defined( C_ENABLE_MEMCOPY_SUPPORT )
/* CODE CATEGORY 1 START*/
V_DEF_FUNC_API(V_NONE, void, CODE) CanCopyToCan(CanChipDataPtr dst, CanChipVoidPtr src, vuint8 len);                                   
/* CODE CATEGORY 1 END*/
/* CODE CATEGORY 1 START*/
V_DEF_FUNC_API(V_NONE, void, CODE) CanCopyFromCan(CanChipVoidPtr dst, CanChipDataPtr src, vuint8 len);
/* CODE CATEGORY 1 END*/
#endif



# if defined( C_ENABLE_TX_FULLCAN_DELAYED_START )
/* CODE CATEGORY 1 START*/
V_DEF_FUNC_API(V_NONE, void, CODE) CanTxFullCanDelayedStart(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 1 END*/
# endif /* C_ENABLE_TX_FULLCAN_DELAYED_START */


#if defined( C_ENABLE_SINGLE_ISR_API )

# if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
     defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
     defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanInterrupt( CAN_HW_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 1 END */
# endif

#else /* C_ENABLE_SINGLE_ISR_API */


# if defined( C_FLEXCAN_ISR_GROUP_B )
#  if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanBusOffInterrupt( CAN_HW_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 1 END */
#  endif
#  if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanWakeUpInterrupt( CAN_HW_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 1 END */
#  endif
#  if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB0To31Interrupt( CAN_HW_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 1 END */
#   if defined( C_ENABLE_MAX_BUFFER_64 )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB32To63Interrupt( CAN_HW_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 1 END */
#   endif
#  endif  /* C_ENABLE_CAN_RXTX_INTERRUPT */
# endif /* C_FLEXCAN_ISR_GROUP_A || C_FLEXCAN_ISR_GROUP_B */
#endif  /* C_ENABLE_SINGLE_ISR_API */

          
/* Possibility to disable the prototypes of interrupt service routines in the driver configuration header file.  */
# if !(defined( C_ENABLE_ISR_PROTOTYPE) || defined( C_DISABLE_ISR_PROTOTYPE ))
#  define C_ENABLE_ISR_PROTOTYPE
# endif


#if defined( C_ENABLE_ISR_PROTOTYPE )
# if defined(C_ENABLE_OSEK_OS)&&\
     defined(C_ENABLE_OSEK_OS_INTCAT2)
/* ISR prototypes mus be provided by OSEK header file */
# else

# if defined( C_ENABLE_SINGLE_ISR_API )

#  if defined( kCanPhysToLogChannelIndex_0 )
#   if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
       defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
       defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanIsr_0( void );
/* CODE CATEGORY 1 END */
#   endif
#  endif /* kCanPhysToLogChannelIndex_0 */ 
#  if defined( kCanPhysToLogChannelIndex_1 )
#   if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
       defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
       defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanIsr_1( void );
/* CODE CATEGORY 1 END */
#   endif
#  endif /* kCanPhysToLogChannelIndex_1 */ 
#  if defined( kCanPhysToLogChannelIndex_2 )
#   if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
       defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
       defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanIsr_2( void );
/* CODE CATEGORY 1 END */
#   endif
#  endif /* kCanPhysToLogChannelIndex_2 */ 
#  if defined( kCanPhysToLogChannelIndex_3 )
#   if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
       defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
       defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanIsr_3( void );
/* CODE CATEGORY 1 END */
#   endif
#  endif /* kCanPhysToLogChannelIndex_3 */ 
#  if defined( kCanPhysToLogChannelIndex_4 )
#   if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
       defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
       defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanIsr_4( void );
/* CODE CATEGORY 1 END */
#   endif
#  endif /* kCanPhysToLogChannelIndex_4 */ 
#  if defined( kCanPhysToLogChannelIndex_5 )
#   if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
       defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
       defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanIsr_5( void );
/* CODE CATEGORY 1 END */
#   endif
#  endif /* kCanPhysToLogChannelIndex_5 */ 
#  if defined( kCanPhysToLogChannelIndex_6 )
#   if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
       defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
       defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanIsr_6( void );
/* CODE CATEGORY 1 END */
#   endif
#  endif /* kCanPhysToLogChannelIndex_6 */ 
#  if defined( kCanPhysToLogChannelIndex_7 )
#   if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
       defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
       defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanIsr_7( void );
/* CODE CATEGORY 1 END */
#   endif
#  endif /* kCanPhysToLogChannelIndex_7 */ 

# else /* C_ENABLE_SINGLE_ISR_API */


#  if defined( C_FLEXCAN_ISR_GROUP_B )
#   if defined( kCanPhysToLogChannelIndex_0 )
#    if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanBusOffIsr_0( void );
/* CODE CATEGORY 1 END */
#    endif
#    if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanWakeUpIsr_0( void );
/* CODE CATEGORY 1 END */
#    endif
#    if defined( C_ENABLE_CAN_RXTX_INTERRUPT )          
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB0To15Isr_0( void );
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB16To31Isr_0( void );
/* CODE CATEGORY 1 END */
#     if defined( C_ENABLE_MAX_BUFFER_64 )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB32To63Isr_0( void );
/* CODE CATEGORY 1 END */
#     endif
#    endif  /* C_ENABLE_CAN_RXTX_INTERRUPT */
#   endif /* kCanPhysToLogChannelIndex_0 */
#   if defined( kCanPhysToLogChannelIndex_1 )
#    if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanBusOffIsr_1( void );
/* CODE CATEGORY 1 END */
#    endif
#    if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanWakeUpIsr_1( void );
/* CODE CATEGORY 1 END */
#    endif
#    if defined( C_ENABLE_CAN_RXTX_INTERRUPT )          
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB0To15Isr_1( void );
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB16To31Isr_1( void );
/* CODE CATEGORY 1 END */
#     if defined( C_ENABLE_MAX_BUFFER_64 )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB32To63Isr_1( void );
/* CODE CATEGORY 1 END */
#     endif
#    endif  /* C_ENABLE_CAN_RXTX_INTERRUPT */
#   endif /* kCanPhysToLogChannelIndex_1 */
#   if defined( kCanPhysToLogChannelIndex_2 )
#    if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanBusOffIsr_2( void );
/* CODE CATEGORY 1 END */
#    endif
#    if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanWakeUpIsr_2( void );
/* CODE CATEGORY 1 END */
#    endif
#    if defined( C_ENABLE_CAN_RXTX_INTERRUPT )          
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB0To15Isr_2( void );
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB16To31Isr_2( void );
/* CODE CATEGORY 1 END */
#     if defined( C_ENABLE_MAX_BUFFER_64 )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB32To63Isr_2( void );
/* CODE CATEGORY 1 END */
#     endif
#    endif  /* C_ENABLE_CAN_RXTX_INTERRUPT */
#   endif /* kCanPhysToLogChannelIndex_2 */
#   if defined( kCanPhysToLogChannelIndex_3 )
#    if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanBusOffIsr_3( void );
/* CODE CATEGORY 1 END */
#    endif
#    if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanWakeUpIsr_3( void );
/* CODE CATEGORY 1 END */
#    endif
#    if defined( C_ENABLE_CAN_RXTX_INTERRUPT )          
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB0To15Isr_3( void );
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB16To31Isr_3( void );
/* CODE CATEGORY 1 END */
#     if defined( C_ENABLE_MAX_BUFFER_64 )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB32To63Isr_3( void );
/* CODE CATEGORY 1 END */
#     endif
#    endif  /* C_ENABLE_CAN_RXTX_INTERRUPT */
#   endif /* kCanPhysToLogChannelIndex_3 */
#   if defined( kCanPhysToLogChannelIndex_4 )
#    if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanBusOffIsr_4( void );
/* CODE CATEGORY 1 END */
#    endif
#    if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanWakeUpIsr_4( void );
/* CODE CATEGORY 1 END */
#    endif
#    if defined( C_ENABLE_CAN_RXTX_INTERRUPT )          
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB0To15Isr_4( void );
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB16To31Isr_4( void );
/* CODE CATEGORY 1 END */
#     if defined( C_ENABLE_MAX_BUFFER_64 )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB32To63Isr_4( void );
/* CODE CATEGORY 1 END */
#     endif
#    endif  /* C_ENABLE_CAN_RXTX_INTERRUPT */
#   endif /* kCanPhysToLogChannelIndex_4 */
#   if defined( kCanPhysToLogChannelIndex_5 )
#    if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanBusOffIsr_5( void );
/* CODE CATEGORY 1 END */
#    endif
#    if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanWakeUpIsr_5( void );
/* CODE CATEGORY 1 END */
#    endif
#    if defined( C_ENABLE_CAN_RXTX_INTERRUPT )          
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB0To15Isr_5( void );
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB16To31Isr_5( void );
/* CODE CATEGORY 1 END */
#     if defined( C_ENABLE_MAX_BUFFER_64 )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB32To63Isr_5( void );
/* CODE CATEGORY 1 END */
#     endif
#    endif  /* C_ENABLE_CAN_RXTX_INTERRUPT */
#   endif /* kCanPhysToLogChannelIndex_5 */
#   if defined( kCanPhysToLogChannelIndex_6 )
#    if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanBusOffIsr_6( void );
/* CODE CATEGORY 1 END */
#    endif
#    if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanWakeUpIsr_6( void );
/* CODE CATEGORY 1 END */
#    endif
#    if defined( C_ENABLE_CAN_RXTX_INTERRUPT )          
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB0To15Isr_6( void );
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB16To31Isr_6( void );
/* CODE CATEGORY 1 END */
#     if defined( C_ENABLE_MAX_BUFFER_64 )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB32To63Isr_6( void );
/* CODE CATEGORY 1 END */
#     endif
#    endif  /* C_ENABLE_CAN_RXTX_INTERRUPT */
#   endif /* kCanPhysToLogChannelIndex_6 */
#   if defined( kCanPhysToLogChannelIndex_7 )
#    if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanBusOffIsr_7( void );
/* CODE CATEGORY 1 END */
#    endif
#    if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanWakeUpIsr_7( void );
/* CODE CATEGORY 1 END */
#    endif
#    if defined( C_ENABLE_CAN_RXTX_INTERRUPT )          
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB0To15Isr_7( void );
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB16To31Isr_7( void );
/* CODE CATEGORY 1 END */
#     if defined( C_ENABLE_MAX_BUFFER_64 )
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB32To63Isr_7( void );
/* CODE CATEGORY 1 END */
#     endif
#    endif  /* C_ENABLE_CAN_RXTX_INTERRUPT */
#   endif /* kCanPhysToLogChannelIndex_7 */
#  endif
# endif /* C_ENABLE_SINGLE_ISR_API */

# endif /* C_ENABLE_OSEK_OS_INTCAT2 */
#endif /* C_ENABLE_ISR_PROTOTYPE */


#if !defined( C_ENABLE_PROTECTED_RX_PROCESS ) && !defined( C_DISABLE_PROTECTED_RX_PROCESS )
# if ( C_SECURITY_LEVEL > 10 )
#  define C_ENABLE_PROTECTED_RX_PROCESS
# endif
#endif


#if defined( C_ENABLE_FLEXCAN_RXFIFO ) && \
    defined( C_ENABLE_EXT_ID_MASKING ) && \
    defined( C_ENABLE_MIXED_RX_FULLCAN_MESSAGES )
#error "Extended ID masking is not possible if mixed IDs are used in FullCAN Rx objects!"
#endif

#endif /* CAN_DEF_H */

/* End of channel */



/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Mpc5500Flexcan2Hll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Mpc5500Flexcan2Hll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Mpc5500Flexcan2Hll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Mpc5500Flexcan2Hll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Mpc5500Flexcan2Hll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Mpc5500Flexcan2Hll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Mpc5500Flexcan2Hll Erzeugungsgangnummer: 1 */

