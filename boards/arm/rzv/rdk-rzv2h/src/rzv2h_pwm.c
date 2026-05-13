/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_pwm.c
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

#ifdef CONFIG_RZV_PWM

#include <errno.h>
#include <stdbool.h>

#include <nuttx/board.h>
#include <nuttx/errno.h>
#include <nuttx/timers/pwm.h>

#include "rzv_gpio.h"
#include "rzv_gpt.h"
#include "rdk-rzv2h.h"
#include "board.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define RZV2H_PWM_CHANNEL_COUNT 4

struct rzv2h_pwm_channel_s
{
  const char *devpath;
  int         gpt_channel;
  uint32_t    gpio;
};

/****************************************************************************
 * Private Data
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv2h_pwm_setup
 *
 * Description:
 *   Configure the GPT channel routed to the EVK PWM test point and register
 *   the lower-half driver with the NuttX PWM subsystem.
 *
 ****************************************************************************/

int rzv2h_pwm_setup(void)
{
  static const struct rzv2h_pwm_channel_s channels[RZV2H_PWM_CHANNEL_COUNT] =
  {
    { "/dev/pwm0", 6,  BOARD_PWM_CH0_GPIO },
    { "/dev/pwm1", 7,  BOARD_PWM_CH1_GPIO },
    { "/dev/pwm2", 9,  BOARD_PWM_CH2_GPIO },
    { "/dev/pwm3", 10, BOARD_PWM_CH3_GPIO },
  };

  static bool initialized;
  FAR struct pwm_lowerhalf_s *pwm;
  int ret;
  int i;

  if (initialized)
    {
      return OK;
    }

  for (i = 0; i < RZV2H_PWM_CHANNEL_COUNT; i++)
    {
      ret = rzv_gpioconfig(channels[i].gpio);
      if (ret < 0)
        {
          return ret;
        }

      pwm = rzv_gpt_initialize(channels[i].gpt_channel);
      if (pwm == NULL)
        {
          return -ENODEV;
        }

      ret = pwm_register(channels[i].devpath, pwm);
      if (ret < 0)
        {
          return ret;
        }
    }

  initialized = true;
  return OK;
}

int board_pwm_initialize(void)
{
  return rzv2h_pwm_setup();
}

#endif /* CONFIG_RZV_PWM */
