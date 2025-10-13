/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_crc.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CRC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CRC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* CRC Base Address */
#ifndef R_CRC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_CRC_BASE           0x40310000
#else
#define R_CRC_BASE           0x50310000
#endif
#endif

/* CRC Register Offsets */

#define R_CRC_CRCCR0_OFFSET     0x00000000  /* CRC Control Register 0 */
#define R_CRC_CRCCR1_OFFSET     0x00000001  /* CRC Control Register 1 */
#define R_CRC_CRCDIR_OFFSET     0x00000004  /* CRC Data Input Register */
#define R_CRC_CRCDIR_BY_OFFSET     0x00000004  /* CRC Data Input Register */
#define R_CRC_CRCDOR_OFFSET     0x00000008  /* CRC Data Output Register */
#define R_CRC_CRCDOR_HA_OFFSET     0x00000008  /* CRC Data Output Register */
#define R_CRC_CRCDOR_BY_OFFSET     0x00000008  /* CRC Data Output Register */
#define R_CRC_CRCSAR_OFFSET     0x0000000c  /* Snoop Address Register */

/* CRC Register Addresses */

#define R_CRC_CRCCR0                 (R_CRC_BASE + R_CRC_CRCCR0_OFFSET)
#define R_CRC_CRCCR1                 (R_CRC_BASE + R_CRC_CRCCR1_OFFSET)
#define R_CRC_CRCDIR                 (R_CRC_BASE + R_CRC_CRCDIR_OFFSET)
#define R_CRC_CRCDIR_BY                 (R_CRC_BASE + R_CRC_CRCDIR_BY_OFFSET)
#define R_CRC_CRCDOR                 (R_CRC_BASE + R_CRC_CRCDOR_OFFSET)
#define R_CRC_CRCDOR_HA                 (R_CRC_BASE + R_CRC_CRCDOR_HA_OFFSET)
#define R_CRC_CRCDOR_BY                 (R_CRC_BASE + R_CRC_CRCDOR_BY_OFFSET)
#define R_CRC_CRCSAR                 (R_CRC_BASE + R_CRC_CRCSAR_OFFSET)

/* Register bit definitions */
/* CRCCR0 Register bit definitions */
#define R_CRC_CRCCR0_GPS_SHIFT                    (0)  /* CRC Generating Polynomial Switching */
#define R_CRC_CRCCR0_GPS_MASK                     0x7
#  define R_CRC_CRCCR0_GPS_001                            (1 << R_CRC_CRCCR0_GPS_SHIFT)  /* 8-bit CRC-8 (X8 + X2 + X + 1) */
#  define R_CRC_CRCCR0_GPS_010                            (2 << R_CRC_CRCCR0_GPS_SHIFT)  /* 16-bit CRC-16 (X16 + X15 + X2 + 1) */
#  define R_CRC_CRCCR0_GPS_011                            (3 << R_CRC_CRCCR0_GPS_SHIFT)  /* 16-bit CRC-CCITT (X16 + X12 + X5 + 1) */
#  define R_CRC_CRCCR0_GPS_100                            (4 << R_CRC_CRCCR0_GPS_SHIFT)  /* 32-bit CRC-32 (X32 + X26 + X23 + X22 + X16 + X12 + X11 +X10 + X8 + X7 + X5 + X4 + X2 + X + 1) */
#  define R_CRC_CRCCR0_GPS_101                            (5 << R_CRC_CRCCR0_GPS_SHIFT)  /* 32-bit CRC-32C (X32 + X28 + X27 + X26 + X25 + X23 + X22 + X20 + X19 + X18 + X14 + X13 + X11 + X10 + X9 + X8 + X6 + 1) */

#define R_CRC_CRCCR0_LMS                          (1 << 6)  /* CRC Calculation Switching */

#define R_CRC_CRCCR0_DORCLR                       (1 << 7)  /* CRCDOR/CRCDOR_HA/CRCDOR_BY Register Clear */

/* CRCCR1 Register bit definitions */
#define R_CRC_CRCCR1_CRCSWR                       (1 << 6)  /* Snoop-On-Write/Read Switch */

#define R_CRC_CRCCR1_CRCSEN                       (1 << 7)  /* Snoop Enable */

/* CRCDIR Register bit definitions */
#define R_CRC_CRCDIR_CRCDIR_SHIFT                 (0)  /* Calculation input Data (Case of CRC-32, CRC-32C ) */
#define R_CRC_CRCDIR_CRCDIR_MASK                  0xffffffff

/* CRCDOR Register bit definitions */
#define R_CRC_CRCDOR_CRCDOR_SHIFT                 (0)  /* Calculation output Data (Case of CRC-32, CRC-32C ) */
#define R_CRC_CRCDOR_CRCDOR_MASK                  0xffffffff

/* CRCDOR_BY Register bit definitions */
#define R_CRC_CRCDOR_BY_CRCDOR_BY_SHIFT           (0)  /* Calculation output Data (Case of CRC-8 ) */
#define R_CRC_CRCDOR_BY_CRCDOR_BY_MASK            0xff

/* CRCSAR Register bit definitions */
#define R_CRC_CRCSAR_CRCSA_SHIFT                  (0)  /* Register Snoop Address */
#define R_CRC_CRCSAR_CRCSA_MASK                   0x3fff


/* Maximum number of channels */

#define CRC_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CRC_H */
