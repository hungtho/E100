/* -----------------------------------------------------------------------------
  Filename:    fbl_mtab.h
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

#if !defined(__FBL_MTAB_H__)
#define __FBL_MTAB_H__

/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

/* Defines ******************************************************************* */

#define FBL_MTAB_DEMOAPPL_BLOCK_NUMBER       0
#define FBL_MTAB_CAL1_BLOCK_NUMBER           1
#define kBlockTypeCode                       0x9Au
#define kBlockTypeData                       0x9Bu

/* Formula to compute kNrOfValidationBytes is (((FBL_MTAB_NO_OF_BLOCKS-1)/8)+1) */
#define kNrOfValidationBytes                 1

/* Macro to determine if the block table is valid */
#define FBL_MTAB_MAGIC_FLAG                  0xB5A4C3D2u
#define IsLogicalBlockTableValid()           (FblLogicalBlockTable.magicFlag == FBL_MTAB_MAGIC_FLAG)

/* Compatibility defines */
#define verifyRAM                            verifyInput
#define verifyROM                            verifyOutput

/* Typedefs ****************************************************************** */

/* Entry type of logical block table */
typedef struct tBlockDescriptorTag
{
  vuint8 blockNr; /* Number of logical block */
  vuint32 blockType;
  tFblAddress blockStartAddress; /* Start address of current block */
  tFblLength blockLength; /* Block length in bytes */
  vuint16 maxProgAttempts; /* Maximum number of reprogramming attempts */
  tExportFct verifyOutput;
} tBlockDescriptor;

/* The logical block table describes the memory layout of logical blocks */
typedef struct tLogicalBlockTableTag
{
  vuint32 magicFlag; /* Value of FBL_MTAB_MAGIC_FLAG - Indicates the existence of the table */
  vuint8 assignFlags[kNrOfValidationBytes]; /* Disposability bit field (mandatory/optional) */
  vuint8 noOfBlocks; /* Number of configured logical blocks */
  tBlockDescriptor logicalBlock[FBL_MTAB_NO_OF_BLOCKS];
} tLogicalBlockTable;

/* Global data *************************************************************** */
#define FBL_LBT_START_SEC_CONST
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
V_MEMROM0 extern  V_MEMROM1 tLogicalBlockTable V_MEMROM2 FblLogicalBlockTable;
#define FBL_LBT_STOP_SEC_CONST
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 312540478
      #error "The magic number of the generated file <C:\Vector\CBD1800772_D00_Mpc57xx\Demo\DemoFbl\Appl\GenData\fbl_mtab.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 312540478
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __FBL_MTAB_H__ */
