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
 * @file    can_lld_cfg.c
 * @brief   CAN Driver configuration code.
 *
 * @addtogroup CAN
 * @{
 */

#include "can_lld_cfg.h"
#include "can.h"

#if (LLD_USE_CAN == TRUE) || defined(__DOXYGEN__)
/*
 * remove info 785 and note 9068 from MISRA check
 * user can define less filter than the maximum defined
 */
/*lint -e785 -e9068*/
/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/


/**
 * @brief   Structure defining the CAN configuration "cfg0".
 */
const CANConfig can_config_cfg0 = {

  CAN_MCR_WRN_EN | CAN_MCR_SRX_DIS,
  CAN_CTRL_PROPSEG(2) | CAN_CTRL_PSEG2(7) |
  CAN_CTRL_PSEG1(2) | CAN_CTRL_PRESDIV(7),
#if (SPC5_CAN_USE_FILTERS == TRUE)
  {
   {0, MASK_REGISTER},
  },
#endif
  /* RX fifo Enabled */
  TRUE,
  /* RX fifo ID Acceptance Mask */
  CAN_RX_FIFO_FORMAT_A,
  /*FIFO Filters*/
  {
  {0, ACCEPTANCE_REGISTER},               /* filter 0 */
  {0, 0},               /* filter 1 */
  {0,0},               /* filter unused 2 */
  {0,0},               /* filter unused 3 */
  {0,0},               /* filter unused 4 */
  {0,0},               /* filter unused 5 */
  {0,0},               /* filter unused 6 */
  {0,0},               /* filter unused 7 */
  {0,0},               /* filter unused 8 */
  {0,0},               /* filter unused 9 */
  {0,0},               /* filter unused 10 */
  {0,0},               /* filter unused 11 */
  {0,0},               /* filter unused 12 */
  {0,0},               /* filter unused 13 */
  {0,0},               /* filter unused 14 */
  {0,0},               /* filter unused 15 */
  {0,0},               /* filter unused 16 */
  {0,0},               /* filter unused 17 */
  {0,0},               /* filter unused 18 */
  {0,0},               /* filter unused 19 */
  {0,0},               /* filter unused 20 */
  {0,0},               /* filter unused 21 */
  {0,0},               /* filter unused 22 */
  {0,0},               /* filter unused 23 */
  {0,0},               /* filter unused 24 */
  {0,0},               /* filter unused 25 */
  {0,0},               /* filter unused 26 */
  {0,0},               /* filter unused 27 */
  {0,0},               /* filter unused 28 */
  {0,0},               /* filter unused 29 */
  {0,0},               /* filter unused 30 */
  {0,0},               /* filter unused 31 */
  },
  /* First MB available for RX and TX */
  8U,
  /* FIFO RX CallBack */
  can_receive,
  /* ERROR Callback */
  cfg0_errorcb,
};

/*===========================================================================*/
/* Driver local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/
/*lint +e785 +e9068*/
#endif /* LLD_USE_CAN */

/** @} */
