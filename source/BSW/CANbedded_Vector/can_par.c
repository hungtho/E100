/* -----------------------------------------------------------------------------
  Filename:    can_par.c
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

#define C_DRV_INTERNAL
#include "can_inc.h"
#include "can_par.h"
#include "v_inc.h"

/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 tCanTxId0 V_MEMROM2 CanTxId0[kCanNumberOfTxObjects] = 
{
  MK_STDID0(0x76Bu) /* ID: 0x0000076b, Handle: 0, LDC_DGN_RESP [BC] */, 
  MK_STDID0(0x563u) /* ID: 0x00000563, Handle: 1, LDC_PCAN_STS [BC] */, 
  MK_STDID0(0x3A1u) /* ID: 0x000003a1, Handle: 2, LDC_3A1h [BC] */, 
  MK_STDID0(0x3A0u) /* ID: 0x000003a0, Handle: 3, LDC_3A0h [BC] */
};
/* ROM CATEGORY 1 END */


/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanTxDLC[kCanNumberOfTxObjects] = 
{
  MK_TX_DLC(8) /* ID: 0x0000076b, Handle: 0, LDC_DGN_RESP [BC] */, 
  MK_TX_DLC(8) /* ID: 0x00000563, Handle: 1, LDC_PCAN_STS [BC] */, 
  MK_TX_DLC(8) /* ID: 0x000003a1, Handle: 2, LDC_3A1h [BC] */, 
  MK_TX_DLC(8) /* ID: 0x000003a0, Handle: 3, LDC_3A0h [BC] */
};
/* ROM CATEGORY 1 END */


#ifdef C_ENABLE_COPY_TX_DATA
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 TxDataPtr V_MEMROM2 CanTxDataPtr[kCanNumberOfTxObjects] = 
{
  (TxDataPtr) LDC_DGN_RESP._c /* ID: 0x0000076b, Handle: 0, LDC_DGN_RESP [BC] */, 
  (TxDataPtr) LDC_PCAN_STS._c /* ID: 0x00000563, Handle: 1, LDC_PCAN_STS [BC] */, 
  (TxDataPtr) LDC_3A1h._c /* ID: 0x000003a1, Handle: 2, LDC_3A1h [BC] */, 
  (TxDataPtr) LDC_3A0h._c /* ID: 0x000003a0, Handle: 3, LDC_3A0h [BC] */
};
/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_PRETRANSMIT_FCT
/* ROM CATEGORY 1 START */
/* PRQA  S 1334 QAC_Can_1334 */ /* MD_Can_1334 */
V_MEMROM0 V_MEMROM1 ApplPreTransmitFct V_MEMROM2 CanTxApplPreTransmitPtr[kCanNumberOfTxObjects] = 
{
  V_NULL /* ID: 0x0000076b, Handle: 0, LDC_DGN_RESP [BC] */, 
  V_NULL /* ID: 0x00000563, Handle: 1, LDC_PCAN_STS [BC] */, 
  V_NULL /* ID: 0x000003a1, Handle: 2, LDC_3A1h [BC] */, 
  V_NULL /* ID: 0x000003a0, Handle: 3, LDC_3A0h [BC] */
};
/* PRQA  L:QAC_Can_1334 */

/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_CONFIRMATION_FCT
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 ApplConfirmationFct V_MEMROM2 CanTxApplConfirmationPtr[kCanNumberOfTxObjects] = 
{
  TpDrvConfirmation /* ID: 0x0000076b, Handle: 0, LDC_DGN_RESP [BC] */, 
  V_NULL /* ID: 0x00000563, Handle: 1, LDC_PCAN_STS [BC] */, 
  V_NULL /* ID: 0x000003a1, Handle: 2, LDC_3A1h [BC] */, 
  V_NULL /* ID: 0x000003a0, Handle: 3, LDC_3A0h [BC] */
};
/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_PART_OFFLINE
/* ROM CATEGORY 2 START */

V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanTxSendMask[kCanNumberOfTxObjects] = 
{
  (vuint8) C_SEND_GRP_NONE /* ID: 0x0000076b, Handle: 0, LDC_DGN_RESP [BC] */, 
  (vuint8) C_SEND_GRP_APPL /* ID: 0x00000563, Handle: 1, LDC_PCAN_STS [BC] */, 
  (vuint8) C_SEND_GRP_APPL /* ID: 0x000003a1, Handle: 2, LDC_3A1h [BC] */, 
  (vuint8) C_SEND_GRP_APPL /* ID: 0x000003a0, Handle: 3, LDC_3A0h [BC] */
};

/* ROM CATEGORY 2 END */

#endif


#ifdef C_ENABLE_CONFIRMATION_FLAG
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanConfirmationOffset[kCanNumberOfTxObjects] = 
{
  0 /* ID: 0x0000076b, Handle: 0, LDC_DGN_RESP [BC] */, 
  0 /* ID: 0x00000563, Handle: 1, LDC_PCAN_STS [BC] */, 
  0 /* ID: 0x000003a1, Handle: 2, LDC_3A1h [BC] */, 
  0 /* ID: 0x000003a0, Handle: 3, LDC_3A0h [BC] */
};
/* ROM CATEGORY 1 END */


/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanConfirmationMask[kCanNumberOfTxObjects] = 
{
  0x00u /* ID: 0x0000076b, Handle: 0, LDC_DGN_RESP [BC] */, 
  0x01u /* ID: 0x00000563, Handle: 1, LDC_PCAN_STS [BC] */, 
  0x02u /* ID: 0x000003a1, Handle: 2, LDC_3A1h [BC] */, 
  0x04u /* ID: 0x000003a0, Handle: 3, LDC_3A0h [BC] */
};
/* ROM CATEGORY 1 END */


#endif




/* Id table depending on search algorithm */
/* Linear search */
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 tCanRxId0 V_MEMROM2 CanRxId0[kCanNumberOfRxObjects] = 
{
  MK_STDID0(0x1D2u) /* ID: 0x000001d2, Handle: 2, VCU_1D2h [BC] */, 
  MK_STDID0(0x763u) /* ID: 0x00000763, Handle: 3, LDC_DGN_REQ [FC] */, 
  MK_STDID0(0x700u) /* ID: 0x00000700, Handle: 4, DIAG_FUNC_REQ [FC] */, 
  MK_STDID0(0x3ACu) /* ID: 0x000003ac, Handle: 0, VCU_3ACh [FC] */, 
  MK_STDID0(0x245u) /* ID: 0x00000245, Handle: 1, VCU_245h [FC] */
};
/* ROM CATEGORY 1 END */


/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 CanReceiveHandle V_MEMROM2 CanRxMsgIndirection[kCanNumberOfRxObjects] = 
{
  2 /* ID: 0x000001d2, Handle: 2, VCU_1D2h */, 
  3 /* ID: 0x00000763, Handle: 3, LDC_DGN_REQ */, 
  4 /* ID: 0x00000700, Handle: 4, DIAG_FUNC_REQ */, 
  0 /* ID: 0x000003ac, Handle: 0, VCU_3ACh */, 
  1 /* ID: 0x00000245, Handle: 1, VCU_245h */
};
/* ROM CATEGORY 1 END */


/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanRxDataLen[kCanNumberOfRxObjects] = 
{
  2 /* ID: 0x000003ac, Handle: 0, VCU_3ACh [FC] */, 
  4 /* ID: 0x00000245, Handle: 1, VCU_245h [FC] */, 
  2 /* ID: 0x000001d2, Handle: 2, VCU_1D2h [BC] */, 
  8 /* ID: 0x00000763, Handle: 3, LDC_DGN_REQ [FC] */, 
  8 /* ID: 0x00000700, Handle: 4, DIAG_FUNC_REQ [FC] */
};
/* ROM CATEGORY 1 END */


#ifdef C_ENABLE_COPY_RX_DATA
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 RxDataPtr V_MEMROM2 CanRxDataPtr[kCanNumberOfRxObjects] = 
{
  (RxDataPtr) VCU_3ACh._c /* ID: 0x000003ac, Handle: 0, VCU_3ACh [FC] */, 
  (RxDataPtr) VCU_245h._c /* ID: 0x00000245, Handle: 1, VCU_245h [FC] */, 
  (RxDataPtr) VCU_1D2h._c /* ID: 0x000001d2, Handle: 2, VCU_1D2h [BC] */, 
  (RxDataPtr) 0 /* ID: 0x00000763, Handle: 3, LDC_DGN_REQ [FC] */, 
  (RxDataPtr) 0 /* ID: 0x00000700, Handle: 4, DIAG_FUNC_REQ [FC] */
};
/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_PRECOPY_FCT
/* CODE CATEGORY 1 START */
/* CODE CATEGORY 1 END */

/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 ApplPrecopyFct V_MEMROM2 CanRxApplPrecopyPtr[kCanNumberOfRxObjects] = 
{
  V_NULL /* ID: 0x000003ac, Handle: 0, VCU_3ACh [FC] */, 
  IlMsgVCU_245hPreCopy /* ID: 0x00000245, Handle: 1, VCU_245h [FC] */, 
  IlMsgVCU_1D2hPreCopy /* ID: 0x000001d2, Handle: 2, VCU_1D2h [BC] */, 
  TpPrecopy /* ID: 0x00000763, Handle: 3, LDC_DGN_REQ [FC] */, 
  TpFuncPrecopy /* ID: 0x00000700, Handle: 4, DIAG_FUNC_REQ [FC] */
};
/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_INDICATION_FCT
/* ROM CATEGORY 1 START */
/* PRQA  S 1334 QAC_Can_1334 */ /* MD_Can_1334 */
V_MEMROM0 V_MEMROM1 ApplIndicationFct V_MEMROM2 CanRxApplIndicationPtr[kCanNumberOfRxObjects] = 
{
  V_NULL /* ID: 0x000003ac, Handle: 0, VCU_3ACh [FC] */, 
  IlMsgVCU_245hIndication /* ID: 0x00000245, Handle: 1, VCU_245h [FC] */, 
  IlMsgVCU_1D2hIndication /* ID: 0x000001d2, Handle: 2, VCU_1D2h [BC] */, 
  V_NULL /* ID: 0x00000763, Handle: 3, LDC_DGN_REQ [FC] */, 
  V_NULL /* ID: 0x00000700, Handle: 4, DIAG_FUNC_REQ [FC] */
};
/* PRQA  L:QAC_Can_1334 */

/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_INDICATION_FLAG
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanIndicationOffset[kCanNumberOfRxObjects] = 
{
  0 /* ID: 0x000003ac, Handle: 0, VCU_3ACh [FC] */, 
  0 /* ID: 0x00000245, Handle: 1, VCU_245h [FC] */, 
  0 /* ID: 0x000001d2, Handle: 2, VCU_1D2h [BC] */, 
  0 /* ID: 0x00000763, Handle: 3, LDC_DGN_REQ [FC] */, 
  0 /* ID: 0x00000700, Handle: 4, DIAG_FUNC_REQ [FC] */
};
/* ROM CATEGORY 1 END */


/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanIndicationMask[kCanNumberOfRxObjects] = 
{
  0x00u /* ID: 0x000003ac, Handle: 0, VCU_3ACh [FC] */, 
  0x00u /* ID: 0x00000245, Handle: 1, VCU_245h [FC] */, 
  0x00u /* ID: 0x000001d2, Handle: 2, VCU_1D2h [BC] */, 
  0x00u /* ID: 0x00000763, Handle: 3, LDC_DGN_REQ [FC] */, 
  0x00u /* ID: 0x00000700, Handle: 4, DIAG_FUNC_REQ [FC] */
};
/* ROM CATEGORY 1 END */


#endif




/* -----------------------------------------------------------------------------
    &&&~ Init structures
 ----------------------------------------------------------------------------- */

/* ROM CATEGORY 4 START */
/* PRQA S 3408 1 */ /* MD_Can_3408_extLinkage */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanInitObjectStartIndex[2] = 
{
  0, 
  1
};

/* ROM CATEGORY 4 END */

/* ROM CATEGORY 4 START */
V_MEMROM0 V_MEMROM1 tCanInitObject V_MEMROM2 CanInitObject[1] = 
{
  
  {
    (vuint8) 0x20 /* Control register 0 */, 
    (vuint8) 0x06 /* Control register 1 */, 
    (vuint8) 0xBB /* Control register 2 */, 
    (vuint8) 0x01 /* Prescaler divider register */
  }
};

V_MEMROM0 V_MEMROM1 tCanInitBasicCan V_MEMROM2 CanInitBasicCan[1][1] = 
{
  
  {
    
    {
      (vuint16) 0x1FFF /* Mask Register High */, 
      (vuint16) 0xFFFF /* Mask Register Low */, 
      (vuint16) 0x074B /* Code Register High */, 
      (vuint16) 0xFFFF /* Code Register Low */
    }
  }
};

/* ROM CATEGORY 4 END */



#if defined(C_ENABLE_MULTI_ECU_CONFIG)
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanPhysToLogChannel[kVNumberOfIdentities][kCanNumberOfPhysChannels] = 
{
  
  {
    0
  }
};
/* ROM CATEGORY 1 END */

#endif

#if defined(C_ENABLE_MULTI_ECU_CONFIG)
/* ROM CATEGORY 2 START */

V_MEMROM0 V_MEMROM1 tVIdentityMsk V_MEMROM2 CanChannelIdentityAssignment[kCanNumberOfChannels] = 
{
  0x01u
};

/* ROM CATEGORY 2 END */

#endif

#if defined(C_ENABLE_MULTI_ECU_PHYS)
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 tVIdentityMsk V_MEMROM2 CanRxIdentityAssignment[kCanNumberOfRxObjects] = 
{
  0x01u /* ID: 0x000003ac, Handle: 0, VCU_3ACh [FC] */, 
  0x01u /* ID: 0x00000245, Handle: 1, VCU_245h [FC] */, 
  0x01u /* ID: 0x000001d2, Handle: 2, VCU_1D2h [BC] */, 
  0x01u /* ID: 0x00000763, Handle: 3, LDC_DGN_REQ [FC] */, 
  0x01u /* ID: 0x00000700, Handle: 4, DIAG_FUNC_REQ [FC] */
};
/* ROM CATEGORY 1 END */

/* ROM CATEGORY 4 START */
V_MEMROM0 V_MEMROM1 tVIdentityMsk V_MEMROM2 CanTxIdentityAssignment[kCanNumberOfTxObjects] = 
{
  0x01u /* ID: 0x0000076b, Handle: 0, LDC_DGN_RESP [BC] */, 
  0x01u /* ID: 0x00000563, Handle: 1, LDC_PCAN_STS [BC] */, 
  0x01u /* ID: 0x000003a1, Handle: 2, LDC_3A1h [BC] */, 
  0x01u /* ID: 0x000003a0, Handle: 3, LDC_3A0h [BC] */
};
/* ROM CATEGORY 4 END */

#endif



#ifdef C_ENABLE_TX_FULLCAN_OBJECTS
/* ROM CATEGORY 2 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanTxHwObj[kCanNumberOfTxObjects] = 
{
  (vuint8) 31 /* ID: 0x76b, Handle: 0 */, 
  (vuint8) 31 /* ID: 0x563, Handle: 1 */, 
  (vuint8) 31 /* ID: 0x3a1, Handle: 2 */, 
  (vuint8) 31 /* ID: 0x3a0, Handle: 3 */
};
/* ROM CATEGORY 2 END */

#endif



/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 345877849
      #error "The magic number of the generated file <D:\07_Working\E100\source\BSW\CANbedded_Vector\can_par.c> is different. Please check time and date of generated files!"
  #endif
#else
  #error "The magic number is not defined in the generated file <D:\07_Working\E100\source\BSW\CANbedded_Vector\can_par.c> "

#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

