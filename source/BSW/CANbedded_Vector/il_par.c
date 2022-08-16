/* -----------------------------------------------------------------------------
  Filename:    il_par.c
  Description: Toolversion: 01.02.12.01.80.07.77.00.00.00
               
               Serial Number: CBD1800777
               Customer Info: Young Hwa Tech Co, Ltd, 
                              Package: CBD Symc SLP1 - in projects for SsangYong 
                              Micro: SPC570S50E1CEFAY
                              Compiler: Green Hills 2017.5.4
               
               
               Generator Fwk   : GENy 
               Generator Module: Il_Vector
               
               Configuration   : D:\07_Working\E100\source\Geny\Prj\CBD1800777_20181105_2_TEST.gny
               
               ECU: 
                       TargetSystem: Hw_Mpc5700Cpu
                       Compiler:     GHS
                       Derivates:    SPC570S50
               
               Channel "Channel0":
                       Databasefile: D:\07_Working\E100\source\Geny\Db\E100_PCAN.dbc
                       Bussystem:    CAN
                       Manufacturer: SYMC
                       Node:         LDC

 ----------------------------------------------------------------------------- */
/* -----------------------------------------------------------------------------
  C O P Y R I G H T
 -------------------------------------------------------------------------------
  Copyright (c) 2001-2015 by Vector Informatik GmbH. All rights reserved.
 
  This software is copyright protected and proprietary to Vector Informatik 
  GmbH.
  
  Vector Informatik GmbH grants to you only those rights as set out in the 
  license conditions.
  
  All other rights remain with Vector Informatik GmbH.
 -------------------------------------------------------------------------------
 ----------------------------------------------------------------------------- */

/* -----------------------------------------------------------------------------
    &&&~ Misra  justifications
 ----------------------------------------------------------------------------- */

/* PRQA S 3458 EOF *//* MD_CBD_19.4 */
/* PRQA S 3408 EOF *//* MD_Il_8.8 */
/* PRQA S 3460 EOF *//* MD_CBD_19.4 */
/* PRQA S 3412 EOF *//* MD_CBD_19.4 */
/* PRQA S 3453 EOF *//* MD_CBD_19.7 */
/* PRQA S 2006 EOF *//* MD_CBD_14.7 */
/* PRQA S 0777 EOF *//* MD_Il_0777 */
/* PRQA S 0778 EOF *//* MD_Il_0778 */
/* PRQA S 0779 EOF *//* MD_Il_0779 */
/* PRQA S 3673 EOF *//* MD_Il_3673 */
/* PRQA S 0310 EOF *//* MD_Il_0310 */
/* PRQA S 0312 EOF *//* MD_Il_0312 */
/* PRQA S 0635 EOF *//* MD_Il_0635 */
/* PRQA S 0781 EOF *//* MD_Il_0781 */
/* PRQA S 3410 EOF *//* MD_Il_3410 */
/* PRQA S 1330 EOF *//* MD_Il_1330 */
/* PRQA S 0342 EOF *//* MD_Il_0342 */
/* PRQA S 0857 EOF *//* MD_CBD_1.1 */
/* PRQA S 3109 EOF *//* MD_CBD_14.3 */
/* PRQA S 0883 EOF *//* */


#include "il_inc.h"

/* -----------------------------------------------------------------------------
    &&&~ local variables
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_CYCLIC_EVENT)
#endif



/* -----------------------------------------------------------------------------
    &&&~ Local function prototypes
 ----------------------------------------------------------------------------- */

/* -----------------------------------------------------------------------------
    &&&~ IL internal rx message timeout indication functions
 ----------------------------------------------------------------------------- */

static void IlMsgVCU_245hTimeoutIndication(void);
static void IlMsgVCU_1D2hTimeoutIndication(void);


/* -----------------------------------------------------------------------------
    &&&~ Message confirmation function prototypes
 ----------------------------------------------------------------------------- */

static void IlMsgLDC_PCAN_STSConfirmation(void );
static void IlMsgLDC_3A0hConfirmation(void );




/* -----------------------------------------------------------------------------
    &&&~ Internal Timer Handles
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_TIMEOUT)
#define IlParHndRxVCU_245h                   0
#define IlParHndRxVCU_1D2h                   1
#endif



#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_TIMEOUT)
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 IlTxTimeoutIndirection[kIlNumberOfTxObjects] = 
{
  kIlNoTxToutIndirection /* ID: 0x00000563, Handle: 0, LDC_PCAN_STS [BC] */, 
  kIlNoTxToutIndirection /* ID: 0x000003a1, Handle: 1, LDC_3A1h [BC] */, 
  kIlNoTxToutIndirection /* ID: 0x000003a0, Handle: 2, LDC_3A0h [BC] */
};
#endif


#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_FAST_ON_START)
V_MEMROM0 V_MEMROM1 IltTxCounter V_MEMROM2 IlTxFastOnStartDuration[kIlNumberOfTxObjects] = 
{
  kIlNoFastOnStartDuration /* ID: 0x00000563, Handle: 0, LDC_PCAN_STS [BC] */, 
  kIlNoFastOnStartDuration /* ID: 0x000003a1, Handle: 1, LDC_3A1h [BC] */, 
  kIlNoFastOnStartDuration /* ID: 0x000003a0, Handle: 2, LDC_3A0h [BC] */
};
#endif


#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_FAST_ON_START) && defined(IL_ENABLE_TX_MODE_SIGNALS)
V_MEMROM0 V_MEMROM1 IltTxCounter V_MEMROM2 IlTxFastOnStartMuxDelay[kIlNumberOfTxObjects] = 
{
  0 /* ID: 0x00000563, Handle: 0, LDC_PCAN_STS [BC] */, 
  0 /* ID: 0x000003a1, Handle: 1, LDC_3A1h [BC] */, 
  0 /* ID: 0x000003a0, Handle: 2, LDC_3A0h [BC] */
};
#endif


#if defined(IL_ENABLE_TX)
V_MEMROM0 V_MEMROM1 IltTxCounter V_MEMROM2 IlTxStartCycles[kIlNumberOfTxObjects] = 
{
  kIlNoCycleTime /* ID: 0x00000563, Handle: 0, LDC_PCAN_STS [BC] */, 
  kIlNoCycleTime /* ID: 0x000003a1, Handle: 1, LDC_3A1h [BC] */, 
  kIlNoCycleTime /* ID: 0x000003a0, Handle: 2, LDC_3A0h [BC] */
};
#endif


#if defined(IL_ENABLE_TX)
V_MEMROM0 V_MEMROM1 IltTxUpdateCounter V_MEMROM2 IlTxUpdateCycles[kIlNumberOfTxObjects] = 
{
  kIlNoDelayTime /* ID: 0x00000563, Handle: 0, LDC_PCAN_STS [BC] */, 
  kIlNoDelayTime /* ID: 0x000003a1, Handle: 1, LDC_3A1h [BC] */, 
  kIlNoDelayTime /* ID: 0x000003a0, Handle: 2, LDC_3A0h [BC] */
};
#endif


#if defined(IL_ENABLE_TX)
V_MEMROM0 V_MEMROM1 IltTxCounter V_MEMROM2 IlTxCyclicCycles[kIlNumberOfTxObjects] = 
{
  50 /* ID: 0x00000563, Handle: 0, LDC_PCAN_STS [BC] */, 
  10 /* ID: 0x000003a1, Handle: 1, LDC_3A1h [BC] */, 
  10 /* ID: 0x000003a0, Handle: 2, LDC_3A0h [BC] */
};
#endif


#if defined(IL_ENABLE_TX) && (defined(IL_ENABLE_TX_CYCLIC_EVENT) || defined(IL_ENABLE_TX_SECURE_EVENT) || defined(IL_ENABLE_TX_FAST_ON_START))
V_MEMROM0 V_MEMROM1 IltTxCounter V_MEMROM2 IlTxEventCycles[kIlNumberOfTxObjects] = 
{
  kIlNoCycleTimeFast /* ID: 0x00000563, Handle: 0, LDC_PCAN_STS [BC] */, 
  kIlNoCycleTimeFast /* ID: 0x000003a1, Handle: 1, LDC_3A1h [BC] */, 
  kIlNoCycleTimeFast /* ID: 0x000003a0, Handle: 2, LDC_3A0h [BC] */
};
#endif


#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_POLLING)
V_MEMROM0 V_MEMROM1 IlConfirmationFct V_MEMROM2 IlTxConfirmationFctPtr[kIlNumberOfTxObjects] = 
{
  IlMsgLDC_PCAN_STSConfirmation /* ID: 0x00000563, Handle: 0, LDC_PCAN_STS [BC] */, 
  V_NULL /* ID: 0x000003a1, Handle: 1, LDC_3A1h [BC] */, 
  IlMsgLDC_3A0hConfirmation /* ID: 0x000003a0, Handle: 2, LDC_3A0h [BC] */
};
#endif


#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_TIMEOUT) && defined(C_MULTIPLE_RECEIVE_CHANNEL) && defined(IL_ENABLE_TX_VARYING_TIMEOUT) && (kIlNumberOfChannels > 1)
V_MEMROM0 V_MEMROM1 IltTxTimeoutCounter V_MEMROM2 IlTxTimeout[kIlNumberOfChannels] = 
{
  5
};
#endif


#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_SECURE_EVENT) && defined(IL_ENABLE_TX_VARYING_REPETITION) && (kIlNumberOfTxObjects > 1)
V_MEMROM0 V_MEMROM1 IltTxRepetitionCounter V_MEMROM2 IlTxRepetitionCounters[kIlNumberOfTxObjects] = 
{
  0 /* ID: 0x00000563, Handle: 0, LDC_PCAN_STS [BC] */, 
  0 /* ID: 0x000003a1, Handle: 1, LDC_3A1h [BC] */, 
  0 /* ID: 0x000003a0, Handle: 2, LDC_3A0h [BC] */
};
#endif


/* -----------------------------------------------------------------------------
    &&&~ Rx Timeout Table
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_TIMEOUT)
V_MEMROM0 V_MEMROM1 IltRxTimeoutCounter V_MEMROM2 IlRxTimeoutTbl[kIlNumberOfRxTimeoutCounters] = 
{
  140 /* ID: 0x00000245, VCU_245h [FC] */, 
  140 /* ID: 0x000001d2, VCU_1D2h [BC] */
};
#endif




#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_TIMEOUT)
V_MEMROM0 V_MEMROM1 IlTimeoutIndicationFct V_MEMROM2 IlRxTimeoutFctPtr[kIlNumberOfRxTimeoutCounters] = 
{
  IlMsgVCU_245hTimeoutIndication /* ID: 0x00000245, VCU_245h [FC] */, 
  IlMsgVCU_1D2hTimeoutIndication /* ID: 0x000001d2, VCU_1D2h [BC] */
};
#endif


#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_POLLING)
V_MEMROM0 V_MEMROM1 IlIndicationFct V_MEMROM2 IlCanRxIndicationFctPtr[kIlCanNumberOfRxObjects] = 
{
  V_NULL /* ID: 0x000003ac, Handle: 0, VCU_3ACh [FC] */, 
  V_NULL /* ID: 0x00000245, Handle: 1, VCU_245h [FC] */, 
  V_NULL /* ID: 0x000001d2, Handle: 2, VCU_1D2h [BC] */
};
#endif


/* -----------------------------------------------------------------------------
    &&&~ TxDefaultInitValue Message Tables
 ----------------------------------------------------------------------------- */

V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 LDC_PCAN_STSIlTxDefaultInitValue[8] = 
{
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0xFE
};
V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 LDC_3A0hIlTxDefaultInitValue[8] = 
{
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x28, 
  0x00, 
  0x00, 
  0x00
};


/* -----------------------------------------------------------------------------
    &&&~ TxDefaultInitValue
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_DEFAULTVALUE)
V_MEMROM0 IL_MEMROM1 vuint8 IL_MEMROM2 IL_MEMROM3 *V_MEMROM1 V_MEMROM2  IlTxDefaultInitValue[kIlNumberOfTxObjects] =
{
  LDC_PCAN_STSIlTxDefaultInitValue,
  V_NULL,
  LDC_3A0hIlTxDefaultInitValue
};
#endif



/* -----------------------------------------------------------------------------
    &&&~ Implementation of Confirmation Functions
 ----------------------------------------------------------------------------- */

static void IlMsgLDC_PCAN_STSConfirmation(void )
{
  ApplMsgAliveCnt_LDC_PCANSigConfirmation();
}


static void IlMsgLDC_3A0hConfirmation(void )
{
  ApplCounter_3A0hSigConfirmation();
}




/* -----------------------------------------------------------------------------
    &&&~ Implementation of Precopy Functions
 ----------------------------------------------------------------------------- */

#ifdef IL_ENABLE_RX
vuint8 IlMsgVCU_245hPreCopy(CanRxInfoStructPtr rxStruct)
{
  rxStruct = rxStruct;
  IlEnterCriticalFlagAccess();
  ilRxTimerFlags[0] |= (vuint8) 0x01;
  IlLeaveCriticalFlagAccess();
  return kCanCopyData;
}


#endif

#ifdef IL_ENABLE_RX
vuint8 IlMsgVCU_1D2hPreCopy(CanRxInfoStructPtr rxStruct)
{
  rxStruct = rxStruct;
  IlEnterCriticalFlagAccess();
  ilRxTimerFlags[0] |= (vuint8) 0x02;
  IlLeaveCriticalFlagAccess();
  return kCanCopyData;
}


#endif



/* -----------------------------------------------------------------------------
    &&&~ Implementation of Indication Functions
 ----------------------------------------------------------------------------- */

void IlMsgVCU_245hIndication(CanReceiveHandle rxObject)
{
  rxObject = rxObject;
  IlEnterCriticalFlagAccess();
  ilRxTimeoutFlags[0] &= (vuint8) 0xFE;
  IlLeaveCriticalFlagAccess();
}


void IlMsgVCU_1D2hIndication(CanReceiveHandle rxObject)
{
  rxObject = rxObject;
  ApplVCU_CMD_LDC_TARGT_VOLTSigIndication();
}




/* -----------------------------------------------------------------------------
    &&&~ Implementation Rx Timeout Indication Functions
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_RX) && (defined(IL_ENABLE_RX_TIMEOUT) || defined(IL_ENABLE_RX_EXT_TIMEOUT))
static void IlMsgVCU_245hTimeoutIndication(void)
{
  CanGlobalInterruptDisable();
  ilRxTimeoutFlags[0] |= (vuint8) 0x01;
  CanGlobalInterruptRestore();
}


#endif

#if defined(IL_ENABLE_RX) && (defined(IL_ENABLE_RX_TIMEOUT) || defined(IL_ENABLE_RX_EXT_TIMEOUT))
static void IlMsgVCU_1D2hTimeoutIndication(void)
{
  CanGlobalInterruptDisable();
  VCU_1D2h._c[0] = (vuint8) 0x00;
  VCU_1D2h._c[1] &= (vuint8) 0xEF;
  VCU_1D2h._c[1] |= (vuint8) 0x00;
  CanGlobalInterruptRestore();
}


#endif



/* -----------------------------------------------------------------------------
    &&&~ Implementation of a function to check IfActive flags
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_SYS_TX_SIGNALS_ARE_ACTIVE_FCT)
Il_Boolean IlTxSignalsAreActive(void )
{
  return IL_FALSE;
}


#endif



/* -----------------------------------------------------------------------------
    &&&~ Implementation function to reset indication flags
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_POLLING)
void IlResetCanIndicationFlags(void )
{
  CanGlobalInterruptDisable();
  CanGlobalInterruptRestore();
}


#endif



/* -----------------------------------------------------------------------------
    &&&~ Implementation function to reset confirmation flags
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_TX)
void IlResetCanConfirmationFlags(void )
{
  CanGlobalInterruptDisable();
  IlGetTxConfirmationFlags(0) &= (vuint8) 0xF8;
  CanGlobalInterruptRestore();
}


#endif



/* -----------------------------------------------------------------------------
    &&&~ Set Tx Signal Access 
 ----------------------------------------------------------------------------- */

/* Handle:    0,Name:            CMXVersion_LDC_PCAN,Size: 16,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxCMXVersion_LDC_PCAN(vuint16 sigData)
{
  IlEnterCriticalCMXVersion_LDC_PCAN();
  LDC_PCAN_STS.LDC_PCAN_STS.CMXVersion_LDC_PCAN_0 = ((vuint8) sigData);
  LDC_PCAN_STS.LDC_PCAN_STS.CMXVersion_LDC_PCAN_1 = ((vuint8) (sigData >> 8));
  IlLeaveCriticalCMXVersion_LDC_PCAN();
}


#endif

/* Handle:    7,Name:                LDC_STS_VOLT_IN,Size: 16,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxLDC_STS_VOLT_IN(vuint16 sigData)
{
  IlEnterCriticalLDC_STS_VOLT_IN();
  LDC_3A1h.LDC_3A1h.LDC_STS_VOLT_IN_0 = ((vuint8) sigData);
  LDC_3A1h.LDC_3A1h.LDC_STS_VOLT_IN_1 = ((vuint8) (sigData >> 8));
  IlLeaveCriticalLDC_STS_VOLT_IN();
}


#endif

/* Handle:   10,Name:               LDC_STS_CURR_OUT,Size: 16,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxLDC_STS_CURR_OUT(vuint16 sigData)
{
  IlEnterCriticalLDC_STS_CURR_OUT();
  LDC_3A1h.LDC_3A1h.LDC_STS_CURR_OUT_0 = ((vuint8) sigData);
  LDC_3A1h.LDC_3A1h.LDC_STS_CURR_OUT_1 = ((vuint8) (sigData >> 8));
  IlLeaveCriticalLDC_STS_CURR_OUT();
}


#endif

/* Handle:   16,Name:              LDC_STS_Power_OUT,Size: 16,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxLDC_STS_Power_OUT(vuint16 sigData)
{
  IlEnterCriticalLDC_STS_Power_OUT();
  LDC_3A0h.LDC_3A0h.LDC_STS_Power_OUT_0 = ((vuint8) sigData);
  LDC_3A0h.LDC_3A0h.LDC_STS_Power_OUT_1 = ((vuint8) (sigData >> 8));
  IlLeaveCriticalLDC_STS_Power_OUT();
}


#endif



#if defined(IL_ENABLE_TX)
V_MEMROM0 V_MEMROM1 CanTransmitHandle V_MEMROM2 IlTxIndirection[kIlNumberOfTxObjects] = 
{
  1 /* ID: 0x00000563, Handle: 0, LDC_PCAN_STS [BC] */, 
  2 /* ID: 0x000003a1, Handle: 1, LDC_3A1h [BC] */, 
  3 /* ID: 0x000003a0, Handle: 2, LDC_3A0h [BC] */
};
#endif


/* -----------------------------------------------------------------------------
    &&&~ CAN handle to Il start stop handle
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_TX) && defined(C_ENABLE_CAN_CANCEL_NOTIFICATION)
V_MEMROM0 V_MEMROM1 IlStartStopHnd V_MEMROM2 IlCanHndToIlHnd[kIlCanNumberOfTxObjects] = 
{
  { 0, 0 } /* no Il message */, 
  { 0, 1 } /* start - stop  ID: 0x00000563, LDC_PCAN_STS [BC] */, 
  { 1, 2 } /* start - stop  ID: 0x000003a1, LDC_3A1h [BC] */, 
  { 2, 3 } /* start - stop  ID: 0x000003a0, LDC_3A0h [BC] */
};
#endif




/* -----------------------------------------------------------------------------
    &&&~ TxTypes for interaction layer tx messages 
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_TX)
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 IlTxType[kIlNumberOfTxObjects] = 
{
  kTxSendCyclic /* ID: 0x00000563, Handle: 0, LDC_PCAN_STS [BC] */, 
  kTxSendCyclic /* ID: 0x000003a1, Handle: 1, LDC_3A1h [BC] */, 
  kTxSendCyclic /* ID: 0x000003a0, Handle: 2, LDC_3A0h [BC] */
};
#endif




/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 345877849
      #error "The magic number of the generated file <D:\07_Working\E100\source\BSW\CANbedded_Vector\il_par.c> is different. Please check time and date of generated files!"
  #endif
#else
  #error "The magic number is not defined in the generated file <D:\07_Working\E100\source\BSW\CANbedded_Vector\il_par.c> "

#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

