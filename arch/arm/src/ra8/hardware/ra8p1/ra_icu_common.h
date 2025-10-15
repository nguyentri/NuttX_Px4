/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_icu_common.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ICU_COMMON_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ICU_COMMON_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ICU_COMMON Base Address */
#ifndef R_ICU_COMMON_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_ICU_COMMON_BASE           0x40006000
#else
#define R_ICU_COMMON_BASE           0x50006000
#endif
#endif

/* ICU_COMMON Register Offsets */

/* IRQCR%s Registers (0-31) */
#define R_ICU_COMMON_IRQCR_OFFSET(m)              (0x00000000 + ((m) * 0x00000001))  /* IRQ Control Register %s */
#define R_ICU_COMMON_NMICR_OFFSET                 0x00000010  /* NMI Pin Interrupt Control Register */
/* INTSELR%s Registers (0-31) */
#define R_ICU_COMMON_INTSELR_OFFSET(m)            (0x00000040 + ((m) * 0x00000004))  /* Interrupt Request Select Register */

/* ICU_COMMON Register Addresses */

#define R_ICU_COMMON_IRQCR(m)                     (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR_OFFSET(m))
#define R_ICU_COMMON_NMICR                        (R_ICU_COMMON_BASE + R_ICU_COMMON_NMICR_OFFSET)
#define R_ICU_COMMON_INTSELR(m)                   (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR_OFFSET(m))

/* Register bit definitions */
/* IRQCR Register bit definitions */
#define R_ICU_COMMON_IRQCR_IRQMD_SHIFT            (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR_IRQMD_MASK             0x3
#  define R_ICU_COMMON_IRQCR_IRQMD_00                     (0 << R_ICU_COMMON_IRQCR_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR_IRQMD_01                     (1 << R_ICU_COMMON_IRQCR_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR_IRQMD_10                     (2 << R_ICU_COMMON_IRQCR_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR_IRQMD_11                     (3 << R_ICU_COMMON_IRQCR_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR_FCLKSEL_SHIFT          (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR_FCLKSEL_MASK           0x30
#  define R_ICU_COMMON_IRQCR_FCLKSEL_00                   (0 << R_ICU_COMMON_IRQCR_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR_FCLKSEL_01                   (1 << R_ICU_COMMON_IRQCR_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR_FCLKSEL_10                   (2 << R_ICU_COMMON_IRQCR_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR_FCLKSEL_11                   (3 << R_ICU_COMMON_IRQCR_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR_FLTEN                  (1 << 7)  /* IRQi Digital Filter Enable */

/* NMICR Register bit definitions */
#define R_ICU_COMMON_NMICR_NMIMD                  (1 << 0)  /* NMI Detection Set */

#define R_ICU_COMMON_NMICR_NFCLKSEL_SHIFT         (4)  /* NMI Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_NMICR_NFCLKSEL_MASK          0x30
#  define R_ICU_COMMON_NMICR_NFCLKSEL_00                  (0 << R_ICU_COMMON_NMICR_NFCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_NMICR_NFCLKSEL_01                  (1 << R_ICU_COMMON_NMICR_NFCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_NMICR_NFCLKSEL_10                  (2 << R_ICU_COMMON_NMICR_NFCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_NMICR_NFCLKSEL_11                  (3 << R_ICU_COMMON_NMICR_NFCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_NMICR_NFLTEN                 (1 << 7)  /* NMI Digital Filter Enable */

/* INTSELR Register bit definitions */
#define R_ICU_COMMON_INTSELR_IS32P000             (1 << 0)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P001             (1 << 1)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P002             (1 << 2)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P003             (1 << 3)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P004             (1 << 4)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P005             (1 << 5)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P006             (1 << 6)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P007             (1 << 7)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P008             (1 << 8)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P009             (1 << 9)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P010             (1 << 10)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P011             (1 << 11)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P012             (1 << 12)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P013             (1 << 13)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P014             (1 << 14)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P015             (1 << 15)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P016             (1 << 16)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P017             (1 << 17)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P018             (1 << 18)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P019             (1 << 19)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P020             (1 << 20)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P021             (1 << 21)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P022             (1 << 22)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P023             (1 << 23)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P024             (1 << 24)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P025             (1 << 25)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P026             (1 << 26)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P027             (1 << 27)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P028             (1 << 28)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P029             (1 << 29)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P030             (1 << 30)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */

#define R_ICU_COMMON_INTSELR_IS32P031             (1 << 31)  /* This bit sets whether the interrupt requests and DTC requests are on the CPU0 side or the CPU1 side. */


/* Maximum number of channels */

#define ICU_COMMON_MAX_CHANNELS    32

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ICU_COMMON_H */
