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
 * @file    clock.h
 * @brief   SPC570Sxx clock subsystem header
 *
 * @addtogroup CLOCK
 * @{
 */

#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "platform.h"
#include "irq.h"
#include "clock_cfg.h"

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/**
 * @name    Common constants
 * @{
 */
#if !defined(FALSE) || defined(__DOXYGEN__)
#define FALSE                               0
#endif

#if !defined(TRUE) || defined(__DOXYGEN__)
#define TRUE                                1
#endif

#define CLOCK_SUCCESS                       0U
#define CLOCK_FAILED                        1U
/** @} */

/**
 * @name    Absolute Maximum Ratings
 * @{
 */
/**
 * @brief   Minimum XOSC clock frequency.
 */
#define SPC5_XOSC_CLK_MIN                   8000000U

/**
 * @brief   Maximum XOSC clock frequency.
 */
#define SPC5_XOSC_CLK_MAX                   40000000U

/**
 * @brief   Minimum PLL0 input clock frequency.
 */
#define SPC5_PLL0IN_MIN                     8000000U

/**
 * @brief   Maximum PLL0 input clock frequency.
 */
#define SPC5_PLL0IN_MAX                     56000000U

/**
 * @brief   Minimum PLL1 input clock frequency.
 */
#define SPC5_PLL1IN_MIN                     37500000U

/**
 * @brief   Maximum PLL1 input clock frequency.
 */
#define SPC5_PLL1IN_MAX                     78125000U

/**
 * @brief   Minimum PLL0 VCO clock frequency.
 */
#define SPC5_PLL0VCO_MIN                    600000000U

/**
 * @brief   Maximum PLL0 VCO clock frequency.
 */
#define SPC5_PLL0VCO_MAX                    1250000000U

/**
 * @brief   Minimum PLL1 VCO clock frequency.
 */
#define SPC5_PLL1VCO_MIN                    600000000U

/**
 * @brief   Maximum PLL1 VCO clock frequency.
 */
#define SPC5_PLL1VCO_MAX                    1250000000U

/**
 * @brief   Minimum PLL0 output clock frequency.
 */
#define SPC5_PLL0_CLK_MIN                   4762000U

/**
 * @brief   Maximum PLL0 output clock frequency.
 */
#define SPC5_PLL0_CLK_MAX                   625000000U

/**
 * @brief   Minimum PLL1 output clock frequency.
 */
#define SPC5_PLL1_CLK_MIN                   4762000U

/**
 * @brief   Maximum PLL1 output clock frequency.
 */
#define SPC5_PLL1_CLK_MAX                   625000000U

/**
 * @brief   Maximum PER_CLK clock frequency.
 */
#define SPC5_PER_CLK_MAX                    80000000U

/**
 * @brief   Maximum SAR_CLK clock frequency.
 */
#define SPC5_SAR_CLK_MAX                    12000000U

/**
 * @brief   Maximum CTU_CLK clock frequency.
 */
#define SPC5_CTU_CLK_MAX                    80000000U

/**
 * @brief   Maximum DSPI_CLK clock frequency.
 */
#define SPC5_DSPI_CLK_MAX                   80000000U

/**
 * @brief   Maximum LIN_CLK clock frequency.
 */
#define SPC5_LIN_CLK_MAX                    80000000U

/**
 * @brief   Maximum ETIMER_CLK.
 */
#define SPC5_ETIMER_CLK_MAX                 80000000U

/**
 * @brief   Maximum CAN_CLK clock frequency.
 */
#define SPC5_CAN_CLK_MAX                    40000000U
/** @} */

/**
 * @name    Internal clock sources
 * @{
 */
#define SPC5_IRC_CLK                        16000000U
/** @} */

/**
 * @name    PLL0 registers bits definitions
 * @{
 */
#define SPC5_PLL0_CR_CLKCFG                 (3UL << 8)
#define SPC5_PLL0_CR_EXPDIE                 (1UL << 7)
#define SPC5_PLL0_CR_LOLIE                  (1UL << 3)

#define SPC5_PLL0_SR_EXTPDF                 (1UL << 7)
#define SPC5_PLL0_SR_LOLF                   (1UL << 3)
#define SPC5_PLL0_SR_LOCK                   (1UL << 2)

#define SPC5_PLL0_DV_RFDPHI1_MASK           (15UL << 27)
#define SPC5_PLL0_DV_RFDPHI1(n)             ((uint32_t)(n) << 27)

#define SPC5_PLL0_DV_RFDPHI_MASK            (63UL << 16)
#define SPC5_PLL0_DV_RFDPHI(n)              ((uint32_t)(n) << 16)

#define SPC5_PLL0_DV_PREDIV_MASK            (7UL << 12)
#define SPC5_PLL0_DV_PREDIV(n)              ((uint32_t)(n) << 12)

#define SPC5_PLL0_DV_MFD_MASK               (127UL << 0)
#define SPC5_PLL0_DV_MFD(n)                 ((uint32_t)(n) << 0)
/** @} */

/**
 * @name    PLL1 registers bits definitions
 * @{
 */
#define SPC5_PLL1_CR_CLKCFG                 (3UL << 7)
#define SPC5_PLL1_CR_EXPDIE                 (1UL << 7)
#define SPC5_PLL1_CR_LOLIE                  (1UL << 3)

#define SPC5_PLL1_SR_EXTPDF                 (1UL << 7)
#define SPC5_PLL1_SR_LOLIF                  (1UL << 3)
#define SPC5_PLL1_SR_LOCK                   (1UL << 2)

#define SPC5_PLL1_DV_RFDPHI_MASK            (63UL << 16)
#define SPC5_PLL1_DV_RFDPHI(n)              ((uint32_t)(n) << 16)

#define SPC5_PLL1_DV_MFD_MASK               (127UL << 0)
#define SPC5_PLL1_DV_MFD(n)                 ((uint32_t)(n) << 0)

#define SPC5_PLL1_FM_MODEN                  (1UL << 30)
#define SPC5_PLL1_FM_MODSEL                 (1UL << 29)
#define SPC5_PLL1_FM_MODPRD_MASK            (0x1FFFUL << 16)
#define SPC5_PLL1_FM_INCSTP_MASK            (0x7FFFUL << 0)

#define SPC5_PLL1_FD_FDEN                   (1UL << 30)
#define SPC5_PLL1_FD_DTHDIS_MASK            (3UL << 16)
#define SPC5_PLL1_FD_DTHDIS(n)              ((uint32_t)(n) << 16)
#define SPC5_PLL1_FD_FRCDIV_MASK            (0xFFFL << 0)
#define SPC5_PLL1_FD_FRCDIV(n)              ((uint32_t)(n) << 0)
/** @} */

/**
 * @name    Clock selectors used in the various CGM SC registers
 * @{
 */
#define SPC5_CGM_SC_MASK                    (15UL << 24)
#define SPC5_CGM_SC_IRC                     (0UL << 24)
#define SPC5_CGM_SC_XOSC                    (1UL << 24)
#define SPC5_CGM_SC_PLL0PHI                 (2UL << 24)
#define SPC5_CGM_SC_PLL0PHI1                (3UL << 24)
#define SPC5_CGM_SC_PLL1PHI                 (4UL << 24)
/** @} */

/**
 * @name    ME_GS register bits definitions
 * @{
 */
#define SPC5_ME_GS_SYSCLK_MASK              (15UL << 0)
#define SPC5_ME_GS_SYSCLK_IRC               (0UL << 0)
#define SPC5_ME_GS_SYSCLK_XOSC              (1UL << 0)
#define SPC5_ME_GS_SYSCLK_PLL0PHI           (2UL << 0)
#define SPC5_ME_GS_SYSCLK_PLL1PHI           (4UL << 0)
/** @} */

/**
 * @name    ME_ME register bits definitions
 * @{
 */
#define SPC5_ME_ME_RESET                    (1UL << 0)
#define SPC5_ME_ME_SAFE                     (1UL << 2)
#define SPC5_ME_ME_DRUN                     (1UL << 3)
#define SPC5_ME_ME_RUN0                     (1UL << 4)
#define SPC5_ME_ME_RUN1                     (1UL << 5)
#define SPC5_ME_ME_RUN2                     (1UL << 6)
#define SPC5_ME_ME_RUN3                     (1UL << 7)
#define SPC5_ME_ME_HALT0                    (1UL << 8)
#define SPC5_ME_ME_STOP0                    (1UL << 10)
/** @} */

/**
 * @name    ME_xxx_MC registers bits definitions
 * @{
 */
#define SPC5_ME_MC_SYSCLK_MASK              (15UL << 0)
#define SPC5_ME_MC_SYSCLK(n)                (((uint32_t)(n)) << 0)
#define SPC5_ME_MC_SYSCLK_IRC               SPC5_ME_MC_SYSCLK(0)
#define SPC5_ME_MC_SYSCLK_XOSC              SPC5_ME_MC_SYSCLK(1)
#define SPC5_ME_MC_SYSCLK_PLL0PHI           SPC5_ME_MC_SYSCLK(2)
#define SPC5_ME_MC_SYSCLK_PLL1PHI           SPC5_ME_MC_SYSCLK(4)
#define SPC5_ME_MC_SYSCLK_DISABLED          SPC5_ME_MC_SYSCLK(15)
#define SPC5_ME_MC_IRCON                    (1UL << 4)
#define SPC5_ME_MC_XOSCON                   (1UL << 5)
#define SPC5_ME_MC_PLL0ON                   (1UL << 6)
#define SPC5_ME_MC_PLL1ON                   (1UL << 7)
#define SPC5_ME_MC_FLAON_MASK               (3UL << 16)
#define SPC5_ME_MC_FLAON(n)                 (((uint32_t)(n)) << 16)
#define SPC5_ME_MC_FLAON_PD                 SPC5_ME_MC_FLAON(1)
#define SPC5_ME_MC_FLAON_LP                 SPC5_ME_MC_FLAON(2)
#define SPC5_ME_MC_FLAON_NORMAL             SPC5_ME_MC_FLAON(3)
#define SPC5_ME_MC_MVRON                    (1UL << 20)
#define SPC5_ME_MC_PDO                      (1UL << 23)
#define SPC5_ME_MC_PWRLVL_MASK              (7UL << 28)
#define SPC5_ME_MC_PWRLVL(n)                (((uint32_t)(n)) << 28)
/** @} */

/**
 * @name    ME_MCTL register bits definitions
 * @{
 */
#define SPC5_ME_MCTL_KEY                    0x5AF0UL
#define SPC5_ME_MCTL_KEY_INV                0xA50FUL
#define SPC5_ME_MCTL_MODE_MASK              (15UL << 28)
#define SPC5_ME_MCTL_MODE(n)                (((uint32_t)(n)) << 28)
/** @} */

/**
 * @name    ME_RUN_PCx registers bits definitions
 * @{
 */
#define SPC5_ME_RUN_PC_SAFE                 (1UL << 2)
#define SPC5_ME_RUN_PC_DRUN                 (1UL << 3)
#define SPC5_ME_RUN_PC_RUN0                 (1UL << 4)
#define SPC5_ME_RUN_PC_RUN1                 (1UL << 5)
#define SPC5_ME_RUN_PC_RUN2                 (1UL << 6)
#define SPC5_ME_RUN_PC_RUN3                 (1UL << 7)
/** @} */

/**
 * @name    ME_LP_PCx registers bits definitions
 * @{
 */
#define SPC5_ME_LP_PC_HALT0                 (1UL << 8)
#define SPC5_ME_LP_PC_STOP0                 (1UL << 10)
/** @} */

/**
 * @name    ME_PCTL registers bits definitions
 * @{
 */
#define SPC5_ME_PCTL_RUN_MASK               (7UL << 0)
#define SPC5_ME_PCTL_RUN(n)                 (((uint8_t)(n)) << 0)
#define SPC5_ME_PCTL_LP_MASK                (7UL << 3)
#define SPC5_ME_PCTL_LP(n)                  (((uint8_t)(n)) << 3)
#define SPC5_ME_PCTL_DBG                    (1UL << 6)
/** @} */

/**
 * @name    SSCM_ERROR register bits definitions
 * @{
 */
#define SPC5_SSCM_ERROR_RAE                 (1U << 0)
#define SPC5_SSCM_ERROR_PAE                 (1U << 1)
/** @} */

/**
 * @name    Run modes
 * @{
 */
#define SPC5_RUNMODE_SAFE                   2U
#define SPC5_RUNMODE_DRUN                   3U
#define SPC5_RUNMODE_RUN0                   4U
#define SPC5_RUNMODE_RUN1                   5U
#define SPC5_RUNMODE_RUN2                   6U
#define SPC5_RUNMODE_RUN3                   7U
#define SPC5_RUNMODE_HALT0                  8U
#define SPC5_RUNMODE_STOP0                  10U
/** @} */

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @brief   Disables the clocks initialization.
 */
#if !defined(SPC5_NO_INIT) || defined(__DOXYGEN__)
#define SPC5_NO_INIT                        FALSE
#endif

/**
 * @brief   Disables the overclock checks.
 */
#if !defined(SPC5_ALLOW_OVERCLOCK) || defined(__DOXYGEN__)
#define SPC5_ALLOW_OVERCLOCK                FALSE
#endif

/**
 * @brief   Disables Clockout
 */
#if !defined(SPC5_ENABLE_CLOCKOUT) || defined(__DOXYGEN__)
#define SPC5_ENABLE_CLOCKOUT                FALSE
#endif

/**
 *
 * @brief   Disables the watchdogs on start.
 */
#if !defined(SPC5_DISABLE_WATCHDOG) || defined(__DOXYGEN__)
#define SPC5_DISABLE_WATCHDOG               TRUE
#endif

/**
 * @brief   PLL0 PREDIV divider value.
 * @note    The default value is calculated for XOSC=40MHz and PLL0VCO=1200MHz.
 */
#if !defined(SPC5_PLL0_PREDIV_VALUE) || defined(__DOXYGEN__)
#define SPC5_PLL0_PREDIV_VALUE              2U
#endif

/**
 * @brief   PLL0 MFD multiplier value.
 * @note    The default value is calculated for XOSC=40MHz and PLL0VCO=1200MHz.
 */
#if !defined(SPC5_PLL0_MFD_VALUE) || defined(__DOXYGEN__)
#define SPC5_PLL0_MFD_VALUE                 30U
#endif

/**
 * @brief   PLL0 RFDPHI divider value.
 * @note    The default value is calculated for XOSC=40MHz and PLL0PHI=60MHz.
 */
#if !defined(SPC5_PLL0_RFDPHI_VALUE) || defined(__DOXYGEN__)
#define SPC5_PLL0_RFDPHI_VALUE              10U
#endif

/**
 * @brief   PLL0 RFDPHI1 divider value.
 * @note    The default value is calculated for XOSC=40MHz and PLL0PHI1=40MHz.
 */
#if !defined(SPC5_PLL0_RFDPHI1_VALUE) || defined(__DOXYGEN__)
#define SPC5_PLL0_RFDPHI1_VALUE             15U
#endif

/**
 * @brief   PLL1 MFD multiplier value.
 * @note    The default value is calculated for XOSC=40MHz and PLL1VCO=800MHz.
 */
#if !defined(SPC5_PLL1_MFD_VALUE) || defined(__DOXYGEN__)
#define SPC5_PLL1_MFD_VALUE                 20U
#endif

/**
 * @brief   PLL1 RFDPHI divider value.
 * @note    The default value is calculated for XOSC=40MHz and PLL1PHI=80MHz.
 */
#if !defined(SPC5_PLL1_RFDPHI_VALUE) || defined(__DOXYGEN__)
#define SPC5_PLL1_RFDPHI_VALUE              5U
#endif

/**
 * @brief   CGM_SC_DC0 clock divider value.
 * @note    Range 1..8, zero means disabled clock.
 * @note    The dividers on the SC must have values that are multiples of
 *          all the other SC dividers except the lowest one.
 */
#if !defined(SPC5_CGM_SC_DC0_DIV_VALUE) || defined(__DOXYGEN__)
#define SPC5_CGM_SC_DC0_DIV_VALUE           2U
#endif

/**
 * @brief   CGM_SC_DC1 clock divider value.
 * @note    Range 1..16, zero means disabled clock.
 * @note    The dividers on the SC must have values that are multiples of
 *          all the other SC dividers except the lowest one.
 */
#if !defined(SPC5_CGM_SC_DC1_DIV_VALUE) || defined(__DOXYGEN__)
#define SPC5_CGM_SC_DC1_DIV_VALUE           4U
#endif

/**
 * @brief   CGM_SC_DC2 clock divider value.
 * @note    Range 1..256, zero means disabled clock.
 * @note    The dividers on the SC must have values that are multiples of
 *          all the other SC dividers except the lowest one.
 */
#if !defined(SPC5_CGM_SC_DC2_DIV_VALUE) || defined(__DOXYGEN__)
#define SPC5_CGM_SC_DC2_DIV_VALUE           8U
#endif

/**
 * @brief   CGM_AC0_SC clock source.
 */
#if !defined(SPC5_CGM_AC0_SC_BITS) || defined(__DOXYGEN__)
#define SPC5_CGM_AC0_SC_BITS                SPC5_CGM_SC_PLL0PHI
#endif

/**
 * @brief   CGM_AC0_DC0 clock divider value.
 * @note    Range 1..16, zero means disabled clock.
 */
#if !defined(SPC5_CGM_AC0_DC0_DIV_VALUE) || defined(__DOXYGEN__)
#define SPC5_CGM_AC0_DC0_DIV_VALUE          5U
#endif

/**
 * @brief   CGM_AC0_DC1 clock divider value.
 * @note    Range 1..128, zero means disabled clock.
 */
#if !defined(SPC5_CGM_AC0_DC1_DIV_VALUE) || defined(__DOXYGEN__)
#define SPC5_CGM_AC0_DC1_DIV_VALUE          25U
#endif

/**
 * @brief   CGM_AC0_DC2 clock divider value.
 * @note    Range 1..128, zero means disabled clock.
 */
#if !defined(SPC5_CGM_AC0_DC2_DIV_VALUE) || defined(__DOXYGEN__)
#define SPC5_CGM_AC0_DC2_DIV_VALUE          25U
#endif

/**
 * @brief   CGM_AC0_DC3 clock divider value.
 * @note    Range 1..128, zero means disabled clock.
 */
#if !defined(SPC5_CGM_AC0_DC3_DIV_VALUE) || defined(__DOXYGEN__)
#define SPC5_CGM_AC0_DC3_DIV_VALUE          4U
#endif

/**
 * @brief   CGM_AC0_DC4 clock divider value.
 * @note    Range 1..16, zero means disabled clock.
 */
#if !defined(SPC5_CGM_AC0_DC4_DIV_VALUE) || defined(__DOXYGEN__)
#define SPC5_CGM_AC0_DC4_DIV_VALUE          4U
#endif

/**
 * @brief   CGM_AC0_DC5 clock divider value.
 * @note    Range 1..16, zero means disabled clock.
 */
#if !defined(SPC5_CGM_AC0_DC5_DIV_VALUE) || defined(__DOXYGEN__)
#define SPC5_CGM_AC0_DC5_DIV_VALUE          4U
#endif

/**
 * @brief   CGM_AC1_SC clock source.
 */
#if !defined(SPC5_CGM_AC1_SC_BITS) || defined(__DOXYGEN__)
#define SPC5_CGM_AC1_SC_BITS                SPC5_CGM_SC_XOSC
#endif

/**
 * @brief   CGM_AC1_DC0 clock divider value.
 * @note    Range 1..64, zero means disabled clock.
 */
#if !defined(SPC5_CGM_AC1_DC0_DIV_VALUE) || defined(__DOXYGEN__)
#define SPC5_CGM_AC1_DC0_DIV_VALUE          4U
#endif

/**
 * @brief   CGM_AC2_SC clock source.
 */
#if !defined(SPC5_CGM_AC2_SC_BITS) || defined(__DOXYGEN__)
#define SPC5_CGM_AC2_SC_BITS                SPC5_CGM_SC_XOSC
#endif

/**
 * @brief   CGM_AC3_SC clock source.
 */
#if !defined(SPC5_CGM_AC3_SC_BITS) || defined(__DOXYGEN__)
#define SPC5_CGM_AC3_SC_BITS                SPC5_CGM_SC_XOSC
#endif

/**
 * @brief   Active run modes in ME_ME register.
 * @note    Modes RESET, SAFE, DRUN, and RUN0 modes are always enabled, there
 *          is no need to specify them.
 */
#if !defined(SPC5_ME_ME_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_ME_BITS                     (SPC5_ME_ME_RUN1 |              \
                                             SPC5_ME_ME_RUN2 |              \
                                             SPC5_ME_ME_RUN3 |              \
                                             SPC5_ME_ME_HALT0 |             \
                                             SPC5_ME_ME_STOP0)
#endif

/**
 * @brief   SAFE mode settings.
 */
#if !defined(SPC5_ME_SAFE_MC_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_SAFE_MC_BITS                (SPC5_ME_MC_PDO)
#endif

/**
 * @brief   DRUN mode settings.
 */
#if !defined(SPC5_ME_DRUN_MC_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_DRUN_MC_BITS                (SPC5_ME_MC_SYSCLK_PLL1PHI |    \
                                             SPC5_ME_MC_IRCON |             \
                                             SPC5_ME_MC_XOSCON |            \
                                             SPC5_ME_MC_PLL0ON |            \
                                             SPC5_ME_MC_PLL1ON |            \
                                             SPC5_ME_MC_FLAON_NORMAL |      \
                                             SPC5_ME_MC_MVRON)
#endif

/**
 * @brief   RUN0 mode settings.
 */
#if !defined(SPC5_ME_RUN0_MC_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN0_MC_BITS                (SPC5_ME_MC_SYSCLK_PLL1PHI |    \
                                             SPC5_ME_MC_IRCON |             \
                                             SPC5_ME_MC_XOSCON |            \
                                             SPC5_ME_MC_PLL0ON |            \
                                             SPC5_ME_MC_PLL1ON |            \
                                             SPC5_ME_MC_FLAON_NORMAL |      \
                                             SPC5_ME_MC_MVRON)
#endif

/**
 * @brief   RUN1 mode settings.
 */
#if !defined(SPC5_ME_RUN1_MC_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN1_MC_BITS                (SPC5_ME_MC_SYSCLK_PLL1PHI |    \
                                             SPC5_ME_MC_IRCON |             \
                                             SPC5_ME_MC_XOSCON |            \
                                             SPC5_ME_MC_PLL0ON |            \
                                             SPC5_ME_MC_PLL1ON |            \
                                             SPC5_ME_MC_FLAON_NORMAL |      \
                                             SPC5_ME_MC_MVRON)
#endif

/**
 * @brief   RUN2 mode settings.
 */
#if !defined(SPC5_ME_RUN2_MC_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN2_MC_BITS                (SPC5_ME_MC_SYSCLK_PLL1PHI |    \
                                             SPC5_ME_MC_IRCON |             \
                                             SPC5_ME_MC_XOSCON |            \
                                             SPC5_ME_MC_PLL0ON |            \
                                             SPC5_ME_MC_PLL1ON |            \
                                             SPC5_ME_MC_FLAON_NORMAL |      \
                                             SPC5_ME_MC_MVRON)
#endif

/**
 * @brief   RUN3 mode settings.
 */
#if !defined(SPC5_ME_RUN3_MC_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN3_MC_BITS                (SPC5_ME_MC_SYSCLK_PLL1PHI |    \
                                             SPC5_ME_MC_IRCON |             \
                                             SPC5_ME_MC_XOSCON |            \
                                             SPC5_ME_MC_PLL0ON |            \
                                             SPC5_ME_MC_PLL1ON |            \
                                             SPC5_ME_MC_FLAON_NORMAL |      \
                                             SPC5_ME_MC_MVRON)
#endif

/**
 * @brief   HALT0 mode settings.
 */
#if !defined(SPC5_ME_HALT0_MC_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_HALT0_MC_BITS               (SPC5_ME_MC_SYSCLK_PLL1PHI |    \
                                             SPC5_ME_MC_IRCON |             \
                                             SPC5_ME_MC_XOSCON |            \
                                             SPC5_ME_MC_PLL0ON |            \
                                             SPC5_ME_MC_PLL1ON |            \
                                             SPC5_ME_MC_FLAON_NORMAL |      \
                                             SPC5_ME_MC_MVRON)
#endif

/**
 * @brief   STOP0 mode settings.
 */
#if !defined(SPC5_ME_STOP0_MC_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_STOP0_MC_BITS               (SPC5_ME_MC_SYSCLK_PLL1PHI |    \
                                             SPC5_ME_MC_IRCON |             \
                                             SPC5_ME_MC_XOSCON |            \
                                             SPC5_ME_MC_PLL0ON |            \
                                             SPC5_ME_MC_PLL1ON |            \
                                             SPC5_ME_MC_FLAON_NORMAL |      \
                                             SPC5_ME_MC_MVRON)
#endif

/**
 * @brief   Peripheral mode 0 (run mode).
 * @note    Do not change this setting, it is expected to be the "never run"
 *          mode.
 */
#if !defined(SPC5_ME_RUN_PC0_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN_PC0_BITS                0
#endif

/**
 * @brief   Peripheral mode 1 (run mode).
 * @note    Do not change this setting, it is expected to be the "always run"
 *          mode.
 */
#if !defined(SPC5_ME_RUN_PC1_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN_PC1_BITS                (SPC5_ME_RUN_PC_SAFE |          \
                                             SPC5_ME_RUN_PC_DRUN |          \
                                             SPC5_ME_RUN_PC_RUN0 |          \
                                             SPC5_ME_RUN_PC_RUN1 |          \
                                             SPC5_ME_RUN_PC_RUN2 |          \
                                             SPC5_ME_RUN_PC_RUN3)
#endif

/**
 * @brief   Peripheral mode 2 (run mode).
 * @note    Do not change this setting, it is expected to be the "only during
 *          normal run" mode.
 */
#if !defined(SPC5_ME_RUN_PC2_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN_PC2_BITS                (SPC5_ME_RUN_PC_DRUN |          \
                                             SPC5_ME_RUN_PC_RUN0 |          \
                                             SPC5_ME_RUN_PC_RUN1 |          \
                                             SPC5_ME_RUN_PC_RUN2 |          \
                                             SPC5_ME_RUN_PC_RUN3)
#endif

/**
 * @brief   Peripheral mode 3 (run mode).
 * @note    Not defined, available to application-specific modes.
 */
#if !defined(SPC5_ME_RUN_PC3_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN_PC3_BITS                (SPC5_ME_RUN_PC_DRUN |          \
                                             SPC5_ME_RUN_PC_RUN0 |          \
                                             SPC5_ME_RUN_PC_RUN1 |          \
                                             SPC5_ME_RUN_PC_RUN2 |          \
                                             SPC5_ME_RUN_PC_RUN3)
#endif

/**
 * @brief   Peripheral mode 4 (run mode).
 * @note    Not defined, available to application-specific modes.
 */
#if !defined(SPC5_ME_RUN_PC4_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN_PC4_BITS                (SPC5_ME_RUN_PC_DRUN |          \
                                             SPC5_ME_RUN_PC_RUN0 |          \
                                             SPC5_ME_RUN_PC_RUN1 |          \
                                             SPC5_ME_RUN_PC_RUN2 |          \
                                             SPC5_ME_RUN_PC_RUN3)
#endif

/**
 * @brief   Peripheral mode 5 (run mode).
 * @note    Not defined, available to application-specific modes.
 */
#if !defined(SPC5_ME_RUN_PC5_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN_PC5_BITS                (SPC5_ME_RUN_PC_DRUN |          \
                                             SPC5_ME_RUN_PC_RUN0 |          \
                                             SPC5_ME_RUN_PC_RUN1 |          \
                                             SPC5_ME_RUN_PC_RUN2 |          \
                                             SPC5_ME_RUN_PC_RUN3)
#endif

/**
 * @brief   Peripheral mode 6 (run mode).
 * @note    Not defined, available to application-specific modes.
 */
#if !defined(SPC5_ME_RUN_PC6_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN_PC6_BITS                (SPC5_ME_RUN_PC_DRUN |          \
                                             SPC5_ME_RUN_PC_RUN0 |          \
                                             SPC5_ME_RUN_PC_RUN1 |          \
                                             SPC5_ME_RUN_PC_RUN2 |          \
                                             SPC5_ME_RUN_PC_RUN3)
#endif

/**
 * @brief   Peripheral mode 7 (run mode).
 * @note    Not defined, available to application-specific modes.
 */
#if !defined(SPC5_ME_RUN_PC7_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN_PC7_BITS                (SPC5_ME_RUN_PC_DRUN |          \
                                             SPC5_ME_RUN_PC_RUN0 |          \
                                             SPC5_ME_RUN_PC_RUN1 |          \
                                             SPC5_ME_RUN_PC_RUN2 |          \
                                             SPC5_ME_RUN_PC_RUN3)
#endif

/**
 * @brief   Peripheral mode 0 (low power mode).
 * @note    Do not change this setting, it is expected to be the "never run"
 *          mode.
 */
#if !defined(SPC5_ME_LP_PC0_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_LP_PC0_BITS                 0
#endif

/**
 * @brief   Peripheral mode 1 (low power mode).
 * @note    Do not change this setting, it is expected to be the "always run"
 *          mode.
 */
#if !defined(SPC5_ME_LP_PC1_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_LP_PC1_BITS                 (SPC5_ME_LP_PC_HALT0 |          \
                                             SPC5_ME_LP_PC_STOP0)
#endif

/**
 * @brief   Peripheral mode 2 (low power mode).
 * @note    Do not change this setting, it is expected to be the "halt only"
 *          mode.
 */
#if !defined(SPC5_ME_LP_PC2_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_LP_PC2_BITS                 (SPC5_ME_LP_PC_HALT0)
#endif

/**
 * @brief   Peripheral mode 3 (low power mode).
 * @note    Do not change this setting, it is expected to be the "stop only"
 *          mode.
 */
#if !defined(SPC5_ME_LP_PC3_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_LP_PC3_BITS                 (SPC5_ME_LP_PC_STOP0)
#endif

/**
 * @brief   Peripheral mode 4 (low power mode).
 * @note    Not defined, available to application-specific modes.
 */
#if !defined(SPC5_ME_LP_PC4_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_LP_PC4_BITS                 (SPC5_ME_LP_PC_HALT0 |          \
                                             SPC5_ME_LP_PC_STOP0)
#endif

/**
 * @brief   Peripheral mode 5 (low power mode).
 * @note    Not defined, available to application-specific modes.
 */
#if !defined(SPC5_ME_LP_PC5_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_LP_PC5_BITS                 (SPC5_ME_LP_PC_HALT0 |          \
                                             SPC5_ME_LP_PC_STOP0)
#endif

/**
 * @brief   Peripheral mode 6 (low power mode).
 * @note    Not defined, available to application-specific modes.
 */
#if !defined(SPC5_ME_LP_PC6_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_LP_PC6_BITS                 (SPC5_ME_LP_PC_HALT0 |          \
                                             SPC5_ME_LP_PC_STOP0)
#endif

/**
 * @brief   Peripheral mode 7 (low power mode).
 * @note    Not defined, available to application-specific modes.
 */
#if !defined(SPC5_ME_LP_PC7_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_LP_PC7_BITS                 (SPC5_ME_LP_PC_HALT0 |          \
                                             SPC5_ME_LP_PC_STOP0)
#endif

/**
 * @brief   Final run mode after initialization.
 * @note    It can be selected between DRUN, RUN0...RUN3.
 */
#if !defined(SPC5_FINAL_RUNMODE) || defined(__DOXYGEN__)
#define SPC5_FINAL_RUNMODE                  SPC5_RUNMODE_RUN0
#endif

/**
 * @brief   SSCM.ERROR register initialization.
 */
#if !defined(SPC5_SSCM_ERROR_INIT) || defined(__DOXYGEN__)
#define SPC5_SSCM_ERROR_INIT                (SPC5_SSCM_ERROR_PAE |          \
                                             SPC5_SSCM_ERROR_RAE)
#endif

/**
 * @brief   Clock initialization failure hook.
 * @note    The default is to stop the system and let the RTC restart it.
 * @note    The hook code must not return.
 */
#if !defined(SPC5_CLOCK_FAILURE_HOOK) || defined(__DOXYGEN__)
#define SPC5_CLOCK_FAILURE_HOOK()           irqSysHalt()
#endif

/**
 * @brief   XOSC disabled initialization.
 * @note    The default is XOSC enabled.
 */
#if !defined(SPC5_XOSC_DISABLED) || defined(__DOXYGEN__)
#define SPC5_XOSC_DISABLED                  FALSE
#endif

/**
 * @brief   XOSCON set at least in one run mode initialization.
 * @note    The default is XOSCON not set in all run modes.
 */
#if !defined(SPC5_ME_MC_IS_XOSCON) || defined(__DOXYGEN__)
#define SPC5_ME_MC_IS_XOSCON                FALSE
#endif

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*-----------------------------------------*
 * Oscillators-related checks.             *
 *-----------------------------------------*/

/* Check on the XOSC frequency.*/
#if (SPC5_XOSC_CLK < SPC5_XOSC_CLK_MIN) ||                                  \
    (SPC5_XOSC_CLK > SPC5_XOSC_CLK_MAX)
#error "invalid SPC5_XOSC_CLK value specified"
#endif

/*-----------------------------------------*
 * PLL-related checks.                     *
 *-----------------------------------------*/

/* Check on SPC5_PLL0_PREDIV_VALUE.*/
#if (SPC5_PLL0_PREDIV_VALUE < 1U) || (SPC5_PLL0_PREDIV_VALUE > 7U)
#error "invalid SPC5_PLL0_PREDIV_VALUE value specified"
#endif

/* Check on SPC5_PLL0_MFD_VALUE.*/
#if (SPC5_PLL0_MFD_VALUE < 8U) || (SPC5_PLL0_MFD_VALUE > 127U)
#error "invalid SPC5_PLL0_MFD_VALUE value specified"
#endif

/* Check on SPC5_PLL0_RFDPHI_VALUE.*/
#if (SPC5_PLL0_RFDPHI_VALUE < 1U) || (SPC5_PLL0_RFDPHI_VALUE > 63U)
#error "invalid SPC5_PLL0_RFDPHI_VALUE value specified"
#endif

/* Check on SPC5_PLL0_RFDPHI1_VALUE.*/
#if (SPC5_PLL0_RFDPHI1_VALUE < 4U) || (SPC5_PLL0_RFDPHI1_VALUE > 15U)
#error "invalid SPC5_PLL0_RFDPHI1_VALUE value specified"
#endif

/* Check on SPC5_PLL1_MFD_VALUE.*/
#if (SPC5_PLL1_MFD_VALUE < 16U) || (SPC5_PLL1_MFD_VALUE > 34U)
#error "invalid SPC5_PLL1_MFD_VALUE value specified"
#endif

/* Check on SPC5_PLL1_RFDPHI_VALUE.*/
#if (SPC5_PLL1_RFDPHI_VALUE < 1U) || (SPC5_PLL1_RFDPHI_VALUE > 63U)
#error "invalid SPC5_PLL1_RFDPHI_VALUE value specified"
#endif

/*-----------------------------------------*
 * Mux-related checks and assignments.     *
 *-----------------------------------------*/

/* Check on SPC5_CGM_AC0_SC_BITS.*/
#if (SPC5_CGM_AC0_SC_BITS == SPC5_CGM_SC_IRC)
#define SPC5_AUX0_CLK                       SPC5_IRC_CLK
#elif (SPC5_CGM_AC0_SC_BITS == SPC5_CGM_SC_XOSC)
#define SPC5_AUX0_CLK                       SPC5_XOSC_CLK
#elif (SPC5_CGM_AC0_SC_BITS == SPC5_CGM_SC_PLL0PHI)
#define SPC5_AUX0_CLK                       SPC5_PLL0_PHI_CLK
#else
#error "invalid SPC5_CGM_AC0_SC_BITS value specified"
#endif

/* Check on SPC5_CGM_AC1_SC_BITS.*/
#if (SPC5_CGM_AC1_SC_BITS == SPC5_CGM_SC_XOSC)
#define SPC5_AUX1_CLK                       SPC5_XOSC_CLK
#elif (SPC5_CGM_AC1_SC_BITS == SPC5_CGM_SC_PLL0PHI)
#define SPC5_AUX1_CLK                       SPC5_PLL0_PHI_CLK
#else
#error "invalid SPC5_CGM_AC1_SC_BITS value specified"
#endif

/* Check on SPC5_CGM_AC2_SC_BITS.*/
#if (SPC5_CGM_AC2_SC_BITS == SPC5_CGM_SC_IRC)
#define SPC5_PLL0_INPUT_CLK                 SPC5_IRC_CLK
#elif (SPC5_CGM_AC2_SC_BITS == SPC5_CGM_SC_XOSC)
#define SPC5_PLL0_INPUT_CLK                 SPC5_XOSC_CLK
#else
#error "invalid SPC5_CGM_AC2_SC_BITS value specified"
#endif

/* Check on SPC5_CGM_AC3_SC_BITS.*/
#if (SPC5_CGM_AC3_SC_BITS == SPC5_CGM_SC_XOSC)
#define SPC5_PLL1_INPUT_CLK                 SPC5_XOSC_CLK
#elif (SPC5_CGM_AC3_SC_BITS == SPC5_CGM_SC_PLL0PHI1)
#define SPC5_PLL1_INPUT_CLK                 SPC5_PLL0_PHI1_CLK
#else
#error "invalid SPC5_CGM_AC3_SC_BITS value specified"
#endif

/*-----------------------------------------*
 * Dividers-related checks.                *
 *-----------------------------------------*/

/* Check on the SC divider 0 settings.*/
#if (SPC5_CGM_SC_DC0_DIV_VALUE >= 1U) && (SPC5_CGM_SC_DC0_DIV_VALUE <= 8U)
#define SPC5_CGM_SC_DC0_BITS                (0x80000000UL |                 \
                                             ((SPC5_CGM_SC_DC0_DIV_VALUE - 1U) << 16U))
#else
#error "invalid SPC5_CGM_SC_DC0_DIV_VALUE value specified"
#endif

/* Check on the SC divider 1 settings.*/
#if (SPC5_CGM_SC_DC1_DIV_VALUE >= 1U) && (SPC5_CGM_SC_DC1_DIV_VALUE <= 16U)
#define SPC5_CGM_SC_DC1_BITS                (0x80000000UL |                 \
                                             ((SPC5_CGM_SC_DC1_DIV_VALUE - 1U) << 16U))
#else
#error "invalid SPC5_CGM_SC_DC1_DIV_VALUE value specified"
#endif

/* Check on the SC divider 2 settings.*/
#if (SPC5_CGM_SC_DC2_DIV_VALUE == 0U) || (SPC5_ENABLE_CLOCKOUT == FALSE)
#define SPC5_CGM_SC_DC2_BITS                0U
#elif (SPC5_CGM_SC_DC2_DIV_VALUE >= 1U) && (SPC5_CGM_SC_DC2_DIV_VALUE <= 256U)
#define SPC5_CGM_SC_DC2_BITS                (0x80000000UL |                 \
                                             ((SPC5_CGM_SC_DC2_DIV_VALUE - 1U) << 16U))
#else
#error "invalid SPC5_CGM_SC_DC2_DIV_VALUE value specified"
#endif

/* Check on the AUX0 divider 0 settings.*/
#if (SPC5_CGM_AC0_DC0_DIV_VALUE == 0U)
#define SPC5_CGM_AC0_DC0_BITS               0U
#elif (SPC5_CGM_AC0_DC0_DIV_VALUE >= 1U) && (SPC5_CGM_AC0_DC0_DIV_VALUE <= 16U)
#define SPC5_CGM_AC0_DC0_BITS               (0x80000000UL |                 \
                                             ((SPC5_CGM_AC0_DC0_DIV_VALUE - 1U) << 16U))
#else
#error "invalid SPC5_CGM_AC0_DC0_DIV_VALUE value specified"
#endif

/* Check on the AUX0 divider 1 settings.*/
#if (SPC5_CGM_AC0_DC1_DIV_VALUE == 0U)
#define SPC5_CGM_AC0_DC1_BITS               0U
#elif (SPC5_CGM_AC0_DC1_DIV_VALUE >= 1U) && (SPC5_CGM_AC0_DC1_DIV_VALUE <= 128U)
#define SPC5_CGM_AC0_DC1_BITS               (0x80000000UL |                 \
                                             ((SPC5_CGM_AC0_DC1_DIV_VALUE - 1U) << 16U))
#else
#error "invalid SPC5_CGM_AC0_DC1_DIV_VALUE value specified"
#endif

/* Check on the AUX0 divider 2 settings.*/
#if (SPC5_CGM_AC0_DC2_DIV_VALUE == 0U)
#define SPC5_CGM_AC0_DC2_BITS               0U
#elif (SPC5_CGM_AC0_DC2_DIV_VALUE >= 1U) && (SPC5_CGM_AC0_DC2_DIV_VALUE <= 128U)
#define SPC5_CGM_AC0_DC2_BITS               (0x80000000UL |                 \
                                             ((SPC5_CGM_AC0_DC2_DIV_VALUE - 1U) << 16U))
#else
#error "invalid SPC5_CGM_AC0_DC2_DIV_VALUE value specified"
#endif

/* Check on the AUX0 divider 3 settings.*/
#if (SPC5_CGM_AC0_DC3_DIV_VALUE == 0U)
#define SPC5_CGM_AC0_DC3_BITS               0U
#elif (SPC5_CGM_AC0_DC3_DIV_VALUE >= 1U) && (SPC5_CGM_AC0_DC3_DIV_VALUE <= 128U)
#define SPC5_CGM_AC0_DC3_BITS               (0x80000000UL |                 \
                                             ((SPC5_CGM_AC0_DC3_DIV_VALUE - 1U) << 16U))
#else
#error "invalid SPC5_CGM_AC0_DC3_DIV_VALUE value specified"
#endif

/* Check on the AUX0 divider 4 settings.*/
#if (SPC5_CGM_AC0_DC4_DIV_VALUE == 0U)
#define SPC5_CGM_AC0_DC4_BITS               0
#elif (SPC5_CGM_AC0_DC4_DIV_VALUE >= 1U) && (SPC5_CGM_AC0_DC4_DIV_VALUE <= 16U)
#define SPC5_CGM_AC0_DC4_BITS               (0x80000000UL |                 \
                                             ((SPC5_CGM_AC0_DC4_DIV_VALUE - 1U) << 16U))
#else
#error "invalid SPC5_CGM_AC0_DC4_DIV_VALUE value specified"
#endif

/* Check on the AUX0 divider 5 settings.*/
#if (SPC5_CGM_AC0_DC5_DIV_VALUE == 0U)
#define SPC5_CGM_AC0_DC5_BITS               0U
#elif (SPC5_CGM_AC0_DC5_DIV_VALUE >= 1U) && (SPC5_CGM_AC0_DC5_DIV_VALUE <= 16U)
#define SPC5_CGM_AC0_DC5_BITS               (0x80000000UL |                \
                                             ((SPC5_CGM_AC0_DC5_DIV_VALUE - 1U) << 16U))
#else
#error "invalid SPC5_CGM_AC0_DC5_DIV_VALUE value specified"
#endif

/* Check on the AUX1 divider 0 settings.*/
#if (SPC5_CGM_AC1_DC0_DIV_VALUE == 0U)
#define SPC5_CGM_AC1_DC0_BITS               0U
#elif (SPC5_CGM_AC1_DC0_DIV_VALUE >= 1U) && (SPC5_CGM_AC1_DC0_DIV_VALUE <= 64U)
#define SPC5_CGM_AC1_DC0_BITS               (0x80000000UL |                 \
                                             ((SPC5_CGM_AC1_DC0_DIV_VALUE - 1U) << 16U))
#else
#error "invalid SPC5_CGM_AC1_DC0_DIV_VALUE value specified"
#endif

/*-----------------------------------------*
 * Clock points calculation and check.     *
 *-----------------------------------------*/

/**
 * @brief   SPC5_PLL0_VCO_CLK clock point.
 */
#define SPC5_PLL0_VCO_CLK                                                   \
  ((SPC5_PLL0_INPUT_CLK / SPC5_PLL0_PREDIV_VALUE) * (2U * SPC5_PLL0_MFD_VALUE))

/* Check on PLL0 VCO output.*/
#if (SPC5_PLL0_VCO_CLK < SPC5_PLL0VCO_MIN) ||                               \
    (SPC5_PLL0_VCO_CLK > SPC5_PLL0VCO_MAX)
#error "SPC5_PLL0_VCO_CLK outside acceptable range (SPC5_PLL0VCO_MIN...SPC5_PLL0VCO_MAX)"
#endif

/**
 * @brief   SPC5_PLL0_PHI_CLK clock point.
 */
#define SPC5_PLL0_PHI_CLK                                                   \
  ((SPC5_PLL0_VCO_CLK / SPC5_PLL0_RFDPHI_VALUE) / 2U)

/* Check on SPC5_PLL0_PHI_CLK.*/
#if ((SPC5_PLL0_PHI_CLK > SPC5_PLL0_CLK_MAX) ||                             \
     (SPC5_PLL0_PHI_CLK < SPC5_PLL0_CLK_MIN)) && (SPC5_ALLOW_OVERCLOCK == FALSE)
#error "SPC5_PLL0_PHI_CLK outside acceptable range (SPC5_PLL0_CLK_MIN...SPC5_PLL0_CLK_MAX)"
#endif

/**
 * @brief   SPC5_PLL0_PHI1_CLK clock point.
 */
#define SPC5_PLL0_PHI1_CLK                                                  \
  ((SPC5_PLL0_VCO_CLK / SPC5_PLL0_RFDPHI1_VALUE) / 2U)

/* Check on SPC5_PLL0_PH1I_CLK.*/
#if ((SPC5_PLL0_PHI1_CLK > SPC5_PLL0_CLK_MAX) ||                            \
     (SPC5_PLL0_PHI1_CLK < SPC5_PLL0_CLK_MIN)) && (SPC5_ALLOW_OVERCLOCK == FALSE)
#error "SPC5_PLL0_PHI1_CLK outside acceptable range (SPC5_PLL0_CLK_MIN...SPC5_PLL0_CLK_MAX)"
#endif

/**
 * @brief   SPC5_PLL1_VCO_CLK clock point.
 */
#define SPC5_PLL1_VCO_CLK                                                   \
  (SPC5_PLL1_INPUT_CLK * SPC5_PLL1_MFD_VALUE)

/* Check on PLL1 VCO output.*/
#if (SPC5_PLL1_VCO_CLK < SPC5_PLL1VCO_MIN) ||                               \
    (SPC5_PLL1_VCO_CLK > SPC5_PLL1VCO_MAX)
#error "SPC5_PLL1_VCO_CLK outside acceptable range (SPC5_PLL1VCO_MIN...SPC5_PLL1VCO_MAX)"
#endif

/**
 * @brief   SPC5_PLL1_PHI_CLK clock point.
 * @note    The calculation is still wrong in the rev.5 RM.
 */
#define SPC5_PLL1_PHI_CLK                                                   \
  ((SPC5_PLL1_VCO_CLK / SPC5_PLL1_RFDPHI_VALUE) / 2U)

/* Check on SPC5_PLL1_PHI_CLK.*/
#if ((SPC5_PLL1_PHI_CLK > SPC5_PLL1_CLK_MAX) ||                             \
     (SPC5_PLL1_PHI_CLK < SPC5_PLL1_CLK_MIN)) && (SPC5_ALLOW_OVERCLOCK == FALSE)
#error "SPC5_PLL1_PHI_CLK outside acceptable range (SPC5_PLL1_CLK_MIN...SPC5_PLL1_CLK_MAX)"
#endif

/**
 * @brief   PER_CLK clock point.
 */
#if (SPC5_CGM_AC0_DC0_DIV_VALUE == 0U)
#define SPC5_PER_CLK                        0U
#else
#define SPC5_PER_CLK                        (SPC5_AUX0_CLK / SPC5_CGM_AC0_DC0_DIV_VALUE)
#endif

/* Check on SPC5_PER_CLK.*/
#if SPC5_PER_CLK > SPC5_PER_CLK_MAX
#error "SPC5_PER_CLK outside acceptable range (0...SPC5_PER_CLK_MAX)"
#endif

/**
 * @brief   SAR_CLK clock point.
 */
#if (SPC5_CGM_AC0_DC1_DIV_VALUE == 0U)
#define SPC5_SAR_CLK                        0U
#else
#define SPC5_SAR_CLK                        (SPC5_AUX0_CLK / SPC5_CGM_AC0_DC1_DIV_VALUE)
#endif

/* Check on SPC5_SAR_CLK.*/
#if SPC5_SAR_CLK > SPC5_SAR_CLK_MAX
#error "SPC5_SAR_CLK outside acceptable range (0...SPC5_SAR_CLK_MAX)"
#endif

/**
 * @brief   CTU clock point.
 */
#if (SPC5_CGM_AC0_DC2_DIV_VALUE == 0U)
#define SPC5_CTU_CLK                        0U
#else
#define SPC5_CTU_CLK                        (SPC5_AUX0_CLK / SPC5_CGM_AC0_DC2_DIV_VALUE)
#endif

/* Check on SPC5_CTU_CLK.*/
#if SPC5_CTU_CLK > SPC5_CTU_CLK_MAX
#error "SPC5_CTU_CLK outside acceptable range (0...SPC5_CTU_CLK_MAX)"
#endif

/**
 * @brief   DSPI_CLK clock point.
 */
#if (SPC5_CGM_AC0_DC3_DIV_VALUE == 0U)
#define SPC5_DSPI_CLK                       0U
#else
#define SPC5_DSPI_CLK                       (SPC5_AUX0_CLK / SPC5_CGM_AC0_DC3_DIV_VALUE)
#endif

/* Check on SPC5_DSPI_CLK.*/
#if SPC5_DSPI_CLK > SPC5_DSPI_CLK_MAX
#error "SPC5_DSPI_CLK outside acceptable range (0...SPC5_DSPI_CLK_MAX)"
#endif

/**
 * @brief   LIN_CLK clock point.
 */
#if (SPC5_CGM_AC0_DC4_DIV_VALUE == 0U)
#define SPC5_LIN_CLK                        0U
#else
#define SPC5_LIN_CLK                        (SPC5_AUX0_CLK / SPC5_CGM_AC0_DC4_DIV_VALUE)
#endif

/* Check on SPC5_LIN_CLK.*/
#if SPC5_LIN_CLK > SPC5_LIN_CLK_MAX
#error "SPC5_LIN_CLK outside acceptable range (0...SPC5_LIN_CLK_MAX)"
#endif

/**
 * @brief   ETIMER_CLK clock point.
 */
#if (SPC5_CGM_AC0_DC5_DIV_VALUE == 0U)
#define SPC5_ETIMER_CLK                     0U
#else
#define SPC5_ETIMER_CLK                     (SPC5_AUX0_CLK / SPC5_CGM_AC0_DC5_DIV_VALUE)
#endif

/* Check on SPC5_ETIMER_CLK.*/
#if SPC5_ETIMER_CLK > SPC5_ETIMER_CLK_MAX
#error "SPC5_ETIMER_CLK outside acceptable range (0...SPC5_ETIMER_CLK_MAX)"
#endif

/**
 * @brief   CAN_CLK clock point.
 */
#if (SPC5_CGM_AC1_DC0_DIV_VALUE == 0U)
#define SPC5_CAN_CLK                        0U
#else
#define SPC5_CAN_CLK                        (SPC5_AUX1_CLK / SPC5_CGM_AC1_DC0_DIV_VALUE)
#endif

/* Check on SPC5_CAN_CLK.*/
#if SPC5_CAN_CLK > SPC5_CAN_CLK_MAX
#error "SPC5_CAN_CLK outside acceptable range (0...SPC5_CAN_CLK_MAX)"
#endif

/* Check on SPC5_PER_CLK.*/
#if SPC5_PER_CLK > SPC5_PER_CLK_MAX
#error "SPC5_PER_CLK outside acceptable range (0...SPC5_PER_CLK_MAX)"
#endif

/* Check XOSC is not used if it is disabled.*/
#if (SPC5_XOSC_DISABLED == TRUE)
#if ((SPC5_CGM_AC0_SC_BITS == SPC5_CGM_SC_XOSC)  || (SPC5_CGM_AC1_SC_BITS == SPC5_CGM_SC_XOSC)  || \
     (SPC5_CGM_AC2_SC_BITS == SPC5_CGM_SC_XOSC)  || (SPC5_CGM_AC3_SC_BITS == SPC5_CGM_SC_XOSC))
#error "XOSC cannot be selected as clock source if it is disabled."
#endif

#if(SPC5_ME_MC_IS_XOSCON == TRUE)
#error "XOSCON cannot be set in one or more Run Modes if XOSC is disabled."
#endif
#endif

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Peripheral type.
 */
typedef enum {
  SPC5_PERIPHERAL_PIT0 = 0
} peripheral_t;

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  void clockInit(void);
  void spc_clock_init(void);
  void __early_init(void);
  uint8_t SPCSetRunMode(uint8_t mode);
  void SPCSetPeripheralClockMode(uint32_t n, uint32_t pctl);
#if (SPC5_NO_INIT == FALSE)
  uint32_t SPCGetSystemClock(void);
  uint32_t SPCGetPeripheralClock(peripheral_t peripheral);
#endif
#ifdef __cplusplus
}
#endif

#endif /* _CLOCK_H_ */

/** @} */
