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
 * @file    crc_lld.h
 * @brief   SPC5xx CRC low level driver header.
 *
 * @addtogroup CRC
 * @{
 */

#ifndef _CRC_LLD_H_
#define _CRC_LLD_H_

#include "spc5_lld.h"
#include "lldconf.h"

#if (LLD_USE_CRC == TRUE) || defined(__DOXYGEN__)

/*******************************************************************************
* Types
*******************************************************************************/
/**
 * @brief    CRC computation results
 */
typedef enum
{
	CRC_NO_ERROR,		/**< @brief   no errors. */
	CRC_ERROR_STATUS,	/**< @brief   some error happened on HW computation. */
	CRC_ERROR_MODULE,	/**< @brief   module not available. */
	CRC_ERROR_CONTEXT,	/**< @brief   context not available. */
	CRC_ERROR_DISABLED	/**< @brief   crc not configured. */
} crc_result_t;

/**
 * @brief    CRC type requests
 */
typedef enum
{
	CRC_TYPE_MODULE,	/**< @brief   request type for module. */
	CRC_TYPE_CONTEXT	/**< @brief   request type for context. */
} crc_type_t;

/*******************************************************************************
* Global functions
*******************************************************************************/
void crc_lld_init(void);
void crc_lld_deinit(void);
uint32_t crc_lld_get_max(crc_type_t crc_type);
crc_result_t crc_lld_calc(uint8_t crc_no, uint8_t ctx_no, uint8_t *msg, uint32_t msg_size, uint32_t *sign);
crc_result_t crc_lld_status(uint8_t crc_no, uint8_t ctx_no);

#endif /* LLD_USE_CRC */
#endif

/** @} */
