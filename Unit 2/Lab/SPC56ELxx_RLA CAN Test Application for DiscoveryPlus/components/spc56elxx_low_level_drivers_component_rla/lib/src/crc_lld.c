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
 * @file    crc_lld.c
 * @brief   SPC5xx CRC low level driver code.
 *
 * @addtogroup CRC
 * @{
 */
#include "crc_lld.h"
#include "crc_lld_cfg.h"

#if (LLD_USE_CRC == TRUE) || defined(__DOXYGEN__)

/*******************************************************************************
* Constants and macros
*******************************************************************************/
/* 
 * Dummy initialization and never used if second CRC module doesn't exist.
 * and to match with MISRA rules
 */
#ifndef CRC_1
#define CRC_1 CRC_0
#define SPC5_CRC_1_PTCL SPC5_CRC_0_PTCL
#endif
#ifndef CRC_CONTEXT_ENABLE
#define CRC_CONTEXT_ENABLE	0x40U
#endif
#define CRC_SEED_RESET		0xFFFFFFFFU

/* The max number of CRC modules to manage */
static volatile struct CRC_tag *CRC_Tag[2];

/*******************************************************************************
* Local functions
*******************************************************************************/
static crc_result_t crc_lld_check(uint8_t crc_no, uint8_t ctx_no) {
	/* Check the maxminum number of available CRC modules */
	if (crc_no >= CRC_MAX_MODULE) {
		return CRC_ERROR_MODULE;
	}
	
	/* Check the maxminum of CRC contexts */
	if (ctx_no >= CRC_MAX_CONTEXT) {
		return CRC_ERROR_CONTEXT;
	}
	
	/* Check if i-esimo CRC module is present */
	if (CRC_Module[crc_no] == 0U) {
		return CRC_ERROR_MODULE;
	}
	
	/* Check if the couple (CRC number, Context number) is enabled */
	if ((CRC_Config[crc_no][ctx_no] & CRC_CONTEXT_ENABLE) == 0U) {
		return CRC_ERROR_DISABLED;
	}
	
	return CRC_NO_ERROR;
}

static inline uint32_t crc_lld_ptcl(uint8_t crc_no) {
	return (crc_no == 0U ? (uint32_t)SPC5_CRC_0_PTCL : (uint32_t)SPC5_CRC_1_PTCL);
}

/*******************************************************************************
* Global functions
*******************************************************************************/
/**
 * @brief   Configure CRC system modules
 *
 * @api
 */
void crc_lld_init(void) {
	uint8_t crc_no, ctx_no;

	/* To match with MISRA rules */
	CRC_Tag[0] = &CRC_0;
	CRC_Tag[1] = &CRC_1;

	for (crc_no = 0U; crc_no < CRC_MAX_MODULE; crc_no++) {
		if (CRC_Module[crc_no] == 1U) {
			SPCSetPeripheralClockMode(crc_lld_ptcl(crc_no),
					(SPC5_ME_PCTL_RUN(2) | SPC5_ME_PCTL_LP(2)));
			for (ctx_no = 0U; ctx_no < CRC_MAX_CONTEXT; ctx_no++) {
				CRC_Tag[crc_no]->CONTEXT[ctx_no].CFG.R = CRC_Config[crc_no][ctx_no];
			}
		}
	}
}

/**
 * @brief   Disable CRC system modules
 *
 * @api
 */
void crc_lld_deinit(void) {
	uint8_t crc_no;
			
	for (crc_no = 0U; crc_no < CRC_MAX_MODULE; crc_no++) {
		if (CRC_Module[crc_no] == 1U) {
			SPCSetPeripheralClockMode(crc_lld_ptcl(crc_no),
					(SPC5_ME_PCTL_RUN(0) | SPC5_ME_PCTL_LP(0)));
		}
	}
}

/**
 * @brief   Return the Maximun Context/CRC module available
 *
 * @param[in] crc_type	the type of the request, module or context type.
 *
 * @return				the max number modules or contexts.
 *
 * @api
 */
uint32_t crc_lld_get_max(crc_type_t crc_type) {
	if (crc_type == CRC_TYPE_MODULE) {
		return CRC_MAX_MODULE;
	}
	return CRC_MAX_CONTEXT;
}

/**
 * @brief   Return the CRC calculation status
 *
 * @param[in] crc_no    number of CRC module to use.
 * @param[in] ctx_no    number of Context to use for selected crc_no module.
 *
 * @return              operation result
 *
 * @api
 */
crc_result_t crc_lld_status(uint8_t crc_no, uint8_t ctx_no) {
	crc_result_t res;

	if ((res = crc_lld_check(crc_no, ctx_no)) == CRC_NO_ERROR) {
		if (CRC_Tag[crc_no]->CONTEXT[ctx_no].CSTAT.R != CRC_SEED_RESET) {
			res = CRC_ERROR_STATUS;
		}
	}
	return res;
}

/**
 * @brief   Calculate CRC signature 
 *
 * @param[in] crc_no    number of CRC module to use.
 * @param[in] ctx_no    number of Context to use for selected crc_no module.
 * @param[in] msg    	 message to computate.
 * @param[in] msg_size  size of message to computate.
 * @param[out] sign     the final signature computated.
 *
 * @return              operation result
 *
 * @api
 */
crc_result_t crc_lld_calc(uint8_t crc_no, uint8_t ctx_no, uint8_t *msg, uint32_t msg_size, uint32_t *sign) {
	crc_result_t res;
	uint8_t i;

	*sign = 0U;
	if ((res = crc_lld_check(crc_no, ctx_no)) == CRC_NO_ERROR) {
		CRC_Tag[crc_no]->CONTEXT[ctx_no].CSTAT.R = CRC_Seed[crc_no][ctx_no];
		for (i = 0U; i < msg_size; i++) {
			CRC_Tag[crc_no]->CONTEXT[ctx_no].INP.BYTE[0] = msg[i];
		}
		*sign = CRC_Tag[crc_no]->CONTEXT[ctx_no].OUTP.R;
		CRC_Tag[crc_no]->CONTEXT[ctx_no].CSTAT.R = CRC_SEED_RESET;
	}
	return res;
}

#endif /* LLD_USE_CRC */
/** @} */
