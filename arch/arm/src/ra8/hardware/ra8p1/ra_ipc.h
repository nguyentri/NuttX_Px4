/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_ipc.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_IPC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_IPC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* IPC Base Address */
#ifndef R_IPC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_IPC_BASE           0x40020000
#else
#define R_IPC_BASE           0x50020000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_IPC_CH_STRIDE    0x00000004
#define R_IPC_CH_BASE(ch)   (R_IPC_BASE + ((uint32_t)(ch) * R_IPC_CH_STRIDE))

/* IPC Register Offsets */

/* IPCSEM%s Registers (0-15) */
#define R_IPC_IPCSEM00_OFFSET     0x00000000  /* Semaphore Register 00 (n = 0 to 15) */
#define R_IPC_IPCSEM01_OFFSET     0x00000004  /* Semaphore Register 01 (n = 0 to 15) */
#define R_IPC_IPCSEM02_OFFSET     0x00000008  /* Semaphore Register 02 (n = 0 to 15) */
#define R_IPC_IPCSEM03_OFFSET     0x0000000c  /* Semaphore Register 03 (n = 0 to 15) */
#define R_IPC_IPCSEM04_OFFSET     0x00000010  /* Semaphore Register 04 (n = 0 to 15) */
#define R_IPC_IPCSEM05_OFFSET     0x00000014  /* Semaphore Register 05 (n = 0 to 15) */
#define R_IPC_IPCSEM06_OFFSET     0x00000018  /* Semaphore Register 06 (n = 0 to 15) */
#define R_IPC_IPCSEM07_OFFSET     0x0000001c  /* Semaphore Register 07 (n = 0 to 15) */
#define R_IPC_IPCSEM08_OFFSET     0x00000020  /* Semaphore Register 08 (n = 0 to 15) */
#define R_IPC_IPCSEM09_OFFSET     0x00000024  /* Semaphore Register 09 (n = 0 to 15) */
#define R_IPC_IPCSEM10_OFFSET     0x00000028  /* Semaphore Register 10 (n = 0 to 15) */
#define R_IPC_IPCSEM11_OFFSET     0x0000002c  /* Semaphore Register 11 (n = 0 to 15) */
#define R_IPC_IPCSEM12_OFFSET     0x00000030  /* Semaphore Register 12 (n = 0 to 15) */
#define R_IPC_IPCSEM13_OFFSET     0x00000034  /* Semaphore Register 13 (n = 0 to 15) */
#define R_IPC_IPCSEM14_OFFSET     0x00000038  /* Semaphore Register 14 (n = 0 to 15) */
#define R_IPC_IPCSEM15_OFFSET     0x0000003c  /* Semaphore Register 15 (n = 0 to 15) */
#define R_IPC_IPC0NMISTA_OFFSET     0x00000080  /* Inter-Processor0 NMI Request Status Register */
#define R_IPC_IPC0NMISET_OFFSET     0x00000084  /* Inter-Processor0 NMI Request Set Register */
#define R_IPC_IPC0NMICLR_OFFSET     0x00000088  /* Inter-Processor0 NMI Request Clear Register */
#define R_IPC_IPC1NMISTA_OFFSET     0x00000090  /* Inter-Processor1 NMI Request Status Register */
#define R_IPC_IPC1NMISET_OFFSET     0x00000094  /* Inter-Processor1 NMI Request Set Register */
#define R_IPC_IPC1NMICLR_OFFSET     0x00000098  /* Inter-Processor1 NMI Request Clear Register */
#define R_IPC_IPC0STA0_OFFSET     0x000000c0  /* Inter-Processor0 Status Register0 */
#define R_IPC_IPC0ISET0_OFFSET     0x000000c4  /* Inter-Processor0 IRQ Request Set Register0 */
#define R_IPC_IPC0TXD0_OFFSET     0x000000c8  /* Inter-Processor0 FIFO Transfer Data Register0 */
#define R_IPC_IPC0RXD0_OFFSET     0x000000cc  /* Inter-Processor0 FIFO Receive Data Register0 */
#define R_IPC_IPC0CLR0_OFFSET     0x000000d0  /* Inter-Processor0 Clear Register0 */
#define R_IPC_IPC0STA1_OFFSET     0x000000e0  /* Inter-Processor0 Status Register1 */
#define R_IPC_IPC0ISET1_OFFSET     0x000000e4  /* Inter-Processor0 IRQ Request Set Register1 */
#define R_IPC_IPC0TXD1_OFFSET     0x000000e8  /* Inter-Processor0 FIFO Transfer Data Register1 */
#define R_IPC_IPC0RXD1_OFFSET     0x000000ec  /* Inter-Processor0 FIFO Receive Data Register1 */
#define R_IPC_IPC0CLR1_OFFSET     0x000000f0  /* Inter-Processor0 Clear Register1 */
#define R_IPC_IPC1STA0_OFFSET     0x00000100  /* Inter-Processor1 Status Register0 */
#define R_IPC_IPC1ISET0_OFFSET     0x00000104  /* Inter-Processor1 IRQ Request Set Register0 */
#define R_IPC_IPC1TXD0_OFFSET     0x00000108  /* Inter-Processor1 FIFO Transfer Data Register0 */
#define R_IPC_IPC1RXD0_OFFSET     0x0000010c  /* Inter-Processor1 FIFO Receive Data Register0 */
#define R_IPC_IPC1CLR0_OFFSET     0x00000110  /* Inter-Processor1 Request Clear Register0 */
#define R_IPC_IPC1STA1_OFFSET     0x00000120  /* Inter-Processor1 Request Status Register1 */
#define R_IPC_IPC1ISET1_OFFSET     0x00000124  /* Inter-Processor1 IRQ Request Set Register1 */
#define R_IPC_IPC1TXD1_OFFSET     0x00000128  /* Inter-Processor1 FIFO Transfer Data Register1 */
#define R_IPC_IPC1RXD1_OFFSET     0x0000012c  /* Inter-Processor1 FIFO Receive Data Register1 */
#define R_IPC_IPC1CLR1_OFFSET     0x00000130  /* Inter-Processor1 Clear Register1 */

/* IPC Register Addresses */

#define R_IPC_IPCSEM00                 (R_IPC_BASE + R_IPC_IPCSEM00_OFFSET)
#define R_IPC_IPCSEM01                 (R_IPC_BASE + R_IPC_IPCSEM01_OFFSET)
#define R_IPC_IPCSEM02                 (R_IPC_BASE + R_IPC_IPCSEM02_OFFSET)
#define R_IPC_IPCSEM03                 (R_IPC_BASE + R_IPC_IPCSEM03_OFFSET)
#define R_IPC_IPCSEM04                 (R_IPC_BASE + R_IPC_IPCSEM04_OFFSET)
#define R_IPC_IPCSEM05                 (R_IPC_BASE + R_IPC_IPCSEM05_OFFSET)
#define R_IPC_IPCSEM06                 (R_IPC_BASE + R_IPC_IPCSEM06_OFFSET)
#define R_IPC_IPCSEM07                 (R_IPC_BASE + R_IPC_IPCSEM07_OFFSET)
#define R_IPC_IPCSEM08                 (R_IPC_BASE + R_IPC_IPCSEM08_OFFSET)
#define R_IPC_IPCSEM09                 (R_IPC_BASE + R_IPC_IPCSEM09_OFFSET)
#define R_IPC_IPCSEM10                 (R_IPC_BASE + R_IPC_IPCSEM10_OFFSET)
#define R_IPC_IPCSEM11                 (R_IPC_BASE + R_IPC_IPCSEM11_OFFSET)
#define R_IPC_IPCSEM12                 (R_IPC_BASE + R_IPC_IPCSEM12_OFFSET)
#define R_IPC_IPCSEM13                 (R_IPC_BASE + R_IPC_IPCSEM13_OFFSET)
#define R_IPC_IPCSEM14                 (R_IPC_BASE + R_IPC_IPCSEM14_OFFSET)
#define R_IPC_IPCSEM15                 (R_IPC_BASE + R_IPC_IPCSEM15_OFFSET)
#define R_IPC_IPC0NMISTA                 (R_IPC_BASE + R_IPC_IPC0NMISTA_OFFSET)
#define R_IPC_IPC0NMISET                 (R_IPC_BASE + R_IPC_IPC0NMISET_OFFSET)
#define R_IPC_IPC0NMICLR                 (R_IPC_BASE + R_IPC_IPC0NMICLR_OFFSET)
#define R_IPC_IPC1NMISTA                 (R_IPC_BASE + R_IPC_IPC1NMISTA_OFFSET)
#define R_IPC_IPC1NMISET                 (R_IPC_BASE + R_IPC_IPC1NMISET_OFFSET)
#define R_IPC_IPC1NMICLR                 (R_IPC_BASE + R_IPC_IPC1NMICLR_OFFSET)
#define R_IPC_IPC0STA0                 (R_IPC_BASE + R_IPC_IPC0STA0_OFFSET)
#define R_IPC_IPC0ISET0                 (R_IPC_BASE + R_IPC_IPC0ISET0_OFFSET)
#define R_IPC_IPC0TXD0                 (R_IPC_BASE + R_IPC_IPC0TXD0_OFFSET)
#define R_IPC_IPC0RXD0                 (R_IPC_BASE + R_IPC_IPC0RXD0_OFFSET)
#define R_IPC_IPC0CLR0                 (R_IPC_BASE + R_IPC_IPC0CLR0_OFFSET)
#define R_IPC_IPC0STA1                 (R_IPC_BASE + R_IPC_IPC0STA1_OFFSET)
#define R_IPC_IPC0ISET1                 (R_IPC_BASE + R_IPC_IPC0ISET1_OFFSET)
#define R_IPC_IPC0TXD1                 (R_IPC_BASE + R_IPC_IPC0TXD1_OFFSET)
#define R_IPC_IPC0RXD1                 (R_IPC_BASE + R_IPC_IPC0RXD1_OFFSET)
#define R_IPC_IPC0CLR1                 (R_IPC_BASE + R_IPC_IPC0CLR1_OFFSET)
#define R_IPC_IPC1STA0                 (R_IPC_BASE + R_IPC_IPC1STA0_OFFSET)
#define R_IPC_IPC1ISET0                 (R_IPC_BASE + R_IPC_IPC1ISET0_OFFSET)
#define R_IPC_IPC1TXD0                 (R_IPC_BASE + R_IPC_IPC1TXD0_OFFSET)
#define R_IPC_IPC1RXD0                 (R_IPC_BASE + R_IPC_IPC1RXD0_OFFSET)
#define R_IPC_IPC1CLR0                 (R_IPC_BASE + R_IPC_IPC1CLR0_OFFSET)
#define R_IPC_IPC1STA1                 (R_IPC_BASE + R_IPC_IPC1STA1_OFFSET)
#define R_IPC_IPC1ISET1                 (R_IPC_BASE + R_IPC_IPC1ISET1_OFFSET)
#define R_IPC_IPC1TXD1                 (R_IPC_BASE + R_IPC_IPC1TXD1_OFFSET)
#define R_IPC_IPC1RXD1                 (R_IPC_BASE + R_IPC_IPC1RXD1_OFFSET)
#define R_IPC_IPC1CLR1                 (R_IPC_BASE + R_IPC_IPC1CLR1_OFFSET)

/* Register bit definitions */
/* IPCSEM Register bit definitions */
#define R_IPC_IPCSEM_LOCK                         (1 << 0)  /* This bit indicates the shared resource is locked. */

/* IPC0NMISTA Register bit definitions */
#define R_IPC_IPC0NMISTA_NMI                      (1 << 0)  /* This bit indicates the status of interrupt request. */

/* IPC0NMISET Register bit definitions */
#define R_IPC_IPC0NMISET_SET                      (1 << 0)  /* Writing 1 to the bit sets IPC0NMISTA.NMI. */

/* IPC0NMICLR Register bit definitions */
#define R_IPC_IPC0NMICLR_CLR                      (1 << 0)  /* Writing 1 to this bit clears IPC0NMISTA.NMI. */

/* IPC1NMISTA Register bit definitions */
#define R_IPC_IPC1NMISTA_NMI                      (1 << 0)  /* This bit indicates the status of interrupt request. */

/* IPC1NMISET Register bit definitions */
#define R_IPC_IPC1NMISET_SET                      (1 << 0)  /* Writing 1 to this bit sets IPC1NMISTA.NMI. */

/* IPC1NMICLR Register bit definitions */
#define R_IPC_IPC1NMICLR_CLR                      (1 << 0)  /* Writing 1 to this bit clears IPC1NMISTA.NMI. */

/* IPC0STA0 Register bit definitions */
#define R_IPC_IPC0STA0_IRQ0                       (1 << 0)  /* This bit indicates the status of interrupt request. */

#define R_IPC_IPC0STA0_IRQ1                       (1 << 1)  /* This bit indicates the status of interrupt request. */

#define R_IPC_IPC0STA0_IRQ2                       (1 << 2)  /* This bit indicates the status of interrupt request. */

#define R_IPC_IPC0STA0_IRQ3                       (1 << 3)  /* This bit indicates the status of interrupt request. */

#define R_IPC_IPC0STA0_IRQ4                       (1 << 4)  /* This bit indicates the status of interrupt request. */

#define R_IPC_IPC0STA0_IRQ5                       (1 << 5)  /* This bit indicates the status of interrupt request. */

#define R_IPC_IPC0STA0_IRQ6                       (1 << 6)  /* This bit indicates the status of interrupt request. */

#define R_IPC_IPC0STA0_IRQ7                       (1 << 7)  /* This bit indicates the status of interrupt request. */

#define R_IPC_IPC0STA0_RDY                        (1 << 16)  /* This bit is set when FIFO is not empty. */

#define R_IPC_IPC0STA0_FULL                       (1 << 17)  /*  */

#define R_IPC_IPC0STA0_RERR                       (1 << 24)  /* Indicates that the message FIFO 00 tried to read data despite being empty. */

#define R_IPC_IPC0STA0_FERR                       (1 << 25)  /* Indicates that the message FIFO 00 tried to send more data even though it was full. */

/* IPC0TXD0 Register bit definitions */
#define R_IPC_IPC0TXD0_TXD_SHIFT                  (0)  /* Transmit data for the Message FIFO 00 */
#define R_IPC_IPC0TXD0_TXD_MASK                   0xffffffff

/* IPC0RXD0 Register bit definitions */
#define R_IPC_IPC0RXD0_RXD_SHIFT                  (0)  /* Received data from the message FIFO 00 */
#define R_IPC_IPC0RXD0_RXD_MASK                   0xffffffff

/* IPC0CLR0 Register bit definitions */
#define R_IPC_IPC0CLR0_RST                        (1 << 16)  /*  */

#define R_IPC_IPC0CLR0_RCLR                       (1 << 24)  /* Writing 1 resets IPC0STA0.RERR. */

#define R_IPC_IPC0CLR0_FCLR                       (1 << 25)  /* Writing 1 resets IPC0STA0. FERR. */

/* IPC0STA1 Register bit definitions */
#define R_IPC_IPC0STA1_RDY                        (1 << 16)  /* This bit is set when FIFO is not empty. */

#define R_IPC_IPC0STA1_FULL                       (1 << 17)  /*  */

#define R_IPC_IPC0STA1_RERR                       (1 << 24)  /* Indicates that the message FIFO 01 tried to read data despite being empty. */

#define R_IPC_IPC0STA1_FERR                       (1 << 25)  /* Indicates that the message FIFO 01 tried to send more data even though it was full. */

/* IPC0TXD1 Register bit definitions */
#define R_IPC_IPC0TXD1_TXD_SHIFT                  (0)  /* Transmit data for the Message FIFO 01 */
#define R_IPC_IPC0TXD1_TXD_MASK                   0xffffffff

/* IPC0RXD1 Register bit definitions */
#define R_IPC_IPC0RXD1_RXD_SHIFT                  (0)  /* Received data from the message FIFO 01 */
#define R_IPC_IPC0RXD1_RXD_MASK                   0xffffffff

/* IPC0CLR1 Register bit definitions */
#define R_IPC_IPC0CLR1_RST                        (1 << 16)  /*  */

#define R_IPC_IPC0CLR1_RCLR                       (1 << 24)  /*  */

#define R_IPC_IPC0CLR1_FCLR                       (1 << 25)  /*  */

/* IPC1STA0 Register bit definitions */
#define R_IPC_IPC1STA0_RDY                        (1 << 16)  /* This bit is set when FIFO is not empty. */

#define R_IPC_IPC1STA0_FULL                       (1 << 17)  /*  */

#define R_IPC_IPC1STA0_RERR                       (1 << 24)  /* This bit indicates that the message FIFO 10 tried to read data despite being empty. */

#define R_IPC_IPC1STA0_FERR                       (1 << 25)  /* This bit indicates that the message FIFO 10 tried to send more data even though it was full. */

/* IPC1TXD0 Register bit definitions */
#define R_IPC_IPC1TXD0_TXD_SHIFT                  (0)  /* Transmit data for the Message FIFO 10 */
#define R_IPC_IPC1TXD0_TXD_MASK                   0xffffffff

/* IPC1RXD0 Register bit definitions */
#define R_IPC_IPC1RXD0_RXD_SHIFT                  (0)  /* Received data from the message FIFO 10 */
#define R_IPC_IPC1RXD0_RXD_MASK                   0xffffffff

/* IPC1CLR0 Register bit definitions */
#define R_IPC_IPC1CLR0_RST                        (1 << 16)  /* Writing 1 resets Message FIFO 10. */

#define R_IPC_IPC1CLR0_RCLR                       (1 << 24)  /*  */

#define R_IPC_IPC1CLR0_FCLR                       (1 << 25)  /* Writing 1 resets IPC1STA0. FERR. */

/* IPC1STA1 Register bit definitions */
#define R_IPC_IPC1STA1_RDY                        (1 << 16)  /* This bit is set when FIFO is not empty. */

#define R_IPC_IPC1STA1_FULL                       (1 << 17)  /*  */

#define R_IPC_IPC1STA1_RERR                       (1 << 24)  /* Indicates that the message FIFO 11 tried to read data despite being empty. */

#define R_IPC_IPC1STA1_FERR                       (1 << 25)  /* Indicates that the message FIFO 11 tried to send more data even though it was full. */

/* IPC1TXD1 Register bit definitions */
#define R_IPC_IPC1TXD1_TXD_SHIFT                  (0)  /* Transmit data for the Message FIFO 11 */
#define R_IPC_IPC1TXD1_TXD_MASK                   0xffffffff

/* IPC1RXD1 Register bit definitions */
#define R_IPC_IPC1RXD1_RXD_SHIFT                  (0)  /* Received data from the message FIFO 11 */
#define R_IPC_IPC1RXD1_RXD_MASK                   0xffffffff

/* IPC1CLR1 Register bit definitions */
#define R_IPC_IPC1CLR1_RST                        (1 << 16)  /* Writing 1 resets message FIFO 11. */

#define R_IPC_IPC1CLR1_RCLR                       (1 << 24)  /* Writing 1 resets IPC1STA1.RERR. */

#define R_IPC_IPC1CLR1_FCLR                       (1 << 25)  /* Writing 1resets IPC1STA1. FERR. */


/* Maximum number of channels */

#define IPC_MAX_CHANNELS    16

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_IPC_H */
