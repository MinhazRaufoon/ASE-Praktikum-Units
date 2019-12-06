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
 * @file    siul_lld.h
 * @brief   SPC5xx SIU/SIUL low level driver header.
 *
 * @addtogroup SIUL
 * @{
 */

#ifndef _SIUL_LLD_H_
#define _SIUL_LLD_H_

#include "spc5_lld.h"
#include "lldconf.h"

#if (LLD_USE_PAL == TRUE) || defined(__DOXYGEN__)

#include "pal.h"

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Returns the logical state of a pad configured as input
 *
 * @param[in] port      Port number related to the pad
 * @param[in] pin       Pin number within the port related to the pad
 * @return              The pad logical state.
 *
 * @api
 */
#define siul_lld_readpad(port, pin)           pal_readpad(port, pin)

/**
 * @brief   Writes the logical state of a pad configured as output
 *
 * @param[in] port      Port number related to the pad
 * @param[in] pin       Pin number within the port related to the pad
 * @param[in] value     Logical value to be written
 *
 * @api
 */
#define siul_lld_writepad(port, pin, value)   pal_writepad(port, pin, value)

/**
 * @brief   Sets the logical state of a pad configured as output
 *
 * @param[in] port      Port number related to the pad
 * @param[in] pin       Pin number within the port related to the pad
 *
 * @api
 */
#define siul_lld_setpad(port, pin)            pal_setpad(port, pin)

/**
 * @brief   Clears the logical state of a pad configured as output
 *
 * @param[in] port      Port number related to the pad
 * @param[in] pin       Pin number within the port related to the pad
 *
 * @api
 */
#define siul_lld_clearpad(port, pin)          pal_clearpad(port, pin)

/**
 * @brief   Toggles the logical state of a pad configured as output
 *
 * @param[in] port      Port number related to the pad
 * @param[in] pin       Pin number within the port related to the pad
 *
 * @api
 */
#define siul_lld_togglepad(port, pin)         pal_togglepad(port, pin)

#if (SPC5_HAS_SIUL_PARALLEL_PORT_REG == TRUE) || defined(__DOXYGEN__)
/**
 * @brief   Returns the input logical state of a complete port
 *
 * @param[in] port      Port number to be read
 * @return              The port logical state.
 *
 * @api
 */
#define siul_lld_readport(port)               pal_readport(port)

/**
 * @brief   Returns the output logical state of a complete port
 *
 * @param[in] port      Port number to be read
 * @return              The port logical state.
 *
 * @api
 */
#define siul_lld_readlatch(port)              pal_readlatch(port)

/**
 * @brief   Writes the output logical state of a complete port
 *
 * @param[in] port      Port number to be written
 * @param[in] value     Logical value to be written
 *
 * @api
 */
#define siul_lld_writeport(port, value)       pal_writeport(port, value)
#endif /* SPC5_HAS_SIUL_PARALLEL_PORT_REG */

/**
 * @brief   Following macros guarantee the backward compatibility
 * @{
 */
#define pal_lld_readpad(port, pin)            siul_lld_readpad(port, pin)
#define pal_lld_writepad(port, pin, value)    siul_lld_writepad(port, pin, value)
#define pal_lld_setpad(port, pin)             siul_lld_setpad(port, pin)
#define pal_lld_clearpad(port, pin)           siul_lld_clearpad(port, pin)
#define pal_lld_togglepad(port, pin)          siul_lld_togglepad(port, pin)
#if (SPC5_HAS_SIUL_PARALLEL_PORT_REG == TRUE) || defined(__DOXYGEN__)
#define pal_lld_readport(port)                siul_lld_readport(port)
#define pal_lld_readlatch(port)               siul_lld_readlatch(port)
#define pal_lld_writeport(port, value)        siul_lld_writeport(port, value)
#endif /* SPC5_HAS_SIUL_PARALLEL_PORT_REG */
/** @} */

#endif /* LLD_USE_PAL */

#endif /* _SIUL_LLD_H_ */

/** @} */
