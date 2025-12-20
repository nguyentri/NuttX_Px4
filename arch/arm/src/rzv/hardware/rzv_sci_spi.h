/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv2h/rzv_sci_spi.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV2H_RZV_SCI_SPI_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV2H_RZV_SCI_SPI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SCI_B Base Addresses (SPI mode) *****************************************/

#define RZV_SCI0_BASE               0x12800C00
#define RZV_SCI1_BASE               0x12801000
#define RZV_SCI2_BASE               0x12801400
#define RZV_SCI3_BASE               0x12801800
#define RZV_SCI4_BASE               0x12801C00
#define RZV_SCI5_BASE               0x12802000
#define RZV_SCI6_BASE               0x12802400
#define RZV_SCI7_BASE               0x12802800
#define RZV_SCI8_BASE               0x12802C00
#define RZV_SCI9_BASE               0x12803000

/* SCI_B SPI Register Offsets **********************************************/

#define RZV_SCI_RDR_OFFSET          0x0000  /* Receive Data Register */
#define RZV_SCI_TDR_OFFSET          0x0004  /* Transmit Data Register */
#define RZV_SCI_CCR0_OFFSET         0x0008  /* Common Control Register 0 */
#define RZV_SCI_CCR1_OFFSET         0x000C  /* Common Control Register 1 */
#define RZV_SCI_CCR2_OFFSET         0x0010  /* Common Control Register 2 */
#define RZV_SCI_CCR3_OFFSET         0x0014  /* Common Control Register 3 */
#define RZV_SCI_CCR4_OFFSET         0x0018  /* Common Control Register 4 */
#define RZV_SCI_CESR_OFFSET         0x001C  /* Communication Enable Status Register */
#define RZV_SCI_HCR_OFFSET          0x001E  /* Half Duplex Control Register */
#define RZV_SCI_ICR_OFFSET          0x0020  /* I2C Control Register */
#define RZV_SCI_FCR_OFFSET          0x0024  /* FIFO Control Register */
#define RZV_SCI_DCR_OFFSET          0x0030  /* Driver Control Register */
#define RZV_SCI_XCR0_OFFSET         0x0034  /* Simple-LIN Control Register 0 */
#define RZV_SCI_XCR1_OFFSET         0x0038  /* Simple-LIN Control Register 1 */
#define RZV_SCI_XCR2_OFFSET         0x003C  /* Simple-LIN Control Register 2 */
#define RZV_SCI_CSR_OFFSET          0x0048  /* Common Status Register */
#define RZV_SCI_ISR_OFFSET          0x004C  /* I2C Status Register */
#define RZV_SCI_FRSR_OFFSET         0x0050  /* FIFO Receive Status Register */
#define RZV_SCI_FTSR_OFFSET         0x0054  /* FIFO Transmit Status Register */
#define RZV_SCI_XSR0_OFFSET         0x005C  /* Simple-LIN Status Register 0 */
#define RZV_SCI_XSR1_OFFSET         0x0060  /* Simple-LIN Status Register 1 */
#define RZV_SCI_CFCLR_OFFSET        0x0068  /* Common Flag Clear Register */
#define RZV_SCI_ICFCLR_OFFSET       0x006C  /* I2C Flag Clear Register */
#define RZV_SCI_FFCLR_OFFSET        0x0070  /* FIFO Flag Clear Register */
#define RZV_SCI_XFCLR_OFFSET        0x0078  /* Simple-LIN Flag Clear Register */

/* SCI_B SPI Register Addresses ********************************************/

#define RZV_SCI_RDR(ch)             ((ch##_BASE) + RZV_SCI_RDR_OFFSET)
#define RZV_SCI_TDR(ch)             ((ch##_BASE) + RZV_SCI_TDR_OFFSET)
#define RZV_SCI_CCR0(ch)            ((ch##_BASE) + RZV_SCI_CCR0_OFFSET)
#define RZV_SCI_CCR1(ch)            ((ch##_BASE) + RZV_SCI_CCR1_OFFSET)
#define RZV_SCI_CCR2(ch)            ((ch##_BASE) + RZV_SCI_CCR2_OFFSET)
#define RZV_SCI_CCR3(ch)            ((ch##_BASE) + RZV_SCI_CCR3_OFFSET)
#define RZV_SCI_CCR4(ch)            ((ch##_BASE) + RZV_SCI_CCR4_OFFSET)
#define RZV_SCI_CESR(ch)            ((ch##_BASE) + RZV_SCI_CESR_OFFSET)
#define RZV_SCI_HCR(ch)             ((ch##_BASE) + RZV_SCI_HCR_OFFSET)
#define RZV_SCI_ICR(ch)             ((ch##_BASE) + RZV_SCI_ICR_OFFSET)
#define RZV_SCI_FCR(ch)             ((ch##_BASE) + RZV_SCI_FCR_OFFSET)
#define RZV_SCI_DCR(ch)             ((ch##_BASE) + RZV_SCI_DCR_OFFSET)
#define RZV_SCI_XCR0(ch)            ((ch##_BASE) + RZV_SCI_XCR0_OFFSET)
#define RZV_SCI_XCR1(ch)            ((ch##_BASE) + RZV_SCI_XCR1_OFFSET)
#define RZV_SCI_XCR2(ch)            ((ch##_BASE) + RZV_SCI_XCR2_OFFSET)
#define RZV_SCI_CSR(ch)             ((ch##_BASE) + RZV_SCI_CSR_OFFSET)
#define RZV_SCI_ISR(ch)             ((ch##_BASE) + RZV_SCI_ISR_OFFSET)
#define RZV_SCI_FRSR(ch)            ((ch##_BASE) + RZV_SCI_FRSR_OFFSET)
#define RZV_SCI_FTSR(ch)            ((ch##_BASE) + RZV_SCI_FTSR_OFFSET)
#define RZV_SCI_XSR0(ch)            ((ch##_BASE) + RZV_SCI_XSR0_OFFSET)
#define RZV_SCI_XSR1(ch)            ((ch##_BASE) + RZV_SCI_XSR1_OFFSET)
#define RZV_SCI_CFCLR(ch)           ((ch##_BASE) + RZV_SCI_CFCLR_OFFSET)
#define RZV_SCI_ICFCLR(ch)          ((ch##_BASE) + RZV_SCI_ICFCLR_OFFSET)
#define RZV_SCI_FFCLR(ch)           ((ch##_BASE) + RZV_SCI_FFCLR_OFFSET)
#define RZV_SCI_XFCLR(ch)           ((ch##_BASE) + RZV_SCI_XFCLR_OFFSET)

/* CCR0 - Common Control Register 0 ****************************************/

#define SCI_CCR0_RE                 (1 << 0)   /* Receive Enable */
#define SCI_CCR0_TE                 (1 << 4)   /* Transmit Enable */
#define SCI_CCR0_MPIE               (1 << 8)   /* Multi-Processor Interrupt Enable */
#define SCI_CCR0_DCME               (1 << 9)   /* Data Compare Match Enable */
#define SCI_CCR0_IDSEL              (1 << 10)  /* ID Select */
#define SCI_CCR0_RIE                (1 << 16)  /* Receive Interrupt Enable */
#define SCI_CCR0_TIE                (1 << 20)  /* Transmit Interrupt Enable */
#define SCI_CCR0_TEIE               (1 << 21)  /* Transmit End Interrupt Enable */
#define SCI_CCR0_SSE                (1 << 24)  /* SS Pin Function Enable */

/* CCR1 - Common Control Register 1 ****************************************/

#define SCI_CCR1_CTSE               (1 << 0)   /* CTS Enable */
#define SCI_CCR1_CTSPEN             (1 << 1)   /* CTS Pin Enable */
#define SCI_CCR1_SPB2DT             (1 << 4)   /* Serial Port Break Data Select */
#define SCI_CCR1_SPB2IO             (1 << 5)   /* Serial Port Break I/O */
#define SCI_CCR1_PE                 (1 << 8)   /* Parity Enable */
#define SCI_CCR1_PM                 (1 << 9)   /* Parity Mode */
#define SCI_CCR1_TINV               (1 << 12)  /* TXD Invert */
#define SCI_CCR1_RINV               (1 << 13)  /* RXD Invert */
#define SCI_CCR1_SPLP               (1 << 16)  /* Loopback */
#define SCI_CCR1_SHARPS             (1 << 20)  /* SHARP "#" Format Select */
#define SCI_CCR1_NFCS_SHIFT         24
#define SCI_CCR1_NFCS_MASK          (0x7 << SCI_CCR1_NFCS_SHIFT)
#define SCI_CCR1_NFEN               (1 << 28)  /* Noise Filter Enable */

/* CCR2 - Common Control Register 2 (Bit Rate) *****************************/

#define SCI_CCR2_BCP_SHIFT          0
#define SCI_CCR2_BCP_MASK           (0x7 << SCI_CCR2_BCP_SHIFT)
#define SCI_CCR2_BGDM               (1 << 4)   /* Baud Rate Generator Double Speed Mode */
#define SCI_CCR2_ABCS               (1 << 5)   /* Asynchronous Base Clock Select */
#define SCI_CCR2_ABCSE              (1 << 6)   /* Asynchronous Base Clock Select Enable */
#define SCI_CCR2_BRR_SHIFT          8
#define SCI_CCR2_BRR_MASK           (0xFF << SCI_CCR2_BRR_SHIFT)
#define SCI_CCR2_BRME               (1 << 16)  /* Bit Rate Modulation Enable */
#define SCI_CCR2_CKS_SHIFT          20
#define SCI_CCR2_CKS_MASK           (0x3 << SCI_CCR2_CKS_SHIFT)
#define SCI_CCR2_CKS_PCLK           (0 << SCI_CCR2_CKS_SHIFT)
#define SCI_CCR2_CKS_PCLK_DIV4      (1 << SCI_CCR2_CKS_SHIFT)
#define SCI_CCR2_CKS_PCLK_DIV16     (2 << SCI_CCR2_CKS_SHIFT)
#define SCI_CCR2_CKS_PCLK_DIV64     (3 << SCI_CCR2_CKS_SHIFT)
#define SCI_CCR2_MDDR_SHIFT         24
#define SCI_CCR2_MDDR_MASK          (0xFF << SCI_CCR2_MDDR_SHIFT)

/* CCR3 - Common Control Register 3 (SPI Configuration) ********************/

#define SCI_CCR3_CPHA               (1 << 0)   /* Clock Phase (SPI) */
#define SCI_CCR3_CPOL               (1 << 1)   /* Clock Polarity (SPI) */
#define SCI_CCR3_BPEN               (1 << 7)   /* Base Clock Pulse Enable */
#define SCI_CCR3_CHR_SHIFT          8
#define SCI_CCR3_CHR_MASK           (0x3 << SCI_CCR3_CHR_SHIFT)
#define SCI_CCR3_CHR_8BIT           (0 << SCI_CCR3_CHR_SHIFT)
#define SCI_CCR3_CHR_7BIT           (1 << SCI_CCR3_CHR_SHIFT)
#define SCI_CCR3_CHR_9BIT           (2 << SCI_CCR3_CHR_SHIFT)
#define SCI_CCR3_LSBF               (1 << 12)  /* LSB First */
#define SCI_CCR3_SINV               (1 << 13)  /* Serial Data Invert */
#define SCI_CCR3_STP                (1 << 14)  /* Stop Bit */
#define SCI_CCR3_RXDESEL            (1 << 15)  /* RXD External Input Pin Deselect */
#define SCI_CCR3_MOD_SHIFT          16
#define SCI_CCR3_MOD_MASK           (0x7 << SCI_CCR3_MOD_SHIFT)
#define SCI_CCR3_MOD_ASYNC          (0 << SCI_CCR3_MOD_SHIFT)
#define SCI_CCR3_MOD_CLOCK_SYNC     (1 << SCI_CCR3_MOD_SHIFT)
#define SCI_CCR3_MOD_SPI            (2 << SCI_CCR3_MOD_SHIFT)
#define SCI_CCR3_MOD_SIMPLE_I2C     (3 << SCI_CCR3_MOD_SHIFT)
#define SCI_CCR3_MOD_SIMPLE_SPI     (4 << SCI_CCR3_MOD_SHIFT)
#define SCI_CCR3_MOD_MANCHESTER     (5 << SCI_CCR3_MOD_SHIFT)
#define SCI_CCR3_MP                 (1 << 19)  /* Multi-Processor Select */
#define SCI_CCR3_FM                 (1 << 20)  /* FIFO Mode Select */
#define SCI_CCR3_DEN                (1 << 21)  /* Driver Enable */
#define SCI_CCR3_CKE_SHIFT          24
#define SCI_CCR3_CKE_MASK           (0x3 << SCI_CCR3_CKE_SHIFT)
#define SCI_CCR3_CKE_INT_SCK_IO     (0 << SCI_CCR3_CKE_SHIFT)  /* Internal clock, SCK I/O disabled */
#define SCI_CCR3_CKE_INT_SCK_OUT    (1 << SCI_CCR3_CKE_SHIFT)  /* Internal clock, SCK output */
#define SCI_CCR3_CKE_EXT_SCK_8X     (2 << SCI_CCR3_CKE_SHIFT)  /* External clock, 8x */
#define SCI_CCR3_CKE_EXT_SCK_16X    (3 << SCI_CCR3_CKE_SHIFT)  /* External clock, 16x */
#define SCI_CCR3_GM                 (1 << 28)  /* GSM Mode */
#define SCI_CCR3_BLK                (1 << 29)  /* Block Transfer */

/* CCR4 - Common Control Register 4 ****************************************/

#define SCI_CCR4_CMPD_SHIFT         0
#define SCI_CCR4_CMPD_MASK          (0x1FF << SCI_CCR4_CMPD_SHIFT)
#define SCI_CCR4_ASEN               (1 << 16)  /* Address Match Sense */
#define SCI_CCR4_ATEN               (1 << 17)  /* Address Match Timing Enable */
#define SCI_CCR4_AST_SHIFT          24
#define SCI_CCR4_AST_MASK           (0x7 << SCI_CCR4_AST_SHIFT)
#define SCI_CCR4_AJD                (1 << 27)  /* Address Match Judgment */
#define SCI_CCR4_ATT_SHIFT          28
#define SCI_CCR4_ATT_MASK           (0x7 << SCI_CCR4_ATT_SHIFT)
#define SCI_CCR4_AET                (1 << 31)  /* Address Match Error Timing */

/* CESR - Communication Enable Status Register *****************************/

#define SCI_CESR_RIST               (1 << 0)   /* Receive In Progress */
#define SCI_CESR_TIST               (1 << 4)   /* Transmit In Progress */

/* FCR - FIFO Control Register *********************************************/

#define SCI_FCR_DRES                (1 << 0)   /* Data Receive Enable Status */
#define SCI_FCR_TTRG_SHIFT          8
#define SCI_FCR_TTRG_MASK           (0x1F << SCI_FCR_TTRG_SHIFT)
#define SCI_FCR_TFRST               (1 << 15)  /* Transmit FIFO Reset */
#define SCI_FCR_RTRG_SHIFT          16
#define SCI_FCR_RTRG_MASK           (0x1F << SCI_FCR_RTRG_SHIFT)
#define SCI_FCR_RFRST               (1 << 23)  /* Receive FIFO Reset */
#define SCI_FCR_RSTRG_SHIFT         24
#define SCI_FCR_RSTRG_MASK          (0x1F << SCI_FCR_RSTRG_SHIFT)

/* CSR - Common Status Register ********************************************/

#define SCI_CSR_ERS                 (1 << 4)   /* Error Signal Status */
#define SCI_CSR_RXDMON              (1 << 15)  /* Serial Receive Data Monitor */
#define SCI_CSR_DCMF                (1 << 16)  /* Data Compare Match Flag */
#define SCI_CSR_DPER                (1 << 17)  /* Data Parity Error */
#define SCI_CSR_DFER                (1 << 18)  /* Data Framing Error */
#define SCI_CSR_ORER                (1 << 24)  /* Overrun Error */
#define SCI_CSR_MFF                 (1 << 26)  /* Mode Fault Flag */
#define SCI_CSR_PER                 (1 << 27)  /* Parity Error */
#define SCI_CSR_FER                 (1 << 28)  /* Framing Error */
#define SCI_CSR_TDRE                (1 << 29)  /* Transmit Data Empty */
#define SCI_CSR_TEND                (1 << 30)  /* Transmit End */
#define SCI_CSR_RDRF                (1 << 31)  /* Receive Data Full */

/* FRSR - FIFO Receive Status Register *************************************/

#define SCI_FRSR_DR                 (1 << 0)   /* Receive Data Ready */
#define SCI_FRSR_R_SHIFT            8
#define SCI_FRSR_R_MASK             (0x3F << SCI_FRSR_R_SHIFT)
#define SCI_FRSR_PNUM_SHIFT         16
#define SCI_FRSR_PNUM_MASK          (0x3F << SCI_FRSR_PNUM_SHIFT)
#define SCI_FRSR_FNUM_SHIFT         24
#define SCI_FRSR_FNUM_MASK          (0x3F << SCI_FRSR_FNUM_SHIFT)

/* FTSR - FIFO Transmit Status Register ************************************/

#define SCI_FTSR_T_SHIFT            0
#define SCI_FTSR_T_MASK             (0x3F << SCI_FTSR_T_SHIFT)

/* CFCLR - Common Flag Clear Register **************************************/

#define SCI_CFCLR_ERSC              (1 << 4)   /* Error Signal Status Clear */
#define SCI_CFCLR_DCMFC             (1 << 16)  /* Data Compare Match Flag Clear */
#define SCI_CFCLR_DPERC             (1 << 17)  /* Data Parity Error Clear */
#define SCI_CFCLR_DFERC             (1 << 18)  /* Data Framing Error Clear */
#define SCI_CFCLR_ORERC             (1 << 24)  /* Overrun Error Clear */
#define SCI_CFCLR_MFFC              (1 << 26)  /* Mode Fault Flag Clear */
#define SCI_CFCLR_PERC              (1 << 27)  /* Parity Error Clear */
#define SCI_CFCLR_FERC              (1 << 28)  /* Framing Error Clear */
#define SCI_CFCLR_TDREC             (1 << 29)  /* Transmit Data Empty Clear */
#define SCI_CFCLR_RDRFC             (1 << 31)  /* Receive Data Full Clear */

/* FFCLR - FIFO Flag Clear Register ****************************************/

#define SCI_FFCLR_DRC               (1 << 0)   /* Data Receive Clear */

/* FIFO sizes **************************************************************/

#define RZV_SCI_FIFO_SIZE           16         /* SCI_B FIFO depth */

/* SPI mode timing parameters **********************************************/

#define RZV_SCI_SPI_MAX_FREQUENCY   50000000   /* 50 MHz max */
#define RZV_SCI_SPI_MIN_FREQUENCY   1000       /* 1 kHz min */

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV2H_RZV_SCI_SPI_H */
