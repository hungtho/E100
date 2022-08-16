/****************************************************************************
*
* Copyright © 2015-2019 STMicroelectronics - All Rights Reserved
*
* License terms: STMicroelectronics Proprietary in accordance with licensing
* terms SLA0089 at www.st.com.
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* EVALUATION ONLY – NOT FOR USE IN PRODUCTION
*****************************************************************************/

/**
 * @file    spc570s_registry.h
 * @brief   SPC570Sxx capabilities registry.
 *
 * @addtogroup PLATFORM
 * @{
 */

#ifndef _SPC570S_REGISTRY_H_
#define _SPC570S_REGISTRY_H_

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Platform capabilities.                                                    */
/*===========================================================================*/

/**
 * @name    SPC570Sxx capabilities
 * @{
 */
/* eDMA attributes.*/
#define SPC5_HAS_EDMA                       TRUE
#define SPC5_HAS_EDMA0                      FALSE
#define SPC5_HAS_EDMA1                      TRUE
#define SPC5_EDMA_DMA1_BASE                 0xFC0A0000UL
#define SPC5_EDMA_NCHANNELS                 16U
#define SPC5_EDMA_COMBO_CH_ERR_HANDLER      vector52
#define SPC5_EDMA_CH0_HANDLER               vector53
#define SPC5_EDMA_CH1_HANDLER               vector54
#define SPC5_EDMA_CH2_HANDLER               vector55
#define SPC5_EDMA_CH3_HANDLER               vector56
#define SPC5_EDMA_CH4_HANDLER               vector57
#define SPC5_EDMA_CH5_HANDLER               vector58
#define SPC5_EDMA_CH6_HANDLER               vector59
#define SPC5_EDMA_CH7_HANDLER               vector60
#define SPC5_EDMA_CH8_HANDLER               vector61
#define SPC5_EDMA_CH9_HANDLER               vector62
#define SPC5_EDMA_CH10_HANDLER              vector63
#define SPC5_EDMA_CH11_HANDLER              vector64
#define SPC5_EDMA_CH12_HANDLER              vector65
#define SPC5_EDMA_CH13_HANDLER              vector66
#define SPC5_EDMA_CH14_HANDLER              vector67
#define SPC5_EDMA_CH15_HANDLER              vector68
#define SPC5_EDMA_COMBO_CH_ERR_NUMBER       52U
#define SPC5_EDMA_CH0_NUMBER                53U
#define SPC5_EDMA_HAS_MUX                   TRUE
#define SPC5_EDMA_NUM_OF_MUX                1U
#define SPC5_EDMA_MUX0_BASE                 0xFFF6C000UL
#define SPC5_EDMA_MUX0_CH_NUM               16U
#define SPC5_EDMA_MUX0_PCTL                 36

/* DSPI attributes.*/
#define SPC5_HAS_DSPI0                      TRUE
#define SPC5_DSPI0_BASE                     0xFFE70000UL
#define SPC5_HAS_DSPI1                      TRUE
#define SPC5_DSPI1_BASE                     0xFFE74000UL
#define SPC5_HAS_DSPI2                      TRUE
#define SPC5_DSPI2_BASE                     0xFBE70000UL
#define SPC5_DSPI_FIFO_DEPTH                4U
#define SPC5_DSPI0_PCTL                     99
#define SPC5_DSPI1_PCTL                     98
#define SPC5_DSPI2_PCTL                     227
#define SPC5_DSPI0_EOQF_HANDLER             vector260
#define SPC5_DSPI0_EOQF_NUMBER              260
#define SPC5_DSPI0_TFFF_HANDLER             vector261
#define SPC5_DSPI0_TFFF_NUMBER              261
#define SPC5_DSPI0_RFDF_HANDLER             vector263
#define SPC5_DSPI0_RFDF_NUMBER              263
#define SPC5_DSPI1_EOQF_HANDLER             vector269
#define SPC5_DSPI1_EOQF_NUMBER              269
#define SPC5_DSPI1_TFFF_HANDLER             vector270
#define SPC5_DSPI1_TFFF_NUMBER              270
#define SPC5_DSPI1_RFDF_HANDLER             vector272
#define SPC5_DSPI1_RFDF_NUMBER              272
#define SPC5_DSPI2_EOQF_HANDLER             vector278
#define SPC5_DSPI2_EOQF_NUMBER              278
#define SPC5_DSPI2_TFFF_HANDLER             vector279
#define SPC5_DSPI2_TFFF_NUMBER              279
#define SPC5_DSPI2_RFDF_HANDLER             vector281
#define SPC5_DSPI2_RFDF_NUMBER              281
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
#define SPC5_HAS_DSPI3                      FALSE
#define SPC5_HAS_DSPI4                      FALSE
#define SPC5_HAS_DSPI5                      FALSE
#define SPC5_HAS_DSPI6                      FALSE
#define SPC5_HAS_DSPI7                      FALSE
#define SPC5_HAS_DSPI8                      FALSE
#define SPC5_HAS_DSPI9                      FALSE

/* LINFlex attributes.*/
#define SPC5_HAS_LINFLEX0                   TRUE
#define SPC5_LINFLEX0_BASE                  0xFFE8C000UL
#define SPC5_LINFLEX0L_BASE                 0xFFE8C000UL
#define SPC5_LINFLEX0H_BASE                 0xFFE8C08CUL
#define SPC5_LINFLEX0_PCTL                  92
#define SPC5_LINFLEX0_RXI_HANDLER           vector376
#define SPC5_LINFLEX0_TXI_HANDLER           vector377
#define SPC5_LINFLEX0_ERR_HANDLER           vector378
#define SPC5_LINFLEX0_RXI_NUMBER            376
#define SPC5_LINFLEX0_TXI_NUMBER            377
#define SPC5_LINFLEX0_ERR_NUMBER            378
#define SPC5_LINFLEX0_DMA_SUPPORTED         TRUE
#define SPC5_LINFLEX0_RX_DMA_MUX0_DEV_ID    9
#define SPC5_LINFLEX0_TX_DMA_MUX0_DEV_ID    10
#define SPC5_LINFLEX0_CLK                   SPC5_LIN_CLK

#define SPC5_HAS_LINFLEX1                   TRUE
#define SPC5_LINFLEX1_BASE                  0xFBE8C000UL
#define SPC5_LINFLEX1L_BASE                 0xFBE8C000UL
#define SPC5_LINFLEX1H_BASE                 0xFBE8C04CUL
#define SPC5_LINFLEX1_PCTL                  220
#define SPC5_LINFLEX1_RXI_HANDLER           vector384
#define SPC5_LINFLEX1_TXI_HANDLER           vector385
#define SPC5_LINFLEX1_ERR_HANDLER           vector386
#define SPC5_LINFLEX1_RXI_NUMBER            384
#define SPC5_LINFLEX1_TXI_NUMBER            385
#define SPC5_LINFLEX1_ERR_NUMBER            386
#define SPC5_LINFLEX1_DMA_SUPPORTED         TRUE
#define SPC5_LINFLEX1_RX_DMA_MUX0_DEV_ID    11
#define SPC5_LINFLEX1_TX_DMA_MUX0_DEV_ID    12
#define SPC5_LINFLEX1_CLK                   SPC5_LIN_CLK

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
/* No SPC5_SIUL2_PCTL to setup */

/* EIRQ */
#define SPC5_SIUL_EIRQ_HAS_0_HANDLER        TRUE
#define SPC5_SIUL_EIRQ_HAS_1_HANDLER        TRUE
#define SPC5_SIUL_EIRQ_HAS_2_HANDLER        TRUE
#define SPC5_SIUL_EIRQ_HAS_3_5_HANDLER      TRUE
#define SPC5_SIUL_EIRQ_0_HANDLER            vector243
#define SPC5_SIUL_EIRQ_1_HANDLER            vector244
#define SPC5_SIUL_EIRQ_2_HANDLER            vector245
#define SPC5_SIUL_EIRQ_3_5_HANDLER          vector246
#define SPC5_SIUL_EIRQ_0_INT_NUMBER         243
#define SPC5_SIUL_EIRQ_1_INT_NUMBER         244
#define SPC5_SIUL_EIRQ_2_INT_NUMBER         245
#define SPC5_SIUL_EIRQ_3_5_INT_NUMBER       246

/* eTimer attributes.*/
#define SPC5_HAS_ETIMER0                    TRUE
#define SPC5_ETIMER0_BASE                   0xFFC20000UL
#define SPC5_ETIMER0_PCTL                   129
#define SPC5_ETIMER0_STS0_HANDLER           vector706
#define SPC5_ETIMER0_STS1_HANDLER           vector707
#define SPC5_ETIMER0_STS2_HANDLER           vector708
#define SPC5_ETIMER0_STS3_HANDLER           vector709
#define SPC5_ETIMER0_STS4_HANDLER           vector710
#define SPC5_ETIMER0_STS5_HANDLER           vector711
#define SPC5_ETIMER0_STS0_NUMBER            706
#define SPC5_ETIMER0_STS1_NUMBER            707
#define SPC5_ETIMER0_STS2_NUMBER            708
#define SPC5_ETIMER0_STS3_NUMBER            709
#define SPC5_ETIMER0_STS4_NUMBER            710
#define SPC5_ETIMER0_STS5_NUMBER            711
#define SPC5_ETIMER0_CLK                    SPC5_ETIMER_CLK

#define SPC5_HAS_ETIMER1                    TRUE
#define SPC5_ETIMER1_BASE                   0xFFC24000UL
#define SPC5_ETIMER1_PCTL                   128
#define SPC5_ETIMER1_STS0_HANDLER           vector717
#define SPC5_ETIMER1_STS1_HANDLER           vector718
#define SPC5_ETIMER1_STS2_HANDLER           vector719
#define SPC5_ETIMER1_STS3_HANDLER           vector720
#define SPC5_ETIMER1_STS4_HANDLER           vector721
#define SPC5_ETIMER1_STS5_HANDLER           vector722
#define SPC5_ETIMER1_STS0_NUMBER            717
#define SPC5_ETIMER1_STS1_NUMBER            718
#define SPC5_ETIMER1_STS2_NUMBER            719
#define SPC5_ETIMER1_STS3_NUMBER            720
#define SPC5_ETIMER1_STS4_NUMBER            721
#define SPC5_ETIMER1_STS5_NUMBER            722
#define SPC5_ETIMER1_CLK                    SPC5_ETIMER_CLK

#define SPC5_HAS_ETIMER2                    TRUE
#define SPC5_ETIMER2_BASE                   0xFBC20000UL
#define SPC5_ETIMER2_PCTL                   131
#define SPC5_ETIMER2_STS0_HANDLER           vector728
#define SPC5_ETIMER2_STS1_HANDLER           vector729
#define SPC5_ETIMER2_STS2_HANDLER           vector730
#define SPC5_ETIMER2_STS3_HANDLER           vector731
#define SPC5_ETIMER2_STS4_HANDLER           vector732
#define SPC5_ETIMER2_STS5_HANDLER           vector733
#define SPC5_ETIMER2_STS0_NUMBER            728
#define SPC5_ETIMER2_STS1_NUMBER            729
#define SPC5_ETIMER2_STS2_NUMBER            730
#define SPC5_ETIMER2_STS3_NUMBER            731
#define SPC5_ETIMER2_STS4_NUMBER            732
#define SPC5_ETIMER2_STS5_NUMBER            733
#define SPC5_ETIMER2_CLK                    SPC5_ETIMER_CLK

#define SPC5_HAS_ETIMER3                    TRUE
#define SPC5_ETIMER3_BASE                   0xFBC24000UL
#define SPC5_ETIMER3_PCTL                   130
#define SPC5_ETIMER3_STS0_HANDLER           vector739
#define SPC5_ETIMER3_STS1_HANDLER           vector740
#define SPC5_ETIMER3_STS2_HANDLER           vector741
#define SPC5_ETIMER3_STS3_HANDLER           vector742
#define SPC5_ETIMER3_STS4_HANDLER           vector743
#define SPC5_ETIMER3_STS5_HANDLER           vector744
#define SPC5_ETIMER3_STS0_NUMBER            739
#define SPC5_ETIMER3_STS1_NUMBER            740
#define SPC5_ETIMER3_STS2_NUMBER            741
#define SPC5_ETIMER3_STS3_NUMBER            742
#define SPC5_ETIMER3_STS4_NUMBER            743
#define SPC5_ETIMER3_STS5_NUMBER            744
#define SPC5_ETIMER3_CLK                    SPC5_ETIMER_CLK

/* FlexCAN attributes.*/
#define SPC5_HAS_FLEXCAN0                   TRUE
#define SPC5_FLEXCAN0_BASE                  0xFFEC0000UL
#define SPC5_FLEXCAN0_PCTL                  79
#define SPC5_FLEXCAN0_MB                    32U
#define SPC5_FLEXCAN0_SHARED_IRQ            TRUE
#define SPC5_FLEXCAN0_ESR_ERR_INT_HANDLER   vector687
#define SPC5_FLEXCAN0_ESR_BOFF_HANDLER      vector688
#define SPC5_FLEXCAN0_BUF_00_03_HANDLER     vector677
#define SPC5_FLEXCAN0_BUF_04_07_HANDLER     vector678
#define SPC5_FLEXCAN0_BUF_08_11_HANDLER     vector679
#define SPC5_FLEXCAN0_BUF_12_15_HANDLER     vector680
#define SPC5_FLEXCAN0_BUF_16_31_HANDLER     vector681
#define SPC5_FLEXCAN0_ESR_ERR_INT_NUMBER    687
#define SPC5_FLEXCAN0_ESR_BOFF_NUMBER       688
#define SPC5_FLEXCAN0_BUF_00_03_NUMBER      677
#define SPC5_FLEXCAN0_BUF_04_07_NUMBER      678
#define SPC5_FLEXCAN0_BUF_08_11_NUMBER      679
#define SPC5_FLEXCAN0_BUF_12_15_NUMBER      680
#define SPC5_FLEXCAN0_BUF_16_31_NUMBER      681
#define SPC5_FLEXCAN0_ENABLE_CLOCK()                                        \
  SPCSetPeripheralClockMode(SPC5_FLEXCAN0_PCTL, SPC5_CAN_FLEXCAN0_START_PCTL)
#define SPC5_FLEXCAN0_DISABLE_CLOCK()                                       \
  SPCSetPeripheralClockMode(SPC5_FLEXCAN0_PCTL, SPC5_CAN_FLEXCAN0_STOP_PCTL)

#define SPC5_HAS_FLEXCAN1                   TRUE
#define SPC5_FLEXCAN1_BASE                  0xFBEC0000UL
#define SPC5_FLEXCAN1_PCTL                  207
#define SPC5_FLEXCAN1_MB                    32U
#define SPC5_FLEXCAN1_SHARED_IRQ            TRUE
#define SPC5_FLEXCAN1_ESR_ERR_INT_HANDLER   vector700
#define SPC5_FLEXCAN1_ESR_BOFF_HANDLER      vector701
#define SPC5_FLEXCAN1_BUF_00_03_HANDLER     vector690
#define SPC5_FLEXCAN1_BUF_04_07_HANDLER     vector691
#define SPC5_FLEXCAN1_BUF_08_11_HANDLER     vector692
#define SPC5_FLEXCAN1_BUF_12_15_HANDLER     vector693
#define SPC5_FLEXCAN1_BUF_16_31_HANDLER     vector694
#define SPC5_FLEXCAN1_ESR_ERR_INT_NUMBER    700
#define SPC5_FLEXCAN1_ESR_BOFF_NUMBER       701
#define SPC5_FLEXCAN1_BUF_00_03_NUMBER      690
#define SPC5_FLEXCAN1_BUF_04_07_NUMBER      691
#define SPC5_FLEXCAN1_BUF_08_11_NUMBER      692
#define SPC5_FLEXCAN1_BUF_12_15_NUMBER      693
#define SPC5_FLEXCAN1_BUF_16_31_NUMBER      694
#define SPC5_FLEXCAN1_ENABLE_CLOCK()                                        \
  SPCSetPeripheralClockMode(SPC5_FLEXCAN1_PCTL, SPC5_CAN_FLEXCAN1_START_PCTL)
#define SPC5_FLEXCAN1_DISABLE_CLOCK()                                       \
  SPCSetPeripheralClockMode(SPC5_FLEXCAN1_PCTL, SPC5_CAN_FLEXCAN1_STOP_PCTL)
#define SPC5_HAS_FLEXCAN2                   FALSE
#define SPC5_HAS_FLEXCAN3                   FALSE
#define SPC5_HAS_FLEXCAN4                   FALSE
#define SPC5_HAS_FLEXCAN5                   FALSE

/* PIT Attributes */
#define SPC5_HAS_PIT                        TRUE
#define SPC5_PIT_BASE                       0xFFF84000UL
#define SPC5_PIT_CHANNELS                   4
#define SPC5_PIT_PCTL                       30
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
#define SPC_PIT_CH0_HANDLER                 vector226
#define SPC_PIT_CH1_HANDLER                 vector227
#define SPC_PIT_CH2_HANDLER                 vector228
#define SPC_PIT_CH3_HANDLER                 vector229
#define SPC_PIT_CH0_INT_NUMBER              226
#define SPC_PIT_CH1_INT_NUMBER              227
#define SPC_PIT_CH2_INT_NUMBER              228
#define SPC_PIT_CH3_INT_NUMBER              229

/* STM Attributes */
#define SPC5_HAS_STM0                       TRUE
#define SPC5_HAS_STM1                       FALSE
#define SPC5_HAS_STM2                       FALSE
#define SPC5_STM0_BASE                      0xFC068000UL
#define SPC5_STM0_CHANNELS                  4
#define SPC5_HAS_STM0_CH0                   TRUE
#define SPC5_HAS_STM0_CH1                   TRUE
#define SPC5_HAS_STM0_CH2                   TRUE
#define SPC5_HAS_STM0_CH3                   TRUE
#define SPC5_STM0_CH1_CH3_SHARED_INT        FALSE
#define SPC5_STM0_CH0_HANDLER               vector44
#define SPC5_STM0_CH1_HANDLER               vector45
#define SPC5_STM0_CH2_HANDLER               vector46
#define SPC5_STM0_CH3_HANDLER               vector47
#define SPC5_STM0_CH0_INT_NUMBER            44
#define SPC5_STM0_CH1_INT_NUMBER            45
#define SPC5_STM0_CH2_INT_NUMBER            46
#define SPC5_STM0_CH3_INT_NUMBER            47

/* SARADC Attributes */
#define SPC5_HAS_SARADC12_0                 TRUE
#define SPC5_SARADC12_0_PCTL                127
#define SPC5_SARADC12_0_HANDLER             vector528
#define SPC5_SARADC12_0_INT_NUMBER          528

#define SPC5_HAS_SARADC12_1                 FALSE
#define SPC5_HAS_SARADC12_2                 FALSE
#define SPC5_HAS_SARADC12_3                 FALSE
#define SPC5_HAS_SARADC12_4                 FALSE
#define SPC5_HAS_SARADC12_5                 FALSE
#define SPC5_HAS_SARADC12_6                 FALSE

#define SPC5_HAS_SARADC12_SV                TRUE
#define SPC5_SARADC12_SV_PCTL               112
#define SPC5_SARADC12_SV_HANDLER            vector543
#define SPC5_SARADC12_SV_INT_NUMBER         543

#define SPC5_HAS_SARADC12_SV_1              FALSE
#define SPC5_HAS_SARADC10_0                 FALSE
#define SPC5_HAS_SARADC10_1                 FALSE
#define SPC5_HAS_SARADC10_STANDBY           FALSE

/* SWT Attributes */
#define SPC5_HAS_SWT0                       FALSE
#define SPC5_HAS_SWT1                       FALSE
#define SPC5_HAS_SWT2                       FALSE
#define SPC5_HAS_SWT3                       FALSE

/* FCCU attributes.*/
#define SPC5_HAS_FCCU                       TRUE
#define SPC5_FCCU_BASE                      0xFBF58000UL
#define SPC5_FCCU_CH_NUMBER                 128U
#define SPC5_FCCU_ALARM_HANDLER             vector488
#define SPC5_FCCU_CONFIG_HANDLER            vector489
#define SPC5_FCCU_ALARM_INT_NUMBER          488
#define SPC5_FCCU_CONFIG_INT_NUMBER         489
#define SPC5_FCCU_HAS_ERR_INPUT_PIN         FALSE
#define SPC5_FCCU_RF_E_REG_RESET_VAL        {0x00001040UL, 0x00000000UL, 0x00000000UL, 0x00000000UL}
#define SPC5_FCCU_MAX_DELTA_T_US            10000UL

#define MC_RGM_FCCU_RST                     MC_RGM.PRST5.B.FCCU_RST
/** @} */

#endif /* _SPC570S_REGISTRY_H_ */

/** @} */
