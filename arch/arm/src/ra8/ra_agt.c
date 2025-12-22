/****************************************************************************
 * arch/arm/src/ra8/ra_agt.c
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
#include <errno.h>
#include <debug.h>
#include <assert.h>

#include <nuttx/arch.h>
#include <nuttx/irq.h>

#include "arm_internal.h"
#include "chip.h"
#include "hardware/ra_memorymap.h"
#include "ra_agt.h"
#include "ra_mstp.h"
#include "ra_icu.h"
#include "ra_clock.h"

#ifdef CONFIG_RA8_AGT

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Maximum number of AGT channels */

#define RA_AGT_NCHANNELS  7

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Private instance storage for all AGT channels (AGT0-6) */

static struct ra_agt_priv_s g_agt_priv[RA_AGT_NCHANNELS];

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_agt_getreg8/16/32
 *
 * Description:
 *   Read AGT register
 *
 ****************************************************************************/

static inline uint8_t ra_agt_getreg8(struct ra_agt_priv_s *priv,
                                      uint32_t offset)
{
  return getreg8(priv->config->base + offset);
}

static inline uint16_t ra_agt_getreg16(struct ra_agt_priv_s *priv,
                                        uint32_t offset)
{
  return getreg16(priv->config->base + offset);
}

static inline uint32_t ra_agt_getreg32(struct ra_agt_priv_s *priv,
                                        uint32_t offset)
{
  return getreg32(priv->config->base + offset);
}

/****************************************************************************
 * Name: ra_agt_putreg8/16/32
 *
 * Description:
 *   Write AGT register
 *
 ****************************************************************************/

static inline void ra_agt_putreg8(struct ra_agt_priv_s *priv,
                                   uint32_t offset, uint8_t value)
{
  putreg8(value, priv->config->base + offset);
}

static inline void ra_agt_putreg16(struct ra_agt_priv_s *priv,
                                    uint32_t offset, uint16_t value)
{
  putreg16(value, priv->config->base + offset);
}

static inline void ra_agt_putreg32(struct ra_agt_priv_s *priv,
                                    uint32_t offset, uint32_t value)
{
  putreg32(value, priv->config->base + offset);
}

/****************************************************************************
 * Name: ra_agt_interrupt
 *
 * Description:
 *   AGT interrupt handler
 *
 ****************************************************************************/

static int ra_agt_interrupt(int irq, void *context, void *arg)
{
  struct ra_agt_priv_s *priv = (struct ra_agt_priv_s *)arg;
  uint8_t agtcr;

  DEBUGASSERT(priv != NULL);

  /* Read control register to check flags */

  agtcr = ra_agt_getreg8(priv, RA_AGTCR_OFFSET);

  /* Check underflow flag */

  if (agtcr & AGTCR_TUNDF)
    {
      /* One-shot mode: Stop timer */

      if (priv->mode == RA_AGT_MODE_ONESHOT)
        {
          ra_agt_putreg8(priv, RA_AGTCR_OFFSET, AGTCR_STOP_CMD);
        }

      /* Call registered callback */

      if (priv->handler)
        {
          priv->handler(irq, context, priv->arg);
        }
    }

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_agt_initialize
 *
 * Description:
 *   Initialize AGT instance (does not start timer)
 *
 ****************************************************************************/

struct ra_agt_priv_s *ra_agt_initialize(
    const struct ra_agt_config_s *config)
{
  struct ra_agt_priv_s *priv;
  uint16_t agtmr1;
  ra_mstp_module_t mstp_id;

  DEBUGASSERT(config != NULL);

  if (config->channel >= RA_AGT_NCHANNELS)
    {
      tmrerr("ERROR: Invalid AGT channel %d\n", config->channel);
      return NULL;
    }

  priv = &g_agt_priv[config->channel];

  /* Check if already initialized */

  if (priv->config != NULL)
    {
      tmrwarn("WARNING: AGT%d already initialized\n", config->channel);
      return NULL;
    }

  tmrinfo("Initializing AGT%d\n", config->channel);

  priv->config = config;

  /* Power on AGT module via MSTP */

  mstp_id = RA_MSTP_AGT0 + config->channel;
  ra_mstp_start(mstp_id);

  /* Stop timer and clear flags */

  ra_agt_putreg8(priv, RA_AGTCR_OFFSET, 0x00);

  /* Wait for count status flag to clear (synchronization) */

  while (ra_agt_getreg8(priv, RA_AGTCR_OFFSET) & AGTCR_TCSTF)
    {
      /* Synchronization delay */
    }

  /* Clear mode register 2 first (per FSP requirement) */

  ra_agt_putreg8(priv, RA_AGTMR2_OFFSET, 0x00);

  /* Configure clock source and divider in AGTMR1 */

  agtmr1 = (config->clock & AGTMR1_TCK_MASK) |
           ((config->divider << AGTMR1_CKS_SHIFT) & AGTMR1_CKS_MASK) |
           AGTMR1_TMOD_TIMER;

  ra_agt_putreg16(priv, RA_AGTMR1_OFFSET, agtmr1);

  /* Initialize state */

  priv->started = false;
  priv->mode = RA_AGT_MODE_PERIODIC;
  priv->period = 0;
  priv->handler = NULL;
  priv->arg = NULL;
  priv->irq = -1;

  tmrinfo("AGT%d initialized: base=0x%08lx clock=0x%02x div=%d\n",
          config->channel, config->base, config->clock, config->divider);

  return priv;
}

/****************************************************************************
 * Name: ra_agt_start
 *
 * Description:
 *   Start timer counting
 *
 ****************************************************************************/

int ra_agt_start(struct ra_agt_priv_s *priv)
{
  DEBUGASSERT(priv != NULL && priv->config != NULL);

  if (priv->started)
    {
      return OK;  /* Already started */
    }

  /* For one-shot mode, reload period */

  if (priv->mode == RA_AGT_MODE_ONESHOT && priv->period > 0)
    {
      if (priv->config->is_agtw)
        {
          ra_agt_putreg32(priv, RA_AGT_OFFSET, priv->period - 1);
        }
      else
        {
          ra_agt_putreg16(priv, RA_AGT_OFFSET, (uint16_t)(priv->period - 1));
        }
    }

  /* Start timer */

  ra_agt_putreg8(priv, RA_AGTCR_OFFSET, AGTCR_START_CMD);

  /* Wait for timer to start */

  while (!(ra_agt_getreg8(priv, RA_AGTCR_OFFSET) & AGTCR_TCSTF))
    {
      /* Wait for count status flag */
    }

  priv->started = true;

  tmrinfo("AGT%d started\n", priv->config->channel);

  return OK;
}

/****************************************************************************
 * Name: ra_agt_stop
 *
 * Description:
 *   Stop timer
 *
 ****************************************************************************/

int ra_agt_stop(struct ra_agt_priv_s *priv)
{
  DEBUGASSERT(priv != NULL && priv->config != NULL);

  if (!priv->started)
    {
      return OK;  /* Already stopped */
    }

  /* Stop timer */

  ra_agt_putreg8(priv, RA_AGTCR_OFFSET, AGTCR_STOP_CMD);

  /* Wait for timer to stop */

  while (ra_agt_getreg8(priv, RA_AGTCR_OFFSET) & AGTCR_TCSTF)
    {
      /* Wait for count status flag to clear */
    }

  priv->started = false;

  tmrinfo("AGT%d stopped\n", priv->config->channel);

  return OK;
}

/****************************************************************************
 * Name: ra_agt_setperiod
 *
 * Description:
 *   Set period in counts
 *
 ****************************************************************************/

int ra_agt_setperiod(struct ra_agt_priv_s *priv, uint32_t counts)
{
  uint32_t max_counts;

  DEBUGASSERT(priv != NULL && priv->config != NULL);

  /* Validate period */

  max_counts = priv->config->is_agtw ? 0xFFFFFFFF : 0xFFFF;
  if (counts == 0 || counts > max_counts)
    {
      tmrerr("ERROR: Invalid period %lu (max=%lu)\n", counts, max_counts);
      return -EINVAL;
    }

  priv->period = counts;

  /* Write to counter register (period - 1) */

  if (priv->config->is_agtw)
    {
      ra_agt_putreg32(priv, RA_AGT_OFFSET, counts - 1);
    }
  else
    {
      ra_agt_putreg16(priv, RA_AGT_OFFSET, (uint16_t)(counts - 1));
    }

  tmrinfo("AGT%d period set to %lu counts\n", priv->config->channel, counts);

  return OK;
}

/****************************************************************************
 * Name: ra_agt_setmode
 *
 * Description:
 *   Set mode (periodic/oneshot)
 *
 ****************************************************************************/

int ra_agt_setmode(struct ra_agt_priv_s *priv, enum ra_agt_mode_e mode)
{
  DEBUGASSERT(priv != NULL && priv->config != NULL);

  if (priv->started)
    {
      tmrerr("ERROR: Cannot change mode while timer is running\n");
      return -EBUSY;
    }

  priv->mode = mode;

  tmrinfo("AGT%d mode set to %s\n",
          priv->config->channel,
          mode == RA_AGT_MODE_ONESHOT ? "oneshot" : "periodic");

  return OK;
}

/****************************************************************************
 * Name: ra_agt_attach
 *
 * Description:
 *   Attach ISR callback
 *
 ****************************************************************************/

int ra_agt_attach(struct ra_agt_priv_s *priv, xcpt_t handler, void *arg)
{
  int ret;

  DEBUGASSERT(priv != NULL && priv->config != NULL);

  priv->handler = handler;
  priv->arg = arg;

  /* Attach interrupt via ICU */

  ret = ra_icu_attach(priv->config->elc_int, ra_agt_interrupt, priv, false);
  if (ret < 0)
    {
      tmrerr("ERROR: Failed to attach AGT%d interrupt: %d\n",
             priv->config->channel, ret);
      return ret;
    }

  priv->irq = ret;

  /* Enable IRQ at NVIC */

  up_enable_irq(priv->irq);

  tmrinfo("AGT%d interrupt attached: IRQ=%d\n",
          priv->config->channel, priv->irq);

  return OK;
}

/****************************************************************************
 * Name: ra_agt_getcounter
 *
 * Description:
 *   Get current counter value
 *
 ****************************************************************************/

uint32_t ra_agt_getcounter(struct ra_agt_priv_s *priv)
{
  DEBUGASSERT(priv != NULL && priv->config != NULL);

  if (priv->config->is_agtw)
    {
      return ra_agt_getreg32(priv, RA_AGT_OFFSET);
    }
  else
    {
      return (uint32_t)ra_agt_getreg16(priv, RA_AGT_OFFSET);
    }
}

/****************************************************************************
 * Name: ra_agt_getfrequency
 *
 * Description:
 *   Get timer frequency in Hz
 *
 ****************************************************************************/

uint32_t ra_agt_getfrequency(struct ra_agt_priv_s *priv)
{
  uint32_t clock_freq;

  DEBUGASSERT(priv != NULL && priv->config != NULL);

  /* Get base clock frequency */

  switch (priv->config->clock)
    {
      case RA_AGT_CLOCK_PCLKB:
        clock_freq = ra_clock_pclkb_frequency();
        break;

      case RA_AGT_CLOCK_LOCO:
        clock_freq = 32000;  /* 32 kHz LOCO */
        break;

      case RA_AGT_CLOCK_SUBCLOCK:
        clock_freq = 32768;  /* 32.768 kHz subclock */
        break;

      default:
        tmrerr("ERROR: Unsupported clock source\n");
        return 0;
    }

  /* Apply divider: 2^divider */

  return clock_freq >> priv->config->divider;
}

/****************************************************************************
 * Name: ra_agt_isrunning
 *
 * Description:
 *   Check if timer is running
 *
 ****************************************************************************/

bool ra_agt_isrunning(struct ra_agt_priv_s *priv)
{
  DEBUGASSERT(priv != NULL && priv->config != NULL);

  return priv->started;
}

#endif /* CONFIG_RA8_AGT */
