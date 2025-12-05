/****************************************************************************
 * arch/arm/src/ra8/ra_elc.c
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

#include "arm_internal.h"
#include "chip.h"
#include "hardware/ra_memorymap.h"
#include "ra_mstp.h"
#include "ra_elc.h"

#ifdef CONFIG_RA_ELC

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Debug output */

#ifdef CONFIG_DEBUG_ELC_INFO
#  define elcinfo  syslog
#else
#  define elcinfo(...)
#endif

#ifdef CONFIG_DEBUG_ELC_ERROR
#  define elcerr   syslog
#else
#  define elcerr(...)
#endif

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* ELC driver private state */

struct ra_elc_priv_s
{
  uint32_t  open;          /* Open state magic number */
  bool      enabled;       /* Global ELC enable state */
};

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* ELC driver state - single instance for the module */

static struct ra_elc_priv_s g_elc_priv =
{
  .open    = 0,
  .enabled = false,
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: elc_putreg8
 *
 * Description:
 *   Write an 8-bit value to an ELC register
 *
 ****************************************************************************/

static inline void elc_putreg8(uint32_t offset, uint8_t value)
{
  putreg8(value, R_ELC_BASE + offset);
}

/****************************************************************************
 * Name: elc_getreg8
 *
 * Description:
 *   Read an 8-bit value from an ELC register
 *
 ****************************************************************************/

static inline uint8_t elc_getreg8(uint32_t offset)
{
  return getreg8(R_ELC_BASE + offset);
}

/****************************************************************************
 * Name: elc_putreg16
 *
 * Description:
 *   Write a 16-bit value to an ELC register
 *
 ****************************************************************************/

static inline void elc_putreg16(uint32_t offset, uint16_t value)
{
  putreg16(value, R_ELC_BASE + offset);
}

/****************************************************************************
 * Name: elc_getreg16
 *
 * Description:
 *   Read a 16-bit value from an ELC register
 *
 ****************************************************************************/

static inline uint16_t elc_getreg16(uint32_t offset)
{
  return getreg16(R_ELC_BASE + offset);
}

/****************************************************************************
 * Name: elc_putreg32
 *
 * Description:
 *   Write a 32-bit value to an ELC register
 *
 ****************************************************************************/

static inline void elc_putreg32(uint32_t offset, uint32_t value)
{
  putreg32(value, R_ELC_BASE + offset);
}

/****************************************************************************
 * Name: elc_getreg32
 *
 * Description:
 *   Read a 32-bit value from an ELC register
 *
 ****************************************************************************/

static inline uint32_t elc_getreg32(uint32_t offset)
{
  return getreg32(R_ELC_BASE + offset);
}

/****************************************************************************
 * Name: elc_is_open
 *
 * Description:
 *   Check if the ELC driver is initialized and open
 *
 ****************************************************************************/

static inline bool elc_is_open(void)
{
  return (g_elc_priv.open == RA_ELC_OPEN_MAGIC);
}

/****************************************************************************
 * Name: elc_validate_peripheral
 *
 * Description:
 *   Validate peripheral number
 *
 ****************************************************************************/

static inline bool elc_validate_peripheral(ra_elc_peripheral_t peripheral)
{
  return (peripheral < ELC_MAX_PERIPHERALS);
}

/****************************************************************************
 * Name: elc_validate_software_event
 *
 * Description:
 *   Validate software event number
 *
 ****************************************************************************/

static inline bool elc_validate_software_event(ra_elc_software_event_t event)
{
  return (event < ELC_MAX_SOFTWARE_EVENTS);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_elc_initialize
 *
 * Description:
 *   Initialize the Event Link Controller (ELC) module.
 *
 ****************************************************************************/

int ra_elc_initialize(void)
{
  irqstate_t flags;
  int ret = OK;

  elcinfo(LOG_INFO, "ELC: Initializing Event Link Controller\n");

  flags = enter_critical_section();

  /* Check if already initialized */

  if (elc_is_open())
    {
      elcerr(LOG_ERR, "ELC: Already initialized\n");
      ret = -EBUSY;
      goto errout;
    }

  /* Enable ELC module clock via MSTP */

  ret = ra_mstp_start(RA_MSTP_ELC);
  if (ret < 0)
    {
      elcerr(LOG_ERR, "ELC: Failed to enable module clock: %d\n", ret);
      goto errout;
    }

  /* Clear all event links by setting ELSR registers to 0 (ELC_EVENT_NONE) */

  for (int i = 0; i < ELC_MAX_PERIPHERALS; i++)
    {
      /* Write to the lower 16 bits (HA) of each ELSR register
       * ELSR registers are 32-bit but we only use the lower 16 bits
       * for event selection
       */

      elc_putreg16(R_ELC_ELSR_OFFSET(i), ELC_EVENT_NONE);
    }

  /* Disable ELC global operation initially */

  elc_putreg8(R_ELC_ELCR_OFFSET, ELC_ELCR_ELCON_DISABLE);

  /* Mark driver as initialized */

  g_elc_priv.open = RA_ELC_OPEN_MAGIC;
  g_elc_priv.enabled = false;

  elcinfo(LOG_INFO, "ELC: Initialized successfully\n");

errout:
  leave_critical_section(flags);
  return ret;
}

/****************************************************************************
 * Name: ra_elc_uninitialize
 *
 * Description:
 *   Uninitialize the Event Link Controller (ELC) module.
 *
 ****************************************************************************/

int ra_elc_uninitialize(void)
{
  irqstate_t flags;
  int ret = OK;

  elcinfo(LOG_INFO, "ELC: Uninitializing Event Link Controller\n");

  flags = enter_critical_section();

  /* Check if initialized */

  if (!elc_is_open())
    {
      elcerr(LOG_ERR, "ELC: Not initialized\n");
      ret = -EINVAL;
      goto errout;
    }

  /* Disable ELC global operation */

  elc_putreg8(R_ELC_ELCR_OFFSET, ELC_ELCR_ELCON_DISABLE);

  /* Clear all event links */

  for (int i = 0; i < ELC_MAX_PERIPHERALS; i++)
    {
      elc_putreg16(R_ELC_ELSR_OFFSET(i), ELC_EVENT_NONE);
    }

  /* Disable ELC module clock */

  ret = ra_mstp_stop(RA_MSTP_ELC);
  if (ret < 0)
    {
      elcerr(LOG_ERR, "ELC: Failed to disable module clock: %d\n", ret);
      /* Continue with cleanup even if MSTP fails */
    }

  /* Mark driver as closed */

  g_elc_priv.open = 0;
  g_elc_priv.enabled = false;

  elcinfo(LOG_INFO, "ELC: Uninitialized successfully\n");

errout:
  leave_critical_section(flags);
  return ret;
}

/****************************************************************************
 * Name: ra_elc_enable
 *
 * Description:
 *   Enable the global operation of the Event Link Controller.
 *
 ****************************************************************************/

int ra_elc_enable(void)
{
  irqstate_t flags;
  int ret = OK;

  flags = enter_critical_section();

  /* Check if initialized */

  if (!elc_is_open())
    {
      elcerr(LOG_ERR, "ELC: Not initialized\n");
      ret = -EINVAL;
      goto errout;
    }

  /* Enable ELC global operation */

  elc_putreg8(R_ELC_ELCR_OFFSET, ELC_ELCR_ELCON_ENABLE);

  g_elc_priv.enabled = true;

  elcinfo(LOG_INFO, "ELC: Global operation enabled\n");

errout:
  leave_critical_section(flags);
  return ret;
}

/****************************************************************************
 * Name: ra_elc_disable
 *
 * Description:
 *   Disable the global operation of the Event Link Controller.
 *
 ****************************************************************************/

int ra_elc_disable(void)
{
  irqstate_t flags;
  int ret = OK;

  flags = enter_critical_section();

  /* Check if initialized */

  if (!elc_is_open())
    {
      elcerr(LOG_ERR, "ELC: Not initialized\n");
      ret = -EINVAL;
      goto errout;
    }

  /* Disable ELC global operation */

  elc_putreg8(R_ELC_ELCR_OFFSET, ELC_ELCR_ELCON_DISABLE);

  g_elc_priv.enabled = false;

  elcinfo(LOG_INFO, "ELC: Global operation disabled\n");

errout:
  leave_critical_section(flags);
  return ret;
}

/****************************************************************************
 * Name: ra_elc_link_set
 *
 * Description:
 *   Create a single event link between a source event and a target
 *   peripheral.
 *
 ****************************************************************************/

int ra_elc_link_set(ra_elc_peripheral_t peripheral, ra_elc_event_t event)
{
  irqstate_t flags;
  int ret = OK;

  flags = enter_critical_section();

  /* Check if initialized */

  if (!elc_is_open())
    {
      elcerr(LOG_ERR, "ELC: Not initialized\n");
      ret = -EINVAL;
      goto errout;
    }

  /* Validate peripheral */

  if (!elc_validate_peripheral(peripheral))
    {
      elcerr(LOG_ERR, "ELC: Invalid peripheral: %d\n", peripheral);
      ret = -EINVAL;
      goto errout;
    }

  /* Set the event link in the ELSR register
   * The ELSR register uses the lower 16 bits (HA field) for event selection
   */

  elc_putreg16(R_ELC_ELSR_OFFSET(peripheral), (uint16_t)event);

  elcinfo(LOG_INFO, "ELC: Link set - peripheral %d -> event 0x%03x\n",
          peripheral, event);

errout:
  leave_critical_section(flags);
  return ret;
}

/****************************************************************************
 * Name: ra_elc_link_break
 *
 * Description:
 *   Break (disable) an existing event link for the specified peripheral.
 *
 ****************************************************************************/

int ra_elc_link_break(ra_elc_peripheral_t peripheral)
{
  irqstate_t flags;
  int ret = OK;

  flags = enter_critical_section();

  /* Check if initialized */

  if (!elc_is_open())
    {
      elcerr(LOG_ERR, "ELC: Not initialized\n");
      ret = -EINVAL;
      goto errout;
    }

  /* Validate peripheral */

  if (!elc_validate_peripheral(peripheral))
    {
      elcerr(LOG_ERR, "ELC: Invalid peripheral: %d\n", peripheral);
      ret = -EINVAL;
      goto errout;
    }

  /* Clear the event link by setting to ELC_EVENT_NONE */

  elc_putreg16(R_ELC_ELSR_OFFSET(peripheral), ELC_EVENT_NONE);

  elcinfo(LOG_INFO, "ELC: Link broken for peripheral %d\n", peripheral);

errout:
  leave_critical_section(flags);
  return ret;
}

/****************************************************************************
 * Name: ra_elc_software_event_generate
 *
 * Description:
 *   Generate a software event.
 *
 ****************************************************************************/

int ra_elc_software_event_generate(ra_elc_software_event_t event_num)
{
  irqstate_t flags;
  int ret = OK;
  volatile uint8_t *p_elsegr;

  flags = enter_critical_section();

  /* Check if initialized */

  if (!elc_is_open())
    {
      elcerr(LOG_ERR, "ELC: Not initialized\n");
      ret = -EINVAL;
      goto errout;
    }

  /* Validate software event number */

  if (!elc_validate_software_event(event_num))
    {
      elcerr(LOG_ERR, "ELC: Invalid software event: %d\n", event_num);
      ret = -EINVAL;
      goto errout;
    }

  /* Get pointer to the ELSEGR register for this software event
   * ELSEGR registers are 8-bit, accessed via the BY (byte) field
   */

  p_elsegr = (volatile uint8_t *)(R_ELC_BASE + R_ELC_ELSEGR_OFFSET(event_num));

  /* Generate software event following the required unlock sequence:
   * Step 1: WI = 0, WE = 0, SEG = 0 (clear register)
   * Step 2: WI = 0, WE = 1, SEG = 0 (enable write to SEG)
   * Step 3: WI = 0, WE = 1, SEG = 1 (generate event)
   */

  *p_elsegr = ELC_ELSEGRN_STEP1;
  *p_elsegr = ELC_ELSEGRN_STEP2;
  *p_elsegr = ELC_ELSEGRN_STEP3;

  elcinfo(LOG_INFO, "ELC: Software event %d generated\n", event_num);

errout:
  leave_critical_section(flags);
  return ret;
}

/****************************************************************************
 * Name: ra_elc_configure
 *
 * Description:
 *   Configure multiple ELC links at once.
 *
 ****************************************************************************/

int ra_elc_configure(const struct ra_elc_config_s *config)
{
  int ret = OK;
  int i;

  /* Validate input */

  if (config == NULL)
    {
      return -EINVAL;
    }

  if (config->nlinks == 0 || config->links == NULL)
    {
      return -EINVAL;
    }

  elcinfo(LOG_INFO, "ELC: Configuring %d links\n", config->nlinks);

  /* Configure each link */

  for (i = 0; i < config->nlinks; i++)
    {
      ret = ra_elc_link_set(config->links[i].peripheral,
                            config->links[i].event);
      if (ret < 0)
        {
          elcerr(LOG_ERR, "ELC: Failed to set link %d: %d\n", i, ret);
          return ret;
        }
    }

  return OK;
}

/****************************************************************************
 * Name: ra_elc_link_get
 *
 * Description:
 *   Get the current event linked to a peripheral.
 *
 ****************************************************************************/

int ra_elc_link_get(ra_elc_peripheral_t peripheral, ra_elc_event_t *event)
{
  irqstate_t flags;
  int ret = OK;

  /* Validate input */

  if (event == NULL)
    {
      return -EINVAL;
    }

  flags = enter_critical_section();

  /* Check if initialized */

  if (!elc_is_open())
    {
      elcerr(LOG_ERR, "ELC: Not initialized\n");
      ret = -EINVAL;
      goto errout;
    }

  /* Validate peripheral */

  if (!elc_validate_peripheral(peripheral))
    {
      elcerr(LOG_ERR, "ELC: Invalid peripheral: %d\n", peripheral);
      ret = -EINVAL;
      goto errout;
    }

  /* Read the event link from the ELSR register */

  *event = elc_getreg16(R_ELC_ELSR_OFFSET(peripheral));

errout:
  leave_critical_section(flags);
  return ret;
}

#endif /* CONFIG_RA_ELC */
