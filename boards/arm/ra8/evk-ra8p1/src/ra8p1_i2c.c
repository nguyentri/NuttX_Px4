/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_i2c.c
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

#include "ra_i2c.h"
#include "ra_gpio.h"
#include "evk-ra8p1.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

#ifdef CONFIG_RA_I2C0
static struct i2c_master_s *g_i2c0_dev = NULL;
#endif

#ifdef CONFIG_RA_I2C1
static struct i2c_master_s *g_i2c1_dev = NULL;
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_i2c_initialize
 *
 * Description:
 *   Initialize I2C bus for EVK-RA8P1 board
 *   Based on FSP sample configuration from hal_data.c and pin_data.c
 *
 * Input Parameters:
 *   bus - I2C bus number (0, 1, or 2)
 *
 * Returned Value:
 *   Pointer to I2C device structure on success; NULL on failure
 *
 ****************************************************************************/

struct i2c_master_s *board_i2c_initialize(int bus)
{
  struct i2c_master_s *dev = NULL;

  i2cinfo("Initializing I2C%d\n", bus);

  switch (bus)
    {
#ifdef CONFIG_RA_I2C0
      case 0:
        /* Initialize I2C0
         * FSP configuration:
         * - Channel: 0
         * - Slave address: configurable (default 0x1D)
         * - Rate: I2C_MASTER_RATE_STANDARD (100 kHz)
         * - Clock settings from FSP:
         *   - CKS: 4 (PCLKB/16)
         *   - BRL: 17, BRH: 16
         *   - Calculated bitrate: ~97.809 kHz, duty cycle: 49%
         * - Pins: P410 (SCL0), P409 (SDA0)
         */

        if (g_i2c0_dev == NULL)
          {
            g_i2c0_dev = ra_i2cbus_initialize(0);
            if (g_i2c0_dev == NULL)
              {
                i2cerr("ERROR: Failed to initialize I2C0\n");
                return NULL;
              }

            i2cinfo("I2C0 initialized successfully\n");
          }

        dev = g_i2c0_dev;
        break;
#endif

#ifdef CONFIG_RA_I2C1
      case 1:
        /* Initialize I2C1
         * FSP configuration:
         * - Channel: 1
         * - Slave address: 0x1D (configurable)
         * - Rate: I2C_MASTER_RATE_STANDARD (100 kHz)
         * - Clock settings from FSP:
         *   - CKS: 4 (PCLKB/16)
         *   - BRL: 17, BRH: 16
         *   - Calculated bitrate: ~97.809 kHz, duty cycle: 49%
         * - Pins: P512/P205 (SCL1), P511/P206 (SDA1)
         *   Default: P205 (SCL1), P206 (SDA1)
         */

        if (g_i2c1_dev == NULL)
          {
            g_i2c1_dev = ra_i2cbus_initialize(1);
            if (g_i2c1_dev == NULL)
              {
                i2cerr("ERROR: Failed to initialize I2C1\n");
                return NULL;
              }

            i2cinfo("I2C1 initialized successfully\n");
          }

        dev = g_i2c1_dev;
        break;
#endif

      default:
        i2cerr("ERROR: Invalid I2C bus: %d\n", bus);
        return NULL;
    }

  return dev;
}

/****************************************************************************
 * Name: board_i2c_uninitialize
 *
 * Description:
 *   Uninitialize I2C bus
 *
 * Input Parameters:
 *   bus - I2C bus number
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure
 *
 ****************************************************************************/

int board_i2c_uninitialize(int bus)
{
  struct i2c_master_s *dev = NULL;
  int ret = OK;

  i2cinfo("Uninitializing I2C%d\n", bus);

  switch (bus)
    {
#ifdef CONFIG_RA_I2C0
      case 0:
        dev = g_i2c0_dev;
        g_i2c0_dev = NULL;
        break;
#endif

#ifdef CONFIG_RA_I2C1
      case 1:
        dev = g_i2c1_dev;
        g_i2c1_dev = NULL;
        break;
#endif

      default:
        i2cerr("ERROR: Invalid I2C bus: %d\n", bus);
        return -EINVAL;
    }

  if (dev != NULL)
    {
      ret = ra_i2cbus_uninitialize(dev);
      if (ret < 0)
        {
          i2cerr("ERROR: Failed to uninitialize I2C%d: %d\n", bus, ret);
        }
    }

  return ret;
}
