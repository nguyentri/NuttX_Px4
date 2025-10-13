/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_dac_b.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DAC_B_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DAC_B_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* DAC_B Base Address */
#ifndef R_DAC_B_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_DAC_B_BASE           0x40233000
#else
#define R_DAC_B_BASE           0x50233000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_DAC_B_CH_STRIDE    0x00000100
#define R_DAC_B_CH_BASE(ch)   (R_DAC_B_BASE + ((uint32_t)(ch) * R_DAC_B_CH_STRIDE))

/* DAC_B Register Offsets */

#define R_DAC_B_DADR_OFFSET                       0x00000000  /* D/A Data Register */
#define R_DAC_B_DACR0_OFFSET                      0x00000004  /* D/A Control 0 Register */
#define R_DAC_B_DACR1_OFFSET                      0x00000008  /* D/A Control 1 Register */
#define R_DAC_B_DACR2_OFFSET                      0x0000000c  /* D/A Control 2 Register */

/* DAC_B Register Addresses */

#define R_DAC_B_DADR(n)                           (R_DAC_B_CH_BASE(n) + R_DAC_B_DADR_OFFSET)
#define R_DAC_B_DACR0(n)                          (R_DAC_B_CH_BASE(n) + R_DAC_B_DACR0_OFFSET)
#define R_DAC_B_DACR1(n)                          (R_DAC_B_CH_BASE(n) + R_DAC_B_DACR1_OFFSET)
#define R_DAC_B_DACR2(n)                          (R_DAC_B_CH_BASE(n) + R_DAC_B_DACR2_OFFSET)

/* Register bit definitions */
/* DADR Register bit definitions */
#define R_DAC_B_DADR_DADR_SHIFT                   (0)  /* D/A converted data */
#define R_DAC_B_DADR_DADR_MASK                    0xffff

/* DACR0 Register bit definitions */
#define R_DAC_B_DACR0_DACEN                       (1 << 0)  /* D/A Output Enable */

#define R_DAC_B_DACR0_DAE                         (1 << 15)  /* D/A Enable R/W */

#define R_DAC_B_DACR0_DAOUTDIS                    (1 << 31)  /* Analog Output Disables */

/* DACR1 Register bit definitions */
#define R_DAC_B_DACR1_DPSEL                       (1 << 16)  /* DADR Format Select R/W */

/* DACR2 Register bit definitions */
#define R_DAC_B_DACR2_OFSSEL                      (1 << 8)  /* DAC Operating Voltage Mode Selection */


/* Maximum number of channels */

#define DAC_B_MAX_CHANNELS    2

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DAC_B_H */
