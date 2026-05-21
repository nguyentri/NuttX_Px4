/****************************************************************************
 * arch/arm/src/ra8/ra_i3c.h
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

#ifndef __ARCH_ARM_SRC_RA_RA8_I3C_H
#define __ARCH_ARM_SRC_RA_RA8_I3C_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* I3C transfer message structure */

struct i3c_msg_s
{
  uint16_t addr;          /* I3C device address */
  uint16_t flags;         /* Message flags */
#define I3C_M_READ    0x0001  /* Read data from device */
#define I3C_M_NOSTOP  0x0040  /* Do not send stop after this message */
  uint8_t *buffer;        /* Buffer for data */
  ssize_t length;         /* Length of buffer */
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: ra_i3cbus_initialize
 *
 * Description:
 *   Initialize the selected I3C port and register as a character device.
 *
 * Input Parameters:
 *   Port number (for hardware that has multiple I3C interfaces)
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure
 *
 ****************************************************************************/

int ra_i3cbus_initialize(int port);

/****************************************************************************
 * Name: ra_i3cbus_uninitialize
 *
 * Description:
 *   De-initialize the selected I3C port, and power down the device.
 *
 * Input Parameters:
 *   Port number
 *
 * Returned Value:
 *   OK on success, ERROR when internal reference count mismatch
 *
 ****************************************************************************/

int ra_i3cbus_uninitialize(int port);

/****************************************************************************
 * Name: ra_i3cbus_transfer
 *
 * Description:
 *   Perform a sequence of I3C messages on the selected I3C port.
 *
 * Input Parameters:
 *   port - I3C port number
 *   msgs - Array of I3C messages
 *   count - Number of messages in the array
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure
 *
 ****************************************************************************/

int ra_i3cbus_transfer(int port, struct i3c_msg_s *msgs, int count);

#endif /* __ARCH_ARM_SRC_RA_RA8_I3C_H */
