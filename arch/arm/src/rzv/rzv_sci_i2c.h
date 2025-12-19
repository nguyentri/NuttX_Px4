/****************************************************************************
 * arch/arm/src/rzv/rzv_sci_i2c.h
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

#ifndef __ARCH_ARM_SRC_RZV_RZV_SCI_I2C_H
#define __ARCH_ARM_SRC_RZV_RZV_SCI_I2C_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/i2c/i2c_master.h>

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Name: rzv_sci_i2c_initialize
 *
 * Description:
 *   Initialize one SCI I2C port (Simple I2C mode using SCI peripheral).
 *   This provides a simpler I2C implementation compared to the dedicated
 *   RIIC peripheral, sharing hardware with UART functionality.
 *
 * Input Parameters:
 *   port - SCI channel number (0-3)
 *
 * Returned Value:
 *   Valid I2C device structure pointer on success; NULL on failure
 *
 ****************************************************************************/

struct i2c_master_s *rzv_sci_i2c_initialize(int port);

/****************************************************************************
 * Name: rzv_sci_i2c_uninitialize
 *
 * Description:
 *   Uninitialize an SCI I2C port
 *
 * Input Parameters:
 *   dev - Device structure as returned by rzv_sci_i2c_initialize()
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

int rzv_sci_i2c_uninitialize(struct i2c_master_s *dev);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RZV_RZV_SCI_I2C_H */
