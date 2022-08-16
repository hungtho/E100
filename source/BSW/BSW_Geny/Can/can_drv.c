/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Mpc5500Flexcan2Hll Erzeugungsgangnummer: 1 */

/* STARTSINGLE_OF_MULTIPLE */


/*****************************************************************************
| Project Name: CAN-DRIVER
|
|    File Name: CAN_DRV.C
|
|  Description: Implementation of the CAN Driver
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2018 by Vector Informatik GmbH.       All rights reserved.
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
| --------     ---------------------     -------------------------------------
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
| 19-Jan-01  0.02     Ht    derived for C16x V3.3
| 09-Mai-01  0.03     Ht    addaption to LI1.2
| 02-Oct-01  1.00     FEV   customization for MPC5XX-TouCAN
| 18-Dec-01  1.01     FEV   C_ENABLE_TX_DIRECT_OBJECTS for CanDirectTxDlc
|                           support for polling (FullCAN/Tx/Error)
| 12-Feb-02  1.02     FEV   support for Metrowerks compiler
| 10-Jun-02  1.03     FEV   adaption to LI1.3
|                           support for extended id's
| 01-Jul-02  1.03.01  FEV   fixed OSEK OS support
| 29-Jul-02  1.04     AMN   added support to Green Hills Compiler
| 02-Oct-02  1.05     FEV   CAN interrupt disable/restore instead of global
|                           in Isr. 
| 04-Dec-02  1.05.01  FEV   ESCAN00003825 DiabData compiler optimizations
| 22-Apr-03  1.06     BWR   ESCAN00004389 Added support for MCORE
|                           ESCAN00005428 Driver calls ApplCanBusOff() upon 
|                           bus off event.
|                           ESCAN00004388 compiler optimizations for Metrowerks
|                           ESCAN00005712 Driver clears pending rx/tx/err
|                           interrupts during initialization.
|                           ESCAN00005715 only changes in header file
|                           ESCAN00005741 Standard identifiers now work in 
|                           Direct Transmit objects when MIXED mode is enabled 
| 08-Jul-03  1.07     BWR   ESCAN00006008 Messages lost due to data corruption issue
| 11-Aug-03  1.08     BWR   ESCAN00006337 Support for MAC710X
|                           ESCAN00005798 CAN interrupts stop firing after Sleep Mode
|                           is exited
|                           ESCAN00005939 Only changes in header file
|                           ESCAN00006967 Incorrect handling of TouCAN issue regarding
|                           receiving due to own transmission
|                           ESCAN00006968 Add ability to strictly ignore reception
|                           of own transmit messages
|                           ESCAN00007125 Support for basicCAN polling mode
|                           ESCAN00007126 Low Priority extended ID is sent before high
|                           priority standard ID
| 06-Jan-04 1.09      BWR   ESCAN00007883 Add support for the MPC5554
|                     TAC   ESCAN00006338 Add support for the MCORE310
| 17-Nov-04 1.10      BWR   ESCAN00009916 No overrun notification to the application
|                           when a message is lost
|                           ESCAN00010207 Naming Conventions
|                           ESCAN00010521 Added casts to avoid compiler warnings
| 06-Mar-05 1.11      BWR   ESCAN00010593 MB deactivation during bus off prevents arbitration
|                           ESCAN00011054 Buff Off and Error Interrupts are not disabled during CanCanInterruptDisable( )
|                           ESCAN00011059 Support for HASH search
|                           ESCAN00011060 Support for multiple basic CAN objects
|                           ESCAN00011074 Sometimes a reception from own transmission is not ignored
|                           ESCAN00011075 CAN Interrupts are restored inside CanInit( ) 
|                           ESCAN00011076 Indication function is called twice for the reception of one CAN message
| 27-Jun-05 1.12      BWR   ESCAN00011694 Reduce basic CAN receive buffer lock time
|                           ESCAN00012505 Support for single CAN interrupt API
|                           ESCAN00012506 ISR routine split in two parts
|                           ESCAN00012676 Unhandled message causes CAN interrupt to fire continously
|                     Wr    ESCAN00013041 Support for Individual Polling Mode
|                           ESCAN00013155 Inconcistency in receive and transmit data corrected
|                           ESCAN00013567 renaming local pointer pTouCAN to pTouCANLocal 
|                           ESCAN00013566 Remove channel parameter of functions CanObjectNrGet, CanObjectNrGetXXX
|                           ESCAN00013565 Access to pCanRxBasicSoftBuffer member
|                           ESCAN00014250 Move shift of hardware object number to CanRxFullCANTask
|                           ESCAN00014325 Setting of locCanIntFlags when ISR split is enabled
|                           ESCAN00014347 Modified setting of txInfoStructConf for ApplCanTxConfirmation()
|                           ESCAN00014406 Return value of Macro CanLL_HwIsStop
| 03-Jan-06 1.12.01   Wr    ESCAN00014767 Corrected condition for while loop
| 08-Mar-06 1.13      Wr    ESCAN00016689 Renamed CanLL_CopyToCan(dst, src, len) and CanLL_CopyFromCan(dst, src, len)
|                           ESCAN00016688 Modified CanLL_SetTxDlc, CanLL_SetTxId and CanLL_TxSetIdType
|                           ESCAN00015030 FullCAN message is received incorrectly. Modified Rx handle adjustment.
|                           ESCAN00016670 Compiler error due to missing array canPollingTaskActive[ ] 
|                           ESCAN00015687 Inconsistency in ISR Split mode 
|                           ESCAN00016934 Modified return value of CanStop for loop abortion
| 21-Aug-06 1.14     BWR    ESCAN00017044 Add support for compiler Gaio
|                           ESCAN00017077 Extended IDs not received in muliple basic CAN mode
|                           ESCAN00017078 Use one common ISR function
|                           ESCAN00017228 Remove MISRA Warnings
|                           ESCAN00017345 Support feature to disable reception of self transmission
| 11-Nov-06 1.15     BWR    ESCAN00018343 Compiler error when -VLE option is used
| 02-Mar-07 1.16     BWR    ESCAN00019820 Resource Category Comments
| 09-Oct-07 1.17     BWR    ESCAN00021488 Out of bounds memory access in transmit confirmation
|                           ESCAN00022637 Missing definition of CanRxIdType[ ] in mixed ID mode
|                           ESCAN00022694 Resource Category incorrect for CanTxIdentityAssignment
| 24-Oct-07 1.18     Ces    ESCAN00022928 Support compiler Green Hills MULTI
|                           ESCAN00023383 Disable global interrupts during storing of receive messages
| 24-May-06 2.00      JMD   ESCAN00016485 Support of additional platform Mpc5500
|                     BWR   ESCAN00016486 Support of RI 1.5 features
| 02-Apr-07 2.01      BWR   ESCAN00018602 Support for MCORE34x
| 20-Jun-07 2.02      BWR   ESCAN00021026 FullCAN receive frame lost in polling mode
|                           ESCAN00021111 Out of bounds memory access in transmit confirmation
| 02-Jul-07 2.03      BWR   ESCAN00020164 Support for Coldfire
| 20-Nov-07 2.04      Ces   ESCAN00017168 ECU will not wakeup after entering sleep mode
|                           ESCAN00023425 Received messages have inconsistent ID, DLC or data.
|                           ESCAN00023384 Support AUTOSAR 2.1
| 27-Dec-07 2.05      BWR   ESCAN00017451 Return value of CanStop is kCanOk when the loop has been aborted
|                           ESCAN00022458 CanInterrupt( ) channel index handling for Multi ECU Config 
|                           ESCAN00023472 parameter of functions CanMsgTransmitSet... has to be pointer not struct
|                           ESCAN00023772 Support for Mpc5500(Flexcan) and Mpc5500(Flexcan2) platforms
|                           ESCAN00023797 Support for Common CAN
|                           ESCAN00023802 Errata 5164 FlexCAN: Freeze FlexCAN A to write RXIMR for FlexCAN C
|                           ESCAN00023803 Support for Greenhills compiler
|                           ESCAN00023897 Support for multiple interrupt API
|                           ESCAN00023896 Filtering reception of self sent frames improved
| 04-Feb-08 2.06      Ces   ESCAN00024363 Corrections for filtering of self sent frames
|                           ESCAN00024365 Support BitQueue for the transmit queue
|                           ESCAN00024366 Support extended IDs for Autosar 2.1
|                     BWR   ESCAN00024485 Clear Interrupt Mask bit for unused CAN objects
| 20-Feb-08 2.07      Ces   ESCAN00024784 Changed workaround implementation for errata 5164
| 13-Mar-08 2.08      Ces   ESCAN00025346 Fixed configurations without SINGLE ISR API
| 04-Apr-08 2.09      Ces   ESCAN00025699 Support Low Level Message Transmit
| 14-Apr-08 2.10      Ces   ESCAN00026054 Support AUTOSAR 3.0
|                     Ces   ESCAN00027149 Support MCF52xx (ColdFire) with gentool GENy
| 04-Jul-08 2.11      Ces   ESCAN00028114 Interrupts are not enabled for some FullCAN receive objects
| 11-Jul-08 2.12      Ces   ESCAN00028334 Support highend features: Multiple BasicCAN, Rx queue and Individual polling
|                           ESCAN00028462 Redesign of ISRs and tasks for Rx and Tx handling
| 11-Aug-08 2.13      Ces   ESCAN00029155 Support MPC560xB and MPC560xC for CANbedded
|                           ESCAN00029665 Support Cancel in Hardware for MPC551x and MPC560x
|                           ESCAN00029666 Support Sleep and WakeUp for MPC560x
| 10-Sep-08 2.14      Ces   ESCAN00029156 Support MPC560xB and MPC560xC for Autosar
| 11-Nov-08 2.15      Ces   ESCAN00031364 Support IMX35 with Flexcan2
| 20-Feb-09 2.16      Ces   ESCAN00033283 MICROSAR: support individual polling and message frame rejection
|                           ESCAN00033288 Improve message frame rejection
|                           ESCAN00033683 Support organi filtering on CPU type little endian and big endian
|                           ESCAN00033684 Removed feature ISR split 
| 16-Mar-09 2.17      Ces   ESCAN00034120 Support IMX25 with Flexcan2 for MICROSAR
|                           ESCAN00034121 Provide mode switch into powerdown DOZE mode in function CanSleep()
|                           ESCAN00034122 Fixed start index of BasicCAN message objects in function CanMB32To63Interrupt
| 26-Mar-09 2.18      Ces   ESCAN00029893 Fixed wrong return values of low level function CanLL_CanSleep
|                           ESCAN00029894 Fixed CanLL_WakeupHandling not called if SINGLE ISR API is used
|                           ESCAN00030831 Fixed compiler error in function CanInterrupt if SINGLE ISR API is used
|                           ESCAN00034687 Fixed wrong base address generated by GENy for platform MAC7100
|                           ESCAN00035373 Support MPC5533 and MPC5534 with FlexCAN2
|                                         Support MPC5605, MPC5606 and MPC5607 with FlexCAN2
|                           ESCAN00035451 CanMsgTransmitSetStdId and CanMsgTransmitSetExtId do return the wrong ID
|                           ESCAN00035452 Extended ID macros do return the wrong ID
|                           ESCAN00035810 Fixed compiler error in function CanMB0To15Interrupt
| 01-Jun-09 2.19      Ces   ESCAN00035431 Support MCU group PC57170x with FlexCAN2
| 06-Jul-09 2.20      Ces   ESCAN00036169 Support MCU group MPC56xx with 32 and 64 mailbox selection
| 20-Jul-09 2.21      Ces   ESCAN00036219 Support compiler Freescale/Metrowerks CodeWarrior
| 2009-09-23  2.22.00  Ces  ESCAN00038620 MICROSAR: FullCAN receive objects stop index is calculated wrong
|                           ESCAN00038857 MICROSAR: Support compiler and memory abstraction
|                           ESCAN00038933 Improve receive and transmit handling in interrupt and polling mode
| 2009-11-26  2.23.00  Ces  ESCAN00039419 Support platform DSP56F8300
|                           ESCAN00039420 Support CommonCAN on platform DSP56F8300
| 2010-04-28  2.24.00  Ces  ESCAN00040029 Support Extended RAM check
|                           ESCAN00040856 Use FlexCAN ISR grouping for derivative configuration
|                           ESCAN00042598 Support compiler GNU
| 2010-07-09  2.25.00  Ces  ESCAN00043337 FullCAN messages are not received
|                           ESCAN00043341 Messages received in BasicCAN are indicated as FullCAN message
|                           ESCAN00043867 Do not lock global interrupts during CanLL_Stop, CanLL_Start and CanLL_Sleep
|                           ESCAN00043868 Support Multiple BasicCAN link time and post build configuration variant
|                           ESCAN00043925 Support platform IMX53 with Flexcan2
|                           ESCAN00044409 Support RxFIFO (only on platforms with Flexcan2)
| 2010-08-06  2.26.00  Ces  ESCAN00044532 Support Flexcan2 without individual receive masks
| 2010-09-27  2.27.00  Ces  ESCAN00045544 Support selectable BusOff recovery variant
|                           ESCAN00045728 Support CAN message retransmit feature for FBL driver
|                           ESCAN00046770 Support MPC5604D and SPC560D4 without individual receive mask registers
|                           ESCAN00045801 MICROSAR only: Compiler warning: "CanLL_WakeUpHandling" was declared but never referenced
| 2010-12-23  2.28.00  Rse  ESCAN00047773 Prevent Compiler warnings of unused variables iMask, index and iFlag
|                           ESCAN00047743 Only one transmission occurs and interrupt fires continuously
| 2011-01-18  2.29.00  Ces  ESCAN00047008 AUTOSAR only: Compiler reports warning or error because C_SECURITY_LEVEL is not defined
|                           ESCAN00047771 Disable FlexCAN before clock source selection according to hardware reference manual
|                           ESCAN00048134 CANbedded only: Compiler warnings due to CAN_ONE_CONTROLLER_OPTIMIZATION and STD_ON
| 2011-02-15  2.30.00  Rse  ESCAN00044745 AUTOSAR only: BasicCAN messages are not received in postbuild configurations
|                           ESCAN00048408 Baudrate settings are invalid after reinitialization, error frames occur continuously on the bus
|                           ESCAN00048435 FullCAN messages are not received after switch from STOP to START mode
|                           ESCAN00048752 MICROSAR only: Message ID 0x0 is sent to the bus instead of the origin FullCAN transmit message ID                           
| 2011-03-09  2.31.00  Ces  ESCAN00048199 FullCAN messages are not correctly initialized and processed on MPC5604D
|                           ESCAN00048284 CANbedded only: Compiler reports warning because locRxHandle is set but never used
|                           ESCAN00049275 BasicCAN messages are not received after change to STOP and back to START mode
|                           ESCAN00049276 FullCAN messages are not received after change to STOP and back to START mode
|                           ESCAN00049340 The transmit task uses canTxIntMaskLo[] instead of canTxPollingMaskLo[]
|                           ESCAN00046511 MICROSAR only: Compiler reports error: "undefined identifier canTxIntMaskLo"
|                           ESCAN00049629 Platform specific selection of derivative features
| 2011-03-30  2.32.00  Rse  ESCAN00049653 Errata e4019PS: Wake-up interrupt may be generated without any recessive to dominant transition
|                           ESCAN00049636 Changed unlock of FullCAN and BasicCAN receive message buffers
|                           ESCAN00049671 Wakeup mask bit is not set during CAN initialization
|                           ESCAN00050034 Support compiler GAIO for FlexCAN2
| 2011-05-06  2.33.00  Rse  ESCAN00050721 MICROSAR only: Duplicated code segment is removed due to core update
| 2011-05-09  2.34.00  Rse  ESCAN00050784 FlexCAN1 only: Messages with extended ID pass the acceptance filter of BasicCANs that should be filtered out
| 2011-05-09  2.34.01  Rse  ESCAN00051020 Mixed MBs only: CPU throws interrupt because incorrect R/W access is done
| 2011-07-05  2.35.00  Rse  - Update HL-CBD 2.13.00 to support error-free CanRetransmit for FBL driver
| 2011-07-05  2.36.00  Rse  - Update HL-ASR 3.13.00 to support partial network (R12)
| 2011-09-13  2.37.00  Rse  ESCAN00053623 Support virtual addressing
| 2011-09-26  2.38.00  Rse  ESCAN00053861 Support access to CAN register in user mode
| 2011-10-20  2.39.00  Rse  ESCAN00053717 CAN Controller is not initialized into operational state
|                           - Some code corrections done which belongs to Support MCore341S Flexcan2 with gentool GENy (54294)
| 2011-11-25  2.40.00  Rse  ESCAN00054294 Support MCore341S Flexcan2 with gentool GENy
| 2011-12-28  2.41.00  Rse  ESCAN00055781 Support context switch (QNX) and QCC compiler for IMX
| 2012-03-20  2.41.01  Rse  ESCAN00057574 MICROSAR and MPC5602D only: FullCAN messages are not received due to wrong interrupt mask settings
|                           ESCAN00057678 MultiBasicCAN = 0 only: Compiler reports "the size of an array must be greater than zero"
| 2012-04-11  2.41.02  Rse  ESCAN00058250 MICROSAR and MPC5602D only: Compile error due to defective preprocessor directive
| 2012-04-11  3.00.00  Rse  ESCAN00056830 CANbedded only: Oscilloscope detects "form error" of transmitted frames due to dominant SRR bit in Extended Id messages
|                           ESCAN00057824 CANbedded only: Compile error: "pFlexCANLocal undeclared (first use in this function)"
|                           ESCAN00058602 Memory Protection Error while CAN initialization
|                           ESCAN00058438 Errata 5164 / e1964: Incorrect message data received
|                           ESCAN00058961 AutoSar only: Can_SetControllerMode(controller, CAN_T_STOP) returns CAN_OK instead of CAN_NOT_OK
|                           ESCAN00059171 Support MSR3 R14
|                           ESCAN00059598 CANbedded only: Compiler warning: missing prototype of function ApplCanCorruptRegisters
| 2012-07-18  3.01.00  Rse  ESCAN00060184 LL reworking: Diverse improvements for better runtime or simpler code
|                           ESCAN00060185 LL reworking: Interrupt and Polling masks should be generated
| 2012-10-19  3.01.01  Rse  - Update HL-ASR 4.03.01 for issue 61352 to prevent endless loop in ASR4.0 when ASR OS is used
| 2012-11-21  3.01.02  Rse  ESCAN00063199 MICROSAR only: infinite loop in Wakeup transition
| 2012-10-12  3.02.00  Rse  ESCAN00062034 MICROSAR and MPC5602D only: Det_ReportError kCanInvalidHwObjHandle or CAN_E_PARAM_HANDLE
|                           ESCAN00062237 MPC5602D only: Undesired CAN message is received and indicated to upper layer
|                           ESCAN00062263 MPC5602D only: FullCAN message is not received
|                           ESCAN00060564 AR3-2445: Perform SilentBSW module analysis for critical code parts
|                           ESCAN00063790 LL reworking: Improve mailbox initialization
| 2013-01-03  3.03.00  Rse  ESCAN00063900 CANbedded only: Support Common CAN for MPC5500 platform
| 2013-03-06  3.03.01  Rse  ESCAN00064571 CANbedded only: CAN messages will not be sent any more
| 2013-06-03  3.03.02  Rse  ESCAN00067362 CANbedded only: Compiler error: identifier "canCanInterruptCounter" is undefined
| 2013-06-12  3.03.03  Rse  - Update Kon-File of kernelbuilder to support ISRs for eight physical channels
| 2013-06-25  3.03.04  Rse  ESCAN00032346 BusOff notification is called twice for one single BusOff event
| 2014-05-07  3.03.05  Rse  ESCAN00075438 Corrupt mailbox is not deactivated
|                           ESCAN00075600 Mailbox RAM check is not suppressed
|                           ESCAN00075599 CAN Controller is active although register check fails
| 2014-05-19  3.03.06  Rse  ESCAN00075753 No messages are received when channel is enabled by CanEnableChannelCommunication API
| 2014-09-11  3.03.07  Her  ESCAN00078122 Extended ID message with dominant SRR-Bit is not received via BasicCAN
| 2014-10-14  3.03.08  Rse  ESCAN00076636 CAN clock settings are invalid after reinitialization, error frames occur continuously on the bus
| 2014-11-12  3.03.09  Rse  ESCAN00075454 Support new interface for Bus Mirroring
| 2015-03-05  3.03.10  Rse  ESCAN00081598 MPC5602D only: FullCAN message with Standard ID 0x400 or Extended ID 0x10000000 does not receive
| 2018-05-15  3.03.11  Rli  ESCAN00099410 Add support for Delayed Transmission of FullCAN for FlexCAN2
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
| --------     ---------------------     -------------------------------------
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
| ---------  ---  ------  ----------------------------------------------------
| 19-Jan-01  0.02  Ht     - derived form C16x V3.3
| 18-Apr-01  1.00  Pl     - derived for ARM7 TDMI
| 02-May-01  1.01  Ht     - adaption to LI1.2
|                         - change from code doupling to indexed
| 31-Oct-01  1.02  Ht     - support hash search
|                  Ht     - optimisation for message access (hardware index)
|                  Vg     - adaption for PowerPC
| 07-Nov-01  1.03  Ht     - remove some comments
|                         - support of basicCAN polling extended
| 12-Dez-01  1.04  Ht     - avoid compiler warnings for KEIL C166
|                         - ESCAN00001881: warning in CanInitPowerOn
|                         - ESCAN00001913: call of CanLL_TxEnd()
|                  Fz     - ESCAN00001914: CanInterruptRestore changed for M32C
| 02-Jan-02  1.05  Ht     - ESCAN00002009: support of polling mode improved
|                         - ESCAN00002010: Prototype of CanHL_TxConfirmation() 
|                                          not available in every case.
| 12-Feb-02  1.06 Pl      - ESCAN00002279: - now it is possible to use only the error-task without the tx-task
|                                          - support of the makro  REENTRANT
|                                          - support of the makro C_HL_ENABLE_RX_INFO_STRUCT_PTR
|                                          - For better performance for the T89C51C there is a switch-case
|                                            instruction for direct call of the PreTransmitfunction
|                                          - add C_ENABLE_RX_BASICCAN_POLLING in CanInitPowerOn
| 18-Mai-02  1.07 Ht      - support Hash search with FullCAN controller
|                         - ESCAN00002707: Reception could went wrong if IL and Hash Search
|                         - ESCAN00002893: adaption to LI 1.3
| 29-Mai-02  1.08 Ht      - ESCAN00003028: Transmission could fail in Polling mode
|                         - ESCAN00003082: call Can_LL_TxEnd() in CanMsgTransmit()
|                         - ESCAN00003083: Hash search with extended ID
|                         - ESCAN00003084: Support C_COMP_METROWERKS_PPC
|                         - ESCAN00002164: Temporary vaiable "i" not defined in function CanBasicCanMsgReceived
|                         - ESCAN00003085: support C_HL_ENABLE_IDTYPE_IN_ID
| 25-Jun     1.08.01 Vg   - Declared localInterruptOldFlag in CanRxTask()
|                         - Corrected call to CanWakeUp for multichannel
| 11-Jul-02  1.08.02 Ht   - ESCAN00003203: Hash Search routine does not work will with extended IDs
|                         - ESCAN00003205: Support of ranges could went wrong on some platforms
| 08-Aug-02  1.08.03 Ht   - ESCAN00003447: Transmission without databuffer and pretransmit-function 
| 08-Aug-02  1.08.04 An   - Added support to Green Hills
| 09-Sep-02  1.09    Ht   - ESCAN00003837: code optimication with KernelBuilder
|                         - ESCAN00004479: change the place oft the functioncall of CanLL_TxCopyMsgTransmit
|                                          in CanMsgTransmit 
| 2002-12-06 1.10    Ht   -                Support consistancy for polling tasks
|                         - ESCAN00004567: Definiton of V_NULL pointer
|                         -                remove include of string.h
|                         -                support Dummy functions for indirect function call 
|                         -                optimization for one single Tx mail box
| 2003-02-04 1.11    Ht   -                optimization for polling mode
| 2003-03-19 1.12    Ht   - ESCAN00005152: optimization of CanInit() in case of Direct Tx Objects
|                         - ESCAN00005143: CompilerWarning about function prototype 
|                                          CanHL_ReceivedRxHandle() and CanHL_IndRxHandle
|                         - ESCAN00005130: Wrong result of Heash Search on second or higher channel               
| 2003-05-12 1.13    Ht   - ESCAN00005624: support CantxMsgDestroyed for multichannel system
|                         - ESCAN00005209: Support confirmation and indication flags for EasyCAN4
|                         - ESCAN00004721: Change data type of Handle in CanRxInfoStruct
| 2003-06-18 1.20   Ht    - ESCAN00005908: support features of RI1.4
|                         - Support FJ16LX-Workaround for multichannel system
|                         - ESCAN00005671: Dynamic Transmit Objects: ID in extended ID frames is wrong
|                         - ESCAN00005863: Notification about cancelation failes in case of CanTxMsgDestroyed
| 2003-06-30 1.21   Ht   - ESCAN00006117: Common Confirmation Function: Write access to wrong memory location
|                        - ESCAN00006008: CanCanInterruptDisable in case of polling
|                        - ESCAN00006118: Optimization for Mixed ID and ID type in Own Register or ID type in ID Register
|                        - ESCAN00006100: transmission with wrong ID in mixed ID mode
|                        - ESCAN00006063: Undesirable hardware dependency for 
|                                         CAN_HL (CanLL_RxBasicTxIdReceived)
| 2003-09-10 1.22   Ht   - ESCAN00006853: Support V_MEMROM0
|                        - ESCAN00006854: suppress some Compiler warnings
|                        - ESCAN00006856: support CanTask if only Wakeup in polling mode
|                        - ESCAN00006857: variable newDLC not defined in case of Variable DataLen
| 2003-10-14 1.23   Ht   - ESCAN00006858: support BrsTime for internal runtime measurement
|                        - ESCAN00006860: support Conditional Msg Receive
|                        - ESCAN00006865: support "Cancel in HW" with CanTask
|                        - ESCAN00006866: support Direct Tx Objects
|                        - ESCAN00007109: support new memory qualifier for const data and pointer to const
| 2004-01-05 1.24   Ml   - ESCAN00007206: resolved preprocessor error for Hitachi compiler
|                   Ml   - ESCAN00007254: several changes
| 2004-02-06 1.25   Ml   - ESCAN00007281: solved compilerwarning
|                   Ml   - removed compiler warnings
| 2004-02-21 1.26   Ml   - ESCAN00007670: CAN RAM check
|                   Ml   - ESCAN00007671: fixed dyn Tx object issue
|                   Ml   - ESCAN00007764: added possibility to adjust Rx handle in LL drv
|                   Ml   - ESCAN00007681: solved compilerwarning in CanHL_IndRxHandle
|                   Ml   - ESCAN00007272: solved queue transmission out of LowLevel object
|                   Ml   - ESCAN00008064: no changes
| 2004-04-16 1.27   Ml   - ESCAN00008204: no changes
|                   Ml   - ESCAN00008160: no changes
|                   Ml   - ESCAN00008266: changed name of parameter of function CanTxGetActHandle
|                   Fz   - ESCAN00008272: Compiler error due to missing array canPollingTaskActive
| 2004-05-10 1.28   Fz   - ESCAN00008328: Compiler error if cancel in hardware is active
|                        - ESCAN00008363: Hole closed when TX in interrupt and cancel in HW is used
|                        - ESCAN00008365: Switch C_ENABLE_APPLCANPREWAKEUP_FCT added
|                        - ESCAN00008391: Wrong parameter macro used in call of 
|                                         CanLL_WakeUpHandling
| 2004-05-24 1.29   Ht   - ESCAN00008441: Interrupt not restored in case of internal error if TX Polling is used
| 2004-09-21 1.30   Ht   - ESCAN00008914: CAN channel may stop transmission for a certain time
|                        - ESCAN00008824: check of reference implementation version added
|                        - ESCAN00008825: No call of ApplCanMsgCancelNotification during CanInit()
|                        - ESCAN00008826: Support asssertions for "Conditional Message Received"  
|                   Ml   - ESCAN00008752: Added function qualifier macros
|                   Ht   - ESCAN00008823: compiler error due to array size 0
|                        - ESCAN00008977: label without instructions
|                        - ESCAN00009485: Message via Normal Tx Object will not be sent  
|                        - ESCAN00009497: support of CommonCAN and RX queue added
|                        - ESCAN00009521: Inconsitancy in total polling mode
| 2004-09-28 1.31   Ht   - ESCAN00009703: unresolved functions CAN_POLLING_IRQ_DISABLE/RESTORE()
| 2004-11-25 1.32   Ht   - move fix for ESCAN00007671 to CAN-LL of DrvCan_MpcToucanHll
|                        - ESCAN00010350: Dynamic Tx messages are send always with Std. ID
|                        - ESCAN00010388: ApplCanMsgConfirmed will only be called if realy transmitted
|                    Ml  - ESCAN00009931: The HardwareLoopCheck should have a channelparameter in multichannel systems.
|                    Ml  - ESCAN00010093: lint warning: function type inconsistent "CanCheckMemory"
|                    Ht  - ESCAN00010811: remove Misra and compiler warnings
|                        - ESCAN00010812: support Multi ECU
|                        - ESCAN00010526: CAN interrupts will be disabled accidently
|                        - ESCAN00010584: ECU may crash or behave strange with Rx queue active
| 2005-01-20 1.33    Ht  - ESCAN00010877: ApplCanMsgTransmitConf() is called erronemous
| 2005-03-03 1.34    Ht  - ESCAN00011139: Improvement/Correction of C_ENABLE_MULTI_ECU_CONFIG
|                        - ESCAN00011511: avoid PC-Lint warnings
|                        - ESCAN00011512: copy DLC in case of variable Rx Datalen
|                        - ESCAN00010847: warning due to missing brakets in can_par.c at CanChannelObject
| 2005-05-23 1.35   Ht   - ESCAN00012445: compiler error "V_MEMROMO undefined"in case of multi ECU
|                        - ESCAN00012350: Compiler Error "Illegal token channel"
| 2005-07-06 1.36   Ht   - ESCAN00012153: Compile Error: missing declaration of variable i
|                        - ESCAN00012460: Confirmation of LowLevel message will run into assertion (C_ENABLE_MULTI_ECU_PHYS enabled)
|                        - support Testpoints for CanTestKit
| 2005-07-14 1.37   Ht   - ESCAN00012892: compile error due to missing logTxObjHandle
|                        - ESCAN00012998: Compile Error: missing declaration of txHandle in CanInit()
|                        - support Testpoints for CanTestKit for FullCAN controller
| 2005-09-21 1.38   Ht   - ESCAN00013597: Linker error: Undefined symbol 'CanHL_IndRxHandle'
| 2005-11-10 1.39.00 Ht  - ESCAN00014331: Compile error due to missing 'else' in function CanTransmit
|
| 2005-04-26 2.00.00  Ht - ESCAN00016698: support RI1.5
|                        - ESCAN00014770: Cosmic compiler reports truncating assignement
|                        - ESCAN00016191: Compiler warning about unused variable in CanTxTask
|
| 2007-01-23 2.01.00  Ht - ESCAN00017279: Usage of SingleGlobalInterruptDisable lead to assertion in OSEK
|                        - ESCAN00017148: Compile error in higher layer due to missing declaration of CanTxMsgHandleToChannel
| 2007-03-14 2.02.00  Ht - ESCAN00019825: error directives added and misra changes
|                        - ESCAN00019827: adaption to never version of VStdLib.
|                        - ESCAN00019619: V_CALLBACK_1 and V_CALLBACK_2 not defined
|                        - ESCAN00019953: Handling of FullCAN reception in interrupt instead of polling or vice versa.
|                        - ESCAN00019958: CanDynTxObjSetId() or CanDynTxObjSetExtId() will run into assertion
| 2007-03-26 2.03.00  Ht - ESCAN00019988: Compile warnings in can_drv.c
|                        - ESCAN00018831: polling mode: function prototype without function implemenation (CanRxFullCANTask + CanRxBasicCANTask)
| 2007-04-20 2.04.00  dH - ESCAN00020299: user assertion fired irregularly due to unknown parameter (in case of CommonCAN)
| 2007-05-02 2.05.00  Ht - ESCAN00021069: Handling of canStatus improved, usage of preprocessor defines unified
|                        - ESCAN00021070: support relocation of HW objects in case of Multiple configuration
|                        - ESCAN00021166: Compiler Warnings: canHwChannel & canReturnCode not used in CanGetStatus
|                        - ESCAN00021223: CanCanInterruptDisabled called during Sleepmode in CanWakeupTask
|                        - ESCAN00022048: Parameter of ApplCancorruptMailbox is hardware channel instead of logical channel - Error directive added
| 2007-11-12 2.06.00  Ht - ESCAN00023188: support CAN Controller specific polling sequence for BasicCAN objects
|                        - ESCAN00023208: Compile issue about undefined variable kCanTxQueuePadBits in the CAN driver in Bit based Tx queue
| 2008-10-20 2.07.00  Ht - ESCAN00023010: support disabled mailboxes in case of extended RAM check
|                        - ESCAN00025706: provide C_SUPPORTS_MULTI_ECU_PHYS
|                        - ESCAN00026120: compiler warnings found on DrvCan_V85xAfcanHll RI 1.5
|                        - ESCAN00026322: ApplCanMsgNotMatched not called in special configuration
|                        - ESCAN00026413: Add possibility to reject remote frames received by FullCAN message objects
|                        - ESCAN00028758: CAN HL must support QNX
|                        - ESCAN00029788: CommonCAN for Driver which support only one Tx object improved (CanInit()).
|                        - ESCAN00029889: Compiler warning about uninitialized variable canHwChannel in CanCanInterruptDisable/Restore()
|                        - ESCAN00029891: Compiler warning: variable "rxHandle" was set but never used
|                        - ESCAN00029929: Support Extended ID Masking for Tx Fullcan messages 
|                        - ESCAN00030371: Improvements (assertions, misra)
|                        - ESCAN00027931: Wrong check of "queueBitPos" size
| 2009-04-08 2.08.00  Ht - ESCAN00034492: no automatic remove of CanCanInterruptDisable/Restore
|                        - ESCAN00031816: CANRANGExIDTYPE can be removed and direct expression used
|                        - ESCAN00032027: CanMsgTransmit shall support tCanMsgTransmitStruct pointer accesses to far RAM
|                        - ESCAN00034488: Postfix for unsigned const in perprocessor directives are not supported by all Compiler (ARM-Compiler 1.2)
| 2009-06-04 2.08.01  Ht - ESCAN00035426: Compiler warning about truncation in CanGetStatus removed
| 2009-10-21 2.09.00  Ht - ESCAN00036258: Compiler warning about "CanHL_ReceivedRxHandle" was declared but never referenced
|                        - ESCAN00038642: Support reentrant functions for compiler with own keyword
|                        - ESCAN00038645: support new switch C_ENABLE_UPDATE_BASE_ADDRESS
| 2010-02-01 2.10.00  Ht - ESCAN00036260: Support configuartion without static Tx messages and only one channel (remove compiler warning)
|                        - ESCAN00040478: Handle update of virtual CanBaseAdress in accordance to QNX documentation
|                        - ESCAN00039235: Compiler Warning: Narrowing or Signed-to-Unsigned type conversion
| 2010-07-22 2.11.00  Ht - ESCAN00044221: support Retransmit functionality for FBL
|                        - ESCAN00044222: internal changes: improve readability and
|                                         change CAN_CAN_INTERRUPT_... macros to avoid preprocessor errors for some compiler
|                        - ESCAN00044174: TxBitQueue only - compiler warning occurs about: condition is always true
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
| 2012-09-28 2.15.02  Ht  - ESCAN00061829: Compiler error:  about(CAN_HL_HW_RX_BASIC/FULL_STARTINDEX(canHwChannel) == 0)
|                         - ESCAN00057831: Compiler warning: "canCanInterruptOldStatus" was declared but never referenced
|                         - ESCAN00057832: Compiler warning: "canCanInterruptCounter" was set but never referenced
|                         - ESCAN00062667: Verify Identity during CanOnline and Misra improvement
|
|    ************    Version and change information of      **********        
|    ************    high level part only                   **********        
|
|    Please find the version number of the whole module in the previous 
|    File header.
|
|************************************************************************* */

#define C_DRV_INTERNAL

/* PRQA S 3453 EOF */      /* suppress messages: a function should probably used instead of function like macro. misra 19.7 */
/* PRQA S 3109 EOF */      /* suppress messages about empty statements. misra 14.3 */
/* PRQA S 2006 EOF */      /* suppress misra message about multiple return. misra 14.7 */


/* lint -function(exit, ApplCanFatalError) */

/* *********************************************************************** */
/* Include files                                                           */
/* *********************************************************************** */

#include "can_inc.h"


/* *********************************************************************** */
/* Version check                                                           */
/* *********************************************************************** */
#if( DRVCAN_MAC7100FLEXCANHLL_VERSION != 0x0303u)
#error "Source and Header file are inconsistent!"
#endif
#if( DRVCAN_MAC7100FLEXCANHLL_RELEASE_VERSION != 0x11u)
#error "Source and Header file are inconsistent!"
#endif

#if( C_VERSION_REF_IMPLEMENTATION != 0x150)
# error "Generated Data and CAN driver source file are inconsistent!"
#endif

#if( DRVCAN__COREHLL_VERSION != 0x0215)
# error "Source and Header file are inconsistent!"
#endif
#if( DRVCAN__COREHLL_RELEASE_VERSION != 0x02)
# error "Source and Header file are inconsistent!"
#endif

#if ( ( DRVCAN__HLLTXQUEUEBIT_VERSION != 0x0106) )
# error "TxQueue Source and Header Version inconsistent!"
#endif
#if ( ( DRVCAN__HLLTXQUEUEBIT_RELEASE_VERSION != 0x04) )
# error "TxQueue Source and Header Version inconsistent!"
#endif


#if defined( DRVCAN__HLLTXQUEUEBIT_VERSION )
# if ( ( DRVCAN__HLLTXQUEUEBIT_VERSION != 0x0106) || \
       ( DRVCAN__HLLTXQUEUEBIT_RELEASE_VERSION != 0x04)  )
#  error "TxQueue Version inconsistent!"
# endif

/* defines to satisfy MISRA checker tool */
# define DRVCAN__HLLTXQUEUEBYTE_VERSION 0x0000
# define DRVCAN__HLLTXQUEUEBYTE_RELEASE_VERSION 0x00

#else
# if defined( DRVCAN__HLLTXQUEUEBYTE_VERSION )
#  if ( ( DRVCAN__HLLTXQUEUEBYTE_VERSION != 0x0104) || \
       ( DRVCAN__HLLTXQUEUEBYTE_RELEASE_VERSION != 0x00)  )
#   error "TxQueue Version inconsistent!"
#  endif
# else
#  error "No TxQueue available"
# endif

/* defines to satisfy MISRA checker tool */
# define DRVCAN__HLLTXQUEUEBIT_VERSION 0x0000
# define DRVCAN__HLLTXQUEUEBIT_RELEASE_VERSION 0x00

#endif


/* *********************************************************************** */
/* Defines                                                                 */
/* *********************************************************************** */


/* return values */ 
#define kCanHlFinishRx                                     ((vuint8)0x00)
#define kCanHlContinueRx                                   ((vuint8)0x01)

#define  CANHL_TX_QUEUE_BIT
#if defined (MISRA_CHECK)
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_WRITE_PROTECTED_REG_RESET",  0277           /* MD_Can_0277_negation */
# pragma PRQA_MACRO_MESSAGES_OFF "CAN_CLEAR_MDIS",                 0277           /* MD_Can_0277_negation */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_CanInterruptDisable",      0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_CanInterruptRestore",      0277,0303,0306 /* MD_Can_0277_negation */ /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "pFlexCAN",                       0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "pFLEXCAN",                       0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "pCanRxMask",                     0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "pRXFIFO",                        0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_TxIsHWObjFree",            0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsSleep",                0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsStop",                 0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsBusOff",               0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsPassive",              0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
# pragma PRQA_MACRO_MESSAGES_OFF "CanLL_HwIsWarning",              0303,0306      /* MD_Can_0303_HWaccess */ /* MD_Can_0306_HWaccess */
#endif
/* define chiphardware and constants concerning CAN controller registers */

/* Bitmasks of FlexCAN module configuration register CANx_MCR */
#define kFlexCAN_MDIS      ((vuint16)0x8000u)     /* Module Disable: shut down FlexCAN clocks */
#define kFlexCAN_FRZ       ((vuint16)0x4000u)     /* Freeze Enable: allow entering the freeze mode */
#define kFlexCAN_FEN       ((vuint16)0x2000u)     /* FIFO enable */
#define kFlexCAN_HALT      ((vuint16)0x1000u)     /* Halt FlexCAN: request entering the freeze mode */
#define kFlexCAN_NOT_RDY   ((vuint16)0x0800u)     /* Not Ready: FlexCAN is in DISABLE, DOZE or STOP mode */
#define kFlexCAN_WAK_MSK   ((vuint16)0x0400u)     /* Wakeup Interrupt Mask: enable wakeup interrupt generation */
#define kFlexCAN_SOFT_RST  ((vuint16)0x0200u)     /* Soft Reset: reset FlexCAN internal state and some memory mapped registers */
#define kFlexCAN_FRZ_ACK   ((vuint16)0x0100u)     /* Freeze Mode Acknowledge */
#define kFlexCAN_SUPV      ((vuint16)0x0080u)     /* Supervisor Mode */
#define kFlexCAN_SLF_WAK   ((vuint16)0x0040u)     /* FlexCAN Self Wakeup by CAN bus activity */
#define kFlexCAN_WRN_EN    ((vuint16)0x0020u)     /* Warning Interrupt Enable */
#define kFlexCAN_LPM_ACK   ((vuint16)0x0010u)     /* Low Power Mode Acknowledge */
#define kFlexCAN_WAK_SRC   ((vuint16)0x0008u)     /* Wakeup Source: enable filtered Rx input signal */
#define kFlexCAN_DOZE      ((vuint16)0x0004u)     /* Doze Mode Enable: allow MCU to switch FlexCAN into DOZE low power mode */
#define kFlexCAN_NOT_DOZE  ((vuint16)0xFFFBu)     /* Doze Mode Disable: do not allow MCU to switch FlexCAN into DOZE low power mode */
#define kFlexCAN_SRX_DIS   ((vuint16)0x0002u)     /* Self Reception Disable */
#define kFlexCAN_BCC       ((vuint16)0x0001u)     /* Backwards Compatibility Configuration: enable Individual Rx Masks */

#define kFlexCAN_LPPRIO_EN ((vuint16)0x2000u)     /* Local Priority Enable */
#define kFlexCAN_AEN       ((vuint16)0x1000u)     /* Abort Enable: enables transmit abort feature */
#define kFlexCAN_IDAM      ((vuint16)0x0300u)     /* ID Acceptance Mode */
#define kFlexCAN_MAXMB     ((vuint16)0x003Fu)     /* Maximum Number of Message Buffers: maximum number of used message buffers = MAXMB+1 */

#define kFlexCAN_BOFF_MSK  ((vuint16)0x8000u)     /* FlexCAN BusOff interrupt mask */
#define kFlexCAN_LOM       ((vuint16)0x0008u)     /* FlexCAN Listen Only Mode */

#if defined( C_CPUTYPE_32BIT )
# define kFlexCAN_WAKE_INT  ((vuint32)0x00000001u)    /* Wake Up interrupt flag */
# define kFlexCAN_ERR_INT   ((vuint32)0x00000002u)    /* Error interrupt flag */
# define kFlexCAN_BOFF_INT  ((vuint32)0x00000004u)    /* Bus Off interrupt flag */ 
# define kFlexCAN_FCS_BOFF  ((vuint32)0x00000020u)    /* Fault Confinement State value for BusOff */
# define kFlexCAN_FCS_EP    ((vuint32)0x00000010u)    /* Fault Confinement State value for ErrorPassive */
# define kFlexCAN_FCS       ((vuint32)0x00000030u)    /* Fault Confinement State */
# define kFlexCAN_RXTX_WARN ((vuint32)0x00000300u)
#endif

#define kFlexCAN_SMP          ((vuint16)0x0080u)    /* FlexCAN sampling mode */
#define kFlexCAN_CLK_SRC      ((vuint16)0x2000u)    /* FlexCAN clock source mask */
#define kFlexCAN_BOFF_REC     ((vuint16)0x0040u)    /* FlexCAN auto BusOff recovery */

#define kFlexCAN_USR_CONFIG_BITS   ((vuint16)0x26EFu) /* user configurable bits in MCR */
#define kFlexCAN_NORMAL_MODE       ((vuint16)0x0000u) /* relevant bits for mode states must all be negated for NORMAL mode */
#define kFlexCAN_MDIS_SLFWAKE_MASK (kFlexCAN_MDIS | kFlexCAN_SLF_WAK | kFlexCAN_WAK_MSK)
#define kFlexCAN_MCR               (kFlexCAN_MDIS | kFlexCAN_FRZ | kFlexCAN_HALT | kFlexCAN_NOT_RDY | kFlexCAN_FRZ_ACK | kFlexCAN_LPM_ACK)
#define kFlexCAN_FREEZE_MODE       (kFlexCAN_FRZ | kFlexCAN_HALT | kFlexCAN_NOT_RDY | kFlexCAN_FRZ_ACK) /* FlexCAN in FREEZE mode: FRZ, HALT, NOT_RDY and FRZ_ACK bit are set */
#define kFlexCAN_DOZE_MODE         (kFlexCAN_NOT_RDY | kFlexCAN_LPM_ACK | kFlexCAN_DOZE) /* FlexCAN in DOZE powerdown mode: NOT_RDY, LPM_ACK and DOZE are bit set */
#define kFlexCAN_DISABLE_MODE      (kFlexCAN_MDIS | kFlexCAN_NOT_RDY | kFlexCAN_LPM_ACK) /* FlexCAN in DISABLE powerdown mode: MDIS, NOT_RDY and LPM_ACK bit are set */

#define kNotFlexCANErrBoff ((vuint16)0x3FFFu)


#if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
# define kTxCodeINACTIVE       ((vuint32)0x08000000)
#else
# define kTxCodeINACTIVE       ((vuint16)0x0800)
#endif

# define CANSFR_CLEAR      ((vuint32)0x00000000u)
# define CANSFR_SET        ((vuint32)0xFFFFFFFFu)

/* Macros to access the CODE-bits in the control/status word ------------------*/
# define kCodeMask         ((vuint16)0x0F00u)     /* Mask to access the CODE in the control/status word */
# define kNotDlcMask       ((vuint32)0xFF000000u)
# define kNotCodeMask      ((vuint32)0xF0FF0000u)

/* Code definitions for receive objects */
# define kRxCodeEmpty      ((vuint32)0x04000000u) /* Message buffer is active and empty */
# define kRxCodeClear      ((vuint32)0x00F00000u) /* Mask to clear control register but leave the ID type */
# define kRxCodeOverrun    ((vuint16)0x0600u)     /* Second frame was received into a full buffer */
# define kRxCodeBusy       ((vuint16)0x0100u)     /* Receive buffer locked */

/* Code definitions for transmit objects */
# if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
#  define kNotIDEMask       ((vuint32)0xFF0F0000u)
#  define kTxCodeTransmit   ((vuint32)0x0C400000u) /* Start transmit session AND set SRR (SRR = '1' is mandatory for Extended but harmless for Standard format) */
#  define kTxDlcMask        ((vuint32)0x006F0000u) /* Mask to access the DLC in the control/status word */
# else
#  define kNotIDEMask       ((vuint16)0xFF0Fu)
#  define kTxCodeTransmit   ((vuint16)0x0C40u)     /* Start transmit session AND set SRR (SRR = '1' is mandatory for Extended but harmless for Standard format) */
#  define kTxDlcMask        ((vuint16)0x006Fu)     /* Mask to access the DLC in the control/status word */
# endif
# define kTxCodeFree       ((vuint16)0x0800u)      /* Transmit object free */
# define kTxCodeAbort      ((vuint32)0x09000000u)  /* Abort message transmission */

# if defined( C_ENABLE_EXTENDED_ID )
#  define kTxCodeInactive  ((vuint32)0x08200000u)  /* Transmit object inactive for extended or mixed IDs */
# else
#  define kTxCodeInactive  ((vuint32)0x08000000u)  /* Transmit object inactive for standard IDs */
# endif

# if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
#  define kCanRxMaskStd     ((vuint32)0x1FFC0000u)
#  if defined( C_ENABLE_EXTENDED_ID )
#   if defined( C_ENABLE_RX_MASK_EXT_ID )
#    define kCanRxMaskExt   ((vuint32)C_MASK_EXT_ID)
#   else
#    define kCanRxMaskExt   ((vuint32)0x1FFFFFFFu)
#   endif
#  endif
# endif

# if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING ) && defined( C_ENABLE_FLEXCAN_RXFIFO )
#  define kRxFIFO_OVERRUN     ((vuint32)0x00000080u)
#  define kRxFIFO_WARN        ((vuint32)0x00000040u)
#  define kRxFIFO_NEWMSG      ((vuint32)0x00000020u)
#  define kRxFIFO_EXT         ((vuint32)0x40000000u)
#  define kRxFIFO_REM         ((vuint32)0x80000000u)
#  define kRxFIFO_MASK        ((vuint32)0xC0000000u)
#  define kRxGMaskValue       ((vuint32)0xFFFFFFFFu)
#  if !defined( C_FLEXCAN_RXFIFO_MAXLOOP )
#   define C_FLEXCAN_RXFIFO_MAXLOOP  5
#  else
#   if ((C_FLEXCAN_RXFIFO_MAXLOOP == 0) || (C_FLEXCAN_RXFIFO_MAXLOOP > 7))
#    error "invalid value! C_FLEXCAN_RXFIFO_MAXLOOP must be within range 1 ... 7"
#   endif
#  endif
# endif




#if !defined( C_MASK_EXT_ID )
# define C_MASK_EXT_ID ((vuint32)0x1FFFFFFFu)
#endif

#if defined( C_ENABLE_EXTENDED_ID )
# define CAN_MSGID(x) (vuint32)(x)
#else
# define CAN_MSGID(x) ((vuint32)(x) << 16)
#endif

/* *********************************************************************** */
/* macros                                                                  */
/* *********************************************************************** */

#if !(defined( C_HL_DISABLE_RX_INFO_STRUCT_PTR ) || defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR ))
# define C_HL_ENABLE_RX_INFO_STRUCT_PTR
#endif

#if defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
# define CAN_HL_P_RX_INFO_STRUCT(channel)                  (pCanRxInfoStruct)  
# define CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)           (pCanRxInfoStruct->Handle)  
#else
# define CAN_HL_P_RX_INFO_STRUCT(channel)                  (&canRxInfoStruct[channel])
# define CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)           (canRxInfoStruct[channel].Handle)  
#endif 


/* disabled - lint -emacro( (572, 778), C_RANGE_MATCH) */


#if defined( C_SINGLE_RECEIVE_CHANNEL )
# if (kCanNumberOfUsedCanRxIdTables == 1)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, mask, code) \
                  (  ((idRaw0) & (tCanRxId0)~MK_RX_RANGE_MASK_IDSTD0(mask)) == MK_RX_RANGE_CODE_IDSTD0(code) )
#  define C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, mask, code) \
                  (  ((idRaw0) & (tCanRxId0)~MK_RX_RANGE_MASK_IDEXT0(mask)) == MK_RX_RANGE_CODE_IDEXT0(code) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 2)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDSTD0(mask)) == MK_RX_RANGE_CODE_IDSTD0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDSTD1(mask)) == MK_RX_RANGE_CODE_IDSTD1(code) ) )
#  define C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDEXT0(mask)) == MK_RX_RANGE_CODE_IDEXT0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDEXT1(mask)) == MK_RX_RANGE_CODE_IDEXT1(code) ) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 3)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDSTD0(mask)) == MK_RX_RANGE_CODE_IDSTD0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDSTD1(mask)) == MK_RX_RANGE_CODE_IDSTD1(code) ) && \
                    ( ((idRaw2) & (tCanRxId2)~ MK_RX_RANGE_MASK_IDSTD2(mask)) == MK_RX_RANGE_CODE_IDSTD2(code) ) )
#  define C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDEXT0(mask)) == MK_RX_RANGE_CODE_IDEXT0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDEXT1(mask)) == MK_RX_RANGE_CODE_IDEXT1(code) ) && \
                    ( ((idRaw2) & (tCanRxId2)~ MK_RX_RANGE_MASK_IDEXT2(mask)) == MK_RX_RANGE_CODE_IDEXT2(code) ) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 4)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDSTD0(mask)) == MK_RX_RANGE_CODE_IDSTD0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDSTD1(mask)) == MK_RX_RANGE_CODE_IDSTD1(code) ) && \
                    ( ((idRaw2) & (tCanRxId2)~ MK_RX_RANGE_MASK_IDSTD2(mask)) == MK_RX_RANGE_CODE_IDSTD2(code) ) && \
                    ( ((idRaw3) & (tCanRxId3)~ MK_RX_RANGE_MASK_IDSTD3(mask)) == MK_RX_RANGE_CODE_IDSTD3(code) ) )
#  define C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDEXT0(mask)) == MK_RX_RANGE_CODE_IDEXT0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDEXT1(mask)) == MK_RX_RANGE_CODE_IDEXT1(code) ) && \
                    ( ((idRaw2) & (tCanRxId2)~ MK_RX_RANGE_MASK_IDEXT2(mask)) == MK_RX_RANGE_CODE_IDEXT2(code) ) && \
                    ( ((idRaw3) & (tCanRxId3)~ MK_RX_RANGE_MASK_IDEXT3(mask)) == MK_RX_RANGE_CODE_IDEXT3(code) ) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 5)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDSTD0(mask)) == MK_RX_RANGE_CODE_IDSTD0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDSTD1(mask)) == MK_RX_RANGE_CODE_IDSTD1(code) ) && \
                    ( ((idRaw2) & (tCanRxId2)~ MK_RX_RANGE_MASK_IDSTD2(mask)) == MK_RX_RANGE_CODE_IDSTD2(code) ) && \
                    ( ((idRaw3) & (tCanRxId3)~ MK_RX_RANGE_MASK_IDSTD3(mask)) == MK_RX_RANGE_CODE_IDSTD3(code) ) && \
                    ( ((idRaw4) & (tCanRxId4)~ MK_RX_RANGE_MASK_IDSTD4(mask)) == MK_RX_RANGE_CODE_IDSTD4(code) ) )
#  define C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, mask, code) \
                  ( ( ((idRaw0) & (tCanRxId0)~ MK_RX_RANGE_MASK_IDEXT0(mask)) == MK_RX_RANGE_CODE_IDEXT0(code) ) && \
                    ( ((idRaw1) & (tCanRxId1)~ MK_RX_RANGE_MASK_IDEXT1(mask)) == MK_RX_RANGE_CODE_IDEXT1(code) ) && \
                    ( ((idRaw2) & (tCanRxId2)~ MK_RX_RANGE_MASK_IDEXT2(mask)) == MK_RX_RANGE_CODE_IDEXT2(code) ) && \
                    ( ((idRaw3) & (tCanRxId3)~ MK_RX_RANGE_MASK_IDEXT3(mask)) == MK_RX_RANGE_CODE_IDEXT3(code) ) && \
                    ( ((idRaw4) & (tCanRxId4)~ MK_RX_RANGE_MASK_IDEXT4(mask)) == MK_RX_RANGE_CODE_IDEXT4(code) ) )
# endif
#else     /* C_MULTIPLE_RECEIVE_CHANNEL */

# if (kCanNumberOfUsedCanRxIdTables == 1)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH( CAN_RX_IDRAW_PARA, mask, code)    \
                                (  ((idRaw0) & (tCanRxId0)~((mask).Id0)) == ((code).Id0) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 2)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH( CAN_RX_IDRAW_PARA, mask, code)    \
                                ( ( ((idRaw0) & (tCanRxId0)~((mask).Id0)) == ((code).Id0) ) &&\
                                  ( ((idRaw1) & (tCanRxId1)~((mask).Id1)) == ((code).Id1) ) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 3)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH( CAN_RX_IDRAW_PARA, mask, code)    \
                                ( ( ((idRaw0) & (tCanRxId0)~((mask).Id0)) == ((code).Id0) ) &&\
                                  ( ((idRaw1) & (tCanRxId1)~((mask).Id1)) == ((code).Id1) ) &&\
                                  ( ((idRaw2) & (tCanRxId2)~((mask).Id2)) == ((code).Id2) ) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 4)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH( CAN_RX_IDRAW_PARA, mask, code)    \
                                ( ( ((idRaw0) & (tCanRxId0)~((mask).Id0)) == ((code).Id0) ) &&\
                                  ( ((idRaw1) & (tCanRxId1)~((mask).Id1)) == ((code).Id1) ) &&\
                                  ( ((idRaw2) & (tCanRxId2)~((mask).Id2)) == ((code).Id2) ) &&\
                                  ( ((idRaw3) & (tCanRxId3)~((mask).Id3)) == ((code).Id3) ) )
# endif
# if (kCanNumberOfUsedCanRxIdTables == 5)
/* Msg(4:3410) Macro parameter not enclosed in (). MISRA Rule 96 - no change */
#  define C_RANGE_MATCH( CAN_RX_IDRAW_PARA, mask, code)    \
                                ( ( ((idRaw0) & (tCanRxId0)~((mask).Id0)) == ((code).Id0) ) &&\
                                  ( ((idRaw1) & (tCanRxId1)~((mask).Id1)) == ((code).Id1) ) &&\
                                  ( ((idRaw2) & (tCanRxId2)~((mask).Id2)) == ((code).Id2) ) &&\
                                  ( ((idRaw3) & (tCanRxId3)~((mask).Id3)) == ((code).Id3) ) &&\
                                  ( ((idRaw4) & (tCanRxId4)~((mask).Id4)) == ((code).Id4) ) )
# endif
#endif


#if (kCanNumberOfUsedCanRxIdTables == 1)
# define CAN_RX_IDRAW_PARA                                 idRaw0
#endif
#if (kCanNumberOfUsedCanRxIdTables == 2)
# define CAN_RX_IDRAW_PARA                                 idRaw0, idRaw1
#endif
#if (kCanNumberOfUsedCanRxIdTables == 3)
# define CAN_RX_IDRAW_PARA                                 idRaw0, idRaw1, idRaw2
#endif
#if (kCanNumberOfUsedCanRxIdTables == 4)
# define CAN_RX_IDRAW_PARA                                 idRaw0, idRaw1, idRaw2, idRaw3
#endif
#if (kCanNumberOfUsedCanRxIdTables == 5)
# define CAN_RX_IDRAW_PARA                                 idRaw0, idRaw1, idRaw2, idRaw3, idRaw4
#endif


#if defined( C_SINGLE_RECEIVE_CHANNEL )
# define channel                                           ((CanChannelHandle)0)
# define canHwChannel                                      ((CanChannelHandle)0)
# define CAN_HL_HW_CHANNEL_STARTINDEX(channel)             ((CanChannelHandle)0)
# define CAN_HL_HW_CHANNEL_STOPINDEX(channel)              ((CanChannelHandle)0)
# define CAN_HL_HW_MSG_TRANSMIT_INDEX(canHwChannel)        (kCanMsgTransmitObj)
# define CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel)           (kCanHwTxNormalIndex)

/* Offset which has to be added to change the hardware Tx handle into a logical handle, which is unique over all channels */
/*        Tx-Hardware-Handle - CAN_HL_HW_TX_STARTINDEX(canHwChannel) + CAN_HL_LOG_HW_TX_STARTINDEX(canHwChannel) */
# define CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel)          ((vsintx)0-(vsintx)kCanHwTxStartIndex)
/* ESCAN00062667 */

# define CAN_HL_TX_STARTINDEX(channel)                     ((CanTransmitHandle)0)
# define CAN_HL_TX_STAT_STARTINDEX(channel)                ((CanTransmitHandle)0)
# define CAN_HL_TX_DYN_ROM_STARTINDEX(channel)             (kCanNumberOfTxStatObjects)
# define CAN_HL_TX_DYN_RAM_STARTINDEX(channel)             ((CanTransmitHandle)0)
/* # define CAN_HL_RX_STARTINDEX(channel)                     ((CanReceiveHandle)0) */
/* index to access the ID tables - Basic index only for linear search 
   for hash search this is the start index of the ??? */
# define CAN_HL_RX_BASIC_STARTINDEX(channel)               ((CanReceiveHandle)0)
# if defined( C_SEARCH_HASH ) || \
     defined( C_SEARCH_INDEX )
#  define CAN_HL_RX_FULL_STARTINDEX(canHwChannel)          ((CanReceiveHandle)0)
# else
#  define CAN_HL_RX_FULL_STARTINDEX(canHwChannel)          (kCanNumberOfRxBasicCANObjects)
# endif
# define CAN_HL_INIT_OBJ_STARTINDEX(channel)               ((vuint8)0)
# define CAN_HL_LOG_HW_TX_STARTINDEX(canHwChannel)         ((CanObjectHandle)0)
# define CAN_HL_HW_TX_STARTINDEX(canHwChannel)             (kCanHwTxStartIndex)
# define CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel)        (kCanHwRxFullStartIndex)
# define CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel)       (kCanHwRxBasicStartIndex)
# define CAN_HL_HW_UNUSED_STARTINDEX(canHwChannel)         (kCanHwUnusedStartIndex)

# define CAN_HL_TX_STOPINDEX(channel)                      (kCanNumberOfTxObjects)
# define CAN_HL_TX_STAT_STOPINDEX(channel)                 (kCanNumberOfTxStatObjects)
# define CAN_HL_TX_DYN_ROM_STOPINDEX(channel)              (kCanNumberOfTxObjects)
# define CAN_HL_TX_DYN_RAM_STOPINDEX(channel)              (kCanNumberOfTxDynObjects)
/* # define CAN_HL_RX_STOPINDEX(channel)                      (kCanNumberOfRxObjects) */
# define CAN_HL_RX_BASIC_STOPINDEX(channel)                (kCanNumberOfRxBasicCANObjects)
# if defined( C_SEARCH_HASH ) || \
     defined( C_SEARCH_INDEX )
#  define CAN_HL_RX_FULL_STOPINDEX(canHwChannel)           (kCanNumberOfRxFullCANObjects)
# else
#  define CAN_HL_RX_FULL_STOPINDEX(canHwChannel)           (kCanNumberOfRxBasicCANObjects+kCanNumberOfRxFullCANObjects)
# endif
# define CAN_HL_INIT_OBJ_STOPINDEX(channel)                (kCanNumberOfInitObjects)
# define CAN_HL_LOG_HW_TX_STOPINDEX(canHwChannel)          (kCanNumberOfUsedTxCANObjects)
# define CAN_HL_HW_TX_STOPINDEX(canHwChannel)              (kCanHwTxStartIndex     +kCanNumberOfUsedTxCANObjects)
# define CAN_HL_HW_RX_FULL_STOPINDEX(canHwChannel)         (kCanHwRxFullStartIndex +kCanNumberOfRxFullCANObjects)
# define CAN_HL_HW_RX_BASIC_STOPINDEX(canHwChannel)        (kCanHwRxBasicStartIndex+kCanNumberOfUsedRxBasicCANObjects)
# define CAN_HL_HW_UNUSED_STOPINDEX(canHwChannel)          (kCanHwUnusedStartIndex +kCanNumberOfUnusedObjects)

#else
#  define canHwChannel                                     channel   /* brackets are not allowed here due to compiler error with Renesas HEW compiler for SH2 */
#  define CAN_HL_HW_CHANNEL_STARTINDEX(channel)            (channel)
#  define CAN_HL_HW_CHANNEL_STOPINDEX(channel)             (channel)

#  define CAN_HL_HW_MSG_TRANSMIT_INDEX(canHwChannel)       (CanHwMsgTransmitIndex[(canHwChannel)])
#  define CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel)          (CanHwTxNormalIndex[(canHwChannel)])
/* Offset which has to be added to change the hardware Tx handle into a logical handle, which is unique over all channels */
/*        Tx-Hardware-Handle - CAN_HL_HW_TX_STARTINDEX(canHwChannel) + CAN_HL_LOG_HW_TX_STARTINDEX(canHwChannel) */
#  define CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel)         (CanTxOffsetHwToLog[(canHwChannel)])

# define CAN_HL_TX_STARTINDEX(channel)                     (CanTxStartIndex[(channel)])
# define CAN_HL_TX_STAT_STARTINDEX(channel)                (CanTxStartIndex[(channel)])
# define CAN_HL_TX_DYN_ROM_STARTINDEX(channel)             (CanTxDynRomStartIndex[(channel)])
# define CAN_HL_TX_DYN_RAM_STARTINDEX(channel)             (CanTxDynRamStartIndex[(channel)])
/* # define CAN_HL_RX_STARTINDEX(channel)                     (CanRxStartIndex[(channel)]) */
/* index to access the ID tables - Basic index only for linear search */
# define CAN_HL_RX_BASIC_STARTINDEX(channel)               (CanRxBasicStartIndex[(channel)])      
# define CAN_HL_RX_FULL_STARTINDEX(canHwChannel)           (CanRxFullStartIndex[(canHwChannel)])
# define CAN_HL_INIT_OBJ_STARTINDEX(channel)               (CanInitObjectStartIndex[(channel)])      
# define CAN_HL_LOG_HW_TX_STARTINDEX(canHwChannel)         (CanLogHwTxStartIndex[(canHwChannel)])
#  define CAN_HL_HW_TX_STARTINDEX(canHwChannel)             (CanHwTxStartIndex[(canHwChannel)])   
#  define CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel)        (CanHwRxFullStartIndex[(canHwChannel)])
#  define CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel)       (CanHwRxBasicStartIndex[(canHwChannel)]) 
#  define CAN_HL_HW_UNUSED_STARTINDEX(canHwChannel)         (CanHwUnusedStartIndex[(canHwChannel)])
                                                           
# define CAN_HL_TX_STOPINDEX(channel)                      (CanTxStartIndex[(channel) + 1]) 
# define CAN_HL_TX_STAT_STOPINDEX(channel)                 (CanTxDynRomStartIndex[(channel)])
# define CAN_HL_TX_DYN_ROM_STOPINDEX(channel)              (CanTxStartIndex[(channel) + 1]) 
# define CAN_HL_TX_DYN_RAM_STOPINDEX(channel)              (CanTxDynRamStartIndex[(channel) + 1])
/* # define CAN_HL_RX_STOPINDEX(channel)                      (CanRxStartIndex[(channel) + 1]) */
/* index to access the ID tables - Basic index only for linear search */
# define CAN_HL_RX_BASIC_STOPINDEX(channel)                (CanRxFullStartIndex[CAN_HL_HW_CHANNEL_STARTINDEX(channel)])
# define CAN_HL_INIT_OBJ_STOPINDEX(channel)                (CanInitObjectStartIndex[(channel) + 1])
# define CAN_HL_LOG_HW_TX_STOPINDEX(canHwChannel)          (CanLogHwTxStartIndex[(canHwChannel) +1])      
#  define CAN_HL_HW_TX_STOPINDEX(canHwChannel)              (CanHwTxStopIndex[(canHwChannel)])
#  define CAN_HL_HW_RX_FULL_STOPINDEX(canHwChannel)         (CanHwRxFullStopIndex[(canHwChannel)])
#  define CAN_HL_HW_RX_BASIC_STOPINDEX(canHwChannel)         (CanHwRxBasicStopIndex[(canHwChannel)])
#  define CAN_HL_HW_UNUSED_STOPINDEX(canHwChannel)         (CanHwUnusedStopIndex[(canHwChannel)])

#endif


#if defined( C_SINGLE_RECEIVE_CHANNEL )

# define CANRANGE0ACCMASK(i)                               C_RANGE0_ACC_MASK
# define CANRANGE0ACCCODE(i)                               C_RANGE0_ACC_CODE
# define CANRANGE1ACCMASK(i)                               C_RANGE1_ACC_MASK
# define CANRANGE1ACCCODE(i)                               C_RANGE1_ACC_CODE
# define CANRANGE2ACCMASK(i)                               C_RANGE2_ACC_MASK
# define CANRANGE2ACCCODE(i)                               C_RANGE2_ACC_CODE
# define CANRANGE3ACCMASK(i)                               C_RANGE3_ACC_MASK
# define CANRANGE3ACCCODE(i)                               C_RANGE3_ACC_CODE

# define APPL_CAN_MSG_RECEIVED( i )                        (APPL_CAN_MSGRECEIVED( i ))

# define APPLCANRANGE0PRECOPY( i )                         (ApplCanRange0Precopy( i ))   
# define APPLCANRANGE1PRECOPY( i )                         (ApplCanRange1Precopy( i ))   
# define APPLCANRANGE2PRECOPY( i )                         (ApplCanRange2Precopy( i ))   
# define APPLCANRANGE3PRECOPY( i )                         (ApplCanRange3Precopy( i ))   

# define APPL_CAN_BUSOFF( i )                              (ApplCanBusOff())
# define APPL_CAN_WAKEUP( i )                              (ApplCanWakeUp())

# if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
#  define APPLCANCANCELNOTIFICATION( i, j )                (APPL_CAN_CANCELNOTIFICATION( j ))
# else
#  define APPLCANCANCELNOTIFICATION( i, j )
# endif
# if defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
#  define APPLCANMSGCANCELNOTIFICATION( i )                (APPL_CAN_MSGCANCELNOTIFICATION())
# else
#  define APPLCANMSGCANCELNOTIFICATION( i )
# endif

# define CAN_RX_INDEX_TBL(channel, id)                      (CanRxIndexTbl[id])

#else

# define CANRANGE0ACCMASK(i)                               (CanChannelObject[i].RangeMask[0])
# define CANRANGE0ACCCODE(i)                               (CanChannelObject[i].RangeCode[0])
# define CANRANGE1ACCMASK(i)                               (CanChannelObject[i].RangeMask[1])
# define CANRANGE1ACCCODE(i)                               (CanChannelObject[i].RangeCode[1])
# define CANRANGE2ACCMASK(i)                               (CanChannelObject[i].RangeMask[2])
# define CANRANGE2ACCCODE(i)                               (CanChannelObject[i].RangeCode[2])
# define CANRANGE3ACCMASK(i)                               (CanChannelObject[i].RangeMask[3])
# define CANRANGE3ACCCODE(i)                               (CanChannelObject[i].RangeCode[3])

/* generated id type of the range */
# define CANRANGE0IDTYPE(i)                                (CanChannelObject[i].RangeIdType[0])
# define CANRANGE1IDTYPE(i)                                (CanChannelObject[i].RangeIdType[1])
# define CANRANGE2IDTYPE(i)                                (CanChannelObject[i].RangeIdType[2])
# define CANRANGE3IDTYPE(i)                                (CanChannelObject[i].RangeIdType[3])

# define APPL_CAN_MSG_RECEIVED( i )                        (CanChannelObject[(i)->Channel].ApplCanMsgReceivedFct(i))

# define APPLCANRANGE0PRECOPY( i )                         (CanChannelObject[(i)->Channel].ApplCanRangeFct[0](i))
# define APPLCANRANGE1PRECOPY( i )                         (CanChannelObject[(i)->Channel].ApplCanRangeFct[1](i))   
# define APPLCANRANGE2PRECOPY( i )                         (CanChannelObject[(i)->Channel].ApplCanRangeFct[2](i))   
# define APPLCANRANGE3PRECOPY( i )                         (CanChannelObject[(i)->Channel].ApplCanRangeFct[3](i))   

# define APPL_CAN_BUSOFF( i )                              (CanChannelObject[i].ApplCanBusOffFct(i))
# define APPL_CAN_WAKEUP( i )                              (CanChannelObject[i].ApplCanWakeUpFct(i))

# if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
#  define APPLCANCANCELNOTIFICATION( i, j )                (CanChannelObject[i].ApplCanCancelNotificationFct( j ))
# else
#  define APPLCANCANCELNOTIFICATION( i, j )
# endif

# if defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
#  define APPLCANMSGCANCELNOTIFICATION( i )                (CanChannelObject[i].ApplCanMsgTransmitCancelNotifyFct( i ))
# else
#  define APPLCANMSGCANCELNOTIFICATION( i )
# endif

# define CAN_RX_INDEX_TBL(channel, id)                      (CanRxIndexTbl[channel][id])

#endif


#if defined ( C_ENABLE_CAN_CAN_INTERRUPT_CONTROL )
# define CAN_CAN_INTERRUPT_DISABLE(channel)                        (CanCanInterruptDisable(CAN_CHANNEL_CANPARA_ONLY))
# define CAN_CAN_INTERRUPT_RESTORE(channel)                        (CanCanInterruptRestore(CAN_CHANNEL_CANPARA_ONLY))
#else
# define CAN_CAN_INTERRUPT_DISABLE(channel)
# define CAN_CAN_INTERRUPT_RESTORE(channel)
#endif


#if defined( C_ENABLE_INDIVIDUAL_POLLING )
/* define first index to array CanHwObjIndivPolling[][] */
#  define CAN_HWOBJINDIVPOLLING_INDEX0                     (canHwChannel)
#endif


/* mask for range enable status */
#define kCanRange0                                         ((vuint16)1)
#define kCanRange1                                         ((vuint16)2)
#define kCanRange2                                         ((vuint16)4)
#define kCanRange3                                         ((vuint16)8)


/* Assertions ---------------------------------------------------------------- */
/* lint -function(exit, ApplCanFatalError) */

/* lint -emacro( (506), assertUser) */
#if defined( C_ENABLE_USER_CHECK )
# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  define assertUser(p, c, e)                                if (!(p))   {ApplCanFatalError(e);}                    /* PRQA S 3412 */
# else
#  define assertUser(p, c, e)                                if (!(p))   {ApplCanFatalError((c), (e));}              /* PRQA S 3412 */
# endif
#else
# define assertUser(p, c, e)
#endif

/* lint -emacro( (506), assertGen) */
#if defined( C_ENABLE_GEN_CHECK )
# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  define assertGen(p, c, e)                                 if (!(p))   {ApplCanFatalError(e);}                    /* PRQA S 3412 */
# else
#  define assertGen(p, c, e)                                 if (!(p))   {ApplCanFatalError((c), (e));}              /* PRQA S 3412 */
# endif
#else
# define assertGen(p, c, e)
#endif

/* lint -emacro( (506), assertHardware) */
#if defined( C_ENABLE_HARDWARE_CHECK )
# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  define assertHardware(p, c, e)                            if (!(p))   {ApplCanFatalError(e);}                    /* PRQA S 3412 */
# else
#  define assertHardware(p, c, e)                            if (!(p))   {ApplCanFatalError((c), (e));}              /* PRQA S 3412 */
# endif
#else
# define assertHardware(p, c, e)
#endif

/* lint -emacro( (506), assertInternal) */
#if defined( C_ENABLE_INTERNAL_CHECK )
# if defined( C_SINGLE_RECEIVE_CHANNEL )
#  define assertInternal(p, c, e)                            if (!(p))   {ApplCanFatalError(e);}                   /* PRQA S 3412 */
# else
#  define assertInternal(p, c, e)                            if (!(p))   {ApplCanFatalError((c), (e));}             /* PRQA S 3412 */
# endif
#else
# define assertInternal(p, c, e)
#endif

#if defined( C_ENABLE_TRANSMIT_QUEUE )
#if defined( C_CPUTYPE_32BIT )
# define kCanTxQueueShift     5
#endif



/* mask used to get the flag index from the handle */
# define kCanTxQueueMask      (((vuint8)1 << kCanTxQueueShift) - (vuint8)1)


#if defined( C_SINGLE_RECEIVE_CHANNEL )
# define CAN_HL_TXQUEUE_PADBITS(channel)             ((CanTransmitHandle)0)
# define CAN_HL_TXQUEUE_STARTINDEX(channel)          ((CanSignedTxHandle)0)
# define CAN_HL_TXQUEUE_STOPINDEX(channel)           ((CanSignedTxHandle)kCanTxQueueSize)
#else
# define CAN_HL_TXQUEUE_PADBITS(channel)             ((CanTransmitHandle)CanTxQueuePadBits[(channel)])
# define CAN_HL_TXQUEUE_STARTINDEX(channel)          (CanTxQueueStartIndex[(channel)])
# define CAN_HL_TXQUEUE_STOPINDEX(channel)           (CanTxQueueStartIndex[(channel) + (CanChannelHandle)1])
#endif


#endif
# define CanMicroModeSystem()
# define CanMicroModeRestore()


#if defined( C_ENABLE_HW_LOOP_TIMER )
# if defined(C_MULTIPLE_RECEIVE_CHANNEL)
#  define CanLL_ApplCanTimerStart(loop)  ApplCanTimerStart(channel, loop)
#  define CanLL_ApplCanTimerEnd(loop)    ApplCanTimerEnd(channel, loop)
#  define CanLL_ApplCanTimerLoop(loop)   ApplCanTimerLoop(channel, loop)
# else
#  define CanLL_ApplCanTimerStart(loop)  ApplCanTimerStart(loop)
#  define CanLL_ApplCanTimerEnd(loop)    ApplCanTimerEnd(loop)
#  define CanLL_ApplCanTimerLoop(loop)   ApplCanTimerLoop(loop)
# endif
#else
# define CanLL_ApplCanTimerStart(loop)
# define CanLL_ApplCanTimerEnd(loop)
# define CanLL_ApplCanTimerLoop(loop)    (vuint8)(1)
#endif

#if defined( C_ENABLE_SLEEP_WAKEUP )
#define C_ENABLE_APPLCANWAKEUP_FCT
#endif

/* Tx normal index */
#define CAN_HW_TX_NORMAL_INDEX(x)      CAN_HL_HW_TX_NORMAL_INDEX(x)

/* Tx Start and Stop index */
#define CAN_HW_TX_STARTINDEX(x)        CAN_HL_HW_TX_STARTINDEX(x)
# if defined( C_CAN_MAX_BUFFER_32 ) || \
     defined( C_CAN_MAX_BUFFER_64 ) || \
     defined( C_CAN_MAX_BUFFER_MIXED )
#  if defined( C_CAN_MAX_BUFFER_32 )
#   define CAN_HW_TX_STOPINDEX(x)       ((vuint16)32)
#  endif
#  if defined( C_CAN_MAX_BUFFER_64 )
#   define CAN_HW_TX_STOPINDEX(x)       ((vuint16)64)
#  endif
#  if defined( C_CAN_MAX_BUFFER_MIXED )
#   define CAN_HW_TX_STOPINDEX(x)       (CanMaxMB[(x)])
#  endif
# else
#  if defined( C_ENABLE_MAX_BUFFER_64 )
#   define CAN_HW_TX_STOPINDEX(x)       ((vuint16)64)
#  else
#   define CAN_HW_TX_STOPINDEX(x)       ((vuint16)32)
#  endif
# endif

/* Tx Full Start and Stop index */
#define CAN_HW_TX_FULL_STARTINDEX(x)   CAN_HL_HW_TX_STARTINDEX(x)
# define CAN_HW_TX_FULL_STOPINDEX(x)   CAN_HL_HW_TX_NORMAL_INDEX(x)

/* Unused Start and Stop index */
#define CAN_HW_UNUSED_STARTINDEX(x)    CAN_HL_HW_UNUSED_STARTINDEX(x)
#define CAN_HW_UNUSED_STOPINDEX(x)     CAN_HL_HW_UNUSED_STOPINDEX(x)

/* Rx Full Start index */
#define CAN_HW_RX_FULL_STARTINDEX(x)   CAN_HL_HW_RX_FULL_STARTINDEX(x)


#define CAN_HW_RX_BASIC_STARTINDEX(x)  CAN_HL_HW_RX_BASIC_STARTINDEX(x)
#define CAN_HW_RX_BASIC_STOPINDEX(x)   CAN_HL_HW_RX_BASIC_STOPINDEX(x)

#if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
# if defined( C_HL_ENABLE_ADJUST_RXHANDLE ) && (kCanNumberOfRxFullCANObjects > 6)
#  define CAN_HW_RX_FULL_STOPINDEX(x)    (CAN_HL_HW_RX_FULL_STOPINDEX(x)+2)
# else
#  define CAN_HW_RX_FULL_STOPINDEX(x)    CAN_HL_HW_RX_FULL_STOPINDEX(x)
# endif
#endif


#if defined ( C_ENABLE_USER_MODE_OS )
# define CAN_WRITE_PROTECTED_REG(reg, val)        osWritePeripheral16(CanProtectedAreaId[canHwChannel], (vuint32)&(reg), (val))
# define CAN_WRITE_PROTECTED_REG_RESET(reg, bits) osModifyPeripheral16(CanProtectedAreaId[canHwChannel], (vuint32)&(reg), (vuint16)~(bits), (vuint16)0x0000u)
# define CAN_WRITE_PROTECTED_REG_SET(reg, bits)   osModifyPeripheral16(CanProtectedAreaId[canHwChannel], (vuint32)&(reg), (vuint16)0xFFFFu, (bits))
# define CAN_READ_PROTECTED_REG(reg)              osReadPeripheral16(CanProtectedAreaId[canHwChannel], (vuint32)&(reg))
#elif defined ( C_ENABLE_USER_MODE_APPL )
# define CAN_WRITE_PROTECTED_REG(reg, val)        ApplCanWriteProtectedRegister(&(reg), (vuint16)0xFFFFu, (val))
# define CAN_WRITE_PROTECTED_REG_RESET(reg, bits) ApplCanWriteProtectedRegister(&(reg), (bits), (vuint16)0x0000u)
# define CAN_WRITE_PROTECTED_REG_SET(reg, bits)   ApplCanWriteProtectedRegister(&(reg), (bits), (bits))
# define CAN_READ_PROTECTED_REG(reg)              ApplCanReadProtectedRegister(&(reg))
#else
# define CAN_WRITE_PROTECTED_REG(reg, val)        (reg) = (val)
# define CAN_WRITE_PROTECTED_REG_RESET(reg, bits) (reg) &= (vuint16)~(bits)
# define CAN_WRITE_PROTECTED_REG_SET(reg, bits)   (reg) |= (bits)
# define CAN_READ_PROTECTED_REG(reg)              (reg)
#endif

#if defined( C_ENABLE_WORKAROUND_ERRATA_E4019PS )
#define CAN_CLEAR_MDIS()                                                                                         \
if( (CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_MDIS_SLFWAKE_MASK) == kFlexCAN_MDIS_SLFWAKE_MASK ) \
{                                                                                                                \
  CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_SLF_WAK | kFlexCAN_WAK_MSK);                     \
  CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_MDIS);                                           \
  CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_SLF_WAK | kFlexCAN_WAK_MSK);                       \
}                                                                                                                \
else                                                                                                             \
{                                                                                                                \
  CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_MDIS);                                           \
}
#else
#define CAN_CLEAR_MDIS() CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_MDIS)
#endif

# define CanLL_TxIsHWObjFree(canHwChannel, txObjHandle) (((pFlexCAN(canHwChannel))->canObject[txObjHandle].control & kCodeMask) == kTxCodeFree)



#if defined( C_COMP_GHS_MPC55XX_FLEXCAN2 )        
# if defined( C_ENABLE_FLEXCAN_DOZE_MODE )
#  define CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY)  ((CAN_READ_PROTECTED_REG((pFlexCAN(canHwChannel))->canmcr) & kFlexCAN_MCR) == kFlexCAN_DOZE_MODE)
# else
#  define CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY)  ((CAN_READ_PROTECTED_REG((pFlexCAN(canHwChannel))->canmcr) & kFlexCAN_MCR) == kFlexCAN_DISABLE_MODE)
# endif
#endif
   
# define CanLL_HwIsStop(CAN_HW_CHANNEL_CANPARA_ONLY) ((CAN_READ_PROTECTED_REG((pFlexCAN(canHwChannel))->canmcr) & kFlexCAN_MCR) == kFlexCAN_FREEZE_MODE)

#define CanLL_HwIsBusOff(CAN_HW_CHANNEL_CANPARA_ONLY) (((pFlexCAN(canHwChannel))->estat & kFlexCAN_FCS_BOFF) != 0)

#if defined( C_ENABLE_EXTENDED_STATUS )
#  define CanLL_HwIsPassive(CAN_HW_CHANNEL_CANPARA_ONLY) (((pFlexCAN(canHwChannel))->estat & kFlexCAN_FCS) == kFlexCAN_FCS_EP)
#  define CanLL_HwIsWarning(CAN_HW_CHANNEL_CANPARA_ONLY) (((pFlexCAN(canHwChannel))->estat & kFlexCAN_RXTX_WARN) != 0)
#endif /* C_ENABLE_EXTENDED_STATUS */


# if defined ( C_ENABLE_TX_FULLCAN_DELAYED_START )
#  define CanGetMailboxDelayed(canHwChannel,hwobject)    (((canLL_canDelayedFullCANTxRequest[canHwChannel][(vuint8)(hwobject >>5)] >> ((vuint32)(hwobject & 0x001Fu))) & ((vuint32) 1)) == 1)
#  define CanSetMailboxDelayed(canHwChannel,hwobject)      (canLL_canDelayedFullCANTxRequest[canHwChannel][(vuint8)(hwobject >>5)] |=  (vuint32)(((vuint32) 1) << (vuint32)(hwobject & 0x001Fu)))
#  define CanClearMailboxDelayed(canHwChannel,hwobject)    (canLL_canDelayedFullCANTxRequest[canHwChannel][(vuint8)(hwobject >>5)] &= (vuint32)~(((vuint32) 1) << (vuint32)(hwobject & 0x001Fu)))
# endif

/* *********************************************************************** */
/* Defines / data types / structs / unions                                 */
/* *********************************************************************** */

#if defined( C_ENABLE_TRANSMIT_QUEUE )
#endif

/* *********************************************************************** */
/* Constants                                                               */
/* *********************************************************************** */

#if defined( C_ENABLE_TRANSMIT_QUEUE )
/* ROM CATEGORY 1 START */
/* lookup table for setting the flags in the queue */
V_MEMROM0 static V_MEMROM1 tCanQueueElementType V_MEMROM2 CanShiftLookUp[1 << kCanTxQueueShift] = 
{
#if defined( C_CPUTYPE_32BIT ) 
   (tCanQueueElementType)0x00000001, (tCanQueueElementType)0x00000002, (tCanQueueElementType)0x00000004, (tCanQueueElementType)0x00000008, 
   (tCanQueueElementType)0x00000010, (tCanQueueElementType)0x00000020, (tCanQueueElementType)0x00000040, (tCanQueueElementType)0x00000080
#endif

#if defined( C_CPUTYPE_32BIT ) 
 , (tCanQueueElementType)0x00000100, (tCanQueueElementType)0x00000200, (tCanQueueElementType)0x00000400, (tCanQueueElementType)0x00000800, 
   (tCanQueueElementType)0x00001000, (tCanQueueElementType)0x00002000, (tCanQueueElementType)0x00004000, (tCanQueueElementType)0x00008000
#endif

#if defined( C_CPUTYPE_32BIT )
 , (tCanQueueElementType)0x00010000, (tCanQueueElementType)0x00020000, (tCanQueueElementType)0x00040000, (tCanQueueElementType)0x00080000, 
   (tCanQueueElementType)0x00100000, (tCanQueueElementType)0x00200000, (tCanQueueElementType)0x00400000, (tCanQueueElementType)0x00800000,
   (tCanQueueElementType)0x01000000, (tCanQueueElementType)0x02000000, (tCanQueueElementType)0x04000000, (tCanQueueElementType)0x08000000, 
   (tCanQueueElementType)0x10000000, (tCanQueueElementType)0x20000000, (tCanQueueElementType)0x40000000, (tCanQueueElementType)0x80000000
#endif
};

/* returns the highest pending flag from the lower nibble */
V_MEMROM0 static V_MEMROM1 vsint8 V_MEMROM2 CanGetHighestFlagFromNibble[16] =        /* PRQA S 3218 */ /* Misra rule 8.7: only accessed in one function. - depends on configuration */
{    
  (vsint8)-1,                /* (vsint8)0xFF - changed due to misra; cast due to R32C */
  0x00,
  0x01, 0x01,
  0x02, 0x02, 0x02, 0x02,
  0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03
};
/* ROM CATEGORY 1 END */
#endif
/* Global constants with CAN driver main and subversion */
/* ROM CATEGORY 4 START*/
V_DEF_CONST(V_NONE, vuint8, CONST) kCanMainVersion   = (vuint8)(( DRVCAN_MAC7100FLEXCANHLL_VERSION ) >> 8);  /*lint !e572 !e778*/
V_DEF_CONST(V_NONE, vuint8, CONST) kCanSubVersion    = (vuint8)(DRVCAN_MAC7100FLEXCANHLL_VERSION & (vuint16)0x00FF);
V_DEF_CONST(V_NONE, vuint8, CONST) kCanBugFixVersion = (vuint8)(DRVCAN_MAC7100FLEXCANHLL_RELEASE_VERSION );
/* ROM CATEGORY 4 END*/

# if defined( C_ENABLE_MAX_BUFFER_64 )
#  define CanBitMask(x)      ((vuint32)((vuint32)0x01 << ((x) & (0x1F))))
#  define CanInvBitMask(x)   ((vuint32)~((vuint32)0x01 << ((x) & (0x1F))))
# else
#  define CanBitMask(x)      ((vuint32)((vuint32)0x01 << (x)))
#  define CanInvBitMask(x)   ((vuint32)~((vuint32)0x01 << (x)))
# endif

/* *********************************************************************** */
/* CAN-Hardware Data Definitions                                           */
/* *********************************************************************** */


/* *********************************************************************** */
/* external declarations                                                   */
/* *********************************************************************** */

#if !defined( CANDRV_SET_CODE_TEST_POINT )
# define CANDRV_SET_CODE_TEST_POINT(x)
#else
extern vuint8 tscCTKTestPointState[CTK_MAX_TEST_POINT];       /* PRQA S 3447 */
#endif

/* *********************************************************************** */
/* global data definitions                                                 */
/* *********************************************************************** */

/* RAM CATEGORY 1 START */
volatile CanReceiveHandle canRxHandle[kCanNumberOfChannels];        /* PRQA S 1514 */
/* RAM CATEGORY 1 END */

/* RAM CATEGORY 3 START */
#if defined( C_ENABLE_CONFIRMATION_FCT ) && \
    defined( C_ENABLE_DYN_TX_OBJECTS )   && \
    defined( C_ENABLE_TRANSMIT_QUEUE )
CanTransmitHandle          confirmHandle[kCanNumberOfChannels];
#endif
/* RAM CATEGORY 3 END */

/* RAM CATEGORY 1 START */
#if defined( C_ENABLE_CONFIRMATION_FLAG )
/* Msg(4:0750) A union type has been used. MISRA Rules 110 - no change */
V_MEMRAM0 volatile V_MEMRAM1_NEAR union CanConfirmationBits V_MEMRAM2_NEAR CanConfirmationFlags;       /* PRQA S 0759 */
#endif

#if defined( C_ENABLE_INDICATION_FLAG )
/* Msg(4:0750) A union type has been used. MISRA Rules 110 - no change */
V_MEMRAM0 volatile V_MEMRAM1_NEAR union CanIndicationBits   V_MEMRAM2_NEAR CanIndicationFlags;         /* PRQA S 0759 */
#endif
/* RAM CATEGORY 1 END */

/* RAM CATEGORY 1 START */
#if defined( C_ENABLE_VARIABLE_RX_DATALEN )
/* ##RI1.4 - 3.31: Dynamic Receive DLC */
volatile vuint8 canVariableRxDataLen[kCanNumberOfRxObjects];
#endif
/* RAM CATEGORY 1 END */

/* RAM CATEGORY 1 START */
CanChipDataPtr canRDSRxPtr[kCanNumberOfChannels];                  /* PRQA S 1514 */
/* RAM CATEGORY 1 END */
/* RAM CATEGORY 1 START */
CanChipDataPtr canRDSTxPtr[kCanNumberOfUsedTxCANObjects];          /* PRQA S 1514 */
/* RAM CATEGORY 1 END */


#if defined( C_ENABLE_RX_BASICCAN_OBJECTS ) || defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/* RAM CATEGORY 1 START*/
V_DEF_VAR(CAN_STATIC, tCanRxMsgBuffer, VAR_NOINIT) canRxMsgBuffer[kCanNumberOfHwChannels];
/* RAM CATEGORY 1 END*/
#endif

/* *********************************************************************** */
/* local data definitions                                                  */
/* *********************************************************************** */

/* support for CAN driver features : */
/* RAM CATEGORY 1 START */
static volatile CanTransmitHandle canHandleCurTxObj[kCanNumberOfUsedTxCANObjects];
/* RAM CATEGORY 1 END */

/* RAM CATEGORY 2 START */
#if defined( C_ENABLE_ECU_SWITCH_PASS )
static vuint8 canPassive[kCanNumberOfChannels];
#endif
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
#if defined( C_ENABLE_CAN_RAM_CHECK )
static vuint8 canComStatus[kCanNumberOfChannels]; /* stores the decision of the App after the last CAN RAM check */
#endif

#if defined( C_ENABLE_DYN_TX_OBJECTS )
static volatile vuint8 canTxDynObjReservedFlag[kCanNumberOfTxDynObjects];

# if defined( C_ENABLE_DYN_TX_ID )
static tCanTxId0 canDynTxId0[kCanNumberOfTxDynObjects];
#  if (kCanNumberOfUsedCanTxIdTables > 1)
static tCanTxId1 canDynTxId1[kCanNumberOfTxDynObjects];
#  endif
#  if (kCanNumberOfUsedCanTxIdTables > 2)
static tCanTxId2 canDynTxId2[kCanNumberOfTxDynObjects];
#  endif
#  if (kCanNumberOfUsedCanTxIdTables > 3)
static tCanTxId3 canDynTxId3[kCanNumberOfTxDynObjects];
#  endif
#  if (kCanNumberOfUsedCanTxIdTables > 4)
static tCanTxId4 canDynTxId4[kCanNumberOfTxDynObjects];
#  endif
#  if defined( C_ENABLE_MIXED_ID )
static tCanIdType                 canDynTxIdType[kCanNumberOfTxDynObjects];
#  endif
# endif

# if defined( C_ENABLE_DYN_TX_DLC )
static vuint8                   canDynTxDLC[kCanNumberOfTxDynObjects];
# endif
# if defined( C_ENABLE_DYN_TX_DATAPTR )
static TxDataPtr                  canDynTxDataPtr[kCanNumberOfTxDynObjects];
# endif
# if defined( C_ENABLE_CONFIRMATION_FCT )
# endif 
#endif /* C_ENABLED_DYN_TX_OBJECTS */


#if defined( C_ENABLE_TX_MASK_EXT_ID )
static tCanTxId0 canTxMask0[kCanNumberOfChannels];
# if (kCanNumberOfUsedCanTxIdTables > 1)
static tCanTxId1 canTxMask1[kCanNumberOfChannels];
# endif
# if (kCanNumberOfUsedCanTxIdTables > 2)
static tCanTxId2 canTxMask2[kCanNumberOfChannels];
# endif
# if (kCanNumberOfUsedCanTxIdTables > 3)
static tCanTxId3 canTxMask3[kCanNumberOfChannels];
# endif
# if (kCanNumberOfUsedCanTxIdTables > 4)
static tCanTxId4 canTxMask4[kCanNumberOfChannels];
# endif
#endif

#if defined( C_ENABLE_VARIABLE_DLC )
static vuint8 canTxDLC_RAM[kCanNumberOfTxObjects];
#endif

static volatile vuint8 canStatus[kCanNumberOfChannels];

# if defined( C_ENABLE_PART_OFFLINE )
static vuint8 canTxPartOffline[kCanNumberOfChannels];
# endif
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 1 START */

#if defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL) && !defined (C_ENABLE_OSEK_CAN_INTCTRL)
static vsintx          canCanInterruptCounter[kCanNumberOfChannels];        /* lint !e551 */
# if defined( C_HL_ENABLE_CAN_IRQ_DISABLE )
static tCanLLCanIntOld canCanInterruptOldStatus[kCanNumberOfHwChannels];
# endif
#endif
/* RAM CATEGORY 1 END */

#if defined( C_HL_ENABLE_LAST_INIT_OBJ )
/* RAM CATEGORY 4 START */
static CanInitHandle lastInitObject[kCanNumberOfChannels];
/* RAM CATEGORY 4 END */
#endif
#if defined( C_ENABLE_TX_POLLING )          || \
    defined( C_ENABLE_RX_FULLCAN_POLLING )  || \
    defined( C_ENABLE_RX_BASICCAN_POLLING ) || \
    defined( C_ENABLE_ERROR_POLLING )       || \
    defined( C_ENABLE_WAKEUP_POLLING )      || \
    (defined( C_HL_ENABLE_CANCEL_IN_HW_TASK ) && defined( C_ENABLE_CANCEL_IN_HW ))
/* RAM CATEGORY 2 START */
static vuint8 canPollingTaskActive[kCanNumberOfChannels];
/* RAM CATEGORY 2 END */
#endif

/* RAM CATEGORY 1 START */
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )  || \
    defined( C_ENABLE_RX_BASICCAN_OBJECTS )
static tCanRxInfoStruct        canRxInfoStruct[kCanNumberOfChannels];
#endif
#if defined( C_ENABLE_CAN_TX_CONF_FCT )
/* ##RI-1.10 Common Callbackfunction in TxInterrupt */
static tCanTxConfInfoStruct    txInfoStructConf[kCanNumberOfChannels];
#endif

#if defined( C_ENABLE_COND_RECEIVE_FCT )
static volatile vuint8 canMsgCondRecState[kCanNumberOfChannels];
#endif

#if defined( C_ENABLE_RX_QUEUE )
static tCanRxQueue canRxQueue;         /* the rx queue (buffer and queue variables) */
#endif
/* RAM CATEGORY 1 END */

#if defined( C_ENABLE_TRANSMIT_QUEUE )
/* RAM CATEGORY 1 START */
static volatile tCanQueueElementType canTxQueueFlags[kCanTxQueueSize];
/* RAM CATEGORY 1 END */
#endif
# if defined (C_ENABLE_TX_FULLCAN_DELAYED_START)
/* RAM CATEGORY 1 START*/
V_DEF_VAR(CAN_STATIC volatile, vuint32, VAR_NOINIT) canLL_canDelayedFullCANTxRequest[kCanNumberOfChannels][2];
/* RAM CATEGORY 1 END*/
# endif /* C_ENABLE_TX_FULLCAN_DELAYED_START */








#if defined( C_ENABLE_UPDATE_BASE_ADDRESS )
/* RAM CATEGORY 1 START*/
V_DEF_P2VAR(V_NONE, vuint32, VAR_NOINIT, REG_CANCELL) canLL_VirtualPtrField[kCanNumberOfHwChannels];
V_DEF_P2VAR(V_NONE, vuint32, VAR_NOINIT, REG_CANCELL) canLL_VirtualPtrFieldTemp[kCanNumberOfHwChannels];
/* RAM CATEGORY 1 END*/
#endif


/* *********************************************************************** */
/*  local prototypes                                                       */
/* *********************************************************************** */
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )  || \
    defined( C_ENABLE_RX_BASICCAN_OBJECTS )
# if defined( C_ENABLE_RX_QUEUE )
/* CODE CATEGORY 1 START */
static vuint8 CanHL_ReceivedRxHandleQueue(CAN_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 1 END */
# endif
/* CODE CATEGORY 1 START */
# if ( kCanNumberOfRxObjects > 0 )
#  if defined( C_ENABLE_RX_QUEUE )
static vuint8 CanHL_ReceivedRxHandle( CAN_CHANNEL_CANTYPE_FIRST tCanRxInfoStruct *pCanRxInfoStruct );
#  else
static vuint8 CanHL_ReceivedRxHandle( CAN_CHANNEL_CANTYPE_ONLY );
#  endif
# endif /* ( kCanNumberOfRxObjects > 0 ) */ 
/* CODE CATEGORY 1 END */
# if defined( C_ENABLE_INDICATION_FLAG ) || \
     defined( C_ENABLE_INDICATION_FCT )
/* CODE CATEGORY 1 START */
static void CanHL_IndRxHandle( CanReceiveHandle rxHandle );
/* CODE CATEGORY 1 END */
# endif
#endif
#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/* CODE CATEGORY 1 START */
static void CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle);  
/* CODE CATEGORY 1 END */
#endif
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/* CODE CATEGORY 1 START */
static void CanFullCanMsgReceived(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle);
/* CODE CATEGORY 1 END */
#endif

/* CODE CATEGORY 1 START */
static void CanHL_TxConfirmation(CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txObjHandle);
/* CODE CATEGORY 1 END */
# if defined( C_ENABLE_CAN_TRANSMIT )
/* CODE CATEGORY 1 START */
static vuint8 CanCopyDataAndStartTransmission(CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txObjHandle, CanTransmitHandle txHandle)  C_API_3;   /* lint !e14 !e31 */
/* CODE CATEGORY 1 END */
# endif   /* C_ENABLE_CAN_TRANSMIT */

#if defined( C_ENABLE_TRANSMIT_QUEUE )
/* CODE CATEGORY 4 START */
static void CanDelQueuedObj( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3;
/* CODE CATEGORY 4 END */
# if defined( C_ENABLE_TX_POLLING ) || \
     (defined( C_HL_ENABLE_CANCEL_IN_HW_TASK )  && defined( C_ENABLE_CANCEL_IN_HW ))
/* CODE CATEGORY 2 START */
static void CanHl_RestartTxQueue( CAN_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 2 END */
# endif
#endif 

/* CODE CATEGORY 2 START */
static void CanHL_ErrorHandling( CAN_HW_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 2 END */

#if defined( C_ENABLE_VARIABLE_RX_DATALEN )
/* CODE CATEGORY 1 START */
static void CanSetVariableRxDatalen ( CanReceiveHandle rxHandle, vuint8 dataLen );
/* CODE CATEGORY 1 END */
#endif


#if defined( C_ENABLE_RX_BASICCAN_OBJECTS ) || defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/* CODE CATEGORY 1 START*/
V_DEF_FUNC_API(CAN_STATIC, void, STATIC_CODE) CanLL_CopyFromCan(CanChipVoidPtr dst, CanChipDataPtr src, vuint8 len);
/* CODE CATEGORY 1 END*/
#endif

#if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING ) 
# if defined( C_ENABLE_WORKAROUND_ERRATA_5164 )
/* CODE CATEGORY 2 START*/
V_DEF_FUNC_API(CAN_STATIC, vuint16, STATIC_CODE) CanErrata5164WorkaroundBegin(CAN_HW_CHANNEL_CANTYPE_ONLY);
V_DEF_FUNC_API(CAN_STATIC, void, STATIC_CODE) CanErrata5164WorkaroundEnd(CAN_HW_CHANNEL_CANTYPE_FIRST vuint16 canMcrReg);
/* CODE CATEGORY 2 END*/
# endif
#endif 

#if defined( C_ENABLE_SLEEP_WAKEUP ) && defined( C_ENABLE_FLEXCAN_DOZE_MODE )
/* CODE CATEGORY 4 START*/
V_DEF_FUNC_API(CAN_STATIC, void, STATIC_CODE) CanLL_WakeUpHandling(CAN_HW_CHANNEL_CANTYPE_ONLY);
/* CODE CATEGORY 4 END*/
#endif

#if defined( C_ENABLE_CAN_RAM_CHECK )
/* CODE CATEGORY 4 START*/
V_DEF_FUNC_API(CAN_STATIC, vuint8, STATIC_CODE) CanLL_IsMailboxCorrupt(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle hwObjHandle);
/* CODE CATEGORY 4 END*/
#endif


#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
    defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
    defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
# if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
#  if defined( C_ENABLE_MAX_BUFFER_64 )
#   if defined ( C_CAN_MAX_BUFFER_MIXED )
#    define   CAN_DISABLE_RXTX_INTERRUPT(canFlagPtr)                               \
          (canFlagPtr)->lowerflags = pFlexcan->imask_lo; pFlexcan->imask_lo = 0;   \
          if( CanMaxMB[canHwChannel] == 64 )                                       \
          {                                                                        \
            (canFlagPtr)->upperflags = pFlexcan->imask_hi; pFlexcan->imask_hi = 0; \
          }                                                     
#    define   CAN_RESTORE_RXTX_INTERRUPT(canFlag)                                  \
          pFlexcan->imask_lo = (canFlag).lowerflags;                                 \
          if( CanMaxMB[canHwChannel] == 64 )                                       \
          {                                                                        \
            pFlexcan->imask_hi = (canFlag).upperflags;                               \
          }
#   else /* C_CAN_MAX_BUFFER_MIXED */
#    define   CAN_DISABLE_RXTX_INTERRUPT(canFlagPtr) (canFlagPtr)->lowerflags = pFlexcan->imask_lo; pFlexcan->imask_lo = 0; \
                                                     (canFlagPtr)->upperflags = pFlexcan->imask_hi; pFlexcan->imask_hi = 0
#    define   CAN_RESTORE_RXTX_INTERRUPT(canFlag)    pFlexcan->imask_lo = (canFlag).lowerflags; \
                                                     pFlexcan->imask_hi = (canFlag).upperflags
#   endif /* C_CAN_MAX_BUFFER_MIXED */
#  else /* C_ENABLE_MAX_BUFFER_64 */
#   define   CAN_DISABLE_RXTX_INTERRUPT(canFlagPtr) (canFlagPtr)->lowerflags = pFlexcan->imask_lo; pFlexcan->imask_lo = 0 /* SBSW_CAN_LL016, SBSW_CAN_LL017 */
#   define   CAN_RESTORE_RXTX_INTERRUPT(canFlag)    pFlexcan->imask_lo = (canFlag).lowerflags /* SBSW_CAN_LL017 */
#  endif /* C_ENABLE_MAX_BUFFER_64 */
# else
#  define   CAN_DISABLE_RXTX_INTERRUPT(canFlagPtr)
#  define   CAN_RESTORE_RXTX_INTERRUPT(canFlag)
# endif
# if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )     
#  define CAN_DISABLE_BUSOFF_INTERRUPT(canFlagPtr)  (canFlagPtr)->canctrl0 = pFlexcan->control0; pFlexcan->control0 &= kNotFlexCANErrBoff /* SBSW_CAN_LL016, SBSW_CAN_LL017 */
#  define CAN_RESTORE_BUSOFF_INTERRUPT(canFlag)     pFlexcan->control0 |= (vuint16)((canFlag).canctrl0 & (vuint16)~kNotFlexCANErrBoff) /* SBSW_CAN_LL017 */
# else
#  define CAN_DISABLE_BUSOFF_INTERRUPT(canFlagPtr)
#  define CAN_RESTORE_BUSOFF_INTERRUPT(canFlag)
# endif 
# if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
#  define CAN_DISABLE_WAKEUP_INTERRUPT(canFlagPtr)  (canFlagPtr)->canmcr = CAN_READ_PROTECTED_REG(pFlexcan->canmcr); CAN_WRITE_PROTECTED_REG_RESET(pFlexcan->canmcr, kFlexCAN_WAK_MSK)
#  define CAN_RESTORE_WAKEUP_INTERRUPT(canFlag)     CAN_WRITE_PROTECTED_REG_SET(pFlexcan->canmcr, (vuint16)((canFlag).canmcr & kFlexCAN_WAK_MSK))
# else
#  define CAN_DISABLE_WAKEUP_INTERRUPT(canFlagPtr)
#  define CAN_RESTORE_WAKEUP_INTERRUPT(canFlag)
# endif
#endif

/* *********************************************************************** */
/*  Error Check                                                            */
/* *********************************************************************** */

/* *************** error check for Organi process ************************ */







/* *************** error check for not supported feature  ****************** */
#if defined( ERROR_C_ENABLE_MSG_TRANSMIT )
# error "Low Level Message Transmit is not supported with this CAN driver implementation"
#endif

#if defined( ERROR_C_ENABLE_INDIVIDUAL_POLLING )
# error "Individual polling is not supported with this CAN driver implementation"
#endif

#if defined( ERROR_C_ENABLE_MULTIPLE_BASICCAN )
# error "Multiple Basic CAN is not supported with this CAN driver implementation"
#endif

#if defined( ERROR_C_ENABLE_RX_QUEUE )
# error "Rx Queue is not supported with this CAN driver implementation"
#endif

#if defined( C_ENABLE_COMMON_CAN )
# error "Common CAN is not supported with this CAN driver implementation"
#endif

#if defined( C_ENABLE_MULTI_ECU_CONFIG )
# error "Multiple Configuration is not supported with this CAN driver implementation"
#endif

#if defined( C_ENABLE_CAN_RAM_CHECK_EXTENDED )
# error "Extended RAM Check is not supported with this CAN driver implementation"
#endif

#if (VSTDLIB__COREHLL_VERSION  <  0x0213 )
# error "Incompatible version of VStdLib. Core Version 2.13.00 or higher is necessary."
#endif


#if (kCanNumberOfHwChannels > 255)
#  error "Too many CAN channels. This driver can only handle up to 255 channels"
#endif

#if defined( C_SEARCH_HASH )
# if !defined( kHashSearchListCountEx )
#  error "kHashSearchListCountEx not defined"
# endif
# if !defined( kHashSearchMaxStepsEx )
#  error "kHashSearchMaxStepsEx not defined"
# endif
# if !defined( kHashSearchListCount )
#  error "kHashSearchListCount not defined"
# endif
# if !defined( kHashSearchMaxSteps )
#  error "kHashSearchMaxSteps not defined"
# endif
# if ( (kHashSearchMaxStepsEx < 1) ||(kHashSearchMaxStepsEx > 32768) )
#  error "kHashSearchMaxStepsEx has ilegal value"
# endif
# if ( kHashSearchListCountEx > 32768 )
#  error "Hash table for extended ID is too large"
# endif
# if ( (kHashSearchMaxSteps < 1) ||(kHashSearchMaxSteps > 32768) )
#  error "kHashSearchMaxStepsEx has ilegal value"
# endif
# if ( kHashSearchListCount > 32768 )
#  error "Hash table for standard ID is too large"
# endif
# if !defined( C_ENABLE_EXTENDED_ID) && (kHashSearchListCountEx > 0)
#  error "kHashSearchListCountEx has to be 0 in this configuration"
# endif
# if defined( C_ENABLE_EXTENDED_ID) && !defined( C_ENABLE_MIXED_ID) &&(kHashSearchListCount > 0)
#  error "kHashSearchListCount has to be 0 in this configuration"
# endif
#endif





#if defined( C_ENABLE_RX_QUEUE )
# if !defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
#  error "RX-Queue requires C_HL_ENABLE_RX_INFO_STRUCT_PTR"
# endif
#endif

#if defined( C_SEARCH_INDEX ) && defined( C_ENABLE_EXTENDED_ID )
# error "Index search is not possible with extended ID's"
#endif /* defined( C_SEARCH_INDEX ) */



#if defined ( CAN_POLLING_IRQ_DISABLE ) || defined ( CAN_POLLING_IRQ_RESTORE )
# error "Feature has changed - use C_DISABLE_CAN_CAN_INTERRUPT_CONTROL to remove the CAN interrupt disabling"
#endif



/* *********************************************************************** */
/*  Functions                                                              */
/* *********************************************************************** */



# if defined( C_ENABLE_MEMCOPY_SUPPORT )
/****************************************************************************
| NAME:             CanCopyFromCan
| CALLED BY:        Application
| PRECONDITIONS:    none
|
| INPUT PARAMETERS: void *             dst        | pointer to destionation buffer
|                   CanChipDataPtr     src        | pointer to CAN buffer
|                   vuint8             len        | number of bytes to copy
|
| RETURN VALUES:    -
|
| DESCRIPTION:      copy data from CAN receive buffer to RAM.
|
| ATTENTION:        
****************************************************************************/
/* Msg(4:3673) The object addressed by the pointer "txMsgStruct" is not modified in this function.
   The use of "const" should be considered to indicate that it never changes. MISRA Rule 81 - no change */
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanCopyFromCan(CanChipVoidPtr dst, CanChipDataPtr src, vuint8 len) /* PRQA S 3673 */ /* suppress message about const pointer */
{
  while(len != 0)
  {
    len--;
    ((CanChipDataPtr)dst)[len] = (src)[len];
  }
}
/* CODE CATEGORY 1 END */

/****************************************************************************
| NAME:             CanCopyToCan
| CALLED BY:        Application
| PRECONDITIONS:    none
|
| INPUT PARAMETERS: void *             src        | pointer to source buffer
|                   CanChipDataPtr     dst        | pointer to CAN buffer
|                   vuint8             len        | number of bytes to copy
|
| RETURN VALUES:    -
|
| DESCRIPTION:      copy data from CAN receive buffer to RAM.
|
| ATTENTION:        
****************************************************************************/
/* Msg(4:3673) The object addressed by the pointer "txMsgStruct" is not modified in this function.
   The use of "const" should be considered to indicate that it never changes. MISRA Rule 81 - no change */
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanCopyToCan(CanChipDataPtr dst, V_DEF_P2VAR_PARA(V_NONE, void, AUTOMATIC, APPL_VAR) src, vuint8 len) C_API_3       /* PRQA S 3673 */     /* suppress message about const pointer */
{
  while(len != 0)
  {
    len--;
    (dst)[len] = ((CanChipDataPtr)src)[len];
  }
}
/* CODE CATEGORY 1 END */
# endif

# if defined( C_ENABLE_TX_FULLCAN_DELAYED_START )
/************************************************************************
| NAME:               CanTxFullCanDelayedStart
| CALLED BY:          Application 
| Preconditions:      none
| PARAMETER:          none
| RETURN VALUE:       none
| Description:        This function requests the transmission for hardware
|                     objects which are pending to be send.
*************************************************************************/
/* CODE CATEGORY 1 START*/
V_DEF_FUNC_API(V_NONE, void, CODE) CanTxFullCanDelayedStart(CAN_CHANNEL_CANTYPE_ONLY)
{
  CanDeclareGlobalInterruptOldStatus
  vuint8 txObjHandle;
# if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
  tFLEXCANPtr pFlexCANLocal;
# else
  tFlexcanPtr pFlexCANLocal;
# endif

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);    /* PRQA S 3109 */
# endif

# if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
  pFlexCANLocal = pFLEXCAN(canHwChannel);
# else
  pFlexCANLocal = pFlexCAN(canHwChannel);
# endif

  /* Disable global interrupts */
  CanNestedGlobalInterruptDisable();
  
  /* Tx FullCANs are sorted by their priority so the ID with the highest priority has the lowest txObjHandle */
  for(txObjHandle=CAN_HL_HW_TX_STARTINDEX(canHwChannel); txObjHandle<CAN_HL_HW_TX_STOPINDEX(canHwChannel); txObjHandle++)
  {
    if (CanGetMailboxDelayed(channel,txObjHandle))
    {
      pFlexCANLocal->canObject[txObjHandle].control |= kTxCodeTransmit; /* start tx of the message */ /* SBSW_CAN_LL012 */
    }
  }
  /* Clear the internal Tx fullcan pendings */
  canLL_canDelayedFullCANTxRequest[channel][0] = 0;
  canLL_canDelayedFullCANTxRequest[channel][1] = 0;
  /* Restore global interrupts */
  CanNestedGlobalInterruptRestore();
}
/* CODE CATEGORY 1 END*/
# endif /* C_ENABLE_TX_FULLCAN_DELAYED_START */


# if defined( C_ENABLE_RX_BASICCAN_OBJECTS ) || defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/****************************************************************************
| NAME:             CanLL_CopyFromCan
| CALLED BY:        CAN driver internal
| PRECONDITIONS:    none
|
| INPUT PARAMETERS: void *             dst        | pointer to destionation buffer
|                   CanChipDataPtr     src        | pointer to CAN buffer
|                   vuint8             len        | number of bytes to copy
|
| RETURN VALUES:    -
|
| DESCRIPTION:      copy data from CAN receive buffer to RAM.
|
| ATTENTION:
****************************************************************************/
/* CODE CATEGORY 1 START*/
V_DEF_FUNC_API(CAN_STATIC, void, STATIC_CODE) CanLL_CopyFromCan(CanChipVoidPtr dst, CanChipDataPtr src, vuint8 len)    /* PRQA S 3673 */      /* suppress message about const pointer */
{
  while(len != 0)
  {
    len--;
    ((CanChipDataPtr)dst)[len] = ((CanChipDataPtr)src)[len];
  }  
}
/* CODE CATEGORY 1 END*/
# endif

#if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
    defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
    defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/***************************************************************************
| NAME:               CanLL_CanInterruptDisable                                          
| CALLED BY:          CAN driver               
| PRECONDITIONS:                                                
| PARAMETER:          ptr to storage variable for channel's IMASK register
|                     and a handle to a channel
| RETURN VALUE:       none                                          
| DESCRIPTION:        Disable the CAN interrupts for a specific channel
|                     by resetting the IMASK register to 0. The initial
|                     value of the IMASK register is stored in 
|                     localInterruptOldFlagPtr.
***************************************************************************/
# define CanLL_CanInterruptDisable(x, canFlagPtr)  \
  {                                                \
    tFlexcanPtr pFlexcan = pFlexCAN(x);            \
    CanMicroModeSystem();                          \
    CAN_DISABLE_RXTX_INTERRUPT(canFlagPtr);        \
    CAN_DISABLE_BUSOFF_INTERRUPT(canFlagPtr);      \
    CAN_DISABLE_WAKEUP_INTERRUPT(canFlagPtr);      \
    CanMicroModeRestore();                         \
  }

/***************************************************************************
| NAME:               CanLL_CanInterruptRestore                                          
| CALLED BY:          CAN driver               
| PRECONDITIONS:      A call to CanLL_CanInterruptDisable had to occur before
|                     a call to this function.                                          
| PARAMETER:          variable holding saved IMASK register for the channel
|                     and a handle to the channel
| RETURN VALUE:       none                                          
| DESCRIPTION:        Restored the CAN interrupts by restoring the value of
|                     the IMASK register.
***************************************************************************/
# define CanLL_CanInterruptRestore(x, canFlag)  \
  {                                             \
    tFlexcanPtr pFlexcan = pFlexCAN(x);         \
    CanMicroModeSystem();                       \
    CAN_RESTORE_RXTX_INTERRUPT(canFlag);        \
    CAN_RESTORE_BUSOFF_INTERRUPT(canFlag);      \
    CAN_RESTORE_WAKEUP_INTERRUPT(canFlag);      \
    CanMicroModeRestore();                      \
  }
#else
# define CanLL_CanInterruptDisable(x,y)
# define CanLL_CanInterruptRestore(x,y)
#endif   /* C_ENABLE_CAN_..._INTERRUPT */

#if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING ) 
# if defined( C_ENABLE_WORKAROUND_ERRATA_5164 )
/****************************************************************************
| NAME:             CanErrata5164WorkaroundBegin
| CALLED BY:        CanInit
| PRECONDITIONS:    none
|
| INPUT PARAMETERS: - 
|
| RETURN VALUES:    vuint16 canMcrReg which stores the CANx_MCR
|
| DESCRIPTION:      This function switches FlexCAN A and FlexCAN C into
|                   freeze mode.
****************************************************************************/
/* CODE CATEGORY 2 START */
V_DEF_FUNC_API(CAN_STATIC, vuint16, STATIC_CODE) CanErrata5164WorkaroundBegin(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  tFlexcanPtr pFlexCANA;  
  tFlexcanPtr pFlexCANC;  
  vuint16  canMcrReg;
  vuint8   loopResult;

  CanMicroModeSystem();
  
  pFlexCANA = (tFlexcanPtr)0xFFFC0000UL;
  pFlexCANC = (tFlexcanPtr)0xFFFC8000UL;
  
  /* Save the MCR value for the channel NOT being initialized */
  if (pFlexCAN(canHwChannel) == 0xFFFC0000)
  {
    /* FlexCAN A is being initialized so save the MCR value for FlexCAN C */
    canMcrReg = CAN_READ_PROTECTED_REG(pFlexCANC->canmcr);
  }
  else if (pFlexCAN(canHwChannel) == 0xFFFC8000)
  {
    /* FlexCAN C is being initialized so save the MCR value for FlexCAN A */
    canMcrReg = CAN_READ_PROTECTED_REG(pFlexCANA->canmcr);
  }
     
  /* The workaround is only necessary for FlexCAN A and FlexCAN C */
  if((pFlexCAN(canHwChannel) == ((tFlexcanPtr)0xFFFC0000)) ||
     (pFlexCAN(canHwChannel) == ((tFlexcanPtr)0xFFFC8000)))
  {
    if((CAN_READ_PROTECTED_REG(pFlexCANC->canmcr) & kFlexCAN_MDIS) != (vuint16)0)
    {      
      CanLL_ApplCanTimerStart(kCanLoopSetDisable);
      do /* wait until FlexCAN C is disabled */
      { 
        loopResult = CanLL_ApplCanTimerLoop(kCanLoopSetDisable);
      }while(((CAN_READ_PROTECTED_REG(pFlexCANC->canmcr) & kFlexCAN_LPM_ACK) == (vuint16)0) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */
      CanLL_ApplCanTimerEnd(kCanLoopSetDisable);  
    

      /* enable FlexCAN C */
      CAN_WRITE_PROTECTED_REG_RESET(pFlexCANC->canmcr, kFlexCAN_MDIS);
    }

    if((CAN_READ_PROTECTED_REG(pFlexCANA->canmcr) & kFlexCAN_MDIS) != (vuint16)0)
    {      
      CanLL_ApplCanTimerStart(kCanLoopSetDisable);
      do /* wait until FlexCAN A is disabled */
      { 
        loopResult = CanLL_ApplCanTimerLoop(kCanLoopSetDisable);
      }while(((CAN_READ_PROTECTED_REG(pFlexCANA->canmcr) & kFlexCAN_LPM_ACK) == (vuint16)0) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */
      CanLL_ApplCanTimerEnd(kCanLoopSetDisable);  
    
    
      /* enable FlexCAN A */
      CAN_WRITE_PROTECTED_REG_RESET(pFlexCANA->canmcr, kFlexCAN_MDIS);
    }

    /* Freeze FlexCAN C before FlexCAN A to avoid register corruption in FlexCAN C */
    CAN_WRITE_PROTECTED_REG_SET(pFlexCANC->canmcr, kFlexCAN_FRZ); /* first set FREEZE bit */
    CAN_WRITE_PROTECTED_REG_SET(pFlexCANC->canmcr, kFlexCAN_HALT);   /* then set HALT bit */
        
    CanLL_ApplCanTimerStart(kCanLoopSetFreeze);
    do /* wait until FlexCAN C is in FREEZE mode */
    {
      loopResult = CanLL_ApplCanTimerLoop(kCanLoopSetFreeze);
    }while(((CAN_READ_PROTECTED_REG(pFlexCANC->canmcr) & kFlexCAN_FRZ_ACK) == (vuint16)0) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */
    CanLL_ApplCanTimerEnd(kCanLoopSetFreeze);  
    
    /* Freeze FlexCAN A next to allow register modifications in either FlexCAN A or C */
    CAN_WRITE_PROTECTED_REG_SET(pFlexCANA->canmcr, kFlexCAN_FRZ); /* first set FREEZE bit */
    CAN_WRITE_PROTECTED_REG_SET(pFlexCANA->canmcr, kFlexCAN_HALT);   /* then set HALT bit */
        
    CanLL_ApplCanTimerStart(kCanLoopSetFreeze);
    do /* wait until FlexCAN A is in FREEZE mode */
    {
      loopResult = CanLL_ApplCanTimerLoop(kCanLoopSetFreeze);
    }while(((CAN_READ_PROTECTED_REG(pFlexCANA->canmcr) & kFlexCAN_FRZ_ACK) == (vuint16)0) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */
    CanLL_ApplCanTimerEnd(kCanLoopSetFreeze);  
  }

  CanMicroModeRestore();
    
  return canMcrReg;
}
/* CODE CATEGORY 2 END */

/****************************************************************************
| NAME:             CanErrata5164WorkaroundEnd
| CALLED BY:        CanInit
| PRECONDITIONS:    none
|
| INPUT PARAMETERS: vuint16 canMcrReg which stores the old CANx_MCR
|
| RETURN VALUES:    -
|
| DESCRIPTION:      This function restores the operation mode of FlexCAN A
|                   and FlexCAN C.
****************************************************************************/
/* CODE CATEGORY 2 START*/
V_DEF_FUNC_API(CAN_STATIC, void, STATIC_CODE) CanErrata5164WorkaroundEnd(CAN_HW_CHANNEL_CANTYPE_FIRST vuint16 canMcrReg)
{
  tFlexcanPtr pFlexCANA;    
  tFlexcanPtr pFlexCANC;  
  vuint8   loopResult;
  
  CanMicroModeSystem();
  
  pFlexCANA = (tFlexcanPtr)0xFFFC0000UL;
  pFlexCANC = (tFlexcanPtr)0xFFFC8000UL;
    
  /* The workaround is only necessary for FlexCAN A and FlexCAN C */
  if((pFlexCAN(canHwChannel) == ((tFlexcanPtr)0xFFFC0000)) ||
     (pFlexCAN(canHwChannel) == ((tFlexcanPtr)0xFFFC8000)))
  {
    /* If FlexCAN C is being initialized, we need to restore the previous state of FlexCAN A
       rather than unconditionally unfreezing it.  In any case FlexCAN A is always first. */
    if(pFlexCAN(canHwChannel) == ((tFlexcanPtr)0xFFFC8000))
    {
      if((canMcrReg & kFlexCAN_MDIS) != (vuint16)0)
      {     
        CAN_WRITE_PROTECTED_REG_SET(pFlexCANA->canmcr, kFlexCAN_MDIS); /* disable FlexCAN A */
      }
      else
      {
        if((canMcrReg & kFlexCAN_HALT) == (vuint16)0)
        {     
          CAN_WRITE_PROTECTED_REG_RESET(pFlexCANA->canmcr, kFlexCAN_HALT);   /* clear HALT bit */
        }
        if((canMcrReg & kFlexCAN_FRZ) == (vuint16)0)
        {
          CAN_WRITE_PROTECTED_REG_RESET(pFlexCANA->canmcr, kFlexCAN_FRZ); /* clear FRZ bit */
        }

        /* If both HALT and FRZ bits were cleared, wait for freeze mode to exit to avoid
           corruption in FlexCAN C */
        if(((canMcrReg & kFlexCAN_HALT) == (vuint16)0) &&
          ((canMcrReg & kFlexCAN_FRZ) == (vuint16)0))
        {
          CanLL_ApplCanTimerStart(kCanLoopClearFreeze);
          do /* wait until FlexCAN A is not in FREEZE mode */
          {
            loopResult = CanLL_ApplCanTimerLoop(kCanLoopClearFreeze);
          }while(((CAN_READ_PROTECTED_REG(pFlexCANA->canmcr) & kFlexCAN_FRZ_ACK) != (vuint16)0) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */
          CanLL_ApplCanTimerEnd(kCanLoopClearFreeze);
        }
      }
    }
    /* FlexCAN A was being initialized and initialization is complete - unfreeze it now.
       FlexCAN A must be unfrozen before FlexCAN C to avoid corruption in FlexCAN C. */
    else
    {
      CAN_WRITE_PROTECTED_REG_RESET(pFlexCANA->canmcr, kFlexCAN_HALT);   /* clear HALT bit */
      CAN_WRITE_PROTECTED_REG_RESET(pFlexCANA->canmcr, kFlexCAN_FRZ); /* clear FRZ bit */
      
      CanLL_ApplCanTimerStart(kCanLoopClearFreeze);
      do /* wait until FlexCAN A is not in FREEZE mode */
      {
        loopResult = CanLL_ApplCanTimerLoop(kCanLoopClearFreeze);
      }while(((CAN_READ_PROTECTED_REG(pFlexCANA->canmcr) & kFlexCAN_FRZ_ACK) != (vuint16)0) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */
      CanLL_ApplCanTimerEnd(kCanLoopClearFreeze);
    }
    
    /* If FlexCAN A is being initialized, we need to restore the previous state of FlexCAN C
       rather than unconditionally unfreezing it. In any case FlexCAN C is always second. */
    if(pFlexCAN(canHwChannel) == ((tFlexcanPtr)0xFFFC0000))
    {
      if((canMcrReg & kFlexCAN_MDIS) != (vuint16)0)
      {     
        CAN_WRITE_PROTECTED_REG_SET(pFlexCANC->canmcr, kFlexCAN_MDIS); /* disable FlexCAN C */
      }
      else
      {
        if((canMcrReg & kFlexCAN_HALT) == (vuint16)0)
        {     
          CAN_WRITE_PROTECTED_REG_RESET(pFlexCANC->canmcr, kFlexCAN_HALT);   /* clear HALT bit */
        }
        if((canMcrReg & kFlexCAN_FRZ) == (vuint16)0)
        {
          CAN_WRITE_PROTECTED_REG_RESET(pFlexCANC->canmcr, kFlexCAN_FRZ); /* clear FRZ bit */
        }
        
        /* If both HALT and FRZ bits were cleared, wait for freeze mode to exit to avoid
           corruption in FlexCAN C */
        if(((canMcrReg & kFlexCAN_HALT) == (vuint16)0) &&
          ((canMcrReg & kFlexCAN_FRZ) == (vuint16)0))
        {
          CanLL_ApplCanTimerStart(kCanLoopClearFreeze);
          do /* wait until FlexCAN C is not in FREEZE mode */
          {
            loopResult = CanLL_ApplCanTimerLoop(kCanLoopClearFreeze);
          }while(((CAN_READ_PROTECTED_REG(pFlexCANC->canmcr) & kFlexCAN_FRZ_ACK) != (vuint16)0) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */
          CanLL_ApplCanTimerEnd(kCanLoopClearFreeze);
        }
      }
    }
    /* FlexCAN C was being initialized and initialization is complete - unfreeze it now.
       FlexCAN C must be unfrozen after FlexCAN A to avoid corruption in FlexCAN C. */
    else
    {
      CAN_WRITE_PROTECTED_REG_RESET(pFlexCANC->canmcr, kFlexCAN_HALT);   /* clear HALT bit */
      CAN_WRITE_PROTECTED_REG_RESET(pFlexCANC->canmcr, kFlexCAN_FRZ); /* clear FRZ bit */
      
      CanLL_ApplCanTimerStart(kCanLoopClearFreeze);
      do /* wait until FlexCAN C is not in FREEZE mode */
      {
        loopResult = CanLL_ApplCanTimerLoop(kCanLoopClearFreeze);
      }while(((CAN_READ_PROTECTED_REG(pFlexCANC->canmcr) & kFlexCAN_FRZ_ACK) != (vuint16)0) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */
      CanLL_ApplCanTimerEnd(kCanLoopClearFreeze);
    }
  } 
  
  CanMicroModeRestore(); 
}
/* CODE CATEGORY 2 END*/
# endif /* C_ENABLE_WORKAROUND_ERRATA_5164 */
#endif /* C_ENABLE_INDIVIDUAL_BUFFER_MASKING */






#if defined( C_ENABLE_SLEEP_WAKEUP ) && defined( C_ENABLE_FLEXCAN_DOZE_MODE )
/****************************************************************************
| NAME:             CanLL_WakeUpHandling
| CALLED BY:        CanWakeUpTask() and WakeUp-ISR
| PRECONDITIONS:    none
|
| INPUT PARAMETERS: CanChannelHandle  channel        | current CAN channel
|                   and parameters which are defined in CanLL_WakeUpTaskLocalParameter
|
| RETURN VALUES:    -
|
| DESCRIPTION:      perform wakeup handling.
|
| ATTENTION:        CanLL_WakeUpHandling has to contain:
|                     ApplCanPreWakeUp(CAN_CHANNEL_CANPARA_ONLY);
|                     CanWakeUp(CAN_CHANNEL_CANPARA_ONLY);        - if hardware does not wake up automatically
|                     APPL_CAN_WAKEUP( channel );
|                   In case of CommonCAN, it might be necessary to call CanWakeUp even if the hardware
|                   wakes up automatically to make sure all associated HW channels are awaken.
****************************************************************************/
/* CODE CATEGORY 4 START*/
V_DEF_FUNC_API(CAN_STATIC, void, STATIC_CODE) CanLL_WakeUpHandling(CAN_HW_CHANNEL_CANTYPE_ONLY)
{
  tFlexcanPtr pFlexCANLocal = pFlexCAN(canHwChannel);
    
    
  #if defined( C_ENABLE_APPLCANPREWAKEUP_FCT )
  ApplCanPreWakeUp( CAN_CHANNEL_CANPARA_ONLY );
  #endif

  CanMicroModeSystem();

  # if defined( C_ENABLE_FLEXCAN_DOZE_MODE )
  /* FlexCAN automatically wakes up from DOZE mode by external bus activity */
  CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_DOZE); /* clear the DOZE bit */
  # endif
  
  pFlexCANLocal->estat = kFlexCAN_WAKE_INT; /* clear pending wakeup interrupt flag */ 
    
  CanMicroModeRestore();


  #if defined( C_ENABLE_APPLCANWAKEUP_FCT )
  APPL_CAN_WAKEUP( CAN_CHANNEL_CANPARA_ONLY );
  #endif
}
/* CODE CATEGORY 4 END*/
#endif /*C_ENABLE_SLEEP_WAKEUP*/

#if defined( C_ENABLE_CAN_RAM_CHECK )
/****************************************************************************
| NAME:             CanLL_IsMailboxCorrupt
| CALLED BY:        CanCheckMemory()
| PRECONDITIONS:    none
|
| INPUT PARAMETERS: CanChannelHandle  channel        | current CAN channel
|                   CanObjectHandle   hwObjHandle    | Handle to hardware object
|
| RETURN VALUES:    kCanTrue:  Mailbox is corrupt
|                   kCanFalse: Mailbox is not corrupt  
|
| DESCRIPTION:      check the current mailbox at index hwObjHandle
****************************************************************************/
/* CODE CATEGORY 4 START */
V_DEF_FUNC_API(CAN_STATIC, vuint8, STATIC_CODE) CanLL_IsMailboxCorrupt(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle hwObjHandle)
{
  tFLEXCANPtr pFlexCANLocal;
  vuint8    result;
  
  pFlexCANLocal = pFLEXCAN(canHwChannel);
  result = kCanFalse;

  {
    /* DLC and IDE register check **********************************************************/
    pFlexCANLocal->canObject[hwObjHandle].control = (vuint16)0x0055;  
    if((pFlexCANLocal->canObject[hwObjHandle].control & (vuint16)0x007F) != (vuint16)0x0055)
    { result = kCanTrue; }        
    pFlexCANLocal->canObject[hwObjHandle].control = (vuint16)0x002A;
    if((pFlexCANLocal->canObject[hwObjHandle].control & (vuint16)0x007F) != (vuint16)0x002A)
    { result = kCanTrue; }      
    pFlexCANLocal->canObject[hwObjHandle].control = (vuint16)0x0000;
    if((pFlexCANLocal->canObject[hwObjHandle].control & (vuint16)0x007F) != (vuint16)0x0000)
    { result = kCanTrue; }   

    /* ID register check *******************************************************************/  
    pFlexCANLocal->canObject[hwObjHandle].msgID = (vuint32)0xAAAAAAAAUL;
    if((pFlexCANLocal->canObject[hwObjHandle].msgID != (vuint32)0xAAAAAAAAUL))
    { result = kCanTrue; }  
    pFlexCANLocal->canObject[hwObjHandle].msgID = (vuint32)0x55555555UL;
    if((pFlexCANLocal->canObject[hwObjHandle].msgID != (vuint32)0x55555555UL))
    { result = kCanTrue; }
    pFlexCANLocal->canObject[hwObjHandle].msgID = (vuint32)0x00000000UL;
    if((pFlexCANLocal->canObject[hwObjHandle].msgID != (vuint32)0x00000000UL))
    { result = kCanTrue; }
          
    /* Data register check *****************************************************************/    
    pFlexCANLocal->canObject[hwObjHandle].data[0] = (vuint32)0xAAAAAAAAUL;
    if(pFlexCANLocal->canObject[hwObjHandle].data[0] != (vuint32)0xAAAAAAAAUL)
    { result = kCanTrue; }
    pFlexCANLocal->canObject[hwObjHandle].data[1] = (vuint32)0xAAAAAAAAUL;
    if(pFlexCANLocal->canObject[hwObjHandle].data[1] != (vuint32)0xAAAAAAAAUL)
    { result = kCanTrue; }
    pFlexCANLocal->canObject[hwObjHandle].data[0] = (vuint32)0x55555555UL;
    if(pFlexCANLocal->canObject[hwObjHandle].data[0] != (vuint32)0x55555555UL)
    { result = kCanTrue; }
    pFlexCANLocal->canObject[hwObjHandle].data[1] = (vuint32)0x55555555UL;
    if(pFlexCANLocal->canObject[hwObjHandle].data[1] != (vuint32)0x55555555UL)
    { result = kCanTrue; }
    pFlexCANLocal->canObject[hwObjHandle].data[0] = (vuint32)0x00000000UL;
    if(pFlexCANLocal->canObject[hwObjHandle].data[0] != (vuint32)0x00000000UL)
    { result = kCanTrue; }
    pFlexCANLocal->canObject[hwObjHandle].data[1] = (vuint32)0x00000000UL;
    if(pFlexCANLocal->canObject[hwObjHandle].data[1] != (vuint32)0x00000000UL)
    { result = kCanTrue; }
    
  }

  return result;
}
/* CODE CATEGORY 4 END */
#endif



#if defined( C_ENABLE_SINGLE_ISR_API )
# if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
     defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
     defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/****************************************************************************
| NAME:             CanInterrupt
| CALLED BY:        application
| PRECONDITIONS:    CanInterrupt() must be called
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Services all pending CAN interrupts (Rx, Tx, Error, Wake)
****************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanInterrupt( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
  #if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
  vuint16  index;
  vuint32  iFlags;
  vuint32  iMaskLo;  
  # if defined( C_ENABLE_MAX_BUFFER_64 )
  vuint32  iMaskHi = 0;
  # endif  
  #endif
  
  #if defined( C_ENABLE_CAN_RXTX_INTERRUPT ) || defined( C_ENABLE_CAN_WAKEUP_INTERRUPT ) ||  defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
  tFlexcanPtr pFlexCANLocal = pFlexCAN(canHwChannel);
  #endif
  
  #if defined( C_ENABLE_CAN_RXTX_INTERRUPT )
  # if defined( C_ENABLE_FLEXCAN_RXFIFO )      
  iMaskLo = pFlexCANLocal->imask_lo & (vuint32)0xFFFFFF00;
  # else
  iMaskLo = pFlexCANLocal->imask_lo;
  # endif  
  # if defined( C_ENABLE_MAX_BUFFER_64 )  
  #  if defined( C_CAN_MAX_BUFFER_MIXED )
  if (CanMaxMB[canHwChannel] == 64)
  #  endif
  {
    iMaskHi = pFlexCANLocal->imask_hi;  
  }
  # endif
  #endif
         
  CanFlexCanInterruptDisable( CAN_CHANNEL_CANPARA_ONLY );
    
  #if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
  if((pFlexCANLocal->estat & kFlexCAN_WAKE_INT) != 0)
  {
    CanLL_WakeUpHandling(CAN_HW_CHANNEL_CANPARA_ONLY);
  }
  #endif
  
  #if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
  {
    if((pFlexCANLocal->estat & kFlexCAN_BOFF_INT) != 0)
    {
      CanHL_ErrorHandling( CAN_HW_CHANNEL_CANPARA_ONLY ); /* SBSW_CAN_LL007 */
    }
  }
  #endif        
  
  #if defined( C_ENABLE_CAN_RXTX_INTERRUPT )    

  # if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
  #  if !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )  
  #   if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
  #    if defined( C_ENABLE_FLEXCAN_RXFIFO )
  index = 0;
  do{
      if((pFlexCANLocal->iflag_lo & kRxFIFO_NEWMSG) != 0)
      {
        CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST 0);
      }
      index++;
  }while(index < (vuint16)(C_FLEXCAN_RXFIFO_MAXLOOP));
  #    else
  iFlags = pFlexCANLocal->iflag_lo & CAN_RXBASIC_INT_MASK_LO(canHwChannel);
  if(iFlags != 0)
  {         
    index = CAN_HW_RX_BASIC_STARTINDEX(canHwChannel);
    #if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
    iFlags >>= index;
    #endif
                
    while(iFlags != 0)
    {
      while((iFlags & (vuint32)0x01) == 0)
      {
        iFlags >>= 1;
        index++;
      }
      CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST index); /* SBSW_CAN_LL008 */
      index++;
      iFlags = (pFlexCANLocal->iflag_lo & CAN_RXBASIC_INT_MASK_LO(canHwChannel)) >> index;
    }   
  } 
    
  #     if defined( C_ENABLE_MAX_BUFFER_64 )
  #      if defined( C_CAN_MAX_BUFFER_MIXED )
  if (CanMaxMB[canHwChannel] == 64)
  #      endif
  {
    iFlags = pFlexCANLocal->iflag_hi & CAN_RXBASIC_INT_MASK_HI(canHwChannel);
    if(iFlags != 0)
    {    
      index = CAN_HW_RX_BASIC_STARTINDEX(canHwChannel);
      if(index > 32)
      {
        iFlags >>= (index-32);
      }
      else
      {
        index = (vuint16)32;
      }
      while(iFlags != 0)
      {
        while((iFlags & (vuint32)0x01) == 0)
        {
          iFlags >>= 1;
          index++;
        }
        CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST index);
        index++;
        iFlags = (pFlexCANLocal->iflag_hi & CAN_RXBASIC_INT_MASK_HI(canHwChannel)) >> (index-32);
      }    
    }
  }
  #     endif  /* C_ENABLE_MAX_BUFFER_64 */
  #    endif  /* C_ENABLE_FLEXCAN_RXFIFO */
  #    endif /* C_ENABLE_INDIVIDUAL_BUFFER_MASKING */
  #  endif
  # endif  /* C_ENABLE_RX_BASICCAN_OBJECTS */
  

  # if !defined( C_ENABLE_TX_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )  
  #  if defined( C_CAN_MAX_BUFFER_32 ) || defined( C_CAN_MAX_BUFFER_MIXED )
  #   if defined( C_CAN_MAX_BUFFER_MIXED )
  if(CAN_HW_TX_STOPINDEX(canHwChannel) == 32)
  #   endif
  {
    {
      iFlags = pFlexCANLocal->iflag_lo & CAN_TX_INT_MASK_LO(canHwChannel);
      #if defined( C_ENABLE_MSG_TRANSMIT )  
      if((iFlags & CanBitMask(30)) != 0)
      {
        CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST 30);      
        iFlags = pFlexCANLocal->iflag_lo & CAN_TX_INT_MASK_LO(canHwChannel);
      }
      #endif  
      if((iFlags & CanBitMask(31)) != 0)
      {
        CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST 31); /* SBSW_CAN_LL009 */
      }
    }
  }
  #  endif /* C_CAN_MAX_BUFFER_32 || C_CAN_MAX_BUFFER_MIXED */
  
  #  if defined( C_ENABLE_MAX_BUFFER_64 )
  #   if defined( C_CAN_MAX_BUFFER_MIXED )
  if(CAN_HW_TX_STOPINDEX(canHwChannel) == 64)
  #   endif
  {
    {
      iFlags = pFlexCANLocal->iflag_hi & CAN_TX_INT_MASK_HI(canHwChannel);
      #if defined( C_ENABLE_MSG_TRANSMIT )  
      if((iFlags & CanBitMask(62)) != 0)
      {
        CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST 62);      
        iFlags = pFlexCANLocal->iflag_hi & CAN_TX_INT_MASK_HI(canHwChannel);
      }
      #endif  
      if((iFlags & CanBitMask(63)) != 0)
      {
        CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST 63);
      } 
    }
  }
  #  endif  /* C_ENABLE_MAX_BUFFER_64 */    
  # endif  /* C_ENABLE_TX_POLLING || C_ENABLE_INDIVIDUAL_POLLING */

  iFlags = pFlexCANLocal->iflag_lo & iMaskLo;
  index = 0;
  while(iFlags != 0)
  {
    while((iFlags & (vuint32)0xFF) == 0)
    {
      iFlags >>= 8;
      index += (vuint16)8;    
    }    
    if((iFlags & (vuint32)0x0F) == 0)
    {
      iFlags >>= 4;
      index += (vuint16)4;
    }        
    while((iFlags & (vuint32)0x01) == 0)
    {
      iFlags >>= 1;
      index++;
    }
    
    #if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
    # if !defined( C_ENABLE_RX_FULLCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
    if((CAN_RXFULL_INT_MASK_LO(canHwChannel) & CanBitMask(index)) != 0)
    {    
      CanFullCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST index); /* SBSW_CAN_LL008 */
    }    
    # endif
    #endif

    #if !defined( C_ENABLE_TX_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
    if((CAN_TX_INT_MASK_LO(canHwChannel) & CanBitMask(index)) != 0)
    {
      CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST index); /* SBSW_CAN_LL008 */
    }    
    #endif

    index++;
    iFlags = (pFlexCANLocal->iflag_lo & iMaskLo) >> index;    
  }
  
  # if defined( C_ENABLE_MAX_BUFFER_64 ) 
  #  if defined( C_CAN_MAX_BUFFER_MIXED )
  if (CanMaxMB[canHwChannel] == 64)
  #  endif
  {
    iFlags = pFlexCANLocal->iflag_hi & iMaskHi;
    index = 0;  
    while(iFlags != 0)
    {
      while((iFlags & (vuint32)0xFF) == 0)
      {
        iFlags >>= 8;
        index += (vuint16)8;    
      }
      if((iFlags & (vuint32)0x0F) == 0)
      {
        iFlags >>= 4;
        index += (vuint16)4;    
      }
      while((iFlags & (vuint32)0x01) == 0)
      {
        iFlags >>= 1;
        index++;
      }
            
      #if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
      # if !defined( C_ENABLE_RX_FULLCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
      if((CAN_RXFULL_INT_MASK_HI(canHwChannel) & CanBitMask(index)) != 0)
      {    
        CanFullCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST (index+32));      
      }    
      # endif
      #endif
     
      #if !defined( C_ENABLE_TX_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
      if((CAN_TX_INT_MASK_HI(canHwChannel) & CanBitMask(index)) != 0)
      {
        CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST (index+32));
      }    
      #endif    
      
      index++;
      iFlags = (pFlexCANLocal->iflag_hi & iMaskHi) >> index;    
    }
  }
  # endif /* C_ENABLE_MAX_BUFFER_64 */   
  
  #endif /* C_ENABLE_CAN_RXTX_INTERRUPT */
  
  CanFlexCanInterruptRestore( CAN_CHANNEL_CANPARA_ONLY );
} /* end of CanInterrupt */
/* CODE CATEGORY 1 END */
# endif

#else /* C_ENABLE_SINGLE_ISR_API */


#  if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/****************************************************************************
| NAME:             CanBusOffInterrupt
| CALLED BY:        application
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt routine for bus off interrupts
****************************************************************************/
/* CODE CATEGORY 1 START*/
V_DEF_FUNC_API(V_NONE, void, CODE) CanBusOffInterrupt( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
  CanFlexCanInterruptDisable( CAN_CHANNEL_CANPARA_ONLY );
  CanHL_ErrorHandling( CAN_HW_CHANNEL_CANPARA_ONLY ); /* SBSW_CAN_LL007 */
  CanFlexCanInterruptRestore( CAN_CHANNEL_CANPARA_ONLY );  
} /* end of CanBusOffInterrupt */
/* CODE CATEGORY 1 END*/
#  endif

#  if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/****************************************************************************
| NAME:             CanWakeUpInterrupt
| CALLED BY:        application
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt routine for wakeup interrupts
****************************************************************************/
/* CODE CATEGORY 1 START*/
V_DEF_FUNC_API(V_NONE, void, CODE) CanWakeUpInterrupt( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
  CanFlexCanInterruptDisable( CAN_HW_CHANNEL_CANPARA_ONLY );  
  CanLL_WakeUpHandling( CAN_HW_CHANNEL_CANPARA_ONLY );
  CanFlexCanInterruptRestore(CAN_HW_CHANNEL_CANPARA_ONLY );  
} /* end of CanWakeUpInterrupt */
/* CODE CATEGORY 1 END*/
#  endif

#  if defined( C_ENABLE_CAN_RXTX_INTERRUPT )


/****************************************************************************
| NAME:             CanMB0To31Interrupt
| CALLED BY:        CanMB0to15Isr , CanMB16to31Isr
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 0 ... 31
****************************************************************************/
/* CODE CATEGORY 1 START */
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB0To31Interrupt( CAN_HW_CHANNEL_CANTYPE_ONLY )
{

  #if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) || defined( C_ENABLE_TX_FULLCAN_OBJECTS ) || \
  ( defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && ( !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING ) ) )
  vuint16  index;
  #endif
  
  #if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) || defined( C_ENABLE_TX_FULLCAN_OBJECTS ) || \
  ( ( !defined( C_ENABLE_TX_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING ) ) && ( defined( C_CAN_MAX_BUFFER_32 ) || defined( C_CAN_MAX_BUFFER_MIXED ) ) ) || \
  ( defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && ( !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING ) ) && !defined( C_ENABLE_FLEXCAN_RXFIFO ) )
  vuint32  iFlags;
  tFlexcanPtr pFlexCANLocal = pFlexCAN(canHwChannel);
  #endif   
  
  #if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) || defined( C_ENABLE_TX_FULLCAN_OBJECTS )
  vuint32 iMask;
  # if defined( C_ENABLE_FLEXCAN_RXFIFO )
  iMask = pFlexCANLocal->imask_lo & (vuint32)0xFFFFFF00;  
  # else
  iMask = pFlexCANLocal->imask_lo;    
  # endif
  #endif
  
  CanFlexCanInterruptDisable( CAN_CHANNEL_CANPARA_ONLY );      
  
  #if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
  # if !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
  #  if defined( C_ENABLE_FLEXCAN_RXFIFO )
  index = 0;
  do{
      if((pFlexCANLocal->iflag_lo & kRxFIFO_NEWMSG) != 0)
      {
        CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST 0);
      }
      index++;
  }while(index < (vuint16)(C_FLEXCAN_RXFIFO_MAXLOOP));
  #  else
  iFlags = pFlexCANLocal->iflag_lo & CAN_RXBASIC_INT_MASK_LO(canHwChannel);
  if(iFlags != 0)
  {         
    index = CAN_HW_RX_BASIC_STARTINDEX(canHwChannel);
    #if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
    iFlags >>= index;
    #endif
            
    while(iFlags != 0)
    {
      while((iFlags & (vuint32)0x01) == 0)
      {
        iFlags >>= 1;
        index++;
      }
      CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST index); /* SBSW_CAN_LL008 */
      index++;    
      iFlags = (pFlexCANLocal->iflag_lo & CAN_RXBASIC_INT_MASK_LO(canHwChannel)) >> index;
    }    
  } 
  #  endif /* C_ENABLE_FLEXCAN_RXFIFO */
  # endif /* !C_ENABLE_RX_BASICCAN_POLLING || C_ENABLE_INDIVIDUAL_POLLING */
  #endif /* C_ENABLE_RX_BASICCAN_OBJECTS */
    
  #if !defined( C_ENABLE_TX_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )   
  # if defined( C_CAN_MAX_BUFFER_32 ) || defined( C_CAN_MAX_BUFFER_MIXED )
  #  if defined( C_CAN_MAX_BUFFER_MIXED ) 
  if(CAN_HW_TX_STOPINDEX(canHwChannel) == 32)
  #  endif
  {
    #if defined( C_ENABLE_INDIVIDUAL_POLLING )  
    if(CAN_TX_INT_MASK_LO(canHwChannel) != 0)
    #endif
    {
      iFlags = pFlexCANLocal->iflag_lo & CAN_TX_INT_MASK_LO(canHwChannel);
      #if defined( C_ENABLE_MSG_TRANSMIT ) 
      if((iFlags & CanBitMask(30)) != 0)
      {
        CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST 30);    
        iFlags = pFlexCANLocal->iflag_lo & CAN_TX_INT_MASK_LO(canHwChannel);
      }    
      #endif
      if((iFlags & CanBitMask(31)) != 0)
      {
        CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST 31); /* SBSW_CAN_LL009 */
      }  
    }
  }
  # endif
  #endif
  
  #if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) || defined( C_ENABLE_TX_FULLCAN_OBJECTS )
  iFlags = pFlexCANLocal->iflag_lo & iMask;  
  index = 0;  
  while(iFlags != 0)
  {
    while((iFlags & (vuint32)0x000F) == 0)
    {
      iFlags >>= 4;
      index += (vuint16)4;
    }            
    while((iFlags & (vuint32)0x0001) == 0)
    {
      iFlags >>= 1;
      index++;
    }
    
    #if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
    # if !defined( C_ENABLE_RX_FULLCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
    if((CAN_RXFULL_INT_MASK_LO(canHwChannel) & CanBitMask(index)) != 0)
    {    
      CanFullCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST index); /* SBSW_CAN_LL008 */
    }    
    # endif
    #endif    
    
    #if !defined( C_ENABLE_TX_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
    if((CAN_TX_INT_MASK_LO(canHwChannel) & CanBitMask(index)) != 0)
    {
      CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST index); /* SBSW_CAN_LL008 */
    }    
    #endif
    
    index++;
    iFlags = (pFlexCANLocal->iflag_lo & iMask) >> index;
  }
  #endif
    
  CanFlexCanInterruptRestore( CAN_CHANNEL_CANPARA_ONLY );     
} /* end of CanMB0To31Interrupt */
/* CODE CATEGORY 1 END */

#   if defined( C_ENABLE_MAX_BUFFER_64 )
/****************************************************************************
| NAME:             CanMB32To63Interrupt
| CALLED BY:        CanMB32To63Isr
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 32 ... 63
****************************************************************************/
/* CODE CATEGORY 1 START*/
V_DEF_FUNC_API(V_NONE, void, CODE) CanMB32To63Interrupt( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
  tFlexcanPtr  pFlexCANLocal = pFlexCAN(canHwChannel);

  #if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) || defined( C_ENABLE_TX_FULLCAN_OBJECTS ) || \
  ( ( defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && !defined( C_ENABLE_FLEXCAN_RXFIFO ) ) && ( !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING ) ) )
  vuint16  index;
  #endif
  vuint32  iFlags;
  
  #if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) || defined( C_ENABLE_TX_FULLCAN_OBJECTS )
  vuint32  iMask;
  iMask = pFlexCANLocal->imask_hi;
  #endif
  
  CanFlexCanInterruptDisable( CAN_CHANNEL_CANPARA_ONLY );      
    
  #if defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && !defined( C_ENABLE_FLEXCAN_RXFIFO )
  # if !defined( C_ENABLE_RX_BASICCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
  iFlags = pFlexCANLocal->iflag_hi & CAN_RXBASIC_INT_MASK_HI(canHwChannel);
  if(iFlags != 0)
  {    
    index = CAN_HW_RX_BASIC_STARTINDEX(canHwChannel);
    if(index > 32)
    {
      iFlags >>= (index-32);
    }
    else
    {
      index = (vuint16)32;
    }
    while(iFlags != 0)
    {
      while((iFlags & (vuint32)0x01) == 0)
      {
        iFlags >>= 1;
        index++;
      }
      CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST index);
      index++;
      iFlags = (pFlexCANLocal->iflag_hi & CAN_RXBASIC_INT_MASK_HI(canHwChannel)) >> (index-32);
    }
  }  
  # endif
  #endif

  #if !defined( C_ENABLE_TX_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
  # if defined( C_ENABLE_INDIVIDUAL_POLLING )
  if(CAN_TX_INT_MASK_HI(canHwChannel) != 0)
  # endif
  {  
    iFlags = pFlexCANLocal->iflag_hi & CAN_TX_INT_MASK_HI(canHwChannel);
    #if defined( C_ENABLE_MSG_TRANSMIT )
    if((iFlags & CanBitMask(62)) != 0)
    {
      CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST 62);      
      iFlags = pFlexCANLocal->iflag_hi & CAN_TX_INT_MASK_HI(canHwChannel);    
    }
    #endif  
    if((iFlags & CanBitMask(63)) != 0)
    {
      CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST 63);      
    }
  }
  #endif  
    
  #if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) || defined( C_ENABLE_TX_FULLCAN_OBJECTS )
  iFlags = pFlexCANLocal->iflag_hi & iMask;
  index = 0;    
  while(iFlags != 0)
  {
    while((iFlags & (vuint32)0x000F) == 0)
    {
      iFlags >>= 4;
      index += (vuint16)4;
    }    
    while((iFlags & (vuint32)0x0001) == 0)
    {
      iFlags >>= 1;
      index++;
    }
    
    #if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
    # if !defined( C_ENABLE_RX_FULLCAN_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
    if((CAN_RXFULL_INT_MASK_HI(canHwChannel) & CanBitMask(index)) != 0)
    {    
      CanFullCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST (index+32));
    }    
    # endif
    #endif    
    
    #if !defined( C_ENABLE_TX_POLLING ) || defined( C_ENABLE_INDIVIDUAL_POLLING )
    if((CAN_TX_INT_MASK_HI(canHwChannel) & CanBitMask(index)) != 0)
    {
      CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST (index+32));
    }    
    #endif
    
    index++;          
    iFlags = (pFlexCANLocal->iflag_hi & iMask) >> index;    
  }
  #endif
    
  CanFlexCanInterruptRestore( CAN_CHANNEL_CANPARA_ONLY );
} /* end of CanMB32To63Interrupt */
/* CODE CATEGORY 1 END */
#    endif /* C_ENABLE_MAX_BUFFER_64 */
#  endif /* C_ENABLE_CAN_RXTX_INTERRUPT */
#endif /* C_ENABLE_SINGLE_ISR_API */

#if defined( C_SINGLE_RECEIVE_CHANNEL )
# define CanPhysToLogChannel_0
# define CanPhysToLogChannelIndex_0
# define CanPhysToLogChannel_1
# define CanPhysToLogChannelIndex_1
# define CanPhysToLogChannel_2
# define CanPhysToLogChannelIndex_2
# define CanPhysToLogChannel_3
# define CanPhysToLogChannelIndex_3
# define CanPhysToLogChannel_4
# define CanPhysToLogChannelIndex_4
# define CanPhysToLogChannel_5
# define CanPhysToLogChannelIndex_5
# define CanPhysToLogChannel_6
# define CanPhysToLogChannelIndex_6
# define CanPhysToLogChannel_7
# define CanPhysToLogChannelIndex_7
#else
# define CanPhysToLogChannel_0       kCanPhysToLogChannelIndex_0
# define CanPhysToLogChannelIndex_0  kCanPhysToLogChannelIndex_0,
# define CanPhysToLogChannel_1       kCanPhysToLogChannelIndex_1
# define CanPhysToLogChannelIndex_1  kCanPhysToLogChannelIndex_1,
# define CanPhysToLogChannel_2       kCanPhysToLogChannelIndex_2
# define CanPhysToLogChannelIndex_2  kCanPhysToLogChannelIndex_2,
# define CanPhysToLogChannel_3       kCanPhysToLogChannelIndex_3
# define CanPhysToLogChannelIndex_3  kCanPhysToLogChannelIndex_3,
# define CanPhysToLogChannel_4       kCanPhysToLogChannelIndex_4
# define CanPhysToLogChannelIndex_4  kCanPhysToLogChannelIndex_4,
# define CanPhysToLogChannel_5       kCanPhysToLogChannelIndex_5
# define CanPhysToLogChannelIndex_5  kCanPhysToLogChannelIndex_5,
# define CanPhysToLogChannel_6       kCanPhysToLogChannelIndex_6
# define CanPhysToLogChannelIndex_6  kCanPhysToLogChannelIndex_6,
# define CanPhysToLogChannel_7       kCanPhysToLogChannelIndex_7
# define CanPhysToLogChannelIndex_7  kCanPhysToLogChannelIndex_7,
#endif

#if defined( C_ENABLE_SINGLE_ISR_API )

# if defined( C_ENABLE_CAN_RXTX_INTERRUPT )   || \
     defined( C_ENABLE_CAN_BUSOFF_INTERRUPT ) || \
     defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
#  if defined( kCanPhysToLogChannelIndex_0 )
/****************************************************************************
| NAME:             CanIsr_0
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for Rx,Tx, BusOff and Wakeup
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_0Cat)
#    if (osdIsrCanIsr_0Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsr_0 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_0Cat)
#    if (osdIsrCanIsr_0Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_0( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanInterrupt(CanPhysToLogChannel_0); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanISR */
/* CODE CATEGORY 1 END */
#  endif /* (kCanPhysToLogChannelIndex_0) */
#  if defined( kCanPhysToLogChannelIndex_1 )
/****************************************************************************
| NAME:             CanIsr_1
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for Rx,Tx, BusOff and Wakeup
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_1Cat)
#    if (osdIsrCanIsr_1Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsr_1 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_1Cat)
#    if (osdIsrCanIsr_1Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_1( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanInterrupt(CanPhysToLogChannel_1); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanISR */
/* CODE CATEGORY 1 END */
#  endif /* (kCanPhysToLogChannelIndex_1) */
#  if defined( kCanPhysToLogChannelIndex_2 )
/****************************************************************************
| NAME:             CanIsr_2
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for Rx,Tx, BusOff and Wakeup
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_2Cat)
#    if (osdIsrCanIsr_2Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsr_2 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_2Cat)
#    if (osdIsrCanIsr_2Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_2( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanInterrupt(CanPhysToLogChannel_2); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanISR */
/* CODE CATEGORY 1 END */
#  endif /* (kCanPhysToLogChannelIndex_2) */
#  if defined( kCanPhysToLogChannelIndex_3 )
/****************************************************************************
| NAME:             CanIsr_3
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for Rx,Tx, BusOff and Wakeup
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_3Cat)
#    if (osdIsrCanIsr_3Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsr_3 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_3Cat)
#    if (osdIsrCanIsr_3Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_3( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanInterrupt(CanPhysToLogChannel_3); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanISR */
/* CODE CATEGORY 1 END */
#  endif /* (kCanPhysToLogChannelIndex_3) */
#  if defined( kCanPhysToLogChannelIndex_4 )
/****************************************************************************
| NAME:             CanIsr_4
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for Rx,Tx, BusOff and Wakeup
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_4Cat)
#    if (osdIsrCanIsr_4Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsr_4 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_4Cat)
#    if (osdIsrCanIsr_4Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_4( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanInterrupt(CanPhysToLogChannel_4); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanISR */
/* CODE CATEGORY 1 END */
#  endif /* (kCanPhysToLogChannelIndex_4) */
#  if defined( kCanPhysToLogChannelIndex_5 )
/****************************************************************************
| NAME:             CanIsr_5
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for Rx,Tx, BusOff and Wakeup
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_5Cat)
#    if (osdIsrCanIsr_5Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsr_5 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_5Cat)
#    if (osdIsrCanIsr_5Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_5( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanInterrupt(CanPhysToLogChannel_5); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanISR */
/* CODE CATEGORY 1 END */
#  endif /* (kCanPhysToLogChannelIndex_5) */
#  if defined( kCanPhysToLogChannelIndex_6 )
/****************************************************************************
| NAME:             CanIsr_6
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for Rx,Tx, BusOff and Wakeup
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_6Cat)
#    if (osdIsrCanIsr_6Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsr_6 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_6Cat)
#    if (osdIsrCanIsr_6Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_6( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanInterrupt(CanPhysToLogChannel_6); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanISR */
/* CODE CATEGORY 1 END */
#  endif /* (kCanPhysToLogChannelIndex_6) */
#  if defined( kCanPhysToLogChannelIndex_7 )
/****************************************************************************
| NAME:             CanIsr_7
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for Rx,Tx, BusOff and Wakeup
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_7Cat)
#    if (osdIsrCanIsr_7Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsr_7 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_7Cat)
#    if (osdIsrCanIsr_7Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_7( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanInterrupt(CanPhysToLogChannel_7); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanISR */
/* CODE CATEGORY 1 END */
#  endif /* (kCanPhysToLogChannelIndex_7) */
# endif /* C_ENABLE_CAN_RXTX_INTERRUPT || C_ENABLE_CAN_BUSOFF_INTERRUPT || C_ENABLE_CAN_WAKEUP_INTERRUPT */

#else /* C_ENABLE_SINGLE_ISR_API */


# if defined( C_FLEXCAN_ISR_GROUP_B )

#  if defined( kCanPhysToLogChannelIndex_0 )
#   if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/****************************************************************************
| NAME:             CanBusOffIsr_0
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for BusOff
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_0Cat)
#    if (osdIsrCanIsr_0Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanBusOffIsr_0 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_0Cat)
#    if (osdIsrCanIsr_0Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanBusOffIsr_0( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanBusOffInterrupt(CanPhysToLogChannel_0); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanBusOffIsr_0 */
/* CODE CATEGORY 1 END */
#   endif /* C_ENABLE_CAN_BUSOFF_INTERRUPT */

#   if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/****************************************************************************
| NAME:             CanWakeupIsr_0
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for Wakeup
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_0Cat)
#    if (osdIsrCanIsr_0Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanWakeUpIsr_0 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_0Cat)
#    if (osdIsrCanIsr_0Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanWakeUpIsr_0( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanWakeUpInterrupt(CanPhysToLogChannel_0); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanWakeUpIsr_0 */
/* CODE CATEGORY 1 END */      
#   endif /* C_ENABLE_CAN_WAKEUP_INTERRUPT */

#   if defined( C_ENABLE_CAN_RXTX_INTERRUPT )

/****************************************************************************
| NAME:             CanMB0To15Isr_0
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 0 ... 15
****************************************************************************/      
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_0Cat)
#    if (osdIsrCanIsr_0Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB0To15Isr_0 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_0Cat)
#    if (osdIsrCanIsr_0Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB0To15Isr_0( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB0To31Interrupt(CanPhysToLogChannel_0); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanMB0To15Isr_0 */
/* CODE CATEGORY 1 END */      

/****************************************************************************
| NAME:             CanMB16To31Isr_0
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 16 ... 31
****************************************************************************/      
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_0Cat)
#    if (osdIsrCanIsr_0Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB16To31Isr_0 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_0Cat)
#    if (osdIsrCanIsr_0Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB16To31Isr_0( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB0To31Interrupt(CanPhysToLogChannel_0); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanMB16To31Isr_0 */
/* CODE CATEGORY 1 END */

#    if defined( C_ENABLE_MAX_BUFFER_64 )
/****************************************************************************
| NAME:             CanMB32To63Isr_0
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 32 ... 63
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_0Cat)
#    if (osdIsrCanIsr_0Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB32To63Isr_0 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_0Cat)
#    if (osdIsrCanIsr_0Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB32To63Isr_0( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB32To63Interrupt(CanPhysToLogChannel_0); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanMB32To63Isr_0 */
/* CODE CATEGORY 1 END */
#    endif /* C_ENABLE_MAX_BUFFER_64 */
#   endif /* C_ENABLE_CAN_RXTX_INTERRUPT */
#  endif /* (kCanPhysToLogChannelIndex_0) */


#  if defined( kCanPhysToLogChannelIndex_1 )
#   if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/****************************************************************************
| NAME:             CanBusOffIsr_1
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for BusOff
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_1Cat)
#    if (osdIsrCanIsr_1Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanBusOffIsr_1 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_1Cat)
#    if (osdIsrCanIsr_1Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanBusOffIsr_1( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanBusOffInterrupt(CanPhysToLogChannel_1); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanBusOffIsr_1 */
/* CODE CATEGORY 1 END */
#   endif /* C_ENABLE_CAN_BUSOFF_INTERRUPT */

#   if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/****************************************************************************
| NAME:             CanWakeupIsr_1
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for Wakeup
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_1Cat)
#    if (osdIsrCanIsr_1Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanWakeUpIsr_1 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_1Cat)
#    if (osdIsrCanIsr_1Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanWakeUpIsr_1( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanWakeUpInterrupt(CanPhysToLogChannel_1); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanWakeUpIsr_1 */
/* CODE CATEGORY 1 END */      
#   endif /* C_ENABLE_CAN_WAKEUP_INTERRUPT */

#   if defined( C_ENABLE_CAN_RXTX_INTERRUPT )

/****************************************************************************
| NAME:             CanMB0To15Isr_1
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 0 ... 15
****************************************************************************/      
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_1Cat)
#    if (osdIsrCanIsr_1Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB0To15Isr_1 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_1Cat)
#    if (osdIsrCanIsr_1Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB0To15Isr_1( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB0To31Interrupt(CanPhysToLogChannel_1); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanMB0To15Isr_1 */
/* CODE CATEGORY 1 END */      

/****************************************************************************
| NAME:             CanMB16To31Isr_1
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 16 ... 31
****************************************************************************/      
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_1Cat)
#    if (osdIsrCanIsr_1Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB16To31Isr_1 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_1Cat)
#    if (osdIsrCanIsr_1Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB16To31Isr_1( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB0To31Interrupt(CanPhysToLogChannel_1); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanMB16To31Isr_1 */
/* CODE CATEGORY 1 END */

#    if defined( C_ENABLE_MAX_BUFFER_64 )
/****************************************************************************
| NAME:             CanMB32To63Isr_1
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 32 ... 63
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_1Cat)
#    if (osdIsrCanIsr_1Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB32To63Isr_1 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_1Cat)
#    if (osdIsrCanIsr_1Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB32To63Isr_1( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB32To63Interrupt(CanPhysToLogChannel_1); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanMB32To63Isr_1 */
/* CODE CATEGORY 1 END */
#    endif /* C_ENABLE_MAX_BUFFER_64 */
#   endif /* C_ENABLE_CAN_RXTX_INTERRUPT */
#  endif /* (kCanPhysToLogChannelIndex_1) */


#  if defined( kCanPhysToLogChannelIndex_2 )
#   if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/****************************************************************************
| NAME:             CanBusOffIsr_2
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for BusOff
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_2Cat)
#    if (osdIsrCanIsr_2Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanBusOffIsr_2 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_2Cat)
#    if (osdIsrCanIsr_2Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanBusOffIsr_2( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanBusOffInterrupt(CanPhysToLogChannel_2); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanBusOffIsr_2 */
/* CODE CATEGORY 1 END */
#   endif /* C_ENABLE_CAN_BUSOFF_INTERRUPT */

#   if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/****************************************************************************
| NAME:             CanWakeupIsr_2
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for Wakeup
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_2Cat)
#    if (osdIsrCanIsr_2Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanWakeUpIsr_2 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_2Cat)
#    if (osdIsrCanIsr_2Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanWakeUpIsr_2( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanWakeUpInterrupt(CanPhysToLogChannel_2); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanWakeUpIsr_2 */
/* CODE CATEGORY 1 END */      
#   endif /* C_ENABLE_CAN_WAKEUP_INTERRUPT */

#   if defined( C_ENABLE_CAN_RXTX_INTERRUPT )

/****************************************************************************
| NAME:             CanMB0To15Isr_2
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 0 ... 15
****************************************************************************/      
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_2Cat)
#    if (osdIsrCanIsr_2Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB0To15Isr_2 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_2Cat)
#    if (osdIsrCanIsr_2Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB0To15Isr_2( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB0To31Interrupt(CanPhysToLogChannel_2); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanMB0To15Isr_2 */
/* CODE CATEGORY 1 END */      

/****************************************************************************
| NAME:             CanMB16To31Isr_2
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 16 ... 31
****************************************************************************/      
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_2Cat)
#    if (osdIsrCanIsr_2Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB16To31Isr_2 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_2Cat)
#    if (osdIsrCanIsr_2Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB16To31Isr_2( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB0To31Interrupt(CanPhysToLogChannel_2); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanMB16To31Isr_2 */
/* CODE CATEGORY 1 END */

#    if defined( C_ENABLE_MAX_BUFFER_64 )
/****************************************************************************
| NAME:             CanMB32To63Isr_2
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 32 ... 63
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_2Cat)
#    if (osdIsrCanIsr_2Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB32To63Isr_2 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_2Cat)
#    if (osdIsrCanIsr_2Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB32To63Isr_2( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB32To63Interrupt(CanPhysToLogChannel_2); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanMB32To63Isr_2 */
/* CODE CATEGORY 1 END */
#    endif /* C_ENABLE_MAX_BUFFER_64 */
#   endif /* C_ENABLE_CAN_RXTX_INTERRUPT */
#  endif /* (kCanPhysToLogChannelIndex_2) */


#  if defined( kCanPhysToLogChannelIndex_3 )
#   if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/****************************************************************************
| NAME:             CanBusOffIsr_3
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for BusOff
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_3Cat)
#    if (osdIsrCanIsr_3Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanBusOffIsr_3 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_3Cat)
#    if (osdIsrCanIsr_3Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanBusOffIsr_3( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanBusOffInterrupt(CanPhysToLogChannel_3); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanBusOffIsr_3 */
/* CODE CATEGORY 1 END */
#   endif /* C_ENABLE_CAN_BUSOFF_INTERRUPT */

#   if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/****************************************************************************
| NAME:             CanWakeupIsr_3
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for Wakeup
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_3Cat)
#    if (osdIsrCanIsr_3Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanWakeUpIsr_3 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_3Cat)
#    if (osdIsrCanIsr_3Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanWakeUpIsr_3( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanWakeUpInterrupt(CanPhysToLogChannel_3); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanWakeUpIsr_3 */
/* CODE CATEGORY 1 END */      
#   endif /* C_ENABLE_CAN_WAKEUP_INTERRUPT */

#   if defined( C_ENABLE_CAN_RXTX_INTERRUPT )

/****************************************************************************
| NAME:             CanMB0To15Isr_3
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 0 ... 15
****************************************************************************/      
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_3Cat)
#    if (osdIsrCanIsr_3Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB0To15Isr_3 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_3Cat)
#    if (osdIsrCanIsr_3Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB0To15Isr_3( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB0To31Interrupt(CanPhysToLogChannel_3); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanMB0To15Isr_3 */
/* CODE CATEGORY 1 END */      

/****************************************************************************
| NAME:             CanMB16To31Isr_3
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 16 ... 31
****************************************************************************/      
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_3Cat)
#    if (osdIsrCanIsr_3Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB16To31Isr_3 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_3Cat)
#    if (osdIsrCanIsr_3Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB16To31Isr_3( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB0To31Interrupt(CanPhysToLogChannel_3); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanMB16To31Isr_3 */
/* CODE CATEGORY 1 END */

#    if defined( C_ENABLE_MAX_BUFFER_64 )
/****************************************************************************
| NAME:             CanMB32To63Isr_3
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 32 ... 63
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_3Cat)
#    if (osdIsrCanIsr_3Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB32To63Isr_3 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_3Cat)
#    if (osdIsrCanIsr_3Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB32To63Isr_3( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB32To63Interrupt(CanPhysToLogChannel_3); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanMB32To63Isr_3 */
/* CODE CATEGORY 1 END */
#    endif /* C_ENABLE_MAX_BUFFER_64 */
#   endif /* C_ENABLE_CAN_RXTX_INTERRUPT */
#  endif /* (kCanPhysToLogChannelIndex_3) */


#  if defined( kCanPhysToLogChannelIndex_4 )
#   if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/****************************************************************************
| NAME:             CanBusOffIsr_4
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for BusOff
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_4Cat)
#    if (osdIsrCanIsr_4Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanBusOffIsr_4 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_4Cat)
#    if (osdIsrCanIsr_4Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanBusOffIsr_4( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanBusOffInterrupt(CanPhysToLogChannel_4); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanBusOffIsr_4 */
/* CODE CATEGORY 1 END */
#   endif /* C_ENABLE_CAN_BUSOFF_INTERRUPT */

#   if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/****************************************************************************
| NAME:             CanWakeupIsr_4
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for Wakeup
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_4Cat)
#    if (osdIsrCanIsr_4Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanWakeUpIsr_4 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_4Cat)
#    if (osdIsrCanIsr_4Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanWakeUpIsr_4( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanWakeUpInterrupt(CanPhysToLogChannel_4); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanWakeUpIsr_4 */
/* CODE CATEGORY 1 END */      
#   endif /* C_ENABLE_CAN_WAKEUP_INTERRUPT */

#   if defined( C_ENABLE_CAN_RXTX_INTERRUPT )

/****************************************************************************
| NAME:             CanMB0To15Isr_4
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 0 ... 15
****************************************************************************/      
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_4Cat)
#    if (osdIsrCanIsr_4Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB0To15Isr_4 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_4Cat)
#    if (osdIsrCanIsr_4Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB0To15Isr_4( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB0To31Interrupt(CanPhysToLogChannel_4); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanMB0To15Isr_4 */
/* CODE CATEGORY 1 END */      

/****************************************************************************
| NAME:             CanMB16To31Isr_4
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 16 ... 31
****************************************************************************/      
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_4Cat)
#    if (osdIsrCanIsr_4Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB16To31Isr_4 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_4Cat)
#    if (osdIsrCanIsr_4Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB16To31Isr_4( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB0To31Interrupt(CanPhysToLogChannel_4); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanMB16To31Isr_4 */
/* CODE CATEGORY 1 END */

#    if defined( C_ENABLE_MAX_BUFFER_64 )
/****************************************************************************
| NAME:             CanMB32To63Isr_4
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 32 ... 63
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_4Cat)
#    if (osdIsrCanIsr_4Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB32To63Isr_4 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_4Cat)
#    if (osdIsrCanIsr_4Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB32To63Isr_4( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB32To63Interrupt(CanPhysToLogChannel_4); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanMB32To63Isr_4 */
/* CODE CATEGORY 1 END */
#    endif /* C_ENABLE_MAX_BUFFER_64 */
#   endif /* C_ENABLE_CAN_RXTX_INTERRUPT */
#  endif /* (kCanPhysToLogChannelIndex_4) */


#  if defined( kCanPhysToLogChannelIndex_5 )
#   if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/****************************************************************************
| NAME:             CanBusOffIsr_5
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for BusOff
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_5Cat)
#    if (osdIsrCanIsr_5Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanBusOffIsr_5 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_5Cat)
#    if (osdIsrCanIsr_5Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanBusOffIsr_5( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanBusOffInterrupt(CanPhysToLogChannel_5); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanBusOffIsr_5 */
/* CODE CATEGORY 1 END */
#   endif /* C_ENABLE_CAN_BUSOFF_INTERRUPT */

#   if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/****************************************************************************
| NAME:             CanWakeupIsr_5
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for Wakeup
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_5Cat)
#    if (osdIsrCanIsr_5Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanWakeUpIsr_5 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_5Cat)
#    if (osdIsrCanIsr_5Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanWakeUpIsr_5( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanWakeUpInterrupt(CanPhysToLogChannel_5); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanWakeUpIsr_5 */
/* CODE CATEGORY 1 END */      
#   endif /* C_ENABLE_CAN_WAKEUP_INTERRUPT */

#   if defined( C_ENABLE_CAN_RXTX_INTERRUPT )

/****************************************************************************
| NAME:             CanMB0To15Isr_5
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 0 ... 15
****************************************************************************/      
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_5Cat)
#    if (osdIsrCanIsr_5Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB0To15Isr_5 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_5Cat)
#    if (osdIsrCanIsr_5Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB0To15Isr_5( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB0To31Interrupt(CanPhysToLogChannel_5); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanMB0To15Isr_5 */
/* CODE CATEGORY 1 END */      

/****************************************************************************
| NAME:             CanMB16To31Isr_5
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 16 ... 31
****************************************************************************/      
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_5Cat)
#    if (osdIsrCanIsr_5Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB16To31Isr_5 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_5Cat)
#    if (osdIsrCanIsr_5Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB16To31Isr_5( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB0To31Interrupt(CanPhysToLogChannel_5); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanMB16To31Isr_5 */
/* CODE CATEGORY 1 END */

#    if defined( C_ENABLE_MAX_BUFFER_64 )
/****************************************************************************
| NAME:             CanMB32To63Isr_5
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 32 ... 63
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_5Cat)
#    if (osdIsrCanIsr_5Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB32To63Isr_5 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_5Cat)
#    if (osdIsrCanIsr_5Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB32To63Isr_5( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB32To63Interrupt(CanPhysToLogChannel_5); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanMB32To63Isr_5 */
/* CODE CATEGORY 1 END */
#    endif /* C_ENABLE_MAX_BUFFER_64 */
#   endif /* C_ENABLE_CAN_RXTX_INTERRUPT */
#  endif /* (kCanPhysToLogChannelIndex_5) */


#  if defined( kCanPhysToLogChannelIndex_6 )
#   if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/****************************************************************************
| NAME:             CanBusOffIsr_6
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for BusOff
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_6Cat)
#    if (osdIsrCanIsr_6Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanBusOffIsr_6 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_6Cat)
#    if (osdIsrCanIsr_6Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanBusOffIsr_6( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanBusOffInterrupt(CanPhysToLogChannel_6); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanBusOffIsr_6 */
/* CODE CATEGORY 1 END */
#   endif /* C_ENABLE_CAN_BUSOFF_INTERRUPT */

#   if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/****************************************************************************
| NAME:             CanWakeupIsr_6
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for Wakeup
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_6Cat)
#    if (osdIsrCanIsr_6Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanWakeUpIsr_6 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_6Cat)
#    if (osdIsrCanIsr_6Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanWakeUpIsr_6( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanWakeUpInterrupt(CanPhysToLogChannel_6); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanWakeUpIsr_6 */
/* CODE CATEGORY 1 END */      
#   endif /* C_ENABLE_CAN_WAKEUP_INTERRUPT */

#   if defined( C_ENABLE_CAN_RXTX_INTERRUPT )

/****************************************************************************
| NAME:             CanMB0To15Isr_6
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 0 ... 15
****************************************************************************/      
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_6Cat)
#    if (osdIsrCanIsr_6Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB0To15Isr_6 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_6Cat)
#    if (osdIsrCanIsr_6Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB0To15Isr_6( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB0To31Interrupt(CanPhysToLogChannel_6); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanMB0To15Isr_6 */
/* CODE CATEGORY 1 END */      

/****************************************************************************
| NAME:             CanMB16To31Isr_6
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 16 ... 31
****************************************************************************/      
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_6Cat)
#    if (osdIsrCanIsr_6Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB16To31Isr_6 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_6Cat)
#    if (osdIsrCanIsr_6Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB16To31Isr_6( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB0To31Interrupt(CanPhysToLogChannel_6); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanMB16To31Isr_6 */
/* CODE CATEGORY 1 END */

#    if defined( C_ENABLE_MAX_BUFFER_64 )
/****************************************************************************
| NAME:             CanMB32To63Isr_6
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 32 ... 63
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_6Cat)
#    if (osdIsrCanIsr_6Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB32To63Isr_6 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_6Cat)
#    if (osdIsrCanIsr_6Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB32To63Isr_6( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB32To63Interrupt(CanPhysToLogChannel_6); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanMB32To63Isr_6 */
/* CODE CATEGORY 1 END */
#    endif /* C_ENABLE_MAX_BUFFER_64 */
#   endif /* C_ENABLE_CAN_RXTX_INTERRUPT */
#  endif /* (kCanPhysToLogChannelIndex_6) */


#  if defined( kCanPhysToLogChannelIndex_7 )
#   if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
/****************************************************************************
| NAME:             CanBusOffIsr_7
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for BusOff
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_7Cat)
#    if (osdIsrCanIsr_7Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanBusOffIsr_7 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_7Cat)
#    if (osdIsrCanIsr_7Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanBusOffIsr_7( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanBusOffInterrupt(CanPhysToLogChannel_7); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanBusOffIsr_7 */
/* CODE CATEGORY 1 END */
#   endif /* C_ENABLE_CAN_BUSOFF_INTERRUPT */

#   if defined( C_ENABLE_CAN_WAKEUP_INTERRUPT )
/****************************************************************************
| NAME:             CanWakeupIsr_7
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for Wakeup
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_7Cat)
#    if (osdIsrCanIsr_7Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanWakeUpIsr_7 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_7Cat)
#    if (osdIsrCanIsr_7Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanWakeUpIsr_7( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanWakeUpInterrupt(CanPhysToLogChannel_7); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanWakeUpIsr_7 */
/* CODE CATEGORY 1 END */      
#   endif /* C_ENABLE_CAN_WAKEUP_INTERRUPT */

#   if defined( C_ENABLE_CAN_RXTX_INTERRUPT )

/****************************************************************************
| NAME:             CanMB0To15Isr_7
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 0 ... 15
****************************************************************************/      
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_7Cat)
#    if (osdIsrCanIsr_7Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB0To15Isr_7 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_7Cat)
#    if (osdIsrCanIsr_7Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB0To15Isr_7( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB0To31Interrupt(CanPhysToLogChannel_7); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanMB0To15Isr_7 */
/* CODE CATEGORY 1 END */      

/****************************************************************************
| NAME:             CanMB16To31Isr_7
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 16 ... 31
****************************************************************************/      
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_7Cat)
#    if (osdIsrCanIsr_7Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB16To31Isr_7 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_7Cat)
#    if (osdIsrCanIsr_7Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB16To31Isr_7( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB0To31Interrupt(CanPhysToLogChannel_7); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* end of CanMB16To31Isr_7 */
/* CODE CATEGORY 1 END */

#    if defined( C_ENABLE_MAX_BUFFER_64 )
/****************************************************************************
| NAME:             CanMB32To63Isr_7
| CALLED BY:        FlexCAN interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service function for message buffer 32 ... 63
****************************************************************************/
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_OSEK_OS ) && defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_7Cat)
#    if (osdIsrCanIsr_7Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanMB32To63Isr_7 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && defined (osdIsrCanIsr_7Cat)
#    if (osdIsrCanIsr_7Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanMB32To63Isr_7( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  CanMB32To63Interrupt(CanPhysToLogChannel_7); /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
} /* END OF CanMB32To63Isr_7 */
/* CODE CATEGORY 1 END */
#    endif /* C_ENABLE_MAX_BUFFER_64 */
#   endif /* C_ENABLE_CAN_RXTX_INTERRUPT */
#  endif /* (kCanPhysToLogChannelIndex_7) */

# endif /* C_FLEXCAN_ISR_GROUP_A || C_FLEXCAN_ISR_GROUP_B */
         




#endif /* C_ENABLE_SINGLE_ISR_API */

/* **************************************************************************
| NAME:             CanInit
| CALLED BY:        CanInitPowerOn(), Network management
| PRECONDITIONS:    none
| INPUT PARAMETERS: Handle to initstructure
| RETURN VALUES:    none
| DESCRIPTION:      initialization of chip-hardware
|                   initialization of receive and transmit message objects
************************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanInit( CAN_CHANNEL_CANTYPE_FIRST CanInitHandle initObject )     /* PRQA S 1505 */
{
#if defined( C_ENABLE_CAN_RAM_CHECK )
  vuint8                 canRamCheckStatus;
#endif
  CanObjectHandle        hwObjHandle;
#if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION ) || \
    defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
  CanTransmitHandle      txHandle;
#endif
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
  CanReceiveHandle       rxHandle;
#endif
  CanObjectHandle        logTxObjHandle;

  vuint8       loopResult;
  tFLEXCANPtr  pFlexCANLocal;
  
  
  #if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING ) && defined( C_ENABLE_RX_BASICCAN_OBJECTS )
  # if defined( C_ENABLE_FLEXCAN_RXFIFO ) 
  #  if defined( C_ENABLE_FLEXCAN_INDIV_RXMASK )
  vuint8   locRxHandle;
  #  endif
  # else
  vuint8   locRxHandle;
  # endif
  #endif
  
  #if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
  # if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
  tCanInitBasicCanPtr pInitBasicCan; /* pointer to ROM table CanInitBasicCan[] */  
  #  if defined( C_ENABLE_FLEXCAN_INDIV_RXMASK )
  vuint16  locMsgIDMaskHi;
  vuint16  locMsgIDMaskLo;  
  #  else
  vuint32  locMsgIDMask;
  #  endif
  #  if defined( C_ENABLE_FLEXCAN_RXFIFO )
  tRXFIFOPtr pRxFIFO;
  #  endif
  # endif
  # if defined( C_ENABLE_FLEXCAN_INDIV_RXMASK )
  #  if defined( C_ENABLE_RX_BASICCAN_OBJECTS ) || defined( C_ENABLE_RX_FULLCAN_OBJECTS )  
  tCanRxMaskPtr pIndivRxMask; /* pointer to FlexCAN individual receive mask registers */
  #  endif
  # endif
  # if defined( C_ENABLE_WORKAROUND_ERRATA_5164 )
  vuint16 canMcrReg;
  # endif
  #endif
  
  #if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
  CanObjectHandle hwAdjObjHandle;
  #endif
  CanDeclareGlobalInterruptOldStatus

#if defined( C_HL_ENABLE_LAST_INIT_OBJ )  
  lastInitObject[channel] = initObject;
#endif

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
/* Msg(4:3759) Implicit conversion: int to unsigned short. MISRA Rule 43 - no change in RI 1.4 */
  initObject  += CAN_HL_INIT_OBJ_STARTINDEX(channel);
#endif


#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);     /* PRQA S 3109 */
#endif
  assertUser(initObject < kCanNumberOfInitObjects, channel, kErrorInitObjectHdlTooLarge);    /* PRQA S 3109 */
  assertUser(initObject < CAN_HL_INIT_OBJ_STOPINDEX(channel), channel, kErrorInitObjectHdlTooLarge);     /* PRQA S 3109 */

#if defined( C_ENABLE_CAN_RAM_CHECK )
  canRamCheckStatus = kCanRamCheckOk;
#endif

  {

    pFlexCANLocal = pFLEXCAN(canHwChannel);
    #if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
    # if defined( C_ENABLE_RX_BASICCAN_OBJECTS ) || defined( C_ENABLE_RX_FULLCAN_OBJECTS )
    #  if defined( C_ENABLE_FLEXCAN_INDIV_RXMASK )
    pIndivRxMask = pCanRxMask(canHwChannel);
    #  endif
    # endif
    # if defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && defined( C_ENABLE_FLEXCAN_RXFIFO )
    pRxFIFO = pRXFIFO(canHwChannel);
    # endif
    #endif
    
    
    # if defined (C_ENABLE_TX_FULLCAN_DELAYED_START)
    /* clear delayed fullcan Tx pendings */
    canLL_canDelayedFullCANTxRequest[channel][0] = 0;
    canLL_canDelayedFullCANTxRequest[channel][1] = 0;
    # endif /* C_ENABLE_TX_FULLCAN_DELAYED_START */
    
    CanMicroModeSystem();
     
    CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_MDIS); /* enable FlexCAN */
    /* request init mode (FREEZE mode) */
    CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_FRZ);
    CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_HALT);
    if ((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_MCR) != kFlexCAN_FREEZE_MODE)
    {
      CanLL_ApplCanTimerStart(kCanLoopEnterFreezeModeInit); /* start hw loop timer */
      do  
      { /* wait for FRZACK */  
        loopResult = CanLL_ApplCanTimerLoop(kCanLoopEnterFreezeModeInit);  
      }while(((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_MCR) != kFlexCAN_FREEZE_MODE) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */
      CanLL_ApplCanTimerEnd(kCanLoopEnterFreezeModeInit); /* stop hw loop timer */
    }
    
    CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_SUPV); /* set all CAN register except the MCR register in unrestricted memory space */
    
    CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_MDIS); /* disable FlexCAN module before clock selection */
    
    #if defined( C_ENABLE_FLEXCAN_SYSTEM_CLOCK )
    pFlexCANLocal->control0 |= (vuint16)(kFlexCAN_CLK_SRC); /* SBSW_CAN_LL005 */
    #else
    pFlexCANLocal->control0 &= (vuint16)~(kFlexCAN_CLK_SRC); /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_LL005 */
    if(CanInitObject[initObject].CanInitCtrl0 != 0)
    {
      pFlexCANLocal->control0 |= (vuint16)(kFlexCAN_CLK_SRC); /* SBSW_CAN_LL005 */
    }
    #endif
    
    CAN_CLEAR_MDIS(); /* clear MDIS bit */ /* SBSW_CAN_LL005 */
    
    CanNestedGlobalInterruptDisable(); /* SBSW_CAN_LL002 */
    #if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING ) && defined( C_ENABLE_WORKAROUND_ERRATA_5164 )
    canMcrReg = CanErrata5164WorkaroundBegin( CAN_HW_CHANNEL_CANPARA_ONLY );
    #endif /* C_ENABLE_INDIVIDUAL_BUFFER_MASKING && C_ENABLE_WORKAROUND_ERRATA_5164 */
    
    CAN_WRITE_PROTECTED_REG(pFlexCANLocal->canmcr, kFlexCAN_SOFT_RST); /* request soft reset */ /* SBSW_CAN_LL005 */
    
    /* wait for soft reset confirmation from hardware */
    CanLL_ApplCanTimerStart(kCanLoopInit); /* start hw loop timer */ /* SBSW_CAN_LL003 */
    do
    { /* wait for SOFT_RST */
      loopResult = CanLL_ApplCanTimerLoop(kCanLoopInit); /* SBSW_CAN_LL003 */
    }while(((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_SOFT_RST) == kFlexCAN_SOFT_RST) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */
    CanLL_ApplCanTimerEnd(kCanLoopInit);  /* stop hw loop timer */ /* SBSW_CAN_LL003 */
    
    
    CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_SUPV); /* set all CAN register except the MCR register in unrestricted memory space */ /* SBSW_CAN_LL005 */
    
    for(hwObjHandle = 0; hwObjHandle < CAN_HW_TX_STOPINDEX(canHwChannel); hwObjHandle++)
    {
      pFlexCANLocal->canObject[hwObjHandle].control = 0; /* set mailbox inactive */ /* SBSW_CAN_LL013 */
    }
    
    
    /* configure maximum message buffers */
    # if defined( C_CAN_MAX_BUFFER_MIXED )
    CAN_WRITE_PROTECTED_REG(pFlexCANLocal->canmaxmb, (vuint16)(CanMaxMB[canHwChannel] - 1)); /* SBSW_CAN_LL005 */
    # else
    CAN_WRITE_PROTECTED_REG(pFlexCANLocal->canmaxmb, (vuint16)(kCanMaxMB - 1)); /* SBSW_CAN_LL005 */
    # endif
    
    CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_USR_CONFIG_BITS); /* clear user configurable bits in MCR */ /* SBSW_CAN_LL005 */
    
    #if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
    # if defined( C_ENABLE_FLEXCAN_INDIV_RXMASK )
    /* Set BCC bit to allow individual buffer masking configuration */
    CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_BCC); /* SBSW_CAN_LL005 */
    # else
    /* clear BCC bit to disable individual buffer masking configuration */
    CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_BCC); /* SBSW_CAN_LL005 */
    # endif
    # if defined( C_ENABLE_FLEXCAN_RXFIFO ) && defined (C_ENABLE_RX_BASICCAN_OBJECTS)
    CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_FEN); /* Set FEN bit to enable Rx FIFO */ /* SBSW_CAN_LL005 */
    # endif
    #endif
    
    #if defined( C_ENABLE_CANCEL_IN_HW )
    # if defined( C_ENABLE_CANCEL_IN_HW_INT )
    CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmaxmb, kFlexCAN_AEN); /* SBSW_CAN_LL005 */
    # endif
    #endif
    
    # if defined( C_ENABLE_SLEEP_WAKEUP ) && defined( C_ENABLE_FLEXCAN_DOZE_MODE )
    CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_SLF_WAK); /* enable wakeup by bus */ /* SBSW_CAN_LL005 */
    #  if defined( C_ENABLE_WAKEUP_POLLING )
    CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_WAK_MSK); /* clear WAK_MSK for polling mode */ /* SBSW_CAN_LL005 */
    #  else
    CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_WAK_MSK); /* set WAK_MSK for wakeup interrupts */ /* SBSW_CAN_LL005 */
    #  endif
    # endif
    
    
    #if defined( C_ENABLE_REJECT_SELF_RX_BY_HW )
    /* frame rejection performed by hardware */
    CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_SRX_DIS); /* SBSW_CAN_LL005 */
    #endif
    
    CanMicroModeRestore();
    
    
    #if defined( C_ENABLE_FLEXCAN_SYSTEM_CLOCK )
    pFlexCANLocal->control0 = (vuint16)(((vuint16)kFlexCAN_CLK_SRC) | ((vuint16)CanInitObject[initObject].CanInitCtrl1)); /* SBSW_CAN_LL005 */
    #else
    pFlexCANLocal->control0 = (vuint16)(((vuint16)CanInitObject[initObject].CanInitCtrl0 << 8) | ((vuint16)CanInitObject[initObject].CanInitCtrl1)); /* SBSW_CAN_LL005 */
    #endif
    pFlexCANLocal->control1 = (vuint16)(((vuint16)CanInitObject[initObject].CanInitPrDiv << 8) | ((vuint16)CanInitObject[initObject].CanInitCtrl2)); /* SBSW_CAN_LL005 */
    
    #if defined( C_ENABLE_FLEXCAN_SAMPLING_MODE )
    pFlexCANLocal->control0 |= (vuint16)(kFlexCAN_SMP); /* SBSW_CAN_LL005 */
    #endif
    #if defined( C_ENABLE_FLEXCAN_AUTO_RECOVERY )
    pFlexCANLocal->control0 &= (vuint16)~(kFlexCAN_BOFF_REC); /* PRQA S 0277 */ /* MD_Can_0277_negation */ /* SBSW_CAN_LL005 */
    #else
    pFlexCANLocal->control0 |= (vuint16)(kFlexCAN_BOFF_REC); /* SBSW_CAN_LL005 */
    #endif
    
    /* Init Tx-Objects -------------------------------------------------------- */
    /* init saved Tx handles: */                   
    /* in case of CommonCAN, transmission is always on the frist HW channel of a CommonCAN channel */
    {
#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
      assertGen( ((vsintx)CAN_HL_HW_TX_STOPINDEX(canHwChannel) + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel)) 
                 == CAN_HL_LOG_HW_TX_STOPINDEX(canHwChannel), channel, kErrorHwToLogTxObjCalculation);          /* PRQA S 3109 */ /* ESCAN00062667 */
      assertGen( ((vsintx)CAN_HL_HW_TX_STARTINDEX(canHwChannel) + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel)) 
                 == CAN_HL_LOG_HW_TX_STARTINDEX(canHwChannel), channel, kErrorHwToLogTxObjCalculation);         /* PRQA S 3109 */ /* ESCAN00062667 */
      assertGen( CAN_HL_LOG_HW_TX_STARTINDEX(canHwChannel) <= CAN_HL_LOG_HW_TX_STOPINDEX(canHwChannel), channel, kErrorHwToLogTxObjCalculation);  /* PRQA S 3109 */
#endif
  
      for (hwObjHandle=CAN_HL_HW_TX_STARTINDEX(canHwChannel); hwObjHandle<CAN_HL_HW_TX_STOPINDEX(canHwChannel); hwObjHandle++ )     /* lint !e661 */
      {
        logTxObjHandle = (CanObjectHandle)((vsintx)hwObjHandle + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel));     /* lint !e661 */

#if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION ) || \
    defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
        if((canStatus[channel] & kCanHwIsInit) == kCanHwIsInit)                    /* lint !e661 */
        {
          /* inform application, if a pending transmission is canceled */
          txHandle = canHandleCurTxObj[logTxObjHandle];

# if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
          if( txHandle < kCanNumberOfTxObjects )
          {
            APPLCANCANCELNOTIFICATION(channel, txHandle);
          }
# endif
# if defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
          if( txHandle == kCanBufferMsgTransmit)
          { 
            APPLCANMSGCANCELNOTIFICATION(channel);
          } 
# endif
        }
#endif

        canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;                   /* MsgObj is free */

#if defined( C_ENABLE_CAN_RAM_CHECK )
        if(kCanTrue == CanLL_IsMailboxCorrupt(CAN_HW_CHANNEL_CANPARA_FIRST hwObjHandle))
        {
# if defined( C_ENABLE_NOTIFY_CORRUPT_MAILBOX )
          ApplCanCorruptMailbox(CAN_CHANNEL_CANPARA_FIRST hwObjHandle);
# endif
          canRamCheckStatus = kCanRamCheckFailed;
        }
#endif

        {
          pFlexCANLocal->canObject[hwObjHandle].control = kTxCodeInactive; /* set transmit object inactive */ /* SBSW_CAN_LL011 */
        }
      }

    }

    /* init unused msg objects ------------------------------------------------ */
    for (hwObjHandle=CAN_HL_HW_UNUSED_STARTINDEX(canHwChannel); hwObjHandle<CAN_HL_HW_UNUSED_STOPINDEX(canHwChannel); hwObjHandle++ )  /* lint !e661 !e681 */
    {
      /* only used for Hll: unused objects need no special initialization because all objects are set to inactive directly after soft reset */
      break;
    }


#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
    /* init full can receive msg objects: ------------------------------------- */
    for (hwObjHandle=CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel); hwObjHandle<CAN_HL_HW_RX_FULL_STOPINDEX(canHwChannel); hwObjHandle++ )
    {
      /* brackets to avoid lint info 834 */
      rxHandle = (hwObjHandle-CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel))+CAN_HL_RX_FULL_STARTINDEX(canHwChannel);

#if defined( C_ENABLE_CAN_RAM_CHECK )
      if(kCanTrue == CanLL_IsMailboxCorrupt(CAN_HW_CHANNEL_CANPARA_FIRST hwObjHandle))
      {
# if defined( C_ENABLE_NOTIFY_CORRUPT_MAILBOX )
        ApplCanCorruptMailbox(CAN_CHANNEL_CANPARA_FIRST hwObjHandle);
# endif
        canRamCheckStatus = kCanRamCheckFailed;
      }
#endif

      hwAdjObjHandle = hwObjHandle;
      #if defined( C_HL_ENABLE_ADJUST_RXHANDLE )
      if(hwAdjObjHandle > 13)
      {
        hwAdjObjHandle += 2;
      }
      #endif
      
      assertHardware(hwAdjObjHandle < CAN_HW_RX_FULL_STOPINDEX(canHwChannel), canHwChannel, kCanInvalidHwObjHandle); /* SBSW_CAN_LL010 */
      
      pFlexCANLocal->canObject[hwAdjObjHandle].msgID = CAN_MSGID((CanGetRxId0(rxHandle))); /* SBSW_CAN_LL011 */
      
      
      {
        pFlexCANLocal->canObject[hwAdjObjHandle].control = (vuint32)(kRxCodeEmpty | ((vuint32)((CanGetRxIdType(rxHandle))) << 16)); /* set ID type and set mailbox ready for receive */ /* SBSW_CAN_LL011 */
      }
    }
#endif

#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
    /* init basic can receive msg object: ------------------------------------- */
    for (hwObjHandle=CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel); hwObjHandle<CAN_HL_HW_RX_BASIC_STOPINDEX(canHwChannel); hwObjHandle++ )
    {
#if defined( C_ENABLE_CAN_RAM_CHECK )
      if(kCanTrue == CanLL_IsMailboxCorrupt(CAN_HW_CHANNEL_CANPARA_FIRST hwObjHandle))
      {
# if defined( C_ENABLE_NOTIFY_CORRUPT_MAILBOX )
        ApplCanCorruptMailbox(CAN_CHANNEL_CANPARA_FIRST hwObjHandle);
# endif
        canRamCheckStatus = kCanRamCheckFailed;
      }
#endif

      /* the LL driver has to know which ID tpyes have to be received by which object */
    }
#endif
                     
    #if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
    
    # if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
    /* initialize individual mask for each BasicCAN mailbox */
    pInitBasicCan = &(((tCanInitBasicCanPtr)(CanInitBasicCan))[initObject * kCanNumberOfRxBasicMasks]); /* PRQA S 0310 */ /* MD_Can_0310 */
    
    #  if defined( C_ENABLE_FLEXCAN_RXFIFO )
    #   if defined( C_ENABLE_FLEXCAN_INDIV_RXMASK )
    locRxHandle = CAN_HW_RX_BASIC_STOPINDEX(canHwChannel) >> 1;
    for(hwObjHandle = 0; hwObjHandle < locRxHandle; hwObjHandle++)
    { 
      locMsgIDMaskHi = pInitBasicCan[hwObjHandle].CanInitMaskHi & (vuint16)0x1FFF;
      locMsgIDMaskLo = pInitBasicCan[hwObjHandle].CanInitMaskLo;
      pIndivRxMask->indivRxMask[hwObjHandle] = (vuint32)(((vuint32)locMsgIDMaskHi << 17) | ((vuint32)locMsgIDMaskLo << 1));
      pIndivRxMask->indivRxMask[hwObjHandle] |= kRxFIFO_MASK; /* bits REM and EXT must always match */
      
      locMsgIDMaskHi = pInitBasicCan[hwObjHandle].CanInitCodeHi & (vuint16)0x1FFF;
      locMsgIDMaskLo = pInitBasicCan[hwObjHandle].CanInitCodeLo;
      pRxFIFO->rxIDTAB[hwObjHandle] = (vuint32)(((vuint32)locMsgIDMaskHi << 17) | ((vuint32)locMsgIDMaskLo << 1));
      if((pInitBasicCan[hwObjHandle].CanInitCodeHi & (vuint16)0x8000) != 0)
      {
        pRxFIFO->rxIDTAB[hwObjHandle] |= kRxFIFO_EXT;
      }
    }
    for(hwObjHandle = locRxHandle; hwObjHandle < 8; hwObjHandle++)
    {
      pRxFIFO->rxIDTAB[hwObjHandle] = pRxFIFO->rxIDTAB[locRxHandle-1];
      pIndivRxMask->indivRxMask[hwObjHandle] = pIndivRxMask->indivRxMask[locRxHandle-1];
    }
    #   else
    /* initialize global mask register and ID register 0 ... 5 */
    pFLEXCAN(canHwChannel)->rxgmask  = kRxGMaskValue;
    locMsgIDMask = (((vuint32)pInitBasicCan[2].CanInitCodeHi & (vuint32)0x1FFF) << 17) | ((vuint32)pInitBasicCan[2].CanInitCodeLo << 1);
    if((pInitBasicCan[2].CanInitCodeHi & (vuint16)0x8000) != 0)
    {
      locMsgIDMask |= kRxFIFO_EXT;
    }
    for(hwObjHandle = 0; hwObjHandle < 6; hwObjHandle++)
    {
      pRxFIFO->rxIDTAB[hwObjHandle] = locMsgIDMask;
    }        
    
    /* initialize mask 14 register and ID register 6 */
    locMsgIDMask = (((vuint32)pInitBasicCan[0].CanInitMaskHi & (vuint32)0x1FFF) << 17) | ((vuint32)pInitBasicCan[0].CanInitMaskLo << 1);
    pFLEXCAN(canHwChannel)->rx14mask = locMsgIDMask | kRxFIFO_MASK;               
    locMsgIDMask = (((vuint32)pInitBasicCan[0].CanInitCodeHi & (vuint32)0x1FFF) << 17) | ((vuint32)pInitBasicCan[0].CanInitCodeLo << 1);
    if((pInitBasicCan[0].CanInitCodeHi & (vuint16)0x8000) != 0)
    {
      locMsgIDMask |= kRxFIFO_EXT;
    }
    pRxFIFO->rxIDTAB[6] = locMsgIDMask;
    
    /* initialize mask 15 register and ID register 7 */
    locMsgIDMask = (((vuint32)pInitBasicCan[1].CanInitMaskHi & (vuint32)0x1FFF) << 17) | ((vuint32)pInitBasicCan[1].CanInitMaskLo << 1);
    pFLEXCAN(canHwChannel)->rx15mask = locMsgIDMask | kRxFIFO_MASK;        
    locMsgIDMask = (((vuint32)pInitBasicCan[1].CanInitCodeHi & (vuint32)0x1FFF) << 17) | ((vuint32)pInitBasicCan[1].CanInitCodeLo << 1);
    if((pInitBasicCan[1].CanInitCodeHi & (vuint16)0x8000) != 0)
    {
      locMsgIDMask |= kRxFIFO_EXT;
    }
    pRxFIFO->rxIDTAB[7] = locMsgIDMask;
    #   endif
    #  else
    for(hwObjHandle = CAN_HW_RX_BASIC_STARTINDEX(canHwChannel); hwObjHandle < CAN_HW_RX_BASIC_STOPINDEX(canHwChannel); hwObjHandle++)
    {  
      locRxHandle = (vuint8)(((vuint8)(hwObjHandle - CAN_HW_RX_BASIC_STARTINDEX(canHwChannel)) & (vuint8)0xFE) >> 1); /* calculate BasicCan offset */
      
      locMsgIDMaskHi = pInitBasicCan[locRxHandle].CanInitMaskHi & (vuint16)0x1FFF;
      locMsgIDMaskLo = pInitBasicCan[locRxHandle].CanInitMaskLo;
      pIndivRxMask->indivRxMask[hwObjHandle] = (vuint32)(((vuint32)locMsgIDMaskHi << 16) | ((vuint32)locMsgIDMaskLo)); /* SBSW_CAN_LL011 */
      
      pFlexCANLocal->canObject[hwObjHandle].msgID  = (vuint32)(((vuint32)pInitBasicCan[locRxHandle].CanInitCodeHi & (vuint32)0x1FFF) << 16); /* SBSW_CAN_LL011 */
      pFlexCANLocal->canObject[hwObjHandle].msgID |= (vuint32)pInitBasicCan[locRxHandle].CanInitCodeLo; /* SBSW_CAN_LL011 */
          
      {
        pFlexCANLocal->canObject[hwObjHandle].control = kRxCodeEmpty; /* configure mailbox as receive message buffer */ /* SBSW_CAN_LL011 */
      }
      #if defined( C_ENABLE_EXTENDED_ID )
      # if defined( C_ENABLE_MIXED_ID )
      if((pInitBasicCan[locRxHandle].CanInitCodeHi & (vuint16)0x8000) != 0)
      # endif
      {
        pFlexCANLocal->canObject[hwObjHandle].control |= CAN_IDTYPE_EXT; /* set IDE bit for extended ID */ /* SBSW_CAN_LL011 */
      }  
      #endif
    }  
    #  endif /* C_ENABLE_FLEXCAN_RXFIFO */
    # endif /* C_ENABLE_RX_BASICCAN_OBJECTS */
    
    # if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) && defined( C_ENABLE_FLEXCAN_INDIV_RXMASK )
    for(hwObjHandle = CAN_HW_RX_FULL_STARTINDEX(canHwChannel); hwObjHandle < CAN_HW_RX_FULL_STOPINDEX(canHwChannel); hwObjHandle++)
    {
      /* initialize individual mask values for each FullCAN mailbox */
      #if defined( C_ENABLE_EXTENDED_ID )     
      # if defined( C_ENABLE_MIXED_ID )
      if((pFlexCANLocal->canObject[hwObjHandle].control & CAN_IDTYPE_EXT) != 0)
      {
        pIndivRxMask->indivRxMask[hwObjHandle] = kCanRxMaskExt; /* SBSW_CAN_LL011 */
      }
      else
      {
        pIndivRxMask->indivRxMask[hwObjHandle] = kCanRxMaskStd; /* SBSW_CAN_LL011 */
      }
      # else
      pIndivRxMask->indivRxMask[hwObjHandle] = kCanRxMaskExt; /* SBSW_CAN_LL011 */
      # endif      
      #else
      pIndivRxMask->indivRxMask[hwObjHandle] = kCanRxMaskStd; /* SBSW_CAN_LL011 */
      #endif      
    }
    # endif /* C_ENABLE_RX_FULLCAN_OBJECTS */
    
    #endif /* C_ENABLE_INDIVIDUAL_BUFFER_MASKING */
    
    /* clear BusOff, Error and WakeUp interrupt flags: ESCAN00032346 */
    pFlexCANLocal->estat = CANSFR_CAST(kFlexCAN_BOFF_INT | kFlexCAN_ERR_INT | kFlexCAN_WAKE_INT);
    
    #if (defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL) && !defined (C_ENABLE_OSEK_CAN_INTCTRL)) 
    if(canCanInterruptCounter[channel] == 0)
    {            
      #if defined( C_ENABLE_CAN_BUSOFF_INTERRUPT )
      pFlexCANLocal->control0 |= kFlexCAN_BOFF_MSK; /* SBSW_CAN_LL005 */
      #endif
      
      pFlexCANLocal->imask_lo = CAN_INT_MASK_LO(canHwChannel); /* SBSW_CAN_LL005 */
      #if defined( C_ENABLE_FLEXCAN_RXFIFO ) && defined (C_ENABLE_RX_BASICCAN_OBJECTS) && !defined( C_ENABLE_RX_BASICCAN_POLLING )
      pFlexCANLocal->imask_lo |= (vuint32)0x0020; /* enable Rx FIFO interrupt */ /* SBSW_CAN_LL005 */
      #endif
      
      #if defined( C_ENABLE_MAX_BUFFER_64 )
      # if defined( C_CAN_MAX_BUFFER_MIXED )
      if(CanMaxMB[canHwChannel] == 64)  
      # endif  
      {
        pFlexCANLocal->imask_hi = CAN_INT_MASK_HI(canHwChannel); /* SBSW_CAN_LL005 */
      }
      #endif  
    }
    #endif
    #if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING ) && defined( C_ENABLE_WORKAROUND_ERRATA_5164 )
    CanErrata5164WorkaroundEnd(CAN_HW_CHANNEL_CANPARA_FIRST canMcrReg);
    #endif /* C_ENABLE_INDIVIDUAL_BUFFER_MASKING && C_ENABLE_WORKAROUND_ERRATA_5164 */
    CanNestedGlobalInterruptRestore(); /* SBSW_CAN_LL002 */
    {
      CanMicroModeSystem();
      CAN_CLEAR_MDIS(); /* clear MDIS bit */
      CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_HALT); /* clear HALT bit */
      CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_FRZ);  /* clear FRZ bit */
      CanMicroModeRestore();
    }
  } /* end of loop over all hw channels */

#if defined( C_ENABLE_TX_OBSERVE )
  ApplCanInit( CAN_CHANNEL_CANPARA_FIRST CAN_HL_LOG_HW_TX_STARTINDEX(canHwChannel), CAN_HL_LOG_HW_TX_STOPINDEX(canHwChannel) );
#endif
#if defined( C_ENABLE_MSG_TRANSMIT_CONF_FCT )
  APPL_CAN_MSGTRANSMITINIT( CAN_CHANNEL_CANPARA_ONLY );
#endif

#if defined( C_ENABLE_CAN_RAM_CHECK )
  if( canRamCheckStatus == kCanRamCheckFailed)
  {
    /* let the application decide if communication is disabled */
    if (ApplCanMemCheckFailed(CAN_CHANNEL_CANPARA_ONLY) == kCanDisableCommunication)
    {
      canComStatus[channel] = kCanDisableCommunication;
    }  
  }
#endif


} /* END OF CanInit */
/* CODE CATEGORY 4 END */


/* **************************************************************************
| NAME:             CanInitPowerOn
| CALLED BY:        Application
| PRECONDITIONS:    This function must be called by the application before
|                   any other CAN driver function 
|                   Interrupts must be disabled
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Initialization of the CAN chip
************************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanInitPowerOn( void )
{ 

#if defined( C_ENABLE_VARIABLE_DLC )        || \
      defined( C_ENABLE_DYN_TX_OBJECTS )      || \
      defined( C_ENABLE_INDICATION_FLAG )     || \
      defined( C_ENABLE_CONFIRMATION_FLAG )
  CanTransmitHandle txHandle;
#endif
#if defined( C_ENABLE_VARIABLE_RX_DATALEN )
  CanReceiveHandle rxHandle;
#endif
  CAN_CHANNEL_CANTYPE_LOCAL


  VStdInitPowerOn();

#if defined( C_ENABLE_VARIABLE_DLC )
  for (txHandle = 0; txHandle < kCanNumberOfTxObjects; txHandle++)
  {
    assertGen(XT_TX_DLC(CanGetTxDlc(txHandle))<(vuint8)9, kCanAllChannels, kErrorTxROMDLCTooLarge);      /* PRQA S 3109 */
    canTxDLC_RAM[txHandle] = CanGetTxDlc(txHandle);
  }
#endif

#if defined( C_ENABLE_DYN_TX_OBJECTS )
  /*  Reset dynamic transmission object management -------------------------- */
  for (txHandle = 0; txHandle < kCanNumberOfTxDynObjects; txHandle++)
  {
    /*  Reset management information  */
    canTxDynObjReservedFlag[txHandle] = 0;
  }
#endif /* C_ENABLE_DYN_TX_OBJECTS */

#if defined( C_ENABLE_VARIABLE_RX_DATALEN )
  /*  Initialize the array with received dlc -------------------------- */
  for (rxHandle = 0; rxHandle < kCanNumberOfRxObjects; rxHandle++) {
    canVariableRxDataLen[rxHandle] = CanGetRxDataLen(rxHandle);
  }
#endif

#if defined( C_ENABLE_INDICATION_FLAG )
/* txHandle as loop variable is ok here, because the number of indication bytes is not as high as the number of Rx Messages */
  for (txHandle = 0; txHandle < kCanNumberOfIndBytes; txHandle++) {
    CanIndicationFlags._c[txHandle] = 0;
  }
#endif

#if defined( C_ENABLE_CONFIRMATION_FLAG )
  for (txHandle = 0; txHandle < kCanNumberOfConfBytes; txHandle++) {
    CanConfirmationFlags._c[txHandle] = 0;
  }
#endif

#if defined( C_ENABLE_RX_QUEUE )
  CanDeleteRxQueue();
#endif

#if defined( C_ENABLE_TRANSMIT_QUEUE )
#endif


#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  for (channel=0; channel<kCanNumberOfChannels; channel++)
#endif
  {

#if defined( C_ENABLE_CAN_RAM_CHECK )
    canComStatus[channel] = kCanEnableCommunication;
#endif
   
    canStatus[channel]              = kCanStatusInit;

    
    
    #if defined( C_ENABLE_UPDATE_BASE_ADDRESS )
    # if defined (C_MULTIPLE_RECEIVE_CHANNEL)
    canLL_VirtualPtrField[channel]     = (vuint32*)ApplCanPowerOnGetBaseAddress((vuint32)(CanHwChannelData[channel].CanBaseAddress), (sizeof(tFLEXCAN)+0x3ff+sizeof(tCanRxMask)));
    canLL_VirtualPtrFieldTemp[channel] = canLL_VirtualPtrField[channel];
    # else
    canLL_VirtualPtrField[0]     = (vuint32*)ApplCanPowerOnGetBaseAddress((vuint32)(C_TOUCAN_BASIS), (sizeof(tFLEXCAN)+0x3ff+sizeof(tCanRxMask)));
    canLL_VirtualPtrFieldTemp[0] = canLL_VirtualPtrField[0];
    # endif
    #endif /* QWRAP / MDWRAP */

#if defined( C_ENABLE_CAN_TX_CONF_FCT )
    txInfoStructConf[channel].Channel = channel;
#endif
#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )  || \
    defined( C_ENABLE_RX_BASICCAN_OBJECTS )
    canRxInfoStruct[channel].Channel  = channel;
#endif

#if defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL) && !defined (C_ENABLE_OSEK_CAN_INTCTRL)
    canCanInterruptCounter[channel] = 0; 
#endif

#if defined( C_ENABLE_TX_POLLING )          || \
      defined( C_ENABLE_RX_FULLCAN_POLLING )  || \
      defined( C_ENABLE_RX_BASICCAN_POLLING ) || \
      defined( C_ENABLE_ERROR_POLLING )       || \
      defined( C_ENABLE_WAKEUP_POLLING )      || \
      (defined( C_HL_ENABLE_CANCEL_IN_HW_TASK ) && defined( C_ENABLE_CANCEL_IN_HW ))
    canPollingTaskActive[channel] = 0;
#endif

#if defined( C_ENABLE_DYN_TX_OBJECTS )   && \
    defined( C_ENABLE_CONFIRMATION_FCT ) && \
    defined( C_ENABLE_TRANSMIT_QUEUE )
  /*  Reset dynamic transmission object management -------------------------- */
    confirmHandle[channel] = kCanBufferFree;
#endif

#if defined( C_ENABLE_TX_MASK_EXT_ID )
    canTxMask0[channel] = 0;
# if (kCanNumberOfUsedCanTxIdTables > 1)
    canTxMask1[channel] = 0;
# endif
# if (kCanNumberOfUsedCanTxIdTables > 2)
    canTxMask2[channel] = 0;
# endif
# if (kCanNumberOfUsedCanTxIdTables > 3)
    canTxMask3[channel] = 0;
# endif
# if (kCanNumberOfUsedCanTxIdTables > 4)
    canTxMask4[channel] = 0;
# endif
#endif

#if defined( C_ENABLE_ECU_SWITCH_PASS )
    canPassive[channel]             = 0;
#endif

#if defined( C_ENABLE_PART_OFFLINE )
    canTxPartOffline[channel]       = kCanTxPartInit;
#endif
#if defined( C_ENABLE_COND_RECEIVE_FCT )
    canMsgCondRecState[channel]     = kCanTrue;
#endif

    canRxHandle[channel] = kCanRxHandleNotUsed;

    {
#if defined( C_ENABLE_TRANSMIT_QUEUE )
  /* clear all Tx queue flags */
      CanDelQueuedObj( CAN_CHANNEL_CANPARA_ONLY );
#endif

      CanInit( CAN_CHANNEL_CANPARA_FIRST 0 );

      /* canStatus is only set to init and online, if CanInit() is called for this channel. */
      canStatus[channel]              |= (kCanHwIsInit | kCanTxOn);
    }

  }

} /* END OF CanInitPowerOn */
/* CODE CATEGORY 4 END */

#if defined( C_ENABLE_TRANSMIT_QUEUE )
/* **********************************************************************
* NAME:               CanDelQueuedObj
* CALLED BY:          
* PRECONDITIONS:      
* PARAMETER:          notify: if set to 1 for every deleted obj the appl is notified
* RETURN VALUE:       -
* DESCRIPTION:        Resets the bits with are set to 0 in mask
*                     Clearing the Transmit-queue
*********************************************************************** */
/* CODE CATEGORY 4 START */
static void CanDelQueuedObj( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3
{ 
  CanSignedTxHandle     queueElementIdx;
  #if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
  CanSignedTxHandle     elementBitIdx;
  CanTransmitHandle     txHandle;
  tCanQueueElementType  elem;
  #endif

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(channel < kCanNumberOfChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);    /* PRQA S 3109 */
# endif

  #  if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
  if((canStatus[channel] & kCanHwIsInit) == kCanHwIsInit)
  {
    CAN_CAN_INTERRUPT_DISABLE(CAN_CHANNEL_CANPARA_ONLY);        /* avoid interruption by CanHL_TxConfirmation */
    for(queueElementIdx = CAN_HL_TXQUEUE_STARTINDEX(channel); queueElementIdx < CAN_HL_TXQUEUE_STOPINDEX(channel); queueElementIdx++)
    { 
      elem = canTxQueueFlags[queueElementIdx];
      if(elem != (tCanQueueElementType)0) /* is there any flag set in the queue element? */
      {
        /* iterate through all flags and notify application for every scheduled transmission */
        for(elementBitIdx = ((CanSignedTxHandle)1 << kCanTxQueueShift) - (CanSignedTxHandle)1; elementBitIdx >= (CanSignedTxHandle)0; elementBitIdx--)
        { 
          if( ( elem & CanShiftLookUp[elementBitIdx] ) != (tCanQueueElementType)0)
          { 
            txHandle = (CanTransmitHandle)((((CanTransmitHandle)queueElementIdx << kCanTxQueueShift) + (CanTransmitHandle)elementBitIdx) - CAN_HL_TXQUEUE_PADBITS(channel));  /* ESCAN00039235 */
            APPLCANCANCELNOTIFICATION(channel, txHandle);
          } 
        } 
        canTxQueueFlags[queueElementIdx] = (tCanQueueElementType)0;
      }
    } 
    CAN_CAN_INTERRUPT_RESTORE(CAN_CHANNEL_CANPARA_ONLY);
  } 
  else
  #  endif
  {
    for(queueElementIdx = CAN_HL_TXQUEUE_STARTINDEX(channel); queueElementIdx < CAN_HL_TXQUEUE_STOPINDEX(channel); queueElementIdx++)
    { 
      canTxQueueFlags[queueElementIdx] = (tCanQueueElementType)0;
    } 
  }

}
/* CODE CATEGORY 4 END */
#endif

#if defined( C_ENABLE_CAN_TRANSMIT )
# if defined( C_ENABLE_CAN_CANCEL_TRANSMIT )
/* CODE CATEGORY 3 START */
/* **************************************************************************
| NAME:             CanCancelTransmit
| CALLED BY:        Application
| PRECONDITIONS:    none
| INPUT PARAMETERS: Tx-Msg-Handle
| RETURN VALUES:    none
| DESCRIPTION:      delete on Msg-Object
************************************************************************** */
C_API_1 void C_API_2 CanCancelTransmit( CanTransmitHandle txHandle )
{
  CanDeclareGlobalInterruptOldStatus
  CAN_CHANNEL_CANTYPE_LOCAL 
  CanObjectHandle        logTxObjHandle;
  /* ##RI1.4 - 1.6: CanCancelTransmit and CanCancelMsgTransmit */
#  if defined( C_ENABLE_CANCEL_IN_HW )
  CanObjectHandle        txObjHandle;
#  endif

# if defined( C_ENABLE_TRANSMIT_QUEUE )
  CanSignedTxHandle queueElementIdx; /* index for accessing the tx queue */
  CanSignedTxHandle elementBitIdx;  /* bit index within the tx queue element */
  CanTransmitHandle queueBitPos;  /* physical bitposition of the handle */
# endif

  if (txHandle < kCanNumberOfTxObjects)         /* legal txHandle ? */
  {
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
    channel = CanGetChannelOfTxObj(txHandle);
# endif

# if defined( C_ENABLE_MULTI_ECU_PHYS )
    assertUser(((CanTxIdentityAssignment[txHandle] & V_ACTIVE_IDENTITY_MSK) != (tVIdentityMsk)0 ), channel, kErrorDisabledTxMessage);    /* PRQA S 3109 */
# endif

    CanNestedGlobalInterruptDisable();
# if defined( C_ENABLE_TRANSMIT_QUEUE )
    #if defined( C_ENABLE_INTERNAL_CHECK ) &&\
        defined( C_MULTIPLE_RECEIVE_CHANNEL )
    if (sizeof(queueBitPos) == 1)
    {
      assertInternal( ((vuint16)((vuint16)kCanNumberOfTxObjects + (vuint16)CanTxQueuePadBits[kCanNumberOfChannels-1]) <= 256u), kCanAllChannels, kErrorTxQueueTooManyHandle) /* PRQA S 3109 */ /*lint !e572 !e506*/
    }
    else
    {
      if (((sizeof(tCanTxQueuePadBits) == 1) && (kCanNumberOfTxObjects > (65536 - 256))) || (sizeof(tCanTxQueuePadBits) > 1))
      {
        assertInternal( ((vuint32)((vuint32)kCanNumberOfTxObjects + (vuint32)CanTxQueuePadBits[kCanNumberOfChannels-1]) <= 65536u), kCanAllChannels, kErrorTxQueueTooManyHandle) /* PRQA S 3109 */ /*lint !e572 !e506*/
      }  
    }
    #endif
    queueBitPos  = txHandle + CAN_HL_TXQUEUE_PADBITS(channel);
    queueElementIdx = (CanSignedTxHandle)(queueBitPos >> kCanTxQueueShift); /* get the queue element where to set the flag */
    elementBitIdx  = (CanSignedTxHandle)(queueBitPos & kCanTxQueueMask);   /* get the flag index wihtin the queue element */
    if( (canTxQueueFlags[queueElementIdx] & CanShiftLookUp[elementBitIdx]) != (tCanQueueElementType)0 )
    {
      canTxQueueFlags[queueElementIdx] &= (tCanQueueElementType)~CanShiftLookUp[elementBitIdx]; /* clear flag from the queue */
      APPLCANCANCELNOTIFICATION(channel, txHandle);
    }
# endif

# if defined( C_ENABLE_TX_FULLCAN_OBJECTS )
    logTxObjHandle = (CanObjectHandle)((vsintx)CanGetTxHwObj(txHandle) + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel));
# else
    logTxObjHandle = (CanObjectHandle)((vsintx)CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel) + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel));
# endif/* C_ENABLE_TX_FULLCAN_OBJECTS */
    if (canHandleCurTxObj[logTxObjHandle] == txHandle)
    {
      canHandleCurTxObj[logTxObjHandle] = kCanBufferCancel;

      /* ##RI1.4 - 1.6: CanCancelTransmit and CanCancelMsgTransmit */
# if defined( C_ENABLE_CANCEL_IN_HW )
#  if defined( C_ENABLE_TX_FULLCAN_OBJECTS )
      txObjHandle = CanGetTxHwObj(txHandle);
#  else
      txObjHandle = CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel);
#  endif /* C_ENABLE_TX_FULLCAN_OBJECTS */
      
      # if defined( C_ENABLE_TX_FULLCAN_DELAYED_START )
      /* Only fullcans are considered */
      if ( (txObjHandle != CAN_HW_TX_NORMAL_INDEX(canHwChannel))
      #  if defined ( C_ENABLE_MSG_TRANSMIT )
      && (txObjHandle != CAN_HL_HW_MSG_TRANSMIT_INDEX(canHwChannel))
      #  endif
      )
      {
        CanDeclareGlobalInterruptOldStatus
      
        /* Disable global interrupts */
        CanNestedGlobalInterruptDisable();
        /* Check whether the cancelled tx object has the internal delayed flag set,
           if yes -> the Tx is not requested yet (in HW) and the appropriate canHandleCurTxObj[logTxObjHandle] is set to kCanBufferCancel here
                     and it has to be not sent by CanTxFullCanDelayedStart()
           if no  -> the Tx is already requested - Tx or Abort acknowledge will come as usual */
        if (CanGetMailboxDelayed(channel, txObjHandle))
        { /* the Tx is not requested yet */
          /* Clear the pending Tx fullcan object from internal delayed Tx flags */
          CanClearMailboxDelayed(channel, txObjHandle);
          /* free the canHandleCurTxObj[logTxObjHandle]. This must be done here, because the Tx is not requested in HW and NO TxACK nor AbACK will come, where
             the semaphore would be freed */
          canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;
        }
        else
        {
          pFLEXCAN(canHwChannel)->canObject[txObjHandle].control = (vuint32)((pFLEXCAN(canHwChannel)->canObject[txObjHandle].control & kNotCodeMask) | kTxCodeAbort);
        }
      
        /* Enable global interrupts */
        CanNestedGlobalInterruptRestore();
      }
      else
      {
        pFLEXCAN(canHwChannel)->canObject[txObjHandle].control = (vuint32)((pFLEXCAN(canHwChannel)->canObject[txObjHandle].control & kNotCodeMask) | kTxCodeAbort);
      }
      # else /* C_ENABLE_TX_FULLCAN_DELAYED_START */
      pFLEXCAN(canHwChannel)->canObject[txObjHandle].control = (vuint32)((pFLEXCAN(canHwChannel)->canObject[txObjHandle].control & kNotCodeMask) | kTxCodeAbort);
      # endif /* C_ENABLE_TX_FULLCAN_DELAYED_START */
# endif /* C_ENABLE_CANCEL_IN_HW */
      APPLCANCANCELNOTIFICATION(channel, txHandle);
    }

    CanNestedGlobalInterruptRestore();
  } /* if (txHandle < kCanNumberOfTxObjects) */
}
/* CODE CATEGORY 3 END */
# endif /* defined( C_ENABLE_CAN_CANCEL_TRANSMIT ) */

#endif /* if defined( C_ENABLE_CAN_TRANSMIT ) */


#if defined( C_ENABLE_MSG_TRANSMIT_CONF_FCT )
/* **************************************************************************
| NAME:             CanCancelMsgTransmit
| CALLED BY:        Application
| PRECONDITIONS:    none
| INPUT PARAMETERS: none or channel
| RETURN VALUES:    none
| DESCRIPTION:      delete on Msg-Object
************************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 void C_API_2 CanCancelMsgTransmit( CAN_CHANNEL_CANTYPE_ONLY )
{
  CanDeclareGlobalInterruptOldStatus
  CanObjectHandle  logTxObjHandle;
# if defined( C_ENABLE_CANCEL_IN_HW )
  CanObjectHandle  txObjHandle;    /* ##RI1.4 - 1.6: CanCancelTransmit and CanCancelMsgTransmit */
# endif

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);    /* PRQA S 3109 */
# endif


  logTxObjHandle = (CanObjectHandle)((vsintx)CAN_HL_HW_MSG_TRANSMIT_INDEX(canHwChannel) + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel));

  CanNestedGlobalInterruptDisable();
  if (canHandleCurTxObj[logTxObjHandle] == kCanBufferMsgTransmit)
  {
    canHandleCurTxObj[logTxObjHandle] = kCanBufferCancel;

    /* ##RI1.4 - 1.6: CanCancelTransmit and CanCancelMsgTransmit */
# if defined( C_ENABLE_CANCEL_IN_HW )
    txObjHandle = CAN_HL_HW_MSG_TRANSMIT_INDEX(canHwChannel);
    
    # if defined( C_ENABLE_TX_FULLCAN_DELAYED_START )
    /* Only fullcans are considered */
    if ( (txObjHandle != CAN_HW_TX_NORMAL_INDEX(canHwChannel))
    #  if defined ( C_ENABLE_MSG_TRANSMIT )
    && (txObjHandle != CAN_HL_HW_MSG_TRANSMIT_INDEX(canHwChannel))
    #  endif
    )
    {
      CanDeclareGlobalInterruptOldStatus
    
      /* Disable global interrupts */
      CanNestedGlobalInterruptDisable();
      /* Check whether the cancelled tx object has the internal delayed flag set,
         if yes -> the Tx is not requested yet (in HW) and the appropriate canHandleCurTxObj[logTxObjHandle] is set to kCanBufferCancel here
                   and it has to be not sent by CanTxFullCanDelayedStart()
         if no  -> the Tx is already requested - Tx or Abort acknowledge will come as usual */
      if (CanGetMailboxDelayed(channel, txObjHandle))
      { /* the Tx is not requested yet */
        /* Clear the pending Tx fullcan object from internal delayed Tx flags */
        CanClearMailboxDelayed(channel, txObjHandle);
        /* free the canHandleCurTxObj[logTxObjHandle]. This must be done here, because the Tx is not requested in HW and NO TxACK nor AbACK will come, where
           the semaphore would be freed */
        canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;
      }
      else
      {
        pFLEXCAN(canHwChannel)->canObject[txObjHandle].control = (vuint32)((pFLEXCAN(canHwChannel)->canObject[txObjHandle].control & kNotCodeMask) | kTxCodeAbort);
      }
    
      /* Enable global interrupts */
      CanNestedGlobalInterruptRestore();
    }
    else
    {
      pFLEXCAN(canHwChannel)->canObject[txObjHandle].control = (vuint32)((pFLEXCAN(canHwChannel)->canObject[txObjHandle].control & kNotCodeMask) | kTxCodeAbort);
    }
    # else /* C_ENABLE_TX_FULLCAN_DELAYED_START */
    pFLEXCAN(canHwChannel)->canObject[txObjHandle].control = (vuint32)((pFLEXCAN(canHwChannel)->canObject[txObjHandle].control & kNotCodeMask) | kTxCodeAbort);
    # endif /* C_ENABLE_TX_FULLCAN_DELAYED_START */
# endif
    APPLCANMSGCANCELNOTIFICATION(channel);
  }
  CanNestedGlobalInterruptRestore();
}
/* CODE CATEGORY 3 END */
#endif


#if defined( C_ENABLE_CAN_TRANSMIT )
# if defined( C_ENABLE_VARIABLE_DLC )
/* CODE CATEGORY 2 START */
/* **************************************************************************
| NAME:             CanTransmitVarDLC
| CALLED BY:        Netmanagement, application
| PRECONDITIONS:    Can driver must be initialized
| INPUT PARAMETERS: Handle to Tx message, DLC of Tx message
| RETURN VALUES:    kCanTxFailed: transmit failed
|                   kCanTxOk    : transmit was succesful
| DESCRIPTION:      If the CAN driver is not ready for send, the application
|                   decide, whether the transmit request is repeated or not.
************************************************************************** */
C_API_1 vuint8 C_API_2 CanTransmitVarDLC(CanTransmitHandle txHandle, vuint8 dlc) C_API_3
{
  assertUser(dlc<(vuint8)9, kCanAllChannels, kErrorTxDlcTooLarge);         /* PRQA S 3109 */
  assertUser(txHandle<kCanNumberOfTxObjects, kCanAllChannels, kErrorTxHdlTooLarge);     /* PRQA S 3109 */

  canTxDLC_RAM[ txHandle ] = (canTxDLC_RAM[ txHandle ] & CanLL_DlcMask) | MK_TX_DLC(dlc);

  return CanTransmit( txHandle );
} /* END OF CanTransmitVarDLC */
/* CODE CATEGORY 2 END */
# endif   /* C_ENABLE_VARIABLE_DLC */

/* **************************************************************************
| NAME:             CanTransmit
| CALLED BY:        application
| PRECONDITIONS:    Can driver must be initialized
| INPUT PARAMETERS: Handle of the transmit object to be send
| RETURN VALUES:    kCanTxFailed: transmit failed
|                   kCanTxOk    : transmit was succesful
| DESCRIPTION:      If the CAN driver is not ready for send, the application
|                   decide, whether the transmit request is repeated or not.
************************************************************************** */
/* CODE CATEGORY 2 START */

C_API_1 vuint8 C_API_2 CanTransmit(CanTransmitHandle txHandle) C_API_3   /* lint !e14 !e31 */
{
  CanDeclareGlobalInterruptOldStatus

# if !defined( C_ENABLE_TX_POLLING )          ||\
     !defined( C_ENABLE_TRANSMIT_QUEUE )      ||\
     defined( C_ENABLE_TX_FULLCAN_OBJECTS )   ||\
     defined( C_ENABLE_INDIVIDUAL_POLLING )
  CanObjectHandle      txObjHandle;
  CanObjectHandle      logTxObjHandle;
  vuint8             rc;
# endif   /* ! C_ENABLE_TX_POLLING  || ! C_ENABLE_TRANSMIT_QUEUE || C_ENABLE_TX_FULLCAN_OBJECTS || C_ENABLE_INDIVIDUAL_POLLING */
  CAN_CHANNEL_CANTYPE_LOCAL

# if defined( C_ENABLE_TRANSMIT_QUEUE )
  CanSignedTxHandle queueElementIdx; /* index for accessing the tx queue */
  CanSignedTxHandle elementBitIdx;  /* bit index within the tx queue element */
  CanTransmitHandle queueBitPos;  /* physical bitposition of the handle */
# endif
  #if defined( C_ENABLE_ECU_SWITCH_PASS )
    
  # if !defined( C_ENABLE_TX_POLLING )         || \
       !defined( C_ENABLE_TRANSMIT_QUEUE )     || \
        defined( C_ENABLE_TX_FULLCAN_OBJECTS ) || \
        defined( C_ENABLE_INDIVIDUAL_POLLING ) 
  # else 
  /* txObjHandle allways required when passive mode is used */     
  CanObjectHandle  txObjHandle;
  # endif
  
  # if defined( C_ENABLE_TX_FULLCAN_OBJECTS )
  txObjHandle = CanGetTxHwObj(txHandle);
  # else
  #  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  txObjHandle = CAN_HW_TX_NORMAL_INDEX(CanGetChannelOfTxObj(txHandle) ); /*lint !e506 */
  #  else 
  txObjHandle = CAN_HW_TX_NORMAL_INDEX(canHwChannel); /*lint !e506 */
  #  endif
  # endif
  
  #endif /* defined( C_ENABLE_ECU_SWITCH_PASS ) */



  assertUser(txHandle<kCanNumberOfTxObjects, kCanAllChannels, kErrorTxHdlTooLarge);      /* PRQA S 3109 */

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  channel = CanGetChannelOfTxObj(txHandle);          /* lint !e661 */
# endif

# if defined( C_ENABLE_MULTI_ECU_PHYS )
  assertUser(((CanTxIdentityAssignment[txHandle] & V_ACTIVE_IDENTITY_MSK) != (tVIdentityMsk)0 ), channel, kErrorDisabledTxMessage);    /* PRQA S 3109 */
# endif

  /* test offline ---------------------------------------------------------- */
  if ( (canStatus[channel] & kCanTxOn) != kCanTxOn )           /* transmit path switched off */
  {
    return kCanTxFailed;
  }

# if defined( C_ENABLE_PART_OFFLINE )
  if ( (canTxPartOffline[channel] & CanTxSendMask[txHandle]) != (vuint8)0)   /* lint !e661 */ /* CAN off ? */
  {
    return (kCanTxPartOffline);
  }
# endif

# if defined( C_ENABLE_CAN_RAM_CHECK )
  if(canComStatus[channel] == kCanDisableCommunication)
  {
    return(kCanCommunicationDisabled);
  }
# endif

# if defined( C_ENABLE_SLEEP_WAKEUP )
  assertUser(!CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanSleep);    /* PRQA S 3109 */
# endif
  assertUser(!CanLL_HwIsStop(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanStop);      /* PRQA S 3109 */

  /* passive mode ---------------------------------------------------------- */
# if defined( C_ENABLE_ECU_SWITCH_PASS )
  if ( canPassive[channel] != (vuint8)0)                             /*  set passive ? */
  {
#  if defined( C_ENABLE_CAN_TX_CONF_FCT ) || \
      defined( C_ENABLE_CONFIRMATION_FCT )
    CAN_CAN_INTERRUPT_DISABLE(channel);      /* avoid CAN Rx interruption */
#  endif

#  if defined( C_ENABLE_CAN_TX_CONF_FCT )
/* ##RI-1.10 Common Callbackfunction in TxInterrupt */
    txInfoStructConf[channel].Handle  = txHandle;
    txInfoStructConf[channel].pChipData = (CanChipDataPtr)&(pFlexCAN(canHwChannel)->canObject[txObjHandle].data[0]);
    txInfoStructConf[channel].pChipMsgObj = (CanChipMsgPtr)&(pFlexCAN(canHwChannel)->canObject[txObjHandle].control);
    APPL_CAN_TX_CONFIRMATION(&txInfoStructConf[channel]);
#  endif

#  if defined( C_ENABLE_CONFIRMATION_FLAG )       /* set transmit ready flag  */
#   if C_SECURITY_LEVEL > 20
    CanNestedGlobalInterruptDisable();
#   endif
    CanConfirmationFlags._c[CanGetConfirmationOffset(txHandle)] |= CanGetConfirmationMask(txHandle);      /* lint !e661 */
#   if C_SECURITY_LEVEL > 20
    CanNestedGlobalInterruptRestore();
#   endif
#  endif

#  if defined( C_ENABLE_CONFIRMATION_FCT )
    {
#   if defined( C_HL_ENABLE_DUMMY_FCT_CALL )
#   else
      if ( CanGetApplConfirmationPtr(txHandle) != V_NULL )
#   endif
      {
         (CanGetApplConfirmationPtr(txHandle))(txHandle);   /* call completion routine  */
      }
    }
#  endif /* C_ENABLE_CONFIRMATION_FCT */

#  if defined( C_ENABLE_CAN_TX_CONF_FCT ) || \
      defined( C_ENABLE_CONFIRMATION_FCT )
    CAN_CAN_INTERRUPT_RESTORE(channel);
#  endif

    return kCanTxOk;
  }
# endif


   /* can transmit enabled ================================================== */

   /* ----------------------------------------------------------------------- */
   /* ---  transmit queue with one objects ---------------------------------- */
   /* ---  transmit using fullcan objects ----------------------------------- */
   /* ----------------------------------------------------------------------- */

#  if !defined( C_ENABLE_TX_POLLING )          ||\
      !defined( C_ENABLE_TRANSMIT_QUEUE )      ||\
      defined( C_ENABLE_TX_FULLCAN_OBJECTS )   ||\
      defined( C_ENABLE_INDIVIDUAL_POLLING )

#   if defined( C_ENABLE_TX_FULLCAN_OBJECTS )
  txObjHandle = CanGetTxHwObj(txHandle);    /* lint !e661 */
#   else
  txObjHandle = CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel);                                          /* msg in object 0 */
#   endif

  logTxObjHandle = (CanObjectHandle)((vsintx)txObjHandle + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel));
#  endif   /* ! C_ENABLE_TX_POLLING  || ! C_ENABLE_TRANSMIT_QUEUE || C_ENABLE_TX_FULLCAN_OBJECTS || C_ENABLE_INDIVIDUAL_POLLING */

  CanNestedGlobalInterruptDisable();
 
  /* test offline after interrupt disable ---------------------------------- */
  if ( (canStatus[channel] & kCanTxOn) != kCanTxOn )                /* transmit path switched off */
  {
    CanNestedGlobalInterruptRestore();
    return kCanTxFailed;
  }
  
  
# if defined( C_ENABLE_TRANSMIT_QUEUE )
#  if defined( C_ENABLE_TX_FULLCAN_OBJECTS )  ||\
      !defined( C_ENABLE_TX_POLLING )         ||\
      defined( C_ENABLE_INDIVIDUAL_POLLING )
  if (
#   if defined( C_ENABLE_TX_FULLCAN_OBJECTS )
       (txObjHandle == CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel))                                   /* disabled - lint !e774 */
#   endif
#   if defined( C_ENABLE_TX_FULLCAN_OBJECTS )  &&\
       ( !defined( C_ENABLE_TX_POLLING )         ||\
          defined( C_ENABLE_INDIVIDUAL_POLLING ) )
     &&
#   endif

#   if defined( C_ENABLE_TX_POLLING )
#    if defined( C_ENABLE_INDIVIDUAL_POLLING )
       ( ( CanHwObjIndivPolling[CAN_HWOBJINDIVPOLLING_INDEX0][txObjHandle] != (vuint8)0 )       /* Object is used in polling mode! */
                         || (canHandleCurTxObj[logTxObjHandle] != kCanBufferFree) )    /* MsgObj used?  */
#    else
        /* write always to queue; transmission is started out of TxTask */
#    endif
#   else
       ( canHandleCurTxObj[logTxObjHandle] != kCanBufferFree)    /* MsgObj used?  */
#   endif
     )
#  endif   /*  ( C_ENABLE_TX_FULLCAN_OBJECTS )  || !( C_ENABLE_TX_POLLING ) || ( C_ENABLE_INDIVIDUAL_POLLING ) */

    {
      /* tx object 0 used -> set msg in queue: ----------------------------- */
      queueBitPos  = txHandle + CAN_HL_TXQUEUE_PADBITS(channel);
      queueElementIdx = (CanSignedTxHandle)(queueBitPos >> kCanTxQueueShift); /* get the queue element where to set the flag */
      elementBitIdx  = (CanSignedTxHandle)(queueBitPos & kCanTxQueueMask);   /* get the flag index wihtin the queue element */
      canTxQueueFlags[queueElementIdx] |= CanShiftLookUp[elementBitIdx];
      CanNestedGlobalInterruptRestore();
      return kCanTxOk;                          
  }
# endif  /* C_ENABLE_TRANSMIT_QUEUE */

# if !defined( C_ENABLE_TX_POLLING )          ||\
     !defined( C_ENABLE_TRANSMIT_QUEUE )      ||\
     defined( C_ENABLE_TX_FULLCAN_OBJECTS )   ||\
     defined( C_ENABLE_INDIVIDUAL_POLLING )

#  if defined( C_ENABLE_TRANSMIT_QUEUE )    && \
      ( defined( C_ENABLE_TX_FULLCAN_OBJECTS )  ||\
        !defined( C_ENABLE_TX_POLLING )         ||\
        defined( C_ENABLE_INDIVIDUAL_POLLING )  )
  else
#  endif
  {
  /* check for transmit message object free --------------------------------- */
    if (( canHandleCurTxObj[logTxObjHandle] != kCanBufferFree)    /* MsgObj used?  */
       || ( !CanLL_TxIsHWObjFree( canHwChannel, txObjHandle ) )

      /* hareware-txObject is not free -------------------------------------- */
       )  /* end of if question */

    {  /* object used */
      /* tx object n used, quit with error */
      CanNestedGlobalInterruptRestore();
      return kCanTxFailed;
    }
  }

  /* Obj, pMsgObject points to is free, transmit msg object: ---------------- */
  canHandleCurTxObj[logTxObjHandle] = txHandle; /* Save hdl of msgObj to be transmitted */
  CanNestedGlobalInterruptRestore();

  rc = CanCopyDataAndStartTransmission( CAN_CHANNEL_CANPARA_FIRST txObjHandle, txHandle);

#  if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
  if ( rc == kCanTxNotify)
  {
    rc = kCanTxFailed;      /* ignore notification if calls of CanCopy.. is performed within CanTransmit */
  }
#  endif


  return(rc);

# else   /* ! C_ENABLE_TX_POLLING  || ! C_ENABLE_TRANSMIT_QUEUE || C_ENABLE_TX_FULLCAN_OBJECTS || C_ENABLE_INDIVIDUAL_POLLING */
# endif   /* ! C_ENABLE_TX_POLLING  || ! C_ENABLE_TRANSMIT_QUEUE || C_ENABLE_TX_FULLCAN_OBJECTS || C_ENABLE_INDIVIDUAL_POLLING */

} /* END OF CanTransmit */
/* CODE CATEGORY 2 END */


/* **************************************************************************
| NAME:             CanCopyDataAndStartTransmission
| CALLED BY:        CanTransmit, CanHl_RestartTxQueue and CanHL_TxConfirmation
| PRECONDITIONS:    - Can driver must be initialized
|                   - canTxCurHandle[logTxObjHandle] must be set
|                   - the hardwareObject (txObjHandle) must be free
| INPUT PARAMETERS: txHandle: Handle of the transmit object to be send
|                   txObjHandle:  Nr of the HardwareObjects to use
| RETURN VALUES:    kCanTxFailed: transmit failed
|                   kCanTxOk    : transmit was succesful
| DESCRIPTION:      If the CAN driver is not ready for send, the application
|                   decide, whether the transmit request is repeated or not.
************************************************************************** */
/* PRQA S 2001 End_CanCopyDataAndStartTransmission */    /* suppress misra message about usage of goto */
/* CODE CATEGORY 1 START */
static vuint8 CanCopyDataAndStartTransmission( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txObjHandle, CanTransmitHandle txHandle) C_API_3   /* lint !e14 !e31 */
{
   CanDeclareGlobalInterruptOldStatus
   vuint8             rc;
   CanObjectHandle      logTxObjHandle;
#  if defined( C_ENABLE_COPY_TX_DATA )  
   TxDataPtr   CanMemCopySrcPtr;
#  endif
# if defined( C_ENABLE_DYN_TX_OBJECTS )
   CanTransmitHandle    dynTxObj;
# endif /* C_ENABLE_DYN_TX_OBJECTS */
# if defined( C_ENABLE_PRETRANSMIT_FCT )
   CanTxInfoStruct      txStruct;
# endif

   #if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
   tFLEXCANPtr pFlexCANLocal;
   vuint32     canTxBuf[2];
   #else
   tFlexcanPtr pFlexCANLocal;
   #endif

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
   assertInternal(channel < kCanNumberOfChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);      /* PRQA S 3109 */
# endif
   assertInternal(txHandle < kCanNumberOfTxObjects, kCanAllChannels, kErrorInternalTxHdlTooLarge);        /* PRQA S 3109 */

# if defined( C_ENABLE_DYN_TX_OBJECTS )
#  if ( kCanNumberOfTxStatObjects == 0)
   dynTxObj = txHandle;               /* only dynamic messages are used */
#  else   /* ( kCanNumberOfTxStatObjects == 0) */
   /* dynamic and static messages are in the system */
   if (txHandle >= CAN_HL_TX_DYN_ROM_STARTINDEX(channel))
   {
     dynTxObj = (txHandle - CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) + CAN_HL_TX_DYN_RAM_STARTINDEX(channel);    /* PRQA S 3382, 0291 */
   }
   else
   {
     dynTxObj = kCanTxHandleNotUsed;
   }
#  endif /* ( kCanNumberOfTxStatObjects == 0) */
# endif /* C_ENABLE_DYN_TX_OBJECTS */

   assertInternal(txObjHandle < CAN_HL_HW_TX_STOPINDEX(canHwChannel), channel, kErrorTxObjHandleWrong);      /* PRQA S 3109 */
   logTxObjHandle = (CanObjectHandle)((vsintx)txObjHandle + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel));

   assertHardware( CanLL_TxIsHWObjFree( canHwChannel, txObjHandle ), channel, kErrorTxBufferBusy);          /* PRQA S 3109 */

   #if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
   pFlexCANLocal = pFLEXCAN(canHwChannel);
   #else
   pFlexCANLocal = pFlexCAN(canHwChannel);
   #endif

   /* set id and dlc  -------------------------------------------------------- */
   {
# if defined( C_ENABLE_DYN_TX_DLC ) || \
      defined( C_ENABLE_DYN_TX_ID )
     if (dynTxObj < kCanNumberOfTxDynObjects)
     {           /* set dynamic part of dynamic objects ---------------------- */
#  if defined( C_ENABLE_DYN_TX_ID )
        # if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
        #  if defined( C_ENABLE_EXTENDED_ID )
        pFlexCANLocal->canObject[txObjHandle].msgID = (vuint32)(canDynTxId0[dynTxObj]); /* SBSW_CAN_LL012 */
        #  else
        pFlexCANLocal->canObject[txObjHandle].msgID = (vuint32)(canDynTxId0[dynTxObj]) << 16; /* SBSW_CAN_LL012 */
        #  endif
        # else
        #  if defined( C_ENABLE_EXTENDED_ID )
        pFlexCANLocal->canObject[txObjHandle].msgIDH = (vuint16)((canDynTxId0[dynTxObj]) >> 16);  /* SBSW_CAN_LL012 */
        pFlexCANLocal->canObject[txObjHandle].msgIDL = (vuint16)(canDynTxId0[dynTxObj]); /* SBSW_CAN_LL012 */
        #  else
        pFlexCANLocal->canObject[txObjHandle].msgIDH = (vuint16)(canDynTxId0[dynTxObj]); /* SBSW_CAN_LL012 */
        #  endif
        # endif
#  endif
 
#  if defined( C_ENABLE_DYN_TX_DLC )
        #if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
        pFlexCANLocal->canObject[txObjHandle].control = (vuint32)((((vuint32)(canDynTxDLC[dynTxObj]) << 16) & kTxDlcMask) | kTxCodeINACTIVE); /* write IDE,SRR and DLC */ /* SBSW_CAN_LL012 */
        #else
        pFlexCANLocal->canObject[txObjHandle].control = (vuint16)(((vuint16)(canDynTxDLC[dynTxObj]) & kTxDlcMask) | kTxCodeINACTIVE); /* write IDE,SRR and DLC */ /* SBSW_CAN_LL012 */
        #endif
#  endif
     }
     else
     {          /* set part of static objects assocciated the dynamic -------- */
#  if defined( C_ENABLE_DYN_TX_ID )
#   if defined( C_ENABLE_TX_MASK_EXT_ID )
#    if defined( C_ENABLE_MIXED_ID )
        if (CanGetTxIdType(txHandle)==kCanIdTypeStd)
        {
          # if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
          #  if defined( C_ENABLE_EXTENDED_ID )
          pFlexCANLocal->canObject[txObjHandle].msgID = (vuint32)(CanGetTxId0(txHandle)); /* SBSW_CAN_LL012 */
          #  else
          pFlexCANLocal->canObject[txObjHandle].msgID = (vuint32)(CanGetTxId0(txHandle)) << 16; /* SBSW_CAN_LL012 */
          #  endif
          # else
          #  if defined( C_ENABLE_EXTENDED_ID )
          pFlexCANLocal->canObject[txObjHandle].msgIDH = (vuint16)((CanGetTxId0(txHandle)) >> 16);  /* SBSW_CAN_LL012 */
          pFlexCANLocal->canObject[txObjHandle].msgIDL = (vuint16)(CanGetTxId0(txHandle)); /* SBSW_CAN_LL012 */
          #  else
          pFlexCANLocal->canObject[txObjHandle].msgIDH = (vuint16)(CanGetTxId0(txHandle)); /* SBSW_CAN_LL012 */
          #  endif
          # endif
        }
        else
#    endif
        {
          /* mask extened ID */
          # if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
          #  if defined( C_ENABLE_EXTENDED_ID )
          pFlexCANLocal->canObject[txObjHandle].msgID = (vuint32)((CanGetTxId0(txHandle)|canTxMask0[channel])); /* SBSW_CAN_LL012 */
          #  else
          pFlexCANLocal->canObject[txObjHandle].msgID = (vuint32)((CanGetTxId0(txHandle)|canTxMask0[channel])) << 16; /* SBSW_CAN_LL012 */
          #  endif
          # else
          #  if defined( C_ENABLE_EXTENDED_ID )
          pFlexCANLocal->canObject[txObjHandle].msgIDH = (vuint16)(((CanGetTxId0(txHandle)|canTxMask0[channel])) >> 16);  /* SBSW_CAN_LL012 */
          pFlexCANLocal->canObject[txObjHandle].msgIDL = (vuint16)((CanGetTxId0(txHandle)|canTxMask0[channel])); /* SBSW_CAN_LL012 */
          #  else
          pFlexCANLocal->canObject[txObjHandle].msgIDH = (vuint16)((CanGetTxId0(txHandle)|canTxMask0[channel])); /* SBSW_CAN_LL012 */
          #  endif
          # endif
        }
#   else
        # if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
        #  if defined( C_ENABLE_EXTENDED_ID )
        pFlexCANLocal->canObject[txObjHandle].msgID = (vuint32)(CanGetTxId0(txHandle)); /* SBSW_CAN_LL012 */
        #  else
        pFlexCANLocal->canObject[txObjHandle].msgID = (vuint32)(CanGetTxId0(txHandle)) << 16; /* SBSW_CAN_LL012 */
        #  endif
        # else
        #  if defined( C_ENABLE_EXTENDED_ID )
        pFlexCANLocal->canObject[txObjHandle].msgIDH = (vuint16)((CanGetTxId0(txHandle)) >> 16);  /* SBSW_CAN_LL012 */
        pFlexCANLocal->canObject[txObjHandle].msgIDL = (vuint16)(CanGetTxId0(txHandle)); /* SBSW_CAN_LL012 */
        #  else
        pFlexCANLocal->canObject[txObjHandle].msgIDH = (vuint16)(CanGetTxId0(txHandle)); /* SBSW_CAN_LL012 */
        #  endif
        # endif
#   endif
#  endif

#  if defined( C_ENABLE_DYN_TX_DLC )
#   if defined( C_ENABLE_VARIABLE_DLC )
        /* init DLC, RAM */
        #if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
        pFlexCANLocal->canObject[txObjHandle].control = (vuint32)((((vuint32)(canTxDLC_RAM[txHandle]) << 16) & kTxDlcMask) | kTxCodeINACTIVE); /* write IDE,SRR and DLC */ /* SBSW_CAN_LL012 */
        #else
        pFlexCANLocal->canObject[txObjHandle].control = (vuint16)(((vuint16)(canTxDLC_RAM[txHandle]) & kTxDlcMask) | kTxCodeINACTIVE); /* write IDE,SRR and DLC */ /* SBSW_CAN_LL012 */
        #endif
#   else
        /* init DLC, ROM */
        #if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
        pFlexCANLocal->canObject[txObjHandle].control = (vuint32)((((vuint32)CanGetTxDlc(txHandle) << 16) & kTxDlcMask) | kTxCodeINACTIVE); /* write IDE,SRR and DLC */ /* SBSW_CAN_LL012 */
        #else
        pFlexCANLocal->canObject[txObjHandle].control = (vuint16)(((vuint16)CanGetTxDlc(txHandle) & kTxDlcMask) | kTxCodeINACTIVE); /* write IDE,SRR and DLC */ /* SBSW_CAN_LL012 */
        #endif
#   endif
#  endif
     }
# endif
     /* set static part commen for static and dynamic objects ---------------- */
# if defined( C_ENABLE_DYN_TX_ID )
# else
#  if defined( C_ENABLE_TX_MASK_EXT_ID )
#   if defined( C_ENABLE_MIXED_ID )
     if (CanGetTxIdType(txHandle)==kCanIdTypeStd)
     {
       # if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
       #  if defined( C_ENABLE_EXTENDED_ID )
       pFlexCANLocal->canObject[txObjHandle].msgID = (vuint32)(CanGetTxId0(txHandle)); /* SBSW_CAN_LL012 */
       #  else
       pFlexCANLocal->canObject[txObjHandle].msgID = (vuint32)(CanGetTxId0(txHandle)) << 16; /* SBSW_CAN_LL012 */
       #  endif
       # else
       #  if defined( C_ENABLE_EXTENDED_ID )
       pFlexCANLocal->canObject[txObjHandle].msgIDH = (vuint16)((CanGetTxId0(txHandle)) >> 16);  /* SBSW_CAN_LL012 */
       pFlexCANLocal->canObject[txObjHandle].msgIDL = (vuint16)(CanGetTxId0(txHandle)); /* SBSW_CAN_LL012 */
       #  else
       pFlexCANLocal->canObject[txObjHandle].msgIDH = (vuint16)(CanGetTxId0(txHandle)); /* SBSW_CAN_LL012 */
       #  endif
       # endif
     }
     else
#   endif
     {
       /* mask extened ID */
       # if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
       #  if defined( C_ENABLE_EXTENDED_ID )
       pFlexCANLocal->canObject[txObjHandle].msgID = (vuint32)((CanGetTxId0(txHandle)|canTxMask0[channel])); /* SBSW_CAN_LL012 */
       #  else
       pFlexCANLocal->canObject[txObjHandle].msgID = (vuint32)((CanGetTxId0(txHandle)|canTxMask0[channel])) << 16; /* SBSW_CAN_LL012 */
       #  endif
       # else
       #  if defined( C_ENABLE_EXTENDED_ID )
       pFlexCANLocal->canObject[txObjHandle].msgIDH = (vuint16)(((CanGetTxId0(txHandle)|canTxMask0[channel])) >> 16);  /* SBSW_CAN_LL012 */
       pFlexCANLocal->canObject[txObjHandle].msgIDL = (vuint16)((CanGetTxId0(txHandle)|canTxMask0[channel])); /* SBSW_CAN_LL012 */
       #  else
       pFlexCANLocal->canObject[txObjHandle].msgIDH = (vuint16)((CanGetTxId0(txHandle)|canTxMask0[channel])); /* SBSW_CAN_LL012 */
       #  endif
       # endif
     }
#  else
     # if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
     #  if defined( C_ENABLE_EXTENDED_ID )
     pFlexCANLocal->canObject[txObjHandle].msgID = (vuint32)(CanGetTxId0(txHandle)); /* SBSW_CAN_LL012 */
     #  else
     pFlexCANLocal->canObject[txObjHandle].msgID = (vuint32)(CanGetTxId0(txHandle)) << 16; /* SBSW_CAN_LL012 */
     #  endif
     # else
     #  if defined( C_ENABLE_EXTENDED_ID )
     pFlexCANLocal->canObject[txObjHandle].msgIDH = (vuint16)((CanGetTxId0(txHandle)) >> 16);  /* SBSW_CAN_LL012 */
     pFlexCANLocal->canObject[txObjHandle].msgIDL = (vuint16)(CanGetTxId0(txHandle)); /* SBSW_CAN_LL012 */
     #  else
     pFlexCANLocal->canObject[txObjHandle].msgIDH = (vuint16)(CanGetTxId0(txHandle)); /* SBSW_CAN_LL012 */
     #  endif
     # endif
#  endif
# endif
# if defined( C_ENABLE_DYN_TX_DLC )
# else
#  if defined( C_ENABLE_VARIABLE_DLC )
     /* init DLC, RAM */
     #if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
     pFlexCANLocal->canObject[txObjHandle].control = (vuint32)((((vuint32)(canTxDLC_RAM[txHandle]) << 16) & kTxDlcMask) | kTxCodeINACTIVE); /* write IDE,SRR and DLC */ /* SBSW_CAN_LL012 */
     #else
     pFlexCANLocal->canObject[txObjHandle].control = (vuint16)(((vuint16)(canTxDLC_RAM[txHandle]) & kTxDlcMask) | kTxCodeINACTIVE); /* write IDE,SRR and DLC */ /* SBSW_CAN_LL012 */
     #endif
#  else
     /* init DLC, ROM */
     #if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
     pFlexCANLocal->canObject[txObjHandle].control = (vuint32)((((vuint32)CanGetTxDlc(txHandle) << 16) & kTxDlcMask) | kTxCodeINACTIVE); /* write IDE,SRR and DLC */ /* SBSW_CAN_LL012 */
     #else
     pFlexCANLocal->canObject[txObjHandle].control = (vuint16)(((vuint16)CanGetTxDlc(txHandle) & kTxDlcMask) | kTxCodeINACTIVE); /* write IDE,SRR and DLC */ /* SBSW_CAN_LL012 */
     #endif
#  endif
# endif

# if defined( C_ENABLE_MIXED_ID )
#   if defined( C_ENABLE_DYN_TX_DLC ) || \
       defined( C_ENABLE_DYN_TX_ID )
     if (dynTxObj < kCanNumberOfTxDynObjects)
     {                      /* set dynamic part of dynamic objects */
#    if defined( C_ENABLE_DYN_TX_ID )
       #if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
       pFlexCANLocal->canObject[txObjHandle].control &= kNotIDEMask; /* clear IDE and SRR bit */ /* SBSW_CAN_LL012 */
       pFlexCANLocal->canObject[txObjHandle].control |= (vuint32)(canDynTxIdType[dynTxObj]) << 16; /* SBSW_CAN_LL012 */
       #else
       pFlexCANLocal->canObject[txObjHandle].control &= kNotIDEMask; /* clear IDE and SRR bit */ /* SBSW_CAN_LL012 */
       pFlexCANLocal->canObject[txObjHandle].control |= (vuint16)(canDynTxIdType[dynTxObj]); /* SBSW_CAN_LL012 */
       #endif
#    else
       #if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
       pFlexCANLocal->canObject[txObjHandle].control &= kNotIDEMask; /* clear IDE and SRR bit */ /* SBSW_CAN_LL012 */
       pFlexCANLocal->canObject[txObjHandle].control |= (vuint32)(CanGetTxIdType(txHandle)) << 16; /* SBSW_CAN_LL012 */
       #else
       pFlexCANLocal->canObject[txObjHandle].control &= kNotIDEMask; /* clear IDE and SRR bit */ /* SBSW_CAN_LL012 */
       pFlexCANLocal->canObject[txObjHandle].control |= (vuint16)(CanGetTxIdType(txHandle)); /* SBSW_CAN_LL012 */
       #endif
#    endif
     }
#   else
#   endif
# endif

   }


 /* call pretransmit function ----------------------------------------------- */
# if defined( C_ENABLE_PRETRANSMIT_FCT )

   /* pointer needed for other modules */
   
   /* get pointer to DLC and ID field in message object */
   txStruct.pChipMsgObj = (CanChipMsgPtr)&(pFlexCANLocal->canObject[txObjHandle].control);
   /* get pointer to datafield in message object */
   #if defined( C_CPUTYPE_BIGENDIAN )
   (txStruct.pChipData) = (CanChipDataPtr)&(pFlexCANLocal->canObject[txObjHandle].data[0]);
   #endif
   
   
   
   canRDSTxPtr[logTxObjHandle] = txStruct.pChipData;
   txStruct.Handle      = txHandle;

   {  
#  if defined( C_HL_ENABLE_DUMMY_FCT_CALL )
#  else
    /* Is there a PreTransmit function ? ------------------------------------- */ 
    if ( CanGetApplPreTransmitPtr(txHandle) != V_NULL )    /* if PreTransmit exists */ 
#  endif
    { 
      if ( (CanGetApplPreTransmitPtr(txHandle)) (txStruct) == kCanNoCopyData)  
      { 
      
        # if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
        #  if defined( C_CPUTYPE_BIGENDIAN )
        ((vuint8*)canTxBuf)[0] = txStruct.pChipData[0];
        ((vuint8*)canTxBuf)[1] = txStruct.pChipData[1];
        ((vuint8*)canTxBuf)[2] = txStruct.pChipData[2];
        ((vuint8*)canTxBuf)[3] = txStruct.pChipData[3];
        ((vuint8*)canTxBuf)[4] = txStruct.pChipData[4];
        ((vuint8*)canTxBuf)[5] = txStruct.pChipData[5];
        ((vuint8*)canTxBuf)[6] = txStruct.pChipData[6];
        ((vuint8*)canTxBuf)[7] = txStruct.pChipData[7];
        #  endif
        pFlexCANLocal->canObject[txObjHandle].data[0] = canTxBuf[0];
        pFlexCANLocal->canObject[txObjHandle].data[1] = canTxBuf[1];
        # else
        #  if defined( C_CPUTYPE_BIGENDIAN )
        pFlexCANLocal->canObject[txObjHandle].data[0] = txStruct.pChipData[0];
        pFlexCANLocal->canObject[txObjHandle].data[1] = txStruct.pChipData[1];        
        pFlexCANLocal->canObject[txObjHandle].data[2] = txStruct.pChipData[2];        
        pFlexCANLocal->canObject[txObjHandle].data[3] = txStruct.pChipData[3];                
        pFlexCANLocal->canObject[txObjHandle].data[4] = txStruct.pChipData[4];        
        pFlexCANLocal->canObject[txObjHandle].data[5] = txStruct.pChipData[5];        
        pFlexCANLocal->canObject[txObjHandle].data[6] = txStruct.pChipData[6];        
        pFlexCANLocal->canObject[txObjHandle].data[7] = txStruct.pChipData[7];
        #  endif
        # endif
        
        /* Do not copy the data - already done by the PreTransmit-function */  
        /* --- start transmission --- */  
        goto startTransmission; 
      } 
    } 
   }  
# endif /* C_ENABLE_PRETRANSMIT_FCT */

 /* copy data --------------------------------------------------------------- */
# if defined( C_ENABLE_COPY_TX_DATA )  
#  if defined( C_ENABLE_DYN_TX_DATAPTR )  
   if (dynTxObj < kCanNumberOfTxDynObjects)  
   {  
      CanMemCopySrcPtr = canDynTxDataPtr[dynTxObj];  
   }  
   else  
#  endif  
   {  
     CanMemCopySrcPtr = CanGetTxDataPtr(txHandle);  
   }  
 /* copy via index in MsgObj data field, copy always 8 bytes ----------- */  
   if ( CanMemCopySrcPtr != V_NULL )   /* copy if buffer exists */
   {
#  if C_SECURITY_LEVEL > 10
     CanNestedGlobalInterruptDisable();  
#  endif

     /* copy data into tx message object */
     # if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
     #  if defined( C_CPUTYPE_BIGENDIAN )
     ((vuint8*)canTxBuf)[0] = CanMemCopySrcPtr[0];
     ((vuint8*)canTxBuf)[1] = CanMemCopySrcPtr[1];
     ((vuint8*)canTxBuf)[2] = CanMemCopySrcPtr[2];
     ((vuint8*)canTxBuf)[3] = CanMemCopySrcPtr[3];
     ((vuint8*)canTxBuf)[4] = CanMemCopySrcPtr[4];
     ((vuint8*)canTxBuf)[5] = CanMemCopySrcPtr[5];
     ((vuint8*)canTxBuf)[6] = CanMemCopySrcPtr[6];
     ((vuint8*)canTxBuf)[7] = CanMemCopySrcPtr[7];
     #  endif
     pFlexCANLocal->canObject[txObjHandle].data[0] = canTxBuf[0]; /* SBSW_CAN_LL012 */
     pFlexCANLocal->canObject[txObjHandle].data[1] = canTxBuf[1]; /* SBSW_CAN_LL012 */
     # else
     #  if defined( C_CPUTYPE_BIGENDIAN )
     pFlexCANLocal->canObject[txObjHandle].data[0] = CanMemCopySrcPtr[0]; /* SBSW_CAN_LL012 */
     pFlexCANLocal->canObject[txObjHandle].data[1] = CanMemCopySrcPtr[1]; /* SBSW_CAN_LL012 */
     pFlexCANLocal->canObject[txObjHandle].data[2] = CanMemCopySrcPtr[2]; /* SBSW_CAN_LL012 */
     pFlexCANLocal->canObject[txObjHandle].data[3] = CanMemCopySrcPtr[3]; /* SBSW_CAN_LL012 */
     pFlexCANLocal->canObject[txObjHandle].data[4] = CanMemCopySrcPtr[4]; /* SBSW_CAN_LL012 */
     pFlexCANLocal->canObject[txObjHandle].data[5] = CanMemCopySrcPtr[5]; /* SBSW_CAN_LL012 */
     pFlexCANLocal->canObject[txObjHandle].data[6] = CanMemCopySrcPtr[6]; /* SBSW_CAN_LL012 */
     pFlexCANLocal->canObject[txObjHandle].data[7] = CanMemCopySrcPtr[7]; /* SBSW_CAN_LL012 */
     #  endif
     # endif /* C_ENABLE_FLEXCAN_32BIT_ACCESS */

#  if C_SECURITY_LEVEL > 10
     CanNestedGlobalInterruptRestore();  
#  endif
   }
# endif /* ( C_ENABLE_COPY_TX_DATA ) */  

   CANDRV_SET_CODE_TEST_POINT(0x10A);

# if defined( C_ENABLE_PRETRANSMIT_FCT )
/* Msg(4:2015) This label is not a case or default label for a switch statement. MISRA Rule 55 */
startTransmission:
# endif

   /* test offline and handle and start transmission ------------------------ */
   CanNestedGlobalInterruptDisable();  
   /* If CanTransmit was interrupted by a re-initialization or CanOffline */  
   /* no transmitrequest of this action should be started      */  
   if ((canHandleCurTxObj[logTxObjHandle] == txHandle) && ((canStatus[channel] & kCanTxOn) == kCanTxOn))
   {  
     
     # if defined (C_ENABLE_TX_FULLCAN_DELAYED_START)
     /* if transmission request is a Tx FullCAN - store transmit request */
     if (txObjHandle != CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel))
     { 
       CanSetMailboxDelayed(channel, txObjHandle);
     }
     else
     /* if transmission request is a Tx Normal - send as usual */
     # endif /* C_ENABLE_TX_FULLCAN_DELAYED_START */
     {
       pFlexCANLocal->canObject[txObjHandle].control |= kTxCodeTransmit; /* start tx of the message */ /* SBSW_CAN_LL012 */
     }
     

# if defined( C_ENABLE_TX_OBSERVE )
     ApplCanTxObjStart( CAN_CHANNEL_CANPARA_FIRST logTxObjHandle );
# endif
     rc = kCanTxOk;                                    
   }  
   else  
   {  
# if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
     if (canHandleCurTxObj[logTxObjHandle] == txHandle)
     {
       /* only CanOffline was called on higher level */
       rc = kCanTxNotify;
     }
     else
# endif
     {
       rc = kCanTxFailed;   
     }
     assertInternal((canHandleCurTxObj[logTxObjHandle] == txHandle) || (canHandleCurTxObj[logTxObjHandle] == kCanBufferFree),
                                                                                       channel, kErrorTxHandleWrong);  /* PRQA S 3109 */
     canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;  /* release TxHandle (CanOffline) */
   }  

   CanNestedGlobalInterruptRestore();

   
   return (rc);   

} /* END OF CanCopyDataAndStartTransmission */
/* CODE CATEGORY 1 END */
/* PRQA L:End_CanCopyDataAndStartTransmission */





#endif /* if defined( C_ENABLE_CAN_TRANSMIT ) */


#if defined( C_ENABLE_TX_POLLING ) || \
    defined( C_ENABLE_RX_FULLCAN_POLLING )  || \
    defined( C_ENABLE_RX_BASICCAN_POLLING ) || \
    defined( C_ENABLE_ERROR_POLLING ) || \
    defined( C_ENABLE_WAKEUP_POLLING ) || \
    (defined( C_HL_ENABLE_CANCEL_IN_HW_TASK ) && defined( C_ENABLE_CANCEL_IN_HW ))
/* **************************************************************************
| NAME:             CanTask
| CALLED BY:        application
| PRECONDITIONS:
| INPUT PARAMETERS: none 
| RETURN VALUES:    none
| DESCRIPTION:      - cyclic Task, 
|                   - polling error bus off
|                   - polling Tx objects
|                   - polling Rx objects
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanTask(void)
{
  CAN_CHANNEL_CANTYPE_LOCAL

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  for (channel = 0; channel < kCanNumberOfChannels; channel++)
# endif
  {
    {
# if defined( C_ENABLE_ERROR_POLLING )
      CanErrorTask(CAN_CHANNEL_CANPARA_ONLY);
# endif

# if defined( C_ENABLE_SLEEP_WAKEUP )
#  if defined( C_ENABLE_WAKEUP_POLLING )
      CanWakeUpTask(CAN_CHANNEL_CANPARA_ONLY);
#  endif
# endif

# if defined( C_ENABLE_TX_POLLING ) || \
     (defined( C_HL_ENABLE_CANCEL_IN_HW_TASK )  && defined( C_ENABLE_CANCEL_IN_HW ))
      CanTxTask(CAN_CHANNEL_CANPARA_ONLY);
# endif

# if defined( C_ENABLE_RX_FULLCAN_POLLING ) && \
     defined( C_ENABLE_RX_FULLCAN_OBJECTS )
      CanRxFullCANTask(CAN_CHANNEL_CANPARA_ONLY);
# endif

# if defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && \
    defined( C_ENABLE_RX_BASICCAN_POLLING )
      CanRxBasicCANTask(CAN_CHANNEL_CANPARA_ONLY);
# endif
    }
  }
}
/* CODE CATEGORY 2 END */
#endif

#if defined( C_ENABLE_ERROR_POLLING )
/* **************************************************************************
| NAME:             CanErrorTask
| CALLED BY:        application
| PRECONDITIONS:
| INPUT PARAMETERS: none 
| RETURN VALUES:    none
| DESCRIPTION:      - cyclic Task, 
|                   - polling error status
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanErrorTask( CAN_CHANNEL_CANTYPE_ONLY )
{

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);    /* PRQA S 3109 */
# endif
  assertUser((canPollingTaskActive[channel] == (vuint8)0), channel, kErrorPollingTaskRecursion);     /* PRQA S 3109 */

  if (canPollingTaskActive[channel] == (vuint8)0)  /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1;

    {
# if defined( C_ENABLE_SLEEP_WAKEUP )
      if ( !CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY))
# endif
      {
        CAN_CAN_INTERRUPT_DISABLE(channel);
        CanHL_ErrorHandling(CAN_HW_CHANNEL_CANPARA_ONLY);
        CAN_CAN_INTERRUPT_RESTORE(channel);
      }
    }

    canPollingTaskActive[channel] = 0;
  }
}
/* CODE CATEGORY 2 END */
#endif

#if defined( C_ENABLE_SLEEP_WAKEUP )
# if defined( C_ENABLE_WAKEUP_POLLING )
/* **************************************************************************
| NAME:             CanWakeUpTask
| CALLED BY:        application
| PRECONDITIONS:
| INPUT PARAMETERS: none 
| RETURN VALUES:    none
| DESCRIPTION:      - cyclic Task, 
|                   - polling CAN wakeup event
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanWakeUpTask(CAN_CHANNEL_CANTYPE_ONLY)
{
  CanDeclareGlobalInterruptOldStatus

#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);     /* PRQA S 3109 */
#  endif
  assertUser((canPollingTaskActive[channel] == (vuint8)0), channel, kErrorPollingTaskRecursion);    /* PRQA S 3109 */

  if (canPollingTaskActive[channel] == (vuint8)0)  /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1;

    if((pFlexCAN(canHwChannel)->estat & kFlexCAN_WAKE_INT) != 0)
    {
      CANDRV_SET_CODE_TEST_POINT(0x111);
      CanNestedGlobalInterruptDisable();          /* ESCAN00021223 */
      CanLL_WakeUpHandling(CAN_CHANNEL_CANPARA_ONLY);
      CanNestedGlobalInterruptRestore();          /* ESCAN00021223 */
    }
    canPollingTaskActive[channel] = 0;
  }
}
/* CODE CATEGORY 2 END */
# endif /* C_ENABLE_WAKEUP_POLLING */
#endif /* C_ENABLE_SLEEP_WAKEUP */

#if defined( C_ENABLE_TX_POLLING ) || \
    (defined( C_HL_ENABLE_CANCEL_IN_HW_TASK )  && defined( C_ENABLE_CANCEL_IN_HW ))
/* **************************************************************************
| NAME:             CanTxTask
| CALLED BY:        application
| PRECONDITIONS:
| INPUT PARAMETERS: none 
| RETURN VALUES:    none
| DESCRIPTION:      - cyclic Task, 
|                   - polling Tx objects
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanTxTask( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3
{
  CanObjectHandle      txObjHandle;

  vuint32     iFlags;
  tFlexcanPtr pFlexCANLocal;


# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);    /* PRQA S 3109 */
# endif
  assertUser((canPollingTaskActive[channel] == (vuint8)0), channel, kErrorPollingTaskRecursion);    /* PRQA S 3109 */

  if (canPollingTaskActive[channel] == (vuint8)0)  /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1;


# if defined( C_ENABLE_SLEEP_WAKEUP )
    if ( !CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY))
# endif
    {
      /* --  polling Tx objects ---------------------------------------- */

# if defined( C_ENABLE_TX_POLLING )
      /* check for global confirmation Pending and may be reset global pending confirmation */
      pFlexCANLocal = pFlexCAN(canHwChannel);
      CAN_CAN_INTERRUPT_DISABLE(channel); /* SBSW_CAN_LL014 */
      #if defined( C_CAN_MAX_BUFFER_32 ) || defined( C_CAN_MAX_BUFFER_MIXED )
      # if defined( C_CAN_MAX_BUFFER_MIXED )
      if(CAN_HW_TX_STOPINDEX(canHwChannel) == 32)
      # endif
      {
        iFlags = pFlexCANLocal->iflag_lo & CAN_TX_POLL_MASK_LO(canHwChannel);
        #if defined( C_ENABLE_MSG_TRANSMIT )  
        if((iFlags & CanBitMask(30)) != 0)
        {
          CANDRV_SET_CODE_TEST_POINT(0x110);
          CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST 30);      
          iFlags = pFlexCANLocal->iflag_lo & CAN_TX_POLL_MASK_LO(canHwChannel);
        }
        #endif  
        if((iFlags & CanBitMask(31)) != 0)
        {
          CANDRV_SET_CODE_TEST_POINT(0x110);
          CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST 31); /* SBSW_CAN_LL009 */
        }      
      }
      #endif
      
      #if defined( C_ENABLE_MAX_BUFFER_64 )
      # if defined( C_CAN_MAX_BUFFER_MIXED )
      if(CAN_HW_TX_STOPINDEX(canHwChannel) == 64)
      # endif
      {
        iFlags = pFlexCANLocal->iflag_hi & CAN_TX_POLL_MASK_HI(canHwChannel);
        #if defined( C_ENABLE_MSG_TRANSMIT )  
        if((iFlags & CanBitMask(62)) != 0)
        {
          CANDRV_SET_CODE_TEST_POINT(0x110);
          CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST 62);      
          iFlags = pFlexCANLocal->iflag_hi & CAN_TX_POLL_MASK_HI(canHwChannel);
        }
        #endif  
        if((iFlags & CanBitMask(63)) != 0)
        {
          CANDRV_SET_CODE_TEST_POINT(0x110);
          CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST 63);
        }  
      }
      #endif
      CAN_CAN_INTERRUPT_RESTORE(channel); /* SBSW_CAN_LL014 */
      
      iFlags = pFlexCANLocal->iflag_lo & CAN_TX_POLL_MASK_LO(canHwChannel);
      #if defined( C_ENABLE_MAX_BUFFER_64 )
      # if defined( C_CAN_MAX_BUFFER_MIXED )
      if (CanMaxMB[canHwChannel] == 64)
      # endif
      {
        iFlags |= pFlexCANLocal->iflag_hi & CAN_TX_POLL_MASK_HI(canHwChannel);
      }
      #endif
      if(iFlags != 0)
      {
        for ( txObjHandle = CAN_HL_HW_TX_STARTINDEX(canHwChannel); txObjHandle < CAN_HL_HW_TX_STOPINDEX(canHwChannel); txObjHandle++ )
        {
#  if defined( C_ENABLE_INDIVIDUAL_POLLING )
          if ( CanHwObjIndivPolling[CAN_HWOBJINDIVPOLLING_INDEX0][txObjHandle] != (vuint8)0 )
#  endif
          {
            /* check for dedicated confirmation pending */
            pFlexCANLocal = pFlexCAN(canHwChannel);
            #if defined( C_ENABLE_MAX_BUFFER_64 )
            if(txObjHandle > (vuint16)31)
            {
              iFlags = pFlexCANLocal->iflag_hi;
            }
            else      
            #endif
            {
              iFlags = pFlexCANLocal->iflag_lo; 
            }
            if((iFlags & CanBitMask(txObjHandle)) != 0)
            {
              CANDRV_SET_CODE_TEST_POINT(0x110);
              CAN_CAN_INTERRUPT_DISABLE(channel);
              /* do tx confirmation */
              CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST txObjHandle );
              CAN_CAN_INTERRUPT_RESTORE(channel);
            }
          } /* if individual polling & object has to be polled */
        }
      }
# endif /* ( C_ENABLE_TX_POLLING ) */

# if defined( C_ENABLE_CANCEL_IN_HW ) && \
          defined( C_HL_ENABLE_CANCEL_IN_HW_TASK )
      /* search for pending cancelation */
    
      for ( txObjHandle = CAN_HL_HW_TX_STARTINDEX(canHwChannel); txObjHandle < CAN_HL_HW_TX_STOPINDEX(canHwChannel); txObjHandle++ )
      {
        /* check for dedicated cancel pending */
        pFlexCANLocal = pFlexCAN(canHwChannel);
        /* conditions for detecting successful cancel transmit */
        /* 1) code register of the tx message buffer must be 0x08 */
        /* 2) interrupt pending flag of the tx message buffer must be 0 */
        /* 3) canHandleCurTxObj[(vsintx)txObjHandle+CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel)] must be kCanBufferCancel */
        #if defined( C_ENABLE_MAX_BUFFER_64 )
        if(txObjHandle > 31)
        {
          #if defined( C_CAN_MAX_BUFFER_MIXED )
          assertHardware((CanMaxMB[canHwChannel] == 64), canHwChannel, kCanInvalidHwObjHandle);
          #endif 
          iFlags = pFlexCANLocal->iflag_hi & CanBitMask(txObjHandle);
        }
        else
        #endif
        {
          iFlags = pFlexCANLocal->iflag_lo & CanBitMask(txObjHandle);
        }        
                
        if((CanLL_TxIsHWObjFree(canHwChannel, txObjHandle)) && (iFlags == 0) && (canHandleCurTxObj[(vsintx)txObjHandle+CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel)] == kCanBufferCancel))
        {
          canHandleCurTxObj[(vsintx)txObjHandle+ CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel)] = kCanBufferFree;     /* release the hardware buffer */
        }
      }
# endif

# if defined( C_ENABLE_TRANSMIT_QUEUE )
      CanHl_RestartTxQueue( CAN_CHANNEL_CANPARA_ONLY );
# endif /*  C_ENABLE_TRANSMIT_QUEUE */

    } /* if ( CanLL_HwIsSleep... ) */

    canPollingTaskActive[channel] = 0;
  }


} /* END OF CanTxTask */
/* CODE CATEGORY 2 END */
#endif /* C_ENABLE_TX_POLLING */

#if defined( C_ENABLE_TRANSMIT_QUEUE )
# if defined( C_ENABLE_TX_POLLING ) || \
     (defined( C_HL_ENABLE_CANCEL_IN_HW_TASK )  && defined( C_ENABLE_CANCEL_IN_HW ))
/* **************************************************************************
| NAME:             CanHl_RestartTxQueue
| CALLED BY:        CanTxTask, via CanLL (TxMsgDestroyed)
| PRECONDITIONS:
| INPUT PARAMETERS: none 
| RETURN VALUES:    none
| DESCRIPTION:      start transmission if queue entry exists and HW is free
************************************************************************** */
/* CODE CATEGORY 2 START */
static void CanHl_RestartTxQueue( CAN_CHANNEL_CANTYPE_ONLY )
{
  CanTransmitHandle    txHandle;
#  if  defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
  vuint8             rc;
#  endif
  CanDeclareGlobalInterruptOldStatus

  CanSignedTxHandle         queueElementIdx;    /* use as signed due to loop */
  CanSignedTxHandle         elementBitIdx;
  tCanQueueElementType             elem;

#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(channel < kCanNumberOfChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);      /* PRQA S 3109 */
#  endif


  if (canHandleCurTxObj[(vsintx)CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel) + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel)] == kCanBufferFree)
  {
    for(queueElementIdx = CAN_HL_TXQUEUE_STOPINDEX(channel) - (CanSignedTxHandle)1; 
                             queueElementIdx >= CAN_HL_TXQUEUE_STARTINDEX(channel); queueElementIdx--)
    {
      elem = canTxQueueFlags[queueElementIdx];
      if(elem != (tCanQueueElementType)0) /* is there any flag set in the queue element? */
      {

        /* Transmit Queued Objects */
        /* start the bitsearch */
        #if defined( C_CPUTYPE_32BIT )
        if((elem & (tCanQueueElementType)0xFFFF0000) != (tCanQueueElementType)0)
        {
          if((elem & (tCanQueueElementType)0xFF000000) != (tCanQueueElementType)0)
          {
            if((elem & (tCanQueueElementType)0xF0000000) != (tCanQueueElementType)0)
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 28] + 28;
            }
            else /* 0x0F000000 */
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 24] + 24;
            }
          }
          else
          {
            if((elem & (tCanQueueElementType)0x00F00000) != (tCanQueueElementType)0)
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 20] + 20;
            }
            else /* 0x000F0000 */
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 16] + 16;
            }
          }
        }
        else
        #endif
        {
        #if defined( C_CPUTYPE_32BIT ) 
          if((elem & (tCanQueueElementType)0x0000FF00) != (tCanQueueElementType)0)
          {
            if((elem & (tCanQueueElementType)0x0000F000) != (tCanQueueElementType)0)
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 12] + 12;
            }
            else /* 0x00000F00 */
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 8] + 8;
            }
          }
          else
        #endif
          {
            if((elem & (tCanQueueElementType)0x000000F0) != (tCanQueueElementType)0)
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 4] + 4;
            }
            else /* 0x0000000F */
            {
              elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem];
            }
          }
        }
        txHandle = (CanTransmitHandle)((((CanTransmitHandle)queueElementIdx << kCanTxQueueShift) + (CanTransmitHandle)elementBitIdx) - CAN_HL_TXQUEUE_PADBITS(channel));
        {

            CanNestedGlobalInterruptDisable();
            if (canHandleCurTxObj[(vsintx)CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel) + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel)] == kCanBufferFree)
            {
              if ( (canTxQueueFlags[queueElementIdx] & CanShiftLookUp[elementBitIdx]) != (tCanQueueElementType)0 )
              {
                canTxQueueFlags[queueElementIdx] &= (tCanQueueElementType)~CanShiftLookUp[elementBitIdx]; /* clear flag from the queue */
                /* Save hdl of msgObj to be transmitted */
                canHandleCurTxObj[(vsintx)CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel) + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel)] = txHandle;
                CanNestedGlobalInterruptRestore();  
#  if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
                rc = CanCopyDataAndStartTransmission(CAN_CHANNEL_CANPARA_FIRST CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel), txHandle);
                if ( rc == kCanTxNotify)
                {
                  APPLCANCANCELNOTIFICATION(channel, txHandle);
                }
#  else
                (void)CanCopyDataAndStartTransmission(CAN_CHANNEL_CANPARA_FIRST CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel), txHandle);
#  endif
                return;
              }

            }
            CanNestedGlobalInterruptRestore();
            return;
        }
      }
    }
  }
} /* End of CanHl_RestartTxQueue */
/* CODE CATEGORY 2 END */
# endif
#endif /*  C_ENABLE_TRANSMIT_QUEUE */

#if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) && \
    defined( C_ENABLE_RX_FULLCAN_POLLING )  
/* **************************************************************************
| NAME:             CanRxFullCANTask
| CALLED BY:        application
| PRECONDITIONS:
| INPUT PARAMETERS: none 
| RETURN VALUES:    none
| DESCRIPTION:      - cyclic Task, 
|                   - polling Rx FullCAN objects
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxFullCANTask(CAN_CHANNEL_CANTYPE_ONLY) C_API_3
{
  vuint32     iFlags;
  tFlexcanPtr pFlexCANLocal;

  CanObjectHandle     rxObjHandle;        /* keyword register removed 2005-06-29 Ht */


# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);     /* PRQA S 3109 */
# endif
  assertUser((canPollingTaskActive[channel] == (vuint8)0), channel, kErrorPollingTaskRecursion);    /* PRQA S 3109 */

  if (canPollingTaskActive[channel] == (vuint8)0)  /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1;

    {
# if defined( C_ENABLE_SLEEP_WAKEUP )
      if ( !CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY))
# endif
      {
        /* --  polling fullcan Rx objects ---------------------------------------- */

        /* check for global fullCan Rx indication pending and may be reset global */
        /* indication pending */
        pFlexCANLocal = pFlexCAN(canHwChannel);
        iFlags = pFlexCANLocal->iflag_lo & CAN_RXFULL_POLL_MASK_LO(canHwChannel);
        # if defined( C_ENABLE_MAX_BUFFER_64 )
        #  if defined( C_CAN_MAX_BUFFER_MIXED )
        if (CanMaxMB[canHwChannel] == 64)
        #  endif
        {
          iFlags |= pFlexCANLocal->iflag_hi & CAN_RXFULL_POLL_MASK_HI(canHwChannel);
        }
        # endif
        
        if(iFlags != 0)
        {
          for(rxObjHandle=CAN_HW_RX_FULL_STARTINDEX(canHwChannel); rxObjHandle<CAN_HW_RX_FULL_STOPINDEX(canHwChannel); rxObjHandle++)
          {     
            #if defined( C_HL_ENABLE_ADJUST_RXHANDLE )
            if((rxObjHandle != 14) && (rxObjHandle != 15))
            #endif
            {
              #if defined( C_ENABLE_MAX_BUFFER_64 )
              if(rxObjHandle > (vuint16)31)
              {
                #if defined( C_ENABLE_INDIVIDUAL_POLLING )
                iFlags = pFlexCANLocal->iflag_hi & CAN_RXFULL_POLL_MASK_HI(canHwChannel);
                #else       
                iFlags = pFlexCANLocal->iflag_hi;
                #endif
              }
              else      
              #endif
              {
                #if defined( C_ENABLE_INDIVIDUAL_POLLING )
                iFlags = pFlexCANLocal->iflag_lo & CAN_RXFULL_POLL_MASK_LO(canHwChannel);
                #else
                iFlags = pFlexCANLocal->iflag_lo;
                #endif
              }                
              if((iFlags & CanBitMask(rxObjHandle)) != 0)
              {
                CANDRV_SET_CODE_TEST_POINT(0x109);
                CAN_CAN_INTERRUPT_DISABLE(channel);
                CanFullCanMsgReceived( CAN_HW_CHANNEL_CANPARA_FIRST rxObjHandle);
                CAN_CAN_INTERRUPT_RESTORE(channel);
              }
            }
          }  
          iFlags = 0;
        }
        
        if(iFlags != 0) /* PRQA S 3355,3359 */ /* MD_Can_13.7 */
        {
          for (rxObjHandle=CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel); rxObjHandle<CAN_HL_HW_RX_FULL_STOPINDEX(canHwChannel); rxObjHandle++ )
          {
# if defined( C_ENABLE_INDIVIDUAL_POLLING )
            if ( CanHwObjIndivPolling[CAN_HWOBJINDIVPOLLING_INDEX0][rxObjHandle] != (vuint8)0 )
# endif
            {
              /* check for dedicated indication pending */
              pFlexCANLocal = pFlexCAN(canHwChannel);
              #if defined( C_ENABLE_MAX_BUFFER_64 )
              if(rxObjHandle > (vuint16)31)
              {
                #if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
                iFlags = pFlexCANLocal->iflag_hi;
                #endif
              }
              else      
              #endif
              {
                #if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
                iFlags = pFlexCANLocal->iflag_lo;
                #endif
              }            
              if((iFlags & CanBitMask(rxObjHandle)) != 0)
              {
                CANDRV_SET_CODE_TEST_POINT(0x109);
                CAN_CAN_INTERRUPT_DISABLE(channel);
                CanFullCanMsgReceived( CAN_HW_CHANNEL_CANPARA_FIRST rxObjHandle);
                CAN_CAN_INTERRUPT_RESTORE(channel);
              }
            }  /* if individual polling & object has to be polled */
          } /* for ( txObjHandle ) */
        } /* if (global pending) */
      } /* if ( CanLL_HwIsSleep ... )  */
    }  /* for (all associated HW channel) */
    canPollingTaskActive[channel] = 0;
  }

} /* END OF CanRxTask */
/* CODE CATEGORY 2 END */
#endif /*  C_ENABLE_RX_FULLCAN_OBJECTS && C_ENABLE_RX_FULLCAN_POLLING */

#if defined( C_ENABLE_RX_BASICCAN_POLLING ) && \
    defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/* **************************************************************************
| NAME:             CanRxBasicCANTask
| CALLED BY:        application
| PRECONDITIONS:
| INPUT PARAMETERS: none 
| RETURN VALUES:    none
| DESCRIPTION:      - cyclic Task, 
|                   - polling Rx BasicCAN objects
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxBasicCANTask(CAN_CHANNEL_CANTYPE_ONLY) C_API_3
{
  vuint32     iFlags;
  #if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING ) && !defined( C_ENABLE_FLEXCAN_RXFIFO )
  vuint32     iMask;
  #endif
  tFlexcanPtr pFlexCANLocal;

  CanObjectHandle     rxObjHandle;          /* keyword register removed 2005-06-29 Ht */


# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);    /* PRQA S 3109 */
# endif
  assertUser((canPollingTaskActive[channel] == (vuint8)0), channel, kErrorPollingTaskRecursion);   /* PRQA S 3109 */

  if (canPollingTaskActive[channel] == (vuint8)0)  /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1;


# if defined( C_ENABLE_SLEEP_WAKEUP )
    if ( !CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY))
# endif
    {

      pFlexCANLocal = pFlexCAN(canHwChannel);
      #if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
      # if defined( C_ENABLE_FLEXCAN_RXFIFO )
      rxObjHandle = 0;
      do{
          if((pFlexCANLocal->iflag_lo & kRxFIFO_NEWMSG) != 0)
          {
            CAN_CAN_INTERRUPT_DISABLE(channel); /* SBSW_CAN_LL014 */
            CANDRV_SET_CODE_TEST_POINT(0x108);      
            CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST 0);
            CAN_CAN_INTERRUPT_RESTORE(channel); /* SBSW_CAN_LL014 */
          }
          rxObjHandle++;
      }while(rxObjHandle < (vuint16)(C_FLEXCAN_RXFIFO_MAXLOOP));
      # else
      iMask = CAN_RXBASIC_POLL_MASK_LO(canHwChannel);
      iFlags = pFlexCANLocal->iflag_lo & iMask;
      if(iFlags != 0)
      {         
        rxObjHandle = CAN_HW_RX_BASIC_STARTINDEX(canHwChannel);
        #if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
        iFlags >>= rxObjHandle;
        #endif      
        while(iFlags != 0)
        {
          while((iFlags & (vuint32)0x01) == 0)
          {
            iFlags >>= 1;
            rxObjHandle++;
          }
          CAN_CAN_INTERRUPT_DISABLE(channel); /* SBSW_CAN_LL014 */
          CANDRV_SET_CODE_TEST_POINT(0x108);
          CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST rxObjHandle); /* SBSW_CAN_LL015 */
          CAN_CAN_INTERRUPT_RESTORE(channel); /* SBSW_CAN_LL014 */
          rxObjHandle++;
          iFlags = (pFlexCANLocal->iflag_lo & iMask) >> rxObjHandle;    
        }
      } 
      
      # if defined( C_ENABLE_MAX_BUFFER_64 )
      #  if defined( C_CAN_MAX_BUFFER_MIXED )
      if (CanMaxMB[canHwChannel] == 64)
      #  endif
      {
        iMask = CAN_RXBASIC_POLL_MASK_HI(canHwChannel);
        iFlags = pFlexCANLocal->iflag_hi & iMask;
        if(iFlags != 0)
        {    
          rxObjHandle = CAN_HW_RX_BASIC_STARTINDEX(canHwChannel);
          if(rxObjHandle > 32)
          {
            iFlags >>= (rxObjHandle-32);
          }
          else
          {
            rxObjHandle = (vuint16)32;
          }
          while(iFlags != 0)
          {
            while((iFlags & (vuint32)0x01) == 0)
            {
              iFlags >>= 1;
              rxObjHandle++;
            }    
            CAN_CAN_INTERRUPT_DISABLE(channel); /* SBSW_CAN_LL014 */
            CANDRV_SET_CODE_TEST_POINT(0x108);
            CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST rxObjHandle); /* SBSW_CAN_LL015 */
            CAN_CAN_INTERRUPT_RESTORE(channel); /* SBSW_CAN_LL014 */
            rxObjHandle++;
            iFlags = (pFlexCANLocal->iflag_hi & iMask) >> (rxObjHandle-32);
          }
        }
      }
      #  endif /* C_ENABLE_MAX_BUFFER_64 */ 
      # endif /* C_ENABLE_FLEXCAN_RXFIFO */
      #endif /* C_ENABLE_INDIVIDUAL_BUFFER_MASKING */
      
      iFlags = 0;
      if(iFlags != 0) /* PRQA S 3356,3359 */ /* MD_Can_13.7 */
      { /* PRQA S 3201 */ /* MD_Can_3201 */
        rxObjHandle = 0; /* to avoid compiler warning "rxObjHandle might be used before set". code not used */
        /* loop over all BasicCAN hardware objects assigend to the BasicCAN which starts with rxObjHandle */
        #if !defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
        #endif
        {
# if defined( C_ENABLE_INDIVIDUAL_POLLING )
          if ( CanHwObjIndivPolling[CAN_HWOBJINDIVPOLLING_INDEX0][rxObjHandle] != (vuint8)0 )
# endif
          {
            /* check for dedicated indication pending */
            #if !defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
            #endif
            {
              CANDRV_SET_CODE_TEST_POINT(0x108);

              CAN_CAN_INTERRUPT_DISABLE(channel);
              CanBasicCanMsgReceived( CAN_HW_CHANNEL_CANPARA_FIRST rxObjHandle);
              CAN_CAN_INTERRUPT_RESTORE(channel);
            }
          } /* if individual polling & object has to be polled */
        /* loop over all BasicCAN hardware objects of channel */
        }
      }
    } /* if ( CanLL_HwIsSleep... )  */

    canPollingTaskActive[channel] = 0;
  }

} /* END OF CanRxTask */
/* CODE CATEGORY 2 END */
#endif /* C_ENABLE_RX_BASICCAN_POLLING && C_ENABLE_RX_BASICCAN_OBJECTS */

/* **************************************************************************
| NAME:             CanHL_ErrorHandling
| CALLED BY:        CanISR(), CanErrorTask()
| PRECONDITIONS:
| INPUT PARAMETERS: none 
| RETURN VALUES:    none
| DESCRIPTION:      - error interrupt (busoff, error warning, ...)
************************************************************************** */
/* CODE CATEGORY 2 START */
static void CanHL_ErrorHandling( CAN_HW_CHANNEL_CANTYPE_ONLY )
{
  tFlexcanPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* pointer to FlexCAN channel object */

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(canHwChannel < kCanNumberOfHwChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);      /* PRQA S 3109 */
#endif




  /* check for status register (bus error)-- */
  if((pFlexCANLocal->estat & kFlexCAN_BOFF_INT) != 0)
  {
    pFlexCANLocal->estat = CANSFR_CAST(kFlexCAN_BOFF_INT | kFlexCAN_ERR_INT); /* clear busoff and error interrupt flags */ /* SBSW_CAN_LL005 */
    /* ==BUS OFF ERROR========================= */
    APPL_CAN_BUSOFF( CAN_CHANNEL_CANPARA_ONLY );            /* call application specific function */
  }


} /* END OF CanHL_ErrorHandling */
/* CODE CATEGORY 2 END */


#if defined( C_ENABLE_INDIVIDUAL_POLLING )
# if defined( C_ENABLE_TX_POLLING )
/* **************************************************************************
| NAME:             CanTxObjTask()
| CALLED BY:        
| PRECONDITIONS:    
| INPUT PARAMETERS: CAN_HW_CHANNEL_CANTYPE_FIRST 
|                   CanObjectHandle txObjHandle
| RETURN VALUES:    none
| DESCRIPTION:      Polling special Object
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanTxObjTask(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle txObjHandle)      /* PRQA S 1330 */
{

  vuint32     iFlags;
  tFlexcanPtr pFlexCANLocal;


#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(canHwChannel < kCanNumberOfHwChannels, kCanAllChannels, kErrorChannelHdlTooLarge);  /* PRQA S 3109 */
#  endif
  assertUser(txObjHandle < CAN_HL_HW_TX_STOPINDEX(canHwChannel), channel, kErrorHwHdlTooLarge);     /* PRQA S 3109 */
  assertUser((CanSignedTxHandle)txObjHandle >= (CanSignedTxHandle)CAN_HL_HW_TX_STARTINDEX(canHwChannel), channel, kErrorHwHdlTooSmall);   /* PRQA S 3109 */ /* lint !e568 */
  assertUser(CanHwObjIndivPolling[CAN_HWOBJINDIVPOLLING_INDEX0][txObjHandle] != (vuint8)0, channel, kErrorHwObjNotInPolling);    /* PRQA S 3109 */
  assertUser((canPollingTaskActive[channel] == (vuint8)0), channel, kErrorPollingTaskRecursion);     /* PRQA S 3109 */

  if (canPollingTaskActive[channel] == (vuint8)0)  /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1;

#  if defined( C_ENABLE_SLEEP_WAKEUP )
    if ( !CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY))
#  endif
    {

      /* check for dedicated confirmation pending */
      pFlexCANLocal = pFlexCAN(canHwChannel);
      #if defined( C_ENABLE_MAX_BUFFER_64 )
      if(txObjHandle > (vuint16)31)
      {
        iFlags = pFlexCANLocal->iflag_hi;
      }
      else      
      #endif
      {
        iFlags = pFlexCANLocal->iflag_lo; 
      }
      if((iFlags & CanBitMask(txObjHandle)) != 0)
      {
        CAN_CAN_INTERRUPT_DISABLE(channel);
        /* do tx confirmation */
        CanHL_TxConfirmation(CAN_HW_CHANNEL_CANPARA_FIRST txObjHandle );
        CAN_CAN_INTERRUPT_RESTORE(channel);
      }

#  if defined( C_ENABLE_TRANSMIT_QUEUE )
      if ( txObjHandle == CAN_HL_HW_TX_NORMAL_INDEX(channel) )
      {
        CanHl_RestartTxQueue( CAN_CHANNEL_CANPARA_ONLY );
      }
#  endif /*  C_ENABLE_TRANSMIT_QUEUE */
    }

    canPollingTaskActive[channel] = 0;
  }
} /* CanTxObjTask */
/* CODE CATEGORY 2 END */
# endif    /* defined( C_ENABLE_INDIVIDUAL_POLLING ) && defined( C_ENABLE_TX_POLLING ) */

# if defined( C_ENABLE_RX_FULLCAN_OBJECTS ) && \
    defined( C_ENABLE_RX_FULLCAN_POLLING )  
/* **************************************************************************
| NAME:             CanRxFullCANObjTask()
| CALLED BY:        
| PRECONDITIONS:    
| INPUT PARAMETERS: CAN_HW_CHANNEL_CANTYPE_FIRST 
|                   CanObjectHandle rxObjHandle
| RETURN VALUES:    none
| DESCRIPTION:      Polling special Object
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxFullCANObjTask(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle)      /* PRQA S 1330 */
{

  vuint32     iFlags;
  tFlexcanPtr pFlexCANLocal;


#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(canHwChannel < kCanNumberOfHwChannels, kCanAllChannels, kErrorChannelHdlTooLarge);   /* PRQA S 3109 */
#  endif
  assertUser(rxObjHandle < CAN_HL_HW_RX_FULL_STOPINDEX(canHwChannel), channel, kErrorHwHdlTooLarge);   /* PRQA S 3109 */
#  if defined( C_SINGLE_RECEIVE_CHANNEL ) 
#   if (CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel) == 0)
  /* avoid compiler warning: comparison is always true ; ESCAN00059736 */
#   else
  assertUser(rxObjHandle >= CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel), channel, kErrorHwHdlTooSmall);  /* PRQA S 3109 */ /* lint !e568 */
#   endif
#  else
  assertUser(rxObjHandle >= CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel), channel, kErrorHwHdlTooSmall);  /* PRQA S 3109 */ /* lint !e568 */
#  endif
  assertUser(CanHwObjIndivPolling[CAN_HWOBJINDIVPOLLING_INDEX0][rxObjHandle] != (vuint8)0, channel, kErrorHwObjNotInPolling);   /* PRQA S 3109 */
  assertUser((canPollingTaskActive[channel] == 0), channel, kErrorPollingTaskRecursion);   /* PRQA S 3109 */

  if (canPollingTaskActive[channel] == (vuint8)0)  /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1;

#  if defined( C_ENABLE_SLEEP_WAKEUP )
    if ( !CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY))
#  endif
    {
      /* check for dedicated indication pending */
      pFlexCANLocal = pFlexCAN(canHwChannel);
      #if defined( C_ENABLE_MAX_BUFFER_64 )
      if(rxObjHandle > (vuint16)31)
      {
        #if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
        iFlags = pFlexCANLocal->iflag_hi;
        #endif
      }
      else      
      #endif
      {
        #if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
        iFlags = pFlexCANLocal->iflag_lo;
        #endif
      }            
      if((iFlags & CanBitMask(rxObjHandle)) != 0)
      {
        CANDRV_SET_CODE_TEST_POINT(0x109);
        CAN_CAN_INTERRUPT_DISABLE(channel);
        CanFullCanMsgReceived( CAN_HW_CHANNEL_CANPARA_FIRST rxObjHandle);
        CAN_CAN_INTERRUPT_RESTORE(channel);
      }
    }
    canPollingTaskActive[channel] = 0;
  }
} /* CanRxFullCANObjTask */
/* CODE CATEGORY 2 END */
# endif

# if defined( C_ENABLE_RX_BASICCAN_POLLING ) && \
    defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/* **************************************************************************
| NAME:             CanRxBasicCANObjTask()
| CALLED BY:        
| PRECONDITIONS:    
| INPUT PARAMETERS: CAN_HW_CHANNEL_CANTYPE_FIRST 
|                   CanObjectHandle rxObjHandle
| RETURN VALUES:    none
| DESCRIPTION:      Polling special Object
************************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanRxBasicCANObjTask(CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle)        /* PRQA S 1330 */
{
#  if kCanNumberOfHwObjPerBasicCan > 1
  CanObjectHandle i;
#  endif

  vuint32     iFlags;
  #if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING ) && !defined( C_ENABLE_FLEXCAN_RXFIFO )
  vuint32     iMask;
  #endif
  tFlexcanPtr pFlexCANLocal;


#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(canHwChannel < kCanNumberOfHwChannels, kCanAllChannels, kErrorChannelHdlTooLarge);   /* PRQA S 3109 */
#  endif
  assertUser(rxObjHandle < CAN_HL_HW_RX_BASIC_STOPINDEX(canHwChannel), channel, kErrorHwHdlTooLarge);  /* PRQA S 3109 */
#  if defined( C_SINGLE_RECEIVE_CHANNEL ) 
#   if (CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel) == 0)
  /* avoid compiler warning: comparison is always true ; ESCAN00058586 */
#   else
  assertUser(rxObjHandle >= CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel), channel, kErrorHwHdlTooSmall); /* PRQA S 3109 */ /* lint !e568 */
#   endif
#  else
  assertUser(rxObjHandle >= CAN_HL_HW_RX_BASIC_STARTINDEX(canHwChannel), channel, kErrorHwHdlTooSmall); /* PRQA S 3109 */ /* lint !e568 */
#  endif
  assertUser(CanHwObjIndivPolling[CAN_HWOBJINDIVPOLLING_INDEX0][rxObjHandle] != (vuint8)0, channel, kErrorHwObjNotInPolling);   /* PRQA S 3109 */
  assertUser((canPollingTaskActive[channel] == (vuint8)0), channel, kErrorPollingTaskRecursion);  /* PRQA S 3109 */

  if (canPollingTaskActive[channel] == (vuint8)0)  /* avoid reentrance */
  {
    canPollingTaskActive[channel] = 1;

#  if defined( C_ENABLE_SLEEP_WAKEUP )
    if ( !CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY) )
#  endif
    {

#  if kCanNumberOfHwObjPerBasicCan > 1
        /* loop over all BasicCAN hardware objects assigend to the BasicCAN which starts with rxObjHandle */
      pFlexCANLocal = pFlexCAN(canHwChannel);
      #if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
      # if defined( C_ENABLE_FLEXCAN_RXFIFO )
      if(pFlexCANLocal->iflag_lo & kRxFIFO_NEWMSG != 0)
      {
        CAN_CAN_INTERRUPT_DISABLE(channel);
        CANDRV_SET_CODE_TEST_POINT(0x109);
        CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST 0);
        CAN_CAN_INTERRUPT_RESTORE(channel);
      }
      # else
      i = rxObjHandle;
      #  if defined( C_ENABLE_MAX_BUFFER_64 )
      if(i > (vuint16)31)
      {
        iMask = CAN_RXBASIC_POLL_MASK_HI(canHwChannel);
        iFlags = pFlexCANLocal->iflag_hi & iMask;
      }
      else
      #  endif
      {
        iMask = CAN_RXBASIC_POLL_MASK_LO(canHwChannel);  
        iFlags = pFlexCANLocal->iflag_lo & iMask;
      }
      if((iFlags & CanBitMask(i)) != 0)
      {
        CAN_CAN_INTERRUPT_DISABLE(channel);
        CANDRV_SET_CODE_TEST_POINT(0x109);
        CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST i);
        CAN_CAN_INTERRUPT_RESTORE(channel);
      }
      
      i++;
      #  if defined( C_ENABLE_MAX_BUFFER_64 )
      if(i > (vuint16)31)
      {
        iMask = CAN_RXBASIC_POLL_MASK_HI(canHwChannel);
        iFlags = pFlexCANLocal->iflag_hi & iMask;
      }
      else
      #  endif
      {
        iMask = CAN_RXBASIC_POLL_MASK_LO(canHwChannel);  
        iFlags = pFlexCANLocal->iflag_lo & iMask;
      }
      if((iFlags & CanBitMask(i)) != 0)
      {
        CAN_CAN_INTERRUPT_DISABLE(channel);
        CANDRV_SET_CODE_TEST_POINT(0x109);
        CanBasicCanMsgReceived(CAN_HW_CHANNEL_CANPARA_FIRST i);
        CAN_CAN_INTERRUPT_RESTORE(channel);
      }
      # endif
      iFlags = 0;
      if(iFlags != 0) /* PRQA S 3356,3359 */ /* MD_Can_13.7 */
      {
      #endif
#  endif
        /* check for dedicated indication pending */
        #if !defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
        #endif
        {
          CANDRV_SET_CODE_TEST_POINT(0x109);
          CAN_CAN_INTERRUPT_DISABLE(channel);
          CanBasicCanMsgReceived( CAN_HW_CHANNEL_CANPARA_FIRST rxObjHandle);
          CAN_CAN_INTERRUPT_RESTORE(channel);
        }
#  if kCanNumberOfHwObjPerBasicCan > 1
        /* loop over all BasicCAN hardware objects assigend to the BasicCAN which starts with rxObjHandle */
      }
#  endif
    }
    canPollingTaskActive[channel] = 0;
  }
} /* CanRxBasicCANObjTask */
/* CODE CATEGORY 2 END */
# endif
#endif /* C_ENABLE_INDIVIDUAL_POLLING */

#if defined( C_ENABLE_RX_BASICCAN_OBJECTS )
/* **************************************************************************
| NAME:             CanBasicCanMsgReceived
| CALLED BY:        CanISR()
| PRECONDITIONS:
| INPUT PARAMETERS: internal can chip number
| RETURN VALUES:    none
| DESCRIPTION:      - basic can receive
************************************************************************** */
/* PRQA S 2001 End_CanBasicCanMsgReceived */    /* suppress misra message about usage of goto */
/* CODE CATEGORY 1 START */
static void CanBasicCanMsgReceived( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle)
{
# if defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
  tCanRxInfoStruct    *pCanRxInfoStruct;
# endif  
  
# if ( !defined( C_SEARCH_HASH ) && \
       !defined( C_SEARCH_INDEX ) )  ||\
     defined( C_ENABLE_RANGE_0 ) || \
     defined( C_ENABLE_RANGE_1 ) || \
     defined( C_ENABLE_RANGE_2 ) || \
     defined( C_ENABLE_RANGE_3 )
  tCanRxId0 idRaw0;
#  if (kCanNumberOfUsedCanRxIdTables > 1)
  tCanRxId1 idRaw1;
#  endif
#  if (kCanNumberOfUsedCanRxIdTables > 2)
  tCanRxId2 idRaw2;
#  endif
#  if (kCanNumberOfUsedCanRxIdTables > 3)
  tCanRxId3 idRaw3;
#  endif
#  if (kCanNumberOfUsedCanRxIdTables > 4)
  tCanRxId4 idRaw4;
#  endif
# endif

# if defined( C_SEARCH_HASH )
#  if (kCanNumberOfRxBasicCANObjects > 0)
#   if (kHashSearchListCountEx > 0)
  vuint32          idExt;
#    if (kHashSearchListCountEx > 1)
  vuint32          winternExt;        /* prehashvalue         */
#    endif
#   endif
#   if (kHashSearchListCount > 0)
  vuint16          idStd;
#    if (kHashSearchListCount > 1)
  vuint16          winternStd;        /* prehashvalue         */
#    endif
#   endif
#   if (((kHashSearchListCountEx > 1) && (kHashSearchMaxStepsEx > 1)) ||\
        ((kHashSearchListCount > 1)   && (kHashSearchMaxSteps > 1))) 
  vuint16          i_increment;    /* delta for next step  */
  vsint16          count;
#   endif
#  endif  /* kCanNumberOfRxBasicCANObjects > 0 */
# endif

  #if defined( C_ENABLE_PROTECTED_RX_PROCESS )
  CanDeclareGlobalInterruptOldStatus
  #endif
  vuint8         loopResult;
  tFlexcanPtr    pFlexCANLocal = pFlexCAN(canHwChannel); /* pointer to FlexCAN channel object */    

# if defined( C_ENABLE_GENERIC_PRECOPY ) || \
    defined( C_ENABLE_PRECOPY_FCT )     || \
    defined( C_ENABLE_COPY_RX_DATA )    || \
    defined( C_ENABLE_INDICATION_FLAG ) || \
    defined( C_ENABLE_INDICATION_FCT )  || \
    defined( C_ENABLE_DLC_CHECK )       || \
    defined( C_ENABLE_NOT_MATCHED_FCT )
#  if (kCanNumberOfRxBasicCANObjects > 0)

  CanReceiveHandle         rxHandle;

  rxHandle = kCanRxHandleNotUsed;

#  endif /* kCanNumberOfRxBasicCANObjects > 0 */
# endif

  CANDRV_SET_CODE_TEST_POINT(0x100);

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(canHwChannel < kCanNumberOfHwChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);  /* PRQA S 3109 */
# endif

  #if defined( C_ENABLE_PROTECTED_RX_PROCESS )
  CanNestedGlobalInterruptDisable(); /* SBSW_CAN_LL002 */
  #endif
  
  CanLL_ApplCanTimerStart(kCanLoopRxBasicIrq); /* start hw loop timer */ /* SBSW_CAN_LL003 */
  do
  { /* Check busy state of receive object */
    canRxMsgBuffer[canHwChannel].control = pFlexCANLocal->canObject[rxObjHandle].control; /* SBSW_CAN_LL004 */
    loopResult = CanLL_ApplCanTimerLoop(kCanLoopRxBasicIrq); /* SBSW_CAN_LL003 */
  }while(((canRxMsgBuffer[canHwChannel].control & kRxCodeBusy) == kRxCodeBusy) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */
  CanLL_ApplCanTimerEnd(kCanLoopRxBasicIrq); /* stop hw loop timer */ /* SBSW_CAN_LL003 */
  
  canRxMsgBuffer[canHwChannel].msgIDH = pFlexCANLocal->canObject[rxObjHandle].msgIDH; /* SBSW_CAN_LL004 */
  #if defined( C_ENABLE_EXTENDED_ID )
  canRxMsgBuffer[canHwChannel].msgIDL = pFlexCANLocal->canObject[rxObjHandle].msgIDL; /* SBSW_CAN_LL004 */
  #endif
  #if defined( C_CPUTYPE_BIGENDIAN )
  *((CanChipDataPtr32)&(canRxMsgBuffer[canHwChannel].data[0])) = (vuint32)*((CanChipDataPtr32)&(pFlexCANLocal->canObject[rxObjHandle].data[0])); /* PRQA S 0310 */ /* MD_Can_0310 */ /* SBSW_CAN_LL004 */
  *((CanChipDataPtr32)&(canRxMsgBuffer[canHwChannel].data[4])) = (vuint32)*((CanChipDataPtr32)&(pFlexCANLocal->canObject[rxObjHandle].data[4])); /* PRQA S 0310 */ /* MD_Can_0310 */ /* SBSW_CAN_LL004 */
  #endif
  
  #if defined( C_ENABLE_FLEXCAN_RXFIFO )
  pFlexCANLocal->iflag_lo = (vuint32)kRxFIFO_NEWMSG; /* clear RxFIFO pending interrupt flag after message is stored! */ /* SBSW_CAN_LL005 */
  #else
  # if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
  #  if defined( C_ENABLE_MAX_BUFFER_64 )
  if(rxObjHandle > (vuint16)31)
  {
    #if defined( C_CAN_MAX_BUFFER_MIXED )
    assertHardware((CanMaxMB[canHwChannel] == 64), canHwChannel, kCanInvalidHwObjHandle);
    #endif    
    pFlexCANLocal->iflag_hi = CanBitMask(rxObjHandle); /* clear pending interrupt flag */ /* SBSW_CAN_LL005 */
  }
  else
  #  endif
  # endif /* C_ENABLE_INDIVIDUAL_BUFFER_MASKING */
  {
    pFlexCANLocal->iflag_lo = CanBitMask(rxObjHandle); /* clear pending interrupt flag */ /* SBSW_CAN_LL005 */
  }
  #endif /* C_ENABLE_FLEXCAN_RXFIFO */
  
  #if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
  /* to unlock only the current receive buffer the timestamp of another not-Rx message object must be read
   * reading the global timer results in a global unlock of all receive buffers */
  canRxMsgBuffer[canHwChannel].timestamp = pFlexCANLocal->canObject[CAN_HW_TX_NORMAL_INDEX(canHwChannel)].timestamp; /* unlock current receive buffer */ /* SBSW_CAN_LL004 */
  #endif
  
  #if defined( C_ENABLE_PROTECTED_RX_PROCESS )
  CanNestedGlobalInterruptRestore(); /* SBSW_CAN_LL002 */
  #endif
  
  #if defined( C_ENABLE_HW_LOOP_TIMER )
  if(loopResult == 0)
  {    
    goto finishBasicCan; /* loop was aborted! don't process this message */
  }
  #endif
  
  

# if defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
  pCanRxInfoStruct =  &canRxInfoStruct[channel];
  (pCanRxInfoStruct->pChipMsgObj) = (CanChipMsgPtr)&(canRxMsgBuffer[canHwChannel].control); /* PRQA S 0310 */ /* MD_Can_0310 */
  (pCanRxInfoStruct->pChipData) = (CanChipDataPtr) &(canRxMsgBuffer[canHwChannel].data[0]);
  canRDSRxPtr[channel] = pCanRxInfoStruct->pChipData;
# else
  (canRxInfoStruct[channel].pChipMsgObj) = (CanChipMsgPtr)&(canRxMsgBuffer[canHwChannel].control); /* PRQA S 0310 */ /* MD_Can_0310 */
  (canRxInfoStruct[channel].pChipData) = (CanChipDataPtr) &(canRxMsgBuffer[canHwChannel].data[0]);
  canRDSRxPtr[channel] = canRxInfoStruct[channel].pChipData;
# endif
  CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)      = kCanRxHandleNotUsed;  

# if defined( C_ENABLE_CAN_RAM_CHECK )
  if(canComStatus[channel] == kCanDisableCommunication)
  {
    goto finishBasicCan; /* ignore reception */
  }
# endif

#  if defined( C_ENABLE_OVERRUN )
  #if defined( C_ENABLE_FLEXCAN_RXFIFO )
  if((pFlexCANLocal->iflag_lo & kRxFIFO_OVERRUN) != 0)
  {
    pFlexCANLocal->iflag_lo = kRxFIFO_OVERRUN | kRxFIFO_WARN; /* clear warning and overflow flag */
  #else
  if((canRxMsgBuffer[canHwChannel].control & kCodeMask) == kRxCodeOverrun)
  {
  #endif
    ApplCanOverrun( CAN_CHANNEL_CANPARA_ONLY );
  }
#  endif

  /* ************************** reject remote frames  ************************************** */


  /* ************************** reject messages with unallowed ID type ************************************** */


# if defined( C_ENABLE_COND_RECEIVE_FCT )
  /* ************************** conditional message receive function  ************************************** */
  if(canMsgCondRecState[channel]==kCanTrue)
  {
    ApplCanMsgCondReceived( CAN_HL_P_RX_INFO_STRUCT(channel) );
  }
# endif

# if defined( C_ENABLE_RECEIVE_FCT )
  /* ************************** call ApplCanMsgReceived() ************************************************** */
  if (APPL_CAN_MSG_RECEIVED( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanNoCopyData)
  {
    goto finishBasicCan;
  }
# endif
  

# if ( !defined( C_SEARCH_HASH ) && \
       !defined( C_SEARCH_INDEX ) ) || \
     defined( C_ENABLE_RANGE_0 ) || \
     defined( C_ENABLE_RANGE_1 ) || \
     defined( C_ENABLE_RANGE_2 ) || \
     defined( C_ENABLE_RANGE_3 )
  /* ************************** calculate idRaw for filtering ********************************************** */
#  if defined( C_ENABLE_EXTENDED_ID )
#   if defined( C_ENABLE_MIXED_ID )
  if (CanRxActualIdType(CAN_HL_P_RX_INFO_STRUCT(channel)) == kCanIdTypeExt)
#   endif
  {
#   if defined( C_ENABLE_RX_MASK_EXT_ID )
    idRaw0 = CanRxActualIdRaw0( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID0(C_MASK_EXT_ID);
#    if (kCanNumberOfUsedCanRxIdTables > 1)
    idRaw1 = CanRxActualIdRaw1( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID1(C_MASK_EXT_ID);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 2)
    idRaw2 = CanRxActualIdRaw2( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID2(C_MASK_EXT_ID);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 3)
    idRaw3 = CanRxActualIdRaw3( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID3(C_MASK_EXT_ID);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 4)
    idRaw4 = CanRxActualIdRaw4( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID4(C_MASK_EXT_ID);
#    endif
#   else
    idRaw0 = CanRxActualIdRaw0( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID0(0x1FFFFFFF);
#    if (kCanNumberOfUsedCanRxIdTables > 1)
    idRaw1 = CanRxActualIdRaw1( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID1(0x1FFFFFFF);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 2)
    idRaw2 = CanRxActualIdRaw2( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID2(0x1FFFFFFF);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 3)
    idRaw3 = CanRxActualIdRaw3( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID3(0x1FFFFFFF);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 4)
    idRaw4 = CanRxActualIdRaw4( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_EXTID4(0x1FFFFFFF);
#    endif
#   endif /*  C_ENABLE_RX_MASK_EXT_ID */
  }
#   if defined( C_ENABLE_MIXED_ID )
  else
  {
    idRaw0 = CanRxActualIdRaw0( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID0(0x7FF);
#    if (kCanNumberOfUsedCanRxIdTables > 1)
    idRaw1 = CanRxActualIdRaw1( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID1(0x7FF);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 2)
    idRaw2 = CanRxActualIdRaw2( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID2(0x7FF);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 3)
    idRaw3 = CanRxActualIdRaw3( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID3(0x7FF);
#    endif
#    if (kCanNumberOfUsedCanRxIdTables > 4)
    idRaw4 = CanRxActualIdRaw4( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID4(0x7FF);
#    endif
  }
#   endif
#  else /* C_ENABLE_EXTENDED_ID */
  {
    idRaw0 = CanRxActualIdRaw0( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID0(0x7FF);
#   if (kCanNumberOfUsedCanRxIdTables > 1)
    idRaw1 = CanRxActualIdRaw1( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID1(0x7FF);
#   endif
#   if (kCanNumberOfUsedCanRxIdTables > 2)
    idRaw2 = CanRxActualIdRaw2( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID2(0x7FF);
#   endif
#   if (kCanNumberOfUsedCanRxIdTables > 3)
    idRaw3 = CanRxActualIdRaw3( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID3(0x7FF);
#   endif
#   if (kCanNumberOfUsedCanRxIdTables > 4)
    idRaw4 = CanRxActualIdRaw4( CAN_HL_P_RX_INFO_STRUCT(channel) ) & MK_STDID4(0x7FF);
#   endif
  }
#  endif /* C_ENABLE_EXTENDED_ID */
# endif /* ( !defined( C_SEARCH_HASH ) && ...  defined( C_ENABLE_RANGE_3 ) */

  /* ***************** Range filtering ****************************************************************** */

  {
#  if defined( C_ENABLE_RANGE_0 )
#   if defined( C_MULTIPLE_RECEIVE_CHANNEL )
    if ( (CanChannelObject[channel].RangeActiveFlag & kCanRange0) != (vuint16)0 )
    {
#    if defined( C_ENABLE_MIXED_ID ) 
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == CANRANGE0IDTYPE(channel))
#    endif
      {
        if ( C_RANGE_MATCH( CAN_RX_IDRAW_PARA, CANRANGE0ACCMASK(channel), CANRANGE0ACCCODE(channel)) )
#   else    /* C_SINGLE_RECEIVE_CHANNEL) */
    {
#    if (C_RANGE0_IDTYPE == kCanIdTypeStd )
#     if defined( C_ENABLE_MIXED_ID ) 
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeStd)
#     endif
      {
        if ( C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, CANRANGE0ACCMASK(channel), CANRANGE0ACCCODE(channel)) )
#    else  /* C_RANGE_0_IDTYPE == kCanIdTypeExt */
#     if defined( C_ENABLE_MIXED_ID ) 
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeExt)
#     endif
      {
        if ( C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, CANRANGE0ACCMASK(channel), CANRANGE0ACCCODE(channel)) )
#    endif
#   endif
        {
#   if defined( C_ENABLE_RX_QUEUE_RANGE )
          if (CanRxQueueRange0[channel] == kCanTrue)
          {
            pCanRxInfoStruct->Handle      = kCanRxHandleRange0;
            (void)CanHL_ReceivedRxHandleQueue( CAN_CHANNEL_CANPARA_ONLY );
            goto finishBasicCan;
          }
          else
#   endif  /* C_ENABLE_RX_QUEUE */
          {
            if (APPLCANRANGE0PRECOPY( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanNoCopyData)
            {
              goto finishBasicCan;
            }
          }
        }
      }
    }
#  endif  /* C_ENABLE_RANGE_0 */

#  if defined( C_ENABLE_RANGE_1 )
#   if defined( C_MULTIPLE_RECEIVE_CHANNEL )
    if ( (CanChannelObject[channel].RangeActiveFlag & kCanRange1) != (vuint16)0 )
    {
#    if defined( C_ENABLE_MIXED_ID ) 
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == CANRANGE1IDTYPE(channel))
#    endif
      {
        if ( C_RANGE_MATCH( CAN_RX_IDRAW_PARA, CANRANGE1ACCMASK(channel), CANRANGE1ACCCODE(channel)) )
#   else    /* C_SINGLE_RECEIVE_CHANNEL) */
    {
#    if (C_RANGE1_IDTYPE == kCanIdTypeStd )
#     if defined( C_ENABLE_MIXED_ID ) 
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeStd)
#     endif
      {
        if ( C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, CANRANGE1ACCMASK(channel), CANRANGE1ACCCODE(channel)) )
#    else  /* C_RANGE_1_IDTYPE == kCanIdTypeExt */
#     if defined( C_ENABLE_MIXED_ID ) 
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeExt)
#     endif
      {
        if ( C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, CANRANGE1ACCMASK(channel), CANRANGE1ACCCODE(channel)) )
#    endif
#   endif
        {
#   if defined( C_ENABLE_RX_QUEUE_RANGE )
          if (CanRxQueueRange1[channel] == kCanTrue)
          {
            pCanRxInfoStruct->Handle      = kCanRxHandleRange1;
            (void)CanHL_ReceivedRxHandleQueue( CAN_CHANNEL_CANPARA_ONLY );
            goto finishBasicCan;
          }
          else
#   endif  /* C_ENABLE_RX_QUEUE */
          {
            if (APPLCANRANGE1PRECOPY( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanNoCopyData)
            {
              goto finishBasicCan;
            }
          }
        }
      }
    }
#  endif  /* C_ENABLE_RANGE_1 */

#  if defined( C_ENABLE_RANGE_2 )
#   if defined( C_MULTIPLE_RECEIVE_CHANNEL )
    if ( (CanChannelObject[channel].RangeActiveFlag & kCanRange2) != (vuint16)0 )
    {
#    if defined( C_ENABLE_MIXED_ID ) 
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == CANRANGE2IDTYPE(channel))
#    endif
      {
        if ( C_RANGE_MATCH( CAN_RX_IDRAW_PARA, CANRANGE2ACCMASK(channel), CANRANGE2ACCCODE(channel)) )
#   else    /* C_SINGLE_RECEIVE_CHANNEL) */
    {
#    if (C_RANGE2_IDTYPE == kCanIdTypeStd )
#     if defined( C_ENABLE_MIXED_ID ) 
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeStd)
#     endif
      {
        if ( C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, CANRANGE2ACCMASK(channel), CANRANGE2ACCCODE(channel)) )
#    else  /* C_RANGE_2_IDTYPE == kCanIdTypeExt */
#     if defined( C_ENABLE_MIXED_ID ) 
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeExt)
#     endif
      {
        if ( C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, CANRANGE2ACCMASK(channel), CANRANGE2ACCCODE(channel)) )
#    endif
#   endif
        {
#   if defined( C_ENABLE_RX_QUEUE_RANGE )
          if (CanRxQueueRange2[channel] == kCanTrue)
          {
            pCanRxInfoStruct->Handle      = kCanRxHandleRange2;
            (void)CanHL_ReceivedRxHandleQueue( CAN_CHANNEL_CANPARA_ONLY );
            goto finishBasicCan;
          }
          else
#   endif  /* C_ENABLE_RX_QUEUE */
          {
            if (APPLCANRANGE2PRECOPY( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanNoCopyData)
            {
              goto finishBasicCan;
            }
          }
        }
      }
    }
#  endif  /* C_ENABLE_RANGE_2 */

#  if defined( C_ENABLE_RANGE_3 )
#   if defined( C_MULTIPLE_RECEIVE_CHANNEL )
    if ( (CanChannelObject[channel].RangeActiveFlag & kCanRange3) != (vuint16)0 )
    {
#    if defined( C_ENABLE_MIXED_ID ) 
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == CANRANGE3IDTYPE(channel))
#    endif
      {
        if ( C_RANGE_MATCH( CAN_RX_IDRAW_PARA, CANRANGE3ACCMASK(channel), CANRANGE3ACCCODE(channel)) )
#   else    /* C_SINGLE_RECEIVE_CHANNEL) */
    {
#    if (C_RANGE3_IDTYPE == kCanIdTypeStd )
#     if defined( C_ENABLE_MIXED_ID ) 
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeStd)
#     endif
      {
        if ( C_RANGE_MATCH_STD( CAN_RX_IDRAW_PARA, CANRANGE3ACCMASK(channel), CANRANGE3ACCCODE(channel)) )
#    else  /* C_RANGE_3_IDTYPE == kCanIdTypeExt */
#     if defined( C_ENABLE_MIXED_ID ) 
      if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanIdTypeExt)
#     endif
      {
        if ( C_RANGE_MATCH_EXT( CAN_RX_IDRAW_PARA, CANRANGE3ACCMASK(channel), CANRANGE3ACCCODE(channel)) )
#    endif
#   endif
        {
#   if defined( C_ENABLE_RX_QUEUE_RANGE )
          if (CanRxQueueRange3[channel] == kCanTrue)
          {
            pCanRxInfoStruct->Handle      = kCanRxHandleRange3;
            (void)CanHL_ReceivedRxHandleQueue( CAN_CHANNEL_CANPARA_ONLY );
            goto finishBasicCan;
          }
          else
#   endif  /* C_ENABLE_RX_QUEUE */
          {
            if (APPLCANRANGE3PRECOPY( CAN_HL_P_RX_INFO_STRUCT(channel) ) == kCanNoCopyData)
            {
              goto finishBasicCan;
            }
          }
        }
      }
    }
#  endif  /* C_ENABLE_RANGE_3 */

  }


# if defined( C_ENABLE_GENERIC_PRECOPY ) || \
    defined( C_ENABLE_PRECOPY_FCT )     || \
    defined( C_ENABLE_COPY_RX_DATA )    || \
    defined( C_ENABLE_INDICATION_FLAG ) || \
    defined( C_ENABLE_INDICATION_FCT )  || \
    defined( C_ENABLE_DLC_CHECK )       || \
    defined( C_ENABLE_NOT_MATCHED_FCT )
# if (kCanNumberOfRxBasicCANObjects > 0)

   /* search the received id in ROM table: */


#  if defined( C_SEARCH_LINEAR )
  /* ************* Linear search ********************************************* */
  {
    for (rxHandle = CAN_HL_RX_BASIC_STARTINDEX(channel); rxHandle < CAN_HL_RX_BASIC_STOPINDEX(channel); rxHandle++)
    {
      if( idRaw0 == CanGetRxId0(rxHandle) )
      {
#   if (kCanNumberOfUsedCanRxIdTables > 1)
        if( idRaw1 == CanGetRxId1(rxHandle) )
#   endif
        {
#   if (kCanNumberOfUsedCanRxIdTables > 2)
          if( idRaw2 == CanGetRxId2(rxHandle) )
#   endif
          {
#   if (kCanNumberOfUsedCanRxIdTables > 3)
            if( idRaw3 == CanGetRxId3(rxHandle) )
#   endif
            {
#   if (kCanNumberOfUsedCanRxIdTables > 4)
              if( idRaw4 == CanGetRxId4(rxHandle) )
#   endif
              {
#   if defined( C_ENABLE_MIXED_ID ) 
                /* verify ID type, if not already done with the ID raw */
                if (CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) ) == CanGetRxIdType(rxHandle))
#   endif
                {
                  /* message found in id table */
                  break;    /* exit loop with index rxHandle */
                }
              }
            }
          }
        }
      }
    }

    if ( rxHandle >= CAN_HL_RX_BASIC_STOPINDEX(channel))     /* no match in linear search detected */
    {
#   if defined( C_ENABLE_NOT_MATCHED_FCT )
      ApplCanMsgNotMatched( CAN_HL_P_RX_INFO_STRUCT(channel) );
#   endif
      goto finishBasicCan;
    }
#   if defined( C_ENABLE_RX_MSG_INDIRECTION )
    else
    {
      rxHandle = CanRxMsgIndirection[rxHandle];       /* indirection for special sort-algoritms */
    }
#   endif
  }
#  endif  /* defined( C_SEARCH_LINEAR ) */

#  if defined( C_SEARCH_HASH )
  /* ************* Hash search ********************************************** */
  {
#   if defined( C_ENABLE_EXTENDED_ID ) 
  /* one or more Extended ID listed */
#    if defined( C_ENABLE_MIXED_ID )
    if((CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) )) == kCanIdTypeExt)
#    endif
#    if (kHashSearchListCountEx > 0)
    {
    /* calculate the logical ID */
#     if defined( C_ENABLE_RX_MASK_EXT_ID )
      idExt          = (CanRxActualId( CAN_HL_P_RX_INFO_STRUCT(channel) ) &  C_MASK_EXT_ID ) | \
                                                                                 ((vuint32)channel << 29);                
#     else
      idExt          = CanRxActualId( CAN_HL_P_RX_INFO_STRUCT(channel) )| ((vuint32)channel << 29);
#     endif

#     if (kHashSearchListCountEx == 1)
      rxHandle       = (CanReceiveHandle)0;
#     else
      winternExt     = idExt + kHashSearchRandomNumberEx;                    
      rxHandle       = (CanReceiveHandle)(winternExt % kHashSearchListCountEx);
#     endif /* (kHashSearchListCountEx == 1) */

#     if ((kHashSearchListCountEx == 1) || (kHashSearchMaxStepsEx == 1))
      if (idExt != CanRxHashIdEx[rxHandle])   
      { 
#      if defined( C_ENABLE_NOT_MATCHED_FCT )
        ApplCanMsgNotMatched( CAN_HL_P_RX_INFO_STRUCT(channel) );
#      endif
        goto finishBasicCan;
      }
#     else /* (kHashSearchListCountEx == 1) || (kHashSearchMaxStepsEx == 1) */

      i_increment = (vuint16)((winternExt % (kHashSearchListCountEx - 1)) + (vuint8)1);          /* ST10-CCAN Keil compiler complains without cast */
      count       = (vsint16)kHashSearchMaxStepsEx - 1;               
  
      while(idExt != CanRxHashIdEx[rxHandle])   
      {
        if(count == (vsint16)0)  
        {
#      if defined( C_ENABLE_NOT_MATCHED_FCT )
          ApplCanMsgNotMatched( CAN_HL_P_RX_INFO_STRUCT(channel) );
#      endif
          goto finishBasicCan;
        }
        count--;
        rxHandle += i_increment;
        if( rxHandle >= (vuint16)kHashSearchListCountEx ) 
        {
          rxHandle -= kHashSearchListCountEx;
        }
      }
#     endif  /* (kHashSearchListCountEx == 1) || (kHashSearchMaxStepsEx == 1) */
      rxHandle = CanRxMsgIndirection[rxHandle+kHashSearchListCount];
    }
#    else /* (kHashSearchListCountEx > 0) */
    {
#     if defined( C_ENABLE_NOT_MATCHED_FCT )
      ApplCanMsgNotMatched( CAN_HL_P_RX_INFO_STRUCT(channel) );
#     endif
      goto finishBasicCan;
    }
#    endif /* (kHashSearchListCountEx > 0) */

#    if defined( C_ENABLE_MIXED_ID )
    else   /* if((CanRxActualIdType( CAN_HL_P_RX_INFO_STRUCT(channel) )) == kCanIdTypeStd)  */
#    endif
#   endif /* If defined( C_ENABLE_EXTENDED_ID ) */

#   if defined( C_ENABLE_MIXED_ID ) || !defined( C_ENABLE_EXTENDED_ID ) 
#    if (kHashSearchListCount > 0)
    {
      idStd          = ((vuint16)CanRxActualId( CAN_HL_P_RX_INFO_STRUCT(channel) ) | ((vuint16)channel << 11));    /* calculate the logical ID */

#     if (kHashSearchListCount == 1)
      rxHandle       = (CanReceiveHandle)0;
#     else
      winternStd     = idStd + kHashSearchRandomNumber;
      rxHandle       = (CanReceiveHandle)(winternStd % kHashSearchListCount);
#     endif /* (kHashSearchListCount == 1) */

#     if ((kHashSearchListCount == 1)  || (kHashSearchMaxSteps == 1))
      if (idStd != CanRxHashId[rxHandle])
      {
#      if defined( C_ENABLE_NOT_MATCHED_FCT )
        ApplCanMsgNotMatched( CAN_HL_P_RX_INFO_STRUCT(channel) );
#      endif
        goto finishBasicCan;
      }
#     else /* ((kHashSearchListCount == 1)  || (kHashSearchMaxSteps == 1)) */

      i_increment = (vuint16)((winternStd % (kHashSearchListCount - 1)) + (vuint8)1);
      count       = (vsint16)kHashSearchMaxSteps-1;

    /* type of CanRxHashId table depends on the used type of Id */
      while ( idStd != CanRxHashId[rxHandle])
      {
        if (count == (vsint16)0)
        {
#     if defined( C_ENABLE_NOT_MATCHED_FCT )
          ApplCanMsgNotMatched( CAN_HL_P_RX_INFO_STRUCT(channel) );
#     endif
          goto finishBasicCan;
        }
        count--; 
        rxHandle += i_increment;
        if ( rxHandle >= kHashSearchListCount )
        {
          rxHandle -= kHashSearchListCount;
        }
      }
#     endif /* ((kHashSearchListCount == 1)  || (kHashSearchMaxSteps == 1)) */
      rxHandle = CanRxMsgIndirection[rxHandle];
    }
#    else /* (kHashSearchListCount > 0) */
    {
#     if defined( C_ENABLE_NOT_MATCHED_FCT )
      ApplCanMsgNotMatched( CAN_HL_P_RX_INFO_STRUCT(channel) );
#     endif
      goto finishBasicCan;
    }
#    endif /* (kHashSearchListCount > 0) */
#   endif /* defined( C_ENABLE_MIXED_ID ) || !defined( C_ENABLE_EXTENDED_ID ) */ 
  }
#  endif /* defined( C_SEARCH_HASH ) */

#  if defined( C_SEARCH_INDEX )
  /* ************* index search *********************************************** */
  {
    rxHandle = CAN_RX_INDEX_TBL(channel, (vuint16)(CanRxActualId( CAN_HL_P_RX_INFO_STRUCT(channel))));
    if ( rxHandle >= kCanNumberOfRxObjects)     /* no match in index search detected */
    {
#   if defined( C_ENABLE_NOT_MATCHED_FCT )
      ApplCanMsgNotMatched( CAN_HL_P_RX_INFO_STRUCT(channel) );
#   endif
      goto finishBasicCan;
    }
  }
#  endif /* defined( C_SEARCH_INDEX ) */


  /* ************************** handle filtered message ************************************************** */
  {
    assertInternal((rxHandle < kCanNumberOfRxObjects), kCanAllChannels, kErrorRxHandleWrong);  /* PRQA S 3109 */ /* legal rxHandle ? */

    CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel) = rxHandle;  

#  if defined( C_ENABLE_RX_QUEUE )
    if (CanHL_ReceivedRxHandleQueue( CAN_CHANNEL_CANPARA_ONLY ) == kCanHlContinueRx)
#  else
    if (CanHL_ReceivedRxHandle( CAN_CHANNEL_CANPARA_ONLY ) == kCanHlContinueRx)
#  endif
    { 
#  if defined( C_ENABLE_INDICATION_FLAG ) || \
          defined( C_ENABLE_INDICATION_FCT )

      CanHL_IndRxHandle( rxHandle );
      

      return;
#  endif
    }
  }
# else  /* kCanNumberOfRxBasicCANObjects > 0 */
#  if defined( C_ENABLE_NOT_MATCHED_FCT )
  ApplCanMsgNotMatched( CAN_HL_P_RX_INFO_STRUCT(channel) );
#  endif
# endif /* kCanNumberOfRxBasicCANObjects > 0 */

# endif

  goto finishBasicCan;     /* to avoid compiler warning */

/* Msg(4:2015) This label is not a case or default label for a switch statement. MISRA Rule 55 */
finishBasicCan:

  /* make receive buffer free */


  return;    /* to avoid compiler warnings about label without code */

} /* end of BasicCan */
/* CODE CATEGORY 1 END */
/* PRQA L:End_CanBasicCanMsgReceived */
#endif

#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )
/* **************************************************************************
| NAME:             CanFullCanMsgReceived
| CALLED BY:        CanISR()
| PRECONDITIONS:
| INPUT PARAMETERS: internal can chip number
| RETURN VALUES:    none
| DESCRIPTION:      - full can receive
************************************************************************** */
/* PRQA S 2001 End_CanFullCanMsgReceived */    /* suppress misra message about usage of goto */
/* CODE CATEGORY 1 START */
static void CanFullCanMsgReceived( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle rxObjHandle )
{
  CanReceiveHandle   rxHandle; 

# if defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
  tCanRxInfoStruct    *pCanRxInfoStruct;
# endif  

  #if defined( C_ENABLE_PROTECTED_RX_PROCESS )
  CanDeclareGlobalInterruptOldStatus
  #endif
  vuint8         loopResult;
  tFlexcanPtr    pFlexCANLocal = pFlexCAN(canHwChannel); /* pointer to FlexCAN channel object */

  CANDRV_SET_CODE_TEST_POINT(0x101);
   
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(canHwChannel < kCanNumberOfHwChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);   /* PRQA S 3109 */
# endif



  #if defined( C_ENABLE_PROTECTED_RX_PROCESS )
  CanNestedGlobalInterruptDisable(); /* SBSW_CAN_LL002 */
  #endif
  
  CanLL_ApplCanTimerStart(kCanLoopRxFullIrq); /* start hw loop timer */ /* SBSW_CAN_LL003 */
  do
  { /* Check busy state of receive object */
    canRxMsgBuffer[canHwChannel].control = pFlexCANLocal->canObject[rxObjHandle].control; /* SBSW_CAN_LL004 */
    loopResult = CanLL_ApplCanTimerLoop(kCanLoopRxFullIrq); /* SBSW_CAN_LL003 */
  }while(((canRxMsgBuffer[canHwChannel].control & kRxCodeBusy) == kRxCodeBusy) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */
  CanLL_ApplCanTimerEnd(kCanLoopRxFullIrq); /* stop hw loop timer */ /* SBSW_CAN_LL003 */
  
  #if defined( C_ENABLE_MAX_BUFFER_64 )
  if(rxObjHandle > (vuint16)31)
  {
    #if defined( C_CAN_MAX_BUFFER_MIXED )
    assertHardware((CanMaxMB[canHwChannel] == 64), canHwChannel, kCanInvalidHwObjHandle);
    #endif      
    pFlexCANLocal->iflag_hi = CanBitMask(rxObjHandle); /* clear pending interrupt flag  */ /* SBSW_CAN_LL005 */
  }
  else
  #endif
  {
    pFlexCANLocal->iflag_lo = CanBitMask(rxObjHandle); /* clear pending interrupt flag  */ /* SBSW_CAN_LL005 */
  }
  
  canRxMsgBuffer[canHwChannel].msgIDH = pFlexCANLocal->canObject[rxObjHandle].msgIDH; /* SBSW_CAN_LL004 */
  #if defined( C_ENABLE_EXTENDED_ID )
  canRxMsgBuffer[canHwChannel].msgIDL = pFlexCANLocal->canObject[rxObjHandle].msgIDL; /* SBSW_CAN_LL004 */
  #endif  
  #if defined( C_CPUTYPE_BIGENDIAN )
  *((CanChipDataPtr32)&(canRxMsgBuffer[canHwChannel].data[0])) = (vuint32)*((CanChipDataPtr32)&(pFlexCANLocal->canObject[rxObjHandle].data[0])); /* PRQA S 0310 */ /* MD_Can_0310 */ /* SBSW_CAN_LL004 */
  *((CanChipDataPtr32)&(canRxMsgBuffer[canHwChannel].data[4])) = (vuint32)*((CanChipDataPtr32)&(pFlexCANLocal->canObject[rxObjHandle].data[4])); /* PRQA S 0310 */ /* MD_Can_0310 */ /* SBSW_CAN_LL004 */
  #endif
  
  #if defined( C_ENABLE_INDIVIDUAL_BUFFER_MASKING )
  /* to unlock only the current receive buffer the timestamp of another not-Rx message object must be read
   * reading the global timer results in a global unlock of all receive buffers */
  canRxMsgBuffer[canHwChannel].timestamp = pFlexCANLocal->canObject[CAN_HW_TX_NORMAL_INDEX(canHwChannel)].timestamp; /* unlock current receive buffer */ /* SBSW_CAN_LL004 */
  #endif
  
  #if defined( C_ENABLE_PROTECTED_RX_PROCESS )
  CanNestedGlobalInterruptRestore(); /* SBSW_CAN_LL002 */
  #endif
  
  #if defined( C_ENABLE_HW_LOOP_TIMER )
  if(loopResult == 0)
  {    
    goto finishRxFullCan; /* loop was aborted! don't process this message */
  }
  #endif
  
  

# if defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
  /* pointer needed for other modules */
  pCanRxInfoStruct =  &canRxInfoStruct[channel];
  (pCanRxInfoStruct->pChipMsgObj) = (CanChipMsgPtr) &(canRxMsgBuffer[canHwChannel].control); /* PRQA S 0310 */ /* MD_Can_0310 */
  (pCanRxInfoStruct->pChipData) = (CanChipDataPtr) &(canRxMsgBuffer[canHwChannel].data[0]);
  canRDSRxPtr[channel] = pCanRxInfoStruct->pChipData;
# else
  (canRxInfoStruct[channel].pChipMsgObj) = (CanChipMsgPtr) &(canRxMsgBuffer[canHwChannel].control); /* PRQA S 0310 */ /* MD_Can_0310 */
  (canRxInfoStruct[channel].pChipData) = (CanChipDataPtr) &(canRxMsgBuffer[canHwChannel].data[0]);
  canRDSRxPtr[channel] = canRxInfoStruct[channel].pChipData;
# endif

# if defined( C_ENABLE_CAN_RAM_CHECK )
  if(canComStatus[channel] == kCanDisableCommunication)
  {
    goto finishRxFullCan; /* ignore reception */
  }
# endif

#  if defined( C_ENABLE_FULLCAN_OVERRUN )

  if ((canRxMsgBuffer[canHwChannel].control & kCodeMask) == kRxCodeOverrun) 
  {
     ApplCanFullCanOverrun( CAN_CHANNEL_CANPARA_ONLY );
  }
#  endif



# if defined( C_ENABLE_COND_RECEIVE_FCT )
  /* ************************** conditional message receive function  ************************************** */
  if(canMsgCondRecState[channel]==kCanTrue)
  {
    ApplCanMsgCondReceived( CAN_HL_P_RX_INFO_STRUCT(channel) );
  }
# endif

# if defined( C_ENABLE_RECEIVE_FCT )
  /* ************************** call ApplCanMsgReceived() ************************************************** */
  if (APPL_CAN_MSG_RECEIVED( CAN_HL_P_RX_INFO_STRUCT(channel) )==kCanNoCopyData)
  {
     goto finishRxFullCan;
  }
# endif

  /* calculate the message handle to access the generated data for the received message */

  /* brackets to avoid lint info 834 */
  rxHandle = (rxObjHandle - CAN_HL_HW_RX_FULL_STARTINDEX(canHwChannel))
# if defined( C_SEARCH_HASH )
                         + kHashSearchListCount
                         + kHashSearchListCountEx
# endif
                         + CAN_HL_RX_FULL_STARTINDEX(canHwChannel);

# if defined( C_HL_ENABLE_ADJUST_RXHANDLE )
  if(rxObjHandle > 15)
  {
    rxHandle -= 2; /* ESCAN00048199: adjust the FullCAN hardware object handle for msg indirection */
  }
# endif

# if defined( C_ENABLE_RX_MSG_INDIRECTION ) || \
     defined( C_SEARCH_HASH ) || \
     defined( C_SEARCH_INDEX )
  rxHandle = CanRxMsgIndirection[rxHandle];
# endif

  assertInternal((rxHandle < kCanNumberOfRxObjects), kCanAllChannels, kErrorRxHandleWrong);  /* PRQA S 3109 */ /* legal rxHandle ? */

  CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel) = rxHandle;  

# if defined( C_ENABLE_RX_QUEUE )
  if (CanHL_ReceivedRxHandleQueue( CAN_CHANNEL_CANPARA_ONLY) == kCanHlContinueRx)
# else
  if (CanHL_ReceivedRxHandle( CAN_CHANNEL_CANPARA_ONLY ) == kCanHlContinueRx)
# endif
  { 
# if defined( C_ENABLE_INDICATION_FLAG ) || \
        defined( C_ENABLE_INDICATION_FCT )

    CanHL_IndRxHandle( rxHandle );


    return;
# endif
  }

  goto finishRxFullCan;     /* to avoid compiler warning */

/* Msg(4:2015) This label is not a case or default label for a switch statement. MISRA Rule 55 */
finishRxFullCan:

  /* make receive buffer free */


  return;    /* to avoid compiler warnings about label without code */
}
/* CODE CATEGORY 1 END */
/* PRQA L:End_CanFullCanMsgReceived */

#endif

#if defined( C_ENABLE_RX_FULLCAN_OBJECTS )  || \
    defined( C_ENABLE_RX_BASICCAN_OBJECTS )
# if ( kCanNumberOfRxObjects > 0 )
/* **************************************************************************
| NAME:             CanHL_ReceivedRxHandle
| CALLED BY:        CanBasicCanMsgReceived, CanFullCanMsgReceived
| PRECONDITIONS:
| INPUT PARAMETERS: Handle of received Message to access generated data
| RETURN VALUES:    none
| DESCRIPTION:      DLC-check, Precopy and copy of Data for received message
************************************************************************** */
/* CODE CATEGORY 1 START */
#  if defined( C_ENABLE_RX_QUEUE )
static vuint8 CanHL_ReceivedRxHandle( CAN_CHANNEL_CANTYPE_FIRST tCanRxInfoStruct *pCanRxInfoStruct )
{
#  else
static vuint8 CanHL_ReceivedRxHandle( CAN_CHANNEL_CANTYPE_ONLY )
{
#  endif
#  if !defined( C_ENABLE_RX_QUEUE ) &&\
    defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
  tCanRxInfoStruct    *pCanRxInfoStruct;
#  endif

#  if defined( C_ENABLE_COPY_RX_DATA )
#   if C_SECURITY_LEVEL > 20
  CanDeclareGlobalInterruptOldStatus
#   endif
#  endif

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(channel < kCanNumberOfChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);  /* PRQA S 3109 */
# endif

#  if !defined( C_ENABLE_RX_QUEUE ) &&\
    defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )
  pCanRxInfoStruct =  &canRxInfoStruct[channel];
#  endif

#  if defined( C_ENABLE_MULTI_ECU_PHYS )
  if ( (CanRxIdentityAssignment[CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)] & V_ACTIVE_IDENTITY_MSK) == (tVIdentityMsk)0 )
  {
    /* message is not a receive message in the active indentity */
    CANDRV_SET_CODE_TEST_POINT(0x10B);
    return  kCanHlFinishRx;
  }
#  endif


#  if defined( C_ENABLE_DLC_CHECK )  
#   if defined( C_ENABLE_DLC_CHECK_MIN_DATALEN )
  if ( (CanGetRxMinDataLen(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel))) > CanRxActualDLC( CAN_HL_P_RX_INFO_STRUCT(channel) ) )
#   else
  if ( (CanGetRxDataLen(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel))) > CanRxActualDLC( CAN_HL_P_RX_INFO_STRUCT(channel) ) )
#   endif
  {
    /* ##RI1.4 - 2.7: Callbackfunction-DLC-Check */
#   if defined( C_ENABLE_DLC_FAILED_FCT )
    ApplCanMsgDlcFailed( CAN_HL_P_RX_INFO_STRUCT(channel) ); 
#   endif  /* C_ENABLE_DLC_FAILED_FCT */
    return  kCanHlFinishRx;
  }
#  endif

#  if defined( C_ENABLE_VARIABLE_RX_DATALEN )
  CanSetVariableRxDatalen (CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel), CanRxActualDLC( CAN_HL_P_RX_INFO_STRUCT(channel)));
#  endif

#  if defined( C_ENABLE_GENERIC_PRECOPY )
  if ( APPL_CAN_GENERIC_PRECOPY( CAN_HL_P_RX_INFO_STRUCT(channel) ) != kCanCopyData)
  {
    return kCanHlFinishRx;  
  }
#  endif

#  if defined( C_ENABLE_PRECOPY_FCT )
#   if defined( C_HL_ENABLE_DUMMY_FCT_CALL )
#   else
  if ( CanGetApplPrecopyPtr(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)) != V_NULL )    /* precopy routine */
#   endif
  {
    /* canRxHandle in indexed drivers only for consistancy check in higher layer modules */
    canRxHandle[channel] = CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel);
    
    if ( CanGetApplPrecopyPtr(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel))( CAN_HL_P_RX_INFO_STRUCT(channel) )==kCanNoCopyData )
    {  /* precopy routine returns kCanNoCopyData:   */
      return  kCanHlFinishRx;
    }                      /* do not copy data check next irpt */
  }
#  endif

#  if defined( C_ENABLE_COPY_RX_DATA )
  /* no precopy or precopy returns kCanCopyData : copy data -- */
  /* copy via index ------------------------------------------- */
  if ( CanGetRxDataPtr(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)) != V_NULL )      /* copy if buffer exists */
  {
    /* copy data --------------------------------------------- */
#   if C_SECURITY_LEVEL > 20
    CanNestedGlobalInterruptDisable();
#   endif
    CANDRV_SET_CODE_TEST_POINT(0x107);
#   if defined( C_ENABLE_COPY_RX_DATA_WITH_DLC )
    if ( CanRxActualDLC( CAN_HL_P_RX_INFO_STRUCT(channel)) < CanGetRxDataLen(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)) )
    {
#    if defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )    
      CanLL_CopyFromCan(CanGetRxDataPtr(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)), pCanRxInfoStruct->pChipData, CanRxActualDLC(CAN_HL_P_RX_INFO_STRUCT(channel)));
#    else
      CanLL_CopyFromCan(CanGetRxDataPtr(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)), canRxInfoStruct[channel].pChipData, CanRxActualDLC(CAN_HL_P_RX_INFO_STRUCT(channel)));
#    endif 
    }
    else
#   endif   /* C_ENABLE_COPY_RX_DATA_WITH_DLC */
    {
#   if defined( C_HL_ENABLE_RX_INFO_STRUCT_PTR )    
      CanLL_CopyFromCan(CanGetRxDataPtr(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)), pCanRxInfoStruct->pChipData, CanGetRxDataLen(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)));
#   else
      CanLL_CopyFromCan(CanGetRxDataPtr(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)), canRxInfoStruct[channel].pChipData, CanGetRxDataLen(CAN_HL_P_RX_INFO_STRUCT_HANDLE(channel)));
#   endif 
    }
#   if C_SECURITY_LEVEL > 20
    CanNestedGlobalInterruptRestore();
#   endif
  }
#  endif /* ( C_ENABLE_COPY_RX_DATA ) */

  CANDRV_SET_CODE_TEST_POINT(0x105);
  return kCanHlContinueRx;
} /* end of CanReceivceRxHandle() */
/* CODE CATEGORY 1 END */

#  if defined( C_ENABLE_INDICATION_FLAG ) || \
     defined( C_ENABLE_INDICATION_FCT )
/* **************************************************************************
| NAME:             CanHL_IndRxHandle
| CALLED BY:        CanBasicCanMsgReceived, CanFullCanMsgReceived
| PRECONDITIONS:
| INPUT PARAMETERS: Handle of received Message to access generated data
| RETURN VALUES:    none
| DESCRIPTION:      DLC-check, Precopy and copy of Data for received message
************************************************************************** */
/* CODE CATEGORY 1 START */
static void CanHL_IndRxHandle( CanReceiveHandle rxHandle )
{
#   if defined( C_ENABLE_INDICATION_FLAG )
#    if C_SECURITY_LEVEL > 20
  CanDeclareGlobalInterruptOldStatus
#    endif
#   endif

#   if defined( C_ENABLE_INDICATION_FLAG )
#    if C_SECURITY_LEVEL > 20
  CanNestedGlobalInterruptDisable();
#    endif
  CanIndicationFlags._c[CanGetIndicationOffset(rxHandle)] |= CanGetIndicationMask(rxHandle);
#    if C_SECURITY_LEVEL > 20
  CanNestedGlobalInterruptRestore();
#    endif
#   endif

#   if defined( C_ENABLE_INDICATION_FCT )
#    if defined( C_HL_ENABLE_DUMMY_FCT_CALL )
#    else
  if ( CanGetApplIndicationPtr(rxHandle) != V_NULL )
#    endif
  {
    CanGetApplIndicationPtr(rxHandle)(rxHandle);  /* call IndicationRoutine */
  }
#   endif
}
/* CODE CATEGORY 1 END */
#  endif /* C_ENABLE_INDICATION_FLAG || C_ENABLE_INDICATION_FCT  */
# endif /* ( kCanNumberOfRxObjects > 0 ) */
#endif


/* **************************************************************************
| NAME:             CanHL_TxConfirmation
| CALLED BY:        CanISR()
| PRECONDITIONS:
| INPUT PARAMETERS: - internal can chip number
|                   - interrupt ID
| RETURN VALUES:    none
| DESCRIPTION:      - full can transmit
************************************************************************** */
/* PRQA S 2001 End_CanHL_TxConfirmation */    /* suppress misra message about usage of goto */
/* CODE CATEGORY 1 START */
static void CanHL_TxConfirmation( CAN_HW_CHANNEL_CANTYPE_FIRST CanObjectHandle txObjHandle)
{
  CanObjectHandle       logTxObjHandle;
  CanTransmitHandle     txHandle;

 
#if defined( C_ENABLE_TRANSMIT_QUEUE )
  CanSignedTxHandle         queueElementIdx;    /* use as signed due to loop */
  CanSignedTxHandle         elementBitIdx;
  tCanQueueElementType             elem;
  CanDeclareGlobalInterruptOldStatus
#else
# if defined( C_ENABLE_CONFIRMATION_FLAG )
#  if C_SECURITY_LEVEL > 20
  CanDeclareGlobalInterruptOldStatus
#  endif
# endif
#endif


#if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION ) && \
    defined( C_ENABLE_TRANSMIT_QUEUE )
  vuint8 rc;
#endif



# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(canHwChannel < kCanNumberOfHwChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);  /* PRQA S 3109 */
# endif



  logTxObjHandle = (CanObjectHandle)((vsintx)txObjHandle + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel));
  txHandle = canHandleCurTxObj[logTxObjHandle];           /* get saved handle */

  {
    #if defined( C_ENABLE_MAX_BUFFER_64 )
    if(txObjHandle > 31)
    {
      #if defined( C_CAN_MAX_BUFFER_MIXED )
      assertHardware((CanMaxMB[canHwChannel] == 64), canHwChannel, kCanInvalidHwObjHandle);
      #endif      
      pFlexCAN(canHwChannel)->iflag_hi = CanBitMask(txObjHandle); /* clear pending interrupt flag */ /* SBSW_CAN_LL005 */
    }
    else
    #endif
    {
      pFlexCAN(canHwChannel)->iflag_lo = CanBitMask(txObjHandle); /* clear pending interrupt flag */ /* SBSW_CAN_LL005 */
    }


    /* check associated transmit handle */
    if (txHandle == kCanBufferFree)
    {
      assertInternal (0, channel, kErrorTxHandleWrong);          /* PRQA S 3109 */ /* lint !e506 !e774 */
      goto finishCanHL_TxConfirmation;
    }  

#if defined( C_ENABLE_TX_OBSERVE ) || \
    defined( C_ENABLE_CAN_TX_CONF_FCT )
# if defined( C_ENABLE_CANCEL_IN_HW )
    /* something todo for ASR, maybe OK or if (1):
    if (CanLL_TxIsHWObjFree(canHwChannel, txObjHandle)) */
# endif
    {
# if defined( C_ENABLE_TX_OBSERVE )
      {
        ApplCanTxObjConfirmed( CAN_CHANNEL_CANPARA_FIRST logTxObjHandle );
      }
# endif

# if defined( C_ENABLE_CAN_TX_CONF_FCT )
/* ##RI-1.10 Common Callbackfunction in TxInterrupt */
        txInfoStructConf[channel].Handle  = txHandle;
        txInfoStructConf[channel].pChipData = (CanChipDataPtr)&(pFlexCAN(canHwChannel)->canObject[txObjHandle].data[0]);
        txInfoStructConf[channel].pChipMsgObj = (CanChipMsgPtr)&(pFlexCAN(canHwChannel)->canObject[txObjHandle].control);
        APPL_CAN_TX_CONFIRMATION(&txInfoStructConf[channel]);
# endif
    }
#endif /* defined( C_ENABLE_TX_OBSERVE ) || defined( C_ENABLE_CAN_TX_CONF_FCT ) */

#if defined( C_ENABLE_TRANSMIT_QUEUE )
# if defined( C_ENABLE_TX_FULLCAN_OBJECTS )  || \
     defined( C_ENABLE_MSG_TRANSMIT )
    if (txObjHandle != CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel))
    {
      canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;                 /* free msg object of FullCAN or LowLevel Tx obj. */
    }
# endif
#else
    canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;                   /* free msg object if queue is not used */
#endif

    if (txHandle != kCanBufferCancel)
    {
#if defined( C_ENABLE_MSG_TRANSMIT )
      if (txObjHandle == CAN_HL_HW_MSG_TRANSMIT_INDEX(canHwChannel))
      {
# if defined( C_ENABLE_MSG_TRANSMIT_CONF_FCT )
        APPL_CAN_MSGTRANSMITCONF( CAN_CHANNEL_CANPARA_ONLY );
# endif

        goto finishCanHL_TxConfirmation;
      }
#endif

#if defined( C_ENABLE_MULTI_ECU_PHYS )
      assertInternal(((CanTxIdentityAssignment[txHandle] & V_ACTIVE_IDENTITY_MSK) != (tVIdentityMsk)0 ), 
                                                                channel, kErrorInternalDisabledTxMessage);  /* PRQA S 3109 */
#endif

#if defined( C_ENABLE_CONFIRMATION_FLAG )       /* set transmit ready flag  */
# if C_SECURITY_LEVEL > 20
      CanNestedGlobalInterruptDisable();
# endif
      CanConfirmationFlags._c[CanGetConfirmationOffset(txHandle)] |= CanGetConfirmationMask(txHandle);
# if C_SECURITY_LEVEL > 20
      CanNestedGlobalInterruptRestore();
# endif
#endif

#if defined( C_ENABLE_CONFIRMATION_FCT )
      {
# if defined( C_HL_ENABLE_DUMMY_FCT_CALL )
# else
        if ( CanGetApplConfirmationPtr(txHandle) != V_NULL )
# endif
        {
          (CanGetApplConfirmationPtr(txHandle))(txHandle);   /* call completion routine  */
        }
      }
#endif /* C_ENABLE_CONFIRMATION_FCT */

    } /* end if kCanBufferCancel */
  
#if defined( C_ENABLE_TRANSMIT_QUEUE )
# if defined( C_ENABLE_TX_FULLCAN_OBJECTS ) ||\
     defined( C_ENABLE_MSG_TRANSMIT )
    if (txObjHandle == CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel)) 
# endif
    {
      CanNestedGlobalInterruptDisable();                /* ESCAN00008914 */

      for(queueElementIdx = CAN_HL_TXQUEUE_STOPINDEX(channel) - (CanSignedTxHandle)1; 
                               queueElementIdx >= CAN_HL_TXQUEUE_STARTINDEX(channel); queueElementIdx--)
      {
        elem = canTxQueueFlags[queueElementIdx];
        if(elem != (tCanQueueElementType)0) /* is there any flag set in the queue element? */
        {

          CanNestedGlobalInterruptRestore();

          /* start the bitsearch */
          #if defined( C_CPUTYPE_32BIT )
          if((elem & (tCanQueueElementType)0xFFFF0000) != (tCanQueueElementType)0)
          {
            if((elem & (tCanQueueElementType)0xFF000000) != (tCanQueueElementType)0)
            {
              if((elem & (tCanQueueElementType)0xF0000000) != (tCanQueueElementType)0)
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 28] + 28;
              }
              else /* 0x0F000000 */
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 24] + 24;
              }
            }
            else
            {
              if((elem & (tCanQueueElementType)0x00F00000) != (tCanQueueElementType)0)
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 20] + 20;
              }
              else /* 0x000F0000 */
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 16] + 16;
              }
            }
          }
          else
          #endif
          {
          #if defined( C_CPUTYPE_32BIT ) 
            if((elem & (tCanQueueElementType)0x0000FF00) != (tCanQueueElementType)0)
            {
              if((elem & (tCanQueueElementType)0x0000F000) != (tCanQueueElementType)0)
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 12] + 12;
              }
              else /* 0x00000F00 */
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 8] + 8;
              }
            }
            else
          #endif
            {
              if((elem & (tCanQueueElementType)0x000000F0) != (tCanQueueElementType)0)
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem >> 4] + 4;
              }
              else /* 0x0000000F */
              {
                elementBitIdx = (CanSignedTxHandle)CanGetHighestFlagFromNibble[elem];
              }
            }
          }
          txHandle = (CanTransmitHandle)((((CanTransmitHandle)queueElementIdx << kCanTxQueueShift) + (CanTransmitHandle)elementBitIdx) - CAN_HL_TXQUEUE_PADBITS(channel));
          {

              /* compute the logical message handle */
              CanNestedGlobalInterruptDisable();
 
              if ( (canTxQueueFlags[queueElementIdx] & CanShiftLookUp[elementBitIdx]) != (tCanQueueElementType)0 )
              {
                canTxQueueFlags[queueElementIdx] &= (tCanQueueElementType)~CanShiftLookUp[elementBitIdx]; /* clear flag from the queue */

                CanNestedGlobalInterruptRestore();  
                canHandleCurTxObj[logTxObjHandle] = txHandle; /* Save hdl of msgObj to be transmitted */
# if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
                rc = CanCopyDataAndStartTransmission( CAN_CHANNEL_CANPARA_FIRST txObjHandle, txHandle); 
                if ( rc == kCanTxNotify)
                {
                  APPLCANCANCELNOTIFICATION(channel, txHandle);
                }
# else       /* C_ENABLE_CAN_CANCEL_NOTIFICATION */
                (void)CanCopyDataAndStartTransmission( CAN_CHANNEL_CANPARA_FIRST txObjHandle, txHandle); 
# endif /* C_ENABLE_CAN_CANCEL_NOTIFICATION */

                goto finishCanHL_TxConfirmation;
              }
              /* meanwhile, the queue is empty. E.g. due to CanOffline on higher level */
              canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;  /* free msg object if queue is empty */
              CanNestedGlobalInterruptRestore();  
              goto finishCanHL_TxConfirmation;
            
          }
          /* no entry found in Queue */
# if defined( CANHL_TX_QUEUE_BIT )
# else
          CanNestedGlobalInterruptDisable();                /* lint !e527 ESCAN00008914 */
                                                 /* unreachable in case of Bit-Queue */
# endif                                                 
        }
      }

      canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;  /* free msg object if queue is empty */
      CanNestedGlobalInterruptRestore();                 /* ESCAN00008914 */
    }
#endif
  /* check for next msg object in queue and transmit it */

/* Msg(4:2015) This label is not a case or default label for a switch statement. MISRA Rule 55 */
finishCanHL_TxConfirmation:
    ;

  }
  return;

} /* END OF CanTxInterrupt */
/* CODE CATEGORY 1 END */
/* PRQA L:End_CanHL_TxConfirmation */


#if defined( C_ENABLE_ECU_SWITCH_PASS )
/* **********************************************************************
* NAME:               CanSetActive
* CALLED BY:          application
* PRECONDITIONS:      none
* PARAMETER:          none or channel
* RETURN VALUE:       none
* DESCRIPTION:        Set the CAN driver into active mode
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetActive( CAN_CHANNEL_CANTYPE_ONLY )
{
#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);     /* PRQA S 3109 */
#endif

  canPassive[channel] = 0;
} /* END OF CanSetActive */
/* CODE CATEGORY 4 END */

/* **********************************************************************
* NAME:               CanSetPassive
* CALLED BY:          application
* PRECONDITIONS:      none
* PARAMETER:          none or channel
* RETURN VALUE:       none
* DESCRIPTION:        Set the can driver into passive mode
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetPassive( CAN_CHANNEL_CANTYPE_ONLY )
{
#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);      /* PRQA S 3109 */
#endif

  canPassive[channel] = 1;
 
# if defined( C_ENABLE_TRANSMIT_QUEUE )
  /* clear all Tx queue flags: */
  CanDelQueuedObj( CAN_CHANNEL_CANPARA_ONLY ); 
# endif
 

} /* END OF CanSetPassive */
/* CODE CATEGORY 4 END */
#endif /* IF defined( C_ENABLE_ECU_SWITCH_PASS ) */


#if defined( C_ENABLE_OFFLINE )
/* **********************************************************************
* NAME:               CanOnline( CanChannelHandle channel )
* CALLED BY:          netmanagement
* PRECONDITIONS:      none
* PARAMETER:          none or channel
* RETURN VALUE:       none
* DESCRIPTION:        Switch on transmit path
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanOnline(CAN_CHANNEL_CANTYPE_ONLY)
{
  CanDeclareGlobalInterruptOldStatus

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);    /* PRQA S 3109 */
#endif
  {

    CanNestedGlobalInterruptDisable();

    canStatus[channel] |= kCanTxOn;

#   if defined( C_ENABLE_ONLINE_OFFLINE_CALLBACK_FCT )
    APPL_CAN_ONLINE(CAN_CHANNEL_CANPARA_ONLY);
#   endif
    CanNestedGlobalInterruptRestore();
  }

}
/* CODE CATEGORY 4 END */


/* **********************************************************************
* NAME:               CanOffline( CanChannelHandle channel )
* CALLED BY:          netmanagement
* PRECONDITIONS:      none
* PARAMETER:          none or channel
* RETURN VALUE:       none
* DESCRIPTION:        Switch off transmit path
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanOffline(CAN_CHANNEL_CANTYPE_ONLY) C_API_3
{
  CanDeclareGlobalInterruptOldStatus

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);     /* PRQA S 3109 */
#endif

  CanNestedGlobalInterruptDisable();

  canStatus[channel] &= kCanTxNotOn;

# if defined( C_ENABLE_ONLINE_OFFLINE_CALLBACK_FCT )
  APPL_CAN_OFFLINE(CAN_CHANNEL_CANPARA_ONLY);
# endif
  CanNestedGlobalInterruptRestore();

# if defined( C_ENABLE_TRANSMIT_QUEUE )
  CanDelQueuedObj( CAN_CHANNEL_CANPARA_ONLY );
# endif

}
/* CODE CATEGORY 4 END */
#endif /* if defined( C_ENABLE_OFFLINE ) */


#if defined( C_ENABLE_PART_OFFLINE )
/* **********************************************************************
* NAME:               CanSetPartOffline
* CALLED BY:          application
* PRECONDITIONS:      none
* PARAMETER:          (channel), sendGroup
* RETURN VALUE:       none
* DESCRIPTION:        Switch partial off transmit path
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetPartOffline(CAN_CHANNEL_CANTYPE_FIRST vuint8 sendGroup)
{
  CanDeclareGlobalInterruptOldStatus

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);    /* PRQA S 3109 */
#endif

  CanNestedGlobalInterruptDisable();
  canTxPartOffline[channel] |= sendGroup;   /* set offlinestate and Save for use of CanOnline/CanOffline */
  CanNestedGlobalInterruptRestore();
}
/* CODE CATEGORY 4 END */


/* **********************************************************************
* NAME:               CanSetPartOnline
* CALLED BY:          application
* PRECONDITIONS:      none
* PARAMETER:          (channel), invSendGroup
* RETURN VALUE:       none
* DESCRIPTION:        Switch partial on transmit path
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetPartOnline(CAN_CHANNEL_CANTYPE_FIRST vuint8 invSendGroup)
{
  CanDeclareGlobalInterruptOldStatus

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);    /* PRQA S 3109 */
#endif

  CanNestedGlobalInterruptDisable();
  canTxPartOffline[channel] &= invSendGroup;
  CanNestedGlobalInterruptRestore();
}
/* CODE CATEGORY 4 END */


/* **********************************************************************
* NAME:               CanGetPartMode
* CALLED BY:          application
* PRECONDITIONS:      none
* PARAMETER:          none or channel
* RETURN VALUE:       canTxPartOffline
* DESCRIPTION:        return status of partoffline-Mode
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanGetPartMode(CAN_CHANNEL_CANTYPE_ONLY)
{
#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);   /* PRQA S 3109 */
#endif

  return canTxPartOffline[channel];
}
/* CODE CATEGORY 4 END */
#endif


/* **************************************************************************
| NAME:             CanGetStatus
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: none or channel
| RETURN VALUES:    Bit coded status (more than one status can be set):
|                   kCanTxOn
|                   kCanHwIsStop        
|                   kCanHwIsInit        
|                   kCanHwIsInconsistent
|                   kCanHwIsWarning     
|                   kCanHwIsPassive     
|                   kCanHwIsBusOff      
|                   kCanHwIsSleep       
| DESCRIPTION:      returns the status of the transmit path and the CAN hardware.
|                   Only one of the statusbits Sleep, Busoff, Passiv, Warning is set.
|                   Sleep has the highest priority, error warning the lowerst. 
************************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 vuint8 C_API_2 CanGetStatus( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3
{
#if defined( C_ENABLE_EXTENDED_STATUS )
#endif


#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);    /* PRQA S 3109 */
#endif

#if defined( C_ENABLE_EXTENDED_STATUS )

# if defined( C_ENABLE_SLEEP_WAKEUP )
  /* *************************** verify Sleep mode *********************************** */
  if ( CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY)   )  { return ( VUINT8_CAST ( canStatus[channel] | kCanHwIsSleep ) ); }

# endif

  /* *************************** verify Stop mode *********************************** */
  if ( CanLL_HwIsStop(CAN_HW_CHANNEL_CANPARA_ONLY)    )  { return ( VUINT8_CAST ( canStatus[channel] | kCanHwIsStop ) ); }

  /* *************************** verify Busoff *********************************** */
  if ( CanLL_HwIsBusOff(CAN_HW_CHANNEL_CANPARA_ONLY)  )  { return ( VUINT8_CAST ( canStatus[channel] | kCanHwIsBusOff ) ); }

  /* *************************** verify Error Passiv ***************************** */
  {
    if ( CanLL_HwIsPassive(CAN_HW_CHANNEL_CANPARA_ONLY) )  { return ( VUINT8_CAST ( canStatus[channel] | kCanHwIsPassive ) ); }
  }

  /* *************************** verify Error Warning **************************** */
  {
    if ( CanLL_HwIsWarning(CAN_HW_CHANNEL_CANPARA_ONLY) )  { return ( VUINT8_CAST ( canStatus[channel] | kCanHwIsWarning ) ); }
  }
#endif
  return ( VUINT8_CAST (canStatus[channel] & kCanTxOn) );

} /* END OF CanGetStatus */
/* CODE CATEGORY 3 END */


/* **************************************************************************
| NAME:             CanSleep
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: none or channel
| RETURN VALUES:    kCanOk, if CanSleep was successfull
|                   kCanFailed, if function failed
|                   kCanNotSupported, if this function is not supported
| DESCRIPTION:      disable CAN 
************************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanSleep(CAN_CHANNEL_CANTYPE_ONLY)
{
#if defined( C_ENABLE_SLEEP_WAKEUP )
  vuint8         canReturnCode;
#endif

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);   /* PRQA S 3109 */
#endif
#if defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL) && !defined (C_ENABLE_OSEK_CAN_INTCTRL)
  assertUser((canCanInterruptCounter[channel] == (vsintx)0), channel, kErrorDisabledCanInt);    /* PRQA S 3109 */
#endif

#if defined( C_ENABLE_COND_RECEIVE_FCT )
  /* this has to be done, even if SLEEP_WAKEUP is not enabled */
  canMsgCondRecState[channel] = kCanTrue;
#endif

#if defined( C_ENABLE_SLEEP_WAKEUP )

  assertUser((canStatus[channel] & kCanTxOn) != kCanTxOn, channel, kErrorCanOnline);   /* PRQA S 3109 */

  {
    assertUser(!CanLL_HwIsStop(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanStop);     /* PRQA S 3109 */
    {
      vuint8      loopResult;
      tFlexcanPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* pointer to FlexCAN channel object */
      
      CanMicroModeSystem();
    
      
      # if defined( C_ENABLE_FLEXCAN_DOZE_MODE )
      CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_DOZE); /* allow FlexCAN to enter DOZE mode */
      loopResult = Appl_CanSleep( CAN_CHANNEL_CANPARA_ONLY );
      if(loopResult == kCanOk)
      {
        canReturnCode = kCanOk;
      }
      else
      {
        CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_DOZE);
        canReturnCode = kCanFailed;
      }
      # else
      CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_HALT); /* clear HALT bit */  
      CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_FRZ);  /* clear FRZ bit */    
      CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_MDIS);     /* request the DISABLE mode */
    
      CanLL_ApplCanTimerStart(kCanLoopEnterDisableMode);
      do{
          loopResult = CanLL_ApplCanTimerLoop(kCanLoopEnterDisableMode);
        }while(((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_MCR) != kFlexCAN_DISABLE_MODE) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */
      CanLL_ApplCanTimerEnd(kCanLoopEnterDisableMode);
    
      if(loopResult != 0) /* PRQA S 3355 */ /* MD_Can_13.7 */
      {
        canReturnCode = kCanOk;
      }
      else
      {
        CAN_CLEAR_MDIS(); /* request the NORMAL mode */  
        canReturnCode = kCanFailed;  
      }  
      # endif
    
      CanMicroModeRestore();
    }
  }
  return canReturnCode;
#else
# if defined( C_MULTIPLE_RECEIVE_CHANNEL ) && \
     defined( V_ENABLE_USE_DUMMY_STATEMENT )
  channel = channel;
# endif
  return kCanNotSupported;
#endif
} /* END OF CanSleep */
/* CODE CATEGORY 4 END */

/* **************************************************************************
| NAME:             CanWakeUp
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: none or channel
| RETURN VALUES:    kCanOk, if CanWakeUp was successfull
|                   kCanFailed, if function failed
|                   kCanNotSupported, if this function is not supported
| DESCRIPTION:      enable CAN 
************************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanWakeUp( CAN_CHANNEL_CANTYPE_ONLY )
{
#if defined( C_ENABLE_SLEEP_WAKEUP )
  vuint8         canReturnCode;


#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);     /* PRQA S 3109 */
#endif
#if defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL) && !defined (C_ENABLE_OSEK_CAN_INTCTRL)
  assertUser((canCanInterruptCounter[channel] == (vsintx)0), channel, kErrorDisabledCanInt);    /* PRQA S 3109 */
#endif

  {
    tFlexcanPtr pFlexCANLocal = pFlexCAN(canHwChannel); /* pointer to FlexCAN channel object */
    
    #if defined( C_ENABLE_FLEXCAN_DOZE_MODE )
    CanMicroModeSystem();
    CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_DOZE); /* exit the DOZE mode */
    pFlexCANLocal->estat = kFlexCAN_WAKE_INT; /* clear pending wakeup interrupt flag */
    canReturnCode = kCanOk;
    #else
    vuint8 loopResult;
    CanMicroModeSystem();
    
    CAN_CLEAR_MDIS(); /* quit DISABLE mode and switch into NORMAL mode */
    CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_HALT); /* clear HALT bit */      
    CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_FRZ);  /* clear FRZ bit  */ 
    
    CanLL_ApplCanTimerStart(kCanLoopEnterNormalMode);
    do{
        loopResult = CanLL_ApplCanTimerLoop(kCanLoopEnterNormalMode);
      }while(((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_MCR) != (vuint16)0) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */
    CanLL_ApplCanTimerEnd(kCanLoopEnterNormalMode);
    
    if(loopResult != 0) /* PRQA S 3355 */ /* MD_Can_13.7 */
    {
      canReturnCode = kCanOk;
    }
    else
    {
      canReturnCode = kCanFailed;  
    }
    #endif
    CanMicroModeRestore();
  }
  return canReturnCode;
#else
# if defined( C_MULTIPLE_RECEIVE_CHANNEL ) && \
     defined( V_ENABLE_USE_DUMMY_STATEMENT )
  channel = channel;
# endif
  return kCanNotSupported;
#endif /* C_ENABLE_SLEEP_WAKEUP */
} /* END OF CanWakeUp */
/* CODE CATEGORY 4 END */


#if defined( C_ENABLE_STOP )
/* **************************************************************************
| NAME:             CanStop
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    kCanOk, if success
|                   kCanFailed, if function failed
|                   kCanNotSupported, if this function is not supported
| DESCRIPTION:      stop CAN-controller
************************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanStop( CAN_CHANNEL_CANTYPE_ONLY )
{
  vuint8         canReturnCode;

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);   /* PRQA S 3109 */
# endif
  assertUser((canStatus[channel] & kCanTxOn) != kCanTxOn, channel, kErrorCanOnline);   /* PRQA S 3109 */

  {
# if defined( C_ENABLE_SLEEP_WAKEUP )
    assertUser(!CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanSleep);   /* PRQA S 3109 */
# endif
    {
      vuint8           loopResult;
      vuint16          hwObjHandle;
      CanObjectHandle  logTxObjHandle;
      tFLEXCANPtr      pFlexCANLocal;
      #if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION ) || defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
      CanTransmitHandle txHandle;
      #endif      
                        
      CanMicroModeSystem();
      pFlexCANLocal = pFLEXCAN(canHwChannel); 
    
      CAN_CLEAR_MDIS(); /* clear MDIS bit */
      CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_FRZ);  /* set FRZ bit */
      CAN_WRITE_PROTECTED_REG_SET(pFlexCANLocal->canmcr, kFlexCAN_HALT); /* set HALT bit */
    
      CanLL_ApplCanTimerStart(kCanLoopEnterFreezeMode); /* start hw loop timer */
      do  
      { /* wait for FRZACK */  
        loopResult = CanLL_ApplCanTimerLoop(kCanLoopEnterFreezeMode);  
      }while(((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_MCR) != kFlexCAN_FREEZE_MODE) && (loopResult != 0));  /* PRQA S 3355 */ /* MD_Can_13.7 */
      CanLL_ApplCanTimerEnd(kCanLoopEnterFreezeMode); /* stop hw loop timer */
    
      if(loopResult != 0) /* PRQA S 3355 */ /* MD_Can_13.7 */
      {   
        pFlexCANLocal->iflag_lo = CANSFR_SET; /* clear pending Rx/Tx interrupts */
        # if defined( C_ENABLE_MAX_BUFFER_64 )
        #  if defined( C_CAN_MAX_BUFFER_MIXED )
        if(CanMaxMB[canHwChannel] == 64)    
        #  endif
        {
          pFlexCANLocal->iflag_hi = CANSFR_SET; /* clear pending Rx/Tx interrupts */    
        }
        # endif
        pFlexCANLocal->estat = (vuint32)0x0007; /* clear pending BusOff and error interrupts */
        # if !defined( C_ENABLE_FLEXCAN_AUTO_RECOVERY )
        pFlexCANLocal->control0 &= (vuint16)~(kFlexCAN_BOFF_REC); /* PRQA S 0277 */ /* MD_Can_0277_negation */
        # endif        
    
        {  
          for(hwObjHandle = CAN_HW_TX_STARTINDEX(canHwChannel); hwObjHandle < CAN_HW_TX_STOPINDEX(canHwChannel); hwObjHandle++)
          {
            logTxObjHandle = (CanObjectHandle)((vsintx)hwObjHandle + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel));      
            #if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION ) || defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
            /* inform application, if a pending transmission is canceled */
            txHandle = canHandleCurTxObj[logTxObjHandle];
            # if defined( C_ENABLE_CAN_CANCEL_NOTIFICATION )
            if(txHandle < kCanNumberOfTxObjects)
            {
              APPLCANCANCELNOTIFICATION(canHwChannel, txHandle);
            }
            # endif
            # if defined( C_ENABLE_CAN_MSG_TRANSMIT_CANCEL_NOTIFICATION )
            if(txHandle == kCanBufferMsgTransmit)
            { 
              APPLCANMSGCANCELNOTIFICATION(canHwChannel);
            } 
            # endif
            #endif
            canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;        
            pFlexCANLocal->canObject[hwObjHandle].control = kTxCodeInactive; /* set mailbox inactive */
          }
    
          #if defined ( C_ENABLE_RX_FULLCAN_OBJECTS )
          for(hwObjHandle = CAN_HW_RX_FULL_STARTINDEX(canHwChannel); hwObjHandle < CAN_HW_RX_FULL_STOPINDEX(canHwChannel); hwObjHandle++)
          {
            #if defined( C_ENABLE_FLEXCAN_RXFIFO ) && !defined( C_ENABLE_FLEXCAN_INDIV_RXMASK )
            if((hwObjHandle != 14) && (hwObjHandle != 15))       
            #endif
            {        
              pFlexCANLocal->canObject[hwObjHandle].control &= kRxCodeClear; /* clear control register and do not change the ID type */
              pFlexCANLocal->canObject[hwObjHandle].control |= kRxCodeEmpty; /* set mailbox ready for receive */
            }
          }
          #endif
    
          #if defined ( C_ENABLE_RX_BASICCAN_OBJECTS )
          # if defined( C_ENABLE_FLEXCAN_RXFIFO )
          pFlexCANLocal->canObject[0].control &= kRxCodeClear; /* clear control register and do not change the ID type */
          pFlexCANLocal->canObject[0].control |= kRxCodeEmpty; /* set mailbox ready for receive */
          # else
          for(hwObjHandle = CAN_HW_RX_BASIC_STARTINDEX(canHwChannel); hwObjHandle < CAN_HW_RX_BASIC_STOPINDEX(canHwChannel); hwObjHandle++)       
          {
            pFlexCANLocal->canObject[hwObjHandle].control &= kRxCodeClear; /* clear control register and do not change the ID type */
            pFlexCANLocal->canObject[hwObjHandle].control |= kRxCodeEmpty; /* set mailbox ready for receive */
          }
          # endif
          #endif
        }
        canReturnCode = kCanOk;
      }
      else
      {
        CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_HALT); /* clear HALT bit */      
        CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_FRZ);  /* clear FRZ bit  */ 
        
        canReturnCode = kCanFailed;
      }
      CanMicroModeRestore();
    }
  }
  return canReturnCode;
}
/* CODE CATEGORY 4 END */

/* **************************************************************************
| NAME:             CanStart
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    kCanOk, if success
|                   kCanFailed, if function failed
|                   kCanNotSupported, if this function is not supported
| DESCRIPTION:      restart CAN-controller
************************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 vuint8 C_API_2 CanStart( CAN_CHANNEL_CANTYPE_ONLY )
{
  vuint8         canReturnCode;

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);   /* PRQA S 3109 */
# endif

  {
    {
      vuint8       loopResult;
      tFlexcanPtr  pFlexCANLocal;
    
      CanMicroModeSystem();
    
      pFlexCANLocal = pFlexCAN(canHwChannel);  
    
      CAN_CLEAR_MDIS(); /* clear MDIS bit */
      CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_HALT); /* clear HALT bit */      
      CAN_WRITE_PROTECTED_REG_RESET(pFlexCANLocal->canmcr, kFlexCAN_FRZ);  /* clear FRZ bit  */ 
      
      #if !defined( C_ENABLE_FLEXCAN_AUTO_RECOVERY )
      pFlexCANLocal->control0 |= (vuint16)(kFlexCAN_BOFF_REC);
      #endif  
    
      CanLL_ApplCanTimerStart(kCanLoopEnterNormalMode); /* start hw loop timer  */
      do  
      { /* wait for NORMAL mode */  
        loopResult = CanLL_ApplCanTimerLoop(kCanLoopEnterNormalMode);
      }while(((CAN_READ_PROTECTED_REG(pFlexCANLocal->canmcr) & kFlexCAN_MCR) != 0) && (loopResult != 0)); /* PRQA S 3355 */ /* MD_Can_13.7 */
      CanLL_ApplCanTimerEnd(kCanLoopEnterNormalMode); /* stop hw loop timer */
    
      if(loopResult != 0) /* PRQA S 3355 */ /* MD_Can_13.7 */
      {
        canReturnCode = kCanOk;
      }
      else
      {
        canReturnCode = kCanFailed;  
      }
      
      CanMicroModeRestore();
    }
  }
  return canReturnCode;
}
/* CODE CATEGORY 4 END */
#endif /* if defined( C_ENABLE_STOP ) */

#if defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL)
/* **************************************************************************
| NAME:             CanCanInterruptDisable
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      disables CAN interrupts and stores old interrupt status
************************************************************************** */
/* CODE CATEGORY 1 START */
C_API_1 void C_API_2 CanCanInterruptDisable( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3
{
# if defined (C_ENABLE_OSEK_CAN_INTCTRL)

  {
    OsCanCanInterruptDisable(CAN_HW_CHANNEL_CANPARA_ONLY);
  }
# else  /* defined (C_ENABLE_OSEK_CAN_INTCTRL) */

  CanDeclareGlobalInterruptOldStatus
#  if defined( C_HL_ENABLE_CAN_IRQ_DISABLE )
#  endif

  /* local variable must reside on stack or registerbank, switched */
  /* in interrupt level                                            */
  /* disable global interrupt                                      */
#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);    /* PRQA S 3109 */
#  endif
  assertUser(canCanInterruptCounter[channel]<(vsint8)0x7f, kCanAllChannels, kErrorIntDisableTooOften);    /* PRQA S 3109 */

  CanNestedGlobalInterruptDisable();
  if (canCanInterruptCounter[channel] == (vsintx)0)  /* if 0 then save old interrupt status */
  {
#  if defined( C_HL_ENABLE_CAN_IRQ_DISABLE )
    {
#   if defined( C_ENABLE_SLEEP_WAKEUP )
      assertUser(!CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanSleep);     /* PRQA S 3109 */
#   endif

      CanLL_CanInterruptDisable(canHwChannel, &canCanInterruptOldStatus[canHwChannel]);
    }
#  endif
#  if defined( C_ENABLE_INTCTRL_ADD_CAN_FCT )
    ApplCanAddCanInterruptDisable(channel);
#  endif
  }
  canCanInterruptCounter[channel]++;               /* common for all platforms */

  CanNestedGlobalInterruptRestore();
# endif  /* C_ENABLE_OSEK_CAN_INTCTRL */
} /* END OF CanCanInterruptDisable */
/* CODE CATEGORY 1 END */

/* **************************************************************************
| NAME:             CanCanInterruptRestore
| CALLED BY:
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      restores the old interrupt status of the CAN interrupt if 
|                   canCanInterruptCounter[channel] is zero
************************************************************************** */
/* CODE CATEGORY 1 START */
C_API_1 void C_API_2 CanCanInterruptRestore( CAN_CHANNEL_CANTYPE_ONLY ) C_API_3
{
# if defined (C_ENABLE_OSEK_CAN_INTCTRL)

  {
    OsCanCanInterruptRestore(CAN_HW_CHANNEL_CANPARA_ONLY);
  }
# else  /* defined (C_ENABLE_OSEK_CAN_INTCTRL) */

  CanDeclareGlobalInterruptOldStatus
#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);     /* PRQA S 3109 */
#  endif
  assertUser(canCanInterruptCounter[channel]>(vsintx)0, kCanAllChannels, kErrorIntRestoreTooOften);   /* PRQA S 3109 */

  CanNestedGlobalInterruptDisable();
  /* restore CAN interrupt */
  canCanInterruptCounter[channel]--;

  if (canCanInterruptCounter[channel] == (vsintx)0)         /* restore interrupt if canCanInterruptCounter=0 */
  {
#  if defined( C_HL_ENABLE_CAN_IRQ_DISABLE )    
    {
#   if defined( C_ENABLE_SLEEP_WAKEUP )
      assertUser(!CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanSleep);   /* PRQA S 3109 */
#   endif

      CanLL_CanInterruptRestore(canHwChannel, canCanInterruptOldStatus[canHwChannel]);
    }
#  endif

#  if defined( C_ENABLE_INTCTRL_ADD_CAN_FCT )
    ApplCanAddCanInterruptRestore(channel);
#  endif
  }
  CanNestedGlobalInterruptRestore();
# endif  /* defined (C_ENABLE_OSEK_CAN_INTCTRL) */
} /* END OF CanCanInterruptRestore */
/* CODE CATEGORY 1 END */
#endif /* defined (C_ENABLE_CAN_CAN_INTERRUPT_CONTROL) */

#if defined( C_ENABLE_MSG_TRANSMIT )
/* **********************************************************************
* NAME:               CanMsgTransmit
* CALLED BY:          CanReceivedFunction
* PRECONDITIONS:      Called in Receive Interrupt
* PARAMETER:          Pointer to message buffer data block; This can either be
*                     a RAM structure data block or the receive buffer in the
*                     CAN chip
* RETURN VALUE:       The return value says that a transmit request was successful
*                     or not
* DESCRIPTION:        Transmit functions for gateway issues (with dynamic
*                     messages). If the transmit buffer is not free, the message
*                     is inserted in the FIFO ring buffer.
*********************************************************************** */
/* Msg(4:3673) The object addressed by the pointer "txMsgStruct" is not modified in this function.
   The use of "const" should be considered to indicate that it never changes. MISRA Rule 81 - no change */
/* CODE CATEGORY 2 START */
# if defined ( V_ENABLE_USED_GLOBAL_VAR )
/* txMsgStruct is located in far memory */
C_API_1 vuint8 C_API_2 CanMsgTransmit( CAN_CHANNEL_CANTYPE_FIRST V_MEMRAM1_FAR tCanMsgTransmitStruct V_MEMRAM2_FAR V_MEMRAM3_FAR *txMsgStruct )       /* PRQA S 3673 */      /* suppress message about const pointer */
{
# else
C_API_1 vuint8 C_API_2 CanMsgTransmit( CAN_CHANNEL_CANTYPE_FIRST tCanMsgTransmitStruct *txMsgStruct )       /* PRQA S 3673 */      /* suppress message about const pointer */
{
# endif
  CanDeclareGlobalInterruptOldStatus
  vuint8                 rc;
  CanObjectHandle          txObjHandle;
  CanObjectHandle          logTxObjHandle;

  #if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
  tFLEXCANPtr pFlexCANLocal;
  vuint32     canTxBuf[2];
  #else
  tFlexcanPtr pFlexCANLocal;
  #endif

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);     /* PRQA S 3109 */
# endif

  assertUser( (txMsgStruct != V_NULL), channel, kErrorNullPointerParameter);   /* PRQA S 3109 */


  CanNestedGlobalInterruptDisable();

  /* --- test on CAN transmit switch --- */
  if ( (canStatus[channel] & kCanTxOn) != kCanTxOn )                /* transmit path switched off */
  {
    CanNestedGlobalInterruptRestore();
    return kCanTxFailed;
  }

# if defined( C_ENABLE_CAN_RAM_CHECK )
  if(canComStatus[channel] == kCanDisableCommunication)
  {
    CanNestedGlobalInterruptRestore();
    return(kCanCommunicationDisabled);
  }
# endif

# if defined( C_ENABLE_SLEEP_WAKEUP )
  assertUser(!CanLL_HwIsSleep(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanSleep);    /* PRQA S 3109 */
# endif
  assertUser(!CanLL_HwIsStop(CAN_HW_CHANNEL_CANPARA_ONLY), channel, kErrorCanStop);      /* PRQA S 3109 */
  
  /* --- check on passive state --- */
# if defined( C_ENABLE_ECU_SWITCH_PASS )
  if ( canPassive[channel] != (vuint8)0)                             /*  set passive ? */
  {
    CanNestedGlobalInterruptRestore();
#  if defined( C_ENABLE_MSG_TRANSMIT_CONF_FCT )
    APPL_CAN_MSGTRANSMITCONF( CAN_CHANNEL_CANPARA_ONLY );
#  endif
    return (kCanTxOk);
  }
# endif /* C_ENABLE_ECU_SWITCH_PASS */

  /* calculate index for canhandleCurTxObj (logical object handle) */
  logTxObjHandle = (CanObjectHandle)((vsintx)CAN_HL_HW_MSG_TRANSMIT_INDEX(canHwChannel) + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel));

  /* check for transmit message object free --------------------------------- */
  /* MsgObj used?  */
  if (( canHandleCurTxObj[logTxObjHandle] != kCanBufferFree ))    
  {
    CanNestedGlobalInterruptRestore();
    return kCanTxFailed;
  }

  /* Obj, pMsgObject points to is free, transmit msg object: ---------------- */
  /* Save hdl of msgObj to be transmitted */
  canHandleCurTxObj[logTxObjHandle] = kCanBufferMsgTransmit;
  CanNestedGlobalInterruptRestore();



  txObjHandle = CAN_HL_HW_MSG_TRANSMIT_INDEX(canHwChannel);
  assertHardware( CanLL_TxIsHWObjFree(canHwChannel, txObjHandle ), channel, kErrorTxBufferBusy);

  #if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
  pFlexCANLocal = pFLEXCAN(canHwChannel);
  #else
  pFlexCANLocal = pFlexCAN(canHwChannel);
  #endif

  CanNestedGlobalInterruptDisable();
  /* Copy all data into transmit object */


  /* If CanTransmit was interrupted by a re-initialization or CanOffline */  
  /* no transmitrequest of this action should be started      */  
  if ((canHandleCurTxObj[logTxObjHandle] == kCanBufferMsgTransmit) && 
                                   ( (canStatus[channel] & kCanTxOn) == kCanTxOn ) )
  {  
     # if defined( C_ENABLE_FLEXCAN_32BIT_ACCESS )
     pFlexCANLocal->canObject[txObjHandle].control = (vuint32)(((vuint32)txMsgStruct->DlcRaw << 16) & kTxDlcMask);
     #  if defined( C_ENABLE_EXTENDED_ID )
     pFlexCANLocal->canObject[txObjHandle].msgID = (vuint32)(((vuint32)txMsgStruct->IdRaw1 << 16) | ((vuint32)txMsgStruct->IdRaw0));
     #  else                                     
     pFlexCANLocal->canObject[txObjHandle].msgID = (vuint32)((vuint32)txMsgStruct->IdRaw1 << 16);
     #  endif
     #  if defined( C_CPUTYPE_BIGENDIAN )
     ((vuint8*)canTxBuf)[0] = txMsgStruct->DataFld[0];
     ((vuint8*)canTxBuf)[1] = txMsgStruct->DataFld[1];
     ((vuint8*)canTxBuf)[2] = txMsgStruct->DataFld[2];
     ((vuint8*)canTxBuf)[3] = txMsgStruct->DataFld[3];
     ((vuint8*)canTxBuf)[4] = txMsgStruct->DataFld[4];
     ((vuint8*)canTxBuf)[5] = txMsgStruct->DataFld[5];
     ((vuint8*)canTxBuf)[6] = txMsgStruct->DataFld[6];
     ((vuint8*)canTxBuf)[7] = txMsgStruct->DataFld[7];
     #  endif
     pFlexCANLocal->canObject[txObjHandle].data[0] = canTxBuf[0];
     pFlexCANLocal->canObject[txObjHandle].data[1] = canTxBuf[1];
     # else
     #  if defined( C_CPUTYPE_BIGENDIAN )  
     CanChipDataPtr16 canDestPtr;
     CanChipDataPtr16 canSrcPtr;
     #  endif
     pFlexCANLocal->canObject[txObjHandle].control = (vuint16)(txMsgStruct->DlcRaw & kTxDlcMask);
     pFlexCANLocal->canObject[txObjHandle].msgIDH = (vuint16)(txMsgStruct->IdRaw1);
     #  if defined( C_ENABLE_EXTENDED_ID )
     pFlexCANLocal->canObject[txObjHandle].msgIDL = (vuint16)(txMsgStruct->IdRaw0);
     #  endif
     #  if defined( C_CPUTYPE_BIGENDIAN )
     canDestPtr = (CanChipDataPtr16) &(pFlexCANLocal->canObject[txObjHandle].data[0]);
     canSrcPtr = (CanChipDataPtr16) &(txMsgStruct->DataFld[0]);
     canDestPtr[0] = canSrcPtr[0];
     canDestPtr[1] = canSrcPtr[1];
     canDestPtr[2] = canSrcPtr[2];
     canDestPtr[3] = canSrcPtr[3];
     #  endif
     # endif /* C_ENABLE_FLEXCAN_32BIT_ACCESS */

     pFlexCANLocal->canObject[txObjHandle].control |= kTxCodeTransmit; 
     

# if defined( C_ENABLE_TX_OBSERVE )
     ApplCanTxObjStart( CAN_CHANNEL_CANPARA_FIRST logTxObjHandle );
# endif
   
     rc = kCanTxOk;                                    
  }  
  else  
  {  
    /* release TxHandle (CanOffline) */
    canHandleCurTxObj[logTxObjHandle] = kCanBufferFree;  
    rc = kCanTxFailed;   
  }  

  CanNestedGlobalInterruptRestore();


  return rc;
} /* end of CanMsgTransmit() */
/* CODE CATEGORY 2 END */
#endif


#if defined( C_ENABLE_DYN_TX_OBJECTS )
/* **********************************************************************
* NAME:           CanGetDynTxObj
* PARAMETER:      txHandle - Handle of the dynamic object to reserve
* RETURN VALUE:   kCanNoTxDynObjAvailable (0xFF) - 
*                   object not available
*                 0..F0 - 
*                   Handle to dynamic transmission object
* DESCRIPTION:    Function reserves and return a handle to a dynamic 
*                   transmission object
*
*                 To use dynamic transmission, an application must get
*                 a dynamic object from CAN-driver. 
*                 Before transmission, application must set all attributes 
*                 (id, dlc, data, confirmation function/flag, pretransmission
*                 etc. - as configurated). 
*                 Application can use a dynamic object for one or many
*                 transmissions (as it likes) - but finally, it must
*                 release the dynamic object by calling CanReleaseDynTxObj.
*********************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 CanTransmitHandle C_API_2 CanGetDynTxObj(CanTransmitHandle txHandle ) C_API_3
{
  CanTransmitHandle nTxDynObj;
  CanDeclareGlobalInterruptOldStatus
  CAN_CHANNEL_CANTYPE_LOCAL
  
  assertUser((txHandle < kCanNumberOfTxObjects), kCanAllChannels, kErrorTxHdlTooLarge);    /* PRQA S 3109 */

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  channel = CanGetChannelOfTxObj(txHandle);
# endif

  assertUser((txHandle <  CAN_HL_TX_DYN_ROM_STOPINDEX(channel)), channel, kErrorAccessedInvalidDynObj);  /* PRQA S 3109 */
# if ( kCanNumberOfTxStatObjects > 0) || defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((txHandle >= CAN_HL_TX_DYN_ROM_STARTINDEX(channel)), channel, kErrorAccessedStatObjAsDyn);  /* PRQA S 3109 */ /* lint !e568 */
# endif

  nTxDynObj = (txHandle - CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) + CAN_HL_TX_DYN_RAM_STARTINDEX(channel); /* PRQA S 3382, 0291 */

  CanNestedGlobalInterruptDisable();
  if ( canTxDynObjReservedFlag[nTxDynObj] != (vuint8)0)
  {
    CanNestedGlobalInterruptRestore();
    return kCanNoTxDynObjAvailable;
  }
  /*  Mark dynamic object as used  */
  canTxDynObjReservedFlag[nTxDynObj] = 1;

# if defined( C_ENABLE_CONFIRMATION_FLAG )
  CanConfirmationFlags._c[CanGetConfirmationOffset(txHandle)] &= 
                            (vuint8)(~CanGetConfirmationMask(txHandle));
# endif
  CanNestedGlobalInterruptRestore();

  /* Initialize dynamic object */
# if defined( C_ENABLE_DYN_TX_DATAPTR )  
  canDynTxDataPtr[nTxDynObj] = V_NULL;  
# endif  
  

  return (txHandle);
}
/* CODE CATEGORY 3 END */

/* **********************************************************************
* NAME:           CanReleaseDynTxObj
* PARAMETER:      hTxObj -
*                   Handle of dynamic transmission object
* RETURN VALUE:   --
* DESCRIPTION:    Function releases dynamic transmission object
*                   which was reserved before (calling CanGetDynTxObj)
*                 
*                 After a transmission of one or more messages is finished,
*                 application must free the reserved resource, formally the
*                 dynamic transmission object calling this function.
*
*                 As the number of dynamic transmission object is limited,
*                 application should not keep unused dynamic transmission
*                 objects for a longer time.
*********************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 vuint8 C_API_2 CanReleaseDynTxObj(CanTransmitHandle txHandle) C_API_3
{
  CanTransmitHandle dynTxObj;
  CAN_CHANNEL_CANTYPE_LOCAL
# if defined( C_ENABLE_TRANSMIT_QUEUE )
  CanSignedTxHandle queueElementIdx; /* index for accessing the tx queue */
  CanSignedTxHandle elementBitIdx;  /* bit index within the tx queue element */
  CanTransmitHandle queueBitPos;  /* physical bitposition of the handle */
# endif
  
  assertUser((txHandle < kCanNumberOfTxObjects), kCanAllChannels, kErrorTxHdlTooLarge);    /* PRQA S 3109 */

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  channel = CanGetChannelOfTxObj(txHandle);
# endif

  assertUser((txHandle <  CAN_HL_TX_DYN_ROM_STOPINDEX(channel)), channel, kErrorAccessedInvalidDynObj);  /* PRQA S 3109 */
# if ( kCanNumberOfTxStatObjects > 0) || defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((txHandle >= CAN_HL_TX_DYN_ROM_STARTINDEX(channel)), channel, kErrorAccessedStatObjAsDyn);  /* PRQA S 3109 */ /* lint !e568 */
# endif

  dynTxObj = (txHandle - CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) + CAN_HL_TX_DYN_RAM_STARTINDEX(channel);  /* PRQA S 3382, 0291 */

  assertInternal((canTxDynObjReservedFlag[dynTxObj] != (vuint8)0), channel, kErrorReleasedUnusedDynObj);  /* PRQA S 3109 */

# if defined( C_ENABLE_TRANSMIT_QUEUE )
  #if defined( C_ENABLE_INTERNAL_CHECK ) &&\
      defined( C_MULTIPLE_RECEIVE_CHANNEL )
  if (sizeof(queueBitPos) == 1)
  {
    assertInternal( ((vuint16)((vuint16)kCanNumberOfTxObjects + (vuint16)CanTxQueuePadBits[kCanNumberOfChannels-1]) <= 256u), kCanAllChannels, kErrorTxQueueTooManyHandle) /* PRQA S 3109 */ /*lint !e572 !e506*/
  }
  else
  {
    if (((sizeof(tCanTxQueuePadBits) == 1) && (kCanNumberOfTxObjects > (65536 - 256))) || (sizeof(tCanTxQueuePadBits) > 1))
    {
      assertInternal( ((vuint32)((vuint32)kCanNumberOfTxObjects + (vuint32)CanTxQueuePadBits[kCanNumberOfChannels-1]) <= 65536u), kCanAllChannels, kErrorTxQueueTooManyHandle) /* PRQA S 3109 */ /*lint !e572 !e506*/
    }  
  }
  #endif
  queueBitPos  = txHandle + CAN_HL_TXQUEUE_PADBITS(channel);
  queueElementIdx = (CanSignedTxHandle)(queueBitPos >> kCanTxQueueShift); /* get the queue element where to set the flag */
  elementBitIdx  = (CanSignedTxHandle)(queueBitPos & kCanTxQueueMask);   /* get the flag index wihtin the queue element */
  if( (canTxQueueFlags[queueElementIdx] & CanShiftLookUp[elementBitIdx]) != (tCanQueueElementType)0 )
  {
  }
  else
# endif
  {
    if (
# if defined( C_ENABLE_CONFIRMATION_FCT ) && \
    defined( C_ENABLE_TRANSMIT_QUEUE )
         (confirmHandle[channel] == txHandle) ||       /* confirmation active ? */
# endif
         (canHandleCurTxObj[(vsintx)CAN_HL_HW_TX_NORMAL_INDEX(canHwChannel) + CAN_HL_TX_OFFSET_HW_TO_LOG(canHwChannel)] != txHandle) )
    {
      /*  Mark dynamic object as not used  */
      canTxDynObjReservedFlag[dynTxObj] = 0;
      return(kCanDynReleased);
    }
  }
  return(kCanDynNotReleased);
}
/* CODE CATEGORY 3 END */
#endif /* C_ENABLE_DYN_TX_OBJECTS */


#if defined( C_ENABLE_DYN_TX_ID ) 
# if !defined( C_ENABLE_EXTENDED_ID ) ||\
     defined( C_ENABLE_MIXED_ID )
/* **********************************************************************
* NAME:           CanDynTxObjSetId
* PARAMETER:      hTxObj -
*                   Handle of dynamic transmission object
*                 id -
*                   Id (standard-format) to register with dynamic object
* RETURN VALUE:   --
* DESCRIPTION:    Function registers submitted id (standard format)
*                 with dynamic object referenced by handle.
*********************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetId(CanTransmitHandle txHandle, vuint16 id) C_API_3
{
  CanTransmitHandle dynTxObj;

  CAN_CHANNEL_CANTYPE_LOCAL
  
  assertUser((txHandle < kCanNumberOfTxObjects), kCanAllChannels, kErrorTxHdlTooLarge);  /* PRQA S 3109 */

#  if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  channel = CanGetChannelOfTxObj(txHandle);
#  endif

  assertUser((txHandle <  CAN_HL_TX_DYN_ROM_STOPINDEX(channel)), channel, kErrorAccessedInvalidDynObj);  /* PRQA S 3109 */
# if ( kCanNumberOfTxStatObjects > 0) || defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((txHandle >= CAN_HL_TX_DYN_ROM_STARTINDEX(channel)), channel, kErrorAccessedStatObjAsDyn);  /* PRQA S 3109 */ /* lint !e568 */
# endif
  assertUser(id <= (vuint16)0x7FF, channel, kErrorWrongId);                                              /* PRQA S 3109 */

  dynTxObj = (txHandle - CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) + CAN_HL_TX_DYN_RAM_STARTINDEX(channel); /* PRQA S 3382, 0291 */

#  if defined( C_ENABLE_MIXED_ID )
  canDynTxIdType[dynTxObj]  = kCanIdTypeStd; 
#  endif

  canDynTxId0[dynTxObj] = MK_STDID0(id);
#  if (kCanNumberOfUsedCanTxIdTables > 1)
  canDynTxId1[dynTxObj] = MK_STDID1(id);
#  endif
#  if (kCanNumberOfUsedCanTxIdTables > 2)
  canDynTxId2[dynTxObj] = MK_STDID2(id);
#  endif
#  if (kCanNumberOfUsedCanTxIdTables > 3)
  canDynTxId3[dynTxObj] = MK_STDID3(id);
#  endif
#  if (kCanNumberOfUsedCanTxIdTables > 4)
  canDynTxId4[dynTxObj] = MK_STDID4(id);
#  endif
}
/* CODE CATEGORY 2 END */
# endif /* !defined( C_ENABLE_EXTENDED_ID ) || defined( C_ENABLE_MIXED_ID ) */
#endif /* C_ENABLE_DYN_TX_ID */

#if defined( C_ENABLE_DYN_TX_ID ) && \
    defined( C_ENABLE_EXTENDED_ID )
/* **********************************************************************
* NAME:           CanDynTxObjSetExtId
* PARAMETER:      hTxObj -  Handle of dynamic transmission object
*                 idExtHi - Id low word (extended-format) to register with
*                                                         dynamic object
*                 idExtLo - Id high word (extended-format) 
* RETURN VALUE:   --
* DESCRIPTION:    Function registers submitted id (standard format)
*                 with dynamic object referenced by handle.
*********************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetExtId(CanTransmitHandle txHandle, vuint16 idExtHi, vuint16 idExtLo) C_API_3
{
  CanTransmitHandle dynTxObj;
  CAN_CHANNEL_CANTYPE_LOCAL
  
  assertUser((txHandle < kCanNumberOfTxObjects), kCanAllChannels, kErrorTxHdlTooLarge);   /* PRQA S 3109 */

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  channel = CanGetChannelOfTxObj(txHandle);
# endif

  assertUser((txHandle <  CAN_HL_TX_DYN_ROM_STOPINDEX(channel)), channel, kErrorAccessedInvalidDynObj);  /* PRQA S 3109 */
# if ( kCanNumberOfTxStatObjects > 0) || defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((txHandle >= CAN_HL_TX_DYN_ROM_STARTINDEX(channel)), channel, kErrorAccessedStatObjAsDyn);  /* PRQA S 3109 */ /* lint !e568 */
# endif
  assertUser(idExtHi <= (vuint16)0x1FFF, channel, kErrorWrongId);                                        /* PRQA S 3109 */

  dynTxObj = (txHandle - CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) + CAN_HL_TX_DYN_RAM_STARTINDEX(channel); /* PRQA S 3382, 0291 */

# if defined( C_ENABLE_MIXED_ID )
  canDynTxIdType[dynTxObj] = kCanIdTypeExt; 
# endif

  canDynTxId0[dynTxObj]      = MK_EXTID0( ((vuint32)idExtHi<<16) | (vuint32)idExtLo );
# if (kCanNumberOfUsedCanTxIdTables > 1)
  canDynTxId1[dynTxObj]      = MK_EXTID1( ((vuint32)idExtHi<<16) | (vuint32)idExtLo );
# endif
# if (kCanNumberOfUsedCanTxIdTables > 2)
  canDynTxId2[dynTxObj]      = MK_EXTID2( ((vuint32)idExtHi<<16) | (vuint32)idExtLo );
# endif
# if (kCanNumberOfUsedCanTxIdTables > 3)
  canDynTxId3[dynTxObj]      = MK_EXTID3( ((vuint32)idExtHi<<16) | (vuint32)idExtLo );
# endif
# if (kCanNumberOfUsedCanTxIdTables > 4)
  canDynTxId4[dynTxObj]      = MK_EXTID4( ((vuint32)idExtHi<<16) | (vuint32)idExtLo );
# endif
}
/* CODE CATEGORY 2 END */
#endif


#if defined( C_ENABLE_DYN_TX_DLC )
/* **********************************************************************
* NAME:           CanDynTxObjSetDlc
* PARAMETER:      hTxObj -
*                   Handle of dynamic transmission object
*                 dlc -
*                   data length code to register with dynamic object
* RETURN VALUE:   --
* DESCRIPTION:    Function registers data length code with 
*                 dynamic object referenced by submitted handle.
*********************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetDlc(CanTransmitHandle txHandle, vuint8 dlc) C_API_3
{
  CanTransmitHandle dynTxObj;
  CAN_CHANNEL_CANTYPE_LOCAL
  
  assertUser((txHandle < kCanNumberOfTxObjects), kCanAllChannels, kErrorTxHdlTooLarge);     /* PRQA S 3109 */

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  channel = CanGetChannelOfTxObj(txHandle);
# endif
  
  assertUser((txHandle <  CAN_HL_TX_DYN_ROM_STOPINDEX(channel)), channel, kErrorAccessedInvalidDynObj);  /* PRQA S 3109 */
# if ( kCanNumberOfTxStatObjects > 0) || defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((txHandle >= CAN_HL_TX_DYN_ROM_STARTINDEX(channel)), channel, kErrorAccessedStatObjAsDyn);  /* PRQA S 3109 */ /* lint !e568 */
# endif
  assertUser(dlc<(vuint8)9, channel, kErrorTxDlcTooLarge);                                               /* PRQA S 3109 */
  
  dynTxObj = (txHandle - CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) + CAN_HL_TX_DYN_RAM_STARTINDEX(channel); /* PRQA S 3382, 0291 */
  
# if defined( C_ENABLE_EXTENDED_ID )
  canDynTxDLC[dynTxObj] = MK_TX_DLC_EXT(dlc);
# else
  canDynTxDLC[dynTxObj] = MK_TX_DLC(dlc);
# endif
}
/* CODE CATEGORY 2 END */
#endif /* C_ENABLE_DYN_TX_DLC */


#if defined( C_ENABLE_DYN_TX_DATAPTR )
/* **********************************************************************
* NAME:           CanDynTxObjSetData
* PARAMETER:      hTxObj -
*                   Handle of dynamic transmission object
*                 pData -
*                   data reference to be stored in data buffer of dynamic object
* RETURN VALUE:   --
* DESCRIPTION:    Functions stores reference to data registered with
*                 dynamic object.
*                 
*                 The number of byte copied is (always) 8. The number of 
*                 relevant (and consequently evaluated) byte is to be 
*                 taken from function CanDynObjGetDLC.
*********************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanDynTxObjSetDataPtr(CanTransmitHandle txHandle, void* pData) C_API_3
{
  CanTransmitHandle dynTxObj;
  CAN_CHANNEL_CANTYPE_LOCAL
  
  assertUser((txHandle < kCanNumberOfTxObjects), kCanAllChannels, kErrorTxHdlTooLarge);    /* PRQA S 3109 */

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  channel = CanGetChannelOfTxObj(txHandle);
# endif

  assertUser((txHandle <  CAN_HL_TX_DYN_ROM_STOPINDEX(channel)), channel, kErrorAccessedInvalidDynObj);  /* PRQA S 3109 */
# if ( kCanNumberOfTxStatObjects > 0) || defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((txHandle >= CAN_HL_TX_DYN_ROM_STARTINDEX(channel)), channel, kErrorAccessedStatObjAsDyn);  /* PRQA S 3109 */ /* lint !e568 */
# endif

  dynTxObj = (txHandle - CAN_HL_TX_DYN_ROM_STARTINDEX(channel)) + CAN_HL_TX_DYN_RAM_STARTINDEX(channel);  /* PRQA S 3382, 0291 */

  canDynTxDataPtr[dynTxObj] = pData;
}
/* CODE CATEGORY 2 END */
#endif /* C_ENABLE_DYN_TX_DATAPTR */




#if defined( C_ENABLE_TX_MASK_EXT_ID )
/* **********************************************************************
* NAME:               CanSetTxIdExtHi
* CALLED BY:          
* PRECONDITIONS:      CanInitPower should already been called.
* PARAMETER:          new source address for the 29-bit CAN-ID
* RETURN VALUE:       -
* DESCRIPTION:        Sets the source address in the lower 8 bit of the
*                     29-bit CAN identifier.
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtHi( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask )
{  
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);     /* PRQA S 3109 */
# endif
  assertUser(mask <= (vuint8)0x1F, channel, kErrorWrongMask);                                /* PRQA S 3109 */

  canTxMask0[channel] = (canTxMask0[channel] & MK_EXTID0(0x00FFFFFFUL)) | MK_EXTID0((vuint32)mask<<24);
# if (kCanNumberOfUsedCanTxIdTables > 1)
  canTxMask1[channel] = (canTxMask1[channel] & MK_EXTID1(0x00FFFFFFUL)) | MK_EXTID1((vuint32)mask<<24);
# endif
# if (kCanNumberOfUsedCanTxIdTables > 2)
  canTxMask2[channel] = (canTxMask2[channel] & MK_EXTID2(0x00FFFFFFUL)) | MK_EXTID2((vuint32)mask<<24);
# endif
# if (kCanNumberOfUsedCanTxIdTables > 3)
  canTxMask3[channel] = (canTxMask3[channel] & MK_EXTID3(0x00FFFFFFUL)) | MK_EXTID3((vuint32)mask<<24);
# endif
# if (kCanNumberOfUsedCanTxIdTables > 4)
  canTxMask4[channel] = (canTxMask4[channel] & MK_EXTID4(0x00FFFFFFUL)) | MK_EXTID4((vuint32)mask<<24);
# endif
}
/* CODE CATEGORY 4 END */

/* **********************************************************************
* NAME:               CanSetTxIdExtMidHi
* CALLED BY:          
* PRECONDITIONS:      CanInitPower should already been called.
* PARAMETER:          new source address for the 29-bit CAN-ID
* RETURN VALUE:       -
* DESCRIPTION:        Sets the source address in the lower 8 bit of the
*                     29-bit CAN identifier.
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtMidHi( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask )
{
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);     /* PRQA S 3109 */
# endif

  canTxMask0[channel] = (canTxMask0[channel] & MK_EXTID0(0xFF00FFFFUL)) | MK_EXTID0((vuint32)mask<<16);   /* lint !e572 */
# if (kCanNumberOfUsedCanTxIdTables > 1)
  canTxMask1[channel] = (canTxMask1[channel] & MK_EXTID1(0xFF00FFFFUL)) | MK_EXTID1((vuint32)mask<<16);   /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 2)
  canTxMask2[channel] = (canTxMask2[channel] & MK_EXTID2(0xFF00FFFFUL)) | MK_EXTID2((vuint32)mask<<16);   /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 3)
  canTxMask3[channel] = (canTxMask3[channel] & MK_EXTID3(0xFF00FFFFUL)) | MK_EXTID3((vuint32)mask<<16);   /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 4)
  canTxMask4[channel] = (canTxMask4[channel] & MK_EXTID4(0xFF00FFFFUL)) | MK_EXTID4((vuint32)mask<<16);   /* lint !e572 */
# endif
}
/* CODE CATEGORY 4 END */

/* **********************************************************************
* NAME:               CanSetTxIdExtMidLo
* CALLED BY:          
* PRECONDITIONS:      CanInitPower should already been called.
* PARAMETER:          new source address for the 29-bit CAN-ID
* RETURN VALUE:       -
* DESCRIPTION:        Sets the source address in the lower 8 bit of the
*                     29-bit CAN identifier.
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtMidLo( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask )
{
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);    /* PRQA S 3109 */
# endif

  canTxMask0[channel] = (canTxMask0[channel] & MK_EXTID0(0xFFFF00FFUL)) | MK_EXTID0((vuint32)mask<<8);    /* lint !e572 */
# if (kCanNumberOfUsedCanTxIdTables > 1)
  canTxMask1[channel] = (canTxMask1[channel] & MK_EXTID1(0xFFFF00FFUL)) | MK_EXTID1((vuint32)mask<<8);    /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 2)
  canTxMask2[channel] = (canTxMask2[channel] & MK_EXTID2(0xFFFF00FFUL)) | MK_EXTID2((vuint32)mask<<8);    /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 3)
  canTxMask3[channel] = (canTxMask3[channel] & MK_EXTID3(0xFFFF00FFUL)) | MK_EXTID3((vuint32)mask<<8);    /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 4)
  canTxMask4[channel] = (canTxMask4[channel] & MK_EXTID4(0xFFFF00FFUL)) | MK_EXTID4((vuint32)mask<<8);    /* lint !e572 */
# endif
}
/* CODE CATEGORY 4 END */

/* **********************************************************************
* NAME:               CanSetTxIdExtLo
* CALLED BY:          
* PRECONDITIONS:      CanInitPower should already been called.
* PARAMETER:          new source address for the 29-bit CAN-ID
* RETURN VALUE:       -
* DESCRIPTION:        Sets the source address in the lower 8 bit of the
*                     29-bit CAN identifier.
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanSetTxIdExtLo( CAN_CHANNEL_CANTYPE_FIRST  vuint8 mask )
{
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser(channel < kCanNumberOfChannels, kCanAllChannels, kErrorChannelHdlTooLarge);    /* PRQA S 3109 */
# endif

  canTxMask0[channel] = (canTxMask0[channel] & MK_EXTID0(0xFFFFFF00UL)) | MK_EXTID0((vuint32)mask);     /* lint !e572 */
# if (kCanNumberOfUsedCanTxIdTables > 1)
  canTxMask1[channel] = (canTxMask1[channel] & MK_EXTID1(0xFFFFFF00UL)) | MK_EXTID1((vuint32)mask);     /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 2)
  canTxMask2[channel] = (canTxMask2[channel] & MK_EXTID2(0xFFFFFF00UL)) | MK_EXTID2((vuint32)mask);     /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 3)
  canTxMask3[channel] = (canTxMask3[channel] & MK_EXTID3(0xFFFFFF00UL)) | MK_EXTID3((vuint32)mask);     /* lint !e572 */
# endif
# if (kCanNumberOfUsedCanTxIdTables > 4)
  canTxMask4[channel] = (canTxMask4[channel] & MK_EXTID4(0xFFFFFF00UL)) | MK_EXTID4((vuint32)mask);    /* lint !e572 */
# endif
}
/* CODE CATEGORY 4 END */
#endif

#if defined( C_ENABLE_TX_OBSERVE )
/* **********************************************************************
* NAME:               CanTxGetActHandle
* CALLED BY:          
* PRECONDITIONS:      
* PARAMETER:          logical hardware object handle
* RETURN VALUE:       handle of the message in the assigned mailbox
* DESCRIPTION:        get transmit handle of the message, which is currently
*                     in the mailbox txHwObject.
*********************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 CanTransmitHandle C_API_2 CanTxGetActHandle( CanObjectHandle logicalTxHdl ) C_API_3
{
  assertUser(logicalTxHdl < kCanNumberOfUsedTxCANObjects, kCanAllChannels, kErrorTxHwHdlTooLarge);     /* PRQA S 3109 */

  return (canHandleCurTxObj[logicalTxHdl]);       /* lint !e661 */
}
/* CODE CATEGORY 3 END */
#endif

#if defined( C_ENABLE_VARIABLE_RX_DATALEN )
/* **********************************************************************
* NAME:               CanSetVariableRxDatalen
* CALLED BY:          
* PRECONDITIONS:      
* PARAMETER:          rxHandle: Handle of receive Message for which the datalen has
*                               to be changed
*                     dataLen:  new number of bytes, which have to be copied to the 
*                               message buffer.
* RETURN VALUE:       -
* DESCRIPTION:        change the dataLen of a receive message to copy a 
*                     smaller number of bytes than defined in the database.
*                     the dataLen can only be decreased. If the parameter
*                     dataLen is bigger than the statically defined value
*                     the statically defined value will be set.
*********************************************************************** */
/* CODE CATEGORY 1 START */
static void CanSetVariableRxDatalen (CanReceiveHandle rxHandle, vuint8 dataLen)
{
  assertInternal(rxHandle < kCanNumberOfRxObjects, kCanAllChannels, kErrorRxHandleWrong);  /* PRQA S 3109 */ /* legal rxHandle ? */
  /* assertion for dataLen not necessary due to runtime check */

  if (dataLen < CanGetRxDataLen(rxHandle))
  {
    canVariableRxDataLen[rxHandle]=dataLen;
  }
  else
  {
    canVariableRxDataLen[rxHandle] = CanGetRxDataLen(rxHandle);
  }
}
/* CODE CATEGORY 1 END */
#endif

#if defined( C_ENABLE_COND_RECEIVE_FCT )
/* **********************************************************************
* NAME:               CanSetMsgReceivedCondition
* CALLED BY:          Application
* PRECONDITIONS:      
* PARAMETER:          -.
* RETURN VALUE:       -
* DESCRIPTION:        The service function CanSetMsgReceivedCondition()
*                     enables the calling of ApplCanMsgCondReceived()
*********************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 void C_API_2 CanSetMsgReceivedCondition( CAN_CHANNEL_CANTYPE_ONLY )
{
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((channel < kCanNumberOfChannels), kCanAllChannels, kErrorChannelHdlTooLarge);     /* PRQA S 3109 */
# endif

  canMsgCondRecState[channel] = kCanTrue;
}
/* CODE CATEGORY 3 END */

/* **********************************************************************
* NAME:               CanResetMsgReceivedCondition
* CALLED BY:          Application
* PRECONDITIONS:      
* PARAMETER:          -
* RETURN VALUE:       -
* DESCRIPTION:        The service function CanResetMsgReceivedCondition()
*                     disables the calling of ApplCanMsgCondReceived()
*********************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 void C_API_2 CanResetMsgReceivedCondition( CAN_CHANNEL_CANTYPE_ONLY )
{
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((channel < kCanNumberOfChannels), kCanAllChannels, kErrorChannelHdlTooLarge);    /* PRQA S 3109 */
# endif

  canMsgCondRecState[channel] = kCanFalse;
}
/* CODE CATEGORY 3 END */

/* **********************************************************************
* NAME:               CanGetMsgReceivedCondition
* CALLED BY:          Application
* PRECONDITIONS:      
* PARAMETER:          -
* RETURN VALUE:       status of Conditional receive function:
*                     kCanTrue : Condition is set -> ApplCanMsgCondReceived 
*                                will be called
*                     kCanFalse: Condition is not set -> ApplCanMsgCondReceived
*                                will not be called
* DESCRIPTION:        The service function CanGetMsgReceivedCondition() 
*                     returns the status of the condition for calling
*                     ApplCanMsgCondReceived()
*********************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 vuint8 C_API_2 CanGetMsgReceivedCondition( CAN_CHANNEL_CANTYPE_ONLY )
{
# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertUser((channel < kCanNumberOfChannels), kCanAllChannels, kErrorChannelHdlTooLarge);   /* PRQA S 3109 */
# endif

  return( canMsgCondRecState[channel] );
}
/* CODE CATEGORY 3 END */
#endif


#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
/* **********************************************************************
* NAME:           ApplCanChannelDummy
* PARAMETER:      channel
*                 current receive channel
* RETURN VALUE:   ---
* DESCRIPTION:    dummy-function for unused Callback-functions
*********************************************************************** */
/* CODE CATEGORY 3 START */
C_API_1 void C_API_2 ApplCanChannelDummy( CanChannelHandle channel )
{
# if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  channel = channel;     /* to avoid lint warnings */
# endif
}
/* CODE CATEGORY 3 END */
#endif   /* C_MULTIPLE_RECEIVE_CHANNEL */


#if defined( C_MULTIPLE_RECEIVE_CHANNEL ) || \
    defined( C_HL_ENABLE_DUMMY_FCT_CALL )
/* **********************************************************************
* NAME:           ApplCanRxStructPtrDummy
* PARAMETER:      rxStruct
*                 pointer of CanRxInfoStruct
* RETURN VALUE:   kCanCopyData 
* DESCRIPTION:    dummy-function for unused Callback-functions
*********************************************************************** */
/* CODE CATEGORY 1 START */
C_API_1 vuint8 C_API_2 ApplCanRxStructPtrDummy( CanRxInfoStructPtr rxStruct )
{
# if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  rxStruct = rxStruct;     /* to avoid lint warnings */
# endif
  return kCanCopyData;
}
/* CODE CATEGORY 1 END */

/* **********************************************************************
* NAME:           ApplCanTxHandleDummy
* PARAMETER:      txHandle
*                 transmit handle
* RETURN VALUE:   ---
* DESCRIPTION:    dummy-function for unused Callback-functions
*********************************************************************** */
/* CODE CATEGORY 1 START */
C_API_1 void C_API_2 ApplCanTxHandleDummy( CanTransmitHandle txHandle )
{
# if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  txHandle = txHandle;     /* to avoid lint warnings */
# endif
}
/* CODE CATEGORY 1 END */
#endif   /* C_MULTIPLE_RECEIVE_CHANNEL || C_HL_ENABLE_DUMMY_FCT_CALL */

#if defined( C_HL_ENABLE_DUMMY_FCT_CALL )
/* **********************************************************************
* NAME:           ApplCanTxStructDummy
* PARAMETER:      txStruct
*                 pointer of CanTxInfoStruct
* RETURN VALUE:   kCanCopyData
* DESCRIPTION:    dummy-function for unused Callback-functions
*********************************************************************** */
/* CODE CATEGORY 1 START */
C_API_1 vuint8 C_API_2 ApplCanTxStructDummy( CanTxInfoStruct txStruct )
{
# if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  txStruct = txStruct;     /* to avoid lint warnings */
# endif
  return kCanCopyData;
}
/* CODE CATEGORY 1 END */

/* **********************************************************************
* NAME:           ApplCanRxHandleDummy
* PARAMETER:      rxHandle
*                 receive handle
* RETURN VALUE:   ---
* DESCRIPTION:    dummy-function for unused Callback-functions
*********************************************************************** */
/* CODE CATEGORY 1 START */
C_API_1 void C_API_2 ApplCanRxHandleDummy( CanReceiveHandle rxHandle )
{
# if defined( V_ENABLE_USE_DUMMY_STATEMENT )
  rxHandle = rxHandle;     /* to avoid lint warnings */
# endif  
}
/* CODE CATEGORY 1 END */
#endif /* C_HL_ENABLE_DUMMY_FCT_CALL */

#if defined( C_ENABLE_RX_QUEUE )
/* **********************************************************************
* NAME:               CanHL_ReceivedRxHandleQueue
* CALLED BY:          CanBasicCanMsgReceived, CanFullCanMsgReceived
* Preconditions:      none
* PARAMETER:          none
* RETURN VALUE:       none
* DESCRIPTION:        Writes receive data into queue or starts further
*                     processing for this message
*********************************************************************** */
/* CODE CATEGORY 1 START */
static vuint8 CanHL_ReceivedRxHandleQueue(CAN_CHANNEL_CANTYPE_ONLY)
{
  CanDeclareGlobalInterruptOldStatus
  tCanRxInfoStruct    *pCanRxInfoStruct;


# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  assertInternal(channel < kCanNumberOfChannels, kCanAllChannels, kErrorInternalChannelHdlTooLarge);  /* PRQA S 3109 */
# endif

  /* Rx Queue is supported with C_HL_ENABLE_RX_INFO_STRUCT_PTR only! */
  pCanRxInfoStruct =  &canRxInfoStruct[channel];

  /* if C_ENABLE_APPLCANPRERXQUEUE is not set, a macro ApplCanPreRxQueue has to be provided by the tool */
  /* in case of ranges, ApplCanPreRxQueue has to return kCanCopyData! */
# if defined( C_ENABLE_APPLCANPRERXQUEUE )
  if(ApplCanPreRxQueue(CAN_HL_P_RX_INFO_STRUCT(channel)) == kCanCopyData)
# endif
  {
    /* Disable the interrupts because nested interrupts can take place -
      CAN interrupts of all channels have to be disabled here */
    CanNestedGlobalInterruptDisable();
    if(canRxQueue.canRxQueueCount < kCanRxQueueSize)   /* Queue full ? */
    {
      if (canRxQueue.canRxQueueWriteIndex == (kCanRxQueueSize - 1) )
      {
        canRxQueue.canRxQueueWriteIndex = 0;
      }
      else
      {
        canRxQueue.canRxQueueWriteIndex++;
      }
      canRxQueue.canRxQueueBuf[canRxQueue.canRxQueueWriteIndex].Channel = channel;
      canRxQueue.canRxQueueBuf[canRxQueue.canRxQueueWriteIndex].Handle  = pCanRxInfoStruct->Handle;

      CanLL_CopyFromCan((void*)&(canRxQueue.canRxQueueBuf[canRxQueue.canRxQueueWriteIndex].CanChipMsgObj),(CanChipDataPtr)pCanRxInfoStruct->pChipMsgObj,16);

      canRxQueue.canRxQueueCount++;
    }
# if defined( C_ENABLE_RXQUEUE_OVERRUN_NOTIFY )
    else
    {
      ApplCanRxQueueOverrun();
    }
# endif
    CanNestedGlobalInterruptRestore();
  } 
# if defined( C_ENABLE_APPLCANPRERXQUEUE )
  else
  {
    /* Call the application call-back functions and set flags */
#  if defined( C_ENABLE_RX_QUEUE_RANGE )
    if (pCanRxInfoStruct->Handle < kCanNumberOfRxObjects )
#  endif
    { 
      return CanHL_ReceivedRxHandle(CAN_CHANNEL_CANPARA_FIRST pCanRxInfoStruct);
    }
  }
# endif
  return kCanHlFinishRx;
}
/* CODE CATEGORY 1 END */

/* **********************************************************************
* NAME:               CanHandleRxMsg
* CALLED BY:          Application
* Preconditions:      none
* PARAMETER:          none
* RETURN VALUE:       none
* DESCRIPTION:        Calls PreCopy and/or Indication, if existent and
*                     set the indication flag
*********************************************************************** */
/* CODE CATEGORY 2 START */
C_API_1 void C_API_2 CanHandleRxMsg(void)
{
  CanDeclareGlobalInterruptOldStatus
  CAN_CHANNEL_CANTYPE_LOCAL
  tCanRxInfoStruct        localCanRxInfoStruct;

  while ( canRxQueue.canRxQueueCount != (vuintx)0 )
  {

# if defined( C_MULTIPLE_RECEIVE_CHANNEL )
    channel = canRxQueue.canRxQueueBuf[canRxQueue.canRxQueueReadIndex].Channel;
# endif


    CAN_CAN_INTERRUPT_DISABLE( channel );

    /* Call the application call-back functions and set flags */
    localCanRxInfoStruct.Handle      = canRxQueue.canRxQueueBuf[canRxQueue.canRxQueueReadIndex].Handle;
    localCanRxInfoStruct.pChipData   = (CanChipDataPtr)&(canRxQueue.canRxQueueBuf[canRxQueue.canRxQueueReadIndex].CanChipMsgObj.DataFld[0]);
    canRDSRxPtr[channel] = localCanRxInfoStruct.pChipData;
    localCanRxInfoStruct.pChipMsgObj = (CanChipMsgPtr) &(canRxQueue.canRxQueueBuf[canRxQueue.canRxQueueReadIndex].CanChipMsgObj);
    localCanRxInfoStruct.Channel     = channel;

# if defined( C_ENABLE_RX_QUEUE_RANGE )
    switch ( localCanRxInfoStruct.Handle)
    {
#  if defined( C_ENABLE_RANGE_0 )
      case kCanRxHandleRange0: (void)APPLCANRANGE0PRECOPY( &localCanRxInfoStruct ); break;
#  endif
#  if defined( C_ENABLE_RANGE_1 )
      case kCanRxHandleRange1: (void)APPLCANRANGE1PRECOPY( &localCanRxInfoStruct ); break;
#  endif
#  if defined( C_ENABLE_RANGE_2 )
      case kCanRxHandleRange2: (void)APPLCANRANGE2PRECOPY( &localCanRxInfoStruct ); break;
#  endif
#  if defined( C_ENABLE_RANGE_3 )
      case kCanRxHandleRange3: (void)APPLCANRANGE3PRECOPY( &localCanRxInfoStruct ); break;
#  endif
      default:
#  if defined( C_ENABLE_INDICATION_FLAG ) || \
      defined( C_ENABLE_INDICATION_FCT )
             if( CanHL_ReceivedRxHandle( CAN_CHANNEL_CANPARA_FIRST &localCanRxInfoStruct ) == kCanHlContinueRx )
             {
               CanHL_IndRxHandle(localCanRxInfoStruct.Handle);
             }
#  else
             (void) CanHL_ReceivedRxHandle( CAN_CHANNEL_CANPARA_FIRST &localCanRxInfoStruct );
#  endif
             break;
   }
# else
#  if defined( C_ENABLE_INDICATION_FLAG ) || \
      defined( C_ENABLE_INDICATION_FCT )
    if( CanHL_ReceivedRxHandle( CAN_CHANNEL_CANPARA_FIRST &localCanRxInfoStruct ) == kCanHlContinueRx )
    {
      CanHL_IndRxHandle(localCanRxInfoStruct.Handle);
    }
#  else
    (void) CanHL_ReceivedRxHandle( CAN_CHANNEL_CANPARA_FIRST &localCanRxInfoStruct );
#  endif
# endif
    
    CAN_CAN_INTERRUPT_RESTORE( channel );

    CanNestedGlobalInterruptDisable();
    if (canRxQueue.canRxQueueReadIndex == (kCanRxQueueSize - 1) )
    {
      canRxQueue.canRxQueueReadIndex = 0;
    }
    else
    {
      canRxQueue.canRxQueueReadIndex++;
    }
    canRxQueue.canRxQueueCount--;
    CanNestedGlobalInterruptRestore();
  }
  return;
} /* end of CanHandleRxMsg() */
/* CODE CATEGORY 2 END */

/* **********************************************************************
* NAME:               CanDeleteRxQueue
* CALLED BY:          Application, CAN driver
* Preconditions:      none
* PARAMETER:          none
* RETURN VALUE:       none
* DESCRIPTION:        delete receive queue
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanDeleteRxQueue(void)
{
  CanDeclareGlobalInterruptOldStatus
  
  CanNestedGlobalInterruptDisable();
  canRxQueue.canRxQueueWriteIndex  = (vuintx)0xFFFFFFFF;
  canRxQueue.canRxQueueReadIndex   = 0;
  canRxQueue.canRxQueueCount       = 0;  
  CanNestedGlobalInterruptRestore();
} /* end of CanDeleteRxQueue() */
/* CODE CATEGORY 4 END */

#endif /* C_ENABLE_RX_QUEUE */

#if defined(C_ENABLE_UPDATE_BASE_ADDRESS)
/* **********************************************************************
* NAME:           CanBaseAddressRequest
* CALLED BY:      Application
* Preconditions:  none
* PARAMETER:      channel: the CAN channel for which the address is requested
* RETURN VALUE:   ---
* DESCRIPTION:    The application calls this function in order to tell the 
*                 CAN driver to request the computation of the virtual 
*                 address of the CAN controller.
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanBaseAddressRequest(CAN_CHANNEL_CANTYPE_ONLY)
{

  {
    # if defined ( C_MULTIPLE_RECEIVE_CHANNEL )
    canLL_VirtualPtrFieldTemp[canHwChannel] = (V_DEF_P2VAR_PARA(V_NONE, vuint32, AUTOMATIC, APPL_VAR)) ApplCanGetBaseAddress((vuint32) CanHwChannelData[canHwChannel].CanBaseAddress, (sizeof(tFLEXCAN)+0x3ff+sizeof(tCanRxMask)));
    # else /* C_MULTIPLE_RECEIVE_CHANNEL */
    canLL_VirtualPtrFieldTemp[0] = (V_DEF_P2VAR_PARA(V_NONE, vuint32, AUTOMATIC, APPL_VAR)) ApplCanGetBaseAddress((vuint32)C_TOUCAN_BASIS, (sizeof(tFLEXCAN)+0x3ff+sizeof(tCanRxMask)));
    # endif /* C_MULTIPLE_RECEIVE_CHANNEL */
  }
}
/* CODE CATEGORY 4 END */

/* **********************************************************************
* NAME:           CanBaseAddressActivate
* CALLED BY:      Application
* Preconditions:  Interrupts have to be disabled
* PARAMETER:      channel: the CAN channel for which the address is requested
* RETURN VALUE:   ---
* DESCRIPTION:    The application calls this function in order to tell the 
*                 CAN driver to activate the virtual address of the CAN 
*                 controller. The adress has to be requested with 
*                 CanBaseAddressRequest() before.
*                 Call is only allowed on Task level and must not interrupt
*                 any CAN driver service functions.
*********************************************************************** */
/* CODE CATEGORY 4 START */
C_API_1 void C_API_2 CanBaseAddressActivate(CAN_CHANNEL_CANTYPE_ONLY)
{

  {
    # if defined ( C_MULTIPLE_RECEIVE_CHANNEL )
    canLL_VirtualPtrField[canHwChannel] = canLL_VirtualPtrFieldTemp[canHwChannel];
    # else /* C_MULTIPLE_RECEIVE_CHANNEL */
    canLL_VirtualPtrField[0] = canLL_VirtualPtrFieldTemp[0];
    # endif /* C_MULTIPLE_RECEIVE_CHANNEL */
  }
}
/* CODE CATEGORY 4 END */
#endif  /* defined(VGEN_ENABLE_MDWRAP) || defined(VGEN_ENABLE_QWRAP) || defined(C_ENABLE_UPDATE_BASE_ADDRESS) */



/* End of channel */
/* STOPSINGLE_OF_MULTIPLE */
/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Mpc5500Flexcan2Hll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Mpc5500Flexcan2Hll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Mpc5500Flexcan2Hll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Mpc5500Flexcan2Hll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Mpc5500Flexcan2Hll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Mpc5500Flexcan2Hll Erzeugungsgangnummer: 1 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCan_Mpc5500Flexcan2Hll Erzeugungsgangnummer: 1 */

