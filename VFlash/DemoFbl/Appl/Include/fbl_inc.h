/***********************************************************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/** \file
 *  \brief         Include File
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
 *  Andreas Wenckebach            AWh           Vector Informatik GmbH
 *  Joern Herwig                  JHg           Vector Informatik GmbH
 *  Marco Riedl                   Rie           Vector Informatik GmbH
 *  Alexander Starke              ASe           Vector Informatik GmbH
 *  Thomas Bezold                 TBe           Vector Informatik GmbH
 *  Achim Strobelt                Ach           Vector Informatik GmbH
 *  Christian Baeuerle            CB            Vector Informatik GmbH
 *  Daniel Koebel                 DKl           Vector Informatik GmbH
 *  Sebastian Loos                Shs           Vector Informatik GmbH
 *  Andre Caspari                 Ci            Vector Informatik GmbH
 *  Torben Stoessel               TnS           Vector Informatik GmbH
 *  Christopher Elkins            CEl           Vector CANtech, Inc.
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version    Date        Author  Change Id        Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  03.00.00   2015-07-23  AWh     ESCAN00083953    Remove unused SLPs
 *                         JHg     ESCAN00084111    Moved fbl_diag.h and fbl_mem.h above fbl_ap.h
 *  03.01.00   2015-09-23  JHg     ESCAN00085442    Moved Fbl_Fbt.h above fbl_mio.h
 *                         Rie     ESCAN00085361    Added support for MMC SLP8
 *  03.02.00   2015-11-30  ASe     ESCAN00086060    Modified code to include WrapNv_inc.h instead of WrapNv.h
 *                         TBe     ESCAN00086693    Modified application file includes for PSA
 *                         Ach     ESCAN00086721    Removed direct include of TPMC header file
 *  03.03.00   2016-01-18  CB      ESCAN00087544    Minor adaptions for Fiat
 *  03.04.00   2016-02-25  Ach     ESCAN00088301    Added include of fbl_main.h
 *  03.05.00   2016-03-08  DKl     ESCAN00088800    Added support for Mazda SLP1
 *  03.06.00   2016-03-16  Shs     ESCAN00088936    Added support for PATAC SLP2
 *  03.06.01   2016-04-05  AWh     ESCAN00089246    Remove Dummy Eeprom include for GM SLP5/6 and Patac SLP2
 *  03.07.00   2016-06-15  Ci      ESCAN00090481    Added include file of RAM I/O driver
 *  03.08.00   2016-07-22  TnS     ESCAN00091082    Added SecModHis to Hmc
 *  03.09.00   2016-10-04  CEl     ESCAN00092177    Added SecModHis to Fiat SLP2
 *  03.10.00   2016-10-21  TnS     ESCAN00092474    Added support for Toyota SLP3
 *  03.11.00   2016-10-31  CB      ESCAN00092599    Added support for SYMC SLP2
 *  03.12.00   2017-01-04  Ci      ESCAN00093445    Added support for VolvoCar SLP2
 *                         Rie     ESCAN00093928    Removed deprecated code
 *  03.13.00   2017-04-21  Ci      ESCAN00094840    Added TestAppl support
 *                         Ci      ESCAN00094842    Added fbl_nvpattern.h
 *                         JHg     ESCAN00094841    Added boot manager callouts
 *  03.14.00   2017-06-07  CB      ESCAN00095456    Added support for Daimler SLP11
 *  03.15.00   2017-08-16  TBe     ESCAN00096320    Fixed includes for Honda SLP1
 *                                 ESCAN00096322    Added include for FlashRom.h
 *                                 ESCAN00096324    Added includes for XCP with MSR components
 *  03.16.00   2017-09-05  DKl     ESCAN00096539    Added SecModHis for Mazda SLP1
 *  03.17.00   2017-11-14  Ach     ESCAN00097388    Added support for Cp_Asr4Xcp
 **********************************************************************************************************************/

#ifndef __FBL_INC_H__
#define __FBL_INC_H__

/***********************************************************************************************************************
 *  VERSION
 **********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : FblInc CQComponent : Implementation */
#define FBLINC_VERSION          0x0317u
#define FBLINC_RELEASE_VERSION  0x00u

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/

/* Version check file */
#include "v_ver.h"
#include "v_cfg.h"
#if defined( VGEN_GENY )
# include "v_inc.h"
#endif /* VGEN_GENY */

/* Security module */
# include "SecM.h"

#include "fbl_def.h"

/* Logical block table types and definitions */
# if defined( V_GEN_GENERATOR_MSR )
#  include "Fbl_Lbt.h"
# else /* VGEN_GENY */
#  include "fbl_mtab.h"
# endif /* VGEN_GENY */

/* Basic types and definitions */


#include "flashdrv.h"
#include "flashdrv_xd1.h"

#if defined( FBL_DIAG_ENABLE_FLASHDRV_ROM )
# include "FlashRom.h"
#endif

#include "fbl_wd.h"
# include "iotypes.h"

/* Flash block table */
#if defined( V_GEN_GENERATOR_MSR )
# include "Fbl_Fbt.h"
#else /* VGEN_GENY */
/* For GENy use-case: see below */
#endif /* VGEN_GENY */
# include "fbl_mio.h"
# include "fbl_flio.h"
# include "fbl_flio_xd1.h"
# include "EepInc.h"
# include "EepIO.h"
/* Application vector table */
# include "applvect.h"


/* API of the communication wrapper */
# include "fbl_cw.h"

/* Hardware dependent header file */
#include "fbl_hw.h"

#if defined( FBL_ENABLE_WRAPPER_NV )
# include "WrapNv_inc.h"
#endif

/* Flash block table */
#if defined( V_GEN_GENERATOR_MSR )
/* For DaVinci Configurator: See above */
#else /* VGEN_GENY */
# include "fbl_apfb.h"
#endif /* VGEN_GENY */


#if defined( kMioDeviceRam )
/* Memory driver for RAM access */
# include "fbl_ramio_inc.h"
#endif



/* Diagnostic layer */
#include "fbl_diag.h"

# include "fbl_mem.h"

/* Application call-back functions */
#if defined( FBL_ENABLE_COMMON_DATA )
#  include "comdat.h"
#endif /* FBL_ENABLE_COMMON_DATA */
#include "fbl_ap.h"
#include "fbl_apwd.h"
# include "fbl_apdi.h"
#  include "fbl_apnv.h"




#if defined( FBL_DEF_ENABLE_NON_KB_MAIN )
# include "fbl_main.h"
#endif /* FBL_DEF_ENABLE_NON_KB_MAIN */

#endif /* __FBL_INC_H__ */

/***********************************************************************************************************************
 *  END OF FILE: FBL_INC.H
 **********************************************************************************************************************/
