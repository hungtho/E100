/* -----------------------------------------------------------------------------
  Filename:    WrapNv_cfg.c
  Description: Toolversion: 01.03.00.01.80.07.72.00.00.00
               
               Serial Number: CBD1800772
               Customer Info: Young Hwa Tech Co, Ltd, 
                              Package: FBL Symc SLP2 - ECU Product for SYMC
                              Micro: SPC570S50E1CEFAY
                              Compiler: Green Hills 2017.5.4
               
               
               Generator Fwk   : GENy 
               Generator Module: SysService_WrapperNv
               
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

#include "WrapNv_inc.h"
#ifdef FBL_ENABLE_EEPMGR
#else
#ifdef NV_ENABLE_ADDRESS_LOOKUP
V_MEMROM0 V_MEMROM1_FAR tNvRecordTbl V_MEMROM2_FAR kNvRecordTbl[] = 
{
  
  {
    kEepMgrHandle_ProgReqFlag, 
    kNvAccessSingle, 
    kEepAddressProgReqFlag, 
    kEepSizeProgReqFlag
  }, 
  
  {
    kEepMgrHandle_ResetResponseFlag, 
    kNvAccessSingle, 
    kEepAddressResetResponseFlag, 
    kEepSizeResetResponseFlag
  }, 
  
  {
    kEepMgrHandle_ApplValidity, 
    kNvAccessSingle, 
    kEepAddressApplValidity, 
    kEepSizeApplValidity
  }, 
  
  {
    kEepMgrHandle_ValidityFlags, 
    kNvAccessSingle, 
    kEepAddressValidityFlags, 
    kEepSizeValidityFlags
  }, 
  
  {
    kEepMgrHandle_ProcessData + kEepMgrHandle_TesterSerialNumber, 
    kNvAccessStructured, 
    kEepAddressTesterSerialNumber, 
    kEepSizeTesterSerialNumber
  }, 
  
  {
    kEepMgrHandle_ProcessData + kEepMgrHandle_ProgrammingDate, 
    kNvAccessStructured, 
    kEepAddressProgrammingDate, 
    kEepSizeProgrammingDate
  }, 
  
  {
    kEepMgrHandle_ProcessData + kEepMgrHandle_SymcPartNumber, 
    kNvAccessStructured, 
    kEepAddressSymcPartNumber, 
    kEepSizeSymcPartNumber
  }, 
  
  {
    kEepMgrHandle_ProcessData + kEepMgrHandle_SymcSoftwareVersion, 
    kNvAccessStructured, 
    kEepAddressSymcSoftwareVersion, 
    kEepSizeSymcSoftwareVersion
  }, 
  
  {
    kEepMgrHandle_ProcessData + kEepMgrHandle_SystemSupplierCode, 
    kNvAccessStructured, 
    kEepAddressSystemSupplierCode, 
    kEepSizeSystemSupplierCode
  }, 
  
  {
    kEepMgrHandle_Metadata + kEepMgrHandle_ProgCounter, 
    kNvAccessStructured, 
    kEepAddressProgCounter, 
    kEepSizeProgCounter
  }, 
  
  {
    kEepMgrHandle_Metadata + kEepMgrHandle_ProgAttempts, 
    kNvAccessStructured, 
    kEepAddressProgAttempts, 
    kEepSizeProgAttempts
  }, 
  
  {
    kEepMgrHandle_Metadata + kEepMgrHandle_CRCValue, 
    kNvAccessStructured, 
    kEepAddressCRCValue, 
    kEepSizeCRCValue
  }, 
  
  {
    kEepMgrHandle_Metadata + kEepMgrHandle_CRCStart, 
    kNvAccessStructured, 
    kEepAddressCRCStart, 
    kEepSizeCRCStart
  }, 
  
  {
    kEepMgrHandle_Metadata + kEepMgrHandle_CRCLength, 
    kNvAccessStructured, 
    kEepAddressCRCLength, 
    kEepSizeCRCLength
  }
};
V_MEMROM0 V_MEMROM1_FAR vuint8 V_MEMROM2_FAR kNvNoOfNvRecords = sizeof(kNvRecordTbl) / sizeof(kNvRecordTbl[0]);
#endif

#endif


/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 312540478
      #error "The magic number of the generated file <C:\Vector\CBD1800772_D00_Mpc57xx\Demo\DemoFbl\Appl\GenData\WrapNv_cfg.c> is different. Please check time and date of generated files!"
  #endif
#else
  #error "The magic number is not defined in the generated file <C:\Vector\CBD1800772_D00_Mpc57xx\Demo\DemoFbl\Appl\GenData\WrapNv_cfg.c> "

#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

