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

#define SPC570_HAL_ADC_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "spc570_hal_adc.h"

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
static void Hal_Adc0_Init(sARADCDriver *saradcp);
static uint16_t CpuInADC ( sARADCDriver *saradcp,  uint8_t u8_AdcCh );

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/
uint16_t Hist_Vout[ HistorySize ];
uint16_t Hist_Iout[ HistorySize ];
uint16_t Hist_Vin[ HistorySize ];
uint16_t Hist_Iin[ HistorySize ];
uint16_t Hist_Temp[ HistorySize ];
uint16_t Hist_SubTemp[ HistorySize ];
uint16_t Hist_12BAT[ HistorySize ];
uint16_t Hist_KeyIn[ HistorySize ];

/***********************************************************5*****************/
/**                                                                        **/
/**                      GLOBAL VARIABLES                                  **/
/**                                                                        **/
/****************************************************************************/
static volatile sARADCDriver SARADC0;

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Function  |            																						      */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void Hal_Adc_Init( void )
{
	SARADC0.saradc = &SAR_ADC_12BIT_0;
	Hal_Adc0_Init( &SARADC0 );
}

/*--------------------------------------------------------------------------*/
/* Function  |            																						      */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
uint16_t HalMovingAvg ( uint16_t ptrArrNumbers[] )
{
  uint8_t cnt;
  uint16_t AvgRet;
  uint16_t u16_Max = ptrArrNumbers[ 0U ];
  uint16_t u16_Min = ptrArrNumbers[ 0U ];
  uint32_t Sum = ptrArrNumbers[ 0U ];

  for( cnt = 1U; cnt < HistorySize; cnt++ )
  {
  	Sum += ptrArrNumbers[ cnt ];

  	if( ptrArrNumbers[ cnt ] > u16_Max ){ u16_Max = ptrArrNumbers[ cnt ]; }
  	if( ptrArrNumbers[ cnt ] < u16_Min ){ u16_Min = ptrArrNumbers[ cnt ]; }
  }

  Sum = Sum - ( ( uint32_t)u16_Max + u16_Min );

  AvgRet = ( uint16_t )( Sum / ( HistorySize - 2U ) );

  /*return the average*/
  return ( AvgRet );
}

/*--------------------------------------------------------------------------*/
/* Function  |            																					        */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void HalAdcBuffer ( uint8_t chn, uint16_t buffer[] )
{
	static uint16_t Index[ CHANNEL_NUMBER ];

	if( chn < CHANNEL_NUMBER )
	{
		buffer[ Index[ chn ] ] = CpuInADC ( &SARADC0, chn ); /* read AD conversion result from AN3 */

		Index[ chn ]++;
		if( Index[ chn ] >= HistorySize ){ Index[ chn ] = 0U; }
	}
}

/****************************************************************************/
/**                                                                        **/
/**                      LOCAL FUNCTIONS                                   **/
/**                                                                        **/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Function  |            																						      */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void Hal_Adc0_Init(sARADCDriver *saradcp)
{
	SPCSetPeripheralClockMode( SPC5_SARADC12_0_PCTL, SPC5_ME_PCTL_RUN( 2 ) | SPC5_ME_PCTL_LP( 2 ) );

	saradcp->saradc->MCR.B.MODE = 0U;	/* select CTU trigger mode */
	saradcp->saradc->PDEDR.R = 0;			/* Set power down exit delay if needed */

	/* Initialize conversion timing based on SARADC clock = 10MHz (80MHz/8) */
	/* set conversion timing for internal channel 0-15*/
	saradcp->saradc->CTR[0].B.CRES = 0U;	/* 12bit resolution */
	saradcp->saradc->CTR[0].B.PRECHG = 1;	/* 100ns > 83ns */
	saradcp->saradc->CTR[0].B.INPSAMP = 5; /* 500ns >= 0.5us */

	saradcp->saradc->MCR.B.PWDN = 0U;			/* Exit from power down mode */
	while(saradcp->saradc->MSR.B.ADCSTATUS != 0U){} /* wait idle state */

	saradcp->saradc->MCR.B.OWREN = 1U;		/* Enable overwrite */
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static uint16_t CpuInADC ( sARADCDriver *saradcp,  uint8_t u8_AdcCh )
{
	uint32_t u32_AdcChReg;

	u32_AdcChReg = ( uint32_t )0x00000001U << u8_AdcCh;

	saradcp->saradc->ICNCMR[ u8_AdcCh / 32U ].R = u32_AdcChReg;
	saradcp->saradc->MCR.B.NSTART = 0x1U;

	while( saradcp->saradc->ICDR[ u8_AdcCh ].B.VALID == 1U ){}

	return ( ( uint16_t)( saradcp->saradc->ICDR[ u8_AdcCh ].B.CDATA ) );
}

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
