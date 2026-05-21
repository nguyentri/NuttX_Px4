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

#define R_CRC_CRCCR0_OFFSET                       0x00000000  /* CRC Control Register0 */
#define R_CRC_CRCCR1_OFFSET                       0x00000001  /* CRC Control Register1 */
#define R_CRC_CRCDIR_OFFSET                       0x00000004  /* CRC Data Input Register */
#define R_CRC_CRCDIR_BY_OFFSET                    0x00000004  /* CRC Data Input Register (byte access) */
#define R_CRC_CRCDOR_OFFSET                       0x00000008  /* CRC Data Output Register */
#define R_CRC_CRCDOR_HA_OFFSET                    0x00000008  /* CRC Data Output Register (halfword access) */
#define R_CRC_CRCDOR_BY_OFFSET                    0x00000008  /* CRC Data Output Register(byte access) */
#define R_CRC_CRCSAR_OFFSET                       0x0000000c  /* Snoop Address Register */

/* CRC Register Addresses */

#define R_CRC_CRCCR0                              (R_CRC_BASE + R_CRC_CRCCR0_OFFSET)
#define R_CRC_CRCCR1                              (R_CRC_BASE + R_CRC_CRCCR1_OFFSET)
#define R_CRC_CRCDIR                              (R_CRC_BASE + R_CRC_CRCDIR_OFFSET)
#define R_CRC_CRCDIR_BY                           (R_CRC_BASE + R_CRC_CRCDIR_BY_OFFSET)
#define R_CRC_CRCDOR                              (R_CRC_BASE + R_CRC_CRCDOR_OFFSET)
#define R_CRC_CRCDOR_HA                           (R_CRC_BASE + R_CRC_CRCDOR_HA_OFFSET)
#define R_CRC_CRCDOR_BY                           (R_CRC_BASE + R_CRC_CRCDOR_BY_OFFSET)
#define R_CRC_CRCSAR                              (R_CRC_BASE + R_CRC_CRCSAR_OFFSET)

/* Register bit definitions */
/* CRCCR0 Register bit definitions */
#define R_CRC_CRCCR0_DORCLR                       (1 << 7)  /* CRCDOR Register Clear */

#define R_CRC_CRCCR0_LMS                          (1 << 6)  /* CRC Calculation Switching */

#define R_CRC_CRCCR0_GPS_SHIFT                    (0)  /* CRC Generating Polynomial Switching */
#define R_CRC_CRCCR0_GPS_MASK                     0x7
#  define R_CRC_CRCCR0_GPS_000                            (0 << R_CRC_CRCCR0_GPS_SHIFT)  /* No calculation is executed. */
#  define R_CRC_CRCCR0_GPS_001                            (1 << R_CRC_CRCCR0_GPS_SHIFT)  /* 8-bit CRC-8 (X8 + X2 + X + 1) */
#  define R_CRC_CRCCR0_GPS_010                            (2 << R_CRC_CRCCR0_GPS_SHIFT)  /* 16-bit CRC-16 (X16 + X15 + X2 + 1) */
#  define R_CRC_CRCCR0_GPS_011                            (3 << R_CRC_CRCCR0_GPS_SHIFT)  /* 16-bit CRC-CCITT (X16 + X12 + X5 + 1) */
#  define R_CRC_CRCCR0_GPS_100                            (4 << R_CRC_CRCCR0_GPS_SHIFT)  /* 32-bit CRC-32 (X32+X26+X23+X22+X16+X12+X11+X10+X8+X7+X5+X4+X2+X+1) */
#  define R_CRC_CRCCR0_GPS_101                            (5 << R_CRC_CRCCR0_GPS_SHIFT)  /* 32-bit CRC-32C (X32+X28+X27+X26+ X25+X23+X22+X20+X19+X18+X14+X13+X11+X10+X9+X8+X6+1) */

/* CRCCR1 Register bit definitions */
#define R_CRC_CRCCR1_CRCSEN                       (1 << 7)  /* Snoop enable bit */

#define R_CRC_CRCCR1_CRCSWR                       (1 << 6)  /* Snoop-on-write/read switch bit */

/* CRCDIR Register bit definitions */
#define R_CRC_CRCDIR_CRCDIR_SHIFT                 (0)  /* Calculation input Data (Case of CRC-32, CRC-32C ) */
#define R_CRC_CRCDIR_CRCDIR_MASK                  0xffffffff

/* CRCDIR_BY Register bit definitions */
#define R_CRC_CRCDIR_BY_CRCDIR_BY_SHIFT           (0)  /* Calculation input Data ( Case of CRC-8, CRC-16 or CRC-CCITT ) */
#define R_CRC_CRCDIR_BY_CRCDIR_BY_MASK            0xff

/* CRCDOR Register bit definitions */
#define R_CRC_CRCDOR_CRCDOR_SHIFT                 (0)  /* Calculation output Data (Case of CRC-32, CRC-32C ) */
#define R_CRC_CRCDOR_CRCDOR_MASK                  0xffffffff

/* CRCDOR_HA Register bit definitions */
#define R_CRC_CRCDOR_HA_CRCDOR_HA_SHIFT           (0)  /* Calculation output Data (Case of CRC-16 or CRC-CCITT ) */
#define R_CRC_CRCDOR_HA_CRCDOR_HA_MASK            0xffff

/* CRCDOR_BY Register bit definitions */
#define R_CRC_CRCDOR_BY_CRCDOR_BY_SHIFT           (0)  /* Calculation output Data (Case of CRC-8 ) */
#define R_CRC_CRCDOR_BY_CRCDOR_BY_MASK            0xff

/* CRCSAR Register bit definitions */
#define R_CRC_CRCSAR_CRCSA_SHIFT                  (0)  /* snoop address bitSet the I/O register address to snoop */
#define R_CRC_CRCSAR_CRCSA_MASK                   0x3fff
#  define R_CRC_CRCSAR_CRCSA_0X0003                       (3 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI0.TDR */
#  define R_CRC_CRCSAR_CRCSA_0X0005                       (5 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI0.RDR */
#  define R_CRC_CRCSAR_CRCSA_0X0023                       (35 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI1.TDR */
#  define R_CRC_CRCSAR_CRCSA_0X0025                       (37 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI1.RDR */
#  define R_CRC_CRCSAR_CRCSA_0X0043                       (67 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI2.TDR */
#  define R_CRC_CRCSAR_CRCSA_0X0045                       (69 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI2.RDR */
#  define R_CRC_CRCSAR_CRCSA_0X0063                       (99 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI3.TDR */
#  define R_CRC_CRCSAR_CRCSA_0X0065                       (101 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI3.RDR */
#  define R_CRC_CRCSAR_CRCSA_0X0083                       (131 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI4.TDR */
#  define R_CRC_CRCSAR_CRCSA_0X0085                       (133 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI4.RDR */
#  define R_CRC_CRCSAR_CRCSA_0X00A3                       (163 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI5.TDR */
#  define R_CRC_CRCSAR_CRCSA_0X00A5                       (165 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI5.RDR */
#  define R_CRC_CRCSAR_CRCSA_0X00C3                       (195 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI6.TDR */
#  define R_CRC_CRCSAR_CRCSA_0X00C5                       (197 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI6.RDR */
#  define R_CRC_CRCSAR_CRCSA_0X00E3                       (227 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI7.TDR */
#  define R_CRC_CRCSAR_CRCSA_0X00E5                       (229 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI7.RDR */
#  define R_CRC_CRCSAR_CRCSA_0X0103                       (259 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI8.TDR */
#  define R_CRC_CRCSAR_CRCSA_0X0105                       (261 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI8.RDR */
#  define R_CRC_CRCSAR_CRCSA_0X0123                       (291 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI9.TDR */
#  define R_CRC_CRCSAR_CRCSA_0X0125                       (293 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI9.RDR */
#  define R_CRC_CRCSAR_CRCSA_0X000F                       (15 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI0.FTDRL */
#  define R_CRC_CRCSAR_CRCSA_0X0011                       (17 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI0.FRDRL */
#  define R_CRC_CRCSAR_CRCSA_0X002F                       (47 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI1.FTDRL */
#  define R_CRC_CRCSAR_CRCSA_0X0031                       (49 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI1.FRDRL */
#  define R_CRC_CRCSAR_CRCSA_0X004F                       (79 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI2.FTDRL */
#  define R_CRC_CRCSAR_CRCSA_0X0051                       (81 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI2.FRDRL */
#  define R_CRC_CRCSAR_CRCSA_0X006F                       (111 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI3.FTDRL */
#  define R_CRC_CRCSAR_CRCSA_0X0071                       (113 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI3.FRDRL */
#  define R_CRC_CRCSAR_CRCSA_0X008F                       (143 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI4.FTDRL */
#  define R_CRC_CRCSAR_CRCSA_0X0091                       (145 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI4.FRDRL */
#  define R_CRC_CRCSAR_CRCSA_0X00AF                       (175 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI5.FTDRL */
#  define R_CRC_CRCSAR_CRCSA_0X00B1                       (177 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI5.FRDRL */
#  define R_CRC_CRCSAR_CRCSA_0X00CF                       (207 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI6.FTDRL */
#  define R_CRC_CRCSAR_CRCSA_0X00D1                       (209 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI6.FRDRL */
#  define R_CRC_CRCSAR_CRCSA_0X00EF                       (239 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI7.FTDRL */
#  define R_CRC_CRCSAR_CRCSA_0X00F1                       (241 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI7.FRDRL */
#  define R_CRC_CRCSAR_CRCSA_0X010F                       (271 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI8.FTDRL */
#  define R_CRC_CRCSAR_CRCSA_0X0111                       (273 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI8.FRDRL */
#  define R_CRC_CRCSAR_CRCSA_0X012F                       (303 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI9.FTDRL */
#  define R_CRC_CRCSAR_CRCSA_0X0131                       (305 << R_CRC_CRCSAR_CRCSA_SHIFT)  /* SCI9.FRDRL */


/* Maximum number of channels */

#define CRC_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CRC_H */
