/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : E100_LDC                                                    **
**  Filename  : spc570_hal_adc.c                                            **
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

#ifndef SPC570_HAL_INCLUDED
#define SPC570_HAL_INCLUDED

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
#define HistorySize 	 ( 10U )
#define CHANNEL_NUMBER ( 10U )

/****************************************************************************/
/**                                                                        **/
/**                      TYPEDEFS AND STRUCTURES                           **/
/**                                                                        **/
/****************************************************************************/
/**
 * @brief Type of a structure representing an edma driver.
 */
typedef struct SARADCDriver sARADCDriver;

/**
 * @brief   Structure representing a SARADC driver.
 */
struct SARADCDriver
{
	/**
   * @brief Pointer to the SARADCx registers block.
   */
  volatile struct SARADC_tag *saradc;
};

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/

# ifdef SPC570_HAL_ADC_C_SRC
# endif

extern uint16_t Hist_Vout[ HistorySize ];
extern uint16_t Hist_Iout[ HistorySize ];
extern uint16_t Hist_Vin[ HistorySize ];
extern uint16_t Hist_Iin[ HistorySize ];
extern uint16_t Hist_Temp[ HistorySize ];
extern uint16_t Hist_SubTemp[ HistorySize ];
extern uint16_t Hist_12BAT[ HistorySize ];
extern uint16_t Hist_KeyIn[ HistorySize ];

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
extern void Hal_Adc_Init( void );
extern void HalAdcBuffer ( uint8_t chn, uint16_t buffer[] );
extern uint16_t HalMovingAvg ( uint16_t ptrArrNumbers[] );

#endif

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
