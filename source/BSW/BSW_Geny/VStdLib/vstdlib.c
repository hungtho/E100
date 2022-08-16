/* Kernbauer Version: 1.16 Konfiguration: VStdLib Erzeugungsgangnummer: 1 */


/**********************************************************************************************************************
| Project Name: vstdlib library
|    File Name: vstdlib_ll.c
|
|  Description        : lowlevel part of the implementation of standard 
|                       Vector functions.
|               PPC and MPC families specific implementation
|                               
|----------------------------------------------------------------------------------------------------------------------
|               C O P Y R I G H T
|----------------------------------------------------------------------------------------------------------------------
|   Copyright (c) by Vector Informatik GmbH.     All rights reserved.
|
|   This software is copyright protected and proprietary to 
|   Vector Informatik GmbH. Vector Informatik GmbH grants to you 
|   only those rights as set out in the license conditions. All 
|   other rights remain with Vector Informatik GmbH.
|
|----------------------------------------------------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|----------------------------------------------------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     ------------------------------------------------------------------------------
| Ml           Patrick Markl             Vector Informatik GmbH
| BWR          Brandon Root              Vector CANtech Inc.
| Ces          Senol Cendere             Vector Informatik GmbH
| Ou           Mihai Olariu              Vector Informatik GmbH
| Rse          Robert Schelkle           Vector Informatik GmbH
| Her          Peter Herrmann            Vector Informatik GmbH
| Zam          Artjom Zabirko            Vector Informatik GmbH
|----------------------------------------------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|----------------------------------------------------------------------------------------------------------------------
| Date       Version   Author  Description
|----------  --------  ------  ----------------------------------------------------------------------------------------
| 2005-12-12   01.00.00   Ml     Creation
| 2006-08-05   01.01.00   Ml     new LL template
| 2006-08-21   01.02.00   Ml     Added C_COMP_GAIO_MPC55XX 
| 2007-06-06   01.03.00   BWR    ESCAN21022 Support for Metrowerks compiler
| 2007-10-24   01.04.00   Ces    ESCAN00022943: Support interrupt disable/restore handling for MPC55xx
|                                ESCAN00022947: Support compiler Green Hills MULTI
| 2008-01-07   01.05.00   Ces    ESCAN00023934: Support instruction set mode VLE
| 2008-01-14   01.06.00   Ces    ESCAN00024022: Support C_COMP_GHS_MPC55XX_FLEXCAN2
|                                               Support C_COMP_GAIO_MPC55XX_FLEXCAN2
|                                               Support C_COMP_DIABDATA_MPC55XX_FLEXCAN2
| 2008-05-15   01.07.00   Ces    ESCAN00026895: Update LL template and HL code
| 2008-08-05   01.08.00   Ces                   Update HL code to support Lib-Version-Check
| 2008-08-14   01.09.00   Ces                   Update HL code due to changes in Lib-Version-Check
| 2009-02-02   01.10.00   Ou     ESCAN00032711: Take over the implementation from  VStdLib_Mpc5x00 into VStdLib_Mpc
|                         Ou     ESCAN00032712: Support new compiler switch: C_COMP_MTRWRKS_MPC5X00_MSCAN
| 2009-07-01   01.11.00   Ces    ESCAN00036137: Support compiler Freescale/Metrowerks CodeWarrior for PowerArchitecture
| 2009-07-30   01.12.00   Ces                   Update HLL part
| 2009-09-14   01.12.01   Ces                   Change C_COMP_DIAB_ to C_COMP_DIABDATA_
| 2010-02-11   01.12.02   Ces                   Change asm to __asm for Metrowerks CodeWarrior
| 2010-04-30   01.13.00   Ces    ESCAN00042470: Replace assembler macros by C functions
|                                ESCAN00042983: Prevent compiler warnings caused by missing function protoypes
|                                               Support compiler GNU for MPC55xx and MPC56xx
|                                               Support Interrupt Lock Level for MPC55xx and MPC56xx
| 2010-06-28  01.13.01    Ces                   C_COMP_DIAB_ was used instead C_COMP_DIABDATA_
| 2010-07-30  01.13.02    Ces                   Update HLL part
| 2010-10-05  01.13.03    Ces    ESCAN00045360: Compiler reports warning due to uninitialized variable used in assembler code
| 2010-10-25  01.13.04    Ces    ESCAN00046460: Reduce inline assembler instructions and make code independent of instruction set
| 2010-11-15  01.14.00    Ces    ESCAN00046925: Prevent inlining of functions VStdGlobalIntDisable and VStdGlobalIntRestore 
| 2011-01-28  01.14.01    Rse    ESCAN00048282: Compiler reports warning, because unused functions exist
| 2011-06-06  01.15.00    Rse    ESCAN00051645: Support compiler DiabData in the version v5.4.0.0
|                                               Support C_COMP_GHS_PPC
| 2012-07-03  01.16.00    Her    ESCAN00059846: Support C_PROCESSOR_MPC5746M with C_COMP_GNU_MPC5700_MCAN
| 2013-02-06  01.17.00    Rse    ESCAN00064876: Support MPC5700 derivatives with FlexCAN3 for GHS, GNU, METROWERKS and DIABDATA
|                                ESCAN00047776: Compiler warning: missing return statement at end of non-void function "VStdGlobalIntDisable"
| 2013-04-03  01.18.00    Her    ESCAN00066641: Support GlobalInterruptDisabe/Restore with C_COMP_GNU_MPC5700_MCAN
| 2013-06-27  01.18.01    Rse    ESCAN00068527: Diverse compile errors occur
| 2013-10-09  01.19.00    Rse    ESCAN00070942: DiabData only: Support workaround for compiler defect WIND00404456
| 2013-10-11  01.20.00    Her    ESCAN00071042: Support MPC5700 derivatives with MCAN for GHS
|                         Her    ESCAN00072545: Support PC5800XX derivative with FlexCan3 for DiabData
| 2014-04-22  01.21.00    Zam    ESCAN00075146: Support MPC55XX derivative with FlexCan2 for Gnu
|********************************************************************************************************************/

/* ********************************************************************************************************************
|
| Project Name : vstdlib library
|    File Name : vstdlib_HL.c
|
|  Description : Highlevel part of the implementation of standard Vector functions
|                               
|----------------------------------------------------------------------------------------------------------------------
|               C O P Y R I G H T
|----------------------------------------------------------------------------------------------------------------------
|   Copyright (c) by Vector Informatik GmbH.     All rights reserved.
|
|   This software is copyright protected and proprietary to 
|   Vector Informatik GmbH. Vector Informatik GmbH grants to you 
|   only those rights as set out in the license conditions. All 
|   other rights remain with Vector Informatik GmbH.
|
|----------------------------------------------------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|----------------------------------------------------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     ------------------------------------------------------------------------------
| Ml           Patrick Markl             Vector Informatik GmbH
| HH           Hartmut Hoerner           Vector Informatik GmbH
| Ms           Gunnar Meiss              Vector Informatik GmbH
| Et           Thomas Ebert              Vector Informatik GmbH
| Bus          Sabine Buecherl           Vector Informatik GmbH
| Hs           Hannes Haas               Vector Informatik GmbH
| BWR          Brandon Root              Vector CANtech Inc.
| Ard          Thomas Arnold             Vector Informatik GmbH
|----------------------------------------------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|----------------------------------------------------------------------------------------------------------------------
| Date       Version   Author  Description
|----------  --------  ------  ----------------------------------------------------------------------------------------
|2003-09-06  00.01.00    Ml     - Creation
|                        Ml     - Added HC12 Cosmic
|2003-10-07  00.02.00    Ml/HH  - v_lib input merged
|2004-04-10  00.03.00    Ml     - Added headerfile
|                        Ml     - Added HC08 Cosmic
|                        Ml     - removed channel dependence for assertions
|                        Ml     - Added function to retrieve the IRQ state
|                        Ml     - Added VSTD_FULL_LIB_SUPPORT switch
|2004-04-27  01.00.00    Ml     - resolved issues found in code inspection
|2004-05-17  01.01.00    Ml     - added assertion
|                        Ml     - added define section
|                        Ml     - changed memoryqualifier
|                        Ml     - changed bugfix into releaseversion
|                        Ml     - added check for correct v_def.h version
|2004-05-18  01.02.00    Ms/HH  - changed memory qualifier concept
|2004-06-01  01.03.00    Ml     - corrected define for IRQ functions
|2004-08-06  01.04.00    Ml     - Split of library into HL and LL
|2004-08-18  01.05.00    Ml     - Added function qualifier
|2004-09-06  01.06.00    Ml     - ESCAN00009316: no changes
|2004-09-27  01.07.00    Ml     - no changes
|                        Ml     - changed namingconvention     
|2004-09-29  01.08.00    Et     - ESCAN00009692: split VStdMemCpy in VStdRamMemCpy and VStdRomMemCpy   
|2004-10-01  01.09.00    Ml     - ESCAN00009731: usage of standard type qualifiers
|2004-10-26  01.10.00    Ml     - ESCAN00010000: LL parts are split into HW specific files
|2004-11-09  01.11.00    Ml     - added VStd_LLPostInclude
|2004-11-15  01.12.00    Ml     - ESCAN00010533: Added optimized memory functions for HC08
|                        Ml     - ESCAN00010672: Added memory qualifier
|2005-01-24  01.13.00    Ml     - ESCAN00010670: Added memset
|2005-02-25  01.14.00    Ml     - ESCAN00011215: Added VStdInitPowerOn
|2005-04-26  01.15.00    Ml     - ESCAN00012047: Encapsulate VStdInitPowerOn
|            01.16.00    Ml     - ESCAN00012105: no changes
|2005-05-30  02.00.00    Ml     - ESCAN00013446: Development concept changed
|2005-09-12  02.01.00    Ml     - ESCAN00013512: Fixed Misra warnings
|2005-11-06  02.02.00    Ml     - ESCAN00014183: Added token for defines and types
|2005-11-28  02.03.00    Ml     - Changed version defines
|                        Ml     - ESCAN00014428: VStdMemClr/Set are now internal functions
|                        Ml     - ESCAN00014409: No changes       
|2005-12-12  02.04.00    Ml/Bus - ESCAN00012774: insert comments for different resource categories
|2006-01-12  02.05.00    Ml     - ESCAN00014897: Changed interrupt handling
|2006-01-14  02.06.00    Ml     - ESCAN00014908: Adapted interrupt control handling for RI1.5
|2006-02-07  02.07.00    Ml     - Added VStdGetInterruptState
|                        Hs     - ESCAN00015802: no changes
|2006-05-09  02.08.00    Ces    - ESCAN00016289: Insert memory qualifier V_MEMROM3 to VStdRomMemCpy()
|2006-05-24  02.09.00    BWR    - ESCAN00016488: Compiler error in VStdSuspendAllInterrupts and VStdResumeAllInterrupts
|2006-07-16  02.10.00    Ml     - Changed return type of VStdGetInterruptState from uint8 to tVStdIrqStateType
|2006-07-31  02.11.00    Ml     - ESCAN00017133: Changed assertion handling
|2006-08-04  02.12.00    Ml     - ESCAN00017188: no changes
|2006-11-20  02.13.00    Ml     - Removed VStdGetInterruptState
|2006-12-07  02.14.00    Ml     - Changed switch names
|                        Ml     - ESCAN00018889: Fixed code inspection report findings
|                               - ESCAN00018880: No changes
|2007-01-27  02.15.00    Ml,Ard - ESCAN00019251: VStdLib HL usable for RI1.4 and RI1.5
|2007-02-19  02.16.00    Ml     - ESCAN00019672: include os.h for AUTOSAR
|                        Ml     - ESCAN00019674: Changed names of interrupt lock macros
|2007-05-10  02.17.00    Ml     - ESCAN00020705: Added _COMMENT switches for single source filtering
|                        Ml     - ESCAN00020241: No changes
|2007-11-26  03.00.00    Ml     - ESCAN00024126: Support word and dword copy routines
|                        Ml     - ESCAN00024192: Default and specific implementations supported at the same time
|2008-06-25  03.01.00    Ml     - ESCAN00023334: Added u suffix to the version numbers
|                        Ml     - ESCAN00018659: Removed warnings if interrupt counter not used
|                        Ml     - ESCAN00015501: No changes
|2008-07-17  03.01.01    Ml     - ESCAN00027617: Added library version check support
|2008-07-23  03.02.00    Ml     - ESCAN00028605: old interrupt status is initialized by low level token
|2008-07-27  03.02.01    Ml     - ESCAN00028752: Include of MSR header according to naming convention
|2008-08-13  03.03.00    Ml     - ESCAN00029196: Encapsulated AUTOSAR library version check
|2008-12-08  03.03.01    Ml     - ESCAN00031855: Additional memcpy interfaces
|2009-06-30  03.04.00    Ml     - ESCAN00036089: Application must care about nested calls in case of user handling of locks
|                        Ml     - ESCAN00035049: Resolved extended version check include
|2009-10-15  03.05.00    Ml     - ESCAN00038482: Added additional function qualifier (VSTD_API_2)
|                        Ml     - ESCAN00038485: Added general OS header include.
|2009-10-19  03.05.01    Ml     - ESCAN00038485: Renamed the OS header include according to osCAN
|2010-01-21  03.06.00    Tvi    - ESCAN00040103: [AUTOSAR] Add support for compiler abstraction
|2011-09-01  03.06.01    Tvi    - ESCAN00052664: [MSR only] "upper/lower case" issue at #include compiler/memory abstraction
|2012-06-20  03.07.00    Tvi    - ESCAN00058623: AR4-170: support VStdLib with CFG5 MSR4 R5
|2013-12-10  03.08.00    Tvi    - ESCAN00065931: Add MISRA justifications
|*********************************************************************************************************************/

#define _VSTD_LIB_C_

#include "vstdlib.h"

#if defined(V_OSTYPE_AUTOSAR)
# include "Os.h"
#elif defined(V_OSTYPE_OSEK)
# include "osek.h"
#endif

#if defined(VSTD_ENABLE_API_AUTOSAR)
# if !defined(vsintx)
#  define vsintx sint8_least
# endif
#endif

/* MICROSAR library version checks */
#if defined(VSTD_ENABLE_MSR_LIB_VERSION_CHECK)
# include "Std_Types.h"
# if !defined(V_SUPPRESS_EXTENDED_VERSION_CHECK)
#  include "v_ver.h"
# endif
#endif

/* *******************************************************************************************************************/
/* Version check                                                                                                     */
/* *******************************************************************************************************************/


#if(VSTDLIB_MPC_VERSION != 0x0121u)
# error "Lowlevel Source and Header files are inconsistent!"
#endif

#if(VSTDLIB_MPC_RELEASE_VERSION != 0x00u)
# error "Lowlevel Source and Header file are inconsistent!"
#endif

/* MICROSAR library version check */
#define VSTDLIB_LIB_VERSION  VSTDLIB_MPC_LIB_VERSION


/* Highlevel version check */
#if(VSTDLIB__COREHLL_VERSION != 0x0308u)
# error "HighLevel Source and Header files are inconsistent!"
#endif

#if(VSTDLIB__COREHLL_RELEASE_VERSION != 0x00u)
# error "HighLevel Source and Header file are inconsistent!"
#endif

/* V_def.h Compatibility Check */
#if !defined(VSTD_ENABLE_API_AUTOSAR)
# if(COMMON_VDEF_VERSION < 0x0220u)
#  error "VstdLib requires at least v_def.h in version 2.20.00!"
# endif
#endif


/* Checks relevant for MICROSAR stack */
#if defined(VSTD_ENABLE_API_AUTOSAR)

/* MICROSAR library version checks */
# if defined(VSTD_ENABLE_MSR_LIB_VERSION_CHECK)
#  if !defined(V_SUPPRESS_EXTENDED_VERSION_CHECK)
#   if !defined(VSTDLIB_LIB_VERSION)
#    error "Make sure VSTDLIB_LIB_VERSION is defined in VStd_LLVersionCheck label!"
#   endif
CONST(uint32, VSTDLIB_CONST) VSTDLIB_LIB_SYMBOL = VSTDLIB_LIB_VERSION;
#  endif /* !V_SUPPRESS_EXTENDED_VERSION_CHECK */
# endif /* VSTD_ENABLE_MSR_LIB_VERSION_CHECK */

/* Additional checks for MICROSAR */
# if !defined(VSTD_USE_MEMORY_MACROS)
#  error "VSTD_USE_MEMROY_MACROS STD_[ON|OFF] must be defined in the Compiler_Cfg.h"
# endif

#endif /* VSTD_ENABLE_API_AUTOSAR */


/* Additional checks */
#if defined(C_COMP_GHS_MPC55XX_FLEXCAN2)        
#else
# error "Platform / Compiler not supported!"
#endif

/* *******************************************************************************************************************/
/* Constants                                                                                                         */
/* *******************************************************************************************************************/
#if defined(VSTD_ENABLE_API_AUTOSAR)
# define VSTDLIB_START_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif
/* ROM CATEGORY 4 START */
VSTD_DEF_CONST(VSTD_NONE, vuint8, CONST) kVStdMainVersion    = (vuint8)(((vuint16)VSTDLIB_MPC_VERSION) >> 8);
VSTD_DEF_CONST(VSTD_NONE, vuint8, CONST) kVStdSubVersion     = (vuint8)(((vuint16)VSTDLIB_MPC_VERSION) & (vuint16)0x00FF);
VSTD_DEF_CONST(VSTD_NONE, vuint8, CONST) kVStdReleaseVersion = (vuint8)( (vuint16)VSTDLIB_MPC_RELEASE_VERSION);
/* ROM CATEGORY 4 END */
#if defined(VSTD_ENABLE_API_AUTOSAR)
# define VSTDLIB_STOP_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif

/* *******************************************************************************************************************/
/* Local Types                                                                                                       */
/* *******************************************************************************************************************/
/* RAM CATEGORY 1 START */
/* RAM CATEGORY 1 END */

/* *******************************************************************************************************************/
/* Defines                                                                                                           */
/* *******************************************************************************************************************/
#if defined( VSTD_ENABLE_LOCK_LEVEL )
# if !defined( PPC_INTC_CPR )
#  if defined (V_CPU_MPC5700)
#   if defined (V_PROCESSOR_PC5800XX)
     /* #define INTC          (*(volatile vuint32*)  0xFFF08000UL)
        #define INTC_CPR_0    (*(volatile vuint32*)  0xFFF08010UL)  - core 0
        #define INTC_CPR_1    (*(volatile vuint32*)  0xFFF08014UL)  - core 1
        #define INTC_CPR_2    (*(volatile vuint32*)  0xFFF08018UL)  - core 2
        #define INTC_CPR_3    (*(volatile vuint32*)  0xFFF0801CUL)  - core 3 */
#    define PPC_INTC_CPR   0xFFF08010ul  /* core 0 */
#   else
     /* #define INTC          (*(volatile vuint32*)  0xFC040000UL)
        #define INTC_CPR_0    (*(volatile vuint32*)  0xFC040010UL)  - core 0
        #define INTC_CPR_1    (*(volatile vuint32*)  0xFC040014UL)  - core 1
        #define INTC_CPR_2    (*(volatile vuint32*)  0xFC040018UL)  - core 2
        #define INTC_CPR_3    (*(volatile vuint32*)  0xFC04001CUL)  - core 3 (NAV) */
#    define PPC_INTC_CPR   0xFC040010ul  /* core 0 */
#   endif
#  else
#   define PPC_INTC_CPR   0xFFF48008
#  endif
# endif
# define VSTD_INTC_CPR   (*((volatile vuint32 *)((vuint32)(PPC_INTC_CPR))))
#endif

#define VSTD_MSR_MASK  ((tVStdIrqStateType)0x8000)  

/* ASR40 Workaround */
#if !defined(STATIC)
# define STATIC static
#endif

#if !defined(VSTD_STATIC_DECL)
# define VSTD_STATIC_DECL static
#endif 

/* *******************************************************************************************************************/
/* Local data definitions                                                                                            */
/* *******************************************************************************************************************/
#if defined(VSTD_ENABLE_API_AUTOSAR)
# define VSTDLIB_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif

# if defined(VSTD_ENABLE_INTCTRL_HANDLING)
#  if defined(VSTD_ENABLE_DEFAULT_INTCTRL)
/* RAM CATEGORY 1 START */
VSTD_DEF_VAR(VSTD_STATIC_DECL, tVStdIrqStateType, VAR_NOINIT) vstdInterruptOldStatus; /* old IRQ state, variable not static because of some inline asm!! */
/* RAM CATEGORY 1 END */
#  endif
#  if defined(VSTD_ENABLE_DEFAULT_INTCTRL)
/* RAM CATEGORY 1 START */
VSTD_DEF_VAR(STATIC, vsintx, VAR_NOINIT) vstdInterruptCounter;   /* interrupt counter */
/* RAM CATEGORY 1 END */
#  endif
# endif


#if defined(VSTD_ENABLE_API_AUTOSAR)
# define VSTDLIB_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif

/* *******************************************************************************************************************/
/* Local function declarations                                                                                       */
/* *******************************************************************************************************************/
#if defined(VSTD_ENABLE_API_AUTOSAR)
# define VSTDLIB_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif


#if defined(VSTD_ENABLE_API_AUTOSAR)
# define VSTDLIB_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif

/* *******************************************************************************************************************/
/* Macros                                                                                                            */
/* *******************************************************************************************************************/

#if defined(VSTD_ENABLE_DEBUG_SUPPORT)
# define VStdAssert(p,e)       if(!(p)){ ApplVStdFatalError(e); }
#else
# define VStdAssert(p,e)
#endif

/* *******************************************************************************************************************/
/* Functions                                                                                                         */
/* *******************************************************************************************************************/
#if defined(VSTD_ENABLE_API_AUTOSAR)
# define VSTDLIB_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif

/* *******************************************************************************************************************
Name          : VStdInitPowerOn
Called by     : init routine
Preconditions : none
Parameters    : none
Return values : none
Description   : initializes the global data of the VStdLib
*********************************************************************************************************************/
/* CODE CATEGORY 4 START */
VSTD_DEF_FUNC_API(VSTD_NONE, void, CODE) VStdInitPowerOn(void)
{

# if defined(VSTD_ENABLE_INTCTRL_HANDLING)
#  if defined(VSTD_ENABLE_DEFAULT_INTCTRL)
  vstdInterruptOldStatus = (tVStdIrqStateType)0;
#  endif
#  if defined(VSTD_ENABLE_DEFAULT_INTCTRL)
  vstdInterruptCounter = (vsintx)0;
#  endif
# endif
  
}
/* CODE CATEGORY 4 END */


#if defined(VSTD_ENABLE_API_AUTOSAR)
/* CODE CATEGORY 1 START */
VSTD_DEF_FUNC_API(VSTD_NONE, void, CODE) VStdMemClr_Func(VSTD_DEF_P2VAR_PARA(VSTD_NONE, uint8, AUTOMATIC, VAR_FAR) pDest, uint16_least nCnt)
{
    /* Defaultimplementation */
    VStdAssert(pDest!=V_NULL, kVStdErrorMemClrInvalidParameter);
    while(nCnt > (vuint16)0x0000)
    {  
      nCnt--;
      ((VSTD_DEF_P2VAR_PARA(VSTD_NONE, vuint8, AUTOMATIC, VAR_FAR))pDest)[nCnt] = (vuint8)0x00;
    } 
}

VSTD_DEF_FUNC_API(VSTD_NONE, void, CODE) VStdMemSet_Func(VSTD_DEF_P2VAR_PARA(VSTD_NONE, uint8, AUTOMATIC, VAR_FAR) pDest, uint8 nPattern, uint16_least nCnt)
{
    /* Defaultimplementation */
    VStdAssert(pDest!=V_NULL, kVStdErrorMemSetInvalidParameter);
    while(nCnt > (vuint16)0x0000)
    {  
      --nCnt;
      ((VSTD_DEF_P2VAR_PARA(VSTD_NONE, vuint8, AUTOMATIC, VAR_FAR))pDest)[nCnt] = nPattern;
    }
}

VSTD_DEF_FUNC_API(VSTD_NONE, void, CODE) VStdMemCpy_Func(VSTD_DEF_P2VAR_PARA(VSTD_NONE, uint8, AUTOMATIC, VAR_FAR) pDest, VSTD_DEF_P2CONST_PARA(VSTD_NONE, uint8, AUTOMATIC, VAR_FAR) pSrc, uint16_least nCnt)
{
    /* Defaultimplementation */
    VStdAssert(pDest!=V_NULL, kVStdErrorMemCpyInvalidParameter);
    VStdAssert(pSrc!=V_NULL, kVStdErrorMemCpyInvalidParameter);
    while(nCnt > (vuint16)0x0000)
    {  
      nCnt--;
      ((VSTD_DEF_P2VAR_PARA(VSTD_NONE, vuint8, AUTOMATIC, VAR_FAR))pDest)[nCnt] = ((VSTD_DEF_P2VAR_PARA(VSTD_NONE, vuint8, AUTOMATIC, VAR_FAR))pSrc)[nCnt];
    } 
}

VSTD_DEF_FUNC_API(VSTD_NONE, void, CODE) VStdMemCpy16_Func(VSTD_DEF_P2VAR_PARA(VSTD_NONE, uint16, AUTOMATIC, VAR_FAR) pDest, VSTD_DEF_P2CONST_PARA(VSTD_NONE, uint16, AUTOMATIC, VAR_FAR) pSrc, uint16_least nCnt)
{
    /* Defaultimplementation */
    VStdAssert(pDest!=V_NULL, kVStdErrorMemCpyInvalidParameter);
    VStdAssert(pSrc!=V_NULL, kVStdErrorMemCpyInvalidParameter);
    while(nCnt > (vuint16)0x0000)
    {
      nCnt--;
      ((VSTD_DEF_P2VAR_PARA(VSTD_NONE, vuint16, AUTOMATIC, VAR_FAR))pDest)[nCnt] = ((VSTD_DEF_P2VAR_PARA(VSTD_NONE, vuint16, AUTOMATIC, VAR_FAR))pSrc)[nCnt];
    } 
}

VSTD_DEF_FUNC_API(VSTD_NONE, void, CODE) VStdMemCpy32_Func(VSTD_DEF_P2VAR_PARA(VSTD_NONE, uint32, AUTOMATIC, VAR_FAR) pDest, VSTD_DEF_P2CONST_PARA(VSTD_NONE, uint32, AUTOMATIC, VAR_FAR) pSrc, uint16_least nCnt)
{
    /* Defaultimplementation */
    VStdAssert(pDest!=V_NULL, kVStdErrorMemCpyInvalidParameter);
    VStdAssert(pSrc!=V_NULL, kVStdErrorMemCpyInvalidParameter);
    while(nCnt > (vuint16)0x0000)
    {
      nCnt--;
      ((VSTD_DEF_P2VAR_PARA(VSTD_NONE, vuint32, AUTOMATIC, VAR_FAR))pDest)[nCnt] = ((VSTD_DEF_P2VAR_PARA(VSTD_NONE, vuint32, AUTOMATIC, VAR_FAR))pSrc)[nCnt];
    } 
}


/* CODE CATEGORY 1 END */
#else /* VSTD_ENABLE_API_AUTOSAR */
# if defined(VSTD_HL_USE_VSTD_MEMSET)
/* *******************************************************************************************************************
Name          : VStdMemSetInternal
Called by     : -
Preconditions : -
Parameters    : void*   pDest    : destination pointer          
                vuint8  nPattern : the value which is used for filling
                vuint16 nCnt     : number of bytes to be filled 
Return values : none
Description   : fills nCnt bytes from address pDest on with the nPattern value
*********************************************************************************************************************/
/* CODE CATEGORY 1 START */
VSTD_API_0 void VSTD_API_1 VStdMemSetInternal(void *pDest, vuint8 nPattern, vuint16 nCnt) VSTD_API_2
{
    /* Defaultimplementation */
    VStdAssert(pDest!=V_NULL, kVStdErrorMemSetInvalidParameter);
    while(nCnt > (vuint16)0x0000)
    {  
      --nCnt;
      ((VSTD_DEF_P2VAR_PARA(VSTD_NONE, vuint8, AUTOMATIC, VAR_FAR))pDest)[nCnt] = nPattern;
    }
}
/* CODE CATEGORY 1 END */
# endif

# if defined(VSTD_HL_USE_VSTD_MEMCLR)
/* *******************************************************************************************************************
Name          : VStdMemClr
Called by     : -
Preconditions : -
Parameters    : void*   pDest : destination pointer          
                vuint16 nCnt  : number of bytes to be filled 
Return values : none
Description   : fills nCnt bytes from address pDest on with 0x00 pattern
*********************************************************************************************************************/
/* CODE CATEGORY 1 START */
VSTD_API_0 void VSTD_API_1 VStdMemClrInternal(void *pDest, vuint16 nCnt) VSTD_API_2
{
    /* Defaultimplementation */
    VStdAssert(pDest!=V_NULL, kVStdErrorMemClrInvalidParameter);
    while(nCnt > (vuint16)0x0000)
    {  
      nCnt--;
      ((VSTD_DEF_P2VAR_PARA(VSTD_NONE, vuint8, AUTOMATIC, VAR_FAR))pDest)[nCnt] = (vuint8)0x00;
    } 
}
/* CODE CATEGORY 1 END */
# endif
 
# if defined(VSTD_HL_USE_VSTD_RAMMEMCPY)
/* *******************************************************************************************************************
Name          : VStdRamMemCpy
Called by     : -
Preconditions : -
Parameters    : void*   pDest : RAM destination pointer          
                void*   pSrc  : RAM source pointer               
                vuint16 nCnt  : number of bytes to be copied 
Return values : none
Description   : moves nCnt bytes from RAM pSrc to RAM pDest
*********************************************************************************************************************/
/* CODE CATEGORY 1 START */
VSTD_API_0 void VSTD_API_1 VStdRamMemCpy(void *pDest, void* pSrc, vuint16 nCnt) VSTD_API_2
{
    /* Defaultimplementation */
    VStdAssert(pDest!=V_NULL, kVStdErrorMemCpyInvalidParameter);
    VStdAssert(pSrc!=V_NULL, kVStdErrorMemCpyInvalidParameter);
    while(nCnt > (vuint16)0x0000)
    {  
      nCnt--;
      ((VSTD_DEF_P2VAR_PARA(VSTD_NONE, vuint8, AUTOMATIC, VAR_FAR))pDest)[nCnt] = ((VSTD_DEF_P2VAR_PARA(VSTD_NONE, vuint8, AUTOMATIC, VAR_FAR))pSrc)[nCnt];
    } 
}
/* CODE CATEGORY 1 END */
# endif

# if defined(VSTD_HL_USE_VSTD_ROMMEMCPY)
/* *******************************************************************************************************************
Name          : VStdRomMemCpy
Called by     : -
Preconditions : -
Parameters    : void*   pDest : RAM destination pointer          
                void*   pSrc  : ROM source pointer               
                vuint16 nCnt  : number of bytes to be copied 
Return values : none
Description   : moves nCnt bytes from ROM pSrc to RAM pDest
*********************************************************************************************************************/
/* CODE CATEGORY 1 START */
VSTD_API_0 void VSTD_API_1 VStdRomMemCpy(void *pDest, V_MEMROM1 void V_MEMROM2 V_MEMROM3 *pSrc, vuint16 nCnt) VSTD_API_2
{  
    /* Defaultimplementation */
    VStdAssert(pDest!=V_NULL, kVStdErrorMemCpyInvalidParameter);
    VStdAssert(pSrc!=V_NULL, kVStdErrorMemCpyInvalidParameter);
    while(nCnt > (vuint16)0x0000)
    {
      nCnt--;
      ((VSTD_DEF_P2VAR_PARA(VSTD_NONE, vuint8, AUTOMATIC, VAR_FAR))pDest)[nCnt] = ((VSTD_DEF_P2CONST_PARA(VSTD_NONE, vuint8, AUTOMATIC, CONST_FAR))pSrc)[nCnt];
    } 
}
/* CODE CATEGORY 1 END */
# endif

# if defined(VSTD_HL_USE_VSTD_WORD_MEMCPY)
/* *******************************************************************************************************************
Name          : VStdRamMemCpy16
Called by     : -
Preconditions : -
Parameters    : void*   pDest    : RAM destination pointer
                void*   pSrc     : RAM source pointer
                vuint16 nWordCnt : Number of words to be copied
Return values : none
Description   : moves nWordCnt words from the source RAM address to the destination RAM address
*********************************************************************************************************************/
/* CODE CATEGORY 1 START */
VSTD_API_0 void VSTD_API_1 VStdRamMemCpy16(void *pDest, void *pSrc, vuint16 nWordCnt) VSTD_API_2
{
    /* Defaultimplementation */
    VStdAssert(pDest!=V_NULL, kVStdErrorMemCpyInvalidParameter);
    VStdAssert(pSrc!=V_NULL, kVStdErrorMemCpyInvalidParameter);
    while(nWordCnt > (vuint16)0x0000)
    {
      nWordCnt--;
      ((VSTD_DEF_P2VAR_PARA(VSTD_NONE, vuint16, AUTOMATIC, VAR_FAR))pDest)[nWordCnt] = ((VSTD_DEF_P2VAR_PARA(VSTD_NONE, vuint16, AUTOMATIC, VAR_FAR))pSrc)[nWordCnt];
    } 
}
/* CODE CATEGORY 1 END */
# endif

# if defined(VSTD_HL_USE_VSTD_DWORD_MEMCPY)
/* *******************************************************************************************************************
Name          : VStdRamMemCpy32
Called by     : -
Preconditions : -
Parameters    : void*   pDest    : RAM destination pointer
                void*   pSrc     : RAM source pointer
                vuint16 nDWordCnt: Number of dwords to be copied
Return values : none
Description   : moves nDWordCnt dwords from the source RAM address to the destination RAM address
*********************************************************************************************************************/
/* CODE CATEGORY 1 START */
VSTD_API_0 void VSTD_API_1 VStdRamMemCpy32(void *pDest, void *pSrc, vuint16 nDWordCnt) VSTD_API_2
{
    /* Defaultimplementation */
    VStdAssert(pDest!=V_NULL, kVStdErrorMemCpyInvalidParameter);
    VStdAssert(pSrc!=V_NULL, kVStdErrorMemCpyInvalidParameter);
    while(nDWordCnt > (vuint16)0x0000)
    {
      nDWordCnt--;
      ((VSTD_DEF_P2VAR_PARA(VSTD_NONE, vuint32, AUTOMATIC, VAR_FAR))pDest)[nDWordCnt] = ((VSTD_DEF_P2VAR_PARA(VSTD_NONE, vuint32, AUTOMATIC, VAR_FAR))pSrc)[nDWordCnt];
    } 
}
/* CODE CATEGORY 1 END */
# endif

#endif /* VSTD_ENABLE_API_AUTOSAR */


#if defined(VSTD_ENABLE_API_AUTOSAR)
#else
/* *******************************************************************************************************************/
/* Additional functions for memory manipulation                                                                      */
/* *******************************************************************************************************************/
#endif

/* *******************************************************************************************************************
The functions below require a plattform specific implementation, therefore 
they are not available for the standard implementation of the library!
*********************************************************************************************************************/
# if defined(VSTD_ENABLE_INTCTRL_HANDLING)
#  if defined(VSTD_ENABLE_DEFAULT_INTCTRL)
/* *******************************************************************************************************************
Name          : VStdSuspendAllInterrupts
Called by     : -
Preconditions : -
Parameters    : none
Return values : none
Description   : disables the global IRQ and saves the current IRQ state
*********************************************************************************************************************/
/* CODE CATEGORY 1 START */
VSTD_DEF_FUNC_API(VSTD_NONE, void, CODE) VStdSuspendAllInterrupts(void) VSTD_API_2
{
  VStdDeclareGlobalInterruptOldStatus
#    if defined(VSTD_ENABLE_OSEK_INTCTRL)
  VStdGlobalInterruptDisable();
  VStdGetGlobalInterruptOldStatus(vstdInterruptOldStatus);
#    else
  VStdAssert(vstdInterruptCounter < 127, kVStdErrorIntDisableTooOften);
  if(vstdInterruptCounter == 0) 
  {
    VStdGlobalInterruptDisable();
    VStdGetGlobalInterruptOldStatus(vstdInterruptOldStatus);
  }
  vstdInterruptCounter++;
#    endif
}
/* CODE CATEGORY 1 END */

/* *******************************************************************************************************************
Name          : VStdResumeAllInterrupts
Called by     : -
Preconditions : -
Parameters    : none
Return values : none
Description   : restores the previous IRQ state
*********************************************************************************************************************/
/* CODE CATEGORY 1 START */
VSTD_DEF_FUNC_API(VSTD_NONE, void, CODE)  VStdResumeAllInterrupts(void) VSTD_API_2
{
  VStdDeclareGlobalInterruptOldStatus
#    if defined(VSTD_ENABLE_OSEK_INTCTRL)
  VStdPutGlobalInterruptOldStatus(vstdInterruptOldStatus);
  VStdGlobalInterruptRestore();
#    else
  VStdAssert(vstdInterruptCounter > 0, kVStdErrorIntRestoreTooOften);
  vstdInterruptCounter--;
  if(vstdInterruptCounter == 0)
  {
    VStdPutGlobalInterruptOldStatus(vstdInterruptOldStatus);
    VStdGlobalInterruptRestore();
  }
#    endif
}
/* CODE CATEGORY 1 END */
#  endif

/* *******************************************************************************************************************/
/* Additional functions for interrupt manipulation                                                                   */
/* *******************************************************************************************************************/
#if defined(VSTD_ENABLE_DEFAULT_INTCTRL)


# if defined( C_COMP_GHS_MPC55XX_FLEXCAN2 )       
 
#   define _ASM __asm

#if defined( C_COMP_GHS_MPC55XX_FLEXCAN2 ) 
#pragma ghs startnoinline /* PRQA S 3116 */ /* compiler specific pragma */
#endif    
/* CODE CATEGORY 1 START */
VSTD_NOINLINE_PRE void VStdGlobalIntDisable_Dummy(void) VSTD_NOINLINE_POST
{
  _ASM(" mfmsr  r3 "); /* get MSR */  
  _ASM(" wrteei 0  "); /* disable interrupts: EE = 0 */
}
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
VSTD_NOINLINE_PRE void VStdGlobalIntRestore(tVStdIrqStateType oldStatus) VSTD_NOINLINE_POST
{
  if((oldStatus & VSTD_MSR_MASK) != 0)
  {
    _ASM(" wrteei 1 "); /* enable interrupts: EE = 1 */
  }
}
/* CODE CATEGORY 1 END */
#if defined( C_COMP_GHS_MPC55XX_FLEXCAN2 ) 
#pragma ghs endnoinline /* PRQA S 3116 */ /* compiler specific pragma */
#endif

#  if defined( VSTD_ENABLE_LOCK_LEVEL )
/* CODE CATEGORY 1 START */
void VStdLL_GlobalInterruptDisable(tVStdIrqStateType *oldStatusPtr)
{
  tVStdIrqStateType vstdMSR;
  vstdMSR = VStdGlobalIntDisable();
  *oldStatusPtr = (tVStdIrqStateType) VSTD_INTC_CPR;  
  VSTD_INTC_CPR = (tVStdIrqStateType) VSTD_INTERRUPT_LOCK_LEVEL;
  _ASM(" mbar 1 ");
  #if defined( C_ENABLE_INSTRUCTION_SET_VLE )
  _ASM(" se_isync ");
  #else
  _ASM(" isync ");
  #endif
  VStdGlobalIntRestore(vstdMSR);
}
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
void VStdLL_GlobalInterruptRestore(tVStdIrqStateType oldStatus)
{ 
  tVStdIrqStateType vstdMSR;
  vstdMSR = VStdGlobalIntDisable();
  _ASM(" mbar 1 ");
  VSTD_INTC_CPR = (tVStdIrqStateType) oldStatus;
  VStdGlobalIntRestore(vstdMSR);
}
/* CODE CATEGORY 1 END */
#  endif
# endif

#endif

# endif

#if defined(VSTD_ENABLE_API_AUTOSAR)
# define VSTDLIB_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif

/* module specific MISRA deviations:

 MD_VStdLib_Header_0342: MISRA rule 19.13
      Reason:     At least ISO C90 is required for AUTOSAR software, so ## support is available.
      Risk:       No risk
      Prevention: No prevention necessary
	  
 MD_VStdLib_Header_0881: MISRA rule 19.12
      Reason:     The evaluation order for ## is not relevant here, as the ## operator is not used in comparisons. ## is used to generate component name specific memory mapping parameters.
      Risk:       No risk
      Prevention: No prevention necessary
	  
 MD_VStdLib_Header_3410: MISRA rule 19.10
      Reason:     The macro parameters are not enclosed in () because they are storage keywords and thus () will result in compilation issues in the resulting code.
      Risk:       No risk
      Prevention: No prevention necessary

 MD_VStdLib_Header_3453: MISRA rule 19.7
      Reason:     QAC incorrectly detects function like macros in the VStdLib header. This is because the AUTOSAR compiler abstraction macros are used in the function prototypes, too.
      Risk:       No risk
      Prevention: No prevention necessary
*/


/************   Organi, Version 3.9.1 Vector-Informatik GmbH  ************/
