/****************************************************************************
 * arch/arm/src/ra8/ra_ulpt.c
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
#include <nuttx/arch.h>
#include <arch/board/board.h>

#include "arm_internal.h"
#include "chip.h"
#include "ra_ulpt.h"
#include "ra_mstp.h"
#include "ra_icu.h"

#if defined(CONFIG_RA_ULPT)

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Register access macros */

#define getreg8(a)       (*(volatile uint8_t *)(a))
#define getreg32(a)      (*(volatile uint32_t *)(a))
#define putreg8(v,a)     (*(volatile uint8_t *)(a) = (v))
#define putreg32(v,a)    (*(volatile uint32_t *)(a) = (v))

/* LOCO frequency - typically 32.768 kHz */

#define RA_LOCO_FREQ_HZ  32768

/* ULPT control register bits */

#define ULPTCR_TSTART    (1 << 0)
#define ULPTCR_TCSTF     (1 << 1)
#define ULPTCR_TSTOP     (1 << 2)
#define ULPTCR_TUNDF     (1 << 5)
#define ULPTCR_TCMAF     (1 << 6)
#define ULPTCR_TCMBF     (1 << 7)
#define ULPTCR_FLAGS     (ULPTCR_TUNDF | ULPTCR_TCMAF | ULPTCR_TCMBF)

/****************************************************************************
 * Private Types
 ****************************************************************************/

struct ra_ulpt_channel_s
{
  bool initialized;
  bool running;
  struct ra_ulpt_config_s config;
  int irq;
};

/****************************************************************************
 * Private Data
 ****************************************************************************/

static struct ra_ulpt_channel_s g_ulpt_channels[RA_ULPT_CHANNELS];

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_ulpt_interrupt
 *
 * Description:
 *   ULPT interrupt handler
 *
 ****************************************************************************/

static int ra_ulpt_interrupt(int irq, FAR void *context, FAR void *arg)
{
  struct ra_ulpt_channel_s *priv = (struct ra_ulpt_channel_s *)arg;
  uint8_t flags;
  int channel;

  DEBUGASSERT(priv != NULL);

  channel = priv->config.channel;

  /* Read and clear interrupt flags */

  flags = getreg8(R_ULPT_ULPTCR(channel));

  if (flags & ULPTCR_FLAGS)
    {
      /* Clear flags by writing 0 to them */

      putreg8(flags & ~ULPTCR_FLAGS, R_ULPT_ULPTCR(channel));

      /* Call user callback if registered */

      if (priv->config.callback != NULL)
        {
          priv->config.callback(channel, priv->config.callback_arg);
        }
    }

  return OK;
}

/****************************************************************************
 * Name: ra_ulpt_enable_module
 *
 * Description:
 *   Enable ULPT module clocking via MSTP
 *
 ****************************************************************************/

static void ra_ulpt_enable_module(int channel)
{
  /* ULPT0 and ULPT1 are controlled by MSTPCRE bits
   * ULPT0: MSTPCRE9
   * ULPT1: MSTPCRE8
   */

  if (channel == 0)
    {
      ra_mstp_start(RA_MSTP_ULPT0);
    }
  else
    {
      ra_mstp_start(RA_MSTP_ULPT1);
    }
}

/****************************************************************************
 * Name: ra_ulpt_disable_module
 *
 * Description:
 *   Disable ULPT module clocking via MSTP
 *
 ****************************************************************************/

static void ra_ulpt_disable_module(int channel)
{
  if (channel == 0)
    {
      ra_mstp_stop(RA_MSTP_ULPT0);
    }
  else
    {
      ra_mstp_stop(RA_MSTP_ULPT1);
    }
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_ulpt_initialize
 *
 * Description:
 *   Initialize a ULPT channel
 *
 ****************************************************************************/

int ra_ulpt_initialize(FAR const struct ra_ulpt_config_s *config)
{
  struct ra_ulpt_channel_s *priv;
  uint8_t ulptmr1;
  uint8_t ulptmr2;
  uint8_t ulptcmsr;
  int channel;

  if (config == NULL)
    {
      return -EINVAL;
    }

  channel = config->channel;
  if (channel >= RA_ULPT_CHANNELS)
    {
      return -EINVAL;
    }

  priv = &g_ulpt_channels[channel];

  if (priv->initialized)
    {
      return -EBUSY;
    }

  /* Enable module clocking */

  ra_ulpt_enable_module(channel);

  /* Stop timer if running */

  putreg8(ULPTCR_TSTOP, R_ULPT_ULPTCR(channel));

  /* Wait for timer to stop */

  while (getreg8(R_ULPT_ULPTCR(channel)) & ULPTCR_TCSTF)
    {
      /* Spin */
    }

  /* Configure ULPTMR1 - clock source and mode */

  ulptmr1 = 0;
  if (config->clock == RA_ULPT_CLOCK_SUBCLOCK)
    {
      ulptmr1 |= R_ULPT_ULPTMR1_TCK1;
    }

  putreg8(ulptmr1, R_ULPT_ULPTMR1(channel));

  /* Configure ULPTMR2 - clock divider and low power mode */

  ulptmr2 = config->divider & R_ULPT_ULPTMR2_CKS_MASK;
  if (config->low_power_mode)
    {
      ulptmr2 |= R_ULPT_ULPTMR2_LPM;
    }

  putreg8(ulptmr2, R_ULPT_ULPTMR2(channel));

  /* Configure compare match registers */

  ulptcmsr = 0;
  if (config->compare_a_enable)
    {
      ulptcmsr |= R_ULPT_ULPTCMSR_TCMEA;
      putreg32(config->compare_a, R_ULPT_ULPTCMA(channel));
    }

  if (config->compare_b_enable)
    {
      ulptcmsr |= R_ULPT_ULPTCMSR_TCMEB;
      putreg32(config->compare_b, R_ULPT_ULPTCMB(channel));
    }

  putreg8(ulptcmsr, R_ULPT_ULPTCMSR(channel));

  /* Set period (counter value) */

  putreg32(config->period, R_ULPT_ULPTCNT(channel));

  /* Store configuration */

  memcpy(&priv->config, config, sizeof(struct ra_ulpt_config_s));

  /* Attach interrupt handler if callback provided */

  if (config->callback != NULL)
    {
      /* Get the IRQ number for this channel */

#ifdef CONFIG_RA8P1_GROUP
      priv->irq = (channel == 0) ? RA_ELC_ULPT0_INT :
                                   RA_ELC_ULPT1_INT;
#else
      priv->irq = (channel == 0) ? RA_ELC_ULPT0_INT :
                                   RA_ELC_ULPT1_INT;
#endif

      /* Attach and enable interrupt */

      priv->irq = ra_icu_attach(priv->irq, ra_ulpt_interrupt, priv, true);
      if (priv->irq < 0)
        {
          tmrerr("Failed to attach ULPT%d interrupt\n", channel);
          ra_ulpt_disable_module(channel);
          return priv->irq;
        }
    }

  priv->initialized = true;
  priv->running = false;

  tmrinfo("ULPT%d initialized, period=%lu\n", channel, config->period);

  return OK;
}

/****************************************************************************
 * Name: ra_ulpt_start
 *
 * Description:
 *   Start the ULPT timer
 *
 ****************************************************************************/

int ra_ulpt_start(int channel)
{
  struct ra_ulpt_channel_s *priv;
  uint8_t ulptcr;

  if (channel >= RA_ULPT_CHANNELS)
    {
      return -EINVAL;
    }

  priv = &g_ulpt_channels[channel];

  if (!priv->initialized)
    {
      return -EAGAIN;
    }

  if (priv->running)
    {
      return OK;
    }

  /* Clear status flags and start timer */

  ulptcr = getreg8(R_ULPT_ULPTCR(channel));
  ulptcr &= ~ULPTCR_FLAGS;
  ulptcr |= ULPTCR_TSTART;
  putreg8(ulptcr, R_ULPT_ULPTCR(channel));

  priv->running = true;

  tmrinfo("ULPT%d started\n", channel);

  return OK;
}

/****************************************************************************
 * Name: ra_ulpt_stop
 *
 * Description:
 *   Stop the ULPT timer
 *
 ****************************************************************************/

int ra_ulpt_stop(int channel)
{
  struct ra_ulpt_channel_s *priv;

  if (channel >= RA_ULPT_CHANNELS)
    {
      return -EINVAL;
    }

  priv = &g_ulpt_channels[channel];

  if (!priv->initialized)
    {
      return -EAGAIN;
    }

  /* Stop timer */

  putreg8(ULPTCR_TSTOP, R_ULPT_ULPTCR(channel));

  /* Wait for timer to stop */

  while (getreg8(R_ULPT_ULPTCR(channel)) & ULPTCR_TCSTF)
    {
      /* Spin */
    }

  priv->running = false;

  tmrinfo("ULPT%d stopped\n", channel);

  return OK;
}

/****************************************************************************
 * Name: ra_ulpt_reset
 *
 * Description:
 *   Reset the ULPT counter
 *
 ****************************************************************************/

int ra_ulpt_reset(int channel)
{
  struct ra_ulpt_channel_s *priv;
  bool was_running;
  int ret;

  if (channel >= RA_ULPT_CHANNELS)
    {
      return -EINVAL;
    }

  priv = &g_ulpt_channels[channel];

  if (!priv->initialized)
    {
      return -EAGAIN;
    }

  was_running = priv->running;

  /* Stop timer */

  if (was_running)
    {
      ret = ra_ulpt_stop(channel);
      if (ret < 0)
        {
          return ret;
        }
    }

  /* Reload period value */

  putreg32(priv->config.period, R_ULPT_ULPTCNT(channel));

  /* Restart if was running */

  if (was_running)
    {
      ret = ra_ulpt_start(channel);
      if (ret < 0)
        {
          return ret;
        }
    }

  return OK;
}

/****************************************************************************
 * Name: ra_ulpt_set_period
 *
 * Description:
 *   Set the timer period
 *
 ****************************************************************************/

int ra_ulpt_set_period(int channel, uint32_t period)
{
  struct ra_ulpt_channel_s *priv;

  if (channel >= RA_ULPT_CHANNELS)
    {
      return -EINVAL;
    }

  priv = &g_ulpt_channels[channel];

  if (!priv->initialized)
    {
      return -EAGAIN;
    }

  priv->config.period = period;
  putreg32(period, R_ULPT_ULPTCNT(channel));

  return OK;
}

/****************************************************************************
 * Name: ra_ulpt_get_count
 *
 * Description:
 *   Get the current counter value
 *
 ****************************************************************************/

uint32_t ra_ulpt_get_count(int channel)
{
  if (channel >= RA_ULPT_CHANNELS)
    {
      return 0;
    }

  return getreg32(R_ULPT_ULPTCNT(channel));
}

/****************************************************************************
 * Name: ra_ulpt_set_callback
 *
 * Description:
 *   Set the timer callback function
 *
 ****************************************************************************/

int ra_ulpt_set_callback(int channel, ra_ulpt_callback_t callback, void *arg)
{
  struct ra_ulpt_channel_s *priv;
  irqstate_t flags;

  if (channel >= RA_ULPT_CHANNELS)
    {
      return -EINVAL;
    }

  priv = &g_ulpt_channels[channel];

  if (!priv->initialized)
    {
      return -EAGAIN;
    }

  flags = enter_critical_section();

  priv->config.callback = callback;
  priv->config.callback_arg = arg;

  leave_critical_section(flags);

  return OK;
}

/****************************************************************************
 * Name: ra_ulpt_deinitialize
 *
 * Description:
 *   De-initialize the ULPT channel
 *
 ****************************************************************************/

int ra_ulpt_deinitialize(int channel)
{
  struct ra_ulpt_channel_s *priv;

  if (channel >= RA_ULPT_CHANNELS)
    {
      return -EINVAL;
    }

  priv = &g_ulpt_channels[channel];

  if (!priv->initialized)
    {
      return OK;
    }

  /* Stop timer */

  ra_ulpt_stop(channel);

  /* Detach interrupt */

  if (priv->irq >= 0)
    {
      ra_icu_detach(priv->irq);
    }

  /* Disable module clocking */

  ra_ulpt_disable_module(channel);

  priv->initialized = false;

  return OK;
}

/****************************************************************************
 * Name: ra_ulpt_setup_lpm_wakeup
 *
 * Description:
 *   Configure ULPT as a wake-up source for low power modes
 *
 ****************************************************************************/

int ra_ulpt_setup_lpm_wakeup(int channel, uint32_t timeout_ms)
{
  struct ra_ulpt_config_s config;
  uint32_t counts;
  uint32_t divider;
  enum ra_ulpt_divider_e div_sel;

  if (channel >= RA_ULPT_CHANNELS)
    {
      return -EINVAL;
    }

  /* Calculate timer counts for the requested timeout
   * LOCO frequency is typically 32.768 kHz
   */

  counts = (uint64_t)timeout_ms * RA_LOCO_FREQ_HZ / 1000;

  /* Select appropriate divider to fit in 32-bit counter */

  if (counts <= 0xFFFFFFFF)
    {
      div_sel = RA_ULPT_DIV_1;
      divider = 1;
    }
  else if ((counts / 2) <= 0xFFFFFFFF)
    {
      div_sel = RA_ULPT_DIV_2;
      divider = 2;
    }
  else if ((counts / 4) <= 0xFFFFFFFF)
    {
      div_sel = RA_ULPT_DIV_4;
      divider = 4;
    }
  else if ((counts / 8) <= 0xFFFFFFFF)
    {
      div_sel = RA_ULPT_DIV_8;
      divider = 8;
    }
  else if ((counts / 16) <= 0xFFFFFFFF)
    {
      div_sel = RA_ULPT_DIV_16;
      divider = 16;
    }
  else if ((counts / 32) <= 0xFFFFFFFF)
    {
      div_sel = RA_ULPT_DIV_32;
      divider = 32;
    }
  else if ((counts / 64) <= 0xFFFFFFFF)
    {
      div_sel = RA_ULPT_DIV_64;
      divider = 64;
    }
  else
    {
      div_sel = RA_ULPT_DIV_128;
      divider = 128;
    }

  counts = counts / divider;

  /* Configure ULPT for LPM wakeup */

  memset(&config, 0, sizeof(config));
  config.channel = channel;
  config.clock = RA_ULPT_CLOCK_LOCO;
  config.divider = div_sel;
  config.period = counts;
  config.low_power_mode = true;
  config.compare_a_enable = false;
  config.compare_b_enable = false;
  config.callback = NULL;

  return ra_ulpt_initialize(&config);
}

#endif /* CONFIG_RA_ULPT */
