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
 * @file    platform.h
 * @brief   platform file.
 */

#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include "core.h"
#include "toolchain.h"
#include "intc.h"
#if !defined(_FROM_ASM_)
#include "typedefs.h"
#include "spr.h"
#include "spc570s_registry.h"
#include "xpc570s.h"
#endif

/**
 * @name    SARDADC References
 *
 * @{
 */
#define SPC5_SARADC_HAS_ALT_REFERENCE  FALSE
#define spc5_saradc                    SARADC_tag
#define SPC5_SARADC12_SV               SAR_ADC_12BIT_B0
#define SPC5_SARADC12_0 		       SAR_ADC_12BIT_0

#endif /* _PLATFORM_H_ */
