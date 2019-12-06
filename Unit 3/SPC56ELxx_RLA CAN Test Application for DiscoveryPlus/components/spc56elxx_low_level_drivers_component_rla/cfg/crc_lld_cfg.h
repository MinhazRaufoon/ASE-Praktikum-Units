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
 * @file    crc_lld_cfg.h
 * @brief   CRC Driver configuration macros and structures.
 * @addtogroup CRC
 * @{
 */

#ifndef _CRC_LLD_CFG_H_
#define _CRC_LLD_CFG_H_

#if (LLD_USE_CRC == TRUE) || defined(__DOXYGEN__)

/* Depending of the platform used you may have available:
 *
 * - At least one or more CRC modules
 * - At least one or more Contexts per CRC module 
 *
 */
/*===========================================================================*/
/* Driver constants, data structures and types.                              */
/*===========================================================================*/


#define CRC_MAX_MODULE					0x01U
#define CRC_MAX_CONTEXT					0x03U

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/
#endif /* LLD_USE_CRC */

#endif /* _CRC_LLD_CFG_H_ */

/** @} */
