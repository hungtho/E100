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

  \brief Description:  Vector Interaction Layer source file
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
                                              -IlRxStop: supend before defaultvalues
  03.10.00  2000-10-30  Ht                    -adaption to CAN driver with channel index
                                              -call of InitIfActiveFlags only if cyclic event enabled
  03.11.00  2000-11-22  Ht                    parameter channel add in several macros (Reset...)
            2000-12-19  Hn                    -single channel version didn't compile 
                                              -some macros exist now in a multi- and a single-channel version 
  03.12.00  2001-04-12  Ht                    -configurable start of timeout monitoring 
                                              -support of bugfix version added
                                              -bugfix in IlRxTask if Rx is suspend
                                              -bugfix in code douppling
                                              -C_ENABLE_TIMEOUT_DELAY changed to IL_ENABLE_RX_TIMEOUT_DELAY 
            2001-04-20  Ht                    -const -> MEMORY_ROM 
                                              -adaption of functions to Keil C5x5
  03.20.00  2001-06-01  Ht                    -new features:
                                              -Tx: Timeout, Defaultvalues, Send on Init
                                              -Rx: Start-Defautvalues, DataChanged
                                              -indication if rx is waiting
  03.21.00  2001-06-08  Ht                    -modified Tx timeout behaviour    
  03.22.00  2001-08-27  Ht      ESCAN00001154 RxStopDefaultValue will not be set in all cases
                                ESCAN00001340 support mode signals
                                ESCAN00001345 Initialisation of data buffers (second or higher channel) went wrong
                                ESCAN00001361 Parameter type of _memclr and _memcpy changed to (void *) 
  03.23.00  2001-09-09  Ht      ESCAN00001416 Elimination of comiler warnings - Tricore
                                ESCAN00001417 Support Multiple receive channel driver
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
                                ESCAN00002395 DataChanged Flags are not reset in IlRxStart()
                                ESCAN00002303 Initialization for Multiplex signals
                                ESCAN00002305 Linker error for function _memcpy
                                ESCAN00002399 Initialization of Rx default values went wrong
                                ESCAN00002400 _memcpy missing if default values are used only on the second channel
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
            2002-05-15  Pl                    comMultipleECUCurrent channel-index added
            2002-06-20  dH                    added some missing 
  03.32.00  2002-06-17  Ht      ESCAN00003075 Unexpected Rx-Timeout notification in MultiECU systems
                                ESCAN00002791 PowerOn initialization
                                ESCAN00002956 signal irelated start, stop and init callback functions
                                ESCAN00002976 additional get function for indication flags access
            2002-07-08  Stu                   Bugfix for initialisation of index and mask in IlTxTimerTask
  03.33.00  2002-09-09  Et      ESCAN00003694 support STmicro ST7 (beCAN) / Hiware
            2002-09-27  Ht      ESCAN00003839 Disabled Transmission for a single message
            2002-04-11  Hp/Fz   ESCAN00004086 Side-effects when clearing VN-related bits in VN- and  Msg -arrays for indexed systems 
                                ESCAN00004088 Side-effects for Indexed-systems when deactivating VNs 
                                ESCAN00003653 Incomplete code loop in IlTxTimerTask for multiple identity ECUs
                                ESCAN00004085 Speed optimisation
                        Si      ESCAN00004084 support for systems with Tx-Signals or Rx-Signals only added
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
                        Fz      ESCAN00005552 Gm-Only : Timeout value reload changed in IlRxRelease for source learning
  03.37.00  2003-05-12  Ht      ESCAN00005627 setting of RxStart and RxStop Default Values could fail
                        Fz      ESCAN00005560 Gm-Only : Incorrect reception handling of application messages in a Multiple-ECU environment
  03.38.00  2003-05-15  Tri     ESCAN00005676 Implementing memory qualifier V_MEMROM0
  03.39.00  2003-07-16  Tri     ESCAN00006095 V_MEMROM0 not used at pointer to constants
                        Ht      ESCAN00005851 Memory access may fail with Physical Multiple ECU 
                                ESCAN00005852 suppressed transmission after cancelation of a message
                        Hp      ESCAN00005993 Change bit-order for IlVnTxSendOnInit[].
                        Ms      ESCAN00006033 Critical Indirections with more than 255 CAN messages
  03.40.00  2003-07-22  HH      ESCAN00005747 use type cast in front of ~ to prevent compiler warnings
                        HH      ESCAN00005823 added dummy statement in IlResetRxTimeoutFlags.
                        HH      ESCAN00003627 added special prototype for _memcpy for Keil compiler C5x5
                        HH      ESCAN00006157 MISRA compliance improved
                        HH      ESCAN00005996 IlUintType replaced by vuintx
                        HH      ESCAN00006275 missing  in IlRxStartVnMsgSupervision
                        HH      ESCAN00006246 compiler warnings M32C
  03.41.00  2003-08-11  Hp      ESCAN00006202 enabled reception on all indexed channels.
                                ESCAN00006334 Gm-Only : Disallow message reception too early
  03.42.00  2003-08-15  Fz      ESCAN00006391 Gm-Only : Argument check wrong
  03.43.00  2003-08-29  Hp      ESCAN00006483 Gm-Only : Return on fail condition of State-handler
                                              when activating VN's. More checks for VN-Nr in indexed systems.
                                ESCAN00006490 Gm-Only : SourceLearning correction in Multi-Channel indexed systems.
  03.44.00  2003-09-08  Hp      ESCAN00006549 Gm-Only : SourceLearning recovery failure in indexed-multi channel sytems
  03.45.00  2003-09-16  Fz      ESCAN00006614 Gm-Only : Source failed notification will not be done 
  03.46.00  2003-09-29  Fz      ESCAN00006700 Gm-Only : Source failed recovery will not be done after source is
                                              learned and VN(s) where deactivated and reactivated
  03.47.00  2003-11-10  Fz/Hp   ESCAN00006830 Gm-Only : Timeout recovery and notification for signals is not done
                                              on multi channel indexed systems.
  03.48.00  2004-01-16  Fz/Tde/Ms
                                ESCAN00006990 Add of TMS320 support
            2003-11-21  Ms      ESCAN00005823 moved dummy statement in IlResetRxTimeoutFlags
  03.49.00  2003-12-11  HH      ESCAN00007143 use V_MEM_* instead of MEMORY_ROM
                        Fz      ESCAN00007274 Gm-Only : Possible message burst after normal com hold released
            2004-02-10  Ms      ESCAN00007506 Set Rx and Tx Default Values at Start or Stop
            2004-03-01  Ms                    adapted Memory Qualifier
            2004-03-02  Ms                    adapted Version Handling
  03.50.00  2004-04-02  HH                    improved MISRA compliance, uses vstdlib instead of own functions
                                ESCAN00006119 since std lib functions are not provided by the IL any more this
                                              not applicable any more
                                ESCAN00007434 added PSA specific behaviour to avoid setting TxSendRequest
                                              in part offline state when CanTransmit is called
                                ESCAN00000815 common module functions _memcpy and _memclr
            2004-05-24  Fz      ESCAN00008453 Gm-Only : IlClrFlagsMSB2LSB and IlClrFlagsLSB2MSB changed
                                ESCAN00008452 Init of array ilVnTxMessageEnable changed
  03.51.00  2004-07-08  Fz      ESCAN00008800 Gm-Only : Missing variable initialization
                                ESCAN00008538 Gm-Only : Send on init not calibrate able
                                ESCAN00008856 Gm-Only : Wrong notification about failed source
  03.52.00  2004-11-17  Fz      ESCAN00009802 Gm-Only : Issue due to change ESCAN00008453 solved
                        Ms      ESCAN00009576 Replace NULL by V_NULL
                                ESCAN00009575 Remove C_COMP_FJVGC
                                ESCAN00009613 Runtime Improvement IlTxStartCycles
                                ESCAN00009616 Conceptional common usage of function pointer tables 
                                             in IlTxConfirmationFctPtr and IlCanRxIndicationFctPtr
                                ESCAN00009633 Naming Conventions
                                ESCAN00007483 Wrong access to indication and confirmation flags of the CAN driver
                                ESCAN00009836 CanGetChannelOfTxObj <-> CanTxMsgHandleToChannel
                                ESCAN00006085 Add Nullpointers and Assertions
                                ESCAN00009889 Remove Useless (IltTxCounter) Cast
                                ESCAN00010057 No changes here
  04.00.00  2005-06-15  Fz      ESCAN00012536 Gm-Only : Dummy functions are not longer generated.
                                              Parts which have used this assumtion changed
                        Ms      ESCAN00010691 Improve MISRA Compliance
                        Ms      ESCAN00010404 Runtime improvement in IlRxStart
                        Ms      ESCAN00010403 IlResetCanIndicationFlags Preprocessor encapsulation
                        Ms      ESCAN00010709 Invalid Confirmation Notification and StartDelay time for Multiplex Messages
                        Ms      ESCAN00010701 Not GM: Activate ApplIlInit extern declaration
                        Ms      ESCAN00010704 Remove IL_NO_COMPATIBILITY
                        Ms      ESCAN00010825 Simplify the macros to modifiy the IL state
                        Ms      ESCAN00010609 IlRxFirstvalueFlagsStartIndex Spelling
                        Ms      ESCAN00010690 Geny Compatibility
                        Ms      ESCAN00008116 Dynamic Rx Timeouts
                        Ms      ESCAN00008651 SetTxDefaultMask
                        Ms      ESCAN00012393 No changes here
                        Ms      ESCAN00008455 No changes here
                        Fz      ESCAN00011748 Gm-Only : IlClrFlagsMSB2LSB and IlClrFlagsLSB2MSB changed
                        Ms      ESCAN00012640 Support of "No Buffer" configurations
  04.01.00  2005-08-02  Ms      ESCAN00012851 Out of Bounds
                        Ms      ESCAN00012946 Geny: Standard Multiplex Interface
                        Ms      ESCAN00013024 Geny: kIlNumberOfRxIndicationBits used, but not defined
                        Ms      ESCAN00013049 Adapt local/parameter memory qualifiers
                        Fz      ESCAN00012988 Gm-Only : Interface of function IlGetRxMessageSourceAddress changed
  04.02.00  2005-12-07  Ms      ESCAN00013387 added FastOnStart for muliplexed messages
                        Ms      ESCAN00013712 added AUTOSAR Pdu Interface
                        Ms      ESCAN00013963 ilTxState in IlSendOnInitMsg
                        Ms      ESCAN00014359 SetTxDefaultWithMask prototype preprocessor encapsulation
                        Ms      ESCAN00014419 Init Default Values (Tms320)
                        Ms      ESCAN00014536 Init Dynamic Timeouts
                        Ms      ESCAN00014539 Invalid Confirmation Notification and StartDelay time for Multiplex Messages
  04.03.00  2005-12-20  Ms      ESCAN00014630 Add Il Rx/Tx Polling for the AUTOSAR PduRouter Interface
  04.04.00  2006-02-23  Ms      ESCAN00014829 No changes here
                        Ms      ESCAN00014880 Implicit cast in state transition macros
                        Ms      ESCAN00015290 No changes here
                        Ms      ESCAN00015456 [SR:033] Add GENy physical multiple ecu support
                        Ms      ESCAN00015457 [SR:034] Add Dynamic Cycle Time at Init
  04.05.00  2006-03-20  Fz      ESCAN00015656 GM-Only: Compiler Error in IlNodeCommActiveFailed
                        Fz      ESCAN00015622 GM-Only: Compiler Error re-definition of NULL
                        Ms      ESCAN00015682 [SR:032] Signal Group API for GENy
                        Ms      ESCAN00015502 No changes here
  04.06.00  2006-04-10  Ms      ESCAN00015892 No changes here
                        Ms      ESCAN00015139 [SR:037] IlSendDirect
                        Ms      ESCAN00016071 No changes here
                        Fz      ESCAN00016041 Compiler error removed for ST7 with Cosmic
  04.07.00  2006-06-14  Ms      ESCAN00015850 IlTxTask call for channels without Il messages
                        Ms      ESCAN00016430 No changes here
  04.08.00  2006-06-27  Ms      ESCAN00013964 GenMsgDelayTime is not taken into account
                        Ms      ESCAN00016729 Transmission Events in IlStartCycle and IlStopCycle
                        Ms      ESCAN00016614 Com_TriggerTransmit AUTOSAR 2.0
                        Ms      ESCAN00016933 GM-Only: No changes here
  04.09.00  2007-04-11  Ms      ESCAN00018540 No changes here
                        Ms      ESCAN00018622 No changes here
                        Ms      ESCAN00019703 GM-Only: No changes here
                        Ms      ESCAN00019849 GM-Only: Unreferenced static functions
                        Ms      ESCAN00020000 IlCanGenericPrecopy Dummy Statement
                        Fz      ESCAN00020134 GM-Only: Unused variables warnings removed
                        Ms      ESCAN00020234 GM-Only: IlNwmInit Preprocessor encapsulation
                        Ms      ESCAN00020235 No changes here
  04.10.00  2007-05-10  Ms      ESCAN00013075 Add IlGetModuleContext/IlSetModuleContext
                        Ms      ESCAN00020730 ilPduRxIndicationFlags prototype declaration
                        Ms      ESCAN00021203 GM-Only: Multiple Channel: timeout flag, function or default value
  05.00.00  2008-01-10  Ms      ESCAN00021361 No changes here
                        Ms      ESCAN00021245 No changes here
                        Ms      ESCAN00021696 No changes here
                        Ms      ESCAN00021708 Rx timeout flag is set, message/signal timeout function is called or default value is set
                        Ms      ESCAN00021271 No changes here
                        Ms      ESCAN00022375 IlStartCycle and IlStopCycle without Tx messages
                        Ms      ESCAN00023206 Split Oem Extensions
                        Ms      ESCAN00023270 No changes here
                        Ms      ESCAN00023300 Remove Signal Group Buffer Reset
                        Ms      ESCAN00023284 Alterable Memory for Tx Default Value
                        Ms      ESCAN00023821 Message Transmission Stops
                        Ms      ESCAN00023822 GM-Only: Message Transmission Stops
  05.01.00  2008-01-25  Ms      ESCAN00023109 PSA-Only: Remove Cyclic Messages Period Reset In An Event Transmission
  05.02.00  2008-04-21  Ms      ESCAN00026301 No changes here
            2008-07-17  Ms      ESCAN00025002 IlStartCycle and IlStopCycle return value without Tx messages
                        Ms      ESCAN00028780 Detect Repetition and Signal Activity
                        Ms      ESCAN00025178 Reset Timeout Flags On Release
                        Ms      ESCAN00013854 Support C_COMP_IAR_M16C for Compiler Version >= 3.00
  05.02.01  2008-10-17  Ms      ESCAN00029307 No changes here
                        Ms      ESCAN00030750 No changes here
  05.02.02  2009-08-28  Ml      ESCAN00037350 No changes here
  05.03.00  2009-11-19  Swa     ESCAN00039257 No changes here
                        Swa     ESCAN00039071 Added dummy statement in IlTxRepetitionsAreActive.
                        Swa     ESCAN00039274 No changes here
            2010-04-20  Swa     ESCAN00042420 No changes here
  05.04.00  2010-06-14  Swa     ESCAN00043305 Compile error in IlTxRepetitionsAreActive 
            2010-06-28  Ms      ESCAN00042424 Reload the Cyclic Timer after a successful Transmission Request
  05.05.00  2010-10-27  Ms      ESCAN00046426 Support C_API_3 to indicate reentrant function calls
  05.06.00  2011-06-28  Ms      ESCAN00051034 Reload the Cyclic Timer after a successful Transmission Request
  05.06.01  2011-07-14  Ms      ESCAN00052200 The Cyclic Timer is reloaded after a successful Transmission Request
  05.06.02  2012-02-06  Ms      ESCAN00056637 The Cyclic Timer is not reloaded after a successful Transmission Request
  05.07.00  2012-01-30  Hho     ESCAN00059505 Support Update Bits (Signal status information)
            2012-03-21  Hho     ESCAN00057706 Improve Misra compliance
  05.07.01  2012-06-26  Ms      ESCAN00059650 The version defines and constants are not 5.07.00
  05.07.02  2012-10-08  Hho     ESCAN00060945 No changes here
  05.08.00  2012-11-05  Hho     ESCAN00062550 improve IlCanCancelNotification runtime
  05.09.00  2013-07-23  Hho     ESCAN00055415 make feature "Reload the Cyclic Timer after a successful Transmission Request" configurable
  05.10.00  2014-07-18  Hho     ESCAN00077165 Dynamic Start Delay Time Support 
                        Hho     ESCAN00077121 Dynamic Minimum Delay Time Support
  05.10.01  2015-05-18  Hho     ESCAN00078311 No changes here
  05.11.00  2015-09-23  Ms      ESCAN00083676 C_COMP_TI_TMS320_DCAN is not supported
            2015-09-24  Ms      ESCAN00085457 Support C_COMP_TI_TMS320 (ECAN) in VGEN_GENY
  05.11.01  2015-12-18  Ms      ESCAN00087231 TMS320: CanDrv Indication and Confirmation Flag Interface does not work
  05.11.02  2016-08-16  Ms      ESCAN00091028 No changes here
  05.11.03  2016-09-23  Ms      ESCAN00092012 No changes here
**********************************************************************************************************************/

/*lint -function(exit,ApplIlFatalError)*/

#define V_IL_VECTOR_COMPONENT_SOURCE

/**********************************************************************************************************************
 * MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/
/* *INDENT-OFF* */
/* PRQA S 3453 EOF *//* MD_CBD_19.7 */
/* PRQA S 2006 EOF *//* MD_CBD_14.7 */
/* PRQA S 0489 EOF *//* MD_Il_0489   */
/* PRQA S 3458 EOF *//* MD_CBD_19.4 */
/* PRQA S 3460 EOF *//* MD_CBD_19.4 */
/* PRQA S 3412 EOF *//* MD_CBD_19.4 */
/* PRQA S 3109 EOF *//* MD_CBD_14.3 */
/* PRQA S 3201 EOF *//* MD_CBD_14.1 */
/* PRQA S 0635 EOF *//* MD_Il_0635  */
/* PRQA S 0779 EOF *//* MD_Il_0779  */
/* PRQA S 0781 EOF *//* MD_Il_0781  */
/* PRQA S 0777 EOF *//* MD_Il_0777  */
/* PRQA S 3673 EOF *//* MD_Il_3673  */
/* PRQA S 3410 EOF *//* MD_Il_3410  */
/* PRQA S 3689 EOF *//* MD_Il_3689  */
/* PRQA S 0857 EOF *//* MD_CBD_1.1 */
/* PRQA S 0342 EOF *//* MD_Il_0342 */
/* PRQA S 0770 EOF *//* MD_Il_0770 */
/* PRQA S 3360 EOF *//* MD_Il_3360 */
/* PRQA S 3355 EOF *//* MD_Il_3355_3356_3359  */
/* PRQA S 3356 EOF *//* MD_Il_3355_3356_3359  */
/* PRQA S 3359 EOF *//* MD_Il_3355_3356_3359  */
/* PRQA S 0310 EOF *//* MD_Il_0310 */
/* PRQA S 0312 EOF *//* MD_Il_0312 */
/* PRQA S 0290 EOF *//* MD_Il_0290 */
/* PRQA S 0291 EOF *//* MD_Il_0291 */
/* PRQA S 0715 EOF *//* MD_CBD_1.1 */
/* PRQA S 3108 EOF *//* MD_Il_3108 */
/* PRQA S 0883 EOF */ /**/
/* *INDENT-ON* */

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "il_inc.h"

/**********************************************************************************************************************
  VERSION CHECK
**********************************************************************************************************************/
#if( IL_VECTOR_VERSION != 0x0511 )
# error "Source and Header file are inconsistent!"
#endif
#if( IL_VECTOR_RELEASE_VERSION != 0x03 )
# error "Source and Header file are inconsistent!"
#endif

/**********************************************************************************************************************
  LOCAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL FUNCTION MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  ModifyChannelState
**********************************************************************************************************************/
/** \defgroup ModifyChannelState
    \brief    These macros shall be used to modify ilChannelState.
    \param    channel      Handle of the CAN channel.
    \return   none */
/**\{*/
/** Set the rx state machine to running */
#define EnableRx(channel)    (Il_ChannelState((channel)) = (vuint8)(((vuint8)(Il_ChannelState((channel)) & kIlIsNotRxWait)) | kIlIsRxRun))
/** Set the tx state machine to running */
#define EnableTx(channel)    (Il_ChannelState((channel)) = (vuint8)(((vuint8)(Il_ChannelState((channel)) & kIlIsNotTxWait)) | kIlIsTxRun))
/** Set the rx state machine to waiting */
#define WaitRx(channel)      (Il_ChannelState((channel)) = (vuint8)(((vuint8)(Il_ChannelState((channel)) & kIlIsNotRxRun)) | kIlIsRxWait))
/** Set the tx state machine to waiting */
#define WaitTx(channel)      (Il_ChannelState((channel)) = (vuint8)(((vuint8)(Il_ChannelState((channel)) & kIlIsNotTxRun)) | kIlIsTxWait))
/** Set the rx state machine to suspended */
#define SuspendRx(channel)   (Il_ChannelState((channel)) = (vuint8)(((vuint8)(Il_ChannelState((channel)) & kIlIsNotRxRun)) & kIlIsNotRxWait))
/** Set the rx state machine to suspended */
#define SuspendTx(channel)   (Il_ChannelState((channel)) = (vuint8)(((vuint8)(Il_ChannelState((channel)) & kIlIsNotTxRun)) & kIlIsNotTxWait))
/**\}*/

/**********************************************************************************************************************
  DecodeChannelState
**********************************************************************************************************************/
/** \ingroup DecodeChannelState */
/**\{*/
/** Tx is running */
#define TxEnabled(channel)      ((Il_ChannelState((channel)) & kIlIsTxRun) != 0)
/** Rx is waiting */
#define RxWaiting(channel)      ((Il_ChannelState((channel)) & kIlIsRxWait) != 0)
/** Tx is waiting */
#define TxWaiting(channel)      ((Il_ChannelState((channel)) & kIlIsTxWait) != 0)
/** Tx is suspended */
#define TxSuspended(channel)    ((Il_ChannelState((channel)) & (kIlIsTxRun | kIlIsTxWait)) == 0)
/** Tx is not suspended */
#define TxNotSuspended(channel) ((Il_ChannelState((channel)) & (kIlIsTxRun | kIlIsTxWait)) != 0)
/** Rx is not suspended */
#define RxNotSuspended(channel) ((Il_ChannelState((channel)) & (kIlIsRxRun | kIlIsRxWait)) != 0)
/**\}*/

#if defined( C_ENABLE_GENERIC_PRECOPY )
/**********************************************************************************************************************
  ModifyChannelReceive
**********************************************************************************************************************/
/** \defgroup ModifyChannelReceive
    \brief    These macros shall be used to modify ilChannelReceive.
    \param    channel      Handle of the CAN channel.
    \return   IlGetChannelReceived : none\n
              IlGetChannelReceived : ilChannelReceive\n
              IlClrChannelReceived : none */
/**\{*/
# if defined( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
#  define IlSetChannelReceived(channel)      (ilChannelReceive[(channel)] = 0x01)
#  define IlGetChannelReceived(channel)      (ilChannelReceive[(channel)])
#  define IlClrChannelReceived(channel)      (ilChannelReceive[(channel)] = 0x00)
# else
#  define IlSetChannelReceived(channel)      (ilChannelReceive =  0x01)
#  define IlGetChannelReceived(channel)      (ilChannelReceive)
#  define IlClrChannelReceived(channel)      (ilChannelReceive =  0   )
# endif
/**\}*/
#endif /* C_ENABLE_GENERIC_PRECOPY */

/**********************************************************************************************************************
  ClearStatusFlags
**********************************************************************************************************************/
/** \defgroup ClearStatusFlags
    \brief    These macros shall be used to clear status flags.
    \param    channel      Handle of the CAN channel.
    \return   none */
/**\{*/
#if defined IL_ENABLE_TX_TIMEOUT_FLAG
# if defined( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
#  define ResetTxTimeoutFlags(channel)        (VStdMemNearClr(&ilTxTimeoutFlags[IlTxTimeoutFlagsStartIndex[(channel)]],(vuint8)(IlTxTimeoutFlagsStartIndex[(channel)+1]-IlTxTimeoutFlagsStartIndex[(channel)])))
# else
#  define ResetTxTimeoutFlags(channel)        (VStdMemNearClr(ilTxTimeoutFlags,(vuint8)kIlNumberOfTxTimeoutFlags))
# endif
#else
# define ResetTxTimeoutFlags(channel)
#endif

#if defined IL_ENABLE_TX_CONFIRMATION_FLAG
# if defined( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
#  define ResetConfirmationFlags(channel)     (VStdMemNearClr(&ilTxConfirmationFlags[IlTxConfirmationFlagsStartIndex[(channel)]],(vuint8)(IlTxConfirmationFlagsStartIndex[(channel)+1]-IlTxConfirmationFlagsStartIndex[(channel)])))
# else
#  define ResetConfirmationFlags(channel)     (VStdMemNearClr(ilTxConfirmationFlags,(vuint8)kIlNumberOfTxConfirmationFlags))
# endif
#else
# define ResetConfirmationFlags(channel)
#endif

#if defined IL_ENABLE_RX_TIMEOUT_FLAG
# if defined( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
#  define ResetRxTimeoutFlags(channel)        (VStdMemNearClr(&ilRxTimeoutFlags[IlRxTimeoutFlagsStartIndex[(channel)]],(vuint8)(IlRxTimeoutFlagsStartIndex[(channel)+1]-IlRxTimeoutFlagsStartIndex[(channel)])))
# else
#  define ResetRxTimeoutFlags(channel)        (VStdMemNearClr(ilRxTimeoutFlags,(vuint8)kIlNumberOfRxTimeoutFlags))
# endif
#else
# define ResetRxTimeoutFlags(channel)
#endif


#if defined( IL_ENABLE_RX_TIMEOUT )
# if defined( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
#  define ResetRxTimerFlags(channel)          (VStdMemNearClr(&ilRxTimerFlags[IlRxTimerFlagsStartIndex[(channel)]],(vuint8)(IlRxTimerFlagsStartIndex[(channel)+1]-IlRxTimerFlagsStartIndex[(channel)])))
# else
#  define ResetRxTimerFlags(channel)          (VStdMemNearClr(ilRxTimerFlags,(vuint8)(kIlNumberOfTimerFlagBytes)))
# endif
#else
# define ResetRxTimerFlags(channel)
#endif


#if defined IL_ENABLE_RX_INDICATION_FLAG
# if defined( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
#  define ResetIndicationFlags(channel)       (VStdMemNearClr(&ilRxIndicationFlags[IlRxIndicationFlagsStartIndex[(channel)]],(vuint8)(IlRxIndicationFlagsStartIndex[(channel)+1]-IlRxIndicationFlagsStartIndex[(channel)])))
# else
#  define ResetIndicationFlags(channel)       (VStdMemNearClr(ilRxIndicationFlags,(vuint8)kIlNumberOfRxIndicationFlags))
# endif
#else
# define ResetIndicationFlags(channel)
#endif

#if defined IL_ENABLE_RX_FIRSTVALUE_FLAG
# if defined( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
#  define ResetFirstvalueFlags(channel)       (VStdMemNearClr(&ilRxFirstvalueFlags[IlRxFirstvalueFlagsStartIndex[(channel)]],(vuint8)(IlRxFirstvalueFlagsStartIndex[(channel)+1]-IlRxFirstvalueFlagsStartIndex[(channel)])))
# else
#  define ResetFirstvalueFlags(channel)       (VStdMemNearClr(ilRxFirstvalueFlags,(vuint8)kIlNumberOfRxFirstvalueFlags))
# endif
#else
# define ResetFirstvalueFlags(channel)
#endif

#if defined IL_ENABLE_RX_DATACHANGED_FLAG
# if defined( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
#  define ResetDataChangedFlags(channel)      (VStdMemNearClr(&ilRxDataChangedFlags[IlRxDataChangedFlagsStartIndex[(channel)]],(vuint8)(IlRxDataChangedFlagsStartIndex[(channel)+1]-IlRxDataChangedFlagsStartIndex[(channel)])))
# else
#  define ResetDataChangedFlags(channel)      (VStdMemNearClr(ilRxDataChangedFlags,(vuint8)kIlNumberOfRxDataChangedFlags))
# endif
#else
# define ResetDataChangedFlags(channel)
#endif
/**\}*/

/**********************************************************************************************************************
  DataAbstraction
**********************************************************************************************************************/
/** \defgroup DataAbstraction
    \brief    These macros shall be used to access tx and message buffers. */
/**\{*/

/**********************************************************************************************************************
  IlGetRxDataPtr
**********************************************************************************************************************/
/** \brief    This method returns the pointer to the buffer of a rx message.
    \param    ilRxHnd  Handle of an IL rx message.
    \return   vuint8*  Pointer to the databuffer.
**********************************************************************************************************************/
#if defined( IL_ENABLE_RX_MODE_SIGNALS ) || defined( IL_ENABLE_SYS_MULTI_ECU_PHYS ) 
# define IlGetRxDataPtr(ilRxHnd)                   (IlRxDataPtr[(ilRxHnd)])
#else
# define IlGetRxDataPtr(ilRxHnd)                   (CanGetRxDataPtr((ilRxHnd)))
#endif

/**********************************************************************************************************************
  IlGetRxDataLen
**********************************************************************************************************************/
/** \brief    This method returns the data length of a rx message.
    \param    ilRxHnd  Handle of an IL rx message.
    \return   vuint8   Length of the rx message in bytes.
**********************************************************************************************************************/
#if defined( IL_ENABLE_RX_MODE_SIGNALS ) || defined( IL_ENABLE_SYS_MULTI_ECU_PHYS ) 
# define IlGetRxDataLen(ilRxHnd)                   (IlRxDataLen[(ilRxHnd)])
#else
# define IlGetRxDataLen(ilRxHnd)                   (CanGetRxDataLen((ilRxHnd)))
#endif

/**\}*/


/**********************************************************************************************************************
  IlGetStartRxTimeoutCounter
**********************************************************************************************************************/
/** \brief    This method returns the number of IlRxTask calls in a channel for the rx timeout time.
    \param    ilRxHnd  Handle of an IL rx message.
    \return   IltRxTimeoutCounter  Number of rx ticks until the rx timeout expires.
**********************************************************************************************************************/
#if defined ( VGEN_GENY ) && defined( IL_ENABLE_RX_DYNAMIC_TIMEOUT )
# define IlGetStartRxTimeoutCounter(ilRxHnd)     (ilRxDynamicTimeoutCounter[(ilRxHnd)])
#else
# if defined( IL_ENABLE_SYS_MULTI_ECU_PHYS )
#  define IlGetStartRxTimeoutCounter(ilRxHnd)    (IlRxTimeoutTbl[V_ACTIVE_IDENTITY_LOG][(ilRxHnd)])
# else
#  define IlGetStartRxTimeoutCounter(ilRxHnd)    (IlRxTimeoutTbl[(ilRxHnd)])
# endif
#endif

/**********************************************************************************************************************
  IlGetInitRxTimeoutCounter
**********************************************************************************************************************/
/** \brief    This method returns the number of IlRxTask calls in a channel for the initial rx timeout time.
    \param    ilRxHnd      Handle of an IL rx message.
    \return   IltRxTimeoutCounter  Number of rx ticks until the initial timeout expires.
**********************************************************************************************************************/
#if defined( IL_ENABLE_SYS_MULTI_ECU_PHYS )
# define IlGetInitRxTimeoutCounter(ilRxHnd)    (IlRxTimeoutTbl[V_ACTIVE_IDENTITY_LOG][(ilRxHnd)])
#else
# define IlGetInitRxTimeoutCounter(ilRxHnd)    (IlRxTimeoutTbl[(ilRxHnd)])
#endif

/**********************************************************************************************************************
  IlGetTxTimeout
**********************************************************************************************************************/
/** \brief    This method returns the number of IlTxTask calls in a channel for the tx timeout time.
    \param    channel      Handle of the CAN channel.
    \return   IltTxTimeoutCounter  Number of tx ticks until the tx timeout expires.
**********************************************************************************************************************/
#if defined ( VGEN_GENY )
# if defined( IL_ENABLE_TX ) && defined( IL_ENABLE_TX_TIMEOUT ) && defined ( IL_ENABLE_TX_VARYING_TIMEOUT )
#  define IlGetTxTimeout(channel)              (IlTxTimeout[channel])
# else
#  define IlGetTxTimeout(channel)              (kIlTxTimeout)
# endif
#else
# define IlGetTxTimeout(channel)               (kIlTxTimeout)
#endif /* VGEN_GENY */

/**********************************************************************************************************************
  IlGetTxCyclicCycles
**********************************************************************************************************************/
/** \brief    This method returns the number of IlTxTask calls for the cyclic transmission of a tx message.
    \param    ilTxHnd      Handle of an IL tx message.
    \return   IltTxCounter  Number of tx ticks until the next transmission request shall be performed.
**********************************************************************************************************************/
#if defined( IL_ENABLE_TX ) && defined( IL_ENABLE_TX_DYNAMIC_CYCLETIME )
# define  IlGetTxCyclicCycles(ilTxHnd)         (ilTxDynCyclicCycles[(ilTxHnd)])
#else
# define  IlGetTxCyclicCycles(ilTxHnd)         (IlTxCyclicCycles[(ilTxHnd)])
#endif

/**********************************************************************************************************************
  IlGetTxDelayCycles
**********************************************************************************************************************/
/** \brief    This method returns the number of IlTxTask calls for the minimum delay time of a tx message.
    \param    ilTxHnd      Handle of an IL tx message.
    \return   IltTxCounter  Number of tx ticks a transmit request shall be delayed. 
**********************************************************************************************************************/
#if defined( IL_ENABLE_TX ) && defined( IL_ENABLE_TX_DYNAMIC_DELAYTIME )
# define  IlGetTxDelayCycles(ilTxHnd)         (ilTxDynDelayCycles[(ilTxHnd)])
#else
# define  IlGetTxDelayCycles(ilTxHnd)         (IlTxUpdateCycles[(ilTxHnd)])
#endif

/**********************************************************************************************************************
  IlGetTxStartDelayCycles
**********************************************************************************************************************/
/** \brief    This method returns the number of IlTxTask calls for the start delay time of a tx message.
    \param    ilTxHnd      Handle of an IL tx message.
    \return   IltTxCounter  Number of tx ticks until the first transmission request shall be performed.
**********************************************************************************************************************/
#if defined( IL_ENABLE_TX ) && defined( IL_ENABLE_TX_DYNAMIC_START_DELAYTIME )
# define  IlGetTxStartDelayCycles(ilTxHnd)         (ilTxDynStartDelayCycles[(ilTxHnd)])
#else
# define  IlGetTxStartDelayCycles(ilTxHnd)         (IlTxStartCycles[(ilTxHnd)])
#endif


/**********************************************************************************************************************
  IlAssert
**********************************************************************************************************************/
/** \brief    This macro has to be used, if ApplIlFatalError needs to be called.
    \param    ilCondition      A boolean expression.
    \param    ilErrorCode      The error number to be submitted.
    \return   none
**********************************************************************************************************************/
#if defined( IL_ENABLE_SYS_TESTDEBUG )
# define IlAssert(ilCondition, ilErrorCode)        if ((ilCondition)==0) {(ApplIlFatalError((ilErrorCode)));} /* PRQA S 3412  *//* MD_CBD_19.4 */
#else
# define IlAssert(ilCondition, ilErrorCode)
#endif


/**********************************************************************************************************************
  LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/


/**********************************************************************************************************************
  LOCAL DATA PROTOTYPES
**********************************************************************************************************************/
#if defined( IL_ENABLE_RX_MULTIPLE_NODES )
/** This variable contains the ECU-mask for Multiple ECUs. The variable is replaced in GENy by V_ACTIVE_IDENTITY_MSK. */
V_MEMRAM0 static V_MEMRAM1 vuintx V_MEMRAM2 ilECUMask;
#endif

#if defined ( IL_ENABLE_RX )
# if defined( C_ENABLE_GENERIC_PRECOPY )
#  if defined( IL_ENABLE_RX_POLLING ) 
/** This variable indicates data reception of a channel */
#   if defined( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 ilChannelReceive[kIlNumberOfChannels];
#   else
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 ilChannelReceive;
#   endif
#  endif /* IL_ENABLE_RX_POLLING || IL_ENABLE_RX_EXT_TIMEOUT */
# endif /* C_ENABLE_GENERIC_PRECOPY */
#endif /* IL_ENABLE_RX */

#if defined ( IL_ENABLE_TX )
/* variable definition for the send type CYCLIC-EVENT ***********************/
# if defined ( IL_ENABLE_TX_CYCLIC_EVENT ) || \
     defined ( IL_ENABLE_TX_SECURE_EVENT ) || \
     defined ( IL_ENABLE_TX_FAST_ON_START )
/** This variable contains the fast cycle time counter for every message. */
V_MEMRAM0 static V_MEMRAM1 IltTxCounter V_MEMRAM2 ilTxEventCounter[kIlNumberOfTxObjects];
# endif
/** This variable contains the standard cycle time and startdelaytime counter for every message. */
V_MEMRAM0 static V_MEMRAM1 IltTxCounter V_MEMRAM2 ilTxCyclicCounter[kIlNumberOfTxObjects];

# if defined( VGEN_GENY ) && defined( IL_ENABLE_TX_DYNAMIC_CYCLETIME )
/** This variable contains the cycle time for every message, if the dynamic cycle time API is used. */
V_MEMRAM0 static V_MEMRAM1 IltTxCounter V_MEMRAM2 ilTxDynCyclicCycles[kIlNumberOfTxObjects];
# endif

# if defined( VGEN_GENY ) && defined( IL_ENABLE_TX_DYNAMIC_DELAYTIME )
/** This variable contains the minimum delay time for every message, if the dynamic delay time API is used. */
V_MEMRAM0 static V_MEMRAM1 IltTxUpdateCounter V_MEMRAM2 ilTxDynDelayCycles[kIlNumberOfTxObjects];
# endif

# if defined( VGEN_GENY ) && defined( IL_ENABLE_TX_DYNAMIC_START_DELAYTIME )
/** This variable contains the start delay time for every message, if the dynamic start delay time API is used. */
V_MEMRAM0 static V_MEMRAM1 IltTxCounter V_MEMRAM2 ilTxDynStartDelayCycles[kIlNumberOfTxObjects];
# endif

#endif /* IL_ENABLE_TX */


/**********************************************************************************************************************
  GLOBAL DATA
**********************************************************************************************************************/
#if defined( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
V_MEMRAM0 V_MEMRAM1 vuint8 V_MEMRAM2 ilChannelState[kIlNumberOfChannels];
#else
V_MEMRAM0 V_MEMRAM1 vuint8 V_MEMRAM2 ilChannelState;
#endif

#if defined ( IL_ENABLE_RX )


# if defined( IL_ENABLE_RX_TIMEOUT )
V_MEMRAM0 V_MEMRAM1 IltRxTimeoutCounter V_MEMRAM2 ilRxTimeoutCounter[kIlNumberOfRxTimeoutCounters];
#  if defined( VGEN_GENY ) && defined( IL_ENABLE_RX_DYNAMIC_TIMEOUT )
V_MEMRAM0 V_MEMRAM1 IltRxTimeoutCounter V_MEMRAM2 ilRxDynamicTimeoutCounter[kIlNumberOfRxTimeoutCounters];
#  endif

V_MEMRAM0 V_MEMRAM1_NEAR vuint8 V_MEMRAM2_NEAR ilRxTimerFlags[kIlNumberOfTimerFlagBytes];

# endif /* IL_ENABLE_RX_TIMEOUT */

# if defined ( IL_ENABLE_RX_INDICATION_FLAG )
V_MEMRAM0 V_MEMRAM1_NEAR vuint8 V_MEMRAM2_NEAR ilRxIndicationFlags[kIlNumberOfRxIndicationFlags];

# endif

# if defined ( IL_ENABLE_RX_FIRSTVALUE_FLAG )
V_MEMRAM0 V_MEMRAM1_NEAR vuint8 V_MEMRAM2_NEAR ilRxFirstvalueFlags[kIlNumberOfRxFirstvalueFlags];

# endif

# if defined ( IL_ENABLE_RX_TIMEOUT_FLAG )
V_MEMRAM0 V_MEMRAM1_NEAR vuint8 V_MEMRAM2_NEAR ilRxTimeoutFlags[kIlNumberOfRxTimeoutFlags];

# endif

# if defined ( IL_ENABLE_RX_DATACHANGED_FLAG )
V_MEMRAM0 V_MEMRAM1_NEAR vuint8 V_MEMRAM2_NEAR ilRxDataChangedFlags[kIlNumberOfRxDataChangedFlags];
# endif

# if !defined (VGEN_GENY) && defined( IL_ENABLE_RX_MODE_SIGNALS )
V_MEMRAM0 V_MEMRAM1_NEAR _ilModeIndicationFlags V_MEMRAM2_NEAR ilModeIndicationFlags;
# endif

#endif /* IL_ENABLE_RX */

#if defined ( IL_ENABLE_TX )

V_MEMRAM0 V_MEMRAM1_NEAR volatile vuint8 V_MEMRAM2_NEAR ilTxState[kIlNumberOfTxObjects];

V_MEMRAM0 V_MEMRAM1 IltTxUpdateCounter V_MEMRAM2 ilTxUpdateCounter[kIlNumberOfTxObjects];

# if defined ( IL_ENABLE_TX_TIMEOUT )
V_MEMRAM0 V_MEMRAM1 IltTxTimeoutCounter V_MEMRAM2 ilTxTimeoutCounter[kIlNumberOfTxTimeoutCounters];
# endif
# if defined( IL_ENABLE_TX_SECURE_EVENT )
V_MEMRAM0 V_MEMRAM1 IltTxRepetitionCounter V_MEMRAM2 ilTxNSendCounter[kIlNumberOfTxObjects];
# endif


# if defined ( IL_ENABLE_TX_TIMEOUT_FLAG )

V_MEMRAM0 V_MEMRAM1_NEAR vuint8 V_MEMRAM2_NEAR ilTxTimeoutFlags[kIlNumberOfTxTimeoutFlags];
# endif

# if defined ( IL_ENABLE_TX_CONFIRMATION_FLAG )

V_MEMRAM0 V_MEMRAM1_NEAR vuint8 V_MEMRAM2_NEAR ilTxConfirmationFlags[kIlNumberOfTxConfirmationFlags];
# endif
#endif /* IL_ENABLE_TX */


V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kIlMainVersion = (vuint8) (IL_VECTOR_VERSION >> 8);
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kIlSubVersion = (vuint8) (IL_VECTOR_VERSION & 0x00FFu);
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kIlReleaseVersion = (vuint8) (IL_VECTOR_RELEASE_VERSION);


/**********************************************************************************************************************
  LOCAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
#if defined( IL_ENABLE_TX )
/**********************************************************************************************************************
  IlSendMessage
**********************************************************************************************************************/
/** \brief    This method performs the transmission request to the CAN Driver.
    \param    ilTxHnd  Handle of the tx message.
    \return   none
    \context  The function is called by IlTxTimerTask or IlSendDirect.
**********************************************************************************************************************/
static void IlSendMessage(IlTransmitHandle ilTxHnd);
#endif

#if defined( IL_ENABLE_RX_STOP_DEFAULTVALUE ) || defined( IL_ENABLE_RX_START_DEFAULTVALUE )
/**********************************************************************************************************************
  SetRxDefaultWithMask
**********************************************************************************************************************/
/** \brief    This method copies default values to the rx message buffer.
    \param    ilRxHnd  Handle of the rx message.
    \param    msk      pointer to a mask array of the rx message. At every position, where the mask bit is set,
                       the default value is set.
    \return   none
    \context  The function is called by IlRxStart or IlRxStop.
**********************************************************************************************************************/
static void SetRxDefaultWithMask(IlReceiveHandle ilRxHnd, V_MEMROM1 vuint8 V_MEMROM2 V_MEMROM3 * msk);
#endif

#if defined( IL_ENABLE_TX_STOP_DEFAULTVALUE ) || defined( IL_ENABLE_TX_START_DEFAULTVALUE )
/**********************************************************************************************************************
  SetTxDefaultWithMask
**********************************************************************************************************************/
/** \brief    This method copies default values to the tx message buffer.
    \param    ilTxHnd  Handle of the tx message.
    \param    msk      pointer to a mask array of the tx message. At every position, where the mask bit is set,
                       the default value is set.
    \return   none
    \context  The function is called by IlTxStart or IlTxStop.
**********************************************************************************************************************/
static void SetTxDefaultWithMask(IlTransmitHandle ilTxHnd, IL_MEMROM1 vuint8 IL_MEMROM2 IL_MEMROM3 * msk);
#endif


/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/
#if defined( IL_ENABLE_RX_STOP_DEFAULTVALUE ) || defined( IL_ENABLE_RX_START_DEFAULTVALUE )
/**********************************************************************************************************************
  SetRxDefaultWithMask
**********************************************************************************************************************/
static void SetRxDefaultWithMask(IlReceiveHandle ilRxHnd, V_MEMROM1 vuint8 V_MEMROM2 V_MEMROM3 * msk)
{
  vuint8 *dst = IlGetRxDataPtr(ilRxHnd);
  vuint8 len = IlGetRxDataLen(ilRxHnd);
  V_MEMROM1 vuint8 V_MEMROM2 V_MEMROM3 *src = IlRxDefaultInitValue[ilRxHnd];

  if (dst == V_NULL)
  {
    return;
  }

#  if defined IL_ENABLE_SYS_ARGCHECK

  if (len > 8)
  {
    return;
  }
#  endif

  while (len > 0)
  {
    len--;
    *dst = (*dst & IL_CAST2UINT8(~(*msk))) | ((*src) & (*msk));
    dst++;
    src++;
    msk++;
  }
}                               /* End of SetRxDefaultWithMask() */
#endif

#if defined( IL_ENABLE_TX_STOP_DEFAULTVALUE ) || defined( IL_ENABLE_TX_START_DEFAULTVALUE )
/**********************************************************************************************************************
  SetTxDefaultWithMask
**********************************************************************************************************************/
static void SetTxDefaultWithMask(IlTransmitHandle ilTxHnd, IL_MEMROM1 vuint8 IL_MEMROM2 IL_MEMROM3 * msk)
{
  vuint8 *dst = IlGetTxDataPtr(ilTxHnd);
  vuint8 len = IlGetTxDlc(ilTxHnd);
  IL_MEMROM1 vuint8 IL_MEMROM2 IL_MEMROM3 *src = IlTxDefaultInitValue[ilTxHnd];

  if (dst == V_NULL)
  {
    return;
  }
#  if defined IL_ENABLE_SYS_ARGCHECK

  if (len > 8)
  {
    return;
  }
#  endif

  while (len > 0)
  {
    len--;
    *dst = (*dst & IL_CAST2UINT8(~(*msk))) | ((*src) & (*msk));
    dst++;
    src++;
    msk++;
  }
}                               /* End of SetTxDefaultWithMask() */
#endif

#if defined ( IL_ENABLE_TX )
/**********************************************************************************************************************
  IlSendMessage
**********************************************************************************************************************/
static void IlSendMessage(IlTransmitHandle ilTxHnd)
{

  CanInterruptDisable();
  ilTxState[ilTxHnd] &= kTxNotSendRequest;

# if defined ( IL_ENABLE_TX_MODE_SIGNALS )
  /* copy mode depended signals to message buffer */
  if (IlTxModeCopyFunctions[ilTxHnd] != V_NULL)
  {
    IlTxModeCopyFunctions[ilTxHnd] ();
  }
# endif

  /* Counter for Update time must be reloaded twice, ------------ */
  /* here and in confirmation fct     --------------------------- */
# if defined ( C_ENABLE_CAN_CANCEL_NOTIFICATION )
  ilTxUpdateCounter[ilTxHnd] = kIlStopUpdateCounterValue;
# else
  ilTxUpdateCounter[ilTxHnd] = IlGetTxDelayCycles(ilTxHnd);
# endif
  CanInterruptRestore();

  if (CanTransmit(IlGetIlTxIndirection(ilTxHnd)) != kCanTxOk)
  {
    CanInterruptDisable();
    {
      ilTxState[ilTxHnd] |= (kTxSendRequest);
    }
    ilTxUpdateCounter[ilTxHnd] = 0;
    CanInterruptRestore();
  }
# if defined( IL_ENABLE_TX_SECURE_EVENT )
  else
  {
#  if defined ( IL_ENABLE_RELOAD_CYCLE_TIMER_ON_TRANSMISSION_REQUEST )
    if ((ilTxState[ilTxHnd] & kTxSendCyclic) != 0)
    {
            /*-- Reload the cycle counter for the cyclic message ----------*/
      ilTxCyclicCounter[ilTxHnd] = IlGetTxCyclicCycles(ilTxHnd);
    }
#  endif
    CanInterruptDisable();
    /* clear send request flag  ----------------------------------- */
    if ((ilTxNSendCounter[ilTxHnd] != 0) && ((ilTxState[ilTxHnd] & kTxNSendRequest) != 0))
    {
      ilTxNSendCounter[ilTxHnd]--;
    }
    ilTxState[ilTxHnd] &= kTxNotNSendRequest;
    CanInterruptRestore();
  }
# else
#  if defined ( IL_ENABLE_RELOAD_CYCLE_TIMER_ON_TRANSMISSION_REQUEST )
  else
  {
    if ((ilTxState[ilTxHnd] & kTxSendCyclic) != 0)
    {
            /*-- Reload the cycle counter for the cyclic message ----------*/
      ilTxCyclicCounter[ilTxHnd] = IlGetTxCyclicCycles(ilTxHnd);
    }
  }
#  endif
# endif
}                               /* End of IlSendMessage() */
#endif /* IL_ENABLE_TX */


/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/
/**********************************************************************************************************************
  IlInitPowerOn
**********************************************************************************************************************/
void IlInitPowerOn(void)
{
#if defined ( C_MULTIPLE_RECEIVE_CHANNEL )
  CanChannelHandle channel;
  for (channel = 0; channel < kIlNumberOfChannels; channel++)
#endif
  {
    IlInit(IL_CHANNEL_ILPARA_ONLY);
  }
}                               /* End of IlInitPowerOn() */

/**********************************************************************************************************************
  IlInit
**********************************************************************************************************************/
void IlInit(IL_CHANNEL_ILTYPE_ONLY)
{

#if defined ( IL_ENABLE_RX )
  IlReceiveHandle ilRxHnd;
#endif
#if defined ( IL_ENABLE_TX )
  IlTransmitHandle ilTxHnd;
#endif

  /* Reset internal state of IL    */
  Il_ChannelState(IL_CHANNEL_ILPARA_MACRO) = kIlIsSuspend;


#if defined( IL_ENABLE_RX_MULTIPLE_NODES )
  /* Setup the ECU mask for multiple ECUs */
  ilECUMask = (vuintx) (0x01 << V_ACTIVE_IDENTITY_LOG);
#endif


#if defined ( IL_ENABLE_RX )

  /***********************************************************
   **  Initialize receive data
   ***********************************************************/


   /*--- Loop for every receive object ---------------------------------------*/
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
  for (ilRxHnd = IlRxMsgStartIndex[channel]; ilRxHnd < IlRxMsgStartIndex[(channel + 1)]; ilRxHnd++)
# else
  for (ilRxHnd = 0; ilRxHnd < kIlNumberOfRxObjects; ilRxHnd++)
# endif
  {
    IlAssert(ilRxHnd < kIlNumberOfRxObjects, ILERR_ILLRXMSGHANDLE);

    if ((IlGetRxDataPtr(ilRxHnd)) != V_NULL)
    {
#  if defined IL_ENABLE_RX_DEFAULTVALUE
      if ((IlRxDefaultInitValue[ilRxHnd]) != V_NULL)
      {
        /*-- Set receive buffer to default values ---------------------------*/
        VStdMemCpyRomToRam(IlGetRxDataPtr(ilRxHnd), IlRxDefaultInitValue[ilRxHnd], IlGetRxDataLen(ilRxHnd));
      }
      else
#  endif /* IL_ENABLE_RX_DEFAULTVALUE */
      {
        /*-- No default value for this buffer. Set to '0' -------------------*/
        VStdMemClr(IlGetRxDataPtr(ilRxHnd), IlGetRxDataLen(ilRxHnd));
      }
    }
  }

   /*--- initialize dynamic Rx timeout objects ---------------------------------------*/
# if defined ( VGEN_GENY ) && defined( IL_ENABLE_RX_TIMEOUT ) && defined( IL_ENABLE_RX_DYNAMIC_TIMEOUT )
#  if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
  for (ilRxHnd = IlRxTimeoutCntStartIndex[channel]; ilRxHnd < IlRxTimeoutCntStartIndex[(channel + 1)]; ilRxHnd++)
#  else
  for (ilRxHnd = 0; ilRxHnd < kIlNumberOfRxTimeoutCounters; ilRxHnd++)
#  endif
  {
    IlAssert(ilRxHnd < kIlNumberOfRxTimeoutCounters, ILERR_ILLRXTIMEOUTINDEX);
    ilRxDynamicTimeoutCounter[ilRxHnd] = IlGetInitRxTimeoutCounter(ilRxHnd);
  }
# endif /* VGEN_GENY && IL_ENABLE_RX_TIMEOUT && IL_ENABLE_RX_DYNAMIC_TIMEOUT */

   /*---- Reset all flags for receive indication -----------------------------*/
  IlResetRxTimeoutFlags(IL_CHANNEL_ILPARA_ONLY);

  ResetRxTimerFlags(IL_CHANNEL_ILPARA_MACRO);
  ResetIndicationFlags(IL_CHANNEL_ILPARA_MACRO);
  ResetFirstvalueFlags(IL_CHANNEL_ILPARA_MACRO);
  ResetDataChangedFlags(IL_CHANNEL_ILPARA_MACRO);


#endif /* IL_ENABLE_RX */


#if defined ( IL_ENABLE_TX )
  /***********************************************************
   **  Initialize transmit data
   ***********************************************************/


  /*----- do the loop for every Tx object  -------------------------------*/
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
  for (ilTxHnd = IlTxMsgStartIndex[channel]; ilTxHnd < IlTxMsgStartIndex[(channel + 1)]; ilTxHnd++)
# else
  for (ilTxHnd = 0; ilTxHnd < kIlNumberOfTxObjects; ilTxHnd++)
# endif
  {
    IlAssert(ilTxHnd < kIlNumberOfTxObjects, ILERR_ILLTXMSGHANDLE);

# if defined( IL_ENABLE_SYS_MULTI_ECU_PHYS )
    if ((IlTxIdentityAssignment[ilTxHnd] & V_ACTIVE_IDENTITY_MSK) == (tVIdentityMsk) 0)
    {
      continue;
    }
# endif

    /************************************************************************/
    /**** Section: Clear Send-Type independent data *************************/
    /************************************************************************/
    if ((IlGetTxDataPtr(ilTxHnd)) != V_NULL)
    {
#  if defined IL_ENABLE_TX_DEFAULTVALUE
      if (IlTxDefaultInitValue[ilTxHnd] != V_NULL)
      {
        /*-- Set receive buffer to default values ---------------------------*/
        VStdMemCpyRomToRam(IlGetTxDataPtr(ilTxHnd), IlTxDefaultInitValue[ilTxHnd], IlGetTxDlc(ilTxHnd));
      }
      else
#  endif /* IL_ENABLE_TX_DEFAULTVALUE */
      {
        /*-- No default value for this buffer. Set to '0' -------------------*/
        /*** Clear message-transmit data-buffer *********************************/
        VStdMemClr(IlGetTxDataPtr(ilTxHnd), IlGetTxDlc(ilTxHnd));
      }
    }

    /*- Clear Tx-status variable. Message is inactive, no sendtype defined -*/
    ilTxState[ilTxHnd] = 0;

    /*--- Clear counter for update time ------------------------------------*/
    ilTxUpdateCounter[ilTxHnd] = 0; /*    */


    /************************************************************************/
    /**** Section: Clear data buffer for CYCLIC messages ********************/
    /************************************************************************/

    /* initialise the Dynamic cycle time counters with the initial defined rom values */
# if defined( VGEN_GENY ) && defined( IL_ENABLE_TX_DYNAMIC_CYCLETIME )
    ilTxDynCyclicCycles[ilTxHnd] = IlTxCyclicCycles[ilTxHnd];
# endif

    /* initialise the Dynamic minimum delay time counters with the initial defined rom values */
# if defined( VGEN_GENY ) && defined( IL_ENABLE_TX_DYNAMIC_DELAYTIME )
    ilTxDynDelayCycles[ilTxHnd] = IlTxUpdateCycles[ilTxHnd];
# endif

    /* initialise the Dynamic start delay time counters with the initial defined rom values */
# if defined( VGEN_GENY ) && defined( IL_ENABLE_TX_DYNAMIC_START_DELAYTIME )
    ilTxDynStartDelayCycles[ilTxHnd] = IlTxStartCycles[ilTxHnd];
# endif


    /*-- Counter for the cycletime -----------------------------------------*/
    ilTxCyclicCounter[ilTxHnd] = 0;


# if defined ( IL_ENABLE_TX_CYCLIC_EVENT ) || \
     defined ( IL_ENABLE_TX_SECURE_EVENT ) || \
     defined ( IL_ENABLE_TX_FAST_ON_START )
    /************************************************************************/
    /**** Section: Clear data buffer for CYCLIC- and SECURE-EVENT messages **/
    /************************************************************************/
    ilTxEventCounter[ilTxHnd] = 0;  /* Clear counter for event timer    */
# endif

  }

  /*---- Reset all flags for transmit path ----------------------------------*/
  ResetTxTimeoutFlags(IL_CHANNEL_ILPARA_MACRO);
  ResetConfirmationFlags(IL_CHANNEL_ILPARA_MACRO);


#endif /* IL_ENABLE_TX */


#if defined(IL_ENABLE_SYS_INIT_FCT)
  ApplIlInit(IL_CHANNEL_ILPARA_ONLY);
#endif
#if defined( IL_ENABLE_SYS_SIGNAL_INIT_FCT )
  IlSignalInit(IL_CHANNEL_ILPARA_ONLY);
#endif
}                               /* End of IlInit() */

/**********************************************************************************************************************
  IlRxStart
**********************************************************************************************************************/
void IlRxStart(IL_CHANNEL_ILTYPE_ONLY)
{
#if defined ( IL_ENABLE_RX )

# if defined ( IL_ENABLE_RX_START_DEFAULTVALUE )
  IlReceiveHandle ilRxHnd;
# endif
# if defined ( IL_ENABLE_RX_TIMEOUT )
  IlRxTimeoutHandle ilRxToHnd;
# endif

  /*** Receive already enabled. Do nothing! **********************************/
  if (RxEnabled(IL_CHANNEL_ILPARA_MACRO))
  {
    return;
  }

# if defined ( IL_ENABLE_RX_START_DEFAULTVALUE )
  /*--- Loop for every receive object ---------------------------------------*/
#  if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
  for (ilRxHnd = IlRxMsgStartIndex[channel]; ilRxHnd < IlRxMsgStartIndex[(channel + 1)]; ilRxHnd++)
#  else
  for (ilRxHnd = 0; ilRxHnd < kIlNumberOfRxObjects; ilRxHnd++)
#  endif
  {
    IlAssert(ilRxHnd < kIlNumberOfRxObjects, ILERR_ILLRXMSGHANDLE);
    /*-- Set receive buffer to default for some signals, if selected -------*/
    if ((IlRxDefaultInitValue[ilRxHnd] != V_NULL) && (IlRxDefaultStartMask[ilRxHnd] != V_NULL))
    {
      SetRxDefaultWithMask(ilRxHnd, IlRxDefaultStartMask[ilRxHnd]);
    }
  }
# endif /* IL_ENABLE_RX_START_DEFAULTVALUE */

# if defined( IL_ENABLE_RX_TIMEOUT )
#  if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
  for (ilRxToHnd = IlRxTimeoutCntStartIndex[channel]; ilRxToHnd < IlRxTimeoutCntStartIndex[(channel + 1)]; ilRxToHnd++)
#  else
  for (ilRxToHnd = 0; ilRxToHnd < kIlNumberOfRxTimeoutCounters; ilRxToHnd++)
#  endif
  {
    IlAssert(ilRxToHnd < kIlNumberOfRxTimeoutCounters, ILERR_ILLRXTIMEOUTINDEX);

    /*--- Reset timeout counter to its initial state --------------------*/
#  if defined ( IL_ENABLE_RX_TIMEOUT_DELAY )
    /* Timeout observation starts with first receive of a message */
    ilRxTimeoutCounter[ilRxToHnd] = 0;
#  else
    ilRxTimeoutCounter[ilRxToHnd] = IlGetStartRxTimeoutCounter(ilRxToHnd);
#  endif
  }
# endif /* IL_ENABLE_RX_TIMEOUT */

  /*---- Reset indication flags of the CAN driver ---------------------------*/
# if defined( IL_ENABLE_RX ) && defined( IL_ENABLE_RX_POLLING )
  IlResetCanIndicationFlags(IL_CHANNEL_ILPARA_ONLY);
# endif
# if !defined( VGEN_GENY ) && defined( IL_ENABLE_RX_MODE_SIGNALS )
  IlResetModeIndicationFlags(IL_CHANNEL_ILPARA_ONLY);
# endif
  /*---- Reset all flags for reception path ---------------------------------*/
  IlResetRxTimeoutFlags(IL_CHANNEL_ILPARA_ONLY);

  ResetRxTimerFlags(IL_CHANNEL_ILPARA_MACRO);
  ResetIndicationFlags(IL_CHANNEL_ILPARA_MACRO);
  ResetFirstvalueFlags(IL_CHANNEL_ILPARA_MACRO);
  ResetDataChangedFlags(IL_CHANNEL_ILPARA_MACRO);


   /*---- call user defined function on start of reception path of IAL -------*/
# if defined IL_ENABLE_SYS_RX_START_FCT
  ApplIlRxStart(IL_CHANNEL_ILPARA_ONLY);
# endif
# if defined( IL_ENABLE_RX_SIGNAL_START_FCT )
  IlSignalRxStart(IL_CHANNEL_ILPARA_ONLY);
# endif

  EnableRx(IL_CHANNEL_ILPARA_MACRO);

#else /* IL_ENABLE_RX */
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1) && defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  channel = channel;            /* to avoid compiler warnings */
# endif
#endif /* IL_ENABLE_RX */
}                               /* End of IlRxStart() */

/**********************************************************************************************************************
  IlTxStart
**********************************************************************************************************************/
void IlTxStart(IL_CHANNEL_ILTYPE_ONLY)
{
#if defined ( IL_ENABLE_TX )
  IlTransmitHandle ilTxHnd;

  /*** Transmit already enabled. Do nothing! *********************************/
  if (TxEnabled(IL_CHANNEL_ILPARA_MACRO))
  {
    return;
  }

  /* load startup times into the counter */
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
  for (ilTxHnd = IlTxMsgStartIndex[channel]; ilTxHnd < IlTxMsgStartIndex[(channel + 1)]; ilTxHnd++)
# else
  for (ilTxHnd = 0; ilTxHnd < kIlNumberOfTxObjects; ilTxHnd++)
# endif
  {
    IlAssert(ilTxHnd < kIlNumberOfTxObjects, ILERR_ILLTXMSGHANDLE);

# if defined IL_ENABLE_TX_START_DEFAULTVALUE
    /*-- Set transmit buffer to default for some signals, if selected -------*/
    if ((IlTxDefaultInitValue[ilTxHnd] != V_NULL) && (IlTxDefaultStartMask[ilTxHnd] != V_NULL)
#  if defined( IL_ENABLE_SYS_MULTI_ECU_PHYS )
        && ((IlTxIdentityAssignment[ilTxHnd] & V_ACTIVE_IDENTITY_MSK) != (tVIdentityMsk) 0)
#  endif
      )
    {
      SetTxDefaultWithMask(ilTxHnd, IlTxDefaultStartMask[ilTxHnd]);
    }
# endif

    /* copy default status from ROM to RAM for later change ---------------- */
    ilTxState[ilTxHnd] = IlTxType[ilTxHnd];

    /*--- Clear counter for update time ------------------------------------*/
    ilTxUpdateCounter[ilTxHnd] = 0; /*    */

# if defined( IL_ENABLE_TX_SECURE_EVENT )
    ilTxNSendCounter[ilTxHnd] = 0;
# endif

# if  defined ( IL_ENABLE_TX_FAST_ON_START )
    if ((IlTxType[ilTxHnd] & kTxFastOnStart) != 0)
    {
      /*--- Set the Time for fast transmission after Start of the CYCLIC messages --------------------*/
      ilTxCyclicCounter[ilTxHnd] = IlTxFastOnStartDuration[ilTxHnd];    /* + 1 already done in the table */

      ilTxEventCounter[ilTxHnd] = IlGetTxStartDelayCycles(ilTxHnd);     /* set start delay time for event timer *//* + 1 already done in the table */
    }
    else
# endif
    {
      /*--- Set the StartDelayTime of the CYCLIC messages --------------------*/
      ilTxCyclicCounter[ilTxHnd] = IlGetTxStartDelayCycles(ilTxHnd);    /* + 1 already done in the table */

# if defined ( IL_ENABLE_TX_CYCLIC_EVENT ) || \
    defined ( IL_ENABLE_TX_SECURE_EVENT ) || \
    defined ( IL_ENABLE_TX_FAST_ON_START )
      ilTxEventCounter[ilTxHnd] = 0;        /* Clear counter for event timer    */
# endif
    }
  }

# if defined ( IL_ENABLE_TX_TIMEOUT )
#  if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
  for (ilTxHnd = IlTxTimeoutCntStartIndex[channel]; ilTxHnd < IlTxTimeoutCntStartIndex[(channel + 1)]; ilTxHnd++)
#  else
  for (ilTxHnd = 0; ilTxHnd < kIlNumberOfTxTimeoutCounters; ilTxHnd++)
#  endif
  {
    /*--- Stop timeout counter --------------------*/
    ilTxTimeoutCounter[ilTxHnd] = 0;
  }
# endif

  /*---- Reset all flags for transmission path ------------------------------*/
  ResetTxTimeoutFlags(IL_CHANNEL_ILPARA_MACRO);
  ResetConfirmationFlags(IL_CHANNEL_ILPARA_MACRO);

  /*---- Reset confirmation flags of the CAN driver ---------------------------*/
  IlResetCanConfirmationFlags(IL_CHANNEL_ILPARA_ONLY);
# if defined(IL_ENABLE_TX_CYCLIC_EVENT)
  InitIfActiveFlags(IL_CHANNEL_ILPARA_ONLY);
# endif


   /*---- call user defined function on start of transmission path of IAL ----*/
# if defined IL_ENABLE_SYS_TX_START_FCT
  ApplIlTxStart(IL_CHANNEL_ILPARA_ONLY);
# endif
# if defined( IL_ENABLE_TX_SIGNAL_START_FCT )
  IlSignalTxStart(IL_CHANNEL_ILPARA_ONLY);
# endif

  EnableTx(IL_CHANNEL_ILPARA_MACRO);

#else /* IL_ENABLE_TX */
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1) && defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  channel = channel;            /* to avoid compiler warnings */
# endif
#endif /* IL_ENABLE_TX */
}                               /* End of IlTxStart() */

/**********************************************************************************************************************
  IlRxStop
**********************************************************************************************************************/
void IlRxStop(IL_CHANNEL_ILTYPE_ONLY)
{
#if defined ( IL_ENABLE_RX )

# if defined IL_ENABLE_RX_STOP_DEFAULTVALUE
  IlReceiveHandle ilRxHnd;
# endif

  if (RxSuspended(IL_CHANNEL_ILPARA_MACRO)) /* Receive already disabled  */
  {
    return;
  }

  SuspendRx(IL_CHANNEL_ILPARA_MACRO);

# if defined IL_ENABLE_RX_STOP_DEFAULTVALUE
  /*--- Loop for every receive object ---------------------------------------*/
#  if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
  for (ilRxHnd = IlRxMsgStartIndex[channel]; ilRxHnd < IlRxMsgStartIndex[(channel + 1)]; ilRxHnd++)
#  else
  for (ilRxHnd = 0; ilRxHnd < kIlNumberOfRxObjects; ilRxHnd++)
#  endif
  {
    IlAssert(ilRxHnd < kIlNumberOfRxObjects, ILERR_ILLRXMSGHANDLE);

    /*-- Set receive buffer to default for some signals, if selected -------*/
    if ((IlRxDefaultInitValue[ilRxHnd] != V_NULL) && (IlRxDefaultStopMask[ilRxHnd] != V_NULL))
    {
      SetRxDefaultWithMask(ilRxHnd, IlRxDefaultStopMask[ilRxHnd]);
    }
  }
# endif


  /*---- call user defined function on stop of reception path of IAL --------*/
# if defined IL_ENABLE_SYS_RX_STOP_FCT
  ApplIlRxStop(IL_CHANNEL_ILPARA_ONLY);
# endif
# if defined( IL_ENABLE_RX_SIGNAL_STOP_FCT )
  IlSignalRxStop(IL_CHANNEL_ILPARA_ONLY);
# endif

#else /* IL_ENABLE_RX */
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1) && defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  channel = channel;            /* to avoid compiler warnings */
# endif
#endif /* IL_ENABLE_RX */
}                               /* End of IlRxStop() */

/**********************************************************************************************************************
  IlTxStop
**********************************************************************************************************************/
void IlTxStop(IL_CHANNEL_ILTYPE_ONLY)
{
#if defined ( IL_ENABLE_TX )

# if defined IL_ENABLE_TX_STOP_DEFAULTVALUE
  IlTransmitHandle ilTxHnd;
# endif

  if (TxSuspended(IL_CHANNEL_ILPARA_MACRO))
  {
    return;
  }
  SuspendTx(IL_CHANNEL_ILPARA_MACRO);

# if defined IL_ENABLE_TX_STOP_DEFAULTVALUE
  /*--- Loop for every receive object ---------------------------------------*/
#  if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
  for (ilTxHnd = IlTxMsgStartIndex[channel]; ilTxHnd < IlTxMsgStartIndex[(channel + 1)]; ilTxHnd++)
#  else
  for (ilTxHnd = 0; ilTxHnd < kIlNumberOfTxObjects; ilTxHnd++)
#  endif
  {
    IlAssert(ilTxHnd < kIlNumberOfTxObjects, ILERR_ILLTXMSGHANDLE);

    /*-- Set receive buffer to default for some signals, if selected -------*/
    if ((IlTxDefaultInitValue[ilTxHnd] != V_NULL) && (IlTxDefaultStopMask[ilTxHnd] != V_NULL)
#  if defined( IL_ENABLE_SYS_MULTI_ECU_PHYS )
        && ((IlTxIdentityAssignment[ilTxHnd] & V_ACTIVE_IDENTITY_MSK) != (tVIdentityMsk) 0)
#  endif
      )
    {
      SetTxDefaultWithMask(ilTxHnd, IlTxDefaultStopMask[ilTxHnd]);
    }
  }
# endif


  /*---- call user defined function on stop of transmission path of IAL -----*/
# if defined IL_ENABLE_SYS_TX_STOP_FCT
  ApplIlTxStop(IL_CHANNEL_ILPARA_ONLY);
# endif
# if defined( IL_ENABLE_TX_SIGNAL_STOP_FCT )
  IlSignalTxStop(IL_CHANNEL_ILPARA_ONLY);
# endif

#else /* IL_ENABLE_TX */
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1) && defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  channel = channel;            /* to avoid compiler warnings */
# endif
#endif /* IL_ENABLE_TX */
}                               /* End of IlTxStop() */

/**********************************************************************************************************************
  IlRxWait
**********************************************************************************************************************/
void IlRxWait(IL_CHANNEL_ILTYPE_ONLY)
{
#if defined ( IL_ENABLE_RX )
  if (RxEnabled(IL_CHANNEL_ILPARA_MACRO))
  {
    WaitRx(IL_CHANNEL_ILPARA_MACRO);
  }
#else /* IL_ENABLE_RX */
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1) && defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  channel = channel;            /* to avoid compiler warnings */
# endif
#endif /* IL_ENABLE_RX */
}                               /* End of IlRxWait() */

/**********************************************************************************************************************
  IlTxWait
**********************************************************************************************************************/
void IlTxWait(IL_CHANNEL_ILTYPE_ONLY)
{
#if defined ( IL_ENABLE_TX )
  if (TxEnabled(IL_CHANNEL_ILPARA_MACRO))
  {
    WaitTx(IL_CHANNEL_ILPARA_MACRO);
  }
#else /* IL_ENABLE_TX */
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1) && defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  channel = channel;            /* to avoid compiler warnings */
# endif
#endif /* IL_ENABLE_TX */
}                               /* End of IlTxWait() */

/**********************************************************************************************************************
  IlRxRelease
**********************************************************************************************************************/
void IlRxRelease(IL_CHANNEL_ILTYPE_ONLY)
{
#if defined ( IL_ENABLE_RX )

# if defined( IL_ENABLE_RX_TIMEOUT )
  IlRxTimeoutHandle ilRxToHnd;
# endif

  if (RxWaiting(IL_CHANNEL_ILPARA_MACRO))
  {
# if defined( IL_ENABLE_RX_TIMEOUT )

    /* reset old message indications for Timeout supervision */
    ResetRxTimerFlags(IL_CHANNEL_ILPARA_MACRO);

#  if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
    for (ilRxToHnd = IlRxTimeoutCntStartIndex[channel]; ilRxToHnd < IlRxTimeoutCntStartIndex[(channel + 1)];
         ilRxToHnd++)
#  else
    for (ilRxToHnd = 0; ilRxToHnd < kIlNumberOfRxTimeoutCounters; ilRxToHnd++)
#  endif
    {
      IlAssert(ilRxToHnd < kIlNumberOfRxTimeoutCounters, ILERR_ILLRXTIMEOUTINDEX);

      /*--- Reset timeout counter to its initial state --------------------*/
#  if defined ( IL_ENABLE_RX_TIMEOUT_DELAY )
      /* Timeout observation starts with first receive of a message */
      ilRxTimeoutCounter[ilRxToHnd] = 0;
#  else
      ilRxTimeoutCounter[ilRxToHnd] = IlGetStartRxTimeoutCounter(ilRxToHnd);
#  endif
    }
# endif

# if defined ( IL_ENABLE_SYS_RX_RESET_TIMEOUT_FLAGS_ON_ILRXRELEASE )
    IlResetRxTimeoutFlags(IL_CHANNEL_ILPARA_ONLY);
# endif


    EnableRx(IL_CHANNEL_ILPARA_MACRO);
  }

#else /* IL_ENABLE_RX */
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1) && defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  channel = channel;            /* to avoid compiler warnings */
# endif
#endif /* IL_ENABLE_RX */
}                               /* End of IlRxRelease() */

/**********************************************************************************************************************
  IlTxRelease
**********************************************************************************************************************/
void IlTxRelease(IL_CHANNEL_ILTYPE_ONLY)
{
#if defined ( IL_ENABLE_TX )
  if (TxWaiting(IL_CHANNEL_ILPARA_MACRO))
  {
    EnableTx(IL_CHANNEL_ILPARA_MACRO);
  }

#else /* IL_ENABLE_TX */
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1) && defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  channel = channel;            /* to avoid compiler warnings */
# endif
#endif /* IL_ENABLE_TX */
}                               /* End of IlTxRelease() */

/**********************************************************************************************************************
  IlRxTask
**********************************************************************************************************************/
void IlRxTask(IL_CHANNEL_ILTYPE_ONLY)
{
  IlRxStateTask(IL_CHANNEL_ILPARA_ONLY);
  IlRxTimerTask(IL_CHANNEL_ILPARA_ONLY);
}                               /* End of IlRxTask() */

/**********************************************************************************************************************
  IlRxStateTask
**********************************************************************************************************************/
void IlRxStateTask(IL_CHANNEL_ILTYPE_ONLY)
{
#if defined ( IL_ENABLE_RX )

# if defined( IL_ENABLE_RX_POLLING ) 
  /* This check shall avoid, that Signal Indication "hangs" without precopy */
#  if defined( C_ENABLE_GENERIC_PRECOPY )
  /* Check if any message for this channel has been received */
  if (IlGetChannelReceived(IL_CHANNEL_ILPARA_MACRO) == 0)
  {
    return;
  }
  /* Reset the channel flag */
  IlClrChannelReceived(IL_CHANNEL_ILPARA_MACRO);
#  endif /* C_ENABLE_GENERIC_PRECOPY */

  if (RxNotSuspended(IL_CHANNEL_ILPARA_MACRO))
  {
#  if defined( IL_ENABLE_RX_POLLING )
    CanReceiveHandle canRxHnd;

      /*--- Loop for every receive object ---------------------------------------*/
#   if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
    for (canRxHnd = IlCanRxMsgStartIndex[channel]; canRxHnd < IlCanRxMsgStartIndex[(channel + 1)]; canRxHnd++)
#   else
    for (canRxHnd = 0; canRxHnd < (CanReceiveHandle) kIlCanNumberOfRxObjects; canRxHnd++)
#   endif
    {
      /* Efficiency might be improved, but this is the way how the CAN-driver does it */
      if ((IlGetRxIndicationFlags(IlGetRxIndicationOffset(canRxHnd)) & IlGetRxIndicationMask(canRxHnd)) !=
          0)
      {
        /*  clear the Indication flags */
        CanInterruptDisable();
        /* IL_CAST2UINT8 is not used here, because the Can Flags are word based for TMS320 */
        IlGetRxIndicationFlags(IlGetRxIndicationOffset(canRxHnd)) &=
          (vuint8) ~ IlGetRxIndicationMask(canRxHnd);
        CanInterruptRestore();

        if (IlCanRxIndicationFctPtr[canRxHnd] != V_NULL)
        {
          IlCanRxIndicationFctPtr[canRxHnd] ();
        }
      }
    }
#  endif

  }
# else /* IL_ENABLE_RX_POLLING || IL_ENABLE_RX_EXT_TIMEOUT */
#  if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1) && defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  channel = channel;            /* to avoid compiler warnings */
#  endif
# endif /* IL_ENABLE_RX_POLLING || IL_ENABLE_RX_EXT_TIMEOUT */

#else /* IL_ENABLE_RX */
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1) && defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  channel = channel;            /* to avoid compiler warnings */
# endif
#endif /* IL_ENABLE_RX */
}                               /* End of IlRxStateTask() */

/**********************************************************************************************************************
  IlRxTimerTask
**********************************************************************************************************************/
void IlRxTimerTask(IL_CHANNEL_ILTYPE_ONLY)
{
#if defined ( IL_ENABLE_RX )

# if defined( IL_ENABLE_RX_TIMEOUT )
#  if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
  IlRxTimeoutHandle ilRxToHnd = IlRxTimeoutCntStartIndex[channel];
#  else
  IlRxTimeoutHandle ilRxToHnd = 0;
#  endif
  vuint8 ilRxPackedIndex;
  vuint8 ilRxPackedMask = 0x01;
# endif

  if (!RxEnabled(IL_CHANNEL_ILPARA_MACRO))
  {
    return;
  }

# if defined( IL_ENABLE_RX_TIMEOUT )

#  if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
  for (ilRxPackedIndex = IlRxTimerFlagsStartIndex[channel]; ilRxPackedIndex < IlRxTimerFlagsStartIndex[channel + 1];
       ilRxPackedIndex++)
#  else
  for (ilRxPackedIndex = 0; ilRxPackedIndex < kIlNumberOfTimerFlagBytes; ilRxPackedIndex++)
#  endif
  {
    vuint8 ilBitMask = 0xFF;
    vuint8 ilFlagMask;

    CanInterruptDisable();
    ilFlagMask = ilRxTimerFlags[ilRxPackedIndex];
    ilRxTimerFlags[ilRxPackedIndex] = 0;
    CanInterruptRestore();

    while (ilBitMask != 0x00)
    {
      ilBitMask &= IL_CAST2UINT8(~(ilRxPackedMask & 0xFFu));
      if ((ilFlagMask & ilRxPackedMask) != 0)
      {
        ilRxTimeoutCounter[ilRxToHnd] = IlGetStartRxTimeoutCounter(ilRxToHnd);
      }
      else
      {
        {
#  if defined( IL_ENABLE_RX_DYNAMIC_TIMEOUT )
          if (ilRxTimeoutCounter[ilRxToHnd] != kIlNoRxTimeoutSupervision)
          {
#  endif
            if (ilRxTimeoutCounter[ilRxToHnd] != 0)
            {
              ilRxTimeoutCounter[ilRxToHnd]--;
              if (ilRxTimeoutCounter[ilRxToHnd] == 0)
              {
                (*IlRxTimeoutFctPtr[ilRxToHnd]) ();
              }
            }
#  if defined( IL_ENABLE_RX_DYNAMIC_TIMEOUT )
          }
#  endif
        }
      }
      if (ilRxPackedMask == 0x80)
      {
        ilRxPackedMask = 0x01;
      }
      else
      {
        ilRxPackedMask = IL_CAST2UINT8(ilRxPackedMask << 1);
      }
      ilRxToHnd++;

#  if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
      if (ilRxToHnd >= IlRxTimeoutCntStartIndex[(channel + 1)])
#  else
      if (ilRxToHnd >= kIlNumberOfRxTimeoutCounters)
#  endif
      {
        ilBitMask = 0x00;
      }
    }
  }
# endif/* IL_ENABLE_RX_TIMEOUT */


#else /* IL_ENABLE_RX */
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1) && defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  channel = channel;            /* to avoid compiler warnings */
# endif

#endif /* IL_ENABLE_RX */
}                               /* End of IlRxTimerTask() */

/**********************************************************************************************************************
  IlInit
**********************************************************************************************************************/
void IlTxTask(IL_CHANNEL_ILTYPE_ONLY)
{
  IlTxStateTask(IL_CHANNEL_ILPARA_ONLY);
  IlTxTimerTask(IL_CHANNEL_ILPARA_ONLY);
}                               /* End of IlTxTask() */

/**********************************************************************************************************************
  IlTxStateTask
**********************************************************************************************************************/
void IlTxStateTask(IL_CHANNEL_ILTYPE_ONLY)
{
#if defined ( IL_ENABLE_TX )
  IlTransmitHandle ilTxHnd;
  CanTransmitHandle cth;

  /* Check if any message for this channel has been recived */
  if (TxNotSuspended(IL_CHANNEL_ILPARA_MACRO))
  {
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
    ilTxHnd = IlTxMsgStartIndex[channel + 1];
    if (IlTxMsgStartIndex[channel] == ilTxHnd)
    {
      return;
    }
# else
    ilTxHnd = kIlNumberOfTxObjects;
# endif
    /*--- Loop for every transmit object ---------------------------------------*/
    do
    {
      /* Initial Decrement */
      ilTxHnd--;

      /* Go from IL handle to CAN handle */
      cth = IlGetIlTxIndirection(ilTxHnd);

      if (cth != kCanTxHandleNotUsed)
      {
        /* Efficiency might be improved, but this is the way how the CAN-driver does it */
        if ((IlGetTxConfirmationFlags(IlGetTxConfirmationOffset(cth)) & IlGetTxConfirmationMask(cth)) != 0)
        {
          /*  Clear the Confirmation flags */
          CanInterruptDisable();
          /* IL_CAST2UINT8 is not used here, because the Can Flags are word based for TMS320 */
          IlGetTxConfirmationFlags(IlGetTxConfirmationOffset(cth)) &=
            (vuint8) ~ IlGetTxConfirmationMask(cth);
          /* Counter for Update time must be reloaded twice, here and in confirmation fct */
          ilTxUpdateCounter[ilTxHnd] = IlGetTxDelayCycles(ilTxHnd);
          CanInterruptRestore();

# if defined( IL_ENABLE_TX_POLLING )
          if (IlTxConfirmationFctPtr[ilTxHnd] != V_NULL)
          {
            IlTxConfirmationFctPtr[ilTxHnd] ();
          }
# endif
        }
      }
# if defined IL_ENABLE_SYS_TRANSMIT_IN_STATETASK

#  error "in case of multiple ECU ILSendMessage is only allowed to be called for Tx messages of the current ECU"

      /*********************************************************************/
      /*-- Send message if send request is set AND update time expired ----*/
      /*********************************************************************/
      if (((ilTxState[ilTxHnd] & kTxSendRequest) != 0) && (ilTxUpdateCounter[ilTxHnd] == 0))
      {
#  if defined ( IL_ENABLE_TX_TIMEOUT )
        if ((ilTxState[ilTxHnd] & kTxCheckTimeout) != 0)
        {
          /* start Timeout supervision for this message */
          IlAssert(IlTxTimeoutIndirection[ilTxHnd] < kIlNumberOfTxTimeoutCounters, ILERR_ILLTXTIMEOUTINDEX);
          CanInterruptDisable();
          if (ilTxTimeoutCounter[IlTxTimeoutIndirection[ilTxHnd]] == 0)
          {
            ilTxTimeoutCounter[IlTxTimeoutIndirection[ilTxHnd]] = IlGetTxTimeout(IL_CHANNEL_ILPARA_MACRO);
          }
          CanInterruptRestore();
        }
#  endif
        IlSendMessage(ilTxHnd);
      }
# endif
    }
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
    while (ilTxHnd != IlTxMsgStartIndex[channel]);
# else
    while (ilTxHnd != 0);
# endif
  }

#else /* IL_ENABLE_TX */
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1) && defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  channel = channel;            /* to avoid compiler warnings */
# endif
#endif /* IL_ENABLE_TX */
}                               /* End of IlTxStateTask() */

/**********************************************************************************************************************
  IlTxTimerTask
**********************************************************************************************************************/
void IlTxTimerTask(IL_CHANNEL_ILTYPE_ONLY)
{
#if defined ( IL_ENABLE_TX )
  IlTransmitHandle ilTxHnd;

  /*----- do Tx-task only if Tx is started ----------------------------------*/
  if (TxEnabled(IL_CHANNEL_ILPARA_MACRO))
  {
# if defined ( IL_ENABLE_TX_TIMEOUT )
    IlCheckTxTimeout(IL_CHANNEL_ILPARA_ONLY);
# endif

# if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
    ilTxHnd = IlTxMsgStartIndex[channel + 1];
    if (IlTxMsgStartIndex[channel] == ilTxHnd)
    {
      return;
    }
# else
    ilTxHnd = kIlNumberOfTxObjects;
# endif
    /*--- Loop for every transmit object ---------------------------------------*/
    do
    {
      /* Initial Decrement */
      ilTxHnd--;
      IlAssert((ilTxHnd < kIlNumberOfTxObjects), ILERR_ILLTXMSGHANDLE);

# if defined( IL_ENABLE_SYS_MULTI_ECU_PHYS )
      /* Suppress  message that is not assigned for this Multi-ECU. */
      if ((IlTxIdentityAssignment[ilTxHnd] & V_ACTIVE_IDENTITY_MSK) == (tVIdentityMsk) 0)
      {
        continue;
      }
# endif

      /*********************************************************************/
      /**** Global section. ************************************************/
      /*********************************************************************/

      CanInterruptDisable();
      /*-- decrement counter for update time ------------------------------*/
      if ((ilTxUpdateCounter[ilTxHnd] != kIlStopUpdateCounterValue) && (ilTxUpdateCounter[ilTxHnd] > 0))
      {
        ilTxUpdateCounter[ilTxHnd]--;
      }
      CanInterruptRestore();

      {
        {
          /*********************************************************************/
          /**** Section for the CYCLIC messages ********************************/
          /*********************************************************************/

          /*-- Check if Cyclic send is active for this message ----------------*/
          if ((ilTxState[ilTxHnd] & kTxSendCyclic) != 0)
          {
            if (ilTxCyclicCounter[ilTxHnd] != 0)    /* decrement timer counter      */
            {
              ilTxCyclicCounter[ilTxHnd]--; /*   only if not 0              */
            }

            /*-- Tx timer expired -> request to send message -----------------*/
            if (ilTxCyclicCounter[ilTxHnd] == 0)
            {
# if  defined ( IL_ENABLE_TX_FAST_ON_START )
#  if defined ( VGEN_GENY ) && defined( IL_ENABLE_TX_MODE_SIGNALS )
              if ((ilTxState[ilTxHnd] & kTxFastOnStart) != 0)
              {
                if (IlTxFastOnStartMuxDelay[ilTxHnd] != 0)
                {
                  /*---- only multiplexed ilTxHnd ----*/
                  ilTxCyclicCounter[ilTxHnd] = IlTxFastOnStartMuxDelay[ilTxHnd];
                  ilTxEventCounter[ilTxHnd] = IlTxFastOnStartMuxDelay[ilTxHnd];
                }
                else
                {
                  /*-- Reload the cycle counter for the cyclic message ----------*/
                  ilTxCyclicCounter[ilTxHnd] = IlGetTxCyclicCycles(ilTxHnd);
                }
#  endif

                CanInterruptDisable();
                ilTxState[ilTxHnd] &= kTxNotFastOnStart;
                CanInterruptRestore();

#  if defined ( VGEN_GENY ) && defined( IL_ENABLE_TX_MODE_SIGNALS )
              }
              else
#  endif
# endif/* IL_ENABLE_TX_FAST_ON_START */
              {
                 /*-- Reload the cycle counter for the cyclic message ----------*/
                ilTxCyclicCounter[ilTxHnd] = IlGetTxCyclicCycles(ilTxHnd);
              }

# if defined ( IL_ENABLE_TX_CYCLIC_EVENT )  || \
    defined ( IL_ENABLE_TX_FAST_ON_START )
              if ((ilTxState[ilTxHnd] & (kTxSendCyclicEvent | kTxFastOnStart)) == 0)
# endif
              {
# if defined ( IL_ENABLE_TX_SECURE_EVENT )
                if ((ilTxNSendCounter[ilTxHnd]) == 0)
# endif
                {
                  /* only if nothing is send fast */
                    /*-- Set the send request bit in tx-status field --------------*/
                  CanInterruptDisable();
                  ilTxState[ilTxHnd] |= kTxSendRequest;
                  CanInterruptRestore();
                }
              }
            }
          }

# if defined ( IL_ENABLE_TX_CYCLIC_EVENT ) || defined ( IL_ENABLE_TX_SECURE_EVENT ) || \
    defined ( IL_ENABLE_TX_FAST_ON_START )

            /*********************************************************************/
            /**** Section for the CYCLIC- and SECURE-EVENT messages **************/
            /*********************************************************************/

            /*-- Check if Cyclic event send is active for this message ----------*/
#  if defined( IL_ENABLE_TX_SECURE_EVENT )
          if (((ilTxState[ilTxHnd] & (kTxSendCyclicEvent | kTxFastOnStart)) != 0)
              || (ilTxNSendCounter[ilTxHnd] != 0))
#  else
          if ((ilTxState[ilTxHnd] & (kTxSendCyclicEvent | kTxFastOnStart)) != 0)
#  endif
          {
            if (ilTxEventCounter[ilTxHnd] != 0)     /* decrement timer counter */
            {
              ilTxEventCounter[ilTxHnd]--;  /*   only if not 0        */
            }

            /*-- Tx EventTimer expired -> request to send message ------------*/
            if (ilTxEventCounter[ilTxHnd] == 0)
            {
              CanInterruptDisable();
#  if defined( IL_ENABLE_TX_SECURE_EVENT )
              if (ilTxNSendCounter[ilTxHnd] != 0)
              {
                ilTxState[ilTxHnd] |= (kTxSendRequest | kTxNSendRequest);
              }
              else
#  endif
              {
                ilTxState[ilTxHnd] |= kTxSendRequest;
              }
              CanInterruptRestore();

              ilTxEventCounter[ilTxHnd] = IlTxEventCycles[ilTxHnd];
            }
          }
# endif/* IL_ENABLE_TX_CYCLIC_EVENT || IL_ENABLE_TX_SECURE_EVENT || IL_ENABLE_TX_FAST_ON_START */
          /*********************************************************************/
          /*-- Send message if send request is set AND update time expired ----*/
          /*********************************************************************/
          if (((ilTxState[ilTxHnd] & kTxSendRequest) != 0) && (ilTxUpdateCounter[ilTxHnd] == 0))
          {
# if defined ( IL_ENABLE_TX_TIMEOUT )
            if ((ilTxState[ilTxHnd] & kTxCheckTimeout) != 0)
            {
              /* start Timeout supervision for this message */
              IlAssert(IlTxTimeoutIndirection[ilTxHnd] < kIlNumberOfTxTimeoutCounters,
                           ILERR_ILLTXTIMEOUTINDEX);
              CanInterruptDisable();
              if (ilTxTimeoutCounter[IlTxTimeoutIndirection[ilTxHnd]] == 0)
              {
                ilTxTimeoutCounter[IlTxTimeoutIndirection[ilTxHnd]] =
                  IlGetTxTimeout(IL_CHANNEL_ILPARA_MACRO);
              }
              CanInterruptRestore();
            }
# endif
            IlSendMessage(ilTxHnd);
          }
        }
      }
    }
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
    while (ilTxHnd != IlTxMsgStartIndex[channel]);
# else
    while (ilTxHnd != 0);
# endif
  }                             /* if TxEnabled */
#else /* IL_ENABLE_TX */
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1) && defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  channel = channel;            /* to avoid compiler warnings */
# endif
#endif /* IL_ENABLE_TX */
}                               /* End of IlTxTimerTask() */

#if defined ( C_ENABLE_CAN_CANCEL_NOTIFICATION )
/**********************************************************************************************************************
  IlCanCancelNotification
**********************************************************************************************************************/
/** \brief    This method is called if a transmit message is deleted (CanCancelTransmit, CanOffline or CanInit)
              and the update counter will be reset.
    \param    txHandle     Handle of the Can Driver tx message.
    \return   none
    \context  The function can be called on task and interupt level.
    \note     The function is called by the Can Driver. Either IlCanCancelNotification is exclusively called or
              the Can Driver sets a confirmation flag or calls a confirmation function.
**********************************************************************************************************************/
void IlCanCancelNotification(CanTransmitHandle txHandle)
{
# if defined ( IL_ENABLE_TX )
  IlTransmitHandle ilTxHnd;

  for (ilTxHnd = IlCanHndToIlHnd[txHandle].start; ilTxHnd < IlCanHndToIlHnd[txHandle].stop; ilTxHnd++)
  {
    ilTxUpdateCounter[ilTxHnd] = 0;
  }
# else /* IL_ENABLE_TX */
#  if defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  txHandle = txHandle;          /* to avoid compiler warnings */
#  endif
# endif /* IL_ENABLE_TX */
}                               /* End of IlCanCancelNotification() */
#endif /* ( C_ENABLE_CAN_CANCEL_NOTIFICATION ) */

#if defined ( C_ENABLE_GENERIC_PRECOPY )
/**********************************************************************************************************************
  IlCanGenericPrecopy
**********************************************************************************************************************/
/** \brief    This method is called immedialtely after the DLC-CHeck and notifies about the reception of a Can message.
    \param    rcvObject    Handle of the Can Driver tx message.
    \param    dptr         Pointer to the received data in the CAN Controller receive register
    \param    rxStruct     Pointer to the receive structure.
    \return   kCanCopyData, if the data processing shall be continued, else kCanNoCopyData.
    \context  The method can be called on task and interupt level.
    \note     The method is called by the Can Driver.
**********************************************************************************************************************/
# if defined( C_SINGLE_RECEIVE_BUFFER )
vuint8 IlCanGenericPrecopy(CanReceiveHandle rcvObject)
#  define canRxHnd  (rcvObject)
# endif
# if defined( C_MULTIPLE_RECEIVE_BUFFER )
     vuint8 IlCanGenericPrecopy(CanReceiveHandle rcvObject, pChipDataPtr dptr)
#  define canRxHnd  (rcvObject)
# endif
# if defined(C_SINGLE_RECEIVE_CHANNEL) || defined(C_MULTIPLE_RECEIVE_CHANNEL)
     vuint8 IlCanGenericPrecopy(CanRxInfoStructPtr rxStruct)
#  define canRxHnd  (rxStruct->Handle)
# endif
{

# if defined ( IL_ENABLE_RX )

#  if defined ( C_MULTIPLE_RECEIVE_BUFFER ) && defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  dptr = dptr;                  /* to avoid compiler warnings */
#  endif

  /* Not an IL message */
  if (canRxHnd >= kIlCanNumberOfRxObjects)
  {
    return kCanCopyData;
  }
  if (RxSuspended(IL_CHANNEL_ILPRECOPY_MACRO))
  {                             /* Receive is disabled  */
    return kCanNoCopyData;
  }
#  if defined( IL_ENABLE_RX_MULTI_ECU_PHYS )
  if ((IlCanRxIdentityAssignment[canRxHnd] & V_ACTIVE_IDENTITY_MSK) == (tVIdentityMsk) 0)
  {
    return kCanNoCopyData;
  }
#  endif

#  if defined( IL_ENABLE_RX_POLLING ) 
  IlSetChannelReceived(IL_CHANNEL_ILPRECOPY_MACRO);
#  endif


  return kCanCopyData;
# else/* IL_ENABLE_RX */
#  if defined ( V_ENABLE_USE_DUMMY_STATEMENT )
#   if defined( C_SINGLE_RECEIVE_BUFFER )
  rcvObject = rcvObject;
#   endif
#   if defined( C_MULTIPLE_RECEIVE_BUFFER )
  rcvObject = rcvObject;
  dptr = dptr;
#   endif
#   if defined(C_SINGLE_RECEIVE_CHANNEL) || defined(C_MULTIPLE_RECEIVE_CHANNEL)
  rxStruct = rxStruct;
#   endif
#  endif/* V_ENABLE_USE_DUMMY_STATEMENT */
  return kCanCopyData;
# endif/* IL_ENABLE_RX */
}                               /* End of IlCanGenericPrecopy() */
#endif /* !IL_TYPE_AUTOSAR && C_ENABLE_GENERIC_PRECOPY */

/**********************************************************************************************************************
  IlGetStatus
**********************************************************************************************************************/
Il_Status IlGetStatus(IL_CHANNEL_ILTYPE_ONLY)
{
  return (Il_Status) Il_ChannelState(IL_CHANNEL_ILPARA_MACRO);
}                               /* End of IlGetStatus() */

#if defined( IL_ENABLE_TX_SEND_ON_INIT )
/**********************************************************************************************************************
  IlSendOnInitMsg
**********************************************************************************************************************/
void IlSendOnInitMsg(IL_CHANNEL_ILTYPE_ONLY)
{
# if defined ( IL_ENABLE_TX )
  IlTransmitHandle ilTxHnd;

#  if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
  IlAssert(channel < kIlNumberOfChannels, ILERR_ILLCHANNEL);

#   if defined IL_ENABLE_SYS_ARGCHECK
  if (channel >= kIlNumberOfChannels)
  {
    return;
  }
#   endif
  CanInterruptDisable();
  for (ilTxHnd = IlTxMsgStartIndex[channel]; ilTxHnd < IlTxMsgStartIndex[(channel + 1)]; ilTxHnd++)
#  else
  CanInterruptDisable();
  for (ilTxHnd = 0; ilTxHnd < kIlNumberOfTxObjects; ilTxHnd++)
#  endif
  {
    /*--- Queue message On-Init only if it is configured to be allowed -----*/
    if ((ilTxState[ilTxHnd] & kTxQueueInit) != 0)
    {
      ilTxState[ilTxHnd] |= kTxSendRequest;
    }
  }
  CanInterruptRestore();

# else/* IL_ENABLE_TX */
#  if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1) && defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  channel = channel;            /* to avoid compiler warnings */
#  endif
# endif/* IL_ENABLE_TX */
}                               /* End of IlSendOnInitMsg() */
#endif /* IL_ENABLE_TX_SEND_ON_INIT */

#if defined IL_ENABLE_TX_STARTSTOP_CYCLIC
/**********************************************************************************************************************
  IlStartCycle
**********************************************************************************************************************/
Il_Status IlStartCycle(IlTransmitHandle ilTxHnd) C_API_3
{
# if defined ( IL_ENABLE_TX )
  /*----- Check for valid handle numbers ------------------------------------*/
  IlAssert(ilTxHnd < kIlNumberOfTxObjects, ILERR_ILLTXMSGHANDLE);

#  if defined IL_ENABLE_SYS_ARGCHECK
  if (ilTxHnd >= kIlNumberOfTxObjects)
  {
    return IL_ERROR;
  }
#  endif

  /*----- Check if SendState already active for this timebase ---------------*/
  if ((ilTxState[ilTxHnd] & kTxSendCyclic) != 0)
  {
    return IL_QUEUED;
  }

  CanInterruptDisable();
  /*--- Set the flag of the cyclic messages in the --------------------------*/
  ilTxState[ilTxHnd] |= kTxSendCyclic;

  /*--- Init cycle counter to the StartDelayTime (if actual time is greater) */
  if (ilTxCyclicCounter[ilTxHnd] > IlGetTxStartDelayCycles(ilTxHnd))    /* + 1 already done in the table */
  {
    ilTxCyclicCounter[ilTxHnd] = IlGetTxStartDelayCycles(ilTxHnd);      /* + 1 already done in the table */
  }
  CanInterruptRestore();

# else /* IL_ENABLE_TX */
#  if defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  ilTxHnd = ilTxHnd;
#  endif
# endif /* IL_ENABLE_TX */
  return IL_OK;
}                               /* End of IlStartCycle(() */

/**********************************************************************************************************************
  IlStopCycle
**********************************************************************************************************************/
Il_Status IlStopCycle(IlTransmitHandle ilTxHnd) C_API_3
{
# if defined ( IL_ENABLE_TX )
  /*----- Check for valid handle numbers ------------------------------------*/
  IlAssert(ilTxHnd < kIlNumberOfTxObjects, ILERR_ILLTXMSGHANDLE);

#  if defined IL_ENABLE_SYS_ARGCHECK
  if (ilTxHnd >= kIlNumberOfTxObjects)
  {
    return IL_ERROR;
  }
#  endif
  CanInterruptDisable();
  ilTxState[ilTxHnd] &= kTxNotSendCyclic;   /* Stop cyclic send        */
  CanInterruptRestore();

# else /* IL_ENABLE_TX */
#  if defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  ilTxHnd = ilTxHnd;
#  endif
# endif /* IL_ENABLE_TX */
  return IL_OK;
}                               /* End of IlStopCycle() */
#endif /* IL_ENABLE_TX_STARTSTOP_CYCLIC */


#if defined(IL_ENABLE_TX_CYCLIC_EVENT)
/**********************************************************************************************************************
  IlStartEvent
**********************************************************************************************************************/
Il_Status IlStartEvent(IlTransmitHandle ilTxHnd) C_API_3
{
  /*----- Check for valid handle numbers ------------------------------------*/
  IlAssert(ilTxHnd < kIlNumberOfTxObjects, ILERR_ILLTXMSGHANDLE);

# if defined IL_ENABLE_SYS_ARGCHECK
  if (ilTxHnd >= kIlNumberOfTxObjects)
  {
    return IL_ERROR;
  }
# endif

  /*--- Start immediately transmission of cyclic event messages -------------*/
  ilTxEventCounter[ilTxHnd] = 0;

  /*-- Set the status of the message for cyclic-event -----------------------*/
  ilTxState[ilTxHnd] |= kTxSendCyclicEvent;

  return (1);
}                               /* End of IlStartEvent() */

/**********************************************************************************************************************
  IlStopEvent
**********************************************************************************************************************/
Il_Status IlStopEvent(IlTransmitHandle ilTxHnd) C_API_3
{
  /*----- Check for valid handle numbers ------------------------------------*/
  IlAssert(ilTxHnd < kIlNumberOfTxObjects, ILERR_ILLTXMSGHANDLE);

# if defined IL_ENABLE_SYS_ARGCHECK
  if (ilTxHnd >= kIlNumberOfTxObjects)
  {
    return IL_ERROR;
  }
# endif

  /* Stop cyclic send        */
  ilTxState[ilTxHnd] &= kTxNotSendCyclicEvent;

  return (0);
}                               /* End of IlStopEvent() */
#endif /* IL_TX_CYCLIC_EVENT */

#if defined ( IL_ENABLE_TX )
/**********************************************************************************************************************
  IlSetEvent
**********************************************************************************************************************/
void IlSetEvent(IlTransmitHandle ilTxHnd) C_API_3
{
  /*----- Check for valid handle numbers ------------------------------------*/
  IlAssert(ilTxHnd < kIlNumberOfTxObjects, ILERR_ILLTXMSGHANDLE);

# if defined IL_ENABLE_SYS_ARGCHECK
  if (ilTxHnd >= kIlNumberOfTxObjects)
  {
    return;
  }
# endif

  ilTxState[ilTxHnd] |= kTxSendRequest;
}                               /* End of IlSetEvent() */
#endif /* IL_ENABLE_TX */

#if defined( IL_ENABLE_TX_SECURE_EVENT )
/**********************************************************************************************************************
  IlSecureEvent
**********************************************************************************************************************/
void IlSecureEvent(IlTransmitHandle ilTxHnd) C_API_3
{
  /*----- Check for valid handle numbers ------------------------------------*/
  IlAssert(ilTxHnd < kIlNumberOfTxObjects, ILERR_ILLTXMSGHANDLE);

# if defined IL_ENABLE_SYS_ARGCHECK
  if (ilTxHnd >= kIlNumberOfTxObjects)
  {
    return;
  }
# endif

  /*--- load repeat counter ---*/
  ilTxNSendCounter[ilTxHnd] = IlGetTxRepetitionCounter(ilTxHnd);

  /*--- Start immediately transmission of cyclic event messages -------------*/
  ilTxEventCounter[ilTxHnd] = 0;
}                               /* End of IlSecureEvent() */
#endif

#if defined ( IL_ENABLE_RX )
# if defined ( IL_ENABLE_RX_INDICATION_FLAG )
/**********************************************************************************************************************
  IlGetSignalIndicationFlag
**********************************************************************************************************************/
vuint8 IlGetSignalIndicationFlag(IlReceiveFlagHandle ilRxFlagHnd)
{
  vuint8 rc;

  CanInterruptDisable();

  rc = ilRxIndicationFlags[IlIndicationOffset[ilRxFlagHnd]] & IlIndicationMask[ilRxFlagHnd];
  if (rc != 0)
  {
    /* reset indication flag */
    ilRxIndicationFlags[IlIndicationOffset[ilRxFlagHnd]] &= IL_CAST2UINT8(~(IlIndicationMask[ilRxFlagHnd]));
  }

  CanInterruptRestore();

  return (rc);
}                               /* End of IlGetSignalIndicationFlag() */
# endif /* ( IL_ENABLE_RX_INDICATION_FLAG ) */
#endif

/**********************************************************************************************************************
  IlResetRxTimeoutFlags
**********************************************************************************************************************/
void IlResetRxTimeoutFlags(IL_CHANNEL_ILTYPE_ONLY)
{
#if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1) && defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  channel = channel;            /* to avoid compiler warnings */
#endif

#if defined ( IL_ENABLE_RX )
  ResetRxTimeoutFlags(channel);
#endif /* IL_ENABLE_RX */

}                               /* End of IlResetRxTimeoutFlags() */

#if defined ( IL_ENABLE_TX ) && defined( IL_ENABLE_SEND_DIRECT )
/**********************************************************************************************************************
  IlSendDirect
**********************************************************************************************************************/
void IlSendDirect(IL_CHANNEL_ILTYPE_FIRST IlTransmitHandle ilTxHnd)
{
  IlAssert(ilTxHnd < kIlNumberOfTxObjects, ILERR_ILLTXMSGHANDLE);
# if defined ( IL_ENABLE_SYS_ARGCHECK )
  if (ilTxHnd >= kIlNumberOfTxObjects)
  {
    return;
  }
# endif

  if (TxEnabled(IL_CHANNEL_ILPARA_MACRO))
  {
    if ((ilTxState[ilTxHnd] & kTxSendRequest) != 0)
    {
# if defined ( IL_ENABLE_TX_TIMEOUT )
      if ((ilTxState[ilTxHnd] & kTxCheckTimeout) != 0)
      {
        /* start Timeout supervision for this message */
        IlAssert(IlTxTimeoutIndirection[ilTxHnd] < kIlNumberOfTxTimeoutCounters, ILERR_ILLTXTIMEOUTINDEX);
        CanInterruptDisable();
        if (ilTxTimeoutCounter[IlTxTimeoutIndirection[ilTxHnd]] == 0)
        {
          ilTxTimeoutCounter[IlTxTimeoutIndirection[ilTxHnd]] = IlGetTxTimeout(IL_CHANNEL_ILPARA_MACRO);
        }
        CanInterruptRestore();
      }
# endif
      IlSendMessage(ilTxHnd);
    }
  }
}                               /* End of IlSendDirect() */
#endif /* ( IL_ENABLE_TX ) && ( IL_ENABLE_SEND_DIRECT ) */


#if defined( VGEN_GENY ) && defined( IL_ENABLE_TX_DYNAMIC_CYCLETIME )
/**********************************************************************************************************************
  IlSetDynTxCycleTimeRaw
**********************************************************************************************************************/
void IlSetDynTxCycleTimeRaw(IlTransmitHandle ilTxHnd, IltTxCounter ilTxTicks)
{
  IlAssert(ilTxHnd < kIlNumberOfTxObjects, ILERR_ILLTXMSGHANDLE);
# if defined ( IL_ENABLE_SYS_ARGCHECK )
  if (ilTxHnd >= kIlNumberOfTxObjects)
  {
    return;
  }
# endif
  ilTxDynCyclicCycles[ilTxHnd] = ilTxTicks;
}                               /* End of IlSetDynTxCycleTimeRaw() */
#endif  /* VGEN_GENY && IL_ENABLE_TX_DYNAMIC_CYCLETIME */


#if defined( VGEN_GENY ) && defined( IL_ENABLE_TX_DYNAMIC_DELAYTIME )
/**********************************************************************************************************************
  IlSetDynTxDelayTimeRaw 
**********************************************************************************************************************/
void IlSetDynTxDelayTimeRaw(IlTransmitHandle ilTxHnd, IltTxUpdateCounter ilTxTicks)
{
  IlAssert(ilTxHnd < kIlNumberOfTxObjects, ILERR_ILLTXMSGHANDLE);
# if defined ( IL_ENABLE_SYS_ARGCHECK )
  if (ilTxHnd >= kIlNumberOfTxObjects)
  {
    return;
  }
# endif
  ilTxDynDelayCycles[ilTxHnd] = ilTxTicks;
}                               /* End of IlSetDynTxDelayTimeRaw() */
#endif  /* VGEN_GENY && IL_ENABLE_TX_DYNAMIC_DELAYTIME */


#if defined( VGEN_GENY ) && defined( IL_ENABLE_TX_DYNAMIC_START_DELAYTIME )
/**********************************************************************************************************************
  IlSetDynTxStartDelayTimeRaw  
**********************************************************************************************************************/
void IlSetDynTxStartDelayTimeRaw(IlTransmitHandle ilTxHnd, IltTxCounter ilTxTicks)
{
  IlAssert(ilTxHnd < kIlNumberOfTxObjects, ILERR_ILLTXMSGHANDLE);
# if defined ( IL_ENABLE_SYS_ARGCHECK )
  if (ilTxHnd >= kIlNumberOfTxObjects)
  {
    return;
  }
# endif
  ilTxDynStartDelayCycles[ilTxHnd] = ilTxTicks;
}                               /* End of IlSetDynTxStartDelayTimeRaw() */
#endif  /* VGEN_GENY && IL_ENABLE_TX_DYNAMIC_START_DELAYTIME */


#if defined( VGEN_GENY ) && defined( IL_ENABLE_SYS_TX_REPETITIONS_ARE_ACTIVE_FCT )
/**********************************************************************************************************************
  IlTxRepetitionsAreActive
**********************************************************************************************************************/
Il_Boolean IlTxRepetitionsAreActive(IL_CHANNEL_ILTYPE_ONLY)
{
# if defined( IL_ENABLE_TX_SECURE_EVENT )
  IlTransmitHandle ilTxHnd;
#  if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
  ilTxHnd = IlTxMsgStartIndex[channel + 1];
  if (IlTxMsgStartIndex[channel] != ilTxHnd)
#  else
  ilTxHnd = kIlNumberOfTxObjects;
#  endif
  {
    /*--- Loop for every transmit object ---------------------------------------*/
    do
    {
      /* Initial Decrement */
      ilTxHnd--;
      if (ilTxNSendCounter[ilTxHnd] != 0)
      {
        return IL_TRUE;
      }
    }
#  if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1)
    while (ilTxHnd != IlTxMsgStartIndex[channel]);
#  else
    while (ilTxHnd != 0);
#  endif
  }
# else
#  if defined ( C_MULTIPLE_RECEIVE_CHANNEL ) && (kIlNumberOfChannels > 1) && defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  channel = channel;            /* to avoid compiler warnings */
#  endif
# endif /* IL_ENABLE_TX_SECURE_EVENT */
  return IL_FALSE;
}
#endif /* VGEN_GENY && IL_ENABLE_SYS_TX_REPETITIONS_ARE_ACTIVE_FCT */


#if defined ( IL_ENABLE_SYS_GET_CONTEXT ) || defined( VGEN_ENABLE_MDWRAP )
/**********************************************************************************************************************
  IlGetModuleContext
**********************************************************************************************************************/
void IlGetModuleContext(tIlModuleContextStructPtr pContext)
{
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL )
  CanChannelHandle channel;
# endif
# if defined ( IL_ENABLE_TX )
  IlTransmitHandle ilTxHnd;
# endif
# if defined( IL_ENABLE_RX_TIMEOUT ) || defined( IL_ENABLE_TX_TIMEOUT ) 
  vuintx i;
# endif


  pContext->ilMagicNumber = ((vuint32) ((vuint32) IL_VECTOR_VERSION << 16) | IL_VECTOR_RELEASE_VERSION);

# if defined ( IL_ENABLE_RX_MULTIPLE_NODES )
  pContext->ilECUMask = ilECUMask;
# endif

/* Copy Channel Dependent Context */
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL )
  for (channel = 0; channel < kIlNumberOfChannels; channel++)
# endif
  {
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL )
    pContext->ilChannelState[channel] = ilChannelState[channel];
#  if defined( IL_ENABLE_RX_POLLING ) 
    pContext->ilChannelReceive[channel] = ilChannelReceive[channel];
#  endif
# else
    pContext->ilChannelState = ilChannelState;
#  if defined( IL_ENABLE_RX_POLLING ) 
    pContext->ilChannelReceive = ilChannelReceive;
#  endif
# endif /* C_MULTIPLE_RECEIVE_CHANNEL */

  }

/* Copy Tx Dependent Context */
# if defined ( IL_ENABLE_TX )
  for (ilTxHnd = 0; ilTxHnd < kIlNumberOfTxObjects; ilTxHnd++)
  {
    pContext->ilTxState[ilTxHnd] = ilTxState[ilTxHnd];
    pContext->ilTxCyclicCounter[ilTxHnd] = ilTxCyclicCounter[ilTxHnd];
    pContext->ilTxUpdateCounter[ilTxHnd] = ilTxUpdateCounter[ilTxHnd];

#  if defined( VGEN_GENY ) && defined( IL_ENABLE_TX_DYNAMIC_CYCLETIME )
    pContext->ilTxDynCyclicCycles[ilTxHnd] = ilTxDynCyclicCycles[ilTxHnd];
#  endif
#  if defined( VGEN_GENY ) && defined( IL_ENABLE_TX_DYNAMIC_DELAYTIME  )
    pContext->ilTxDynDelayCycles[ilTxHnd] = ilTxDynDelayCycles[ilTxHnd];
#  endif
#  if defined( VGEN_GENY ) && defined( IL_ENABLE_TX_DYNAMIC_START_DELAYTIME  )
    pContext->ilTxDynStartDelayCycles[ilTxHnd] = ilTxDynStartDelayCycles[ilTxHnd];
#  endif
#  if defined( IL_ENABLE_TX_SECURE_EVENT )
    pContext->ilTxNSendCounter[ilTxHnd] = ilTxNSendCounter[ilTxHnd];
#  endif
#  if defined ( IL_ENABLE_TX_CYCLIC_EVENT ) || defined ( IL_ENABLE_TX_SECURE_EVENT ) || defined ( IL_ENABLE_TX_FAST_ON_START )
    pContext->ilTxEventCounter[ilTxHnd] = ilTxEventCounter[ilTxHnd];
#  endif
  }

#  if defined( IL_ENABLE_TX_CYCLIC_EVENT )
  pContext->ilIfActiveFlags = ilIfActiveFlags;
#  endif
#  if defined( IL_ENABLE_TX_TIMEOUT_FLAG )
  VStdMemCpyRamToRam(pContext->ilTxTimeoutFlags, ilTxTimeoutFlags, kIlNumberOfTxTimeoutFlags);
#  endif
#  if defined( IL_ENABLE_TX_CONFIRMATION_FLAG )
  VStdMemCpyRamToRam(pContext->ilTxConfirmationFlags, ilTxConfirmationFlags, kIlNumberOfTxConfirmationFlags);
#  endif
#  if defined( IL_ENABLE_TX_TIMEOUT )
  for (i = 0; i < (vuintx) kIlNumberOfTxTimeoutCounters; i++)
  {
    pContext->ilTxTimeoutCounter[i] = ilTxTimeoutCounter[i];
  }
#  endif
# endif /* IL_ENABLE_TX */

/* Copy Rx Dependent Context */
# if defined ( IL_ENABLE_RX )
#  if defined( IL_ENABLE_RX_TIMEOUT )
  for (i = 0; i < (vuintx) kIlNumberOfRxTimeoutCounters; i++)
  {
    pContext->ilRxTimeoutCounter[i] = ilRxTimeoutCounter[i];
#   if defined ( VGEN_GENY ) && defined( IL_ENABLE_RX_DYNAMIC_TIMEOUT )
    pContext->ilRxDynamicTimeoutCounter[i] = ilRxDynamicTimeoutCounter[i];
#   endif
  }
  VStdMemCpyRamToRam(pContext->ilRxTimerFlags, ilRxTimerFlags, kIlNumberOfTimerFlagBytes);
#  endif
#  if defined( IL_ENABLE_RX_DATACHANGED_FLAG )
  VStdMemCpyRamToRam(pContext->ilRxDataChangedFlags, ilRxDataChangedFlags, kIlNumberOfRxDataChangedFlags);
#  endif
#  if defined( IL_ENABLE_RX_INDICATION_FLAG )
  VStdMemCpyRamToRam(pContext->ilRxIndicationFlags, ilRxIndicationFlags, kIlNumberOfRxIndicationFlags);
#  endif
#  if defined( IL_ENABLE_RX_FIRSTVALUE_FLAG )
  VStdMemCpyRamToRam(pContext->ilRxFirstvalueFlags, ilRxFirstvalueFlags, kIlNumberOfRxFirstvalueFlags);
#  endif
#  if defined ( IL_ENABLE_RX_TIMEOUT_FLAG )
  VStdMemCpyRamToRam(pContext->ilRxTimeoutFlags, ilRxTimeoutFlags, kIlNumberOfRxTimeoutFlags);
#  endif
#  if !defined( VGEN_GENY ) && defined( IL_ENABLE_RX_MODE_SIGNALS )
  pContext->ilModeIndicationFlags = ilModeIndicationFlags;
#  endif
# endif /* IL_ENABLE_RX */

}                               /* End of IlGetModuleContext() */
#endif /* IL_ENABLE_SYS_GET_CONTEXT || VGEN_ENABLE_MDWRAP */

#if defined ( IL_ENABLE_SYS_SET_CONTEXT ) || defined( VGEN_ENABLE_QWRAP )
/**********************************************************************************************************************
  IlSetModuleContext
**********************************************************************************************************************/
vuint8 IlSetModuleContext(tIlModuleContextStructPtr pContext)
{
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL )
  CanChannelHandle channel;
# endif
# if defined ( IL_ENABLE_TX )
  IlTransmitHandle ilTxHnd;
# endif
# if defined( IL_ENABLE_RX_TIMEOUT ) || defined( IL_ENABLE_TX_TIMEOUT ) 
  vuintx i;
# endif

  if (pContext->ilMagicNumber == (vuint32) (((vuint32) IL_VECTOR_VERSION << 16) | IL_VECTOR_RELEASE_VERSION))
  {
# if defined ( IL_ENABLE_RX_MULTIPLE_NODES )
    ilECUMask = pContext->ilECUMask;
# endif

/* Copy Channel Dependent Context */
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL )
    for (channel = 0; channel < kIlNumberOfChannels; channel++)
# endif
    {
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL )
      ilChannelState[channel] = pContext->ilChannelState[channel];
#  if defined( IL_ENABLE_RX_POLLING ) 
      ilChannelReceive[channel] = pContext->ilChannelReceive[channel];
#  endif
# else
      ilChannelState = pContext->ilChannelState;
#  if defined( IL_ENABLE_RX_POLLING ) 
      ilChannelReceive = pContext->ilChannelReceive;
#  endif
# endif /* C_MULTIPLE_RECEIVE_CHANNEL */
    }

/* Copy Tx Dependent Context */
# if defined ( IL_ENABLE_TX )
    for (ilTxHnd = 0; ilTxHnd < kIlNumberOfTxObjects; ilTxHnd++)
    {
      ilTxState[ilTxHnd] = pContext->ilTxState[ilTxHnd];
      ilTxCyclicCounter[ilTxHnd] = pContext->ilTxCyclicCounter[ilTxHnd];
      ilTxUpdateCounter[ilTxHnd] = pContext->ilTxUpdateCounter[ilTxHnd];

#  if defined( VGEN_GENY ) && defined( IL_ENABLE_TX_DYNAMIC_CYCLETIME )
      ilTxDynCyclicCycles[ilTxHnd] = pContext->ilTxDynCyclicCycles[ilTxHnd];
#  endif
#  if defined( VGEN_GENY ) && defined( IL_ENABLE_TX_DYNAMIC_DELAYTIME  )
      ilTxDynDelayCycles[ilTxHnd] = pContext->ilTxDynDelayCycles[ilTxHnd];
#  endif
#  if defined( VGEN_GENY ) && defined( IL_ENABLE_TX_DYNAMIC_START_DELAYTIME  )
      ilTxDynStartDelayCycles[ilTxHnd] = pContext->ilTxDynStartDelayCycles[ilTxHnd];
#  endif
#  if defined( IL_ENABLE_TX_SECURE_EVENT )
      ilTxNSendCounter[ilTxHnd] = pContext->ilTxNSendCounter[ilTxHnd];
#  endif
#  if defined ( IL_ENABLE_TX_CYCLIC_EVENT ) || defined ( IL_ENABLE_TX_SECURE_EVENT ) || defined ( IL_ENABLE_TX_FAST_ON_START )
      ilTxEventCounter[ilTxHnd] = pContext->ilTxEventCounter[ilTxHnd];
#  endif
    }
#  if defined( IL_ENABLE_TX_CYCLIC_EVENT )
    ilIfActiveFlags = pContext->ilIfActiveFlags;
#  endif
#  if defined( IL_ENABLE_TX_TIMEOUT_FLAG )
    VStdMemCpyRamToNearRam(ilTxTimeoutFlags, pContext->ilTxTimeoutFlags, kIlNumberOfTxTimeoutFlags);
#  endif
#  if defined( IL_ENABLE_TX_CONFIRMATION_FLAG )
    VStdMemCpyRamToNearRam(ilTxConfirmationFlags, pContext->ilTxConfirmationFlags, kIlNumberOfTxConfirmationFlags);
#  endif
#  if defined( IL_ENABLE_TX_TIMEOUT )
    for (i = 0; i < (vuintx) kIlNumberOfTxTimeoutCounters; i++)
    {
      ilTxTimeoutCounter[i] = pContext->ilTxTimeoutCounter[i];
    }
#  endif
# endif /* IL_ENABLE_TX */

/* Copy Rx Dependent Context */
# if defined ( IL_ENABLE_RX )
#  if defined( IL_ENABLE_RX_TIMEOUT )
    for (i = 0; i < (vuintx) kIlNumberOfRxTimeoutCounters; i++)
    {
      ilRxTimeoutCounter[i] = pContext->ilRxTimeoutCounter[i];
#   if defined ( VGEN_GENY ) && defined( IL_ENABLE_RX_DYNAMIC_TIMEOUT )
      ilRxDynamicTimeoutCounter[i] = pContext->ilRxDynamicTimeoutCounter[i];
#   endif
    }
    VStdMemCpyRamToNearRam(ilRxTimerFlags, pContext->ilRxTimerFlags, kIlNumberOfTimerFlagBytes);
#  endif /* IL_ENABLE_RX_TIMEOUT */
#  if defined( IL_ENABLE_RX_DATACHANGED_FLAG )
    VStdMemCpyRamToNearRam(ilRxDataChangedFlags, pContext->ilRxDataChangedFlags, kIlNumberOfRxDataChangedFlags);
#  endif
#  if defined( IL_ENABLE_RX_INDICATION_FLAG )
    VStdMemCpyRamToNearRam(ilRxIndicationFlags, pContext->ilRxIndicationFlags, kIlNumberOfRxIndicationFlags);
#  endif
#  if defined( IL_ENABLE_RX_FIRSTVALUE_FLAG )
    VStdMemCpyRamToNearRam(ilRxFirstvalueFlags, pContext->ilRxFirstvalueFlags, kIlNumberOfRxFirstvalueFlags);
#  endif
#  if defined ( IL_ENABLE_RX_TIMEOUT_FLAG )
    VStdMemCpyRamToNearRam(ilRxTimeoutFlags, pContext->ilRxTimeoutFlags, kIlNumberOfRxTimeoutFlags);
#  endif
#  if !defined( VGEN_GENY ) && defined( IL_ENABLE_RX_MODE_SIGNALS )
    ilModeIndicationFlags = pContext->ilModeIndicationFlags;
#  endif
# endif /* IL_ENABLE_RX */


    return 1;
  }
  else
  {
    return 0;
  }
}                               /* End of IlSetModuleContext() */
#endif /* IL_ENABLE_SYS_SET_CONTEXT || VGEN_ENABLE_QWRAP */

/**********************************************************************************************************************
  CanCopyFromCan
**********************************************************************************************************************/
#if defined ( VGEN_CANGEN_VERSION ) && defined ( IL_ENABLE_RX_MODE_SIGNALS ) && !defined ( C_ENABLE_MEMCOPY_SUPPORT )
void CanCopyFromCan(void *dst, CanChipDataPtr src, vuint8 len)
{
  if (dst == V_NULL)
  {
    return;
  }

  while (len > 0)
  {
    len--;
    *((vuint8 *) dst) = *(src++);
    dst = ((vuint8 *) dst) + 1;
  }
}                               /* End of CanCopyFromCan() */
#endif



/**********************************************************************************************************************
   GLOBAL MISRA / PCLINT JUSTIFICATION
**********************************************************************************************************************/
/* module specific MISRA deviations:
     MD_Il_0489 : MISRA rule: 17.4
        Reason:      The pointer arithmetic is required for optimized routing implementation.
        Risk:        Invalid memory accesses.
        Prevention:  Verified at integration with the customer hardware with the automated integration test suite.
	 
     MD_Il_0779: MISRA rule: 5.1
        Reason:   Generated names by the NameDecorator are longer then 32 characters.
        Risk:        Invalid memory accesses.
        Prevention: Verified at integration with the customer hardware with the automated integration test suite.
        Fix:            Change settings of NameDecorator.
		
     MD_Il_0777: MISRA rule: 5.1
        Reason:   External identifiers are not unique within the first 6 characters.
        Risk:        Invalid memory accesses.
        Prevention: Verified at integration with the customer hardware with the automated integration test suite.
        Fix:            Change settings of NameDecorator.
		
     MD_Il_0778: 
        Reason:   Generated names by the NameDecorator are longer then 32 characters.
        Risk:        Invalid memory accesses.
        Prevention: Verified at integration with the customer hardware with the automated integration test suite.
        Fix:            Change settings of NameDecorator.
		
     MD_Il_3673:  MISRA rule: 16.7
        Reason:   A pointer is not declared as const although he is not modifyed.
        Risk:       No functional risk.
        Prevention: Not required.
	  
     MD_Il_0310:  MISRA rule: 11.4
        Reason:      Cast operation to uint8* required for optimized memory clear operation. Implementation is correct.
        Risk:        Invalid memory access.
        Prevention:  Verified at integration with the customer hardware with the automated integration test suite.
	  
     MD_Il_0312:  MISRA rule: 11.5
        Reason:     Cast form volatile to none volatile type. RDS structs are only used within Pretransmit and Precopy functions. The implementation is correct.
        Risk:        Invalid memory access.
        Prevention:  Verified at integration with the customer hardware with the automated integration test suite.
	 
      MD_Il_0635:  MISRA rule: 6.4
        Reason:      Bitfields are required for message access.
        Risk:        Undefined compiler behaviour.
        Prevention:  Usage of vbittype in bit-fields verified by CAN-Driver component.
	 
     MD_Il_0781:  MISRA rule:5.6
        Reason:      The generated names are unique in there namespace.
        Risk:        No functional risk.
        Prevention:  Not required.
	 
     MD_Il_3355_3356_3359
        Reason:      IlAssert works sometimes only with more than one channel
        Risk:        No functional risk.
        Prevention:  Not required.
	 
     MD_Il_19.10:
        Reason: Parameter used in structures that does not allow brackets.
        Risk: None atomic parameter lead to compile errors.
        Prevention: Used parameter is always atomic depend on usage.
	 
     MD_Il_8.8
        Reason: External linkage used for library check.
        Risk: Library check failed.
        Prevention: Integration test version check.
	 
     MD_Il_3689
        Reason: The Parameter ilRxToHnd could run out of bounds
        Risk: Invalid memory access.
        Prevention: A If condition assure that the ilRxToHnd will not run out of bounds
	
     MD_Il_1330
        Reason: A Parameter is named different in the CAN Driver
        Risk:        No functional risk.
        Prevention:  Not required.
	 
     MD_Il_0342:
        Reason:     Glue operator needed for optimized code implementation style. K&R compatible compilers are mandatory.
        Risk:       Compile errors.
        Prevention: K&R compatible compilers are mandatory.

     MD_Il_0770: MISRA rule: 14.5
        Reason: Continue statement is used for proper functionality of code and for better readability.
        Risk: Relevant fragments of code not executed.
        Prevention:  Verified at integration with the customer hardware with the automated integration test suite.
        
     MD_Il_3360
        Reason: A do-while loop will be only be executed once.
        Risk:        No functional risk.
        Prevention:  Not required.
      
      MD_Il_0290    
        Reason: negated mask is interpreted as a negative value by qac
        Risk:        No functional risk.
        Prevention:  Not required.
        
     MD_Il_0291    
        Reason: negated mask is interpreted as a negative value by qac
        Risk:        No functional risk.
        Prevention:  Not required.
        
 */



/**********************************************************************************************************************
  END OF FILE: Il.c
**********************************************************************************************************************/
/* STOPSINGLE_OF_MULTIPLE */
