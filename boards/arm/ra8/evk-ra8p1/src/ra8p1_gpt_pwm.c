/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_gpt_pwm.c
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
#include <sys/types.h>

#include <nuttx/timers/pwm.h>
#include <nuttx/timers/timer.h>

#include "chip.h"
#include "ra_gpt.h"

#ifdef CONFIG_PWM

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

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
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_gpt_initialize
 *
 * Description:
 *   Initialize GPT (General Purpose Timer) PWM devices.
 *   This function registers the configured GPT channels with the PWM driver
 *   subsystem.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on any failure.
 *
 ****************************************************************************/

int board_gpt_initialize(void)
{
  int ret = OK;

#ifdef CONFIG_RA_GPT0
  /* Initialize GPT0 for PWM output */
  struct pwm_lowerhalf_s *pwm0 = ra_gpt_initialize(0);
  if (pwm0 == NULL)
    {
      pwmerr("Failed to initialize GPT0\n");
      return -ENODEV;
    }

  /* Register PWM device */
  ret = pwm_register("/dev/pwm0", pwm0);
  if (ret < 0)
    {
      pwmerr("pwm_register /dev/pwm0 failed: %d\n", ret);
      return ret;
    }
#endif

#ifdef CONFIG_RA_GPT1
  /* Initialize GPT1 for PWM output */
  struct pwm_lowerhalf_s *pwm1 = ra_gpt_initialize(1);
  if (pwm1 == NULL)
    {
      pwmerr("Failed to initialize GPT1\n");
      return -ENODEV;
    }

  ret = pwm_register("/dev/pwm1", pwm1);
  if (ret < 0)
    {
      pwmerr("pwm_register /dev/pwm1 failed: %d\n", ret);
      return ret;
    }
#endif

#ifdef CONFIG_RA_GPT2
  /* Initialize GPT2 for PWM output */
  struct pwm_lowerhalf_s *pwm2 = ra_gpt_initialize(2);
  if (pwm2 == NULL)
    {
      pwmerr("Failed to initialize GPT2\n");
      return -ENODEV;
    }

  ret = pwm_register("/dev/pwm2", pwm2);
  if (ret < 0)
    {
      pwmerr("pwm_register /dev/pwm2 failed: %d\n", ret);
      return ret;
    }
#endif

#ifdef CONFIG_RA_GPT3
  /* Initialize GPT3 for PWM output */
  struct pwm_lowerhalf_s *pwm3 = ra_gpt_initialize(3);
  if (pwm3 == NULL)
    {
      pwmerr("Failed to initialize GPT3\n");
      return -ENODEV;
    }

  ret = pwm_register("/dev/pwm3", pwm3);
  if (ret < 0)
    {
      pwmerr("pwm_register /dev/pwm3 failed: %d\n", ret);
      return ret;
    }
#endif

#ifdef CONFIG_RA_GPT4
  /* Initialize GPT4 for PWM output */
  struct pwm_lowerhalf_s *pwm4 = ra_gpt_initialize(4);
  if (pwm4 == NULL)
    {
      pwmerr("Failed to initialize GPT4\n");
      return -ENODEV;
    }

  ret = pwm_register("/dev/pwm4", pwm4);
  if (ret < 0)
    {
      pwmerr("pwm_register /dev/pwm4 failed: %d\n", ret);
      return ret;
    }
#endif

#ifdef CONFIG_RA_GPT5
  /* Initialize GPT5 for PWM output */
  struct pwm_lowerhalf_s *pwm5 = ra_gpt_initialize(5);
  if (pwm5 == NULL)
    {
      pwmerr("Failed to initialize GPT5\n");
      return -ENODEV;
    }

  ret = pwm_register("/dev/pwm5", pwm5);
  if (ret < 0)
    {
      pwmerr("pwm_register /dev/pwm5 failed: %d\n", ret);
      return ret;
    }
#endif

  pwminfo("GPT PWM devices registered successfully\n");
  return ret;
}

#endif /* CONFIG_PWM */
