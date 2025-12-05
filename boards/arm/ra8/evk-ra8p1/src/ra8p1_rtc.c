/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_rtc.c
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

#include <nuttx/timers/rtc.h>

#ifdef CONFIG_RTC_DRIVER
#  include <nuttx/timers/rtc.h>
#  include "ra_rtc_lowerhalf.h"
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_rtc_initialize
 *
 * Description:
 *   Initialize and register the RTC driver.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

#ifdef CONFIG_RTC_DRIVER
int board_rtc_initialize(void)
{
  FAR struct rtc_lowerhalf_s *lower;
  int ret;

  rtcinfo("Registering RTC driver\n");

  /* Get the lower-half driver interface */

  lower = ra_rtc_lowerhalf();
  if (lower == NULL)
    {
      rtcerr("ERROR: Failed to get RTC lower-half interface\n");
      return -ENODEV;
    }

  /* Register the RTC driver at /dev/rtc0 */

  ret = rtc_initialize(0, lower);
  if (ret < 0)
    {
      rtcerr("ERROR: rtc_initialize failed: %d\n", ret);
      return ret;
    }

  rtcinfo("RTC driver registered at /dev/rtc0\n");
  return OK;
}
#endif /* CONFIG_RTC_DRIVER */
