/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_usbhs.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_USBHS_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_USBHS_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* USBHS Base Address */
#ifndef R_USBHS_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_USBHS_BASE           0x40351000
#else
#define R_USBHS_BASE           0x50351000
#endif
#endif

/* USBHS Register Offsets */

#define R_USBHS_SYSCFG_OFFSET                     0x00000000  /* System Configuration Control Register */
#define R_USBHS_BUSWAIT_OFFSET                    0x00000002  /* CPU Bus Wait Register */
#define R_USBHS_SYSSTS0_OFFSET                    0x00000004  /* System Configuration Status Register */
#define R_USBHS_PLLSTA_OFFSET                     0x00000006  /* PLL Status Register */
#define R_USBHS_DVSTCTR0_OFFSET                   0x00000008  /* Device State Control Register 0 */
#define R_USBHS_TESTMODE_OFFSET                   0x0000000c  /* USB Test Mode Register */
#define R_USBHS_CFIFO_OFFSET                      0x00000014  /* FIFO Port Register */
#define R_USBHS_CFIFOL_OFFSET                     0x00000014  /* FIFO Port Register */
#define R_USBHS_CFIFOLL_OFFSET                    0x00000014  /* FIFO Port Register */
#define R_USBHS_CFIFOH_OFFSET                     0x00000016  /* FIFO Port Register */
#define R_USBHS_CFIFOHH_OFFSET                    0x00000017  /* FIFO Port Register */
/* D%sFIFO Registers (0-1) */
#define R_USBHS_DFIFO_OFFSET(m)                   (0x00000018 + ((m) * 0x00000004))  /* FIFO Port Register */
/* D%sFIFOL Registers (0-1) */
#define R_USBHS_DFIFOL_OFFSET(m)                  (0x00000018 + ((m) * 0x00000004))  /* FIFO Port Register */
/* D%sFIFOLL Registers (0-1) */
#define R_USBHS_DFIFOLL_OFFSET(m)                 (0x00000018 + ((m) * 0x00000004))  /* FIFO Port Register */
/* D%sFIFOH Registers (0-1) */
#define R_USBHS_DFIFOH_OFFSET(m)                  (0x0000001a + ((m) * 0x00000004))  /* FIFO Port Register */
/* D%sFIFOHH Registers (0-1) */
#define R_USBHS_DFIFOHH_OFFSET(m)                 (0x0000001b + ((m) * 0x00000004))  /* FIFO Port Register */
#define R_USBHS_CFIFOSEL_OFFSET                   0x00000020  /* CFIFO Port Selection Register */
#define R_USBHS_CFIFOCTR_OFFSET                   0x00000022  /* FIFO Port Control Register */
/* D%sFIFOSEL Registers (0-1) */
#define R_USBHS_DFIFOSEL_OFFSET(m)                (0x00000028 + ((m) * 0x00000004))  /* D%sFIFO Port Selection Register */
/* D%sFIFOCTR Registers (0-1) */
#define R_USBHS_DFIFOCTR_OFFSET(m)                (0x0000002a + ((m) * 0x00000004))  /* FIFO Port Control Register */
#define R_USBHS_INTENB0_OFFSET                    0x00000030  /* Interrupt Enable Register 0 */
#define R_USBHS_INTENB1_OFFSET                    0x00000032  /* Interrupt Enable Register 1 */
#define R_USBHS_BRDYENB_OFFSET                    0x00000036  /* BRDY Interrupt Enable Register */
#define R_USBHS_NRDYENB_OFFSET                    0x00000038  /* NRDY Interrupt Enable Register */
#define R_USBHS_BEMPENB_OFFSET                    0x0000003a  /* BEMP Interrupt Enable Register */
#define R_USBHS_SOFCFG_OFFSET                     0x0000003c  /* SOF Output Configuration Register */
#define R_USBHS_PHYSET_OFFSET                     0x0000003e  /* PHY Setting Register */
#define R_USBHS_INTSTS0_OFFSET                    0x00000040  /* Interrupt Status Register 0 */
#define R_USBHS_INTSTS1_OFFSET                    0x00000042  /* Interrupt Status Register 1 */
#define R_USBHS_BRDYSTS_OFFSET                    0x00000046  /* BRDY Interrupt Status Register */
#define R_USBHS_NRDYSTS_OFFSET                    0x00000048  /* NRDY Interrupt Status Register */
#define R_USBHS_BEMPSTS_OFFSET                    0x0000004a  /* BEMP Interrupt Status Register */
#define R_USBHS_FRMNUM_OFFSET                     0x0000004c  /* Frame Number Register */
#define R_USBHS_UFRMNUM_OFFSET                    0x0000004e  /* µFrame Number Register */
#define R_USBHS_USBADDR_OFFSET                    0x00000050  /* USB Address Register */
#define R_USBHS_USBREQ_OFFSET                     0x00000054  /* USB Request Type Register */
#define R_USBHS_USBVAL_OFFSET                     0x00000056  /* USB Request Value Register */
#define R_USBHS_USBINDX_OFFSET                    0x00000058  /* USB Request Index Register */
#define R_USBHS_USBLENG_OFFSET                    0x0000005a  /* USB Request Length Register */
#define R_USBHS_DCPCFG_OFFSET                     0x0000005c  /* DCP Configuration Register */
#define R_USBHS_DCPMAXP_OFFSET                    0x0000005e  /* DCP Maximum Packet Size Register */
#define R_USBHS_DCPCTR_OFFSET                     0x00000060  /* DCP Control Register */
#define R_USBHS_PIPESEL_OFFSET                    0x00000064  /* Pipe Window Select Register */
#define R_USBHS_PIPECFG_OFFSET                    0x00000068  /* Pipe Configuration Register */
#define R_USBHS_PIPEBUF_OFFSET                    0x0000006a  /* Pipe Buffer Register */
#define R_USBHS_PIPEMAXP_OFFSET                   0x0000006c  /* Pipe Maximum Packet Size Register */
#define R_USBHS_PIPEPERI_OFFSET                   0x0000006e  /* Pipe Cycle Control Register */
/* PIPE%sCTR Registers (1-9) */
#define R_USBHS_PIPECTR_OFFSET(m)                 (0x00000070 + ((m) * 0x00000002))  /* Pipe %s Control Register */
/* PIPE%sTRE Registers (1-5) */
#define R_USBHS_PIPETRE_OFFSET(m)                 (0x00000090 + ((m) * 0x00000004))  /* Pipe %s Transaction Counter Enable Register */
/* PIPE%sTRN Registers (1-5) */
#define R_USBHS_PIPETRN_OFFSET(m)                 (0x00000092 + ((m) * 0x00000004))  /* Pipe %s Transaction Counter Register */
/* DEVADD%s Registers (0-9) */
#define R_USBHS_DEVADD_OFFSET(m)                  (0x000000d0 + ((m) * 0x00000002))  /* Device Address %s Configuration Register  */
#define R_USBHS_DEVADDA_OFFSET                    0x000000e4  /* Device Address A Configuration Register  */
#define R_USBHS_LPCTRL_OFFSET                     0x00000100  /* Low Power Control Register */
#define R_USBHS_LPSTS_OFFSET                      0x00000102  /* Low Power Status Register */
#define R_USBHS_BCCTRL_OFFSET                     0x00000140  /* Battery Charging Control Register */
#define R_USBHS_PL1CTRL1_OFFSET                   0x00000144  /* Function L1 Control Register 1 */
#define R_USBHS_PL1CTRL2_OFFSET                   0x00000146  /* Function L1 Control Register 2 */
#define R_USBHS_HL1CTRL1_OFFSET                   0x00000148  /* Host L1 Control Register 1 */
#define R_USBHS_HL1CTRL2_OFFSET                   0x0000014a  /* Host L1 Control Register 2 */
#define R_USBHS_DPUSR0R_OFFSET                    0x00000160  /* Deep Software Standby USB Transceiver Control/Pin Monitor Register */
#define R_USBHS_DPUSR1R_OFFSET                    0x00000164  /* Deep Software Standby USB Suspend/Resume Interrupt Register */
#define R_USBHS_DPUSR2R_OFFSET                    0x00000168  /* Deep Software Standby USB Suspend/Resume Interrupt Register */
#define R_USBHS_DPUSRCR_OFFSET                    0x0000016a  /* Deep Software Standby USB Suspend/Resume Command Register */

/* USBHS Register Addresses */

#define R_USBHS_SYSCFG                            (R_USBHS_BASE + R_USBHS_SYSCFG_OFFSET)
#define R_USBHS_BUSWAIT                           (R_USBHS_BASE + R_USBHS_BUSWAIT_OFFSET)
#define R_USBHS_SYSSTS0                           (R_USBHS_BASE + R_USBHS_SYSSTS0_OFFSET)
#define R_USBHS_PLLSTA                            (R_USBHS_BASE + R_USBHS_PLLSTA_OFFSET)
#define R_USBHS_DVSTCTR0                          (R_USBHS_BASE + R_USBHS_DVSTCTR0_OFFSET)
#define R_USBHS_TESTMODE                          (R_USBHS_BASE + R_USBHS_TESTMODE_OFFSET)
#define R_USBHS_CFIFO                             (R_USBHS_BASE + R_USBHS_CFIFO_OFFSET)
#define R_USBHS_CFIFOL                            (R_USBHS_BASE + R_USBHS_CFIFOL_OFFSET)
#define R_USBHS_CFIFOLL                           (R_USBHS_BASE + R_USBHS_CFIFOLL_OFFSET)
#define R_USBHS_CFIFOH                            (R_USBHS_BASE + R_USBHS_CFIFOH_OFFSET)
#define R_USBHS_CFIFOHH                           (R_USBHS_BASE + R_USBHS_CFIFOHH_OFFSET)
#define R_USBHS_DFIFO(m)                          (R_USBHS_BASE + R_USBHS_DFIFO_OFFSET(m))
#define R_USBHS_DFIFOL(m)                         (R_USBHS_BASE + R_USBHS_DFIFOL_OFFSET(m))
#define R_USBHS_DFIFOLL(m)                        (R_USBHS_BASE + R_USBHS_DFIFOLL_OFFSET(m))
#define R_USBHS_DFIFOH(m)                         (R_USBHS_BASE + R_USBHS_DFIFOH_OFFSET(m))
#define R_USBHS_DFIFOHH(m)                        (R_USBHS_BASE + R_USBHS_DFIFOHH_OFFSET(m))
#define R_USBHS_CFIFOSEL                          (R_USBHS_BASE + R_USBHS_CFIFOSEL_OFFSET)
#define R_USBHS_CFIFOCTR                          (R_USBHS_BASE + R_USBHS_CFIFOCTR_OFFSET)
#define R_USBHS_DFIFOSEL(m)                       (R_USBHS_BASE + R_USBHS_DFIFOSEL_OFFSET(m))
#define R_USBHS_DFIFOCTR(m)                       (R_USBHS_BASE + R_USBHS_DFIFOCTR_OFFSET(m))
#define R_USBHS_INTENB0                           (R_USBHS_BASE + R_USBHS_INTENB0_OFFSET)
#define R_USBHS_INTENB1                           (R_USBHS_BASE + R_USBHS_INTENB1_OFFSET)
#define R_USBHS_BRDYENB                           (R_USBHS_BASE + R_USBHS_BRDYENB_OFFSET)
#define R_USBHS_NRDYENB                           (R_USBHS_BASE + R_USBHS_NRDYENB_OFFSET)
#define R_USBHS_BEMPENB                           (R_USBHS_BASE + R_USBHS_BEMPENB_OFFSET)
#define R_USBHS_SOFCFG                            (R_USBHS_BASE + R_USBHS_SOFCFG_OFFSET)
#define R_USBHS_PHYSET                            (R_USBHS_BASE + R_USBHS_PHYSET_OFFSET)
#define R_USBHS_INTSTS0                           (R_USBHS_BASE + R_USBHS_INTSTS0_OFFSET)
#define R_USBHS_INTSTS1                           (R_USBHS_BASE + R_USBHS_INTSTS1_OFFSET)
#define R_USBHS_BRDYSTS                           (R_USBHS_BASE + R_USBHS_BRDYSTS_OFFSET)
#define R_USBHS_NRDYSTS                           (R_USBHS_BASE + R_USBHS_NRDYSTS_OFFSET)
#define R_USBHS_BEMPSTS                           (R_USBHS_BASE + R_USBHS_BEMPSTS_OFFSET)
#define R_USBHS_FRMNUM                            (R_USBHS_BASE + R_USBHS_FRMNUM_OFFSET)
#define R_USBHS_UFRMNUM                           (R_USBHS_BASE + R_USBHS_UFRMNUM_OFFSET)
#define R_USBHS_USBADDR                           (R_USBHS_BASE + R_USBHS_USBADDR_OFFSET)
#define R_USBHS_USBREQ                            (R_USBHS_BASE + R_USBHS_USBREQ_OFFSET)
#define R_USBHS_USBVAL                            (R_USBHS_BASE + R_USBHS_USBVAL_OFFSET)
#define R_USBHS_USBINDX                           (R_USBHS_BASE + R_USBHS_USBINDX_OFFSET)
#define R_USBHS_USBLENG                           (R_USBHS_BASE + R_USBHS_USBLENG_OFFSET)
#define R_USBHS_DCPCFG                            (R_USBHS_BASE + R_USBHS_DCPCFG_OFFSET)
#define R_USBHS_DCPMAXP                           (R_USBHS_BASE + R_USBHS_DCPMAXP_OFFSET)
#define R_USBHS_DCPCTR                            (R_USBHS_BASE + R_USBHS_DCPCTR_OFFSET)
#define R_USBHS_PIPESEL                           (R_USBHS_BASE + R_USBHS_PIPESEL_OFFSET)
#define R_USBHS_PIPECFG                           (R_USBHS_BASE + R_USBHS_PIPECFG_OFFSET)
#define R_USBHS_PIPEBUF                           (R_USBHS_BASE + R_USBHS_PIPEBUF_OFFSET)
#define R_USBHS_PIPEMAXP                          (R_USBHS_BASE + R_USBHS_PIPEMAXP_OFFSET)
#define R_USBHS_PIPEPERI                          (R_USBHS_BASE + R_USBHS_PIPEPERI_OFFSET)
#define R_USBHS_PIPECTR(m)                        (R_USBHS_BASE + R_USBHS_PIPECTR_OFFSET(m))
#define R_USBHS_PIPETRE(m)                        (R_USBHS_BASE + R_USBHS_PIPETRE_OFFSET(m))
#define R_USBHS_PIPETRN(m)                        (R_USBHS_BASE + R_USBHS_PIPETRN_OFFSET(m))
#define R_USBHS_DEVADD(m)                         (R_USBHS_BASE + R_USBHS_DEVADD_OFFSET(m))
#define R_USBHS_DEVADDA                           (R_USBHS_BASE + R_USBHS_DEVADDA_OFFSET)
#define R_USBHS_LPCTRL                            (R_USBHS_BASE + R_USBHS_LPCTRL_OFFSET)
#define R_USBHS_LPSTS                             (R_USBHS_BASE + R_USBHS_LPSTS_OFFSET)
#define R_USBHS_BCCTRL                            (R_USBHS_BASE + R_USBHS_BCCTRL_OFFSET)
#define R_USBHS_PL1CTRL1                          (R_USBHS_BASE + R_USBHS_PL1CTRL1_OFFSET)
#define R_USBHS_PL1CTRL2                          (R_USBHS_BASE + R_USBHS_PL1CTRL2_OFFSET)
#define R_USBHS_HL1CTRL1                          (R_USBHS_BASE + R_USBHS_HL1CTRL1_OFFSET)
#define R_USBHS_HL1CTRL2                          (R_USBHS_BASE + R_USBHS_HL1CTRL2_OFFSET)
#define R_USBHS_DPUSR0R                           (R_USBHS_BASE + R_USBHS_DPUSR0R_OFFSET)
#define R_USBHS_DPUSR1R                           (R_USBHS_BASE + R_USBHS_DPUSR1R_OFFSET)
#define R_USBHS_DPUSR2R                           (R_USBHS_BASE + R_USBHS_DPUSR2R_OFFSET)
#define R_USBHS_DPUSRCR                           (R_USBHS_BASE + R_USBHS_DPUSRCR_OFFSET)

/* Register bit definitions */
/* SYSCFG Register bit definitions */
#define R_USBHS_SYSCFG_USBE                       (1 << 0)  /* USBHS Operation Enable */

#define R_USBHS_SYSCFG_DPRPU                      (1 << 4)  /* D+ Line Resistor Control */

#define R_USBHS_SYSCFG_DRPD                       (1 << 5)  /* D+/D- Line Resistor Control */

#define R_USBHS_SYSCFG_DCFM                       (1 << 6)  /* Controller Operation Select */

#define R_USBHS_SYSCFG_HSE                        (1 << 7)  /* High-Speed Operation Enable */

#define R_USBHS_SYSCFG_CNEN                       (1 << 8)  /* Single-ended Receiver Enable */

/* BUSWAIT Register bit definitions */
#define R_USBHS_BUSWAIT_BWAIT_SHIFT               (0)  /* CPU Bus Access Wait Specification */
#define R_USBHS_BUSWAIT_BWAIT_MASK                0xf

/* SYSSTS0 Register bit definitions */
#define R_USBHS_SYSSTS0_LNST_SHIFT                (0)  /* USB Data Line Status Monitor Flag */
#define R_USBHS_SYSSTS0_LNST_MASK                 0x3

#define R_USBHS_SYSSTS0_IDMON                     (1 << 2)  /* USBHS_ID Pin Monitor Flag */

#define R_USBHS_SYSSTS0_SOFEA                     (1 << 5)  /* SOF Active Monitor Flag While Host Controller Operation Is Selected */

#define R_USBHS_SYSSTS0_HTACT                     (1 << 6)  /* Host Sequencer Status Monitor Flag */

#define R_USBHS_SYSSTS0_OVCMON_SHIFT              (14)  /* External USBHS_OVRCURA or USBHS_OVRCURA-DS, and USBHS_OVRCURB or USBHS_OVRCURBB-DS Input Pin Monitor Flag */
#define R_USBHS_SYSSTS0_OVCMON_MASK               0xc000

/* PLLSTA Register bit definitions */
#define R_USBHS_PLLSTA_PLLLOCK                    (1 << 0)  /* PLL Lock Flag */

/* DVSTCTR0 Register bit definitions */
#define R_USBHS_DVSTCTR0_RHST_SHIFT               (0)  /* USB Bus Reset Status Flag */
#define R_USBHS_DVSTCTR0_RHST_MASK                0x7
#  define R_USBHS_DVSTCTR0_RHST_000                       (0 << R_USBHS_DVSTCTR0_RHST_SHIFT)  /* Communication speed indeterminate (powered state or no connection) */
#  define R_USBHS_DVSTCTR0_RHST_001                       (1 << R_USBHS_DVSTCTR0_RHST_SHIFT)  /* Host controller mode Low-speed connection Device controller mode USB bus reset in progress or low-speed connection  */
#  define R_USBHS_DVSTCTR0_RHST_010                       (2 << R_USBHS_DVSTCTR0_RHST_SHIFT)  /* Host controller mode Full-speed connection Device controller mode USB bus reset in progress or full-speed connection  */
#  define R_USBHS_DVSTCTR0_RHST_011                       (3 << R_USBHS_DVSTCTR0_RHST_SHIFT)  /* Host controller mode High-speed connection Device controller mode USB bus reset in progress or high-speed connection  */

#define R_USBHS_DVSTCTR0_UACT                     (1 << 4)  /* USB Bus Operation Enable for the Host Controller Operation */

#define R_USBHS_DVSTCTR0_RESUME                   (1 << 5)  /* Resume Signal Output for the Host Controller Operation */

#define R_USBHS_DVSTCTR0_USBRST                   (1 << 6)  /* USB Bus Reset Output for the Host Controller Operation */

#define R_USBHS_DVSTCTR0_RWUPE                    (1 << 7)  /* Remote Wakeup Detection Enable for the Host Controller Operation */

#define R_USBHS_DVSTCTR0_WKUP                     (1 << 8)  /* Remote Wakeup Output for the Device Controller Operation */

#define R_USBHS_DVSTCTR0_VBUSEN                   (1 << 9)  /* USBHS_VBUSEN Output Pin Control */

#define R_USBHS_DVSTCTR0_EXICEN                   (1 << 10)  /* USBHS_EXICEN Output Pin Control */

#define R_USBHS_DVSTCTR0_HNPBTOA                  (1 << 11)  /* Host Negotiation Protocol (HNP) Control */

/* TESTMODE Register bit definitions */
#define R_USBHS_TESTMODE_UTST_SHIFT               (0)  /* Test Mode */
#define R_USBHS_TESTMODE_UTST_MASK                0xf

/* CFIFO Register bit definitions */
#define R_USBHS_CFIFO_FIFOPORT_SHIFT              (0)  /* Read receive data from the FIFO buffer or write transmit data to the FIFO buffer by accessing these bits. */
#define R_USBHS_CFIFO_FIFOPORT_MASK               0xffffffff

/* CFIFOL Register bit definitions */
#define R_USBHS_CFIFOL_FIFOPORT_SHIFT             (0)  /* Read receive data from the FIFO buffer or write transmit data to the FIFO buffer by accessing these bits. */
#define R_USBHS_CFIFOL_FIFOPORT_MASK              0xffff

/* CFIFOLL Register bit definitions */
#define R_USBHS_CFIFOLL_FIFOPORT_SHIFT            (0)  /* Read receive data from the FIFO buffer or write transmit data to the FIFO buffer by accessing these bits. */
#define R_USBHS_CFIFOLL_FIFOPORT_MASK             0xff

/* CFIFOH Register bit definitions */
#define R_USBHS_CFIFOH_FIFOPORT_SHIFT             (0)  /* Read receive data from the FIFO buffer or write transmit data to the FIFO buffer by accessing these bits. */
#define R_USBHS_CFIFOH_FIFOPORT_MASK              0xffff

/* CFIFOHH Register bit definitions */
#define R_USBHS_CFIFOHH_FIFOPORT_SHIFT            (0)  /* Read receive data from the FIFO buffer or write transmit data to the FIFO buffer by accessing these bits. */
#define R_USBHS_CFIFOHH_FIFOPORT_MASK             0xff

/* DFIFO Register bit definitions */
#define R_USBHS_DFIFO_FIFOPORT_SHIFT              (0)  /* Read receive data from the FIFO buffer or write transmit data to the FIFO buffer by accessing these bits. */
#define R_USBHS_DFIFO_FIFOPORT_MASK               0xffffffff

/* DFIFOL Register bit definitions */
#define R_USBHS_DFIFOL_FIFOPORT_SHIFT             (0)  /* Read receive data from the FIFO buffer or write transmit data to the FIFO buffer by accessing these bits. */
#define R_USBHS_DFIFOL_FIFOPORT_MASK              0xffff

/* DFIFOLL Register bit definitions */
#define R_USBHS_DFIFOLL_FIFOPORT_SHIFT            (0)  /* Read receive data from the FIFO buffer or write transmit data to the FIFO buffer by accessing these bits. */
#define R_USBHS_DFIFOLL_FIFOPORT_MASK             0xff

/* DFIFOH Register bit definitions */
#define R_USBHS_DFIFOH_FIFOPORT_SHIFT             (0)  /* Read receive data from the FIFO buffer or write transmit data to the FIFO buffer by accessing these bits. */
#define R_USBHS_DFIFOH_FIFOPORT_MASK              0xffff

/* DFIFOHH Register bit definitions */
#define R_USBHS_DFIFOHH_FIFOPORT_SHIFT            (0)  /* Read receive data from the FIFO buffer or write transmit data to the FIFO buffer by accessing these bits. */
#define R_USBHS_DFIFOHH_FIFOPORT_MASK             0xff

/* CFIFOSEL Register bit definitions */
#define R_USBHS_CFIFOSEL_CURPIPE_SHIFT            (0)  /* FIFO Port Access Pipe Specification */
#define R_USBHS_CFIFOSEL_CURPIPE_MASK             0xf
#  define R_USBHS_CFIFOSEL_CURPIPE_0X0                    (0 << R_USBHS_CFIFOSEL_CURPIPE_SHIFT)  /* DCP (default control pipe) */
#  define R_USBHS_CFIFOSEL_CURPIPE_0X1                    (1 << R_USBHS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 1 */
#  define R_USBHS_CFIFOSEL_CURPIPE_0X2                    (2 << R_USBHS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 2 */
#  define R_USBHS_CFIFOSEL_CURPIPE_0X3                    (3 << R_USBHS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 3 */
#  define R_USBHS_CFIFOSEL_CURPIPE_0X4                    (4 << R_USBHS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 4 */
#  define R_USBHS_CFIFOSEL_CURPIPE_0X5                    (5 << R_USBHS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 5 */
#  define R_USBHS_CFIFOSEL_CURPIPE_0X6                    (6 << R_USBHS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 6 */
#  define R_USBHS_CFIFOSEL_CURPIPE_0X7                    (7 << R_USBHS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 7 */
#  define R_USBHS_CFIFOSEL_CURPIPE_0X8                    (8 << R_USBHS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 8 */
#  define R_USBHS_CFIFOSEL_CURPIPE_0X9                    (9 << R_USBHS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 9 */

#define R_USBHS_CFIFOSEL_ISEL                     (1 << 5)  /* FIFO Port Access Direction when DCP Is Selected */

#define R_USBHS_CFIFOSEL_BIGEND                   (1 << 8)  /* FIFO Port Endian Control */

#define R_USBHS_CFIFOSEL_MBW_SHIFT                (10)  /* CFIFO Port Access Bit Width */
#define R_USBHS_CFIFOSEL_MBW_MASK                 0xc00
#  define R_USBHS_CFIFOSEL_MBW_00                         (0 << R_USBHS_CFIFOSEL_MBW_SHIFT)  /* 8-bit width */
#  define R_USBHS_CFIFOSEL_MBW_01                         (1 << R_USBHS_CFIFOSEL_MBW_SHIFT)  /* 16-bit width */
#  define R_USBHS_CFIFOSEL_MBW_10                         (2 << R_USBHS_CFIFOSEL_MBW_SHIFT)  /* 32-bit width */
#  define R_USBHS_CFIFOSEL_MBW_11                         (3 << R_USBHS_CFIFOSEL_MBW_SHIFT)  /* Setting prohibited */

#define R_USBHS_CFIFOSEL_REW                      (1 << 14)  /* Buffer Pointer Rewind */

#define R_USBHS_CFIFOSEL_RCNT                     (1 << 15)  /* Read Count Mode */

/* CFIFOCTR Register bit definitions */
#define R_USBHS_CFIFOCTR_DTLN_SHIFT               (0)  /* Receive Data Length Flag */
#define R_USBHS_CFIFOCTR_DTLN_MASK                0xfff

#define R_USBHS_CFIFOCTR_FRDY                     (1 << 13)  /* FIFO Port Ready Flag */

#define R_USBHS_CFIFOCTR_BCLR                     (1 << 14)  /* CPU Buffer Clear */

#define R_USBHS_CFIFOCTR_BVAL                     (1 << 15)  /* FIFO Buffer Valid Flag */

/* DFIFOSEL Register bit definitions */
#define R_USBHS_DFIFOSEL_CURPIPE_SHIFT            (0)  /* FIFO Port Access Pipe Specification */
#define R_USBHS_DFIFOSEL_CURPIPE_MASK             0xf
#  define R_USBHS_DFIFOSEL_CURPIPE_0X0                    (0 << R_USBHS_DFIFOSEL_CURPIPE_SHIFT)  /* No pipe specification */
#  define R_USBHS_DFIFOSEL_CURPIPE_0X1                    (1 << R_USBHS_DFIFOSEL_CURPIPE_SHIFT)  /* Pipe 1 */
#  define R_USBHS_DFIFOSEL_CURPIPE_0X2                    (2 << R_USBHS_DFIFOSEL_CURPIPE_SHIFT)  /* Pipe 2 */
#  define R_USBHS_DFIFOSEL_CURPIPE_0X3                    (3 << R_USBHS_DFIFOSEL_CURPIPE_SHIFT)  /* Pipe 3 */
#  define R_USBHS_DFIFOSEL_CURPIPE_0X4                    (4 << R_USBHS_DFIFOSEL_CURPIPE_SHIFT)  /* Pipe 4 */
#  define R_USBHS_DFIFOSEL_CURPIPE_0X5                    (5 << R_USBHS_DFIFOSEL_CURPIPE_SHIFT)  /* Pipe 5 */
#  define R_USBHS_DFIFOSEL_CURPIPE_0X6                    (6 << R_USBHS_DFIFOSEL_CURPIPE_SHIFT)  /* Pipe 6 */
#  define R_USBHS_DFIFOSEL_CURPIPE_0X7                    (7 << R_USBHS_DFIFOSEL_CURPIPE_SHIFT)  /* Pipe 7 */
#  define R_USBHS_DFIFOSEL_CURPIPE_0X8                    (8 << R_USBHS_DFIFOSEL_CURPIPE_SHIFT)  /* Pipe 8 */
#  define R_USBHS_DFIFOSEL_CURPIPE_0X9                    (9 << R_USBHS_DFIFOSEL_CURPIPE_SHIFT)  /* Pipe 9 */

#define R_USBHS_DFIFOSEL_BIGEND                   (1 << 8)  /* FIFO Port Endian Control */

#define R_USBHS_DFIFOSEL_MBW_SHIFT                (10)  /* FIFO Port Access Bit Width */
#define R_USBHS_DFIFOSEL_MBW_MASK                 0xc00
#  define R_USBHS_DFIFOSEL_MBW_00                         (0 << R_USBHS_DFIFOSEL_MBW_SHIFT)  /* 8-bit width */
#  define R_USBHS_DFIFOSEL_MBW_01                         (1 << R_USBHS_DFIFOSEL_MBW_SHIFT)  /* 16-bit width */
#  define R_USBHS_DFIFOSEL_MBW_10                         (2 << R_USBHS_DFIFOSEL_MBW_SHIFT)  /* 32-bit width */
#  define R_USBHS_DFIFOSEL_MBW_11                         (3 << R_USBHS_DFIFOSEL_MBW_SHIFT)  /* Setting prohibited */

#define R_USBHS_DFIFOSEL_DREQE                    (1 << 12)  /* DMAC/DTC Transfer Request Enable */

#define R_USBHS_DFIFOSEL_DCLRM                    (1 << 13)  /* Auto FIFO Buffer Clear Mode after Specified Pipe is Read */

#define R_USBHS_DFIFOSEL_REW                      (1 << 14)  /* Buffer Pointer Rewind */

#define R_USBHS_DFIFOSEL_RCNT                     (1 << 15)  /* Read Count Mode */

/* DFIFOCTR Register bit definitions */
#define R_USBHS_DFIFOCTR_DTLN_SHIFT               (0)  /* Receive Data Length Flag */
#define R_USBHS_DFIFOCTR_DTLN_MASK                0xfff

#define R_USBHS_DFIFOCTR_FRDY                     (1 << 13)  /* FIFO Port Ready Flag */

#define R_USBHS_DFIFOCTR_BCLR                     (1 << 14)  /* CPU Buffer Clear */

#define R_USBHS_DFIFOCTR_BVAL                     (1 << 15)  /* FIFO Buffer Valid Flag */

/* INTENB0 Register bit definitions */
#define R_USBHS_INTENB0_BRDYE                     (1 << 8)  /* Buffer Ready Interrupt Request Enable */

#define R_USBHS_INTENB0_NRDYE                     (1 << 9)  /* Buffer Not Ready Response Interrupt Request Enable */

#define R_USBHS_INTENB0_BEMPE                     (1 << 10)  /* Buffer Empty Interrupt Request Enable */

#define R_USBHS_INTENB0_CTRE                      (1 << 11)  /* Control Transfer Stage Transition Interrupt Request Enable */

#define R_USBHS_INTENB0_DVSE                      (1 << 12)  /* Device State Transition Interrupt Request Enable */

#define R_USBHS_INTENB0_SOFE                      (1 << 13)  /* Frame Number Update Interrupt Request Enable */

#define R_USBHS_INTENB0_RSME                      (1 << 14)  /* Resume Interrupt Request Enable */

#define R_USBHS_INTENB0_VBSE                      (1 << 15)  /* VBUS Interrupt Request Enable */

/* INTENB1 Register bit definitions */
#define R_USBHS_INTENB1_PDDETINTE                 (1 << 0)  /* PDDETINT Detection Interrupt Request Enable */

#define R_USBHS_INTENB1_SACKE                     (1 << 4)  /* Setup Transaction Normal Response Interrupt Request Enable */

#define R_USBHS_INTENB1_SIGNE                     (1 << 5)  /* Setup Transaction Error Interrupt Request Enable */

#define R_USBHS_INTENB1_EOFERRE                   (1 << 6)  /* EOF Error Detection Interrupt Request Enable */

#define R_USBHS_INTENB1_LPMENDE                   (1 << 8)  /* LPM Transaction End Interrupt Request Enable */

#define R_USBHS_INTENB1_L1RSMENDE                 (1 << 9)  /* L1 Resume End Interrupt Enable */

#define R_USBHS_INTENB1_ATTCHE                    (1 << 11)  /* Connection Detection Interrupt Request Enable */

#define R_USBHS_INTENB1_DTCHE                     (1 << 12)  /* Disconnection Detection Interrupt Request Enable */

#define R_USBHS_INTENB1_BCHGE                     (1 << 14)  /* USB Bus Change Interrupt Request Enable */

#define R_USBHS_INTENB1_OVRCRE                    (1 << 15)  /* OVRCRE Interrupt Request Enable */

/* BRDYENB Register bit definitions */
#define R_USBHS_BRDYENB_PIPEBRDYE_SHIFT           (0)  /* BRDY Interrupt Request Enable for Pipes [9:0] */
#define R_USBHS_BRDYENB_PIPEBRDYE_MASK            0x3ff
#  define R_USBHS_BRDYENB_PIPEBRDYE_0                     (0 << R_USBHS_BRDYENB_PIPEBRDYE_SHIFT)  /* Disable interrupt request */
#  define R_USBHS_BRDYENB_PIPEBRDYE_1                     (1 << R_USBHS_BRDYENB_PIPEBRDYE_SHIFT)  /* Enable interrupt request */

/* NRDYENB Register bit definitions */
#define R_USBHS_NRDYENB_PIPENRDYE_SHIFT           (0)  /* NRDY Interrupt Enable for Pipes [9:0] */
#define R_USBHS_NRDYENB_PIPENRDYE_MASK            0x3ff
#  define R_USBHS_NRDYENB_PIPENRDYE_0                     (0 << R_USBHS_NRDYENB_PIPENRDYE_SHIFT)  /* Disable interrupt request */
#  define R_USBHS_NRDYENB_PIPENRDYE_1                     (1 << R_USBHS_NRDYENB_PIPENRDYE_SHIFT)  /* Enable interrupt request */

/* BEMPENB Register bit definitions */
#define R_USBHS_BEMPENB_PIPEBEMPE_SHIFT           (0)  /* BEMP Interrupt Enable for Pipes [9:0] */
#define R_USBHS_BEMPENB_PIPEBEMPE_MASK            0x3ff
#  define R_USBHS_BEMPENB_PIPEBEMPE_0                     (0 << R_USBHS_BEMPENB_PIPEBEMPE_SHIFT)  /* Disable interrupt request */
#  define R_USBHS_BEMPENB_PIPEBEMPE_1                     (1 << R_USBHS_BEMPENB_PIPEBEMPE_SHIFT)  /* Enable interrupt request */

/* SOFCFG Register bit definitions */
#define R_USBHS_SOFCFG_EDGESTS                    (1 << 4)  /* Interrupt Edge Processing Status Flag */

#define R_USBHS_SOFCFG_INTL                       (1 << 5)  /* Interrupt Output Sense Select */

#define R_USBHS_SOFCFG_BRDYM                      (1 << 6)  /* PIPEBRDY Interrupt Status Clear Timing */

#define R_USBHS_SOFCFG_TRNENSEL                   (1 << 8)  /* Transaction-Enabled Time Select */

/* PHYSET Register bit definitions */
#define R_USBHS_PHYSET_DIRPD                      (1 << 0)  /* Power-Down Control */

#define R_USBHS_PHYSET_PLLRESET                   (1 << 1)  /* PLL Reset Control */

#define R_USBHS_PHYSET_CDPEN                      (1 << 3)  /* Charging Downstream Port Enable */

#define R_USBHS_PHYSET_CLKSEL_SHIFT               (4)  /* Input Clock Frequency Select */
#define R_USBHS_PHYSET_CLKSEL_MASK                0x30
#  define R_USBHS_PHYSET_CLKSEL_00                        (0 << R_USBHS_PHYSET_CLKSEL_SHIFT)  /* 12 MHz */
#  define R_USBHS_PHYSET_CLKSEL_01                        (1 << R_USBHS_PHYSET_CLKSEL_SHIFT)  /* 48 MHz */
#  define R_USBHS_PHYSET_CLKSEL_10                        (2 << R_USBHS_PHYSET_CLKSEL_SHIFT)  /* 20 MHz */
#  define R_USBHS_PHYSET_CLKSEL_11                        (3 << R_USBHS_PHYSET_CLKSEL_SHIFT)  /* 24 MHz */

#define R_USBHS_PHYSET_REPSEL_SHIFT               (8)  /* Terminating Resistance Adjustment Cycle */
#define R_USBHS_PHYSET_REPSEL_MASK                0x300
#  define R_USBHS_PHYSET_REPSEL_00                        (0 << R_USBHS_PHYSET_REPSEL_SHIFT)  /* No cycle is set */
#  define R_USBHS_PHYSET_REPSEL_01                        (1 << R_USBHS_PHYSET_REPSEL_SHIFT)  /* Adjust terminating resistance at 16-second intervals */
#  define R_USBHS_PHYSET_REPSEL_10                        (2 << R_USBHS_PHYSET_REPSEL_SHIFT)  /* Adjust terminating resistance at 64-second intervals */
#  define R_USBHS_PHYSET_REPSEL_11                        (3 << R_USBHS_PHYSET_REPSEL_SHIFT)  /* Adjust terminating resistance at 128-second intervals */

#define R_USBHS_PHYSET_REPSTART                   (1 << 11)  /* Forcibly Start Terminating Resistance Adjustment */

#define R_USBHS_PHYSET_HSEB                       (1 << 15)  /* CL-only mode */

/* INTSTS0 Register bit definitions */
#define R_USBHS_INTSTS0_CTSQ_SHIFT                (0)  /* Control Transfer Stage Flag */
#define R_USBHS_INTSTS0_CTSQ_MASK                 0x7
#  define R_USBHS_INTSTS0_CTSQ_000                        (0 << R_USBHS_INTSTS0_CTSQ_SHIFT)  /* Idle or setup stage */
#  define R_USBHS_INTSTS0_CTSQ_001                        (1 << R_USBHS_INTSTS0_CTSQ_SHIFT)  /* Control read data stage */
#  define R_USBHS_INTSTS0_CTSQ_010                        (2 << R_USBHS_INTSTS0_CTSQ_SHIFT)  /* Control read status stage */
#  define R_USBHS_INTSTS0_CTSQ_011                        (3 << R_USBHS_INTSTS0_CTSQ_SHIFT)  /* Control write data stage */
#  define R_USBHS_INTSTS0_CTSQ_100                        (4 << R_USBHS_INTSTS0_CTSQ_SHIFT)  /* Control write status stage */
#  define R_USBHS_INTSTS0_CTSQ_101                        (5 << R_USBHS_INTSTS0_CTSQ_SHIFT)  /* Control write (no data) status stage */
#  define R_USBHS_INTSTS0_CTSQ_110                        (6 << R_USBHS_INTSTS0_CTSQ_SHIFT)  /* Control transfer sequence error */

#define R_USBHS_INTSTS0_VALID                     (1 << 3)  /* USB Request Reception Flag */

#define R_USBHS_INTSTS0_DVSQ_SHIFT                (4)  /* Device State */
#define R_USBHS_INTSTS0_DVSQ_MASK                 0x70
#  define R_USBHS_INTSTS0_DVSQ_000                        (0 << R_USBHS_INTSTS0_DVSQ_SHIFT)  /* Powered state */
#  define R_USBHS_INTSTS0_DVSQ_001                        (1 << R_USBHS_INTSTS0_DVSQ_SHIFT)  /* Default state */
#  define R_USBHS_INTSTS0_DVSQ_010                        (2 << R_USBHS_INTSTS0_DVSQ_SHIFT)  /* Address state */
#  define R_USBHS_INTSTS0_DVSQ_011                        (3 << R_USBHS_INTSTS0_DVSQ_SHIFT)  /* Configured state */

#define R_USBHS_INTSTS0_VBSTS                     (1 << 7)  /* VBUS Input Status Flag */

#define R_USBHS_INTSTS0_BRDY                      (1 << 8)  /* BRDY Interrupt Status Flag */

#define R_USBHS_INTSTS0_NRDY                      (1 << 9)  /* NRDY Interrupt Status Flag */

#define R_USBHS_INTSTS0_BEMP                      (1 << 10)  /* BEMP Interrupt Status Flag */

#define R_USBHS_INTSTS0_CTRT                      (1 << 11)  /* Control Transfer Stage Transition Interrupt Status Flag */

#define R_USBHS_INTSTS0_DVST                      (1 << 12)  /* Device State Transition Interrupt Status Flag */

#define R_USBHS_INTSTS0_SOFR                      (1 << 13)  /* Frame Number Refresh Interrupt Status Flag */

#define R_USBHS_INTSTS0_RESM                      (1 << 14)  /* Resume Interrupt Status Flag */

#define R_USBHS_INTSTS0_VBINT                     (1 << 15)  /* VBUS Interrupt Status Flag */

/* INTSTS1 Register bit definitions */
#define R_USBHS_INTSTS1_PDDETINT                  (1 << 0)  /* PDDET Detection Interrupt Status Flag */

#define R_USBHS_INTSTS1_SACK                      (1 << 4)  /* Setup Transaction Normal Response Interrupt Status Flag */

#define R_USBHS_INTSTS1_SIGN                      (1 << 5)  /* Setup Transaction Error Interrupt Status Flag */

#define R_USBHS_INTSTS1_EOFERR                    (1 << 6)  /* EOF Error Detection Interrupt Status Flag */

#define R_USBHS_INTSTS1_LPMEND                    (1 << 8)  /* LPM Transaction End Interrupt Status Flag */

#define R_USBHS_INTSTS1_L1RSMEND                  (1 << 9)  /* L1 Resume End Interrupt Status Flag */

#define R_USBHS_INTSTS1_ATTCH                     (1 << 11)  /* USB Connection Detection Interrupt Status Flag */

#define R_USBHS_INTSTS1_DTCH                      (1 << 12)  /* USB Disconnection Detection Interrupt Status Flag */

#define R_USBHS_INTSTS1_BCHG                      (1 << 14)  /* USB Bus Change Interrupt Status Flag */

#define R_USBHS_INTSTS1_OVRCR                     (1 << 15)  /* OVRCR Interrupt Status Flag */

/* BRDYSTS Register bit definitions */
#define R_USBHS_BRDYSTS_PIPEBRDY_SHIFT            (0)  /* BRDY Interrupt Status Flag for Pipe[9:0] */
#define R_USBHS_BRDYSTS_PIPEBRDY_MASK             0x3ff
#  define R_USBHS_BRDYSTS_PIPEBRDY_0                      (0 << R_USBHS_BRDYSTS_PIPEBRDY_SHIFT)  /* No BRDY interrupt occurred */
#  define R_USBHS_BRDYSTS_PIPEBRDY_1                      (1 << R_USBHS_BRDYSTS_PIPEBRDY_SHIFT)  /* BRDY interrupt occurred */

/* NRDYSTS Register bit definitions */
#define R_USBHS_NRDYSTS_PIPENRDY_SHIFT            (0)  /* NRDY Interrupt Status Flag for Pipe[9:0] */
#define R_USBHS_NRDYSTS_PIPENRDY_MASK             0x3ff
#  define R_USBHS_NRDYSTS_PIPENRDY_0                      (0 << R_USBHS_NRDYSTS_PIPENRDY_SHIFT)  /* No NRDY interrupt occurred */
#  define R_USBHS_NRDYSTS_PIPENRDY_1                      (1 << R_USBHS_NRDYSTS_PIPENRDY_SHIFT)  /* NRDY interrupt occurred. */

/* BEMPSTS Register bit definitions */
#define R_USBHS_BEMPSTS_PIPEBEMP_SHIFT            (0)  /* BEMP Interrupt Status Flag for Pipe[9:0] */
#define R_USBHS_BEMPSTS_PIPEBEMP_MASK             0x3ff
#  define R_USBHS_BEMPSTS_PIPEBEMP_0                      (0 << R_USBHS_BEMPSTS_PIPEBEMP_SHIFT)  /* No BEMP interrupt occurred */
#  define R_USBHS_BEMPSTS_PIPEBEMP_1                      (1 << R_USBHS_BEMPSTS_PIPEBEMP_SHIFT)  /* BEMP interrupt occurred. */

/* FRMNUM Register bit definitions */
#define R_USBHS_FRMNUM_FRNM_SHIFT                 (0)  /* Frame Number Flag */
#define R_USBHS_FRMNUM_FRNM_MASK                  0x7ff

#define R_USBHS_FRMNUM_CRCE                       (1 << 14)  /* CRC Error Detection Status Flag */

#define R_USBHS_FRMNUM_OVRN                       (1 << 15)  /* Overrun/Underrun Detection Status Flag */

/* UFRMNUM Register bit definitions */
#define R_USBHS_UFRMNUM_UFRNM_SHIFT               (0)  /* Microframe number */
#define R_USBHS_UFRMNUM_UFRNM_MASK                0x7

#define R_USBHS_UFRMNUM_DVCHG                     (1 << 15)  /* Device State Change */

/* USBADDR Register bit definitions */
#define R_USBHS_USBADDR_USBADDR_SHIFT             (0)  /* USB Address Flag */
#define R_USBHS_USBADDR_USBADDR_MASK              0x7f

#define R_USBHS_USBADDR_STSRECOV0_SHIFT           (8)  /* Status Recovery */
#define R_USBHS_USBADDR_STSRECOV0_MASK            0x700
#  define R_USBHS_USBADDR_STSRECOV0_000                   (0 << R_USBHS_USBADDR_STSRECOV0_SHIFT)  /* Reserved */
#  define R_USBHS_USBADDR_STSRECOV0_001                   (1 << R_USBHS_USBADDR_STSRECOV0_SHIFT)  /* [D] Return to the full-speed connection and Default state */
#  define R_USBHS_USBADDR_STSRECOV0_010                   (2 << R_USBHS_USBADDR_STSRECOV0_SHIFT)  /* [D] Return to the full-speed connection and Address state [H] Return to the low-speed state (bits DVSTCTR0.RHST[2:0] = 001b)  */
#  define R_USBHS_USBADDR_STSRECOV0_011                   (3 << R_USBHS_USBADDR_STSRECOV0_SHIFT)  /* [D] Return to the full-speed connection and Configured state */
#  define R_USBHS_USBADDR_STSRECOV0_100                   (4 << R_USBHS_USBADDR_STSRECOV0_SHIFT)  /* [D] Return to the suspend connection and Suspend state [H] Return to the full-speed state (bits DVSTCTR0.RHST[2:0] = 010b)  */
#  define R_USBHS_USBADDR_STSRECOV0_101                   (5 << R_USBHS_USBADDR_STSRECOV0_SHIFT)  /* [D] Return to the high-speed connection and Default state */
#  define R_USBHS_USBADDR_STSRECOV0_110                   (6 << R_USBHS_USBADDR_STSRECOV0_SHIFT)  /* [D] Return to the high-speed connection and Address state [H] Return to the high-speed state (bits DVSTCTR0.RHST[2:0] = 011b)  */
#  define R_USBHS_USBADDR_STSRECOV0_111                   (7 << R_USBHS_USBADDR_STSRECOV0_SHIFT)  /* [D] Return to the high-speed connection and Configured state */

/* USBREQ Register bit definitions */
#define R_USBHS_USBREQ_BMREQUESTTYPE_SHIFT        (0)  /* USB request bmRequestType value */
#define R_USBHS_USBREQ_BMREQUESTTYPE_MASK         0xff

#define R_USBHS_USBREQ_BREQUEST_SHIFT             (8)  /* USB request bRequest value */
#define R_USBHS_USBREQ_BREQUEST_MASK              0xff00

/* USBVAL Register bit definitions */
#define R_USBHS_USBVAL_WVALUE_SHIFT               (0)  /* USB request wValue value */
#define R_USBHS_USBVAL_WVALUE_MASK                0xffff

/* USBINDX Register bit definitions */
#define R_USBHS_USBINDX_WINDEX_SHIFT              (0)  /* USB request wIndex value */
#define R_USBHS_USBINDX_WINDEX_MASK               0xffff

/* USBLENG Register bit definitions */
#define R_USBHS_USBLENG_WLENTUH_SHIFT             (0)  /* USB request wLength value */
#define R_USBHS_USBLENG_WLENTUH_MASK              0xffff

/* DCPCFG Register bit definitions */
#define R_USBHS_DCPCFG_DIR                        (1 << 4)  /* Transfer Direction */

#define R_USBHS_DCPCFG_SHTNAK                     (1 << 7)  /* Pipe Blocking on End of Transfer */

#define R_USBHS_DCPCFG_CNTMD                      (1 << 8)  /* Continuous Transfer Mode */

/* DCPMAXP Register bit definitions */
#define R_USBHS_DCPMAXP_MXPS_SHIFT                (0)  /* Maximum Packet Size */
#define R_USBHS_DCPMAXP_MXPS_MASK                 0x7f

#define R_USBHS_DCPMAXP_DEVSEL_SHIFT              (12)  /* Device Select */
#define R_USBHS_DCPMAXP_DEVSEL_MASK               0xf000
#  define R_USBHS_DCPMAXP_DEVSEL_0X0                      (0 << R_USBHS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0x0 */
#  define R_USBHS_DCPMAXP_DEVSEL_0X1                      (1 << R_USBHS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0x1 */
#  define R_USBHS_DCPMAXP_DEVSEL_0X2                      (2 << R_USBHS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0x2 */
#  define R_USBHS_DCPMAXP_DEVSEL_0X3                      (3 << R_USBHS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0x3 */
#  define R_USBHS_DCPMAXP_DEVSEL_0X4                      (4 << R_USBHS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0x4 */
#  define R_USBHS_DCPMAXP_DEVSEL_0X5                      (5 << R_USBHS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0x5 */

/* DCPCTR Register bit definitions */
#define R_USBHS_DCPCTR_PID_SHIFT                  (0)  /* Response PID */
#define R_USBHS_DCPCTR_PID_MASK                   0x3
#  define R_USBHS_DCPCTR_PID_00                           (0 << R_USBHS_DCPCTR_PID_SHIFT)  /* NAK response */
#  define R_USBHS_DCPCTR_PID_01                           (1 << R_USBHS_DCPCTR_PID_SHIFT)  /* BUF response (depends on buffer state) */
#  define R_USBHS_DCPCTR_PID_10                           (2 << R_USBHS_DCPCTR_PID_SHIFT)  /* STALL response */
#  define R_USBHS_DCPCTR_PID_10                           (2 << R_USBHS_DCPCTR_PID_SHIFT)  /* STALL response */

#define R_USBHS_DCPCTR_CCPL                       (1 << 2)  /* Control Transfer End Enable */

#define R_USBHS_DCPCTR_PINGE                      (1 << 4)  /* PING Token Issue Enable */

#define R_USBHS_DCPCTR_PBUSY                      (1 << 5)  /* Pipe Busy Flag */

#define R_USBHS_DCPCTR_SQMON                      (1 << 6)  /* Sequence Toggle Bit Monitor Flag */

#define R_USBHS_DCPCTR_SQSET                      (1 << 7)  /* Sequence Toggle Bit Set */

#define R_USBHS_DCPCTR_SQCLR                      (1 << 8)  /* Sequence Toggle Bit Clear */

#define R_USBHS_DCPCTR_SUREQCLR                   (1 << 11)  /* SUREQ Bit Clear */

#define R_USBHS_DCPCTR_CSSTS                      (1 << 12)  /* CSSTS Status Flag */

#define R_USBHS_DCPCTR_CSCLR                      (1 << 13)  /* CSSTS Status Flag Clear */

#define R_USBHS_DCPCTR_SUREQ                      (1 << 14)  /* SETUP Token Transmission */

#define R_USBHS_DCPCTR_BSTS                       (1 << 15)  /* Buffer Status Flag */

/* PIPESEL Register bit definitions */
#define R_USBHS_PIPESEL_PIPESEL_SHIFT             (0)  /* Pipe Window Select */
#define R_USBHS_PIPESEL_PIPESEL_MASK              0xf
#  define R_USBHS_PIPESEL_PIPESEL_0X0                     (0 << R_USBHS_PIPESEL_PIPESEL_SHIFT)  /* No pipe selected */
#  define R_USBHS_PIPESEL_PIPESEL_0X1                     (1 << R_USBHS_PIPESEL_PIPESEL_SHIFT)  /* Pipe 1 */
#  define R_USBHS_PIPESEL_PIPESEL_0X2                     (2 << R_USBHS_PIPESEL_PIPESEL_SHIFT)  /* Pipe 2 */
#  define R_USBHS_PIPESEL_PIPESEL_0X3                     (3 << R_USBHS_PIPESEL_PIPESEL_SHIFT)  /* Pipe 3 */
#  define R_USBHS_PIPESEL_PIPESEL_0X4                     (4 << R_USBHS_PIPESEL_PIPESEL_SHIFT)  /* Pipe 4 */
#  define R_USBHS_PIPESEL_PIPESEL_0X5                     (5 << R_USBHS_PIPESEL_PIPESEL_SHIFT)  /* Pipe 5 */
#  define R_USBHS_PIPESEL_PIPESEL_0X6                     (6 << R_USBHS_PIPESEL_PIPESEL_SHIFT)  /* Pipe 6 */
#  define R_USBHS_PIPESEL_PIPESEL_0X7                     (7 << R_USBHS_PIPESEL_PIPESEL_SHIFT)  /* Pipe 7 */
#  define R_USBHS_PIPESEL_PIPESEL_0X8                     (8 << R_USBHS_PIPESEL_PIPESEL_SHIFT)  /* Pipe 8 */
#  define R_USBHS_PIPESEL_PIPESEL_0X9                     (9 << R_USBHS_PIPESEL_PIPESEL_SHIFT)  /* Pipe 9 */

/* PIPECFG Register bit definitions */
#define R_USBHS_PIPECFG_EPNUM_SHIFT               (0)  /* Endpoint Number */
#define R_USBHS_PIPECFG_EPNUM_MASK                0xf

#define R_USBHS_PIPECFG_DIR                       (1 << 4)  /* Transfer Direction */

#define R_USBHS_PIPECFG_SHTNAK                    (1 << 7)  /* Pipe Disabled at End of Transfer */

#define R_USBHS_PIPECFG_CNTMD                     (1 << 8)  /* Continuous Transfer Mode */

#define R_USBHS_PIPECFG_DBLB                      (1 << 9)  /* Double Buffer Mode */

#define R_USBHS_PIPECFG_BFRE                      (1 << 10)  /* BRDY Interrupt Operation Specification */

#define R_USBHS_PIPECFG_TYPE_SHIFT                (14)  /* Transfer Type */
#define R_USBHS_PIPECFG_TYPE_MASK                 0xc000
#  define R_USBHS_PIPECFG_TYPE_00                         (0 << R_USBHS_PIPECFG_TYPE_SHIFT)  /* Pipe not used */
#  define R_USBHS_PIPECFG_TYPE_01                         (1 << R_USBHS_PIPECFG_TYPE_SHIFT)  /* (Pipe 1 to 5) Bulk transfer (Pipe 6 to 9) Setting prohibited  */
#  define R_USBHS_PIPECFG_TYPE_10                         (2 << R_USBHS_PIPECFG_TYPE_SHIFT)  /* (Pipe 1 to 5) Setting prohibited (Pipe 6 to 9) Interrupt transfer  */
#  define R_USBHS_PIPECFG_TYPE_11                         (3 << R_USBHS_PIPECFG_TYPE_SHIFT)  /* (Pipe 1 to 2) Isochronous transfer (Pipe 3 to 9) Setting prohibited  */

/* PIPEBUF Register bit definitions */
#define R_USBHS_PIPEBUF_BUFNMB_SHIFT              (0)  /* Buffer Number */
#define R_USBHS_PIPEBUF_BUFNMB_MASK               0xff

#define R_USBHS_PIPEBUF_BUFSIZE_SHIFT             (10)  /* Buffer Size */
#define R_USBHS_PIPEBUF_BUFSIZE_MASK              0x7c00

/* PIPEMAXP Register bit definitions */
#define R_USBHS_PIPEMAXP_MXPS_SHIFT               (0)  /* Maximum Packet Size */
#define R_USBHS_PIPEMAXP_MXPS_MASK                0x7ff

#define R_USBHS_PIPEMAXP_DEVSEL_SHIFT             (12)  /* Device Select */
#define R_USBHS_PIPEMAXP_DEVSEL_MASK              0xf000

/* PIPEPERI Register bit definitions */
#define R_USBHS_PIPEPERI_IITV_SHIFT               (0)  /* Interval Error Detection Interval */
#define R_USBHS_PIPEPERI_IITV_MASK                0x7

#define R_USBHS_PIPEPERI_IFIS                     (1 << 12)  /* Isochronous IN Buffer Flush */

/* PIPECTR Register bit definitions */
#define R_USBHS_PIPECTR_PID_SHIFT                 (0)  /* Response PID */
#define R_USBHS_PIPECTR_PID_MASK                  0x3
#  define R_USBHS_PIPECTR_PID_00                          (0 << R_USBHS_PIPECTR_PID_SHIFT)  /* NAK response */
#  define R_USBHS_PIPECTR_PID_01                          (1 << R_USBHS_PIPECTR_PID_SHIFT)  /* BUF response (depends on buffer state) */
#  define R_USBHS_PIPECTR_PID_10                          (2 << R_USBHS_PIPECTR_PID_SHIFT)  /* STALL response */
#  define R_USBHS_PIPECTR_PID_11                          (3 << R_USBHS_PIPECTR_PID_SHIFT)  /* STALL response */

#define R_USBHS_PIPECTR_PBUSY                     (1 << 5)  /* Pipe Busy Flag */

#define R_USBHS_PIPECTR_SQMON                     (1 << 6)  /* Sequence Toggle Bit Monitor Flag */

#define R_USBHS_PIPECTR_SQSET                     (1 << 7)  /* Sequence Toggle Bit Set */

#define R_USBHS_PIPECTR_SQCLR                     (1 << 8)  /* Sequence Toggle Bit Clear */

#define R_USBHS_PIPECTR_ACLRM                     (1 << 9)  /* Auto Buffer Clear Mode */

#define R_USBHS_PIPECTR_ATREPM                    (1 << 10)  /* Auto Response Mode */

#define R_USBHS_PIPECTR_CSSTS                     (1 << 12)  /* CSSTS Status Flag */

#define R_USBHS_PIPECTR_CSCLR                     (1 << 13)  /* CSPLIT Status Clear */

#define R_USBHS_PIPECTR_INBUFM                    (1 << 14)  /* Transmit Buffer Monitor Flag */

#define R_USBHS_PIPECTR_BSTS                      (1 << 15)  /* Buffer Status Flag */

/* PIPETRE Register bit definitions */
#define R_USBHS_PIPETRE_TRCLR                     (1 << 8)  /* Transaction Counter Clear */

#define R_USBHS_PIPETRE_TRENB                     (1 << 9)  /* Transaction Counter Enable */

/* PIPETRN Register bit definitions */
#define R_USBHS_PIPETRN_TRNCNT_SHIFT              (0)  /* Transaction Counter */
#define R_USBHS_PIPETRN_TRNCNT_MASK               0xffff

/* DEVADD Register bit definitions */
#define R_USBHS_DEVADD_USBSPD_SHIFT               (6)  /* Transfer Speed of Communication Target Device */
#define R_USBHS_DEVADD_USBSPD_MASK                0xc0
#  define R_USBHS_DEVADD_USBSPD_00                        (0 << R_USBHS_DEVADD_USBSPD_SHIFT)  /* Do not use DEVADDn */
#  define R_USBHS_DEVADD_USBSPD_01                        (1 << R_USBHS_DEVADD_USBSPD_SHIFT)  /* Low speed */
#  define R_USBHS_DEVADD_USBSPD_10                        (2 << R_USBHS_DEVADD_USBSPD_SHIFT)  /* Full speed */
#  define R_USBHS_DEVADD_USBSPD_11                        (3 << R_USBHS_DEVADD_USBSPD_SHIFT)  /* High speed */

#define R_USBHS_DEVADD_HUBPORT_SHIFT              (8)  /* Communication Target Connecting Hub Port */
#define R_USBHS_DEVADD_HUBPORT_MASK               0x700
#  define R_USBHS_DEVADD_HUBPORT_000                      (0 << R_USBHS_DEVADD_HUBPORT_SHIFT)  /* Connect directly to the USBHS port */

#define R_USBHS_DEVADD_UPPHUB_SHIFT               (11)  /* Communication Target Connecting Hub Register */
#define R_USBHS_DEVADD_UPPHUB_MASK                0x7800
#  define R_USBHS_DEVADD_UPPHUB_0X0                       (0 << R_USBHS_DEVADD_UPPHUB_SHIFT)  /* Connect directly to the USBHS port */

/* DEVADDA Register bit definitions */
#define R_USBHS_DEVADDA_USBSPD_SHIFT              (6)  /* Transfer Speed of Communication Target Device */
#define R_USBHS_DEVADDA_USBSPD_MASK               0xc0
#  define R_USBHS_DEVADDA_USBSPD_00                       (0 << R_USBHS_DEVADDA_USBSPD_SHIFT)  /* Do not use DEVADDn */
#  define R_USBHS_DEVADDA_USBSPD_01                       (1 << R_USBHS_DEVADDA_USBSPD_SHIFT)  /* Low speed */
#  define R_USBHS_DEVADDA_USBSPD_10                       (2 << R_USBHS_DEVADDA_USBSPD_SHIFT)  /* Full speed */
#  define R_USBHS_DEVADDA_USBSPD_11                       (3 << R_USBHS_DEVADDA_USBSPD_SHIFT)  /* High speed */

#define R_USBHS_DEVADDA_HUBPORT_SHIFT             (8)  /* Communication Target Connecting Hub Port */
#define R_USBHS_DEVADDA_HUBPORT_MASK              0x700
#  define R_USBHS_DEVADDA_HUBPORT_000                     (0 << R_USBHS_DEVADDA_HUBPORT_SHIFT)  /* Connect directly to the USBHS port */

#define R_USBHS_DEVADDA_UPPHUB_SHIFT              (11)  /* Communication Target Connecting Hub Register */
#define R_USBHS_DEVADDA_UPPHUB_MASK               0x7800
#  define R_USBHS_DEVADDA_UPPHUB_0X0                      (0 << R_USBHS_DEVADDA_UPPHUB_SHIFT)  /* Connect directly to the USBHS port */

/* LPCTRL Register bit definitions */
#define R_USBHS_LPCTRL_HWUPM                      (1 << 7)  /* Resume Return Mode Setting */

/* LPSTS Register bit definitions */
#define R_USBHS_LPSTS_SUSPENDM                    (1 << 14)  /* UTMI SuspendM Control */

/* BCCTRL Register bit definitions */
#define R_USBHS_BCCTRL_IDPSRCE                    (1 << 0)  /* IDPSRC Control */

#define R_USBHS_BCCTRL_IDMSINKE                   (1 << 1)  /* IDMSINK Control */

#define R_USBHS_BCCTRL_VDPSRCE                    (1 << 2)  /* VDPSRC Control */

#define R_USBHS_BCCTRL_IDPSINKE                   (1 << 3)  /* IDPSINK Control */

#define R_USBHS_BCCTRL_VDMSRCE                    (1 << 4)  /* VDMSRC Control */

#define R_USBHS_BCCTRL_DCPMODE                    (1 << 5)  /* DCP Mode Control */

#define R_USBHS_BCCTRL_CHGDETSTS                  (1 << 8)  /* CHGDET Status Flag */

#define R_USBHS_BCCTRL_PDDETSTS                   (1 << 9)  /* PDDET Status Flag */

/* PL1CTRL1 Register bit definitions */
#define R_USBHS_PL1CTRL1_L1RESPEN                 (1 << 0)  /* L1 Response Enable */

#define R_USBHS_PL1CTRL1_L1RESPMD_SHIFT           (1)  /* L1 Response Mode */
#define R_USBHS_PL1CTRL1_L1RESPMD_MASK            0x6
#  define R_USBHS_PL1CTRL1_L1RESPMD_00                    (0 << R_USBHS_PL1CTRL1_L1RESPMD_SHIFT)  /* NYET response */
#  define R_USBHS_PL1CTRL1_L1RESPMD_01                    (1 << R_USBHS_PL1CTRL1_L1RESPMD_SHIFT)  /* ACK response */
#  define R_USBHS_PL1CTRL1_L1RESPMD_10                    (2 << R_USBHS_PL1CTRL1_L1RESPMD_SHIFT)  /* STALL response */
#  define R_USBHS_PL1CTRL1_L1RESPMD_11                    (3 << R_USBHS_PL1CTRL1_L1RESPMD_SHIFT)  /* Response based on L1NEGOMD setting */

#define R_USBHS_PL1CTRL1_L1NEGOMD                 (1 << 3)  /* L1 Response Negotiation Control */

#define R_USBHS_PL1CTRL1_DVSQ_SHIFT               (4)  /* DVSQ Extension Flag */
#define R_USBHS_PL1CTRL1_DVSQ_MASK                0xf0
#  define R_USBHS_PL1CTRL1_DVSQ_0000                      (0 << R_USBHS_PL1CTRL1_DVSQ_SHIFT)  /* Powered state */
#  define R_USBHS_PL1CTRL1_DVSQ_0001                      (1 << R_USBHS_PL1CTRL1_DVSQ_SHIFT)  /* Default state */
#  define R_USBHS_PL1CTRL1_DVSQ_0010                      (2 << R_USBHS_PL1CTRL1_DVSQ_SHIFT)  /* Address state */
#  define R_USBHS_PL1CTRL1_DVSQ_0011                      (3 << R_USBHS_PL1CTRL1_DVSQ_SHIFT)  /* Configured state */
#  define R_USBHS_PL1CTRL1_DVSQ_01XX                      (0 << R_USBHS_PL1CTRL1_DVSQ_SHIFT)  /* Suspend state */
#  define R_USBHS_PL1CTRL1_DVSQ_10XX                      (0 << R_USBHS_PL1CTRL1_DVSQ_SHIFT)  /* L1 state */

#define R_USBHS_PL1CTRL1_HIRDTHR_SHIFT            (8)  /* L1 Response Negotiation Threshold Value */
#define R_USBHS_PL1CTRL1_HIRDTHR_MASK             0xf00

#define R_USBHS_PL1CTRL1_L1EXTMD                  (1 << 14)  /* PHY Control Mode at L1 Return */

/* PL1CTRL2 Register bit definitions */
#define R_USBHS_PL1CTRL2_HIRDMON_SHIFT            (8)  /* HIRD Value Monitor */
#define R_USBHS_PL1CTRL2_HIRDMON_MASK             0xf00

#define R_USBHS_PL1CTRL2_RWEMON                   (1 << 12)  /* RWE Value Monitor */

/* HL1CTRL1 Register bit definitions */
#define R_USBHS_HL1CTRL1_L1REQ                    (1 << 0)  /* L1 Transition Request */

#define R_USBHS_HL1CTRL1_L1STATUS_SHIFT           (1)  /* L1 Request Completion Status */
#define R_USBHS_HL1CTRL1_L1STATUS_MASK            0x6
#  define R_USBHS_HL1CTRL1_L1STATUS_00                    (0 << R_USBHS_HL1CTRL1_L1STATUS_SHIFT)  /* ACK received */
#  define R_USBHS_HL1CTRL1_L1STATUS_01                    (1 << R_USBHS_HL1CTRL1_L1STATUS_SHIFT)  /* NYET received */
#  define R_USBHS_HL1CTRL1_L1STATUS_10                    (2 << R_USBHS_HL1CTRL1_L1STATUS_SHIFT)  /* STALL received */
#  define R_USBHS_HL1CTRL1_L1STATUS_11                    (3 << R_USBHS_HL1CTRL1_L1STATUS_SHIFT)  /* Transaction error */

/* HL1CTRL2 Register bit definitions */
#define R_USBHS_HL1CTRL2_L1ADDR_SHIFT             (0)  /* LPM Token Device Address */
#define R_USBHS_HL1CTRL2_L1ADDR_MASK              0xf

#define R_USBHS_HL1CTRL2_HIRD_SHIFT               (8)  /* LPM Token HIRD */
#define R_USBHS_HL1CTRL2_HIRD_MASK                0xf00

#define R_USBHS_HL1CTRL2_L1RWE                    (1 << 12)  /* LPM Token L1 Remote Wake Enable */

#define R_USBHS_HL1CTRL2_BESL                     (1 << 15)  /* BESL & Alternate HIRD */

/* DPUSR0R Register bit definitions */
#define R_USBHS_DPUSR0R_DOVCAHM                   (1 << 20)  /* OVRCURA Input Flag */

#define R_USBHS_DPUSR0R_DOVCBHM                   (1 << 21)  /* OVRCURB Input Flag */

#define R_USBHS_DPUSR0R_DVBSTSHM                  (1 << 23)  /* VBUS Input Flag */

/* DPUSR1R Register bit definitions */
#define R_USBHS_DPUSR1R_DOVCAHE                   (1 << 4)  /* OVRCURA Interrupt Enable Clear */

#define R_USBHS_DPUSR1R_DOVCBHE                   (1 << 5)  /* OVRCURB Interrupt Enable Clear */

#define R_USBHS_DPUSR1R_DVBSTSHE                  (1 << 7)  /* VBUS Interrupt Enable/Clear */

#define R_USBHS_DPUSR1R_DOVCAH                    (1 << 20)  /* OVRCURA Interrupt Source Return Status Flag */

#define R_USBHS_DPUSR1R_DOVCBH                    (1 << 21)  /* OVRCURB Interrupt Source Return Status Flag */

#define R_USBHS_DPUSR1R_DVBSTSH                   (1 << 23)  /* VBUS Interrupt Source Return Status Flag */

/* DPUSR2R Register bit definitions */
#define R_USBHS_DPUSR2R_DPINT                     (1 << 0)  /* Indication of Return from DP Interrupt Source */

#define R_USBHS_DPUSR2R_DMINT                     (1 << 1)  /* Indication of Return from DM Interrupt Source */

#define R_USBHS_DPUSR2R_DPVAL                     (1 << 4)  /* DP Input */

#define R_USBHS_DPUSR2R_DMVAL                     (1 << 5)  /* DM Input */

#define R_USBHS_DPUSR2R_DPINTE                    (1 << 8)  /* DP Interrupt Enable Clear */

#define R_USBHS_DPUSR2R_DMINTE                    (1 << 9)  /* DM Interrupt Enable Clear */

/* DPUSRCR Register bit definitions */
#define R_USBHS_DPUSRCR_FIXPHY                    (1 << 0)  /* USB Transceiver Control Fix */

#define R_USBHS_DPUSRCR_FIXPHYPD                  (1 << 1)  /* USB Transceiver Control Fix for PLL */


/* Maximum number of channels */

#define USBHS_MAX_CHANNELS    10

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_USBHS_H */
