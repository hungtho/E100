/****************************************************************************
*
* Copyright © 2015-2019 STMicroelectronics - All Rights Reserved
*
* License terms: STMicroelectronics Proprietary in accordance with licensing
* terms SLA0089 at www.st.com.
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* EVALUATION ONLY – NOT FOR USE IN PRODUCTION
*****************************************************************************/
/**
 * @file    eirq.c
 * @brief   SPC5xx EIRQ code.
 *
 * @addtogroup EIRQ
 * @{
 */

#include "eirq.h"
#include "eirq_cfg.h"
#include "osal.h"

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/
void manage_eirq_interrupt(uint8_t eirqnum);

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/	

/**
 * @brief  manage external interrupt occurred and call related callback
 *
 * @param[in] eirqnum number of External Interrupt Occurred
 */
void manage_eirq_interrupt(uint8_t eirqnum) {
  uint8_t i;
  i = 0U;
  while (eirqconf[i].eirqNumber != -1) {
    if (eirqnum == (uint8_t)eirqconf[i].eirqNumber) {
      /* call related callback */
      if (eirqconf[i].callback != NULL) {
        eirqconf[i].callback();
      }
    }
    i++;
  }
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#if defined (_SPC570Sxx_) || defined (_SPC574Sxx_) || defined(__DOXYGEN__)

#if (SPC5_SIUL_EIRQ_HAS_0_HANDLER == TRUE)
/**
 * @brief  EIRQ 0 interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_SIUL_EIRQ_0_HANDLER) {

  IRQ_PROLOGUE();

  osalEnterCriticalFromISR();

  manage_eirq_interrupt(0U);

  SIUL2.DISR0.R = (1UL << 0);

  osalExitCriticalFromISR();

  IRQ_EPILOGUE();
}
#endif /* SPC5_SIUL_EIRQ_HAS_0_HANDLER */

#if (SPC5_SIUL_EIRQ_HAS_1_HANDLER == TRUE)
/**
 * @brief  EIRQ 1 interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_SIUL_EIRQ_1_HANDLER) {

  IRQ_PROLOGUE();

  osalEnterCriticalFromISR();

  manage_eirq_interrupt(1U);

  SIUL2.DISR0.R = (1UL << 1);

  osalExitCriticalFromISR();

  IRQ_EPILOGUE();
}
#endif /* SPC5_SIUL_EIRQ_HAS_1_HANDLER */

#if (SPC5_SIUL_EIRQ_HAS_2_HANDLER == TRUE)
/**
 * @brief  EIRQ 2 interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_SIUL_EIRQ_2_HANDLER) {

  IRQ_PROLOGUE();

  osalEnterCriticalFromISR();

  manage_eirq_interrupt(2U);

  SIUL2.DISR0.R = (1UL << 2);

  osalExitCriticalFromISR();

  IRQ_EPILOGUE();
}
#endif /* SPC5_SIUL_EIRQ_HAS_2_HANDLER */

#if (SPC5_SIUL_EIRQ_HAS_3_5_HANDLER == TRUE)
/**
 * @brief  EIRQ 3-5 interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_SIUL_EIRQ_3_5_HANDLER) {
  uint8_t i;

  IRQ_PROLOGUE();

  osalEnterCriticalFromISR();

  for (i = 3U; i < 6U; i++) {
    /*check eirq occurred */
    if (((SIUL2.DISR0.R >> i) & 0x01U) == 1U) {
      /*call management function*/
      manage_eirq_interrupt(i);
      /*reset interrupt flag*/
      SIUL2.DISR0.R = (1UL << i);
    }
  }	  

  osalExitCriticalFromISR();

  IRQ_EPILOGUE();
}
#endif /* SPC5_SIUL_EIRQ_HAS_3_5_HANDLER */

#elif defined (_SPC574Kxx_) || defined(__DOXYGEN__)

#if (SPC5_SIUL_EIRQ_HAS_0_7_HANDLER == TRUE)
/**
 * @brief  EIRQ 0-7 interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_SIUL_EIRQ_0_7_HANDLER) {
  uint8_t i;

  IRQ_PROLOGUE();

  osalEnterCriticalFromISR();

  for (i = 0U; i < 8U; i++) {
    /*check eirq occurred */
    if (((SIUL2.DISR0.R >> i) & 0x01U) == 1U) {
      /*call management function*/
      manage_eirq_interrupt(i);
      /*reset interrupt flag*/
      SIUL2.DISR0.R = (1UL << i);
    }
  }

  osalExitCriticalFromISR();

  IRQ_EPILOGUE();
}
#endif /* SPC5_SIUL_EIRQ_HAS_0_7_HANDLER */

#if (SPC5_SIUL_EIRQ_HAS_8_15_HANDLER == TRUE)
/**
 * @brief  EIRQ 8-15 interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_SIUL_EIRQ_8_15_HANDLER) {
  uint8_t i;

  IRQ_PROLOGUE();

  osalEnterCriticalFromISR();

  for (i = 8U; i < 16U; i++) {
    /*check eirq occurred */
    if (((SIUL2.DISR0.R >> i) & 0x01U) == 1U) {
      /*call management function*/
      manage_eirq_interrupt(i);
      /*reset interrupt flag*/
      SIUL2.DISR0.R = (1UL << i);
    }
  }

  osalExitCriticalFromISR();

  IRQ_EPILOGUE();
}
#endif /* SPC5_SIUL_EIRQ_HAS_8_15_HANDLER */

#endif

#if defined (_SPC582Bxx_) || defined(_SPC584Bxx_) || defined (_SPC58ECxx_) || defined (_SPC58xGxx_) || defined (_SPC58xNxx_) || defined (_SPC572Lxx_) || defined(__DOXYGEN__)

#if (SPC5_SIUL_HAS_EXT_INT_0_HANDLER == TRUE)
/**
 * @brief  EIRQ 0-7 interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_SIUL_EXT_INT_0_HANDLER) {
  uint8_t i;

  IRQ_PROLOGUE();

  osalEnterCriticalFromISR();

  for (i = SPC5_SIUL_IRQ_VECTOR_0_MIN; i < SPC5_SIUL_IRQ_VECTOR_0_MAX + 1U; i++) { 
#if defined (_SPC572Lxx_)
    /* Only the REQ0 and REQ5 are available in the Interrupt vector 0 for SPC572L
     * platform; the value of  MIN is set to 0 and the MAX to 5,
     * the intermediate values (1,2,3 and 4) will be skipped in the check.
     */
    if ((i > SPC5_SIUL_IRQ_VECTOR_0_MIN) && (i < SPC5_SIUL_IRQ_VECTOR_0_MAX)) {
      continue;
    }
#endif
    /*check eirq occurred */
    if (((SIUL2.DISR0.R >> i) & 0x01U) == 1U) {
      /*call management function*/
      manage_eirq_interrupt(i);
      /*reset interrupt flag*/
      SIUL2.DISR0.R = (1UL << i);
    }
  }

  osalExitCriticalFromISR();

  IRQ_EPILOGUE();
}
#endif /* SPC5_SIUL_HAS_EXT_INT_0_HANDLER */

#if (SPC5_SIUL_HAS_EXT_INT_1_HANDLER == TRUE)
/**
 * @brief  EIRQ 8-15 interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_SIUL_EXT_INT_1_HANDLER) {
  uint8_t i;

  IRQ_PROLOGUE();

  osalEnterCriticalFromISR();

  for (i = SPC5_SIUL_IRQ_VECTOR_1_MIN; i < SPC5_SIUL_IRQ_VECTOR_1_MAX + 1U; i++) {
    /*check eirq occurred */
    if (((SIUL2.DISR0.R >> i) & 0x01U) == 1U) {
      /*call management function*/
      manage_eirq_interrupt(i);
      /*reset interrupt flag*/
      SIUL2.DISR0.R = (1UL << i);
    }
  }

  osalExitCriticalFromISR();

  IRQ_EPILOGUE();
}
#endif /* SPC5_SIUL_HAS_EXT_INT_1_HANDLER */

#if (SPC5_SIUL_HAS_EXT_INT_2_HANDLER == TRUE)
/**
 * @brief  EIRQ 16-23 interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_SIUL_EXT_INT_2_HANDLER) {
  uint8_t i;

  IRQ_PROLOGUE();

  osalEnterCriticalFromISR();

  for (i = SPC5_SIUL_IRQ_VECTOR_2_MIN; i < SPC5_SIUL_IRQ_VECTOR_2_MAX + 1U; i++) {
    /*check eirq occurred */
    if (((SIUL2.DISR0.R >> i) & 0x01U) == 1U) {
      /*call management function*/
      manage_eirq_interrupt(i);
      /*reset interrupt flag*/
      SIUL2.DISR0.R = (1UL << i);
    }
  }

  osalExitCriticalFromISR();

  IRQ_EPILOGUE();
}
#endif /* SPC5_SIUL_HAS_EXT_INT_2_HANDLER */

#if (SPC5_SIUL_HAS_EXT_INT_3_HANDLER == TRUE)
/**
 * @brief  EIRQ 24-31 interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_SIUL_EXT_INT_3_HANDLER) {
  uint8_t i;

  IRQ_PROLOGUE();

  osalEnterCriticalFromISR();

  for (i = SPC5_SIUL_IRQ_VECTOR_3_MIN; i < SPC5_SIUL_IRQ_VECTOR_3_MAX + 1U; i++) {
    /*check eirq occurred */
    if (((SIUL2.DISR0.R >> i) & 0x01U) == 1U) {
      /*call management function*/
      manage_eirq_interrupt(i);
      /*reset interrupt flag*/
      SIUL2.DISR0.R = (1UL << i);
    }
  }

  osalExitCriticalFromISR();

  IRQ_EPILOGUE();
}
#endif /* SPC5_SIUL_HAS_EXT_INT_3_HANDLER */

#endif

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Eirq initialization.
 *
 * @init
 */
void eirqInit(void) {
  uint8_t i;
  uint8_t eirqnum;

  /* Priority settings */
#if defined (_SPC570Sxx_) || defined (_SPC574Sxx_) || defined(__DOXYGEN__)
#if (SPC5_SIUL_EIRQ_HAS_0_HANDLER == TRUE)
  INTC_PSR(SPC5_SIUL_EIRQ_0_INT_NUMBER) = SPC5_EIRQ_0_IRQ_PRIORITY;
#endif
#if (SPC5_SIUL_EIRQ_HAS_1_HANDLER == TRUE)
  INTC_PSR(SPC5_SIUL_EIRQ_1_INT_NUMBER) = SPC5_EIRQ_1_IRQ_PRIORITY;
#endif
#if (SPC5_SIUL_EIRQ_HAS_2_HANDLER == TRUE)
  INTC_PSR(SPC5_SIUL_EIRQ_2_INT_NUMBER) = SPC5_EIRQ_2_IRQ_PRIORITY;
#endif
#if (SPC5_SIUL_EIRQ_HAS_3_5_HANDLER == TRUE)
  INTC_PSR(SPC5_SIUL_EIRQ_3_5_INT_NUMBER) = SPC5_EIRQ_3_5_IRQ_PRIORITY;
#endif
#elif defined (_SPC574Kxx_)|| defined(__DOXYGEN__)
#if (SPC5_SIUL_EIRQ_HAS_0_7_HANDLER == TRUE)
  INTC_PSR(SPC5_SIUL_EIRQ_0_7_INT_NUMBER) = SPC5_EIRQ_0_7_IRQ_PRIORITY;
#endif
#if (SPC5_SIUL_EIRQ_HAS_8_15_HANDLER == TRUE)
  INTC_PSR(SPC5_SIUL_EIRQ_8_15_INT_NUMBER) = SPC5_EIRQ_8_15_IRQ_PRIORITY;
#endif
#endif
#if defined (_SPC582Bxx_) || defined (_SPC572Lxx_) || defined (_SPC584Bxx_) || defined (_SPC58ECxx_) || defined (_SPC58xGxx_) || defined (_SPC58xNxx_) || defined(__DOXYGEN__)
#if (SPC5_SIUL_HAS_EXT_INT_0_HANDLER == TRUE)
  INTC_PSR(SPC5_SIUL_EXT_INT_0_INT_NUMBER) = SPC5_EXT_INT_0_IRQ_PRIORITY;
#endif
#if (SPC5_SIUL_HAS_EXT_INT_1_HANDLER == TRUE)
  INTC_PSR(SPC5_SIUL_EXT_INT_1_INT_NUMBER) = SPC5_EXT_INT_1_IRQ_PRIORITY;
#endif
#if (SPC5_SIUL_HAS_EXT_INT_2_HANDLER == TRUE)
  INTC_PSR(SPC5_SIUL_EXT_INT_2_INT_NUMBER) = SPC5_EXT_INT_2_IRQ_PRIORITY;
#endif
#if (SPC5_SIUL_HAS_EXT_INT_3_HANDLER == TRUE)
  INTC_PSR(SPC5_SIUL_EXT_INT_3_INT_NUMBER) = SPC5_EXT_INT_3_IRQ_PRIORITY;
#endif
#endif
  /* Registers Configuration */
  i = 0;
  while (eirqconf[i].eirqNumber != -1) {
    eirqnum = (uint8_t)eirqconf[i].eirqNumber;
    /* set rising edge event flag*/
    if (eirqconf[i].risingEdge == TRUE) {
      SIUL2.IREER0.R |= (1UL << eirqnum);
    }
    /* set falling edge event flag*/
    if (eirqconf[i].fallingEdge == TRUE) {
      SIUL2.IFEER0.R |= (1UL << eirqnum);
    }
    /* set antiglitch filter */
    if (eirqconf[i].filterEnable == TRUE) {
      SIUL2.IFER0.R |= (1UL << eirqnum);
    }
    /* enable eirq interrupt */
    SIUL2.DIRER0.R |= (1UL << eirqnum);
    i++;
  }
}

/** @} */
