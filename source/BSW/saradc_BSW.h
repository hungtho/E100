/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : E100_LDC                                                    **
**  Filename  : saradc_BSW.h                                                **
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

#ifndef SARADC_BSW_INCLUDED
#define SARADC_BSW_INCLUDED

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "components.h"

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
typedef struct
{
	uint16_t InputCurrent;   /**< Raw ADC reading to Input Current measurement [0 to 4095] */
	uint16_t InputVoltage;   /**< Raw ADC reading to Input Voltage measurement [0 to 4095] */
	uint16_t OutputCurrent;   /**< Raw ADC reading to Output Current measurement [0 to 4095] */
	uint16_t OutputVoltage;    /**< Raw ADC reading to Output Voltage measurement [0 to 4095] */
	uint16_t Temperature;   /**< Raw ADC reading to temperature measurement [0 to 4095] */
	uint16_t TemperatureSub;   /**< Raw ADC reading to temperature measurement [0 to 4095] */
	uint16_t BatteryVoltage;   /**< Raw ADC reading to Battery Voltage measurement [0 to 4095] */
	uint16_t KeyInVoltage;    /**< Raw ADC reading to KeyIn Voltage measurement [0 to 4095] */
}ADC_results_t;

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/

# ifdef SARADC_BSW_C_SRC
# endif

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
extern void BSW_SARADC_Init( void );
extern void BSW_UpdateADCValues( void );

#endif

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
