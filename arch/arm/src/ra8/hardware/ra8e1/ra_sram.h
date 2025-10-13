/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_sram.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SRAM_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SRAM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SRAM Base Address */
#ifndef R_SRAM_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_SRAM_BASE           0x40002000
#else
#define R_SRAM_BASE           0x50002000
#endif
#endif

/* SRAM Register Offsets */

#define R_SRAM_SRAMPRCR_S_OFFSET                  0x00000000  /* SRAM Protection Control Register for Secure */
#define R_SRAM_SRAMWTSC_OFFSET                    0x00000008  /* SRAM Wait State Control Register */
#define R_SRAM_SRAMCR1_OFFSET                     0x00000014  /* SRAM Control Register 1 */
#define R_SRAM_SRAMESR_OFFSET                     0x00000040  /* SRAM Error Status Register */
#define R_SRAM_SRAMESCLR_OFFSET                   0x00000048  /* SRAM Error Status Clear Register */
#define R_SRAM_SRAMEAR2_OFFSET                    0x00000058  /* SRAM Error Address Register */
#define R_SRAM_STBRAMCR_OFFSET                    0x00000110  /* Standby SRAM Control Register */
#define R_SRAM_STBRAMEAR_OFFSET                   0x00000150  /* Standby SRAM Error Address Register */

/* SRAM Register Addresses */

#define R_SRAM_SRAMPRCR_S                         (R_SRAM_BASE + R_SRAM_SRAMPRCR_S_OFFSET)
#define R_SRAM_SRAMWTSC                           (R_SRAM_BASE + R_SRAM_SRAMWTSC_OFFSET)
#define R_SRAM_SRAMCR1                            (R_SRAM_BASE + R_SRAM_SRAMCR1_OFFSET)
#define R_SRAM_SRAMESR                            (R_SRAM_BASE + R_SRAM_SRAMESR_OFFSET)
#define R_SRAM_SRAMESCLR                          (R_SRAM_BASE + R_SRAM_SRAMESCLR_OFFSET)
#define R_SRAM_SRAMEAR2                           (R_SRAM_BASE + R_SRAM_SRAMEAR2_OFFSET)
#define R_SRAM_STBRAMCR                           (R_SRAM_BASE + R_SRAM_STBRAMCR_OFFSET)
#define R_SRAM_STBRAMEAR                          (R_SRAM_BASE + R_SRAM_STBRAMEAR_OFFSET)

/* Register bit definitions */
/* SRAMPRCR_S Register bit definitions */
#define R_SRAM_SRAMPRCR_S_PR                      (1 << 0)  /* Register Write Control */

#define R_SRAM_SRAMPRCR_S_KW_SHIFT                (8)  /* Write Key Code */
#define R_SRAM_SRAMPRCR_S_KW_MASK                 0xff00

/* SRAMWTSC Register bit definitions */
#define R_SRAM_SRAMWTSC_WTEN                      (1 << 0)  /* SRAM Wait Enable */

/* SRAMCR1 Register bit definitions */
#define R_SRAM_SRAMCR1_OAD                        (1 << 0)  /* Operation after Detection for Parity Error Detection */

/* SRAMESR Register bit definitions */
#define R_SRAM_SRAMESR_ERR1                       (1 << 2)  /* SRAM1 Parity Error Status */

#define R_SRAM_SRAMESR_ERRS                       (1 << 14)  /* Standby SRAM Parity Error status */

#define R_SRAM_SRAMESR_ERR00                      (1 << 0)  /* SRAM0 1-bit ECC Error Status */

#define R_SRAM_SRAMESR_ERR01                      (1 << 1)  /* SRAM0 2-bit ECC Error Status */

/* SRAMESCLR Register bit definitions */
#define R_SRAM_SRAMESCLR_CLR1                     (1 << 2)  /* SRAM1 Parity Error Status Clear */

#define R_SRAM_SRAMESCLR_CLRS                     (1 << 14)  /* Standby SRAM Parity Error Status Clear */

#define R_SRAM_SRAMESCLR_CLR00                    (1 << 0)  /* SRAM0 1-bit ECC Error Status Clear */

#define R_SRAM_SRAMESCLR_CLR01                    (1 << 1)  /* SRAM0 2-bit ECC Error Status Clear */

/* SRAMEAR2 Register bit definitions */
#define R_SRAM_SRAMEAR2_EA_SHIFT                  (3)  /* SRAM Error Address */
#define R_SRAM_SRAMEAR2_EA_MASK                   0xffff8

/* STBRAMCR Register bit definitions */
#define R_SRAM_STBRAMCR_OAD                       (1 << 0)  /* Operation after detection */

/* STBRAMEAR Register bit definitions */
#define R_SRAM_STBRAMEAR_EA_SHIFT                 (2)  /* SRAM Error Address */
#define R_SRAM_STBRAMEAR_EA_MASK                  0x3fc


/* Maximum number of channels */

#define SRAM_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SRAM_H */
