/* -----------------------------------------------------------------------------
  Filename:    fbl_cw_cfg.h
  Description: Toolversion: 01.03.00.01.80.07.72.00.00.00
               
               Serial Number: CBD1800772
               Customer Info: Young Hwa Tech Co, Ltd, 
                              Package: FBL Symc SLP2 - ECU Product for SYMC
                              Micro: SPC570S50E1CEFAY
                              Compiler: Green Hills 2017.5.4
               
               
               Generator Fwk   : GENy 
               Generator Module: FblWrapperCom_Can
               
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

#if !defined(__FBL_CW_CFG_H__)
#define __FBL_CW_CFG_H__

/* Configuration types */
typedef void (*tFblCwIndicationHandler)( vuint8, volatile vuint8*, vuintx );
typedef void (*tFblCwConfirmationHandler)( vuint8 );
/* Receive identifier structure */
typedef struct tFblCanRxIdListTag
{
  vuintx nrOfNodes; /* Number of nodes, e.g. used by multiple nodes setups */
  vuintx nrOfChannels; /* Number of channels, e.g. used by multiple platforms setups */
  vuintx fblCanIdTableIndex; /* Index into FblCanIdTable */
  vuintx rxObject; /* Message object parameter in FblHandleRxMsg */
  V_MEMROM1 vuint32 V_MEMROM2 V_MEMROM3 * idList; /* Flattened ID list */
  tFblCwIndicationHandler fblCwIndicationHandler; /* Message handler called by FblHandleRxMsg */
  vuintx connectionIndex; /* Connection index, e.g. used by multiple connection setups */
} tFblCanRxIdList;
/* Transmit identifier structure */
typedef struct tFblCanTxIdListTag
{
  vuintx nrOfNodes; /* Number of nodes, e.g. used by multiple nodes setups */
  vuintx nrOfChannels; /* Number of channels, e.g. used by multiple platforms setups */
  vuintx txObject; /* Message object parameter in FblHandleRxMsg */
  V_MEMROM1 vuint32 V_MEMROM2 V_MEMROM3 * idList; /* Flattened ID list */
  tFblCwConfirmationHandler fblCwConfirmationHandler; /* Confirmation function called after message has been transmitted */
  vuintx connectionIndex; /* Connection index, e.g. used by multiple connection setups */
} tFblCanTxIdList;
/* Basic CAN defines */
/* Receive identifiers */
#define FBL_CAN_NUMBER_OF_RX_ID              2u
#define FBL_CAN_NUMBER_OF_RANGES             0u
#define FBL_NUMBER_OF_RX_ID                  (FBL_CAN_NUMBER_OF_RX_ID + FBL_CAN_NUMBER_OF_RANGES)
/* Special configuration for NormalFixed Addressing */
#define FBL_CW_DISABLE_NORMAL_FIXED_ADDRESSING
#define FBL_DISABLE_CAN_RX_RANGE
/* Special configuration for Extended Addressing */
#define FBL_CW_DISABLE_EXTENDED_ADDRESSING
/* Special configuration for Mixed Addressing */
#define FBL_CW_DISABLE_MIXED_ADDRESSING
/* Response identifiers */
#define FBL_NUMBER_OF_TX_ID                  1u
#define kFblCwDiagTxObject                   0u

#define FBL_CW_CFG_START_SEC_CONST
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Configuration */
V_MEMROM0 extern  V_MEMROM1 vuint32 V_MEMROM2 diagPhysRxIdList[1];
V_MEMROM0 extern  V_MEMROM1 vuint32 V_MEMROM2 diagFuncRxIdList[1];
V_MEMROM0 extern  V_MEMROM1 vuint32 V_MEMROM2 diagPhysTxIdList[1];
V_MEMROM0 extern  V_MEMROM1 tFblCanRxIdList V_MEMROM2 fblCanIdRxConfiguration[FBL_NUMBER_OF_RX_ID];
V_MEMROM0 extern  V_MEMROM1 tFblCanTxIdList V_MEMROM2 fblCanIdTxConfiguration[FBL_NUMBER_OF_TX_ID];
#define FBL_CW_NUMBER_OF_CHANNELS            1
#define FBL_CW_DISABLE_MULTIPLE_CHANNELS
#define FBL_CW_NUMBER_OF_NODES               1
#define FBL_CW_DISABLE_MULTIPLE_NODES
#define FBL_CW_NUMBER_OF_CONNECTIONS         1
#define FBL_CW_DISABLE_MULTIPLE_CONNECTIONS

#define FBL_CW_CFG_STOP_SEC_CONST
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* User Config File ********************************************************** */
/* User Section ************************************************************** */
/* FblWrapperCom_Can feature selection */
# define FBL_CW_ENABLE_PHYSICAL_REQUEST_HANDLER
# define FBL_CW_ENABLE_FUNCTIONAL_REQUEST_HANDLER
/* *************************************************************************** */

/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 312540478
      #error "The magic number of the generated file <C:\Vector\CBD1800772_D00_Mpc57xx\Demo\DemoFbl\Appl\GenData\fbl_cw_cfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 312540478
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __FBL_CW_CFG_H__ */
