/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_scifa.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SCIFA_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SCIFA_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SCIFA Base Addresses **************************************************/

#ifndef RZV_SCIFA0_BASE
#  define RZV_SCIFA0_BASE             0x11C01400
#endif
#ifndef RZV_SCIFA_BASE
#  define RZV_SCIFA_BASE              RZV_SCIFA0_BASE
#endif

/* SCIFA Register Offsets *************************************************/

#define RZV_SCIFA_SMR_OFFSET                             0x0000  /* SMR */
#define RZV_SCIFA_MDDR_OFFSET                            0x0002  /* MDDR */
#define RZV_SCIFA_BRR_OFFSET                             0x0003  /* BRR */
#define RZV_SCIFA_SCR_OFFSET                             0x0005  /* SCR */
#define RZV_SCIFA_FSR_OFFSET                             0x0008  /* FSR */
#define RZV_SCIFA_FRDR_OFFSET                            0x000A  /* FRDR */
#define RZV_SCIFA_FCR_OFFSET                             0x000C  /* FCR */
#define RZV_SCIFA_FDR_OFFSET                             0x000E  /* FDR */
#define RZV_SCIFA_SPTR_OFFSET                            0x0010  /* SPTR */
#define RZV_SCIFA_LSR_OFFSET                             0x0012  /* LSR */
#define RZV_SCIFA_SEMR_OFFSET                            0x0014  /* SEMR */
#define RZV_SCIFA_FTCR_OFFSET                            0x0016  /* FTCR */

/* SCIFA Register Addresses ************************************************/

#define RZV_SCIFA_SMR                                (RZV_SCIFA_BASE + RZV_SCIFA_SMR_OFFSET)
#define RZV_SCIFA_MDDR                               (RZV_SCIFA_BASE + RZV_SCIFA_MDDR_OFFSET)
#define RZV_SCIFA_BRR                                (RZV_SCIFA_BASE + RZV_SCIFA_BRR_OFFSET)
#define RZV_SCIFA_SCR                                (RZV_SCIFA_BASE + RZV_SCIFA_SCR_OFFSET)
#define RZV_SCIFA_FSR                                (RZV_SCIFA_BASE + RZV_SCIFA_FSR_OFFSET)
#define RZV_SCIFA_FRDR                               (RZV_SCIFA_BASE + RZV_SCIFA_FRDR_OFFSET)
#define RZV_SCIFA_FCR                                (RZV_SCIFA_BASE + RZV_SCIFA_FCR_OFFSET)
#define RZV_SCIFA_FDR                                (RZV_SCIFA_BASE + RZV_SCIFA_FDR_OFFSET)
#define RZV_SCIFA_SPTR                               (RZV_SCIFA_BASE + RZV_SCIFA_SPTR_OFFSET)
#define RZV_SCIFA_LSR                                (RZV_SCIFA_BASE + RZV_SCIFA_LSR_OFFSET)
#define RZV_SCIFA_SEMR                               (RZV_SCIFA_BASE + RZV_SCIFA_SEMR_OFFSET)
#define RZV_SCIFA_FTCR                               (RZV_SCIFA_BASE + RZV_SCIFA_FTCR_OFFSET)

/* SCIFA BRR Register Bit Definitions ********************************/

#define SCIFA_BRR_BRR_SHIFT                     (0)      /* Bits 0-7: Brr */
#define SCIFA_BRR_BRR_MASK                      (0xff << SCIFA_BRR_BRR_SHIFT)

/* SCIFA FCR Register Bit Definitions ********************************/

#define SCIFA_FCR_LOOP                          (1 << 0)  /* Loop */

#define SCIFA_FCR_RFRST                         (1 << 1)  /* Rfrst */

#define SCIFA_FCR_TFRST                         (1 << 2)  /* Tfrst */

#define SCIFA_FCR_TTRG_SHIFT                    (4)      /* Bits 4-5: Ttrg */
#define SCIFA_FCR_TTRG_MASK                     (0x3 << SCIFA_FCR_TTRG_SHIFT)

#define SCIFA_FCR_RTRG_SHIFT                    (6)      /* Bits 6-7: Rtrg */
#define SCIFA_FCR_RTRG_MASK                     (0x3 << SCIFA_FCR_RTRG_SHIFT)

/* SCIFA FDR Register Bit Definitions ********************************/

#define SCIFA_FDR_R_SHIFT                       (0)      /* Bits 0-4: R */
#define SCIFA_FDR_R_MASK                        (0x1f << SCIFA_FDR_R_SHIFT)

#define SCIFA_FDR_T_SHIFT                       (8)      /* Bits 8-12: T */
#define SCIFA_FDR_T_MASK                        (0x1f << SCIFA_FDR_T_SHIFT)

/* SCIFA FRDR Register Bit Definitions *******************************/

#define SCIFA_FRDR_FRDR_SHIFT                   (0)      /* Bits 0-7: Frdr */
#define SCIFA_FRDR_FRDR_MASK                    (0xff << SCIFA_FRDR_FRDR_SHIFT)

/* SCIFA FSR Register Bit Definitions ********************************/

#define SCIFA_FSR_DR                            (1 << 0)  /* Dr */

#define SCIFA_FSR_RDF                           (1 << 1)  /* Rdf */

#define SCIFA_FSR_PER                           (1 << 2)  /* Per */

#define SCIFA_FSR_FER                           (1 << 3)  /* Fer */

#define SCIFA_FSR_BRK                           (1 << 4)  /* Brk */

#define SCIFA_FSR_TDFE                          (1 << 5)  /* Tdfe */

#define SCIFA_FSR_TEND                          (1 << 6)  /* Tend */

#define SCIFA_FSR_ER                            (1 << 7)  /* Er */

/* SCIFA FTCR Register Bit Definitions *******************************/

#define SCIFA_FTCR_TFTC_SHIFT                   (0)      /* Bits 0-4: Tftc */
#define SCIFA_FTCR_TFTC_MASK                    (0x1f << SCIFA_FTCR_TFTC_SHIFT)

#define SCIFA_FTCR_TTRGS                        (1 << 7)  /* Ttrgs */

#define SCIFA_FTCR_RFTC_SHIFT                   (8)      /* Bits 8-12: Rftc */
#define SCIFA_FTCR_RFTC_MASK                    (0x1f << SCIFA_FTCR_RFTC_SHIFT)

#define SCIFA_FTCR_RTRGS                        (1 << 15)  /* Rtrgs */

/* SCIFA FTDR Register Bit Definitions *******************************/

#define SCIFA_FTDR_FTDR_SHIFT                   (0)      /* Bits 0-7: Ftdr */
#define SCIFA_FTDR_FTDR_MASK                    (0xff << SCIFA_FTDR_FTDR_SHIFT)

/* SCIFA LSR Register Bit Definitions ********************************/

#define SCIFA_LSR_ORER                          (1 << 0)  /* Orer */

#define SCIFA_LSR_FER_SHIFT                     (2)      /* Bits 2-5: Fer */
#define SCIFA_LSR_FER_MASK                      (0xf << SCIFA_LSR_FER_SHIFT)

#define SCIFA_LSR_PER_SHIFT                     (8)      /* Bits 8-11: Per */
#define SCIFA_LSR_PER_MASK                      (0xf << SCIFA_LSR_PER_SHIFT)

/* SCIFA MDDR Register Bit Definitions *******************************/

#define SCIFA_MDDR_MDDR_SHIFT                   (0)      /* Bits 0-7: Mddr */
#define SCIFA_MDDR_MDDR_MASK                    (0xff << SCIFA_MDDR_MDDR_SHIFT)

/* SCIFA SCR Register Bit Definitions ********************************/

#define SCIFA_SCR_CKE_SHIFT                     (0)      /* Bits 0-1: Cke */
#define SCIFA_SCR_CKE_MASK                      (0x3 << SCIFA_SCR_CKE_SHIFT)

#define SCIFA_SCR_TEIE                          (1 << 2)  /* Teie */

#define SCIFA_SCR_REIE                          (1 << 3)  /* Reie */

#define SCIFA_SCR_RE                            (1 << 4)  /* Re */

#define SCIFA_SCR_TE                            (1 << 5)  /* Te */

#define SCIFA_SCR_RIE                           (1 << 6)  /* Rie */

#define SCIFA_SCR_TIE                           (1 << 7)  /* Tie */

/* SCIFA SEMR Register Bit Definitions *******************************/

#define SCIFA_SEMR_ABCS0                        (1 << 0)  /* Abcs0 */

#define SCIFA_SEMR_NFEN                         (1 << 2)  /* Nfen */

#define SCIFA_SEMR_DIR                          (1 << 3)  /* Dir */

#define SCIFA_SEMR_MDDRS                        (1 << 4)  /* Mddrs */

#define SCIFA_SEMR_BRME                         (1 << 5)  /* Brme */

#define SCIFA_SEMR_BGDM                         (1 << 7)  /* Bgdm */

/* SCIFA SMR Register Bit Definitions ********************************/

#define SCIFA_SMR_CKS_SHIFT                     (0)      /* Bits 0-1: Cks */
#define SCIFA_SMR_CKS_MASK                      (0x3 << SCIFA_SMR_CKS_SHIFT)

#define SCIFA_SMR_STOP                          (1 << 3)  /* Stop */

#define SCIFA_SMR_PM                            (1 << 4)  /* Pm */

#define SCIFA_SMR_PE                            (1 << 5)  /* Pe */

#define SCIFA_SMR_CHR                           (1 << 6)  /* Chr */

/* SCIFA SPTR Register Bit Definitions *******************************/

#define SCIFA_SPTR_SPB2DT                       (1 << 0)  /* Spb2Dt */

#define SCIFA_SPTR_SPB2IO                       (1 << 1)  /* Spb2Io */

/* SCIFA Channel definitions */
#define RZV_SCIFA_CHANNEL_0        0

/* Maximum number of SCIFA channels */
#define RZV_SCIFA_MAX_CHANNELS     1

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SCIFA_H */
