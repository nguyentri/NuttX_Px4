/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_wdt.c
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
#include <syslog.h>
#include <errno.h>

#include <nuttx/timers/watchdog.h>

#include "rzv_wdt.h"

#ifdef CONFIG_RZV_WDT

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_wdt_setup
 *
 * Description:
 *   Initialize the watchdog timer for the board. This function is called
 *   from board initialization to set up the watchdog timer according to
 *   the board configuration.
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure.
 *
 ****************************************************************************/

int rzv_wdt_setup(void)
{
  int ret = OK;

#ifdef CONFIG_RZV_WDT0
  /* Initialize WDT0 for CR8_0 core (typically used for PX4) */

  ret = rzv_wdt_initialize(CONFIG_RZV_WDT0_DEVPATH, 0);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize WDT0: %d\n", ret);
      return ret;
    }

  syslog(LOG_INFO, "WDT0 initialized at %s\n", CONFIG_RZV_WDT0_DEVPATH);
#endif

#ifdef CONFIG_RZV_WDT1
  /* Initialize WDT1 for CR8_1 core */

  ret = rzv_wdt_initialize(CONFIG_RZV_WDT1_DEVPATH, 1);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize WDT1: %d\n", ret);
      return ret;
    }

  syslog(LOG_INFO, "WDT1 initialized at %s\n", CONFIG_RZV_WDT1_DEVPATH);
#endif

#ifdef CONFIG_RZV_WDT2
  /* Initialize WDT2 for CM33 core */

  ret = rzv_wdt_initialize(CONFIG_RZV_WDT2_DEVPATH, 2);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize WDT2: %d\n", ret);
      return ret;
    }

  syslog(LOG_INFO, "WDT2 initialized at %s\n", CONFIG_RZV_WDT2_DEVPATH);
#endif

#ifdef CONFIG_RZV_WDT3
  /* Initialize WDT3 for CA55 core */

  ret = rzv_wdt_initialize(CONFIG_RZV_WDT3_DEVPATH, 3);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize WDT3: %d\n", ret);
      return ret;
    }

  syslog(LOG_INFO, "WDT3 initialized at %s\n", CONFIG_RZV_WDT3_DEVPATH);
#endif

  return ret;
}

#endif /* CONFIG_RZV_WDT */
