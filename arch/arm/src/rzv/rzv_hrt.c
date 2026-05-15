/****************************************************************************
 * arch/arm/src/rzv/rzv_hrt.c
 *
 * PX4 High-Resolution Timer (HRT) shim for RZ/V2H, backed by GTM7.
 *
 * Design:
 *   GTM7 free-run mode (MD1=1, MD0=0) provides a free-running 32-bit
 *   counter at P1CLK (100 MHz → 10 ns resolution, ~42.9 s wrap period).
 *
 *   rzv_hrt_absolute_time() reads OSTMnCNT directly — no ISR needed for
 *   wall-clock.  The 64-bit accumulator (g_hrt_epoch_us) is updated on
 *   each counter overflow detected in rzv_hrt_absolute_time().
 *
 *   One-shot / periodic calls use the GTM7 compare register.  In one-shot
 *   mode the driver temporarily switches GTM7 to interval mode (auto-reload)
 *   so the compare fires, then restores free-run in the ISR.  Periodic mode
 *   leaves interval mode active.
 *
 *   Channel collision: GTM7 is dedicated to HRT.  GTM0-6 are available for
 *   NuttX timer devices.  The NuttX tick uses the CR8 ARM private timer (not
 *   any GTM channel).
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

#ifdef CONFIG_RZV_HRT

#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>

#include "arm_internal.h"
#include "hardware/rzv_gtm.h"
#include "rzv_icu.h"
#include "rzv_clock.h"
#include "rzv_hrt.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#ifndef getreg8
#  define getreg8(a)    (*(volatile uint8_t *)(a))
#endif

#ifndef putreg8
#  define putreg8(v, a) (*(volatile uint8_t *)(a) = (v))
#endif

#ifndef getreg32
#  define getreg32(a)    (*(volatile uint32_t *)(a))
#endif

#ifndef putreg32
#  define putreg32(v, a) (*(volatile uint32_t *)(a) = (v))
#endif

/* GTM7 base address (verified against FSP gtm_iodefine.h) */

#define HRT_GTM_BASE    RZV_GTM7_BASE

/* Register access shortcuts */

#define HRT_REG8(off)   (HRT_GTM_BASE + (off))
#define HRT_REG32(off)  (HRT_GTM_BASE + (off))

/* ELC event for GTM7 (from rzv2h_irq.h: 0x3C) */

#define HRT_ELC_EVENT   RZV_ELC_GTM7_GTMTINT

/* Minimum compare value to avoid immediate re-trigger */

#define HRT_MIN_TICKS   10U

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* HRT driver state */

struct rzv_hrt_state_s
{
  bool             initialized;   /* True after rzv_hrt_initialize() */
  bool             periodic;      /* True for hrt_call_every, false for one-shot */
  uint32_t         clock_hz;      /* GTM source clock in Hz (P1CLK) */
  uint32_t         last_cnt;      /* Last sampled counter — for overflow detection */
  uint64_t         accum_ticks;   /* Accumulated 64-bit ticks across overflows */
  rzv_hrt_callback_t callback;    /* User callback (NULL = none) */
  void            *arg;           /* Callback argument */
  int              irq;           /* Allocated ICU IRQ number, or -1 */
};

/****************************************************************************
 * Private Data
 ****************************************************************************/

static struct rzv_hrt_state_s g_hrt;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: hrt_get_clock_hz
 *
 * Description:
 *   Return GTM source clock (P1CLK).  Falls back to compile-time constant
 *   if clock table not yet populated.
 *
 ****************************************************************************/

static uint32_t hrt_get_clock_hz(void)
{
  uint32_t freq = rzv_clock_get_rate(RZV_CLOCK_P1CLK);

  if (freq == 0)
    {
      freq = RZV_GTM_FALLBACK_CLOCK_HZ;
    }

  return freq;
}

/****************************************************************************
 * Name: hrt_cnt_to_us
 *
 * Description:
 *   Convert a raw tick count to microseconds using the P1CLK frequency.
 *
 ****************************************************************************/

static inline uint64_t hrt_cnt_to_us(uint64_t ticks, uint32_t clock_hz)
{
  /* Avoid 64-bit division when possible: if clock_hz is a power of two
   * this reduces to a shift, but the general division path is fine for
   * initialization-time calls.
   */

  return (ticks * 1000000ULL) / (uint64_t)clock_hz;
}

/****************************************************************************
 * Name: hrt_isr
 *
 * Description:
 *   GTM7 compare-match ISR.  Must complete in < 2 µs — no logging, no mutex.
 *
 ****************************************************************************/

static int hrt_isr(int irq, void *context, void *arg)
{
  rzv_hrt_callback_t cb;
  void *cb_arg;

  /* Clear ICU state for this slot */

  rzv_icu_clear_irq(irq);

  /* For one-shot: stop timer, snapshot accum, switch back to free-run mode.
   * Snapshot before stop for the same reason as hrt_arm_compare: OSTMTS
   * zeroes OSTMnCNT, so we must commit elapsed ticks before restarting to
   * keep accum_ticks monotonic.  UP-only: relies on CR8 single-core;
   * SMP would need spin_lock_irqsave here. */

  if (!g_hrt.periodic)
    {
      uint32_t cur_cnt = getreg32(HRT_REG32(RZV_GTM_OSTMCNT_OFFSET));
      g_hrt.accum_ticks += (uint64_t)(cur_cnt - g_hrt.last_cnt);

      putreg8(GTM_OSTMTT_OSTMTT, HRT_REG8(RZV_GTM_OSTMTT_OFFSET));  /* stop */
      putreg8(GTM_MODE_FREERUN,  HRT_REG8(RZV_GTM_OSTMCTL_OFFSET));  /* free-run */
      putreg8(GTM_OSTMTS_OSTMTS, HRT_REG8(RZV_GTM_OSTMTS_OFFSET));  /* start — CNT resets to 0 */

      g_hrt.last_cnt = 0;  /* re-baseline after OSTMTS */
    }

  /* Snapshot callback pointers then invoke — avoids race with rzv_hrt_cancel */

  cb     = g_hrt.callback;
  cb_arg = g_hrt.arg;

  if (cb != NULL)
    {
      if (!g_hrt.periodic)
        {
          /* Clear before invoking so callback can re-arm */

          g_hrt.callback = NULL;
          g_hrt.arg      = NULL;
        }

      cb(cb_arg);
    }

  return OK;
}

/****************************************************************************
 * Name: hrt_arm_compare
 *
 * Description:
 *   Program GTM7 for a compare-match after 'ticks' counter ticks.
 *   'interval' selects MD1=0 (interval/auto-reload) vs MD1=1 (free-run with
 *   compare).  For one-shot we use interval mode momentarily so the compare
 *   fires, then ISR restores free-run.
 *
 *   Caller holds critical section.
 *
 ****************************************************************************/

static void hrt_arm_compare(uint32_t ticks, bool interval)
{
  uint8_t mode;

  /* Clamp minimum to avoid immediate re-trigger before ISR is dispatched */

  if (ticks < HRT_MIN_TICKS)
    {
      ticks = HRT_MIN_TICKS;
    }

  mode = interval ? GTM_MODE_INTERVAL : GTM_MODE_FREERUN;

  /* Snapshot elapsed ticks into accum_ticks BEFORE stopping the counter.
   * After OSTMTS (start), OSTMnCNT resets to 0 (RZ/V2H OSTM TRM behavior —
   * hardware zeroes CNT on every start; if TRM confirms otherwise this block
   * remains correct: last_cnt=0, cnt=small → delta=small → no false advance).
   * Without this snapshot, last_cnt would exceed the new (zeroed) cnt giving
   * delta = (0 - old_last_cnt) ≈ UINT32_MAX → ~42 s phantom advance.
   * All of this must be done inside the caller's critical section. */
  {
    uint32_t cur_cnt = getreg32(HRT_REG32(RZV_GTM_OSTMCNT_OFFSET));
    g_hrt.accum_ticks += (uint64_t)(cur_cnt - g_hrt.last_cnt);
  }

  putreg8(GTM_OSTMTT_OSTMTT, HRT_REG8(RZV_GTM_OSTMTT_OFFSET));  /* stop */
  putreg32(ticks,             HRT_REG32(RZV_GTM_OSTMCMP_OFFSET));
  putreg8(mode,               HRT_REG8(RZV_GTM_OSTMCTL_OFFSET));
  putreg8(GTM_OSTMTS_OSTMTS, HRT_REG8(RZV_GTM_OSTMTS_OFFSET));  /* start — CNT resets to 0 */

  /* Re-baseline: counter is now 0 after OSTMTS. */
  g_hrt.last_cnt = 0;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_hrt_initialize
 ****************************************************************************/

int rzv_hrt_initialize(void)
{
  int ret;

  if (g_hrt.initialized)
    {
      return OK;
    }

  /* Enable GTM7 clock and unreset via CPG.
   * RZV_CPG_CLK_GTM7 = domain 5, bit 7 (placeholder, unverified vs UM).
   * Clock enable failure is non-fatal at this stage — hardware may already
   * be clocked (bootloader) — log and proceed.
   */

  ret = rzv_clock_enable(RZV_CPG_CLK_GTM7);
  if (ret < 0)
    {
      tmrwarn("HRT: Failed to enable GTM7 clock: %d (proceeding)\n", ret);
    }

  ret = rzv_module_unreset(RZV_CPG_CLK_GTM7);
  if (ret < 0)
    {
      tmrwarn("HRT: Failed to unreset GTM7: %d (proceeding)\n", ret);
    }

  g_hrt.clock_hz    = hrt_get_clock_hz();
  g_hrt.last_cnt    = 0;
  g_hrt.accum_ticks = 0;
  g_hrt.callback    = NULL;
  g_hrt.arg         = NULL;
  g_hrt.periodic    = false;
  g_hrt.irq         = -1;

  /* Stop GTM7, configure free-run mode (MD1=1, MD0=0), set compare to max,
   * then start.  The counter now runs continuously — rzv_hrt_absolute_time()
   * reads it at any time without an ISR.
   */

  putreg8(GTM_OSTMTT_OSTMTT, HRT_REG8(RZV_GTM_OSTMTT_OFFSET));
  putreg32(UINT32_MAX,        HRT_REG32(RZV_GTM_OSTMCMP_OFFSET));
  putreg8(GTM_MODE_FREERUN,  HRT_REG8(RZV_GTM_OSTMCTL_OFFSET));
  putreg8(GTM_OSTMTS_OSTMTS, HRT_REG8(RZV_GTM_OSTMTS_OFFSET));

  /* Attach IRQ via ICU (used by hrt_call_after/every) */

  ret = rzv_icu_attach(HRT_ELC_EVENT, hrt_isr, NULL, true);
  if (ret < 0)
    {
      tmrerr("HRT: Failed to attach GTM7 IRQ: %d\n", ret);

      /* HRT absolute time still works; call scheduling will not */

      g_hrt.irq = -1;
    }
  else
    {
      g_hrt.irq = ret;
    }

  g_hrt.initialized = true;

  tmrinfo("HRT: initialized GTM7, P1CLK = %lu Hz, IRQ = %d\n",
          (unsigned long)g_hrt.clock_hz, g_hrt.irq);

  return OK;
}

/****************************************************************************
 * Name: rzv_hrt_absolute_time
 *
 * Description:
 *   Returns microseconds since rzv_hrt_initialize().
 *
 *   Overflow handling: the 32-bit counter wraps every ~42.9 s at 100 MHz.
 *   We detect wraps by comparing the current counter to the last sampled
 *   value.  This is safe only if called more frequently than the wrap period.
 *   For PX4 use this is always satisfied (hrt_work runs at ≥1 Hz).
 *
 ****************************************************************************/

uint64_t rzv_hrt_absolute_time(void)
{
  uint32_t cnt1;
  uint32_t cnt2;
  uint64_t accum;
  uint32_t last;
  uint32_t delta;
  irqstate_t flags;

  /* Lockless fast path (Lamport read): sample cnt, read shared state, sample
   * cnt again.  If cnt2 >= cnt1, no wrap/stop-start occurred during the read
   * so the snapshot is coherent.  Use cnt2 as the current value.
   * Falls back to a CS-protected update if the retry loop detects a race
   * (stop+start in hrt_arm_compare or hrt_isr resets last_cnt and accum
   * while we were reading — caught by cnt2 < cnt1 after the second read).
   * On UP/CR8 with no concurrent threads reading this path this degenerates
   * to two register reads with no lock overhead on the happy path. */

  cnt1  = getreg32(HRT_REG32(RZV_GTM_OSTMCNT_OFFSET));
  accum = g_hrt.accum_ticks;
  last  = g_hrt.last_cnt;
  cnt2  = getreg32(HRT_REG32(RZV_GTM_OSTMCNT_OFFSET));

  if (cnt2 < cnt1)
    {
      /* A stop+start (or wrap) raced with our read; fall back to CS path. */
      flags = enter_critical_section();
      cnt2  = getreg32(HRT_REG32(RZV_GTM_OSTMCNT_OFFSET));
      accum = g_hrt.accum_ticks;
      last  = g_hrt.last_cnt;
      g_hrt.accum_ticks += (uint64_t)(cnt2 - last);
      g_hrt.last_cnt     = cnt2;
      accum = g_hrt.accum_ticks;
      leave_critical_section(flags);
      return hrt_cnt_to_us(accum, g_hrt.clock_hz);
    }

  /* Happy path: compute delta from the coherent snapshot without modifying
   * shared state.  Note: accum_ticks is updated lazily here (read-only path).
   * Writers (hrt_arm_compare, hrt_isr) commit their own delta under CS before
   * resetting last_cnt, so this read is always consistent.
   * Detect 32-bit counter wrap correctly via unsigned subtraction. */
  delta = cnt2 - last;
  return hrt_cnt_to_us(accum + (uint64_t)delta, g_hrt.clock_hz);
}

/****************************************************************************
 * Name: rzv_hrt_call_after
 ****************************************************************************/

int rzv_hrt_call_after(uint32_t delay_us, rzv_hrt_callback_t callback,
                       void *arg)
{
  irqstate_t flags;
  uint64_t   ticks64;

  if (!g_hrt.initialized)
    {
      return -ENODEV;
    }

  if (callback == NULL || delay_us == 0)
    {
      return -EINVAL;
    }

  if (g_hrt.irq < 0)
    {
      /* IRQ not wired; cannot schedule */

      return -ENOSYS;
    }

  ticks64 = ((uint64_t)delay_us * g_hrt.clock_hz) / 1000000ULL;
  if (ticks64 > UINT32_MAX)
    {
      return -ERANGE;
    }

  flags = enter_critical_section();

  g_hrt.callback = callback;
  g_hrt.arg      = arg;
  g_hrt.periodic = false;

  /* Arm in interval mode — ISR fires, then ISR restores free-run */

  hrt_arm_compare((uint32_t)ticks64, true /* interval momentarily */);

  leave_critical_section(flags);

  return OK;
}

/****************************************************************************
 * Name: rzv_hrt_call_every
 ****************************************************************************/

int rzv_hrt_call_every(uint32_t period_us, rzv_hrt_callback_t callback,
                       void *arg)
{
  irqstate_t flags;
  uint64_t   ticks64;

  if (!g_hrt.initialized)
    {
      return -ENODEV;
    }

  if (callback == NULL || period_us == 0)
    {
      return -EINVAL;
    }

  if (g_hrt.irq < 0)
    {
      return -ENOSYS;
    }

  ticks64 = ((uint64_t)period_us * g_hrt.clock_hz) / 1000000ULL;
  if (ticks64 > UINT32_MAX)
    {
      return -ERANGE;
    }

  flags = enter_critical_section();

  g_hrt.callback = callback;
  g_hrt.arg      = arg;
  g_hrt.periodic = true;

  /* Interval mode: GTM auto-reloads OSTMCMP on each match */

  hrt_arm_compare((uint32_t)ticks64, true /* interval = auto-reload */);

  leave_critical_section(flags);

  return OK;
}

/****************************************************************************
 * Name: rzv_hrt_cancel
 ****************************************************************************/

void rzv_hrt_cancel(void)
{
  irqstate_t flags;

  if (!g_hrt.initialized)
    {
      return;
    }

  flags = enter_critical_section();

  g_hrt.callback = NULL;
  g_hrt.arg      = NULL;
  g_hrt.periodic = false;

  /* Stop compare-match; restore free-run so absolute_time keeps working */

  putreg8(GTM_OSTMTT_OSTMTT, HRT_REG8(RZV_GTM_OSTMTT_OFFSET));
  putreg32(UINT32_MAX,        HRT_REG32(RZV_GTM_OSTMCMP_OFFSET));
  putreg8(GTM_MODE_FREERUN,  HRT_REG8(RZV_GTM_OSTMCTL_OFFSET));
  putreg8(GTM_OSTMTS_OSTMTS, HRT_REG8(RZV_GTM_OSTMTS_OFFSET));

  leave_critical_section(flags);
}

#endif /* CONFIG_RZV_HRT */
