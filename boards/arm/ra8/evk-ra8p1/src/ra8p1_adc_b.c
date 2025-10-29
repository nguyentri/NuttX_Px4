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
 *  - GPIO_BATT_CURR   (AN104) - Battery Current ACS712 on Port P005
 *
 * Expansion Pins:
 *  - GPIO_ARDUINO_AN0 (AN001) - Arduino AN0 on Port P001
 *  - GPIO_GROVE2_AN0  (AN002) - Grove2 AN0 on Port P002 (if available as analog)
 */

/* ADC channel configuration */
#define ADC_BATTERY_VOLTAGE_CHANNEL    0   /* AN000 - Battery Voltage */
#define ADC_BATTERY_CURRENT_CHANNEL    104 /* AN104 - Battery Current */
#define ADC_ARDUINO_AN0_CHANNEL        1   /* AN001 - Arduino Expansion */

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
  uint32_t chanlist;
  int nchannels = 0;
  int ret = OK;

  ainfo("Setting up ADC-B for evk-ra8p1\n");

  /* Configure the ADC channel list for enabled features */
  chanlist = 0;

#ifdef CONFIG_EXAMPLES_ADC
  /* Enable battery monitoring channels if ADC examples are configured */
  chanlist |= (1 << ADC_BATTERY_VOLTAGE_CHANNEL);
  nchannels++;

#ifdef CONFIG_RA_ADC_BATTERY_CURRENT
  chanlist |= (1 << ADC_BATTERY_CURRENT_CHANNEL);
  nchannels++;
#endif

#ifdef CONFIG_RA_ADC_ARDUINO
  chanlist |= (1 << ADC_ARDUINO_AN0_CHANNEL);
  nchannels++;
#endif
#endif

  if (nchannels == 0)
    {
      ainfo("No ADC channels configured\n");
      return OK;
    }

  /* Initialize the ADC-B module */
  adc_dev = ra8_adc_initialize(chanlist, nchannels);
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
