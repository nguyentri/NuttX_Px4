/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_elc.c
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
#include <syslog.h>

#include <nuttx/board.h>
#include <arch/board/board.h>

#include "ra_elc.h"
#include "evk-ra8p1.h"

/* Include IRQ definitions for ELC event macros */

#include <arch/ra8/ra8p1_irq.h>

#ifdef CONFIG_RA_ELC

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Types
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

#ifdef CONFIG_RA8P1_ELC_GPT_ADC_EXAMPLE
/* Example: GPT0 overflow triggers ADC scan group 0
 * This configuration links:
 *   - GPT0 counter overflow -> ADC0 scan trigger A
 *   - Software event 0 -> GPT A (to start GPT0)
 */

static const struct ra_elc_link_s g_elc_gpt_adc_links[] =
{
  /* Link GPT0 counter overflow event to ADC0 scan trigger A */

  {
    .peripheral = RA_ELC_PERIPHERAL_ADC0,
    .event      = RA_ELC_GPT0_COUNTER_OVERFLOW,
  },

  /* Link software event 0 to GPT A (for starting GPT via software) */

  {
    .peripheral = RA_ELC_PERIPHERAL_GPT_A,
    .event      = RA_ELC_ELC_SOFTWARE_EVENT_0,
  },

  /* Link GPT0 overflow to GPT B (for stopping another timer) */

  {
    .peripheral = RA_ELC_PERIPHERAL_GPT_B,
    .event      = RA_ELC_GPT0_COUNTER_OVERFLOW,
  },
};

static const struct ra_elc_config_s g_elc_gpt_adc_config =
{
  .nlinks = sizeof(g_elc_gpt_adc_links) / sizeof(g_elc_gpt_adc_links[0]),
  .links  = g_elc_gpt_adc_links,
};
#endif /* CONFIG_RA8P1_ELC_GPT_ADC_EXAMPLE */

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_elc_initialize
 *
 * Description:
 *   Initialize the Event Link Controller on the EVK-RA8P1 board.
 *   This function sets up event links between peripherals as configured.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   OK on success; a negated errno on failure.
 *
 ****************************************************************************/

int board_elc_initialize(void)
{
  int ret;

  syslog(LOG_INFO, "ELC: Initializing board ELC configuration\n");

  /* Initialize the ELC module */

  ret = ra_elc_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ELC: Failed to initialize: %d\n", ret);
      return ret;
    }

#ifdef CONFIG_RA8P1_ELC_GPT_ADC_EXAMPLE
  /* Configure ELC links for GPT-triggered ADC */

  ret = ra_elc_configure(&g_elc_gpt_adc_config);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ELC: Failed to configure GPT-ADC links: %d\n", ret);
      return ret;
    }

  syslog(LOG_INFO, "ELC: GPT-ADC event links configured\n");
#endif

  /* Enable ELC global operation */

  ret = ra_elc_enable();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ELC: Failed to enable: %d\n", ret);
      return ret;
    }

  syslog(LOG_INFO, "ELC: Initialized successfully\n");

  return OK;
}

/****************************************************************************
 * Name: board_elc_gpt_trigger_adc
 *
 * Description:
 *   Configure ELC to trigger ADC conversions from GPT timer events.
 *   This is a convenience function for setting up a common use case.
 *
 * Input Parameters:
 *   gpt_channel - GPT channel number (0-13)
 *   adc_trigger - ADC trigger peripheral (RA_ELC_PERIPHERAL_ADC0/1/2)
 *   event_type  - 0 = overflow, 1 = compare match A, 2 = compare match B
 *
 * Returned Value:
 *   OK on success; a negated errno on failure.
 *
 ****************************************************************************/

int board_elc_gpt_trigger_adc(int gpt_channel, int adc_trigger,
                               int event_type)
{
  ra_elc_event_t event;
  int ret;

  /* Calculate event number based on GPT channel and event type
   * GPT events are organized as:
   *   GPT0: 0x181 (Capture/Compare A), 0x182 (B), ... 0x187 (Overflow)
   *   GPT1: 0x18A, 0x18B, ... 0x190
   *   etc.
   */

  switch (event_type)
    {
      case 0:  /* Overflow */
        switch (gpt_channel)
          {
            case 0:
              event = RA_ELC_GPT0_COUNTER_OVERFLOW;
              break;
            case 1:
              event = RA_ELC_GPT1_COUNTER_OVERFLOW;
              break;
            case 2:
              event = RA_ELC_GPT2_COUNTER_OVERFLOW;
              break;
            case 3:
              event = RA_ELC_GPT3_COUNTER_OVERFLOW;
              break;
            case 4:
              event = RA_ELC_GPT4_COUNTER_OVERFLOW;
              break;
            case 5:
              event = RA_ELC_GPT5_COUNTER_OVERFLOW;
              break;
            case 6:
              event = RA_ELC_GPT6_COUNTER_OVERFLOW;
              break;
            case 7:
              event = RA_ELC_GPT7_COUNTER_OVERFLOW;
              break;
            default:
              return -EINVAL;
          }
        break;

      case 1:  /* Compare Match A */
        switch (gpt_channel)
          {
            case 0:
              event = RA_ELC_GPT0_CAPTURE_COMPARE_A;
              break;
            case 1:
              event = RA_ELC_GPT1_CAPTURE_COMPARE_A;
              break;
            case 2:
              event = RA_ELC_GPT2_CAPTURE_COMPARE_A;
              break;
            case 3:
              event = RA_ELC_GPT3_CAPTURE_COMPARE_A;
              break;
            case 4:
              event = RA_ELC_GPT4_CAPTURE_COMPARE_A;
              break;
            case 5:
              event = RA_ELC_GPT5_CAPTURE_COMPARE_A;
              break;
            case 6:
              event = RA_ELC_GPT6_CAPTURE_COMPARE_A;
              break;
            case 7:
              event = RA_ELC_GPT7_CAPTURE_COMPARE_A;
              break;
            default:
              return -EINVAL;
          }
        break;

      case 2:  /* Compare Match B */
        switch (gpt_channel)
          {
            case 0:
              event = RA_ELC_GPT0_CAPTURE_COMPARE_B;
              break;
            case 1:
              event = RA_ELC_GPT1_CAPTURE_COMPARE_B;
              break;
            case 2:
              event = RA_ELC_GPT2_CAPTURE_COMPARE_B;
              break;
            case 3:
              event = RA_ELC_GPT3_CAPTURE_COMPARE_B;
              break;
            case 4:
              event = RA_ELC_GPT4_CAPTURE_COMPARE_B;
              break;
            case 5:
              event = RA_ELC_GPT5_CAPTURE_COMPARE_B;
              break;
            case 6:
              event = RA_ELC_GPT6_CAPTURE_COMPARE_B;
              break;
            case 7:
              event = RA_ELC_GPT7_CAPTURE_COMPARE_B;
              break;
            default:
              return -EINVAL;
          }
        break;

      default:
        return -EINVAL;
    }

  /* Set the event link */

  ret = ra_elc_link_set((ra_elc_peripheral_t)adc_trigger, event);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ELC: Failed to set GPT%d -> ADC link: %d\n",
             gpt_channel, ret);
      return ret;
    }

  syslog(LOG_INFO, "ELC: GPT%d event 0x%03x -> ADC trigger %d\n",
         gpt_channel, event, adc_trigger);

  return OK;
}

#endif /* CONFIG_RA_ELC */
