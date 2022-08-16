/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/** \file
 *  \brief        Implementation of the HIS security module - Seed/key authentication
 *
 *  \description  Implements OEM specific challenge/response scheme
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

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/

/* Security module interfaces */
#include "Sec.h"

/***********************************************************************************************************************
 *   VERSION
 **********************************************************************************************************************/

#if ( SECACCESS_HIS_SYMC_VERSION != 0x0100u ) || \
    ( SECACCESS_HIS_SYMC_RELEASE_VERSION != 0x00u )
# error "Error in SEC_SEEDKEYVENDOR.C: Source and header file are inconsistent!"
#endif

/***********************************************************************************************************************
 *   DEFINES
 **********************************************************************************************************************/

/* Seed-Key constants */
#define kKryptoA              0x6ed9eba1ul
#define kKryptoB              0xa953fd4eul
#define kKryptoC              0x5a827999ul
#define kKryptoD              0x8f1bbcdcul

/***********************************************************************************************************************
 *  CONFIGURATION CHECKS
 **********************************************************************************************************************/

/* Standard HIS API used */
#if ( SEC_SEED_LENGTH != 8u )
# error "Only seed lengths (in bytes) of 4 or 8 are supported by the example code!"
#endif /* SEC_SEED_LENGTH */
#if ( SEC_KEY_LENGTH != 4u )
# error "Only a key length (in bytes) of 4 is supported by the example code!"
#endif /* SEC_KEY_LENGTH */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  SecM_ComputeKeyVendor
 **********************************************************************************************************************/
/*! \brief       Calculates a key value based on the provided seed and constant value
 *  \param[in]   inputSeed The random seed the key calculation shall be based on
 *  \param[in]   constant A fixed constant used by the key calculation algorithm
 *  \param[out]  computedKey Pointer to resulting key data as a formula of key = f(seed,k)
 *  \return      SECM_OK     if calculation was successful
 *               SECM_NOT_OK if calculation has failed (e.g. wrong parameters)
 **********************************************************************************************************************/
SecM_StatusType SecM_ComputeKeyVendor( SecM_SeedType inputSeed, SecM_ConstType constant,  /* PRQA S 3673 */ /* MD_SecSeedKeyVendor_3673 */
   V_MEMRAM1 SecM_KeyStorageType V_MEMRAM2 V_MEMRAM3 * computedKey )                      /* PRQA S 3673 */ /* MD_SecSeedKeyVendor_3673 */
{
   SecM_StatusType   result;
   SecM_KeyStorageType tmpX, tmpY;

   result = SECM_OK;

   /* Implementation example for key calculation */
   /* Standard HIS API used */

   tmpX = (inputSeed.seedX ^ constant) * kKryptoA + kKryptoB;
   tmpY = (inputSeed.seedY ^ constant) * kKryptoC + kKryptoD;
   *computedKey = tmpX ^ tmpY;

   return result;
}

/**********************************************************************************************************************
 *  MISRA
 *********************************************************************************************************************/

/* Module specific MISRA deviations:

  MD_SecSeedKeyVendor_3673:
     Reason: API defined by HIS specification.
     Risk: No identifiable risk.
     Prevention: No prevention required.

*/

/***********************************************************************************************************************
 *  END OF FILE: SEC_SEEDKEYVENDOR.C
 **********************************************************************************************************************/
