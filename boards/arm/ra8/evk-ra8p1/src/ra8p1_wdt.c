/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_wdt.c
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

#include <nuttx/timers/watchdog.h>
#include <arch/board/board.h>

#include "ra_wdt.h"
#include "evk-ra8p1.h"

#ifdef CONFIG_RA_WDT

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_wdt_initialize
 *
 * Description:
 *   Initialize the watchdog timer.  The watchdog timer is initialized and
 *   registered as 'devpath'.  The initial state of the watchdog time is
 *   disabled.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

void board_wdt_initialize(void)
{
  int ret;

  /* Initialize the watchdog timer */

  ret = ra_wdt_initialize("/dev/watchdog0");
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: ra_wdt_initialize failed: %d\n", ret);
    }
}

#endif /* CONFIG_RA_WDT */
