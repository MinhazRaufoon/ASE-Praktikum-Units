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
 * @file    irq_cfg.c
 * @brief   IRQ configuration code.
 *
 * @addtogroup IRQ
 * @{
 */

#include "irq.h"


/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module ISRs.                                                              */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Generated initialization code.
 *
 * @special
 */
void irq_cfg_init(void) {

  INTC_PSR(60) = INTC_PSR_ENABLE(INTC_PSR_MAINCORE, 8);
  INTC_PSR(61) = INTC_PSR_ENABLE(INTC_PSR_MAINCORE, 12);
  INTC_PSR(127) = INTC_PSR_ENABLE(INTC_PSR_MAINCORE, 12);
}

/** @} */
