/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : KSC_FBL                                                     **
**  Filename  : GpFunc.c                                                    **
**  Version   : -.- (PCB : )                                                **
**  Date      : 2019.04.11                                                  **
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

#define GPFUNC_C_SRC

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "GpFunc.h"
#include "flashdriver.h"

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
static uint8_t Flash_Drv_Erase ( uint8_t u8_Block, uint8_t u8_FlashSpace );
static uint8_t Flash_Drv_Program ( UINT32 u32_Addr, UINT32 *u32p_Buffer, UINT32 u32_Len );
static uint32_t MemoryGetuint32_t ( uint32_t u32_Addr );

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

static SSD_CONFIG sts_FlashCfg =
{
  C55_REG_BASE,							/* C55 control register base */
  MAIN_ARRAY_BASE,					/* base of main array */
  {1, 4, 2, 2}, 						/* u8_Blocks info of low address space */
  {0, 0, 0, 0}, 						/* u8_Blocks info of mid address space */
  {4, 0, 0, 0}, 						/* u8_Blocks info of high address space */
  2, 												/* number of u8_Blocks in 256K address space */
  UTEST_ARRAY_BASE, 				/* base of UTEST array */
  TRUE, 										/* interface flag indicate main or alternate interface */
  C55_PROGRAMMABLE_SIZE,		/* programmable size */
  FALSE 										/* debug mode selection */
};

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
void Gp_Func_Init ( void )
{
	UINT32 u32_Ret;
	uint32_t u32_Delay = 0U;

	if( FlashInit ( &sts_FlashCfg ) == C55_OK )
	{
		do
		{
			u32_Delay++;
			u32_Ret = SetLock ( &sts_FlashCfg, C55_BLOCK_HIGH, UNLOCK_ALL_BLOCKS ); /* Dflash */
		}while( ( u32_Ret != C55_OK ) && ( u32_Delay < 10000U ) );
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
void EEP_WriteDataByIdentifier ( UINT32 *u32_dtcbuffer, UINT32 Address)
{
	if( Flash_Drv_Program ( Address, u32_dtcbuffer, 32U ) == FLASH_OK )
	{
		switch( Address )
		{
			case BLOCK1_ADDR - 0x80U:
				if( Flash_Drv_Erase ( 1U, FLASH_HIGH_SPACE ) == FLASH_OK )
				{
					present_addr =  present_addr + 0x20U;
				}
				break;
			case BLOCK2_ADDR - 0x20U:
				if( Flash_Drv_Erase ( 0U, FLASH_HIGH_SPACE ) == FLASH_OK )
				{
					present_addr =  BLOCK0_ADDR;
				}
				break;
			default:
				present_addr =  present_addr + 0x20U;
				break;
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
uint32_t EEP_ReadDataByIdentifier ( uint32_t u32_Addr)
{
	uint32_t u32_ReadMode;

	u32_ReadMode = MemoryGetuint32_t ( u32_Addr );

	return u32_ReadMode;
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
static uint8_t Flash_Drv_Erase ( uint8_t u8_Block, uint8_t u8_FlashSpace )
{
	UINT32 u32_LowBlockSelect;
	UINT32 u32_MidBlockSelect;
	UINT32 u32_HighBlockSelect;
	uint8_t u8_Ret = FLASH_OK;
	UINT32 u32_ChkSts;
	NLARGE_BLOCK_SEL st_LargeBlockSelect;
	CONTEXT_DATA st_DummyCtxData;

	u32_LowBlockSelect = 0;
	u32_MidBlockSelect = 0;
	u32_HighBlockSelect = 0;
	st_LargeBlockSelect.firstLargeBlockSelect = 0U;
	st_LargeBlockSelect.secondLargeBlockSelect = 0U;

	if( ( u8_FlashSpace == FLASH_256K_SPACE ) || ( u8_FlashSpace == FLASH_128K_SPACE ) )
	{
		st_LargeBlockSelect.firstLargeBlockSelect = ( 1UL << u8_Block );
	}
	else if( u8_FlashSpace == FLASH_HIGH_SPACE )
	{
		u32_HighBlockSelect =  ( ( UINT32 )1U << u8_Block );
	}
	else
	{
		if( u8_FlashSpace == FLASH_LOW_SPACE )
		{
			u32_LowBlockSelect = ( ( UINT32 )1U << u8_Block );
		}
	}

	/* Erase the Block */
	if( FlashErase ( &sts_FlashCfg, C55_ERASE_MAIN, u32_LowBlockSelect, u32_MidBlockSelect, u32_HighBlockSelect, st_LargeBlockSelect ) != C55_OK )
	{
		u8_Ret = FLASH_ERROR_ERASE;
	}

	/* Call FlashCheckStatus() to check status of the progress */
	while( FlashCheckStatus ( &sts_FlashCfg, C55_MODE_OP_ERASE, &u32_ChkSts, &st_DummyCtxData) == C55_INPROGRESS ){}

	if( C55_OK != u32_ChkSts )
	{
		u8_Ret = FLASH_ERROR_ERASE;
	}

	return ( u8_Ret );
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static uint8_t Flash_Drv_Program ( UINT32 u32_Addr, UINT32 *u32p_Buffer, UINT32 u32_Len )
{
  uint8_t u8_Ret = FLASH_OK;
  UINT32 u32_BufferPointer;
  UINT32 u32_ChkSts;
  CONTEXT_DATA st_PgmCtxData;

  u32_BufferPointer = ( uint32_t )&u32p_Buffer[ 0 ];

  if( FlashProgram ( &sts_FlashCfg, FALSE, u32_Addr, u32_Len, u32_BufferPointer, &st_PgmCtxData ) == C55_OK )
  {
    /* Call FlashCheckStatus() to check status of the progress */
    while( FlashCheckStatus ( &sts_FlashCfg, C55_MODE_OP_PROGRAM, &u32_ChkSts, &st_PgmCtxData) == C55_INPROGRESS ){}

    if( u32_ChkSts != C55_OK ){ u8_Ret = FLASH_ERROR_PROGRAM; }
  }
  else
  {
  	u8_Ret = FLASH_ERROR_PROGRAM;
  }

  /* ( void )u32p_Buffer; */

  return ( u8_Ret );
}

/*--------------------------------------------------------------------------*/
/* Function  |                                                              */
/* Name      |                                                              */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
static uint32_t MemoryGetuint32_t ( uint32_t u32_Addr )
{
	uint32_t u32_MemData;

	u32_MemData = *( ( volatile uint32_t * )u32_Addr );

	return ( u32_MemData );
}

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
