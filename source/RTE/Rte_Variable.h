/*
 * Rte_Variable.h
 *
 *  Created on: 2019. 1. 23.
 *      Author: owner
 */

#ifndef RTE_VARIABLE_H_
#define RTE_VARIABLE_H_

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "Rte_LdcConfig.h"

/****************************************************************************/
/**                                                                        **/
/**                      DEFINITIONS AND MACROS                            **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                      TYPEDEFS AND STRUCTURES                           **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/

# ifndef RTE_VARIABLE_C_SRC
# endif

extern uint8_t rteCanBusOffCnt;
extern uint8_t rteCanRxPathDisable;
extern uint16_t rteVcuCmdLdcTargetVolt; /* Low Votage(12V) Output LDC Target voltage */
extern uint16_t u16g_StartPwmOn_cnt;
extern uint16_t u16g_StartSrOn_cnt;
extern AdcRealValuesType rteAdcRealResult;

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
extern uint8_t RTE_GET_CAN_BUS_OFF_STATE(void);
extern void RTE_SET_CAN_BUS_OFF_STATE(uint8_t val);
extern uint16_t RTE_GET_PHASE_SHIFT_VAL(void);
extern void RTE_SET_PHASE_SHIFT_VAL(uint16_t val);
extern uint32_t RTE_GET_POWER_LATCH_COUNTER_VAL(void);
extern void RTE_ADD_POWER_LATCH_COUNTER_VAL(void);
extern void RTE_CLEAR_POWER_LATCH_COUNTER_VAL(void);
extern uint8_t RTE_SOFT_STOP( uint16_t u16_rteshift );

extern LDC_MODE_DEF RTE_GET_LDC_MODE_STATUS(void);
extern void RTE_SET_LDC_MODE_STATUS(LDC_MODE_DEF val);

extern LDC_RUN_DEF RTE_GET_LDC_RUN_STATUS(void);
extern void RTE_SET_LDC_RUN_STATUS(LDC_RUN_DEF val);

extern LdcDiagnosisType* RTE_GET_LDC_DIAGNOSIS_STATUS(void);
extern void RTE_SET_LDC_DIAGNOSIS_STATUS(const LdcDiagnosisType* val);

extern uint32_t RTE_GET_DERATING_TARGET_VOLT(uint16_t deratingVolt);
/* CAN */
extern uint8_t RTE_GET_IGN3_STS( void );
extern uint8_t RTE_GET_CMD_ENABLE_LDC(void);
extern uint32_t RTE_GET_CMD_TARGET_VOLT(void);

/* ADC */
extern ADC_results_t* RTE_GET_ADC_RAW_RESULT(void);
extern void RTE_SET_ADC_RAW_RESULT(const ADC_results_t* val);
extern AdcRealValuesType* RTE_GET_ADC_REAL_RESULT(void);
extern void RTE_SET_ADC_REAL_RESULT(const AdcRealValuesType* val);

extern uint16_t RTE_GET_ADC_RAW_VOUT(void);
extern uint16_t RTE_GET_ADC_RAW_IOUT(void);
extern LDC_DERATING_STAT RTE_GET_DERATING_STAT(void);
extern void RTE_SET_DERATING_STAT(LDC_DERATING_STAT val);

/* CAN communication */
extern void RTE_CAN_IL_TASK ( void );
extern void RTE_CAN_Diag_TASK ( void );
extern void RTE_UPDATE_CAN_RX(void);
extern void RTE_UPDATE_CAN_TX(void);
extern void RTE_BattLvl_Check ( void );

extern void CRC8_Init ( void );

#endif

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
