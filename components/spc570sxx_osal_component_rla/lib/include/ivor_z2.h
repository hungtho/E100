/****************************************************************************
*
* Copyright © 2018-2019 STMicroelectronics - All Rights Reserved
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
 * @file    ivor_z2.h
 * @brief   Interrupt Handler Macros.
 *
 * @addtogroup PPC_CORE
 * @{
 */

 #define _FROM_ASM_

#if !defined(__DOXYGEN__)

#define LOAD_IVOR1_EXC_REG LOAD_MCSSR0_MCSSR1
#define LOAD_IVOR9_EXC_REG LOAD_DSSR0_DSSR1
#define RET_IVOR1 se_rfmci
#define RET_IVOR9 se_rfdi 

#endif /* !defined(__DOXYGEN__) */

/** @} */
