/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : E100_LDC                                                    **
**  Filename  : spc570_hal_pwm.c                                            **
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

#define SPC570_HAL_PWM_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "platform.h"
#include "spc570_hal_pwm.h"
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
	uint16_t period;
	uint16_t duty;
	uint16_t deadTime0;		/* dead time for rising */
	uint16_t deadTime1;		/* dead time for falling */
	uint16_t phaseShift;
	uint16_t phaseShiftActive;
}tPwmProp;

/****************************************************************************/
/**                                                                        **/
/**                      PROTOTYPES OF LOCAL FUNCTIONS                     **/
/**                                                                        **/
/****************************************************************************/
static void HAL_PWM_ETIMER3_Config( eTIMERDriver *etimerp );

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/
eTIMERDriver ETIMER3;

/****************************************************************************/
/**                                                                        **/
/**                      STATIC VARIABLES                                  **/
/**                                                                        **/
/****************************************************************************/
static tPwmProp pwmCD;
static tPwmProp pwmEF;

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
void HAL_PSFB_Init( void )
{
	ETIMER3.etimer_tagp = &TIMER3;
	HAL_PWM_ETIMER3_Config( &ETIMER3 );
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void HAL_PWM_SR_SET_DUTY( eTIMERDriver *etimerp, uint16_t duty )
{
	uint16_t highsideN;

	pwmEF.duty = duty;

	highsideN = pwmEF.period - ( pwmEF.duty - ( pwmEF.deadTime0 / 2U ) );

	etimerp->etimer_tagp->CH[ 4 ].CMPLD1.R = highsideN ;
	etimerp->etimer_tagp->CH[ 5 ].CMPLD1.R = highsideN;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void HAL_PSFB_SHIFT( uint16_t shift )
{
	if( shift > PHASE_SHIFT_MAX_VAL ){ pwmCD.phaseShift = PHASE_SHIFT_MAX_VAL; }
	else{ pwmCD.phaseShift = shift; }
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void HAL_PSFB_OUTPUT_ENABLE( eTIMERDriver *etimerp )
{
	etimerp->etimer_tagp->CH[ 0 ].CTRL2.B.OEN = 1U; /* output enable */
	etimerp->etimer_tagp->CH[ 1 ].CTRL2.B.OEN = 1U; /* output enable */
	etimerp->etimer_tagp->CH[ 2 ].CTRL2.B.OEN = 1U; /* output enable */
	etimerp->etimer_tagp->CH[ 3 ].CTRL2.B.OEN = 1U; /* output enable */
	etimerp->etimer_tagp->ENBL.R = 0x3FU; /* Enable etimer channel 0,1,2,3,4,5 */
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void HAL_PSFB_OUTPUT_DISABLE ( eTIMERDriver *etimerp )
{
	etimerp->etimer_tagp->CH[ 0 ].CTRL2.B.OEN = 0U; /* output disable */
	etimerp->etimer_tagp->CH[ 1 ].CTRL2.B.OEN = 0U; /* output disable */
	etimerp->etimer_tagp->CH[ 2 ].CTRL2.B.OEN = 0U; /* output disable */
	etimerp->etimer_tagp->CH[ 3 ].CTRL2.B.OEN = 0U; /* output disable */
	etimerp->etimer_tagp->ENBL.R = 0x00U; /* Disable etimer channel 0,1,2,3,4,5 */
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void HAL_PSFB_SR_OUTPUT_ENABLE( eTIMERDriver *etimerp )
{
	etimerp->etimer_tagp->CH[ 4 ].CTRL2.B.OEN = 1U; /* output enable */
	etimerp->etimer_tagp->CH[ 5 ].CTRL2.B.OEN = 1U; /* output enable */
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void HAL_PSFB_SR_OUTPUT_DISABLE( eTIMERDriver *etimerp )
{
	etimerp->etimer_tagp->CH[ 4 ].CTRL2.B.OEN = 0U; /* output enable */
	etimerp->etimer_tagp->CH[ 5 ].CTRL2.B.OEN = 0U; /* output enable */
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
IRQ_HANDLER( SPC5_ETIMER3_TC3IR_HANDLER )
{
	eTIMERDriver *petimer = &ETIMER3;
	uint16_t shiftB;

	IRQ_PROLOGUE();

	shiftB = ( uint16_t )( pwmCD.phaseShift - pwmCD.phaseShiftActive );
	pwmCD.phaseShiftActive = pwmCD.phaseShift;

	petimer->etimer_tagp->CH[ 2 ].CMPLD2.R = ( uint16_t )ETIMER_3_DEAD_TIME - ( uint16_t )shiftB;
	petimer->etimer_tagp->CH[ 3 ].CMPLD2.R = ( uint16_t )( ( 0xFFFFU -shiftB ) + 1U );

	petimer->etimer_tagp->CH[ 3 ].STS.B.TCF2 = 0x1U;

	IRQ_EPILOGUE();
}

/****************************************************************************/
/**                                                                        **/
/**                      LOCAL FUNCTIONS                                   **/
/**                                                                        **/
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static void HAL_PWM_ETIMER3_Config( eTIMERDriver *etimerp )
{
	pwmCD.period = ( uint16_t )ETIMER_3_PERIOD;
	pwmCD.duty = 0U;
	pwmCD.deadTime0 = ETIMER_3_DEAD_TIME;
	pwmCD.deadTime1 = ETIMER_3_DEAD_TIME;
	pwmCD.phaseShift = 0U;
	pwmCD.phaseShiftActive = 0U;

	pwmEF.period = ( uint16_t )ETIMER_3_PERIOD;
	pwmEF.duty = 0U;
	pwmEF.deadTime0 = ETIMER_3_DEAD_TIME;
	pwmEF.deadTime1 = ETIMER_3_DEAD_TIME;

	SPCSetPeripheralClockMode( SPC5_ETIMER3_PCTL, SPC5_ME_PCTL_RUN( 2 ) | SPC5_ME_PCTL_LP( 2 ) );

	etimerp->etimer_tagp->ENBL.R = 0x00U; /* enable etimer channel 0,1,2,3 */
	/*---------------------------------------------------------------------------/
		@ channel A
	----------------------------------------------------------------------------*/
	etimerp->etimer_tagp->CH[ 0 ].CTRL1.B.CNTMODE = 0x01U; /* Counter mode = count rising edges */
	etimerp->etimer_tagp->CH[ 0 ].CTRL1.B.PRISRC = 0x18U; /* Primary count source = IBBus clock devide by prescaler 1 */
	etimerp->etimer_tagp->CH[ 0 ].CTRL1.B.LENGTH = 1U; /* Count until compare */
	etimerp->etimer_tagp->CH[ 0 ].CTRL1.B.ONCE = 0U; /* Continuous count */

	etimerp->etimer_tagp->CH[ 0 ].CTRL2.B.OEN = 0U; /* Output disable */
	etimerp->etimer_tagp->CH[ 0 ].CTRL2.B.OPS = 0U; /* True polarity */
	etimerp->etimer_tagp->CH[ 0 ].CTRL2.B.OUTMODE = 0x08U;	/* Set on successful compare on COMP1, clear on successful compare on COMP2 */

	etimerp->etimer_tagp->CH[ 0 ].CCCTRL.B.CLC1 = 0x03U; /* Load COMP1 with CMPLD1 upon successful compare with the value in COMP2 */
	etimerp->etimer_tagp->CH[ 0 ].CCCTRL.B.CLC2 = 0x07U; /* Load CNTR with CMPLD2 upon successful compare with the value in COMP2 */

	etimerp->etimer_tagp->CH[ 0 ].COMP1.R = ETIMER_3_DUTY/* + ETIMER_3_DEAD_TIME*/; /* Compare value for counter */
	etimerp->etimer_tagp->CH[ 0 ].COMP2.R = ( uint16_t )ETIMER_3_PERIOD; /* Compare value for counter */
	etimerp->etimer_tagp->CH[ 0 ].CMPLD1.R = ETIMER_3_DUTY + ETIMER_3_DEAD_TIME;
	etimerp->etimer_tagp->CH[ 0 ].CMPLD2.R = 0;

	etimerp->etimer_tagp->CH[ 0 ].LOAD.R = 0U; /* Reload value used to initialize the counter */
	etimerp->etimer_tagp->CH[ 0 ].CNTR.R = 0U; /* Initial value */

	/*---------------------------------------------------------------------------/
		@ channel B
	----------------------------------------------------------------------------*/
	etimerp->etimer_tagp->CH[ 1 ].CTRL1.B.CNTMODE = 0x01U; /* Counter mode = count rising edges */
	etimerp->etimer_tagp->CH[ 1 ].CTRL1.B.PRISRC = 0x18U; /* Primary count source = IBBus clock devide by prescaler 1 */
	etimerp->etimer_tagp->CH[ 1 ].CTRL1.B.LENGTH = 1U; /* Count until compare */
	etimerp->etimer_tagp->CH[ 1 ].CTRL1.B.ONCE = 0U; /* Continuous count */

	etimerp->etimer_tagp->CH[ 1 ].CTRL2.B.OEN = 0U; /* Output disable */
	etimerp->etimer_tagp->CH[ 1 ].CTRL2.B.OPS = 1U; /* Inverted polarity */
	etimerp->etimer_tagp->CH[ 1 ].CTRL2.B.OUTMODE = 0x08U;	/* Set on successful compare on COMP1, clear on successful compare on COMP2 */

	etimerp->etimer_tagp->CH[ 1 ].CCCTRL.B.CLC1 = 0x03U; /* Load COMP1 with CMPLD1 upon successful compare with the value in COMP2 */
	etimerp->etimer_tagp->CH[ 1 ].CCCTRL.B.CLC2 = 0x07U; /* Load CNTR with CMPLD2 upon successful compare with the value in COMP2 */

	etimerp->etimer_tagp->CH[ 1 ].COMP1.R = ETIMER_3_DUTY; /* Compare value for counter */
	etimerp->etimer_tagp->CH[ 1 ].COMP2.R = ( uint16_t )( ETIMER_3_PERIOD + ETIMER_3_DEAD_TIME ); /* Compare value for counter */
	etimerp->etimer_tagp->CH[ 1 ].CMPLD1.R = ETIMER_3_DUTY;
	etimerp->etimer_tagp->CH[ 1 ].CMPLD2.R = ETIMER_3_DEAD_TIME;

	etimerp->etimer_tagp->CH[ 1 ].LOAD.R = 0U; /* Reload value used to initialize the counter */
	etimerp->etimer_tagp->CH[ 1 ].CNTR.R = 0U; /* Initial value */

	/*---------------------------------------------------------------------------/
		@ channel D
	----------------------------------------------------------------------------*/
	etimerp->etimer_tagp->CH[ 2 ].CTRL1.B.CNTMODE = 0x01U; /* Counter mode = count rising edges */
	etimerp->etimer_tagp->CH[ 2 ].CTRL1.B.PRISRC = 0x18U; /* Primary count source = IBBus clock devide by prescaler 1 */
	etimerp->etimer_tagp->CH[ 2 ].CTRL1.B.LENGTH = 1U; /* Count until compare */
	etimerp->etimer_tagp->CH[ 2 ].CTRL1.B.ONCE = 0U; /* Continuous count */

	etimerp->etimer_tagp->CH[ 2 ].CTRL2.B.OEN = 0U; /* Output disable */
	etimerp->etimer_tagp->CH[ 2 ].CTRL2.B.OPS = 1U; /* Inverted polarity */
	etimerp->etimer_tagp->CH[ 2 ].CTRL2.B.OUTMODE = 0x08U;	/* Set on successful compare on COMP1, clear on successful compare on COMP2 */

	etimerp->etimer_tagp->CH[ 2 ].CCCTRL.B.CLC1 = 0x03U; /* Load COMP1 with CMPLD1 upon successful compare with the value in COMP2 */
	etimerp->etimer_tagp->CH[ 2 ].CCCTRL.B.CLC2 = 0x07U; /* Load CNTR with CMPLD2 upon successful compare with the value in COMP2 */

	etimerp->etimer_tagp->CH[ 2 ].COMP1.R = ETIMER_3_DUTY; /* Compare value for counter */
	etimerp->etimer_tagp->CH[ 2 ].COMP2.R = ( uint16_t )( ETIMER_3_PERIOD + ETIMER_3_DEAD_TIME ); /* Compare value for counter */
	etimerp->etimer_tagp->CH[ 2 ].CMPLD1.R = ETIMER_3_DUTY;
	etimerp->etimer_tagp->CH[ 2 ].CMPLD2.R = ETIMER_3_DEAD_TIME;

	etimerp->etimer_tagp->CH[ 2 ].LOAD.R = 0U; /* Reload value used to initialize the counter */
	etimerp->etimer_tagp->CH[ 2 ].CNTR.R = 0U; /* Initial value */

	/*---------------------------------------------------------------------------/
		@ channel C
	----------------------------------------------------------------------------*/
	etimerp->etimer_tagp->CH[ 3 ].CTRL1.B.CNTMODE = 0x01U; /* Counter mode = count rising edges */
	etimerp->etimer_tagp->CH[ 3 ].CTRL1.B.PRISRC = 0x18U; /* Primary count source = IBBus clock devide by prescaler 1 */
	etimerp->etimer_tagp->CH[ 3 ].CTRL1.B.LENGTH = 1U; /* Count until compare */
	etimerp->etimer_tagp->CH[ 3 ].CTRL1.B.ONCE = 0U; /* Continuous count */

	etimerp->etimer_tagp->CH[ 3 ].CTRL2.B.OEN = 0U; /* Output disable */
	etimerp->etimer_tagp->CH[ 3 ].CTRL2.B.OPS = 0U; /* True polarity */
	etimerp->etimer_tagp->CH[ 3 ].CTRL2.B.OUTMODE = 0x08U;	/* Set on successful compare on COMP1, clear on successful compare on COMP2 */

	etimerp->etimer_tagp->CH[ 3 ].CCCTRL.B.CLC1 = 0x03U; /* Load COMP1 with CMPLD1 upon successful compare with the value in COMP2 */
	etimerp->etimer_tagp->CH[ 3 ].CCCTRL.B.CLC2 = 0x07U; /* Load CNTR with CMPLD2 upon successful compare with the value in COMP2 */

	etimerp->etimer_tagp->CH[ 3 ].COMP1.R = ETIMER_3_DUTY + ETIMER_3_DEAD_TIME; /* Compare value for counter */
	etimerp->etimer_tagp->CH[ 3 ].COMP2.R = ( uint16_t )ETIMER_3_PERIOD; /* Compare value for counter */
	etimerp->etimer_tagp->CH[ 3 ].CMPLD1.R = ETIMER_3_DUTY + ETIMER_3_DEAD_TIME;
	etimerp->etimer_tagp->CH[ 3 ].CMPLD2.R = 0U;

	etimerp->etimer_tagp->CH[ 3 ].LOAD.R = 0U; /* Reload value used to initialize the counter */
	etimerp->etimer_tagp->CH[ 3 ].CNTR.R = 0U; /* Initial value */

	/*---------------------------------------------------------------------------/
		@ channel SR1
	----------------------------------------------------------------------------*/
	etimerp->etimer_tagp->CH[ 4 ].CTRL1.B.CNTMODE = 0x01U; /* Counter mode = count rising edges */
	etimerp->etimer_tagp->CH[ 4 ].CTRL1.B.PRISRC = 0x18U; /* Primary count source = IBBus clock devide by prescaler 1 */
	etimerp->etimer_tagp->CH[ 4 ].CTRL1.B.LENGTH = 1U; /* Count until compare */
	etimerp->etimer_tagp->CH[ 4 ].CTRL1.B.ONCE = 0U; /* Continuous count */

	etimerp->etimer_tagp->CH[ 4 ].CTRL2.B.OEN = 0U; /* Output disable */
	etimerp->etimer_tagp->CH[ 4 ].CTRL2.B.OPS = 0U; /* True polarity */
	etimerp->etimer_tagp->CH[ 4 ].CTRL2.B.OUTMODE = 0x08U;	/* Set on successful compare on COMP1, clear on successful compare on COMP2 */

	etimerp->etimer_tagp->CH[ 4 ].CCCTRL.B.CLC1 = 0x03U; /* Load COMP1 with CMPLD1 upon successful compare with the value in COMP2 */
	etimerp->etimer_tagp->CH[ 4 ].CCCTRL.B.CLC2 = 0x07U; /* Load CNTR with CMPLD2 upon successful compare with the value in COMP2 */

	etimerp->etimer_tagp->CH[ 4 ].COMP1.R = ETIMER_3_DUTY + ETIMER_3_DEAD_TIME; /* Compare value for counter */
	etimerp->etimer_tagp->CH[ 4 ].COMP2.R = ( uint16_t )ETIMER_3_PERIOD; /* Compare value for counter */
	etimerp->etimer_tagp->CH[ 4 ].CMPLD1.R = ETIMER_3_DUTY + ETIMER_3_DEAD_TIME;
	etimerp->etimer_tagp->CH[ 4 ].CMPLD2.R = 0U;

	etimerp->etimer_tagp->CH[ 4 ].LOAD.R = 0U; /* Reload value used to initialize the counter */
	etimerp->etimer_tagp->CH[ 4 ].CNTR.R = ( uint16_t )( ETIMER_3_PERIOD / 2 ) - ( ETIMER_3_DEAD_TIME/ 2 ); /* Initial value */

	/*---------------------------------------------------------------------------/
		@ channel SR2
	----------------------------------------------------------------------------*/
	etimerp->etimer_tagp->CH[ 5 ].CTRL1.B.CNTMODE = 0x01U; /* Counter mode = count rising edges */
	etimerp->etimer_tagp->CH[ 5 ].CTRL1.B.PRISRC = 0x18U; /* Primary count source = IBBus clock devide by prescaler 1 */
	etimerp->etimer_tagp->CH[ 5 ].CTRL1.B.LENGTH = 1U; /* Count until compare */
	etimerp->etimer_tagp->CH[ 5 ].CTRL1.B.ONCE = 0U; /* Continuous count */

	etimerp->etimer_tagp->CH[ 5 ].CTRL2.B.OEN = 0U; /* Output disable */
	etimerp->etimer_tagp->CH[ 5 ].CTRL2.B.OPS = 0U; /* True polarity */
	etimerp->etimer_tagp->CH[ 5 ].CTRL2.B.OUTMODE = 0x08U;	/* Set on successful compare on COMP1, clear on successful compare on COMP2 */

	etimerp->etimer_tagp->CH[ 5 ].CCCTRL.B.CLC1 = 0x03U; /* Load COMP1 with CMPLD1 upon successful compare with the value in COMP2 */
	etimerp->etimer_tagp->CH[ 5 ].CCCTRL.B.CLC2 = 0x07U; /* Load CNTR with CMPLD2 upon successful compare with the value in COMP2 */

	etimerp->etimer_tagp->CH[ 5 ].COMP1.R = ETIMER_3_DUTY + ETIMER_3_DEAD_TIME; /* Compare value for counter */
	etimerp->etimer_tagp->CH[ 5 ].COMP2.R = ( uint16_t )ETIMER_3_PERIOD; /* Compare value for counter */
	etimerp->etimer_tagp->CH[ 5 ].CMPLD1.R = ETIMER_3_DUTY + ETIMER_3_DEAD_TIME;
	etimerp->etimer_tagp->CH[ 5 ].CMPLD2.R = 0U;

	etimerp->etimer_tagp->CH[ 5 ].LOAD.R = 0U; /* Reload value used to initialize the counter */
	etimerp->etimer_tagp->CH[ 5 ].CNTR.R = ( uint16_t )( -ETIMER_3_DEAD_TIME / 2 ); /* Initial value */

	/* configure interrupt for PWM C */
	etimerp->etimer_tagp->CH[ 3 ].STS.R = 0x3FFU;	/* clear interrupt flag */
	etimerp->etimer_tagp->CH[ 3 ].INTDMA.B.TCF2IE = 0x1U;		/* Enable timer2 compare 2 flag interrupt */

	INTC_0.PSR[SPC5_ETIMER3_TC3IR_NUMBER].R = INTC_PSR_ENABLE( INTC_PSR_CORE0, 15 );
}

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/

