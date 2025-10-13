/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_mipi_dsi.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MIPI_DSI_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MIPI_DSI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* MIPI_DSI Base Address */
#ifndef R_MIPI_DSI_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_MIPI_DSI_BASE           0x40346000
#else
#define R_MIPI_DSI_BASE           0x50346000
#endif
#endif

/* MIPI_DSI Register Offsets */

#define R_MIPI_DSI_ISR_OFFSET                     0x00000000  /* Interrupt Status Register */
#define R_MIPI_DSI_LINKSR_OFFSET                  0x00000010  /* Link Status Register */
#define R_MIPI_DSI_TXSETR_OFFSET                  0x00000100  /* Transmit Set Register */
#define R_MIPI_DSI_HSCLKSETR_OFFSET               0x00000104  /* HS Clock Set Register */
#define R_MIPI_DSI_ULPSSETR_OFFSET                0x00000108  /* ULPS Set Register */
#define R_MIPI_DSI_ULPSCR_OFFSET                  0x0000010c  /* ULPS Control Register */
#define R_MIPI_DSI_RSTCR_OFFSET                   0x00000110  /* Reset Control Register */
#define R_MIPI_DSI_RSTSR_OFFSET                   0x00000114  /* Reset Status Register */
#define R_MIPI_DSI_DSISETR_OFFSET                 0x00000120  /* DSI Set Register */
#define R_MIPI_DSI_TXPPD0R_OFFSET                 0x00000160  /* Transmit Packet Payload Data 0 Register */
#define R_MIPI_DSI_TXPPD1R_OFFSET                 0x00000164  /* Transmit Packet Payload Data 1 Register */
#define R_MIPI_DSI_TXPPD2R_OFFSET                 0x00000168  /* Transmit Packet Payload Data 2 Register */
#define R_MIPI_DSI_TXPPD3R_OFFSET                 0x0000016c  /* Transmit Packet Payload Data 3 Register */
#define R_MIPI_DSI_RXSR_OFFSET                    0x00000200  /* Receive Status Register */
#define R_MIPI_DSI_RXSCR_OFFSET                   0x00000204  /* Receive Status Clear Register */
#define R_MIPI_DSI_RXIER_OFFSET                   0x00000208  /* Receive Interrupt Enable Register */
#define R_MIPI_DSI_PRESPTOBTASETR_OFFSET          0x00000210  /* Peripheral Response Timeout BTA Set Register */
#define R_MIPI_DSI_PRESPTOLPSETR_OFFSET           0x00000214  /* Peripheral Response Timeout LP Set Register */
#define R_MIPI_DSI_PRESPTOHSSETR_OFFSET           0x00000218  /* Peripheral Response Timeout HS Set Register */
#define R_MIPI_DSI_AKEPLATIR_OFFSET               0x00000220  /* Acknowledge and Error Report Packet Parameter Latest Info Register */
#define R_MIPI_DSI_AKEPACMSR_OFFSET               0x00000224  /* Acknowledge and Error Report Packet Parameter Accumulate Status Register */
#define R_MIPI_DSI_AKEPSCR_OFFSET                 0x00000228  /* Acknowledge and Error Report Packet Parameter Status Clear Register */
#define R_MIPI_DSI_RXRSSR_OFFSET                  0x00000230  /* Receive Result Saved Status Register */
#define R_MIPI_DSI_RXRSSCR_OFFSET                 0x00000234  /* Receive Result Saved Status Clear Register */
#define R_MIPI_DSI_RXRINFOOWSR_OFFSET             0x00000238  /* Receive Result Info Overwrite Status Register */
#define R_MIPI_DSI_RXRINFOOWSCR_OFFSET            0x0000023c  /* Receive Result Info Overwrite Status Clear Register */
/* RXRSS%sR Registers (0-3) */
#define R_MIPI_DSI_RXRSSR_OFFSET(m)               (0x00000240 + ((m) * 0x00000004))  /* Receive Result Save Slot-x Register (x = 0 to 3) */
#define R_MIPI_DSI_RXPPD0R_OFFSET                 0x000002c0  /* Receive Packet Payload Data 0 Register */
#define R_MIPI_DSI_RXPPD1R_OFFSET                 0x000002c4  /* Receive Packet Payload Data 1 Register */
#define R_MIPI_DSI_RXPPD2R_OFFSET                 0x000002c8  /* Receive Packet Payload Data 2 Register */
#define R_MIPI_DSI_RXPPD3R_OFFSET                 0x000002cc  /* Receive Packet Payload Data 3 Register */
#define R_MIPI_DSI_HSTXTOSETR_OFFSET              0x000002e0  /* HS TX Timeout Set Register */
#define R_MIPI_DSI_LRXHTOSETR_OFFSET              0x000002e4  /* LRX-H Timeout Set Register */
#define R_MIPI_DSI_TATOSETR_OFFSET                0x000002e8  /* TA Timeout Set Register */
#define R_MIPI_DSI_FERRSR_OFFSET                  0x00000300  /* Fatal Error Status Register */
#define R_MIPI_DSI_FERRSCR_OFFSET                 0x00000304  /* Fatal Error Status Clear Register */
#define R_MIPI_DSI_FERRIER_OFFSET                 0x00000308  /* Fatal Error Interrupt Enable Register */
#define R_MIPI_DSI_CLSTPTSETR_OFFSET              0x00000314  /* Clock Lane Stop Time Set Register */
#define R_MIPI_DSI_LPTRNSTSETR_OFFSET             0x00000318  /* LP Transition Time Set Register */
#define R_MIPI_DSI_PLSR_OFFSET                    0x00000320  /* Physical Lane Status Register */
#define R_MIPI_DSI_PLSCR_OFFSET                   0x00000324  /* Physical Lane Status Clear Register */
#define R_MIPI_DSI_PLIER_OFFSET                   0x00000328  /* Physical Lane Interrupt Enable Register */
#define R_MIPI_DSI_VMSET0R_OFFSET                 0x00000400  /* Video Mode Set 0 Register */
#define R_MIPI_DSI_VMSET1R_OFFSET                 0x00000404  /* Video Mode Set 1 Register */
#define R_MIPI_DSI_VMSR_OFFSET                    0x00000410  /* Video Mode Status Register */
#define R_MIPI_DSI_VMSCR_OFFSET                   0x00000414  /* Video Mode Status Clear Register */
#define R_MIPI_DSI_VMIER_OFFSET                   0x00000418  /* Video Mode Interrupt Enable Register */
#define R_MIPI_DSI_VMPPSETR_OFFSET                0x00000420  /* Video Mode Pixel Packet Set Register */
#define R_MIPI_DSI_VMVSSETR_OFFSET                0x00000428  /* Video Mode Vertical Size Set Register */
#define R_MIPI_DSI_VMVPSETR_OFFSET                0x0000042c  /* Video Mode Vertical Porch Set Register */
#define R_MIPI_DSI_VMHSSETR_OFFSET                0x00000430  /* Video Mode Horizontal Size Set Register */
#define R_MIPI_DSI_VMHPSETR_OFFSET                0x00000434  /* Video Mode Horizontal Porch Set Register */
#define R_MIPI_DSI_SQCH0SET0R_OFFSET              0x000005c0  /* Sequence Channel 0 Set 0 Register */
#define R_MIPI_DSI_SQCH0SR_OFFSET                 0x000005d0  /* Sequence Channel 0 Status Register */
#define R_MIPI_DSI_SQCH0SCR_OFFSET                0x000005d4  /* Sequence Channel 0 Status Clear Register */
#define R_MIPI_DSI_SQCH0IER_OFFSET                0x000005d8  /* Sequence Channel 0 Interrupt Enable Register */
#define R_MIPI_DSI_SQCH1SET0R_OFFSET              0x00000600  /* Sequence Channel 1 Set 0 Register */
#define R_MIPI_DSI_SQCH1SR_OFFSET                 0x00000610  /* Sequence Channel 1 Status Register */
#define R_MIPI_DSI_SQCH1SCR_OFFSET                0x00000614  /* Sequence Channel 1 Status Clear Register */
#define R_MIPI_DSI_SQCH1IER_OFFSET                0x00000618  /* Sequence Channel 1 Interrupt Enable Register */
/* SQCH0DSC%sAR Registers (0-7) */
#define R_MIPI_DSI_SQCH0DSCAR_OFFSET(m)           (0x00000780 + ((m) * 0x00000010))  /* Sequence Channel 0 Descriptor-m A Register (m = 0 to 7) */
/* SQCH0DSC%sBR Registers (0-7) */
#define R_MIPI_DSI_SQCH0DSCBR_OFFSET(m)           (0x00000784 + ((m) * 0x00000010))  /* Sequence Channel 0 Descriptor-m B Register (m = 0 to 7) */
/* SQCH0DSC%sCR Registers (0-7) */
#define R_MIPI_DSI_SQCH0DSCCR_OFFSET(m)           (0x00000788 + ((m) * 0x00000010))  /* Sequence Channel 0 Descriptor-m C Register */
/* SQCH0DSC%sDR Registers (0-7) */
#define R_MIPI_DSI_SQCH0DSCDR_OFFSET(m)           (0x0000078c + ((m) * 0x00000010))  /* Sequence Channel 0 Descriptor-m D Register (m = 0 to 7) */
/* SQCH1DSC%sAR Registers (0-7) */
#define R_MIPI_DSI_SQCH1DSCAR_OFFSET(m)           (0x00000800 + ((m) * 0x00000010))  /* Sequence Channel 1 Descriptor-m A Register (m = 0 to 7) */
/* SQCH1DSC%sBR Registers (0-7) */
#define R_MIPI_DSI_SQCH1DSCBR_OFFSET(m)           (0x00000804 + ((m) * 0x00000010))  /* Sequence Channel 1 Descriptor-m B Register (m = 0 to 7) */
/* SQCH1DSC%sCR Registers (0-7) */
#define R_MIPI_DSI_SQCH1DSCCR_OFFSET(m)           (0x00000808 + ((m) * 0x00000010))  /* Sequence Channel 1 Descriptor-m C Register */
/* SQCH1DSC%sDR Registers (0-7) */
#define R_MIPI_DSI_SQCH1DSCDR_OFFSET(m)           (0x0000080c + ((m) * 0x00000010))  /* Sequence Channel 1 Descriptor-m D Register (m = 0 to 7) */

/* MIPI_DSI Register Addresses */

#define R_MIPI_DSI_ISR                            (R_MIPI_DSI_BASE + R_MIPI_DSI_ISR_OFFSET)
#define R_MIPI_DSI_LINKSR                         (R_MIPI_DSI_BASE + R_MIPI_DSI_LINKSR_OFFSET)
#define R_MIPI_DSI_TXSETR                         (R_MIPI_DSI_BASE + R_MIPI_DSI_TXSETR_OFFSET)
#define R_MIPI_DSI_HSCLKSETR                      (R_MIPI_DSI_BASE + R_MIPI_DSI_HSCLKSETR_OFFSET)
#define R_MIPI_DSI_ULPSSETR                       (R_MIPI_DSI_BASE + R_MIPI_DSI_ULPSSETR_OFFSET)
#define R_MIPI_DSI_ULPSCR                         (R_MIPI_DSI_BASE + R_MIPI_DSI_ULPSCR_OFFSET)
#define R_MIPI_DSI_RSTCR                          (R_MIPI_DSI_BASE + R_MIPI_DSI_RSTCR_OFFSET)
#define R_MIPI_DSI_RSTSR                          (R_MIPI_DSI_BASE + R_MIPI_DSI_RSTSR_OFFSET)
#define R_MIPI_DSI_DSISETR                        (R_MIPI_DSI_BASE + R_MIPI_DSI_DSISETR_OFFSET)
#define R_MIPI_DSI_TXPPD0R                        (R_MIPI_DSI_BASE + R_MIPI_DSI_TXPPD0R_OFFSET)
#define R_MIPI_DSI_TXPPD1R                        (R_MIPI_DSI_BASE + R_MIPI_DSI_TXPPD1R_OFFSET)
#define R_MIPI_DSI_TXPPD2R                        (R_MIPI_DSI_BASE + R_MIPI_DSI_TXPPD2R_OFFSET)
#define R_MIPI_DSI_TXPPD3R                        (R_MIPI_DSI_BASE + R_MIPI_DSI_TXPPD3R_OFFSET)
#define R_MIPI_DSI_RXSR                           (R_MIPI_DSI_BASE + R_MIPI_DSI_RXSR_OFFSET)
#define R_MIPI_DSI_RXSCR                          (R_MIPI_DSI_BASE + R_MIPI_DSI_RXSCR_OFFSET)
#define R_MIPI_DSI_RXIER                          (R_MIPI_DSI_BASE + R_MIPI_DSI_RXIER_OFFSET)
#define R_MIPI_DSI_PRESPTOBTASETR                 (R_MIPI_DSI_BASE + R_MIPI_DSI_PRESPTOBTASETR_OFFSET)
#define R_MIPI_DSI_PRESPTOLPSETR                  (R_MIPI_DSI_BASE + R_MIPI_DSI_PRESPTOLPSETR_OFFSET)
#define R_MIPI_DSI_PRESPTOHSSETR                  (R_MIPI_DSI_BASE + R_MIPI_DSI_PRESPTOHSSETR_OFFSET)
#define R_MIPI_DSI_AKEPLATIR                      (R_MIPI_DSI_BASE + R_MIPI_DSI_AKEPLATIR_OFFSET)
#define R_MIPI_DSI_AKEPACMSR                      (R_MIPI_DSI_BASE + R_MIPI_DSI_AKEPACMSR_OFFSET)
#define R_MIPI_DSI_AKEPSCR                        (R_MIPI_DSI_BASE + R_MIPI_DSI_AKEPSCR_OFFSET)
#define R_MIPI_DSI_RXRSSR                         (R_MIPI_DSI_BASE + R_MIPI_DSI_RXRSSR_OFFSET)
#define R_MIPI_DSI_RXRSSCR                        (R_MIPI_DSI_BASE + R_MIPI_DSI_RXRSSCR_OFFSET)
#define R_MIPI_DSI_RXRINFOOWSR                    (R_MIPI_DSI_BASE + R_MIPI_DSI_RXRINFOOWSR_OFFSET)
#define R_MIPI_DSI_RXRINFOOWSCR                   (R_MIPI_DSI_BASE + R_MIPI_DSI_RXRINFOOWSCR_OFFSET)
#define R_MIPI_DSI_RXRSSR(m)                      (R_MIPI_DSI_BASE + R_MIPI_DSI_RXRSSR_OFFSET(m))
#define R_MIPI_DSI_RXPPD0R                        (R_MIPI_DSI_BASE + R_MIPI_DSI_RXPPD0R_OFFSET)
#define R_MIPI_DSI_RXPPD1R                        (R_MIPI_DSI_BASE + R_MIPI_DSI_RXPPD1R_OFFSET)
#define R_MIPI_DSI_RXPPD2R                        (R_MIPI_DSI_BASE + R_MIPI_DSI_RXPPD2R_OFFSET)
#define R_MIPI_DSI_RXPPD3R                        (R_MIPI_DSI_BASE + R_MIPI_DSI_RXPPD3R_OFFSET)
#define R_MIPI_DSI_HSTXTOSETR                     (R_MIPI_DSI_BASE + R_MIPI_DSI_HSTXTOSETR_OFFSET)
#define R_MIPI_DSI_LRXHTOSETR                     (R_MIPI_DSI_BASE + R_MIPI_DSI_LRXHTOSETR_OFFSET)
#define R_MIPI_DSI_TATOSETR                       (R_MIPI_DSI_BASE + R_MIPI_DSI_TATOSETR_OFFSET)
#define R_MIPI_DSI_FERRSR                         (R_MIPI_DSI_BASE + R_MIPI_DSI_FERRSR_OFFSET)
#define R_MIPI_DSI_FERRSCR                        (R_MIPI_DSI_BASE + R_MIPI_DSI_FERRSCR_OFFSET)
#define R_MIPI_DSI_FERRIER                        (R_MIPI_DSI_BASE + R_MIPI_DSI_FERRIER_OFFSET)
#define R_MIPI_DSI_CLSTPTSETR                     (R_MIPI_DSI_BASE + R_MIPI_DSI_CLSTPTSETR_OFFSET)
#define R_MIPI_DSI_LPTRNSTSETR                    (R_MIPI_DSI_BASE + R_MIPI_DSI_LPTRNSTSETR_OFFSET)
#define R_MIPI_DSI_PLSR                           (R_MIPI_DSI_BASE + R_MIPI_DSI_PLSR_OFFSET)
#define R_MIPI_DSI_PLSCR                          (R_MIPI_DSI_BASE + R_MIPI_DSI_PLSCR_OFFSET)
#define R_MIPI_DSI_PLIER                          (R_MIPI_DSI_BASE + R_MIPI_DSI_PLIER_OFFSET)
#define R_MIPI_DSI_VMSET0R                        (R_MIPI_DSI_BASE + R_MIPI_DSI_VMSET0R_OFFSET)
#define R_MIPI_DSI_VMSET1R                        (R_MIPI_DSI_BASE + R_MIPI_DSI_VMSET1R_OFFSET)
#define R_MIPI_DSI_VMSR                           (R_MIPI_DSI_BASE + R_MIPI_DSI_VMSR_OFFSET)
#define R_MIPI_DSI_VMSCR                          (R_MIPI_DSI_BASE + R_MIPI_DSI_VMSCR_OFFSET)
#define R_MIPI_DSI_VMIER                          (R_MIPI_DSI_BASE + R_MIPI_DSI_VMIER_OFFSET)
#define R_MIPI_DSI_VMPPSETR                       (R_MIPI_DSI_BASE + R_MIPI_DSI_VMPPSETR_OFFSET)
#define R_MIPI_DSI_VMVSSETR                       (R_MIPI_DSI_BASE + R_MIPI_DSI_VMVSSETR_OFFSET)
#define R_MIPI_DSI_VMVPSETR                       (R_MIPI_DSI_BASE + R_MIPI_DSI_VMVPSETR_OFFSET)
#define R_MIPI_DSI_VMHSSETR                       (R_MIPI_DSI_BASE + R_MIPI_DSI_VMHSSETR_OFFSET)
#define R_MIPI_DSI_VMHPSETR                       (R_MIPI_DSI_BASE + R_MIPI_DSI_VMHPSETR_OFFSET)
#define R_MIPI_DSI_SQCH0SET0R                     (R_MIPI_DSI_BASE + R_MIPI_DSI_SQCH0SET0R_OFFSET)
#define R_MIPI_DSI_SQCH0SR                        (R_MIPI_DSI_BASE + R_MIPI_DSI_SQCH0SR_OFFSET)
#define R_MIPI_DSI_SQCH0SCR                       (R_MIPI_DSI_BASE + R_MIPI_DSI_SQCH0SCR_OFFSET)
#define R_MIPI_DSI_SQCH0IER                       (R_MIPI_DSI_BASE + R_MIPI_DSI_SQCH0IER_OFFSET)
#define R_MIPI_DSI_SQCH1SET0R                     (R_MIPI_DSI_BASE + R_MIPI_DSI_SQCH1SET0R_OFFSET)
#define R_MIPI_DSI_SQCH1SR                        (R_MIPI_DSI_BASE + R_MIPI_DSI_SQCH1SR_OFFSET)
#define R_MIPI_DSI_SQCH1SCR                       (R_MIPI_DSI_BASE + R_MIPI_DSI_SQCH1SCR_OFFSET)
#define R_MIPI_DSI_SQCH1IER                       (R_MIPI_DSI_BASE + R_MIPI_DSI_SQCH1IER_OFFSET)
#define R_MIPI_DSI_SQCH0DSCAR(m)                  (R_MIPI_DSI_BASE + R_MIPI_DSI_SQCH0DSCAR_OFFSET(m))
#define R_MIPI_DSI_SQCH0DSCBR(m)                  (R_MIPI_DSI_BASE + R_MIPI_DSI_SQCH0DSCBR_OFFSET(m))
#define R_MIPI_DSI_SQCH0DSCCR(m)                  (R_MIPI_DSI_BASE + R_MIPI_DSI_SQCH0DSCCR_OFFSET(m))
#define R_MIPI_DSI_SQCH0DSCDR(m)                  (R_MIPI_DSI_BASE + R_MIPI_DSI_SQCH0DSCDR_OFFSET(m))
#define R_MIPI_DSI_SQCH1DSCAR(m)                  (R_MIPI_DSI_BASE + R_MIPI_DSI_SQCH1DSCAR_OFFSET(m))
#define R_MIPI_DSI_SQCH1DSCBR(m)                  (R_MIPI_DSI_BASE + R_MIPI_DSI_SQCH1DSCBR_OFFSET(m))
#define R_MIPI_DSI_SQCH1DSCCR(m)                  (R_MIPI_DSI_BASE + R_MIPI_DSI_SQCH1DSCCR_OFFSET(m))
#define R_MIPI_DSI_SQCH1DSCDR(m)                  (R_MIPI_DSI_BASE + R_MIPI_DSI_SQCH1DSCDR_OFFSET(m))

/* Register bit definitions */
/* ISR Register bit definitions */
#define R_MIPI_DSI_ISR_SQ0                        (1 << 0)  /* Sequence Channel-0 Interrupt Flag */

#define R_MIPI_DSI_ISR_SQ1                        (1 << 4)  /* Sequence Channel-1 Interrupt Flag */

#define R_MIPI_DSI_ISR_VM                         (1 << 8)  /* Video Mode Interrupt Flag */

#define R_MIPI_DSI_ISR_RCV                        (1 << 12)  /* Receive Interrupt Flag */

#define R_MIPI_DSI_ISR_FERR                       (1 << 16)  /* Fatal Error Interrupt Flag */

#define R_MIPI_DSI_ISR_PPI                        (1 << 20)  /* PPI Interrupt Flag */

/* LINKSR Register bit definitions */
#define R_MIPI_DSI_LINKSR_SQ0RUN                  (1 << 0)  /* Sequence Channel-0 Running Flag */

#define R_MIPI_DSI_LINKSR_SQ1RUN                  (1 << 4)  /* Sequence Channel-1 Running Flag */

#define R_MIPI_DSI_LINKSR_VRUN                    (1 << 8)  /* Video Mode Operation Running Flag */

#define R_MIPI_DSI_LINKSR_HSBUSY                  (1 << 12)  /* HS Operation Busy Flag */

#define R_MIPI_DSI_LINKSR_LPBUSY                  (1 << 13)  /* LP Operation Busy Flag */

/* TXSETR Register bit definitions */
#define R_MIPI_DSI_TXSETR_NUMLANE_SHIFT           (0)  /* Number of Lane */
#define R_MIPI_DSI_TXSETR_NUMLANE_MASK            0x3
#  define R_MIPI_DSI_TXSETR_NUMLANE_00                    (0 << R_MIPI_DSI_TXSETR_NUMLANE_SHIFT)  /* 1 Lane (Use of Lane-0) */
#  define R_MIPI_DSI_TXSETR_NUMLANE_01                    (1 << R_MIPI_DSI_TXSETR_NUMLANE_SHIFT)  /* 2 Lane (Use of Lane-0 and Lane-1) */

#define R_MIPI_DSI_TXSETR_CLEN                    (1 << 8)  /* Clock Lane Enable */

#define R_MIPI_DSI_TXSETR_DLEN                    (1 << 9)  /* Data Lane Enable */

/* HSCLKSETR Register bit definitions */
#define R_MIPI_DSI_HSCLKSETR_HSCLST               (1 << 0)  /* HS Clock Start */

#define R_MIPI_DSI_HSCLKSETR_HSCLMD               (1 << 1)  /* HS Clock Running Mode */

/* ULPSSETR Register bit definitions */
#define R_MIPI_DSI_ULPSSETR_WKUP_SHIFT            (0)  /* ULPS Wakeup Period */
#define R_MIPI_DSI_ULPSSETR_WKUP_MASK             0xff

/* ULPSCR Register bit definitions */
#define R_MIPI_DSI_ULPSCR_CLENT                   (1 << 24)  /* CL ULPS Enter */

#define R_MIPI_DSI_ULPSCR_CLEXIT                  (1 << 25)  /* CL ULPS Exit */

#define R_MIPI_DSI_ULPSCR_DLENT                   (1 << 28)  /* DL ULPS Enter */

#define R_MIPI_DSI_ULPSCR_DLEXIT                  (1 << 29)  /* DL ULPS Exit */

/* RSTCR Register bit definitions */
#define R_MIPI_DSI_RSTCR_SWRST                    (1 << 0)  /* Software Reset */

#define R_MIPI_DSI_RSTCR_FTXSTP                   (1 << 16)  /* Force TX Stop Mode */

/* RSTSR Register bit definitions */
#define R_MIPI_DSI_RSTSR_RSTHS                    (1 << 0)  /* HS Software Reset Status */

#define R_MIPI_DSI_RSTSR_RSTLP                    (1 << 1)  /* LP Software Reset Status */

#define R_MIPI_DSI_RSTSR_RSTAPB                   (1 << 2)  /* APB Software Reset Status */

#define R_MIPI_DSI_RSTSR_RSTAXI                   (1 << 3)  /* AXI Software Reset Status */

#define R_MIPI_DSI_RSTSR_RSTV                     (1 << 4)  /* Video Software Reset Status */

#define R_MIPI_DSI_RSTSR_DL0STP                   (1 << 8)  /* Data Lane-0 Stop Status */

#define R_MIPI_DSI_RSTSR_DL1STP                   (1 << 9)  /* Data Lane-1 Stop Status */

#define R_MIPI_DSI_RSTSR_DL0DIR                   (1 << 15)  /* Data Lane-0 Direction */

/* DSISETR Register bit definitions */
#define R_MIPI_DSI_DSISETR_MRPSZ_SHIFT            (0)  /* Maximum Return Packet Size */
#define R_MIPI_DSI_DSISETR_MRPSZ_MASK             0xffff

#define R_MIPI_DSI_DSISETR_ECCEN                  (1 << 16)  /* ECC Check Enable */

#define R_MIPI_DSI_DSISETR_VC0CRCEN               (1 << 20)  /* VC-0 CRC Check Enable */

#define R_MIPI_DSI_DSISETR_VC1CRCEN               (1 << 21)  /* VC-1 CRC Check Enable */

#define R_MIPI_DSI_DSISETR_VC2CRCEN               (1 << 22)  /* VC-2 CRC Check Enable */

#define R_MIPI_DSI_DSISETR_VC3CRCEN               (1 << 23)  /* VC-3 CRC Check Enable */

#define R_MIPI_DSI_DSISETR_SCREN                  (1 << 29)  /* Data Scramble Enable */

#define R_MIPI_DSI_DSISETR_EXTEMD                 (1 << 30)  /* External Tearing Effect Detection Sense Select */

#define R_MIPI_DSI_DSISETR_EOTPEN                 (1 << 31)  /* HS Transfer EoTp Enable */

/* TXPPD0R Register bit definitions */
#define R_MIPI_DSI_TXPPD0R_DATA0_SHIFT            (0)  /* Payload Data 0 */
#define R_MIPI_DSI_TXPPD0R_DATA0_MASK             0xff

#define R_MIPI_DSI_TXPPD0R_DATA1_SHIFT            (8)  /* Payload Data 1 */
#define R_MIPI_DSI_TXPPD0R_DATA1_MASK             0xff00

#define R_MIPI_DSI_TXPPD0R_DATA2_SHIFT            (16)  /* Payload Data 2 */
#define R_MIPI_DSI_TXPPD0R_DATA2_MASK             0xff0000

#define R_MIPI_DSI_TXPPD0R_DATA3_SHIFT            (24)  /* Payload Data 3 */
#define R_MIPI_DSI_TXPPD0R_DATA3_MASK             0xff000000

/* TXPPD1R Register bit definitions */
#define R_MIPI_DSI_TXPPD1R_DATA4_SHIFT            (0)  /* Payload Data 4 */
#define R_MIPI_DSI_TXPPD1R_DATA4_MASK             0xff

#define R_MIPI_DSI_TXPPD1R_DATA5_SHIFT            (8)  /* Payload Data 5 */
#define R_MIPI_DSI_TXPPD1R_DATA5_MASK             0xff00

#define R_MIPI_DSI_TXPPD1R_DATA6_SHIFT            (16)  /* Payload Data 6 */
#define R_MIPI_DSI_TXPPD1R_DATA6_MASK             0xff0000

#define R_MIPI_DSI_TXPPD1R_DATA7_SHIFT            (24)  /* Payload Data 7 */
#define R_MIPI_DSI_TXPPD1R_DATA7_MASK             0xff000000

/* TXPPD2R Register bit definitions */
#define R_MIPI_DSI_TXPPD2R_DATA8_SHIFT            (0)  /* Payload Data 8 */
#define R_MIPI_DSI_TXPPD2R_DATA8_MASK             0xff

#define R_MIPI_DSI_TXPPD2R_DATA9_SHIFT            (8)  /* Payload Data 9 */
#define R_MIPI_DSI_TXPPD2R_DATA9_MASK             0xff00

#define R_MIPI_DSI_TXPPD2R_DATA10_SHIFT           (16)  /* Payload Data 10 */
#define R_MIPI_DSI_TXPPD2R_DATA10_MASK            0xff0000

#define R_MIPI_DSI_TXPPD2R_DATA11_SHIFT           (24)  /* Payload Data 11 */
#define R_MIPI_DSI_TXPPD2R_DATA11_MASK            0xff000000

/* TXPPD3R Register bit definitions */
#define R_MIPI_DSI_TXPPD3R_DATA12_SHIFT           (0)  /* Payload Data 12 */
#define R_MIPI_DSI_TXPPD3R_DATA12_MASK            0xff

#define R_MIPI_DSI_TXPPD3R_DATA13_SHIFT           (8)  /* Payload Data 13 */
#define R_MIPI_DSI_TXPPD3R_DATA13_MASK            0xff00

#define R_MIPI_DSI_TXPPD3R_DATA14_SHIFT           (16)  /* Payload Data 14 */
#define R_MIPI_DSI_TXPPD3R_DATA14_MASK            0xff0000

#define R_MIPI_DSI_TXPPD3R_DATA15_SHIFT           (24)  /* Payload Data 15 */
#define R_MIPI_DSI_TXPPD3R_DATA15_MASK            0xff000000

/* RXSR Register bit definitions */
#define R_MIPI_DSI_RXSR_BTAREND                   (1 << 0)  /* BTA Request End Interrupt Flag */

#define R_MIPI_DSI_RXSR_LRXHTO                    (1 << 1)  /* LP-RX Host Processor Timeout Interrupt Flag */

#define R_MIPI_DSI_RXSR_TATO                      (1 << 2)  /* Turnaround Acknowledge Timeout Interrupt Flag */

#define R_MIPI_DSI_RXSR_RXRESP                    (1 << 8)  /* Response Packet Receive Interrupt Flag */

#define R_MIPI_DSI_RXSR_RXEOTP                    (1 << 10)  /* EoTp Receive Interrupt Flag */

#define R_MIPI_DSI_RXSR_RXACK                     (1 << 14)  /* ACK Trigger Receive Interrupt Flag */

#define R_MIPI_DSI_RXSR_EXTEDET                   (1 << 15)  /* External Tearing Effect Detect Interrupt Flag */

#define R_MIPI_DSI_RXSR_MLFERR                    (1 << 16)  /* Malform Error Interrupt Flag */

#define R_MIPI_DSI_RXSR_ECCERRM                   (1 << 17)  /* Multi Bit ECC Error Interrupt Flag */

#define R_MIPI_DSI_RXSR_UNEXERR                   (1 << 18)  /* Unexpected Packet Error Interrupt Flag */

#define R_MIPI_DSI_RXSR_WCERR                     (1 << 20)  /* Word Count Error Interrupt Flag */

#define R_MIPI_DSI_RXSR_CRCERR                    (1 << 21)  /* CRC Error Interrupt Flag */

#define R_MIPI_DSI_RXSR_IBERR                     (1 << 22)  /* Internal Bus Error Interrupt Flag */

#define R_MIPI_DSI_RXSR_RXOVFERR                  (1 << 23)  /* Receive Buffer Overflow Error Interrupt Flag */

#define R_MIPI_DSI_RXSR_PRTOERR                   (1 << 24)  /* Peripheral Response Timeout Error Interrupt Flag */

#define R_MIPI_DSI_RXSR_NORESERR                  (1 << 25)  /* No Response Error Interrupt Flag */

#define R_MIPI_DSI_RXSR_RSIZEERR                  (1 << 26)  /* Return Packet Size Error Interrupt Flag */

#define R_MIPI_DSI_RXSR_ECCERRS                   (1 << 28)  /* Single Bit ECC Error Interrupt Flag */

#define R_MIPI_DSI_RXSR_RXAKE                     (1 << 30)  /* Acknowledge and Error Report Receive Interrupt Flag */

#define R_MIPI_DSI_RXSR_RXTE                      (1 << 13)  /* Tearing Effect Trigger Receive Interrupt Flag */

/* RXSCR Register bit definitions */
#define R_MIPI_DSI_RXSCR_BTAREND                  (1 << 0)  /* BTA Request End Interrupt Flag Clear */

#define R_MIPI_DSI_RXSCR_LRXHTO                   (1 << 1)  /* LP-RX Host Processor Timeout Interrupt Flag Clear */

#define R_MIPI_DSI_RXSCR_TATO                     (1 << 2)  /* Turnaround Acknowledge Timeout Interrupt Flag Clear */

#define R_MIPI_DSI_RXSCR_RXRESP                   (1 << 8)  /* Response Packet Receive Interrupt Flag Clear */

#define R_MIPI_DSI_RXSCR_RXEOTP                   (1 << 10)  /* EoTp Receive Interrupt Flag Clear */

#define R_MIPI_DSI_RXSCR_RXACK                    (1 << 14)  /* ACK Trigger Receive Interrupt Flag Clear */

#define R_MIPI_DSI_RXSCR_EXTEDET                  (1 << 15)  /* External Tearing Effect Detect Interrupt Flag Clear */

#define R_MIPI_DSI_RXSCR_MLFERR                   (1 << 16)  /* Malform Error Interrupt Flag Clear */

#define R_MIPI_DSI_RXSCR_ECCERRM                  (1 << 17)  /* Multi Bit ECC Error Interrupt Flag Clear */

#define R_MIPI_DSI_RXSCR_UNEXERR                  (1 << 18)  /* Unexpected Packet Error Interrupt Flag Clear */

#define R_MIPI_DSI_RXSCR_WCERR                    (1 << 20)  /* Word Count Error Interrupt Flag Clear */

#define R_MIPI_DSI_RXSCR_CRCERR                   (1 << 21)  /* CRC Error Interrupt Flag Clear */

#define R_MIPI_DSI_RXSCR_IBERR                    (1 << 22)  /* Internal Bus Error Interrupt Flag Clear */

#define R_MIPI_DSI_RXSCR_RXOVFERR                 (1 << 23)  /* Receive Buffer Overflow Error Interrupt Flag Clear */

#define R_MIPI_DSI_RXSCR_PRTOERR                  (1 << 24)  /* Peripheral Response Timeout Error Interrupt Flag Clear */

#define R_MIPI_DSI_RXSCR_NORESERR                 (1 << 25)  /* No Response Error Interrupt Flag Clear */

#define R_MIPI_DSI_RXSCR_RSIZEERR                 (1 << 26)  /* Return Packet Size Error Interrupt Flag Clear */

#define R_MIPI_DSI_RXSCR_ECCERRS                  (1 << 28)  /* Single Bit ECC Error Interrupt Flag Clear */

#define R_MIPI_DSI_RXSCR_RXAKE                    (1 << 30)  /* Acknowledge and Error Report Receive Interrupt Flag Clear */

#define R_MIPI_DSI_RXSCR_RXTE                     (1 << 13)  /* Tearing Effect Trigger Receive Interrupt Flag Clear */

/* RXIER Register bit definitions */
#define R_MIPI_DSI_RXIER_BTAREND                  (1 << 0)  /* BTA Request End Interrupt Enable */

#define R_MIPI_DSI_RXIER_LRXHTO                   (1 << 1)  /* LP-RX Host Processor Timeout Interrupt Enable */

#define R_MIPI_DSI_RXIER_TATO                     (1 << 2)  /* Turnaround Acknowledge Timeout Interrupt Enable */

#define R_MIPI_DSI_RXIER_RXRESP                   (1 << 8)  /* Response Packet Receive Interrupt Enable */

#define R_MIPI_DSI_RXIER_RXEOTP                   (1 << 10)  /* EoTp Receive Interrupt Enable */

#define R_MIPI_DSI_RXIER_RXACK                    (1 << 14)  /* ACK Trigger Receive Interrupt Enable */

#define R_MIPI_DSI_RXIER_EXTEDET                  (1 << 15)  /* External Tearing Effect Detect Interrupt Enable */

#define R_MIPI_DSI_RXIER_MLFERR                   (1 << 16)  /* Malform Error Interrupt Enable */

#define R_MIPI_DSI_RXIER_ECCERRM                  (1 << 17)  /* Multi-bit ECC Error Interrupt Enable */

#define R_MIPI_DSI_RXIER_UNEXERR                  (1 << 18)  /* Unexpected Packet Error Interrupt Enable */

#define R_MIPI_DSI_RXIER_WCERR                    (1 << 20)  /* Word Count Error Interrupt Enable */

#define R_MIPI_DSI_RXIER_CRCERR                   (1 << 21)  /* CRC Error Interrupt Enable */

#define R_MIPI_DSI_RXIER_IBERR                    (1 << 22)  /* Internal Bus Error Interrupt Enable */

#define R_MIPI_DSI_RXIER_RXOVFERR                 (1 << 23)  /* Receive Buffer Overflow Error Interrupt Enable */

#define R_MIPI_DSI_RXIER_PRTOERR                  (1 << 24)  /* Peripheral Response Timeout Error Interrupt Enable */

#define R_MIPI_DSI_RXIER_NORESERR                 (1 << 25)  /* No Response Error Interrupt Enable */

#define R_MIPI_DSI_RXIER_RSIZEERR                 (1 << 26)  /* Return Packet Size Error Interrupt Enable */

#define R_MIPI_DSI_RXIER_ECCERRS                  (1 << 28)  /* Single Bit ECC Error Interrupt Enable */

#define R_MIPI_DSI_RXIER_RXAKE                    (1 << 30)  /* Acknowledge and Error Report Receive Interrupt Enable */

#define R_MIPI_DSI_RXIER_RXTE                     (1 << 13)  /* Tearing Effect Trigger Receive Interrupt Enable */

/* PRESPTOBTASETR Register bit definitions */
#define R_MIPI_DSI_PRESPTOBTASETR_PRTBTA_SHIFT    (0)  /* Peripheral Response Timeout Count */
#define R_MIPI_DSI_PRESPTOBTASETR_PRTBTA_MASK     0xffffffff

/* PRESPTOLPSETR Register bit definitions */
#define R_MIPI_DSI_PRESPTOLPSETR_LPWTO_SHIFT      (0)  /* LPDT WRITE Request Timeout */
#define R_MIPI_DSI_PRESPTOLPSETR_LPWTO_MASK       0xffff

#define R_MIPI_DSI_PRESPTOLPSETR_LPRTO_SHIFT      (16)  /* LPDT READ Request Timeout */
#define R_MIPI_DSI_PRESPTOLPSETR_LPRTO_MASK       0xffff0000

/* PRESPTOHSSETR Register bit definitions */
#define R_MIPI_DSI_PRESPTOHSSETR_HSWTO_SHIFT      (0)  /* HS WRITE Request Timeout */
#define R_MIPI_DSI_PRESPTOHSSETR_HSWTO_MASK       0xffff

#define R_MIPI_DSI_PRESPTOHSSETR_HSRTO_SHIFT      (16)  /* HS READ Request Timeout */
#define R_MIPI_DSI_PRESPTOHSSETR_HSRTO_MASK       0xffff0000

/* AKEPLATIR Register bit definitions */
#define R_MIPI_DSI_AKEPLATIR_EREP_SHIFT           (0)  /* Error Report */
#define R_MIPI_DSI_AKEPLATIR_EREP_MASK            0xffff

#define R_MIPI_DSI_AKEPLATIR_VC_SHIFT             (16)  /* Virtual Channel ID */
#define R_MIPI_DSI_AKEPLATIR_VC_MASK              0xf0000
#  define R_MIPI_DSI_AKEPLATIR_VC_0X0                     (0 << R_MIPI_DSI_AKEPLATIR_VC_SHIFT)  /* No Error Report received */
#  define R_MIPI_DSI_AKEPLATIR_VC_0X1                     (1 << R_MIPI_DSI_AKEPLATIR_VC_SHIFT)  /* From VC-0 */
#  define R_MIPI_DSI_AKEPLATIR_VC_0X2                     (2 << R_MIPI_DSI_AKEPLATIR_VC_SHIFT)  /* From VC-1 */
#  define R_MIPI_DSI_AKEPLATIR_VC_0X4                     (4 << R_MIPI_DSI_AKEPLATIR_VC_SHIFT)  /* From VC-2 */
#  define R_MIPI_DSI_AKEPLATIR_VC_0X8                     (8 << R_MIPI_DSI_AKEPLATIR_VC_SHIFT)  /* From VC-3 */

/* AKEPACMSR Register bit definitions */
#define R_MIPI_DSI_AKEPACMSR_AEREP_SHIFT          (0)  /* Accumulated Error Report */
#define R_MIPI_DSI_AKEPACMSR_AEREP_MASK           0xffff

#define R_MIPI_DSI_AKEPACMSR_AVC0                 (1 << 16)  /* Virtual Channel-0 Accumulated Information */

#define R_MIPI_DSI_AKEPACMSR_AVC1                 (1 << 17)  /* Virtual Channel-1 Accumulated Information */

#define R_MIPI_DSI_AKEPACMSR_AVC2                 (1 << 18)  /* Virtual Channel-2 Accumulated Information */

#define R_MIPI_DSI_AKEPACMSR_AVC3                 (1 << 19)  /* Virtual Channel-3 Accumulated Information */

#define R_MIPI_DSI_AKEPACMSR_AVC_SHIFT            (16)  /* Virtual Channel ID */
#define R_MIPI_DSI_AKEPACMSR_AVC_MASK             0xf0000

/* AKEPSCR Register bit definitions */
#define R_MIPI_DSI_AKEPSCR_AEREP_SHIFT            (0)  /* Accumulated Error Report Clear */
#define R_MIPI_DSI_AKEPSCR_AEREP_MASK             0xffff
#  define R_MIPI_DSI_AKEPSCR_AEREP_0                      (0 << R_MIPI_DSI_AKEPSCR_AEREP_SHIFT)  /* No operation */
#  define R_MIPI_DSI_AKEPSCR_AEREP_1                      (1 << R_MIPI_DSI_AKEPSCR_AEREP_SHIFT)  /* Clear the AKEPACMSR.AEREP[15:0] bits */

#define R_MIPI_DSI_AKEPSCR_AVC0                   (1 << 16)  /* Virtual Channel-0 Accumulated Information Clear */

#define R_MIPI_DSI_AKEPSCR_AVC1                   (1 << 17)  /* Virtual Channel-1 Accumulated Information Clear */

#define R_MIPI_DSI_AKEPSCR_AVC2                   (1 << 18)  /* Virtual Channel-2 Accumulated Information Clear */

#define R_MIPI_DSI_AKEPSCR_AVC3                   (1 << 19)  /* Virtual Channel-3 Accumulated Information Clear */

#define R_MIPI_DSI_AKEPSCR_AVC_SHIFT              (16)  /* Virtual Channel ID */
#define R_MIPI_DSI_AKEPSCR_AVC_MASK               0xf0000

/* RXRSSR Register bit definitions */
#define R_MIPI_DSI_RXRSSR_SLT0VLD                 (1 << 0)  /* Slot-0 Valid Flag */

#define R_MIPI_DSI_RXRSSR_SLT1VLD                 (1 << 1)  /* Slot-1 Valid Flag */

#define R_MIPI_DSI_RXRSSR_SLT2VLD                 (1 << 2)  /* Slot-2 Valid Flag */

#define R_MIPI_DSI_RXRSSR_SLT3VLD                 (1 << 3)  /* Slot-3 Valid Flag */

/* RXRSSCR Register bit definitions */
#define R_MIPI_DSI_RXRSSCR_SLT0VLD                (1 << 0)  /* Slot-0 Valid Flag Clear */

#define R_MIPI_DSI_RXRSSCR_SLT1VLD                (1 << 1)  /* Slot-1 Valid Flag Clear */

#define R_MIPI_DSI_RXRSSCR_SLT2VLD                (1 << 2)  /* Slot-2 Valid Flag Clear */

#define R_MIPI_DSI_RXRSSCR_SLT3VLD                (1 << 3)  /* Slot-3 Valid Flag Clear */

/* RXRINFOOWSR Register bit definitions */
#define R_MIPI_DSI_RXRINFOOWSR_SL0OW              (1 << 0)  /* Slot-0 Information Overwrite Flag */

#define R_MIPI_DSI_RXRINFOOWSR_SL1OW              (1 << 1)  /* Slot-1 Information Overwrite Flag */

#define R_MIPI_DSI_RXRINFOOWSR_SL2OW              (1 << 2)  /* Slot-2 Information Overwrite Flag */

#define R_MIPI_DSI_RXRINFOOWSR_SL3OW              (1 << 3)  /* Slot-3 Information Overwrite Flag */

/* RXRINFOOWSCR Register bit definitions */
#define R_MIPI_DSI_RXRINFOOWSCR_SL0OW             (1 << 0)  /* Slot-0 Information Overwrite Flag Clear */

#define R_MIPI_DSI_RXRINFOOWSCR_SL1OW             (1 << 1)  /* Slot-1 Information Overwrite Flag Clear */

#define R_MIPI_DSI_RXRINFOOWSCR_SL2OW             (1 << 2)  /* Slot-2 Information Overwrite Flag Clear */

#define R_MIPI_DSI_RXRINFOOWSCR_SL3OW             (1 << 3)  /* Slot-3 Information Overwrite Flag Clear */

/* RXRSSR Register bit definitions */
#define R_MIPI_DSI_RXRSSR_DATA0_SHIFT             (0)  /* Data 0 */
#define R_MIPI_DSI_RXRSSR_DATA0_MASK              0xff

#define R_MIPI_DSI_RXRSSR_DATA1_SHIFT             (8)  /* Data 1 */
#define R_MIPI_DSI_RXRSSR_DATA1_MASK              0xff00

#define R_MIPI_DSI_RXRSSR_DT_SHIFT                (16)  /* Data Type */
#define R_MIPI_DSI_RXRSSR_DT_MASK                 0x3f0000

#define R_MIPI_DSI_RXRSSR_VC_SHIFT                (22)  /* Virtual Channel ID */
#define R_MIPI_DSI_RXRSSR_VC_MASK                 0xc00000

#define R_MIPI_DSI_RXRSSR_FMT                     (1 << 24)  /* Packet Format */

#define R_MIPI_DSI_RXRSSR_RXSUC                   (1 << 25)  /* Receive Success */

#define R_MIPI_DSI_RXRSSR_RXFERR                  (1 << 26)  /* Fatal Error */

#define R_MIPI_DSI_RXRSSR_RXFAIL                  (1 << 27)  /* Receive Fail */

#define R_MIPI_DSI_RXRSSR_RXPFAIL                 (1 << 28)  /* Receive Packet Data Fail */

#define R_MIPI_DSI_RXRSSR_RXCERR                  (1 << 29)  /* Receive Correctable Error */

#define R_MIPI_DSI_RXRSSR_RXAKE                   (1 << 30)  /* Receive Acknowledge and Error Report Packet */

#define R_MIPI_DSI_RXRSSR_INFOOW                  (1 << 31)  /* Information Overwrite */

#define R_MIPI_DSI_RXRSSR_SLT0VLD                 (1 << 0)  /* Slot-0 Valid Flag */

#define R_MIPI_DSI_RXRSSR_SLT1VLD                 (1 << 1)  /* Slot-1 Valid Flag */

#define R_MIPI_DSI_RXRSSR_SLT2VLD                 (1 << 2)  /* Slot-2 Valid Flag */

#define R_MIPI_DSI_RXRSSR_SLT3VLD                 (1 << 3)  /* Slot-3 Valid Flag */

/* RXPPD0R Register bit definitions */
#define R_MIPI_DSI_RXPPD0R_DATA0_SHIFT            (0)  /* Payload Data 0 */
#define R_MIPI_DSI_RXPPD0R_DATA0_MASK             0xff

#define R_MIPI_DSI_RXPPD0R_DATA1_SHIFT            (8)  /* Payload Data 1 */
#define R_MIPI_DSI_RXPPD0R_DATA1_MASK             0xff00

#define R_MIPI_DSI_RXPPD0R_DATA2_SHIFT            (16)  /* Payload Data 2 */
#define R_MIPI_DSI_RXPPD0R_DATA2_MASK             0xff0000

#define R_MIPI_DSI_RXPPD0R_DATA3_SHIFT            (24)  /* Payload Data 3 */
#define R_MIPI_DSI_RXPPD0R_DATA3_MASK             0xff000000

/* RXPPD1R Register bit definitions */
#define R_MIPI_DSI_RXPPD1R_DATA4_SHIFT            (0)  /* Payload Data 4 */
#define R_MIPI_DSI_RXPPD1R_DATA4_MASK             0xff

#define R_MIPI_DSI_RXPPD1R_DATA5_SHIFT            (8)  /* Payload Data 5 */
#define R_MIPI_DSI_RXPPD1R_DATA5_MASK             0xff00

#define R_MIPI_DSI_RXPPD1R_DATA6_SHIFT            (16)  /* Payload Data 6 */
#define R_MIPI_DSI_RXPPD1R_DATA6_MASK             0xff0000

#define R_MIPI_DSI_RXPPD1R_DATA7_SHIFT            (24)  /* Payload Data 7 */
#define R_MIPI_DSI_RXPPD1R_DATA7_MASK             0xff000000

/* RXPPD2R Register bit definitions */
#define R_MIPI_DSI_RXPPD2R_DATA8_SHIFT            (0)  /* Payload Data 8 */
#define R_MIPI_DSI_RXPPD2R_DATA8_MASK             0xff

#define R_MIPI_DSI_RXPPD2R_DATA9_SHIFT            (8)  /* Payload Data 9 */
#define R_MIPI_DSI_RXPPD2R_DATA9_MASK             0xff00

#define R_MIPI_DSI_RXPPD2R_DATA10_SHIFT           (16)  /* Payload Data 10 */
#define R_MIPI_DSI_RXPPD2R_DATA10_MASK            0xff0000

#define R_MIPI_DSI_RXPPD2R_DATA11_SHIFT           (24)  /* Payload Data 11 */
#define R_MIPI_DSI_RXPPD2R_DATA11_MASK            0xff000000

/* RXPPD3R Register bit definitions */
#define R_MIPI_DSI_RXPPD3R_DATA12_SHIFT           (0)  /* Payload Data 12 */
#define R_MIPI_DSI_RXPPD3R_DATA12_MASK            0xff

#define R_MIPI_DSI_RXPPD3R_DATA13_SHIFT           (8)  /* Payload Data 13 */
#define R_MIPI_DSI_RXPPD3R_DATA13_MASK            0xff00

#define R_MIPI_DSI_RXPPD3R_DATA14_SHIFT           (16)  /* Payload Data 14 */
#define R_MIPI_DSI_RXPPD3R_DATA14_MASK            0xff0000

#define R_MIPI_DSI_RXPPD3R_DATA15_SHIFT           (24)  /* Payload Data 15 */
#define R_MIPI_DSI_RXPPD3R_DATA15_MASK            0xff000000

/* HSTXTOSETR Register bit definitions */
#define R_MIPI_DSI_HSTXTOSETR_HTXTO_SHIFT         (0)  /* HS TX Timeout Count */
#define R_MIPI_DSI_HSTXTOSETR_HTXTO_MASK          0xffffffff

/* LRXHTOSETR Register bit definitions */
#define R_MIPI_DSI_LRXHTOSETR_LRXHTO_SHIFT        (0)  /* LP-RX Host Processor Timeout */
#define R_MIPI_DSI_LRXHTOSETR_LRXHTO_MASK         0xffffffff

/* TATOSETR Register bit definitions */
#define R_MIPI_DSI_TATOSETR_TATO_SHIFT            (0)  /* Turnaround Acknowledge Timeout */
#define R_MIPI_DSI_TATOSETR_TATO_MASK             0xffffffff

/* FERRSR Register bit definitions */
#define R_MIPI_DSI_FERRSR_HTXTO                   (1 << 0)  /* HS TX Timeout Interrupt Flag */

#define R_MIPI_DSI_FERRSR_LRXHTO                  (1 << 1)  /* LP-RX Host Processor Timeout Interrupt Flag */

#define R_MIPI_DSI_FERRSR_TATO                    (1 << 2)  /* Turnaround Acknowledge Timeout Interrupt Flag */

#define R_MIPI_DSI_FERRSR_ESCENT                  (1 << 16)  /* Escape mode Entry Error Interrupt Flag */

#define R_MIPI_DSI_FERRSR_SYNCESC                 (1 << 17)  /* LPDT Sync Error Interrupt Flag */

#define R_MIPI_DSI_FERRSR_CTRL                    (1 << 18)  /* Control Error Interrupt Flag */

#define R_MIPI_DSI_FERRSR_CLP0                    (1 << 19)  /* LP0 Contention Error Interrupt Flag */

#define R_MIPI_DSI_FERRSR_CLP1                    (1 << 20)  /* LP1 Contention Error Interrupt Flag */

#define R_MIPI_DSI_FERRSR_CLP0S                   (1 << 27)  /* LP0 Contention Error Status */

#define R_MIPI_DSI_FERRSR_CLP1S                   (1 << 28)  /* LP1 Contention Error Status */

/* FERRSCR Register bit definitions */
#define R_MIPI_DSI_FERRSCR_HTXTO                  (1 << 0)  /* HS TX Timeout Interrupt Flag Clear */

#define R_MIPI_DSI_FERRSCR_LRXHTO                 (1 << 1)  /* LP-RX Host Processor Timeout Interrupt Flag Clear */

#define R_MIPI_DSI_FERRSCR_TATO                   (1 << 2)  /* Turnaround Acknowledge Timeout Interrupt Flag Clear */

#define R_MIPI_DSI_FERRSCR_ESCENT                 (1 << 16)  /* Escape Mode Entry Error Interrupt Flag Clear */

#define R_MIPI_DSI_FERRSCR_SYNCESC                (1 << 17)  /* LPDT Sync Error Interrupt Flag Clear */

#define R_MIPI_DSI_FERRSCR_CTRL                   (1 << 18)  /* Control Error Interrupt Flag Clear */

#define R_MIPI_DSI_FERRSCR_CLP0                   (1 << 19)  /* LP0 Contention Error Interrupt Flag Clear */

#define R_MIPI_DSI_FERRSCR_CLP1                   (1 << 20)  /* LP1 Contention Error Interrupt Flag Clear */

/* FERRIER Register bit definitions */
#define R_MIPI_DSI_FERRIER_HTXTO                  (1 << 0)  /* HS TX Timeout Interrupt Enable */

#define R_MIPI_DSI_FERRIER_LRXHTO                 (1 << 1)  /* LP-RX Host Processor Timeout Interrupt Enable */

#define R_MIPI_DSI_FERRIER_TATO                   (1 << 2)  /* Turnaround Acknowledge Timeout Interrupt Enable */

#define R_MIPI_DSI_FERRIER_ESCENT                 (1 << 16)  /* Escape mode Entry Error Interrupt Enable */

#define R_MIPI_DSI_FERRIER_SYNCESC                (1 << 17)  /* LPDT Sync Error Interrupt Enable */

#define R_MIPI_DSI_FERRIER_CTRL                   (1 << 18)  /* Control Error Interrupt Enable */

#define R_MIPI_DSI_FERRIER_CLP0                   (1 << 19)  /* LP0 Contention Error Interrupt Enable */

#define R_MIPI_DSI_FERRIER_CLP1                   (1 << 20)  /* LP1 Contention Error Interrupt Enable */

/* CLSTPTSETR Register bit definitions */
#define R_MIPI_DSI_CLSTPTSETR_CLKSTPT_SHIFT       (2)  /* Clock Stop Time */
#define R_MIPI_DSI_CLSTPTSETR_CLKSTPT_MASK        0xffc

#define R_MIPI_DSI_CLSTPTSETR_CLKBFHT_SHIFT       (16)  /* Clock Beforehand Time */
#define R_MIPI_DSI_CLSTPTSETR_CLKBFHT_MASK        0xff0000

#define R_MIPI_DSI_CLSTPTSETR_CLKKPT_SHIFT        (24)  /* Clock Keep Time */
#define R_MIPI_DSI_CLSTPTSETR_CLKKPT_MASK         0xff000000

/* LPTRNSTSETR Register bit definitions */
#define R_MIPI_DSI_LPTRNSTSETR_GOLPBKT_SHIFT      (0)  /* Go LP and Back Time */
#define R_MIPI_DSI_LPTRNSTSETR_GOLPBKT_MASK       0x3ff

/* PLSR Register bit definitions */
#define R_MIPI_DSI_PLSR_CLUAN                     (1 << 0)  /* Clock Lane UlpsActiveNot Status */

#define R_MIPI_DSI_PLSR_CLSTP                     (1 << 1)  /* Clock Lane Stop Status */

#define R_MIPI_DSI_PLSR_DL0RLE                    (1 << 2)  /* Data Lane-0 RxLpdtEsc Status */

#define R_MIPI_DSI_PLSR_DL0RUE                    (1 << 3)  /* Data Lane-0 RxUlpsEsc Status */

#define R_MIPI_DSI_PLSR_DL0UAN                    (1 << 4)  /* Data Lane-0 UlpsActiveNot Status */

#define R_MIPI_DSI_PLSR_DL1UAN                    (1 << 5)  /* Data Lane-1 UlpsActiveNot Status */

#define R_MIPI_DSI_PLSR_DL0STP                    (1 << 8)  /* Data Lane-0 Stop Status */

#define R_MIPI_DSI_PLSR_DL1STP                    (1 << 9)  /* Data Lane-1 Stop Status */

#define R_MIPI_DSI_PLSR_DL0RX2TX                  (1 << 12)  /* Data Lane-0 RX to TX Transition Interrupt Flag */

#define R_MIPI_DSI_PLSR_DL0TX2RX                  (1 << 13)  /* Data Lane-0 TX to RX Transition Interrupt Flag */

#define R_MIPI_DSI_PLSR_DL0DIR                    (1 << 15)  /* Data Lane-0 Direction */

#define R_MIPI_DSI_PLSR_CLULPENT                  (1 << 24)  /* Clock Lane ULPS Enter Interrupt Flag */

#define R_MIPI_DSI_PLSR_CLULPEXT                  (1 << 25)  /* Clock Lane ULPS Exit Interrupt Flag */

#define R_MIPI_DSI_PLSR_CLLP2HS                   (1 << 26)  /* Clock Lane LP to HS Transition Interrupt Flag */

#define R_MIPI_DSI_PLSR_CLHS2LP                   (1 << 27)  /* Clock Lane HS to LP Transition Interrupt Flag */

#define R_MIPI_DSI_PLSR_DLULPENT                  (1 << 28)  /* Data Lane ULPS Enter Interrupt Flag */

#define R_MIPI_DSI_PLSR_DLULPEXT                  (1 << 29)  /* Data Lane ULPS Exit Interrupt Flag */

/* PLSCR Register bit definitions */
#define R_MIPI_DSI_PLSCR_DL0RX2TX                 (1 << 12)  /* Data Lane-0 RX to TX Transition Interrupt Flag Clear */

#define R_MIPI_DSI_PLSCR_DL0TX2RX                 (1 << 13)  /* Data Lane-0 TX to RX Transition Interrupt Flag Clear */

#define R_MIPI_DSI_PLSCR_CLULPENT                 (1 << 24)  /* Clock Lane ULPS Enter Interrupt Flag Clear */

#define R_MIPI_DSI_PLSCR_CLULPEXT                 (1 << 25)  /* Clock Lane ULPS Exit Interrupt Flag Clear */

#define R_MIPI_DSI_PLSCR_CLLP2HS                  (1 << 26)  /* Clock Lane LP to HS Transition Interrupt Flag Clear */

#define R_MIPI_DSI_PLSCR_CLHS2LP                  (1 << 27)  /* Clock Lane HS to LP Transition Interrupt Flag Clear */

#define R_MIPI_DSI_PLSCR_DLULPENT                 (1 << 28)  /* Data Lane ULPS Enter Interrupt Flag Clear */

#define R_MIPI_DSI_PLSCR_DLULPEXT                 (1 << 29)  /* Data Lane ULPS Exit Interrupt Flag Clear */

/* PLIER Register bit definitions */
#define R_MIPI_DSI_PLIER_DL0RX2TX                 (1 << 12)  /* Data Lane-0 RX to TX Transition Interrupt Enable */

#define R_MIPI_DSI_PLIER_DL0TX2RX                 (1 << 13)  /* Data Lane-0 TX to RX Transition Interrupt Enable */

#define R_MIPI_DSI_PLIER_CLULPENT                 (1 << 24)  /* Clock Lane ULPS Enter Interrupt Enable */

#define R_MIPI_DSI_PLIER_CLULPEXT                 (1 << 25)  /* Clock Lane ULPS Exit Interrupt Enable */

#define R_MIPI_DSI_PLIER_CLLP2HS                  (1 << 26)  /* Clock Lane LP to HS Transition Interrupt Enable */

#define R_MIPI_DSI_PLIER_CLHS2LP                  (1 << 27)  /* Clock Lane HS to LP Transition Interrupt Enable */

#define R_MIPI_DSI_PLIER_DLULPENT                 (1 << 28)  /* Data Lane ULPS Enter Interrupt Enable */

#define R_MIPI_DSI_PLIER_DLULPEXT                 (1 << 29)  /* Data Lane ULPS Exit Interrupt Enable */

/* VMSET0R Register bit definitions */
#define R_MIPI_DSI_VMSET0R_VSTART                 (1 << 0)  /* Video Mode Operation Start */

#define R_MIPI_DSI_VMSET0R_VSTOP                  (1 << 1)  /* Video Mode Operation Stop */

#define R_MIPI_DSI_VMSET0R_HSANOLP                (1 << 8)  /* HSA Period No LP */

#define R_MIPI_DSI_VMSET0R_HBPNOLP                (1 << 9)  /* HBP Period No LP */

#define R_MIPI_DSI_VMSET0R_HFPNOLP                (1 << 10)  /* HFP Period No LP */

/* VMSET1R Register bit definitions */
#define R_MIPI_DSI_VMSET1R_DLY_SHIFT              (2)  /* Delay Value */
#define R_MIPI_DSI_VMSET1R_DLY_MASK               0x3ffc

/* VMSR Register bit definitions */
#define R_MIPI_DSI_VMSR_START                     (1 << 0)  /* Video Mode Operation Start Interrupt Flag */

#define R_MIPI_DSI_VMSR_STOP                      (1 << 1)  /* Video Mode Operation Stop Interrupt Flag */

#define R_MIPI_DSI_VMSR_RUNNING                   (1 << 2)  /* Video Mode Operation Running Status */

#define R_MIPI_DSI_VMSR_VIRDY                     (1 << 3)  /* Video Mode Operation Ready Interrupt Flag */

#define R_MIPI_DSI_VMSR_TIMERR                    (1 << 20)  /* Timing Error Interrupt Flag */

#define R_MIPI_DSI_VMSR_VBUFUDF                   (1 << 22)  /* Video Buffer Underflow Error Interrupt Flag */

#define R_MIPI_DSI_VMSR_VBUFOVF                   (1 << 23)  /* Video Buffer Overflow Error Interrupt Flag */

/* VMSCR Register bit definitions */
#define R_MIPI_DSI_VMSCR_START                    (1 << 0)  /* Video Mode Operation Start Interrupt Flag Clear */

#define R_MIPI_DSI_VMSCR_STOP                     (1 << 1)  /* Video Mode Operation Stop Interrupt Flag Clear */

#define R_MIPI_DSI_VMSCR_VIRDY                    (1 << 3)  /* Video Mode Operation Ready Interrupt Flag Clear */

#define R_MIPI_DSI_VMSCR_TIMERR                   (1 << 20)  /* Timing Error Interrupt Flag Clear */

#define R_MIPI_DSI_VMSCR_VBUFUDF                  (1 << 22)  /* Video Buffer Underflow Error Interrupt Flag Clear */

#define R_MIPI_DSI_VMSCR_VBUFOVF                  (1 << 23)  /* Video Buffer Overflow Error Interrupt Flag Clear */

/* VMIER Register bit definitions */
#define R_MIPI_DSI_VMIER_START                    (1 << 0)  /* Video Mode Operation Start Interrupt Enable */

#define R_MIPI_DSI_VMIER_STOP                     (1 << 1)  /* Video Mode Operation Stop Interrupt Enable */

#define R_MIPI_DSI_VMIER_VIRDY                    (1 << 3)  /* Video Mode Operation Ready Interrupt Enable */

#define R_MIPI_DSI_VMIER_TIMERR                   (1 << 20)  /* Timing Error Interrupt Enable */

#define R_MIPI_DSI_VMIER_VBUFUDF                  (1 << 22)  /* Video Buffer Underflow Error Interrupt Enable */

#define R_MIPI_DSI_VMIER_VBUFOVF                  (1 << 23)  /* Video Buffer Overflow Error Interrupt Enable */

/* VMPPSETR Register bit definitions */
#define R_MIPI_DSI_VMPPSETR_TXESYNC               (1 << 15)  /* Transmit End of Sync Pulse */

#define R_MIPI_DSI_VMPPSETR_DT_SHIFT              (16)  /* Video Mode Data Type */
#define R_MIPI_DSI_VMPPSETR_DT_MASK               0x3f0000
#  define R_MIPI_DSI_VMPPSETR_DT_0X0E                     (14 << R_MIPI_DSI_VMPPSETR_DT_SHIFT)  /* Packed Pixel Stream, 16-bit RGB */
#  define R_MIPI_DSI_VMPPSETR_DT_0X1E                     (30 << R_MIPI_DSI_VMPPSETR_DT_SHIFT)  /* Packed Pixel Stream, 18-bit RGB */
#  define R_MIPI_DSI_VMPPSETR_DT_0X3E                     (62 << R_MIPI_DSI_VMPPSETR_DT_SHIFT)  /* Packed Pixel Stream, 24-bit RGB */

#define R_MIPI_DSI_VMPPSETR_VC_SHIFT              (22)  /* Video Mode Virtual Channel */
#define R_MIPI_DSI_VMPPSETR_VC_MASK               0xc00000

/* VMVSSETR Register bit definitions */
#define R_MIPI_DSI_VMVSSETR_VSA_SHIFT             (0)  /* VSA Lines */
#define R_MIPI_DSI_VMVSSETR_VSA_MASK              0xfff

#define R_MIPI_DSI_VMVSSETR_VSPOL                 (1 << 15)  /* VSYNC Polarity */

#define R_MIPI_DSI_VMVSSETR_VACT_SHIFT            (16)  /* Vertical Active Lines */
#define R_MIPI_DSI_VMVSSETR_VACT_MASK             0x7fff0000

/* VMVPSETR Register bit definitions */
#define R_MIPI_DSI_VMVPSETR_VBP_SHIFT             (0)  /* VBP Lines */
#define R_MIPI_DSI_VMVPSETR_VBP_MASK              0x1fff

#define R_MIPI_DSI_VMVPSETR_VFP_SHIFT             (16)  /* VFP Lines */
#define R_MIPI_DSI_VMVPSETR_VFP_MASK              0x1fff0000

/* VMHSSETR Register bit definitions */
#define R_MIPI_DSI_VMHSSETR_HSA_SHIFT             (0)  /* HSA Pixels */
#define R_MIPI_DSI_VMHSSETR_HSA_MASK              0xfff

#define R_MIPI_DSI_VMHSSETR_HSPOL                 (1 << 15)  /* HSYNC Polarity */

#define R_MIPI_DSI_VMHSSETR_HACT_SHIFT            (16)  /* HACT Pixels */
#define R_MIPI_DSI_VMHSSETR_HACT_MASK             0x7fff0000

/* VMHPSETR Register bit definitions */
#define R_MIPI_DSI_VMHPSETR_HBP_SHIFT             (0)  /* HBP Pixels */
#define R_MIPI_DSI_VMHPSETR_HBP_MASK              0x1fff

#define R_MIPI_DSI_VMHPSETR_HFP_SHIFT             (16)  /* HFP Pixels */
#define R_MIPI_DSI_VMHPSETR_HFP_MASK              0x1fff0000

/* SQCH0SET0R Register bit definitions */
#define R_MIPI_DSI_SQCH0SET0R_START               (1 << 0)  /* Sequence Operation Start */

/* SQCH0SR Register bit definitions */
#define R_MIPI_DSI_SQCH0SR_RUNNING                (1 << 2)  /* Sequence Operation Running Status */

#define R_MIPI_DSI_SQCH0SR_AACTFIN                (1 << 4)  /* All Actions Finish Interrupt Flag */

#define R_MIPI_DSI_SQCH0SR_ADESFIN                (1 << 8)  /* All Descriptors Finish Interrupt Flag */

#define R_MIPI_DSI_SQCH0SR_TXIBERR                (1 << 24)  /* TX Internal Bus Error Interrupt Flag */

#define R_MIPI_DSI_SQCH0SR_RXFERR                 (1 << 26)  /* Receive Fatal Error Interrupt Flag */

#define R_MIPI_DSI_SQCH0SR_RXFAIL                 (1 << 27)  /* Receive Fail Interrupt Flag */

#define R_MIPI_DSI_SQCH0SR_RXPFAIL                (1 << 28)  /* Receive Packet Data Fail Interrupt Flag */

#define R_MIPI_DSI_SQCH0SR_RXCORERR               (1 << 29)  /* Receive Correctable Error Interrupt Flag */

#define R_MIPI_DSI_SQCH0SR_RXAKE                  (1 << 30)  /* Receive Acknowledge and Error Report Packet Interrupt Flag */

#define R_MIPI_DSI_SQCH0SR_DABORT                 (1 << 16)  /* Descriptor Abort Interrupt Flag */

#define R_MIPI_DSI_SQCH0SR_SIZEERR                (1 << 19)  /* Packet Size Error Interrupt Flag */

/* SQCH0SCR Register bit definitions */
#define R_MIPI_DSI_SQCH0SCR_AACTFIN               (1 << 4)  /* All Actions Finish Interrupt Flag Clear */

#define R_MIPI_DSI_SQCH0SCR_ADESFIN               (1 << 8)  /* All Descriptors Finish Interrupt Flag Clear */

#define R_MIPI_DSI_SQCH0SCR_TXIBERR               (1 << 24)  /* TX Internal Bus Error Interrupt Flag Clear */

#define R_MIPI_DSI_SQCH0SCR_RXFERR                (1 << 26)  /* Receive Fatal Error Interrupt Flag Clear */

#define R_MIPI_DSI_SQCH0SCR_RXFAIL                (1 << 27)  /* Receive Fail Interrupt Flag Clear */

#define R_MIPI_DSI_SQCH0SCR_RXPFAIL               (1 << 28)  /* Receive Packet Data Fail Interrupt Flag Clear */

#define R_MIPI_DSI_SQCH0SCR_RXCORERR              (1 << 29)  /* Receive Correctable Error Interrupt Flag Clear */

#define R_MIPI_DSI_SQCH0SCR_RXAKE                 (1 << 30)  /* Receive Acknowledge and Error Report Packet Interrupt Flag Clear */

#define R_MIPI_DSI_SQCH0SCR_DABORT                (1 << 16)  /* Descriptor Abort Interrupt Flag Clear */

#define R_MIPI_DSI_SQCH0SCR_SIZEERR               (1 << 19)  /* Packet Size Error Interrupt Flag Clear */

/* SQCH0IER Register bit definitions */
#define R_MIPI_DSI_SQCH0IER_AACTFIN               (1 << 4)  /* All Actions Finish Interrupt Enable */

#define R_MIPI_DSI_SQCH0IER_ADESFIN               (1 << 8)  /* All Descriptors Finish Interrupt Enable */

#define R_MIPI_DSI_SQCH0IER_TXIBERR               (1 << 24)  /* TX Internal Bus Error Interrupt Enable */

#define R_MIPI_DSI_SQCH0IER_RXFERR                (1 << 26)  /* Receive Fatal Error Interrupt Enable */

#define R_MIPI_DSI_SQCH0IER_RXFAIL                (1 << 27)  /* Receive Fail Interrupt Enable */

#define R_MIPI_DSI_SQCH0IER_RXPFAIL               (1 << 28)  /* Receive Packet Data Fail Interrupt Enable */

#define R_MIPI_DSI_SQCH0IER_RXCORERR              (1 << 29)  /* Receive Correctable Error Interrupt Enable */

#define R_MIPI_DSI_SQCH0IER_RXAKE                 (1 << 30)  /* Receive Acknowledge and Error Report Packet Interrupt Enable */

#define R_MIPI_DSI_SQCH0IER_DABORT                (1 << 16)  /* Descriptor Abort Interrupt Enable */

#define R_MIPI_DSI_SQCH0IER_SIZEERR               (1 << 19)  /* Packet Size Error Interrupt Enable */

/* SQCH1SET0R Register bit definitions */
#define R_MIPI_DSI_SQCH1SET0R_START               (1 << 0)  /* Sequence Operation Start */

/* SQCH1SR Register bit definitions */
#define R_MIPI_DSI_SQCH1SR_RUNNING                (1 << 2)  /* Sequence Operation Running Status */

#define R_MIPI_DSI_SQCH1SR_AACTFIN                (1 << 4)  /* All Actions Finish Interrupt Flag */

#define R_MIPI_DSI_SQCH1SR_ADESFIN                (1 << 8)  /* All Descriptors Finish Interrupt Flag */

#define R_MIPI_DSI_SQCH1SR_SIZEERR                (1 << 19)  /* Packet Size Error Interrupt Flag */

#define R_MIPI_DSI_SQCH1SR_TXIBERR                (1 << 24)  /* TX Internal Bus Error Interrupt Flag */

#define R_MIPI_DSI_SQCH1SR_RXFERR                 (1 << 26)  /* Receive Fatal Error Interrupt Flag */

#define R_MIPI_DSI_SQCH1SR_RXFAIL                 (1 << 27)  /* Receive Fail Interrupt Flag */

#define R_MIPI_DSI_SQCH1SR_RXPFAIL                (1 << 28)  /* Receive Packet Data Fail Interrupt Flag */

#define R_MIPI_DSI_SQCH1SR_RXCORERR               (1 << 29)  /* Receive Correctable Error Interrupt Flag */

#define R_MIPI_DSI_SQCH1SR_RXAKE                  (1 << 30)  /* Receive Acknowledge and Error Report Packet Interrupt Flag */

#define R_MIPI_DSI_SQCH1SR_DABORT                 (1 << 16)  /* Descriptor Abort Interrupt Flag */

/* SQCH1SCR Register bit definitions */
#define R_MIPI_DSI_SQCH1SCR_AACTFIN               (1 << 4)  /* All Actions Finish Interrupt Flag Clear */

#define R_MIPI_DSI_SQCH1SCR_ADESFIN               (1 << 8)  /* All Descriptors Finish Interrupt Flag Clear */

#define R_MIPI_DSI_SQCH1SCR_SIZEERR               (1 << 19)  /* Packet Size Error Interrupt Flag Clear */

#define R_MIPI_DSI_SQCH1SCR_TXIBERR               (1 << 24)  /* TX Internal Bus Error Interrupt Flag Clear */

#define R_MIPI_DSI_SQCH1SCR_RXFERR                (1 << 26)  /* Receive Fatal Error Interrupt Flag Clear */

#define R_MIPI_DSI_SQCH1SCR_RXFAIL                (1 << 27)  /* Receive Fail Interrupt Flag Clear */

#define R_MIPI_DSI_SQCH1SCR_RXPFAIL               (1 << 28)  /* Receive Packet Data Fail Interrupt Flag Clear */

#define R_MIPI_DSI_SQCH1SCR_RXCORERR              (1 << 29)  /* Receive Correctable Error Interrupt Flag Clear */

#define R_MIPI_DSI_SQCH1SCR_RXAKE                 (1 << 30)  /* Receive Acknowledge and Error Report Packet Interrupt Flag Clear */

#define R_MIPI_DSI_SQCH1SCR_DABORT                (1 << 16)  /* Descriptor Abort Interrupt Flag Clear */

/* SQCH1IER Register bit definitions */
#define R_MIPI_DSI_SQCH1IER_AACTFIN               (1 << 4)  /* All Actions Finish Interrupt Enable */

#define R_MIPI_DSI_SQCH1IER_ADESFIN               (1 << 8)  /* All Descriptors Finish Interrupt Enable */

#define R_MIPI_DSI_SQCH1IER_SIZEERR               (1 << 19)  /* Packet Size Error Interrupt Enable */

#define R_MIPI_DSI_SQCH1IER_TXIBERR               (1 << 24)  /* TX Internal Bus Error Interrupt Enable */

#define R_MIPI_DSI_SQCH1IER_RXFERR                (1 << 26)  /* Receive Fatal Error Interrupt Enable */

#define R_MIPI_DSI_SQCH1IER_RXFAIL                (1 << 27)  /* Receive Fail Interrupt Enable */

#define R_MIPI_DSI_SQCH1IER_RXPFAIL               (1 << 28)  /* Receive Packet Data Fail Interrupt Enable */

#define R_MIPI_DSI_SQCH1IER_RXCORERR              (1 << 29)  /* Receive Correctable Error Interrupt Enable */

#define R_MIPI_DSI_SQCH1IER_RXAKE                 (1 << 30)  /* Receive Acknowledge and Error Report Packet Interrupt Enable */

#define R_MIPI_DSI_SQCH1IER_DABORT                (1 << 16)  /* Descriptor Abort Interrupt Enable */

/* SQCH0DSCAR Register bit definitions */
#define R_MIPI_DSI_SQCH0DSCAR_DATA0_SHIFT         (0)  /* Data 0 */
#define R_MIPI_DSI_SQCH0DSCAR_DATA0_MASK          0xff

#define R_MIPI_DSI_SQCH0DSCAR_DATA1_SHIFT         (8)  /* Data 1 */
#define R_MIPI_DSI_SQCH0DSCAR_DATA1_MASK          0xff00

#define R_MIPI_DSI_SQCH0DSCAR_DT_SHIFT            (16)  /* Data Type */
#define R_MIPI_DSI_SQCH0DSCAR_DT_MASK             0x3f0000

#define R_MIPI_DSI_SQCH0DSCAR_VC_SHIFT            (22)  /* Virtual Channel */
#define R_MIPI_DSI_SQCH0DSCAR_VC_MASK             0xc00000

#define R_MIPI_DSI_SQCH0DSCAR_FMT                 (1 << 24)  /* Format */

#define R_MIPI_DSI_SQCH0DSCAR_SPD                 (1 << 25)  /* Speed */

#define R_MIPI_DSI_SQCH0DSCAR_BTA_SHIFT           (26)  /* Bus Turn Around */
#define R_MIPI_DSI_SQCH0DSCAR_BTA_MASK            0xc000000
#  define R_MIPI_DSI_SQCH0DSCAR_BTA_00                    (0 << R_MIPI_DSI_SQCH0DSCAR_BTA_SHIFT)  /* TX request without BTA or no-operation */
#  define R_MIPI_DSI_SQCH0DSCAR_BTA_01                    (1 << R_MIPI_DSI_SQCH0DSCAR_BTA_SHIFT)  /* TX non-read request with BTA */
#  define R_MIPI_DSI_SQCH0DSCAR_BTA_10                    (2 << R_MIPI_DSI_SQCH0DSCAR_BTA_SHIFT)  /* TX read request with BTA */
#  define R_MIPI_DSI_SQCH0DSCAR_BTA_11                    (3 << R_MIPI_DSI_SQCH0DSCAR_BTA_SHIFT)  /* BTA only */

#define R_MIPI_DSI_SQCH0DSCAR_NXACT_SHIFT         (28)  /* Next Action */
#define R_MIPI_DSI_SQCH0DSCAR_NXACT_MASK          0x30000000
#  define R_MIPI_DSI_SQCH0DSCAR_NXACT_00                  (0 << R_MIPI_DSI_SQCH0DSCAR_NXACT_SHIFT)  /* Terminate the sequence operation after this descriptor processing is finished */
#  define R_MIPI_DSI_SQCH0DSCAR_NXACT_01                  (1 << R_MIPI_DSI_SQCH0DSCAR_NXACT_SHIFT)  /* Start the next descriptor processing after this descriptor processing is finished */

/* SQCH0DSCBR Register bit definitions */
#define R_MIPI_DSI_SQCH0DSCBR_DTSEL_SHIFT         (24)  /* Data Select */
#define R_MIPI_DSI_SQCH0DSCBR_DTSEL_MASK          0x3000000
#  define R_MIPI_DSI_SQCH0DSCBR_DTSEL_00                  (0 << R_MIPI_DSI_SQCH0DSCBR_DTSEL_SHIFT)  /* Use Packet Payload Data Register (TXPPDxR, RXPPDxR)  */
#  define R_MIPI_DSI_SQCH0DSCBR_DTSEL_01                  (1 << R_MIPI_DSI_SQCH0DSCBR_DTSEL_SHIFT)  /* Use memory space */

/* SQCH0DSCCR Register bit definitions */
#define R_MIPI_DSI_SQCH0DSCCR_FINACT              (1 << 0)  /* Finish Action */

#define R_MIPI_DSI_SQCH0DSCCR_AUXOP               (1 << 22)  /* Auxiliary Operation */

#define R_MIPI_DSI_SQCH0DSCCR_ACTCODE_SHIFT       (24)  /* Action Code */
#define R_MIPI_DSI_SQCH0DSCCR_ACTCODE_MASK        0xff000000

/* SQCH0DSCDR Register bit definitions */
#define R_MIPI_DSI_SQCH0DSCDR_LADDR_SHIFT         (0)  /* Lower Address */
#define R_MIPI_DSI_SQCH0DSCDR_LADDR_MASK          0xffffffff

/* SQCH1DSCAR Register bit definitions */
#define R_MIPI_DSI_SQCH1DSCAR_DATA0_SHIFT         (0)  /* Data 0 */
#define R_MIPI_DSI_SQCH1DSCAR_DATA0_MASK          0xff

#define R_MIPI_DSI_SQCH1DSCAR_DATA1_SHIFT         (8)  /* Data 1 */
#define R_MIPI_DSI_SQCH1DSCAR_DATA1_MASK          0xff00

#define R_MIPI_DSI_SQCH1DSCAR_DT_SHIFT            (16)  /* Data Type */
#define R_MIPI_DSI_SQCH1DSCAR_DT_MASK             0x3f0000

#define R_MIPI_DSI_SQCH1DSCAR_VC_SHIFT            (22)  /* Virtual Channel */
#define R_MIPI_DSI_SQCH1DSCAR_VC_MASK             0xc00000

#define R_MIPI_DSI_SQCH1DSCAR_FMT                 (1 << 24)  /* Format */

#define R_MIPI_DSI_SQCH1DSCAR_SPD                 (1 << 25)  /* Speed */

#define R_MIPI_DSI_SQCH1DSCAR_BTA_SHIFT           (26)  /* Bus Turn Around */
#define R_MIPI_DSI_SQCH1DSCAR_BTA_MASK            0xc000000
#  define R_MIPI_DSI_SQCH1DSCAR_BTA_00                    (0 << R_MIPI_DSI_SQCH1DSCAR_BTA_SHIFT)  /* TX request without BTA or no-operation */
#  define R_MIPI_DSI_SQCH1DSCAR_BTA_01                    (1 << R_MIPI_DSI_SQCH1DSCAR_BTA_SHIFT)  /* TX non-read request with BTA */
#  define R_MIPI_DSI_SQCH1DSCAR_BTA_10                    (2 << R_MIPI_DSI_SQCH1DSCAR_BTA_SHIFT)  /* TX read request with BTA */
#  define R_MIPI_DSI_SQCH1DSCAR_BTA_11                    (3 << R_MIPI_DSI_SQCH1DSCAR_BTA_SHIFT)  /* BTA only */

#define R_MIPI_DSI_SQCH1DSCAR_NXACT_SHIFT         (28)  /* Next Action */
#define R_MIPI_DSI_SQCH1DSCAR_NXACT_MASK          0x30000000
#  define R_MIPI_DSI_SQCH1DSCAR_NXACT_00                  (0 << R_MIPI_DSI_SQCH1DSCAR_NXACT_SHIFT)  /* Terminate the sequence operation after this descriptor processing is finished */
#  define R_MIPI_DSI_SQCH1DSCAR_NXACT_01                  (1 << R_MIPI_DSI_SQCH1DSCAR_NXACT_SHIFT)  /* Start the next descriptor processing after this descriptor processing is finished */

/* SQCH1DSCBR Register bit definitions */
#define R_MIPI_DSI_SQCH1DSCBR_DTSEL_SHIFT         (24)  /* Data Select */
#define R_MIPI_DSI_SQCH1DSCBR_DTSEL_MASK          0x3000000
#  define R_MIPI_DSI_SQCH1DSCBR_DTSEL_00                  (0 << R_MIPI_DSI_SQCH1DSCBR_DTSEL_SHIFT)  /* Use Packet Payload Data Register (TXPPDxR, RXPPDxR)  */
#  define R_MIPI_DSI_SQCH1DSCBR_DTSEL_01                  (1 << R_MIPI_DSI_SQCH1DSCBR_DTSEL_SHIFT)  /* Use memory space */

/* SQCH1DSCCR Register bit definitions */
#define R_MIPI_DSI_SQCH1DSCCR_FINACT              (1 << 0)  /* Finish Action */

#define R_MIPI_DSI_SQCH1DSCCR_AUXOP               (1 << 22)  /* Auxiliary Operation */

#define R_MIPI_DSI_SQCH1DSCCR_ACTCODE_SHIFT       (24)  /* Action Code */
#define R_MIPI_DSI_SQCH1DSCCR_ACTCODE_MASK        0xff000000

/* SQCH1DSCDR Register bit definitions */
#define R_MIPI_DSI_SQCH1DSCDR_LADDR_SHIFT         (0)  /* Lower Address */
#define R_MIPI_DSI_SQCH1DSCDR_LADDR_MASK          0xffffffff


/* Maximum number of channels */

#define MIPI_DSI_MAX_CHANNELS    8

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MIPI_DSI_H */
