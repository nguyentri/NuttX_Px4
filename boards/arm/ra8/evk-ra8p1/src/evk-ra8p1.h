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

#ifdef CONFIG_RA_POEG
#include "ra_poeg.h"
#endif

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
 * Name: board_gpio_initialize
 *
 * Description:
 *   Initialize all board GPIO pins using centralized configuration
 *
 ****************************************************************************/

int board_gpio_initialize(void);

/****************************************************************************
 * Name: board_sci_spi_initialize
 *
 * Description:
 *   Initialize SCI SPI drivers
 *
 ****************************************************************************/

#ifdef CONFIG_RA_SCI_SPI
int board_sci_spi_initialize(void);
#endif

/****************************************************************************
 * Name: board_cac_initialize
 *
 * Description:
 *   Initialize the CAC driver for the board.
 *
 ****************************************************************************/

#ifdef CONFIG_RA_CAC
int board_cac_initialize(void);
#endif

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

#ifdef CONFIG_RA_ADC_B
int board_adc_initialize(void);
#endif

/****************************************************************************
 * Name: board_elc_initialize
 *
 * Description:
 *   Initialize the Event Link Controller on the EVK-RA8P1 board.
 *
 * Returned Value:
 *   OK on success; a negated errno on failure.
 *
 ****************************************************************************/

#ifdef CONFIG_RA_ELC
int board_elc_initialize(void);
#endif

/****************************************************************************
 * Name: board_rtc_initialize
 *
 * Description:
 *   Initialize and register the RTC driver.
 *
 * Returned Value:
 *   OK on success; a negated errno on failure.
 *
 ****************************************************************************/

#ifdef CONFIG_RTC_DRIVER
int board_rtc_initialize(void);
#endif

/****************************************************************************
 * RA8P1 driver interfaces for use by applications on the evk-ra8p1 board
 ****************************************************************************/

#ifdef CONFIG_RA8P1_GPIO
int board_gpio_initialize(void);
#endif

/****************************************************************************
 * Name: board_pwm_initialize
 *
 * Description:
 *   Initialize PWM and register the PWM device.
 *
 ****************************************************************************/

#if defined(CONFIG_PWM)
int board_pwm_initialize(void);
#endif

/****************************************************************************
 * Name: board_i2c_initialize
 *
 * Description:
 *   Initialize I2C bus for EVK-RA8P1 board
 *
 * Input Parameters:
 *   bus - I2C bus number (0 or 1)
 *
 * Returned Value:
 *   Pointer to I2C device structure on success; NULL on failure
 *
 ****************************************************************************/

#if defined(CONFIG_RA_I2C)
struct i2c_master_s;
struct i2c_master_s *board_i2c_initialize(int bus);
int board_i2c_uninitialize(int bus);
#endif

/****************************************************************************
 * Name: board_i3c_initialize
 *
 * Description:
 *   Initialize and register the I3C driver.
 *
 ****************************************************************************/

int board_i3c_initialize(void);

/****************************************************************************
 * Name: board_canfd_initialize
 *
 * Description:
 *   Initialize the OSPI driver and register the MTD device.
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

#ifdef CONFIG_RA_OSPI
int board_ospi_initialize(void);
#endif

/****************************************************************************
 * Name: board_canfd_initialize
 *
 * Description:
 *   Initialize CAN-FD interfaces for the EVK-RA8P1 board
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

#ifdef CONFIG_RA_CANFD
int board_canfd_initialize(void);
#endif


/****************************************************************************
 * MRAM Driver Interface
 ****************************************************************************/

#ifdef CONFIG_RA_MRAM
/****************************************************************************
 * Name: board_mram_initialize
 *
 * Description:
 *   Initialize MRAM storage for code (OTA/bootloader) and data (parameters).
 *
 * Returned Value:
 *   OK on success, negative errno on failure.
 *
 ****************************************************************************/

int board_mram_initialize(void);

/****************************************************************************
 * Name: board_get_code_mram / board_get_data_mram
 *
 * Description:
 *   Get MTD device pointers for direct MRAM access.
 *
 ****************************************************************************/

#ifdef CONFIG_RA_MRAM_CODE
struct mtd_dev_s *board_get_code_mram(void);
#endif

#ifdef CONFIG_RA_MRAM_DATA
struct mtd_dev_s *board_get_data_mram(void);
ssize_t board_mram_read_param(off_t offset, void *buffer, size_t len);
ssize_t board_mram_write_param(off_t offset, const void *buffer, size_t len);
int board_mram_erase_params(void);
#endif
#endif /* CONFIG_RA_MRAM */

/****************************************************************************
 * SDRAM Driver Interface
 ****************************************************************************/

#ifdef CONFIG_RA_SDRAM
/****************************************************************************
 * Name: board_sdram_initialize
 *
 * Description:
 *   Initialize external SDRAM on the EVK-RA8P1 board.
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure.
 *
 ****************************************************************************/

int board_sdram_initialize(void);

/****************************************************************************
 * Name: board_sdram_selfrefresh_enter / board_sdram_selfrefresh_exit
 *
 * Description:
 *   Enter/exit SDRAM self-refresh mode for low-power states.
 *
 ****************************************************************************/

int board_sdram_selfrefresh_enter(void);
int board_sdram_selfrefresh_exit(void);

/****************************************************************************
 * Name: board_get_sdram_base / board_get_sdram_size
 *
 * Description:
 *   Get SDRAM base address and size.
 *
 ****************************************************************************/

uintptr_t board_get_sdram_base(void);
size_t board_get_sdram_size(void);

#endif /* CONFIG_RA_SDRAM */

/****************************************************************************
 * Name: ra_sdhi_init
 *
 * Description:
 *   Initialize SDHI-based SD Card support
 *
 ****************************************************************************/

#ifdef CONFIG_RA_SDHI
int board_sdhi_init(void);
#endif

/****************************************************************************
 * Example application interfaces
 ****************************************************************************/
#ifdef RA8P1_EXAMPLE_SUPPORT
/* Run all enabled application examples (used by board_bringup()) */
int ra8p1_app_examples(void);
#endif

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

#ifdef CONFIG_RA8P1_PWM_EXAMPLE
int ra8p1_pwm_initialize(void);
int ra8p1_pwm_main(int argc, char *argv[]);
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

#ifdef CONFIG_RA8P1_SPI_GY912_EXAMPLE
struct spi_dev_s;
int gy912_register_sensors(FAR struct spi_dev_s *spi);
#endif

#ifdef CONFIG_RA8P1_OSPI_EXAMPLE
int ra8p1_ospi_test_init(void);
int ra8p1_ospi_test_main(int argc, char *argv[]);
#endif

#ifdef CONFIG_RA_WDT
void board_wdt_initialize(void);
#endif

#ifdef CONFIG_RA_IWDT
void board_iwdt_initialize(void);
#endif

#ifdef CONFIG_RA8P1_WDT_TEST
int wdg_test_main(int argc, char *argv[]);
#endif

/****************************************************************************
 * LPM (Low Power Mode) Interface
 ****************************************************************************/

#ifdef CONFIG_RA_LPM

/****************************************************************************
 * Name: board_lpm_initialize
 *
 * Description:
 *   Initialize the Low Power Mode subsystem for this board.
 *
 * Returned Value:
 *   OK on success; a negated errno on failure.
 *
 ****************************************************************************/

int board_lpm_initialize(void);

/****************************************************************************
 * Name: board_lpm_enter_sleep
 *
 * Description:
 *   Enter Sleep mode. CPU is halted, peripherals continue to run.
 *
 * Returned Value:
 *   OK on wake-up; a negated errno on failure.
 *
 ****************************************************************************/

int board_lpm_enter_sleep(void);

/****************************************************************************
 * Name: board_lpm_enter_deep_sleep
 *
 * Description:
 *   Enter Deep Sleep mode.
 *
 * Returned Value:
 *   OK on wake-up; a negated errno on failure.
 *
 ****************************************************************************/

int board_lpm_enter_deep_sleep(void);

/****************************************************************************
 * Name: board_lpm_enter_standby
 *
 * Description:
 *   Enter Software Standby mode.
 *
 * Input Parameters:
 *   timeout_ms - Wake-up timeout in milliseconds (0 = no timeout)
 *
 * Returned Value:
 *   OK on wake-up; a negated errno on failure.
 *
 ****************************************************************************/

int board_lpm_enter_standby(uint32_t timeout_ms);

#ifdef CONFIG_RA_LPM_DEEP_STANDBY_SUPPORT
/****************************************************************************
 * Name: board_lpm_enter_deep_standby
 *
 * Description:
 *   Enter Deep Software Standby mode.
 *   WARNING: System will reset on wake-up!
 *
 * Input Parameters:
 *   timeout_ms - Wake-up timeout in milliseconds (0 = no timeout)
 *
 * Returned Value:
 *   Does not return on success. Returns negated errno on failure.
 *
 ****************************************************************************/

int board_lpm_enter_deep_standby(uint32_t timeout_ms);

/****************************************************************************
 * Name: board_lpm_check_deep_standby_reset
 *
 * Description:
 *   Check if the system woke up from Deep Software Standby.
 *
 * Returned Value:
 *   True if woke from deep standby, false otherwise.
 *
 ****************************************************************************/

bool board_lpm_check_deep_standby_reset(void);

/****************************************************************************
 * Name: board_lpm_get_deep_standby_wakeup_source
 *
 * Description:
 *   Get the source that woke the system from Deep Software Standby.
 *
 * Input Parameters:
 *   source - Pointer to receive the wake-up source flags.
 *
 * Returned Value:
 *   OK on success; a negated errno on failure.
 *
 ****************************************************************************/

int board_lpm_get_deep_standby_wakeup_source(FAR uint64_t *source);
#endif /* CONFIG_RA_LPM_DEEP_STANDBY_SUPPORT */

struct ra_lpm_status_s;
int board_lpm_get_status(struct ra_lpm_status_s *status);

#endif /* CONFIG_RA_LPM */

/****************************************************************************
 * POEG (Port Output Enable for GPT) Interface
 ****************************************************************************/

#ifdef CONFIG_RA_POEG

/****************************************************************************
 * Name: board_poeg_initialize
 *
 * Description:
 *   Initialize POEG for emergency PWM shutdown.
 *   Provides hardware failsafe to disable GPT outputs on fault conditions.
 *
 * Returned Value:
 *   OK on success; a negated errno on failure.
 *
 ****************************************************************************/

int board_poeg_initialize(void);

/****************************************************************************
 * Name: board_poeg_reset
 *
 * Description:
 *   Reset POEG status and re-enable GPT outputs.
 *   Should only be called after fault condition is resolved.
 *
 * Returned Value:
 *   OK on success; a negated errno on failure.
 *
 ****************************************************************************/

int board_poeg_reset(void);

/****************************************************************************
 * Name: board_poeg_get_status
 *
 * Description:
 *   Get current POEG status.
 *
 * Input Parameters:
 *   status - Pointer to status structure to fill
 *
 * Returned Value:
 *   OK on success; a negated errno on failure.
 *
 ****************************************************************************/

struct ra_poeg_status_s;
int board_poeg_get_status(struct ra_poeg_status_s *status);

/****************************************************************************
 * Name: board_poeg_software_disable
 *
 * Description:
 *   Trigger software disable of GPT outputs.
 *
 * Returned Value:
 *   OK on success; a negated errno on failure.
 *
 ****************************************************************************/

int board_poeg_software_disable(void);

#endif /* CONFIG_RA_POEG */

#endif /* __ASSEMBLY__ */
#endif /* __BOARDS_ARM_RA8_EVK_RA8P1_SRC_H */
