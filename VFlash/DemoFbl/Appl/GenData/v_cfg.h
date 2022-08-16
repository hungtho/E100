/* -----------------------------------------------------------------------------
  Filename:    v_cfg.h
  Description: Toolversion: 01.03.00.01.80.07.72.00.00.00
               
               Serial Number: CBD1800772
               Customer Info: Young Hwa Tech Co, Ltd, 
                              Package: FBL Symc SLP2 - ECU Product for SYMC
                              Micro: SPC570S50E1CEFAY
                              Compiler: Green Hills 2017.5.4
               
               
               Generator Fwk   : GENy 
               Generator Module: GenTool_GenyVcfgNameDecorator
               
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

/* FBL is enabled */
#define VGEN_ENABLE_CANFBL


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


/* -----------------------------------------------------------------------------
    &&&~ Optimization
 ----------------------------------------------------------------------------- */

#ifndef V_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define V_ATOMIC_BIT_ACCESS_IN_BITFIELD      STD_OFF
#endif

#ifndef V_ATOMIC_VARIABLE_ACCESS
#define V_ATOMIC_VARIABLE_ACCESS             16
#endif



#ifndef C_CLIENT_VECTOR
#define C_CLIENT_VECTOR
#endif


/* hw.cfg: user config file begin */
/*
 * This file must be included in Geny for configurations with Velvety derivatives.
 * Please see readme for more detailed info.
*/

#define V_COMP_GHS_MPC5700
#define V_CPU_MPC5700

/* hw.cfg: user config file end */

/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 312540478
      #error "The magic number of the generated file <C:\Vector\CBD1800772_D00_Mpc57xx\Demo\DemoFbl\Appl\GenData\v_cfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 312540478
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __V_CFG_H__ */
