/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/** \file
 *  \brief        Configuration of the HIS security module - Seed/key authentication
 *
 *  \description  Offers challenge/response authentication interface
 *  -------------------------------------------------------------------------------------------------------------------
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \par Copyright
 *  \verbatim
 *  Copyright (c) 2016 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 */
/*********************************************************************************************************************/

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
 *  01.00.00   2016-11-07  CB                       Initial release
 **********************************************************************************************************************/

#ifndef __SEC_SEEDKEY_CFG_H__
#define __SEC_SEEDKEY_CFG_H__

/***********************************************************************************************************************
 *   VERSION
 **********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : SecAccess_His_Symc CQComponent : Implementation */
#define SECACCESS_HIS_SYMC_VERSION            0x0100u
#define SECACCESS_HIS_SYMC_RELEASE_VERSION    0x00u

/* Reference interface version */
/** Major interface version identifies incompatible changes */
#define SECACCESS_API_REFERENCE_VERSION_MAJOR      0x01u
/** Minor interface version identifies backward compatible changes */
#define SECACCESS_API_REFERENCE_VERSION_MINOR      0x00u
/** Release interface version identifies cosmetic changes */
#define SECACCESS_API_REFERENCE_VERSION_RELEASE    0x00u

/***********************************************************************************************************************
 *  DEFINES
 **********************************************************************************************************************/

/* --- Configuration of seed/key interface --- */

/** Seed length in bytes */
#define SEC_SEED_LENGTH       8u
/** Key length in bytes */
#define SEC_KEY_LENGTH        4u

#endif /* __SEC_SEEDKEY_CFG_H__ */

/***********************************************************************************************************************
 *  END OF FILE: SEC_SEEDKEY_CFG.H
 **********************************************************************************************************************/
