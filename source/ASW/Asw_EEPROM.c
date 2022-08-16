/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : E100_LDC                                                    **
**  Filename  : Asw_EEPROM.c                                                **
**  Version   : -.- (PCB : )                                                **
**  Date      : 2019.10.21                                                  **
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

#define ASW_EEPROM_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "Asw_EEPROM.h"
#include "Asw_DiagCan.h"
#include "GpFunc.h"

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
static void DTC_Eeprom_Write ( void );

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/
const uint8_t DTC_CODE_Array[ 3 ][ DTC_CODE_NUMBER ] =
{
	{ 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0xD1, 0xD1 },
	{ 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x01, 0x02 },
	{ 0x9F, 0x9F, 0x96, 0x96, 0x96, 0x96, 0x98, 0x9A, 0x08, 0x08 }
};

uint32_t DTC_BUFFER[ 8 ] = { 0, 0, 0, 0, 0, 0, 0, 0 };
uint32_t present_addr;
uint8_t u8_DtcControl = 0U;
uint8_t u8g_ReqReset = 0U;

/****************************************************************************/
/**                                                                        **/
/**                      GLOBAL VARIABLES                                  **/
/**                                                                        **/
/****************************************************************************/
static uint32_t EEPROM_DTC_BUFFER[ 8 ] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static uint8_t WriteEEPROM_Flag = 0U;

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
void FindCurrentAdd ( void )
{
	uint32_t u32_add = BLOCK0_ADDR;
	uint8_t u8_foundFresentAdd_Flag = 0U;

	uint32_t u32_eep_tmp;
	uint32_t u32_eep_tmp1;
	uint32_t u32_eep_tmp2;
	uint32_t u32_eep_tmp3;

	if( EEP_ReadDataByIdentifier( BLOCK2_ADDR - 0x20U ) != 0xFFFFFFFFU )
	{
		u32_add = BLOCK0_ADDR;
	}
	else
	{
		if( EEP_ReadDataByIdentifier( BLOCK1_ADDR ) == 0xFFFFFFFFU )
		{
			u32_add = BLOCK0_ADDR;
		}
		else
		{
			u32_add = BLOCK1_ADDR;
		}
	}

	while( u8_foundFresentAdd_Flag != 1U )
	{
		u32_eep_tmp = EEP_ReadDataByIdentifier( u32_add );
		u32_eep_tmp1 = EEP_ReadDataByIdentifier( u32_add + 0x4U );
		u32_eep_tmp2 = EEP_ReadDataByIdentifier( u32_add + 0x8U );
		u32_eep_tmp3 = EEP_ReadDataByIdentifier( u32_add + 0xCU );

		if( ( u32_eep_tmp & u32_eep_tmp1 & u32_eep_tmp2 & u32_eep_tmp3 ) != 0xFFFFFFFFU )
		{
			u32_add += 0x20U;
		}
		else
		{
			u8_foundFresentAdd_Flag = 1U;
			present_addr = u32_add;
		}
	}
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void DTC_Eeprom_Read ( uint32_t addr )
{
	uint8_t u8_i = 0U;
	uint32_t ee_addr;
	uint32_t ee_read;

	if( ( addr >= BLOCK0_ADDR ) && ( addr < BLOCK2_ADDR ) )
	{
		for( u8_i = 0U; u8_i < 8U; u8_i++ )
		{
			if( addr == BLOCK0_ADDR )
			{
				ee_addr = ( BLOCK2_ADDR - 0x20U ) + ( ( uint32_t )u8_i * 0x04U );
			}
			else
			{
				ee_addr = ( addr - 0x20U ) + ( ( uint32_t )u8_i * 0x04U );
			}

			ee_read = EEP_ReadDataByIdentifier( ee_addr );

			if( ee_read != 0xFFFFFFFFU )
			{
				DTC_BUFFER[ u8_i ] = ee_read;
				EEPROM_DTC_BUFFER[ u8_i ] = ee_read;
			}
		}
	}
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void DTC_Eeprom_Update ( void )
{
	uint8_t u8s_i = 0U;
	uint32_t u32_tmp = 0;
	uint8_t u8_BufIdx;
	uint8_t u8_BufPtr;
	uint32_t u32_BufSts;

	for( u8s_i = 0U; u8s_i < DTC_CODE_NUMBER; u8s_i++ )
	{
		u32_tmp = ( uint32_t )0x00000001U << u8s_i;

		u8_BufIdx = ( uint8_t )( u8s_i / 4U );
		u8_BufPtr = ( uint8_t )( u8s_i % 4U );

		/* Save DTC_Code into DTC array buffer */
		if( ( u32_tmp & u32g_LDC_ERR_Sts ) != 0U )
		{
			u32_BufSts = ( uint32_t )0x09U << ( ( uint32_t )u8_BufPtr * 8U );
			DTC_BUFFER[ u8_BufIdx ] |= u32_BufSts;
		}
		else
		{
			u32_BufSts = ( uint32_t )0x01U << ( ( uint32_t )u8_BufPtr * 8U );
			DTC_BUFFER[ u8_BufIdx ] &= ( ~u32_BufSts );
		}
	}

	return;
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void Eeprom_Write ( void )
{
	DTC_Eeprom_Write();

	if( WriteEEPROM_Flag == 1U )
	{
		/* Write dtc code to EEPROM during key off */
		EEP_WriteDataByIdentifier( &DTC_BUFFER[ 0 ], ( UINT32 )present_addr );
		WriteEEPROM_Flag = 0U;
	}
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
static void DTC_Eeprom_Write ( void )
{
	uint8_t u8_j = 0U;

	for( u8_j = 0; u8_j < 8U; u8_j++ )
	{
		if( DTC_BUFFER [ u8_j ] != EEPROM_DTC_BUFFER [ u8_j ] )
		{
			EEPROM_DTC_BUFFER [ u8_j ] = DTC_BUFFER [ u8_j ];
			WriteEEPROM_Flag = 1U;
		}
	}
}

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
