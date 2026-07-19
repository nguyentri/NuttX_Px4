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

/* This board configuration matches the RDK-RZV2H GPIO header pin mapping.
 *
 * Sensors:
 *   - MPU9250 IMU on RSPI0 (P90=MOSI, P91=MISO, P92=SCK, P93=SSLA0) with INT on P50
 *   - BMP280 barometer on SCI-mode I2C7 (P76=SDA, P77=SCL) at address 0x76
 *
 * Serial Ports:
 *   - SCI3 (/dev/ttyS3): NSH Console
 *   - SCI4 (/dev/ttyS4): TFminiPlus (P70=TXD, P71=RXD)
 *   - SCI5 (/dev/ttyS5): Sik Telemetry (P72=TXD, P73=RXD)
 *   - SCI6 (/dev/ttyS6): fs-a8s RC (P75=RXD)
 *   - SCI9 (/dev/ttyS9): GPS M10 (P82=TXD, P83=RXD)
 *
 * PWM Outputs (ESC channels):
 *   - ESC1: PA4 (GPT6A) - GPIO12/PWM0
 *   - ESC2: PA7 (GPT7B) - GPIO13/PWM1
 *   - ESC3: P96 (GPT9A) - GPIO19
 *   - ESC4: P53 (GPT10B) - GPIO06
 */

/* Clocking *****************************************************************/

/* The RZV2H EVK has a 24 MHz crystal oscillator */

#define RZV_BOARD_XTAL_FREQUENCY  24000000  /* 24 MHz */

/* Board clock frequency aliases — NuttX convention.
 * board.h previously only defined XTAL; drivers expecting
 * BOARD_CPU_FREQ or BOARD_PCLK_* would fall back to rzv_clock_get_rate() which
 * returns 0 for many IDs (see review finding #3).  Define authoritative values
 * here to match EVK defaults in rzv_clock.h.
 * NOTE: These are compile-time defaults.  If TF-A reprogrammed CDDIV/CSDIV
 * the actual frequencies may differ — update when divider readback is
 * implemented (rzv_clock_divider_init). */

#define BOARD_CPU_FREQ           800000000  /* CR8 I6CLK 800 MHz */
#define BOARD_PCLK0_FREQ         100000000  /* P0CLK 100 MHz */
#define BOARD_PCLK1_FREQ         100000000  /* P1CLK 100 MHz */
#define BOARD_PCLK4_FREQ         200000000  /* P4CLK 200 MHz (SPI, GPT source) */
#define BOARD_SYSCLK_FREQ        200000000  /* I7CLK 200 MHz */

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

/* UART device paths and assignments.
 *
 * PX4 flight ports use sparse SCI channel numbering:
 * - RC input: /dev/ttyS6  (SCI6 RX-only)
 * - MAVLink:  /dev/ttyS5  (SCI5)
 * - GPS:      /dev/ttyS9  (SCI9)
 * - Console:  /dev/ttyS3  (SCI3) for standalone NSH bring-up
 */

#define BOARD_UART_RC_DEVICE         "/dev/ttyS6"
#define BOARD_UART_MAVLINK_DEVICE    "/dev/ttyS5"
#define BOARD_UART_GPS_DEVICE        "/dev/ttyS9"

/* SCI3 is used as the default NSH console interface */

#define BOARD_CONSOLE_UART        3       /* Use SCI3 for console */
#define BOARD_CONSOLE_BAUD        115200
#define BOARD_CONSOLE_BITS        8
#define BOARD_CONSOLE_PARITY      0
#define BOARD_CONSOLE_2STOP       0

/* SCI UART pin definitions using canonical pinmap macros.
 * SCI4/5/6/9 flight pins are configured by rzv2h_serial.c through the
 * BOARD_P7_x/BOARD_P8_x definitions below.
 */

/* SCI3 pins for NSH Console. RDK pinconfig routes RSCI3 to P34/P35;
 * P56/P57 are disabled there and must not be used as the console pair.
 */

#define BOARD_SCI3_TXD_GPIO   GPIO_TXD_MOSI4_SDA3_P3_4_M2    /* P34 = PORT3 pin 4, Mode2 */
#define BOARD_SCI3_RXD_GPIO   GPIO_RXD_MISO3_SCL3_P3_5_M2    /* P35 = PORT3 pin 5, Mode2 */


/* I2C Configuration ********************************************************/

/* I2C bus configuration matching PX4 board setup
 *
 * SCI-mode I2C7 is used for the BMP280 barometer sensor at address 0x76
 * This corresponds to the I2C barometer channel.
 */

/* Number of I2C buses defined in PX4 board_config.h */
#define PX4_NUMBER_I2C_BUSES    1

/* I2C7 pins for barometer (Port 7, Mode 1):
 *
 * I2C7_SDA: P76 (SDA7 - Mode 1) - BMP280 SDA (GPIO02)
 * I2C7_SCL: P77 (SCL7 - Mode 1) - BMP280 SCL (GPIO03)
 */

#define BOARD_I2C7_SDA_GPIO   GPIO_TXD7_MOSI7_SDA7_P7_6_M1   /* P76 = PORT7 pin 6, Mode1 */
#define BOARD_I2C7_SCL_GPIO   GPIO_RXD7_MISO7_SCL7_P7_7_M1   /* P77 = PORT7 pin 7, Mode1 */
/* Default I2C bus for sensors (barometer on bus 7) */
#define BOARD_I2C_SENSOR_BUS  7  /* Use SCI-mode I2C7 for barometer sensor */

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

/* SCI-I2C configuration ****************************************************/

/* The RDK-RZV2H PX4 barometer path uses SCI-mode I2C7 on P76/P77. The lower
 * numbered SCI-I2C alternates overlap GPS or PWM pins and are intentionally
 * not exposed as board defaults.
 *
 * Schematic verification status:
 *   - No schematic PDF available in refs/ at time of this implementation.
 *   - GY-912 socket on RDK-RZV2H is wired to RIIC (see i2c-gy912 defconfig).
 *   - SCI0-3 I2C pin macros below are derived from rzv2h_pinmap.h symbols
 *     and are correct for pin mux, but BOARD ROUTING IS UNVERIFIED.
 *   - The sci-i2c-gy912 defconfig is a synthetic driver smoke test only;
 *     i2c probe will return empty (no slave on bus) unless GY-912 is
 *     physically rewired to a SCI channel.
 *
 * Pin mapping (RXD pin → SCL, TXD pin → SDA per SCI-B I2C convention):
 *   SCI0: RXD0=P51(Mode1)→SCL, TXD0=P50(Mode1)→SDA
 *   SCI1: RXD1=P53(Mode1)→SCL, TXD1=P52(Mode1)→SDA
 *   SCI2: RXD2=P55(Mode1)→SCL, TXD2=P54(Mode1)→SDA
 *   SCI3: RXD3=P57(Mode1)→SCL, TXD3=P56(Mode1)→SDA
 */

#define BOARD_SCI0_I2C_SCL_GPIO  GPIO_RXD0_MISO0_SCL0_P5_1_M1  /* P51 Mode1 */
#define BOARD_SCI0_I2C_SDA_GPIO  GPIO_TXD0_MOSI0_DA0_P5_0_M1   /* P50 Mode1 */
#define BOARD_SCI0_I2C_SCL_RESET_GPIO  (GPIO_P5_1_OUTPUT_HIGH | GPIO_OPENDRAIN)
#define BOARD_SCI0_I2C_SDA_RESET_GPIO  (GPIO_P5_0_OUTPUT_HIGH | GPIO_OPENDRAIN)

#define BOARD_SCI1_I2C_SCL_GPIO  GPIO_RXD1_MISO1_SCL1_P5_3_M1  /* P53 Mode1 */
#define BOARD_SCI1_I2C_SDA_GPIO  GPIO_TXD1_MOSI1_SDA1_P5_2_M1  /* P52 Mode1 */
#define BOARD_SCI1_I2C_SCL_RESET_GPIO  (GPIO_P5_3_OUTPUT_HIGH | GPIO_OPENDRAIN)
#define BOARD_SCI1_I2C_SDA_RESET_GPIO  (GPIO_P5_2_OUTPUT_HIGH | GPIO_OPENDRAIN)

#define BOARD_SCI2_I2C_SCL_GPIO  GPIO_RXD2_MISO2_SCL2_P5_5_M1  /* P55 Mode1 */
#define BOARD_SCI2_I2C_SDA_GPIO  GPIO_TXD2_MOSI2_SDA2_P5_4_M1  /* P54 Mode1 */
#define BOARD_SCI2_I2C_SCL_RESET_GPIO  (GPIO_P5_5_OUTPUT_HIGH | GPIO_OPENDRAIN)
#define BOARD_SCI2_I2C_SDA_RESET_GPIO  (GPIO_P5_4_OUTPUT_HIGH | GPIO_OPENDRAIN)

#define BOARD_SCI3_I2C_SCL_GPIO  GPIO_RXD3_MISO3_SCL3_P5_7_M1  /* P57 Mode1 */
#define BOARD_SCI3_I2C_SDA_GPIO  GPIO_TXD3_MOSI3_SDA3_P5_6_M1  /* P56 Mode1 */
#define BOARD_SCI3_I2C_SCL_RESET_GPIO  (GPIO_P5_7_OUTPUT_HIGH | GPIO_OPENDRAIN)
#define BOARD_SCI3_I2C_SDA_RESET_GPIO  (GPIO_P5_6_OUTPUT_HIGH | GPIO_OPENDRAIN)

/* RDK-RZV2H exposes only SCI0 in Simple-SPI mode. SCI1-3 require board
 * routing and chip-select definitions before they can be supported.
 */

#if defined(CONFIG_RZV_SCI1_SPI) || defined(CONFIG_RZV_SCI2_SPI) || \
    defined(CONFIG_RZV_SCI3_SPI)
#  error "RDK-RZV2H: SCI Simple-SPI supports SCI0 only"
#endif

/* Ethernet (GBETH0 RGMII) Configuration ************************************/

/* TODO(rzv2h-eth-pins): RGMII pin assignments for GBETH0 on RDK-RZV2H are
 * not yet populated.  boards/arm/rzv/rdk-rzv2h/src/rzv2h_ether.c declares
 * the GPIO_ETH0_* macros as (0) placeholders and skips rzv_gpioconfig()
 * calls until these are confirmed from the RDK-RZV2H board schematic.
 *
 * Once the schematic is available, define the following BOARD_ETH0_*
 * symbols here (using the GPIO_<func>_P<port>_<pin>_M<mode> naming style
 * already used for SPI / SCI / I2C above) and propagate them into
 * rzv2h_ether.c::rzv2h_ether_pinconfig():
 *   BOARD_ETH0_TXD0_GPIO, BOARD_ETH0_TXD1_GPIO, BOARD_ETH0_TXD2_GPIO,
 *   BOARD_ETH0_TXD3_GPIO, BOARD_ETH0_TX_CLK_GPIO, BOARD_ETH0_TX_CTL_GPIO,
 *   BOARD_ETH0_RXD0_GPIO, BOARD_ETH0_RXD1_GPIO, BOARD_ETH0_RXD2_GPIO,
 *   BOARD_ETH0_RXD3_GPIO, BOARD_ETH0_RX_CLK_GPIO, BOARD_ETH0_RX_CTL_GPIO,
 *   BOARD_ETH0_MDC_GPIO,  BOARD_ETH0_MDIO_GPIO
 * Add equivalent BOARD_ETH1_* set if/when GBETH1 is wired on this board.
 */

/* SPI Configuration ********************************************************/

/* SPI bus configuration (per PX4 board_config.h)
 *
 * RSPI0 = single bus for MPU9250 IMU. Single-IMU per RDK-RZ/V2H pinout BOM.
 * P94/SSLA1 is routed but unused (no second IMU wired).
 */

/* Number of SPI buses (must match PX4 board_config.h) */
#define PX4_NUMBER_SPI_BUSES    1

/* RSPI0 for MPU9250 IMU:
 *
 * RSPI0_MOSI: P90 (Mode 1)
 * RSPI0_MISO: P91 (Mode 1)
 * RSPI0_SCK:  P92 (Mode 1)
 * RSPI0_SS0:  P93 (SSLA0, MPU9250 hardware chip-select)
 * RSPI0_SS1:  P94 (SSLA1, routed but unused)
 */

#define BOARD_SPI0_MOSI_GPIO  GPIO_MOSA_P9_0_M1         /* P90 = PORT9 pin 0, Mode1 */
#define BOARD_SPI0_MISO_GPIO  GPIO_MISO4_P9_1_M1        /* P91 = PORT9 pin 1, Mode1 */
#define BOARD_SPI0_SCK_GPIO   GPIO_RSPCK4_P9_2_M1       /* P92 = PORT9 pin 2, Mode1 */
#define BOARD_SPI0_SS0_GPIO   GPIO_SSLA0_P9_3_M1        /* P93 = PORT9 pin 3, Mode1 - MPU9250 */

/* Sensor Configuration *****************************************************/

/* MPU9250 IMU Sensor (RSPI0)
 *
 * Chip select: P93 (RSPI0 SSLA0, hardware CS)
 * Data Ready (DRDY) interrupt: P50 (TINT_ENABLE)
 */

#define BOARD_MPU9250_BUS           0        /* RSPI0 */
#define BOARD_MPU9250_CS_GPIO       GPIO_P9_3_OUTPUT_HIGH  /* P93 chip select */
#define BOARD_MPU9250_DRDY_GPIO     GPIO_P5_0_INPUT  /* P50, TINT */

/* External IRQ configuration for MPU9250 DRDY */
#define BOARD_MPU9250_DRDY_IRQ_ENABLE   1

/* BMP280 Barometer Sensor (I2C7)
 *
 * The BMP280 is connected via I2C bus 7
 * I2C address: 0x76
 * Pins: P76 (SDA7/GPIO02), P77 (SCL7/GPIO03)
 */

#define BOARD_BMP280_BUS            7        /* SCI-mode I2C bus 7 */
#define BOARD_BMP280_ADDR           0x76     /* I2C device address */

/* Sensor bus aliases for driver compatibility */
#define BOARD_IMU_SPI_BUS           BOARD_MPU9250_BUS
#define BOARD_BARO_I2C_BUS          BOARD_BMP280_BUS

/* PWM Configuration ********************************************************/

/* PWM outputs using GPT (General PWM Timer) modules
 *
 * ESC Channel Configuration (from GPIO header pin mapping):
 * - ESC1 (PWM0): PA4 (GPIO12/PWM0) - GPT6A (Mode 11)
 * - ESC2 (PWM1): PA7 (GPIO13/PWM1) - GPT7B (Mode 11)
 * - ESC3 (PWM2): P96 (GPIO19)      - GPT9A (Mode 9)
 * - ESC4 (PWM3): P53 (GPIO06)      - GPT10B (Mode 11)
 */

/* Maximum number of PWM channels (from board_pwm_out.h) */
#define BOARD_PWM_MAX_CHANNELS      4

/* PWM channel GPIO definitions (matching ESC pinmap) */
#define BOARD_PWM_CH0_GPIO      GPIO_GTIOC6A_PA_4_M11  /* ESC1: GPT6A on PA4 */
#define BOARD_PWM_CH1_GPIO      GPIO_GTIOC7B_PA_7_M11  /* ESC2: GPT7B on PA7 */
#define BOARD_PWM_CH2_GPIO      GPIO_GTIOC9A_P9_6_M9   /* ESC3: GPT9A on P96 */
#define BOARD_PWM_CH3_GPIO      GPIO_GTIOC10B_P5_3_M11 /* ESC4: GPT10B on P53 */

/* PWM default parameters (from board_pwm_out.cpp) */
#define BOARD_PWM_DEFAULT_PERIOD_US     20000    /* 20ms period (50Hz) */
#define BOARD_PWM_DEFAULT_MIN_US        900      /* Minimum pulse width */
#define BOARD_PWM_DEFAULT_MAX_US        2100     /* Maximum pulse width */

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

/* Pin configurations
 *
 * These definitions reflect the actual pin assignments used in the
 * PX4 configuration, ensuring compatibility between NuttX and the
 * reference implementation.
 */

/* P5_0 - MPU9250 DRDY with TINT (external interrupt) capability */
#define BOARD_P5_0_GPIO   GPIO_P5_0_INPUT  /* DRDY for IMU sensor */

/* P7_0, P7_1, P7_2, P7_3 - SCI4/SCI5 UART functions (Mode 1) */
#define BOARD_P7_0_GPIO   GPIO_TXD4_MOSI4_SDA4_P7_0_M1  /* SCI4 TX - TFminiPlus (GPIO22) */
#define BOARD_P7_1_GPIO   GPIO_RXD4_MISO4_SCL4_P7_1_M1  /* SCI4 RX - TFminiPlus (GPIO27) */
#define BOARD_P7_2_GPIO   GPIO_TXD5_MOSI5_SDA5_P7_2_M1  /* SCI5 TX - Sik Tel v3 (GPIO14) */
#define BOARD_P7_3_GPIO   GPIO_RXD5_MISO5_SCL5_P7_3_M1  /* SCI5 RX - Sik Tel v3 (GPIO15) */

#define BOARD_P7_4_GPIO	  GPIO_P7_4_OUTPUT_LOW
#define BOARD_P7_5_GPIO   GPIO_RXD6_MISO6_SCL6_P7_5_M1  /* SCI6 RX - fs-a8s (GPIO04) */
#define BOARD_P7_6_GPIO   GPIO_TXD7_MOSI7_SDA7_P7_6_M1  /* I2C7 SDA - BMP280 (GPIO02) */
#define BOARD_P7_7_GPIO   GPIO_RXD7_MISO7_SCL7_P7_7_M1  /* I2C7 SCL - BMP280 (GPIO03) */

/* P8_2, P8_3 - SCI9 UART for GPS M10 (Mode 6) */
#define BOARD_P8_2_GPIO   GPIO_TXD9_MOSI9_SDA9_P8_2_M6  /* SCI9 TX - GPS M10 (GPIO23) */
#define BOARD_P8_3_GPIO   GPIO_RXD9_MISO9_SCL9_P8_3_M6  /* SCI9 RX - GPS M10 (GPIO24) */

/* P9_0..P9_4 - RSPI0 for MPU9250 IMU (Mode 1). P94 unused (single-IMU). */
#define BOARD_P9_0_GPIO   GPIO_MOSA_P9_0_M1   /* RSPI0 MOSI - MPU9250 */
#define BOARD_P9_1_GPIO   GPIO_MISO4_P9_1_M1  /* RSPI0 MISO - MPU9250 */
#define BOARD_P9_2_GPIO   GPIO_RSPCK4_P9_2_M1 /* RSPI0 SCK - MPU9250 */
#define BOARD_P9_3_GPIO   GPIO_SSLA0_P9_3_M1  /* RSPI0 SSLA0 - MPU9250 CS */

/* CAN-FD Pin Configuration *************************************************/

/* RDK-RZV2H CAN-FD channel pin assignments (PSEL=5 for CAN/CANFD function).
 *
 * Channel 0 (RDK "CAN1") — /dev/can0, active under CONFIG_RZV_CANFD0:
 *   CAN1_TXD: P80 = PORT8 pin 0 → CTX0  (GPIO_CTX0_P8_0_M5)
 *   CAN1_RXD: P81 = PORT8 pin 1 → CRX0  (GPIO_CRQ0_P8_1_M5)
 *
 * Channel 1 (RDK "CAN2") — /dev/can1, active under CONFIG_RZV_CANFD1:
 *   CAN2_TXD: P86 = PORT8 pin 6 → CTX3  (GPIO_CTX3_P8_6_M5)
 *   CAN2_RXD: P87 = PORT8 pin 7 → CRX3  (GPIO_CRX3_P8_7_M5)
 */

#define BOARD_CANFD0_TX_GPIO  GPIO_CTX0_P8_0_M5   /* P80 CH0 TX, PSEL=5 */
#define BOARD_CANFD0_RX_GPIO  GPIO_CRQ0_P8_1_M5   /* P81 CH0 RX, PSEL=5 */
#define BOARD_CANFD1_TX_GPIO  GPIO_CTX3_P8_6_M5   /* P86 CH1 TX, PSEL=5 */
#define BOARD_CANFD1_RX_GPIO  GPIO_CRX3_P8_7_M5   /* P87 CH1 RX, PSEL=5 */

#if defined(CONFIG_RZV_SCI1_I2C) && defined(CONFIG_RZV_PWM)
#  error "RDK-RZV2H: RZV_SCI1_I2C (SCL on P5_3 M1) and RZV_PWM (CH3 on P5_3 M11) both drive P5_3. Disable one."
#endif

/* Board Capabilities *******************************************************/

#define BOARD_HAS_LEDS        1
/* RDK-RZV2H has no dedicated user buttons wired to a GPIO header; the
 * NuttX button API is present but reports zero buttons.  See rzv2h_buttons.c.
 */
#define BOARD_HAS_BUTTONS     0
#define BOARD_HAS_I2C         1
#define BOARD_HAS_SPI         1
#define BOARD_HAS_PWM         1
#define BOARD_HAS_ADC         1
#define BOARD_HAS_WATCHDOG    1

/* PX4 Board Configuration Compatibility ************************************/

/* Board UUID for PX4 identification (matching board_config.h) */
#define BOARD_OVERRIDE_UUID   "RZV2H0000000000"  /* 16 characters */


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
