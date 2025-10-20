/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_gpt_pins.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT_PINS_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT_PINS_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include "ra_pinmap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GPT Channel A Output Pin Definitions (GTIOCA) - default options */
#define GPIO_GPT0_A                    GPIO_GTIOC0A_1      /* P2.11 */
#define GPIO_GPT1_A                    GPIO_GTIOC10A_1     /* P1.9 */
#define GPIO_GPT2_A                    GPIO_GTIOC11A_1     /* P7.11 */
#define GPIO_GPT3_A                    GPIO_GTIOC12A_1     /* P7.8 - TBD */
#define GPIO_GPT4_A                    GPIO_GTIOC13A_1     /* P5.2 - TBD */
#define GPIO_GPT5_A                    GPIO_GTIOC14A_1     /* P5.11 - TBD */
#define GPIO_GPT6_A                    GPIO_GTIOC15A_1     /* P7.15 - TBD */
#define GPIO_GPT7_A                    GPIO_GTIOC16A_1     /* P6.11 - TBD */
#define GPIO_GPT8_A                    GPIO_GTIOC17A_1     /* P6.9 - TBD */
#define GPIO_GPT9_A                    GPIO_GTIOC30A_1     /* P1.12 - TBD */
#define GPIO_GPT10_A                   GPIO_GTIOC31A_1     /* P8.13 - TBD */
#define GPIO_GPT11_A                   GPIO_GTIOC32A_1     /* P9.4 - TBD */
#define GPIO_GPT12_A                   GPIO_GTIOC33A_1     /* P9.5 - TBD */
#define GPIO_GPT13_A                   GPIO_GTIOC34A_1     /* P8.14 - TBD */

/* GPT Channel B Output Pin Definitions (GTIOCB) - default options */
#define GPIO_GPT0_B                    GPIO_GTIOC0B_1      /* P2.10 */
#define GPIO_GPT1_B                    GPIO_GTIOC10B_1     /* P1.8 */
#define GPIO_GPT2_B                    GPIO_GTIOC11B_1     /* P7.10 */
#define GPIO_GPT3_B                    GPIO_GTIOC12B_1     /* P7.9 - TBD */
#define GPIO_GPT4_B                    GPIO_GTIOC13B_1     /* P5.1 - TBD */
#define GPIO_GPT5_B                    GPIO_GTIOC14B_1     /* P5.10 - TBD */
#define GPIO_GPT6_B                    GPIO_GTIOC15B_1     /* P7.14 - TBD */
#define GPIO_GPT7_B                    GPIO_GTIOC16B_1     /* P6.10 - TBD */
#define GPIO_GPT8_B                    GPIO_GTIOC17B_1     /* P6.8 - TBD */
#define GPIO_GPT9_B                    GPIO_GTIOC30B_1     /* P1.11 - TBD */
#define GPIO_GPT10_B                   GPIO_GTIOC31B_1     /* P8.12 - TBD */
#define GPIO_GPT11_B                   GPIO_GTIOC32B_1     /* P9.6 - TBD */
#define GPIO_GPT12_B                   GPIO_GTIOC33B_1     /* P9.7 - TBD */
#define GPIO_GPT13_B                   GPIO_GTIOC34B_1     /* P8.15 - TBD */

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT_PINS_H */
