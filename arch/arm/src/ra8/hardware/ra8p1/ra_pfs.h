/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_pfs.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_PFS_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_PFS_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* PFS Base Address */
#ifndef R_PFS_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_PFS_BASE           0x40400800
#else
#define R_PFS_BASE           0x50400800
#endif
#endif

/* PFS Register Array Strides */
#define R_PFS_PSEL_PORT_OFFSET          0x40
#define R_PFS_PSEL_PIN_OFFSET           0x04

/* PFS Register Offsets */

/* PFS Register Offsets - Use R_PFS_OFFSET(port, pin) macro */
#define R_PFS_OFFSET(port, pin)    ((port) * 0x40 + (pin) * 0x04)
#define R_PFS_HA_OFFSET(port, pin) ((port) * 0x40 + (pin) * 0x04)
#define R_PFS_BY_OFFSET(port, pin) ((port) * 0x40 + (pin) * 0x04)

/* Ethernet Control Register */
#define R_PFS_PFENET_OFFSET             0x00000500

/* Write-Protect Register for Secure */
#define R_PFS_PWPR_S_OFFSET             0x00000514

/* Port Security Attribution register offset */
#define R_PFS_P0SAR_OFFSET              0x00000530

/* PFS Register Addresses */

/* PFS Register Parameterized Macros */

/* PmnPFS - Pin Function Select Register */
#define R_PFS(port,pin)                 (R_PFS_BASE + (port)*R_PFS_PSEL_PORT_OFFSET + (pin)*R_PFS_PSEL_PIN_OFFSET)

/* Alternate register formats */
#define R_PFS_HA(port,pin)              (R_PFS_BASE + (port)*R_PFS_PSEL_PORT_OFFSET + (pin)*R_PFS_PSEL_PIN_OFFSET)
#define R_PFS_BY(port,pin)              (R_PFS_BASE + (port)*R_PFS_PSEL_PORT_OFFSET + (pin)*R_PFS_PSEL_PIN_OFFSET)

/* Other PFS registers */
#define R_PFS_PFENET                    (R_PFS_BASE + R_PFS_PFENET_OFFSET)
#define R_PFS_PWPR                      (R_PFS_BASE + R_PFS_PWPR_S_OFFSET)

/* Port Security Attribution Registers */
#define R_PFS_PMSAR(port)               (R_PFS_BASE + R_PFS_P0SAR_OFFSET + (port)*0x04)

/* Register bit definitions */
/* PFS Common Bit Definitions (applicable to all PmnPFS registers) */

#define R_PFS_PODR                      (1 << 0)  /* Port Output Data */

#define R_PFS_PIDR                      (1 << 1)  /* Pmn State */

#define R_PFS_PDR                       (1 << 2)  /* Port Direction */

#define R_PFS_PCR                       (1 << 4)  /* Pull-up Control */

#define R_PFS_NCODR                     (1 << 6)  /* N-Channel Open-Drain Control */

#define R_PFS_DSCR_SHIFT                (10)  /* Port Drive Capability */
#define R_PFS_DSCR_MASK                 0xc00
#  define R_PFS_DSCR_00                         (0 << R_PFS_DSCR_SHIFT)  /* Low drive */
#  define R_PFS_DSCR_01                         (1 << R_PFS_DSCR_SHIFT)  /* Middle drive */
#  define R_PFS_DSCR_10                         (2 << R_PFS_DSCR_SHIFT)  /* High-speed high-drive */
#  define R_PFS_DSCR_11                         (3 << R_PFS_DSCR_SHIFT)  /* High drive */

#define R_PFS_EOFR_SHIFT                (12)  /* Event on Falling/Event on Rising */
#define R_PFS_EOFR_MASK                 0x3000
#  define R_PFS_EOFR_00                         (0 << R_PFS_EOFR_SHIFT)  /* Don't care */
#  define R_PFS_EOFR_01                         (1 << R_PFS_EOFR_SHIFT)  /* Detect rising edge */
#  define R_PFS_EOFR_10                         (2 << R_PFS_EOFR_SHIFT)  /* Detect falling edge */
#  define R_PFS_EOFR_11                         (3 << R_PFS_EOFR_SHIFT)  /* Detect both edges */

#define R_PFS_ISEL                      (1 << 14)  /* IRQ Input Enable */

#define R_PFS_ASEL                      (1 << 15)  /* Analog Input Enable */

#define R_PFS_PMR                       (1 << 16)  /* Port Mode Control */

#define R_PFS_PSEL_SHIFT                (24)  /* Peripheral Select */
#define R_PFS_PSEL_MASK                 0x1f000000

/* PWPR - Write-Protect Register */

#define R_PWPR_PFSWE                    (6)  /* PmnPFS Register Write Enable */
#define R_PWPR_B0WI                     (7)  /* PFSWE Bit Write Disable */


/* Maximum number of channels */

#define PFS_MAX_CHANNELS    12

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_PFS_H */
