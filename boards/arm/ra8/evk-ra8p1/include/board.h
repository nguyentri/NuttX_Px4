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


/* UART/SCI Pin Definitions */
#define GPIO_SCI0_RX   GPIO_TXD0_A  /* TBD - Telemetry */
#define GPIO_SCI0_TX   GPIO_RXD0_A  /* TBD - Telemetry */

#define GPIO_SCI2_RX   GPIO_TXD2_A  /* TBD - Console */
#define GPIO_SCI2_TX   GPIO_RXD2_A  /* TBD - Console */

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

/* I2C Pin Definitions */
#define GPIO_I2C3_SDA   	GPIO_SDA3_A_1    /* TBD - Expansion I2C */
#define GPIO_I2C3_SCL   	GPIO_SCL3_A_1   /*  TBD - Expansion I2C */

/* LED Pin Definitions */
#define GPIO_LED1       GPIO_PA04_OUTPUT_HIGH  /* TBD - LED1 */
#define GPIO_LED2       GPIO_PA05_OUTPUT_HIGH  /* TBD - LED2 */

/* Button Pin Definitions */
#define GPIO_SW1        	GPIO_IRQ13_P009        /* TBD - User Button */

/* IMU Data Ready Pin */
#define GPIO_IMU_DRDY		GPIO_P409_INPUT_PULLUP /* TBD - ICM20948 Data Ready */

/* Battery Monitoring */
#define GPIO_BATT_VOLT   	GPIO_ADC_AN000 /* TBD - Battery Voltage (5.7:1) */
#define GPIO_BATT_CURR   	GPIO_ADC_AN104 /* TBD - Battery Current (ACS712) */

/* I2C Expansion Bus */
#define GPIO_EXP_SDA     	GPIO_I2C1_SDA  /* TBD - Expansion I2C SDA */
#define GPIO_EXP_SCL     	GPIO_I2C1_SCL  /* TBD - Expansion I2C SCL */

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


#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __ASSEMBLY__ */

#endif /* __BOARDS_ARM_RA8_EVK_RA8P1_INCLUDE_BOARD_H */
