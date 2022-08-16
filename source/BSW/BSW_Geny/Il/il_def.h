/* Kernbauer Version: 1.14 Konfiguration: Il_Vector Erzeugungsgangnummer: 166 */

/* STARTSINGLE_OF_MULTIPLE */
/* KB begin Il_Vector_HeaderText */
/* KB end Il_Vector_HeaderText */
/**********************************************************************************************************************
  COPYRIGHT
-----------------------------------------------------------------------------------------------------------------------
  \par      copyright
  \verbatim
  Copyright (c) 2000-2016 by Vector Informatik GmbH. All rights reserved.
 
                This software is copyright protected and proprietary to Vector Informatik GmbH.
                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
                All other rights remain with Vector Informatik GmbH.
  \endverbatim
-----------------------------------------------------------------------------------------------------------------------
  FILE DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
  \file  File:  Il_Def.h
      Project:  Il_Vector
       Module:  -
    Generator:  -

  \brief Description:  Vector Interaction Layer header file
**********************************************************************************************************************/

/**********************************************************************************************************************
  AUTHOR IDENTITY
-----------------------------------------------------------------------------------------------------------------------
  Name                          Initials      Company
-----------------------------------------------------------------------------------------------------------------------
  Heike Honert                  Ht            Vector Informatik GmbH
  Stephan Hoffmann              Hn            Vector CANtech, Inc.
  Armin Happel                  Hp            Vector Informatik GmbH
  Gunnar de Haan                dH            Vector Informatik GmbH
  Bernd Stumpf                  Stu           Vector Informatik GmbH	
  Thomas Ebert                  Et            Vector Informatik GmbH
  Werner Ziegler                Zw            Vector Informatik GmbH
  Thomas Petrus                 Pet           Vector Informatik GmbH
  Ralf Fritz                    Fz            Vector Informatik GmbH
  Gunnar Meiss                  Ms            Vector Informatik GmbH
  Marc Rauscher                 Mra           Vector Informatik GmbH
  Frank Triem                   Tri           Vector Informatik GmbH
  Todd Emaus                    Tde           Vector CANtech, Inc.
  Hartmut Hoerner               Hh            Vector Informatik GmbH
  Patrick Markl                 Ml            Vector Informatik GmbH
  Sebastian Waldvogel           Swa           Vector Informatik GmbH
  Heiko Huebler                 Hho           Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
-----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Change Id     Description
-----------------------------------------------------------------------------------------------------------------------
  03.00.00  2000-05-08  Ht                    Creation of Vector IL derived from GMLAN Interaction Layer V2.30
  03.01.00  2000-06-16  Ht                    signal-sendtype "ifActive" added
  03.02.00  2000-06-28  Bd                    InitIfActiveFlags call with channelindex ()
  03.03.00  2000-09-05  Ht                    some comment changed
  03.10.00  2000-10-30  Ht                    -adaption to CAN driver with channel index
                                              -call of InitIfActiveFlags only if cyclic event enabled
  03.11.00  2000-11-22  Ht                    version number increased
  03.12.00  2001-04-12  Ht                    -INTERACTION_LAYER_BUGFIX_VERSION added
                                              -extern declaration of module version  
                                              -adapted extern declaration to IAR M16C
            2001-04-20  Ht                    -adaption of functions to Keil C5x5
  03.20.00  2001-06-01  Ht                    -new features:
                                              -Tx: Timeout, Defaultvalues, Send on Init
                                              -Rx: Start-Defautvalues, DataChanged
                                              -indication if rx is waiting
  03.21.00  2001-06-08  Ht                    -modified Tx timeout behaviour
  03.22.00  2001-08-27  Ht      ESCAN00001168 Restart of Rx timeout monitoring in waiting mode
                                              -Storage class of ilChannelState changed (no longer static) 
  03.23.00  2001-09-09  Ht      ESCAN00001417 Support Multiple receive channel driver
  03.24.00  2001-09-12  Ht      ESCAN00001448 Elimination of compiler warnings - state macros
  03.25.00  2001-11-15  Hp      ESCAN00002245 Merge GMLAN-IL with Vector-IL.
                                              Adding GMLAN V3.0 related features.
  03.26.00  2001-11-20  Hp                    -Gm-Only :
                                              -New interface function indicates learned message source address.
                                              -Learned source address only indicated when new.
                                              -Bugfix for VN-array initialisation.
                                              -Support for physical Multi-ECU configuration.
            2002-01-30  Ms      ESCAN00002188 IlRxTask calls IlRxGenTask only if RxEnabled
  03.27.00  2002-02-07  Ht      ESCAN00001760 insert module specific define
                                ESCAN00002305 Linker error for function _memcpy
  03.28.00  2002-02-25  Hp      ESCAN00002252 New callback function for dynamic source address learning.
                                              Revised timeout supervision for learned Extended-IDs
            2002-03-06  Hp      ESCAN00002428 Split the tasks and call message functions individually.
  03.30.00  2002-04-23  Ht      ESCAN00002199 Export extern declarations from IL.c to IL_def.h
                                ESCAN00002604 If no rx-timeout control is used, the IL cannot be compiled
                                ESCAN00002638 extern declaration of IlRxMsgECUMask changed  
                                ESCAN00002689 one call cycle missing for Start delay time
                                ESCAN00002713 Support the new features with multi channel systems
                                ESCAN00002714 Reset RxTimerFlags in IlRxRelease()
                                ESCAN00002715 Support systems without Tx or Rx messages
                                ESCAN00002716 ID priority of Tx messages could be inverted
            2002-04-29  Hp                    Signal supervision fail indication when new msgs on a VN become active
            2002-05-15  Hp                    Gm-Only : Minor corrections for GMLAN in IlTxTimerTask() and IlDequeueNonActiveTxMessages
                                              Gm-Only : start implementing indexed version
                                              Correct the check for max. number of nodes when learning a new address.
  03.32.00  2002-06-17  Ht      ESCAN00003075 Unexpected Rx-Timeout notification in MultiECU systems
                                ESCAN00002791 PowerOn initialization
                                ESCAN00002956 signal irelated start, stop and init callback functions
                                ESCAN00002976 additional get function for indication flags access
            2002-07-08  Stu                   Bugfix for initialisation of index and mask in IlTxTimerTask
  03.33.00  2002-09-09  Et      ESCAN00003694 support STmicro ST7 (beCAN) / Hiware
            2002-09-27  Zw                    support STmicro ST7 (beCAN)/Hiware additional changes after review
  03.34.00  2002-10-29  Fz                    No changes
                        Hp      ESCAN00004099 Function added that provides the status of an NCA
  03.35.00  2002-11-06  Hp      ESCAN00004124 Gm-Only : Compile error for function IlGetNodeCommActiveState() 
                                              for GMLAN without Extended-IDs
            2002-12-05  Pet     ESCAN00004364 wrong define for 8Bit CPU
  03.35.01  2002-12-18  Pet     ESCAN00004495 rx indirection check not needed when indirection index search is used
  03.36.00  2003-05-04  Fz      ESCAN00004484 Timeoutnotification for VN start changed
                                ESCAN00004424 Code optimization for transmission without Repetition
                                ESCAN00004621 Problem in macro IlClrChannelReceived removed  
                                ESCAN00004665 Gm-Only : Wrong index into structure used
                                ESCAN00004715 Gm-Only : Compiler failure removed
                        Hp      ESCAN00004740 Add a function that clears the Timeout indication for receive signals
                        Ms      ESCAN00004956 PClint comments to avoid unauthorized Warnings
                        Mra     ESCAN00005013 Fixed missing  inside of the IlCanGenericPrecopy function
                        Ms      ESCAN00004413 warning from TI TMS470 Compiler
                                ESCAN00003525 memory qualifier for zero page mapping - HC08
                                ESCAN00004662 Size of "extern" object 'IlIndicationOffset' is unknown
                        Fz      ESCAN00005215 Gm-Only : Some assertions modified
                        Ht      ESCAN00002196 Improve Runtime for default values setting of RxSignals in Multiple ECU's
                                ESCAN00004205 Support  for Dual Rate Messages
                                ESCAN00004559 Optimisation for IlRxStateTask not working on indexed  multi channel systems
                                ESCAN00004652 PSA specific timer handling for Periodic and Event triggered messages is not supported by IL 
                                ESCAN00005214 avoid compiler warning in IlRxStateTask about unused parameter
                                ESCAN00005463 Setting of TxDefaultvalue could fail
  03.37.00  2003-05-12  Ht      ESCAN00005627 setting of RxStart and RxStop Default Values could fail
                        Fz      ESCAN00005560 Gm-Only : Incorrect reception handling of application messages in a Multiple-ECU environment
  03.38.00  2003-05-15  Tri     ESCAN00005676 Implementing memory qualifier V_MEMROM0
  03.39.00  2003-07-16  Tri     ESCAN00006095 V_MEMROM0 not used at pointer to constants
                        Ht      ESCAN00005851 Memory access may fail with Physical Multiple ECU 
                                ESCAN00005852 suppressed transmission after cancelation of a message
                        Hp      ESCAN00005993 Change bit-order for IlVnTxSendOnInit[].
                        Ms      ESCAN00006033 Critical Indirections with more than 255 CAN messages
  03.40.00  2003-07-16  HH      ESCAN00005827 added define for error  ILERR_ILLCHANNEL
                        HH      ESCAN00006157 MISRA compliance improved
                        HH      ESCAN00005996 IlUintType replaced by vuintx
  03.41.00  2003-08-11  Hp                    No changes here
  03.42.00  2003-08-15  Fz                    No changes here
  03.43.00  2003-08-29  Hp                    No changes here
  03.44.00  2003-09-08  Hp                    No changes here
  03.45.00  2003-09-16  Fz                    No changes here
  03.46.00  2003-09-29  Fz                    No changes here
  03.47.00  2003-10-14  Fz                    No changes here
  03.48.00  2004-01-16  Fz/Tde/Ms
                                ESCAN00006990 Add of TMS320 support
  03.49.00  2003-12-11  HH      ESCAN00007143 use V_MEM_* instead of MEMORY_ROM
            2004-02-05  Ms                    added v_def.h compatibility check
            2004-03-01  Ms                    adapted Memory Qualifier
            2004-03-02  Ms                    adapted Version Handling
  03.50.00  2004-04-02  HH                    improved MISRA compliance, uses vstdlib instead of own functions
                                ESCAN00000815 common module functions _memcpy and _memclr
            2004-05-14  Ms                    Added Memcopysupport check in relation to RI 1.4
                                              Incremented and improved V_DEF_VERSION check
                                              Added vstdlib compatibility check
                                              Improved CANGen compatibility Check
                                              Removed Memory Qualifier Workaround
            2004-05-19  HH/Ms   ESCAN00007288 ilTxState and IlTxStartCycles arrays are accessed but not defined
  03.51.00  2004-07-09  Fz      ESCAN00008856 Gm-Only : Wrong notification about failed source
  03.52.00  2004-11-17  Fz      ESCAN00009802 No changes here
                        Ms      ESCAN00009576 No changes here
                                ESCAN00009575 Remove C_COMP_FJVGC
                                ESCAN00009613 No changes here
                                ESCAN00009616 Conceptional common usage of function pointer tables 
                                              in IlTxConfirmationFctPtr and IlCanRxIndicationFctPtr
                                ESCAN00009633 Naming Conventions
                                ESCAN00007483 No changes here
                                ESCAN00009836 No changes here
                                ESCAN00006085 No changes here
                                ESCAN00009889 No changes here
                                ESCAN00010057 VStdLib Switch
  04.00.00  2005-06-15  Fz      ESCAN00010505 No changes here
                        Ms      ESCAN00010691 Improve MISRA Compliance
                        Ms      ESCAN00010404 No changes here
                        Ms      ESCAN00010403 IlResetCanIndicationFlags Preprocessor encapsulation
                        Ms      ESCAN00010709 Invalid Confirmation Notification and StartDelay time for Multiplex Messages
                        Ms      ESCAN00010701 Not GM: Activate ApplIlInit extern declaration
                        Ms      ESCAN00010704 Remove IL_NO_COMPATIBILITY
                        Ms      ESCAN00010825 No changes here
                        Ms      ESCAN00010609 IlRxFirstvalueFlagsStartIndex Spelling
                        Ms      ESCAN00010690 Geny Compatibility
                        Ms      ESCAN00008116 Dynamic Rx Timeouts
                        Ms      ESCAN00008651 No changes here
                        Ms      ESCAN00012393 Organi Check
                        Ms      ESCAN00008455 Geny: Preprocessor Checks
                        Ms      ESCAN00012640 No changes here
                        Ms      ESCAN00012640 No changes here
  04.01.00  2005-08-02  Ms      ESCAN00012851 No changes here
                        Ms      ESCAN00012946 Geny: Standard Multiplex Interface
                        Ms      ESCAN00013024 Geny: kIlNumberOfRxIndicationBits used, but not defined
                        Ms      ESCAN00013049 No changes here
                        Fz      ESCAN00012988 Interface of function IlGetRxMessageSourceAddress changed
  04.02.00  2005-12-07  Ms      ESCAN00013387 added FastOnStart for muliplexed messages
                        Ms      ESCAN00013712 added AUTOSAR Pdu Interface
                        Ms      ESCAN00013963 No changes here
                        Ms      ESCAN00014359 No changes here
                        Ms      ESCAN00014419 Init Default Values (Tms320)
                        Ms      ESCAN00014536 Init Dynamic Timeouts
                        Ms      ESCAN00014539 No changes here
  04.03.00  2005-12-20  Ms      ESCAN00014630 Add Il Rx/Tx Polling for the AUTOSAR PduRouter Interface
  04.04.00  2006-02-23  Ms      ESCAN00014829 IlTxTimeout extern declaration
                        Ms      ESCAN00014880 No changes here
                        Ms      ESCAN00015290 AUTOSAR: Change Interrupt Mapping
                        Ms      ESCAN00015456 [SR:033] Add GENy physical multiple ecu support
                        Ms      ESCAN00015457 [SR:034] Add Dynamic Cycle Time at Init
  04.05.00  2006-03-20  Fz      ESCAN00015656 GM-Only: Compiler Error in IlNodeCommActiveFailed
                        Fz      ESCAN00015622 GM-Only: Compiler Error re-definition of NULL
                        Ms      ESCAN00015682 [SR:032] Signal Group API for GENy
                        Ms      ESCAN00015502 VStdLib Compatibility
  04.06.00  2006-04-10  Ms      ESCAN00015892 Support for AUTOSAR 1.0 management API
                        Ms      ESCAN00015139 [SR:037] IlSendDirect
                        Ms      ESCAN00016071 Dynamic Rx Timeout Value
                        Fz      ESCAN00016041 No changes here
  04.07.00  2006-06-14  Ms      ESCAN00015850 No changes here
                        Ms      ESCAN00016430 [SR:039] AUTOSAR 2.0.0
  04.08.00  2006-06-27  Ms      ESCAN00013964 No changes here
                        Ms      ESCAN00016729 No changes here
                        Ms      ESCAN00016933 GM-Only: Compile error in IlSet/GetRxMessageSourceAddress when using no IL rx polling mode
  04.09.00  2007-04-11  Ms      ESCAN00018540 Compiler warning with Hiware(Metrowerks)
                        Ms      ESCAN00018622 Support Only Hll Based VStdLibs
                        Ms      ESCAN00019703 GM-Only: Move extern declarations to gmlcal.h
                        Ms      ESCAN00019849 GM-Only: No changes here
                        Ms      ESCAN00020000 No changes here
                        Fz      ESCAN00020134 GM-Only: No changes here
                        Ms      ESCAN00020234 GM-Only: No changes here
                        Ms      ESCAN00020235 AUTOSAR API: Remove unreferenced constant defines
  04.10.00  2007-05-10  Ms      ESCAN00013075 Add IlGetModuleContext/IlSetModuleContext
                        Ms      ESCAN00020730 No changes here
                        Ms      ESCAN00021203 GM-Only: No changes here
  05.00.00  2008-01-10  Ms      ESCAN00021361 GM-Only: Compile error in IlVnRx/TxMessageEnabled
                        Ms      ESCAN00021245 IlGetModuleContext/IlSetModuleContext with IfActive
                        Ms      ESCAN00021696 C_ENABLE_MULTI_ECU_PHYS Compatibility
                        Ms      ESCAN00021708 No changes here
                        Ms      ESCAN00021271 IlSendDirect declaration
                        Ms      ESCAN00022375 No changes here
                        Ms      ESCAN00023206 Split Oem Extensions
                        Ms      ESCAN00023270 Near ilIfActiveFlags
                        Ms      ESCAN00023300 Remove Signal Group Buffer Reset
                        Ms      ESCAN00023284 Alterable Memory for Tx Default Value
                        Ms      ESCAN00023821 No changes here
                        Ms      ESCAN00023822 GM-Only: No changes here
  05.01.00  2008-01-25  Ms      ESCAN00023109 PSA-Only: No changes here
  05.02.00  2008-04-21  Ms      ESCAN00026301 SendType IfActive and Multiple Channels
            2008-07-17  Ms      ESCAN00025002 No changes here
                        Ms      ESCAN00028780 Detect Repetition and Signal Activity
                        Ms      ESCAN00025178 No changes here
                        Ms      ESCAN00013854 Support C_COMP_IAR_M16C for Compiler Version >= 3.00
  05.02.01  2008-10-17  Ms      ESCAN00029307 Unsigned comparison with 0 is always false in a preprocessor check
                        Ms      ESCAN00030750 The description of IlRxWait() is incorrect
  05.02.02  2009-08-28  Ml      ESCAN00037350 Resolved typo in Organi define
  05.03.00  2009-11-19  Swa     ESCAN00039257 Added support for DrvCan search algorithm C_SEARCH_ID_MODE
                        Swa     ESCAN00039071 No changes here
                        Swa     ESCAN00039274 Moved type declarations before context struct
            2010-04-20  Swa     ESCAN00042420 IlGetModuleContext/IlSetModuleContext with IfActive for C_COMP_QCC_SH4_RCAN
  05.04.00  2010-06-14  Swa     ESCAN00043305 No changes here
            2010-06-28  Ms      ESCAN00042424 No changes here
  05.05.00  2010-10-27  Ms      ESCAN00046426 Support C_API_3 to indicate reentrant function calls
  05.06.00  2011-06-28  Ms      ESCAN00051034 No changes here
  05.06.01  2011-07-14  Ms      ESCAN00052200 No changes here
  05.06.02  2012-02-06  Ms      ESCAN00056637 No changes here
  05.07.00  2012-01-30  Hho     ESCAN00059505 Support Update Bits (Signal status information)
            2012-03-21  Hho     ESCAN00057706 No changes here
  05.07.01  2012-06-26  Ms      ESCAN00059650 The version defines and constants are not 5.07.00
  05.07.02  2012-10-08  Hho     ESCAN00060945 Clear first value and timeout signal flags upon relevant VN deactivation
  05.08.00  2012-11-05  Hho     ESCAN00062550 improve IlCanCancelNotification runtime
  05.09.00  2013-07-23  Hho     ESCAN00055415 No changes here
  05.10.00  2014-07-18  Hho     ESCAN00077165 Dynamic Start Delay Time Support 
                        Hho     ESCAN00077121 Dynamic Minimum Delay Time Support 
  05.10.01  2015-05-18  Hho     ESCAN00078311 Data changed flags initialized incorrectly/overwritten at initialization/IlRxStart
  05.11.00  2015-09-23  Ms      ESCAN00083676 C_COMP_TI_TMS320_DCAN is not supported
            2015-09-24  Ms      ESCAN00085457 Support C_COMP_TI_TMS320 (ECAN) in VGEN_GENY
  05.11.01  2015-12-18  Ms      ESCAN00087231 No changes here
  05.11.02  2016-08-16  Ms      ESCAN00091028 Compiler warning: truncation of values in IlIndicationOffset with more than 2048 indication flags
  05.11.03  2016-09-23  Ms      ESCAN00092012 Compiler warning: truncation of values in IlRxIndicationFlagsStartIndex with more than 2048 indication flags and multiple channels
**********************************************************************************************************************/

#if !defined ( V_IL_DEF_COMPONENT_HEADER )
# define V_IL_DEF_COMPONENT_HEADER
/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** \defgroup Il_VectorVersion Il_Vector version defines
    \brief The defines are used in the constant Table IlTxType and ilTxState to configure the send behaviour state of Tx messages. */
/**\{*/
/* ##V_CFG_MANAGEMENT ##CQProject : Il_Vector CQComponent : Implementation */
/** This is the Il_Vector bcd coded main- and subversion bcd. */
# define IL_VECTOR_VERSION          0x0511
/** This is the Il_Vector bcd coded releaseversion. */
# define IL_VECTOR_RELEASE_VERSION  0x03
/** This is the Il_Vector decimal Kernelbuilder build version. */
# define IL_VECTOR_BUILD_VERSION    166
/**\}*/

/** \defgroup CommonReturnValue Common Return Values
    \brief The defines are used to evaluate the return value of various Il_Vector functions. */
/**\{*/
/** The function returned successful. */
# define IL_OK                  0
/** The function returned, but the operation was interrupted.
    The function has been called either with and invalid argument or in an invalid call context. */
# define IL_ERROR              -3
/**\}*/

/** \defgroup IlStartCycleReturnValue IlStartCycle Return Values
    \brief The defines are used to evaluate the return value of IlStartCycle. */
/**\{*/
/** The message is already transmitted cyclically. */
# define IL_QUEUED             -2
/**\}*/

/** \defgroup IlBooleanReturnValue Boolean Return Value
    \brief The defines are used to evaluate the return value of the function with Il_Boolean return. */
/**\{*/
# define IL_FALSE            ((Il_Boolean)0)
# define IL_TRUE             ((Il_Boolean)1)
/**\}*/

#  define IL_CAST2UINT8(argument)        ((vuint8) (argument))

/** \defgroup IlTxTypeValuesAndMasks IlTxType Values and Masks
    \brief The defines are used in the constant Table IlTxType and ilTxState to configure the send behaviour state of Tx messages. */
/**\{*/
/** This value is used, if nothing is configured for the message. */
# define kTxNoTxType           (vuint8)0x00
/** The message is transmitted cyclically. */
# define kTxSendCyclic         (vuint8)0x01
/** The message is currently transmitted fast (IfActive). */
# define kTxSendCyclicEvent    (vuint8)0x02
/** The timeout supervision for the message is activated. */
# define kTxCheckTimeout       (vuint8)0x04
/** The message is transmitted with repetition. */
# define kTxNSendRequest       (vuint8)0x08
/** The message is transmitted with the fast cycle rate if the start transition is performed for tx. */
# define kTxFastOnStart        (vuint8)0x10
/** The message will be transmitted if IlSendOnInitMsg is called. */
# define kTxQueueInit          (vuint8)0x20
/** The transmission request to the Data Link layer will be performed in the next IlTxTask call, if possible. */
# define kTxSendRequest        (vuint8)0x80

/** This mask is used to deactivate or decode kTxSendCyclic */
# define kTxNotSendCyclic      (vuint8)0xfe
/** This mask is used to deactivate or decode kTxSendCyclicEvent */
# define kTxNotSendCyclicEvent (vuint8)0xfd
/** This mask is used to deactivate or decode kTxCheckTimeout */
# define kTxNotCheckTimeout    (vuint8)0xfb
/** This mask is used to deactivate or decode kTxNSendRequest */
# define kTxNotNSendRequest    (vuint8)0xf7
/** This mask is used to deactivate or decode kTxFastOnStart */
# define kTxNotFastOnStart     (vuint8)0xef
/** This mask is used to deactivate or decode kTxQueueInit */
# define kTxNotQueueInit       (vuint8)0xdf
/** This mask is used to deactivate or decode kTxSendRequest */
# define kTxNotSendRequest     (vuint8)0x7f
/**\}*/

/** \defgroup ApplIlFatalErrorCodes ApplIlFatalError Error Codes
    \brief The defines are used as parameter for ApplIlFatalError. */
/**\{*/
/** The Tx message handle was not in a valid range. */
# define ILERR_ILLTXMSGHANDLE               (vuint8) 0x02
/** The Rx message handle was not in a valid range. */
# define ILERR_ILLRXMSGHANDLE               (vuint8) 0x03
/** The Tx timeout handle was not in a valid range. */
# define ILERR_ILLTXTIMEOUTINDEX            (vuint8) 0x12
/** The Rx timeout handle was not in a valid range. */
# define ILERR_ILLRXTIMEOUTINDEX            (vuint8) 0x13
/** The channel handle was not in a valid range. */
# define ILERR_ILLCHANNEL                   (vuint8) 0x17
/**\} */

/** \defgroup IL_ChannelStateValuesAndMasks IL_ChannelState Values and Masks
    \brief The defines are used to evaluate the current channel state. */
/**\{*/
/** The Rx and Tx state machine of this channel is in the suspended state. */
# define kIlIsSuspend     (vuint8)0x00
/** The Tx state machine of this channel is in the waiting state. */
# define kIlIsTxWait      (vuint8)0x01
/** The Tx state machine of this channel is in the running state. */
# define kIlIsTxRun       (vuint8)0x02
/** The Rx state machine of this channel is in the waiting state. */
# define kIlIsRxWait      (vuint8)0x04
/** The Rx state machine of this channel is in the running state. */
# define kIlIsRxRun       (vuint8)0x08
/** The Rx and Tx state machine of this channel is in the running state. */
# define kIlIsRxTxRun     (vuint8)0x0A

/** This mask is used to deactivate or decode kIlIsSuspend */
# define kIlIsNotSuspend     (vuint8)0xff
/** This mask is used to deactivate or decode kIlIsTxWait */
# define kIlIsNotTxWait      (vuint8)0xfe
/** This mask is used to deactivate or decode kIlIsTxRun */
# define kIlIsNotTxRun       (vuint8)0xfd
/** This mask is used to deactivate or decode kIlIsRxWait */
# define kIlIsNotRxWait      (vuint8)0xfb
/** This mask is used to deactivate or decode kIlIsRxRun */
# define kIlIsNotRxRun       (vuint8)0xf7
/** This mask is used to deactivate or decode kIlIsRxTxRun */
# define kIlIsNotRxTxRun     (vuint8)0xf5
/**\} */

/** \defgroup SpecialTableValues Reserved Array Constants
    \brief The defines are used to evaluate values in tables with reserved meanings. */
/**\{*/

/** If the IL Tx message handle has no Can Driver Tx handle, this value shall be used in the IlTxIndirection table.
    If the value is not defined by the Can Driver, the maximum value of the datatype CanTransmitHandle must be defined. */
# if !defined( kCanTxHandleNotUsed )
#  define kCanTxHandleNotUsed       ((CanTransmitHandle) 0xFFFFFFFF)
# endif

/** This value shall be used, if ilTxUpdateCounter of an IL Tx message handle is paused.
    The maximum value of the datatype IltTxUpdateCounter must be defined. */
# define kIlStopUpdateCounterValue  ((IltTxUpdateCounter)0xFFFFu)

# if defined ( VGEN_GENY )
/** This value shall be used, if the IL Tx handle has no IlTxTimeoutIndirection. */
#  define kIlNoTxToutIndirection               0x00u
/** This value shall be used, if the IL Tx handle has no IlTxFastOnStartDuration. */
#  define kIlNoFastOnStartDuration             0x01u
/** This value shall be used in IlTxStartCycles, if the IL Tx handle is not transmitted cyclically. */
#  define kIlNoCycleTime                       0x01u
/** This value shall be used in IlTxUpdateCycles, if the IL Tx handle has no delay time. */
#  define kIlNoDelayTime                       0x01u
/** This value shall be used in IlTxEventCycles, if the IL Tx handle cannot be transmitted with a fast cyclic period. */
#  define kIlNoCycleTimeFast                   0x01u
# endif/* VGEN_GENY */
/**\} */

/** \defgroup APIChannelAbstraction API Channel Abstraction
    \brief The defines are used to abstact single channel and multiple channel APIs. */
/**\{*/
# if defined( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
#  define IL_CHANNEL_ILTYPE_ONLY          CanChannelHandle channel
#  define IL_CHANNEL_ILTYPE_FIRST         CanChannelHandle channel,
#  define IL_CHANNEL_ILTYPE_LOCAL         CanChannelHandle channel;
#  define IL_CHANNEL_ILPARA_ONLY          channel
#  define IL_CHANNEL_ILPARA_FIRST         channel,
#  define IL_CHANNEL_ILPARA_MACRO         channel
#  define IL_CHANNEL_ILPRECOPY_MACRO      rxStruct->Channel
# else
#  define IL_CHANNEL_ILTYPE_ONLY          void
#  define IL_CHANNEL_ILTYPE_FIRST
#  define IL_CHANNEL_ILTYPE_LOCAL
#  define IL_CHANNEL_ILPARA_ONLY
#  define IL_CHANNEL_ILPARA_FIRST
#  define IL_CHANNEL_ILPARA_MACRO         0
#  define IL_CHANNEL_ILPRECOPY_MACRO      0
# endif
/**\}*/


/** \defgroup CanChipDataPtr access abstraction for PreTransmit
    \brief The defines are used to abstact the CanChipDataPtr access in the PreTransmit function */
/**\{*/
# if defined(C_MULTIPLE_RECEIVE_CHANNEL) || defined(C_SINGLE_RECEIVE_CHANNEL)
#  define IL_PRETRANSMIT_PARA            ctis
#  define IL_PRETRANSMIT_TYPE            CanTxInfoStruct
#  define IL_PRETRANSMIT_DATA_PTR(para)  para.pChipData
# else
#  define IL_PRETRANSMIT_PARA            txObject
#  define IL_PRETRANSMIT_TYPE            CanChipDataPtr
#  define IL_PRETRANSMIT_DATA_PTR(para)  para
# endif
/**\}*/


/** \defgroup CompatibilityMultipleNodes Multiple Nodes Compatibility
    \brief The defines are used to abstact the multiple nodes of CANGen and GENy. */
/**\{*/
# if defined ( VGEN_GENY )
#  if defined ( IL_ENABLE_SYS_MULTI_ECU_PHYS )
#   define IL_ENABLE_RX_MULTI_ECU_PHYS
#  else/* IL_ENABLE_SYS_MULTI_ECU_PHYS */
#   define IL_DISABLE_RX_MULTI_ECU_PHYS
#  endif
# else
#  if defined ( IL_ENABLE_SYS_MULTIPLE_NODES )
#   define IL_ENABLE_RX_MULTIPLE_NODES
#   define IL_ENABLE_RX_MULTI_ECU_PHYS
#   define IL_ENABLE_SYS_MULTI_ECU_PHYS

#   define tVIdentityMsk                         vuint8
#   define IlRxMsgECUMask                    IlCanRxIdentityAssignment
#   define IlTxMsgECUMask                    IlTxIdentityAssignment
#   define kIlNumberOfIdentities             kIlNumberOfNodes
#   define V_ACTIVE_IDENTITY_LOG             comMultipleECUCurrent
#   define V_ACTIVE_IDENTITY_MSK             ilECUMask

#  else
#   define IL_DISABLE_RX_MULTI_ECU_PHYS
#  endif
# endif
/**\} */

/** \defgroup CompatibilityAUTOSAR AUTOSAR Compatibility
    \brief The defines are used to abstact the IL, Can Driver interface to the AUTOSAR COM interface. */
/**\{*/
/**\} */

#  define IL_MEMROM1  V_MEMROM1
#  define IL_MEMROM2  V_MEMROM2
#  define IL_MEMROM3  V_MEMROM3

/**********************************************************************************************************************
  GLOBAL CHECK MACROS
**********************************************************************************************************************/
/* Compatibility Checks **********************************************************************************************/

# if defined ( VGEN_GENY )
/* Il_Vector - GenTool_Geny Compatibility Check */
#  if !defined( IL_VECTORDLL_VERSION )
#   error "Incompatible Il_Vector - GenTool_Geny with this Il_Vector-Implementation. IL_VECTORDLL_VERSION has to be defined!"
#  endif
#  if !defined( IL_VECTORDLL_RELEASE_VERSION )
#   error "Incompatible Il_Vector - GenTool_Geny with this Il_Vector-Implementation. IL_VECTORDLL_RELEASE_VERSION has to be defined!"
#  endif
#  if defined( IL_VECTORDLL_VERSION ) && defined( IL_VECTORDLL_RELEASE_VERSION )
#   if ( IL_VECTORDLL_VERSION < 0x0107u )
#    error "Incompatible Il_Vector - GenTool_Geny with this Il_Vector-Implementation!"
#   else
#   endif
#  endif

/* required to work around issue in MISRA checker tool */
#  define CANGENEXE_VERSION 0x0000u
#  define CANGENEXE_RELEASE_VERSION 0x00u

# else
/* Il_Vector - GenTool_CanGen Compatibility Check */
#  if !defined( CANGENEXE_VERSION )
#   error "Incompatible Il_Vector - GenTool_CanGen with this Il_Vector-Implementation. CANGENEXE_VERSION has to be defined!"
#  endif
#  if !defined( CANGENEXE_RELEASE_VERSION )
#   error "Incompatible Il_Vector - GenTool_CanGen with this Il_Vector-Implementation. CANGENEXE_RELEASE_VERSION has to be defined!"
#  endif
#  if defined( CANGENEXE_VERSION ) && defined( CANGENEXE_RELEASE_VERSION )
#   if ( CANGENEXE_VERSION < 0x0424u )
#    error "Incompatible Il_Vector - GenTool_CanGen with this Il_Vector-Implementation!"
#   else
#   endif
#  endif

/* required to work around issue in MISRA checker tool */
#  define IL_VECTORDLL_VERSION 0x0000u
#  define IL_VECTORDLL_RELEASE_VERSION 0x00u

# endif

/* Il_Vector GenTool Compatibility Check */
# if ( IL_IMPLEMENTATION_VERSION != 0x0202u )
#  error "Incompatible IL implementation version!"
# endif


/* Common_Vdef-Implementation Compatibility Check */
# if !defined( COMMON_VDEF_VERSION )
#  error "Incompatible Common_Vdef-Implementation with this Il_Vector-Implementation. COMMON_VDEF_VERSION has to be defined!"
# endif
# if !defined( COMMON_VDEF_RELEASE_VERSION )
#  error "Incompatible Common_Vdef-Implementation with this Il_Vector-Implementation. COMMON_VDEF_RELEASE_VERSION has to be defined!"
# endif
# if defined( COMMON_VDEF_VERSION ) && defined( COMMON_VDEF_RELEASE_VERSION )
#  if ( COMMON_VDEF_VERSION < 0x0289u )
#   error "Incompatible Common_Vdef-Implementation with this Il_Vector-Implementation!"
#  else
#  endif
# endif

/* VStdLib Compatibility Check */
# if !defined( VGEN_ENABLE_VSTDLIB ) && !defined ( V_ENABLE_VSTDLIB )
#  error  "Error in File V_cfg.h: VGEN_ENABLE_VSTDLIB or V_ENABLE_VSTDLIB must be defined to use the Common_VStdLib-Implementation for this Il_Vector Implementation."
# endif
/* VStdLib__coreHll-Implementation Compatibility Check */
# if defined( VSTDLIB__COREHLL_VERSION )
#  if ( VSTDLIB__COREHLL_VERSION < 0x0203u )
#   error "Incompatible VStdLib__coreHll-Implementation with this Il_Vector-Implementation!"
#  endif
# else
#  error "Incompatible VStdLib__coreHll-Implementation with this Il_Vector-Implementation. VSTDLIB__COREHLL_VERSION has to be defined!"
# endif /* VSTDLIB__COREHLL_VERSION */
# if defined( VSTDLIB__COREHLL_RELEASE_VERSION )
# else
#  error "Incompatible VStdLib__coreHll-Implementation with this Il_Vector-Implementation. VSTDLIB__COREHLL_RELEASE_VERSION has to be defined!"
# endif /* VSTDLIB__COREHLL_RELEASE_VERSION */

/* Organi Check ******************************************************************************************************/

/* Oem Check *********************************************************************************************************/
# if defined ( VGEN_GENY )
# endif


# if defined( IL_ENABLE_SYS_GET_CONTEXT ) || defined( IL_ENABLE_SYS_SET_CONTEXT )|| \
    defined( VGEN_ENABLE_MDWRAP )        || defined( VGEN_ENABLE_QWRAP )

/* Check not supported Can Drivers */
#  if defined( C_SINGLE_RECEIVE_BUFFER ) || defined( C_MULTIPLE_RECEIVE_BUFFER )
#   error "The IlGetModuleContext/IlSetModuleContext interface is not supported code replicated Can Drivers!"
#  endif
#  if defined ( IL_ENABLE_TX_CYCLIC_EVENT )
#    error "The IlGetModuleContext/IlSetModuleContext Interface cannot be used with Messages and Signals, which have the sendtype IfActive!"
#  endif
/* Check not supported C_COMP switches */
# endif

/* Compatibility Check ***********************************************************************************************/


/* Vector CanDriver Interface Check Channel _Z *******************************************************************/
#  if !defined( XT_TX_DLC )
#   error  "Incompatible CanDriver: Missing Macro 'XT_TX_DLC'"
#  endif

#  if ( C_VERSION_REF_IMPLEMENTATION >= 0x120u )
#   if !defined( CanGetRxDataPtr )
#    error  "Incompatible CanDriver: Missing Macro 'CanGetRxDataPtr'"
#   endif
#   if !defined( CanGetRxDataLen )
#    error  "Incompatible CanDriver: Missing Macro 'CanGetRxDataLen'"
#   endif
#   if !defined( CanGetTxDlc )
#    error  "Incompatible CanDriver: Missing Macro 'CanGetTxDlc'"
#   endif
#   if !defined( CanGetTxDataPtr )
#    error  "Incompatible CanDriver: Missing Macro 'CanGetTxDataPtr'"
#   endif
#  endif
#  if !defined( CanGetConfirmationOffset )
#   error  "Incompatible CanDriver: Missing Macro 'CanGetConfirmationOffset'"
#  endif
#  if !defined( CanGetConfirmationMask )
#   error  "Incompatible CanDriver: Missing Macro 'CanGetConfirmationMask'"
#  endif
#  if !defined( CanGetIndicationOffset )
#   error  "Incompatible CanDriver: Missing Macro 'CanGetIndicationOffset'"
#  endif
#  if !defined( CanGetIndicationMask )
#   error  "Incompatible CanDriver: Missing Macro 'CanGetIndicationMask'"
#  endif
#  if defined ( C_ENABLE_CAN_CANCEL_NOTIFICATION ) && defined( C_MULTIPLE_RECEIVE_CHANNEL )
#   if !defined( CanGetChannelOfTxObj )
#    error  "Incompatible CanDriver: Missing Macro 'CanGetChannelOfTxObj'"
#   endif
#  endif

#  if defined( VGEN_GENY ) && ( C_VERSION_REF_IMPLEMENTATION < 0x130u )
#   error  "Incompatible CanDriver: The Reference Implementation must be higher than Version RI 1.3!"
#  endif

#  if defined( IL_ENABLE_TX_UPDATE_BITS )
#   if !defined( C_ENABLE_MEMCOPY_SUPPORT )
#    error  "Error: CopyToCAN and CopyFromCAN Service must be enabled for UpdateBits!"
#   endif
#  endif

#  if !defined( VGEN_GENY )
#   if !defined( C_SEARCH_INDEX ) && !defined( C_SEARCH_ID_MODE ) && !defined( C_ENABLE_RX_MSG_INDIRECTION )
#    error  "Error in File CAN_CFG.h: Rx Message Indirection has to be enabled"
#   endif
#  endif

#  if ( C_VERSION_REF_IMPLEMENTATION >= 0x130u ) && !defined ( C_ENABLE_CAN_CANCEL_NOTIFICATION )
#   error  "Error in File Can_cfg.h: CAN Cancel Notification has to be enabled!"
#  endif

# if defined( VGEN_GENY )
/* Geny Compiler Switch - Constant Integrity Check *******************************************************************/


/* Compiler Switch - Constant Integrity Check */

/* Value Existance Check */
#  if !defined( kIlNumberOfChannels )
#   error  "Error in File Il_Cfg.h: kIlNumberOfChannels must be defined."
#  else
/* Value Range Check */
#   if ( kIlNumberOfChannels <= 0)
#    error  "Error in File Il_Cfg.h: kIlNumberOfChannels must be > 0."
#   endif
#  endif

/* Value Existance Check */
#  if !defined( kIlNumberOfIdentities )
#   error  "Error in File Il_Cfg.h: kIlNumberOfIdentities must be defined."
#  else
/* Value Range Check */
#   if ( kIlNumberOfIdentities <= 0)
#    error  "Error in File Il_Cfg.h: kIlNumberOfIdentities must be > 0."
#   endif
#  endif

#  if defined( IL_ENABLE_RX )
/* Value Existance Check */
#   if !defined( kIlNumberOfRxObjects )
#    error  "Error in File Il_Cfg.h: kIlNumberOfRxObjects must be defined if IL_ENABLE_RX is defined."
#   else
/* Value Range Check */
#    if ( kIlNumberOfRxObjects <= 0)
#     error  "Error in File Il_Cfg.h: kIlNumberOfRxObjects must be > 0 if IL_ENABLE_RX is defined."
#    endif
#   endif
/* Value Existance Check */
#   if !defined( kIlCanNumberOfRxObjects )
#    error  "Error in File Il_Cfg.h: kIlCanNumberOfRxObjects must be defined if IL_ENABLE_RX is defined."
#   else
/* Value Range Check */
#    if ( kIlCanNumberOfRxObjects <= 0)
#     error  "Error in File Il_Cfg.h: kIlCanNumberOfRxObjects must be > 0 if IL_ENABLE_RX is defined."
#    endif
#   endif
#  elif defined( IL_DISABLE_RX )
/* Value Existance Check */
#   if defined( kIlNumberOfRxObjects )
/* Value Range Check */
#    if ( kIlNumberOfRxObjects != 0 )
#     error  "Error in File Il_Cfg.h: kIlNumberOfRxObjects must be 0 if IL_DISABLE_RX is defined."
#    endif
#   endif
/* Value Existance Check */
#   if defined( kIlCanNumberOfRxObjects )
/* Value Range Check */
#    if ( kIlCanNumberOfRxObjects != 0 )
#     error  "Error in File Il_Cfg.h: kIlCanNumberOfRxObjects must be 0 if IL_DISABLE_RX is defined."
#    endif
#   endif
#  endif
       /* IL_ENABLE_RX */

#  if defined( IL_ENABLE_RX_INDICATION_FLAG )
/* Value Existance Check */
#   if !defined( kIlNumberOfRxIndicationFlags )
#    error  "Error in File Il_Cfg.h: kIlNumberOfRxIndicationFlags must be defined if IL_ENABLE_RX_INDICATION_FLAG is defined."
#   else
/* Value Range Check */
#    if ( kIlNumberOfRxIndicationFlags <= 0)
#     error  "Error in File Il_Cfg.h: kIlNumberOfRxIndicationFlags must be > 0 if IL_ENABLE_RX_INDICATION_FLAG is defined."
#    endif
#   endif
/* Value Existance Check */
#   if !defined( kIlNumberOfRxIndicationBits )
#    error  "Error in File Il_Cfg.h: kIlNumberOfRxIndicationBits must be defined if IL_ENABLE_RX_INDICATION_FLAG is defined."
#   else
/* Value Range Check */
#    if ( kIlNumberOfRxIndicationBits <= 0)
#     error  "Error in File Il_Cfg.h: kIlNumberOfRxIndicationBits must be > 0 if IL_ENABLE_RX_INDICATION_FLAG is defined."
#    endif
#   endif
#  elif defined( IL_DISABLE_RX_INDICATION_FLAG )
/* Value Existance Check */
#   if defined( kIlNumberOfRxIndicationFlags )
/* Value Range Check */
#    if ( kIlNumberOfRxIndicationFlags != 0 )
#     error  "Error in File Il_Cfg.h: kIlNumberOfRxIndicationFlags must be 0 if IL_DISABLE_RX_INDICATION_FLAG is defined."
#    endif
#   endif
/* Value Existance Check */
#   if defined( kIlNumberOfRxIndicationBits )
/* Value Range Check */
#    if ( kIlNumberOfRxIndicationBits != 0 )
#     error  "Error in File Il_Cfg.h: kIlNumberOfRxIndicationBits must be 0 if IL_DISABLE_RX_INDICATION_FLAG is defined."
#    endif
#   endif
#  endif
       /* IL_ENABLE_RX_INDICATION_FLAG */

#  if defined( IL_ENABLE_RX_FIRSTVALUE_FLAG )
/* Value Existance Check */
#   if !defined( kIlNumberOfRxFirstvalueFlags )
#    error  "Error in File Il_Cfg.h: kIlNumberOfRxFirstvalueFlags must be defined if IL_ENABLE_RX_FIRSTVALUE_FLAG is defined."
#   else
/* Value Range Check */
#    if ( kIlNumberOfRxFirstvalueFlags <= 0)
#     error  "Error in File Il_Cfg.h: kIlNumberOfRxFirstvalueFlags must be > 0 if IL_ENABLE_RX_FIRSTVALUE_FLAG is defined."
#    endif
#   endif
#  elif defined( IL_DISABLE_RX_FIRSTVALUE_FLAG )
/* Value Existance Check */
#   if defined( kIlNumberOfRxFirstvalueFlags )
/* Value Range Check */
#    if ( kIlNumberOfRxFirstvalueFlags != 0 )
#     error  "Error in File Il_Cfg.h: kIlNumberOfRxFirstvalueFlags must be 0 if IL_DISABLE_RX_FIRSTVALUE_FLAG is defined."
#    endif
#   endif
#  endif
       /* IL_ENABLE_RX_FIRSTVALUE_FLAG */

#  if defined( IL_ENABLE_RX_DATACHANGED_FLAG )
/* Value Existance Check */
#   if !defined( kIlNumberOfRxDataChangedFlags )
#    error  "Error in File Il_Cfg.h: kIlNumberOfRxDataChangedFlags must be defined if IL_ENABLE_RX_DATACHANGED_FLAG is defined."
#   else
/* Value Range Check */
#    if ( kIlNumberOfRxDataChangedFlags <= 0)
#     error  "Error in File Il_Cfg.h: kIlNumberOfRxDataChangedFlags must be > 0 if IL_ENABLE_RX_DATACHANGED_FLAG is defined."
#    endif
#   endif
#  elif defined( IL_DISABLE_RX_DATACHANGED_FLAG )
/* Value Existance Check */
#   if defined( kIlNumberOfRxDataChangedFlags )
/* Value Range Check */
#    if ( kIlNumberOfRxDataChangedFlags != 0 )
#     error  "Error in File Il_Cfg.h: kIlNumberOfRxDataChangedFlags must be 0 if IL_DISABLE_RX_DATACHANGED_FLAG is defined."
#    endif
#   endif
#  endif
       /* IL_ENABLE_RX_DATACHANGED_FLAG */

#  if defined( IL_ENABLE_RX_TIMEOUT )
/* Value Existance Check */
#   if !defined( kIlNumberOfRxTimeoutCounters )
#    error  "Error in File Il_Cfg.h: kIlNumberOfRxTimeoutCounters must be defined if IL_ENABLE_RX_TIMEOUT is defined."
#   else
/* Value Range Check */
#    if ( kIlNumberOfRxTimeoutCounters <= 0)
#     error  "Error in File Il_Cfg.h: kIlNumberOfRxTimeoutCounters must be > 0 if IL_ENABLE_RX_TIMEOUT is defined."
#    endif
#   endif
/* Value Existance Check */
#   if !defined( kIlNumberOfTimerFlagBytes )
#    error  "Error in File Il_Cfg.h: kIlNumberOfTimerFlagBytes must be defined if IL_ENABLE_RX_TIMEOUT is defined."
#   else
/* Value Range Check */
#    if ( kIlNumberOfTimerFlagBytes <= 0)
#     error  "Error in File Il_Cfg.h: kIlNumberOfTimerFlagBytes must be > 0 if IL_ENABLE_RX_TIMEOUT is defined."
#    endif
#   endif
#  elif defined( IL_DISABLE_RX_TIMEOUT )
/* Value Existance Check */
#   if defined( kIlNumberOfRxTimeoutCounters )
/* Value Range Check */
#    if ( kIlNumberOfRxTimeoutCounters != 0 )
#     error  "Error in File Il_Cfg.h: kIlNumberOfRxTimeoutCounters must be 0 if IL_DISABLE_RX_TIMEOUT is defined."
#    endif
#   endif
/* Value Existance Check */
#   if defined( kIlNumberOfTimerFlagBytes )
/* Value Range Check */
#    if ( kIlNumberOfTimerFlagBytes != 0 )
#     error  "Error in File Il_Cfg.h: kIlNumberOfTimerFlagBytes must be 0 if IL_DISABLE_RX_TIMEOUT is defined."
#    endif
#   endif
#  endif
       /* IL_ENABLE_RX_TIMEOUT */

#  if defined( IL_ENABLE_RX_TIMEOUT_FLAG )
/* Value Existance Check */
#   if !defined( kIlNumberOfRxTimeoutFlags )
#    error  "Error in File Il_Cfg.h: kIlNumberOfRxTimeoutFlags must be defined if IL_ENABLE_RX_TIMEOUT_FLAG is defined."
#   else
/* Value Range Check */
#    if ( kIlNumberOfRxTimeoutFlags <= 0)
#     error  "Error in File Il_Cfg.h: kIlNumberOfRxTimeoutFlags must be > 0 if IL_ENABLE_RX_TIMEOUT_FLAG is defined."
#    endif
#   endif
#  elif defined( IL_DISABLE_RX_TIMEOUT_FLAG )
/* Value Existance Check */
#   if defined( kIlNumberOfRxTimeoutFlags )
/* Value Range Check */
#    if ( kIlNumberOfRxTimeoutFlags != 0 )
#     error  "Error in File Il_Cfg.h: kIlNumberOfRxTimeoutFlags must be 0 if IL_DISABLE_RX_TIMEOUT_FLAG is defined."
#    endif
#   endif
#  endif
       /* IL_ENABLE_RX_TIMEOUT_FLAG */

#  if defined( IL_ENABLE_TX )
/* Value Existance Check */
#   if !defined( kIlNumberOfTxObjects )
#    error  "Error in File Il_Cfg.h: kIlNumberOfTxObjects must be defined if IL_ENABLE_TX is defined."
#   else
/* Value Range Check */
#    if ( kIlNumberOfTxObjects <= 0)
#     error  "Error in File Il_Cfg.h: kIlNumberOfTxObjects must be > 0 if IL_ENABLE_TX is defined."
#    endif
#   endif
#  elif defined( IL_DISABLE_TX )
/* Value Existance Check */
#   if defined( kIlNumberOfTxObjects )
/* Value Range Check */
#    if ( kIlNumberOfTxObjects != 0 )
#     error  "Error in File Il_Cfg.h: kIlNumberOfTxObjects must be 0 if IL_DISABLE_TX is defined."
#    endif
#   endif
#  endif
       /* IL_ENABLE_TX */

#  if defined( IL_ENABLE_TX_CONFIRMATION_FLAG )
/* Value Existance Check */
#   if !defined( kIlNumberOfTxConfirmationFlags )
#    error  "Error in File Il_Cfg.h: kIlNumberOfTxConfirmationFlags must be defined if IL_ENABLE_TX_CONFIRMATION_FLAG is defined."
#   else
/* Value Range Check */
#    if ( kIlNumberOfTxConfirmationFlags <= 0)
#     error  "Error in File Il_Cfg.h: kIlNumberOfTxConfirmationFlags must be > 0 if IL_ENABLE_TX_CONFIRMATION_FLAG is defined."
#    endif
#   endif
#  elif defined( IL_DISABLE_TX_CONFIRMATION_FLAG )
/* Value Existance Check */
#   if defined( kIlNumberOfTxConfirmationFlags )
/* Value Range Check */
#    if ( kIlNumberOfTxConfirmationFlags != 0 )
#     error  "Error in File Il_Cfg.h: kIlNumberOfTxConfirmationFlags must be 0 if IL_DISABLE_TX_CONFIRMATION_FLAG is defined."
#    endif
#   endif
#  endif
       /* IL_ENABLE_TX_CONFIRMATION_FLAG */

#  if defined( IL_DISABLE_TX_VARYING_REPETITION )
#  elif defined( IL_ENSABLE_TX_VARYING_REPETITION )
#   if defined( kIlNumberOfTxConfirmationFlags )
#    if ( kIlNumberOfTxConfirmationFlags != 0 )
#     error  "Error in File Il_Cfg.h: kIlNumberOfTxConfirmationFlags must be 0 if IL_ENSABLE_TX_VARYING_REPETITION is defined."
#    endif
#   endif
#  endif
       /* IL_ENABLE_TX_VARYING_REPETITION */

#  if defined( IL_ENABLE_TX_TIMEOUT )
/* Value Existance Check */
#   if !defined( kIlNumberOfTxTimeoutCounters )
#    error  "Error in File Il_Cfg.h: kIlNumberOfTxTimeoutCounters must be defined if IL_ENABLE_TX_TIMEOUT is defined."
#   else
/* Value Range Check */
#    if ( kIlNumberOfTxTimeoutCounters <= 0)
#     error  "Error in File Il_Cfg.h: kIlNumberOfTxTimeoutCounters must be > 0 if IL_ENABLE_TX_TIMEOUT is defined."
#    endif
#   endif
#  elif defined( IL_DISABLE_TX_TIMEOUT )
/* Value Existance Check */
#   if defined( kIlNumberOfTxTimeoutCounters )
/* Value Range Check */
#    if ( kIlNumberOfTxTimeoutCounters != 0 )
#     error  "Error in File Il_Cfg.h: kIlNumberOfTxTimeoutCounters must be 0 if IL_DISABLE_TX_TIMEOUT is defined."
#    endif
#   endif
#  endif
       /* IL_ENABLE_TX_TIMEOUT */

#  if defined( IL_ENABLE_TX_TIMEOUT_FLAG )
/* Value Existance Check */
#   if !defined( kIlNumberOfTxTimeoutFlags )
#    error  "Error in File Il_Cfg.h: kIlNumberOfTxTimeoutFlags must be defined if IL_ENABLE_TX_TIMEOUT_FLAG is defined."
#   else
/* Value Range Check */
#    if ( kIlNumberOfTxTimeoutFlags <= 0)
#     error  "Error in File Il_Cfg.h: kIlNumberOfTxTimeoutFlags must be > 0 if IL_ENABLE_TX_TIMEOUT_FLAG is defined."
#    endif
#   endif
#  elif defined( IL_DISABLE_TX_TIMEOUT_FLAG )
/* Value Existance Check */
#   if defined( kIlNumberOfTxTimeoutFlags )
/* Value Range Check */
#    if ( kIlNumberOfTxTimeoutFlags != 0 )
#     error  "Error in File Il_Cfg.h: kIlNumberOfTxTimeoutFlags must be 0 if IL_DISABLE_TX_TIMEOUT_FLAG is defined."
#    endif
#   endif
#  endif
       /* IL_ENABLE_TX_TIMEOUT_FLAG */


/* Compiler Switch Integrity Check */

#  if defined( IL_ENABLE_RX ) && defined( IL_DISABLE_RX )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_RX' and 'IL_DISABLE_RX' is defined."
#  endif
#  if defined( IL_ENABLE_RX_DATACHANGED_FLAG ) && defined( IL_DISABLE_RX_DATACHANGED_FLAG )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_RX_DATACHANGED_FLAG' and 'IL_DISABLE_RX_DATACHANGED_FLAG' is defined."
#  endif
#  if defined( IL_ENABLE_RX_DEFAULTVALUE ) && defined( IL_DISABLE_RX_DEFAULTVALUE )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_RX_DEFAULTVALUE' and 'IL_DISABLE_RX_DEFAULTVALUE' is defined."
#  endif
#  if defined( IL_ENABLE_RX_DYNAMIC_TIMEOUT ) && defined( IL_DISABLE_RX_DYNAMIC_TIMEOUT )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_RX_DYNAMIC_TIMEOUT' and 'IL_DISABLE_RX_DYNAMIC_TIMEOUT' is defined."
#  endif
#  if defined( IL_ENABLE_RX_FIRSTVALUE_FLAG ) && defined( IL_DISABLE_RX_FIRSTVALUE_FLAG )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_RX_FIRSTVALUE_FLAG' and 'IL_DISABLE_RX_FIRSTVALUE_FLAG' is defined."
#  endif
#  if defined( IL_ENABLE_RX_INDICATION_FLAG ) && defined( IL_DISABLE_RX_INDICATION_FLAG )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_RX_INDICATION_FLAG' and 'IL_DISABLE_RX_INDICATION_FLAG' is defined."
#  endif
#  if defined( IL_ENABLE_RX_INTERRUPT ) && defined( IL_DISABLE_RX_INTERRUPT )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_RX_INTERRUPT' and 'IL_DISABLE_RX_INTERRUPT' is defined."
#  endif
#  if defined( IL_ENABLE_RX_MODE_SIGNALS ) && defined( IL_DISABLE_RX_MODE_SIGNALS )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_RX_MODE_SIGNALS' and 'IL_DISABLE_RX_MODE_SIGNALS' is defined."
#  endif
#  if defined( IL_ENABLE_RX_POLLING ) && defined( IL_DISABLE_RX_POLLING )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_RX_POLLING' and 'IL_DISABLE_RX_POLLING' is defined."
#  endif
#  if defined( IL_ENABLE_RX_SIGNAL_START_FCT ) && defined( IL_DISABLE_RX_SIGNAL_START_FCT )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_RX_SIGNAL_START_FCT' and 'IL_DISABLE_RX_SIGNAL_START_FCT' is defined."
#  endif
#  if defined( IL_ENABLE_RX_SIGNAL_STOP_FCT ) && defined( IL_DISABLE_RX_SIGNAL_STOP_FCT )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_RX_SIGNAL_STOP_FCT' and 'IL_DISABLE_RX_SIGNAL_STOP_FCT' is defined."
#  endif
#  if defined( IL_ENABLE_RX_START_DEFAULTVALUE ) && defined( IL_DISABLE_RX_START_DEFAULTVALUE )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_RX_START_DEFAULTVALUE' and 'IL_DISABLE_RX_START_DEFAULTVALUE' is defined."
#  endif
#  if defined( IL_ENABLE_RX_STOP_DEFAULTVALUE ) && defined( IL_DISABLE_RX_STOP_DEFAULTVALUE )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_RX_STOP_DEFAULTVALUE' and 'IL_DISABLE_RX_STOP_DEFAULTVALUE' is defined."
#  endif
#  if defined( IL_ENABLE_RX_TIMEOUT ) && defined( IL_DISABLE_RX_TIMEOUT )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_RX_TIMEOUT' and 'IL_DISABLE_RX_TIMEOUT' is defined."
#  endif
#  if defined( IL_ENABLE_RX_TIMEOUT_DELAY ) && defined( IL_DISABLE_RX_TIMEOUT_DELAY )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_RX_TIMEOUT_DELAY' and 'IL_DISABLE_RX_TIMEOUT_DELAY' is defined."
#  endif
#  if defined( IL_ENABLE_RX_TIMEOUT_FLAG ) && defined( IL_DISABLE_RX_TIMEOUT_FLAG )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_RX_TIMEOUT_FLAG' and 'IL_DISABLE_RX_TIMEOUT_FLAG' is defined."
#  endif
#  if defined( IL_ENABLE_SYS_ARGCHECK ) && defined( IL_DISABLE_SYS_ARGCHECK )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_SYS_ARGCHECK' and 'IL_DISABLE_SYS_ARGCHECK' is defined."
#  endif
#  if defined( IL_ENABLE_SYS_INIT_FCT ) && defined( IL_DISABLE_SYS_INIT_FCT )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_SYS_INIT_FCT' and 'IL_DISABLE_SYS_INIT_FCT' is defined."
#  endif
#  if defined ( VGEN_GENY )
#   if defined( IL_ENABLE_SYS_MULTI_ECU_PHYS ) && defined( IL_DISABLE_SYS_MULTI_ECU_PHYS )
#    error "Error in File Il_Cfg.h: 'IL_ENABLE_SYS_MULTI_ECU_PHYS' and 'IL_DISABLE_SYS_MULTI_ECU_PHYS' is defined."
#   endif
#  else
#   if defined( IL_ENABLE_SYS_MULTIPLE_NODES ) && defined( IL_DISABLE_SYS_MULTIPLE_NODES )
#    error "Error in File Il_Cfg.h: 'IL_ENABLE_SYS_MULTIPLE_NODES' and 'IL_DISABLE_SYS_MULTIPLE_NODES' is defined."
#   endif
#  endif
#  if defined( IL_ENABLE_SYS_RX_START_FCT ) && defined( IL_DISABLE_SYS_RX_START_FCT )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_SYS_RX_START_FCT' and 'IL_DISABLE_SYS_RX_START_FCT' is defined."
#  endif
#  if defined( IL_ENABLE_SYS_RX_STOP_FCT ) && defined( IL_DISABLE_SYS_RX_STOP_FCT )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_SYS_RX_STOP_FCT' and 'IL_DISABLE_SYS_RX_STOP_FCT' is defined."
#  endif
#  if defined( IL_ENABLE_SYS_SIGNAL_INIT_FCT ) && defined( IL_DISABLE_SYS_SIGNAL_INIT_FCT )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_SYS_SIGNAL_INIT_FCT' and 'IL_DISABLE_SYS_SIGNAL_INIT_FCT' is defined."
#  endif
#  if defined( IL_ENABLE_SYS_TESTDEBUG ) && defined( IL_DISABLE_SYS_TESTDEBUG )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_SYS_TESTDEBUG' and 'IL_DISABLE_SYS_TESTDEBUG' is defined."
#  endif
#  if defined( IL_ENABLE_TX ) && defined( IL_DISABLE_TX )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_TX' and 'IL_DISABLE_TX' is defined."
#  endif
#  if defined( IL_ENABLE_TX_CONFIRMATION_FLAG ) && defined( IL_DISABLE_TX_CONFIRMATION_FLAG )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_TX_CONFIRMATION_FLAG' and 'IL_DISABLE_TX_CONFIRMATION_FLAG' is defined."
#  endif
#  if defined( IL_ENABLE_TX_CYCLIC_EVENT ) && defined( IL_DISABLE_TX_CYCLIC_EVENT )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_TX_CYCLIC_EVENT' and 'IL_DISABLE_TX_CYCLIC_EVENT' is defined."
#  endif
#  if defined( IL_ENABLE_TX_DEFAULTVALUE ) && defined( IL_DISABLE_TX_DEFAULTVALUE )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_TX_DEFAULTVALUE' and 'IL_DISABLE_TX_DEFAULTVALUE' is defined."
#  endif
#  if defined( IL_ENABLE_TX_DYNAMIC_CYCLETIME ) && defined( IL_DISABLE_TX_DYNAMIC_CYCLETIME )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_TX_DYNAMIC_CYCLETIME' and 'IL_DISABLE_TX_DYNAMIC_CYCLETIME' is defined."
#  endif
#  if defined( IL_ENABLE_TX_FAST_ON_START ) && defined( IL_DISABLE_TX_FAST_ON_START )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_TX_FAST_ON_START' and 'IL_DISABLE_TX_FAST_ON_START' is defined."
#  endif
#  if defined( IL_ENABLE_TX_INTERRUPT ) && defined( IL_DISABLE_TX_INTERRUPT )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_TX_INTERRUPT' and 'IL_DISABLE_TX_INTERRUPT' is defined."
#  endif
#  if defined( IL_ENABLE_TX_MODE_SIGNALS ) && defined( IL_DISABLE_TX_MODE_SIGNALS )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_TX_MODE_SIGNALS' and 'IL_DISABLE_TX_MODE_SIGNALS' is defined."
#  endif
#  if defined( IL_ENABLE_TX_POLLING ) && defined( IL_DISABLE_TX_POLLING )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_TX_POLLING' and 'IL_DISABLE_TX_POLLING' is defined."
#  endif
#  if defined( IL_ENABLE_TX_SECURE_EVENT ) && defined( IL_DISABLE_TX_SECURE_EVENT )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_TX_SECURE_EVENT' and 'IL_DISABLE_TX_SECURE_EVENT' is defined."
#  endif
#  if defined( IL_ENABLE_TX_SEND_ON_INIT ) && defined( IL_DISABLE_TX_SEND_ON_INIT )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_TX_SEND_ON_INIT' and 'IL_DISABLE_TX_SEND_ON_INIT' is defined."
#  endif
#  if defined( IL_ENABLE_TX_SIGNAL_START_FCT ) && defined( IL_DISABLE_TX_SIGNAL_START_FCT )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_TX_SIGNAL_START_FCT' and 'IL_DISABLE_TX_SIGNAL_START_FCT' is defined."
#  endif
#  if defined( IL_ENABLE_TX_SIGNAL_STOP_FCT ) && defined( IL_DISABLE_TX_SIGNAL_STOP_FCT )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_TX_SIGNAL_STOP_FCT' and 'IL_DISABLE_TX_SIGNAL_STOP_FCT' is defined."
#  endif
#  if defined( IL_ENABLE_TX_START_DEFAULTVALUE ) && defined( IL_DISABLE_TX_START_DEFAULTVALUE )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_TX_START_DEFAULTVALUE' and 'IL_DISABLE_TX_START_DEFAULTVALUE' is defined."
#  endif
#  if defined( IL_ENABLE_TX_STARTSTOP_CYCLIC ) && defined( IL_DISABLE_TX_STARTSTOP_CYCLIC )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_TX_STARTSTOP_CYCLIC' and 'IL_DISABLE_TX_STARTSTOP_CYCLIC' is defined."
#  endif
#  if defined( IL_ENABLE_TX_STOP_DEFAULTVALUE ) && defined( IL_DISABLE_TX_STOP_DEFAULTVALUE )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_TX_STOP_DEFAULTVALUE' and 'IL_DISABLE_TX_STOP_DEFAULTVALUE' is defined."
#  endif
#  if defined( IL_ENABLE_TX_TIMEOUT ) && defined( IL_DISABLE_TX_TIMEOUT )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_TX_TIMEOUT' and 'IL_DISABLE_TX_TIMEOUT' is defined."
#  endif
#  if defined( IL_ENABLE_TX_TIMEOUT_FLAG ) && defined( IL_DISABLE_TX_TIMEOUT_FLAG )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_TX_TIMEOUT_FLAG' and 'IL_DISABLE_TX_TIMEOUT_FLAG' is defined."
#  endif
#  if defined( IL_ENABLE_TX_VARYING_REPETITION ) && defined( IL_DISABLE_TX_VARYING_REPETITION )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_TX_VARYING_REPETITION' and 'IL_DISABLE_TX_VARYING_REPETITION' is defined."
#  endif
#  if defined( IL_ENABLE_TX_VARYING_TIMEOUT ) && defined( IL_DISABLE_TX_VARYING_TIMEOUT )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_TX_VARYING_TIMEOUT' and 'IL_DISABLE_TX_VARYING_TIMEOUT' is defined."
#  endif
#  if defined( IL_ENABLE_SYS_TX_START_FCT ) && defined( IL_DISABLE_SYS_TX_START_FCT )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_SYS_TX_START_FCT' and 'IL_DISABLE_SYS_TX_START_FCT' is defined."
#  endif
#  if defined( IL_ENABLE_SYS_TX_STOP_FCT ) && defined( IL_DISABLE_SYS_TX_STOP_FCT )
#   error "Error in File Il_Cfg.h: 'IL_ENABLE_SYS_TX_STOP_FCT' and 'IL_DISABLE_SYS_TX_STOP_FCT' is defined."
#  endif

# endif/* VGEN_GENY */

/* Feature Compatibility *********************************************************************************************/
# if defined ( VGEN_GENY )
#  if defined ( IL_ENABLE_SYS_MULTIPLE_NODES )
#   error "The compiler switch IL_ENABLE_SYS_MULTIPLE_NODES is not used any more in Geny by Il_Vector!"
#  endif
# endif

/* Hardware Compiler Compatibility Check *****************************************************************************/
# if defined ( VGEN_GENY )

/* Check supported C_COMP switches for VGEN_GENY */

# else/* VGEN_GENY */

/* Target Specific */

# endif/* VGEN_GENY */

# if !defined ( IL_MEMROM1 )
#  error "IL_MEMROM1 must be defined!"
# endif
# if !defined ( IL_MEMROM2 )
#  error "IL_MEMROM2 must be defined!"
# endif
# if !defined ( IL_MEMROM3 )
#  error "IL_MEMROM3 must be defined!"
# endif

/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/



/**********************************************************************************************************************
  IlGetTxDataPtr
**********************************************************************************************************************/
/** \brief    This method returns the pointer to the buffer of a tx message.
    \param    ilTxHnd  Handle of an IL tx message.
    \return   vuint8*  Pointer to the databuffer.
**********************************************************************************************************************/
# if defined( IL_ENABLE_TX_MODE_SIGNALS ) 
#  define  IlGetTxDataPtr(ilTxHnd)                  (IlTxDataPtr[(ilTxHnd)])
# else
#  define  IlGetTxDataPtr(ilTxHnd)                  (CanGetTxDataPtr(IlGetIlTxIndirection((ilTxHnd))))
# endif

/**********************************************************************************************************************
  IlGetTxDlc
**********************************************************************************************************************/
/** \brief    This method returns the data length code of a tx message.
    \param    ilTxHnd  Handle of an IL tx message.
    \return   vuint8   Dlc of the tx message in bytes.
**********************************************************************************************************************/
# if defined( IL_ENABLE_TX_MODE_SIGNALS ) 
#  define  IlGetTxDlc(ilTxHnd)                      (IlTxDLC[(ilTxHnd)])
# else
#  define  IlGetTxDlc(ilTxHnd)                      (XT_TX_DLC(CanGetTxDlc(IlGetIlTxIndirection((ilTxHnd)))))
# endif


/**********************************************************************************************************************
  IlGetIlTxIndirection
**********************************************************************************************************************/
/** \brief    This method returns the Can Driver Handle of a IL tx message.
    \param    ilTxHnd  Handle of an IL tx message.
    \return   CanTransmitHandle  Can Driver tx message handle.
**********************************************************************************************************************/
# if defined( IL_ENABLE_SYS_MULTI_ECU_PHYS )
#  define IlGetIlTxIndirection(ilTxHnd)             (IlTxIndirection[V_ACTIVE_IDENTITY_LOG][(ilTxHnd)])
# else
#  define IlGetIlTxIndirection(ilTxHnd)             (IlTxIndirection[(ilTxHnd)])
# endif


/**********************************************************************************************************************
  IlGetRxMsgStartIndex
**********************************************************************************************************************/
/** \brief    This method returns the first Il Rx message handle of the channel
              in a kIlNumberOfRxObjects sorted table.
    \param    channel      Handle of the CAN channel.
    \return   IlReceiveHandle  Il Rx message handle
**********************************************************************************************************************/
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
#  define IlGetRxMsgStartIndex(channel)      (IlRxMsgStartIndex[channel])
# else
#  define IlGetRxMsgStartIndex(channel)      0
# endif

/**********************************************************************************************************************
  IlGetTxMsgStartIndex
**********************************************************************************************************************/
/** \brief    This method returns the first IL Tx message handle of the channel
              in a kIlNumberOfTxObjects sorted table.
    \param    channel      Handle of the CAN channel.
    \return   IlTransmitHandle  Il Tx message handle
**********************************************************************************************************************/
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
#  define IlGetTxMsgStartIndex(channel)      (IlTxMsgStartIndex[channel])
# else
#  define IlGetTxMsgStartIndex(channel)      0
# endif

/**********************************************************************************************************************
  Il_ChannelState
**********************************************************************************************************************/
/** \brief    This method serves to access the ilChannelState variable of a channel.
    \param    channel      Handle of the CAN channel.
    \return   vuint8       This variable contains the current state of a channel bit coded.
                           Use the DecodeChannelState and ModifyChannelState macros to extract
                           the current state of the channel.
**********************************************************************************************************************/
# if defined( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
#  define Il_ChannelState(channel)    (ilChannelState[(channel)])
# else
#  define Il_ChannelState(channel)    (ilChannelState)
# endif

# if defined( IL_ENABLE_TX ) && defined( IL_ENABLE_TX_SECURE_EVENT )
/**********************************************************************************************************************
  IlGetTxRepetitionCounter
**********************************************************************************************************************/
/** \brief    This method returns the number of repetitions for an IL Tx handle.
    \param    ilTxHnd      Handle of an IL Tx message.
    \return   IltTxRepetitionCounter  Number of Repetitions.
**********************************************************************************************************************/
#  if defined ( VGEN_GENY )
#   if defined( IL_ENABLE_TX_VARYING_REPETITION )
#    define IlGetTxRepetitionCounter(ilTxHnd)       (IlTxRepetitionCounters[ilTxHnd])
#   else
#    define IlGetTxRepetitionCounter(ilTxHnd)       ((IltTxRepetitionCounter) kIlNumberOfTxRepetitions)
#   endif
#  else
#   define IlGetTxRepetitionCounter(ilTxHnd)        ((IltTxRepetitionCounter) kIlNumberOfTxRepetitions)
#  endif/* VGEN_GENY */
# endif/* IL_ENABLE_TX && IL_ENABLE_TX_SECURE_EVENT */

/**********************************************************************************************************************
  DecodeChannelState
**********************************************************************************************************************/
/** \defgroup DecodeChannelState Decode Il_ChannelState
    \brief    These macros shall be used to decode the return value of Il_ChannelState.
    \param    channel      Handle of the CAN channel.
    \return   (vuint8) 0 : The channel is not in the state.\n
              > 0        : The channel is in the state.
*/
/**\{*/
/** Rx is suspended  */
# define RxSuspended(channel) ((Il_ChannelState((channel)) & (kIlIsRxRun | kIlIsRxWait))==0)
/** Rx is running  */
# define RxEnabled(channel)   ((Il_ChannelState((channel)) & kIlIsRxRun) != 0)
/**\} */


/**********************************************************************************************************************
  IlGetStatusReturnValue
**********************************************************************************************************************/
/** \defgroup IlGetStatusReturnValue Decode IlGetStatus Return Value
    \brief    These macros shall be used to decode the return value of IlGetStatus.
    \param    state           Il_Status returned from IlGetStatus.
    \return   (Il_Status) 0 : The channel is not in the state.\n
              > 0           : The channel is in the state.
*/
/**\{*/
/** Tx is running */
# define IlIsTxRun(state)          (((state) & kIlIsTxRun)               ? 1 : 0)
/** Tx is waiting */
# define IlIsTxWait(state)         (((state) & kIlIsTxWait)              ? 1 : 0)
/** Tx is suspended */
# define IlIsTxSuspend(state)      (((state) & (kIlIsTxWait|kIlIsTxRun)) ? 0 : 1)
/** Rx is running */
# define IlIsRxRun(state)          (((state) & kIlIsRxRun)               ? 1 : 0)
/** Rx is waiting */
# define IlIsRxWait(state)         (((state) & kIlIsRxWait)              ? 1 : 0)
/** Rx is suspended */
# define IlIsRxSuspend(state)      (((state) & (kIlIsRxWait|kIlIsRxRun)) ? 0 : 1)
/**\} */

# if defined ( VGEN_GENY )
/** IL Abstraction of CanGlobalInterruptDisable. */
#  define IlEnterCriticalFlagAccess() CanGlobalInterruptDisable()
/** IL Abstraction of CanGlobalInterruptRestore. */
#  define IlLeaveCriticalFlagAccess() CanGlobalInterruptRestore()

#  if defined( IL_ENABLE_RX_TIMEOUT ) && defined( IL_ENABLE_RX_DYNAMIC_TIMEOUT )
/**********************************************************************************************************************
  IlConvertMs2RxToutCnt
**********************************************************************************************************************/
/** \brief    This method calculates the number of IlRxTask calls in a channel for a Rx timeout time.
    \param    ilChannelCycles  cycle time of IlRxTask calls in milliseconds
    \param    msTime           Rx timeout time time in milliseconds
    \return   IltRxTimeoutCounter   The Rx timeout counter in multiples of IlRxTask calls of this channel.
**********************************************************************************************************************/
#   define IlConvertMs2RxToutCnt(ilChannelCycles, msTime)         ((IltRxTimeoutCounter) ((msTime) / (ilChannelCycles)))
/**********************************************************************************************************************
  IlConvertRxToutCnt2Ms
**********************************************************************************************************************/
/** \brief    This method returns currently set ilRxDynamicTimeoutCounter in milliseconds.
    \param    ilChannelCycles  cycle time of IlRxTask calls in milliseconds
    \param    ilRxTimeoutHnd   Rx timeout handle
    \return   The current Rx timeout in milliseconds for the Rx timeout handle
**********************************************************************************************************************/
#   define IlConvertRxToutCnt2Ms(ilChannelCycles, ilRxTimeoutHnd) (ilRxDynamicTimeoutCounter[(ilRxTimeoutHnd)] * (ilChannelCycles))
#  endif

#  if (defined( IL_ENABLE_TX_DYNAMIC_CYCLETIME ) || defined( IL_ENABLE_TX_DYNAMIC_DELAYTIME ) || defined( IL_ENABLE_TX_DYNAMIC_START_DELAYTIME ))
/**********************************************************************************************************************
  IlConvertChannelCyclesAndMs2TxTicks
**********************************************************************************************************************/
/** \brief    This method returns currently set ilRxDynamicTimeoutCounter in milliseconds.
    \param    ilChannelCycles  cycle time of IlRxTask calls in milliseconds
    \param    ilMsTime         Rx timeout handle
    \return   IltTxCounter     The current Rx timeout in milliseconds for the Rx timeout handle
**********************************************************************************************************************/
#   define IlConvertChannelCyclesAndMs2TxTicks(ilChannelCycles, ilMsTime)    ((ilMsTime) / (ilChannelCycles))
#  endif

#  if defined( IL_ENABLE_TX_DYNAMIC_CYCLETIME )
/**********************************************************************************************************************
  IlSetDynTxCycleTimeMs
**********************************************************************************************************************/
/** \brief    Sets the cycle time of an il message.

              The macro is called from the application. The function has no effect, if the il message handle is not 
              transmitted cyclically. This is defined in the dbc file with the attibutes GenMsgSendType and
              GenSigSendType. Please refer to the technical reference for details. To activate the cyclic transmission
              of an il message handle use the il API function IlStartCycle.
  
    \param_i ilChannelCycles : This value is the call cycle time of the IlTxTask in the current channel in
                               milliseconds. The value is generated to the file il_cfg.h as define
                               e.g. for channel 1 kIlTxCycleTime_1
    \param   ilTxHnd       This value is the handle of the Tx message. The generated file il_par.h contains generated
                           defines for the message handles.
    \param   ilMsTime      This value is the time in milliseconds, until the cyclic event is raised. The value has to
                           be smaller than 65534.
    \return  none
    \context The macro must be called within the Il callback function ApplIlInit or in the signal oriented init callback function.
    \warning Do not use the macro for handles containing multiplexed signals.
**********************************************************************************************************************/
#   if defined( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
#    define IlSetDynTxCycleTimeMs(ilChannelCycles, ilTxHnd, ilMsTime)          IlSetDynTxCycleTimeRaw((ilTxHnd), ((IltTxCounter) IlConvertChannelCyclesAndMs2TxTicks((ilChannelCycles), (ilMsTime))))
#   else
#    define IlSetDynTxCycleTimeMs(ilTxHnd, ilMsTime)                           IlSetDynTxCycleTimeRaw((ilTxHnd), ((IltTxCounter) IlConvertChannelCyclesAndMs2TxTicks((kIlTxCycleTime), (ilMsTime))))
#   endif
#  endif

#  if defined( IL_ENABLE_TX_DYNAMIC_DELAYTIME )
/**********************************************************************************************************************
  IlSetDynTxDelayTimeMs
**********************************************************************************************************************/
/** \brief    Sets the minimum delay time of an il message.
              The macro is called from the application.
  
    \param_i ilChannelCycles : This value is the call cycle time of the IlTxTask in the current channel in
                               milliseconds. The value is generated to the file il_cfg.h as define
                               e.g. for channel 1 kIlTxCycleTime_1
    \param   ilTxHnd       This value is the handle of the Tx message. The generated file il_par.h contains generated
                           defines for the message handles.
    \param   ilMsTime      This value is the minimum delay time in milliseconds, between two send events.
                           The value has to be smaller than 65534.
    \return  none
    \context The macro must be called within the Il callback function ApplIlInit or in the signal oriented init callback function.
    \warning Do not use the macro for handles containing multiplexed signals.
**********************************************************************************************************************/
#   if defined( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
#    define IlSetDynTxDelayTimeMs(ilChannelCycles, ilTxHnd, ilMsTime)          IlSetDynTxDelayTimeRaw((ilTxHnd), ((IltTxUpdateCounter) IlConvertChannelCyclesAndMs2TxTicks((ilChannelCycles), (ilMsTime))))
#   else
#    define IlSetDynTxDelayTimeMs(ilTxHnd, ilMsTime)                           IlSetDynTxDelayTimeRaw((ilTxHnd), ((IltTxUpdateCounter) IlConvertChannelCyclesAndMs2TxTicks((kIlTxCycleTime), (ilMsTime))))
#   endif
#  endif/* IL_ENABLE_TX_DYNAMIC_DELAYTIME */

#  if defined( IL_ENABLE_TX_DYNAMIC_START_DELAYTIME  )
/**********************************************************************************************************************
  IlSetDynTxStartDelayTimeMs
**********************************************************************************************************************/
/** \brief    Sets the start delay time of an il message.
              The macro is called from the application. The function has no effect, if the il message handle is not 
              transmitted cyclically. 
  
    \param_i ilChannelCycles : This value is the call cycle time of the IlTxTask in the current channel in
                               milliseconds. The value is generated to the file il_cfg.h as define
                               e.g. for channel 1 kIlTxCycleTime_1
    \param   ilTxHnd       This value is the handle of the Tx message. The generated file il_par.h contains generated
                           defines for the message handles.
    \param   ilMsTime      This value is the start delay time in milliseconds. The value has to be smaller than 65534.
    \return  none
    \context The macro must be called within the Il callback function ApplIlInit.
    \warning Do not use the macro for handles containing multiplexed signals.
**********************************************************************************************************************/
#   if defined( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
#    define IlSetDynTxStartDelayTimeMs(ilChannelCycles, ilTxHnd, ilMsTime)          IlSetDynTxStartDelayTimeRaw((ilTxHnd),((IltTxCounter) IlConvertChannelCyclesAndMs2TxTicks((ilChannelCycles), (ilMsTime))))
#   else
#    define IlSetDynTxStartDelayTimeMs(ilTxHnd, ilMsTime)                           IlSetDynTxStartDelayTimeRaw((ilTxHnd),((IltTxCounter) IlConvertChannelCyclesAndMs2TxTicks((kIlTxCycleTime), (ilMsTime))))
#   endif
#  endif/* IL_ENABLE_TX_DYNAMIC_START_DELAYTIME  */

# endif/* VGEN_GENY */

/** \ingroup CompatibilityAUTOSAR */
/**\{*/
#  if defined ( IL_ENABLE_TX )
#   define IlGetTxConfirmationFlags(x)   (CanConfirmationFlags._c[x])
#   define IlGetTxConfirmationMask(x)    (CanGetConfirmationMask(x))
#   define IlGetTxConfirmationOffset(x)  (CanGetConfirmationOffset(x))
#  endif

#  if defined ( IL_ENABLE_RX ) && defined ( IL_ENABLE_RX_POLLING )
#   define IlGetRxIndicationFlags(x)     (CanIndicationFlags._c[x])
#   define IlGetRxIndicationMask(x)      (CanGetIndicationMask(x))
#   define IlGetRxIndicationOffset(x)    (CanGetIndicationOffset(x))
#  endif
/**\}*/

/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
typedef void (*IlTxModeCopyFct) (void);
typedef void (*IlIndicationFct) (void);
typedef void (*IlTimeoutIndicationFct) (void);
typedef void (*IlConfirmationFct) (void);
typedef vsint8 Il_Status;
typedef vsint8 Il_Boolean;

# if defined ( VGEN_GENY )
#  if ( kIlNumberOfTxObjects < 256 )
typedef vuint8 IlTransmitHandle;
#  endif
#  if ( kIlNumberOfTxObjects >= 256 ) && ( kIlNumberOfTxObjects < 65536 )
typedef vuint16 IlTransmitHandle;
#  endif
#  if ( kIlNumberOfTxObjects >= 65536 )
#   error "The Maximum Number of supported Tx Objects is exceeded"
#  endif

#  if ( kIlNumberOfRxObjects < 256 )
typedef vuint8 IlReceiveHandle;
#  endif
#  if ( kIlNumberOfRxObjects >= 256 ) && ( kIlNumberOfRxObjects < 65536 )
typedef vuint16 IlReceiveHandle;
#  endif
#  if ( kIlNumberOfRxObjects >= 65536 )
#   error "The Maximum Number of supported Rx Objects is exceeded"
#  endif

#  if defined ( IL_ENABLE_RX_INDICATION_FLAG )
#   if ( kIlNumberOfRxIndicationBits < 256 )
typedef vuint8 IlReceiveFlagHandle;
#   endif
#   if ( kIlNumberOfRxIndicationBits >= 256 ) && ( kIlNumberOfRxIndicationBits < 65536 )
typedef vuint16 IlReceiveFlagHandle;
#   endif
#   if ( kIlNumberOfRxIndicationBits >= 65536 )
#    error "The Maximum Number of supported Rx Objects is exceeded"
#   endif
#   if ( kIlNumberOfRxIndicationBits < 2049 )
typedef vuint8 IltRxIndicationOffset;
#   endif
#   if ( kIlNumberOfRxIndicationBits >= 2049 ) && ( kIlNumberOfRxIndicationBits < 524288 )
typedef vuint16 IltRxIndicationOffset;
#   endif
#   if ( kIlNumberOfRxIndicationBits >= 524288 )
#    error "The Maximum Number of supported kIlNumberOfRxIndicationBits is exceeded"
#   endif
#  endif/* IL_ENABLE_RX_INDICATION_FLAG */

#  if defined( IL_ENABLE_RX_DATACHANGED_FLAG )
#   if ( kIlNumberOfRxDataChangedFlags < 256 )
typedef vuint8 IlRxDataChangedFlagHandle;
#   endif
#   if ( kIlNumberOfRxDataChangedFlags >= 256 ) && ( kIlNumberOfRxDataChangedFlags < 65536 )
typedef vuint16 IlRxDataChangedFlagHandle;
#   endif
#   if ( kIlNumberOfRxDataChangedFlags >= 65536 )
#    error "The Maximum Number of supported Rx Data Change Flags is exceeded"
#   endif
#  endif
       /* IL_ENABLE_RX_DATACHANGED_FLAG */

# else/* VGEN_GENY */

typedef vuint8 IltTxRepetitionCounter;

typedef CanReceiveHandle IlReceiveHandle;
typedef CanTransmitHandle IlTransmitHandle;
typedef CanReceiveHandle IlReceiveFlagHandle;
typedef vuint16 IlRxDataChangedFlagHandle;

# endif/* VGEN_GENY */

# if defined ( C_ENABLE_CAN_CANCEL_NOTIFICATION )
typedef struct IlStartStopHndType
{
  IlTransmitHandle start;
  IlTransmitHandle stop;
} IlStartStopHnd;
# endif

# if defined ( IL_ENABLE_RX_TIMEOUT )
#  if ( kIlNumberOfRxTimeoutCounters < 255 )
typedef vuint8 IlRxTimeoutHandle;
#  endif
#  if ( kIlNumberOfRxTimeoutCounters >= 255 ) && ( kIlNumberOfRxTimeoutCounters < 65535 )
typedef vuint16 IlRxTimeoutHandle;
#  endif
#  if ( kIlNumberOfRxTimeoutCounters >= 65535 )
#   error "The Maximum Number of supported Rx Timeout Counters is exceeded!"
#  endif
# endif/* IL_ENABLE_RX_TIMEOUT */



# if defined( IL_ENABLE_SYS_GET_CONTEXT ) || defined( IL_ENABLE_SYS_SET_CONTEXT )|| \
    defined( VGEN_ENABLE_MDWRAP )        || defined( VGEN_ENABLE_QWRAP )

/* Il_Vector context structure */
typedef struct
{
  vuint32 ilMagicNumber;

#  if defined ( IL_ENABLE_RX_MULTIPLE_NODES )
  vuintx ilECUMask;
#  endif

#  if defined( C_MULTIPLE_RECEIVE_CHANNEL ) && ( kIlNumberOfChannels > 1 )
  vuint8 ilChannelState[kIlNumberOfChannels];
#   if defined( IL_ENABLE_RX_POLLING ) 
  vuint8 ilChannelReceive[kIlNumberOfChannels];
#   endif
#  else
  vuint8 ilChannelState;
#   if defined( IL_ENABLE_RX_POLLING ) 
  vuint8 ilChannelReceive;
#   endif
#  endif

#  if defined ( IL_ENABLE_TX )

  vuint8 ilTxState[kIlNumberOfTxObjects];
  IltTxCounter ilTxCyclicCounter[kIlNumberOfTxObjects];
  IltTxUpdateCounter ilTxUpdateCounter[kIlNumberOfTxObjects];
#   if defined( IL_ENABLE_TX_CYCLIC_EVENT )
#    if defined( VGEN_GENY )
  IlTIfActiveFlag ilIfActiveFlags;
#    else
  _ilIfActiveFlags ilIfActiveFlags;
#    endif
#   endif                       /* IL_ENABLE_TX_CYCLIC_EVENT */
#   if defined( VGEN_GENY ) && defined( IL_ENABLE_TX_DYNAMIC_CYCLETIME )
  IltTxCounter ilTxDynCyclicCycles[kIlNumberOfTxObjects];
#   endif
#   if defined( VGEN_GENY ) && defined( IL_ENABLE_TX_DYNAMIC_DELAYTIME )
  IltTxUpdateCounter ilTxDynDelayCycles[kIlNumberOfTxObjects];
#   endif
#   if defined( VGEN_GENY ) && defined( IL_ENABLE_TX_DYNAMIC_START_DELAYTIME )
  IltTxCounter ilTxDynStartDelayCycles[kIlNumberOfTxObjects];
#   endif
#   if defined( IL_ENABLE_TX_TIMEOUT_FLAG )
  vuint8 ilTxTimeoutFlags[kIlNumberOfTxTimeoutFlags];
#   endif
#   if defined( IL_ENABLE_TX_CONFIRMATION_FLAG )
  vuint8 ilTxConfirmationFlags[kIlNumberOfTxConfirmationFlags];
#   endif
#   if defined( IL_ENABLE_TX_SECURE_EVENT )
  IltTxRepetitionCounter ilTxNSendCounter[kIlNumberOfTxObjects];
#   endif
#   if defined( IL_ENABLE_TX_TIMEOUT )
  IltTxTimeoutCounter ilTxTimeoutCounter[kIlNumberOfTxTimeoutCounters];
#   endif
#   if defined ( IL_ENABLE_TX_CYCLIC_EVENT ) || defined ( IL_ENABLE_TX_SECURE_EVENT ) || defined ( IL_ENABLE_TX_FAST_ON_START )
  IltTxCounter ilTxEventCounter[kIlNumberOfTxObjects];
#   endif
#  endif                        /* IL_ENABLE_TX */

#  if defined ( IL_ENABLE_RX )
#   if defined( IL_ENABLE_RX_TIMEOUT )
  IltRxTimeoutCounter ilRxTimeoutCounter[kIlNumberOfRxTimeoutCounters];
  vuint8 ilRxTimerFlags[kIlNumberOfTimerFlagBytes];
#    if defined ( VGEN_GENY ) && defined( IL_ENABLE_RX_DYNAMIC_TIMEOUT )
  IltRxTimeoutCounter ilRxDynamicTimeoutCounter[kIlNumberOfRxTimeoutCounters];
#    endif
#   endif                       /* IL_ENABLE_RX_TIMEOUT */
#   if defined( IL_ENABLE_RX_DATACHANGED_FLAG )
  vuint8 ilRxDataChangedFlags[kIlNumberOfRxDataChangedFlags];
#   endif
#   if defined( IL_ENABLE_RX_INDICATION_FLAG )
  vuint8 ilRxIndicationFlags[kIlNumberOfRxIndicationFlags];
#   endif
#   if defined( IL_ENABLE_RX_FIRSTVALUE_FLAG )
  vuint8 ilRxFirstvalueFlags[kIlNumberOfRxFirstvalueFlags];
#   endif
#   if defined ( IL_ENABLE_RX_TIMEOUT_FLAG )
  vuint8 ilRxTimeoutFlags[kIlNumberOfRxTimeoutFlags];
#   endif
#   if !defined( VGEN_GENY ) && defined( IL_ENABLE_RX_MODE_SIGNALS )
  _ilModeIndicationFlags ilModeIndicationFlags;
#   endif
#  endif                        /* IL_ENABLE_RX */

}
tIlModuleContextStruct;

typedef tIlModuleContextStruct *tIlModuleContextStructPtr;

# endif/* IL_ENABLE_SYS_GET_CONTEXT || IL_ENABLE_SYS_SET_CONTEXT */

/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/** This variable contains the communication state of each channel. */
# if defined( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
V_MEMRAM0 extern V_MEMRAM1 vuint8 V_MEMRAM2 ilChannelState[kIlNumberOfChannels];
# else
V_MEMRAM0 extern V_MEMRAM1 vuint8 V_MEMRAM2 ilChannelState;
# endif

# if defined ( IL_ENABLE_RX )


#  if defined( IL_ENABLE_RX_TIMEOUT )
/** This variable contains the Rx timeout counter. */
V_MEMRAM0 extern V_MEMRAM1 IltRxTimeoutCounter V_MEMRAM2 ilRxTimeoutCounter[kIlNumberOfRxTimeoutCounters];

#   if defined( VGEN_GENY ) && defined( IL_ENABLE_RX_DYNAMIC_TIMEOUT )
/** This variable contains the dynamic Rx timeout counter. */
V_MEMRAM0 extern V_MEMRAM1 IltRxTimeoutCounter V_MEMRAM2 ilRxDynamicTimeoutCounter[kIlNumberOfRxTimeoutCounters];
#   endif


/** This variable contains a Rx timeout flag for each Rx timeout counter to indicate the reception of the timeout supervised message. */
V_MEMRAM0 extern V_MEMRAM1_NEAR vuint8 V_MEMRAM2_NEAR ilRxTimerFlags[kIlNumberOfTimerFlagBytes];

#  endif/* IL_ENABLE_RX_TIMEOUT */

#  if defined ( IL_ENABLE_RX_INDICATION_FLAG )
/** This variable contains each configured Rx signal indication flag, to indicate the reception of a signal. */
V_MEMRAM0 extern V_MEMRAM1_NEAR vuint8 V_MEMRAM2_NEAR ilRxIndicationFlags[kIlNumberOfRxIndicationFlags];

#  endif

#  if defined ( IL_ENABLE_RX_FIRSTVALUE_FLAG )
/** This variable contains each configured Rx signal firstvalue flag, to indicate the first reception of a signal. */
V_MEMRAM0 extern V_MEMRAM1_NEAR vuint8 V_MEMRAM2_NEAR ilRxFirstvalueFlags[kIlNumberOfRxFirstvalueFlags];

#  endif

#  if defined ( IL_ENABLE_RX_TIMEOUT_FLAG )
/** This variable contains each configured Rx signal timeout flag. */
V_MEMRAM0 extern V_MEMRAM1_NEAR vuint8 V_MEMRAM2_NEAR ilRxTimeoutFlags[kIlNumberOfRxTimeoutFlags];

#  endif

#  if defined ( IL_ENABLE_RX_DATACHANGED_FLAG )
/** This variable contains each configured Rx signal datachanged flag, to indicate the change of the signal value. */
V_MEMRAM0 extern V_MEMRAM1_NEAR vuint8 V_MEMRAM2_NEAR ilRxDataChangedFlags[kIlNumberOfRxDataChangedFlags];

#  endif

#  if !defined (VGEN_GENY) && defined( IL_ENABLE_RX_MODE_SIGNALS )
/** This variable contains for each mode of Rx messages, which contain multiplexed signals a mode indication flag. */
V_MEMRAM0 extern V_MEMRAM1_NEAR _ilModeIndicationFlags V_MEMRAM2_NEAR ilModeIndicationFlags;

#  endif

# endif/* IL_ENABLE_RX */

# if defined ( IL_ENABLE_TX )

/** This variable contains several states and functionalities bit coded for each Tx message.
  76543210
  |||||||+--- Send cyclic  is active
  ||||||+---- cyclic-event is active
  |||||+----- Tx-Timeout check active
  ||||+------ Send request for a single event
  |||+------- manuell cyclic-event is active
  ||+-------- Message is allowed for queueing on-init/reinit of VN
  |+--------- unused
  +---------- Internal send-request for IL-queue.
*/
V_MEMRAM0 extern V_MEMRAM1_NEAR volatile vuint8 V_MEMRAM2_NEAR ilTxState[kIlNumberOfTxObjects];

/** This variable contains the Tx updated counter. If the value is !=0, the transmission of messages is not allowed. */
V_MEMRAM0 extern V_MEMRAM1 IltTxUpdateCounter V_MEMRAM2 ilTxUpdateCounter[kIlNumberOfTxObjects];

#  if defined(C_ENABLE_CAN_CANCEL_NOTIFICATION)
/** CAN handle to Il start stop handle */
V_MEMROM0 extern V_MEMROM1 IlStartStopHnd V_MEMROM2 IlCanHndToIlHnd[kIlCanNumberOfTxObjects];
#  endif

#  if defined ( IL_ENABLE_TX_TIMEOUT )
/** This variable contains the Tx timeout counter. */
V_MEMRAM0 extern V_MEMRAM1 IltTxTimeoutCounter V_MEMRAM2 ilTxTimeoutCounter[kIlNumberOfTxTimeoutCounters];
#  endif
#  if defined( IL_ENABLE_TX_SECURE_EVENT )
/** This variable contains the number of transmit repetitions to be performed for each Tx message. */
V_MEMRAM0 extern V_MEMRAM1 IltTxRepetitionCounter V_MEMRAM2 ilTxNSendCounter[kIlNumberOfTxObjects];
#  endif


#  if defined( IL_ENABLE_TX_CYCLIC_EVENT )
#   if defined( IL_ENABLE_SYS_GET_CONTEXT ) || defined( IL_ENABLE_SYS_SET_CONTEXT )|| \
     defined( VGEN_ENABLE_MDWRAP )        || defined( VGEN_ENABLE_QWRAP )
#    if defined( VGEN_GENY )
/** This variable contains for each Tx ifactive signal an ifactive flag. */
V_MEMRAM0 extern V_MEMRAM1_NEAR IlTIfActiveFlag V_MEMRAM2_NEAR ilIfActiveFlags;
#    else
/** This variable contains for each Tx ifactive signal an ifactive flag. */
V_MEMRAM0 extern V_MEMRAM1_NEAR _ilIfActiveFlags V_MEMRAM2_NEAR ilIfActiveFlags;
#    endif
#   endif
#  endif

#  if defined ( IL_ENABLE_TX_TIMEOUT_FLAG )
/** This variable contains each configured Tx signal timeout flag, to indicate the timeout of a signal. */
V_MEMRAM0 extern V_MEMRAM1_NEAR vuint8 V_MEMRAM2_NEAR ilTxTimeoutFlags[kIlNumberOfTxTimeoutFlags];
#  endif

#  if defined ( IL_ENABLE_TX_CONFIRMATION_FLAG )
/** This variable contains each configured Tx signal confirmation flag, to indicate the successful transmission of a signal. */
V_MEMRAM0 extern V_MEMRAM1_NEAR vuint8 V_MEMRAM2_NEAR ilTxConfirmationFlags[kIlNumberOfTxConfirmationFlags];
#  endif
# endif/* IL_ENABLE_TX */

/** This variable contains the bcd coded main version of the Il_Vector. */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kIlMainVersion;
/** This variable contains the bcd coded sub version of the Il_Vector. */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kIlSubVersion;
/** This variable contains the bcd coded release version of the Il_Vector. */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kIlReleaseVersion;

# if defined ( IL_ENABLE_RX )

#  if defined( IL_ENABLE_RX_MODE_SIGNALS ) || defined( IL_ENABLE_SYS_MULTI_ECU_PHYS ) 
/** This constant contains the length of each Rx message. */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 IlRxDataLen[kIlNumberOfRxObjects];
/** This constant references the data pointer of each Rx message buffer. */
V_MEMROM0 extern V_MEMROM1 RxDataPtr V_MEMROM2 IlRxDataPtr[kIlNumberOfRxObjects];
#  else
#   if !defined ( VGEN_GENY ) && ( C_VERSION_REF_IMPLEMENTATION < 0x120u )
/** If the interface does not exists for former Can Drivers, the interface must be defined by the IL and the tables have to be exported. */
#    if ! defined ( CanGetRxDataLen )
#     define CanGetRxDataLen(i)   CanRxDataLen[(i)]
/** This constant contains the length of each Can Driver Rx message. IL messages are at the beginning in the same order as in the IL. */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 CanRxDataLen[kCanNumberOfRxObjects];
#    endif
#    if ! defined ( CanGetRxDataPtr )
#     define CanGetRxDataPtr(i)   CanRxDataPtr[(i)]
/** This constant references the data pointer of each Can Driver Rx message. IL messages are at the beginning in the same order as in the IL. */
V_MEMROM0 extern V_MEMROM1 RxDataPtr V_MEMROM2 CanRxDataPtr[kCanNumberOfRxObjects];
#    endif
#   endif
#  endif

#  if defined( IL_ENABLE_RX_DEFAULTVALUE )
/** This constant references the data pointer to an array with the length of the Rx message, which contains the default values for all signals. Undefined signals or gaps have the value 0. */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 V_MEMROM3 *V_MEMROM1 V_MEMROM2
  IlRxDefaultInitValue[kIlNumberOfRxObjects];
#  endif
#  if defined ( IL_ENABLE_RX_START_DEFAULTVALUE )
/** This constant references the data pointer to an array with the length of the Rx message.
    The Value referenced by IlRxDefaultInitValue is valid at the transition start, if the referenced IlRxDefaultStartMask has at the bit position the value 1. */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 V_MEMROM3 *V_MEMROM1 V_MEMROM2
  IlRxDefaultStartMask[kIlNumberOfRxObjects];
#  endif
#  if defined ( IL_ENABLE_RX_STOP_DEFAULTVALUE )
/** This constant references the data pointer to an array with the length of the Rx message.
    The Value referenced by IlRxDefaultInitValue is valid at the transition stop, if the referenced IlRxDefaultStopMask has at the bit position the value 1. */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 V_MEMROM3 *V_MEMROM1 V_MEMROM2
  IlRxDefaultStopMask[kIlNumberOfRxObjects];
#  endif

#  if defined ( IL_ENABLE_RX_POLLING )
/** This constant references a IL internal indication function for each Rx messsage if the function is required and generated, else V_NULL. */
V_MEMROM0 extern V_MEMROM1 IlIndicationFct V_MEMROM2 IlCanRxIndicationFctPtr[kIlCanNumberOfRxObjects];
#  endif

#  if defined ( IL_ENABLE_RX_INDICATION_FLAG )
/** This constant contains the byte offset of the table ilRxIndicationFlags for each indication bit. */
V_MEMROM0 extern V_MEMROM1 IltRxIndicationOffset V_MEMROM2 IlIndicationOffset[kIlNumberOfRxIndicationBits];
/** This constant contains a mask for each indication bit, to decode the indication bit in the table ilRxIndicationFlags. */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 IlIndicationMask[kIlNumberOfRxIndicationBits];
#  endif

#  if defined(IL_ENABLE_RX_TIMEOUT)
/** This constant references a IL internal timeout function for each Rx timeout counter if the function is required and generated, else V_NULL. */
V_MEMROM0 extern V_MEMROM1 IlTimeoutIndicationFct V_MEMROM2 IlRxTimeoutFctPtr[kIlNumberOfRxTimeoutCounters];
#    if defined(IL_ENABLE_SYS_MULTI_ECU_PHYS)
/** This constant contains Rx timeout counter for each Rx timeout counter in each identity of an ECU. */
V_MEMROM0 extern V_MEMROM1 IltRxTimeoutCounter V_MEMROM2
  IlRxTimeoutTbl[kIlNumberOfIdentities][kIlNumberOfRxTimeoutCounters];
#    else
/** This constant contains Rx timeout counter for each Rx timeout counter, if the ECU has one identity. */
V_MEMROM0 extern V_MEMROM1 IltRxTimeoutCounter V_MEMROM2 IlRxTimeoutTbl[kIlNumberOfRxTimeoutCounters];
#    endif
#  endif

#  if defined ( VGEN_GENY )
#   if defined( IL_ENABLE_RX_MULTI_ECU_PHYS )
/** This constant contains for each IL message in the CAN Driver table a mapping to the current active identity.
    If the LSB2MSB bitindex(IdentityIndex) is set to 1, the Rx message is active, else not. */
V_MEMROM0 extern V_MEMROM1 tVIdentityMsk V_MEMROM2 IlCanRxIdentityAssignment[kIlCanNumberOfRxObjects];
#   endif
#  else
#   if defined( IL_ENABLE_RX_MULTI_ECU_PHYS )
/** This constant contains for each Can Driver message a mapping to the current active identity.
    If the LSB2MSB bitindex(IdentityIndex) is set to 1, the Rx message is active, else not. */
V_MEMROM0 extern V_MEMROM1 tVIdentityMsk V_MEMROM2 IlCanRxIdentityAssignment[kCanNumberOfRxObjects];
#   endif
#  endif

#  if defined( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
/** This constant contains for each channel the startindex of the first message in
    kIlNumberOfRxObjcets ordered arrays. The last index is kIlNumberOfRxObjcets. */
V_MEMROM0 extern V_MEMROM1 IlReceiveHandle V_MEMROM2 IlRxMsgStartIndex[kIlNumberOfChannels + 1];
#   if defined ( IL_ENABLE_RX_POLLING ) 
/** This constant contains for each channel the startindex of the first Can Driver message in
    kIlCanNumberOfRxObjects ordered arrays. The last index is kIlCanNumberOfRxObjects. */
V_MEMROM0 extern V_MEMROM1 CanReceiveHandle V_MEMROM2 IlCanRxMsgStartIndex[kIlNumberOfChannels + 1];
#   endif
#   if defined( IL_ENABLE_RX_TIMEOUT )
/** This constant contains for each channel the startindex of the first timeout counter in
    kIlNumberOfRxTimeoutCounters ordered arrays. The last index is kIlNumberOfRxTimeoutCounters. */
V_MEMROM0 extern V_MEMROM1 IlReceiveHandle V_MEMROM2 IlRxTimeoutCntStartIndex[kIlNumberOfChannels + 1];
#   endif
#   if defined( IL_ENABLE_RX_TIMEOUT )
/** This constant contains for each channel the startindex of the first timer flag byte in
    kIlNumberOfTimerFlagBytes ordered arrays. The last index is kIlNumberOfTimerFlagBytes. */
V_MEMROM0 extern V_MEMROM1 IlReceiveHandle V_MEMROM2 IlRxTimerFlagsStartIndex[kIlNumberOfChannels + 1];
#   endif
#   if defined( IL_ENABLE_RX_TIMEOUT_FLAG )
/** This constant contains for each channel the startindex of the first timeout flag byte in
    kIlNumberOfRxTimeoutFlags ordered arrays. The last index is kIlNumberOfRxTimeoutFlags. */
V_MEMROM0 extern V_MEMROM1 IlReceiveHandle V_MEMROM2 IlRxTimeoutFlagsStartIndex[kIlNumberOfChannels + 1];
#   endif
#   if defined( IL_ENABLE_RX_FIRSTVALUE_FLAG )
/** This constant contains for each channel the startindex of the first firstvalue flag byte in
    kIlNumberOfRxFirstvalueFlags ordered arrays. The last index is kIlNumberOfRxFirstvalueFlags. */
V_MEMROM0 extern V_MEMROM1 IlReceiveHandle V_MEMROM2 IlRxFirstvalueFlagsStartIndex[kIlNumberOfChannels + 1];
#   endif
#   if defined( IL_ENABLE_RX_INDICATION_FLAG )
/** This constant contains for each channel the startindex of the first indication flag byte in
    kIlNumberOfRxIndicationFlags ordered arrays. The last index is kIlNumberOfRxIndicationFlags. */
V_MEMROM0 extern V_MEMROM1 IltRxIndicationOffset V_MEMROM2 IlRxIndicationFlagsStartIndex[kIlNumberOfChannels + 1];
#   endif
#   if defined( IL_ENABLE_RX_DATACHANGED_FLAG )
/** This constant contains for each channel the startindex of the first datachanged flag byte in
    kIlNumberOfRxDataChangedFlags ordered arrays. The last index is kIlNumberOfRxDataChangedFlags. */
V_MEMROM0 extern V_MEMROM1 IlRxDataChangedFlagHandle V_MEMROM2 IlRxDataChangedFlagsStartIndex[kIlNumberOfChannels + 1];
#   endif
#  endif

# endif/* defined ( IL_ENABLE_RX ) */

# if defined ( IL_ENABLE_TX )

#  if defined( IL_ENABLE_TX_MODE_SIGNALS ) 
/** This constant contains the length of each Tx message. */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 IlTxDLC[kIlNumberOfTxObjects];
/** This constant references the data pointer of each Tx message buffer. */
V_MEMROM0 extern V_MEMROM1 TxDataPtr V_MEMROM2 IlTxDataPtr[kIlNumberOfTxObjects];
#  else
#   if !defined ( VGEN_GENY ) && ( C_VERSION_REF_IMPLEMENTATION < 0x120u )
/** If the interface does not exists for former Can Drivers, the interface must be defined by the IL and the tables have to be exported. */
#    if !defined ( CanGetTxDlc )
#     define CanGetTxDlc(i)       CanTxDlc[(i)]
/** This constant contains the length of each Can Driver Tx message. IL messages are at the beginning in the same order as in the IL. */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 CanTxDlc[kCanNumberOfTxObjects];
#    endif
#    if !defined ( CanGetTxDataPtr )
#     define CanGetTxDataPtr(i)   CanTxDataPtr[(i)]
/** This constant references the data pointer of each Can Driver Tx message buffer. IL messages are at the beginning in the same order as in the IL. */
V_MEMROM0 extern V_MEMROM1 TxDataPtr V_MEMROM2 CanTxDataPtr[kCanNumberOfTxObjects];
#    endif
#   endif
#  endif

#  if defined ( VGEN_GENY ) && defined( IL_ENABLE_TX_SECURE_EVENT ) && defined( IL_ENABLE_TX_VARYING_REPETITION )
V_MEMROM0 extern V_MEMROM1 IltTxRepetitionCounter V_MEMROM2 IlTxRepetitionCounters[kIlNumberOfTxObjects];
#  endif

#  if defined ( IL_ENABLE_TX_START_DEFAULTVALUE )
/** This constant references the data pointer to an array with the length of the Tx message, which contains the default values for all signals. Undefined signals or gaps have the value 0. */
V_MEMROM0 extern IL_MEMROM1 vuint8 IL_MEMROM2 IL_MEMROM3 *V_MEMROM1 V_MEMROM2
  IlTxDefaultStartMask[kIlNumberOfTxObjects];
#  endif
#  if defined( IL_ENABLE_TX_DEFAULTVALUE )
/** This constant references the data pointer to an array with the length of the Tx message.
    The Value referenced by IlTxDefaultInitValue is valid at the transition start, if the referenced IlTxDefaultStartMask has at the bit position the value 1. */
V_MEMROM0 extern IL_MEMROM1 vuint8 IL_MEMROM2 IL_MEMROM3 *V_MEMROM1 V_MEMROM2
  IlTxDefaultInitValue[kIlNumberOfTxObjects];
#  endif
#  if defined ( IL_ENABLE_TX_STOP_DEFAULTVALUE )
/** This constant references the data pointer to an array with the length of the Tx message.
    The Value referenced by IlTxDefaultInitValue is valid at the transition stop, if the referenced IlTxDefaultStopMask has at the bit position the value 1. */
V_MEMROM0 extern IL_MEMROM1 vuint8 IL_MEMROM2 IL_MEMROM3 *V_MEMROM1 V_MEMROM2
  IlTxDefaultStopMask[kIlNumberOfTxObjects];
#  endif

/** This constant contains the predefined sendtype of all Tx messages. */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 IlTxType[kIlNumberOfTxObjects];


/** This constant contains the GenMsgCycleTime of all Tx messages in multiples of IlTxTask calls. */
V_MEMROM0 extern V_MEMROM1 IltTxCounter V_MEMROM2 IlTxCyclicCycles[kIlNumberOfTxObjects];

/** This constant contains the GenMsgStartDelayTime of all Tx messages in multiples of IlTxTask calls. */
V_MEMROM0 extern V_MEMROM1 IltTxCounter V_MEMROM2 IlTxStartCycles[kIlNumberOfTxObjects];

/** This constant contains the GenMsgDelayTime of all Tx messages in multiples of IlTxTask calls. */
V_MEMROM0 extern V_MEMROM1 IltTxUpdateCounter V_MEMROM2 IlTxUpdateCycles[kIlNumberOfTxObjects];

#   if defined ( IL_ENABLE_TX_CYCLIC_EVENT ) || defined ( IL_ENABLE_TX_SECURE_EVENT ) || defined ( IL_ENABLE_TX_FAST_ON_START )
/** This constant contains the GenMsgCycleTimeFast of all Tx messages in multiples of IlTxTask calls. */
V_MEMROM0 extern V_MEMROM1 IltTxCounter V_MEMROM2 IlTxEventCycles[kIlNumberOfTxObjects];
#   endif

#  if defined ( IL_ENABLE_TX_FAST_ON_START )
/** This constant contains the calculated GenMsgFastOnStart of all Tx messages in multiples of IlTxTask calls.
    The GenMsgStartDelayTime is taken additional into account. */
V_MEMROM0 extern V_MEMROM1 IltTxCounter V_MEMROM2 IlTxFastOnStartDuration[kIlNumberOfTxObjects];
#  endif

#  if defined ( VGEN_GENY ) && defined ( IL_ENABLE_TX_FAST_ON_START ) && defined( IL_ENABLE_TX_MODE_SIGNALS )
/** This constant contains calculated mode delay offset times for multiplexor value specific Tx handles of the IL in multiples of IlTxTask calls.
    The values are used to equalize the mode cycles in the transition from the GenMsgFastOnStart time to the normal cyclic transmission. */
V_MEMROM0 extern V_MEMROM1 IltTxCounter V_MEMROM2 IlTxFastOnStartMuxDelay[kIlNumberOfTxObjects];
#  endif

#  if defined ( IL_ENABLE_TX_POLLING )
/** This constant references a IL internal confirmation function for each Tx messsage if the function is required and generated, else V_NULL. */
V_MEMROM0 extern V_MEMROM1 IlConfirmationFct V_MEMROM2 IlTxConfirmationFctPtr[kIlNumberOfTxObjects];
#  endif

#  if defined( IL_ENABLE_TX_TIMEOUT )
/** This constant references for each Tx messsage the Tx timeout handle. The value in this table for the Tx message
    is only valid, if kTxCheckTimeout is set in the ilTxState array is set. */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 IlTxTimeoutIndirection[kIlNumberOfTxObjects];
#  endif

#  if defined(IL_ENABLE_SYS_MULTI_ECU_PHYS)
/** This constant contains for each il Tx message the Can Driver Tx handle in each identity of an ECU. */
V_MEMROM0 extern V_MEMROM1 CanTransmitHandle V_MEMROM2
  IlTxIndirection[kIlNumberOfIdentities][kIlNumberOfTxObjects];
#  else
/** This constant contains for each il Tx message the Can Driver Tx handle, if the ECU has one identity. */
V_MEMROM0 extern V_MEMROM1 CanTransmitHandle V_MEMROM2 IlTxIndirection[kIlNumberOfTxObjects];
#  endif

#  if defined ( IL_ENABLE_TX_MODE_SIGNALS )
/** This constant references for multiplexor value specific Tx handles of the IL functions to copy the multiplexor value specific data. */
V_MEMROM0 extern V_MEMROM1 IlTxModeCopyFct V_MEMROM2 IlTxModeCopyFunctions[kIlNumberOfTxObjects];
#  endif

#  if defined( IL_ENABLE_SYS_MULTI_ECU_PHYS )
/** This constant contains for each IL message a mapping to the current active identity. 
    If the LSB2MSB bitindex(IdentityIndex) is set to 1, the Rx message is active, else not. */
V_MEMROM0 extern V_MEMROM1 tVIdentityMsk V_MEMROM2 IlTxIdentityAssignment[kIlNumberOfTxObjects];
#  endif

#  if defined( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
/** This constant contains for each channel the startindex of the first message in
    kIlNumberOfTxObjcets ordered arrays. The last index is kIlNumberOfTxObjcets. */
V_MEMROM0 extern V_MEMROM1 IlTransmitHandle V_MEMROM2 IlTxMsgStartIndex[kIlNumberOfChannels + 1];
#   if defined( IL_ENABLE_TX_TIMEOUT )
/** This constant contains for each channel the startindex of the first Tx timeout counter in
    kIlNumberOfTxTimeoutCounters ordered arrays. The last index is kIlNumberOfTxTimeoutCounters. */
V_MEMROM0 extern V_MEMROM1 IlTransmitHandle V_MEMROM2 IlTxTimeoutCntStartIndex[kIlNumberOfChannels + 1];
#   endif
#   if defined( IL_ENABLE_TX_CONFIRMATION_FLAG )
/** This constant contains for each channel the startindex of the first Tx confirmation flag in
    kIlNumberOfTxConfirmationFlags ordered arrays. The last index is kIlNumberOfTxConfirmationFlags. */
V_MEMROM0 extern V_MEMROM1 IlTransmitHandle V_MEMROM2 IlTxConfirmationFlagsStartIndex[kIlNumberOfChannels + 1];
#   endif
#   if defined( IL_ENABLE_TX_TIMEOUT_FLAG )
/** This constant contains for each channel the startindex of the first Tx timeout flag in
    kIlNumberOfTxTimeoutFlags ordered arrays. The last index is kIlNumberOfTxTimeoutFlags. */
V_MEMROM0 extern V_MEMROM1 IlTransmitHandle V_MEMROM2 IlTxTimeoutFlagsStartIndex[kIlNumberOfChannels + 1];
#   endif
#   if defined ( VGEN_GENY ) && defined( IL_ENABLE_TX_TIMEOUT ) && defined ( IL_ENABLE_TX_VARYING_TIMEOUT )
/** This constant contains the calculated ILTxTimeout of each channel in multiples of IlTxTask calls. */
V_MEMROM0 extern V_MEMROM1 IltTxTimeoutCounter V_MEMROM2 IlTxTimeout[kIlNumberOfChannels];
#   endif
#  endif

# endif/* defined ( IL_ENABLE_TX ) */




/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  IlInitPowerOn
**********************************************************************************************************************/
/** \brief    This method initializes the Il_Vector on all channels.\n
              IlInit is called for every channel.
    \return   none
    \context  The function must be called with disabled interrupts.\n
              The function must not interrupt IlRxTask, IlRxStateTask, IlTxTask, IlTxStateTask,
              IlInit, IlRxStart, IlTxStart, IlRxStop, IlTxStop.
    \note     The function is called by the Application or Ccl (Communication Control Layer).
**********************************************************************************************************************/
extern void IlInitPowerOn(void);

/**********************************************************************************************************************
  IlInit
**********************************************************************************************************************/
/** \brief    This method initializes the Il_Vector on a channel.\n
              Rx and Tx data buffers and flags are set to the initial state. If no default value for a message is
              defined, the data buffer is set to 0x00.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \context  The function must be called with disabled interrupts.\n
              The function must not interrupt IlRxTask, IlRxStateTask, IlTxTask, IlTxStateTask,
              IlInitPowerOn, IlRxStart, IlTxStart, IlRxStop, IlTxStop.
    \note     The function is called by the Application, Ccl (Communication Control Layer) or IlInitPowerOn.
**********************************************************************************************************************/
extern void IlInit(IL_CHANNEL_ILTYPE_ONLY);

/**********************************************************************************************************************
  IlRxStart
**********************************************************************************************************************/
/** \brief    This method enables the reception of messages.
              The transition "start" of the Rx state machine is performed.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \context  The function must be called on task level.\n
              The function must not interrupt IlRxTask, IlRxStateTask, IlTxTask, IlTxStateTask, 
              IlInitPowerOn, IlInit, IlTxStart, IlRxStop, IlTxStop.
    \note     The function is called by the Application or Nm (Network Management).
**********************************************************************************************************************/
extern void IlRxStart(IL_CHANNEL_ILTYPE_ONLY);

/**********************************************************************************************************************
  IlTxStart
**********************************************************************************************************************/
/** \brief    This method enables the transmission of messages and starts the transmission of periodic messages.
              The transition "start" of the Tx state machine is performed.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \context  The function must be called on task level.\n
              The function must not interrupt IlRxTask, IlRxStateTask, IlTxTask, IlTxStateTask, 
              IlInitPowerOn, IlInit, IlTxStart, IlRxStop, IlTxStop.
    \note     The function is called by the Application or Nm (Network Management).
**********************************************************************************************************************/
extern void IlTxStart(IL_CHANNEL_ILTYPE_ONLY);

/**********************************************************************************************************************
  IlRxStop
**********************************************************************************************************************/
/** \brief    This method disables the reception of messages.
              The transition "stop" of the Rx state machine is performed.
              The method is used for example to enter the Sleep Mode of an ECU.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \context  The function must be called on task level.\n
              The function must not interrupt IlRxTask, IlRxStateTask, IlTxTask, IlTxStateTask, 
              IlInitPowerOn, IlInit, IlTxStart, IlRxStop, IlTxStop.
    \note     The function is called by the Application or Nm (Network Management).
**********************************************************************************************************************/
extern void IlRxStop(IL_CHANNEL_ILTYPE_ONLY);

/**********************************************************************************************************************
  IlTxStop
**********************************************************************************************************************/
/** \brief    This method disables the transmission of messages (Sleep Mode).
              The transition "stop" of the Tx state machine is performed.
              The method is used for example to enter the Sleep Mode of an ECU.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \context  The function must be called on task level.\n
              The function must not interrupt IlInitPowerOn, IlInit, IlRxTask, IlRxStateTask, IlRxTimerTask, IlTxTask,
              IlTxStateTask, IlTxTimerTask, IlRxStart, IlTxStart, IlRxStop
    \note     The function is called by the Application or Nm (Network Management).
**********************************************************************************************************************/
extern void IlTxStop(IL_CHANNEL_ILTYPE_ONLY);

/**********************************************************************************************************************
  IlRxWait
**********************************************************************************************************************/
/** \brief    This method halts the timeout monitoring of reception messages.
              The transition "wait" of the Rx state machine is performed.
              The method is used for example when the bus-off mode of an ECU was entered.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \context  The function can be called on task and interrupt level.
    \note     The function is called by the Application or Nm (Network Management).
**********************************************************************************************************************/
extern void IlRxWait(IL_CHANNEL_ILTYPE_ONLY);

/**********************************************************************************************************************
  IlTxWait
**********************************************************************************************************************/
/** \brief    This method halts the transmission of messages.
              The transition "wait" of the Tx state machine is performed.
              The method is used for example when the bus-off mode of an ECU was entered.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \context  The function can be called on task and interrupt level.
    \note     The function is called by the Application or Nm (Network Management).
**********************************************************************************************************************/
extern void IlTxWait(IL_CHANNEL_ILTYPE_ONLY);

/**********************************************************************************************************************
  IlRxRelease
**********************************************************************************************************************/
/** \brief    The transition "release" of the Rx state machine is performed.\n
              -Restart the Rx Timeout Monitoring\n
              -Clear the timeout flags if IL_ENABLE_SYS_RX_RESET_TIMEOUT_FLAGS_ON_ILRXRELEASE is defined.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \context  The function can be called on task and interrupt level.
    \note     The function is called by the Application or Nm (Network Management).
**********************************************************************************************************************/
extern void IlRxRelease(IL_CHANNEL_ILTYPE_ONLY);

/**********************************************************************************************************************
  IlTxRelease
**********************************************************************************************************************/
/** \brief    This method resumes the transmission of messages from the "Waiting" state.
              The transition "release" of the Tx state machine is performed.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \context  The function can be called on task and interrupt level.
    \note     The function is called by the Application or Nm (Network Management).
**********************************************************************************************************************/
extern void IlTxRelease(IL_CHANNEL_ILTYPE_ONLY);

/**********************************************************************************************************************
  IlRxTask
**********************************************************************************************************************/
/** \brief    This method must be called periodically in the Rx task cycle time configured in the generation tool.
              The IlRxTimerTask and IlRxStateTask are called by this method.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \context  The function must be called on task level.\n
              The function must not interrupt IlRxStateTask, IlTxTask, IlTxStateTask,
              IlInitPowerOn, IlInit, IlRxStart, IlTxStart, IlRxStop, IlTxStop
    \note     The function is called by the Application or Ccl (Communication Control Layer).
**********************************************************************************************************************/
extern void IlRxTask(IL_CHANNEL_ILTYPE_ONLY);

/**********************************************************************************************************************
  IlTxTask
**********************************************************************************************************************/
/** \brief    This method must be called periodically in the Tx task cycle time configured in the generation tool.
              The IlTxTimerTask and IlTxStateTask are called by this method.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \context  The function must be called on task level.\n
              The function must not interrupt IlRxStateTask, IlTxTask, IlTxStateTask,
              IlInitPowerOn, IlInit, IlRxStart, IlTxStart, IlRxStop, IlTxStop
    \note     The function is called by the Application or Ccl (Communication Control Layer).
**********************************************************************************************************************/
extern void IlTxTask(IL_CHANNEL_ILTYPE_ONLY);

/**********************************************************************************************************************
  IlRxStateTask
**********************************************************************************************************************/
/** \brief    This method is called periodically by the IlRxTask. The function can be called in a faster rate 
              than the IlRxTask to check additionally for polled indication events.
              The usage of the IlRxTask shall be preferred.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \context  The function must be called on task level.\n
              The function must not interrupt IlRxStateTask, IlTxTask, IlTxStateTask,
              IlInitPowerOn, IlInit, IlRxStart, IlTxStart, IlRxStop, IlTxStop
    \note     The function is called by the Application or IlRxTask.
**********************************************************************************************************************/
extern void IlRxStateTask(IL_CHANNEL_ILTYPE_ONLY);

/**********************************************************************************************************************
  IlTxStateTask
**********************************************************************************************************************/
/** \brief    This method is called periodically by the IlTxTask. The function can be called in a faster rate,
              than the IlTxTask, to check additionally for polled confirmation events.
              The usage of the IlTxTask shall be preferred.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \context  The function must be called on task level.\n
              The function must not interrupt IlRxStateTask, IlTxTask, IlTxStateTask,
              IlInitPowerOn, IlInit, IlRxStart, IlTxStart, IlRxStop, IlTxStop
    \note     The function is called by the Application or IlTxTask.
**********************************************************************************************************************/
extern void IlTxStateTask(IL_CHANNEL_ILTYPE_ONLY);

/**********************************************************************************************************************
  IlRxTimerTask
**********************************************************************************************************************/
/** \brief    This method is called periodically by the IlRxTask. If the application separates the handling of
              notification and timing and the IlRxTask is not used, this function must be called periodically
              in the Rx task cycle time configured in the generation tool.
              The usage of the IlRxTask shall be preferred.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \context  The function must be called on task level.\n
              The function must not interrupt IlRxStateTask, IlTxTask, IlTxStateTask,
              IlInitPowerOn, IlInit, IlRxStart, IlTxStart, IlRxStop, IlTxStop
    \note     The function is called by the Application or IlRxTask.
**********************************************************************************************************************/
extern void IlRxTimerTask(IL_CHANNEL_ILTYPE_ONLY);

/**********************************************************************************************************************
  IlTxTimerTask
**********************************************************************************************************************/
/** \brief    This method is called periodically by the IlTxTask. If the application separates the handling of
              notification and timing and the IlTxTask is not used, this function must be called periodically
              in the Tx task cycle time configured in the generation tool.
              The usage of the IlTxTask shall be preferred.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \context  The function must be called on task level.\n
              The function must not interrupt IlRxStateTask, IlTxTask, IlTxStateTask,
              IlInitPowerOn, IlInit, IlRxStart, IlTxStart, IlRxStop, IlTxStop
    \note     The function is called by the Application or IlTxTask.
**********************************************************************************************************************/
extern void IlTxTimerTask(IL_CHANNEL_ILTYPE_ONLY);

# if defined ( IL_ENABLE_TX )
/**********************************************************************************************************************
  IlSetEvent
**********************************************************************************************************************/
/** \brief    This method serves to set a transmission request for a message.
    \param    ilTxHnd  Handle of the Tx message.
    \return   none
    \context  The function can be called on task and interrupt level.
    \note     The function is called by the Application or by IlPutTx method.
**********************************************************************************************************************/
extern void IlSetEvent(IlTransmitHandle ilTxHnd) C_API_3;
# endif

# if defined ( IL_ENABLE_TX ) && defined( IL_ENABLE_TX_SECURE_EVENT )
/**********************************************************************************************************************
  IlSecureEvent
**********************************************************************************************************************/
/** \brief    This method serves to set a transmission request for a message with repetitions.
    \param    ilTxHnd  Handle of the Tx message.
    \return   none
    \context  The function can be called on task and interrupt level.
    \note     The function is called by the IlPutTx method.
**********************************************************************************************************************/
     extern void IlSecureEvent(IlTransmitHandle ilTxHnd) C_API_3;
# endif

# if defined ( IL_ENABLE_TX ) && defined ( IL_ENABLE_TX_CYCLIC_EVENT )
/**********************************************************************************************************************
  IlStartEvent
**********************************************************************************************************************/
/** \brief    This method starts the fast cyclic transmission of a message.
    \param    ilTxHnd         Handle of the Tx message.
    \return   (Il_Status) 1 : the fast transmission is started\n
              IL_ERROR      : the ilTxHnd is invalid
    \context  The function can be called on task and interrupt level.
    \note     The function is called by the IlPutTx method.
**********************************************************************************************************************/
     extern Il_Status IlStartEvent(IlTransmitHandle ilTxHnd) C_API_3;
# endif

# if defined ( IL_ENABLE_TX ) && defined ( IL_ENABLE_TX_CYCLIC_EVENT )
/**********************************************************************************************************************
  IlStopEvent
**********************************************************************************************************************/
/** \brief    This method stops the fast cyclic transmission of a message.
    \param    ilTxHnd         Handle of the Tx message.
    \return   (Il_Status) 0 : the fast transmission is stopped\n
              IL_ERROR      : the ilTxHnd is invalid
    \context  The function can be called on task and interrupt level.
    \note     The function is called by the IlPutTx method.
**********************************************************************************************************************/
     extern Il_Status IlStopEvent(IlTransmitHandle ilTxHnd) C_API_3;
# endif

# if defined ( IL_ENABLE_TX_STARTSTOP_CYCLIC )
/**********************************************************************************************************************
  IlStartCycle
**********************************************************************************************************************/
/** \brief    This method serves to start cyclic transmission requests of a message.
              Using this function can violate the predefined behavior of your module!
    \param    ilTxHnd     Handle of the Tx message.
    \return   IL_OK     : the cyclic transmission request is started\n
              IL_QUEUED : the cyclic transmission request is already enabled\n
              IL_ERROR  : the ilTxHnd is invalid
    \context  The function can be called on task and interrupt level.
    \note     The function is called by the Application.
**********************************************************************************************************************/
     extern Il_Status IlStartCycle(IlTransmitHandle ilTxHnd) C_API_3;
# endif

# if defined ( IL_ENABLE_TX_STARTSTOP_CYCLIC )
/**********************************************************************************************************************
  IlStopCycle
**********************************************************************************************************************/
/** \brief    This method serves to stop the cyclic transmission request of a Tx message. Pending transmission
              requests are not taken into account.
              Using this function can violate the predefined behavior of your module!
    \param    ilTxHnd    Handle of the Tx message.
    \return   IL_OK    : the cyclic transmission request is removed\n
              IL_ERROR : the ilTxHnd is invalid
    \context  The function can be called on task and interrupt level.
    \note     The function is called by the Application.
**********************************************************************************************************************/
     extern Il_Status IlStopCycle(IlTransmitHandle ilTxHnd) C_API_3;
# endif

# if defined ( IL_ENABLE_TX_SEND_ON_INIT )
/**********************************************************************************************************************
  IlSendOnInitMsg
**********************************************************************************************************************/
/** \brief    This method serves to set a transmission request flag for all messages configured as SendOnInit messages.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \context  The function must be called on task level.
    \note     The function is called by the Application.
**********************************************************************************************************************/
     extern void IlSendOnInitMsg(IL_CHANNEL_ILTYPE_ONLY);
# endif

/**********************************************************************************************************************
  IlGetStatus
**********************************************************************************************************************/
/** \brief    Gets the current state of the Interaction Layer state machine.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   Il_Status : the value must be decoded with the following set of macros.\n
              The macros will return 0 (false) or 1 (true).
              \li IlIsTxRun(state)     : Tx is running
              \li IlIsTxWait(state)    : Tx is waiting
              \li IlIsTxSuspend(state) : Tx is suspended
              \li IlIsRxRun(state)     : Rx is running
              \li IlIsRxWait(state)    : Rx is waiting
              \li IlIsRxSuspend(state) : Rx is suspended
    \context  The function can be called on task and interrupt level.
    \note     The function is called by the Application.
**********************************************************************************************************************/
     extern Il_Status IlGetStatus(IL_CHANNEL_ILTYPE_ONLY);

# if defined( IL_ENABLE_SEND_DIRECT )
/**********************************************************************************************************************
  IlSendDirect
**********************************************************************************************************************/
/** \brief    Refer to the Application Note AN-ISC-8-1045_IlSendDirect.pdf
    \param    ilTxHnd  Handle of the Tx message.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \warning  Do not use this API, without taking the application note into account.
**********************************************************************************************************************/
     extern void IlSendDirect(IL_CHANNEL_ILTYPE_FIRST IlTransmitHandle ilTxHnd);
# endif

# if defined ( IL_ENABLE_SYS_GET_CONTEXT ) || defined( VGEN_ENABLE_MDWRAP )
/**********************************************************************************************************************
  IlGetModuleContext
**********************************************************************************************************************/
/** \brief    This function copies the context of the component to a structure.
    \param    pContext  pointer to a tIlModuleContextStructPtr context structure.
    \return   none
    \pre      The component context must be saved
    \post     The structure contains the component state
    \context  The function must be called with disabled interrupts.
**********************************************************************************************************************/
     extern void IlGetModuleContext(tIlModuleContextStructPtr pContext);
# endif

# if defined ( IL_ENABLE_SYS_SET_CONTEXT ) || defined( VGEN_ENABLE_QWRAP )
/**********************************************************************************************************************
  IlSetModuleContext
**********************************************************************************************************************/
/** \brief    This function copies a given context to a component.
    \param    pContext      pointer to a tIlModuleContextStructPtr context structure.
    \return   (vuint8) 0  : the magicNumber member of the tIlModuleContextStructPtr parameter is invalid.\n
              (vuint8) 1  : the magicNumber member of the tIlModuleContextStructPtr parameter is valid.
    \pre      The component context must be initialised.
    \post     The structure contains the component state.
    \context  The function must be called with disabled interrupts.
**********************************************************************************************************************/
     extern vuint8 IlSetModuleContext(tIlModuleContextStructPtr pContext);
# endif



/* Callback functions ************************************************************************************************/

# if defined ( IL_ENABLE_SYS_INIT_FCT )
/**********************************************************************************************************************
  ApplIlInit
**********************************************************************************************************************/
/** \brief    This method is called to indicate the performed initialization.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \context  The function is called by the IL in the context of IlInit.
**********************************************************************************************************************/
     extern void ApplIlInit(IL_CHANNEL_ILTYPE_ONLY);
# endif

# if defined ( IL_ENABLE_SYS_RX_START_FCT )
/**********************************************************************************************************************
  ApplIlRxStart
**********************************************************************************************************************/
/** \brief    This method is called to indicate the performed transition start for the Rx state machine.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \context  The function is called by the IL in the context of IlRxStart.
**********************************************************************************************************************/
     extern void ApplIlRxStart(IL_CHANNEL_ILTYPE_ONLY);
# endif

# if defined ( IL_ENABLE_SYS_TX_START_FCT )
/**********************************************************************************************************************
  ApplIlTxStart
**********************************************************************************************************************/
/** \brief    This method is called to indicate the performed transition start for the Tx state machine.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \context  The function is called by the IL in the context of IlTxStart.
**********************************************************************************************************************/
     extern void ApplIlTxStart(IL_CHANNEL_ILTYPE_ONLY);
# endif

# if defined ( IL_ENABLE_SYS_RX_STOP_FCT )
/**********************************************************************************************************************
  ApplIlRxStop
**********************************************************************************************************************/
/** \brief    This method is called to indicate the performed transition stop for the Rx state machine.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \context  The function is called by the IL in the context of IlRxStop.
**********************************************************************************************************************/
     extern void ApplIlRxStop(IL_CHANNEL_ILTYPE_ONLY);
# endif

# if defined ( IL_ENABLE_SYS_TX_STOP_FCT )
/**********************************************************************************************************************
  ApplIlTxStop
**********************************************************************************************************************/
/** \brief    This method is called to indicate the performed transition stop for the Tx state machine.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \context  The function is called by the IL in the context of IlTxStop.
**********************************************************************************************************************/
     extern void ApplIlTxStop(IL_CHANNEL_ILTYPE_ONLY);
# endif

# if defined ( IL_ENABLE_SYS_TESTDEBUG )
/**********************************************************************************************************************
  ApplIlFatalError
**********************************************************************************************************************/
/** \brief    If assertions are configured, this function is called to indicate invalid user conditions
              (API, reentrance), inconsistent generated data, hardware errors and internal errors.
    \param    errorNumber  numeric error code
    \return   none
    \context  The function is be called by the IL on task and interrupt level.
**********************************************************************************************************************/
     extern void ApplIlFatalError(vuint8 errorNumber);
# endif

/* API Macro wrapped internal functions ******************************************************************************/

# if defined ( IL_ENABLE_RX ) && defined ( IL_ENABLE_RX_INDICATION_FLAG )
/**********************************************************************************************************************
  IlGetSignalIndicationFlag
**********************************************************************************************************************/
/** \brief    This method is used by the generated IlGetClr* macros to return and clear indication flags.
    \param    ilRxFlagHnd  Handle of the Rx flag.
    \return   (vuint8) 0 : the indication flag is not set.\n
                     > 0 : the indication flag was set.
    \context  The function can be called on task and interrupt level.
    \note     The function is called by the Application indirectly from the IlGetClr macros.
    \warning  Do not call this Il internal API from the application!
**********************************************************************************************************************/
     extern vuint8 IlGetSignalIndicationFlag(IlReceiveFlagHandle ilRxFlagHnd);
# endif


# if defined( VGEN_GENY ) && defined( IL_ENABLE_TX_DYNAMIC_CYCLETIME )
/**********************************************************************************************************************
  IlSetDynTxCycleTimeRaw
**********************************************************************************************************************/
/** \brief    Sets the cycle time of an Il message.
              The macro is called from the application. The function has no effect, if the Il message handle is not
              transmitted cyclically. This is defined in the dbc database file with the attributes GenMsgSendType and
              GenSigSendType. Please refer to the technical reference for details. To activate the cyclic transmission
              of an Il message handle use the Il API function IlStartCycle.
    \param    ilTxHnd      This value is the handle of the Tx message. The generated file il_par.h contains generated
                           defines for the message handles.
    \param    ilTxTicks     This value is the number of calls of the IlTxTask, until the cyclic event is raised.
    \return   none
    \context  The function must be called within the Il callback function ApplIlInit or in the signal oriented init
              callback function.
    \note     The function is called by the Application.
    \warning  Do not use the function for handles containing multiplexed signals
**********************************************************************************************************************/
     extern void IlSetDynTxCycleTimeRaw(IlTransmitHandle ilTxHnd, IltTxCounter ilTxTicks);
# endif/* VGEN_GENY && IL_ENABLE_TX_DYNAMIC_CYCLETIME */

# if defined( VGEN_GENY ) && defined( IL_ENABLE_TX_DYNAMIC_DELAYTIME )
/**********************************************************************************************************************
  IlSetDynTxDelayTimeRaw
**********************************************************************************************************************/
/** \brief    Sets the minimum delay time of an Il message.
              The macro is called from the application. The function has no effect, if the Il message handle is not
              transmitted cyclically. 
    \param    ilTxHnd      This value is the handle of the Tx message. The generated file il_par.h contains generated
                           defines for the message handles.
    \param    ilTxTicks     This value is the number of calls of the IlTxTask, until the cyclic event is raised.
    \return   none
    \context  The function must be called within the Il callback function ApplIlInit or in the signal oriented init
              callback function.
    \note     The function is called by the Application.
    \warning  Do not use the function for handles containing multiplexed signals
**********************************************************************************************************************/
     extern void IlSetDynTxDelayTimeRaw(IlTransmitHandle ilTxHnd, IltTxUpdateCounter ilTxTicks);
# endif/* VGEN_GENY && IL_ENABLE_TX_DYNAMIC_DELAYTIME */


# if defined( VGEN_GENY ) && defined( IL_ENABLE_TX_DYNAMIC_START_DELAYTIME )
/**********************************************************************************************************************
  IlSetDynTxStartDelayTimeRaw
**********************************************************************************************************************/
/** \brief    Sets the start delay time of an Il message.
              The macro is called from the application. The function has no effect, if the Il message handle is not
              transmitted cyclically. 
    \param    ilTxHnd      This value is the handle of the Tx message. The generated file il_par.h contains generated
                           defines for the message handles.
    \param    ilTxTicks     This value is the number of calls of the IlTxTask, until the cyclic event is raised.
    \return   none
    \context  The function must be called within the Il callback function ApplIlInit.
    \note     The function is called by the Application.
    \warning  Do not use the function for handles containing multiplexed signals
**********************************************************************************************************************/
     extern void IlSetDynTxStartDelayTimeRaw(IlTransmitHandle ilTxHnd, IltTxCounter ilTxTicks);
# endif/* VGEN_GENY && IL_ENABLE_TX_DYNAMIC_START_DELAYTIME */


# if defined( VGEN_GENY ) && defined( IL_ENABLE_SYS_TX_REPETITIONS_ARE_ACTIVE_FCT )
/**********************************************************************************************************************
  IlTxRepetitionsAreActive
**********************************************************************************************************************/
/** \brief    This method can be used to detect if messages with repetitions are queued for transmission on a channel.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   IL_TRUE   : Messages with repetitions are queued for transmission.\n
              IL_FALSE  : No message with repetitions is queued for transmission.
    \context  The function can be called on task and interrupt level.
    \note     The function is called by the Application.
    \warning  The function does not support Virtual Networks.
**********************************************************************************************************************/
     Il_Boolean IlTxRepetitionsAreActive(IL_CHANNEL_ILTYPE_ONLY);
# endif/* VGEN_GENY && IL_ENABLE_TX_REPETITIONS_COMPLETED */

# if defined( VGEN_GENY ) && defined( IL_ENABLE_SYS_TX_SIGNALS_ARE_ACTIVE_FCT )
/**********************************************************************************************************************
  IlTxSignalsAreActive
**********************************************************************************************************************/
/** \brief    This method can be used to detect if signals are active on a channel.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   IL_TRUE   : Signals are in the active state.\n
              IL_FALSE  : No signal is in the active state.
    \context  The function can be called on task and interrupt level.
    \note     The function is called by the Application.
    \warning  The function does not support Virtual Networks.
**********************************************************************************************************************/
     Il_Boolean IlTxSignalsAreActive(IL_CHANNEL_ILTYPE_ONLY);
# endif/* VGEN_GENY && IL_ENABLE_TX_REPETITIONS_COMPLETED */


/* Stack internal functions ******************************************************************************************/

/**********************************************************************************************************************
  IlResetRxTimeoutFlags
**********************************************************************************************************************/
/** \brief    This method clears Rx timeout flags of the Application and internal ilNodeCommActiveTimeoutFlags.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \context  The function can be called on task and interrupt level.
    \note     The function is called by the Application.
    \warning  Do not call this Il internal API from the application!
**********************************************************************************************************************/
     extern void IlResetRxTimeoutFlags(IL_CHANNEL_ILTYPE_ONLY);

/* Il_Vector internal functions **************************************************************************************/

# if !defined( VGEN_GENY )
#  if defined (C_ENABLE_MEMCOPY_SUPPORT)
#  else
/**********************************************************************************************************************
  CanCopyFromCan
**********************************************************************************************************************/
/** \brief    This method serves to copy data from the register of the CAN controller to the message buffer.
    \param    dst  Pointer to the message buffer.
    \param    src  Pointer to the register of the CAN controller.
    \param    len  Number of bytes to be copied
    \return   none
    \context  The function must be called in the call context of a Can Driver precopy function.
**********************************************************************************************************************/
     extern void CanCopyFromCan(void *dst, CanChipDataPtr src, vuint8 len);
#  endif
# endif/* VGEN_GENY */

# if defined( IL_ENABLE_TX ) && defined( IL_ENABLE_TX_CYCLIC_EVENT )
/**********************************************************************************************************************
  InitIfActiveFlags
**********************************************************************************************************************/
/** \brief    This method clears all if active flags of a channel.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \note     The function is called by the IlTxStart.
    \warning  Do not call this Il internal API from the application!
**********************************************************************************************************************/
     extern void InitIfActiveFlags(IL_CHANNEL_ILTYPE_ONLY);
# endif

# if defined( IL_ENABLE_TX )
/**********************************************************************************************************************
  IlResetCanConfirmationFlags
**********************************************************************************************************************/
/** \brief    This method clears all Can Driver confirmation flags of IL Tx messages of a channel.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \note     The function is called by the IlTxStart.
    \warning  Do not call this Il internal API from the application!
**********************************************************************************************************************/
     extern void IlResetCanConfirmationFlags(IL_CHANNEL_ILTYPE_ONLY);
# endif

# if defined( IL_ENABLE_RX ) && defined( IL_ENABLE_RX_POLLING )
/**********************************************************************************************************************
  IlResetCanIndicationFlags
**********************************************************************************************************************/
/** \brief    This method clears all Can Driver indication flags of IL Rx messages of a channel.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \note     The function is called by the IlRxStart.
    \warning  Do not call this Il internal API from the application!
**********************************************************************************************************************/
     extern void IlResetCanIndicationFlags(IL_CHANNEL_ILTYPE_ONLY);
# endif

# if defined( IL_ENABLE_RX ) && !defined( VGEN_GENY ) && defined( IL_ENABLE_RX_MODE_SIGNALS )
/**********************************************************************************************************************
  IlResetModeIndicationFlags
**********************************************************************************************************************/
/** \brief    This method clears IL internal mode indication flags of a channel.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \note     The function is called by the IlRxStart.
    \warning  Do not call this Il internal API from the application!
**********************************************************************************************************************/
     extern void IlResetModeIndicationFlags(IL_CHANNEL_ILTYPE_ONLY);
# endif

# if defined( IL_ENABLE_TX ) && defined( IL_ENABLE_TX_TIMEOUT )
/**********************************************************************************************************************
  IlCheckTxTimeout
**********************************************************************************************************************/
/** \brief    This method checks the IL internal Tx timeout flags, decrements Tx timeout counters, calls Tx timeout
              callback functions and sets Tx timeout flags of a channel.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \note     The function is called by the IlTxTimerTask.
    \warning  Do not call this Il internal API from the application!
**********************************************************************************************************************/
     extern void IlCheckTxTimeout(IL_CHANNEL_ILTYPE_ONLY);
# endif

# if defined( IL_ENABLE_SYS_SIGNAL_INIT_FCT )
/**********************************************************************************************************************
  IlSignalInit
**********************************************************************************************************************/
/** \brief    This method calls all configured init signal callback functions of a channel.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \note     The function is called by IlInit.
    \warning  Do not call this Il internal API from the application!
**********************************************************************************************************************/
     extern void IlSignalInit(IL_CHANNEL_ILTYPE_ONLY);
# endif

# if defined( IL_ENABLE_RX ) && defined( IL_ENABLE_RX_SIGNAL_START_FCT )
/**********************************************************************************************************************
  IlSignalRxStart
**********************************************************************************************************************/
/** \brief    This method calls all configured Rx start signal callback functions of a channel.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \note     The function is called by IlRxStart.
    \warning  Do not call this Il internal API from the application!
**********************************************************************************************************************/
     extern void IlSignalRxStart(IL_CHANNEL_ILTYPE_ONLY);
# endif

# if defined( IL_ENABLE_TX ) && defined( IL_ENABLE_TX_SIGNAL_START_FCT )
/**********************************************************************************************************************
  IlSignalTxStart
**********************************************************************************************************************/
/** \brief    This method calls all configured Tx start signal callback functions of a channel.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \note     The function is called by IlTxStart.
    \warning  Do not call this Il internal API from the application!
**********************************************************************************************************************/
     extern void IlSignalTxStart(IL_CHANNEL_ILTYPE_ONLY);
# endif

# if defined( IL_ENABLE_RX ) && defined( IL_ENABLE_RX_SIGNAL_STOP_FCT )
/**********************************************************************************************************************
  IlSignalRxStop
**********************************************************************************************************************/
/** \brief    This method calls all configured Rx stop signal callback functions of a channel.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \note     The function is called by IlRxStop.
    \warning  Do not call this Il internal API from the application!
**********************************************************************************************************************/
     extern void IlSignalRxStop(IL_CHANNEL_ILTYPE_ONLY);
# endif

# if defined( IL_ENABLE_TX ) && defined( IL_ENABLE_TX_SIGNAL_STOP_FCT )
/**********************************************************************************************************************
  IlSignalTxStop
**********************************************************************************************************************/
/** \brief    This method calls all configured Tx stop signal callback functions of a channel.
    \param_i  channel : Handle of the logical Can Driver channel.
    \return   none
    \note     The function is called by IlTxStop.
    \warning  Do not call this Il internal API from the application!
**********************************************************************************************************************/
     extern void IlSignalTxStop(IL_CHANNEL_ILTYPE_ONLY);
# endif




/**********************************************************************************************************************
  END OF FILE: Il_Def.h
**********************************************************************************************************************/
#endif /* V_IL_DEF_COMPONENT_HEADER */
/* STOPSINGLE_OF_MULTIPLE */
