/****************************************************************************
*
* Copyright © 2017-2019 STMicroelectronics - All Rights Reserved
*
* License terms: STMicroelectronics Proprietary in accordance with licensing
* terms SLA0089 at www.st.com.
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* EVALUATION ONLY – NOT FOR USE IN PRODUCTION
*****************************************************************************/

/**
 * @file    FlashMap.h
 * @brief   FlashMap for SPC570Sxx
 * @details See component documentation
 *
 *
 * @addtogroup SPC5_FLASH
 * @{
 */

#ifndef _FLASHMAP_H_
#define _FLASHMAP_H_

#define C55_REG_BASE                    0xFFFE0000UL
#define MAIN_ARRAY_BASE                 0x00404000UL
#define UTEST_ARRAY_BASE                0x00400000UL
#define UTEST_ARRAY_SIZE                0x00004000UL

#define C55_PROGRAMMABLE_SIZE           0x80UL

#define BUFFER_SIZE_BYTE                0x1000UL

/* Lock State */
#define LOCK_ALL_BLOCKS                 0xFFFFFFFFUL
#define UNLOCK_ALL_BLOCKS               0x00000000UL

/* FLASH sectorization */
/* Low space block 0 */
#define FLS_OFFSET_LOW_8K_BLOCK0        0x00404000UL  /* Offset of low block 0 */
#define FLS_SIZE_LOW_8K_BLOCK0          0x2000UL      /* 16KB size */

/* Low space block 1 */
#define FLS_OFFSET_LOW_16K_BLOCK1       0x00FC0000UL  /* Offset of low block 1 */
#define FLS_SIZE_LOW_16K_BLOCK1         0x4000UL      /* 16KB size */

/* Low space block 2 */
#define FLS_OFFSET_LOW_16K_BLOCK2       0x00FC4000UL  /* Offset of low block 2 */
#define FLS_SIZE_LOW_16K_BLOCK2         0x4000UL      /* 16KB size */

/* Low space block 3 */
#define FLS_OFFSET_LOW_16K_BLOCK3       0x00FC8000UL  /* Offset of low block 3 */
#define FLS_SIZE_LOW_16K_BLOCK3         0x4000UL      /* 16KB size */

/* Low space block 4 */
#define FLS_OFFSET_LOW_16K_BLOCK4       0x00FCC000UL  /* Offset of low block 4 */
#define FLS_SIZE_LOW_16K_BLOCK4         0x4000UL      /* 16KB size */

/* Low space block 5 */
#define FLS_OFFSET_LOW_32K_BLOCK5       0x00FD0000UL  /* Offset of low block 5 */
#define FLS_SIZE_LOW_32K_BLOCK5         0x8000UL      /* 32KB size */

/* Low space block 6 */
#define FLS_OFFSET_LOW_32K_BLOCK6       0x00FD8000UL  /* Offset of low block 6 */
#define FLS_SIZE_LOW_32K_BLOCK6         0x8000UL      /* 32KB size */

/* Low space block 7 */
#define FLS_OFFSET_LOW_64K_BLOCK7       0x00FE0000UL  /* Offset of low block 7 */
#define FLS_SIZE_LOW_64K_BLOCK7         0x10000UL      /* 64KB size */

/* Low space block 8 */
#define FLS_OFFSET_LOW_64K_BLOCK8       0x00FF0000UL  /* Offset of low block 8 */
#define FLS_SIZE_LOW_64K_BLOCK8         0x10000UL     /* 64KB size */

/* Large space block 0 */
#define FLS_OFFSET_128K_BLOCK9          0x01000000UL  /* Offset of large block 0 */
#define FLS_SIZE_128K_BLOCK9            0x20000UL     /* 128KB size */
                                        
/* Large space block 1 */               
#define FLS_OFFSET_128K_BLOCK10         0x01020000UL  /* Offset of large block 1 */
#define FLS_SIZE_128K_BLOCK10           0x20000UL     /* 128KB size */

/* High space block 0 */
#define FLS_OFFSET_HIGH_8K_BLOCK0       0x00800000UL  /* Offset of high block 0 */
#define FLS_SIZE_HIGH_8K_BLOCK0         0x2000UL      /* 8KB size */
                                       
/* High space block 1 */               
#define FLS_OFFSET_HIGH_8K_BLOCK1       0x00802000UL  /* Offset of high block 1 */
#define FLS_SIZE_HIGH_8K_BLOCK1         0x2000UL      /* 8KB size */
                                       
/* High space block 2 */               
#define FLS_OFFSET_HIGH_8K_BLOCK2       0x00804000UL  /* Offset of high block 2 */
#define FLS_SIZE_HIGH_8K_BLOCK2         0x2000UL      /* 8KB size */
                                       
/* High space block 3 */               
#define FLS_OFFSET_HIGH_8K_BLOCK3       0x00806000UL  /* Offset of high block 3 */
#define FLS_SIZE_HIGH_8K_BLOCK3         0x2000UL      /* 8KB size */

#define FLASH_ARRAY_SIZE                0x80000UL     /* Flash total size */


/* Prototype of error trap function */
void ErrorTrap(UINT32 returnCode);

/* Typedef for null callback */
typedef void (*tpfNullCallback)(void);

#endif

/** @} */
