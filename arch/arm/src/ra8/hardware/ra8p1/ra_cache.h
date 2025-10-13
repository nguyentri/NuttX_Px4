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
#define R_CACHE_CCATAD_DATA_OFFSET                0x00000018  /* C-Cache Test Access Data (DATA) */
#define R_CACHE_CCATAD_ECC_OFFSET                 0x00000018  /* C-Cache Test Access Data (ECC) */
#define R_CACHE_CCATAD_LRU_OFFSET                 0x00000018  /* C-Cache Test Access Data (LRU) */
#define R_CACHE_CCATAD_TAG_OFFSET                 0x00000018  /* C-Cache Test Access Data (TAG) */
#define R_CACHE_CCATAD_TAGECC_OFFSET              0x00000018  /* C-Cache Test Access Data (TAGECC) */
#define R_CACHE_SCACTL_OFFSET                     0x00000040  /* S-Cache Control Register */
#define R_CACHE_SCAFCT_OFFSET                     0x00000044  /* S-Cache Flush Control Register */
#define R_CACHE_SCAWTA_OFFSET                     0x0000004c  /* S-Cache Write Attribute */
#define R_CACHE_SCAEDST_OFFSET                    0x00000050  /* S-Cache Error Detection Status */
#define R_CACHE_SCATAA_OFFSET                     0x00000054  /* S-Cache Test Access Address */
#define R_CACHE_SCATAD_DATA_OFFSET                0x00000058  /* S-Cache Test Access Data (DATA) */
#define R_CACHE_SCATAD_ECC_OFFSET                 0x00000058  /* S-Cache Test Access Data (ECC) */
#define R_CACHE_SCATAD_LRU_OFFSET                 0x00000058  /* S-Cache Test Access Data (LRU) */
#define R_CACHE_SCATAD_TAG_OFFSET                 0x00000058  /* S-Cache Test Access Data (TAG) */
#define R_CACHE_CAPOAD_OFFSET                     0x00000200  /* Cache Parity Error Operation After Detection Register */
#define R_CACHE_CAPRCR_OFFSET                     0x00000204  /* Cache Protection Register */

/* CACHE Register Addresses */

#define R_CACHE_CCACTL                            (R_CACHE_BASE + R_CACHE_CCACTL_OFFSET)
#define R_CACHE_CCAFCT                            (R_CACHE_BASE + R_CACHE_CCAFCT_OFFSET)
#define R_CACHE_CCAWTA                            (R_CACHE_BASE + R_CACHE_CCAWTA_OFFSET)
#define R_CACHE_CCAEDST                           (R_CACHE_BASE + R_CACHE_CCAEDST_OFFSET)
#define R_CACHE_CCATAA                            (R_CACHE_BASE + R_CACHE_CCATAA_OFFSET)
#define R_CACHE_CCATAD_DATA                       (R_CACHE_BASE + R_CACHE_CCATAD_DATA_OFFSET)
#define R_CACHE_CCATAD_ECC                        (R_CACHE_BASE + R_CACHE_CCATAD_ECC_OFFSET)
#define R_CACHE_CCATAD_LRU                        (R_CACHE_BASE + R_CACHE_CCATAD_LRU_OFFSET)
#define R_CACHE_CCATAD_TAG                        (R_CACHE_BASE + R_CACHE_CCATAD_TAG_OFFSET)
#define R_CACHE_CCATAD_TAGECC                     (R_CACHE_BASE + R_CACHE_CCATAD_TAGECC_OFFSET)
#define R_CACHE_SCACTL                            (R_CACHE_BASE + R_CACHE_SCACTL_OFFSET)
#define R_CACHE_SCAFCT                            (R_CACHE_BASE + R_CACHE_SCAFCT_OFFSET)
#define R_CACHE_SCAWTA                            (R_CACHE_BASE + R_CACHE_SCAWTA_OFFSET)
#define R_CACHE_SCAEDST                           (R_CACHE_BASE + R_CACHE_SCAEDST_OFFSET)
#define R_CACHE_SCATAA                            (R_CACHE_BASE + R_CACHE_SCATAA_OFFSET)
#define R_CACHE_SCATAD_DATA                       (R_CACHE_BASE + R_CACHE_SCATAD_DATA_OFFSET)
#define R_CACHE_SCATAD_ECC                        (R_CACHE_BASE + R_CACHE_SCATAD_ECC_OFFSET)
#define R_CACHE_SCATAD_LRU                        (R_CACHE_BASE + R_CACHE_SCATAD_LRU_OFFSET)
#define R_CACHE_SCATAD_TAG                        (R_CACHE_BASE + R_CACHE_SCATAD_TAG_OFFSET)
#define R_CACHE_CAPOAD                            (R_CACHE_BASE + R_CACHE_CAPOAD_OFFSET)
#define R_CACHE_CAPRCR                            (R_CACHE_BASE + R_CACHE_CAPRCR_OFFSET)

/* Register bit definitions */
/* CCACTL Register bit definitions */
#define R_CACHE_CCACTL_ENC                        (1 << 0)  /* C-cache enable bit */

#define R_CACHE_CCACTL_FC                         (1 << 8)  /* C-Cache flush bit */

#define R_CACHE_CCACTL_WB                         (1 << 9)  /* C-cache write-back */

/* CCAFCT Register bit definitions */
#define R_CACHE_CCAFCT_FC                         (1 << 0)  /* C-Cache flush bit */

#define R_CACHE_CCAFCT_WB                         (1 << 1)  /* C-Cache write-back */

/* CCAWTA Register bit definitions */
#define R_CACHE_CCAWTA_WT                         (1 << 0)  /* C-Cache write-through */

#define R_CACHE_CCAWTA_WA                         (1 << 1)  /* C-Cache write-allocation */

/* CCAEDST Register bit definitions */
#define R_CACHE_CCAEDST_ESD0                      (1 << 0)  /* C-Cache data error status 0 */

#define R_CACHE_CCAEDST_ESD1                      (1 << 1)  /* C-Cache data error status 1 */

#define R_CACHE_CCAEDST_ESTC                      (1 << 2)  /* C-Cache tag clean line invalidate status */

#define R_CACHE_CCAEDST_ESTD                      (1 << 3)  /* C-Cache tag dirty line invalidate status */

#define R_CACHE_CCAEDST_EST2                      (1 << 4)  /* C-Cache tag 2-bit error status */

/* CCATAA Register bit definitions */
#define R_CACHE_CCATAA_OFFSET_SHIFT               (2)  /* Address offset */
#define R_CACHE_CCATAA_OFFSET_MASK                0x1c

#define R_CACHE_CCATAA_ENTRY_SHIFT                (5)  /* Address entry */
#define R_CACHE_CCATAA_ENTRY_MASK                 0xfe0

#define R_CACHE_CCATAA_TARGET_SHIFT               (16)  /* Access target */
#define R_CACHE_CCATAA_TARGET_MASK                0x70000
#  define R_CACHE_CCATAA_TARGET_000                       (0 << R_CACHE_CCATAA_TARGET_SHIFT)  /* Cache data read or write */
#  define R_CACHE_CCATAA_TARGET_001                       (1 << R_CACHE_CCATAA_TARGET_SHIFT)  /* Data ECC code read or write */
#  define R_CACHE_CCATAA_TARGET_010                       (2 << R_CACHE_CCATAA_TARGET_SHIFT)  /* Tag, V, D read or write */
#  define R_CACHE_CCATAA_TARGET_011                       (3 << R_CACHE_CCATAA_TARGET_SHIFT)  /* LRU read or write */
#  define R_CACHE_CCATAA_TARGET_100                       (4 << R_CACHE_CCATAA_TARGET_SHIFT)  /* Tag ECC code read or write */

#define R_CACHE_CCATAA_RW                         (1 << 23)  /* Read write */

#define R_CACHE_CCATAA_WAY_SHIFT                  (30)  /* Address way */
#define R_CACHE_CCATAA_WAY_MASK                   0xc0000000

/* CCATAD_DATA Register bit definitions */
#define R_CACHE_CCATAD_DATA_DATA_SHIFT            (0)  /* C-Cache test access data */
#define R_CACHE_CCATAD_DATA_DATA_MASK             0xffffffff

/* CCATAD_ECC Register bit definitions */
#define R_CACHE_CCATAD_ECC_ECC_SHIFT              (0)  /* C-Cache test access ECC code */
#define R_CACHE_CCATAD_ECC_ECC_MASK               0x7f

/* CCATAD_LRU Register bit definitions */
#define R_CACHE_CCATAD_LRU_LRU_SHIFT              (0)  /* C-Cache test access LRU data */
#define R_CACHE_CCATAD_LRU_LRU_MASK               0x1f

/* CCATAD_TAG Register bit definitions */
#define R_CACHE_CCATAD_TAG_D                      (1 << 0)  /* C-Cache test access Dirty */

#define R_CACHE_CCATAD_TAG_V                      (1 << 1)  /* C-Cache test access Valid */

#define R_CACHE_CCATAD_TAG_TAG_SHIFT              (12)  /* C-Cache test access Tag data */
#define R_CACHE_CCATAD_TAG_TAG_MASK               0xfffff000

/* CCATAD_TAGECC Register bit definitions */
#define R_CACHE_CCATAD_TAGECC_TAGECC_SHIFT        (0)  /* C-Cache test access Tag ECC code */
#define R_CACHE_CCATAD_TAGECC_TAGECC_MASK         0x7f

/* SCACTL Register bit definitions */
#define R_CACHE_SCACTL_ENS                        (1 << 0)  /* S-Cache enable bit */

#define R_CACHE_SCACTL_FS                         (1 << 8)  /* S-Cache flush bit */

#define R_CACHE_SCACTL_WB                         (1 << 9)  /* S-Cache write-back */

/* SCAFCT Register bit definitions */
#define R_CACHE_SCAFCT_FS                         (1 << 0)  /* S-Cache flush bit */

#define R_CACHE_SCAFCT_WB                         (1 << 1)  /* S-Cache write-back */

/* SCAWTA Register bit definitions */
#define R_CACHE_SCAWTA_WT                         (1 << 0)  /* S-Cache write-through */

#define R_CACHE_SCAWTA_WA                         (1 << 1)  /* S-Cache write-allocation */

/* SCAEDST Register bit definitions */
#define R_CACHE_SCAEDST_ESD0                      (1 << 0)  /* S-Cache data error status 0 */

#define R_CACHE_SCAEDST_ESD1                      (1 << 1)  /* S-Cache data error status 1 */

#define R_CACHE_SCAEDST_ESTC                      (1 << 2)  /* S-Cache Tag clean line invalidate status */

#define R_CACHE_SCAEDST_ESTD                      (1 << 3)  /* S-Cache Tag dirty line invalidate status */

#define R_CACHE_SCAEDST_EST2                      (1 << 4)  /* S-Cache Tag 2-bit error status */

/* SCATAA Register bit definitions */
#define R_CACHE_SCATAA_OFFSET_SHIFT               (2)  /* Address offset */
#define R_CACHE_SCATAA_OFFSET_MASK                0x1c

#define R_CACHE_SCATAA_ENTRY_SHIFT                (5)  /* Address entry */
#define R_CACHE_SCATAA_ENTRY_MASK                 0xfe0

#define R_CACHE_SCATAA_TARGET_SHIFT               (16)  /* Access target */
#define R_CACHE_SCATAA_TARGET_MASK                0x70000
#  define R_CACHE_SCATAA_TARGET_000                       (0 << R_CACHE_SCATAA_TARGET_SHIFT)  /* Cache data read or write */
#  define R_CACHE_SCATAA_TARGET_001                       (1 << R_CACHE_SCATAA_TARGET_SHIFT)  /* Data ECC code read or write */
#  define R_CACHE_SCATAA_TARGET_010                       (2 << R_CACHE_SCATAA_TARGET_SHIFT)  /* Tag, V, D read or write */
#  define R_CACHE_SCATAA_TARGET_011                       (3 << R_CACHE_SCATAA_TARGET_SHIFT)  /* LRU read or write */
#  define R_CACHE_SCATAA_TARGET_100                       (4 << R_CACHE_SCATAA_TARGET_SHIFT)  /* Tag ECC code read or write */

#define R_CACHE_SCATAA_RW                         (1 << 23)  /* Read write */

#define R_CACHE_SCATAA_WAY_SHIFT                  (30)  /* Address way */
#define R_CACHE_SCATAA_WAY_MASK                   0xc0000000

/* SCATAD_DATA Register bit definitions */
#define R_CACHE_SCATAD_DATA_DATA_SHIFT            (0)  /* S-Cache test access data */
#define R_CACHE_SCATAD_DATA_DATA_MASK             0xffffffff

/* SCATAD_ECC Register bit definitions */
#define R_CACHE_SCATAD_ECC_ECC_SHIFT              (0)  /* S-Cache test access ECC code */
#define R_CACHE_SCATAD_ECC_ECC_MASK               0x7f

/* SCATAD_LRU Register bit definitions */
#define R_CACHE_SCATAD_LRU_LRU_SHIFT              (0)  /* S-Cache test access LRU data */
#define R_CACHE_SCATAD_LRU_LRU_MASK               0x1f

/* SCATAD_TAG Register bit definitions */
#define R_CACHE_SCATAD_TAG_D                      (1 << 0)  /* S-Cache test access Dirty */

#define R_CACHE_SCATAD_TAG_V                      (1 << 1)  /* S-Cache test access Valid */

#define R_CACHE_SCATAD_TAG_TAG_SHIFT              (12)  /* S-Cache test access Tag data */
#define R_CACHE_SCATAD_TAG_TAG_MASK               0xfffff000

/* CAPOAD Register bit definitions */
#define R_CACHE_CAPOAD_OAD                        (1 << 0)  /* Operation after detection bit */

#define R_CACHE_CAPOAD_ECCMOD1                    (1 << 3)  /* ECC enable */

#define R_CACHE_CAPOAD_E1STSEN                    (1 << 4)  /* ECC correctable error information update enable */

/* CAPRCR Register bit definitions */
#define R_CACHE_CAPRCR_PRCR                       (1 << 0)  /* Register Write Control bit */

#define R_CACHE_CAPRCR_KW_SHIFT                   (1)  /* Write Key Code bit */
#define R_CACHE_CAPRCR_KW_MASK                    0xfe


/* Maximum number of channels */

#define CACHE_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CACHE_H */
