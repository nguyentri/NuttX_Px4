/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_iic.c
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
#include <errno.h>

#include <nuttx/i2c/i2c_master.h>

#include <arch/board/board.h>

#include "rzv_gpio.h"
#include "rzv_i2c.h"
#include "rdk-rzv2h.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv2h_i2c_initialize
 *
 * Description:
 *   Initialize and configure the I2C (RIIC) interfaces for the RZV2H EVK
 *
 ****************************************************************************/

int rzv2h_i2c_initialize(void)
{
  struct i2c_master_s *i2c;
  int ret = OK;

#ifdef CONFIG_RZV_I2C0
  /* Configure RIIC0 pins */

  rzv_gpioconfig(BOARD_I2C0_SDA_GPIO);
  rzv_gpioconfig(BOARD_I2C0_SCL_GPIO);

  /* Initialize RIIC0 */

  i2c = rzv_i2c_initialize(0);
  if (i2c == NULL)
    {
      i2cerr("ERROR: Failed to initialize I2C0\n");
      ret = -ENODEV;
    }
  else
    {
      i2cinfo("I2C0 (RIIC0) initialized\n");

#ifdef CONFIG_I2C_DRIVER
      /* Register the I2C character driver */

      ret = i2c_register(i2c, 0);
      if (ret < 0)
        {
          i2cerr("ERROR: Failed to register I2C0 driver: %d\n", ret);
        }
#endif
    }
#endif

#ifdef CONFIG_RZV_I2C1
  /* Configure RIIC1 pins */

  rzv_gpioconfig(BOARD_I2C1_SDA_GPIO);
  rzv_gpioconfig(BOARD_I2C1_SCL_GPIO);

  /* Initialize RIIC1 */

  i2c = rzv_i2c_initialize(1);
  if (i2c == NULL)
    {
      i2cerr("ERROR: Failed to initialize I2C1\n");
      ret = -ENODEV;
    }
  else
    {
      i2cinfo("I2C1 (RIIC1) initialized\n");

#ifdef CONFIG_I2C_DRIVER
      /* Register the I2C character driver */

      ret = i2c_register(i2c, 1);
      if (ret < 0)
        {
          i2cerr("ERROR: Failed to register I2C1 driver: %d\n", ret);
        }
#endif
    }
#endif

#ifdef CONFIG_RZV_I2C2
  /* Configure RIIC2 pins */

  rzv_gpioconfig(BOARD_I2C2_SDA_GPIO);
  rzv_gpioconfig(BOARD_I2C2_SCL_GPIO);

  /* Initialize RIIC2 */

  i2c = rzv_i2c_initialize(2);
  if (i2c == NULL)
    {
      i2cerr("ERROR: Failed to initialize I2C2\n");
      ret = -ENODEV;
    }
  else
    {
      i2cinfo("I2C2 (RIIC2) initialized\n");

#ifdef CONFIG_I2C_DRIVER
      /* Register the I2C character driver */

      ret = i2c_register(i2c, 2);
      if (ret < 0)
        {
          i2cerr("ERROR: Failed to register I2C2 driver: %d\n", ret);
        }
#endif
    }
#endif

#ifdef CONFIG_RZV_I2C3
  /* Configure RIIC3 pins (if defined in board.h) */

  /* Note: RIIC3 pins not currently defined in EVK board.h */

  i2c = rzv_i2c_initialize(3);
  if (i2c == NULL)
    {
      i2cerr("ERROR: Failed to initialize I2C3\n");
      ret = -ENODEV;
    }
  else
    {
      i2cinfo("I2C3 (RIIC3) initialized\n");

#ifdef CONFIG_I2C_DRIVER
      /* Register the I2C character driver */

      ret = i2c_register(i2c, 3);
      if (ret < 0)
        {
          i2cerr("ERROR: Failed to register I2C3 driver: %d\n", ret);
        }
#endif
    }
#endif

  return ret;
}
