/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_elc.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ELC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ELC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ELC Base Address */
#ifndef R_ELC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_ELC_BASE           0x40201000
#else
#define R_ELC_BASE           0x50201000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_ELC_CH_STRIDE    0x00000004
#define R_ELC_CH_BASE(ch)   (R_ELC_BASE + ((uint32_t)(ch) * R_ELC_CH_STRIDE))

/* ELC Register Offsets */

#define R_ELC_ELCR_OFFSET                         0x00000000  /* Event Link Controller Register */
/* ELSEGR%s Registers (0-1) */
#define R_ELC_ELSEGR_OFFSET                       0x00000004  /* Event Link Software Event Generation Register %s */
#define R_ELC_ELSEGR_INCREMENT                    0x00000004
/* ELSR%s Registers (0-17) */
#define R_ELC_ELSR_OFFSET                         0x00000020  /* Event Link Setting Registern */
#define R_ELC_ELSR_INCREMENT                      0x00000004
#define R_ELC_ELSR30_OFFSET                       0x00000098  /* Event Link Setting Register30 */
#define R_ELC_ELCSARA_OFFSET                      0x000000e0  /* Event Link Controller Security Attribution Register A */
#define R_ELC_ELCSARB_OFFSET                      0x000000e4  /* Event Link Controller Security Attribution Register B */
#define R_ELC_ELCPARA_OFFSET                      0x000000f0  /* Event Link Controller Privilege Attribution Register A */
#define R_ELC_ELCPARB_OFFSET                      0x000000f4  /* Event Link Controller Privilege Attribution Register B */

/* ELC Register Addresses */

#define R_ELC_ELCR                                (R_ELC_BASE + R_ELC_ELCR_OFFSET)
#define R_ELC_ELSEGR(n)                           (R_ELC_BASE + R_ELC_ELSEGR_OFFSET + (n)*0x00000004)
#define R_ELC_ELSR(n)                             (R_ELC_BASE + R_ELC_ELSR_OFFSET + (n)*0x00000004)
#define R_ELC_ELSR30                              (R_ELC_BASE + R_ELC_ELSR30_OFFSET)
#define R_ELC_ELCSARA                             (R_ELC_BASE + R_ELC_ELCSARA_OFFSET)
#define R_ELC_ELCSARB                             (R_ELC_BASE + R_ELC_ELCSARB_OFFSET)
#define R_ELC_ELCPARA                             (R_ELC_BASE + R_ELC_ELCPARA_OFFSET)
#define R_ELC_ELCPARB                             (R_ELC_BASE + R_ELC_ELCPARB_OFFSET)

/* Register bit definitions */
/* ELCR Register bit definitions */
#define R_ELC_ELCR_ELCON                          (1 << 7)  /* All Event Link Enable */

/* ELSEGR Register bit definitions */
#define R_ELC_ELSEGR_SEG                          (1 << 0)  /* Software Event Generation */

#define R_ELC_ELSEGR_WE                           (1 << 6)  /* SEG Bit Write Enable */

#define R_ELC_ELSEGR_WI                           (1 << 7)  /* ELSEGR Register Write Disable */

/* ELSR Register bit definitions */
#define R_ELC_ELSR_ELS_SHIFT                      (0)  /* Event Link Select */
#define R_ELC_ELSR_ELS_MASK                       0x1ff

/* ELSR30 Register bit definitions */
#define R_ELC_ELSR30_ELS_SHIFT                    (0)  /* Event Link Select */
#define R_ELC_ELSR30_ELS_MASK                     0x1ff

/* ELCSARA Register bit definitions */
#define R_ELC_ELCSARA_ELCR                        (1 << 0)  /* Event Link Controller Register Security Attribution */

#define R_ELC_ELCSARA_ELSEGR0                     (1 << 1)  /* Event Link Software Event Generation Register 0 Security Attribution */

#define R_ELC_ELCSARA_ELSEGR1                     (1 << 2)  /* Event Link Software Event Generation Register 1 Security Attribution */

/* ELCSARB Register bit definitions */
#define R_ELC_ELCSARB_ELSR_SHIFT                  (0)  /* Event Link Setting Register n Security Attribution */
#define R_ELC_ELCSARB_ELSR_MASK                   0x3ffff
#  define R_ELC_ELCSARB_ELSR_0                            (0 << R_ELC_ELCSARB_ELSR_SHIFT)  /* Secure */
#  define R_ELC_ELCSARB_ELSR_1                            (1 << R_ELC_ELCSARB_ELSR_SHIFT)  /* Non-secure */

#define R_ELC_ELCSARB_ELSR0                       (1 << 0)  /* Event Link Setting Register 0 Security Attribution */

#define R_ELC_ELCSARB_ELSR1                       (1 << 1)  /* Event Link Setting Register 1 Security Attribution */

#define R_ELC_ELCSARB_ELSR2                       (1 << 2)  /* Event Link Setting Register 2 Security Attribution */

#define R_ELC_ELCSARB_ELSR3                       (1 << 3)  /* Event Link Setting Register 3 Security Attribution */

#define R_ELC_ELCSARB_ELSR4                       (1 << 4)  /* Event Link Setting Register 4 Security Attribution */

#define R_ELC_ELCSARB_ELSR5                       (1 << 5)  /* Event Link Setting Register 5 Security Attribution */

#define R_ELC_ELCSARB_ELSR6                       (1 << 6)  /* Event Link Setting Register 6 Security Attribution */

#define R_ELC_ELCSARB_ELSR7                       (1 << 7)  /* Event Link Setting Register 7 Security Attribution */

#define R_ELC_ELCSARB_ELSR8                       (1 << 8)  /* Event Link Setting Register 8 Security Attribution */

#define R_ELC_ELCSARB_ELSR9                       (1 << 9)  /* Event Link Setting Register 9 Security Attribution */

#define R_ELC_ELCSARB_ELSR10                      (1 << 10)  /* Event Link Setting Register 10 Security Attribution */

#define R_ELC_ELCSARB_ELSR11                      (1 << 11)  /* Event Link Setting Register 11 Security Attribution */

#define R_ELC_ELCSARB_ELSR12                      (1 << 12)  /* Event Link Setting Register 12 Security Attribution */

#define R_ELC_ELCSARB_ELSR13                      (1 << 13)  /* Event Link Setting Register 13 Security Attribution */

#define R_ELC_ELCSARB_ELSR14                      (1 << 14)  /* Event Link Setting Register 14 Security Attribution */

#define R_ELC_ELCSARB_ELSR15                      (1 << 15)  /* Event Link Setting Register 15 Security Attribution */

#define R_ELC_ELCSARB_ELSR16                      (1 << 16)  /* Event Link Setting Register 16 Security Attribution */

#define R_ELC_ELCSARB_ELSR17                      (1 << 17)  /* Event Link Setting Register 17 Security Attribution */

#define R_ELC_ELCSARB_ELSR30                      (1 << 30)  /* Event Link Setting Register 30 Security Attribution */

/* ELCPARA Register bit definitions */
#define R_ELC_ELCPARA_ELCR                        (1 << 0)  /* Event Link Controller Register Privilege Attribution */

#define R_ELC_ELCPARA_ELSEGR0                     (1 << 1)  /* Event Link Software Event Generation Register 0 Privilege Attribution */

#define R_ELC_ELCPARA_ELSEGR1                     (1 << 2)  /* Event Link Software Event Generation Register 1 Privilege Attribution */

/* ELCPARB Register bit definitions */
#define R_ELC_ELCPARB_ELSR_SHIFT                  (0)  /* Event Link Setting Register n Privilege Attribution */
#define R_ELC_ELCPARB_ELSR_MASK                   0x3ffff
#  define R_ELC_ELCPARB_ELSR_0                            (0 << R_ELC_ELCPARB_ELSR_SHIFT)  /* Privileged */
#  define R_ELC_ELCPARB_ELSR_1                            (1 << R_ELC_ELCPARB_ELSR_SHIFT)  /* Unprivileged */

#define R_ELC_ELCPARB_ELSR0                       (1 << 0)  /* Event Link Setting Register 0 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR1                       (1 << 1)  /* Event Link Setting Register 1 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR2                       (1 << 2)  /* Event Link Setting Register 2 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR3                       (1 << 3)  /* Event Link Setting Register 3 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR4                       (1 << 4)  /* Event Link Setting Register 4 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR5                       (1 << 5)  /* Event Link Setting Register 5 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR6                       (1 << 6)  /* Event Link Setting Register 6 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR7                       (1 << 7)  /* Event Link Setting Register 7 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR8                       (1 << 8)  /* Event Link Setting Register 8 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR9                       (1 << 9)  /* Event Link Setting Register 9 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR10                      (1 << 10)  /* Event Link Setting Register 10 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR11                      (1 << 11)  /* Event Link Setting Register 11 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR12                      (1 << 12)  /* Event Link Setting Register 12 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR13                      (1 << 13)  /* Event Link Setting Register 13 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR14                      (1 << 14)  /* Event Link Setting Register 14 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR15                      (1 << 15)  /* Event Link Setting Register 15 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR16                      (1 << 16)  /* Event Link Setting Register 16 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR17                      (1 << 17)  /* Event Link Setting Register 17 Privilege Attribution */

#define R_ELC_ELCPARB_ELSR30                      (1 << 30)  /* Event Link Setting Register 30 Privilege Attribution */


/* Maximum number of channels */

#define ELC_MAX_CHANNELS    18

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ELC_H */
