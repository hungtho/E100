/*
                             *******************
******************************* C SOURCE FILE ********************************
**                           *******************                            **
**                                                                          **
**  Project   : E100_LDC                                                    **
**  Filename  : Asw_DiagCan.h                                               **
**  Version   : -.- (PCB : )                                                **
**  Date      : 2019.08.01                                                  **
**                                                                          **
******************************************************************************
**                                                                          **
**  (c) 2019 YOUNG HWA TECH Co., Ltd. All Rights Reserved                   **
**                                                                          **
**                       YOUNG HWA TECH Co., Ltd.                           **
******************************************************************************

VERSION HISTORY:
----------------

Version     : -.-
Date        : ----.--.--
Revised by  : Tran Duc Hung
Description : Original version.

*/

#ifndef ASW_DIAGCAN_INCLUDED
#define ASW_DIAGCAN_INCLUDED

/****************************************************************************/
/**                                                                        **/
/**                      MODULES USED                                      **/
/**                                                                        **/
/****************************************************************************/
#include "../RTE/Rte_AswBswLink.h"

/****************************************************************************/
/**                                                                        **/
/**                      DEFINITIONS AND MACROS                            **/
/**                                                                        **/
/****************************************************************************/
#define DefaultSession        								( 0x01U )
#define ProgrammingSession    								( 0x02U )
#define ExtendedDiagSession										( 0x03U )

#define hardReset															( 0x01U )

#define RequestSeed														( 0x01U )
#define SendKey																( 0x02U )
#define SECURITY_LOCK													( 0x00U	)
#define SECURITY_UNLOCK												( 0x01U	)
#define SECURITY_SEQ_FALSE										( 0x00U	)
#define SECURITY_SEQ_TRUE											( 0x01U	)

#define enableRxAndTx													( 0x00U )
#define enableRxAndDisableTx									( 0x01U )
#define disableRxAndEnableTx									( 0x02U )
#define disableRxAndTx												( 0x03U )

#define CAN_CTRL_ENABLE												( 0x00U )
#define CAN_CTRL_DISABLE											( 0x01U )

#define ON																		( 0x01U )
#define OFF																		( 0x02U )
#define DTC_DISABLE														( 0x01U )
#define DTC_ENABLE														( 0x00U )

#define reportNumberOfDTCByStatusMask 				( 0x01U )
#define reportDTCByStatusMask									( 0x02U )

#define startRoutine													( 0x01U )

/****************************************************************************/
/**                                                                        **/
/**                      TYPEDEFS AND STRUCTURES                           **/
/**                                                                        **/
/****************************************************************************/

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED VARIABLES                                **/
/**                                                                        **/
/****************************************************************************/

# ifndef ASW_DIAGCAN_C_SRC
# endif

/****************************************************************************/
/**                                                                        **/
/**                      EXPORTED FUNCTIONS                                **/
/**                                                                        **/
/****************************************************************************/
extern void DiagCan_DiagCanValues( LdcDiagnosisType* pDiagFlags );

#endif

/****************************************************************************/
/**                                                                        **/
/**                      EOF                                               **/
/**                                                                        **/
/****************************************************************************/
