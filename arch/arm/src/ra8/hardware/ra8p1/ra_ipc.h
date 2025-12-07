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

/* IPC Register Offsets */

/* IPCSEM Registers - Semaphore Registers (16 semaphores) */

#define R_IPC_IPCSEM_OFFSET(m)                    (0x00000000 + ((m) * 0x00000004))

/* IPCNMI Registers - Inter-Processor NMI Registers */

#define R_IPC_IPC0NMI_STA_OFFSET                  0x00000080
#define R_IPC_IPC0NMI_SET_OFFSET                  0x00000084
#define R_IPC_IPC0NMI_CLR_OFFSET                  0x00000088

#define R_IPC_IPC1NMI_STA_OFFSET                  0x00000090
#define R_IPC_IPC1NMI_SET_OFFSET                  0x00000094
#define R_IPC_IPC1NMI_CLR_OFFSET                  0x00000098

/* IPC Channel Registers - Inter-Processor Communication Channels */

#define R_IPC_IPC0_OFFSET                         0x000000c0
#define R_IPC_IPC1_OFFSET                         0x00000100

/* IPC Channel Register Offsets (within each IPC block) */

#define RA_IPC_CH_STA_OFFSET                       0x00000000
#define RA_IPC_CH_SET_OFFSET                       0x00000004
#define RA_IPC_CH_TXD_OFFSET                       0x00000008
#define RA_IPC_CH_RXD_OFFSET                       0x0000000c
#define RA_IPC_CH_CLR_OFFSET                       0x00000010

/* Two channels per IPC */

#define RA_IPC_CH0_OFFSET                          0x00000000
#define RA_IPC_CH1_OFFSET                          0x00000020

/* IPC Register Addresses */

/* Semaphore Registers */

#define R_IPC_IPCSEM(m)                           (R_IPC_BASE + R_IPC_IPCSEM_OFFSET(m))

/* NMI Registers */

#define R_IPC_IPC0NMI_STA                         (R_IPC_BASE + R_IPC_IPC0NMI_STA_OFFSET)
#define R_IPC_IPC0NMI_SET                         (R_IPC_BASE + R_IPC_IPC0NMI_SET_OFFSET)
#define R_IPC_IPC0NMI_CLR                         (R_IPC_BASE + R_IPC_IPC0NMI_CLR_OFFSET)

#define R_IPC_IPC1NMI_STA                         (R_IPC_BASE + R_IPC_IPC1NMI_STA_OFFSET)
#define R_IPC_IPC1NMI_SET                         (R_IPC_BASE + R_IPC_IPC1NMI_SET_OFFSET)
#define R_IPC_IPC1NMI_CLR                         (R_IPC_BASE + R_IPC_IPC1NMI_CLR_OFFSET)

/* IPC Channel Registers - Core 0 to Core 1 */

#define R_IPC_IPC0_CH0_STA                        (R_IPC_BASE + R_IPC_IPC0_OFFSET + RA_IPC_CH0_OFFSET + RA_IPC_CH_STA_OFFSET)
#define R_IPC_IPC0_CH0_SET                        (R_IPC_BASE + R_IPC_IPC0_OFFSET + RA_IPC_CH0_OFFSET + RA_IPC_CH_SET_OFFSET)
#define R_IPC_IPC0_CH0_TXD                        (R_IPC_BASE + R_IPC_IPC0_OFFSET + RA_IPC_CH0_OFFSET + RA_IPC_CH_TXD_OFFSET)
#define R_IPC_IPC0_CH0_RXD                        (R_IPC_BASE + R_IPC_IPC0_OFFSET + RA_IPC_CH0_OFFSET + RA_IPC_CH_RXD_OFFSET)
#define R_IPC_IPC0_CH0_CLR                        (R_IPC_BASE + R_IPC_IPC0_OFFSET + RA_IPC_CH0_OFFSET + RA_IPC_CH_CLR_OFFSET)

#define R_IPC_IPC0_CH1_STA                        (R_IPC_BASE + R_IPC_IPC0_OFFSET + RA_IPC_CH1_OFFSET + RA_IPC_CH_STA_OFFSET)
#define R_IPC_IPC0_CH1_SET                        (R_IPC_BASE + R_IPC_IPC0_OFFSET + RA_IPC_CH1_OFFSET + RA_IPC_CH_SET_OFFSET)
#define R_IPC_IPC0_CH1_TXD                        (R_IPC_BASE + R_IPC_IPC0_OFFSET + RA_IPC_CH1_OFFSET + RA_IPC_CH_TXD_OFFSET)
#define R_IPC_IPC0_CH1_RXD                        (R_IPC_BASE + R_IPC_IPC0_OFFSET + RA_IPC_CH1_OFFSET + RA_IPC_CH_RXD_OFFSET)
#define R_IPC_IPC0_CH1_CLR                        (R_IPC_BASE + R_IPC_IPC0_OFFSET + RA_IPC_CH1_OFFSET + RA_IPC_CH_CLR_OFFSET)

/* IPC Channel Registers - Core 1 to Core 0 */

#define R_IPC_IPC1_CH0_STA                        (R_IPC_BASE + R_IPC_IPC1_OFFSET + RA_IPC_CH0_OFFSET + RA_IPC_CH_STA_OFFSET)
#define R_IPC_IPC1_CH0_SET                        (R_IPC_BASE + R_IPC_IPC1_OFFSET + RA_IPC_CH0_OFFSET + RA_IPC_CH_SET_OFFSET)
#define R_IPC_IPC1_CH0_TXD                        (R_IPC_BASE + R_IPC_IPC1_OFFSET + RA_IPC_CH0_OFFSET + RA_IPC_CH_TXD_OFFSET)
#define R_IPC_IPC1_CH0_RXD                        (R_IPC_BASE + R_IPC_IPC1_OFFSET + RA_IPC_CH0_OFFSET + RA_IPC_CH_RXD_OFFSET)
#define R_IPC_IPC1_CH0_CLR                        (R_IPC_BASE + R_IPC_IPC1_OFFSET + RA_IPC_CH0_OFFSET + RA_IPC_CH_CLR_OFFSET)

#define R_IPC_IPC1_CH1_STA                        (R_IPC_BASE + R_IPC_IPC1_OFFSET + RA_IPC_CH1_OFFSET + RA_IPC_CH_STA_OFFSET)
#define R_IPC_IPC1_CH1_SET                        (R_IPC_BASE + R_IPC_IPC1_OFFSET + RA_IPC_CH1_OFFSET + RA_IPC_CH_SET_OFFSET)
#define R_IPC_IPC1_CH1_TXD                        (R_IPC_BASE + R_IPC_IPC1_OFFSET + RA_IPC_CH1_OFFSET + RA_IPC_CH_TXD_OFFSET)
#define R_IPC_IPC1_CH1_RXD                        (R_IPC_BASE + R_IPC_IPC1_OFFSET + RA_IPC_CH1_OFFSET + RA_IPC_CH_RXD_OFFSET)
#define R_IPC_IPC1_CH1_CLR                        (R_IPC_BASE + R_IPC_IPC1_OFFSET + RA_IPC_CH1_OFFSET + RA_IPC_CH_CLR_OFFSET)

/* Register bit definitions */

/* IPCSEM Register bit definitions */

#define IPC_IPCSEM_LOCK                            (1 << 0)  /* Indicates the shared resource is locked */

/* IPCNMI Register bit definitions */

#define IPC_IPCNMI_STA_NMI                         (1 << 0)  /* NMI Status */
#define IPC_IPCNMI_SET_SET                         (1 << 0)  /* NMI Set Request */
#define IPC_IPCNMI_CLR_CLR                         (1 << 0)  /* NMI Clear */

/* IPC Channel Status Register (STA) bit definitions */

#define IPC_CH_STA_IRQ0                            (1 << 0)   /* IRQ0 Status */
#define IPC_CH_STA_IRQ1                            (1 << 1)   /* IRQ1 Status */
#define IPC_CH_STA_IRQ2                            (1 << 2)   /* IRQ2 Status */
#define IPC_CH_STA_IRQ3                            (1 << 3)   /* IRQ3 Status */
#define IPC_CH_STA_IRQ4                            (1 << 4)   /* IRQ4 Status */
#define IPC_CH_STA_IRQ5                            (1 << 5)   /* IRQ5 Status */
#define IPC_CH_STA_IRQ6                            (1 << 6)   /* IRQ6 Status */
#define IPC_CH_STA_IRQ7                            (1 << 7)   /* IRQ7 Status */
#define IPC_CH_STA_IRQ_MASK                        (0xFF)     /* All IRQ bits mask */
#define IPC_CH_STA_RDY                             (1 << 16)  /* Ready Status - FIFO not empty */
#define IPC_CH_STA_FULL                            (1 << 17)  /* FIFO Full Status */
#define IPC_CH_STA_RERR                            (1 << 24)  /* Read Error - tried to read from empty FIFO */
#define IPC_CH_STA_FERR                            (1 << 25)  /* FIFO Error - tried to write to full FIFO */

/* IPC Channel Set Register (SET) bit definitions */

#define IPC_CH_SET_SET0                            (1 << 0)   /* Set IRQ0 */
#define IPC_CH_SET_SET1                            (1 << 1)   /* Set IRQ1 */
#define IPC_CH_SET_SET2                            (1 << 2)   /* Set IRQ2 */
#define IPC_CH_SET_SET3                            (1 << 3)   /* Set IRQ3 */
#define IPC_CH_SET_SET4                            (1 << 4)   /* Set IRQ4 */
#define IPC_CH_SET_SET5                            (1 << 5)   /* Set IRQ5 */
#define IPC_CH_SET_SET6                            (1 << 6)   /* Set IRQ6 */
#define IPC_CH_SET_SET7                            (1 << 7)   /* Set IRQ7 */
#define IPC_CH_SET_MASK                            (0xFF)     /* All SET bits mask */

/* IPC Channel Clear Register (CLR) bit definitions */

#define IPC_CH_CLR_CLR0                            (1 << 0)   /* Clear IRQ0 */
#define IPC_CH_CLR_CLR1                            (1 << 1)   /* Clear IRQ1 */
#define IPC_CH_CLR_CLR2                            (1 << 2)   /* Clear IRQ2 */
#define IPC_CH_CLR_CLR3                            (1 << 3)   /* Clear IRQ3 */
#define IPC_CH_CLR_CLR4                            (1 << 4)   /* Clear IRQ4 */
#define IPC_CH_CLR_CLR5                            (1 << 5)   /* Clear IRQ5 */
#define IPC_CH_CLR_CLR6                            (1 << 6)   /* Clear IRQ6 */
#define IPC_CH_CLR_CLR7                            (1 << 7)   /* Clear IRQ7 */
#define IPC_CH_CLR_MASK                            (0xFF)     /* All CLR bits mask */
#define IPC_CH_CLR_RST                             (1 << 16)  /* Reset Channel - resets message FIFO */
#define IPC_CH_CLR_RCLR                            (1 << 24)  /* Clear Read Error */
#define IPC_CH_CLR_FCLR                            (1 << 25)  /* Clear FIFO Error */

/* Backward compatibility aliases (default to IRQ0 for simple usage) */

#define IPC_CH_STA_IRQ                             IPC_CH_STA_IRQ0
#define IPC_CH_SET_SET                             IPC_CH_SET_SET0
#define IPC_CH_CLR_CLR                             IPC_CH_CLR_CLR0

/* Configuration Constants */

#define IPC_MAX_SEMAPHORES                         16         /* 16 semaphores available */
#define IPC_MAX_IPC_BLOCKS                         2          /* IPC0 and IPC1 */
#define IPC_MAX_CHANNELS_PER_BLOCK                 2          /* 2 channels per IPC block */
#define IPC_MAX_CHANNELS                           (IPC_MAX_IPC_BLOCKS * IPC_MAX_CHANNELS_PER_BLOCK)

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_IPC_H */
