/* -----------------------------------------------------------------------------
  Filename:    drv_par.c
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

#include "v_inc.h"
#include "can_inc.h"

#include "drv_par.h"
/* -----------------------------------------------------------------------------
    &&&~ Message Buffers
 ----------------------------------------------------------------------------- */

/* RAM CATEGORY 2 START */
/* PRQA  S 0759 QAC_Can_0759 */ /* MD_Can_0759 */
V_MEMRAM0 V_MEMRAM1 _c_VCU_245h_buf V_MEMRAM2 VCU_245h;
V_MEMRAM0 V_MEMRAM1 _c_LDC_3A1h_buf V_MEMRAM2 LDC_3A1h;
V_MEMRAM0 V_MEMRAM1 _c_LDC_3A0h_buf V_MEMRAM2 LDC_3A0h;
V_MEMRAM0 V_MEMRAM1 _c_VCU_3ACh_buf V_MEMRAM2 VCU_3ACh;
V_MEMRAM0 V_MEMRAM1 _c_VCU_1D2h_buf V_MEMRAM2 VCU_1D2h;
V_MEMRAM0 V_MEMRAM1 _c_LDC_DGN_RESP_buf V_MEMRAM2 LDC_DGN_RESP;
V_MEMRAM0 V_MEMRAM1 _c_LDC_PCAN_STS_buf V_MEMRAM2 LDC_PCAN_STS;
/* PRQA  L:QAC_Can_0759 */

/* RAM CATEGORY 2 END */





/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 345877849
      #error "The magic number of the generated file <D:\07_Working\E100\source\BSW\CANbedded_Vector\drv_par.c> is different. Please check time and date of generated files!"
  #endif
#else
  #error "The magic number is not defined in the generated file <D:\07_Working\E100\source\BSW\CANbedded_Vector\drv_par.c> "

#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

