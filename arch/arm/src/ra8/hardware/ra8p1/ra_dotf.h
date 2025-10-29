/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_dotf.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DOTF_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DOTF_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* DOTF Base Address */
#ifndef R_DOTF_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_DOTF_BASE           0x40268800
#else
#define R_DOTF_BASE           0x50268800
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_DOTF_CH_STRIDE    0x00000100
#define R_DOTF_CH_BASE(ch)   (R_DOTF_BASE + ((uint32_t)(ch) * R_DOTF_CH_STRIDE))

/* DOTF Register Offsets */

#define R_DOTF_CONVAREAST_OFFSET                  0x00000000  /* DOTF Conversion Area Start Address Register */
#define R_DOTF_CONVAREAD_OFFSET                   0x00000004  /* DOTF Conversion Area End Address Register */
#define R_DOTF_REG00_OFFSET                       0x00000080  /* Register 0 */
#define R_DOTF_REG03_OFFSET                       0x0000008c  /* Register 03 */

/* DOTF Register Addresses */

#define R_DOTF_CONVAREAST(n)                      (R_DOTF_CH_BASE(n) + R_DOTF_CONVAREAST_OFFSET)
#define R_DOTF_CONVAREAD(n)                       (R_DOTF_CH_BASE(n) + R_DOTF_CONVAREAD_OFFSET)
#define R_DOTF_REG00(n)                           (R_DOTF_CH_BASE(n) + R_DOTF_REG00_OFFSET)
#define R_DOTF_REG03(n)                           (R_DOTF_CH_BASE(n) + R_DOTF_REG03_OFFSET)

/* Register bit definitions */
/* CONVAREAST Register bit definitions */
#define R_DOTF_CONVAREAST_RESERVED_SHIFT          (0)  /* These fields are read as 0 */
#define R_DOTF_CONVAREAST_RESERVED_MASK           0xfff

#define R_DOTF_CONVAREAST_CONVAREAST_SHIFT        (12)  /* First address of decryption processing area */
#define R_DOTF_CONVAREAST_CONVAREAST_MASK         0xfffff000

/* CONVAREAD Register bit definitions */
#define R_DOTF_CONVAREAD_RESERVED_SHIFT           (0)  /* These fields are read as 0 */
#define R_DOTF_CONVAREAD_RESERVED_MASK            0xfff

#define R_DOTF_CONVAREAD_CONVAREAD_SHIFT          (12)  /* End address of decryption processing area */
#define R_DOTF_CONVAREAD_CONVAREAD_MASK           0xfffff000

/* REG00 Register bit definitions */
#define R_DOTF_REG00_RESERVED_SHIFT               (30)  /* These fields are read as 0 */
#define R_DOTF_REG00_RESERVED_MASK                0xc0000000

#define R_DOTF_REG00_B09                          (1 << 9)  /* Bit 09 */

#define R_DOTF_REG00_B16                          (1 << 16)  /* Bit 09 */

#define R_DOTF_REG00_B17                          (1 << 17)  /* Bit 17 */

#define R_DOTF_REG00_B20                          (1 << 20)  /* Bit 20 */

#define R_DOTF_REG00_B24_SHIFT                    (24)  /* Bit24-25 */
#define R_DOTF_REG00_B24_MASK                     0x3000000
#  define R_DOTF_REG00_B24_00                             (0 << R_DOTF_REG00_B24_SHIFT)  /* Bit24-25 */
#  define R_DOTF_REG00_B24_01                             (1 << R_DOTF_REG00_B24_SHIFT)  /* Bit24-25 */
#  define R_DOTF_REG00_B24_10                             (2 << R_DOTF_REG00_B24_SHIFT)  /* Bit24-25 */
#  define R_DOTF_REG00_B24_11                             (3 << R_DOTF_REG00_B24_SHIFT)  /* Bit24-25 */

#define R_DOTF_REG00_B28_SHIFT                    (28)  /* Bit28-29 */
#define R_DOTF_REG00_B28_MASK                     0x30000000
#  define R_DOTF_REG00_B28_00                             (0 << R_DOTF_REG00_B28_SHIFT)  /* Bit28-29 */
#  define R_DOTF_REG00_B28_01                             (1 << R_DOTF_REG00_B28_SHIFT)  /* Bit28-29 */
#  define R_DOTF_REG00_B28_10                             (2 << R_DOTF_REG00_B28_SHIFT)  /* Bit28-29 */
#  define R_DOTF_REG00_B28_11                             (3 << R_DOTF_REG00_B28_SHIFT)  /* Bit28-29 */

/* REG03 Register bit definitions */
#define R_DOTF_REG03_B00_SHIFT                    (0)  /* Bit 0 */
#define R_DOTF_REG03_B00_MASK                     0xffffffff


/* Maximum number of channels */

#define DOTF_MAX_CHANNELS    2

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DOTF_H */
