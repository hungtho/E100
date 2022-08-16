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

#ifndef _BOARD_H_
#define _BOARD_H_

#include "pal.h"

/*
 * Setup for a generic SPC570Sxx board.
 */

/*
 * Board identifiers.
 */
#define BOARD_GENERIC_SPC570SXX
#define BOARD_NAME                  "Generic SPC570Sxx"

/*
 * I/O definitions.
 */
#define WTD_PWM                     0U
#define HW_FAULT_DECTECTED_PIN      13U
#define ADC_AN9                     3U
#define ADC_AN8                     4U
#define ADC_AN7                     5U
#define ADC_AN6                     6U
#define ADC_AN5                     7U
#define ADC_AN3                     11U
#define POWER_LATCH                 3U
#define ADC_AN2                     14U
#define ADC_AN0                     1U
#define PWM_A0                      7U
#define PWM_A1                      8U
#define CANTX                       10U
#define PWM_B0                      11U
#define PWM_B1                      14U
#define SR1                         15U
#define STANDBY_CAN2                7U
#define SR2                         8U
#define INH_PIN                     9U

/*
 * MSCR_MUX definitions.
 */
#define MSCR_MUX_CAN0_RX_CFG        0U

/*
 * Support macros.
 */
#define MSCR_IO_INDEX(port, pin)  (((port) * 16U) + (pin))

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
