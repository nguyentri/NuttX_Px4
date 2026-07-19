/****************************************************************************
 * arch/arm/src/rzv/rzv_sci_spi.h
 *
 * Public API for the RZ/V2H SCI-B SPI master driver (Simple-SPI mode,
 * interrupt-driven, CPU-mode only).
 *
 * Board integration ABI
 * ---------------------
 * The board configures MOSI, MISO, SCK, and chip-select before calling
 * rzv_sci_spi_initialize(). Pin routing is board-specific and is not
 * selected by this lower-half.
 *
 * The board must also provide weak overrides for:
 *   void rzv_sci_spi_select(struct spi_dev_s *, uint32_t devid, bool sel)
 *   uint8_t rzv_sci_spi_status(struct spi_dev_s *, uint32_t devid)
 *
 * Licensed under Apache License 2.0 — see top-level NOTICE.
 *
 ****************************************************************************/

#ifndef __ARCH_ARM_SRC_RZV_RZV_SCI_SPI_H
#define __ARCH_ARM_SRC_RZV_RZV_SCI_SPI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/spi/spi.h>

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef CONFIG_RZV_SCI_SPI

/****************************************************************************
 * Name: rzv_sci_spi_initialize
 *
 * Description:
 *   Initialise a SCI channel as SPI master (Simple-SPI mode).
 *
 * Input Parameters:
 *   channel - SCI channel index (0..9); must match an enabled
 *             CONFIG_RZV_SCIn_SPI Kconfig option.
 *
 * Returned Value:
 *   Pointer to struct spi_dev_s on success.
 *   NULL if channel not enabled, IRQ attach fails, or clock error.
 *
 * Notes:
 *   - Call once per channel; subsequent calls return the same pointer.
 *   - Pass the returned pointer to spi_register() (board glue).
 *   - Driver is CPU-mode only (no DMAC).
 *   - Only 8-bit word size supported.
 *
 ****************************************************************************/

struct spi_dev_s *rzv_sci_spi_initialize(int channel);

#endif /* CONFIG_RZV_SCI_SPI */

#endif /* __ARCH_ARM_SRC_RZV_RZV_SCI_SPI_H */
