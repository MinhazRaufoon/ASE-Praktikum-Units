/*
    SPC5 RLA - Copyright (C) 2015 STMicroelectronics

    Licensed under the Apache License, Version 2.0 (the "License").
    You may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    clock.c
 * @brief   SPC56ELxx clock subsystem source.
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

  /* FCCU CF errors clearing.*/
  /* Clear FCCU CF Status Register0 errors.*/
  FCCU.CFK.R = 0x618B7A50UL;
  FCCU.CFS[0].R = 0xFFFFFFFFUL;
  while (FCCU.CTRL.B.OPS != 3U) {
  }

  /* Clear FCCU NCF Status Register0 errors.*/
  FCCU.NCFK.R = 0xAB3498FEUL;
  FCCU.NCFS[0].R  = 0xFFFFFFFFUL;
  while (FCCU.CTRL.B.OPS != 3U) {
  }

  /* RGM errors clearing.*/
  RGM.FES.R = 0xFFFFU;
  RGM.DES.R = 0xFFFFU;
}
#endif /* SPC5_CLEAR_FCCU_RGM */

/**
 * @brief   Return 1 if the core is in SAFE mode as result of a fault latched
 *          by the FCCU, 0 otherwise.
 *
 * @notapi
 */
static uint8_t spc_fccu_safe_mode(void) {

 return (uint8_t)(RGM.FES.B.F_FCCU_SAFE);
}

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
 * @brief   SPC56ELxx clocks and PLL initialization.
 *
 * @note    This function must be invoked only after the system reset.
 *
 * @special
 */
void spc_clock_init(void) {

  /* The clock initialization is bypassed if the core is in SAFE mode after a
     reset issued by the FCCU as result of a fault.*/
  if(spc_fccu_safe_mode() == 0U) {

    /* Waiting for IRC stabilization before attempting anything else.*/
    while (ME.GS.B.S_IRCOSC == 0U){
    }

#if (SPC5_NO_INIT == FALSE)

    /* CMUs initialization.*/
    CGM.CMU_0_CSR.R = 0x6UL;
    CGM.CMU_1_CSR.R = 0UL;
    CGM.CMU_2_CSR.R = 0UL;

#if SPC5_DISABLE_WATCHDOG
    /* SWT disabled.*/
    SWT.SR.R = 0xC520;
    SWT.SR.R = 0xD928;
    SWT.CR.R = 0xFF00000AU;
#endif

    /* Enabling peripheral bridges to allow any operation.*/
    AIPS.MPROT.R      = 0x77777777;
    AIPS.PACR0_7.R    = 0;
    AIPS.PACR8_15.R   = 0;
    AIPS.PACR16_23.R  = 0;
    AIPS.PACR24_31.R  = 0;
    AIPS.OPACR0_7.R   = 0;
    AIPS.OPACR8_15.R  = 0;
    AIPS.OPACR16_23.R = 0;
    AIPS.OPACR24_31.R = 0;
    AIPS.OPACR32_39.R = 0;
    AIPS.OPACR40_47.R = 0;
    AIPS.OPACR48_55.R = 0;
    AIPS.OPACR56_63.R = 0;
    AIPS.OPACR64_71.R = 0;
    AIPS.OPACR72_79.R = 0;
    AIPS.OPACR80_87.R = 0;
    AIPS.OPACR88_95.R = 0;

    /* SSCM initialization. Setting up the most restrictive handling of
       invalid accesses to peripherals.*/
    SSCM.ERROR.R = (uint16_t)SPC5_SSCM_ERROR_INIT;

    /* Clear FCCU/RGM errors if FCCU driver is disabled, otherwise the errors are
       managed by the FCCU driver.*/
#if (SPC5_CLEAR_FCCU_RGM == TRUE)
    spc_clear_fccu_rgm();
#endif /* SPC5_CLEAR_FCCU_RGM */

    /* The system must be in DRUN mode on entry, if this is not the case then
       it is considered a serious anomaly.*/
    if (SPCGetRunMode() != SPC5_RUNMODE_DRUN) {
      SPC5_CLOCK_FAILURE_HOOK();
    }

#if defined(SPC5_OSC_BYPASS)
    /* If the board is equipped with an oscillator instead of a crystal then the
       bypass must be activated.*/
    CGM.OSC_CTL.B.OSCBYP = TRUE;
#endif /* SPC5_OSC_BYPASS */

    /* Setting the various dividers and source selectors.*/
    /* Memory-mapped register definitions incompatible with MISRA rule. */
    /*lint -e10 -e40 -e63*/
    CGM.SC_DC0.R    = (uint8_t)SPC5_CGM_SC_DC0;
    CGM.AC0_DC0_3.R = SPC5_CGM_AC0_DC0 | SPC5_CGM_AC0_DC1;
    CGM.AC0_SC.R    = SPC5_AUX0CLK_SRC;
    CGM.AC1_DC0_3.R = SPC5_CGM_AC1_DC0;
    CGM.AC1_SC.R    = SPC5_AUX1CLK_SRC;
    CGM.AC2_DC0_3.R = SPC5_CGM_AC2_DC0;
    CGM.AC2_SC.R    = SPC5_AUX2CLK_SRC;
    CGM.AC3_SC.R    = SPC5_FMPLL0_CLK_SRC;
    CGM.AC4_SC.R    = SPC5_FMPLL1_CLK_SRC;
    /*lint +e10 +e40 +e63*/

    /* Enables the XOSC in order to check its functionality before proceeding
       with the initialization.*/
    ME.DRUN.R = SPC5_ME_MC_SYSCLK_IRC | SPC5_ME_MC_IRCON | SPC5_ME_MC_XOSC0ON |           \
                SPC5_ME_MC_FLAON_NORMAL | SPC5_ME_MC_MVRON;
    if (SPCSetRunMode(SPC5_RUNMODE_DRUN) == CLOCK_FAILED) {
      SPC5_CLOCK_FAILURE_HOOK();
    }

    /* Initialization of the FMPLLs settings.*/
    CGM.FMPLL[0].CR.R = SPC5_FMPLL0_ODF |
                        SPC5_FMPLL_IDF(SPC5_FMPLL0_IDF_VALUE) |
                        SPC5_FMPLL_NDIV(SPC5_FMPLL0_NDIV_VALUE) |
                        SPC5_FMPLL0_OPTIONS;
    CGM.FMPLL[0].MR.R = SPC5_FMPLL0_MR_INIT;
    CGM.FMPLL[1].CR.R = SPC5_FMPLL1_ODF |
                        SPC5_FMPLL_IDF(SPC5_FMPLL1_IDF_VALUE) |
                        SPC5_FMPLL_NDIV(SPC5_FMPLL1_NDIV_VALUE) |
                        SPC5_FMPLL1_OPTIONS;
    CGM.FMPLL[1].MR.R = SPC5_FMPLL1_MR_INIT;

    /* Run modes initialization, note writes to the MC registers are verified
       by a protection mechanism, the operation success is verified at the
       end of the sequence.*/
    ME.IS.R           = 8;                        /* Resetting I_ICONF status.*/
    ME.MER.R          = SPC5_ME_ME_BITS;          /* Enabled run modes.       */
    ME.SAFE.R         = SPC5_ME_SAFE_MC_BITS;     /* SAFE run mode.           */
    ME.DRUN.R         = SPC5_ME_DRUN_MC_BITS;     /* DRUN run mode.           */
    ME.RUN[0].R       = SPC5_ME_RUN0_MC_BITS;     /* RUN0 run mode.           */
    ME.RUN[1].R       = SPC5_ME_RUN1_MC_BITS;     /* RUN1 run mode.           */
    ME.RUN[2].R       = SPC5_ME_RUN2_MC_BITS;     /* RUN2 run mode.           */
    ME.RUN[3].R       = SPC5_ME_RUN3_MC_BITS;     /* RUN0 run mode.           */
    ME.HALT0.R        = SPC5_ME_HALT0_MC_BITS;    /* HALT0 run mode.          */
    ME.STOP0.R        = SPC5_ME_STOP0_MC_BITS;    /* STOP0 run mode.          */
    if ((ME.IS.B.I_ICONF & 1U) == 1U) {
      /* Configuration rejected.*/
      SPC5_CLOCK_FAILURE_HOOK();
    }

    /* Peripherals run and low power modes initialization.*/
    ME.RUNPC[0].R     = SPC5_ME_RUN_PC0_BITS;
    ME.RUNPC[1].R     = SPC5_ME_RUN_PC1_BITS;
    ME.RUNPC[2].R     = SPC5_ME_RUN_PC2_BITS;
    ME.RUNPC[3].R     = SPC5_ME_RUN_PC3_BITS;
    ME.RUNPC[4].R     = SPC5_ME_RUN_PC4_BITS;
    ME.RUNPC[5].R     = SPC5_ME_RUN_PC5_BITS;
    ME.RUNPC[6].R     = SPC5_ME_RUN_PC6_BITS;
    ME.RUNPC[7].R     = SPC5_ME_RUN_PC7_BITS;
    ME.LPPC[0].R      = SPC5_ME_LP_PC0_BITS;
    ME.LPPC[1].R      = SPC5_ME_LP_PC1_BITS;
    ME.LPPC[2].R      = SPC5_ME_LP_PC2_BITS;
    ME.LPPC[3].R      = SPC5_ME_LP_PC3_BITS;
    ME.LPPC[4].R      = SPC5_ME_LP_PC4_BITS;
    ME.LPPC[5].R      = SPC5_ME_LP_PC5_BITS;
    ME.LPPC[6].R      = SPC5_ME_LP_PC6_BITS;
    ME.LPPC[7].R      = SPC5_ME_LP_PC7_BITS;

    /* CFLASH settings initialized for a maximum clock of 120MHz.*/
    /* Memory-mapped register definitions incompatible with MISRA rule. */
    /*lint -e10 -e40 -e63*/
    CFLASH.PFCR0.B.B02_APC  = 3;
    CFLASH.PFCR0.B.B02_WWSC = 3;
    CFLASH.PFCR0.B.B02_RWSC = 3;
    /*lint +e10 +e40 +e63*/

    /* Switches again to DRUN mode (current mode) in order to update the
       settings.*/
    if (SPCSetRunMode(SPC5_RUNMODE_DRUN) == CLOCK_FAILED) {
      SPC5_CLOCK_FAILURE_HOOK();
    }

    /* If Enabled Clock Out selection after all the other configurations.*/
#if (SPC5_ENABLE_CLOCKOUT == TRUE)
    CGM.OCDS_SC.R  = SPC5_CLKOUT_SRC | SPC5_CGM_OCDS_SELDIV;
    CGM.OC_EN.B.EN = 1U;
#else
    CGM.OC_EN.B.EN = 0U;
#endif
#endif /* !SPC5_NO_INIT */
  }
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
 * @brief   Returns the current system run mode.
 *
 * @return              Current system run mode.
 */
uint8_t SPCGetRunMode(void) {

  return (uint8_t)(ME.GS.B.S_CURRENT_MODE);
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
  ME.IS.R = 0x1FU;

  /* Starts a transition process.*/
  ME.MCTL.R = SPC5_ME_MCTL_MODE(mode) | SPC5_ME_MCTL_KEY;
  ME.MCTL.R = SPC5_ME_MCTL_MODE(mode) | SPC5_ME_MCTL_KEY_INV;

  /* Waits for the mode switch or an error condition.*/
  while (ME.IS.R == 0U){
    ;
  }
  /* Check if no error during mode switch */
  if (ME.IS.B.I_MTC == 1U){
    return CLOCK_SUCCESS;
  }else{
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

  ME.PCTL[n].R = (uint8_t)pctl;
  mode = (uint8_t)ME.MCTL.B.TARGET_MODE;
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

  sysclk = ME.GS.B.S_SYSCLK;
  switch (sysclk) {
  case SPC5_ME_GS_SYSCLK_IRC:
    return SPC5_IRC_CLK;
  case SPC5_ME_GS_SYSCLK_XOSC:
    return SPC5_XOSC_CLK;
  case SPC5_ME_GS_SYSCLK_FMPLL0:
    return SPC5_FMPLL0_CLK;
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
#if (SPC5_SYSCLK_DIVIDER_VALUE == 0U)
    return 0;
#else
    return (SPCGetSystemClock() / SPC5_SYSCLK_DIVIDER_VALUE);
#endif
  default:
    return 0;
  }
}
#endif /* !SPC5_NO_INIT */

/** @} */
