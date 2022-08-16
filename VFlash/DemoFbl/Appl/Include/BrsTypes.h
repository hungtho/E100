
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
  \file  File:  BrsTypes.h
      Project:  Vector Basic Runtime System for FBL
       Module:  BrsMain

  \brief Description:  Compatibility header for FBL with CBD ComStack
                       - BrsTypes.h is included by BrsHw / ...

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
  01.00.00  2018-10-29  visbwa  Added revision history
                                Added workaround for Std_ReturnType, E_OK and E_NOT_OK
**********************************************************************************************************************/

#ifndef _BRSTYPES_H_
#define _BRSTYPES_H_

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "v_cfg.h"
#include "v_def.h"

#if !defined (uint8) /* ASR compatibility */
typedef vuint8    uint8;
#endif

#if !defined (uint16) /* ASR compatibility */
typedef vuint16    uint16;
#endif

#if !defined (uint32) /* ASR compatibility */
typedef vuint32    uint32;
#endif

#if !defined (sint8) /* ASR compatibility */
typedef vsint8    sint8;
#endif

#if !defined (sint16) /* ASR compatibility */
typedef vsint16    sint16;
#endif

#if !defined (sint32) /* ASR compatibility */
typedef vsint32    sint32;
#endif

/* Workaround for types, used by BrsHw and not available within GENy stacks */
#if !defined (Std_ReturnType)
typedef uint8 Std_ReturnType;
#endif

#if !defined (E_OK)
#define E_OK      (0u)
#endif

#if !defined (E_NOT_OK)
#define E_NOT_OK  (1u)
#endif

#endif /*_BRSTYPES_H_*/
