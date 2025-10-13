/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_iic.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_IIC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_IIC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* IIC Base Address */
#ifndef R_IIC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_IIC_BASE           0x4025e000
#else
#define R_IIC_BASE           0x5025e000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_IIC_CH_STRIDE    0x00000100
#define R_IIC_CH_BASE(ch)   (R_IIC_BASE + ((uint32_t)(ch) * R_IIC_CH_STRIDE))

/* IIC Register Offsets */

#define R_IIC_ICCR1_OFFSET     0x00000000  /* I2C Bus Control Register 1 */

/* IIC Register Addresses */

#define R_IIC_ICCR1                 (R_IIC_BASE + R_IIC_ICCR1_OFFSET)

/* Register bit definitions */
/* ICCR1 Register bit definitions */
#define R_IIC_ICCR1_SDAI                          (1 << 0)  /* SDA Line Monitor */

#define R_IIC_ICCR1_SCLI                          (1 << 1)  /* SCL Line Monitor */

#define R_IIC_ICCR1_SDAO                          (1 << 2)  /* SDA Output Control/Monitor */

#define R_IIC_ICCR1_SCLO                          (1 << 3)  /* SCL Output Control/Monitor */

#define R_IIC_ICCR1_SOWP                          (1 << 4)  /* SCLO/SDAO Write Protect */

#define R_IIC_ICCR1_CLO                           (1 << 5)  /* Extra SCL Clock Cycle Output */

#define R_IIC_ICCR1_IICRST                        (1 << 6)  /* I2C Bus Interface Internal Reset */

#define R_IIC_ICCR1_ICE                           (1 << 7)  /* I2C Bus Interface Enable */


/* Maximum number of channels */

#define IIC_MAX_CHANNELS    3

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_IIC_H */
