/****************************************************************************
 * arch/arm/src/rzv/rzv_riic.h
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

#ifndef __ARCH_ARM_SRC_RZV_RIIC_H
#define __ARCH_ARM_SRC_RZV_RIIC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/i2c/i2c_master.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* RIIC Port Numbers */

#define RZV_RIIC0                  0
#define RZV_RIIC1                  1
#define RZV_RIIC2                  2
#define RZV_RIIC3                  3

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

#ifndef __ASSEMBLY__

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_riic_initialize
 *
 * Description:
 *   Initialize the selected RIIC port. And return a unique instance of struct
 *   i2c_master_s. This function may be called to obtain multiple instances
 *   of the interface, each of which may be set up with a different frequency
 *   and slave address.
 *
 * Input Parameters:
 *   port - Port number (0-3)
 *
 * Returned Value:
 *   Valid I2C device structure reference on success; a NULL on failure
 *
 ****************************************************************************/

struct i2c_master_s *rzv_riic_initialize(int port);

/****************************************************************************
 * Name: rzv_riic_uninitialize
 *
 * Description:
 *   De-initialize the selected RIIC port, and power down the device.
 *
 * Input Parameters:
 *   dev - Device structure as returned by rzv_riic_initialize()
 *
 * Returned Value:
 *   OK on success, ERROR when internal reference count mismatch or dev
 *   points to invalid hardware device.
 *
 ****************************************************************************/

int rzv_riic_uninitialize(struct i2c_master_s *dev);

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_RZV_RIIC_H */
