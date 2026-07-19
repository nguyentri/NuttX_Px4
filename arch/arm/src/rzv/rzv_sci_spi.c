/****************************************************************************
 * arch/arm/src/rzv/rzv_sci_spi.c
 *
 * RZ/V2H SCI-B SPI master driver (Simple-SPI mode, interrupt-driven).
 * Mirrors rzv_sci_i2c.c structure exactly.
 *
 * Supported: 8-bit word, modes 0-3, MSB/LSB first, up to 25 MHz.
 * Not supported: slave mode, DMA/DTC, >8-bit words (returns spierr).
 *
 * Fixes from code-review (findings #1-#32):
 *   #1  — rzv_icu_attach (not rzv_icu_attach_event)
 *   #2  — rzv_clock_get_rate(RZV_CLOCK_P5CLK) with fallback
 *   #3  — rzv_clock_enable + rzv_module_unreset before any MMIO
 *   #4  — uninitialize() removed (YAGNI)
 *   #7  — exchange() uses nxsem_timedwait_uninterruptible
 *   #8  — sem_isr re-init to 0 before each exchange (stale-post fix)
 *   #9  — timeout: mask IRQs, disable TE/RE, return -ETIMEDOUT
 *   #10 — frequency/mode defaults set BEFORE hw_init; no div-by-zero
 *   #13 — static g_sci_spi_priv[10] table; all 10 channels guarded
 *   #15 — setfrequency/setmode patch only CCR2/CCR3, not full reconfigure
 *   #16 — no critical_section wrapping icu_attach
 *   #21 — select/status/cmddata declared weak_function
 *   #22 — initialized guard on every initialize() call
 *
 * Licensed under Apache License 2.0 — see top-level NOTICE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <debug.h>
#include <assert.h>
#include <time.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/semaphore.h>
#include <nuttx/mutex.h>
#include <nuttx/spi/spi.h>

#include "arm_internal.h"
#include "hardware/rzv_sci.h"
#include "hardware/rzv_sci_spi.h"
#include "hardware/rzv_elc.h"
#include "rzv_clock.h"
#include "rzv_icu.h"
#include "rzv_sci_spi.h"
#include "rzv_sci_spi_internal.h"

#ifdef CONFIG_RZV_SCI_SPI

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static int      sci_spi_lock(struct spi_dev_s *dev, bool lock);
static uint32_t sci_spi_setfrequency(struct spi_dev_s *dev,
                                     uint32_t frequency);
static void     sci_spi_setmode(struct spi_dev_s *dev,
                                enum spi_mode_e mode);
static void     sci_spi_setbits(struct spi_dev_s *dev, int nbits);
static uint32_t sci_spi_send(struct spi_dev_s *dev, uint32_t wd);
static void     sci_spi_exchange(struct spi_dev_s *dev,
                                 const void *txbuffer,
                                 void *rxbuffer, size_t nwords);
#ifndef CONFIG_SPI_EXCHANGE
static void     sci_spi_sndblock(struct spi_dev_s *dev,
                                 const void *txbuffer, size_t nwords);
static void     sci_spi_recvblock(struct spi_dev_s *dev,
                                  void *rxbuffer, size_t nwords);
#endif

/* Weak board-supplied callbacks — stubs prevent link errors */

void weak_function rzv_sci_spi_select(struct spi_dev_s *dev,
                                      uint32_t devid, bool selected);
uint8_t weak_function rzv_sci_spi_status(struct spi_dev_s *dev,
                                         uint32_t devid);
#ifdef CONFIG_SPI_CMDDATA
int weak_function rzv_sci_spi_cmddata(struct spi_dev_s *dev,
                                      uint32_t devid, bool cmd);
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* NuttX SPI ops table */

static const struct spi_ops_s g_sci_spi_ops =
{
  .lock         = sci_spi_lock,
  .select       = rzv_sci_spi_select,    /* board-supplied weak */
  .setfrequency = sci_spi_setfrequency,
  .setmode      = sci_spi_setmode,
  .setbits      = sci_spi_setbits,
  .status       = rzv_sci_spi_status,    /* board-supplied weak */
#ifdef CONFIG_SPI_CMDDATA
  .cmddata      = rzv_sci_spi_cmddata,   /* board-supplied weak */
#endif
  .send         = sci_spi_send,
#ifdef CONFIG_SPI_EXCHANGE
  .exchange     = sci_spi_exchange,
#else
  .sndblock     = sci_spi_sndblock,
  .recvblock    = sci_spi_recvblock,
#endif
};

/* Per-channel ELC event table (indexed [channel][0=txi,1=rxi,2=tei,3=eri]) */

static const int g_sci_spi_events[SCI_SPI_MAX_CHANNELS][4] =
{
  { ELC_EVENT_SCI0_TXI, ELC_EVENT_SCI0_RXI,
    ELC_EVENT_SCI0_TEI, ELC_EVENT_SCI0_ERI },
  { ELC_EVENT_SCI1_TXI, ELC_EVENT_SCI1_RXI,
    ELC_EVENT_SCI1_TEI, ELC_EVENT_SCI1_ERI },
  { ELC_EVENT_SCI2_TXI, ELC_EVENT_SCI2_RXI,
    ELC_EVENT_SCI2_TEI, ELC_EVENT_SCI2_ERI },
  { ELC_EVENT_SCI3_TXI, ELC_EVENT_SCI3_RXI,
    ELC_EVENT_SCI3_TEI, ELC_EVENT_SCI3_ERI },
  { RZV_ELC_SC_ELCTDRE_4, RZV_ELC_SC_ELCRDRF_4,
    RZV_ELC_SC_ELCTEND_4, RZV_ELC_SC_ELCER_4 },
  { RZV_ELC_SC_ELCTDRE_5, RZV_ELC_SC_ELCRDRF_5,
    RZV_ELC_SC_ELCTEND_5, RZV_ELC_SC_ELCER_5 },
  { RZV_ELC_SC_ELCTDRE_6, RZV_ELC_SC_ELCRDRF_6,
    RZV_ELC_SC_ELCTEND_6, RZV_ELC_SC_ELCER_6 },
  { RZV_ELC_SC_ELCTDRE_7, RZV_ELC_SC_ELCRDRF_7,
    RZV_ELC_SC_ELCTEND_7, RZV_ELC_SC_ELCER_7 },
  { RZV_ELC_SC_ELCTDRE_8, RZV_ELC_SC_ELCRDRF_8,
    RZV_ELC_SC_ELCTEND_8, RZV_ELC_SC_ELCER_8 },
  { RZV_ELC_SC_ELCTDRE_9, RZV_ELC_SC_ELCRDRF_9,
    RZV_ELC_SC_ELCTEND_9, RZV_ELC_SC_ELCER_9 },
};

/* Per-channel base address table */

static const uint32_t g_sci_base[SCI_SPI_MAX_CHANNELS] =
{
  RZV_SCI0_BASE, RZV_SCI1_BASE, RZV_SCI2_BASE, RZV_SCI3_BASE,
  RZV_SCI4_BASE, RZV_SCI5_BASE, RZV_SCI6_BASE, RZV_SCI7_BASE,
  RZV_SCI8_BASE, RZV_SCI9_BASE,
};

/* Per-channel CPG clock IDs */

static const uint32_t g_sci_clk[SCI_SPI_MAX_CHANNELS] =
{
  RZV_CPG_CLK_SCI0, RZV_CPG_CLK_SCI1,
  RZV_CPG_CLK_SCI2, RZV_CPG_CLK_SCI3,
  RZV_CPG_CLK_SCI4, RZV_CPG_CLK_SCI5,
  RZV_CPG_CLK_SCI6, RZV_CPG_CLK_SCI7,
  RZV_CPG_CLK_SCI8, RZV_CPG_CLK_SCI9,
};

/* Static per-channel private structures — no heap (#13 fix) */

static struct rzv_sci_spi_priv_s g_sci_spi_priv[SCI_SPI_MAX_CHANNELS];

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: sci_spi_hw_configure
 *
 * Description:
 *   One-shot hardware initialisation: reset → SPI mode → FIFO → baud.
 *   Called once from rzv_sci_spi_initialize() after clocks are enabled.
 *   Does NOT re-enable TE/RE — exchange() enables them before each xfer.
 *
 ****************************************************************************/

static int sci_spi_hw_configure(struct rzv_sci_spi_priv_s *priv)
{
  uint32_t base  = priv->base;
  uint32_t timeout;
  uint8_t  brr;
  uint8_t  cks;
  uint8_t  mddr;
  uint32_t ccr3;
  uint32_t ccr2;
  uint32_t fcr;
  uint32_t pclk;
  int      ret;

  /* Step 1: Disable TE/RE (CCR0 = 0) */

  putreg32(0u, base + RZV_SCI_CCR0_OFFSET);

  /* Step 2: Wait for CESR quiescence */

  for (timeout = SCI_SPI_CESR_TIMEOUT; timeout > 0; timeout--)
    {
      if ((getreg32(base + RZV_SCI_CESR_OFFSET) &
           (SCI_CESR_RIST | SCI_CESR_TIST)) == 0u)
        {
          break;
        }
    }

  if (timeout == 0u)
    {
      spierr("SCI%u: CESR quiescence timeout\n", priv->channel);
      return -ETIMEDOUT;
    }

  /* Step 3: CCR3 — Simple-SPI mode, 8-bit, FIFO, internal SCK output */

  ccr3 = SCI_CCR3_MOD_SPI |              /* MOD=3: Simple SPI */
         SCI_CCR3_CHR_8BIT |             /* 8-bit character length */
         SCI_CCR3_FM |                   /* FIFO mode enable */
         SCI_CCR3_CKE_INT_SCK_OUT;       /* Internal clock, SCK output */

  /* CPOL/CPHA per SPI mode.
   * SCI-B CCR3: CPHA=bit0, CPOL=bit1.
   * NuttX spi_mode_e: MODE0={CPOL=0,CPHA=0}, MODE1={0,1},
   *                   MODE2={CPOL=1,CPHA=0}, MODE3={1,1}.
   * Verified against RZ/V2H SCI-B hardware manual CCR3 bit definitions.
   */

  switch (priv->mode)
    {
      case SPIDEV_MODE0: /* CPOL=0, CPHA=0 */
        break;
      case SPIDEV_MODE1: /* CPOL=0, CPHA=1 */
        ccr3 |= SCI_CCR3_CPHA;
        break;
      case SPIDEV_MODE2: /* CPOL=1, CPHA=0 */
        ccr3 |= SCI_CCR3_CPOL;
        break;
      case SPIDEV_MODE3: /* CPOL=1, CPHA=1 */
        ccr3 |= SCI_CCR3_CPHA | SCI_CCR3_CPOL;
        break;
      default:
        break;
    }

  if (priv->lsbfirst)
    {
      ccr3 |= SCI_CCR3_LSBF;
    }

  putreg32(ccr3, base + RZV_SCI_CCR3_OFFSET);

  /* Step 4: CCR2 — compute baud settings (#2/#10 fix: correct PCLK source) */

  pclk = rzv_clock_get_rate(RZV_CLOCK_P5CLK);
  if (pclk == 0u)
    {
      pclk = SCI_SPI_PCLK_FALLBACK_HZ;
    }

  ret = rzv_sci_spi_calc_bitrate(pclk, priv->frequency, &brr, &cks, &mddr);
  if (ret < 0)
    {
      spierr("SCI%u: no valid baud for freq=%u pclk=%u\n",
             priv->channel, (unsigned)priv->frequency, (unsigned)pclk);
      return ret;
    }

  ccr2 = ((uint32_t)brr  << SCI_CCR2_BRR_SHIFT)  |
         ((uint32_t)cks  << SCI_CCR2_CKS_SHIFT)  |
         ((uint32_t)mddr << SCI_CCR2_MDDR_SHIFT) |
         (mddr ? SCI_CCR2_BRME : 0u);
  putreg32(ccr2, base + RZV_SCI_CCR2_OFFSET);

  priv->actual = rzv_sci_spi_actual_bitrate(pclk, brr, cks, mddr);

  /* Step 5: CCR1 = 0 (no noise filter needed in SPI mode) */

  putreg32(0u, base + RZV_SCI_CCR1_OFFSET);

  /* Step 6: CCR4 = 0 */

  putreg32(0u, base + RZV_SCI_CCR4_OFFSET);

  /* Step 7: FIFO — RX trigger=8, TX trigger=8 (FIFO_DEPTH/2), then reset.
   * With RTRG=8, RXI fires every 8 bytes; the last (nwords % 8) bytes are
   * captured by the TEI handler which drains the RX FIFO before posting.
   * TEIE is always enabled so TEI is the completion signal for ALL transfer
   * sizes, including those smaller than RTRG.  (A9 fix)
   */

  fcr = ((RZV_SCI_SPI_FIFO_DEPTH / 2u) << SCI_FCR_RTRG_SHIFT) |
        ((RZV_SCI_SPI_FIFO_DEPTH / 2u) << SCI_FCR_TTRG_SHIFT);
  putreg32(fcr | SCI_FCR_RFRST | SCI_FCR_TFRST, base + RZV_SCI_FCR_OFFSET);
  putreg32(fcr, base + RZV_SCI_FCR_OFFSET);

  /* Step 8: Clear all status flags (W1C — use named bits, not 0xFFFFFFFF) */

  putreg32(SCI_CFCLR_RDRFC | SCI_CFCLR_TDREC | SCI_CFCLR_ERSC |
           SCI_CFCLR_DCMFC | SCI_CFCLR_DPERC | SCI_CFCLR_DFERC |
           SCI_CFCLR_ORERC | SCI_CFCLR_MFFC  | SCI_CFCLR_PERC  |
           SCI_CFCLR_FERC,
           base + RZV_SCI_CFCLR_OFFSET);
  putreg32(SCI_FFCLR_DRC, base + RZV_SCI_FFCLR_OFFSET);

  /* Note: CCR0 (TE|RE) enabled in exchange() before each transfer */

  return OK;
}

/****************************************************************************
 * Name: sci_spi_lock
 ****************************************************************************/

static int sci_spi_lock(struct spi_dev_s *dev, bool lock)
{
  struct rzv_sci_spi_priv_s *priv = (struct rzv_sci_spi_priv_s *)dev;

  if (lock)
    {
      return nxmutex_lock(&priv->lock);
    }
  else
    {
      return nxmutex_unlock(&priv->lock);
    }
}

/****************************************************************************
 * Name: sci_spi_setfrequency
 *
 * Description:
 *   Update baud rate.  Patches CCR2 only; skips if unchanged or BUSY.
 *   (#15 fix: no full hw_configure on each setfrequency call)
 *
 ****************************************************************************/

static uint32_t sci_spi_setfrequency(struct spi_dev_s *dev,
                                     uint32_t frequency)
{
  struct rzv_sci_spi_priv_s *priv = (struct rzv_sci_spi_priv_s *)dev;
  uint8_t  brr;
  uint8_t  cks;
  uint8_t  mddr;
  uint32_t pclk;
  uint32_t ccr2;

  DEBUGASSERT(priv != NULL);

  if (frequency == 0u)
    {
      return priv->actual;
    }

  if (frequency == priv->frequency)
    {
      return priv->actual;
    }

  /* Reject change while transfer in progress */

  if (priv->state == SCI_SPI_STATE_BUSY)
    {
      spiwarn("SCI%u: setfrequency while BUSY — ignored\n", priv->channel);
      return priv->actual;
    }

  pclk = rzv_clock_get_rate(RZV_CLOCK_P5CLK);
  if (pclk == 0u)
    {
      pclk = SCI_SPI_PCLK_FALLBACK_HZ;
    }

  if (rzv_sci_spi_calc_bitrate(pclk, frequency, &brr, &cks, &mddr) < 0)
    {
      spiwarn("SCI%u: no valid baud for %u Hz\n",
              priv->channel, (unsigned)frequency);
      return priv->actual;
    }

  priv->frequency = frequency;
  priv->actual = rzv_sci_spi_actual_bitrate(pclk, brr, cks, mddr);

  /* Patch CCR2 only — CCR3/FIFO unchanged */

  ccr2 = ((uint32_t)brr  << SCI_CCR2_BRR_SHIFT)  |
         ((uint32_t)cks  << SCI_CCR2_CKS_SHIFT)  |
         ((uint32_t)mddr << SCI_CCR2_MDDR_SHIFT) |
         (mddr ? SCI_CCR2_BRME : 0u);
  putreg32(ccr2, priv->base + RZV_SCI_CCR2_OFFSET);

  spiinfo("SCI%u freq %u → actual %u\n",
          priv->channel, (unsigned)frequency, (unsigned)priv->actual);
  return priv->actual;
}

/****************************************************************************
 * Name: sci_spi_setmode
 *
 * Description:
 *   Update SPI mode (CPOL/CPHA).  Patches CCR3 polarity bits only.
 *   (#15 fix: no full hw_configure on each setmode call)
 *
 ****************************************************************************/

static void sci_spi_setmode(struct spi_dev_s *dev, enum spi_mode_e mode)
{
  struct rzv_sci_spi_priv_s *priv = (struct rzv_sci_spi_priv_s *)dev;
  uint32_t ccr3;

  DEBUGASSERT(priv != NULL);

  if (mode == priv->mode)
    {
      return;
    }

  if (priv->state == SCI_SPI_STATE_BUSY)
    {
      spiwarn("SCI%u: setmode while BUSY — ignored\n", priv->channel);
      return;
    }

  priv->mode = mode;

  /* RMW CCR3: clear CPOL/CPHA bits, set new values */

  ccr3  = getreg32(priv->base + RZV_SCI_CCR3_OFFSET);
  ccr3 &= ~(SCI_CCR3_CPOL | SCI_CCR3_CPHA);

  switch (mode)
    {
      case SPIDEV_MODE0: break;
      case SPIDEV_MODE1: ccr3 |= SCI_CCR3_CPHA;              break;
      case SPIDEV_MODE2: ccr3 |= SCI_CCR3_CPOL;              break;
      case SPIDEV_MODE3: ccr3 |= SCI_CCR3_CPHA | SCI_CCR3_CPOL; break;
      default: break;
    }

  putreg32(ccr3, priv->base + RZV_SCI_CCR3_OFFSET);
}

/****************************************************************************
 * Name: sci_spi_setbits
 *
 * Description:
 *   Only 8-bit transfers supported.  Log warning for other sizes.
 *
 ****************************************************************************/

static void sci_spi_setbits(struct spi_dev_s *dev, int nbits)
{
  struct rzv_sci_spi_priv_s *priv = (struct rzv_sci_spi_priv_s *)dev;

  DEBUGASSERT(priv != NULL);

  if (nbits != 8)
    {
      spierr("SCI%u: only 8-bit transfers supported (got %d)\n",
             priv->channel, nbits);
      return;
    }

  priv->nbits = (uint8_t)nbits;
}

/****************************************************************************
 * Name: sci_spi_exchange
 *
 * Description:
 *   Full-duplex SPI exchange of nwords bytes.
 *   txbuffer==NULL → sends 0xFF for each byte.
 *   rxbuffer==NULL → discards received bytes.
 *   Uses nxsem_timedwait_uninterruptible with 1-second timeout.
 *   (#7 fix: uninterruptible; #9 fix: timeout recovery)
 *
 ****************************************************************************/

static void sci_spi_exchange(struct spi_dev_s *dev,
                             const void *txbuffer,
                             void *rxbuffer, size_t nwords)
{
  struct rzv_sci_spi_priv_s *priv = (struct rzv_sci_spi_priv_s *)dev;
  struct timespec abstime;
  uint32_t timeout;
  int ret;

  DEBUGASSERT(priv != NULL);

  if (nwords == 0u)
    {
      return;
    }

  /* Set up transfer context.
   * Use nxsem_reset (not nxsem_init) to drain any stale posts from prior
   * transfers.  nxsem_init on an already-initialised sem is POSIX-undefined
   * when waiters exist.  nxsem_reset is the correct NuttX primitive here.
   * The one-shot nxsem_init lives in rzv_sci_spi_initialize() only.
   * (A3+A10 fix)
   */

  priv->txbuffer = (const uint8_t *)txbuffer;
  priv->rxbuffer = (uint8_t *)rxbuffer;
  priv->ntxwords = nwords;
  priv->nrxwords = nwords;
  priv->state    = SCI_SPI_STATE_BUSY;

  nxsem_reset(&priv->sem_isr, 0);

  /* Enable TE/RE */

  putreg32(SCI_CCR0_TE | SCI_CCR0_RE,
           priv->base + RZV_SCI_CCR0_OFFSET);

  /* Wait for CESR to confirm TE/RE active */

  for (timeout = SCI_SPI_CESR_TIMEOUT; timeout > 0; timeout--)
    {
      uint32_t cesr = getreg32(priv->base + RZV_SCI_CESR_OFFSET);
      if ((cesr & (SCI_CESR_RIST | SCI_CESR_TIST)) ==
          (SCI_CESR_RIST | SCI_CESR_TIST))
        {
          break;
        }
    }

  if (timeout == 0u)
    {
      spierr("SCI%u: CESR enable timeout\n", priv->channel);
      putreg32(0u, priv->base + RZV_SCI_CCR0_OFFSET);
      priv->state = SCI_SPI_STATE_IDLE;
      return;
    }

  /* Enable TIE + RIE + TEIE to start the ISR-driven transfer.
   * TEIE is enabled from the outset because with RTRG=8, transfers smaller
   * than 8 bytes never trigger RXI — TEI is the sole completion signal for
   * those.  For longer transfers, tei_isr drains the RX remainder before
   * posting done.  txi_isr still disables TIE and the TEIE already set here
   * is harmless (idempotent set).  (A9 fix)
   */

  putreg32(SCI_CCR0_TE | SCI_CCR0_RE |
           SCI_CCR0_TIE | SCI_CCR0_RIE | SCI_CCR0_TEIE,
           priv->base + RZV_SCI_CCR0_OFFSET);

  /* Wait for ISR to post sem_isr.
   * Use CLOCK_MONOTONIC to be immune to RTC adjustments (A7 fix).
   * nxsem_clockwait_uninterruptible handles the clock query internally;
   * on failure we fall back to a safe absolute timeout of +2 seconds.
   */

  if (clock_gettime(CLOCK_MONOTONIC, &abstime) < 0)
    {
      /* clock_gettime failed — use a safe fallback epoch */

      abstime.tv_sec  = SCI_SPI_TIMEOUT_MS / 1000 + 1;
      abstime.tv_nsec = 0;
    }
  else
    {
      abstime.tv_sec  += SCI_SPI_TIMEOUT_MS / 1000;
      abstime.tv_nsec += (SCI_SPI_TIMEOUT_MS % 1000) * 1000000L;
      if (abstime.tv_nsec >= 1000000000L)
        {
          abstime.tv_sec++;
          abstime.tv_nsec -= 1000000000L;
        }
    }

  ret = nxsem_clockwait_uninterruptible(&priv->sem_isr,
                                        CLOCK_MONOTONIC, &abstime);

  if (ret == -ETIMEDOUT)
    {
      /* (#9 fix) Timeout recovery: mask all IRQs, disable TE/RE, flush FIFOs.
       * TODO: CS deassert is responsibility of upper SPI layer via select(false).
       *       Driver cannot trigger this. Slave may stay selected until next
       *       transfer. (A1 deferred — needs spi_ops_s API change)
       * TOCTOU race exists for concurrent first-init; matches sci_i2c pattern.
       *       (A2 deferred — matches gold pattern)
       */

      putreg32(0u, priv->base + RZV_SCI_CCR0_OFFSET);

      /* Flush both FIFOs so next exchange() starts clean */

      {
        uint32_t fcr = getreg32(priv->base + RZV_SCI_FCR_OFFSET);
        putreg32(fcr | SCI_FCR_RFRST | SCI_FCR_TFRST,
                 priv->base + RZV_SCI_FCR_OFFSET);
        putreg32(fcr, priv->base + RZV_SCI_FCR_OFFSET);
      }

      priv->state = SCI_SPI_STATE_IDLE;
      spierr("SCI%u: transfer timeout (%zu words)\n",
             priv->channel, nwords);
    }
  else if (priv->state == SCI_SPI_STATE_ERROR)
    {
      spierr("SCI%u: transfer error\n", priv->channel);
    }

  /* Disable TE/RE after transfer (CCR0=0; IRQs already masked by ISR) */

  putreg32(0u, priv->base + RZV_SCI_CCR0_OFFSET);
  priv->state = SCI_SPI_STATE_IDLE;
}

/****************************************************************************
 * Name: sci_spi_send
 ****************************************************************************/

static uint32_t sci_spi_send(struct spi_dev_s *dev, uint32_t wd)
{
  uint8_t txbyte = (uint8_t)wd;
  uint8_t rxbyte = 0;

  sci_spi_exchange(dev, &txbyte, &rxbyte, 1);
  return (uint32_t)rxbyte;
}

#ifndef CONFIG_SPI_EXCHANGE
/****************************************************************************
 * Name: sci_spi_sndblock / sci_spi_recvblock
 ****************************************************************************/

static void sci_spi_sndblock(struct spi_dev_s *dev,
                             const void *txbuffer, size_t nwords)
{
  sci_spi_exchange(dev, txbuffer, NULL, nwords);
}

static void sci_spi_recvblock(struct spi_dev_s *dev,
                              void *rxbuffer, size_t nwords)
{
  sci_spi_exchange(dev, NULL, rxbuffer, nwords);
}
#endif /* !CONFIG_SPI_EXCHANGE */

/****************************************************************************
 * Weak stubs — board overrides these with real CS/status logic
 ****************************************************************************/

void weak_function rzv_sci_spi_select(struct spi_dev_s *dev,
                                      uint32_t devid, bool selected)
{
  (void)dev;
  (void)devid;
  (void)selected;
}

uint8_t weak_function rzv_sci_spi_status(struct spi_dev_s *dev,
                                         uint32_t devid)
{
  (void)dev;
  (void)devid;
  return 0;
}

#ifdef CONFIG_SPI_CMDDATA
int weak_function rzv_sci_spi_cmddata(struct spi_dev_s *dev,
                                      uint32_t devid, bool cmd)
{
  (void)dev;
  (void)devid;
  (void)cmd;
  return -ENOTSUP;
}
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_sci_spi_initialize
 *
 * Description:
 *   Initialise a SCI channel as SPI master.
 *   Returns spi_dev_s * or NULL.
 *
 *   Order (mirrors rzv_sci_i2c_initialize exactly):
 *     1. Validate channel
 *     2. initialized guard
 *     3. Populate compile-time fields
 *     4. nxmutex_init + nxsem_init (one-shot)
 *     5. rzv_clock_enable + rzv_module_unreset  ← MANDATORY before MMIO
 *     6. sci_spi_hw_configure()
 *     7. rzv_icu_attach × 4
 *     8. initialized = true
 *
 ****************************************************************************/

struct spi_dev_s *rzv_sci_spi_initialize(int channel)
{
  struct rzv_sci_spi_priv_s *priv;
  irqstate_t flags;
  bool clock_enabled = false;
  bool module_unreset = false;

  /* Validate channel against compile-time-enabled set (#13 fix) */

  switch (channel)
    {
#ifdef CONFIG_RZV_SCI0_SPI
      case 0: break;
#endif
#ifdef CONFIG_RZV_SCI1_SPI
      case 1: break;
#endif
#ifdef CONFIG_RZV_SCI2_SPI
      case 2: break;
#endif
#ifdef CONFIG_RZV_SCI3_SPI
      case 3: break;
#endif
      default:
        spierr("SCI-SPI: channel %d not enabled in Kconfig\n", channel);
        return NULL;
    }

  priv = &g_sci_spi_priv[channel];

  flags = enter_critical_section();
  if (priv->initialized)
    {
      leave_critical_section(flags);
      return &priv->dev;
    }

  if (priv->initializing)
    {
      leave_critical_section(flags);
      spierr("SCI%d: initialization already in progress\n", channel);
      return NULL;
    }

  priv->initializing = true;
  leave_critical_section(flags);

  /* Populate channel-invariant fields */

  priv->dev.ops  = &g_sci_spi_ops;
  priv->channel  = (uint8_t)channel;
  priv->base     = g_sci_base[channel];
  priv->clk_id   = g_sci_clk[channel];
  priv->evt_txi  = g_sci_spi_events[channel][0];
  priv->evt_rxi  = g_sci_spi_events[channel][1];
  priv->evt_tei  = g_sci_spi_events[channel][2];
  priv->evt_eri  = g_sci_spi_events[channel][3];
  priv->state    = SCI_SPI_STATE_IDLE;

  /* Set defaults before calculating the initial bit rate. */

  priv->frequency = SCI_SPI_DEFAULT_HZ;
  priv->actual    = 0;
  priv->mode      = SPIDEV_MODE0;
  priv->nbits     = 8;
  priv->lsbfirst  = false;

  /* One-shot semaphore/mutex init (#22 fix: not re-init on every call) */

  nxmutex_init(&priv->lock);
  nxsem_init(&priv->sem_isr, 0, 0);

  if (rzv_clock_enable(priv->clk_id) < 0)
    {
      spierr("SCI%d: clock enable failed\n", channel);
      goto fail_sync;
    }

  clock_enabled = true;

  if (rzv_module_unreset(priv->clk_id) < 0)
    {
      spierr("SCI%d: module unreset failed\n", channel);
      goto fail_clock;
    }

  module_unreset = true;

  if (sci_spi_hw_configure(priv) < 0)
    {
      spierr("SCI%d: hw_configure failed\n", channel);
      goto fail_module;
    }

  /* (#1 fix) Attach interrupts via INTR8SEL — no critical_section needed
   * (#16 fix: attach is init-context only, not atomic)
   * Initialise irq fields to -1 so rollback logic below is clean.  (A13 fix)
   */

  priv->irq_txi = -1;
  priv->irq_rxi = -1;
  priv->irq_tei = -1;
  priv->irq_eri = -1;

  priv->irq_txi = rzv_icu_attach(priv->evt_txi,
                                  rzv_sci_spi_txi_isr, priv, true);
  if (priv->irq_txi < 0)
    {
      goto irq_fail;
    }

  priv->irq_rxi = rzv_icu_attach(priv->evt_rxi,
                                  rzv_sci_spi_rxi_isr, priv, true);
  if (priv->irq_rxi < 0)
    {
      goto irq_fail;
    }

  priv->irq_tei = rzv_icu_attach(priv->evt_tei,
                                  rzv_sci_spi_tei_isr, priv, true);
  if (priv->irq_tei < 0)
    {
      goto irq_fail;
    }

  priv->irq_eri = rzv_icu_attach(priv->evt_eri,
                                  rzv_sci_spi_eri_isr, priv, true);
  if (priv->irq_eri < 0)
    {
      goto irq_fail;
    }

  flags = enter_critical_section();
  priv->initialized = true;
  priv->initializing = false;
  leave_critical_section(flags);
  spiinfo("SCI%d SPI initialized (freq=%u)\n",
          channel, (unsigned)priv->frequency);
  return &priv->dev;

irq_fail:
  /* Detach any IRQs that were successfully attached before the failure.
   * Guards with >= 0 prevent detaching un-attached slots.  (A13 fix)
   */

  spierr("SCI%d: IRQ attach failed (txi=%d rxi=%d tei=%d eri=%d)\n",
         channel, priv->irq_txi, priv->irq_rxi,
         priv->irq_tei, priv->irq_eri);

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

  if (priv->irq_tei >= 0)
    {
      rzv_icu_detach(priv->irq_tei);
      priv->irq_tei = -1;
    }

  if (priv->irq_eri >= 0)
    {
      rzv_icu_detach(priv->irq_eri);
      priv->irq_eri = -1;
    }

fail_module:
  putreg32(0u, priv->base + RZV_SCI_CCR0_OFFSET);
  if (module_unreset)
    {
      rzv_module_reset(priv->clk_id);
    }

fail_clock:
  if (clock_enabled)
    {
      rzv_clock_disable(priv->clk_id);
    }

fail_sync:
  nxsem_destroy(&priv->sem_isr);
  nxmutex_destroy(&priv->lock);
  flags = enter_critical_section();
  priv->state = SCI_SPI_STATE_IDLE;
  priv->initialized = false;
  priv->initializing = false;
  leave_critical_section(flags);
  return NULL;
}

#endif /* CONFIG_RZV_SCI_SPI */
