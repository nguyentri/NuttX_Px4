/****************************************************************************
 * arch/arm/src/rzv/rzv_sci_spi.c
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
#include <arch/rzv/irq.h>

#include "arm_internal.h"
#include "chip.h"
#include "hardware/rzv_memorymap.h"
#include "hardware/rzv2h/rzv_sci_b_spi.h"
#include "barriers.h"

#include "rzv_clock.h"
#include "rzv_icu.h"
#include "rzv_sci_spi.h"

#include <nuttx/cache.h>

#ifdef CONFIG_RZV_SCI_SPI

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SCI_B SPI Maximum frequency */

#define R_SCI_SPI_MAX_FREQUENCY      50000000

/* SCI_B SPI Timeout */

#define R_SCI_SPI_TIMEOUT_MS         1000

/* Clock calculation constants */

#define R_SCI_SPI_CLK_MAX_N          (0xFFU)
#define R_SCI_SPI_CLK_MAX_DIV        (R_SCI_SPI_CLK_MAX_N + 1)

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* SCI_B SPI Device hardware configuration */

struct rzv_sci_spi_config_s
{
  uint32_t base;              /* SCI_B base address */
  uint8_t  channel;           /* SCI_B channel number (0-9) */
  uint32_t rxi_irq;           /* RX interrupt number (will be dynamically assigned) */
  uint32_t txi_irq;           /* TX interrupt number (will be dynamically assigned) */
  uint32_t tei_irq;           /* TE interrupt number (will be dynamically assigned) */
  uint32_t eri_irq;           /* ER interrupt number (will be dynamically assigned) */
  uint32_t rxi_elc;           /* RX ELC event number */
  uint32_t txi_elc;           /* TX ELC event number */
  uint32_t tei_elc;           /* TE ELC event number */
  uint32_t eri_elc;           /* ER ELC event number */
};

/* SCI_B SPI Device Private Data */

struct rzv_sci_spi_priv_s
{
  struct spi_dev_s             spi_dev;       /* External SPI interface */
  const struct rzv_sci_spi_config_s *config;  /* Hardware configuration */
  mutex_t                      lock;          /* Device mutex */
  sem_t                        sem_isr;       /* ISR wait semaphore */

  uint32_t                     frequency;     /* Current frequency */
  uint32_t                     actual;        /* Actual frequency */
  enum spi_mode_e              mode;          /* Current SPI mode */
  uint8_t                      nbits;         /* Data width (8 bits) */
  bool                         lsbfirst;      /* LSB first */

  /* Transfer state */

  const uint8_t               *txbuffer;      /* TX buffer pointer */
  uint8_t                     *rxbuffer;      /* RX buffer pointer */
  size_t                       ntxwords;      /* TX words remaining */
  size_t                       nrxwords;      /* RX words remaining */
  bool                         error;         /* Transfer error flag */

  /* Interrupt request numbers (dynamically assigned) */

  int                          rxi_irq;       /* RX interrupt */
  int                          txi_irq;       /* TX interrupt */
  int                          tei_irq;       /* TE interrupt */
  int                          eri_irq;       /* ER interrupt */

#ifdef CONFIG_PM
  struct pm_callback_s         pmcb;          /* PM callbacks */
#endif
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Low-level helpers */

static void rzv_sci_spi_putreg32(struct rzv_sci_spi_priv_s *priv,
                                 uint8_t offset, uint32_t value);
static uint32_t rzv_sci_spi_getreg32(struct rzv_sci_spi_priv_s *priv,
                                     uint8_t offset);
static void rzv_sci_spi_putreg8(struct rzv_sci_spi_priv_s *priv,
                                uint8_t offset, uint8_t value);
static uint8_t rzv_sci_spi_getreg8(struct rzv_sci_spi_priv_s *priv,
                                   uint8_t offset);

/* Hardware configuration */

static void rzv_sci_spi_hw_initialize(struct rzv_sci_spi_priv_s *priv);
static void rzv_sci_spi_hw_configure(struct rzv_sci_spi_priv_s *priv);
static int rzv_sci_spi_calculate_bitrate(uint32_t bitrate,
                                         uint8_t *brr, uint8_t *cks,
                                         uint8_t *mddr);

/* Transfer helpers */

static void rzv_sci_spi_writeword(struct rzv_sci_spi_priv_s *priv,
                                  uint8_t data);
static uint8_t rzv_sci_spi_readword(struct rzv_sci_spi_priv_s *priv);
static void rzv_sci_spi_enable(struct rzv_sci_spi_priv_s *priv);
static void rzv_sci_spi_disable(struct rzv_sci_spi_priv_s *priv);

/* Interrupt handling */

static int rzv_sci_spi_rxi_interrupt(int irq, void *context, void *arg);
static int rzv_sci_spi_txi_interrupt(int irq, void *context, void *arg);
static int rzv_sci_spi_tei_interrupt(int irq, void *context, void *arg);
static int rzv_sci_spi_eri_interrupt(int irq, void *context, void *arg);

/* SPI methods */

static int rzv_sci_spi_lock(struct spi_dev_s *dev, bool lock);
static uint32_t rzv_sci_spi_setfrequency(struct spi_dev_s *dev,
                                         uint32_t frequency);
static void rzv_sci_spi_setmode(struct spi_dev_s *dev, enum spi_mode_e mode);
static void rzv_sci_spi_setbits(struct spi_dev_s *dev, int nbits);
#ifdef CONFIG_SPI_HWFEATURES
static int rzv_sci_spi_hwfeatures(struct spi_dev_s *dev,
                                  spi_hwfeatures_t features);
#endif
static uint32_t rzv_sci_spi_send(struct spi_dev_s *dev, uint32_t wd);
static void rzv_sci_spi_exchange(struct spi_dev_s *dev,
                                 const void *txbuffer,
                                 void *rxbuffer, size_t nwords);
#ifndef CONFIG_SPI_EXCHANGE
static void rzv_sci_spi_sndblock(struct spi_dev_s *dev,
                                 const void *txbuffer,
                                 size_t nwords);
static void rzv_sci_spi_recvblock(struct spi_dev_s *dev, void *rxbuffer,
                                  size_t nwords);
#endif

/* Weak external functions */

const struct rzv_sci_spi_ext_dev_config_s *
weak_function rzv_sci_spi_get_dev_config(struct spi_dev_s *dev,
                                         uint32_t devid);

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* SCI_B SPI operations */

static const struct spi_ops_s rzv_sci_spi_ops =
{
  .lock              = rzv_sci_spi_lock,
  .select            = rzv_sci_spi_select,    /* Provided externally */
  .setfrequency      = rzv_sci_spi_setfrequency,
  .setmode           = rzv_sci_spi_setmode,
  .setbits           = rzv_sci_spi_setbits,
#ifdef CONFIG_SPI_HWFEATURES
  .hwfeatures        = rzv_sci_spi_hwfeatures,
#endif
  .status            = rzv_sci_spi_status,     /* Provided externally */
#ifdef CONFIG_SPI_CMDDATA
  .cmddata           = rzv_sci_spi_cmddata,    /* Provided externally */
#endif
  .send              = rzv_sci_spi_send,
#ifdef CONFIG_SPI_EXCHANGE
  .exchange          = rzv_sci_spi_exchange,
#else
  .sndblock          = rzv_sci_spi_sndblock,
  .recvblock         = rzv_sci_spi_recvblock,
#endif
#ifdef CONFIG_SPI_CALLBACK
  .registercallback  = rzv_sci_spi_register_callback, /* Provided externally */
#endif
};

/* SCI_B SPI device configurations */

#ifdef CONFIG_RZV_SCI0_SPI
static const struct rzv_sci_spi_config_s rzv_sci0_spi_config =
{
  .base     = RZV_SCI0_BASE,
  .channel  = 0,
  .rxi_elc  = RZV_ELC_SC_ELCRDRF_0,
  .txi_elc  = RZV_ELC_SC_ELCTDRE_0,
  .tei_elc  = RZV_ELC_SC_ELCTEND_0,
  .eri_elc  = RZV_ELC_SC_ELCER_0,
};

static struct rzv_sci_spi_priv_s rzv_sci0_spi_priv =
{
  .spi_dev =
  {
    .ops = &rzv_sci_spi_ops,
  },
  .config = &rzv_sci0_spi_config,
};
#endif

#ifdef CONFIG_RZV_SCI1_SPI
static const struct rzv_sci_spi_config_s rzv_sci1_spi_config =
{
  .base     = RZV_SCI1_BASE,
  .channel  = 1,
  .rxi_elc  = RZV_ELC_SC_ELCRDRF_1,
  .txi_elc  = RZV_ELC_SC_ELCTDRE_1,
  .tei_elc  = RZV_ELC_SC_ELCTEND_1,
  .eri_elc  = RZV_ELC_SC_ELCER_1,
};

static struct rzv_sci_spi_priv_s rzv_sci1_spi_priv =
{
  .spi_dev =
  {
    .ops = &rzv_sci_spi_ops,
  },
  .config = &rzv_sci1_spi_config,
};
#endif

/* Additional SCI channels 2-9 would follow the same pattern */

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_sci_spi_putreg32
 *
 * Description:
 *   Write 32-bit value to SCI_B register
 *
 ****************************************************************************/

static void rzv_sci_spi_putreg32(struct rzv_sci_spi_priv_s *priv,
                                 uint8_t offset, uint32_t value)
{
  putreg32(value, priv->config->base + offset);
}

/****************************************************************************
 * Name: rzv_sci_spi_getreg32
 *
 * Description:
 *   Read 32-bit value from SCI_B register
 *
 ****************************************************************************/

static uint32_t rzv_sci_spi_getreg32(struct rzv_sci_spi_priv_s *priv,
                                     uint8_t offset)
{
  return getreg32(priv->config->base + offset);
}

/****************************************************************************
 * Name: rzv_sci_spi_putreg8
 *
 * Description:
 *   Write 8-bit value to SCI_B register
 *
 ****************************************************************************/

static void rzv_sci_spi_putreg8(struct rzv_sci_spi_priv_s *priv,
                                uint8_t offset, uint8_t value)
{
  putreg8(value, priv->config->base + offset);
}

/****************************************************************************
 * Name: rzv_sci_spi_getreg8
 *
 * Description:
 *   Read 8-bit value from SCI_B register
 *
 ****************************************************************************/

static uint8_t rzv_sci_spi_getreg8(struct rzv_sci_spi_priv_s *priv,
                                   uint8_t offset)
{
  return getreg8(priv->config->base + offset);
}

/****************************************************************************
 * Name: rzv_sci_spi_calculate_bitrate
 *
 * Description:
 *   Calculate baud rate generator settings for desired frequency
 *
 * Input Parameters:
 *   bitrate - Desired SPI bit rate
 *   brr     - Pointer to store BRR value
 *   cks     - Pointer to store CKS value (clock source divisor)
 *   mddr    - Pointer to store MDDR value (modulation duty)
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

static int rzv_sci_spi_calculate_bitrate(uint32_t bitrate,
                                         uint8_t *brr, uint8_t *cks,
                                         uint8_t *mddr)
{
  uint32_t pclk;
  uint32_t divisor;
  uint32_t n;
  uint8_t  k;
  uint32_t best_diff = UINT32_MAX;
  uint8_t  best_brr = 0;
  uint8_t  best_cks = 0;
  uint32_t actual_rate;
  uint32_t diff;

  /* Get peripheral clock */

  pclk = rzv_get_pclk();

  /* Try different clock divider settings */

  for (k = 0; k <= 3; k++)
    {
      /* Calculate required divisor: PCLK / (divider * bitrate * 2) - 1 */

      divisor = 1 << (2 * k);  /* CKS: 0=÷1, 1=÷4, 2=÷16, 3=÷64 */

      /* Calculate BRR: n = (PCLK / (divisor * bitrate * 2)) - 1 */

      n = (pclk / (divisor * bitrate * 2)) - 1;

      if (n <= R_SCI_SPI_CLK_MAX_N)
        {
          /* Calculate actual rate */

          actual_rate = pclk / (divisor * 2 * (n + 1));
          diff = (actual_rate > bitrate) ?
                 (actual_rate - bitrate) : (bitrate - actual_rate);

          if (diff < best_diff)
            {
              best_diff = diff;
              best_brr = n;
              best_cks = k;
            }
        }
    }

  if (best_diff == UINT32_MAX)
    {
      return -EINVAL;
    }

  *brr = best_brr;
  *cks = best_cks;
  *mddr = 0;  /* Not using modulation */

  return OK;
}

/****************************************************************************
 * Name: rzv_sci_spi_hw_configure
 *
 * Description:
 *   Configure SCI_B hardware for SPI mode
 *
 ****************************************************************************/

static void rzv_sci_spi_hw_configure(struct rzv_sci_spi_priv_s *priv)
{
  uint32_t ccr0, ccr1, ccr2, ccr3, fcr;
  uint8_t brr, cks, mddr;

  /* Disable SCI_B */

  rzv_sci_spi_disable(priv);

  /* Clear all flags */

  rzv_sci_spi_putreg32(priv, RZV_SCI_CFCLR_OFFSET, 0xFFFFFFFF);
  rzv_sci_spi_putreg32(priv, RZV_SCI_FFCLR_OFFSET, 0xFFFFFFFF);

  /* Configure CCR3 for SPI mode */

  ccr3 = SCI_CCR3_MOD_SPI;           /* SPI mode */
  ccr3 |= SCI_CCR3_CHR_8BIT;         /* 8-bit data */
  ccr3 |= SCI_CCR3_FM;               /* FIFO mode */
  ccr3 |= SCI_CCR3_CKE_INT_SCK_OUT;  /* Internal clock, SCK output */

  /* Configure clock phase and polarity based on mode */

  switch (priv->mode)
    {
      case SPIDEV_MODE0:
        /* CPOL=0, CPHA=0 */

        break;

      case SPIDEV_MODE1:
        /* CPOL=0, CPHA=1 */

        ccr3 |= SCI_CCR3_CPHA;
        break;

      case SPIDEV_MODE2:
        /* CPOL=1, CPHA=0 */

        ccr3 |= SCI_CCR3_CPOL;
        break;

      case SPIDEV_MODE3:
        /* CPOL=1, CPHA=1 */

        ccr3 |= SCI_CCR3_CPHA | SCI_CCR3_CPOL;
        break;
    }

  /* Configure bit order */

  if (priv->lsbfirst)
    {
      ccr3 |= SCI_CCR3_LSBF;
    }

  rzv_sci_spi_putreg32(priv, RZV_SCI_CCR3_OFFSET, ccr3);

  /* Calculate and configure baud rate */

  if (rzv_sci_spi_calculate_bitrate(priv->frequency, &brr, &cks, &mddr) == OK)
    {
      ccr2 = (brr << SCI_CCR2_BRR_SHIFT) | (cks << SCI_CCR2_CKS_SHIFT);
      if (mddr != 0)
        {
          ccr2 |= SCI_CCR2_BRME | (mddr << SCI_CCR2_MDDR_SHIFT);
        }

      rzv_sci_spi_putreg32(priv, RZV_SCI_CCR2_OFFSET, ccr2);
    }

  /* Configure CCR0 */

  ccr0 = SCI_CCR0_RE |    /* Receive enable */
         SCI_CCR0_TE |    /* Transmit enable */
         SCI_CCR0_RIE |   /* RX interrupt enable */
         SCI_CCR0_TIE |   /* TX interrupt enable */
         SCI_CCR0_TEIE;   /* TE interrupt enable */

  rzv_sci_spi_putreg32(priv, RZV_SCI_CCR0_OFFSET, ccr0);

  /* Configure CCR1 (noise filter, etc.) */

  ccr1 = 0;  /* Default settings */
  rzv_sci_spi_putreg32(priv, RZV_SCI_CCR1_OFFSET, ccr1);

  /* Configure FIFO */

  fcr = (1 << SCI_FCR_RTRG_SHIFT) |   /* RX trigger level = 1 */
        (1 << SCI_FCR_TTRG_SHIFT);    /* TX trigger level = 1 */
  rzv_sci_spi_putreg32(priv, RZV_SCI_FCR_OFFSET, fcr);

  /* Reset FIFOs */

  rzv_sci_spi_putreg32(priv, RZV_SCI_FCR_OFFSET,
                       fcr | SCI_FCR_RFRST | SCI_FCR_TFRST);
  rzv_sci_spi_putreg32(priv, RZV_SCI_FCR_OFFSET, fcr);

  ARM_DSB();
  ARM_ISB();
}

/****************************************************************************
 * Name: rzv_sci_spi_hw_initialize
 *
 * Description:
 *   Initialize SCI_B hardware
 *
 ****************************************************************************/

static void rzv_sci_spi_hw_initialize(struct rzv_sci_spi_priv_s *priv)
{
  /* Enable module clock (MSTP) */

  /* Note: Clock enabling should be done in board-specific code */

  /* Configure hardware */

  rzv_sci_spi_hw_configure(priv);

  spiinfo("SCI%d SPI initialized\n", priv->config->channel);
}

/****************************************************************************
 * Name: rzv_sci_spi_writeword
 *
 * Description:
 *   Write one byte to SCI_B TX register
 *
 ****************************************************************************/

static void rzv_sci_spi_writeword(struct rzv_sci_spi_priv_s *priv,
                                  uint8_t data)
{
  rzv_sci_spi_putreg8(priv, RZV_SCI_TDR_OFFSET, data);
}

/****************************************************************************
 * Name: rzv_sci_spi_readword
 *
 * Description:
 *   Read one byte from SCI_B RX register
 *
 ****************************************************************************/

static uint8_t rzv_sci_spi_readword(struct rzv_sci_spi_priv_s *priv)
{
  return rzv_sci_spi_getreg8(priv, RZV_SCI_RDR_OFFSET);
}

/****************************************************************************
 * Name: rzv_sci_spi_enable
 *
 * Description:
 *   Enable SCI_B SPI
 *
 ****************************************************************************/

static void rzv_sci_spi_enable(struct rzv_sci_spi_priv_s *priv)
{
  uint32_t ccr0;

  ccr0 = rzv_sci_spi_getreg32(priv, RZV_SCI_CCR0_OFFSET);
  ccr0 |= SCI_CCR0_RE | SCI_CCR0_TE;
  rzv_sci_spi_putreg32(priv, RZV_SCI_CCR0_OFFSET, ccr0);

  ARM_DSB();
  ARM_ISB();
}

/****************************************************************************
 * Name: rzv_sci_spi_disable
 *
 * Description:
 *   Disable SCI_B SPI
 *
 ****************************************************************************/

static void rzv_sci_spi_disable(struct rzv_sci_spi_priv_s *priv)
{
  uint32_t ccr0;

  ccr0 = rzv_sci_spi_getreg32(priv, RZV_SCI_CCR0_OFFSET);
  ccr0 &= ~(SCI_CCR0_RE | SCI_CCR0_TE);
  rzv_sci_spi_putreg32(priv, RZV_SCI_CCR0_OFFSET, ccr0);

  ARM_DSB();
  ARM_ISB();
}

/****************************************************************************
 * Name: rzv_sci_spi_rxi_interrupt
 *
 * Description:
 *   RX interrupt handler
 *
 ****************************************************************************/

static int rzv_sci_spi_rxi_interrupt(int irq, void *context, void *arg)
{
  struct rzv_sci_spi_priv_s *priv = (struct rzv_sci_spi_priv_s *)arg;
  uint32_t csr;
  uint8_t data;

  csr = rzv_sci_spi_getreg32(priv, RZV_SCI_CSR_OFFSET);

  /* Check for receive data full */

  if (csr & SCI_CSR_RDRF)
    {
      /* Read data */

      data = rzv_sci_spi_readword(priv);

      if (priv->rxbuffer && priv->nrxwords > 0)
        {
          *priv->rxbuffer++ = data;
          priv->nrxwords--;
        }

      /* Clear flag */

      rzv_sci_spi_putreg32(priv, RZV_SCI_CFCLR_OFFSET, SCI_CFCLR_RDRFC);
    }

  /* Check if transfer complete */

  if (priv->nrxwords == 0 && priv->ntxwords == 0)
    {
      /* Disable interrupts */

      uint32_t ccr0 = rzv_sci_spi_getreg32(priv, RZV_SCI_CCR0_OFFSET);
      ccr0 &= ~(SCI_CCR0_RIE | SCI_CCR0_TIE);
      rzv_sci_spi_putreg32(priv, RZV_SCI_CCR0_OFFSET, ccr0);

      /* Wake up waiting thread */

      nxsem_post(&priv->sem_isr);
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_sci_spi_txi_interrupt
 *
 * Description:
 *   TX interrupt handler
 *
 ****************************************************************************/

static int rzv_sci_spi_txi_interrupt(int irq, void *context, void *arg)
{
  struct rzv_sci_spi_priv_s *priv = (struct rzv_sci_spi_priv_s *)arg;
  uint32_t csr;
  uint8_t data;

  csr = rzv_sci_spi_getreg32(priv, RZV_SCI_CSR_OFFSET);

  /* Check for transmit data empty */

  if (csr & SCI_CSR_TDRE)
    {
      if (priv->ntxwords > 0)
        {
          /* Get next byte to transmit */

          data = priv->txbuffer ? *priv->txbuffer++ : 0xFF;
          priv->ntxwords--;

          /* Write data */

          rzv_sci_spi_writeword(priv, data);

          /* Clear flag */

          rzv_sci_spi_putreg32(priv, RZV_SCI_CFCLR_OFFSET, SCI_CFCLR_TDREC);
        }
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_sci_spi_tei_interrupt
 *
 * Description:
 *   TE (transmit end) interrupt handler
 *
 ****************************************************************************/

static int rzv_sci_spi_tei_interrupt(int irq, void *context, void *arg)
{
  struct rzv_sci_spi_priv_s *priv = (struct rzv_sci_spi_priv_s *)arg;
  uint32_t csr;

  csr = rzv_sci_spi_getreg32(priv, RZV_SCI_CSR_OFFSET);

  if (csr & SCI_CSR_TEND)
    {
      /* Transmission complete */

      spiinfo("TE interrupt\n");
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_sci_spi_eri_interrupt
 *
 * Description:
 *   Error interrupt handler
 *
 ****************************************************************************/

static int rzv_sci_spi_eri_interrupt(int irq, void *context, void *arg)
{
  struct rzv_sci_spi_priv_s *priv = (struct rzv_sci_spi_priv_s *)arg;
  uint32_t csr;

  csr = rzv_sci_spi_getreg32(priv, RZV_SCI_CSR_OFFSET);

  /* Check for errors */

  if (csr & (SCI_CSR_ORER | SCI_CSR_PER | SCI_CSR_FER | SCI_CSR_MFF))
    {
      spierr("SCI%d error: CSR=0x%08x\n", priv->config->channel, csr);
      priv->error = true;

      /* Clear error flags */

      rzv_sci_spi_putreg32(priv, RZV_SCI_CFCLR_OFFSET,
                           SCI_CFCLR_ORERC | SCI_CFCLR_PERC |
                           SCI_CFCLR_FERC | SCI_CFCLR_MFFC);

      /* Wake up waiting thread */

      nxsem_post(&priv->sem_isr);
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_sci_spi_lock
 *
 * Description:
 *   Lock/unlock the SPI device
 *
 ****************************************************************************/

static int rzv_sci_spi_lock(struct spi_dev_s *dev, bool lock)
{
  struct rzv_sci_spi_priv_s *priv = (struct rzv_sci_spi_priv_s *)dev;
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
 * Name: rzv_sci_spi_setfrequency
 *
 * Description:
 *   Set the SPI frequency
 *
 ****************************************************************************/

static uint32_t rzv_sci_spi_setfrequency(struct spi_dev_s *dev,
                                         uint32_t frequency)
{
  struct rzv_sci_spi_priv_s *priv = (struct rzv_sci_spi_priv_s *)dev;
  uint8_t brr, cks, mddr;
  uint32_t pclk;
  uint32_t divisor;

  if (frequency != priv->frequency)
    {
      /* Limit frequency range */

      if (frequency > RZV_SCI_SPI_MAX_FREQUENCY)
        {
          frequency = RZV_SCI_SPI_MAX_FREQUENCY;
        }
      else if (frequency < RZV_SCI_SPI_MIN_FREQUENCY)
        {
          frequency = RZV_SCI_SPI_MIN_FREQUENCY;
        }

      priv->frequency = frequency;

      /* Calculate actual frequency */

      if (rzv_sci_spi_calculate_bitrate(frequency, &brr, &cks, &mddr) == OK)
        {
          pclk = rzv_get_pclk();
          divisor = 1 << (2 * cks);
          priv->actual = pclk / (divisor * 2 * (brr + 1));

          /* Reconfigure hardware */

          rzv_sci_spi_hw_configure(priv);
        }

      spiinfo("Frequency: %d -> %d\n", frequency, priv->actual);
    }

  return priv->actual;
}

/****************************************************************************
 * Name: rzv_sci_spi_setmode
 *
 * Description:
 *   Set the SPI mode
 *
 ****************************************************************************/

static void rzv_sci_spi_setmode(struct spi_dev_s *dev, enum spi_mode_e mode)
{
  struct rzv_sci_spi_priv_s *priv = (struct rzv_sci_spi_priv_s *)dev;

  if (mode != priv->mode)
    {
      priv->mode = mode;
      rzv_sci_spi_hw_configure(priv);
      spiinfo("Mode: %d\n", mode);
    }
}

/****************************************************************************
 * Name: rzv_sci_spi_setbits
 *
 * Description:
 *   Set the number of bits per word
 *
 ****************************************************************************/

static void rzv_sci_spi_setbits(struct spi_dev_s *dev, int nbits)
{
  struct rzv_sci_spi_priv_s *priv = (struct rzv_sci_spi_priv_s *)dev;

  /* SCI_B SPI only supports 8-bit transfers */

  if (nbits != 8)
    {
      spierr("Unsupported nbits: %d (only 8-bit supported)\n", nbits);
      return;
    }

  priv->nbits = nbits;
}

#ifdef CONFIG_SPI_HWFEATURES
/****************************************************************************
 * Name: rzv_sci_spi_hwfeatures
 *
 * Description:
 *   Set hardware-specific feature flags
 *
 ****************************************************************************/

static int rzv_sci_spi_hwfeatures(struct spi_dev_s *dev,
                                  spi_hwfeatures_t features)
{
  struct rzv_sci_spi_priv_s *priv = (struct rzv_sci_spi_priv_s *)dev;

  /* Check for LSB first */

  if ((features & HWFEAT_LSBFIRST) != 0)
    {
      priv->lsbfirst = true;
    }
  else
    {
      priv->lsbfirst = false;
    }

  rzv_sci_spi_hw_configure(priv);

  return OK;
}
#endif

/****************************************************************************
 * Name: rzv_sci_spi_send
 *
 * Description:
 *   Exchange one word on SPI
 *
 ****************************************************************************/

static uint32_t rzv_sci_spi_send(struct spi_dev_s *dev, uint32_t wd)
{
  struct rzv_sci_spi_priv_s *priv = (struct rzv_sci_spi_priv_s *)dev;
  uint8_t txbyte = (uint8_t)wd;
  uint8_t rxbyte = 0;

  rzv_sci_spi_exchange(dev, &txbyte, &rxbyte, 1);

  return (uint32_t)rxbyte;
}

/****************************************************************************
 * Name: rzv_sci_spi_exchange
 *
 * Description:
 *   Exchange a block of data on SPI
 *
 ****************************************************************************/

static void rzv_sci_spi_exchange(struct spi_dev_s *dev,
                                 const void *txbuffer,
                                 void *rxbuffer, size_t nwords)
{
  struct rzv_sci_spi_priv_s *priv = (struct rzv_sci_spi_priv_s *)dev;
  uint32_t ccr0;

  /* Set up transfer state */

  priv->txbuffer = (const uint8_t *)txbuffer;
  priv->rxbuffer = (uint8_t *)rxbuffer;
  priv->ntxwords = nwords;
  priv->nrxwords = nwords;
  priv->error = false;

  /* Clear semaphore */

  while (nxsem_trywait(&priv->sem_isr) == OK);

  /* Enable interrupts */

  ccr0 = rzv_sci_spi_getreg32(priv, RZV_SCI_CCR0_OFFSET);
  ccr0 |= SCI_CCR0_RIE | SCI_CCR0_TIE;
  rzv_sci_spi_putreg32(priv, RZV_SCI_CCR0_OFFSET, ccr0);

  /* Start first transmission */

  if (priv->ntxwords > 0)
    {
      uint8_t data = priv->txbuffer ? *priv->txbuffer++ : 0xFF;
      priv->ntxwords--;
      rzv_sci_spi_writeword(priv, data);
    }

  /* Wait for completion */

  nxsem_wait(&priv->sem_isr);

  /* Check for errors */

  if (priv->error)
    {
      spierr("Transfer error occurred\n");
    }
}

#ifndef CONFIG_SPI_EXCHANGE
/****************************************************************************
 * Name: rzv_sci_spi_sndblock
 *
 * Description:
 *   Send a block of data on SPI
 *
 ****************************************************************************/

static void rzv_sci_spi_sndblock(struct spi_dev_s *dev,
                                 const void *txbuffer,
                                 size_t nwords)
{
  rzv_sci_spi_exchange(dev, txbuffer, NULL, nwords);
}

/****************************************************************************
 * Name: rzv_sci_spi_recvblock
 *
 * Description:
 *   Receive a block of data from SPI
 *
 ****************************************************************************/

static void rzv_sci_spi_recvblock(struct spi_dev_s *dev, void *rxbuffer,
                                  size_t nwords)
{
  rzv_sci_spi_exchange(dev, NULL, rxbuffer, nwords);
}
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_sci_spibus_initialize
 *
 * Description:
 *   Initialize the selected SCI_B SPI bus
 *
 ****************************************************************************/

struct spi_dev_s *rzv_sci_spibus_initialize(int bus)
{
  struct rzv_sci_spi_priv_s *priv = NULL;
  irqstate_t flags;
  int ret;

  spiinfo("Initializing SCI%d SPI bus\n", bus);

  /* Get device instance */

  switch (bus)
    {
#ifdef CONFIG_RZV_SCI0_SPI
      case 0:
        priv = &rzv_sci0_spi_priv;
        break;
#endif
#ifdef CONFIG_RZV_SCI1_SPI
      case 1:
        priv = &rzv_sci1_spi_priv;
        break;
#endif
      default:
        spierr("Invalid bus number: %d\n", bus);
        return NULL;
    }

  /* Initialize mutex and semaphore */

  nxmutex_init(&priv->lock);
  nxsem_init(&priv->sem_isr, 0, 0);

  /* Set default configuration */

  priv->frequency = 100000;  /* 100 kHz default */
  priv->actual = 0;
  priv->mode = SPIDEV_MODE0;
  priv->nbits = 8;
  priv->lsbfirst = false;

  /* Initialize hardware */

  rzv_sci_spi_hw_initialize(priv);

  /* Attach interrupts using dynamic IRQ assignment */

  flags = enter_critical_section();

  /* RXI interrupt */

  priv->rxi_irq = rzv_icu_attach_event(priv->config->rxi_elc,
                                       rzv_sci_spi_rxi_interrupt,
                                       priv);
  if (priv->rxi_irq < 0)
    {
      spierr("Failed to attach RXI interrupt\n");
      goto errout;
    }

  /* TXI interrupt */

  priv->txi_irq = rzv_icu_attach_event(priv->config->txi_elc,
                                       rzv_sci_spi_txi_interrupt,
                                       priv);
  if (priv->txi_irq < 0)
    {
      spierr("Failed to attach TXI interrupt\n");
      goto errout;
    }

  /* TEI interrupt */

  priv->tei_irq = rzv_icu_attach_event(priv->config->tei_elc,
                                       rzv_sci_spi_tei_interrupt,
                                       priv);
  if (priv->tei_irq < 0)
    {
      spierr("Failed to attach TEI interrupt\n");
      goto errout;
    }

  /* ERI interrupt */

  priv->eri_irq = rzv_icu_attach_event(priv->config->eri_elc,
                                       rzv_sci_spi_eri_interrupt,
                                       priv);
  if (priv->eri_irq < 0)
    {
      spierr("Failed to attach ERI interrupt\n");
      goto errout;
    }

  /* Enable interrupts */

  up_enable_irq(priv->rxi_irq);
  up_enable_irq(priv->txi_irq);
  up_enable_irq(priv->tei_irq);
  up_enable_irq(priv->eri_irq);

  leave_critical_section(flags);

  spiinfo("SCI%d SPI bus initialized successfully\n", bus);

  return &priv->spi_dev;

errout:
  leave_critical_section(flags);
  return NULL;
}

/****************************************************************************
 * Name: rzv_sci_spibus_uninitialize
 *
 * Description:
 *   Uninitialize an SCI_B SPI bus
 *
 ****************************************************************************/

int rzv_sci_spibus_uninitialize(struct spi_dev_s *dev)
{
  struct rzv_sci_spi_priv_s *priv = (struct rzv_sci_spi_priv_s *)dev;

  /* Disable interrupts */

  up_disable_irq(priv->rxi_irq);
  up_disable_irq(priv->txi_irq);
  up_disable_irq(priv->tei_irq);
  up_disable_irq(priv->eri_irq);

  /* Detach interrupts */

  irq_detach(priv->rxi_irq);
  irq_detach(priv->txi_irq);
  irq_detach(priv->tei_irq);
  irq_detach(priv->eri_irq);

  /* Disable hardware */

  rzv_sci_spi_disable(priv);

  /* Destroy mutex and semaphore */

  nxmutex_destroy(&priv->lock);
  nxsem_destroy(&priv->sem_isr);

  return OK;
}

/****************************************************************************
 * Name: rzv_sci_spi_setbitorder
 *
 * Description:
 *   Set the SCI_B SPI bit order (MSB-first or LSB-first)
 *
 ****************************************************************************/

void rzv_sci_spi_setbitorder(struct spi_dev_s *dev, bool lsbfirst)
{
  struct rzv_sci_spi_priv_s *priv = (struct rzv_sci_spi_priv_s *)dev;

  priv->lsbfirst = lsbfirst;
  rzv_sci_spi_hw_configure(priv);
}

#endif /* CONFIG_RZV_SCI_SPI */
