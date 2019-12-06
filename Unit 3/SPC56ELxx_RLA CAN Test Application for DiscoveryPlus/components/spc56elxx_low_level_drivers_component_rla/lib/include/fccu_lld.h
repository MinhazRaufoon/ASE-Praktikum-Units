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
 * @file    fccu_lld.h
 * @brief   SPC5xx FCCU low level driver header.
 *
 * @addtogroup FCCU
 * @{
 */

#ifndef _FCCU_LLD_H_
#define _FCCU_LLD_H_

#include "spc5_lld.h"
#include "lldconf.h"

#if (LLD_USE_FCCU == TRUE) || defined(__DOXYGEN__)

#include "spc5_fccu.h"

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    FCCU Control Register bits definitions
 * @{
 */
#define SPC5_FCCU_CTRL_OPS_IDLE             0U  /* Operation status = Idle */
#define SPC5_FCCU_CTRL_OPS_PROGRESS         1U  /* Operation status = In progress */
#define SPC5_FCCU_CTRL_OPS_ABORTED          2U  /* Operation status = Aborted */
#define SPC5_FCCU_CTRL_OPS_SUCCESS          3U  /* Operation status = Successful */
#define SPC5_FCCU_CTRL_OPR_OP0              0U  /* No operation.*/
#define SPC5_FCCU_CTRL_OPR_OP1              1U  /* Set the FCCU into the CONFIG state.*/
#define SPC5_FCCU_CTRL_OPR_OP2              2U  /* Set the FCCU into the NORMAL state.*/
#define SPC5_FCCU_CTRL_OPR_OP3              3U  /* Read the FCCU state.*/
#define SPC5_FCCU_CTRL_OPR_OP4              4U  /* Read the FCCU frozen status flags.*/
#define SPC5_FCCU_CTRL_OPR_OP5              5U  /* Read the FCCU frozen status flags.*/
#define SPC5_FCCU_CTRL_OPR_OP6              6U  /* Read the FCCU frozen status flags.*/
#define SPC5_FCCU_CTRL_OPR_OP7              7U  /* Read the FCCU frozen status flags.*/
#define SPC5_FCCU_CTRL_OPR_OP8              8U  /* Read the FCCU frozen status flags.*/
#define SPC5_FCCU_CTRL_OPR_OP9              9U  /* Read the CF status register.*/
#define SPC5_FCCU_CTRL_OPR_OP10             10U /* Read the NCF status register.*/
#define SPC5_FCCU_CTRL_OPR_OP11             11U /* CF status clear operation in progress.*/
#define SPC5_FCCU_CTRL_OPR_OP12             12U /* NCF status clear operation in progress.*/
#define SPC5_FCCU_CTRL_OPR_OP13             13U /* Clear the freeze status registers.*/
#define SPC5_FCCU_CTRL_OPR_OP14             14U /* CONFIG to NORMAL FCCU state (configuration timeout) in progress.*/
#define SPC5_FCCU_CTRL_OPR_OP15             15U /* Clear the operation status.*/
#define SPC5_FCCU_CTRL_OPR_OP16             16U /* Lock the FCCU configuration.*/
#define SPC5_FCCU_CTRL_OPR_OP17             17U /* Read the ALARM timer.*/
#define SPC5_FCCU_CTRL_OPR_OP18             18U /* Read the SMRT timer.*/
#define SPC5_FCCU_CTRL_OPR_OP19             19U /* Read the CFG timer.*/
#define SPC5_FCCU_CTRL_OPR_OP31             31U /* Run the NVM loading operation.*/
/** @} */

/**
 * @name    FCCU Control Key Register bits definitions
 * @{
 */
#define SPC5_FCCU_CTRLK_OP1_KEY             0x913756AFUL
#define SPC5_FCCU_CTRLK_OP2_KEY             0x825A132BUL
#define SPC5_FCCU_CTRLK_OP16_KEY            0x7ACB32F0UL
#define SPC5_FCCU_CTRLK_OP31_KEY            0x29AF8752UL
/** @} */

/**
 * @name    FCCU Configuration Register bits definitions
 * @{
 */
#define SPC5_FCCU_CFG_SMRT_DELAY1           0U
#define SPC5_FCCU_CFG_SMRT_DELAY2           1U
#define SPC5_FCCU_CFG_SMRT_DELAY4           2U
#define SPC5_FCCU_CFG_SMRT_DELAY8           3U
#define SPC5_FCCU_CFG_SMRT_DELAY16          4U
#define SPC5_FCCU_CFG_SMRT_DELAY32          5U
#define SPC5_FCCU_CFG_SMRT_DELAY64          6U
#define SPC5_FCCU_CFG_SMRT_DELAY128         7U
#define SPC5_FCCU_CFG_SMRT_DELAY256         8U
#define SPC5_FCCU_CFG_SMRT_DELAY512         9U
#define SPC5_FCCU_CFG_SMRT_DELAY1024        10U
#define SPC5_FCCU_CFG_SMRT_DELAY2048        11U
#define SPC5_FCCU_CFG_SMRT_DELAY4096        12U
#define SPC5_FCCU_CFG_SMRT_DELAY8192        13U
#define SPC5_FCCU_CFG_SMRT_DELAY16384       14U
#define SPC5_FCCU_CFG_SMRT_DELAY32768       15U
#define SPC5_FCCU_CFG_CM_LABELLING          0U
#define SPC5_FCCU_CFG_CM_TRANSPARENCY       1U
#define SPC5_FCCU_CFG_SM_SLOW               0U
#define SPC5_FCCU_CFG_SM_FAST               1U
#define SPC5_FCCU_CFG_PS_1H_0L              0U
#define SPC5_FCCU_CFG_PS_1L_0H              1U
#define SPC5_FCCU_CFG_FOM_DUAL_RAIL         0U
#define SPC5_FCCU_CFG_FOM_TIME_SWITCHING    1U
#define SPC5_FCCU_CFG_FOM_BI_STABLE         2U
#define SPC5_FCCU_CFG_FOP_DIV2              0U
#define SPC5_FCCU_CFG_FOP_DIV4              1U
#define SPC5_FCCU_CFG_FOP_DIV6              2U
#define SPC5_FCCU_CFG_FOP_DIV8              3U
#define SPC5_FCCU_CFG_FOP_DIV10             4U
#define SPC5_FCCU_CFG_FOP_DIV12             5U
#define SPC5_FCCU_CFG_FOP_DIV14             6U
/** @} */

/**
 * @name    FCCU CFS Configuration Registers bits definitions
 * @{
 */
#define SPC5_FCCU_CFS_MASK                  (3UL)
#define SPC5_FCCU_CFS_NO_RESET              0U
#define SPC5_FCCU_CFS_SHORT_FUNCTIONAL      1U
#define SPC5_FCCU_CFS_LONG_FUNCTIONAL       2U
/** @} */

/**
 * @name    FCCU NCFS Configuration Registers bits definitions
 * @{
 */
#define SPC5_FCCU_NCFS_MASK                 (3UL)
#define SPC5_FCCU_NCFS_NO_RESET             0U
#define SPC5_FCCU_NCFS_SHORT_FUNCTIONAL     1U
#define SPC5_FCCU_NCFS_LONG_FUNCTIONAL      2U
/** @} */

/**
 * @name    FCCU Critical fault key
 * @{
 */
#define SPC5_FCCU_CRITICAL_FAULT_KEY        0x618B7A50UL
/** @} */

/**
 * @name    FCCU No-Critical fault key
 * @{
 */
#define SPC5_FCCU_NO_CRITICAL_FAULT_KEY     0xAB3498FEUL
/** @} */

/**
 * @name    FCCU NCF Enable Registers bits definitions
 * @{
 */
#define SPC5_FCCU_NCFE_MASK                 (1UL)
#define SPC5_FCCU_NCFE_DISABLE              0U
#define SPC5_FCCU_NCFE_ENABLE               1U
/** @} */

/**
 * @name    FCCU NCF Timeout Enable Registers bits definitions
 * @{
 */
#define SPC5_FCCU_NCFTOE_MASK               (1UL)
#define SPC5_FCCU_NCFTOE_DISABLE            0U
#define SPC5_FCCU_NCFTOE_ENABLE             1U
/** @} */

/**
 * @name    FCCU Status Register bits definitions
 * @{
 */
#define SPC5_FCCU_STATUS_NORMAL             0U
#define SPC5_FCCU_STATUS_CONFIG             1U
#define SPC5_FCCU_STATUS_ALARM              2U
#define SPC5_FCCU_STATUS_FAULT              3U
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @brief   FCCU Configuration interrupt priority level setting.
 */
#if !defined(SPC5_FCCU_CONFIG_IRQ_PRIO) || defined(__DOXYGEN__)
#define SPC5_FCCU_CONFIG_IRQ_PRIO           INTC_PSR_ENABLE(INTC_PSR_MAINCORE, 8)
#endif


/**
 * @brief   FCCU Alarm interrupt priority level setting.
 */
#if !defined(SPC5_FCCU_ALARM_IRQ_PRIO) || defined(__DOXYGEN__)
#define SPC5_FCCU_ALARM_IRQ_PRIO            INTC_PSR_ENABLE(INTC_PSR_MAINCORE, 8)
#endif

/**
 * @brief   FCCU error hook.
 */
#if !defined(SPC5_FCCU_ERROR_HOOK) || defined(__DOXYGEN__)
#define SPC5_FCCU_ERROR_HOOK(fccudp)        irqSysHalt()
#endif

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type of a structure representing a FCCU driver.
 */
typedef struct FCCUDriver FCCUDriver;

/**
 * @brief   FCCU notification callback type.
 *
 * @param[in] fccup     pointer to the @p FCCUDriver object triggering the
 *                      callback
 */
typedef void (*fccucallback_t)(FCCUDriver *fccudp);

/**
 * @brief   FCCU CF channel configuration structure.
 */
typedef struct {
  /**
   * @brief   Internal recoverable fault reaction.
   */
  uint8_t                    int_reaction;
} FCCUCFChannelConfig;

/**
 * @brief   FCCU NCF channel configuration structure.
 */
typedef struct {
  /**
   * @brief   Flag set if the alarm timeout is enabled on the channel.
   */
  uint8_t                    alarm_timeout_en;
  /**
   * @brief   Callback function related to the channel alarm IRQ.
   */
  fccucallback_t             alarm_irq_cb;
  /**
   * @brief   Internal recoverable fault reaction.
   */
  uint8_t                    int_reaction;
} FCCUNCFChannelConfig;

/**
 * @brief   FCCU driver configuration structure.
 */
typedef struct {
  /**
   * @brief   FCCU safe mode request timer selection.
   */
  uint8_t                    smrt;
  /**
   * @brief   FCCU configuration mode selection.
   */
  uint8_t                    cm;
  /**
   * @brief   FCCU switching mode selection.
   */
  uint8_t                    sm;
  /**
   * @brief   FCCU polarity switch selection.
   */
  uint8_t                    ps;
  /**
   * @brief   FCCU fault output mode selection.
   */
  uint8_t                    fom;
  /**
   * @brief   FCCU fault output prescaler.
   */
  uint8_t                    fop;
  /**
   * @brief   FCCU configuration timeout value.
   */
  uint32_t                   config_timeout;
  /**
   * @brief   Flag set if the configuration timeout irq is enabled.
   */
  uint32_t                   config_timeout_irq_en;
  /**
   * @brief   Callback function related to the configuration timeout IRQ.
   */
  fccucallback_t             config_irq_cb;
  /**
   * @brief   FCCU alarm timeout value.
   */
  uint32_t                   alarm_timeout;
  /**
   * @brief   FCCU CF channels configurations.
   */
  const FCCUCFChannelConfig  *cf_channel[SPC5_FCCU_CF_CH_NUMBER];
  /**
   * @brief   FCCU NCF channels configurations.
   */
  const FCCUNCFChannelConfig *ncf_channel[SPC5_FCCU_NCF_CH_NUMBER];
} FCCUConfig;

/**
 * @brief   Structure representing an FCCU driver.
 */
struct FCCUDriver {
  /**
   * @brief   Current configuration data.
   */
  const FCCUConfig           *config;
  /**
   * @brief   Pointer to the FCCU registers block.
   */
  volatile struct spc5_fccu  *fccup;
};

/**
 * @brief   Structure representing the FCCU status.
 */
typedef struct {
  /**
   * @brief   FCCU state machine status.
   */
  uint8_t                    fsm_status;
  /**
   * @brief   FCCU CF Status Registers.
   */
  uint32_t                   cf_status_reg[SPC5_FCCU_CF_CH_NUMBER / 32U];
  /**
   * @brief   FCCU NCF Status Registers.
   */
  uint32_t                   ncf_status_reg[SPC5_FCCU_NCF_CH_NUMBER / 32U];
} FCCUStatus;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @brief   FCCU register value calculation.
 * @details Return an unsigned int with val left-shifted of pos bits and "1" in 
 *          the other positions.
 */
#define SPC5_FCCU_SET_REG_FIELD(reg, mask, pos, val)       (((uint32_t)reg & ~((uint32_t)(mask) << pos)) | ((uint32_t)(val) << pos))

/*===========================================================================*/
/* IRQ Handlers                                                              */
/*===========================================================================*/

IRQ_HANDLER(SPC5_FCCU_ALARM_HANDLER);
IRQ_HANDLER(SPC5_FCCU_CONFIG_HANDLER);

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

extern FCCUDriver FCCUD1;

#ifdef __cplusplus
extern "C" {
#endif
  void fccu_lld_init(void);
  void fccu_lld_clear(FCCUDriver *fccudp);
  void fccu_lld_reset(FCCUDriver *fccudp);
  void fccu_lld_start(FCCUDriver *fccudp, const FCCUConfig *config);
  uint8_t fccu_lld_status(FCCUDriver *fccudp, FCCUStatus *status);
  void fccu_lld_clear_critical_fault(FCCUDriver *fccudp, uint8_t cf_ch);
  void fccu_lld_clear_nocritical_fault(FCCUDriver *fccudp, uint8_t ncf_ch);
  void fccu_lld_lock_conf(FCCUDriver *fccudp);
#ifdef __cplusplus
}
#endif

#endif /* LLD_USE_FCCU */

#endif /* _FCCU_LLD_H_ */

/** @} */
