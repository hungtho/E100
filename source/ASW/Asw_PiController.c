/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : E100_LDC                                                    **
**  Filename  : Asw_PiController.c                                          **
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

#define ASW_PICONTROLLER_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "Asw_PiController.h"

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
static uint16_t PiCtrl_Voltage_PI_Controller( int32_t IRef, int32_t VRef, int32_t VoutAdc, int32_t IoutAdc );
static uint16_t PiCtrl_Current_PI_Controller( int32_t IRef, int32_t AdcIout );

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/
uint8_t u8g_softstart_end = 0U;

/****************************************************************************/
/**                                                                        **/
/**                      GLOBAL VARIABLES                                  **/
/**                                                                        **/
/****************************************************************************/
static uint32_t VoReferenceQ15 = 0U;
static int32_t Verror = 0U;
static int32_t Ierror= 0U;

static int32_t preVerror = 0U;
static int32_t preVerror1 = 0U;
static int32_t VoltageIntegralOutput = 0U;
static int32_t VoltagePropOutput = 0U;
static int32_t VoltageDerOutput = 0U;
static int32_t VoltagePIOutput = 0U;
static int32_t preVoltagePIOutput = 0U;
static int32_t VoltagePI_FinalOutput = 0U;

static int32_t preIerror = 0U;
static int32_t preIerror1 = 0U;
static int32_t CurrentPropOutput = 0U;
static int32_t CurrentIntegralOutput = 0U;
static int32_t CurrentDerOutput = 0U;
static int32_t CurrentPIOutput = 0U;
static int32_t preCurrentPIOutput = 0U;
static int32_t CurrentPIOutput_Final = 0U;

static const uint32_t VoREF1 = _IQ17( 30.0 / MaxOutputVoltage );	/* First value reference of output voltage */

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
void PiCtrl_PIController_Init(void)
{
	VoReferenceQ15 = VoREF1;
	Verror = 0U;
	Ierror= 0U;

	preVerror = 0U;
	preVerror1 = 0U;
	VoltagePropOutput = 0U;
	VoltageIntegralOutput = 0U;
	VoltageDerOutput = 0U;
	VoltagePIOutput = 0U;
	preVoltagePIOutput = 0U;
	VoltagePI_FinalOutput = 0U;

	CurrentPropOutput = 0U;
	CurrentIntegralOutput = 0U;
	CurrentDerOutput = 0U;
	preIerror = 0U;
	CurrentPIOutput = 0U;
	preIerror1 = 0U;
	preCurrentPIOutput = 0U;
	CurrentPIOutput_Final = 0U;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
uint16_t PiCtrl_DigitalCompensator( uint32_t VReferenceIQ, uint32_t IReferenceIQ )
{
	uint16_t pwmShiftB = 0;
	uint32_t AdcVout_Q15 = ( ( uint32_t )RTE_GET_ADC_RAW_VOUT() << 5U ); /* Transform Q12 to Q17 */
	uint32_t AdcIout_Q15 = ( ( uint32_t )RTE_GET_ADC_RAW_IOUT() << 5U ); /* Transform Q12 to Q17 */

	if( VoReferenceQ15 >= AdcVout_Q15 )  /* ramp-up */
	{
		if( VoReferenceQ15 > VReferenceIQ )
		{
			VoReferenceQ15 = VReferenceIQ;
			u8g_softstart_end = 1U;
		}
		else
		{
			VoReferenceQ15 += ( VReferenceIQ / 200U );
		}
	}
	else	/* ramp_down */
	{
		VoReferenceQ15 -= ( VReferenceIQ / 200U );

		if( VoReferenceQ15 < VReferenceIQ )
		{
			VoReferenceQ15 = VReferenceIQ;
		}
	}

	/* Step3: Implement controller */
	pwmShiftB = PiCtrl_Voltage_PI_Controller( ( int32_t )IReferenceIQ,
																						( int32_t )VoReferenceQ15,
																						( int32_t )AdcVout_Q15,
																						( int32_t )AdcIout_Q15 );

	return ( pwmShiftB );
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static uint16_t PiCtrl_Voltage_PI_Controller( int32_t IRef, int32_t VRef, int32_t VoutAdc, int32_t IoutAdc )
{
	uint16_t phaseshift = 0U;
	int32_t CurRef = 0U;

	/* Calculate error */
  Verror = VRef - VoutAdc;

  /* Determine new output */
	VoltagePropOutput = ( ( ( KpVoltage + KiVoltage ) * ( ( int32_t )Verror ) ) >> 13U );
	VoltageIntegralOutput = ( ( ( -KpVoltage + KiVoltage ) * ( ( int32_t )preVerror ) ) >> 13U );
	VoltageDerOutput = ( ( ( KdVoltage * Verror ) >> 13U ) - ( ( ( 2 * KdVoltage ) * preVerror ) >> 13U ) ) + ( ( ( KdVoltage * preVerror1 ) ) >> 13U );

	VoltagePIOutput  = ( int32_t )VoltagePropOutput  + ( int32_t )VoltageIntegralOutput + ( int32_t )VoltageDerOutput + ( int32_t )preVoltagePIOutput;

	/* Saturated output */
#if ( DERATING_IN_USE )
	if( VoltagePIOutput >  IRef )
	{
		VoltagePI_FinalOutput =  IRef;
	}
	else if( VoltagePIOutput < 0 )
	{
		VoltagePI_FinalOutput = 0U ;
	}
	else
	{
		VoltagePI_FinalOutput = VoltagePIOutput;
	}
#else
	if( VoltagePIOutput >  SATURATION_CUR_128 ) /* need to change SATURATION_CUR -> IRef (SATURATION_CUR * 80 / 100) */
	{
		VoltagePI_FinalOutput =  SATURATION_CUR_128;
	}
	else if( VoltagePIOutput < 0 )
	{
		VoltagePI_FinalOutput = 0 ;
	}
	else
	{
		VoltagePI_FinalOutput = VoltagePIOutput;
	}
#endif

	/* Store outputs */
	preVoltagePIOutput = VoltagePI_FinalOutput;

	/* Update error values */
	preVerror = Verror;
	preVerror1 = preVerror;

	CurRef = VoltagePI_FinalOutput;

	phaseshift = PiCtrl_Current_PI_Controller( CurRef, IoutAdc );

	return phaseshift;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static uint16_t PiCtrl_Current_PI_Controller( int32_t IRef, int32_t AdcIout ) /* IRef -> Limit currenct */
{
	uint16_t Shift = 0U;

  Ierror = IRef - AdcIout;

  /* Determine new output */
	CurrentPropOutput = ( ( ( KpCurrent + KiCurrent ) * ( ( int32_t )Ierror ) ) >> 12U);
	CurrentIntegralOutput = ( ( ( -KpCurrent + KiCurrent ) * ( ( int32_t )preIerror ) ) >> 12U );
	CurrentDerOutput = ( ( ( KdCurrent * Ierror ) >> 12U ) - ( ( 2 * KdCurrent * preIerror ) >> 12U ) ) + ( ( KdCurrent * preIerror1 ) >> 12U );

	CurrentPIOutput  = ( int32_t )CurrentPropOutput  + ( int32_t )CurrentIntegralOutput + ( int32_t )preCurrentPIOutput;

	/* Saturated output */
	if( CurrentPIOutput > duty_max )
	{
		CurrentPIOutput_Final = duty_max;
	}
	else if( CurrentPIOutput < 0 )
	{
		CurrentPIOutput_Final = 0U;
	}
	else
	{
	 CurrentPIOutput_Final= CurrentPIOutput;
	}

	Shift = ( ( uint32_t )CurrentPIOutput_Final * MaxPhase ) >> 17U;

	/* Store outputs */
	preCurrentPIOutput = CurrentPIOutput_Final;

	/* Update error values */
	preIerror = Ierror;
	preIerror1 = preIerror;

	return ( Shift );
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
