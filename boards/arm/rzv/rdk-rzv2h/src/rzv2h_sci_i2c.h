/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_sci_i2c.h
 *
 * Board-level glue for SCI-B Simple-I2C master driver.
 * Calls rzv_sci_i2c_initialize() then i2c_register() for each enabled
 * SCI channel configured as I2C in Kconfig.
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

#ifndef __BOARDS_ARM_RZV_RDK_RZV2H_SRC_RZV2H_SCI_I2C_H
#define __BOARDS_ARM_RZV_RDK_RZV2H_SRC_RZV2H_SCI_I2C_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Bus numbers for SCI-I2C channels.
 * RIIC buses occupy 0..2; SCI-I2C buses start at 10 to avoid collisions.
 */

#define BOARD_SCI_I2C_BUS_BASE  10  /* SCI0→bus10, SCI1→bus11, SCI2→bus12, SCI3→bus13 */

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef CONFIG_RZV_SCI_I2C

/****************************************************************************
 * Name: rzv2h_sci_i2c_setup
 *
 * Description:
 *   Initialise all SCI channels configured as I2C master and register them
 *   with the NuttX I2C framework. Called from rzv2h_bringup.c.
 *
 * Returned Value:
 *   0 on success; negative errno if any channel fails to initialise.
 *
 ****************************************************************************/

int rzv2h_sci_i2c_setup(void);

#endif /* CONFIG_RZV_SCI_I2C */

#endif /* __BOARDS_ARM_RZV_RDK_RZV2H_SRC_RZV2H_SCI_I2C_H */
