/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_sci_i2c.c
 *
 * Board-level bringup wrapper for SCI-B Simple-I2C master driver.
 * Calls rzv_sci_i2c_initialize() for each Kconfig-enabled SCI I2C channel
 * and registers the resulting i2c_master_s with the NuttX I2C framework.
 *
 * Bus numbering: SCI0→10, SCI1→11, SCI2→12, SCI3→13
 * (RIIC buses 0..2 already taken; 10+ avoids collisions)
 *
 * Audit: Phase 04 — board glue / defconfig / smoke
 * Ref: boards/arm/rzv/rdk-rzv2h/src/rzv2h_bringup.c (RIIC pattern)
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
#include <syslog.h>

#include <nuttx/i2c/i2c_master.h>

#include "rzv_sci_i2c.h"
#include "rzv2h_sci_i2c.h"

/****************************************************************************
 * Private Macros
 ****************************************************************************/

/* Register one SCI channel as I2C, log result, return on fatal error */

#define SETUP_CHANNEL(ch) \
  do { \
    struct i2c_master_s *dev_ = rzv_sci_i2c_initialize(ch); \
    if (dev_ == NULL) \
      { \
        syslog(LOG_ERR, "ERROR: SCI%d I2C init failed\n", (ch)); \
        return -ENODEV; \
      } \
    int ret_ = i2c_register(dev_, BOARD_SCI_I2C_BUS_BASE + (ch)); \
    if (ret_ < 0) \
      { \
        syslog(LOG_ERR, "ERROR: SCI%d I2C register failed: %d\n", \
               (ch), ret_); \
        return ret_; \
      } \
    syslog(LOG_INFO, "SCI%d I2C initialized (bus %d)\n", \
           (ch), BOARD_SCI_I2C_BUS_BASE + (ch)); \
  } while (0)

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv2h_sci_i2c_setup
 *
 * Description:
 *   Initialize all SCI-I2C master channels enabled by Kconfig and register
 *   them with the NuttX I2C driver framework. Called from rzv2h_bringup.c.
 *
 *   Pin configuration is handled inside rzv_sci_i2c_initialize() via the
 *   BOARD_SCIn_I2C_SDA_GPIO / BOARD_SCIn_I2C_SCL_GPIO macros from board.h.
 *
 *   Schematic note (audit dim 15): RDK-RZV2H GY-912 connector routes to
 *   RIIC2, NOT to any SCI channel. The sci-i2c-gy912 defconfig therefore
 *   exercises SCI3 as a synthetic smoke target (no slave expected on bus);
 *   i2c_probe will return empty or -ENXIO, which is acceptable.
 *
 * Returned Value:
 *   0 on success; negative errno on first channel failure.
 *
 ****************************************************************************/

int rzv2h_sci_i2c_setup(void)
{
#ifdef CONFIG_RZV_SCI0_I2C
  SETUP_CHANNEL(0);
#endif

#ifdef CONFIG_RZV_SCI1_I2C
  SETUP_CHANNEL(1);
#endif

#ifdef CONFIG_RZV_SCI2_I2C
  SETUP_CHANNEL(2);
#endif

#ifdef CONFIG_RZV_SCI3_I2C
  SETUP_CHANNEL(3);
#endif

  return OK;
}
