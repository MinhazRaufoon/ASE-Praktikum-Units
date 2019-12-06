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
 * @file    core1.h
 * @brief   core1 boot module header.
 *
 * @addtogroup PPC_BOOT
 * @{
 */

#ifndef _CORE1_H_
#define _CORE1_H_

#include "boot.h"

#if (BOOT_CORE1 == 1)
/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/
#ifdef __cplusplus
extern "C" {
#endif
  void runCore1(void);
#ifdef __cplusplus
}
#endif

#endif /* BOOT_CORE1 == 1 */

#endif /* _CORE1_H_ */

/** @} */
