/***********************************************************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/** \file
 *  \brief         Compacts the include files for the NV-Wrapper
 *
 *  --------------------------------------------------------------------------------------------------------------------
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \par Copyright
 *  \verbatim
 *  Copyright (c) 2012 by Vector Informatik GmbH.                                                  All rights reserved.
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
 *  Achim Strobelt                Ach           Vector Informatik GmbH
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version    Date        Author  Change Id        Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  01.00.00   2009-07-08  CB                       Initial implementation
 *  01.01.00   2012-01-26  Ach                      No changes
 *  01.02.00   2012-11-29  Ach     ESCAN00062931    Adapted comments to use Doxygen
 **********************************************************************************************************************/

#ifndef __WRAPPERNV_INC_H__
#define __WRAPPERNV_INC_H__

/* Include Vector standard includes first */
#include "v_cfg.h"
#include "v_def.h"

#include "fbl_inc.h"

#if defined( FBL_ENABLE_EEPMGR )
# include "iotypes.h"
# include "fbl_flio_Xd.h"
# include "EepMgr_inc.h"
#else
# include "iotypes.h"
# include "eepinc.h"
# include "eepio.h"
#endif

#include "WrapNv.h"

#endif   /* __WRAPPERNV_INC_H__ */

/***********************************************************************************************************************
 *  END OF FILE: _WRAPNV_INC.H
 **********************************************************************************************************************/
