/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_pwm.c
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
#include <errno.h>
#include <debug.h>

#include <nuttx/board.h>
#include <nuttx/timers/pwm.h>

#include <arch/board/board.h>

#include "chip.h"
#include "arm_internal.h"
#include "ra_gpio.h"
#include "ra_gpt.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Configuration ************************************************************/

/* PWM Channels for ESC control:
 * - Motor 1: GPT3 Channel A (P912)
 * - Motor 2: GPT5 Channel A (P915)
 * - Motor 3: GPT11 Channel A (P903)
 * - Motor 4: GPT13 Channel A (P515)
 */

#define PWM_MOTOR1_CHANNEL  3
#define PWM_MOTOR2_CHANNEL  5
#define PWM_MOTOR3_CHANNEL  11
#define PWM_MOTOR4_CHANNEL  13

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_pwm_initialize
 *
 * Description:
 *   Initialize PWM and register the PWM devices for motor control.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int board_pwm_initialize(void)
{
  static bool initialized = false;
  struct pwm_lowerhalf_s *pwm;
  int ret;

  /* Have we already initialized? */

  if (!initialized)
    {
      /* Configure GPIO pins for GPT output */

#ifdef CONFIG_RA_GPT3
      /* Motor 1: P912 - GPT3 Channel A */
      ra_gpioconfig(GPIO_TIM3_CH1OUT);
#endif

#ifdef CONFIG_RA_GPT5
      /* Motor 2: P915 - GPT5 Channel A */
      ra_gpioconfig(GPIO_TIM5_CH1OUT);
#endif

#ifdef CONFIG_RA_GPT11
      /* Motor 3: P903 - GPT11 Channel A */
      ra_gpioconfig(GPIO_TIM11_CH1OUT);
#endif

#ifdef CONFIG_RA_GPT13
      /* Motor 4: P515 - GPT13 Channel A */
      ra_gpioconfig(GPIO_TIM13_CH1OUT);
#endif

      /* Initialize Motor 1 - GPT3 */

#ifdef CONFIG_RA_GPT3
      pwm = ra_gpt_initialize(PWM_MOTOR1_CHANNEL);
      if (!pwm)
        {
          pwmerr("ERROR: Failed to get GPT3 interface\n");
          return -ENODEV;
        }

      ret = pwm_register("/dev/pwm0", pwm);
      if (ret < 0)
        {
          pwmerr("ERROR: pwm_register /dev/pwm0 failed: %d\n", ret);
          return ret;
        }

      pwminfo("Registered /dev/pwm0 (Motor 1 - GPT3A/P912)\n");
#endif

      /* Initialize Motor 2 - GPT5 */

#ifdef CONFIG_RA_GPT5
      pwm = ra_gpt_initialize(PWM_MOTOR2_CHANNEL);
      if (!pwm)
        {
          pwmerr("ERROR: Failed to get GPT5 interface\n");
          return -ENODEV;
        }

      ret = pwm_register("/dev/pwm1", pwm);
      if (ret < 0)
        {
          pwmerr("ERROR: pwm_register /dev/pwm1 failed: %d\n", ret);
          return ret;
        }

      pwminfo("Registered /dev/pwm1 (Motor 2 - GPT5A/P915)\n");
#endif

      /* Initialize Motor 3 - GPT11 */

#ifdef CONFIG_RA_GPT11
      pwm = ra_gpt_initialize(PWM_MOTOR3_CHANNEL);
      if (!pwm)
        {
          pwmerr("ERROR: Failed to get GPT11 interface\n");
          return -ENODEV;
        }

      ret = pwm_register("/dev/pwm2", pwm);
      if (ret < 0)
        {
          pwmerr("ERROR: pwm_register /dev/pwm2 failed: %d\n", ret);
          return ret;
        }

      pwminfo("Registered /dev/pwm2 (Motor 3 - GPT11A/P903)\n");
#endif

      /* Initialize Motor 4 - GPT13 */

#ifdef CONFIG_RA_GPT13
      pwm = ra_gpt_initialize(PWM_MOTOR4_CHANNEL);
      if (!pwm)
        {
          pwmerr("ERROR: Failed to get GPT13 interface\n");
          return -ENODEV;
        }

      ret = pwm_register("/dev/pwm3", pwm);
      if (ret < 0)
        {
          pwmerr("ERROR: pwm_register /dev/pwm3 failed: %d\n", ret);
          return ret;
        }

      pwminfo("Registered /dev/pwm3 (Motor 4 - GPT13A/P515)\n");
#endif

      /* Now we are initialized */

      initialized = true;
    }

  return OK;
}
