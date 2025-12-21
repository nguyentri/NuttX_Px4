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
#  define LED_DRIVER_PATH "/dev/userleds"
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

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
  board_gpio_initialize();

#ifdef CONFIG_RA_WDT
  board_wdt_initialize();
#endif

#ifdef CONFIG_RA_IWDT
  board_iwdt_initialize();
#endif

#ifdef CONFIG_RA_IPC
  /* Initialize Inter-Processor Communication */

  ret = board_ipc_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize IPC: %d\n", ret);
    }
  else
    {
      syslog(LOG_INFO, "IPC initialized successfully\n");
    }
#endif

#ifdef CONFIG_RA_SCI_SPI
  ret = board_sci_spi_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize SCI SPI: %d\n", ret);
    }
#endif

#ifdef CONFIG_RA_I3C
  ret = board_i3c_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize I3C\n");
    }
#endif

#ifdef CONFIG_RA_SDRAM
  /* Initialize external SDRAM
   * Note: SDRAM should be initialized early as it may be used for heap
   */

  ret = board_sdram_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize SDRAM: %d\n", ret);
    }
  else
    {
      syslog(LOG_INFO, "SDRAM initialized successfully\n");
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

#ifdef CONFIG_RA_ELC
  /* Initialize Event Link Controller
   * Note: ELC should be initialized after GPT and ADC modules
   * so that event links can be established properly
   */

  ret = board_elc_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize ELC: %d\n", ret);
    }
  else
    {
      syslog(LOG_INFO, "ELC initialized successfully\n");
    }
#endif

#ifdef CONFIG_RA_POEG
  /* Initialize POEG for emergency PWM shutdown
   * Note: POEG should be initialized after GPT modules
   * to provide hardware failsafe for PWM outputs
   */

  ret = board_poeg_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize POEG: %d\n", ret);
    }
  else
    {
      syslog(LOG_INFO, "POEG initialized successfully\n");
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

#ifdef CONFIG_RA_SDHI
  /* Initialize SDHI interface */

  ret = board_sdhi_init();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize SDHI: %d\n", ret);
    }
  else
    {
      syslog(LOG_INFO, "SDHI initialized successfully\n");
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

#ifdef CONFIG_RA_CAC
  ret = board_cac_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: board_cac_initialize failed: %d\n", ret);
    }
  else
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize CAC: %d\n", ret);
    }
#endif

#ifdef CONFIG_RA_LPM
  /* Initialize Low Power Mode subsystem */

  ret = board_lpm_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize LPM: %d\n", ret);
    }
  else
    {
      syslog(LOG_INFO, "LPM initialized successfully\n");
    }
#endif

#ifdef CONFIG_RA_IPC
  /* Initialize Inter-Processor Communication */

  ret = board_ipc_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize IPC: %d\n", ret);
    }
  else
    {
      syslog(LOG_INFO, "IPC initialized successfully on CPU%d\n",
             CONFIG_RA_CPU_CORE);
    }
#endif

#ifdef CONFIG_RA8P1_EXAMPLE_SUPPORT
    /* Run application examples */
  ra8p1_app_examples();
#endif

  return ret;
}
