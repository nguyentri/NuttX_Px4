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
 * - Motor 1: GPT3 Channel A (P300)
 * - Motor 2: GPT0 Channel A (P415)
 * - Motor 3: GPT2 Channel A (P113)
 * - Motor 4: GPT4 Channel A (P302)
 */

#define PWM_MOTOR1_CHANNEL  3
#define PWM_MOTOR2_CHANNEL  0
#define PWM_MOTOR3_CHANNEL  2
#define PWM_MOTOR4_CHANNEL  4

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
      /* Motor 1: P300 - GPT3 Channel A */
      ra_gpioconfig(GPIO_GTIOC3A_1);
#endif

#ifdef CONFIG_RA_GPT0
      /* Motor 2: P415 - GPT0 Channel A */
      ra_gpioconfig(GPIO_GTIOC0A_2);
#endif

#ifdef CONFIG_RA_GPT2
      /* Motor 3: P113 - GPT2 Channel A */
      ra_gpioconfig(GPIO_GTIOC2A_2);
#endif

#ifdef CONFIG_RA_GPT4
      /* Motor 4: P302 - GPT4 Channel A */
      ra_gpioconfig(GPIO_GTIOC4A_2);
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

      pwminfo("Registered /dev/pwm0 (Motor 1 - GPT3A/P300)\n");
#endif

      /* Initialize Motor 2 - GPT0 */

#ifdef CONFIG_RA_GPT0
      pwm = ra_gpt_initialize(PWM_MOTOR2_CHANNEL);
      if (!pwm)
        {
          pwmerr("ERROR: Failed to get GPT0 interface\n");
          return -ENODEV;
        }

      ret = pwm_register("/dev/pwm1", pwm);
      if (ret < 0)
        {
          pwmerr("ERROR: pwm_register /dev/pwm1 failed: %d\n", ret);
          return ret;
        }

      pwminfo("Registered /dev/pwm1 (Motor 2 - GPT0A/P415)\n");
#endif

      /* Initialize Motor 3 - GPT2 */

#ifdef CONFIG_RA_GPT2
      pwm = ra_gpt_initialize(PWM_MOTOR3_CHANNEL);
      if (!pwm)
        {
          pwmerr("ERROR: Failed to get GPT2 interface\n");
          return -ENODEV;
        }

      ret = pwm_register("/dev/pwm2", pwm);
      if (ret < 0)
        {
          pwmerr("ERROR: pwm_register /dev/pwm2 failed: %d\n", ret);
          return ret;
        }

      pwminfo("Registered /dev/pwm2 (Motor 3 - GPT2A/P113)\n");
#endif

      /* Initialize Motor 4 - GPT4 */

#ifdef CONFIG_RA_GPT4
      pwm = ra_gpt_initialize(PWM_MOTOR4_CHANNEL);
      if (!pwm)
        {
          pwmerr("ERROR: Failed to get GPT4 interface\n");
          return -ENODEV;
        }

      ret = pwm_register("/dev/pwm3", pwm);
      if (ret < 0)
        {
          pwmerr("ERROR: pwm_register /dev/pwm3 failed: %d\n", ret);
          return ret;
        }

      pwminfo("Registered /dev/pwm3 (Motor 4 - GPT4A/P302)\n");
#endif

      /* Now we are initialized */

      initialized = true;
    }

  return OK;
}
