/****************************************************************************
 * arch/arm/src/ra8/hardware/ra_gpio.h
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

/* Usage Example:
 *
 * // Configure P1_05 as output pin
 * gpio_pinset_t led_pin = GPIO_OUTPUT_PIN(1, 5);
 * ra_configgpio(led_pin);
 *
 * // Configure P0_03 as input with pull-up
 * gpio_pinset_t button_pin = GPIO_INPUT_PULLUP_PIN(0, 3);
 * ra_configgpio(button_pin);
 *
 * // Control GPIO pins
 * ra_gpiowrite(led_pin, true);     // Turn on LED
 * bool button_state = ra_gpioread(button_pin);  // Read button
 */

#ifndef __ARCH_ARM_SRC_RA_HARDWARE_RA_GPIO_H
#define __ARCH_ARM_SRC_RA_HARDWARE_RA_GPIO_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include "chip.h"
#include "hardware/ra_memorymap.h"
#include "hardware/ra_system.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Register Offsets *********************************************************/

#define R_PORT_PCNTR1_OFFSET            0x0000  /* Port Control Register 1 (32-bits) */
#define R_PORT_PDR_OFFSET               0x0000  /* Pmn Direction (16-bits) */
#define R_PORT_PODR_OFFSET              0x0002  /* Pmn Output Data (16-bits) */
#define R_PORT_PCNTR2_OFFSET            0x0004  /* Port Control Register 2 (32-bits) */
#define R_PORT_EIDR_OFFSET              0x0006  /* Port Event Input Data (16-bits) */
#define R_PORT_PIDR_OFFSET              0x0004  /* Pmn State (16-bits) */
#define R_PORT_PCNTR3_OFFSET            0x0008  /* Port Control Register 3 (32-bits) */
#define R_PORT_PORR_OFFSET              0x000a  /* Pmn Output Reset (16-bits) */
#define R_PORT_POSR_OFFSET              0x0008  /* Pmn Output Set (16-bits) */
#define R_PORT_PCNTR4_OFFSET            0x000c  /* Port Control Register 3 (32-bits) */
#define R_PORT_EOSR_OFFSET              0x000c  /* Pmn Output Reset (16-bits) */
#define R_PORT_EORR_OFFSET              0x000e  /* Pmn Event Output Set (16-bits) */

#define R_PORT_OFFSET                   0x0020  /* Relative Port Offset */

#define R_PFS_PSEL_PORT_OFFSET          0x40
#define R_PFS_PSEL_PIN_OFFSET           0x04
#define R_PWPR_OFFSET                   0x514
#define R_PMSAR_OFFSET                  0x530

/* PSCU - Port Security Control Unit Registers */

#define R_PSCU_PSARB_OFFSET             0x04
#define R_PSCU_PSARC_OFFSET             0x08
#define R_PSCU_PSARD_OFFSET             0x0C
#define R_PSCU_PSARE_OFFSET             0x10

#define R_PSCU_PSARB                    (R_PSCU_BASE + R_PSCU_PSARB_OFFSET)
#define R_PSCU_PSARC                    (R_PSCU_BASE + R_PSCU_PSARC_OFFSET)
#define R_PSCU_PSARD                    (R_PSCU_BASE + R_PSCU_PSARD_OFFSET)
#define R_PSCU_PSARE                    (R_PSCU_BASE + R_PSCU_PSARE_OFFSET)

/* Register Addresses *******************************************************/

#define R_PFS(port,pin)                 (R_PFS_BASE + (port)*R_PFS_PSEL_PORT_OFFSET + (pin)*R_PFS_PSEL_PIN_OFFSET)
#define R_PWPR                          (R_PFS_BASE + R_PWPR_OFFSET)

/* PMSAR - Port Security Attribution Registers */

#define R_PMSAR_BASE                      (R_PFS_BASE + R_PMSAR_OFFSET)
#define R_PMSAR(port)                     (R_PMSAR_BASE + (port) * 0x04)
#define R_PMSAR_NUM                       (10)  /* Ports 0-9 have PMSAR registers */

/* Register Bitfield Definitions ********************************************/

/* PFS - Pmn Pin Function Control Register */

#define R_PFS_PSEL_SHIFT_16       (24)   /* Hardware PSEL position in PFS register */
#define R_PFS_PSEL_SHIFT_8        (8)    /* PSEL position in gpio_pinset_t.cfg (bits 8-12) */
#define R_PFS_PSEL_MASK           (0x1f) /* 5-bit mask for PSEL field */
/* GPIO Configurations for gpio_pinset_t.cfg field, 1 << bit configuration */
#define R_PFS_PMR                 (16) /* Bit 16: Port Mode Control */
#define R_PFS_ASEL                (15) /* Bit 15: Analog Input enable */
#define R_PFS_ISEL                (14) /* Bit 14: IRQ input enable */
#define R_PFS_EOR                 (13) /* Bit 13: Event on Rising */
#define R_PFS_EOF                 (12) /* Bit 12: Event on Falling */
#define R_PFS_DSCR1               (11) /* Bit 11: Port Drive Capability 1 */
#define R_PFS_DSCR                (10) /* Bit 10: Port Drive Capability */
#define R_PFS_NCODR               ( 6) /* Bit 6: N-Channel Open Drain Control */
#define R_PFS_PCR                 ( 4) /* Bit 4: Pull-up Control */
#define R_PFS_PDR                 ( 2) /* Bit 2: Port Direction */
#define R_PFS_PIDR                ( 1) /* Bit 1: Port Input Data */
#define R_PFS_PODR                ( 0) /* Bit 0: Port Output Data */

/* PMISC Register Bits */
#define R_PWPR_B0WI        ( 7) /* 80: PFSWE Bit Write Disable */
#define R_PWPR_PFSWE       ( 6) /* 40: PFS Register Write Enable */

/* Bit definitions for PWPR are provided in ra_gpio.h to avoid duplication here. */

#define PFS_PSEL_HIZ                 (0x00 << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_AGT                 (0x01 << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_GPT                 (0x02 << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_AGT1                (0x03 << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_SCI                 (0x04 << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_SCI1                (0x05 << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_SPI                 (0x06 << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_IIC                 (0x07 << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_KINT                (0x08 << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_CLKOUT_ACMPLP_RTC   (0x09 << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_CAC_ADC14           (0x0a << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_CTSU                (0x0c << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_SLCDC               (0x0d << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_CAN                 (0x10 << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_SSIE                (0x12 << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_USBFS               (0x13 << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_DAC                 (0x14 << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_TRACE               (0x15 << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_DEBUG               (0x16 << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_OPAMP               (0x17 << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_XSPI                (0x18 << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_ETHERNET            (0x19 << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_CEU                 (0x1A << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_OSPI                (0x1B << R_PFS_PSEL_SHIFT_8)
#define PFS_PSEL_ULPT                (0x1C << R_PFS_PSEL_SHIFT_8)

/* Relative PORT Registers */

#  define R_PORT_PCNTR1(port)          (R_PORT0_BASE + (port)*R_PORT_OFFSET + R_PORT_PCNTR1_OFFSET)
#  define R_PORT_PODR(port)            (R_PORT0_BASE + (port)*R_PORT_OFFSET + R_PORT_PODR_OFFSET)
#  define R_PORT_PDR(port)             (R_PORT0_BASE + (port)*R_PORT_OFFSET + R_PORT_PDR_OFFSET)
#  define R_PORT_PCNTR2(port)          (R_PORT0_BASE + (port)*R_PORT_OFFSET + R_PORT_PCNTR2_OFFSET)
#  define R_PORT_EIDR(port)            (R_PORT0_BASE + (port)*R_PORT_OFFSET + R_PORT_EIDR_OFFSET)
#  define R_PORT_PIDR(port)            (R_PORT0_BASE + (port)*R_PORT_OFFSET + R_PORT_PIDR_OFFSET)
#  define R_PORT_PCNTR3(port)          (R_PORT0_BASE + (port)*R_PORT_OFFSET + R_PORT_PCNTR3_OFFSET)
#  define R_PORT_PORR(port)            (R_PORT0_BASE + (port)*R_PORT_OFFSET + R_PORT_PORR_OFFSET)
#  define R_PORT_POSR(port)            (R_PORT0_BASE + (port)*R_PORT_OFFSET + R_PORT_POSR_OFFSET)
#  define R_PORT_PCNTR4(port)          (R_PORT0_BASE + (port)*R_PORT_OFFSET + R_PORT_PCNTR4_OFFSET)
#  define R_PORT_EORR(port)            (R_PORT0_BASE + (port)*R_PORT_OFFSET + R_PORT_EORR_OFFSET)
#  define R_PORT_EOSR(port)            (R_PORT0_BASE + (port)*R_PORT_OFFSET + R_PORT_EOSR_OFFSET)

/* GPIO Configuration Bit Fields for cfg field in gpio_pinset_t struct */
/* These align with the R_PFS_* bit positions for direct use */

#define GPIO_CFG_OUTPUT                   (1 << R_PFS_PDR)    /* Output direction */
#define GPIO_CFG_PULLUP                   (1 << R_PFS_PCR)    /* Enable pull-up */
#define GPIO_CFG_OPENDRAIN                (1 << R_PFS_NCODR)  /* Open-drain output */
#define GPIO_CFG_DRIVE_MID                (1 << R_PFS_DSCR)   /* Mid drive strength */
#define GPIO_CFG_DRIVE_HIGH               ((1 << R_PFS_DSCR) | (1 << R_PFS_DSCR1)) /* High drive */
#define GPIO_CFG_ANALOG                   (1 << R_PFS_ASEL)   /* Analog mode */
#define GPIO_CFG_IRQ                      (1 << R_PFS_ISEL)   /* IRQ input enable */
#define GPIO_CFG_PERIPHERAL               (1 << R_PFS_PMR)    /* Peripheral mode */

/* Macros to extract fields from gpio_pinset_t */
#define GPIO_PORT_MASK    (0xFF000000UL)
#define GPIO_PIN_MASK     (0x00FF0000UL)
#define GPIO_CFG_MASK     (0x0000FFFFUL)

#define GPIO_PORT_SHIFT   (24)
#define GPIO_PIN_SHIFT    (16)
#define GPIO_CFG_SHIFT    (0)

#define GPIO_GET_PORT(pinset)  (((pinset) & GPIO_PORT_MASK) >> GPIO_PORT_SHIFT)
#define GPIO_GET_PIN(pinset)   (((pinset) & GPIO_PIN_MASK) >> GPIO_PIN_SHIFT)
#define GPIO_GET_CFG(pinset)   ((pinset) & GPIO_CFG_MASK)

/* GPIO Configuration macros are defined in ra8e1_pinmap.h */

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Public Functions Prototypes
 ****************************************************************************/

#endif /* __ARCH_ARM_SRC_RA_HARDWARE_RA_GPIO_H */
