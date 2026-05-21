/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_tsu.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_TSU_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_TSU_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* TSU Base Addresses ****************************************************/

#ifndef RZV_TSU0_BASE
#  define RZV_TSU0_BASE               0x11000000
#endif
#ifndef RZV_TSU1_BASE
#  define RZV_TSU1_BASE               0x14002000
#endif

/* TSU Register Offsets ***************************************************/

#define RZV_TSU_TSU_SSUSR_OFFSET                         0x0000  /* TSU_SSUSR */
#define RZV_TSU_TSU_STRGR_OFFSET                         0x0004  /* TSU_STRGR */
#define RZV_TSU_TSU_SOSR1_OFFSET                         0x0008  /* TSU_SOSR1 */
#define RZV_TSU_TSU_SCRR_OFFSET                          0x0010  /* TSU_SCRR */
#define RZV_TSU_TSU_SSR_OFFSET                           0x0014  /* TSU_SSR */
#define RZV_TSU_TSU_CMSR_OFFSET                          0x0018  /* TSU_CMSR */
#define RZV_TSU_TSU_LLSR_OFFSET                          0x001C  /* TSU_LLSR */
#define RZV_TSU_TSU_ULSR_OFFSET                          0x0020  /* TSU_ULSR */
#define RZV_TSU_TSU_SISR_OFFSET                          0x0030  /* TSU_SISR */
#define RZV_TSU_TSU_SIER_OFFSET                          0x0034  /* TSU_SIER */
#define RZV_TSU_TSU_SICR_OFFSET                          0x0038  /* TSU_SICR */

/* TSU Register Addresses **************************************************/

#define RZV_TSU_TSU_SSUSR(ch)                        (RZV_TSU##ch##_BASE + RZV_TSU_TSU_SSUSR_OFFSET)
#define RZV_TSU_TSU_STRGR(ch)                        (RZV_TSU##ch##_BASE + RZV_TSU_TSU_STRGR_OFFSET)
#define RZV_TSU_TSU_SOSR1(ch)                        (RZV_TSU##ch##_BASE + RZV_TSU_TSU_SOSR1_OFFSET)
#define RZV_TSU_TSU_SCRR(ch)                         (RZV_TSU##ch##_BASE + RZV_TSU_TSU_SCRR_OFFSET)
#define RZV_TSU_TSU_SSR(ch)                          (RZV_TSU##ch##_BASE + RZV_TSU_TSU_SSR_OFFSET)
#define RZV_TSU_TSU_CMSR(ch)                         (RZV_TSU##ch##_BASE + RZV_TSU_TSU_CMSR_OFFSET)
#define RZV_TSU_TSU_LLSR(ch)                         (RZV_TSU##ch##_BASE + RZV_TSU_TSU_LLSR_OFFSET)
#define RZV_TSU_TSU_ULSR(ch)                         (RZV_TSU##ch##_BASE + RZV_TSU_TSU_ULSR_OFFSET)
#define RZV_TSU_TSU_SISR(ch)                         (RZV_TSU##ch##_BASE + RZV_TSU_TSU_SISR_OFFSET)
#define RZV_TSU_TSU_SIER(ch)                         (RZV_TSU##ch##_BASE + RZV_TSU_TSU_SIER_OFFSET)
#define RZV_TSU_TSU_SICR(ch)                         (RZV_TSU##ch##_BASE + RZV_TSU_TSU_SICR_OFFSET)

/* TSU B0_CMSR Register Bit Definitions ******************************/

#define TSU_B0_CMSR_CMPEN                       (1 << 0)  /* Cmpen */

#define TSU_B0_CMSR_CMPCOND                     (1 << 1)  /* Cmpcond */

/* TSU B0_LLSR Register Bit Definitions ******************************/

#define TSU_B0_LLSR_LLIM_SHIFT                  (0)      /* Bits 0-11: Llim */
#define TSU_B0_LLSR_LLIM_MASK                   (0xfff << TSU_B0_LLSR_LLIM_SHIFT)

/* TSU B0_SCRR Register Bit Definitions ******************************/

#define TSU_B0_SCRR_OUT12BIT_TS_SHIFT           (0)      /* Bits 0-11: Out12Bit Ts */
#define TSU_B0_SCRR_OUT12BIT_TS_MASK            (0xfff << TSU_B0_SCRR_OUT12BIT_TS_SHIFT)

/* TSU B0_SICR Register Bit Definitions ******************************/

#define TSU_B0_SICR_ADCLR                       (1 << 0)  /* Adclr */

#define TSU_B0_SICR_CMPCLR                      (1 << 1)  /* Cmpclr */

/* TSU B0_SIER Register Bit Definitions ******************************/

#define TSU_B0_SIER_ADIE                        (1 << 0)  /* Adie */

#define TSU_B0_SIER_CMPIE                       (1 << 1)  /* Cmpie */

/* TSU B0_SISR Register Bit Definitions ******************************/

#define TSU_B0_SISR_ADF                         (1 << 0)  /* Adf */

#define TSU_B0_SISR_CMPF                        (1 << 1)  /* Cmpf */

/* TSU B0_SOSR1 Register Bit Definitions *****************************/

#define TSU_B0_SOSR1_ADCT_SHIFT                 (0)      /* Bits 0-1: Adct */
#define TSU_B0_SOSR1_ADCT_MASK                  (0x3 << TSU_B0_SOSR1_ADCT_SHIFT)

#define TSU_B0_SOSR1_TRGE                       (1 << 3)  /* Trge */

#define TSU_B0_SOSR1_ADCS                       (1 << 4)  /* Adcs */

#define TSU_B0_SOSR1_OUTSEL                     (1 << 9)  /* Outsel */

/* TSU B0_SSR Register Bit Definitions *******************************/

#define TSU_B0_SSR_CONV                         (1 << 0)  /* Conv */

/* TSU B0_SSUSR Register Bit Definitions *****************************/

#define TSU_B0_SSUSR_EN_TS                      (1 << 0)  /* En Ts */

/* TSU B0_SSUSR_ADC Register Bit Definitions *************************/

#define TSU_B0_SSUSR_ADC_PD_TS                  (1 << 1)  /* Pd Ts */

/* TSU B0_SSUSR_SOC Register Bit Definitions *************************/

#define TSU_B0_SSUSR_SOC_TS_EN                  (1 << 2)  /* Ts En */

/* TSU B0_STRGR Register Bit Definitions *****************************/

#define TSU_B0_STRGR_ADST                       (1 << 0)  /* Adst */

/* TSU B0_ULSR Register Bit Definitions ******************************/

#define TSU_B0_ULSR_ULIM_SHIFT                  (0)      /* Bits 0-11: Ulim */
#define TSU_B0_ULSR_ULIM_MASK                   (0xfff << TSU_B0_ULSR_ULIM_SHIFT)

/* TSU Channel definitions */
#define RZV_TSU_CHANNEL_0          0
#define RZV_TSU_CHANNEL_1          1

/* Maximum number of TSU channels */
#define RZV_TSU_MAX_CHANNELS       2

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_TSU_H */
