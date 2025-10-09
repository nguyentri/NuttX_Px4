/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/evk-ra8p1.h
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

#ifndef __BOARDS_ARM_RA8_EVK_RA8P1_SRC_H
#define __BOARDS_ARM_RA8_EVK_RA8P1_SRC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>

#include <stdint.h>

#include <arch/irq.h>
#include <nuttx/irq.h>

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
 * Public Functions Definitions
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

int ra8p1_bringup(void);

/* Run all enabled application examples (used by ra8p1_bringup()) */
int ra8p1_app_examples(void);

/****************************************************************************
 * Name: ra8p1_boardinitialize
 *
 * Description:
 *   All RA8P1 architectures must provide the following entry point.  This
 *   entry point is called early in the initialization -- after all memory
 *   has been configured and mapped but before any devices have been
 *   initialized.
 *
 ****************************************************************************/

void ra8p1_boardinitialize(void);

/****************************************************************************
 * Name: board_autoled_initialize
 *
 * Description:
 *   Initialize NuttX-controlled LEDs logic
 *
 ****************************************************************************/

#ifdef CONFIG_ARCH_LEDS
void board_autoled_initialize(void);
void board_autoled_on(int led);
void board_autoled_off(int led);
#endif

/****************************************************************************
 * Nuttx driver interfaces
 ****************************************************************************/

#ifdef CONFIG_RTC_DRIVER
int board_rtc_initialize(void);
#endif

/****************************************************************************
 * RA8P1 driver interfaces for use by applications on the fpb-ra8p1 board
 ****************************************************************************/

#ifdef CONFIG_RA8P1_GPIO
int ra8p1_gpio_initialize(void);
#endif

/****************************************************************************
 * Example application interfaces
 ****************************************************************************/

#ifdef CONFIG_RA8P1_SPI_LOOPBACK_EXAMPLE
int ra8p1_spi_loopback_init(void);
int ra8p1_spi_loopback_test(void);
int ra8p1_spi_loopback_main(int argc, char *argv[]);
 #endif

#ifdef CONFIG_RA8P1_SPI_MASTERSLAVE_EXAMPLE
int ra8p1_spi_masterslave_init(void);
int ra8p1_spi_masterslave_test(void);
int ra8p1_spi_masterslave_main(int argc, char *argv[]);
#endif

#ifdef CONFIG_RA8P1_ADC_BMS_EXAMPLE
int ra8p1_adc_bms_init(void);
int ra8p1_adc_bms_main(int argc, FAR char *argv[]);
#endif

#ifdef CONFIG_RA8P1_ADC_EXAMPLE
/* Board-level ADC initialization */
int ra8p1_adc_driver_initialize(void);
#endif

#ifdef CONFIG_RA8P1_CODE_FLASH_EXAMPLE
int ra8p1_code_flash_init(void);
int ra8p1_code_flash_test(void);
int ra8p1_code_flash_info(void);
int ra8p1_code_flash_main(int argc, char *argv[]);
#endif

#ifdef CONFIG_RA8P1_DATA_FLASH_EXAMPLE
int ra8p1_data_flash_init(void);
int ra8p1_data_flash_test(void);
int ra8p1_data_flash_main(int argc, char *argv[]);
#endif

#ifdef CONFIG_RA8P1_GPT_PWM_EXAMPLE
int ra8p1_gpt_pwm_initialize(void);
int ra8p1_gpt_pwm_main(int argc, char *argv[]);
#endif

#ifdef CONFIG_RA8P1_PWM_ESCS_EXAMPLE
int ra8p1_gpt_escs_init(void);
int ra8p1_gpt_escs_main(int argc, char *argv[]);
#endif

#ifdef CONFIG_RA8P1_GPS_EXAMPLE
int ra8p1_gps_init(void);
int ra8p1_gps_main(int argc, char *argv[]);
#endif

#ifdef CONFIG_RA8P1_SBUS_EXAMPLE
int ra8p1_sbus_init(void);
int ra8p1_sbus_main(int argc, char *argv[]);
#endif

#ifdef CONFIG_RA8P1_I2C_ACC_EXAMPLE
int ra8p1_i2c_acc_init(void);
int ra8p1_i2c_acc_main(int argc, char *argv[]);
#endif

#ifdef CONFIG_RA8P1_I2C_GY912_EXAMPLE
int ra8p1_i2c_gy912_init(void);
int ra8p1_i2c_gy912_main(int argc, FAR char *argv[]);
#endif

#ifdef CONFIG_RA8P1_RUST_EXAMPLE
int ra8p1_rust_sample_init(void);
#endif

/****************************************************************************
 * Name: gy912_register_sensors
 *
 * Description:
 *   Register GY-912 sensors with the sensor framework
 *
 ****************************************************************************/

#ifdef CONFIG_RA8P1_SPI_GY912_EXAMPLE
struct spi_dev_s;
int gy912_register_sensors(FAR struct spi_dev_s *spi);
#endif

#endif /* __ASSEMBLY__ */
#endif /* __BOARDS_ARM_RA8_EVK_RA8P1_SRC_H */
