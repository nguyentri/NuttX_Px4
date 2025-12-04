/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_bringup.c
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

#include <syslog.h>
#include <debug.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <errno.h>

#include <nuttx/board.h>
#include <nuttx/fs/fs.h>
#include <nuttx/leds/userled.h>
#include <nuttx/timers/pwm.h>

#include <arch/board/board.h>
#include "arm_internal.h"
#include "evk-ra8p1.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
#undef HAVE_LEDS

#if !defined(CONFIG_ARCH_LEDS) && defined(CONFIG_USERLED_LOWER)
#  define HAVE_LEDS 1
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra8p1_bringup
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

int ra8p1_bringup(void)
{
  int ret = 0;

  syslog(LOG_INFO, "Nuttx: RA8P1 Board bring-up starting...\n");

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

  /* Configure all GPIO pins */
  ra8p1_gpio_initialize();

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
#endif

#ifdef CONFIG_RTC_DRIVER
  /* Initialize RTC driver */
  ret = board_rtc_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize RTC: %d\n", ret);
    }
  else
    {
      syslog(LOG_INFO, "RTC initialized successfully\n");
    }
#endif

#if defined(CONFIG_RA_I2C0) || defined(CONFIG_RA_I2C1)
  /* Initialize I2C buses */
#ifdef CONFIG_RA_I2C0
  if (board_i2c_initialize(0) != NULL)
    {
      syslog(LOG_INFO, "I2C0 initialized successfully\n");
    }
  else
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize I2C0\n");
    }
#endif

#ifdef CONFIG_RA_I2C1
  if (board_i2c_initialize(1) != NULL)
    {
      syslog(LOG_INFO, "I2C1 initialized successfully\n");
    }
  else
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize I2C1\n");
    }
#endif
#endif

#ifdef CONFIG_RA_ADC
  /* Initialize ADC-B module */
  ret = board_adc_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize ADC: %d\n", ret);
    }
  else
    {
      syslog(LOG_INFO, "ADC-B initialized successfully\n");
    }
#endif

#ifdef CONFIG_PWM
  /* Initialize GPT PWM devices */
  ret = board_gpt_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize GPT PWM: %d\n", ret);
    }
  else
    {
      syslog(LOG_INFO, "GPT PWM devices initialized successfully\n");
    }
#endif

#ifdef CONFIG_RA_MRAM
  /* Initialize MRAM storage for OTA/bootloader and parameter storage */

  ret = board_mram_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize MRAM: %d\n", ret);
    }
  else
    {
      syslog(LOG_INFO, "MRAM storage initialized successfully\n");
    }
#endif

#ifdef CONFIG_RA_CANFD
  /* Initialize CAN-FD interfaces */

  ret = board_canfd_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize CAN-FD: %d\n", ret);
    }
  else
    {
      syslog(LOG_INFO, "CAN-FD initialized successfully\n");
    }
#endif

#ifdef CONFIG_RA_OSPI
  /* Initialize OSPI interface */

  ret = board_ospi_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize OSPI: %d\n", ret);
    }
  else
    {
      syslog(LOG_INFO, "OSPI initialized successfully\n");
    }
#endif

#ifdef CONFIG_RA_MIPI_CSI
  /* Initialize MIPI-CSI Camera */
  extern int board_mipi_csi_initialize(void);
  ret = board_mipi_csi_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize MIPI-CSI: %d\n", ret);
    }
  else
    {
      syslog(LOG_INFO, "MIPI-CSI initialized successfully\n");
    }
#endif

  ra8p1_app_examples();

  return ret;
}
