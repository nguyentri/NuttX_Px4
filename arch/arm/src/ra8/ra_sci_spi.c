/****************************************************************************
 * arch/arm/src/ra8/ra_sci_spi.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <debug.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/mutex.h>
#include <nuttx/semaphore.h>
#include <nuttx/spi/spi.h>
#include <nuttx/power/pm.h>

#include <arch/board/board.h>
#include <arch/ra8/irq.h>

#include "arm_internal.h"
#include "chip.h"
#include "hardware/ra_memorymap.h"
#include "barriers.h"

#include "ra_clock.h"
#include "ra_dtc.h"
#include "ra_dmac.h"
#include "ra_mstp.h"
#include "ra_sci_spi.h"
#include "ra_icu.h"

#include <nuttx/cache.h>

#ifdef CONFIG_RA_SCI_SPI

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SCI_SPI Maximum frequency */
#define R_SCI_SPI_MAX_FREQUENCY      50000000

/* SCI_SPI Timeout */
#define R_SCI_SPI_TIMEOUT_MS         1000

/* Clock calculation constants */
#define R_SCI_SPI_CLK_MAX_N          (0xFFU)
#define R_SCI_SPI_CLK_MAX_n          (3U)
#define R_SCI_SPI_CLK_MAX_DIV        ((R_SCI_SPI_CLK_MAX_N + 1) * \
                                      (1 << (2 * R_SCI_SPI_CLK_MAX_n)))

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* SCI_SPI Device hardware configuration */
struct ra_sci_spi_config_s
{
  uint32_t base;              /* SCI_SPI base address */
  uint8_t  channel;           /* SCI channel number (0-9) */
  uint32_t rxi_elc;           /* RXI ELC event number */
  uint32_t txi_elc;           /* TXI ELC event number */
  uint32_t tei_elc;           /* TEI ELC event number */
  uint32_t eri_elc;           /* ERI ELC event number */
  uint32_t mstp;              /* MSTP bit number */
};

/* SCI_SPI Device Private Data */
struct ra_sci_spi_priv_s
{
  struct spi_dev_s             spidev;       /* Externally visible part of the SPI interface */
  const struct ra_sci_spi_config_s *config;  /* Port configuration */

  mutex_t                      lock;         /* Held while chip is selected for mutual exclusion */
  sem_t                        sem_isr;      /* Interrupt wait semaphore */

  uint32_t                     frequency;    /* Requested clock frequency */
  uint32_t                     actual_frequency; /* Actual clock frequency */
  enum spi_mode_e              mode;         /* Mode 0-3 */
  uint8_t                      nbits;        /* Width of word in bits (7, 8, or 9) */
  bool                         lsbfirst;     /* True: LSB first */
  uint32_t                     devid;        /* Currently selected device ID */
  bool                         initialized;  /* Initialization flag */

  /* Runtime IRQ numbers assigned by ICU (FIX CD#4) */
  int                          rxi_irq;      /* RX interrupt number */
  int                          txi_irq;      /* TX interrupt number */
  int                          tei_irq;      /* Transfer end interrupt number */
  int                          eri_irq;      /* Error interrupt number */

  /* Transfer state */
  const uint8_t               *txbuffer;     /* Source buffer for TX */
  uint8_t                     *rxbuffer;     /* Dest buffer for RX */
  size_t                       ntxwords;     /* Num words to transmit */
  size_t                       nrxwords;     /* Num words to receive */
  size_t                       txidx;        /* Current TX index */
  size_t                       rxidx;        /* Current RX index */
  bool                         error;        /* Transfer error flag */

  /* DTC support for high-performance transfers */
#ifdef CONFIG_RA_DTC
  ra_dtc_handle_t              dtc_tx_handle; /* TX DTC handle */
  ra_dtc_handle_t              dtc_rx_handle; /* RX DTC handle */
  bool                         use_dtc;       /* DTC enabled for this transfer */
#endif

  /* DMAC support for even higher performance */
#ifdef CONFIG_RA_DMAC
  ra_dmac_handle_t             dma_tx_handle; /* TX DMAC handle */
  ra_dmac_handle_t             dma_rx_handle; /* RX DMAC handle */
  volatile bool                dma_tx_done;   /* TX DMA completion flag */
  volatile bool                dma_rx_done;   /* RX DMA completion flag */
  bool                         use_dma;       /* DMAC enabled for this transfer */
#endif

#ifdef CONFIG_PM
  struct pm_callback_s         pmcb;         /* PM callbacks */
#endif
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Low-level helpers */
static void ra_sci_spi_putreg32(struct ra_sci_spi_priv_s *priv,
                                uint8_t offset, uint32_t value);
static uint32_t ra_sci_spi_getreg32(struct ra_sci_spi_priv_s *priv,
                                    uint8_t offset);
static void ra_sci_spi_putreg8(struct ra_sci_spi_priv_s *priv,
                               uint8_t offset, uint8_t value);
static uint8_t ra_sci_spi_getreg8(struct ra_sci_spi_priv_s *priv,
                                  uint8_t offset);

/* Hardware configuration */
static void ra_sci_spi_hw_initialize(struct ra_sci_spi_priv_s *priv);
static void ra_sci_spi_hw_configure(struct ra_sci_spi_priv_s *priv);
static int ra_sci_spi_calculate_bitrate(uint32_t bitrate,
                                        bool use_scispiclk,
                                        uint8_t *brr, uint8_t *cks,
                                        uint8_t *bgdm);

/* DTC support */
#ifdef CONFIG_RA_DTC
static int ra_sci_spi_dtc_setup(struct ra_sci_spi_priv_s *priv);
static void ra_sci_spi_dtc_start(struct ra_sci_spi_priv_s *priv);
static void ra_sci_spi_dtc_stop(struct ra_sci_spi_priv_s *priv);
static int ra_sci_spi_dtc_configure_transfer(struct ra_sci_spi_priv_s *priv,
                                            const void *txbuffer,
                                            void *rxbuffer,
                                            size_t nwords);
#endif

/* DMAC support */
#ifdef CONFIG_RA_DMAC
static int ra_sci_spi_dma_setup(struct ra_sci_spi_priv_s *priv);
static int ra_sci_spi_dma_transfer(struct ra_sci_spi_priv_s *priv,
                                   const void *txbuffer,
                                   void *rxbuffer,
                                   size_t nwords);
static void ra_sci_spi_dma_stop(struct ra_sci_spi_priv_s *priv);
static void ra_sci_spi_dma_tx_callback(void *handle, int event, void *arg);
static void ra_sci_spi_dma_rx_callback(void *handle, int event, void *arg);
#endif

/* Transfer helpers */
static void ra_sci_spi_writeword(struct ra_sci_spi_priv_s *priv,
                                 uint8_t data);
static uint8_t ra_sci_spi_readword(struct ra_sci_spi_priv_s *priv);
static void ra_sci_spi_configure_fifo(struct ra_sci_spi_priv_s *priv,
                                      size_t nwords);
static void ra_sci_spi_enable(struct ra_sci_spi_priv_s *priv);
static void ra_sci_spi_disable(struct ra_sci_spi_priv_s *priv);

/* Interrupt handling */
static int ra_sci_spi_rxi_interrupt(int irq, void *context, void *arg);
static int ra_sci_spi_txi_interrupt(int irq, void *context, void *arg);
static int ra_sci_spi_tei_interrupt(int irq, void *context, void *arg);
static int ra_sci_spi_eri_interrupt(int irq, void *context, void *arg);

/* SPI methods */
static int ra_sci_spi_lock(struct spi_dev_s *dev, bool lock);
static uint32_t ra_sci_spi_setfrequency(struct spi_dev_s *dev,
                                        uint32_t frequency);
static void ra_sci_spi_setmode(struct spi_dev_s *dev, enum spi_mode_e mode);
static void ra_sci_spi_setbits(struct spi_dev_s *dev, int nbits);
#ifdef CONFIG_SPI_HWFEATURES
static int ra_sci_spi_hwfeatures(struct spi_dev_s *dev,
                                 spi_hwfeatures_t features);
#endif
static uint32_t ra_sci_spi_send(struct spi_dev_s *dev, uint32_t wd);
static void ra_sci_spi_exchange(struct spi_dev_s *dev,
                                const void *txbuffer,
                                void *rxbuffer, size_t nwords);
#ifndef CONFIG_SPI_EXCHANGE
static void ra_sci_spi_sndblock(struct spi_dev_s *dev,
                                const void *txbuffer,
                                size_t nwords);
static void ra_sci_spi_recvblock(struct spi_dev_s *dev, void *rxbuffer,
                                 size_t nwords);
#endif

/* Weak external functions */
const struct ra_sci_spi_ext_dev_config_s *
weak_function ra_sci_spi_get_dev_config(struct spi_dev_s *dev,
                                        uint32_t devid);

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* SCI_SPI operations */
static const struct spi_ops_s ra_sci_spi_ops =
{
  .lock              = ra_sci_spi_lock,
  .select            = ra_sci_spi_select,     /* Provided externally */
  .setfrequency      = ra_sci_spi_setfrequency,
  .setmode           = ra_sci_spi_setmode,
  .setbits           = ra_sci_spi_setbits,
#ifdef CONFIG_SPI_HWFEATURES
  .hwfeatures        = ra_sci_spi_hwfeatures,
#endif
  .status            = ra_sci_spi_status,     /* Provided externally */
#ifdef CONFIG_SPI_CMDDATA
  .cmddata           = ra_sci_spi_cmddata,    /* Provided externally */
#endif
  .send              = ra_sci_spi_send,
#ifdef CONFIG_SPI_EXCHANGE
  .exchange          = ra_sci_spi_exchange,
#else
  .sndblock          = ra_sci_spi_sndblock,
  .recvblock         = ra_sci_spi_recvblock,
#endif
#ifdef CONFIG_SPI_CALLBACK
  .registercallback  = ra_sci_spi_register_callback, /* Provided externally */
#endif
};

/* SCI_SPI device configurations */
#ifdef CONFIG_RA_SCI0_SPI
static const struct ra_sci_spi_config_s ra_sci0_spi_config =
{
  .base     = R_SCI_B_CH_BASE(0),
  .channel  = 0,
  .rxi_elc  = RA_ELC_SCI0_RXI,
  .txi_elc  = RA_ELC_SCI0_TXI,
  .tei_elc  = RA_ELC_SCI0_TEI,
  .eri_elc  = RA_ELC_SCI0_ERI,
  .mstp     = RA_MSTP_SCI0,
};

static struct ra_sci_spi_priv_s ra_sci0_spi_priv =
{
  .spidev =
  {
    .ops = &ra_sci_spi_ops,
  },
  .config = &ra_sci0_spi_config,
  .devid = 0xffffffff,
  .initialized = false,
};
#endif

#ifdef CONFIG_RA_SCI1_SPI
static const struct ra_sci_spi_config_s ra_sci1_spi_config =
{
  .base     = R_SCI_B_CH_BASE(1),
  .channel  = 1,
  .rxi_elc  = RA_ELC_SCI1_RXI,
  .txi_elc  = RA_ELC_SCI1_TXI,
  .tei_elc  = RA_ELC_SCI1_TEI,
  .eri_elc  = RA_ELC_SCI1_ERI,
  .mstp     = RA_MSTP_SCI1,
};

static struct ra_sci_spi_priv_s ra_sci1_spi_priv =
{
  .spidev =
  {
    .ops = &ra_sci_spi_ops,
  },
  .config = &ra_sci1_spi_config,
  .devid = 0xffffffff,
  .initialized = false,
};
#endif

/* Additional SCI channels 2-9 would follow the same pattern */

/* DTC initialization flag */
#ifdef CONFIG_RA_DTC
static bool g_dtc_initialized = false;
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_sci_spi_putreg32
 *
 * Description:
 *   Write a 32-bit value to an SCI_SPI register
 *
 ****************************************************************************/

static void ra_sci_spi_putreg32(struct ra_sci_spi_priv_s *priv,
                                uint8_t offset, uint32_t value)
{
  putreg32(value, priv->config->base + offset);
}

/****************************************************************************
 * Name: ra_sci_spi_getreg32
 *
 * Description:
 *   Read a 32-bit value from an SCI_SPI register
 *
 ****************************************************************************/

static uint32_t ra_sci_spi_getreg32(struct ra_sci_spi_priv_s *priv,
                                    uint8_t offset)
{
  return getreg32(priv->config->base + offset);
}

/****************************************************************************
 * Name: ra_sci_spi_putreg8
 *
 * Description:
 *   Write an 8-bit value to an SCI_SPI register
 *
 ****************************************************************************/

static void ra_sci_spi_putreg8(struct ra_sci_spi_priv_s *priv,
                               uint8_t offset, uint8_t value)
{
  putreg8(value, priv->config->base + offset);
}

/****************************************************************************
 * Name: ra_sci_spi_getreg8
 *
 * Description:
 *   Read an 8-bit value from an SCI_SPI register
 *
 ****************************************************************************/

static uint8_t ra_sci_spi_getreg8(struct ra_sci_spi_priv_s *priv,
                                  uint8_t offset)
{
  return getreg8(priv->config->base + offset);
}

/****************************************************************************
 * Name: ra_sci_spi_calculate_bitrate
 *
 * Description:
 *   Calculate BRR, CKS, and BGDM values for desired bitrate
 *
 * Input Parameters:
 *   bitrate       - Desired bitrate in Hz
 *   use_scispiclk - true to use SCISPICLK, false for PCLK
 *   brr           - Output: BRR value
 *   cks           - Output: CKS value (0-3)
 *   bgdm          - Output: BGDM value (0 or 1)
 *
 * Returned Value:
 *   OK on success, negated errno on failure
 *
 ****************************************************************************/

static int ra_sci_spi_calculate_bitrate(uint32_t bitrate,
                                        bool use_scispiclk,
                                        uint8_t *brr, uint8_t *cks,
                                        uint8_t *bgdm)
{
  uint32_t source_clock;
  uint32_t divisor;
  uint32_t calculated_bitrate;
  uint8_t  n;
  uint8_t  N;
  int      bgdm_enabled;  /* 0 or 1 for BGDM disabled/enabled */
  uint32_t best_error = UINT32_MAX;
  uint8_t  best_brr = 0;
  uint8_t  best_cks = 0;
  uint8_t  best_bgdm = 0;

  /* Get source clock frequency (MV#4 fix) */
  if (use_scispiclk)
    {
      /* Use SCISPICLK source based on Kconfig selection
       * CONFIG_RA_SCISPICLK_SOURCE determines: HOCO(0), MOCO(1), LOCO(2),
       * MAIN_OSC(3), PLL1P(5), or DISABLED(15)
       */
      source_clock = ra_get_peripheral_clock(RA_PCLK_SCICLK);
      if (source_clock == 0)
        {
          spierr("SCISPICLK not available or disabled in Kconfig\n");
          return -EINVAL;
        }
    }
  else
    {
      source_clock = ra_get_peripheral_clock(RA_PCLK_PCLKA);
    }

  /* Try all combinations of N (BRR), n (CKS), and BGDM to find the best */
  for (n = 0; n <= R_SCI_SPI_CLK_MAX_n; n++)
    {
      for (bgdm_enabled = 0; bgdm_enabled < 2; bgdm_enabled++)
        {
          /* Calculate divisor: bitrate = source_clock / (divisor * (N + 1)) */
          /* divisor = 2 * 2^(2n-1) or 2^(2n) depending on BGDM */
          if (bgdm_enabled)
            {
              divisor = (1 << (2 * n));
            }
          else
            {
              if (n == 0)
                {
                  divisor = 1;
                }
              else
                {
                  divisor = 2 * (1 << (2 * n - 1));
                }
            }

          /* Calculate required N (BRR value) */
          N = (source_clock / (divisor * bitrate)) - 1;

          if (N > R_SCI_SPI_CLK_MAX_N)
            {
              continue;
            }

          /* Calculate actual bitrate with this N */
          calculated_bitrate = source_clock / (divisor * (N + 1));

          /* Calculate error */
          uint32_t error = (calculated_bitrate > bitrate) ?
                           (calculated_bitrate - bitrate) :
                           (bitrate - calculated_bitrate);

          /* Keep track of best match */
          if (error < best_error)
            {
              best_error = error;
              best_brr = N;
              best_cks = n;
              best_bgdm = bgdm_enabled ? 1 : 0;

              /* If exact match, we're done */
              if (error == 0)
                {
                  goto found;
                }
            }
        }
    }

found:
  *brr = best_brr;
  *cks = best_cks;
  *bgdm = best_bgdm;

  return OK;
}

/****************************************************************************
 * Name: ra_sci_spi_hw_configure
 *
 * Description:
 *   Configure SCI_SPI hardware registers based on current settings
 *
 ****************************************************************************/

static void ra_sci_spi_hw_configure(struct ra_sci_spi_priv_s *priv)
{
  uint32_t ccr0;
  uint32_t ccr1;
  uint32_t ccr2;
  uint32_t ccr3;
  uint32_t fcr;
  uint8_t brr;
  uint8_t cks;
  uint8_t bgdm;

  /* Disable SCI before configuration */
  ra_sci_spi_disable(priv);

  /* Clear any pending flags */
  ra_sci_spi_putreg32(priv, R_SCI_B_CFCLR_OFFSET, 0xFFFFFFFF);
  ra_sci_spi_putreg32(priv, R_SCI_B_FFCLR_OFFSET, 0xFFFFFFFF);

  /* Configure CCR0: Disable receive and transmit for now */
  ccr0 = 0;
  ra_sci_spi_putreg32(priv, R_SCI_B_CCR0_OFFSET, ccr0);

  /* Configure CCR1: Disable all interrupts initially */
  ccr1 = 0;
  ra_sci_spi_putreg32(priv, R_SCI_B_CCR1_OFFSET, ccr1);

  /* Configure CCR2: Clock settings and baud rate */
  ra_sci_spi_calculate_bitrate(priv->frequency, false,
                               &brr, &cks, &bgdm);

  ccr2 = (brr << R_SCI_B_CCR2_BRR_SHIFT) |
         (cks << R_SCI_B_CCR2_CKS_SHIFT);

  if (bgdm)
    {
      ccr2 |= R_SCI_B_CCR2_BGDM;
    }

  ra_sci_spi_putreg32(priv, R_SCI_B_CCR2_OFFSET, ccr2);

  /* Configure CCR3: Simple SPI mode, data format */
  ccr3 = R_SCI_B_CCR3_MOD_011;  /* Simple SPI mode */

  /* Set 8-bit data length */
  ccr3 |= R_SCI_B_CCR3_CHR_10;

  /* Set clock phase and polarity based on mode */
  switch (priv->mode)
    {
      case SPIDEV_MODE0:  /* CPOL=0, CPHA=0 */
        /* Default values */
        break;

      case SPIDEV_MODE1:  /* CPOL=0, CPHA=1 */
        ccr3 |= R_SCI_B_CCR3_CPHA;
        break;

      case SPIDEV_MODE2:  /* CPOL=1, CPHA=0 */
        ccr3 |= R_SCI_B_CCR3_CPOL;
        break;

      case SPIDEV_MODE3:  /* CPOL=1, CPHA=1 */
        ccr3 |= R_SCI_B_CCR3_CPHA | R_SCI_B_CCR3_CPOL;
        break;

      case SPIDEV_MODETI:  /* TI mode not supported */
      default:
        break;
    }

  /* Set bit order */
  if (priv->lsbfirst)
    {
      ccr3 |= R_SCI_B_CCR3_LSBF;
    }

  /* Enable internal clock output on SCK pin for master mode */
  ccr3 |= R_SCI_B_CCR3_CKE_01;

  ra_sci_spi_putreg32(priv, R_SCI_B_CCR3_OFFSET, ccr3);

  /* Configure CCR4: Default values */
  ra_sci_spi_putreg32(priv, R_SCI_B_CCR4_OFFSET, 0);

  /* Configure FIFO Control Register */
  fcr = 0;

  /* Reset FIFOs to clear any stale data (MV#3 fix) */
  fcr |= R_SCI_B_FCR_TFRST | R_SCI_B_FCR_RFRST;
  ra_sci_spi_putreg32(priv, R_SCI_B_FCR_OFFSET, fcr);

  /* Wait for FIFO reset to complete */
  up_udelay(1);

  /* Configure FIFO triggers - will be adjusted per transfer (MV#9 fix)
   * Default to minimal triggers for initialization
   */
  fcr = 0;
  fcr |= (1 << R_SCI_B_FCR_TTRG_SHIFT);  /* TX trigger = 1 */
  fcr |= (1 << R_SCI_B_FCR_RTRG_SHIFT);  /* RX trigger = 1 */
  ra_sci_spi_putreg32(priv, R_SCI_B_FCR_OFFSET, fcr);
}

/****************************************************************************
 * Name: ra_sci_spi_hw_initialize
 *
 * Description:
 *   Initialize SCI_SPI hardware
 *
 ****************************************************************************/

static void ra_sci_spi_hw_initialize(struct ra_sci_spi_priv_s *priv)
{
  /* Enable module stop for SCI channel */
  ra_mstp_start(priv->config->mstp);

  /* Configure hardware with initial settings */
  ra_sci_spi_hw_configure(priv);
}

/****************************************************************************
 * Name: ra_sci_spi_writeword
 *
 * Description:
 *   Write a byte to the SCI_SPI data register
 *
 ****************************************************************************/

static void ra_sci_spi_writeword(struct ra_sci_spi_priv_s *priv,
                                 uint8_t data)
{
  ra_sci_spi_putreg8(priv, R_SCI_B_TDR_BY_OFFSET, data);
}

/****************************************************************************
 * Name: ra_sci_spi_readword
 *
 * Description:
 *   Read a byte from the SCI_SPI data register
 *
 ****************************************************************************/

static uint8_t ra_sci_spi_readword(struct ra_sci_spi_priv_s *priv)
{
  return ra_sci_spi_getreg8(priv, R_SCI_B_RDR_BY_OFFSET);
}

/****************************************************************************
 * Name: ra_sci_spi_configure_fifo
 *
 * Description:
 *   Configure FIFO trigger levels based on transfer size (MV#9)
 *
 ****************************************************************************/

static void ra_sci_spi_configure_fifo(struct ra_sci_spi_priv_s *priv,
                                      size_t nwords)
{
  uint32_t fcr;
  uint8_t tx_trigger;
  uint8_t rx_trigger;

  /* Adaptive FIFO trigger levels to reduce interrupt overhead:
   * - Small transfers (< 4 bytes): trigger = 1 (immediate response)
   * - Medium transfers (4-15 bytes): trigger = 4 (balanced)
   * - Large transfers (>= 16 bytes): trigger = 8 (batch processing)
   */
  if (nwords < 4)
    {
      tx_trigger = 1;
      rx_trigger = 1;
    }
  else if (nwords < 16)
    {
      tx_trigger = 4;
      rx_trigger = 4;
    }
  else
    {
      tx_trigger = 8;
      rx_trigger = 8;
    }

  fcr = ra_sci_spi_getreg32(priv, R_SCI_B_FCR_OFFSET);
  fcr &= ~(R_SCI_B_FCR_TTRG_MASK | R_SCI_B_FCR_RTRG_MASK);
  fcr |= (tx_trigger << R_SCI_B_FCR_TTRG_SHIFT);
  fcr |= (rx_trigger << R_SCI_B_FCR_RTRG_SHIFT);
  ra_sci_spi_putreg32(priv, R_SCI_B_FCR_OFFSET, fcr);
}

/****************************************************************************
 * Name: ra_sci_spi_enable
 *
 * Description:
 *   Enable SCI_SPI transmitter and receiver
 *
 ****************************************************************************/

static void ra_sci_spi_enable(struct ra_sci_spi_priv_s *priv)
{
  uint32_t ccr0;

  /* MV#8 FIX: Enable interrupts BEFORE RE/TE to prevent spurious interrupts
   * Per FSP pattern: interrupts should be ready before enabling transceiver
   */
  ccr0 = ra_sci_spi_getreg32(priv, R_SCI_B_CCR0_OFFSET);
  ccr0 |= R_SCI_B_CCR0_RIE | R_SCI_B_CCR0_TIE | R_SCI_B_CCR0_TEIE;
  ra_sci_spi_putreg32(priv, R_SCI_B_CCR0_OFFSET, ccr0);

  /* Now enable receive and transmit */
  ccr0 = ra_sci_spi_getreg32(priv, R_SCI_B_CCR0_OFFSET);
  ccr0 |= R_SCI_B_CCR0_RE | R_SCI_B_CCR0_TE;
  ra_sci_spi_putreg32(priv, R_SCI_B_CCR0_OFFSET, ccr0);
}

/****************************************************************************
 * Name: ra_sci_spi_disable
 *
 * Description:
 *   Disable SCI_SPI transmitter and receiver
 *
 ****************************************************************************/

static void ra_sci_spi_disable(struct ra_sci_spi_priv_s *priv)
{
  uint32_t ccr0;

  /* Disable interrupts */
  ccr0 = ra_sci_spi_getreg32(priv, R_SCI_B_CCR0_OFFSET);
  ccr0 &= ~(R_SCI_B_CCR0_RIE | R_SCI_B_CCR0_TIE | R_SCI_B_CCR0_TEIE);
  ra_sci_spi_putreg32(priv, R_SCI_B_CCR0_OFFSET, ccr0);

  /* Disable receive and transmit */
  ccr0 = ra_sci_spi_getreg32(priv, R_SCI_B_CCR0_OFFSET);
  ccr0 &= ~(R_SCI_B_CCR0_RE | R_SCI_B_CCR0_TE);
  ra_sci_spi_putreg32(priv, R_SCI_B_CCR0_OFFSET, ccr0);
}

#ifdef CONFIG_RA_DTC
/****************************************************************************
 * Name: ra_sci_spi_dtc_setup
 *
 * Description:
 *   Setup DTC for SCI_SPI transfers
 *
 ****************************************************************************/

static int ra_sci_spi_dtc_setup(struct ra_sci_spi_priv_s *priv)
{
  ra_dtc_config_t dtc_config;
  int ret;

  /* Initialize DTC module if not already done */
  if (!g_dtc_initialized)
    {
      ret = ra_dtc_initialize();
      if (ret < 0)
        {
          spierr("DTC initialization failed: %d\n", ret);
          return ret;
        }
      g_dtc_initialized = true;
    }

  /* Configure TX DTC */
  memset(&dtc_config, 0, sizeof(ra_dtc_config_t));
  dtc_config.mode = RA_DTC_MODE_NORMAL;
  dtc_config.size = RA_DTC_SIZE_BYTE;
  dtc_config.src_addr_mode = RA_DTC_ADDR_INCR;
  dtc_config.dest_addr_mode = RA_DTC_ADDR_FIXED;
  dtc_config.src_addr = 0;  /* Will be set per transfer */
  dtc_config.dest_addr = priv->config->base + R_SCI_B_TDR_BY_OFFSET;
  dtc_config.transfer_count = 0;  /* Will be set per transfer */
  dtc_config.elc_src = priv->config->txi_elc;
  dtc_config.irq_src = priv->txi_irq;

  ret = ra_dtc_open(&priv->dtc_tx_handle, &dtc_config);
  if (ret < 0)
    {
      spierr("TX DTC open failed: %d\n", ret);
      return ret;
    }

  /* Configure RX DTC */
  memset(&dtc_config, 0, sizeof(ra_dtc_config_t));
  dtc_config.mode = RA_DTC_MODE_NORMAL;
  dtc_config.size = RA_DTC_SIZE_BYTE;
  dtc_config.src_addr_mode = RA_DTC_ADDR_FIXED;
  dtc_config.dest_addr_mode = RA_DTC_ADDR_INCR;
  dtc_config.src_addr = priv->config->base + R_SCI_B_RDR_BY_OFFSET;
  dtc_config.dest_addr = 0;  /* Will be set per transfer */
  dtc_config.transfer_count = 0;  /* Will be set per transfer */
  dtc_config.elc_src = priv->config->rxi_elc;
  dtc_config.irq_src = priv->rxi_irq;

  ret = ra_dtc_open(&priv->dtc_rx_handle, &dtc_config);
  if (ret < 0)
    {
      spierr("RX DTC open failed: %d\n", ret);
      ra_dtc_close(priv->dtc_tx_handle);
      return ret;
    }

  spiinfo("DTC setup complete for SCI%d\n", priv->config->channel);
  return OK;
}

/****************************************************************************
 * Name: ra_sci_spi_dtc_configure_transfer
 *
 * Description:
 *   Configure DTC for a specific transfer
 *
 ****************************************************************************/

static int ra_sci_spi_dtc_configure_transfer(struct ra_sci_spi_priv_s *priv,
                                             const void *txbuffer,
                                             void *rxbuffer,
                                             size_t nwords)
{
  uint32_t tx_src = txbuffer ? (uint32_t)txbuffer : 0;
  uint32_t rx_dest = rxbuffer ? (uint32_t)rxbuffer : 0;
  int ret;

  /* Configure TX DTC */
  if (txbuffer)
    {
      ret = ra_dtc_reset(priv->dtc_tx_handle, tx_src,
                        priv->config->base + R_SCI_B_TDR_BY_OFFSET,
                        nwords);
      if (ret < 0)
        {
          spierr("TX DTC reset failed: %d\n", ret);
          return ret;
        }
    }

  /* Configure RX DTC */
  if (rxbuffer)
    {
      ret = ra_dtc_reset(priv->dtc_rx_handle,
                        priv->config->base + R_SCI_B_RDR_BY_OFFSET,
                        rx_dest, nwords);
      if (ret < 0)
        {
          spierr("RX DTC reset failed: %d\n", ret);
          return ret;
        }
    }

  return OK;
}

/****************************************************************************
 * Name: ra_sci_spi_dtc_start
 *
 * Description:
 *   Start DTC transfer
 *
 ****************************************************************************/

static void ra_sci_spi_dtc_start(struct ra_sci_spi_priv_s *priv)
{
  /* Enable DTC for RX (must be enabled first) */
  if (priv->rxbuffer)
    {
      ra_dtc_enable(priv->dtc_rx_handle);
    }

  /* Enable DTC for TX */
  if (priv->txbuffer)
    {
      ra_dtc_enable(priv->dtc_tx_handle);
    }
}

/****************************************************************************
 * Name: ra_sci_spi_dtc_stop
 *
 * Description:
 *   Stop DTC transfer
 *
 ****************************************************************************/

static void ra_sci_spi_dtc_stop(struct ra_sci_spi_priv_s *priv)
{
  if (priv->dtc_tx_handle)
    {
      ra_dtc_disable(priv->dtc_tx_handle);
    }

  if (priv->dtc_rx_handle)
    {
      ra_dtc_disable(priv->dtc_rx_handle);
    }
}
#endif /* CONFIG_RA_DTC */

#ifdef CONFIG_RA_DMAC
/****************************************************************************
 * Name: ra_sci_spi_dma_tx_callback
 *
 * Description:
 *   DMAC TX completion callback
 *
 ****************************************************************************/

static void ra_sci_spi_dma_tx_callback(void *handle, int event, void *arg)
{
  struct ra_sci_spi_priv_s *priv = (struct ra_sci_spi_priv_s *)arg;

  if (event == RA_DMAC_EVENT_COMPLETE)
    {
      priv->dma_tx_done = true;
      spiinfo("TX DMA complete\n");
    }
  else if (event == RA_DMAC_EVENT_ERROR)
    {
      priv->error = true;
      priv->dma_tx_done = true;
      spierr("TX DMA error\n");
    }

  /* Wake up waiting thread if both TX and RX complete */
  if (priv->dma_tx_done && priv->dma_rx_done)
    {
      nxsem_post(&priv->sem_isr);
    }
}

/****************************************************************************
 * Name: ra_sci_spi_dma_rx_callback
 *
 * Description:
 *   DMAC RX completion callback
 *
 ****************************************************************************/

static void ra_sci_spi_dma_rx_callback(void *handle, int event, void *arg)
{
  struct ra_sci_spi_priv_s *priv = (struct ra_sci_spi_priv_s *)arg;

  if (event == RA_DMAC_EVENT_COMPLETE)
    {
      priv->dma_rx_done = true;
      spiinfo("RX DMA complete\n");
    }
  else if (event == RA_DMAC_EVENT_ERROR)
    {
      priv->error = true;
      priv->dma_rx_done = true;
      spierr("RX DMA error\n");
    }

  /* Wake up waiting thread if both TX and RX complete */
  if (priv->dma_tx_done && priv->dma_rx_done)
    {
      nxsem_post(&priv->sem_isr);
    }
}

/****************************************************************************
 * Name: ra_sci_spi_dma_setup
 *
 * Description:
 *   Setup DMAC for SCI_SPI transfers
 *
 ****************************************************************************/

static int ra_sci_spi_dma_setup(struct ra_sci_spi_priv_s *priv)
{
  ra_dmac_config_t dma_config;
  int ret;

  /* Initialize DMAC module */
  ret = ra_dmac_initialize();
  if (ret < 0 && ret != -EBUSY)
    {
      spierr("DMAC initialization failed: %d\n", ret);
      return ret;
    }

  /* Configure TX DMAC */
  memset(&dma_config, 0, sizeof(ra_dmac_config_t));
  dma_config.mode = RA_DMAC_MODE_NORMAL;
  dma_config.size = RA_DMAC_SIZE_8BIT;
  dma_config.src_addr_mode = RA_DMAC_ADDR_INCR;
  dma_config.dest_addr_mode = RA_DMAC_ADDR_FIXED;
  dma_config.trigger = RA_DMAC_TRIGGER_HW;
  dma_config.src_addr = 0;  /* Will be set per transfer */
  dma_config.dest_addr = priv->config->base + R_SCI_B_TDR_BY_OFFSET;
  dma_config.transfer_count = 0;  /* Will be set per transfer */
  dma_config.elc_src = priv->config->txi_elc;
  dma_config.callback = ra_sci_spi_dma_tx_callback;
  dma_config.user_data = priv;

  ret = ra_dmac_open(&priv->dma_tx_handle, &dma_config);
  if (ret < 0)
    {
      spierr("TX DMAC open failed: %d\n", ret);
      return ret;
    }

  /* Configure RX DMAC */
  memset(&dma_config, 0, sizeof(ra_dmac_config_t));
  dma_config.mode = RA_DMAC_MODE_NORMAL;
  dma_config.size = RA_DMAC_SIZE_8BIT;
  dma_config.src_addr_mode = RA_DMAC_ADDR_FIXED;
  dma_config.dest_addr_mode = RA_DMAC_ADDR_INCR;
  dma_config.trigger = RA_DMAC_TRIGGER_HW;
  dma_config.src_addr = priv->config->base + R_SCI_B_RDR_BY_OFFSET;
  dma_config.dest_addr = 0;  /* Will be set per transfer */
  dma_config.transfer_count = 0;  /* Will be set per transfer */
  dma_config.elc_src = priv->config->rxi_elc;
  dma_config.callback = ra_sci_spi_dma_rx_callback;
  dma_config.user_data = priv;

  ret = ra_dmac_open(&priv->dma_rx_handle, &dma_config);
  if (ret < 0)
    {
      spierr("RX DMAC open failed: %d\n", ret);
      ra_dmac_close(priv->dma_tx_handle);
      return ret;
    }

  spiinfo("DMAC setup complete for SCI%d\n", priv->config->channel);
  return OK;
}

/****************************************************************************
 * Name: ra_sci_spi_dma_transfer
 *
 * Description:
 *   Perform DMA transfer
 *
 ****************************************************************************/

static int ra_sci_spi_dma_transfer(struct ra_sci_spi_priv_s *priv,
                                   const void *txbuffer,
                                   void *rxbuffer,
                                   size_t nwords)
{
  uint32_t tx_src = txbuffer ? (uint32_t)txbuffer : 0;
  uint32_t rx_dest = rxbuffer ? (uint32_t)rxbuffer : 0;
  int ret;

  /* Reset completion flags */
  priv->dma_tx_done = false;
  priv->dma_rx_done = false;

  /* Configure TX DMAC */
  if (txbuffer)
    {
      ret = ra_dmac_reset(priv->dma_tx_handle, tx_src,
                         priv->config->base + R_SCI_B_TDR_BY_OFFSET,
                         nwords);
      if (ret < 0)
        {
          spierr("TX DMAC reset failed: %d\n", ret);
          return ret;
        }

      ret = ra_dmac_enable(priv->dma_tx_handle);
      if (ret < 0)
        {
          spierr("TX DMAC enable failed: %d\n", ret);
          return ret;
        }
    }
  else
    {
      /* No TX buffer, mark TX as done */
      priv->dma_tx_done = true;
    }

  /* Configure RX DMAC */
  if (rxbuffer)
    {
      ret = ra_dmac_reset(priv->dma_rx_handle,
                         priv->config->base + R_SCI_B_RDR_BY_OFFSET,
                         rx_dest, nwords);
      if (ret < 0)
        {
          spierr("RX DMAC reset failed: %d\n", ret);
          if (txbuffer)
            {
              ra_dmac_disable(priv->dma_tx_handle);
            }
          return ret;
        }

      ret = ra_dmac_enable(priv->dma_rx_handle);
      if (ret < 0)
        {
          spierr("RX DMAC enable failed: %d\n", ret);
          if (txbuffer)
            {
              ra_dmac_disable(priv->dma_tx_handle);
            }
          return ret;
        }
    }
  else
    {
      /* No RX buffer, mark RX as done */
      priv->dma_rx_done = true;
    }

  return OK;
}

/****************************************************************************
 * Name: ra_sci_spi_dma_stop
 *
 * Description:
 *   Stop DMA transfer
 *
 ****************************************************************************/

static void ra_sci_spi_dma_stop(struct ra_sci_spi_priv_s *priv)
{
  if (priv->dma_tx_handle)
    {
      ra_dmac_disable(priv->dma_tx_handle);
    }

  if (priv->dma_rx_handle)
    {
      ra_dmac_disable(priv->dma_rx_handle);
    }
}
#endif /* CONFIG_RA_DMAC */

/****************************************************************************
 * Name: ra_sci_spi_rxi_interrupt
 *
 * Description:
 *   SCI_SPI receive interrupt handler
 *
 ****************************************************************************/

static int ra_sci_spi_rxi_interrupt(int irq, void *context, void *arg)
{
  struct ra_sci_spi_priv_s *priv = (struct ra_sci_spi_priv_s *)arg;
  uint32_t csr;
  uint8_t data;

  DEBUGASSERT(priv != NULL);

  /* Check for receive data ready */
  csr = ra_sci_spi_getreg32(priv, R_SCI_B_CSR_OFFSET);

  if (csr & R_SCI_B_CSR_RDRF)
    {
      /* Read received data */
      data = ra_sci_spi_readword(priv);

      /* Store in receive buffer if provided */
      if (priv->rxbuffer != NULL && priv->rxidx < priv->nrxwords)
        {
          priv->rxbuffer[priv->rxidx] = data;
        }

      priv->rxidx++;

      /* Clear RDRF flag */
      ra_sci_spi_putreg32(priv, R_SCI_B_CFCLR_OFFSET, R_SCI_B_CSR_RDRF);

      /* MV#5 FIX: Check if all data received and signal completion
       * This provides early completion detection without waiting for TEI
       */
      if (priv->rxidx >= priv->nrxwords)
        {
          /* All data received - disable RX interrupt */
          uint32_t ccr0 = ra_sci_spi_getreg32(priv, R_SCI_B_CCR0_OFFSET);
          ccr0 &= ~R_SCI_B_CCR0_RIE;
          ra_sci_spi_putreg32(priv, R_SCI_B_CCR0_OFFSET, ccr0);
        }
    }

  return OK;
}

/****************************************************************************
 * Name: ra_sci_spi_txi_interrupt
 *
 * Description:
 *   SCI_SPI transmit interrupt handler
 *
 ****************************************************************************/

static int ra_sci_spi_txi_interrupt(int irq, void *context, void *arg)
{
  struct ra_sci_spi_priv_s *priv = (struct ra_sci_spi_priv_s *)arg;
  uint32_t csr;
  uint8_t data;

  DEBUGASSERT(priv != NULL);

  /* Check for transmit data empty */
  csr = ra_sci_spi_getreg32(priv, R_SCI_B_CSR_OFFSET);

  if (csr & R_SCI_B_CSR_TDRE)
    {
      if (priv->txidx < priv->ntxwords)
        {
          /* Get next byte to transmit */
          if (priv->txbuffer != NULL)
            {
              data = priv->txbuffer[priv->txidx];
            }
          else
            {
              data = 0xFF;  /* Dummy data for read-only transfer */
            }

          /* Write data to transmit register */
          ra_sci_spi_writeword(priv, data);
          priv->txidx++;

          /* Clear TDRE flag */
          ra_sci_spi_putreg32(priv, R_SCI_B_CFCLR_OFFSET, R_SCI_B_CSR_TDRE);
        }
      else
        {
          /* MV#7 FIX: All data queued - disable TXI interrupt
           * Let TEI interrupt handle final transfer completion
           */
          uint32_t ccr0 = ra_sci_spi_getreg32(priv, R_SCI_B_CCR0_OFFSET);
          ccr0 &= ~R_SCI_B_CCR0_TIE;
          ra_sci_spi_putreg32(priv, R_SCI_B_CCR0_OFFSET, ccr0);
        }
    }

  return OK;
}

/****************************************************************************
 * Name: ra_sci_spi_tei_interrupt
 *
 * Description:
 *   SCI_SPI transfer end interrupt handler
 *
 ****************************************************************************/

static int ra_sci_spi_tei_interrupt(int irq, void *context, void *arg)
{
  struct ra_sci_spi_priv_s *priv = (struct ra_sci_spi_priv_s *)arg;

  DEBUGASSERT(priv != NULL);

  /* Transfer complete - wake up waiting thread */
  nxsem_post(&priv->sem_isr);

  return OK;
}

/****************************************************************************
 * Name: ra_sci_spi_eri_interrupt
 *
 * Description:
 *   SCI_SPI error interrupt handler
 *
 ****************************************************************************/

static int ra_sci_spi_eri_interrupt(int irq, void *context, void *arg)
{
  struct ra_sci_spi_priv_s *priv = (struct ra_sci_spi_priv_s *)arg;
  uint32_t csr;

  DEBUGASSERT(priv != NULL);

  /* Read and clear error flags */
  csr = ra_sci_spi_getreg32(priv, R_SCI_B_CSR_OFFSET);

  spierr("SCI_SPI error: CSR=0x%08lx\n", (unsigned long)csr);

  /* Set error flag */
  priv->error = true;

  /* Clear error flags */
  ra_sci_spi_putreg32(priv, R_SCI_B_CFCLR_OFFSET,
                     R_SCI_B_CSR_ORER | R_SCI_B_CSR_FER |
                     R_SCI_B_CSR_PER);

  /* Wake up waiting thread */
  nxsem_post(&priv->sem_isr);

  return OK;
}

/****************************************************************************
 * Name: ra_sci_spi_lock
 *
 * Description:
 *   Lock or unlock the SPI device
 *
 ****************************************************************************/

static int ra_sci_spi_lock(struct spi_dev_s *dev, bool lock)
{
  struct ra_sci_spi_priv_s *priv = (struct ra_sci_spi_priv_s *)dev;
  int ret;

  if (lock)
    {
      ret = nxmutex_lock(&priv->lock);
    }
  else
    {
      ret = nxmutex_unlock(&priv->lock);
    }

  return ret;
}

/****************************************************************************
 * Name: ra_sci_spi_setfrequency
 *
 * Description:
 *   Set the SPI frequency
 *
 ****************************************************************************/

static uint32_t ra_sci_spi_setfrequency(struct spi_dev_s *dev,
                                        uint32_t frequency)
{
  struct ra_sci_spi_priv_s *priv = (struct ra_sci_spi_priv_s *)dev;
  uint8_t brr;
  uint8_t cks;
  uint8_t bgdm;
  uint32_t ccr2;
  uint32_t source_clock;
  uint32_t divisor;

  if (frequency == priv->frequency)
    {
      return priv->actual_frequency;
    }

  /* Limit frequency to maximum */
  if (frequency > R_SCI_SPI_MAX_FREQUENCY)
    {
      frequency = R_SCI_SPI_MAX_FREQUENCY;
    }

  priv->frequency = frequency;

  /* Calculate baud rate settings */
  ra_sci_spi_calculate_bitrate(frequency, false, &brr, &cks, &bgdm);

  /* Update CCR2 register */
  ccr2 = ra_sci_spi_getreg32(priv, R_SCI_B_CCR2_OFFSET);
  ccr2 &= ~(R_SCI_B_CCR2_BRR_MASK | R_SCI_B_CCR2_CKS_MASK |
            R_SCI_B_CCR2_BGDM);
  ccr2 |= (brr << R_SCI_B_CCR2_BRR_SHIFT) |
          (cks << R_SCI_B_CCR2_CKS_SHIFT);

  if (bgdm)
    {
      ccr2 |= R_SCI_B_CCR2_BGDM;
    }

  ra_sci_spi_putreg32(priv, R_SCI_B_CCR2_OFFSET, ccr2);

  /* Calculate actual frequency */
  source_clock = ra_get_peripheral_clock(RA_PCLK_PCLKA);

  if (bgdm)
    {
      divisor = (1 << (2 * cks));
    }
  else
    {
      if (cks == 0)
        {
          divisor = 1;
        }
      else
        {
          divisor = 2 * (1 << (2 * cks - 1));
        }
    }

  priv->actual_frequency = source_clock / (divisor * (brr + 1));

  spiinfo("Requested: %ld Hz, Actual: %ld Hz\n",
          frequency, priv->actual_frequency);

  return priv->actual_frequency;
}

/****************************************************************************
 * Name: ra_sci_spi_setmode
 *
 * Description:
 *   Set the SPI mode
 *
 ****************************************************************************/

static void ra_sci_spi_setmode(struct spi_dev_s *dev,
                               enum spi_mode_e mode)
{
  struct ra_sci_spi_priv_s *priv = (struct ra_sci_spi_priv_s *)dev;
  uint32_t ccr3;

  if (mode == priv->mode)
    {
      return;
    }

  priv->mode = mode;

  /* Update CCR3 register for clock phase and polarity */
  ccr3 = ra_sci_spi_getreg32(priv, R_SCI_B_CCR3_OFFSET);
  ccr3 &= ~(R_SCI_B_CCR3_CPHA | R_SCI_B_CCR3_CPOL);

  switch (mode)
    {
      case SPIDEV_MODE0:  /* CPOL=0, CPHA=0 */
        /* Default values */
        break;

      case SPIDEV_MODE1:  /* CPOL=0, CPHA=1 */
        ccr3 |= R_SCI_B_CCR3_CPHA;
        break;

      case SPIDEV_MODE2:  /* CPOL=1, CPHA=0 */
        ccr3 |= R_SCI_B_CCR3_CPOL;
        break;

      case SPIDEV_MODE3:  /* CPOL=1, CPHA=1 */
        ccr3 |= R_SCI_B_CCR3_CPHA | R_SCI_B_CCR3_CPOL;
        break;

      case SPIDEV_MODETI:  /* TI mode not supported */
      default:
        break;
    }

  ra_sci_spi_putreg32(priv, R_SCI_B_CCR3_OFFSET, ccr3);

  spiinfo("mode=%d\n", mode);
}

/****************************************************************************
 * Name: ra_sci_spi_setbits
 *
 * Description:
 *   Set the number of bits per word (SCI_SPI only supports 8 bits)
 *
 ****************************************************************************/

static void ra_sci_spi_setbits(struct spi_dev_s *dev, int nbits)
{
  struct ra_sci_spi_priv_s *priv = (struct ra_sci_spi_priv_s *)dev;
  uint32_t ccr3;

  /* SCI-B SPI supports 7, 8, and 9-bit transfers */
  if (nbits != 7 && nbits != 8 && nbits != 9)
    {
      spierr("Only 7, 8, and 9-bit transfers supported, requested: %d\n", nbits);
      return;
    }

  priv->nbits = nbits;

  /* Update CCR3 CHR field for data length */
  ccr3 = ra_sci_spi_getreg32(priv, R_SCI_B_CCR3_OFFSET);
  ccr3 &= ~R_SCI_B_CCR3_CHR_MASK;

  switch (nbits)
    {
      case 7:
        ccr3 |= R_SCI_B_CCR3_CHR_11;  /* 7-bit */
        break;
      case 8:
        ccr3 |= R_SCI_B_CCR3_CHR_10;  /* 8-bit */
        break;
      case 9:
        ccr3 |= R_SCI_B_CCR3_CHR_00;  /* 9-bit */
        break;
    }

  ra_sci_spi_putreg32(priv, R_SCI_B_CCR3_OFFSET, ccr3);

  spiinfo("nbits=%d\n", nbits);
}

#ifdef CONFIG_SPI_HWFEATURES
/****************************************************************************
 * Name: ra_sci_spi_hwfeatures
 *
 * Description:
 *   Set hardware-specific feature flags
 *
 ****************************************************************************/

static int ra_sci_spi_hwfeatures(struct spi_dev_s *dev,
                                 spi_hwfeatures_t features)
{
  /* No special hardware features supported yet */
  return (features == 0) ? OK : -ENOSYS;
}
#endif

/****************************************************************************
 * Name: ra_sci_spi_send
 *
 * Description:
 *   Exchange one word on SPI
 *
 ****************************************************************************/

static uint32_t ra_sci_spi_send(struct spi_dev_s *dev, uint32_t wd)
{
  uint8_t txbyte = (uint8_t)wd;
  uint8_t rxbyte = 0;

  /* Exchange one byte */
  ra_sci_spi_exchange(dev, &txbyte, &rxbyte, 1);

  return (uint32_t)rxbyte;
}

/****************************************************************************
 * Name: ra_sci_spi_exchange
 *
 * Description:
 *   Exchange a block of data on SPI
 *
 ****************************************************************************/

static void ra_sci_spi_exchange(struct spi_dev_s *dev,
                                const void *txbuffer,
                                void *rxbuffer, size_t nwords)
{
  struct ra_sci_spi_priv_s *priv = (struct ra_sci_spi_priv_s *)dev;
  const struct ra_sci_spi_ext_dev_config_s *dev_config;
  uint32_t csr;
  int timeout_ms = R_SCI_SPI_TIMEOUT_MS;
  int ret = OK;
#if defined(CONFIG_RA_DMAC)
  bool use_dma = false;
#endif
#if defined(CONFIG_RA_DTC)
  bool use_dtc = false;
#endif

  /* Setup transfer state */
  priv->txbuffer = (const uint8_t *)txbuffer;
  priv->rxbuffer = (uint8_t *)rxbuffer;
  priv->ntxwords = nwords;
  priv->nrxwords = nwords;
  priv->txidx = 0;
  priv->rxidx = 0;
  priv->error = false;

  /* Check device configuration for DMA/DTC preference */
  dev_config = ra_sci_spi_get_dev_config(dev, priv->devid);

  /* Determine transfer method based on device config and transfer size
   * DMA is preferred for large transfers, DTC for medium, interrupts for small
   */
#ifdef CONFIG_RA_DMAC
  if (dev_config && dev_config->use_dma && priv->dma_tx_handle && nwords >= 16)
    {
      use_dma = true;
      priv->use_dma = true;
    }
#endif

#ifdef CONFIG_RA_DTC
  if (!use_dma && dev_config && dev_config->use_dtc &&
      priv->dtc_tx_handle && nwords >= 8)
    {
      use_dtc = true;
      priv->use_dtc = true;
    }
#endif

  /* MV#6 FIX: Memory barrier to ensure buffer pointers are visible
   * to interrupt handlers/DMA before enabling transfers
   */
  ARM_DSB();
  ARM_ISB();

  /* Initialize semaphore */
  nxsem_reset(&priv->sem_isr, 0);

  /* Configure FIFO triggers based on transfer size (MV#9) */
  ra_sci_spi_configure_fifo(priv, nwords);

#ifdef CONFIG_RA_DMAC
  /* DMA transfer path */
  if (use_dma)
    {
      spiinfo("Using DMAC for %zu bytes\n", nwords);

      ret = ra_sci_spi_dma_transfer(priv, txbuffer, rxbuffer, nwords);
      if (ret < 0)
        {
          spierr("DMAC transfer setup failed: %d\n", ret);
          use_dma = false;  /* Fall back to interrupt mode */
          priv->use_dma = false;
        }
      else
        {
          /* Enable SCI_SPI for DMA */
          ra_sci_spi_enable(priv);

          /* Wait for DMA completion */
          ret = nxsem_tickwait(&priv->sem_isr, MSEC2TICK(timeout_ms));

          /* Stop DMA and disable SCI_SPI */
          ra_sci_spi_dma_stop(priv);
          ra_sci_spi_disable(priv);

          if (ret < 0)
            {
              spierr("DMAC transfer timeout\n");
              priv->error = true;
            }

          return;
        }
    }
#endif

#ifdef CONFIG_RA_DTC
  /* DTC transfer path */
  if (use_dtc)
    {
      spiinfo("Using DTC for %zu bytes\n", nwords);

      ret = ra_sci_spi_dtc_configure_transfer(priv, txbuffer, rxbuffer, nwords);
      if (ret < 0)
        {
          spierr("DTC transfer setup failed: %d\n", ret);
          use_dtc = false;  /* Fall back to interrupt mode */
          priv->use_dtc = false;
        }
      else
        {
          /* Start DTC */
          ra_sci_spi_dtc_start(priv);

          /* Enable SCI_SPI - DTC will handle data movement */
          ra_sci_spi_enable(priv);

          /* Wait for transfer completion */
          ret = nxsem_tickwait(&priv->sem_isr, MSEC2TICK(timeout_ms));

          /* Stop DTC and disable SCI_SPI */
          ra_sci_spi_dtc_stop(priv);
          ra_sci_spi_disable(priv);

          if (ret < 0)
            {
              spierr("DTC transfer timeout\n");
              priv->error = true;
            }

          return;
        }
    }
#endif

  /* Interrupt-driven transfer (fallback or for small transfers) */
  spiinfo("Using interrupt mode for %zu bytes\n", nwords);

  /* Enable SCI_SPI - TXI interrupt will automatically start the transfer */
  ra_sci_spi_enable(priv);

  /* Wait for transfer completion with timeout */
  ret = nxsem_tickwait(&priv->sem_isr, MSEC2TICK(timeout_ms));

  /* Disable SCI_SPI */
  ra_sci_spi_disable(priv);

  /* Check for timeout */
  if (ret < 0)
    {
      spierr("SCI_SPI transfer timeout: %d\n", ret);
      priv->error = true;
    }

  /* Check for transfer errors */
  if (priv->error)
    {
      csr = ra_sci_spi_getreg32(priv, R_SCI_B_CSR_OFFSET);
      spierr("SCI_SPI transfer failed, CSR=0x%08lx\n", (unsigned long)csr);
    }
}

#ifndef CONFIG_SPI_EXCHANGE
/****************************************************************************
 * Name: ra_sci_spi_sndblock
 *
 * Description:
 *   Send a block of data on SPI
 *
 ****************************************************************************/

static void ra_sci_spi_sndblock(struct spi_dev_s *dev,
                                const void *txbuffer,
                                size_t nwords)
{
  ra_sci_spi_exchange(dev, txbuffer, NULL, nwords);
}

/****************************************************************************
 * Name: ra_sci_spi_recvblock
 *
 * Description:
 *   Receive a block of data from SPI
 *
 ****************************************************************************/

static void ra_sci_spi_recvblock(struct spi_dev_s *dev, void *rxbuffer,
                                 size_t nwords)
{
  ra_sci_spi_exchange(dev, NULL, rxbuffer, nwords);
}
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_sci_spibus_initialize
 *
 * Description:
 *   Initialize the selected SCI_SPI bus
 *
 ****************************************************************************/

struct spi_dev_s *ra_sci_spibus_initialize(int bus)
{
  struct ra_sci_spi_priv_s *priv = NULL;
  irqstate_t flags;

  spiinfo("Initializing SCI_SPI bus %d\n", bus);

  /* Get device instance */
  switch (bus)
    {
#ifdef CONFIG_RA_SCI0_SPI
      case 0:
        priv = &ra_sci0_spi_priv;
        break;
#endif

#ifdef CONFIG_RA_SCI1_SPI
      case 1:
        priv = &ra_sci1_spi_priv;
        break;
#endif

      default:
        return NULL;
    }

  /* Has the device already been initialized? */
  if (priv->initialized)
    {
      /* Yes, return a reference to the device */
      return (struct spi_dev_s *)priv;
    }

  /* Initialize device state */
  flags = enter_critical_section();

  nxmutex_init(&priv->lock);
  nxsem_init(&priv->sem_isr, 0, 0);

  /* Set default configuration */
  priv->frequency = 10000000;  /* 10 MHz default */
  priv->mode = SPIDEV_MODE0;
  priv->nbits = 8;
  priv->lsbfirst = false;

  /* Initialize hardware */
  ra_sci_spi_hw_initialize(priv);

  /* Attach interrupts - store IRQ numbers in priv (FIX CD#4) */
  priv->rxi_irq = ra_icu_attach(priv->config->rxi_elc,
                                ra_sci_spi_rxi_interrupt,
                                priv, true);
  priv->txi_irq = ra_icu_attach(priv->config->txi_elc,
                                ra_sci_spi_txi_interrupt,
                                priv, true);
  priv->tei_irq = ra_icu_attach(priv->config->tei_elc,
                                ra_sci_spi_tei_interrupt,
                                priv, true);
  priv->eri_irq = ra_icu_attach(priv->config->eri_elc,
                                ra_sci_spi_eri_interrupt,
                                priv, true);

#ifdef CONFIG_RA_DTC
  /* Setup DTC if enabled */
  if (ra_sci_spi_dtc_setup(priv) == OK)
    {
      spiinfo("DTC enabled for SCI%d\n", priv->config->channel);
    }
  else
    {
      spiwarn("DTC setup failed for SCI%d, using interrupts only\n",
              priv->config->channel);
    }
#endif

#ifdef CONFIG_RA_DMAC
  /* Setup DMAC if enabled */
  if (ra_sci_spi_dma_setup(priv) == OK)
    {
      spiinfo("DMAC enabled for SCI%d\n", priv->config->channel);
    }
  else
    {
      spiwarn("DMAC setup failed for SCI%d, using interrupts/DTC\n",
              priv->config->channel);
    }
#endif

  /* Mark as initialized */
  priv->initialized = true;

  leave_critical_section(flags);

  spiinfo("SCI_SPI bus %d initialized\n", bus);

  return (struct spi_dev_s *)priv;
}

/****************************************************************************
 * Name: ra_sci_spibus_uninitialize
 *
 * Description:
 *   Uninitialize the selected SCI_SPI bus (cleanup for power management)
 *
 ****************************************************************************/

int ra_sci_spibus_uninitialize(struct spi_dev_s *dev)
{
  struct ra_sci_spi_priv_s *priv = (struct ra_sci_spi_priv_s *)dev;
  irqstate_t flags;

  if (priv == NULL || !priv->initialized)
    {
      return -EINVAL;
    }

  flags = enter_critical_section();

  /* Disable SCI_SPI */
  ra_sci_spi_disable(priv);

  /* Detach interrupts */
  if (priv->rxi_irq >= 0)
    {
      up_disable_irq(priv->rxi_irq);
      irq_detach(priv->rxi_irq);
    }

  if (priv->txi_irq >= 0)
    {
      up_disable_irq(priv->txi_irq);
      irq_detach(priv->txi_irq);
    }

  if (priv->tei_irq >= 0)
    {
      up_disable_irq(priv->tei_irq);
      irq_detach(priv->tei_irq);
    }

  if (priv->eri_irq >= 0)
    {
      up_disable_irq(priv->eri_irq);
      irq_detach(priv->eri_irq);
    }

#ifdef CONFIG_RA_DTC
  /* Close DTC handles */
  if (priv->dtc_tx_handle)
    {
      ra_dtc_close(priv->dtc_tx_handle);
      priv->dtc_tx_handle = NULL;
    }

  if (priv->dtc_rx_handle)
    {
      ra_dtc_close(priv->dtc_rx_handle);
      priv->dtc_rx_handle = NULL;
    }
#endif

#ifdef CONFIG_RA_DMAC
  /* Close DMAC handles */
  if (priv->dma_tx_handle)
    {
      ra_dmac_close(priv->dma_tx_handle);
      priv->dma_tx_handle = NULL;
    }

  if (priv->dma_rx_handle)
    {
      ra_dmac_close(priv->dma_rx_handle);
      priv->dma_rx_handle = NULL;
    }
#endif

  /* Stop module clock to save power */
  ra_mstp_stop(priv->config->mstp);

  /* Clean up synchronization objects */
  nxmutex_destroy(&priv->lock);
  nxsem_destroy(&priv->sem_isr);

  /* Mark as uninitialized */
  priv->initialized = false;

  leave_critical_section(flags);

  spiinfo("SCI_SPI bus %d uninitialized\n", priv->config->channel);

  return OK;
}

/****************************************************************************
 * Name: ra_sci_spi_select (weak function)
 *
 * Description:
 *   Select or deselect the SPI device (implemented by board-specific code)
 *
 ****************************************************************************/

weak_function void ra_sci_spi_select(struct spi_dev_s *dev,
                                     uint32_t devid, bool selected)
{
  /* Default implementation - should be overridden by board-specific code */
  spiwarn("Default ra_sci_spi_select() called - devid=%lu selected=%d\n",
          (unsigned long)devid, selected);
  spiwarn("Board-specific implementation required for chip select!\n");
}

/****************************************************************************
 * Name: ra_sci_spi_status (weak function)
 *
 * Description:
 *   Get SPI device status (implemented by board-specific code)
 *
 ****************************************************************************/

weak_function uint8_t ra_sci_spi_status(struct spi_dev_s *dev,
                                        uint32_t devid)
{
  return 0;
}

#ifdef CONFIG_SPI_CMDDATA
/****************************************************************************
 * Name: ra_sci_spi_cmddata (weak function)
 *
 * Description:
 *   Control CMD/DATA line (implemented by board-specific code)
 *
 ****************************************************************************/

weak_function int ra_sci_spi_cmddata(struct spi_dev_s *dev,
                                     uint32_t devid, bool cmd)
{
  return -ENOSYS;
}
#endif

/****************************************************************************
 * Name: ra_sci_spi_register_callback (weak function)
 *
 * Description:
 *   Register a callback (implemented by board-specific code)
 *
 ****************************************************************************/

weak_function int ra_sci_spi_register_callback(struct spi_dev_s *dev,
                                               sci_spi_callback_t callback,
                                               void *arg)
{
  return -ENOSYS;
}

/****************************************************************************
 * Name: ra_sci_spi_get_dev_config (weak function)
 *
 * Description:
 *   Get device configuration (implemented by board-specific code)
 *
 ****************************************************************************/

weak_function const struct ra_sci_spi_ext_dev_config_s *
ra_sci_spi_get_dev_config(struct spi_dev_s *dev, uint32_t devid)
{
  return NULL;
}

/****************************************************************************
 * Name: ra_sci_spi_setbitorder
 *
 * Description:
 *   Set the SPI bit order
 *
 ****************************************************************************/

void ra_sci_spi_setbitorder(struct spi_dev_s *dev, bool lsbfirst)
{
  struct ra_sci_spi_priv_s *priv = (struct ra_sci_spi_priv_s *)dev;
  uint32_t ccr3;

  if (lsbfirst == priv->lsbfirst)
    {
      return;
    }

  priv->lsbfirst = lsbfirst;

  /* Update CCR3 register */
  ccr3 = ra_sci_spi_getreg32(priv, R_SCI_B_CCR3_OFFSET);

  if (lsbfirst)
    {
      ccr3 |= R_SCI_B_CCR3_LSBF;
    }
  else
    {
      ccr3 &= ~R_SCI_B_CCR3_LSBF;
    }

  ra_sci_spi_putreg32(priv, R_SCI_B_CCR3_OFFSET, ccr3);
}

#endif /* CONFIG_RA_SCI_SPI */
