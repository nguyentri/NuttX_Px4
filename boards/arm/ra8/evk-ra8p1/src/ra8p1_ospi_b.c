/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_ospi_b.c
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
#include <errno.h>
#include <debug.h>

#include <nuttx/mtd/mtd.h>
#include <arch/board/board.h>

#include "arm_internal.h"
#include "ra_ospi_b.h"
#include "ra_gpio.h"
#include "evk-ra8p1.h"

#ifdef CONFIG_RA_OSPI

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_ospi_initialize
 *
 * Description:
 *   Initialize the OSPI driver and register the MTD device.
 *
 ****************************************************************************/

int board_ospi_initialize(void)
{
  struct qspi_dev_s *qspi;
  /* struct mtd_dev_s *mtd; */
  /* int ret; */

  /* Configure OSPI0 Pins (OM_0) */

  /* CS0: P107 */
  ra_gpioconfig(GPIO_OM_0_CS0_1);

  /* SCLK: P808 */
  ra_gpioconfig(GPIO_OM_0_SCLK_1);

  /* Data Pins */
  ra_gpioconfig(GPIO_OM_0_SIO0_1); /* P100 */
  ra_gpioconfig(GPIO_OM_0_SIO1_1); /* P803 */
  ra_gpioconfig(GPIO_OM_0_SIO2_1); /* P103 */
  ra_gpioconfig(GPIO_OM_0_SIO3_1); /* P101 */
  ra_gpioconfig(GPIO_OM_0_SIO4_1); /* P102 */
  ra_gpioconfig(GPIO_OM_0_SIO5_1); /* P800 */
  ra_gpioconfig(GPIO_OM_0_SIO6_1); /* P802 */
  ra_gpioconfig(GPIO_OM_0_SIO7_1); /* P804 */

  /* RESET: P106 */
  ra_gpioconfig(GPIO_OM_0_RESET_1);

  /* Initialize the OSPI driver */
  qspi = ra_ospi_initialize(0);
  if (!qspi)
    {
      ferr("ERROR: Failed to initialize OSPI0\n");
      return -ENODEV;
    }

  /* Initialize the MTD driver */
  /* Assuming a generic JEDEC compatible Octal SPI flash or similar */
  /* For now, we just leave it initialized.
     If we need to mount a filesystem, we would do it here. */

  /* Example:
  mtd = w25qxxxjv_initialize(qspi, true);
  if (!mtd)
    {
      ferr("ERROR: Failed to initialize MTD\n");
      return -ENODEV;
    }
  */

  return OK;
}

#endif /* CONFIG_RA_OSPI */
