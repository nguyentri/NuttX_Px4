/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_sci.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SCI_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SCI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SCI Base Address */
#ifndef R_SCI_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_SCI_BASE           0x40358000
#else
#define R_SCI_BASE           0x50358000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_SCI_CH_STRIDE    0x00000100
#define R_SCI_CH_BASE(ch)   (R_SCI_BASE + ((uint32_t)(ch) * R_SCI_CH_STRIDE))

/* SCI Register Offsets */

#define R_SCI_SMR_OFFSET                          0x00000000  /* Serial Mode Register (SCMR.SMIF = 0) */
#define R_SCI_SMR_SMCI_OFFSET                     0x00000000  /* Serial mode register (SCMR.SMIF = 1) */
#define R_SCI_BRR_OFFSET                          0x00000001  /* Bit Rate Register */
#define R_SCI_SCR_OFFSET                          0x00000002  /* Serial Control Register (SCMR.SMIF = 0) */
#define R_SCI_SCR_SMCI_OFFSET                     0x00000002  /* Serial Control Register (SCMR.SMIF =1) */
#define R_SCI_TDR_OFFSET                          0x00000003  /* Transmit Data Register */
#define R_SCI_SSR_OFFSET                          0x00000004  /* Serial Status Register(SCMR.SMIF = 0 and FCR.FM=0) */
#define R_SCI_SSR_FIFO_OFFSET                     0x00000004  /* Serial Status Register(SCMR.SMIF = 0 and FCR.FM=1) */
#define R_SCI_SSR_MANC_OFFSET                     0x00000004  /* Serial Status Register for Manchester Mode (SCMR.SMIF = 0, and MMR.MANEN = 1) */
#define R_SCI_SSR_SMCI_OFFSET                     0x00000004  /* Serial Status Register(SCMR.SMIF = 1) */
#define R_SCI_RDR_OFFSET                          0x00000005  /* Receive Data Register */
#define R_SCI_SCMR_OFFSET                         0x00000006  /* Smart Card Mode Register */
#define R_SCI_SEMR_OFFSET                         0x00000007  /* Serial Extended Mode Register */
#define R_SCI_SNFR_OFFSET                         0x00000008  /* Noise Filter Setting Register */
#define R_SCI_SIMR1_OFFSET                        0x00000009  /* I2C Mode Register 1 */
#define R_SCI_SIMR2_OFFSET                        0x0000000a  /* I2C Mode Register 2 */
#define R_SCI_SIMR3_OFFSET                        0x0000000b  /* I2C Mode Register 3 */
#define R_SCI_SISR_OFFSET                         0x0000000c  /* I2C Status Register */
#define R_SCI_SPMR_OFFSET                         0x0000000d  /* SPI Mode Register */
#define R_SCI_TDRHL_OFFSET                        0x0000000e  /* Transmit 9-bit Data Register */
#define R_SCI_FTDRHL_OFFSET                       0x0000000e  /* Transmit FIFO Data Register HL */
#define R_SCI_FTDRH_OFFSET                        0x0000000e  /* Transmit FIFO Data Register H */
#define R_SCI_TDRHL_MAN_OFFSET                    0x0000000e  /* Transmit Data Register for Manchester Mode (MMR.MANEN = 1) */
#define R_SCI_FTDRL_OFFSET                        0x0000000f  /* Transmit FIFO Data Register L */
#define R_SCI_RDRHL_OFFSET                        0x00000010  /* Receive 9-bit Data Register */
#define R_SCI_FRDRHL_OFFSET                       0x00000010  /* Receive FIFO Data Register HL */
#define R_SCI_RDRHL_MAN_OFFSET                    0x00000010  /* Receive Data Register for Manchester Mode (MMR.MANEN = 1) */
#define R_SCI_FRDRH_OFFSET                        0x00000010  /* Receive FIFO Data Register H */
#define R_SCI_FRDRL_OFFSET                        0x00000011  /* Receive FIFO Data Register L */
#define R_SCI_MDDR_OFFSET                         0x00000012  /* Modulation Duty Register */
#define R_SCI_DCCR_OFFSET                         0x00000013  /* Data Compare Match Control Register */
#define R_SCI_FCR_OFFSET                          0x00000014  /* FIFO Control Register */
#define R_SCI_FDR_OFFSET                          0x00000016  /* FIFO Data Count Register */
#define R_SCI_LSR_OFFSET                          0x00000018  /* Line Status Register */
#define R_SCI_CDR_OFFSET                          0x0000001a  /* Compare Match Data Register */
#define R_SCI_SPTR_OFFSET                         0x0000001c  /* Serial Port Register */
#define R_SCI_ACTR_OFFSET                         0x0000001d  /* Adjustment Communication Timing Register */
#define R_SCI_ESMER_OFFSET                        0x00000020  /* Extended Serial Module Enable Register */
#define R_SCI_MMR_OFFSET                          0x00000020  /* Manchester Mode Register */
#define R_SCI_CR0_OFFSET                          0x00000021  /* Control Register 0 */
#define R_SCI_CR1_OFFSET                          0x00000022  /* Control Register 1 */
#define R_SCI_TMPR_OFFSET                         0x00000022  /* Transmit Manchester Preface Setting Register */
#define R_SCI_CR2_OFFSET                          0x00000023  /* Control Register 2 */
#define R_SCI_RMPR_OFFSET                         0x00000023  /* Receive Manchester Preface Setting Register */
#define R_SCI_CR3_OFFSET                          0x00000024  /* Control Register 3 */
#define R_SCI_MESR_OFFSET                         0x00000024  /* Manchester Extended Error Status Register */
#define R_SCI_PCR_OFFSET                          0x00000025  /* Port Control Register */
#define R_SCI_MECR_OFFSET                         0x00000025  /* Manchester Extended Error Control Register */
#define R_SCI_ICR_OFFSET                          0x00000026  /* Interrupt Control Register */
#define R_SCI_STR_OFFSET                          0x00000027  /* Status Register */
#define R_SCI_STCR_OFFSET                         0x00000028  /* Status Clear Register */
#define R_SCI_CF0DR_OFFSET                        0x00000029  /* Control Field 0 Data Register */
#define R_SCI_CF0CR_OFFSET                        0x0000002a  /* Control Field 0 Compare Enable Register */
#define R_SCI_CF0RR_OFFSET                        0x0000002b  /* Control Field 0 Receive Data Register */
#define R_SCI_PCF1DR_OFFSET                       0x0000002c  /* Primary Control Field 1 Data Register */
#define R_SCI_SCF1DR_OFFSET                       0x0000002d  /* Secondary Control Field 1 Data Register */
#define R_SCI_CF1CR_OFFSET                        0x0000002e  /* Control Field 1 Compare Enable Register */
#define R_SCI_CF1RR_OFFSET                        0x0000002f  /* Control Field 1 Receive Data Register */
#define R_SCI_TCR_OFFSET                          0x00000030  /* Timer Control Register */
#define R_SCI_TMR_OFFSET                          0x00000031  /* Timer Mode Register */
#define R_SCI_TPRE_OFFSET                         0x00000032  /* Timer Prescaler Register */
#define R_SCI_TCNT_OFFSET                         0x00000033  /* Timer Count Register */
#define R_SCI_SCIMSKEN_OFFSET                     0x0000003c  /* SCI5 TXD Output Mask Enable Register */

/* SCI Register Addresses */

#define R_SCI_SMR(n)                              (R_SCI_CH_BASE(n) + R_SCI_SMR_OFFSET)
#define R_SCI_SMR_SMCI(n)                         (R_SCI_CH_BASE(n) + R_SCI_SMR_SMCI_OFFSET)
#define R_SCI_BRR(n)                              (R_SCI_CH_BASE(n) + R_SCI_BRR_OFFSET)
#define R_SCI_SCR(n)                              (R_SCI_CH_BASE(n) + R_SCI_SCR_OFFSET)
#define R_SCI_SCR_SMCI(n)                         (R_SCI_CH_BASE(n) + R_SCI_SCR_SMCI_OFFSET)
#define R_SCI_TDR(n)                              (R_SCI_CH_BASE(n) + R_SCI_TDR_OFFSET)
#define R_SCI_SSR(n)                              (R_SCI_CH_BASE(n) + R_SCI_SSR_OFFSET)
#define R_SCI_SSR_FIFO(n)                         (R_SCI_CH_BASE(n) + R_SCI_SSR_FIFO_OFFSET)
#define R_SCI_SSR_MANC(n)                         (R_SCI_CH_BASE(n) + R_SCI_SSR_MANC_OFFSET)
#define R_SCI_SSR_SMCI(n)                         (R_SCI_CH_BASE(n) + R_SCI_SSR_SMCI_OFFSET)
#define R_SCI_RDR(n)                              (R_SCI_CH_BASE(n) + R_SCI_RDR_OFFSET)
#define R_SCI_SCMR(n)                             (R_SCI_CH_BASE(n) + R_SCI_SCMR_OFFSET)
#define R_SCI_SEMR(n)                             (R_SCI_CH_BASE(n) + R_SCI_SEMR_OFFSET)
#define R_SCI_SNFR(n)                             (R_SCI_CH_BASE(n) + R_SCI_SNFR_OFFSET)
#define R_SCI_SIMR1(n)                            (R_SCI_CH_BASE(n) + R_SCI_SIMR1_OFFSET)
#define R_SCI_SIMR2(n)                            (R_SCI_CH_BASE(n) + R_SCI_SIMR2_OFFSET)
#define R_SCI_SIMR3(n)                            (R_SCI_CH_BASE(n) + R_SCI_SIMR3_OFFSET)
#define R_SCI_SISR(n)                             (R_SCI_CH_BASE(n) + R_SCI_SISR_OFFSET)
#define R_SCI_SPMR(n)                             (R_SCI_CH_BASE(n) + R_SCI_SPMR_OFFSET)
#define R_SCI_TDRHL(n)                            (R_SCI_CH_BASE(n) + R_SCI_TDRHL_OFFSET)
#define R_SCI_FTDRHL(n)                           (R_SCI_CH_BASE(n) + R_SCI_FTDRHL_OFFSET)
#define R_SCI_FTDRH(n)                            (R_SCI_CH_BASE(n) + R_SCI_FTDRH_OFFSET)
#define R_SCI_TDRHL_MAN(n)                        (R_SCI_CH_BASE(n) + R_SCI_TDRHL_MAN_OFFSET)
#define R_SCI_FTDRL(n)                            (R_SCI_CH_BASE(n) + R_SCI_FTDRL_OFFSET)
#define R_SCI_RDRHL(n)                            (R_SCI_CH_BASE(n) + R_SCI_RDRHL_OFFSET)
#define R_SCI_FRDRHL(n)                           (R_SCI_CH_BASE(n) + R_SCI_FRDRHL_OFFSET)
#define R_SCI_RDRHL_MAN(n)                        (R_SCI_CH_BASE(n) + R_SCI_RDRHL_MAN_OFFSET)
#define R_SCI_FRDRH(n)                            (R_SCI_CH_BASE(n) + R_SCI_FRDRH_OFFSET)
#define R_SCI_FRDRL(n)                            (R_SCI_CH_BASE(n) + R_SCI_FRDRL_OFFSET)
#define R_SCI_MDDR(n)                             (R_SCI_CH_BASE(n) + R_SCI_MDDR_OFFSET)
#define R_SCI_DCCR(n)                             (R_SCI_CH_BASE(n) + R_SCI_DCCR_OFFSET)
#define R_SCI_FCR(n)                              (R_SCI_CH_BASE(n) + R_SCI_FCR_OFFSET)
#define R_SCI_FDR(n)                              (R_SCI_CH_BASE(n) + R_SCI_FDR_OFFSET)
#define R_SCI_LSR(n)                              (R_SCI_CH_BASE(n) + R_SCI_LSR_OFFSET)
#define R_SCI_CDR(n)                              (R_SCI_CH_BASE(n) + R_SCI_CDR_OFFSET)
#define R_SCI_SPTR(n)                             (R_SCI_CH_BASE(n) + R_SCI_SPTR_OFFSET)
#define R_SCI_ACTR(n)                             (R_SCI_CH_BASE(n) + R_SCI_ACTR_OFFSET)
#define R_SCI_ESMER(n)                            (R_SCI_CH_BASE(n) + R_SCI_ESMER_OFFSET)
#define R_SCI_MMR(n)                              (R_SCI_CH_BASE(n) + R_SCI_MMR_OFFSET)
#define R_SCI_CR0(n)                              (R_SCI_CH_BASE(n) + R_SCI_CR0_OFFSET)
#define R_SCI_CR1(n)                              (R_SCI_CH_BASE(n) + R_SCI_CR1_OFFSET)
#define R_SCI_TMPR(n)                             (R_SCI_CH_BASE(n) + R_SCI_TMPR_OFFSET)
#define R_SCI_CR2(n)                              (R_SCI_CH_BASE(n) + R_SCI_CR2_OFFSET)
#define R_SCI_RMPR(n)                             (R_SCI_CH_BASE(n) + R_SCI_RMPR_OFFSET)
#define R_SCI_CR3(n)                              (R_SCI_CH_BASE(n) + R_SCI_CR3_OFFSET)
#define R_SCI_MESR(n)                             (R_SCI_CH_BASE(n) + R_SCI_MESR_OFFSET)
#define R_SCI_PCR(n)                              (R_SCI_CH_BASE(n) + R_SCI_PCR_OFFSET)
#define R_SCI_MECR(n)                             (R_SCI_CH_BASE(n) + R_SCI_MECR_OFFSET)
#define R_SCI_ICR(n)                              (R_SCI_CH_BASE(n) + R_SCI_ICR_OFFSET)
#define R_SCI_STR(n)                              (R_SCI_CH_BASE(n) + R_SCI_STR_OFFSET)
#define R_SCI_STCR(n)                             (R_SCI_CH_BASE(n) + R_SCI_STCR_OFFSET)
#define R_SCI_CF0DR(n)                            (R_SCI_CH_BASE(n) + R_SCI_CF0DR_OFFSET)
#define R_SCI_CF0CR(n)                            (R_SCI_CH_BASE(n) + R_SCI_CF0CR_OFFSET)
#define R_SCI_CF0RR(n)                            (R_SCI_CH_BASE(n) + R_SCI_CF0RR_OFFSET)
#define R_SCI_PCF1DR(n)                           (R_SCI_CH_BASE(n) + R_SCI_PCF1DR_OFFSET)
#define R_SCI_SCF1DR(n)                           (R_SCI_CH_BASE(n) + R_SCI_SCF1DR_OFFSET)
#define R_SCI_CF1CR(n)                            (R_SCI_CH_BASE(n) + R_SCI_CF1CR_OFFSET)
#define R_SCI_CF1RR(n)                            (R_SCI_CH_BASE(n) + R_SCI_CF1RR_OFFSET)
#define R_SCI_TCR(n)                              (R_SCI_CH_BASE(n) + R_SCI_TCR_OFFSET)
#define R_SCI_TMR(n)                              (R_SCI_CH_BASE(n) + R_SCI_TMR_OFFSET)
#define R_SCI_TPRE(n)                             (R_SCI_CH_BASE(n) + R_SCI_TPRE_OFFSET)
#define R_SCI_TCNT(n)                             (R_SCI_CH_BASE(n) + R_SCI_TCNT_OFFSET)
#define R_SCI_SCIMSKEN(n)                         (R_SCI_CH_BASE(n) + R_SCI_SCIMSKEN_OFFSET)

/* Register bit definitions */
/* SMR Register bit definitions */
#define R_SCI_SMR_CM                              (1 << 7)  /* Communication Mode */

#define R_SCI_SMR_CHR                             (1 << 6)  /* Character Length(Valid only in asynchronous mode) */

#define R_SCI_SMR_PE                              (1 << 5)  /* Parity Enable(Valid only in asynchronous mode) */

#define R_SCI_SMR_PM                              (1 << 4)  /* Parity Mode (Valid only when the PE bit is 1) */

#define R_SCI_SMR_STOP                            (1 << 3)  /* Stop Bit Length(Valid only in asynchronous mode) */

#define R_SCI_SMR_MP                              (1 << 2)  /* Multi-Processor Mode(Valid only in asynchronous mode) */

#define R_SCI_SMR_CKS_SHIFT                       (0)  /* Clock Select */
#define R_SCI_SMR_CKS_MASK                        0x3
#  define R_SCI_SMR_CKS_00                                (0 << R_SCI_SMR_CKS_SHIFT)  /* PCLK clock */
#  define R_SCI_SMR_CKS_01                                (1 << R_SCI_SMR_CKS_SHIFT)  /* PCLK/4 clock */
#  define R_SCI_SMR_CKS_10                                (2 << R_SCI_SMR_CKS_SHIFT)  /* PCLK/16 clock */
#  define R_SCI_SMR_CKS_11                                (3 << R_SCI_SMR_CKS_SHIFT)  /* PCLK/64 clock */

/* SMR_SMCI Register bit definitions */
#define R_SCI_SMR_SMCI_GM                         (1 << 7)  /* GSM Mode */

#define R_SCI_SMR_SMCI_BLK                        (1 << 6)  /* Block Transfer Mode */

#define R_SCI_SMR_SMCI_PE                         (1 << 5)  /* Parity Enable(Valid only in asynchronous mode) */

#define R_SCI_SMR_SMCI_PM                         (1 << 4)  /* Parity Mode (Valid only when the PE bit is 1) */

#define R_SCI_SMR_SMCI_BCP_SHIFT                  (2)  /* Base Clock Pulse(Valid only in asynchronous mode) */
#define R_SCI_SMR_SMCI_BCP_MASK                   0xc
#  define R_SCI_SMR_SMCI_BCP_00                           (0 << R_SCI_SMR_SMCI_BCP_SHIFT)  /* 93 clock cycles(S=93) (SCMR.BCP2=0) / 32 clock cycles(S=32)  (SCMR.BCP2=1)  */
#  define R_SCI_SMR_SMCI_BCP_01                           (1 << R_SCI_SMR_SMCI_BCP_SHIFT)  /* 128 clock cycles(S=128) (SCMR.BCP2=0) / 64 clock cycles(S=64) (SCMR.BCP2=1) */
#  define R_SCI_SMR_SMCI_BCP_10                           (2 << R_SCI_SMR_SMCI_BCP_SHIFT)  /* 186 clock cycles(S=186) (SCMR.BCP2=0) / 372 clock cycles(S=372) (SCMR.BCP2=1) */
#  define R_SCI_SMR_SMCI_BCP_11                           (3 << R_SCI_SMR_SMCI_BCP_SHIFT)  /* 512 clock cycles(S=512) (SCMR.BCP2=0) / 256 clock cycles(S=256) (SCMR.BCP2=1) */

#define R_SCI_SMR_SMCI_CKS_SHIFT                  (0)  /* Clock Select */
#define R_SCI_SMR_SMCI_CKS_MASK                   0x3
#  define R_SCI_SMR_SMCI_CKS_00                           (0 << R_SCI_SMR_SMCI_CKS_SHIFT)  /* PCLK clock */
#  define R_SCI_SMR_SMCI_CKS_01                           (1 << R_SCI_SMR_SMCI_CKS_SHIFT)  /* PCLK/4 clock */
#  define R_SCI_SMR_SMCI_CKS_10                           (2 << R_SCI_SMR_SMCI_CKS_SHIFT)  /* PCLK/16 clock */
#  define R_SCI_SMR_SMCI_CKS_11                           (3 << R_SCI_SMR_SMCI_CKS_SHIFT)  /* PCLK/64 clock */

/* BRR Register bit definitions */
#define R_SCI_BRR_BRR_SHIFT                       (0)  /* BRR is an 8-bit register that adjusts the bit rate. */
#define R_SCI_BRR_BRR_MASK                        0xff

/* SCR Register bit definitions */
#define R_SCI_SCR_TIE                             (1 << 7)  /* Transmit Interrupt Enable */

#define R_SCI_SCR_RIE                             (1 << 6)  /* Receive Interrupt Enable */

#define R_SCI_SCR_TE                              (1 << 5)  /* Transmit Enable */

#define R_SCI_SCR_RE                              (1 << 4)  /* Receive Enable */

#define R_SCI_SCR_MPIE                            (1 << 3)  /* Multi-Processor Interrupt Enable(Valid in asynchronous mode when SMR.MP = 1) */

#define R_SCI_SCR_TEIE                            (1 << 2)  /* Transmit End Interrupt Enable */

#define R_SCI_SCR_CKE_SHIFT                       (0)  /* Clock Enable */
#define R_SCI_SCR_CKE_MASK                        0x3
#  define R_SCI_SCR_CKE_00                                (0 << R_SCI_SCR_CKE_SHIFT)  /* The SCKn pin is available for use as an I/O port in accord with the I/O port settings.(Asynchronous mode) / The SCKn pin functions as the clock output pin(Clock synchronous mode) */
#  define R_SCI_SCR_CKE_01                                (1 << R_SCI_SCR_CKE_SHIFT)  /* The clock with the same frequency as the bit rate is output from the SCKn pin.(Asynchronous mode) / The SCKn pin functions as the clock output pin(Clock synchronous mode) */

/* SCR_SMCI Register bit definitions */
#define R_SCI_SCR_SMCI_TIE                        (1 << 7)  /* Transmit Interrupt Enable */

#define R_SCI_SCR_SMCI_RIE                        (1 << 6)  /* Receive Interrupt Enable */

#define R_SCI_SCR_SMCI_TE                         (1 << 5)  /* Transmit Enable */

#define R_SCI_SCR_SMCI_RE                         (1 << 4)  /* Receive Enable */

#define R_SCI_SCR_SMCI_MPIE                       (1 << 3)  /* Multi-Processor Interrupt Enable */

#define R_SCI_SCR_SMCI_TEIE                       (1 << 2)  /* Transmit End Interrupt Enable */

#define R_SCI_SCR_SMCI_CKE_SHIFT                  (0)  /* Clock Enable */
#define R_SCI_SCR_SMCI_CKE_MASK                   0x3
#  define R_SCI_SCR_SMCI_CKE_00                           (0 << R_SCI_SCR_SMCI_CKE_SHIFT)  /* Output disabled(SMR_SMCI.GM=0) / Output fixed low(SMR_SMCI.GM=1) */
#  define R_SCI_SCR_SMCI_CKE_01                           (1 << R_SCI_SCR_SMCI_CKE_SHIFT)  /* Clock Output */
#  define R_SCI_SCR_SMCI_CKE_10                           (2 << R_SCI_SCR_SMCI_CKE_SHIFT)  /* Setting prohibited(SMR_SMCI.GM=0) / Output fixed High(SMR_SMCI.GM=1) */
#  define R_SCI_SCR_SMCI_CKE_11                           (3 << R_SCI_SCR_SMCI_CKE_SHIFT)  /* Setting prohibited(SMR_SMCI.GM=0) / Clock Output(SMR_SMCI.GM=1) */

/* TDR Register bit definitions */
#define R_SCI_TDR_TDR_SHIFT                       (0)  /* TDR is an 8-bit register that stores transmit data. */
#define R_SCI_TDR_TDR_MASK                        0xff

/* SSR Register bit definitions */
#define R_SCI_SSR_TDRE                            (1 << 7)  /* Transmit Data Empty Flag */

#define R_SCI_SSR_RDRF                            (1 << 6)  /* Receive Data Full Flag */

#define R_SCI_SSR_ORER                            (1 << 5)  /* Overrun Error Flag */

#define R_SCI_SSR_FER                             (1 << 4)  /* Framing Error Flag */

#define R_SCI_SSR_PER                             (1 << 3)  /* Parity Error Flag */

#define R_SCI_SSR_TEND                            (1 << 2)  /* Transmit End Flag */

#define R_SCI_SSR_MPB                             (1 << 1)  /* Multi-Processor */

#define R_SCI_SSR_MPBT                            (1 << 0)  /* Multi-Processor Bit Transfer */

/* SSR_FIFO Register bit definitions */
#define R_SCI_SSR_FIFO_TDFE                       (1 << 7)  /* Transmit FIFO data empty flag */

#define R_SCI_SSR_FIFO_RDF                        (1 << 6)  /* Receive FIFO data full flag */

#define R_SCI_SSR_FIFO_ORER                       (1 << 5)  /* Overrun Error Flag */

#define R_SCI_SSR_FIFO_FER                        (1 << 4)  /* Framing Error Flag */

#define R_SCI_SSR_FIFO_PER                        (1 << 3)  /* Parity Error Flag */

#define R_SCI_SSR_FIFO_TEND                       (1 << 2)  /* Transmit End Flag */

#define R_SCI_SSR_FIFO_DR                         (1 << 0)  /* Receive Data Ready flag(Valid only in asynchronous mode(including multi-processor) and FIFO selected) */

/* SSR_MANC Register bit definitions */
#define R_SCI_SSR_MANC_TDRE                       (1 << 7)  /* Transmit Data Empty Flag */

#define R_SCI_SSR_MANC_RDRF                       (1 << 6)  /* Receive Data Full Flag */

#define R_SCI_SSR_MANC_ORER                       (1 << 5)  /* Overrun Error Flag */

#define R_SCI_SSR_MANC_FER                        (1 << 4)  /* Framing Error Flag */

#define R_SCI_SSR_MANC_PER                        (1 << 3)  /* Parity Error Flag */

#define R_SCI_SSR_MANC_TEND                       (1 << 2)  /* Transmit End Flag */

#define R_SCI_SSR_MANC_MPB                        (1 << 1)  /* Multi-Processor */

#define R_SCI_SSR_MANC_MER                        (1 << 0)  /* Manchester Error Flag Valid for Manchester mode only */

/* SSR_SMCI Register bit definitions */
#define R_SCI_SSR_SMCI_TDRE                       (1 << 7)  /* Transmit Data Empty Flag */

#define R_SCI_SSR_SMCI_RDRF                       (1 << 6)  /* Receive Data Full Flag */

#define R_SCI_SSR_SMCI_ORER                       (1 << 5)  /* Overrun Error Flag */

#define R_SCI_SSR_SMCI_ERS                        (1 << 4)  /* Error Signal Status Flag */

#define R_SCI_SSR_SMCI_PER                        (1 << 3)  /* Parity Error Flag */

#define R_SCI_SSR_SMCI_TEND                       (1 << 2)  /* Transmit End Flag */

#define R_SCI_SSR_SMCI_MPB                        (1 << 1)  /* Multi-ProcessorThis bit should be 0 in smart card interface mode. */

#define R_SCI_SSR_SMCI_MPBT                       (1 << 0)  /* Multi-Processor Bit TransferThis bit should be 0 in smart card interface mode. */

/* RDR Register bit definitions */
#define R_SCI_RDR_RDR_SHIFT                       (0)  /* RDR is an 8-bit register that stores receive data. */
#define R_SCI_RDR_RDR_MASK                        0xff

/* SCMR Register bit definitions */
#define R_SCI_SCMR_BCP2                           (1 << 7)  /* Base Clock Pulse 2Selects the number of base clock cycles in combination with the SMR.BCP[1:0] bits */

#define R_SCI_SCMR_CHR1                           (1 << 4)  /* Character Length 1(Only valid in asynchronous mode) */

#define R_SCI_SCMR_SDIR                           (1 << 3)  /* Transmitted/Received Data Transfer DirectionNOTE: The setting is invalid and a fixed data length of 8 bits is used in modes other than asynchronous mode.Set this bit to 1 if operation is to be in simple I2C mode. */

#define R_SCI_SCMR_SINV                           (1 << 2)  /* Transmitted/Received Data InvertSet this bit to 0 if operation is to be in simple I2C mode. */

#define R_SCI_SCMR_SMIF                           (1 << 0)  /* Smart Card Interface Mode Select */

/* SEMR Register bit definitions */
#define R_SCI_SEMR_RXDESEL                        (1 << 7)  /* Asynchronous Start Bit Edge Detection Select(Valid only in asynchronous mode) */

#define R_SCI_SEMR_BGDM                           (1 << 6)  /* Baud Rate Generator Double-Speed Mode Select(Only valid the CKE[1] bit in SCR is 0 in asynchronous mode). */

#define R_SCI_SEMR_NFEN                           (1 << 5)  /* Digital Noise Filter Function Enable(The NFEN bit should be 0 without simple I2C mode and asynchronous mode.)In asynchronous mode, for RXDn input only. In simple I2C mode, for RXDn/TxDn input. */

#define R_SCI_SEMR_ABCS                           (1 << 4)  /* Asynchronous Mode Base Clock Select(Valid only in asynchronous mode) */

#define R_SCI_SEMR_ABCSE                          (1 << 3)  /* Asynchronous Mode Extended Base Clock Select 1(Valid only in asynchronous mode and SCR.CKE[1]=0) */

#define R_SCI_SEMR_BRME                           (1 << 2)  /* Bit Rate Modulation Enable */

#define R_SCI_SEMR_PADIS                          (1 << 1)  /* Preamble function Disable (Valid only in asynchronous mode).  */

#define R_SCI_SEMR_ACS0                           (1 << 0)  /* Asynchronous Mode Clock Source Select (Valid only in asynchronous mode).  */

/* SNFR Register bit definitions */
#define R_SCI_SNFR_NFCS_SHIFT                     (0)  /* Noise Filter Clock Select */
#define R_SCI_SNFR_NFCS_MASK                      0x7
#  define R_SCI_SNFR_NFCS_000                             (0 << R_SCI_SNFR_NFCS_SHIFT)  /* The clock signal divided by 1 is used with the noise filter.(In asynchronous mode) */
#  define R_SCI_SNFR_NFCS_001                             (1 << R_SCI_SNFR_NFCS_SHIFT)  /* The clock signal divided by 1 is used with the noise filter.(In simple I2C mode) */
#  define R_SCI_SNFR_NFCS_010                             (2 << R_SCI_SNFR_NFCS_SHIFT)  /* The clock signal divided by 2 is used with the noise filter.(In simple I2C mode) */
#  define R_SCI_SNFR_NFCS_011                             (3 << R_SCI_SNFR_NFCS_SHIFT)  /* The clock signal divided by 4 is used with the noise filter.(In simple I2C mode) */
#  define R_SCI_SNFR_NFCS_100                             (4 << R_SCI_SNFR_NFCS_SHIFT)  /* The clock signal divided by 8 is used with the noise filter.(In simple I2C mode) */

/* SIMR1 Register bit definitions */
#define R_SCI_SIMR1_IICDL_SHIFT                   (3)  /* SDA Delay Output SelectCycles below are of the clock signal from the on-chip baud rate generator. */
#define R_SCI_SIMR1_IICDL_MASK                    0xf8
#  define R_SCI_SIMR1_IICDL_00000                         (0 << R_SCI_SIMR1_IICDL_SHIFT)  /* No output delay */

#define R_SCI_SIMR1_IICM                          (1 << 0)  /* Simple I2C Mode Select */

/* SIMR2 Register bit definitions */
#define R_SCI_SIMR2_IICACKT                       (1 << 5)  /* ACK Transmission Data */

#define R_SCI_SIMR2_IICCSC                        (1 << 1)  /* Clock Synchronization */

#define R_SCI_SIMR2_IICINTM                       (1 << 0)  /* I2C Interrupt Mode Select */

/* SIMR3 Register bit definitions */
#define R_SCI_SIMR3_IICSCLS_SHIFT                 (6)  /* SCL Output Select */
#define R_SCI_SIMR3_IICSCLS_MASK                  0xc0
#  define R_SCI_SIMR3_IICSCLS_00                          (0 << R_SCI_SIMR3_IICSCLS_SHIFT)  /* Serial clock output */
#  define R_SCI_SIMR3_IICSCLS_01                          (1 << R_SCI_SIMR3_IICSCLS_SHIFT)  /* Generate a start, restart, or stop condition. */
#  define R_SCI_SIMR3_IICSCLS_10                          (2 << R_SCI_SIMR3_IICSCLS_SHIFT)  /* Output the low level on the SSCLn pin. */
#  define R_SCI_SIMR3_IICSCLS_11                          (3 << R_SCI_SIMR3_IICSCLS_SHIFT)  /* Place the SSCLn pin in the high-impedance state. */

#define R_SCI_SIMR3_IICSDAS_SHIFT                 (4)  /* SDA Output Select */
#define R_SCI_SIMR3_IICSDAS_MASK                  0x30
#  define R_SCI_SIMR3_IICSDAS_00                          (0 << R_SCI_SIMR3_IICSDAS_SHIFT)  /* Serial data output */
#  define R_SCI_SIMR3_IICSDAS_01                          (1 << R_SCI_SIMR3_IICSDAS_SHIFT)  /* Generate a start, restart, or stop condition. */
#  define R_SCI_SIMR3_IICSDAS_10                          (2 << R_SCI_SIMR3_IICSDAS_SHIFT)  /* Output the low level on the SSDAn pin. */
#  define R_SCI_SIMR3_IICSDAS_11                          (3 << R_SCI_SIMR3_IICSDAS_SHIFT)  /* Place the SSDAn pin in the high-impedance state. */

#define R_SCI_SIMR3_IICSTIF                       (1 << 3)  /* Issuing of Start, Restart, or Stop Condition Completed Flag(When 0 is written to IICSTIF, it is cleared to 0.) */

#define R_SCI_SIMR3_IICSTPREQ                     (1 << 2)  /* Stop Condition Generation */

#define R_SCI_SIMR3_IICRSTAREQ                    (1 << 1)  /* Restart Condition Generation */

#define R_SCI_SIMR3_IICSTAREQ                     (1 << 0)  /* Start Condition Generation */

/* SISR Register bit definitions */
#define R_SCI_SISR_IICACKR                        (1 << 0)  /* ACK Reception Data Flag */

/* SPMR Register bit definitions */
#define R_SCI_SPMR_CKPH                           (1 << 7)  /* Clock Phase Select */

#define R_SCI_SPMR_CKPOL                          (1 << 6)  /* Clock Polarity Select */

#define R_SCI_SPMR_MFF                            (1 << 4)  /* Mode Fault Flag */

#define R_SCI_SPMR_CSTPEN                         (1 << 3)  /* CTS external pin Enable */

#define R_SCI_SPMR_MSS                            (1 << 2)  /* Master Slave Select */

#define R_SCI_SPMR_CTSE                           (1 << 1)  /* CTS Enable */

#define R_SCI_SPMR_SSE                            (1 << 0)  /* SSn Pin Function Enable */

/* TDRHL Register bit definitions */
#define R_SCI_TDRHL_TDRHL_SHIFT                   (0)  /* TDRHL is a 16-bit register that stores transmit data. */
#define R_SCI_TDRHL_TDRHL_MASK                    0xffff

/* FTDRHL Register bit definitions */
#define R_SCI_FTDRHL_MPBT                         (1 << 9)  /* Multi-processor transfer bit flag(Valid only in asynchronous mode and SMR.MP=1 and FIFO selected) */

#define R_SCI_FTDRHL_TDAT_SHIFT                   (0)  /* Serial transmit data (Valid only in asynchronous mode(including multi-processor) or clock synchronous mode, and FIFO selected) */
#define R_SCI_FTDRHL_TDAT_MASK                    0x1ff

/* FTDRH Register bit definitions */
#define R_SCI_FTDRH_MPBT                          (1 << 1)  /* Multi-processor transfer bit flag(Valid only in asynchronous mode and SMR.MP=1 and FIFO selected) */

#define R_SCI_FTDRH_TDATH                         (1 << 0)  /* Serial transmit data (b8) (Valid only in asynchronous mode(including multi-processor) or clock synchronous mode, and FIFO selected) */

/* FTDRL Register bit definitions */
#define R_SCI_FTDRL_TDATL_SHIFT                   (0)  /* Serial transmit data(b7-b0) (Valid only in asynchronous mode(including multi-processor) or clock synchronous mode, and FIFO selected) */
#define R_SCI_FTDRL_TDATL_MASK                    0xff

/* RDRHL Register bit definitions */
#define R_SCI_RDRHL_RDRHL_SHIFT                   (0)  /* RDRHL is an 16-bit register that stores receive data. */
#define R_SCI_RDRHL_RDRHL_MASK                    0xffff

/* FRDRHL Register bit definitions */
#define R_SCI_FRDRHL_RDF                          (1 << 14)  /* Receive FIFO data full flag(It is same as SSR.RDF) */

#define R_SCI_FRDRHL_ORER                         (1 << 13)  /* Overrun error flag(It is same as SSR.ORER) */

#define R_SCI_FRDRHL_FER                          (1 << 12)  /* Framing error flag */

#define R_SCI_FRDRHL_PER                          (1 << 11)  /* Parity error flag */

#define R_SCI_FRDRHL_DR                           (1 << 10)  /* Receive data ready flag(It is same as SSR.DR) */

#define R_SCI_FRDRHL_MPB                          (1 << 9)  /* Multi-processor bit flag(Valid only in asynchronous mode with SMR.MP=1 and FIFO selected) It can read multi-processor bit corresponded to serial receive data(RDATA[8:0]) */

#define R_SCI_FRDRHL_RDAT_SHIFT                   (0)  /* Serial receive data(Valid only in asynchronous mode(including multi-processor) or clock synchronous mode, and FIFO selected) */
#define R_SCI_FRDRHL_RDAT_MASK                    0x1ff

/* TDRHL_MAN Register bit definitions */
#define R_SCI_TDRHL_MAN_TDAT_SHIFT                (0)  /* Serial transmit data */
#define R_SCI_TDRHL_MAN_TDAT_MASK                 0x1ff

#define R_SCI_TDRHL_MAN_MPBT                      (1 << 9)  /* Multi-processor Transfer Bit Flag */

#define R_SCI_TDRHL_MAN_TSYNC                     (1 << 12)  /* Transmit SYNC data bit */

/* RDRHL_MAN Register bit definitions */
#define R_SCI_RDRHL_MAN_RDAT_SHIFT                (0)  /* Serial Receive Data */
#define R_SCI_RDRHL_MAN_RDAT_MASK                 0x1ff

#define R_SCI_RDRHL_MAN_MPB                       (1 << 9)  /* Multi-processor Bit */

#define R_SCI_RDRHL_MAN_RSYNC                     (1 << 12)  /* Receive SYNC data bit */

/* FRDRH Register bit definitions */
#define R_SCI_FRDRH_RDF                           (1 << 6)  /* Receive FIFO data full flag(It is same as SSR.RDF) */

#define R_SCI_FRDRH_ORER                          (1 << 5)  /* Overrun error flag(It is same as SSR.ORER) */

#define R_SCI_FRDRH_FER                           (1 << 4)  /* Framing error flag */

#define R_SCI_FRDRH_PER                           (1 << 3)  /* Parity error flag */

#define R_SCI_FRDRH_DR                            (1 << 2)  /* Receive data ready flag(It is same as SSR.DR) */

#define R_SCI_FRDRH_MPB                           (1 << 1)  /* Multi-processor bit flag(Valid only in asynchronous mode with SMR.MP=1 and FIFO selected) It can read multi-processor bit corresponded to serial receive data(RDATA[8:0]) */

#define R_SCI_FRDRH_RDATH                         (1 << 0)  /* Serial receive data(b8)(Valid only in asynchronous mode(including multi-processor) or clock synchronous mode, and FIFO selected) */

/* FRDRL Register bit definitions */
#define R_SCI_FRDRL_RDATL_SHIFT                   (0)  /* Serial receive data(Valid only in asynchronous mode(including multi-processor) or clock synchronous mode, and FIFO selected)NOTE: When reading both of FRDRH register and FRDRL register, please read by an order of the FRDRH register and the FRDRL register. */
#define R_SCI_FRDRL_RDATL_MASK                    0xff

/* MDDR Register bit definitions */
#define R_SCI_MDDR_MDDR_SHIFT                     (0)  /* MDDR corrects the bit rate adjusted by the BRR register. */
#define R_SCI_MDDR_MDDR_MASK                      0xff

/* DCCR Register bit definitions */
#define R_SCI_DCCR_DCME                           (1 << 7)  /* Data Compare Match Enable(Valid only in asynchronous mode(including multi-processor)  */

#define R_SCI_DCCR_IDSEL                          (1 << 6)  /* ID frame select(Valid only in asynchronous mode(including multi-processor)  */

#define R_SCI_DCCR_DFER                           (1 << 4)  /* Data Compare Match Framing Error Flag */

#define R_SCI_DCCR_DPER                           (1 << 3)  /* Data Compare Match Parity Error Flag */

#define R_SCI_DCCR_DCMF                           (1 << 0)  /* Data Compare Match Flag */

/* FCR Register bit definitions */
#define R_SCI_FCR_RSTRG_SHIFT                     (12)  /* RTS Output Active Trigger Number Select(Valid only in asynchronous mode(including multi-processor) or clock synchronous mode) */
#define R_SCI_FCR_RSTRG_MASK                      0xf000
#  define R_SCI_FCR_RSTRG_0000                            (0 << R_SCI_FCR_RSTRG_SHIFT)  /* Trigger number 0 */

#define R_SCI_FCR_RTRG_SHIFT                      (8)  /* Receive FIFO data trigger number(Valid only in asynchronous mode(including multi-processor) or clock synchronous mode) */
#define R_SCI_FCR_RTRG_MASK                       0xf00
#  define R_SCI_FCR_RTRG_0000                             (0 << R_SCI_FCR_RTRG_SHIFT)  /* Trigger number 0 */

#define R_SCI_FCR_TTRG_SHIFT                      (4)  /* Transmit FIFO data trigger number(Valid only in asynchronous mode(including multi-processor) or clock synchronous mode) */
#define R_SCI_FCR_TTRG_MASK                       0xf0
#  define R_SCI_FCR_TTRG_0000                             (0 << R_SCI_FCR_TTRG_SHIFT)  /* Trigger number 0 */

#define R_SCI_FCR_DRES                            (1 << 3)  /* Receive data ready error select bit(When detecting a reception data ready, the interrupt request is selected.) */

#define R_SCI_FCR_TFRST                           (1 << 2)  /* Transmit FIFO Data Register Reset(Valid only in FCR.FM=1) */

#define R_SCI_FCR_RFRST                           (1 << 1)  /* Receive FIFO Data Register Reset(Valid only in FCR.FM=1) */

#define R_SCI_FCR_FM                              (1 << 0)  /* FIFO Mode Select(Valid only in asynchronous mode(including multi-processor) or clock synchronous mode) */

/* FDR Register bit definitions */
#define R_SCI_FDR_T_SHIFT                         (8)  /* Transmit FIFO Data CountIndicate the quantity of non-transmit data stored in FTDRH and FTDRL(Valid only in asynchronous mode(including multi-processor) or clock synchronous mode, while FCR.FM=1) */
#define R_SCI_FDR_T_MASK                          0x1f00

#define R_SCI_FDR_R_SHIFT                         (0)  /* Receive FIFO Data CountIndicate the quantity of receive data stored in FRDRH and FRDRL(Valid only in asynchronous mode(including multi-processor) or clock synchronous mode, while FCR.FM=1) */
#define R_SCI_FDR_R_MASK                          0x1f

/* LSR Register bit definitions */
#define R_SCI_LSR_PNUM_SHIFT                      (8)  /* Parity Error CountIndicates the quantity of data with a parity error among the receive data stored in the receive FIFO data register (FRDRH and FRDRL). */
#define R_SCI_LSR_PNUM_MASK                       0x1f00

#define R_SCI_LSR_FNUM_SHIFT                      (2)  /* Framing Error CountIndicates the quantity of data with a framing error among the receive data stored in the receive FIFO data register (FRDRH and FRDRL). */
#define R_SCI_LSR_FNUM_MASK                       0x7c

#define R_SCI_LSR_ORER                            (1 << 0)  /* Overrun Error Flag (Valid only in asynchronous mode(including multi-processor) or clock synchronous mode, and FIFO selected) */

/* CDR Register bit definitions */
#define R_SCI_CDR_CMPD_SHIFT                      (0)  /* Compare Match DataCompare data pattern for address match wake-up function  */
#define R_SCI_CDR_CMPD_MASK                       0x1ff

/* SPTR Register bit definitions */
#define R_SCI_SPTR_SPB2IO                         (1 << 2)  /* Serial port break I/O bit(It's selected whether the value of SPB2DT is output to TxD terminal.) */

#define R_SCI_SPTR_SPB2DT                         (1 << 1)  /* Serial port break data select bit(The output level of TxD terminal is selected when SCR.TE = 0.) */

#define R_SCI_SPTR_RXDMON                         (1 << 0)  /* Serial input data monitor bit(The state of the RXD terminal is shown.) */

#define R_SCI_SPTR_RINV                           (1 << 4)  /* RXD invert bit */

#define R_SCI_SPTR_TINV                           (1 << 5)  /* TXD invert bit */

#define R_SCI_SPTR_ASEN                           (1 << 6)  /* Adjust receive sampling timing enable */

#define R_SCI_SPTR_ATEN                           (1 << 7)  /* Adjust transmit timing enable */

/* ACTR Register bit definitions */
#define R_SCI_ACTR_AST_SHIFT                      (0)  /* Adjustment value for receive Sampling Timing */
#define R_SCI_ACTR_AST_MASK                       0x7

#define R_SCI_ACTR_AJD                            (1 << 3)  /* Adjustment Direction for receive sampling timing */

#define R_SCI_ACTR_ATT_SHIFT                      (4)  /* Adjustment value for Transmit timing */
#define R_SCI_ACTR_ATT_MASK                       0x70

#define R_SCI_ACTR_AET                            (1 << 7)  /* Adjustment edge for transmit timing */

/* ESMER Register bit definitions */
#define R_SCI_ESMER_ESME                          (1 << 0)  /* Extended Serial Mode Enable */

/* CR0 Register bit definitions */
#define R_SCI_CR0_SFSF                            (1 << 1)  /* Start Frame Status Flag */

#define R_SCI_CR0_RXDSF                           (1 << 2)  /* RXDXn Input Status Flag */

#define R_SCI_CR0_BRME                            (1 << 3)  /* Bit Rate Measurement Enable */

/* CR1 Register bit definitions */
#define R_SCI_CR1_BFE                             (1 << 0)  /* Break Field Enable */

#define R_SCI_CR1_CF0RE                           (1 << 1)  /* Control Field 0 Reception Enable */

#define R_SCI_CR1_CF1DS_SHIFT                     (2)  /* Control Field 1 Data Register Select */
#define R_SCI_CR1_CF1DS_MASK                      0xc
#  define R_SCI_CR1_CF1DS_00                              (0 << R_SCI_CR1_CF1DS_SHIFT)  /* Selects comparison with the value in PCF1DR. */
#  define R_SCI_CR1_CF1DS_01                              (1 << R_SCI_CR1_CF1DS_SHIFT)  /* Selects comparison with the value in SCF1DR. */
#  define R_SCI_CR1_CF1DS_10                              (2 << R_SCI_CR1_CF1DS_SHIFT)  /* Selects comparison with the values in PCF1DR and SCF1DR. */
#  define R_SCI_CR1_CF1DS_11                              (3 << R_SCI_CR1_CF1DS_SHIFT)  /* Setting prohibited. */

#define R_SCI_CR1_PIBE                            (1 << 4)  /* Priority Interrupt Bit Enable */

#define R_SCI_CR1_PIBS_SHIFT                      (5)  /* Priority Interrupt Bit Select */
#define R_SCI_CR1_PIBS_MASK                       0xe0
#  define R_SCI_CR1_PIBS_000                              (0 << R_SCI_CR1_PIBS_SHIFT)  /* 0th bit of Control Field 1 */
#  define R_SCI_CR1_PIBS_001                              (1 << R_SCI_CR1_PIBS_SHIFT)  /* 1st bit of Control Field 1 */
#  define R_SCI_CR1_PIBS_010                              (2 << R_SCI_CR1_PIBS_SHIFT)  /* 2nd bit of Control Field 1 */
#  define R_SCI_CR1_PIBS_011                              (3 << R_SCI_CR1_PIBS_SHIFT)  /* 3rd bit of Control Field 1 */
#  define R_SCI_CR1_PIBS_100                              (4 << R_SCI_CR1_PIBS_SHIFT)  /* 4th bit of Control Field 1 */
#  define R_SCI_CR1_PIBS_101                              (5 << R_SCI_CR1_PIBS_SHIFT)  /* 5th bit of Control Field 1 */
#  define R_SCI_CR1_PIBS_110                              (6 << R_SCI_CR1_PIBS_SHIFT)  /* 6th bit of Control Field 1 */
#  define R_SCI_CR1_PIBS_111                              (7 << R_SCI_CR1_PIBS_SHIFT)  /* 7th bit of Control Field 1 */

/* CR2 Register bit definitions */
#define R_SCI_CR2_DFCS_SHIFT                      (0)  /* RXDXn Signal Digital Filter Clock Select */
#define R_SCI_CR2_DFCS_MASK                       0x7
#  define R_SCI_CR2_DFCS_000                              (0 << R_SCI_CR2_DFCS_SHIFT)  /* Filter is disabled. */
#  define R_SCI_CR2_DFCS_001                              (1 << R_SCI_CR2_DFCS_SHIFT)  /* Filter clock is SCI base clock */
#  define R_SCI_CR2_DFCS_010                              (2 << R_SCI_CR2_DFCS_SHIFT)  /* Filter clock is PCLK/8 */
#  define R_SCI_CR2_DFCS_011                              (3 << R_SCI_CR2_DFCS_SHIFT)  /* Filter clock is PCLK/16 */
#  define R_SCI_CR2_DFCS_100                              (4 << R_SCI_CR2_DFCS_SHIFT)  /* Filter clock is PCLK/32 */
#  define R_SCI_CR2_DFCS_101                              (5 << R_SCI_CR2_DFCS_SHIFT)  /* Filter clock is PCLK/64 */
#  define R_SCI_CR2_DFCS_110                              (6 << R_SCI_CR2_DFCS_SHIFT)  /* Filter clock is PCLK/128 */
#  define R_SCI_CR2_DFCS_111                              (7 << R_SCI_CR2_DFCS_SHIFT)  /* Setting prohibited */

#define R_SCI_CR2_BCCS_SHIFT                      (4)  /* Bus Collision Detection Clock Select */
#define R_SCI_CR2_BCCS_MASK                       0x30
#  define R_SCI_CR2_BCCS_00                               (0 << R_SCI_CR2_BCCS_SHIFT)  /* SCI base clock */
#  define R_SCI_CR2_BCCS_01                               (1 << R_SCI_CR2_BCCS_SHIFT)  /* SCI base clock frequency divided by 2 */
#  define R_SCI_CR2_BCCS_10                               (2 << R_SCI_CR2_BCCS_SHIFT)  /* SCI base clock frequency divided by 4 */
#  define R_SCI_CR2_BCCS_11                               (3 << R_SCI_CR2_BCCS_SHIFT)  /* Setting prohibited */

#define R_SCI_CR2_RTS_SHIFT                       (6)  /* RXDXn Reception Sampling Timing Select */
#define R_SCI_CR2_RTS_MASK                        0xc0
#  define R_SCI_CR2_RTS_00                                (0 << R_SCI_CR2_RTS_SHIFT)  /* Rising edge of the 8th cycle of SCI base clock */
#  define R_SCI_CR2_RTS_01                                (1 << R_SCI_CR2_RTS_SHIFT)  /* Rising edge of the 10th cycle of SCI base clock */
#  define R_SCI_CR2_RTS_10                                (2 << R_SCI_CR2_RTS_SHIFT)  /* Rising edge of the 12th cycle of SCI base clock */
#  define R_SCI_CR2_RTS_11                                (3 << R_SCI_CR2_RTS_SHIFT)  /* Rising edge of the 14th cycle of SCI base clock */

/* CR3 Register bit definitions */
#define R_SCI_CR3_SDST                            (1 << 0)  /* Start Frame Detection Start */

/* PCR Register bit definitions */
#define R_SCI_PCR_TXDXPS                          (1 << 0)  /* TXDXn Signal Polarity Select */

#define R_SCI_PCR_RXDXPS                          (1 << 1)  /* RXDXn Signal Polarity Select */

#define R_SCI_PCR_SHARPS                          (1 << 4)  /* TXDXn/RXDXn Pin Multiplexing Select */

/* ICR Register bit definitions */
#define R_SCI_ICR_BFDIE                           (1 << 0)  /* Break Field Low Width Detected Interrupt Enable */

#define R_SCI_ICR_CF0MIE                          (1 << 1)  /* Control Field 0 Match Detected Interrupt Enable */

#define R_SCI_ICR_CF1MIE                          (1 << 2)  /* Control Field 1 Match Detected Interrupt Enable */

#define R_SCI_ICR_PIBDIE                          (1 << 3)  /* Priority Interrupt Bit Detected Interrupt Enable */

#define R_SCI_ICR_BCDIE                           (1 << 4)  /* Bus Collision Detected Interrupt Enable */

#define R_SCI_ICR_AEDIE                           (1 << 5)  /* Valid Edge Detected Interrupt Enable */

/* STR Register bit definitions */
#define R_SCI_STR_BFDF                            (1 << 0)  /* Break Field Low Width Detection Flag */

#define R_SCI_STR_CF0MF                           (1 << 1)  /* Control Field 0 Match Flag */

#define R_SCI_STR_CF1MF                           (1 << 2)  /* Control Field 1 Match Flag */

#define R_SCI_STR_PIBDF                           (1 << 3)  /* Priority Interrupt Bit Detection Flag */

#define R_SCI_STR_BCDF                            (1 << 4)  /* Bus Collision Detected Flag */

#define R_SCI_STR_AEDF                            (1 << 5)  /* Valid Edge Detection Flag */

/* STCR Register bit definitions */
#define R_SCI_STCR_BFDCL                          (1 << 0)  /* BFDF Clear */

#define R_SCI_STCR_CF0MCL                         (1 << 1)  /* CF0MF Clear */

#define R_SCI_STCR_CF1MCL                         (1 << 2)  /* CF1MF Clear */

#define R_SCI_STCR_PIBDCL                         (1 << 3)  /* PIBDF Clear */

#define R_SCI_STCR_BCDCL                          (1 << 4)  /* BCDF Clear */

#define R_SCI_STCR_AEDCL                          (1 << 5)  /* AEDF Clear */

/* CF0CR Register bit definitions */
#define R_SCI_CF0CR_CF0CE0                        (1 << 0)  /* Control Field 0 Bit 0 Compare Enable */

#define R_SCI_CF0CR_CF0CE1                        (1 << 1)  /* Control Field 1 Bit 0 Compare Enable */

#define R_SCI_CF0CR_CF0CE2                        (1 << 2)  /* Control Field 2 Bit 0 Compare Enable */

#define R_SCI_CF0CR_CF0CE3                        (1 << 3)  /* Control Field 3 Bit 0 Compare Enable */

#define R_SCI_CF0CR_CF0CE4                        (1 << 4)  /* Control Field 4 Bit 0 Compare Enable */

#define R_SCI_CF0CR_CF0CE5                        (1 << 5)  /* Control Field 5 Bit 0 Compare Enable */

#define R_SCI_CF0CR_CF0CE6                        (1 << 6)  /* Control Field 6 Bit 0 Compare Enable */

#define R_SCI_CF0CR_CF0CE7                        (1 << 7)  /* Control Field 7 Bit 0 Compare Enable */

/* CF1CR Register bit definitions */
#define R_SCI_CF1CR_CF1CE0                        (1 << 0)  /* Control Field 1 Bit 0 Compare Enable */

#define R_SCI_CF1CR_CF1CE1                        (1 << 1)  /* Control Field 1 Bit 1 Compare Enable */

#define R_SCI_CF1CR_CF1CE2                        (1 << 2)  /* Control Field 1 Bit 2 Compare Enable */

#define R_SCI_CF1CR_CF1CE3                        (1 << 3)  /* Control Field 1 Bit 3 Compare Enable */

#define R_SCI_CF1CR_CF1CE4                        (1 << 4)  /* Control Field 1 Bit 4 Compare Enable */

#define R_SCI_CF1CR_CF1CE5                        (1 << 5)  /* Control Field 1 Bit 5 Compare Enable */

#define R_SCI_CF1CR_CF1CE6                        (1 << 6)  /* Control Field 1 Bit 6 Compare Enable */

#define R_SCI_CF1CR_CF1CE7                        (1 << 7)  /* Control Field 1 Bit 7 Compare Enable */

/* TCR Register bit definitions */
#define R_SCI_TCR_TCST                            (1 << 0)  /* Timer Count Start */

/* TMR Register bit definitions */
#define R_SCI_TMR_TOMS_SHIFT                      (0)  /* Timer Operating Mode Select */
#define R_SCI_TMR_TOMS_MASK                       0x3
#  define R_SCI_TMR_TOMS_00                               (0 << R_SCI_TMR_TOMS_SHIFT)  /* Timer mode */
#  define R_SCI_TMR_TOMS_01                               (1 << R_SCI_TMR_TOMS_SHIFT)  /* Break Field low width determination mode */
#  define R_SCI_TMR_TOMS_10                               (2 << R_SCI_TMR_TOMS_SHIFT)  /* Break Field low width output mode */
#  define R_SCI_TMR_TOMS_11                               (3 << R_SCI_TMR_TOMS_SHIFT)  /* Setting prohibited */

#define R_SCI_TMR_TWRC                            (1 << 3)  /* Counter Write Control */

#define R_SCI_TMR_TCSS_SHIFT                      (4)  /* Timer Count Clock Source Select */
#define R_SCI_TMR_TCSS_MASK                       0x70
#  define R_SCI_TMR_TCSS_000                              (0 << R_SCI_TMR_TCSS_SHIFT)  /* PCLK */
#  define R_SCI_TMR_TCSS_001                              (1 << R_SCI_TMR_TCSS_SHIFT)  /* PCLK/2 */
#  define R_SCI_TMR_TCSS_010                              (2 << R_SCI_TMR_TCSS_SHIFT)  /* PCLK/4 */
#  define R_SCI_TMR_TCSS_011                              (3 << R_SCI_TMR_TCSS_SHIFT)  /* PCLK/8 */
#  define R_SCI_TMR_TCSS_100                              (4 << R_SCI_TMR_TCSS_SHIFT)  /* PCLK/16 */
#  define R_SCI_TMR_TCSS_101                              (5 << R_SCI_TMR_TCSS_SHIFT)  /* PCLK/32 */
#  define R_SCI_TMR_TCSS_110                              (6 << R_SCI_TMR_TCSS_SHIFT)  /* PCLK/64 */
#  define R_SCI_TMR_TCSS_111                              (7 << R_SCI_TMR_TCSS_SHIFT)  /* PCLK/128 */

/* SCIMSKEN Register bit definitions */
#define R_SCI_SCIMSKEN_MSKEN                      (1 << 0)  /* SCI5 TXD Output Mask Enable */

/* MMR Register bit definitions */
#define R_SCI_MMR_MANEN                           (1 << 7)  /* Manchester Mode Enable */

#define R_SCI_MMR_SBSEL                           (1 << 6)  /* Start Bit Select */

#define R_SCI_MMR_SYNSEL                          (1 << 5)  /* SYNC Select */

#define R_SCI_MMR_SYNVAL                          (1 << 4)  /* SYNC Value Setting */

#define R_SCI_MMR_ERTEN                           (1 << 2)  /* Manchester Edge Retiming Enable */

#define R_SCI_MMR_TMPOL                           (1 << 1)  /* Polarity of Transmit Manchester Code */

#define R_SCI_MMR_RMPOL                           (1 << 0)  /* Polarity of Received Manchester Code */

/* TMPR Register bit definitions */
#define R_SCI_TMPR_TPLEN_SHIFT                    (0)  /* Transmit Preface Length */
#define R_SCI_TMPR_TPLEN_MASK                     0xf
#  define R_SCI_TMPR_TPLEN_0X0                            (0 << R_SCI_TMPR_TPLEN_SHIFT)  /* Disables the transmit preface generation */

#define R_SCI_TMPR_TPPAT_SHIFT                    (4)  /* Transmit Preface Pattern */
#define R_SCI_TMPR_TPPAT_MASK                     0x30
#  define R_SCI_TMPR_TPPAT_00                             (0 << R_SCI_TMPR_TPPAT_SHIFT)  /* All zeros */
#  define R_SCI_TMPR_TPPAT_01                             (1 << R_SCI_TMPR_TPPAT_SHIFT)  /* Zero one */
#  define R_SCI_TMPR_TPPAT_10                             (2 << R_SCI_TMPR_TPPAT_SHIFT)  /* One zero */
#  define R_SCI_TMPR_TPPAT_11                             (3 << R_SCI_TMPR_TPPAT_SHIFT)  /* All ones */

/* RMPR Register bit definitions */
#define R_SCI_RMPR_RPLEN_SHIFT                    (0)  /* Receive Preface Length */
#define R_SCI_RMPR_RPLEN_MASK                     0xf
#  define R_SCI_RMPR_RPLEN_0X0                            (0 << R_SCI_RMPR_RPLEN_SHIFT)  /* Disables the receive preface generation */

#define R_SCI_RMPR_RPPAT_SHIFT                    (4)  /* Receive Preface Pattern */
#define R_SCI_RMPR_RPPAT_MASK                     0x30
#  define R_SCI_RMPR_RPPAT_00                             (0 << R_SCI_RMPR_RPPAT_SHIFT)  /* All zeros */
#  define R_SCI_RMPR_RPPAT_01                             (1 << R_SCI_RMPR_RPPAT_SHIFT)  /* Zero one */
#  define R_SCI_RMPR_RPPAT_10                             (2 << R_SCI_RMPR_RPPAT_SHIFT)  /* One zero */
#  define R_SCI_RMPR_RPPAT_11                             (3 << R_SCI_RMPR_RPPAT_SHIFT)  /* All ones */

/* MESR Register bit definitions */
#define R_SCI_MESR_PFER                           (1 << 0)  /* Preface Error Flag */

#define R_SCI_MESR_SYER                           (1 << 1)  /* SYNC Error Flag */

#define R_SCI_MESR_SBER                           (1 << 2)  /* Start Bit Error Flag */

/* MECR Register bit definitions */
#define R_SCI_MECR_PFEREN                         (1 << 0)  /* Preface Error Flag */

#define R_SCI_MECR_SYEREN                         (1 << 1)  /* Receive SYNC Error Enable */

#define R_SCI_MECR_SBEREN                         (1 << 2)  /* Start Bit Error Enable */


/* Maximum number of channels */

#define SCI_MAX_CHANNELS    10

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_SCI_H */
