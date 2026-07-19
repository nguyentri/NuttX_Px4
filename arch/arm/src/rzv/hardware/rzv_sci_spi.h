/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_sci_spi.h
 *
 * SPI-mode-specific bit definitions for SCI-B.
 *
 * ALL register offsets and base addresses are in hardware/rzv_sci.h.
 * This header contains ONLY SPI-mode-specific values not already defined
 * in hardware/rzv_sci.h — primarily CCR3.MOD value disambiguation and
 * the SPI frequency bounds used by the driver.
 *
 * (#14 fix: deleted RZV_SCIn_BASE / RZV_SCI_*_OFFSET duplicates)
 * (#32 fix: deleted RZV_SCI_RDR(ch) token-pasting macros — unused)
 *
 * Licensed under Apache License 2.0 — see top-level NOTICE.
 *
 ****************************************************************************/

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SCI_SPI_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SCI_SPI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include "hardware/rzv_sci.h"   /* All offsets, bases, and shared bit defs */

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* CCR3.MOD field values — SPI mode selection.
 * hardware/rzv_sci.h defines SCI_CCR3_MOD_SPI = (0x3 << 16) for
 * Simple-SPI mode (the mode used by this driver).
 * SCI_CCR3_MOD_CLOCK_SYNC = (0x1 << 16) is clock-synchronous (not SPI).
 * Alias provided for clarity in SPI-mode code.
 */

#define SCI_CCR3_MOD_SIMPLE_SPI     SCI_CCR3_MOD_SPI  /* Alias: explicit name */

/* CCR3.CKE field values for synchronous / SPI mode.
 * rzv_sci.h defines shift/mask only; concrete values used by SPI driver.
 * (These were in the old hardware/rzv_sci_spi.h and are SPI-specific.)
 */

#define SCI_CCR3_CKE_INT_SCK_IO  \
  (0u << SCI_CCR3_CKE_SHIFT)   /* Internal clock, SCK I/O disabled */
#define SCI_CCR3_CKE_INT_SCK_OUT \
  (1u << SCI_CCR3_CKE_SHIFT)   /* Internal clock, SCK output (master) */
#define SCI_CCR3_CKE_EXT_SCK_8X  \
  (2u << SCI_CCR3_CKE_SHIFT)   /* External clock, 8× oversampling */
#define SCI_CCR3_CKE_EXT_SCK_16X \
  (3u << SCI_CCR3_CKE_SHIFT)   /* External clock, 16× oversampling */

/* SPI-specific frequency bounds — single definition here (#11 fix: was
 * duplicated between rzv_sci_spi.h and rzv_sci_spi.c with same value).
 * Used by rzv_sci_spi.c and board-level code.
 */

#define RZV_SCI_SPI_MAX_FREQUENCY   25000000u  /* 25 MHz max */
#define RZV_SCI_SPI_MIN_FREQUENCY   1000u      /* 1 kHz min */

/* FIFO depth — used in FCR trigger-level calculations */

#define RZV_SCI_SPI_FIFO_DEPTH      16u

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SCI_SPI_H */
