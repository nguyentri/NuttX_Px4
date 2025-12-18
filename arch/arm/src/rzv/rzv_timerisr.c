/****************************************************************************
 * arch/arm/src/rzv/rzv_timerisr.c
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
#include <time.h>
#include <debug.h>

#include <nuttx/arch.h>
#include <nuttx/clock.h>
#include <nuttx/spinlock.h>

#include "arm_internal.h"
#include "rzv_clock.h"
#include "hardware/rzv_private_timer.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Timer configuration */

/* Timer prescaler default: if not provided, use 0 (divide by 1) */
#ifndef TIMER_PRESCALER
#  define TIMER_PRESCALER 0
#endif

/* TIMER_FREQ will be computed at runtime from peripheral clock */
#define TIMER_FREQ_RUNTIME() rzv_get_pclk_frequency()

/****************************************************************************
 * Private Data
 ****************************************************************************/

static uint32_t g_timer_load_value;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_timerisr
 *
 * Description:
 *   The timer ISR will perform a variety of services for various portions
 *   of the system.
 *
 ****************************************************************************/

static int rzv_timerisr(int irq, void *context, void *arg)
{
  /* Clear the interrupt */

  putreg32(PRIVATE_TIMER_PTISR_CLR, RZV_PRIVATE_TIMER_PTISR);

  /* Process timer interrupt */

  nxsched_process_timer();

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: up_timer_initialize
 *
 * Description:
 *   This function is called during start-up to initialize the timer
 *   interrupt.
 *
 ****************************************************************************/

void up_timer_initialize(void)
{
  uint32_t periphclk;
  uint32_t load_value;
  uint32_t ctrl;

  /* Get peripheral clock frequency */

  periphclk = rzv_get_pclk_frequency();

  /* Calculate load value for desired tick rate
   * Load value = (Clock Frequency / (Prescaler + 1) / Tick Rate) - 1
   */

  load_value = (periphclk / (TIMER_PRESCALER + 1) / CLOCKS_PER_SEC) - 1;
  g_timer_load_value = load_value;

  tmrinfo("Timer initialization: freq=%lu prescaler=%u load=%lu\n",
          periphclk, TIMER_PRESCALER, load_value);

  /* Disable timer */

  putreg32(0, RZV_PRIVATE_TIMER_PTCTLR);

  /* Set the load value */

  putreg32(load_value, RZV_PRIVATE_TIMER_PTLR);

  /* Set the prescaler */

  ctrl = (TIMER_PRESCALER << PRIVATE_TIMER_PTCTLR_PRESCALER_SHIFT) &
         PRIVATE_TIMER_PTCTLR_PRESCALER_MASK;

  /* Enable auto-reload and interrupts */

  ctrl |= PRIVATE_TIMER_PTCTLR_AR | PRIVATE_TIMER_PTCTLR_IRQE;

  putreg32(ctrl, RZV_PRIVATE_TIMER_PTCTLR);

  /* Attach the timer interrupt handler */

  irq_attach(RZV_ELC_CMTW_CH0_CMT2_ELCCMP, rzv_timerisr, NULL);

  /* Enable the timer interrupt */

  up_enable_irq(RZV_ELC_CMTW_CH0_CMT2_ELCCMP);

  /* Enable the timer */

  ctrl |= PRIVATE_TIMER_PTCTLR_TE;
  putreg32(ctrl, RZV_PRIVATE_TIMER_PTCTLR);

  tmrinfo("Timer started\n");
}

/****************************************************************************
 * Name: up_timer_gettime
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
 *   Provided by platform-specific code and called from the RTOS base code.
 *
 * Input Parameters:
 *   ts - Provides the location in which to return the up-time.
 *
 * Returned Value:
 *   Zero (OK) is returned on success; a negated errno value is returned on
 *   any failure.
 *
 * Assumptions:
 *   Called from the normal tasking context.
 *
 ****************************************************************************/

#ifdef CONFIG_CLOCK_TIMEKEEPING
int up_timer_gettime(struct timespec *ts)
{
  uint64_t usec;
  uint32_t counter;
  uint32_t load;
  irqstate_t flags;

  flags = spin_lock_irqsave(NULL);

  /* Get the current counter value and load value */

  counter = getreg32(RZV_PRIVATE_TIMER_PTCR);
  load = g_timer_load_value;

  /* Calculate elapsed time in microseconds
   * The counter counts down from load value
   */

  usec = (uint64_t)(load - counter) * USEC_PER_SEC /
    (TIMER_FREQ_RUNTIME() / (TIMER_PRESCALER + 1));

  /* Add the accumulated tick count */

  usec += (uint64_t)clock_systime_ticks() * USEC_PER_TICK;

  spin_unlock_irqrestore(NULL, flags);

  /* Convert to timespec */

  ts->tv_sec  = usec / USEC_PER_SEC;
  ts->tv_nsec = (usec % USEC_PER_SEC) * NSEC_PER_USEC;

  return OK;
}
#endif

/****************************************************************************
 * Name: up_timer_getcounter
 *
 * Description:
 *   Return the current value of the free-running timer counter.
 *
 ****************************************************************************/

uint32_t up_timer_getcounter(void)
{
  return getreg32(RZV_PRIVATE_TIMER_PTCR);
}

/****************************************************************************
 * Name: up_timer_getfreq
 *
 * Description:
 *   Return the frequency of the free-running timer counter.
 *
 ****************************************************************************/

uint32_t up_timer_getfreq(void)
{
  return TIMER_FREQ_RUNTIME() / (TIMER_PRESCALER + 1);
}