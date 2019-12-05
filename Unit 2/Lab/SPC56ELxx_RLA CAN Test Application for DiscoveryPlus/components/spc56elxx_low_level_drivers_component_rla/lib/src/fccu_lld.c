/*
    SPC5 RLA - Copyright (C) 2019 STMicroelectronics

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
 * @file    fccu_lld.c
 * @brief   SPC5xx FCCU low level driver code.
 *
 * @addtogroup FCCU
 * @{
 */

#include "fccu_lld.h"

#if (LLD_USE_FCCU == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/**
 * @brief   FCCU driver identifier.
 */
FCCUDriver FCCUD1;

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/**
 * @brief   FCCU operation status.
 *
 * @param[in] fccudp    pointer to a @p FCCUDriver object
 *
 * @return              operation status
 *
 * @notapi
 */
static inline uint8_t fccu_lld_get_op_status(FCCUDriver *fccudp) {

  return (uint8_t)(fccudp->fccup->CTRL.B.OPS);
}

/**
 * @brief   Set FCCU into CONFIG state.
 *
 * @param[in] fccudp    pointer to a @p FCCUDriver object
 *
 * @notapi
 */
static void fccu_lld_set_into_config(FCCUDriver *fccudp) {

  fccudp->fccup->CTRLK.R = SPC5_FCCU_CTRLK_OP1_KEY;
  fccudp->fccup->CTRL.R  = (uint32_t)SPC5_FCCU_CTRL_OPR_OP1;

  while(fccu_lld_get_op_status(fccudp) != SPC5_FCCU_CTRL_OPS_SUCCESS) {

  }
}

/**
 * @brief   Set FCCU into NORMAL state.
 *
 * @param[in] fccudp    pointer to a @p FCCUDriver object
 *
 * @notapi
 */
static void fccu_lld_set_into_normal(FCCUDriver *fccudp) {

  fccudp->fccup->CTRLK.R = SPC5_FCCU_CTRLK_OP2_KEY;
  fccudp->fccup->CTRL.R  = (uint32_t)SPC5_FCCU_CTRL_OPR_OP2;

  while(fccu_lld_get_op_status(fccudp) != SPC5_FCCU_CTRL_OPS_SUCCESS) {

  }
}

/**
 * @brief   Read FCCU Status.
 *
 * @param[in] fccudp    pointer to a @p FCCUDriver object
 *
 * @return              FCCU Status
 *
 * @notapi
 */
static inline uint8_t fccu_lld_get_status(FCCUDriver *fccudp) {

  fccudp->fccup->CTRL.R = (uint32_t)SPC5_FCCU_CTRL_OPR_OP3;

  while(fccu_lld_get_op_status(fccudp) != SPC5_FCCU_CTRL_OPS_SUCCESS) {

  }

  return (uint8_t)(fccudp->fccup->STAT.B.STATUS);
}

/**
 * @brief   Read FCCU CF Status register.
 *
 * @param[in] fccudp    pointer to a @p FCCUDriver object
 * @param[in] cfs_reg   FCCU CF Status register number
 *
 * @return              FCCU CF Status register value
 *
 * @notapi
 */
static inline uint32_t fccu_lld_get_cf_status_reg(FCCUDriver *fccudp, uint8_t cfs_reg) {

  fccudp->fccup->CTRL.R = (uint32_t)SPC5_FCCU_CTRL_OPR_OP9;

  while(fccu_lld_get_op_status(fccudp) != SPC5_FCCU_CTRL_OPS_SUCCESS) {

  }

  return (uint32_t)(fccudp->fccup->CFS[cfs_reg].R);
}


/**
 * @brief   Read FCCU NCF Status register.
 *
 * @param[in] fccudp    pointer to a @p FCCUDriver object
 * @param[in] ncfs_reg  FCCU NCF Status register number
 *
 * @return              FCCU NCF Status register value
 *
 * @notapi
 */
static inline uint32_t fccu_lld_get_ncf_status_reg(FCCUDriver *fccudp, uint8_t ncfs_reg) {

  fccudp->fccup->CTRL.R = (uint32_t)SPC5_FCCU_CTRL_OPR_OP10;

  while(fccu_lld_get_op_status(fccudp) != SPC5_FCCU_CTRL_OPS_SUCCESS) {

  }

  return (uint32_t)(fccudp->fccup->NCFS[ncfs_reg].R);
}

/**
 * @brief   Clear FCCU CF Status register bits.
 *
 * @param[in] fccudp    pointer to a @p FCCUDriver object
 * @param[in] cf_reg    FCCU CF Status register number
 * @param[in] value     FCCU CF Status register value
 *
 * @notapi
 */
static inline void fccu_lld_set_cf_status_reg(FCCUDriver *fccudp, uint8_t cf_reg, uint32_t value) {

  fccudp->fccup->CFK.R = SPC5_FCCU_CRITICAL_FAULT_KEY;
  fccudp->fccup->CFS[cf_reg].R = (uint32_t)(value);

  while(fccu_lld_get_op_status(fccudp) != SPC5_FCCU_CTRL_OPS_SUCCESS) {

  }
}

/**
 * @brief   Clear FCCU NCF Status register bits.
 *
 * @param[in] fccudp    pointer to a @p FCCUDriver object
 * @param[in] ncf_reg   FCCU NCF Status register number
 * @param[in] value     FCCU NCF Status register value
 *
 * @notapi
 */
static inline void fccu_lld_set_ncf_status_reg(FCCUDriver *fccudp, uint8_t ncf_reg, uint32_t value) {

  fccudp->fccup->NCFK.R = SPC5_FCCU_NO_CRITICAL_FAULT_KEY;
  fccudp->fccup->NCFS[ncf_reg].R = (uint32_t)(value);

  while(fccu_lld_get_op_status(fccudp) != SPC5_FCCU_CTRL_OPS_SUCCESS) {

  }
}

/**
 * @brief   FCCU Alarm interrupt handler function.
 *
 * @param[in] fccudp    pointer to a @p FCCUDriver object
 *
 * @notapi
 */
static inline void fccu_serve_alarm_interrupt(FCCUDriver *fccudp) {

  uint8_t i, j;
  uint32_t ncf_reg_value;
  uint32_t toe_reg_value;

  osalEnterCriticalFromISR();

  for(i = 0; i < (SPC5_FCCU_NCF_CH_NUMBER / 32U); i++) {
    ncf_reg_value = fccu_lld_get_ncf_status_reg(fccudp, i);
    toe_reg_value = fccudp->fccup->NCF_TOE[i].R;
    if(ncf_reg_value != 0U) {
      for(j = 0; j < 32U; j++) {
        /* If a no-critical fault occurs and the related time out is enabled
		   and a timeout callback function is defined, the callback is invoked.*/
        if(((0x1U & (ncf_reg_value >> j)) == 1U)  &&
           ((0x1U & (toe_reg_value >> j)) == 1U) &&
           (fccudp->config->ncf_channel[(i * 32U + j)]->alarm_irq_cb != NULL)) {
          fccudp->config->ncf_channel[(i * 32U + j)]->alarm_irq_cb(fccudp);
        }
      }
    }
  }

  osalExitCriticalFromISR();
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#if !defined(SPC5_FCCU_ALARM_HANDLER)
#error "SPC5_FCCU_ALARM_HANDLER not defined"
#endif
/**
 * @brief   FCCU Alarm interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_FCCU_ALARM_HANDLER) {

  IRQ_PROLOGUE();

  fccu_serve_alarm_interrupt(&FCCUD1);

  IRQ_EPILOGUE();
}

#if !defined(SPC5_FCCU_CONFIG_HANDLER)
#error "SPC5_FCCU_CONFIG_HANDLER not defined"
#endif
/**
 * @brief   FCCU Configuration interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_FCCU_CONFIG_HANDLER) {

  FCCUDriver *fccudp = &FCCUD1;

  IRQ_PROLOGUE();

  /* If a configuration timeout callback is defined, it is invoked.*/
  if(fccudp->config->config_irq_cb != NULL) {
    fccudp->config->config_irq_cb(fccudp);
  }

  /* Clear the configuration timeout Status flag.*/
  fccudp->fccup->IRQ_STAT.B.CFG_TO_STAT = 1U;

  IRQ_EPILOGUE();
}

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level FCCU driver initialization.
 *
 * @init
 */
void fccu_lld_init(void) {

  FCCUD1.fccup = &SPC5_FCCU;
  INTC_PSR(SPC5_FCCU_CONFIG_INT_NUMBER) = SPC5_FCCU_CONFIG_IRQ_PRIO;
}

/**
 * @brief   Clear FCCU CF/NCF flags.
 *
 * @param[in] fccudp    pointer to a @p FCCUDriver object
 *
 * @api
 */
void fccu_lld_clear(FCCUDriver *fccudp) {

  uint8_t i;

  do {
    /* Clear all FCCU CF Status registers.*/
    for(i = 0; i < (SPC5_FCCU_CF_CH_NUMBER / 32U); i++) {
      fccu_lld_set_cf_status_reg(fccudp, i, 0xFFFFFFFFUL);
    }
    /* Clear all FCCU NCF Status registers.*/
    for(i = 0; i < (SPC5_FCCU_NCF_CH_NUMBER / 32U); i++) {
      fccu_lld_set_ncf_status_reg(fccudp, i, 0xFFFFFFFFUL);
    }
  } while(fccu_lld_get_status(fccudp) != SPC5_FCCU_STATUS_NORMAL);
}

/**
 * @brief   Reset FCCU after a fault.
 *
 * @param[in] fccudp    pointer to a @p FCCUDriver object
 *
 * @api
 */
void fccu_lld_reset(FCCUDriver *fccudp) {

  uint8_t i;

  do {

    /* Clear all FCCU CF Status registers.*/
    for(i = 0; i < (SPC5_FCCU_CF_CH_NUMBER / 32U); i++) {
      fccu_lld_set_cf_status_reg(fccudp, i, 0xFFFFFFFFUL);
    }

    /* Clear all FCCU NCF Status registers.*/
    for(i = 0; i < (SPC5_FCCU_NCF_CH_NUMBER / 32U); i++) {
      fccu_lld_set_ncf_status_reg(fccudp, i, 0xFFFFFFFFUL);
    }

    /* Reset FCCU through the RGM register.*/
    RGM.FES.R = 0xFFFFU;

  } while(fccu_lld_get_status(fccudp) != SPC5_FCCU_STATUS_NORMAL);

  /* When a fault occurs, the FCCU moves the core in SAFE mode. After clearing
     the faults, the core can leave the SAFE mode and move in DRUN mode before
     to be reinitialized.*/
  if (SPCGetRunMode() == SPC5_RUNMODE_SAFE) {
    if (SPCSetRunMode(SPC5_RUNMODE_DRUN) == CLOCK_FAILED) {
      SPC5_CLOCK_FAILURE_HOOK();
    }
  }
}

/**
 * @brief   Low level FCCU driver configuration and start.
 *
 * @param[in] fccudp    pointer to a @p FCCUDriver object
 * @param[in] config    the architecture-dependent FCCU driver configuration.
 *
 * @api
 */
void fccu_lld_start(FCCUDriver *fccudp, const FCCUConfig *config) {

  uint8_t i;
  uint8_t ch_reg;
  uint8_t ch_pos;

  /* Setup the FCCU configuration.*/
  fccudp->config = config;

  /* The ALARM IRQ is enabled in the fccu_lld_start function (instead of in the
     fccu_lld_init function) in order to avoid that after a functional reset
     the related callback function will be called before its initialization.*/
  INTC_PSR(SPC5_FCCU_ALARM_INT_NUMBER) = SPC5_FCCU_ALARM_IRQ_PRIO;

  /* Setup configuration timeout.*/
  fccudp->fccup->CFG_TO.B.TO = (uint8_t)(fccudp->config->config_timeout);

  /* Check if enable the configuration timeout irq.*/
  if(fccudp->config->config_timeout_irq_en == TRUE) {
    fccudp->fccup->IRQ_EN.B.CFG_TO_IEN = 1U;
  }

  /* Set FCCU into CONFIG state.*/
  fccu_lld_set_into_config(fccudp);

  /* Check if the FCCU is set in CONFIG state.*/
  if(fccu_lld_get_status(fccudp) != SPC5_FCCU_STATUS_CONFIG) {
    SPC5_FCCU_ERROR_HOOK(fccudp);
  }

  /* Configure all critical faults as SW recoverable faults.*/
  for(i = 0; i < (SPC5_FCCU_CF_CH_NUMBER / 32U); i++) {
    fccudp->fccup->CF_CFG[i].R = 0xFFFFFFFFUL;
  }

  /* Configure all no-critical faults as SW recoverable faults.*/
  for(i = 0; i < (SPC5_FCCU_NCF_CH_NUMBER / 32U); i++) {
    fccudp->fccup->NCF_CFG[i].R = 0xFFFFFFFFUL;
  }

  /* Setup critical fault state configuration.*/
  for(i = 0; i < SPC5_FCCU_CF_CH_NUMBER; i++) {
    ch_reg = i / 16U;
    ch_pos = ((i % 16U) * 2U);
    if(fccudp->config->cf_channel[i] != NULL) {
      fccudp->fccup->CFS_CFG[ch_reg].R = SPC5_FCCU_SET_REG_FIELD(fccudp->fccup->CFS_CFG[ch_reg].R, SPC5_FCCU_CFS_MASK, ch_pos, (fccudp->config->cf_channel[i]->int_reaction));
    } else {
      fccudp->fccup->CFS_CFG[ch_reg].R = SPC5_FCCU_SET_REG_FIELD(fccudp->fccup->CFS_CFG[ch_reg].R, SPC5_FCCU_CFS_MASK, ch_pos, SPC5_FCCU_CFS_NO_RESET);
    }
  }

  /* Setup no-critical fault state configuration.*/
  for(i = 0; i < SPC5_FCCU_NCF_CH_NUMBER; i++) {
    ch_reg = i / 16U;
    ch_pos = ((i % 16U) * 2U);
    if(fccudp->config->ncf_channel[i] != NULL) {
      fccudp->fccup->NCFS_CFG[ch_reg].R = SPC5_FCCU_SET_REG_FIELD(fccudp->fccup->NCFS_CFG[ch_reg].R, SPC5_FCCU_NCFS_MASK, ch_pos, (fccudp->config->ncf_channel[i]->int_reaction));
    } else {
      fccudp->fccup->NCFS_CFG[ch_reg].R = SPC5_FCCU_SET_REG_FIELD(fccudp->fccup->NCFS_CFG[ch_reg].R, SPC5_FCCU_NCFS_MASK, ch_pos, SPC5_FCCU_NCFS_NO_RESET);
    }
  }

  /* Enable no-critical faults.*/
  for(i = 0; i < SPC5_FCCU_NCF_CH_NUMBER; i++) {
    ch_reg = i / 32U;
    ch_pos = (i % 32U);
    if(fccudp->config->ncf_channel[i] != NULL) {
      fccudp->fccup->NCFE[ch_reg].R = SPC5_FCCU_SET_REG_FIELD(fccudp->fccup->NCFE[ch_reg].R, SPC5_FCCU_NCFE_MASK, ch_pos, SPC5_FCCU_NCFE_ENABLE);
    } else {
      fccudp->fccup->NCFE[ch_reg].R = SPC5_FCCU_SET_REG_FIELD(fccudp->fccup->NCFE[ch_reg].R, SPC5_FCCU_NCFE_MASK, ch_pos, SPC5_FCCU_NCFE_DISABLE);
    }
  }

  /* Enable no-critical fault timeout.*/
  for(i = 0; i < SPC5_FCCU_NCF_CH_NUMBER; i++) {
    ch_reg = i / 32U;
    ch_pos = (i % 32U);
    if((fccudp->config->ncf_channel[i] != NULL) && (fccudp->config->ncf_channel[i]->alarm_timeout_en == TRUE)) {
      fccudp->fccup->NCF_TOE[ch_reg].R = SPC5_FCCU_SET_REG_FIELD(fccudp->fccup->NCF_TOE[ch_reg].R, SPC5_FCCU_NCFTOE_MASK, ch_pos, SPC5_FCCU_NCFTOE_ENABLE);
    } else {
      fccudp->fccup->NCF_TOE[ch_reg].R = SPC5_FCCU_SET_REG_FIELD(fccudp->fccup->NCF_TOE[ch_reg].R, SPC5_FCCU_NCFTOE_MASK, ch_pos, SPC5_FCCU_NCFTOE_DISABLE);
    }
  }

  /* Set no-critical fault alarm timeout.*/
  fccudp->fccup->NCF_TO.R = fccudp->config->alarm_timeout;

  /* Set the FCCU Configuration register fields.*/
  fccudp->fccup->CFG.B.FOP = fccudp->config->fop;
  fccudp->fccup->CFG.B.FOM = fccudp->config->fom;
  fccudp->fccup->CFG.B.PS = fccudp->config->ps;
  fccudp->fccup->CFG.B.SM = fccudp->config->sm;
  fccudp->fccup->CFG.B.CM = fccudp->config->cm;
  fccudp->fccup->CFG.B.SMRT = fccudp->config->smrt;

  /* Set FCCU into NORMAL state.*/
  fccu_lld_set_into_normal(fccudp);

  /* Check if the FCCU is set in NORMAL state.*/
  if(fccu_lld_get_status(fccudp) != SPC5_FCCU_STATUS_NORMAL) {
    SPC5_FCCU_ERROR_HOOK(fccudp);
  }
}

/**
 * @brief   Return the FCCU status.
 *
 * @param[in] fccudp    pointer to a @p FCCUDriver object
 * @param[in] status    structure containing the FCCU state machine status and
 *                      the values of the CF/NCF Status registers
 *
 * @return              FALSE if no fault is occurred, TRUE otherwise
 *
 * @api
 */
uint8_t fccu_lld_status(FCCUDriver *fccudp, FCCUStatus *status) {

  uint8_t i;
  uint8_t fault = FALSE;

  status->fsm_status = fccu_lld_get_status(fccudp);

  for(i = 0; i < SPC5_FCCU_CF_CH_NUMBER / 32U; i++) {
    status->cf_status_reg[i] = fccu_lld_get_cf_status_reg(fccudp, i);
    status->ncf_status_reg[i] = fccu_lld_get_ncf_status_reg(fccudp, i);
    if(status->cf_status_reg[i] != 0UL || status->ncf_status_reg[i] != 0UL) {
      fault = TRUE;
    }
  }

  return fault;
}

/**
 * @brief   Clear the FCCU critical fault related to the specified channel.
 *
 * @param[in] fccudp    pointer to a @p FCCUDriver object
 * @param[in] cf_ch     FCCU critical fault channel
 *
 * @api
 */
void fccu_lld_clear_critical_fault(FCCUDriver *fccudp, uint8_t cf_ch) {

  do {
    /* Clear the FCCU CF fault.*/
    fccu_lld_set_cf_status_reg(fccudp, (cf_ch / 32U), (1UL << (cf_ch % 32U)));
  } while(fccu_lld_get_status(fccudp) != SPC5_FCCU_STATUS_NORMAL);
}

/**
 * @brief   Clear the FCCU no-critical fault related to the specified channel.
 *
 * @param[in] fccudp    pointer to a @p FCCUDriver object
 * @param[in] ncf_ch    FCCU no-critical fault channel
 *
 * @api
 */
void fccu_lld_clear_nocritical_fault(FCCUDriver *fccudp, uint8_t ncf_ch) {

  do {
    /* Clear the FCCU NCF fault.*/
    fccu_lld_set_ncf_status_reg(fccudp, (ncf_ch / 32U), (1UL << (ncf_ch % 32U)));
  } while(fccu_lld_get_status(fccudp) != SPC5_FCCU_STATUS_NORMAL);
}

/**
 * @brief   Lock FCCU configuration.
 *
 * @param[in] fccudp    pointer to a @p FCCUDriver object
 *
 * @api
 */
void fccu_lld_lock_conf(FCCUDriver *fccudp) {

  fccudp->fccup->CTRLK.R = SPC5_FCCU_CTRLK_OP16_KEY;
  fccudp->fccup->CTRL.R  = (uint32_t)SPC5_FCCU_CTRL_OPR_OP2;

  while(fccu_lld_get_op_status(fccudp) != SPC5_FCCU_CTRL_OPS_SUCCESS) {

  }
}

#endif /* LLD_USE_FCCU */

/** @} */
