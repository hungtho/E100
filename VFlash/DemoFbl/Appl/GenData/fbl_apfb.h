/* -----------------------------------------------------------------------------
  Filename:    fbl_apfb.h
  Description: Toolversion: 01.03.00.01.80.07.72.00.00.00
               
               Serial Number: CBD1800772
               Customer Info: Young Hwa Tech Co, Ltd, 
                              Package: FBL Symc SLP2 - ECU Product for SYMC
                              Micro: SPC570S50E1CEFAY
                              Compiler: Green Hills 2017.5.4
               
               
               Generator Fwk   : GENy 
               Generator Module: GenTool_GenyFblCanBase
               
               Configuration   : C:\Vector\CBD1800772_D00_Mpc57xx\Demo\DemoFbl\Config\DemoFbl.gny
               
               ECU: 
                       TargetSystem: Hw_Mpc5700Cpu
                       Compiler:     GHS
                       Derivates:    SPC570S50
               
               Channel "Channel0":
                       Databasefile: D:\usr\usage\Delivery\CBD18x\CBD1800772\D00\external\Demo\DemoFbl\Config\DemoFBL_Symc_SLP2.dbc
                       Bussystem:    CAN
                       Manufacturer: Vector
                       Node:         Demo

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

#if !defined(__FBL_APFB_H__)
#define __FBL_APFB_H__

/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

/* Defines ******************************************************************* */
#define kMioDeviceFlash_XD1                  0
#define kMioDeviceFlash                      1

/* Typedefs ****************************************************************** */
typedef struct tFlashBlockTag
{
  tFblAddress begin;
  tFblAddress end;
  vuint8 device;
} tFlashBlock;

/* Global data *************************************************************** */
#define FBL_FBT_START_SEC_CONST
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
V_MEMROM0 extern  V_MEMROM1_FAR tFlashBlock V_MEMROM2_FAR FlashBlock[12];
V_MEMROM0 extern  V_MEMROM1_FAR vuint8 V_MEMROM2_FAR kNrOfFlashBlock;

V_MEMROM0 extern  V_MEMROM1_FAR tMemDrv V_MEMROM2_FAR memDrvLst[2];
V_MEMROM0 extern  V_MEMROM1_FAR vuint8 V_MEMROM2_FAR kNrOfMemDrv;
#define FBL_FBT_STOP_SEC_CONST
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 312540478
      #error "The magic number of the generated file <C:\Vector\CBD1800772_D00_Mpc57xx\Demo\DemoFbl\Appl\GenData\fbl_apfb.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 312540478
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __FBL_APFB_H__ */
