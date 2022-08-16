/* -----------------------------------------------------------------------------
  Filename:    drv_par.h
  Description: Toolversion: 01.02.12.01.80.07.77.00.00.00
               
               Serial Number: CBD1800777
               Customer Info: Young Hwa Tech Co, Ltd, 
                              Package: CBD Symc SLP1 - in projects for SsangYong 
                              Micro: SPC570S50E1CEFAY
                              Compiler: Green Hills 2017.5.4
               
               
               Generator Fwk   : GENy 
               Generator Module: GenTool_GenyDriverBase
               
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

#if !defined(__DRV_PAR_H__)
#define __DRV_PAR_H__

/* -----------------------------------------------------------------------------
    &&&~ Signal Structures
 ----------------------------------------------------------------------------- */

typedef struct _c_VCU_245h_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 6;
  vbittype VCU_Ready : 2;
} _c_VCU_245h_msgType;
typedef struct _c_LDC_3A1h_msgTypeTag
{
  vbittype LDC_STS_VOLT_IN_1 : 8;
  vbittype LDC_STS_VOLT_IN_0 : 8;
  vbittype LDC_STS_VOLT_OUT : 8;
  vbittype LDC_STS_CURR_IN : 8;
  vbittype LDC_STS_CURR_OUT_1 : 8;
  vbittype LDC_STS_CURR_OUT_0 : 8;
  vbittype unused0 : 8;
  vbittype unused1 : 8;
} _c_LDC_3A1h_msgType;
typedef struct _c_LDC_3A0h_msgTypeTag
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
} _c_LDC_3A0h_msgType;
typedef struct _c_VCU_3ACh_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 6;
  vbittype VCU_IGN4_STS : 1;
  vbittype VCU_IGN3_STS : 1;
} _c_VCU_3ACh_msgType;
typedef struct _c_VCU_1D2h_msgTypeTag
{
  vbittype VCU_CMD_LDC_TARGT_VOLT : 8;
  vbittype unused0 : 3;
  vbittype VCU_CMD_EN_LDC : 1;
  vbittype unused1 : 4;
} _c_VCU_1D2h_msgType;
typedef struct _c_LDC_DGN_RESP_msgTypeTag
{
  vbittype DGN_RESP_LDC_7 : 8;
  vbittype DGN_RESP_LDC_6 : 8;
  vbittype DGN_RESP_LDC_5 : 8;
  vbittype DGN_RESP_LDC_4 : 8;
  vbittype DGN_RESP_LDC_3 : 8;
  vbittype DGN_RESP_LDC_2 : 8;
  vbittype DGN_RESP_LDC_1 : 8;
  vbittype DGN_RESP_LDC_0 : 8;
} _c_LDC_DGN_RESP_msgType;
typedef struct _c_LDC_PCAN_STS_msgTypeTag
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
} _c_LDC_PCAN_STS_msgType;


/* -----------------------------------------------------------------------------
    &&&~ Signal value names
 ----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
    &&&~ Message Unions
 ----------------------------------------------------------------------------- */

typedef union _c_VCU_245h_bufTag
{
  vuint8 _c[4];
  _c_VCU_245h_msgType VCU_245h;
} _c_VCU_245h_buf;
typedef union _c_LDC_3A1h_bufTag
{
  vuint8 _c[8];
  _c_LDC_3A1h_msgType LDC_3A1h;
} _c_LDC_3A1h_buf;
typedef union _c_LDC_3A0h_bufTag
{
  vuint8 _c[8];
  _c_LDC_3A0h_msgType LDC_3A0h;
} _c_LDC_3A0h_buf;
typedef union _c_VCU_3ACh_bufTag
{
  vuint8 _c[2];
  _c_VCU_3ACh_msgType VCU_3ACh;
} _c_VCU_3ACh_buf;
typedef union _c_VCU_1D2h_bufTag
{
  vuint8 _c[2];
  _c_VCU_1D2h_msgType VCU_1D2h;
} _c_VCU_1D2h_buf;
typedef union _c_LDC_DGN_RESP_bufTag
{
  vuint8 _c[8];
  _c_LDC_DGN_RESP_msgType LDC_DGN_RESP;
} _c_LDC_DGN_RESP_buf;
typedef union _c_LDC_PCAN_STS_bufTag
{
  vuint8 _c[8];
  _c_LDC_PCAN_STS_msgType LDC_PCAN_STS;
} _c_LDC_PCAN_STS_buf;


/* -----------------------------------------------------------------------------
    &&&~ Message Buffers
 ----------------------------------------------------------------------------- */

/* RAM CATEGORY 2 START */
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_VCU_245h_buf V_MEMRAM2 VCU_245h;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_LDC_3A1h_buf V_MEMRAM2 LDC_3A1h;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_LDC_3A0h_buf V_MEMRAM2 LDC_3A0h;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_VCU_3ACh_buf V_MEMRAM2 VCU_3ACh;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_VCU_1D2h_buf V_MEMRAM2 VCU_1D2h;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_LDC_DGN_RESP_buf V_MEMRAM2 LDC_DGN_RESP;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_LDC_PCAN_STS_buf V_MEMRAM2 LDC_PCAN_STS;
/* RAM CATEGORY 2 END */






/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 345877849
      #error "The magic number of the generated file <D:\07_Working\E100\source\BSW\CANbedded_Vector\drv_par.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 345877849
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __DRV_PAR_H__ */
