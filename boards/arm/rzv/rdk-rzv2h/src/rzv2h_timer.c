/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_timer.c
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
#include <sys/ioctl.h>

#include <errno.h>
#include <debug.h>
#include <syslog.h>
#include <stdio.h>

#include <nuttx/timers/timer.h>

#include "rzv_gtm.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_timer_initialize
 *
 * Description:
 *   Configure the timer driver.
 *
 ****************************************************************************/

int board_timer_initialize(void)
{
  int ret = OK;
  FAR struct timer_lowerhalf_s *lower = NULL;

#ifdef CONFIG_RZV_GTM0_TIMER
  /* Initialize GTM0 */

  lower = rzv_gtm_timer_initialize(0);
  if (lower == NULL)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize GTM0\n");
      ret = -ENODEV;
    }
  else
    {
      timer_register("/dev/timer0", lower);
      syslog(LOG_INFO, "GTM0 registered as /dev/timer0\n");
    }
#endif

#ifdef CONFIG_RZV_GTM1_TIMER
  /* Initialize GTM1 */

  lower = rzv_gtm_timer_initialize(1);
  if (lower == NULL)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize GTM1\n");
      ret = -ENODEV;
    }
  else
    {
      ret = timer_register("/dev/timer1", lower);
      if (ret < 0)
        {
          syslog(LOG_ERR, "ERROR: Failed to register GTM1: %d\n", ret);
        }
      else
        {
          syslog(LOG_INFO, "GTM1 registered as /dev/timer1\n");
        }
    }
#endif

#ifdef CONFIG_RZV_GTM2_TIMER
  /* Initialize GTM2 */

  lower = rzv_gtm_timer_initialize(2);
  if (lower == NULL)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize GTM2\n");
      ret = -ENODEV;
    }
  else
    {
      timer_register("/dev/timer2", lower);
      syslog(LOG_INFO, "GTM2 registered as /dev/timer2\n");
    }
#endif

#ifdef CONFIG_RZV_GTM3_TIMER
  /* Initialize GTM3 */

  lower = rzv_gtm_timer_initialize(3);
  if (lower == NULL)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize GTM3\n");
      ret = -ENODEV;
    }
  else
    {
      ret = timer_register("/dev/timer3", lower);
      if (ret < 0)
        {
          syslog(LOG_ERR, "ERROR: Failed to register GTM3: %d\n", ret);
        }
      else
        {
          syslog(LOG_INFO, "GTM3 registered as /dev/timer3\n");
        }
    }
#endif

#ifdef CONFIG_RZV_GTM4_TIMER
  /* Initialize GTM4 */

  lower = rzv_gtm_timer_initialize(4);
  if (lower == NULL)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize GTM4\n");
      ret = -ENODEV;
    }
  else
    {
      ret = timer_register("/dev/timer4", lower);
      if (ret < 0)
        {
          syslog(LOG_ERR, "ERROR: Failed to register GTM4: %d\n", ret);
        }
      else
        {
          syslog(LOG_INFO, "GTM4 registered as /dev/timer4\n");
        }
    }
#endif

#ifdef CONFIG_RZV_GTM5_TIMER
  /* Initialize GTM5 */

  lower = rzv_gtm_timer_initialize(5);
  if (lower == NULL)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize GTM5\n");
      ret = -ENODEV;
    }
  else
    {
      ret = timer_register("/dev/timer5", lower);
      if (ret < 0)
        {
          syslog(LOG_ERR, "ERROR: Failed to register GTM5: %d\n", ret);
        }
      else
        {
          syslog(LOG_INFO, "GTM5 registered as /dev/timer5\n");
        }
    }
#endif

#ifdef CONFIG_RZV_GTM6_TIMER
  /* Initialize GTM6 */

  lower = rzv_gtm_timer_initialize(6);
  if (lower == NULL)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize GTM6\n");
      ret = -ENODEV;
    }
  else
    {
      ret = timer_register("/dev/timer6", lower);
      if (ret < 0)
        {
          syslog(LOG_ERR, "ERROR: Failed to register GTM6: %d\n", ret);
        }
      else
        {
          syslog(LOG_INFO, "GTM6 registered as /dev/timer6\n");
        }
    }
#endif

#ifdef CONFIG_RZV_GTM7_TIMER
  /* Initialize GTM7 */

  lower = rzv_gtm_timer_initialize(7);
  if (lower == NULL)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize GTM7\n");
      ret = -ENODEV;
    }
  else
    {
      ret = timer_register("/dev/timer7", lower);
      if (ret < 0)
        {
          syslog(LOG_ERR, "ERROR: Failed to register GTM7: %d\n", ret);
        }
      else
        {
          syslog(LOG_INFO, "GTM7 registered as /dev/timer7\n");
        }
    }
#endif

  return ret;
}
