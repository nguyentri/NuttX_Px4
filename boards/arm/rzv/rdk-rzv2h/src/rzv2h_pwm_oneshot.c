/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_pwm_oneshot.c
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

#ifdef CONFIG_RZV2H_PWM_ONESHOT_EXAMPLE

#include <errno.h>
#include <syslog.h>

#include <arch/board/board.h>

#include "rdk-rzv2h.h"

int pwm_main(int argc, char *argv[]);

/****************************************************************************
 * Public Functions
 ****************************************************************************/

int rzv2h_pwm_oneshot_init(void)
{
  int ret = board_pwm_initialize();
  if (ret < 0 && ret != -EALREADY)
    {
      syslog(LOG_ERR, "ERROR: board_pwm_initialize() failed: %d\n", ret);
      return ret;
    }

  return OK;
}

int rzv2h_pwm_oneshot_main(int argc, char *argv[])
{
  char *args[] = {"pwm", NULL};
  return pwm_main(1, args);
}

#endif /* CONFIG_RZV2H_PWM_ONESHOT_EXAMPLE */
