/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : E100_LDC                                                    **
**  Filename  : Asw_DiagAdc.h                                               **
**  Version   : -.- (PCB : )                                                **
**  Date      : 2019.08.01                                                  **
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
Revised by  : Tran Duc Hung
Description : Original version.

*/

#ifndef ASW_DIAGADC_INCLUDED
#define ASW_DIAGADC_INCLUDED

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "../RTE/Rte_AswBswLink.h"
#include "saradc_BSW.h"

/****************************************************************************/
/**                                                                        **/
/**                      DEFINITIONS AND MACROS                            **/
/**                                                                        **/
/****************************************************************************/
#define DTC_U1102									( ( uint32_t )( 0x00000200 ) )	/* CAN timeout */
#define DTC_U1101									( ( uint32_t )( 0x00000100 ) )  /* CAN bus off */
#define DTC_P1109									( ( uint32_t )( 0x00000080 ) )  /* Fail control*/
#define DTC_P1108									( ( uint32_t )( 0x00000040 ) )	/* Temp is over 115C */
#define DTC_P1107									( ( uint32_t )( 0x00000020 ) )	/* Bplus != Vout > 8V */
#define DTC_P1106					        ( ( uint32_t )( 0x00000010 ) )	/* Temp sensor is broken */
#define DTC_P1105									( ( uint32_t )( 0x00000008 ) )	/* Short circuit Iout sensor */
#define DTC_P1104									( ( uint32_t )( 0x00000004 ) )	/* Short circuit Iin sensor */
#define DTC_P1103									( ( uint32_t )( 0x00000002 ) )	/* Iin > 10A */
#define DTC_P1102								  ( ( uint32_t )( 0x00000001 ) )	/* Vout > 22V */

#define setReg32Bits( RegName, SetMask )		( ( RegName ) |= ( uint32_t )( SetMask ) )
#define clrReg32Bits( RegName, ClrMask )    ( ( RegName ) &= ( uint32_t )( ~( ClrMask ) & 0xFFFFFFFFU ) )
#define clrSetReg32Bits( RegName, ClrMask, SetMask )    ( ( RegName ) = ( ( RegName ) & ( ( uint32_t )( ~( ClrMask ) & 0xFFFFFFFFU ) ) ) | ( uint32_t )( SetMask ) )

#define OUTPUT_V_ERR_CNT						( 30000U ) /* 30s*/
#define TEMPER_ERR_CNT							( 5000U )	 /* 5s */
#define TEMP_SENSOR_SHORT_ERR_CNT		( 500U )	/* 500ms */
#define SENSOR_ERR_CNT							( 500U )  /* 500ms */
#define CAN_BUS_OFF_ERR_CNT	    		( 2U ) /* 2 time */
#define CAN_TIME_OUT_ERR_CNT    		( 1000U ) /* 1s */
#define OUTPUT_FAIL_ERR_ERR_CNT			( 10000U ) /* 10s */
#define TEMP_SENSOR_OPEN_ERR_CNT 		( 10000U ) /* 10s */

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

# ifndef ASW_DIAGADC_C_SRC
# endif

extern uint32_t u32g_LDC_ERR_Sts;
extern uint8_t u8g_Restart_Request;
extern uint16_t u16g_p1109Err_Cnt;
extern uint8_t u8g_P1109_FaultReadyCnt;
extern uint8_t u8g_checkTemp_Flag;
extern uint8_t u8g_p1109_FaultTime;
extern uint8_t u8g_p1107_FaultTime;

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
extern void DiagAdc_DiagAdcValues( LdcDiagnosisType* pDiagFlags, LDC_MODE_DEF ldcModeStat, LDC_RUN_DEF ldcRunStat, const AdcRealValuesType* adcValues );

#endif

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
