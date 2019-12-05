/*
    SPC5 RLA - Copyright (C) 2017 STMicroelectronics

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
 * @file    core1.c
 * @brief   core1 boot module code.
 *
 * @addtogroup PPC_BOOT
 * @{
 */

#include "components.h"

#if (BOOT_CORE1 == 1)
/*===========================================================================*/
/* Module extern definitions.                                                 */
/*===========================================================================*/
extern void *_reset_address1(void);
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
/* Module exported functions.                                                */
/*===========================================================================*/

/**
 * @brief  Run Core 1 using SSCM registers  
 *
 * @api
 */

void runCore1(void){

  /* Start core1.*/
  /* Conversion between a pointer to function and another type needed to update
     the DPMBOOT register with the address of the core1 reset routine.*/
  /*lint -e9074 -e546 */
  SSCM.DPMBOOT.R = ((uint32_t)&_reset_address1 | 0x02UL);
  /*lint +e9074 +e546 */ 
  SSCM.DPMKEY.R = 0x5AF0;
  SSCM.DPMKEY.R = 0xA50F; 
}
#endif /* BOOT_CORE1 */
/** @} */
