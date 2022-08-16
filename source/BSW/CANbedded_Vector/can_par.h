/* -----------------------------------------------------------------------------
  Filename:    can_par.h
  Description: Toolversion: 01.02.12.01.80.07.77.00.00.00
               
               Serial Number: CBD1800777
               Customer Info: Young Hwa Tech Co, Ltd, 
                              Package: CBD Symc SLP1 - in projects for SsangYong 
                              Micro: SPC570S50E1CEFAY
                              Compiler: Green Hills 2017.5.4
               
               
               Generator Fwk   : GENy 
               Generator Module: DrvCan__base
               
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

#if !defined(__CAN_PAR_H__)
#define __CAN_PAR_H__

#include "can_cfg.h"
#include "v_inc.h"
#include "drv_par.h"

/* -----------------------------------------------------------------------------
    &&&~ Extern declarations of callback functions
 ----------------------------------------------------------------------------- */

#if defined(C_MULTIPLE_RECEIVE_CHANNEL) || defined(C_SINGLE_RECEIVE_CHANNEL)
#endif

/* CODE CATEGORY 1 START */
extern vuint8 IlMsgVCU_245hPreCopy(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 IlMsgVCU_1D2hPreCopy(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 TpPrecopy(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 TpFuncPrecopy(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */


/* -----------------------------------------------------------------------------
    &&&~ Extern declarations of confirmation functions
 ----------------------------------------------------------------------------- */

/* CODE CATEGORY 1 START */
extern void TpDrvConfirmation(CanTransmitHandle txObject);
/* CODE CATEGORY 1 END */



/* -----------------------------------------------------------------------------
    &&&~ Extern declarations of indication functions
 ----------------------------------------------------------------------------- */

/* CODE CATEGORY 1 START */
extern void IlMsgVCU_245hIndication(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void IlMsgVCU_1D2hIndication(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */





/* -----------------------------------------------------------------------------
    &&&~ Handles of send objects
 ----------------------------------------------------------------------------- */

#define CanTxLDC_DGN_RESP                    0
#define CanTxLDC_PCAN_STS                    1
#define CanTxLDC_3A1h                        2
#define CanTxLDC_3A0h                        3


/* -----------------------------------------------------------------------------
    &&&~ Access to confirmation flags
 ----------------------------------------------------------------------------- */

#define LDC_PCAN_STS_conf_b                  (CanConfirmationFlags.w[0].b0)
#define CanWriteSyncLDC_PCAN_STS_conf_b(x) \
{ \
  CanStartFlagWriteSync(); \
  LDC_PCAN_STS_conf_b = (x); \
  CanEndFlagWriteSync(); \
}
#define LDC_3A1h_conf_b                      (CanConfirmationFlags.w[0].b1)
#define CanWriteSyncLDC_3A1h_conf_b(x) \
{ \
  CanStartFlagWriteSync(); \
  LDC_3A1h_conf_b = (x); \
  CanEndFlagWriteSync(); \
}
#define LDC_3A0h_conf_b                      (CanConfirmationFlags.w[0].b2)
#define CanWriteSyncLDC_3A0h_conf_b(x) \
{ \
  CanStartFlagWriteSync(); \
  LDC_3A0h_conf_b = (x); \
  CanEndFlagWriteSync(); \
}


/* -----------------------------------------------------------------------------
    &&&~ Handles of receive objects
 ----------------------------------------------------------------------------- */

#define CanRxVCU_3ACh                        0
#define CanRxVCU_245h                        1
#define CanRxVCU_1D2h                        2
#define CanRxLDC_DGN_REQ                     3
#define CanRxDIAG_FUNC_REQ                   4


/* -----------------------------------------------------------------------------
    &&&~ Access to data bytes of Rx messages
 ----------------------------------------------------------------------------- */

/* ID: 0x000003ac, Handle: 0, VCU_3ACh [FC] */
#define c1_VCU_3ACh_c                        (VCU_3ACh._c[0])
#define c2_VCU_3ACh_c                        (VCU_3ACh._c[1])

/* ID: 0x00000245, Handle: 1, VCU_245h [FC] */
#define c1_VCU_245h_c                        (VCU_245h._c[0])
#define c2_VCU_245h_c                        (VCU_245h._c[1])
#define c3_VCU_245h_c                        (VCU_245h._c[2])
#define c4_VCU_245h_c                        (VCU_245h._c[3])

/* ID: 0x000001d2, Handle: 2, VCU_1D2h [BC] */
#define c1_VCU_1D2h_c                        (VCU_1D2h._c[0])
#define c2_VCU_1D2h_c                        (VCU_1D2h._c[1])



/* -----------------------------------------------------------------------------
    &&&~ Access to data bytes of Tx messages
 ----------------------------------------------------------------------------- */

/* ID: 0x0000076b, Handle: 0, LDC_DGN_RESP [BC] */
#define c1_LDC_DGN_RESP_c                    (LDC_DGN_RESP._c[0])
#define c2_LDC_DGN_RESP_c                    (LDC_DGN_RESP._c[1])
#define c3_LDC_DGN_RESP_c                    (LDC_DGN_RESP._c[2])
#define c4_LDC_DGN_RESP_c                    (LDC_DGN_RESP._c[3])
#define c5_LDC_DGN_RESP_c                    (LDC_DGN_RESP._c[4])
#define c6_LDC_DGN_RESP_c                    (LDC_DGN_RESP._c[5])
#define c7_LDC_DGN_RESP_c                    (LDC_DGN_RESP._c[6])
#define c8_LDC_DGN_RESP_c                    (LDC_DGN_RESP._c[7])

/* ID: 0x00000563, Handle: 1, LDC_PCAN_STS [BC] */
#define c1_LDC_PCAN_STS_c                    (LDC_PCAN_STS._c[0])
#define c2_LDC_PCAN_STS_c                    (LDC_PCAN_STS._c[1])
#define c3_LDC_PCAN_STS_c                    (LDC_PCAN_STS._c[2])
#define c4_LDC_PCAN_STS_c                    (LDC_PCAN_STS._c[3])
#define c5_LDC_PCAN_STS_c                    (LDC_PCAN_STS._c[4])
#define c6_LDC_PCAN_STS_c                    (LDC_PCAN_STS._c[5])
#define c7_LDC_PCAN_STS_c                    (LDC_PCAN_STS._c[6])
#define c8_LDC_PCAN_STS_c                    (LDC_PCAN_STS._c[7])

/* ID: 0x000003a1, Handle: 2, LDC_3A1h [BC] */
#define c1_LDC_3A1h_c                        (LDC_3A1h._c[0])
#define c2_LDC_3A1h_c                        (LDC_3A1h._c[1])
#define c3_LDC_3A1h_c                        (LDC_3A1h._c[2])
#define c4_LDC_3A1h_c                        (LDC_3A1h._c[3])
#define c5_LDC_3A1h_c                        (LDC_3A1h._c[4])
#define c6_LDC_3A1h_c                        (LDC_3A1h._c[5])
#define c7_LDC_3A1h_c                        (LDC_3A1h._c[6])
#define c8_LDC_3A1h_c                        (LDC_3A1h._c[7])

/* ID: 0x000003a0, Handle: 3, LDC_3A0h [BC] */
#define c1_LDC_3A0h_c                        (LDC_3A0h._c[0])
#define c2_LDC_3A0h_c                        (LDC_3A0h._c[1])
#define c3_LDC_3A0h_c                        (LDC_3A0h._c[2])
#define c4_LDC_3A0h_c                        (LDC_3A0h._c[3])
#define c5_LDC_3A0h_c                        (LDC_3A0h._c[4])
#define c6_LDC_3A0h_c                        (LDC_3A0h._c[5])
#define c7_LDC_3A0h_c                        (LDC_3A0h._c[6])
#define c8_LDC_3A0h_c                        (LDC_3A0h._c[7])



/* -----------------------------------------------------------------------------
    &&&~ RDS Access
 ----------------------------------------------------------------------------- */

typedef struct _c_LDC_DGN_REQ_RDS_msgTypeTag
{
  vbittype DGN_REQ_LDC_7 : 8;
  vbittype DGN_REQ_LDC_6 : 8;
  vbittype DGN_REQ_LDC_5 : 8;
  vbittype DGN_REQ_LDC_4 : 8;
  vbittype DGN_REQ_LDC_3 : 8;
  vbittype DGN_REQ_LDC_2 : 8;
  vbittype DGN_REQ_LDC_1 : 8;
  vbittype DGN_REQ_LDC_0 : 8;
} _c_LDC_DGN_REQ_RDS_msgType;

typedef struct _c_DIAG_FUNC_REQ_RDS_msgTypeTag
{
  vbittype DIAG_REQ_FUNC_7 : 8;
  vbittype DIAG_REQ_FUNC_6 : 8;
  vbittype DIAG_REQ_FUNC_5 : 8;
  vbittype DIAG_REQ_FUNC_4 : 8;
  vbittype DIAG_REQ_FUNC_3 : 8;
  vbittype DIAG_REQ_FUNC_2 : 8;
  vbittype DIAG_REQ_FUNC_1 : 8;
  vbittype DIAG_REQ_FUNC_0 : 8;
} _c_DIAG_FUNC_REQ_RDS_msgType;

typedef struct _c_VCU_3ACh_RDS_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 6;
  vbittype VCU_IGN4_STS : 1;
  vbittype VCU_IGN3_STS : 1;
} _c_VCU_3ACh_RDS_msgType;

typedef struct _c_VCU_245h_RDS_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 6;
  vbittype VCU_Ready : 2;
} _c_VCU_245h_RDS_msgType;

typedef struct _c_VCU_1D2h_RDS_msgTypeTag
{
  vbittype VCU_CMD_LDC_TARGT_VOLT : 8;
  vbittype unused0 : 3;
  vbittype VCU_CMD_EN_LDC : 1;
  vbittype unused1 : 4;
} _c_VCU_1D2h_RDS_msgType;

typedef struct _c_LDC_3A1h_RDS_msgTypeTag
{
  vbittype LDC_STS_VOLT_IN_1 : 8;
  vbittype LDC_STS_VOLT_IN_0 : 8;
  vbittype LDC_STS_VOLT_OUT : 8;
  vbittype LDC_STS_CURR_IN : 8;
  vbittype LDC_STS_CURR_OUT_1 : 8;
  vbittype LDC_STS_CURR_OUT_0 : 8;
  vbittype unused0 : 8;
  vbittype unused1 : 8;
} _c_LDC_3A1h_RDS_msgType;

typedef struct _c_LDC_3A0h_RDS_msgTypeTag
{
  vbittype LDC_Out_Mode : 2;
  vbittype unused0 : 1;
  vbittype LDC_STS_MODE : 3;
  vbittype LDC_STS_Ready : 2;
  vbittype unused1 : 3;
  vbittype LDC_Service_WRN_IND : 1;
  vbittype unused2 : 1;
  vbittype LDC_Out_Emergency : 1;
  vbittype unused3 : 2;
  vbittype LDC_STS_Power_OUT_1 : 8;
  vbittype LDC_STS_Power_OUT_0 : 8;
  vbittype LDC_STS_TEMP : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 4;
  vbittype Counter_3A0h : 4;
  vbittype Checksum_3A0h : 8;
} _c_LDC_3A0h_RDS_msgType;

typedef struct _c_LDC_DGN_RESP_RDS_msgTypeTag
{
  vbittype DGN_RESP_LDC_7 : 8;
  vbittype DGN_RESP_LDC_6 : 8;
  vbittype DGN_RESP_LDC_5 : 8;
  vbittype DGN_RESP_LDC_4 : 8;
  vbittype DGN_RESP_LDC_3 : 8;
  vbittype DGN_RESP_LDC_2 : 8;
  vbittype DGN_RESP_LDC_1 : 8;
  vbittype DGN_RESP_LDC_0 : 8;
} _c_LDC_DGN_RESP_RDS_msgType;

typedef struct _c_LDC_PCAN_STS_RDS_msgTypeTag
{
  vbittype CMXVersion_LDC_PCAN_1 : 8;
  vbittype CMXVersion_LDC_PCAN_0 : 8;
  vbittype unused0 : 6;
  vbittype DTCInfo_LDC_PCAN : 2;
  vbittype SupplyVoltage_LDC_PCAN : 8;
  vbittype RxErrCnt_LDC_PCAN : 8;
  vbittype TxErrCnt_LDC_PCAN : 8;
  vbittype BusOffCnt_LDC_PCAN : 8;
  vbittype MsgAliveCnt_LDC_PCAN : 8;
} _c_LDC_PCAN_STS_RDS_msgType;

typedef union _c_RDS0_bufTag
{
  vuint8 _c[8];
  _c_LDC_DGN_REQ_RDS_msgType LDC_DGN_REQ;
} _c_RDS0_buf;
typedef union _c_RDS1_bufTag
{
  vuint8 _c[8];
  _c_DIAG_FUNC_REQ_RDS_msgType DIAG_FUNC_REQ;
} _c_RDS1_buf;
typedef union _c_RDS2_bufTag
{
  vuint8 _c[2];
  _c_VCU_3ACh_RDS_msgType VCU_3ACh;
} _c_RDS2_buf;
typedef union _c_RDS3_bufTag
{
  vuint8 _c[4];
  _c_VCU_245h_RDS_msgType VCU_245h;
} _c_RDS3_buf;
typedef union _c_RDSBasic_bufTag
{
  vuint8 _c[2];
  _c_VCU_1D2h_RDS_msgType VCU_1D2h;
} _c_RDSBasic_buf;
typedef union _c_RDS_Tx_bufTag
{
  vuint8 _c[8];
  _c_LDC_3A1h_RDS_msgType LDC_3A1h;
  _c_LDC_3A0h_RDS_msgType LDC_3A0h;
  _c_LDC_DGN_RESP_RDS_msgType LDC_DGN_RESP;
  _c_LDC_PCAN_STS_RDS_msgType LDC_PCAN_STS;
} _c_RDS_Tx_buf;


#define RDS0                                 ((* ((_c_RDS0_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDS1                                 ((* ((_c_RDS1_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDS2                                 ((* ((_c_RDS2_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDS3                                 ((* ((_c_RDS3_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDSBasic                             ((* ((_c_RDSBasic_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))
#define RDSTx                                ((* ((_c_RDS_Tx_buf MEMORY_NORMAL *)(canRDSTxPtr[0]))))



/* -----------------------------------------------------------------------------
    &&&~ Message Hardware Objects
 ----------------------------------------------------------------------------- */

#define CanRxLDC_DGN_REQ_HW_OBJ              0
#define CanRxLDC_DGN_REQ_HW_CHANNEL          0
#define CanRxDIAG_FUNC_REQ_HW_OBJ            1
#define CanRxDIAG_FUNC_REQ_HW_CHANNEL        0
#define CanRxVCU_3ACh_HW_OBJ                 2
#define CanRxVCU_3ACh_HW_CHANNEL             0
#define CanRxVCU_245h_HW_OBJ                 3
#define CanRxVCU_245h_HW_CHANNEL             0
#define C_BASIC0_HW_OBJ                      4
#define C_BASIC0_HW_CHANNEL                  0
#define C_BASIC1_HW_OBJ                      5
#define C_BASIC1_HW_CHANNEL                  0
#define C_TX_NORMAL_HW_OBJ                   31
#define C_TX_NORMAL_HW_CHANNEL               0






/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 345877849
      #error "The magic number of the generated file <D:\07_Working\E100\source\BSW\CANbedded_Vector\can_par.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 345877849
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __CAN_PAR_H__ */
