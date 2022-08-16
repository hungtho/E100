/* -----------------------------------------------------------------------------
  Filename:    v_cfg.h
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

#if !defined(__V_CFG_H__)
#define __V_CFG_H__

#ifndef VGEN_GENY
#define VGEN_GENY
#endif

#ifndef GENy
#define GENy
#endif

#ifndef SUPPLIER_CANBEDDED
#define SUPPLIER_CANBEDDED                   30
#endif

/* -----------------------------------------------------------------------------
    &&&~ Version
 ----------------------------------------------------------------------------- */

#ifndef VERSIONNUMBER
#define VERSIONNUMBER                        0x110
#endif



/* -----------------------------------------------------------------------------
    &&&~ General Switches
 ----------------------------------------------------------------------------- */

#ifndef V_OSTYPE_NONE
#define V_OSTYPE_NONE
#endif



/* -----------------------------------------------------------------------------
    &&&~ Processor specific
 ----------------------------------------------------------------------------- */

#ifndef C_CPUTYPE_32BIT
#define C_CPUTYPE_32BIT
#endif


#ifndef V_CPUTYPE_BITARRAY_32BIT
#define V_CPUTYPE_BITARRAY_32BIT
#endif


#ifndef C_CPUTYPE_BIGENDIAN
#define C_CPUTYPE_BIGENDIAN
#endif


#ifndef C_CPUTYPE_BITORDER_MSB2LSB
#define C_CPUTYPE_BITORDER_MSB2LSB
#endif


#ifndef V_DISABLE_USE_DUMMY_FUNCTIONS
#define V_DISABLE_USE_DUMMY_FUNCTIONS
#endif


#ifndef V_ENABLE_USE_DUMMY_STATEMENT
#define V_ENABLE_USE_DUMMY_STATEMENT
#endif


#ifndef C_COMP_GHS_MPC55XX_FLEXCAN2
#define C_COMP_GHS_MPC55XX_FLEXCAN2
#endif


#ifndef V_CPU_MPC55XX
#define V_CPU_MPC55XX
#endif

#ifndef V_COMP_GHS
#define V_COMP_GHS
#endif

#ifndef V_COMP_GHS_MPC55XX
#define V_COMP_GHS_MPC55XX
#endif

#ifndef V_PROCESSOR_SPC570S50
#define V_PROCESSOR_SPC570S50
#endif


#ifndef C_PROCESSOR_SPC570S50
#define C_PROCESSOR_SPC570S50
#endif




/* -----------------------------------------------------------------------------
    &&&~ Used Modules
 ----------------------------------------------------------------------------- */

#ifndef VGEN_ENABLE_VSTDLIB
#define VGEN_ENABLE_VSTDLIB
#endif

#ifndef VSTD_ENABLE_APPL_INTCTRL
#define VSTD_ENABLE_APPL_INTCTRL
#endif

void TEST_DI(void);
void TEST_EI(void);
#ifndef VStdUserNestedDisable
#define VStdUserNestedDisable                TEST_DI
#endif

#ifndef VStdUserNestedRestore
#define VStdUserNestedRestore                TEST_EI
#endif

#ifndef VSTD_DISABLE_DEBUG_SUPPORT
#define VSTD_DISABLE_DEBUG_SUPPORT
#endif

#ifndef VSTD_ENABLE_LIBRARY_FUNCTIONS
#define VSTD_ENABLE_LIBRARY_FUNCTIONS
#endif


#define VGEN_ENABLE_DIAG_CANDESC_UDS
#define VGEN_ENABLE_DIAG_CANDESC_UDS2012
#define VGEN_ENABLE_CAN_DRV
#define C_ENABLE_CAN_CHANNELS
#define V_BUSTYPE_CAN
#define VGEN_ENABLE_IL_VECTOR
#define VGEN_ENABLE_TP_ISO_MC


#ifndef kVNumberOfIdentities
#define kVNumberOfIdentities                 1
#endif

#ifndef tVIdentityMsk
#define tVIdentityMsk                        vuint8
#endif

#ifndef kVIdentityIdentity_0
#define kVIdentityIdentity_0                 (vuint8) 0
#endif

#ifndef VSetActiveIdentity
#define VSetActiveIdentity(identityLog)
#endif

#ifndef V_ACTIVE_IDENTITY_MSK
#define V_ACTIVE_IDENTITY_MSK                1
#endif

#ifndef V_ACTIVE_IDENTITY_LOG
#define V_ACTIVE_IDENTITY_LOG                0
#endif


#define DIAG_API_CALL_TYPE
#define DIAG_API_CALLBACK_TYPE
#define DIAG_INTERNAL_CALL_TYPE
#define DRV_API_CALL_TYPE
#define DRV_API_CALLBACK_TYPE
#define TP_API_CALL_TYPE
#define TP_API_CALLBACK_TYPE
#define TP_INTERNAL_CALL_TYPE

/* -----------------------------------------------------------------------------
    &&&~ Versions of Preconfig Files
 ----------------------------------------------------------------------------- */

#define VGEN_OEM_PRECONFIG_SYMC_SLP1_Generic
#define VGEN_OEM_PRECONFIG_VERSION           0x0101
#define VGEN_OEM_PRECONFIG_RELEASE_VERSION   0x00
#define VGEN_USER_PRECONFIG_BODY_CAN_ECU
#define VGEN_USER_PRECONFIG_VERSION          0x0100
#define VGEN_USER_PRECONFIG_RELEASE_VERSION  0x00


/* -----------------------------------------------------------------------------
    &&&~ Optimization
 ----------------------------------------------------------------------------- */

#ifndef V_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define V_ATOMIC_BIT_ACCESS_IN_BITFIELD      STD_OFF
#endif

#ifndef V_ATOMIC_VARIABLE_ACCESS
#define V_ATOMIC_VARIABLE_ACCESS             16
#endif




#ifndef VGEN_ENABLE_VSTDLIB
/* Diag_CanDesc requires VSTDLIB */
#define VGEN_ENABLE_VSTDLIB
#endif

#ifndef C_CLIENT_SYMC
#define C_CLIENT_SYMC
#endif

#ifndef __LDC__
#define __LDC__
#endif

/* -----------------------------------------------------------------------------
    &&&~ Compatibility defines for ComSetCurrentECU
 ----------------------------------------------------------------------------- */

#ifndef kComNumberOfNodes
#define kComNumberOfNodes                    kVNumberOfIdentities
#endif

#ifndef ComSetCurrentECU
#define ComSetCurrentECU                     VSetActiveIdentity
#endif

#ifndef comMultipleECUCurrent
#define comMultipleECUCurrent                vActiveIdentityLog
#endif



#define C_VERSION_REF_IMPLEMENTATION         0x150u


#ifndef VGEN_ENABLE_VSTDLIB
/* DrvCan__baseRi15 requires VSTDLIB */
#define VGEN_ENABLE_VSTDLIB
#endif

#ifndef VGEN_ENABLE_VSTDLIB
#define VGEN_ENABLE_VSTDLIB
#endif


#ifndef VGEN_ENABLE_VSTDLIB
/* TpMC requires VSTDLIB */
#define VGEN_ENABLE_VSTDLIB
#endif



/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 345877849
      #error "The magic number of the generated file <D:\07_Working\E100\source\BSW\CANbedded_Vector\v_cfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 345877849
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __V_CFG_H__ */
