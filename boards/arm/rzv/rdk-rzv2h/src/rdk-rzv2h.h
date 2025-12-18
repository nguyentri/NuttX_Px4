/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rdk-rzv2h.h
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

#ifndef __BOARDS_ARM_RZV_RDK_RZV2H_SRC_H
#define __BOARDS_ARM_RZV_RDK_RZV2H_SRC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdint.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* Forward declarations */
struct spi_dev_s;

/****************************************************************************
 * Public Data
 ****************************************************************************/

#ifndef __ASSEMBLY__

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: rzv2h_bringup
 *
 * Description:
 *   Perform architecture-specific initialization
 *
 *   CONFIG_BOARD_LATE_INITIALIZE=y :
 *     Called from board_late_initialize().
 *
 *   CONFIG_BOARD_LATE_INITIALIZE=n && CONFIG_BOARDCTL=y :
 *     Called from the NSH library
 *
 ****************************************************************************/

int rzv2h_bringup(void);

/****************************************************************************
 * Name: rzv2h_led_initialize
 *
 * Description:
 *   Initialize LEDs
 *
 ****************************************************************************/

void rzv2h_led_initialize(void);

/****************************************************************************
 * Name: rzv2h_button_initialize
 *
 * Description:
 *   Initialize buttons
 *
 ****************************************************************************/

void rzv2h_button_initialize(void);

/****************************************************************************
 * Name: rzv2h_pwm_setup
 *
 * Description:
 *   Configure the GPT channel routed to the EVK PWM test point and register
 *   the lower-half driver with the NuttX PWM subsystem.
 *
 ****************************************************************************/

#ifdef CONFIG_RZV_GPT_PWM
int rzv2h_pwm_setup(void);
#endif

/****************************************************************************
 * Name: rzv2h_serial_setup
 *
 * Description:
 *   Configure SCI/UART pins for serial communication
 *
 ****************************************************************************/

#ifdef CONFIG_RZV_UART_SCI
void rzv2h_serial_setup(void);
#endif

/****************************************************************************
 * Name: rzv2h_serial_register
 *
 * Description:
 *   Register SCI/UART devices
 *
 ****************************************************************************/

#ifdef CONFIG_RZV_UART_SCI
int rzv2h_serial_register(void);
#endif

#endif /* __ASSEMBLY__ */
#endif /* __BOARDS_ARM_RZV_RDK_RZV2H_SRC_H */