/* -----------------------------------------------------------------------------
  Filename:    fbl_cfg.h
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

#if !defined(__FBL_CFG_H__)
#define __FBL_CFG_H__

/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

#define FBL_USE_OWN_MEMCPY
#define FBL_WATCHDOG_ON
#define FBL_WATCHDOG_TIME                    (1 / FBL_REPEAT_CALL_CYCLE)
#define FBL_HEADER_ADDRESS                   0xFC0400u
#define FBL_ENABLE_APPL_TASK
#define FBL_ENABLE_MULTIPLE_MODULES
#define FBL_DIAG_BUFFER_LENGTH               4095
#define FBL_DIAG_TIME_P2MAX                  (50 / FBL_REPEAT_CALL_CYCLE)
#define FBL_DIAG_TIME_P3MAX                  (2000 / FBL_REPEAT_CALL_CYCLE)
#define FBL_ENABLE_SLEEPMODE
#define FBL_SLEEP_TIME                       300000
#define FBL_ENABLE_GAP_FILL
#define kFillChar                            0xFFu
#define FBL_ENABLE_MULTIPLE_MEM_DEVICES
#define FBL_MEMDRV_SEGMENT_SIZE              8
#define FBL_ENABLE_PRESENCE_PATTERN
#define FBL_ENABLE_FBL_START
#define FBL_DISABLE_RESPONSE_AFTER_RESET
#define FBL_DISABLE_USERSUBFUNCTION
#define FBL_DISABLE_USERSERVICE
#define FBL_MTAB_NO_OF_BLOCKS                2
/* Data Processing */
#define FBL_DISABLE_DATA_PROCESSING
#define FBL_DISABLE_ENCRYPTION_MODE
#define FBL_DISABLE_COMPRESSION_MODE
#define FBL_MEM_PROC_BUFFER_SIZE             0x0100
/* Project State */
#define FBL_INTEGRATION                      2
#define FBL_PRODUCTION                       1
#define FBL_PROJECT_STATE                    FBL_INTEGRATION
#define FBL_ENABLE_SYSTEM_CHECK
#define FBL_ENABLE_DEBUG_STATUS
#define FBL_ENABLE_ASSERTION
/* FblLib_Mem */
#define FBL_MEM_DISABLE_VERIFY_PIPELINED
#define FBL_MEM_ENABLE_VERIFY_OUTPUT
#define FBL_MEM_VERIFY_SEGMENTATION          0x40
#define FBL_DISABLE_ADAPTIVE_DATA_TRANSFER_RCRRP
#define FBL_DISABLE_PIPELINED_PROGRAMMING
#define FBL_MEM_WRITE_SEGMENTATION           0x0100
#define FBL_ENABLE_UNALIGNED_DATA_TRANSFER
/* CAN Identifier */

/* Flexcan3 specific ********************************************************* */
#define FLASH_SIZE                           1536
#define FBL_TIMER_RELOAD_VALUE               19999
#define FBL_ENABLE_DMA_FLASH_READ
#define FBL_FLASH_REG_0                      0xFFFE0000u
#define FLASH_SETUP                          6

#define CAN_CTRL0                            0x00
#define CAN_CTRL1                            0x06
#define CAN_CTRL2                            0x1B
#define CAN_PRESDIV                          0x09
#define FBL_HW_DISABLE_FLEXCAN2_FEATURESET
#define FBL_HW_ENABLE_PARITY_CHECK_AVAILABLE
/* Mpc5700 */
#define FBL_CAN_REG_OFFSET                   0xFFEC0000u

/* Manufacturer specific part ************************************************ */
/* FBL multiple nodes support: */
#define FBL_DISABLE_MULTIPLE_NODES

#define SWM_DATA_MAX_NOAR                    8
#define FLASHDRIVER_BLOCKINDEX               0x30u
#define FBL_ENABLE_SEC_ACCESS_DELAY
#define FBL_SEC_ACCESS_DELAY_TIME            10000u
#define FBL_DIAG_ENABLE_ADDR_BASED_DOWNLOAD
#define FBL_APPL_DISABLE_STARTUP_DEPENDENCY_CHECK


/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

/* User Config File ********************************************************** */
#define FBL_ENABLE_VECTOR_HW /* Enable Vector HW*/
#define FBL_ENABLE_WRITE_RCHW
/* User Section ************************************************************** */
#define FBL_ENABLE_CAN_CONFIRMATION
#define FBL_ENABLE_SECMOD_VECTOR
#if !defined( FBL_DISABLE_WRAPPER_NV )
# define FBL_ENABLE_WRAPPER_NV
#endif

/* Task handling in RAM */

/* User task handling */
#if defined( FBL_ENABLE_APPL_TASK )
# if !defined( FBL_DISABLE_APPL_STATE_TASK )
#  define FBL_ENABLE_APPL_STATE_TASK
# endif
# if !defined( FBL_DISABLE_APPL_TIMER_TASK )
#  define FBL_ENABLE_APPL_TIMER_TASK
# endif
#endif

#if defined( FBL_ENABLE_MULTIPLE_NODES )
# undef FBL_ENABLE_MULTIPLE_NODES
#endif
/* User Section Pcu ********************************************************** */
/* Feature set of SPC570S50 */
#define FBL_SFR_SIU_TYPE   2u

/* Defines for peripheral module base addresses */
#define FBL_SWT_BASE       0xFC058000ul      /**< Software watchdog timer base address */
#define FBL_PIT_BASE       0xFFF84000ul      /**< PIT base address */
#define FBL_PLL_BASE       0xFFFB0100ul      /**< Dual PLL base register */
#define FBL_ME_BASE        0xFFFB8000ul      /**< Mode entry module base register */
#define FBL_CMU_BASE       0xC3FE0100ul      /**< Clock monitoring unit base register */
#define FBL_CMU_PLL_BASE   0xFFFB0200ul      /**< CMU base register for PLL */
#define FBL_CGM_BASE       0xFFFB0000ul      /**< Clock generation module */
#define FBL_RGM_BASE       0xFFFA8000ul      /**< Reset generation module base register */
#define FBL_SIUL2_BASE     0xFFFC0000ul      /**< SIU lite base address */
#define FBL_STM_BASE       0xFC068000ul      /**< System timer base address */
#define FBL_EDMA_BASE      0xFC0A0000ul      /**< eDMA0 base address */

/* Define to check preconfiguration of base addresses */
#define FBL_SFR_BASE_ADRESSES_PRECONFIGURED
/* *************************************************************************** */


/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 312540478
      #error "The magic number of the generated file <C:\Vector\CBD1800772_D00_Mpc57xx\Demo\DemoFbl\Appl\GenData\fbl_cfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 312540478
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __FBL_CFG_H__ */
