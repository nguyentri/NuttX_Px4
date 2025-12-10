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

/* MSTPCRB - Module Stop Control Register B */
#define R_MSTP_MSTPCRB_SCI0            R_MSTP_MSTPCRB_MSTPB31
#define R_MSTP_MSTPCRB_SCI1            R_MSTP_MSTPCRB_MSTPB30
#define R_MSTP_MSTPCRB_SCI2            R_MSTP_MSTPCRB_MSTPB29
#define R_MSTP_MSTPCRB_SCI3            R_MSTP_MSTPCRB_MSTPB28
#define R_MSTP_MSTPCRB_SCI4            R_MSTP_MSTPCRB_MSTPB27
#define R_MSTP_MSTPCRB_SCI5            R_MSTP_MSTPCRB_MSTPB26
#define R_MSTP_MSTPCRB_SCI6            R_MSTP_MSTPCRB_MSTPB25
#define R_MSTP_MSTPCRB_SCI7            R_MSTP_MSTPCRB_MSTPB24
#define R_MSTP_MSTPCRB_SCI8            R_MSTP_MSTPCRB_MSTPB23
#define R_MSTP_MSTPCRB_SCI9            R_MSTP_MSTPCRB_MSTPB22
#define R_MSTP_MSTPCRB_SPI0            R_MSTP_MSTPCRB_MSTPB19
#define R_MSTP_MSTPCRB_SPI1            R_MSTP_MSTPCRB_MSTPB18
#define R_MSTP_MSTPCRB_OSPI0           R_MSTP_MSTPCRB_MSTPB16 /* 00010000: Octal Serial Peripheral Interface 0 Module Stop */
#define R_MSTP_MSTPCRB_OSPI1           R_MSTP_MSTPCRB_MSTPB17 /* 00020000: Octal Serial Peripheral Interface 1 Module Stop */
#define R_MSTP_MSTPCRB_USBHS           R_MSTP_MSTPCRB_MSTPB12 /* 00001000: USB High Speed Module Stop */
#define R_MSTP_MSTPCRB_USBFS           R_MSTP_MSTPCRB_MSTPB11
#define R_MSTP_MSTPCRB_IIC0            R_MSTP_MSTPCRB_MSTPB9
#define R_MSTP_MSTPCRB_IIC1            R_MSTP_MSTPCRB_MSTPB8
#define R_MSTP_MSTPCRB_I3C             R_MSTP_MSTPCRB_MSTPB4  /* 00000010: I3C Bus Interface Module Stop */

/* Compatibility aliases */
#define R_MSTP_MSTPCRC_SCE5            R_MSTP_MSTPCRC_MSTPC31
#define R_MSTP_MSTPCRC_LAYER3_SWITCH   R_MSTP_MSTPCRC_MSTPC30  /* Layer 3 Ethernet Switch Module Stop */
#define R_MSTP_MSTPCRC_ETHER_PHY_CLK   R_MSTP_MSTPCRC_MSTPC28  /* Ether-PHY Clock Module Stop */
#define R_MSTP_MSTPCRC_CANFD0          R_MSTP_MSTPCRC_MSTPC27
#define R_MSTP_MSTPCRC_CANFD1          R_MSTP_MSTPCRC_MSTPC26
#define R_MSTP_MSTPCRC_CEU             R_MSTP_MSTPCRC_MSTPC16
#define R_MSTP_MSTPCRC_VIN             R_MSTP_MSTPCRC_MSTPC16
#define R_MSTP_MSTPCRC_MIPI_CSI        R_MSTP_MSTPCRC_MSTPC17
#define R_MSTP_MSTPCRC_ELC             R_MSTP_MSTPCRC_MSTPC14
#define R_MSTP_MSTPCRC_DOC             R_MSTP_MSTPCRC_MSTPC13
#define R_MSTP_MSTPCRC_SDHI            R_MSTP_MSTPCRC_MSTPC12
#define R_MSTP_MSTPCRC_SRC             R_MSTP_MSTPCRC_MSTPC9
#define R_MSTP_MSTPCRC_SSIE0           R_MSTP_MSTPCRC_MSTPC8
#define R_MSTP_MSTPCRC_SSI0            R_MSTP_MSTPCRC_MSTPC8
#define R_MSTP_MSTPCRC_SSIE1           R_MSTP_MSTPCRC_MSTPC7
#define R_MSTP_MSTPCRC_SSI1            R_MSTP_MSTPCRC_MSTPC7
#define R_MSTP_MSTPCRC_DRW             R_MSTP_MSTPCRC_MSTPC6
#define R_MSTP_MSTPCRC_JPEG            R_MSTP_MSTPCRC_MSTPC5
#define R_MSTP_MSTPCRC_GLCDC           R_MSTP_MSTPCRC_MSTPC4
#define R_MSTP_MSTPCRC_CTSU            R_MSTP_MSTPCRC_MSTPC3
#define R_MSTP_MSTPCRC_PDC             R_MSTP_MSTPCRC_MSTPC2
#define R_MSTP_MSTPCRC_CRC             R_MSTP_MSTPCRC_MSTPC1
#define R_MSTP_MSTPCRC_CAC             R_MSTP_MSTPCRC_MSTPC0

/* MSTPCRD - Module Stop Control Register D */
#define R_MSTP_MSTPCRD_OPAMP           R_MSTP_MSTPCRD_MSTPD31
#define R_MSTP_MSTPCRD_ACMPLP          R_MSTP_MSTPCRD_MSTPD29
#define R_MSTP_MSTPCRD_ACMPHS0         R_MSTP_MSTPCRD_MSTPD28
#define R_MSTP_MSTPCRD_ACMPHS1         R_MSTP_MSTPCRD_MSTPD27
#define R_MSTP_MSTPCRD_ACMPHS          R_MSTP_MSTPCRD_MSTPD28  /* Default to ACMPHS0 */
#define R_MSTP_MSTPCRD_RTC             R_MSTP_MSTPCRD_MSTPD23
#define R_MSTP_MSTPCRD_TSN             R_MSTP_MSTPCRD_MSTPD22
#define R_MSTP_MSTPCRD_ADC0            R_MSTP_MSTPCRD_MSTPD21
#define R_MSTP_MSTPCRD_ADC1            R_MSTP_MSTPCRD_MSTPD20
#define R_MSTP_MSTPCRD_DAC0            R_MSTP_MSTPCRD_MSTPD20
#define R_MSTP_MSTPCRD_DAC1            R_MSTP_MSTPCRD_MSTPD19
#define R_MSTP_MSTPCRD_POEG0           R_MSTP_MSTPCRD_MSTPD14
#define R_MSTP_MSTPCRD_POEG1           R_MSTP_MSTPCRD_MSTPD13
#define R_MSTP_MSTPCRD_POEG2           R_MSTP_MSTPCRD_MSTPD12
#define R_MSTP_MSTPCRD_POEG3           R_MSTP_MSTPCRD_MSTPD11
#define R_MSTP_MSTPCRD_POEG            R_MSTP_MSTPCRD_MSTPD14  /* Default to POEG0 */
#define R_MSTP_MSTPCRD_AGT0            R_MSTP_MSTPCRD_MSTPD5
#define R_MSTP_MSTPCRD_AGT1            R_MSTP_MSTPCRD_MSTPD4

/* MSTPCRE - Module Stop Control Register E */
#define R_MSTP_MSTPCRE_GPT0            R_MSTP_MSTPCRE_MSTPE31
#define R_MSTP_MSTPCRE_GPT1            R_MSTP_MSTPCRE_MSTPE30
#define R_MSTP_MSTPCRE_GPT2            R_MSTP_MSTPCRE_MSTPE29
#define R_MSTP_MSTPCRE_GPT3            R_MSTP_MSTPCRE_MSTPE28
#define R_MSTP_MSTPCRE_GPT4            R_MSTP_MSTPCRE_MSTPE27
#define R_MSTP_MSTPCRE_GPT5            R_MSTP_MSTPCRE_MSTPE26
#define R_MSTP_MSTPCRE_GPT10           R_MSTP_MSTPCRE_MSTPE21
#define R_MSTP_MSTPCRE_GPT11           R_MSTP_MSTPCRE_MSTPE20
#define R_MSTP_MSTPCRE_GPT12           R_MSTP_MSTPCRE_MSTPE19
#define R_MSTP_MSTPCRE_GPT13           R_MSTP_MSTPCRE_MSTPE18
#define R_MSTP_MSTPCRE_ULPT0           R_MSTP_MSTPCRE_MSTPE9
#define R_MSTP_MSTPCRE_ULPT1           R_MSTP_MSTPCRE_MSTPE8

/* Module enumeration for MSTP control */

typedef enum
{
  /* MSTPCRA register modules */
  RA_MSTP_UNNECESSARY = 0,  /* MSTPA0: Unnecessary Circuit */
  RA_MSTP_SRAM1,            /* MSTPA1: SRAM1 */
  RA_MSTP_STANDBY_SRAM,     /* MSTPA15: Standby SRAM */
  RA_MSTP_DMAC_DTC,         /* MSTPA22: DMA Controller and Data Transfer Controller */

  /* MSTPCRB register modules */
  RA_MSTP_SCI0,             /* MSTPB31: Serial Communication Interface 0 */
  RA_MSTP_SCI1,             /* MSTPB30: Serial Communication Interface 1 */
  RA_MSTP_SCI2,             /* MSTPB29: Serial Communication Interface 2 */
  RA_MSTP_SCI3,             /* MSTPB28: Serial Communication Interface 3 */
  RA_MSTP_SCI4,             /* MSTPB27: Serial Communication Interface 4 */
  RA_MSTP_SCI9,             /* MSTPB22: Serial Communication Interface 9 */
  RA_MSTP_SPI0,             /* MSTPB19: Serial Peripheral Interface 0 */
  RA_MSTP_SPI1,             /* MSTPB18: Serial Peripheral Interface 1 */
  RA_MSTP_SCI10,            /* MSTPB16: SCI Communication Interface 10 */
  RA_MSTP_ETHERCAT,         /* MSTPB15: EtherCAT */
  RA_MSTP_OSPI0,            /* MSTPB16: Octal Serial Peripheral Interface 0 */
  RA_MSTP_OSPI1,            /* MSTPB17: Octal Serial Peripheral Interface 1 */
  RA_MSTP_USBHS,            /* MSTPB12: USB High Speed */
  RA_MSTP_USBFS,            /* MSTPB11: Universal Serial Bus 2.0 FS Interface */
  RA_MSTP_IIC0,             /* MSTPB9: I2C Bus Interface 0 */
  RA_MSTP_IIC1,             /* MSTPB8: I2C Bus Interface 1 */
  RA_MSTP_I3C,              /* MSTPB4: I3C */

  /* MSTPCRC register modules */
  RA_MSTP_SCE5,             /* MSTPC31: Renesas Secure IP */
  RA_MSTP_LAYER3_SWITCH,    /* MSTPC30: Layer 3 Ethernet Switch (ESWM) */
  RA_MSTP_ETHER_PHY_CLK,    /* MSTPC28: Ether-PHY Clock */
  RA_MSTP_CANFD0,           /* MSTPC27: Controller Area Network with Flexible Data-Rate 0 */
  RA_MSTP_CANFD1,           /* MSTPC26: Controller Area Network with Flexible Data-Rate 1 */
  RA_MSTP_CEU,              /* MSTPC16: Capture Engine Unit */
  RA_MSTP_VIN,              /* MSTPC16: Video Input (same as CEU) */
  RA_MSTP_MIPI_CSI,         /* MSTPC17: MIPI-CSI */
  RA_MSTP_ELC,              /* MSTPC14: Event Link Controller */
  RA_MSTP_DOC,              /* MSTPC13: Data Operation Circuit */
  RA_MSTP_SDHI,             /* MSTPC12: SD/MMC Host Interface */
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

  /* MSTPCRD register modules */
  RA_MSTP_OPAMP,            /* MSTPD31: Operational Amplifier */
  RA_MSTP_ACMPLP,           /* MSTPD29: Low-Power Analog Comparator */
  RA_MSTP_ACMPHS0,          /* MSTPD28: High-Speed Analog Comparator 0 */
  RA_MSTP_ACMPHS1,          /* MSTPD27: High-Speed Analog Comparator 1 */
  RA_MSTP_RTC,              /* MSTPD23: Real Time Clock */
  RA_MSTP_TSN,              /* MSTPD22: Temperature Sensor */
  RA_MSTP_ADC0,             /* MSTPD21: 12-bit A/D Converter 0 */
  RA_MSTP_ADC1,             /* MSTPD20: 12-bit A/D Converter 1 */
  RA_MSTP_DAC0,             /* MSTPD20: 12-bit D/A Converter 0 */
  RA_MSTP_DAC1,             /* MSTPD19: 12-bit D/A Converter 1 */
  RA_MSTP_POEG0,            /* MSTPD14: Port Output Enable for GPT Group A */
  RA_MSTP_POEG1,            /* MSTPD13: Port Output Enable for GPT Group B */
  RA_MSTP_POEG2,            /* MSTPD12: Port Output Enable for GPT Group C */
  RA_MSTP_POEG3,            /* MSTPD11: Port Output Enable for GPT Group D */
  RA_MSTP_AGT0,             /* MSTPD5: Low Power Asynchronous General Purpose Timer 0 */
  RA_MSTP_AGT1,             /* MSTPD4: Low Power Asynchronous General Purpose Timer 1 */

  /* MSTPCRE register modules */
  RA_MSTP_GPT0,             /* MSTPE31: General PWM Timer 0 */
  RA_MSTP_GPT1,             /* MSTPE30: General PWM Timer 1 */
  RA_MSTP_GPT2,             /* MSTPE29: General PWM Timer 2 */
  RA_MSTP_GPT3,             /* MSTPE28: General PWM Timer 3 */
  RA_MSTP_GPT4,             /* MSTPE27: General PWM Timer 4 */
  RA_MSTP_GPT5,             /* MSTPE26: General PWM Timer 5 */
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
