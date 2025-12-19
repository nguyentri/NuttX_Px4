/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_sci_i2c.h
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
#include <nuttx/i2c/i2c_master.h>

/****************************************************************************
 * Public Function Prototypes
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

struct i2c_master_s *board_sci_i2c_initialize(int channel);

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

int rzv2h_sci_i2c_initialize(void);

#endif /* __BOARDS_ARM_RZV_RDK_RZV2H_SRC_RZV2H_SCI_I2C_H */
