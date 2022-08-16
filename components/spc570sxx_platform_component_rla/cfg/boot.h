/****************************************************************************
*
* Copyright © 2015-2019 STMicroelectronics - All Rights Reserved
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
 * @file    boot.h
 * @brief   Boot parameters for the SPC570Sxx.
 * @{
 */

#ifndef _BOOT_H_
#define _BOOT_H_

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/**
 * @name    BUCSR registers definitions
 * @{
 */
#define BUCSR_BPEN              0x00000001
#define BUCSR_BALLOC_BFI        0x00000200
/** @} */

/**
 * @name   MSR register definitions
 * @{
 */
#define MSR_WE                  0x00040000
#define MSR_CE                  0x00020000
#define MSR_EE                  0x00008000
#define MSR_PR                  0x00004000
#define MSR_ME                  0x00001000
#define MSR_DE                  0x00000200
#define MSR_IS                  0x00000020
#define MSR_DS                  0x00000010
#define MSR_RI                  0x00000002
/** @} */

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/*
 * BUCSR default settings.
 */
#define BUCSR_DEFAULT           (BUCSR_BPEN | BUCSR_BALLOC_BFI)

/*
 * MSR default settings.
 */
#define MSR_DEFAULT             (MSR_WE | MSR_CE | MSR_ME)

/*
 * Boot default settings.
 */
#define BOOT_PERFORM_CORE_INIT  1

/*
 * VLE mode default settings.
 */
#define BOOT_USE_VLE            1

/*
 * RAM relocation flag.
 */
#define BOOT_RELOCATE_IN_RAM    0

#define BOOT_LOAD_IN_RAM        0

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

#endif /* _BOOT_H_ */

/** @} */
