/****************************************************************************
 * arch/arm/src/ra8/ra_poeg.c
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
#include <assert.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/arch.h>
#include <nuttx/irq.h>
#include <arch/board/board.h>

#include "arm_internal.h"
#include "chip.h"
#include "ra_poeg.h"
#include "ra_icu.h"
#include "ra_mstp.h"
#include "hardware/ra_memorymap.h"

#ifdef CONFIG_RA_POEG

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Helper macros to access POEG registers */

#define POEG_POEGG_OFFSET(ch)  ((ch) * 0x100)
#define POEG_POEGG(ch)         (R_POEG_BASE + POEG_POEGG_OFFSET(ch))

/* Status flag masks */

#define POEG_STATUS_FLAGS  (R_POEG_POEGGA_PIDF | R_POEG_POEGGA_IOCF | \
                            R_POEG_POEGGA_OSTPF | R_POEG_POEGGA_SSF)

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* POEG device state */

struct ra_poeg_dev_s
{
  bool               initialized;  /* Device is initialized */
  uint8_t            channel;      /* POEG channel */
  uint32_t           base;         /* Register base address */
  int                irq;          /* IRQ number */
  poeg_callback_t    callback;     /* User callback */
  void              *arg;          /* Callback argument */
};

/****************************************************************************
 * Private Data
 ****************************************************************************/

static struct ra_poeg_dev_s g_poeg_devs[POEG_MAX_CHANNELS];

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_poeg_getreg
 *
 * Description:
 *   Read a POEG register.
 *
 ****************************************************************************/

static inline uint32_t ra_poeg_getreg(uint32_t base)
{
  return getreg32(base);
}

/****************************************************************************
 * Name: ra_poeg_putreg
 *
 * Description:
 *   Write to a POEG register.
 *
 ****************************************************************************/

static inline void ra_poeg_putreg(uint32_t base, uint32_t value)
{
  putreg32(value, base);
}

/****************************************************************************
 * Name: ra_poeg_modifyreg
 *
 * Description:
 *   Modify a POEG register (read-modify-write).
 *
 ****************************************************************************/

static inline void ra_poeg_modifyreg(uint32_t base,
                                     uint32_t clearbits,
                                     uint32_t setbits)
{
  uint32_t regval = ra_poeg_getreg(base);
  regval &= ~clearbits;
  regval |= setbits;
  ra_poeg_putreg(base, regval);
}

/****************************************************************************
 * Name: ra_poeg_interrupt
 *
 * Description:
 *   POEG interrupt handler.
 *
 ****************************************************************************/

static int ra_poeg_interrupt(int irq, void *context, void *arg)
{
  struct ra_poeg_dev_s *dev = (struct ra_poeg_dev_s *)arg;
  uint32_t regval;
  uint32_t status;

  DEBUGASSERT(dev != NULL);

  /* Read status register */

  regval = ra_poeg_getreg(dev->base);
  status = regval & POEG_STATUS_FLAGS;

  /* Call user callback if registered */

  if (dev->callback != NULL && status != 0)
    {
      dev->callback(dev->channel, status, dev->arg);
    }

  /* Note: Status flags are NOT cleared here. User must explicitly call
   * ra_poeg_reset() to clear flags and re-enable GPT outputs.
   */

  return OK;
}

/****************************************************************************
 * Name: ra_poeg_mstp_channel
 *
 * Description:
 *   Get MSTP module ID for POEG channel.
 *
 ****************************************************************************/

static int ra_poeg_mstp_channel(uint8_t channel)
{
  switch (channel)
    {
      case 0:
        return RA_MSTP_POEG0;
      case 1:
        return RA_MSTP_POEG1;
      case 2:
        return RA_MSTP_POEG2;
      case 3:
        return RA_MSTP_POEG3;
      default:
        return -EINVAL;
    }
}

/****************************************************************************
 * Name: ra_poeg_get_elc_event
 *
 * Description:
 *   Get ELC event number for POEG channel.
 *
 ****************************************************************************/

static int ra_poeg_get_elc_event(uint8_t channel)
{
#if defined(CONFIG_RA8P1_GROUP)
  switch (channel)
    {
      case 0:
        return RA_ELC_POEG0_EVENT;
      case 1:
        return RA_ELC_POEG1_EVENT;
      case 2:
        return RA_ELC_POEG2_EVENT;
      case 3:
        return RA_ELC_POEG3_EVENT;
      default:
        return -EINVAL;
    }
#elif defined(CONFIG_RA8E1_GROUP)
  switch (channel)
    {
      case 0:
        return RA_ELC_POEG0_EVENT;
      case 1:
        return RA_ELC_POEG1_EVENT;
      default:
        return -EINVAL;
    }
#else
  return -ENOTSUP;
#endif
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_poeg_initialize
 *
 * Description:
 *   Initialize the POEG driver for a specific channel.
 *
 ****************************************************************************/

int ra_poeg_initialize(const struct ra_poeg_config_s *config)
{
  struct ra_poeg_dev_s *dev;
  uint32_t regval;
  int mstp_id;
  int elc_event;
  int ret;

  DEBUGASSERT(config != NULL);

  if (config->channel >= POEG_MAX_CHANNELS)
    {
      _err("ERROR: Invalid POEG channel: %d\n", config->channel);
      return -EINVAL;
    }

  dev = &g_poeg_devs[config->channel];

  if (dev->initialized)
    {
      _err("ERROR: POEG channel %d already initialized\n",
           config->channel);
      return -EBUSY;
    }

  /* Initialize device structure */

  dev->channel  = config->channel;
  dev->base     = POEG_POEGG(config->channel);
  dev->callback = config->callback;
  dev->arg      = config->arg;

  /* Enable POEG module clock via MSTP */

  mstp_id = ra_poeg_mstp_channel(config->channel);
  if (mstp_id < 0)
    {
      _err("ERROR: Invalid MSTP ID for channel %d\n", config->channel);
      return mstp_id;
    }

  ra_mstp_start(mstp_id);

  /* Build POEGG register configuration */

  regval = 0;

  /* Configure trigger sources */

  if (config->trigger & RA_POEG_TRIGGER_PIN)
    {
      regval |= R_POEG_POEGGA_PIDE;
    }

  if (config->trigger & RA_POEG_TRIGGER_GPT_OUTPUT)
    {
      regval |= R_POEG_POEGGA_IOCE;
    }

  if (config->trigger & RA_POEG_TRIGGER_OSCILLATION_STOP)
    {
      regval |= R_POEG_POEGGA_OSTPE;
    }

  /* Configure ACMPHS comparator triggers */

  if (config->trigger & RA_POEG_TRIGGER_ACMPHS0)
    {
      regval |= R_POEG_POEGGA_CDRE0;
    }

  if (config->trigger & RA_POEG_TRIGGER_ACMPHS1)
    {
      regval |= R_POEG_POEGGA_CDRE1;
    }

  if (config->trigger & RA_POEG_TRIGGER_ACMPHS2)
    {
      regval |= R_POEG_POEGGA_CDRE2;
    }

  if (config->trigger & RA_POEG_TRIGGER_ACMPHS3)
    {
      regval |= R_POEG_POEGGA_CDRE3;
    }

  /* Configure pin polarity */

  if (config->polarity == RA_POEG_POLARITY_ACTIVE_LOW)
    {
      regval |= R_POEG_POEGGA_INV;
    }

  /* Configure noise filter */

  if (config->noise_filter != RA_POEG_FILTER_DISABLED)
    {
      regval |= R_POEG_POEGGA_NFEN;
      regval |= ((config->noise_filter >> 1) << R_POEG_POEGGA_NFCS_SHIFT) &
                R_POEG_POEGGA_NFCS_MASK;
    }

  /* Write configuration to POEGG register */

  ra_poeg_putreg(dev->base, regval);

  /* Set up interrupt if callback is provided */

  if (config->callback != NULL)
    {
      elc_event = ra_poeg_get_elc_event(config->channel);
      if (elc_event < 0)
        {
          _err("ERROR: Invalid ELC event for channel %d\n",
               config->channel);
          ra_mstp_stop(mstp_id);
          return elc_event;
        }

      /* Attach interrupt handler */

      ret = ra_icu_attach(elc_event, ra_poeg_interrupt, dev, true);
      if (ret < 0)
        {
          _err("ERROR: Failed to attach POEG interrupt: %d\n", ret);
          ra_mstp_stop(mstp_id);
          return ret;
        }

      dev->irq = ret;

      /* Set interrupt priority */

      ra_icu_set_priority(dev->irq, config->priority);
    }

  dev->initialized = true;

  _info("POEG channel %d initialized\n", config->channel);

  return OK;
}

/****************************************************************************
 * Name: ra_poeg_deinitialize
 *
 * Description:
 *   Deinitialize the POEG driver for a specific channel.
 *
 ****************************************************************************/

int ra_poeg_deinitialize(uint8_t channel)
{
  struct ra_poeg_dev_s *dev;
  int mstp_id;

  if (channel >= POEG_MAX_CHANNELS)
    {
      _err("ERROR: Invalid POEG channel: %d\n", channel);
      return -EINVAL;
    }

  dev = &g_poeg_devs[channel];

  if (!dev->initialized)
    {
      return -ENODEV;
    }

  /* Detach interrupt if configured */

  if (dev->irq >= 0)
    {
      ra_icu_detach(dev->irq);
      dev->irq = -1;
    }

  /* Clear POEGG register */

  ra_poeg_putreg(dev->base, 0);

  /* Disable POEG module clock */

  mstp_id = ra_poeg_mstp_channel(channel);
  if (mstp_id >= 0)
    {
      ra_mstp_stop(mstp_id);
    }

  dev->initialized = false;
  dev->callback    = NULL;
  dev->arg         = NULL;

  _info("POEG channel %d deinitialized\n", channel);

  return OK;
}

/****************************************************************************
 * Name: ra_poeg_software_disable
 *
 * Description:
 *   Trigger software disable of GPT outputs.
 *
 ****************************************************************************/

int ra_poeg_software_disable(uint8_t channel)
{
  struct ra_poeg_dev_s *dev;

  if (channel >= POEG_MAX_CHANNELS)
    {
      return -EINVAL;
    }

  dev = &g_poeg_devs[channel];

  if (!dev->initialized)
    {
      return -ENODEV;
    }

  /* Set software stop flag */

  ra_poeg_modifyreg(dev->base, 0, R_POEG_POEGGA_SSF);

  _info("POEG channel %d: software disable triggered\n", channel);

  return OK;
}

/****************************************************************************
 * Name: ra_poeg_reset
 *
 * Description:
 *   Reset POEG status flags and re-enable GPT outputs.
 *
 ****************************************************************************/

int ra_poeg_reset(uint8_t channel)
{
  struct ra_poeg_dev_s *dev;

  if (channel >= POEG_MAX_CHANNELS)
    {
      return -EINVAL;
    }

  dev = &g_poeg_devs[channel];

  if (!dev->initialized)
    {
      return -ENODEV;
    }

  /* Clear status flags by writing 0 to them */

  ra_poeg_modifyreg(dev->base, POEG_STATUS_FLAGS, 0);

  _info("POEG channel %d: status reset\n", channel);

  return OK;
}

/****************************************************************************
 * Name: ra_poeg_get_status
 *
 * Description:
 *   Get the current POEG status.
 *
 ****************************************************************************/

int ra_poeg_get_status(uint8_t channel, struct ra_poeg_status_s *status)
{
  struct ra_poeg_dev_s *dev;
  uint32_t regval;

  if (channel >= POEG_MAX_CHANNELS || status == NULL)
    {
      return -EINVAL;
    }

  dev = &g_poeg_devs[channel];

  if (!dev->initialized)
    {
      return -ENODEV;
    }

  /* Read POEGG register */

  regval = ra_poeg_getreg(dev->base);

  /* Extract status flags */

  status->flags = regval & (POEG_STATUS_FLAGS | R_POEG_POEGGA_ST);

  /* GPT outputs are disabled if any status flag is set */

  status->disabled = ((regval & POEG_STATUS_FLAGS) != 0);

  return OK;
}

#endif /* CONFIG_RA_POEG */
