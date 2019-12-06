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
 * @file    core.h
 * @brief   Core parameters for the SPC56ELxx.
 * @{
 */

#ifndef _CORE_H_
#define _CORE_H_

/**
 * @brief   Specific model identification macro.
 */
#define _SPC56EL60L3_

/**
 * @brief   Family identification macro.
 */
#define _SPC56ELxx_

/**
 * @brief   Power e200z core model.
 */
#define CORE_VARIANT                4

/**
 * @brief   Main core number.
 */
#define MAIN_CORE                   0

/**
 * @brief   Number of writable bits in IVPR register.
 */
#define CORE_IVPR_BITS              16

/**
 * @brief   IVORx registers support.
 */
#define CORE_SUPPORTS_IVORS         1

/**
 * @brief   Book E instruction set support.
 */
#define CORE_SUPPORTS_BOOKE         1

/**
 * @brief   VLE instruction set support.
 */
#define CORE_SUPPORTS_VLE           1

/**
 * @brief   Supports VLS Load/Store Multiple Volatile instructions.
 */
#define CORE_SUPPORTS_VLE_MULTI     1

/**
 * @brief   Supports the decrementer timer.
 */
#define CORE_SUPPORTS_DECREMENTER   1

/**
 * @brief   Number of pins.
 */
#define CORE_PINS_NUMBER            100U

/**
 * @brief   type of package.
 */
#define CORE_MCU_PACKAGE            LQFP100

#endif /* _CORE_H_ */

/** @} */
