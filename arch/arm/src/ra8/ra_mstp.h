/****************************************************************************
 * arch/arm/src/ra8/ra_mstp.h
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

#ifndef __ARCH_ARM_SRC_RA_RA8_MSTP_H
#define __ARCH_ARM_SRC_RA_RA8_MSTP_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>

#include <hardware/ra_memorymap.h>
#include <ra_mstp.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* MSTPCRA - Module Stop Control Register A */
/* Based on FSP bsp_module_stop.h for RA8P1 */
#define R_MSTP_MSTPCRA_NPU             R_MSTP_MSTPCRA_MSTPA16  /* Neural Processing Unit */
#if CONFIG_RA_CPU_CORE == 0
#  define R_MSTP_MSTPCRA_DMAC          R_MSTP_MSTPCRA_MSTPA22  /* DMA Controller CPU0 */
#else
#  define R_MSTP_MSTPCRA_DMAC          R_MSTP_MSTPCRA_MSTPA23  /* DMA Controller CPU1 */
#endif
#define R_MSTP_MSTPCRA_DTC             R_MSTP_MSTPCRA_MSTPA22  /* Data Transfer Controller */

/* MSTPCRB - Module Stop Control Register B (Bit 31 to 0) */
#define R_MSTP_MSTPCRB_SCI0            R_MSTP_MSTPCRB_MSTPB31  /* Serial Communication Interface 0 */
#define R_MSTP_MSTPCRB_SCI1            R_MSTP_MSTPCRB_MSTPB30  /* Serial Communication Interface 1 */
#define R_MSTP_MSTPCRB_SCI2            R_MSTP_MSTPCRB_MSTPB29  /* Serial Communication Interface 2 */
#define R_MSTP_MSTPCRB_SCI3            R_MSTP_MSTPCRB_MSTPB28  /* Serial Communication Interface 3 */
#define R_MSTP_MSTPCRB_SCI4            R_MSTP_MSTPCRB_MSTPB27  /* Serial Communication Interface 4 */
#define R_MSTP_MSTPCRB_SCI5            R_MSTP_MSTPCRB_MSTPB26  /* Serial Communication Interface 5 */
#define R_MSTP_MSTPCRB_SCI6            R_MSTP_MSTPCRB_MSTPB25  /* Serial Communication Interface 6 */
#define R_MSTP_MSTPCRB_SCI7            R_MSTP_MSTPCRB_MSTPB24  /* Serial Communication Interface 7 */
#define R_MSTP_MSTPCRB_SCI8            R_MSTP_MSTPCRB_MSTPB23  /* Serial Communication Interface 8 */
#define R_MSTP_MSTPCRB_SCI9            R_MSTP_MSTPCRB_MSTPB22  /* Serial Communication Interface 9 */
/* Bit 21-20: Reserved */
#define R_MSTP_MSTPCRB_SPI0            R_MSTP_MSTPCRB_MSTPB19  /* Serial Peripheral Interface 0 */
#define R_MSTP_MSTPCRB_SPI1            R_MSTP_MSTPCRB_MSTPB18  /* Serial Peripheral Interface 1 */
#define R_MSTP_MSTPCRB_OSPI1           R_MSTP_MSTPCRB_MSTPB17  /* Octal SPI 1 */
#define R_MSTP_MSTPCRB_OSPI0           R_MSTP_MSTPCRB_MSTPB16  /* Octal SPI 0 */
#define R_MSTP_MSTPCRB_ETHER0          R_MSTP_MSTPCRB_MSTPB15  /* Ethernet Controller 0 (not available on RA8P1) */
#define R_MSTP_MSTPCRB_ETHER1          R_MSTP_MSTPCRB_MSTPB14  /* Ethernet Controller 1 (not available on RA8P1) */
#define R_MSTP_MSTPCRB_EPTPC           R_MSTP_MSTPCRB_MSTPB13  /* Precision Time Protocol Controller */
#define R_MSTP_MSTPCRB_USBHS           R_MSTP_MSTPCRB_MSTPB12  /* USB High Speed */
#define R_MSTP_MSTPCRB_USBFS           R_MSTP_MSTPCRB_MSTPB11  /* USB Full Speed */
/* Bit 10: Reserved */
#define R_MSTP_MSTPCRB_IIC0            R_MSTP_MSTPCRB_MSTPB9   /* I2C Bus Interface 0 */
#define R_MSTP_MSTPCRB_IIC1            R_MSTP_MSTPCRB_MSTPB8   /* I2C Bus Interface 1 */
#define R_MSTP_MSTPCRB_IIC2            R_MSTP_MSTPCRB_MSTPB7   /* I2C Bus Interface 2 */
#define R_MSTP_MSTPCRB_QSPI            R_MSTP_MSTPCRB_MSTPB6   /* Quad Serial Peripheral Interface */
#define R_MSTP_MSTPCRB_IRDA            R_MSTP_MSTPCRB_MSTPB5   /* Infrared Data Association */
#define R_MSTP_MSTPCRB_I3C             R_MSTP_MSTPCRB_MSTPB4   /* I3C Bus Interface */
#define R_MSTP_MSTPCRB_CEC             R_MSTP_MSTPCRB_MSTPB3   /* Consumer Electronics Control */
#define R_MSTP_MSTPCRB_CAN0            R_MSTP_MSTPCRB_MSTPB2   /* Controller Area Network 0 */
#define R_MSTP_MSTPCRB_CAN1            R_MSTP_MSTPCRB_MSTPB1   /* Controller Area Network 1 */
/* Bit 0: Reserved */

/* MSTPCRC - Module Stop Control Register C (Bit 31 to 0) */
#define R_MSTP_MSTPCRC_SCE5            R_MSTP_MSTPCRC_MSTPC31  /* Renesas Secure IP (not available on RA8P1) */
#define R_MSTP_MSTPCRC_LAYER3_SWITCH   R_MSTP_MSTPCRC_MSTPC30  /* Layer 3 Ethernet Switch */
/* Bit 29: Reserved */
#define R_MSTP_MSTPCRC_ETHER_PHY_CLK   R_MSTP_MSTPCRC_MSTPC28  /* Ethernet PHY Clock */
#define R_MSTP_MSTPCRC_CANFD0          R_MSTP_MSTPCRC_MSTPC27  /* CAN with Flexible Data-Rate 0 */
#define R_MSTP_MSTPCRC_CANFD1          R_MSTP_MSTPCRC_MSTPC26  /* CAN with Flexible Data-Rate 1 */
/* Bit 25: Reserved */
#define R_MSTP_MSTPCRC_PDM             R_MSTP_MSTPCRC_MSTPC24  /* Pulse Density Modulation */
/* Bit 23-22: Reserved */
#define R_MSTP_MSTPCRC_IIRFA           R_MSTP_MSTPCRC_MSTPC21  /* IIR Filter Accelerator */
#define R_MSTP_MSTPCRC_TFU             R_MSTP_MSTPCRC_MSTPC20  /* Trigonometric Function Unit */
/* Bit 19-18: Reserved */
#define R_MSTP_MSTPCRC_MIPI_CSI        R_MSTP_MSTPCRC_MSTPC17  /* MIPI Camera Serial Interface */
#define R_MSTP_MSTPCRC_CEU             R_MSTP_MSTPCRC_MSTPC16  /* Capture Engine Unit */
#define R_MSTP_MSTPCRC_VIN             R_MSTP_MSTPCRC_MSTPC16  /* Video Input (same as CEU) */
#define R_MSTP_MSTPCRC_MACL            R_MSTP_MSTPCRC_MSTPC15  /* MAC Accelerator */
#define R_MSTP_MSTPCRC_ELC             R_MSTP_MSTPCRC_MSTPC14  /* Event Link Controller */
#define R_MSTP_MSTPCRC_DOC             R_MSTP_MSTPCRC_MSTPC13  /* Data Operation Circuit */
#define R_MSTP_MSTPCRC_SDHI            R_MSTP_MSTPCRC_MSTPC12  /* SD/MMC Host Interface */
/* Bit 11: Reserved */
#define R_MSTP_MSTPCRC_MIPI_DSI        R_MSTP_MSTPCRC_MSTPC10  /* MIPI Display Serial Interface */
#define R_MSTP_MSTPCRC_SRC             R_MSTP_MSTPCRC_MSTPC9   /* Sampling Rate Converter */
#define R_MSTP_MSTPCRC_SSIE0           R_MSTP_MSTPCRC_MSTPC8   /* Serial Sound Interface Enhanced 0 */
#define R_MSTP_MSTPCRC_SSI0            R_MSTP_MSTPCRC_MSTPC8   /* Alias for SSIE0 */
#define R_MSTP_MSTPCRC_SSIE1           R_MSTP_MSTPCRC_MSTPC7   /* Serial Sound Interface Enhanced 1 */
#define R_MSTP_MSTPCRC_SSI1            R_MSTP_MSTPCRC_MSTPC7   /* Alias for SSIE1 */
#define R_MSTP_MSTPCRC_DRW             R_MSTP_MSTPCRC_MSTPC6   /* 2D Drawing Engine */
#define R_MSTP_MSTPCRC_JPEG            R_MSTP_MSTPCRC_MSTPC5   /* JPEG Codec */
#define R_MSTP_MSTPCRC_GLCDC           R_MSTP_MSTPCRC_MSTPC4   /* Graphics LCD Controller */
#define R_MSTP_MSTPCRC_SLCDC           R_MSTP_MSTPCRC_MSTPC4   /* Segment LCD Controller (not available on RA8P1) */
#define R_MSTP_MSTPCRC_CTSU            R_MSTP_MSTPCRC_MSTPC3   /* Capacitive Touch Sensing Unit */
#define R_MSTP_MSTPCRC_PDC             R_MSTP_MSTPCRC_MSTPC2   /* Parallel Data Capture */
#define R_MSTP_MSTPCRC_CRC             R_MSTP_MSTPCRC_MSTPC1   /* Cyclic Redundancy Check */
#define R_MSTP_MSTPCRC_CAC             R_MSTP_MSTPCRC_MSTPC0   /* Clock Frequency Accuracy Measurement */

/* MSTPCRD - Module Stop Control Register D (Bit 31 to 0) */
#define R_MSTP_MSTPCRD_OPAMP           R_MSTP_MSTPCRD_MSTPD31  /* Operational Amplifier (not available on RA8P1) */
/* Bit 30: Reserved */
#define R_MSTP_MSTPCRD_ACMPLP          R_MSTP_MSTPCRD_MSTPD29  /* Low-Power Analog Comparator (not available on RA8P1) */
#define R_MSTP_MSTPCRD_ACMPHS0         R_MSTP_MSTPCRD_MSTPD28  /* High-Speed Analog Comparator 0 */
#define R_MSTP_MSTPCRD_ACMPHS1         R_MSTP_MSTPCRD_MSTPD27  /* High-Speed Analog Comparator 1 */
#define R_MSTP_MSTPCRD_ACMPHS2         R_MSTP_MSTPCRD_MSTPD26  /* High-Speed Analog Comparator 2 */
#define R_MSTP_MSTPCRD_ACMPHS3         R_MSTP_MSTPCRD_MSTPD25  /* High-Speed Analog Comparator 3 */
#define R_MSTP_MSTPCRD_ACMPHS          R_MSTP_MSTPCRD_MSTPD28  /* Default to ACMPHS0 */
/* Bit 24: Reserved */
#define R_MSTP_MSTPCRD_RTC             R_MSTP_MSTPCRD_MSTPD23  /* Real Time Clock */
#define R_MSTP_MSTPCRD_TSN             R_MSTP_MSTPCRD_MSTPD22  /* Temperature Sensor */
#define R_MSTP_MSTPCRD_ADC0            R_MSTP_MSTPCRD_MSTPD21  /* A/D Converter 0 (ADC_B) */
#define R_MSTP_MSTPCRD_ADC1            R_MSTP_MSTPCRD_MSTPD20  /* A/D Converter 1 (ADC_B) */
#define R_MSTP_MSTPCRD_DAC0            R_MSTP_MSTPCRD_MSTPD20  /* D/A Converter 0 (DAC_B) */
#define R_MSTP_MSTPCRD_DAC1            R_MSTP_MSTPCRD_MSTPD19  /* D/A Converter 1 (DAC_B) */
#define R_MSTP_MSTPCRD_DAC8            R_MSTP_MSTPCRD_MSTPD19  /* 8-bit D/A Converter (not available on RA8P1) */
/* Bit 18: Reserved */
#define R_MSTP_MSTPCRD_SDADC           R_MSTP_MSTPCRD_MSTPD17  /* Sigma-Delta A/D Converter (not available on RA8P1) */
/* Bit 16-15: Reserved */
#define R_MSTP_MSTPCRD_POEG0           R_MSTP_MSTPCRD_MSTPD14  /* Port Output Enable for GPT Group 0 */
#define R_MSTP_MSTPCRD_POEG1           R_MSTP_MSTPCRD_MSTPD13  /* Port Output Enable for GPT Group 1 */
#define R_MSTP_MSTPCRD_POEG2           R_MSTP_MSTPCRD_MSTPD12  /* Port Output Enable for GPT Group 2 */
#define R_MSTP_MSTPCRD_POEG3           R_MSTP_MSTPCRD_MSTPD11  /* Port Output Enable for GPT Group 3 */
#define R_MSTP_MSTPCRD_POEG            R_MSTP_MSTPCRD_MSTPD14  /* Default to POEG0 */
/* Bit 10-7: Reserved */
#define R_MSTP_MSTPCRD_GPT_PDG         R_MSTP_MSTPCRD_MSTPD6   /* GPT Port Output Disable Group */
#define R_MSTP_MSTPCRD_AGT0            R_MSTP_MSTPCRD_MSTPD5   /* Asynchronous General Purpose Timer 0 */
#define R_MSTP_MSTPCRD_AGT1            R_MSTP_MSTPCRD_MSTPD4   /* Asynchronous General Purpose Timer 1 */
/* Bit 3-0: Reserved */

/* MSTPCRE - Module Stop Control Register E (Bit 31 to 0) */
#define R_MSTP_MSTPCRE_GPT0            R_MSTP_MSTPCRE_MSTPE31  /* General PWM Timer 0 */
#define R_MSTP_MSTPCRE_GPT1            R_MSTP_MSTPCRE_MSTPE30  /* General PWM Timer 1 */
#define R_MSTP_MSTPCRE_GPT2            R_MSTP_MSTPCRE_MSTPE29  /* General PWM Timer 2 */
#define R_MSTP_MSTPCRE_GPT3            R_MSTP_MSTPCRE_MSTPE28  /* General PWM Timer 3 */
#define R_MSTP_MSTPCRE_GPT4            R_MSTP_MSTPCRE_MSTPE27  /* General PWM Timer 4 */
#define R_MSTP_MSTPCRE_GPT5            R_MSTP_MSTPCRE_MSTPE26  /* General PWM Timer 5 */
#define R_MSTP_MSTPCRE_GPT6            R_MSTP_MSTPCRE_MSTPE25  /* General PWM Timer 6 */
#define R_MSTP_MSTPCRE_GPT7            R_MSTP_MSTPCRE_MSTPE24  /* General PWM Timer 7 */
#define R_MSTP_MSTPCRE_GPT8            R_MSTP_MSTPCRE_MSTPE23  /* General PWM Timer 8 */
#define R_MSTP_MSTPCRE_GPT9            R_MSTP_MSTPCRE_MSTPE22  /* General PWM Timer 9 */
#define R_MSTP_MSTPCRE_GPT10           R_MSTP_MSTPCRE_MSTPE21  /* General PWM Timer 10 */
#define R_MSTP_MSTPCRE_GPT11           R_MSTP_MSTPCRE_MSTPE20  /* General PWM Timer 11 */
#define R_MSTP_MSTPCRE_GPT12           R_MSTP_MSTPCRE_MSTPE19  /* General PWM Timer 12 */
#define R_MSTP_MSTPCRE_GPT13           R_MSTP_MSTPCRE_MSTPE18  /* General PWM Timer 13 */
/* Bit 17-10: Reserved */
#define R_MSTP_MSTPCRE_ULPT0           R_MSTP_MSTPCRE_MSTPE9   /* Ultra-Low Power Timer 0 */
#define R_MSTP_MSTPCRE_ULPT1           R_MSTP_MSTPCRE_MSTPE8   /* Ultra-Low Power Timer 1 */
/* Bit 7-0: Reserved */

/* Module enumeration for MSTP control */

typedef enum
{
  /* MSTPCRA register modules */
  RA_MSTP_NPU = 0,          /* MSTPA16: Neural Processing Unit */
  RA_MSTP_DMAC,             /* MSTPA22/23: DMA Controller (CPU0=22, CPU1=23) */
  RA_MSTP_DTC,              /* MSTPA22: Data Transfer Controller */

  /* MSTPCRB register modules (Bit 31 to 0) */
  RA_MSTP_SCI0,             /* MSTPB31: Serial Communication Interface 0 */
  RA_MSTP_SCI1,             /* MSTPB30: Serial Communication Interface 1 */
  RA_MSTP_SCI2,             /* MSTPB29: Serial Communication Interface 2 */
  RA_MSTP_SCI3,             /* MSTPB28: Serial Communication Interface 3 */
  RA_MSTP_SCI4,             /* MSTPB27: Serial Communication Interface 4 */
  RA_MSTP_SCI5,             /* MSTPB26: Serial Communication Interface 5 */
  RA_MSTP_SCI6,             /* MSTPB25: Serial Communication Interface 6 */
  RA_MSTP_SCI7,             /* MSTPB24: Serial Communication Interface 7 */
  RA_MSTP_SCI8,             /* MSTPB23: Serial Communication Interface 8 */
  RA_MSTP_SCI9,             /* MSTPB22: Serial Communication Interface 9 */
  RA_MSTP_SPI0,             /* MSTPB19: Serial Peripheral Interface 0 */
  RA_MSTP_SPI1,             /* MSTPB18: Serial Peripheral Interface 1 */
  RA_MSTP_OSPI1,            /* MSTPB17: Octal Serial Peripheral Interface 1 */
  RA_MSTP_OSPI0,            /* MSTPB16: Octal Serial Peripheral Interface 0 */
  RA_MSTP_EPTPC,            /* MSTPB13: Precision Time Protocol Controller */
  RA_MSTP_USBHS,            /* MSTPB12: USB High Speed */
  RA_MSTP_USBFS,            /* MSTPB11: Universal Serial Bus 2.0 FS Interface */
  RA_MSTP_IIC0,             /* MSTPB9: I2C Bus Interface 0 */
  RA_MSTP_IIC1,             /* MSTPB8: I2C Bus Interface 1 */
  RA_MSTP_IIC2,             /* MSTPB7: I2C Bus Interface 2 */
  RA_MSTP_QSPI,             /* MSTPB6: Quad Serial Peripheral Interface */
  RA_MSTP_IRDA,             /* MSTPB5: Infrared Data Association */
  RA_MSTP_I3C,              /* MSTPB4: I3C */
  RA_MSTP_CEC,              /* MSTPB3: Consumer Electronics Control */
  RA_MSTP_CAN0,             /* MSTPB2: Controller Area Network 0 */
  RA_MSTP_CAN1,             /* MSTPB1: Controller Area Network 1 */

  /* MSTPCRC register modules (Bit 31 to 0) */
  RA_MSTP_LAYER3_SWITCH,    /* MSTPC30: Layer 3 Ethernet Switch (ESWM) */
  RA_MSTP_ETHER_PHY_CLK,    /* MSTPC28: Ether-PHY Clock */
  RA_MSTP_CANFD0,           /* MSTPC27: Controller Area Network with Flexible Data-Rate 0 */
  RA_MSTP_CANFD1,           /* MSTPC26: Controller Area Network with Flexible Data-Rate 1 */
  RA_MSTP_PDM,              /* MSTPC24: Pulse Density Modulation */
  RA_MSTP_IIRFA,            /* MSTPC21: IIR Filter Accelerator */
  RA_MSTP_TFU,              /* MSTPC20: Trigonometric Function Unit */
  RA_MSTP_MIPI_CSI,         /* MSTPC17: MIPI-CSI */
  RA_MSTP_CEU,              /* MSTPC16: Capture Engine Unit */
  RA_MSTP_VIN,              /* MSTPC16: Video Input (alias for CEU) */
  RA_MSTP_MACL,             /* MSTPC15: MAC Accelerator */
  RA_MSTP_ELC,              /* MSTPC14: Event Link Controller */
  RA_MSTP_DOC,              /* MSTPC13: Data Operation Circuit */
  RA_MSTP_SDHI,             /* MSTPC12: SD/MMC Host Interface */
  RA_MSTP_MIPI_DSI,         /* MSTPC10: MIPI Display Serial Interface */
  RA_MSTP_SRC,              /* MSTPC9: Sampling Rate Converter */
  RA_MSTP_SSIE0,            /* MSTPC8: Serial Sound Interface Enhanced 0 */
  RA_MSTP_SSIE1,            /* MSTPC7: Serial Sound Interface Enhanced 1 */
  RA_MSTP_DRW,              /* MSTPC6: 2D Drawing Engine */
  RA_MSTP_JPEG,             /* MSTPC5: JPEG Codec */
  RA_MSTP_GLCDC,            /* MSTPC4: Graphics LCD Controller */
  RA_MSTP_CTSU,             /* MSTPC3: Capacitive Touch Sensing Unit */
  RA_MSTP_PDC,              /* MSTPC2: Parallel Data Capture */
  RA_MSTP_CRC,              /* MSTPC1: Cyclic Redundancy Check Calculator */
  RA_MSTP_CAC,              /* MSTPC0: Clock Frequency Accuracy Measurement Circuit */

  /* MSTPCRD register modules (Bit 31 to 0) */
  RA_MSTP_ACMPHS0,          /* MSTPD28: High-Speed Analog Comparator 0 */
  RA_MSTP_ACMPHS1,          /* MSTPD27: High-Speed Analog Comparator 1 */
  RA_MSTP_ACMPHS2,          /* MSTPD26: High-Speed Analog Comparator 2 */
  RA_MSTP_ACMPHS3,          /* MSTPD25: High-Speed Analog Comparator 3 */
  RA_MSTP_RTC,              /* MSTPD23: Real Time Clock */
  RA_MSTP_TSN,              /* MSTPD22: Temperature Sensor */
  RA_MSTP_ADC0,             /* MSTPD21: A/D Converter 0 (ADC_B) */
  RA_MSTP_ADC1,             /* MSTPD20: A/D Converter 1 (ADC_B) */
  RA_MSTP_DAC0,             /* MSTPD20: D/A Converter 0 (DAC_B) - same bit as ADC1 */
  RA_MSTP_DAC1,             /* MSTPD19: D/A Converter 1 (DAC_B) */
  RA_MSTP_POEG0,            /* MSTPD14: Port Output Enable for GPT Group 0 */
  RA_MSTP_POEG1,            /* MSTPD13: Port Output Enable for GPT Group 1 */
  RA_MSTP_POEG2,            /* MSTPD12: Port Output Enable for GPT Group 2 */
  RA_MSTP_POEG3,            /* MSTPD11: Port Output Enable for GPT Group 3 */
  RA_MSTP_GPT_PDG,          /* MSTPD6: GPT Port Output Disable Group */
  RA_MSTP_AGT0,             /* MSTPD5: Asynchronous General Purpose Timer 0 */
  RA_MSTP_AGT1,             /* MSTPD4: Asynchronous General Purpose Timer 1 */

  /* MSTPCRE register modules (Bit 31 to 0) */
  RA_MSTP_GPT0,             /* MSTPE31: General PWM Timer 0 */
  RA_MSTP_GPT1,             /* MSTPE30: General PWM Timer 1 */
  RA_MSTP_GPT2,             /* MSTPE29: General PWM Timer 2 */
  RA_MSTP_GPT3,             /* MSTPE28: General PWM Timer 3 */
  RA_MSTP_GPT4,             /* MSTPE27: General PWM Timer 4 */
  RA_MSTP_GPT5,             /* MSTPE26: General PWM Timer 5 */
  RA_MSTP_GPT6,             /* MSTPE25: General PWM Timer 6 */
  RA_MSTP_GPT7,             /* MSTPE24: General PWM Timer 7 */
  RA_MSTP_GPT8,             /* MSTPE23: General PWM Timer 8 */
  RA_MSTP_GPT9,             /* MSTPE22: General PWM Timer 9 */
  RA_MSTP_GPT10,            /* MSTPE21: General PWM Timer 10 */
  RA_MSTP_GPT11,            /* MSTPE20: General PWM Timer 11 */
  RA_MSTP_GPT12,            /* MSTPE19: General PWM Timer 12 */
  RA_MSTP_GPT13,            /* MSTPE18: General PWM Timer 13 */
  RA_MSTP_ULPT0,            /* MSTPE9: Ultra-Low Power Timer 0 */
  RA_MSTP_ULPT1,            /* MSTPE8: Ultra-Low Power Timer 1 */

  R_MSTP_MAX_MODULE
} ra_mstp_module_t;

/* MSTP status structure */

typedef struct
{
  uint32_t mstpcra;    /* MSTPCRA register value */
  uint32_t mstpcrb;    /* MSTPCRB register value */
  uint32_t mstpcrc;    /* MSTPCRC register value */
  uint32_t mstpcrd;    /* MSTPCRD register value */
  uint32_t mstpcre;    /* MSTPCRE register value */
} ra_mstp_status_t;

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
 * Name: ra_mstp_initialize
 *
 * Description:
 *   Initialize the MSTP driver
 *
 ****************************************************************************/

void ra_mstp_initialize(void);

/****************************************************************************
 * Name: ra_mstp_start
 *
 * Description:
 *   Start (enable clock for) a peripheral module
 *
 * Input Parameters:
 *   module - The module to start
 *
 * Returned Value:
 *   OK on success; negated errno on failure
 *
 ****************************************************************************/

int ra_mstp_start(ra_mstp_module_t module);

/****************************************************************************
 * Name: ra_mstp_stop
 *
 * Description:
 *   Stop (disable clock for) a peripheral module
 *
 * Input Parameters:
 *   module - The module to stop
 *
 * Returned Value:
 *   OK on success; negated errno on failure
 *
 ****************************************************************************/

int ra_mstp_stop(ra_mstp_module_t module);

/****************************************************************************
 * Name: ra_mstp_is_stopped
 *
 * Description:
 *   Check if a peripheral module is stopped
 *
 * Input Parameters:
 *   module - The module to check
 *
 * Returned Value:
 *   true if module is stopped; false if running
 *
 ****************************************************************************/

bool ra_mstp_is_stopped(ra_mstp_module_t module);

/****************************************************************************
 * Name: ra_mstp_start_multiple
 *
 * Description:
 *   Start multiple modules atomically
 *
 * Input Parameters:
 *   modules - Array of modules to start
 *   count   - Number of modules in array
 *
 * Returned Value:
 *   OK on success; negated errno on failure
 *
 ****************************************************************************/

int ra_mstp_start_multiple(const ra_mstp_module_t *modules, int count);

/****************************************************************************
 * Name: ra_mstp_stop_multiple
 *
 * Description:
 *   Stop multiple modules atomically
 *
 * Input Parameters:
 *   modules - Array of modules to stop
 *   count   - Number of modules in array
 *
 * Returned Value:
 *   OK on success; negated errno on failure
 *
 ****************************************************************************/

int ra_mstp_stop_multiple(const ra_mstp_module_t *modules, int count);

/****************************************************************************
 * Name: ra_mstp_get_status
 *
 * Description:
 *   Get the current MSTP register status
 *
 * Input Parameters:
 *   status - Pointer to status structure to fill
 *
 ****************************************************************************/

void ra_mstp_get_status(ra_mstp_status_t *status);

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RA_RA8_MSTP_H */
