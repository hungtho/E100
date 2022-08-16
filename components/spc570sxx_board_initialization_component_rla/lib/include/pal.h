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
 * @file    pal.h
 * @brief   SPC5xx SIUL2 low level driver header.
 *
 * @addtogroup PAL
 * @{
 */

#ifndef _PAL_H_
#define _PAL_H_

#include "platform.h"
#include "clock.h"

/**
 * @name    Logic level constants
 * @{
 */
/**
 * @brief   Logical low state.
 */
#define PAL_LOW                         0U

/**
 * @brief   Logical high state.
 */
#define PAL_HIGH                        1U
/** @} */

/*===========================================================================*/
/* Unsupported modes and specific modes                                      */
/*===========================================================================*/

#undef PAL_MODE_RESET
#undef PAL_MODE_UNCONNECTED
#undef PAL_MODE_INPUT
#undef PAL_MODE_INPUT_PULLUP
#undef PAL_MODE_INPUT_PULLDOWN
#undef PAL_MODE_INPUT_ANALOG
#undef PAL_MODE_OUTPUT_PUSHPULL
#undef PAL_MODE_OUTPUT_OPENDRAIN

/**
 * @name    SIUL2-specific PAL modes
 * @{
 */
#define PAL_SPC5_OERC_MASK          (3UL << 28)
#define PAL_SPC5_OERC(n)            ((uint32_t)(n) << 28)
#define PAL_SPC5_OERC_WEAK          PAL_SPC5_OERC(0)
#define PAL_SPC5_OERC_MEDIUM        PAL_SPC5_OERC(1)
#define PAL_SPC5_OERC_STRONG        PAL_SPC5_OERC(2)
#define PAL_SPC5_OERC_VERY_STRONG   PAL_SPC5_OERC(3)
#if defined(_SPC570Sxx_) ||  defined(_SPC574Sxx_)
#define PAL_SPC5_ODC_MASK           (3UL << 24)
#else
#define PAL_SPC5_ODC_MASK           (7UL << 24)
#endif
#define PAL_SPC5_ODC(n)             ((uint32_t)(n) << 24)
#define PAL_SPC5_ODC_DISABLED       PAL_SPC5_ODC(0)
#define PAL_SPC5_ODC_OPEN_DRAIN     PAL_SPC5_ODC(1)
#define PAL_SPC5_ODC_PUSH_PULL      PAL_SPC5_ODC(2)
#define PAL_SPC5_ODC_OPEN_SOURCE    PAL_SPC5_ODC(3)
#if !defined(_SPC570Sxx_)
#define PAL_SPC5_ODC_MSC_LVDS       PAL_SPC5_ODC(4)
#define PAL_SPC5_ODC_LFAST_LVDS     PAL_SPC5_ODC(5)
#endif
#define PAL_SPC5_SMC                (1UL << 23)
#define PAL_SPC5_APC                (1UL << 22)
#define PAL_SPC5_ILS_MASK           (3UL << 20)
#define PAL_SPC5_ILS(n)             ((uint32_t)(n) << 20)
#define PAL_SPC5_ILS_TTL            PAL_SPC5_ILS(0)
#define PAL_SPC5_ILS_LVDS           PAL_SPC5_ILS(1)
#define PAL_SPC5_ILS_CMOS           PAL_SPC5_ILS(2)
#define PAL_SPC5_IBE                (1UL << 19)
#define PAL_SPC5_HYS                (1UL << 18)
#define PAL_SPC5_WPDE               (1UL << 17)
#define PAL_SPC5_WPUE               (1UL << 16)
#define PAL_SPC5_INV                (1UL << 15)
#define PAL_SPC5_SSS_MASK           (255UL << 0)
#define PAL_SPC5_SSS(n)             ((uint32_t)(n) << 0)
/** @} */

/**
 * @name    Pads mode constants
 * @{
 */
/**
 * @brief   After reset state.
 */
#define PAL_MODE_RESET                  (PAL_SPC5_SMC | PAL_SPC5_IBE |      \
                                         PAL_SPC5_WPUE)

/**
 * @brief   Safe state for <b>unconnected</b> pads.
 */
#define PAL_MODE_UNCONNECTED            (PAL_SPC5_SMC | PAL_SPC5_IBE |      \
                                         PAL_SPC5_WPUE)

/**
 * @brief   Regular input high-Z pad.
 */
#define PAL_MODE_INPUT                  (PAL_SPC5_SMC | PAL_SPC5_IBE)

/**
 * @brief   Input pad with weak pull up resistor.
 */
#define PAL_MODE_INPUT_PULLUP           (PAL_SPC5_SMC | PAL_SPC5_IBE |      \
                                         PAL_SPC5_WPUE)

/**
 * @brief   Input pad with weak pull down resistor.
 */
#define PAL_MODE_INPUT_PULLDOWN         (PAL_SPC5_SMC | PAL_SPC5_IBE |      \
                                         PAL_SPC5_WPDE)

/**
 * @brief   Analog input mode.
 */
#if defined(_SPC570Sxx_) || defined(_SPC574Sxx_)
#define PAL_MODE_INPUT_ANALOG           (PAL_SPC5_SMC)
#else
#define PAL_MODE_INPUT_ANALOG           (PAL_SPC5_SMC | PAL_SPC5_APC)
#endif

/**
 * @brief   Push-pull output pad.
 */
#define PAL_MODE_OUTPUT_PUSHPULL        (PAL_SPC5_SMC |                     \
                                         PAL_SPC5_ODC_PUSH_PULL |           \
                                         PAL_SPC5_IBE)

/**
 * @brief   Open-drain output pad.
 */
#define PAL_MODE_OUTPUT_OPENDRAIN       (PAL_SPC5_SMC |                     \
                                         PAL_SPC5_ODC_OPEN_DRAIN |          \
                                         PAL_SPC5_IBE)
/**
 * @brief   Alternate "n" output pad.
 * @note    Both the IBE and ODC bits are specified in this mask.
 */
#define PAL_MODE_OUTPUT_ALTERNATE(n)    (PAL_SPC5_SMC |                     \
                                         PAL_SPC5_ODC_PUSH_PULL |           \
                                         PAL_SPC5_IBE |                     \
                                         PAL_SPC5_SSS(n))
/** @} */

/*===========================================================================*/
/* I/O Ports Types and constants.                                            */
/*===========================================================================*/

/**
 * @brief   Width, in bits, of an I/O port.
 */
#define PAL_IOPORTS_WIDTH 16U

/**
 * @brief   Whole port mask.
 * @brief   This macro specifies all the valid bits into a port.
 */
#define PAL_WHOLE_PORT ((ioportmask_t)0xFFFF)

/**
 * @brief   Digital I/O port sized unsigned type.
 */
typedef uint16_t ioportmask_t;

/**
 * @brief   Digital I/O modes.
 */
typedef uint32_t iomode_t;

/**
 * @brief   Port Identifier.
 * @details This type can be a scalar or some kind of pointer, do not make
 *          any assumption about it, use the provided macros when populating
 *          variables of this type.
 */
typedef uint32_t ioportid_t;

/**
 * @brief   SIUL2 MSCR_IO register initializer type.
 */
typedef struct {
  int16_t mscr_index;
  uint8_t gpdo_value;
  iomode_t mscr_value;
} spc_mscr_io_init_t;

/**
 * @brief   SIUL2 MSCR_MUX register initializer type.
 */
typedef struct {
  int16_t mscr_io_index;
  int16_t mscr_index;
  uint16_t mscr_value;
} spc_mscr_mux_init_t;

/**
 * @brief   Generic I/O ports static initializer.
 * @details An instance of this structure must be passed to @p palInit() at
 *          system startup time in order to initialized the digital I/O
 *          subsystem. This represents only the initial setup, specific pads
 *          or whole ports can be reprogrammed at later time.
 * @note    Implementations may extend this structure to contain more,
 *          architecture dependent, fields.
 */
typedef struct {
  const spc_mscr_io_init_t *mscr_io;
  const spc_mscr_mux_init_t *mscr_mux;
} PALConfig;

/*===========================================================================*/
/* I/O Ports Identifiers.                                                    */
/*===========================================================================*/

/**
 * @brief   I/O port A identifier.
 */
#define PORT_A          0U

/**
 * @brief   I/O port B identifier.
 */
#define PORT_B          1U

/**
 * @brief   I/O port C identifier.
 */
#define PORT_C          2U

/**
 * @brief   I/O port D identifier.
 */
#define PORT_D          3U

/**
 * @brief   I/O port E identifier.
 */
#define PORT_E          4U

/**
 * @brief   I/O port F identifier.
 */
#define PORT_F          5U

/**
 * @brief   I/O port G identifier.
 */
#define PORT_G          6U

/**
 * @brief   I/O port H identifier.
 */
#define PORT_H          7U

/**
 * @brief   I/O port I identifier.
 */
#define PORT_I          8U

/**
 * @brief   I/O port J identifier.
 */
#define PORT_J          9U

/**
 * @brief   I/O port K identifier.
 */
#define PORT_K          10U

/**
 * @brief   I/O port L identifier.
 */
#define PORT_L          11U

/**
 * @brief   I/O port M identifier.
 */
#define PORT_M          12U

/**
 * @brief   I/O port N identifier.
 */
#define PORT_N          13U

/**
 * @brief   I/O port O identifier.
 */
#define PORT_O          14U

/**
 * @brief   I/O port P identifier.
 */
#define PORT_P          15U

/*===========================================================================*/
/* Implementation, some of the following macros could be implemented as      */
/* functions, if so please put them in pal_lld.c.                            */
/*===========================================================================*/

/**
 * @brief   Port bit helper macro.
 * @note    Overrides the one in @p pal.h.
 *
 * @param[in] n         bit position within the port
 *
 * @return              The bit mask.
 */
#define PAL_PORT_BIT(n) ((ioportmask_t)(0x8000U >> (n)))

/**
 * @brief   Reads the physical I/O port states.
 *
 * @param[in] port      port identifier
 * @return              The port bits.
 *
 * @notapi
 */
#define pal_readport(port)                                              \
  (SIUL2.PGPDI[port].R)

/**
 * @brief   Reads the output latch.
 * @details The purpose of this function is to read back the latched output
 *          value.
 *
 * @param[in] port      port identifier
 * @return              The latched logical states.
 *
 * @notapi
 */
#define pal_readlatch(port)                                             \
  (SIUL2.PGPDO[port].R)

/**
 * @brief   Writes a bits mask on a I/O port.
 *
 * @param[in] port      port identifier
 * @param[in] bits      bits to be written on the specified port
 *
 * @notapi
 */
#define pal_writeport(port, bits)                                       \
  ((SIUL2.PGPDO)[port].R = (bits))

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
#define pal_readgroup(port, mask, offset)                               \
  _pal_lld_readgroup(port, mask, offset)

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
#define pal_writegroup(port, mask, offset, bits)                        \
  _pal_writegroup(port, mask, offset, bits)

/**
 * @brief   Pads group mode setup.
 * @details This function programs a pads group belonging to the same port
 *          with the specified mode.
 * @note    Programming an unknown or unsupported mode is silently ignored.
 *
 * @param[in] port      port identifier
 * @param[in] mask      group mask. A '0' in the position i means that the mode
 *                      of pad i will be not changed, a '1' means that the mode
 *                      of pad i will be updated.
 * @param[in] mode      group mode
 *
 * @notapi
 */
#define pal_setgroupmode(port, mask, mode)                              \
  _pal_setgroupmode(port, mask, mode)

/**
 * @brief   Reads a logical state from an I/O pad.
 * @note    The @ref PAL provides a default software implementation of this
 *          functionality, implement this function if can optimize it by using
 *          special hardware functionalities or special coding.
 *
 * @param[in] port      port identifier
 * @param[in] pad       pad number within the port
 * @return              The logical state.
 * @retval PAL_LOW      low logical state.
 * @retval PAL_HIGH     high logical state.
 *
 * @notapi
 */
#define pal_readpad(port, pad)                                          \
  (SIUL2.GPDI[((port) * 16U) + (pad)].R)

/**
 * @brief   Writes a logical state on an output pad.
 * @note    This function is not meant to be invoked directly by the
 *          application  code.
 * @note    The @ref PAL provides a default software implementation of this
 *          functionality, implement this function if can optimize it by using
 *          special hardware functionalities or special coding.
 *
 * @param[in] port      port identifier
 * @param[in] pad       pad number within the port
 * @param[in] bit       logical value, the value must be @p PAL_LOW or
 *                      @p PAL_HIGH
 *
 * @notapi
 */
#define pal_writepad(port, pad, bit)                                    \
  (SIUL2.GPDO[((port) * 16U) + (pad)].R = (bit))

/**
 * @brief   Sets a pad logical state to @p PAL_HIGH.
 *
 * @param[in] port      port identifier
 * @param[in] pad       pad number within the port
 *
 * @notapi
 */
#define pal_setpad(port, pad)                                           \
  (SIUL2.GPDO[((port) * 16U) + (pad)].R = 1)

/**
 * @brief   Clears a pad logical state to @p PAL_LOW.
 *
 * @param[in] port      port identifier
 * @param[in] pad       pad number within the port
 *
 * @notapi
 */
#define pal_clearpad(port, pad)                                         \
  (SIUL2.GPDO[((port) * 16U) + (pad)].R = 0)

/**
 * @brief   Toggles a pad logical state.
 * @note    The @ref PAL provides a default software implementation of this
 *          functionality, implement this function if can optimize it by using
 *          special hardware functionalities or special coding.
 *
 * @param[in] port      port identifier
 * @param[in] pad       pad number within the port
 *
 * @notapi
 */
#define pal_togglepad(port, pad)                                        \
  (SIUL2.GPDO[((port) * 16U) + (pad)].R = ~SIUL2.GPDO[((port) * 16U) + (pad)].R)

/**
 * @brief   Pad mode setup.
 * @details This function programs a pad with the specified mode.
 * @note    The @ref PAL provides a default software implementation of this
 *          functionality, implement this function if can optimize it by using
 *          special hardware functionalities or special coding.
 * @note    Programming an unknown or unsupported mode is silently ignored.
 *
 * @param[in] port      port identifier
 * @param[in] pad       pad number within the port
 * @param[in] mode      pad mode
 *
 * @notapi
 */
#define pal_setpadmode(port, pad, mode)

#ifdef __cplusplus
extern "C" {
#endif
  void pal_init(const PALConfig *config);
  ioportmask_t _pal_readgroup(ioportid_t port, ioportmask_t mask,
                              uint_fast8_t offset);
  void _pal_writegroup(ioportid_t port, ioportmask_t mask, uint_fast8_t offset,
                       ioportmask_t bits);
  void _pal_setgroupmode(ioportid_t port, ioportmask_t mask, iomode_t mode);
#ifdef __cplusplus
}
#endif

#endif /* _PAL_H_ */

/** @} */
