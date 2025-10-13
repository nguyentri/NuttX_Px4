/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_mipi_phy.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MIPI_PHY_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MIPI_PHY_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* MIPI_PHY Base Address */
#ifndef R_MIPI_PHY_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_MIPI_PHY_BASE           0x40346c00
#else
#define R_MIPI_PHY_BASE           0x50346c00
#endif
#endif

/* MIPI_PHY Register Offsets */

#define R_MIPI_PHY_DPHYREFCR_OFFSET               0x00000000  /* D-PHY Reference Clock Setting Register */
#define R_MIPI_PHY_DPHYPLFCR_OFFSET               0x00000004  /* D-PHY PLL Frequency Control Register */
#define R_MIPI_PHY_DPHYPLOCR_OFFSET               0x00000008  /* D-PHY PLL Operation Control Register */
#define R_MIPI_PHY_DPHYESCCR_OFFSET               0x0000000c  /* D-PHY Escape Mode Clock Control Register */
#define R_MIPI_PHY_DPHYPWRCR_OFFSET               0x00000010  /* D-PHY Power Supplying Control Register */
#define R_MIPI_PHY_DPHYSFR_OFFSET                 0x0000001c  /* D-PHY Status Flag Register */
#define R_MIPI_PHY_DPHYOCR_OFFSET                 0x00000020  /* D-PHY Operation Control Register */
#define R_MIPI_PHY_DPHYTIM1_OFFSET                0x00000024  /* D-PHY Timing Control Register 1 */
#define R_MIPI_PHY_DPHYTIM2_OFFSET                0x00000028  /* D-PHY Timing Control Register 2 */
#define R_MIPI_PHY_DPHYTIM3_OFFSET                0x0000002c  /* D-PHY Timing Control Register 3 */
#define R_MIPI_PHY_DPHYTIM4_OFFSET                0x00000030  /* D-PHY Timing Control Register 4 */
#define R_MIPI_PHY_DPHYTIM5_OFFSET                0x00000034  /* D-PHY Timing Control Register 5 */
#define R_MIPI_PHY_DPHYTIM6_OFFSET                0x00000038  /* D-PHY Timing Control Register 6 */
#define R_MIPI_PHY_DPHYMDC_OFFSET                 0x00000048  /* D-PHY Mode Control Register */

/* MIPI_PHY Register Addresses */

#define R_MIPI_PHY_DPHYREFCR                      (R_MIPI_PHY_BASE + R_MIPI_PHY_DPHYREFCR_OFFSET)
#define R_MIPI_PHY_DPHYPLFCR                      (R_MIPI_PHY_BASE + R_MIPI_PHY_DPHYPLFCR_OFFSET)
#define R_MIPI_PHY_DPHYPLOCR                      (R_MIPI_PHY_BASE + R_MIPI_PHY_DPHYPLOCR_OFFSET)
#define R_MIPI_PHY_DPHYESCCR                      (R_MIPI_PHY_BASE + R_MIPI_PHY_DPHYESCCR_OFFSET)
#define R_MIPI_PHY_DPHYPWRCR                      (R_MIPI_PHY_BASE + R_MIPI_PHY_DPHYPWRCR_OFFSET)
#define R_MIPI_PHY_DPHYSFR                        (R_MIPI_PHY_BASE + R_MIPI_PHY_DPHYSFR_OFFSET)
#define R_MIPI_PHY_DPHYOCR                        (R_MIPI_PHY_BASE + R_MIPI_PHY_DPHYOCR_OFFSET)
#define R_MIPI_PHY_DPHYTIM1                       (R_MIPI_PHY_BASE + R_MIPI_PHY_DPHYTIM1_OFFSET)
#define R_MIPI_PHY_DPHYTIM2                       (R_MIPI_PHY_BASE + R_MIPI_PHY_DPHYTIM2_OFFSET)
#define R_MIPI_PHY_DPHYTIM3                       (R_MIPI_PHY_BASE + R_MIPI_PHY_DPHYTIM3_OFFSET)
#define R_MIPI_PHY_DPHYTIM4                       (R_MIPI_PHY_BASE + R_MIPI_PHY_DPHYTIM4_OFFSET)
#define R_MIPI_PHY_DPHYTIM5                       (R_MIPI_PHY_BASE + R_MIPI_PHY_DPHYTIM5_OFFSET)
#define R_MIPI_PHY_DPHYTIM6                       (R_MIPI_PHY_BASE + R_MIPI_PHY_DPHYTIM6_OFFSET)
#define R_MIPI_PHY_DPHYMDC                        (R_MIPI_PHY_BASE + R_MIPI_PHY_DPHYMDC_OFFSET)

/* Register bit definitions */
/* DPHYREFCR Register bit definitions */
#define R_MIPI_PHY_DPHYREFCR_RFREQ_SHIFT          (0)  /* Reference Clock Frequency Setting */
#define R_MIPI_PHY_DPHYREFCR_RFREQ_MASK           0xff

/* DPHYPLFCR Register bit definitions */
#define R_MIPI_PHY_DPHYPLFCR_IDIV_SHIFT           (0)  /* D-PHY PLL Input Frequency Division Ratio Select */
#define R_MIPI_PHY_DPHYPLFCR_IDIV_MASK            0x3
#  define R_MIPI_PHY_DPHYPLFCR_IDIV_00                    (0 << R_MIPI_PHY_DPHYPLFCR_IDIV_SHIFT)  /* 1 */
#  define R_MIPI_PHY_DPHYPLFCR_IDIV_01                    (1 << R_MIPI_PHY_DPHYPLFCR_IDIV_SHIFT)  /* 1/2 */
#  define R_MIPI_PHY_DPHYPLFCR_IDIV_10                    (2 << R_MIPI_PHY_DPHYPLFCR_IDIV_SHIFT)  /* 1/3 */
#  define R_MIPI_PHY_DPHYPLFCR_IDIV_11                    (3 << R_MIPI_PHY_DPHYPLFCR_IDIV_SHIFT)  /* 1/4 */

#define R_MIPI_PHY_DPHYPLFCR_NFMUL_SHIFT          (8)  /* D-PHY PLL Frequency Multiplication Factor Select (Fractional Part) */
#define R_MIPI_PHY_DPHYPLFCR_NFMUL_MASK           0x300
#  define R_MIPI_PHY_DPHYPLFCR_NFMUL_00                   (0 << R_MIPI_PHY_DPHYPLFCR_NFMUL_SHIFT)  /* 0.00 */
#  define R_MIPI_PHY_DPHYPLFCR_NFMUL_01                   (1 << R_MIPI_PHY_DPHYPLFCR_NFMUL_SHIFT)  /* 0.33 */
#  define R_MIPI_PHY_DPHYPLFCR_NFMUL_10                   (2 << R_MIPI_PHY_DPHYPLFCR_NFMUL_SHIFT)  /* 0.66 */
#  define R_MIPI_PHY_DPHYPLFCR_NFMUL_11                   (3 << R_MIPI_PHY_DPHYPLFCR_NFMUL_SHIFT)  /* 0.50 */

#define R_MIPI_PHY_DPHYPLFCR_PMUL_SHIFT           (12)  /*  */
#define R_MIPI_PHY_DPHYPLFCR_PMUL_MASK            0x3000
#  define R_MIPI_PHY_DPHYPLFCR_PMUL_00                    (0 << R_MIPI_PHY_DPHYPLFCR_PMUL_SHIFT)  /* 1 */
#  define R_MIPI_PHY_DPHYPLFCR_PMUL_01                    (1 << R_MIPI_PHY_DPHYPLFCR_PMUL_SHIFT)  /* 1/2 */
#  define R_MIPI_PHY_DPHYPLFCR_PMUL_10                    (2 << R_MIPI_PHY_DPHYPLFCR_PMUL_SHIFT)  /* 1/4 */
#  define R_MIPI_PHY_DPHYPLFCR_PMUL_11                    (3 << R_MIPI_PHY_DPHYPLFCR_PMUL_SHIFT)  /* 1/8 */

#define R_MIPI_PHY_DPHYPLFCR_NMUL_SHIFT           (16)  /* D-PHY PLL Frequency Multiplication Factor Select (Integer Part) */
#define R_MIPI_PHY_DPHYPLFCR_NMUL_MASK            0x1ff0000

/* DPHYPLOCR Register bit definitions */
#define R_MIPI_PHY_DPHYPLOCR_PLLSTP               (1 << 0)  /* D-PHY PLL Operation Control */

/* DPHYESCCR Register bit definitions */
#define R_MIPI_PHY_DPHYESCCR_ESCDIV_SHIFT         (0)  /* Escape Mode Transfer Clock Division Ratio */
#define R_MIPI_PHY_DPHYESCCR_ESCDIV_MASK          0x1f

/* DPHYPWRCR Register bit definitions */
#define R_MIPI_PHY_DPHYPWRCR_PWRSEN               (1 << 0)  /* D-PHY Power Supplying Control */

/* DPHYSFR Register bit definitions */
#define R_MIPI_PHY_DPHYSFR_PWRSF                  (1 << 0)  /* D-PHY LDO Power-on Status Flag */

#define R_MIPI_PHY_DPHYSFR_PLLSF                  (1 << 8)  /* D-PHY PLL Oscillation Stabilization Flag */

/* DPHYOCR Register bit definitions */
#define R_MIPI_PHY_DPHYOCR_DPHYEN                 (1 << 0)  /* D-PHY Operation Control */

/* DPHYTIM1 Register bit definitions */
#define R_MIPI_PHY_DPHYTIM1_TINIT_SHIFT           (0)  /* D-PHY T_INIT Parameter Setting */
#define R_MIPI_PHY_DPHYTIM1_TINIT_MASK            0x7ffff

/* DPHYTIM2 Register bit definitions */
#define R_MIPI_PHY_DPHYTIM2_TCLKPREP_SHIFT        (0)  /* D-PHY T_CLK_PREPARE Parameter Setting */
#define R_MIPI_PHY_DPHYTIM2_TCLKPREP_MASK         0xff

#define R_MIPI_PHY_DPHYTIM2_TCLKSETT_SHIFT        (8)  /* D-PHY T_CLK_SETTLE Parameter Setting */
#define R_MIPI_PHY_DPHYTIM2_TCLKSETT_MASK         0xff00

#define R_MIPI_PHY_DPHYTIM2_TCLKMISS_SHIFT        (16)  /* D-PHY T_CLK_MISS Parameter Setting */
#define R_MIPI_PHY_DPHYTIM2_TCLKMISS_MASK         0xff0000

/* DPHYTIM3 Register bit definitions */
#define R_MIPI_PHY_DPHYTIM3_THSPREP_SHIFT         (0)  /* D-PHY T_THS_PREPARE Parameter Setting */
#define R_MIPI_PHY_DPHYTIM3_THSPREP_MASK          0xff

#define R_MIPI_PHY_DPHYTIM3_THSSETT_SHIFT         (8)  /* D-PHY T_THS_SETTLE Parameter Setting */
#define R_MIPI_PHY_DPHYTIM3_THSSETT_MASK          0xff00

/* DPHYTIM4 Register bit definitions */
#define R_MIPI_PHY_DPHYTIM4_TCLKZERO_SHIFT        (0)  /* D-PHY T_CLK_ZERO Parameter Setting */
#define R_MIPI_PHY_DPHYTIM4_TCLKZERO_MASK         0xff

#define R_MIPI_PHY_DPHYTIM4_TCLKPRE_SHIFT         (8)  /* D-PHY T_TCLK_PRE Parameter Setting */
#define R_MIPI_PHY_DPHYTIM4_TCLKPRE_MASK          0xff00

#define R_MIPI_PHY_DPHYTIM4_TCLKPOST_SHIFT        (16)  /* D-PHY T_TCLK_POST Parameter Setting */
#define R_MIPI_PHY_DPHYTIM4_TCLKPOST_MASK         0xff0000

#define R_MIPI_PHY_DPHYTIM4_TCLKTRL_SHIFT         (24)  /* D-PHY T_TCLK_TRAIL Parameter Setting */
#define R_MIPI_PHY_DPHYTIM4_TCLKTRL_MASK          0xff000000

/* DPHYTIM5 Register bit definitions */
#define R_MIPI_PHY_DPHYTIM5_THSZERO_SHIFT         (0)  /* D-PHY T_THS_ZERO Parameter Setting */
#define R_MIPI_PHY_DPHYTIM5_THSZERO_MASK          0xff

#define R_MIPI_PHY_DPHYTIM5_THSTRL_SHIFT          (8)  /* D-PHY T_THS_TRAIL Parameter Setting */
#define R_MIPI_PHY_DPHYTIM5_THSTRL_MASK           0xff00

#define R_MIPI_PHY_DPHYTIM5_THSEXIT_SHIFT         (16)  /* D-PHY T_THS_EXIT Parameter Setting */
#define R_MIPI_PHY_DPHYTIM5_THSEXIT_MASK          0xff0000

/* DPHYTIM6 Register bit definitions */
#define R_MIPI_PHY_DPHYTIM6_TLPX_SHIFT            (0)  /* D-PHY T_TLPX Parameter Setting */
#define R_MIPI_PHY_DPHYTIM6_TLPX_MASK             0xff

/* DPHYMDC Register bit definitions */
#define R_MIPI_PHY_DPHYMDC_MASTEREN               (1 << 0)  /* D-PHY Master/Slave Select */


/* Maximum number of channels */

#define MIPI_PHY_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MIPI_PHY_H */
