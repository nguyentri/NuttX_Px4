/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_ipc.c
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

#ifdef CONFIG_RA_IPC

#include <stdint.h>
#include <stdbool.h>
#include <debug.h>

#include <nuttx/board.h>
#include <arch/board/board.h>

#include "ra_ipc.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_ipc_initialize
 *
 * Description:
 *   Initialize IPC subsystem for EVK-RA8P1 board
 *
 ****************************************************************************/

int board_ipc_initialize(void)
{
  int ret;

  _info("Initializing IPC driver for %s (CPU%d)\n",
        CONFIG_RA_CPU_CORE == 0 ? "CM85" : "CM33",
        CONFIG_RA_CPU_CORE);

  /* Initialize lower-half IPC driver */

  ret = ra_ipc_initialize();
  if (ret < 0)
    {
      _err("Failed to initialize IPC driver: %d\n", ret);
      return ret;
    }

#ifdef CONFIG_RA_IPC_IPCC
  /* Initialize IPCC upper-half integration */

  ret = ra_ipcc_initialize();
  if (ret < 0)
    {
      _err("Failed to initialize IPCC: %d\n", ret);
      return ret;
    }

  _info("IPCC devices registered: /dev/ipcc0-3\n");
#endif

  _info("IPC initialization complete\n");

  return OK;
}

#endif /* CONFIG_RA_IPC */
