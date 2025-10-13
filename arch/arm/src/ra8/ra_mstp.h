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

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/


/* Compatibility aliases */
#define R_MSTP_MSTPCRB_SCI0            R_MSTP_MSTPCRB_MSTPB31
#define R_MSTP_MSTPCRB_SCI1            R_MSTP_MSTPCRB_MSTPB30
#define R_MSTP_MSTPCRB_SCI2            R_MSTP_MSTPCRB_MSTPB29
#define R_MSTP_MSTPCRB_SCI3            R_MSTP_MSTPCRB_MSTPB28
#define R_MSTP_MSTPCRB_SCI4            R_MSTP_MSTPCRB_MSTPB27
#define R_MSTP_MSTPCRB_SCI9            R_MSTP_MSTPCRB_MSTPB22
#define R_MSTP_MSTPCRB_SPI0            R_MSTP_MSTPCRB_MSTPB19
#define R_MSTP_MSTPCRB_SPI1            R_MSTP_MSTPCRB_MSTPB18
#define R_MSTP_MSTPCRB_USBFS           R_MSTP_MSTPCRB_MSTPB11
#define R_MSTP_MSTPCRB_IIC0            R_MSTP_MSTPCRB_MSTPB9
#define R_MSTP_MSTPCRB_IIC1            R_MSTP_MSTPCRB_MSTPB8

/* MSTPCRC - Module Stop Control Register C */

#define R_MSTP_MSTPCRC_MSTPC31         (1 << 31) /* 80000000: Renesas Secure IP Module Stop */
#define R_MSTP_MSTPCRC_MSTPC27         (1 << 27) /* 08000000: Controller Area Network with Flexible Data-Rate 0 Module Stop */
#define R_MSTP_MSTPCRC_MSTPC26         (1 << 26) /* 04000000: Controller Area Network with Flexible Data-Rate 1 Module Stop */
#define R_MSTP_MSTPCRC_MSTPC16         (1 << 16) /* 00010000: Capture Engine Unit Module Stop */
#define R_MSTP_MSTPCRC_MSTPC14         (1 << 14) /* 00004000: Event Link Controller Module Stop */
#define R_MSTP_MSTPCRC_MSTPC13         (1 << 13) /* 00002000: Data Operation Circuit Module Stop */
#define R_MSTP_MSTPCRC_MSTPC8          (1 <<  8) /* 00000100: Serial Sound Interface Enhanced 0 Module Stop */
#define R_MSTP_MSTPCRC_MSTPC7          (1 <<  7) /* 00000080: Serial Sound Interface Enhanced 1 Module Stop */
#define R_MSTP_MSTPCRC_MSTPC1          (1 <<  1) /* 00000002: Cyclic Redundancy Check Calculator Module Stop */
#define R_MSTP_MSTPCRC_MSTPC0          (1 <<  0) /* 00000001: Clock Frequency Accuracy Measurement Circuit Module Stop */

/* Compatibility aliases */
#define R_MSTP_MSTPCRC_SCE5            R_MSTP_MSTPCRC_MSTPC31
#define R_MSTP_MSTPCRC_CANFD0          R_MSTP_MSTPCRC_MSTPC27
#define R_MSTP_MSTPCRC_CANFD1          R_MSTP_MSTPCRC_MSTPC26
#define R_MSTP_MSTPCRC_CEU             R_MSTP_MSTPCRC_MSTPC16
#define R_MSTP_MSTPCRC_ELC             R_MSTP_MSTPCRC_MSTPC14
#define R_MSTP_MSTPCRC_DOC             R_MSTP_MSTPCRC_MSTPC13
#define R_MSTP_MSTPCRC_SSIE0           R_MSTP_MSTPCRC_MSTPC8
#define R_MSTP_MSTPCRC_SSI0            R_MSTP_MSTPCRC_MSTPC8
#define R_MSTP_MSTPCRC_SSIE1           R_MSTP_MSTPCRC_MSTPC7
#define R_MSTP_MSTPCRC_SSI1            R_MSTP_MSTPCRC_MSTPC7
#define R_MSTP_MSTPCRC_CRC             R_MSTP_MSTPCRC_MSTPC1
#define R_MSTP_MSTPCRC_CAC             R_MSTP_MSTPCRC_MSTPC0

/* MSTPCRD - Module Stop Control Register D */

#define R_MSTP_MSTPCRD_MSTPD28         (1 << 28) /* 10000000: High-Speed Analog Comparator 0 Module Stop */
#define R_MSTP_MSTPCRD_MSTPD27         (1 << 27) /* 08000000: High-Speed Analog Comparator 1 Module Stop */
#define R_MSTP_MSTPCRD_MSTPD23         (1 << 23) /* 00800000: Real-Time Clock Module Stop */
#define R_MSTP_MSTPCRD_MSTPD22         (1 << 22) /* 00400000: Temperature Sensor Module Stop */
#define R_MSTP_MSTPCRD_MSTPD20         (1 << 20) /* 00100000: 12-bit D/A Converter Module Stop */
#define R_MSTP_MSTPCRD_MSTPD16         (1 << 16) /* 00010000: 12-bit A/D Converter 0 Module Stop */
#define R_MSTP_MSTPCRD_MSTPD15         (1 << 15) /* 00008000: 12-bit A/D Converter 1 Module Stop */
#define R_MSTP_MSTPCRD_MSTPD14         (1 << 14) /* 00004000: Port Output Enable for GPT Group A Module Stop */
#define R_MSTP_MSTPCRD_MSTPD13         (1 << 13) /* 00002000: Port Output Enable for GPT Group B Module Stop */
#define R_MSTP_MSTPCRD_MSTPD12         (1 << 12) /* 00001000: Port Output Enable for GPT Group C Module Stop */
#define R_MSTP_MSTPCRD_MSTPD11         (1 << 11) /* 00000800: Port Output Enable for GPT Group D Module Stop */
#define R_MSTP_MSTPCRD_MSTPD5          (1 <<  5) /* 00000020: Low Power Asynchronous General Purpose Timer 0 Module Stop */
#define R_MSTP_MSTPCRD_MSTPD4          (1 <<  4) /* 00000010: Low Power Asynchronous General Purpose Timer 1 Module Stop */

/* Compatibility aliases */
#define R_MSTP_MSTPCRD_ACMPHS0         R_MSTP_MSTPCRD_MSTPD28
#define R_MSTP_MSTPCRD_ACMPHS1         R_MSTP_MSTPCRD_MSTPD27
#define R_MSTP_MSTPCRD_ACMPHS          R_MSTP_MSTPCRD_MSTPD28  /* Default to ACMPHS0 */
#define R_MSTP_MSTPCRD_RTC             R_MSTP_MSTPCRD_MSTPD23
#define R_MSTP_MSTPCRD_TSN             R_MSTP_MSTPCRD_MSTPD22
#define R_MSTP_MSTPCRD_DAC12           R_MSTP_MSTPCRD_MSTPD20
#define R_MSTP_MSTPCRD_DAC             R_MSTP_MSTPCRD_MSTPD20
#define R_MSTP_MSTPCRD_ADC0            R_MSTP_MSTPCRD_MSTPD16
#define R_MSTP_MSTPCRD_ADC1            R_MSTP_MSTPCRD_MSTPD15
#define R_MSTP_MSTPCRD_POEG0           R_MSTP_MSTPCRD_MSTPD14
#define R_MSTP_MSTPCRD_POEG1           R_MSTP_MSTPCRD_MSTPD13
#define R_MSTP_MSTPCRD_POEG2           R_MSTP_MSTPCRD_MSTPD12
#define R_MSTP_MSTPCRD_POEG3           R_MSTP_MSTPCRD_MSTPD11
#define R_MSTP_MSTPCRD_POEG            R_MSTP_MSTPCRD_MSTPD14  /* Default to POEG0 */
#define R_MSTP_MSTPCRD_AGT0            R_MSTP_MSTPCRD_MSTPD5
#define R_MSTP_MSTPCRD_AGT1            R_MSTP_MSTPCRD_MSTPD4

/* MSTPCRE - Module Stop Control Register E */

#define R_MSTP_MSTPCRE_MSTPE31         (1 << 31) /* 80000000: General PWM Timer 0 Module Stop */
#define R_MSTP_MSTPCRE_MSTPE30         (1 << 30) /* 40000000: General PWM Timer 1 Module Stop */
#define R_MSTP_MSTPCRE_MSTPE29         (1 << 29) /* 20000000: General PWM Timer 2 Module Stop */
#define R_MSTP_MSTPCRE_MSTPE28         (1 << 28) /* 10000000: General PWM Timer 3 Module Stop */
#define R_MSTP_MSTPCRE_MSTPE27         (1 << 27) /* 08000000: General PWM Timer 4 Module Stop */
#define R_MSTP_MSTPCRE_MSTPE26         (1 << 26) /* 04000000: General PWM Timer 5 Module Stop */
#define R_MSTP_MSTPCRE_MSTPE21         (1 << 21) /* 00200000: General PWM Timer 10 Module Stop */
#define R_MSTP_MSTPCRE_MSTPE20         (1 << 20) /* 00100000: General PWM Timer 11 Module Stop */
#define R_MSTP_MSTPCRE_MSTPE19         (1 << 19) /* 00080000: General PWM Timer 12 Module Stop */
#define R_MSTP_MSTPCRE_MSTPE18         (1 << 18) /* 00040000: General PWM Timer 13 Module Stop */
#define R_MSTP_MSTPCRE_MSTPE9          (1 <<  9) /* 00000200: Ultra-Low Power Timer 0 Module Stop */
#define R_MSTP_MSTPCRE_MSTPE8          (1 <<  8) /* 00000100: Ultra-Low Power Timer 1 Module Stop */

/* Compatibility aliases */
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
  RA_MSTP_USBFS,            /* MSTPB11: Universal Serial Bus 2.0 FS Interface */
  RA_MSTP_IIC0,             /* MSTPB9: I2C Bus Interface 0 */
  RA_MSTP_IIC1,             /* MSTPB8: I2C Bus Interface 1 */

  /* MSTPCRC register modules */
  RA_MSTP_SCE5,             /* MSTPC31: Renesas Secure IP */
  RA_MSTP_CANFD0,           /* MSTPC27: Controller Area Network with Flexible Data-Rate 0 */
  RA_MSTP_CANFD1,           /* MSTPC26: Controller Area Network with Flexible Data-Rate 1 */
  RA_MSTP_CEU,              /* MSTPC16: Capture Engine Unit */
  RA_MSTP_ELC,              /* MSTPC14: Event Link Controller */
  RA_MSTP_DOC,              /* MSTPC13: Data Operation Circuit */
  RA_MSTP_SSIE0,            /* MSTPC8: Serial Sound Interface Enhanced 0 */
  RA_MSTP_SSIE1,            /* MSTPC7: Serial Sound Interface Enhanced 1 */
  RA_MSTP_CRC,              /* MSTPC1: Cyclic Redundancy Check Calculator */
  RA_MSTP_CAC,              /* MSTPC0: Clock Frequency Accuracy Measurement Circuit */

  /* MSTPCRD register modules */
  RA_MSTP_ACMPHS0,          /* MSTPD28: High-Speed Analog Comparator 0 */
  RA_MSTP_ACMPHS1,          /* MSTPD27: High-Speed Analog Comparator 1 */
  RA_MSTP_RTC,              /* MSTPD23: Real Time Clock */
  RA_MSTP_TSN,              /* MSTPD22: Temperature Sensor */
  RA_MSTP_DAC12,            /* MSTPD20: 12-bit D/A Converter */
  RA_MSTP_ADC0,             /* MSTPD16: 12-bit A/D Converter 0 */
  RA_MSTP_ADC1,             /* MSTPD15: 12-bit A/D Converter 1 */
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
