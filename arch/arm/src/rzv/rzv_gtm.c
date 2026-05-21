/****************************************************************************
 * arch/arm/src/rzv/rzv_gtm.c
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
#include <errno.h>
#include <debug.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/timers/timer.h>
#include <nuttx/kmalloc.h>

#include "chip.h"
#include "arm_internal.h"
#include "hardware/rzv_gtm.h"
#include "rzv_gtm.h"
#include "rzv_icu.h"
#include "rzv_clock.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#ifndef getreg8
#  define getreg8(a)    (*(volatile uint8_t *)(a))
#endif

#ifndef putreg8
#  define putreg8(v,a)  (*(volatile uint8_t *)(a) = (v))
#endif

#ifndef getreg32
#  define getreg32(a)    (*(volatile uint32_t *)(a))
#endif

#ifndef putreg32
#  define putreg32(v,a)  (*(volatile uint32_t *)(a) = (v))
#endif

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* GTM lower-half driver state */

struct rzv_gtm_lowerhalf_s
{
  const struct timer_ops_s *ops;   /* NuttX timer operations */
  uint32_t base;                   /* GTM base address */
  uint32_t frequency;              /* Clock frequency in Hz */
  uint32_t timeout;                /* Configured timeout in microseconds */
  int channel;                     /* Channel number (0-7) */
  int irq;                         /* Allocated ICU IRQ slot or -1 */
  tccb_t callback;                 /* User callback function */
  void *arg;                       /* Callback argument */
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Register access helpers */

static inline uint32_t gtm_getreg32(struct rzv_gtm_lowerhalf_s *priv,
                                     unsigned int offset);
static inline void gtm_putreg32(struct rzv_gtm_lowerhalf_s *priv,
                                 unsigned int offset, uint32_t val);
static inline uint8_t gtm_getreg8(struct rzv_gtm_lowerhalf_s *priv,
                                   unsigned int offset);
static inline void gtm_putreg8(struct rzv_gtm_lowerhalf_s *priv,
                                unsigned int offset, uint8_t val);

/* Timer lower-half operations */

static int gtm_timer_start(FAR struct timer_lowerhalf_s *lower);
static int gtm_timer_stop(FAR struct timer_lowerhalf_s *lower);
static int gtm_timer_getstatus(FAR struct timer_lowerhalf_s *lower,
                                FAR struct timer_status_s *status);
static int gtm_timer_settimeout(FAR struct timer_lowerhalf_s *lower,
                                 uint32_t timeout);
static void gtm_timer_setcallback(FAR struct timer_lowerhalf_s *lower,
                                   tccb_t callback, FAR void *arg);
static int gtm_timer_maxtimeout(FAR struct timer_lowerhalf_s *lower,
                                 FAR uint32_t *maxtimeout);

/* Interrupt handler */

static int gtm_interrupt(int irq, void *context, void *arg);

/* Helper functions */

static uintptr_t gtm_get_base(int channel);
static int gtm_get_elc_event(int channel);
static uint32_t gtm_get_clk_id(int channel);

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Timer operations structure */

static const struct timer_ops_s g_gtm_timer_ops =
{
  .start       = gtm_timer_start,
  .stop        = gtm_timer_stop,
  .getstatus   = gtm_timer_getstatus,
  .settimeout  = gtm_timer_settimeout,
  .setcallback = gtm_timer_setcallback,
  .maxtimeout  = gtm_timer_maxtimeout,
  .ioctl       = NULL,  /* No custom ioctls for now */
};

/* Clock IDs for each GTM channel */

static const uint32_t g_gtm_clocks[RZV_GTM_MAX_CHANNELS] =
{
  RZV_CPG_CLK_GTM0,
  RZV_CPG_CLK_GTM1,
  RZV_CPG_CLK_GTM2,
  RZV_CPG_CLK_GTM3,
  RZV_CPG_CLK_GTM4,
  RZV_CPG_CLK_GTM5,
  RZV_CPG_CLK_GTM6,
  RZV_CPG_CLK_GTM7,
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: gtm_getreg32
 ****************************************************************************/

static inline uint32_t gtm_getreg32(struct rzv_gtm_lowerhalf_s *priv,
                                     unsigned int offset)
{
  return getreg32(priv->base + offset);
}

/****************************************************************************
 * Name: gtm_putreg32
 ****************************************************************************/

static inline void gtm_putreg32(struct rzv_gtm_lowerhalf_s *priv,
                                 unsigned int offset, uint32_t val)
{
  putreg32(val, priv->base + offset);
}

/****************************************************************************
 * Name: gtm_getreg8
 ****************************************************************************/

static inline uint8_t gtm_getreg8(struct rzv_gtm_lowerhalf_s *priv,
                                   unsigned int offset)
{
  return getreg8(priv->base + offset);
}

/****************************************************************************
 * Name: gtm_putreg8
 ****************************************************************************/

static inline void gtm_putreg8(struct rzv_gtm_lowerhalf_s *priv,
                                unsigned int offset, uint8_t val)
{
  putreg8(val, priv->base + offset);
}

/****************************************************************************
 * Name: gtm_get_base
 ****************************************************************************/

static uintptr_t gtm_get_base(int channel)
{
  switch (channel)
    {
      case 0: return RZV_GTM0_BASE;
      case 1: return RZV_GTM1_BASE;
      case 2: return RZV_GTM2_BASE;
      case 3: return RZV_GTM3_BASE;
      case 4: return RZV_GTM4_BASE;
      case 5: return RZV_GTM5_BASE;
      case 6: return RZV_GTM6_BASE;
      case 7: return RZV_GTM7_BASE;
      default: return 0;
    }
}

/****************************************************************************
 * Name: gtm_get_elc_event
 ****************************************************************************/

static int gtm_get_elc_event(int channel)
{
  switch (channel)
    {
      case 0: return RZV_ELC_GTM0_GTMTINT;
      case 1: return RZV_ELC_GTM1_GTMTINT;
      case 2: return RZV_ELC_GTM2_GTMTINT;
      case 3: return RZV_ELC_GTM3_GTMTINT;
      case 4: return RZV_ELC_GTM4_GTMTINT;
      case 5: return RZV_ELC_GTM5_GTMTINT;
      case 6: return RZV_ELC_GTM6_GTMTINT;
      case 7: return RZV_ELC_GTM7_GTMTINT;
      default: return -EINVAL;
    }
}

/****************************************************************************
 * Name: gtm_get_clk_id
 ****************************************************************************/

static uint32_t gtm_get_clk_id(int channel)
{
  if (channel >= 0 && channel < RZV_GTM_MAX_CHANNELS)
    {
      return g_gtm_clocks[channel];
    }

  /* Return UINT32_MAX as invalid sentinel — 0 could collide with a valid
   * clock ID in domain 0 bit 0 encoding. */
  return UINT32_MAX;
}

/****************************************************************************
 * Name: gtm_interrupt
 *
 * Description:
 *   GTM interrupt handler. Called by ICU when GTM compare match occurs.
 *
 ****************************************************************************/

static int gtm_interrupt(int irq, void *context, void *arg)
{
  struct rzv_gtm_lowerhalf_s *priv = (struct rzv_gtm_lowerhalf_s *)arg;

  /* Clear ICU IRQ state for this allocated slot */

  rzv_icu_clear_irq(irq);

  /* Invoke user callback if registered */

  if (priv->callback != NULL)
    {
      uint32_t next_interval_us = 0;
      priv->callback(&next_interval_us, priv->arg);
    }

  return OK;
}

/****************************************************************************
 * Name: gtm_timer_start
 *
 * Description:
 *   Start the timer, resetting the time to the current timeout.
 *
 ****************************************************************************/

static int gtm_timer_start(FAR struct timer_lowerhalf_s *lower)
{
  struct rzv_gtm_lowerhalf_s *priv = (struct rzv_gtm_lowerhalf_s *)lower;

  tmrinfo("Starting GTM%d\n", priv->channel);

  /* Start timer by setting OSTMnTS */

  gtm_putreg8(priv, RZV_GTM_OSTMTS_OFFSET, GTM_OSTMTS_OSTMTS);

  return OK;
}

/****************************************************************************
 * Name: gtm_timer_stop
 *
 * Description:
 *   Stop the timer.
 *
 ****************************************************************************/

static int gtm_timer_stop(FAR struct timer_lowerhalf_s *lower)
{
  struct rzv_gtm_lowerhalf_s *priv = (struct rzv_gtm_lowerhalf_s *)lower;

  tmrinfo("Stopping GTM%d\n", priv->channel);

  /* Stop timer by setting OSTMnTT */

  gtm_putreg8(priv, RZV_GTM_OSTMTT_OFFSET, GTM_OSTMTT_OSTMTT);

  return OK;
}

/****************************************************************************
 * Name: gtm_timer_getstatus
 *
 * Description:
 *   Get the current timer status.
 *
 ****************************************************************************/

static int gtm_timer_getstatus(FAR struct timer_lowerhalf_s *lower,
                                FAR struct timer_status_s *status)
{
  struct rzv_gtm_lowerhalf_s *priv = (struct rzv_gtm_lowerhalf_s *)lower;
  uint8_t te;
  uint32_t cnt;
  uint32_t cmp;
  uint64_t timeleft_ticks;

  DEBUGASSERT(priv != NULL && status != NULL);

  /* Read timer enable status from OSTMnTE */

  te = gtm_getreg8(priv, RZV_GTM_OSTMTE_OFFSET);

  /* Initialize status structure */

  memset(status, 0, sizeof(struct timer_status_s));

  /* Set flags based on timer running state */

  status->flags = (te & GTM_OSTMTE_TE) ? TCFLAGS_ACTIVE : 0;

  /* Read current counter value (OSTMnCNT) */

  cnt = gtm_getreg32(priv, RZV_GTM_OSTMCNT_OFFSET);

  /* Read compare value (OSTMnCMP) */

  cmp = gtm_getreg32(priv, RZV_GTM_OSTMCMP_OFFSET);

  /* Store timeout in microseconds */

  status->timeout = priv->timeout;

  /* Calculate time left until next compare match
   * In free-running mode, we calculate based on compare value
   */

  if (te & GTM_OSTMTE_TE)
    {
      /* Timer is running - calculate remaining time */

      if (cmp > cnt)
        {
          timeleft_ticks = cmp - cnt;
        }
      else
        {
          /* Counter has passed compare - will wrap and match */

          timeleft_ticks = (UINT32_MAX - cnt) + cmp + 1;
        }

      /* Convert ticks to microseconds */

      status->timeleft = (uint32_t)((timeleft_ticks * 1000000ULL) /
                                     priv->frequency);
    }
  else
    {
      /* Timer is stopped */

      status->timeleft = 0;
    }

  return OK;
}

/****************************************************************************
 * Name: gtm_timer_settimeout
 *
 * Description:
 *   Set a new timeout value (and reset the timer).
 *
 ****************************************************************************/

static int gtm_timer_settimeout(FAR struct timer_lowerhalf_s *lower,
                                 uint32_t timeout)
{
  struct rzv_gtm_lowerhalf_s *priv = (struct rzv_gtm_lowerhalf_s *)lower;
  irqstate_t flags;
  uint64_t ticks;

  DEBUGASSERT(priv != NULL);

  if (timeout == 0)
    {
      tmrerr("ERROR: Invalid timeout: 0\n");
      return -EINVAL;
    }

  tmrinfo("GTM%d: Setting timeout to %lu microseconds\n",
          priv->channel, (unsigned long)timeout);

  /* Convert microseconds to timer ticks */

  ticks = ((uint64_t)timeout * priv->frequency) / 1000000ULL;

  if (ticks > UINT32_MAX)
    {
      tmrerr("ERROR: Timeout too large for 32-bit timer\n");
      return -ERANGE;
    }

  /* Stop timer, update compare value, restart — under critical section to
   * prevent a concurrent settimeout from racing the stop/start sequence.
   * Interval mode auto-reloads OSTMCMP after each match so this sequence
   * is safe: stop → write CMP → restart.
   */

  flags = enter_critical_section();

  gtm_putreg8(priv, RZV_GTM_OSTMTT_OFFSET, GTM_OSTMTT_OSTMTT);  /* stop */
  priv->timeout = timeout;
  gtm_putreg32(priv, RZV_GTM_OSTMCMP_OFFSET, (uint32_t)ticks);
  gtm_putreg8(priv, RZV_GTM_OSTMTS_OFFSET, GTM_OSTMTS_OSTMTS);  /* start */

  leave_critical_section(flags);

  tmrinfo("GTM%d: Set compare value to %lu ticks\n",
          priv->channel, (unsigned long)(uint32_t)ticks);

  return OK;
}

/****************************************************************************
 * Name: gtm_timer_setcallback
 *
 * Description:
 *   Set the interrupt callback.
 *
 ****************************************************************************/

static void gtm_timer_setcallback(FAR struct timer_lowerhalf_s *lower,
                                   tccb_t callback, FAR void *arg)
{
  struct rzv_gtm_lowerhalf_s *priv = (struct rzv_gtm_lowerhalf_s *)lower;

  DEBUGASSERT(priv != NULL);

  tmrinfo("GTM%d: Setting callback\n", priv->channel);

  /* Save callback and argument */

  priv->callback = callback;
  priv->arg = arg;
}

/****************************************************************************
 * Name: gtm_timer_maxtimeout
 *
 * Description:
 *   Get the maximum timeout value supported by the timer (in microseconds).
 *
 ****************************************************************************/

static int gtm_timer_maxtimeout(FAR struct timer_lowerhalf_s *lower,
                                 FAR uint32_t *maxtimeout)
{
  struct rzv_gtm_lowerhalf_s *priv = (struct rzv_gtm_lowerhalf_s *)lower;
  uint64_t max_us;

  DEBUGASSERT(priv != NULL && maxtimeout != NULL);

  /* Maximum timeout = UINT32_MAX ticks / frequency in MHz */

  max_us = ((uint64_t)UINT32_MAX * 1000000ULL) / priv->frequency;

  /* Clamp to UINT32_MAX microseconds */

  if (max_us > UINT32_MAX)
    {
      *maxtimeout = UINT32_MAX;
    }
  else
    {
      *maxtimeout = (uint32_t)max_us;
    }

  tmrinfo("GTM%d: Maximum timeout is %lu microseconds\n",
          priv->channel, (unsigned long)*maxtimeout);

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_gtm_get_frequency
 *
 * Description:
 *   Get the clock frequency for a GTM channel in Hz.
 *
 * Input Parameters:
 *   channel - GTM channel number (0-7)
 *
 * Returned Value:
 *   Clock frequency in Hz, or 0 on error
 *
 ****************************************************************************/

uint32_t rzv_gtm_get_frequency(int channel)
{
  uint32_t freq;

  if (channel < 0 || channel >= RZV_GTM_MAX_CHANNELS)
    {
      return 0;
    }

  /* GTM source clock is P1CLK on RZ/V2H (BSP_FEATURE_GTM_SOURCE_CLOCK).
   * Query the runtime clock table first; fall back to compile-time constant
   * if the table has not yet been populated (early boot).
   */

  freq = rzv_clock_get_rate(RZV_CLOCK_P1CLK);
  if (freq == 0)
    {
      freq = RZV_GTM_FALLBACK_CLOCK_HZ;
      tmrwarn("GTM%d: P1CLK not in clock table, using fallback %lu Hz\n",
              channel, (unsigned long)freq);
    }

  return freq;
}

/****************************************************************************
 * Name: rzv_gtm_timer_initialize
 *
 * Description:
 *   Initialize GTM timer for use as NuttX timer device.
 *   Returns timer_lowerhalf_s interface for registration with
 *   timer_register().
 *
 * Input Parameters:
 *   channel - GTM channel number (0-7)
 *
 * Returned Value:
 *   Pointer to timer_lowerhalf_s on success, NULL on failure
 *
 ****************************************************************************/

FAR struct timer_lowerhalf_s *rzv_gtm_timer_initialize(int channel)
{
  struct rzv_gtm_lowerhalf_s *priv;
  uintptr_t base;
  uint32_t clk_id;
  int evt;
  int ret;

  tmrinfo("Initializing GTM%d\n", channel);

  /* Validate channel number */

  if (channel < 0 || channel >= RZV_GTM_MAX_CHANNELS)
    {
      tmrerr("ERROR: Invalid channel: %d\n", channel);
      return NULL;
    }

  /* Get base address */

  base = gtm_get_base(channel);
  if (base == 0)
    {
      tmrerr("ERROR: Failed to get base address for GTM%d\n", channel);
      return NULL;
    }

  /* Allocate private structure */

  priv = (struct rzv_gtm_lowerhalf_s *)
         kmm_zalloc(sizeof(struct rzv_gtm_lowerhalf_s));
  if (priv == NULL)
    {
      tmrerr("ERROR: Failed to allocate memory for GTM%d\n", channel);
      return NULL;
    }

  /* Initialize structure */

  priv->ops = &g_gtm_timer_ops;
  priv->base = base;
  priv->channel = channel;
  priv->frequency = rzv_gtm_get_frequency(channel);
  priv->timeout = 0;
  priv->irq = -1;
  priv->callback = NULL;
  priv->arg = NULL;

  /* Enable GTM clock via CPG */

  clk_id = gtm_get_clk_id(channel);
  if (clk_id == UINT32_MAX)
    {
      tmrerr("ERROR: Failed to get clock ID for GTM%d\n", channel);
      goto errout_with_priv;
    }

  ret = rzv_clock_enable(clk_id);
  if (ret < 0)
    {
      tmrerr("ERROR: Failed to enable clock for GTM%d: %d\n",
             channel, ret);
      goto errout_with_priv;
    }

  tmrinfo("GTM%d: Clock enabled (ID: 0x%08lx)\n", channel, (unsigned long)clk_id);

  /* Initialization sequence per RZ/V2H hardware reference:
   * 1. CPG clock enable + unreset (done above)
   * 2. Stop (idempotent)
   * 3. Set OSTMCTL = interval mode (MD1:MD0 = 00, no interrupt-on-start)
   * 4. Set OSTMCMP = compare value (default 1 s)
   * 5. Clear OSTMCNT defensively (write not supported on OSTM; counter
   *    resets at start — documented here for clarity)
   * 6. Attach IRQ
   * 7. Start is deferred to gtm_timer_start()
   *
   * Interval mode (MD1=0): counter reloads from OSTMCMP on each match,
   * IRQ fires every period.  Free-run (MD1=1) is for HRT only (GTM7).
   */

  /* Step 2: stop timer (idempotent if already stopped) */

  gtm_putreg8(priv, RZV_GTM_OSTMTT_OFFSET, GTM_OSTMTT_OSTMTT);

  /* Step 3: interval mode, no interrupt-on-start */

  gtm_putreg8(priv, RZV_GTM_OSTMCTL_OFFSET, GTM_MODE_INTERVAL);

  tmrinfo("GTM%d: Configured for interval mode\n", channel);

  /* Step 4: default compare value = 1 second */

  gtm_putreg32(priv, RZV_GTM_OSTMCMP_OFFSET, priv->frequency);
  priv->timeout = 1000000;  /* 1 second in microseconds */

  /* Step 6: attach interrupt handler via ICU */

  evt = gtm_get_elc_event(channel);
  if (evt < 0)
    {
      tmrerr("ERROR: Failed to get ELC event for GTM%d\n", channel);
      goto errout_with_clock;
    }

  ret = rzv_icu_attach(evt, gtm_interrupt, priv, true);
  if (ret < 0)
    {
      tmrerr("ERROR: Failed to attach interrupt for GTM%d: %d\n",
             channel, ret);
      goto errout_with_clock;
    }

  priv->irq = ret;

  tmrinfo("GTM%d: Interrupt attached (IRQ slot: %d, ELC event: 0x%02x)\n",
          channel, priv->irq, evt);

  /* Step 7: timer starts only when gtm_timer_start() is called */

  tmrinfo("GTM%d: Initialization complete (frequency: %lu Hz)\n",
          channel, (unsigned long)priv->frequency);

  return (FAR struct timer_lowerhalf_s *)priv;

errout_with_clock:
  rzv_clock_disable(clk_id);

errout_with_priv:
  kmm_free(priv);
  return NULL;
}
