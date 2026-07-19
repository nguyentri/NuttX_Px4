/****************************************************************************
 * arch/arm/src/rzv/rzv_sci_spi_internal.h
 *
 * Private types and prototypes shared between rzv_sci_spi.c,
 * rzv_sci_spi_isr.c, and rzv_sci_spi_clock.c.
 *
 * Licensed under Apache License 2.0 — see top-level NOTICE.
 *
 ****************************************************************************/

#ifndef __ARCH_ARM_SRC_RZV_RZV_SCI_SPI_INTERNAL_H
#define __ARCH_ARM_SRC_RZV_RZV_SCI_SPI_INTERNAL_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>
#include <nuttx/semaphore.h>
#include <nuttx/mutex.h>
#include <nuttx/spi/spi.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Transfer timeout (ms) — matches sci_i2c pattern */

#define SCI_SPI_TIMEOUT_MS          1000

/* CESR poll iterations for TE/RE enable/disable acknowledgement */

#define SCI_SPI_CESR_TIMEOUT        10000u

/* SPI clock source is P5CLK (100 MHz) — same as I2C */

#define SCI_SPI_PCLK_FALLBACK_HZ    RZV_CLOCK_P5CLK_HZ

/* Default SPI frequency when not yet set */

#define SCI_SPI_DEFAULT_HZ          1000000u   /* 1 MHz */

/* Maximum number of SCI channels with SPI support */

#define SCI_SPI_MAX_CHANNELS        10

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* Transfer state machine */

enum rzv_sci_spi_state_e
{
  SCI_SPI_STATE_IDLE = 0,   /* No transfer in progress */
  SCI_SPI_STATE_BUSY,       /* Transfer running */
  SCI_SPI_STATE_DONE,       /* Transfer complete (success) */
  SCI_SPI_STATE_ERROR,      /* Transfer aborted by ERI */
};

/* Per-channel private structure (static, no heap allocation) */

struct rzv_sci_spi_priv_s
{
  /* NuttX SPI device — MUST be first so casts work */

  struct spi_dev_s          dev;

  /* Channel configuration (compile-time) */

  uint8_t                   channel;   /* 0..9 */
  uint32_t                  base;      /* SCI base address */
  uint32_t                  clk_id;   /* RZV_CPG_CLK_SCIn */
  int                       evt_txi;  /* ELC event for TXI */
  int                       evt_rxi;  /* ELC event for RXI */
  int                       evt_tei;  /* ELC event for TEI */
  int                       evt_eri;  /* ELC event for ERI */

  /* Allocated IRQ numbers (from rzv_icu_attach) */

  int                       irq_txi;
  int                       irq_rxi;
  int                       irq_tei;
  int                       irq_eri;

  /* Exclusive-access mutex and completion semaphore */

  mutex_t                   lock;     /* Per-device bus lock */
  sem_t                     sem_isr;  /* 0 = waiting; ISR posts on done/error */

  /* Current SPI configuration */

  uint32_t                  frequency;  /* Current target frequency (Hz) */
  uint32_t                  actual;     /* Actual configured frequency (Hz) */
  enum spi_mode_e           mode;       /* Current SPI mode (0..3) */
  uint8_t                   nbits;      /* Word size (8 only) */
  bool                      lsbfirst;   /* LSB-first bit order */

  /* Current transfer context (ISR writes, exchange() reads) */

  const uint8_t            *txbuffer;   /* TX data pointer (NULL = send 0xFF) */
  uint8_t                  *rxbuffer;   /* RX data pointer (NULL = discard) */
  volatile size_t           ntxwords;   /* TX bytes remaining */
  volatile size_t           nrxwords;   /* RX bytes remaining */
  volatile enum rzv_sci_spi_state_e state;

  bool                      initialized;
  bool                      initializing;
};

/****************************************************************************
 * Function Prototypes (cross-file, not public API)
 ****************************************************************************/

/* rzv_sci_spi_clock.c */

int rzv_sci_spi_calc_bitrate(uint32_t pclk_hz, uint32_t bitrate,
                             uint8_t *brr, uint8_t *cks, uint8_t *mddr);
uint32_t rzv_sci_spi_actual_bitrate(uint32_t pclk_hz, uint8_t brr,
                                    uint8_t cks, uint8_t mddr);

/* rzv_sci_spi_isr.c */

int rzv_sci_spi_txi_isr(int irq, void *context, void *arg);
int rzv_sci_spi_rxi_isr(int irq, void *context, void *arg);
int rzv_sci_spi_tei_isr(int irq, void *context, void *arg);
int rzv_sci_spi_eri_isr(int irq, void *context, void *arg);

#endif /* __ARCH_ARM_SRC_RZV_RZV_SCI_SPI_INTERNAL_H */
