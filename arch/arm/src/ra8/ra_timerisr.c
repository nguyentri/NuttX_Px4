/****************************************************************************
 * arch/arm/src/ra8/ra_timerisr.c
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
#include <debug.h>
#include <assert.h>

#include <nuttx/arch.h>
#include <nuttx/irq.h>
#include <nuttx/clock.h>
#include <arch/board/board.h>
#include <arch/irq.h>
#include <syslog.h>

#include "nvic.h"
#include "chip.h"
#include "arm_internal.h"
#include "ra_clock.h"
#include "ra_icu.h"
#include "ra_mstp.h"
#include "hardware/ra_gpt.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#  define SYSTICK_CLOCK     RA_CPUCLK_FREQUENCY
#  define SYSTICK_RELOAD    ((SYSTICK_CLOCK / CLK_TCK) - 1)

/* The size of the reload field is 24 bits.  Verify that the reload value
 * will fit in the reload register.
 */

#define SYSTICK_MAX 0x00ffffff
#if defined(SYSTICK_RELOAD) && SYSTICK_RELOAD > SYSTICK_MAX
#  error SYSTICK_RELOAD exceeds the range of the RELOAD register
#endif

/****************************************************************************
 * Private Data
 * ************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Function:  ra_timer_arch_isr
 *
 * Description:
 *   The timer ISR will perform a variety of services for various portions
 *   of the systems.
 *
 ****************************************************************************/
int ra_timer_arch_isr(int irq, void *context, void *arg)
{
  /* Process timer interrupt */
  nxsched_process_timer();
  return 0;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Function:  up_timer_initialize
 *
 * Description:
 *   This function is called during start-up to initialize
 *   the timer interrupt. Implementation based on working
 *   and adapted for NuttX system timer requirements.
 *
 ****************************************************************************/

void up_timer_initialize(void)
{
  uint32_t regval;

  /* Disable SysTick during setup */
  putreg32(0, NVIC_SYSTICK_CTRL);

  /* Clear current value register */
  putreg32(0, NVIC_SYSTICK_CURRENT);

  /* Set reload register value for desired tick rate */
  /* SYSTICK_RELOAD should be calculated as (SYSTICK_CLOCK / CLK_TCK) - 1 */
  DEBUGASSERT(SYSTICK_RELOAD > 0 && SYSTICK_RELOAD <= SYSTICK_MAX);
  putreg32(SYSTICK_RELOAD, NVIC_SYSTICK_RELOAD);

  /* Attach the SysTick interrupt handler */
  /* SysTick uses a fixed exception number (-1) which maps to a specific IRQ */
  irq_attach(RA_IRQ_SYSTICK, (xcpt_t)ra_timer_arch_isr, NULL);

  /* Configure and enable SysTick:
   * - ENABLE: Enable the counter
   * - TICKINT: Enable SysTick exception request
   * - CLKSOURCE: Use processor clock as source (set to 1)
   *   If CLKSOURCE = 0, uses external reference clock
   *   If CLKSOURCE = 1, uses processor clock
   */
  regval = NVIC_SYSTICK_CTRL_ENABLE | NVIC_SYSTICK_CTRL_TICKINT | NVIC_SYSTICK_CTRL_CLKSOURCE;
  putreg32(regval, NVIC_SYSTICK_CTRL);

  /* SysTick is now configured and will generate periodic interrupts
   * at the rate specified by CLK_TCK (typically 1000Hz for NuttX)
   */
  //syslog(LOG_INFO, "Nuttx: Clock = %u MHz, Tick rate = %u Hz (reload = %u)\n",
  //      SYSTICK_CLOCK / 1000000, CLK_TCK, SYSTICK_RELOAD + 1);
}

/****************************************************************************
 * Function:  up_timer_gettime
 *
 * Description:
 *   Return the elapsed time since power-up (or, more correctly, since
 *   up_timer_initialize() was called).  This function is functionally
 *   equivalent to:
 *
 *      int clock_gettime(clockid_t clockid, struct timespec *ts);
 *
 *   when clockid is CLOCK_MONOTONIC.
 *
 *   This function provides the basis for reporting the current time and
 *   also is used to eliminate error build-up from small errors in interval
 *   time calculations.
 *
 * Input Parameters:
 *   ts - Provides the location in which to return the up-time.
 *
 * Returned Value:
 *   Zero (OK) is returned on success; a negated errno value is returned on
 *   any failure.
 *
 * Assumptions:
 *   Called from the normal tasking context.  The implementation must
 *   provide whatever mutual exclusion is necessary for correct operation.
 *   This can include disabling interrupts in order to assure atomic register
 *   operations.
 *
 ****************************************************************************/

int up_timer_gettime(struct timespec *ts)
{
  uint64_t usecs;
  uint32_t reload;
  uint32_t current;
  uint32_t elapsed;
  irqstate_t flags;

  DEBUGASSERT(ts != NULL);

  /* Get the reload and current counter values and the tick count, being
   * careful that we get a coherent set of values.
   */

  flags = enter_critical_section();

  /* Get SysTick registers */
  reload  = getreg32(NVIC_SYSTICK_RELOAD) + 1;
  current = getreg32(NVIC_SYSTICK_CURRENT);

  /* Get the number of full ticks elapsed */
  usecs = clock_systime_ticks() * USEC_PER_TICK;

  /* Add the partial tick time */
  elapsed = reload - current;
  usecs  += (elapsed * USEC_PER_TICK) / reload;

  leave_critical_section(flags);

  /* Convert to timespec */
  ts->tv_sec  = usecs / USEC_PER_SEC;
  ts->tv_nsec = (usecs % USEC_PER_SEC) * NSEC_PER_USEC;

  return OK;
}

/****************************************************************************
 * Function:  up_timer_cancel
 *
 * Description:
 *   Cancel the interval timer and return the time remaining on the timer.
 *   These two steps need to be as nearly atomic as possible.
 *   nxsched_timer_expiration() will not be called unless the timer is
 *   restarted with up_timer_start().
 *
 *   If, as a race condition, the timer has already expired when this
 *   function is called, then that pending interrupt must be cleared so
 *   that up_timer_start() and the remaining time of zero should be
 *   returned.
 *
 *   NOTE: This function may execute at a high rate with no timer running (as
 *   when pre-emption is enabled and disabled).
 *
 * Input Parameters:
 *   ts - Location to return the remaining time.  Zero should be returned
 *        if the timer is not active.  ts may be zero in which case the
 *        time remaining is not returned.
 *
 * Returned Value:
 *   Zero (OK) is returned on success.  A call to up_timer_cancel() when
 *   the timer is not active should also return success; a negated errno
 *   value is returned on any failure.
 *
 * Assumptions:
 *   May be called from interrupt level handling or from the normal tasking
 *   level.  Interrupts may need to be disabled internally to assure
 *   non-reentrancy.
 *
 ****************************************************************************/

int up_timer_cancel(struct timespec *ts)
{
  uint32_t reload;
  uint32_t current;
  uint32_t remaining;

  if (ts != NULL)
    {
      /* Get the current SysTick state */
      reload  = getreg32(NVIC_SYSTICK_RELOAD) + 1;
      current = getreg32(NVIC_SYSTICK_CURRENT);

      /* Calculate remaining time in this tick period */
      remaining = current;

      /* Convert to microseconds */
      uint32_t remaining_usecs = (remaining * USEC_PER_TICK) / reload;

      /* Convert to timespec */
      ts->tv_sec  = 0;
      ts->tv_nsec = remaining_usecs * NSEC_PER_USEC;
    }

  /* Disable SysTick temporarily */
  putreg32(0, NVIC_SYSTICK_CTRL);

  /* Clear current counter */
  putreg32(0, NVIC_SYSTICK_CURRENT);

  return OK;
}

/****************************************************************************
 * Function:  up_timer_start
 *
 * Description:
 *   Start the interval timer.  nxsched_timer_expiration() will be called at
 *   the completion of the timeout (unless up_timer_cancel is called to stop
 *   the timing).
 *
 *   Provided by platform-specific code and called from the RTOS base code.
 *
 * Input Parameters:
 *   ts - Provides the time interval until nxsched_timer_expiration() is
 *        called.
 *
 * Returned Value:
 *   Zero (OK) is returned on success; a negated errno value is returned on
 *   any failure.
 *
 * Assumptions:
 *   May be called from interrupt level handling or from the normal tasking
 *   level.  Interrupts may need to be disabled internally to assure
 *   non-reentrancy.
 *
 ****************************************************************************/

int up_timer_start(const struct timespec *ts)
{
  uint64_t usecs;
  uint32_t reload_val;
  uint32_t regval;

  DEBUGASSERT(ts != NULL);

  /* Convert timespec to microseconds */
  usecs = (uint64_t)ts->tv_sec * USEC_PER_SEC +
          (uint64_t)ts->tv_nsec / NSEC_PER_USEC;

  /* Convert microseconds to SysTick counts */
  reload_val = (usecs * SYSTICK_CLOCK) / USEC_PER_SEC;

  /* Ensure reload value is within valid range */
  if (reload_val == 0)
    {
      reload_val = 1;
    }
  else if (reload_val > SYSTICK_MAX)
    {
      reload_val = SYSTICK_MAX;
    }

  /* Disable SysTick during setup */
  putreg32(0, NVIC_SYSTICK_CTRL);

  /* Clear current value */
  putreg32(0, NVIC_SYSTICK_CURRENT);

  /* Set new reload value */
  putreg32(reload_val - 1, NVIC_SYSTICK_RELOAD);

  /* Enable SysTick with interrupt and processor clock */
  regval = NVIC_SYSTICK_CTRL_ENABLE | NVIC_SYSTICK_CTRL_TICKINT | NVIC_SYSTICK_CTRL_CLKSOURCE;
  putreg32(regval, NVIC_SYSTICK_CTRL);

  return OK;
}
