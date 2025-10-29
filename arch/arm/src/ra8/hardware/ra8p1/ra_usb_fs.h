/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_usb_fs.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_USB_FS_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_USB_FS_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* USB_FS Base Address */
#ifndef R_USB_FS_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_USB_FS_BASE           0x40250000
#else
#define R_USB_FS_BASE           0x50250000
#endif
#endif

/* USB_FS Register Offsets */

#define R_USB_FS_SYSCFG_OFFSET                    0x00000000  /* System Configuration Control Register */
#define R_USB_FS_BUSWAIT_OFFSET                   0x00000002  /* CPU Bus Wait Register */
#define R_USB_FS_SYSSTS0_OFFSET                   0x00000004  /* System Configuration Status Register 0  */
#define R_USB_FS_PLLSTA_OFFSET                    0x00000006  /* PLL Status Register */
#define R_USB_FS_DVSTCTR0_OFFSET                  0x00000008  /* Device State Control Register 0 */
#define R_USB_FS_TESTMODE_OFFSET                  0x0000000c  /* USB Test Mode Register  */
#define R_USB_FS_CFIFOL_OFFSET                    0x00000014  /* CFIFO Port Register L */
#define R_USB_FS_CFIFOLL_OFFSET                   0x00000014  /* CFIFO Port Register LL */
#define R_USB_FS_CFIFO_OFFSET                     0x00000014  /* CFIFO Port Register */
#define R_USB_FS_CFIFOH_OFFSET                    0x00000016  /* CFIFO Port Register H */
#define R_USB_FS_CFIFOHH_OFFSET                   0x00000017  /* CFIFO Port Register HH */
#define R_USB_FS_D0FIFOL_OFFSET                   0x00000018  /* D0FIFO Port Register L */
#define R_USB_FS_D0FIFOLL_OFFSET                  0x00000018  /* D0FIFO Port Register LL */
#define R_USB_FS_D0FIFO_OFFSET                    0x00000018  /* D0FIFO Port Register */
#define R_USB_FS_D0FIFOH_OFFSET                   0x0000001a  /* D0FIFO Port Register H */
#define R_USB_FS_D0FIFOHH_OFFSET                  0x0000001b  /* D0FIFO Port Register HH */
#define R_USB_FS_D1FIFOL_OFFSET                   0x0000001c  /* D1FIFO Port Register L */
#define R_USB_FS_D1FIFOLL_OFFSET                  0x0000001c  /* D1FIFO Port Register LL */
#define R_USB_FS_D1FIFO_OFFSET                    0x0000001c  /* D1FIFO Port Register */
#define R_USB_FS_D1FIFOH_OFFSET                   0x0000001e  /* D1FIFO Port Register H */
#define R_USB_FS_D1FIFOHH_OFFSET                  0x0000001f  /* D1FIFO Port Register HH */
#define R_USB_FS_CFIFOSEL_OFFSET                  0x00000020  /* CFIFO Port Select Register */
#define R_USB_FS_CFIFOCTR_OFFSET                  0x00000022  /* CFIFO Port Control Register */
#define R_USB_FS_D0FIFOSEL_OFFSET                 0x00000028  /* D0FIFO Port Select Register */
#define R_USB_FS_D0FIFOCTR_OFFSET                 0x0000002a  /* D0FIFO Port Control Register */
#define R_USB_FS_D1FIFOSEL_OFFSET                 0x0000002c  /* D1FIFO Port Select Register */
#define R_USB_FS_D1FIFOCTR_OFFSET                 0x0000002e  /* D1FIFO Port Control Register */
#define R_USB_FS_INTENB0_OFFSET                   0x00000030  /* Interrupt Enable Register 0 */
#define R_USB_FS_INTENB1_OFFSET                   0x00000032  /* Interrupt Enable Register 1  */
#define R_USB_FS_BRDYENB_OFFSET                   0x00000036  /* BRDY Interrupt Enable Register */
#define R_USB_FS_NRDYENB_OFFSET                   0x00000038  /* NRDY Interrupt Enable Register */
#define R_USB_FS_BEMPENB_OFFSET                   0x0000003a  /* BEMP Interrupt Enable Register */
#define R_USB_FS_SOFCFG_OFFSET                    0x0000003c  /* SOF Output Configuration Register  */
#define R_USB_FS_PHYSET_OFFSET                    0x0000003e  /* PHY Setting Register */
#define R_USB_FS_INTSTS0_OFFSET                   0x00000040  /* Interrupt Status Register 0 */
#define R_USB_FS_INTSTS1_OFFSET                   0x00000042  /* Interrupt Status Register 1 */
#define R_USB_FS_BRDYSTS_OFFSET                   0x00000046  /* BRDY Interrupt Status Register */
#define R_USB_FS_NRDYSTS_OFFSET                   0x00000048  /* NRDY Interrupt Status Register */
#define R_USB_FS_BEMPSTS_OFFSET                   0x0000004a  /* BEMP Interrupt Status Register */
#define R_USB_FS_FRMNUM_OFFSET                    0x0000004c  /* Frame Number Register */
#define R_USB_FS_DVCHGR_OFFSET                    0x0000004e  /* Device State Change Register */
#define R_USB_FS_USBADDR_OFFSET                   0x00000050  /* USB Address Register */
#define R_USB_FS_USBREQ_OFFSET                    0x00000054  /* USB Request Type Register */
#define R_USB_FS_USBVAL_OFFSET                    0x00000056  /* USB Request Value Register */
#define R_USB_FS_USBINDX_OFFSET                   0x00000058  /* USB Request Index Register */
#define R_USB_FS_USBLENG_OFFSET                   0x0000005a  /* USB Request Length Register */
#define R_USB_FS_DCPCFG_OFFSET                    0x0000005c  /* DCP Configuration Register */
#define R_USB_FS_DCPMAXP_OFFSET                   0x0000005e  /* DCP Maximum Packet Size Register */
#define R_USB_FS_DCPCTR_OFFSET                    0x00000060  /* DCP Control Register */
#define R_USB_FS_PIPESEL_OFFSET                   0x00000064  /* Pipe Window Select Register */
#define R_USB_FS_PIPECFG_OFFSET                   0x00000068  /* Pipe Configuration Register */
#define R_USB_FS_PIPEMAXP_OFFSET                  0x0000006c  /* Pipe Maximum Packet Size Register  */
#define R_USB_FS_PIPEPERI_OFFSET                  0x0000006e  /* Pipe Cycle Control Register */
/* PIPE_CTR[%s] Registers () */
#define R_USB_FS_PIPE_CTR_OFFSET(m)               (0x00000070 + ((m) * 0x00000002))  /* Pipe %s Control Register */
/* PIPE_TR[%s] Registers () */
#define R_USB_FS_PIPE_TR_OFFSET(m)                (0x00000090 + ((m) * 0x00000004))  /* Pipe Transaction Counter Registers */
#define R_USB_FS_USBBCCTRL0_OFFSET                0x000000b0  /* BC Control Register 0 */
#define R_USB_FS_UCKSEL_OFFSET                    0x000000c4  /* USB Clock Selection Register */
#define R_USB_FS_USBMC_OFFSET                     0x000000cc  /* USB Module Control Register */
/* DEVADD[%s] Registers () */
#define R_USB_FS_DEVADD_OFFSET(m)                 (0x000000d0 + ((m) * 0x00000002))  /* Device Address Configuration Register */
#define R_USB_FS_PHYSLEW_OFFSET                   0x000000f0  /* PHY Cross Point Adjustment Register  */
#define R_USB_FS_LPCTRL_OFFSET                    0x00000100  /* Low Power Control Register */
#define R_USB_FS_LPSTS_OFFSET                     0x00000102  /* Low Power Status Register */
#define R_USB_FS_BCCTRL_OFFSET                    0x00000140  /* Battery Charging Control Register */
#define R_USB_FS_PL1CTRL1_OFFSET                  0x00000144  /* Function L1 Control Register 1 */
#define R_USB_FS_PL1CTRL2_OFFSET                  0x00000146  /* Function L1 Control Register 2 */
#define R_USB_FS_HL1CTRL1_OFFSET                  0x00000148  /* Host L1 Control Register 1 */
#define R_USB_FS_HL1CTRL2_OFFSET                  0x0000014a  /* Host L1 Control Register 2 */
#define R_USB_FS_DPUSR0R_OFFSET                   0x00000160  /* Deep Standby USB Transceiver Control/Pin Monitor Register  */
#define R_USB_FS_DPUSR1R_OFFSET                   0x00000164  /* Deep Standby USB Suspend/Resume Interrupt Register */
#define R_USB_FS_DPUSR2R_OFFSET                   0x00000168  /* Deep Standby USB Suspend/Resume Interrupt Register */
#define R_USB_FS_DPUSRCR_OFFSET                   0x0000016a  /* Deep Standby USB Suspend/Resume Command Register */
#define R_USB_FS_DPUSR0R_FS_OFFSET                0x00000400  /* Deep Software Standby USB Transceiver Control/Pin Monitor Register */
#define R_USB_FS_DPUSR1R_FS_OFFSET                0x00000404  /* Deep Software Standby USB Suspend/Resume Interrupt Register */

/* USB_FS Register Addresses */

#define R_USB_FS_SYSCFG                           (R_USB_FS_BASE + R_USB_FS_SYSCFG_OFFSET)
#define R_USB_FS_BUSWAIT                          (R_USB_FS_BASE + R_USB_FS_BUSWAIT_OFFSET)
#define R_USB_FS_SYSSTS0                          (R_USB_FS_BASE + R_USB_FS_SYSSTS0_OFFSET)
#define R_USB_FS_PLLSTA                           (R_USB_FS_BASE + R_USB_FS_PLLSTA_OFFSET)
#define R_USB_FS_DVSTCTR0                         (R_USB_FS_BASE + R_USB_FS_DVSTCTR0_OFFSET)
#define R_USB_FS_TESTMODE                         (R_USB_FS_BASE + R_USB_FS_TESTMODE_OFFSET)
#define R_USB_FS_CFIFOL                           (R_USB_FS_BASE + R_USB_FS_CFIFOL_OFFSET)
#define R_USB_FS_CFIFOLL                          (R_USB_FS_BASE + R_USB_FS_CFIFOLL_OFFSET)
#define R_USB_FS_CFIFO                            (R_USB_FS_BASE + R_USB_FS_CFIFO_OFFSET)
#define R_USB_FS_CFIFOH                           (R_USB_FS_BASE + R_USB_FS_CFIFOH_OFFSET)
#define R_USB_FS_CFIFOHH                          (R_USB_FS_BASE + R_USB_FS_CFIFOHH_OFFSET)
#define R_USB_FS_D0FIFOL                          (R_USB_FS_BASE + R_USB_FS_D0FIFOL_OFFSET)
#define R_USB_FS_D0FIFOLL                         (R_USB_FS_BASE + R_USB_FS_D0FIFOLL_OFFSET)
#define R_USB_FS_D0FIFO                           (R_USB_FS_BASE + R_USB_FS_D0FIFO_OFFSET)
#define R_USB_FS_D0FIFOH                          (R_USB_FS_BASE + R_USB_FS_D0FIFOH_OFFSET)
#define R_USB_FS_D0FIFOHH                         (R_USB_FS_BASE + R_USB_FS_D0FIFOHH_OFFSET)
#define R_USB_FS_D1FIFOL                          (R_USB_FS_BASE + R_USB_FS_D1FIFOL_OFFSET)
#define R_USB_FS_D1FIFOLL                         (R_USB_FS_BASE + R_USB_FS_D1FIFOLL_OFFSET)
#define R_USB_FS_D1FIFO                           (R_USB_FS_BASE + R_USB_FS_D1FIFO_OFFSET)
#define R_USB_FS_D1FIFOH                          (R_USB_FS_BASE + R_USB_FS_D1FIFOH_OFFSET)
#define R_USB_FS_D1FIFOHH                         (R_USB_FS_BASE + R_USB_FS_D1FIFOHH_OFFSET)
#define R_USB_FS_CFIFOSEL                         (R_USB_FS_BASE + R_USB_FS_CFIFOSEL_OFFSET)
#define R_USB_FS_CFIFOCTR                         (R_USB_FS_BASE + R_USB_FS_CFIFOCTR_OFFSET)
#define R_USB_FS_D0FIFOSEL                        (R_USB_FS_BASE + R_USB_FS_D0FIFOSEL_OFFSET)
#define R_USB_FS_D0FIFOCTR                        (R_USB_FS_BASE + R_USB_FS_D0FIFOCTR_OFFSET)
#define R_USB_FS_D1FIFOSEL                        (R_USB_FS_BASE + R_USB_FS_D1FIFOSEL_OFFSET)
#define R_USB_FS_D1FIFOCTR                        (R_USB_FS_BASE + R_USB_FS_D1FIFOCTR_OFFSET)
#define R_USB_FS_INTENB0                          (R_USB_FS_BASE + R_USB_FS_INTENB0_OFFSET)
#define R_USB_FS_INTENB1                          (R_USB_FS_BASE + R_USB_FS_INTENB1_OFFSET)
#define R_USB_FS_BRDYENB                          (R_USB_FS_BASE + R_USB_FS_BRDYENB_OFFSET)
#define R_USB_FS_NRDYENB                          (R_USB_FS_BASE + R_USB_FS_NRDYENB_OFFSET)
#define R_USB_FS_BEMPENB                          (R_USB_FS_BASE + R_USB_FS_BEMPENB_OFFSET)
#define R_USB_FS_SOFCFG                           (R_USB_FS_BASE + R_USB_FS_SOFCFG_OFFSET)
#define R_USB_FS_PHYSET                           (R_USB_FS_BASE + R_USB_FS_PHYSET_OFFSET)
#define R_USB_FS_INTSTS0                          (R_USB_FS_BASE + R_USB_FS_INTSTS0_OFFSET)
#define R_USB_FS_INTSTS1                          (R_USB_FS_BASE + R_USB_FS_INTSTS1_OFFSET)
#define R_USB_FS_BRDYSTS                          (R_USB_FS_BASE + R_USB_FS_BRDYSTS_OFFSET)
#define R_USB_FS_NRDYSTS                          (R_USB_FS_BASE + R_USB_FS_NRDYSTS_OFFSET)
#define R_USB_FS_BEMPSTS                          (R_USB_FS_BASE + R_USB_FS_BEMPSTS_OFFSET)
#define R_USB_FS_FRMNUM                           (R_USB_FS_BASE + R_USB_FS_FRMNUM_OFFSET)
#define R_USB_FS_DVCHGR                           (R_USB_FS_BASE + R_USB_FS_DVCHGR_OFFSET)
#define R_USB_FS_USBADDR                          (R_USB_FS_BASE + R_USB_FS_USBADDR_OFFSET)
#define R_USB_FS_USBREQ                           (R_USB_FS_BASE + R_USB_FS_USBREQ_OFFSET)
#define R_USB_FS_USBVAL                           (R_USB_FS_BASE + R_USB_FS_USBVAL_OFFSET)
#define R_USB_FS_USBINDX                          (R_USB_FS_BASE + R_USB_FS_USBINDX_OFFSET)
#define R_USB_FS_USBLENG                          (R_USB_FS_BASE + R_USB_FS_USBLENG_OFFSET)
#define R_USB_FS_DCPCFG                           (R_USB_FS_BASE + R_USB_FS_DCPCFG_OFFSET)
#define R_USB_FS_DCPMAXP                          (R_USB_FS_BASE + R_USB_FS_DCPMAXP_OFFSET)
#define R_USB_FS_DCPCTR                           (R_USB_FS_BASE + R_USB_FS_DCPCTR_OFFSET)
#define R_USB_FS_PIPESEL                          (R_USB_FS_BASE + R_USB_FS_PIPESEL_OFFSET)
#define R_USB_FS_PIPECFG                          (R_USB_FS_BASE + R_USB_FS_PIPECFG_OFFSET)
#define R_USB_FS_PIPEMAXP                         (R_USB_FS_BASE + R_USB_FS_PIPEMAXP_OFFSET)
#define R_USB_FS_PIPEPERI                         (R_USB_FS_BASE + R_USB_FS_PIPEPERI_OFFSET)
#define R_USB_FS_PIPE_CTR(m)                      (R_USB_FS_BASE + R_USB_FS_PIPE_CTR_OFFSET(m))
#define R_USB_FS_PIPE_TR(m)                       (R_USB_FS_BASE + R_USB_FS_PIPE_TR_OFFSET(m))
#define R_USB_FS_USBBCCTRL0                       (R_USB_FS_BASE + R_USB_FS_USBBCCTRL0_OFFSET)
#define R_USB_FS_UCKSEL                           (R_USB_FS_BASE + R_USB_FS_UCKSEL_OFFSET)
#define R_USB_FS_USBMC                            (R_USB_FS_BASE + R_USB_FS_USBMC_OFFSET)
#define R_USB_FS_DEVADD(m)                        (R_USB_FS_BASE + R_USB_FS_DEVADD_OFFSET(m))
#define R_USB_FS_PHYSLEW                          (R_USB_FS_BASE + R_USB_FS_PHYSLEW_OFFSET)
#define R_USB_FS_LPCTRL                           (R_USB_FS_BASE + R_USB_FS_LPCTRL_OFFSET)
#define R_USB_FS_LPSTS                            (R_USB_FS_BASE + R_USB_FS_LPSTS_OFFSET)
#define R_USB_FS_BCCTRL                           (R_USB_FS_BASE + R_USB_FS_BCCTRL_OFFSET)
#define R_USB_FS_PL1CTRL1                         (R_USB_FS_BASE + R_USB_FS_PL1CTRL1_OFFSET)
#define R_USB_FS_PL1CTRL2                         (R_USB_FS_BASE + R_USB_FS_PL1CTRL2_OFFSET)
#define R_USB_FS_HL1CTRL1                         (R_USB_FS_BASE + R_USB_FS_HL1CTRL1_OFFSET)
#define R_USB_FS_HL1CTRL2                         (R_USB_FS_BASE + R_USB_FS_HL1CTRL2_OFFSET)
#define R_USB_FS_DPUSR0R                          (R_USB_FS_BASE + R_USB_FS_DPUSR0R_OFFSET)
#define R_USB_FS_DPUSR1R                          (R_USB_FS_BASE + R_USB_FS_DPUSR1R_OFFSET)
#define R_USB_FS_DPUSR2R                          (R_USB_FS_BASE + R_USB_FS_DPUSR2R_OFFSET)
#define R_USB_FS_DPUSRCR                          (R_USB_FS_BASE + R_USB_FS_DPUSRCR_OFFSET)
#define R_USB_FS_DPUSR0R_FS                       (R_USB_FS_BASE + R_USB_FS_DPUSR0R_FS_OFFSET)
#define R_USB_FS_DPUSR1R_FS                       (R_USB_FS_BASE + R_USB_FS_DPUSR1R_FS_OFFSET)

/* Register bit definitions */
/* SYSCFG Register bit definitions */
#define R_USB_FS_SYSCFG_SCKE                      (1 << 10)  /* USB Clock Enable */

#define R_USB_FS_SYSCFG_CNEN                      (1 << 8)  /* CNEN Single End Receiver Enable */

#define R_USB_FS_SYSCFG_DCFM                      (1 << 6)  /* Controller Function Select */

#define R_USB_FS_SYSCFG_DRPD                      (1 << 5)  /* D+/D- Line Resistor Control */

#define R_USB_FS_SYSCFG_DPRPU                     (1 << 4)  /* D+ Line Resistor Control */

#define R_USB_FS_SYSCFG_DMRPU                     (1 << 3)  /* D- Line Resistor Control  */

#define R_USB_FS_SYSCFG_USBE                      (1 << 0)  /* USB Operation Enable */

/* BUSWAIT Register bit definitions */
#define R_USB_FS_BUSWAIT_BWAIT_SHIFT              (0)  /* CPU Bus Access Wait Specification     BWAIT waits (BWAIT+2 access cycles) */
#define R_USB_FS_BUSWAIT_BWAIT_MASK               0xf

/* SYSSTS0 Register bit definitions */
#define R_USB_FS_SYSSTS0_OVCMON_SHIFT             (14)  /* External USB0_OVRCURA/ USB0_OVRCURB Input Pin MonitorThe OCVMON[1] bit indicates the status of the USBHS_OVRCURA pin. The OCVMON[0] bit indicates the status of the USBHS_OVRCURB pin. */
#define R_USB_FS_SYSSTS0_OVCMON_MASK              0xc000

#define R_USB_FS_SYSSTS0_HTACT                    (1 << 6)  /* USB Host Sequencer Status Monitor */

#define R_USB_FS_SYSSTS0_SOFEA                    (1 << 5)  /* SOF Active Monitor While Host Controller Function is Selected. */

#define R_USB_FS_SYSSTS0_IDMON                    (1 << 2)  /* External ID0 Input Pin Monitor */

#define R_USB_FS_SYSSTS0_LNST_SHIFT               (0)  /* USB Data Line Status Monitor */
#define R_USB_FS_SYSSTS0_LNST_MASK                0x3
#  define R_USB_FS_SYSSTS0_LNST_00                        (0 << R_USB_FS_SYSSTS0_LNST_SHIFT)  /* SE0  */
#  define R_USB_FS_SYSSTS0_LNST_01                        (1 << R_USB_FS_SYSSTS0_LNST_SHIFT)  /* K-State (FS) / J-State(LS)   */
#  define R_USB_FS_SYSSTS0_LNST_10                        (2 << R_USB_FS_SYSSTS0_LNST_SHIFT)  /* J-State(FS) / K-State(LS) */
#  define R_USB_FS_SYSSTS0_LNST_11                        (3 << R_USB_FS_SYSSTS0_LNST_SHIFT)  /* SE1 */

/* PLLSTA Register bit definitions */
#define R_USB_FS_PLLSTA_PLLLOCK                   (1 << 0)  /* PLL Lock Flag */

/* DVSTCTR0 Register bit definitions */
#define R_USB_FS_DVSTCTR0_HNPBTOA                 (1 << 11)  /* Host Negotiation Protocol (HNP) Control     This bit is used when switching from device B to device A while in OTG mode. If the HNPBTOA bit is 1, the internal function control keeps the suspended state until the HNP processing ends even  though SYSCFG.DPRPU = 0 or SYSCFG.DCFM = 1 is set. */

#define R_USB_FS_DVSTCTR0_EXICEN                  (1 << 10)  /* USB_EXICEN Output Pin Control */

#define R_USB_FS_DVSTCTR0_VBUSEN                  (1 << 9)  /* USB_VBUSEN Output Pin Control */

#define R_USB_FS_DVSTCTR0_WKUP                    (1 << 8)  /* Wakeup Output */

#define R_USB_FS_DVSTCTR0_RWUPE                   (1 << 7)  /* Wakeup Detection Enable */

#define R_USB_FS_DVSTCTR0_USBRST                  (1 << 6)  /* USB Bus Reset Output */

#define R_USB_FS_DVSTCTR0_RESUME                  (1 << 5)  /* Resume Output */

#define R_USB_FS_DVSTCTR0_UACT                    (1 << 4)  /* USB Bus Enable */

#define R_USB_FS_DVSTCTR0_RHST_SHIFT              (0)  /* USB Bus Reset Status */
#define R_USB_FS_DVSTCTR0_RHST_MASK               0x7
#  define R_USB_FS_DVSTCTR0_RHST_000                      (0 << R_USB_FS_DVSTCTR0_RHST_SHIFT)  /* Communication speed not determined */
#  define R_USB_FS_DVSTCTR0_RHST_001                      (1 << R_USB_FS_DVSTCTR0_RHST_SHIFT)  /* Low-speed connection(When the host controller is selected) /USB bus reset in progress( When the function controller is selected) */
#  define R_USB_FS_DVSTCTR0_RHST_010                      (2 << R_USB_FS_DVSTCTR0_RHST_SHIFT)  /* Full-speed connection(When the host controller is selected) /USB bus reset in progress or full-speed connection(When the function controller is selected) */
#  define R_USB_FS_DVSTCTR0_RHST_011                      (3 << R_USB_FS_DVSTCTR0_RHST_SHIFT)  /* Setting prohibited */

/* TESTMODE Register bit definitions */
#define R_USB_FS_TESTMODE_UTST_SHIFT              (0)  /* Test Mode */
#define R_USB_FS_TESTMODE_UTST_MASK               0xf
#  define R_USB_FS_TESTMODE_UTST_0000                     (0 << R_USB_FS_TESTMODE_UTST_SHIFT)  /* Normal operation */
#  define R_USB_FS_TESTMODE_UTST_0001                     (1 << R_USB_FS_TESTMODE_UTST_SHIFT)  /* Test_J TestMode(When the Function Controller Function is Selected) */
#  define R_USB_FS_TESTMODE_UTST_0010                     (2 << R_USB_FS_TESTMODE_UTST_SHIFT)  /* Test_K TestMode(When the Function Controller Function is Selected) */
#  define R_USB_FS_TESTMODE_UTST_0011                     (3 << R_USB_FS_TESTMODE_UTST_SHIFT)  /* Test_SE0_NAK TestMode(When the Function Controller Function is Selected) */
#  define R_USB_FS_TESTMODE_UTST_0100                     (4 << R_USB_FS_TESTMODE_UTST_SHIFT)  /* Test_Packet TestMode(When the Function Controller Function is Selected) */
#  define R_USB_FS_TESTMODE_UTST_0101                     (5 << R_USB_FS_TESTMODE_UTST_SHIFT)  /* Reserved TestMode(When the Function Controller Function is Selected) */
#  define R_USB_FS_TESTMODE_UTST_0110                     (6 << R_USB_FS_TESTMODE_UTST_SHIFT)  /* Reserved TestMode(When the Function Controller Function is Selected) */
#  define R_USB_FS_TESTMODE_UTST_0111                     (7 << R_USB_FS_TESTMODE_UTST_SHIFT)  /* Reserved TestMode(When the Function Controller Function is Selected) */
#  define R_USB_FS_TESTMODE_UTST_1001                     (9 << R_USB_FS_TESTMODE_UTST_SHIFT)  /* Test_J TestMode(When the Host Controller Function is Selected) */
#  define R_USB_FS_TESTMODE_UTST_1010                     (10 << R_USB_FS_TESTMODE_UTST_SHIFT)  /* Test_K TestMode(When the Host Controller Function is Selected) */
#  define R_USB_FS_TESTMODE_UTST_1011                     (11 << R_USB_FS_TESTMODE_UTST_SHIFT)  /* Test_SE0_NAK TestMode(When the Host Controller Function is Selected) */
#  define R_USB_FS_TESTMODE_UTST_1100                     (12 << R_USB_FS_TESTMODE_UTST_SHIFT)  /* Test_Packet TestMode(When the Host Controller Function is Selected) */
#  define R_USB_FS_TESTMODE_UTST_1101                     (13 << R_USB_FS_TESTMODE_UTST_SHIFT)  /* Test_Force_EnableTestMode(When the Host Controller Function is Selected) */
#  define R_USB_FS_TESTMODE_UTST_1110                     (14 << R_USB_FS_TESTMODE_UTST_SHIFT)  /* Reserved TestMode(When the Host Controller Function is Selected) */
#  define R_USB_FS_TESTMODE_UTST_1111                     (15 << R_USB_FS_TESTMODE_UTST_SHIFT)  /* Reserved TestMode(When the Host Controller Function is Selected) */

/* CFIFOSEL Register bit definitions */
#define R_USB_FS_CFIFOSEL_RCNT                    (1 << 15)  /* Read Count Mode */

#define R_USB_FS_CFIFOSEL_REW                     (1 << 14)  /* Buffer Pointer Rewind */

#define R_USB_FS_CFIFOSEL_MBW_SHIFT               (10)  /* CFIFO Port Access Bit Width */
#define R_USB_FS_CFIFOSEL_MBW_MASK                0xc00
#  define R_USB_FS_CFIFOSEL_MBW_0                         (0 << R_USB_FS_CFIFOSEL_MBW_SHIFT)  /* 8-bit width */
#  define R_USB_FS_CFIFOSEL_MBW_1                         (1 << R_USB_FS_CFIFOSEL_MBW_SHIFT)  /* 16-bit width */
#  define R_USB_FS_CFIFOSEL_MBW_2                         (2 << R_USB_FS_CFIFOSEL_MBW_SHIFT)  /* 32-bit width */

#define R_USB_FS_CFIFOSEL_BIGEND                  (1 << 8)  /* CFIFO Port Endian Control */

#define R_USB_FS_CFIFOSEL_ISEL                    (1 << 5)  /* CFIFO Port Access Direction When DCP is Selected */

#define R_USB_FS_CFIFOSEL_CURPIPE_SHIFT           (0)  /* CFIFO Port Access Pipe Specification */
#define R_USB_FS_CFIFOSEL_CURPIPE_MASK            0xf
#  define R_USB_FS_CFIFOSEL_CURPIPE_0000                  (0 << R_USB_FS_CFIFOSEL_CURPIPE_SHIFT)  /* DCP (Default control pipe) */
#  define R_USB_FS_CFIFOSEL_CURPIPE_0001                  (1 << R_USB_FS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 1 */
#  define R_USB_FS_CFIFOSEL_CURPIPE_0010                  (2 << R_USB_FS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 2 */
#  define R_USB_FS_CFIFOSEL_CURPIPE_0011                  (3 << R_USB_FS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 3 */
#  define R_USB_FS_CFIFOSEL_CURPIPE_0100                  (4 << R_USB_FS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 4 */
#  define R_USB_FS_CFIFOSEL_CURPIPE_0101                  (5 << R_USB_FS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 5 */
#  define R_USB_FS_CFIFOSEL_CURPIPE_0110                  (6 << R_USB_FS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 6 */
#  define R_USB_FS_CFIFOSEL_CURPIPE_0111                  (7 << R_USB_FS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 7 */
#  define R_USB_FS_CFIFOSEL_CURPIPE_1000                  (8 << R_USB_FS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 8 */
#  define R_USB_FS_CFIFOSEL_CURPIPE_1001                  (9 << R_USB_FS_CFIFOSEL_CURPIPE_SHIFT)  /* Pipe 9 */

/* CFIFOCTR Register bit definitions */
#define R_USB_FS_CFIFOCTR_BVAL                    (1 << 15)  /* Buffer Memory Valid Flag */

#define R_USB_FS_CFIFOCTR_BCLR                    (1 << 14)  /* CPU Buffer ClearNote: Only 0 can be read. */

#define R_USB_FS_CFIFOCTR_FRDY                    (1 << 13)  /* FIFO Port Ready */

#define R_USB_FS_CFIFOCTR_DTLN_SHIFT              (0)  /* Receive Data LengthIndicates the length of the receive data. */
#define R_USB_FS_CFIFOCTR_DTLN_MASK               0xfff

/* D0FIFOSEL Register bit definitions */
#define R_USB_FS_D0FIFOSEL_RCNT                   (1 << 15)  /* Read Count Mode */

#define R_USB_FS_D0FIFOSEL_REW                    (1 << 14)  /* Buffer Pointer RewindNote: Only 0 can be read. */

#define R_USB_FS_D0FIFOSEL_DCLRM                  (1 << 13)  /* Auto Buffer Memory Clear Mode Accessed after Specified Pipe Data is Read */

#define R_USB_FS_D0FIFOSEL_DREQE                  (1 << 12)  /* DMA/DTC Transfer Request Enable */

#define R_USB_FS_D0FIFOSEL_MBW_SHIFT              (10)  /* FIFO Port Access Bit Width */
#define R_USB_FS_D0FIFOSEL_MBW_MASK               0xc00
#  define R_USB_FS_D0FIFOSEL_MBW_0                        (0 << R_USB_FS_D0FIFOSEL_MBW_SHIFT)  /* 8-bit width */
#  define R_USB_FS_D0FIFOSEL_MBW_1                        (1 << R_USB_FS_D0FIFOSEL_MBW_SHIFT)  /* 16-bit width */
#  define R_USB_FS_D0FIFOSEL_MBW_2                        (2 << R_USB_FS_D0FIFOSEL_MBW_SHIFT)  /* 32-bit width */

#define R_USB_FS_D0FIFOSEL_BIGEND                 (1 << 8)  /* FIFO Port Endian Control */

#define R_USB_FS_D0FIFOSEL_CURPIPE_SHIFT          (0)  /* FIFO Port Access Pipe Specification */
#define R_USB_FS_D0FIFOSEL_CURPIPE_MASK           0xf
#  define R_USB_FS_D0FIFOSEL_CURPIPE_0000                 (0 << R_USB_FS_D0FIFOSEL_CURPIPE_SHIFT)  /* DCP (Default control pipe) */
#  define R_USB_FS_D0FIFOSEL_CURPIPE_0001                 (1 << R_USB_FS_D0FIFOSEL_CURPIPE_SHIFT)  /* Pipe 1 */
#  define R_USB_FS_D0FIFOSEL_CURPIPE_0010                 (2 << R_USB_FS_D0FIFOSEL_CURPIPE_SHIFT)  /* Pipe 2 */
#  define R_USB_FS_D0FIFOSEL_CURPIPE_0011                 (3 << R_USB_FS_D0FIFOSEL_CURPIPE_SHIFT)  /* Pipe 3 */
#  define R_USB_FS_D0FIFOSEL_CURPIPE_0100                 (4 << R_USB_FS_D0FIFOSEL_CURPIPE_SHIFT)  /* Pipe 4 */
#  define R_USB_FS_D0FIFOSEL_CURPIPE_0101                 (5 << R_USB_FS_D0FIFOSEL_CURPIPE_SHIFT)  /* Pipe 5 */
#  define R_USB_FS_D0FIFOSEL_CURPIPE_0110                 (6 << R_USB_FS_D0FIFOSEL_CURPIPE_SHIFT)  /* Pipe 6 */
#  define R_USB_FS_D0FIFOSEL_CURPIPE_0111                 (7 << R_USB_FS_D0FIFOSEL_CURPIPE_SHIFT)  /* Pipe 7 */
#  define R_USB_FS_D0FIFOSEL_CURPIPE_1000                 (8 << R_USB_FS_D0FIFOSEL_CURPIPE_SHIFT)  /* Pipe 8 */
#  define R_USB_FS_D0FIFOSEL_CURPIPE_1001                 (9 << R_USB_FS_D0FIFOSEL_CURPIPE_SHIFT)  /* Pipe 9 */

/* D0FIFOCTR Register bit definitions */
#define R_USB_FS_D0FIFOCTR_BVAL                   (1 << 15)  /* Buffer Memory Valid Flag */

#define R_USB_FS_D0FIFOCTR_BCLR                   (1 << 14)  /* CPU Buffer ClearNote: Only 0 can be read. */

#define R_USB_FS_D0FIFOCTR_FRDY                   (1 << 13)  /* FIFO Port Ready */

#define R_USB_FS_D0FIFOCTR_DTLN_SHIFT             (0)  /* Receive Data LengthIndicates the length of the receive data. */
#define R_USB_FS_D0FIFOCTR_DTLN_MASK              0xfff

/* D1FIFOSEL Register bit definitions */
#define R_USB_FS_D1FIFOSEL_RCNT                   (1 << 15)  /* Read Count Mode */

#define R_USB_FS_D1FIFOSEL_REW                    (1 << 14)  /* Buffer Pointer Rewind */

#define R_USB_FS_D1FIFOSEL_DCLRM                  (1 << 13)  /* Auto Buffer Memory Clear Mode Accessed after Specified Pipe Data is Read */

#define R_USB_FS_D1FIFOSEL_DREQE                  (1 << 12)  /* DMA/DTC Transfer Request Enable */

#define R_USB_FS_D1FIFOSEL_MBW_SHIFT              (10)  /* FIFO Port Access Bit Width */
#define R_USB_FS_D1FIFOSEL_MBW_MASK               0xc00
#  define R_USB_FS_D1FIFOSEL_MBW_0                        (0 << R_USB_FS_D1FIFOSEL_MBW_SHIFT)  /* 8-bit width */
#  define R_USB_FS_D1FIFOSEL_MBW_1                        (1 << R_USB_FS_D1FIFOSEL_MBW_SHIFT)  /* 16-bit width */
#  define R_USB_FS_D1FIFOSEL_MBW_2                        (2 << R_USB_FS_D1FIFOSEL_MBW_SHIFT)  /* 32-bit width */

#define R_USB_FS_D1FIFOSEL_BIGEND                 (1 << 8)  /* FIFO Port Endian Control */

#define R_USB_FS_D1FIFOSEL_CURPIPE_SHIFT          (0)  /* FIFO Port Access Pipe Specification */
#define R_USB_FS_D1FIFOSEL_CURPIPE_MASK           0xf
#  define R_USB_FS_D1FIFOSEL_CURPIPE_0000                 (0 << R_USB_FS_D1FIFOSEL_CURPIPE_SHIFT)  /* DCP (Default control pipe) */
#  define R_USB_FS_D1FIFOSEL_CURPIPE_0001                 (1 << R_USB_FS_D1FIFOSEL_CURPIPE_SHIFT)  /* Pipe 1 */
#  define R_USB_FS_D1FIFOSEL_CURPIPE_0010                 (2 << R_USB_FS_D1FIFOSEL_CURPIPE_SHIFT)  /* Pipe 2 */
#  define R_USB_FS_D1FIFOSEL_CURPIPE_0011                 (3 << R_USB_FS_D1FIFOSEL_CURPIPE_SHIFT)  /* Pipe 3 */
#  define R_USB_FS_D1FIFOSEL_CURPIPE_0100                 (4 << R_USB_FS_D1FIFOSEL_CURPIPE_SHIFT)  /* Pipe 4 */
#  define R_USB_FS_D1FIFOSEL_CURPIPE_0101                 (5 << R_USB_FS_D1FIFOSEL_CURPIPE_SHIFT)  /* Pipe 5 */
#  define R_USB_FS_D1FIFOSEL_CURPIPE_0110                 (6 << R_USB_FS_D1FIFOSEL_CURPIPE_SHIFT)  /* Pipe 6 */
#  define R_USB_FS_D1FIFOSEL_CURPIPE_0111                 (7 << R_USB_FS_D1FIFOSEL_CURPIPE_SHIFT)  /* Pipe 7 */
#  define R_USB_FS_D1FIFOSEL_CURPIPE_1000                 (8 << R_USB_FS_D1FIFOSEL_CURPIPE_SHIFT)  /* Pipe 8 */
#  define R_USB_FS_D1FIFOSEL_CURPIPE_1001                 (9 << R_USB_FS_D1FIFOSEL_CURPIPE_SHIFT)  /* Pipe 9 */

/* D1FIFOCTR Register bit definitions */
#define R_USB_FS_D1FIFOCTR_BVAL                   (1 << 15)  /* Buffer Memory Valid Flag */

#define R_USB_FS_D1FIFOCTR_BCLR                   (1 << 14)  /* CPU Buffer ClearNote: Only 0 can be read. */

#define R_USB_FS_D1FIFOCTR_FRDY                   (1 << 13)  /* FIFO Port Ready */

#define R_USB_FS_D1FIFOCTR_DTLN_SHIFT             (0)  /* Receive Data LengthIndicates the length of the receive data. */
#define R_USB_FS_D1FIFOCTR_DTLN_MASK              0xfff

/* INTENB0 Register bit definitions */
#define R_USB_FS_INTENB0_VBSE                     (1 << 15)  /* VBUS Interrupt Enable */

#define R_USB_FS_INTENB0_RSME                     (1 << 14)  /* Resume Interrupt Enable */

#define R_USB_FS_INTENB0_SOFE                     (1 << 13)  /* Frame Number Update Interrupt Enable */

#define R_USB_FS_INTENB0_DVSE                     (1 << 12)  /* Device State Transition Interrupt Enable */

#define R_USB_FS_INTENB0_CTRE                     (1 << 11)  /* Control Transfer Stage Transition Interrupt Enable */

#define R_USB_FS_INTENB0_BEMPE                    (1 << 10)  /* Buffer Empty Interrupt Enable */

#define R_USB_FS_INTENB0_NRDYE                    (1 << 9)  /* Buffer Not Ready Response Interrupt Enable */

#define R_USB_FS_INTENB0_BRDYE                    (1 << 8)  /* Buffer Ready Interrupt Enable */

/* INTENB1 Register bit definitions */
#define R_USB_FS_INTENB1_OVRCRE                   (1 << 15)  /* Overcurrent Input Change Interrupt Enable */

#define R_USB_FS_INTENB1_BCHGE                    (1 << 14)  /* USB Bus Change Interrupt Enable */

#define R_USB_FS_INTENB1_DTCHE                    (1 << 12)  /* Disconnection Detection Interrupt Enable */

#define R_USB_FS_INTENB1_ATTCHE                   (1 << 11)  /* Connection Detection Interrupt Enable */

#define R_USB_FS_INTENB1_EOFERRE                  (1 << 6)  /* EOF Error Detection Interrupt Enable */

#define R_USB_FS_INTENB1_SIGNE                    (1 << 5)  /* Setup Transaction Error Interrupt Enable */

#define R_USB_FS_INTENB1_SACKE                    (1 << 4)  /* Setup Transaction Normal Response Interrupt Enable */

#define R_USB_FS_INTENB1_PDDETINTE0               (1 << 0)  /* PDDETINT0 Detection Interrupt Enable */

/* BRDYENB Register bit definitions */
#define R_USB_FS_BRDYENB_PIPE_SBRDYE              (1 << 0)  /* BRDY Interrupt Enable for PIPE */

#define R_USB_FS_BRDYENB_PIPE0BRDYE               (1 << 0)  /* BRDY Interrupt Enable for PIPE */

#define R_USB_FS_BRDYENB_PIPE1BRDYE               (1 << 1)  /* BRDY Interrupt Enable for PIPE */

#define R_USB_FS_BRDYENB_PIPE2BRDYE               (1 << 2)  /* BRDY Interrupt Enable for PIPE */

#define R_USB_FS_BRDYENB_PIPE3BRDYE               (1 << 3)  /* BRDY Interrupt Enable for PIPE */

#define R_USB_FS_BRDYENB_PIPE4BRDYE               (1 << 4)  /* BRDY Interrupt Enable for PIPE */

#define R_USB_FS_BRDYENB_PIPE5BRDYE               (1 << 5)  /* BRDY Interrupt Enable for PIPE */

#define R_USB_FS_BRDYENB_PIPE6BRDYE               (1 << 6)  /* BRDY Interrupt Enable for PIPE */

#define R_USB_FS_BRDYENB_PIPE7BRDYE               (1 << 7)  /* BRDY Interrupt Enable for PIPE */

#define R_USB_FS_BRDYENB_PIPE8BRDYE               (1 << 8)  /* BRDY Interrupt Enable for PIPE */

#define R_USB_FS_BRDYENB_PIPE9BRDYE               (1 << 9)  /* BRDY Interrupt Enable for PIPE */

/* NRDYENB Register bit definitions */
#define R_USB_FS_NRDYENB_PIPE_SNRDYE              (1 << 0)  /* NRDY Interrupt Enable for PIPE */

#define R_USB_FS_NRDYENB_PIPE0NRDYE               (1 << 0)  /* NRDY Interrupt Enable for PIPE */

#define R_USB_FS_NRDYENB_PIPE1NRDYE               (1 << 1)  /* NRDY Interrupt Enable for PIPE */

#define R_USB_FS_NRDYENB_PIPE2NRDYE               (1 << 2)  /* NRDY Interrupt Enable for PIPE */

#define R_USB_FS_NRDYENB_PIPE3NRDYE               (1 << 3)  /* NRDY Interrupt Enable for PIPE */

#define R_USB_FS_NRDYENB_PIPE4NRDYE               (1 << 4)  /* NRDY Interrupt Enable for PIPE */

#define R_USB_FS_NRDYENB_PIPE5NRDYE               (1 << 5)  /* NRDY Interrupt Enable for PIPE */

#define R_USB_FS_NRDYENB_PIPE6NRDYE               (1 << 6)  /* NRDY Interrupt Enable for PIPE */

#define R_USB_FS_NRDYENB_PIPE7NRDYE               (1 << 7)  /* NRDY Interrupt Enable for PIPE */

#define R_USB_FS_NRDYENB_PIPE8NRDYE               (1 << 8)  /* NRDY Interrupt Enable for PIPE */

#define R_USB_FS_NRDYENB_PIPE9NRDYE               (1 << 9)  /* NRDY Interrupt Enable for PIPE */

/* BEMPENB Register bit definitions */
#define R_USB_FS_BEMPENB_PIPE_SBEMPE              (1 << 0)  /* BEMP Interrupt Enable for PIPE */

#define R_USB_FS_BEMPENB_PIPE0BEMPE               (1 << 0)  /* BEMP Interrupt Enable for PIPE */

#define R_USB_FS_BEMPENB_PIPE1BEMPE               (1 << 1)  /* BEMP Interrupt Enable for PIPE */

#define R_USB_FS_BEMPENB_PIPE2BEMPE               (1 << 2)  /* BEMP Interrupt Enable for PIPE */

#define R_USB_FS_BEMPENB_PIPE3BEMPE               (1 << 3)  /* BEMP Interrupt Enable for PIPE */

#define R_USB_FS_BEMPENB_PIPE4BEMPE               (1 << 4)  /* BEMP Interrupt Enable for PIPE */

#define R_USB_FS_BEMPENB_PIPE5BEMPE               (1 << 5)  /* BEMP Interrupt Enable for PIPE */

#define R_USB_FS_BEMPENB_PIPE6BEMPE               (1 << 6)  /* BEMP Interrupt Enable for PIPE */

#define R_USB_FS_BEMPENB_PIPE7BEMPE               (1 << 7)  /* BEMP Interrupt Enable for PIPE */

#define R_USB_FS_BEMPENB_PIPE8BEMPE               (1 << 8)  /* BEMP Interrupt Enable for PIPE */

#define R_USB_FS_BEMPENB_PIPE9BEMPE               (1 << 9)  /* BEMP Interrupt Enable for PIPE */

/* SOFCFG Register bit definitions */
#define R_USB_FS_SOFCFG_TRNENSEL                  (1 << 8)  /* Transaction-Enabled Time Select  */

#define R_USB_FS_SOFCFG_BRDYM                     (1 << 6)  /* BRDY Interrupt Status Clear Timing */

#define R_USB_FS_SOFCFG_INTL                      (1 << 5)  /* Interrupt Output Sense Select */

#define R_USB_FS_SOFCFG_EDGESTS                   (1 << 4)  /* Edge Interrupt Output Status Monitor  */

/* PHYSET Register bit definitions */
#define R_USB_FS_PHYSET_HSEB                      (1 << 15)  /* CL-Only Mode */

#define R_USB_FS_PHYSET_REPSTART                  (1 << 11)  /* Forcibly Start Terminating Resistance Adjustment */

#define R_USB_FS_PHYSET_REPSEL_SHIFT              (8)  /* Terminating Resistance Adjustment Cycle */
#define R_USB_FS_PHYSET_REPSEL_MASK               0x300
#  define R_USB_FS_PHYSET_REPSEL_00                       (0 << R_USB_FS_PHYSET_REPSEL_SHIFT)  /* No cycle is set. */
#  define R_USB_FS_PHYSET_REPSEL_01                       (1 << R_USB_FS_PHYSET_REPSEL_SHIFT)  /* Adjust terminating resistance at 16-second intervals.  */
#  define R_USB_FS_PHYSET_REPSEL_10                       (2 << R_USB_FS_PHYSET_REPSEL_SHIFT)  /* Adjust terminating resistance at 64-second intervals. */
#  define R_USB_FS_PHYSET_REPSEL_11                       (3 << R_USB_FS_PHYSET_REPSEL_SHIFT)  /* Adjust terminating resistance at 128-second intervals. */

#define R_USB_FS_PHYSET_CLKSEL_SHIFT              (4)  /* Input System Clock Frequency */
#define R_USB_FS_PHYSET_CLKSEL_MASK               0x30
#  define R_USB_FS_PHYSET_CLKSEL_00                       (0 << R_USB_FS_PHYSET_CLKSEL_SHIFT)  /* Setting Prohibited */
#  define R_USB_FS_PHYSET_CLKSEL_01                       (1 << R_USB_FS_PHYSET_CLKSEL_SHIFT)  /* 12 MHz */
#  define R_USB_FS_PHYSET_CLKSEL_10                       (2 << R_USB_FS_PHYSET_CLKSEL_SHIFT)  /* 20 MHz */
#  define R_USB_FS_PHYSET_CLKSEL_11                       (3 << R_USB_FS_PHYSET_CLKSEL_SHIFT)  /* 24 MHz */

#define R_USB_FS_PHYSET_CDPEN                     (1 << 3)  /* Charging Downstream Port Enable */

#define R_USB_FS_PHYSET_PLLRESET                  (1 << 1)  /* PLL Reset Control */

#define R_USB_FS_PHYSET_DIRPD                     (1 << 0)  /* Power-Down Control */

/* INTSTS0 Register bit definitions */
#define R_USB_FS_INTSTS0_VBINT                    (1 << 15)  /* VBUS Interrupt Status */

#define R_USB_FS_INTSTS0_RESM                     (1 << 14)  /* Resume Interrupt Status */

#define R_USB_FS_INTSTS0_SOFR                     (1 << 13)  /* Frame Number Refresh Interrupt Status */

#define R_USB_FS_INTSTS0_DVST                     (1 << 12)  /* Device State Transition Interrupt Status */

#define R_USB_FS_INTSTS0_CTRT                     (1 << 11)  /* Control Transfer Stage Transition Interrupt Status */

#define R_USB_FS_INTSTS0_BEMP                     (1 << 10)  /* Buffer Empty Interrupt Status */

#define R_USB_FS_INTSTS0_NRDY                     (1 << 9)  /* Buffer Not Ready Interrupt Status */

#define R_USB_FS_INTSTS0_BRDY                     (1 << 8)  /* Buffer Ready Interrupt Status */

#define R_USB_FS_INTSTS0_VBSTS                    (1 << 7)  /* VBUS Input Status */

#define R_USB_FS_INTSTS0_DVSQ_SHIFT               (4)  /* Device State */
#define R_USB_FS_INTSTS0_DVSQ_MASK                0x70
#  define R_USB_FS_INTSTS0_DVSQ_000                       (0 << R_USB_FS_INTSTS0_DVSQ_SHIFT)  /* Powered state */
#  define R_USB_FS_INTSTS0_DVSQ_001                       (1 << R_USB_FS_INTSTS0_DVSQ_SHIFT)  /* Default state */
#  define R_USB_FS_INTSTS0_DVSQ_010                       (2 << R_USB_FS_INTSTS0_DVSQ_SHIFT)  /* Address state */
#  define R_USB_FS_INTSTS0_DVSQ_011                       (3 << R_USB_FS_INTSTS0_DVSQ_SHIFT)  /* Configured state */

#define R_USB_FS_INTSTS0_VALID                    (1 << 3)  /* USB Request Reception */

#define R_USB_FS_INTSTS0_CTSQ_SHIFT               (0)  /* Control Transfer Stage */
#define R_USB_FS_INTSTS0_CTSQ_MASK                0x7
#  define R_USB_FS_INTSTS0_CTSQ_000                       (0 << R_USB_FS_INTSTS0_CTSQ_SHIFT)  /* Idle or setup stage */
#  define R_USB_FS_INTSTS0_CTSQ_001                       (1 << R_USB_FS_INTSTS0_CTSQ_SHIFT)  /* Control read data stage */
#  define R_USB_FS_INTSTS0_CTSQ_010                       (2 << R_USB_FS_INTSTS0_CTSQ_SHIFT)  /* Control read status stage */
#  define R_USB_FS_INTSTS0_CTSQ_011                       (3 << R_USB_FS_INTSTS0_CTSQ_SHIFT)  /* Control write data stage */
#  define R_USB_FS_INTSTS0_CTSQ_100                       (4 << R_USB_FS_INTSTS0_CTSQ_SHIFT)  /* Control write status stage */
#  define R_USB_FS_INTSTS0_CTSQ_101                       (5 << R_USB_FS_INTSTS0_CTSQ_SHIFT)  /* Control write (no data) status stage */
#  define R_USB_FS_INTSTS0_CTSQ_110                       (6 << R_USB_FS_INTSTS0_CTSQ_SHIFT)  /* Control transfer sequence error */

/* INTSTS1 Register bit definitions */
#define R_USB_FS_INTSTS1_OVRCR                    (1 << 15)  /* Overcurrent Input Change Interrupt Status */

#define R_USB_FS_INTSTS1_BCHG                     (1 << 14)  /* USB Bus Change Interrupt Status */

#define R_USB_FS_INTSTS1_DTCH                     (1 << 12)  /* USB Disconnection Detection Interrupt Status */

#define R_USB_FS_INTSTS1_ATTCH                    (1 << 11)  /* ATTCH Interrupt Status */

#define R_USB_FS_INTSTS1_L1RSMEND                 (1 << 9)  /* L1 Resume End Interrupt Status */

#define R_USB_FS_INTSTS1_LPMEND                   (1 << 8)  /* LPM Transaction End Interrupt Status */

#define R_USB_FS_INTSTS1_EOFERR                   (1 << 6)  /* EOF Error Detection Interrupt Status */

#define R_USB_FS_INTSTS1_SIGN                     (1 << 5)  /* Setup Transaction Error Interrupt Status */

#define R_USB_FS_INTSTS1_SACK                     (1 << 4)  /* Setup Transaction Normal Response Interrupt Status */

#define R_USB_FS_INTSTS1_PDDETINT0                (1 << 0)  /* PDDET0 Detection Interrupt Status */

/* BRDYSTS Register bit definitions */
#define R_USB_FS_BRDYSTS_PIPE_SBRDY               (1 << 0)  /* BRDY Interrupt Status for PIPE */

#define R_USB_FS_BRDYSTS_PIPE0BRDY                (1 << 0)  /* BRDY Interrupt Status for PIPE */

#define R_USB_FS_BRDYSTS_PIPE1BRDY                (1 << 1)  /* BRDY Interrupt Status for PIPE */

#define R_USB_FS_BRDYSTS_PIPE2BRDY                (1 << 2)  /* BRDY Interrupt Status for PIPE */

#define R_USB_FS_BRDYSTS_PIPE3BRDY                (1 << 3)  /* BRDY Interrupt Status for PIPE */

#define R_USB_FS_BRDYSTS_PIPE4BRDY                (1 << 4)  /* BRDY Interrupt Status for PIPE */

#define R_USB_FS_BRDYSTS_PIPE5BRDY                (1 << 5)  /* BRDY Interrupt Status for PIPE */

#define R_USB_FS_BRDYSTS_PIPE6BRDY                (1 << 6)  /* BRDY Interrupt Status for PIPE */

#define R_USB_FS_BRDYSTS_PIPE7BRDY                (1 << 7)  /* BRDY Interrupt Status for PIPE */

#define R_USB_FS_BRDYSTS_PIPE8BRDY                (1 << 8)  /* BRDY Interrupt Status for PIPE */

#define R_USB_FS_BRDYSTS_PIPE9BRDY                (1 << 9)  /* BRDY Interrupt Status for PIPE */

/* NRDYSTS Register bit definitions */
#define R_USB_FS_NRDYSTS_PIPE_SNRDY               (1 << 0)  /* NRDY Interrupt Status for PIPE */

#define R_USB_FS_NRDYSTS_PIPE0NRDY                (1 << 0)  /* NRDY Interrupt Status for PIPE */

#define R_USB_FS_NRDYSTS_PIPE1NRDY                (1 << 1)  /* NRDY Interrupt Status for PIPE */

#define R_USB_FS_NRDYSTS_PIPE2NRDY                (1 << 2)  /* NRDY Interrupt Status for PIPE */

#define R_USB_FS_NRDYSTS_PIPE3NRDY                (1 << 3)  /* NRDY Interrupt Status for PIPE */

#define R_USB_FS_NRDYSTS_PIPE4NRDY                (1 << 4)  /* NRDY Interrupt Status for PIPE */

#define R_USB_FS_NRDYSTS_PIPE5NRDY                (1 << 5)  /* NRDY Interrupt Status for PIPE */

#define R_USB_FS_NRDYSTS_PIPE6NRDY                (1 << 6)  /* NRDY Interrupt Status for PIPE */

#define R_USB_FS_NRDYSTS_PIPE7NRDY                (1 << 7)  /* NRDY Interrupt Status for PIPE */

#define R_USB_FS_NRDYSTS_PIPE8NRDY                (1 << 8)  /* NRDY Interrupt Status for PIPE */

#define R_USB_FS_NRDYSTS_PIPE9NRDY                (1 << 9)  /* NRDY Interrupt Status for PIPE */

/* BEMPSTS Register bit definitions */
#define R_USB_FS_BEMPSTS_PIPE_SBEMP               (1 << 0)  /* BEMP Interrupt Status for PIPE */

#define R_USB_FS_BEMPSTS_PIPE0BEMP                (1 << 0)  /* BEMP Interrupt Status for PIPE */

#define R_USB_FS_BEMPSTS_PIPE1BEMP                (1 << 1)  /* BEMP Interrupt Status for PIPE */

#define R_USB_FS_BEMPSTS_PIPE2BEMP                (1 << 2)  /* BEMP Interrupt Status for PIPE */

#define R_USB_FS_BEMPSTS_PIPE3BEMP                (1 << 3)  /* BEMP Interrupt Status for PIPE */

#define R_USB_FS_BEMPSTS_PIPE4BEMP                (1 << 4)  /* BEMP Interrupt Status for PIPE */

#define R_USB_FS_BEMPSTS_PIPE5BEMP                (1 << 5)  /* BEMP Interrupt Status for PIPE */

#define R_USB_FS_BEMPSTS_PIPE6BEMP                (1 << 6)  /* BEMP Interrupt Status for PIPE */

#define R_USB_FS_BEMPSTS_PIPE7BEMP                (1 << 7)  /* BEMP Interrupt Status for PIPE */

#define R_USB_FS_BEMPSTS_PIPE8BEMP                (1 << 8)  /* BEMP Interrupt Status for PIPE */

#define R_USB_FS_BEMPSTS_PIPE9BEMP                (1 << 9)  /* BEMP Interrupt Status for PIPE */

/* FRMNUM Register bit definitions */
#define R_USB_FS_FRMNUM_OVRN                      (1 << 15)  /* Overrun/Underrun Detection Status */

#define R_USB_FS_FRMNUM_CRCE                      (1 << 14)  /* Receive Data Error */

#define R_USB_FS_FRMNUM_FRNM_SHIFT                (0)  /* Frame NumberLatest frame number */
#define R_USB_FS_FRMNUM_FRNM_MASK                 0x7ff

/* DVCHGR Register bit definitions */
#define R_USB_FS_DVCHGR_DVCHG                     (1 << 15)  /* Device State Change */

/* USBADDR Register bit definitions */
#define R_USB_FS_USBADDR_STSRECOV0_SHIFT          (8)  /* Status Recovery */
#define R_USB_FS_USBADDR_STSRECOV0_MASK           0xf00
#  define R_USB_FS_USBADDR_STSRECOV0_001                  (1 << R_USB_FS_USBADDR_STSRECOV0_SHIFT)  /* Return to the full-speed state(bits DVSTCTR0.RHST[2:0] = 010b), bits INTSTS0.DVSQ[2:0] = 001b (Default state)(function controller selected) */
#  define R_USB_FS_USBADDR_STSRECOV0_010                  (2 << R_USB_FS_USBADDR_STSRECOV0_SHIFT)  /* Return to the full-speed state (bits DVSTCTR0.RHST[2:0] = 010b), bits INTSTS0.DVSQ[2:0] = 010b (Address state)(function controller selected)/ Return to the low-speed state (bitsDVSTCTR0.RHST[2:0] = 001b)(host controller is selected) */
#  define R_USB_FS_USBADDR_STSRECOV0_011                  (3 << R_USB_FS_USBADDR_STSRECOV0_SHIFT)  /* Return to the full-speed state (bits DVSTCTR0.RHST[2:0] = 010b), bits INTSTS0.DVSQ[2:0] = 011b (Configured state)(function controller selected) */
#  define R_USB_FS_USBADDR_STSRECOV0_100                  (4 << R_USB_FS_USBADDR_STSRECOV0_SHIFT)  /* Return to the full-speed state (bits DVSTCTR0.RHST[2:0] = 010b)(host controller selected) */
#  define R_USB_FS_USBADDR_STSRECOV0_101                  (5 << R_USB_FS_USBADDR_STSRECOV0_SHIFT)  /* Return to the high-speed state (bits DVSTCTR0.RHST[2:0] = 011b), bits INTSTS0.DVSQ[2:0] = 001b (Default state)(function controller selected) */
#  define R_USB_FS_USBADDR_STSRECOV0_110                  (6 << R_USB_FS_USBADDR_STSRECOV0_SHIFT)  /* Return to the high-speed state (bits DVSTCTR0.RHST[2:0] = 011b), bits INTSTS0.DVSQ[2:0] = 010b (Address state)(function controller selected)/ Return to the high-speed state (bits DVSTCTR0.RHST[2:0] = 011b)(host controller selected) */
#  define R_USB_FS_USBADDR_STSRECOV0_111                  (7 << R_USB_FS_USBADDR_STSRECOV0_SHIFT)  /* Return to the high-speed state (bits DVSTCTR0.RHST[2:0] = 011b), bits INTSTS0.DVSQ[2:0] = 011b (Configured state)(function controller selected) */

#define R_USB_FS_USBADDR_USBADDR_SHIFT            (0)  /* USB Address In device controller mode, these flags indicate the USB address assigned by the host when the USBHS processed the SET_ADDRESS request successfully. */
#define R_USB_FS_USBADDR_USBADDR_MASK             0x7f

/* USBREQ Register bit definitions */
#define R_USB_FS_USBREQ_BREQUEST_SHIFT            (8)  /* RequestThese bits store the USB request bRequest value. */
#define R_USB_FS_USBREQ_BREQUEST_MASK             0xff00

#define R_USB_FS_USBREQ_BMREQUESTTYPE_SHIFT       (0)  /* Request TypeThese bits store the USB request bmRequestType value. */
#define R_USB_FS_USBREQ_BMREQUESTTYPE_MASK        0xff

/* USBVAL Register bit definitions */
#define R_USB_FS_USBVAL_WVALUE_SHIFT              (0)  /* ValueThese bits store the USB request Value value. */
#define R_USB_FS_USBVAL_WVALUE_MASK               0xffff

/* USBINDX Register bit definitions */
#define R_USB_FS_USBINDX_WINDEX_SHIFT             (0)  /* IndexThese bits store the USB request wIndex value. */
#define R_USB_FS_USBINDX_WINDEX_MASK              0xffff

/* USBLENG Register bit definitions */
#define R_USB_FS_USBLENG_WLENGTH_SHIFT            (0)  /* LengthThese bits store the USB request wLength value. */
#define R_USB_FS_USBLENG_WLENGTH_MASK             0xffff

/* DCPCFG Register bit definitions */
#define R_USB_FS_DCPCFG_CNTMD                     (1 << 8)  /* Continuous Transfer Mode */

#define R_USB_FS_DCPCFG_SHTNAK                    (1 << 7)  /* Pipe Disabled at End of Transfer */

#define R_USB_FS_DCPCFG_DIR                       (1 << 4)  /* Transfer Direction */

/* DCPMAXP Register bit definitions */
#define R_USB_FS_DCPMAXP_DEVSEL_SHIFT             (12)  /* Device Select */
#define R_USB_FS_DCPMAXP_DEVSEL_MASK              0xf000
#  define R_USB_FS_DCPMAXP_DEVSEL_0000                    (0 << R_USB_FS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0000 */
#  define R_USB_FS_DCPMAXP_DEVSEL_0001                    (1 << R_USB_FS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0001 */
#  define R_USB_FS_DCPMAXP_DEVSEL_0010                    (2 << R_USB_FS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0010 */
#  define R_USB_FS_DCPMAXP_DEVSEL_0011                    (3 << R_USB_FS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0011 */
#  define R_USB_FS_DCPMAXP_DEVSEL_0100                    (4 << R_USB_FS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0100 */
#  define R_USB_FS_DCPMAXP_DEVSEL_0101                    (5 << R_USB_FS_DCPMAXP_DEVSEL_SHIFT)  /* Address 0101 */

#define R_USB_FS_DCPMAXP_MXPS_SHIFT               (0)  /* Maximum Packet SizeThese bits set the maximum amount of data (maximum packet size) in payloads for the DCP. */
#define R_USB_FS_DCPMAXP_MXPS_MASK                0x7f
#  define R_USB_FS_DCPMAXP_MXPS_0X08                      (8 << R_USB_FS_DCPMAXP_MXPS_SHIFT)  /* 8 bytes */
#  define R_USB_FS_DCPMAXP_MXPS_0X10                      (16 << R_USB_FS_DCPMAXP_MXPS_SHIFT)  /* 16 bytes */
#  define R_USB_FS_DCPMAXP_MXPS_0X18                      (24 << R_USB_FS_DCPMAXP_MXPS_SHIFT)  /* 24 bytes */
#  define R_USB_FS_DCPMAXP_MXPS_0X20                      (32 << R_USB_FS_DCPMAXP_MXPS_SHIFT)  /* 32 bytes */
#  define R_USB_FS_DCPMAXP_MXPS_0X28                      (40 << R_USB_FS_DCPMAXP_MXPS_SHIFT)  /* 40 bytes */
#  define R_USB_FS_DCPMAXP_MXPS_0X30                      (48 << R_USB_FS_DCPMAXP_MXPS_SHIFT)  /* 48 bytes */
#  define R_USB_FS_DCPMAXP_MXPS_0X38                      (56 << R_USB_FS_DCPMAXP_MXPS_SHIFT)  /* 56 bytes */
#  define R_USB_FS_DCPMAXP_MXPS_0X40                      (64 << R_USB_FS_DCPMAXP_MXPS_SHIFT)  /* 64 bytes */
#  define R_USB_FS_DCPMAXP_MXPS_0X48                      (72 << R_USB_FS_DCPMAXP_MXPS_SHIFT)  /* 72 bytes */
#  define R_USB_FS_DCPMAXP_MXPS_0X50                      (80 << R_USB_FS_DCPMAXP_MXPS_SHIFT)  /* 80 bytes */
#  define R_USB_FS_DCPMAXP_MXPS_0X58                      (88 << R_USB_FS_DCPMAXP_MXPS_SHIFT)  /* 88 bytes */
#  define R_USB_FS_DCPMAXP_MXPS_0X60                      (96 << R_USB_FS_DCPMAXP_MXPS_SHIFT)  /* 96 bytes */
#  define R_USB_FS_DCPMAXP_MXPS_0X68                      (104 << R_USB_FS_DCPMAXP_MXPS_SHIFT)  /* 104 bytes */
#  define R_USB_FS_DCPMAXP_MXPS_0X70                      (112 << R_USB_FS_DCPMAXP_MXPS_SHIFT)  /* 112 bytes */
#  define R_USB_FS_DCPMAXP_MXPS_0X78                      (120 << R_USB_FS_DCPMAXP_MXPS_SHIFT)  /* 120 bytes */

/* DCPCTR Register bit definitions */
#define R_USB_FS_DCPCTR_BSTS                      (1 << 15)  /* Buffer Status */

#define R_USB_FS_DCPCTR_SUREQ                     (1 << 14)  /* Setup Token Transmission */

#define R_USB_FS_DCPCTR_SUREQCLR                  (1 << 11)  /* SUREQ Bit Clear */

#define R_USB_FS_DCPCTR_SQCLR                     (1 << 8)  /* Sequence Toggle Bit Clear */

#define R_USB_FS_DCPCTR_SQSET                     (1 << 7)  /* Sequence Toggle Bit Set */

#define R_USB_FS_DCPCTR_SQMON                     (1 << 6)  /* Sequence Toggle Bit Monitor */

#define R_USB_FS_DCPCTR_PBUSY                     (1 << 5)  /* Pipe Busy */

#define R_USB_FS_DCPCTR_CCPL                      (1 << 2)  /* Control Transfer End Enable */

#define R_USB_FS_DCPCTR_PID_SHIFT                 (0)  /* Response PID */
#define R_USB_FS_DCPCTR_PID_MASK                  0x3
#  define R_USB_FS_DCPCTR_PID_00                          (0 << R_USB_FS_DCPCTR_PID_SHIFT)  /* NAK response */
#  define R_USB_FS_DCPCTR_PID_01                          (1 << R_USB_FS_DCPCTR_PID_SHIFT)  /* BUF response (depending on the buffer state) */
#  define R_USB_FS_DCPCTR_PID_10                          (2 << R_USB_FS_DCPCTR_PID_SHIFT)  /* STALL response */
#  define R_USB_FS_DCPCTR_PID_11                          (3 << R_USB_FS_DCPCTR_PID_SHIFT)  /* STALL response */

/* PIPESEL Register bit definitions */
#define R_USB_FS_PIPESEL_PIPESEL_SHIFT            (0)  /* Pipe Window Select */
#define R_USB_FS_PIPESEL_PIPESEL_MASK             0xf
#  define R_USB_FS_PIPESEL_PIPESEL_0000                   (0 << R_USB_FS_PIPESEL_PIPESEL_SHIFT)  /* No pipe selected */
#  define R_USB_FS_PIPESEL_PIPESEL_0001                   (1 << R_USB_FS_PIPESEL_PIPESEL_SHIFT)  /* PIPE1 */
#  define R_USB_FS_PIPESEL_PIPESEL_0010                   (2 << R_USB_FS_PIPESEL_PIPESEL_SHIFT)  /* PIPE2 */
#  define R_USB_FS_PIPESEL_PIPESEL_0011                   (3 << R_USB_FS_PIPESEL_PIPESEL_SHIFT)  /* PIPE3 */
#  define R_USB_FS_PIPESEL_PIPESEL_0100                   (4 << R_USB_FS_PIPESEL_PIPESEL_SHIFT)  /* PIPE4 */
#  define R_USB_FS_PIPESEL_PIPESEL_0101                   (5 << R_USB_FS_PIPESEL_PIPESEL_SHIFT)  /* PIPE5 */
#  define R_USB_FS_PIPESEL_PIPESEL_0110                   (6 << R_USB_FS_PIPESEL_PIPESEL_SHIFT)  /* PIPE6 */
#  define R_USB_FS_PIPESEL_PIPESEL_0111                   (7 << R_USB_FS_PIPESEL_PIPESEL_SHIFT)  /* PIPE7 */
#  define R_USB_FS_PIPESEL_PIPESEL_1000                   (8 << R_USB_FS_PIPESEL_PIPESEL_SHIFT)  /* PIPE8 */
#  define R_USB_FS_PIPESEL_PIPESEL_1001                   (9 << R_USB_FS_PIPESEL_PIPESEL_SHIFT)  /* PIPE9 */

/* PIPECFG Register bit definitions */
#define R_USB_FS_PIPECFG_TYPE_SHIFT               (14)  /* Transfer Type */
#define R_USB_FS_PIPECFG_TYPE_MASK                0xc000
#  define R_USB_FS_PIPECFG_TYPE_00                        (0 << R_USB_FS_PIPECFG_TYPE_SHIFT)  /* Pipe not used */
#  define R_USB_FS_PIPECFG_TYPE_01                        (1 << R_USB_FS_PIPECFG_TYPE_SHIFT)  /* Bulk transfer(PIPE1 and PIPE5) /Setting prohibited(PIPE6 to PIPE9) */
#  define R_USB_FS_PIPECFG_TYPE_10                        (2 << R_USB_FS_PIPECFG_TYPE_SHIFT)  /* Setting prohibited(PIPE1 and PIPE5) /Interrupt transfer(PIPE6 to PIPE9) */
#  define R_USB_FS_PIPECFG_TYPE_11                        (3 << R_USB_FS_PIPECFG_TYPE_SHIFT)  /* Isochronous transfer(PIPE1 and PIPE2) /Setting prohibited(PIPE3 to PIPE9)  */

#define R_USB_FS_PIPECFG_BFRE                     (1 << 10)  /* BRDY Interrupt Operation Specification */

#define R_USB_FS_PIPECFG_DBLB                     (1 << 9)  /* Double Buffer Mode */

#define R_USB_FS_PIPECFG_SHTNAK                   (1 << 7)  /* Pipe Disabled at End of Transfer */

#define R_USB_FS_PIPECFG_DIR                      (1 << 4)  /* Transfer Direction */

#define R_USB_FS_PIPECFG_EPNUM_SHIFT              (0)  /* Endpoint NumberThese bits specify the endpoint number for the selected pipe.Setting 0000b means unused pipe.  */
#define R_USB_FS_PIPECFG_EPNUM_MASK               0xf

/* PIPEMAXP Register bit definitions */
#define R_USB_FS_PIPEMAXP_DEVSEL_SHIFT            (12)  /* Device Select */
#define R_USB_FS_PIPEMAXP_DEVSEL_MASK             0xf000
#  define R_USB_FS_PIPEMAXP_DEVSEL_0000                   (0 << R_USB_FS_PIPEMAXP_DEVSEL_SHIFT)  /* Address 0000 */
#  define R_USB_FS_PIPEMAXP_DEVSEL_0001                   (1 << R_USB_FS_PIPEMAXP_DEVSEL_SHIFT)  /* Address 0001 */
#  define R_USB_FS_PIPEMAXP_DEVSEL_0010                   (2 << R_USB_FS_PIPEMAXP_DEVSEL_SHIFT)  /* Address 0010 */
#  define R_USB_FS_PIPEMAXP_DEVSEL_0011                   (3 << R_USB_FS_PIPEMAXP_DEVSEL_SHIFT)  /* Address 0011 */
#  define R_USB_FS_PIPEMAXP_DEVSEL_0100                   (4 << R_USB_FS_PIPEMAXP_DEVSEL_SHIFT)  /* Address 0100 */
#  define R_USB_FS_PIPEMAXP_DEVSEL_0101                   (5 << R_USB_FS_PIPEMAXP_DEVSEL_SHIFT)  /* Address 0101 */

#define R_USB_FS_PIPEMAXP_MXPS_SHIFT              (0)  /* Maximum Packet SizePIPE1 and PIPE2:  1 byte (001h) to 256 bytes (100h)PIPE3 to PIPE5:   8 bytes (008h), 16 bytes (010h),  32 bytes (020h), 64 bytes (040h)   (Bits [8:7] and [2:0] are not provided.)PIPE6 to PIPE9:  1 byte (001h) to 64 bytes (040h)  (Bits [8:7] are not provided.) */
#define R_USB_FS_PIPEMAXP_MXPS_MASK               0x1ff

/* PIPEPERI Register bit definitions */
#define R_USB_FS_PIPEPERI_IFIS                    (1 << 12)  /* Isochronous IN Buffer Flush */

#define R_USB_FS_PIPEPERI_IITV_SHIFT              (0)  /* Interval Error Detection IntervalSpecifies the interval error detection timing for the selected pipe in terms of frames, which is expressed as nth power of 2. */
#define R_USB_FS_PIPEPERI_IITV_MASK               0x7

/* PIPE_CTR Register bit definitions */
#define R_USB_FS_PIPE_CTR_BSTS                    (1 << 15)  /* Buffer Status */

#define R_USB_FS_PIPE_CTR_INBUFM                  (1 << 14)  /* Transmit Buffer Monitor */

#define R_USB_FS_PIPE_CTR_CSCLR                   (1 << 13)  /* CSPLIT Status ClearSet this bit to 1 when clearing the CSSTS bit of the relevant pipe */

#define R_USB_FS_PIPE_CTR_CSSTS                   (1 << 12)  /* CSSTS StatusThis bit indicates the CSPLIT status of Split Transaction of the relevant pipe */

#define R_USB_FS_PIPE_CTR_ATREPM                  (1 << 10)  /* Auto Response Mode */

#define R_USB_FS_PIPE_CTR_ACLRM                   (1 << 9)  /* Auto Buffer Clear Mode */

#define R_USB_FS_PIPE_CTR_SQCLR                   (1 << 8)  /* Sequence Toggle Bit Clear */

#define R_USB_FS_PIPE_CTR_SQSET                   (1 << 7)  /* Sequence Toggle Bit Set */

#define R_USB_FS_PIPE_CTR_SQMON                   (1 << 6)  /* Sequence Toggle Bit Confirmation */

#define R_USB_FS_PIPE_CTR_PBUSY                   (1 << 5)  /* Pipe Busy */

#define R_USB_FS_PIPE_CTR_PID_SHIFT               (0)  /* Response PID */
#define R_USB_FS_PIPE_CTR_PID_MASK                0x3
#  define R_USB_FS_PIPE_CTR_PID_00                        (0 << R_USB_FS_PIPE_CTR_PID_SHIFT)  /* NAK response */
#  define R_USB_FS_PIPE_CTR_PID_01                        (1 << R_USB_FS_PIPE_CTR_PID_SHIFT)  /* BUF response (depending on the buffer state) */
#  define R_USB_FS_PIPE_CTR_PID_10                        (2 << R_USB_FS_PIPE_CTR_PID_SHIFT)  /* STALL response */
#  define R_USB_FS_PIPE_CTR_PID_11                        (3 << R_USB_FS_PIPE_CTR_PID_SHIFT)  /* STALL response */

/* DEVADD Register bit definitions */
#define R_USB_FS_DEVADD_UPPHUB_SHIFT              (11)  /* Communication Target Connecting Hub Register */
#define R_USB_FS_DEVADD_UPPHUB_MASK               0x7800
#  define R_USB_FS_DEVADD_UPPHUB_0000                     (0 << R_USB_FS_DEVADD_UPPHUB_SHIFT)  /* Directly connected to the port of the USBHS. */

#define R_USB_FS_DEVADD_HUBPORT_SHIFT             (8)  /* Communication Target Connecting Hub Port */
#define R_USB_FS_DEVADD_HUBPORT_MASK              0x700
#  define R_USB_FS_DEVADD_HUBPORT_000                     (0 << R_USB_FS_DEVADD_HUBPORT_SHIFT)  /* Directly connected to the port of the USBHS.  */

#define R_USB_FS_DEVADD_USBSPD_SHIFT              (6)  /* Transfer Speed of Communication Target Device */
#define R_USB_FS_DEVADD_USBSPD_MASK               0xc0
#  define R_USB_FS_DEVADD_USBSPD_00                       (0 << R_USB_FS_DEVADD_USBSPD_SHIFT)  /* DEVADDn is not used */
#  define R_USB_FS_DEVADD_USBSPD_01                       (1 << R_USB_FS_DEVADD_USBSPD_SHIFT)  /* Low speed */
#  define R_USB_FS_DEVADD_USBSPD_10                       (2 << R_USB_FS_DEVADD_USBSPD_SHIFT)  /* Full speed */
#  define R_USB_FS_DEVADD_USBSPD_11                       (3 << R_USB_FS_DEVADD_USBSPD_SHIFT)  /* Setting prohibited */

/* USBBCCTRL0 Register bit definitions */
#define R_USB_FS_USBBCCTRL0_PDDETSTS0             (1 << 9)  /* D+ Pin 0.6 V Input Detection Status */

#define R_USB_FS_USBBCCTRL0_CHGDETSTS0            (1 << 8)  /* D- Pin 0.6 V Input Detection Status */

#define R_USB_FS_USBBCCTRL0_BATCHGE0              (1 << 7)  /* BC (Battery Charger) Function Ch0 General Enable Control */

#define R_USB_FS_USBBCCTRL0_VDMSRCE0              (1 << 5)  /* D- Pin VDMSRC (0.6 V) Output Control */

#define R_USB_FS_USBBCCTRL0_IDPSINKE0             (1 << 4)  /* D+ Pin 0.6 V Input Detection (Comparator and Sink) Control */

#define R_USB_FS_USBBCCTRL0_VDPSRCE0              (1 << 3)  /* D+ Pin VDPSRC (0.6 V) Output Control */

#define R_USB_FS_USBBCCTRL0_IDMSINKE0             (1 << 2)  /* D- Pin 0.6 V Input Detection (Comparator and Sink) Control */

#define R_USB_FS_USBBCCTRL0_IDPSRCE0              (1 << 1)  /* D+ Pin IDPSRC Output Control */

#define R_USB_FS_USBBCCTRL0_RPDME0                (1 << 0)  /* D- Pin Pull-Down Control */

/* UCKSEL Register bit definitions */
#define R_USB_FS_UCKSEL_UCKSELC                   (1 << 0)  /* USB Clock Selection */

/* USBMC Register bit definitions */
#define R_USB_FS_USBMC_VDCEN                      (1 << 7)  /* USB Regulator On/Off Control */

#define R_USB_FS_USBMC_VDDUSBE                    (1 << 0)  /* USB Reference Power Supply Circuit On/Off Control */

/* PHYSLEW Register bit definitions */
#define R_USB_FS_PHYSLEW_SLEWF01                  (1 << 3)  /* Receiver Cross Point Adjustment 01 */

#define R_USB_FS_PHYSLEW_SLEWF00                  (1 << 2)  /* Receiver Cross Point Adjustment 00 */

#define R_USB_FS_PHYSLEW_SLEWR01                  (1 << 1)  /* Receiver Cross Point Adjustment 01 */

#define R_USB_FS_PHYSLEW_SLEWR00                  (1 << 0)  /* Receiver Cross Point Adjustment 00 */

/* LPCTRL Register bit definitions */
#define R_USB_FS_LPCTRL_HWUPM                     (1 << 7)  /* Resume Return Mode Setting */

/* LPSTS Register bit definitions */
#define R_USB_FS_LPSTS_SUSPENDM                   (1 << 14)  /* UTMI SuspendM Control */

/* BCCTRL Register bit definitions */
#define R_USB_FS_BCCTRL_PDDETSTS                  (1 << 9)  /* PDDET Status */

#define R_USB_FS_BCCTRL_CHGDETSTS                 (1 << 8)  /* CHGDET Status */

#define R_USB_FS_BCCTRL_DCPMODE                   (1 << 5)  /* DCP Mode Control */

#define R_USB_FS_BCCTRL_VDMSRCE                   (1 << 4)  /* VDMSRC Control */

#define R_USB_FS_BCCTRL_IDPSINKE                  (1 << 3)  /* IDPSINK Control */

#define R_USB_FS_BCCTRL_VDPSRCE                   (1 << 2)  /* VDPSRC Control */

#define R_USB_FS_BCCTRL_IDMSINKE                  (1 << 1)  /* IDMSINK Control */

#define R_USB_FS_BCCTRL_IDPSRCE                   (1 << 0)  /* IDPSRC Control */

/* PL1CTRL1 Register bit definitions */
#define R_USB_FS_PL1CTRL1_L1EXTMD                 (1 << 14)  /* PHY Control Mode at L1 Return */

#define R_USB_FS_PL1CTRL1_HIRDTHR_SHIFT           (8)  /* L1 Response Negotiation Threshold ValueHIRD threshold value used for L1NEGOMD.The format is the same as the HIRD field in HL1CTRL. */
#define R_USB_FS_PL1CTRL1_HIRDTHR_MASK            0xf00

#define R_USB_FS_PL1CTRL1_DVSQ_SHIFT              (4)  /* DVSQ Extension.DVSQ[3] is Mirror of DVSQ[2:0] in INTSTS0.Indicates the L1 state together with the device state bits DVSQ[2:0]. */
#define R_USB_FS_PL1CTRL1_DVSQ_MASK               0xf0
#  define R_USB_FS_PL1CTRL1_DVSQ_0000                     (0 << R_USB_FS_PL1CTRL1_DVSQ_SHIFT)  /* Powered state */
#  define R_USB_FS_PL1CTRL1_DVSQ_0001                     (1 << R_USB_FS_PL1CTRL1_DVSQ_SHIFT)  /* Default state */
#  define R_USB_FS_PL1CTRL1_DVSQ_0010                     (2 << R_USB_FS_PL1CTRL1_DVSQ_SHIFT)  /* Address state */
#  define R_USB_FS_PL1CTRL1_DVSQ_0011                     (3 << R_USB_FS_PL1CTRL1_DVSQ_SHIFT)  /* Configured state */
#  define R_USB_FS_PL1CTRL1_DVSQ_0100                     (4 << R_USB_FS_PL1CTRL1_DVSQ_SHIFT)  /* Suspended state */
#  define R_USB_FS_PL1CTRL1_DVSQ_0101                     (5 << R_USB_FS_PL1CTRL1_DVSQ_SHIFT)  /* Suspended state */
#  define R_USB_FS_PL1CTRL1_DVSQ_0110                     (6 << R_USB_FS_PL1CTRL1_DVSQ_SHIFT)  /* Suspended state */
#  define R_USB_FS_PL1CTRL1_DVSQ_0111                     (7 << R_USB_FS_PL1CTRL1_DVSQ_SHIFT)  /* Suspended state */
#  define R_USB_FS_PL1CTRL1_DVSQ_1000                     (8 << R_USB_FS_PL1CTRL1_DVSQ_SHIFT)  /* L1 state */
#  define R_USB_FS_PL1CTRL1_DVSQ_1001                     (9 << R_USB_FS_PL1CTRL1_DVSQ_SHIFT)  /* L1 state */
#  define R_USB_FS_PL1CTRL1_DVSQ_1010                     (10 << R_USB_FS_PL1CTRL1_DVSQ_SHIFT)  /* L1 state */
#  define R_USB_FS_PL1CTRL1_DVSQ_1011                     (11 << R_USB_FS_PL1CTRL1_DVSQ_SHIFT)  /* L1 state */

#define R_USB_FS_PL1CTRL1_L1NEGOMD                (1 << 3)  /* L1 Response Negotiation Control.NOTE: This bit is valid only when the L1RESPMD[1:0] value is 2'b11. */

#define R_USB_FS_PL1CTRL1_L1RESPMD_SHIFT          (1)  /* L1 Response Mode */
#define R_USB_FS_PL1CTRL1_L1RESPMD_MASK           0x6
#  define R_USB_FS_PL1CTRL1_L1RESPMD_00                   (0 << R_USB_FS_PL1CTRL1_L1RESPMD_SHIFT)  /* NYET */
#  define R_USB_FS_PL1CTRL1_L1RESPMD_01                   (1 << R_USB_FS_PL1CTRL1_L1RESPMD_SHIFT)  /* ACK */
#  define R_USB_FS_PL1CTRL1_L1RESPMD_10                   (2 << R_USB_FS_PL1CTRL1_L1RESPMD_SHIFT)  /* STALL */
#  define R_USB_FS_PL1CTRL1_L1RESPMD_11                   (3 << R_USB_FS_PL1CTRL1_L1RESPMD_SHIFT)  /* According to the L1NEGOMD bit */

#define R_USB_FS_PL1CTRL1_L1RESPEN                (1 << 0)  /* L1 Response Enable */

/* PL1CTRL2 Register bit definitions */
#define R_USB_FS_PL1CTRL2_RWEMON                  (1 << 12)  /* RWE Value Monitor */

#define R_USB_FS_PL1CTRL2_HIRDMON_SHIFT           (8)  /* HIRD Value Monitor */
#define R_USB_FS_PL1CTRL2_HIRDMON_MASK            0xf00
#  define R_USB_FS_PL1CTRL2_HIRDMON_0                     (0 << R_USB_FS_PL1CTRL2_HIRDMON_SHIFT)  /* The HIRD field value of the LPM token received last is reflected. */
#  define R_USB_FS_PL1CTRL2_HIRDMON_1                     (1 << R_USB_FS_PL1CTRL2_HIRDMON_SHIFT)  /* The HIRD field value of the LPM token received last is reflected. */

/* HL1CTRL1 Register bit definitions */
#define R_USB_FS_HL1CTRL1_L1STATUS_SHIFT          (1)  /* L1 Request Completion Status */
#define R_USB_FS_HL1CTRL1_L1STATUS_MASK           0x6
#  define R_USB_FS_HL1CTRL1_L1STATUS_00                   (0 << R_USB_FS_HL1CTRL1_L1STATUS_SHIFT)  /* ACK received */
#  define R_USB_FS_HL1CTRL1_L1STATUS_01                   (1 << R_USB_FS_HL1CTRL1_L1STATUS_SHIFT)  /* NYET received */
#  define R_USB_FS_HL1CTRL1_L1STATUS_10                   (2 << R_USB_FS_HL1CTRL1_L1STATUS_SHIFT)  /* STALL received */
#  define R_USB_FS_HL1CTRL1_L1STATUS_11                   (3 << R_USB_FS_HL1CTRL1_L1STATUS_SHIFT)  /* Transaction error */

#define R_USB_FS_HL1CTRL1_L1REQ                   (1 << 0)  /* L1 Transition Request */

/* HL1CTRL2 Register bit definitions */
#define R_USB_FS_HL1CTRL2_BESL                    (1 << 15)  /* BESL & Alternate HIRDThis bit selects the K-State drive period at the time of L1 Resume. */

#define R_USB_FS_HL1CTRL2_L1RWE                   (1 << 12)  /* LPM Token L1 RemoteWake EnableThese bits specify the value to be set in the RWE field of LPM token. */

#define R_USB_FS_HL1CTRL2_HIRD_SHIFT              (8)  /* LPM Token HIRD */
#define R_USB_FS_HL1CTRL2_HIRD_MASK               0xf00
#  define R_USB_FS_HL1CTRL2_HIRD_0000                     (0 << R_USB_FS_HL1CTRL2_HIRD_SHIFT)  /* 50 us(Setting prohibited(BESL = 0)) / 75 us(BESL = 1) */
#  define R_USB_FS_HL1CTRL2_HIRD_0001                     (1 << R_USB_FS_HL1CTRL2_HIRD_SHIFT)  /* 125 us(BESL = 0) / 100 us(BESL = 1) */
#  define R_USB_FS_HL1CTRL2_HIRD_0010                     (2 << R_USB_FS_HL1CTRL2_HIRD_SHIFT)  /* 200 us(BESL = 0) / 150 us(BESL = 1) */
#  define R_USB_FS_HL1CTRL2_HIRD_0011                     (3 << R_USB_FS_HL1CTRL2_HIRD_SHIFT)  /* 275 us(BESL = 0) / 250 us(BESL = 1) */
#  define R_USB_FS_HL1CTRL2_HIRD_0100                     (4 << R_USB_FS_HL1CTRL2_HIRD_SHIFT)  /* 350 us(BESL = 0) / 350 us(BESL = 1) */
#  define R_USB_FS_HL1CTRL2_HIRD_0101                     (5 << R_USB_FS_HL1CTRL2_HIRD_SHIFT)  /* 425 us(BESL = 0) / 450 us(BESL = 1) */
#  define R_USB_FS_HL1CTRL2_HIRD_0110                     (6 << R_USB_FS_HL1CTRL2_HIRD_SHIFT)  /* 500 us(BESL = 0) / 950 us(BESL = 1) */
#  define R_USB_FS_HL1CTRL2_HIRD_0111                     (7 << R_USB_FS_HL1CTRL2_HIRD_SHIFT)  /* 575 us(BESL = 0) / 1950 us(BESL = 1) */
#  define R_USB_FS_HL1CTRL2_HIRD_1000                     (8 << R_USB_FS_HL1CTRL2_HIRD_SHIFT)  /* 650 us(BESL = 0) / 2950 us(BESL = 1) */
#  define R_USB_FS_HL1CTRL2_HIRD_1001                     (9 << R_USB_FS_HL1CTRL2_HIRD_SHIFT)  /* 725 us(BESL = 0) / 3950 us(BESL = 1) */
#  define R_USB_FS_HL1CTRL2_HIRD_1010                     (10 << R_USB_FS_HL1CTRL2_HIRD_SHIFT)  /* 800 us(BESL = 0) / 4950 us(BESL = 1) */
#  define R_USB_FS_HL1CTRL2_HIRD_1011                     (11 << R_USB_FS_HL1CTRL2_HIRD_SHIFT)  /* 875 us(BESL = 0) / 5950 us(BESL = 1) */
#  define R_USB_FS_HL1CTRL2_HIRD_1100                     (12 << R_USB_FS_HL1CTRL2_HIRD_SHIFT)  /* 950 us(BESL = 0) / 6950 us(BESL = 1) */
#  define R_USB_FS_HL1CTRL2_HIRD_1101                     (13 << R_USB_FS_HL1CTRL2_HIRD_SHIFT)  /* 1025 us(Setting prohibited(BESL = 0)) / 7950 us(BESL = 1) */
#  define R_USB_FS_HL1CTRL2_HIRD_1110                     (14 << R_USB_FS_HL1CTRL2_HIRD_SHIFT)  /* 1100 us(Setting prohibited(BESL = 0)) / 8950 us(BESL = 1) */
#  define R_USB_FS_HL1CTRL2_HIRD_1111                     (15 << R_USB_FS_HL1CTRL2_HIRD_SHIFT)  /* 1175 us(Setting prohibited(BESL = 0)) / 9950 us(BESL = 1) */

#define R_USB_FS_HL1CTRL2_L1ADDR_SHIFT            (0)  /* LPM Token DeviceAddressThese bits specify the value to be set in the ADDR field of LPM token. */
#define R_USB_FS_HL1CTRL2_L1ADDR_MASK             0xf

/* DPUSR0R Register bit definitions */
#define R_USB_FS_DPUSR0R_DVBSTSHM                 (1 << 23)  /* VBUS InputIndicates VBUS input signal on the HS side of USB port. */

#define R_USB_FS_DPUSR0R_DOVCBHM                  (1 << 21)  /* OVRCURB InputIndicates OVRCURB input signal on the HS side of USB port. */

#define R_USB_FS_DPUSR0R_DOVCAHM                  (1 << 20)  /* OVRCURA InputIndicates OVRCURA input signal on the HS side of USB port. */

/* DPUSR1R Register bit definitions */
#define R_USB_FS_DPUSR1R_DVBSTSH                  (1 << 23)  /* Indication of Return from VBUS Interrupt Source */

#define R_USB_FS_DPUSR1R_DOVCBH                   (1 << 21)  /* Indication of Return from OVRCURB Interrupt Source */

#define R_USB_FS_DPUSR1R_DOVCAH                   (1 << 20)  /* Indication of Return from OVRCURA Interrupt Source */

#define R_USB_FS_DPUSR1R_DVBSTSHE                 (1 << 7)  /* VBUS Interrupt Enable/Clear */

#define R_USB_FS_DPUSR1R_DOVCBHE                  (1 << 5)  /* OVRCURB Interrupt Enable Clear */

#define R_USB_FS_DPUSR1R_DOVCAHE                  (1 << 4)  /* OVRCURA Interrupt Enable Clear */

/* DPUSR2R Register bit definitions */
#define R_USB_FS_DPUSR2R_DMINTE                   (1 << 9)  /* DM Interrupt Enable Clear */

#define R_USB_FS_DPUSR2R_DPINTE                   (1 << 8)  /* DP Interrupt Enable Clear */

#define R_USB_FS_DPUSR2R_DMVAL                    (1 << 5)  /* DM InputIndicates DM input signal on the HS side of USB port. */

#define R_USB_FS_DPUSR2R_DPVAL                    (1 << 4)  /* DP InputIndicates DP input signal on the HS side of USB port. */

#define R_USB_FS_DPUSR2R_DMINT                    (1 << 1)  /* Indication of Return from DM Interrupt Source */

#define R_USB_FS_DPUSR2R_DPINT                    (1 << 0)  /* Indication of Return from DP Interrupt Source */

/* DPUSRCR Register bit definitions */
#define R_USB_FS_DPUSRCR_FIXPHYPD                 (1 << 1)  /* USB Transceiver Control Fix for PLL */

#define R_USB_FS_DPUSRCR_FIXPHY                   (1 << 0)  /* USB Transceiver Control Fix */

/* DPUSR0R_FS Register bit definitions */
#define R_USB_FS_DPUSR0R_FS_DVBSTS0               (1 << 23)  /* USB VBUS InputIndicates the VBUS input signal of the USB. */

#define R_USB_FS_DPUSR0R_FS_DOVCB0                (1 << 21)  /* USB OVRCURB InputIndicates the OVRCURB input signal of the USB. */

#define R_USB_FS_DPUSR0R_FS_DOVCA0                (1 << 20)  /* USB OVRCURA InputIndicates the OVRCURA input signal of the USB. */

#define R_USB_FS_DPUSR0R_FS_DM0                   (1 << 17)  /* USB D-InputIndicates the D- input signal of the USB. */

#define R_USB_FS_DPUSR0R_FS_DP0                   (1 << 16)  /* USB0 D+ InputIndicates the D+ input signal of the USB. */

#define R_USB_FS_DPUSR0R_FS_FIXPHY0               (1 << 4)  /* USB Transceiver Output Fix */

#define R_USB_FS_DPUSR0R_FS_DRPD0                 (1 << 3)  /* D+/D- Pull-Down Resistor Control */

#define R_USB_FS_DPUSR0R_FS_RPUE0                 (1 << 1)  /* DP Pull-Up Resistor Control */

#define R_USB_FS_DPUSR0R_FS_SRPC0                 (1 << 0)  /* USB Single End Receiver Control */

/* DPUSR1R_FS Register bit definitions */
#define R_USB_FS_DPUSR1R_FS_DVBINT0               (1 << 23)  /* USB VBUS Interrupt Source Recovery */

#define R_USB_FS_DPUSR1R_FS_DOVRCRB0              (1 << 21)  /* USB OVRCURB Interrupt Source Recovery */

#define R_USB_FS_DPUSR1R_FS_DOVRCRA0              (1 << 20)  /* USB OVRCURA Interrupt Source Recovery */

#define R_USB_FS_DPUSR1R_FS_DMINT0                (1 << 17)  /* USB DM Interrupt Source Recovery */

#define R_USB_FS_DPUSR1R_FS_DPINT0                (1 << 16)  /* USB DP Interrupt Source Recovery */

#define R_USB_FS_DPUSR1R_FS_DVBSE0                (1 << 7)  /* USB VBUS Interrupt Enable/Clear */

#define R_USB_FS_DPUSR1R_FS_DOVRCRBE0             (1 << 5)  /* USB OVRCURB Interrupt Enable/Clear */

#define R_USB_FS_DPUSR1R_FS_DOVRCRAE0             (1 << 4)  /* USB OVRCURA Interrupt Enable/Clear */

#define R_USB_FS_DPUSR1R_FS_DMINTE0               (1 << 1)  /* USB DM Interrupt Enable/Clear */

#define R_USB_FS_DPUSR1R_FS_DPINTE0               (1 << 0)  /* USB DP Interrupt Enable/Clear */


/* Maximum number of channels */

#define USB_FS_MAX_CHANNELS    10

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_USB_FS_H */
