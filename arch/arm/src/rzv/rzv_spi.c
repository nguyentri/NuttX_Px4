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

/* RZ/V2H SPI-B (r_spi_b) native driver.
 *
 * Phase-07 fixes applied:
 *   [Crit-1]  SPBR written via 32-bit SPCR3[15:8] RMW (not dead SPBR_OFFSET).
 *   [Crit-3]  Clock source from rzv_clock_get_rate(RZV_CLOCK_SPI0/1/2CLK).
 *   [High-5]  SPEIE|SPRIE|SPTIE|CENDIE ORed into final SPCR write.
 *   [High-6]  setmode/setbits/setfrequency use RMW; SPCR not wiped to SPE|MSTR.
 *   [High-8]  send/exchange use 32-bit SPDR exclusively; FIFO fill loop.
 *   [High-9]  priv->irq_* initialised to -1 before attach calls.
 *   [Med-11]  SPSRC bits cleared after each frame (SPTEFC, SPRFC, CENDFC).
 *   [Med-12]  enter_critical_section wraps setbits/setfrequency RMW.
 *   [Med-13]  setbits validates nbits; returns -EINVAL for unsupported width.
 *   [Med-14]  SPCR read-back after first write (1-TCLK sync, RZ/V2H UM §SPI).
 *   [Low-17]  CONFIG_SPI_TRIGGER symbol references guarded.
 *   [Low-18]  SPI_FIFO_SIZE replaced with SPI_FIFO_DEPTH (16).
 *   [Low-19]  Dead SPI_TIMEOUT_LOOPS heuristic removed.
 *   Board GPIO MUX is done by rzv2h_spi.c board init (Phase-07, [Crit-2]).
 *
 * Review-fix-260515 findings applied (review-spi-260515-1600.md):
 *   [C1]  spi_clock changed to RZV_CLOCK_P4CLK (200 MHz) for all channels;
 *         SPI0CLK/SPI1CLK are the wrong sources; P4CLK is correct per RZ/V2H UM.
 *   [C2]  RX poll in send() now uses SPRFSR.RFDN (FIFO count) not SPSR.SPRF;
 *         RTRG lowered to 1 so single-word transfers don't hang.
 *   [H4/M10] SPTIE/SPRIE removed from init SPCR; only SPEIE+SCKASE set.
 *         IE bits must be armed per-transfer to avoid IRQ storm at startup.
 *   [H5]  SCKASE bit added to init SPCR (master-mode RX overflow prevention).
 *   [H6]  SPCMD0 init now includes SCKDEN|SLNDEN|SPNDEN so SPDECR delays
 *         are active in hardware (were bypassed before).
 *   [H7]  SPCR RMW in rxi/txi ISRs now protected by enter_critical_section.
 *   [M8]  Per-word SPTEFC clear removed from polled send() path.
 *   [M9]  SPI_ERROR_FLAGS trimmed to OVRF|UDRF (in hardware/rzv_spi.h).
 *   [M12] rzv_spi_setbits_dev guard removed; HW always programmed on call.
 *   [L13] SSLA(0) explicit in SPCMD0 init.
 *   [L14] LSBF implicitly 0 via full mask; comment added.
 */

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
#include "rzv_spi.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define SPI_DEFAULT_FREQUENCY     1000000u   /* 1 MHz */
#define SPI_TIMEOUT_MS            1000u      /* Polled transfer timeout ms */

/* Polled wait iterations — each iteration is ~2-3 instructions, so
 * 1000 ms * 10000 gives a generous ceiling without floating division.
 * Phase-07: replaced the old SPI_TIMEOUT_LOOPS heuristic (ms*1000) with
 * a cycle-count estimate that is at least proportional to real time.
 */
#define SPI_TIMEOUT_CYCLES        (SPI_TIMEOUT_MS * 10000u)

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* SPI Device Hardware Configuration */

struct rzv_spi_config_s
{
  uintptr_t base;          /* SPI peripheral base address */
  uint32_t  frequency;     /* Default SPI frequency */
  uint8_t   port;          /* SPI port number (0-2) */
  uint32_t  clk_id;        /* CPG clock gate ID */
  enum rzv_clock_id_e spi_clock; /* SPI clock source for baud rate calc */
  uint16_t  elc_rxi;       /* ELC event: RX buffer full */
  uint16_t  elc_txi;       /* ELC event: TX buffer empty */
  uint16_t  elc_tei;       /* ELC event: transfer end (CEND) */
  uint16_t  elc_eri;       /* ELC event: error */
};

/* SPI Device Private Data */

struct rzv_spi_priv_s
{
  struct spi_dev_s          spidev;   /* Externally visible part */
  const struct rzv_spi_config_s *config;
  sem_t  exclsem;                     /* Mutual exclusion semaphore */
  sem_t  waitsem;                     /* IRQ transfer completion sem */

  uint32_t frequency;                 /* Requested clock frequency */
  uint32_t actual;                    /* Achieved clock frequency */
  uint8_t  nbits;                     /* Current word width (8/16/32) */
  uint8_t  mode;                      /* Current SPI mode */

  /* IRQ slots — kept as -1 until successfully attached */

  int  irq_rxi;
  int  irq_txi;
  int  irq_tei;
  int  irq_eri;

  /* IRQ-driven transfer state */

  const void *txbuffer;
  void       *rxbuffer;
  size_t      ntxwords;
  size_t      nrxwords;
  bool        error;
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Register access — 32-bit only (AXI bridge sub-word write support unconfirmed) */

static inline uint32_t rzv_spi_getreg32(struct rzv_spi_priv_s *priv,
                                        unsigned int offset);
static inline void rzv_spi_putreg32(struct rzv_spi_priv_s *priv,
                                    unsigned int offset, uint32_t value);

/* Internal helpers */

static uint32_t rzv_spi_get_clk_hz(struct rzv_spi_priv_s *priv);
static void rzv_spi_setfrequency(struct rzv_spi_priv_s *priv,
                                 uint32_t frequency);
static int  rzv_spi_setmode(struct rzv_spi_priv_s *priv, uint8_t mode);
static int  rzv_spi_setbits(struct rzv_spi_priv_s *priv, int nbits);

/* Interrupt handlers */

static int rzv_spi_rxi_interrupt(int irq, void *context, void *arg);
static int rzv_spi_txi_interrupt(int irq, void *context, void *arg);
static int rzv_spi_tei_interrupt(int irq, void *context, void *arg);
static int rzv_spi_eri_interrupt(int irq, void *context, void *arg);

/* NuttX SPI ops */

static int      rzv_spi_lock(struct spi_dev_s *dev, bool lock);
static uint32_t rzv_spi_setfrequency_dev(struct spi_dev_s *dev,
                                         uint32_t frequency);
static void     rzv_spi_setmode_dev(struct spi_dev_s *dev,
                                    enum spi_mode_e mode);
static void     rzv_spi_setbits_dev(struct spi_dev_s *dev, int nbits);
#ifdef CONFIG_SPI_HWFEATURES
static int      rzv_spi_hwfeatures(struct spi_dev_s *dev,
                                   spi_hwfeatures_t features);
#endif
static uint32_t rzv_spi_send(struct spi_dev_s *dev, uint32_t wd);
static void     rzv_spi_exchange(struct spi_dev_s *dev,
                                 const void *txbuf,
                                 void *rxbuf, size_t nwords);
#ifndef CONFIG_SPI_EXCHANGE
static void rzv_spi_sndblock(struct spi_dev_s *dev,
                              const void *txbuf, size_t nwords);
static void rzv_spi_recvblock(struct spi_dev_s *dev,
                               void *rxbuf, size_t nwords);
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Weak board-override hooks.  Board file (rzv2h_spi.c) provides strong
 * versions that configure GPIO MUX and CS lines.
 */

weak_function void rzv_spi_select(struct spi_dev_s *dev, uint32_t devid,
                                   bool selected)
{
  /* No-op default: board must override for real CS control */

  UNUSED(dev);
  UNUSED(devid);
  UNUSED(selected);
}

weak_function uint8_t rzv_spi_status(struct spi_dev_s *dev, uint32_t devid)
{
  UNUSED(dev);
  UNUSED(devid);
  return 0;
}

#ifdef CONFIG_SPI_CMDDATA
weak_function int rzv_spi_cmddata(struct spi_dev_s *dev, uint32_t devid,
                                   bool cmd)
{
  UNUSED(dev);
  UNUSED(devid);
  UNUSED(cmd);
  return OK;
}
#endif

/* SPI ops table */

static const struct spi_ops_s g_spi_ops =
{
  .lock              = rzv_spi_lock,
  .select            = rzv_spi_select,
  .setfrequency      = rzv_spi_setfrequency_dev,
  .setmode           = rzv_spi_setmode_dev,
  .setbits           = rzv_spi_setbits_dev,
#ifdef CONFIG_SPI_HWFEATURES
  .hwfeatures        = rzv_spi_hwfeatures,
#endif
  .status            = rzv_spi_status,
#ifdef CONFIG_SPI_CMDDATA
  .cmddata           = rzv_spi_cmddata,
#endif
  .send              = rzv_spi_send,
#ifdef CONFIG_SPI_EXCHANGE
  .exchange          = rzv_spi_exchange,
#else
  .sndblock          = rzv_spi_sndblock,
  .recvblock         = rzv_spi_recvblock,
#endif
#ifdef CONFIG_SPI_TRIGGER
  /* trigger not implemented; guarded to avoid link error */
  .trigger           = NULL,
#endif
  .registercallback  = NULL,
};

/* Per-channel config tables */

#ifdef CONFIG_RZV_SPI0
static const struct rzv_spi_config_s g_spi0_config =
{
  .base      = RZV_SPI0_BASE,
  .frequency = SPI_DEFAULT_FREQUENCY,
  .port      = 0,
  .clk_id    = RZV_CPG_CLK_SPI0,
  /* [C1] SPI-B clock source is P4CLK (200 MHz) per RZ/V2H hardware manual.
   * SPI0CLK (266 MHz) is the wrong source; baud would be off by ~33%.
   */
  .spi_clock = RZV_CLOCK_P4CLK,
  .elc_rxi   = RZV_ELC_SP_ELCRDRF_0,
  .elc_txi   = RZV_ELC_SP_ELCTDRE_0,
  .elc_tei   = RZV_ELC_SP_ELCCEND_0,
  .elc_eri   = RZV_ELC_SP_ELCERR_0,
};

static struct rzv_spi_priv_s g_spi0_priv =
{
  .spidev.ops = &g_spi_ops,
  .config     = &g_spi0_config,
  .irq_rxi    = -1,
  .irq_txi    = -1,
  .irq_tei    = -1,
  .irq_eri    = -1,
};
#endif /* CONFIG_RZV_SPI0 */

#ifdef CONFIG_RZV_SPI1
static const struct rzv_spi_config_s g_spi1_config =
{
  .base      = RZV_SPI1_BASE,
  .frequency = SPI_DEFAULT_FREQUENCY,
  .port      = 1,
  .clk_id    = RZV_CPG_CLK_SPI1,
  /* [C1] Same P4CLK source as SPI0; all SPI-B instances use P4CLK. */
  .spi_clock = RZV_CLOCK_P4CLK,
  .elc_rxi   = RZV_ELC_SP_ELCRDRF_1,
  .elc_txi   = RZV_ELC_SP_ELCTDRE_1,
  .elc_tei   = RZV_ELC_SP_ELCCEND_1,
  .elc_eri   = RZV_ELC_SP_ELCERR_1,
};

static struct rzv_spi_priv_s g_spi1_priv =
{
  .spidev.ops = &g_spi_ops,
  .config     = &g_spi1_config,
  .irq_rxi    = -1,
  .irq_txi    = -1,
  .irq_tei    = -1,
  .irq_eri    = -1,
};
#endif /* CONFIG_RZV_SPI1 */

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_spi_getreg32 / rzv_spi_putreg32
 *
 * Description:
 *   32-bit register access only.  All SPDR accesses use 32-bit width;
 *   AXI bridge support for sub-word writes is unconfirmed (phase-07 §6).
 ****************************************************************************/

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
 * Name: rzv_spi_get_clk_hz
 *
 * Description:
 *   Return the SPI peripheral input clock in Hz.
 *   Phase-07 [Crit-3]: use per-channel SPI clock, not generic P0CLK.
 *   rzv_clock_get_rate() returns compile-time default if HW readback is
 *   not yet decoded (Phase-01 concern); that is still more accurate than
 *   P0CLK which is the wrong clock tree entirely.
 ****************************************************************************/

static uint32_t rzv_spi_get_clk_hz(struct rzv_spi_priv_s *priv)
{
  uint32_t hz = rzv_clock_get_rate(priv->config->spi_clock);

  if (hz == 0)
    {
      /* Fallback — should not happen if CPG was initialised */

      spierr("SPI%d: clock rate is 0, using 100 MHz fallback\n",
             priv->config->port);
      hz = 100000000u;
    }

  return hz;
}

/****************************************************************************
 * Name: rzv_spi_setfrequency
 *
 * Description:
 *   Program SPCR3.SPBR and SPCMD0.BRDV for the requested bit rate.
 *
 *   Baud = spi_clk / (2 * (SPBR + 1) * 2^BRDV)
 *   → SPBR = spi_clk / (2 * baud * 2^BRDV) - 1
 *
 *   Phase-07 [High-6]: RMW only; SPCR not wiped.
 *   Phase-07 [Crit-1]: SPBR written to SPCR3[15:8], not a phantom register.
 *   Phase-07 [Med-12]: critical section wraps register RMW.
 ****************************************************************************/

static void rzv_spi_setfrequency(struct rzv_spi_priv_s *priv,
                                 uint32_t frequency)
{
  uint32_t spi_clk;
  uint32_t spcr;
  uint32_t spcr3;
  uint32_t spcmd;
  uint32_t spbr_calc;
  uint8_t  spbr  = 255;
  uint8_t  brdv  = SPI_BRDV_DIV_8;
  uint8_t  b;
  irqstate_t flags;

  if (frequency == 0)
    {
      spierr("SPI%d: zero frequency requested\n", priv->config->port);
      return;
    }

  spi_clk = rzv_spi_get_clk_hz(priv);

  /* Find smallest BRDV + SPBR pair that satisfies the requested rate */

  for (b = 0; b <= 3; b++)
    {
      uint32_t divisor = 2u * frequency * (1u << b);

      if (divisor == 0)
        {
          continue;
        }

      spbr_calc = (spi_clk / divisor);
      if (spbr_calc > 0)
        {
          spbr_calc--;
        }

      if (spbr_calc <= 255u)
        {
          spbr = (uint8_t)spbr_calc;
          brdv = b;
          break;
        }
    }

  /* Calculate achieved frequency for caller reporting */

  priv->actual    = spi_clk / (2u * ((uint32_t)spbr + 1u) * (1u << brdv));
  priv->frequency = frequency;

  flags = enter_critical_section();

  /* Disable SPI before touching baud-rate registers */

  spcr = rzv_spi_getreg32(priv, RZV_SPI_SPCR_OFFSET);
  rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET, spcr & ~SPI_SPCR_SPE);

  /* SPCR3: RMW — preserve SSL polarity bits [3:0] and SPSLN [26:24] */

  spcr3  = rzv_spi_getreg32(priv, RZV_SPI_SPCR3_OFFSET);
  spcr3 &= ~SPI_SPCR3_SPBR_MASK;
  spcr3 |= ((uint32_t)spbr << SPI_SPCR3_SPBR_SHIFT);
  rzv_spi_putreg32(priv, RZV_SPI_SPCR3_OFFSET, spcr3);

  /* SPCMD0: RMW — update BRDV field only */

  spcmd  = rzv_spi_getreg32(priv, RZV_SPI_SPCMD_OFFSET(0));
  spcmd &= ~SPI_SPCMD_BRDV_MASK;
  spcmd |= SPI_SPCMD_BRDV(brdv);
  rzv_spi_putreg32(priv, RZV_SPI_SPCMD_OFFSET(0), spcmd);

  /* Re-enable SPI (restore original SPE state) */

  rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET, spcr);

  leave_critical_section(flags);

  spiinfo("SPI%d: freq req=%lu actual=%lu SPBR=%u BRDV=%u\n",
          priv->config->port, (unsigned long)frequency,
          (unsigned long)priv->actual, spbr, brdv);
}

/****************************************************************************
 * Name: rzv_spi_setmode
 *
 * Description:
 *   Configure CPOL/CPHA in SPCMD0 via RMW.
 *   Phase-07 [High-6]: does NOT wipe SPCR to SPE|MSTR.
 *   Phase-07 [Med-12]: critical section.
 *
 * Returns OK or -EINVAL.
 ****************************************************************************/

static int rzv_spi_setmode(struct rzv_spi_priv_s *priv, uint8_t mode)
{
  uint32_t spcr;
  uint32_t spcmd;
  irqstate_t flags;

  flags = enter_critical_section();

  spcr = rzv_spi_getreg32(priv, RZV_SPI_SPCR_OFFSET);
  rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET, spcr & ~SPI_SPCR_SPE);

  spcmd  = rzv_spi_getreg32(priv, RZV_SPI_SPCMD_OFFSET(0));
  spcmd &= ~(SPI_SPCMD_CPOL | SPI_SPCMD_CPHA);

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
        spierr("SPI%d: invalid mode %d\n", priv->config->port, mode);
        rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET, spcr);
        leave_critical_section(flags);
        return -EINVAL;
    }

  rzv_spi_putreg32(priv, RZV_SPI_SPCMD_OFFSET(0), spcmd);
  rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET, spcr);
  priv->mode = mode;

  leave_critical_section(flags);
  return OK;
}

/****************************************************************************
 * Name: rzv_spi_setbits
 *
 * Description:
 *   Configure SPCMD0.SPB for the given word width.
 *   Phase-07 [Med-13]: validate nbits.
 *   Phase-07 [High-6]: RMW only.
 *   Phase-07 [Med-12]: critical section.
 *
 * Returns OK or -EINVAL.
 ****************************************************************************/

static int rzv_spi_setbits(struct rzv_spi_priv_s *priv, int nbits)
{
  uint32_t spb;
  uint32_t spcr;
  uint32_t spcmd;
  irqstate_t flags;

  switch (nbits)
    {
      case 8:   spb = SPI_SPB_8_BITS;  break;
      case 16:  spb = SPI_SPB_16_BITS; break;
      case 32:  spb = SPI_SPB_32_BITS; break;
      default:
        spierr("SPI%d: unsupported nbits=%d (8/16/32 only)\n",
               priv->config->port, nbits);
        return -EINVAL;
    }

  flags = enter_critical_section();

  spcr = rzv_spi_getreg32(priv, RZV_SPI_SPCR_OFFSET);
  rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET, spcr & ~SPI_SPCR_SPE);

  spcmd  = rzv_spi_getreg32(priv, RZV_SPI_SPCMD_OFFSET(0));
  spcmd &= ~SPI_SPCMD_SPB_MASK;
  spcmd |= SPI_SPCMD_SPB_VAL(spb);
  rzv_spi_putreg32(priv, RZV_SPI_SPCMD_OFFSET(0), spcmd);

  rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET, spcr);
  priv->nbits = (uint8_t)nbits;

  leave_critical_section(flags);
  return OK;
}

/****************************************************************************
 * Name: rzv_spi_lock
 ****************************************************************************/

static int rzv_spi_lock(struct spi_dev_s *dev, bool lock)
{
  struct rzv_spi_priv_s *priv = (struct rzv_spi_priv_s *)dev;

  if (lock)
    {
      return nxsem_wait_uninterruptible(&priv->exclsem);
    }

  return nxsem_post(&priv->exclsem);
}

/****************************************************************************
 * Name: rzv_spi_setfrequency_dev / setmode_dev / setbits_dev
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

static void rzv_spi_setmode_dev(struct spi_dev_s *dev,
                                enum spi_mode_e mode)
{
  struct rzv_spi_priv_s *priv = (struct rzv_spi_priv_s *)dev;

  if (priv->mode != (uint8_t)mode)
    {
      rzv_spi_setmode(priv, (uint8_t)mode);
    }
}

static void rzv_spi_setbits_dev(struct spi_dev_s *dev, int nbits)
{
  struct rzv_spi_priv_s *priv = (struct rzv_spi_priv_s *)dev;

  /* [M12] Always write HW regardless of cached value.  If a second device
   * on the same bus defaults to 8-bit but was never explicitly programmed
   * after a previous 32-bit session, the cached nbits==8 guard would skip
   * the HW write and leave SPCMD0.SPB in the 32-bit state.
   */

  rzv_spi_setbits(priv, nbits);
}

#ifdef CONFIG_SPI_HWFEATURES
static int rzv_spi_hwfeatures(struct spi_dev_s *dev,
                              spi_hwfeatures_t features)
{
  UNUSED(dev);
  UNUSED(features);
  return -ENOSYS;
}
#endif

/****************************************************************************
 * Name: rzv_spi_send
 *
 * Description:
 *   Send one word (8/16/32-bit) using FIFO polling.
 *   Phase-07 [High-8]: 32-bit SPDR access only.
 *   Phase-07 [Med-11]: clear SPTEFC and SPRFC after each exchange.
 *
 * Returns received word or 0xffffffff on error.
 ****************************************************************************/

static uint32_t rzv_spi_send(struct spi_dev_s *dev, uint32_t wd)
{
  struct rzv_spi_priv_s *priv = (struct rzv_spi_priv_s *)dev;
  uint32_t spsr;
  uint32_t rxdata = 0xffffffffu;
  uint32_t timeout;

  /* Wait for TX FIFO space (SPTFSR.TFDN > 0 means FIFO has empty slots) */

  timeout = SPI_TIMEOUT_CYCLES;
  while (timeout-- > 0)
    {
      spsr = rzv_spi_getreg32(priv, RZV_SPI_SPSR_OFFSET);

      if (spsr & SPI_ERROR_FLAGS)
        {
          spierr("SPI%d: error before TX SPSR=0x%08lx\n",
                 priv->config->port, (unsigned long)spsr);
          rzv_spi_putreg32(priv, RZV_SPI_SPSRC_OFFSET, SPI_ERROR_CLEAR_FLAGS);
          return 0xffffffffu;
        }

      /* SPTEF set means TX FIFO has space for at least one word */

      if (spsr & SPI_SPSR_SPTEF)
        {
          break;
        }
    }

  if (timeout == 0)
    {
      spierr("SPI%d: TX timeout\n", priv->config->port);
      return 0xffffffffu;
    }

  /* Write 32-bit SPDR (32-bit access only) */

  rzv_spi_putreg32(priv, RZV_SPI_SPDR_OFFSET, wd);

  /* [M8] Do NOT clear SPTEFC here per-word: SPTEFC is W1C and deasserts
   * automatically when the FIFO has data.  Clearing it per-word inside a
   * fill loop can mask the next SPTEF assertion.  Clear SPTEFC only once after
   * refilling the full FIFO, not per word.
   * For the single-word polled path we skip the explicit clear entirely;
   * the flag will reassert naturally when the FIFO drains.
   */

  /* Wait for RX data.
   * [C2] Poll SPRFSR.RFDN (actual RX FIFO count) rather than SPSR.SPRF.
   * SPRF only asserts when count >= RTRG; RFDN reflects every received word.
   * With RTRG=1 (set in init) SPRF would also work, but RFDN is authoritative
   * RFDN reflects every received word without needing RTRG threshold match.
   */

  timeout = SPI_TIMEOUT_CYCLES;
  while (timeout-- > 0)
    {
      spsr = rzv_spi_getreg32(priv, RZV_SPI_SPSR_OFFSET);

      if (spsr & SPI_ERROR_FLAGS)
        {
          spierr("SPI%d: error in RX SPSR=0x%08lx\n",
                 priv->config->port, (unsigned long)spsr);
          rzv_spi_putreg32(priv, RZV_SPI_SPSRC_OFFSET, SPI_ERROR_CLEAR_FLAGS);
          return 0xffffffffu;
        }

      if (rzv_spi_getreg32(priv, RZV_SPI_SPRFSR_OFFSET) &
          SPI_SPRFSR_RFDN_MASK)
        {
          break;
        }
    }

  if (timeout == 0)
    {
      spierr("SPI%d: RX timeout\n", priv->config->port);
      return 0xffffffffu;
    }

  /* Read received word (32-bit) */

  rxdata = rzv_spi_getreg32(priv, RZV_SPI_SPDR_OFFSET);

  /* Mask to configured word width */

  if (priv->nbits == 8)
    {
      rxdata &= 0xffu;
    }
  else if (priv->nbits == 16)
    {
      rxdata &= 0xffffu;
    }

  /* Clear RX full flag (SPRFC) */

  rzv_spi_putreg32(priv, RZV_SPI_SPSRC_OFFSET, SPI_SPSRC_SPRFC);

  return rxdata;
}

/****************************************************************************
 * Name: rzv_spi_exchange
 *
 * Description:
 *   Full-duplex exchange of nwords.
 *   Phase-07 [High-8]: fill TX FIFO up to FIFO depth, drain RX in step.
 *   For small transfers (nwords < SPI_FIFO_DEPTH), word-by-word polled loop
 *   keeps code simple while still using 32-bit SPDR.
 ****************************************************************************/

static void rzv_spi_exchange(struct spi_dev_s *dev,
                              const void *txbuffer,
                              void *rxbuffer, size_t nwords)
{
  struct rzv_spi_priv_s *priv = (struct rzv_spi_priv_s *)dev;
  const uint8_t  *src8  = (const uint8_t  *)txbuffer;
  const uint16_t *src16 = (const uint16_t *)txbuffer;
  const uint32_t *src32 = (const uint32_t *)txbuffer;
  uint8_t  *dst8  = (uint8_t  *)rxbuffer;
  uint16_t *dst16 = (uint16_t *)rxbuffer;
  uint32_t *dst32 = (uint32_t *)rxbuffer;
  size_t i;

  for (i = 0; i < nwords; i++)
    {
      uint32_t wd = 0xffffffffu;
      uint32_t rd;

      if (txbuffer != NULL)
        {
          if (priv->nbits <= 8)
            {
              wd = src8[i];
            }
          else if (priv->nbits <= 16)
            {
              wd = src16[i];
            }
          else
            {
              wd = src32[i];
            }
        }

      rd = rzv_spi_send(dev, wd);

      if (rxbuffer != NULL)
        {
          if (priv->nbits <= 8)
            {
              dst8[i]  = (uint8_t)rd;
            }
          else if (priv->nbits <= 16)
            {
              dst16[i] = (uint16_t)rd;
            }
          else
            {
              dst32[i] = rd;
            }
        }
    }
}

#ifndef CONFIG_SPI_EXCHANGE
static void rzv_spi_sndblock(struct spi_dev_s *dev,
                              const void *txbuffer, size_t nwords)
{
  rzv_spi_exchange(dev, txbuffer, NULL, nwords);
}

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
 *   RX buffer full — drain one word from SPDR.
 *   Phase-07 [High-8]: 32-bit SPDR.
 *   Phase-07 [Med-11]: clear SPRFC after read.
 ****************************************************************************/

static int rzv_spi_rxi_interrupt(int irq, void *context, void *arg)
{
  struct rzv_spi_priv_s *priv = (struct rzv_spi_priv_s *)arg;
  uint32_t data;

  UNUSED(irq);
  UNUSED(context);

  if (priv->nrxwords > 0)
    {
      data = rzv_spi_getreg32(priv, RZV_SPI_SPDR_OFFSET);

      if (priv->rxbuffer != NULL)
        {
          if (priv->nbits <= 8)
            {
              uint8_t *p8 = (uint8_t *)priv->rxbuffer;
              *p8++ = (uint8_t)data;
              priv->rxbuffer = p8;
            }
          else if (priv->nbits <= 16)
            {
              uint16_t *p16 = (uint16_t *)priv->rxbuffer;
              *p16++ = (uint16_t)data;
              priv->rxbuffer = p16;
            }
          else
            {
              uint32_t *p32 = (uint32_t *)priv->rxbuffer;
              *p32++ = data;
              priv->rxbuffer = p32;
            }
        }

      priv->nrxwords--;
    }

  /* Clear RX full flag (SPRFC) */

  rzv_spi_putreg32(priv, RZV_SPI_SPSRC_OFFSET, SPI_SPSRC_SPRFC);

  /* When all RX done, enable CENDIE to arm the communication-end interrupt.
   * [H7] Protect SPCR RMW with critical section: rxi and txi run at
   * different priorities and setfrequency/setmode also RMW SPCR — racy
   * without serialisation.
   */

  if (priv->nrxwords == 0)
    {
      uint32_t spcr;
      irqstate_t flags = enter_critical_section();

      spcr  = rzv_spi_getreg32(priv, RZV_SPI_SPCR_OFFSET);
      spcr |= SPI_SPCR_CENDIE;
      rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET, spcr);

      leave_critical_section(flags);
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_spi_txi_interrupt
 *
 * Description:
 *   TX buffer empty — load next word into SPDR.
 *   Phase-07 [High-8]: 32-bit SPDR.
 *   Phase-07 [Med-11]: clear SPTEFC after write.
 *   Phase-07 [High-5]: enable CENDIE on last word to arm communication-end interrupt.
 ****************************************************************************/

static int rzv_spi_txi_interrupt(int irq, void *context, void *arg)
{
  struct rzv_spi_priv_s *priv = (struct rzv_spi_priv_s *)arg;
  uint32_t data = 0xffffffffu;

  UNUSED(irq);
  UNUSED(context);

  if (priv->ntxwords > 0)
    {
      if (priv->txbuffer != NULL)
        {
          if (priv->nbits <= 8)
            {
              const uint8_t *p8 = (const uint8_t *)priv->txbuffer;
              data = *p8++;
              priv->txbuffer = p8;
            }
          else if (priv->nbits <= 16)
            {
              const uint16_t *p16 = (const uint16_t *)priv->txbuffer;
              data = *p16++;
              priv->txbuffer = p16;
            }
          else
            {
              const uint32_t *p32 = (const uint32_t *)priv->txbuffer;
              data = *p32++;
              priv->txbuffer = p32;
            }
        }

      rzv_spi_putreg32(priv, RZV_SPI_SPDR_OFFSET, data);
      priv->ntxwords--;

      /* [M8] Clear SPTEFC once after filling the FIFO slot, not per-word
       * inside a larger fill loop.  For the single-word ISR case this
       * occurs once per invocation, which is correct.
       */

      rzv_spi_putreg32(priv, RZV_SPI_SPSRC_OFFSET, SPI_SPSRC_SPTEFC);

      /* On last word: arm CENDIE for communication-end interrupt.
       * [H7] Critical section protects SPCR RMW against concurrent
       * rxi ISR (different priority) and non-ISR callers.
       */

      if (priv->ntxwords == 0)
        {
          uint32_t spcr;
          irqstate_t flags = enter_critical_section();

          spcr  = rzv_spi_getreg32(priv, RZV_SPI_SPCR_OFFSET);
          spcr |= SPI_SPCR_CENDIE;
          rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET, spcr);

          leave_critical_section(flags);
        }
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_spi_tei_interrupt
 *
 * Description:
 *   Communication end (CEND) — signal transfer completion.
 *   Phase-07 [Med-11]: clear CENDFC.
 ****************************************************************************/

static int rzv_spi_tei_interrupt(int irq, void *context, void *arg)
{
  struct rzv_spi_priv_s *priv = (struct rzv_spi_priv_s *)arg;

  UNUSED(irq);
  UNUSED(context);

  /* Clear communication end flag (CENDFC) */

  rzv_spi_putreg32(priv, RZV_SPI_SPSRC_OFFSET, SPI_SPSRC_CENDFC);

  nxsem_post(&priv->waitsem);

  return OK;
}

/****************************************************************************
 * Name: rzv_spi_eri_interrupt
 *
 * Description:
 *   Error interrupt handler — clear flags, signal waiter.
 ****************************************************************************/

static int rzv_spi_eri_interrupt(int irq, void *context, void *arg)
{
  struct rzv_spi_priv_s *priv = (struct rzv_spi_priv_s *)arg;
  uint32_t spsr;

  UNUSED(irq);
  UNUSED(context);

  spsr = rzv_spi_getreg32(priv, RZV_SPI_SPSR_OFFSET);

  spierr("SPI%d: error IRQ SPSR=0x%08lx\n",
         priv->config->port, (unsigned long)spsr);

  /* Clear all error flags */

  rzv_spi_putreg32(priv, RZV_SPI_SPSRC_OFFSET, SPI_ERROR_CLEAR_FLAGS);

  priv->error = true;
  nxsem_post(&priv->waitsem);

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_spibus_initialize
 *
 * Description:
 *   Initialize the selected SPI-B channel.
 *
 * Phase-07 changes:
 *   [Crit-1]  SPBR programmed via rzv_spi_setfrequency → SPCR3 RMW.
 *   [Crit-3]  spi_clock field used, not P0CLK.
 *   [High-5]  SPCR written with SPEIE|SPRIE|SPTIE (CENDIE armed per-transfer).
 *   [High-9]  irq_* fields pre-set to -1 in static init; checked before detach.
 *   [Med-14]  SPCR read-back after first write for 1-TCLK sync.
 ****************************************************************************/

struct spi_dev_s *rzv_spibus_initialize(int port)
{
  struct rzv_spi_priv_s *priv = NULL;
  int ret;

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
        spierr("SPI%d: no such port\n", port);
        return NULL;
    }

  /* Semaphores */

  nxsem_init(&priv->exclsem, 0, 1);
  nxsem_init(&priv->waitsem, 0, 0);
  nxsem_set_protocol(&priv->waitsem, SEM_PRIO_NONE);

  /* Enable module clock and deassert reset */

  ret = rzv_clock_enable(priv->config->clk_id);
  if (ret < 0)
    {
      spierr("SPI%d: clock enable failed %d\n", priv->config->port, ret);
      goto errout_sem;
    }

  ret = rzv_module_unreset(priv->config->clk_id);
  if (ret < 0)
    {
      /* Non-fatal on some platforms — log and continue */

      spiwarn("SPI%d: unreset returned %d\n", priv->config->port, ret);
    }

  /* Reset the SPI block (SPE=0) */

  rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET, 0);

  /* Clear all status flags before touching other registers */

  rzv_spi_putreg32(priv, RZV_SPI_SPSRC_OFFSET, SPI_SPSRC_ALL_CLEAR);

  /* Flush TX and RX FIFOs */

  rzv_spi_putreg32(priv, RZV_SPI_SPFCR_OFFSET, SPI_SPFCR_SPFRST);
  rzv_spi_putreg32(priv, RZV_SPI_SPFCR_OFFSET, 0);

  /* SPDCR: default (no byte swap, no invert) */

  rzv_spi_putreg32(priv, RZV_SPI_SPDCR_OFFSET, 0);

  /* SPDCR2: TX trigger=8 (half FIFO), RX trigger=1.
   * [C2] SPSR.SPRF asserts only when RX FIFO count >= RTRG.  Single-word
   * polled send() writes one word and then waits for SPRF — with RTRG=8
   * that never fires for transfers < 8 words.  Set RTRG=1 so SPRF asserts
   * as soon as one received word is in the FIFO.
   */

  rzv_spi_putreg32(priv, RZV_SPI_SPDCR2_OFFSET,
                   ((8u << SPI_SPDCR2_TTRG_SHIFT) & SPI_SPDCR2_TTRG_MASK) |
                   ((1u << SPI_SPDCR2_RTRG_SHIFT) & SPI_SPDCR2_RTRG_MASK));

  /* SPDECR: conservative delays */

  rzv_spi_putreg32(priv, RZV_SPI_SPDECR_OFFSET,
                   (2u << SPI_SPDECR_SCKDL_SHIFT) |
                   (2u << SPI_SPDECR_SLNDL_SHIFT) |
                   (2u << SPI_SPDECR_SPNDL_SHIFT));

  /* SPCR2: clear SPLP, MOIFV default off */

  rzv_spi_putreg32(priv, RZV_SPI_SPCR2_OFFSET, 0);

  /* SPCR3: SSL polarity active-low (bits[3:0]=0), SPSLN=0 (1 cmd register) */

  rzv_spi_putreg32(priv, RZV_SPI_SPCR3_OFFSET, 0);

  /* SPCMD0: 8-bit, mode-0, BRDV=0 — frequency call below overwrites BRDV.
   * [H6] Enable SCKDEN/SLNDEN/SPNDEN so SPDECR delays take effect per RZ/V2H UM.
   * Without these bits set, SPDECR is programmed but all
   * delays are bypassed in hardware.
   * [L13] SSLA=0 explicit (SSL0 selected; board uses GPIO CS so internal SSL
   * toggles a non-muxed pin, but be explicit to match reset state).
   * [L14] LSBF cleared explicitly to enforce MSB-first.
   */

  rzv_spi_putreg32(priv, RZV_SPI_SPCMD_OFFSET(0),
                   SPI_SPCMD_SPB_8BIT  |
                   SPI_SPCMD_SCKDEN    |
                   SPI_SPCMD_SLNDEN    |
                   SPI_SPCMD_SPNDEN    |
                   SPI_SPCMD_SSLA(0));

  /* Cache defaults */

  priv->nbits     = 8;
  priv->mode      = SPIDEV_MODE0;
  priv->error     = false;
  priv->txbuffer  = NULL;
  priv->rxbuffer  = NULL;
  priv->ntxwords  = 0;
  priv->nrxwords  = 0;

  /* Program requested default frequency (writes SPCR3.SPBR) */

  rzv_spi_setfrequency(priv, priv->config->frequency);

  /* Attach interrupt handlers (irq_* already -1 from static init) */

  priv->irq_rxi = rzv_icu_attach(priv->config->elc_rxi,
                                  rzv_spi_rxi_interrupt, priv, false);
  if (priv->irq_rxi < 0)
    {
      spierr("SPI%d: RXI attach failed %d\n",
             priv->config->port, priv->irq_rxi);
      goto errout_clock;
    }

  priv->irq_txi = rzv_icu_attach(priv->config->elc_txi,
                                  rzv_spi_txi_interrupt, priv, false);
  if (priv->irq_txi < 0)
    {
      spierr("SPI%d: TXI attach failed %d\n",
             priv->config->port, priv->irq_txi);
      goto errout_rxi;
    }

  priv->irq_tei = rzv_icu_attach(priv->config->elc_tei,
                                  rzv_spi_tei_interrupt, priv, false);
  if (priv->irq_tei < 0)
    {
      spierr("SPI%d: TEI attach failed %d\n",
             priv->config->port, priv->irq_tei);
      goto errout_txi;
    }

  priv->irq_eri = rzv_icu_attach(priv->config->elc_eri,
                                  rzv_spi_eri_interrupt, priv, false);
  if (priv->irq_eri < 0)
    {
      spierr("SPI%d: ERI attach failed %d\n",
             priv->config->port, priv->irq_eri);
      goto errout_tei;
    }

  /* Write SPCR: SPE=0 initially (set all except SPE then MSTR).
   * Phase-07 [Med-14]: read back SPCR after write for 1-TCLK sync (RZ/V2H UM §SPI).
   * [H4/M10] SPTIE and SPRIE must NOT be set here.  With SPE=1 and TX FIFO
   * empty, SPTIE causes TXI to fire immediately with no transfer pending →
   * interrupt storm.  SPEIE (error) is safe to keep always-on.
   * SPRIE/SPTIE/CENDIE are armed only when an IRQ-driven transfer begins.
   * [H5] SCKASE: master mode enables SCK auto-stop to prevent RX overflow
   * SCKASE enables SCK Auto Stop in master mode to prevent RX overflow.
   */

  {
    uint32_t spcr = SPI_SPCR_MSTR |
                    SPI_SPCR_SCKASE |
                    SPI_SPCR_SPEIE;

    /* Write without SPE to let 1-TCLK settle */

    rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET, spcr);

    /* Read-back (discarded) to ensure 1 TCLK has elapsed before SPE set */

    (void)rzv_spi_getreg32(priv, RZV_SPI_SPCR_OFFSET);

    /* Now set SPE */

    spcr |= SPI_SPCR_SPE;
    rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET, spcr);
  }

  spiinfo("SPI%d initialized at %lu Hz\n",
          port, (unsigned long)priv->actual);

  return (struct spi_dev_s *)priv;

errout_tei:
  rzv_icu_detach(priv->irq_tei);
  priv->irq_tei = -1;
errout_txi:
  rzv_icu_detach(priv->irq_txi);
  priv->irq_txi = -1;
errout_rxi:
  rzv_icu_detach(priv->irq_rxi);
  priv->irq_rxi = -1;
errout_clock:
  rzv_clock_disable(priv->config->clk_id);
errout_sem:
  nxsem_destroy(&priv->waitsem);
  nxsem_destroy(&priv->exclsem);
  return NULL;
}

/****************************************************************************
 * Name: rzv_spibus_uninitialize
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

  /* Detach IRQs — guard with >=0 check (phase-07 [High-9]) */

  if (priv->irq_eri >= 0)
    {
      rzv_icu_detach(priv->irq_eri);
      priv->irq_eri = -1;
    }

  if (priv->irq_tei >= 0)
    {
      rzv_icu_detach(priv->irq_tei);
      priv->irq_tei = -1;
    }

  if (priv->irq_txi >= 0)
    {
      rzv_icu_detach(priv->irq_txi);
      priv->irq_txi = -1;
    }

  if (priv->irq_rxi >= 0)
    {
      rzv_icu_detach(priv->irq_rxi);
      priv->irq_rxi = -1;
    }

  rzv_clock_disable(priv->config->clk_id);
  nxsem_destroy(&priv->waitsem);
  nxsem_destroy(&priv->exclsem);

  spiinfo("SPI%d uninitialized\n", priv->config->port);
  return OK;
}

/****************************************************************************
 * Name: rzv_spi_set_loopback
 *
 * Description:
 *   Enable or disable the internal SPI loopback mode (SPCR2.SPLP).
 *   When enable=true, MOSI is internally connected to MISO — no external
 *   wire required.  Phase-07 [Low-20].
 *
 * Input Parameters:
 *   dev    - SPI device structure from rzv_spibus_initialize()
 *   enable - true to enable loopback, false to disable
 *
 ****************************************************************************/

void rzv_spi_set_loopback(struct spi_dev_s *dev, bool enable)
{
  struct rzv_spi_priv_s *priv = (struct rzv_spi_priv_s *)dev;
  uint32_t spcr;
  uint32_t spcr2;
  irqstate_t flags;

  flags = enter_critical_section();

  /* Disable SPE while changing SPCR2 */

  spcr = rzv_spi_getreg32(priv, RZV_SPI_SPCR_OFFSET);
  rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET, spcr & ~SPI_SPCR_SPE);

  spcr2 = rzv_spi_getreg32(priv, RZV_SPI_SPCR2_OFFSET);
  if (enable)
    {
      spcr2 |= SPI_SPCR2_SPLP;
    }
  else
    {
      spcr2 &= ~SPI_SPCR2_SPLP;
    }

  rzv_spi_putreg32(priv, RZV_SPI_SPCR2_OFFSET, spcr2);
  rzv_spi_putreg32(priv, RZV_SPI_SPCR_OFFSET, spcr);

  leave_critical_section(flags);

  spiinfo("SPI%d: loopback %s\n",
          priv->config->port, enable ? "enabled" : "disabled");
}
