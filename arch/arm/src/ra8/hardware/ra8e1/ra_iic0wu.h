/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8e1/ra_iic0wu.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_IIC0WU_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_IIC0WU_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* IIC0WU Base Address */
#ifndef R_IIC0WU_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_IIC0WU_BASE           0x4025e014
#else
#define R_IIC0WU_BASE           0x5025e014
#endif
#endif

/* IIC0WU Register Offsets */

#define R_IIC0WU_ICWUR_OFFSET                     0x00000002  /* I2C Bus Wakeup Unit Register */
#define R_IIC0WU_ICWUR2_OFFSET                    0x00000003  /* I2C Bus Wakeup Unit Register 2 */

/* IIC0WU Register Addresses */

#define R_IIC0WU_ICWUR                            (R_IIC0WU_BASE + R_IIC0WU_ICWUR_OFFSET)
#define R_IIC0WU_ICWUR2                           (R_IIC0WU_BASE + R_IIC0WU_ICWUR2_OFFSET)

/* Register bit definitions */
/* ICWUR Register bit definitions */
#define R_IIC0WU_ICWUR_WUAFA                      (1 << 0)  /* Wakeup Analog Filter Additional Selection */

#define R_IIC0WU_ICWUR_WUACK                      (1 << 4)  /* ACK Bit for Wakeup Mode */

#define R_IIC0WU_ICWUR_WUF                        (1 << 5)  /* Wakeup Event Occurrence Flag */

#define R_IIC0WU_ICWUR_WUIE                       (1 << 6)  /* Wakeup Interrupt Request Enable */

#define R_IIC0WU_ICWUR_WUE                        (1 << 7)  /* Wakeup Function Enable */

/* ICWUR2 Register bit definitions */
#define R_IIC0WU_ICWUR2_WUSEN                     (1 << 0)  /* Wakeup Function Synchronous Enable */

#define R_IIC0WU_ICWUR2_WUASYF                    (1 << 1)  /* Wakeup Function Asynchronous Operation Status Flag */

#define R_IIC0WU_ICWUR2_WUSYF                     (1 << 2)  /* Wakeup Function Synchronous Operation Status Flag */


/* Maximum number of channels */

#define IIC0WU_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_IIC0WU_H */
