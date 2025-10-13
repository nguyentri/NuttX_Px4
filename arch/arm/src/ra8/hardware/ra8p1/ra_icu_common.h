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

/* Channel stride for multi-channel peripherals */
#define R_ICU_COMMON_CH_STRIDE    0x00000004
#define R_ICU_COMMON_CH_BASE(ch)   (R_ICU_COMMON_BASE + ((uint32_t)(ch) * R_ICU_COMMON_CH_STRIDE))

/* ICU_COMMON Register Offsets */

#define R_ICU_COMMON_IRQCR0_OFFSET     0x00000000  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR1_OFFSET     0x00000001  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR2_OFFSET     0x00000002  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR3_OFFSET     0x00000003  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR4_OFFSET     0x00000004  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR5_OFFSET     0x00000005  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR6_OFFSET     0x00000006  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR7_OFFSET     0x00000007  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR8_OFFSET     0x00000008  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR9_OFFSET     0x00000009  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR10_OFFSET     0x0000000a  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR11_OFFSET     0x0000000b  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR12_OFFSET     0x0000000c  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR13_OFFSET     0x0000000d  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR14_OFFSET     0x0000000e  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR15_OFFSET     0x0000000f  /* IRQ Control Register */
#define R_ICU_COMMON_NMICR_OFFSET     0x00000010  /* NMI Pin Interrupt Control Register */
#define R_ICU_COMMON_IRQCR16_OFFSET     0x00000014  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR17_OFFSET     0x00000015  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR18_OFFSET     0x00000016  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR19_OFFSET     0x00000017  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR20_OFFSET     0x00000018  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR21_OFFSET     0x00000019  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR22_OFFSET     0x0000001a  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR23_OFFSET     0x0000001b  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR24_OFFSET     0x0000001c  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR25_OFFSET     0x0000001d  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR26_OFFSET     0x0000001e  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR27_OFFSET     0x0000001f  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR28_OFFSET     0x00000020  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR29_OFFSET     0x00000021  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR30_OFFSET     0x00000022  /* IRQ Control Register */
#define R_ICU_COMMON_IRQCR31_OFFSET     0x00000023  /* IRQ Control Register */
/* INTSELR%s Registers (0-31) */
#define R_ICU_COMMON_INTSELR00_OFFSET     0x00000040  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR01_OFFSET     0x00000044  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR02_OFFSET     0x00000048  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR03_OFFSET     0x0000004c  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR04_OFFSET     0x00000050  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR05_OFFSET     0x00000054  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR06_OFFSET     0x00000058  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR07_OFFSET     0x0000005c  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR08_OFFSET     0x00000060  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR09_OFFSET     0x00000064  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR10_OFFSET     0x00000068  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR11_OFFSET     0x0000006c  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR12_OFFSET     0x00000070  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR13_OFFSET     0x00000074  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR14_OFFSET     0x00000078  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR15_OFFSET     0x0000007c  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR16_OFFSET     0x00000080  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR17_OFFSET     0x00000084  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR18_OFFSET     0x00000088  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR19_OFFSET     0x0000008c  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR20_OFFSET     0x00000090  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR21_OFFSET     0x00000094  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR22_OFFSET     0x00000098  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR23_OFFSET     0x0000009c  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR24_OFFSET     0x000000a0  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR25_OFFSET     0x000000a4  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR26_OFFSET     0x000000a8  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR27_OFFSET     0x000000ac  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR28_OFFSET     0x000000b0  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR29_OFFSET     0x000000b4  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR30_OFFSET     0x000000b8  /* Interrupt Request Select Register */
#define R_ICU_COMMON_INTSELR31_OFFSET     0x000000bc  /* Interrupt Request Select Register */

/* ICU_COMMON Register Addresses */

#define R_ICU_COMMON_IRQCR0                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR0_OFFSET)
#define R_ICU_COMMON_IRQCR1                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR1_OFFSET)
#define R_ICU_COMMON_IRQCR2                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR2_OFFSET)
#define R_ICU_COMMON_IRQCR3                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR3_OFFSET)
#define R_ICU_COMMON_IRQCR4                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR4_OFFSET)
#define R_ICU_COMMON_IRQCR5                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR5_OFFSET)
#define R_ICU_COMMON_IRQCR6                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR6_OFFSET)
#define R_ICU_COMMON_IRQCR7                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR7_OFFSET)
#define R_ICU_COMMON_IRQCR8                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR8_OFFSET)
#define R_ICU_COMMON_IRQCR9                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR9_OFFSET)
#define R_ICU_COMMON_IRQCR10                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR10_OFFSET)
#define R_ICU_COMMON_IRQCR11                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR11_OFFSET)
#define R_ICU_COMMON_IRQCR12                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR12_OFFSET)
#define R_ICU_COMMON_IRQCR13                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR13_OFFSET)
#define R_ICU_COMMON_IRQCR14                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR14_OFFSET)
#define R_ICU_COMMON_IRQCR15                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR15_OFFSET)
#define R_ICU_COMMON_NMICR                 (R_ICU_COMMON_BASE + R_ICU_COMMON_NMICR_OFFSET)
#define R_ICU_COMMON_IRQCR16                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR16_OFFSET)
#define R_ICU_COMMON_IRQCR17                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR17_OFFSET)
#define R_ICU_COMMON_IRQCR18                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR18_OFFSET)
#define R_ICU_COMMON_IRQCR19                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR19_OFFSET)
#define R_ICU_COMMON_IRQCR20                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR20_OFFSET)
#define R_ICU_COMMON_IRQCR21                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR21_OFFSET)
#define R_ICU_COMMON_IRQCR22                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR22_OFFSET)
#define R_ICU_COMMON_IRQCR23                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR23_OFFSET)
#define R_ICU_COMMON_IRQCR24                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR24_OFFSET)
#define R_ICU_COMMON_IRQCR25                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR25_OFFSET)
#define R_ICU_COMMON_IRQCR26                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR26_OFFSET)
#define R_ICU_COMMON_IRQCR27                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR27_OFFSET)
#define R_ICU_COMMON_IRQCR28                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR28_OFFSET)
#define R_ICU_COMMON_IRQCR29                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR29_OFFSET)
#define R_ICU_COMMON_IRQCR30                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR30_OFFSET)
#define R_ICU_COMMON_IRQCR31                 (R_ICU_COMMON_BASE + R_ICU_COMMON_IRQCR31_OFFSET)
#define R_ICU_COMMON_INTSELR00                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR00_OFFSET)
#define R_ICU_COMMON_INTSELR01                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR01_OFFSET)
#define R_ICU_COMMON_INTSELR02                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR02_OFFSET)
#define R_ICU_COMMON_INTSELR03                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR03_OFFSET)
#define R_ICU_COMMON_INTSELR04                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR04_OFFSET)
#define R_ICU_COMMON_INTSELR05                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR05_OFFSET)
#define R_ICU_COMMON_INTSELR06                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR06_OFFSET)
#define R_ICU_COMMON_INTSELR07                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR07_OFFSET)
#define R_ICU_COMMON_INTSELR08                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR08_OFFSET)
#define R_ICU_COMMON_INTSELR09                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR09_OFFSET)
#define R_ICU_COMMON_INTSELR10                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR10_OFFSET)
#define R_ICU_COMMON_INTSELR11                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR11_OFFSET)
#define R_ICU_COMMON_INTSELR12                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR12_OFFSET)
#define R_ICU_COMMON_INTSELR13                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR13_OFFSET)
#define R_ICU_COMMON_INTSELR14                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR14_OFFSET)
#define R_ICU_COMMON_INTSELR15                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR15_OFFSET)
#define R_ICU_COMMON_INTSELR16                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR16_OFFSET)
#define R_ICU_COMMON_INTSELR17                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR17_OFFSET)
#define R_ICU_COMMON_INTSELR18                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR18_OFFSET)
#define R_ICU_COMMON_INTSELR19                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR19_OFFSET)
#define R_ICU_COMMON_INTSELR20                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR20_OFFSET)
#define R_ICU_COMMON_INTSELR21                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR21_OFFSET)
#define R_ICU_COMMON_INTSELR22                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR22_OFFSET)
#define R_ICU_COMMON_INTSELR23                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR23_OFFSET)
#define R_ICU_COMMON_INTSELR24                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR24_OFFSET)
#define R_ICU_COMMON_INTSELR25                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR25_OFFSET)
#define R_ICU_COMMON_INTSELR26                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR26_OFFSET)
#define R_ICU_COMMON_INTSELR27                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR27_OFFSET)
#define R_ICU_COMMON_INTSELR28                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR28_OFFSET)
#define R_ICU_COMMON_INTSELR29                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR29_OFFSET)
#define R_ICU_COMMON_INTSELR30                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR30_OFFSET)
#define R_ICU_COMMON_INTSELR31                 (R_ICU_COMMON_BASE + R_ICU_COMMON_INTSELR31_OFFSET)

/* Register bit definitions */
/* IRQCR0 Register bit definitions */
#define R_ICU_COMMON_IRQCR0_IRQMD_SHIFT           (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR0_IRQMD_MASK            0x3
#  define R_ICU_COMMON_IRQCR0_IRQMD_00                    (0 << R_ICU_COMMON_IRQCR0_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR0_IRQMD_01                    (1 << R_ICU_COMMON_IRQCR0_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR0_IRQMD_10                    (2 << R_ICU_COMMON_IRQCR0_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR0_IRQMD_11                    (3 << R_ICU_COMMON_IRQCR0_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR0_FCLKSEL_SHIFT         (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR0_FCLKSEL_MASK          0x30
#  define R_ICU_COMMON_IRQCR0_FCLKSEL_00                  (0 << R_ICU_COMMON_IRQCR0_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR0_FCLKSEL_01                  (1 << R_ICU_COMMON_IRQCR0_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR0_FCLKSEL_10                  (2 << R_ICU_COMMON_IRQCR0_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR0_FCLKSEL_11                  (3 << R_ICU_COMMON_IRQCR0_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR0_FLTEN                 (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR1 Register bit definitions */
#define R_ICU_COMMON_IRQCR1_IRQMD_SHIFT           (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR1_IRQMD_MASK            0x3
#  define R_ICU_COMMON_IRQCR1_IRQMD_00                    (0 << R_ICU_COMMON_IRQCR1_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR1_IRQMD_01                    (1 << R_ICU_COMMON_IRQCR1_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR1_IRQMD_10                    (2 << R_ICU_COMMON_IRQCR1_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR1_IRQMD_11                    (3 << R_ICU_COMMON_IRQCR1_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR1_FCLKSEL_SHIFT         (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR1_FCLKSEL_MASK          0x30
#  define R_ICU_COMMON_IRQCR1_FCLKSEL_00                  (0 << R_ICU_COMMON_IRQCR1_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR1_FCLKSEL_01                  (1 << R_ICU_COMMON_IRQCR1_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR1_FCLKSEL_10                  (2 << R_ICU_COMMON_IRQCR1_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR1_FCLKSEL_11                  (3 << R_ICU_COMMON_IRQCR1_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR1_FLTEN                 (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR2 Register bit definitions */
#define R_ICU_COMMON_IRQCR2_IRQMD_SHIFT           (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR2_IRQMD_MASK            0x3
#  define R_ICU_COMMON_IRQCR2_IRQMD_00                    (0 << R_ICU_COMMON_IRQCR2_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR2_IRQMD_01                    (1 << R_ICU_COMMON_IRQCR2_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR2_IRQMD_10                    (2 << R_ICU_COMMON_IRQCR2_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR2_IRQMD_11                    (3 << R_ICU_COMMON_IRQCR2_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR2_FCLKSEL_SHIFT         (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR2_FCLKSEL_MASK          0x30
#  define R_ICU_COMMON_IRQCR2_FCLKSEL_00                  (0 << R_ICU_COMMON_IRQCR2_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR2_FCLKSEL_01                  (1 << R_ICU_COMMON_IRQCR2_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR2_FCLKSEL_10                  (2 << R_ICU_COMMON_IRQCR2_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR2_FCLKSEL_11                  (3 << R_ICU_COMMON_IRQCR2_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR2_FLTEN                 (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR3 Register bit definitions */
#define R_ICU_COMMON_IRQCR3_IRQMD_SHIFT           (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR3_IRQMD_MASK            0x3
#  define R_ICU_COMMON_IRQCR3_IRQMD_00                    (0 << R_ICU_COMMON_IRQCR3_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR3_IRQMD_01                    (1 << R_ICU_COMMON_IRQCR3_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR3_IRQMD_10                    (2 << R_ICU_COMMON_IRQCR3_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR3_IRQMD_11                    (3 << R_ICU_COMMON_IRQCR3_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR3_FCLKSEL_SHIFT         (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR3_FCLKSEL_MASK          0x30
#  define R_ICU_COMMON_IRQCR3_FCLKSEL_00                  (0 << R_ICU_COMMON_IRQCR3_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR3_FCLKSEL_01                  (1 << R_ICU_COMMON_IRQCR3_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR3_FCLKSEL_10                  (2 << R_ICU_COMMON_IRQCR3_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR3_FCLKSEL_11                  (3 << R_ICU_COMMON_IRQCR3_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR3_FLTEN                 (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR4 Register bit definitions */
#define R_ICU_COMMON_IRQCR4_IRQMD_SHIFT           (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR4_IRQMD_MASK            0x3
#  define R_ICU_COMMON_IRQCR4_IRQMD_00                    (0 << R_ICU_COMMON_IRQCR4_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR4_IRQMD_01                    (1 << R_ICU_COMMON_IRQCR4_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR4_IRQMD_10                    (2 << R_ICU_COMMON_IRQCR4_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR4_IRQMD_11                    (3 << R_ICU_COMMON_IRQCR4_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR4_FCLKSEL_SHIFT         (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR4_FCLKSEL_MASK          0x30
#  define R_ICU_COMMON_IRQCR4_FCLKSEL_00                  (0 << R_ICU_COMMON_IRQCR4_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR4_FCLKSEL_01                  (1 << R_ICU_COMMON_IRQCR4_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR4_FCLKSEL_10                  (2 << R_ICU_COMMON_IRQCR4_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR4_FCLKSEL_11                  (3 << R_ICU_COMMON_IRQCR4_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR4_FLTEN                 (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR5 Register bit definitions */
#define R_ICU_COMMON_IRQCR5_IRQMD_SHIFT           (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR5_IRQMD_MASK            0x3
#  define R_ICU_COMMON_IRQCR5_IRQMD_00                    (0 << R_ICU_COMMON_IRQCR5_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR5_IRQMD_01                    (1 << R_ICU_COMMON_IRQCR5_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR5_IRQMD_10                    (2 << R_ICU_COMMON_IRQCR5_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR5_IRQMD_11                    (3 << R_ICU_COMMON_IRQCR5_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR5_FCLKSEL_SHIFT         (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR5_FCLKSEL_MASK          0x30
#  define R_ICU_COMMON_IRQCR5_FCLKSEL_00                  (0 << R_ICU_COMMON_IRQCR5_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR5_FCLKSEL_01                  (1 << R_ICU_COMMON_IRQCR5_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR5_FCLKSEL_10                  (2 << R_ICU_COMMON_IRQCR5_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR5_FCLKSEL_11                  (3 << R_ICU_COMMON_IRQCR5_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR5_FLTEN                 (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR6 Register bit definitions */
#define R_ICU_COMMON_IRQCR6_IRQMD_SHIFT           (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR6_IRQMD_MASK            0x3
#  define R_ICU_COMMON_IRQCR6_IRQMD_00                    (0 << R_ICU_COMMON_IRQCR6_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR6_IRQMD_01                    (1 << R_ICU_COMMON_IRQCR6_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR6_IRQMD_10                    (2 << R_ICU_COMMON_IRQCR6_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR6_IRQMD_11                    (3 << R_ICU_COMMON_IRQCR6_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR6_FCLKSEL_SHIFT         (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR6_FCLKSEL_MASK          0x30
#  define R_ICU_COMMON_IRQCR6_FCLKSEL_00                  (0 << R_ICU_COMMON_IRQCR6_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR6_FCLKSEL_01                  (1 << R_ICU_COMMON_IRQCR6_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR6_FCLKSEL_10                  (2 << R_ICU_COMMON_IRQCR6_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR6_FCLKSEL_11                  (3 << R_ICU_COMMON_IRQCR6_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR6_FLTEN                 (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR7 Register bit definitions */
#define R_ICU_COMMON_IRQCR7_IRQMD_SHIFT           (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR7_IRQMD_MASK            0x3
#  define R_ICU_COMMON_IRQCR7_IRQMD_00                    (0 << R_ICU_COMMON_IRQCR7_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR7_IRQMD_01                    (1 << R_ICU_COMMON_IRQCR7_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR7_IRQMD_10                    (2 << R_ICU_COMMON_IRQCR7_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR7_IRQMD_11                    (3 << R_ICU_COMMON_IRQCR7_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR7_FCLKSEL_SHIFT         (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR7_FCLKSEL_MASK          0x30
#  define R_ICU_COMMON_IRQCR7_FCLKSEL_00                  (0 << R_ICU_COMMON_IRQCR7_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR7_FCLKSEL_01                  (1 << R_ICU_COMMON_IRQCR7_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR7_FCLKSEL_10                  (2 << R_ICU_COMMON_IRQCR7_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR7_FCLKSEL_11                  (3 << R_ICU_COMMON_IRQCR7_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR7_FLTEN                 (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR8 Register bit definitions */
#define R_ICU_COMMON_IRQCR8_IRQMD_SHIFT           (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR8_IRQMD_MASK            0x3
#  define R_ICU_COMMON_IRQCR8_IRQMD_00                    (0 << R_ICU_COMMON_IRQCR8_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR8_IRQMD_01                    (1 << R_ICU_COMMON_IRQCR8_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR8_IRQMD_10                    (2 << R_ICU_COMMON_IRQCR8_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR8_IRQMD_11                    (3 << R_ICU_COMMON_IRQCR8_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR8_FCLKSEL_SHIFT         (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR8_FCLKSEL_MASK          0x30
#  define R_ICU_COMMON_IRQCR8_FCLKSEL_00                  (0 << R_ICU_COMMON_IRQCR8_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR8_FCLKSEL_01                  (1 << R_ICU_COMMON_IRQCR8_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR8_FCLKSEL_10                  (2 << R_ICU_COMMON_IRQCR8_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR8_FCLKSEL_11                  (3 << R_ICU_COMMON_IRQCR8_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR8_FLTEN                 (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR9 Register bit definitions */
#define R_ICU_COMMON_IRQCR9_IRQMD_SHIFT           (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR9_IRQMD_MASK            0x3
#  define R_ICU_COMMON_IRQCR9_IRQMD_00                    (0 << R_ICU_COMMON_IRQCR9_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR9_IRQMD_01                    (1 << R_ICU_COMMON_IRQCR9_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR9_IRQMD_10                    (2 << R_ICU_COMMON_IRQCR9_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR9_IRQMD_11                    (3 << R_ICU_COMMON_IRQCR9_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR9_FCLKSEL_SHIFT         (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR9_FCLKSEL_MASK          0x30
#  define R_ICU_COMMON_IRQCR9_FCLKSEL_00                  (0 << R_ICU_COMMON_IRQCR9_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR9_FCLKSEL_01                  (1 << R_ICU_COMMON_IRQCR9_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR9_FCLKSEL_10                  (2 << R_ICU_COMMON_IRQCR9_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR9_FCLKSEL_11                  (3 << R_ICU_COMMON_IRQCR9_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR9_FLTEN                 (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR10 Register bit definitions */
#define R_ICU_COMMON_IRQCR10_IRQMD_SHIFT          (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR10_IRQMD_MASK           0x3
#  define R_ICU_COMMON_IRQCR10_IRQMD_00                   (0 << R_ICU_COMMON_IRQCR10_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR10_IRQMD_01                   (1 << R_ICU_COMMON_IRQCR10_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR10_IRQMD_10                   (2 << R_ICU_COMMON_IRQCR10_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR10_IRQMD_11                   (3 << R_ICU_COMMON_IRQCR10_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR10_FCLKSEL_SHIFT        (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR10_FCLKSEL_MASK         0x30
#  define R_ICU_COMMON_IRQCR10_FCLKSEL_00                 (0 << R_ICU_COMMON_IRQCR10_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR10_FCLKSEL_01                 (1 << R_ICU_COMMON_IRQCR10_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR10_FCLKSEL_10                 (2 << R_ICU_COMMON_IRQCR10_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR10_FCLKSEL_11                 (3 << R_ICU_COMMON_IRQCR10_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR10_FLTEN                (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR11 Register bit definitions */
#define R_ICU_COMMON_IRQCR11_IRQMD_SHIFT          (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR11_IRQMD_MASK           0x3
#  define R_ICU_COMMON_IRQCR11_IRQMD_00                   (0 << R_ICU_COMMON_IRQCR11_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR11_IRQMD_01                   (1 << R_ICU_COMMON_IRQCR11_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR11_IRQMD_10                   (2 << R_ICU_COMMON_IRQCR11_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR11_IRQMD_11                   (3 << R_ICU_COMMON_IRQCR11_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR11_FCLKSEL_SHIFT        (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR11_FCLKSEL_MASK         0x30
#  define R_ICU_COMMON_IRQCR11_FCLKSEL_00                 (0 << R_ICU_COMMON_IRQCR11_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR11_FCLKSEL_01                 (1 << R_ICU_COMMON_IRQCR11_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR11_FCLKSEL_10                 (2 << R_ICU_COMMON_IRQCR11_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR11_FCLKSEL_11                 (3 << R_ICU_COMMON_IRQCR11_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR11_FLTEN                (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR12 Register bit definitions */
#define R_ICU_COMMON_IRQCR12_IRQMD_SHIFT          (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR12_IRQMD_MASK           0x3
#  define R_ICU_COMMON_IRQCR12_IRQMD_00                   (0 << R_ICU_COMMON_IRQCR12_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR12_IRQMD_01                   (1 << R_ICU_COMMON_IRQCR12_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR12_IRQMD_10                   (2 << R_ICU_COMMON_IRQCR12_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR12_IRQMD_11                   (3 << R_ICU_COMMON_IRQCR12_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR12_FCLKSEL_SHIFT        (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR12_FCLKSEL_MASK         0x30
#  define R_ICU_COMMON_IRQCR12_FCLKSEL_00                 (0 << R_ICU_COMMON_IRQCR12_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR12_FCLKSEL_01                 (1 << R_ICU_COMMON_IRQCR12_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR12_FCLKSEL_10                 (2 << R_ICU_COMMON_IRQCR12_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR12_FCLKSEL_11                 (3 << R_ICU_COMMON_IRQCR12_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR12_FLTEN                (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR13 Register bit definitions */
#define R_ICU_COMMON_IRQCR13_IRQMD_SHIFT          (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR13_IRQMD_MASK           0x3
#  define R_ICU_COMMON_IRQCR13_IRQMD_00                   (0 << R_ICU_COMMON_IRQCR13_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR13_IRQMD_01                   (1 << R_ICU_COMMON_IRQCR13_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR13_IRQMD_10                   (2 << R_ICU_COMMON_IRQCR13_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR13_IRQMD_11                   (3 << R_ICU_COMMON_IRQCR13_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR13_FCLKSEL_SHIFT        (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR13_FCLKSEL_MASK         0x30
#  define R_ICU_COMMON_IRQCR13_FCLKSEL_00                 (0 << R_ICU_COMMON_IRQCR13_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR13_FCLKSEL_01                 (1 << R_ICU_COMMON_IRQCR13_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR13_FCLKSEL_10                 (2 << R_ICU_COMMON_IRQCR13_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR13_FCLKSEL_11                 (3 << R_ICU_COMMON_IRQCR13_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR13_FLTEN                (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR14 Register bit definitions */
#define R_ICU_COMMON_IRQCR14_IRQMD_SHIFT          (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR14_IRQMD_MASK           0x3
#  define R_ICU_COMMON_IRQCR14_IRQMD_00                   (0 << R_ICU_COMMON_IRQCR14_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR14_IRQMD_01                   (1 << R_ICU_COMMON_IRQCR14_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR14_IRQMD_10                   (2 << R_ICU_COMMON_IRQCR14_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR14_IRQMD_11                   (3 << R_ICU_COMMON_IRQCR14_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR14_FCLKSEL_SHIFT        (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR14_FCLKSEL_MASK         0x30
#  define R_ICU_COMMON_IRQCR14_FCLKSEL_00                 (0 << R_ICU_COMMON_IRQCR14_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR14_FCLKSEL_01                 (1 << R_ICU_COMMON_IRQCR14_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR14_FCLKSEL_10                 (2 << R_ICU_COMMON_IRQCR14_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR14_FCLKSEL_11                 (3 << R_ICU_COMMON_IRQCR14_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR14_FLTEN                (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR15 Register bit definitions */
#define R_ICU_COMMON_IRQCR15_IRQMD_SHIFT          (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR15_IRQMD_MASK           0x3
#  define R_ICU_COMMON_IRQCR15_IRQMD_00                   (0 << R_ICU_COMMON_IRQCR15_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR15_IRQMD_01                   (1 << R_ICU_COMMON_IRQCR15_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR15_IRQMD_10                   (2 << R_ICU_COMMON_IRQCR15_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR15_IRQMD_11                   (3 << R_ICU_COMMON_IRQCR15_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR15_FCLKSEL_SHIFT        (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR15_FCLKSEL_MASK         0x30
#  define R_ICU_COMMON_IRQCR15_FCLKSEL_00                 (0 << R_ICU_COMMON_IRQCR15_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR15_FCLKSEL_01                 (1 << R_ICU_COMMON_IRQCR15_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR15_FCLKSEL_10                 (2 << R_ICU_COMMON_IRQCR15_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR15_FCLKSEL_11                 (3 << R_ICU_COMMON_IRQCR15_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR15_FLTEN                (1 << 7)  /* IRQi Digital Filter Enable */

/* NMICR Register bit definitions */
#define R_ICU_COMMON_NMICR_NMIMD                  (1 << 0)  /* NMI Detection Set */

#define R_ICU_COMMON_NMICR_NFCLKSEL_SHIFT         (4)  /* NMI Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_NMICR_NFCLKSEL_MASK          0x30
#  define R_ICU_COMMON_NMICR_NFCLKSEL_00                  (0 << R_ICU_COMMON_NMICR_NFCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_NMICR_NFCLKSEL_01                  (1 << R_ICU_COMMON_NMICR_NFCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_NMICR_NFCLKSEL_10                  (2 << R_ICU_COMMON_NMICR_NFCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_NMICR_NFCLKSEL_11                  (3 << R_ICU_COMMON_NMICR_NFCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_NMICR_NFLTEN                 (1 << 7)  /* NMI Digital Filter Enable */

/* IRQCR16 Register bit definitions */
#define R_ICU_COMMON_IRQCR16_IRQMD_SHIFT          (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR16_IRQMD_MASK           0x3
#  define R_ICU_COMMON_IRQCR16_IRQMD_00                   (0 << R_ICU_COMMON_IRQCR16_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR16_IRQMD_01                   (1 << R_ICU_COMMON_IRQCR16_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR16_IRQMD_10                   (2 << R_ICU_COMMON_IRQCR16_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR16_IRQMD_11                   (3 << R_ICU_COMMON_IRQCR16_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR16_FCLKSEL_SHIFT        (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR16_FCLKSEL_MASK         0x30
#  define R_ICU_COMMON_IRQCR16_FCLKSEL_00                 (0 << R_ICU_COMMON_IRQCR16_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR16_FCLKSEL_01                 (1 << R_ICU_COMMON_IRQCR16_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR16_FCLKSEL_10                 (2 << R_ICU_COMMON_IRQCR16_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR16_FCLKSEL_11                 (3 << R_ICU_COMMON_IRQCR16_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR16_FLTEN                (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR17 Register bit definitions */
#define R_ICU_COMMON_IRQCR17_IRQMD_SHIFT          (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR17_IRQMD_MASK           0x3
#  define R_ICU_COMMON_IRQCR17_IRQMD_00                   (0 << R_ICU_COMMON_IRQCR17_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR17_IRQMD_01                   (1 << R_ICU_COMMON_IRQCR17_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR17_IRQMD_10                   (2 << R_ICU_COMMON_IRQCR17_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR17_IRQMD_11                   (3 << R_ICU_COMMON_IRQCR17_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR17_FCLKSEL_SHIFT        (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR17_FCLKSEL_MASK         0x30
#  define R_ICU_COMMON_IRQCR17_FCLKSEL_00                 (0 << R_ICU_COMMON_IRQCR17_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR17_FCLKSEL_01                 (1 << R_ICU_COMMON_IRQCR17_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR17_FCLKSEL_10                 (2 << R_ICU_COMMON_IRQCR17_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR17_FCLKSEL_11                 (3 << R_ICU_COMMON_IRQCR17_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR17_FLTEN                (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR18 Register bit definitions */
#define R_ICU_COMMON_IRQCR18_IRQMD_SHIFT          (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR18_IRQMD_MASK           0x3
#  define R_ICU_COMMON_IRQCR18_IRQMD_00                   (0 << R_ICU_COMMON_IRQCR18_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR18_IRQMD_01                   (1 << R_ICU_COMMON_IRQCR18_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR18_IRQMD_10                   (2 << R_ICU_COMMON_IRQCR18_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR18_IRQMD_11                   (3 << R_ICU_COMMON_IRQCR18_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR18_FCLKSEL_SHIFT        (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR18_FCLKSEL_MASK         0x30
#  define R_ICU_COMMON_IRQCR18_FCLKSEL_00                 (0 << R_ICU_COMMON_IRQCR18_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR18_FCLKSEL_01                 (1 << R_ICU_COMMON_IRQCR18_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR18_FCLKSEL_10                 (2 << R_ICU_COMMON_IRQCR18_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR18_FCLKSEL_11                 (3 << R_ICU_COMMON_IRQCR18_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR18_FLTEN                (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR19 Register bit definitions */
#define R_ICU_COMMON_IRQCR19_IRQMD_SHIFT          (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR19_IRQMD_MASK           0x3
#  define R_ICU_COMMON_IRQCR19_IRQMD_00                   (0 << R_ICU_COMMON_IRQCR19_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR19_IRQMD_01                   (1 << R_ICU_COMMON_IRQCR19_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR19_IRQMD_10                   (2 << R_ICU_COMMON_IRQCR19_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR19_IRQMD_11                   (3 << R_ICU_COMMON_IRQCR19_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR19_FCLKSEL_SHIFT        (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR19_FCLKSEL_MASK         0x30
#  define R_ICU_COMMON_IRQCR19_FCLKSEL_00                 (0 << R_ICU_COMMON_IRQCR19_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR19_FCLKSEL_01                 (1 << R_ICU_COMMON_IRQCR19_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR19_FCLKSEL_10                 (2 << R_ICU_COMMON_IRQCR19_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR19_FCLKSEL_11                 (3 << R_ICU_COMMON_IRQCR19_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR19_FLTEN                (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR20 Register bit definitions */
#define R_ICU_COMMON_IRQCR20_IRQMD_SHIFT          (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR20_IRQMD_MASK           0x3
#  define R_ICU_COMMON_IRQCR20_IRQMD_00                   (0 << R_ICU_COMMON_IRQCR20_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR20_IRQMD_01                   (1 << R_ICU_COMMON_IRQCR20_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR20_IRQMD_10                   (2 << R_ICU_COMMON_IRQCR20_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR20_IRQMD_11                   (3 << R_ICU_COMMON_IRQCR20_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR20_FCLKSEL_SHIFT        (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR20_FCLKSEL_MASK         0x30
#  define R_ICU_COMMON_IRQCR20_FCLKSEL_00                 (0 << R_ICU_COMMON_IRQCR20_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR20_FCLKSEL_01                 (1 << R_ICU_COMMON_IRQCR20_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR20_FCLKSEL_10                 (2 << R_ICU_COMMON_IRQCR20_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR20_FCLKSEL_11                 (3 << R_ICU_COMMON_IRQCR20_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR20_FLTEN                (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR21 Register bit definitions */
#define R_ICU_COMMON_IRQCR21_IRQMD_SHIFT          (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR21_IRQMD_MASK           0x3
#  define R_ICU_COMMON_IRQCR21_IRQMD_00                   (0 << R_ICU_COMMON_IRQCR21_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR21_IRQMD_01                   (1 << R_ICU_COMMON_IRQCR21_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR21_IRQMD_10                   (2 << R_ICU_COMMON_IRQCR21_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR21_IRQMD_11                   (3 << R_ICU_COMMON_IRQCR21_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR21_FCLKSEL_SHIFT        (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR21_FCLKSEL_MASK         0x30
#  define R_ICU_COMMON_IRQCR21_FCLKSEL_00                 (0 << R_ICU_COMMON_IRQCR21_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR21_FCLKSEL_01                 (1 << R_ICU_COMMON_IRQCR21_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR21_FCLKSEL_10                 (2 << R_ICU_COMMON_IRQCR21_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR21_FCLKSEL_11                 (3 << R_ICU_COMMON_IRQCR21_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR21_FLTEN                (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR22 Register bit definitions */
#define R_ICU_COMMON_IRQCR22_IRQMD_SHIFT          (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR22_IRQMD_MASK           0x3
#  define R_ICU_COMMON_IRQCR22_IRQMD_00                   (0 << R_ICU_COMMON_IRQCR22_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR22_IRQMD_01                   (1 << R_ICU_COMMON_IRQCR22_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR22_IRQMD_10                   (2 << R_ICU_COMMON_IRQCR22_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR22_IRQMD_11                   (3 << R_ICU_COMMON_IRQCR22_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR22_FCLKSEL_SHIFT        (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR22_FCLKSEL_MASK         0x30
#  define R_ICU_COMMON_IRQCR22_FCLKSEL_00                 (0 << R_ICU_COMMON_IRQCR22_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR22_FCLKSEL_01                 (1 << R_ICU_COMMON_IRQCR22_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR22_FCLKSEL_10                 (2 << R_ICU_COMMON_IRQCR22_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR22_FCLKSEL_11                 (3 << R_ICU_COMMON_IRQCR22_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR22_FLTEN                (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR23 Register bit definitions */
#define R_ICU_COMMON_IRQCR23_IRQMD_SHIFT          (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR23_IRQMD_MASK           0x3
#  define R_ICU_COMMON_IRQCR23_IRQMD_00                   (0 << R_ICU_COMMON_IRQCR23_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR23_IRQMD_01                   (1 << R_ICU_COMMON_IRQCR23_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR23_IRQMD_10                   (2 << R_ICU_COMMON_IRQCR23_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR23_IRQMD_11                   (3 << R_ICU_COMMON_IRQCR23_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR23_FCLKSEL_SHIFT        (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR23_FCLKSEL_MASK         0x30
#  define R_ICU_COMMON_IRQCR23_FCLKSEL_00                 (0 << R_ICU_COMMON_IRQCR23_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR23_FCLKSEL_01                 (1 << R_ICU_COMMON_IRQCR23_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR23_FCLKSEL_10                 (2 << R_ICU_COMMON_IRQCR23_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR23_FCLKSEL_11                 (3 << R_ICU_COMMON_IRQCR23_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR23_FLTEN                (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR24 Register bit definitions */
#define R_ICU_COMMON_IRQCR24_IRQMD_SHIFT          (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR24_IRQMD_MASK           0x3
#  define R_ICU_COMMON_IRQCR24_IRQMD_00                   (0 << R_ICU_COMMON_IRQCR24_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR24_IRQMD_01                   (1 << R_ICU_COMMON_IRQCR24_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR24_IRQMD_10                   (2 << R_ICU_COMMON_IRQCR24_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR24_IRQMD_11                   (3 << R_ICU_COMMON_IRQCR24_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR24_FCLKSEL_SHIFT        (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR24_FCLKSEL_MASK         0x30
#  define R_ICU_COMMON_IRQCR24_FCLKSEL_00                 (0 << R_ICU_COMMON_IRQCR24_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR24_FCLKSEL_01                 (1 << R_ICU_COMMON_IRQCR24_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR24_FCLKSEL_10                 (2 << R_ICU_COMMON_IRQCR24_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR24_FCLKSEL_11                 (3 << R_ICU_COMMON_IRQCR24_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR24_FLTEN                (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR25 Register bit definitions */
#define R_ICU_COMMON_IRQCR25_IRQMD_SHIFT          (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR25_IRQMD_MASK           0x3
#  define R_ICU_COMMON_IRQCR25_IRQMD_00                   (0 << R_ICU_COMMON_IRQCR25_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR25_IRQMD_01                   (1 << R_ICU_COMMON_IRQCR25_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR25_IRQMD_10                   (2 << R_ICU_COMMON_IRQCR25_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR25_IRQMD_11                   (3 << R_ICU_COMMON_IRQCR25_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR25_FCLKSEL_SHIFT        (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR25_FCLKSEL_MASK         0x30
#  define R_ICU_COMMON_IRQCR25_FCLKSEL_00                 (0 << R_ICU_COMMON_IRQCR25_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR25_FCLKSEL_01                 (1 << R_ICU_COMMON_IRQCR25_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR25_FCLKSEL_10                 (2 << R_ICU_COMMON_IRQCR25_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR25_FCLKSEL_11                 (3 << R_ICU_COMMON_IRQCR25_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR25_FLTEN                (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR26 Register bit definitions */
#define R_ICU_COMMON_IRQCR26_IRQMD_SHIFT          (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR26_IRQMD_MASK           0x3
#  define R_ICU_COMMON_IRQCR26_IRQMD_00                   (0 << R_ICU_COMMON_IRQCR26_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR26_IRQMD_01                   (1 << R_ICU_COMMON_IRQCR26_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR26_IRQMD_10                   (2 << R_ICU_COMMON_IRQCR26_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR26_IRQMD_11                   (3 << R_ICU_COMMON_IRQCR26_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR26_FCLKSEL_SHIFT        (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR26_FCLKSEL_MASK         0x30
#  define R_ICU_COMMON_IRQCR26_FCLKSEL_00                 (0 << R_ICU_COMMON_IRQCR26_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR26_FCLKSEL_01                 (1 << R_ICU_COMMON_IRQCR26_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR26_FCLKSEL_10                 (2 << R_ICU_COMMON_IRQCR26_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR26_FCLKSEL_11                 (3 << R_ICU_COMMON_IRQCR26_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR26_FLTEN                (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR27 Register bit definitions */
#define R_ICU_COMMON_IRQCR27_IRQMD_SHIFT          (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR27_IRQMD_MASK           0x3
#  define R_ICU_COMMON_IRQCR27_IRQMD_00                   (0 << R_ICU_COMMON_IRQCR27_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR27_IRQMD_01                   (1 << R_ICU_COMMON_IRQCR27_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR27_IRQMD_10                   (2 << R_ICU_COMMON_IRQCR27_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR27_IRQMD_11                   (3 << R_ICU_COMMON_IRQCR27_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR27_FCLKSEL_SHIFT        (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR27_FCLKSEL_MASK         0x30
#  define R_ICU_COMMON_IRQCR27_FCLKSEL_00                 (0 << R_ICU_COMMON_IRQCR27_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR27_FCLKSEL_01                 (1 << R_ICU_COMMON_IRQCR27_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR27_FCLKSEL_10                 (2 << R_ICU_COMMON_IRQCR27_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR27_FCLKSEL_11                 (3 << R_ICU_COMMON_IRQCR27_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR27_FLTEN                (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR28 Register bit definitions */
#define R_ICU_COMMON_IRQCR28_IRQMD_SHIFT          (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR28_IRQMD_MASK           0x3
#  define R_ICU_COMMON_IRQCR28_IRQMD_00                   (0 << R_ICU_COMMON_IRQCR28_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR28_IRQMD_01                   (1 << R_ICU_COMMON_IRQCR28_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR28_IRQMD_10                   (2 << R_ICU_COMMON_IRQCR28_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR28_IRQMD_11                   (3 << R_ICU_COMMON_IRQCR28_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR28_FCLKSEL_SHIFT        (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR28_FCLKSEL_MASK         0x30
#  define R_ICU_COMMON_IRQCR28_FCLKSEL_00                 (0 << R_ICU_COMMON_IRQCR28_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR28_FCLKSEL_01                 (1 << R_ICU_COMMON_IRQCR28_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR28_FCLKSEL_10                 (2 << R_ICU_COMMON_IRQCR28_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR28_FCLKSEL_11                 (3 << R_ICU_COMMON_IRQCR28_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR28_FLTEN                (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR29 Register bit definitions */
#define R_ICU_COMMON_IRQCR29_IRQMD_SHIFT          (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR29_IRQMD_MASK           0x3
#  define R_ICU_COMMON_IRQCR29_IRQMD_00                   (0 << R_ICU_COMMON_IRQCR29_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR29_IRQMD_01                   (1 << R_ICU_COMMON_IRQCR29_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR29_IRQMD_10                   (2 << R_ICU_COMMON_IRQCR29_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR29_IRQMD_11                   (3 << R_ICU_COMMON_IRQCR29_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR29_FCLKSEL_SHIFT        (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR29_FCLKSEL_MASK         0x30
#  define R_ICU_COMMON_IRQCR29_FCLKSEL_00                 (0 << R_ICU_COMMON_IRQCR29_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR29_FCLKSEL_01                 (1 << R_ICU_COMMON_IRQCR29_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR29_FCLKSEL_10                 (2 << R_ICU_COMMON_IRQCR29_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR29_FCLKSEL_11                 (3 << R_ICU_COMMON_IRQCR29_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR29_FLTEN                (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR30 Register bit definitions */
#define R_ICU_COMMON_IRQCR30_IRQMD_SHIFT          (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR30_IRQMD_MASK           0x3
#  define R_ICU_COMMON_IRQCR30_IRQMD_00                   (0 << R_ICU_COMMON_IRQCR30_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR30_IRQMD_01                   (1 << R_ICU_COMMON_IRQCR30_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR30_IRQMD_10                   (2 << R_ICU_COMMON_IRQCR30_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR30_IRQMD_11                   (3 << R_ICU_COMMON_IRQCR30_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR30_FCLKSEL_SHIFT        (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR30_FCLKSEL_MASK         0x30
#  define R_ICU_COMMON_IRQCR30_FCLKSEL_00                 (0 << R_ICU_COMMON_IRQCR30_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR30_FCLKSEL_01                 (1 << R_ICU_COMMON_IRQCR30_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR30_FCLKSEL_10                 (2 << R_ICU_COMMON_IRQCR30_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR30_FCLKSEL_11                 (3 << R_ICU_COMMON_IRQCR30_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR30_FLTEN                (1 << 7)  /* IRQi Digital Filter Enable */

/* IRQCR31 Register bit definitions */
#define R_ICU_COMMON_IRQCR31_IRQMD_SHIFT          (0)  /* IRQi Detection Sense Select */
#define R_ICU_COMMON_IRQCR31_IRQMD_MASK           0x3
#  define R_ICU_COMMON_IRQCR31_IRQMD_00                   (0 << R_ICU_COMMON_IRQCR31_IRQMD_SHIFT)  /* Falling edge */
#  define R_ICU_COMMON_IRQCR31_IRQMD_01                   (1 << R_ICU_COMMON_IRQCR31_IRQMD_SHIFT)  /* Rising edge */
#  define R_ICU_COMMON_IRQCR31_IRQMD_10                   (2 << R_ICU_COMMON_IRQCR31_IRQMD_SHIFT)  /* Rising and falling edges */
#  define R_ICU_COMMON_IRQCR31_IRQMD_11                   (3 << R_ICU_COMMON_IRQCR31_IRQMD_SHIFT)  /* Low level */

#define R_ICU_COMMON_IRQCR31_FCLKSEL_SHIFT        (4)  /* IRQi Digital Filter Sampling Clock Select */
#define R_ICU_COMMON_IRQCR31_FCLKSEL_MASK         0x30
#  define R_ICU_COMMON_IRQCR31_FCLKSEL_00                 (0 << R_ICU_COMMON_IRQCR31_FCLKSEL_SHIFT)  /* PCLKB */
#  define R_ICU_COMMON_IRQCR31_FCLKSEL_01                 (1 << R_ICU_COMMON_IRQCR31_FCLKSEL_SHIFT)  /* PCLKB/8 */
#  define R_ICU_COMMON_IRQCR31_FCLKSEL_10                 (2 << R_ICU_COMMON_IRQCR31_FCLKSEL_SHIFT)  /* PCLKB/32 */
#  define R_ICU_COMMON_IRQCR31_FCLKSEL_11                 (3 << R_ICU_COMMON_IRQCR31_FCLKSEL_SHIFT)  /* PCLKB/64 */

#define R_ICU_COMMON_IRQCR31_FLTEN                (1 << 7)  /* IRQi Digital Filter Enable */

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
