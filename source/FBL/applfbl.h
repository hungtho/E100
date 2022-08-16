/***********************************************************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/** \file
 *  \brief         Application information header for Bootloader test
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
 *
 *  \par Note
 *  \verbatim
 *  Please note, that this file contains a collection of callback functions to be used with the Flash Bootloader.
 *  These functions may influence the behavior of the bootloader in principle.
 *  Therefore, great care must be taken to verify the correctness of the implementation.
 *
 *  The contents of the originally delivered files are only examples resp. implementation proposals.
 *  With regard to the fact that these functions are meant for demonstration purposes only, Vector Informatik´s
 *  liability shall be expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
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
 *  01.00.00   2016-11-07  CB      -                First implementation for SSangyong
 **********************************************************************************************************************/

#ifndef __APPLFBL_H__
#define __APPLFBL_H__

/***********************************************************************************************************************
 *  DEFINES
 **********************************************************************************************************************/
#define kApplSizeSymcPartNumber                 10u      /**< Size of SYMC Part NUmber                */
#define kApplSizeSymcSoftwareVersion             2u      /**< Size of SYMC Software Version           */
#define kApplSizeSystemSupplierCode              5u      /**< Size of System Supplier Code          */
#define kApplSizeSupplierSwVersion               3u      /**< Size of Compatibility software version  */

#define kApplNumberHwCompatibilityEntries        3u      /**< Size of Number of hardware compatibility field entries */
#define kApplSizeSupplierHwVersion               2u      /**< Size of Compatibility hardware version  */


/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/* The following structure is used to get information from the downloaded logical block */
typedef struct tagApplInfoHeader
{
   /* SYMC Software Identification Data */
   vuint8 kApplSymcPartNumber[kApplSizeSymcPartNumber];              /**< DID F187h, 10bytes ASCII: SYMC Part NUmber */
   vuint8 kApplSymcSoftwareVersion[kApplSizeSymcSoftwareVersion];    /**< DID F189h, 2bytes ASCII: SYMC Software Version */
   vuint8 kApplSystemSupplierCode[kApplSizeSystemSupplierCode];      /**< DID F18Ah, 5bytes ASCII: System Supplier Code */

   /* Compatibility Information */
   vuint8 kApplSupplierSoftwareVersion[kApplSizeSupplierSwVersion];  /**< Supplier-specific software version for compatibility check   */
   vuint8 kApplSupplierCompatibleHwVersions;                         /**< Number of compatible hardware versions                       */
                                                                     /**< Supplier-specific harware version for compatibility check    */
   vuint8 kApplSupplierHardwareVersion[kApplNumberHwCompatibilityEntries*kApplSizeSupplierHwVersion];
} tApplInfoHeader;

#endif  /* __APPLFBL_H__ */


/***********************************************************************************************************************
 *  END OF FILE: APPLFBL.H
 **********************************************************************************************************************/
