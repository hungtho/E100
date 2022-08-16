
/*
                             *******************
******************************* C HEADER FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : SPC570S_FBL                                                 **
**  Filename  : Defines.h                                                   **
**  Version   : -.- (PCB : )                                                **
**  Date      : 2019.05.10                                                  **
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

#ifndef DEFINES_INCLUDED
#define DEFINES_INCLUDED

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "components.h"
#include "platform.h"

/****************************************************************************/
/**                                                                        **/
/**                      DEFINITIONS AND MACROS                            **/
/**                                                                        **/
/****************************************************************************/
#define BLOCK0_ADDR									( 0x00800000U )
#define BLOCK1_ADDR									( 0x00802000U )
#define BLOCK2_ADDR									( 0x00804000U )
#define BLOCK3_ADDR									( 0x00806000U )

#define BASE_TICK		( 1U )  /* 5us per 1 tick  */

/* decompose 8 bit data in nibble stream */
/* #define Get8BitHiNibble( data )   ( ( uint8_t )( ( data & 0xF0U ) >> 4 ) ) */
/* #define Get8BitLoNibble( data )   ( ( uint8_t )( ( data & 0x0FU ) ) ) */

/* decompose 16 bit data in uint8_t stream */
/* #define Get16BitHiByte( data )    ( ( uint8_t )( ( ( uint16_t )( data ) ) >> 8 ) ) */
/* #define Get16BitLoByte( data )    ( ( uint8_t )( data ) ) */

/* decompose 32 bit data in uint8_t stream */
/* #define Get32BitHiHiByte( data )    ( ( uint8_t )( ( ( uint32_t )( data ) ) >> 24 ) ) */
/* #define Get32BitHiLoByte( data )    ( ( uint8_t )( ( ( uint32_t )( data ) ) >> 16 ) ) */
/* #define Get32BitLoHiByte( data )    ( ( uint8_t )( ( ( uint32_t )( data ) ) >> 8 ) ) */
/* #define Get32BitLoLoByte( data )    ( ( uint8_t )( data ) ) */

/* decompose 32 bit data in uint16_t stream */
/* #define Get32BitHiWord( data )    ( ( uint16_t )( ( ( uint32_t )( data ) ) >> 16 ) ) */
/* #define Get32BitLoWord( data )    ( ( uint16_t )( data ) ) */

/*****************************************************************************
  @ Internal definitions of the error constants.
*****************************************************************************/
#define ERR_OK          ( 0U )  /* OK */
#define ERR_SPEED       ( 1U )  /* This device does not work in the active speed mode. */
#define ERR_RANGE       ( 2U )  /* Parameter out of range. */
#define ERR_VALUE       ( 3U )  /* Parameter of incorrect value. */
#define ERR_OVERFLOW    ( 4U )  /* Timer overflow. */
#define ERR_MATH        ( 5U )  /* Overflow during evaluation. */
#define ERR_ENABLED     ( 6U )  /* Device is enabled. */
#define ERR_DISABLED    ( 7U )  /* Device is disabled. */
#define ERR_BUSY        ( 8U )  /* Device is busy. */
#define ERR_NOTAVAIL    ( 9U )  /* Requested value or method not available. */
#define ERR_RXEMPTY     ( 10U ) /* No data in receiver. */
#define ERR_TXFULL      ( 11U ) /* Transmitter is full. */
#define ERR_BUSOFF      ( 12U ) /* Bus not available. */
#define ERR_OVERRUN     ( 13U ) /* Overrun error is detected. */
#define ERR_FRAMING     ( 14U ) /* Framing error is detected. */
#define ERR_PARITY      ( 15U ) /* Parity error is detected. */
#define ERR_NOISE       ( 16U ) /* Noise error is detected. */
#define ERR_IDLE        ( 17U ) /* Idle error is detected. */
#define ERR_FAULT       ( 18U ) /* Fault error is detected. */
#define ERR_BREAK       ( 19U ) /* Break char is received during communication. */
#define ERR_CRC         ( 20U ) /* CRC error is detected. */
#define ERR_ARBITR      ( 21U ) /* A node losts arbitration. This error occurs if two nodes start transmission at the same time. */
#define ERR_PROTECT     ( 22U ) /* Protection error is detected. */
#define ERR_UNDERFLOW   ( 23U ) /* Underflow error is detected. */
#define ERR_UNDERRUN    ( 24U ) /* Underrun error is detected. */
#define ERR_COMMON      ( 25U ) /* Common error of a device. */
#define ERR_LINSYNC     ( 26U ) /* LIN synchronization error is detected. */

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

# ifndef DEFINES_C_SRC
# endif

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/

#endif

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
