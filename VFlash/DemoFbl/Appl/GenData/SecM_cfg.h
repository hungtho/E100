/* -----------------------------------------------------------------------------
  Filename:    SecM_cfg.h
  Description: Toolversion: 01.03.00.01.80.07.72.00.00.00
               
               Serial Number: CBD1800772
               Customer Info: Young Hwa Tech Co, Ltd, 
                              Package: FBL Symc SLP2 - ECU Product for SYMC
                              Micro: SPC570S50E1CEFAY
                              Compiler: Green Hills 2017.5.4
               
               
               Generator Fwk   : GENy 
               Generator Module: SysService_SecModHis
               
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

#if !defined(__SECM_CFG_H__)
#define __SECM_CFG_H__

#define SEC_CLASS_DDD                        0
#define SEC_CLASS_C                          1
#define SEC_CLASS_CCC                        2
#define SEC_CLASS_VENDOR                     3
#define SEC_DEVELOPMENT                      1
#define SEC_PRODUCTION                       2
#define SEC_ADDRESS                          1
#define SEC_FILE                             2
#define SEC_CRC_SPEED_OPTIMIZED              0
#define SEC_CRC_SIZE_OPTIMIZED               1
#define SEC_RIPEMD160                        0
#define SEC_SHA1                             1
#define SEC_SHA256                           2

#define SEC_MODE                             SEC_PRODUCTION
#define SEC_CRC_OPT                          SEC_CRC_SIZE_OPTIMIZED
#define SEC_DISABLE_DECRYPTION
#define SEC_DISABLE_ENCRYPTION
#define SEC_DISABLE_DECRYPTION_KEY_EXTERNAL
#define SEC_ENABLE_DECRYPTION_KEY_INTERNAL
#define SEC_ECU_KEY                          0xFFFFFFFFu
#define SEC_KEY_TIMEOUT                      0
#define SEC_CALL_CYCLE                       10
#define SEC_DISABLE_SEEDKEY_KEY_EXTERNAL
#define SEC_ENABLE_SEEDKEY_KEY_INTERNAL
#define SEC_HASH_ALGORITHM                   SEC_SHA1
#define SEC_SECURITY_CLASS                   SEC_CLASS_DDD
#define SEC_DISABLE_SECURITY_CLASS_DDD
#define SEC_DISABLE_SECURITY_CLASS_C
#define SEC_DISABLE_SECURITY_CLASS_CCC
#define SEC_DISABLE_SECURITY_CLASS_VENDOR
#define SEC_DISABLE_VERIFICATION_KEY_EXTERNAL
#define SEC_ENABLE_VERIFICATION_KEY_INTERNAL
#define SEC_SIZE_CHECKSUM_VENDOR             0
#define SEC_MEMORY_ACCESS                    SEC_ADDRESS
#define SEC_VERIFY_BYTES                     64
#define SEC_ENABLE_VERIFICATION_ADDRESS_LENGTH
#define SEC_ENABLE_CRC_TOTAL
#define SEC_DISABLE_CRC_WRITTEN
#define SEC_DISABLE_VENDOR_CHECKSUM
#define SEC_VER_SIG_OFFSET                   0
#define SEC_VER_CRC_OFFSET                   0

/* User Config File ********************************************************** */
/* User Section ************************************************************** */

/* *************************************************************************** */

/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 312540478
      #error "The magic number of the generated file <C:\Vector\CBD1800772_D00_Mpc57xx\Demo\DemoFbl\Appl\GenData\SecM_cfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 312540478
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __SECM_CFG_H__ */
