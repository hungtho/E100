/*
                             *******************
******************************* C HEADER FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : E100_LDC                                                    **
**  Filename  : Rte_Typedef.h                                               **
**  Version   : -.- (PCB : )                                                **
**  Date      : 2019.09.05                                                  **
**                                                                          **
******************************************************************************
**                                                                          **
**  (c) 2019 YOUNG HWA TECH Co., Ltd. All Rights Reserved                   **
**                                                                          **
**                       YOUNG HWA TECH Co., Ltd.                           **
******************************************************************************

VERSION HISTORY:
----------------

Version     : -.-
Date        : ----.--.--
Revised by  : Im, Hong Kyun
Description : Original version.

*/

#ifndef RTE_TYPEDEF_INCLUDED
#define RTE_TYPEDEF_INCLUDED

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "../BSW/saradc_BSW.h"
#include "spc570_hal_pwm.h"
#include "MatLib.h"

/****************************************************************************/
/**                                                                        **/
/**                      DEFINITIONS AND MACROS                            **/
/**                                                                        **/
/****************************************************************************/
#define yTRUE 						( 1U )
#define yFALSE 						( 0U )

#define yDTC_ERR 					( 1U )
#define yDTC_OK 					( 0U )

#define MaxOutputCurrent	( 2492.0 )
#define MaxOutputVoltage	( 214.1 )

/* Current testing */
#define TEST_CUR_REF			( 1200.0 )		/* need to change - Limit current : 120A = (120 * 10.0) */
#define TEST_IoRef        ( TEST_CUR_REF / MaxOutputCurrent )  	/* Base output voltage is taken as 14V and reference is scaled it down to 12V*/

#define CUR_REF_160				( 1600.0 )		/* Limit current : 160 A*/
#define CUR_REF_128				( 1280.0 )	/* Limit current : 160 A*/
#define IoRef_128         ( CUR_REF_128 / MaxOutputCurrent )  	/* Base output voltage is taken as 14V and reference is scaled it down to 12V*/
#define IoRef_160         (CUR_REF_160 / MaxOutputCurrent )  	/* Base output voltage is taken as 14V and reference is scaled it down to 12V*/

/* DUTY  limit */
#define TEST_LMT_CURR ( 0 )
#if ( !TEST_LMT_CURR )
#define SATURATION_CUR_128   ( _IQ17(IoRef_128) ) /* Saturated current value : 128A */
#define SATURATION_CUR_160   ( _IQ17(IoRef_160) ) /* Saturated current value : 160A */
#else
#define SATURATION_CUR_128   _IQ17(TEST_IoRef) /* Saturated current value : 128A */
#define SATURATION_CUR_160   _IQ17(TEST_IoRef) /* Saturated current value : 160A */
#endif

#define MaxPhase		( ETIMER_3_PERIOD / 2U )

#define EEP_INDEX_WRITE_STATUS 		( 0U )

/****************************************************************************/
/**                                                                        **/
/**                      TYPEDEFS AND STRUCTURES                           **/
/**                                                                        **/
/****************************************************************************/

typedef struct LdcDiagnosis
{

	uint8_t Diag_LdcTemp;			/* Temperature (-40 ~ 105)*/
	uint8_t Diag_LdcTempSub;			/* Temperature (-40 ~ 105)*/
	uint8_t Diag_HV_V;				/* HV V - 입력전압	(250V ~ 420V) */
	uint8_t Diag_HV_I;				/* HV I - 입력전류 (0A ~ 20A) */
	uint8_t Diag_LV_V;				/* LV V(Battery)- 출력전압 (6V ~ 16V) */
	uint8_t Diag_LV_I;				/* LV I(Battery)- 출력전류 (0A ~ 128A) */
	uint8_t Diag_LV_PeakCurr;		/* LV Peak Current (ON/OFF) */
	uint8_t Diag_CanBusOffSts;	/* CAN bus State */
	uint8_t Diag_dtc_P1107;
	uint8_t Diag_dtc_P1109;
}LdcDiagnosisType;

typedef struct ADC_results_real_t
{
	uint16_t realInputCurrent;
	uint16_t realInputVoltage;
	uint16_t realOutputCurrent;
	uint16_t realOutputVoltage;
	int16_t realTemperature;
	int16_t realTemperatureSub;
	uint16_t realSupplyVoltage;
	uint16_t realBatteryVoltage;
	uint16_t realKeyInVoltage;
}AdcRealValuesType;

enum MCU_MODE_STATE
{
	MCU_RESET = 0,
	MCU_INITIALIZE,
	MCU_READY
};

typedef enum LDC_MODE_STATE
{
	LDC_MODE_READY = 0,
	LDC_MODE_NORMAL,
	LDC_MODE_WARNING,
	LDC_MODE_FAULT,
	LDC_MODE_DERATING,
	LDC_MODE_FAILURE
}LDC_MODE_DEF;

typedef enum LDC_RUN_MODE
{
	LDC_RUN_STANDBY = 0,
	LDC_RUN_POWERON
}LDC_RUN_DEF;

typedef enum DERATING_STATUS
{
	DERARING_NOT_USE = 0U,
	DERARING_TEMP_LV01,	/* 110 초과 */
	DERARING_TEMP_LV02,	/* 115 초과 */
	DERARING_TEMP_LV03,	/* 118 초과 */
	DERARING_VOLT, /* 230~250, 420~430 구간에서 출력 전압을 12V로 De-rating */
	DERARING_CURR_LV01, /* 128A 초과 시 출력 전류 제한 160 1초 유지 */
	DERARING_CURR_LV02 /* DERARING_CURR_LV01 1초 유지 후 전류 제한 값 128A 설정 */
}LDC_DERATING_STAT;

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/

# ifndef RTE_TYPEDEF_C_SRC
# endif

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/

#endif

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
