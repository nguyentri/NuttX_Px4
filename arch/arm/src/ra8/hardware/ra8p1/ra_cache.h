/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_cache.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CACHE_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CACHE_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* CACHE Base Address */
#ifndef R_CACHE_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_CACHE_BASE           0x4001c000
#else
#define R_CACHE_BASE           0x5001c000
#endif
#endif

/* CACHE Register Offsets */

#define R_CACHE_CCACTL_OFFSET                     0x00000000  /* C-Cache Control Register */
#define R_CACHE_CCAFCT_OFFSET                     0x00000004  /* C-Cache Flush Control Register */
#define R_CACHE_CCAWTA_OFFSET                     0x0000000c  /* C-Cache Write Attribute */
#define R_CACHE_CCAEDST_OFFSET                    0x00000010  /* C-Cache Error Detection Status */
#define R_CACHE_CCATAA_OFFSET                     0x00000014  /* C-Cache Test Access Address */
#define R_CACHE_CCATAD_OFFSET                     0x00000018  /* C-Cache Test Access Data */
#define R_CACHE_SCACTL_OFFSET                     0x00000040  /* S-Cache Control Register */
#define R_CACHE_SCAFCT_OFFSET                     0x00000044  /* S-Cache Flush Control Register */
#define R_CACHE_SCAWTA_OFFSET                     0x0000004c  /* S-Cache Write Attribute */
#define R_CACHE_SCAEDST_OFFSET                    0x00000050  /* S-Cache Error Detection Status */
#define R_CACHE_SCATAA_OFFSET                     0x00000054  /* S-Cache Test Access Address */
#define R_CACHE_SCATAD_OFFSET                     0x00000058  /* C-Cache Test Access Data */
#define R_CACHE_CAPOAD_OFFSET                     0x00000200  /* Cache Parity Error Operation After Detection Register */
#define R_CACHE_CAPRCR_OFFSET                     0x00000204  /* Cache Protection Register */

/* CACHE Register Addresses */

#define R_CACHE_CCACTL                            (R_CACHE_BASE + R_CACHE_CCACTL_OFFSET)
#define R_CACHE_CCAFCT                            (R_CACHE_BASE + R_CACHE_CCAFCT_OFFSET)
#define R_CACHE_CCAWTA                            (R_CACHE_BASE + R_CACHE_CCAWTA_OFFSET)
#define R_CACHE_CCAEDST                           (R_CACHE_BASE + R_CACHE_CCAEDST_OFFSET)
#define R_CACHE_CCATAA                            (R_CACHE_BASE + R_CACHE_CCATAA_OFFSET)
#define R_CACHE_CCATAD                            (R_CACHE_BASE + R_CACHE_CCATAD_OFFSET)
#define R_CACHE_SCACTL                            (R_CACHE_BASE + R_CACHE_SCACTL_OFFSET)
#define R_CACHE_SCAFCT                            (R_CACHE_BASE + R_CACHE_SCAFCT_OFFSET)
#define R_CACHE_SCAWTA                            (R_CACHE_BASE + R_CACHE_SCAWTA_OFFSET)
#define R_CACHE_SCAEDST                           (R_CACHE_BASE + R_CACHE_SCAEDST_OFFSET)
#define R_CACHE_SCATAA                            (R_CACHE_BASE + R_CACHE_SCATAA_OFFSET)
#define R_CACHE_SCATAD                            (R_CACHE_BASE + R_CACHE_SCATAD_OFFSET)
#define R_CACHE_CAPOAD                            (R_CACHE_BASE + R_CACHE_CAPOAD_OFFSET)
#define R_CACHE_CAPRCR                            (R_CACHE_BASE + R_CACHE_CAPRCR_OFFSET)

/* Register bit definitions */
/* CCACTL Register bit definitions */
#define R_CACHE_CCACTL_ENC                        (1 << 0)  /* C-Cache Enable */

#define R_CACHE_CCACTL_FC                         (1 << 8)  /* C-Cache flush bit */

#define R_CACHE_CCACTL_WB                         (1 << 9)  /* C-cache write back */

/* CCAFCT Register bit definitions */
#define R_CACHE_CCAFCT_FC                         (1 << 0)  /* C-Cache Flush */

#define R_CACHE_CCAFCT_WB                         (1 << 1)  /* C-Cache write back */

/* CCAWTA Register bit definitions */
#define R_CACHE_CCAWTA_WT                         (1 << 0)  /* C-Cache write through */

#define R_CACHE_CCAWTA_WA                         (1 << 1)  /* C-Cache write allocation */

/* CCAEDST Register bit definitions */
#define R_CACHE_CCAEDST_ESD0                      (1 << 0)  /* C-Cache data error status 0 */

#define R_CACHE_CCAEDST_ESD1                      (1 << 1)  /* C-Cache data error status 1 */

#define R_CACHE_CCAEDST_ESTC                      (1 << 2)  /* C-Cache Tag clean line invalidate status */

#define R_CACHE_CCAEDST_ESTD                      (1 << 3)  /* C-Cache Tag dirty line invalidate status */

#define R_CACHE_CCAEDST_EST2                      (1 << 4)  /* C-Cache Tag 2bit error status */

/* CCATAA Register bit definitions */
#define R_CACHE_CCATAA_OFFSET_SHIFT               (2)  /* address offset */
#define R_CACHE_CCATAA_OFFSET_MASK                0x1c

#define R_CACHE_CCATAA_ENTRY_SHIFT                (5)  /* address entry */
#define R_CACHE_CCATAA_ENTRY_MASK                 0xfe0

#define R_CACHE_CCATAA_TARGET_SHIFT               (16)  /* access target */
#define R_CACHE_CCATAA_TARGET_MASK                0x70000
#  define R_CACHE_CCATAA_TARGET_00                        (0 << R_CACHE_CCATAA_TARGET_SHIFT)  /* Cache data read or write. */
#  define R_CACHE_CCATAA_TARGET_01                        (1 << R_CACHE_CCATAA_TARGET_SHIFT)  /* ECC code read or write. */
#  define R_CACHE_CCATAA_TARGET_10                        (2 << R_CACHE_CCATAA_TARGET_SHIFT)  /* TAG,V,D read or write. */
#  define R_CACHE_CCATAA_TARGET_11                        (3 << R_CACHE_CCATAA_TARGET_SHIFT)  /* LRU read or write. */

#define R_CACHE_CCATAA_RW                         (1 << 23)  /* read write */

#define R_CACHE_CCATAA_WAY_SHIFT                  (30)  /* address way */
#define R_CACHE_CCATAA_WAY_MASK                   0xc0000000

/* CCATAD Register bit definitions */
#define R_CACHE_CCATAD_DATA_SHIFT                 (0)  /* Cache data */
#define R_CACHE_CCATAD_DATA_MASK                  0xffffffff

/* SCACTL Register bit definitions */
#define R_CACHE_SCACTL_ENS                        (1 << 0)  /* S-Cache Enable */

#define R_CACHE_SCACTL_FS                         (1 << 8)  /* S-Cache flush bit */

#define R_CACHE_SCACTL_WB                         (1 << 9)  /* S-cache write back */

/* SCAFCT Register bit definitions */
#define R_CACHE_SCAFCT_FS                         (1 << 0)  /* S-Cache Flush */

#define R_CACHE_SCAFCT_WB                         (1 << 1)  /* S-Cache write back */

/* SCAWTA Register bit definitions */
#define R_CACHE_SCAWTA_WT                         (1 << 0)  /* S-Cache write through */

#define R_CACHE_SCAWTA_WA                         (1 << 1)  /* S-Cache write allocation */

/* SCAEDST Register bit definitions */
#define R_CACHE_SCAEDST_ESD0                      (1 << 0)  /* S-Cache data error status 0 */

#define R_CACHE_SCAEDST_ESD1                      (1 << 1)  /* S-Cache data error status 1 */

#define R_CACHE_SCAEDST_ESTC                      (1 << 2)  /* S-Cache Tag clean line invalidate status */

#define R_CACHE_SCAEDST_ESTD                      (1 << 3)  /* S-Cache Tag dirty line invalidate status */

#define R_CACHE_SCAEDST_EST2                      (1 << 4)  /* S-Cache Tag 2bit error status */

/* SCATAA Register bit definitions */
#define R_CACHE_SCATAA_OFFSET_SHIFT               (2)  /* address offset */
#define R_CACHE_SCATAA_OFFSET_MASK                0x1c

#define R_CACHE_SCATAA_ENTRY_SHIFT                (5)  /* address entry */
#define R_CACHE_SCATAA_ENTRY_MASK                 0xfe0

#define R_CACHE_SCATAA_TARGET_SHIFT               (16)  /* access target */
#define R_CACHE_SCATAA_TARGET_MASK                0x70000
#  define R_CACHE_SCATAA_TARGET_00                        (0 << R_CACHE_SCATAA_TARGET_SHIFT)  /* Cache data read or write. */
#  define R_CACHE_SCATAA_TARGET_01                        (1 << R_CACHE_SCATAA_TARGET_SHIFT)  /* ECC code read or write. */
#  define R_CACHE_SCATAA_TARGET_10                        (2 << R_CACHE_SCATAA_TARGET_SHIFT)  /* TAG,V,D read or write. */
#  define R_CACHE_SCATAA_TARGET_11                        (3 << R_CACHE_SCATAA_TARGET_SHIFT)  /* LRU read or write. */

#define R_CACHE_SCATAA_RW                         (1 << 23)  /* read write */

#define R_CACHE_SCATAA_WAY_SHIFT                  (30)  /* address way */
#define R_CACHE_SCATAA_WAY_MASK                   0xc0000000

/* SCATAD Register bit definitions */
#define R_CACHE_SCATAD_DATA_SHIFT                 (0)  /* Cache data */
#define R_CACHE_SCATAD_DATA_MASK                  0xffffffff

/* CAPOAD Register bit definitions */
#define R_CACHE_CAPOAD_OAD                        (1 << 0)  /* Operation after Detection */

#define R_CACHE_CAPOAD_ECCMOD1                    (1 << 3)  /* ECC enable */

#define R_CACHE_CAPOAD_E1STSEN                    (1 << 4)  /* ECC 1-Bit Error Information Update Enable */

/* CAPRCR Register bit definitions */
#define R_CACHE_CAPRCR_PRCR                       (1 << 0)  /* Register Write Control */

#define R_CACHE_CAPRCR_KW_SHIFT                   (1)  /* Write key code */
#define R_CACHE_CAPRCR_KW_MASK                    0xfe


/* Maximum number of channels */

#define CACHE_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CACHE_H */
