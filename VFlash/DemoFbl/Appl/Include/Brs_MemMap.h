
/**********************************************************************************************************************
  COPYRIGHT
-----------------------------------------------------------------------------------------------------------------------
  \par      copyright
  \verbatim
  Copyright (c) 2017 by Vector Informatik GmbH.                                                  All rights reserved.

                This software is copyright protected and proprietary to Vector Informatik GmbH.
                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
                All other rights remain with Vector Informatik GmbH.
  \endverbatim
-----------------------------------------------------------------------------------------------------------------------
  FILE DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
  \file  File:  Brs_MemMap.h
      Project:  Vector Basic Runtime System for FlashBootLoader
       Module:  BrsFblMain

  \brief Description:  Module specific MemMap Header to allow linking of specific parts of BRS code in RAM.
                       This is just a template and has to be adapted platform/compiler specific within every project.

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
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
 ----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Description
  --------  ----------  ------  ---------------------------------------------------------------------------------------
  01.00.00  2017-12-20  visbwa  Initial creation for new BrsFbl
**********************************************************************************************************************/

#ifndef BRS_MEMMAP_ERROR
  #define BRS_MEMMAP_ERROR
#endif

/* #error "Add your compiler-specific pragma to allocate code in a section that will later be configured in the linker script to run from RAM" */

/*******  CODE sections **********************************************************************************************/
#ifdef BRS_START_SEC_RAM_CODE
  /* #pragma <enter your compiler specific pragma> */

  /* Sample for PPC and DiabData: */
  /*#pragma section CODE "RAMCODE"*/
  
  # pragma ghs section text=".RAMCODE"
  
  #undef BRS_START_SEC_RAM_CODE
  #undef BRS_MEMMAP_ERROR 
#endif

#ifdef BRS_STOP_SEC_RAM_CODE
  /* #pragma <enter your compiler specific pragma> */

  /* Sample for PPC and DiabData: */
  /*#pragma section CODE*/
  
  # pragma ghs section text=default
  
  #undef BRS_STOP_SEC_RAM_CODE 
  #undef BRS_MEMMAP_ERROR
#endif

/*******  CONST sections  ********************************************************************************************/
#ifdef BRS_START_SEC_RAM_CONST
  /* #pragma <enter your compiler specific pragma> */

  /* Sample for PPC and DiabData: */
  /*#pragma section CONST "RAMCODE"*/
  
  # pragma ghs startdata
  # pragma ghs section rodata=".RAMCONST"

  #undef BRS_START_SEC_RAM_CONST
  #undef BRS_MEMMAP_ERROR 
#endif

#ifdef BRS_STOP_SEC_RAM_CONST
  /* #pragma <enter your compiler specific pragma> */

  /* Sample for PPC and DiabData: */
  /*#pragma section CONST*/
  
  # pragma ghs section rodata=default
  # pragma ghs enddata

  #undef BRS_STOP_SEC_RAM_CONST
  #undef BRS_MEMMAP_ERROR
#endif

#if defined (BRS_MEMMAP_ERROR)
  #error "Error in Brs_MemMap.h: MemMap section is not included!"
#endif
