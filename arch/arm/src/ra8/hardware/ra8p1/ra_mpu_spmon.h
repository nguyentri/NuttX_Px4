/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_mpu_spmon.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MPU_SPMON_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MPU_SPMON_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* MPU_SPMON Base Address */
#ifndef R_MPU_SPMON_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_MPU_SPMON_BASE           0x40000d00
#else
#define R_MPU_SPMON_BASE           0x50000d00
#endif
#endif

/* MPU_SPMON Register Offsets */

/* SP[%s] Registers () */
#define R_MPU_SPMON_SP_OFFSET(m)                  (0x00000000 + ((m) * 0x00000010))  /* Stack Pointer Monitor */

/* MPU_SPMON Register Addresses */

#define R_MPU_SPMON_SP(m)                         (R_MPU_SPMON_BASE + R_MPU_SPMON_SP_OFFSET(m))

/* Register bit definitions */

/* Maximum number of channels */

#define MPU_SPMON_MAX_CHANNELS    2

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MPU_SPMON_H */
