/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_sci.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SCI_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SCI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SCI Base Addresses ****************************************************/

#ifndef RZV_SCI0_BASE
#  define RZV_SCI0_BASE               0x12800C00
#endif
#ifndef RZV_SCI1_BASE
#  define RZV_SCI1_BASE               0x12801000
#endif
#ifndef RZV_SCI2_BASE
#  define RZV_SCI2_BASE               0x12801400
#endif
#ifndef RZV_SCI3_BASE
#  define RZV_SCI3_BASE               0x12801800
#endif
#ifndef RZV_SCI4_BASE
#  define RZV_SCI4_BASE               0x12801C00
#endif
#ifndef RZV_SCI5_BASE
#  define RZV_SCI5_BASE               0x12802000
#endif
#ifndef RZV_SCI6_BASE
#  define RZV_SCI6_BASE               0x12802400
#endif
#ifndef RZV_SCI7_BASE
#  define RZV_SCI7_BASE               0x12802800
#endif
#ifndef RZV_SCI8_BASE
#  define RZV_SCI8_BASE               0x12802C00
#endif
#ifndef RZV_SCI9_BASE
#  define RZV_SCI9_BASE               0x12803000
#endif

/* SCI Register Offsets ***************************************************/

/* CCR%s Registers (0-4) */
#define RZV_SCI_CCR_OFFSET(m)                   (0x00000008 + ((m) * 0x00000004))  /* CCR Register %s */
/* XCR%s Registers (0-2) */
#define RZV_SCI_XCR_OFFSET(m)                   (0x00000034 + ((m) * 0x00000004))  /* XCR Register %s */
/* XSR%s Registers (0-1) */
#define RZV_SCI_XSR_OFFSET(m)                   (0x0000005C + ((m) * 0x00000004))  /* XSR Register %s */
#define RZV_SCI_RDR_OFFSET                            0x0000  /* Receive Data Register */
#define RZV_SCI_TDR_OFFSET                            0x0004  /* Transmit Data Register */
#define RZV_SCI_CCR0_OFFSET                           0x0008  /* Common Control Register 0 */
#define RZV_SCI_CCR1_OFFSET                           0x000C  /* Common Control Register 1 */
#define RZV_SCI_CCR2_OFFSET                           0x0010  /* Common Control Register 2 */
#define RZV_SCI_CCR3_OFFSET                           0x0014  /* Common Control Register 3 */
#define RZV_SCI_CCR4_OFFSET                           0x0018  /* Common Control Register 4 */
#define RZV_SCI_CESR_OFFSET                           0x001C  /* Communication Enable Status Register */
#define RZV_SCI_HCR_OFFSET                            0x001E  /* Half data communication Control Register */
#define RZV_SCI_ICR_OFFSET                            0x0020  /* Simple I2C Control Register */
#define RZV_SCI_FCR_OFFSET                            0x0024  /* FIFO Control Register */
#define RZV_SCI_DCR_OFFSET                            0x0030  /* Driver Control Register */
#define RZV_SCI_XCR0_OFFSET                           0x0034  /* Simple-LIN(SCIX) Control Register 0 */
#define RZV_SCI_XCR1_OFFSET                           0x0038  /* Simple-LIN(SCIX) Control Register 1 */
#define RZV_SCI_XCR2_OFFSET                           0x003C  /* Simple-LIN(SCIX) Control Register 2 */
#define RZV_SCI_CSR_OFFSET                            0x0048  /* Common Status Register */
#define RZV_SCI_ISR_OFFSET                            0x004C  /* Simple I2C Status Register */
#define RZV_SCI_FRSR_OFFSET                           0x0050  /* FIFO Receive Status Register */
#define RZV_SCI_FTSR_OFFSET                           0x0054  /* FIFO Transmit Status Register */
#define RZV_SCI_XSR0_OFFSET                           0x005C  /* Simple-LIN(SCIX) Status Register 0 */
#define RZV_SCI_XSR1_OFFSET                           0x0060  /* Simple-LIN(SCIX) Status Register 1 */
#define RZV_SCI_CFCLR_OFFSET                          0x0068  /* Common Flag Clear Register */
#define RZV_SCI_ICFCLR_OFFSET                         0x006C  /* Simple I2C Flag Clear Register */
#define RZV_SCI_FFCLR_OFFSET                          0x0070  /* FIFO Flag Clear Register */
#define RZV_SCI_XFCLR_OFFSET                          0x0078  /* Simple-LIN(SCIX) Flag Clear Register */

/* SCI Register Addresses **************************************************/

#define RZV_SCI_CCR(ch,m)                            (RZV_SCI##ch##_BASE + RZV_SCI_CCR_OFFSET(m))
#define RZV_SCI_XCR(ch,m)                            (RZV_SCI##ch##_BASE + RZV_SCI_XCR_OFFSET(m))
#define RZV_SCI_XSR(ch,m)                            (RZV_SCI##ch##_BASE + RZV_SCI_XSR_OFFSET(m))
#define RZV_SCI_RDR(ch)                              (RZV_SCI##ch##_BASE + RZV_SCI_RDR_OFFSET)
#define RZV_SCI_TDR(ch)                              (RZV_SCI##ch##_BASE + RZV_SCI_TDR_OFFSET)
#define RZV_SCI_CCR0(ch)                             (RZV_SCI##ch##_BASE + RZV_SCI_CCR0_OFFSET)
#define RZV_SCI_CCR1(ch)                             (RZV_SCI##ch##_BASE + RZV_SCI_CCR1_OFFSET)
#define RZV_SCI_CCR2(ch)                             (RZV_SCI##ch##_BASE + RZV_SCI_CCR2_OFFSET)
#define RZV_SCI_CCR3(ch)                             (RZV_SCI##ch##_BASE + RZV_SCI_CCR3_OFFSET)
#define RZV_SCI_CCR4(ch)                             (RZV_SCI##ch##_BASE + RZV_SCI_CCR4_OFFSET)
#define RZV_SCI_CESR(ch)                             (RZV_SCI##ch##_BASE + RZV_SCI_CESR_OFFSET)
#define RZV_SCI_HCR(ch)                              (RZV_SCI##ch##_BASE + RZV_SCI_HCR_OFFSET)
#define RZV_SCI_ICR(ch)                              (RZV_SCI##ch##_BASE + RZV_SCI_ICR_OFFSET)
#define RZV_SCI_FCR(ch)                              (RZV_SCI##ch##_BASE + RZV_SCI_FCR_OFFSET)
#define RZV_SCI_DCR(ch)                              (RZV_SCI##ch##_BASE + RZV_SCI_DCR_OFFSET)
#define RZV_SCI_XCR0(ch)                             (RZV_SCI##ch##_BASE + RZV_SCI_XCR0_OFFSET)
#define RZV_SCI_XCR1(ch)                             (RZV_SCI##ch##_BASE + RZV_SCI_XCR1_OFFSET)
#define RZV_SCI_XCR2(ch)                             (RZV_SCI##ch##_BASE + RZV_SCI_XCR2_OFFSET)
#define RZV_SCI_CSR(ch)                              (RZV_SCI##ch##_BASE + RZV_SCI_CSR_OFFSET)
#define RZV_SCI_ISR(ch)                              (RZV_SCI##ch##_BASE + RZV_SCI_ISR_OFFSET)
#define RZV_SCI_FRSR(ch)                             (RZV_SCI##ch##_BASE + RZV_SCI_FRSR_OFFSET)
#define RZV_SCI_FTSR(ch)                             (RZV_SCI##ch##_BASE + RZV_SCI_FTSR_OFFSET)
#define RZV_SCI_XSR0(ch)                             (RZV_SCI##ch##_BASE + RZV_SCI_XSR0_OFFSET)
#define RZV_SCI_XSR1(ch)                             (RZV_SCI##ch##_BASE + RZV_SCI_XSR1_OFFSET)
#define RZV_SCI_CFCLR(ch)                            (RZV_SCI##ch##_BASE + RZV_SCI_CFCLR_OFFSET)
#define RZV_SCI_ICFCLR(ch)                           (RZV_SCI##ch##_BASE + RZV_SCI_ICFCLR_OFFSET)
#define RZV_SCI_FFCLR(ch)                            (RZV_SCI##ch##_BASE + RZV_SCI_FFCLR_OFFSET)
#define RZV_SCI_XFCLR(ch)                            (RZV_SCI##ch##_BASE + RZV_SCI_XFCLR_OFFSET)

/* SCI CCR Register Bit Definitions (Parameterized) ************************/

#define SCI_CCR_RE(m)                                     (1 << 0)  /* Re */
#define SCI_CCR_TE(m)                                     (1 << 4)  /* Te */
#define SCI_CCR_MPIE(m)                                   (1 << 8)  /* Mpie */
#define SCI_CCR_DCME(m)                                   (1 << 9)  /* Dcme */
#define SCI_CCR_IDSEL(m)                                  (1 << 10) /* Idsel (CCR0 bit 10) */
/* NOTE: SCI_CCR3_IDSEL removed — IDSEL lives in CCR0 bit 10, not CCR3 (P0-3 fix) */
#define SCI_CCR_RIE(m)                                    (1 << 16) /* Rie */
#define SCI_CCR_TIE(m)                                    (1 << 20) /* Tie */
#define SCI_CCR_TEIE(m)                                   (1 << 21) /* Teie */
#define SCI_CCR_SSE(m)                                    (1 << 24) /* Sse */

/* SCI XCR Register Bit Definitions (Parameterized) ************************/

#define SCI_XCR_TCSS_SHIFT                                (0)      /* Bits 0-1: Tcss */
#define SCI_XCR_TCSS_MASK(m)                              (0x3 << SCI_XCR_TCSS_SHIFT)
#define SCI_XCR_TCSS(m,val)                               (((val) << SCI_XCR_TCSS_SHIFT) & SCI_XCR_TCSS_MASK(m))
#define SCI_XCR_BFE(m)                                    (1 << 8)  /* Bfe */
#define SCI_XCR_CF0RE(m)                                  (1 << 9)  /* Cf0Re */
#define SCI_XCR_CF1DS_SHIFT                               (10)      /* Bits 10-11: Cf1Ds */
#define SCI_XCR_CF1DS_MASK(m)                             (0x3 << SCI_XCR_CF1DS_SHIFT)
#define SCI_XCR_CF1DS(m,val)                              (((val) << SCI_XCR_CF1DS_SHIFT) & SCI_XCR_CF1DS_MASK(m))
#define SCI_XCR_PIBE(m)                                   (1 << 12)  /* Pibe */
#define SCI_XCR_PIBS_SHIFT                                (13)      /* Bits 13-15: Pibs */
#define SCI_XCR_PIBS_MASK(m)                              (0x7 << SCI_XCR_PIBS_SHIFT)
#define SCI_XCR_PIBS(m,val)                               (((val) << SCI_XCR_PIBS_SHIFT) & SCI_XCR_PIBS_MASK(m))
#define SCI_XCR_BFOIE(m)                                  (1 << 16)  /* Bfoie */
#define SCI_XCR_BCDIE(m)                                  (1 << 17)  /* Bcdie */
#define SCI_XCR_BFDIE(m)                                  (1 << 20)  /* Bfdie */
#define SCI_XCR_COFIE(m)                                  (1 << 21)  /* Cofie */
#define SCI_XCR_AEDIE(m)                                  (1 << 22)  /* Aedie */
#define SCI_XCR_BCCS_SHIFT                                (24)      /* Bits 24-25: Bccs */
#define SCI_XCR_BCCS_MASK(m)                              (0x3 << SCI_XCR_BCCS_SHIFT)
#define SCI_XCR_BCCS(m,val)                               (((val) << SCI_XCR_BCCS_SHIFT) & SCI_XCR_BCCS_MASK(m))

/* SCI XSR Register Bit Definitions (Parameterized) ************************/

#define SCI_XSR_SFSF(m)                                   (1 << 0)  /* Sfsf */
#define SCI_XSR_RXDSF(m)                                  (1 << 1)  /* Rxdsf */
#define SCI_XSR_BFOF(m)                                   (1 << 8)  /* Bfof */
#define SCI_XSR_BCDF(m)                                   (1 << 9)  /* Bcdf */
#define SCI_XSR_BFDF(m)                                   (1 << 10)  /* Bfdf */
#define SCI_XSR_CF0MF(m)                                  (1 << 11)  /* Cf0Mf */
#define SCI_XSR_CF1MF(m)                                  (1 << 12)  /* Cf1Mf */
#define SCI_XSR_PIBDF(m)                                  (1 << 13)  /* Pibdf */
#define SCI_XSR_COF(m)                                    (1 << 14)  /* Cof */
#define SCI_XSR_AEDF(m)                                   (1 << 15)  /* Aedf */
#define SCI_XSR_CF0RD_SHIFT                               (16)      /* Bits 16-23: Cf0Rd */
#define SCI_XSR_CF0RD_MASK(m)                             (0xff << SCI_XSR_CF0RD_SHIFT)
#define SCI_XSR_CF0RD(m,val)                              (((val) << SCI_XSR_CF0RD_SHIFT) & SCI_XSR_CF0RD_MASK(m))
#define SCI_XSR_CF1RD_SHIFT                               (24)      /* Bits 24-31: Cf1Rd */
#define SCI_XSR_CF1RD_MASK(m)                             (0xff << SCI_XSR_CF1RD_SHIFT)
#define SCI_XSR_CF1RD(m,val)                              (((val) << SCI_XSR_CF1RD_SHIFT) & SCI_XSR_CF1RD_MASK(m))

/* SCI CFCLR Register Bit Definitions *****************************/

#define SCI_CFCLR_ERSC                       (1 << 4)  /* Ersc */

#define SCI_CFCLR_DCMFC                      (1 << 16)  /* Dcmfc */

#define SCI_CFCLR_DPERC                      (1 << 17)  /* Dperc */

#define SCI_CFCLR_DFERC                      (1 << 18)  /* Dferc */

#define SCI_CFCLR_ORERC                      (1 << 24)  /* Orerc */

#define SCI_CFCLR_MFFC                       (1 << 26)  /* Mffc */

#define SCI_CFCLR_PERC                       (1 << 27)  /* Perc */

#define SCI_CFCLR_FERC                       (1 << 28)  /* Ferc */

#define SCI_CFCLR_TDREC                      (1 << 29)  /* Tdrec */

#define SCI_CFCLR_RDRFC                      (1 << 31)  /* Rdrfc */

/* SCI B0_FFCLR Register Bit Definitions *****************************/

#define SCI_FFCLR_DRC                        (1 << 0)  /* Drc */

/* SCI B0_ICFCLR Register Bit Definitions ****************************/

#define SCI_ICFCLR_IICSTIFC                  (1 << 3)  /* Iicstifc */

/* SCI B0_XFCLR Register Bit Definitions *****************************/

#define SCI_XFCLR_BFOC                       (1 << 8)  /* Bfoc */

#define SCI_XFCLR_BCDC                       (1 << 9)  /* Bcdc */

#define SCI_XFCLR_BFDC                       (1 << 10)  /* Bfdc */

#define SCI_XFCLR_CF0MC                      (1 << 11)  /* Cf0Mc */

#define SCI_XFCLR_CF1MC                      (1 << 12)  /* Cf1Mc */

#define SCI_XFCLR_PIBDC                      (1 << 13)  /* Pibdc */

#define SCI_XFCLR_COFC                       (1 << 14)  /* Cofc */

#define SCI_XFCLR_AEDC                       (1 << 15)  /* Aedc */


/* SCI Common Control Register 0 (CCR0) ************************************/

#define SCI_CCR0_RE             (1 << 0)  /* Receive Enable */
#define SCI_CCR0_TE             (1 << 4)  /* Transmit Enable */
#define SCI_CCR0_MPIE           (1 << 8)  /* Multi-Processor Interrupt Enable */
#define SCI_CCR0_DCME           (1 << 9)  /* Data Compare Match Enable */
#define SCI_CCR0_IDSE           (1 << 10) /* Idle State Select */
#define SCI_CCR0_RIE            (1 << 16) /* Receive Interrupt Enable */
#define SCI_CCR0_TIE            (1 << 20) /* Transmit Interrupt Enable */
#define SCI_CCR0_TEIE           (1 << 21) /* Transmit End Interrupt Enable */
#define SCI_CCR0_SSE            (1 << 24) /* SS Pin Function Enable */
#define SCI_CCR0_CKE_SHIFT      (25)      /* Bits 25-26: Clock Enable */
#define SCI_CCR0_CKE_MASK       (0x3 << SCI_CCR0_CKE_SHIFT)

/* SCI Common Control Register 1 (CCR1) ************************************/
/* P0-4 fix: corrected all bit positions to match FSP sci_b_iodefine.h CCR1_b
 * STOP, LSBF removed (live in CCR3.STP=14, CCR3.LSBF=12)
 * CTSINV, RTSINV removed (not present in RZ/V2H SCI-B CCR1)
 */

#define SCI_CCR1_CTSE           (1 << 0)  /* CTS Enable */
#define SCI_CCR1_CTSPEN         (1 << 1)  /* CTS Pin Enable (was CTSIE — wrong name) */
#define SCI_CCR1_SPB2DT         (1 << 4)  /* Serial Port Break 2 Data (output) */
#define SCI_CCR1_SPB2IO         (1 << 5)  /* Serial Port Break 2 I/O direction */
#define SCI_CCR1_PE             (1 << 8)  /* Parity Enable */
#define SCI_CCR1_PM             (1 << 9)  /* Parity Mode (0=even, 1=odd) */
#define SCI_CCR1_TINV           (1 << 12) /* TXD Inversion */
#define SCI_CCR1_RINV           (1 << 13) /* RXD Inversion */
#define SCI_CCR1_SPLP           (1 << 16) /* Simple Loopback (was misnamed PE at bit16) */
#define SCI_CCR1_SHARPS         (1 << 20) /* SHARPS mode enable */
#define SCI_CCR1_NFCS_SHIFT     (24)      /* Bits 24-26: Noise Filter Clock Select */
#define SCI_CCR1_NFCS_MASK      (0x7 << SCI_CCR1_NFCS_SHIFT)
#define SCI_CCR1_NFEN           (1 << 28) /* Noise Filter Enable */

/* SCI Common Control Register 2 (CCR2) ************************************/
/* P0-1 fix: complete rewrite to match FSP sci_b_iodefine.h CCR2_b layout.
 * Old NuttX layout was entirely wrong — BRR at bits[0:7], CKS at bits[8:9],
 * MDDR at [16:23], ABCSE/ABCS/BGDM at 24/25/26, BFME at 27.
 * Correct (FSP) layout: BCP=[2:0], BGDM=4, ABCS=5, ABCSE=6, BRR=[15:8],
 * BRME=16, CKS=[18:17], MDDR=[31:24].
 * Build CCR2 value with single write per pseudocode in phase plan.
 */

#define SCI_CCR2_BCP_SHIFT      (0)       /* Bits 0-2: Base Clock Period */
#define SCI_CCR2_BCP_MASK       (0x7 << SCI_CCR2_BCP_SHIFT)
#define SCI_CCR2_BGDM           (1 << 4)  /* Baud Rate Generator Double-Speed Mode */
#define SCI_CCR2_ABCS           (1 << 5)  /* Async Base Clock Select */
#define SCI_CCR2_ABCSE          (1 << 6)  /* Async Base Clock Select Extended */
#define SCI_CCR2_BRR_SHIFT      (8)       /* Bits 8-15: Bit Rate Register */
#define SCI_CCR2_BRR_MASK       (0xff << SCI_CCR2_BRR_SHIFT)
#define SCI_CCR2_BRME           (1 << 16) /* Bit Rate Modulation Enable */
#define SCI_CCR2_CKS_SHIFT      (17)      /* Bits 17-18: Clock Select (n) */
#define SCI_CCR2_CKS_MASK       (0x3 << SCI_CCR2_CKS_SHIFT)
#define SCI_CCR2_MDDR_SHIFT     (24)      /* Bits 24-31: Modulation Duty Register */
#define SCI_CCR2_MDDR_MASK      (0xffu << SCI_CCR2_MDDR_SHIFT)

/* Helper macro: build full CCR2 value in a single write (avoids RMW on baud fields).
 * Usage: SCI_CCR2_BUILD(mddr, cks, brme, brr, abcse, abcs, bgdm, bcp)
 */
#define SCI_CCR2_BUILD(mddr, cks, brme, brr, abcse, abcs, bgdm, bcp) \
  (((uint32_t)(mddr)  << SCI_CCR2_MDDR_SHIFT) | \
   ((uint32_t)(cks)   << SCI_CCR2_CKS_SHIFT)  | \
   ((uint32_t)(brme)  << 16)                   | \
   ((uint32_t)(brr)   << SCI_CCR2_BRR_SHIFT)   | \
   ((abcse) ? SCI_CCR2_ABCSE : 0)              | \
   ((abcs)  ? SCI_CCR2_ABCS  : 0)              | \
   ((bgdm)  ? SCI_CCR2_BGDM  : 0)              | \
   ((uint32_t)(bcp)   & SCI_CCR2_BCP_MASK))

/* Clear mask covering all baud-rate fields (use before OR-in new values) */
#define SCI_CCR2_BAUD_MASK \
  (SCI_CCR2_MDDR_MASK | SCI_CCR2_CKS_MASK | SCI_CCR2_BRME | \
   SCI_CCR2_BRR_MASK  | SCI_CCR2_ABCSE    | SCI_CCR2_ABCS  | \
   SCI_CCR2_BGDM      | SCI_CCR2_BCP_MASK)

/* SCI Common Control Register 3 (CCR3) ************************************/
/* P0-3, P0-5, Low-17 fixes: corrected bit positions per FSP CCR3_b.
 * BPEN moved from bit 0 to bit 7 (Low-17).
 * FM (FIFO mode enable) added at bit 20 — was missing entirely (P0-5).
 * LSBF added at bit 12 (removed from CCR1 where it was wrong).
 * SINV, RXDESEL, MP, DEN, CKE, GM, BLK added per FSP.
 */

#define SCI_CCR3_CPHA           (1 << 0)  /* SPI clock phase */
#define SCI_CCR3_CPOL           (1 << 1)  /* SPI clock polarity */
#define SCI_CCR3_BPEN           (1 << 7)  /* Base Pointer Enable (Low-17 fix: was bit 0) */
#define SCI_CCR3_CHR_SHIFT      (8)       /* Bits 8-9: Character Length */
#define SCI_CCR3_CHR_MASK       (0x3 << SCI_CCR3_CHR_SHIFT)
#  define SCI_CCR3_CHR_7BIT     (0x3 << SCI_CCR3_CHR_SHIFT)  /* 7-bit data */
#  define SCI_CCR3_CHR_8BIT     (0x0 << SCI_CCR3_CHR_SHIFT)  /* 8-bit data */
#  define SCI_CCR3_CHR_9BIT     (0x1 << SCI_CCR3_CHR_SHIFT)  /* 9-bit data */
#define SCI_CCR3_LSBF           (1 << 12) /* LSB First (moved from CCR1 where it was wrong) */
#define SCI_CCR3_SINV           (1 << 13) /* Signal Inversion */
#define SCI_CCR3_STP            (1 << 14) /* Stop Bit Length */
#  define SCI_CCR3_STP_1BIT     (0 << 14)                    /* 1 stop bit */
#  define SCI_CCR3_STP_2BIT     (1 << 14)                    /* 2 stop bits */
#define SCI_CCR3_RXDESEL        (1 << 15) /* RX Deselect in synchronous mode */
#define SCI_CCR3_MOD_SHIFT      (16)      /* Bits 16-18: Mode Select */
#define SCI_CCR3_MOD_MASK       (0x7 << SCI_CCR3_MOD_SHIFT)
#  define SCI_CCR3_MOD_ASYNC    (0x0 << SCI_CCR3_MOD_SHIFT)  /* Asynchronous mode */
#  define SCI_CCR3_MOD_SYNC     (0x1 << SCI_CCR3_MOD_SHIFT)  /* Synchronous mode */
#  define SCI_CCR3_MOD_SPI      (0x3 << SCI_CCR3_MOD_SHIFT)  /* Simple SPI mode */
#  define SCI_CCR3_MOD_I2C      (0x4 << SCI_CCR3_MOD_SHIFT)  /* Simple I2C mode */
#define SCI_CCR3_MP             (1 << 19) /* Multi-Processor mode */
#define SCI_CCR3_FM             (1 << 20) /* FIFO Mode Enable (P0-5 fix: was FCR bit 7 — wrong) */
#define SCI_CCR3_DEN            (1 << 21) /* Driver Enable (RS-485 DE signal) */
#define SCI_CCR3_CKE_SHIFT      (24)      /* Bits 24-25: Clock Enable for synchronous */
#define SCI_CCR3_CKE_MASK       (0x3 << SCI_CCR3_CKE_SHIFT)
#define SCI_CCR3_GM             (1 << 28) /* GSM mode */
#define SCI_CCR3_BLK            (1 << 29) /* Block transfer mode */

/* SCI Common Control Register 4 (CCR4) ************************************/
/* Low-16 fix: corrected all CCR4 bit names to match FSP CCR4_b.
 * CPHA/CPOL/MFF/MSS do NOT live here — they are CCR3 fields in SCI-B.
 * CCR4 is used for auto-baud detection and compare-data features.
 */

#define SCI_CCR4_CMPD_SHIFT     (0)       /* Bits 0-8: Compare Data */
#define SCI_CCR4_CMPD_MASK      (0x1ff << SCI_CCR4_CMPD_SHIFT)
#define SCI_CCR4_ASEN           (1 << 16) /* Auto-baud Sync Enable */
#define SCI_CCR4_ATEN           (1 << 17) /* Auto-baud Timing Enable */
#define SCI_CCR4_AST_SHIFT      (24)      /* Bits 24-26: Auto-baud Sync Threshold */
#define SCI_CCR4_AST_MASK       (0x7 << SCI_CCR4_AST_SHIFT)
#define SCI_CCR4_AJD            (1 << 27) /* Auto-baud Judgment */
#define SCI_CCR4_ATT_SHIFT      (28)      /* Bits 28-30: Auto-baud Timing Threshold */
#define SCI_CCR4_ATT_MASK       (0x7 << SCI_CCR4_ATT_SHIFT)
#define SCI_CCR4_AET            (1 << 31) /* Auto-baud Error Threshold */
/* SCI CESR Register Bit Definitions *********************************/

#define SCI_CESR_RIST                           (1 << 0)  /* Rist */

#define SCI_CESR_TIST                           (1 << 4)  /* Tist */

/* SCI CSR Register Bit Definitions **********************************/

#define SCI_CSR_ERS                             (1 << 4)  /* Ers */

#define SCI_CSR_RXDMON                          (1 << 15)  /* Rxdmon */

#define SCI_CSR_DCMF                            (1 << 16)  /* Dcmf */

#define SCI_CSR_DPER                            (1 << 17)  /* Dper */

#define SCI_CSR_DFER                            (1 << 18)  /* Dfer */

#define SCI_CSR_ORER                            (1 << 24)  /* Orer */

#define SCI_CSR_MFF                             (1 << 26)  /* Mff */

#define SCI_CSR_PER                             (1 << 27)  /* Per */

#define SCI_CSR_FER                             (1 << 28)  /* Fer */

#define SCI_CSR_TDRE                            (1 << 29)  /* Tdre */

#define SCI_CSR_TEND                            (1 << 30)  /* Tend */

#define SCI_CSR_RDRF                            (1 << 31)  /* Rdrf */

/* SCI DCR Register Bit Definitions **********************************/

#define SCI_DCR_DEPOL                           (1 << 0)  /* Depol */

#define SCI_DCR_DEAST_SHIFT                     (8)      /* Bits 8-12: Deast */
#define SCI_DCR_DEAST_MASK                      (0x1f << SCI_DCR_DEAST_SHIFT)

#define SCI_DCR_DENGT_SHIFT                     (16)      /* Bits 16-20: Dengt */
#define SCI_DCR_DENGT_MASK                      (0x1f << SCI_DCR_DENGT_SHIFT)

/* SCI FCR Register Bit Definitions **********************************/
/* P0-5 fix: SCI_FCR_FM (bit 7) removed — bit 7 is RESERVED in FCR for SCI-B.
 * FIFO mode enable lives in CCR3.FM (bit 20). Use SCI_CCR3_FM instead.
 */

#define SCI_FCR_DRES                            (1 << 0)  /* Data Receive Error Select */
/* Bit 7: RESERVED — do not set. FM enable is CCR3.FM bit 20. */

#define SCI_FCR_TTRG_SHIFT                      (8)      /* Bits 8-12: Ttrg */
#define SCI_FCR_TTRG_MASK                       (0x1f << SCI_FCR_TTRG_SHIFT)

#define SCI_FCR_TFRST                           (1 << 15)  /* Tfrst */

#define SCI_FCR_RTRG_SHIFT                      (16)      /* Bits 16-20: Rtrg */
#define SCI_FCR_RTRG_MASK                       (0x1f << SCI_FCR_RTRG_SHIFT)

#define SCI_FCR_RFRST                           (1 << 23)  /* Rfrst */

#define SCI_FCR_RSTRG_SHIFT                     (24)      /* Bits 24-28: Rstrg */
#define SCI_FCR_RSTRG_MASK                      (0x1f << SCI_FCR_RSTRG_SHIFT)

/* SCI FRSR Register Bit Definitions *********************************/

#define SCI_FRSR_DR                             (1 << 0)  /* Dr */

#define SCI_FRSR_R_SHIFT                        (8)      /* Bits 8-13: R */
#define SCI_FRSR_R_MASK                         (0x3f << SCI_FRSR_R_SHIFT)

#define SCI_FRSR_PNUM_SHIFT                     (16)      /* Bits 16-21: Pnum */
#define SCI_FRSR_PNUM_MASK                      (0x3f << SCI_FRSR_PNUM_SHIFT)

#define SCI_FRSR_FNUM_SHIFT                     (24)      /* Bits 24-29: Fnum */
#define SCI_FRSR_FNUM_MASK                      (0x3f << SCI_FRSR_FNUM_SHIFT)

/* SCI FTSR Register Bit Definitions *********************************/

#define SCI_FTSR_T_SHIFT                        (0)      /* Bits 0-5: T */
#define SCI_FTSR_T_MASK                         (0x3f << SCI_FTSR_T_SHIFT)

/* SCI HCR Register Bit Definitions **********************************/

#define SCI_HCR_HDEN                            (1 << 0)  /* Hden */

/* SCI ICR Register Bit Definitions **********************************/

#define SCI_ICR_IICDL_SHIFT                     (0)      /* Bits 0-4: Iicdl */
#define SCI_ICR_IICDL_MASK                      (0x1f << SCI_ICR_IICDL_SHIFT)

#define SCI_ICR_IICINTM                         (1 << 8)  /* Iicintm */

#define SCI_ICR_IICCSC                          (1 << 9)  /* Iiccsc */

#define SCI_ICR_IICACKT                         (1 << 13)  /* Iicackt */

#define SCI_ICR_IICSTAREQ                       (1 << 16)  /* Iicstareq */

#define SCI_ICR_IICRSTAREQ                      (1 << 17)  /* Iicrstareq */

#define SCI_ICR_IICSTPREQ                       (1 << 18)  /* Iicstpreq */

#define SCI_ICR_IICSDAS_SHIFT                   (20)      /* Bits 20-21: Iicsdas */
#define SCI_ICR_IICSDAS_MASK                    (0x3 << SCI_ICR_IICSDAS_SHIFT)

#define SCI_ICR_IICSCLS_SHIFT                   (22)      /* Bits 22-23: Iicscls */
#define SCI_ICR_IICSCLS_MASK                    (0x3 << SCI_ICR_IICSCLS_SHIFT)

/* SCI ISR Register Bit Definitions **********************************/

#define SCI_ISR_IICACKR                         (1 << 0)  /* Iicackr */

#define SCI_ISR_IICSTIF                         (1 << 3)  /* Iicstif */

/* =========================================================================
 * I2C-mode helper macro (FSP r_sci_b_i2c.c line 62-64)
 *
 * SCI_I2C_REQ - Build an ICR request word atomically.
 *
 * Per FSP SCI_B_I2C_PRV_GENERATE_REQUEST: IICSDAS and IICSCLS must be
 * written in the same store as the request bit (STAREQ/RSTAREQ/STPREQ).
 * This macro clears the SDAS and SCLS fields, then ORs in new values + req.
 *
 *   base - current ICR value (preserves IICDL, IICINTM, IICCSC, IICACKT)
 *   sdas - IICSDAS value (0=output, 3=high-Z); use 1 when issuing a request
 *   scls - IICSCLS value (0=output, 3=high-Z); use 1 when issuing a request
 *   req  - request bit: SCI_ICR_IICSTAREQ / IICRSTAREQ / IICSTPREQ
 *
 * Usage: putreg32(SCI_I2C_REQ(icr, 1, 1, SCI_ICR_IICSTAREQ), base+ICR_OFF)
 * =========================================================================
 */
#define SCI_I2C_REQ(base, sdas, scls, req) \
  (((base) & ~(SCI_ICR_IICSDAS_MASK | SCI_ICR_IICSCLS_MASK)) | \
   (((uint32_t)(sdas)) << SCI_ICR_IICSDAS_SHIFT) | \
   (((uint32_t)(scls)) << SCI_ICR_IICSCLS_SHIFT) | \
   (req))

/* SCI RDR Register Bit Definitions **********************************/

#define SCI_RDR_RDAT_SHIFT                      (0)      /* Bits 0-8: Rdat */
#define SCI_RDR_RDAT_MASK                       (0x1ff << SCI_RDR_RDAT_SHIFT)

#define SCI_RDR_MPB                             (1 << 9)  /* Mpb */

#define SCI_RDR_DR                              (1 << 10)  /* Dr */

#define SCI_RDR_FPER                            (1 << 11)  /* Fper */

#define SCI_RDR_FFER                            (1 << 12)  /* Ffer */

#define SCI_RDR_ORER                            (1 << 24)  /* Orer */

#define SCI_RDR_PER                             (1 << 27)  /* Per */

#define SCI_RDR_FER                             (1 << 28)  /* Fer */

/* L3 fix: SCI_RDR_BY_RDAT is the same bit as SCI_RDR_FER (both bit 28).
 * They are aliases; BY_RDAT is removed to avoid misleading code. Use SCI_RDR_FER. */
/* #define SCI_RDR_BY_RDAT (1 << 28) -- alias of SCI_RDR_FER, removed (L3) */

/* SCI TDR Register Bit Definitions **********************************/

#define SCI_TDR_TDAT_SHIFT                      (0)      /* Bits 0-8: Tdat */
#define SCI_TDR_TDAT_MASK                       (0x1ff << SCI_TDR_TDAT_SHIFT)

#define SCI_TDR_MPBT                            (1 << 9)  /* Mpbt */

#define SCI_TDR_BY_TDAT_SHIFT                   (0)      /* Bits 0-7: By Tdat */
#define SCI_TDR_BY_TDAT_MASK                    (0xff << SCI_TDR_BY_TDAT_SHIFT)

/* SCI XCR0 Register Bit Definitions *********************************/

#define SCI_XCR0_TCSS_SHIFT                     (0)      /* Bits 0-1: Tcss */
#define SCI_XCR0_TCSS_MASK                      (0x3 << SCI_XCR0_TCSS_SHIFT)

#define SCI_XCR0_BFE                            (1 << 8)  /* Bfe */

#define SCI_XCR0_CF0RE                          (1 << 9)  /* Cf0Re */

#define SCI_XCR0_CF1DS_SHIFT                    (10)      /* Bits 10-11: Cf1Ds */
#define SCI_XCR0_CF1DS_MASK                     (0x3 << SCI_XCR0_CF1DS_SHIFT)

#define SCI_XCR0_PIBE                           (1 << 12)  /* Pibe */

#define SCI_XCR0_PIBS_SHIFT                     (13)      /* Bits 13-15: Pibs */
#define SCI_XCR0_PIBS_MASK                      (0x7 << SCI_XCR0_PIBS_SHIFT)

#define SCI_XCR0_BFOIE                          (1 << 16)  /* Bfoie */

#define SCI_XCR0_BCDIE                          (1 << 17)  /* Bcdie */

#define SCI_XCR0_BFDIE                          (1 << 20)  /* Bfdie */

#define SCI_XCR0_COFIE                          (1 << 21)  /* Cofie */

#define SCI_XCR0_AEDIE                          (1 << 22)  /* Aedie */

#define SCI_XCR0_BCCS_SHIFT                     (24)      /* Bits 24-25: Bccs */
#define SCI_XCR0_BCCS_MASK                      (0x3 << SCI_XCR0_BCCS_SHIFT)

/* SCI XCR1 Register Bit Definitions *********************************/

#define SCI_XCR1_TCST                           (1 << 0)  /* Tcst */

#define SCI_XCR1_SDST                           (1 << 4)  /* Sdst */

#define SCI_XCR1_BMEN                           (1 << 5)  /* Bmen */

#define SCI_XCR1_PCF1D_SHIFT                    (8)      /* Bits 8-15: Pcf1D */
#define SCI_XCR1_PCF1D_MASK                     (0xff << SCI_XCR1_PCF1D_SHIFT)

#define SCI_XCR1_SCF1D_SHIFT                    (16)      /* Bits 16-23: Scf1D */
#define SCI_XCR1_SCF1D_MASK                     (0xff << SCI_XCR1_SCF1D_SHIFT)

#define SCI_XCR1_CF1CE_SHIFT                    (24)      /* Bits 24-31: Cf1Ce */
#define SCI_XCR1_CF1CE_MASK                     (0xff << SCI_XCR1_CF1CE_SHIFT)

/* SCI XCR2 Register Bit Definitions *********************************/

#define SCI_XCR2_CF0D_SHIFT                     (0)      /* Bits 0-7: Cf0D */
#define SCI_XCR2_CF0D_MASK                      (0xff << SCI_XCR2_CF0D_SHIFT)

#define SCI_XCR2_CF0CE_SHIFT                    (8)      /* Bits 8-15: Cf0Ce */
#define SCI_XCR2_CF0CE_MASK                     (0xff << SCI_XCR2_CF0CE_SHIFT)

#define SCI_XCR2_BFLW_SHIFT                     (16)      /* Bits 16-31: Bflw */
#define SCI_XCR2_BFLW_MASK                      (0xffff << SCI_XCR2_BFLW_SHIFT)

/* SCI XSR0 Register Bit Definitions *********************************/

#define SCI_XSR0_SFSF                           (1 << 0)  /* Sfsf */

#define SCI_XSR0_RXDSF                          (1 << 1)  /* Rxdsf */

#define SCI_XSR0_BFOF                           (1 << 8)  /* Bfof */

#define SCI_XSR0_BCDF                           (1 << 9)  /* Bcdf */

#define SCI_XSR0_BFDF                           (1 << 10)  /* Bfdf */

#define SCI_XSR0_CF0MF                          (1 << 11)  /* Cf0Mf */

#define SCI_XSR0_CF1MF                          (1 << 12)  /* Cf1Mf */

#define SCI_XSR0_PIBDF                          (1 << 13)  /* Pibdf */

#define SCI_XSR0_COF                            (1 << 14)  /* Cof */

#define SCI_XSR0_AEDF                           (1 << 15)  /* Aedf */

#define SCI_XSR0_CF0RD_SHIFT                    (16)      /* Bits 16-23: Cf0Rd */
#define SCI_XSR0_CF0RD_MASK                     (0xff << SCI_XSR0_CF0RD_SHIFT)

#define SCI_XSR0_CF1RD_SHIFT                    (24)      /* Bits 24-31: Cf1Rd */
#define SCI_XSR0_CF1RD_MASK                     (0xff << SCI_XSR0_CF1RD_SHIFT)

/* SCI XSR1 Register Bit Definitions *********************************/

#define SCI_XSR1_TCNT_SHIFT                     (0)      /* Bits 0-15: Tcnt */
#define SCI_XSR1_TCNT_MASK                      (0xffff << SCI_XSR1_TCNT_SHIFT)

/* SCI Channel definitions */
#define RZV_SCI_CHANNEL_0          0
#define RZV_SCI_CHANNEL_1          1
#define RZV_SCI_CHANNEL_2          2
#define RZV_SCI_CHANNEL_3          3
#define RZV_SCI_CHANNEL_4          4
#define RZV_SCI_CHANNEL_5          5
#define RZV_SCI_CHANNEL_6          6
#define RZV_SCI_CHANNEL_7          7
#define RZV_SCI_CHANNEL_8          8
#define RZV_SCI_CHANNEL_9          9

/* Maximum number of SCI channels */
#define RZV_SCI_MAX_CHANNELS       10

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SCI_H */
