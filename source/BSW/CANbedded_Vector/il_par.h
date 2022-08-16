/* -----------------------------------------------------------------------------
  Filename:    il_par.h
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

#if !defined(__IL_PAR_H__)
#define __IL_PAR_H__

/* -----------------------------------------------------------------------------
    &&&~ Typedefs
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_TX)
typedef vuint8 IltTxCounter;
#endif

#if defined(IL_ENABLE_TX)
typedef vuint8 IltTxUpdateCounter;
#endif

#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_TIMEOUT)
typedef vuint8 IltTxTimeoutCounter;
#endif

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_TIMEOUT)
typedef vuint8 IltRxTimeoutCounter;
#endif

#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_SECURE_EVENT)
typedef vuint8 IltTxRepetitionCounter;
#endif



/* -----------------------------------------------------------------------------
    &&&~ Message Handles
 ----------------------------------------------------------------------------- */

#define IlRxMsgHndVCU_3ACh                   0
#define IlRxMsgHndVCU_245h                   1
#define IlRxMsgHndVCU_1D2h                   2
#define IlTxMsgHndLDC_PCAN_STS               0
#define IlTxMsgHndLDC_3A1h                   1
#define IlTxMsgHndLDC_3A0h                   2


/* -----------------------------------------------------------------------------
    &&&~ Signal Handles
 ----------------------------------------------------------------------------- */

#define IlRxSigHndVCU_IGN3_STS               IlRxMsgHndVCU_3ACh
#define IlRxSigHndVCU_IGN4_STS               IlRxMsgHndVCU_3ACh
#define IlRxSigHndVCU_Ready                  IlRxMsgHndVCU_245h
#define IlRxSigHndVCU_CMD_LDC_TARGT_VOLT     IlRxMsgHndVCU_1D2h
#define IlRxSigHndVCU_CMD_EN_LDC             IlRxMsgHndVCU_1D2h
#define IlTxSigHndCMXVersion_LDC_PCAN        IlTxMsgHndLDC_PCAN_STS
#define IlTxSigHndDTCInfo_LDC_PCAN           IlTxMsgHndLDC_PCAN_STS
#define IlTxSigHndSupplyVoltage_LDC_PCAN     IlTxMsgHndLDC_PCAN_STS
#define IlTxSigHndRxErrCnt_LDC_PCAN          IlTxMsgHndLDC_PCAN_STS
#define IlTxSigHndTxErrCnt_LDC_PCAN          IlTxMsgHndLDC_PCAN_STS
#define IlTxSigHndBusOffCnt_LDC_PCAN         IlTxMsgHndLDC_PCAN_STS
#define IlTxSigHndMsgAliveCnt_LDC_PCAN       IlTxMsgHndLDC_PCAN_STS
#define IlTxSigHndLDC_STS_VOLT_IN            IlTxMsgHndLDC_3A1h
#define IlTxSigHndLDC_STS_VOLT_OUT           IlTxMsgHndLDC_3A1h
#define IlTxSigHndLDC_STS_CURR_IN            IlTxMsgHndLDC_3A1h
#define IlTxSigHndLDC_STS_CURR_OUT           IlTxMsgHndLDC_3A1h
#define IlTxSigHndLDC_STS_Ready              IlTxMsgHndLDC_3A0h
#define IlTxSigHndLDC_STS_MODE               IlTxMsgHndLDC_3A0h
#define IlTxSigHndLDC_Out_Mode               IlTxMsgHndLDC_3A0h
#define IlTxSigHndLDC_Out_Emergency          IlTxMsgHndLDC_3A0h
#define IlTxSigHndLDC_Service_WRN_IND        IlTxMsgHndLDC_3A0h
#define IlTxSigHndLDC_STS_Power_OUT          IlTxMsgHndLDC_3A0h
#define IlTxSigHndLDC_STS_TEMP               IlTxMsgHndLDC_3A0h
#define IlTxSigHndCounter_3A0h               IlTxMsgHndLDC_3A0h
#define IlTxSigHndChecksum_3A0h              IlTxMsgHndLDC_3A0h


/* -----------------------------------------------------------------------------
    &&&~ Critical section macros for signals
 ----------------------------------------------------------------------------- */

#define IlEnterCriticalCMXVersion_LDC_PCAN() CanGlobalInterruptDisable()
#define IlLeaveCriticalCMXVersion_LDC_PCAN() CanGlobalInterruptRestore()
#define IlEnterCriticalDTCInfo_LDC_PCAN()    CanGlobalInterruptDisable()
#define IlLeaveCriticalDTCInfo_LDC_PCAN()    CanGlobalInterruptRestore()
#define IlEnterCriticalSupplyVoltage_LDC_PCAN() CanGlobalInterruptDisable()
#define IlLeaveCriticalSupplyVoltage_LDC_PCAN() CanGlobalInterruptRestore()
#define IlEnterCriticalRxErrCnt_LDC_PCAN()   CanGlobalInterruptDisable()
#define IlLeaveCriticalRxErrCnt_LDC_PCAN()   CanGlobalInterruptRestore()
#define IlEnterCriticalTxErrCnt_LDC_PCAN()   CanGlobalInterruptDisable()
#define IlLeaveCriticalTxErrCnt_LDC_PCAN()   CanGlobalInterruptRestore()
#define IlEnterCriticalBusOffCnt_LDC_PCAN()  CanGlobalInterruptDisable()
#define IlLeaveCriticalBusOffCnt_LDC_PCAN()  CanGlobalInterruptRestore()
#define IlEnterCriticalMsgAliveCnt_LDC_PCAN() CanGlobalInterruptDisable()
#define IlLeaveCriticalMsgAliveCnt_LDC_PCAN() CanGlobalInterruptRestore()
#define IlEnterCriticalLDC_STS_VOLT_IN()     CanGlobalInterruptDisable()
#define IlLeaveCriticalLDC_STS_VOLT_IN()     CanGlobalInterruptRestore()
#define IlEnterCriticalLDC_STS_VOLT_OUT()    CanGlobalInterruptDisable()
#define IlLeaveCriticalLDC_STS_VOLT_OUT()    CanGlobalInterruptRestore()
#define IlEnterCriticalLDC_STS_CURR_IN()     CanGlobalInterruptDisable()
#define IlLeaveCriticalLDC_STS_CURR_IN()     CanGlobalInterruptRestore()
#define IlEnterCriticalLDC_STS_CURR_OUT()    CanGlobalInterruptDisable()
#define IlLeaveCriticalLDC_STS_CURR_OUT()    CanGlobalInterruptRestore()
#define IlEnterCriticalLDC_STS_Ready()       CanGlobalInterruptDisable()
#define IlLeaveCriticalLDC_STS_Ready()       CanGlobalInterruptRestore()
#define IlEnterCriticalLDC_STS_MODE()        CanGlobalInterruptDisable()
#define IlLeaveCriticalLDC_STS_MODE()        CanGlobalInterruptRestore()
#define IlEnterCriticalLDC_Out_Mode()        CanGlobalInterruptDisable()
#define IlLeaveCriticalLDC_Out_Mode()        CanGlobalInterruptRestore()
#define IlEnterCriticalLDC_Out_Emergency()   CanGlobalInterruptDisable()
#define IlLeaveCriticalLDC_Out_Emergency()   CanGlobalInterruptRestore()
#define IlEnterCriticalLDC_Service_WRN_IND() CanGlobalInterruptDisable()
#define IlLeaveCriticalLDC_Service_WRN_IND() CanGlobalInterruptRestore()
#define IlEnterCriticalLDC_STS_Power_OUT()   CanGlobalInterruptDisable()
#define IlLeaveCriticalLDC_STS_Power_OUT()   CanGlobalInterruptRestore()
#define IlEnterCriticalLDC_STS_TEMP()        CanGlobalInterruptDisable()
#define IlLeaveCriticalLDC_STS_TEMP()        CanGlobalInterruptRestore()
#define IlEnterCriticalCounter_3A0h()        CanGlobalInterruptDisable()
#define IlLeaveCriticalCounter_3A0h()        CanGlobalInterruptRestore()
#define IlEnterCriticalChecksum_3A0h()       CanGlobalInterruptDisable()
#define IlLeaveCriticalChecksum_3A0h()       CanGlobalInterruptRestore()
#define IlEnterCriticalVCU_IGN3_STS()        CanGlobalInterruptDisable()
#define IlLeaveCriticalVCU_IGN3_STS()        CanGlobalInterruptRestore()
#define IlEnterCriticalVCU_IGN4_STS()        CanGlobalInterruptDisable()
#define IlLeaveCriticalVCU_IGN4_STS()        CanGlobalInterruptRestore()
#define IlEnterCriticalVCU_Ready()           CanGlobalInterruptDisable()
#define IlLeaveCriticalVCU_Ready()           CanGlobalInterruptRestore()
#define IlEnterCriticalVCU_CMD_LDC_TARGT_VOLT() CanGlobalInterruptDisable()
#define IlLeaveCriticalVCU_CMD_LDC_TARGT_VOLT() CanGlobalInterruptRestore()
#define IlEnterCriticalVCU_CMD_EN_LDC()      CanGlobalInterruptDisable()
#define IlLeaveCriticalVCU_CMD_EN_LDC()      CanGlobalInterruptRestore()


/* -----------------------------------------------------------------------------
    &&&~ Access to RxTimeout flags
 ----------------------------------------------------------------------------- */

#define IlGetVCU_ReadyRxTimeout()            (((vuint8) (ilRxTimeoutFlags[0] & (vuint8) 0x01)) != (vuint8) 0x00)
#define IlSetVCU_ReadyRxTimeout()            (ilRxTimeoutFlags[0] |= (vuint8) 0x01)
#define IlClrVCU_ReadyRxTimeout()            (ilRxTimeoutFlags[0] &= (vuint8) (0xFF & (vuint8) 0xFE))


/* -----------------------------------------------------------------------------
    &&&~ Declaration Confirmation Functions
 ----------------------------------------------------------------------------- */

/* Application signal confirmation callback functions */
extern void ApplMsgAliveCnt_LDC_PCANSigConfirmation(void);
extern void ApplCounter_3A0hSigConfirmation(void);


/* -----------------------------------------------------------------------------
    &&&~ Declaration Indication Functions
 ----------------------------------------------------------------------------- */

/* Application signal indication callback functions */
extern void ApplVCU_CMD_LDC_TARGT_VOLTSigIndication(void);


/* -----------------------------------------------------------------------------
    &&&~ Declaration User Timeout Functions
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_TIMEOUT)
#endif



/* -----------------------------------------------------------------------------
    &&&~ Get Rx Signal Access for signals smaller or equal 8bit
 ----------------------------------------------------------------------------- */

/* Handle:    0,Name:                   VCU_IGN3_STS,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxVCU_IGN3_STS()                (VCU_3ACh.VCU_3ACh.VCU_IGN3_STS)
#endif

/* Handle:    1,Name:                   VCU_IGN4_STS,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxVCU_IGN4_STS()                (VCU_3ACh.VCU_3ACh.VCU_IGN4_STS)
#endif

/* Handle:    2,Name:                      VCU_Ready,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxVCU_Ready()                   (VCU_245h.VCU_245h.VCU_Ready)
#endif

/* Handle:    3,Name:         VCU_CMD_LDC_TARGT_VOLT,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxVCU_CMD_LDC_TARGT_VOLT()      (VCU_1D2h.VCU_1D2h.VCU_CMD_LDC_TARGT_VOLT)
#endif

/* Handle:    4,Name:                 VCU_CMD_EN_LDC,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxVCU_CMD_EN_LDC()              (VCU_1D2h.VCU_1D2h.VCU_CMD_EN_LDC)
#endif



/* -----------------------------------------------------------------------------
    &&&~ Set Tx Signal Access for signals smaller or equal 8bit, SendType cyclic or none
 ----------------------------------------------------------------------------- */

/* Handle:    1,Name:               DTCInfo_LDC_PCAN,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxDTCInfo_LDC_PCAN(c) \
{ \
  IlEnterCriticalDTCInfo_LDC_PCAN(); \
  LDC_PCAN_STS.LDC_PCAN_STS.DTCInfo_LDC_PCAN = (c); \
  IlLeaveCriticalDTCInfo_LDC_PCAN(); \
}
#endif

/* Handle:    2,Name:         SupplyVoltage_LDC_PCAN,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxSupplyVoltage_LDC_PCAN(c) \
{ \
  IlEnterCriticalSupplyVoltage_LDC_PCAN(); \
  LDC_PCAN_STS.LDC_PCAN_STS.SupplyVoltage_LDC_PCAN = (c); \
  IlLeaveCriticalSupplyVoltage_LDC_PCAN(); \
}
#endif

/* Handle:    3,Name:              RxErrCnt_LDC_PCAN,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxRxErrCnt_LDC_PCAN(c) \
{ \
  IlEnterCriticalRxErrCnt_LDC_PCAN(); \
  LDC_PCAN_STS.LDC_PCAN_STS.RxErrCnt_LDC_PCAN = (c); \
  IlLeaveCriticalRxErrCnt_LDC_PCAN(); \
}
#endif

/* Handle:    4,Name:              TxErrCnt_LDC_PCAN,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxTxErrCnt_LDC_PCAN(c) \
{ \
  IlEnterCriticalTxErrCnt_LDC_PCAN(); \
  LDC_PCAN_STS.LDC_PCAN_STS.TxErrCnt_LDC_PCAN = (c); \
  IlLeaveCriticalTxErrCnt_LDC_PCAN(); \
}
#endif

/* Handle:    5,Name:             BusOffCnt_LDC_PCAN,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxBusOffCnt_LDC_PCAN(c) \
{ \
  IlEnterCriticalBusOffCnt_LDC_PCAN(); \
  LDC_PCAN_STS.LDC_PCAN_STS.BusOffCnt_LDC_PCAN = (c); \
  IlLeaveCriticalBusOffCnt_LDC_PCAN(); \
}
#endif

/* Handle:    6,Name:           MsgAliveCnt_LDC_PCAN,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxMsgAliveCnt_LDC_PCAN(c) \
{ \
  IlEnterCriticalMsgAliveCnt_LDC_PCAN(); \
  LDC_PCAN_STS.LDC_PCAN_STS.MsgAliveCnt_LDC_PCAN = (c); \
  IlLeaveCriticalMsgAliveCnt_LDC_PCAN(); \
}
#endif

/* Handle:    8,Name:               LDC_STS_VOLT_OUT,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxLDC_STS_VOLT_OUT(c) \
{ \
  IlEnterCriticalLDC_STS_VOLT_OUT(); \
  LDC_3A1h.LDC_3A1h.LDC_STS_VOLT_OUT = (c); \
  IlLeaveCriticalLDC_STS_VOLT_OUT(); \
}
#endif

/* Handle:    9,Name:                LDC_STS_CURR_IN,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxLDC_STS_CURR_IN(c) \
{ \
  IlEnterCriticalLDC_STS_CURR_IN(); \
  LDC_3A1h.LDC_3A1h.LDC_STS_CURR_IN = (c); \
  IlLeaveCriticalLDC_STS_CURR_IN(); \
}
#endif

/* Handle:   11,Name:                  LDC_STS_Ready,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxLDC_STS_Ready(c) \
{ \
  IlEnterCriticalLDC_STS_Ready(); \
  LDC_3A0h.LDC_3A0h.LDC_STS_Ready = (c); \
  IlLeaveCriticalLDC_STS_Ready(); \
}
#endif

/* Handle:   12,Name:                   LDC_STS_MODE,Size:  3,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxLDC_STS_MODE(c) \
{ \
  IlEnterCriticalLDC_STS_MODE(); \
  LDC_3A0h.LDC_3A0h.LDC_STS_MODE = (c); \
  IlLeaveCriticalLDC_STS_MODE(); \
}
#endif

/* Handle:   13,Name:                   LDC_Out_Mode,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxLDC_Out_Mode(c) \
{ \
  IlEnterCriticalLDC_Out_Mode(); \
  LDC_3A0h.LDC_3A0h.LDC_Out_Mode = (c); \
  IlLeaveCriticalLDC_Out_Mode(); \
}
#endif

/* Handle:   14,Name:              LDC_Out_Emergency,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxLDC_Out_Emergency(c) \
{ \
  IlEnterCriticalLDC_Out_Emergency(); \
  LDC_3A0h.LDC_3A0h.LDC_Out_Emergency = (c); \
  IlLeaveCriticalLDC_Out_Emergency(); \
}
#endif

/* Handle:   15,Name:            LDC_Service_WRN_IND,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxLDC_Service_WRN_IND(c) \
{ \
  IlEnterCriticalLDC_Service_WRN_IND(); \
  LDC_3A0h.LDC_3A0h.LDC_Service_WRN_IND = (c); \
  IlLeaveCriticalLDC_Service_WRN_IND(); \
}
#endif

/* Handle:   17,Name:                   LDC_STS_TEMP,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxLDC_STS_TEMP(c) \
{ \
  IlEnterCriticalLDC_STS_TEMP(); \
  LDC_3A0h.LDC_3A0h.LDC_STS_TEMP = (c); \
  IlLeaveCriticalLDC_STS_TEMP(); \
}
#endif

/* Handle:   18,Name:                   Counter_3A0h,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxCounter_3A0h(c) \
{ \
  IlEnterCriticalCounter_3A0h(); \
  LDC_3A0h.LDC_3A0h.Counter_3A0h = (c); \
  IlLeaveCriticalCounter_3A0h(); \
}
#endif

/* Handle:   19,Name:                  Checksum_3A0h,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxChecksum_3A0h(c) \
{ \
  IlEnterCriticalChecksum_3A0h(); \
  LDC_3A0h.LDC_3A0h.Checksum_3A0h = (c); \
  IlLeaveCriticalChecksum_3A0h(); \
}
#endif



/* -----------------------------------------------------------------------------
    &&&~ Set Tx Signal Access extern decl
 ----------------------------------------------------------------------------- */

/* Handle:    0,Name:            CMXVersion_LDC_PCAN,Size: 16,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxCMXVersion_LDC_PCAN(vuint16 sigData);
#endif

/* Handle:    7,Name:                LDC_STS_VOLT_IN,Size: 16,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxLDC_STS_VOLT_IN(vuint16 sigData);
#endif

/* Handle:   10,Name:               LDC_STS_CURR_OUT,Size: 16,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxLDC_STS_CURR_OUT(vuint16 sigData);
#endif

/* Handle:   16,Name:              LDC_STS_Power_OUT,Size: 16,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxLDC_STS_Power_OUT(vuint16 sigData);
#endif




/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 345877849
      #error "The magic number of the generated file <D:\07_Working\E100\source\BSW\CANbedded_Vector\il_par.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 345877849
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __IL_PAR_H__ */
