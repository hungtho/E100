/************************************************************************
*            (c) Copyright Freescale Semiconductor, 2011                *
*                        All Rights Reserved                            *
*************************************************************************

*************************************************************************
*                                                                       *
*   Freescale reserves the right to make changes without further notice *
*   to any product herein to improve reliability, function or design.   *
*   Freescale does not assume any liability arising out of the          *
*   application or use of any product, circuit, or software described   *
*   herein; neither does it convey any license under its patent rights  *
*   nor the rights of others.                                           *
*                                                                       *
*   Freescale products are not designed, intended, or authorized for    *
*   use as components in systems intended for surgical implant into     *
*   the body, or other applications intended to support life, or for    *
*   any other application in which the failure of the Freescale product *
*   could create a situation where personal injury or death may occur.  *
*                                                                       *
*   Should Buyer purchase or use Freescale products for any such        *
*   unintended or unauthorized application, Buyer shall indemnify and   *
*   hold Freescale and its officers, employees, subsidiaries,           *
*   affiliates, and distributors harmless against all claims costs,     *
*   damages, and expenses, and reasonable attorney fees arising out     *
*   of, directly or indirectly, any claim of personal injury or death   *
*   associated with such unintended or unauthorized use, even if such   *
*   claim alleges that Freescale was negligent regarding the design     *
*   or manufacture of the part.                                         *
*                                                                       *
*   Freescale and the Freescale logo* are registered trademarks of      *
*   Freescale Semicondutor, Inc.                                        *
*                                                                       *
*************************************************************************

*************************************************************************
*                                                                       *
*               Standard Software Driver for C55                        *
*                                                                       *
* FILE NAME     :  ssd_c55.h                                            *
* DATE          :  December 19, 2011                                    *
* AUTHOR        :  FPT Team                                             *
* E-mail        :  r56611@freescale.com                                 *
*                                                                       *
*************************************************************************/
/****************************************************************************
*
* Copyright © 2012-2019 STMicroelectronics - All Rights Reserved
*
* License terms: STMicroelectronics Proprietary in accordance with licensing
* terms SLA0089 at www.st.com.
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* EVALUATION ONLY – NOT FOR USE IN PRODUCTION
*****************************************************************************/
/******************************* CHANGES *********************************
  0.1.0   12.19.2011         FPT Team      Initial Version
  0.1.2   01.17.2012         FPT Team      Removed C55_ERROR_RANGE and
                                           SSD_CONFIG.uTestArraySize 
  0.1.3   02.06.2012         FPT Team      Changed prototype of
                                           FlashCheckStatus 
  0.1.4	  02.24.2012         Chen He       Moved pReqCompletionFn to CONTEXT_DATA 
                                           to be compiler independent
  0.1.5   03.23.2011         FPT Team      Update values of macros for suspend
                                           operation, resume operation and 
                                           user's test mode and returnCode
                                           returned within FlashCheckStatus()
*************************************************************************/

#ifndef _SSD_C55_H_
#define _SSD_C55_H_

#include "ssd_types.h"

/*************************************************************************/
/*                       Compiler select macros                          */
/*************************************************************************/
#define CODE_WARRIOR        0x00UL
#define DIAB_COMPILER       0x01UL
#define GREEN_HILLS         0x02UL

/*************************************************************************/
/*                  Offsets of C55 Control Registers                     */
/*************************************************************************/
#define C55_MCR             0x0000UL       /* Module Configuration Register */
#define C55_MCRA            0x0004UL       /* Alternate Module Configuration Register */
#define C55_MCRE            0x0008UL       /* Extended Module Configuration Register */
#define C55_LOCK0           0x0010UL       /* Lock 0 Register */
#define C55_LOCK1           0x0014UL       /* Lock 1 Register */
#define C55_LOCK2           0x0018UL       /* Lock 2 Register */
#define C55_LOCK3           0x001CUL       /* Lock 3 Register */
#define C55_LOCK0A          0x0028UL       /* Alternate Lock 0 Register */
#define C55_LOCK1A          0x002CUL       /* Alternate Lock 1 Register */
#define C55_SEL0            0x0038UL       /* Select 0 Register */
#define C55_SEL1            0x003CUL       /* Select 1 Register */
#define C55_SEL2            0x0040UL       /* Select 2 Register */
#define C55_SEL3            0x0044UL       /* Select 3 Register */
#define C55_ADR             0x0050UL       /* Address Register */
#define C55_UT0             0x0054UL       /* User Test 0 register */
#define C55_UM0             0x0058UL       /* User MISR 0 Register */
#define C55_UM1             0x005CUL       /* User MISR 1 Register */
#define C55_UM2             0x0060UL       /* User MISR 2 Register */
#define C55_UM3             0x0064UL       /* User MISR 3 Register */
#define C55_UM4             0x0068UL       /* User MISR 4 Register */
#define C55_UM5             0x006CUL       /* User MISR 5 Register */
#define C55_UM6             0x0070UL       /* User MISR 6 Register */
#define C55_UM7             0x0074UL       /* User MISR 7 Register */
#define C55_UM8             0x0078UL       /* User MISR 8 Register */
#define C55_UM9             0x007CUL       /* User MISR 9 Register */
#define C55_OPP0            0x0080UL       /* Over-Program Protection 0 Register */
#define C55_OPP1            0x0084UL       /* Over-Program Protection 1 Register */
#define C55_OPP2            0x0088UL       /* Over-Program Protection 2 Register */
#define C55_OPP3            0x008CUL       /* Over-Program Protection 3 Register */

/*************************************************************************/
/*              C55 Module Control Registers Field Definitions           */
/*************************************************************************/
/* Module Configuration Register */
#define C55_MCR_RVE         0x80000000UL   /* Read Voltage Error */
#define C55_MCR_RRE         0x40000000UL   /* Read Reference Error */
#define C55_MCR_AEE         0x20000000UL   /* Address Encode Error */
#define C55_MCR_EEE         0x10000000UL   /* ECC after ECC Error */
#define C55_MCR_EER         0x00008000UL   /* ECC Event Error */
#define C55_MCR_RWE         0x00004000UL   /* Read While Write Event Error */
#define C55_MCR_SBC         0x00002000UL   /* Single Bit Correction Error */
#define C55_MCR_PEAS        0x00000800UL   /* Program/Erase Access Space */
#define C55_MCR_DONE        0x00000400UL   /* State Machine Status */
#define C55_MCR_PEG         0x00000200UL   /* Program/Erase Good */
#define C55_MCR_PECIE       0x00000100UL   /* Program/Erase Complete Interrupt Enable */
#define C55_MCR_FERS        0x00000080UL   /* Factory Erase */
#define C55_MCR_PGM         0x00000010UL   /* Program */
#define C55_MCR_PSUS        0x00000008UL   /* Program Suspend */
#define C55_MCR_ERS         0x00000004UL   /* Erase */
#define C55_MCR_ESUS        0x00000002UL   /* Erase Suspend */
#define C55_MCR_EHV         0x00000001UL   /* Enable High Voltage */

/* User Test 0 Register */
#define C55_UT0_UTE         0x80000000UL
#define C55_UT0_SBCE        0x40000000UL
#define C55_UT0_NAIBP       0x00000200UL
#define C55_UT0_AIBPE       0x00000100UL
#define C55_UT0_AISUS       0x00000040UL
#define C55_UT0_MRE         0x00000020UL
#define C55_UT0_MRV         0x00000010UL
#define C55_UT0_AIS         0x00000004UL
#define C55_UT0_AIE         0x00000002UL
#define C55_UT0_AID         0x00000001UL

/*************************************************************************/
/*                   Return Codes for SSD functions                      */
/*************************************************************************/

#define C55_OK                      0x00000000UL
#define C55_ERROR_ALIGNMENT         0x00000001UL   /* Alignment error */
#define C55_ERROR_BUSY              0x00000004UL   /* New program/erase cannot be preformed while previous high voltage operation in progress */
#define C55_ERROR_PGOOD             0x00000008UL   /* The program operation is unsuccessful */
#define C55_ERROR_EGOOD             0x00000010UL   /* The erase operation is unsuccessful */
#define C55_ERROR_NOT_BLANK         0x00000020UL   /* There is non-blank location in the checked flash memory */
#define C55_ERROR_VERIFY            0x00000040UL   /* There is a mismatch between the source data and content in the checked flash memory */
#define C55_ERROR_BLOCK_INDICATOR   0x00000080UL   /* Invalid block indicator */
#define C55_ERROR_ALTERNATE         0x00000100UL   /* The operation is unsupported via alternate interface */
#define C55_ERROR_FACTORY_OP        0x00000200UL   /* Factory erase/program cannot be performed */
#define C55_ERROR_MISMATCH          0x00000400UL   /* The MISR generated by the AIC hardware doesnot match the MISR passed by the user */
#define C55_ERROR_NO_BLOCK          0x00000800UL   /* No blocks have been enabled for Array Integrity check */
#define C55_ERROR_ADDR_SEQ          0x00001000UL   /* Invalid address sequence */
#define C55_ERROR_MARGIN_LEVEL      0x00002000UL   /* Invalid margin level */
#define C55_ERROR_ERASE_OPTION      0x00004000UL   /* Invalid erase option */
#define C55_ERROR_MODE_OP           0x00008000UL   /* Invalid mode op */

#define C55_DONE                    0x00010000UL   /* Done status */
#define C55_INPROGRESS              0x00020000UL   /* InProgress status */

/*************************************************************************/
/*            Predefined values for flags, options variables             */
/*************************************************************************/

/* Checking mode used in FlashCheckStatus */
#define C55_MODE_OP_PROGRAM         0x00U
#define C55_MODE_OP_ERASE           0x01U
#define C55_MODE_OP_PROGRAM_VERIFY  0x02U
#define C55_MODE_OP_BLANK_CHECK     0x03U
#define C55_MODE_OP_CHECK_SUM       0x04U
#define C55_MODE_OP_USER_TEST_CHECK 0x05U

/* Indicators for getting/setting block lock state */
#define C55_BLOCK_LOW               0x00U  /* Block lock protection of low address space */
#define C55_BLOCK_MID               0x01U  /* Block lock protection of mid address space */
#define C55_BLOCK_HIGH              0x02U  /* Block lock protection of high address space */
#define C55_BLOCK_LARGE_FIRST       0x03U  /* Block lock protection of first 32 blocks in LARGE address space */
#define C55_BLOCK_LARGE_SECOND      0x04U  /* Block lock protection of next 16 blocks in LARGE address space */
#define C55_BLOCK_UTEST             0x05U  /* Block lock protection of UTest address space */

/* Declarations for flash suspend operation */
#define C55_SUS_NOTHING             0x10U   /* No program/erase operation */
#define C55_PGM_WRITE               0x11U   /* A program sequence in interlock write stage. */
#define C55_ERS_WRITE               0x12U   /* An erase sequence in interlock write stage. */
#define C55_ERS_SUS_PGM_WRITE       0x13U   /* An erase-suspend program sequence in interlock write stage. */
#define C55_PGM_SUS                 0x14U   /* The program operation is in suspend state */
#define C55_ERS_SUS                 0x15U   /* The erase operation is in suspend state */
#define C55_ERS_SUS_PGM_SUS         0x16U   /* The erase-suspended program operation is in suspend state */
#define C55_USER_TEST_SUS           0x17U   /* The UTest check operation is in suspend state */

/* Declarations for flash resume operation */
#define C55_RES_NOTHING             0x20U  /* No suspended program/erase operation */
#define C55_RES_PGM                 0x21U  /* The program operation is resumed */
#define C55_RES_ERS                 0x22U  /* The erase operation is resumed */
#define C55_RES_ERS_PGM             0x23U  /* The erase-suspended program operation is resumed */
#define C55_RES_USER_TEST           0x24U  /* The UTest check operation is resumed */

#define C55_USER_TEST_BREAK_SBC     0x30U   /* The UTest check operation is broken by Single bit correction */
#define C55_USER_TEST_BREAK_DBD     0x31U   /* The UTest check operation is broken by Double bit detection */

/* Declarations of margin levels */
#define C55_MARGIN_LEVEL_PROGRAM    0x00U
#define C55_MARGIN_LEVEL_ERASE      0x01U

/* Declarations of address sequences */
#define C55_ADDR_SEQ_PROPRIETARY    0x00U
#define C55_ADDR_SEQ_LINEAR         0x01U

/* Declarations of break options */
#define C55_BREAK_NONE              0x00U   /* No break at all */
#define C55_BREAK_ON_DBD            0x01U   /* Break on Double bit detection */
#define C55_BREAK_ON_DBD_SBC        0x02U   /* Break on bot Double bit detection and Single bit correction */

/* Declarations of erase options */
#define C55_ERASE_MAIN              0x00U   /* Perform normal erase on main array */
#define C55_ERASE_MAIN_FERS         0x01U   /* Perform factory erase on main array */
#define C55_ERASE_UTEST             0x02U   /* Perform erase on UTest array */
#define C55_ERASE_UTEST_FERS        0x03U   /* Perform factory erase on UTest array */

/*************************************************************************/
/*                   Other Macros for SSD functions                      */
/*************************************************************************/

#define C55_WORD_SIZE               4UL      /* size of a word in byte */
#define C55_DWORD_SIZE              8UL      /* size of a double word in byte */

#define C55_USER_TEST_ENABLE_PASSWORD      0xF9F99999UL
#define C55_FACTORY_ERASE_DIARY_LOCATION   0x0020UL

#define NULL_POINTER                ((void *)0xFFFFFFFFUL)

/* Macros for Accessing the Registers */
#define C55_REG_BIT_SET(address, mask)        (*(VUINT32*)(address) |= (mask))
#define C55_REG_BIT_CLEAR(address, mask)      (*(VUINT32*)(address) &= ~(mask))
#define C55_REG_BIT_TEST(address, mask)       (*(VUINT32*)(address) & (mask))
#define C55_REG_WRITE(address, value)         (*(VUINT32*)(address) = (value))
#define C55_REG_READ(address)                 ((UINT32)(*(VUINT32*)(address)))
#define C55_GET_BIT(value, position)          (UINT8)(((value) >> (position)) & 0x01)

/* Set/Clear C55-MCR bits without affecting MCR-EER, MCR-RWE, and MCR-SBC */
#define C55_MCR_BIT_SET(MCRAddress, mask)      \
    C55_REG_WRITE(MCRAddress, ((mask | C55_REG_READ(MCRAddress)) & (~(C55_MCR_EER | C55_MCR_RWE | C55_MCR_SBC))))

#define C55_MCR_BIT_CLEAR(MCRAddress, mask)    \
    C55_REG_WRITE(MCRAddress, (((~mask) & C55_REG_READ(MCRAddress)) & (~(C55_MCR_EER | C55_MCR_RWE | C55_MCR_SBC))))

#define C55_MCR_EER_CLEAR(MCRAddress)    \
    C55_REG_WRITE(MCRAddress, (C55_REG_READ(MCRAddress) | C55_MCR_RWE | C55_MCR_SBC))
    
#define C55_MCR_RWE_CLEAR(MCRAddress)    \
    C55_REG_WRITE(MCRAddress, (C55_REG_READ(MCRAddress) | C55_MCR_EER | C55_MCR_SBC))
    
#define C55_MCR_SBC_CLEAR(MCRAddress)    \
    C55_REG_WRITE(MCRAddress, (C55_REG_READ(MCRAddress) | C55_MCR_EER | C55_MCR_RWE))
    
#define C55_MCR_EER_RWE_SBC_CLEAR(MCRAddress)    \
    C55_REG_WRITE(MCRAddress, (C55_REG_READ(MCRAddress) | C55_MCR_EER | C55_MCR_RWE | C55_MCR_SBC))

#define C55_MAIN_ARRAY_SIZE(pSSDConfig)    \
    ((((pSSDConfig->lowBlockInfo.n8KBlockNum + pSSDConfig->midBlockInfo.n8KBlockNum + \
    pSSDConfig->highBlockInfo.n8KBlockNum) << 3 /*8*/) + \
	((pSSDConfig->lowBlockInfo.n16KBlockNum + pSSDConfig->midBlockInfo.n16KBlockNum + \
    pSSDConfig->highBlockInfo.n16KBlockNum) << 4 /*16*/) + \
    ((pSSDConfig->lowBlockInfo.n32KBlockNum + pSSDConfig->midBlockInfo.n32KBlockNum + \
    pSSDConfig->highBlockInfo.n32KBlockNum) << 5 /*32*/) + \
    ((pSSDConfig->lowBlockInfo.n64KBlockNum + pSSDConfig->midBlockInfo.n64KBlockNum + \
    pSSDConfig->highBlockInfo.n64KBlockNum) << 6 /*64*/) + \
    (pSSDConfig->nLargeBlockNum << 8)) << 10 /*1024*/)

#define C55_LOW_BLOCK_NUM(pSSDConfig)     \
    (pSSDConfig->lowBlockInfo.n16KBlockNum + pSSDConfig->lowBlockInfo.n32KBlockNum +  \
    pSSDConfig->lowBlockInfo.n64KBlockNum + pSSDConfig->lowBlockInfo.n8KBlockNum)
    
#define C55_MID_BLOCK_NUM(pSSDConfig)     \
    (pSSDConfig->midBlockInfo.n16KBlockNum + pSSDConfig->midBlockInfo.n32KBlockNum +  \
    pSSDConfig->midBlockInfo.n64KBlockNum + pSSDConfig->midBlockInfo.n8KBlockNum)

#define C55_HIGH_BLOCK_NUM(pSSDConfig)     \
    (pSSDConfig->highBlockInfo.n16KBlockNum + pSSDConfig->highBlockInfo.n32KBlockNum +  \
    pSSDConfig->highBlockInfo.n64KBlockNum + pSSDConfig->highBlockInfo.n8KBlockNum)
    
/*************************************************************************/
/*                   SSD Configuration Structure                         */
/*************************************************************************/

/* Block information for an address space */
typedef struct _c55_block_info
{
    UINT32 n8KBlockNum;			 /* Number of 8K blocks */
	UINT32 n16KBlockNum;         /* Number of 16K blocks */
    UINT32 n32KBlockNum;         /* Number of 32K blocks */
    UINT32 n64KBlockNum;         /* Number of 64K blocks */
} BLOCK_INFO, *PBLOCK_INFO;

/* SSD Configuration Structure */
typedef struct _c55_ssd_config
{
    UINT32 c55RegBase;           /* C55 control register base */
    UINT32 mainArrayBase;        /* base of main array */
    BLOCK_INFO lowBlockInfo;     /* blocks info of low address space */
    BLOCK_INFO midBlockInfo;     /* blocks info of mid address space */
    BLOCK_INFO highBlockInfo;    /* blocks info of high address space */
    UINT32 nLargeBlockNum;       /* number of blocks in Large address space */
    UINT32 uTestArrayBase;       /* base of UTEST array */
    BOOL mainInterfaceFlag;      /* interface flag indicate main or alternate interface */
    UINT32 programmableSize;     /* programmable size */
    BOOL BDMEnable;              /* debug mode selection */
} SSD_CONFIG, *PSSD_CONFIG;

/* MISR structure */
typedef struct _c55_misr
{
    UINT32 W0;
    UINT32 W1;
    UINT32 W2;
    UINT32 W3;
    UINT32 W4;
    UINT32 W5;
    UINT32 W6;
    UINT32 W7;
    UINT32 W8;
    UINT32 W9;
} MISR, *PMISR;

/* Structure data for the context values */
typedef struct _c55_context_data
{
    UINT32 dest;
    UINT32 size;
    UINT32 source;
    UINT32 *pFailedAddress;
    UINT32 *pFailedData;
    UINT32 *pFailedSource;
    UINT32 *pSum;
    PMISR pMisr;
    void* pReqCompletionFn;
} CONTEXT_DATA, *PCONTEXT_DATA;

/* Block select structure for Large address space */
typedef struct _c55_nLarge_block_sel
{
    UINT32 firstLargeBlockSelect;
    UINT32 secondLargeBlockSelect;
} NLARGE_BLOCK_SEL, *PNLARGE_BLOCK_SEL;

/*************************************************************************/
/*                      Prototypes of wrapper SSD Functions              */
/*************************************************************************/

extern UINT32 FlashInit ( PSSD_CONFIG pSSDConfig );

extern UINT32 FlashErase ( PSSD_CONFIG pSSDConfig,
                    UINT8 eraseOption,
                    UINT32 lowBlockSelect,
                    UINT32 midBlockSelect,
                    UINT32 highBlockSelect,
                    NLARGE_BLOCK_SEL nLargeBlockSelect
                    );

extern UINT32 FlashEraseAlternate ( PSSD_CONFIG pSSDConfig,
                    UINT32 interlockAddress
                    );

extern UINT32 BlankCheck ( PSSD_CONFIG pSSDConfig,
                    UINT32 dest,
                    UINT32 size,
                    UINT32 *pFailedAddress,
                    UINT32 *pFailedData,
                    PCONTEXT_DATA pCtxData
                    );

extern UINT32 FlashProgram ( PSSD_CONFIG pSSDConfig,
                    BOOL factoryPgmFlag,
                    UINT32 dest,
                    UINT32 size,
                    UINT32 source,
                    PCONTEXT_DATA pCtxData
                    );

extern UINT32 ProgramVerify ( PSSD_CONFIG pSSDConfig,
                    UINT32 dest,
                    UINT32 size,
                    UINT32 source,
                    UINT32 *pFailedAddress,
                    UINT32 *pFailedData,
                    UINT32 *pFailedSource,
                    PCONTEXT_DATA pCtxData
                    );

extern UINT32 FlashCheckStatus ( PSSD_CONFIG pSSDConfig,
                    UINT8 modeOp,
                    UINT32 *opResult,
                    PCONTEXT_DATA pCtxData
                    );

extern UINT32 GetLock ( PSSD_CONFIG pSSDConfig,
                    UINT8 blkLockIndicator,
                    UINT32 *blkLockState
                    );

extern UINT32 SetLock ( PSSD_CONFIG pSSDConfig,
                    UINT8 blkLockIndicator,
                    UINT32 blkLockState
                    );

extern UINT32 OverPgmProtGetStatus ( PSSD_CONFIG pSSDConfig,
                    UINT8 blkProtIndicator,
                    UINT32 *blkProtState
                    );

extern UINT32 CheckSum ( PSSD_CONFIG pSSDConfig,
                    UINT32 dest,
                    UINT32 size,
                    UINT32 *pSum,
                    PCONTEXT_DATA pCtxData
                    );

extern UINT32 FlashSuspend ( PSSD_CONFIG pSSDConfig,
                    UINT8 *suspendState
                    );

extern UINT32 FlashResume ( PSSD_CONFIG pSSDConfig,
                    UINT8 *resumeState
                    );

extern UINT32 FlashArrayIntegrityCheck ( PSSD_CONFIG pSSDConfig,
                    UINT32 lowEnabledBlocks,
                    UINT32 midEnabledBlocks,
                    UINT32 highEnabledBlocks,                    
		    NLARGE_BLOCK_SEL nLargeEnabledBlocks,
                    UINT8 breakOption,
                    UINT8 addrSeq,
                    PMISR pMisrValue,
                    PCONTEXT_DATA pCtxData
                    );

extern UINT32 FlashArrayIntegritySuspend ( PSSD_CONFIG pSSDConfig,
                    UINT8 *suspendState
                    );

extern UINT32 FlashArrayIntegrityResume ( PSSD_CONFIG pSSDConfig,
                    UINT8 *resumeState
                    );

extern UINT32 UserMarginReadCheck ( PSSD_CONFIG pSSDConfig,
                    UINT32 lowEnabledBlocks,
                    UINT32 midEnabledBlocks,
                    UINT32 highEnabledBlocks,
		    NLARGE_BLOCK_SEL nLargeBlockSelect,
                    UINT8 breakOption,
                    UINT8 marginLevel,
                    PMISR pMisrValue,
                    PCONTEXT_DATA pCtxData
                    );

/*************************************************************************/
/*                      SSD Function Pointer Types                       */
/*************************************************************************/

typedef UINT32 (*PFLASHINIT) ( PSSD_CONFIG pSSDConfig );

typedef UINT32 (*PFLASHERASE) ( PSSD_CONFIG pSSDConfig,
                    UINT8 eraseOption,
                    UINT32 lowBlockSelect,
                    UINT32 midBlockSelect,
                    UINT32 highBlockSelect,
		    NLARGE_BLOCK_SEL nLargeBlockSelect                    
                    );

typedef UINT32 (*PFLASHERASEALTERNATE) ( PSSD_CONFIG pSSDConfig,
                    UINT32 interlockAddress
                    );

typedef UINT32 (*PBLANKCHECK) ( PSSD_CONFIG pSSDConfig,
                    UINT32 dest,
                    UINT32 size,
                    UINT32 *pFailedAddress,
                    UINT32 *pFailedData,
                    PCONTEXT_DATA pCtxData
                    );

typedef UINT32 (*PFLASHPROGRAM) ( PSSD_CONFIG pSSDConfig,
                    BOOL factoryPgmFlag,
                    UINT32 dest,
                    UINT32 size,
                    UINT32 source,
                    PCONTEXT_DATA pCtxData
                    );

typedef UINT32 (*PPROGRAMVERIFY) ( PSSD_CONFIG pSSDConfig,
                    UINT32 dest,
                    UINT32 size,
                    UINT32 source,
                    UINT32 *pFailedAddress,
                    UINT32 *pFailedData,
                    UINT32 *pFailedSource,
                    PCONTEXT_DATA pCtxData
                    );

typedef UINT32 (*PFLASHCHECKSTATUS) ( PSSD_CONFIG pSSDConfig,
                    UINT8 modeOp,
                    UINT32 *opResult,
                    PCONTEXT_DATA pCtxData
                    );

typedef UINT32 (*PGETLOCK) ( PSSD_CONFIG pSSDConfig,
                    UINT8 blkLockIndicator,
                    UINT32 *blkLockState
                    );

typedef UINT32 (*PSETLOCK) ( PSSD_CONFIG pSSDConfig,
                    UINT8 blkLockIndicator,
                    UINT32 blkLockState
                    );

typedef UINT32 (*POVERPGMPROTGETSTATUS) ( PSSD_CONFIG pSSDConfig,
                    UINT8 blkProtIndicator,
                    UINT32* blkProtState
                    );

typedef UINT32 (*PCHECKSUM) ( PSSD_CONFIG pSSDConfig,
                    UINT32 dest,
                    UINT32 size,
                    UINT32 *pSum,
                    PCONTEXT_DATA pCtxData
                    );

typedef UINT32 (*PFLASHSUSPEND) ( PSSD_CONFIG pSSDConfig,
                    UINT8 *suspendState
                    );

typedef UINT32 (*PFLASHRESUME) ( PSSD_CONFIG pSSDConfig,
                    UINT8 *resumeState
                    );

typedef UINT32 (*PFLASHARRAYINTEGRITYCHECK) ( PSSD_CONFIG pSSDConfig,
                    UINT32 lowEnabledBlocks,
                    UINT32 midEnabledBlocks,
                    UINT32 highEnabledBlocks,
		    NLARGE_BLOCK_SEL nLargeEnableBlocks,
                    UINT8 breakOption,
                    UINT8 addrSeq,
                    PMISR pMisrValue,
                    PCONTEXT_DATA pCtxData
                    );

typedef UINT32 (*PFLASHARRAYINTEGRITYSUSPEND) ( PSSD_CONFIG pSSDConfig,
                    UINT8 *suspendState
                    );

typedef UINT32 (*PFLASHARRAYINTEGRITYRESUME) ( PSSD_CONFIG pSSDConfig,
                    UINT8 *resumeState
                    );

typedef UINT32 (*PUSERMARGINREADCHECK) ( PSSD_CONFIG pSSDConfig,
                    UINT32 lowEnabledBlocks,
                    UINT32 midEnabledBlocks,
                    UINT32 highEnabledBlocks,
		    NLARGE_BLOCK_SEL nLargeEnableBlocks,
                    UINT8 breakOption,
                    UINT8 marginLevel,
                    PMISR pMisrValue,
                    PCONTEXT_DATA pCtxData
                    );

#endif /* _SSD_C55_H_ */
