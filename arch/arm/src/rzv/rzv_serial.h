/****************************************************************************
 * arch/arm/src/rzv/rzv_serial.h
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

#ifndef __ARCH_ARM_SRC_RZV_RZV_SERIAL_H
#define __ARCH_ARM_SRC_RZV_RZV_SERIAL_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SCI channel identifiers */

#define RZV_SCI_CHANNEL_0    0
#define RZV_SCI_CHANNEL_1    1
#define RZV_SCI_CHANNEL_2    2
#define RZV_SCI_CHANNEL_3    3
#define RZV_SCI_CHANNEL_4    4
#define RZV_SCI_CHANNEL_5    5
#define RZV_SCI_CHANNEL_6    6
#define RZV_SCI_CHANNEL_7    7
#define RZV_SCI_CHANNEL_8    8
#define RZV_SCI_CHANNEL_9    9

/* Maximum number of SCI channels */

#define RZV_SCI_MAX_CHANNELS 10

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* SCI parity configuration */

enum rzv_sci_parity_e
{
  RZV_SCI_PARITY_NONE = 0,   /* No parity */
  RZV_SCI_PARITY_ODD  = 1,   /* Odd parity */
  RZV_SCI_PARITY_EVEN = 2    /* Even parity */
};

/* SCI data bits configuration */

enum rzv_sci_databits_e
{
  RZV_SCI_DATABITS_7 = 7,    /* 7 data bits */
  RZV_SCI_DATABITS_8 = 8,    /* 8 data bits */
  RZV_SCI_DATABITS_9 = 9     /* 9 data bits */
};

/* SCI stop bits configuration */

enum rzv_sci_stopbits_e
{
  RZV_SCI_STOPBITS_1 = 0,    /* 1 stop bit */
  RZV_SCI_STOPBITS_2 = 1     /* 2 stop bits */
};

/****************************************************************************
 * Public Data
 ****************************************************************************/

#ifndef __ASSEMBLY__
#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: rzv2h_serial_setup
 *
 * Description:
 *   Board-specific SCI/UART pin configuration.
 *   This function should be called early during board initialization
 *   to configure the GPIO pins for UART operation.
 *
 ****************************************************************************/

void rzv2h_serial_setup(void);

/****************************************************************************
 * Name: rzv2h_serial_register
 *
 * Description:
 *   Board-specific SCI/UART device registration.
 *   Called after serial driver initialization for any board-specific
 *   setup requirements.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int rzv2h_serial_register(void);

#ifdef __cplusplus
}
#endif
#endif /* __ASSEMBLY__ */

#endif /* __ARCH_ARM_SRC_RZV_RZV_SERIAL_H */
