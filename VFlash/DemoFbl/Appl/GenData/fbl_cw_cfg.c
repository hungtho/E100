/* -----------------------------------------------------------------------------
  Filename:    fbl_cw_cfg.c
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

#define FBL_CW_CFG_SOURCE

#include "fbl_inc.h"

#define FBL_CW_CFG_START_SEC_CONST
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

V_MEMROM0 V_MEMROM1 vuint32 V_MEMROM2 diagPhysRxIdList[1] = { MK_STDID(0x763u) };
V_MEMROM0 V_MEMROM1 vuint32 V_MEMROM2 diagFuncRxIdList[1] = { MK_STDID(0x700u) };
V_MEMROM0 V_MEMROM1 vuint32 V_MEMROM2 diagPhysTxIdList[1] = { MK_STDID(0x76Bu) };
/* RX ID configuration */
V_MEMROM0 V_MEMROM1 tFblCanRxIdList V_MEMROM2 fblCanIdRxConfiguration[FBL_NUMBER_OF_RX_ID] = 
{
  
  {
    1u /* Nodes / nrOfNodes */, 
    1u /* Channels / nrOfChannels */, 
    0u /* MessageObject / fblCanIdTableIndex */, 
    FblRxCanMsg0Hdl /* ReceiveHandle / rxObject */, 
    diagPhysRxIdList /* GenName / idList */, 
    FblCwProcessPhysicalRequest /* IndicationConfirmationFunction / fblCwIndicationHandler */, 
    0u /* ConnectionIndex / connectionIndex */
  }, 
  
  {
    1u /* Nodes / nrOfNodes */, 
    1u /* Channels / nrOfChannels */, 
    1u /* MessageObject / fblCanIdTableIndex */, 
    FblRxCanMsg1Hdl /* ReceiveHandle / rxObject */, 
    diagFuncRxIdList /* GenName / idList */, 
    FblCwProcessFunctionalRequest /* IndicationConfirmationFunction / fblCwIndicationHandler */, 
    0u /* ConnectionIndex / connectionIndex */
  }
};
/* TX ID configuration */
V_MEMROM0 V_MEMROM1 tFblCanTxIdList V_MEMROM2 fblCanIdTxConfiguration[FBL_NUMBER_OF_TX_ID] = 
{
  
  {
    1u /* Nodes / nrOfNodes */, 
    1u /* Channels / nrOfChannels */, 
    0u /* MessageObject / txObject */, 
    diagPhysTxIdList /* GenName / idList */, 
    FblTpConfirmation /* IndicationConfirmationFunction / fblCwConfirmationHandler */, 
    0u /* ConnectionIndex / connectionIndex */
  }
};

#define FBL_CW_CFG_STOP_SEC_CONST
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 312540478
      #error "The magic number of the generated file <C:\Vector\CBD1800772_D00_Mpc57xx\Demo\DemoFbl\Appl\GenData\fbl_cw_cfg.c> is different. Please check time and date of generated files!"
  #endif
#else
  #error "The magic number is not defined in the generated file <C:\Vector\CBD1800772_D00_Mpc57xx\Demo\DemoFbl\Appl\GenData\fbl_cw_cfg.c> "

#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

