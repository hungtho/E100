/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/** \file
 *  \brief        MemMap section definition to locate (link) data or code in memory
 *  \details      This file contains compiler specific section definition for every segment that can be mapped
 *                within the Flash Bootloader to a specific location.
 *
 *  \note
 *                Please note, that this file contains a collection of definitions to be used with the Flash Bootloader.
 *                This code may influence the behavior of the Bootloader in principle. Therefore, great care
 *                must be taken to verify the correctness of the implementation.
 *
 *                The contents of the originally delivered files are only examples resp. implementation proposals.
 *                With regard to the fact that these definitions are meant for demonstration purposes only,
 *                Vector Informatik's liability shall be expressly excluded in cases of ordinary negligence, to the
 *                extent admissible by law or statute.
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \par Copyright
 *  \verbatim
 *  Copyright (c) 2018 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  THIS IS A GENERATED FILE
 *  Generator version : 01.08.02
 *  Generation date :   2018-12-11
 *********************************************************************************************************************/

/* PRQA S 0841 EOF */ /* MD_MSR_19.6 */
/* PRQA S 0883 EOF */ /* MD_MemMap_0883 */
/* PRQA S 3116 EOF */ /* MD_MSR_3.4 */

#define FBL_MEMMAP_ERROR

#if defined( APPL_FBL_INFO_HEADER_START_SEC_CONST )
   /* #pragma <enter your compiler specific pragma> */

# pragma ghs section rodata=".APPLHEADER"
# pragma ghs startdata

# undef APPL_FBL_INFO_HEADER_START_SEC_CONST
# undef FBL_MEMMAP_ERROR
#endif

#if defined( APPL_FBL_INFO_HEADER_STOP_SEC_CONST )
   /* #pragma <enter your compiler specific pragma> */
# pragma ghs section rodata=default
# pragma ghs enddata

# undef APPL_FBL_INFO_HEADER_STOP_SEC_CONST
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( EEPDUMMY_FULL_START_SEC_CODE )
   /* #pragma <enter your compiler specific pragma> */
# undef EEPDUMMY_FULL_START_SEC_CODE
# undef FBL_MEMMAP_ERROR
#endif

#if defined( EEPDUMMY_FULL_STOP_SEC_CODE )
   /* #pragma <enter your compiler specific pragma> */
# undef EEPDUMMY_FULL_STOP_SEC_CODE
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( EEPDUMMY_START_SEC_VAR )
# pragma ghs section bss=".EEPDATA"
# undef EEPDUMMY_START_SEC_VAR
# undef FBL_MEMMAP_ERROR
#endif

#if defined( EEPDUMMY_STOP_SEC_VAR )
# pragma ghs section bss=default
# undef EEPDUMMY_STOP_SEC_VAR
# undef EEPDUMMY_STOP_SEC_VAR_EXPORT
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( FBLAP_RAMCODE_START_SEC_CODE ) || \
    defined( FBLAP_RAMCODE_START_SEC_CODE_EXPORT )
# pragma ghs section text=".RAMCODE"
# undef FBLAP_RAMCODE_START_SEC_CODE
# undef FBLAP_RAMCODE_START_SEC_CODE_EXPORT
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBLAP_RAMCODE_STOP_SEC_CODE ) || \
    defined( FBLAP_RAMCODE_STOP_SEC_CODE_EXPORT )
# pragma ghs section
# undef FBLAP_RAMCODE_STOP_SEC_CODE
# undef FBLAP_RAMCODE_STOP_SEC_CODE_EXPORT
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( FBLDIAG_RAMCODE_START_SEC_CODE )
   /* #pragma <enter your compiler specific pragma> */
# undef FBLDIAG_RAMCODE_START_SEC_CODE
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBLDIAG_RAMCODE_STOP_SEC_CODE )
   /* #pragma <enter your compiler specific pragma> */
# undef FBLDIAG_RAMCODE_STOP_SEC_CODE
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( FBLFLIO_FLASHCODE_START_SEC_VAR )
# pragma ghs section bss="FLASHDRV"
# undef FBLFLIO_FLASHCODE_START_SEC_VAR
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBLFLIO_FLASHCODE_STOP_SEC_VAR )
# pragma ghs section bss=default
# undef FBLFLIO_FLASHCODE_STOP_SEC_VAR
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( FBLHEADER_START_SEC_CONST )
# pragma ghs section rodata=".FBLHEADER"
# pragma ghs startdata
# undef FBLHEADER_START_SEC_CONST
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBLHEADER_STOP_SEC_CONST )
#  pragma ghs section rodata=default
#  pragma ghs enddata
# undef FBLHEADER_STOP_SEC_CONST
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( FBLHW_FBLCANTRANSMITTED_START_SEC_CODE )
   /* #pragma <enter your compiler specific pragma> */
# undef FBLHW_FBLCANTRANSMITTED_START_SEC_CODE
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBLHW_FBLCANTRANSMITTED_STOP_SEC_CODE )
   /* #pragma <enter your compiler specific pragma> */
# undef FBLHW_FBLCANTRANSMITTED_STOP_SEC_CODE
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( FBLHW_RAMCODE_START_SEC_CODE )
   /* #pragma <enter your compiler specific pragma> */
# undef FBLHW_RAMCODE_START_SEC_CODE
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBLHW_RAMCODE_STOP_SEC_CODE )
   /* #pragma <enter your compiler specific pragma> */
# undef FBLHW_RAMCODE_STOP_SEC_CODE
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( FBLHW_START_SEC_CODE )
   /* #pragma <enter your compiler specific pragma> */
# undef FBLHW_START_SEC_CODE
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBLHW_STOP_SEC_CODE )
   /* #pragma <enter your compiler specific pragma> */
# undef FBLHW_STOP_SEC_CODE
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( FBLLIB_MEM_RAMCODE_START_SEC_CODE ) || \
    defined( FBLLIB_MEM_RAMCODE_START_SEC_CODE_EXPORT )
   /* #pragma <enter your compiler specific pragma> */
# undef FBLLIB_MEM_RAMCODE_START_SEC_CODE
# undef FBLLIB_MEM_RAMCODE_START_SEC_CODE_EXPORT
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBLLIB_MEM_RAMCODE_STOP_SEC_CODE ) || \
    defined( FBLLIB_MEM_RAMCODE_STOP_SEC_CODE_EXPORT )
   /* #pragma <enter your compiler specific pragma> */
# undef FBLLIB_MEM_RAMCODE_STOP_SEC_CODE
# undef FBLLIB_MEM_RAMCODE_STOP_SEC_CODE_EXPORT
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( FBLLIB_MEM_START_SEC_CONST )
   /* #pragma <enter your compiler specific pragma> */
# undef FBLLIB_MEM_START_SEC_CONST
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBLLIB_MEM_STOP_SEC_CONST )
   /* #pragma <enter your compiler specific pragma> */
# undef FBLLIB_MEM_STOP_SEC_CONST
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( FBLLIB_MEM_START_SEC_VAR ) || \
    defined( FBLLIB_MEM_START_SEC_VAR_EXPORT )
   /* #pragma <enter your compiler specific pragma> */
# undef FBLLIB_MEM_START_SEC_VAR
# undef FBLLIB_MEM_START_SEC_VAR_EXPORT
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBLLIB_MEM_STOP_SEC_VAR ) || \
    defined( FBLLIB_MEM_STOP_SEC_VAR_EXPORT )
   /* #pragma <enter your compiler specific pragma> */
# undef FBLLIB_MEM_STOP_SEC_VAR
# undef FBLLIB_MEM_STOP_SEC_VAR_EXPORT
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( FBLMIO_START_SEC_CODE )
   /* #pragma <enter your compiler specific pragma> */
# undef FBLMIO_START_SEC_CODE
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBLMIO_STOP_SEC_CODE )
   /* #pragma <enter your compiler specific pragma> */
# undef FBLMIO_STOP_SEC_CODE
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( FBLTP_RAMCODE_START_SEC_CODE )
   /* #pragma <enter your compiler specific pragma> */
# undef FBLTP_RAMCODE_START_SEC_CODE
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBLTP_RAMCODE_STOP_SEC_CODE )
   /* #pragma <enter your compiler specific pragma> */
# undef FBLTP_RAMCODE_STOP_SEC_CODE
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( FBL_APPLVECT_START_SEC_CONST ) || \
    defined( FBL_APPLVECT_START_SEC_CONST_EXPORT )
# pragma ghs section rodata=".APPLVECT"
# undef FBL_APPLVECT_START_SEC_CONST
# undef FBL_APPLVECT_START_SEC_CONST_EXPORT
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBL_APPLVECT_STOP_SEC_CONST ) || \
    defined( FBL_APPLVECT_STOP_SEC_CONST_EXPORT )
# pragma ghs section rodata=default
# undef FBL_APPLVECT_STOP_SEC_CONST

# undef FBL_APPLVECT_STOP_SEC_CONST_EXPORT
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBL_CW_CFG_START_SEC_CONST )
   /* #pragma <enter your compiler specific pragma> */
# undef FBL_CW_CFG_START_SEC_CONST
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBL_CW_CFG_STOP_SEC_CONST )
   /* #pragma <enter your compiler specific pragma> */
# undef FBL_CW_CFG_STOP_SEC_CONST
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( FBL_CW_FULL_START_SEC_CODE )
   /* #pragma <enter your compiler specific pragma> */
# undef FBL_CW_FULL_START_SEC_CODE
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBL_CW_FULL_STOP_SEC_CODE )
   /* #pragma <enter your compiler specific pragma> */
# undef FBL_CW_FULL_STOP_SEC_CODE
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( FBL_CW_TASK_START_SEC_CODE )
   /* #pragma <enter your compiler specific pragma> */
# undef FBL_CW_TASK_START_SEC_CODE
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBL_CW_TASK_STOP_SEC_CODE )
   /* #pragma <enter your compiler specific pragma> */
# undef FBL_CW_TASK_STOP_SEC_CODE
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( FBL_FBT_START_SEC_CONST )
   /* #pragma <enter your compiler specific pragma> */
# undef FBL_FBT_START_SEC_CONST
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBL_FBT_STOP_SEC_CONST )
   /* #pragma <enter your compiler specific pragma> */
# undef FBL_FBT_STOP_SEC_CONST
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( FBL_LBT_START_SEC_CONST )
   /* #pragma <enter your compiler specific pragma> */
# undef FBL_LBT_START_SEC_CONST
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBL_LBT_STOP_SEC_CONST )
   /* #pragma <enter your compiler specific pragma> */
# undef FBL_LBT_STOP_SEC_CONST
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( FBL_MAIN_FBLSTART_START_SEC_CODE )
   /* #pragma <enter your compiler specific pragma> */
# undef FBL_MAIN_FBLSTART_START_SEC_CODE
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBL_MAIN_FBLSTART_STOP_SEC_CODE )
   /* #pragma <enter your compiler specific pragma> */
# undef FBL_MAIN_FBLSTART_STOP_SEC_CODE
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( FBL_MAIN_MAGICFLAG_START_SEC_VAR )
   /* #pragma <enter your compiler specific pragma> */
# pragma ghs startdata
# pragma ghs section bss=".FBLMAGIC"
# undef FBL_MAIN_MAGICFLAG_START_SEC_VAR
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBL_MAIN_MAGICFLAG_STOP_SEC_VAR )
   /* #pragma <enter your compiler specific pragma> */
# pragma ghs section
# pragma ghs enddata
# undef FBL_MAIN_MAGICFLAG_STOP_SEC_VAR
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( FLASHDRV_FLASHHEADER_START_SEC_CONST )
#  pragma ghs startdata
#  pragma ghs section rodata=".FLASHDRVHEADER"
# undef FLASHDRV_FLASHHEADER_START_SEC_CONST
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FLASHDRV_FLASHHEADER_STOP_SEC_CONST )
#  pragma ghs section rodata=default
#  pragma ghs enddata
# undef FLASHDRV_FLASHHEADER_STOP_SEC_CONST
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( INITWATCHDOG_START_SEC_CODE ) || \
    defined( INITWATCHDOG_START_SEC_CODE_EXPORT )
   /* #pragma <enter your compiler specific pragma> */
# undef INITWATCHDOG_START_SEC_CODE
# undef INITWATCHDOG_START_SEC_CODE_EXPORT
# undef FBL_MEMMAP_ERROR
#endif

#if defined( INITWATCHDOG_STOP_SEC_CODE ) || \
    defined( INITWATCHDOG_STOP_SEC_CODE_EXPORT )
   /* #pragma <enter your compiler specific pragma> */
# undef INITWATCHDOG_STOP_SEC_CODE
# undef INITWATCHDOG_STOP_SEC_CODE_EXPORT
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( LOOKFORWATCHDOG_START_SEC_CODE ) || \
    defined( LOOKFORWATCHDOG_START_SEC_CODE_EXPORT )
# pragma ghs section text=".RAMCODE"
# undef LOOKFORWATCHDOG_START_SEC_CODE
# undef LOOKFORWATCHDOG_START_SEC_CODE_EXPORT
# undef FBL_MEMMAP_ERROR
#endif

#if defined( LOOKFORWATCHDOG_STOP_SEC_CODE ) || \
    defined( LOOKFORWATCHDOG_STOP_SEC_CODE_EXPORT )
# pragma ghs section text=default
# undef LOOKFORWATCHDOG_STOP_SEC_CODE
# undef LOOKFORWATCHDOG_STOP_SEC_CODE_EXPORT
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( MEMCPY_START_SEC_CODE )
   /* #pragma <enter your compiler specific pragma> */
# undef MEMCPY_START_SEC_CODE
# undef FBL_MEMMAP_ERROR
#endif

#if defined( MEMCPY_STOP_SEC_CODE )
   /* #pragma <enter your compiler specific pragma> */
# undef MEMCPY_STOP_SEC_CODE
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( SECMPAR_START_SEC_DATA )
   /* #pragma <enter your compiler specific pragma> */
# undef SECMPAR_START_SEC_DATA
# undef FBL_MEMMAP_ERROR
#endif

#if defined( SECMPAR_STOP_SEC_DATA )
   /* #pragma <enter your compiler specific pragma> */
# undef SECMPAR_STOP_SEC_DATA
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( WDTRIGGER_START_SEC_CODE ) || \
    defined( WDTRIGGER_START_SEC_CODE_EXPORT )
# pragma ghs section text=".RAMCODE"
# undef WDTRIGGER_START_SEC_CODE
# undef WDTRIGGER_START_SEC_CODE_EXPORT
# undef FBL_MEMMAP_ERROR
#endif

#if defined( WDTRIGGER_STOP_SEC_CODE ) || \
    defined( WDTRIGGER_STOP_SEC_CODE_EXPORT )
# pragma ghs section text=default
# undef WDTRIGGER_STOP_SEC_CODE
# undef WDTRIGGER_STOP_SEC_CODE_EXPORT
# undef FBL_MEMMAP_ERROR
#endif

/* ----------------------------------------------------------------------------------------------------------------- */

#if defined( FBL_MEMMAP_ERROR )
# error "Error in MemMap.h: MemMap section is not included!"
#endif

/* Module specific MISRA deviations:

   MD_MemMap_0883:
      Reason:     This file has to be included multiple times explicitly, due to the memory mapping mechanism.
      Risk:       No risk due to the undef pragmas and error pragma.
      Prevention: No prevention.

*/

/**********************************************************************************************************************
 *  END OF FILE: MEMMAP.H
 *********************************************************************************************************************/
