/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_poeg.c
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
#include <syslog.h>
#include <errno.h>
#include <debug.h>

#include <arch/board/board.h>
#include "evk-ra8p1.h"
#include "ra_poeg.h"
#include "ra_gpio.h"

#ifdef CONFIG_RA_POEG

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GTETRGB Pin Configuration - P614 */

#define GPIO_GTETRGB                GPIO_P614_INPUT

/****************************************************************************
 * Private Data
 ****************************************************************************/

static bool g_poeg_initialized = false;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_poeg_callback
 *
 * Description:
 *   POEG event callback - called when GPT outputs are disabled
 *
 ****************************************************************************/

static void board_poeg_callback(uint8_t channel, uint32_t status, void *arg)
{
  /* Log the event */

  syslog(LOG_WARNING, "POEG: GPT outputs disabled on channel %d\n",
         channel);

  if (status & RA_POEG_STATUS_PIN_DETECT)
    {
      syslog(LOG_WARNING, "  - Triggered by GTETRG pin\n");
    }

  if (status & RA_POEG_STATUS_GPT_DETECT)
    {
      syslog(LOG_WARNING, "  - Triggered by GPT output level\n");
    }

  if (status & RA_POEG_STATUS_OSC_STOP)
    {
      syslog(LOG_WARNING, "  - Triggered by oscillator stop\n");
    }

  if (status & RA_POEG_STATUS_SOFTWARE)
    {
      syslog(LOG_WARNING, "  - Triggered by software\n");
    }

  /* In a real safety-critical application:
   * - Log the event to non-volatile memory
   * - Enter safe state
   * - Notify other systems
   * - May require manual reset or external intervention
   */
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_poeg_initialize
 *
 * Description:
 *   Initialize POEG for emergency PWM shutdown on EVK-RA8P1.
 *   This provides hardware failsafe for motor control and other critical
 *   PWM applications.
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure.
 *
 ****************************************************************************/

int board_poeg_initialize(void)
{
  struct ra_poeg_config_s config;
  int ret;

  if (g_poeg_initialized)
    {
      return OK;
    }

  syslog(LOG_INFO, "Initializing POEG for PWM failsafe...\n");

  /* Configure GTETRGB input pin (P614) */

  ret = ra_gpioconfig(GPIO_GTETRGB);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to configure GTETRGB pin: %d\n", ret);
      return ret;
    }

  /* Configure POEG */

  config.channel      = BOARD_POEG_CHANNEL;
  config.trigger      = BOARD_POEG_TRIGGER;
  config.polarity     = BOARD_POEG_POLARITY;
  config.noise_filter = BOARD_POEG_NOISE_FILTER;
  config.elc_event    = RA_ELC_POEG1_EVENT;  /* Channel B = POEG1 */
  config.priority     = BOARD_POEG_PRIORITY;
  config.callback     = board_poeg_callback;
  config.arg          = NULL;

  ret = ra_poeg_initialize(&config);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize POEG: %d\n", ret);
      return ret;
    }

  g_poeg_initialized = true;

  syslog(LOG_INFO, "POEG initialized successfully\n");
  syslog(LOG_INFO, "  - Channel: %d (POEG Group B)\n",
         BOARD_POEG_CHANNEL);
  syslog(LOG_INFO, "  - GTETRG pin: P614 (J14:20)\n");
  syslog(LOG_INFO, "  - Polarity: Active LOW\n");
  syslog(LOG_INFO, "  - Noise filter: PCLKB/32\n");
  syslog(LOG_INFO, "Connect P614 to GND to trigger emergency shutdown\n");

  return OK;
}

/****************************************************************************
 * Name: board_poeg_reset
 *
 * Description:
 *   Reset POEG status and re-enable GPT outputs.
 *   Should only be called after the fault condition is resolved.
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure.
 *
 ****************************************************************************/

int board_poeg_reset(void)
{
  int ret;

  if (!g_poeg_initialized)
    {
      return -ENODEV;
    }

  ret = ra_poeg_reset(BOARD_POEG_CHANNEL);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to reset POEG: %d\n", ret);
      return ret;
    }

  syslog(LOG_INFO, "POEG reset - GPT outputs re-enabled\n");

  return OK;
}

/****************************************************************************
 * Name: board_poeg_get_status
 *
 * Description:
 *   Get current POEG status.
 *
 * Input Parameters:
 *   status - Pointer to status structure to fill
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure.
 *
 ****************************************************************************/

int board_poeg_get_status(struct ra_poeg_status_s *status)
{
  if (!g_poeg_initialized || status == NULL)
    {
      return -EINVAL;
    }

  return ra_poeg_get_status(BOARD_POEG_CHANNEL, status);
}

/****************************************************************************
 * Name: board_poeg_software_disable
 *
 * Description:
 *   Trigger software disable of GPT outputs.
 *   Useful for testing or emergency shutdown from software.
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure.
 *
 ****************************************************************************/

int board_poeg_software_disable(void)
{
  int ret;

  if (!g_poeg_initialized)
    {
      return -ENODEV;
    }

  ret = ra_poeg_software_disable(BOARD_POEG_CHANNEL);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to trigger software disable: %d\n",
             ret);
      return ret;
    }

  syslog(LOG_WARNING, "POEG software disable triggered\n");

  return OK;
}

#endif /* CONFIG_RA_POEG */
