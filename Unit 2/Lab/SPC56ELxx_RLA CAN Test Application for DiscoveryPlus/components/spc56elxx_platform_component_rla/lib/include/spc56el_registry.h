/*
    SPC5 RLA- Copyright (C) 2015 STMicroelectronics

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
 * @file    spc56el_registry.h
 * @brief   SPC56ELxx capabilities registry.
 *
 * @addtogroup PLATFORM
 * @{
 */

#ifndef _SPC56EL_REGISTRY_H_
#define _SPC56EL_REGISTRY_H_

/*===========================================================================*/
/* Platform capabilities.                                                    */
/*===========================================================================*/

/**
 * @name    SPC56ELxx capabilities
 * @{
 */
/* eDMA attributes.*/
#define SPC5_HAS_EDMA                       TRUE
#define SPC5_EDMA_BASE                      0xFFF44000UL
#define SPC5_EDMA_NCHANNELS                 16U
#define SPC5_EDMA_ERR_FLAG_31_0_HANDLER     vector10
#define SPC5_EDMA_CH0_HANDLER               vector11
#define SPC5_EDMA_CH1_HANDLER               vector12
#define SPC5_EDMA_CH2_HANDLER               vector13
#define SPC5_EDMA_CH3_HANDLER               vector14
#define SPC5_EDMA_CH4_HANDLER               vector15
#define SPC5_EDMA_CH5_HANDLER               vector16
#define SPC5_EDMA_CH6_HANDLER               vector17
#define SPC5_EDMA_CH7_HANDLER               vector18
#define SPC5_EDMA_CH8_HANDLER               vector19
#define SPC5_EDMA_CH9_HANDLER               vector20
#define SPC5_EDMA_CH10_HANDLER              vector21
#define SPC5_EDMA_CH11_HANDLER              vector22
#define SPC5_EDMA_CH12_HANDLER              vector23
#define SPC5_EDMA_CH13_HANDLER              vector24
#define SPC5_EDMA_CH14_HANDLER              vector25
#define SPC5_EDMA_CH15_HANDLER              vector26
#define SPC5_EDMA_ERR_FLAG_31_0_NUMBER      10U
#define SPC5_EDMA_CH0_NUMBER                11U
#define SPC5_EDMA_HAS_MUX                   TRUE
#define SPC5_EDMA_DMAMUX_BASE               0xFFFDC000UL
#define SPC5_EDMA_NUM_OF_MUX                1U

/* DSPI attribures.*/
#define SPC5_HAS_DSPI0                      TRUE
#define SPC5_DSPI0_BASE                     0xFFF90000UL
#define SPC5_HAS_DSPI1                      TRUE
#define SPC5_DSPI1_BASE                     0xFFF94000UL
#define SPC5_HAS_DSPI2                      TRUE
#define SPC5_DSPI2_BASE                     0xFFF98000UL
#define SPC5_HAS_DSPI3                      FALSE
#define SPC5_HAS_DSPI4                      FALSE
#define SPC5_HAS_DSPI5                      FALSE
#define SPC5_HAS_DSPI6                      FALSE
#define SPC5_HAS_DSPI7                      FALSE
#define SPC5_HAS_DSPI8                      FALSE
#define SPC5_HAS_DSPI9                      FALSE
#define SPC5_DSPI_FIFO_DEPTH                5U
#define SPC5_DSPI0_PCTL                     4
#define SPC5_DSPI1_PCTL                     5
#define SPC5_DSPI2_PCTL                     6
#define SPC5_DSPI0_TX1_DMA_DEV_ID           1
#define SPC5_DSPI0_TX2_DMA_DEV_ID           0
#define SPC5_DSPI0_RX_DMA_DEV_ID            2
#define SPC5_DSPI1_TX1_DMA_DEV_ID           3
#define SPC5_DSPI1_TX2_DMA_DEV_ID           0
#define SPC5_DSPI1_RX_DMA_DEV_ID            4
#define SPC5_DSPI2_TX1_DMA_DEV_ID           5
#define SPC5_DSPI2_TX2_DMA_DEV_ID           0
#define SPC5_DSPI2_RX_DMA_DEV_ID            6
#define SPC5_DSPI0_EOQF_HANDLER             vector75
#define SPC5_DSPI0_EOQF_NUMBER              75
#define SPC5_DSPI0_TFFF_HANDLER             vector76
#define SPC5_DSPI0_TFFF_NUMBER              76
#define SPC5_DSPI0_RFDF_HANDLER             vector78
#define SPC5_DSPI0_RFDF_NUMBER              78
#define SPC5_DSPI1_EOQF_HANDLER             vector95
#define SPC5_DSPI1_EOQF_NUMBER              95
#define SPC5_DSPI1_TFFF_HANDLER             vector96
#define SPC5_DSPI1_TFFF_NUMBER              96
#define SPC5_DSPI1_RFDF_HANDLER             vector98
#define SPC5_DSPI1_RFDF_NUMBER              98
#define SPC5_DSPI2_EOQF_HANDLER             vector115
#define SPC5_DSPI2_EOQF_NUMBER              115
#define SPC5_DSPI2_TFFF_HANDLER             vector116
#define SPC5_DSPI2_TFFF_NUMBER              116
#define SPC5_DSPI2_RFDF_HANDLER             vector118
#define SPC5_DSPI2_RFDF_NUMBER              118
#define SPC5_DSPI0_ENABLE_CLOCK()                                           \
  SPCSetPeripheralClockMode(SPC5_DSPI0_PCTL, SPC5_SPI_DSPI0_START_PCTL)
#define SPC5_DSPI0_DISABLE_CLOCK()                                          \
  SPCSetPeripheralClockMode(SPC5_DSPI0_PCTL, SPC5_SPI_DSPI0_STOP_PCTL)
#define SPC5_DSPI1_ENABLE_CLOCK()                                           \
  SPCSetPeripheralClockMode(SPC5_DSPI1_PCTL, SPC5_SPI_DSPI1_START_PCTL)
#define SPC5_DSPI1_DISABLE_CLOCK()                                          \
  SPCSetPeripheralClockMode(SPC5_DSPI1_PCTL, SPC5_SPI_DSPI1_STOP_PCTL)
#define SPC5_DSPI2_ENABLE_CLOCK()                                           \
  SPCSetPeripheralClockMode(SPC5_DSPI2_PCTL, SPC5_SPI_DSPI2_START_PCTL)
#define SPC5_DSPI2_DISABLE_CLOCK()                                          \
  SPCSetPeripheralClockMode(SPC5_DSPI2_PCTL, SPC5_SPI_DSPI2_STOP_PCTL)

/* LINFlex attributes.*/
#define SPC5_HAS_LINFLEX0                   TRUE
#define SPC5_LINFLEX0_BASE                  0xFFE40000UL
#define SPC5_LINFLEX0L_BASE                 0xFFE40000UL
#define SPC5_LINFLEX0H_BASE                 0xFFE4008CUL
#define SPC5_LINFLEX0_PCTL                  48
#define SPC5_LINFLEX0_RXI_HANDLER           vector79
#define SPC5_LINFLEX0_TXI_HANDLER           vector80
#define SPC5_LINFLEX0_ERR_HANDLER           vector81
#define SPC5_LINFLEX0_RXI_NUMBER            79
#define SPC5_LINFLEX0_TXI_NUMBER            80
#define SPC5_LINFLEX0_ERR_NUMBER            81
#define SPC5_LINFLEX0_DMA_SUPPORTED         FALSE
#define SPC5_LINFLEX0_CLK                   (SPCGetSystemClock() /       \
                                             SPC5_SYSCLK_DIVIDER_VALUE)

#define SPC5_HAS_LINFLEX1                   TRUE
#define SPC5_LINFLEX1_BASE                  0xFFE44000UL
#define SPC5_LINFLEX1L_BASE                 0xFFE44000UL
#define SPC5_LINFLEX1H_BASE                 0xFFE4404CUL
#define SPC5_LINFLEX1_PCTL                  49
#define SPC5_LINFLEX1_RXI_HANDLER           vector99
#define SPC5_LINFLEX1_TXI_HANDLER           vector100
#define SPC5_LINFLEX1_ERR_HANDLER           vector101
#define SPC5_LINFLEX1_RXI_NUMBER            99
#define SPC5_LINFLEX1_TXI_NUMBER            100
#define SPC5_LINFLEX1_ERR_NUMBER            101
#define SPC5_LINFLEX1_DMA_SUPPORTED         FALSE
#define SPC5_LINFLEX1_CLK                   (SPCGetSystemClock() /       \
                                             SPC5_SYSCLK_DIVIDER_VALUE)

#define SPC5_HAS_LINFLEX2                   FALSE
#define SPC5_HAS_LINFLEX3                   FALSE
#define SPC5_HAS_LINFLEX4                   FALSE
#define SPC5_HAS_LINFLEX5                   FALSE
#define SPC5_HAS_LINFLEX6                   FALSE
#define SPC5_HAS_LINFLEX7                   FALSE
#define SPC5_HAS_LINFLEX8                   FALSE
#define SPC5_HAS_LINFLEX9                   FALSE
#define SPC5_HAS_LINFLEX10                  FALSE
#define SPC5_HAS_LINFLEX11                  FALSE
#define SPC5_HAS_LINFLEX12                  FALSE
#define SPC5_HAS_LINFLEX13                  FALSE
#define SPC5_HAS_LINFLEX14                  FALSE
#define SPC5_HAS_LINFLEX15                  FALSE
#define SPC5_HAS_LINFLEX16                  FALSE
#define SPC5_HAS_LINFLEX17                  FALSE
#define SPC5_HAS_LINFLEX18                  FALSE
#define SPC5_HAS_LINFLEX19                  FALSE
#define SPC5_HAS_LINFLEX20                  FALSE
#define SPC5_HAS_LINFLEX21                  FALSE
#define SPC5_HAS_LINFLEX22                  FALSE
#define SPC5_HAS_LINFLEX23                  FALSE

/* SIUL attributes.*/
#define SPC5_HAS_SIUL                       TRUE
#define SPC5_HAS_SIUL_PARALLEL_PORT_REG     TRUE
#define SPC5_SIUL_NUM_PORTS                 8
#define SPC5_SIUL_NUM_PCRS                  133U
#define SPC5_SIUL_NUM_PADSELS               44U

/* EIRQ */
#define SPC5_SIUL_EIRQ_HAS_0_7_HANDLER      TRUE
#define SPC5_SIUL_EIRQ_HAS_8_15_HANDLER     TRUE
#define SPC5_SIUL_EIRQ_HAS_16_23_HANDLER    TRUE
#define SPC5_SIUL_EIRQ_HAS_24_31_HANDLER    TRUE
#define SPC5_SIUL_EIRQ_0_7_HANDLER          vector41
#define SPC5_SIUL_EIRQ_8_15_HANDLER         vector42
#define SPC5_SIUL_EIRQ_16_23_HANDLER        vector43
#define SPC5_SIUL_EIRQ_24_31_HANDLER        vector44
#define SPC5_SIUL_EIRQ_0_7_INT_NUMBER       41
#define SPC5_SIUL_EIRQ_8_15_INT_NUMBER      42
#define SPC5_SIUL_EIRQ_16_23_INT_NUMBER     43
#define SPC5_SIUL_EIRQ_24_31_INT_NUMBER     44
/** @} */

/* FlexPWM attributes.*/
#define SPC5_HAS_FLEXPWM0                   TRUE
#define SPC5_FLEXPWM0_BASE                  0xFFE24000UL
#define SPC5_FLEXPWM0_PCTL                  41
#define SPC5_FLEXPWM0_RF0_HANDLER           vector179
#define SPC5_FLEXPWM0_COF0_HANDLER          vector180
#define SPC5_FLEXPWM0_CAF0_HANDLER          vector181
#define SPC5_FLEXPWM0_RF1_HANDLER           vector182
#define SPC5_FLEXPWM0_COF1_HANDLER          vector183
#define SPC5_FLEXPWM0_CAF1_HANDLER          vector184
#define SPC5_FLEXPWM0_RF2_HANDLER           vector185
#define SPC5_FLEXPWM0_COF2_HANDLER          vector186
#define SPC5_FLEXPWM0_CAF2_HANDLER          vector187
#define SPC5_FLEXPWM0_RF3_HANDLER           vector188
#define SPC5_FLEXPWM0_COF3_HANDLER          vector189
#define SPC5_FLEXPWM0_CAF3_HANDLER          vector190
#define SPC5_FLEXPWM0_FFLAG_HANDLER         vector191
#define SPC5_FLEXPWM0_REF_HANDLER           vector192
#define SPC5_FLEXPWM0_RF0_NUMBER            179
#define SPC5_FLEXPWM0_COF0_NUMBER           180
#define SPC5_FLEXPWM0_CAF0_NUMBER           181
#define SPC5_FLEXPWM0_RF1_NUMBER            182
#define SPC5_FLEXPWM0_COF1_NUMBER           183
#define SPC5_FLEXPWM0_CAF1_NUMBER           184
#define SPC5_FLEXPWM0_RF2_NUMBER            185
#define SPC5_FLEXPWM0_COF2_NUMBER           186
#define SPC5_FLEXPWM0_CAF2_NUMBER           187
#define SPC5_FLEXPWM0_RF3_NUMBER            188
#define SPC5_FLEXPWM0_COF3_NUMBER           189
#define SPC5_FLEXPWM0_CAF3_NUMBER           190
#define SPC5_FLEXPWM0_FFLAG_NUMBER          191
#define SPC5_FLEXPWM0_REF_NUMBER            192
#define SPC5_FLEXPWM0_CLK                   SPC5_MCONTROL_CLK

#define SPC5_HAS_FLEXPWM1                   TRUE
#define SPC5_FLEXPWM1_BASE                  0xFFE28000UL
#define SPC5_FLEXPWM1_PCTL                  42
#define SPC5_FLEXPWM1_RF0_HANDLER           vector233
#define SPC5_FLEXPWM1_COF0_HANDLER          vector234
#define SPC5_FLEXPWM1_CAF0_HANDLER          vector235
#define SPC5_FLEXPWM1_RF1_HANDLER           vector236
#define SPC5_FLEXPWM1_COF1_HANDLER          vector237
#define SPC5_FLEXPWM1_CAF1_HANDLER          vector238
#define SPC5_FLEXPWM1_RF2_HANDLER           vector239
#define SPC5_FLEXPWM1_COF2_HANDLER          vector240
#define SPC5_FLEXPWM1_CAF2_HANDLER          vector241
#define SPC5_FLEXPWM1_RF3_HANDLER           vector242
#define SPC5_FLEXPWM1_COF3_HANDLER          vector243
#define SPC5_FLEXPWM1_CAF3_HANDLER          vector244
#define SPC5_FLEXPWM1_FFLAG_HANDLER         vector245
#define SPC5_FLEXPWM1_REF_HANDLER           vector246
#define SPC5_FLEXPWM1_RF0_NUMBER            233
#define SPC5_FLEXPWM1_COF0_NUMBER           234
#define SPC5_FLEXPWM1_CAF0_NUMBER           235
#define SPC5_FLEXPWM1_RF1_NUMBER            236
#define SPC5_FLEXPWM1_COF1_NUMBER           237
#define SPC5_FLEXPWM1_CAF1_NUMBER           238
#define SPC5_FLEXPWM1_RF2_NUMBER            239
#define SPC5_FLEXPWM1_COF2_NUMBER           240
#define SPC5_FLEXPWM1_CAF2_NUMBER           241
#define SPC5_FLEXPWM1_RF3_NUMBER            242
#define SPC5_FLEXPWM1_COF3_NUMBER           243
#define SPC5_FLEXPWM1_CAF3_NUMBER           244
#define SPC5_FLEXPWM1_FFLAG_NUMBER          245
#define SPC5_FLEXPWM1_REF_NUMBER            246
#define SPC5_FLEXPWM1_CLK                   SPC5_MCONTROL_CLK

#define SPC5_HAS_FLEXPWM2                   FALSE

/* eTimer attributes.*/
#define SPC5_HAS_ETIMER0                    TRUE
#define SPC5_ETIMER0_BASE                   0xFFE18000UL
#define SPC5_ETIMER0_PCTL                   38
#define SPC5_ETIMER0_TC0IR_HANDLER          vector157
#define SPC5_ETIMER0_TC1IR_HANDLER          vector158
#define SPC5_ETIMER0_TC2IR_HANDLER          vector159
#define SPC5_ETIMER0_TC3IR_HANDLER          vector160
#define SPC5_ETIMER0_TC4IR_HANDLER          vector161
#define SPC5_ETIMER0_TC5IR_HANDLER          vector162
#define SPC5_ETIMER0_WTIF_HANDLER           vector165
#define SPC5_ETIMER0_RCF_HANDLER            vector167
#define SPC5_ETIMER0_TC0IR_NUMBER           157
#define SPC5_ETIMER0_TC1IR_NUMBER           158
#define SPC5_ETIMER0_TC2IR_NUMBER           159
#define SPC5_ETIMER0_TC3IR_NUMBER           160
#define SPC5_ETIMER0_TC4IR_NUMBER           161
#define SPC5_ETIMER0_TC5IR_NUMBER           162
#define SPC5_ETIMER0_WTIF_NUMBER            165
#define SPC5_ETIMER0_RCF_NUMBER             167
#define SPC5_ETIMER0_CLK                    SPC5_MCONTROL_CLK

#define SPC5_HAS_ETIMER1                    TRUE
#define SPC5_ETIMER1_BASE                   0xFFE1C000UL
#define SPC5_ETIMER1_PCTL                   39
#define SPC5_ETIMER1_TC0IR_HANDLER          vector168
#define SPC5_ETIMER1_TC1IR_HANDLER          vector169
#define SPC5_ETIMER1_TC2IR_HANDLER          vector170
#define SPC5_ETIMER1_TC3IR_HANDLER          vector171
#define SPC5_ETIMER1_TC4IR_HANDLER          vector172
#define SPC5_ETIMER1_TC5IR_HANDLER          vector173
#define SPC5_ETIMER1_RCF_HANDLER            vector178
#define SPC5_ETIMER1_TC0IR_NUMBER           168
#define SPC5_ETIMER1_TC1IR_NUMBER           169
#define SPC5_ETIMER1_TC2IR_NUMBER           170
#define SPC5_ETIMER1_TC3IR_NUMBER           171
#define SPC5_ETIMER1_TC4IR_NUMBER           172
#define SPC5_ETIMER1_TC5IR_NUMBER           173
#define SPC5_ETIMER1_RCF_NUMBER             178
#define SPC5_ETIMER1_CLK                    SPC5_MCONTROL_CLK

#define SPC5_HAS_ETIMER2                    TRUE
#define SPC5_ETIMER2_BASE                   0xFFE20000UL
#define SPC5_ETIMER2_PCTL                   40
#define SPC5_ETIMER2_TC0IR_HANDLER          vector222
#define SPC5_ETIMER2_TC1IR_HANDLER          vector223
#define SPC5_ETIMER2_TC2IR_HANDLER          vector224
#define SPC5_ETIMER2_TC3IR_HANDLER          vector225
#define SPC5_ETIMER2_TC4IR_HANDLER          vector226
#define SPC5_ETIMER2_TC5IR_HANDLER          vector227
#define SPC5_ETIMER2_RCF_HANDLER            vector232
#define SPC5_ETIMER2_TC0IR_NUMBER           222
#define SPC5_ETIMER2_TC1IR_NUMBER           223
#define SPC5_ETIMER2_TC2IR_NUMBER           224
#define SPC5_ETIMER2_TC3IR_NUMBER           225
#define SPC5_ETIMER2_TC4IR_NUMBER           226
#define SPC5_ETIMER2_TC5IR_NUMBER           227
#define SPC5_ETIMER2_RCF_NUMBER             232
#define SPC5_ETIMER2_CLK                    SPC5_MCONTROL_CLK

#define SPC5_HAS_ETIMER3                    FALSE

/* FlexCAN attributes.*/
#define SPC5_HAS_FLEXCAN0                   TRUE
#define SPC5_FLEXCAN0_BASE                  0xFFFC0000UL
#define SPC5_FLEXCAN0_PCTL                  16
#define SPC5_FLEXCAN0_MB                    32U
#define SPC5_FLEXCAN0_SHARED_IRQ            TRUE
#define SPC5_FLEXCAN0_ESR_ERR_INT_HANDLER   vector65
#define SPC5_FLEXCAN0_ESR_BOFF_HANDLER      vector66
#define SPC5_FLEXCAN0_ESR_WAK_HANDLER       vector67
#define SPC5_FLEXCAN0_BUF_00_03_HANDLER     vector68
#define SPC5_FLEXCAN0_BUF_04_07_HANDLER     vector69
#define SPC5_FLEXCAN0_BUF_08_11_HANDLER     vector70
#define SPC5_FLEXCAN0_BUF_12_15_HANDLER     vector71
#define SPC5_FLEXCAN0_BUF_16_31_HANDLER     vector72
#define SPC5_FLEXCAN0_ESR_ERR_INT_NUMBER    65
#define SPC5_FLEXCAN0_ESR_BOFF_NUMBER       66
#define SPC5_FLEXCAN0_ESR_WAK_NUMBER        67
#define SPC5_FLEXCAN0_BUF_00_03_NUMBER      68
#define SPC5_FLEXCAN0_BUF_04_07_NUMBER      69
#define SPC5_FLEXCAN0_BUF_08_11_NUMBER      70
#define SPC5_FLEXCAN0_BUF_12_15_NUMBER      71
#define SPC5_FLEXCAN0_BUF_16_31_NUMBER      72
#define SPC5_FLEXCAN0_ENABLE_CLOCK()        SPCSetPeripheralClockMode(SPC5_FLEXCAN0_PCTL, SPC5_CAN_FLEXCAN0_START_PCTL);
#define SPC5_FLEXCAN0_DISABLE_CLOCK()       SPCSetPeripheralClockMode(SPC5_FLEXCAN0_PCTL, SPC5_CAN_FLEXCAN0_STOP_PCTL);

#define SPC5_HAS_FLEXCAN1                   TRUE
#define SPC5_FLEXCAN1_BASE                  0xFFFC4000UL
#define SPC5_FLEXCAN1_PCTL                  17
#define SPC5_FLEXCAN1_MB                    32U
#define SPC5_FLEXCAN1_SHARED_IRQ            TRUE
#define SPC5_FLEXCAN1_ESR_ERR_INT_HANDLER   vector85
#define SPC5_FLEXCAN1_ESR_BOFF_HANDLER      vector86
#define SPC5_FLEXCAN1_ESR_WAK_HANDLER       vector87
#define SPC5_FLEXCAN1_BUF_00_03_HANDLER     vector88
#define SPC5_FLEXCAN1_BUF_04_07_HANDLER     vector89
#define SPC5_FLEXCAN1_BUF_08_11_HANDLER     vector90
#define SPC5_FLEXCAN1_BUF_12_15_HANDLER     vector91
#define SPC5_FLEXCAN1_BUF_16_31_HANDLER     vector92
#define SPC5_FLEXCAN1_ESR_ERR_INT_NUMBER    85
#define SPC5_FLEXCAN1_ESR_BOFF_NUMBER       86
#define SPC5_FLEXCAN1_ESR_WAK_NUMBER        87
#define SPC5_FLEXCAN1_BUF_00_03_NUMBER      88
#define SPC5_FLEXCAN1_BUF_04_07_NUMBER      89
#define SPC5_FLEXCAN1_BUF_08_11_NUMBER      90
#define SPC5_FLEXCAN1_BUF_12_15_NUMBER      91
#define SPC5_FLEXCAN1_BUF_16_31_NUMBER      92
#define SPC5_FLEXCAN1_ENABLE_CLOCK()        SPCSetPeripheralClockMode(SPC5_FLEXCAN1_PCTL, SPC5_CAN_FLEXCAN1_START_PCTL);
#define SPC5_FLEXCAN1_DISABLE_CLOCK()       SPCSetPeripheralClockMode(SPC5_FLEXCAN1_PCTL, SPC5_CAN_FLEXCAN1_STOP_PCTL);

#if defined(_SPC56EL70L5_) || defined(_SPC564L70L5_) || defined(_SPC564L70L3_) 
#define SPC5_HAS_FLEXCAN2                   TRUE
#else
#define SPC5_HAS_FLEXCAN2                   FALSE
#endif
#define SPC5_FLEXCAN2_BASE                  0xFFFC8000UL
#define SPC5_FLEXCAN2_PCTL                  18
#define SPC5_FLEXCAN2_MB                    32U
#define SPC5_FLEXCAN2_SHARED_IRQ            TRUE
#define SPC5_FLEXCAN2_ESR_ERR_INT_HANDLER   vector105
#define SPC5_FLEXCAN2_ESR_BOFF_HANDLER      vector106
#define SPC5_FLEXCAN2_ESR_WAK_HANDLER       vector107
#define SPC5_FLEXCAN2_BUF_00_03_HANDLER     vector108
#define SPC5_FLEXCAN2_BUF_04_07_HANDLER     vector109
#define SPC5_FLEXCAN2_BUF_08_11_HANDLER     vector110
#define SPC5_FLEXCAN2_BUF_12_15_HANDLER     vector111
#define SPC5_FLEXCAN2_BUF_16_31_HANDLER     vector112
#define SPC5_FLEXCAN2_ESR_ERR_INT_NUMBER    105
#define SPC5_FLEXCAN2_ESR_BOFF_NUMBER       106
#define SPC5_FLEXCAN2_ESR_WAK_NUMBER        107
#define SPC5_FLEXCAN2_BUF_00_03_NUMBER      108
#define SPC5_FLEXCAN2_BUF_04_07_NUMBER      109
#define SPC5_FLEXCAN2_BUF_08_11_NUMBER      110
#define SPC5_FLEXCAN2_BUF_12_15_NUMBER      111
#define SPC5_FLEXCAN2_BUF_16_31_NUMBER      112
#define SPC5_FLEXCAN2_ENABLE_CLOCK()        SPCSetPeripheralClockMode(SPC5_FLEXCAN2_PCTL, SPC5_CAN_FLEXCAN2_START_PCTL);
#define SPC5_FLEXCAN2_DISABLE_CLOCK()       SPCSetPeripheralClockMode(SPC5_FLEXCAN2_PCTL, SPC5_CAN_FLEXCAN2_STOP_PCTL);
#define SPC5_HAS_FLEXCAN3                   FALSE
#define SPC5_HAS_FLEXCAN4                   FALSE
#define SPC5_HAS_FLEXCAN5                   FALSE

/* ADC attributes.*/
#define SPC5_ADC_HAS_TRC                    FALSE

#define SPC5_HAS_ADC0                       TRUE
#define SPC5_ADC_ADC0_BASE                  0xFFE00000UL
#define SPC5_ADC_ADC0_HAS_CTR0              TRUE
#define SPC5_ADC_ADC0_HAS_CTR1              TRUE
#define SPC5_ADC_ADC0_HAS_CTR2              FALSE
#define SPC5_ADC_ADC0_HAS_NCMR0             TRUE
#define SPC5_ADC_ADC0_HAS_NCMR1             FALSE
#define SPC5_ADC_ADC0_HAS_NCMR2             FALSE
#define SPC5_ADC_ADC0_HAS_THRHLR0           TRUE
#define SPC5_ADC_ADC0_HAS_THRHLR1           TRUE
#define SPC5_ADC_ADC0_HAS_THRHLR2           TRUE
#define SPC5_ADC_ADC0_HAS_THRHLR3           TRUE
#define SPC5_ADC_ADC0_HAS_THRHLR4           TRUE
#define SPC5_ADC_ADC0_HAS_THRHLR5           TRUE
#define SPC5_ADC_ADC0_HAS_THRHLR6           TRUE
#define SPC5_ADC_ADC0_HAS_THRHLR7           TRUE
#define SPC5_ADC_ADC0_HAS_THRHLR8           TRUE
#define SPC5_ADC_ADC0_HAS_THRHLR9           TRUE
#define SPC5_ADC_ADC0_HAS_THRHLR10          TRUE
#define SPC5_ADC_ADC0_HAS_THRHLR11          TRUE
#define SPC5_ADC_ADC0_HAS_THRHLR12          TRUE
#define SPC5_ADC_ADC0_HAS_THRHLR13          TRUE
#define SPC5_ADC_ADC0_HAS_THRHLR14          TRUE
#define SPC5_ADC_ADC0_HAS_THRHLR15          TRUE
#define SPC5_ADC_ADC0_HAS_CWENR0            TRUE
#define SPC5_ADC_ADC0_HAS_CWENR1            FALSE
#define SPC5_ADC_ADC0_HAS_CWENR2            FALSE
#define SPC5_ADC_ADC0_HAS_CWSEL0            TRUE
#define SPC5_ADC_ADC0_HAS_CWSEL1            TRUE
#define SPC5_ADC_ADC0_HAS_CWSEL2            FALSE
#define SPC5_ADC_ADC0_HAS_CWSEL3            FALSE
#define SPC5_ADC_ADC0_HAS_CWSEL4            FALSE
#define SPC5_ADC_ADC0_HAS_CWSEL5            FALSE
#define SPC5_ADC_ADC0_HAS_CWSEL6            FALSE
#define SPC5_ADC_ADC0_HAS_CWSEL7            FALSE
#define SPC5_ADC_ADC0_HAS_CWSEL8            FALSE
#define SPC5_ADC_ADC0_HAS_CWSEL9            FALSE
#define SPC5_ADC_ADC0_HAS_CWSEL10           FALSE
#define SPC5_ADC_ADC0_HAS_CWSEL11           FALSE
#define SPC5_ADC_ADC0_HAS_CIMR0             TRUE
#define SPC5_ADC_ADC0_HAS_CIMR1             FALSE
#define SPC5_ADC_ADC0_HAS_CIMR2             FALSE
#define SPC5_ADC_ADC0_HAS_CEOCFR0           TRUE
#define SPC5_ADC_ADC0_HAS_CEOCFR1           FALSE
#define SPC5_ADC_ADC0_HAS_CEOCFR2           FALSE
#define SPC5_ADC0_PCTL                      32
#define SPC5_ADC0_DMA_DEV_ID                20
#define SPC5_ADC0_EOC_HANDLER               vector62
#define SPC5_ADC0_EOC_NUMBER                62
#define SPC5_ADC0_WD_HANDLER                vector64
#define SPC5_ADC0_WD_NUMBER                 64

#define SPC5_HAS_ADC1                       TRUE
#define SPC5_ADC_ADC1_BASE                  0xFFE04000UL
#define SPC5_ADC_ADC1_HAS_CTR0              TRUE
#define SPC5_ADC_ADC1_HAS_CTR1              TRUE
#define SPC5_ADC_ADC1_HAS_CTR2              FALSE
#define SPC5_ADC_ADC1_HAS_NCMR0             TRUE
#define SPC5_ADC_ADC1_HAS_NCMR1             FALSE
#define SPC5_ADC_ADC1_HAS_NCMR2             FALSE
#define SPC5_ADC_ADC1_HAS_THRHLR0           TRUE
#define SPC5_ADC_ADC1_HAS_THRHLR1           TRUE
#define SPC5_ADC_ADC1_HAS_THRHLR2           TRUE
#define SPC5_ADC_ADC1_HAS_THRHLR3           TRUE
#define SPC5_ADC_ADC1_HAS_THRHLR4           TRUE
#define SPC5_ADC_ADC1_HAS_THRHLR5           TRUE
#define SPC5_ADC_ADC1_HAS_THRHLR6           TRUE
#define SPC5_ADC_ADC1_HAS_THRHLR7           TRUE
#define SPC5_ADC_ADC1_HAS_THRHLR8           TRUE
#define SPC5_ADC_ADC1_HAS_THRHLR9           TRUE
#define SPC5_ADC_ADC1_HAS_THRHLR10          TRUE
#define SPC5_ADC_ADC1_HAS_THRHLR11          TRUE
#define SPC5_ADC_ADC1_HAS_THRHLR12          TRUE
#define SPC5_ADC_ADC1_HAS_THRHLR13          TRUE
#define SPC5_ADC_ADC1_HAS_THRHLR14          TRUE
#define SPC5_ADC_ADC1_HAS_THRHLR15          TRUE
#define SPC5_ADC_ADC1_HAS_CWENR0            TRUE
#define SPC5_ADC_ADC1_HAS_CWENR1            FALSE
#define SPC5_ADC_ADC1_HAS_CWENR2            FALSE
#define SPC5_ADC_ADC1_HAS_CWSEL0            TRUE
#define SPC5_ADC_ADC1_HAS_CWSEL1            TRUE
#define SPC5_ADC_ADC1_HAS_CWSEL2            FALSE
#define SPC5_ADC_ADC1_HAS_CWSEL3            FALSE
#define SPC5_ADC_ADC1_HAS_CWSEL4            FALSE
#define SPC5_ADC_ADC1_HAS_CWSEL5            FALSE
#define SPC5_ADC_ADC1_HAS_CWSEL6            FALSE
#define SPC5_ADC_ADC1_HAS_CWSEL7            FALSE
#define SPC5_ADC_ADC1_HAS_CWSEL8            FALSE
#define SPC5_ADC_ADC1_HAS_CWSEL9            FALSE
#define SPC5_ADC_ADC1_HAS_CWSEL10           FALSE
#define SPC5_ADC_ADC1_HAS_CWSEL11           FALSE
#define SPC5_ADC_ADC1_HAS_CIMR0             TRUE
#define SPC5_ADC_ADC1_HAS_CIMR1             FALSE
#define SPC5_ADC_ADC1_HAS_CIMR2             FALSE
#define SPC5_ADC_ADC1_HAS_CEOCFR0           TRUE
#define SPC5_ADC_ADC1_HAS_CEOCFR1           FALSE
#define SPC5_ADC_ADC1_HAS_CEOCFR2           FALSE
#define SPC5_ADC1_PCTL                      33
#define SPC5_ADC1_DMA_DEV_ID                21
#define SPC5_ADC1_EOC_HANDLER               vector82
#define SPC5_ADC1_EOC_NUMBER                82
#define SPC5_ADC1_WD_HANDLER                vector84
#define SPC5_ADC1_WD_NUMBER                 84

/* PIT Attributes */
#define SPC5_HAS_PIT                        TRUE
#define SPC5_PIT_BASE                       0xC3FF0000UL
#define SPC5_PIT_CHANNELS                   4
#define SPC5_PIT_PCTL                       92
#define SPC5_PIT_ENABLE_CLOCK()             SPCSetPeripheralClockMode(SPC5_PIT_PCTL, SPC5_PIT_START_PCTL);
#define SPC5_PIT_DISABLE_CLOCK()            SPCSetPeripheralClockMode(SPC5_PIT_PCTL, SPC5_PIT_STOP_PCTL);
#define SPC5_HAS_PIT_CH0                    TRUE
#define SPC5_HAS_PIT_CH1                    TRUE
#define SPC5_HAS_PIT_CH2                    TRUE
#define SPC5_HAS_PIT_CH3                    TRUE
#define SPC5_HAS_PIT_CH4                    FALSE
#define SPC5_HAS_PIT_CH5                    FALSE
#define SPC5_HAS_PIT_CH6                    FALSE
#define SPC5_HAS_PIT_CH7                    FALSE
#define SPC_PIT_CH0_HANDLER                 vector59
#define SPC_PIT_CH1_HANDLER                 vector60
#define SPC_PIT_CH2_HANDLER                 vector61
#define SPC_PIT_CH3_HANDLER                 vector127
#define SPC_PIT_CH0_INT_NUMBER              59
#define SPC_PIT_CH1_INT_NUMBER              60
#define SPC_PIT_CH2_INT_NUMBER              61
#define SPC_PIT_CH3_INT_NUMBER              127

/* STM Attributes */
#define SPC5_HAS_STM0                       TRUE
#define SPC5_HAS_STM1                       FALSE
#define SPC5_HAS_STM2                       FALSE
#define SPC5_STM0_BASE                      0xFFF3C000UL
#define SPC5_STM0_CHANNELS                  4
#define SPC5_HAS_STM0_CH0                   TRUE
#define SPC5_HAS_STM0_CH1                   TRUE
#define SPC5_HAS_STM0_CH2                   TRUE
#define SPC5_HAS_STM0_CH3                   TRUE
#define SPC5_STM0_CH1_CH3_SHARED_INT        FALSE
#define SPC5_STM0_CH0_HANDLER               vector30
#define SPC5_STM0_CH1_HANDLER               vector31
#define SPC5_STM0_CH2_HANDLER               vector32
#define SPC5_STM0_CH3_HANDLER               vector33
#define SPC5_STM0_CH0_INT_NUMBER            30
#define SPC5_STM0_CH1_INT_NUMBER            31
#define SPC5_STM0_CH2_INT_NUMBER            32
#define SPC5_STM0_CH3_INT_NUMBER            33

/* CRC attributes.*/
#define SPC5_HAS_CRC_0                       TRUE
#define SPC5_CRC_0_PTCL                      58
#define CRC_0                                CRC
#define CONTEXT                              CNTX
#define CRC_tag                              CRC_struct_tag

/* FCCU Attributes */
#define SPC5_HAS_FCCU                       TRUE
#define SPC5_FCCU_BASE                      0xFFE6C000UL
#define SPC5_FCCU_CF_CH_NUMBER              32U
#define SPC5_FCCU_NCF_CH_NUMBER             32U
#define SPC5_FCCU_ALARM_HANDLER             vector250
#define SPC5_FCCU_CONFIG_HANDLER            vector251
#define SPC5_FCCU_ALARM_INT_NUMBER          250
#define SPC5_FCCU_CONFIG_INT_NUMBER         251

/** @} */

#endif /* _SPC56EL_REGISTRY_H_ */

/** @} */
