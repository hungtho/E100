/* -----------------------------------------------------------------------------
  Filename:    fbl_apfb.c
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

#define FBL_FBT_SOURCE

/* Includes ****************************************************************** */
#include "fbl_inc.h"

/* Global data *************************************************************** */
#define FBL_FBT_START_SEC_CONST
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
V_MEMROM0 V_MEMROM1_FAR tFlashBlock V_MEMROM2_FAR FlashBlock[12] = 
{
  
  {
    0x800000u /* 8 KB - Data Block 0 */, 
    0x801FFFu, 
    kMioDeviceFlash_XD1
  }, 
  
  {
    0x802000u /* 8 KB - Data Block 1 */, 
    0x803FFFu, 
    kMioDeviceFlash_XD1
  }, 
  
  {
    0x804000u /* 8 KB - Data Block 2 */, 
    0x805FFFu, 
    kMioDeviceFlash_XD1
  }, 
  
  {
    0x806000u /* 8 KB - Data Block 3 */, 
    0x807FFFu, 
    kMioDeviceFlash_XD1
  }, 
  
  {
    0xFC8000u /* 16 KB - Code Block 2 (boot location 2) */, 
    0xFCBFFFu, 
    kMioDeviceFlash
  }, 
  
  {
    0xFCC000u /* 16 KB - Code Block 3 (boot location 3) */, 
    0xFCFFFFu, 
    kMioDeviceFlash
  }, 
  
  {
    0xFD0000u /* 32 KB - Code Block 0 */, 
    0xFD7FFFu, 
    kMioDeviceFlash
  }, 
  
  {
    0xFD8000u /* 32 KB - Code Block 1 */, 
    0xFDFFFFu, 
    kMioDeviceFlash
  }, 
  
  {
    0xFE0000u /* 64 KB - Code Block 0 */, 
    0xFEFFFFu, 
    kMioDeviceFlash
  }, 
  
  {
    0xFF0000u /* 64 KB - Code Block 1 */, 
    0xFFFFFFu, 
    kMioDeviceFlash
  }, 
  
  {
    0x01000000u /* 128 KB - Code Block 0 (boot location 4) */, 
    0x0101FFFFu, 
    kMioDeviceFlash
  }, 
  
  {
    0x01020000u /* 128 KB - Code Block 1 (boot location 5) */, 
    0x0103FFFFu, 
    kMioDeviceFlash
  }
};
V_MEMROM0 V_MEMROM1_FAR vuint8 V_MEMROM2_FAR kNrOfFlashBlock = sizeof(FlashBlock) / sizeof(FlashBlock[0]);

V_MEMROM0 V_MEMROM1_FAR tMemDrv V_MEMROM2_FAR memDrvLst[2] = 
{
  
  {
    Flash_XD1Driver_InitSync, 
    Flash_XD1Driver_DeinitSync, 
    Flash_XD1Driver_REraseSync, 
    Flash_XD1Driver_RWriteSync, 
    Flash_XD1Driver_RReadSync, 
    8
  }, 
  
  {
    FlashDriver_InitSync, 
    FlashDriver_DeinitSync, 
    FlashDriver_REraseSync, 
    FlashDriver_RWriteSync, 
    FlashDriver_RReadSync, 
    FLASH_SEGMENT_SIZE
  }
};
V_MEMROM0 V_MEMROM1_FAR vuint8 V_MEMROM2_FAR kNrOfMemDrv = sizeof(memDrvLst) / sizeof(memDrvLst[0]);
#define FBL_FBT_STOP_SEC_CONST
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Try to check consistency between memory device driver */
/* header files (e.g. flashdrv.h) and GENy configuration */
#ifdef FLASH_XD1_SEGMENT_SIZE
#if (FLASH_XD1_SEGMENT_SIZE != 8)
# error "Consistency check failed! Adjust GENy configuration!"
#endif

#endif

#ifdef FBL_FLASH_XD1_DELETED
#if (FBL_FLASH_XD1_DELETED != 0xFFu)
# error "Consistency check failed! Adjust GENy configuration!"
#endif

#endif

#ifdef FLASH_SEGMENT_SIZE
#if (FLASH_SEGMENT_SIZE != 8)
# error "Consistency check failed! Adjust GENy configuration!"
#endif

#endif

#ifdef FBL_FLASH_DELETED
#if (FBL_FLASH_DELETED != 0xFFu)
# error "Consistency check failed! Adjust GENy configuration!"
#endif

#endif



/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 312540478
      #error "The magic number of the generated file <C:\Vector\CBD1800772_D00_Mpc57xx\Demo\DemoFbl\Appl\GenData\fbl_apfb.c> is different. Please check time and date of generated files!"
  #endif
#else
  #error "The magic number is not defined in the generated file <C:\Vector\CBD1800772_D00_Mpc57xx\Demo\DemoFbl\Appl\GenData\fbl_apfb.c> "

#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

