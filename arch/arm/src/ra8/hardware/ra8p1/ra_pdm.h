/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_pdm.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_PDM_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_PDM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* PDM Base Address */
#ifndef R_PDM_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_PDM_BASE           0x40256000
#else
#define R_PDM_BASE           0x50256000
#endif
#endif

/* PDM Register Offsets */

#define R_PDM_PDCSTRTR_OFFSET                     0x00000000  /* Channel Software Start Trigger Register */
#define R_PDM_PDCSTPTR_OFFSET                     0x00000004  /* Channel Software Stop Trigger Register */
#define R_PDM_PDCCHGTR_OFFSET                     0x00000008  /* Channel Software Change Trigger Register */
#define R_PDM_PDCICR_OFFSET                       0x0000000c  /* Channel Interrupt Control Register */
#define R_PDM_PDCSR_OFFSET                        0x00000010  /* Channel Status Register */
#define R_PDM_PDCSCR_OFFSET                       0x00000014  /* Channel Status Clear Register */
#define R_PDM_PDCSDCR_OFFSET                      0x00000020  /* Channel Sound Detection Control Register */
#define R_PDM_PDCDRCR_OFFSET                      0x00000024  /* Channel Data Read Control Register  */
#define R_PDM_PDCDCR_OFFSET                       0x00000028  /* Channel Data Clear Register */
#define R_PDM_PDVR_OFFSET                         0x00000080  /* Version Register */
/* CH[%s] Registers () */
#define R_PDM_CH_OFFSET(m)                        (0x00000100 + ((m) * 0x00000100))  /* PDM Channel-Specific Registers */

/* PDM Register Addresses */

#define R_PDM_PDCSTRTR                            (R_PDM_BASE + R_PDM_PDCSTRTR_OFFSET)
#define R_PDM_PDCSTPTR                            (R_PDM_BASE + R_PDM_PDCSTPTR_OFFSET)
#define R_PDM_PDCCHGTR                            (R_PDM_BASE + R_PDM_PDCCHGTR_OFFSET)
#define R_PDM_PDCICR                              (R_PDM_BASE + R_PDM_PDCICR_OFFSET)
#define R_PDM_PDCSR                               (R_PDM_BASE + R_PDM_PDCSR_OFFSET)
#define R_PDM_PDCSCR                              (R_PDM_BASE + R_PDM_PDCSCR_OFFSET)
#define R_PDM_PDCSDCR                             (R_PDM_BASE + R_PDM_PDCSDCR_OFFSET)
#define R_PDM_PDCDRCR                             (R_PDM_BASE + R_PDM_PDCDRCR_OFFSET)
#define R_PDM_PDCDCR                              (R_PDM_BASE + R_PDM_PDCDCR_OFFSET)
#define R_PDM_PDVR                                (R_PDM_BASE + R_PDM_PDVR_OFFSET)
#define R_PDM_CH(m)                               (R_PDM_BASE + R_PDM_CH_OFFSET(m))

/* Register bit definitions */
/* PDCSTRTR Register bit definitions */
#define R_PDM_PDCSTRTR_STRTRG0                    (1 << 0)  /* Channel 0 start trigger */

#define R_PDM_PDCSTRTR_STRTRG1                    (1 << 1)  /* Channel 1 start trigger */

#define R_PDM_PDCSTRTR_STRTRG2                    (1 << 2)  /* Channel 2 start trigger */

/* PDCSTPTR Register bit definitions */
#define R_PDM_PDCSTPTR_STPTRG0                    (1 << 0)  /* Channel 0 stop trigger */

#define R_PDM_PDCSTPTR_STPTRG1                    (1 << 1)  /* Channel 1 stop trigger */

#define R_PDM_PDCSTPTR_STPTRG2                    (1 << 2)  /* Channel 2 stop trigger */

/* PDCCHGTR Register bit definitions */
#define R_PDM_PDCCHGTR_CHGTRG0                    (1 << 0)  /* Channel 0 change trigger */

#define R_PDM_PDCCHGTR_CHGTRG1                    (1 << 1)  /* Channel 1 change trigger */

#define R_PDM_PDCCHGTR_CHGTRG2                    (1 << 2)  /* Channel 2 change trigger */

/* PDCICR Register bit definitions */
#define R_PDM_PDCICR_ISDE0                        (1 << 8)  /* Channel 0 sound detection interrupt enable bit */

#define R_PDM_PDCICR_ISDE1                        (1 << 9)  /* Channel 1 sound detection interrupt enable bit */

#define R_PDM_PDCICR_ISDE2                        (1 << 10)  /* Channel 2 sound detection interrupt enable bit */

#define R_PDM_PDCICR_IDRE0                        (1 << 16)  /* Channel 0 data reception interrupt enable bit */

#define R_PDM_PDCICR_IDRE1                        (1 << 17)  /* Channel 1 data reception interrupt enable bit */

#define R_PDM_PDCICR_IDRE2                        (1 << 18)  /* Channel 2 data reception interrupt enable bit */

#define R_PDM_PDCICR_IEDE0                        (1 << 24)  /* Channel 0 error detection interrupt enable bit */

#define R_PDM_PDCICR_IEDE1                        (1 << 25)  /* Channel 1 error detection interrupt enable bit */

#define R_PDM_PDCICR_IEDE2                        (1 << 26)  /* Channel 2 error detection interrupt enable bit */

/* PDCSR Register bit definitions */
#define R_PDM_PDCSR_STATE0                        (1 << 0)  /* Channel 0 state */

#define R_PDM_PDCSR_STATE1                        (1 << 1)  /* Channel 1 state */

#define R_PDM_PDCSR_STATE2                        (1 << 2)  /* Channel 2 state */

#define R_PDM_PDCSR_SDF0                          (1 << 8)  /* Channel 0 sound detection flag */

#define R_PDM_PDCSR_SDF1                          (1 << 9)  /* Channel 1 sound detection flag */

#define R_PDM_PDCSR_SDF2                          (1 << 10)  /* Channel 2 sound detection flag */

#define R_PDM_PDCSR_DRF0                          (1 << 16)  /* Channel 0 data reception flag */

#define R_PDM_PDCSR_DRF1                          (1 << 17)  /* Channel 1 data reception flag */

#define R_PDM_PDCSR_DRF2                          (1 << 18)  /* Channel 2 data reception flag */

#define R_PDM_PDCSR_EDF0                          (1 << 24)  /* Channel 0 error detection flag */

#define R_PDM_PDCSR_EDF1                          (1 << 25)  /* Channel 1 error detection flag */

#define R_PDM_PDCSR_EDF2                          (1 << 26)  /* Channel 2 error detection flag */

/* PDCSCR Register bit definitions */
#define R_PDM_PDCSCR_SDFC0                        (1 << 8)  /* Channel 0 sound detection flag clear */

#define R_PDM_PDCSCR_SDFC1                        (1 << 9)  /* Channel 1 sound detection flag clear */

#define R_PDM_PDCSCR_SDFC2                        (1 << 10)  /* Channel 2 sound detection flag clear */

/* PDCSDCR Register bit definitions */
#define R_PDM_PDCSDCR_SDE0                        (1 << 0)  /* Channel 0 sound detection enable bit */

#define R_PDM_PDCSDCR_SDE1                        (1 << 1)  /* Channel 1 sound detection enable bit */

#define R_PDM_PDCSDCR_SDE2                        (1 << 2)  /* Channel 2 sound detection enable bit */

/* PDCDRCR Register bit definitions */
#define R_PDM_PDCDRCR_DATRE0                      (1 << 0)  /* Channel 0 data read enable bit */

#define R_PDM_PDCDRCR_DATRE1                      (1 << 1)  /* Channel 1 data read enable bit */

#define R_PDM_PDCDRCR_DATRE2                      (1 << 2)  /* Channel 2 data read enable bit */

/* PDCDCR Register bit definitions */
#define R_PDM_PDCDCR_DATC0                        (1 << 0)  /* Channel 0 data clear */

#define R_PDM_PDCDCR_DATC1                        (1 << 1)  /* Channel 1 data clear */

#define R_PDM_PDCDCR_DATC2                        (1 << 2)  /* Channel 2 data clear */

/* PDVR Register bit definitions */
#define R_PDM_PDVR_VER_SHIFT                      (0)  /* Version */
#define R_PDM_PDVR_VER_MASK                       0xfff


/* Maximum number of channels */

#define PDM_MAX_CHANNELS    3

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_PDM_H */
