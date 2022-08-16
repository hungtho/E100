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
 * @file    pal.c
 * @brief   SPC5xx SIUL2 low level driver code.
 *
 * @addtogroup PAL
 * @{
 */

#include "pal.h"

#if defined(SPC5_SIUL_SYSTEM_PINS)
static const unsigned system_pins[] = {SPC5_SIUL_SYSTEM_PINS};
#endif

/**
 * @brief   SPC5xx I/O ports configuration.
 *
 * @param[in] config    the SPC5xx ports configuration
 *
 * @notapi
 */
void pal_init(const PALConfig *config) {
  unsigned i;

#if defined(SPC5_SIUL2_PCTL)
  /* SIUL clock gating if present.*/
  SPCSetPeripheralClockMode(SPC5_SIUL2_PCTL,
      SPC5_ME_PCTL_RUN(2) | SPC5_ME_PCTL_LP(2));
#endif

  /* Initialize MSCR_MUX registers.*/
  i = 0;
  while (config->mscr_mux[i].mscr_index != -1) {
    SIUL2.MSCR_MUX[config->mscr_mux[i].mscr_index].R =
        config->mscr_mux[i].mscr_value;
    if (config->mscr_mux[i].mscr_io_index != -1) {
      /* Set for the input PINs the IBE to 1.*/
      SIUL2.MSCR_IO[config->mscr_mux[i].mscr_io_index].B.IBE = 1;
    }
    i++;
  }

  /* Initialize MSCR_IO registers for defined pads.*/
  i = 0;
  while (config->mscr_io[i].mscr_index != -1) {
    SIUL2.GPDO[config->mscr_io[i].mscr_index].R = config->mscr_io[i].gpdo_value;
    SIUL2.MSCR_IO[config->mscr_io[i].mscr_index].R =
        config->mscr_io[i].mscr_value;
    i++;
  }
}

/**
 * @brief   Reads a group of bits.
 *
 * @param[in] port      port identifier
 * @param[in] mask      group mask
 * @param[in] offset    group bit offset within the port
 * @return              The group logical states.
 *
 * @notapi
 */
ioportmask_t _pal_readgroup(ioportid_t port, ioportmask_t mask,
                            uint_fast8_t offset) {

  (void)port;
  (void)mask;
  (void)offset;
  return 0;
}

/**
 * @brief   Writes a group of bits.
 *
 * @param[in] port      port identifier
 * @param[in] mask      group mask
 * @param[in] offset    group bit offset within the port
 * @param[in] bits      bits to be written. Values exceeding the group width
 *                      are masked.
 *
 * @notapi
 */
void _pal_writegroup(ioportid_t port, ioportmask_t mask, uint_fast8_t offset,
                     ioportmask_t bits) {

  (void)port;
  (void)mask;
  (void)offset;
  (void)bits;
}

/**
 * @brief   Pads mode setup.
 * @details This function programs a pads group belonging to the same port
 *          with the specified mode.
 *
 * @param[in] port      the port identifier
 * @param[in] mask      the group mask. A '0' in the position i means that the
 *                      mode of pad i will be not changed, a '1' means that the
 *                      mode of pad i will be updated.
 * @param[in] mode      the mode
 *
 * @notapi
 */
void _pal_setgroupmode(ioportid_t port, ioportmask_t mask, iomode_t mode) {
  uint32_t pcr_index = (uint32_t)(port * PAL_IOPORTS_WIDTH);
  ioportmask_t m1 = 0x8000U;
  while (m1 != 0U) {
    if ((mask & m1) != 0U) {
      SIUL2.MSCR_IO[pcr_index].R = mode;
    }
    m1 >>= 1;
    ++pcr_index;
  }
}

/** @} */
