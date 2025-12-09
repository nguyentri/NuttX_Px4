/****************************************************************************
 * arch/arm/src/ra8/ra_wdt.c
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
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/irq.h>
#include <nuttx/timers/watchdog.h>
#include <arch/board/board.h>

#include "arm_internal.h"
#include "ra_wdt.h"
#include "ra_icu.h"
#include "hardware/ra8p1/ra_wdt.h"
#include "ra_mstp.h"
#include "ra_clock.h"

#if defined(CONFIG_RA_WDT)

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Clocking *****************************************************************/

/* The WDT uses PCLK.  The maximum timeout depends on the PCLK frequency
 * and the maximum clock divider.
 */

#define WDT_MAXTIMEOUT (10000) /* 10 seconds (arbitrary max) */

/****************************************************************************
 * Private Types
 ****************************************************************************/

struct ra_wdt_lowerhalf_s
{
  const struct watchdog_ops_s *ops;
  uint32_t timeout; /* The actual timeout value */
  bool     started; /* The timer is started */
  uint8_t  reload;  /* The 8-bit reload value */
  uint8_t  cks;     /* The clock select value */
  uint8_t  tops;    /* The timeout period select value */
  int      irq;     /* The IRQ number */
  xcpt_t   handler; /* User NMI handler */
  uint8_t  channel; /* Channel index (0..WDT_MAX_CHANNELS-1) */
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Interrupt handling *******************************************************/

static int    ra_wdt_interrupt(int irq, FAR void *context, FAR void *arg);

/* "Lower half" driver methods **********************************************/

static int    ra_wdt_start(FAR struct watchdog_lowerhalf_s *lower);
static int    ra_wdt_stop(FAR struct watchdog_lowerhalf_s *lower);
static int    ra_wdt_keepalive(FAR struct watchdog_lowerhalf_s *lower);
static int    ra_wdt_getstatus(FAR struct watchdog_lowerhalf_s *lower,
                               FAR struct watchdog_status_s *status);
static int    ra_wdt_settimeout(FAR struct watchdog_lowerhalf_s *lower,
                                uint32_t timeout);
static xcpt_t ra_wdt_capture(FAR struct watchdog_lowerhalf_s *lower,
                             xcpt_t handler);
static int    ra_wdt_ioctl(FAR struct watchdog_lowerhalf_s *lower,
                           int cmd, unsigned long arg);

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const struct watchdog_ops_s g_wdgops =
{
  .start      = ra_wdt_start,
  .stop       = ra_wdt_stop,
  .keepalive  = ra_wdt_keepalive,
  .getstatus  = ra_wdt_getstatus,
  .settimeout = ra_wdt_settimeout,
  .capture    = ra_wdt_capture,
  .ioctl      = ra_wdt_ioctl,
};

static struct ra_wdt_lowerhalf_s g_wdtdev;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_wdt_interrupt
 *
 * Description:
 *   WDT interrupt
 *
 * Input Parameters:
 *   Usual interrupt handler arguments.
 *
 * Returned Value:
 *   Always zero
 *
 ****************************************************************************/

static int ra_wdt_interrupt(int irq, FAR void *context, FAR void *arg)
{
  FAR struct ra_wdt_lowerhalf_s *priv = (FAR struct ra_wdt_lowerhalf_s *)arg;

  UNUSED(irq);
  UNUSED(context);

  wdwarn("WDT underflow/refresh error interrupt!\n");

  /* Read and clear status flags */

  uint16_t sr = getreg16(R_WDT_WDTSR(priv->channel));
  if (sr & R_WDT_WDTSR_UNDFF)
    {
      wdwarn("WDT underflow detected\n");
    }

  if (sr & R_WDT_WDTSR_REFEF)
    {
      wdwarn("WDT refresh error detected\n");
    }

  /* Call user handler if registered (NMI mode) */

#ifdef CONFIG_RA_WDT_NMI_MODE
  if (priv->handler != NULL)
    {
      priv->handler(irq, context, arg);
    }
#endif

  return OK;
}

/****************************************************************************
 * Name: ra_wdt_start
 *
 * Description:
 *   Start the watchdog timer, resetting the time to the current timeout,
 *
 * Input Parameters:
 *   lower - A pointer the publicly visible representation of the "lower-half"
 *           driver state structure.
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure.
 *
 ****************************************************************************/

static int ra_wdt_start(FAR struct watchdog_lowerhalf_s *lower)
{
  FAR struct ra_wdt_lowerhalf_s *priv = (FAR struct ra_wdt_lowerhalf_s *)lower;
  uint16_t regval;

  wdinfo("Entry\n");

  if (priv->started)
    {
      return OK;
    }

  /* WARNING: WDT behavior depends on OFS0 option bytes configuration:
   * - Auto-start mode: WDT starts on power-on, WDTCR already configured
   * - Register-start mode: WDTCR can be configured here
   * WDTCR is write-once after WDT starts in register-start mode.
   * This driver assumes register-start mode for runtime configuration.
   */

  /* Check if WDT already running (auto-start mode or previous start) */

  uint16_t sr = getreg16(R_WDT_WDTSR(priv->channel));
  if (sr & (R_WDT_WDTSR_UNDFF | R_WDT_WDTSR_REFEF))
    {
      wdwarn("WDT status flags set - may be in auto-start mode\n");
      wdwarn("Runtime configuration may not take effect\n");
    }

  /* Set the timeout period and clock divider */
  /* NOTE: In register-start mode, WDTCR must be written BEFORE first refresh.
   * In auto-start mode, WDTCR write has no effect (configured by OFS0).
   */

  /* Configure WDTCR */
  /* Window Start/End Position: 100% - 0% (Always allow refresh) */
  /* Clock Division Ratio: priv->cks */
  /* Timeout Period: priv->tops */

  regval = (R_WDT_WDTCR_RPSS_11 | R_WDT_WDTCR_RPES_11 |
            (priv->cks & R_WDT_WDTCR_CKS_MASK) |
            (priv->tops & R_WDT_WDTCR_TOPS_MASK));

  putreg16(regval, R_WDT_WDTCR(priv->channel));

  /* Reset the WDT */
  putreg8(0x00, R_WDT_WDTRR(priv->channel));
  putreg8(0xff, R_WDT_WDTRR(priv->channel));

  priv->started = true;

  return OK;
}

/****************************************************************************
 * Name: ra_wdt_stop
 *
 * Description:
 *   Stop the watchdog timer
 *
 * Input Parameters:
 *   lower - A pointer the publicly visible representation of the "lower-half"
 *           driver state structure.
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure.
 *
 ****************************************************************************/

static int ra_wdt_stop(FAR struct watchdog_lowerhalf_s *lower)
{
  FAR struct ra_wdt_lowerhalf_s *priv = (FAR struct ra_wdt_lowerhalf_s *)lower;

  wdinfo("Entry\n");

  /* The RA8 WDT cannot be stopped once started in some modes.
   * However, if we are in a mode where it can be stopped, we would do it here.
   * For now, we just mark it as stopped in our structure.
   */

  priv->started = false;

  return OK;
}

/****************************************************************************
 * Name: ra_wdt_keepalive
 *
 * Description:
 *   Reset the watchdog timer to the current timeout value, prevent any
 *   imminent watchdog timeouts.  This is sometimes referred as "pinging"
 *   the watchdog.
 *
 * Input Parameters:
 *   lower - A pointer the publicly visible representation of the "lower-half"
 *           driver state structure.
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure.
 *
 ****************************************************************************/

static int ra_wdt_keepalive(FAR struct watchdog_lowerhalf_s *lower)
{
  FAR struct ra_wdt_lowerhalf_s *priv = (FAR struct ra_wdt_lowerhalf_s *)lower;

  wdinfo("Entry\n");

  if (!priv->started)
    {
      return OK;
    }

  /* Refresh the WDT */
  /* Write 0x00 then 0xFF to WDTRR to refresh */
  putreg8(0x00, R_WDT_WDTRR(priv->channel));
  putreg8(0xff, R_WDT_WDTRR(priv->channel));

  return OK;
}

/****************************************************************************
 * Name: ra_wdt_getstatus
 *
 * Description:
 *   Get the current watchdog timer status
 *
 * Input Parameters:
 *   lower  - A pointer the publicly visible representation of the "lower-half"
 *            driver state structure.
 *   status - The location to return the watchdog status information.
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure.
 *
 ****************************************************************************/

static int ra_wdt_getstatus(FAR struct watchdog_lowerhalf_s *lower,
                            FAR struct watchdog_status_s *status)
{
  FAR struct ra_wdt_lowerhalf_s *priv = (FAR struct ra_wdt_lowerhalf_s *)lower;

  wdinfo("Entry\n");

  if (!status)
    {
      return -EINVAL;
    }

  status->flags = 0;

  if (priv->started)
    {
      status->flags |= WDFLAGS_ACTIVE;
    }

  /* Calculate time left from down counter value in WDTSR */
  status->timeout = priv->timeout;
  status->timeleft = 0;

  if (priv->started)
    {
      uint16_t wdtsr = getreg16(R_WDT_WDTSR(priv->channel));
      uint32_t counter = wdtsr & R_WDT_WDTSR_CNTVAL_MASK;
      uint32_t pclk = ra_get_peripheral_clock(RA_PCLK_PCLKB);
      uint32_t cks_div = 128; /* default */

      switch (priv->cks)
        {
        case R_WDT_WDTCR_CKS_0001:
          cks_div = 4;
          break;
        case R_WDT_WDTCR_CKS_0100:
          cks_div = 64;
          break;
        case R_WDT_WDTCR_CKS_1111:
          cks_div = 128;
          break;
        case R_WDT_WDTCR_CKS_0110:
          cks_div = 512;
          break;
        case R_WDT_WDTCR_CKS_0111:
          cks_div = 2048;
          break;
        case R_WDT_WDTCR_CKS_1000:
          cks_div = 8192;
          break;
        default:
          cks_div = 128;
          break;
        }

      if (pclk != 0)
        {
          uint64_t timeleft_ms = ((uint64_t)counter * (uint64_t)cks_div * 1000ULL) / (uint64_t)pclk;
          if (timeleft_ms > UINT32_MAX)
            {
              status->timeleft = UINT32_MAX;
            }
          else
            {
              status->timeleft = (uint32_t)timeleft_ms;
            }
        }
    }

  return OK;
}

/****************************************************************************
 * Name: ra_wdt_settimeout
 *
 * Description:
 *   Set a new timeout value (and reset the watchdog timer)
 *
 * Input Parameters:
 *   lower   - A pointer the publicly visible representation of the "lower-half"
 *             driver state structure.
 *   timeout - The new timeout value in milliseconds.
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure.
 *
 ****************************************************************************/

static int ra_wdt_settimeout(FAR struct watchdog_lowerhalf_s *lower,
                             uint32_t timeout)
{
  FAR struct ra_wdt_lowerhalf_s *priv = (FAR struct ra_wdt_lowerhalf_s *)lower;
  uint32_t pclk;
  uint32_t best_timeout;
  int best_tops;
  int best_cks;
  int tops;
  int cks;
  uint32_t cks_div[] = {4, 64, 128, 512, 2048, 8192};
  uint32_t cks_val[] = {
      R_WDT_WDTCR_CKS_0001,
      R_WDT_WDTCR_CKS_0100,
      R_WDT_WDTCR_CKS_1111,
      R_WDT_WDTCR_CKS_0110,
      R_WDT_WDTCR_CKS_0111,
      R_WDT_WDTCR_CKS_1000
  };
  uint32_t tops_cycles[] = {1024, 4096, 8192, 16384};
  uint32_t tops_val[] = {
      R_WDT_WDTCR_TOPS_00,
      R_WDT_WDTCR_TOPS_01,
      R_WDT_WDTCR_TOPS_10,
      R_WDT_WDTCR_TOPS_11
  };

  wdinfo("Entry: timeout=%lu\n", (unsigned long)timeout);

  /* Get PCLKB frequency dynamically */

  pclk = ra_get_peripheral_clock(RA_PCLK_PCLKB);
  if (pclk == 0)
    {
      wderr("ERROR: Failed to get PCLKB frequency\n");
      return -EINVAL;
    }

  wdinfo("PCLKB frequency: %lu Hz\n", (unsigned long)pclk);

  /* Find the best CKS and TOPS to match the requested timeout */
  /* timeout (ms) = (cycles * 1000) / (PCLK / div) */
  /* cycles = (timeout * PCLK) / (1000 * div) */

  best_timeout = 0;
  best_tops = 0;
  best_cks = 0;

  for (cks = 0; cks < 6; cks++)
    {
      for (tops = 0; tops < 4; tops++)
        {
           uint32_t t = (uint64_t)tops_cycles[tops] * cks_div[cks] * 1000 / pclk;
           if (t >= timeout)
             {
               if (best_timeout == 0 || t < best_timeout)
                 {
                   best_timeout = t;
                   best_tops = tops;
                   best_cks = cks;
                 }
             }
        }
    }

  if (best_timeout == 0)
    {
      /* Timeout too long, use max */
      best_tops = 3;
      best_cks = 5;
      best_timeout = (uint64_t)tops_cycles[3] * cks_div[5] * 1000 / pclk;
    }

  priv->timeout = best_timeout;
  priv->tops = tops_val[best_tops];
  priv->cks = cks_val[best_cks];

  wdinfo("Selected timeout=%lu, tops=%u, cks=%u\n",
         (unsigned long)priv->timeout, (unsigned int)priv->tops, (unsigned int)priv->cks);

  /* If started, update the registers */
  if (priv->started)
    {
      ra_wdt_start(lower);
    }

  return OK;
}

/****************************************************************************
 * Name: ra_wdt_capture
 *
 * Description:
 *   Don't reset on watchdog timeout; instead, call this user provider
 *   timeout handler.  NOTE:  Providing handler==NULL will restore the
 *   reset behavior.
 *
 * Input Parameters:
 *   lower      - A pointer the publicly visible representation of the "lower-half"
 *                driver state structure.
 *   handler    - The new interrupt handler
 *
 * Returned Value:
 *   The previous interrupt handler (if any)
 *
 ****************************************************************************/

static xcpt_t ra_wdt_capture(FAR struct watchdog_lowerhalf_s *lower,
                             xcpt_t handler)
{
  wdinfo("handler=%p\n", handler);

#ifdef CONFIG_RA_WDT_NMI_MODE
  FAR struct ra_wdt_lowerhalf_s *priv = (FAR struct ra_wdt_lowerhalf_s *)lower;
  xcpt_t oldhandler;

  /* Save and replace the current handler */

  oldhandler = priv->handler;
  priv->handler = handler;

  /* Enable IRQ if handler is being registered */

  if (handler != NULL && priv->irq >= 0)
    {
      up_enable_irq(priv->irq);
      wdinfo("WDT NMI handler registered and IRQ enabled\n");
    }
  else if (handler == NULL && priv->irq >= 0)
    {
      up_disable_irq(priv->irq);
      wdinfo("WDT NMI handler unregistered and IRQ disabled\n");
    }

  return oldhandler;
#else
  UNUSED(lower);
  UNUSED(handler);
  wdwarn("NMI mode not configured (CONFIG_RA_WDT_NMI_MODE not defined)\n");
  wdwarn("WDT will reset on timeout - cannot use capture handler\n");
  return NULL;
#endif
}

/****************************************************************************
 * Name: ra_wdt_ioctl
 *
 * Description:
 *   Any ioctl commands that are not recognized by the "upper-half" driver
 *   are forwarded to the lower half driver through this method.
 *
 * Input Parameters:
 *   lower - A pointer the publicly visible representation of the "lower-half"
 *           driver state structure.
 *   cmd   - The ioctl command value
 *   arg   - The optional argument that accompanies the 'cmd'.  The
 *           interpretation of this argument depends on the particular
 *           command.
 *
 * Returned Value:
 *   Zero on success; a negated errno value on failure.
 *
 ****************************************************************************/

static int ra_wdt_ioctl(FAR struct watchdog_lowerhalf_s *lower, int cmd,
                        unsigned long arg)
{
  wdinfo("Entry: cmd=%d\n", cmd);
  return -ENOTTY;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_wdt_initialize
 *
 * Description:
 *   Initialize the WDT watchdog time.  The watchdog timer is initialized and
 *   registered as 'devpath'.  The initial state of the watchdog time is
 *   disabled.
 *
 * Input Parameters:
 *   devpath - The full path to the watchdog.  This should be of the form
 *     /dev/watchdog0
 *
 * Returned Value:
 *   Zero (OK) is returned on success; a negated errno value is returned on
 *   any failure.
 *
 ****************************************************************************/

int ra_wdt_initialize(FAR const char *devpath, int channel)
{
  FAR struct ra_wdt_lowerhalf_s *priv = &g_wdtdev;
  int ret;

  wdinfo("Entry: devpath=%s\n", devpath);

  /* Initialize the driver state structure. */

  priv->ops     = &g_wdgops;
  priv->started = false;
  priv->timeout = 0;

  /* Initialize handler to NULL */

  priv->handler = NULL;

  /* Validate and store channel */
  if (channel < 0 || channel >= WDT_MAX_CHANNELS)
    {
      wderr("ERROR: invalid channel %d (max %d)\n", channel, WDT_MAX_CHANNELS);
      return -EINVAL;
    }
  priv->channel = (uint8_t)channel;
  /* Default to 128 divider and maximum tops (16384 cycles) */
  priv->cks = R_WDT_WDTCR_CKS_1111;
  priv->tops = R_WDT_WDTCR_TOPS_11;
  /* Default to 128 divider and maximum tops (16384 cycles) */
  priv->cks = R_WDT_WDTCR_CKS_1111;
  priv->tops = R_WDT_WDTCR_TOPS_11;

  /* Attach the interrupt (don't enable yet - will enable in NMI mode) */

#ifdef RA_ELC_WDT0_UNDERFLOW
  /* Choose event based on channel */
  int event = (channel == 0) ? RA_ELC_WDT0_UNDERFLOW : RA_ELC_WDT1_UNDERFLOW;
  priv->irq = ra_icu_attach(event, ra_wdt_interrupt, priv, false);
  if (priv->irq < 0)
    {
      wderr("ERROR: ra_icu_attach failed: %d\n", priv->irq);
      return priv->irq;
    }

  /* Set high priority for watchdog interrupt */

  ra_icu_set_priority(priv->irq, 2);
  wdinfo("WDT IRQ %d attached and configured\n", priv->irq);
#else
  priv->irq = -1;
  wdwarn("RA_ELC_WDT0_UNDERFLOW not defined in ra8p1_irq.h\n");
  wdwarn("WDT will operate in reset-only mode\n");
#endif

  /* Register the watchdog driver */

  if (watchdog_register(devpath, (FAR struct watchdog_lowerhalf_s *)priv) == NULL)
    {
      wderr("ERROR: watchdog_register failed\n");
      ret = -ENODEV;
#ifdef RA_ELC_WDT0_UNDERFLOW
      if (priv->irq >= 0)
        {
          ra_icu_detach(priv->irq);
        }
#endif
      return ret;
    }

  wdinfo("WDT driver registered at %s\n", devpath);

  return OK;
}

#endif /* CONFIG_RA_WDT */
