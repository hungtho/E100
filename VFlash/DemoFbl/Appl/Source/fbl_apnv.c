/* Kernbauer Version: 1.12 Konfiguration: FBL Erzeugungsgangnummer: 1 */

/***********************************************************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/** \file
 *  \brief         Application dependent nonvolatile memory access routines
 *
 *  \note          Please note, that this file contains a collection of callback functions to be used with the
 *                 Flash Bootloader. These functions may influence the behavior of the bootloader in principle.
 *                 Therefore, great care must be taken to verify the correctness of the implementation.
 *                 The contents of the originally delivered files are only examples resp. implementation proposals.
 *                 With regard to the fact that these functions are meant for demonstration purposes only, Vector
 *                 Informatik's liability shall be expressly excluded in cases of ordinary negligence, to the extent
 *                 admissible by law or statute.
 *
 *  --------------------------------------------------------------------------------------------------------------------
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \par Copyright
 *  \verbatim
 *  Copyright (c) 2016 by Vector Informatik GmbH.                                                  All rights reserved.
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
 *  Christian Baeuerle            CB            Vector Informatik GmbH
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version    Date        Author  Change Id        Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  02.00.00   2016-11-07  CB      -                Initial version based on UDS2 component
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY (kbFbl_apAPI.c)
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version    Date        Author  Change Id        Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  00.90.00   2003-12-10  CB                       First implementation
 *  00.91.00   2004-01-08  CB                       Decryption/decompression interface changed
 *                         CB                       Parameters for ApplFblVerifyChecksum changed
 *  01.00.00   2004-02-24  CB                       Release
 *  01.01.00   2004-03-24  Rr                       Added new functions
 *  01.02.00   2004-03-25  WM                       Minor changes and enhancements for new OEM
 *  01.03.00   2004-04-23  WM                       Added watchdog trigger functions
 *                         ACP                      Added ApplFblSecurityStatus
 *                         AMN                      Added ApplFblIsValidFlashBlock, and ApplFblReadBlock
 *  01.04.00   2004-05-07  CB                       Added ApplCanBusOff, ApplCanWakeUp
 *  01.05.00   2004-05-19  CB                       Minor changes
 *  01.06.00   2004-06-30  MHz                      No changes
 *  01.07.00   2004-07-22  CB                       Added ApplFblReadEcuIdentification,
 *                                                  ApplFblStoreTesterCode, ApplFblStoreProgrammingDate
 *  01.08.00   2004-08-06  WM                       Added ApplFblRWSecurityAccessDelayFlag
 *  01.09.00   2004-09-09  Rr                       Minor changes for ApplFblCanBusOff
 *  01.10.00   2004-09-16  WM                       Added PRE and POST section for ApplFblWDTrigger
 *  01.11.00   2004-10-25  AP      ESCAN00010007    Adaption to support Vector
 *                                                  component OSEK NM
 *  01.12.00   2004-12-23  AMN                      Changed prototype of ApplFblWriteDataById
 *                                                  Added an ifdef to ApplFblCanParamInit
 *                                                  Added function ApplFblPBLConfigSet
 *                                                  Corrected the paramters in ApplFblRWProgCounter
 *                                                  Define name changes PBL->CAN
 *                         ACP                      Version check reworked
 *                         CB                       Added fingerprint functions
 *  01.13.00   2005-01-14  CB                       Added several API functions
 *  01.14.00   2005-03-22  WM      ESCAN00011595    MISRA warnings
 *  01.15.00   2005-09-29  WM                       _PRE_ and _POST_ section for ApplFblWDTriggerEnd
 *                                                  V_VER.H consistency check added
 *  01.16.00   2005-12-08  WM      ESCAN00014594    FblApSrcApplFblTpParamInit token
 *                                                  added for TPMC
 *  01.17.00   2006-02-28  AMN                      Added ApplFblCopyToRAM and ApplFblIsValidAppInRAM
 *  01.18.00   2006-03-24  QPs                      Added ApplFblGetSubNodeRxCanId for Gateway
 *                                                  implementation
 *  01.19.00   2006-04-25  CB      ESCAN00015917    Return value added for
 *                                                  ApplFblInvalidateBlock
 *                         WM      ESCAN00015960    ApplFblVerifySegmentChecksum added
 *                         Ls                       added KBTok_FblApSrcApplFblCheckProgDependencies
 *                         QPs     ESCAN00016110    Added ApplCanBusOff for the Gateway
 *                         CB      ESCAN00016144    Return value added for
 *                                                  ApplFblInitDecryption
 *                         CB      ESCAN00016147    ApplFblStoreBootSwIdent added
 *                                 ESCAN00016171    ApplFblSetSecAccessDelayFlag,
 *                                                  ApplFblGetSecAccessDelayFlag and
 *                                                  ApplFblClrSecAccessDelayFlag added
 *  01.20.00   2006-05-18  ACP     ESCAN00016438    Added kStartupPreInit/PostInit
 *                                                  definition for new ApplFblStartup() parameter
 *  01.21.00   2006-06-29  FHE                      No changes
 *  01.22.00   2006-07-24  JHg                      Added V_CALLBACK_NEAR to watchdog trigger
 *                         CB      ESCAN00017003    Added ApplFblProgrammingStateChanged
 *                         AMN                      Added ApplFblValidateFile
 *                                                  Added a token to reference local prototypes
 *                                                  from the OEM layer
 *  01.23.00   2006-08-28  JHg                      Added token for additional watchdog functions
 *                         AMN     ESCAN00017479    Modified the API of the
 *                                                  ApplFblValidateApp for Misra compliance
 *                                                  Removed ApplFblIsValidFlashBlock because it's
 *                                                  not used anymore
 *  01.24.00   2006-12-06  FHE     ESCAN00018639    Added ApplFblCheckConditions
 *  01.25.00   2007-02-07  Hp      ESCAN00019129    Add support for CCP in the bootloader
 *                                                  Add PreHandler and presence-pattern support.
 *  01.26.00   2007-03-30  WM      ESCAN00020175    Added ApplFblCheckProgPreconditions
 *  01.27.00   2007-07-06  JHg                      Return value added to ApplFblDecryption and
 *                                                  ApplFblDeinitDecryption
 *  01.28.00   2007-07-27  Ls      ESCAN00022542    FBL_ENABLE_PRE_WDINIT_COMMENT added
 *  01.29.00   2008-03-07  Ci      ESCAN00014726    FBL_COPY_CODE_TO_RAM_ON_STARTUP
 *                                                  renamed to FBL_ENABLE_COPY..
 *                         Hp      ESCAN00014726    Support for memmap and FBL_ENABLE_COPY_CODE_TO_RAM_ON_STARTUP
 *                                                  to map ApplFblWDTrigger and ApplFblWDTriggerEnd to special location
 *                         JHg                      Update CAN driver Tx confirmation routines to RI 1.4 API
 *                         Hp      ESCAN00025029    Support Vector decompression module (optional)
 *  01.30.00   2008-03-28  JHg     ESCAN00025354    Remove COMMENT restriction from FBL_ENABLE_PRE_WDINIT
 *                                                  If enabled watchdog will be already initalized in ApplFblInit
 *                                 ESCAN00025355    FBL_ENABLE_PRE_TIMERINIT added
 *                                                  If enabled timer will be already initalized in ApplFblInit
 *  01.31.00   2008-06-13  Ci      ESCAN00025071    Extended function description of
 *                                                  ApplFblStartup() with kStartupStayInBoot
 *                                 ESCAN00027445    Added support for configurations
 *                                                  with multiple CAN channels
 *  01.32.00   2008-09-10  JHg     ESCAN00029860    Moved PRE_WDINIT and PRE_TIMERINIT to fbl_main
 *  01.33.00   2008-10-15  FHe     ESCAN00030640    Added support for VAG spec 1.2.1
 *  01.34.00   2009-03-13  JHg     ESCAN00032180    Added support for multichannel configurations
 *                                                  to ApplCanTxObjStart, ApplCanTxObjConfirmed
 *                                                  Updated description of ApplCanMsgReceived
 *                         FHe                      Restored old format of ApplFblCheckProgConditions
 *                         Ci      ESCAN00033475    Added gateway specific callback
 *                                                  functions (Gw_Route support)
 *  01.35.00   2009-03-12  QPs     ESCAN00033801    Added communication wrapper specific
 *                                                  callback functions
 *  01.36.00   2009-07-21  QPs     ESCAN00035282    Added DC SLP10 extension:
 *                                                  ApplFblControlFailSafeReaction
 *                         AWh     ESCAN00036825    Inconsistent return value type between
 *                                                  ReadDataByCommonId prototype and implementation
 *  01.37.00   2009-08-31  AWh     ESCAN00037405    No changes
 *                         QPs     ESCAN00037479    Added FrTrcv specific callback functions
 *  01.38.00   2009-09-18  Tbe     ESCAN00037856    Added Ethernet/DoIP specific
 *                                                  callback functions
 *  01.39.00   2009-12-02  Ci      ESCAN00038917    Adapted prototype of
 *                                                  ApplFblFatalError()
 *                                 ESCAN00038918    Added support for validation
 *                                                  struct handling
 *                                 ESCAN00038919    Added callback for flash erased
 *                                                  detection
 *  01.40.00   2010-02-15  Ci      ESCAN00040663    Enhanced flash erased detection
 *                                                  interface
 *                         Ci      ESCAN00040852    Replaced decryption interface by
 *                                                  data processing API
 *  01.41.00   2010-07-08  MVi     ESCAN00043736    Remove pragmas when memmap is used
 *                         Ci      ESCAN00043863    Added function ApplCanTpConfirmation
 *                         QPs     ESCAN00043896    Added support for LIN bootloader
 *  01.42.00   2010-07-23  CB      ESCAN00044299    Default implementation of decompression
 *  01.43.00   2010-09-15  Ci      ESCAN00044991    Added new Gw_Route API functions
 *  01.44.00   2010-12-10  MVi     ESCAN00047478    Enhanced flash erased detection interface
 *                                 ESCAN00047482    Added routine control succeeded interface
 *  01.45.00   2011-02-03  Ach     ESCAN00048191    Use normal fixed addressing without TPMC
 *  01.46.00   2011-07-14  Ci      ESCAN00052149    Adapted Gw_Route task interface
 *  01.47.00   2011-11-25  Hp      ESCAN00052787    Extend support for PresencePatterns
 *  01.48.00   2011-12-14  AWh     ESCAN00055586    Extend Api with ApplFblInvalidateApp function
 *  01.49.00   2012-02-14  Ach     ESCAN00056341    Added ApplFblStartApplication() function
 *  01.50.00   2012-02-22  Ach     ESCAN00052787    Extend support for PresencePatterns
 *                         MVi     ESCAN00056833    Extend support for PresencePatterns (HMC)
 *                                 ESCAN00056834    No changes
 *                         CB      ESCAN00056642    Added ApplFblCanPlatformToPhysChannel()
 *  01.51.00   2012-03-23  QPs     ESCAN00057230    Extend support for FlexRay
 *                         Ach     ESCAN00057636    Remove local memSegment variables
 *                         CB      ESCAN00057670    Added Suspend Programming API
 *  01.52.00   2012-03-30  QPs     ESCAN00058040    No changes
 *  01.53.00   2012-08-16  MVi     ESCAN00060433    Support for PresencePatterns
 *                                                  with 256 byte segment size
 *  01.54.00   2012-12-06  AWh     ESCAN00061619    Moved presence pattern macros to header
 *                         Ach     ESCAN00062912    Adapted comments to use Doxygen
 *  01.55.00   2013-01-24  Ach     ESCAN00064406    Support return value IO_E_ERASED for presence pattern
 *                         JHg     ESCAN00064421    Added callback ApplFblOnTransitionSession
 *                                 ESCAN00064437    Added callback ApplFblStateTask
 *  01.56.00   2013-02-08  ASe     ESCAN00064889    Reworked comments
 *  01.57.00   2014-01-21  ASe     ESCAN00072931    Fixed compiler warning (HMC)
 *  01.58.00   2014-02-24  MVi     ESCAN00073549    Removed HMC exceptions to support new mtab header
 *  01.58.01   2014-04-03  ASe     ESCAN00074701    Fixed comments
 *  01.59.00   2014-07-16  QPs     ESCAN00077127    Extend support for LIN
 *  01.60.00   2014-08-25  Dod     ESCAN00078033    Add callbacks ApplFblMemPreWrite/Erase and ApplFblGetLogBlkHash
 *  01.61.00   2015-01-13  Ach     ESCAN00080481    Change visibility of ApplFblChkModulePresence()
 *  01.62.00   2015-05-12  CB      ESCAN00082959    Added functions to read and store the TP target address
 *  01.63.00   2015-05-27  CB      ESCAN00083167    Additional callback functions for status backup
 *  01.64.00   2015-09-14  Ci      ESCAN00084704    Removed data processing default implementation
 *                         QPs     ESCAN00085203    Added callback ApplFblCheckTesterSourceAddr
 *  01.64.01   2015-12-15  TnS     ESCAN00087100    Moved initialization for Timer Interrupt use case to FblWd
 *  01.65.00   2016-01-11  ASe     ESCAN00087324    Presence pattern handling fails on word-addressed platforms
 *                         Rr      ESCAN00087414    Extend Renault SLP3 specific API for reading light LogZone
 *  01.66.00   2016-02-25  TnS     ESCAN00088471    MISRA related code changes
 *  01.67.00   2016-03-07  MVi     ESCAN00088759    Added ApplFblIsValidBlock
 *  01.68.00   2016-03-17  Shs     ESCAN00088957    No changes
 *  01.69.00   2016-05-09  HRf     ESCAN00089907    Encapsulate FlexRay specific code in ApplFblCwWakeUp()
 *  01.70.00   2016-05-17  Rie     ESCAN00090027    Performed MISRA analysis
 *  01.71.00   2016-06-27  Ach     ESCAN00090683    Support configuration switch FBL_CW_ENABLE_MULTIPLE_NODES
 *  01.72.00   2016-07-15  DlM     ESCAN00090996    Added function for programming voltage check
 *  01.73.00   2016-08-02  Ach     ESCAN00091282    Added ApplFblGetVerificationData()
 *  01.74.00   2016-08-24  Rie     ESCAN00091646    Added ApplFblCheckFuncTargetAddr()
 *  01.75.00   2016-10-04  CEl     ESCAN00092168    Added ApplFblSetLogBlkHash()
 *  01.76.00   2016-12-01  Ach     ESCAN00093116    Added length parameter to ApplFblGetVerificationData()
 *  01.77.00   2017-02-07  Ach     ESCAN00093891    Added constant definition for common data structure
 *  01.77.01   2017-06-22  Rie     ESCAN00095595    Fixed evaluation of the presence pattern
 *  01.78.00   2017-07-04  CB      ESCAN00095725    Added functions to read and write the segment list in NV-memory
 *                         CEl     ESCAN00095744    Added ApplFblStartSeperationTime()
 *  01.79.00   2017-07-31  Ach     ESCAN00096124    Add interface to handle DET callouts
 *  01.80.00   2017-08-08  Rie     ESCAN00096215    Added support for latest TpLin
 *  01.81.00   2017-09-13  Ach     ESCAN00096636    Add interface definition for ApplDiagUserRoutine
 *  01.82.00   2017-10-09  Ach     ESCAN00096961    ApplFbl_DetEntryHandler() uses wrong interface definition
 *  01.83.00   2017-12-20  Ach     ESCAN00097821    Added interface to handle DcmDslRxTesterSourceAddress
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  REVISION HISTORY (KbFbl_apOem.c)
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version    Date        Author  Change Id        Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  02.00.00   2016-11-07  CB      -                Initial version based on UDS2 component
 *  02.01.00   2017-01-24  CB      ESCAN00093698    Added example code for data processing
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY (KbFbl_apHW.h, Brs)
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version    Date        Author  Change Id        Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  01.00.00   2018-02-26  Csz                      Initial version
 *  01.00.01   2018-03-08  Csz                      Call the BrsHwTogglePin functions directly and include BrsHw.h
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/

#include "fbl_inc.h"

#include "BrsHw.h"

/***********************************************************************************************************************
 *  VERSION
 **********************************************************************************************************************/

#if ( FBLKBAPI_FRAMENV_SYMC_VERSION != 0x0200u ) || \
    ( FBLKBAPI_FRAMENV_SYMC_RELEASE_VERSION != 0x00u )
# error "Error in fbl_apnv.c Source and header file are inconsistent!"
#endif

#if ( (FBLKBAPI_FRAMENV_SYMC_VERSION != _FBLKBAPI_FRAMENV_OEM_VERSION ) || \
      (FBLKBAPI_FRAMENV_SYMC_RELEASE_VERSION != _FBLKBAPI_FRAMENV_OEM_RELEASE_VERSION) )
# error "Error in fbl_apxx.c: Source and v_ver.h are inconsistent!"
#endif

/***********************************************************************************************************************
 *  DEFINES
 **********************************************************************************************************************/

#if defined( FBL_ENABLE_PRESENCE_PATTERN )
/* PRQA S 3453 TAG_FblApNv_3453_1 */ /* MD_MSR_19.7 */
/* Memory driver access */
#define ApplFblReadPattern(buffer, address)           (MemDriver_RReadSync((IO_MemPtrType)(buffer), (IO_SizeType)kFblPresencePatternSize, (IO_PositionType)(address)))
#define ApplFblWritePattern(buffer, length, address)  (MemDriver_RWriteSync((IO_MemPtrType)(buffer), (IO_SizeType)(length), (IO_PositionType)(address)) == IO_E_OK)


V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 blockPresencePattern[kFblPresencePatternSize] = kFblPresencePattern;
/* PRQA L:TAG_FblApNv_3453_1 */
#endif /* FBL_ENABLE_PRESENCE_PATTERN */

/* Configuration check */
# if ( kEepSizeValidityFlags != kNrOfValidationBytes )
#  error "Size of block validity data is not correct. Check GENy configuration of size."
# endif

/***********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

#if defined( FBL_ENABLE_PRESENCE_PATTERN )
/** Presence pattern buffer with alignment to platform requirements */
typedef struct
{
#if defined( C_CPUTYPE_32BIT ) || \
    defined( C_CPUTYPE_16BIT )
   vuint32  dummy;
#endif /* C_CPUTYPE_32BIT || C_CPUTYPE_16BIT */
   vuint8   data[FBL_PP_SEGMENT_SIZE];
} tFblpresPtnAlignedBuffer;
#endif /* FBL_ENABLE_PRESENCE_PATTERN */

typedef vuint16   tFblApnvProgCountType;

/***********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/

#if defined( FBL_ENABLE_PRESENCE_PATTERN )
V_MEMRAM0 static V_MEMRAM1 tBlockDescriptor V_MEMRAM2 currentValidatedBlock;
#endif /* FBL_ENABLE_PRESENCE_PATTERN */

/***********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

#if defined( FBL_ENABLE_PRESENCE_PATTERN )
static vsint16 ApplFblGetPresencePatternBaseAddress( vuint8 blockNr, IO_PositionType * pPresPtnAddr, IO_SizeType * pPresPtnLen );
static tFblResult ApplFblSetModulePresence( tBlockDescriptor * blockDescriptor );
static tFblResult ApplFblClrModulePresence( tBlockDescriptor * blockDescriptor );
#endif /* FBL_ENABLE_PRESENCE_PATTERN */
static tFblResult ApplFblChgBlockValid( vuint8 mode, tBlockDescriptor descriptor );

/***********************************************************************************************************************
 *   GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  ApplFblChgBlockValid
 **********************************************************************************************************************/
/*! \brief       This function changes the validation flag of a logical block.
 *               The state information is stored inverted.
 *  \pre         EEPROM driver must be initialized before call
 *  \param[in]   mode (kEepValidateBlock/kEepInvalidateBlock)
 *  \param[in]   descriptor Block descriptor
 *  \return      kFblOk if successful, kFblFailed otherwise
 **********************************************************************************************************************/
static tFblResult ApplFblChgBlockValid( vuint8 mode, tBlockDescriptor descriptor )
{
   vuint8         validityMask;
   tFblResult     result;

   vuint8         byteIdx;
   vuint8         validityFlags[kEepSizeValidityFlags];
   vuint8         validityCheck[kEepSizeValidityFlags];

   byteIdx = (vuint8)(descriptor.blockNr >> 0x03u);
   validityMask = (vuint8)(0x01u << (descriptor.blockNr & 0x07u));

   result = kFblFailed;

   if (((ApplFblNvReadValidityFlags(validityFlags))) == kFblOk)
   {
      if (mode == kEepValidateBlock)
      {
         validityFlags[byteIdx] &= FblInvert8Bit(validityMask);
      }
      else
      {
         validityFlags[byteIdx] |= validityMask;
      }

      /* Modify validity flags */
      if (ApplFblNvWriteValidityFlags(validityFlags) == kFblOk)
      {
         /* Read modified flags */
         if (ApplFblNvReadValidityFlags(validityCheck) == kFblOk)
         {
            /* Check if flags were written correctly */
            if (validityCheck[byteIdx] == validityFlags[byteIdx])
            {
               result = kFblOk;
            }
         }
      }
   }
   return result;
}

#if defined( FBL_ENABLE_PRESENCE_PATTERN )

/***********************************************************************************************************************
 *  ApplFblGetPresencePatternBaseAddress
 **********************************************************************************************************************/
/*! \brief         Calculates the base address of the presence pattern and mask.
 *  \pre           LBT is present
 *  \param[in]     blockNr Logical block number
 *  \param[in,out] pPresPtnAddr Pointer to RAM location to place the address to the begin of presence pattern
 *  \param[in,out] pPresPtnLen Pointer to the RAM location where the length of the presence pattern shall be stored to
 *  \return        memSegment of the presence pattern location or -1 in case of an error
 **********************************************************************************************************************/
static vsint16 ApplFblGetPresencePatternBaseAddress( vuint8 blockNr, IO_PositionType * pPresPtnAddr, IO_SizeType * pPresPtnLen )
{
   IO_PositionType   presPtnEndAddress;
   IO_SizeType       presPtnLength;

# if defined( FBL_ENABLE_DEBUG_STATUS )
   if ((0xFFFFFFFFu - FblLogicalBlockTable.logicalBlock[blockNr].blockLength) < FblLogicalBlockTable.logicalBlock[blockNr].blockStartAddress)
   {
      /* Overflow if block start address + block length is  *
       * calculated - behavior has to be checked carefully. */
      while (1)
      {
         ;
      }
   }
# endif /* FBL_ENABLE_DEBUG_STATUS */

    presPtnEndAddress = FblLogicalBlockTable.logicalBlock[blockNr].blockStartAddress + FblLogicalBlockTable.logicalBlock[blockNr].blockLength;
    /* Read the memory segment address */
    memSegment = FblMemSegmentNrGet( (presPtnEndAddress - (kFblPresencePatternSize*2)) );
   /* Check if a valid memory segment in the flash block table was found */
   if (memSegment >= 0)
   {
      /* Get the flash segment length of the device */
      /* Adjust if necessary (device's segment size is smaller than presence pattern size) */
      if (MemDriver_SegmentSize < kFblPresencePatternSize)  /* PRQA S 3325 */ /* MD_FblKbApi_3325 */
      {  /* PRQA S 3201 */ /* MD_FblKbApi_3201 */
         presPtnLength = kFblPresencePatternSize;
      }
      else
      {  /* PRQA S 3201 */ /* MD_FblKbApi_3201 */
         presPtnLength = MemDriver_SegmentSize;
      }
      /* Put results into arguments */
      *pPresPtnAddr = (presPtnEndAddress - (presPtnLength * 2));
      *pPresPtnLen  = presPtnLength;
   }

   return memSegment;
}

/***********************************************************************************************************************
 *  ApplFblModuleSetPresence
 **********************************************************************************************************************/
/*! \brief       Writes the presence pattern into the flash memory.
 *  \details     The location of the presence pattern will be taken from the logical block descriptor.
 *  \pre         Module programming successfully performed and checksum calculation succeeded.
 *  \param[in]   blockDescriptor Pointer to the logical block descriptor
 *  \return      kFblOk: Presence pattern successfully set, kFblFailed: Error writing presence pattern
 **********************************************************************************************************************/
static tFblResult ApplFblSetModulePresence( tBlockDescriptor * blockDescriptor )
{
   IO_PositionType            presPtnAddress;
   IO_SizeType                presPtnLen;
   IO_ErrorType               readResult;
   vuint32                    i;
   tFblResult                 result;
   tFblpresPtnAlignedBuffer   flashHeader;
   vuint8 *                   pFlashHeader;

   /* Set presence pattern for this module */

   /* Calculate location of presence pattern.           */
   /* Note that the end of the block descriptor already */
   /* points to the presence pattern itself.            */
   memSegment = ApplFblGetPresencePatternBaseAddress(blockDescriptor->blockNr, &presPtnAddress, &presPtnLen);

   if (memSegment >= 0)
   {
      /* FlashWrite requires an aligned address to RAM */
      pFlashHeader = flashHeader.data;

      /* Copy presence pattern to RAM buffer */
      for (i = 0u; i < kFblPresencePatternSize; i++)
      {
         pFlashHeader[i] = blockPresencePattern[i];
      }
#if ( FBL_PP_SEGMENT_SIZE > kFblPresencePatternSize )
      /* Clear remaining buffer if any */
      for (i = kFblPresencePatternSize; i < FBL_PP_SEGMENT_SIZE; i++)
      {
         pFlashHeader[i] = 0;
      }
#endif
      (void)FblRealTimeSupport();

      /* Write presence pattern */
      if (!ApplFblWritePattern(pFlashHeader, presPtnLen, presPtnAddress))
      {
         return kFblFailed;
      }

      /* Read mask pattern */
      readResult = ApplFblReadPattern(pFlashHeader, (presPtnAddress+presPtnLen));
      if ((readResult != IO_E_OK) && (readResult != IO_E_ERASED))
      {
         return kFblFailed;
      }

      /* Check if the erase pattern is set correctly */
      for (i = 0u; i < kFblPresencePatternSize; i++)
      {
         if (pFlashHeader[i] != FBL_FLASH_DELETED)
         {
            return kFblFailed;
         }
      }

      /* Return value depends on the Check if presence pattern is now valid */
      result = ApplFblChkModulePresence(blockDescriptor);
   }
   else
   {
      /* Memory segment for the presence pattern address not found */
      result = kFblFailed;
   }

   return result;
}  /* PRQA S 2006 */ /* MD_MSR_14.7 */

/***********************************************************************************************************************
 *  ApplFblModuleClrPresence
 **********************************************************************************************************************/
/*! \brief       Sets the mask presence pattern in flash memory to invalidate the block.
 *  \details     The location of the presence pattern will be taken from the logical block descriptor.
 *  \pre         Module shall be marked as invalid now.
 *  \param[in]   blockDescriptor Pointer to the logical block descriptor
 *  \return      kFblOk: Mask for invalidation successfully written, kFblFailed: Error writing invalidation mask
 **********************************************************************************************************************/
static tFblResult ApplFblClrModulePresence( tBlockDescriptor * blockDescriptor )
{
   tFblResult                 result = kFblOk;
   vuint32                    i;
   IO_PositionType            presPtnAddress;
   IO_SizeType                presPtnLen;
   tFblpresPtnAlignedBuffer   flashHeader;
   vuint8 *                   pFlashHeader;

   /* Calculate location of presence pattern.           */
   /* Note that the end of the block descriptor already */
   /* points to the presence pattern itself.            */
   memSegment = ApplFblGetPresencePatternBaseAddress(blockDescriptor->blockNr, &presPtnAddress, &presPtnLen);

   /* valid segment found */
   if (memSegment >= 0)
   {
     /* FlashWrite requires an aligned address to RAM */
     pFlashHeader = flashHeader.data;

      /* Check if presence pattern is set for this module */
      /* Only clear and remove the marker if not already disabled */
      if (ApplFblChkModulePresence(blockDescriptor) == kFblOk)
      {
         /* Copy presence pattern to RAM buffer */
         for (i = 0u; i < kFblPresencePatternSize; i++)
         {
            /* Set the inverse of the presence pattern */
            pFlashHeader[i] = FblInvert8Bit(blockPresencePattern[i]);
         }
#if ( FBL_PP_SEGMENT_SIZE > kFblPresencePatternSize )
         /* Clear remaining buffer if any */
         for (i = kFblPresencePatternSize; i < FBL_PP_SEGMENT_SIZE; i++)
         {
            pFlashHeader[i] = 0;
         }
#endif
         /* Now write them */
         if (!ApplFblWritePattern(pFlashHeader, presPtnLen, (presPtnAddress + presPtnLen)))
         {
            /* Writing the mask has failed. */
            result = kFblFailed;
         }
         (void)FblRealTimeSupport();
      }
   }
   else
   {
      /* Check if presence pattern is set for this module */
      /* Only clear and remove the marker if not already disabled */
      if (ApplFblChkModulePresence(blockDescriptor)==kFblOk)
      {
         result = kFblFailed;
      }
   }

   return result;
}

/***********************************************************************************************************************
 *  ApplFblChkModulePresence
 **********************************************************************************************************************/
/*! \brief       Checks if mask and value of the presence pattern are set for a valid module.
 *  \details     The location of the presence pattern and mask is taken from the logical block table in FBL_MTAB.C.
 *  \param[in]   blockDescriptor Pointer to the logical block descriptor
 *  \return      kFblOk:     Presence pattern are set and Mask value are OK,
 *               kFblFailed: Presence pattern not set or mask flag not correct.
 **********************************************************************************************************************/
/* PRQA S 3673 1 */ /* MD_FblKbApi_3673 */
tFblResult ApplFblChkModulePresence( tBlockDescriptor * blockDescriptor )
{
   vuint8           flashPresPtn[kFblPresencePatternSize];
   vuint8           flashPresMsk[kFblPresencePatternSize];
   IO_PositionType  presPtnAddress;
   IO_SizeType      presPtnLen;
   IO_ErrorType     readResult;
   vuint32          i;
   tFblResult       result;

   result = kFblOk;

   /* Calculate location of presence pattern.           */
   /* Note that the end of the block descriptor already */
   /* points to the presence pattern itself.            */
   memSegment = ApplFblGetPresencePatternBaseAddress(blockDescriptor->blockNr, &presPtnAddress, &presPtnLen);

   if (memSegment < 0)
   {
      result = kFblFailed;
   }

   if (kFblOk == result)
   {
      /* Read presence pattern value */
      readResult = ApplFblReadPattern(flashPresPtn, presPtnAddress);
      if ((readResult != IO_E_OK) && (readResult != IO_E_ERASED))
      {
         /* Read has failed */
         result = kFblFailed;
      }
   }

   if (kFblOk == result)
   {
      /* Read presence pattern mask */
      readResult = ApplFblReadPattern(flashPresMsk, (presPtnAddress + presPtnLen));
      if ((readResult != IO_E_OK) && (readResult != IO_E_ERASED))
      {
         /* Read has failed */
         result = kFblFailed;
      }
   }

   if (kFblOk == result)
   {
      for (i = 0u; ((i < kFblPresencePatternSize) && (kFblOk == result)); i++)
      {
         /* Compare the PP-value against the expected one */ /* PRQA S 3353 2 */ /* MD_FblKbApi_3353 */
         if (   (flashPresPtn[i] != blockPresencePattern[i])
             || (flashPresMsk[i] != FBL_FLASH_DELETED))
         {
            /* PP value is different or MASK does not have its expected value */
            result = kFblFailed;
         }
      }
   }

   return result;
}

/***********************************************************************************************************************
 *  ApplFblAdjustLbtBlockData
 **********************************************************************************************************************/
/*! \brief         This function is called whenever the bootloader queries the range for the logical blocks.
 *  \details       This info is typically stored in fbl_mtab.c and generated from GENy. This function
 *                 can be used to spare a range from the LBT at runtime that shall not be flashed.
 *                 The purpose of this function is mainly to spare two flashable
 *                 segments at the very end to store the mask and pattern for validation,
 *                 so that they can't overwritten during a download.
 *                 | programmable data | mask | pattern |
 *  \param[in,out] blockDescriptor Pointer to LBT-Descriptor
 **********************************************************************************************************************/
tFblResult ApplFblAdjustLbtBlockData( tBlockDescriptor * blockDescriptor )
{
   IO_PositionType  presPtnAddress;
   IO_SizeType      presPtnLen;
   tFblResult       result;

   /* Calculate location of presence pattern.           */
   /* Note that the end of the block descriptor already */
   /* points to the presence pattern itself.            */
   memSegment = ApplFblGetPresencePatternBaseAddress(blockDescriptor->blockNr, &presPtnAddress, &presPtnLen);

   if (memSegment >= 0)
   {
      /* Reduce length for presence pattern and mask */
      blockDescriptor->blockLength -= (presPtnLen*2);
      result = kFblOk;
   }
   else
   {
      result = kFblFailed;
   }

   return result;
}
#endif /* FBL_ENABLE_PRESENCE_PATTERN */

/***********************************************************************************************************************
 *  ApplFblGetModuleHeaderAddress
 **********************************************************************************************************************/
/*! \brief       This function has to return the address of the module header.
 *  \pre         Logical blocks need a module header
 *  \param[in]   blockNr
 *  \return      Address of module header information structure
 **********************************************************************************************************************/
tFblAddress ApplFblGetModuleHeaderAddress( vuint8 blockNr )
{
   tFblAddress moduleHeaderAddr;

   /* The module header (containing the software identification information   *
    * and the interface version for consistency check) may be placed          *
    * at e.g.                                                                 *
    * - the beginning of the logical block (offset = +0x00 ) or               *
    * - with an offset to the beginning of the block (offset = +0xXX)         *
    * - with an offset to the end of the block (offset = -0xXX)               *
    * To provide an application specific flexibility, this function can       *
    * return the address depending on the block type and -number.             */

   /* Determine the module header address: */
   if (blockNr == 0x00)
   {
      /* This is just a demonstration, that e.g. a certain block  *
       * can be treated different (with a certain offset):        */
      moduleHeaderAddr = FblLogicalBlockTable.logicalBlock[blockNr].blockStartAddress + 0x500;
   }
   else
   {
      /* For all other blocks: */
      moduleHeaderAddr = FblLogicalBlockTable.logicalBlock[blockNr].blockStartAddress;
   }

   return moduleHeaderAddr;
}

/***********************************************************************************************************************
 *  ApplFblExtProgRequest
 **********************************************************************************************************************/
/*! \brief       Function is called on power-on reset to check if an external programming request exists.
 *  \details     If the flag is set, the flag is cleared and the function returns kProgRequest.
 *  \return      kProgRequest = external programming request, kNoProgRequest = programming request flag not set
 **********************************************************************************************************************/
tFblProgStatus ApplFblExtProgRequest( void )
{
   tFblProgStatus progStatus;
# if defined( FBL_ENABLE_FBL_START )
   /* Check a pattern in uninitialized RAM to see if this
    * is a reprogramming request from the application */
   if (FblChkFblStartMagicFlag())
   {
      /* Clear immediately the request */
      FblClrFblStartMagicFlag();

      progStatus = kProgRequest;
   }
# else /* ! FBL_ENABLE_FBL_START */
   vuint8 progReqFlag;

   /* Check the reprogramming request flag */
   if (ApplFblNvReadProgReqFlag(&progReqFlag) == kFblOk)
   {
      if (progReqFlag == kEepFblReprogram)
      {
         /* Reprogramming flag is set, clear flag */
         progReqFlag = 0u;
         (void)ApplFblNvWriteProgReqFlag(&progReqFlag);  /* PRQA S 3425 */ /* MD_FblKbApiOem_3425 */

         progStatus = kProgRequest;
      }
      else /* != kEepFblReprogram */
      {
         progStatus = kNoProgRequest;
      }
   }
# endif /* ! FBL_ENABLE_FBL_START */
   else
   {
      progStatus = kNoProgRequest;
   }

   return progStatus;
}

/***********************************************************************************************************************
 *  ApplFblValidateBlock
 **********************************************************************************************************************/
/*! \brief       Function is called after a successful download (CRC check was successful) to validate the logical block
 *  \pre         Logical block must be successfully downloaded
 *  \param[in]   blockDescriptor Block descriptor structure
 *  \return      kFblOk = validation successfully performed, kFblFailed = validation failed
 **********************************************************************************************************************/
tFblResult ApplFblValidateBlock( tBlockDescriptor blockDescriptor )
{
   tFblResult result;

   /* Initialize variables */
   result = kFblOk;

#if defined( FBL_ENABLE_PRESENCE_PATTERN )
   /* Save block descriptor of currently validated block.
    * The block descriptor will be used to validate the application. */
   currentValidatedBlock = blockDescriptor;
#endif /* FBL_ENABLE_PRESENCE_PATTERN */

   /* Set current block valid */
   if (ApplFblChgBlockValid(kEepValidateBlock, blockDescriptor) != kFblOk)
   {
      result = kFblFailed;
   }
 
   return result;
}

/***********************************************************************************************************************
 *  ApplFblInvalidateBlock
 **********************************************************************************************************************/
/*! \brief       Whenever the bootloader needs to delete data, this function is called
 *               to invalidate the current logical block.
 *  \param[in]   blockDescriptor Block descriptor structure
 *  \return      kFblOk: invalidation successfully performed, kFblFailed: invalidation failed
 **********************************************************************************************************************/
tFblResult ApplFblInvalidateBlock( tBlockDescriptor blockDescriptor )
{
   tFblResult result;
   /* Invalidate application validity flag */
   result = ApplFblInvalidateApp();

   /* Erase valid flag of current block */
   if (result == kFblOk)
   {
      result = ApplFblChgBlockValid(kEepInvalidateBlock, blockDescriptor);
   }

   return result;
}

/***********************************************************************************************************************
 *  ApplFblIsValidApp
 **********************************************************************************************************************/
/*! \brief       Function is called on power-up to check if the application is successfully validated or not.
 *  \details     Returns kApplValid if application is valid (all mandatory blocks available) and application start is
 *               allowed. Otherwise it returns kApplInvalid.
 **********************************************************************************************************************/
tApplStatus ApplFblIsValidApp( void )
{
   tApplStatus applicationStatus;
#if defined( FBL_ENABLE_PRESENCE_PATTERN )
   vuintx currentBlockNr;
   tBlockDescriptor tempBlockDescriptor;
#else
   vuint8 applValidity;
#endif /* FBL_ENABLE_PRESENCE_PATTERN */

   /* Initialize variables */
   applicationStatus = kApplInvalid;

#if defined( FBL_ENABLE_PRESENCE_PATTERN )
   /* Read validity from application validity pattern
    * Scan all logical blocks until one block with application valid flag is found */
   currentBlockNr = FBL_MTAB_NO_OF_BLOCKS;
   while ((currentBlockNr > 0u) && (applicationStatus == kApplInvalid))
   {
      currentBlockNr--;
      tempBlockDescriptor = FblLogicalBlockTable.logicalBlock[currentBlockNr];
      if (ApplFblChkModulePresence(&tempBlockDescriptor) == kFblOk)
      {
         applicationStatus = kApplValid;
      }
   }
#else
   /* Read validity from NV-memory */
   if (ApplFblNvReadApplValidity(&applValidity) == kFblOk)
   {
      if (applValidity == kEepApplConsistent)
      {
         applicationStatus = kApplValid;
      }
   }
#endif /* FBL_ENABLE_PRESENCE_PATTERN */

#if ( FBL_PROJECT_STATE >= FBL_INTEGRATION )
   if ((applicationStatus == kApplValid) && (FblCheckBootVectTableIsValid()))
   {
      /* Application is valid but contains an APPLVECT_FROM_BOOT.
       * Therefore it is not possible to jump to startup code of application.
       * Probably the Bootloader was reprogrammed with a debugger. */
      applicationStatus = kApplInvalid;
   }
#endif /* FBL_PROJECT_STATE >= FBL_INTEGRATION */

   return applicationStatus;
}  /* PRQA S 2006 */ /* MD_MSR_14.7 */

/***********************************************************************************************************************
 *  ApplFblErrorNotification
 **********************************************************************************************************************/
/*! \brief       Call-back function for diagnostic trouble code entries.
 *  \details     This function is called whenever a flash programming error occurred.
 *  \param[in]   errorType The error type
 *  \param[in]   errorCode The error code
 **********************************************************************************************************************/
void ApplFblErrorNotification( tFblErrorType errorType, tFblErrorCode errorCode )
{
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )
   /* Parameters not used: avoid compiler warning */ /* PRQA S 3112 2 */ /* MD_MSR_14.2 */
   (void)errorType;
   (void)errorCode;
#endif
}

/***********************************************************************************************************************
 *  ApplFblIncProgCounts
 **********************************************************************************************************************/
/*! \brief       Increment programming counter
 *  \param[in]   blockDescriptor Block descriptor
 *  \return      kFblOk / kFblFailed
 **********************************************************************************************************************/
tFblResult ApplFblIncProgCounts( tBlockDescriptor blockDescriptor )
{
   tFblApnvProgCountType progCounts;
   vuint8 nvBuffer[sizeof(tFblApnvProgCountType)];
   tFblResult status;

   status = (tFblResult)ApplFblNvReadProgCounter(blockDescriptor.blockNr, nvBuffer);
   progCounts = (tFblApnvProgCountType)FblMemGetInteger(sizeof(nvBuffer), nvBuffer);

   if (status == kFblOk)
   {
      /* Value is stored inverted because of erase value */
      progCounts = FblInvert16Bit(progCounts);
      progCounts++;
      progCounts = FblInvert16Bit(progCounts);

      FblMemSetInteger(sizeof(nvBuffer), progCounts, nvBuffer);
      status = (tFblResult)ApplFblNvWriteProgCounter(blockDescriptor.blockNr, nvBuffer);
   }

   return status;
}

/***********************************************************************************************************************
 *  ApplFblGetProgCounts
 **********************************************************************************************************************/
/*! \brief       Get programming counter
 *  \param[in]   blockDescriptor Block descriptor
 *  \param[in]   progCounts The programming counter
 *  \return      kFblOk / kFblFailed
 **********************************************************************************************************************/
tFblResult ApplFblGetProgCounts( tBlockDescriptor blockDescriptor, V_MEMRAM1 vuint16 V_MEMRAM2 V_MEMRAM3 * progCounts)
{
   tFblResult status;
   vuint8 nvBuffer[sizeof(tFblApnvProgCountType)];
   tFblApnvProgCountType tempCount;

   status = (tFblResult)ApplFblNvReadProgCounter(blockDescriptor.blockNr, nvBuffer);
   tempCount = (tFblApnvProgCountType)FblMemGetInteger(sizeof(nvBuffer), nvBuffer);
   tempCount = FblInvert16Bit(tempCount);

   *progCounts = (vuint16)tempCount;

   return status;
}

/***********************************************************************************************************************
 *  ApplFblIncProgAttempts
 **********************************************************************************************************************/
/*! \brief       Increment programming attempt counter
 *  \param[in]   blockDescriptor Block descriptor
 *  \return      kFblOk / kFblFailed
 **********************************************************************************************************************/
tFblResult ApplFblIncProgAttempts( tBlockDescriptor blockDescriptor )
{
   tFblApnvProgCountType progAttempts;
   vuint8 nvBuffer[sizeof(tFblApnvProgCountType)];
   tFblResult status;

   status = (tFblResult)ApplFblNvReadProgAttempts(blockDescriptor.blockNr, nvBuffer);
   progAttempts = (tFblApnvProgCountType)FblMemGetInteger(sizeof(nvBuffer), nvBuffer);

   if (status == kFblOk)
   {
      /* Value is stored inverted because of erase value */
      progAttempts = FblInvert16Bit(progAttempts);
      progAttempts++;
      progAttempts = FblInvert16Bit(progAttempts);

      FblMemSetInteger(sizeof(nvBuffer), progAttempts, nvBuffer);
      status = (tFblResult)ApplFblNvWriteProgAttempts(blockDescriptor.blockNr, nvBuffer);
   }

   return status;
}

/***********************************************************************************************************************
 *  ApplFblGetProgAttempts
 **********************************************************************************************************************/
/*! \brief       Get programming attempt counter
 *  \param[in]   blockDescriptor Block descriptor
 *  \param[out]  progAttempts The returned programming attempts
 *  \return      kFblOk / kFblFailed
 **********************************************************************************************************************/
tFblResult ApplFblGetProgAttempts( tBlockDescriptor blockDescriptor, V_MEMRAM1 vuint16 V_MEMRAM2 V_MEMRAM3 * progAttempts )
{
   tFblResult status;
   vuint8 nvBuffer[sizeof(tFblApnvProgCountType)];
   tFblApnvProgCountType tempCount;

   status = (tFblResult)ApplFblNvReadProgAttempts(blockDescriptor.blockNr, nvBuffer);
   tempCount = (tFblApnvProgCountType)FblMemGetInteger(sizeof(nvBuffer), nvBuffer);
   tempCount = FblInvert16Bit(tempCount);
   *progAttempts = (vuint16)tempCount;

   return status;
}

#if defined( SEC_VER_DISABLE_CRC_TOTAL )
#else
/***********************************************************************************************************************
 *  ApplFblWriteCRCTotal
 **********************************************************************************************************************/
/*! \brief       Store CRC total. String buffer used to avoid little/big endian permutation.
 *  \param[in]   blockDescriptor Block descriptor
 *  \param[in]   crcStart Start address of CRC calculation
 *  \param[in]   crcLength Length of CRC calculation
 *  \param[in]   crcValue The CRC value
 *  \return      kFblOk / kFblFailed
 **********************************************************************************************************************/
tFblResult ApplFblWriteCRCTotal( V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor, vuint32 crcStart, vuint32 crcLength, vuint32 crcValue )
{
   tFblResult status;
   vuint8 strConversionBuffer[4u];

   status = kFblOk;

# if ( kEepSizeCRCStart  != 4u ) || \
     ( kEepSizeCRCLength != 4u ) || \
     ( kEepSizeCRCValue  != 4u )
#  error "Error in FBL_APNV.C: Configuration error (kEepSizeCRC... != 4)"
# endif

   FblMemSetInteger(kEepSizeCRCStart, crcStart, strConversionBuffer);
   status |= (tFblResult)ApplFblNvWriteCRCStart(blockDescriptor->blockNr, strConversionBuffer);

   FblMemSetInteger(kEepSizeCRCLength, crcLength, strConversionBuffer);
   status |= (tFblResult)ApplFblNvWriteCRCLength(blockDescriptor->blockNr, strConversionBuffer);

   FblMemSetInteger(kEepSizeCRCValue, crcValue, strConversionBuffer);
   status |= (tFblResult)ApplFblNvWriteCRCValue(blockDescriptor->blockNr, strConversionBuffer);

   return status;
}
#endif /* SEC_VER_DISABLE_CRC_TOTAL */

/***********************************************************************************************************************
 *  ApplFblValidateApp
 **********************************************************************************************************************/
/*! \brief       Function is called after a successful download to validate a file.
 *  \pre         Complete file must be successfully downloaded
 *  \return      kFblOk = validation successfully performed, kFblFailed = validation failed
 **********************************************************************************************************************/
tFblResult ApplFblValidateApp( void )
{
   tFblResult result;
# if defined( FBL_ENABLE_PRESENCE_PATTERN )
# else
   vuint8 applValidity;
# endif /* FBL_ENABLE_PRESENCE_PATTERN */

# if defined( FBL_ENABLE_PRESENCE_PATTERN )
   /* Set presence pattern in last flashed logical block. */
   result = ApplFblSetModulePresence(&currentValidatedBlock);
# else
   applValidity = kEepApplConsistent;
   result = (tFblResult)ApplFblNvWriteApplValidity(&applValidity);
# endif /* FBL_ENABLE_PRESENCE_PATTERN */

   return result;
}

/***********************************************************************************************************************
 *  ApplFblInvalidateApp
 **********************************************************************************************************************/
/*! \brief       Function is called before erasure of the application
 *  \return      kFblOk = invalidation successfully performed, kFblFailed = invalidation failed
 **********************************************************************************************************************/
tFblResult ApplFblInvalidateApp( void )
{
   tFblResult result;
# if defined( FBL_ENABLE_PRESENCE_PATTERN )
   vuintx currentBlockNr;
   tBlockDescriptor tempBlockDescriptor;
# else
   vuint8 applValidity;
# endif /* FBL_ENABLE_PRESENCE_PATTERN */

# if defined( FBL_ENABLE_PRESENCE_PATTERN )
   /* Loop over all logical blocks to invalidate application flag */
   currentBlockNr = 0u;
   result = kFblOk;
   while ((currentBlockNr < FBL_MTAB_NO_OF_BLOCKS) && (result == kFblOk))
   {
      tempBlockDescriptor = FblLogicalBlockTable.logicalBlock[currentBlockNr];
      result = ApplFblClrModulePresence(&tempBlockDescriptor);

      /* Prepare index for next loop */
      currentBlockNr++;
   }
# else
   applValidity = kEepApplInconsistent;
   result = (tFblResult)ApplFblNvWriteApplValidity(&applValidity);
# endif /* FBL_ENABLE_PRESENCE_PATTERN */

   return result;
}

/* module specific MISRA deviations:
   MD_FblKbApi_3201:
      Reason: Configuration or platform specific dependent unreachable code.
      Risk: Incorrect behavior depend on settings.
      Prevention: No prevention required.

   MD_FblKbApi_3325:
      Reason: This control expression is always true or false depend on configuration aspect and used platform specific
              implementation.
      Risk: Incorrect behavior depend on settings.
      Prevention: No prevention required.

   MD_FblKbApi_3353:
      Reason: Variable is set in an other function via call-by-reference.
      Risk: No identifiable risk.
      Prevention: No prevention required.

   MD_FblKbApi_3673:
      Reason: Function is part of the bootloader API which provides the possibility to influence the bootloader behavior
              by modifying the output parameters. The provided default implementation of the function doesn't
              necessarily make use of all available parameters.
      Risk: The parameter value might be changed unintentionally, thus causing malfunction in the calling instance.
      Prevention: Provide detailed information about the API and its usage in the user documentation.

   MD_FblKbApiOem_3315:
      Reason: Example code shows how the function can be implemented and is therefore left empty.
      Risk: No identifiable risk.
      Prevention: No prevention required.

   MD_FblKbApiOem_3353:
      Reason: Data is initialize by a function. Data is initialized in all cases.
      Risk: No identifiable risk.
      Prevention: No prevention required.

   MD_FblKbApiOem_3425:
      Reason: The WrapNv call uses the ternary operator to remap the return value of IO_E_OK to kFblOk. As both of
       them are defined to the value zero the remapping has no side affects.
      Risk: No identifiable risk.
      Prevention: No prevention required.


*/

/***********************************************************************************************************************
 *  FBL_APNV.C
 **********************************************************************************************************************/
