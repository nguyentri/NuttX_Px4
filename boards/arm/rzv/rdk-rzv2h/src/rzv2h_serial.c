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
 *   SCI1 is used as the default NSH console interface.
 *
 ****************************************************************************/

void rzv2h_serial_setup(void)
{
#if defined(CONFIG_RZV_SCI0)
  /* Configure SCI0 pins for UART operation (RC input)
   * SCI0_TXD: P5_0 (Mode 1)
   * SCI0_RXD: P5_1 (Mode 1)
   */

  sinfo("Configuring SCI0 pins for UART (RC input)\n");

  rzv_gpioconfig(BOARD_SCI0_TXD_GPIO);
  rzv_gpioconfig(BOARD_SCI0_RXD_GPIO);

  sinfo("SCI0 UART pins configured\n");
#endif

#if defined(CONFIG_RZV_SCI1) || defined(CONFIG_SCI1_SERIAL_CONSOLE)
  /* Configure SCI1 pins for UART operation (MAVLink)
   * SCI1_TXD: P5_2 (Mode 1)
   * SCI1_RXD: P5_3 (Mode 1)
   */

  sinfo("Configuring SCI1 pins for UART (MAVLink)\n");

  rzv_gpioconfig(BOARD_SCI1_TXD_GPIO);
  rzv_gpioconfig(BOARD_SCI1_RXD_GPIO);

  sinfo("SCI1 UART pins configured\n");
#endif

#if defined(CONFIG_RZV_SCI2)
  /* Configure SCI2 pins for UART operation (GPS)
   * SCI2_TXD: P5_4 (Mode 1)
   * SCI2_RXD: P5_5 (Mode 1)
   */

  sinfo("Configuring SCI2 pins for UART (GPS)\n");

  rzv_gpioconfig(BOARD_SCI2_TXD_GPIO);
  rzv_gpioconfig(BOARD_SCI2_RXD_GPIO);

  sinfo("SCI2 UART pins configured\n");
#endif

#if defined(CONFIG_RZV_SCI3) || defined(CONFIG_SCI3_SERIAL_CONSOLE)
  /* Configure SCI3 pins for UART operation (NSH Console)
   * SCI3_TXD: P5_6 (Mode 1)
   * SCI3_RXD: P5_7 (Mode 1)
   */

  sinfo("Configuring SCI3 pins for UART (NSH Console)\n");

  rzv_gpioconfig(BOARD_SCI3_TXD_GPIO);
  rzv_gpioconfig(BOARD_SCI3_RXD_GPIO);

  sinfo("SCI3 UART pins configured\n");
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
