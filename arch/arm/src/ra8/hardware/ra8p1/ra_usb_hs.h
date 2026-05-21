/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_usb_hs.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_USB_HS_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_USB_HS_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* USB_HS Base Address */
#ifndef R_USB_HS_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_USB_HS_BASE           0x40351000
#else
#define R_USB_HS_BASE           0x50351000
#endif
#endif

/* USB_HS Register Offsets */

#define R_USB_HS_SYSCFG_OFFSET                    0x00000000  /* System Configuration Control Register */
#define R_USB_HS_BUSWAIT_OFFSET                   0x00000002  /* CPU Bus Wait Register */
#define R_USB_HS_SYSSTS0_OFFSET                   0x00000004  /* System Configuration Status Register */
#define R_USB_HS_PLLSTA_OFFSET                    0x00000006  /* PLL Status Register */
#define R_USB_HS_DVSTCTR0_OFFSET                  0x00000008  /* Device State Control Register 0 */
#define R_USB_HS_TESTMODE_OFFSET                  0x0000000c  /* USB Test Mode Register  */
#define R_USB_HS_CFIFO_OFFSET                     0x00000014  /* CFIFO Port Register */
#define R_USB_HS_CFIFOL_OFFSET                    0x00000014  /* CFIFO Port Register L */
#define R_USB_HS_CFIFOLL_OFFSET                   0x00000014  /* CFIFO Port Register LL */
#define R_USB_HS_CFIFOH_OFFSET                    0x00000016  /* CFIFO Port Register H */
#define R_USB_HS_CFIFOHH_OFFSET                   0x00000017  /* CFIFO Port Register HH */
#define R_USB_HS_D0FIFO_OFFSET                    0x00000018  /* D0FIFO Port Register */
#define R_USB_HS_D0FIFOL_OFFSET                   0x00000018  /* D0FIFO Port Register L */
#define R_USB_HS_D0FIFOLL_OFFSET                  0x00000018  /* D0FIFO Port Register LL */
#define R_USB_HS_D0FIFOH_OFFSET                   0x0000001a  /* D0FIFO Port Register H */
#define R_USB_HS_D0FIFOHH_OFFSET                  0x0000001b  /* D0FIFO Port Register HH */
#define R_USB_HS_D1FIFO_OFFSET                    0x0000001c  /* D1FIFO Port Register */
#define R_USB_HS_D1FIFOL_OFFSET                   0x0000001c  /* D1FIFO Port Register L */
#define R_USB_HS_D1FIFOLL_OFFSET                  0x0000001c  /* D1FIFO Port Register LL */
#define R_USB_HS_D1FIFOH_OFFSET                   0x0000001e  /* D1FIFO Port Register H */
#define R_USB_HS_D1FIFOHH_OFFSET                  0x0000001f  /* D1FIFO Port Register HH */
#define R_USB_HS_CFIFOSEL_OFFSET                  0x00000020  /* CFIFO Port Select Register */
#define R_USB_HS_CFIFOCTR_OFFSET                  0x00000022  /* CFIFO Port Control Register */
#define R_USB_HS_D0FIFOSEL_OFFSET                 0x00000028  /* D0FIFO Port Select Register */
#define R_USB_HS_D0FIFOCTR_OFFSET                 0x0000002a  /* D0FIFO Port Control Register  */
#define R_USB_HS_D1FIFOSEL_OFFSET                 0x0000002c  /* D1FIFO Port Select Register */
#define R_USB_HS_D1FIFOCTR_OFFSET                 0x0000002e  /* D1FIFO Port Control Register  */
#define R_USB_HS_INTENB0_OFFSET                   0x00000030  /* Interrupt Enable Register 0 */
#define R_USB_HS_INTENB1_OFFSET                   0x00000032  /* Interrupt Enable Register 1  */
#define R_USB_HS_BRDYENB_OFFSET                   0x00000036  /* BRDY Interrupt Enable Register */
#define R_USB_HS_NRDYENB_OFFSET                   0x00000038  /* NRDY Interrupt Enable Register */
#define R_USB_HS_BEMPENB_OFFSET                   0x0000003a  /* BEMP Interrupt Enable Register */
#define R_USB_HS_SOFCFG_OFFSET                    0x0000003c  /* SOF Pin Configuration Register  */
#define R_USB_HS_PHYSET_OFFSET                    0x0000003e  /* PHY Setting Register */
#define R_USB_HS_INTSTS0_OFFSET                   0x00000040  /* Interrupt Status Register 0 */
#define R_USB_HS_INTSTS1_OFFSET                   0x00000042  /* Interrupt Status Register 1 */
#define R_USB_HS_BRDYSTS_OFFSET                   0x00000046  /* BRDY Interrupt Status Register */
#define R_USB_HS_NRDYSTS_OFFSET                   0x00000048  /* NRDY Interrupt Status Register */
#define R_USB_HS_BEMPSTS_OFFSET                   0x0000004a  /* BEMP Interrupt Status Register */
#define R_USB_HS_FRMNUM_OFFSET                    0x0000004c  /* Frame Number Register */
#define R_USB_HS_UFRMNUM_OFFSET                   0x0000004e  /* uFrame Number Register  */
#define R_USB_HS_USBADDR_OFFSET                   0x00000050  /* USB Address Register */
#define R_USB_HS_USBREQ_OFFSET                    0x00000054  /* USB Request Type Register */
#define R_USB_HS_USBVAL_OFFSET                    0x00000056  /* USB Request Value Register */
#define R_USB_HS_USBINDX_OFFSET                   0x00000058  /* USB Request Index Register */
#define R_USB_HS_USBLENG_OFFSET                   0x0000005a  /* USB Request Length Register  */
#define R_USB_HS_DCPCFG_OFFSET                    0x0000005c  /* DCP Configuration Register */
#define R_USB_HS_DCPMAXP_OFFSET                   0x0000005e  /* DCP Maximum Packet Size Register  */
#define R_USB_HS_DCPCTR_OFFSET                    0x00000060  /* DCP Control Register */
#define R_USB_HS_PIPESEL_OFFSET                   0x00000064  /* Pipe Window Select Register */
#define R_USB_HS_PIPECFG_OFFSET                   0x00000068  /* Pipe Configuration Register */
#define R_USB_HS_PIPEBUF_OFFSET                   0x0000006a  /* Pipe Buffer Register */
#define R_USB_HS_PIPEMAXP_OFFSET                  0x0000006c  /* Pipe Maximum Packet Size Register */
#define R_USB_HS_PIPEPERI_OFFSET                  0x0000006e  /* Pipe Cycle Control Register */
/* PIPE_CTR[%s] Registers () */
#define R_USB_HS_PIPE_CTR_OFFSET(m)               (0x00000070 + ((m) * 0x00000002))  /* PIPE Control Register */
/* PIPE_TR[%s] Registers () */
#define R_USB_HS_PIPE_TR_OFFSET(m)                (0x00000090 + ((m) * 0x00000004))  /* Pipe Transaction Counter Registers */
/* DEVADD[%s] Registers () */
#define R_USB_HS_DEVADD_OFFSET(m)                 (0x000000d0 + ((m) * 0x00000002))  /* Device Address Configuration Register */
#define R_USB_HS_LPCTRL_OFFSET                    0x00000100  /* Low Power Control Register */
#define R_USB_HS_LPSTS_OFFSET                     0x00000102  /* Low Power Status Register */
#define R_USB_HS_BCCTRL_OFFSET                    0x00000140  /* Battery Charging Control Register */
#define R_USB_HS_PL1CTRL1_OFFSET                  0x00000144  /* Function L1 Control Register 1 */
#define R_USB_HS_PL1CTRL2_OFFSET                  0x00000146  /* Function L1 Control Register 2 */
#define R_USB_HS_HL1CTRL1_OFFSET                  0x00000148  /* Host L1 Control Register 1 */
#define R_USB_HS_HL1CTRL2_OFFSET                  0x0000014a  /* Host L1 Control Register 2 */
#define R_USB_HS_PHYTRIM1_OFFSET                  0x00000150  /* PHY Timing Register 1 */
#define R_USB_HS_PHYTRIM2_OFFSET                  0x00000152  /* PHY Timing Register 2 */
#define R_USB_HS_DPUSR0R_OFFSET                   0x00000160  /* Deep Standby USB Transceiver Control/Pin Monitor Register  */
#define R_USB_HS_DPUSR1R_OFFSET                   0x00000164  /* Deep Standby USB Suspend/Resume Interrupt Register */
#define R_USB_HS_DPUSR2R_OFFSET                   0x00000168  /* Deep Standby USB Suspend/Resume Interrupt Register */
#define R_USB_HS_DPUSRCR_OFFSET                   0x0000016a  /* Deep Standby USB Suspend/Resume Command Register */

/* USB_HS Register Addresses */

#define R_USB_HS_SYSCFG                           (R_USB_HS_BASE + R_USB_HS_SYSCFG_OFFSET)
#define R_USB_HS_BUSWAIT                          (R_USB_HS_BASE + R_USB_HS_BUSWAIT_OFFSET)
#define R_USB_HS_SYSSTS0                          (R_USB_HS_BASE + R_USB_HS_SYSSTS0_OFFSET)
#define R_USB_HS_PLLSTA                           (R_USB_HS_BASE + R_USB_HS_PLLSTA_OFFSET)
#define R_USB_HS_DVSTCTR0                         (R_USB_HS_BASE + R_USB_HS_DVSTCTR0_OFFSET)
#define R_USB_HS_TESTMODE                         (R_USB_HS_BASE + R_USB_HS_TESTMODE_OFFSET)
#define R_USB_HS_CFIFO                            (R_USB_HS_BASE + R_USB_HS_CFIFO_OFFSET)
#define R_USB_HS_CFIFOL                           (R_USB_HS_BASE + R_USB_HS_CFIFOL_OFFSET)
#define R_USB_HS_CFIFOLL                          (R_USB_HS_BASE + R_USB_HS_CFIFOLL_OFFSET)
#define R_USB_HS_CFIFOH                           (R_USB_HS_BASE + R_USB_HS_CFIFOH_OFFSET)
#define R_USB_HS_CFIFOHH                          (R_USB_HS_BASE + R_USB_HS_CFIFOHH_OFFSET)
#define R_USB_HS_D0FIFO                           (R_USB_HS_BASE + R_USB_HS_D0FIFO_OFFSET)
#define R_USB_HS_D0FIFOL                          (R_USB_HS_BASE + R_USB_HS_D0FIFOL_OFFSET)
#define R_USB_HS_D0FIFOLL                         (R_USB_HS_BASE + R_USB_HS_D0FIFOLL_OFFSET)
#define R_USB_HS_D0FIFOH                          (R_USB_HS_BASE + R_USB_HS_D0FIFOH_OFFSET)
#define R_USB_HS_D0FIFOHH                         (R_USB_HS_BASE + R_USB_HS_D0FIFOHH_OFFSET)
#define R_USB_HS_D1FIFO                           (R_USB_HS_BASE + R_USB_HS_D1FIFO_OFFSET)
#define R_USB_HS_D1FIFOL                          (R_USB_HS_BASE + R_USB_HS_D1FIFOL_OFFSET)
#define R_USB_HS_D1FIFOLL                         (R_USB_HS_BASE + R_USB_HS_D1FIFOLL_OFFSET)
#define R_USB_HS_D1FIFOH                          (R_USB_HS_BASE + R_USB_HS_D1FIFOH_OFFSET)
#define R_USB_HS_D1FIFOHH                         (R_USB_HS_BASE + R_USB_HS_D1FIFOHH_OFFSET)
#define R_USB_HS_CFIFOSEL                         (R_USB_HS_BASE + R_USB_HS_CFIFOSEL_OFFSET)
#define R_USB_HS_CFIFOCTR                         (R_USB_HS_BASE + R_USB_HS_CFIFOCTR_OFFSET)
#define R_USB_HS_D0FIFOSEL                        (R_USB_HS_BASE + R_USB_HS_D0FIFOSEL_OFFSET)
#define R_USB_HS_D0FIFOCTR                        (R_USB_HS_BASE + R_USB_HS_D0FIFOCTR_OFFSET)
#define R_USB_HS_D1FIFOSEL                        (R_USB_HS_BASE + R_USB_HS_D1FIFOSEL_OFFSET)
#define R_USB_HS_D1FIFOCTR                        (R_USB_HS_BASE + R_USB_HS_D1FIFOCTR_OFFSET)
#define R_USB_HS_INTENB0                          (R_USB_HS_BASE + R_USB_HS_INTENB0_OFFSET)
#define R_USB_HS_INTENB1                          (R_USB_HS_BASE + R_USB_HS_INTENB1_OFFSET)
#define R_USB_HS_BRDYENB                          (R_USB_HS_BASE + R_USB_HS_BRDYENB_OFFSET)
#define R_USB_HS_NRDYENB                          (R_USB_HS_BASE + R_USB_HS_NRDYENB_OFFSET)
#define R_USB_HS_BEMPENB                          (R_USB_HS_BASE + R_USB_HS_BEMPENB_OFFSET)
#define R_USB_HS_SOFCFG                           (R_USB_HS_BASE + R_USB_HS_SOFCFG_OFFSET)
#define R_USB_HS_PHYSET                           (R_USB_HS_BASE + R_USB_HS_PHYSET_OFFSET)
#define R_USB_HS_INTSTS0                          (R_USB_HS_BASE + R_USB_HS_INTSTS0_OFFSET)
#define R_USB_HS_INTSTS1                          (R_USB_HS_BASE + R_USB_HS_INTSTS1_OFFSET)
#define R_USB_HS_BRDYSTS                          (R_USB_HS_BASE + R_USB_HS_BRDYSTS_OFFSET)
#define R_USB_HS_NRDYSTS                          (R_USB_HS_BASE + R_USB_HS_NRDYSTS_OFFSET)
#define R_USB_HS_BEMPSTS                          (R_USB_HS_BASE + R_USB_HS_BEMPSTS_OFFSET)
#define R_USB_HS_FRMNUM                           (R_USB_HS_BASE + R_USB_HS_FRMNUM_OFFSET)
#define R_USB_HS_UFRMNUM                          (R_USB_HS_BASE + R_USB_HS_UFRMNUM_OFFSET)
#define R_USB_HS_USBADDR                          (R_USB_HS_BASE + R_USB_HS_USBADDR_OFFSET)
#define R_USB_HS_USBREQ                           (R_USB_HS_BASE + R_USB_HS_USBREQ_OFFSET)
#define R_USB_HS_USBVAL                           (R_USB_HS_BASE + R_USB_HS_USBVAL_OFFSET)
#define R_USB_HS_USBINDX                          (R_USB_HS_BASE + R_USB_HS_USBINDX_OFFSET)
#define R_USB_HS_USBLENG                          (R_USB_HS_BASE + R_USB_HS_USBLENG_OFFSET)
#define R_USB_HS_DCPCFG                           (R_USB_HS_BASE + R_USB_HS_DCPCFG_OFFSET)
#define R_USB_HS_DCPMAXP                          (R_USB_HS_BASE + R_USB_HS_DCPMAXP_OFFSET)
#define R_USB_HS_DCPCTR                           (R_USB_HS_BASE + R_USB_HS_DCPCTR_OFFSET)
#define R_USB_HS_PIPESEL                          (R_USB_HS_BASE + R_USB_HS_PIPESEL_OFFSET)
#define R_USB_HS_PIPECFG                          (R_USB_HS_BASE + R_USB_HS_PIPECFG_OFFSET)
#define R_USB_HS_PIPEBUF                          (R_USB_HS_BASE + R_USB_HS_PIPEBUF_OFFSET)
#define R_USB_HS_PIPEMAXP                         (R_USB_HS_BASE + R_USB_HS_PIPEMAXP_OFFSET)
#define R_USB_HS_PIPEPERI                         (R_USB_HS_BASE + R_USB_HS_PIPEPERI_OFFSET)
#define R_USB_HS_PIPE_CTR(m)                      (R_USB_HS_BASE + R_USB_HS_PIPE_CTR_OFFSET(m))
#define R_USB_HS_PIPE_TR(m)                       (R_USB_HS_BASE + R_USB_HS_PIPE_TR_OFFSET(m))
#define R_USB_HS_DEVADD(m)                        (R_USB_HS_BASE + R_USB_HS_DEVADD_OFFSET(m))
#define R_USB_HS_LPCTRL                           (R_USB_HS_BASE + R_USB_HS_LPCTRL_OFFSET)
#define R_USB_HS_LPSTS                            (R_USB_HS_BASE + R_USB_HS_LPSTS_OFFSET)
#define R_USB_HS_BCCTRL                           (R_USB_HS_BASE + R_USB_HS_BCCTRL_OFFSET)
#define R_USB_HS_PL1CTRL1                         (R_USB_HS_BASE + R_USB_HS_PL1CTRL1_OFFSET)
#define R_USB_HS_PL1CTRL2                         (R_USB_HS_BASE + R_USB_HS_PL1CTRL2_OFFSET)
#define R_USB_HS_HL1CTRL1                         (R_USB_HS_BASE + R_USB_HS_HL1CTRL1_OFFSET)
#define R_USB_HS_HL1CTRL2                         (R_USB_HS_BASE + R_USB_HS_HL1CTRL2_OFFSET)
#define R_USB_HS_PHYTRIM1                         (R_USB_HS_BASE + R_USB_HS_PHYTRIM1_OFFSET)
#define R_USB_HS_PHYTRIM2                         (R_USB_HS_BASE + R_USB_HS_PHYTRIM2_OFFSET)
#define R_USB_HS_DPUSR0R                          (R_USB_HS_BASE + R_USB_HS_DPUSR0R_OFFSET)
#define R_USB_HS_DPUSR1R                          (R_USB_HS_BASE + R_USB_HS_DPUSR1R_OFFSET)
#define R_USB_HS_DPUSR2R                          (R_USB_HS_BASE + R_USB_HS_DPUSR2R_OFFSET)
#define R_USB_HS_DPUSRCR                          (R_USB_HS_BASE + R_USB_HS_DPUSRCR_OFFSET)

/* Register bit definitions */
/* SYSCFG Register bit definitions */
#define R_USB_HS_SYSCFG_CNEN                      (1 << 8)  /* Single End Receiver Enable */

#define R_USB_HS_SYSCFG_HSE                       (1 << 7)  /* High-Speed Operation Enable */

#define R_USB_HS_SYSCFG_DCFM                      (1 << 6)  /* Controller Function Select */

#define R_USB_HS_SYSCFG_DRPD                      (1 << 5)  /* D+/D- Line Resistor Control */

#define R_USB_HS_SYSCFG_DPRPU                     (1 << 4)  /* D+ Line Resistor Control */

#define R_USB_HS_SYSCFG_USBE                      (1 << 0)  /* USB Operation Enable */

/* BUSWAIT Register bit definitions */
#define R_USB_HS_BUSWAIT_BWAIT_SHIFT              (0)  /* CPU Bus Access Wait Specification     BWAIT waits (BWAIT+2 access cycles) */
#define R_USB_HS_BUSWAIT_BWAIT_MASK               0xf

/* SYSSTS0 Register bit definitions */
#define R_USB_HS_SYSSTS0_HTACT                    (1 << 6)  /* Host Sequencer Status Monitor */

#define R_USB_HS_SYSSTS0_SOFEA                    (1 << 5)  /* SOF Active Monitor While Host Controller Function is Selected. */

#define R_USB_HS_SYSSTS0_IDMON                    (1 << 2)  /* ID0 Pin Monitor */

#define R_USB_HS_SYSSTS0_LNST_SHIFT               (0)  /* USB Data Line Status Monitor */
#define R_USB_HS_SYSSTS0_LNST_MASK                0x3
#  define R_USB_HS_SYSSTS0_LNST_00                        (0 << R_USB_HS_SYSSTS0_LNST_SHIFT)  /* SE0 (During Low-Speed Operation:only when the host controller function is selected or During Full-Speed Operation) /Squelch (During Hi-Speed Operation or During Chirp Operation) */
#  define R_USB_HS_SYSSTS0_LNST_01                        (1 << R_USB_HS_SYSSTS0_LNST_SHIFT)  /* K-State (During Low-Speed Operation:only when the host controller function is selected) /J-State (During Full-Speed Operation) /Unsquelch (During Hi-Speed Operation) /Chirp J (During Chirp Operation) */
#  define R_USB_HS_SYSSTS0_LNST_10                        (2 << R_USB_HS_SYSSTS0_LNST_SHIFT)  /* J-State (During Low-Speed Operation:only when the host controller function is selected) /K-State (During Full-Speed Operation) /Invalid (During Hi-Speed Operation) /Chirp K (During Chirp Operation) */
#  define R_USB_HS_SYSSTS0_LNST_11                        (3 << R_USB_HS_SYSSTS0_LNST_SHIFT)  /* SE1 (During Low-Speed Operation:only when the host controller function is selected or During Full-Speed Operation) /Invalid (During Hi-Speed Operation or During Chirp Operation) */

#define R_USB_HS_SYSSTS0_OVCMON_SHIFT             (14)  /* External USB1_OVRCURA/USB1_OVRCURB Input Pin MonitorThe OCVMON[1] bit indicates the status of the USBHS_OVRCURA pin. The OCVMON[0] bit indicates the status of the USBHS_OVRCURB pin. */
#define R_USB_HS_SYSSTS0_OVCMON_MASK              0xc000

/* PLLSTA Register bit definitions */
#define R_USB_HS_PLLSTA_PLLLOCK                   (1 << 0)  /* PLL Lock Flag */

/* DVSTCTR0 Register bit definitions */
#define R_USB_HS_DVSTCTR0_HNPBTOA                 (1 << 11)  /* Host Negotiation Protocol (HNP) Control Use this bit when switching from device B to device A in OTGmode. If the HNPBTOA bit is 1, the internal function controlremains in the Suspend state until the HNP processing endseven if SYSCFG.DPRPU = 0 or SYSCFG.DCFM = 1 is set. */

#define R_USB_HS_DVSTCTR0_EXICEN                  (1 << 10)  /* USBHS_EXICEN Output Pin Control */

#define R_USB_HS_DVSTCTR0_VBUSEN                  (1 << 9)  /* USBHS_VBUSEN Output Pin Control */

#define R_USB_HS_DVSTCTR0_WKUP                    (1 << 8)  /* Remote Wakeup Output for the Device Controller Operation */

#define R_USB_HS_DVSTCTR0_RWUPE                   (1 << 7)  /* Remote Wakeup Detection Enable for the Host Controller Operation */

#define R_USB_HS_DVSTCTR0_USBRST                  (1 << 6)  /* USB Bus Reset Output for the Host Controller Operation */

#define R_USB_HS_DVSTCTR0_RESUME                  (1 << 5)  /* Resume Signal Output for the Host Controller Operation */

#define R_USB_HS_DVSTCTR0_UACT                    (1 << 4)  /* USB Bus Operation Enable for the Host Controller Operation */

#define R_USB_HS_DVSTCTR0_RHST_SHIFT              (0)  /* USB Bus Reset Status */
#define R_USB_HS_DVSTCTR0_RHST_MASK               0x7
#  define R_USB_HS_DVSTCTR0_RHST_000                      (0 << R_USB_HS_DVSTCTR0_RHST_SHIFT)  /* Communication speed not determined */
#  define R_USB_HS_DVSTCTR0_RHST_001                      (1 << R_USB_HS_DVSTCTR0_RHST_SHIFT)  /* Low-speed connection(When the host controller function is selected) /USB bus reset in progress or low-speed connection(When the function controller function is selected) */
#  define R_USB_HS_DVSTCTR0_RHST_010                      (2 << R_USB_HS_DVSTCTR0_RHST_SHIFT)  /* Full-speed connection(When the host controller function is selected) /USB bus reset in progress or full-speed connection(When the function controller function is selected) */
#  define R_USB_HS_DVSTCTR0_RHST_011                      (3 << R_USB_HS_DVSTCTR0_RHST_SHIFT)  /* Setting prohibited */

/* TESTMODE Register bit definitions */
#define R_USB_HS_TESTMODE_UTST_SHIFT              (0)  /* Test Mode */
#define R_USB_HS_TESTMODE_UTST_MASK               0xf
#  define R_USB_HS_TESTMODE_UTST_0000                     (0 << R_USB_HS_TESTMODE_UTST_SHIFT)  /* Normal operation */
#  define R_USB_HS_TESTMODE_UTST_0001                     (1 << R_USB_HS_TESTMODE_UTST_SHIFT)  /* Test_J TestMode(When the Function Controller Function is Selected) */
#  define R_USB_HS_TESTMODE_UTST_0010                     (2 << R_USB_HS_TESTMODE_UTST_SHIFT)  /* Test_K TestMode(When the Function Controller Function is Selected) */
#  define R_USB_HS_TESTMODE_UTST_0011                     (3 << R_USB_HS_TESTMODE_UTST_SHIFT)  /* Test_SE0_NAK TestMode(When the Function Controller Function is Selected) */
#  define R_USB_HS_TESTMODE_UTST_0100                     (4 << R_USB_HS_TESTMODE_UTST_SHIFT)  /* Test_Packet TestMode(When the Function Controller Function is Selected) */
#  define R_USB_HS_TESTMODE_UTST_0101                     (5 << R_USB_HS_TESTMODE_UTST_SHIFT)  /* Reserved TestMode(When the Function Controller Function is Selected) */
#  define R_USB_HS_TESTMODE_UTST_0110                     (6 << R_USB_HS_TESTMODE_UTST_SHIFT)  /* Reserved TestMode(When the Function Controller Function is Selected) */
#  define R_USB_HS_TESTMODE_UTST_0111                     (7 << R_USB_HS_TESTMODE_UTST_SHIFT)  /* Reserved TestMode(When the Function Controller Function is Selected) */
#  define R_USB_HS_TESTMODE_UTST_1001                     (9 << R_USB_HS_TESTMODE_UTST_SHIFT)  /* Test_J TestMode(When the Host Controller Function is Selected) */
#  define R_USB_HS_TESTMODE_UTST_1010                     (10 << R_USB_HS_TESTMODE_UTST_SHIFT)  /* Test_K TestMode(When the Host Controller Function is Selected) */
#  define R_USB_HS_TESTMODE_UTST_1011                     (11 << R_USB_HS_TESTMODE_UTST_SHIFT)  /* Test_SE0_NAK TestMode(When the Host Controller Function is Selected) */
#  define R_USB_HS_TESTMODE_UTST_1100                     (12 << R_USB_HS_TESTMODE_UTST_SHIFT)  /* Test_Packet TestMode(When the Host Controller Function is Selected) */
#  define R_USB_HS_TESTMODE_UTST_1101                     (13 << R_USB_HS_TESTMODE_UTST_SHIFT)  /* Test_Force_EnableTestMode(When the Host Controller Function is Selected) */
#  define R_USB_HS_TESTMODE_UTST_1110                     (14 << R_USB_HS_TESTMODE_UTST_SHIFT)  /* Reserved TestMode(When the Host Controller Function is Selected) */
#  define R_USB_HS_TESTMODE_UTST_1111                     (15 << R_USB_HS_TESTMODE_UTST_SHIFT)  /* Reserved TestMode(When the Host Controller Function is Selected) */

/* CFIFO Register bit definitions */
#define R_USB_HS_CFIFO_FIFOPORT_SHIFT             (0)  /* FIFO Port.Read receive data from the FIFO buffer or write transmit data to the FIFO buffer by accessing these bits. */
#define R_USB_HS_CFIFO_FIFOPORT_MASK              0xffffffff

/* D0FIFO Register bit definitions */
#define R_USB_HS_D0FIFO_FIFOPORT_SHIFT            (0)  /* FIFO Port Read receive data from the FIFO buffer or write transmit data to the FIFO buffer by accessing these bits. */
#define R_USB_HS_D0FIFO_FIFOPORT_MASK             0xffffffff

/* D1FIFO Register bit definitions */
#define R_USB_HS_D1FIFO_FIFOPORT_SHIFT            (0)  /* FIFO PortRead receive data from the FIFO buffer or write transmit data to the FIFO buffer by accessing these bits. */
#define R_USB_HS_D1FIFO_FIFOPORT_MASK             0xffffffff

/* CFIFOSEL Register bit definitions */
#define R_USB_HS_CFIFOSEL_RCNT                    (1 << 15)  /* Read Count Mode */

#define R_USB_HS_CFIFOSEL_REW                     (1 << 14)  /* Buffer Pointer Rewind */

#define R_USB_HS_CFIFOSEL_MBW_SHIFT               (10)  /* CFIFO Port Access Bit Width */
#define R_USB_HS_CFIFOSEL_MBW_MASK                0xc00
#  define R_USB_HS_CFIFOSEL_MBW_00                        (0 << R_USB_HS_CFIFOSEL_MBW_SHIFT)  /* 8-bit width */
#  define R_USB_HS_CFIFOSEL_MBW_01                        (1 << R_USB_HS_CFIFOSEL_MBW_SHIFT)  /* 16-bit width */
#  define R_USB_HS_CFIFOSEL_MBW_10                        (2 << R_USB_HS_CFIFOSEL_MBW_SHIFT)  /* 32-bit width */
#  define R_USB_HS_CFIFOSEL_MBW_11                        (3 << R_USB_HS_CFIFOSEL_MBW_SHIFT)  /* Setting prohibited */

#define R_USB_HS_CFIFOSEL_BIGEND                  (1 << 8)  /* FIFO Port Endian Control */

#define R_USB_HS_CFIFOSEL_ISEL                    (1 << 5)  /* FIFO Port Access Direction when DCP is Selected */

#define R_USB_HS_CFIFOSEL_CURPIPE_SHIFT           (0)  /* FIFO Port Access Pipe Specification */
#define R_USB_HS_CFIFOSEL_CURPIPE_MASK            0xf
#  define R_USB_HS_CFIFOSEL_CURPIPE_0000                  (0 << R_USB_HS_CFIFOSEL_CURPIPE_SHIFT)  /* DCP */
#  define R_USB_HS_CFIFOSEL_CURPIPE_0001                  (1 << R_USB_HS_CFIFOSEL_CURPIPE_SHIFT)  /* PIPE1 */
#  define R_USB_HS_CFIFOSEL_CURPIPE_0010                  (2 << R_USB_HS_CFIFOSEL_CURPIPE_SHIFT)  /* PIPE2 */
#  define R_USB_HS_CFIFOSEL_CURPIPE_0011                  (3 << R_USB_HS_CFIFOSEL_CURPIPE_SHIFT)  /* PIPE3 */
#  define R_USB_HS_CFIFOSEL_CURPIPE_0100                  (4 << R_USB_HS_CFIFOSEL_CURPIPE_SHIFT)  /* PIPE4 */
#  define R_USB_HS_CFIFOSEL_CURPIPE_0101                  (5 << R_USB_HS_CFIFOSEL_CURPIPE_SHIFT)  /* PIPE5 */
#  define R_USB_HS_CFIFOSEL_CURPIPE_0110                  (6 << R_USB_HS_CFIFOSEL_CURPIPE_SHIFT)  /* PIPE6 */
#  define R_USB_HS_CFIFOSEL_CURPIPE_0111                  (7 << R_USB_HS_CFIFOSEL_CURPIPE_SHIFT)  /* PIPE7 */
#  define R_USB_HS_CFIFOSEL_CURPIPE_1000                  (8 << R_USB_HS_CFIFOSEL_CURPIPE_SHIFT)  /* PIPE8 */
#  define R_USB_HS_CFIFOSEL_CURPIPE_1001                  (9 << R_USB_HS_CFIFOSEL_CURPIPE_SHIFT)  /* PIPE9 */

/* CFIFOCTR Register bit definitions */
#define R_USB_HS_CFIFOCTR_BVAL                    (1 << 15)  /* Buffer Memory Valid Flag */

#define R_USB_HS_CFIFOCTR_BCLR                    (1 << 14)  /* CPU Buffer Clear */

#define R_USB_HS_CFIFOCTR_FRDY                    (1 << 13)  /* FIFO Port ReadyIndicates whether the FIFO port can be accessed. */

#define R_USB_HS_CFIFOCTR_DTLN_SHIFT              (0)  /* Receive Data Length.Indicates the length of the receive data. */
#define R_USB_HS_CFIFOCTR_DTLN_MASK               0xfff

/* D0FIFOSEL Register bit definitions */
#define R_USB_HS_D0FIFOSEL_RCNT                   (1 << 15)  /* Read Count Mode */

#define R_USB_HS_D0FIFOSEL_REW                    (1 << 14)  /* Buffer Pointer Rewind */

#define R_USB_HS_D0FIFOSEL_DCLRM                  (1 << 13)  /* Auto Buffer Memory Clear Mode Accessed after Specified Pipe Data is Read */

#define R_USB_HS_D0FIFOSEL_DREQE                  (1 << 12)  /* UCL_Dx_DREQ Signal Output Enable */

#define R_USB_HS_D0FIFOSEL_MBW_SHIFT              (10)  /* FIFO Port Access Bit Width */
#define R_USB_HS_D0FIFOSEL_MBW_MASK               0xc00
#  define R_USB_HS_D0FIFOSEL_MBW_00                       (0 << R_USB_HS_D0FIFOSEL_MBW_SHIFT)  /* 8-bit width */
#  define R_USB_HS_D0FIFOSEL_MBW_01                       (1 << R_USB_HS_D0FIFOSEL_MBW_SHIFT)  /* 16-bit width */
#  define R_USB_HS_D0FIFOSEL_MBW_10                       (2 << R_USB_HS_D0FIFOSEL_MBW_SHIFT)  /* 32-bit width */
#  define R_USB_HS_D0FIFOSEL_MBW_11                       (3 << R_USB_HS_D0FIFOSEL_MBW_SHIFT)  /* Setting prohibited */

#define R_USB_HS_D0FIFOSEL_BIGEND                 (1 << 8)  /* FIFO Port Endian Control */

#define R_USB_HS_D0FIFOSEL_CURPIPE_SHIFT          (0)  /* FIFO Port Access Pipe Specification */
#define R_USB_HS_D0FIFOSEL_CURPIPE_MASK           0xf
#  define R_USB_HS_D0FIFOSEL_CURPIPE_0000                 (0 << R_USB_HS_D0FIFOSEL_CURPIPE_SHIFT)  /* No pipe specified */
#  define R_USB_HS_D0FIFOSEL_CURPIPE_0001                 (1 << R_USB_HS_D0FIFOSEL_CURPIPE_SHIFT)  /* Pipe1 */
#  define R_USB_HS_D0FIFOSEL_CURPIPE_0010                 (2 << R_USB_HS_D0FIFOSEL_CURPIPE_SHIFT)  /* Pipe 2 */
#  define R_USB_HS_D0FIFOSEL_CURPIPE_0011                 (3 << R_USB_HS_D0FIFOSEL_CURPIPE_SHIFT)  /* Pipe 3 */
#  define R_USB_HS_D0FIFOSEL_CURPIPE_0100                 (4 << R_USB_HS_D0FIFOSEL_CURPIPE_SHIFT)  /* Pipe 4 */
#  define R_USB_HS_D0FIFOSEL_CURPIPE_0101                 (5 << R_USB_HS_D0FIFOSEL_CURPIPE_SHIFT)  /* Pipe 5 */
#  define R_USB_HS_D0FIFOSEL_CURPIPE_0110                 (6 << R_USB_HS_D0FIFOSEL_CURPIPE_SHIFT)  /* Pipe 6 */
#  define R_USB_HS_D0FIFOSEL_CURPIPE_0111                 (7 << R_USB_HS_D0FIFOSEL_CURPIPE_SHIFT)  /* Pipe 7 */
#  define R_USB_HS_D0FIFOSEL_CURPIPE_1000                 (8 << R_USB_HS_D0FIFOSEL_CURPIPE_SHIFT)  /* Pipe 8 */
#  define R_USB_HS_D0FIFOSEL_CURPIPE_1001                 (9 << R_USB_HS_D0FIFOSEL_CURPIPE_SHIFT)  /* Pipe 9 */

/* D0FIFOCTR Register bit definitions */
#define R_USB_HS_D0FIFOCTR_BVAL                   (1 << 15)  /* Buffer Memory Valid Flag */

#define R_USB_HS_D0FIFOCTR_BCLR                   (1 << 14)  /* CPU Buffer Clear */

#define R_USB_HS_D0FIFOCTR_FRDY                   (1 << 13)  /* FIFO Port ReadyIndicates whether the FIFO port can be accessed. */

#define R_USB_HS_D0FIFOCTR_DTLN_SHIFT             (0)  /* Receive Data Length.Indicates the length of the receive data. */
#define R_USB_HS_D0FIFOCTR_DTLN_MASK              0xfff

/* D1FIFOSEL Register bit definitions */
#define R_USB_HS_D1FIFOSEL_RCNT                   (1 << 15)  /* Read Count Mode */

#define R_USB_HS_D1FIFOSEL_REW                    (1 << 14)  /* Buffer Pointer Rewind */

#define R_USB_HS_D1FIFOSEL_DCLRM                  (1 << 13)  /* Auto Buffer Memory Clear Mode Accessed after Specified Pipe Data is Read */

#define R_USB_HS_D1FIFOSEL_DREQE                  (1 << 12)  /* UCL_Dx_DREQ Signal Output Enable */

#define R_USB_HS_D1FIFOSEL_MBW_SHIFT              (10)  /* FIFO Port Access Bit Width */
#define R_USB_HS_D1FIFOSEL_MBW_MASK               0xc00
#  define R_USB_HS_D1FIFOSEL_MBW_00                       (0 << R_USB_HS_D1FIFOSEL_MBW_SHIFT)  /* 8-bit width */
#  define R_USB_HS_D1FIFOSEL_MBW_01                       (1 << R_USB_HS_D1FIFOSEL_MBW_SHIFT)  /* 16-bit width */
#  define R_USB_HS_D1FIFOSEL_MBW_10                       (2 << R_USB_HS_D1FIFOSEL_MBW_SHIFT)  /* 32-bit width */
#  define R_USB_HS_D1FIFOSEL_MBW_11                       (3 << R_USB_HS_D1FIFOSEL_MBW_SHIFT)  /* Setting prohibited */

#define R_USB_HS_D1FIFOSEL_BIGEND                 (1 << 8)  /* FIFO Port Endian Control */

#define R_USB_HS_D1FIFOSEL_CURPIPE_SHIFT          (0)  /* FIFO Port Access Pipe Specification */
#define R_USB_HS_D1FIFOSEL_CURPIPE_MASK           0xf
#  define R_USB_HS_D1FIFOSEL_CURPIPE_0000                 (0 << R_USB_HS_D1FIFOSEL_CURPIPE_SHIFT)  /* No pipe specified */
#  define R_USB_HS_D1FIFOSEL_CURPIPE_0001                 (1 << R_USB_HS_D1FIFOSEL_CURPIPE_SHIFT)  /* Pipe 1 */
#  define R_USB_HS_D1FIFOSEL_CURPIPE_0010                 (2 << R_USB_HS_D1FIFOSEL_CURPIPE_SHIFT)  /* Pipe 2 */
#  define R_USB_HS_D1FIFOSEL_CURPIPE_0011                 (3 << R_USB_HS_D1FIFOSEL_CURPIPE_SHIFT)  /* Pipe 3 */
#  define R_USB_HS_D1FIFOSEL_CURPIPE_0100                 (4 << R_USB_HS_D1FIFOSEL_CURPIPE_SHIFT)  /* Pipe 4 */
#  define R_USB_HS_D1FIFOSEL_CURPIPE_0101                 (5 << R_USB_HS_D1FIFOSEL_CURPIPE_SHIFT)  /* Pipe 5 */
#  define R_USB_HS_D1FIFOSEL_CURPIPE_0110                 (6 << R_USB_HS_D1FIFOSEL_CURPIPE_SHIFT)  /* Pipe 6 */
#  define R_USB_HS_D1FIFOSEL_CURPIPE_0111                 (7 << R_USB_HS_D1FIFOSEL_CURPIPE_SHIFT)  /* Pipe 7 */
#  define R_USB_HS_D1FIFOSEL_CURPIPE_1000                 (8 << R_USB_HS_D1FIFOSEL_CURPIPE_SHIFT)  /* Pipe 8 */
#  define R_USB_HS_D1FIFOSEL_CURPIPE_1001                 (9 << R_USB_HS_D1FIFOSEL_CURPIPE_SHIFT)  /* Pipe 9 */

/* D1FIFOCTR Register bit definitions */
#define R_USB_HS_D1FIFOCTR_BVAL                   (1 << 15)  /* Buffer Memory Valid Flag */

#define R_USB_HS_D1FIFOCTR_BCLR                   (1 << 14)  /* CPU Buffer Clear */

#define R_USB_HS_D1FIFOCTR_FRDY                   (1 << 13)  /* FIFO Port ReadyIndicates whether the FIFO port can be accessed. */

#define R_USB_HS_D1FIFOCTR_DTLN_SHIFT             (0)  /* Receive Data Length.Indicates the length of the receive data. */
#define R_USB_HS_D1FIFOCTR_DTLN_MASK              0xfff

/* INTENB0 Register bit definitions */
#define R_USB_HS_INTENB0_VBSE                     (1 << 15)  /* VBUS Interrupt Enable */

#define R_USB_HS_INTENB0_RSME                     (1 << 14)  /* Resume Interrupt Enable */

#define R_USB_HS_INTENB0_SOFE                     (1 << 13)  /* Frame Number Update Interrupt Enable */

#define R_USB_HS_INTENB0_DVSE                     (1 << 12)  /* Device State Transition Interrupt Enable */

#define R_USB_HS_INTENB0_CTRE                     (1 << 11)  /* Control Transfer Stage Transition Interrupt Enable */

#define R_USB_HS_INTENB0_BEMPE                    (1 << 10)  /* Buffer Empty Interrupt Enable */

#define R_USB_HS_INTENB0_NRDYE                    (1 << 9)  /* Buffer Not Ready Response Interrupt Enable */

#define R_USB_HS_INTENB0_BRDYE                    (1 << 8)  /* Buffer Ready Interrupt Enable */

/* INTENB1 Register bit definitions */
#define R_USB_HS_INTENB1_OVRCRE                   (1 << 15)  /* OVRCRE Interrupt Enable */

#define R_USB_HS_INTENB1_BCHGE                    (1 << 14)  /* USB Bus Change Interrupt Enable */

#define R_USB_HS_INTENB1_DTCHE                    (1 << 12)  /* Disconnection Detection Interrupt Enable */

#define R_USB_HS_INTENB1_ATTCHE                   (1 << 11)  /* Connection Detection Interrupt Enable */

#define R_USB_HS_INTENB1_L1RSMENDE                (1 << 9)  /* L1 Resume End Interrupt Enable */

#define R_USB_HS_INTENB1_LPMENDE                  (1 << 8)  /* LPM Transaction End Interrupt Enable */

#define R_USB_HS_INTENB1_EOFERRE                  (1 << 6)  /* EOF Error Detection Interrupt Enable */

#define R_USB_HS_INTENB1_SIGNE                    (1 << 5)  /* Setup Transaction Error Interrupt Enable */

#define R_USB_HS_INTENB1_SACKE                    (1 << 4)  /* Setup Transaction Normal Response Interrupt Enable */

#define R_USB_HS_INTENB1_PDDETINTE0               (1 << 0)  /* PDDETINT0 Detection Interrupt Enable */

/* BRDYENB Register bit definitions */
#define R_USB_HS_BRDYENB_PIPEBRDYE_SHIFT          (0)  /* BRDY Interrupt Enable for Each Pipe */
#define R_USB_HS_BRDYENB_PIPEBRDYE_MASK           0x3ff
#  define R_USB_HS_BRDYENB_PIPEBRDYE_0                    (0 << R_USB_HS_BRDYENB_PIPEBRDYE_SHIFT)  /* Interrupt output disabled */
#  define R_USB_HS_BRDYENB_PIPEBRDYE_1                    (1 << R_USB_HS_BRDYENB_PIPEBRDYE_SHIFT)  /* Interrupt output enabled */

/* NRDYENB Register bit definitions */
#define R_USB_HS_NRDYENB_PIPENRDYE_SHIFT          (0)  /* NRDY Interrupt Enable for Each Pipe */
#define R_USB_HS_NRDYENB_PIPENRDYE_MASK           0x3ff
#  define R_USB_HS_NRDYENB_PIPENRDYE_0                    (0 << R_USB_HS_NRDYENB_PIPENRDYE_SHIFT)  /* Interrupt output disabled */
#  define R_USB_HS_NRDYENB_PIPENRDYE_1                    (1 << R_USB_HS_NRDYENB_PIPENRDYE_SHIFT)  /* Interrupt output enabled */

/* BEMPENB Register bit definitions */
#define R_USB_HS_BEMPENB_PIPEBEMPE_SHIFT          (0)  /* BEMP Interrupt Enable for Each Pipe */
#define R_USB_HS_BEMPENB_PIPEBEMPE_MASK           0x3ff
#  define R_USB_HS_BEMPENB_PIPEBEMPE_0                    (0 << R_USB_HS_BEMPENB_PIPEBEMPE_SHIFT)  /* Interrupt output disabled */
#  define R_USB_HS_BEMPENB_PIPEBEMPE_1                    (1 << R_USB_HS_BEMPENB_PIPEBEMPE_SHIFT)  /* Interrupt output enabled */

/* SOFCFG Register bit definitions */
#define R_USB_HS_SOFCFG_TRNENSEL                  (1 << 8)  /* Transaction-Enabled Time Select.The transfer efficiency can be improved by setting this bit to 1 if no low-speed device is connected directly or via FS-HUB to the USB port. */

#define R_USB_HS_SOFCFG_BRDYM                     (1 << 6)  /* PIPEBRDY Interrupt Status Clear Timing.This bit can be set only in the initial setting (before communications).The setting cannot be changed once communication starts. */

#define R_USB_HS_SOFCFG_INTL                      (1 << 5)  /* Interrupt Output Sense Select */

#define R_USB_HS_SOFCFG_EDGESTS                   (1 << 4)  /* Interrupt Edge Processing Status Monitor */

/* PHYSET Register bit definitions */
#define R_USB_HS_PHYSET_HSEB                      (1 << 15)  /* CL-Only Mode */

#define R_USB_HS_PHYSET_REPSTART                  (1 << 11)  /* Forcibly Start Terminating Resistance Adjustment */

#define R_USB_HS_PHYSET_REPSEL_SHIFT              (8)  /* Terminating Resistance Adjustment Cycle */
#define R_USB_HS_PHYSET_REPSEL_MASK               0x300
#  define R_USB_HS_PHYSET_REPSEL_00                       (0 << R_USB_HS_PHYSET_REPSEL_SHIFT)  /* No cycle is set. */
#  define R_USB_HS_PHYSET_REPSEL_01                       (1 << R_USB_HS_PHYSET_REPSEL_SHIFT)  /* Adjust terminating resistance at 16-second intervals.  */
#  define R_USB_HS_PHYSET_REPSEL_10                       (2 << R_USB_HS_PHYSET_REPSEL_SHIFT)  /* Adjust terminating resistance at 64-second intervals. */
#  define R_USB_HS_PHYSET_REPSEL_11                       (3 << R_USB_HS_PHYSET_REPSEL_SHIFT)  /* Adjust terminating resistance at 128-second intervals. */

#define R_USB_HS_PHYSET_CLKSEL_SHIFT              (4)  /* Input System Clock Frequency */
#define R_USB_HS_PHYSET_CLKSEL_MASK               0x30
#  define R_USB_HS_PHYSET_CLKSEL_00                       (0 << R_USB_HS_PHYSET_CLKSEL_SHIFT)  /* Setting Prohibited */
#  define R_USB_HS_PHYSET_CLKSEL_01                       (1 << R_USB_HS_PHYSET_CLKSEL_SHIFT)  /* 12 MHz */
#  define R_USB_HS_PHYSET_CLKSEL_10                       (2 << R_USB_HS_PHYSET_CLKSEL_SHIFT)  /* 20 MHz */
#  define R_USB_HS_PHYSET_CLKSEL_11                       (3 << R_USB_HS_PHYSET_CLKSEL_SHIFT)  /* 24 MHz */

#define R_USB_HS_PHYSET_CDPEN                     (1 << 3)  /* Charging Downstream Port Enable */

#define R_USB_HS_PHYSET_PLLRESET                  (1 << 1)  /* PLL Reset Control */

#define R_USB_HS_PHYSET_DIRPD                     (1 << 0)  /* Power-Down Control */

/* INTSTS0 Register bit definitions */
#define R_USB_HS_INTSTS0_VBINT                    (1 << 15)  /* VBUS Interrupt Status */

#define R_USB_HS_INTSTS0_RESM                     (1 << 14)  /* Resume Interrupt Status */

#define R_USB_HS_INTSTS0_SOFR                     (1 << 13)  /* Frame Number Refresh Interrupt Status */

#define R_USB_HS_INTSTS0_DVST                     (1 << 12)  /* Device State Transition Interrupt Status */

#define R_USB_HS_INTSTS0_CTRT                     (1 << 11)  /* Control Transfer Stage Transition Interrupt Status */

#define R_USB_HS_INTSTS0_BEMP                     (1 << 10)  /* Buffer Empty Interrupt Status */

#define R_USB_HS_INTSTS0_NRDY                     (1 << 9)  /* Buffer Not Ready Interrupt Status */

#define R_USB_HS_INTSTS0_BRDY                     (1 << 8)  /* Buffer Ready Interrupt Status */

#define R_USB_HS_INTSTS0_VBSTS                    (1 << 7)  /* VBUS Input Status */

#define R_USB_HS_INTSTS0_DVSQ_SHIFT               (4)  /* Device State */
#define R_USB_HS_INTSTS0_DVSQ_MASK                0x70
#  define R_USB_HS_INTSTS0_DVSQ_000                       (0 << R_USB_HS_INTSTS0_DVSQ_SHIFT)  /* Powered state */
#  define R_USB_HS_INTSTS0_DVSQ_001                       (1 << R_USB_HS_INTSTS0_DVSQ_SHIFT)  /* Default state */
#  define R_USB_HS_INTSTS0_DVSQ_010                       (2 << R_USB_HS_INTSTS0_DVSQ_SHIFT)  /* Address state */
#  define R_USB_HS_INTSTS0_DVSQ_011                       (3 << R_USB_HS_INTSTS0_DVSQ_SHIFT)  /* Configured state */

#define R_USB_HS_INTSTS0_VALID                    (1 << 3)  /* USB Request Reception */

#define R_USB_HS_INTSTS0_CTSQ_SHIFT               (0)  /* Control Transfer Stage */
#define R_USB_HS_INTSTS0_CTSQ_MASK                0x7
#  define R_USB_HS_INTSTS0_CTSQ_000                       (0 << R_USB_HS_INTSTS0_CTSQ_SHIFT)  /* Idle or setup stage */
#  define R_USB_HS_INTSTS0_CTSQ_001                       (1 << R_USB_HS_INTSTS0_CTSQ_SHIFT)  /* Control read data stage */
#  define R_USB_HS_INTSTS0_CTSQ_010                       (2 << R_USB_HS_INTSTS0_CTSQ_SHIFT)  /* Control read status stage */
#  define R_USB_HS_INTSTS0_CTSQ_011                       (3 << R_USB_HS_INTSTS0_CTSQ_SHIFT)  /* Control write data stage */
#  define R_USB_HS_INTSTS0_CTSQ_100                       (4 << R_USB_HS_INTSTS0_CTSQ_SHIFT)  /* Control write status stage */
#  define R_USB_HS_INTSTS0_CTSQ_101                       (5 << R_USB_HS_INTSTS0_CTSQ_SHIFT)  /* Control write (no data) status stage */
#  define R_USB_HS_INTSTS0_CTSQ_110                       (6 << R_USB_HS_INTSTS0_CTSQ_SHIFT)  /* Control transfer sequence error */
#  define R_USB_HS_INTSTS0_CTSQ_111                       (7 << R_USB_HS_INTSTS0_CTSQ_SHIFT)  /* Setting prohibited */

/* INTSTS1 Register bit definitions */
#define R_USB_HS_INTSTS1_OVRCR                    (1 << 15)  /* Overcurrent Interrupt Status */

#define R_USB_HS_INTSTS1_BCHG                     (1 << 14)  /* USB Bus Change Interrupt Status */

#define R_USB_HS_INTSTS1_DTCH                     (1 << 12)  /* USB Disconnection Detection Interrupt Status */

#define R_USB_HS_INTSTS1_ATTCH                    (1 << 11)  /* USB Connection Detection Interrupt Status */

#define R_USB_HS_INTSTS1_L1RSMEND                 (1 << 9)  /* L1 Resume End Interrupt Status */

#define R_USB_HS_INTSTS1_LPMEND                   (1 << 8)  /* LPM Transaction End Interrupt Status */

#define R_USB_HS_INTSTS1_EOFERR                   (1 << 6)  /* EOF Error Detection Interrupt Status */

#define R_USB_HS_INTSTS1_SIGN                     (1 << 5)  /* Setup Transaction Error Interrupt Status */

#define R_USB_HS_INTSTS1_SACK                     (1 << 4)  /* Setup Transaction Normal Response Interrupt Status */

#define R_USB_HS_INTSTS1_PDDETINT0                (1 << 0)  /* PDDET Detection Interrupt Status */

/* BRDYSTS Register bit definitions */
#define R_USB_HS_BRDYSTS_PIPEBRDY_SHIFT           (0)  /* BRDY Interrupt Status for Each Pipe */
#define R_USB_HS_BRDYSTS_PIPEBRDY_MASK            0x3ff
#  define R_USB_HS_BRDYSTS_PIPEBRDY_0                     (0 << R_USB_HS_BRDYSTS_PIPEBRDY_SHIFT)  /* Interrupts are not generated */
#  define R_USB_HS_BRDYSTS_PIPEBRDY_1                     (1 << R_USB_HS_BRDYSTS_PIPEBRDY_SHIFT)  /* Interrupts are generated */

/* NRDYSTS Register bit definitions */
#define R_USB_HS_NRDYSTS_PIPENRDY_SHIFT           (0)  /* NRDY Interrupt Status for Each Pipe */
#define R_USB_HS_NRDYSTS_PIPENRDY_MASK            0x3ff
#  define R_USB_HS_NRDYSTS_PIPENRDY_0                     (0 << R_USB_HS_NRDYSTS_PIPENRDY_SHIFT)  /* Interrupts are not generated */
#  define R_USB_HS_NRDYSTS_PIPENRDY_1                     (1 << R_USB_HS_NRDYSTS_PIPENRDY_SHIFT)  /* Interrupts are generated */

/* BEMPSTS Register bit definitions */
#define R_USB_HS_BEMPSTS_PIPEBEMP_SHIFT           (0)  /* BEMP Interrupt Status for Each Pipe */
#define R_USB_HS_BEMPSTS_PIPEBEMP_MASK            0x3ff
#  define R_USB_HS_BEMPSTS_PIPEBEMP_0                     (0 << R_USB_HS_BEMPSTS_PIPEBEMP_SHIFT)  /* Interrupts are not generated */
#  define R_USB_HS_BEMPSTS_PIPEBEMP_1                     (1 << R_USB_HS_BEMPSTS_PIPEBEMP_SHIFT)  /* Interrupts are generated */

/* FRMNUM Register bit definitions */
#define R_USB_HS_FRMNUM_OVRN                      (1 << 15)  /* Overrun/Underrun Detection Status */

#define R_USB_HS_FRMNUM_CRCE                      (1 << 14)  /* CRC Error Detection Status */

#define R_USB_HS_FRMNUM_FRNM_SHIFT                (0)  /* Frame Number.Indicate the latest frame number. */
#define R_USB_HS_FRMNUM_FRNM_MASK                 0x7ff

/* UFRMNUM Register bit definitions */
#define R_USB_HS_UFRMNUM_DVCHG                    (1 << 15)  /* Device State Change */

#define R_USB_HS_UFRMNUM_UFRNM_SHIFT              (0)  /* MicroframeIndicate the microframe number. */
#define R_USB_HS_UFRMNUM_UFRNM_MASK               0x7

/* USBADDR Register bit definitions */
#define R_USB_HS_USBADDR_STSRECOV0_SHIFT          (8)  /* Status Recovery */
#define R_USB_HS_USBADDR_STSRECOV0_MASK           0x700
#  define R_USB_HS_USBADDR_STSRECOV0_001                  (1 << R_USB_HS_USBADDR_STSRECOV0_SHIFT)  /* Return to the full-speed state(bits DVSTCTR0.RHST[2:0] = 010b), bits INTSTS0.DVSQ[2:0] = 001b (Default state)(function controller selected) */
#  define R_USB_HS_USBADDR_STSRECOV0_010                  (2 << R_USB_HS_USBADDR_STSRECOV0_SHIFT)  /* Return to the full-speed state (bits DVSTCTR0.RHST[2:0] = 010b), bits INTSTS0.DVSQ[2:0] = 010b (Address state)(function controller selected)/ Return to the low-speed state (bitsDVSTCTR0.RHST[2:0] = 001b)(host controller is selected) */
#  define R_USB_HS_USBADDR_STSRECOV0_011                  (3 << R_USB_HS_USBADDR_STSRECOV0_SHIFT)  /* Return to the full-speed state (bits DVSTCTR0.RHST[2:0] = 010b), bits INTSTS0.DVSQ[2:0] = 011b (Configured state)(function controller selected) */
#  define R_USB_HS_USBADDR_STSRECOV0_100                  (4 << R_USB_HS_USBADDR_STSRECOV0_SHIFT)  /* Return to the full-speed state (bits DVSTCTR0.RHST[2:0] = 010b)(host controller selected) */
#  define R_USB_HS_USBADDR_STSRECOV0_101                  (5 << R_USB_HS_USBADDR_STSRECOV0_SHIFT)  /* Return to the high-speed state (bits DVSTCTR0.RHST[2:0] = 011b), bits INTSTS0.DVSQ[2:0] = 001b (Default state)(function controller selected) */
#  define R_USB_HS_USBADDR_STSRECOV0_110                  (6 << R_USB_HS_USBADDR_STSRECOV0_SHIFT)  /* Return to the high-speed state (bits DVSTCTR0.RHST[2:0] = 011b), bits INTSTS0.DVSQ[2:0] = 010b (Address state)(function controller selected)/ Return to the high-speed state (bits DVSTCTR0.RHST[2:0] = 011b)(host controller selected) */
#  define R_USB_HS_USBADDR_STSRECOV0_111                  (7 << R_USB_HS_USBADDR_STSRECOV0_SHIFT)  /* Return to the high-speed state (bits DVSTCTR0.RHST[2:0] = 011b), bits INTSTS0.DVSQ[2:0] = 011b (Configured state)(function controller selected) */

/* USBREQ Register bit definitions */
#define R_USB_HS_USBREQ_BREQUEST_SHIFT            (8)  /* USB request bRequest value     Finction controller selected : read-only     Host controller selected : read-write */
#define R_USB_HS_USBREQ_BREQUEST_MASK             0xff00

#define R_USB_HS_USBREQ_BMREQUESTTYPE_SHIFT       (0)  /* USB request bmRequestType value     Finction controller selected : read-only     Host controller selected : read-write */
#define R_USB_HS_USBREQ_BMREQUESTTYPE_MASK        0xff

/* USBVAL Register bit definitions */
#define R_USB_HS_USBVAL_WVALUE_SHIFT              (0)  /* Value of USB request wValue     Finction controller selected : read-only     Host controller selected : read-write */
#define R_USB_HS_USBVAL_WVALUE_MASK               0xffff

/* USBINDX Register bit definitions */
#define R_USB_HS_USBINDX_WINDEX_SHIFT             (0)  /* Value of USB request wIndex     Finction controller selected : read-only     Host controller selected : read-write */
#define R_USB_HS_USBINDX_WINDEX_MASK              0xffff

/* USBLENG Register bit definitions */
#define R_USB_HS_USBLENG_WLENGTH_SHIFT            (0)  /* Value of USB request wLength     Finction controller selected : read-only     Host controller selected : read-write */
#define R_USB_HS_USBLENG_WLENGTH_MASK             0xffff

/* DCPCFG Register bit definitions */
#define R_USB_HS_DCPCFG_CNTMD                     (1 << 8)  /* Continuous Transfer Mode */

#define R_USB_HS_DCPCFG_SHTNAK                    (1 << 7)  /* Pipe Blocking on End of Transfer */

#define R_USB_HS_DCPCFG_DIR                       (1 << 4)  /* Transfer Direction */

/* DCPMAXP Register bit definitions */
#define R_USB_HS_DCPMAXP_DEVSEL_SHIFT             (12)  /* Device SelectThese bits specify the address of the destination function device for control transfer when the host controller function is selected. */
#define R_USB_HS_DCPMAXP_DEVSEL_MASK              0xf000
#  define R_USB_HS_DCPMAXP_DEVSEL_0000                    (0 << R_USB_HS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0000 */
#  define R_USB_HS_DCPMAXP_DEVSEL_0001                    (1 << R_USB_HS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0001 */
#  define R_USB_HS_DCPMAXP_DEVSEL_0010                    (2 << R_USB_HS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0010 */
#  define R_USB_HS_DCPMAXP_DEVSEL_0011                    (3 << R_USB_HS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0011 */
#  define R_USB_HS_DCPMAXP_DEVSEL_0100                    (4 << R_USB_HS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0100 */
#  define R_USB_HS_DCPMAXP_DEVSEL_0101                    (5 << R_USB_HS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0101 */

#define R_USB_HS_DCPMAXP_MXPS_SHIFT               (0)  /* Maximum Packet SizeThese bits specify the maximum data payload (maximum packet size) for the DCP. */
#define R_USB_HS_DCPMAXP_MXPS_MASK                0x7f

/* DCPCTR Register bit definitions */
#define R_USB_HS_DCPCTR_BSTS                      (1 << 15)  /* Buffer Status */

#define R_USB_HS_DCPCTR_SUREQ                     (1 << 14)  /* SETUP Token Transmission */

#define R_USB_HS_DCPCTR_CSCLR                     (1 << 13)  /* Split Transaction CSPLIT Status Clear */

#define R_USB_HS_DCPCTR_CSSTS                     (1 << 12)  /* Split Transaction COMPLETE SPLIT(CSPLIT) Status */

#define R_USB_HS_DCPCTR_SUREQCLR                  (1 << 11)  /* SUREQ Bit Clear */

#define R_USB_HS_DCPCTR_SQCLR                     (1 << 8)  /* Toggle Bit Clear */

#define R_USB_HS_DCPCTR_SQSET                     (1 << 7)  /* Toggle Bit Set */

#define R_USB_HS_DCPCTR_SQMON                     (1 << 6)  /* Sequence Toggle Bit Monitor */

#define R_USB_HS_DCPCTR_PBUSY                     (1 << 5)  /* Pipe Busy */

#define R_USB_HS_DCPCTR_PINGE                     (1 << 4)  /* PING Token Issue Enable */

#define R_USB_HS_DCPCTR_CCPL                      (1 << 2)  /* Control Transfer End Enable */

#define R_USB_HS_DCPCTR_PID_SHIFT                 (0)  /* Response PID */
#define R_USB_HS_DCPCTR_PID_MASK                  0x3
#  define R_USB_HS_DCPCTR_PID_00                          (0 << R_USB_HS_DCPCTR_PID_SHIFT)  /* NAK response */
#  define R_USB_HS_DCPCTR_PID_01                          (1 << R_USB_HS_DCPCTR_PID_SHIFT)  /* BUF response (depending on buffer state) */
#  define R_USB_HS_DCPCTR_PID_10                          (2 << R_USB_HS_DCPCTR_PID_SHIFT)  /* STALL response */
#  define R_USB_HS_DCPCTR_PID_11                          (3 << R_USB_HS_DCPCTR_PID_SHIFT)  /* STALL response */

/* PIPECFG Register bit definitions */
#define R_USB_HS_PIPECFG_TYPE_SHIFT               (14)  /* Transfer Type */
#define R_USB_HS_PIPECFG_TYPE_MASK                0xc000
#  define R_USB_HS_PIPECFG_TYPE_00                        (0 << R_USB_HS_PIPECFG_TYPE_SHIFT)  /* Pipe not used */
#  define R_USB_HS_PIPECFG_TYPE_01                        (1 << R_USB_HS_PIPECFG_TYPE_SHIFT)  /* Bulk transfer */
#  define R_USB_HS_PIPECFG_TYPE_10                        (2 << R_USB_HS_PIPECFG_TYPE_SHIFT)  /* Interrupt transfer */
#  define R_USB_HS_PIPECFG_TYPE_11                        (3 << R_USB_HS_PIPECFG_TYPE_SHIFT)  /* Isochronous transfer */

#define R_USB_HS_PIPECFG_BFRE                     (1 << 10)  /* BRDY Interrupt Operation Specification */

#define R_USB_HS_PIPECFG_DBLB                     (1 << 9)  /* Double Buffer Mode */

#define R_USB_HS_PIPECFG_CNTMD                    (1 << 8)  /* Continuous Transfer Mode */

#define R_USB_HS_PIPECFG_SHTNAK                   (1 << 7)  /* Pipe Disabled at End of Transfer */

#define R_USB_HS_PIPECFG_DIR                      (1 << 4)  /* Transfer Direction */

#define R_USB_HS_PIPECFG_EPNUM_SHIFT              (0)  /* Endpoint Number */
#define R_USB_HS_PIPECFG_EPNUM_MASK               0xf
#  define R_USB_HS_PIPECFG_EPNUM_000                      (0 << R_USB_HS_PIPECFG_EPNUM_SHIFT)  /* the selected pipe is not used */

/* PIPEBUF Register bit definitions */
#define R_USB_HS_PIPEBUF_BUFSIZE_SHIFT            (10)  /* Buffer Size    00h: 64 bytes    01h: 128 bytes      :    1Fh: 2 Kbytes */
#define R_USB_HS_PIPEBUF_BUFSIZE_MASK             0x7c00

#define R_USB_HS_PIPEBUF_BUFNMB_SHIFT             (0)  /* Buffer NumberThese bits specify the FIFO buffer number of the selected pipe (04h to 87h). */
#define R_USB_HS_PIPEBUF_BUFNMB_MASK              0xff

/* PIPEMAXP Register bit definitions */
#define R_USB_HS_PIPEMAXP_DEVSEL_SHIFT            (12)  /* Device SelectThese bits specify the address of the peripheral device when the host controller function is selected. */
#define R_USB_HS_PIPEMAXP_DEVSEL_MASK             0xf000

#define R_USB_HS_PIPEMAXP_MXPS_SHIFT              (0)  /* Maximum Packet SizeThese bits specify the maximum data payload (maximum packet size) for the selected pipe.A size of 1h to 40h bytes can be set for PIPE6 to PIPE9. */
#define R_USB_HS_PIPEMAXP_MXPS_MASK               0x7ff

/* PIPEPERI Register bit definitions */
#define R_USB_HS_PIPEPERI_IFIS                    (1 << 12)  /* Isochronous IN Buffer Flush */

#define R_USB_HS_PIPEPERI_IITV_SHIFT              (0)  /* Interval Error Detection IntervalThese bits specify the transfer interval timing for the selected pipe as n-th power of 2 of the frame timing. */
#define R_USB_HS_PIPEPERI_IITV_MASK               0x7

/* PIPE_CTR Register bit definitions */
#define R_USB_HS_PIPE_CTR_BSTS                    (1 << 15)  /* Buffer StatusThis bit indicates the FIFO buffer status for the relevant pipe. */

#define R_USB_HS_PIPE_CTR_INBUFM                  (1 << 14)  /* Transmit Buffer MonitorThis bit indicates the FIFO buffer status for the relevant pipe in the transmitting direction. */

#define R_USB_HS_PIPE_CTR_CSCLR                   (1 << 13)  /* CSPLIT Status ClearSet this bit to 1 when clearing the CSSTS bit of the relevant pipe */

#define R_USB_HS_PIPE_CTR_CSSTS                   (1 << 12)  /* CSSTS StatusThis bit indicates the CSPLIT status of Split Transaction of the relevant pipe */

#define R_USB_HS_PIPE_CTR_ATREPM                  (1 << 10)  /* Auto Response ModeThis bit enables or disables auto response mode for the relevant pipe. */

#define R_USB_HS_PIPE_CTR_ACLRM                   (1 << 9)  /* Auto Buffer Clear ModeThis bit enables or disables auto buffer clear mode for the relevant pipe */

#define R_USB_HS_PIPE_CTR_SQCLR                   (1 << 8)  /* Toggle Bit ClearThis bit is set to 1 when the expected value of the sequence toggle bit for the next transaction of the relevant pipe is cleared to DATA0 */

#define R_USB_HS_PIPE_CTR_SQSET                   (1 << 7)  /* Toggle Bit SetThis bit is set to 1 when the expected value of the sequence toggle bit for the next transaction of the relevant pipe is set for DATA1 */

#define R_USB_HS_PIPE_CTR_SQMON                   (1 << 6)  /* Toggle Bit ConfirmationThis bit indicates the expected value of the sequence toggle bit for the next transaction of the relevant pipe */

#define R_USB_HS_PIPE_CTR_PBUSY                   (1 << 5)  /* Pipe BusyThis bit indicates whether the relevant pipe is being used for the USB bus */

#define R_USB_HS_PIPE_CTR_PID_SHIFT               (0)  /* Response PIDThese bits specify the response type for the next transaction of the relevant pipe. */
#define R_USB_HS_PIPE_CTR_PID_MASK                0x3
#  define R_USB_HS_PIPE_CTR_PID_00                        (0 << R_USB_HS_PIPE_CTR_PID_SHIFT)  /* NAK response */
#  define R_USB_HS_PIPE_CTR_PID_01                        (1 << R_USB_HS_PIPE_CTR_PID_SHIFT)  /* BUF response (depending on buffer state) */
#  define R_USB_HS_PIPE_CTR_PID_10                        (2 << R_USB_HS_PIPE_CTR_PID_SHIFT)  /* STALL response */
#  define R_USB_HS_PIPE_CTR_PID_11                        (3 << R_USB_HS_PIPE_CTR_PID_SHIFT)  /* STALL response */

/* DEVADD Register bit definitions */
#define R_USB_HS_DEVADD_UPPHUB_SHIFT              (11)  /* Communication Target Connecting Hub Register */
#define R_USB_HS_DEVADD_UPPHUB_MASK               0x7800
#  define R_USB_HS_DEVADD_UPPHUB_0000                     (0 << R_USB_HS_DEVADD_UPPHUB_SHIFT)  /* Directly connected to the port of the USBHS. */

#define R_USB_HS_DEVADD_HUBPORT_SHIFT             (8)  /* Communication Target Connecting Hub Port */
#define R_USB_HS_DEVADD_HUBPORT_MASK              0x700
#  define R_USB_HS_DEVADD_HUBPORT_000                     (0 << R_USB_HS_DEVADD_HUBPORT_SHIFT)  /* Directly connected to the port of the USBHS.  */

#define R_USB_HS_DEVADD_USBSPD_SHIFT              (6)  /* Transfer Speed of Communication Target Device */
#define R_USB_HS_DEVADD_USBSPD_MASK               0xc0
#  define R_USB_HS_DEVADD_USBSPD_00                       (0 << R_USB_HS_DEVADD_USBSPD_SHIFT)  /* DEVADDx is not used. */
#  define R_USB_HS_DEVADD_USBSPD_01                       (1 << R_USB_HS_DEVADD_USBSPD_SHIFT)  /* Low speed */
#  define R_USB_HS_DEVADD_USBSPD_10                       (2 << R_USB_HS_DEVADD_USBSPD_SHIFT)  /* Full speed */
#  define R_USB_HS_DEVADD_USBSPD_11                       (3 << R_USB_HS_DEVADD_USBSPD_SHIFT)  /* High speed */

/* LPCTRL Register bit definitions */
#define R_USB_HS_LPCTRL_HWUPM                     (1 << 7)  /* Resume Return Mode Setting */

/* LPSTS Register bit definitions */
#define R_USB_HS_LPSTS_SUSPENDM                   (1 << 14)  /* UTMI SuspendM Control */

/* BCCTRL Register bit definitions */
#define R_USB_HS_BCCTRL_PDDETSTS                  (1 << 9)  /* PDDET Status */

#define R_USB_HS_BCCTRL_CHGDETSTS                 (1 << 8)  /* CHGDET Status */

#define R_USB_HS_BCCTRL_DCPMODE                   (1 << 5)  /* DCP Mode Control */

#define R_USB_HS_BCCTRL_VDMSRCE                   (1 << 4)  /* VDMSRC Control */

#define R_USB_HS_BCCTRL_IDPSINKE                  (1 << 3)  /* IDPSINK Control */

#define R_USB_HS_BCCTRL_VDPSRCE                   (1 << 2)  /* VDPSRC Control */

#define R_USB_HS_BCCTRL_IDMSINKE                  (1 << 1)  /* IDMSINK Control */

#define R_USB_HS_BCCTRL_IDPSRCE                   (1 << 0)  /* IDPSRC Control */

/* PL1CTRL1 Register bit definitions */
#define R_USB_HS_PL1CTRL1_L1EXTMD                 (1 << 14)  /* PHY Control Mode at L1 Return */

#define R_USB_HS_PL1CTRL1_HIRDTHR_SHIFT           (8)  /* L1 Response Negotiation Threshold ValueHIRD threshold value used for L1NEGOMD.The format is the same as the HIRD field in HL1CTRL. */
#define R_USB_HS_PL1CTRL1_HIRDTHR_MASK            0xf00

#define R_USB_HS_PL1CTRL1_DVSQ_SHIFT              (4)  /* DVSQ Extension.DVSQ[3] is Mirror of DVSQ[2:0] in INTSTS0.Indicates the L1 state together with the device state bits DVSQ[2:0]. */
#define R_USB_HS_PL1CTRL1_DVSQ_MASK               0xf0
#  define R_USB_HS_PL1CTRL1_DVSQ_0000                     (0 << R_USB_HS_PL1CTRL1_DVSQ_SHIFT)  /* Powered state */
#  define R_USB_HS_PL1CTRL1_DVSQ_0001                     (1 << R_USB_HS_PL1CTRL1_DVSQ_SHIFT)  /* Default state */
#  define R_USB_HS_PL1CTRL1_DVSQ_0010                     (2 << R_USB_HS_PL1CTRL1_DVSQ_SHIFT)  /* Address state */
#  define R_USB_HS_PL1CTRL1_DVSQ_0011                     (3 << R_USB_HS_PL1CTRL1_DVSQ_SHIFT)  /* Configured state */
#  define R_USB_HS_PL1CTRL1_DVSQ_0100                     (4 << R_USB_HS_PL1CTRL1_DVSQ_SHIFT)  /* Suspended state */
#  define R_USB_HS_PL1CTRL1_DVSQ_0101                     (5 << R_USB_HS_PL1CTRL1_DVSQ_SHIFT)  /* Suspended state */
#  define R_USB_HS_PL1CTRL1_DVSQ_0110                     (6 << R_USB_HS_PL1CTRL1_DVSQ_SHIFT)  /* Suspended state */
#  define R_USB_HS_PL1CTRL1_DVSQ_0111                     (7 << R_USB_HS_PL1CTRL1_DVSQ_SHIFT)  /* Suspended state */
#  define R_USB_HS_PL1CTRL1_DVSQ_1000                     (8 << R_USB_HS_PL1CTRL1_DVSQ_SHIFT)  /* L1 state */
#  define R_USB_HS_PL1CTRL1_DVSQ_1001                     (9 << R_USB_HS_PL1CTRL1_DVSQ_SHIFT)  /* L1 state */
#  define R_USB_HS_PL1CTRL1_DVSQ_1010                     (10 << R_USB_HS_PL1CTRL1_DVSQ_SHIFT)  /* L1 state */
#  define R_USB_HS_PL1CTRL1_DVSQ_1011                     (11 << R_USB_HS_PL1CTRL1_DVSQ_SHIFT)  /* L1 state */

#define R_USB_HS_PL1CTRL1_L1NEGOMD                (1 << 3)  /* L1 Response Negotiation Control.NOTE: This bit is valid only when the L1RESPMD[1:0] value is 2'b11. */

#define R_USB_HS_PL1CTRL1_L1RESPMD_SHIFT          (1)  /* L1 Response Mode */
#define R_USB_HS_PL1CTRL1_L1RESPMD_MASK           0x6
#  define R_USB_HS_PL1CTRL1_L1RESPMD_00                   (0 << R_USB_HS_PL1CTRL1_L1RESPMD_SHIFT)  /* NYET */
#  define R_USB_HS_PL1CTRL1_L1RESPMD_01                   (1 << R_USB_HS_PL1CTRL1_L1RESPMD_SHIFT)  /* ACK */
#  define R_USB_HS_PL1CTRL1_L1RESPMD_10                   (2 << R_USB_HS_PL1CTRL1_L1RESPMD_SHIFT)  /* STALL */
#  define R_USB_HS_PL1CTRL1_L1RESPMD_11                   (3 << R_USB_HS_PL1CTRL1_L1RESPMD_SHIFT)  /* According to the L1NEGOMD bit */

#define R_USB_HS_PL1CTRL1_L1RESPEN                (1 << 0)  /* L1 Response Enable */

/* PL1CTRL2 Register bit definitions */
#define R_USB_HS_PL1CTRL2_RWEMON                  (1 << 12)  /* RWE Value Monitor */

#define R_USB_HS_PL1CTRL2_HIRDMON_SHIFT           (8)  /* HIRD Value Monitor */
#define R_USB_HS_PL1CTRL2_HIRDMON_MASK            0xf00
#  define R_USB_HS_PL1CTRL2_HIRDMON_0                     (0 << R_USB_HS_PL1CTRL2_HIRDMON_SHIFT)  /* The HIRD field value of the LPM token received last is reflected. */
#  define R_USB_HS_PL1CTRL2_HIRDMON_1                     (1 << R_USB_HS_PL1CTRL2_HIRDMON_SHIFT)  /* The HIRD field value of the LPM token received last is reflected. */

/* HL1CTRL1 Register bit definitions */
#define R_USB_HS_HL1CTRL1_L1STATUS_SHIFT          (1)  /* L1 Request Completion Status */
#define R_USB_HS_HL1CTRL1_L1STATUS_MASK           0x6
#  define R_USB_HS_HL1CTRL1_L1STATUS_00                   (0 << R_USB_HS_HL1CTRL1_L1STATUS_SHIFT)  /* ACK received */
#  define R_USB_HS_HL1CTRL1_L1STATUS_01                   (1 << R_USB_HS_HL1CTRL1_L1STATUS_SHIFT)  /* NYET received */
#  define R_USB_HS_HL1CTRL1_L1STATUS_10                   (2 << R_USB_HS_HL1CTRL1_L1STATUS_SHIFT)  /* STALL received */
#  define R_USB_HS_HL1CTRL1_L1STATUS_11                   (3 << R_USB_HS_HL1CTRL1_L1STATUS_SHIFT)  /* Transaction error */

#define R_USB_HS_HL1CTRL1_L1REQ                   (1 << 0)  /* L1 Transition Request */

/* HL1CTRL2 Register bit definitions */
#define R_USB_HS_HL1CTRL2_BESL                    (1 << 15)  /* BESL & Alternate HIRDThis bit selects the K-State drive period at the time of L1 Resume. */

#define R_USB_HS_HL1CTRL2_L1RWE                   (1 << 12)  /* LPM Token L1 RemoteWake EnableThese bits specify the value to be set in the RWE field of LPM token. */

#define R_USB_HS_HL1CTRL2_HIRD_SHIFT              (8)  /* LPM Token HIRD */
#define R_USB_HS_HL1CTRL2_HIRD_MASK               0xf00
#  define R_USB_HS_HL1CTRL2_HIRD_0000                     (0 << R_USB_HS_HL1CTRL2_HIRD_SHIFT)  /* 50 us(Setting prohibited(BESL = 0)) / 75 us(BESL = 1) */
#  define R_USB_HS_HL1CTRL2_HIRD_0001                     (1 << R_USB_HS_HL1CTRL2_HIRD_SHIFT)  /* 125 us(BESL = 0) / 100 us(BESL = 1) */
#  define R_USB_HS_HL1CTRL2_HIRD_0010                     (2 << R_USB_HS_HL1CTRL2_HIRD_SHIFT)  /* 200 us(BESL = 0) / 150 us(BESL = 1) */
#  define R_USB_HS_HL1CTRL2_HIRD_0011                     (3 << R_USB_HS_HL1CTRL2_HIRD_SHIFT)  /* 275 us(BESL = 0) / 250 us(BESL = 1) */
#  define R_USB_HS_HL1CTRL2_HIRD_0100                     (4 << R_USB_HS_HL1CTRL2_HIRD_SHIFT)  /* 350 us(BESL = 0) / 350 us(BESL = 1) */
#  define R_USB_HS_HL1CTRL2_HIRD_0101                     (5 << R_USB_HS_HL1CTRL2_HIRD_SHIFT)  /* 425 us(BESL = 0) / 450 us(BESL = 1) */
#  define R_USB_HS_HL1CTRL2_HIRD_0110                     (6 << R_USB_HS_HL1CTRL2_HIRD_SHIFT)  /* 500 us(BESL = 0) / 950 us(BESL = 1) */
#  define R_USB_HS_HL1CTRL2_HIRD_0111                     (7 << R_USB_HS_HL1CTRL2_HIRD_SHIFT)  /* 575 us(BESL = 0) / 1950 us(BESL = 1) */
#  define R_USB_HS_HL1CTRL2_HIRD_1000                     (8 << R_USB_HS_HL1CTRL2_HIRD_SHIFT)  /* 650 us(BESL = 0) / 2950 us(BESL = 1) */
#  define R_USB_HS_HL1CTRL2_HIRD_1001                     (9 << R_USB_HS_HL1CTRL2_HIRD_SHIFT)  /* 725 us(BESL = 0) / 3950 us(BESL = 1) */
#  define R_USB_HS_HL1CTRL2_HIRD_1010                     (10 << R_USB_HS_HL1CTRL2_HIRD_SHIFT)  /* 800 us(BESL = 0) / 4950 us(BESL = 1) */
#  define R_USB_HS_HL1CTRL2_HIRD_1011                     (11 << R_USB_HS_HL1CTRL2_HIRD_SHIFT)  /* 875 us(BESL = 0) / 5950 us(BESL = 1) */
#  define R_USB_HS_HL1CTRL2_HIRD_1100                     (12 << R_USB_HS_HL1CTRL2_HIRD_SHIFT)  /* 950 us(BESL = 0) / 6950 us(BESL = 1) */
#  define R_USB_HS_HL1CTRL2_HIRD_1101                     (13 << R_USB_HS_HL1CTRL2_HIRD_SHIFT)  /* 1025 us(Setting prohibited(BESL = 0)) / 7950 us(BESL = 1) */
#  define R_USB_HS_HL1CTRL2_HIRD_1110                     (14 << R_USB_HS_HL1CTRL2_HIRD_SHIFT)  /* 1100 us(Setting prohibited(BESL = 0)) / 8950 us(BESL = 1) */
#  define R_USB_HS_HL1CTRL2_HIRD_1111                     (15 << R_USB_HS_HL1CTRL2_HIRD_SHIFT)  /* 1175 us(Setting prohibited(BESL = 0)) / 9950 us(BESL = 1) */

#define R_USB_HS_HL1CTRL2_L1ADDR_SHIFT            (0)  /* LPM Token DeviceAddressThese bits specify the value to be set in the ADDR field of LPM token. */
#define R_USB_HS_HL1CTRL2_L1ADDR_MASK             0xf

/* PHYTRIM1 Register bit definitions */
#define R_USB_HS_PHYTRIM1_IMPOFFSET_SHIFT         (12)  /* terminating resistance offset value setting.Offset value for adjusting the terminating resistance. */
#define R_USB_HS_PHYTRIM1_IMPOFFSET_MASK          0x7000

#define R_USB_HS_PHYTRIM1_HSIUP_SHIFT             (8)  /* HS Output Level Setting */
#define R_USB_HS_PHYTRIM1_HSIUP_MASK              0xf00

#define R_USB_HS_PHYTRIM1_PCOMPENB                (1 << 7)  /* PVDD Start-up Detection */

#define R_USB_HS_PHYTRIM1_DFALL_SHIFT             (2)  /* FS/LS Falling-Edge Output Waveform Adjustment Function */
#define R_USB_HS_PHYTRIM1_DFALL_MASK              0xc

#define R_USB_HS_PHYTRIM1_DRISE_SHIFT             (0)  /* FS/LS Rising-Edge Output Waveform Adjustment Function */
#define R_USB_HS_PHYTRIM1_DRISE_MASK              0x3

/* PHYTRIM2 Register bit definitions */
#define R_USB_HS_PHYTRIM2_DIS_SHIFT               (12)  /* Disconnect Detection Level */
#define R_USB_HS_PHYTRIM2_DIS_MASK                0x7000

#define R_USB_HS_PHYTRIM2_PDR_SHIFT               (8)  /* HS Output Adjustment Function */
#define R_USB_HS_PHYTRIM2_PDR_MASK                0x300

#define R_USB_HS_PHYTRIM2_HSRXENMO                (1 << 7)  /* HS Receive Enable Control Mode */

#define R_USB_HS_PHYTRIM2_SQU_SHIFT               (0)  /* Squelch Detection Level */
#define R_USB_HS_PHYTRIM2_SQU_MASK                0xf

/* DPUSR0R Register bit definitions */
#define R_USB_HS_DPUSR0R_DVBSTSHM                 (1 << 23)  /* VBUS InputIndicates VBUS input signal on the HS side of USB port. */

#define R_USB_HS_DPUSR0R_DOVCBHM                  (1 << 21)  /* OVRCURB InputIndicates OVRCURB input signal on the HS side of USB port. */

#define R_USB_HS_DPUSR0R_DOVCAHM                  (1 << 20)  /* OVRCURA InputIndicates OVRCURA input signal on the HS side of USB port. */

/* DPUSR1R Register bit definitions */
#define R_USB_HS_DPUSR1R_DVBSTSH                  (1 << 23)  /* Indication of Return from VBUS Interrupt Source */

#define R_USB_HS_DPUSR1R_DOVCBH                   (1 << 21)  /* Indication of Return from OVRCURB Interrupt Source */

#define R_USB_HS_DPUSR1R_DOVCAH                   (1 << 20)  /* Indication of Return from OVRCURA Interrupt Source */

#define R_USB_HS_DPUSR1R_DVBSTSHE                 (1 << 7)  /* VBUS Interrupt Enable/Clear */

#define R_USB_HS_DPUSR1R_DOVCBHE                  (1 << 5)  /* OVRCURB Interrupt Enable Clear */

#define R_USB_HS_DPUSR1R_DOVCAHE                  (1 << 4)  /* OVRCURA Interrupt Enable Clear */

/* DPUSR2R Register bit definitions */
#define R_USB_HS_DPUSR2R_DMINTE                   (1 << 9)  /* DM Interrupt Enable Clear */

#define R_USB_HS_DPUSR2R_DPINTE                   (1 << 8)  /* DP Interrupt Enable Clear */

#define R_USB_HS_DPUSR2R_DMVAL                    (1 << 5)  /* DM InputIndicates DM input signal on the HS side of USB port. */

#define R_USB_HS_DPUSR2R_DPVAL                    (1 << 4)  /* DP InputIndicates DP input signal on the HS side of USB port. */

#define R_USB_HS_DPUSR2R_DMINT                    (1 << 1)  /* Indication of Return from DM Interrupt Source */

#define R_USB_HS_DPUSR2R_DPINT                    (1 << 0)  /* Indication of Return from DP Interrupt Source */

/* DPUSRCR Register bit definitions */
#define R_USB_HS_DPUSRCR_FIXPHYPD                 (1 << 1)  /* USB Transceiver Control Fix for PLL */

#define R_USB_HS_DPUSRCR_FIXPHY                   (1 << 0)  /* USB Transceiver Control Fix */


/* Maximum number of channels */

#define USB_HS_MAX_CHANNELS    10

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_USB_HS_H */
