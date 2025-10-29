/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_xspi.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_XSPI_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_XSPI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* XSPI Base Address */
#ifndef R_XSPI_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_XSPI_BASE           0x40268000
#else
#define R_XSPI_BASE           0x50268000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_XSPI_CH_STRIDE    0x00000400
#define R_XSPI_CH_BASE(ch)   (R_XSPI_BASE + ((uint32_t)(ch) * R_XSPI_CH_STRIDE))

/* XSPI Register Offsets */

#define R_XSPI_WRAPCFG_OFFSET                     0x00000000  /* xSPI Wrapper Configuration register */
#define R_XSPI_COMCFG_OFFSET                      0x00000004  /* xSPI Common Configuration register */
/* BMCFGCH[%s] Registers () */
#define R_XSPI_BMCFGCH_OFFSET(m)                  (0x00000008 + ((m) * 0x00000004))  /* xSPI Bridge Map Configuration register */
/* CMCFGCS[%s] Registers () */
#define R_XSPI_CMCFGCS_OFFSET(m)                  (0x00000010 + ((m) * 0x00000010))  /* xSPI Command Map Configuration registers */
/* LIOCFGCS[%s] Registers () */
#define R_XSPI_LIOCFGCS_OFFSET(m)                 (0x00000050 + ((m) * 0x00000004))  /* xSPI Link I/O Configuration register CS%s */
#define R_XSPI_ABMCFG_OFFSET                      0x00000058  /* xSPI AXI Bridge Map Config */
#define R_XSPI_BMCTL0_OFFSET                      0x00000060  /* xSPI Bridge Map Control register 0 */
#define R_XSPI_BMCTL1_OFFSET                      0x00000064  /* xSPI Bridge Map Control register 1 */
/* CMCTLCH[%s] Registers () */
#define R_XSPI_CMCTLCH_OFFSET(m)                  (0x00000068 + ((m) * 0x00000004))  /* xSPI Command Map Control register */
#define R_XSPI_CDCTL0_OFFSET                      0x00000070  /* xSPI Command Manual Control register 0 */
#define R_XSPI_CDCTL1_OFFSET                      0x00000074  /* xSPI Command Manual Control register 1 */
#define R_XSPI_CDCTL2_OFFSET                      0x00000078  /* xSPI Command Manual Control register 2 */
/* CDBUF[%s] Registers () */
#define R_XSPI_CDBUF_OFFSET(m)                    (0x00000080 + ((m) * 0x00000010))  /* xSPI BUF register */
#define R_XSPI_LPCTL0_OFFSET                      0x00000100  /* xSPI Link Pattern Control register 0 */
#define R_XSPI_LPCTL1_OFFSET                      0x00000104  /* xSPI Link Pattern Control register 1 */
#define R_XSPI_LIOCTL_OFFSET                      0x00000108  /* xSPI Link I/O Control register */
/* CCCTLCS[%s] Registers () */
#define R_XSPI_CCCTLCS_OFFSET(m)                  (0x00000130 + ((m) * 0x00000020))  /* xSPI CS register */
#define R_XSPI_VERSTT_OFFSET                      0x00000180  /* xSPI Version register */
#define R_XSPI_COMSTT_OFFSET                      0x00000184  /* xSPI Common Status register */
/* CASTTCS[%s] Registers () */
#define R_XSPI_CASTTCS_OFFSET(m)                  (0x00000188 + ((m) * 0x00000004))  /* xSPI Calibration Status register */
#define R_XSPI_INTS_OFFSET                        0x00000190  /* xSPI Interrupt Status register */
#define R_XSPI_INTC_OFFSET                        0x00000194  /* xSPI Interrupt Clear register */
#define R_XSPI_INTE_OFFSET                        0x00000198  /* xSPI Interrupt Enable register */

/* XSPI Register Addresses */

#define R_XSPI_WRAPCFG(n)                         (R_XSPI_CH_BASE(n) + R_XSPI_WRAPCFG_OFFSET)
#define R_XSPI_COMCFG(n)                          (R_XSPI_CH_BASE(n) + R_XSPI_COMCFG_OFFSET)
#define R_XSPI_BMCFGCH(n, m)                      (R_XSPI_CH_BASE(n) + R_XSPI_BMCFGCH_OFFSET(m))
#define R_XSPI_CMCFGCS(n, m)                      (R_XSPI_CH_BASE(n) + R_XSPI_CMCFGCS_OFFSET(m))
#define R_XSPI_LIOCFGCS(n, m)                     (R_XSPI_CH_BASE(n) + R_XSPI_LIOCFGCS_OFFSET(m))
#define R_XSPI_ABMCFG(n)                          (R_XSPI_CH_BASE(n) + R_XSPI_ABMCFG_OFFSET)
#define R_XSPI_BMCTL0(n)                          (R_XSPI_CH_BASE(n) + R_XSPI_BMCTL0_OFFSET)
#define R_XSPI_BMCTL1(n)                          (R_XSPI_CH_BASE(n) + R_XSPI_BMCTL1_OFFSET)
#define R_XSPI_CMCTLCH(n, m)                      (R_XSPI_CH_BASE(n) + R_XSPI_CMCTLCH_OFFSET(m))
#define R_XSPI_CDCTL0(n)                          (R_XSPI_CH_BASE(n) + R_XSPI_CDCTL0_OFFSET)
#define R_XSPI_CDCTL1(n)                          (R_XSPI_CH_BASE(n) + R_XSPI_CDCTL1_OFFSET)
#define R_XSPI_CDCTL2(n)                          (R_XSPI_CH_BASE(n) + R_XSPI_CDCTL2_OFFSET)
#define R_XSPI_CDBUF(n, m)                        (R_XSPI_CH_BASE(n) + R_XSPI_CDBUF_OFFSET(m))
#define R_XSPI_LPCTL0(n)                          (R_XSPI_CH_BASE(n) + R_XSPI_LPCTL0_OFFSET)
#define R_XSPI_LPCTL1(n)                          (R_XSPI_CH_BASE(n) + R_XSPI_LPCTL1_OFFSET)
#define R_XSPI_LIOCTL(n)                          (R_XSPI_CH_BASE(n) + R_XSPI_LIOCTL_OFFSET)
#define R_XSPI_CCCTLCS(n, m)                      (R_XSPI_CH_BASE(n) + R_XSPI_CCCTLCS_OFFSET(m))
#define R_XSPI_VERSTT(n)                          (R_XSPI_CH_BASE(n) + R_XSPI_VERSTT_OFFSET)
#define R_XSPI_COMSTT(n)                          (R_XSPI_CH_BASE(n) + R_XSPI_COMSTT_OFFSET)
#define R_XSPI_CASTTCS(n, m)                      (R_XSPI_CH_BASE(n) + R_XSPI_CASTTCS_OFFSET(m))
#define R_XSPI_INTS(n)                            (R_XSPI_CH_BASE(n) + R_XSPI_INTS_OFFSET)
#define R_XSPI_INTC(n)                            (R_XSPI_CH_BASE(n) + R_XSPI_INTC_OFFSET)
#define R_XSPI_INTE(n)                            (R_XSPI_CH_BASE(n) + R_XSPI_INTE_OFFSET)

/* Register bit definitions */
/* WRAPCFG Register bit definitions */
#define R_XSPI_WRAPCFG_CKSFTCS0_SHIFT             (0)  /* CK shift for slave0 */
#define R_XSPI_WRAPCFG_CKSFTCS0_MASK              0x1f
#  define R_XSPI_WRAPCFG_CKSFTCS0_0                       (0 << R_XSPI_WRAPCFG_CKSFTCS0_SHIFT)  /* No shift */
#  define R_XSPI_WRAPCFG_CKSFTCS0_1                       (1 << R_XSPI_WRAPCFG_CKSFTCS0_SHIFT)  /* Add a delay of 1 cell */

#define R_XSPI_WRAPCFG_RESERVED_SHIFT             (29)  /* These bits are read as 000. The write value should be 000. */
#define R_XSPI_WRAPCFG_RESERVED_MASK              0xe0000000

#define R_XSPI_WRAPCFG_DSSFTCS0_SHIFT             (8)  /* DS shift for slave0 */
#define R_XSPI_WRAPCFG_DSSFTCS0_MASK              0x1f00
#  define R_XSPI_WRAPCFG_DSSFTCS0_0                       (0 << R_XSPI_WRAPCFG_DSSFTCS0_SHIFT)  /* No shift */
#  define R_XSPI_WRAPCFG_DSSFTCS0_1                       (1 << R_XSPI_WRAPCFG_DSSFTCS0_SHIFT)  /* Add a delay of 1 cell */

#define R_XSPI_WRAPCFG_CKSFTCS1_SHIFT             (16)  /* CK shift for slave1 */
#define R_XSPI_WRAPCFG_CKSFTCS1_MASK              0x1f0000

#define R_XSPI_WRAPCFG_DSSFTCS1_SHIFT             (24)  /* DS shift for slave1 */
#define R_XSPI_WRAPCFG_DSSFTCS1_MASK              0x1f000000

/* COMCFG Register bit definitions */
#define R_XSPI_COMCFG_ARBMD_SHIFT                 (0)  /* Channel arbitration mode */
#define R_XSPI_COMCFG_ARBMD_MASK                  0x3

#define R_XSPI_COMCFG_RESERVED_SHIFT              (18)  /* These bits are read as 00000000000000. The write value should be 00000000000000. */
#define R_XSPI_COMCFG_RESERVED_MASK               0xfffc0000

#define R_XSPI_COMCFG_ECSINTOUTEN_SHIFT           (4)  /* ECS/INT Output Enable */
#define R_XSPI_COMCFG_ECSINTOUTEN_MASK            0x30

#define R_XSPI_COMCFG_OEASTEX                     (1 << 16)  /* Output Enable Asserting extension */

#define R_XSPI_COMCFG_OENEGEX                     (1 << 17)  /* Output Enable Negating extension */

/* BMCFGCH Register bit definitions */
#define R_XSPI_BMCFGCH_WRMD                       (1 << 0)  /* AHB Write Response mode */

#define R_XSPI_BMCFGCH_RESERVED_SHIFT             (17)  /* These bits are read as 0000000. The write value should be 0000000. */
#define R_XSPI_BMCFGCH_RESERVED_MASK              0xfe0000

#define R_XSPI_BMCFGCH_MWRCOMB                    (1 << 7)  /* Memory Write Combination mode */

#define R_XSPI_BMCFGCH_MWRSIZE_SHIFT              (8)  /* Memory Write Size */
#define R_XSPI_BMCFGCH_MWRSIZE_MASK               0xff00

#define R_XSPI_BMCFGCH_PREEN                      (1 << 16)  /* Prefetch enable */

#define R_XSPI_BMCFGCH_CMBTIM_SHIFT               (24)  /* Combination timer */
#define R_XSPI_BMCFGCH_CMBTIM_MASK                0xff000000
#  define R_XSPI_BMCFGCH_CMBTIM_00H                       (0 << R_XSPI_BMCFGCH_CMBTIM_SHIFT)  /* means disabling the combination timer. When the timer is */

/* LIOCFGCS Register bit definitions */
#define R_XSPI_LIOCFGCS_PRTMD_SHIFT               (0)  /* Protocol mode */
#define R_XSPI_LIOCFGCS_PRTMD_MASK                0x3ff
#  define R_XSPI_LIOCFGCS_PRTMD_0_000_000_000B            (0 << R_XSPI_LIOCFGCS_PRTMD_SHIFT)  /* 1S-1S-1S */
#  define R_XSPI_LIOCFGCS_PRTMD_1_110_110_010B            (946 << R_XSPI_LIOCFGCS_PRTMD_SHIFT)  /* 4S-4D-4D */
#  define R_XSPI_LIOCFGCS_PRTMD_1_111_111_111B            (1023 << R_XSPI_LIOCFGCS_PRTMD_SHIFT)  /* 8D-8D-8D */
#  define R_XSPI_LIOCFGCS_PRTMD_1_011_111_111B            (767 << R_XSPI_LIOCFGCS_PRTMD_SHIFT)  /* 8D-8D-8S */
#  define R_XSPI_LIOCFGCS_PRTMD_0_001_001_000B            (72 << R_XSPI_LIOCFGCS_PRTMD_SHIFT)  /* 1S-2S-2S */
#  define R_XSPI_LIOCFGCS_PRTMD_0_001_001_001B            (73 << R_XSPI_LIOCFGCS_PRTMD_SHIFT)  /* 2S-2S-2S */
#  define R_XSPI_LIOCFGCS_PRTMD_0_010_010_000B            (144 << R_XSPI_LIOCFGCS_PRTMD_SHIFT)  /* 1S-4S-4S */
#  define R_XSPI_LIOCFGCS_PRTMD_0_010_010_010B            (146 << R_XSPI_LIOCFGCS_PRTMD_SHIFT)  /* 4S-4S-4S */

#define R_XSPI_LIOCFGCS_LATEMD                    (1 << 10)  /* Latency mode */

#define R_XSPI_LIOCFGCS_WRMSKMD                   (1 << 11)  /* Write mask mode */

#define R_XSPI_LIOCFGCS_RESERVED                  (1 << 15)  /* This bit is read as 0. The write value should be 0. */

#define R_XSPI_LIOCFGCS_CSMIN_SHIFT               (16)  /* CS minimum idle term */
#define R_XSPI_LIOCFGCS_CSMIN_MASK                0xf0000
#  define R_XSPI_LIOCFGCS_CSMIN_0                         (0 << R_XSPI_LIOCFGCS_CSMIN_SHIFT)  /* 1 cycle */

#define R_XSPI_LIOCFGCS_CSASTEX                   (1 << 20)  /* CS asserting extension */

#define R_XSPI_LIOCFGCS_CSNEGEX                   (1 << 21)  /* CS negating extension */

#define R_XSPI_LIOCFGCS_SDRDRV                    (1 << 22)  /* SDR driving timing */

#define R_XSPI_LIOCFGCS_SDRSMPMD                  (1 << 23)  /* SDR Sampling mode */

#define R_XSPI_LIOCFGCS_SDRSMPSFT_SHIFT           (24)  /* SDR Sampling window shift */
#define R_XSPI_LIOCFGCS_SDRSMPSFT_MASK            0xf000000
#  define R_XSPI_LIOCFGCS_SDRSMPSFT_0                     (0 << R_XSPI_LIOCFGCS_SDRSMPSFT_SHIFT)  /* Sample w/o delay */
#  define R_XSPI_LIOCFGCS_SDRSMPSFT_1                     (1 << R_XSPI_LIOCFGCS_SDRSMPSFT_SHIFT)  /* Sample at 1 cycle delay */

#define R_XSPI_LIOCFGCS_DDRSMPEX_SHIFT            (28)  /* DDR sampling window extend */
#define R_XSPI_LIOCFGCS_DDRSMPEX_MASK             0xf0000000
#  define R_XSPI_LIOCFGCS_DDRSMPEX_0                      (0 << R_XSPI_LIOCFGCS_DDRSMPEX_SHIFT)  /* Expand no cycle */
#  define R_XSPI_LIOCFGCS_DDRSMPEX_1                      (1 << R_XSPI_LIOCFGCS_DDRSMPEX_SHIFT)  /* Expand 1 cycle */

/* ABMCFG Register bit definitions */
#define R_XSPI_ABMCFG_ODRMD_SHIFT                 (0)  /* AXI Transfer Ordering Mode */
#define R_XSPI_ABMCFG_ODRMD_MASK                  0x3

#define R_XSPI_ABMCFG_RESERVED_SHIFT              (2)  /* These bits are read as 00000000000000. The write value should be 00000000000000. */
#define R_XSPI_ABMCFG_RESERVED_MASK               0xfffc

#define R_XSPI_ABMCFG_CHSEL_SHIFT                 (16)  /* AXI ID to Bridge Channel Select */
#define R_XSPI_ABMCFG_CHSEL_MASK                  0xffff0000

/* BMCTL0 Register bit definitions */
#define R_XSPI_BMCTL0_CH0CS0ACC_SHIFT             (0)  /* System bus ch0 to slave0 memory area access enable */
#define R_XSPI_BMCTL0_CH0CS0ACC_MASK              0x3

#define R_XSPI_BMCTL0_CH0CS1ACC_SHIFT             (2)  /* System bus ch0 to slave1 memory area access enable */
#define R_XSPI_BMCTL0_CH0CS1ACC_MASK              0xc

#define R_XSPI_BMCTL0_CH1CS0ACC_SHIFT             (4)  /* System bus ch1 to slave0 memory area access enable */
#define R_XSPI_BMCTL0_CH1CS0ACC_MASK              0x30

#define R_XSPI_BMCTL0_CH1CS1ACC_SHIFT             (6)  /* System bus ch1 to slave1 memory area access enable */
#define R_XSPI_BMCTL0_CH1CS1ACC_MASK              0xc0

#define R_XSPI_BMCTL0_RESERVED_SHIFT              (16)  /* These bits are read as 0000000000000000. The write value should be 0000000000000000. */
#define R_XSPI_BMCTL0_RESERVED_MASK               0xffff0000

/* BMCTL1 Register bit definitions */
#define R_XSPI_BMCTL1_RESERVED_SHIFT              (16)  /* The write value should be 0000000000000000. */
#define R_XSPI_BMCTL1_RESERVED_MASK               0xffff0000

#define R_XSPI_BMCTL1_MWRPUSHCH_S                 (1 << 8)  /* Memory Write Data Push for ch%s */

#define R_XSPI_BMCTL1_PBUFCLRCH_S                 (1 << 10)  /* Prefetch Buffer clear for ch%s */

#define R_XSPI_BMCTL1_MWRPUSHCH0                  (1 << 8)  /* Memory Write Data Push for ch0 */

#define R_XSPI_BMCTL1_MWRPUSHCH1                  (1 << 9)  /* Memory Write Data Push for ch1 */

#define R_XSPI_BMCTL1_PBUFCLRCH0                  (1 << 10)  /* Prefetch Buffer clear for ch0 */

#define R_XSPI_BMCTL1_PBUFCLRCH1                  (1 << 11)  /* Prefetch Buffer clear for ch1 */

/* CMCTLCH Register bit definitions */
#define R_XSPI_CMCTLCH_XIPENCODE_SHIFT            (0)  /* XiP mode enter code */
#define R_XSPI_CMCTLCH_XIPENCODE_MASK             0xff

#define R_XSPI_CMCTLCH_XIPEXCODE_SHIFT            (8)  /* XiP mode exit code */
#define R_XSPI_CMCTLCH_XIPEXCODE_MASK             0xff00

#define R_XSPI_CMCTLCH_XIPEN                      (1 << 16)  /* XiP mode enable */

#define R_XSPI_CMCTLCH_RESERVED_SHIFT             (17)  /* These bits are read as 000000000000000. The write value should be 000000000000000. */
#define R_XSPI_CMCTLCH_RESERVED_MASK              0xfffe0000

/* CDCTL0 Register bit definitions */
#define R_XSPI_CDCTL0_TRREQ                       (1 << 0)  /* Transaction request */

#define R_XSPI_CDCTL0_PERMD                       (1 << 1)  /* Periodic mode */

#define R_XSPI_CDCTL0_RESERVED_SHIFT              (28)  /* These bits are read as 0000. The write value should be 0000. */
#define R_XSPI_CDCTL0_RESERVED_MASK               0xf0000000

#define R_XSPI_CDCTL0_CSSEL                       (1 << 3)  /* Chip select */

#define R_XSPI_CDCTL0_TRNUM_SHIFT                 (4)  /* Transaction number */
#define R_XSPI_CDCTL0_TRNUM_MASK                  0x30
#  define R_XSPI_CDCTL0_TRNUM_0                           (0 << R_XSPI_CDCTL0_TRNUM_SHIFT)  /* Issue 1 command (using command buffer0) */
#  define R_XSPI_CDCTL0_TRNUM_1                           (1 << R_XSPI_CDCTL0_TRNUM_SHIFT)  /* Issue 2 commands (using command buffer0-1) */

#define R_XSPI_CDCTL0_PERITV_SHIFT                (16)  /* Periodic transaction interval */
#define R_XSPI_CDCTL0_PERITV_MASK                 0x1f0000
#  define R_XSPI_CDCTL0_PERITV_0                          (0 << R_XSPI_CDCTL0_PERITV_SHIFT)  /* 2(=2^1) cycles */
#  define R_XSPI_CDCTL0_PERITV_1                          (1 << R_XSPI_CDCTL0_PERITV_SHIFT)  /* 4(=2^2) cycles */

#define R_XSPI_CDCTL0_PERREP_SHIFT                (24)  /* Periodic transaction repeat */
#define R_XSPI_CDCTL0_PERREP_MASK                 0xf000000

/* CDCTL1 Register bit definitions */
#define R_XSPI_CDCTL1_PEREXP_SHIFT                (0)  /* Periodic transaction expected value */
#define R_XSPI_CDCTL1_PEREXP_MASK                 0xffffffff

/* CDCTL2 Register bit definitions */
#define R_XSPI_CDCTL2_PERMSK_SHIFT                (0)  /* Periodic transaction masked value */
#define R_XSPI_CDCTL2_PERMSK_MASK                 0xffffffff

/* LPCTL0 Register bit definitions */
#define R_XSPI_LPCTL0_PATREQ                      (1 << 0)  /* Pattern request */

#define R_XSPI_LPCTL0_RESERVED_SHIFT              (29)  /* These bits are read as 00. The write value should be 00. */
#define R_XSPI_LPCTL0_RESERVED_MASK               0x60000000

#define R_XSPI_LPCTL0_CSSEL                       (1 << 3)  /* Chip select */

#define R_XSPI_LPCTL0_XDPIN_SHIFT                 (4)  /* XiP Disable pattern pin */
#define R_XSPI_LPCTL0_XDPIN_MASK                  0x30
#  define R_XSPI_LPCTL0_XDPIN_0                           (0 << R_XSPI_LPCTL0_XDPIN_SHIFT)  /* 1pin */
#  define R_XSPI_LPCTL0_XDPIN_1                           (1 << R_XSPI_LPCTL0_XDPIN_SHIFT)  /* 2pin */

#define R_XSPI_LPCTL0_XD1LEN_SHIFT                (16)  /* XiP Disable pattern 1st phase length */
#define R_XSPI_LPCTL0_XD1LEN_MASK                 0x1f0000
#  define R_XSPI_LPCTL0_XD1LEN_0                          (0 << R_XSPI_LPCTL0_XD1LEN_SHIFT)  /* 0 cycle */

#define R_XSPI_LPCTL0_XD1VAL                      (1 << 23)  /* XiP Disable pattern 1st phase value */

#define R_XSPI_LPCTL0_XD2LEN_SHIFT                (24)  /* XiP Disable pattern 2nd phase length */
#define R_XSPI_LPCTL0_XD2LEN_MASK                 0x1f000000
#  define R_XSPI_LPCTL0_XD2LEN_0                          (0 << R_XSPI_LPCTL0_XD2LEN_SHIFT)  /* 0 cycle */

#define R_XSPI_LPCTL0_XD2VAL                      (1 << 31)  /* XiP Disable pattern 2nd phase value */

/* LPCTL1 Register bit definitions */
#define R_XSPI_LPCTL1_PATREQ_SHIFT                (0)  /* Pattern request */
#define R_XSPI_LPCTL1_PATREQ_MASK                 0x3
#  define R_XSPI_LPCTL1_PATREQ_00                         (0 << R_XSPI_LPCTL1_PATREQ_SHIFT)  /* No request */
#  define R_XSPI_LPCTL1_PATREQ_01                         (1 << R_XSPI_LPCTL1_PATREQ_SHIFT)  /* Request Reset pattern */
#  define R_XSPI_LPCTL1_PATREQ_10                         (2 << R_XSPI_LPCTL1_PATREQ_SHIFT)  /* Request CS only pattern */

#define R_XSPI_LPCTL1_RESERVED_SHIFT              (16)  /* These bits are read as 0000000000000000. The write value should be 0000000000000000. */
#define R_XSPI_LPCTL1_RESERVED_MASK               0xffff0000

#define R_XSPI_LPCTL1_CSSEL                       (1 << 3)  /* Chip select */

#define R_XSPI_LPCTL1_RSTREP_SHIFT                (4)  /* Reset pattern repeat */
#define R_XSPI_LPCTL1_RSTREP_MASK                 0x30
#  define R_XSPI_LPCTL1_RSTREP_0                          (0 << R_XSPI_LPCTL1_RSTREP_SHIFT)  /* 4 times (Specified on Reset Signaling Protocol) */
#  define R_XSPI_LPCTL1_RSTREP_1                          (1 << R_XSPI_LPCTL1_RSTREP_SHIFT)  /* 5 times */

#define R_XSPI_LPCTL1_RSTWID_SHIFT                (8)  /* Reset pattern width */
#define R_XSPI_LPCTL1_RSTWID_MASK                 0x700
#  define R_XSPI_LPCTL1_RSTWID_0                          (0 << R_XSPI_LPCTL1_RSTWID_SHIFT)  /* 2(=2^1) cycles */
#  define R_XSPI_LPCTL1_RSTWID_1                          (1 << R_XSPI_LPCTL1_RSTWID_SHIFT)  /* 4(=2^2) cycles */

#define R_XSPI_LPCTL1_RSTSU_SHIFT                 (12)  /* Reset pattern data output setup time */
#define R_XSPI_LPCTL1_RSTSU_MASK                  0x7000
#  define R_XSPI_LPCTL1_RSTSU_0                           (0 << R_XSPI_LPCTL1_RSTSU_SHIFT)  /* 1 cycle */

/* LIOCTL Register bit definitions */
#define R_XSPI_LIOCTL_WPCS_S                      (1 << 0)  /* WP drive for slave %s */

#define R_XSPI_LIOCTL_RESERVED_SHIFT              (18)  /* These bits are read as 00000000000000. The write value should be 00000000000000. */
#define R_XSPI_LIOCTL_RESERVED_MASK               0xfffc0000

#define R_XSPI_LIOCTL_RSTCS_S                     (1 << 16)  /* Reset drive for slave %s */

#define R_XSPI_LIOCTL_WPCS0                       (1 << 0)  /* WP drive for slave 0 */

#define R_XSPI_LIOCTL_WPCS1                       (1 << 1)  /* WP drive for slave 1 */

#define R_XSPI_LIOCTL_RSTCS0                      (1 << 16)  /* Reset drive for slave 0 */

#define R_XSPI_LIOCTL_RSTCS1                      (1 << 17)  /* Reset drive for slave 1 */

/* VERSTT Register bit definitions */
#define R_XSPI_VERSTT_VER_SHIFT                   (0)  /* Version */
#define R_XSPI_VERSTT_VER_MASK                    0xffffffff

/* COMSTT Register bit definitions */
#define R_XSPI_COMSTT_MEMACCCH_S                  (1 << 0)  /* Memory access ongoing from ch%s */

#define R_XSPI_COMSTT_RESERVED_SHIFT              (23)  /* These bits are read as 000000000. */
#define R_XSPI_COMSTT_RESERVED_MASK               0xff800000

#define R_XSPI_COMSTT_PBUFNECH_S                  (1 << 4)  /* Prefetch Buffer Not Empty for ch%s */

#define R_XSPI_COMSTT_WRBUFNECH_S                 (1 << 6)  /* Write Buffer Not Empty for ch%s */

#define R_XSPI_COMSTT_ECSCS_S                     (1 << 16)  /* ECS monitor for slave%s */

#define R_XSPI_COMSTT_INTCS_S                     (1 << 17)  /* INT monitor for slave%s */

#define R_XSPI_COMSTT_RSTOCS_S                    (1 << 18)  /* RSTO monitor for slave%s */

#define R_XSPI_COMSTT_MEMACCCH0                   (1 << 0)  /* Memory access ongoing from ch0 */

#define R_XSPI_COMSTT_MEMACCCH1                   (1 << 1)  /* Memory access ongoing from ch1 */

#define R_XSPI_COMSTT_PBUFNECH0                   (1 << 4)  /* Prefetch Buffer Not Empty for ch0 */

#define R_XSPI_COMSTT_PBUFNECH1                   (1 << 5)  /* Prefetch Buffer Not Empty for ch1 */

#define R_XSPI_COMSTT_WRBUFNECH0                  (1 << 6)  /* Write Buffer Not Empty for ch0 */

#define R_XSPI_COMSTT_WRBUFNECH1                  (1 << 7)  /* Write Buffer Not Empty for ch1 */

#define R_XSPI_COMSTT_ECSCS0                      (1 << 16)  /* ECS monitor for slave0 */

#define R_XSPI_COMSTT_INTCS0                      (1 << 17)  /* INT monitor for slave0 */

#define R_XSPI_COMSTT_RSTOCS0                     (1 << 18)  /* RSTO monitor for slave0 */

#define R_XSPI_COMSTT_ECSCS1                      (1 << 20)  /* ECS monitor for slave1 */

#define R_XSPI_COMSTT_INTCS1                      (1 << 21)  /* INT monitor for slave1 */

#define R_XSPI_COMSTT_RSTOCS1                     (1 << 22)  /* RSTO monitor for slave1 */

/* CASTTCS Register bit definitions */
#define R_XSPI_CASTTCS_CASUC_SHIFT                (0)  /* Calibration Success */
#define R_XSPI_CASTTCS_CASUC_MASK                 0xffffffff

/* INTS Register bit definitions */
#define R_XSPI_INTS_CMDCMP                        (1 << 0)  /* Command Completed */

#define R_XSPI_INTS_PATCMP                        (1 << 1)  /* Pattern Completed */

#define R_XSPI_INTS_INICMP                        (1 << 2)  /* Initial Sequence Completed */

#define R_XSPI_INTS_PERTO                         (1 << 3)  /* Periodic transaction timeout */

#define R_XSPI_INTS_DSTOCS_S                      (1 << 4)  /* DS timeout for slave%s */

#define R_XSPI_INTS_RESERVED_SHIFT                (22)  /* These bits are read as 000000. */
#define R_XSPI_INTS_RESERVED_MASK                 0xfc00000

#define R_XSPI_INTS_ECSCS_S                       (1 << 8)  /* ECC error detection for slave%s */

#define R_XSPI_INTS_INTCS_S                       (1 << 12)  /* Interrupt detection for slave%s */

#define R_XSPI_INTS_BRGOFCH_S                     (1 << 16)  /* Bridge Buffer overflow for CH%s */

#define R_XSPI_INTS_BRGUFCH_S                     (1 << 18)  /* Bridge Buffer underflow for CH%s */

#define R_XSPI_INTS_BUSERRCH_S                    (1 << 20)  /* AHB bus error for CH%s */

#define R_XSPI_INTS_CAFAILCS_S                    (1 << 28)  /* Calibration failed for slave%s */

#define R_XSPI_INTS_CASUCCS_S                     (1 << 30)  /* Calibration success for slave%s */

#define R_XSPI_INTS_DSTOCS0                       (1 << 4)  /* DS timeout for slave0 */

#define R_XSPI_INTS_DSTOCS1                       (1 << 5)  /* DS timeout for slave1 */

#define R_XSPI_INTS_ECSCS0                        (1 << 8)  /* ECC error detection for slave0 */

#define R_XSPI_INTS_ECSCS1                        (1 << 9)  /* ECC error detection for slave1 */

#define R_XSPI_INTS_INTCS0                        (1 << 12)  /* Interrupt detection for slave0 */

#define R_XSPI_INTS_INTCS1                        (1 << 13)  /* Interrupt detection for slave1 */

#define R_XSPI_INTS_BRGOFCH0                      (1 << 16)  /* Bridge Buffer overflow for CH0 */

#define R_XSPI_INTS_BRGOFCH1                      (1 << 17)  /* Bridge Buffer overflow for CH1 */

#define R_XSPI_INTS_BRGUFCH0                      (1 << 18)  /* Bridge Buffer underflow for CH0 */

#define R_XSPI_INTS_BRGUFCH1                      (1 << 19)  /* Bridge Buffer underflow for CH1 */

#define R_XSPI_INTS_BUSERRCH0                     (1 << 20)  /* AHB bus error for CH0 */

#define R_XSPI_INTS_BUSERRCH1                     (1 << 21)  /* AHB bus error for CH1 */

#define R_XSPI_INTS_CAFAILCS0                     (1 << 28)  /* Calibration failed for slave0 */

#define R_XSPI_INTS_CAFAILCS1                     (1 << 29)  /* Calibration failed for slave1 */

#define R_XSPI_INTS_CASUCCS0                      (1 << 30)  /* Calibration success for slave0 */

#define R_XSPI_INTS_CASUCCS1                      (1 << 31)  /* Calibration success for slave1 */

/* INTC Register bit definitions */
#define R_XSPI_INTC_CMDCMPC                       (1 << 0)  /* Command Completed interrupt clear */

#define R_XSPI_INTC_PATCMPC                       (1 << 1)  /* Pattern Completed interrupt clear */

#define R_XSPI_INTC_INICMPC                       (1 << 2)  /* Initial Sequence Completed interrupt clear */

#define R_XSPI_INTC_PERTOC                        (1 << 3)  /* Periodic transaction timeout interrupt clear */

#define R_XSPI_INTC_DSTOCS_SC                     (1 << 4)  /* DS timeout for slave%s interrupt clear */

#define R_XSPI_INTC_RESERVED_SHIFT                (22)  /* The write value should be 000000. */
#define R_XSPI_INTC_RESERVED_MASK                 0xfc00000

#define R_XSPI_INTC_ECSCS_SC                      (1 << 8)  /* ECC error detection for slave%s interrupt clear */

#define R_XSPI_INTC_INTCS_SC                      (1 << 12)  /* Interrupt detection for slave%s interrupt clear */

#define R_XSPI_INTC_BRGOFCH_SC                    (1 << 16)  /* Bridge Buffer overflow for CH%s interrupt clear */

#define R_XSPI_INTC_BRGUFCH_SC                    (1 << 18)  /* Bridge Buffer underflow for CH%s interrupt clear */

#define R_XSPI_INTC_BUSERRCH_SC                   (1 << 20)  /* AHB bus error for CH%s interrupt clear */

#define R_XSPI_INTC_CAFAILCS_SC                   (1 << 28)  /* Calibration failed for slave%s interrupt clear */

#define R_XSPI_INTC_CASUCCS_SC                    (1 << 30)  /* Calibration success for slave%s interrupt clear */

#define R_XSPI_INTC_DSTOCS0C                      (1 << 4)  /* DS timeout for slave0 interrupt clear */

#define R_XSPI_INTC_DSTOCS1C                      (1 << 5)  /* DS timeout for slave1 interrupt clear */

#define R_XSPI_INTC_ECSCS0C                       (1 << 8)  /* ECC error detection for slave0 interrupt clear */

#define R_XSPI_INTC_ECSCS1C                       (1 << 9)  /* ECC error detection for slave1 interrupt clear */

#define R_XSPI_INTC_INTCS0C                       (1 << 12)  /* Interrupt detection for slave0 interrupt clear */

#define R_XSPI_INTC_INTCS1C                       (1 << 13)  /* Interrupt detection for slave1 interrupt clear */

#define R_XSPI_INTC_BRGOFCH0C                     (1 << 16)  /* Bridge Buffer overflow for CH0 interrupt clear */

#define R_XSPI_INTC_BRGOFCH1C                     (1 << 17)  /* Bridge Buffer overflow for CH1 interrupt clear */

#define R_XSPI_INTC_BRGUFCH0C                     (1 << 18)  /* Bridge Buffer underflow for CH0 interrupt clear */

#define R_XSPI_INTC_BRGUFCH1C                     (1 << 19)  /* Bridge Buffer underflow for CH1 interrupt clear */

#define R_XSPI_INTC_BUSERRCH0C                    (1 << 20)  /* AHB bus error for CH0 interrupt clear */

#define R_XSPI_INTC_BUSERRCH1C                    (1 << 21)  /* AHB bus error for CH1 interrupt clear */

#define R_XSPI_INTC_CAFAILCS0C                    (1 << 28)  /* Calibration failed for slave0 interrupt clear */

#define R_XSPI_INTC_CAFAILCS1C                    (1 << 29)  /* Calibration failed for slave1 interrupt clear */

#define R_XSPI_INTC_CASUCCS0C                     (1 << 30)  /* Calibration success for slave0 interrupt clear */

#define R_XSPI_INTC_CASUCCS1C                     (1 << 31)  /* Calibration success for slave1 interrupt clear */

/* INTE Register bit definitions */
#define R_XSPI_INTE_CMDCMPE                       (1 << 0)  /* Command Completed interrupt enable */

#define R_XSPI_INTE_PATCMPE                       (1 << 1)  /* Pattern Completed interrupt enable */

#define R_XSPI_INTE_INICMPE                       (1 << 2)  /* Initial Sequence Completed interrupt enable */

#define R_XSPI_INTE_PERTOE                        (1 << 3)  /* Periodic transaction timeout interrupt enable */

#define R_XSPI_INTE_DSTOCS_SE                     (1 << 4)  /* DS timeout for slave%s interrupt enable */

#define R_XSPI_INTE_RESERVED_SHIFT                (22)  /* These bits are read as 000000. The write value should be 000000. */
#define R_XSPI_INTE_RESERVED_MASK                 0xfc00000

#define R_XSPI_INTE_ECSCS_SE                      (1 << 8)  /* ECC error detection for slave%s interrupt enable */

#define R_XSPI_INTE_INTCS_SE                      (1 << 12)  /* Interrupt detection for slave%s interrupt enable */

#define R_XSPI_INTE_BRGOFCH_SE                    (1 << 16)  /* Bridge Buffer overflow for CH%s interrupt enable */

#define R_XSPI_INTE_BRGUFCH_SE                    (1 << 18)  /* Bridge Buffer underflow for CH%s interrupt enable */

#define R_XSPI_INTE_BUSERRCH_SE                   (1 << 20)  /* AHB bus error for CH%s interrupt enable */

#define R_XSPI_INTE_CAFAILCS_SE                   (1 << 28)  /* Calibration failed for slave%s interrupt enable */

#define R_XSPI_INTE_CASUCCS_SE                    (1 << 30)  /* Calibration success for slave%s interrupt enable */

#define R_XSPI_INTE_DSTOCS0E                      (1 << 4)  /* DS timeout for slave0 interrupt enable */

#define R_XSPI_INTE_DSTOCS1E                      (1 << 5)  /* DS timeout for slave1 interrupt enable */

#define R_XSPI_INTE_ECSCS0E                       (1 << 8)  /* ECC error detection for slave0 interrupt enable */

#define R_XSPI_INTE_ECSCS1E                       (1 << 9)  /* ECC error detection for slave1 interrupt enable */

#define R_XSPI_INTE_INTCS0E                       (1 << 12)  /* Interrupt detection for slave0 interrupt enable */

#define R_XSPI_INTE_INTCS1E                       (1 << 13)  /* Interrupt detection for slave1 interrupt enable */

#define R_XSPI_INTE_BRGOFCH0E                     (1 << 16)  /* Bridge Buffer overflow for CH0 interrupt enable */

#define R_XSPI_INTE_BRGOFCH1E                     (1 << 17)  /* Bridge Buffer overflow for CH1 interrupt enable */

#define R_XSPI_INTE_BRGUFCH0E                     (1 << 18)  /* Bridge Buffer underflow for CH0 interrupt enable */

#define R_XSPI_INTE_BRGUFCH1E                     (1 << 19)  /* Bridge Buffer underflow for CH1 interrupt enable */

#define R_XSPI_INTE_BUSERRCH0E                    (1 << 20)  /* AHB bus error for CH0 interrupt enable */

#define R_XSPI_INTE_BUSERRCH1E                    (1 << 21)  /* AHB bus error for CH1 interrupt enable */

#define R_XSPI_INTE_CAFAILCS0E                    (1 << 28)  /* Calibration failed for slave0 interrupt enable */

#define R_XSPI_INTE_CAFAILCS1E                    (1 << 29)  /* Calibration failed for slave1 interrupt enable */

#define R_XSPI_INTE_CASUCCS0E                     (1 << 30)  /* Calibration success for slave0 interrupt enable */

#define R_XSPI_INTE_CASUCCS1E                     (1 << 31)  /* Calibration success for slave1 interrupt enable */


/* Maximum number of channels */

#define XSPI_MAX_CHANNELS    4

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_XSPI_H */
