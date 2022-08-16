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
 * @file    osal.c
 * @brief   OSAL module code.
 *
 * @addtogroup OSAL
 * @{
 */

#include "osal.h"

/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

#if (OSAL_OS_ENABLE == FALSE)
#if (OSAL_SYSTIMER_ENABLE == TRUE)
#define OSAL_INIT()                         osalSysTimeInit()
#define OSAL_THREAD_DELAY_SEC(sec)          osalSysTimeDelayTicks(osalSysTime_S2ST(sec))
#define OSAL_THREAD_DELAY_MILLISEC(msec)    osalSysTimeDelayTicks(osalSysTime_MS2ST(msec))
#define OSAL_THREAD_DELAY_MICROSEC(usec)    osalSysTimeDelayTicks(osalSysTime_US2ST(usec))
#define OSAL_THREAD_GET_TICKS()             osalSysTimeGetTicks()
#else
#define OSAL_INIT()
#endif /* (OSAL_SYSTIMER_ENABLE == TRUE) */
#define OSAL_ENTER_CRITICAL()               osalIsrDisable()
#define OSAL_EXIT_CRITICAL()                osalIsrEnable()
#elif (OSAL_FREERTOS_ENABLE == TRUE)
#define OSAL_INIT()
#if (OSAL_SYSTIMER_ENABLE == TRUE)
#define OSAL_THREAD_DELAY_SEC(sec)          vTaskDelay(osalSysTime_S2ST(sec))
#define OSAL_THREAD_DELAY_MILLISEC(msec)    vTaskDelay(osalSysTime_MS2ST(msec))
#define OSAL_THREAD_DELAY_MICROSEC(usec)    vTaskDelay(osalSysTime_US2ST(usec))
#define OSAL_THREAD_GET_TICKS()             xTaskGetTickCount()
#endif /* (OSAL_SYSTIMER_ENABLE == TRUE) */
#define OSAL_ENTER_CRITICAL()               vTaskEnterCritical()
#define OSAL_EXIT_CRITICAL()                vTaskExitCritical()
#endif /* (OSAL_OS_ENABLE == FALSE) */

/*===========================================================================*/
/* Module exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

#if (OSAL_SYSTIMER_ENABLE == TRUE)
#if (OSAL_OS_ENABLE == FALSE)
/**
 * @brief   System time.
 */
static volatile osalsystime_t osalsystime;
#endif /* (OSAL_OS_ENABLE == FALSE) */

/**
 * @brief   System time number of ticks per second.
 */
static uint32_t osal_ticks_per_sec = 0;
#endif /* (OSAL_SYSTIMER_ENABLE == TRUE) */

#if (OSAL_OS_ENABLE == FALSE)
/**
 * @brief   Interrupt enable/disable count.
 */
static uint32_t osalIsrCnt = 0;

/**
 * @brief   Interrupt enable/disable status.
 */
static uint32_t osalIsExtIntEnable = 0;
#endif /* (OSAL_OS_ENABLE == FALSE) */

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

#if (OSAL_SYSTIMER_ENABLE == TRUE)
/**
 * @brief   Configures and enables the System Timer.
 *
 * @param[in] ticks_per_sec      number of ticks per second
 *
 * @notapi
 */
void osalSysTimeSetup(uint32_t ticks_per_sec)
{

  osal_ticks_per_sec = ticks_per_sec;

  sysTimeSetup(ticks_per_sec);
}

/**
 * @brief   Reset the System Timer.
 *
 * @notapi
 */
void osalSysTimeReset(void)
{
  /* Resets the PIT channel 0 IRQ flag.*/
  sysTimeReset();
}

/**
 * @brief   Seconds to system ticks.
 * @details Converts from seconds to system ticks number.
 * @note    The result is rounded upward to the next tick boundary.
 *
 * @param[in] sec       number of seconds
 * @return              The number of ticks.
 *
 * @noapi
 */
static inline osalsystime_t osalSysTime_S2ST(uint32_t sec) {
  return ((osalsystime_t)((sec) * (osal_ticks_per_sec)));
}

/**
 * @brief   Milliseconds to system ticks.
 * @details Converts from milliseconds to system ticks number.
 * @note    The result is rounded upward to the next tick boundary.
 *
 * @param[in] msec      number of milliseconds
 * @return              The number of ticks.
 *
 * @noapi
 */
static inline osalsystime_t osalSysTime_MS2ST(uint32_t msec) {
  return ((msec == 0U) ? ((osalsystime_t) 0) :
                         ((osalsystime_t)((((msec) * (osal_ticks_per_sec) - 1UL) / 1000UL) + 1UL)));
}

/**
 * @brief   Microseconds to system ticks.
 * @details Converts from microseconds to system ticks number.
 * @note    The result is rounded upward to the next tick boundary.
 *
 * @param[in] usec      number of microseconds
 * @return              The number of ticks.
 *
 * @noapi
 */
static inline osalsystime_t osalSysTime_US2ST(uint32_t usec) {
  return ((usec == 0U) ? ((osalsystime_t) 0) :
                         ((osalsystime_t)((((usec) * (osal_ticks_per_sec) - 1UL) / 1000000UL) + 1UL)));
}

/**
 * @brief   System ticks to seconds.
 * @details Converts from system ticks number to seconds.
 * @note    The result is rounded downward.
 *
 * @param[in] ticks     number of ticks
 * @return              The number of seconds.
 *
 * @noapi
 */
static inline uint32_t osalSysTime_ST2S(osalsystime_t ticks) {
  return ((uint32_t)(((osalsystime_t)ticks) / osal_ticks_per_sec));
}

/**
 * @brief   System ticks to milliseconds.
 * @details Converts from system ticks number to milliseconds.
 * @note    The result is rounded downward.
 *
 * @param[in] ticks     number of ticks
 * @return              The number of milliseconds.
 *
 * @noapi
 */
static inline uint32_t osalSysTime_ST2MS(osalsystime_t ticks) {
  return ((uint32_t)((((osalsystime_t)ticks) * 1000UL) / osal_ticks_per_sec));
}

/**
 * @brief   System ticks to microseconds.
 * @details Converts from system ticks number to microseconds.
 * @note    The result is rounded downward.
 *
 * @param[in] ticks     number of ticks
 * @return              The number of microseconds.
 *
 * @noapi
 */
static inline uint32_t osalSysTime_ST2US(osalsystime_t ticks) {
  return ((uint32_t)((((osalsystime_t)ticks) * 1000000UL) / osal_ticks_per_sec));
}

#if (OSAL_OS_ENABLE == FALSE)
/**
 * @brief   System Time Initialization.
 *
 * @notapi
 */
static void osalSysTimeInit(void) {

  /* System time initialization.*/
  osalsystime = 0;

  osalSysTimeSetup((uint32_t)OSAL_SYSTIMER_TICK_FREQ_HZ);
}

/**
 * @brief   Delays for the specified number of ticks.
 *
 * @param[in] ticks     number of ticks
 *
 * @notapi
 */
static void osalSysTimeDelayTicks(osalsystime_t ticks) {

  osalsystime_t current;
  
  current = osalsystime;
  while (osalsystime < current + ticks) {
  }

}

/**
 * @brief   Returns the current number of ticks.
 *
 * @return              The number of ticks.
 *
 * @notapi
 */
static uint32_t osalSysTimeGetTicks(void) {

  return osalsystime;
}
#endif /* (OSAL_OS_ENABLE == FALSE) */
#endif /* (OSAL_SYSTIMER_ENABLE == TRUE) */

#if (OSAL_OS_ENABLE == FALSE)
/**
 * @brief   If enabled, disables the interrupts.
 *
 * @notapi
 */
static void osalIsrDisable(void) {

  osalIsrCnt++;
  if (osalIsrCnt == 1U) {
    osalIsExtIntEnable = irqGetExtIntEnable();
    if (osalIsExtIntEnable != 0U) {
      irqIsrDisable();
    }
  }
}

/**
 * @brief   If previously enabled, re-enables the interrupts.
 *
 * @notapi
 */
static void osalIsrEnable(void) {

  osalIsrCnt--;
  if ((osalIsExtIntEnable != 0U) && (osalIsrCnt == 0U)) {
    irqIsrEnable();
  }
}
#endif /* (OSAL_OS_ENABLE == FALSE) */

/*===========================================================================*/
/* Module interrupt handlers.                                                */
/*===========================================================================*/

#if (OSAL_SYSTIMER_ENABLE == TRUE)
#if (OSAL_OS_ENABLE == FALSE)
/**
 * @brief   PIT channel 0 interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(OSAL_SYSTIMER_IRQ_HANDLER) {

  IRQ_PROLOGUE();

  osalEnterCriticalFromISR();
  
  osalsystime++;
  
  osalExitCriticalFromISR();

  osalSysTimeReset();

  IRQ_EPILOGUE();
}
#endif /* (OSAL_OS_ENABLE == FALSE) */
#endif /* (OSAL_SYSTIMER_ENABLE == TRUE) */

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

#if (OSAL_SYSTIMER_ENABLE == TRUE)
/**
 * @brief   Delays for the specified number of seconds.
 * @note    The specified time is rounded up to a value allowed by the real
 *          system tick clock.
 * @note    The maximum specifiable value is implementation dependent.
 *
 * @param[in] sec       time in seconds, must be different from zero
 *
 * @api
 */
void osalThreadDelaySeconds(uint32_t sec) {

  OSAL_THREAD_DELAY_SEC(sec);
}

/**
 * @brief   Delays for the specified number of milliseconds.
 * @note    The specified time is rounded up to a value allowed by the real
 *          system tick clock.
 * @note    The maximum specifiable value is implementation dependent.
 *
 * @param[in] msec      time in milliseconds, must be different from zero
 *
 * @api
 */
void osalThreadDelayMilliseconds(uint32_t msec) {

  OSAL_THREAD_DELAY_MILLISEC(msec);
}

/**
 * @brief   Delays for the specified number of microseconds.
 * @note    The specified time is rounded up to a value allowed by the real
 *          system tick clock.
 * @note    The maximum specifiable value is implementation dependent.
 *
 * @param[in] usec      time in microseconds, must be different from zero
 *
 * @api
 */
void osalThreadDelayMicroseconds(uint32_t usec) {

  OSAL_THREAD_DELAY_MICROSEC(usec);
}

/**
 * @brief   Returns the number of seconds since System Timer init.
 *
 * @return              number of seconds.
 *
 * @api
 */
uint32_t osalThreadGetSeconds(void) {

  return osalSysTime_ST2S(OSAL_THREAD_GET_TICKS());
}

/**
 * @brief   Returns the number of milliseconds since System Timer init.
 *
 * @return              number of milliseconds.
 *
 * @api
 */
uint32_t osalThreadGetMilliseconds(void) {

  return osalSysTime_ST2MS(OSAL_THREAD_GET_TICKS());
}

/**
 * @brief   Returns the number of microseconds since System Timer init.
 *
 * @return              number of microseconds.
 *
 * @api
 */
uint32_t osalThreadGetMicroseconds(void) {

  return osalSysTime_ST2US(OSAL_THREAD_GET_TICKS());
}

#endif /* (OSAL_SYSTIMER_ENABLE == TRUE) */

#if CORE_SUPPORTS_IVORS
  extern void _spr_init(void);
#endif

/**
 * @brief   OSAL module initialization.
 *
 * @api
 */
void osalInit(void) {

#if CORE_SUPPORTS_IVORS
  _spr_init();
#endif
  OSAL_INIT();
}

/**
 * @brief   Enters a critical zone.
 *
 * @api
 */
void osalEnterCritical(void) {

  OSAL_ENTER_CRITICAL();
}

/**
 * @brief   Leaves a critical zone.
 *
 * @api
 */
void osalExitCritical(void) {

  OSAL_EXIT_CRITICAL();
}

/**
 * @brief   Enters a critical zone from ISR.
 *
 * @api
 */
void osalEnterCriticalFromISR(void) {

#if (OSAL_ENABLE_IRQ_PREEMPTION == TRUE)
  OSAL_ENTER_CRITICAL();
#endif
}

/**
 * @brief   Leaves a critical zone from ISR.
 *
 * @api
 */
void osalExitCriticalFromISR(void) {

#if (OSAL_ENABLE_IRQ_PREEMPTION == TRUE)
  OSAL_EXIT_CRITICAL();
#endif
}

/** @} */
