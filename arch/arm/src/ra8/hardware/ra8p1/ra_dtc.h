/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_dtc.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DTC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DTC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* DTC Base Address */
#ifndef R_DTC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_DTC_BASE           0x4000ac00
#else
#define R_DTC_BASE           0x5000ac00
#endif
#endif

/* DTC Register Offsets */

#define R_DTC_DTCCR_OFFSET                        0x00000000  /* DTC Control Register */
#define R_DTC_DTCVBR_OFFSET                       0x00000004  /* DTC Vector Base Register */
#define R_DTC_DTCADMOD_OFFSET                     0x00000008  /* DTC Address Mode Register */
#define R_DTC_DTCST_OFFSET                        0x0000000c  /* DTC Module Start Register */
#define R_DTC_DTCSTS_OFFSET                       0x0000000e  /* DTC Status Register */
#define R_DTC_DTCCR_SEC_OFFSET                    0x00000010  /* DTC Control Register for secure Region */
#define R_DTC_DTCVBR_SEC_OFFSET                   0x00000014  /* DTC Vector Base Register for secure Region */
#define R_DTC_DTCDISP_OFFSET                      0x00000018  /* DTC Address Displacement Register */
#define R_DTC_DTEVR_OFFSET                        0x00000020  /* DTC Error Vector Register */
#define R_DTC_DTCIBR_OFFSET                       0x00000024  /* DTC Index Table Base Register */
#define R_DTC_DTCOR_OFFSET                        0x00000028  /* DTC Operation Register */
#define R_DTC_DTCSQE_OFFSET                       0x0000002c  /* DTC Sequence Transfer Enable Register */

/* DTC Register Addresses */

#define R_DTC_DTCCR                               (R_DTC_BASE + R_DTC_DTCCR_OFFSET)
#define R_DTC_DTCVBR                              (R_DTC_BASE + R_DTC_DTCVBR_OFFSET)
#define R_DTC_DTCADMOD                            (R_DTC_BASE + R_DTC_DTCADMOD_OFFSET)
#define R_DTC_DTCST                               (R_DTC_BASE + R_DTC_DTCST_OFFSET)
#define R_DTC_DTCSTS                              (R_DTC_BASE + R_DTC_DTCSTS_OFFSET)
#define R_DTC_DTCCR_SEC                           (R_DTC_BASE + R_DTC_DTCCR_SEC_OFFSET)
#define R_DTC_DTCVBR_SEC                          (R_DTC_BASE + R_DTC_DTCVBR_SEC_OFFSET)
#define R_DTC_DTCDISP                             (R_DTC_BASE + R_DTC_DTCDISP_OFFSET)
#define R_DTC_DTEVR                               (R_DTC_BASE + R_DTC_DTEVR_OFFSET)
#define R_DTC_DTCIBR                              (R_DTC_BASE + R_DTC_DTCIBR_OFFSET)
#define R_DTC_DTCOR                               (R_DTC_BASE + R_DTC_DTCOR_OFFSET)
#define R_DTC_DTCSQE                              (R_DTC_BASE + R_DTC_DTCSQE_OFFSET)

/* Register bit definitions */
/* DTCCR Register bit definitions */
#define R_DTC_DTCCR_RRS                           (1 << 4)  /* DTC Transfer Information Read Skip Enable. */

/* DTCVBR Register bit definitions */
#define R_DTC_DTCVBR_DTCVBR_SHIFT                 (0)  /* DTC Vector Base Address. */
#define R_DTC_DTCVBR_DTCVBR_MASK                  0xffffffff

/* DTCADMOD Register bit definitions */
#define R_DTC_DTCADMOD_SHORT                      (1 << 0)  /* Short-Address Mode Set */

/* DTCST Register bit definitions */
#define R_DTC_DTCST_DTCST                         (1 << 0)  /* DTC Module Start */

/* DTCSTS Register bit definitions */
#define R_DTC_DTCSTS_VECN_SHIFT                   (0)  /* DTC-Activating Vector Number MonitoringThese bits indicate the vector number for the activating source when DTC transfer is in progress.The value is only valid if DTC transfer is in progress (the value of the ACT flag is 1) */
#define R_DTC_DTCSTS_VECN_MASK                    0xff

#define R_DTC_DTCSTS_ACT                          (1 << 15)  /* DTC Active Flag */

/* DTCCR_SEC Register bit definitions */
#define R_DTC_DTCCR_SEC_RRS                       (1 << 4)  /* DTC Transfer Information Read Skip Enable. */

/* DTCVBR_SEC Register bit definitions */
#define R_DTC_DTCVBR_SEC_DTCVBR_SHIFT             (0)  /* DTC Vector Base Address. */
#define R_DTC_DTCVBR_SEC_DTCVBR_MASK              0xffffffff

/* DTCDISP Register bit definitions */
#define R_DTC_DTCDISP_DTCDISP_SHIFT               (0)  /* DTC Address Displacement */
#define R_DTC_DTCDISP_DTCDISP_MASK                0xffffffff

/* DTEVR Register bit definitions */
#define R_DTC_DTEVR_DTEV_SHIFT                    (0)  /* DTC Error Vector Number */
#define R_DTC_DTEVR_DTEV_MASK                     0xff

#define R_DTC_DTEVR_DTEVSAM                       (1 << 8)  /* DTC Error Vector Number SA Monitor */

#define R_DTC_DTEVR_DTESTA                        (1 << 16)  /* DTC Error Status Flag */

/* DTCIBR Register bit definitions */
#define R_DTC_DTCIBR_DTCIBR_SHIFT                 (10)  /* DTC Index Table Base Address */
#define R_DTC_DTCIBR_DTCIBR_MASK                  0xfffffc00

/* DTCOR Register bit definitions */
#define R_DTC_DTCOR_SQTFRL                        (1 << 0)  /* Sequence Transfer Stop */

/* DTCSQE Register bit definitions */
#define R_DTC_DTCSQE_VECN_SHIFT                   (0)  /* DTC Sequence Transfer Vector Number Specified */
#define R_DTC_DTCSQE_VECN_MASK                    0xff

#define R_DTC_DTCSQE_ESPSEL                       (1 << 15)  /* DTC Sequence Transfer Enable */


/* Maximum number of channels */

#define DTC_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DTC_H */
