/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_cac.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CAC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CAC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* CAC Base Address */
#ifndef R_CAC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_CAC_BASE           0x40202400
#else
#define R_CAC_BASE           0x50202400
#endif
#endif

/* CAC Register Offsets */

#define R_CAC_CACR0_OFFSET                        0x00000000  /* CAC Control Register 0  */
#define R_CAC_CACR1_OFFSET                        0x00000001  /* CAC Control Register 1 */
#define R_CAC_CACR2_OFFSET                        0x00000002  /* CAC Control Register 2  */
#define R_CAC_CAICR_OFFSET                        0x00000003  /* CAC Interrupt Control Register  */
#define R_CAC_CASTR_OFFSET                        0x00000004  /* CAC Status Register  */
#define R_CAC_CAULVR_OFFSET                       0x00000006  /* CAC Upper-Limit Value Setting Register  */
#define R_CAC_CALLVR_OFFSET                       0x00000008  /* CAC Lower-Limit Value Setting Register  */
#define R_CAC_CACNTBR_OFFSET                      0x0000000a  /* CAC Counter Buffer Register */

/* CAC Register Addresses */

#define R_CAC_CACR0                               (R_CAC_BASE + R_CAC_CACR0_OFFSET)
#define R_CAC_CACR1                               (R_CAC_BASE + R_CAC_CACR1_OFFSET)
#define R_CAC_CACR2                               (R_CAC_BASE + R_CAC_CACR2_OFFSET)
#define R_CAC_CAICR                               (R_CAC_BASE + R_CAC_CAICR_OFFSET)
#define R_CAC_CASTR                               (R_CAC_BASE + R_CAC_CASTR_OFFSET)
#define R_CAC_CAULVR                              (R_CAC_BASE + R_CAC_CAULVR_OFFSET)
#define R_CAC_CALLVR                              (R_CAC_BASE + R_CAC_CALLVR_OFFSET)
#define R_CAC_CACNTBR                             (R_CAC_BASE + R_CAC_CACNTBR_OFFSET)

/* Register bit definitions */
/* CACR0 Register bit definitions */
#define R_CAC_CACR0_CFME                          (1 << 0)  /* Clock Frequency Measurement Enable. */

/* CACR1 Register bit definitions */
#define R_CAC_CACR1_EDGES_SHIFT                   (6)  /* Valid Edge Select */
#define R_CAC_CACR1_EDGES_MASK                    0xc0
#  define R_CAC_CACR1_EDGES_00                            (0 << R_CAC_CACR1_EDGES_SHIFT)  /* Rising edge */
#  define R_CAC_CACR1_EDGES_01                            (1 << R_CAC_CACR1_EDGES_SHIFT)  /* Falling edge */
#  define R_CAC_CACR1_EDGES_10                            (2 << R_CAC_CACR1_EDGES_SHIFT)  /* Both rising and falling edges */
#  define R_CAC_CACR1_EDGES_11                            (3 << R_CAC_CACR1_EDGES_SHIFT)  /* Setting prohibited */

#define R_CAC_CACR1_TCSS_SHIFT                    (4)  /* Measurement Target Clock Frequency Division Ratio Select */
#define R_CAC_CACR1_TCSS_MASK                     0x30
#  define R_CAC_CACR1_TCSS_00                             (0 << R_CAC_CACR1_TCSS_SHIFT)  /* No division */
#  define R_CAC_CACR1_TCSS_01                             (1 << R_CAC_CACR1_TCSS_SHIFT)  /* x 1/4 clock */
#  define R_CAC_CACR1_TCSS_10                             (2 << R_CAC_CACR1_TCSS_SHIFT)  /* x 1/8 clock */
#  define R_CAC_CACR1_TCSS_11                             (3 << R_CAC_CACR1_TCSS_SHIFT)  /* x 1/32 clock */

#define R_CAC_CACR1_FMCS_SHIFT                    (1)  /* Measurement Target Clock Select */
#define R_CAC_CACR1_FMCS_MASK                     0xe
#  define R_CAC_CACR1_FMCS_000                            (0 << R_CAC_CACR1_FMCS_SHIFT)  /* Main clock */
#  define R_CAC_CACR1_FMCS_001                            (1 << R_CAC_CACR1_FMCS_SHIFT)  /* Sub-clock */
#  define R_CAC_CACR1_FMCS_010                            (2 << R_CAC_CACR1_FMCS_SHIFT)  /* HOCO clock */
#  define R_CAC_CACR1_FMCS_011                            (3 << R_CAC_CACR1_FMCS_SHIFT)  /* MOCO clock */
#  define R_CAC_CACR1_FMCS_100                            (4 << R_CAC_CACR1_FMCS_SHIFT)  /* LOCO clock */
#  define R_CAC_CACR1_FMCS_101                            (5 << R_CAC_CACR1_FMCS_SHIFT)  /* Peripheral module clock(PCLKB) */
#  define R_CAC_CACR1_FMCS_110                            (6 << R_CAC_CACR1_FMCS_SHIFT)  /* IWDTCLK clock */
#  define R_CAC_CACR1_FMCS_111                            (7 << R_CAC_CACR1_FMCS_SHIFT)  /* Setting prohibited */

#define R_CAC_CACR1_CACREFE                       (1 << 0)  /* CACREF Pin Input Enable */

/* CACR2 Register bit definitions */
#define R_CAC_CACR2_DFS_SHIFT                     (6)  /* Digital Filter Selection */
#define R_CAC_CACR2_DFS_MASK                      0xc0
#  define R_CAC_CACR2_DFS_00                              (0 << R_CAC_CACR2_DFS_SHIFT)  /* Digital filtering is disabled. */
#  define R_CAC_CACR2_DFS_01                              (1 << R_CAC_CACR2_DFS_SHIFT)  /* The sampling clock for the digital filter is the frequency measuring clock. */
#  define R_CAC_CACR2_DFS_10                              (2 << R_CAC_CACR2_DFS_SHIFT)  /* The sampling clock for the digital filter is the frequency measuring clock divided by 4. */
#  define R_CAC_CACR2_DFS_11                              (3 << R_CAC_CACR2_DFS_SHIFT)  /* The sampling clock for the digital filter is the frequency measuring clock divided by 16. */

#define R_CAC_CACR2_RCDS_SHIFT                    (4)  /* Measurement Reference Clock Frequency Division Ratio Select */
#define R_CAC_CACR2_RCDS_MASK                     0x30
#  define R_CAC_CACR2_RCDS_00                             (0 << R_CAC_CACR2_RCDS_SHIFT)  /* 1/32 clock */
#  define R_CAC_CACR2_RCDS_01                             (1 << R_CAC_CACR2_RCDS_SHIFT)  /* 1/128 clock */
#  define R_CAC_CACR2_RCDS_10                             (2 << R_CAC_CACR2_RCDS_SHIFT)  /* 1/1024 clock */
#  define R_CAC_CACR2_RCDS_11                             (3 << R_CAC_CACR2_RCDS_SHIFT)  /* 1/8192 clock */

#define R_CAC_CACR2_RSCS_SHIFT                    (1)  /* Measurement Reference Clock Select */
#define R_CAC_CACR2_RSCS_MASK                     0xe
#  define R_CAC_CACR2_RSCS_000                            (0 << R_CAC_CACR2_RSCS_SHIFT)  /* Main clock */
#  define R_CAC_CACR2_RSCS_001                            (1 << R_CAC_CACR2_RSCS_SHIFT)  /* Sub-clock */
#  define R_CAC_CACR2_RSCS_010                            (2 << R_CAC_CACR2_RSCS_SHIFT)  /* HOCO clock */
#  define R_CAC_CACR2_RSCS_011                            (3 << R_CAC_CACR2_RSCS_SHIFT)  /* MOCO clock */
#  define R_CAC_CACR2_RSCS_100                            (4 << R_CAC_CACR2_RSCS_SHIFT)  /* LOCO clock */
#  define R_CAC_CACR2_RSCS_101                            (5 << R_CAC_CACR2_RSCS_SHIFT)  /* Peripheral module clock(PCLKB) */
#  define R_CAC_CACR2_RSCS_110                            (6 << R_CAC_CACR2_RSCS_SHIFT)  /* IWDTCLK clock */
#  define R_CAC_CACR2_RSCS_111                            (7 << R_CAC_CACR2_RSCS_SHIFT)  /* Setting prohibited */

#define R_CAC_CACR2_RPS                           (1 << 0)  /* Reference Signal Select  */

/* CAICR Register bit definitions */
#define R_CAC_CAICR_OVFFCL                        (1 << 6)  /* OVFF Clear  */

#define R_CAC_CAICR_MENDFCL                       (1 << 5)  /* MENDF Clear  */

#define R_CAC_CAICR_FERRFCL                       (1 << 4)  /* FERRF Clear */

#define R_CAC_CAICR_OVFIE                         (1 << 2)  /* Overflow Interrupt Request  Enable */

#define R_CAC_CAICR_MENDIE                        (1 << 1)  /* Measurement End Interrupt Request Enable */

#define R_CAC_CAICR_FERRIE                        (1 << 0)  /* Frequency Error Interrupt Request Enable */

/* CASTR Register bit definitions */
#define R_CAC_CASTR_OVFF                          (1 << 2)  /* Counter Overflow Flag  */

#define R_CAC_CASTR_MENDF                         (1 << 1)  /* Measurement End Flag */

#define R_CAC_CASTR_FERRF                         (1 << 0)  /* Frequency Error Flag */

/* CAULVR Register bit definitions */
#define R_CAC_CAULVR_CAULVR_SHIFT                 (0)  /* CAULVR is a 16-bit readable/writable register that stores the upper-limit value of the frequency. */
#define R_CAC_CAULVR_CAULVR_MASK                  0xffff

/* CALLVR Register bit definitions */
#define R_CAC_CALLVR_CALLVR_SHIFT                 (0)  /* CALLVR is a 16-bit readable/writable register that stores the lower-limit value of the frequency. */
#define R_CAC_CALLVR_CALLVR_MASK                  0xffff

/* CACNTBR Register bit definitions */
#define R_CAC_CACNTBR_CACNTBR_SHIFT               (0)  /* CACNTBR is a 16-bit read-only register that retains the counter value at the time a valid reference signal edge is input */
#define R_CAC_CACNTBR_CACNTBR_MASK                0xffff


/* Maximum number of channels */

#define CAC_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CAC_H */
