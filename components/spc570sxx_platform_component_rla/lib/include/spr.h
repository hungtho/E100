/****************************************************************************
*
* Copyright © 2019 STMicroelectronics - All Rights Reserved
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
 * @file    spr.h
 * @brief   Special purpose registers header.
 */

#ifndef _SPR_H_
#define _SPR_H_

#ifdef __ghs__
#include <ppc_ghs.h>
#endif

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/**
 * @name    Special purpose register numbers
 * @{
 */
#define SPC5_SPR_XER         1    /* Integer Exception Register */
#define SPC5_SPR_LR          8    /* Link Register */
#define SPC5_SPR_CTR         9    /* Count Register */
#define SPC5_SPR_SRR0        26   /* Save/Restore Register 0 */
#define SPC5_SPR_SRR1        27   /* Save/Restore Register 1 */
#define SPC5_SPR_PID0        48   /* Process ID Register */
#define SPC5_SPR_CSRR0       58   /* Critical Save/Restore Register 0 */
#define SPC5_SPR_CSRR1       59   /* Critical Save/Restore Register 1 */
#define SPC5_SPR_DEAR        61   /* Data Exception Address Register */
#define SPC5_SPR_ESR         62   /* Exception Syndrome Register */
#define SPC5_SPR_IVPR        63   /* Interrupt Vector Prefix Register */
#define SPC5_SPR_SPRG0       272  /* SPR General 0 */
#define SPC5_SPR_SPRG1       273  /* SPR General 1 */
#define SPC5_SPR_SPRG2       274  /* SPR General 2 */
#define SPC5_SPR_SPRG3       275  /* SPR General 3 */
#define SPC5_SPR_PIR         286  /* Processor ID Register */
#define SPC5_SPR_PVR         287  /* Processor Version Register */
#define SPC5_SPR_DBSR        304  /* Debug Status Register */
#define SPC5_SPR_DBCR0       308  /* Debug Control Register 0 */
#define SPC5_SPR_DBCR1       309  /* Debug Control Register 1 */
#define SPC5_SPR_DBCR2       310  /* Debug Control Register 2 */
#define SPC5_SPR_IAC1        312  /* Instruction Address Compare 1 */
#define SPC5_SPR_IAC2        313  /* Instruction Address Compare 2 */
#define SPC5_SPR_IAC3        314  /* Instruction Address Compare 3 */
#define SPC5_SPR_IAC4        315  /* Instruction Address Compare 4 */
#define SPC5_SPR_DAC1        316  /* Data Address Compare 1 */
#define SPC5_SPR_DAC2        317  /* Data Address Compare 2 */
#define SPC5_SPR_DVC1        318  /* Data Value Compare 1 */
#define SPC5_SPR_DVC2        319  /* Data Value Compare 2 */
#define SPC5_SPR_SPEFSCR     512  /* LSP/EFP APU status and control register */
#define SPC5_SPR_L1CFG0      515  /* L1 cache config register 0 */
#define SPC5_SPR_L1CFG1      516  /* L1 cache config register 1 */
#define SPC5_SPR_NPIDR       517  /* Nexus 3 Process ID register */
#define SPC5_SPR_DBCR3       561  /* Debug control register 3 */
#define SPC5_SPR_DBCNT       562  /* Debug Counter register */
#define SPC5_SPR_DBCR4       563  /* Debug control register 4 */
#define SPC5_SPR_DBCR5       564  /* Debug control register 5 */
#define SPC5_SPR_IAC5        565  /* Instruction Address Compare 5 */
#define SPC5_SPR_IAC6        566  /* Instruction Address Compare 6 */
#define SPC5_SPR_IAC7        567  /* Instruction Address Compare 7 */
#define SPC5_SPR_IAC8        568  /* Instruction Address Compare 8 */
#define SPC5_SPR_MCSRR0      570  /* Machine Check Save/Restore Register 0 */
#define SPC5_SPR_MCSRR1      571  /* Machine Check Save/Restore Register 1 */
#define SPC5_SPR_MCSR        572  /* Machine Check Syndrome Register */
#define SPC5_SPR_MCAR        573  /* Machine Check Address Register */
#define SPC5_SPR_DSRR0       574  /* Debug save/restore register 0 */
#define SPC5_SPR_DSRR1       575  /* Debug save/restore register 1 */
#define SPC5_SPR_DDAM        576  /* Debug Data Acquisition Messaging register */
#define SPC5_SPR_DAC3        592  /* Data Address Compare 3 */
#define SPC5_SPR_DAC4        593  /* Data Address Compare 4 */
#define SPC5_SPR_DBCR7       596  /* Debug control register 7 */
#define SPC5_SPR_DBCR8       597  /* Debug control register 8 */
#define SPC5_SPR_DDEAR       600  /* Debug Data Effective Address register */
#define SPC5_SPR_DVC1U       601  /* Data Value Compare 1 Upper */
#define SPC5_SPR_DVC2U       602  /* Data Value Compare 2 Upper */
#define SPC5_SPR_DBCR6       603  /* Debug control register 6 */
#define SPC5_SPR_MAS0        624  /* MPU assist register 0 */
#define SPC5_SPR_MAS1        625  /* MPU assist register 1 */
#define SPC5_SPR_MAS2        626  /* MPU assist register 2 */
#define SPC5_SPR_MAS3        627  /* MPU assist register 3 */
#define SPC5_SPR_EDBRAC0     638  /* External debug resource allocation control register 0 */
#define SPC5_SPR_MPU0CFG     692  /* MPU0 configuration register */
#define SPC5_SPR_L1FINV1     959  /* L1 cache flush and invalidate control register 0 */
#define SPC5_SPR_DEVENT      975  /* Debug Event register */
#define SPC5_SPR_HID0        1008 /* Hardware implementation dependent reg 0 */
#define SPC5_SPR_HID1        1009 /* Hardware implementation dependent reg 1 */
#define SPC5_SPR_L1CSR0      1010 /* L1 cache control and status register 0 */
#define SPC5_SPR_L1CSR1      1011 /* L1 cache control and status register 1 */
#define SPC5_SPR_BUCSR       1013 /* Branch Unit Control and Status Register */
#define SPC5_SPR_MPU0CSR0    1014 /* MPU0 configuration register */
#define SPC5_SPR_MMUCFG      1015 /* MMU/MPU configuration register */
#define SPC5_SPR_L1FINV0     1016 /* L1 cache flush and invalidate control register 0 */
#define SPC5_SPR_SVR         1023 /* System Version Register */
/** @} */

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Value to string conversion.
 *
 * @notapi
 */
#define STRINGFY(_a_)        #_a_

/**
 * @brief   MPU read entry.
 * @details When this macro is invoked, data is read from the MPU into the MAS
 *          registers.
 *
 * @api
 */
#define mpure()              asm volatile ("mpure")

/**
 * @brief   MPU write entry
 * @details When this macro is invoked, data is written to the MPU from the MAS
 *          registers.
 *
 * @api
 */
#define mpuwe()              asm volatile ("mpuwe")

/**
 * @brief   MPU Synchronize.
 *
 * @api
 */
#define mpusync()            asm volatile ("mpusync")

/**
 * @brief   Move to Special Purpose Register.
 *
 * @param[in] _spr_     Special Purpose Register to be set.
 * @param[in] _v_       Value to be set.
 *
 * @api
 */
#define mtspr(_spr_, _v_)    asm volatile ("mtspr " STRINGFY(_spr_) ", %0" : : "r" (_v_))

/**
 * @brief   Move from Special Purpose Register.
 *
 * @param[in] _spr_     Special Purpose Register to be read.
 * @param[out] _v_      Read value.
 *
 * @api
 */
#define mfspr(_spr_, _v_)    asm volatile ("mfspr %0, " STRINGFY(_spr_) : "=r" (_v_) : )

/**
 * @brief   Instructions synchronize.
 *
 * @api
 */
#ifdef __ghs__
#define isync()              __ISYNC()
#else
#define isync()              asm volatile ("isync")
#endif

/**
 * @brief   Memory synchronize.
 *
 * @api
 */
#define msync()              asm volatile ("msync")

#endif /* _SPR_H_ */
