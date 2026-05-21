/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_icu.h
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

/* RZV2H external interrupt register definitions
 *
 * RZ/V2H keeps these external interrupt status/configuration registers in
 * the INTC block.  Keep the historical RZV_ICU_* names for existing callers,
 * but use the R_INTC base address from the RZ/V2H hardware manual.
 *
 * The registers handle external interrupt signal conditioning:
 * - NMI: Non-Maskable Interrupt
 * - IRQ0-15: External interrupt pins with configurable detection
 * - TINT0-31: External trigger input pins
 */

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_ICU_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_ICU_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* INTC Base Address */

#define RZV_ICU_BASE                0x10400000

/* NMI Status and Control Registers */

#define RZV_ICU_NSCNT_OFFSET        0x0000  /* NMI Status Control Register */
#define RZV_ICU_NSCLR_OFFSET        0x0004  /* NMI Status Clear Register */
#define RZV_ICU_NMITR_OFFSET        0x0008  /* NMI Trigger Selection (NITSAR) */
/* 0x000c: RESERVED — do NOT write (CRIT-4: was wrongly named NMIFLTC) */

#define RZV_ICU_NSCNT               (RZV_ICU_BASE + RZV_ICU_NSCNT_OFFSET)
#define RZV_ICU_NSCLR               (RZV_ICU_BASE + RZV_ICU_NSCLR_OFFSET)
#define RZV_ICU_NMITR               (RZV_ICU_BASE + RZV_ICU_NMITR_OFFSET)

/* NMI/IRQ digital filter registers do NOT exist in the INTC block.
 * Per RZ/V2H hardware manual they live in the GPIO peripheral (FILONOFF/
 * FILNUM/FILCLKSEL).  Writing 0x0C or 0x1C in INTC hits RESERVED space.
 * CRIT-4: RZV_ICU_NMIFLTC and RZV_ICU_IFLTC are REMOVED.
 * Filter configuration must be done via GPIO FILONOFF/FILNUM/FILCLKSEL regs.
 */

/* IRQ Status and Control Registers */

#define RZV_ICU_ISCTR_OFFSET        0x0010  /* IRQ Status Control Register */
#define RZV_ICU_ISCLR_OFFSET        0x0014  /* IRQ Status Clear Register */
#define RZV_ICU_IITSR_OFFSET        0x0018  /* IRQ Detection Method Selection */
/* 0x001c: RESERVED1 — do NOT write (CRIT-4: was wrongly named IFLTC) */

#define RZV_ICU_ISCTR               (RZV_ICU_BASE + RZV_ICU_ISCTR_OFFSET)
#define RZV_ICU_ISCLR               (RZV_ICU_BASE + RZV_ICU_ISCLR_OFFSET)
#define RZV_ICU_IITSR               (RZV_ICU_BASE + RZV_ICU_IITSR_OFFSET)

/* TINT Status and Control Registers */

#define RZV_ICU_TSCTR_OFFSET        0x0020  /* TINT Status Control Register */
#define RZV_ICU_TSCLR_OFFSET        0x0024  /* TINT Status Clear Register */
#define RZV_ICU_TITSR0_OFFSET       0x0028  /* TINT Detection Method Selection 0 */
#define RZV_ICU_TITSR1_OFFSET       0x002c  /* TINT Detection Method Selection 1 */
#define RZV_ICU_TFLTC_OFFSET        0x0030  /* TINT Filter Control */

#define RZV_ICU_TSCTR               (RZV_ICU_BASE + RZV_ICU_TSCTR_OFFSET)
#define RZV_ICU_TSCLR               (RZV_ICU_BASE + RZV_ICU_TSCLR_OFFSET)
#define RZV_ICU_TITSR0              (RZV_ICU_BASE + RZV_ICU_TITSR0_OFFSET)
#define RZV_ICU_TITSR1              (RZV_ICU_BASE + RZV_ICU_TITSR1_OFFSET)
#define RZV_ICU_TFLTC               (RZV_ICU_BASE + RZV_ICU_TFLTC_OFFSET)

/* DMAC/DTC Activation Registers (for future use) */

#define RZV_ICU_DSCTR_OFFSET        0x0034  /* DMAC/DTC Status Control */
#define RZV_ICU_DSCLR_OFFSET        0x0038  /* DMAC/DTC Status Clear */
#define RZV_ICU_DITSR_OFFSET        0x003c  /* DMAC/DTC Detection Method */

/* Wakeup Interrupt Registers (for future use) */

#define RZV_ICU_WSCTR_OFFSET        0x0040  /* Wakeup Status Control */
#define RZV_ICU_WSCLR_OFFSET        0x0044  /* Wakeup Status Clear */
#define RZV_ICU_WITSR_OFFSET        0x0048  /* Wakeup Detection Method */
#define RZV_ICU_WFLTC_OFFSET        0x004c  /* Wakeup Filter Control */

/* Register Bit Definitions */

/* NMI Status Control Register (NSCNT) */

#define ICU_NSCNT_NSTAT             (1 << 0)  /* NMI Status Flag */

/* NMI Trigger Selection Register (NMITR) */

#define ICU_NMITR_NFLTEN            (1 << 0)  /* NMI Filter Enable */

/* NMI Filter Control: REMOVED — 0x0C is RESERVED in INTC block.
 * CRIT-4: filter config lives in GPIO FILONOFF/FILNUM/FILCLKSEL registers.
 */

/* IRQ Status Control Register (ISCTR) - 16 bits, one per IRQ0-15 */

#define ICU_ISCTR_STAT(n)           (1 << (n))  /* IRQ[n] Status Flag */

/* IRQ Detection Method Selection Register (IITSR) - 2 bits per IRQ */

#define ICU_IITSR_IITSEL_SHIFT(n)   ((n) * 2)
#define ICU_IITSR_IITSEL_MASK(n)    (0x3 << ICU_IITSR_IITSEL_SHIFT(n))
#define ICU_IITSR_IITSEL(n, val)    (((val) & 0x3) << ICU_IITSR_IITSEL_SHIFT(n))

/* IRQ Detection Method Values */

#define ICU_IITSR_LOWLEVEL          0  /* Low level detection */
#define ICU_IITSR_FALLING           1  /* Falling edge detection */
#define ICU_IITSR_RISING            2  /* Rising edge detection */
#define ICU_IITSR_BOTH              3  /* Both edges detection */

/* IRQ Filter Control: REMOVED — 0x1C is RESERVED1 in INTC block.
 * CRIT-4: filter clock selection lives in GPIO peripheral (FILCLKSEL).
 * Filter clock constants kept for future GPIO filter implementation.
 */

#define ICU_FCLKSEL_PCLKL_DIV1      0  /* PCLKL */
#define ICU_FCLKSEL_PCLKL_DIV8      1  /* PCLKL/8 */
#define ICU_FCLKSEL_PCLKL_DIV32     2  /* PCLKL/32 */
#define ICU_FCLKSEL_PCLKL_DIV64     3  /* PCLKL/64 */

/* TINT Status Control Register (TSCTR) - 32 bits, one per TINT0-31 */

#define ICU_TSCTR_STAT(n)           (1 << (n))  /* TINT[n] Status Flag */

/* TINT Detection Method Selection Registers (TITSR0/1) - 2 bits per TINT */

#define ICU_TITSR_TITSEL_SHIFT(n)   (((n) % 16) * 2)
#define ICU_TITSR_TITSEL_MASK(n)    (0x3 << ICU_TITSR_TITSEL_SHIFT(n))
#define ICU_TITSR_TITSEL(n, val)    (((val) & 0x3) << ICU_TITSR_TITSEL_SHIFT(n))

/* TITSR0 is for TINT0-15, TITSR1 is for TINT16-31 */

#define ICU_TITSR_LOWLEVEL          0  /* Low level detection */
#define ICU_TITSR_FALLING           1  /* Falling edge detection */
#define ICU_TITSR_RISING            2  /* Rising edge detection */
#define ICU_TITSR_BOTH              3  /* Both edges detection */

/* TINT Filter Control Register (TFLTC) */

#define ICU_TFLTC_FCLKSEL_SHIFT(n)  ((n) * 2)  /* Filter Clock for TINT[n] */
#define ICU_TFLTC_FCLKSEL_MASK(n)   (0x3 << ICU_TFLTC_FCLKSEL_SHIFT(n))

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_ICU_H */
