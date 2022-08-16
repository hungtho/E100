/* -----------------------------------------------------------------------------
  Filename:    v_par.c
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

/* -----------------------------------------------------------------------------
    &&&~ BaseEnv_PSF_Includes
 ----------------------------------------------------------------------------- */

#include "v_inc.h"
#include "can_inc.h"



/* -----------------------------------------------------------------------------
    &&&~ GENy Version Information
 ----------------------------------------------------------------------------- */

/* ROM CATEGORY 4 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kGENyVersion[kGENyVersionNumberOfBytes] = 
{
  VGEN_DELIVERY_VERSION_BYTE_0, 
  VGEN_DELIVERY_VERSION_BYTE_1, 
  VGEN_DELIVERY_VERSION_BYTE_2, 
  VGEN_DELIVERY_VERSION_BYTE_3, 
  VGEN_DELIVERY_VERSION_BYTE_4, 
  VGEN_DELIVERY_VERSION_BYTE_5, 
  VGEN_DELIVERY_VERSION_BYTE_6, 
  VGEN_DELIVERY_VERSION_BYTE_7, 
  VGEN_DELIVERY_VERSION_BYTE_8, 
  VGEN_DELIVERY_VERSION_BYTE_9
};
/* ROM CATEGORY 4 END */



/* ROM CATEGORY 4 START */
V_MEMROM0 V_MEMROM1 tDBCVersion V_MEMROM2 kDBCVersion[1] = 
{
  { 0x19, 0x5, 0x19, 0x10, 0x110 }
};
/* ROM CATEGORY 4 END */


/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 345877849
      #error "The magic number of the generated file <D:\07_Working\E100\source\BSW\CANbedded_Vector\v_par.c> is different. Please check time and date of generated files!"
  #endif
#else
  #error "The magic number is not defined in the generated file <D:\07_Working\E100\source\BSW\CANbedded_Vector\v_par.c> "

#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

