/*---------------------------------------------------------------------------- 
 * License information:
 *   -    Serialnumber:       CBD1800777
  ----------------------------------------------------------------------------
 * Software is licensed for:
 * Young Hwa Tech Co, Ltd, 
 * Package: CBD Symc SLP1 - in projects for SsangYong 
 * Micro: SPC570S50E1CEFAY
 * Compiler: Green Hills 2017.5.4
  ---------------------------------------------------------------------------*/
/*  --------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  --------------------------------------------------------------------------
 *
 *  Description:  
 *  1) Check that all currently compiled files in the system have the correct 
 *     versions according to the delivered software integration package (SIP).
 *  2) Provide the SIP version as ROM constants for e.g. diagnostic purposes.
 *
 *  Usage hints:
 *    If a compiler error occurs within this file, a wrong version
 *    for the notified module has been detected. 
 *    Please check, if
 *    a) The module is part of your project and the include path is 
 *       set correct (if not, the compiler may assume 0 for the 
 *       version number comparison)
 *    b) The used module may have an incorrect version for this
 *       project. Proof carefully, if a newer (or older) version
 *       of the notified component is already available on your site
 *       and an erroneous version mixup had occurred. See the required
 *       module's main and bugfix version above of the error message.
 *    c) This may be the wrong SIP version check file for the project.
 *       Proof carefully, if the file has been exchanged together with
 *       the latest change of a component (e.g. an bugfix delivery), 
 *       too.
 *    In case none of the above mention points is true, please contact 
 *    your Vector's contact person for further help.
 *
 *  Background information:
 *    Each Vector software component checks its own header
 *    and code files for version consistency. With this, a version  
 *    mixup within each component could be detected during compilation.
 *    To detect the mixup of different components in a project, too,
 *    this version check file has been introduced.
  ---------------------------------------------------------------------------*/


#include "v_inc.h"

#if defined (VGEN_ENABLE_IL_VECTOR)
# include "il_inc.h"
#endif
#if defined (VGEN_ENABLE_LIN_TP)
# include "dtl_inc.h"
#endif
/* Include sequence: include nmh.h before nmh_can.h is included */
#if defined (VGEN_ENABLE_NMHIGH)
# include "nmh.h"
#endif
#if defined (VGEN_ENABLE_TPJ1939_ASRBAM)
# include "J1939Tp_Types.h"
#endif

#if defined (VGEN_ENABLE_LIN_TP)
# if defined ( DTL_PROCESSING_COOKED )
#  define TPLIN_COOCKEDMASTECU_VERSION                       TPLIN_COOCKEDSLAVECU_VERSION
#  define TPLIN_COOCKEDMASTECU_RELEASE_VERSION               TPLIN_COOCKEDSLAVECU_RELEASE_VERSION
# endif

# if defined ( DTL_PROCESSING_RAW )
#  define TPLIN_RAWMASTECU_VERSION                           TPLIN_COOCKEDSLAVECU_VERSION
#  define TPLIN_RAWMASTECU_RELEASE_VERSION                   TPLIN_COOCKEDSLAVECU_RELEASE_VERSION
# endif
#endif

/*----------------------------------------------------------------------------
  DrvCan_Mpc5500Flexcan2Hll
  ---------------------------------------------------------------------------*/
#if defined (VGEN_ENABLE_CAN_DRV)
# include "can_def.h"
#endif

/*----------------------------------------------------------------------------
  Il_Vector
  ---------------------------------------------------------------------------*/
#if defined (VGEN_ENABLE_IL_VECTOR)
# include "il_def.h"
#endif

/*----------------------------------------------------------------------------
  Tp_Iso15765
  ---------------------------------------------------------------------------*/
#if defined (VGEN_ENABLE_TP_ISO_MC)
# include "tpmc.h"
#endif

/*----------------------------------------------------------------------------
  VStdLib_Mpc
  ---------------------------------------------------------------------------*/
#if defined (VGEN_ENABLE_VSTDLIB)
# include "vstdlib.h"
#endif


/*----------------------------------------------------------------------------
  DrvCan_Mpc5500Flexcan2Hll
  ---------------------------------------------------------------------------*/
#if defined (VGEN_ENABLE_CAN_DRV)
# if (DRVCAN_MAC7100FLEXCANHLL_VERSION != 0x0303)
#  error "DrvCan_Mpc5500Flexcan2Hll: Wrong main/sub version (DRVCAN_MAC7100FLEXCANHLL_VERSION) detected for this SIP delivery!"
# endif
# if (DRVCAN_MAC7100FLEXCANHLL_RELEASE_VERSION != 0x11)
#  error "DrvCan_Mpc5500Flexcan2Hll: Wrong release version (DRVCAN_MAC7100FLEXCANHLL_RELEASE_VERSION) detected for this SIP delivery!"
# endif
#endif

/*----------------------------------------------------------------------------
  Il_Vector
  ---------------------------------------------------------------------------*/
#if defined (VGEN_ENABLE_IL_VECTOR)
# if (IL_VECTOR_VERSION != 0x0511)
#  error "Il_Vector: Wrong main/sub version (IL_VECTOR_VERSION) detected for this SIP delivery!"
# endif
# if (IL_VECTOR_RELEASE_VERSION != 0x03)
#  error "Il_Vector: Wrong release version (IL_VECTOR_RELEASE_VERSION) detected for this SIP delivery!"
# endif
#endif

/*----------------------------------------------------------------------------
  Tp_Iso15765
  ---------------------------------------------------------------------------*/
#if defined (VGEN_ENABLE_TP_ISO_MC)
# if (TP_ISO15765_VERSION != 0x0401)
#  error "Tp_Iso15765: Wrong main/sub version (TP_ISO15765_VERSION) detected for this SIP delivery!"
# endif
# if (TP_ISO15765_RELEASE_VERSION != 0x00)
#  error "Tp_Iso15765: Wrong release version (TP_ISO15765_RELEASE_VERSION) detected for this SIP delivery!"
# endif
#endif

/*----------------------------------------------------------------------------
  VStdLib_Mpc
  ---------------------------------------------------------------------------*/
#if defined (VGEN_ENABLE_VSTDLIB)
# if (VSTDLIB_MPC_VERSION != 0x0121)
#  error "VStdLib_Mpc: Wrong main/sub version (VSTDLIB_MPC_VERSION) detected for this SIP delivery!"
# endif
# if (VSTDLIB_MPC_RELEASE_VERSION != 0x00)
#  error "VStdLib_Mpc: Wrong release version (VSTDLIB_MPC_RELEASE_VERSION) detected for this SIP delivery!"
# endif
#endif


/*----------------------------------------------------------------------------
  Store SIP version in ROM constants
  ---------------------------------------------------------------------------*/
/* ROM CATEGORY 4 START*/
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kSipMainVersion   = (vuint8)(VGEN_DELIVERY_VERSION_BYTE_0);
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kSipSubVersion    = (vuint8)(VGEN_DELIVERY_VERSION_BYTE_1);
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kSipBugFixVersion = (vuint8)(VGEN_DELIVERY_VERSION_BYTE_2);
/* ROM CATEGORY 4 END*/

