/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_adc_b_hwtrigger.c
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
#include <nuttx/analog/adc.h>

#include "ra_elc.h"
#include "ra_adc_b.h"
#include "evk-ra8p1.h"

/* Include IRQ definitions for ELC event macros */

#include <arch/ra8/ra8p1_irq.h>

#ifdef CONFIG_RA8P1_ADC_HW_TRIGGER_EXAMPLE

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GPT configuration for ADC triggering example
 * These values can be adjusted based on the desired sampling rate
 */

#define ADC_TRIGGER_GPT_CHANNEL    0      /* Use GPT0 */
#define ADC_TRIGGER_GPT_USE_CMPB   false  /* Use Compare Match A */

/****************************************************************************
 * Private Types
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/
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
 *   Note: For the ADC-ELC example, the ADC driver's built-in functions
 *   (ra8_adc_configure_gpt_trigger, ra8_adc_configure_elc_trigger) handle
 *   the ELC link configuration internally, so manual ELC setup is not
 *   required for ADC triggering.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   OK on success; a negated errno on failure.
 *
 ****************************************************************************/
#ifdef CONFIG_RA_ELC
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
#endif /* CONFIG_RA_ELC */

/****************************************************************************
 * Name: board_adc_initialize
 *
 * Description:
 *   Initialize ADC for GPT-triggered sampling via ELC.
 *   This example demonstrates hardware-triggered ADC conversions using
 *   GPT timer overflow events through the Event Link Controller.
 *   Overrides the default weak implementation.
 *
 ****************************************************************************/

int board_adc_initialize(void)
{
  FAR struct adc_dev_s *adc_dev;
  struct ra_adc_b_chan_cfg_s channels[4];
  int ret;

  syslog(LOG_INFO, "ADC-ELC: Initializing ADC with GPT trigger example\n");

  /* Configure multiple channels for the example
   * This demonstrates sampling multiple analog inputs synchronized
   * to a GPT timer event (e.g., for motor control applications)
   */

  /* Channel 0: Battery Voltage (AN000 on P004) */
  channels[0].vchannel = 0;
  channels[0].pchannel = RA_ADC_CHANNEL_AN000;
  channels[0].scan_group_id = 0;
  channels[0].sampling_table = 0;
  channels[0].resolution = RA_ADC_RESOLUTION_12BIT;
  channels[0].differential = false;
  channels[0].sample_hold = false;

  /* Channel 1: Battery Current (AN004 on P000) */
  channels[1].vchannel = 1;
  channels[1].pchannel = RA_ADC_CHANNEL_AN004;
  channels[1].scan_group_id = 0;
  channels[1].sampling_table = 0;
  channels[1].resolution = RA_ADC_RESOLUTION_12BIT;
  channels[1].differential = false;
  channels[1].sample_hold = false;

  /* Channel 2: Arduino AN0 (AN001 on P003) */
  channels[2].vchannel = 2;
  channels[2].pchannel = RA_ADC_CHANNEL_AN001;
  channels[2].scan_group_id = 0;
  channels[2].sampling_table = 0;
  channels[2].resolution = RA_ADC_RESOLUTION_12BIT;
  channels[2].differential = false;
  channels[2].sample_hold = false;

  /* Channel 3: Arduino AN1 (AN002 on P002) */
  channels[3].vchannel = 3;
  channels[3].pchannel = RA_ADC_CHANNEL_AN002;
  channels[3].scan_group_id = 0;
  channels[3].sampling_table = 0;
  channels[3].resolution = RA_ADC_RESOLUTION_12BIT;
  channels[3].differential = false;
  channels[3].sample_hold = false;

  /* Initialize ADC driver with all channels in scan group 0 */
  adc_dev = ra8_adc_initialize(channels, 4);
  if (adc_dev == NULL)
    {
      syslog(LOG_ERR, "ADC-ELC: Failed to initialize ADC driver\n");
      return -ENODEV;
    }

  /* Configure GPT0 as trigger source using Compare Match A
   * This allows ADC conversions to be synchronized with PWM or
   * periodic timer events for precise sampling timing
   */
  ret = ra8_adc_configure_gpt_trigger(adc_dev, 0, false);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ADC-ELC: Failed to configure GPT trigger: %d\n", ret);
      return ret;
    }

  /* Enable hardware triggering
   * Once enabled, ADC conversions will automatically start on each
   * GPT0 Compare Match A event (no software trigger needed)
   */
  ret = ra8_adc_enable_hw_trigger(adc_dev, true);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ADC-ELC: Failed to enable hardware trigger: %d\n",
             ret);
      return ret;
    }

  /* Set continuous scan mode for automatic re-triggering */
  ret = ra8_adc_set_scan_mode(adc_dev, RA_ADC_MODE_CONTINUOUS_SCAN);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ADC-ELC: Failed to set scan mode: %d\n", ret);
      return ret;
    }

  /* Register the ADC driver */
  ret = adc_register("/dev/adc0", adc_dev);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ADC-ELC: Failed to register driver: %d\n", ret);
      return ret;
    }

  syslog(LOG_INFO,
         "ADC-ELC: Initialized /dev/adc0 with GPT0 trigger\n");
  syslog(LOG_INFO,
         "ADC-ELC: 4 channels in scan group 0, continuous mode\n");
  syslog(LOG_INFO,
         "ADC-ELC: Hardware triggered by GPT0 Compare Match A\n");

  return OK;
}
#endif /* CONFIG_RA8P1_ADC_HW_TRIGGER_EXAMPLE */
