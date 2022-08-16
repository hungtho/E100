/* -----------------------------------------------------------------------------
  Filename:    WrapNv_cfg.h
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

#if !defined(__WRAPNV_CFG_H__)
#define __WRAPNV_CFG_H__

#ifdef FBL_ENABLE_EEPMGR
#else
#define NV_ENABLE_ADDRESS_LOOKUP
#endif


/*
*                                 ADDRESS        HANDLE         DESCRIPTION
*
*   Memory Layout
*   |
*   +-- ProgReqFlag               0x40008b00     1              Programming request flag
*   |
*   +-- ResetResponseFlag         0x40008b01     2              Reset response flag
*   |
*   +-- ApplValidity              0x40008b02     3              Application validity flag
*   |
*   +-- ValidityFlags             0x40008b03     4              Logical block validity flags
*   |
*   +-- ProcessData
*   |   |
*   |   +-- TesterSerialNumber    0x40008b04     5              Rerpair Shop Code or Tester Serial Number (BCD)
*   |   |
*   |   +-- ProgrammingDate       0x40008b0c     6              Programming Date (BCD)
*   |   |
*   |   +-- SymcPartNumber        0x40008b0f     7              SYMC Part Number (ASCII)
*   |   |
*   |   +-- SymcSoftwareVersion   0x40008b19     8              SYMC Software Version (ASCII)
*   |   |
*   |   +-- SystemSupplierCode    0x40008b1b     9              System Supplier Code (ASCII)
*   |
*   +-- 3 x Metadata                                            Internal meta data (for each logical block)
*       |
*       +-- ProgCounter           0x40008b20     10             Successful reprogramming attempts
*       |
*       +-- ProgAttempts          0x40008b22     11             Reprogramming attempts
*       |
*       +-- CRCValue              0x40008b24     12             CRC total of logical block
*       |
*       +-- CRCStart              0x40008b28     13             Start address of CRC total
*       |
*       +-- CRCLength             0x40008b2c     14             Length of CRC total
*/

/* Size defines ************************************************************** */
#define kEepSizeProgReqFlag                  0x01u
#define kEepSizeResetResponseFlag            0x01u
#define kEepSizeApplValidity                 0x01u
#define kEepSizeValidityFlags                0x01u
#define kEepSizeTesterSerialNumber           0x08u
#define kEepSizeProgrammingDate              0x03u
#define kEepSizeSymcPartNumber               0x0Au
#define kEepSizeSymcSoftwareVersion          0x02u
#define kEepSizeSystemSupplierCode           0x05u
#define kEepSizeProcessData                  (kEepSizeTesterSerialNumber + kEepSizeProgrammingDate + kEepSizeSymcPartNumber + kEepSizeSymcSoftwareVersion + kEepSizeSystemSupplierCode)
#define kEepSizeProgCounter                  0x02u
#define kEepSizeProgAttempts                 0x02u
#define kEepSizeCRCValue                     0x04u
#define kEepSizeCRCStart                     0x04u
#define kEepSizeCRCLength                    0x04u
#define kEepSizeMetadata                     (kEepSizeProgCounter + kEepSizeProgAttempts + kEepSizeCRCValue + kEepSizeCRCStart + kEepSizeCRCLength)
/* Address defines *********************************************************** */
#ifdef FBL_ENABLE_EEPMGR
#else
#define kEepFblBaseAddress                   0x40008B00u
#define kEepStartAddress                     kEepFblBaseAddress
#define kEepAddressProgReqFlag               kEepStartAddress
#define kEepAddressResetResponseFlag         (kEepAddressProgReqFlag + kEepSizeProgReqFlag)
#define kEepAddressApplValidity              (kEepAddressResetResponseFlag + kEepSizeResetResponseFlag)
#define kEepAddressValidityFlags             (kEepAddressApplValidity + kEepSizeApplValidity)
#define kEepAddressProcessData               (kEepAddressValidityFlags + kEepSizeValidityFlags)
#define kEepAddressTesterSerialNumber        kEepAddressProcessData
#define kEepAddressProgrammingDate           (kEepAddressTesterSerialNumber + kEepSizeTesterSerialNumber)
#define kEepAddressSymcPartNumber            (kEepAddressProgrammingDate + kEepSizeProgrammingDate)
#define kEepAddressSymcSoftwareVersion       (kEepAddressSymcPartNumber + kEepSizeSymcPartNumber)
#define kEepAddressSystemSupplierCode        (kEepAddressSymcSoftwareVersion + kEepSizeSymcSoftwareVersion)
#define kEepAddressMetadata                  (kEepAddressProcessData + kEepSizeProcessData)
#define kEepAddressProgCounter               kEepAddressMetadata
#define kEepAddressProgAttempts              (kEepAddressProgCounter + kEepSizeProgCounter)
#define kEepAddressCRCValue                  (kEepAddressProgAttempts + kEepSizeProgAttempts)
#define kEepAddressCRCStart                  (kEepAddressCRCValue + kEepSizeCRCValue)
#define kEepAddressCRCLength                 (kEepAddressCRCStart + kEepSizeCRCStart)
#define kEepEndAddress                       (kEepAddressMetadata + kEepSizeMetadata * 3 - 1)
#define kEepSizeOfEeprom                     (kEepEndAddress - kEepStartAddress + 1)
/* Initialize NvStructSize-Array */
#define kNvNoOfStructs                       0x02u
#define kNvSizeStructs                       {kEepSizeProcessData, kEepSizeMetadata}
#endif

/* Handle defines ************************************************************ */
#define kEepMgrFirstHandle                   1
#define kEepMgrHandle_ProgReqFlag            kEepMgrFirstHandle
#define kEepMgrHandle_ResetResponseFlag      (kEepMgrHandle_ProgReqFlag + 1)
#define kEepMgrHandle_ApplValidity           (kEepMgrHandle_ResetResponseFlag + 1)
#define kEepMgrHandle_ValidityFlags          (kEepMgrHandle_ApplValidity + 1)
#define kNvHandleStruct0                     0x00u
#define kEepMgrHandle_ProcessData            (NV_MK_STRUCT_ID(kNvHandleStruct0, kEepMgrHandle_ValidityFlags + 1))
#define kEepMgrHandle_TesterSerialNumber     0
#define kEepMgrHandle_ProgrammingDate        (kEepMgrHandle_TesterSerialNumber + 1)
#define kEepMgrHandle_SymcPartNumber         (kEepMgrHandle_ProgrammingDate + 1)
#define kEepMgrHandle_SymcSoftwareVersion    (kEepMgrHandle_SymcPartNumber + 1)
#define kEepMgrHandle_SystemSupplierCode     (kEepMgrHandle_SymcSoftwareVersion + 1)
#define kEepMgrNrOfProcessDataHdls           (kEepMgrHandle_SystemSupplierCode + 1)
#define kNvHandleStruct1                     0x01u
#define kEepMgrHandle_Metadata               (NV_MK_STRUCT_ID(kNvHandleStruct1, NV_GET_STRUCT_ID(kEepMgrHandle_ProcessData) + kEepMgrNrOfProcessDataHdls))
#define kEepMgrHandle_ProgCounter            0
#define kEepMgrHandle_ProgAttempts           (kEepMgrHandle_ProgCounter + 1)
#define kEepMgrHandle_CRCValue               (kEepMgrHandle_ProgAttempts + 1)
#define kEepMgrHandle_CRCStart               (kEepMgrHandle_CRCValue + 1)
#define kEepMgrHandle_CRCLength              (kEepMgrHandle_CRCStart + 1)
#define kEepMgrNrOfMetadataHdls              (kEepMgrHandle_CRCLength + 1)
#define kEepMgrLastHandle                    (NV_GET_STRUCT_ID(kEepMgrHandle_Metadata) + kEepMgrNrOfMetadataHdls * 3 - 1)
#define kEepMgrNumberOfHandles               (kEepMgrLastHandle - kEepMgrFirstHandle + 1)
#ifdef FBL_ENABLE_EEPMGR
/* Initialize NvStructSize-Array */
#define kNvNoOfStructs                       0x02u
#define kNvSizeStructs                       {kEepMgrNrOfProcessDataHdls, kEepMgrNrOfMetadataHdls}
#endif

/* Access macros ************************************************************* */
#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadProgReqFlag(buf)        ((EepMgrRead(kEepMgrHandle_ProgReqFlag, buf, kEepSizeProgReqFlag) == kEepSizeProgReqFlag) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgReqFlag(buf)       ((EepMgrWrite(kEepMgrHandle_ProgReqFlag, buf, kEepSizeProgReqFlag) == kEepMgrOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadProgReqFlag(buf)        ((EepromDriver_RReadSync(buf, kEepSizeProgReqFlag, kEepAddressProgReqFlag) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgReqFlag(buf)       ((EepromDriver_RWriteSync(buf, kEepSizeProgReqFlag, kEepAddressProgReqFlag) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadResetResponseFlag(buf)  ((EepMgrRead(kEepMgrHandle_ResetResponseFlag, buf, kEepSizeResetResponseFlag) == kEepSizeResetResponseFlag) ? kFblOk : kFblFailed)
#define ApplFblNvWriteResetResponseFlag(buf) ((EepMgrWrite(kEepMgrHandle_ResetResponseFlag, buf, kEepSizeResetResponseFlag) == kEepMgrOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadResetResponseFlag(buf)  ((EepromDriver_RReadSync(buf, kEepSizeResetResponseFlag, kEepAddressResetResponseFlag) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteResetResponseFlag(buf) ((EepromDriver_RWriteSync(buf, kEepSizeResetResponseFlag, kEepAddressResetResponseFlag) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadApplValidity(buf)       ((EepMgrRead(kEepMgrHandle_ApplValidity, buf, kEepSizeApplValidity) == kEepSizeApplValidity) ? kFblOk : kFblFailed)
#define ApplFblNvWriteApplValidity(buf)      ((EepMgrWrite(kEepMgrHandle_ApplValidity, buf, kEepSizeApplValidity) == kEepMgrOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadApplValidity(buf)       ((EepromDriver_RReadSync(buf, kEepSizeApplValidity, kEepAddressApplValidity) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteApplValidity(buf)      ((EepromDriver_RWriteSync(buf, kEepSizeApplValidity, kEepAddressApplValidity) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadValidityFlags(buf)      ((EepMgrRead(kEepMgrHandle_ValidityFlags, buf, kEepSizeValidityFlags) == kEepSizeValidityFlags) ? kFblOk : kFblFailed)
#define ApplFblNvWriteValidityFlags(buf)     ((EepMgrWrite(kEepMgrHandle_ValidityFlags, buf, kEepSizeValidityFlags) == kEepMgrOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadValidityFlags(buf)      ((EepromDriver_RReadSync(buf, kEepSizeValidityFlags, kEepAddressValidityFlags) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteValidityFlags(buf)     ((EepromDriver_RWriteSync(buf, kEepSizeValidityFlags, kEepAddressValidityFlags) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadTesterSerialNumber(idx, buf) ((EepMgrRead(NV_GET_STRUCT_ID(kEepMgrHandle_ProcessData) + kEepMgrHandle_TesterSerialNumber, buf, kEepSizeTesterSerialNumber) == kEepSizeTesterSerialNumber) ? kFblOk : kFblFailed)
#define ApplFblNvWriteTesterSerialNumber(idx, buf) ((EepMgrWrite(NV_GET_STRUCT_ID(kEepMgrHandle_ProcessData) + kEepMgrHandle_TesterSerialNumber, buf, kEepSizeTesterSerialNumber) == kEepMgrOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadTesterSerialNumber(idx, buf) ((EepromDriver_RReadSync(buf, kEepSizeTesterSerialNumber, kEepAddressTesterSerialNumber) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteTesterSerialNumber(idx, buf) ((EepromDriver_RWriteSync(buf, kEepSizeTesterSerialNumber, kEepAddressTesterSerialNumber) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadProgrammingDate(idx, buf) ((EepMgrRead(NV_GET_STRUCT_ID(kEepMgrHandle_ProcessData) + kEepMgrHandle_ProgrammingDate, buf, kEepSizeProgrammingDate) == kEepSizeProgrammingDate) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgrammingDate(idx, buf) ((EepMgrWrite(NV_GET_STRUCT_ID(kEepMgrHandle_ProcessData) + kEepMgrHandle_ProgrammingDate, buf, kEepSizeProgrammingDate) == kEepMgrOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadProgrammingDate(idx, buf) ((EepromDriver_RReadSync(buf, kEepSizeProgrammingDate, kEepAddressProgrammingDate) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgrammingDate(idx, buf) ((EepromDriver_RWriteSync(buf, kEepSizeProgrammingDate, kEepAddressProgrammingDate) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadSymcPartNumber(idx, buf) ((EepMgrRead(NV_GET_STRUCT_ID(kEepMgrHandle_ProcessData) + kEepMgrHandle_SymcPartNumber, buf, kEepSizeSymcPartNumber) == kEepSizeSymcPartNumber) ? kFblOk : kFblFailed)
#define ApplFblNvWriteSymcPartNumber(idx, buf) ((EepMgrWrite(NV_GET_STRUCT_ID(kEepMgrHandle_ProcessData) + kEepMgrHandle_SymcPartNumber, buf, kEepSizeSymcPartNumber) == kEepMgrOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadSymcPartNumber(idx, buf) ((EepromDriver_RReadSync(buf, kEepSizeSymcPartNumber, kEepAddressSymcPartNumber) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteSymcPartNumber(idx, buf) ((EepromDriver_RWriteSync(buf, kEepSizeSymcPartNumber, kEepAddressSymcPartNumber) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadSymcSoftwareVersion(idx, buf) ((EepMgrRead(NV_GET_STRUCT_ID(kEepMgrHandle_ProcessData) + kEepMgrHandle_SymcSoftwareVersion, buf, kEepSizeSymcSoftwareVersion) == kEepSizeSymcSoftwareVersion) ? kFblOk : kFblFailed)
#define ApplFblNvWriteSymcSoftwareVersion(idx, buf) ((EepMgrWrite(NV_GET_STRUCT_ID(kEepMgrHandle_ProcessData) + kEepMgrHandle_SymcSoftwareVersion, buf, kEepSizeSymcSoftwareVersion) == kEepMgrOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadSymcSoftwareVersion(idx, buf) ((EepromDriver_RReadSync(buf, kEepSizeSymcSoftwareVersion, kEepAddressSymcSoftwareVersion) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteSymcSoftwareVersion(idx, buf) ((EepromDriver_RWriteSync(buf, kEepSizeSymcSoftwareVersion, kEepAddressSymcSoftwareVersion) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadSystemSupplierCode(idx, buf) ((EepMgrRead(NV_GET_STRUCT_ID(kEepMgrHandle_ProcessData) + kEepMgrHandle_SystemSupplierCode, buf, kEepSizeSystemSupplierCode) == kEepSizeSystemSupplierCode) ? kFblOk : kFblFailed)
#define ApplFblNvWriteSystemSupplierCode(idx, buf) ((EepMgrWrite(NV_GET_STRUCT_ID(kEepMgrHandle_ProcessData) + kEepMgrHandle_SystemSupplierCode, buf, kEepSizeSystemSupplierCode) == kEepMgrOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadSystemSupplierCode(idx, buf) ((EepromDriver_RReadSync(buf, kEepSizeSystemSupplierCode, kEepAddressSystemSupplierCode) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteSystemSupplierCode(idx, buf) ((EepromDriver_RWriteSync(buf, kEepSizeSystemSupplierCode, kEepAddressSystemSupplierCode) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadProgCounter(idx, buf)   ((EepMgrRead(NV_GET_STRUCT_ID(kEepMgrHandle_Metadata) + kEepMgrHandle_ProgCounter + (idx * kEepMgrNrOfMetadataHdls), buf, kEepSizeProgCounter) == kEepSizeProgCounter) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgCounter(idx, buf)  ((EepMgrWrite(NV_GET_STRUCT_ID(kEepMgrHandle_Metadata) + kEepMgrHandle_ProgCounter + (idx * kEepMgrNrOfMetadataHdls), buf, kEepSizeProgCounter) == kEepMgrOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadProgCounter(idx, buf)   ((EepromDriver_RReadSync(buf, kEepSizeProgCounter, kEepAddressProgCounter + (idx * kEepSizeMetadata)) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgCounter(idx, buf)  ((EepromDriver_RWriteSync(buf, kEepSizeProgCounter, kEepAddressProgCounter + (idx * kEepSizeMetadata)) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadProgAttempts(idx, buf)  ((EepMgrRead(NV_GET_STRUCT_ID(kEepMgrHandle_Metadata) + kEepMgrHandle_ProgAttempts + (idx * kEepMgrNrOfMetadataHdls), buf, kEepSizeProgAttempts) == kEepSizeProgAttempts) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgAttempts(idx, buf) ((EepMgrWrite(NV_GET_STRUCT_ID(kEepMgrHandle_Metadata) + kEepMgrHandle_ProgAttempts + (idx * kEepMgrNrOfMetadataHdls), buf, kEepSizeProgAttempts) == kEepMgrOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadProgAttempts(idx, buf)  ((EepromDriver_RReadSync(buf, kEepSizeProgAttempts, kEepAddressProgAttempts + (idx * kEepSizeMetadata)) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteProgAttempts(idx, buf) ((EepromDriver_RWriteSync(buf, kEepSizeProgAttempts, kEepAddressProgAttempts + (idx * kEepSizeMetadata)) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadCRCValue(idx, buf)      ((EepMgrRead(NV_GET_STRUCT_ID(kEepMgrHandle_Metadata) + kEepMgrHandle_CRCValue + (idx * kEepMgrNrOfMetadataHdls), buf, kEepSizeCRCValue) == kEepSizeCRCValue) ? kFblOk : kFblFailed)
#define ApplFblNvWriteCRCValue(idx, buf)     ((EepMgrWrite(NV_GET_STRUCT_ID(kEepMgrHandle_Metadata) + kEepMgrHandle_CRCValue + (idx * kEepMgrNrOfMetadataHdls), buf, kEepSizeCRCValue) == kEepMgrOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadCRCValue(idx, buf)      ((EepromDriver_RReadSync(buf, kEepSizeCRCValue, kEepAddressCRCValue + (idx * kEepSizeMetadata)) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteCRCValue(idx, buf)     ((EepromDriver_RWriteSync(buf, kEepSizeCRCValue, kEepAddressCRCValue + (idx * kEepSizeMetadata)) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadCRCStart(idx, buf)      ((EepMgrRead(NV_GET_STRUCT_ID(kEepMgrHandle_Metadata) + kEepMgrHandle_CRCStart + (idx * kEepMgrNrOfMetadataHdls), buf, kEepSizeCRCStart) == kEepSizeCRCStart) ? kFblOk : kFblFailed)
#define ApplFblNvWriteCRCStart(idx, buf)     ((EepMgrWrite(NV_GET_STRUCT_ID(kEepMgrHandle_Metadata) + kEepMgrHandle_CRCStart + (idx * kEepMgrNrOfMetadataHdls), buf, kEepSizeCRCStart) == kEepMgrOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadCRCStart(idx, buf)      ((EepromDriver_RReadSync(buf, kEepSizeCRCStart, kEepAddressCRCStart + (idx * kEepSizeMetadata)) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteCRCStart(idx, buf)     ((EepromDriver_RWriteSync(buf, kEepSizeCRCStart, kEepAddressCRCStart + (idx * kEepSizeMetadata)) == IO_E_OK) ? kFblOk : kFblFailed)
#endif

#ifdef FBL_ENABLE_EEPMGR
#define ApplFblNvReadCRCLength(idx, buf)     ((EepMgrRead(NV_GET_STRUCT_ID(kEepMgrHandle_Metadata) + kEepMgrHandle_CRCLength + (idx * kEepMgrNrOfMetadataHdls), buf, kEepSizeCRCLength) == kEepSizeCRCLength) ? kFblOk : kFblFailed)
#define ApplFblNvWriteCRCLength(idx, buf)    ((EepMgrWrite(NV_GET_STRUCT_ID(kEepMgrHandle_Metadata) + kEepMgrHandle_CRCLength + (idx * kEepMgrNrOfMetadataHdls), buf, kEepSizeCRCLength) == kEepMgrOk) ? kFblOk : kFblFailed)
#else
#define ApplFblNvReadCRCLength(idx, buf)     ((EepromDriver_RReadSync(buf, kEepSizeCRCLength, kEepAddressCRCLength + (idx * kEepSizeMetadata)) == IO_E_OK) ? kFblOk : kFblFailed)
#define ApplFblNvWriteCRCLength(idx, buf)    ((EepromDriver_RWriteSync(buf, kEepSizeCRCLength, kEepAddressCRCLength + (idx * kEepSizeMetadata)) == IO_E_OK) ? kFblOk : kFblFailed)
#endif


#ifdef FBL_ENABLE_EEPMGR
#else
#define ApplFblIsValidEepAddress(i)          ((i >= kEepStartAddress) && (i <= kEepEndAddress))
#endif

#define ApplFblIsValidEepMgrHandle(i)        ((i >= kEepMgrFirstHandle) && (i <= kEepMgrLastHandle))

/* User Config File ********************************************************** */

/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 312540478
      #error "The magic number of the generated file <C:\Vector\CBD1800772_D00_Mpc57xx\Demo\DemoFbl\Appl\GenData\WrapNv_cfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 312540478
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __WRAPNV_CFG_H__ */
