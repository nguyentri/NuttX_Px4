/****************************************************************************
 * arch/arm/src/rzv/rzv_sdhi.c
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

/* RZ/V2H (R9A09G057H) SDHI lower-half driver -- PIO implementation.
 *
 * Implements 1-bit PIO data path, IRQ-driven command/data completion,
 * 400 kHz init clock, and basic error handling.  DMA deferred.
 *
 * Register references:
 *   arch/arm/src/rzv/hardware/rzv_sdhi.h   (UM-derived, 8-byte stride)
 *   RZ/V2H Hardware User Manual s6.2
 *
 * Structural reference: arch/arm/src/ra8/ra_sdhi.c
 *
 * NuttX SDIO lower-half contract: function pointers stored directly in
 * struct sdio_dev_s (no separate ops struct); see include/nuttx/sdio.h.
 *
 * Key design decisions:
 * - INFO1/INFO2 clear rule: write 0 to bit(s) being cleared, 1 to others
 *   (UM s6.2.3.3).  See RZV_SDHI_INFO_CLEAR(handled_bits).
 * - BUF0 is 32-bit; all data pumped as uint32_t with ARM_DSB() between bursts.
 * - CBSY must be 0 before writing SD_CMD or changing CLK_CTRL divider.
 * - NuttX upper-half uses waitenable()/eventwait() model (not waitresponse for
 *   data transfers); waitresponse() used only for command-phase.
 *
 * CPG clock/reset IDs (authoritative decode lives in rzv_clock.h; see
 * RZV_CPG_CLK_SDHIn / RZV_CPG_RST_SDHIn):
 *   SDHI0 IMCLK: CLKON domain 10, bit 3
 *   SDHI0 IXRST: RST   domain 10, bit 7
 *   (The earlier "domain 14" figure was a base-offset double-count bug,
 *    corrected in rzv_clock.h.)
 *   By design NuttX gates IMCLK only.  The additional SDHI clocks
 *   (IMCLK2/CLK_HS/ACLK in CPG_CLKON_10) are enabled by the boot firmware
 *   (u-boot/TF-A) before NuttX starts, so they are intentionally not
 *   re-gated here.
 *
 * IRQ:
 *   SDHI CH0 OXMNIRQ = GIC SPI 735 = NuttX IRQ 767 (base 32)
 *   Source: refs/rzv2h_gb_ether/include/rzv2h_irq.h line 681
 */

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/arch.h>
#include <nuttx/clock.h>
#include <nuttx/irq.h>
#include <nuttx/sdio.h>
#include <nuttx/mmcsd.h>
#include <nuttx/semaphore.h>
#include <nuttx/wqueue.h>
#include <nuttx/wdog.h>

#include "chip.h"
#include "arm_internal.h"
#include "rzv_sdhi.h"
#include "rzv_clock.h"
#include "hardware/rzv_sdhi.h"

#ifdef CONFIG_RZV_SDHI

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define RZV_SDHI_NSLOTS            3   /* SD0, SD1, SD2 */

/* Timeout values */

#define RZV_SDHI_CMDTIMEOUT        MSEC2TICK(500)   /* command response */
#define RZV_SDHI_LONGTIMEOUT       MSEC2TICK(2000)  /* data transfer */
#define RZV_SDHI_CBSY_TIMEOUT_MS   1000             /* CBSY clear wait */

/* SD_OPTION default: 1-bit bus, max timeout counter (0xE), timeout mult=0 */

#define RZV_SDHI_SD_OPTION_INIT   (RZV_SDHI_SD_OPTION_WIDTH1 | \
                                   RZV_SDHI_SD_OPTION_TIMEOUT_MAX | 0x40u)

/* CLK_CTRL init: 400 kHz divider, SDCLK enabled, auto-gate on */

#define RZV_SDHI_CLK_CTRL_INIT    (RZV_SDHI_SD_CLK_CTRL_DIV_128 | \
                                   RZV_SDHI_SD_CLK_CTRL_SCLKEN   | \
                                   RZV_SDHI_SD_CLK_CTRL_SDCLKOFFEN)

/* INFO1/INFO2 "all events masked" values (writing all 1s masks everything) */

#define RZV_SDHI_INFO1_MASK_ALL   0xffffffffu
#define RZV_SDHI_INFO2_MASK_ALL   0xffffffffu

/* INFO register clear helper (UM s6.2.3.3.1: write 0 to bit being cleared,
 * 1 to all others).  Independent of current register value -- do NOT
 * read-modify-write.  Usage: putreg32(RZV_SDHI_INFO_CLEAR(bits), REG). */

#define RZV_SDHI_INFO_CLEAR(bits)  (~(uint32_t)(bits))

/* Register address helpers (base already stored in priv->base) */

#define RZV_SDHI_REG16(base, off)  ((base) + (off))
#define RZV_SDHI_REG32(base, off)  ((base) + (off))

/* Combined error mask covering all INFO2 error bits */

#define RZV_SDHI_SD_INFO2_ALL_ERRORS  RZV_SDHI_SD_INFO2_ERR_ALL

/* ARM data synchronisation barrier after BUF0 burst (Cortex-A55 cache) */

#ifndef ARM_DSB
#  if defined(__GNUC__)
#    define ARM_DSB()  __asm__ __volatile__("dsb sy" : : : "memory")
#  else
#    define ARM_DSB()  do {} while (0)
#  endif
#endif

/* IRQ array indexed by slot.  Uses canonical names from hardware/rzv_sdhi.h
 * (DRY -- no local aliases).  GIC SPI 735 -> NuttX INTID 767, per
 * RZV_IRQ_FIRST = 32 in rzv2h_irq.h.
 */

static const int g_rzv_sdhi_irq[RZV_SDHI_NSLOTS] =
{
  RZV_SDHI_CH0_OXMN_IRQ,
  RZV_SDHI_CH1_OXMN_IRQ,
  RZV_SDHI_CH2_OXMN_IRQ,
};

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* Lower-half device state.
 * 'dev' must be FIRST -- callers cast sdio_dev_s* <-> rzv_sdhi_dev_s*.
 */

struct rzv_sdhi_dev_s
{
  struct sdio_dev_s  dev;          /* Standard SDIO interface (MUST be first) */
  int                slot;         /* Slot index: 0=SD0, 1=SD1, 2=SD2 */
  uintptr_t          base;         /* Register base address */
  bool               initialized;  /* True after rzv_sdhi_initialize() */

  /* Transfer state */

  bool               widebus;      /* True when 4-bit bus is active */
  uint32_t          *buffer;       /* Current PIO transfer buffer pointer */
  uint32_t           remaining;    /* Bytes remaining in PIO transfer */
  uint32_t           blocksize;    /* Block size for current transfer */
  uint32_t           nblocks;      /* Block count */
  bool               multiblock;   /* True for multi-block transfer */

  /* Cached error status from last ISR */

  uint32_t           err_sts1;     /* SD_ERR_STS1 at error time */
  uint32_t           err_sts2;     /* SD_ERR_STS2 at error time */

  /* Event synchronisation */

  sem_t              waitsem;      /* Semaphore posted by ISR */
  sdio_eventset_t    waitevents;   /* Events the caller is waiting for */
  sdio_eventset_t    wkupevent;    /* Event that triggered wakeup */
  struct wdog_s      waitwdog;     /* Watchdog for event timeout */

  /* Callback (card insert/remove) */

  worker_t           callback;
  void              *cbarg;
  sdio_eventset_t    cbevents;
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static int  rzv_sdhi_interrupt(int irq, void *context, void *arg);
static void rzv_sdhi_eventtimeout(wdparm_t arg);
static int  rzv_sdhi_wait_cbsy(struct rzv_sdhi_dev_s *priv,
                               uint32_t timeout_ms);

/* SDIO ops */

static void rzv_sdhi_reset(FAR struct sdio_dev_s *dev);
static sdio_capset_t rzv_sdhi_capabilities(FAR struct sdio_dev_s *dev);
static sdio_statset_t rzv_sdhi_status(FAR struct sdio_dev_s *dev);
static void rzv_sdhi_widebus(FAR struct sdio_dev_s *dev, bool enable);
static void rzv_sdhi_clock(FAR struct sdio_dev_s *dev,
                           enum sdio_clock_e rate);
static int  rzv_sdhi_attach(FAR struct sdio_dev_s *dev);
static int  rzv_sdhi_sendcmd(FAR struct sdio_dev_s *dev, uint32_t cmd,
                             uint32_t arg);
#ifdef CONFIG_SDIO_BLOCKSETUP
static void rzv_sdhi_blocksetup(FAR struct sdio_dev_s *dev,
                                unsigned int blocklen, unsigned int nblocks);
#endif
static int  rzv_sdhi_recvsetup(FAR struct sdio_dev_s *dev,
                               FAR uint8_t *buffer, size_t nbytes);
static int  rzv_sdhi_sendsetup(FAR struct sdio_dev_s *dev,
                               FAR const uint8_t *buffer, size_t nbytes);
static int  rzv_sdhi_cancel(FAR struct sdio_dev_s *dev);
static int  rzv_sdhi_waitresponse(FAR struct sdio_dev_s *dev, uint32_t cmd);
static int  rzv_sdhi_recv_r1(FAR struct sdio_dev_s *dev, uint32_t cmd,
                             uint32_t *R1);
static int  rzv_sdhi_recv_r2(FAR struct sdio_dev_s *dev, uint32_t cmd,
                             uint32_t R2[4]);
static int  rzv_sdhi_recv_r3(FAR struct sdio_dev_s *dev, uint32_t cmd,
                             uint32_t *R3);
static int  rzv_sdhi_recv_r4(FAR struct sdio_dev_s *dev, uint32_t cmd,
                             uint32_t *R4);
static int  rzv_sdhi_recv_r5(FAR struct sdio_dev_s *dev, uint32_t cmd,
                             uint32_t *R5);
static int  rzv_sdhi_recv_r6(FAR struct sdio_dev_s *dev, uint32_t cmd,
                             uint32_t *R6);
static int  rzv_sdhi_recv_r7(FAR struct sdio_dev_s *dev, uint32_t cmd,
                             uint32_t *R7);
static void rzv_sdhi_waitenable(FAR struct sdio_dev_s *dev,
                                sdio_eventset_t eventset, uint32_t timeout);
static sdio_eventset_t rzv_sdhi_eventwait(FAR struct sdio_dev_s *dev);
static void rzv_sdhi_callbackenable(FAR struct sdio_dev_s *dev,
                                    sdio_eventset_t eventset);
static int  rzv_sdhi_registercallback(FAR struct sdio_dev_s *dev,
                                      worker_t callback, void *arg);
#ifdef CONFIG_SDIO_DMA
static int  rzv_sdhi_dmarecvsetup(FAR struct sdio_dev_s *dev,
                                  FAR uint8_t *buffer, size_t buflen);
static int  rzv_sdhi_dmasendsetup(FAR struct sdio_dev_s *dev,
                                  FAR const uint8_t *buffer, size_t buflen);
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Per-slot device instances */

static struct rzv_sdhi_dev_s g_rzv_sdhi_dev[RZV_SDHI_NSLOTS];

/* Base address table indexed by slot */

static const uintptr_t g_rzv_sdhi_base[RZV_SDHI_NSLOTS] =
{
  RZV_SDHI0_BASE,  /* Slot 0 -- RDK SD card connector (QSD0_*) */
  RZV_SDHI1_BASE,  /* Slot 1 */
  RZV_SDHI2_BASE,  /* Slot 2 */
};

/****************************************************************************
 * Private Functions -- Low-level helpers
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_sdhi_wait_cbsy
 *
 * Description:
 *   Spin-wait for SD_INFO2.CBSY to clear (command-busy).
 *   Must be called before writing SD_CMD or changing CLK_CTRL.DIV.
 *   UM rule: do not issue next command while CBSY=1.
 *
 ****************************************************************************/

static int rzv_sdhi_wait_cbsy(struct rzv_sdhi_dev_s *priv,
                              uint32_t timeout_ms)
{
  uint32_t start = clock_systime_ticks();
  uint32_t timeout_ticks = MSEC2TICK(timeout_ms);

  while (getreg32(RZV_SDHI_REG32(priv->base,
                                  RZV_SDHI_SD_INFO2_OFFSET)) &
         RZV_SDHI_SD_INFO2_CBSY)
    {
      if ((clock_systime_ticks() - start) > timeout_ticks)
        {
          mcerr("SDHI%d: CBSY timeout\n", priv->slot);
          return -ETIMEDOUT;
        }

      up_udelay(1);
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_sdhi_disableints
 *
 * Description:
 *   Mask all INFO1 and INFO2 interrupts.
 *
 ****************************************************************************/

static void rzv_sdhi_disableints(struct rzv_sdhi_dev_s *priv)
{
  putreg32(RZV_SDHI_INFO1_MASK_ALL,
           RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_INFO1_MASK_OFFSET));
  putreg32(RZV_SDHI_INFO2_MASK_ALL,
           RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_INFO2_MASK_OFFSET));
}

/****************************************************************************
 * Name: rzv_sdhi_configwaitints
 *
 * Description:
 *   Enable the specified INFO1/INFO2 interrupt bits by clearing their mask
 *   bits.  Mask all other bits.
 *
 *   info1_en: bitmask of INFO1 bits to enable (unmasked)
 *   info2_en: bitmask of INFO2 bits to enable (unmasked)
 *   events:   waitevents to store in priv
 *
 ****************************************************************************/

static void rzv_sdhi_configwaitints(struct rzv_sdhi_dev_s *priv,
                                    uint32_t info1_en, uint32_t info2_en,
                                    sdio_eventset_t events)
{
  irqstate_t flags;

  flags = enter_critical_section();

  priv->waitevents = events;
  priv->wkupevent  = 0;

  /* Mask = inverse of enable bits; set all others */

  putreg32(~info1_en,
           RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_INFO1_MASK_OFFSET));
  putreg32(~info2_en,
           RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_INFO2_MASK_OFFSET));

  leave_critical_section(flags);
}

/****************************************************************************
 * Name: rzv_sdhi_eventtimeout
 *
 * Description:
 *   Watchdog callback -- post the wait semaphore with TIMEOUT.
 *
 ****************************************************************************/

static void rzv_sdhi_eventtimeout(wdparm_t arg)
{
  struct rzv_sdhi_dev_s *priv = (struct rzv_sdhi_dev_s *)arg;

  /* Claim wkupevent atomically vs ISR (FIX 5 watchdog side).
   * If ISR already claimed it, do not double-post the semaphore.
   */

  if (priv->wkupevent == 0)
    {
      priv->wkupevent = SDIOWAIT_TIMEOUT;
      rzv_sdhi_disableints(priv);
      nxsem_post(&priv->waitsem);
    }
}

/****************************************************************************
 * Name: rzv_sdhi_interrupt
 *
 * Description:
 * Combined ISR for SDHI CH0 OXMNIRQ (handles command done, data
 *   done, PIO read/write, and errors).  Demux INFO1 and INFO2 bits.
 *
 *   Clear rule (UM s6.2.3.3.1):
 *     Write 0 to bit being cleared, 1 to all other bits.
 *     Use RZV_SDHI_INFO_CLEAR(handled_bits) to form write-back value.
 *
 *   ARM DSB after BUF0 burst to maintain data coherency on Cortex-A55.
 *
 ****************************************************************************/

static int rzv_sdhi_interrupt(int irq, void *context, void *arg)
{
  struct rzv_sdhi_dev_s *priv = (struct rzv_sdhi_dev_s *)arg;
  uint32_t info1;
  uint32_t info2;
  sdio_eventset_t events = 0;

  /* Accumulate clear masks -- written ONCE per register at end of ISR.
   * Rule (UM s6.2.3.3.1): write 0 to bit being cleared, 1 to all others.
   * Start with "clear nothing" (all 1s = leave all bits alone).
   */

  uint32_t info1_clear = 0xffffffffu;  /* bits to write back to INFO1 */
  uint32_t info2_clear = 0xffffffffu;  /* bits to write back to INFO2 */

  /* Read interrupt status registers */

  info1 = getreg32(RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_INFO1_OFFSET));
  info2 = getreg32(RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_INFO2_OFFSET));

  /* --- PIO Buffer Read (BRE): pump BUF0 -> caller buffer --- */

  if (info2 & RZV_SDHI_SD_INFO2_BRE)
    {
      /* Drain available data into the caller's buffer, 32 bits at a time.
       * Keep looping while BRE is set and data remains.
       * ARM_DSB() after each FIFO word to ensure ordering on Cortex-A55.
       */

      while (priv->remaining >= 4)
        {
          if (priv->buffer != NULL)
            {
              *priv->buffer = getreg32(
                RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_BUF0_OFFSET));
              ARM_DSB();
              priv->buffer++;
              priv->remaining -= 4;
            }
          else
            {
              /* Null buffer -- discard to unblock hardware */

              (void)getreg32(
                RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_BUF0_OFFSET));
              ARM_DSB();
              events |= SDIOWAIT_ERROR;
              break;
            }

          /* Re-read INFO2 to see if more data is ready */

          info2 = getreg32(
            RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_INFO2_OFFSET));
          if (!(info2 & RZV_SDHI_SD_INFO2_BRE))
            {
              break;
            }
        }

      /* Accumulate BRE clear into INFO2 mask (write 0 to BRE bit) */

      info2_clear &= ~RZV_SDHI_SD_INFO2_BRE;
    }

  /* --- PIO Buffer Write (BWE): pump caller buffer -> BUF0 --- */

  if (info2 & RZV_SDHI_SD_INFO2_BWE)
    {
      while (priv->remaining >= 4)
        {
          if (priv->buffer != NULL)
            {
              putreg32(*priv->buffer,
                       RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_BUF0_OFFSET));
              ARM_DSB();
              priv->buffer++;
              priv->remaining -= 4;
            }
          else
            {
              putreg32(0u,
                       RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_BUF0_OFFSET));
              ARM_DSB();
              events |= SDIOWAIT_ERROR;
              break;
            }

          /* Re-read INFO2 to see if TX FIFO can accept more */

          info2 = getreg32(
            RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_INFO2_OFFSET));
          if (!(info2 & RZV_SDHI_SD_INFO2_BWE))
            {
              break;
            }
        }

      /* Accumulate BWE clear into INFO2 mask */

      info2_clear &= ~RZV_SDHI_SD_INFO2_BWE;
    }

  /* --- Error bits in INFO2 --- */

  if (info2 & RZV_SDHI_SD_INFO2_ALL_ERRORS)
    {
      /* Save error details for diagnostics */

      priv->err_sts1 = getreg32(
        RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_ERR_STS1_OFFSET));
      priv->err_sts2 = getreg32(
        RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_ERR_STS2_OFFSET));

      mcerr("SDHI%d: ERR INFO2=0x%08" PRIx32
            " ERR_STS1=0x%08" PRIx32 " ERR_STS2=0x%08" PRIx32 "\n",
            priv->slot, info2, priv->err_sts1, priv->err_sts2);

      if (info2 & RZV_SDHI_SD_INFO2_RSPTO)
        {
          events |= SDIOWAIT_TIMEOUT;
        }
      else
        {
          events |= SDIOWAIT_ERROR;
        }

      /* Accumulate error bits clear into INFO2 mask */

      info2_clear &= ~RZV_SDHI_SD_INFO2_ALL_ERRORS;
    }

  /* --- Response received (INFO1.RSPEND) --- */

  if (info1 & RZV_SDHI_SD_INFO1_RSPEND)
    {
      events |= SDIOWAIT_CMDDONE;

      /* Accumulate RSPEND clear into INFO1 mask */

      info1_clear &= ~RZV_SDHI_SD_INFO1_RSPEND;
    }

  /* --- Access end / data transfer complete (INFO1.ACEND) --- */

  if (info1 & RZV_SDHI_SD_INFO1_ACEND)
    {
      events |= SDIOWAIT_TRANSFERDONE;

      /* Accumulate ACEND clear into INFO1 mask */

      info1_clear &= ~RZV_SDHI_SD_INFO1_ACEND;
    }

  /* Write INFO1 and INFO2 ONCE each (FIX 2 + FIX 11).
   * This clears all handled bits in a single write and defensively
   * leaves unhandled-but-asserted bits alone (prevent IRQ storm).
   */

  putreg32(info1_clear,
           RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_INFO1_OFFSET));
  putreg32(info2_clear,
           RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_INFO2_OFFSET));

  /* Wake waiter only if this ISR is first to claim wkupevent (FIX 5).
   * Guard against watchdog having already claimed it.
   */

  if (events != 0 && (events & priv->waitevents) != 0)
    {
      if (priv->wkupevent == 0)
        {
          priv->wkupevent = events;
          rzv_sdhi_disableints(priv);
          wd_cancel(&priv->waitwdog);
          nxsem_post(&priv->waitsem);
        }
    }

  return OK;
}

/****************************************************************************
 * Private Functions -- SDIO op implementations
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_sdhi_reset (task 2.1)
 *
 * Description:
 *   Pulse SOFT_RST to reset the SDHI state machine, then restore default
 *   masks and 400 kHz clock.  Called from rzv_sdhi_initialize() and
 *   rzv_sdhi_cancel() on error recovery.
 *
 *   Sequence (UM s6.2.2.2.14):
 *     1. Write SDRST=0 (assert reset -- active low)
 *     2. Wait >= 1 us
 *     3. Write SDRST=1 (release reset)
 *     4. Mask all interrupts
 *     5. Set SD_OPTION (1-bit, max timeout)
 *     6. Set 400 kHz divider: clear SCLKEN -> write DIV=0x20 -> set SCLKEN
 *
 ****************************************************************************/

static void rzv_sdhi_reset(FAR struct sdio_dev_s *dev)
{
  FAR struct rzv_sdhi_dev_s *priv = (FAR struct rzv_sdhi_dev_s *)dev;
  uint32_t reg;

  mcinfo("SDHI%d: reset\n", priv->slot);

  /* Assert SOFT_RST (SDRST = 0 = active low reset) */

  putreg32(0u, RZV_SDHI_REG32(priv->base, RZV_SDHI_SOFT_RST_OFFSET));
  up_udelay(10);

  /* Release SOFT_RST (SDRST = 1) */

  putreg32(RZV_SDHI_SOFT_RST_SDRST,
           RZV_SDHI_REG32(priv->base, RZV_SDHI_SOFT_RST_OFFSET));
  up_udelay(10);

  /* Mask all interrupts */

  rzv_sdhi_disableints(priv);

  /* Clear any stale INFO1/INFO2 flags
   * Write all-1s is safe: any 1 in INFO is "event occurred"; writing 0
   * clears; writing 1 leaves -- so writing all-zeros clears all, but the
   * UM says "write 0 to the bit you want clear, 1 to others".  After
   * reset, safest is write 0 explicitly to clear all. */

  putreg32(0u, RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_INFO1_OFFSET));
  putreg32(0u, RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_INFO2_OFFSET));

  /* Set SD_OPTION: 1-bit bus width (WIDTH1=1), max timeout */

  putreg16(RZV_SDHI_SD_OPTION_INIT,
           RZV_SDHI_REG16(priv->base, RZV_SDHI_SD_OPTION_OFFSET));

  /* Block size = 512 bytes */

  putreg16(512u, RZV_SDHI_REG16(priv->base, RZV_SDHI_SD_SIZE_OFFSET));

  /* Set 400 kHz clock:
   *   UM rule: clear SCLKEN -> write DIV -> set SCLKEN.
   *   SDCLK = (IMCLK/4)/128 = (200MHz/4)/128 = 390.6 kHz
   *   (IMCLK = 200 MHz, confirmed for RDK-RZV2H)
   */

  reg = getreg16(RZV_SDHI_REG16(priv->base, RZV_SDHI_SD_CLK_CTRL_OFFSET));
  reg &= ~RZV_SDHI_SD_CLK_CTRL_SCLKEN;
  putreg16((uint16_t)reg,
           RZV_SDHI_REG16(priv->base, RZV_SDHI_SD_CLK_CTRL_OFFSET));

  reg = (RZV_SDHI_SD_CLK_CTRL_DIV_128 |
         RZV_SDHI_SD_CLK_CTRL_SDCLKOFFEN);
  putreg16((uint16_t)reg,
           RZV_SDHI_REG16(priv->base, RZV_SDHI_SD_CLK_CTRL_OFFSET));

  reg |= RZV_SDHI_SD_CLK_CTRL_SCLKEN;
  putreg16((uint16_t)reg,
           RZV_SDHI_REG16(priv->base, RZV_SDHI_SD_CLK_CTRL_OFFSET));

  /* Reset transfer state */

  priv->buffer     = NULL;
  priv->remaining  = 0;
  priv->blocksize  = 512;
  priv->nblocks    = 1;
  priv->multiblock = false;
  priv->err_sts1   = 0;
  priv->err_sts2   = 0;
  priv->wkupevent  = 0;

  mcinfo("SDHI%d: reset complete, CLK_CTRL=0x%04x\n",
         priv->slot,
         (unsigned)getreg16(
           RZV_SDHI_REG16(priv->base, RZV_SDHI_SD_CLK_CTRL_OFFSET)));
}

/****************************************************************************
 * Name: rzv_sdhi_capabilities
 ****************************************************************************/

static sdio_capset_t rzv_sdhi_capabilities(FAR struct sdio_dev_s *dev)
{
  /* SDIO_CAPS_4BIT: hardware supports 4-bit bus; widebus() op configures it.
   * SDIO_CAPS_DMASUPPORTED: not set -- DMA deferred.
   * SDIO_CAPS_8BIT: not set -- 8-bit eMMC not supported in MVP.
   */

  return SDIO_CAPS_4BIT;
}

/****************************************************************************
 * Name: rzv_sdhi_status
 ****************************************************************************/

static sdio_statset_t rzv_sdhi_status(FAR struct sdio_dev_s *dev)
{
  FAR struct rzv_sdhi_dev_s *priv = (FAR struct rzv_sdhi_dev_s *)dev;
  uint32_t info1;

  info1 = getreg32(RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_INFO1_OFFSET));

  mcinfo("SDHI%d: status INFO1=0x%08" PRIx32 "\n", priv->slot, info1);

  /* INFO1.INFO3 (SDCDIN) = card insertion flag; bit set when card present.
   * Controller card-detect is the RDK-RZV2H detection path (confirmed).
   */

  if (info1 & RZV_SDHI_SD_INFO1_SDCDIN)
    {
      return SDIO_STATUS_PRESENT;
    }

  return 0;
}

/****************************************************************************
 * Name: rzv_sdhi_widebus
 *
 * Description:
 *   Configure bus width via SD_OPTION register.
 *
 *   SD_OPTION bit 15 (WIDTH1): 0 = 4-bit bus, 1 = 1-bit bus (reset default).
 *   RZ/V2H uses only this single bit for SD-mode width; no WIDTH8/WIDTH4
 *   compound field -- SD0 supports 1/4/8-bit but 8-bit uses HOST_MODE, not
 * OPTION.WIDTH (MVP: 1-bit and 4-bit only, no 8-bit eMMC).
 *   Source: UM s6.2.2.1 SD_OPTION description + FSP r_sdhi.c OPTION writes.
 *   NEEDS_VERIFY: confirm WIDTH8 is irrelevant for SD-mode (eMMC-only concern).
 *
 *   Sequence: read OPTION -> mask WIDTH1 -> set per width -> write back.
 *
 ****************************************************************************/

static void rzv_sdhi_widebus(FAR struct sdio_dev_s *dev, bool enable)
{
  FAR struct rzv_sdhi_dev_s *priv = (FAR struct rzv_sdhi_dev_s *)dev;
  uint32_t opt;

  priv->widebus = enable;

  opt = getreg16(RZV_SDHI_REG16(priv->base, RZV_SDHI_SD_OPTION_OFFSET));

  if (enable)
    {
      /* 4-bit: clear WIDTH1 bit (bit 15 = 0 -> 4-bit) */

      opt &= ~RZV_SDHI_SD_OPTION_WIDTH1;
    }
  else
    {
      /* 1-bit: set WIDTH1 bit (bit 15 = 1 -> 1-bit) */

      opt |= RZV_SDHI_SD_OPTION_WIDTH1;
    }

  putreg16((uint16_t)opt,
           RZV_SDHI_REG16(priv->base, RZV_SDHI_SD_OPTION_OFFSET));

  mcinfo("SDHI%d: widebus=%d, SD_OPTION=0x%04x\n", priv->slot,
         (int)enable, (unsigned)opt);
}

/****************************************************************************
 * Name: rzv_sdhi_clock (task 2.2)
 *
 * Description:
 *   Set SDCLK frequency.  Lookup table based on IMCLK=200 MHz (confirmed
 *   for RDK-RZV2H).  Must wait for CBSY=0 before changing divider (UM req).
 *
 *   Divider formula: SDCLK = (IMCLK/4)/N, one-hot DIV[7:0].
 *   Lookup table (IMCLK = 200 MHz):
 *     CLOCK_IDMODE        -> DIV=0x20 -> ~391 kHz
 *     CLOCK_SD_TRANSFER_1BIT,
 *     CLOCK_SD_TRANSFER_4BIT -> DIV=0x00 -> 25 MHz
 *
 ****************************************************************************/

static void rzv_sdhi_clock(FAR struct sdio_dev_s *dev,
                           enum sdio_clock_e rate)
{
  FAR struct rzv_sdhi_dev_s *priv = (FAR struct rzv_sdhi_dev_s *)dev;
  uint16_t div;
  uint16_t reg;
  int ret;

  switch (rate)
    {
      case CLOCK_SD_TRANSFER_1BIT:
      case CLOCK_SD_TRANSFER_4BIT:
        /* 25 MHz: DIV=0x00 -> SDCLK=(200MHz/4)/2=25 MHz (IMCLK=200 MHz) */

        div = RZV_SDHI_SD_CLK_CTRL_DIV_2;
        mcinfo("SDHI%d: clock -> 25 MHz (DIV=0x00)\n", priv->slot);
        break;

      case CLOCK_IDMODE:
      default:
        /* 400 kHz init: DIV=0x20 -> ~391 kHz */

        div = RZV_SDHI_SD_CLK_CTRL_DIV_128;
        mcinfo("SDHI%d: clock -> ~400 kHz (DIV=0x20)\n", priv->slot);
        break;
    }

  /* Wait for CBSY=0 before changing CLK divider (UM rule) */

  ret = rzv_sdhi_wait_cbsy(priv, RZV_SDHI_CBSY_TIMEOUT_MS);
  if (ret < 0)
    {
      mcerr("SDHI%d: CBSY stuck -- skipping clock change\n", priv->slot);
      return;
    }

  /* Sequence: clear SCLKEN -> write DIV -> set SCLKEN */

  reg = (uint16_t)getreg16(
    RZV_SDHI_REG16(priv->base, RZV_SDHI_SD_CLK_CTRL_OFFSET));
  reg &= ~RZV_SDHI_SD_CLK_CTRL_SCLKEN;
  putreg16(reg, RZV_SDHI_REG16(priv->base, RZV_SDHI_SD_CLK_CTRL_OFFSET));

  reg  = (uint16_t)(div & RZV_SDHI_SD_CLK_CTRL_DIV_MASK);
  reg |= RZV_SDHI_SD_CLK_CTRL_SDCLKOFFEN;
  putreg16(reg, RZV_SDHI_REG16(priv->base, RZV_SDHI_SD_CLK_CTRL_OFFSET));

  reg |= RZV_SDHI_SD_CLK_CTRL_SCLKEN;
  putreg16(reg, RZV_SDHI_REG16(priv->base, RZV_SDHI_SD_CLK_CTRL_OFFSET));

  up_udelay(100);  /* Let clock stabilise */
}

/****************************************************************************
 * Name: rzv_sdhi_attach (task 2.8)
 *
 * Description:
 *   Attach the combined OXMNIRQ ISR and enable the interrupt.
 *
 ****************************************************************************/

static int rzv_sdhi_attach(FAR struct sdio_dev_s *dev)
{
  FAR struct rzv_sdhi_dev_s *priv = (FAR struct rzv_sdhi_dev_s *)dev;
  int irq;
  int ret;

  irq = g_rzv_sdhi_irq[priv->slot];

  ret = irq_attach(irq, rzv_sdhi_interrupt, priv);
  if (ret < 0)
    {
      mcerr("SDHI%d: irq_attach(%d) failed: %d\n", priv->slot, irq, ret);
      return ret;
    }

  up_enable_irq(irq);

  mcinfo("SDHI%d: IRQ %d attached and enabled\n", priv->slot, irq);
  return OK;
}

/****************************************************************************
 * Name: rzv_sdhi_sendcmd (task 2.3)
 *
 * Description:
 *   Build and issue an SD command.
 *
 *   Register write order (UM requirement):
 *     1. SD_ARG  (bits [15:0] of arg)
 *     2. SD_ARG1 (bits [31:16] of arg)
 *     3. SD_CMD  (command index + flags) -- triggers execution
 *
 *   CMD encoding:
 *     Bits [5:0]:  command index
 *     Bits [10:8]: response type (000=none, 011=R1/R6/R7, 100=R2, 101=R3/R4)
 *     Bit  [11]:   data transfer (CMDTP)
 *     Bit  [12]:   read direction (CMDRW; 1=read, 0=write)
 *     Bit  [13]:   multi-block (TRSTP)
 *
 *   NuttX MMCSD cmd word layout (from include/nuttx/sdio.h):
 *     MMCSD_CMDIDX_SHIFT/MASK, MMCSD_RESPONSE_MASK, MMCSD_DATAXFR_MASK,
 *     MMCSD_WRXFR, MMCSD_MULTIBLOCK, MMCSD_R1/R1B/R2/R3/R4/R5/R6/R7_RESPONSE
 *
 ****************************************************************************/

static int rzv_sdhi_sendcmd(FAR struct sdio_dev_s *dev, uint32_t cmd,
                            uint32_t arg)
{
  FAR struct rzv_sdhi_dev_s *priv = (FAR struct rzv_sdhi_dev_s *)dev;
  uint16_t cmd_reg = 0;
  uint8_t  cmdidx;
  int      ret;

  /* Wait for CBSY=0 before writing command */

  ret = rzv_sdhi_wait_cbsy(priv, RZV_SDHI_CBSY_TIMEOUT_MS);
  if (ret < 0)
    {
      return ret;
    }

  /* Command index [5:0] */

  cmdidx  = (uint8_t)((cmd & MMCSD_CMDIDX_MASK) >> MMCSD_CMDIDX_SHIFT);
  cmd_reg = (uint16_t)(cmdidx & RZV_SDHI_SD_CMD_CMDIDX_MASK);

  /* Response type */

  switch (cmd & MMCSD_RESPONSE_MASK)
    {
      case MMCSD_NO_RESPONSE:
        cmd_reg |= RZV_SDHI_SD_CMD_RSP_NONE;
        break;

      case MMCSD_R2_RESPONSE:
        cmd_reg |= RZV_SDHI_SD_CMD_RSP_R2;
        break;

      case MMCSD_R3_RESPONSE:
      case MMCSD_R4_RESPONSE:
        /* R3/R4: no CRC, 48-bit; map to RSP=101 (R3 in FSP terms) */

        cmd_reg |= RZV_SDHI_SD_CMD_RSP_R3;
        break;

      default:
        /* R1/R1b/R5/R6/R7: map to RSP=011 */

        cmd_reg |= RZV_SDHI_SD_CMD_RSP_R1;
        break;
    }

  /* Data transfer flag */

  if (cmd & MMCSD_DATAXFR_MASK)
    {
      cmd_reg |= RZV_SDHI_SD_CMD_DATA;

      if (!(cmd & MMCSD_WRXFR))
        {
          cmd_reg |= RZV_SDHI_SD_CMD_READ;  /* 1 = read */
        }

      if (priv->multiblock)
        {
          cmd_reg |= RZV_SDHI_SD_CMD_MULTI;
          cmd_reg |= RZV_SDHI_SD_CMD_CMD12; /* Auto CMD12 for multi-block */
        }
    }

  mcinfo("SDHI%d: sendcmd idx=%u arg=0x%08" PRIx32 " cmd_reg=0x%04x\n",
         priv->slot, cmdidx, arg, (unsigned)cmd_reg);

  /* Write argument -- SD_ARG=low 16 bits, SD_ARG1=high 16 bits */

  putreg16((uint16_t)(arg & 0xffff),
           RZV_SDHI_REG16(priv->base, RZV_SDHI_SD_ARG_OFFSET));
  putreg16((uint16_t)((arg >> 16) & 0xffff),
           RZV_SDHI_REG16(priv->base, RZV_SDHI_SD_ARG1_OFFSET));

  /* Arm command-done interrupt before writing CMD (INFO1.RSPEND) */

  rzv_sdhi_configwaitints(priv,
                          RZV_SDHI_SD_INFO1_RSPEND,
                          RZV_SDHI_SD_INFO2_ALL_ERRORS,
                          SDIOWAIT_CMDDONE | SDIOWAIT_TIMEOUT |
                          SDIOWAIT_ERROR);

  /* Write command register -- this triggers the command */

  putreg16(cmd_reg,
           RZV_SDHI_REG16(priv->base, RZV_SDHI_SD_CMD_OFFSET));

  return OK;
}

/****************************************************************************
 * Name: rzv_sdhi_blocksetup
 *
 * Description:
 *   Set block size and count for upcoming data transfer.
 *
 ****************************************************************************/

#ifdef CONFIG_SDIO_BLOCKSETUP
static void rzv_sdhi_blocksetup(FAR struct sdio_dev_s *dev,
                                unsigned int blocklen, unsigned int nblocks)
{
  FAR struct rzv_sdhi_dev_s *priv = (FAR struct rzv_sdhi_dev_s *)dev;

  priv->blocksize  = blocklen;
  priv->nblocks    = nblocks;
  priv->multiblock = (nblocks > 1);

  putreg16((uint16_t)blocklen,
           RZV_SDHI_REG16(priv->base, RZV_SDHI_SD_SIZE_OFFSET));

  if (nblocks > 1)
    {
      putreg16((uint16_t)nblocks,
               RZV_SDHI_REG16(priv->base, RZV_SDHI_SD_SECCNT_OFFSET));

      /* Enable block count mode in SD_STOP */

      putreg16(0x0100u,
               RZV_SDHI_REG16(priv->base, RZV_SDHI_SD_STOP_OFFSET));
    }
  else
    {
      putreg16(0u,
               RZV_SDHI_REG16(priv->base, RZV_SDHI_SD_STOP_OFFSET));
    }

  mcinfo("SDHI%d: blocksetup len=%u cnt=%u\n", priv->slot, blocklen, nblocks);
}
#endif /* CONFIG_SDIO_BLOCKSETUP */

/****************************************************************************
 * Name: rzv_sdhi_recvsetup (task 2.6)
 *
 * Description:
 *   Set up for PIO receive.  Save buffer pointer, arm BRE interrupt.
 *
 ****************************************************************************/

static int rzv_sdhi_recvsetup(FAR struct sdio_dev_s *dev,
                              FAR uint8_t *buffer, size_t nbytes)
{
  FAR struct rzv_sdhi_dev_s *priv = (FAR struct rzv_sdhi_dev_s *)dev;
  irqstate_t flags;

  DEBUGASSERT(buffer != NULL && nbytes > 0);

  if (((uintptr_t)buffer & 3) != 0)
    {
      mcerr("SDHI%d: recvsetup buffer must be 4-byte aligned: %p\n",
            priv->slot, buffer);
      return -EINVAL;
    }

  if ((nbytes & 3) != 0)
    {
      mcerr("SDHI%d: recvsetup nbytes must be multiple of 4: %zu\n",
            priv->slot, nbytes);
      return -EINVAL;
    }

  /* Set block size before arming interrupts */

  putreg16((uint16_t)priv->blocksize,
           RZV_SDHI_REG16(priv->base, RZV_SDHI_SD_SIZE_OFFSET));

  /* Write buffer/remaining under critical section to prevent a stale ISR
   * (from a previous cancelled transfer) from seeing half-updated state.
   */

  flags = enter_critical_section();
  priv->buffer    = (uint32_t *)(uintptr_t)buffer;
  priv->remaining = nbytes;
  leave_critical_section(flags);

  /* Arm BRE (buffer read enable) + ACCESS_END + error interrupts */

  rzv_sdhi_configwaitints(priv,
                          RZV_SDHI_SD_INFO1_ACEND,
                          RZV_SDHI_SD_INFO2_BRE |
                          RZV_SDHI_SD_INFO2_ALL_ERRORS,
                          SDIOWAIT_TRANSFERDONE | SDIOWAIT_TIMEOUT |
                          SDIOWAIT_ERROR);

  mcinfo("SDHI%d: recvsetup buf=%p bytes=%zu\n", priv->slot, buffer, nbytes);
  return OK;
}

/****************************************************************************
 * Name: rzv_sdhi_sendsetup (task 2.6)
 *
 * Description:
 *   Set up for PIO transmit.  Save buffer pointer, arm BWE interrupt.
 *
 ****************************************************************************/

static int rzv_sdhi_sendsetup(FAR struct sdio_dev_s *dev,
                              FAR const uint8_t *buffer, size_t nbytes)
{
  FAR struct rzv_sdhi_dev_s *priv = (FAR struct rzv_sdhi_dev_s *)dev;
  irqstate_t flags;

  DEBUGASSERT(buffer != NULL && nbytes > 0);

  if (((uintptr_t)buffer & 3) != 0)
    {
      mcerr("SDHI%d: sendsetup buffer must be 4-byte aligned: %p\n",
            priv->slot, buffer);
      return -EINVAL;
    }

  if ((nbytes & 3) != 0)
    {
      mcerr("SDHI%d: sendsetup nbytes must be multiple of 4: %zu\n",
            priv->slot, nbytes);
      return -EINVAL;
    }

  /* Set block size before arming interrupts */

  putreg16((uint16_t)priv->blocksize,
           RZV_SDHI_REG16(priv->base, RZV_SDHI_SD_SIZE_OFFSET));

  /* Write buffer/remaining under critical section (see recvsetup comment).
   * Cast via uintptr_t to suppress -Wcast-qual; ISR only reads from buffer.
   */

  flags = enter_critical_section();
  priv->buffer    = (uint32_t *)(uintptr_t)buffer;
  priv->remaining = nbytes;
  leave_critical_section(flags);

  /* Arm BWE (buffer write enable) + ACCESS_END + error interrupts */

  rzv_sdhi_configwaitints(priv,
                          RZV_SDHI_SD_INFO1_ACEND,
                          RZV_SDHI_SD_INFO2_BWE |
                          RZV_SDHI_SD_INFO2_ALL_ERRORS,
                          SDIOWAIT_TRANSFERDONE | SDIOWAIT_TIMEOUT |
                          SDIOWAIT_ERROR);

  mcinfo("SDHI%d: sendsetup buf=%p bytes=%zu\n", priv->slot, buffer, nbytes);
  return OK;
}

/****************************************************************************
 * Name: rzv_sdhi_cancel (task 2.9)
 *
 * Description:
 *   Abort the current operation: mask all interrupts, pulse SOFT_RST,
 *   post all waiters with -ECANCELED.
 *
 ****************************************************************************/

static int rzv_sdhi_cancel(FAR struct sdio_dev_s *dev)
{
  FAR struct rzv_sdhi_dev_s *priv = (FAR struct rzv_sdhi_dev_s *)dev;
  irqstate_t flags;
  bool need_post;

  mcinfo("SDHI%d: cancel\n", priv->slot);

  /* Mask all interrupts immediately before manipulating state.
   * Must be done outside the critical section because disableints
   * does register writes that need to complete before we null the buffer.
   */

  rzv_sdhi_disableints(priv);

  /* Cancel the watchdog timer */

  wd_cancel(&priv->waitwdog);

  /* Soft-reset the controller */

  putreg32(0u, RZV_SDHI_REG32(priv->base, RZV_SDHI_SOFT_RST_OFFSET));
  up_udelay(10);
  putreg32(RZV_SDHI_SOFT_RST_SDRST,
           RZV_SDHI_REG32(priv->base, RZV_SDHI_SOFT_RST_OFFSET));

  /* Atomically null buffer, clear state, and decide whether to post.
   * Critical section ensures ISR cannot observe a partially-torn state
   * (buffer non-NULL but waitevents already cleared, or vice versa).
   */

  flags = enter_critical_section();

  need_post        = (priv->waitevents != 0 && priv->wkupevent == 0);
  priv->buffer     = NULL;
  priv->remaining  = 0;
  priv->waitevents = 0;

  if (need_post)
    {
      priv->wkupevent = SDIOWAIT_ERROR;
    }

  leave_critical_section(flags);

  if (need_post)
    {
      nxsem_post(&priv->waitsem);
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_sdhi_waitresponse (task 2.4)
 *
 * Description:
 *   Wait for a command response (sem posted by ISR when RSPEND fires).
 *   On wakeup check INFO2 for errors.
 *
 *   Note: NuttX MMCSD upper-half calls waitenable()/eventwait() for data
 *   transfers; waitresponse() is used only for command-phase waiting.
 *
 ****************************************************************************/

static int rzv_sdhi_waitresponse(FAR struct sdio_dev_s *dev, uint32_t cmd)
{
  FAR struct rzv_sdhi_dev_s *priv = (FAR struct rzv_sdhi_dev_s *)dev;
  int ret;

  ret = nxsem_tickwait_uninterruptible(&priv->waitsem, RZV_SDHI_CMDTIMEOUT);

  rzv_sdhi_disableints(priv);

  if (ret < 0)
    {
      mcerr("SDHI%d: waitresponse semaphore timeout (cmd=0x%08" PRIx32 ")\n",
            priv->slot, cmd);

      /* Reset controller so CBSY is cleared; otherwise next sendcmd hangs. */

      rzv_sdhi_reset(&priv->dev);
      return -ETIMEDOUT;
    }

  if (priv->wkupevent & SDIOWAIT_TIMEOUT)
    {
      mcerr("SDHI%d: response timeout (INFO2 RSPTO)\n", priv->slot);

      /* Same recovery: reset to clear CBSY before next command. */

      rzv_sdhi_reset(&priv->dev);
      return -ETIMEDOUT;
    }

  if (priv->wkupevent & SDIOWAIT_ERROR)
    {
      mcerr("SDHI%d: response error ERR_STS1=0x%08" PRIx32
            " ERR_STS2=0x%08" PRIx32 "\n",
            priv->slot, priv->err_sts1, priv->err_sts2);
      return -EIO;
    }

  mcinfo("SDHI%d: response OK\n", priv->slot);
  return OK;
}

/****************************************************************************
 * Name: rzv_sdhi_recv_r1 / recvshort (task 2.5)
 *
 * Description:
 *   Read 32-bit R1/R5/R6/R7 response from SD_RSP10.
 *
 ****************************************************************************/

static int rzv_sdhi_recv_r1(FAR struct sdio_dev_s *dev, uint32_t cmd,
                            uint32_t *R1)
{
  FAR struct rzv_sdhi_dev_s *priv = (FAR struct rzv_sdhi_dev_s *)dev;

  if (R1 == NULL)
    {
      return -EINVAL;
    }

  *R1 = getreg32(RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_RSP10_OFFSET));

  mcinfo("SDHI%d: recv_r1 R1=0x%08" PRIx32 "\n", priv->slot, *R1);
  return OK;
}

/****************************************************************************
 * Name: rzv_sdhi_recv_r2 (task 2.5)
 *
 * Description:
 *   Read 128-bit R2 (CID/CSD) response.
 *   SDHI stores: RSP76=[127:96], RSP54=[95:64], RSP32=[63:32], RSP10=[31:0].
 *   NuttX expects R2[0]=[127:96], R2[1]=[95:64], R2[2]=[63:32], R2[3]=[31:0].
 *
 ****************************************************************************/

static int rzv_sdhi_recv_r2(FAR struct sdio_dev_s *dev, uint32_t cmd,
                            uint32_t R2[4])
{
  FAR struct rzv_sdhi_dev_s *priv = (FAR struct rzv_sdhi_dev_s *)dev;

  if (R2 == NULL)
    {
      return -EINVAL;
    }

  R2[0] = getreg32(RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_RSP76_OFFSET));
  R2[1] = getreg32(RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_RSP54_OFFSET));
  R2[2] = getreg32(RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_RSP32_OFFSET));
  R2[3] = getreg32(RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_RSP10_OFFSET));

  mcinfo("SDHI%d: recv_r2 [0]=0x%08" PRIx32 " [1]=0x%08" PRIx32
         " [2]=0x%08" PRIx32 " [3]=0x%08" PRIx32 "\n",
         priv->slot, R2[0], R2[1], R2[2], R2[3]);
  return OK;
}

/****************************************************************************
 * Name: rzv_sdhi_recv_r3 (task 2.5)
 *
 * Description:
 *   Read 32-bit R3 (OCR) from SD_RSP10.
 *
 ****************************************************************************/

static int rzv_sdhi_recv_r3(FAR struct sdio_dev_s *dev, uint32_t cmd,
                            uint32_t *R3)
{
  FAR struct rzv_sdhi_dev_s *priv = (FAR struct rzv_sdhi_dev_s *)dev;

  if (R3 == NULL)
    {
      return -EINVAL;
    }

  *R3 = getreg32(RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_RSP10_OFFSET));

  mcinfo("SDHI%d: recv_r3 R3=0x%08" PRIx32 "\n", priv->slot, *R3);
  return OK;
}

/****************************************************************************
 * Name: rzv_sdhi_recv_r4 (task 2.5)
 ****************************************************************************/

static int rzv_sdhi_recv_r4(FAR struct sdio_dev_s *dev, uint32_t cmd,
                            uint32_t *R4)
{
  FAR struct rzv_sdhi_dev_s *priv = (FAR struct rzv_sdhi_dev_s *)dev;

  if (R4 == NULL)
    {
      return -EINVAL;
    }

  *R4 = getreg32(RZV_SDHI_REG32(priv->base, RZV_SDHI_SD_RSP10_OFFSET));
  return OK;
}

/****************************************************************************
 * Name: rzv_sdhi_recv_r5 (task 2.5)
 ****************************************************************************/

static int rzv_sdhi_recv_r5(FAR struct sdio_dev_s *dev, uint32_t cmd,
                            uint32_t *R5)
{
  return rzv_sdhi_recv_r1(dev, cmd, R5);
}

/****************************************************************************
 * Name: rzv_sdhi_recv_r6 (task 2.5)
 ****************************************************************************/

static int rzv_sdhi_recv_r6(FAR struct sdio_dev_s *dev, uint32_t cmd,
                            uint32_t *R6)
{
  return rzv_sdhi_recv_r1(dev, cmd, R6);
}

/****************************************************************************
 * Name: rzv_sdhi_recv_r7 (task 2.5)
 ****************************************************************************/

static int rzv_sdhi_recv_r7(FAR struct sdio_dev_s *dev, uint32_t cmd,
                            uint32_t *R7)
{
  return rzv_sdhi_recv_r1(dev, cmd, R7);
}

/****************************************************************************
 * Name: rzv_sdhi_waitenable
 *
 * Description:
 *   Arm the watchdog timer for the event-wait timeout.  The ISR will post
 *   the semaphore directly; the watchdog fires as fallback.
 *
 ****************************************************************************/

static void rzv_sdhi_waitenable(FAR struct sdio_dev_s *dev,
                                sdio_eventset_t eventset, uint32_t timeout)
{
  FAR struct rzv_sdhi_dev_s *priv = (FAR struct rzv_sdhi_dev_s *)dev;

  priv->waitevents = eventset;
  priv->wkupevent  = 0;

  wd_start(&priv->waitwdog, timeout, rzv_sdhi_eventtimeout,
           (wdparm_t)priv);
}

/****************************************************************************
 * Name: rzv_sdhi_eventwait
 *
 * Description:
 *   Block until the ISR posts the semaphore (or watchdog fires).
 *
 ****************************************************************************/

static sdio_eventset_t rzv_sdhi_eventwait(FAR struct sdio_dev_s *dev)
{
  FAR struct rzv_sdhi_dev_s *priv = (FAR struct rzv_sdhi_dev_s *)dev;
  int ret;

  ret = nxsem_wait_uninterruptible(&priv->waitsem);
  wd_cancel(&priv->waitwdog);

  if (ret < 0)
    {
      return SDIOWAIT_ERROR;
    }

  return priv->wkupevent;
}

/****************************************************************************
 * Name: rzv_sdhi_callbackenable
 ****************************************************************************/

static void rzv_sdhi_callbackenable(FAR struct sdio_dev_s *dev,
                                    sdio_eventset_t eventset)
{
  FAR struct rzv_sdhi_dev_s *priv = (FAR struct rzv_sdhi_dev_s *)dev;

  priv->cbevents = eventset;
}

/****************************************************************************
 * Name: rzv_sdhi_registercallback
 ****************************************************************************/

static int rzv_sdhi_registercallback(FAR struct sdio_dev_s *dev,
                                     worker_t callback, void *arg)
{
  FAR struct rzv_sdhi_dev_s *priv = (FAR struct rzv_sdhi_dev_s *)dev;

  priv->callback = callback;
  priv->cbarg    = arg;
  return OK;
}

/****************************************************************************
 * DMA stubs
 ****************************************************************************/

#ifdef CONFIG_SDIO_DMA
static int rzv_sdhi_dmarecvsetup(FAR struct sdio_dev_s *dev,
                                 FAR uint8_t *buffer, size_t buflen)
{
  /* configure integrated DMAC RX (CC_EXT_MODE + DM_CM_DTRAN_*) */

  (void)buffer;
  (void)buflen;
  return -ENOSYS;
}

static int rzv_sdhi_dmasendsetup(FAR struct sdio_dev_s *dev,
                                 FAR const uint8_t *buffer, size_t buflen)
{
  /* configure integrated DMAC TX */

  (void)buffer;
  (void)buflen;
  return -ENOSYS;
}
#endif /* CONFIG_SDIO_DMA */

/****************************************************************************
 * Name: rzv_sdhi_bind_ops
 *
 * Description:
 *   Assign all SDIO function pointers into the sdio_dev_s embedded in priv.
 *
 ****************************************************************************/

static void rzv_sdhi_bind_ops(FAR struct rzv_sdhi_dev_s *priv)
{
  FAR struct sdio_dev_s *dev = &priv->dev;

  dev->reset          = rzv_sdhi_reset;
  dev->capabilities   = rzv_sdhi_capabilities;
  dev->status         = rzv_sdhi_status;
  dev->widebus        = rzv_sdhi_widebus;
  dev->clock          = rzv_sdhi_clock;
  dev->attach         = rzv_sdhi_attach;
  dev->sendcmd        = rzv_sdhi_sendcmd;
#ifdef CONFIG_SDIO_BLOCKSETUP
  dev->blocksetup     = rzv_sdhi_blocksetup;
#endif
  dev->recvsetup      = rzv_sdhi_recvsetup;
  dev->sendsetup      = rzv_sdhi_sendsetup;
  dev->cancel         = rzv_sdhi_cancel;
  dev->waitresponse   = rzv_sdhi_waitresponse;
  dev->recv_r1        = rzv_sdhi_recv_r1;
  dev->recv_r2        = rzv_sdhi_recv_r2;
  dev->recv_r3        = rzv_sdhi_recv_r3;
  dev->recv_r4        = rzv_sdhi_recv_r4;
  dev->recv_r5        = rzv_sdhi_recv_r5;
  dev->recv_r6        = rzv_sdhi_recv_r6;
  dev->recv_r7        = rzv_sdhi_recv_r7;
  dev->waitenable     = rzv_sdhi_waitenable;
  dev->eventwait      = rzv_sdhi_eventwait;
  dev->callbackenable = rzv_sdhi_callbackenable;
  dev->registercallback = rzv_sdhi_registercallback;
#ifdef CONFIG_SDIO_DMA
  dev->dmarecvsetup   = rzv_sdhi_dmarecvsetup;
  dev->dmasendsetup   = rzv_sdhi_dmasendsetup;
#endif
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_sdhi_initialize (task 2.10)
 *
 * Description:
 *   Initialize the RZ/V2H SDHI controller for the specified slot.
 *
 *   Sequence:
 *     1. Enable SDHI CPG clock via rzv_clock_enable_sdhi(slot)
 *     2. Release reset via rzv_reset_release_sdhi(slot)
 *     3. Init semaphore
 *     4. Bind function pointers
 *     5. Call rzv_sdhi_reset() to configure controller state
 *
 *   CPG IDs (see rzv_clock.h for the authoritative decode):
 *     SDHI0 IMCLK: CLKON domain 10 bit 3
 *     SDHI0 IXRST: RST   domain 10 bit 7
 *
 * Input Parameters:
 *   slot - 0 = SD0 (RDK card slot), 1 = SD1, 2 = SD2
 *
 * Returned Value:
 *   Pointer to struct sdio_dev_s on success; NULL on failure.
 *
 ****************************************************************************/

FAR struct sdio_dev_s *rzv_sdhi_initialize(int slot)
{
  FAR struct rzv_sdhi_dev_s *priv;
  int ret;

  if (slot < 0 || slot >= RZV_SDHI_NSLOTS)
    {
      mcerr("rzv_sdhi: invalid slot %d\n", slot);
      return NULL;
    }

  priv = &g_rzv_sdhi_dev[slot];

  if (priv->initialized)
    {
      return &priv->dev;
    }

  /* Zero state */

  memset(priv, 0, sizeof(struct rzv_sdhi_dev_s));

  priv->slot      = slot;
  priv->base      = g_rzv_sdhi_base[slot];
  priv->blocksize = 512;
  priv->nblocks   = 1;

  /* Wire all SDIO function pointers */

  rzv_sdhi_bind_ops(priv);

  /* Initialise the wait semaphore (binary, starts locked) */

  nxsem_init(&priv->waitsem, 0, 0);

  /* Step 1: Enable SDHI CPG clock (CLKON domain 10, bit 3 = IMCLK).
   * IMCLK2/CLK_HS/ACLK are provided by the boot firmware (see file header).
   */

  ret = rzv_clock_enable_sdhi(slot);
  if (ret < 0)
    {
      /* Non-fatal: u-boot may have already enabled clocks.  Log a warning
       * so silent clock-not-enabled is not masked; if clock was not enabled
       * by u-boot, every command will time out with no clear diagnostic.
       */

      mcerr("SDHI%d: CPG clock enable failed: %d (continuing -- "
            "u-boot may have pre-enabled)\n", slot, ret);
    }

  /* Step 2: Release SDHI reset (RST domain 10, bit 7). */

  ret = rzv_reset_release_sdhi(slot);
  if (ret < 0)
    {
      mcerr("rzv_sdhi: reset release failed for slot %d: %d\n", slot, ret);
      /* Non-fatal -- continue */
    }

  /* Step 3: Software reset of SDHI IP and initial configuration */

  rzv_sdhi_reset(&priv->dev);

  priv->initialized = true;

  mcinfo("rzv_sdhi: slot %d initialized, base=0x%08" PRIxPTR "\n",
         slot, priv->base);

  return &priv->dev;
}

#endif /* CONFIG_RZV_SDHI */
