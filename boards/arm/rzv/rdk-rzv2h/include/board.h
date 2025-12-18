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

/* SCI1 is used as the default NSH console interface:
 *
 * SCI1_TXD: P38 (TXD1 - Mode 1)
 * SCI1_RXD: P39 (RXD1 - Mode 1)
 *
 * This provides serial communication via the onboard USB-to-UART converter
 * or can be connected to external devices.
 */

#define BOARD_CONSOLE_UART        1       /* Use SCI1 for console */
#define BOARD_CONSOLE_BAUD        115200
#define BOARD_CONSOLE_BITS        8
#define BOARD_CONSOLE_PARITY      0
#define BOARD_CONSOLE_2STOP       0

/* SCI UART pin definitions using canonical pinmap macros */

/* SCI1 pins for NSH console (default) */

#define BOARD_SCI1_TXD_GPIO   GPIO_TXD1_MOSI1_SDA1_P5_2_M1    /* P52 = PORT5 pin 2, Mode1 */
#define BOARD_SCI1_RXD_GPIO   GPIO_RXD1_MISO1_SCL1_P5_3_M1    /* P53 = PORT5 pin 3, Mode1 */

/* SCI0 pins (alternative UART interface) */

#define BOARD_SCI0_TXD_GPIO   GPIO_TXD0_MOSI0_DA0_P5_0_M1    /* P50 = PORT5 pin 0, Mode1 */
#define BOARD_SCI0_RXD_GPIO   GPIO_RXD0_MISO0_SCL0_P5_1_M1    /* P51 = PORT5 pin 1, Mode1 */


/* I2C Configuration ********************************************************/

/* RIIC (Renesas I2C) Configuration - Legacy naming kept for compatibility */

/* RIIC2 pins via Pmod Type6 I2C connector (CN6):
 *
 * I2C2_SDA (RIIC2): P20 (SDA2 - Mode 4)
 * I2C2_SCL (RIIC2): P21 (SCL2 - Mode 4)
 *
 * Also used for PCIe slot and DA7212 audio codec on EXP board
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

/* Default I2C bus for sensors/expansion (RIIC0 recommended for GY-912) */

#define BOARD_I2C_SENSOR_BUS  0  /* Use RIIC0 for sensor expansion */

/* SPI Configuration ********************************************************/

/* SPI0 (Pmod Type2 SPI connector CN2):
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

/* PWM Configuration ********************************************************/

/* PWM outputs using GPT timers (examples - update based on actual usage):
 *
 * PWM0 (GTIOC0A): P40 (Mode 9) - example
 * Note: EVK uses various GTIOC pins; update based on specific requirements
 */

#define BOARD_PWM0_GPIO       GPIO_GTIOC0A_P4_0_M9    /* P40 = PORT4 pin 0, Mode9 */

/* ADC Configuration ********************************************************/

/* ADC input channels:
 *
 * ADC0_CH0: AN000 (Analog input)
 * ADC0_CH1: AN001 (Analog input)
 * ADC0_CH2: AN002 (Analog input)
 * ADC0_CH3: AN003 (Analog input)
 */

#define BOARD_ADC_NCHANNELS   4

/* GPIO Pins ***********************************************************/

/* P1_4 - configured as input with noise filter and TINT in FSP */
/* Use canonical pinmap name for P1_4 input */
#define BOARD_P1_4_GPIO   GPIO_P1_4_INPUT_PULLUP

/* P2_0 and P2_1 - peripheral function mode4 in FSP */
/* Use mode-specific canonical pinmap names */
#define BOARD_P2_0_GPIO   GPIO_SDA2_P2_0_M4
#define BOARD_P2_1_GPIO   GPIO_SCL2_P2_1_M4

/* P3_4 and P3_5 - peripheral function mode2 (fast slew) */
/* Use canonical mode2 pin names (TXD/RXD style) */
#define BOARD_P3_4_GPIO   GPIO_TXD_MOSI4_SDA3_P3_4_M2
#define BOARD_P3_5_GPIO   GPIO_RXD_MISO3_SCL3_P3_5_M2

/* P3_6 - peripheral function mode5 */
/* Use canonical mode5 pin name */
#define BOARD_P3_6_GPIO   GPIO_SSLA2_P3_6_M5

/* P3_7 - peripheral function mode9 (slow slew) */
/* Use canonical GTIOC/GTETR mode9 macro */
#define BOARD_P3_7_GPIO   GPIO_GTIOC7B_P3_7_M9

/* P4_0 and P4_6 - peripheral function mode9 (slow slew) */
/* Use canonical GTIOC mode9 macros */
#define BOARD_P4_0_GPIO   GPIO_GTIOC0A_P4_0_M9
#define BOARD_P4_6_GPIO   GPIO_GTIOC3A_P4_6_M9

/* P5_3 - peripheral function mode1 (fast slew) */
/* Use RXD/MISO style canonical macro for mode1 */
#define BOARD_P5_3_GPIO   GPIO_RXD1_MISO1_SCL1_P5_3_M1

/* P6_3 - peripheral function mode11 (slow slew) */
/* Use GTIOC11B mode11 macro */
#define BOARD_P6_3_GPIO   GPIO_GTIOC11B_P6_3_M11

/* P9_0, P9_1, P9_2 - peripheral function mode1 (fast slew) */
/* Use canonical SPI/UART mode1 macros where appropriate */
#define BOARD_P9_0_GPIO   GPIO_MOSA_P9_0_M1
#define BOARD_P9_1_GPIO   GPIO_MISO4_P9_1_M1
#define BOARD_P9_2_GPIO   GPIO_RSPCK4_P9_2_M1

/* P6_0 - used by FSP event config as output (map as GPIO output low) */
/* Use canonical P6_0 output low macro */
#define BOARD_P6_0_GPIO   GPIO_P6_0_OUTPUT_LOW

/* LED pins from FSP board_leds.c: provide aliases to existing NuttX LED macros
 * NuttX `board.h` already defines BOARD_LED1_GPIO = GPIO_P0_0_OUTPUT_HIGH etc.
 * Add explicit aliases for clarity. */
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

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __BOARDS_ARM_RZV2H_RZV2H_EVK_INCLUDE_BOARD_H */