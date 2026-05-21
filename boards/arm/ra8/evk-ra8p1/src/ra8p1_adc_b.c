/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_adc_b.c
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
#include <debug.h>

#include <arch/board/board.h>
#include <nuttx/analog/adc.h>
#include <nuttx/analog/ioctl.h>

#include "ra_adc_b.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/**
 * ADC Configuration for evk-ra8p1:adc-b
 *
 * Battery Monitoring:
 *  - GPIO_BATT_VOLT   (AN000) - Battery Voltage 5.7:1 divider on Port P004
 *  - GPIO_BATT_CURR   (AN004) - Battery Current ACS712 on Port P000
 *
 * Expansion Pins:
 *  - GPIO_ARDUINO_AN0 (AN001) - Arduino AN0 on Port P003
 *  - GPIO_GROVE2_AN0  (AN002) - Grove2 AN0 on Port P002 (if available as analog)
 *
 * Note: ADC-B supports virtual channels 0-32 for ADC Unit 0 (AN000-AN022)
 *       For ADC Unit 1 channels (AN100+), use separate driver instance
 */

/* ADC channel configuration - physical channel numbers */

#define ADC_BATTERY_VOLTAGE_CHANNEL    RA_ADC_CHANNEL_AN000  /* AN000 - Battery Voltage */
#define ADC_BATTERY_CURRENT_CHANNEL    RA_ADC_CHANNEL_AN004  /* AN004 - Battery Current */
#define ADC_ARDUINO_AN0_CHANNEL        RA_ADC_CHANNEL_AN001  /* AN001 - Arduino Expansion */
#define ADC_ARDUINO_AN1_CHANNEL        RA_ADC_CHANNEL_AN002  /* AN002 - Arduino Expansion */

/* Maximum channels supported by 32-bit channel mask */

#define ADC_MAX_CHANNELS_MASK          32

/****************************************************************************
 * Private Types
 ****************************************************************************/

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra8_adc_setup
 *
 * Description:
 *   Initialize and register the ADC device for evk-ra8p1
 *
 ****************************************************************************/

int ra8_adc_setup(void)
{
  FAR struct adc_dev_s *adc_dev;
  struct ra_adc_b_chan_cfg_s channels[RA_ADC_B_MAX_CHANNELS];
  int nchannels = 0;
  int ret = OK;

  ainfo("Setting up ADC-B for evk-ra8p1\n");

  /* Configure the ADC channel list for enabled features. */

#ifdef CONFIG_EXAMPLES_ADC
  /* Enable battery monitoring channels if ADC examples are configured */

  if (nchannels < ADC_B_MAX_CHANNELS)
    {
      channels[nchannels].vchannel = 0;
      channels[nchannels].pchannel = ADC_BATTERY_VOLTAGE_CHANNEL;
      channels[nchannels].scan_group_id = 0;
      channels[nchannels].sampling_table = 0;
      channels[nchannels].resolution = RA_ADC_RESOLUTION_12BIT; /* Use default */
      channels[nchannels].differential = false;
      channels[nchannels].sample_hold = false;
      nchannels++;
    }

#ifdef CONFIG_RA_ADC_BATTERY_CURRENT
  if (nchannels < ADC_B_MAX_CHANNELS)
    {
      channels[nchannels].vchannel = 1;
      channels[nchannels].pchannel = ADC_BATTERY_CURRENT_CHANNEL;
      channels[nchannels].scan_group_id = 0;
      channels[nchannels].sampling_table = 0;
      channels[nchannels].resolution = RA_ADC_RESOLUTION_12BIT;
      channels[nchannels].differential = false;
      channels[nchannels].sample_hold = false;
      nchannels++;
    }
#endif

#ifdef CONFIG_RA_ADC_ARDUINO
  if (nchannels < ADC_B_MAX_CHANNELS)
    {
      channels[nchannels].vchannel = 2;
      channels[nchannels].pchannel = ADC_ARDUINO_AN0_CHANNEL;
      channels[nchannels].scan_group_id = 0;
      channels[nchannels].sampling_table = 0;
      channels[nchannels].resolution = RA_ADC_RESOLUTION_12BIT;
      channels[nchannels].differential = false;
      channels[nchannels].sample_hold = false;
      nchannels++;
    }
#endif
#endif

  if (nchannels == 0)
    {
      ainfo("No ADC channels configured\n");
      return OK;
    }

  /* Initialize the ADC-B module */
  adc_dev = ra8_adc_initialize(channels, nchannels);
  if (adc_dev == NULL)
    {
      aerr("ERROR: Failed to initialize ADC-B\n");
      return -ENODEV;
    }

  /* Register the ADC driver at /dev/adc0 */
  ret = adc_register("/dev/adc0", adc_dev);
  if (ret < 0)
    {
      aerr("ERROR: adc_register failed: %d\n", ret);
      return ret;
    }

  ainfo("ADC-B setup complete with %d channels\n", nchannels);
  return OK;
}

/****************************************************************************
 * Name: board_adc_initialize
 *
 * Description:
 *   Board-level ADC initialization hook called during board setup
 *
 ****************************************************************************/

weak_function int board_adc_initialize(void)
{
#ifdef CONFIG_RA_ADC_B
  return ra8_adc_setup();
#else
  return OK;
#endif
}
