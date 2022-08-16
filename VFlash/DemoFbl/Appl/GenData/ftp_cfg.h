/* -----------------------------------------------------------------------------
  Filename:    ftp_cfg.h
  Description: Toolversion: 01.03.00.01.80.07.72.00.00.00
               
               Serial Number: CBD1800772
               Customer Info: Young Hwa Tech Co, Ltd, 
                              Package: FBL Symc SLP2 - ECU Product for SYMC
                              Micro: SPC570S50E1CEFAY
                              Compiler: Green Hills 2017.5.4
               
               
               Generator Fwk   : GENy 
               Generator Module: FblTp_Iso
               
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

#if !defined(__FTP_CFG_H__)
#define __FTP_CFG_H__

/* PRQA S 3453 EOF */ /* MD_MSR_19.7 */
#define FBL_TP_DISABLE_EXTENDED_ADDRESSING
#define FBL_TP_ENABLE_TX_FRAME_PADDING
#define kFblTpFillPattern                    170
#define FBL_TP_DISABLE_ACCEPT_TOO_LARGE_DATA
#define FBL_TP_DISABLE_OVERRUN_FLAG_IN_FC
#define FBL_TP_DISABLE_ISO_COMPLIANCE
#define FBL_TP_DISABLE_ONLY_FIRST_FC
#define FBL_TP_ENABLE_FLOW_STATE
#define kFblTpWFTmax                         16u
#define FBL_TP_DISABLE_NO_STMIN_AFTER_FC
#define FBL_TP_DISABLE_WAIT_CORRECT_SN
#define FBL_TP_ENABLE_ISO15765_2_2
#define FBL_TP_DISABLE_VARIABLE_TX_DLC
#define FBL_TP_ENABLE_FIX_RX_DLC_CHECK
#define FBL_TP_DISABLE_VARIABLE_RX_DLC
#define FBL_TP_ENABLE_INTERNAL_MEMCPY
#define TpCallCycle                          1
#define FBL_TP_ENABLE_CONFIRMATION_INTERRUPT
#define FBL_TP_DISABLE_QUEUED_REQUESTS
#define kFblTpConfInterruptTimeout           70
#define kFblTpSTMin                          0
#define kFblTpTimeoutFC                      150
#define kFblTpTimeoutCF                      150
#define kFblTpTransmitCF                     10
#define kFblTpBlocksize                      8
#define kFblTpBufferSize                     4095
#define __ApplFblTpErrorIndication(i)        FblCwTpErrorIndication(i)
#define __ApplFblTpDataInd(i)                FblCwTpDataInd(i)
#define __ApplFblTpDataIndOverrun(actLen, refLen) FblCwTpDataIndBO(actLen, refLen)
#define __ApplFblTpConfirm(i)                FblCwTpConfirmation(i)
#define __ApplFblTpCopyFromCAN(dst, src, len) (void)(MEMCPY( (void *)(dst), (V_MEMROM0 V_MEMROM1 void V_MEMROM2 *)(src), (size_t)(len) ))
#define __ApplFblTpCopyToCAN(dst, src, len)  (void)(MEMCPY( (void *)(dst), (V_MEMROM0 V_MEMROM1 void V_MEMROM2 *)(src), (size_t)(len) ))
#define __ApplFblTpNotifyTx(i)
#define __ApplFblTpCanMessageTransmitted()
#define __ApplFblTpCanMessageReceived()
#define __ApplFblTpRxSF()                    FblCwTpRxStartIndication()
#define __ApplFblTpRxFF()                    FblCwTpRxStartIndication()
#define __ApplFblTpRxCF()
#define __ApplFblTpMsgTooLong(len_lobyte, len_hibyte)
#ifndef C_CPUTYPE_8BIT
#define FBL_TP_ENABLE_OSEK_DATA_LENGTH
typedef vuint16 tTpDataType;
#else
#define FBL_TP_ENABLE_OSEK_DATA_LENGTH
typedef vuint16 tTpDataType;
#endif


/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 312540478
      #error "The magic number of the generated file <C:\Vector\CBD1800772_D00_Mpc57xx\Demo\DemoFbl\Appl\GenData\ftp_cfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 312540478
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __FTP_CFG_H__ */
