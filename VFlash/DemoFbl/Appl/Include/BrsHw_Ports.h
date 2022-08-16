
/**********************************************************************************************************************
  COPYRIGHT
-----------------------------------------------------------------------------------------------------------------------
  \par      copyright
  \verbatim
  Copyright (c) 2018 by Vector Informatik GmbH.                                                  All rights reserved.

                This software is copyright protected and proprietary to Vector Informatik GmbH.
                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
                All other rights remain with Vector Informatik GmbH.
  \endverbatim
-----------------------------------------------------------------------------------------------------------------------
  FILE DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
  \file  File:  BrsHw_Ports.h
      Project:  Vector Basic Runtime System
       Module:  BrsHw for platform Freescale/ST Mpc57xx

  \brief Description:  This header file contains the information for the evalboard specific port settings,
                       supported by this Brs implementation.

  \attention Please note:
    The demo and example programs only show special aspects of the software. With regard to the fact
    that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
    expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
**********************************************************************************************************************/

/**********************************************************************************************************************
  AUTHOR IDENTITY
 ----------------------------------------------------------------------------------------------------------------------
  Name                          Initials      Company
  ----------------------------  ------------  -------------------------------------------------------------------------
  Benjamin Walter               visbwa        Vector Informatik GmbH
  Cyrille Wamba                 viswca        Vector Informatik GmbH
  Ivo Georgiev                  visivg        Vector Informatik GmbH
  Sascha Mauser                 vismaa        Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
 ----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Description
  --------  ----------  ------  ---------------------------------------------------------------------------------------
  01.00.00  2016-08-29  visbwa  Initial creation for TCM support and alive LED handling
  01.00.01  2017-01-11  viswca  Added TCM pins for MPC5773N and MPC5748G
            2017-01-20  visbwa  Review
  01.01.00  2017-07-03  visivg  Complete rework, added SPC57xx_144PIN support and abstraction for BRSHW_SIU_GROUP_D_2
            2017-07-07  visbwa  Review
  01.01.01  2017-07-12  visivg  Fixed compiler warning within brsHw_Port_PullOption
  01.01.02  2017-07-17  visivg  Added defines for port pins
  01.01.03  2017-08-11  vismaa  Added Led Port A0 for DEFAULT
  01.01.04  2017-11-15  vismaa  Added MCAN pins for BRSHW_SIU_GROUP_A, added new define for MCAN in BRSHW_SIU_GROUP_B
  01.01.05  2018-03-28  visbwa  Review according to Brs_Template 2.02.02,
                                added BRSHW_PORT_LED for DEFAULT mode and pins 98 + 114
**********************************************************************************************************************/

#ifndef _BRSHW_PORTS_H_
#define _BRSHW_PORTS_H_

/*******************************************************************************
  Generic PORT definition types
********************************************************************************/
typedef enum
{
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTGROUP_B,
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTGROUP_D,
  BRSHW_PORT_PORTGROUP_E,
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTGROUP_G,
  BRSHW_PORT_PORTGROUP_H,
  BRSHW_PORT_PORTGROUP_I,
  BRSHW_PORT_PORTGROUP_J,
  BRSHW_PORT_PORTGROUP_K,
  BRSHW_PORT_PORTGROUP_L,
  BRSHW_PORT_PORTGROUP_M
}brsHw_Port_PortGroupType;

typedef enum
{
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_PORTNUMBER_15
}brsHw_Port_PortNumberType;

typedef enum
{
  BRSHW_PORT_ALT_0,
  BRSHW_PORT_ALT_1,
  BRSHW_PORT_ALT_2,
  BRSHW_PORT_ALT_3,
  BRSHW_PORT_ALT_4,
  BRSHW_PORT_ALT_5,
  BRSHW_PORT_ALT_6,
  BRSHW_PORT_ALT_7,
  BRSHW_PORT_ALT_8,
  BRSHW_PORT_ALT_9
}brsHw_Port_AlternativeType;

typedef enum
{
  PORT_PULL_UP_ENABLED,
  PORT_PULL_DOWN_ENABLED,
  PORT_PULL_FUNCTION_DISABLED
}brsHw_Port_PullOption;

typedef struct
{
  brsHw_Port_PullOption PortPullOption;
}brsHw_Port_ConfType;

#if defined (BRSHW_SIU_GROUP_B)
typedef struct
{
  uint32                     muxMSCRValue;
  brsHw_Port_AlternativeType muxMultiplexedAlternative;
}brsHw_Port_PortType;

#elif defined (BRSHW_SIU_GROUP_D_2)
typedef enum
{
  BRSHW_PORT_SIUL_A,
  BRSHW_PORT_SIUL_B
}brsHw_Port_SIULType;

typedef struct
{
  uint32                     muxMSCRValue;
  brsHw_Port_SIULType        portSIUL;
  brsHw_Port_AlternativeType muxMultiplexedAlternative;
}brsHw_Port_PortType;

#else
typedef struct
{
  brsHw_Port_PortGroupType   portGroup;
  brsHw_Port_PortNumberType  portNumber;
  brsHw_Port_AlternativeType portAlternative;
}brsHw_Port_PortType;
#endif /*BRSHW_SIU_GROUP_x*/

#if defined (BRSHW_SIU_GROUP_A)
typedef struct
{
  uint32                     muxIMCRValue;
  brsHw_Port_AlternativeType muxMultiplexedAlternative;
}brsHw_Port_MultiplexedType;

#elif defined (BRSHW_SIU_GROUP_B)
typedef enum
{
  BRSHW_PORT_SIUL_MUXSEL_0,
  BRSHW_PORT_SIUL_MUXSEL_1,
  BRSHW_PORT_SIUL_MUXSEL_2,
  BRSHW_PORT_SIUL_MUXSEL_3,
  BRSHW_PORT_SIUL_MUXSEL_4,
  BRSHW_PORT_SIUL_MUXSEL_5,
  BRSHW_PORT_SIUL_MUXSEL_6,
  BRSHW_PORT_SIUL_MUXSEL_7,
  BRSHW_PORT_SIUL_MUXSEL_8,
  BRSHW_PORT_SIUL_MUXSEL_9,
  BRSHW_PORT_SIUL_MUXSEL_10,
  BRSHW_PORT_SIUL_MUXSEL_11,
  BRSHW_PORT_SIUL_MUXSEL_12,
  BRSHW_PORT_SIUL_MUXSEL_13,
  BRSHW_PORT_SIUL_MUXSEL_14,
  BRSHW_PORT_SIUL_MUXSEL_15
}brsHw_Port_MUXSEL;

typedef struct
{
  uint32                     muxIMUXValue;
  brsHw_Port_MUXSEL          muxMUXSEL;
  brsHw_Port_AlternativeType muxMultiplexedAlternative;
}brsHw_Port_MultiplexedType;

const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_EMPTY_DUMMY = { /* For Pins w/o IMUX */
  0xFF,
  BRSHW_PORT_SIUL_MUXSEL_0,
  BRSHW_PORT_ALT_0};

#else
typedef struct
{
  uint32                     muxMSCRValue;
  brsHw_Port_AlternativeType muxMultiplexedAlternative;
}brsHw_Port_MultiplexedType;
#endif /*BRSHW_SIU_GROUP_x*/

#define BRSHW_PORT_LOGIC_HIGH (uint8)1
#define BRSHW_PORT_LOGIC_LOW  (uint8)0

/*******************************************************************************
  PIN configuration for TCM support
********************************************************************************/
#if defined (BRS_ENABLE_TCM_SUPPORT)
# if defined (BRS_DERIVATIVE_MPC5773N)
const brsHw_Port_PortType BRSHW_PORT_TCM_SDA_OUT = {
  BRSHW_PORT_PORTGROUP_H,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType BRSHW_PORT_TCM_SDA_IN = {
  BRSHW_PORT_PORTGROUP_H,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_TCM_SDA_IN = {
  118u,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType BRSHW_PORT_TCM_CLK_OUT = {
  BRSHW_PORT_PORTGROUP_H,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType BRSHW_PORT_TCM_CLK_IN = {
  BRSHW_PORT_PORTGROUP_H,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_TCM_CLK_IN = {
  119u,
  BRSHW_PORT_ALT_0};

#if 0
const brsHw_Port_PortType BRSHW_PORT_TCM_INTA_IN = {
  BRSHW_PORT_PORTGROUP_G,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_TCM_INTA_IN = {
  104u,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType BRSHW_PORT_TCM_INTB_IN = {
  BRSHW_PORT_PORTGROUP_G,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_TCM_INTB_IN = {
  105u,
  BRSHW_PORT_ALT_0};
#  endif /*BRS_ENABLE_TCM_EXT_IRQ*/

# elif defined (BRS_DERIVATIVE_MPC5748G)
const brsHw_Port_PortType BRSHW_PORT_TCM_SDA_OUT = {
  BRSHW_PORT_PORTGROUP_I,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType BRSHW_PORT_TCM_SDA_IN = {
  BRSHW_PORT_PORTGROUP_I,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_TCM_SDA_IN = {
  137u,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType BRSHW_PORT_TCM_CLK_OUT = {
  BRSHW_PORT_PORTGROUP_I,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_ALT_0};
const brsHw_Port_PortType BRSHW_PORT_TCM_CLK_IN = {
  BRSHW_PORT_PORTGROUP_I,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_TCM_CLK_IN = {
  138u,
  BRSHW_PORT_ALT_0};

#if 0
const brsHw_Port_PortType BRSHW_PORT_TCM_INTA_IN = {
  BRSHW_PORT_PORTGROUP_K,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_1};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_TCM_INTA_IN = {
  687u,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_TCM_INTB_IN = {
  BRSHW_PORT_PORTGROUP_M,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_ALT_1};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_TCM_INTB_IN = {
  680u,
  BRSHW_PORT_ALT_1};
#  endif /*BRS_ENABLE_TCM_EXT_IRQ*/

# else
  #error "TCM-Ports for your environment not yet configured within BrsHw_Ports.h. Configure them or disable BRS_ENABLE_TCM_SUPPORT."
# endif /*BRS_DERIVATIVE_x*/
#endif /*BRS_ENABLE_TCM_SUPPORT*/

/*******************************************************************************
  PIN configuration for alive LED support
********************************************************************************/
#if defined (BRS_ENABLE_SUPPORT_LEDS)
# if !defined (VGEN_ENABLE_DRVPORT)
#  if defined (BRS_EVA_BOARD_DEFAULT)
#   if (BRSHW_LED_PORT_NUMBER == 2)
const brsHw_Port_PortType BRSHW_PORT_LED = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_0};

#   elif (BRSHW_LED_PORT_NUMBER == 0)
const brsHw_Port_PortType BRSHW_PORT_LED = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_0};

#   elif (BRSHW_LED_PORT_NUMBER == 8)
const brsHw_Port_PortType BRSHW_PORT_LED = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_0};

#   elif (BRSHW_LED_PORT_NUMBER == 98)
const brsHw_Port_PortType BRSHW_PORT_LED = {
  BRSHW_PORT_PORTGROUP_G,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_0};

#   elif (BRSHW_LED_PORT_NUMBER == 114)
const brsHw_Port_PortType BRSHW_PORT_LED = {
  0u,
  BRSHW_PORT_ALT_0};

#   else
  #error "Your chosen BRSHW_LED_PORT_NUMBER (configured within BrsHw_DerivativeList.h) ist not yet supported for LED support DEFAULT. Feel free to add the support, or disable BRS LED support."
#   endif

#  elif defined (BRS_EVA_BOARD_SPC574Kx_144PIN)
const brsHw_Port_PortType BRSHW_PORT_LED = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_0};

#  elif defined (BRS_EVA_BOARD_VEBN01473) || \
        defined (BRS_EVA_BOARD_VEBN01655) || \
        defined (BRS_EVA_BOARD_HSR165)
const brsHw_Port_PortType BRSHW_PORT_LED = {
  0u,
  BRSHW_PORT_SIUL_B,
  BRSHW_PORT_ALT_1};

#  else
  #error "Your chosen EvaBoard ist not yet supported for LED support. Feel free to add your EvaBoard on top, or disable BRS LED support."
#  endif

# else
  #error "Configure the valid PortPin for the LED within your DrvPort config and uncomment this error. Or disable BRS_ENABLE_SUPPORT_LEDS."
# endif /*!VGEN_ENABLE_DRVPORT*/
#endif /*BRS_ENABLE_SUPPORT_LEDS*/

/*******************************************************************************
  PIN configuration for toggle WD pin support
********************************************************************************/
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_START_SEC_RAM_CONST
  #include "Brs_MemMap.h"   /* PRQA S 5087 *//* MD_MSR_19.1 */
# endif

  #error "Please configure here the needed WD-toggle pin and uncomment this error, or disable BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN"*/

const brsHw_Port_PortType BRSHW_PORT_TOGGLE_WD = {
  BRSHW_PORT_PORTGROUP_x,
  BRSHW_PORT_PORTNUMBER_x,
  BRSHW_PORT_ALT_x};

# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_STOP_SEC_RAM_CONST
  #include "Brs_MemMap.h"   /* PRQA S 5087 *//* MD_MSR_19.1 */
# endif
#endif /*BRS_ENABLE_SUPPORT_WD_PIN*/

/*******************************************************************************
  PIN configuration for toggle CUSTOM pin support
********************************************************************************/
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  #error "Please configure here the needed custom toggle pin and uncomment this error, or disable BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN"*/

const brsHw_Port_PortType BRSHW_PORT_TOGGLE_CUSTOM = {
  BRSHW_PORT_PORTGROUP_x,
  BRSHW_PORT_PORTNUMBER_x,
  BRSHW_PORT_ALT_x};
#endif /*BRS_ENABLE_SUPPORT_CUSTOM_PIN*/

/*******************************************************************************
  ------------------------------------------------------------
  COMMUNICATION DRIVER SPECIFIC PORT SETTINGS
  ------------------------------------------------------------
********************************************************************************/
/*******************************************************************************
  GENERAL COMMUNICATION DRIVER SPECIFIC SETTINGS
********************************************************************************/

#if defined (BRSHW_SIU_GROUP_A)
/*******************************************************************************
  CAN driver
********************************************************************************/
# if defined (VGEN_ENABLE_CAN_DRV)
#  if defined (BRS_EVA_BOARD_S32R274_257BALL)
#   if defined (kCanPhysToLogChannelIndex_0)
const brsHw_Port_PortType BRSHW_PORT_CAN0_TX = {
  BRSHW_PORT_PORTGROUP_B,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_1}; /*PB1 (mscr17)*/
const brsHw_Port_PortType BRSHW_PORT_CAN0_RX = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_15,
  BRSHW_PORT_ALT_0}; /*PA15 (mscr15)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN0_RX = {
  0u,
  BRSHW_PORT_ALT_1}; /*PA15 (imcr0)*/
#   endif /*kCanPhysToLogChannelIndex_0*/

#   if defined (kCanPhysToLogChannelIndex_1)
#    if defined (kCanPhysToLogChannelIndex_0)
       #error "FlexCan1 only usable if FlexCan0 is not used (FlexCan1.RX -> FlexCan0.TX!)"
#    endif
const brsHw_Port_PortType BRSHW_PORT_CAN1_TX = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_1}; /*PA14 (mscr14)*/
const brsHw_Port_PortType BRSHW_PORT_CAN1_RX = {
  BRSHW_PORT_PORTGROUP_B,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_0}; /*PB1 (mscr17)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN1_RX = {
  1u,
  BRSHW_PORT_ALT_1}; /*PB1 (imcr1)*/
#   endif /*kCanPhysToLogChannelIndex_1*/

#   if defined (kCanPhysToLogChannelIndex_2)
const brsHw_Port_PortType BRSHW_PORT_CAN2_TX = {
  BRSHW_PORT_PORTGROUP_I,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_1}; /*PI5 (mscr133)*/
const brsHw_Port_PortType BRSHW_PORT_CAN2_RX = {
  BRSHW_PORT_PORTGROUP_I,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_0}; /*PI6 (mscr134)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN2_RX = {
  2u,
  BRSHW_PORT_ALT_3}; /*PI6 (imcr2)*/
#   endif /*kCanPhysToLogChannelIndex_2*/

#   if defined (kCanPhysToLogChannelIndex_3)
  #error "Port config for these CAN channels not yet implemented!"
#   endif

#  else /*BRS_EVA_BOARD_x*/
#   if defined (kCanPhysToLogChannelIndex_0)
const brsHw_Port_PortType BRSHW_PORT_CAN0_TX = {
  BRSHW_PORT_PORTGROUP_B,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_1}; /*PB0 (mscr16)*/
const brsHw_Port_PortType BRSHW_PORT_CAN0_RX = {
  BRSHW_PORT_PORTGROUP_B,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_0}; /*PB1 (mscr17)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN0_RX = {
  0u,
  BRSHW_PORT_ALT_0}; /*PB1 (imcr0)*/
#   endif /*kCanPhysToLogChannelIndex_0*/

#   if defined (kCanPhysToLogChannelIndex_1)
  #error "As pdf-datasheet does not fit to attached excel-sheet, its not clear if imcr setting is correct" 
const brsHw_Port_PortType BRSHW_PORT_CAN1_TX = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_1}; /*PA14 (mscr14)*/
const brsHw_Port_PortType BRSHW_PORT_CAN1_RX = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_15,
  BRSHW_PORT_ALT_0}; /*PA15 (mscr15)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN1_RX = {
  1u,
  BRSHW_PORT_ALT_2}; /*PB1 (imcr1)*/
#   endif /*kCanPhysToLogChannelIndex_1*/

#   if defined (kCanPhysToLogChannelIndex_2)
const brsHw_Port_PortType BRSHW_PORT_CAN2_TX = {
  BRSHW_PORT_PORTGROUP_I,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_1}; /*PI5 (mscr133)*/
const brsHw_Port_PortType BRSHW_PORT_CAN2_RX = {
  BRSHW_PORT_PORTGROUP_I,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_0}; /*PI6 (mscr134)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN2_RX = {
  2u,
  BRSHW_PORT_ALT_3}; /*PI6 (imcr2)*/
#   endif /*kCanPhysToLogChannelIndex_2*/

#   if defined (kCanPhysToLogChannelIndex_3)
const brsHw_Port_PortType BRSHW_PORT_CAN3_TX = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_15,
  BRSHW_PORT_ALT_2}; /*PF15 (mscr95)*/
const brsHw_Port_PortType BRSHW_PORT_CAN3_RX = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_0}; /*PF14 (mscr94)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN3_RX = {
  3u,
  BRSHW_PORT_ALT_2}; /*PF14 (imcr3)*/
#   endif /*kCanPhysToLogChannelIndex_3*/
#  endif /*BRS_EVA_BOARD_x*/

#   if defined (kCan_30_McanPhysToLogChannelIndex_0)
const brsHw_Port_PortType BRSHW_PORT_CAN0_SECOND_CANCELL_TX = {
  BRSHW_PORT_PORTGROUP_D,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_ALT_5}; /*PD12 (mscr60)*/
const brsHw_Port_PortType BRSHW_PORT_CAN0_SECOND_CANCELL_RX = {
  BRSHW_PORT_PORTGROUP_D,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_0}; /*PD9 (mscr57)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN0_SECOND_CANCELL_RX = {
  92u,
  BRSHW_PORT_ALT_1}; /*PD9 (imcr92)*/
#   endif /*kCan_30_McanPhysToLogChannelIndex_0*/

#   if defined (kCan_30_McanPhysToLogChannelIndex_1)
const brsHw_Port_PortType BRSHW_PORT_CAN1_SECOND_CANCELL_TX = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_4}; /*PF14 (mscr94)*/
const brsHw_Port_PortType BRSHW_PORT_CAN1_SECOND_CANCELL_RX = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_15,
  BRSHW_PORT_ALT_0}; /*PF15 (mscr95)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN1_SECOND_CANCELL_RX = {
  92u,
  BRSHW_PORT_ALT_5}; /*PD9 (imcr3)*/
#   endif /*kCan_30_McanPhysToLogChannelIndex_1*/

#  if defined (kCanPhysToLogChannelIndex_4) || defined (kCan_30_McanPhysToLogChannelIndex_2)
  #error "Port config for these CAN channels not yet implemented!"
#  endif
# endif /*VGEN_ENABLE_CAN_DRV*/

/*******************************************************************************
  LIN driver
********************************************************************************/
# if defined (VGEN_ENABLE_LIN_DRV)
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
const brsHw_Port_PortType BRSHW_PORT_LIN0_TX = {
  BRSHW_PORT_PORTGROUP_B,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_1}; /*PB2 (mscr18)*/
const brsHw_Port_PortType BRSHW_PORT_LIN0_RX = {
  BRSHW_PORT_PORTGROUP_B,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_0}; /*PB3 (mscr19)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN0_RX = {
  62u,
  BRSHW_PORT_ALT_1}; /*PB3 (imcr62) LIN0_RX*/
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_0*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
const brsHw_Port_PortType BRSHW_PORT_LIN1_TX = {
  BRSHW_PORT_PORTGROUP_D,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_2}; /*PD9 (mscr57)*/
const brsHw_Port_PortType BRSHW_PORT_LIN1_RX = {
  BRSHW_PORT_PORTGROUP_D,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_ALT_0}; /*PD12 (mscr60)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN1_RX = {
  63u,
  BRSHW_PORT_ALT_2}; /*PE6 (imcr63) LIN1_RX*/
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_1*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_2)
const brsHw_Port_PortType BRSHW_PORT_LIN2_TX = {
  BRSHW_PORT_PORTGROUP_J,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_2}; /*PJ2 (mscr146)*/
const brsHw_Port_PortType BRSHW_PORT_LIN2_RX = {
  BRSHW_PORT_PORTGROUP_J,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_0}; /*PJ3 (mscr147)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN2_RX = {
  64u,
  BRSHW_PORT_ALT_2}; /*PJ3 (imcr64) LIN2_RX*/
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_2*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_3) || \
      defined (LIN_ENABLE_HARDWARE_INTERFACE_4)
  #error "Port config for these LIN channels not yet implemented!"
#  endif
# endif /*VGEN_ENABLE_LIN_DRV*/

/*******************************************************************************
  FLEXRAY driver
********************************************************************************/
# if defined (VGEN_ENABLE_DRVFR__BASEASR)
  /* ERAY-A */
const brsHw_Port_PortType BRSHW_PORT_FR0A_TX = {
  BRSHW_PORT_PORTGROUP_D,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_1}; /*PD0 (mscr48)*/
const brsHw_Port_PortType BRSHW_PORT_FR0A_RX = {
  BRSHW_PORT_PORTGROUP_D,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_0}; /*PD1 (mscr49)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_FR0A_RX = {
  136u,
  BRSHW_PORT_ALT_1}; /*PD1 (imcr136)*/
#define _BRSHW_PORT_FR0A_TXEN
const brsHw_Port_PortType BRSHW_PORT_FR0A_TXEN = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_15,
  BRSHW_PORT_ALT_1}; /*PC15 (mscr47)*/

  /* ERAY-B */
const brsHw_Port_PortType BRSHW_PORT_FR0B_TX = {
  BRSHW_PORT_PORTGROUP_D,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_1}; /*PD3 (mscr51)*/
const brsHw_Port_PortType BRSHW_PORT_FR0B_RX = {
  BRSHW_PORT_PORTGROUP_D,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_0}; /*PD2 (mscr50)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_FR0B_RX = {
  137u,
  BRSHW_PORT_ALT_1}; /*PD2 (imcr137)*/
#define _BRSHW_PORT_FR0B_TXEN
const brsHw_Port_PortType BRSHW_PORT_FR0B_TXEN = {
  BRSHW_PORT_PORTGROUP_D,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_1}; /*PD4 (mscr52)*/
# endif /*VGEN_ENABLE_DRVFR__BASEASR*/
#endif /*BRSHW_SIU_GROUP_A*/

#if defined (BRSHW_SIU_GROUP_B)
/*******************************************************************************
  CAN driver
********************************************************************************/
# if defined (VGEN_ENABLE_CAN_DRV)
#  if defined (kCanPhysToLogChannelIndex_3)
  #error "Please note, that the Wakeup interrupts for 0 and 1 can not be used, if FlexCan D is used. You can delete this error if this is no problem for you!"
#  else
#define _BRSHW_PORT_CAN_WAKEUP_IRQ_0
const brsHw_Port_PortType BRSHW_PORT_CAN_WAKEUP_IRQ_0 = { /* Configure port for IRQ[0] */
  193u,
  BRSHW_PORT_ALT_2}; /*(mscr193)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_0 = {
  3u,
  BRSHW_PORT_SIUL_MUXSEL_0,
  BRSHW_PORT_ALT_0};
#define _BRSHW_PORT_CAN_WAKEUP_IRQ_1
const brsHw_Port_PortType BRSHW_PORT_CAN_WAKEUP_IRQ_1 = { /* Configure port for IRQ[1] */
  194u,
  BRSHW_PORT_ALT_2}; /*(mscr193)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_1 = {
  1u,
  BRSHW_PORT_SIUL_MUXSEL_5,
  BRSHW_PORT_ALT_1};
#  endif /*else kCanPhysToLogChannelIndex_3*/
#define _BRSHW_PORT_CAN_WAKEUP_IRQ_2
const brsHw_Port_PortType BRSHW_PORT_CAN_WAKEUP_IRQ_2 = { /* Configure port for IRQ[2] */
  211u,
  BRSHW_PORT_ALT_2}; /*(mscr211)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_2 = {
  3u,
  BRSHW_PORT_SIUL_MUXSEL_2,
  BRSHW_PORT_ALT_0};
#define _BRSHW_PORT_CAN_WAKEUP_IRQ_3
const brsHw_Port_PortType BRSHW_PORT_CAN_WAKEUP_IRQ_3 = { /* Configure port for IRQ[3] */
  212u,
  BRSHW_PORT_ALT_2}; /*(mscr212)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_3 = {
  3u,
  BRSHW_PORT_SIUL_MUXSEL_3,
  BRSHW_PORT_ALT_0};
#define _BRSHW_PORT_CAN_WAKEUP_IRQ_4
const brsHw_Port_PortType BRSHW_PORT_CAN_WAKEUP_IRQ_4 = { /* Configure port for IRQ[4] */
  208u,
  BRSHW_PORT_ALT_2}; /*(mscr208)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_4 = {
  3u,
  BRSHW_PORT_SIUL_MUXSEL_4,
  BRSHW_PORT_ALT_0};
#define _BRSHW_PORT_CAN_WAKEUP_IRQ_5
const brsHw_Port_PortType BRSHW_PORT_CAN_WAKEUP_IRQ_5 = { /* Configure port for IRQ[5] */
  209u,
  BRSHW_PORT_ALT_2}; /*(mscr209)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_5 = {
  3u,
  BRSHW_PORT_SIUL_MUXSEL_5,
  BRSHW_PORT_ALT_0};
#define _BRSHW_PORT_CAN_WAKEUP_IRQ_6
const brsHw_Port_PortType BRSHW_PORT_CAN_WAKEUP_IRQ_6 = { /* Configure port for IRQ[6] */
  146u,
  BRSHW_PORT_ALT_2}; /*(mscr146)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_6 = {
  3u,
  BRSHW_PORT_SIUL_MUXSEL_6,
  BRSHW_PORT_ALT_0};
#define _BRSHW_PORT_CAN_WAKEUP_IRQ_7
const brsHw_Port_PortType BRSHW_PORT_CAN_WAKEUP_IRQ_7 = { /* Configure port for IRQ[7] */
  113u,
  BRSHW_PORT_ALT_2}; /*(mscr113)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_7 = {
  3u,
  BRSHW_PORT_SIUL_MUXSEL_6,
  BRSHW_PORT_ALT_0};

#  if defined (BRSHW_USED_CANCELL_DEFAULT)
#   if defined (kCanPhysToLogChannelIndex_0)
const brsHw_Port_PortType BRSHW_PORT_CAN0_TX = { /* TX, PC[9] (P10[9] on Freescale MPC57xx EvaBoard) */
  83u,
  BRSHW_PORT_ALT_1}; /*(mscr83)*/
const brsHw_Port_PortType BRSHW_PORT_CAN0_RX = { /* RX, PC[8] (P10[8] on Freescale MPC57xx EvaBoard) */
  84u,
  BRSHW_PORT_ALT_1}; /*(mscr84)*/
#define BRSHW_PORT_MUX_CAN0_RX BRSHW_PORT_MUX_EMPTY_DUMMY
#   endif /*kCanPhysToLogChannelIndex_0*/

#   if defined (kCanPhysToLogChannelIndex_1)
const brsHw_Port_PortType BRSHW_PORT_CAN1_TX = { /* TX, PA[10] (P8[10] on Freescale MPC57xx EvaBoard) */
  85u,
  BRSHW_PORT_ALT_1}; /*(mscr85)*/
const brsHw_Port_PortType BRSHW_PORT_CAN1_RX = { /* RX, PA[11] (P8[11] on Freescale MPC57xx EvaBoard) */
  86u,
  BRSHW_PORT_ALT_1}; /*(mscr86)*/
#define BRSHW_PORT_MUX_CAN1_RX BRSHW_PORT_MUX_EMPTY_DUMMY
#   endif /*kCanPhysToLogChannelIndex_1*/

#   if defined (kCanPhysToLogChannelIndex_2)
const brsHw_Port_PortType BRSHW_PORT_CAN2_TX = { /* TX, PG[5] (P14[5] on Freescale MPC57xx EvaBoard) */
  87u,
  BRSHW_PORT_ALT_1}; /*(mscr87)*/
const brsHw_Port_PortType BRSHW_PORT_CAN2_RX = { /* RX, PG[7] (P14[7] on Freescale MPC57xx EvaBoard) */
  88u,
  BRSHW_PORT_ALT_1}; /*(mscr88)*/
#define BRSHW_PORT_MUX_CAN2_RX BRSHW_PORT_MUX_EMPTY_DUMMY
#   endif /*kCanPhysToLogChannelIndex_2*/

#   if defined (kCanPhysToLogChannelIndex_3)
const brsHw_Port_PortType BRSHW_PORT_CAN3_TX = { /* TX, PE[5] (P12[5] on Freescale MPC57xx EvaBoard) */
  246u,
  BRSHW_PORT_ALT_1}; /*(mscr246)*/
const brsHw_Port_PortType BRSHW_PORT_CAN3_RX = { /* RX, PG[14] (P14[14] on Freescale MPC57xx EvaBoard) */
  247u,
  BRSHW_PORT_ALT_1}; /*(mscr247)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN3_RX = {
  1u,
  BRSHW_PORT_SIUL_MUXSEL_5,
  BRSHW_PORT_ALT_0};
#   endif /*kCanPhysToLogChannelIndex_3*/

#   if defined (kCanPhysToLogChannelIndex_4)
const brsHw_Port_PortType BRSHW_PORT_CAN4_TX = { /*TX*/
  201u,
  BRSHW_PORT_ALT_3}; /*(mscr201)*/
const brsHw_Port_PortType BRSHW_PORT_CAN4_RX = { /*RX*/
  202u,
  BRSHW_PORT_ALT_3}; /*(mscr202)*/
#define BRSHW_PORT_MUX_CAN4_RX BRSHW_PORT_MUX_EMPTY_DUMMY
#   endif /*kCanPhysToLogChannelIndex_4*/
#  endif /*BRSHW_USED_CANCELL_DEFAULT*/

#  if defined (BRSHW_USED_CANCELL_MCAN)
#   if defined (kCan_30_McanPhysToLogChannelIndex_0)
const brsHw_Port_PortType BRSHW_PORT_CAN0_SECOND_CANCELL_TX = {  /* MCAN0TX, PC[9] (P10[9] on Freescale MPC57xx EvaBoard) */
  83u,
  BRSHW_PORT_ALT_3}; /*(mscr83)*/
const brsHw_Port_PortType BRSHW_PORT_CAN0_SECOND_CANCELL_RX = { /* MCAN0RX, PC[8] (P10[8] on Freescale MPC57xx EvaBoard) */
  84u,
  BRSHW_PORT_ALT_3}; /*(mscr84)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN0_SECOND_CANCELL_RX = {
  1u,
  BRSHW_PORT_SIUL_MUXSEL_0,
  BRSHW_PORT_ALT_1};
#   endif /*kCanPhysToLogChannelIndex_0*/

#   if defined (kCan_30_McanPhysToLogChannelIndex_1)
const brsHw_Port_PortType BRSHW_PORT_CAN1_SECOND_CANCELL_TX = { /* MCAN1TX, PE[5] (P12[5] on Freescale MPC57xx EvaBoard) */
  246u,
  BRSHW_PORT_ALT_3}; /*(mscr246)*/
const brsHw_Port_PortType BRSHW_PORT_CAN1_SECOND_CANCELL_RX = { /* MCAN1RX, PG[14] (P14[14] on Freescale MPC57xx EvaBoard) */
  247u,
  BRSHW_PORT_ALT_3}; /*(mscr247)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN1_SECOND_CANCELL_RX = {
  1u,
  BRSHW_PORT_SIUL_MUXSEL_1,
  BRSHW_PORT_ALT_1};
#   endif /*kCanPhysToLogChannelIndex_1*/
#  endif /*BRSHW_USED_CANCELL_MCAN*/

#  if defined (kCanPhysToLogChannelIndex_2) || defined (kCanPhysToLogChannelIndex_3) || \
      defined (kCanPhysToLogChannelIndex_4) || defined (kCan_30_McanPhysToLogChannelIndex_2)
  #error "Port config for these CAN channels not yet implemented!"
#  endif

# endif /*VGEN_ENABLE_CAN_DRV*/

/*******************************************************************************
  LIN driver
********************************************************************************/
# if defined (VGEN_ENABLE_LIN_DRV)
#define _BRSHW_PORT_CONF_LIN
const brsHw_Port_ConfType BRSHW_PORT_CONF_LIN = {
  PORT_PULL_UP_ENABLED};

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
const brsHw_Port_PortType BRSHW_PORT_LIN0_TX = {
  89u,
  BRSHW_PORT_ALT_1}; /*(mscr89)*/
const brsHw_Port_PortType BRSHW_PORT_LIN0_RX = {
  90u,
  BRSHW_PORT_ALT_1}; /*(mscr90)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN0_RX = {
  4u,
  BRSHW_PORT_SIUL_MUXSEL_1,
  BRSHW_PORT_ALT_0};
#  endif

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
const brsHw_Port_PortType BRSHW_PORT_LIN1_TX = {
  91u,
  BRSHW_PORT_ALT_1}; /*(mscr91)*/
const brsHw_Port_PortType BRSHW_PORT_LIN1_RX = {
  92u,
  BRSHW_PORT_ALT_1}; /*(mscr92)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN1_RX = {
  4u,
  BRSHW_PORT_SIUL_MUXSEL_2,
  BRSHW_PORT_ALT_0};
#  endif

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_2)
const brsHw_Port_PortType BRSHW_PORT_LIN2_TX = {
  244u,
  BRSHW_PORT_ALT_1}; /*(mscr244)*/
const brsHw_Port_PortType BRSHW_PORT_LIN2_RX = {
  245u,
  BRSHW_PORT_ALT_1}; /*(mscr245)*/
#define BRSHW_PORT_MUX_LIN2_RX BRSHW_PORT_MUX_EMPTY_DUMMY
#  endif

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_3)
const brsHw_Port_PortType BRSHW_PORT_LIN3_TX = {
  99u,
  BRSHW_PORT_ALT_4}; /*(mscr99)*/
const brsHw_Port_PortType BRSHW_PORT_LIN3_RX = {
  101u,
  BRSHW_PORT_ALT_3}; /*(mscr101)*/
#define BRSHW_PORT_MUX_LIN3_RX BRSHW_PORT_MUX_EMPTY_DUMMY
#  endif

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_4)
const brsHw_Port_PortType BRSHW_PORT_LIN4_TX = {
  100u,
  BRSHW_PORT_ALT_3}; /*(mscr100)*/
const brsHw_Port_PortType BRSHW_PORT_LIN4_RX = {
  88u,
  BRSHW_PORT_ALT_3}; /*(mscr88)*/
#define BRSHW_PORT_MUX_LIN4_RX BRSHW_PORT_MUX_EMPTY_DUMMY
#  endif

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_5)
const brsHw_Port_PortType BRSHW_PORT_LIN5_TX = {
  458u,
  BRSHW_PORT_ALT_2}; /*(mscr100)*/
const brsHw_Port_PortType BRSHW_PORT_LIN5_RX = {
  458u,
  BRSHW_PORT_ALT_2}; /*(mscr88)*/
#define BRSHW_PORT_MUX_LIN4_RX BRSHW_PORT_MUX_EMPTY_DUMMY
#  endif
# endif /*VGEN_ENABLE_LIN_DRV*/

/*******************************************************************************
  FLEXRAY driver
********************************************************************************/
# if defined (VGEN_ENABLE_DRVFR__BASEASR)
  #error "Flexray for this SIU Group not yet supported!"
# endif
#endif /*BRSHW_SIU_GROUP_B*/

#if defined (BRSHW_SIU_GROUP_C)
/*******************************************************************************
  CAN driver
********************************************************************************/
# if defined (VGEN_ENABLE_CAN_DRV)
#  if defined (kCanPhysToLogChannelIndex_0)
const brsHw_Port_PortType BRSHW_PORT_CAN0_TX = {
  BRSHW_PORT_PORTGROUP_E,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_1}; /*PE5 (mscr69)*/
const brsHw_Port_PortType BRSHW_PORT_CAN0_RX = {
  BRSHW_PORT_PORTGROUP_G,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_0}; /*PG14 (mscr110)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN0_RX = {
  752u,
  BRSHW_PORT_ALT_2}; /*PG14 (mscr752)*/
#  endif /*kCanPhysToLogChannelIndex_0*/

#  if defined (kCanPhysToLogChannelIndex_1)
const brsHw_Port_PortType BRSHW_PORT_CAN1_TX = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_1}; /*PA10 (mscr10)*/
const brsHw_Port_PortType BRSHW_PORT_CAN1_RX = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_ALT_0}; /*PA11 (mscr11)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN1_RX = {
  758u,
  BRSHW_PORT_ALT_2}; /*PA11 (mscr758)*/
#  endif /*kCanPhysToLogChannelIndex_1*/

#  if defined (kCanPhysToLogChannelIndex_2)
const brsHw_Port_PortType BRSHW_PORT_CAN2_TX = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_1}; /*PC9 (mscr41)*/
const brsHw_Port_PortType BRSHW_PORT_CAN2_RX = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_0}; /*PC8 (mscr40)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN2_RX = {
  759u,
  BRSHW_PORT_ALT_3}; /*PC8 (mscr759)*/
#  endif /*kCanPhysToLogChannelIndex_2*/

#  if defined (kCanPhysToLogChannelIndex_3)
const brsHw_Port_PortType BRSHW_PORT_CAN3_TX = {
  BRSHW_PORT_PORTGROUP_J,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_1}; /*PJ1 (mscr145)*/
const brsHw_Port_PortType BRSHW_PORT_CAN3_RX = {
  BRSHW_PORT_PORTGROUP_J,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_0}; /*PJ0 (mscr144)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN3_RX = {
  760u,
  BRSHW_PORT_ALT_2}; /*PJ0 (mscr760)*/
#  endif /*kCanPhysToLogChannelIndex_3*/
# endif /*VGEN_ENABLE_CAN_DRV*/

/*******************************************************************************
  LIN driver
********************************************************************************/
# if defined (VGEN_ENABLE_LIN_DRV)
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
const brsHw_Port_PortType BRSHW_PORT_LIN0_TX = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_ALT_2}; /*PA12 (mscr12)*/
const brsHw_Port_PortType BRSHW_PORT_LIN0_RX = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_ALT_0}; /*PC11 (mscr59)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN0_RX = {
  848u,
  BRSHW_PORT_ALT_4}; /*PC11 (mscr848) LIN0_RX*/
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_0*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
const brsHw_Port_PortType BRSHW_PORT_LIN1_TX = {
  BRSHW_PORT_PORTGROUP_E,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_2}; /*PE7 (mscr71)*/
const brsHw_Port_PortType BRSHW_PORT_LIN1_RX = {
  BRSHW_PORT_PORTGROUP_E,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_0}; /*PE6 (mscr70)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN1_RX = {
  849u,
  BRSHW_PORT_ALT_1}; /*PE6 (mscr849) LIN1_RX*/
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_1*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_2)
const brsHw_Port_PortType BRSHW_PORT_LIN2_TX = {
  BRSHW_PORT_PORTGROUP_D,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_2}; /*PD14 (mscr62)*/
const brsHw_Port_PortType BRSHW_PORT_LIN2_RX = {
  BRSHW_PORT_PORTGROUP_D,
  BRSHW_PORT_PORTNUMBER_15,
  BRSHW_PORT_ALT_0}; /*PD15 (mscr63) */
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN2_RX = {
  850u,
  BRSHW_PORT_ALT_1}; /*PD15 (mscr850) LIN2_RX*/
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_2*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_14)
const brsHw_Port_PortType BRSHW_PORT_LIN14_TX = {
  BRSHW_PORT_PORTGROUP_E,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_ALT_2}; /*PE11 (mscr75)*/
const brsHw_Port_PortType BRSHW_PORT_LIN14_RX = {
  BRSHW_PORT_PORTGROUP_E,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_0}; /*PE10 (mscr74)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN14_RX = {
  862u,
  BRSHW_PORT_ALT_1}; /*PE10 (mscr862) LIN14_RX*/
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_14*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_15)
const brsHw_Port_PortType BRSHW_PORT_LIN15_TX = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_2}; /*PC9 (mscr41)*/
const brsHw_Port_PortType BRSHW_PORT_LIN15_RX = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_0}; /*PC8 (mscr40)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN15_RX = {
  863u,
  BRSHW_PORT_ALT_1}; /*PC8 (mscr863) LIN15_RX*/
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_15*/
# endif /*VGEN_ENABLE_LIN_DRV*/

/*******************************************************************************
  FLEXRAY driver
********************************************************************************/
# if defined (VGEN_ENABLE_DRVFR__BASEASR)
  /* ERAY-A */
const brsHw_Port_PortType BRSHW_PORT_FR0A_TX = {
  BRSHW_PORT_PORTGROUP_H,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_5}; /*PH7 (mscr119)*/
const brsHw_Port_PortType BRSHW_PORT_FR0A_RX = {
  BRSHW_PORT_PORTGROUP_H,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_FR0A_RX = {
  772u,
  BRSHW_PORT_ALT_3}; /*PH9 (mscr772)*/
#define _BRSHW_PORT_FR0A_TXEN
const brsHw_Port_PortType BRSHW_PORT_FR0A_TXEN = {
  BRSHW_PORT_PORTGROUP_H,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_5}; /*PH8 (mscr120)*/
# endif /*VGEN_ENABLE_DRVFR__BASEASR*/
#endif /*BRSHW_SIU_GROUP_C*/

#if defined (BRSHW_SIU_GROUP_D_1)
/*******************************************************************************
  CAN driver
********************************************************************************/
# if defined (VGEN_ENABLE_CAN_DRV)
#  if defined (kCanPhysToLogChannelIndex_0) /*SIUL2_A*/
const brsHw_Port_PortType BRSHW_PORT_CAN0_TX = {
  46u,
  BRSHW_PORT_SIUL_A,
  BRSHW_PORT_ALT_1}; /*(mscr46)*/
const brsHw_Port_PortType BRSHW_PORT_CAN0_RX = {
  47u,
  BRSHW_PORT_SIUL_A,
  BRSHW_PORT_ALT_1}; /*(mscr47)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN0_RX = {
  47u,
  BRSHW_PORT_ALT_1}; /*(mscr47)*/
#  endif /*kCanPhysToLogChannelIndex_0*/
# endif /*VGEN_ENABLE_CAN_DRV*/
/* all other pin settings are done within SIUL2_B part (BRSHW_SIU_GROUP_D_2) */
#endif /*BRSHW_SIU_GROUP_D_1*/

#if defined (BRSHW_SIU_GROUP_D_2)
/*******************************************************************************
  CAN driver
********************************************************************************/
# if defined (VGEN_ENABLE_CAN_DRV)
  /* kCanPhysToLogChannelIndex_0 settings are done within SIUL2_A part */
#  if defined (kCanPhysToLogChannelIndex_1)  /*SIUL2_B*/
const brsHw_Port_PortType BRSHW_PORT_CAN1_TX = {
  32u,
  BRSHW_PORT_SIUL_B,
  BRSHW_PORT_ALT_1}; /*(mscr32)*/
const brsHw_Port_PortType BRSHW_PORT_CAN1_RX = {
  33u,
  BRSHW_PORT_SIUL_B,
  BRSHW_PORT_ALT_1}; /*(mscr33)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN1_RX = {
  33u,
  BRSHW_PORT_ALT_1}; /*(mscr33)*/
#  endif /*kCanPhysToLogChannelIndex_1*/

#  if defined (kCanPhysToLogChannelIndex_2) || defined (kCanPhysToLogChannelIndex_3) || \
      defined (kCanPhysToLogChannelIndex_4)
  #error "Port config for these CAN channels not yet implemented!"
#  endif
# endif /*VGEN_ENABLE_CAN_DRV*/

/*******************************************************************************
  FLEXRAY driver
********************************************************************************/
# if defined (VGEN_ENABLE_DRVFR__BASEASR)
const brsHw_Port_PortType BRSHW_PORT_FR0A_TX = {
  43u,
  BRSHW_PORT_SIUL_B,
  BRSHW_PORT_ALT_1};
const brsHw_Port_PortType BRSHW_PORT_FR0A_RX = {
  44u,
  BRSHW_PORT_SIUL_B,
  BRSHW_PORT_ALT_1};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_FR0A_RX = {
  44u,
  BRSHW_PORT_ALT_1}; /*(mscr44)*/
#define _BRSHW_PORT_FR0A_TXEN
const brsHw_Port_PortType BRSHW_PORT_FR0A_TXEN = {
  45u,
  BRSHW_PORT_SIUL_B,
  BRSHW_PORT_ALT_1};
# endif /*VGEN_ENABLE_DRVFR__BASEASR*/

# if defined (BRS_EVA_BOARD_VEBN01357)
#  if defined (VGEN_ENABLE_LIN_DRV)
  #error "The following lines of code were active in old BRS code. Not sure if this is still needed (board manual seems to not fit)"
  ///* disable input hysteresis for GIPOA[106] - this is necessary to get LINFlex_A1_RXD to work */
  //(*(volatile uint32*) (  0xFFFA4000 + 0x240 + (4*106))) = 0x30080002;
  ///* disable input hysteresis for GIPOA[105] - this is necessary to get LINFlex_A2_RXD to work */
  //(*(volatile uint32*) (  0xFFFA4000 + 0x240 + (4*105))) = 0x30080002;
#  endif /*VGEN_ENABLE_LIN_DRV*/

#  if defined(VGEN_ENABLE_DRVFR__BASEASR)
  #error "The following lines of code were active in old BRS code. Not sure if this is still needed (board manual seems to not fit)"
  ///* Configure FlexRay Transceiver */
  ///* set GPIO8 as output -> EN_FR_A */
  //SIU_MSCR(8) = BRSHW_PCR_PIN_ASSIGNMENT_GPIO_OUTPUT;
  //SIU_GPDO(8) |= 0x01;
  ///* set GPIO10 as output -> WU_FR_A */
  //SIU_MSCR(10) = BRSHW_PCR_PIN_ASSIGNMENT_GPIO_OUTPUT;
  //SIU_GPDO(10) |= 0x01;
  ///* set GPIO26 as output -> FR_BGE */
  //SIU_MSCR(26) = BRSHW_PCR_PIN_ASSIGNMENT_GPIO_OUTPUT;
  //SIU_GPDO(26) |= 0x01;
#  endif /*VGEN_ENABLE_DRVFR__BASEASR*/
# endif /*BRS_EVA_BOARD_VEBN01357*/
#endif /*BRSHW_SIU_GROUP_D_2*/

#if defined (BRSHW_SIU_GROUP_E)
/*******************************************************************************
  CAN driver
********************************************************************************/
# if defined (VGEN_ENABLE_CAN_DRV)
/* Set ports of external interrupts 4, 10, 15 as input (Currently used as external CAN Wakeup source) */
#define _BRSHW_PORT_CAN_WAKEUP_IRQ_4
const brsHw_Port_PortType BRSHW_PORT_CAN_WAKEUP_IRQ_4 = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_4 = {
  660u,
  BRSHW_PORT_ALT_1};
#define _BRSHW_PORT_CAN_WAKEUP_IRQ_10
const brsHw_Port_PortType BRSHW_PORT_CAN_WAKEUP_IRQ_10 = {
  BRSHW_PORT_PORTGROUP_E,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_10 = {
  666u,
  BRSHW_PORT_ALT_1};
#define _BRSHW_PORT_CAN_WAKEUP_IRQ_15
  const brsHw_Port_PortType BRSHW_PORT_CAN_WAKEUP_IRQ_15 = {
  BRSHW_PORT_PORTGROUP_G,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN_WAKEUP_IRQ_15 = {
  671u,
  BRSHW_PORT_ALT_1};

#  if defined (kCanPhysToLogChannelIndex_0)
const brsHw_Port_PortType BRSHW_PORT_CAN0_TX = {
  BRSHW_PORT_PORTGROUP_B,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_1}; /*PB0 (mscr16)*/
const brsHw_Port_PortType BRSHW_PORT_CAN0_RX = {
  BRSHW_PORT_PORTGROUP_B,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_0}; /*PB1 (mscr17)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN0_RX = {
  700u,
  BRSHW_PORT_ALT_2}; /*PB1 (mscr700)*/
#   if defined (BRS_EVA_BOARD_VEBN01335)
#define _BRSHW_PORT_CAN0_TRCV_STB
const brsHw_Port_PortType BRSHW_PORT_CAN0_TRCV_STB = {
  BRSHW_PORT_PORTGROUP_E,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_0}; /*PE9 (mscr73)*/
#define _BRSHW_PORT_CAN0_TRCV_EN
const brsHw_Port_PortType BRSHW_PORT_CAN0_TRCV_EN = {
  BRSHW_PORT_PORTGROUP_G,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_0}; /*PG6 (mscr102)*/
#   endif
#  endif /*kCanPhysToLogChannelIndex_0*/

#  if defined (kCanPhysToLogChannelIndex_1)
#   if defined (BRS_EVA_BOARD_VEBN01335)
const brsHw_Port_PortType BRSHW_PORT_CAN1_TX = {
  BRSHW_PORT_PORTGROUP_J,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_1}; /*PJ14 (mscr158)*/
const brsHw_Port_PortType BRSHW_PORT_CAN1_RX = {
  BRSHW_PORT_PORTGROUP_J,
  BRSHW_PORT_PORTNUMBER_15,
  BRSHW_PORT_ALT_0}; /*PJ15 (mscr159)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN1_RX = {
  701u,
  BRSHW_PORT_ALT_6}; /*PJ15 (mscr701) MCAN_1_RX*/
#define _BRSHW_PORT_CAN1_TRCV_STB
const brsHw_Port_PortType BRSHW_PORT_CAN1_TRCV_STB = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_0}; /*PF10 (mscr90)*/
#define _BRSHW_PORT_CAN1_TRCV_EN
const brsHw_Port_PortType BRSHW_PORT_CAN1_TRCV_EN = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_ALT_0}; /*PF12 (mscr92)*/

#   else
const brsHw_Port_PortType BRSHW_PORT_CAN1_TX = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_1}; /*PC10 (mscr42)*/
const brsHw_Port_PortType BRSHW_PORT_CAN1_RX = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_ALT_0}; /*PC11 (mscr43)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN1_RX = {
  701u,
  BRSHW_PORT_ALT_3}; /*PC11 (mscr701) MCAN_1_RX*/
#   endif /*else BRS_EVA_BOARD_VEBN01335*/
#  endif /*kCanPhysToLogChannelIndex_1*/

#  if defined (kCanPhysToLogChannelIndex_2)
const brsHw_Port_PortType BRSHW_PORT_CAN2_TX = {
  BRSHW_PORT_PORTGROUP_E,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_1}; /*PE8 (mscr72)*/
const brsHw_Port_PortType BRSHW_PORT_CAN2_RX = {
  BRSHW_PORT_PORTGROUP_E,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_0}; /*PE9 (mscr73)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN2_RX = {
  702u,
  BRSHW_PORT_ALT_1}; /*PE9 (mscr702)*/
#  endif /*kCanPhysToLogChannelIndex_2*/

#  if defined (kCanPhysToLogChannelIndex_3)
const brsHw_Port_PortType BRSHW_PORT_CAN3_TX = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_1}; /*PF8 (mscr88)*/
const brsHw_Port_PortType BRSHW_PORT_CAN3_RX = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_0}; /*PF9 (mscr89)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN3_RX = {
  703u,
  BRSHW_PORT_ALT_4}; /*PF9 (mscr703)*/
#  endif /*kCanPhysToLogChannelIndex_3*/

#  if defined (kCanPhysToLogChannelIndex_4)
const brsHw_Port_PortType BRSHW_PORT_CAN4_TX = {
  BRSHW_PORT_PORTGROUP_J,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_2}; /*PJ9 (mscr153)*/
const brsHw_Port_PortType BRSHW_PORT_CAN4_RX = {
  BRSHW_PORT_PORTGROUP_J,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_0}; /*PJ10 (mscr154)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN4_RX = {
  704u,
  BRSHW_PORT_ALT_4}; /*PJ10 (mscr704)*/
#  endif /*kCanPhysToLogChannelIndex_4*/

#  if defined (kCanPhysToLogChannelIndex_5)
const brsHw_Port_PortType BRSHW_PORT_CAN5_TX = {
  BRSHW_PORT_PORTGROUP_K,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_1}; /*PK4 (mscr164)*/
const brsHw_Port_PortType BRSHW_PORT_CAN5_RX = {
  BRSHW_PORT_PORTGROUP_K,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_0}; /*PK3 (mscr163)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN5_RX = {
  705u,
  BRSHW_PORT_ALT_3}; /*PK3 (mscr705)*/
#  endif /*kCanPhysToLogChannelIndex_5*/

#  if defined (kCanPhysToLogChannelIndex_6)
const brsHw_Port_PortType BRSHW_PORT_CAN6_TX = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_4}; /*PF0 (mscr80)*/
const brsHw_Port_PortType BRSHW_PORT_CAN6_RX = {
  BRSHW_PORT_PORTGROUP_B,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_0}; /*PB10 (mscr26)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN6_RX = {
  706u,
  BRSHW_PORT_ALT_1}; /*PB10 (mscr706)*/
#  endif /*kCanPhysToLogChannelIndex_6*/

#  if defined (kCanPhysToLogChannelIndex_7)
const brsHw_Port_PortType BRSHW_PORT_CAN7_TX = {
  BRSHW_PORT_PORTGROUP_G,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_3}; /*PG2 (mscr98)*/
const brsHw_Port_PortType BRSHW_PORT_CAN7_RX = {
  BRSHW_PORT_PORTGROUP_G,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_0}; /*PG3 (mscr99)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN7_RX = {
  707u,
  BRSHW_PORT_ALT_1}; /*PB1 (mscr707)*/
#  endif /*kCanPhysToLogChannelIndex_7*/
# endif /*VGEN_ENABLE_CAN_DRV*/

/*******************************************************************************
  LIN driver
********************************************************************************/
# if defined (VGEN_ENABLE_LIN_DRV)
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
const brsHw_Port_PortType BRSHW_PORT_LIN0_TX = {
  BRSHW_PORT_PORTGROUP_B,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_1}; /*PB2 (mscr18)*/
const brsHw_Port_PortType BRSHW_PORT_LIN0_RX = {
  BRSHW_PORT_PORTGROUP_B,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_0}; /*PB3 (mscr19)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN0_RX = {
  712u,
  BRSHW_PORT_ALT_2}; /*PB3 (mscr712) LIN0_RX*/
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_0*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
const brsHw_Port_PortType BRSHW_PORT_LIN1_TX = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_1}; /*PC6 (mscr38)*/
const brsHw_Port_PortType BRSHW_PORT_LIN1_RX = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_0}; /*PC7 (mscr39)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN1_RX = {
  713u,
  BRSHW_PORT_ALT_1}; /*PC7 (mscr 713) LIN1_RX*/
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_1*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_2)
const brsHw_Port_PortType BRSHW_PORT_LIN2_TX = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_1}; /*PC8 (mscr40)*/
const brsHw_Port_PortType BRSHW_PORT_LIN2_RX = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_0}; /*PC9 (mscr41)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN2_RX = {
  714u,
  BRSHW_PORT_ALT_2}; /*PC9 (mscr714) LIN2_RX*/
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_2*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_3)
const brsHw_Port_PortType BRSHW_PORT_LIN3_TX = {
  BRSHW_PORT_PORTGROUP_E,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_1}; /*PE10 (mscr74)*/
const brsHw_Port_PortType BRSHW_PORT_LIN3_RX = {
  BRSHW_PORT_PORTGROUP_E,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_ALT_0}; /*PE11 (mscr75)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN3_RX = {
  715u,
  BRSHW_PORT_ALT_2}; /*PE11 (mscr715) LIN3_RX*/
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_3*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_4)
const brsHw_Port_PortType BRSHW_PORT_LIN4_TX = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_2}; /*PF10 (mscr90)*/
const brsHw_Port_PortType BRSHW_PORT_LIN4_RX = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_ALT_0}; /*PF11 (mscr91)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN4_RX = {
  716u,
  BRSHW_PORT_ALT_2}; /*PF11 (mscr716) LIN4_RX*/
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_4*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_5)
const brsHw_Port_PortType BRSHW_PORT_LIN5_TX = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_ALT_2}; /*PF12 (mscr92)*/
const brsHw_Port_PortType BRSHW_PORT_LIN5_RX = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_ALT_0}; /*PF13 (9)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN5_RX = {
  717u,
  BRSHW_PORT_ALT_2}; /*PF13 (mscr717) LIN5_RX*/
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_5*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_6)
const brsHw_Port_PortType BRSHW_PORT_LIN6_TX = {
  BRSHW_PORT_PORTGROUP_G,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_2}; /*PG6 (mscr102)*/
const brsHw_Port_PortType BRSHW_PORT_LIN6_RX = {
  BRSHW_PORT_PORTGROUP_G,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_0}; /*PG7 (mscr103)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN6_RX = {
  718u,
  BRSHW_PORT_ALT_1}; /*PG7 (mscr718) LIN6_RX*/
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_6*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_7)
const brsHw_Port_PortType BRSHW_PORT_LIN7_TX = {
  BRSHW_PORT_PORTGROUP_G,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_2}; /*PG8 (mscr104)*/
const brsHw_Port_PortType BRSHW_PORT_LIN7_RX = {
  BRSHW_PORT_PORTGROUP_G,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_0}; /*PG9 (mscr105)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN7_RX = {
  719u,
  BRSHW_PORT_ALT_1}; /*PG9 (mscr719) LIN7_RX*/
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_7*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_8)
const brsHw_Port_PortType BRSHW_PORT_LIN8_TX = {
  BRSHW_PORT_PORTGROUP_G,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_2}; /*PG14 (mscr110)*/
const brsHw_Port_PortType BRSHW_PORT_LIN8_RX = {
  BRSHW_PORT_PORTGROUP_G,
  BRSHW_PORT_PORTNUMBER_15,
  BRSHW_PORT_ALT_0}; /*PG15 (mscr111)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN8_RX = {
  720u,
  BRSHW_PORT_ALT_1}; /*PG15 (mscr720) LIN8_RX*/
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_8*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_9)
const brsHw_Port_PortType BRSHW_PORT_LIN9_TX = {
  BRSHW_PORT_PORTGROUP_I,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_2}; /*PI2 (mscr130)*/
const brsHw_Port_PortType BRSHW_PORT_LIN9_RX = {
  BRSHW_PORT_PORTGROUP_I,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_0}; /*PI3 (mscr131)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN9_RX = {
  721u,
  BRSHW_PORT_ALT_1}; /*PI3 (mscr721) LIN9_RX*/
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_9*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_10)
  #error "Port config for these LIN channels not yet implemented!"
#  endif
# endif /*VGEN_ENABLE_LIN_DRV*/
/*******************************************************************************
  FLEXRAY driver
********************************************************************************/
# if defined (VGEN_ENABLE_DRVFR__BASEASR)
const brsHw_Port_PortType BRSHW_PORT_FR0A_TX = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_4};
const brsHw_Port_PortType BRSHW_PORT_FR0A_RX = {
  BRSHW_PORT_PORTGROUP_E,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_FR0A_RX = {
  736u,
  BRSHW_PORT_ALT_1}; /*PE3 (mscr736)*/
#define _BRSHW_PORT_FR0A_TXEN
const brsHw_Port_PortType BRSHW_PORT_FR0A_TXEN = {
  BRSHW_PORT_PORTGROUP_E,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_2};

const brsHw_Port_PortType BRSHW_PORT_FR0B_TX = {
  BRSHW_PORT_PORTGROUP_E,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_3};
const brsHw_Port_PortType BRSHW_PORT_FR0B_RX = {
  BRSHW_PORT_PORTGROUP_E,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_FR0B_RX = {
  737u,
  BRSHW_PORT_ALT_1}; /*PE5 (mscr737)*/
#define _BRSHW_PORT_FR0B_TXEN
const brsHw_Port_PortType BRSHW_PORT_FR0B_TXEN = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_2};
# endif /*VGEN_ENABLE_DRVFR__BASEASR*/

/*******************************************************************************
  ETHERNET driver
********************************************************************************/
# if defined (VGEN_ENABLE_DRVETH__BASEASR)
#define _BRSHW_PORT_ETH0_RXCLK
const brsHw_Port_PortType BRSHW_PORT_ETH0_RXCLK = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_ETH0_RXCLK = {
  960u,
  BRSHW_PORT_ALT_1}; /*PA3 (mscr760)*/
#define _BRSHW_PORT_ETH0_RXD3
const brsHw_Port_PortType BRSHW_PORT_ETH0_RXD3 = {
  BRSHW_PORT_PORTGROUP_E,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_ETH0_RXD3 = {
  966u,
  BRSHW_PORT_ALT_1}; /*PE13 (mscr966)*/
#define _BRSHW_PORT_ETH0_RXD2
const brsHw_Port_PortType BRSHW_PORT_ETH0_RXD2 = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_ETH0_RXD2 = {
  965u,
  BRSHW_PORT_ALT_1}; /*PA7 (mscr965)*/
const brsHw_Port_PortType BRSHW_PORT_ETH0_RXD1 = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_ETH0_RXD1 = {
  964u,
  BRSHW_PORT_ALT_1}; /*PA8 (mscr965)*/
const brsHw_Port_PortType BRSHW_PORT_ETH0_RXD0 = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_ETH0_RXD0 = {
  963u,
  BRSHW_PORT_ALT_1}; /*PA9 (mscr963)*/
const brsHw_Port_PortType BRSHW_PORT_ETH0_COL = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_ETH0_COL = {
  968u,
  BRSHW_PORT_ALT_1}; /*PA10 (mscr968)*/
#define _BRSHW_PORT_ETH0_RXER
const brsHw_Port_PortType BRSHW_PORT_ETH0_RXER = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_ETH0_RXER = {
  967u,
  BRSHW_PORT_ALT_1}; /*PA11 (mscr967)*/
const brsHw_Port_PortType BRSHW_PORT_ETH0_CRS = {
  BRSHW_PORT_PORTGROUP_E,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_ETH0_CRS = {
  970u,
  BRSHW_PORT_ALT_1}; /*PE12 (mscr970)*/

#  if (MPC5748G_CUT == 2)
const brsHw_Port_PortType BRSHW_PORT_ETH0_MDIO = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_4};
#  else
const brsHw_Port_PortType BRSHW_PORT_ETH0_MDIO = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_0};
#  endif

const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_ETH0_MDIO = {
  962u,
  BRSHW_PORT_ALT_1}; /*PF14 (mscr962)*/
const brsHw_Port_PortType BRSHW_PORT_ETH0_RXDV = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_15,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_ETH0_RXDV = {
  969u,
  BRSHW_PORT_ALT_1}; /*PF15 (mscr969)*/
const brsHw_Port_PortType BRSHW_PORT_ETH0_REFCLK = {
  BRSHW_PORT_PORTGROUP_G,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_ETH0_REFCLK = {
  961u,
  BRSHW_PORT_ALT_1}; /*PG1 (mscr961)*/
#define _BRSHW_PORT_ETH0_MDC
const brsHw_Port_PortType BRSHW_PORT_ETH0_MDC = {
  BRSHW_PORT_PORTGROUP_G,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_3};
#define _BRSHW_PORT_ETH0_TXD3
const brsHw_Port_PortType BRSHW_PORT_ETH0_TXD3 = {
  BRSHW_PORT_PORTGROUP_G,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_ALT_4};
#define _BRSHW_PORT_ETH0_TXD2
const brsHw_Port_PortType BRSHW_PORT_ETH0_TXD2 = {
  BRSHW_PORT_PORTGROUP_G,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_ALT_4};
const brsHw_Port_PortType BRSHW_PORT_ETH0_TXD1 = {
  BRSHW_PORT_PORTGROUP_H,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_3};
const brsHw_Port_PortType BRSHW_PORT_ETH0_TXD0 = {
  BRSHW_PORT_PORTGROUP_H,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_4};
const brsHw_Port_PortType BRSHW_PORT_ETH0_TXEN = {
  BRSHW_PORT_PORTGROUP_H,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_4};
#define _BRSHW_PORT_ETH0_TXER
const brsHw_Port_PortType BRSHW_PORT_ETH0_TXER = {
  BRSHW_PORT_PORTGROUP_H,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_3};
# endif /*VGEN_ENABLE_DRVETH__BASEASR*/
#endif /*BRSHW_SIU_GROUP_E*/

#if defined (BRSHW_SIU_GROUP_F)
/*******************************************************************************
  CAN driver
********************************************************************************/
# if defined (VGEN_ENABLE_CAN_DRV)
#  if defined (kCanPhysToLogChannelIndex_0)
const brsHw_Port_PortType BRSHW_PORT_CAN0_TX = {
  BRSHW_PORT_PORTGROUP_D,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_1}; /*PD10 (mscr58)*/
const brsHw_Port_PortType BRSHW_PORT_CAN0_RX = {
  BRSHW_PORT_PORTGROUP_D,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_0}; /*PD9 (mscr57)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN0_RX = {
  512u,
  BRSHW_PORT_ALT_1}; /*PD9 (mscr512)*/
#define _BRSHW_PORT_CAN0_TRCV_STB
const brsHw_Port_PortType BRSHW_PORT_CAN0_TRCV_STB = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_0}; /*PA7 (mscr7)*/
#  endif /*kCanPhysToLogChannelIndex_0*/

#  if defined (kCanPhysToLogChannelIndex_1)
const brsHw_Port_PortType BRSHW_PORT_CAN1_TX = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_ALT_2}; /*PA13 (mscr13)*/
const brsHw_Port_PortType BRSHW_PORT_CAN1_RX = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_0}; /*PC2 (mscr34)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN1_RX = {
  513u,
  BRSHW_PORT_ALT_3}; /*PC2 (mscr513) MCAN_1_RX*/
#  endif /*kCanPhysToLogChannelIndex_1*/
# endif /*VGEN_ENABLE_CAN_DRV*/

/*******************************************************************************
  LIN driver
********************************************************************************/
# if defined (VGEN_ENABLE_LIN_DRV)
  #error "SIU Group for LIN not yet supported!"
# endif

/*******************************************************************************
  FLEXRAY driver
********************************************************************************/
# if defined (VGEN_ENABLE_DRVFR__BASEASR)
  #error "SIU Group for Flexray not yet supported!"
# endif
#endif /*BRSHW_SIU_GROUP_F*/

#if defined (BRSHW_SIU_GROUP_G)
/*******************************************************************************
  CAN driver
********************************************************************************/
# if defined (VGEN_ENABLE_CAN_DRV)
#  if defined (kCanPhysToLogChannelIndex_0)
const brsHw_Port_PortType BRSHW_PORT_CAN0_TX = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_12,
  BRSHW_PORT_ALT_8}; /*PF12 (mscr92)*/
const brsHw_Port_PortType BRSHW_PORT_CAN0_RX = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_13,
  BRSHW_PORT_ALT_0}; /*PF13 (mscr93)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN0_RX = {
  700u,
  BRSHW_PORT_ALT_4}; /*PF13 (mscr700)*/
#  endif /*kCanPhysToLogChannelIndex_0*/

#  if defined (kCanPhysToLogChannelIndex_1)
const brsHw_Port_PortType BRSHW_PORT_CAN1_TX = {
  BRSHW_PORT_PORTGROUP_D,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_8}; /*PD1 (mscr49)*/
const brsHw_Port_PortType BRSHW_PORT_CAN1_RX = {
  BRSHW_PORT_PORTGROUP_D,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_0}; /*PD0 (mscr48)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN1_RX = {
  701u,
  BRSHW_PORT_ALT_1}; /*PD0 (mscr701) MCAN_1_RX*/
#  endif /*kCanPhysToLogChannelIndex_1*/

#  if defined (kCanPhysToLogChannelIndex_2)
const brsHw_Port_PortType BRSHW_PORT_CAN2_TX = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_8}; /*PC7 (mscr39)*/
const brsHw_Port_PortType BRSHW_PORT_CAN2_RX = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_0}; /*PC6 (mscr38)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN2_RX = {
  702u,
  BRSHW_PORT_ALT_1}; /*PC6 (mscr702) MCAN_2_RX*/
#  endif /*kCanPhysToLogChannelIndex_2*/

#  if defined (kCanPhysToLogChannelIndex_3)
const brsHw_Port_PortType BRSHW_PORT_CAN3_TX = {
  BRSHW_PORT_PORTGROUP_G,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_ALT_8}; /*PG11 (mscr107)*/
const brsHw_Port_PortType BRSHW_PORT_CAN3_RX = {
  BRSHW_PORT_PORTGROUP_G,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_0}; /*PG9 (mscr105)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN3_RX = {
  703u,
  BRSHW_PORT_ALT_3}; /*PG9 (mscr703) MCAN_3_RX*/
#  endif /*kCanPhysToLogChannelIndex_3*/
# endif /*VGEN_ENABLE_CAN_DRV*/

/*******************************************************************************
  LIN driver
********************************************************************************/
# if defined (VGEN_ENABLE_LIN_DRV)
#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_0)
const brsHw_Port_PortType BRSHW_PORT_LIN0_TX = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_9}; /*PF10 (mscr90)*/
const brsHw_Port_PortType BRSHW_PORT_LIN0_RX = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_ALT_0}; /*PF11 (mscr91)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN0_RX = {
  752u,
  BRSHW_PORT_ALT_2}; /*PF11 (mscr752) LIN0_RX*/
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_0*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_1)
const brsHw_Port_PortType BRSHW_PORT_LIN1_TX = {
  BRSHW_PORT_PORTGROUP_G,
  BRSHW_PORT_PORTNUMBER_6,
  BRSHW_PORT_ALT_8}; /*PG6 (mscr102)*/
const brsHw_Port_PortType BRSHW_PORT_LIN1_RX = {
  BRSHW_PORT_PORTGROUP_G,
  BRSHW_PORT_PORTNUMBER_5,
  BRSHW_PORT_ALT_0}; /*PG5 (mscr101)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN1_RX = {
  701u,
  BRSHW_PORT_ALT_3}; /*PG5 (mscr 701) LIN1_RX*/
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_1*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_2)
const brsHw_Port_PortType BRSHW_PORT_LIN2_TX = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_0,
  BRSHW_PORT_ALT_9}; /*PF0 (mscr80)*/
const brsHw_Port_PortType BRSHW_PORT_LIN2_RX = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_1,
  BRSHW_PORT_ALT_0}; /*PF1 (mscr81)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN2_RX = {
  754u,
  BRSHW_PORT_ALT_3}; /*PF1 (mscr754) LIN2_RX*/
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_2*/

#  if defined (LIN_ENABLE_HARDWARE_INTERFACE_3)
const brsHw_Port_PortType BRSHW_PORT_LIN3_TX = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_2,
  BRSHW_PORT_ALT_9}; /*PF2 (mscr82)*/
const brsHw_Port_PortType BRSHW_PORT_LIN3_RX = {
  BRSHW_PORT_PORTGROUP_F,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_0}; /*PF3 (mscr83)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_LIN3_RX = {
  755u,
  BRSHW_PORT_ALT_2}; /*PF3 (mscr755) LIN3_RX*/
#  endif /*LIN_ENABLE_HARDWARE_INTERFACE_3*/
# endif /*VGEN_ENABLE_LIN_DRV*/

/*******************************************************************************
  FLEXRAY driver
********************************************************************************/
#  if defined (VGEN_ENABLE_DRVFR__BASEASR)
  #error "SIU Group for Flexray not yet supported!"
#  endif
#endif /*BRSHW_SIU_GROUP_G*/

#if defined (BRSHW_SIU_GROUP_H)
/*******************************************************************************
  CAN driver
********************************************************************************/
# if defined (VGEN_ENABLE_CAN_DRV)
#  if defined (kCanPhysToLogChannelIndex_0)
const brsHw_Port_PortType BRSHW_PORT_CAN0_TX = {
  BRSHW_PORT_PORTGROUP_D,
  BRSHW_PORT_PORTNUMBER_14,
  BRSHW_PORT_ALT_1}; /*PD14 (mscr62)*/
const brsHw_Port_PortType BRSHW_PORT_CAN0_RX = {
  BRSHW_PORT_PORTGROUP_D,
  BRSHW_PORT_PORTNUMBER_15,
  BRSHW_PORT_ALT_0}; /*PD15 (mscr63)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN0_RX = {
  752u,
  BRSHW_PORT_ALT_1}; /*PD15 (mscr752)*/
#  endif /*kCanPhysToLogChannelIndex_0*/

#  if defined (kCanPhysToLogChannelIndex_1)
const brsHw_Port_PortType BRSHW_PORT_CAN1_TX = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_1}; /*PA10 (mscr10)*/
const brsHw_Port_PortType BRSHW_PORT_CAN1_RX = {
  BRSHW_PORT_PORTGROUP_A,
  BRSHW_PORT_PORTNUMBER_11,
  BRSHW_PORT_ALT_0}; /*PA11 (mscr11)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN1_RX = {
  758u,
  BRSHW_PORT_ALT_2}; /*PA11 (mscr758) MCAN_1_RX*/
#  endif /*kCanPhysToLogChannelIndex_1*/

#  if defined (kCanPhysToLogChannelIndex_2)
const brsHw_Port_PortType BRSHW_PORT_CAN2_TX = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_1}; /*PC9 (mscr41)*/
const brsHw_Port_PortType BRSHW_PORT_CAN2_RX = {
  BRSHW_PORT_PORTGROUP_C,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_0}; /*PC8 (mscr40)*/
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_CAN2_RX = {
  759u,
  BRSHW_PORT_ALT_3}; /*PC8 (mscr759) MCAN_2_RX*/
#  endif /*kCanPhysToLogChannelIndex_2*/

#  if defined (kCanPhysToLogChannelIndex_3) || defined (kCanPhysToLogChannelIndex_4)
  #error "Port config for these CAN channels not yet implemented!"
#  endif
# endif /*VGEN_ENABLE_CAN_DRV*/

/*******************************************************************************
  LIN driver
********************************************************************************/
# if defined (VGEN_ENABLE_LIN_DRV)
   #error "SIU Group for LIN not yet supported!"
# endif

/*******************************************************************************
  FLEXRAY driver
********************************************************************************/
# if defined (VGEN_ENABLE_DRVFR__BASEASR)
  /* ERAY-A */
const brsHw_Port_PortType BRSHW_PORT_FR0A_TX = {
  BRSHW_PORT_PORTGROUP_H,
  BRSHW_PORT_PORTNUMBER_7,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_FR0A_RX = {
  BRSHW_PORT_PORTGROUP_H,
  BRSHW_PORT_PORTNUMBER_9,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_FR0A_RX = {
  772u,
  BRSHW_PORT_ALT_3}; /*PH9 (mscr772)*/
const brsHw_Port_PortType BRSHW_PORT_FR0A_TXEN = {
  BRSHW_PORT_PORTGROUP_H,
  BRSHW_PORT_PORTNUMBER_8,
  BRSHW_PORT_ALT_5};

  /* ERAY-B */
const brsHw_Port_PortType BRSHW_PORT_FR0B_TX = {
  BRSHW_PORT_PORTGROUP_H,
  BRSHW_PORT_PORTNUMBER_3,
  BRSHW_PORT_ALT_5};
const brsHw_Port_PortType BRSHW_PORT_FR0B_RX = {
  BRSHW_PORT_PORTGROUP_H,
  BRSHW_PORT_PORTNUMBER_10,
  BRSHW_PORT_ALT_0};
const brsHw_Port_MultiplexedType BRSHW_PORT_MUX_FR0B_RX = {
  773u,
  BRSHW_PORT_ALT_3}; /*PH10 (mscr773)*/
const brsHw_Port_PortType BRSHW_PORT_FR0B_TXEN = {
  BRSHW_PORT_PORTGROUP_H,
  BRSHW_PORT_PORTNUMBER_4,
  BRSHW_PORT_ALT_5};
# endif /*VGEN_ENABLE_DRVFR__BASEASR*/
#endif /*BRSHW_SIU_GROUP_H*/

#endif /*_BRSHW_PORTS_H_*/
