/****************************************************************************
 * arch/arm/src/rzv/rzv_wdt.c
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

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/irq.h>
#include <nuttx/clock.h>
#include <nuttx/timers/watchdog.h>

#include "arm_internal.h"
#include "chip.h"
#include "rzv_wdt.h"
#include "rzv_clock.h"
#include "rzv_icu.h"
#include "hardware/rzv_wdt.h"
#include "hardware/rzv_cpg.h"
#include "hardware/rzv_sysc.h"

#ifdef CONFIG_RZV_WDT

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Debug output configuration */

#ifdef CONFIG_DEBUG_WATCHDOG_INFO
#  define wdinfo  _info
#else
#  define wdinfo(x...)
#endif

#ifdef CONFIG_DEBUG_WATCHDOG_WARN
#  define wdwarn  _warn
#else
#  define wdwarn(x...)
#endif

#ifdef CONFIG_DEBUG_WATCHDOG_ERROR
#  define wderr   _err
#else
#  define wderr(x...)
#endif

/* Default timeout values */

#define WDT_MAXTIMEOUT            60000     /* 60 seconds max timeout (ms) */
#define WDT_MINTIMEOUT            1         /* 1 ms min timeout */

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* WDT Device State */

struct rzv_wdt_priv_s
{
  const struct watchdog_ops_s *ops;   /* Standard watchdog operations */
  uintptr_t base;                     /* WDT register base address */
  uint32_t  timeout;                  /* Configured timeout value (ms) */
  uint32_t  frequency;                /* WDT clock frequency after divider */
  uint8_t   cks;                      /* Clock divider setting */
  uint8_t   tops;                     /* Timeout period setting */
  uint8_t   channel;                  /* WDT channel (0-3) */
  int       irq;                      /* IRQ number if using NMI mode */
  xcpt_t    handler;                  /* Watchdog interrupt handler */
  void      *arg;                     /* Handler argument */
  bool      started;                  /* Watchdog started flag */
  bool      configured;               /* Configuration completed flag */
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Register access */

static inline uint8_t rzv_wdt_getreg8(struct rzv_wdt_priv_s *priv,
                                      unsigned int offset);
static inline void rzv_wdt_putreg8(struct rzv_wdt_priv_s *priv,
                                   unsigned int offset, uint8_t value);
static inline uint16_t rzv_wdt_getreg16(struct rzv_wdt_priv_s *priv,
                                        unsigned int offset);
static inline void rzv_wdt_putreg16(struct rzv_wdt_priv_s *priv,
                                    unsigned int offset, uint16_t value);

/* Clock and initialization */

static int rzv_wdt_clock_enable(uint8_t channel);
static void rzv_wdt_refresh_sequence(struct rzv_wdt_priv_s *priv);

/* WDT Operations */

static int rzv_wdt_start(struct watchdog_lowerhalf_s *lower);
static int rzv_wdt_stop(struct watchdog_lowerhalf_s *lower);
static int rzv_wdt_keepalive(struct watchdog_lowerhalf_s *lower);
static int rzv_wdt_getstatus(struct watchdog_lowerhalf_s *lower,
                             struct watchdog_status_s *status);
static int rzv_wdt_settimeout(struct watchdog_lowerhalf_s *lower,
                              uint32_t timeout);
static xcpt_t rzv_wdt_capture(struct watchdog_lowerhalf_s *lower,
                              xcpt_t handler);
static int rzv_wdt_ioctl(struct watchdog_lowerhalf_s *lower,
                         int cmd, unsigned long arg);

/* Interrupt handling */

static int rzv_wdt_interrupt(int irq, void *context, void *arg);

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Watchdog Operations */

static const struct watchdog_ops_s g_wdt_ops =
{
  .start      = rzv_wdt_start,
  .stop       = rzv_wdt_stop,
  .keepalive  = rzv_wdt_keepalive,
  .getstatus  = rzv_wdt_getstatus,
  .settimeout = rzv_wdt_settimeout,
  .capture    = rzv_wdt_capture,
  .ioctl      = rzv_wdt_ioctl,
};

/* WDT Device instances */

static struct rzv_wdt_priv_s g_wdt_priv[RZV_WDT_MAX_CHANNELS];
static struct watchdog_lowerhalf_s g_wdt_dev[RZV_WDT_MAX_CHANNELS];

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_wdt_getreg8
 ****************************************************************************/

static inline uint8_t rzv_wdt_getreg8(struct rzv_wdt_priv_s *priv,
                                      unsigned int offset)
{
  return getreg8(priv->base + offset);
}

/****************************************************************************
 * Name: rzv_wdt_putreg8
 ****************************************************************************/

static inline void rzv_wdt_putreg8(struct rzv_wdt_priv_s *priv,
                                   unsigned int offset, uint8_t value)
{
  putreg8(value, priv->base + offset);
}

/****************************************************************************
 * Name: rzv_wdt_getreg16
 ****************************************************************************/

static inline uint16_t rzv_wdt_getreg16(struct rzv_wdt_priv_s *priv,
                                        unsigned int offset)
{
  return getreg16(priv->base + offset);
}

/****************************************************************************
 * Name: rzv_wdt_putreg16
 ****************************************************************************/

static inline void rzv_wdt_putreg16(struct rzv_wdt_priv_s *priv,
                                    unsigned int offset, uint16_t value)
{
  putreg16(value, priv->base + offset);
}

/****************************************************************************
 * Name: rzv_wdt_clock_enable
 ****************************************************************************/

/* Per-channel SYS_WDTx_CTRL absolute address (channel 1 is at 0x0C0C, not
 * sequential — see hardware/rzv_sysc.h:190-193).
 */

static uintptr_t rzv_wdt_sysc_ctrl(uint8_t channel)
{
  switch (channel)
    {
      case 0: return RZV_SYSC_SYS_WDT0_CTRL;
      case 1: return RZV_SYSC_SYS_WDT1_CTRL;
      case 2: return RZV_SYSC_SYS_WDT2_CTRL;
      case 3: return RZV_SYSC_SYS_WDT3_CTRL;
      default: return 0;
    }
}

/****************************************************************************
 * Name: rzv_wdt_clock_enable
 *
 * Description:
 *   Turn on CPG clock gates (CLKP + LOCO), wait for clock-monitor to confirm,
 *   then deassert the WDT reset and wait for reset-monitor. Mirrors FSP
 *   R_BSP_MODULE_START_FSP_IP_WDT (bsp_override.h:1382). MSTOP is a no-op on
 *   RZ/V2H for WDT.
 *
 ****************************************************************************/

static int rzv_wdt_clock_enable(uint8_t channel)
{
  uint32_t clkp_bit  = RZV_CPG_CLKON_WDT_CLKP_BIT(channel);
  uint32_t loco_bit  = RZV_CPG_CLKON_WDT_LOCO_BIT(channel);
  uintptr_t clkp_reg = RZV_CPG_CLKON(RZV_CPG_CLKON_WDT_CLKP_M(channel));
  uintptr_t loco_reg = RZV_CPG_CLKON(RZV_CPG_CLKON_WDT_LOCO_M(channel));
  uintptr_t clkmon   = RZV_CPG_CLKMON(RZV_CPG_CLKMON_WDT_M);
  uint32_t rst_bit   = RZV_CPG_RST_WDT_BIT(channel);
  uintptr_t rstmon   = RZV_CPG_RSTMON(RZV_CPG_RSTMON_WDT_M);
  int timeout;

  /* Enable CLKP and LOCO gates (with WEN). */

  putreg32((clkp_bit << RZV_CPG_CLK_WEN_SHIFT) | clkp_bit, clkp_reg);
  putreg32((loco_bit << RZV_CPG_CLK_WEN_SHIFT) | loco_bit, loco_reg);

  /* Wait for clock monitor to confirm. CLKMON_2 carries WDT bits for
   * ch=0..2; for ch=3 LOCO/CLKP live elsewhere — best-effort wait, then
   * proceed (FSP itself only polls CLKMON_2).
   */

  timeout = 1000;
  while (timeout-- > 0)
    {
      uint32_t mon = getreg32(clkmon);
      if ((mon & (clkp_bit | loco_bit)) == (clkp_bit | loco_bit))
        {
          break;
        }
    }

  /* Deassert reset (with WEN). */

  putreg32((rst_bit << RZV_CPG_CLK_WEN_SHIFT) | rst_bit,
           RZV_CPG_RST(RZV_CPG_RST_WDT_M));

  /* Wait for reset monitor (RSTMON bit reads 0 when reset is released). */

  timeout = 1000;
  while (timeout-- > 0)
    {
      if ((getreg32(rstmon) & RZV_CPG_RSTMON_WDT_BIT(channel)) == 0)
        {
          wdinfo("WDT%d clock+reset released\n", channel);
          return OK;
        }
    }

  wderr("ERROR: WDT%d reset monitor timeout\n", channel);
  return -ETIMEDOUT;
}

/****************************************************************************
 * Name: rzv_wdt_refresh_sequence
 *
 * Description:
 *   Execute the WDT refresh sequence. The RZV2H WDT requires a two-step
 *   refresh to prevent accidental refreshes:
 *   1. Write 0x00 to WDTRR
 *   2. Write 0xFF to WDTRR
 *
 ****************************************************************************/

static void rzv_wdt_refresh_sequence(struct rzv_wdt_priv_s *priv)
{
  irqstate_t flags;

  flags = enter_critical_section();

  /* Step 1: Write 0x00 */

  rzv_wdt_putreg8(priv, RZV_WDT_WDTRR_OFFSET, 0x00);

  /* Step 2: Write 0xFF */

  rzv_wdt_putreg8(priv, RZV_WDT_WDTRR_OFFSET, 0xFF);

  leave_critical_section(flags);
}

/****************************************************************************
 * Name: rzv_wdt_calculate_timeout
 ****************************************************************************/

static int rzv_wdt_calculate_timeout(struct rzv_wdt_priv_s *priv,
                                     uint32_t timeout_ms)
{
  uint32_t pclk;
  uint32_t best_timeout = 0;
  /* WDT IP count clock is OSCCLK (24 MHz on RZ/V2H EVK), not P0CLK.
   * Matches FSP r_wdt.c which uses R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_OSCCLK).
   */
  int best_tops = -1;
  int best_cks = -1;
  int i;
  int j;

  /* Clock divider values */

  const uint32_t cks_div[] = {4, 16, 32, 64, 128, 256, 512, 2048, 8192};
  const uint8_t cks_val[] =
    {
      0x1,  /* PCLK/4 */
      0x2,  /* PCLK/16 */
      0x3,  /* PCLK/32 */
      0x4,  /* PCLK/64 */
      0xF,  /* PCLK/128 */
      0x5,  /* PCLK/256 */
      0x6,  /* PCLK/512 */
      0x7,  /* PCLK/2048 */
      0x8   /* PCLK/8192 */
    };

  /* Timeout period cycles */

  const uint32_t tops_cycles[] = {1024, 4096, 8192, 16384};
  const uint8_t tops_val[] = {0x0, 0x1, 0x2, 0x3};

  /* WDT count clock is OSCCLK (24 MHz), not P0CLK. */

  pclk = RZV_CLOCK_OSCCLK_HZ;
  wdinfo("WDT OSCCLK frequency: %lu Hz\n", (unsigned long)pclk);

  /* Find the best CKS and TOPS combination to match the requested timeout
   * timeout (ms) = (cycles * 1000) / (PCLK / div)
   */

  for (i = 0; i < 9; i++)
    {
      for (j = 0; j < 4; j++)
        {
          uint64_t t;

          /* Calculate timeout in milliseconds using 64-bit to avoid overflow */

          t = ((uint64_t)tops_cycles[j] * (uint64_t)cks_div[i] * 1000ULL) /
              (uint64_t)pclk;

          /* Check if this combination meets or exceeds requested timeout */

          if (t >= timeout_ms)
            {
              /* Use the smallest timeout that meets the requirement */

              if (best_timeout == 0 || t < best_timeout)
                {
                  best_timeout = (uint32_t)t;
                  best_tops = j;
                  best_cks = i;
                }
            }
        }
    }

  if (best_tops < 0 || best_cks < 0)
    {
      /* Timeout too long, use maximum */

      best_tops = 3;
      best_cks = 5;
      best_timeout = ((uint64_t)tops_cycles[3] * (uint64_t)cks_div[5] *
                      1000ULL) / (uint64_t)pclk;
      wdwarn("Requested timeout %lu ms too long, using max %lu ms\n",
             (unsigned long)timeout_ms, (unsigned long)best_timeout);
    }

  /* Store configuration */

  priv->timeout = best_timeout;
  priv->tops = tops_val[best_tops];
  priv->cks = cks_val[best_cks];
  priv->frequency = pclk / cks_div[best_cks];

  wdinfo("Selected timeout=%lu ms, cks=0x%x (div=%u), tops=0x%x (cycles=%u)\n",
         (unsigned long)priv->timeout, priv->cks, cks_div[best_cks],
         priv->tops, tops_cycles[best_tops]);

  return OK;
}

/****************************************************************************
 * Name: rzv_wdt_configure
 *
 * Description:
 *   Configure WDT registers. This must be called BEFORE the first refresh.
 *   WDTCR is write-once after the first refresh in register-start mode.
 *
 ****************************************************************************/

static int rzv_wdt_configure(struct rzv_wdt_priv_s *priv)
{
  uint16_t wdtcr;
  uint16_t verify;

  if (priv->configured)
    {
      wdwarn("WDT%d already configured (write-once register)\n",
             priv->channel);
      return -EBUSY;
    }

  /* Check if WDT is already running (auto-start mode) */

  uint16_t wdtsr = rzv_wdt_getreg16(priv, RZV_WDT_WDTSR_OFFSET);
  if (wdtsr & (WDT_WDTSR_UNDFF | WDT_WDTSR_REFEF))
    {
      wdwarn("WDT%d status flags set (0x%04x) - may be in auto-start mode\n",
             priv->channel, wdtsr);
      wdwarn("Runtime configuration may not take effect\n");

      /* Clear status flags */

      rzv_wdt_putreg16(priv, RZV_WDT_WDTSR_OFFSET,
                       wdtsr & ~(WDT_WDTSR_UNDFF | WDT_WDTSR_REFEF));
    }

  /* Configure WDTCR: Clock divider, Timeout period, Window mode
   * RPSS = 11, RPES = 11: 100% window (no window restriction)
   */

  wdtcr = ((priv->cks << WDT_WDTCR_CKS_SHIFT) & WDT_WDTCR_CKS_MASK) |
          ((priv->tops << WDT_WDTCR_TOPS_SHIFT) & WDT_WDTCR_TOPS_MASK) |
          ((0x3 << WDT_WDTCR_RPES_SHIFT) & WDT_WDTCR_RPES_MASK) |
          ((0x3 << WDT_WDTCR_RPSS_SHIFT) & WDT_WDTCR_RPSS_MASK);

  rzv_wdt_putreg16(priv, RZV_WDT_WDTCR_OFFSET, wdtcr);

  /* Verify write succeeded */

  verify = rzv_wdt_getreg16(priv, RZV_WDT_WDTCR_OFFSET);
  if (verify != wdtcr)
    {
      wderr("ERROR: WDTCR write failed (wrote 0x%04x, read 0x%04x)\n",
            wdtcr, verify);
      return -EIO;
    }

  /* Configure WDTRCR: Reset or interrupt mode */

#ifdef CONFIG_RZV_WDT_INTERRUPT_MODE
  /* NMI/Interrupt mode */

  rzv_wdt_putreg8(priv, RZV_WDT_WDTRCR_OFFSET, WDT_WDTRCR_RSTIRQS);
  wdinfo("WDT%d configured for NMI mode\n", priv->channel);
#else
  /* Reset mode (default) */

  rzv_wdt_putreg8(priv, RZV_WDT_WDTRCR_OFFSET, 0);
  wdinfo("WDT%d configured for reset mode\n", priv->channel);
#endif

  /* Route WDT underflow to system reset (reset mode only). FSP equivalent:
   * R_BSP_WDT_SYSTEM_RESET_ENABLE (bsp_wdt.h:55).
   */

#ifndef CONFIG_RZV_WDT_INTERRUPT_MODE
  putreg32(RZV_CPG_ERRORRST_SEL2_BIT(priv->channel) |
           RZV_CPG_ERRORRST_SEL2_WEN(priv->channel),
           RZV_CPG_ERRORRST_SEL(RZV_CPG_ERRORRST_SEL2_M));
#endif

  /* Release the counter halt latch in SYSC so the WDT actually counts.
   * Equivalent to FSP R_BSP_WDT_COUNTING_ENABLE (bsp_wdt.h:38).
   * Write WDTSTOPMASK (WEN=1) with bp_halted=0.
   */

  {
    uintptr_t ctrl = rzv_wdt_sysc_ctrl(priv->channel);
    if (ctrl != 0)
      {
        putreg32(SYS_WDT_CTRL_WDTSTOPMASK, ctrl);
      }
  }

  priv->configured = true;

  wdinfo("WDT%d configured: WDTCR=0x%04x\n", priv->channel, wdtcr);

  return OK;
}

/****************************************************************************
 * Name: rzv_wdt_start
 ****************************************************************************/

static int rzv_wdt_start(struct watchdog_lowerhalf_s *lower)
{
  struct rzv_wdt_priv_s *priv = (struct rzv_wdt_priv_s *)lower;
  int ret;

  if (lower == NULL)
    {
      return -EINVAL;
    }

  wdinfo("Starting WDT%d\n", priv->channel);

  if (priv->started)
    {
      wdinfo("WDT%d already started\n", priv->channel);
      return OK;
    }

  /* Configure if not already done */

  if (!priv->configured)
    {
      ret = rzv_wdt_configure(priv);
      if (ret < 0)
        {
          wderr("ERROR: Failed to configure WDT%d: %d\n",
                priv->channel, ret);
          return ret;
        }
    }

  /* Execute first refresh sequence to start the watchdog */

  rzv_wdt_refresh_sequence(priv);

  priv->started = true;

  wdinfo("WDT%d started successfully\n", priv->channel);

  return OK;
}

/****************************************************************************
 * Name: rzv_wdt_stop
 ****************************************************************************/

static int rzv_wdt_stop(struct watchdog_lowerhalf_s *lower)
{
  struct rzv_wdt_priv_s *priv = (struct rzv_wdt_priv_s *)lower;

  if (lower == NULL)
    {
      return -EINVAL;
    }

  wdinfo("Stopping WDT%d\n", priv->channel);

  /* Halt the counter via SYSC: set bp_halted=1 with WEN=1.
   * Per FSP bsp_wdt.h R_BSP_WDT_COUNTING_ENABLE, writing bp_halted=1
   * with the WDTSTOPMASK WEN bit set freezes the WDT counter immediately.
   */

  {
    uintptr_t ctrl = rzv_wdt_sysc_ctrl(priv->channel);
    if (ctrl != 0)
      {
        putreg32(SYS_WDT_CTRL_BP_HALTED | SYS_WDT_CTRL_WDTSTOPMASK, ctrl);
      }
  }

  priv->started = false;
  return OK;
}

/****************************************************************************
 * Name: rzv_wdt_keepalive
 ****************************************************************************/

static int rzv_wdt_keepalive(struct watchdog_lowerhalf_s *lower)
{
  struct rzv_wdt_priv_s *priv = (struct rzv_wdt_priv_s *)lower;

  if (lower == NULL)
    {
      return -EINVAL;
    }

  if (!priv->started)
    {
      wdwarn("WDT%d keepalive called but not started\n", priv->channel);
      return -EINVAL;
    }

  wdinfo("WDT%d keepalive\n", priv->channel);

  /* Execute refresh sequence */

  rzv_wdt_refresh_sequence(priv);

  return OK;
}

/****************************************************************************
 * Name: rzv_wdt_getstatus
 ****************************************************************************/

static int rzv_wdt_getstatus(struct watchdog_lowerhalf_s *lower,
                             struct watchdog_status_s *status)
{
  struct rzv_wdt_priv_s *priv = (struct rzv_wdt_priv_s *)lower;
  uint16_t wdtsr;

  if (lower == NULL || status == NULL)
    {
      return -EINVAL;
    }

  /* Get status register */

  wdtsr = rzv_wdt_getreg16(priv, RZV_WDT_WDTSR_OFFSET);

  /* Return status */

  status->flags = 0;
  if (priv->started)
    {
      status->flags |= WDFLAGS_ACTIVE;
    }

  if (priv->handler != NULL)
    {
      status->flags |= WDFLAGS_CAPTURE;
    }

  status->timeout = priv->timeout;

  /* Calculate time left until timeout
   * The counter counts DOWN from max_count to 0
   */

  if (priv->started && priv->frequency > 0)
    {
      uint16_t counter = wdtsr & WDT_WDTSR_CNTVAL_MASK;
      uint64_t timeleft_ms;

      /* Counter value IS the time remaining */

      timeleft_ms = ((uint64_t)counter * 1000ULL) / (uint64_t)priv->frequency;

      if (timeleft_ms > UINT32_MAX)
        {
          status->timeleft = UINT32_MAX;
        }
      else
        {
          status->timeleft = (uint32_t)timeleft_ms;
        }
    }
  else
    {
      status->timeleft = 0;
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_wdt_settimeout
 ****************************************************************************/

static int rzv_wdt_settimeout(struct watchdog_lowerhalf_s *lower,
                              uint32_t timeout)
{
  struct rzv_wdt_priv_s *priv = (struct rzv_wdt_priv_s *)lower;
  int ret;

  if (lower == NULL)
    {
      return -EINVAL;
    }

  if (timeout < WDT_MINTIMEOUT || timeout > WDT_MAXTIMEOUT)
    {
      wderr("ERROR: Timeout out of range: %lu\n", (unsigned long)timeout);
      return -ERANGE;
    }

  /* Check if already started - cannot reconfigure after first refresh */

  if (priv->started)
    {
      wderr("ERROR: Cannot change timeout after WDT started (write-once)\n");
      return -EBUSY;
    }

  wdinfo("Setting WDT%d timeout: %lu ms\n", priv->channel,
         (unsigned long)timeout);

  /* Calculate and store timeout parameters */

  ret = rzv_wdt_calculate_timeout(priv, timeout);
  if (ret < 0)
    {
      wderr("ERROR: Failed to calculate timeout: %d\n", ret);
      return ret;
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_wdt_capture
 ****************************************************************************/

static xcpt_t rzv_wdt_capture(struct watchdog_lowerhalf_s *lower,
                              xcpt_t handler)
{
  struct rzv_wdt_priv_s *priv = (struct rzv_wdt_priv_s *)lower;
  xcpt_t oldhandler;

  if (lower == NULL)
    {
      return NULL;
    }

  wdinfo("WDT%d capture handler: %p\n", priv->channel, handler);

#ifdef CONFIG_RZV_WDT_INTERRUPT_MODE
  oldhandler = priv->handler;
  priv->handler = handler;
  priv->arg = priv;

  /* Enable or disable IRQ based on handler */

  if (handler != NULL && priv->irq >= 0)
    {
      up_enable_irq(priv->irq);
      wdinfo("WDT%d IRQ %d enabled\n", priv->channel, priv->irq);
    }
  else if (handler == NULL && priv->irq >= 0)
    {
      up_disable_irq(priv->irq);
      wdinfo("WDT%d IRQ %d disabled\n", priv->channel, priv->irq);
    }

  return oldhandler;
#else
  wdwarn("WDT%d capture requires CONFIG_RZV_WDT_INTERRUPT_MODE\n",
         priv->channel);
  return NULL;
#endif
}

/****************************************************************************
 * Name: rzv_wdt_ioctl
 ****************************************************************************/

static int rzv_wdt_ioctl(struct watchdog_lowerhalf_s *lower,
                         int cmd, unsigned long arg)
{
  /* No special IOCTL commands supported yet */

  return -ENOTTY;
}

/****************************************************************************
 * Name: rzv_wdt_interrupt
 ****************************************************************************/

static int rzv_wdt_interrupt(int irq, void *context, void *arg)
{
  struct rzv_wdt_priv_s *priv = (struct rzv_wdt_priv_s *)arg;
  uint16_t wdtsr;

  DEBUGASSERT(priv != NULL);

  wdwarn("WDT%d interrupt! (underflow or refresh error)\n", priv->channel);

  /* Get and clear status flags */

  wdtsr = rzv_wdt_getreg16(priv, RZV_WDT_WDTSR_OFFSET);

  if (wdtsr & WDT_WDTSR_UNDFF)
    {
      wderr("WDT%d UNDERFLOW detected\n", priv->channel);
    }

  if (wdtsr & WDT_WDTSR_REFEF)
    {
      wderr("WDT%d REFRESH ERROR detected\n", priv->channel);
    }

  /* Clear interrupt flags. Hardware does not always clear in the same cycle;
   * loop with a bounded retry until flags read back as 0 (matches FSP
   * r_wdt.c status-clear loop).
   */

  {
    int retries = 16;
    while (retries-- > 0)
      {
        uint16_t cur = rzv_wdt_getreg16(priv, RZV_WDT_WDTSR_OFFSET);
        if ((cur & (WDT_WDTSR_UNDFF | WDT_WDTSR_REFEF)) == 0)
          {
            break;
          }
        rzv_wdt_putreg16(priv, RZV_WDT_WDTSR_OFFSET,
                         cur & ~(WDT_WDTSR_UNDFF | WDT_WDTSR_REFEF));
      }
  }

  /* Call user handler if registered */

  if (priv->handler != NULL)
    {
      priv->handler(irq, context, priv->arg);
    }

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_wdt_initialize
 *
 * Description:
 *   Initialize the WDT watchdog timer. The watchdog timer is initialized and
 *   registered as 'devpath'. The initial state of the watchdog timer is
 *   disabled.
 *
 * Input Parameters:
 *   devpath - The full path to the watchdog. This should be of the form
 *             /dev/watchdog0
 *   channel - The WDT channel number (0..RZV_WDT_MAX_CHANNELS-1)
 *
 * Returned Value:
 *   Zero (OK) is returned on success; a negated errno value is returned on
 *   any failure.
 *
 ****************************************************************************/

int rzv_wdt_initialize(FAR const char *devpath, int channel)
{
  struct rzv_wdt_priv_s *priv;
  int ret;

  wdinfo("Initializing WDT%d at %s\n", channel, devpath);

  /* Validate channel */

  if (channel < 0 || channel >= RZV_WDT_MAX_CHANNELS)
    {
      wderr("ERROR: Invalid channel %d (max %d)\n",
            channel, RZV_WDT_MAX_CHANNELS - 1);
      return -EINVAL;
    }

  if (devpath == NULL)
    {
      wderr("ERROR: Invalid devpath\n");
      return -EINVAL;
    }

  /* Get device instance */

  priv = &g_wdt_priv[channel];
  memset(priv, 0, sizeof(struct rzv_wdt_priv_s));

  /* Set base address based on channel */

  switch (channel)
    {
      case 0:
        priv->base = RZV_WDT0_BASE;
        break;
      case 1:
        priv->base = RZV_WDT1_BASE;
        break;
      case 2:
        priv->base = RZV_WDT2_BASE;
        break;
      case 3:
        priv->base = RZV_WDT3_BASE;
        break;
      default:
        wderr("ERROR: Invalid channel %d\n", channel);
        return -EINVAL;
    }

  /* Initialize driver state structure */

  priv->ops = &g_wdt_ops;
  priv->channel = channel;
  priv->started = false;
  priv->configured = false;
  priv->handler = NULL;
  priv->irq = -1;

  /* Set default timeout (can be overridden by settimeout) */

  ret = rzv_wdt_calculate_timeout(priv, 5000);  /* 5 second default */
  if (ret < 0)
    {
      wderr("ERROR: Failed to calculate default timeout: %d\n", ret);
      return ret;
    }

  /* Enable peripheral clock */

  ret = rzv_wdt_clock_enable(channel);
  if (ret < 0)
    {
      wderr("ERROR: Failed to enable WDT%d clock: %d\n", channel, ret);
      return ret;
    }

  /* Attach interrupt if in NMI mode */

#ifdef CONFIG_RZV_WDT_INTERRUPT_MODE
  /* Select appropriate interrupt event based on channel
   * Channel 0 (CR8_0): RZV_ELC_IWDT_ELCWUN_CR8_0 (0x8F)
   * Channel 1 (CR8_1): RZV_ELC_IWDT_ELCWUN_CR8_1 (0x90)
   * Channel 2 (CM33):  RZV_ELC_IWDT_ELCWUN_CM33 (0x8E)
   * Channel 3 (CA55):  RZV_ELC_IWDT_ELCWUN_CA55 (0x8D)
   */

  int event = -1;

  switch (channel)
    {
      case 0:
        event = RZV_ELC_IWDT_ELCWUN_CR8_0;
        break;
      case 1:
        event = RZV_ELC_IWDT_ELCWUN_CR8_1;
        break;
      case 2:
        event = RZV_ELC_IWDT_ELCWUN_CM33;
        break;
      case 3:
        event = RZV_ELC_IWDT_ELCWUN_CA55;
        break;
      default:
        wderr("ERROR: Invalid channel for interrupt: %d\n", channel);
        return -EINVAL;
    }

  priv->irq = rzv_icu_attach(event, rzv_wdt_interrupt, priv, false);
  if (priv->irq < 0)
    {
      wderr("ERROR: Failed to attach WDT%d interrupt: %d\n",
            channel, priv->irq);
      return priv->irq;
    }

  /* Set high priority for watchdog interrupt */

  rzv_icu_set_priority(priv->irq, 2);
  wdinfo("WDT%d IRQ %d attached (event 0x%02x)\n",
         channel, priv->irq, event);
#endif

  /* Register the watchdog driver */

  g_wdt_dev[channel].ops = &g_wdt_ops;

  ret = watchdog_register(devpath,
                          (FAR struct watchdog_lowerhalf_s *)priv);
  if (ret < 0)
    {
      wderr("ERROR: Failed to register WDT%d: %d\n", channel, ret);
#ifdef CONFIG_RZV_WDT_INTERRUPT_MODE
      if (priv->irq >= 0)
        {
          rzv_icu_detach(priv->irq);
        }
#endif
      return ret;
    }

  wdinfo("WDT%d driver registered at %s\n", channel, devpath);

  return OK;
}

#endif /* CONFIG_RZV_WDT */
