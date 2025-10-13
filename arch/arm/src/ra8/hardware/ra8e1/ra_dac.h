/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_dac.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DAC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DAC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* DAC Base Address */
#ifndef R_DAC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_DAC_BASE           0x40333000
#else
#define R_DAC_BASE           0x50333000
#endif
#endif

#define R_DAC_CH_BASE(ch)   (R_DAC_BASE + ((uint32_t)(ch) * R_DAC_CH_STRIDE))

/* DAC Register Offsets */

/* DADR%s Registers (0) */
#define R_DAC_DADR_OFFSET                         0x00000000  /* D/A Data Register %s */
#define R_DAC_DACR_OFFSET                         0x00000004  /* D/A Control Register */
#define R_DAC_DADPR_OFFSET                        0x00000005  /* DADRn Format Select Register */
#define R_DAC_DAADSCR_OFFSET                      0x00000006  /* D/A A/D Synchronous Start Control Register */
#define R_DAC_DAAMPCR_OFFSET                      0x00000008  /* D/A Output Amplifier Control Register */
#define R_DAC_DAASWCR_OFFSET                      0x0000001c  /* D/A Amplifier Stabilization Wait Control Register */
#define R_DAC_DAADUSR_OFFSET                      0x000010c0  /* D/A A/D Synchronous Unit Select Register */

/* DAC Register Addresses */

#define R_DAC_DADR                                (R_DAC_BASE + R_DAC_DADR_OFFSET)
#define R_DAC_DACR                                (R_DAC_BASE + R_DAC_DACR_OFFSET)
#define R_DAC_DADPR                               (R_DAC_BASE + R_DAC_DADPR_OFFSET)
#define R_DAC_DAADSCR                             (R_DAC_BASE + R_DAC_DAADSCR_OFFSET)
#define R_DAC_DAAMPCR                             (R_DAC_BASE + R_DAC_DAAMPCR_OFFSET)
#define R_DAC_DAASWCR                             (R_DAC_BASE + R_DAC_DAASWCR_OFFSET)
#define R_DAC_DAADUSR                             (R_DAC_BASE + R_DAC_DAADUSR_OFFSET)

/* Register bit definitions */
/* DADR Register bit definitions */
#define R_DAC_DADR_DADR_SHIFT                     (0)  /* D/A Data RegisterNOTE: When DADPR.DPSEL = 0, the high-order 4 bits are fixed to 0: right justified format. When DADPR.DPSEL = 1, the low-order 4 bits are fixed to 0: left justified format. */
#define R_DAC_DADR_DADR_MASK                      0xffff

/* DACR Register bit definitions */
#define R_DAC_DACR_DAOE0                          (1 << 6)  /* D/A Output Enable 0 */

#define R_DAC_DACR_DAE                            (1 << 5)  /* D/A Enable */

#define R_DAC_DACR_DAOE1                          (1 << 7)  /* D/A Output Enable 0 */

/* DADPR Register bit definitions */
#define R_DAC_DADPR_DPSEL                         (1 << 7)  /* DADRn Format Select */

/* DAADSCR Register bit definitions */
#define R_DAC_DAADSCR_DAADST                      (1 << 7)  /* D/A A/D Synchronous Conversion */

/* DAAMPCR Register bit definitions */
#define R_DAC_DAAMPCR_DAAMP0                      (1 << 6)  /* Amplifier Control 0 */

#define R_DAC_DAAMPCR_DAAMP1                      (1 << 7)  /* Amplifier Control */

/* DAASWCR Register bit definitions */
#define R_DAC_DAASWCR_DAASW0                      (1 << 6)  /* D/A Amplifier Stabilization Wait 0 and D/A internal output control */

#define R_DAC_DAASWCR_DAASW1                      (1 << 7)  /* Set the DAASW1 bit to 1 in the initialization procedure to wait for stabilization of the output amplifier of D/A channel 1. When DAASW1 is set to 1, D/A conversion operates, but the conversion result D/A is not output from channel 1. When the DAASW1 bit is 0, the stabilization wait time stops, and the D/A conversion result of channel 1 is output through the output amplifier. */

/* DAADUSR Register bit definitions */
#define R_DAC_DAADUSR_AMADSEL1                    (1 << 1)  /* A/D Unit 1 Select */

#define R_DAC_DAADUSR_AMADSEL0                    (1 << 0)  /* The DAADUSR register selects the target ADC12 unit for D/A and A/D synchronous conversions. Set bit [0] to 1 to select unit 0 as the target synchronous unit for the MCU. When setting the DAADSCR.DAADST bit to 1 for synchronous conversions, select the target unit in this register in advance. Only set the DAADUSR register while the ADCSR.ADST bit of the ADC12 is set to 0 and the DAADSCR.DAADST bit is set to 0. */


/* Maximum number of channels */

#define DAC_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DAC_H */
