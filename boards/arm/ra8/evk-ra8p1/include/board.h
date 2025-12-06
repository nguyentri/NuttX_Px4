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

/****************************************************************************************************
 * Memory Configuration
 ****************************************************************************************************/

/* MRAM (Magnetoresistive RAM) - Non-volatile memory used as code flash */
#define BOARD_FLASH_SIZE                (1 * 1024 * 1024)  /* 1MB MRAM */
#define BOARD_FLASH_SECTORS             256                /* 4KB sectors */

/* SRAM */
#define BOARD_RAM_SIZE                  (2 * 1024 * 1024)  /* 2MB SRAM with ECC */

/* MRAM Configuration */
#define BOARD_MRAM_CODE_BASE            0x02000000
#define BOARD_MRAM_CODE_SIZE            0x000F0000  /* 1MB - 64KB (960KB code) */
#define BOARD_MRAM_DATA_BASE            0x020F0000  /* Last 64KB for params */
#define BOARD_MRAM_DATA_SIZE            0x00010000  /* 64KB */
#define BOARD_MRAM_WRITE_SIZE           32          /* 32 bytes per write */
#define BOARD_MRAM_BLOCK_SIZE           4096        /* 4KB sectors */

/* External Octo-SPI Flash */
#define BOARD_OSPI_FLASH_BASE           0x80000000  /* Octo-SPI CS0 */
#define BOARD_OSPI_FLASH_SIZE           (64 * 1024 * 1024)  /* 64MB (512Mb) */
#define BOARD_OSPI_FLASH_SECTOR_SIZE    4096        /* 4KB sectors */

/* Mass Storage Configuration */
#define BOARD_HAS_NO_SDCARD             1  /* No SD card slot */

/****************************************************************************
 * UART/SCI Pin Definitions
 ****************************************************************************/

/* SCI2 - NSH Console (Pmod 1 UART: P802=RXD2, P801=TXD2/MOSI2)
 * ⚠️  CONFLICT: Shares pins with Pmod 1 SPI and OSPI DQS/SIO6!
 * Hardware: Usually hardwired to USB-Serial converter
 * Resolution: This is the default console. To use Pmod 1 SPI,
 *             redirect console to SCI0 or SCI7.
 */
#define GPIO_SCI2_RX   GPIO_RXD2_B  /* P802 - Console RX ⚠️ Conflicts: MISO2, OSPI_SIO6 */
#define GPIO_SCI2_TX   GPIO_TXD2_B  /* P801 - Console TX ⚠️ Conflicts: MOSI2, OSPI_DQS */

/* SCI0 - Pmod 2 UART (P602=RXD0/MISOB, P603=TXD0/MOSIB)
 * ⚠️  CONFLICT: Shares pins with Pmod 2 SPI!
 * Use Case: Alternate console location when SCI2 is used for Pmod 1 SPI
 */
#define GPIO_SCI0_RX   GPIO_RXD0_B  /* P602 - Pmod 2 RX ⚠️ Conflicts: MISO0 */
#define GPIO_SCI0_TX   GPIO_TXD0_B  /* P603 - Pmod 2 TX ⚠️ Conflicts: MOSI0 */

/* SCI7 - Arduino/mikroBUS UART (P808=RXD7, P809=TXD7)
 * ✓ SAFE: No major conflicts
 * Use Case: Alternate console location or Arduino/mikroBUS communication
 */
#define GPIO_SCI7_RX   GPIO_RXD7_A  /* P808 - Arduino D0/mikroBUS RX ✓ SAFE */
#define GPIO_SCI7_TX   GPIO_TXD7_A  /* P809 - Arduino D1/mikroBUS TX ✓ SAFE */

/****************************************************************************
 * SPI Pin Definitions
 ****************************************************************************/

/* SPI0 (Pmod 2): P601=RSPCKB, P602=MISOB, P603=MOSIB, P604=SSLB0
 * ⚠️  CONFLICT: P602/P603 shared with SCI0 UART
 * ⚠️  CONFLICT: P601 can conflict with OSPI_WP1 (write protect)
 */
#define GPIO_SPI0_SCK   GPIO_RSPCKA_B_1        /* P601 - Pmod 2 SCK ⚠️ Conflicts: OSPI_WP1 */
#define GPIO_SPI0_MISO  GPIO_MISO0_B_1         /* P602 - Pmod 2 MISO ⚠️ Conflicts: RXD0 */
#define GPIO_SPI0_MOSI  GPIO_MOSI0_B_2         /* P603 - Pmod 2 MOSI ⚠️ Conflicts: TXD0 */
#define GPIO_SPI0_CS0   GPIO_SSLB0_A_1         /* P604 - Pmod 2 CS ✓ SAFE */

/* SPI1 (Pmod 1): P803=SCK2, P802=MISO2, P801=MOSI2, P804=SS2
 * ⚠️  SEVERE CONFLICT: P801/P802 conflict with SCI2 console UART!
 * ⚠️  SEVERE CONFLICT: All pins conflict with OSPI flash signals!
 */
#define GPIO_SPI1_SCK   GPIO_RSPCKA_C_1        /* P803 - Pmod 1 SCK ⚠️ Conflicts: OSPI_SIO1 */
#define GPIO_SPI1_MISO  GPIO_MISO2_A_1         /* P802 - Pmod 1 MISO ⚠️ Conflicts: RXD2, OSPI_SIO6 */
#define GPIO_SPI1_MOSI  GPIO_MOSI2_A_1         /* P801 - Pmod 1 MOSI ⚠️ Conflicts: TXD2, OSPI_DQS */
#define GPIO_SPI1_CS0   GPIO_SSLE2_A_1         /* P804 - Pmod 1 CS ⚠️ Conflicts: OSPI_SIO7 */

/* Arduino SPI (P100=MISOB, P101=MOSIB, P102=RSPCKB, P103=SSLB0)
 * ⚠️  SEVERE CONFLICT: These pins conflict with OSPI Flash!
 * Pin Conflicts (Hardware jumpers may control):
 *   P100: MISO (D12) ⚡ OSPI_SIO0 ⚡ GPT8B
 *   P101: MOSI (D11) ⚡ OSPI_SIO3 ⚡ GPT8A
 *   P102: SCK  (D13) ⚡ OSPI_SIO4 ⚡ GPT2B
 *   P103: CS0  (D10) ⚡ OSPI_SIO2 ⚡ GPT2A
 *   P110: CS1  (D9)  ⚡  GPT9B
 */
#define GPIO_ARDUINO_SPI_SCK   GPIO_RSPCKA_B_1      /* P102 - Arduino D13 ⚠️ Conflicts: OSPI_SIO4, GPT2B */
#define GPIO_ARDUINO_SPI_MISO  GPIO_MISOB_A_1       /* P100 - Arduino D12 ⚠️ Conflicts: OSPI_SIO0, GPT8B */
#define GPIO_ARDUINO_SPI_MOSI  GPIO_MOSIB_A_1       /* P101 - Arduino D11 ⚠️ Conflicts: OSPI_SIO3, GPT8A */
#define GPIO_ARDUINO_SPI_CS0   GPIO_SSLB0_A_1       /* P103 - Arduino D10 ⚠️ Conflicts: OSPI_SIO2, GPT2A */
#define GPIO_ARDUINO_SPI_CS1   GPIO_P110_OUTPUT_HIGH    /* P110 - repurposed for another CS   ⚠️ Conflicts: GPT9B */


/****************************************************************************
 * PWM/GPT Pin Definitions
 *
 * This section includes ALL available GPT pins, including those from
 * parallel graphics connector (not used in NuttX).
 *
 * Conflict-Free PWM Pins (✓ SAFE):
 * ========================================================

 * PWM1:   GPIO_GPT3_A     (P912) - GPT3A  ✓
 * PWM2:   GPIO_GPT3_B     (P911) - GPT3B  ✓
 * PWM3:   GPIO_GPT5_A     (P915) - GPT5A  ✓
 * PWM4:   GPIO_GPT5_B     (P914) - GPT5B  ✓
 * PWM5:   GPIO_GPT10_A    (P810) - GPT10A ✓ Arduino D4
 * PWM6:   GPIO_GPT10_B    (P811) - GPT10B ✓ Arduino D3
 * PWM7:   GPIO_GPT11_A    (P903) - GPT11A ✓
 * PWM8:   GPIO_GPT11_B    (P904) - GPT11B ✓
 * PWM9:   GPIO_GPT12_A    (P715) - GPT12A ✓
 * PWM10:  GPIO_GPT12_B    (P714) - GPT12B ✓
 * PWM11:  GPIO_GPT13_A    (P515) - GPT13A ✓
 * PWM12:  GPIO_GPT13_B    (P514) - GPT13B ✓
 *
 * PWM Pins with Conflicts (use with caution):
 * ===========================================
 * ⚠️ GPT1A/B  (P105/P104)   - Conflicts: OSPI_ECS/CS0
 * ⚠️ GPT2A/B  (P103/P102 or P713/P712) - P103/P102 conflict with Arduino SPI & OSPI
 * ⚠️ GPT4A/B  (P205/P301)   - P301 conflicts with SDRAM
 * ⚠️ GPT6A/B  (P400/P401)   - Conflicts with I2C0
 * ⚠️ GPT7B    (P303)        - Conflicts with Green LED
 * ⚠️ GPT8A/B  (P101/P100)   - Conflicts with Arduino SPI & OSPI
 ****************************************************************************/

/* GPT Channel A Output Pins */
#define GPIO_PWM_GPT1_A_1     GPIO_GTIOC1A_1      /* P105 ⚠️ Arduino D6, OSPI_ECS */
#define GPIO_PWM_GPT2_A_1     GPIO_GTIOC2A_1      /* P103 ⚠️ Arduino D10, OSPI_SIO2, SPI CS */
#define GPIO_PWM_GPT2_A_3     GPIO_GTIOC2A_3      /* P713 ✓ From parallel graphics */
#define GPIO_PWM_GPT3_A_2     GPIO_GTIOC3A_2      /* P912 ✓ From parallel graphics */
#define GPIO_PWM_GPT4_A_1     GPIO_GTIOC4A_1      /* P205 ✓ SAFE */
#define GPIO_PWM_GPT5_A_3     GPIO_GTIOC5A_4      /* P915 ✓ From parallel graphics */
#define GPIO_PWM_GPT6_A_1     GPIO_GTIOC6A_1      /* P400 ⚠️ I2C0_SCL, CAM_D2 */
#define GPIO_PWM_GPT7_A_1     GPIO_GTIOC7A_1      /* P304 ⚠️ Ethernet TXD3 */
#define GPIO_PWM_GPT8_A_1     GPIO_GTIOC8A_1      /* P101 ⚠️ Arduino D11, OSPI_SIO3, SPI MOSI */
#define GPIO_PWM_GPT9_A_1     GPIO_GTIOC9A_1      /* PB06 ✓ From parallel graphics */
#define GPIO_PWM_GPT10_A_2    GPIO_GTIOC10A_2     /* P810 ✓ Arduino D4, mikroBUS PWM */
#define GPIO_PWM_GPT11_A_1    GPIO_GTIOC11A_1     /* P711 ✓ From parallel graphics (legacy) */
#define GPIO_PWM_GPT11_A_4    GPIO_GTIOC11A_4     /* P903 ✓ From parallel graphics */
#define GPIO_PWM_GPT12_A_1    GPIO_GTIOC12A_1     /* P715 ✓ From parallel graphics */
#define GPIO_PWM_GPT13_A_1    GPIO_GTIOC13A_1     /* P515 ✓ NO CONFLICTS */

/* GPT Channel B Output Pins */
#define GPIO_PWM_GPT1_B_1     GPIO_GTIOC1B_1      /* P104 ⚠️ Arduino D5, OSPI_CS0 */
#define GPIO_PWM_GPT2_B_1     GPIO_GTIOC2B_1      /* P102 ⚠️ Arduino D13, OSPI_SIO4, SPI SCK */
#define GPIO_PWM_GPT2_B_2     GPIO_GTIOC2B_3      /* P712 ✓ From parallel graphics */
#define GPIO_PWM_GPT3_B_3     GPIO_GTIOC3B_3      /* P911 ✓ From parallel graphics */
#define GPIO_PWM_GPT4_B_1     GPIO_GTIOC4B_1      /* P301 ⚠️ SDRAM_DQ1 */
#define GPIO_PWM_GPT5_B_4     GPIO_GTIOC5B_4      /* P914 ✓ From parallel graphics */
#define GPIO_PWM_GPT6_B_1     GPIO_GTIOC6B_1      /* P401 ⚠️ I2C0_SDA */
#define GPIO_PWM_GPT7_B_1     GPIO_GTIOC7B_1      /* P303 ⚠️ Green LED */
#define GPIO_PWM_GPT8_B_1     GPIO_GTIOC8B_1      /* P100 ⚠️ Arduino D12, OSPI_SIO0, SPI MISO */
#define GPIO_PWM_GPT9_B_1     GPIO_GTIOC9B_1      /* PB07 ✓ From parallel graphics */
#define GPIO_PWM_GPT10_B_2    GPIO_GTIOC10B_2     /* P811 ✓ Arduino D3 */
#define GPIO_PWM_GPT11_B_4    GPIO_GTIOC11B_4     /* P904 ✓ From parallel graphics */
#define GPIO_PWM_GPT12_B_1    GPIO_GTIOC12B_1     /* P714 ✓ From parallel graphics */
#define GPIO_PWM_GPT13_B_2    GPIO_GTIOC13B_2     /* P514 ✓ NO CONFLICTS */

/* Arduino PWM Pins (for Arduino shield compatibility) */
#define GPIO_ARDUINO_D3_PWM   GPIO_GTIOC10B_2   /* P811 ✓ SAFE */
#define GPIO_ARDUINO_D4_PWM   GPIO_GTIOC10A_2   /* P810 ✓ SAFE */
#define GPIO_ARDUINO_D5_PWM   GPIO_GTIOC1B_1    /* P104 ⚠️ OSPI_CS0 */
#define GPIO_ARDUINO_D6_PWM   GPIO_GTIOC1A_1    /* P105 ⚠️ OSPI_ECS */
#define GPIO_ARDUINO_D9_PWM   GPIO_GTIOC9B_1    /* P110 ⚠️ SPI_CS1 */
#define GPIO_ARDUINO_D10_PWM  GPIO_GTIOC2A_1    /* P103 ⚠️ SPI_CS0, OSPI_SIO2 */
#define GPIO_ARDUINO_D11_PWM  GPIO_GTIOC8A_1    /* P101 ⚠️ SPI_MOSI, OSPI_SIO3 */
#define GPIO_ARDUINO_D12_PWM  GPIO_GTIOC8B_1    /* P100 ⚠️ SPI_MISO, OSPI_SIO0 */

/* mikroBUS PWM Pin */
#define GPIO_MIKROBUS_PWM     GPIO_GTIOC10A_2   /* P810 ✓ SAFE */

/* Motor PWM Configuration using GPT channels
 * Motor 1: P912 (GPT3A)
 * Motor 2: P915 (GPT5A)
 * Motor 3: P903 (GPT11A
 * Motor 4: P515 (GPT13A
 *
 * Note: Pin assignments verified from RA8P1 pinmap for ESC control
 */
#define GPIO_TIM3_CH1OUT     GPIO_PWM_GPT3_A_2     /* P912 - GPT3A - Motor 1 */
#define GPIO_TIM5_CH1OUT     GPIO_PWM_GPT5_A_3     /* P915 - GPT5A - Motor 2 */
#define GPIO_TIM11_CH1OUT    GPIO_PWM_GPT11_A_4    /* P903 - GPT11A - Motor 3 */
#define GPIO_TIM13_CH1OUT    GPIO_PWM_GPT13_A_1    /* P515 - GPT13A - Motor 4 */

/****************************************************************************
 * I2C Pin Definitions
 ****************************************************************************/

/* I2C0/I3C (P400=SCL0, P401=SDA0) - Grove 1, Qwiic, Arduino, mikroBUS
 * ⚠️  CONFLICT: P400/P401 conflict with GPT6A/B and Camera data pins
 * Resolution: I2C0 takes priority over GPT6
 */
#define GPIO_I2C0_SCL        GPIO_SCL0_B_1   /* P400 ⚠️ Conflicts: GPT6A, CAM_D2 */
#define GPIO_I2C0_SDA        GPIO_SDA0_B_1   /* P401 ⚠️ Conflicts: GPT6B */
#define GPIO_I3C_SCL         GPIO_I3C_SCL0_1 /* P400 - I3C SCL (same pin as I2C0) */
#define GPIO_I3C_SDA         GPIO_SDA0_B_1   /* P401 - I3C SDA (same pin as I2C0) */

/* I2C1 (P512=SCL1, P511=SDA1) - Grove 2, Camera Port, Qwiic
 * ✓ SAFE: Can be shared between multiple devices with unique addresses
 */
#define GPIO_I2C1_SCL        GPIO_SCL1_A_2   /* P512 ✓ Shared: Grove2, Camera, Qwiic */
#define GPIO_I2C1_SDA        GPIO_SDA1_B_1   /* P511 ✓ Shared: Grove2, Camera, Qwiic */

/* Grove Connectors */
#define GPIO_GROVE1_SCL_I2C0  GPIO_I2C0_SCL  /* P400 - Grove 1 on I2C0 */
#define GPIO_GROVE1_SDA_I2C0  GPIO_I2C0_SDA  /* P401 - Grove 1 on I2C0 */
#define GPIO_GROVE1_SCL_I2C1  GPIO_I2C1_SCL  /* P512 - Grove 1 on I2C1 (alternate) */
#define GPIO_GROVE1_SDA_I2C1  GPIO_I2C1_SDA  /* P511 - Grove 1 on I2C1 (alternate) */

#define GPIO_GROVE2_SCL       GPIO_I2C1_SCL  /* P512 - Grove 2 I2C */
#define GPIO_GROVE2_SDA       GPIO_I2C1_SDA  /* P511 - Grove 2 I2C */
#define GPIO_GROVE2_AN0       GPIO_P002_ANALOG /* P002 - Grove 2 analog option */
#define GPIO_GROVE2_AN1       GPIO_P005_ANALOG /* P005 - Grove 2 analog option */

/* Qwiic Connector (supports both I2C0 and I2C1) */
#define GPIO_QWIIC_SCL_I2C0   GPIO_I2C0_SCL  /* P400 - Qwiic on I2C0 */
#define GPIO_QWIIC_SDA_I2C0   GPIO_I2C0_SDA  /* P401 - Qwiic on I2C0 */
#define GPIO_QWIIC_SCL_I2C1   GPIO_I2C1_SCL  /* P512 - Qwiic on I2C1 */
#define GPIO_QWIIC_SDA_I2C1   GPIO_I2C1_SDA  /* P511 - Qwiic on I2C1 */

/* Arduino I2C (supports both I2C0 and I2C1) */
#define GPIO_ARDUINO_SCL_I2C0 GPIO_I2C0_SCL  /* P400 - Arduino I2C on I2C0 */
#define GPIO_ARDUINO_SDA_I2C0 GPIO_I2C0_SDA  /* P401 - Arduino I2C on I2C0 */
#define GPIO_ARDUINO_SCL_I2C1 GPIO_I2C1_SCL  /* P512 - Arduino I2C on I2C1 */
#define GPIO_ARDUINO_SDA_I2C1 GPIO_I2C1_SDA  /* P511 - Arduino I2C on I2C1 */

/* mikroBUS I2C (supports both I2C0 and I2C1) */
#define GPIO_MIKROBUS_SCL_I2C0 GPIO_I2C0_SCL /* P400 - mikroBUS on I2C0 */
#define GPIO_MIKROBUS_SDA_I2C0 GPIO_I2C0_SDA /* P401 - mikroBUS on I2C0 */
#define GPIO_MIKROBUS_SCL_I2C1 GPIO_I2C1_SCL /* P512 - mikroBUS on I2C1 */
#define GPIO_MIKROBUS_SDA_I2C1 GPIO_I2C1_SDA /* P511 - mikroBUS on I2C1 */

/* Camera I2C */
#define GPIO_CAMERA_SCL       GPIO_I2C1_SCL  /* P512 - Camera I2C SCL */
#define GPIO_CAMERA_SDA       GPIO_I2C1_SDA  /* P511 - Camera I2C SDA */

/****************************************************************************
 * LED Pin Definitions
 ****************************************************************************/

/* User LEDs */
#define GPIO_USER_LED_BLUE    GPIO_P600_OUTPUT_HIGH  /* P600 ✓ NO CONFLICTS */
#define GPIO_USER_LED_GREEN   GPIO_P303_OUTPUT_HIGH  /* P303 ⚠️ Conflicts: GPT7B */
#define GPIO_USER_LED_RED     GPIO_PA07_OUTPUT_HIGH  /* PA07 ✓ NO CONFLICTS */

/* LED Aliases */
#define GPIO_LED1             GPIO_USER_LED_BLUE
#define GPIO_LED2             GPIO_USER_LED_GREEN
#define GPIO_LED3             GPIO_USER_LED_RED

/****************************************************************************
 * Button and Switch Pin Definitions
 ****************************************************************************/

/* User Switches */
#define GPIO_USER_SW1         GPIO_IRQ13_P009_DS      /* P009 - SW1 (IRQ13-DS) */
#define GPIO_USER_SW2         GPIO_P008_INPUT_PULLUP  /* P008 - SW2 (IRQ12-DS) */

/* Button Aliases */
#define GPIO_SW1              GPIO_USER_SW1
#define GPIO_SW2              GPIO_USER_SW2

/* Interrupt Pins */
#define GPIO_ARDUINO_D2_INT   GPIO_IRQ16_P011   /* P011 - Arduino D2 (IRQ16) */
#define GPIO_ARDUINO_D3_INT   GPIO_IRQ22_P811   /* P811 - Arduino D3 (IRQ22) */
#define GPIO_MIKROBUS_INT     GPIO_IRQ22_PD01   /* PD01 - mikroBUS INT (IRQ22) */
#define GPIO_CAMERA_INT       GPIO_IRQ14_P010   /* P010 - Camera INT (IRQ14) */
#define GPIO_PMOD1_IRQ        GPIO_P006_INPUT_PULLUP /* P006 - Pmod 1 IRQ (IRQ11-DS) */
#define GPIO_PMOD2_IRQ        GPIO_IRQ15_P012   /* P012 - Pmod 2 IRQ (IRQ15) */

/****************************************************************************
 * Analog Input Pin Definitions (ADC)
 ****************************************************************************/

/* Arduino Analog Inputs */
#define GPIO_ARDUINO_A0       GPIO_P001_ANALOG  /* P001 (AN001) */
#define GPIO_ARDUINO_A1       GPIO_P007_ANALOG  /* P007 (AN007) */
#define GPIO_ARDUINO_A2       GPIO_P003_ANALOG  /* P003 (AN003) */
#define GPIO_ARDUINO_A3       GPIO_P004_ANALOG  /* P004 (AN004) */
#define GPIO_ARDUINO_A4       GPIO_P014_ANALOG  /* P014 (AN014/DA0) */
#define GPIO_ARDUINO_A5       GPIO_P015_ANALOG  /* P015 (AN015/DA1) */

/* mikroBUS Analog Input */
#define GPIO_MIKROBUS_AN      GPIO_P004_ANALOG  /* P004 (AN004) */

/* Grove 2 Analog Inputs */
#define GPIO_GROVE2_AN0       GPIO_P002_ANALOG  /* P002 (AN002) */
#define GPIO_GROVE2_AN1       GPIO_P005_ANALOG  /* P005 (AN005) */

/* ADC Channel Definitions */
#define ADC_ARDUINO_A0_CHANNEL     1   /* AN001 */
#define ADC_ARDUINO_A1_CHANNEL     7   /* AN007 */
#define ADC_ARDUINO_A2_CHANNEL     3   /* AN003 */
#define ADC_ARDUINO_A3_CHANNEL     4   /* AN004 */
#define ADC_ARDUINO_A4_CHANNEL     14  /* AN014 */
#define ADC_ARDUINO_A5_CHANNEL     15  /* AN015 */
#define ADC_MIKROBUS_CHANNEL       4   /* AN004 */
#define ADC_GROVE2_AN0_CHANNEL     2   /* AN002 */
#define ADC_GROVE2_AN1_CHANNEL     5   /* AN005 */

/****************************************************************************
 * GPIO Pin Definitions (General Purpose)
 ****************************************************************************/

/* Arduino Digital Pins */
#define GPIO_ARDUINO_D2       GPIO_P011_OUTPUT_HIGH  /* P011 - Arduino D2 */
#define GPIO_ARDUINO_D7       GPIO_P312_OUTPUT_HIGH  /* P312 - Arduino D7 */
#define GPIO_ARDUINO_D8       GPIO_PD01_OUTPUT_HIGH  /* PD01 - Arduino D8 */

/* mikroBUS GPIO */
#define GPIO_MIKROBUS_RST     GPIO_P201_OUTPUT_HIGH  /* P201/MD - mikroBUS RST */

/* Pmod GPIO pins */
#define GPIO_PMOD1_RST        GPIO_P402_OUTPUT_HIGH  /* P402 - Pmod 1 RESET */
#define GPIO_PMOD1_GPIO1      GPIO_P412_OUTPUT_HIGH  /* P412 - Pmod 1 GPIO */
#define GPIO_PMOD1_GPIO2      GPIO_P413_OUTPUT_HIGH  /* P413 - Pmod 1 GPIO */

#define GPIO_PMOD2_RST        GPIO_P410_OUTPUT_HIGH  /* P410 - Pmod 2 RESET */
#define GPIO_PMOD2_GPIO1      GPIO_P409_OUTPUT_HIGH  /* P409 - Pmod 2 GPIO */
#define GPIO_PMOD2_GPIO2      GPIO_P704_OUTPUT_HIGH  /* P704 - Pmod 2 GPIO */

/* Camera GPIO */
#define GPIO_CAMERA_RST       GPIO_P709_OUTPUT_HIGH  /* P709 - Camera RESET */
#define GPIO_CAMERA_PWDN      GPIO_P705_OUTPUT_LOW   /* P705 - Camera PWDN */
#define GPIO_CAMERA_XCLK      GPIO_P501_OUTPUT_HIGH  /* P501 - Camera XCLK */

/****************************************************************************
 * Ethernet Pin Definitions (RGMII Interface)
 ****************************************************************************/

/* Ethernet PHY Management Interface (MDIO/MDC) */
#define GPIO_ETH_MDC          GPIO_ET0_MDC_1         /* P415 - Ethernet PHY MDC */
#define GPIO_ETH_MDIO         GPIO_ET0_MDIO_1        /* P414 - Ethernet PHY MDIO */
#define GPIO_ETH_RSTN         GPIO_P708_OUTPUT_HIGH  /* P708 - Ethernet PHY Reset */
#define GPIO_ETH_INT          GPIO_P107_INPUT_PULLUP /* P107 - Ethernet PHY Interrupt (MDINT) */

/* Ethernet RGMII Transmit Interface */
#define GPIO_ETH_TXD0         GPIO_RGMII1_TXD0_1     /* P307 - Ethernet TX Data 0 */
#define GPIO_ETH_TXD1         GPIO_RGMII1_TXD1_1     /* P306 - Ethernet TX Data 1 */
#define GPIO_ETH_TXD2         GPIO_RGMII1_TXD2_1     /* P305 - Ethernet TX Data 2 */
#define GPIO_ETH_TXD3         GPIO_RGMII1_TXD3_1     /* P304 - Ethernet TX Data 3 */
#define GPIO_ETH_TX_CTL       GPIO_RGMII1_TX_CTL_1   /* P310 - Ethernet TX Control/Enable */
#define GPIO_ETH_TX_CLK       GPIO_RGMII1_TXC_1      /* P308 - Ethernet TX Clock */

/* Ethernet RGMII Receive Interface */
#define GPIO_ETH_RXD0         GPIO_RGMII1_RXD0_1     /* P906 - Ethernet RX Data 0 */
#define GPIO_ETH_RXD1         GPIO_RGMII1_RXD1_1     /* P907 - Ethernet RX Data 1 */
#define GPIO_ETH_RXD2         GPIO_RGMII1_RXD2_1     /* P908 - Ethernet RX Data 2 */
#define GPIO_ETH_RXD3         GPIO_RGMII1_RXD3_1     /* P909 - Ethernet RX Data 3 */
#define GPIO_ETH_RX_CTL       GPIO_RGMII1_RX_CTL_1   /* P905 - Ethernet RX Control */
#define GPIO_ETH_RX_CLK       GPIO_RGMII1_RXC_1      /* P904 - Ethernet RX Clock */

/****************************************************************************
 * CAN-FD Pin Definitions
 ****************************************************************************/
#define GPIO_CANFD1_TX       GPIO_CTX1_5            /* P909 - CAN-FD1 TX */
#define GPIO_CANFD1_RX       GPIO_CRX1_4            /* P908 - CAN-FD1 RX */

#define GPIO_CANFD0_TX       GPIO_CTX0_3            /* P312 - CAN-FD0 TX */
#define GPIO_CANFD0_RX       GPIO_CRX0_3            /* P311 - CAN-FD0 RX */

/****************************************************************************
 * SDRAM Interface Pin Definitions (32-bit data bus)
 * Uses GPIO_SDRAM_*_Pxxx macros from ra_pinmap.h with PFS_PSEL_BUS
 ****************************************************************************/

/* SDRAM Address Lines (directly from pinmap with BUS function) */
#define BOARD_SDRAM_A0        GPIO_SDRAM_A0_PA05     /* PA05 - SDRAM Address 0 (A0/BC0/DQM1) */
#define BOARD_SDRAM_A1        GPIO_SDRAM_A1_PA04     /* PA04 - SDRAM Address 1 (A1/DQM3) */
#define BOARD_SDRAM_A2        GPIO_SDRAM_A2_PA03     /* PA03 - SDRAM Address 2 (A2) */
#define BOARD_SDRAM_A3        GPIO_SDRAM_A3_PA02     /* PA02 - SDRAM Address 3 (A3) */
#define BOARD_SDRAM_A4        GPIO_SDRAM_A4_PA01     /* PA01 - SDRAM Address 4 (A4) */
#define BOARD_SDRAM_A5        GPIO_SDRAM_A5_PA00     /* PA00 - SDRAM Address 5 (A5) */
#define BOARD_SDRAM_A6        GPIO_SDRAM_A6_P503     /* P503 - SDRAM Address 6 (A6) */
#define BOARD_SDRAM_A7        GPIO_SDRAM_A7_P504     /* P504 - SDRAM Address 7 (A7) */
#define BOARD_SDRAM_A8        GPIO_SDRAM_A8_P505     /* P505 - SDRAM Address 8 (A8) */
#define BOARD_SDRAM_A9        GPIO_SDRAM_A9_P506     /* P506 - SDRAM Address 9 (A9) */
#define BOARD_SDRAM_A10       GPIO_SDRAM_A10_P507    /* P507 - SDRAM Address 10 (A10) */
#define BOARD_SDRAM_A11       GPIO_SDRAM_A11_P508    /* P508 - SDRAM Address 11 (A11) */
#define BOARD_SDRAM_A12       GPIO_SDRAM_A12_P509    /* P509 - SDRAM Address 12 (A12) */
#define BOARD_SDRAM_A13       GPIO_SDRAM_A13_P510    /* P510 - SDRAM Address 13 (A13) */
#define BOARD_SDRAM_A14       GPIO_SDRAM_A14_P608    /* P608 - SDRAM Address 14 (A14) */
#define BOARD_SDRAM_A15       GPIO_SDRAM_A15_PD00    /* PD00 - SDRAM Address 15 (A15) */
#define BOARD_SDRAM_A16       GPIO_SDRAM_A16_PC15    /* PC15 - SDRAM Address 16 (A16) */
#define BOARD_SDRAM_A17       GPIO_SDRAM_A17_P408    /* P408 - SDRAM Address 17 (A17) */
#define BOARD_SDRAM_A18       GPIO_SDRAM_A18_P409    /* P409 - SDRAM Address 18 (A18) */
#define BOARD_SDRAM_A19       GPIO_SDRAM_A19_P410    /* P410 - SDRAM Address 19 (A19) */
#define BOARD_SDRAM_A20       GPIO_SDRAM_A20_P411    /* P411 - SDRAM Address 20 (A20) */
#define BOARD_SDRAM_A21       GPIO_SDRAM_A21_P412    /* P412 - SDRAM Address 21 (A21) */
#define BOARD_SDRAM_A22       GPIO_SDRAM_A22_P413    /* P413 - SDRAM Address 22 (A22) */
#define BOARD_SDRAM_A23       GPIO_SDRAM_A23_P414    /* P414 - SDRAM Address 23 (A23) */

/* SDRAM Data Lines (32-bit data bus DQ0-DQ31) */
#define BOARD_SDRAM_DQ0       GPIO_SDRAM_DQ0_P302    /* P302 - SDRAM Data 0 (D0/DQ0) */
#define BOARD_SDRAM_DQ1       GPIO_SDRAM_DQ1_P301    /* P301 - SDRAM Data 1 (D1/DQ1) */
#define BOARD_SDRAM_DQ2       GPIO_SDRAM_DQ2_P300    /* P300 - SDRAM Data 2 (D2/DQ2) */
#define BOARD_SDRAM_DQ3       GPIO_SDRAM_DQ3_P112    /* P112 - SDRAM Data 3 (D3/DQ3) */
#define BOARD_SDRAM_DQ4       GPIO_SDRAM_DQ4_P113    /* P113 - SDRAM Data 4 (D4/DQ4) */
#define BOARD_SDRAM_DQ5       GPIO_SDRAM_DQ5_P114    /* P114 - SDRAM Data 5 (D5/DQ5) */
#define BOARD_SDRAM_DQ6       GPIO_SDRAM_DQ6_P115    /* P115 - SDRAM Data 6 (D6/DQ6) */
#define BOARD_SDRAM_DQ7       GPIO_SDRAM_DQ7_P609    /* P609 - SDRAM Data 7 (D7/DQ7) */
#define BOARD_SDRAM_DQ8       GPIO_SDRAM_DQ8_PA11    /* PA11 - SDRAM Data 8 (D8/DQ8) */
#define BOARD_SDRAM_DQ9       GPIO_SDRAM_DQ9_PA12    /* PA12 - SDRAM Data 9 (D9/DQ9) */
#define BOARD_SDRAM_DQ10      GPIO_SDRAM_DQ10_PA13   /* PA13 - SDRAM Data 10 (D10/DQ10) */
#define BOARD_SDRAM_DQ11      GPIO_SDRAM_DQ11_PA14   /* PA14 - SDRAM Data 11 (D11/DQ11) */
#define BOARD_SDRAM_DQ12      GPIO_SDRAM_DQ12_P610   /* P610 - SDRAM Data 12 (D12/DQ12) */
#define BOARD_SDRAM_DQ13      GPIO_SDRAM_DQ13_P611   /* P611 - SDRAM Data 13 (D13/DQ13) */
#define BOARD_SDRAM_DQ14      GPIO_SDRAM_DQ14_P612   /* P612 - SDRAM Data 14 (D14/DQ14) */
#define BOARD_SDRAM_DQ15      GPIO_SDRAM_DQ15_P613   /* P613 - SDRAM Data 15 (D15/DQ15) */
#define BOARD_SDRAM_DQ16      GPIO_SDRAM_DQ16_PC14   /* PC14 - SDRAM Data 16 (D16/DQ16) */
#define BOARD_SDRAM_DQ17      GPIO_SDRAM_DQ17_PC13   /* PC13 - SDRAM Data 17 (D17/DQ17) */
#define BOARD_SDRAM_DQ18      GPIO_SDRAM_DQ18_PC12   /* PC12 - SDRAM Data 18 (D18/DQ18) */
#define BOARD_SDRAM_DQ19      GPIO_SDRAM_DQ19_PC11   /* PC11 - SDRAM Data 19 (D19/DQ19) */
#define BOARD_SDRAM_DQ20      GPIO_SDRAM_DQ20_PC10   /* PC10 - SDRAM Data 20 (D20/DQ20) */
#define BOARD_SDRAM_DQ21      GPIO_SDRAM_DQ21_PC09   /* PC09 - SDRAM Data 21 (D21/DQ21) */
#define BOARD_SDRAM_DQ22      GPIO_SDRAM_DQ22_PC08   /* PC08 - SDRAM Data 22 (D22/DQ22) */
#define BOARD_SDRAM_DQ23      GPIO_SDRAM_DQ23_PC07   /* PC07 - SDRAM Data 23 (D23/DQ23) */
#define BOARD_SDRAM_DQ24      GPIO_SDRAM_DQ24_PC06   /* PC06 - SDRAM Data 24 (D24/DQ24) */
#define BOARD_SDRAM_DQ25      GPIO_SDRAM_DQ25_PC05   /* PC05 - SDRAM Data 25 (D25/DQ25) */
#define BOARD_SDRAM_DQ26      GPIO_SDRAM_DQ26_PC04   /* PC04 - SDRAM Data 26 (D26/DQ26) */
#define BOARD_SDRAM_DQ27      GPIO_SDRAM_DQ27_PC03   /* PC03 - SDRAM Data 27 (D27/DQ27) */
#define BOARD_SDRAM_DQ28      GPIO_SDRAM_DQ28_PC02   /* PC02 - SDRAM Data 28 (D28/DQ28) */
#define BOARD_SDRAM_DQ29      GPIO_SDRAM_DQ29_PC01   /* PC01 - SDRAM Data 29 (D29/DQ29) */
#define BOARD_SDRAM_DQ30      GPIO_SDRAM_DQ30_PC00   /* PC00 - SDRAM Data 30 (D30/DQ30) */
#define BOARD_SDRAM_DQ31      GPIO_SDRAM_DQ31_P607   /* P607 - SDRAM Data 31 (D31/DQ31) */

/* SDRAM Data Mask / Byte Enables */
#define BOARD_SDRAM_DQM0      GPIO_SDRAM_DQM0_P614   /* P614 - SDRAM Data Mask 0 (WR/WR0/DQM0) */
#define BOARD_SDRAM_DQM1      GPIO_SDRAM_DQM1_PA05   /* PA05 - SDRAM Data Mask 1 (A0/BC0/DQM1) */
#define BOARD_SDRAM_DQM2      GPIO_SDRAM_DQM2_P615   /* P615 - SDRAM Data Mask 2 (WR2/BC2/DQM2) */
#define BOARD_SDRAM_DQM3      GPIO_SDRAM_DQM3_PA04   /* PA04 - SDRAM Data Mask 3 (A1/DQM3) */

/* SDRAM Control Signals */
#define BOARD_SDRAM_CKE       GPIO_SDRAM_CKE_PA06    /* PA06 - SDRAM Clock Enable (CS1/CKE) */
#define BOARD_SDRAM_CLK       GPIO_SDRAM_SDCLK_PA15  /* PA15 - SDRAM Clock (EBCLK/SDCLK) */
#define BOARD_SDRAM_CS        GPIO_SDRAM_SDCS_P813   /* P813 - SDRAM Chip Select (SDCS) */
#define BOARD_SDRAM_WE        GPIO_SDRAM_WE_PA08     /* PA08 - SDRAM Write Enable (CS0/WE) */
#define BOARD_SDRAM_CAS       GPIO_SDRAM_CAS_PA09    /* PA09 - SDRAM Column Address Strobe (CS3/CAS) */
#define BOARD_SDRAM_RAS       GPIO_SDRAM_RAS_PA10    /* PA10 - SDRAM Row Address Strobe (CS2/RAS) */


/****************************************************************************
 * USB High Speed Pin Definitions (Connector J7)
 ****************************************************************************/

/* USB HS VBUS Detection and Control - P408 */
#define GPIO_USBHS_VBUS       GPIO_USBHS_VBUS_1      /* P408 - USB HS VBUS Sense (USBHS_cVBUS_CON) */

/* USB HS ID Detection - P411 (option 1) */
#define GPIO_USBHS_ID         GPIO_USBHS_ID_1        /* P411 - USB HS ID Detection */

/* USB HS Overcurrent Detection - P413/P413_DS */
#define GPIO_USBHS_OVRCURA    GPIO_USBHS_OVRCURA_1   /* P413 - USB HS Overcurrent A */

/* USB HS VBUS Enable - P407 (option 1) */
#define GPIO_USBHS_VBUSEN     GPIO_USBHS_VBUSEN_1    /* P407 - USB HS VBUS Enable */

/* USB HS External IC Enable - P412 (option 1) */
#define GPIO_USBHS_EXICEN     GPIO_USBHS_EXICEN_1    /* P412 - USB HS External IC Enable */

/* USB HS Differential Pair - P815 (DM/DP are typically internal to USB PHY) */
#define GPIO_USBHS_DM         GPIO_USB_DM_1          /* P815 - USB HS D- (USBH_N) */

/* Note: USB High Speed differential pairs (DA+/DA-, DB+/DB-, TX+/TX-, RX+/RX-)
 * shown in board.csv J7 connector are typically routed internally and may not
 * require explicit GPIO pin configuration. The USB controller handles these
 * signals automatically. Configuration Channel pins (USB_HS_CC1, USB_HS_CC2)
 * are for USB Type-C functionality.
 */

/****************************************************************************
 * OSPI/QSPI Flash Pin Definitions (Octo-SPI Interface)
 ****************************************************************************/

/* OSPI Flash Control Signals */
#define GPIO_OSPI_CS          GPIO_OM_0_CS0_1        /* P104 - QSPI_FLASH_CS# (OSPI Chip Select 0) */
#define GPIO_OSPI_RESET       GPIO_OM_0_RESET_1      /* P106 - QSPI_FLASH_RESET# (OSPI Reset) */
#define GPIO_OSPI_ECS         GPIO_OM_0_CS1_1        /* P105 - QSPI_FLASH_ECS# (Extended Chip Select 1) */

/* OSPI Flash Data Signals (8-bit data bus SIO0-SIO7) */
/* Note: GPIO_OM_0_SIO0_1 not defined in ra_pinmap.h - using manual construction for P100 */
#define GPIO_OSPI_SIO0        (gpio_pinset_t)(PORT1 | PIN0 | PFS_PSEL_XSPI)  /* P100 - QSPI_FLASH_SIO0 */
#define GPIO_OSPI_SIO1        GPIO_OM_0_SIO1_1       /* P803 - QSPI_FLASH_SIO1 (Data I/O 1) */
#define GPIO_OSPI_SIO2        GPIO_OM_0_SIO2_1       /* P103 - QSPI_FLASH_SIO2 (Data I/O 2) */
#define GPIO_OSPI_SIO3        GPIO_OM_0_SIO3_1       /* P101 - QSPI_FLASH_SIO3 (Data I/O 3) */
#define GPIO_OSPI_SIO4        GPIO_OM_0_SIO4_1       /* P102 - QSPI_FLASH_SIO4 (Data I/O 4) */
#define GPIO_OSPI_SIO5        GPIO_OM_0_SIO5_1       /* P800 - QSPI_FLASH_SIO5 (Data I/O 5) */
#define GPIO_OSPI_SIO6        GPIO_OM_0_SIO6_1       /* P802 - QSPI_FLASH_SIO6 (Data I/O 6) */
#define GPIO_OSPI_SIO7        GPIO_OM_0_SIO7_1       /* P804 - QSPI_FLASH_SIO7 (Data I/O 7) */

/* OSPI Flash Clock Signals */
/* Note: board.csv shows P808 for SCLK but GPIO_OM_0_SCLKN_1 maps to P809 with PFS_PSEL_IIC.
 * This is likely a documentation error. For P808, use manual construction with XSPI function.
 * Similarly, GPIO_OM_0_GPPT1_PPS_1 (P801) is mapped for DQS but check if dedicated DQS
 * function selector is needed instead of GPPT (General Purpose Port Timer).
 */
#define GPIO_OSPI_SCLK        (gpio_pinset_t)(PORT8 | PIN8 | PFS_PSEL_XSPI)  /* P808 - QSPI_FLASH_SCLK */
#define GPIO_OSPI_DQS         GPIO_OM_0_GPPT1_PPS_1  /* P801 - QSPI_FLASH_DQS (Data Strobe) */

/* Additional OSPI control signals available but not mapped:
 * - GPIO_OM_0_ECSINT1_1 (P105) - Extended CS Interrupt
 * - GPIO_OM_0_RSTO1_1 (P600) - Reset Output 1
 * - GPIO_OM_0_WP1_1 (P601) - Write Protect 1
 * The OM_0 prefix indicates Octo-SPI Memory controller channel 0.
 * OSPI supports 1-1-1, 1-1-8, 1-8-8, and 8-8-8 transfer modes with DTR.
 */

/****************************************************************************
 * Camera Interface Pin Definitions (Connector J35)
 ****************************************************************************/

/* Parallel Camera Interface Data Lines (8-bit mode: D0-D7, 12-bit mode: D0-D11) */
/* Note: board.csv shows only D2-D9 are connected (D0, D1, D10, D11 are NC) */
#define GPIO_CAM_D2           GPIO_P400              /* P400 - CAM_D2 (Parallel D0 in board mapping) */
#define GPIO_CAM_D3           GPIO_P902              /* P902 - CAM_D3 (Parallel D1) */
#define GPIO_CAM_D4           GPIO_P405              /* P405 - CAM_D4 (Parallel D2) */
#define GPIO_CAM_D5           GPIO_P406              /* P406 - CAM_D5 (Parallel D3) */
#define GPIO_CAM_D6           GPIO_P700              /* P700 - CAM_D6 (Parallel D4) */
#define GPIO_CAM_D7           GPIO_P701              /* P701 - CAM_D7 (Parallel D5) */
#define GPIO_CAM_D8           GPIO_P702              /* P702 - CAM_D8 (Parallel D6) */
#define GPIO_CAM_D9           GPIO_P703              /* P703 - CAM_D9 (Parallel D7) */
/* CAM_D0, CAM_D1, CAM_D10, CAM_D11 are NC (Not Connected) on J35 */

/* Parallel Camera Control Signals */
#define GPIO_CAM_VSYNC        GPIO_PB02              /* PB02 - CAM_VSYNC (Vertical Sync) */
#define GPIO_CAM_HSYNC        GPIO_PB03              /* PB03 - CAM_HSYNC (Horizontal Sync) */
#define GPIO_CAM_PCLK         GPIO_PB04              /* PB04 - CAM_PCLK (Pixel Clock) */

/* MIPI CSI-2 Interface (Camera Serial Interface - Differential Pairs)
 * Note: MIPI CSI-2 signals are high-speed differential pairs that typically
 * don't require explicit GPIO configuration as they are handled by the MIPI PHY.
 * The board.csv shows these signals:
 * - MIPI_CSI_DL0_P/N (Data Lane 0 differential pair)
 * - MIPI_CSI_DL1_P/N (Data Lane 1 differential pair)
 * - MIPI_CSI_CL_P/N (Clock Lane differential pair)
 *
 * These are dedicated MIPI CSI-2 pins without GPIO pin numbers in the EVK-RA8P1.
 * Configuration is done through MIPI D-PHY controller registers, not GPIO PFS.
 */

/* Camera I2C Control (uses shared I2C1 bus) */
#define GPIO_CAM_I2C_SCL      GPIO_I2C_SCL1          /* P512 - Camera I2C Clock (shared) */
#define GPIO_CAM_I2C_SDA      GPIO_I2C_SDA1          /* P511 - Camera I2C Data (shared) */

/* Camera GPIO Control Pins (from earlier GPIO section) */
/* GPIO_CAM_RST and GPIO_CAM_PWDN were already defined in GPIO Definitions section */

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

/* GPIO initialization list pattern */
#define RA8_GPIO_INIT_LIST  { \
  GPIO_SCI2_RX,                 /* Console RX - P802 */ \
  GPIO_SCI2_TX,                 /* Console TX - P801 */ \
  GPIO_SCI0_RX,                 /* Pmod 2 UART RX - P602 */ \
  GPIO_SCI0_TX,                 /* Pmod 2 UART TX - P603 */ \
  GPIO_SCI7_RX,                 /* Arduino/mikroBUS UART RX - P808 */ \
  GPIO_SCI7_TX,                 /* Arduino/mikroBUS UART TX - P809 */ \
  GPIO_ARDUINO_SPI_SCK,         /* P102 - Arduino D13 */ \
  GPIO_ARDUINO_SPI_MISO,        /* P100 - Arduino D12 */ \
  GPIO_ARDUINO_SPI_MOSI,        /* P101 - Arduino D11 */ \
  GPIO_ARDUINO_SPI_CS0,         /* P103 - Arduino D10 */ \
  GPIO_ARDUINO_SPI_CS1,         /* P110 - repurposed for another CS */ \
  GPIO_I2C0_SCL,                /* I2C0 Clock - P400 */ \
  GPIO_I2C0_SDA,                /* I2C0 Data - P401 */ \
  GPIO_I2C1_SCL,                /* I2C1 Clock - P512 */ \
  GPIO_I2C1_SDA,                /* I2C1 Data - P511 */ \
  GPIO_USER_LED_BLUE,           /* Blue LED - P600 */ \
  GPIO_USER_LED_GREEN,          /* Green LED - P303 */ \
  GPIO_USER_LED_RED,            /* Red LED - PA07 */ \
  GPIO_USER_SW1,                /* User Button SW1 - P009 */ \
  GPIO_USER_SW2                 /* User Button SW2 - P008 */ \
}


#endif /* __BOARDS_ARM_RA8_EVK_RA8P1_INCLUDE_BOARD_H */
