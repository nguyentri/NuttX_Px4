/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/include/board.h
 *
 * SPDX-License-Identifier: Apache-2.0
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

#ifndef __BOARDS_ARM_RA8_EVK_RA8P1_INCLUDE_BOARD_H
#define __BOARDS_ARM_RA8_EVK_RA8P1_INCLUDE_BOARD_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/* Do not include RA8 driver header files here. */

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/



/* UART/SCI Pin Definitions
 * Note: map RX/TX macros to the RA pinmap GPIO_* definitions.
 * The original file had RX/TX swapped for SCI0 and SCI2; use
 * the RA8P1 pinmap names so board code uses the correct pins.
 */
#define GPIO_SCI0_RX   GPIO_RXD0_A  /* Telemetry RX */
#define GPIO_SCI0_TX   GPIO_TXD0_A  /* Telemetry TX */

#define GPIO_SCI2_RX   GPIO_RXD2_A  /* Console RX */
#define GPIO_SCI2_TX   GPIO_TXD2_A  /* Console TX */

#define GPIO_SCI3_RX   GPIO_RXD3_B  /* TBD - RC Input */
#define GPIO_SCI3_TX   GPIO_TXD3_B  /* TBD - RC Input */

/* SPI Pin Definitions for Sensors */
#define GPIO_SPI0_SCK   GPIO_RSPCKA_A_1          /* SPI0 Clock */
#define GPIO_SPI0_MOSI  GPIO_MOSI0_A_1           /* SPI0 MOSI */
#define GPIO_SPI0_MISO  GPIO_MISO0_A_1           /* SPI0 MISO */

#define GPIO_SPI1_SCK   GPIO_RSPCKA_B_1          /* SPI1 Clock */
#define GPIO_SPI1_MOSI  GPIO_MOSI1_B_1           /* SPI1 MOSI */
#define GPIO_SPI1_MISO  GPIO_MISO1_B_1           /* SPI1 MISO */
#define GPIO_SPI1_CS0   GPIO_P408_OUTPUT_HIGH    /* TBD - ICM20948 CS */
#define GPIO_SPI1_CS1   GPIO_P407_OUTPUT_HIGH    /* TBD - BMP388 CS */

/* SPI Slave Select aliases (for compatibility) */
#define GPIO_SPI1_SS0   GPIO_SPI1_CS0            /* TBD - ICM20948 CS */
#define GPIO_SPI1_SS1   GPIO_SPI1_CS1            /* TBD - BMP388 CS */

/* PWM/GPT Timer Pin Definitions for Motor Control */
#define GPIO_GPT0_A     GPIO_GTIOC0A_3         /* TBD- Motor 2 */
#define GPIO_GPT2_A     GPIO_GTIOC2A_2         /* TBD- Motor 3 */
#define GPIO_GPT3_A     GPIO_GTIOC3A_1         /* TBD- Motor 1 */
#define GPIO_GPT4_A     GPIO_GTIOC4A_2         /* TBD- Motor 4 */

/* GPT Channel A Output Pin Definitions (GTIOCA) - default options */
#define GPIO_GPT0_A     GPIO_GTIOC0A_1      /* P2.11 */
#define GPIO_GPT1_A     GPIO_GTIOC10A_1     /* P1.9 */
#define GPIO_GPT2_A     GPIO_GTIOC11A_1     /* P7.11 */
#define GPIO_GPT3_A     GPIO_GTIOC12A_1     /* P7.8 - TBD */
#define GPIO_GPT4_A     GPIO_GTIOC13A_1     /* P5.2 - TBD */
#define GPIO_GPT5_A     GPIO_GTIOC14A_1     /* P5.11 - TBD */
#define GPIO_GPT6_A     GPIO_GTIOC15A_1     /* P7.15 - TBD */
#define GPIO_GPT7_A     GPIO_GTIOC16A_1     /* P6.11 - TBD */
#define GPIO_GPT8_A     GPIO_GTIOC17A_1     /* P6.9 - TBD */
#define GPIO_GPT9_A     GPIO_GTIOC30A_1     /* P1.12 - TBD */
#define GPIO_GPT10_A    GPIO_GTIOC31A_1     /* P8.13 - TBD */
#define GPIO_GPT11_A    GPIO_GTIOC32A_1     /* P9.4 - TBD */
#define GPIO_GPT12_A    GPIO_GTIOC33A_1     /* P9.5 - TBD */
#define GPIO_GPT13_A    GPIO_GTIOC34A_1     /* P8.14 - TBD */

/* GPT Channel B Output Pin Definitions (GTIOCB) - default options */
#define GPIO_GPT0_B                    GPIO_GTIOC0B_1      /* P2.10 */
#define GPIO_GPT1_B      GPIO_GTIOC10B_1     /* P1.8 */
#define GPIO_GPT2_B      GPIO_GTIOC11B_1     /* P7.10 */
#define GPIO_GPT3_B      GPIO_GTIOC12B_1     /* P7.9 - TBD */
#define GPIO_GPT4_B      GPIO_GTIOC13B_1     /* P5.1 - TBD */
#define GPIO_GPT5_B      GPIO_GTIOC14B_1     /* P5.10 - TBD */
#define GPIO_GPT6_B      GPIO_GTIOC15B_1     /* P7.14 - TBD */
#define GPIO_GPT7_B      GPIO_GTIOC16B_1     /* P6.10 - TBD */
#define GPIO_GPT8_B      GPIO_GTIOC17B_1     /* P6.8 - TBD */
#define GPIO_GPT9_B      GPIO_GTIOC30B_1     /* P1.11 - TBD */
#define GPIO_GPT10_B     GPIO_GTIOC31B_1     /* P8.12 - TBD */
#define GPIO_GPT11_B     GPIO_GTIOC32B_1     /* P9.6 - TBD */
#define GPIO_GPT12_B     GPIO_GTIOC33B_1     /* P9.7 - TBD */
#define GPIO_GPT13_B     GPIO_GTIOC34B_1     /* P8.15 - TBD */

/* I2C Pin Definitions */
#define GPIO_I2C3_SDA   	GPIO_SDA3_A_1    /* TBD - Expansion I2C */
#define GPIO_I2C3_SCL   	GPIO_SCL3_A_1   /*  TBD - Expansion I2C */

/* LED Pin Definitions */
#define GPIO_LED1       GPIO_PA04_OUTPUT_HIGH  /* TBD - LED1 */
#define GPIO_LED2       GPIO_PA05_OUTPUT_HIGH  /* TBD - LED2 */

/* FSP-labelled LEDs */
/* USER_LED_GREEN  -> BSP_IO_PORT_03_PIN_03 */
#define GPIO_USER_LED_GREEN    GPIO_P303_OUTPUT_HIGH
/* USER_LED_BLUE   -> BSP_IO_PORT_06_PIN_00 */
#define GPIO_USER_LED_BLUE     GPIO_P600_OUTPUT_HIGH
/* USER_LED_RED    -> BSP_IO_PORT_10_PIN_07 */
#define GPIO_USER_LED_RED      GPIO_PA07_OUTPUT_HIGH /* PORT10 PIN7 alias is PA07 */

/* Button Pin Definitions */
#define GPIO_SW1        	GPIO_IRQ13_P009        /* TBD - User Button (USER_SW1 BSP_IO_PORT_00_PIN_09) */

/* FSP-labelled user switches */
/* USER_SW_CFG_INT -> BSP_IO_PORT_00_PIN_00 */
#define GPIO_USER_SW_CFG_INT  GPIO_P000_INPUT /* PORT0 PIN0 - raw input (no IRQ defined) */
/* USER_SW2 -> BSP_IO_PORT_00_PIN_08 */
#define GPIO_USER_SW2         GPIO_P008_INPUT_PULLUP

/* IMU Data Ready Pin */
#define GPIO_IMU_DRDY		GPIO_P409_INPUT_PULLUP /* TBD - ICM20948 Data Ready */

/* SPI sensor chip selects (FSP labels map to physical pins) */
/* OSPI / sensor CS examples kept as existing GPIO_P408/407 */

/* Battery Monitoring */
#define GPIO_BATT_VOLT   	GPIO_ADC_AN000 /* TBD - Battery Voltage (5.7:1) */
#define GPIO_BATT_CURR   	GPIO_ADC_AN104 /* TBD - Battery Current (ACS712) */

/* Map FSP analog labels to ra_pinmap analog macros where known */
/* ARDUINO_AN0 -> BSP_IO_PORT_00_PIN_01 -> PORT0 PIN1 -> use GPIO_P001_ANALOG */
#define GPIO_ARDUINO_AN0     GPIO_P001_ANALOG
/* GROVE2_AN0 -> BSP_IO_PORT_00_PIN_02 -> PORT0 PIN2 not listed as analog in ra_pinmap; keep as input */
#define GPIO_GROVE2_AN0       GPIO_P002_INPUT

/* I2C pins (FSP labels) */
/* I3C_SCL -> BSP_IO_PORT_04_PIN_00  */
#define GPIO_I3C_SCL_FSP      GPIO_I3C_SCL0_1
/* I3C_SDA -> BSP_IO_PORT_04_PIN_01 */
#define GPIO_I3C_SDA_FSP      GPIO_SDA1_A_1

/* I2C Expansion Bus */
#define GPIO_EXP_SDA     	GPIO_I2C1_SDA  /* TBD - Expansion I2C SDA */
#define GPIO_EXP_SCL     	GPIO_I2C1_SCL  /* TBD - Expansion I2C SCL */

/* ADC Analog Input Pins
 * NOTE: The ADC-B module uses voltage dividers and sensor inputs:
 * - Battery Voltage: 5.7:1 divider on P004 (AN000) - reads 0-25.65V range
 * - Battery Current: ACS712 current sensor on P005 (AN104)
 * - Arduino AN0: Expansion connector on P001 (AN001)
 * - Grove2 AN0: Analog input on P002 (if available, P002_ANALOG)
 */

/* ADC channel definitions for battery monitoring and expansion */
#define ADC_BATT_VOLTAGE_CHANNEL   0    /* AN000 - Battery voltage divider input */
#define ADC_BATT_CURRENT_CHANNEL   104  /* AN104 - ACS712 current sensor input */
#define ADC_ARDUINO_CHANNEL        1    /* AN001 - Arduino expansion analog */
#define ADC_GROVE2_CHANNEL         2    /* AN002 - Grove2 expansion analog (if supported) */

/* These LEDs are not used by the board port unless CONFIG_ARCH_LEDS is
 * defined. In that case, the usage by the board port is defined in
 * include/board.h and src/ra8p1_auto_leds.c. The LEDs are used to encode
 * OS-related events as follows:
 *
 *  SYMBOL                		MEANING               LED STATE
 *                                                      	 LED1   LED2
 *  -----------------------  --------------------------  ----  ----
 */
#define LED_STARTED       	0  /* NuttX has been started     OFF   OFF  */
#define LED_HEAPALLOCATE  	0  /* Heap has been allocated    OFF   OFF  */
#define LED_IRQSENABLED   	0  /* Interrupts enabled         OFF   OFF  */
#define LED_STACKCREATED  	1  /* Idle stack created         ON    OFF  */
#define LED_INIRQ         	2  /* In an interrupt            N/C   ON   */
#define LED_SIGNAL        	2  /* In a signal handler        N/C   ON   */
#define LED_ASSERTION     	2  /* An assertion failed        N/C   ON   */
#define LED_PANIC         	3  /* The system has crashed     N/C   BLINK */
#define LED_IDLE          	3  /* MCU is in sleep mode       ----  Not used ---- */

/* Board LED Definitions */
#define LED_1         		0
#define LED_2         		1
#define NLEDS         		2

/* LED bits for use with board_userled_all() */
#define LED_1_BIT    		(1 << LED_1)
#define LED_2_BIT    		(1 << LED_2)


/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifndef __ASSEMBLY__

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/**
 * Name: board_gpt_initialize
 *
 * Description:
 *   Initialize GPT (General Purpose Timer) PWM devices.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on any failure.
 */
#ifdef CONFIG_PWM
int board_gpt_initialize(void);
#endif

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __ASSEMBLY__ */

#endif /* __BOARDS_ARM_RA8_EVK_RA8P1_INCLUDE_BOARD_H */
