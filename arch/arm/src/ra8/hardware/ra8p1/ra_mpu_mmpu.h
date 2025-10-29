/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_mpu_mmpu.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MPU_MMPU_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MPU_MMPU_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* MPU_MMPU Base Address */
#ifndef R_MPU_MMPU_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_MPU_MMPU_BASE           0x40000000
#else
#define R_MPU_MMPU_BASE           0x50000000
#endif
#endif

/* MPU_MMPU Register Offsets */

#define R_MPU_MMPU_OAD_OFFSET                     0x00000000  /* MMPU Operation After Detection Register */
#define R_MPU_MMPU_OADPT_OFFSET                   0x00000004  /* MMPU Operation After Detection Protect Register */
/* %s Registers (DMAC0,DMAC1,EDMAC,GLCDC,DRW,MIPI_DSI,CEU,MIPI_CSI,NPU) */
#define R_MPU_MMPU__OFFSET(m)                     (0x00000100 + ((m) * 0x00000200))  /* %s MMPU Registers */

/* MPU_MMPU Register Addresses */

#define R_MPU_MMPU_OAD                            (R_MPU_MMPU_BASE + R_MPU_MMPU_OAD_OFFSET)
#define R_MPU_MMPU_OADPT                          (R_MPU_MMPU_BASE + R_MPU_MMPU_OADPT_OFFSET)
#define R_MPU_MMPU_(m)                            (R_MPU_MMPU_BASE + R_MPU_MMPU__OFFSET(m))

/* Register bit definitions */
/* OAD Register bit definitions */
#define R_MPU_MMPU_OAD_KEY_SHIFT                  (8)  /* Write Keyword The data written to these bits are not stored. */
#define R_MPU_MMPU_OAD_KEY_MASK                   0xff00
#  define R_MPU_MMPU_OAD_KEY_0XA5                         (165 << R_MPU_MMPU_OAD_KEY_SHIFT)  /* Writing to the OAD and ENABLE bit is valid, when the KEY bits are written 0xA5. */

#define R_MPU_MMPU_OAD_OAD                        (1 << 0)  /* Operation after detection */

/* OADPT Register bit definitions */
#define R_MPU_MMPU_OADPT_KEY_SHIFT                (8)  /* Write Keyword The data written to these bits are not stored. */
#define R_MPU_MMPU_OADPT_KEY_MASK                 0xff00
#  define R_MPU_MMPU_OADPT_KEY_0XA5                       (165 << R_MPU_MMPU_OADPT_KEY_SHIFT)  /* Writing to the OAD and ENABLE bit is valid, when the KEY bits are written 0xA5. */

#define R_MPU_MMPU_OADPT_PROTECT                  (1 << 0)  /* Protection of register */


/* Maximum number of channels */

#define MPU_MMPU_MAX_CHANNELS    9

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MPU_MMPU_H */
