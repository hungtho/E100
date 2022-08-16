/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : E100_LDC                                                    **
**  Filename  : saradc_BSW.c                                                **
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

#define SARADC_BSW_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "saradc_BSW.h"
#include "../RTE/Rte_AswBswLink.h"
#include "../HAL/spc570_hal_adc.h"

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
/**                      PROTOTYPES OF LOCAL FUNCTIONS                     **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                      GLOBAL VARIABLES                                  **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void BSW_SARADC_Init( void )
{
	Hal_Adc_Init();
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void BSW_UpdateADCValues( void )
{
	ADC_results_t averagedAdcResult = { 0, };

	HalAdcBuffer ( 0U, Hist_SubTemp );
	HalAdcBuffer ( 2U, Hist_KeyIn );
	HalAdcBuffer ( 3U, Hist_12BAT );
	HalAdcBuffer ( 5U, Hist_Vout );
	HalAdcBuffer ( 6U, Hist_Iout );
	HalAdcBuffer ( 7U, Hist_Vin );
	HalAdcBuffer ( 8U, Hist_Iin );
	HalAdcBuffer ( 9U, Hist_Temp );

	/* Calculate ADC average values */
	averagedAdcResult.KeyInVoltage = HalMovingAvg( Hist_KeyIn);
	averagedAdcResult.BatteryVoltage = HalMovingAvg( Hist_12BAT );
	averagedAdcResult.OutputVoltage = HalMovingAvg( Hist_Vout);
	averagedAdcResult.OutputCurrent = HalMovingAvg( Hist_Iout);
	averagedAdcResult.InputVoltage = HalMovingAvg( Hist_Vin );
	averagedAdcResult.InputCurrent = HalMovingAvg( Hist_Iin);
	averagedAdcResult.Temperature = HalMovingAvg( Hist_Temp );
	averagedAdcResult.TemperatureSub = HalMovingAvg( Hist_Temp );

	/* update values to RTE */
	RTE_SET_ADC_RAW_RESULT( &averagedAdcResult );
}

/****************************************************************************/
/**                                                                        **/
/**                      LOCAL FUNCTIONS                                   **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
