/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_mipi_csi.c
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
#include <stdint.h>
#include <stdbool.h>
#include <debug.h>

#include <nuttx/arch.h>
#include <nuttx/board.h>
#include <arch/board/board.h>

#include "ra_gpio.h"
#include "ra_mipi_csi.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Camera Control Pins */
#define GPIO_CAM_RST    GPIO_CAMERA_RST
#define GPIO_CAM_PWR    GPIO_CAMERA_PWDN

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_mipi_csi_initialize
 *
 * Description:
 *   Initialize the MIPI-CSI camera interface.
 *
 ****************************************************************************/

int board_mipi_csi_initialize(void)
{
  int ret;

  _info("Initializing MIPI-CSI Camera...\n");

  /* Configure Camera Control Pins */
  ra_gpioconfig(GPIO_CAM_RST);
  ra_gpioconfig(GPIO_CAM_PWR);

  /* Power Up Sequence */
  ra_gpiowrite(GPIO_CAM_PWR, 0); /* Power Up */
  up_mdelay(10);

  /* Reset Camera */
  ra_gpiowrite(GPIO_CAM_RST, 0); /* Assert Reset */
  up_mdelay(10);
  ra_gpiowrite(GPIO_CAM_RST, 1); /* Deassert Reset */
  up_mdelay(10);

  /* Initialize Driver */
  ret = ra_mipi_csi_initialize();
  if (ret < 0)
    {
      _err("ERROR: ra_mipi_csi_initialize failed: %d\n", ret);
      return ret;
    }

  return OK;
}
