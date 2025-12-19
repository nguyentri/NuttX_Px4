/****************************************************************************
 * boards/arm/rzv2h/rzv2h-evk/include/board.h
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

#ifndef __BOARDS_ARM_RZV2H_RZV2H_EVK_INCLUDE_BOARD_H
#define __BOARDS_ARM_RZV2H_RZV2H_EVK_INCLUDE_BOARD_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#ifndef __ASSEMBLY__
#  include <stdint.h>
#  include <stdbool.h>
#endif

#include "rzv_gpio.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Board Configuration Overview *********************************************/

/* This board configuration is aligned with the PX4 FreeRTOS+FSP reference
 * implementation for the Renesas RZV2H platform. Key features:
 *
 * Sensors:
 *   - MPU9250 IMU on SPI bus 0 with DRDY on P5_0
 *   - BMP388/BMP280 barometer on I2C bus 7 at address 0x76
 *
 * Serial Ports:
 *   - SCI0 (/dev/ttyS0): RC input - Port 5 pins 0-1
 *   - SCI1 (/dev/ttyS1): MAVLink telemetry - Port 5 pins 2-3
 *   - SCI2 (/dev/ttyS2): GPS - Port 5 pins 4-5
 *   - SCI3 (/dev/ttyS3): NSH Console - Port 5 pins 6-7
 *
 * PWM Outputs:
 *   - 4 channels using GPT timers on Port 7 (P7_1, P7_2, P7_5, P7_6)
 *
 * Pin assignments follow the FSP configuration in pin_data.c
 */

/* Clocking *****************************************************************/

/* The RZV2H EVK has a 24 MHz crystal oscillator */

#define RZV_BOARD_XTAL_FREQUENCY  24000000  /* 24 MHz */

/* LED definitions **********************************************************/

/* The RZV2H EVK has 4 user LEDs:
 *
 * LED1: P0_0 (GPIO Port 0, Pin 0)
 * LED2: P0_1 (GPIO Port 0, Pin 1)
 * LED3: P0_2 (GPIO Port 0, Pin 2)
 * LED4: P0_3 (GPIO Port 0, Pin 3)
 *
 * These LEDs are active low (write 0 to turn on)
 * We use OUTPUT_HIGH as initial state (LED off) since they are active low
 */

#define BOARD_LED1_GPIO   GPIO_P0_0_OUTPUT_HIGH
#define BOARD_LED2_GPIO   GPIO_P0_1_OUTPUT_HIGH
#define BOARD_LED3_GPIO   GPIO_P0_2_OUTPUT_HIGH
#define BOARD_LED4_GPIO   GPIO_P0_3_OUTPUT_HIGH

#define BOARD_NLEDS       4

/* LED index values for use with board_userled() */

#define BOARD_LED1        0
#define BOARD_LED2        1
#define BOARD_LED3        2
#define BOARD_LED4        3

/* LED bits for use with board_userled_all() */

#define BOARD_LED1_BIT    (1 << BOARD_LED1)
#define BOARD_LED2_BIT    (1 << BOARD_LED2)
#define BOARD_LED3_BIT    (1 << BOARD_LED3)
#define BOARD_LED4_BIT    (1 << BOARD_LED4)

/* If CONFIG_ARCH_LEDS is defined, the LEDs will be controlled as follows
 * for NuttX debug functionality (where NC means "No Change").
 */

#define LED_STARTED       0  /* OFF      OFF      OFF      OFF      */
#define LED_HEAPALLOCATE  1  /* ON       OFF      OFF      OFF      */
#define LED_IRQSENABLED   2  /* OFF      ON       OFF      OFF      */
#define LED_STACKCREATED  3  /* OFF      OFF      ON       OFF      */
#define LED_INIRQ         4  /* NC       NC       NC       ON       */
#define LED_SIGNAL        5  /* NC       NC       NC       NC       */
#define LED_ASSERTION     6  /* BLINK    NC       NC       NC       */
#define LED_PANIC         7  /* BLINK    BLINK    BLINK    BLINK    */

/* Button definitions *******************************************************/

/* The RZV2H EVK does not have dedicated user buttons in the pin mapping table.
 * The following are placeholders and should be updated based on actual hardware.
 * For now, using GPIO inputs as examples (update these based on your board design)
 */

/* Placeholder button definitions - update based on actual EVK button hardware */
#define BOARD_NBUTTONS      0

/* UART Configuration *******************************************************/

/* UART device paths and assignments (matching PX4 board configuration)
 *
 * Following the PX4 board serial configuration from rzv_serial_config.h:
 * - RC input: /dev/ttyS0  (SCI0)
 * - MAVLink:  /dev/ttyS1  (SCI1)
 * - GPS:      /dev/ttyS2  (SCI2)
 * - Console:  /dev/ttyS3  (SCI3) - NSH shell
 */

#define BOARD_UART_RC_DEVICE         "/dev/ttyS0"
#define BOARD_UART_MAVLINK_DEVICE    "/dev/ttyS1"
#define BOARD_UART_GPS_DEVICE        "/dev/ttyS2"

/* SCI3 is used as the default NSH console interface */

#define BOARD_CONSOLE_UART        3       /* Use SCI3 for console */
#define BOARD_CONSOLE_BAUD        115200
#define BOARD_CONSOLE_BITS        8
#define BOARD_CONSOLE_PARITY      0
#define BOARD_CONSOLE_2STOP       0

/* SCI UART pin definitions using canonical pinmap macros */

/* SCI0 pins for RC input (Port 5, Mode 1) */

#define BOARD_SCI0_TXD_GPIO   GPIO_TXD0_MOSI0_DA0_P5_0_M1    /* P50 = PORT5 pin 0, Mode1 */
#define BOARD_SCI0_RXD_GPIO   GPIO_RXD0_MISO0_SCL0_P5_1_M1   /* P51 = PORT5 pin 1, Mode1 */

/* SCI1 pins for MAVLink (Port 5, Mode 1) */

#define BOARD_SCI1_TXD_GPIO   GPIO_TXD1_MOSI1_SDA1_P5_2_M1   /* P52 = PORT5 pin 2, Mode1 */
#define BOARD_SCI1_RXD_GPIO   GPIO_RXD1_MISO1_SCL1_P5_3_M1   /* P53 = PORT5 pin 3, Mode1 */

/* SCI2 pins for GPS (Port 5, Mode 1) */

#define BOARD_SCI2_TXD_GPIO   GPIO_TXD2_MOSI2_SDA2_P5_4_M1   /* P54 = PORT5 pin 4, Mode1 */
#define BOARD_SCI2_RXD_GPIO   GPIO_RXD2_MISO2_SCL2_P5_5_M1   /* P55 = PORT5 pin 5, Mode1 */

/* SCI3 pins for NSH Console (Port 5, Mode 1) */

#define BOARD_SCI3_TXD_GPIO   GPIO_TXD3_MOSI3_SDA3_P5_6_M1   /* P56 = PORT5 pin 6, Mode1 */
#define BOARD_SCI3_RXD_GPIO   GPIO_RXD3_MISO3_SCL3_P5_7_M1   /* P57 = PORT5 pin 7, Mode1 */


/* I2C Configuration ********************************************************/

/* I2C bus configuration matching PX4 board setup
 *
 * I2C7 (RIIC7) is used for the BMP388 barometer sensor at address 0x76
 * This corresponds to g_i2c_baro in the FSP configuration
 */

/* Number of I2C buses defined in PX4 board_config.h */
#define PX4_NUMBER_I2C_BUSES    1

/* I2C7 pins for barometer (Port 9, Mode 2):
 *
 * I2C7_SDA (RIIC7): P90 (SDA6 via SCI8_TX - Mode 2)
 * I2C7_SCL (RIIC7): P91 (SCL6 via SCI8_RX - Mode 2)
 *
 * Note: Port 9 provides I2C6 functionality via SCI8 in Mode 2
 */

#define BOARD_I2C7_SDA_GPIO   GPIO_TXD8_MOSI8_SDA6_P9_0_M2   /* P90 = PORT9 pin 0, Mode2 */
#define BOARD_I2C7_SCL_GPIO   GPIO_RXD8_MISO8_SCL6_P9_1_M2   /* P91 = PORT9 pin 1, Mode2 */
#define BOARD_RIIC7_SDA_GPIO  BOARD_I2C7_SDA_GPIO  /* Alias for RIIC7 */
#define BOARD_RIIC7_SCL_GPIO  BOARD_I2C7_SCL_GPIO  /* Alias for RIIC7 */

/* Default I2C bus for sensors (barometer on bus 7) */
#define BOARD_I2C_SENSOR_BUS  7  /* Use RIIC7 for barometer sensor */

/* RIIC (Renesas I2C) Configuration - Additional buses for expansion */

/* RIIC2 pins via Pmod Type6 I2C connector (CN6):
 *
 * I2C2_SDA (RIIC2): P20 (SDA2 - Mode 4)
 * I2C2_SCL (RIIC2): P21 (SCL2 - Mode 4)
 */

#define BOARD_I2C2_SDA_GPIO   GPIO_SDA2_P2_0_M4    /* P20 = PORT2 pin 0, Mode4 */
#define BOARD_I2C2_SCL_GPIO   GPIO_SCL2_P2_1_M4    /* P21 = PORT2 pin 1, Mode4 */
#define BOARD_RIIC2_SDA_GPIO  BOARD_I2C2_SDA_GPIO  /* Alias for RIIC2 */
#define BOARD_RIIC2_SCL_GPIO  BOARD_I2C2_SCL_GPIO  /* Alias for RIIC2 */

/* RIIC0 pins (Camera/MIPI):
 *
 * I2C0_SDA (RIIC0): P30 (SDA0 - Mode 1) - MIPI CSI-2 CH0
 * I2C0_SCL (RIIC0): P31 (SCL0 - Mode 1) - MIPI CSI-2 CH0
 */

#define BOARD_I2C0_SDA_GPIO   GPIO_SDA0_P3_0_M1    /* P30 = PORT3 pin 0, Mode1 */
#define BOARD_I2C0_SCL_GPIO   GPIO_SCL0_P3_1_M1    /* P31 = PORT3 pin 1, Mode1 */
#define BOARD_RIIC0_SDA_GPIO  BOARD_I2C0_SDA_GPIO  /* Alias for RIIC0 */
#define BOARD_RIIC0_SCL_GPIO  BOARD_I2C0_SCL_GPIO  /* Alias for RIIC0 */

/* RIIC1 pins (Camera/MIPI):
 *
 * I2C1_SDA (RIIC1): P32 (SDA1 - Mode 1) - MIPI CSI-2 CH1
 * I2C1_SCL (RIIC1): P33 (SCL1 - Mode 1) - MIPI CSI-2 CH1
 */

#define BOARD_I2C1_SDA_GPIO   GPIO_SDA1_P3_2_M1    /* P32 = PORT3 pin 2, Mode1 */
#define BOARD_I2C1_SCL_GPIO   GPIO_SCL1_P3_3_M1    /* P33 = PORT3 pin 3, Mode1 */
#define BOARD_RIIC1_SDA_GPIO  BOARD_I2C1_SDA_GPIO  /* Alias for RIIC1 */
#define BOARD_RIIC1_SCL_GPIO  BOARD_I2C1_SCL_GPIO  /* Alias for RIIC1 */

/* SCI I2C Configuration (Simple I2C mode on SCI peripherals) **************/

/* SCI0 I2C pins:
 *
 * SCI0_SDA: P82 (SDA - Mode 6) - Simple I2C
 * SCI0_SCL: P83 (SCL - Mode 6) - Simple I2C
 */

#define BOARD_SCI0_SDA_GPIO   GPIO_TXD0_P8_2_M6     /* P82 = PORT8 pin 2, Mode6 */
#define BOARD_SCI0_SCL_GPIO   GPIO_RXD0_P8_3_M6     /* P83 = PORT8 pin 3, Mode6 */

/* SCI1 I2C pins:
 *
 * SCI1_SDA: P53 (SDA - Mode 11) - Simple I2C
 * SCI1_SCL: P96 (SCL - Mode 9) - Simple I2C
 */

#define BOARD_SCI1_SDA_GPIO   GPIO_TXD1_P5_3_M11    /* P53 = PORT5 pin 3, Mode11 */
#define BOARD_SCI1_SCL_GPIO   GPIO_RXD1_P9_6_M9     /* P96 = PORT9 pin 6, Mode9 */

/* SCI2 I2C pins:
 *
 * SCI2_SDA: PA4 (SDA - Mode 11) - Simple I2C
 * SCI2_SCL: PA7 (SCL - Mode 11) - Simple I2C
 */

#define BOARD_SCI2_SDA_GPIO   GPIO_TXD2_PA_4_M11    /* PA4 = PORT10 pin 4, Mode11 */
#define BOARD_SCI2_SCL_GPIO   GPIO_RXD2_PA_7_M11    /* PA7 = PORT10 pin 7, Mode11 */

/* SCI3 I2C pins:
 *
 * SCI3_SDA: (Define based on your board schematic)
 * SCI3_SCL: (Define based on your board schematic)
 */

/* Note: SCI3 I2C pin configuration depends on board-specific design */

/* SPI Configuration ********************************************************/

/* SPI bus configuration matching PX4 board setup
 *
 * SPI0 is used for the MPU9250 IMU sensor
 * This corresponds to g_spi_imu in the FSP configuration
 */

/* Number of SPI buses defined in PX4 board_config.h */
#define PX4_NUMBER_SPI_BUSES    2

/* SPI0 for MPU9250 IMU (g_spi_imu):
 *
 * SPI0_CS:    (Chip select handled by FSP configuration)
 * SPI0_MOSI:  (Configure via FSP)
 * SPI0_MISO:  (Configure via FSP)
 * SPI0_SCK:   (Configure via FSP)
 *
 * Note: Actual pin assignments are managed through FSP pin configuration
 */

/* SPI0 (Pmod Type2 SPI connector CN2 - alternative configuration):
 *
 * SPI0_SSLA (CS):  PA7 (SSLC0 - Mode 5)
 * SPI0_MOSI:       PB4 (MOSI0 - Mode 5)
 * SPI0_MISO:       PB3 (MISO0 - Mode 5)
 * SPI0_SCK:        PB5 (RSPCK0 - Mode 5)
 */

#define BOARD_SPI0_CS_GPIO    GPIO_SSLC0_PA_7_M5     /* PA7 = PORT10 pin 7, Mode5 */
#define BOARD_SPI0_MOSI_GPIO  GPIO_MOSI0_PB_4_M5     /* PB4 = PORT11 pin 4, Mode5 */
#define BOARD_SPI0_MISO_GPIO  GPIO_MISO0_PB_3_M5     /* PB3 = PORT11 pin 3, Mode5 */
#define BOARD_SPI0_SCK_GPIO   GPIO_RSPCK0_PB_5_M5    /* PB5 = PORT11 pin 5, Mode5 */

/* Sensor Configuration *****************************************************/

/* MPU9250 IMU Sensor (SPI0)
 *
 * The MPU9250 is connected via SPI bus 0 (g_spi_imu)
 * Chip select is managed internally by FSP
 * Data Ready (DRDY) interrupt on P50 (PORT5 pin 0)
 *
 * From spi.cpp: drdy_gpio = BSP_IO_PORT_05_PIN_00
 * From pin_data.c: P50 configured with TINT_ENABLE for interrupt
 */

#define BOARD_MPU9250_BUS           0        /* SPI bus 0 */
#define BOARD_MPU9250_DRDY_GPIO     GPIO_P5_0_INPUT  /* P50 = PORT5 pin 0, input with IRQ */

/* External IRQ configuration for MPU9250 DRDY
 * From pin_data.c: P50 has IOPORT_CFG_TINT_ENABLE set
 * This enables the external interrupt (TINT) capability
 */
#define BOARD_MPU9250_DRDY_IRQ_ENABLE   1

/* BMP388/BMP280 Barometer Sensor (I2C7)
 *
 * The BMP388 (or BMP280 variant) is connected via I2C bus 7 (g_i2c_baro)
 * I2C address: 0x76 (from board_config.h: PX4_I2C_OBDEV_BMP280)
 */

#define BOARD_BMP388_BUS            7        /* I2C bus 7 (RIIC7) */
#define BOARD_BMP388_ADDR           0x76     /* I2C device address */
#define BOARD_BMP280_BUS            BOARD_BMP388_BUS   /* Alias for BMP280 */
#define BOARD_BMP280_ADDR           BOARD_BMP388_ADDR  /* Same address */

/* Sensor bus aliases for driver compatibility */
#define BOARD_IMU_SPI_BUS           BOARD_MPU9250_BUS
#define BOARD_BARO_I2C_BUS          BOARD_BMP388_BUS

/* PWM Configuration ********************************************************/

/* PWM outputs using GPT (General PWM Timer) modules
 *
 * Configuration matches PX4 board_pwm_out.cpp timer bindings:
 * - Timer1 (GTIOCA) - PWM Channel 0
 * - Timer2 (GTIOCB) - PWM Channel 1
 * - Timer3 (GTIOCA) - PWM Channel 2
 * - Timer4 (GTIOCB) - PWM Channel 3
 *
 * Pin assignments from pin_data.c (Port 7, Mode 1):
 * - P71, P72, P73 configured for GPT peripheral mode
 * - P75, P76, P77 configured for GPT peripheral mode
 */

/* Maximum number of PWM channels (from board_pwm_out.h) */
#define BOARD_PWM_MAX_CHANNELS      4

/* PWM channel GPIO definitions (Port 7 GPT pins, Mode 1) */
#define BOARD_PWM_CH0_GPIO      GPIO_GTIOC1A_P7_1_M1   /* Timer1 GTIOCA on P71 */
#define BOARD_PWM_CH1_GPIO      GPIO_GTIOC2B_P7_2_M1   /* Timer2 GTIOCB on P72 */
#define BOARD_PWM_CH2_GPIO      GPIO_GTIOC3A_P7_5_M1   /* Timer3 GTIOCA on P75 */
#define BOARD_PWM_CH3_GPIO      GPIO_GTIOC4B_P7_6_M1   /* Timer4 GTIOCB on P76 */

/* PWM default parameters (from board_pwm_out.cpp) */
#define BOARD_PWM_DEFAULT_PERIOD_US     20000    /* 20ms period (50Hz) */
#define BOARD_PWM_DEFAULT_MIN_US        900      /* Minimum pulse width */
#define BOARD_PWM_DEFAULT_MAX_US        2100     /* Maximum pulse width */

/* Legacy PWM GPIO for compatibility */
#define BOARD_PWM0_GPIO       BOARD_PWM_CH0_GPIO

/* ADC Configuration ********************************************************/

/* ADC input channels for RZV2H ADC_E peripheral:
 *
 * The RDK-RZV2H board provides ADC input channels AN000-AN007.
 * Configure which channels to enable in rzv2h_adc.c
 *
 * Channel mappings (typical RZV2H pinout - verify with board schematic):
 *   AN000 - Analog input 0
 *   AN001 - Analog input 1
 *   AN002 - Analog input 2
 *   AN003 - Analog input 3
 *   AN004 - Analog input 4
 *   AN005 - Analog input 5
 *   AN006 - Analog input 6
 *   AN007 - Analog input 7
 *
 * Note: ADC pins are typically dedicated analog inputs and may not
 * require explicit GPIO configuration. Refer to the RZV2H hardware
 * manual for specific pin functions.
 */

/* Default ADC channel configuration - modify as needed */

#define BOARD_ADC_CHANNEL_0     0    /* AN000 */
#define BOARD_ADC_CHANNEL_1     1    /* AN001 */
#define BOARD_ADC_CHANNEL_2     2    /* AN002 */
#define BOARD_ADC_CHANNEL_3     3    /* AN003 */

/* Uncomment to enable additional channels */

/* #define BOARD_ADC_CHANNEL_4     4 */ /* AN004 */
/* #define BOARD_ADC_CHANNEL_5     5 */ /* AN005 */
/* #define BOARD_ADC_CHANNEL_6     6 */ /* AN006 */
/* #define BOARD_ADC_CHANNEL_7     7 */ /* AN007 */

/* Total number of enabled ADC channels */

#define BOARD_ADC_NCHANNELS     4

/* ADC GPIO pin definitions (if needed for explicit configuration)
 * Most ADC pins are dedicated analog inputs and don't need GPIO setup.
 * These definitions are provided for boards that require it.
 */

/* #define BOARD_ADC_PIN_AN000     GPIO_P4_4_ANALOG */  /* Example - verify with schematic */
/* #define BOARD_ADC_PIN_AN001     GPIO_P4_5_ANALOG */
/* #define BOARD_ADC_PIN_AN002     GPIO_P4_6_ANALOG */
/* #define BOARD_ADC_PIN_AN003     GPIO_P4_7_ANALOG */

/* GPIO Pins ***********************************************************/

/* Pin configurations from FSP pin_data.c
 *
 * These definitions reflect the actual pin assignments used in the
 * PX4 FreeRTOS+FSP configuration, ensuring compatibility between
 * NuttX and the reference implementation.
 */

/* P5_0 - MPU9250 DRDY with TINT (external interrupt) capability */
#define BOARD_P5_0_GPIO   GPIO_P5_0_INPUT  /* DRDY for IMU sensor */

/* P5_3 - SCI1 RX (Mode 1) */
#define BOARD_P5_3_GPIO   GPIO_RXD1_MISO1_SCL1_P5_3_M1

/* P7_0, P7_1, P7_2, P7_3 - SCI4/SCI5 UART functions (Mode 1) */
#define BOARD_P7_0_GPIO   GPIO_TXD4_MOSI4_SDA4_P7_0_M1  /* SCI4 TX */
#define BOARD_P7_1_GPIO   GPIO_RXD4_MISO4_SCL4_P7_1_M1  /* SCI4 RX */
#define BOARD_P7_2_GPIO   GPIO_TXD5_MOSI5_SDA5_P7_2_M1  /* SCI5 TX */
#define BOARD_P7_3_GPIO   GPIO_RXD5_MISO5_SCL5_P7_3_M1  /* SCI5 RX */

/* P7_5, P7_6, P7_7 - SCI6/SCI7 UART functions (Mode 1) */
#define BOARD_P7_5_GPIO   GPIO_RXD6_MISO6_SCL6_P7_5_M1  /* SCI6 RX */
#define BOARD_P7_6_GPIO   GPIO_TXD7_MOSI7_SDA7_P7_6_M1  /* SCI7 TX */
#define BOARD_P7_7_GPIO   GPIO_RXD7_MISO7_SCL7_P7_7_M1  /* SCI7 RX */

/* P8_2, P8_3 - SCI0 alternate pins (Mode 6) */
#define BOARD_P8_2_GPIO   GPIO_TXD0_P8_2_M6     /* SCI0 TX alternate */
#define BOARD_P8_3_GPIO   GPIO_RXD0_P8_3_M6     /* SCI0 RX alternate */

/* P9_0 - I2C6/SCI8 SDA (Mode 2) */
#define BOARD_P9_0_GPIO   GPIO_TXD8_MOSI8_SDA6_P9_0_M2  /* I2C6 SDA via SCI8 */

/* Legacy GPIO pin definitions (from previous configuration) */

/* P1_4 - configured as input with noise filter and TINT in FSP */
#define BOARD_P1_4_GPIO   GPIO_P1_4_INPUT_PULLUP

/* P2_0 and P2_1 - I2C2 peripheral function mode4 */
#define BOARD_P2_0_GPIO   GPIO_SDA2_P2_0_M4
#define BOARD_P2_1_GPIO   GPIO_SCL2_P2_1_M4

/* P3_4 and P3_5 - peripheral function mode2 (fast slew) */
#define BOARD_P3_4_GPIO   GPIO_TXD_MOSI4_SDA3_P3_4_M2
#define BOARD_P3_5_GPIO   GPIO_RXD_MISO3_SCL3_P3_5_M2

/* P3_6 - peripheral function mode5 */
#define BOARD_P3_6_GPIO   GPIO_SSLA2_P3_6_M5

/* P3_7 - peripheral function mode9 (slow slew) */
#define BOARD_P3_7_GPIO   GPIO_GTIOC7B_P3_7_M9

/* P4_0 and P4_6 - peripheral function mode9 (slow slew) */
#define BOARD_P4_0_GPIO   GPIO_GTIOC0A_P4_0_M9
#define BOARD_P4_6_GPIO   GPIO_GTIOC3A_P4_6_M9

/* P6_3 - peripheral function mode11 (slow slew) */
#define BOARD_P6_3_GPIO   GPIO_GTIOC11B_P6_3_M11

/* P9_1, P9_2 - I2C6/SCI8 and SPI peripheral functions */
#define BOARD_P9_1_GPIO   GPIO_RXD8_MISO8_SCL6_P9_1_M2  /* I2C6 SCL via SCI8 */
#define BOARD_P9_2_GPIO   GPIO_RSPCK4_P9_2_M1   /* SPI4 clock */

/* P6_0 - used by FSP event config as output */
#define BOARD_P6_0_GPIO   GPIO_P6_0_OUTPUT_LOW

/* LED pins - aliases to existing NuttX LED macros */
#define BOARD_P0_0_GPIO   GPIO_P0_0_OUTPUT_HIGH
#define BOARD_P0_1_GPIO   GPIO_P0_1_OUTPUT_HIGH

/* End of FSP-generated pin mappings */

/* Board Capabilities *******************************************************/

#define BOARD_HAS_LEDS        1
#define BOARD_HAS_BUTTONS     1
#define BOARD_HAS_I2C         1
#define BOARD_HAS_SPI         1
#define BOARD_HAS_PWM         1
#define BOARD_HAS_ADC         1
#define BOARD_HAS_WATCHDOG    1

/* PX4 Board Configuration Compatibility ************************************/

/* Board UUID for PX4 identification (matching board_config.h) */
#define BOARD_OVERRIDE_UUID   "RZV2H0000000000"  /* 16 characters */

/* System architecture ID */
#define PX4_SOC_ARCH_ID       0  /* PX4_SOC_ARCH_ID_UNUSED */

/* Battery monitoring configuration (no ADC battery monitoring) */
#define ADC_BATTERY_VOLTAGE_CHANNEL    -1
#define ADC_BATTERY_CURRENT_CHANNEL    -1
#define BOARD_NUMBER_BRICKS            1
#define BOARD_ADC_BRICK_VALID          0
#define BOARD_NUMBER_USB_BRICKS        0
#define BOARD_USB_VBUS_VALID           0

/* RC Serial port (matching RC_SERIAL_PORT in board_config.h) */
#define RC_SERIAL_PORT        BOARD_UART_RC_DEVICE

/* Configuration flags */
#define CONFIG_I2C            1
#define CONFIG_SPI            1
#define CONFIG_UART           1

/****************************************************************************
 * Public Types
 ****************************************************************************/

#ifndef __ASSEMBLY__

/****************************************************************************
 * Public Data
 ****************************************************************************/

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_board_initialize
 *
 * Description:
 *   All RZV2H architectures must provide the following entry point. This
 *   entry point is called early in the initialization -- after clocking
 *   and memory have been configured but before caches have been enabled
 *   and before any devices have been initialized.
 *
 ****************************************************************************/

void rzv_board_initialize(void);

/****************************************************************************
 * Name: rzv_spi_initialize
 *
 * Description:
 *   Initialize SPI chip select GPIOs
 *
 ****************************************************************************/

#ifdef CONFIG_RZV_SPI
void rzv_spi_initialize(void);
#endif

/****************************************************************************
 * Name: board_spi_initialize
 *
 * Description:
 *   Initialize and register SPI devices for the board
 *
 ****************************************************************************/

#ifdef CONFIG_RZV_SPI
int board_spi_initialize(void);
#endif

/****************************************************************************
 * Name: rzv2h_adc_setup
 *
 * Description:
 *   Initialize ADC and register the ADC device
 *
 ****************************************************************************/

#ifdef CONFIG_RZV_ADC
int rzv2h_adc_setup(void);
#endif

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __BOARDS_ARM_RZV2H_RZV2H_EVK_INCLUDE_BOARD_H */