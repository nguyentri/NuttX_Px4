/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_cac.c
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

#include <nuttx/arch.h>
#include <arch/board/board.h>

#include "ra_cac.h"
#include "evk-ra8p1.h"

#ifdef CONFIG_RA_CAC

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_cac_initialize
 *
 * Description:
 *   Initialize the CAC driver for the board.
 *
 ****************************************************************************/

int board_cac_initialize(void)
{
  int ret;

#ifdef CONFIG_RA_CAC_EXTERNAL_REF
  /* Configure CACREF pin for external reference clock input */
  ret = ra_gpioconfig(GPIO_CACREF);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to configure CACREF pin: %d\n", ret);
      return ret;
    }
#endif

  /* Initialize the CAC driver */
  ret = ra_cac_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: ra_cac_initialize failed: %d\n", ret);
    }

  return ret;
}

#endif /* CONFIG_RA_CAC */
