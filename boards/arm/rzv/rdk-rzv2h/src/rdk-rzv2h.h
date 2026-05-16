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

#include <nuttx/config.h>
#include <stdint.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define LED_DRIVER_PATH "/dev/userleds"

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* Forward declarations */

struct spi_dev_s;
struct i2c_master_s;

/****************************************************************************
 * Public Data
 ****************************************************************************/

#ifndef __ASSEMBLY__

/****************************************************************************
 * Public Function Prototypes
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

int board_bringup(void);

/****************************************************************************
 * Name: board_button_initialize
 *
 * Description:
 *   Initialize buttons
 *
 ****************************************************************************/

#ifdef CONFIG_ARCH_BUTTONS
void board_button_initialize(void);
#endif

/****************************************************************************
 * Name: board_i2c_initialize
 *
 * Description:
 *   Initialize I2C bus and return a pointer to the I2C device
 *
 ****************************************************************************/

#ifdef CONFIG_RZV_I2C
struct i2c_master_s *board_i2c_initialize(int bus);
#endif

/****************************************************************************
 * Name: board_spi_initialize
 *
 * Description:
 *   Initialize SPI buses
 *
 ****************************************************************************/

#ifdef CONFIG_RZV_SPI
int board_spi_initialize(void);
#endif

/****************************************************************************
 * Name: board_sci_spi_initialize
 *
 * Description:
 *   Initialize SCI_B SPI buses
 *
 ****************************************************************************/

#ifdef CONFIG_RZV_SCI_SPI
int board_sci_spi_initialize(void);
#endif

/****************************************************************************
 * Name: rzv2h_adc_setup
 *
 * Description:
 *   Initialize ADC and register device
 *
 ****************************************************************************/

#ifdef CONFIG_RZV_ADC
int rzv2h_adc_setup(void);
#endif

/****************************************************************************
 * Name: board_pwm_initialize
 *
 * Description:
 *   Initialize GPT PWM devices and register with PWM subsystem
 *
 ****************************************************************************/

#ifdef CONFIG_PWM
int board_pwm_initialize(void);
#endif

/****************************************************************************
 * Name: rzv2h_dtc_initialize
 *
 * Description:
 *   Initialize DTC (Data Transfer Controller)
 *
 ****************************************************************************/

#ifdef CONFIG_RZV_DTC
int rzv2h_dtc_initialize(void);
#endif

/****************************************************************************
 * Name: rzv_wdt_setup
 *
 * Description:
 *   Initialize Watchdog Timer
 *
 ****************************************************************************/

#ifdef CONFIG_RZV_WDT
int rzv_wdt_setup(void);
#endif

/****************************************************************************
 * Name: board_timer_initialize
 *
 * Description:
 *   Initialize GTM timers
 *
 ****************************************************************************/

#ifdef CONFIG_RZV_GTM
int board_timer_initialize(void);
#endif

/****************************************************************************
 * Name: board_ipc_initialize
 *
 * Description:
 *   Initialize RZ/V2H CR8 OpenAMP/RPMsg and optional IPCC device.
 *
 ****************************************************************************/

#ifdef CONFIG_RZV_OPENAMP
int board_ipc_initialize(void);
#endif

/****************************************************************************
 * Name: rzv2h_xspi_paramfs_initialize
 *
 * Description:
 *   Initialize XSPI-backed LittleFS parameter storage.
 *
 ****************************************************************************/

#ifdef CONFIG_RDK_RZV2H_XSPI_PARAMFS
int rzv2h_xspi_paramfs_initialize(void);
#endif

/****************************************************************************
 * Name: rzv2h_ether_initialize
 *
 * Description:
 *   Initialize the Ethernet (GBETH) driver
 *
 ****************************************************************************/

#ifdef CONFIG_RZV_ETHERNET
int rzv2h_ether_initialize(void);
#endif

/****************************************************************************
 * Name: rzv2h_app_examples
 *
 * Description:
 *   Run all enabled board example applications
 *
 ****************************************************************************/

/****************************************************************************
 * Name: rzv2h_serial_setup
 *
 * Description:
 *   Configure serial pins for UART operation
 *
 ****************************************************************************/

void rzv2h_serial_setup(void);

#ifdef CONFIG_RZV2H_EXAMPLE_SUPPORT
int rzv2h_app_examples(void);
#endif

/****************************************************************************
 * Example application initialization functions
 ****************************************************************************/

#ifdef CONFIG_RZV2H_SPI_LOOPBACK_EXAMPLE
int rzv2h_spi_loopback_init(void);
int rzv2h_spi_loopback_main(int argc, char *argv[]);
#endif

#ifdef CONFIG_RZV2H_I2C_GY912_EXAMPLE
int rzv2h_i2c_gy912_init(void);
int rzv2h_i2c_gy912_main(int argc, char *argv[]);
#endif

#ifdef CONFIG_RZV2H_SPI_GY921_EXAMPLE
int rzv2h_spi_gy921_init(void);
int rzv2h_spi_gy921_main(int argc, char *argv[]);
#endif

#ifdef CONFIG_RZV2H_PWM_ONESHOT_EXAMPLE
int rzv2h_pwm_oneshot_init(void);
int rzv2h_pwm_oneshot_main(int argc, char *argv[]);
#endif

#ifdef CONFIG_RZV2H_WDT_TEST
int rzv2h_wdt_test_init(void);
int wdt_test_main(int argc, char *argv[]);
#endif

#endif /* __ASSEMBLY__ */
#endif /* __BOARDS_ARM_RZV_RDK_RZV2H_SRC_H */
