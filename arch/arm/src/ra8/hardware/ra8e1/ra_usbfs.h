/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_usbfs.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_USBFS_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_USBFS_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* USBFS Base Address */
#ifndef R_USBFS_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_USBFS_BASE           0x40250000
#else
#define R_USBFS_BASE           0x50250000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_USBFS_CH_STRIDE    0x00000004
#define R_USBFS_CH_BASE(ch)   (R_USBFS_BASE + ((uint32_t)(ch) * R_USBFS_CH_STRIDE))

/* USBFS Register Offsets */

#define R_USBFS_SYSCFG_OFFSET                     0x00000000  /* System Configuration Control Register */
#define R_USBFS_SYSSTS0_OFFSET                    0x00000004  /* System Configuration Status Register 0 */
#define R_USBFS_DVSTCTR0_OFFSET                   0x00000008  /* Device State Control Register 0 */
#define R_USBFS_CFIFO_OFFSET                      0x00000014  /* CFIFO Port Register */
#define R_USBFS_CFIFOL_OFFSET                     0x00000014  /* CFIFO Port Register */
/* D%sFIFO Registers (0-1) */
#define R_USBFS_DFIFO_OFFSET                      0x00000018  /* D%sFIFO Port Register */
#define R_USBFS_DFIFO_INCREMENT                   0x00000004
/* D%sFIFOL Registers (0-1) */
#define R_USBFS_DFIFOL_OFFSET                     0x00000018  /* D%sFIFO Port Register */
#define R_USBFS_DFIFOL_INCREMENT                  0x00000004
#define R_USBFS_CFIFOSEL_OFFSET                   0x00000020  /* CFIFO Port Select Register */
#define R_USBFS_CFIFOCTR_OFFSET                   0x00000022  /* CFIFO Port Control Register */
/* D%sFIFOSEL Registers (0-1) */
#define R_USBFS_DFIFOSEL_OFFSET                   0x00000028  /* D%sFIFO Port Select Register */
#define R_USBFS_DFIFOSEL_INCREMENT                0x00000004
/* D%sFIFOCTR Registers (0-1) */
#define R_USBFS_DFIFOCTR_OFFSET                   0x0000002a  /* D%sFIFO Port Control Register */
#define R_USBFS_DFIFOCTR_INCREMENT                0x00000004
#define R_USBFS_INTENB0_OFFSET                    0x00000030  /* Interrupt Enable Register 0 */
#define R_USBFS_INTENB1_OFFSET                    0x00000032  /* Interrupt Enable Register 1 */
#define R_USBFS_BRDYENB_OFFSET                    0x00000036  /* BRDY Interrupt Enable Register */
#define R_USBFS_NRDYENB_OFFSET                    0x00000038  /* NRDY Interrupt Enable Register */
#define R_USBFS_BEMPENB_OFFSET                    0x0000003a  /* BEMP Interrupt Enable Register */
#define R_USBFS_SOFCFG_OFFSET                     0x0000003c  /* SOF Output Configuration Register */
#define R_USBFS_INTSTS0_OFFSET                    0x00000040  /* Interrupt Status Register 0 */
#define R_USBFS_INTSTS1_OFFSET                    0x00000042  /* Interrupt Status Register 1 */
#define R_USBFS_BRDYSTS_OFFSET                    0x00000046  /* BRDY Interrupt Status Register */
#define R_USBFS_NRDYSTS_OFFSET                    0x00000048  /* NRDY Interrupt Status Register */
#define R_USBFS_BEMPSTS_OFFSET                    0x0000004a  /* BEMP Interrupt Status Register */
#define R_USBFS_FRMNUM_OFFSET                     0x0000004c  /* Frame Number Register */
#define R_USBFS_DVCHGR_OFFSET                     0x0000004e  /* Device State Change Register */
#define R_USBFS_USBADDR_OFFSET                    0x00000050  /* USB Address Register */
#define R_USBFS_USBREQ_OFFSET                     0x00000054  /* USB Request Type Register */
#define R_USBFS_USBVAL_OFFSET                     0x00000056  /* USB Request Value Register */
#define R_USBFS_USBINDX_OFFSET                    0x00000058  /* USB Request Index Register */
#define R_USBFS_USBLENG_OFFSET                    0x0000005a  /* USB Request Length Register */
#define R_USBFS_DCPCFG_OFFSET                     0x0000005c  /* DCP Configuration Register */
#define R_USBFS_DCPMAXP_OFFSET                    0x0000005e  /* DCP Maximum Packet Size Register */
#define R_USBFS_DCPCTR_OFFSET                     0x00000060  /* DCP Control Register */
#define R_USBFS_PIPESEL_OFFSET                    0x00000064  /* Pipe Window Select Register */
#define R_USBFS_PIPECFG_OFFSET                    0x00000068  /* Pipe Configuration Register */
#define R_USBFS_PIPEMAXP_OFFSET                   0x0000006c  /* Pipe Maximum Packet Size Register */
#define R_USBFS_PIPEPERI_OFFSET                   0x0000006e  /* Pipe Cycle Control Register */
/* PIPE%sCTR Registers (1-5) */
#define R_USBFS_PIPECTR_OFFSET                    0x00000070  /* PIPE%s Control Registers */
#define R_USBFS_PIPECTR_INCREMENT                 0x00000002
/* PIPE%sTRE Registers (1-5) */
#define R_USBFS_PIPETRE_OFFSET                    0x00000090  /* PIPE%s Transaction Counter Enable Register */
#define R_USBFS_PIPETRE_INCREMENT                 0x00000004
/* PIPE%sTRN Registers (1-5) */
#define R_USBFS_PIPETRN_OFFSET                    0x00000092  /* PIPE%s Transaction Counter Register */
#define R_USBFS_PIPETRN_INCREMENT                 0x00000004
/* DEVADD%s Registers (0-5) */
#define R_USBFS_DEVADD_OFFSET                     0x000000d0  /* Device Address %s Configuration Register */
#define R_USBFS_DEVADD_INCREMENT                  0x00000002
#define R_USBFS_DPUSR0R_OFFSET                    0x00000400  /* Deep Software Standby USB Transceiver Control/Pin Monitor Register */
#define R_USBFS_DPUSR1R_OFFSET                    0x00000404  /* Deep Software Standby USB Suspend/Resume Interrupt Register */

/* USBFS Register Addresses */

#define R_USBFS_SYSCFG                            (R_USBFS_BASE + R_USBFS_SYSCFG_OFFSET)
#define R_USBFS_SYSSTS0                           (R_USBFS_BASE + R_USBFS_SYSSTS0_OFFSET)
#define R_USBFS_DVSTCTR0                          (R_USBFS_BASE + R_USBFS_DVSTCTR0_OFFSET)
#define R_USBFS_CFIFO                             (R_USBFS_BASE + R_USBFS_CFIFO_OFFSET)
#define R_USBFS_CFIFOL                            (R_USBFS_BASE + R_USBFS_CFIFOL_OFFSET)
#define R_USBFS_DFIFO(n)                          (R_USBFS_BASE + R_USBFS_DFIFO_OFFSET + (n)*0x00000004)
#define R_USBFS_DFIFOL(n)                         (R_USBFS_BASE + R_USBFS_DFIFOL_OFFSET + (n)*0x00000004)
#define R_USBFS_CFIFOSEL                          (R_USBFS_BASE + R_USBFS_CFIFOSEL_OFFSET)
#define R_USBFS_CFIFOCTR                          (R_USBFS_BASE + R_USBFS_CFIFOCTR_OFFSET)
#define R_USBFS_DFIFOSEL(n)                       (R_USBFS_BASE + R_USBFS_DFIFOSEL_OFFSET + (n)*0x00000004)
#define R_USBFS_DFIFOCTR(n)                       (R_USBFS_BASE + R_USBFS_DFIFOCTR_OFFSET + (n)*0x00000004)
#define R_USBFS_INTENB0                           (R_USBFS_BASE + R_USBFS_INTENB0_OFFSET)
#define R_USBFS_INTENB1                           (R_USBFS_BASE + R_USBFS_INTENB1_OFFSET)
#define R_USBFS_BRDYENB                           (R_USBFS_BASE + R_USBFS_BRDYENB_OFFSET)
#define R_USBFS_NRDYENB                           (R_USBFS_BASE + R_USBFS_NRDYENB_OFFSET)
#define R_USBFS_BEMPENB                           (R_USBFS_BASE + R_USBFS_BEMPENB_OFFSET)
#define R_USBFS_SOFCFG                            (R_USBFS_BASE + R_USBFS_SOFCFG_OFFSET)
#define R_USBFS_INTSTS0                           (R_USBFS_BASE + R_USBFS_INTSTS0_OFFSET)
#define R_USBFS_INTSTS1                           (R_USBFS_BASE + R_USBFS_INTSTS1_OFFSET)
#define R_USBFS_BRDYSTS                           (R_USBFS_BASE + R_USBFS_BRDYSTS_OFFSET)
#define R_USBFS_NRDYSTS                           (R_USBFS_BASE + R_USBFS_NRDYSTS_OFFSET)
#define R_USBFS_BEMPSTS                           (R_USBFS_BASE + R_USBFS_BEMPSTS_OFFSET)
#define R_USBFS_FRMNUM                            (R_USBFS_BASE + R_USBFS_FRMNUM_OFFSET)
#define R_USBFS_DVCHGR                            (R_USBFS_BASE + R_USBFS_DVCHGR_OFFSET)
#define R_USBFS_USBADDR                           (R_USBFS_BASE + R_USBFS_USBADDR_OFFSET)
#define R_USBFS_USBREQ                            (R_USBFS_BASE + R_USBFS_USBREQ_OFFSET)
#define R_USBFS_USBVAL                            (R_USBFS_BASE + R_USBFS_USBVAL_OFFSET)
#define R_USBFS_USBINDX                           (R_USBFS_BASE + R_USBFS_USBINDX_OFFSET)
#define R_USBFS_USBLENG                           (R_USBFS_BASE + R_USBFS_USBLENG_OFFSET)
#define R_USBFS_DCPCFG                            (R_USBFS_BASE + R_USBFS_DCPCFG_OFFSET)
#define R_USBFS_DCPMAXP                           (R_USBFS_BASE + R_USBFS_DCPMAXP_OFFSET)
#define R_USBFS_DCPCTR                            (R_USBFS_BASE + R_USBFS_DCPCTR_OFFSET)
#define R_USBFS_PIPESEL                           (R_USBFS_BASE + R_USBFS_PIPESEL_OFFSET)
#define R_USBFS_PIPECFG                           (R_USBFS_BASE + R_USBFS_PIPECFG_OFFSET)
#define R_USBFS_PIPEMAXP                          (R_USBFS_BASE + R_USBFS_PIPEMAXP_OFFSET)
#define R_USBFS_PIPEPERI                          (R_USBFS_BASE + R_USBFS_PIPEPERI_OFFSET)
#define R_USBFS_PIPECTR(n)                        (R_USBFS_BASE + R_USBFS_PIPECTR_OFFSET + (n)*0x00000002)
#define R_USBFS_PIPETRE(n)                        (R_USBFS_BASE + R_USBFS_PIPETRE_OFFSET + (n)*0x00000004)
#define R_USBFS_PIPETRN(n)                        (R_USBFS_BASE + R_USBFS_PIPETRN_OFFSET + (n)*0x00000004)
#define R_USBFS_DEVADD(n)                         (R_USBFS_BASE + R_USBFS_DEVADD_OFFSET + (n)*0x00000002)
#define R_USBFS_DPUSR0R                           (R_USBFS_BASE + R_USBFS_DPUSR0R_OFFSET)
#define R_USBFS_DPUSR1R                           (R_USBFS_BASE + R_USBFS_DPUSR1R_OFFSET)

/* Register bit definitions */
/* SYSCFG Register bit definitions */
#define R_USBFS_SYSCFG_USBE                       (1 << 0)  /* USBFS Operation Enable */

#define R_USBFS_SYSCFG_DPRPU                      (1 << 4)  /* D+ Line Resistor Control */

#define R_USBFS_SYSCFG_DRPD                       (1 << 5)  /* D+/D– Line Resistor Control */

#define R_USBFS_SYSCFG_DCFM                       (1 << 6)  /* Controller Function Select */

#define R_USBFS_SYSCFG_SCKE                       (1 << 10)  /* USB Clock Enable */

/* SYSSTS0 Register bit definitions */
#define R_USBFS_SYSSTS0_LNST_SHIFT                (0)  /* USB Data Line Status Monitor */
#define R_USBFS_SYSSTS0_LNST_MASK                 0x3

#define R_USBFS_SYSSTS0_IDMON                     (1 << 2)  /* External ID0 Input Pin Monitor */

#define R_USBFS_SYSSTS0_SOFEA                     (1 << 5)  /* Active Monitor When the Host Controller Is Selected */

#define R_USBFS_SYSSTS0_HTACT                     (1 << 6)  /* USB Host Sequencer Status Monitor */

#define R_USBFS_SYSSTS0_OVCMON_SHIFT              (14)  /* External USB_OVRCURA, USB_OVRCURA-DS, USB_OVRCURB or USB_OVRCURB-DS Input Pin Monitor */
#define R_USBFS_SYSSTS0_OVCMON_MASK               0xc000

/* DVSTCTR0 Register bit definitions */
#define R_USBFS_DVSTCTR0_RHST_SHIFT               (0)  /* USB Bus Reset Status */
#define R_USBFS_DVSTCTR0_RHST_MASK                0x7
#  define R_USBFS_DVSTCTR0_RHST_000                       (0 << R_USBFS_DVSTCTR0_RHST_SHIFT)  /* In host controller mode: Communication speed indeterminate (powered state or no connection) In device controller mode: Communication speed indeterminate  */
#  define R_USBFS_DVSTCTR0_RHST_001                       (1 << R_USBFS_DVSTCTR0_RHST_SHIFT)  /* In host controller mode: Low-speed connection In device controller mode: USB bus reset in progress  */
#  define R_USBFS_DVSTCTR0_RHST_010                       (2 << R_USBFS_DVSTCTR0_RHST_SHIFT)  /* In host controller mode: Full-speed connection In device controller mode: USB bus reset in progress or full-speed connection  */
#  define R_USBFS_DVSTCTR0_RHST_011                       (3 << R_USBFS_DVSTCTR0_RHST_SHIFT)  /* Setting prohibited */

#define R_USBFS_DVSTCTR0_UACT                     (1 << 4)  /* USB Bus Enable */

#define R_USBFS_DVSTCTR0_RESUME                   (1 << 5)  /* Resume Output */

#define R_USBFS_DVSTCTR0_USBRST                   (1 << 6)  /* USB Bus Reset Output */

#define R_USBFS_DVSTCTR0_RWUPE                    (1 << 7)  /* Wakeup Detection Enable */

#define R_USBFS_DVSTCTR0_WKUP                     (1 << 8)  /* Wakeup Output */

#define R_USBFS_DVSTCTR0_VBUSEN                   (1 << 9)  /* USB_VBUSEN Output Pin Control */

#define R_USBFS_DVSTCTR0_EXICEN                   (1 << 10)  /* USB_EXICEN Output Pin Control */

#define R_USBFS_DVSTCTR0_HNPBTOA                  (1 << 11)  /* Host Negotiation Protocol (HNP) Control */

/* CFIFO Register bit definitions */
#define R_USBFS_CFIFO_FIFOPORT_SHIFT              (0)  /* FIFO Port */
#define R_USBFS_CFIFO_FIFOPORT_MASK               0xffff

/* CFIFOL Register bit definitions */
#define R_USBFS_CFIFOL_FIFOPORT_SHIFT             (0)  /* FIFO Port */
#define R_USBFS_CFIFOL_FIFOPORT_MASK              0xff

/* DFIFO Register bit definitions */
#define R_USBFS_DFIFO_FIFOPORT_SHIFT              (0)  /* FIFO Port */
#define R_USBFS_DFIFO_FIFOPORT_MASK               0xffff

/* DFIFOL Register bit definitions */
#define R_USBFS_DFIFOL_FIFOPORT_SHIFT             (0)  /* FIFO Port */
#define R_USBFS_DFIFOL_FIFOPORT_MASK              0xff

/* CFIFOSEL Register bit definitions */
#define R_USBFS_CFIFOSEL_CURPIPE_SHIFT            (0)  /* CFIFO Port Access Pipe Specification */
#define R_USBFS_CFIFOSEL_CURPIPE_MASK             0xf
#  define R_USBFS_CFIFOSEL_CURPIPE_0X0                    (0 << R_USBFS_CFIFOSEL_CURPIPE_SHIFT)  /* Default Control Pipe */
#  define R_USBFS_CFIFOSEL_CURPIPE_0X1                    (0 << R_USBFS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 1 */
#  define R_USBFS_CFIFOSEL_CURPIPE_0X2                    (0 << R_USBFS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 2 */
#  define R_USBFS_CFIFOSEL_CURPIPE_0X3                    (0 << R_USBFS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 3 */
#  define R_USBFS_CFIFOSEL_CURPIPE_0X4                    (0 << R_USBFS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 4 */
#  define R_USBFS_CFIFOSEL_CURPIPE_0X5                    (0 << R_USBFS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 5 */
#  define R_USBFS_CFIFOSEL_CURPIPE_0X6                    (0 << R_USBFS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 6 */
#  define R_USBFS_CFIFOSEL_CURPIPE_0X7                    (0 << R_USBFS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 7 */
#  define R_USBFS_CFIFOSEL_CURPIPE_0X8                    (0 << R_USBFS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 8 */
#  define R_USBFS_CFIFOSEL_CURPIPE_0X9                    (0 << R_USBFS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 9 */

#define R_USBFS_CFIFOSEL_ISEL                     (1 << 5)  /* CFIFO Port Access Direction When DCP Is Selected */

#define R_USBFS_CFIFOSEL_BIGEND                   (1 << 8)  /* CFIFO Port Endian Control */

#define R_USBFS_CFIFOSEL_MBW                      (1 << 10)  /* CFIFO Port Access Bit Width */

#define R_USBFS_CFIFOSEL_REW                      (1 << 14)  /* Buffer Pointer Rewind */

#define R_USBFS_CFIFOSEL_RCNT                     (1 << 15)  /* Read Count Mode */

/* CFIFOCTR Register bit definitions */
#define R_USBFS_CFIFOCTR_DTLN_SHIFT               (0)  /* Receive Data Length */
#define R_USBFS_CFIFOCTR_DTLN_MASK                0x1ff

#define R_USBFS_CFIFOCTR_FRDY                     (1 << 13)  /* FIFO Port Ready */

#define R_USBFS_CFIFOCTR_BCLR                     (1 << 14)  /* CPU Buffer Clear */

#define R_USBFS_CFIFOCTR_BVAL                     (1 << 15)  /* Buffer Memory Valid Flag */

/* DFIFOSEL Register bit definitions */
#define R_USBFS_DFIFOSEL_CURPIPE_SHIFT            (0)  /* FIFO Port Access Pipe Specification */
#define R_USBFS_DFIFOSEL_CURPIPE_MASK             0xf
#  define R_USBFS_DFIFOSEL_CURPIPE_0X0                    (0 << R_USBFS_DFIFOSEL_CURPIPE_SHIFT)  /* Default Control Pipe */
#  define R_USBFS_DFIFOSEL_CURPIPE_0X1                    (0 << R_USBFS_DFIFOSEL_CURPIPE_SHIFT)  /* Pipe 1 */
#  define R_USBFS_DFIFOSEL_CURPIPE_0X2                    (0 << R_USBFS_DFIFOSEL_CURPIPE_SHIFT)  /* Pipe 2 */
#  define R_USBFS_DFIFOSEL_CURPIPE_0X3                    (0 << R_USBFS_DFIFOSEL_CURPIPE_SHIFT)  /* Pipe 3 */
#  define R_USBFS_DFIFOSEL_CURPIPE_0X4                    (0 << R_USBFS_DFIFOSEL_CURPIPE_SHIFT)  /* Pipe 4 */
#  define R_USBFS_DFIFOSEL_CURPIPE_0X5                    (0 << R_USBFS_DFIFOSEL_CURPIPE_SHIFT)  /* Pipe 5 */
#  define R_USBFS_DFIFOSEL_CURPIPE_0X6                    (0 << R_USBFS_DFIFOSEL_CURPIPE_SHIFT)  /* Pipe 6 */
#  define R_USBFS_DFIFOSEL_CURPIPE_0X7                    (0 << R_USBFS_DFIFOSEL_CURPIPE_SHIFT)  /* Pipe 7 */
#  define R_USBFS_DFIFOSEL_CURPIPE_0X8                    (0 << R_USBFS_DFIFOSEL_CURPIPE_SHIFT)  /* Pipe 8 */
#  define R_USBFS_DFIFOSEL_CURPIPE_0X9                    (0 << R_USBFS_DFIFOSEL_CURPIPE_SHIFT)  /* Pipe 9 */

#define R_USBFS_DFIFOSEL_BIGEND                   (1 << 8)  /* FIFO Port Endian Control */

#define R_USBFS_DFIFOSEL_MBW                      (1 << 10)  /* FIFO Port Access Bit Width */

#define R_USBFS_DFIFOSEL_DREQE                    (1 << 12)  /* DMA/DTC Transfer Request Enable */

#define R_USBFS_DFIFOSEL_DCLRM                    (1 << 13)  /* Auto Buffer Memory Clear Mode Accessed after Specified Pipe Data is Read */

#define R_USBFS_DFIFOSEL_REW                      (1 << 14)  /* Buffer Pointer Rewind */

#define R_USBFS_DFIFOSEL_RCNT                     (1 << 15)  /* Read Count Mode */

/* DFIFOCTR Register bit definitions */
#define R_USBFS_DFIFOCTR_DTLN_SHIFT               (0)  /* Receive Data Length */
#define R_USBFS_DFIFOCTR_DTLN_MASK                0x1ff

#define R_USBFS_DFIFOCTR_FRDY                     (1 << 13)  /* FIFO Port Ready */

#define R_USBFS_DFIFOCTR_BCLR                     (1 << 14)  /* CPU Buffer Clear */

#define R_USBFS_DFIFOCTR_BVAL                     (1 << 15)  /* Buffer Memory Valid Flag */

/* INTENB0 Register bit definitions */
#define R_USBFS_INTENB0_BRDYE                     (1 << 8)  /* Buffer Ready Interrupt Enable */

#define R_USBFS_INTENB0_NRDYE                     (1 << 9)  /* Buffer Not Ready Response Interrupt Enable */

#define R_USBFS_INTENB0_BEMPE                     (1 << 10)  /* Buffer Empty Interrupt Enable */

#define R_USBFS_INTENB0_CTRE                      (1 << 11)  /* Control Transfer Stage Transition Interrupt Enable */

#define R_USBFS_INTENB0_DVSE                      (1 << 12)  /* Device State Transition Interrupt Enable */

#define R_USBFS_INTENB0_SOFE                      (1 << 13)  /* Frame Number Update Interrupt Enable */

#define R_USBFS_INTENB0_RSME                      (1 << 14)  /* Resume Interrupt Enable */

#define R_USBFS_INTENB0_VBSE                      (1 << 15)  /* VBUS Interrupt Enable */

/* INTENB1 Register bit definitions */
#define R_USBFS_INTENB1_SACKE                     (1 << 4)  /* Setup Transaction Normal Response Interrupt Enable */

#define R_USBFS_INTENB1_SIGNE                     (1 << 5)  /* Setup Transaction Error Interrupt Enable */

#define R_USBFS_INTENB1_EOFERRE                   (1 << 6)  /* EOF Error Detection Interrupt Enable */

#define R_USBFS_INTENB1_ATTCHE                    (1 << 11)  /* Connection Detection Interrupt Enable */

#define R_USBFS_INTENB1_DTCHE                     (1 << 12)  /* Disconnection Detection Interrupt Enable */

#define R_USBFS_INTENB1_BCHGE                     (1 << 14)  /* USB Bus Change Interrupt Enable */

#define R_USBFS_INTENB1_OVRCRE                    (1 << 15)  /* Overcurrent Input Change Interrupt Enable */

/* BRDYENB Register bit definitions */
#define R_USBFS_BRDYENB_PIPE0BRDYE                (1 << 0)  /* BRDY Interrupt Enable for Pipe 0 */

#define R_USBFS_BRDYENB_PIPE1BRDYE                (1 << 1)  /* BRDY Interrupt Enable for Pipe 1 */

#define R_USBFS_BRDYENB_PIPE2BRDYE                (1 << 2)  /* BRDY Interrupt Enable for Pipe 2 */

#define R_USBFS_BRDYENB_PIPE3BRDYE                (1 << 3)  /* BRDY Interrupt Enable for Pipe 3 */

#define R_USBFS_BRDYENB_PIPE4BRDYE                (1 << 4)  /* BRDY Interrupt Enable for Pipe 4 */

#define R_USBFS_BRDYENB_PIPE5BRDYE                (1 << 5)  /* BRDY Interrupt Enable for Pipe 5 */

#define R_USBFS_BRDYENB_PIPE6BRDYE                (1 << 6)  /* BRDY Interrupt Enable for Pipe 6 */

#define R_USBFS_BRDYENB_PIPE7BRDYE                (1 << 7)  /* BRDY Interrupt Enable for Pipe 7 */

#define R_USBFS_BRDYENB_PIPE8BRDYE                (1 << 8)  /* BRDY Interrupt Enable for Pipe 8 */

#define R_USBFS_BRDYENB_PIPE9BRDYE                (1 << 9)  /* BRDY Interrupt Enable for Pipe 9 */

/* NRDYENB Register bit definitions */
#define R_USBFS_NRDYENB_PIPE0NRDYE                (1 << 0)  /* NRDY Interrupt Enable for Pipe 0 */

#define R_USBFS_NRDYENB_PIPE1NRDYE                (1 << 1)  /* NRDY Interrupt Enable for Pipe 1 */

#define R_USBFS_NRDYENB_PIPE2NRDYE                (1 << 2)  /* NRDY Interrupt Enable for Pipe 2 */

#define R_USBFS_NRDYENB_PIPE3NRDYE                (1 << 3)  /* NRDY Interrupt Enable for Pipe 3 */

#define R_USBFS_NRDYENB_PIPE4NRDYE                (1 << 4)  /* NRDY Interrupt Enable for Pipe 4 */

#define R_USBFS_NRDYENB_PIPE5NRDYE                (1 << 5)  /* NRDY Interrupt Enable for Pipe 5 */

#define R_USBFS_NRDYENB_PIPE6NRDYE                (1 << 6)  /* NRDY Interrupt Enable for Pipe 6 */

#define R_USBFS_NRDYENB_PIPE7NRDYE                (1 << 7)  /* NRDY Interrupt Enable for Pipe 7 */

#define R_USBFS_NRDYENB_PIPE8NRDYE                (1 << 8)  /* NRDY Interrupt Enable for Pipe 8 */

#define R_USBFS_NRDYENB_PIPE9NRDYE                (1 << 9)  /* NRDY Interrupt Enable for Pipe 9 */

/* BEMPENB Register bit definitions */
#define R_USBFS_BEMPENB_PIPE0BEMPE                (1 << 0)  /* BEMP Interrupt Enable for Pipe 0 */

#define R_USBFS_BEMPENB_PIPE1BEMPE                (1 << 1)  /* BEMP Interrupt Enable for Pipe 1 */

#define R_USBFS_BEMPENB_PIPE2BEMPE                (1 << 2)  /* BEMP Interrupt Enable for Pipe 2 */

#define R_USBFS_BEMPENB_PIPE3BEMPE                (1 << 3)  /* BEMP Interrupt Enable for Pipe 3 */

#define R_USBFS_BEMPENB_PIPE4BEMPE                (1 << 4)  /* BEMP Interrupt Enable for Pipe 4 */

#define R_USBFS_BEMPENB_PIPE5BEMPE                (1 << 5)  /* BEMP Interrupt Enable for Pipe 5 */

#define R_USBFS_BEMPENB_PIPE6BEMPE                (1 << 6)  /* BEMP Interrupt Enable for Pipe 6 */

#define R_USBFS_BEMPENB_PIPE7BEMPE                (1 << 7)  /* BEMP Interrupt Enable for Pipe 7 */

#define R_USBFS_BEMPENB_PIPE8BEMPE                (1 << 8)  /* BEMP Interrupt Enable for Pipe 8 */

#define R_USBFS_BEMPENB_PIPE9BEMPE                (1 << 9)  /* BEMP Interrupt Enable for Pipe 9 */

/* SOFCFG Register bit definitions */
#define R_USBFS_SOFCFG_EDGESTS                    (1 << 4)  /* Edge Interrupt Output Status Monitor */

#define R_USBFS_SOFCFG_BRDYM                      (1 << 6)  /* BRDY Interrupt Status Clear Timing */

#define R_USBFS_SOFCFG_TRNENSEL                   (1 << 8)  /* Transaction-Enabled Time Select */

/* INTSTS0 Register bit definitions */
#define R_USBFS_INTSTS0_CTSQ_SHIFT                (0)  /* Control Transfer Stage */
#define R_USBFS_INTSTS0_CTSQ_MASK                 0x7
#  define R_USBFS_INTSTS0_CTSQ_000                        (0 << R_USBFS_INTSTS0_CTSQ_SHIFT)  /* Idle or setup stage */
#  define R_USBFS_INTSTS0_CTSQ_001                        (1 << R_USBFS_INTSTS0_CTSQ_SHIFT)  /* Control read data stage */
#  define R_USBFS_INTSTS0_CTSQ_010                        (2 << R_USBFS_INTSTS0_CTSQ_SHIFT)  /* Control read status stage */
#  define R_USBFS_INTSTS0_CTSQ_011                        (3 << R_USBFS_INTSTS0_CTSQ_SHIFT)  /* Control write data stage */
#  define R_USBFS_INTSTS0_CTSQ_100                        (4 << R_USBFS_INTSTS0_CTSQ_SHIFT)  /* Control write status stage */
#  define R_USBFS_INTSTS0_CTSQ_101                        (5 << R_USBFS_INTSTS0_CTSQ_SHIFT)  /* Control write (no data) status stage */
#  define R_USBFS_INTSTS0_CTSQ_110                        (6 << R_USBFS_INTSTS0_CTSQ_SHIFT)  /* Control transfer sequence error */

#define R_USBFS_INTSTS0_VALID                     (1 << 3)  /* USB Request Reception */

#define R_USBFS_INTSTS0_DVSQ_SHIFT                (4)  /* Device State */
#define R_USBFS_INTSTS0_DVSQ_MASK                 0x70
#  define R_USBFS_INTSTS0_DVSQ_000                        (0 << R_USBFS_INTSTS0_DVSQ_SHIFT)  /* Powered state */
#  define R_USBFS_INTSTS0_DVSQ_001                        (1 << R_USBFS_INTSTS0_DVSQ_SHIFT)  /* Default state */
#  define R_USBFS_INTSTS0_DVSQ_010                        (2 << R_USBFS_INTSTS0_DVSQ_SHIFT)  /* Address state */
#  define R_USBFS_INTSTS0_DVSQ_011                        (3 << R_USBFS_INTSTS0_DVSQ_SHIFT)  /* Configured state */

#define R_USBFS_INTSTS0_VBSTS                     (1 << 7)  /* VBUS Input Status */

#define R_USBFS_INTSTS0_BRDY                      (1 << 8)  /* Buffer Ready Interrupt Status */

#define R_USBFS_INTSTS0_NRDY                      (1 << 9)  /* Buffer Not Ready Interrupt Status */

#define R_USBFS_INTSTS0_BEMP                      (1 << 10)  /* Buffer Empty Interrupt Status */

#define R_USBFS_INTSTS0_CTRT                      (1 << 11)  /* Control Transfer Stage Transition Interrupt Status */

#define R_USBFS_INTSTS0_DVST                      (1 << 12)  /* Device State Transition Interrupt Status */

#define R_USBFS_INTSTS0_SOFR                      (1 << 13)  /* Frame Number Refresh Interrupt Status */

#define R_USBFS_INTSTS0_RESM                      (1 << 14)  /* Resume Interrupt Status */

#define R_USBFS_INTSTS0_VBINT                     (1 << 15)  /* VBUS Interrupt Status */

/* INTSTS1 Register bit definitions */
#define R_USBFS_INTSTS1_SACK                      (1 << 4)  /* Setup Transaction Normal Response Interrupt Status */

#define R_USBFS_INTSTS1_SIGN                      (1 << 5)  /* Setup Transaction Error Interrupt Status */

#define R_USBFS_INTSTS1_EOFERR                    (1 << 6)  /* EOF Error Detection Interrupt Status */

#define R_USBFS_INTSTS1_ATTCH                     (1 << 11)  /* ATTCH Interrupt Status */

#define R_USBFS_INTSTS1_DTCH                      (1 << 12)  /* USB Disconnection Detection Interrupt Status */

#define R_USBFS_INTSTS1_BCHG                      (1 << 14)  /* USB Bus Change Interrupt Status */

#define R_USBFS_INTSTS1_OVRCR                     (1 << 15)  /* Overcurrent Input Change Interrupt Status */

/* BRDYSTS Register bit definitions */
#define R_USBFS_BRDYSTS_PIPE0BRDY                 (1 << 0)  /* BRDY Interrupt Status for Pipe 0 */

#define R_USBFS_BRDYSTS_PIPE1BRDY                 (1 << 1)  /* BRDY Interrupt Status for Pipe 1 */

#define R_USBFS_BRDYSTS_PIPE2BRDY                 (1 << 2)  /* BRDY Interrupt Status for Pipe 2 */

#define R_USBFS_BRDYSTS_PIPE3BRDY                 (1 << 3)  /* BRDY Interrupt Status for Pipe 3 */

#define R_USBFS_BRDYSTS_PIPE4BRDY                 (1 << 4)  /* BRDY Interrupt Status for Pipe 4 */

#define R_USBFS_BRDYSTS_PIPE5BRDY                 (1 << 5)  /* BRDY Interrupt Status for Pipe 5 */

#define R_USBFS_BRDYSTS_PIPE6BRDY                 (1 << 6)  /* BRDY Interrupt Status for Pipe 6 */

#define R_USBFS_BRDYSTS_PIPE7BRDY                 (1 << 7)  /* BRDY Interrupt Status for Pipe 7 */

#define R_USBFS_BRDYSTS_PIPE8BRDY                 (1 << 8)  /* BRDY Interrupt Status for Pipe 8 */

#define R_USBFS_BRDYSTS_PIPE9BRDY                 (1 << 9)  /* BRDY Interrupt Status for Pipe 9 */

/* NRDYSTS Register bit definitions */
#define R_USBFS_NRDYSTS_PIPE0NRDY                 (1 << 0)  /* NRDY Interrupt Status for Pipe 0 */

#define R_USBFS_NRDYSTS_PIPE1NRDY                 (1 << 1)  /* NRDY Interrupt Status for Pipe 1 */

#define R_USBFS_NRDYSTS_PIPE2NRDY                 (1 << 2)  /* NRDY Interrupt Status for Pipe 2 */

#define R_USBFS_NRDYSTS_PIPE3NRDY                 (1 << 3)  /* NRDY Interrupt Status for Pipe 3 */

#define R_USBFS_NRDYSTS_PIPE4NRDY                 (1 << 4)  /* NRDY Interrupt Status for Pipe 4 */

#define R_USBFS_NRDYSTS_PIPE5NRDY                 (1 << 5)  /* NRDY Interrupt Status for Pipe 5 */

#define R_USBFS_NRDYSTS_PIPE6NRDY                 (1 << 6)  /* NRDY Interrupt Status for Pipe 6 */

#define R_USBFS_NRDYSTS_PIPE7NRDY                 (1 << 7)  /* NRDY Interrupt Status for Pipe 7 */

#define R_USBFS_NRDYSTS_PIPE8NRDY                 (1 << 8)  /* NRDY Interrupt Status for Pipe 8 */

#define R_USBFS_NRDYSTS_PIPE9NRDY                 (1 << 9)  /* NRDY Interrupt Status for Pipe 9 */

/* BEMPSTS Register bit definitions */
#define R_USBFS_BEMPSTS_PIPE0BEMP                 (1 << 0)  /* BEMP Interrupt Status for Pipe 0 */

#define R_USBFS_BEMPSTS_PIPE1BEMP                 (1 << 1)  /* BEMP Interrupt Status for Pipe 1 */

#define R_USBFS_BEMPSTS_PIPE2BEMP                 (1 << 2)  /* BEMP Interrupt Status for Pipe 2 */

#define R_USBFS_BEMPSTS_PIPE3BEMP                 (1 << 3)  /* BEMP Interrupt Status for Pipe 3 */

#define R_USBFS_BEMPSTS_PIPE4BEMP                 (1 << 4)  /* BEMP Interrupt Status for Pipe 4 */

#define R_USBFS_BEMPSTS_PIPE5BEMP                 (1 << 5)  /* BEMP Interrupt Status for Pipe 5 */

#define R_USBFS_BEMPSTS_PIPE6BEMP                 (1 << 6)  /* BEMP Interrupt Status for Pipe 6 */

#define R_USBFS_BEMPSTS_PIPE7BEMP                 (1 << 7)  /* BEMP Interrupt Status for Pipe 7 */

#define R_USBFS_BEMPSTS_PIPE8BEMP                 (1 << 8)  /* BEMP Interrupt Status for Pipe 8 */

#define R_USBFS_BEMPSTS_PIPE9BEMP                 (1 << 9)  /* BEMP Interrupt Status for Pipe 9 */

/* FRMNUM Register bit definitions */
#define R_USBFS_FRMNUM_FRNM_SHIFT                 (0)  /* Frame Number */
#define R_USBFS_FRMNUM_FRNM_MASK                  0x7ff

#define R_USBFS_FRMNUM_CRCE                       (1 << 14)  /* Receive Data Error */

#define R_USBFS_FRMNUM_OVRN                       (1 << 15)  /* Overrun/Underrun Detection Status */

/* DVCHGR Register bit definitions */
#define R_USBFS_DVCHGR_DVCHG                      (1 << 15)  /* Device State Change */

/* USBADDR Register bit definitions */
#define R_USBFS_USBADDR_USBADDR_SHIFT             (0)  /* USB Address */
#define R_USBFS_USBADDR_USBADDR_MASK              0x7f

#define R_USBFS_USBADDR_STSRECOV_SHIFT            (8)  /* Status Recovery */
#define R_USBFS_USBADDR_STSRECOV_MASK             0xf00
#  define R_USBFS_USBADDR_STSRECOV_0X4                    (0 << R_USBFS_USBADDR_STSRECOV_SHIFT)  /* Recovery in device controller mode: Setting prohibited Recovery in host controller mode: Return to the low-speed state (bits DVSTCTR0.RHST[2:0] = 001b)  */
#  define R_USBFS_USBADDR_STSRECOV_0X8                    (0 << R_USBFS_USBADDR_STSRECOV_SHIFT)  /* Recovery in device controller mode: Setting prohibited Recovery in host controller mode: Return to the full-speed state (bits DVSTCTR0.RHST[2:0] = 010b)  */
#  define R_USBFS_USBADDR_STSRECOV_0X9                    (0 << R_USBFS_USBADDR_STSRECOV_SHIFT)  /* Recovery in device controller mode: Return to the full-speed state (bits DVSTCTR0.RHST[2:0] = 010b), bits INTSTS0.DVSQ[2:0] = 001b (default state) Recovery in host controller mode: Setting prohibited  */
#  define R_USBFS_USBADDR_STSRECOV_0XA                    (0 << R_USBFS_USBADDR_STSRECOV_SHIFT)  /* Recovery in device controller mode: Return to the full-speed state (bits DVSTCTR0.RHST[2:0] = 010b), bits INTSTS0.DVSQ[2:0] = 010b (address state) Recovery in host controller mode: Setting prohibited  */
#  define R_USBFS_USBADDR_STSRECOV_0XB                    (0 << R_USBFS_USBADDR_STSRECOV_SHIFT)  /* Recovery in device controller mode: Return to the full-speed state (bits DVSTCTR0.RHST[2:0] = 010b), bits INTSTS0.DVSQ[2:0] = 011b (configured state) Recovery in host controller mode: Setting prohibited  */

/* USBREQ Register bit definitions */
#define R_USBFS_USBREQ_BMREQUESTTYPE_SHIFT        (0)  /* Request Type */
#define R_USBFS_USBREQ_BMREQUESTTYPE_MASK         0xff

#define R_USBFS_USBREQ_BREQUEST_SHIFT             (8)  /* Request */
#define R_USBFS_USBREQ_BREQUEST_MASK              0xff00

/* USBVAL Register bit definitions */
#define R_USBFS_USBVAL_WVALUE_SHIFT               (0)  /* Value */
#define R_USBFS_USBVAL_WVALUE_MASK                0xffff

/* USBINDX Register bit definitions */
#define R_USBFS_USBINDX_WINDEX_SHIFT              (0)  /* Index */
#define R_USBFS_USBINDX_WINDEX_MASK               0xffff

/* USBLENG Register bit definitions */
#define R_USBFS_USBLENG_WLENTUH_SHIFT             (0)  /* Length */
#define R_USBFS_USBLENG_WLENTUH_MASK              0xffff

/* DCPCFG Register bit definitions */
#define R_USBFS_DCPCFG_DIR                        (1 << 4)  /* Transfer Direction */

#define R_USBFS_DCPCFG_SHTNAK                     (1 << 7)  /* Pipe Disabled at End of Transfer */

/* DCPMAXP Register bit definitions */
#define R_USBFS_DCPMAXP_MXPS_SHIFT                (0)  /* Maximum Packet Size */
#define R_USBFS_DCPMAXP_MXPS_MASK                 0x7f

#define R_USBFS_DCPMAXP_DEVSEL_SHIFT              (12)  /* Device Select */
#define R_USBFS_DCPMAXP_DEVSEL_MASK               0xf000
#  define R_USBFS_DCPMAXP_DEVSEL_0X0                      (0 << R_USBFS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0000b */
#  define R_USBFS_DCPMAXP_DEVSEL_0X1                      (0 << R_USBFS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0001b */
#  define R_USBFS_DCPMAXP_DEVSEL_0X2                      (0 << R_USBFS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0010b */
#  define R_USBFS_DCPMAXP_DEVSEL_0X3                      (0 << R_USBFS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0011b */
#  define R_USBFS_DCPMAXP_DEVSEL_0X4                      (0 << R_USBFS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0100b */
#  define R_USBFS_DCPMAXP_DEVSEL_0X5                      (0 << R_USBFS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0101b */

/* DCPCTR Register bit definitions */
#define R_USBFS_DCPCTR_PID_SHIFT                  (0)  /* Response PID */
#define R_USBFS_DCPCTR_PID_MASK                   0x3
#  define R_USBFS_DCPCTR_PID_00                           (0 << R_USBFS_DCPCTR_PID_SHIFT)  /* NAK response */
#  define R_USBFS_DCPCTR_PID_01                           (1 << R_USBFS_DCPCTR_PID_SHIFT)  /* BUF response (depends on the buffer state) */
#  define R_USBFS_DCPCTR_PID_10                           (2 << R_USBFS_DCPCTR_PID_SHIFT)  /* STALL response */
#  define R_USBFS_DCPCTR_PID_11                           (3 << R_USBFS_DCPCTR_PID_SHIFT)  /* STALL response */

#define R_USBFS_DCPCTR_CCPL                       (1 << 2)  /* Control Transfer End Enable */

#define R_USBFS_DCPCTR_PBUSY                      (1 << 5)  /* Pipe Busy */

#define R_USBFS_DCPCTR_SQMON                      (1 << 6)  /* Sequence Toggle Bit Monitor */

#define R_USBFS_DCPCTR_SQSET                      (1 << 7)  /* Sequence Toggle Bit Set */

#define R_USBFS_DCPCTR_SQCLR                      (1 << 8)  /* Sequence Toggle Bit Clear */

#define R_USBFS_DCPCTR_SUREQCLR                   (1 << 11)  /* SUREQ Bit Clear */

#define R_USBFS_DCPCTR_SUREQ                      (1 << 14)  /* Setup Token Transmission */

#define R_USBFS_DCPCTR_BSTS                       (1 << 15)  /* Buffer Status */

/* PIPESEL Register bit definitions */
#define R_USBFS_PIPESEL_PIPESEL_SHIFT             (0)  /* Pipe Window Select */
#define R_USBFS_PIPESEL_PIPESEL_MASK              0xf
#  define R_USBFS_PIPESEL_PIPESEL_0X0                     (0 << R_USBFS_PIPESEL_PIPESEL_SHIFT)  /* No pipe selected */
#  define R_USBFS_PIPESEL_PIPESEL_0X1                     (0 << R_USBFS_PIPESEL_PIPESEL_SHIFT)  /* Pipe 1 */
#  define R_USBFS_PIPESEL_PIPESEL_0X2                     (0 << R_USBFS_PIPESEL_PIPESEL_SHIFT)  /* Pipe 2 */
#  define R_USBFS_PIPESEL_PIPESEL_0X3                     (0 << R_USBFS_PIPESEL_PIPESEL_SHIFT)  /* Pipe 3 */
#  define R_USBFS_PIPESEL_PIPESEL_0X4                     (0 << R_USBFS_PIPESEL_PIPESEL_SHIFT)  /* Pipe 4 */
#  define R_USBFS_PIPESEL_PIPESEL_0X5                     (0 << R_USBFS_PIPESEL_PIPESEL_SHIFT)  /* Pipe 5 */
#  define R_USBFS_PIPESEL_PIPESEL_0X6                     (0 << R_USBFS_PIPESEL_PIPESEL_SHIFT)  /* Pipe 6 */
#  define R_USBFS_PIPESEL_PIPESEL_0X7                     (0 << R_USBFS_PIPESEL_PIPESEL_SHIFT)  /* Pipe 7 */
#  define R_USBFS_PIPESEL_PIPESEL_0X8                     (0 << R_USBFS_PIPESEL_PIPESEL_SHIFT)  /* Pipe 8 */
#  define R_USBFS_PIPESEL_PIPESEL_0X9                     (0 << R_USBFS_PIPESEL_PIPESEL_SHIFT)  /* Pipe 9 */

/* PIPECFG Register bit definitions */
#define R_USBFS_PIPECFG_EPNUM_SHIFT               (0)  /* Endpoint Number */
#define R_USBFS_PIPECFG_EPNUM_MASK                0xf

#define R_USBFS_PIPECFG_DIR                       (1 << 4)  /* Transfer Direction */

#define R_USBFS_PIPECFG_SHTNAK                    (1 << 7)  /* Pipe Disabled at End of Transfer */

#define R_USBFS_PIPECFG_DBLB                      (1 << 9)  /* Double Buffer Mode */

#define R_USBFS_PIPECFG_BFRE                      (1 << 10)  /* BRDY Interrupt Operation Specification */

#define R_USBFS_PIPECFG_TYPE_SHIFT                (14)  /* Transfer Type */
#define R_USBFS_PIPECFG_TYPE_MASK                 0xc000
#  define R_USBFS_PIPECFG_TYPE_00                         (0 << R_USBFS_PIPECFG_TYPE_SHIFT)  /* Pipe not used */
#  define R_USBFS_PIPECFG_TYPE_01                         (1 << R_USBFS_PIPECFG_TYPE_SHIFT)  /* Pipes 1 and 2: Bulk transfer Pipes 3 to 5: Bulk transfer Pipes 6 to 9: Setting prohibited  */
#  define R_USBFS_PIPECFG_TYPE_10                         (2 << R_USBFS_PIPECFG_TYPE_SHIFT)  /* Pipes 1 and 2: Setting prohibited Pipes 3 to 5: Setting prohibited Pipes 6 to 9: Interrupt transfer  */
#  define R_USBFS_PIPECFG_TYPE_11                         (3 << R_USBFS_PIPECFG_TYPE_SHIFT)  /* Pipes 1 and 2: Isochronous transfer Pipes 3 to 5: Setting prohibited Pipes 6 to 9: Setting prohibited  */

/* PIPEMAXP Register bit definitions */
#define R_USBFS_PIPEMAXP_MXPS_SHIFT               (0)  /* Maximum Packet Size */
#define R_USBFS_PIPEMAXP_MXPS_MASK                0x1ff

#define R_USBFS_PIPEMAXP_DEVSEL_SHIFT             (12)  /* Device Select */
#define R_USBFS_PIPEMAXP_DEVSEL_MASK              0xf000
#  define R_USBFS_PIPEMAXP_DEVSEL_0X0                     (0 << R_USBFS_PIPEMAXP_DEVSEL_SHIFT)  /* Address 0000b */
#  define R_USBFS_PIPEMAXP_DEVSEL_0X1                     (0 << R_USBFS_PIPEMAXP_DEVSEL_SHIFT)  /* Address 0001b */
#  define R_USBFS_PIPEMAXP_DEVSEL_0X2                     (0 << R_USBFS_PIPEMAXP_DEVSEL_SHIFT)  /* Address 0010b */
#  define R_USBFS_PIPEMAXP_DEVSEL_0X3                     (0 << R_USBFS_PIPEMAXP_DEVSEL_SHIFT)  /* Address 0011b */
#  define R_USBFS_PIPEMAXP_DEVSEL_0X4                     (0 << R_USBFS_PIPEMAXP_DEVSEL_SHIFT)  /* Address 0100b */
#  define R_USBFS_PIPEMAXP_DEVSEL_0X5                     (0 << R_USBFS_PIPEMAXP_DEVSEL_SHIFT)  /* Address 0101b */

/* PIPEPERI Register bit definitions */
#define R_USBFS_PIPEPERI_IITV_SHIFT               (0)  /* Interval Error Detection Interval */
#define R_USBFS_PIPEPERI_IITV_MASK                0x7

#define R_USBFS_PIPEPERI_IFIS                     (1 << 12)  /* Isochronous IN Buffer Flush */

/* PIPECTR Register bit definitions */
#define R_USBFS_PIPECTR_PID_SHIFT                 (0)  /* Response PID */
#define R_USBFS_PIPECTR_PID_MASK                  0x3
#  define R_USBFS_PIPECTR_PID_00                          (0 << R_USBFS_PIPECTR_PID_SHIFT)  /* NAK response */
#  define R_USBFS_PIPECTR_PID_01                          (1 << R_USBFS_PIPECTR_PID_SHIFT)  /* BUF response (depends buffer state) */
#  define R_USBFS_PIPECTR_PID_10                          (2 << R_USBFS_PIPECTR_PID_SHIFT)  /* STALL response */
#  define R_USBFS_PIPECTR_PID_11                          (3 << R_USBFS_PIPECTR_PID_SHIFT)  /* STALL response */

#define R_USBFS_PIPECTR_PBUSY                     (1 << 5)  /* Pipe Busy */

#define R_USBFS_PIPECTR_SQMON                     (1 << 6)  /* Sequence Toggle Bit Confirmation */

#define R_USBFS_PIPECTR_SQSET                     (1 << 7)  /* Sequence Toggle Bit Set */

#define R_USBFS_PIPECTR_SQCLR                     (1 << 8)  /* Sequence Toggle Bit Clear */

#define R_USBFS_PIPECTR_ACLRM                     (1 << 9)  /* Auto Buffer Clear Mode */

#define R_USBFS_PIPECTR_ATREPM                    (1 << 10)  /* Auto Response Mode */

#define R_USBFS_PIPECTR_INBUFM                    (1 << 14)  /* Transmit Buffer Monitor */

#define R_USBFS_PIPECTR_BSTS                      (1 << 15)  /* Buffer Status */

/* PIPECTR Register bit definitions */
#define R_USBFS_PIPECTR_PID_SHIFT                 (0)  /* Response PID */
#define R_USBFS_PIPECTR_PID_MASK                  0x3
#  define R_USBFS_PIPECTR_PID_00                          (0 << R_USBFS_PIPECTR_PID_SHIFT)  /* NAK response */
#  define R_USBFS_PIPECTR_PID_01                          (1 << R_USBFS_PIPECTR_PID_SHIFT)  /* BUF response (depends buffer state) */
#  define R_USBFS_PIPECTR_PID_10                          (2 << R_USBFS_PIPECTR_PID_SHIFT)  /* STALL response */
#  define R_USBFS_PIPECTR_PID_11                          (3 << R_USBFS_PIPECTR_PID_SHIFT)  /* STALL response */

#define R_USBFS_PIPECTR_PBUSY                     (1 << 5)  /* Pipe Busy */

#define R_USBFS_PIPECTR_SQMON                     (1 << 6)  /* Sequence Toggle Bit Confirmation */

#define R_USBFS_PIPECTR_SQSET                     (1 << 7)  /* Sequence Toggle Bit Set */

#define R_USBFS_PIPECTR_SQCLR                     (1 << 8)  /* Sequence Toggle Bit Clear */

#define R_USBFS_PIPECTR_ACLRM                     (1 << 9)  /* Auto Buffer Clear Mode */

#define R_USBFS_PIPECTR_BSTS                      (1 << 15)  /* Buffer Status */

/* PIPETRE Register bit definitions */
#define R_USBFS_PIPETRE_TRCLR                     (1 << 8)  /* Transaction Counter Clear */

#define R_USBFS_PIPETRE_TRENB                     (1 << 9)  /* Transaction Counter Enable */

/* PIPETRN Register bit definitions */
#define R_USBFS_PIPETRN_TRNCNT_SHIFT              (0)  /* Transaction Counter */
#define R_USBFS_PIPETRN_TRNCNT_MASK               0xffff

/* DEVADD Register bit definitions */
#define R_USBFS_DEVADD_USBSPD_SHIFT               (6)  /* Transfer Speed of Communication Target Device */
#define R_USBFS_DEVADD_USBSPD_MASK                0xc0
#  define R_USBFS_DEVADD_USBSPD_00                        (0 << R_USBFS_DEVADD_USBSPD_SHIFT)  /* Do not use DEVADDn */
#  define R_USBFS_DEVADD_USBSPD_01                        (1 << R_USBFS_DEVADD_USBSPD_SHIFT)  /* Low-speed */
#  define R_USBFS_DEVADD_USBSPD_10                        (2 << R_USBFS_DEVADD_USBSPD_SHIFT)  /* Full-speed */
#  define R_USBFS_DEVADD_USBSPD_11                        (3 << R_USBFS_DEVADD_USBSPD_SHIFT)  /* Setting prohibited */

/* DPUSR0R Register bit definitions */
#define R_USBFS_DPUSR0R_SRPC0                     (1 << 0)  /* USB Single-ended Receiver Control */

#define R_USBFS_DPUSR0R_RPUE0                     (1 << 1)  /* DP Pull-Up Resistor Control */

#define R_USBFS_DPUSR0R_DRPD0                     (1 << 3)  /* D+/D- Pull-Down Resistor Control */

#define R_USBFS_DPUSR0R_FIXPHY0                   (1 << 4)  /* USB Transceiver Output Fix */

#define R_USBFS_DPUSR0R_DP0                       (1 << 16)  /* USB D+ Input */

#define R_USBFS_DPUSR0R_DM0                       (1 << 17)  /* USB D- Input */

#define R_USBFS_DPUSR0R_DOVCA0                    (1 << 20)  /* USB OVRCURA-DS Input */

#define R_USBFS_DPUSR0R_DOVCB0                    (1 << 21)  /* USB OVRCURB-DS Input */

#define R_USBFS_DPUSR0R_DVBSTS0                   (1 << 23)  /* USB VBUS Input */

/* DPUSR1R Register bit definitions */
#define R_USBFS_DPUSR1R_DPINTE0                   (1 << 0)  /* USB DP Interrupt Enable/Clear */

#define R_USBFS_DPUSR1R_DMINTE0                   (1 << 1)  /* USB DM Interrupt Enable/Clear */

#define R_USBFS_DPUSR1R_DOVRCRAE0                 (1 << 4)  /* USB OVRCURA-DS Interrupt Enable/Clear */

#define R_USBFS_DPUSR1R_DOVRCRBE0                 (1 << 5)  /* USB OVRCURB-DS Interrupt Enable/Clear */

#define R_USBFS_DPUSR1R_DVBSE0                    (1 << 7)  /* USB VBUS Interrupt Enable/Clear */

#define R_USBFS_DPUSR1R_DPINT0                    (1 << 16)  /* USB DP Interrupt Source Recovery */

#define R_USBFS_DPUSR1R_DMINT0                    (1 << 17)  /* USB DM Interrupt Source Recovery */

#define R_USBFS_DPUSR1R_DOVRCRA0                  (1 << 20)  /* USB OVRCURA-DS Interrupt Source Recovery */

#define R_USBFS_DPUSR1R_DOVRCRB0                  (1 << 21)  /* USB OVRCURB-DS Interrupt Source Recovery */

#define R_USBFS_DPUSR1R_DVBINT0                   (1 << 23)  /* USB VBUS Interrupt Source Recovery */


/* Maximum number of channels */

#define USBFS_MAX_CHANNELS    6

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_USBFS_H */
