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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SCIF_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SCIF_H

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
#ifndef RZV_SCIF_BASE
#  define RZV_SCIF_BASE              RZV_SCIFA0_BASE
#endif

/* SCIFA Register Offsets *************************************************/

/* Offsets verified against scifa_iodefine.h (R9A09G057H). MDDR and BRR
 * share offset 0x02; MDDRS bit in SEMR selects which is mapped.
 */

#define RZV_SCIF_SMR_OFFSET                             0x0000  /* SMR  (u16) */
#define RZV_SCIF_MDDR_OFFSET                            0x0002  /* MDDR (u8, MDDRS=1) */
#define RZV_SCIF_BRR_OFFSET                             0x0002  /* BRR  (u8, MDDRS=0) */
#define RZV_SCIF_SCR_OFFSET                             0x0004  /* SCR  (u16) */
#define RZV_SCIF_FTDR_OFFSET                            0x0006  /* FTDR (u8, write-only) */
#define RZV_SCIF_FSR_OFFSET                             0x0008  /* FSR  (u16) */
#define RZV_SCIF_FRDR_OFFSET                            0x000A  /* FRDR (u8, read-only) */
#define RZV_SCIF_FCR_OFFSET                             0x000C  /* FCR  (u16) */
#define RZV_SCIF_FDR_OFFSET                             0x000E  /* FDR  (u16) */
#define RZV_SCIF_SPTR_OFFSET                            0x0010  /* SPTR (u16) */
#define RZV_SCIF_LSR_OFFSET                             0x0012  /* LSR  (u16) */
#define RZV_SCIF_SEMR_OFFSET                            0x0014  /* SEMR (u8) */
#define RZV_SCIF_FTCR_OFFSET                            0x0016  /* FTCR (u16) */

/* SCIFA Register Addresses ************************************************/

#define RZV_SCIF_SMR                                (RZV_SCIF_BASE + RZV_SCIF_SMR_OFFSET)
#define RZV_SCIF_MDDR                               (RZV_SCIF_BASE + RZV_SCIF_MDDR_OFFSET)
#define RZV_SCIF_BRR                                (RZV_SCIF_BASE + RZV_SCIF_BRR_OFFSET)
#define RZV_SCIF_SCR                                (RZV_SCIF_BASE + RZV_SCIF_SCR_OFFSET)
#define RZV_SCIF_FSR                                (RZV_SCIF_BASE + RZV_SCIF_FSR_OFFSET)
#define RZV_SCIF_FRDR                               (RZV_SCIF_BASE + RZV_SCIF_FRDR_OFFSET)
#define RZV_SCIF_FCR                                (RZV_SCIF_BASE + RZV_SCIF_FCR_OFFSET)
#define RZV_SCIF_FDR                                (RZV_SCIF_BASE + RZV_SCIF_FDR_OFFSET)
#define RZV_SCIF_SPTR                               (RZV_SCIF_BASE + RZV_SCIF_SPTR_OFFSET)
#define RZV_SCIF_LSR                                (RZV_SCIF_BASE + RZV_SCIF_LSR_OFFSET)
#define RZV_SCIF_SEMR                               (RZV_SCIF_BASE + RZV_SCIF_SEMR_OFFSET)
#define RZV_SCIF_FTCR                               (RZV_SCIF_BASE + RZV_SCIF_FTCR_OFFSET)

/* SCIFA BRR Register Bit Definitions ********************************/

#define SCIF_BRR_BRR_SHIFT                     (0)      /* Bits 0-7: Brr */
#define SCIF_BRR_BRR_MASK                      (0xff << SCIF_BRR_BRR_SHIFT)

/* SCIFA FCR Register Bit Definitions ********************************/

#define SCIF_FCR_LOOP                          (1 << 0)  /* Loop */

#define SCIF_FCR_RFRST                         (1 << 1)  /* Rfrst */

#define SCIF_FCR_TFRST                         (1 << 2)  /* Tfrst */

#define SCIF_FCR_TTRG_SHIFT                    (4)      /* Bits 4-5: Ttrg */
#define SCIF_FCR_TTRG_MASK                     (0x3 << SCIF_FCR_TTRG_SHIFT)

#define SCIF_FCR_RTRG_SHIFT                    (6)      /* Bits 6-7: Rtrg */
#define SCIF_FCR_RTRG_MASK                     (0x3 << SCIF_FCR_RTRG_SHIFT)

/* SCIFA FDR Register Bit Definitions ********************************/

#define SCIF_FDR_R_SHIFT                       (0)      /* Bits 0-4: R */
#define SCIF_FDR_R_MASK                        (0x1f << SCIF_FDR_R_SHIFT)

#define SCIF_FDR_T_SHIFT                       (8)      /* Bits 8-12: T */
#define SCIF_FDR_T_MASK                        (0x1f << SCIF_FDR_T_SHIFT)

/* SCIFA FRDR Register Bit Definitions *******************************/

#define SCIF_FRDR_FRDR_SHIFT                   (0)      /* Bits 0-7: Frdr */
#define SCIF_FRDR_FRDR_MASK                    (0xff << SCIF_FRDR_FRDR_SHIFT)

/* SCIFA FSR Register Bit Definitions ********************************/

#define SCIF_FSR_DR                            (1 << 0)  /* Dr (W0C) */

#define SCIF_FSR_RDF                           (1 << 1)  /* Rdf (W0C) */

/* NOTE: FSR.PER (bit 2) and FSR.FER (bit 3) are READ-ONLY in CMSIS
 * (__IM uint16_t). HW clears them only when the errored byte is drained
 * from FRDR. Writing 0 to these positions in a W0C clear pattern is a
 * silent no-op — code must read FRDR to discard the bad byte.
 */
#define SCIF_FSR_PER                           (1 << 2)  /* Per (RO; cleared by FRDR read) */

#define SCIF_FSR_FER                           (1 << 3)  /* Fer (RO; cleared by FRDR read) */

#define SCIF_FSR_BRK                           (1 << 4)  /* Brk */

#define SCIF_FSR_TDFE                          (1 << 5)  /* Tdfe */

#define SCIF_FSR_TEND                          (1 << 6)  /* Tend */

#define SCIF_FSR_ER                            (1 << 7)  /* Er */

/* SCIFA FTCR Register Bit Definitions *******************************/

#define SCIF_FTCR_TFTC_SHIFT                   (0)      /* Bits 0-4: Tftc */
#define SCIF_FTCR_TFTC_MASK                    (0x1f << SCIF_FTCR_TFTC_SHIFT)

#define SCIF_FTCR_TTRGS                        (1 << 7)  /* Ttrgs */

#define SCIF_FTCR_RFTC_SHIFT                   (8)      /* Bits 8-12: Rftc */
#define SCIF_FTCR_RFTC_MASK                    (0x1f << SCIF_FTCR_RFTC_SHIFT)

#define SCIF_FTCR_RTRGS                        (1 << 15)  /* Rtrgs */

/* SCIFA FTDR Register Bit Definitions *******************************/

#define SCIF_FTDR_FTDR_SHIFT                   (0)      /* Bits 0-7: Ftdr */
#define SCIF_FTDR_FTDR_MASK                    (0xff << SCIF_FTDR_FTDR_SHIFT)

/* SCIFA LSR Register Bit Definitions ********************************/

#define SCIF_LSR_ORER                          (1 << 0)  /* Orer (W0C) */

/* NOTE: LSR.FER[5:2] and LSR.PER[11:8] are READ-ONLY counters in CMSIS
 * (__IM uint16_t). Do NOT attempt to write/clear them — HW updates them
 * as bytes with errors flow through the RX FIFO. Provided for status
 * inspection only.
 */
#define SCIF_LSR_FER_SHIFT                     (2)      /* Bits 2-5: Fer (RO counter) */
#define SCIF_LSR_FER_MASK                      (0xf << SCIF_LSR_FER_SHIFT)

#define SCIF_LSR_PER_SHIFT                     (8)      /* Bits 8-11: Per (RO counter) */
#define SCIF_LSR_PER_MASK                      (0xf << SCIF_LSR_PER_SHIFT)

/* SCIFA MDDR Register Bit Definitions *******************************/

#define SCIF_MDDR_MDDR_SHIFT                   (0)      /* Bits 0-7: Mddr */
#define SCIF_MDDR_MDDR_MASK                    (0xff << SCIF_MDDR_MDDR_SHIFT)

/* SCIFA SCR Register Bit Definitions ********************************/

#define SCIF_SCR_CKE_SHIFT                     (0)      /* Bits 0-1: Cke */
#define SCIF_SCR_CKE_MASK                      (0x3 << SCIF_SCR_CKE_SHIFT)

#define SCIF_SCR_TEIE                          (1 << 2)  /* Teie */

#define SCIF_SCR_REIE                          (1 << 3)  /* Reie */

#define SCIF_SCR_RE                            (1 << 4)  /* Re */

#define SCIF_SCR_TE                            (1 << 5)  /* Te */

#define SCIF_SCR_RIE                           (1 << 6)  /* Rie */

#define SCIF_SCR_TIE                           (1 << 7)  /* Tie */

/* SCIFA SEMR Register Bit Definitions *******************************/

#define SCIF_SEMR_ABCS0                        (1 << 0)  /* Abcs0 */

#define SCIF_SEMR_NFEN                         (1 << 2)  /* Nfen */

#define SCIF_SEMR_DIR                          (1 << 3)  /* Dir */

#define SCIF_SEMR_MDDRS                        (1 << 4)  /* Mddrs */

#define SCIF_SEMR_BRME                         (1 << 5)  /* Brme */

#define SCIF_SEMR_BGDM                         (1 << 7)  /* Bgdm */

/* SCIFA SMR Register Bit Definitions ********************************/

#define SCIF_SMR_CKS_SHIFT                     (0)      /* Bits 0-1: Cks */
#define SCIF_SMR_CKS_MASK                      (0x3 << SCIF_SMR_CKS_SHIFT)

#define SCIF_SMR_STOP                          (1 << 3)  /* Stop */

#define SCIF_SMR_PM                            (1 << 4)  /* Pm */

#define SCIF_SMR_PE                            (1 << 5)  /* Pe */

#define SCIF_SMR_CHR                           (1 << 6)  /* Chr */

/* SCIFA SPTR Register Bit Definitions *******************************/

#define SCIF_SPTR_SPB2DT                       (1 << 0)  /* Spb2Dt */

#define SCIF_SPTR_SPB2IO                       (1 << 1)  /* Spb2Io */

/* SCIFA Channel definitions */
#define RZV_SCIF_CHANNEL_0        0

/* Maximum number of SCIFA channels */
#define RZV_SCIF_MAX_CHANNELS     1

/* FCR TTRG field encoding (bits 5:4): TX-FIFO-empty trigger.
 *   0 = 8 bytes free, 1 = 4 bytes free, 2 = 2 bytes free, 3 = 0 bytes free
 */
#define SCIF_FCR_TTRG_8                        0
#define SCIF_FCR_TTRG_4                        1
#define SCIF_FCR_TTRG_2                        2
#define SCIF_FCR_TTRG_0                        3

/* FCR RTRG field encoding (bits 7:6): RX-FIFO-full trigger.
 *   0 = 1 byte, 1 = 4 bytes, 2 = 8 bytes, 3 = 14 bytes
 */
#define SCIF_FCR_RTRG_1                        0
#define SCIF_FCR_RTRG_4                        1
#define SCIF_FCR_RTRG_8                        2
#define SCIF_FCR_RTRG_14                       3

/* SCIFA on RZ/V2H has no modem-control-enable bit in FCR (unlike SCI).
 * Hardware flow control (RTS/CTS) is not supported on this peripheral.
 * Any code path that needs MCE semantics is a porting bug — emit a
 * compile error from the driver TU if flow-control configs are set.
 */

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SCIF_H */
