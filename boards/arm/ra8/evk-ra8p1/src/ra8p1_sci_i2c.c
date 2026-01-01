/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_sci_i2c.c
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

#include "ra_sci_i2c.h"
#include "ra_gpio.h"
#include "evk-ra8p1.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SCI I2C Pin Definitions for EVK-RA8P1
 *
 * SCI1 I2C Mode:
 *   - SDA: P400 (TXD1_A) - requires open-drain, pull-up
 *   - SCL: P401 (RXD1_A) - requires open-drain, pull-up
 *
 * For SCI Simple I2C mode, TXD becomes SDA and RXD becomes SCL.
 * Both pins must be configured as:
 *   - Peripheral mode (PMR=1)
 *   - PSEL = SCI1_3_5_7_9 (0x05)
 *   - Open-drain (NCODR=1)
 *   - Internal pull-up (PCR=1) or external pull-ups required
 */

#define GPIO_SCI1_I2C_SDA  (PORT4 | PIN0 | GPIO_PERIPHERAL | \
                            PFS_PSEL_SCI1_3_5_7_9 | \
                            GPIO_OPENDRAIN | GPIO_PULLUP)

#define GPIO_SCI1_I2C_SCL  (PORT4 | PIN1 | GPIO_PERIPHERAL | \
                            PFS_PSEL_SCI1_3_5_7_9 | \
                            GPIO_OPENDRAIN | GPIO_PULLUP)

/* SCI0 I2C Mode (if needed):
 *   - SDA: P102 (TXD0_A) or other available TXD0 pin
 *   - SCL: P103 (RXD0_A) or other available RXD0 pin
 */

#define GPIO_SCI0_I2C_SDA  (PORT1 | PIN2 | GPIO_PERIPHERAL | \
                            PFS_PSEL_SCI0_2_4_6_8 | \
                            GPIO_OPENDRAIN | GPIO_PULLUP)

#define GPIO_SCI0_I2C_SCL  (PORT1 | PIN3 | GPIO_PERIPHERAL | \
                            PFS_PSEL_SCI0_2_4_6_8 | \
                            GPIO_OPENDRAIN | GPIO_PULLUP)

/****************************************************************************
 * Private Data
 ****************************************************************************/

#ifdef CONFIG_RA_SCI0_I2C
static struct i2c_master_s *g_sci_i2c0_dev = NULL;
#endif

#ifdef CONFIG_RA_SCI1_I2C
static struct i2c_master_s *g_sci_i2c1_dev = NULL;
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_sci_i2c_initialize
 *
 * Description:
 *   Initialize SCI I2C bus for EVK-RA8P1 board.
 *   This uses SCI peripheral in Simple I2C mode (not hardware IIC).
 *
 * Input Parameters:
 *   bus - SCI channel number configured for I2C (0-9)
 *
 * Returned Value:
 *   Pointer to I2C device structure on success; NULL on failure
 *
 ****************************************************************************/

struct i2c_master_s *board_sci_i2c_initialize(int bus)
{
  struct i2c_master_s *dev = NULL;

  i2cinfo("Initializing SCI%d I2C\n", bus);

  switch (bus)
    {
#ifdef CONFIG_RA_SCI0_I2C
      case 0:
        /* Initialize SCI0 in Simple I2C mode
         * Pins: P102 (SDA), P103 (SCL) - or alternate pins
         */

        if (g_sci_i2c0_dev == NULL)
          {
            /* Configure GPIO pins for SCI0 I2C
             * Both SDA and SCL need:
             * - Peripheral mode
             * - Open-drain output
             * - Pull-up enabled (or use external pull-ups)
             */

            ra_gpioconfig(GPIO_SCI0_I2C_SDA);
            ra_gpioconfig(GPIO_SCI0_I2C_SCL);

            g_sci_i2c0_dev = ra_sci_i2cbus_initialize(0);
            if (g_sci_i2c0_dev == NULL)
              {
                i2cerr("ERROR: Failed to initialize SCI0 I2C\n");
                return NULL;
              }

            i2cinfo("SCI0 I2C initialized successfully\n");
          }

        dev = g_sci_i2c0_dev;
        break;
#endif

#ifdef CONFIG_RA_SCI1_I2C
      case 1:
        /* Initialize SCI1 in Simple I2C mode
         * Pins: P400 (SDA), P401 (SCL)
         */

        if (g_sci_i2c1_dev == NULL)
          {
            /* Configure GPIO pins for SCI1 I2C
             * Both SDA and SCL need:
             * - Peripheral mode
             * - Open-drain output
             * - Pull-up enabled (or use external pull-ups)
             */

            ra_gpioconfig(GPIO_SCI1_I2C_SDA);
            ra_gpioconfig(GPIO_SCI1_I2C_SCL);

            g_sci_i2c1_dev = ra_sci_i2cbus_initialize(1);
            if (g_sci_i2c1_dev == NULL)
              {
                i2cerr("ERROR: Failed to initialize SCI1 I2C\n");
                return NULL;
              }

            i2cinfo("SCI1 I2C initialized successfully\n");
          }

        dev = g_sci_i2c1_dev;
        break;
#endif

      default:
        i2cerr("ERROR: Invalid SCI I2C bus: %d\n", bus);
        return NULL;
    }

  return dev;
}

/****************************************************************************
 * Name: board_sci_i2c_uninitialize
 *
 * Description:
 *   Uninitialize SCI I2C bus
 *
 * Input Parameters:
 *   bus - SCI channel number
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure
 *
 ****************************************************************************/

int board_sci_i2c_uninitialize(int bus)
{
  struct i2c_master_s *dev = NULL;
  int ret = OK;

  i2cinfo("Uninitializing SCI%d I2C\n", bus);

  switch (bus)
    {
#ifdef CONFIG_RA_SCI0_I2C
      case 0:
        dev = g_sci_i2c0_dev;
        g_sci_i2c0_dev = NULL;
        break;
#endif

#ifdef CONFIG_RA_SCI1_I2C
      case 1:
        dev = g_sci_i2c1_dev;
        g_sci_i2c1_dev = NULL;
        break;
#endif

      default:
        i2cerr("ERROR: Invalid SCI I2C bus: %d\n", bus);
        return -EINVAL;
    }

  if (dev != NULL)
    {
      ret = ra_sci_i2cbus_uninitialize(dev);
      if (ret < 0)
        {
          i2cerr("ERROR: Failed to uninitialize SCI%d I2C: %d\n", bus, ret);
        }
    }

  return ret;
}
