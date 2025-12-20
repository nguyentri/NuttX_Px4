/****************************************************************************
 * arch/arm/src/rzv/rzv_spi.c
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
#include <assert.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/semaphore.h>
#include <nuttx/spi/spi.h>

#include "arm_internal.h"
#include "chip.h"
#include "rzv_clock.h"
#include "rzv_icu.h"
#include "rzv_gpio.h"
#include "hardware/rzv_spi.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Default values ***********************************************************/

#define SPI_DEFAULT_FREQUENCY     1000000   /* 1 MHz */
#define SPI_FIFO_SIZE             4         /* FIFO depth */
#define SPI_TIMEOUT_MS            1000      /* Transfer timeout in ms */
#define SPI_TIMEOUT_LOOPS         (SPI_TIMEOUT_MS * 1000) /* Timeout iterations */

/* Error flags to check in SPSR */
#define SPI_ERROR_FLAGS   (SPI_SPSR_OVRF | SPI_SPSR_MODF | \
                           SPI_SPSR_PERF | SPI_SPSR_UDRF)

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* SPI Device Hardware Configuration */

struct rzv_spi_config_s
{
  uintptr_t base;         /* SPI base address */
  uint32_t  frequency;    /* Default SPI frequency */
  uint8_t   port;         /* SPI port number (0-2) */
  uint32_t  clk_id;       /* Clock ID for CPG */
  uint16_t  elc_rxi;      /* ELC event for RX interrupt */
  uint16_t  elc_txi;      /* ELC event for TX interrupt */
  uint16_t  elc_tei;      /* ELC event for Transfer end */
  uint16_t  elc_eri;      /* ELC event for Error interrupt */
};

/* SPI Device Private Data */

struct rzv_spi_priv_s
{
  struct spi_dev_s spidev;            /* Externally visible part */
  const struct rzv_spi_config_s *config; /* Port configuration */
  sem_t exclsem;                      /* Mutual exclusion semaphore */
  sem_t waitsem;                      /* Wait for transfer completion */

  uint32_t frequency;                 /* Requested clock frequency */
  uint32_t actual;                    /* Actual clock frequency */
  uint8_t  nbits;                     /* Width of word in bits (8 or 16) */
  uint8_t  mode;                      /* SPI mode */

  /* IRQ tracking */
  int      irq_rxi;                   /* Allocated RX IRQ */
  int      irq_txi;                   /* Allocated TX IRQ */
  int      irq_tei;                   /* Allocated TEI IRQ */
  int      irq_eri;                   /* Allocated Error IRQ */

  /* Transfer state */
  const void *txbuffer;               /* TX buffer pointer */
  void       *rxbuffer;               /* RX buffer pointer */
  size_t      ntxwords;               /* TX words remaining */
  size_t      nrxwords;               /* RX words remaining */
  bool        error;                  /* Transfer error flag */
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* SPI Register Access */

static inline uint8_t rzv_spi_getreg8(struct rzv_spi_priv_s *priv,
                                      unsigned int offset);
static inline void rzv_spi_putreg8(struct rzv_spi_priv_s *priv,
                                   unsigned int offset, uint8_t value);
static inline uint16_t rzv_spi_getreg16(struct rzv_spi_priv_s *priv,
                                        unsigned int offset);
static inline void rzv_spi_putreg16(struct rzv_spi_priv_s *priv,
                                    unsigned int offset, uint16_t value);
static inline uint32_t rzv_spi_getreg32(struct rzv_spi_priv_s *priv,
                                        unsigned int offset);
static inline void rzv_spi_putreg32(struct rzv_spi_priv_s *priv,
                                    unsigned int offset, uint32_t value);

/* SPI Helpers */

static void rzv_spi_setfrequency(struct rzv_spi_priv_s *priv,
                                 uint32_t frequency);
static void rzv_spi_setmode(struct rzv_spi_priv_s *priv, uint8_t mode);
static void rzv_spi_setbits(struct rzv_spi_priv_s *priv, uint8_t nbits);

/* Interrupt handlers */

static int rzv_spi_rxi_interrupt(int irq, void *context, void *arg);
static int rzv_spi_txi_interrupt(int irq, void *context, void *arg);
static int rzv_spi_tei_interrupt(int irq, void *context, void *arg);
static int rzv_spi_eri_interrupt(int irq, void *context, void *arg);

/* SPI Operations */

static int rzv_spi_lock(struct spi_dev_s *dev, bool lock);
static uint32_t rzv_spi_setfrequency_dev(struct spi_dev_s *dev,
                                         uint32_t frequency);
static void rzv_spi_setmode_dev(struct spi_dev_s *dev,
                                enum spi_mode_e mode);
static void rzv_spi_setbits_dev(struct spi_dev_s *dev, int nbits);
#ifdef CONFIG_SPI_HWFEATURES
static int rzv_spi_hwfeatures(struct spi_dev_s *dev,
                              spi_hwfeatures_t features);
#endif
static uint32_t rzv_spi_send(struct spi_dev_s *dev, uint32_t wd);
static void rzv_spi_exchange(struct spi_dev_s *dev,
                             const void *txbuffer,
                             void *rxbuffer, size_t nwords);
#ifndef CONFIG_SPI_EXCHANGE
static void rzv_spi_sndblock(struct spi_dev_s *dev,
                             const void *txbuffer, size_t nwords);
static void rzv_spi_recvblock(struct spi_dev_s *dev,
                              void *rxbuffer, size_t nwords);
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Weak default implementations for board-specific SPI functions */

weak_function void rzv_spi_select(struct spi_dev_s *dev, uint32_t devid,
                                   bool selected)
{
  /* Default implementation does nothing */
}

weak_function uint8_t rzv_spi_status(struct spi_dev_s *dev, uint32_t devid)
{
  /* Default implementation returns 0 */
  return 0;
}

#ifdef CONFIG_SPI_CMDDATA
weak_function int rzv_spi_cmddata(struct spi_dev_s *dev, uint32_t devid,
                                   bool cmd)
{
  /* Default implementation returns OK */
  return OK;
}
#endif

/* SPI Interface */

static const struct spi_ops_s g_spi_ops =
{
  .lock              = rzv_spi_lock,
  .select            = rzv_spi_select,      /* Provided by board */
  .setfrequency      = rzv_spi_setfrequency_dev,
  .setmode           = rzv_spi_setmode_dev,
  .setbits           = rzv_spi_setbits_dev,
#ifdef CONFIG_SPI_HWFEATURES
  .hwfeatures        = rzv_spi_hwfeatures,
#endif
  .status            = rzv_spi_status,      /* Provided by board */
#ifdef CONFIG_SPI_CMDDATA
  .cmddata           = rzv_spi_cmddata,     /* Provided by board */
#endif
  .send              = rzv_spi_send,
#ifdef CONFIG_SPI_EXCHANGE
  .exchange          = rzv_spi_exchange,
#else
  .sndblock          = rzv_spi_sndblock,
  .recvblock         = rzv_spi_recvblock,
#endif
#ifdef CONFIG_SPI_TRIGGER
  .trigger           = rzv_spi_trigger,     /* Not implemented */
#endif
  .registercallback  = NULL,                /* Not implemented */
};

/* SPI0 Configuration */

#ifdef CONFIG_RZV_SPI0
static const struct rzv_spi_config_s g_spi0_config =
{
  .base      = RZV_SPI0_BASE,
  .frequency = SPI_DEFAULT_FREQUENCY,
  .port      = 0,
  .clk_id    = RZV_CPG_CLK_SPI0,
  .elc_rxi   = RZV_ELC_SP_ELCRDRF_0,
  .elc_txi   = RZV_ELC_SP_ELCTDRE_0,
  .elc_tei   = RZV_ELC_SP_ELCCEND_0,
  .elc_eri   = RZV_ELC_SP_ELCERR_0,
};

static struct rzv_spi_priv_s g_spi0_priv =
{
  .spidev.ops = &g_spi_ops,
  .config     = &g_spi0_config,
};
#endif

/* SPI1 Configuration */

#ifdef CONFIG_RZV_SPI1
static const struct rzv_spi_config_s g_spi1_config =
{
  .base      = RZV_SPI1_BASE,
  .frequency = SPI_DEFAULT_FREQUENCY,
  .port      = 1,
  .clk_id    = RZV_CPG_CLK_SPI1,
  .elc_rxi   = RZV_ELC_SP_ELCRDRF_1,
  .elc_txi   = RZV_ELC_SP_ELCTDRE_1,
  .elc_tei   = RZV_ELC_SP_ELCCEND_1,
  .elc_eri   = RZV_ELC_SP_ELCERR_1,
};

static struct rzv_spi_priv_s g_spi1_priv =
{
  .spidev.ops = &g_spi_ops,
  .config     = &g_spi1_config,
};
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_spi_getreg8/16/32
 ****************************************************************************/

static inline uint8_t rzv_spi_getreg8(struct rzv_spi_priv_s *priv,
                                      unsigned int offset)
{
  return getreg8(priv->config->base + offset);
}

static inline void rzv_spi_putreg8(struct rzv_spi_priv_s *priv,
                                   unsigned int offset, uint8_t value)
{
  putreg8(value, priv->config->base + offset);
}

static inline uint16_t rzv_spi_getreg16(struct rzv_spi_priv_s *priv,
                                        unsigned int offset)
{
  return getreg16(priv->config->base + offset);
}

static inline void rzv_spi_putreg16(struct rzv_spi_priv_s *priv,
                                    unsigned int offset, uint16_t value)
{
  putreg16(value, priv->config->base + offset);
}

static inline uint32_t rzv_spi_getreg32(struct rzv_spi_priv_s *priv,
                                        unsigned int offset)
{
  return getreg32(priv->config->base + offset);
}

static inline void rzv_spi_putreg32(struct rzv_spi_priv_s *priv,
                                    unsigned int offset, uint32_t value)
{
  putreg32(value, priv->config->base + offset);
}

/****************************************************************************
 * Name: rzv_spi_setfrequency
 ****************************************************************************/

static void rzv_spi_setfrequency(struct rzv_spi_priv_s *priv,
                                 uint32_t frequency)
{
  uint32_t pclk;
  uint32_t divisor;
  uint8_t spbr;
  uint8_t brdv;

  /* Get peripheral clock */
  pclk = rzv_get_pclk_frequency();

  /* Calculate bit rate using correct formula:
   * Bit Rate = PCLK / (2 * (SPBR + 1) * 2^BRDV)
   * Therefore: SPBR = (PCLK / (2 * Bit Rate * 2^BRDV)) - 1
   */

  for (brdv = 0; brdv <= 3; brdv++)
    {
      uint32_t divider = 2 * frequency * (1 << brdv);
      uint32_t spbr_calc = (pclk / divider);

      if (spbr_calc > 0)
        {
          spbr_calc--; /* SPBR is (divider - 1) */
        }

      if (spbr_calc <= 255)
        {
          spbr = (uint8_t)spbr_calc;
          break;
        }
    }

  if (brdv > 3)
    {
      /* Limit to maximum divisor */
      brdv = 3;
      spbr = 255;
      spiwarn("Frequency %lu too low, using minimum\n", frequency);
    }

  /* Disable SPI (SPCR is a 32-bit control register) */
  rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET, 0);

  /* Set bit rate (SPBR register) */
  rzv_spi_putreg8(priv, RZV_SPI_SPBR_OFFSET, spbr);

  /* Update command register with BRDV (SPCMD is 32-bit) */
  uint32_t spcmd = rzv_spi_getreg32(priv, RZV_SPI_SPCMD_OFFSET(0));
  spcmd = (spcmd & ~SPI_SPCMD_BRDV_MASK) |
    ((brdv << SPI_SPCMD_BRDV_SHIFT) & SPI_SPCMD_BRDV_MASK);
  rzv_spi_putreg32(priv, RZV_SPI_SPCMD_OFFSET(0), spcmd);

  /* Calculate actual frequency */
  priv->actual = pclk / (2 * (spbr + 1) * (1 << brdv));
  priv->frequency = frequency;

  /* Re-enable SPI */
  rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET,
                  SPI_SPCR_SPE | SPI_SPCR_MSTR);

  spiinfo("Frequency: request=%lu actual=%lu\n",
          frequency, priv->actual);
}

/****************************************************************************
 * Name: rzv_spi_setmode
 ****************************************************************************/

static void rzv_spi_setmode(struct rzv_spi_priv_s *priv, uint8_t mode)
{
  uint32_t spcmd;  /* Fixed: SPCMD is 32-bit register */

  /* Disable SPI */
  rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET, 0);

  /* Read command register */
  spcmd = rzv_spi_getreg32(priv, RZV_SPI_SPCMD_OFFSET(0));

  /* Clear mode bits (CPOL, CPHA) */
  spcmd &= ~(SPI_SPCMD_CPOL | SPI_SPCMD_CPHA);

  /* Set mode */
  switch (mode)
    {
      case SPIDEV_MODE0:  /* CPOL=0 CPHA=0 */
        break;

      case SPIDEV_MODE1:  /* CPOL=0 CPHA=1 */
        spcmd |= SPI_SPCMD_CPHA;
        break;

      case SPIDEV_MODE2:  /* CPOL=1 CPHA=0 */
        spcmd |= SPI_SPCMD_CPOL;
        break;

      case SPIDEV_MODE3:  /* CPOL=1 CPHA=1 */
        spcmd |= SPI_SPCMD_CPOL | SPI_SPCMD_CPHA;
        break;

      default:
        spierr("Invalid mode: %d\n", mode);
        return;
    }

  /* Write command register */
  rzv_spi_putreg32(priv, RZV_SPI_SPCMD_OFFSET(0), spcmd);

  priv->mode = mode;

  /* Re-enable SPI */
  rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET,
                  SPI_SPCR_SPE | SPI_SPCR_MSTR);

  spiinfo("Mode: %d\n", mode);
}

/****************************************************************************
 * Name: rzv_spi_setbits
 ****************************************************************************/

static void rzv_spi_setbits(struct rzv_spi_priv_s *priv, uint8_t nbits)
{
  uint32_t spcmd;  /* Fixed: SPCMD is 32-bit register */

  /* Disable SPI */
  rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET, 0);

  /* Read command register */
  spcmd = rzv_spi_getreg32(priv, RZV_SPI_SPCMD_OFFSET(0));

  /* Clear data length bits */
  spcmd &= ~SPI_SPCMD_SPB_MASK;

  /* Set data length */
  if (nbits == 8)
    {
      spcmd |= SPI_SPCMD_SPB_8BIT;
    }
  else if (nbits == 16)
    {
      spcmd |= SPI_SPCMD_SPB_16BIT;
    }
  else
    {
      return;
    }

  /* Write command register (32-bit) */
  rzv_spi_putreg32(priv, RZV_SPI_SPCMD_OFFSET(0), spcmd);

  priv->nbits = nbits;

  /* Re-enable SPI */
  rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET,
                  SPI_SPCR_SPE | SPI_SPCR_MSTR);

  spiinfo("Bits: %d\n", nbits);
}

/****************************************************************************
 * Name: rzv_spi_lock
 ****************************************************************************/

static int rzv_spi_lock(struct spi_dev_s *dev, bool lock)
{
  struct rzv_spi_priv_s *priv = (struct rzv_spi_priv_s *)dev;
  int ret;

  if (lock)
    {
      ret = nxsem_wait_uninterruptible(&priv->exclsem);
    }
  else
    {
      ret = nxsem_post(&priv->exclsem);
    }

  return ret;
}

/****************************************************************************
 * Name: rzv_spi_setfrequency_dev
 ****************************************************************************/

static uint32_t rzv_spi_setfrequency_dev(struct spi_dev_s *dev,
                                         uint32_t frequency)
{
  struct rzv_spi_priv_s *priv = (struct rzv_spi_priv_s *)dev;

  if (priv->frequency != frequency)
    {
      rzv_spi_setfrequency(priv, frequency);
    }

  return priv->actual;
}

/****************************************************************************
 * Name: rzv_spi_setmode_dev
 ****************************************************************************/

static void rzv_spi_setmode_dev(struct spi_dev_s *dev,
                                enum spi_mode_e mode)
{
  struct rzv_spi_priv_s *priv = (struct rzv_spi_priv_s *)dev;

  if (priv->mode != mode)
    {
      rzv_spi_setmode(priv, mode);
    }
}

/****************************************************************************
 * Name: rzv_spi_setbits_dev
 ****************************************************************************/

static void rzv_spi_setbits_dev(struct spi_dev_s *dev, int nbits)
{
  struct rzv_spi_priv_s *priv = (struct rzv_spi_priv_s *)dev;

  if (priv->nbits != nbits)
    {
      rzv_spi_setbits(priv, nbits);
    }
}

/****************************************************************************
 * Name: rzv_spi_send
 ****************************************************************************/

static uint32_t rzv_spi_send(struct spi_dev_s *dev, uint32_t wd)
{
  struct rzv_spi_priv_s *priv = (struct rzv_spi_priv_s *)dev;
  uint32_t rxdata = 0xffff;
  uint32_t spsr;
  int timeout;

  /* Wait for TX buffer empty with timeout */
  timeout = SPI_TIMEOUT_LOOPS;
  while (timeout-- > 0)
    {
      spsr = rzv_spi_getreg32(priv, RZV_SPI_SPSR_OFFSET);

      /* Check for errors */
      if (spsr & SPI_ERROR_FLAGS)
        {
          spierr("SPI error flags: 0x%08lx\n", spsr);
          /* Clear error flags */
          rzv_spi_putreg32(priv, RZV_SPI_SPSRC_OFFSET,
                          spsr & SPI_ERROR_FLAGS);
          return 0xffff;
        }

      if (spsr & SPI_SPSR_SPTEF)
        {
          break;
        }
    }

  if (timeout <= 0)
    {
      spierr("TX timeout\n");
      return 0xffff;
    }

  /* Write data */
  if (priv->nbits == 8)
    {
      rzv_spi_putreg8(priv, RZV_SPI_SPDR_OFFSET, (uint8_t)wd);
    }
  else
    {
      rzv_spi_putreg16(priv, RZV_SPI_SPDR_OFFSET, (uint16_t)wd);
    }

  /* Wait for RX data full with timeout */
  timeout = SPI_TIMEOUT_LOOPS;
  while (timeout-- > 0)
    {
      spsr = rzv_spi_getreg32(priv, RZV_SPI_SPSR_OFFSET);

      /* Check for errors */
      if (spsr & SPI_ERROR_FLAGS)
        {
          spierr("SPI error flags: 0x%08lx\n", spsr);
          /* Clear error flags */
          rzv_spi_putreg32(priv, RZV_SPI_SPSRC_OFFSET,
                          spsr & SPI_ERROR_FLAGS);
          return 0xffff;
        }

      if (spsr & SPI_SPSR_SPRF)
        {
          break;
        }
    }

  if (timeout <= 0)
    {
      spierr("RX timeout\n");
      return 0xffff;
    }

  /* Read received data */
  if (priv->nbits == 8)
    {
      rxdata = rzv_spi_getreg8(priv, RZV_SPI_SPDR_OFFSET);
    }
  else
    {
      rxdata = rzv_spi_getreg16(priv, RZV_SPI_SPDR_OFFSET);
    }

  return rxdata;
}

/****************************************************************************
 * Name: rzv_spi_exchange
 ****************************************************************************/

static void rzv_spi_exchange(struct spi_dev_s *dev,
                             const void *txbuffer,
                             void *rxbuffer, size_t nwords)
{
  struct rzv_spi_priv_s *priv = (struct rzv_spi_priv_s *)dev;
  const uint8_t *src8 = txbuffer;
  uint8_t *dest8 = rxbuffer;
  const uint16_t *src16 = txbuffer;
  uint16_t *dest16 = rxbuffer;
  size_t i;

  for (i = 0; i < nwords; i++)
    {
      uint32_t wd = 0xffff;
      uint32_t rd;

      if (txbuffer)
        {
          if (priv->nbits == 8)
            {
              wd = *src8++;
            }
          else
            {
              wd = *src16++;
            }
        }

      rd = rzv_spi_send(dev, wd);

      if (rxbuffer)
        {
          if (priv->nbits == 8)
            {
              *dest8++ = (uint8_t)rd;
            }
          else
            {
              *dest16++ = (uint16_t)rd;
            }
        }
    }
}

/****************************************************************************
 * Name: rzv_spi_sndblock
 ****************************************************************************/

#ifndef CONFIG_SPI_EXCHANGE
static void rzv_spi_sndblock(struct spi_dev_s *dev,
                             const void *txbuffer, size_t nwords)
{
  rzv_spi_exchange(dev, txbuffer, NULL, nwords);
}
#endif

/****************************************************************************
 * Name: rzv_spi_recvblock
 ****************************************************************************/

#ifndef CONFIG_SPI_EXCHANGE
static void rzv_spi_recvblock(struct spi_dev_s *dev,
                              void *rxbuffer, size_t nwords)
{
  rzv_spi_exchange(dev, NULL, rxbuffer, nwords);
}
#endif

/****************************************************************************
 * Name: rzv_spi_rxi_interrupt
 *
 * Description:
 *   RX buffer full interrupt handler
 *
 ****************************************************************************/

static int rzv_spi_rxi_interrupt(int irq, void *context, void *arg)
{
  struct rzv_spi_priv_s *priv = (struct rzv_spi_priv_s *)arg;
  uint32_t data;

  /* Read received data */
  if (priv->nrxwords > 0 && priv->rxbuffer)
    {
      if (priv->nbits == 8)
        {
          data = rzv_spi_getreg8(priv, RZV_SPI_SPDR_OFFSET);
          ((uint8_t *)priv->rxbuffer)[0] = (uint8_t)data;
          priv->rxbuffer = (void *)(((uint8_t *)priv->rxbuffer) + 1);
        }
      else
        {
          data = rzv_spi_getreg16(priv, RZV_SPI_SPDR_OFFSET);
          ((uint16_t *)priv->rxbuffer)[0] = (uint16_t)data;
          priv->rxbuffer = (void *)(((uint16_t *)priv->rxbuffer) + 1);
        }

      priv->nrxwords--;
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_spi_txi_interrupt
 *
 * Description:
 *   TX buffer empty interrupt handler
 *
 ****************************************************************************/

static int rzv_spi_txi_interrupt(int irq, void *context, void *arg)
{
  struct rzv_spi_priv_s *priv = (struct rzv_spi_priv_s *)arg;
  uint32_t data = 0xffff;

  /* Transmit next word */
  if (priv->ntxwords > 0)
    {
      if (priv->txbuffer)
        {
          if (priv->nbits == 8)
            {
              data = ((uint8_t *)priv->txbuffer)[0];
              priv->txbuffer = (const void *)(((uint8_t *)priv->txbuffer) + 1);
            }
          else
            {
              data = ((uint16_t *)priv->txbuffer)[0];
              priv->txbuffer = (const void *)(((uint16_t *)priv->txbuffer) + 1);
            }
        }

      /* Write data */
      if (priv->nbits == 8)
        {
          rzv_spi_putreg8(priv, RZV_SPI_SPDR_OFFSET, (uint8_t)data);
        }
      else
        {
          rzv_spi_putreg16(priv, RZV_SPI_SPDR_OFFSET, (uint16_t)data);
        }

      priv->ntxwords--;
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_spi_tei_interrupt
 *
 * Description:
 *   Transfer end interrupt handler
 *
 ****************************************************************************/

static int rzv_spi_tei_interrupt(int irq, void *context, void *arg)
{
  struct rzv_spi_priv_s *priv = (struct rzv_spi_priv_s *)arg;

  /* Signal transfer completion */
  nxsem_post(&priv->waitsem);

  return OK;
}

/****************************************************************************
 * Name: rzv_spi_eri_interrupt
 *
 * Description:
 *   Error interrupt handler
 *
 ****************************************************************************/

static int rzv_spi_eri_interrupt(int irq, void *context, void *arg)
{
  struct rzv_spi_priv_s *priv = (struct rzv_spi_priv_s *)arg;
  uint32_t spsr;

  /* Read status register */
  spsr = rzv_spi_getreg32(priv, RZV_SPI_SPSR_OFFSET);

  spierr("SPI error interrupt: SPSR=0x%08lx\n", spsr);

  /* Clear error flags */
  rzv_spi_putreg32(priv, RZV_SPI_SPSRC_OFFSET, spsr & SPI_ERROR_FLAGS);

  /* Set error flag and signal completion */
  priv->error = true;
  nxsem_post(&priv->waitsem);

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_spibus_initialize
 ****************************************************************************/

struct spi_dev_s *rzv_spibus_initialize(int port)
{
  struct rzv_spi_priv_s *priv = NULL;
  int ret;

  /* Get device structure */
  switch (port)
    {
#ifdef CONFIG_RZV_SPI0
      case 0:
        priv = &g_spi0_priv;
        break;
#endif

#ifdef CONFIG_RZV_SPI1
      case 1:
        priv = &g_spi1_priv;
        break;
#endif

      default:
        return NULL;
    }

  /* Initialize semaphores */
  nxsem_init(&priv->exclsem, 0, 1);
  nxsem_init(&priv->waitsem, 0, 0);
  nxsem_set_protocol(&priv->waitsem, SEM_PRIO_NONE);

  /* Enable module clock */
  ret = rzv_clock_enable(priv->config->clk_id);
  if (ret < 0)
    {
      spierr("Failed to enable clock: %d\n", ret);
      return NULL;
    }

  /* Reset SPI - disable all functions */
  rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET, 0);

  /* Reset and clear FIFOs */
  rzv_spi_putreg32(priv, RZV_SPI_SPFCR_OFFSET, SPI_SPFCR_SPFRST);
  rzv_spi_putreg32(priv, RZV_SPI_SPFCR_OFFSET, 0);

  /* Clear all status flags */
  rzv_spi_putreg32(priv, RZV_SPI_SPSRC_OFFSET, 0xFD800000);

  /* Configure SPDCR - Data Control Register */
  rzv_spi_putreg32(priv, RZV_SPI_SPDCR_OFFSET, 0);

  /* Configure SPDCR2 - FIFO trigger levels */
  rzv_spi_putreg32(priv, RZV_SPI_SPDCR2_OFFSET,
                  (1 << SPI_SPDCR2_TTRG_SHIFT) |  /* TX trigger = 1 */
                  (1 << SPI_SPDCR2_RTRG_SHIFT));  /* RX trigger = 1 */

  /* Configure SPDECR - Delay Control Register */
  rzv_spi_putreg32(priv, RZV_SPI_SPDECR_OFFSET,
                  (2 << SPI_SPDECR_SCKDL_SHIFT) |   /* Clock delay */
                  (2 << SPI_SPDECR_SLNDL_SHIFT) |   /* SSL negation delay */
                  (2 << SPI_SPDECR_SPNDL_SHIFT));   /* Next access delay */

  /* Configure SPCMD0 - Command register for master mode, 8-bit */
  rzv_spi_putreg32(priv, RZV_SPI_SPCMD_OFFSET(0),
                  SPI_SPCMD_SPB_8BIT);  /* 8-bit data */

  /* Set default values */
  priv->nbits = 8;
  priv->mode = SPIDEV_MODE0;
  priv->error = false;
  priv->txbuffer = NULL;
  priv->rxbuffer = NULL;
  priv->ntxwords = 0;
  priv->nrxwords = 0;

  /* Set default frequency */
  rzv_spi_setfrequency(priv, priv->config->frequency);

  /* Attach interrupt handlers using ICU */
  priv->irq_rxi = rzv_icu_attach(priv->config->elc_rxi,
                                 rzv_spi_rxi_interrupt, priv, false);
  if (priv->irq_rxi < 0)
    {
      spierr("Failed to attach RXI interrupt: %d\n", priv->irq_rxi);
      goto errout_clock;
    }

  priv->irq_txi = rzv_icu_attach(priv->config->elc_txi,
                                 rzv_spi_txi_interrupt, priv, false);
  if (priv->irq_txi < 0)
    {
      spierr("Failed to attach TXI interrupt: %d\n", priv->irq_txi);
      goto errout_rxi;
    }

  priv->irq_tei = rzv_icu_attach(priv->config->elc_tei,
                                 rzv_spi_tei_interrupt, priv, false);
  if (priv->irq_tei < 0)
    {
      spierr("Failed to attach TEI interrupt: %d\n", priv->irq_tei);
      goto errout_txi;
    }

  priv->irq_eri = rzv_icu_attach(priv->config->elc_eri,
                                 rzv_spi_eri_interrupt, priv, false);
  if (priv->irq_eri < 0)
    {
      spierr("Failed to attach ERI interrupt: %d\n", priv->irq_eri);
      goto errout_tei;
    }

  /* Enable SPI in master mode */
  rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET,
                  SPI_SPCR_SPE |        /* Enable SPI */
                  SPI_SPCR_MSTR);       /* Master mode */

  spiinfo("SPI%d initialized\n", port);
  return (struct spi_dev_s *)priv;

errout_tei:
  rzv_icu_detach(priv->irq_tei);
errout_txi:
  rzv_icu_detach(priv->irq_txi);
errout_rxi:
  rzv_icu_detach(priv->irq_rxi);
errout_clock:
  rzv_clock_disable(priv->config->clk_id);
  return NULL;
}

/****************************************************************************
 * Name: rzv_spibus_uninitialize
 *
 * Description:
 *   Uninitialize an SPI bus
 *
 ****************************************************************************/

int rzv_spibus_uninitialize(struct spi_dev_s *dev)
{
  struct rzv_spi_priv_s *priv = (struct rzv_spi_priv_s *)dev;

  if (priv == NULL)
    {
      return -EINVAL;
    }

  /* Disable SPI */
  rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET, 0);

  /* Detach interrupt handlers */
  if (priv->irq_eri >= 0)
    {
      rzv_icu_detach(priv->irq_eri);
    }

  if (priv->irq_tei >= 0)
    {
      rzv_icu_detach(priv->irq_tei);
    }

  if (priv->irq_txi >= 0)
    {
      rzv_icu_detach(priv->irq_txi);
    }

  if (priv->irq_rxi >= 0)
    {
      rzv_icu_detach(priv->irq_rxi);
    }

  /* Disable module clock */
  rzv_clock_disable(priv->config->clk_id);

  /* Destroy semaphores */
  nxsem_destroy(&priv->waitsem);
  nxsem_destroy(&priv->exclsem);

  spiinfo("SPI%d uninitialized\n", priv->config->port);

  return OK;
}