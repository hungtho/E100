/* -----------------------------------------------------------------------------
  Filename:    tp_cfg.h
  Description: Toolversion: 01.02.12.01.80.07.77.00.00.00
               
               Serial Number: CBD1800777
               Customer Info: Young Hwa Tech Co, Ltd, 
                              Package: CBD Symc SLP1 - in projects for SsangYong 
                              Micro: SPC570S50E1CEFAY
                              Compiler: Green Hills 2017.5.4
               
               
               Generator Fwk   : GENy 
               Generator Module: Tp_Iso15765
               
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

#if !defined(__TP_CFG_H__)
#define __TP_CFG_H__

#include "can_par.h"
#define TP_MEMORY_MODEL_DATA

#define TP_ENABLE_SINGLE_MSG_OBJ
#define TP_ISO15765DLL_VERSION               0x0236u
#define TP_ISO15765DLL_RELEASE_VERSION       0x00u

#define kTpNumberOfCanChannels               1
#ifndef kTpOn
#define kTpOn                                1
#endif

#ifndef kTpOff
#define kTpOff                               0
#endif

#define TP_TYPE_SINGLE_NORMAL_ADDRESSING_MULTI_BASED
struct tTpCopyToCanInfoStruct_s
{
  canuint8                       Channel;     /* TP Channel                           */
  TxDataPtr                      pDestination;/* Pointer to destination buffer        */
  TP_MEMORY_MODEL_DATA canuint8* pSource;     /* Pointer to source buffer (if linear) */
  canuint16                      Length;      /* The maximum length to copy           */
};
typedef struct tTpCopyToCanInfoStruct_s tTpCopyToCanInfoStruct;
typedef struct tTpCopyToCanInfoStruct_s *TpCopyToCanInfoStructPtr;

#define TP_USE_ISO_COMPLIANCE                kTpOn
#define TP_USE_FAST_PRECOPY                  kTpOff
#define TP_USE_DIAGPRECOPY                   kTpOff
#define TP_CAN_CHANNEL_INDEX                 0
#define TP_ENABLE_ISO_15765_2_2
#define TP_DISABLE_ASR_SINGLE_TP
#define TP_DISABLE_OBD_PRECOPY

/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

#define TP_USE_EXTENDED_API_BS               kTpOff
#define TP_USE_EXTENDED_API_STMIN            kTpOff
#define TP_USE_TX_OF_FC_IN_ISR               kTpOn
#define TP_USE_OVERRUN_INDICATION            kTpOff
#define TP_USE_ONLY_FIRST_FC                 kTpOn
#define TP_USE_FAST_TX_TRANSMISSION          kTpOff
#define TP_USE_QUEUE_IN_ISR                  kTpOn
#define TP_USE_NO_STMIN_AFTER_FC             kTpOff
#define MEMORY_NEAR_TP_SAVE                  MEMORY_NEAR
#define TP_USE_TX_HANDLE_CHANGEABLE          kTpOff
#define TP_USE_GATEWAY_API                   kTpOff
#define TP_USE_RX_CHANNEL_WITHOUT_FC         kTpOff
#define TP_USE_TX_CHANNEL_WITHOUT_FC         kTpOff
#define TP_USE_OLD_STMIN_CALCULATION         kTpOff
#define TP_USE_VARIABLE_RX_DLC_CHECK         kTpOff
#define TP_USE_FIX_RX_DLC_CHECK              kTpOn
#define TP_USE_PADDING                       kTpOn
#define TP_PADDING_PATTERN                   0x00
#define TP_USE_VARIABLE_DLC                  kTpOff
#define TP_DISABLE_IGNORE_FC_RES_STMIN
#define TP_DISABLE_CANCEL_FC_RES_STMIN
#define TP_DISABLE_IGNORE_FC_OVFL
#define TP_DISABLE_WAIT_FOR_CORRECT_SN
#define TP_DISABLE_SINGLE_CHAN_MULTICONN
#define TP_DISABLE_FC_WAIT
#define TP_USE_UNEXPECTED_FC_CANCELATION     kTpOff
#define TP_DISABLE_EXT_COPYFROMCAN_API


/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

#define TP_USE_NORMAL_ADDRESSING             kTpOn
#define TP_USE_NORMAL_FIXED_ADDRESSING       kTpOff
#define TP_USE_EXTENDED_ADDRESSING           kTpOff
#define TP_USE_MIXED_11_ADDRESSING           kTpOff
#define TP_USE_MIXED_29_ADDRESSING           kTpOff
#define TP_ENABLE_SINGLE_CHANNEL_TP
#define TP_DISABLE_MULTIPLE_ADDRESSING
#define TP_DISABLE_MULTIPLE_NODES
#define TP_DISABLE_USER_CHECK
#define TP_DISABLE_INTERNAL_CHECK
#define TP_DISABLE_GEN_CHECK
#define TP_DISABLE_RUNTIME_CHECK
#define TP_DISABLE_CANFD
#define TP_DISABLE_LONG_FIRST_FRAMES


/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

#define TP_USE_PRE_COPY_CHECK                kTpOff
#define TP_USE_APPL_PRECOPY                  kTpOff
#define TP_USE_FREE_CHANNEL_SEARCH           kTpOff
#define TP_USE_CUSTOM_RX_MEMCPY              kTpOff
#define TP_DISABLE_FUNCTIONAL_FC_WAIT


/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

#define TP_USE_STMIN_OF_FC                   kTpOn
#define TP_USE_TP_TRANSMIT_QUEUE             kTpOff
#define TP_USE_DYN_ID                        kTpOff
#define TP_USE_CUSTOM_TX_MEMCPY              kTpOn


/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

#define TP_USE_WAIT_FRAMES                   kTpOff
#define TP_USE_MULTIPLE_BASEADDRESS          kTpOff
#define TP_USE_PRE_DISPATCHED_MODE           kTpOff


/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

#define TP_USE_EXT_IDS_FOR_NORMAL            kTpOff
#define TP_USE_MIXED_IDS_FOR_NORMAL          kTpOff


/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

#define TP_DISABLE_MIN_TIMER
#define kTpTxChannelCount                    1
#define kTpRxChannelCount                    1

#define TpMemCpy                             memcpy
#define TpTxCallCycle                        10
#define TpRxCallCycle                        10

#define kBSRequested                         8
#define kTpTxConfirmationTimeout             11
#define kTpRxConfirmationTimeout             11
#define TpSTMin                              40
#define TpTxTimeoutFC                        16
#define TpRxTimeoutCF                        16
#define TpTxTransmitCF                       1
#define __ApplTpPreCopyCheckFunction(x)
#define __ApplTpPrecopyCheckFCFunctional(tpCurrentTargetAddress)
#define TP_DISABLE_CHECKTA_COMPATIBILITY


/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

#define TP_FUNC_ENABLE_RECEPTION
#define TP_FUNC_ENABLE_NORMAL_ADDRESSING
#define TP_FUNC_DISABLE_NORMAL_FIXED_ADDRESSING
#define TP_FUNC_DISABLE_EXTENDED_ADDRESSING
#define TP_FUNC_DISABLE_MIXED_11_ADDRESSING
#define TP_FUNC_DISABLE_MIXED_29_ADDRESSING
#define TP_FUNC_DISABLE_APPL_PRECOPY
#define __ApplTpFuncGetBuffer                DescGetFuncBuffer
canuint8* DescGetFuncBuffer(vuint16 dataLength);
#define __ApplTpFuncIndication               DescFuncReqInd
void DescFuncReqInd(vuint16 dataLength);


#define TP_USE_TP_INDICATION kTpOn
#define TP_USE_RX_ERROR_INDICATION kTpOn
#define TP_USE_TP_CONFIRMATION kTpOn
#define TP_USE_TP_RX_SF kTpOff
#define TP_USE_TP_RX_FF kTpOff
#define TP_USE_TP_RX_CF kTpOff
#define TP_USE_TP_NOTIFY_TX kTpOff
#define TP_USE_TP_CAN_MESSAGE_TRANSMITTED kTpOff
#define TP_USE_TP_TX_FC kTpOff
#define TP_USE_TP_RX_GET_BUFFER kTpOn
#define TP_USE_TX_ERROR_INDICATION kTpOn
#define TP_USE_TP_COPY_TO_CAN kTpOn
#define TP_USE_TP_COPY_FROM_CAN kTpOff
#define TP_USE_TP_RX_CAN_MESSAGE_TRANSMITTED kTpOff
#define TP_USE_TP_TX_DELAY_FINISHED kTpOff

#define kTpTxHandle CanTxLDC_DGN_RESP

#define kTpTxData LDC_DGN_RESP._c


/* function prototypes */
void DescPhysReqInd(canuint16 datLen);
void DescRxErrorIndication(canuint8 errNo);
void DescConfirmation(canuint8 state);
canuint8* DescGetBuffer(canuint16 datLen);
canuint8 DescTxErrorIndication(canuint8 errNo);
vuint8 DescCopyToCAN(TpCopyToCanInfoStructPtr infoStruct);

#define __ApplTpRxIndication(tpChannel, datLen) (DescPhysReqInd(datLen))
#define __ApplTpRxErrorIndication(tpChannel, errNo) (DescRxErrorIndication(errNo))
#define __ApplTpTxConfirmation(tpChannel, state) (DescConfirmation(state))
#define __ApplTpRxSF(tpChannel) 
#define __ApplTpRxFF(tpChannel) 
#define __ApplTpRxCF(tpChannel) 
#define __ApplTpTxNotification(tpChannel, datLen) 
#define __ApplTpTxCanMessageTransmitted(tpChannel) 
#define __ApplTpTxFC(tpChannel) 
#define __ApplTpRxGetBuffer(tpChannel, datLen) (DescGetBuffer(datLen))
#define __ApplTpTxErrorIndication(tpChannel, errNo) (DescTxErrorIndication(errNo))
#define __ApplTpTxCopyToCAN(infoStruct) (DescCopyToCAN(infoStruct))
#define __ApplTpRxCopyFromCAN(tpChannel, src, datLen) 
#define __ApplTpRxCanMessageTransmitted(tpChannel) 
#define __ApplTpTxDelayFinished(tpChannel, state)

#define	TP_FUNC_ENBLE_VARIABLE_DLC_CHECK
#ifdef TP_PADDING_PATTERN
#undef TP_PADDING_PATTERN
#define TP_PADDING_PATTERN 0xAA
#endif

/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 345877849
      #error "The magic number of the generated file <D:\07_Working\E100\source\BSW\CANbedded_Vector\tp_cfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 345877849
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __TP_CFG_H__ */
