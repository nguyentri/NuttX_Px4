/****************************************************************************
 * arch/arm/src/ra8/ra_iwdt.c
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
#include "ra_iwdt.h"
#include "ra_icu.h"
#include "hardware/ra8p1/ra_iwdt.h"

#if defined(CONFIG_RA_IWDT)

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Clocking *****************************************************************/

/* The IWDT uses the IWDTCLK which is derived from LOCO (Low-speed On-Chip Oscillator).
 * Per RA8P1 datasheet:
 *   - LOCO frequency: 32.768 kHz (±15% tolerance)
 *   - IWDTCLK = LOCO / 15 = 2184.5 Hz (typical)
 * This clock is independent of system clock and runs even in low-power modes.
 */
#define IWDT_LOCO_FREQUENCY   32768
#define IWDT_CLOCK_FREQUENCY  (IWDT_LOCO_FREQUENCY / 15)  /* 2184.5 Hz */

/* Register Access **********************************************************/

#define ra_getreg8(o)    getreg8(R_IWDT_BASE + (o))
#define ra_getreg16(o)   getreg16(R_IWDT_BASE + (o))
#define ra_getreg32(o)   getreg32(R_IWDT_BASE + (o))

#define ra_putreg8(v,o)  putreg8(v, R_IWDT_BASE + (o))
#define ra_putreg16(v,o) putreg16(v, R_IWDT_BASE + (o))
#define ra_putreg32(v,o) putreg32(v, R_IWDT_BASE + (o))

/****************************************************************************
 * Private Types
 ****************************************************************************/

struct ra_iwdt_lowerhalf_s
{
  const struct watchdog_ops_s *ops;
  uint32_t timeout;   /* The actual timeout value in milliseconds */
  bool     started;   /* The timer is started */
  bool     autostart; /* Hardware auto-start mode detected */
  uint8_t  cks;       /* The clock select value */
  uint8_t  tops;      /* The timeout period select value */
  int      irq;       /* The IRQ number */
  xcpt_t   handler;   /* User handler for NMI mode */
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Interrupt handling *******************************************************/

static int    ra_iwdt_interrupt(int irq, FAR void *context, FAR void *arg);

/* "Lower half" driver methods **********************************************/

static int    ra_iwdt_start(FAR struct watchdog_lowerhalf_s *lower);
static int    ra_iwdt_stop(FAR struct watchdog_lowerhalf_s *lower);
static int    ra_iwdt_keepalive(FAR struct watchdog_lowerhalf_s *lower);
static int    ra_iwdt_getstatus(FAR struct watchdog_lowerhalf_s *lower,
                                FAR struct watchdog_status_s *status);
static int    ra_iwdt_settimeout(FAR struct watchdog_lowerhalf_s *lower,
                                 uint32_t timeout);
static xcpt_t ra_iwdt_capture(FAR struct watchdog_lowerhalf_s *lower,
                              xcpt_t handler);
static int    ra_iwdt_ioctl(FAR struct watchdog_lowerhalf_s *lower,
                            int cmd, unsigned long arg);

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const struct watchdog_ops_s g_iwdtops =
{
  .start      = ra_iwdt_start,
  .stop       = ra_iwdt_stop,
  .keepalive  = ra_iwdt_keepalive,
  .getstatus  = ra_iwdt_getstatus,
  .settimeout = ra_iwdt_settimeout,
  .capture    = ra_iwdt_capture,
  .ioctl      = ra_iwdt_ioctl,
};

static struct ra_iwdt_lowerhalf_s g_iwdtdev;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_iwdt_interrupt
 *
 * Description:
 *   IWDT interrupt
 *
 * Input Parameters:
 *   Usual interrupt handler arguments.
 *
 * Returned Value:
 *   Always zero
 *
 ****************************************************************************/

static int ra_iwdt_interrupt(int irq, FAR void *context, FAR void *arg)
{
  FAR struct ra_iwdt_lowerhalf_s *priv = (FAR struct ra_iwdt_lowerhalf_s *)arg;
  uint16_t sr;

  /* Check if the IWDT is enabled */

  if (priv->started)
    {
      /* Read and check status flags */

      sr = ra_getreg16(R_IWDT_IWDTSR_OFFSET);

      if (sr & R_IWDT_IWDTSR_UNDFF)
        {
          wderr("IWDT underflow detected!\n");
        }

      if (sr & R_IWDT_IWDTSR_REFEF)
        {
          wderr("IWDT refresh error detected!\n");
        }

      /* Call user handler if registered (NMI mode) */

      if (priv->handler)
        {
          priv->handler(irq, context, arg);
        }

      /* Note: In reset mode, we won't reach here as MCU will reset */
    }

  return OK;
}

/****************************************************************************
 * Name: ra_iwdt_start
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

static int ra_iwdt_start(FAR struct watchdog_lowerhalf_s *lower)
{
  FAR struct ra_iwdt_lowerhalf_s *priv = (FAR struct ra_iwdt_lowerhalf_s *)lower;
  uint16_t regval;
  uint16_t sr;

  wdinfo("Entry\n");

  if (priv->started)
    {
      return OK;
    }

  /* Check if IWDT is already running (auto-start mode from OFS0)
   * If CNTVAL is non-zero, the watchdog has already been started by hardware.
   */

  sr = ra_getreg16(R_IWDT_IWDTSR_OFFSET);
  if ((sr & R_IWDT_IWDTSR_CNTVAL_MASK) != 0)
    {
      wdwarn("IWDT already running (auto-start mode detected)\n");
      wdwarn("Using hardware-configured settings from OFS0\n");
      priv->autostart = true;
      priv->started = true;

      /* In auto-start mode, IWDTCR is write-once and already configured.
       * We can only refresh the counter.
       */

      ra_putreg8(0x00, R_IWDT_IWDTRR_OFFSET);
      ra_putreg8(0xff, R_IWDT_IWDTRR_OFFSET);
      return OK;
    }

  /* Register-start mode: Configure watchdog before starting */

  wdinfo("Configuring IWDT in register-start mode\n");

  /* Configure IWDTRCR - Reset/Interrupt control
   * RSTIRQS = 1: Reset on underflow (default safe mode)
   * RSTIRQS = 0: NMI on underflow (requires handler registration)
   */

#ifdef CONFIG_RA_IWDT_NMI_MODE
  ra_putreg8(0x00, R_IWDT_IWDTRCR_OFFSET);  /* NMI mode */
  wdinfo("IWDT configured for NMI mode\n");
#else
  ra_putreg8(R_IWDT_IWDTRCR_RSTIRQS, R_IWDT_IWDTRCR_OFFSET);  /* Reset mode */
  wdinfo("IWDT configured for reset mode\n");
#endif

  /* Configure IWDTCR - Timeout and window settings
   * Window Start/End Position: 100% - 0% (Always allow refresh)
   * Clock Division Ratio: priv->cks
   * Timeout Period: priv->tops
   *
   * Note: IWDTCR is write-once after first refresh in register-start mode!
   */

  regval = (R_IWDT_IWDTCR_RPSS_11 | R_IWDT_IWDTCR_RPES_11 |
            (priv->cks & R_IWDT_IWDTCR_CKS_MASK) |
            (priv->tops & R_IWDT_IWDTCR_TOPS_MASK));

  ra_putreg16(regval, R_IWDT_IWDTCR_OFFSET);

  /* Configure IWDTCSTPR - Sleep mode control */

#ifdef CONFIG_RA_IWDT_STOP_IN_SLEEP
  ra_putreg8(R_IWDT_IWDTCSTPR_SLCSTP, R_IWDT_IWDTCSTPR_OFFSET);
  wdinfo("IWDT will stop in sleep mode\n");
#else
  ra_putreg8(0x00, R_IWDT_IWDTCSTPR_OFFSET);
  wdinfo("IWDT will continue in sleep mode\n");
#endif

  /* First refresh starts the IWDT in register-start mode
   * WARNING: After this, IWDT cannot be stopped!
   */

  ra_putreg8(0x00, R_IWDT_IWDTRR_OFFSET);
  ra_putreg8(0xff, R_IWDT_IWDTRR_OFFSET);

  priv->autostart = false;
  priv->started = true;

  return OK;
}

/****************************************************************************
 * Name: ra_iwdt_stop
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

static int ra_iwdt_stop(FAR struct watchdog_lowerhalf_s *lower)
{
  FAR struct ra_iwdt_lowerhalf_s *priv = (FAR struct ra_iwdt_lowerhalf_s *)lower;

  wdinfo("Entry\n");

  /* CRITICAL HARDWARE LIMITATION:
   * The RA8P1 IWDT CANNOT be stopped once started, in either mode:
   *   - Auto-start mode: Started by OFS0 at power-on
   *   - Register-start mode: Started by first refresh after configuration
   *
   * This is a fundamental hardware design for safety/security.
   * The only way to stop IWDT is to reset the MCU.
   *
   * We mark it as "stopped" in software to prevent keepalive,
   * which will cause a watchdog reset after timeout expires.
   */

  wdwarn("IWDT cannot be stopped once started (hardware limitation)\n");
  wdwarn("Marking as stopped - system will reset after timeout\n");

  priv->started = false;

  return OK;
}

/****************************************************************************
 * Name: ra_iwdt_keepalive
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

static int ra_iwdt_keepalive(FAR struct watchdog_lowerhalf_s *lower)
{
  FAR struct ra_iwdt_lowerhalf_s *priv = (FAR struct ra_iwdt_lowerhalf_s *)lower;

  wdinfo("Entry\n");

  if (!priv->started)
    {
      return OK;
    }

  /* Refresh the IWDT */
  /* Write 0x00 then 0xFF to IWDTRR to refresh */
  ra_putreg8(0x00, R_IWDT_IWDTRR_OFFSET);
  ra_putreg8(0xff, R_IWDT_IWDTRR_OFFSET);

  return OK;
}

/****************************************************************************
 * Name: ra_iwdt_getstatus
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

static int ra_iwdt_getstatus(FAR struct watchdog_lowerhalf_s *lower,
                             FAR struct watchdog_status_s *status)
{
  FAR struct ra_iwdt_lowerhalf_s *priv = (FAR struct ra_iwdt_lowerhalf_s *)lower;

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

  status->timeout = priv->timeout;

  /* Read counter value if possible */
  /* IWDTSR has CNTVAL bits 13-0 */
  uint16_t sr = ra_getreg16(R_IWDT_IWDTSR_OFFSET);
  /* uint16_t count = sr & R_IWDT_IWDTSR_CNTVAL_MASK; */
  (void)sr;

  /* Convert count to timeleft */
  /* This requires knowing the current clock divider and frequency */
  /* For now, just return 0 or approximate */
  status->timeleft = 0;

  return OK;
}

/****************************************************************************
 * Name: ra_iwdt_settimeout
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

static int ra_iwdt_settimeout(FAR struct watchdog_lowerhalf_s *lower,
                              uint32_t timeout)
{
  FAR struct ra_iwdt_lowerhalf_s *priv = (FAR struct ra_iwdt_lowerhalf_s *)lower;
  uint32_t pclk = IWDT_CLOCK_FREQUENCY;
  uint32_t best_timeout;
  int best_tops;
  int best_cks;
  int tops;
  int cks;

  /* CKS dividers: 1, 16, 32, 64, 128, 256 */
  /*
  uint32_t cks_div[] = {1, 16, 32, 64, 128, 256};
  uint32_t cks_val[] = {
      R_IWDT_IWDTCR_CKS_0000,
      R_IWDT_IWDTCR_CKS_0010,
      R_IWDT_IWDTCR_CKS_0011,
      R_IWDT_IWDTCR_CKS_0010,
      R_IWDT_IWDTCR_CKS_1111,
      R_IWDT_IWDTCR_CKS_0101
  };
  */

  /* Clock divider lookup table
   * Per RA8P1 datasheet, IWDT supports these clock divisions:
   */

  uint32_t cks_div[] = {1, 16, 32, 64, 128, 256};
  uint32_t cks_val[] = {
      R_IWDT_IWDTCR_CKS_0000,  /* Code 0:  IWDTCLK / 1   */
      R_IWDT_IWDTCR_CKS_0010,  /* Code 2:  IWDTCLK / 16  */
      R_IWDT_IWDTCR_CKS_0011,  /* Code 3:  IWDTCLK / 32  */
      R_IWDT_IWDTCR_CKS_0100,  /* Code 4:  IWDTCLK / 64  */
      R_IWDT_IWDTCR_CKS_1111,  /* Code 15: IWDTCLK / 128 */
      R_IWDT_IWDTCR_CKS_0101   /* Code 5:  IWDTCLK / 256 */
  };  uint32_t tops_cycles[] = {128, 512, 1024, 2048};
  uint32_t tops_val[] = {
      R_IWDT_IWDTCR_TOPS_00,
      R_IWDT_IWDTCR_TOPS_01,
      R_IWDT_IWDTCR_TOPS_10,
      R_IWDT_IWDTCR_TOPS_11
  };

  wdinfo("Entry: timeout=%" PRIu32 "\n", timeout);

  best_timeout = 0;
  best_tops = 0;
  best_cks = 0;

  /* Find best divider and timeout combination
   * Formula: timeout_ms = (cycles * divider * 1000) / IWDTCLK_freq
   */

  for (cks = 0; cks < 6; cks++)
    {
      for (tops = 0; tops < 4; tops++)
        {
           /* Timeout formula: timeout_ms = (cycles * divider * 1000) / IWDTCLK
            * Example: 2048 cycles * 128 divider / 2184.5 Hz ≈ 120 seconds
            */
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
      /* Timeout too long, use max: 2048 cycles * 256 divider ≈ 240 seconds */
      best_tops = 3;
      best_cks = 5;
      best_timeout = (uint64_t)tops_cycles[3] * cks_div[5] * 1000 / pclk;
    }

  priv->timeout = best_timeout;
  priv->tops = tops_val[best_tops];
  priv->cks = cks_val[best_cks];

  wdinfo("Selected timeout=%" PRIu32 ", tops=%d, cks=%d\n", priv->timeout, priv->tops, priv->cks);

  /* If started, update the registers */
  if (priv->started)
    {
      ra_iwdt_start(lower);
    }

  return OK;
}

/****************************************************************************
 * Name: ra_iwdt_capture
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

static xcpt_t ra_iwdt_capture(FAR struct watchdog_lowerhalf_s *lower,
                              xcpt_t handler)
{
  FAR struct ra_iwdt_lowerhalf_s *priv = (FAR struct ra_iwdt_lowerhalf_s *)lower;
  xcpt_t oldhandler;

  wdinfo("handler=%p\n", handler);

#ifdef CONFIG_RA_IWDT_NMI_MODE
  /* Save and replace the current handler */

  oldhandler = priv->handler;
  priv->handler = handler;

  /* Enable IRQ if handler is being registered */

  if (handler != NULL && priv->irq >= 0)
    {
      up_enable_irq(priv->irq);
      wdinfo("IWDT NMI handler registered and IRQ enabled\n");
    }
  else if (handler == NULL && priv->irq >= 0)
    {
      up_disable_irq(priv->irq);
      wdinfo("IWDT NMI handler unregistered and IRQ disabled\n");
    }

  return oldhandler;
#else
  UNUSED(priv);
  UNUSED(oldhandler);
  wdwarn("NMI mode not configured (CONFIG_RA_IWDT_NMI_MODE not defined)\n");
  wdwarn("IWDT will reset on timeout - cannot use capture handler\n");
  return NULL;
#endif
}

/****************************************************************************
 * Name: ra_iwdt_ioctl
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

static int ra_iwdt_ioctl(FAR struct watchdog_lowerhalf_s *lower, int cmd,
                         unsigned long arg)
{
  wdinfo("Entry: cmd=%d\n", cmd);
  return -ENOTTY;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_iwdt_initialize
 *
 * Description:
 *   Initialize the IWDT watchdog time.  The watchdog timer is initialized and
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

int ra_iwdt_initialize(FAR const char *devpath)
{
  FAR struct ra_iwdt_lowerhalf_s *priv = &g_iwdtdev;
  int ret;

  wdinfo("Entry: devpath=%s\n", devpath);

  /* MSTP (Module Stop) Control Note:
   * The IWDT runs from dedicated IWDTCLK (LOCO/15) which is independent
   * of the system clock and does not require MSTP control.
   * IWDT is always powered for safety/security purposes.
   * Per RA8P1 hardware manual, IWDT has no MSTP bit.
   */

  /* Initialize the driver state structure */

  priv->ops       = &g_iwdtops;
  priv->started   = false;
  priv->autostart = false;
  priv->timeout   = 0;
  priv->handler   = NULL;
  priv->irq       = -1;

  /* Attach the interrupt for NMI/underflow events
   * Note: IRQ is registered but not enabled until:
   *   - NMI mode is configured (CONFIG_RA_IWDT_NMI_MODE)
   *   - User registers a handler via capture()
   */

#ifdef RA_ELC_IWDT_UNDERFLOW
  priv->irq = ra_icu_attach(RA_ELC_IWDT_UNDERFLOW, ra_iwdt_interrupt,
                            priv, false);
  if (priv->irq < 0)
    {
      wderr("ERROR: ra_icu_attach failed: %d\n", priv->irq);
      return priv->irq;
    }

  /* Set high priority for safety-critical watchdog interrupt */

  ret = ra_icu_set_priority(priv->irq, 2);
  if (ret < 0)
    {
      wderr("ERROR: ra_icu_set_priority failed: %d\n", ret);
      ra_icu_detach(priv->irq);
      return ret;
    }

  wdinfo("IWDT IRQ %d attached with priority 2\n", priv->irq);

  /* IRQ will be enabled when:
   *   1. NMI mode is configured AND
   *   2. User registers handler via watchdog_capture()
   */

#else
  wdwarn("RA_ELC_IWDT_UNDERFLOW not defined in ra8p1_irq.h\n");
  wdwarn("IWDT will operate in reset-only mode\n");
#endif

  /* Register the watchdog driver */

  if (watchdog_register(devpath, (FAR struct watchdog_lowerhalf_s *)priv) == NULL)
    {
      wderr("ERROR: watchdog_register failed\n");
      ret = -ENODEV;
#ifdef RA_ELC_IWDT_UNDERFLOW
      if (priv->irq >= 0)
        {
          ra_icu_detach(priv->irq);
        }
#endif
      return ret;
    }

  wdinfo("IWDT driver registered at %s\n", devpath);

  return OK;
}

#endif /* CONFIG_RA_IWDT */
