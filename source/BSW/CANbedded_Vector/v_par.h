/* -----------------------------------------------------------------------------
  Filename:    v_par.h
  Description: Toolversion: 01.02.12.01.80.07.77.00.00.00
               
               Serial Number: CBD1800777
               Customer Info: Young Hwa Tech Co, Ltd, 
                              Package: CBD Symc SLP1 - in projects for SsangYong 
                              Micro: SPC570S50E1CEFAY
                              Compiler: Green Hills 2017.5.4
               
               
               Generator Fwk   : GENy 
               Generator Module: GenTool_GenyVcfgNameDecorator
               
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

#if !defined(__V_PAR_H__)
#define __V_PAR_H__

/* -----------------------------------------------------------------------------
    &&&~ BaseEnv_PHF_Includes
 ----------------------------------------------------------------------------- */

#include "v_cfg.h"
#include "v_def.h"


/* -----------------------------------------------------------------------------
    &&&~ GENy Version Information
 ----------------------------------------------------------------------------- */

#define VGEN_DELIVERY_VERSION_BYTE_0         0x01
#define VGEN_DELIVERY_VERSION_BYTE_1         0x02
#define VGEN_DELIVERY_VERSION_BYTE_2         0x12
#define VGEN_DELIVERY_VERSION_BYTE_3         0x01
#define VGEN_DELIVERY_VERSION_BYTE_4         0x80
#define VGEN_DELIVERY_VERSION_BYTE_5         0x07
#define VGEN_DELIVERY_VERSION_BYTE_6         0x77
#define VGEN_DELIVERY_VERSION_BYTE_7         0x00
#define VGEN_DELIVERY_VERSION_BYTE_8         0x00
#define VGEN_DELIVERY_VERSION_BYTE_9         0x00
#define kGENyVersionNumberOfBytes            10
/* ROM CATEGORY 4 START */
V_MEMROM0 extern  V_MEMROM1 vuint8 V_MEMROM2 kGENyVersion[kGENyVersionNumberOfBytes];
/* ROM CATEGORY 4 END */



typedef struct tDBCVersionTag
{
  vuint8 kYear;
  vuint8 kMonth;
  vuint8 kWeek;
  vuint8 kDay;
  vuint32 kNumber;
} tDBCVersion;
V_MEMROM0 extern  V_MEMROM1 tDBCVersion V_MEMROM2 kDBCVersion[1];

/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 345877849
      #error "The magic number of the generated file <D:\07_Working\E100\source\BSW\CANbedded_Vector\v_par.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 345877849
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __V_PAR_H__ */
