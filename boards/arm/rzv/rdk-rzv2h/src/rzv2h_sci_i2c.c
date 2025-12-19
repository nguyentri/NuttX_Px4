/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_sci_i2c.c
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

#include <nuttx/i2c/i2c_master.h>
#include <arch/board/board.h>

#include "arm_internal.h"
#include "rzv_gpio.h"
#include "rzv_sci_i2c.h"

#ifdef CONFIG_RZV_SCI_I2C

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv2h_sci_i2c_configure_pins
 *
 * Description:
 *   Configure GPIO pins for SCI I2C operation
 *
 ****************************************************************************/

static void rzv2h_sci_i2c_configure_pins(int channel)
{
  switch (channel)
    {
#ifdef CONFIG_RZV_SCI0_I2C
    case 0:
      /* Configure SCI0 pins for I2C mode (SDA/SCL) */
      rzv_gpioconfig(BOARD_SCI0_SDA_GPIO);
      rzv_gpioconfig(BOARD_SCI0_SCL_GPIO);
      i2cinfo("Configured SCI0 I2C pins\n");
      break;
#endif

#ifdef CONFIG_RZV_SCI1_I2C
    case 1:
      /* Configure SCI1 pins for I2C mode (SDA/SCL) */
      rzv_gpioconfig(BOARD_SCI1_SDA_GPIO);
      rzv_gpioconfig(BOARD_SCI1_SCL_GPIO);
      i2cinfo("Configured SCI1 I2C pins\n");
      break;
#endif

#ifdef CONFIG_RZV_SCI2_I2C
    case 2:
      /* Configure SCI2 pins for I2C mode (SDA/SCL) */
      rzv_gpioconfig(BOARD_SCI2_SDA_GPIO);
      rzv_gpioconfig(BOARD_SCI2_SCL_GPIO);
      i2cinfo("Configured SCI2 I2C pins\n");
      break;
#endif

#ifdef CONFIG_RZV_SCI3_I2C
    case 3:
      /* Configure SCI3 pins for I2C mode (SDA/SCL) */
      rzv_gpioconfig(BOARD_SCI3_SDA_GPIO);
      rzv_gpioconfig(BOARD_SCI3_SCL_GPIO);
      i2cinfo("Configured SCI3 I2C pins\n");
      break;
#endif

    default:
      i2cerr("ERROR: Invalid SCI I2C channel %d\n", channel);
      break;
    }
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_sci_i2c_initialize
 *
 * Description:
 *   Initialize and register the SCI I2C bus for the specified channel
 *
 * Input Parameters:
 *   channel - SCI channel number (0-3)
 *
 * Returned Value:
 *   Pointer to the I2C master device structure on success; NULL on failure
 *
 ****************************************************************************/

struct i2c_master_s *board_sci_i2c_initialize(int channel)
{
  struct i2c_master_s *i2c;

  i2cinfo("Initializing SCI%d I2C\n", channel);

  /* Configure GPIO pins for I2C */

  rzv2h_sci_i2c_configure_pins(channel);

  /* Initialize the SCI I2C driver */

  i2c = rzv_sci_i2c_initialize(channel);
  if (i2c == NULL)
    {
      i2cerr("ERROR: Failed to initialize SCI%d I2C\n", channel);
      return NULL;
    }

  i2cinfo("SCI%d I2C initialized successfully\n", channel);

  return i2c;
}

/****************************************************************************
 * Name: rzv2h_sci_i2c_initialize
 *
 * Description:
 *   Initialize all configured SCI I2C buses
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

int rzv2h_sci_i2c_initialize(void)
{
  int ret = OK;

  i2cinfo("Initializing SCI I2C buses\n");

#ifdef CONFIG_RZV_SCI0_I2C
  if (board_sci_i2c_initialize(0) == NULL)
    {
      i2cerr("ERROR: Failed to initialize SCI0 I2C\n");
      ret = -ENODEV;
    }
#endif

#ifdef CONFIG_RZV_SCI1_I2C
  if (board_sci_i2c_initialize(1) == NULL)
    {
      i2cerr("ERROR: Failed to initialize SCI1 I2C\n");
      ret = -ENODEV;
    }
#endif

#ifdef CONFIG_RZV_SCI2_I2C
  if (board_sci_i2c_initialize(2) == NULL)
    {
      i2cerr("ERROR: Failed to initialize SCI2 I2C\n");
      ret = -ENODEV;
    }
#endif

#ifdef CONFIG_RZV_SCI3_I2C
  if (board_sci_i2c_initialize(3) == NULL)
    {
      i2cerr("ERROR: Failed to initialize SCI3 I2C\n");
      ret = -ENODEV;
    }
#endif

  return ret;
}

#endif /* CONFIG_RZV_SCI_I2C */
