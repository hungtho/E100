/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : E100_LDC                                                    **
**  Filename  : flexcan_BSW.c                                               **
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

#define FLEXCAN_BSW_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "flexcan_BSW.h"
#include "v_inc.h"
#include "desc.h"
#include "../RTE/Rte_AswBswLink.h"
#include "Asw_DiagAdc.h"

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
uint8_t u8g_CAN_WaitTx = 0U;

/****************************************************************************/
/**                                                                        **/
/**                      GLOBAL VARIABLES                                  **/
/**                                                                        **/
/****************************************************************************/
static uint16_t u16s_canBusoffCnt = 0U;
static uint8_t u8g_CAN_Release_cnt = 0U;

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
void BSW_FlexCan_Init( void )
{
	SPCSetPeripheralClockMode( SPC5_FLEXCAN0_PCTL, SPC5_ME_PCTL_RUN( 2 ) | SPC5_ME_PCTL_LP( 2 ) );

	CanInitPowerOn();
	IlInitPowerOn();
	TpInitPowerOn();
	DescInitPowerOn( 0U );
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void TEST_DI( void ) /* [CS_IGNORE=MISRA_C_2012.MISRA_C_2012_08_02;void Hal_CtuSetTriggerDelay(CTUDriver *ctup,uint16_t ch, uint16_t delay, uint16_t enableReload)] */
{
	irqIsrDisable();
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void TEST_EI( void ) /* [CS_IGNORE=MISRA_C_2012.MISRA_C_2012_08_02;Can not handle this fucntion. This function is generated automatically by Vector Embedded] */
{
	irqIsrEnable();
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void ApplCanFatalError( CAN_CHANNEL_CANTYPE_FIRST vuint8 errorNumber ) {}/* [CS_IGNORE=MISRA_C_2012.MISRA_C_2012_02_07;can not handle this fucntion. this is for vector] */ /* [CS_IGNORE=MISRA_C_2012.MISRA_C_2012_08_02;Can not handle this fucntion. This function is generated automatically by Vector Embedded] */ /* [CS_IGNORE=MISRA_C_2012.MISRA_C_2012_08_04;Can not handle this fucntion. This function is generated automatically by Vector Embedded] */

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void ApplIlFatalError( vuint8 errorNumber ){} /* [CS_IGNORE=MISRA_C_2012.MISRA_C_2012_08_04;Can not handle this fucntion. This function is generated automatically by Vector Embedded] */

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void  ApplCanBusOff(void) /* [CS_IGNORE=MISRA_C_2012.MISRA_C_2012_08_02;Can not handle this fucntion. This function is generated automatically by Vector Embedded] */ /* [CS_IGNORE=MISRA_C_2012.MISRA_C_2012_08_04;Can not handle this fucntion. This function is generated automatically by Vector Embedded] */
{
	if( rteCanBusOffCnt < 253 ){ rteCanBusOffCnt++; }

	if( u16s_canBusoffCnt >= CAN_BUS_OFF_ERR_CNT )
	{
		setReg32Bits( u32g_LDC_ERR_Sts, DTC_U1101 );
		RTE_SET_CAN_BUS_OFF_STATE( 0U );
	}
	else
	{
		u16s_canBusoffCnt++;
	}
	u8g_CAN_WaitTx = 1U;
	u8g_CAN_Release_cnt = 0U;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
vuint8 ApplCanMsgReceived( CanRxInfoStructPtr rxStruct ) /* [CS_IGNORE=MISRA_C_2012.MISRA_C_2012_02_07;Can not handle this fucntion. This function is generated automatically by Vector Embedded] */ /* [CS_IGNORE=MISRA_C_2012.MISRA_C_2012_08_02;Can not handle this fucntion. This function is generated automatically by Vector Embedded] */ /* [CS_IGNORE=MISRA_C_2012.MISRA_C_2012_08_04;Can not handle this fucntion. This function is generated automatically by Vector Embedded] */
{
	rteCanBusOffCnt = 0U;
	u16s_canBusoffCnt = 0U;
	clrReg32Bits( u32g_LDC_ERR_Sts, DTC_U1101 );
	RTE_SET_CAN_BUS_OFF_STATE( 1U );

	return ( kCanCopyData );
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void Conf_BRS_INVENTED_TX_MSG(CanTransmitHandle txObject){} /* [CS_IGNORE=MISRA_C_2012.MISRA_C_2012_02_07;Can not handle this fucntion. This function is generated automatically by Vector Embedded] */ /* [CS_IGNORE=MISRA_C_2012.MISRA_C_2012_08_02;Can not handle this fucntion. This function is generated automatically by Vector Embedded] */

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void VCU245_TEST(CanReceiveHandle rcvObject){} /* [CS_IGNORE=MISRA_C_2012.MISRA_C_2012_02_07;Can not handle this fucntion. This function is generated automatically by Vector Embedded] */ /* [CS_IGNORE=MISRA_C_2012.MISRA_C_2012_08_02;Can not handle this fucntion. This function is generated automatically by Vector Embedded] */

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void CAN_ReleasTx ( void )
{
	if( u8g_CAN_WaitTx == 1U )
	{
		u8g_CAN_Release_cnt++;
		if( u8g_CAN_Release_cnt >= 20U )
		{
			CanResetBusOffStart( 0U );
			u8g_CAN_WaitTx = 0U;
		}
	}

	return;
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
