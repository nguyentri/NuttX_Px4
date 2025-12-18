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
#include "hardware/rzv_memorymap.h"
#include "hardware/rzv_spi.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Default values ***********************************************************/

#define SPI_DEFAULT_FREQUENCY     1000000   /* 1 MHz */
#define SPI_FIFO_SIZE             4         /* FIFO depth */

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* SPI Device Hardware Configuration */

struct rzv_spi_config_s
{
  uintptr_t base;         /* SPI base address */
  uint32_t  frequency;    /* Default SPI frequency */
  uint8_t   port;         /* SPI port number (0-2) */
  uint8_t   irq_rxi;      /* Receive interrupt */
  uint8_t   irq_txi;      /* Transmit interrupt */
  uint8_t   irq_tei;      /* Transmit end interrupt */
  uint8_t   irq_eri;      /* Error interrupt */
};

/* SPI Device Private Data */

struct rzv_spi_priv_s
{
  struct spi_dev_s spidev;            /* Externally visible part */
  const struct rzv_spi_config_s *config; /* Port configuration */
  sem_t exclsem;                      /* Mutual exclusion semaphore */

  uint32_t frequency;                 /* Requested clock frequency */
  uint32_t actual;                    /* Actual clock frequency */
  uint8_t  nbits;                     /* Width of word in bits (8 or 16) */
  uint8_t  mode;                      /* SPI mode */
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
  .irq_rxi   = 0,  /* To be configured */
  .irq_txi   = 0,
  .irq_tei   = 0,
  .irq_eri   = 0,
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
  .irq_rxi   = 0,
  .irq_txi   = 0,
  .irq_tei   = 0,
  .irq_eri   = 0,
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

  /* Calculate bit rate
   * Bit rate = PCLK / (2 * (SPBR + 1) * 2^BRDV)
   */

  for (brdv = 0; brdv <= 3; brdv++)
    {
      divisor = frequency * 2 * (1 << brdv);
      spbr = (pclk / divisor) - 1;

      if (spbr <= 255)
        {
          break;
        }
    }

  if (brdv > 3)
    {
      brdv = 3;
      spbr = 255;
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
  uint16_t spcmd;

  /* Disable SPI (SPCR is 32-bit) */
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
        return;
    }

  /* Write command register (32-bit) */
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
  uint16_t spcmd;

  /* Disable SPI (SPCR is 32-bit) */
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
  uint32_t rxdata;

  /* Wait for TX buffer empty */
  while ((rzv_spi_getreg8(priv, RZV_SPI_SPSR_OFFSET) &
          SPI_SPSR_SPTEF) == 0);

  /* Write data */
  if (priv->nbits == 8)
    {
      rzv_spi_putreg8(priv, RZV_SPI_SPDR_OFFSET, (uint8_t)wd);
    }
  else
    {
      rzv_spi_putreg16(priv, RZV_SPI_SPDR_OFFSET, (uint16_t)wd);
    }

  /* Wait for RX data full */
  while ((rzv_spi_getreg8(priv, RZV_SPI_SPSR_OFFSET) &
          SPI_SPSR_SPRF) == 0);

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
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_spibus_initialize
 ****************************************************************************/

struct spi_dev_s *rzv_spibus_initialize(int port)
{
  struct rzv_spi_priv_s *priv = NULL;

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

  /* Initialize semaphore */
  nxsem_init(&priv->exclsem, 0, 1);

  /* Initialize SPI hardware */

  /* Reset SPI (SPCR/SPCMD are 32-bit registers) */
  rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET, 0);

  /* Configure as master, 8-bit mode (SPCMD is 32-bit) */
  rzv_spi_putreg32(priv, RZV_SPI_SPCMD_OFFSET(0),
                  SPI_SPCMD_SPB_8BIT);

  /* Set default values */
  priv->nbits = 8;
  priv->mode = SPIDEV_MODE0;

  /* Set default frequency */
  rzv_spi_setfrequency(priv, priv->config->frequency);

  /* Enable SPI in master mode */
  rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET,
                  SPI_SPCR_SPE | SPI_SPCR_MSTR);

  return (struct spi_dev_s *)priv;
}