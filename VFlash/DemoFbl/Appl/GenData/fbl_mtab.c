/* -----------------------------------------------------------------------------
  Filename:    fbl_mtab.c
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

/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

#define FBL_LBT_SOURCE

/* Includes ****************************************************************** */
#include "fbl_inc.h"

/* Global data *************************************************************** */
#define FBL_LBT_START_SEC_CONST
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
V_MEMROM0 V_MEMROM1 tLogicalBlockTable V_MEMROM2 FblLogicalBlockTable = 
{
  FBL_MTAB_MAGIC_FLAG, 
  
  {
    0x1
  } /* Disposability bit field (mandatory/optional) */, 
  FBL_MTAB_NO_OF_BLOCKS, 
  
  {
    
    {
      0, 
      kBlockTypeCode /* Block Type */, 
      0xFC8000u /* Block Start Address */, 
      0x010000u /* Block Length (End Address = 0xFD7FFF) */, 
      0x00 /* Max Prog Attempts */, 
      (tExportFct)SecM_Verification /* Output Verification */
    } /* Name 'DemoAppl', Mandatory */, 
    
    {
      1, 
      kBlockTypeCode /* Block Type */, 
      0x800000u /* Block Start Address */, 
      0x8000u /* Block Length (End Address = 0x807FFF) */, 
      0x00 /* Max Prog Attempts */, 
      (tExportFct)SecM_Verification /* Output Verification */
    } /* Name 'CAL1', Optional */
  }
};
#define FBL_LBT_STOP_SEC_CONST
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 312540478
      #error "The magic number of the generated file <C:\Vector\CBD1800772_D00_Mpc57xx\Demo\DemoFbl\Appl\GenData\fbl_mtab.c> is different. Please check time and date of generated files!"
  #endif
#else
  #error "The magic number is not defined in the generated file <C:\Vector\CBD1800772_D00_Mpc57xx\Demo\DemoFbl\Appl\GenData\fbl_mtab.c> "

#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

