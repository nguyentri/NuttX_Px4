/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_serial.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache Software Foundation (ASF)
 * under one or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information regarding copyright
 * ownership.  The ASF licenses this file to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of the License at
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

#include <nuttx/serial/serial.h>

#include <arch/board/board.h>

#include "rzv_gpio.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv2h_serial_setup
 *
 * Description:
 *   Configure SCI pins for UART operation on the RDK-RZV2H board.
 *   This function is called early during board initialization to set up
 *   the UART pins before the serial driver is initialized.
 *
 *   The PX4 RDK-RZV2H port uses sparse SCI numbering so each channel keeps
 *   its hardware-aligned /dev/ttySN name.
 *
 ****************************************************************************/

void rzv2h_serial_setup(void)
{
#if defined(CONFIG_RZV_SCI3) || defined(CONFIG_SCI3_SERIAL_CONSOLE)
  /* SCI3: NSH console on P3_4/P3_5 per RDK pinconfig.
   * Pinmap SCI macros encode only PORT|PIN|PSEL; RZV_GPIO_PERIPH must be
   * OR'ed in or rzv_gpioconfig() treats the pin as a plain GPIO input and
   * never programs PMC/PFC (UART pins would stay unmuxed).
   */

  sinfo("Configuring SCI3 pins for UART (NSH Console)\n");

  rzv_gpioconfig(BOARD_SCI3_TXD_GPIO | RZV_GPIO_PERIPH);
  rzv_gpioconfig(BOARD_SCI3_RXD_GPIO | RZV_GPIO_PERIPH);

  sinfo("SCI3 UART pins configured\n");
#endif

#if defined(CONFIG_RZV_SCI4)
  /* SCI4: TFminiPlus on P7_0/P7_1. */

  sinfo("Configuring SCI4 pins for UART (TFminiPlus)\n");

  rzv_gpioconfig(BOARD_P7_0_GPIO | RZV_GPIO_PERIPH);
  rzv_gpioconfig(BOARD_P7_1_GPIO | RZV_GPIO_PERIPH);

  sinfo("SCI4 UART pins configured\n");
#endif

#if defined(CONFIG_RZV_SCI5)
  /* SCI5: MAVLink telemetry on P7_2/P7_3. */

  sinfo("Configuring SCI5 pins for UART (MAVLink)\n");

  rzv_gpioconfig(BOARD_P7_2_GPIO | RZV_GPIO_PERIPH);
  rzv_gpioconfig(BOARD_P7_3_GPIO | RZV_GPIO_PERIPH);

  sinfo("SCI5 UART pins configured\n");
#endif

#if defined(CONFIG_RZV_SCI6)
  /* SCI6: SBUS RC input uses RX only on P7_5. */

  sinfo("Configuring SCI6 RX pin for UART (RC input)\n");

  rzv_gpioconfig(BOARD_P7_5_GPIO | RZV_GPIO_PERIPH);

  sinfo("SCI6 UART RX pin configured\n");
#endif

#if defined(CONFIG_RZV_SCI9)
  /* SCI9: GPS M10 on P8_2/P8_3. */

  sinfo("Configuring SCI9 pins for UART (GPS)\n");

  rzv_gpioconfig(BOARD_P8_2_GPIO | RZV_GPIO_PERIPH);
  rzv_gpioconfig(BOARD_P8_3_GPIO | RZV_GPIO_PERIPH);

  sinfo("SCI9 UART pins configured\n");
#endif
}

/****************************************************************************
 * Name: rzv2h_serial_register
 *
 * Description:
 *   Register SCI serial devices. This function is typically called
 *   from the board-specific bringup logic.
 *
 ****************************************************************************/

int rzv2h_serial_register(void)
{
  /* Serial driver registration is handled by arm_serialinit()
   * which is called from up_initialize().
   * This function can be used for any board-specific serial setup
   * that needs to happen after the serial driver is initialized.
   */

  return OK;
}
