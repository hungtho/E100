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
* EVALUATION ONLY ?? NOT FOR USE IN PRODUCTION
*****************************************************************************/

/**
 * @file    clock.c
 * @brief   SPC570Sxx clock subsystem source.
 *
 * @addtogroup CLOCK
 * @{
 */

#include "clock.h"

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

#if (SPC5_CLEAR_FCCU_RGM == TRUE)
/**
 * @brief   Clear FCCU Status Register errors and RGM errors.
 *
 * @notapi
 */
static void spc_clear_fccu_rgm(void) {

  /* Clear FCCU Status Register0 errors */
  FCCU.RFK.R = 0xAB3498FEUL;
  FCCU.RF_S[0].R = 0xFFFFFFFFUL;
  while (FCCU.CTRL.B.OPS != 0x03UL) {
  }

  /* Clear FCCU Status Register1 errors */
  FCCU.RFK.R = 0xAB3498FEUL;
  FCCU.RF_S[1].R = 0xFFFFFFFFUL;
  while (FCCU.CTRL.B.OPS != 0x03UL) {
  }

  /* Clear FCCU Status Register2 errors */
  FCCU.RFK.R = 0xAB3498FEUL;
  FCCU.RF_S[2].R = 0xFFFFFFFFUL;
  while (FCCU.CTRL.B.OPS != 0x03UL) {
  }

  /* Clear FCCU Status Register3 errors */
  FCCU.RFK.R = 0xAB3498FEUL;
  FCCU.RF_S[3].R = 0xFFFFFFFFUL;
  while (FCCU.CTRL.B.OPS != 0x03UL) {
  }

  /* RGM errors clearing.*/
  MC_RGM.FES.R = 0xFFFFU;
  MC_RGM.DES.R = 0xFFFFU;
}
#endif /* SPC5_CLEAR_FCCU_RGM */

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Clock initialization.
 *
 * @notapi
 */
void clockInit(void) {

  /* The system is switched in the final run mode (default is RUN0 mode).*/
  if (SPCSetRunMode(SPC5_FINAL_RUNMODE) == CLOCK_FAILED) {
    SPC5_CLOCK_FAILURE_HOOK();
  }
}

/**
 * @brief   SPC570Sxx clocks and PLL initialization.
 *
 * @note    This function must be invoked only after the system reset.
 *
 * @special
 */
void spc_clock_init(void) {

  /* Waiting for IRC stabilization before attempting anything else.*/
  while (MC_ME.GS.B.S_IRCOSC == 0U) {
  }

#if (SPC5_NO_INIT == FALSE)

#if SPC5_DISABLE_WATCHDOG
  /* SWTs disabled.*/
  SWT_0.SR.R = 0xC520U;
  SWT_0.SR.R = 0xD928U;
  SWT_0.CR.R = 0xFF000002UL;
#endif

  /* SSCM initialization from configuration data.*/
  SSCM.ERROR.R = (uint16_t)SPC5_SSCM_ERROR_INIT;

  /* Clear FCCU/RGM errors if FCCU driver is disabled, otherwise the errors are
     managed by the FCCU driver.*/
#if (SPC5_CLEAR_FCCU_RGM == TRUE)
  spc_clear_fccu_rgm();
#endif /* SPC5_CLEAR_FCCU_RGM */

  /* The system must be in DRUN mode on entry, if this is not the case then
     it is considered a serious anomaly.*/
#if 0 /* FBL(v-flash) */
  if (MC_ME.GS.B.S_CURRENT_MODE != (uint8_t)SPC5_RUNMODE_DRUN) {
    SPC5_CLOCK_FAILURE_HOOK();
  }
#endif

#if (SPC5_XOSC_DISABLED == FALSE)
#if (SPC5_OSC_BYPASS == TRUE)
  /* If the board is equipped with an oscillator instead of a crystal then the
     bypass must be activated.*/
  XOSC.CTL.B.OSCBYP = TRUE;
#endif /* SPC5_OSC_BYPASS */
#endif /* !SPC5_XOSC_DISABLED */

  /* Memory-mapped register definitions incompatible with MISRA rule. */
  /*lint -e10 -e40 -e63*/
  /* Setting the system dividers to their final values.*/
  MC_CGM.SC_DC0.R   = SPC5_CGM_SC_DC0_BITS;
  MC_CGM.SC_DC1.R   = SPC5_CGM_SC_DC1_BITS;
  MC_CGM.SC_DC2.R   = SPC5_CGM_SC_DC2_BITS;
  
  /* Setting the auxiliary dividers to their final values.*/
  MC_CGM.AC0_DC0.R  = SPC5_CGM_AC0_DC0_BITS;
  MC_CGM.AC0_DC1.R  = SPC5_CGM_AC0_DC1_BITS;
  MC_CGM.AC0_DC2.R  = SPC5_CGM_AC0_DC2_BITS;
  MC_CGM.AC0_DC3.R  = SPC5_CGM_AC0_DC3_BITS;
  MC_CGM.AC0_DC4.R  = SPC5_CGM_AC0_DC4_BITS;
  MC_CGM.AC0_DC5.R  = SPC5_CGM_AC0_DC5_BITS;
  MC_CGM.AC1_DC0.R  = SPC5_CGM_AC1_DC0_BITS;
  
  /* Setting the clock selectors to their final sources.*/
  MC_CGM.AC0_SC.R   = SPC5_CGM_AC0_SC_BITS;
  MC_CGM.AC1_SC.R   = SPC5_CGM_AC1_SC_BITS;
  MC_CGM.AC2_SC.R   = SPC5_CGM_AC2_SC_BITS;
  MC_CGM.AC3_SC.R   = SPC5_CGM_AC3_SC_BITS;
  /*lint +e10 +e40 +e63*/

#if (SPC5_XOSC_DISABLED == FALSE)
  /* Enables the XOSC in order to check its functionality before proceeding
     with the initialization.*/
  MC_ME.DRUN_MC.R   = SPC5_ME_MC_SYSCLK_IRC | SPC5_ME_MC_IRCON |
                      SPC5_ME_MC_XOSCON | SPC5_ME_MC_FLAON_NORMAL |
                      SPC5_ME_MC_MVRON;
#if 0 /* FBL(v-flash) */
  if (SPCSetRunMode(SPC5_RUNMODE_DRUN) == CLOCK_FAILED) {
    SPC5_CLOCK_FAILURE_HOOK();
  }
#endif
#endif /* !SPC5_XOSC_DISABLED */

  /* PLLs initialization, the changes will have effect on mode switch.*/
  PLLDIG.PLL0CR.R   = 0U;
  PLLDIG.PLL0DV.R   = SPC5_PLL0_DV_RFDPHI1(SPC5_PLL0_RFDPHI1_VALUE) |
                      SPC5_PLL0_DV_RFDPHI(SPC5_PLL0_RFDPHI_VALUE) |
                      SPC5_PLL0_DV_PREDIV(SPC5_PLL0_PREDIV_VALUE) |
                      SPC5_PLL0_DV_MFD(SPC5_PLL0_MFD_VALUE);
  PLLDIG.PLL1CR.R   = 0U;
  PLLDIG.PLL1DV.R   = SPC5_PLL1_DV_RFDPHI(SPC5_PLL1_RFDPHI_VALUE) |
                      SPC5_PLL1_DV_MFD(SPC5_PLL1_MFD_VALUE);

  /* Run modes initialization, note writes to the MC registers are verified
     by a protection mechanism, the operation success is verified at the
     end of the sequence.*/
  MC_ME.IS.R        = 8U;                        /* Resetting I_ICONF status.*/
  MC_ME.ME.R        = SPC5_ME_ME_BITS;
  MC_ME.SAFE_MC.R   = SPC5_ME_SAFE_MC_BITS;
  MC_ME.DRUN_MC.R   = SPC5_ME_DRUN_MC_BITS;
  MC_ME.RUN_MC[0].R = SPC5_ME_RUN0_MC_BITS;
  MC_ME.RUN_MC[1].R = SPC5_ME_RUN1_MC_BITS;
  MC_ME.RUN_MC[2].R = SPC5_ME_RUN2_MC_BITS;
  MC_ME.RUN_MC[3].R = SPC5_ME_RUN3_MC_BITS;
  MC_ME.HALT0_MC.R   = SPC5_ME_HALT0_MC_BITS;
  MC_ME.STOP0_MC.R   = SPC5_ME_STOP0_MC_BITS;

  if ((MC_ME.IS.B.I_ICONF & 1U) == 1U) {
    /* Configuration rejected.*/
    SPC5_CLOCK_FAILURE_HOOK();
  }

  /* Peripherals run and low power modes initialization.*/
  MC_ME.RUN_PC[0].R = SPC5_ME_RUN_PC0_BITS;
  MC_ME.RUN_PC[1].R = SPC5_ME_RUN_PC1_BITS;
  MC_ME.RUN_PC[2].R = SPC5_ME_RUN_PC2_BITS;
  MC_ME.RUN_PC[3].R = SPC5_ME_RUN_PC3_BITS;
  MC_ME.RUN_PC[4].R = SPC5_ME_RUN_PC4_BITS;
  MC_ME.RUN_PC[5].R = SPC5_ME_RUN_PC5_BITS;
  MC_ME.RUN_PC[6].R = SPC5_ME_RUN_PC6_BITS;
  MC_ME.RUN_PC[7].R = SPC5_ME_RUN_PC7_BITS;
  MC_ME.LP_PC[0].R  = SPC5_ME_LP_PC0_BITS;
  MC_ME.LP_PC[1].R  = SPC5_ME_LP_PC1_BITS;
  MC_ME.LP_PC[2].R  = SPC5_ME_LP_PC2_BITS;
  MC_ME.LP_PC[3].R  = SPC5_ME_LP_PC3_BITS;
  MC_ME.LP_PC[4].R  = SPC5_ME_LP_PC4_BITS;
  MC_ME.LP_PC[5].R  = SPC5_ME_LP_PC5_BITS;
  MC_ME.LP_PC[6].R  = SPC5_ME_LP_PC6_BITS;
  MC_ME.LP_PC[7].R  = SPC5_ME_LP_PC7_BITS;

  /* Switches again to DRUN mode (current mode) in order to update the
     settings.*/
  if (SPCSetRunMode(SPC5_RUNMODE_DRUN) == CLOCK_FAILED) {
    SPC5_CLOCK_FAILURE_HOOK();
  }

#endif /* !SPC5_NO_INIT */
}

/**
 * @brief   Early initialization code.
 * @note    This initialization must be performed just after stack setup and
 *          before any other initialization.
 *
 * @special
 */
void __early_init(void) {

  spc_clock_init();
}

/**
 * @brief   Switches the system to the specified run mode.
 *
 * @param[in] mode      one of the possible run modes
 *
 * @return              The operation status.
 * @retval CLOCK_SUCCESS if the switch operation has been completed.
 * @retval CLOCK_FAILED  if the switch operation failed.
 */
uint8_t SPCSetRunMode(uint8_t mode) {

  /* Clearing status register bits */
  MC_ME.IS.R = 0x3FU;

  /* Starts a transition process.*/
  MC_ME.MCTL.R = SPC5_ME_MCTL_MODE(mode) | SPC5_ME_MCTL_KEY;
  MC_ME.MCTL.R = SPC5_ME_MCTL_MODE(mode) | SPC5_ME_MCTL_KEY_INV;

  /* Waits for the mode switch or an error condition.*/
  while (MC_ME.IS.R == 0U) {
    ;
  }
  /* Check if no error during mode switch */
  if (MC_ME.IS.B.I_MTC == 1U) {
    return CLOCK_SUCCESS;
  } else {
    return CLOCK_FAILED;
  }
}

/**
 * @brief   Changes the clock mode of a peripheral.
 *
 * @param[in] n         index of the @p PCTL register
 * @param[in] pctl      new value for the @p PCTL register
 *
 * @notapi
 */
void SPCSetPeripheralClockMode(uint32_t n, uint32_t pctl) {
  uint8_t mode;

  MC_ME.PCTL[n].R = (uint8_t)pctl;
  mode = (uint8_t)MC_ME.MCTL.B.TARGET_MODE;
  if(SPCSetRunMode(mode) == CLOCK_FAILED) {
    SPC5_CLOCK_FAILURE_HOOK();
  }
}

#if (SPC5_NO_INIT == FALSE) || defined(__DOXYGEN__)
/**
 * @brief   Returns the system clock under the current run mode.
 *
 * @return              The system clock in Hertz.
 */
uint32_t SPCGetSystemClock(void) {
  uint32_t sysclk;

  sysclk = MC_ME.GS.B.S_SYSCLK;
  switch (sysclk) {
  case SPC5_ME_GS_SYSCLK_IRC:
    return SPC5_IRC_CLK / (MC_CGM.SC_DC0.B.DIV + 1UL);
  case SPC5_ME_GS_SYSCLK_XOSC:
    return SPC5_XOSC_CLK / (MC_CGM.SC_DC0.B.DIV + 1UL);
  case SPC5_ME_GS_SYSCLK_PLL0PHI:
    return SPC5_PLL0_PHI_CLK / (MC_CGM.SC_DC0.B.DIV + 1UL);
  case SPC5_ME_GS_SYSCLK_PLL1PHI:
    return SPC5_PLL1_PHI_CLK / (MC_CGM.SC_DC0.B.DIV + 1UL);
  default:
    return 0;
  }
}

/**
 * @brief   Returns the peripheral clock.
 *
 * @param[in] peripheral  identifier of the peripheral related to the clock to
 *                        be returned.
 *
 * @return              The peripheral clock in Hertz.
 */
uint32_t SPCGetPeripheralClock(peripheral_t peripheral) {

  switch (peripheral) {
  case SPC5_PERIPHERAL_PIT0:
    return SPC5_PER_CLK;
  default:
    return 0;
  }
}
#endif /* !SPC5_NO_INIT */

/** @} */
