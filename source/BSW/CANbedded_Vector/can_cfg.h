/* -----------------------------------------------------------------------------
  Filename:    can_cfg.h
  Description: Toolversion: 01.02.12.01.80.07.77.00.00.00
               
               Serial Number: CBD1800777
               Customer Info: Young Hwa Tech Co, Ltd, 
                              Package: CBD Symc SLP1 - in projects for SsangYong 
                              Micro: SPC570S50E1CEFAY
                              Compiler: Green Hills 2017.5.4
               
               
               Generator Fwk   : GENy 
               Generator Module: DrvCan__base
               
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

#if !defined(__CAN_CFG_H__)
#define __CAN_CFG_H__

#include "v_cfg.h"
#define HW_MPC55XX_FLEXCAN2CPUCANDLL_VERSION 0x0130u
#define HW_MPC55XX_FLEXCAN2CPUCANDLL_RELEASE_VERSION 0x01u

#define HW__BASECPUCANDLL_VERSION            0x0302u
#define HW__BASECPUCANDLL_RELEASE_VERSION    0x01u

#define DRVCAN__BASEDLL_VERSION              0x0326u
#define DRVCAN__BASEDLL_RELEASE_VERSION      0x00u

#define DRVCAN__BASERI14DLL_VERSION          0x0209u
#define DRVCAN__BASERI14DLL_RELEASE_VERSION  0x02u

#define DRVCAN__BASERI15DLL_VERSION          0x0109u
#define DRVCAN__BASERI15DLL_RELEASE_VERSION  0x01u

#define DRVCAN__BASEHLLDLL_VERSION           0x0307u
#define DRVCAN__BASEHLLDLL_RELEASE_VERSION   0x00u

#define DRVCAN__BASERI14HLLDLL_VERSION       0x0208u
#define DRVCAN__BASERI14HLLDLL_RELEASE_VERSION 0x00u

#define DRVCAN__BASERI15HLLDLL_VERSION       0x0103u
#define DRVCAN__BASERI15HLLDLL_RELEASE_VERSION 0x00u

#define CAN_DRV_MAC7100DLL_VERSION           0x0117u
#define CAN_DRV_MAC7100DLL_RELEASE_VERSION   0x00u


#define kCanNumberOfChannels                 1
#define kCanNumberOfHwChannels               1
#define kCanNumberOfPhysChannels             1
#define C_DISABLE_MEMCOPY_SUPPORT
#define C_DISABLE_OSEK_OS
#define C_DISABLE_VARIABLE_DLC
#define C_DISABLE_DLC_FAILED_FCT
#define C_DISABLE_VARIABLE_RX_DATALEN
#define C_DISABLE_MULTI_ECU_CONFIG
#define C_DISABLE_MULTI_ECU_PHYS
#define C_DISABLE_EXTENDED_ID
#define C_DISABLE_MIXED_ID
#define C_ENABLE_RECEIVE_FCT
#define APPL_CAN_MSGRECEIVED                 ApplCanMsgReceived

#define C_DISABLE_ECU_SWITCH_PASS
#define C_ENABLE_TRANSMIT_QUEUE
#define C_DISABLE_OVERRUN
#define C_DISABLE_INTCTRL_BY_APPL
#define C_DISABLE_COMMON_CAN
#define C_ENABLE_USER_CHECK
#define C_ENABLE_HARDWARE_CHECK
#define C_ENABLE_GEN_CHECK
#define C_ENABLE_INTERNAL_CHECK
#define C_DISABLE_DYN_RX_OBJECTS
#define C_DISABLE_DYN_TX_OBJECTS
#define C_DISABLE_DYN_TX_ID
#define C_DISABLE_DYN_TX_DLC
#define C_DISABLE_DYN_TX_DATAPTR
#define C_DISABLE_DYN_TX_PRETRANS_FCT
#define C_DISABLE_DYN_TX_CONF_FCT
#define C_DISABLE_EXTENDED_STATUS
#define C_DISABLE_TX_OBSERVE
#define C_DISABLE_HW_LOOP_TIMER
#define C_DISABLE_NOT_MATCHED_FCT
#define C_SECURITY_LEVEL                     30

#define C_DISABLE_MULTICHANNEL_API
#define C_ENABLE_PART_OFFLINE
#define C_DISABLE_RANGE_0
#define C_DISABLE_RANGE_1
#define C_DISABLE_RANGE_2
#define C_DISABLE_RANGE_3
#define kCanNumberOfTxObjects                4
#define kCanNumberOfTxStatObjects            4
#define kCanNumberOfTxDynObjects             0
#define kCanNumberOfRxObjects                5
#define kCanNumberOfRxStatFullCANObjects     4
#define kCanNumberOfRxStatBasicCANObjects    1
#define kCanNumberOfRxDynFullCANObjects      0
#define kCanNumberOfRxDynBasicCANObjects     0
#define kCanNumberOfRxDynObjects             0
#define kCanNumberOfRxStatObjects            5
#define kCanNumberOfConfFlags                3
#define kCanNumberOfIndFlags                 0
#define kCanNumberOfConfirmationFlags        1
#define kCanNumberOfIndicationFlags          0
#define kCanNumberOfInitObjects              1
#define kCanExtNumberOfInitObjects           0
#define kCanHwRxDynFullStartIndex            4
#define C_SEARCH_LINEAR

#define C_ENABLE_RX_MSG_INDIRECTION

#define C_ENABLE_CONFIRMATION_FLAG
#define C_DISABLE_INDICATION_FLAG
#define C_DISABLE_PRETRANSMIT_FCT
#define C_ENABLE_CONFIRMATION_FCT
#define C_ENABLE_INDICATION_FCT
#define C_ENABLE_PRECOPY_FCT
#define C_ENABLE_COPY_TX_DATA
#define C_ENABLE_COPY_RX_DATA
#define C_DISABLE_DLC_CHECK
#define C_DISABLE_DLC_CHECK_MIN_DATALEN

#define C_ENABLE_GENERIC_PRECOPY
#define APPL_CAN_GENERIC_PRECOPY             IlCanGenericPrecopy

#define C_SEND_GRP_NONE                      0x00u
#define C_SEND_GRP_ALL                       0xFFu
#define C_SEND_GRP_APPL                      0x01u
#define C_SEND_GRP_IL                        0x02u
#define C_SEND_GRP_USER2                     0x04u
#define C_SEND_GRP_USER3                     0x08u
#define C_SEND_GRP_USER4                     0x10u
#define C_SEND_GRP_USER5                     0x20u
#define C_SEND_GRP_USER6                     0x40u
#define C_SEND_GRP_USER7                     0x80u
#define C_ENABLE_CAN_CANCEL_NOTIFICATION
#define APPL_CAN_CANCELNOTIFICATION          IlCanCancelNotification

#define kCanPhysToLogChannelIndex_0
#define C_ENABLE_RX_FULLCAN_OBJECTS
#define C_ENABLE_RX_BASICCAN_OBJECTS
#define kCanNumberOfRxFullCANObjects         4

#define kCanNumberOfRxBasicCANObjects        1
#define kCanInitObj1                         0
#define C_DISABLE_TX_MASK_EXT_ID
#define C_DISABLE_RX_MASK_EXT_ID
#define C_MASK_EXT_ID                        0xFFFFFFFFu

#define C_ENABLE_CAN_CAN_INTERRUPT_CONTROL
#define C_DISABLE_CAN_TX_CONF_MSG_ACCESS
#define C_DISABLE_CAN_TX_CONF_FCT

#define C_ENABLE_TX_POLLING
#define C_ENABLE_RX_BASICCAN_POLLING
#define C_ENABLE_RX_FULLCAN_POLLING
#define C_ENABLE_ERROR_POLLING
#define C_ENABLE_WAKEUP_POLLING
#define C_DISABLE_FULLCAN_OVERRUN
#define C_DISABLE_OSEK_OS_INTCAT2
#define C_DISABLE_COPY_RX_DATA_WITH_DLC
#define kCanTxQueueBytes                     4
#define kCanNumberOfMaxBasicCAN              1
#define kCanNumberOfHwObjPerBasicCan         2
#define C_DISABLE_CAN_RAM_CHECK
#define C_DISABLE_SLEEP_WAKEUP
#define C_DISABLE_CANCEL_IN_HW
#define C_DISABLE_ONLINE_OFFLINE_CALLBACK_FCT

#define kCanChannel_Channel0                 0
#define C_DISABLE_INTCTRL_ADD_CAN_FCT
#if defined(C_SINGLE_RECEIVE_BUFFER) || defined(C_MULTIPLE_RECEIVE_BUFFER)
#error "DrvCan__baseRI1.5 doesn't support Single/Multiple Receive Buffer API for the callback 'ApplCanMsgReceived'!"
#endif

#define C_DISABLE_RETRANSMIT
#define kCanNumberOfUsedCanTxIdTables        1
#define kCanNumberOfUsedCanRxIdTables        1
#define kCanHwUnusedStartIndex               6

#define kCanHwRxFullStartIndex               0

#define kCanNumberOfUsedTxCANObjects         1

#define kCanNumberOfUnusedObjects            25

#define kCanNumberOfTxDirectObjects          0

#define C_DISABLE_TX_FULLCAN_OBJECTS


#define C_ENABLE_HW_OBJ_EXCEED_255_CFG

#define C_DISABLE_INDIVIDUAL_POLLING
#define kCanNumberOfHwObjIndivPolling        32

#define C_TOUCAN_BASIS                       0xFFEC0000u
#define kCanInterruptMaskLo                  0x00u
#define kCanRxFullPollingMaskLo              0x0Fu
#define kCanRxBasicPollingMaskLo             0x30u
#define kCanTxPollingMaskLo                  0x80000000u
#define kCanMsgTransmitObj                   32
#define kCanHwTxNormalIndex                  31
#define kCanHwTxStartIndex                   31
#define kCanHwRxBasicStartIndex              4
#define kCanNumberOfUsedRxBasicCANObjects    2
#define C_DISABLE_INTERRUPT
#define C_DISABLE_SINGLE_ISR_API
#define C_ENABLE_FLEXCAN_INDIV_RXMASK
#define C_DISABLE_FLEXCAN_RXFIFO
#define C_CAN_MAX_BUFFER_32
#define C_ENABLE_MIXED_RX_FULLCAN_MESSAGES



/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 345877849
      #error "The magic number of the generated file <D:\07_Working\E100\source\BSW\CANbedded_Vector\can_cfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 345877849
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __CAN_CFG_H__ */
