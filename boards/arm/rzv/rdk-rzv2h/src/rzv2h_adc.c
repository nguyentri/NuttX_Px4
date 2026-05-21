/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_adc.c
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

#include <errno.h>
#include <debug.h>

#include <nuttx/analog/adc.h>

#include <arch/board/board.h>

#include "rzv_gpio.h"
#include "rzv_adc.h"
#include "rdk-rzv2h.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ADC device path */

#define ADC_DEVPATH "/dev/adc0"

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* ADC channel configuration
 * Configure which channels to enable. Channels 0-7 are available.
 * Modify this array to enable different channels as needed.
 */

#ifdef CONFIG_RZV_ADC0
static const uint8_t g_adc_chanlist[] =
{
  BOARD_ADC_CHANNEL_0,    /* Channel 0 - AN000 */
#ifdef BOARD_ADC_CHANNEL_1
  BOARD_ADC_CHANNEL_1,    /* Channel 1 - AN001 */
#endif
#ifdef BOARD_ADC_CHANNEL_2
  BOARD_ADC_CHANNEL_2,    /* Channel 2 - AN002 */
#endif
#ifdef BOARD_ADC_CHANNEL_3
  BOARD_ADC_CHANNEL_3,    /* Channel 3 - AN003 */
#endif
#ifdef BOARD_ADC_CHANNEL_4
  BOARD_ADC_CHANNEL_4,    /* Channel 4 - AN004 */
#endif
#ifdef BOARD_ADC_CHANNEL_5
  BOARD_ADC_CHANNEL_5,    /* Channel 5 - AN005 */
#endif
#ifdef BOARD_ADC_CHANNEL_6
  BOARD_ADC_CHANNEL_6,    /* Channel 6 - AN006 */
#endif
#ifdef BOARD_ADC_CHANNEL_7
  BOARD_ADC_CHANNEL_7,    /* Channel 7 - AN007 */
#endif
};

#define ADC_NCHANNELS (sizeof(g_adc_chanlist) / sizeof(uint8_t))
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv2h_adc_setup
 *
 * Description:
 *   Initialize ADC and register the ADC device.
 *
 ****************************************************************************/

int rzv2h_adc_setup(void)
{
#ifdef CONFIG_RZV_ADC0
  int ret;

  ainfo("Initializing ADC0\n");

  /* Configure ADC GPIO pins
   * These pins need to be configured as analog inputs.
   * The specific pin configuration depends on the board design.
   * For RZV2H, ADC pins are typically dedicated analog pins that
   * may not require explicit GPIO configuration, but we include
   * this for completeness.
   */

  /* Example: Configure AN000 (P4_4 on some RZV2H variants) as analog */

#ifdef BOARD_ADC_PIN_AN000
  rzv_gpio_config(BOARD_ADC_PIN_AN000);
#endif

#ifdef BOARD_ADC_PIN_AN001
  rzv_gpio_config(BOARD_ADC_PIN_AN001);
#endif

#ifdef BOARD_ADC_PIN_AN002
  rzv_gpio_config(BOARD_ADC_PIN_AN002);
#endif

#ifdef BOARD_ADC_PIN_AN003
  rzv_gpio_config(BOARD_ADC_PIN_AN003);
#endif

#ifdef BOARD_ADC_PIN_AN004
  rzv_gpio_config(BOARD_ADC_PIN_AN004);
#endif

#ifdef BOARD_ADC_PIN_AN005
  rzv_gpio_config(BOARD_ADC_PIN_AN005);
#endif

#ifdef BOARD_ADC_PIN_AN006
  rzv_gpio_config(BOARD_ADC_PIN_AN006);
#endif

#ifdef BOARD_ADC_PIN_AN007
  rzv_gpio_config(BOARD_ADC_PIN_AN007);
#endif

  /* Initialize ADC driver */

  ret = rzv_adc_initialize(ADC_DEVPATH, g_adc_chanlist, ADC_NCHANNELS);
  if (ret < 0)
    {
      aerr("ERROR: rzv_adc_initialize failed: %d\n", ret);
      return ret;
    }

  ainfo("ADC0 initialized successfully\n");
  return OK;
#else
  return -ENODEV;
#endif
}
