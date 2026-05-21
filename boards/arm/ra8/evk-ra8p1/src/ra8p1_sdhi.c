/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_sdhi.c
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

#include <stdbool.h>
#include <stdio.h>
#include <debug.h>
#include <errno.h>

#include <nuttx/sdio.h>
#include <nuttx/mmcsd.h>

#include "ra_gpio.h"
#include "ra_sdhi.h"
#include "evk-ra8p1.h"

#ifdef CONFIG_RA_SDHI

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SDHI Channel 0 */
/* CMD: PD04 */
#define GPIO_SDHI0_CMD   (GPIO_PERIPHERAL | GPIO_PULLUP | GPIO_CFG_DRIVE_HIGH | \
                          PFS_PSEL_SDHI_MMC | PORT13 | PIN4)
/* CLK: PD05 */
#define GPIO_SDHI0_CLK   (GPIO_PERIPHERAL | GPIO_CFG_DRIVE_HIGH | \
                          PFS_PSEL_SDHI_MMC | PORT13 | PIN5)
/* DAT0: PD03 */
#define GPIO_SDHI0_DAT0  (GPIO_PERIPHERAL | GPIO_PULLUP | GPIO_CFG_DRIVE_HIGH | \
                          PFS_PSEL_SDHI_MMC | PORT13 | PIN3)
/* DAT1: PD02 */
#define GPIO_SDHI0_DAT1  (GPIO_PERIPHERAL | GPIO_PULLUP | GPIO_CFG_DRIVE_HIGH | \
                          PFS_PSEL_SDHI_MMC | PORT13 | PIN2)
/* DAT2: PD01 */
#define GPIO_SDHI0_DAT2  (GPIO_PERIPHERAL | GPIO_PULLUP | GPIO_CFG_DRIVE_HIGH | \
                          PFS_PSEL_SDHI_MMC | PORT13 | PIN1)
/* DAT3: P111 */
#define GPIO_SDHI0_DAT3  (GPIO_PERIPHERAL | GPIO_PULLUP | GPIO_CFG_DRIVE_HIGH | \
                          PFS_PSEL_SDHI_MMC | PORT1 | PIN11)
/* CD: P503 - Input, Pullup? Usually CD is pulled up on board. */
/* Note: P503 is also SDRAM_A6, but here used as CD. */
/* We configure it as GPIO Input for software CD check or Peripheral if using SDHI CD function? */
/* FSP uses SDHI CD function usually if available. */
/* P503 has SD0CD function (PSEL 0x15). */
#define GPIO_SDHI0_CD    (GPIO_PERIPHERAL | GPIO_PULLUP | \
                          PFS_PSEL_SDHI_MMC | PORT5 | PIN3)
/* WP: PD06 */
#define GPIO_SDHI0_WP    (GPIO_PERIPHERAL | GPIO_PULLUP | \
                          PFS_PSEL_SDHI_MMC | PORT13 | PIN6)

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_sdhi_initialize
 *
 * Description:
 *   Initialize SDHI-based SD Card support
 *
 ****************************************************************************/

int board_sdhi_init(void)
{
  struct sdio_dev_s *sdio;
  int ret;

  /* Configure Pins */
  ra_gpioconfig(GPIO_SDHI0_CMD);
  ra_gpioconfig(GPIO_SDHI0_CLK);
  ra_gpioconfig(GPIO_SDHI0_DAT0);

#ifdef CONFIG_SDIO_WIDTH_D1_ONLY
  /* 1-bit mode */
#else
  /* 4-bit mode */
  ra_gpioconfig(GPIO_SDHI0_DAT1);
  ra_gpioconfig(GPIO_SDHI0_DAT2);
  ra_gpioconfig(GPIO_SDHI0_DAT3);
#endif

  ra_gpioconfig(GPIO_SDHI0_CD);
  ra_gpioconfig(GPIO_SDHI0_WP);

  /* Initialize SDHI driver */
  sdio = ra_sdhi_initialize(RA_SDHI_CHANNEL_0);
  if (!sdio)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize SDHI driver\n");
      return -ENODEV;
    }

  /* Initialize MMC/SD slot */
  ret = mmcsd_slotinitialize(0, sdio);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to bind SDHI to MMC/SD slot: %d\n", ret);
      return ret;
    }

  return OK;
}

#endif /* CONFIG_RA_SDHI */
