/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_acmphs.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ACMPHS_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ACMPHS_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ACMPHS Base Address */
#ifndef R_ACMPHS_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_ACMPHS_BASE           0x40236000
#else
#define R_ACMPHS_BASE           0x50236000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_ACMPHS_CH_STRIDE    0x00000100
#define R_ACMPHS_CH_BASE(ch)   (R_ACMPHS_BASE + ((uint32_t)(ch) * R_ACMPHS_CH_STRIDE))

/* ACMPHS Register Offsets */

#define R_ACMPHS_CMPCTL_OFFSET     0x00000000  /* Comparator Control Register */
#define R_ACMPHS_CMPSEL0_OFFSET     0x00000004  /* Comparator Input Select Register */
#define R_ACMPHS_CMPSEL1_OFFSET     0x00000008  /* Comparator Reference Voltage Select Register */
#define R_ACMPHS_CMPMON_OFFSET     0x0000000c  /* Comparator Output Monitor Register */
#define R_ACMPHS_CPIOC_OFFSET     0x00000010  /* Comparator Output Control Register */
#define R_ACMPHS_CPINTCTL_OFFSET     0x00000040  /* Comparator Interrupt Control Register */
#define R_ACMPHS_CPMSKCTL_OFFSET     0x00000044  /* Comparator Interrupt Mask Control Register */

/* ACMPHS Register Addresses */

#define R_ACMPHS_CMPCTL                 (R_ACMPHS_BASE + R_ACMPHS_CMPCTL_OFFSET)
#define R_ACMPHS_CMPSEL0                 (R_ACMPHS_BASE + R_ACMPHS_CMPSEL0_OFFSET)
#define R_ACMPHS_CMPSEL1                 (R_ACMPHS_BASE + R_ACMPHS_CMPSEL1_OFFSET)
#define R_ACMPHS_CMPMON                 (R_ACMPHS_BASE + R_ACMPHS_CMPMON_OFFSET)
#define R_ACMPHS_CPIOC                 (R_ACMPHS_BASE + R_ACMPHS_CPIOC_OFFSET)
#define R_ACMPHS_CPINTCTL                 (R_ACMPHS_BASE + R_ACMPHS_CPINTCTL_OFFSET)
#define R_ACMPHS_CPMSKCTL                 (R_ACMPHS_BASE + R_ACMPHS_CPMSKCTL_OFFSET)

/* Register bit definitions */
/* CMPCTL Register bit definitions */
#define R_ACMPHS_CMPCTL_CINV                      (1 << 0)  /* Comparator Output Polarity Selection */

#define R_ACMPHS_CMPCTL_COE                       (1 << 1)  /* Comparator Output Enable */

#define R_ACMPHS_CMPCTL_CSTEN                     (1 << 2)  /* Interrupt Select */

#define R_ACMPHS_CMPCTL_CEG_SHIFT                 (3)  /* Selection of Valid Edge (Edge Selector) */
#define R_ACMPHS_CMPCTL_CEG_MASK                  0x18
#  define R_ACMPHS_CMPCTL_CEG_00                          (0 << R_ACMPHS_CMPCTL_CEG_SHIFT)  /* Do not detect edge */
#  define R_ACMPHS_CMPCTL_CEG_01                          (1 << R_ACMPHS_CMPCTL_CEG_SHIFT)  /* Detect rising edge */
#  define R_ACMPHS_CMPCTL_CEG_10                          (2 << R_ACMPHS_CMPCTL_CEG_SHIFT)  /* Detect falling edge */
#  define R_ACMPHS_CMPCTL_CEG_11                          (3 << R_ACMPHS_CMPCTL_CEG_SHIFT)  /* Detect both edges */

#define R_ACMPHS_CMPCTL_CDFS_SHIFT                (5)  /* Noise Filter Selection */
#define R_ACMPHS_CMPCTL_CDFS_MASK                 0x60
#  define R_ACMPHS_CMPCTL_CDFS_00                         (0 << R_ACMPHS_CMPCTL_CDFS_SHIFT)  /* Do not use noise filter */
#  define R_ACMPHS_CMPCTL_CDFS_01                         (1 << R_ACMPHS_CMPCTL_CDFS_SHIFT)  /* Use noise filter sampling frequency of PCLKB/23 */
#  define R_ACMPHS_CMPCTL_CDFS_10                         (2 << R_ACMPHS_CMPCTL_CDFS_SHIFT)  /* Use noise filter sampling frequency of PCLKB/24 */
#  define R_ACMPHS_CMPCTL_CDFS_11                         (3 << R_ACMPHS_CMPCTL_CDFS_SHIFT)  /* Use noise filter sampling frequency of PCLKB/25 */

#define R_ACMPHS_CMPCTL_HCMPON                    (1 << 7)  /* Comparator Operation Control */

/* CMPSEL0 Register bit definitions */
#define R_ACMPHS_CMPSEL0_CMPSEL_SHIFT             (0)  /* Comparator Input Selection */
#define R_ACMPHS_CMPSEL0_CMPSEL_MASK              0xf
#  define R_ACMPHS_CMPSEL0_CMPSEL_0X00                    (0 << R_ACMPHS_CMPSEL0_CMPSEL_SHIFT)  /* Do not input */
#  define R_ACMPHS_CMPSEL0_CMPSEL_0X01                    (0 << R_ACMPHS_CMPSEL0_CMPSEL_SHIFT)  /* Select IVCMP0 */
#  define R_ACMPHS_CMPSEL0_CMPSEL_0X02                    (0 << R_ACMPHS_CMPSEL0_CMPSEL_SHIFT)  /* Select IVCMP1 */
#  define R_ACMPHS_CMPSEL0_CMPSEL_0X04                    (0 << R_ACMPHS_CMPSEL0_CMPSEL_SHIFT)  /* Select IVCMP2 */
#  define R_ACMPHS_CMPSEL0_CMPSEL_0X08                    (0 << R_ACMPHS_CMPSEL0_CMPSEL_SHIFT)  /* Select IVCMP3 */

/* CMPSEL1 Register bit definitions */
#define R_ACMPHS_CMPSEL1_CRVS_SHIFT               (0)  /* Reference Voltage Selection */
#define R_ACMPHS_CMPSEL1_CRVS_MASK                0x3f
#  define R_ACMPHS_CMPSEL1_CRVS_0X00                      (0 << R_ACMPHS_CMPSEL1_CRVS_SHIFT)  /* Do not input */
#  define R_ACMPHS_CMPSEL1_CRVS_0X01                      (0 << R_ACMPHS_CMPSEL1_CRVS_SHIFT)  /* Select IVREF0 */
#  define R_ACMPHS_CMPSEL1_CRVS_0X02                      (0 << R_ACMPHS_CMPSEL1_CRVS_SHIFT)  /* Select IVREF1 */
#  define R_ACMPHS_CMPSEL1_CRVS_0X04                      (0 << R_ACMPHS_CMPSEL1_CRVS_SHIFT)  /* Select IVREF2 */
#  define R_ACMPHS_CMPSEL1_CRVS_0X08                      (0 << R_ACMPHS_CMPSEL1_CRVS_SHIFT)  /* Select IVREF3 */

/* CMPMON Register bit definitions */
#define R_ACMPHS_CMPMON_COMPMON                   (1 << 0)  /* Comparator Output Monitor */

#define R_ACMPHS_CMPMON_CMPMON                    (1 << 0)  /* Comparator output monitor */

/* CPIOC Register bit definitions */
#define R_ACMPHS_CPIOC_CPOE                       (1 << 0)  /* External Pin Output Enable */

#define R_ACMPHS_CPIOC_VREFEN                     (1 << 7)  /*  */

/* CPINTCTL Register bit definitions */
#define R_ACMPHS_CPINTCTL_MSKE                    (1 << 0)  /* Comparator Interrupt Periodic Mask Enable */

/* CPMSKCTL Register bit definitions */
#define R_ACMPHS_CPMSKCTL_MSKSEL_SHIFT            (0)  /* Comparator Interrupt Periodic Mask Selection */
#define R_ACMPHS_CPMSKCTL_MSKSEL_MASK             0x7
#  define R_ACMPHS_CPMSKCTL_MSKSEL_000                    (0 << R_ACMPHS_CPMSKCTL_MSKSEL_SHIFT)  /* Enable interrupt masking by GTIOC0A output signal */
#  define R_ACMPHS_CPMSKCTL_MSKSEL_001                    (1 << R_ACMPHS_CPMSKCTL_MSKSEL_SHIFT)  /* Enable interrupt masking by GTIOC1A output signal */
#  define R_ACMPHS_CPMSKCTL_MSKSEL_010                    (2 << R_ACMPHS_CPMSKCTL_MSKSEL_SHIFT)  /* Enable interrupt masking by GTIOC2A output signal */
#  define R_ACMPHS_CPMSKCTL_MSKSEL_011                    (3 << R_ACMPHS_CPMSKCTL_MSKSEL_SHIFT)  /* Enable interrupt masking by GTIOC3A output signal */
#  define R_ACMPHS_CPMSKCTL_MSKSEL_100                    (4 << R_ACMPHS_CPMSKCTL_MSKSEL_SHIFT)  /* Enable interrupt masking by GTIOC4A output signal */
#  define R_ACMPHS_CPMSKCTL_MSKSEL_101                    (5 << R_ACMPHS_CPMSKCTL_MSKSEL_SHIFT)  /* Enable interrupt masking by GTIOC5A output signal */
#  define R_ACMPHS_CPMSKCTL_MSKSEL_110                    (6 << R_ACMPHS_CPMSKCTL_MSKSEL_SHIFT)  /* Enable interrupt masking by GTIOC6A output signal */
#  define R_ACMPHS_CPMSKCTL_MSKSEL_111                    (7 << R_ACMPHS_CPMSKCTL_MSKSEL_SHIFT)  /* Enable interrupt masking by GTIOC7A output signal */


/* Maximum number of channels */

#define ACMPHS_MAX_CHANNELS    4

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ACMPHS_H */
