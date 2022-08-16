/***********************************************************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/** \file
 *  \brief         Main module of FBL
 *
 *  --------------------------------------------------------------------------------------------------------------------
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \par Copyright
 *  \verbatim
 *  Copyright (c) 2017 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  --------------------------------------------------------------------------------------------------------------------
 *  Achim Strobelt                Ach           Vector Informatik GmbH
 *  Marco Riedl                   Rie           Vector Informatik GmbH
 *  Thomas Mueller                ThM           Vector Informatik GmbH
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version    Date        Author  Change Id        Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  03.00.00   2016-02-26  Ach     -                First implementation, based on FblKbMain_Frame 01.52.00
 *  03.00.01   2016-02-26  Ach     ESCAN00088625    No changes
 *  03.01.00   2016-05-13  Rie     ESCAN00089848    No changes
 *  03.02.00   2016-08-23  Ach     ESCAN00091452    Removed bootloader package version information from FblHeader
 *  03.02.01   2016-10-25  Ach     ESCAN00092497    Check diagnostic task call cycle to be configured to 1ms
 *  03.03.00   2017-05-09  ThM     ESCAN00094543    Added MemMap include for FblStart()
 *                         Ach     ESCAN00094542    Support automatic DemoAppl creation
 *  03.04.00   2017-07-28  Ach     ESCAN00096094    Support FblWrapperCom_PduR 5.x
 **********************************************************************************************************************/

#ifndef __FBL_MAIN_H__
#define __FBL_MAIN_H__

/***********************************************************************************************************************
 *  VERSION
 **********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : FblMain CQComponent : Implementation */
#define FBL_MAIN_VERSION           0x0304u
#define FBL_MAIN_RELEASE_VERSION   0x00u

/***********************************************************************************************************************
 *  DEFINES
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  Main state definitions
 **********************************************************************************************************************/
#define kFblMainStateStartFromReset             0u
#define kFblMainStateStartFromAppl              1u
#define kFblMainStateStartFromXcp               2u
#define kFblMainStateApplicationValid           3u
#define kFblMainStateWaitStartMessage           4u
#define kFblMainStateStartMessageReceived       5u
#define kFblMainStateFblShutdownRequest         6u

#define kFblMainNumberOfStates                  7u

/***********************************************************************************************************************
 *  State handling framework
 **********************************************************************************************************************/
/* PRQA S 3453 3 */ /* MD_MSR_19.7 */
#define GetFblMainState(state)                  FBL_STATE_TEST(fblMainStates, (state)) /**< Read fbl_main state bit */
#define SetFblMainState(state)                  FBL_STATE_SET(fblMainStates, state)    /**< Set fbl_main state bit */
#define ClrFblMainState(state)                  FBL_STATE_CLR(fblMainStates, state)    /**< Clear fbl_main state bit */

#define FblMainGetStartFromReset()              GetFblMainState( kFblMainStateStartFromReset )
#define FblMainGetStartFromAppl()               GetFblMainState( kFblMainStateStartFromAppl )
#define FblMainGetStartFromXcp()                GetFblMainState( kFblMainStateStartFromXcp )
#define FblMainGetApplicationValid()            GetFblMainState( kFblMainStateApplicationValid )
#define FblMainGetWaitStartMessage()            GetFblMainState( kFblMainStateWaitStartMessage )
#define FblMainGetStartMessageReceived()        GetFblMainState( kFblMainStateStartMessageReceived )
#define FblMainGetFblShutdownRequest()          GetFblMainState( kFblMainStateFblShutdownRequest )

#define FblMainSetFblShutdownRequest()          SetFblMainState( kFblMainStateFblShutdownRequest )
#define FblMainClrFblShutdownRequest()          ClrFblMainState( kFblMainStateFblShutdownRequest )
#define FblSetShutdownRequest()                 FblMainSetFblShutdownRequest()

/***********************************************************************************************************************
 *  Initialization steps
 **********************************************************************************************************************/
#define kFblInitPowerOn                      0x00u /**< Power-on initialization step */
#define kFblInitBaseInitialization           0x01u /**< Init steps before application validity check */
#define kFblInitFblCommunication             0x02u /**< Bootloader initialization first part - mainly communication */
#define kFblInitFblFinalize                  0x03u /**< Finalize Bootloader initialization if application isn't started */

#define kFblInitPreCallback                  0x00u /**< Initialization callback before core init function */
#define kFblInitPostCallback                 0x80u /**< Initialization callback after core init function */

/***********************************************************************************************************************
 *  FblHeader access
 **********************************************************************************************************************/

/* Define to access the FBL header structure */
#define FblHeaderTable  ((V_MEMROM1_FAR tFblHeader V_MEMROM2_FAR V_MEMROM3 *)(FBL_HEADER_ADDRESS))
#define FblHeaderLocal  ((V_MEMROM1_FAR tFblHeader V_MEMROM2_FAR V_MEMROM3 *)(&FblHeader))

/* Access macros for FblHeader elements for application */
#if defined( FBL_ENABLE_COMMON_DATA )
# define GetFblCommonDataPtr()   (FblHeaderTable->pFblCommonData)
#endif

#if defined( FBL_ENABLE_FBL_START )
# if defined( FBL_MAIN_ENABLE_FBLSTART_PARAM )
#  define CallFblStart(pParam, length) (FblHeaderTable->pFblStartFct)(pParam, length)
# else
#  define CallFblStart()   (FblHeaderTable->pFblStartFct)()
# endif
#endif /* FBL_ENABLE_FBL_START */

#if defined( FBL_ENABLE_FBL_START )
/* Define pattern for magic flags used for reprogramming indication */
# define kFblStartMagicByte0     0x50u /* 'P' */
# define kFblStartMagicByte1     0x72u /* 'r' */
# define kFblStartMagicByte2     0x6Fu /* 'o' */
# define kFblStartMagicByte3     0x67u /* 'g' */
# define kFblStartMagicByte4     0x53u /* 'S' */
# define kFblStartMagicByte5     0x69u /* 'i' */
# define kFblStartMagicByte6     0x67u /* 'g' */
# define kFblStartMagicByte7     0x6Eu /* 'n' */
# define kFblNoOfMagicBytes      8u
# define kFblClearMagicByte      0x00u

# define FblSetFblStartMagicFlag() \
{ \
   fblStartMagicFlag[0] = kFblStartMagicByte0; \
   fblStartMagicFlag[1] = kFblStartMagicByte1; \
   fblStartMagicFlag[2] = kFblStartMagicByte2; \
   fblStartMagicFlag[3] = kFblStartMagicByte3; \
   fblStartMagicFlag[4] = kFblStartMagicByte4; \
   fblStartMagicFlag[5] = kFblStartMagicByte5; \
   fblStartMagicFlag[6] = kFblStartMagicByte6; \
   fblStartMagicFlag[7] = kFblStartMagicByte7; \
}

# define FblChkFblStartMagicFlag() \
   ((    (fblStartMagicFlag[0] == kFblStartMagicByte0) \
      && (fblStartMagicFlag[1] == kFblStartMagicByte1) \
      && (fblStartMagicFlag[2] == kFblStartMagicByte2) \
      && (fblStartMagicFlag[3] == kFblStartMagicByte3) \
      && (fblStartMagicFlag[4] == kFblStartMagicByte4) \
      && (fblStartMagicFlag[5] == kFblStartMagicByte5) \
      && (fblStartMagicFlag[6] == kFblStartMagicByte6) \
      && (fblStartMagicFlag[7] == kFblStartMagicByte7)) ? 1u : 0u)

# define FblClrFblStartMagicFlag()                 \
   {                                               \
      fblStartMagicFlag[0] = kFblClearMagicByte;   \
      fblStartMagicFlag[1] = kFblClearMagicByte;   \
      fblStartMagicFlag[2] = kFblClearMagicByte;   \
      fblStartMagicFlag[3] = kFblClearMagicByte;   \
      fblStartMagicFlag[4] = kFblClearMagicByte;   \
      fblStartMagicFlag[5] = kFblClearMagicByte;   \
      fblStartMagicFlag[6] = kFblClearMagicByte;   \
      fblStartMagicFlag[7] = kFblClearMagicByte;   \
   }
#endif /* #if defined( FBL_ENABLE_FBL_START ) */

/***********************************************************************************************************************
*  COM WRAPPER COMPATIBILITY DEFINITIONS
**********************************************************************************************************************/

/* Define interface version for classic FblWrapperCom modules */
#if !defined( FBL_CW_API_REFERENCE_VERSION_MAJOR )
/** Major interface version identifies incompatible changes */
# define FBL_CW_API_REFERENCE_VERSION_MAJOR     0x01u
/** Minor interface version identifies backward compatible changes */
# define FBL_CW_API_REFERENCE_VERSION_MINOR     0x00u
/** Release interface version identifies cosmetic changes */
# define FBL_CW_API_REFERENCE_VERSION_RELEASE   0x00u
#endif

#if !defined( FBL_CW_CFG_PTR )
# define FBL_CW_CFG_PTR V_NULL
#endif

/***********************************************************************************************************************
 *  TYPE DEFINITIONS
 **********************************************************************************************************************/

#if defined( FBL_ENABLE_COMMON_DATA )
/** Pointer to shared ROM constants */
typedef V_MEMROM1_FAR void V_MEMROM2_FAR V_MEMROM3 * tFblCommonDataPtr;
#endif /* FBL_ENABLE_COMMON_DATA */

#if defined( FBL_ENABLE_FBL_START )
# if defined( FBL_MAIN_ENABLE_FBLSTART_PARAM )
/** Pointer to call FblStart() function */
typedef FBL_CALL_TYPE void (*tFblStrtFct)(void* pParam, vuint8 length);
# else
/** Pointer to call FblStart() function */
typedef FBL_CALL_TYPE void (*tFblStrtFct)(void);
# endif /* FBL_MAIN_ENABLE_FBLSTART_PARAM */
#endif /* FBL_ENABLE_FBL_START */
/** Pointer type to logical block table */
typedef V_MEMROM1_FAR tLogicalBlockTable V_MEMROM2_FAR V_MEMROM3 * tFblHeaderLogicalBlockTablePtr;

/** FBL header structure */
typedef struct
{
   tFblHeaderLogicalBlockTablePtr pLogicalBlockTable;
#if defined( FBL_ENABLE_COMMON_DATA )
   tFblCommonDataPtr pFblCommonData;   /**< Common data structure - OEM dependent */
#endif /* FBL_ENABLE_COMMON_DATA */
#if defined( FBL_ENABLE_FBL_START )
   tFblStrtFct pFblStartFct;           /**< Pointer to FblStart-function */
#endif /* FBL_ENABLE_FBL_START */
} tFblHeader;

/***********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/
V_MEMRAM0 extern V_MEMRAM1_NEAR tFblStateBitmap V_MEMRAM2_NEAR fblMainStates[FBL_STATE_INDEX(kFblMainNumberOfStates - 1u) + 1u];

# define FBLHEADER_START_SEC_CONST
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
V_MEMROM0 extern V_MEMROM1 tFblHeader V_MEMROM2 FblHeader;
# define FBLHEADER_STOP_SEC_CONST
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if defined( FBL_ENABLE_FBL_START )
#  define FBL_MAIN_MAGICFLAG_START_SEC_VAR
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/* Entering bootloader with 8 byte special ('FBLSTARTMAGIC') values */
V_MEMRAM0 extern volatile V_MEMRAM1 vuint8 V_MEMRAM2 fblStartMagicFlag[kFblNoOfMagicBytes];
#  if defined( FBL_MAIN_ENABLE_FBLSTART_PARAM )
V_MEMRAM0 extern volatile V_MEMRAM1 tFblStartParamter V_MEMRAM2 fblStartParameter;
#  endif /* FBL_MAIN_ENABLE_FBLSTART_PARAM */
#  define FBL_MAIN_MAGICFLAG_STOP_SEC_VAR
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
# endif /* FBL_ENABLE_FBL_START */

/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

# if defined( FBL_ENABLE_FBL_START )
#  define FBL_MAIN_FBLSTART_START_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#  if defined( FBL_MAIN_ENABLE_FBLSTART_PARAM )
void V_CALLBACK_NEAR FblStart( V_MEMRAM1 void V_MEMRAM2 V_MEMRAM3 * pFblStartParam, vuint8 length );
#  else
void V_CALLBACK_NEAR FblStart( void );
#  endif /* FBL_MAIN_ENABLE_FBLSTART_PARAM */
#  define FBL_MAIN_FBLSTART_STOP_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
# endif /* FBL_ENABLE_FBL_START */

/***********************************************************************************************************************
 *  CONFIGURATION CHECKS
 **********************************************************************************************************************/

/* Check diagnostic task call cycle */
#if defined( kDiagCallCycle )
# if( kDiagCallCycle != 1u )
#  error "Diagnostic task call cycle has to be configured to 1ms."
# endif
#endif /* kDiagCallCycle */

#endif /* __FBL_MAIN_H__ */

/***********************************************************************************************************************
 *  END OF FILE: FBL_MAIN.H
 **********************************************************************************************************************/
