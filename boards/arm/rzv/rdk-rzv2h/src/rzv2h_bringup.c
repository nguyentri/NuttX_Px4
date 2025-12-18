/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_bringup.c
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

#include <sys/mount.h>
#include <stdbool.h>
#include <stddef.h>
#include <syslog.h>
#include <debug.h>
#include <errno.h>

#include <nuttx/board.h>
#include <nuttx/fs/fs.h>
#include <nuttx/leds/userled.h>
#include <nuttx/timers/pwm.h>

#include <arch/board/board.h>
#include "arm_internal.h"
#include "rdk-rzv2h.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#undef HAVE_LEDS

#if !defined(CONFIG_ARCH_LEDS) && defined(CONFIG_USERLED_LOWER)
#  define HAVE_LEDS 1
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_bringup
 *
 * Description:
 *   Perform architecture-specific initialization
 *
 *   CONFIG_BOARD_LATE_INITIALIZE=y :
 *     Called from board_late_initialize().
 *
 *   CONFIG_BOARD_LATE_INITIALIZE=y && CONFIG_BOARDCTL=y :
 *     Called from the NSH library
 *
 ****************************************************************************/

int board_bringup(void)
{
  int ret = 0;

  syslog(LOG_INFO, "NuttX: RDK-RZV2H Board bring-up starting...\n");

#ifdef CONFIG_FS_PROCFS
  /* Mount the procfs file system */

  ret = nx_mount(NULL, "/proc", "procfs", 0, NULL);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to mount procfs at /proc: %d\n", ret);
    }
  else
    {
      syslog(LOG_INFO, "Mounted procfs at /proc\n");
    }
#endif

#ifdef HAVE_LEDS
  /* Initialize LED support */

  board_userled_initialize();

  /* Register the LED driver */

  ret = userled_lower_initialize(LED_DRIVER_PATH);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: userled_lower_initialize() failed: %d\n", ret);
    }
  else
    {
      syslog(LOG_INFO, "LED driver initialized successfully\n");
    }
#endif

#ifdef CONFIG_ARCH_BUTTONS
  /* Initialize buttons */

  board_button_initialize();
  syslog(LOG_INFO, "Buttons initialized\n");
#endif

#if defined(CONFIG_RZV_RIIC0) || defined(CONFIG_RZV_RIIC1) || defined(CONFIG_RZV_RIIC2)
  /* Initialize I2C buses */

#ifdef CONFIG_RZV_RIIC0
  if (board_i2c_initialize(0) != NULL)
    {
      syslog(LOG_INFO, "I2C0 (RIIC0) initialized successfully\n");
    }
  else
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize I2C0\n");
    }
#endif

#ifdef CONFIG_RZV_RIIC1
  if (board_i2c_initialize(1) != NULL)
    {
      syslog(LOG_INFO, "I2C1 (RIIC1) initialized successfully\n");
    }
  else
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize I2C1\n");
    }
#endif

#ifdef CONFIG_RZV_RIIC2
  if (board_i2c_initialize(2) != NULL)
    {
      syslog(LOG_INFO, "I2C2 (RIIC2) initialized successfully\n");
    }
  else
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize I2C2\n");
    }
#endif
#endif

#ifdef CONFIG_RZV_SPI
  /* Initialize SPI buses */

  ret = board_spi_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize SPI: %d\n", ret);
    }
  else
    {
      syslog(LOG_INFO, "SPI initialized successfully\n");
    }
#endif

#ifdef CONFIG_RZV_ADC
  /* Initialize ADC module */

  ret = board_adc_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize ADC: %d\n", ret);
    }
  else
    {
      syslog(LOG_INFO, "ADC initialized successfully\n");
    }
#endif

#ifdef CONFIG_PWM
  /* Initialize GPT PWM devices */

  ret = board_pwm_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize GPT PWM: %d\n", ret);
    }
  else
    {
      syslog(LOG_INFO, "GPT PWM devices initialized successfully\n");
    }
#endif

#ifdef CONFIG_RZV2H_EXAMPLE_SUPPORT
  /* Run application examples */

  rzv2h_app_examples();
#endif

  syslog(LOG_INFO, "NuttX: RDK-RZV2H Board bring-up complete\n");
  return ret;
}

/****************************************************************************
 * Name: board_late_initialize
 *
 * Description:
 *   If CONFIG_BOARD_LATE_INITIALIZE is selected, then an additional
 *   initialization call will be performed in the boot-up sequence to a
 *   function called board_late_initialize().  board_late_initialize() will
 *   be called immediately after up_initialize() is called and just before
 *   the initial application is started.  This additional initialization
 *   phase may be used, for example, to initialize board-specific device
 *   drivers.
 *
 ****************************************************************************/

#ifdef CONFIG_BOARD_LATE_INITIALIZE
void board_late_initialize(void)
{
  /* Perform board-specific initialization */

  board_bringup();
}
#endif