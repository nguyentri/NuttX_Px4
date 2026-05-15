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
#include "rzv_gpio.h"
#include "rzv2h_sci_i2c.h"

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
  int first_error = 0;  /* audit finding #10: preserve first failure; ret is
                         * overwritten by each subsystem so errors are swallowed.
                         * first_error captures the earliest non-zero status. */

  syslog(LOG_INFO, "NuttX: RDK-RZV2H Board bring-up starting...\n");

#ifdef CONFIG_RZV_GPIO_IRQ
  /* Phase-03 [High-12, audit §4]: Initialize GPIO IRQ slot table.
   * Sets icu_slot sentinel to -1 in all entries. BSS zero-init leaves
   * icu_slot=0, which equals a valid NuttX IRQ causing false "attached" state.
   * Must be called before any rzv_gpiosetevent() invocation.
   * Source: rzv_gpio.h rzv_gpio_irq_initialize().
   */
  rzv_gpio_irq_initialize();
  syslog(LOG_INFO, "GPIO IRQ subsystem initialized\n");
#endif

#ifdef CONFIG_FS_PROCFS
  /* Mount the procfs file system */

  ret = nx_mount(NULL, "/proc", "procfs", 0, NULL);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to mount procfs at /proc: %d\n", ret);
      if (first_error == 0) first_error = ret;
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
      if (first_error == 0) first_error = ret;
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

#if defined(CONFIG_RZV_I2C0) || defined(CONFIG_RZV_I2C1) || defined(CONFIG_RZV_I2C2)
  /* Initialize I2C bus */

#ifdef CONFIG_RZV_I2C0
  if (board_i2c_initialize(0) != NULL)
    {
      syslog(LOG_INFO, "I2C0 (RIIC0) initialized successfully\n");
    }
  else
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize I2C0\n");
    }
#endif

#ifdef CONFIG_RZV_I2C1
  if (board_i2c_initialize(1) != NULL)
    {
      syslog(LOG_INFO, "I2C1 (RIIC1) initialized successfully\n");
    }
  else
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize I2C1\n");
    }
#endif

#ifdef CONFIG_RZV_I2C2
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

#ifdef CONFIG_RZV_SCI_I2C
  /* Initialize SCI-B Simple-I2C master channels */

  ret = rzv2h_sci_i2c_setup();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize SCI I2C: %d\n", ret);
      if (first_error == 0) first_error = ret;
    }
#endif

#ifdef CONFIG_RZV_SPI
  /* Initialize SPI buses */

  ret = board_spi_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize SPI: %d\n", ret);
      if (first_error == 0) first_error = ret;
    }
  else
    {
      syslog(LOG_INFO, "SPI initialized successfully\n");
    }
#endif

#ifdef CONFIG_RDK_RZV2H_XSPI_PARAMFS
  /* Mount CR8-owned XSPI parameter storage at /fs. */

  ret = rzv2h_xspi_paramfs_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize XSPI paramfs: %d\n", ret);
      if (first_error == 0) first_error = ret;
    }
#endif

#ifdef CONFIG_RZV_SCI_SPI
  /* Initialize SCI_B SPI buses */

  ret = board_sci_spi_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize SCI SPI: %d\n", ret);
      if (first_error == 0) first_error = ret;
    }
  else
    {
      syslog(LOG_INFO, "SCI SPI initialized successfully\n");
    }
#endif

#ifdef CONFIG_RZV_ADC
  /* Initialize ADC module */

  ret = rzv2h_adc_setup();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize ADC: %d\n", ret);
      if (first_error == 0) first_error = ret;
    }
  else
    {
      syslog(LOG_INFO, "ADC initialized successfully\n");
    }
#endif

#ifdef CONFIG_RZV_ETHERNET
  /* Initialize Ethernet (GBETH) driver */

  ret = rzv2h_ether_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize Ethernet: %d\n", ret);
      if (first_error == 0) first_error = ret;
    }
  else
    {
      syslog(LOG_INFO, "Ethernet (GBETH) initialized successfully\n");
    }
#endif

#ifdef CONFIG_PWM
  /* Initialize GPT PWM devices */

  ret = board_pwm_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize GPT PWM: %d\n", ret);
      if (first_error == 0) first_error = ret;
    }
  else
    {
      syslog(LOG_INFO, "GPT PWM devices initialized successfully\n");
    }
#endif

#ifdef CONFIG_RZV_WDT
  /* Initialize Watchdog Timer */

  ret = rzv_wdt_setup();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize WDT: %d\n", ret);
      if (first_error == 0) first_error = ret;
    }
  else
    {
      syslog(LOG_INFO, "Watchdog Timer initialized successfully\n");
    }
#endif

#ifdef CONFIG_RZV_GTM
  /* Initialize GTM Timers */

  ret = board_timer_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize GTM timers: %d\n", ret);
      if (first_error == 0) first_error = ret;
    }
  else
    {
      syslog(LOG_INFO, "GTM timers initialized successfully\n");
    }
#endif

#ifdef CONFIG_RZV2H_EXAMPLE_SUPPORT
  /* Run application examples */

  rzv2h_app_examples();
#endif

  syslog(LOG_INFO, "NuttX: RDK-RZV2H Board bring-up complete\n");

  /* audit finding #10: return first error seen, not the last subsystem's ret */

  return first_error;
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
