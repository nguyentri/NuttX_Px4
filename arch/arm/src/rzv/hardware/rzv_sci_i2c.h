/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_sci_i2c.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SCI_I2C_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SCI_I2C_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SCI Base Addresses ****************************************************/

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

#define RZV_SCI_SMR_OFFSET       0x00  /* Serial Mode Register */
#define RZV_SCI_BRR_OFFSET       0x01  /* Bit Rate Register */
#define RZV_SCI_SCR_OFFSET       0x02  /* Serial Control Register */
#define RZV_SCI_TDR_OFFSET       0x03  /* Transmit Data Register */
#define RZV_SCI_SSR_OFFSET       0x04  /* Serial Status Register */
#define RZV_SCI_RDR_OFFSET       0x05  /* Receive Data Register */
#define RZV_SCI_SCMR_OFFSET      0x06  /* Smart Card Mode Register */
#define RZV_SCI_SEMR_OFFSET      0x07  /* Serial Extended Mode Register */
#define RZV_SCI_SNFR_OFFSET      0x08  /* Noise Filter Setting Register */
#define RZV_SCI_SIMR1_OFFSET     0x20  /* Simple I2C Mode Register 1 */
#define RZV_SCI_SIMR2_OFFSET     0x21  /* Simple I2C Mode Register 2 */
#define RZV_SCI_SIMR3_OFFSET     0x22  /* Simple I2C Mode Register 3 */
#define RZV_SCI_SISR_OFFSET      0x23  /* Simple I2C Status Register */
#define RZV_SCI_SPMR_OFFSET      0x24  /* SPI Mode Register */
#define RZV_SCI_CDR_OFFSET       0x28  /* Clock Division Register */
#define RZV_SCI_DCCR_OFFSET      0x2C  /* Data Compare Control Register */
#define RZV_SCI_FCR_OFFSET       0x30  /* FIFO Control Register */
#define RZV_SCI_FDR_OFFSET       0x34  /* FIFO Data Count Register */
#define RZV_SCI_LSR_OFFSET       0x38  /* Line Status Register */
#define RZV_SCI_XCR0_OFFSET      0x60  /* Extended Control Register 0 */
#define RZV_SCI_XCR1_OFFSET      0x61  /* Extended Control Register 1 */
#define RZV_SCI_XCR2_OFFSET      0x62  /* Extended Control Register 2 */
#define RZV_SCI_ICR_OFFSET       0x63  /* I2C Control Register */
#define RZV_SCI_STR_OFFSET       0x64  /* Status Register */
#define RZV_SCI_STCR_OFFSET      0x65  /* Status Clear Register */
#define RZV_SCI_CF0RR_OFFSET     0x68  /* Compare Function 0 Receive */
#define RZV_SCI_CF0CR_OFFSET     0x6C  /* Compare Function 0 Control */
#define RZV_SCI_CF0TR_OFFSET     0x70  /* Compare Function 0 Transmit */
#define RZV_SCI_CF1RR_OFFSET     0x74  /* Compare Function 1 Receive */
#define RZV_SCI_CF1CR_OFFSET     0x78  /* Compare Function 1 Control */
#define RZV_SCI_CF1TR_OFFSET     0x7C  /* Compare Function 1 Transmit */
#define RZV_SCI_ACR_OFFSET       0x80  /* Address Compare Register */

/* SMR - Serial Mode Register (I2C mode) */

#define SCI_SMR_CKS_SHIFT        (0)   /* Clock Select */
#define SCI_SMR_CKS_MASK         (0x03 << SCI_SMR_CKS_SHIFT)
#define SCI_SMR_CKS_DIV1         (0x00 << SCI_SMR_CKS_SHIFT)
#define SCI_SMR_CKS_DIV4         (0x01 << SCI_SMR_CKS_SHIFT)
#define SCI_SMR_CKS_DIV16        (0x02 << SCI_SMR_CKS_SHIFT)
#define SCI_SMR_CKS_DIV64        (0x03 << SCI_SMR_CKS_SHIFT)
#define SCI_SMR_MP               (1 << 2)   /* Multi-processor mode */
#define SCI_SMR_STOP             (1 << 3)   /* Stop bit length */
#define SCI_SMR_PM               (1 << 4)   /* Parity mode */
#define SCI_SMR_PE               (1 << 5)   /* Parity enable */
#define SCI_SMR_CHR              (1 << 6)   /* Character length */
#define SCI_SMR_CM               (1 << 7)   /* Communication mode */

/* SCR - Serial Control Register */

#define SCI_SCR_CKE_SHIFT        (0)   /* Clock Enable */
#define SCI_SCR_CKE_MASK         (0x03 << SCI_SCR_CKE_SHIFT)
#define SCI_SCR_TEIE             (1 << 2)   /* Transmit End Interrupt Enable */
#define SCI_SCR_MPIE             (1 << 3)   /* Multi-processor Interrupt Enable */
#define SCI_SCR_RE               (1 << 4)   /* Receive Enable */
#define SCI_SCR_TE               (1 << 5)   /* Transmit Enable */
#define SCI_SCR_RIE              (1 << 6)   /* Receive Interrupt Enable */
#define SCI_SCR_TIE              (1 << 7)   /* Transmit Interrupt Enable */

/* SSR - Serial Status Register */

#define SCI_SSR_MPBT             (1 << 0)   /* Multi-processor bit transfer */
#define SCI_SSR_MPB              (1 << 1)   /* Multi-processor bit */
#define SCI_SSR_TEND             (1 << 2)   /* Transmit End Flag */
#define SCI_SSR_PER              (1 << 3)   /* Parity Error Flag */
#define SCI_SSR_FER              (1 << 4)   /* Framing Error Flag */
#define SCI_SSR_ORER             (1 << 5)   /* Overrun Error Flag */
#define SCI_SSR_RDRF             (1 << 6)   /* Receive Data Full Flag */
#define SCI_SSR_TDRE             (1 << 7)   /* Transmit Data Empty Flag */

/* SCMR - Smart Card Mode Register */

#define SCI_SCMR_SMIF            (1 << 0)   /* Smart Card Interface Mode Select */
#define SCI_SCMR_SINV            (1 << 2)   /* Transmitted/Received Data Invert */
#define SCI_SCMR_SDIR            (1 << 3)   /* Transmitted/Received Data Transfer Direction */
#define SCI_SCMR_BCP2            (1 << 7)   /* Base Clock Pulse 2 */

/* SEMR - Serial Extended Mode Register */

#define SCI_SEMR_ACS0            (1 << 0)   /* Asynchronous Mode Clock Source Select */
#define SCI_SEMR_ABCS            (1 << 4)   /* Asynchronous Mode Base Clock Select */
#define SCI_SEMR_NFEN            (1 << 5)   /* Digital Noise Filter Function Enable */
#define SCI_SEMR_BGDM            (1 << 6)   /* Baud Rate Generator Double-Speed Mode Select */
#define SCI_SEMR_RXDESEL         (1 << 7)   /* Asynchronous Start Bit Edge Detection Select */

/* SIMR1 - Simple I2C Mode Register 1 */

#define SCI_SIMR1_IICM           (1 << 0)   /* Simple I2C Mode Select */
#define SCI_SIMR1_IICDL_SHIFT    (3)        /* SDA Delay Output Select */
#define SCI_SIMR1_IICDL_MASK     (0x1F << SCI_SIMR1_IICDL_SHIFT)
#define SCI_SIMR1_IICDL(n)       (((n) & 0x1F) << SCI_SIMR1_IICDL_SHIFT)

/* SIMR2 - Simple I2C Mode Register 2 */

#define SCI_SIMR2_IICINTM        (1 << 0)   /* I2C Interrupt Mode Select */
#define SCI_SIMR2_IICCSC         (1 << 1)   /* Clock Synchronization */
#define SCI_SIMR2_IICACKT        (1 << 5)   /* ACK Transmission Data */

/* SIMR3 - Simple I2C Mode Register 3 */

#define SCI_SIMR3_IICSTAREQ      (1 << 0)   /* Start Condition Generation */
#define SCI_SIMR3_IICRSTAREQ     (1 << 1)   /* Restart Condition Generation */
#define SCI_SIMR3_IICSTPREQ      (1 << 2)   /* Stop Condition Generation */
#define SCI_SIMR3_IICSTIF        (1 << 3)   /* Issuing of Start, Restart, or Stop Condition Completed Flag */
#define SCI_SIMR3_IICSDAS_SHIFT  (4)        /* SDA Output Select */
#define SCI_SIMR3_IICSDAS_MASK   (0x03 << SCI_SIMR3_IICSDAS_SHIFT)
#define SCI_SIMR3_IICSCLS_SHIFT  (6)        /* SCL Output Select */
#define SCI_SIMR3_IICSCLS_MASK   (0x03 << SCI_SIMR3_IICSCLS_SHIFT)

/* SISR - Simple I2C Status Register */

#define SCI_SISR_IICACKR         (1 << 0)   /* ACK Reception Data Flag */

/* ICR - I2C Control Register */

#define SCI_ICR_IICINTM          (1 << 0)   /* I2C Interrupt Mode */
#define SCI_ICR_IICCSC           (1 << 1)   /* I2C Clock Synchronization */
#define SCI_ICR_IICACKT          (1 << 5)   /* I2C ACK Transmission */

/* STR - Status Register */

#define SCI_STR_CFER             (1 << 0)   /* Compare Function Error Flag */
#define SCI_STR_ORER             (1 << 5)   /* Overrun Error Flag */
#define SCI_STR_FER              (1 << 4)   /* Framing Error Flag */
#define SCI_STR_PER              (1 << 3)   /* Parity Error Flag */

/* FCR - FIFO Control Register */

#define SCI_FCR_DRES             (1 << 15)  /* Receive Data Ready Error Select */
#define SCI_FCR_TTRG_SHIFT       (8)        /* Transmit FIFO Data Trigger */
#define SCI_FCR_TTRG_MASK        (0x0F << SCI_FCR_TTRG_SHIFT)
#define SCI_FCR_RTRG_SHIFT       (0)        /* Receive FIFO Data Trigger */
#define SCI_FCR_RTRG_MASK        (0x0F << SCI_FCR_RTRG_SHIFT)
#define SCI_FCR_RSTRG_SHIFT      (4)        /* RTS Output Active Trigger */
#define SCI_FCR_RSTRG_MASK       (0x0F << SCI_FCR_RSTRG_SHIFT)

/* Clock configuration for I2C (assuming PCLK = 100MHz) */

#define RZV_SCI_I2C_PCLK         100000000  /* Peripheral clock (Hz) */

/* Standard I2C frequencies */

#define RZV_SCI_I2C_FREQ_100KHZ  100000
#define RZV_SCI_I2C_FREQ_400KHZ  400000

/* Maximum number of SCI channels that support I2C mode */

#define RZV_SCI_I2C_MAX_CHANNELS 4

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SCI_I2C_H */
