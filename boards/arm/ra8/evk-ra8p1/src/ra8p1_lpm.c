/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_lpm.c
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
#include <stdbool.h>
#include <string.h>
#include <debug.h>
#include <errno.h>
#include <syslog.h>

#include <nuttx/power/pm.h>

#include "ra_lpm.h"
#include "ra_ulpt.h"
#include "evk-ra8p1.h"

#ifdef CONFIG_RA_LPM

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Default wake-up timeout for standby modes (10 seconds) */

#ifndef BOARD_LPM_WAKEUP_TIMEOUT_MS
#  define BOARD_LPM_WAKEUP_TIMEOUT_MS  10000
#endif

/* ULPT channel for LPM wake-up */

#define LPM_ULPT_CHANNEL  0

/****************************************************************************
 * Private Data
 ****************************************************************************/

static bool g_lpm_initialized = false;

#ifdef CONFIG_PM
static uint32_t g_standby_timeout_ms = BOARD_LPM_WAKEUP_TIMEOUT_MS;
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

#ifdef CONFIG_PM

/****************************************************************************
 * Name: board_lpm_pm_notify
 *
 * Description:
 *   Notify the driver of new power state. This callback is called after
 *   all drivers have had the opportunity to prepare for the new power state.
 *
 ****************************************************************************/

static void board_lpm_pm_notify(FAR struct pm_callback_s *cb, int domain,
                                enum pm_state_e pmstate)
{
  switch (pmstate)
    {
      case PM_NORMAL:
        _info("LPM: Returned to NORMAL state\n");
        break;

      case PM_IDLE:
        _info("LPM: Entered IDLE state\n");
        break;

      case PM_STANDBY:
        _info("LPM: Entered STANDBY state\n");
        break;

      case PM_SLEEP:
        _info("LPM: Entered SLEEP state\n");
        break;

      default:
        break;
    }
}

/****************************************************************************
 * Name: board_lpm_pm_prepare
 *
 * Description:
 *   Request the driver to prepare for a new power state. This is a warning
 *   that the system is about to enter into a new power state. The driver
 *   should begin whatever operations that may be required to enter power
 *   state. The driver may abort the state change mode by returning a
 *   non-zero value from the callback function.
 *
 ****************************************************************************/

static int board_lpm_pm_prepare(FAR struct pm_callback_s *cb, int domain,
                                 enum pm_state_e pmstate)
{
  int ret = OK;

  switch (pmstate)
    {
      case PM_NORMAL:
      case PM_IDLE:
        /* Nothing to prepare for these states */

        break;

      case PM_STANDBY:
        /* Setup ULPT timer for wake-up from standby */

        _info("LPM: Preparing for STANDBY with %lu ms timeout\n",
              (unsigned long)g_standby_timeout_ms);

        ret = ra_ulpt_setup_lpm_wakeup(LPM_ULPT_CHANNEL,
                                        g_standby_timeout_ms);
        if (ret < 0)
          {
            _err("LPM: Failed to setup ULPT wake-up: %d\n", ret);
          }

        break;

      case PM_SLEEP:
        _info("LPM: Preparing for SLEEP\n");
        break;

      default:
        break;
    }

  return ret;
}

static struct pm_callback_s g_lpm_pmcb =
{
  .notify  = board_lpm_pm_notify,
  .prepare = board_lpm_pm_prepare,
};

#endif /* CONFIG_PM */

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_lpm_initialize
 *
 * Description:
 *   Initialize the Low Power Mode (LPM) support for the board. This
 *   function configures the LPM peripheral and registers with the NuttX
 *   Power Management framework if enabled.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int board_lpm_initialize(void)
{
  int ret;

  if (g_lpm_initialized)
    {
      return OK;
    }

  _info("LPM: Initializing LPM driver\n");

  /* Initialize the LPM driver */

  ret = ra_lpm_initialize();
  if (ret < 0)
    {
      _err("LPM: Failed to initialize LPM driver: %d\n", ret);
      return ret;
    }

  /* Configure default LPM settings */

  struct ra_lpm_config_s lpm_config;
  memset(&lpm_config, 0, sizeof(lpm_config));

  /* Default mode is sleep */

  lpm_config.mode = RA_LPM_MODE_SLEEP;

  /* Enable common wake-up sources */

  lpm_config.wakeup_sources = RA_LPM_WAKEUP_IRQ0 |
                              RA_LPM_WAKEUP_IRQ1 |
                              RA_LPM_WAKEUP_NMI  |
                              RA_LPM_WAKEUP_ULPT0 |
                              RA_LPM_WAKEUP_RTC_INT |
                              RA_LPM_WAKEUP_RTC_ALM;

  /* Configure for Deep Standby Mode 1 (default) */

#ifdef CONFIG_RA_LPM_DEEP_STANDBY_MODE1
  lpm_config.power_supply = RA_LPM_POWER_SUPPLY_MODE1;
#elif defined(CONFIG_RA_LPM_DEEP_STANDBY_MODE2)
  lpm_config.power_supply = RA_LPM_POWER_SUPPLY_MODE2;
#elif defined(CONFIG_RA_LPM_DEEP_STANDBY_MODE3)
  lpm_config.power_supply = RA_LPM_POWER_SUPPLY_MODE3;
#else
  lpm_config.power_supply = RA_LPM_POWER_SUPPLY_MODE1;
#endif

  /* Retain I/O port state in deep standby if configured */

#ifdef CONFIG_RA_LPM_DEEP_STANDBY_IO_RETAIN
  lpm_config.io_port_state = RA_LPM_IO_PORT_RETAIN;
#else
  lpm_config.io_port_state = RA_LPM_IO_PORT_RESET;
#endif

  /* Set DCDC soft start mode */

  lpm_config.dcss_mode = RA_LPM_DCSS_MODE_256US;

  /* Enable output ports in standby if needed */

  lpm_config.output_port_enable = false;

  ret = ra_lpm_configure(&lpm_config);
  if (ret < 0)
    {
      _err("LPM: Failed to configure LPM: %d\n", ret);
      return ret;
    }

  /* Initialize ULPT0 for timed wake-up */

#ifdef CONFIG_RA_ULPT0
  _info("LPM: Initializing ULPT0 for wake-up timer\n");

  ret = ra_ulpt_initialize(LPM_ULPT_CHANNEL);
  if (ret < 0)
    {
      _err("LPM: Failed to initialize ULPT0: %d\n", ret);
      return ret;
    }
#endif

#ifdef CONFIG_PM
  /* Register with PM framework */

  ret = pm_register(&g_lpm_pmcb);
  if (ret < 0)
    {
      _err("LPM: Failed to register with PM framework: %d\n", ret);
      return ret;
    }

  _info("LPM: Registered with PM framework\n");
#endif

  g_lpm_initialized = true;
  _info("LPM: Initialization complete\n");

  return OK;
}

/****************************************************************************
 * Name: board_lpm_set_standby_timeout
 *
 * Description:
 *   Set the timeout for automatic wake-up from standby mode.
 *
 * Input Parameters:
 *   timeout_ms - Wake-up timeout in milliseconds
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

void board_lpm_set_standby_timeout(uint32_t timeout_ms)
{
#ifdef CONFIG_PM
  g_standby_timeout_ms = timeout_ms;
  _info("LPM: Standby timeout set to %lu ms\n", (unsigned long)timeout_ms);
#endif
}

/****************************************************************************
 * Name: board_lpm_enter_sleep
 *
 * Description:
 *   Enter sleep mode. CPU clock stops, but peripheral clocks continue.
 *   Wakes up on any interrupt.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int board_lpm_enter_sleep(void)
{
  _info("LPM: Entering sleep mode\n");
  return ra_lpm_enter(RA_LPM_MODE_SLEEP);
}

/****************************************************************************
 * Name: board_lpm_enter_deep_sleep
 *
 * Description:
 *   Enter deep sleep mode. CPU and most peripheral clocks stop.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int board_lpm_enter_deep_sleep(void)
{
  _info("LPM: Entering deep sleep mode\n");
  return ra_lpm_enter(RA_LPM_MODE_DEEP_SLEEP);
}

/****************************************************************************
 * Name: board_lpm_enter_standby
 *
 * Description:
 *   Enter software standby mode with optional timeout.
 *
 * Input Parameters:
 *   timeout_ms - Wake-up timeout in milliseconds (0 = no timeout)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int board_lpm_enter_standby(uint32_t timeout_ms)
{
  int ret;

  _info("LPM: Entering standby mode (timeout=%lu ms)\n",
        (unsigned long)timeout_ms);

  /* Setup ULPT timer if timeout is specified */

  if (timeout_ms > 0)
    {
      ret = ra_ulpt_setup_lpm_wakeup(LPM_ULPT_CHANNEL, timeout_ms);
      if (ret < 0)
        {
          _err("LPM: Failed to setup wake-up timer: %d\n", ret);
          return ret;
        }
    }

  /* Enter standby mode */

  ret = ra_lpm_enter(RA_LPM_MODE_SW_STANDBY);

  /* Stop ULPT after wake-up if it was started */

  if (timeout_ms > 0)
    {
      ra_ulpt_stop(LPM_ULPT_CHANNEL);
    }

  return ret;
}

/****************************************************************************
 * Name: board_lpm_enter_deep_standby
 *
 * Description:
 *   Enter deep software standby mode with optional timeout.
 *   This is the lowest power mode. System will reset on wake-up.
 *
 * Input Parameters:
 *   timeout_ms - Wake-up timeout in milliseconds (0 = no timeout)
 *
 * Returned Value:
 *   This function does not return on successful entry to deep standby.
 *   On error, returns a negated errno value.
 *
 ****************************************************************************/

int board_lpm_enter_deep_standby(uint32_t timeout_ms)
{
  int ret;

  _info("LPM: Entering deep standby mode (timeout=%lu ms)\n",
        (unsigned long)timeout_ms);

  /* Setup ULPT timer if timeout is specified */

  if (timeout_ms > 0)
    {
      ret = ra_ulpt_setup_lpm_wakeup(LPM_ULPT_CHANNEL, timeout_ms);
      if (ret < 0)
        {
          _err("LPM: Failed to setup wake-up timer: %d\n", ret);
          return ret;
        }
    }

  /* Select deep standby mode based on configuration */

#ifdef CONFIG_RA_LPM_DEEP_STANDBY_MODE1
  ret = ra_lpm_enter(RA_LPM_MODE_DEEP_SW_STANDBY_1);
#elif defined(CONFIG_RA_LPM_DEEP_STANDBY_MODE2)
  ret = ra_lpm_enter(RA_LPM_MODE_DEEP_SW_STANDBY_2);
#elif defined(CONFIG_RA_LPM_DEEP_STANDBY_MODE3)
  ret = ra_lpm_enter(RA_LPM_MODE_DEEP_SW_STANDBY_3);
#else
  ret = ra_lpm_enter(RA_LPM_MODE_DEEP_SW_STANDBY_1);
#endif

  /* Should not reach here if deep standby succeeded */

  return ret;
}

/****************************************************************************
 * Name: board_lpm_check_deep_standby_reset
 *
 * Description:
 *   Check if the system was reset due to wake-up from deep standby mode.
 *
 * Returned Value:
 *   true if woke from deep standby, false otherwise.
 *
 ****************************************************************************/

bool board_lpm_check_deep_standby_reset(void)
{
  struct ra_lpm_status_s status;

  if (ra_lpm_get_status(&status) == OK)
    {
      return status.deep_standby_reset;
    }

  return false;
}

/****************************************************************************
 * Name: board_lpm_get_deep_standby_wakeup_source
 *
 * Description:
 *   Get the wake-up source that caused exit from deep standby mode.
 *
 * Input Parameters:
 *   source - Pointer to store wake-up source flags
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int board_lpm_get_deep_standby_wakeup_source(FAR uint64_t *source)
{
  struct ra_lpm_status_s status;
  int ret;

  if (source == NULL)
    {
      return -EINVAL;
    }

  ret = ra_lpm_get_status(&status);
  if (ret == OK)
    {
      *source = status.wakeup_flags;
    }

  return ret;
}

/****************************************************************************
 * Name: board_lpm_get_status
 *
 * Description:
 *   Get current LPM status information.
 *
 * Input Parameters:
 *   status - Pointer to status structure
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int board_lpm_get_status(FAR struct ra_lpm_status_s *status)
{
  return ra_lpm_get_status(status);
}

#endif /* CONFIG_RA_LPM */
