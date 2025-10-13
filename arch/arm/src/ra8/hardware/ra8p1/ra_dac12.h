/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_dac12.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DAC12_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DAC12_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* DAC12 Base Address */
#ifndef R_DAC12_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_DAC12_BASE           0x40233000
#else
#define R_DAC12_BASE           0x50233000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_DAC12_CH_STRIDE    0x00000100
#define R_DAC12_CH_BASE(ch)   (R_DAC12_BASE + ((uint32_t)(ch) * R_DAC12_CH_STRIDE))

/* DAC12 Register Offsets */

#define R_DAC12_DADR_OFFSET     0x00000000  /* D/A Data Register */
#define R_DAC12_DACR0_OFFSET     0x00000004  /* D/A Control 0 Register */
#define R_DAC12_DACR1_OFFSET     0x00000008  /* D/A Control 1 Register */
#define R_DAC12_DACR2_OFFSET     0x0000000c  /* D/A Control 2 Register */

/* DAC12 Register Addresses */

#define R_DAC12_DADR                 (R_DAC12_BASE + R_DAC12_DADR_OFFSET)
#define R_DAC12_DACR0                 (R_DAC12_BASE + R_DAC12_DACR0_OFFSET)
#define R_DAC12_DACR1                 (R_DAC12_BASE + R_DAC12_DACR1_OFFSET)
#define R_DAC12_DACR2                 (R_DAC12_BASE + R_DAC12_DACR2_OFFSET)

/* Register bit definitions */
/* DACR Register bit definitions */
#define R_DAC12_DACR_DACEN                        (1 << 0)  /* D/A Output Enable */

#define R_DAC12_DACR_DAE                          (1 << 15)  /* D/A Enable R/W */

#define R_DAC12_DACR_DAOUTDIS                     (1 << 31)  /* Analog Output Disables */

/* DACR Register bit definitions */
#define R_DAC12_DACR_DPSEL                        (1 << 16)  /* DADR Format Select R/W */

/* DACR Register bit definitions */
#define R_DAC12_DACR_OFSSEL                       (1 << 8)  /* DAC Operating Voltage Mode Selection */


/* Maximum number of channels */

#define DAC12_MAX_CHANNELS    2

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DAC12_H */
