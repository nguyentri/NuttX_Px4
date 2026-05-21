/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_ospi_b.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_OSPI_B_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_OSPI_B_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* OSPI_B Base Address */
#ifndef R_OSPI_B_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_OSPI_B_BASE           0x40268000
#else
#define R_OSPI_B_BASE           0x50268000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_OSPI_B_CH_STRIDE    0x00000400
#define R_OSPI_B_CH_BASE(ch)   (R_OSPI_B_BASE + ((uint32_t)(ch) * R_OSPI_B_CH_STRIDE))

/* OSPI_B Register Offsets */

#define R_OSPI_B_WRAPCFG_OFFSET                   0x00000000  /* OSPI Wrapper Configuration Register */
#define R_OSPI_B_COMCFG_OFFSET                    0x00000004  /* OSPI Common Configuration Register */
/* BMCFGCH%s Registers (0-1) */
#define R_OSPI_B_BMCFGCH_OFFSET(m)                (0x00000008 + ((m) * 0x00000004))  /* OSPI Bridge Map Configuration Register Chn (n = 0, 1) */
/* CMCFG0CS%s Registers (0-1) */
#define R_OSPI_B_CMCFG0CS_OFFSET(m)               (0x00000010 + ((m) * 0x00000010))  /* OSPI Command Map Configuration Register 0 CSn */
/* CMCFG1CS%s Registers (0-1) */
#define R_OSPI_B_CMCFG1CS_OFFSET(m)               (0x00000014 + ((m) * 0x00000010))  /* OSPI Command Map Configuration Register 1 CSn */
/* CMCFG2CS%s Registers (0-1) */
#define R_OSPI_B_CMCFG2CS_OFFSET(m)               (0x00000018 + ((m) * 0x00000010))  /* OSPI Command Map Configuration Register 2 CSn */
/* LIOCFGCS%s Registers (0-1) */
#define R_OSPI_B_LIOCFGCS_OFFSET(m)               (0x00000050 + ((m) * 0x00000004))  /* OSPI Link I/O Configuration Register CSn */
#define R_OSPI_B_BMCTL0_OFFSET                    0x00000060  /* OSPI Bridge Map Control Register 0 */
#define R_OSPI_B_BMCTL1_OFFSET                    0x00000064  /* OSPI Bridge Map Control Register 1 */
/* CMCTLCH%s Registers (0-1) */
#define R_OSPI_B_CMCTLCH_OFFSET(m)                (0x00000068 + ((m) * 0x00000004))  /* OSPI Command Map Control Register CHn (n = 0, 1) */
#define R_OSPI_B_CDCTL0_OFFSET                    0x00000070  /* OSPI Command Manual Control Register 0 */
#define R_OSPI_B_CDCTL1_OFFSET                    0x00000074  /* OSPI Command Manual Control Register 1 */
#define R_OSPI_B_CDCTL2_OFFSET                    0x00000078  /* OSPI Command Manual Control Register 2 */
/* CDTBUF%s Registers (0-3) */
#define R_OSPI_B_CDTBUF_OFFSET(m)                 (0x00000080 + ((m) * 0x00000010))  /* OSPI Command Manual Type Buf %s */
/* CDABUF%s Registers (0-3) */
#define R_OSPI_B_CDABUF_OFFSET(m)                 (0x00000084 + ((m) * 0x00000010))  /* OSPI Command Manual Address Buf %s */
/* CDD0BUF%s Registers (0-3) */
#define R_OSPI_B_CDD0BUF_OFFSET(m)                (0x00000088 + ((m) * 0x00000010))  /* OSPI Command Manual Data 0 Buf %s */
/* CDD1BUF%s Registers (0-3) */
#define R_OSPI_B_CDD1BUF_OFFSET(m)                (0x0000008c + ((m) * 0x00000010))  /* OSPI Command Manual Data 1 Buf %s */
#define R_OSPI_B_LPCTL0_OFFSET                    0x00000100  /* OSPI Link Pattern Control Register 0 */
#define R_OSPI_B_LPCTL1_OFFSET                    0x00000104  /* OSPI Link Pattern Control Register 1 */
#define R_OSPI_B_LIOCTL_OFFSET                    0x00000108  /* OSPI Link I/O Control Register */
/* CCCTL0CS%s Registers (0-1) */
#define R_OSPI_B_CCCTL0CS_OFFSET(m)               (0x00000130 + ((m) * 0x00000020))  /* OSPI Command Calibration Control Register 0 CSn */
/* CCCTL1CS%s Registers (0-1) */
#define R_OSPI_B_CCCTL1CS_OFFSET(m)               (0x00000134 + ((m) * 0x00000020))  /* OSPI Command Calibration Control Register 1 CSn */
/* CCCTL2CS%s Registers (0-1) */
#define R_OSPI_B_CCCTL2CS_OFFSET(m)               (0x00000138 + ((m) * 0x00000020))  /* OSPI Command Calibration Control Register 2 CSn */
/* CCCTL3CS%s Registers (0-1) */
#define R_OSPI_B_CCCTL3CS_OFFSET(m)               (0x0000013c + ((m) * 0x00000020))  /* OSPI Command Calibration Control Register 3 CSn */
/* CCCTL4CS%s Registers (0-1) */
#define R_OSPI_B_CCCTL4CS_OFFSET(m)               (0x00000140 + ((m) * 0x00000020))  /* OSPI Command Calibration Control Register 4 CSn */
/* CCCTL5CS%s Registers (0-1) */
#define R_OSPI_B_CCCTL5CS_OFFSET(m)               (0x00000144 + ((m) * 0x00000020))  /* OSPI Command Calibration Control Register 5 CSn */
/* CCCTL6CS%s Registers (0-1) */
#define R_OSPI_B_CCCTL6CS_OFFSET(m)               (0x00000148 + ((m) * 0x00000020))  /* OSPI Command Calibration Control Register 6 CSn */
/* CCCTL7CS%s Registers (0-1) */
#define R_OSPI_B_CCCTL7CS_OFFSET(m)               (0x0000014c + ((m) * 0x00000020))  /* OSPI Command Calibration Control Register 7 CSn */
#define R_OSPI_B_COMSTT_OFFSET                    0x00000184  /* OSPI Common Status Register */
/* CASTTCS%s Registers (0-1) */
#define R_OSPI_B_CASTTCS_OFFSET(m)                (0x00000188 + ((m) * 0x00000004))  /* OSPI Calibration Status Register CSn */
#define R_OSPI_B_INTS_OFFSET                      0x00000190  /* OSPI Interrupt Status Register */
#define R_OSPI_B_INTC_OFFSET                      0x00000194  /* OSPI Interrupt Clear Register */
#define R_OSPI_B_INTE_OFFSET                      0x00000198  /* OSPI Interrupt Enable Register */

/* OSPI_B Register Addresses */

#define R_OSPI_B_WRAPCFG(n)                       (R_OSPI_B_CH_BASE(n) + R_OSPI_B_WRAPCFG_OFFSET)
#define R_OSPI_B_COMCFG(n)                        (R_OSPI_B_CH_BASE(n) + R_OSPI_B_COMCFG_OFFSET)
#define R_OSPI_B_BMCFGCH(n, m)                    (R_OSPI_B_CH_BASE(n) + R_OSPI_B_BMCFGCH_OFFSET(m))
#define R_OSPI_B_CMCFG0CS(n, m)                   (R_OSPI_B_CH_BASE(n) + R_OSPI_B_CMCFG0CS_OFFSET(m))
#define R_OSPI_B_CMCFG1CS(n, m)                   (R_OSPI_B_CH_BASE(n) + R_OSPI_B_CMCFG1CS_OFFSET(m))
#define R_OSPI_B_CMCFG2CS(n, m)                   (R_OSPI_B_CH_BASE(n) + R_OSPI_B_CMCFG2CS_OFFSET(m))
#define R_OSPI_B_LIOCFGCS(n, m)                   (R_OSPI_B_CH_BASE(n) + R_OSPI_B_LIOCFGCS_OFFSET(m))
#define R_OSPI_B_BMCTL0(n)                        (R_OSPI_B_CH_BASE(n) + R_OSPI_B_BMCTL0_OFFSET)
#define R_OSPI_B_BMCTL1(n)                        (R_OSPI_B_CH_BASE(n) + R_OSPI_B_BMCTL1_OFFSET)
#define R_OSPI_B_CMCTLCH(n, m)                    (R_OSPI_B_CH_BASE(n) + R_OSPI_B_CMCTLCH_OFFSET(m))
#define R_OSPI_B_CDCTL0(n)                        (R_OSPI_B_CH_BASE(n) + R_OSPI_B_CDCTL0_OFFSET)
#define R_OSPI_B_CDCTL1(n)                        (R_OSPI_B_CH_BASE(n) + R_OSPI_B_CDCTL1_OFFSET)
#define R_OSPI_B_CDCTL2(n)                        (R_OSPI_B_CH_BASE(n) + R_OSPI_B_CDCTL2_OFFSET)
#define R_OSPI_B_CDTBUF(n, m)                     (R_OSPI_B_CH_BASE(n) + R_OSPI_B_CDTBUF_OFFSET(m))
#define R_OSPI_B_CDABUF(n, m)                     (R_OSPI_B_CH_BASE(n) + R_OSPI_B_CDABUF_OFFSET(m))
#define R_OSPI_B_CDD0BUF(n, m)                    (R_OSPI_B_CH_BASE(n) + R_OSPI_B_CDD0BUF_OFFSET(m))
#define R_OSPI_B_CDD1BUF(n, m)                    (R_OSPI_B_CH_BASE(n) + R_OSPI_B_CDD1BUF_OFFSET(m))
#define R_OSPI_B_LPCTL0(n)                        (R_OSPI_B_CH_BASE(n) + R_OSPI_B_LPCTL0_OFFSET)
#define R_OSPI_B_LPCTL1(n)                        (R_OSPI_B_CH_BASE(n) + R_OSPI_B_LPCTL1_OFFSET)
#define R_OSPI_B_LIOCTL(n)                        (R_OSPI_B_CH_BASE(n) + R_OSPI_B_LIOCTL_OFFSET)
#define R_OSPI_B_CCCTL0CS(n, m)                   (R_OSPI_B_CH_BASE(n) + R_OSPI_B_CCCTL0CS_OFFSET(m))
#define R_OSPI_B_CCCTL1CS(n, m)                   (R_OSPI_B_CH_BASE(n) + R_OSPI_B_CCCTL1CS_OFFSET(m))
#define R_OSPI_B_CCCTL2CS(n, m)                   (R_OSPI_B_CH_BASE(n) + R_OSPI_B_CCCTL2CS_OFFSET(m))
#define R_OSPI_B_CCCTL3CS(n, m)                   (R_OSPI_B_CH_BASE(n) + R_OSPI_B_CCCTL3CS_OFFSET(m))
#define R_OSPI_B_CCCTL4CS(n, m)                   (R_OSPI_B_CH_BASE(n) + R_OSPI_B_CCCTL4CS_OFFSET(m))
#define R_OSPI_B_CCCTL5CS(n, m)                   (R_OSPI_B_CH_BASE(n) + R_OSPI_B_CCCTL5CS_OFFSET(m))
#define R_OSPI_B_CCCTL6CS(n, m)                   (R_OSPI_B_CH_BASE(n) + R_OSPI_B_CCCTL6CS_OFFSET(m))
#define R_OSPI_B_CCCTL7CS(n, m)                   (R_OSPI_B_CH_BASE(n) + R_OSPI_B_CCCTL7CS_OFFSET(m))
#define R_OSPI_B_COMSTT(n)                        (R_OSPI_B_CH_BASE(n) + R_OSPI_B_COMSTT_OFFSET)
#define R_OSPI_B_CASTTCS(n, m)                    (R_OSPI_B_CH_BASE(n) + R_OSPI_B_CASTTCS_OFFSET(m))
#define R_OSPI_B_INTS(n)                          (R_OSPI_B_CH_BASE(n) + R_OSPI_B_INTS_OFFSET)
#define R_OSPI_B_INTC(n)                          (R_OSPI_B_CH_BASE(n) + R_OSPI_B_INTC_OFFSET)
#define R_OSPI_B_INTE(n)                          (R_OSPI_B_CH_BASE(n) + R_OSPI_B_INTE_OFFSET)

/* Register bit definitions */
/* WRAPCFG Register bit definitions */
#define R_OSPI_B_WRAPCFG_DSSFTCS0_SHIFT           (8)  /* DS Shift for Slave 0 */
#define R_OSPI_B_WRAPCFG_DSSFTCS0_MASK            0x1f00

#define R_OSPI_B_WRAPCFG_DSSFTCS1_SHIFT           (24)  /* DS Shift for Slave 1 */
#define R_OSPI_B_WRAPCFG_DSSFTCS1_MASK            0x1f000000

/* COMCFG Register bit definitions */
#define R_OSPI_B_COMCFG_ARBMD_SHIFT               (0)  /* Channel Arbitration Mode */
#define R_OSPI_B_COMCFG_ARBMD_MASK                0x3
#  define R_OSPI_B_COMCFG_ARBMD_00                        (0 << R_OSPI_B_COMCFG_ARBMD_SHIFT)  /* Round-robin (ch0-ch1-ch0-ch1…) */
#  define R_OSPI_B_COMCFG_ARBMD_01                        (1 << R_OSPI_B_COMCFG_ARBMD_SHIFT)  /* Always ch0 win */
#  define R_OSPI_B_COMCFG_ARBMD_10                        (2 << R_OSPI_B_COMCFG_ARBMD_SHIFT)  /* Always ch1 win */
#  define R_OSPI_B_COMCFG_ARBMD_11                        (3 << R_OSPI_B_COMCFG_ARBMD_SHIFT)  /* Reserved */

#define R_OSPI_B_COMCFG_OEASTEX                   (1 << 16)  /* Output Enable Asserting Extension */

#define R_OSPI_B_COMCFG_OENEGEX                   (1 << 17)  /* Output Enable Negating Extension */

/* BMCFGCH Register bit definitions */
#define R_OSPI_B_BMCFGCH_WRMD                     (1 << 0)  /* System Bus Write Response Mode */

#define R_OSPI_B_BMCFGCH_MWRCOMB                  (1 << 7)  /* Memory Write Combination Mode */

#define R_OSPI_B_BMCFGCH_MWRSIZE_SHIFT            (8)  /* Memory Write Size */
#define R_OSPI_B_BMCFGCH_MWRSIZE_MASK             0xff00

#define R_OSPI_B_BMCFGCH_PREEN                    (1 << 16)  /* Prefetch Enable */

#define R_OSPI_B_BMCFGCH_CMBTIM_SHIFT             (24)  /* Combination Timer */
#define R_OSPI_B_BMCFGCH_CMBTIM_MASK              0xff000000

/* CMCFG0CS Register bit definitions */
#define R_OSPI_B_CMCFG0CS_FFMT_SHIFT              (0)  /* Frame Format */
#define R_OSPI_B_CMCFG0CS_FFMT_MASK               0x3
#  define R_OSPI_B_CMCFG0CS_FFMT_00                       (0 << R_OSPI_B_CMCFG0CS_FFMT_SHIFT)  /* Normal format: Command 1 byte, address ADDSIZE, data up to system bus transaction  */
#  define R_OSPI_B_CMCFG0CS_FFMT_01                       (1 << R_OSPI_B_CMCFG0CS_FFMT_SHIFT)  /* 8D-8D-8D profile 1.0 format: Command 2 bytes, address ADDSIZE, data up to system bus transaction  */
#  define R_OSPI_B_CMCFG0CS_FFMT_10                       (2 << R_OSPI_B_CMCFG0CS_FFMT_SHIFT)  /* 8D-8D-8D profile 2.0 Command Modifier format: Command & Modifier 6 bytes, data up to system bus transaction  */
#  define R_OSPI_B_CMCFG0CS_FFMT_11                       (3 << R_OSPI_B_CMCFG0CS_FFMT_SHIFT)  /* 8D-8D-8D profile 2.0 Commands with Extended Command Modifier format: Command & Modifier 6 bytes, data up to system bus transaction  */

#define R_OSPI_B_CMCFG0CS_ADDSIZE_SHIFT           (2)  /* Address Size */
#define R_OSPI_B_CMCFG0CS_ADDSIZE_MASK            0xc
#  define R_OSPI_B_CMCFG0CS_ADDSIZE_00                    (0 << R_OSPI_B_CMCFG0CS_ADDSIZE_SHIFT)  /* 1 byte (256-byte address space) */
#  define R_OSPI_B_CMCFG0CS_ADDSIZE_01                    (1 << R_OSPI_B_CMCFG0CS_ADDSIZE_SHIFT)  /* 2 bytes (64-KB address space) */
#  define R_OSPI_B_CMCFG0CS_ADDSIZE_10                    (2 << R_OSPI_B_CMCFG0CS_ADDSIZE_SHIFT)  /* 3 bytes (16-MB address space) */
#  define R_OSPI_B_CMCFG0CS_ADDSIZE_11                    (3 << R_OSPI_B_CMCFG0CS_ADDSIZE_SHIFT)  /* 4 bytes (4-GB address space) */

#define R_OSPI_B_CMCFG0CS_WPBSTMD                 (1 << 4)  /* Wrapping Burst Mode */

#define R_OSPI_B_CMCFG0CS_ARYAMD                  (1 << 5)  /* Array Address Mode */

#define R_OSPI_B_CMCFG0CS_ADDRPEN_SHIFT           (16)  /* Address Replace Enable */
#define R_OSPI_B_CMCFG0CS_ADDRPEN_MASK            0xff0000
#  define R_OSPI_B_CMCFG0CS_ADDRPEN_0                     (0 << R_OSPI_B_CMCFG0CS_ADDRPEN_SHIFT)  /* No replacement (xSPI frame address field is the same as system bus address) */
#  define R_OSPI_B_CMCFG0CS_ADDRPEN_1                     (1 << R_OSPI_B_CMCFG0CS_ADDRPEN_SHIFT)  /* Replacement */

#define R_OSPI_B_CMCFG0CS_ADDRPCD_SHIFT           (24)  /* Address Replace Code */
#define R_OSPI_B_CMCFG0CS_ADDRPCD_MASK            0xff000000

/* CMCFG1CS Register bit definitions */
#define R_OSPI_B_CMCFG1CS_RDCMD_SHIFT             (0)  /* Read Command */
#define R_OSPI_B_CMCFG1CS_RDCMD_MASK              0xffff

#define R_OSPI_B_CMCFG1CS_RDLATE_SHIFT            (16)  /* Read Latency Cycle */
#define R_OSPI_B_CMCFG1CS_RDLATE_MASK             0x1f0000

/* CMCFG2CS Register bit definitions */
#define R_OSPI_B_CMCFG2CS_WRCMD_SHIFT             (0)  /* Write Command */
#define R_OSPI_B_CMCFG2CS_WRCMD_MASK              0xffff

#define R_OSPI_B_CMCFG2CS_WRLATE_SHIFT            (16)  /* Write Latency Cycle */
#define R_OSPI_B_CMCFG2CS_WRLATE_MASK             0x1f0000

/* LIOCFGCS Register bit definitions */
#define R_OSPI_B_LIOCFGCS_PRTMD_SHIFT             (0)  /* Protocol Mode */
#define R_OSPI_B_LIOCFGCS_PRTMD_MASK              0x3ff
#  define R_OSPI_B_LIOCFGCS_PRTMD_0X000                   (0 << R_OSPI_B_LIOCFGCS_PRTMD_SHIFT)  /* 1S-1S-1S */
#  define R_OSPI_B_LIOCFGCS_PRTMD_0X3B2                   (946 << R_OSPI_B_LIOCFGCS_PRTMD_SHIFT)  /* 4S-4D-4D */
#  define R_OSPI_B_LIOCFGCS_PRTMD_0X3FF                   (1023 << R_OSPI_B_LIOCFGCS_PRTMD_SHIFT)  /* 8D-8D-8D */
#  define R_OSPI_B_LIOCFGCS_PRTMD_0X048                   (72 << R_OSPI_B_LIOCFGCS_PRTMD_SHIFT)  /* 1S-2S-2S */
#  define R_OSPI_B_LIOCFGCS_PRTMD_0X049                   (73 << R_OSPI_B_LIOCFGCS_PRTMD_SHIFT)  /* 2S-2S-2S */
#  define R_OSPI_B_LIOCFGCS_PRTMD_0X090                   (144 << R_OSPI_B_LIOCFGCS_PRTMD_SHIFT)  /* 1S-4S-4S */
#  define R_OSPI_B_LIOCFGCS_PRTMD_0X092                   (146 << R_OSPI_B_LIOCFGCS_PRTMD_SHIFT)  /* 4S-4S-4S */

#define R_OSPI_B_LIOCFGCS_LATEMD                  (1 << 10)  /* Latency Mode */

#define R_OSPI_B_LIOCFGCS_WRMSKMD                 (1 << 11)  /* Write Mask Mode */

#define R_OSPI_B_LIOCFGCS_CSMIN_SHIFT             (16)  /* CS Minimum Idle Term */
#define R_OSPI_B_LIOCFGCS_CSMIN_MASK              0xf0000

#define R_OSPI_B_LIOCFGCS_CSASTEX                 (1 << 20)  /* CS Asserting Extension */

#define R_OSPI_B_LIOCFGCS_CSNEGEX                 (1 << 21)  /* CS Negating Extension */

#define R_OSPI_B_LIOCFGCS_SDRDRV                  (1 << 22)  /* SDR Driving Timing */

#define R_OSPI_B_LIOCFGCS_SDRSMPMD                (1 << 23)  /* SDR Sampling Mode */

#define R_OSPI_B_LIOCFGCS_SDRSMPSFT_SHIFT         (24)  /* SDR Sampling window shift */
#define R_OSPI_B_LIOCFGCS_SDRSMPSFT_MASK          0xf000000

#define R_OSPI_B_LIOCFGCS_DDRSMPEX_SHIFT          (28)  /* DDR Sampling Window Extend */
#define R_OSPI_B_LIOCFGCS_DDRSMPEX_MASK           0xf0000000

/* BMCTL0 Register bit definitions */
#define R_OSPI_B_BMCTL0_CH0CS0ACC_SHIFT           (0)  /* System bus ch0 to slave 0 memory area access enable */
#define R_OSPI_B_BMCTL0_CH0CS0ACC_MASK            0x3
#  define R_OSPI_B_BMCTL0_CH0CS0ACC_00                    (0 << R_OSPI_B_BMCTL0_CH0CS0ACC_SHIFT)  /* Read/write disable */
#  define R_OSPI_B_BMCTL0_CH0CS0ACC_01                    (1 << R_OSPI_B_BMCTL0_CH0CS0ACC_SHIFT)  /* Read enable, write disable */
#  define R_OSPI_B_BMCTL0_CH0CS0ACC_10                    (2 << R_OSPI_B_BMCTL0_CH0CS0ACC_SHIFT)  /* Read disable, write enable */
#  define R_OSPI_B_BMCTL0_CH0CS0ACC_11                    (3 << R_OSPI_B_BMCTL0_CH0CS0ACC_SHIFT)  /* Read/write enable */

#define R_OSPI_B_BMCTL0_CH0CS1ACC_SHIFT           (2)  /* System bus ch0 to slave 1 memory area access enable */
#define R_OSPI_B_BMCTL0_CH0CS1ACC_MASK            0xc
#  define R_OSPI_B_BMCTL0_CH0CS1ACC_00                    (0 << R_OSPI_B_BMCTL0_CH0CS1ACC_SHIFT)  /* Read/write disable */
#  define R_OSPI_B_BMCTL0_CH0CS1ACC_01                    (1 << R_OSPI_B_BMCTL0_CH0CS1ACC_SHIFT)  /* Read enable, write disable */
#  define R_OSPI_B_BMCTL0_CH0CS1ACC_10                    (2 << R_OSPI_B_BMCTL0_CH0CS1ACC_SHIFT)  /* Read disable, write enable */
#  define R_OSPI_B_BMCTL0_CH0CS1ACC_11                    (3 << R_OSPI_B_BMCTL0_CH0CS1ACC_SHIFT)  /* Read/write enable */

#define R_OSPI_B_BMCTL0_CH1CS0ACC_SHIFT           (4)  /* System bus ch1 to slave 0 memory area access enable */
#define R_OSPI_B_BMCTL0_CH1CS0ACC_MASK            0x30
#  define R_OSPI_B_BMCTL0_CH1CS0ACC_00                    (0 << R_OSPI_B_BMCTL0_CH1CS0ACC_SHIFT)  /* Read/write disable */
#  define R_OSPI_B_BMCTL0_CH1CS0ACC_01                    (1 << R_OSPI_B_BMCTL0_CH1CS0ACC_SHIFT)  /* Read enable, write disable */
#  define R_OSPI_B_BMCTL0_CH1CS0ACC_10                    (2 << R_OSPI_B_BMCTL0_CH1CS0ACC_SHIFT)  /* Read disable, write enable */
#  define R_OSPI_B_BMCTL0_CH1CS0ACC_11                    (3 << R_OSPI_B_BMCTL0_CH1CS0ACC_SHIFT)  /* Read/write enable */

#define R_OSPI_B_BMCTL0_CH1CS1ACC_SHIFT           (6)  /* System bus ch1 to slave 1 memory area access enable */
#define R_OSPI_B_BMCTL0_CH1CS1ACC_MASK            0xc0
#  define R_OSPI_B_BMCTL0_CH1CS1ACC_00                    (0 << R_OSPI_B_BMCTL0_CH1CS1ACC_SHIFT)  /* Read/write disable */
#  define R_OSPI_B_BMCTL0_CH1CS1ACC_01                    (1 << R_OSPI_B_BMCTL0_CH1CS1ACC_SHIFT)  /* Read enable, write disable */
#  define R_OSPI_B_BMCTL0_CH1CS1ACC_10                    (2 << R_OSPI_B_BMCTL0_CH1CS1ACC_SHIFT)  /* Read disable, write enable */
#  define R_OSPI_B_BMCTL0_CH1CS1ACC_11                    (3 << R_OSPI_B_BMCTL0_CH1CS1ACC_SHIFT)  /* Read/write enable */

/* BMCTL1 Register bit definitions */
#define R_OSPI_B_BMCTL1_MWRPUSHCH0                (1 << 8)  /* Memory Write Data Push for ch0 */

#define R_OSPI_B_BMCTL1_MWRPUSHCH1                (1 << 9)  /* Memory Write Data Push for ch1 */

#define R_OSPI_B_BMCTL1_PBUFCLRCH0                (1 << 10)  /* Prefetch Buffer Clear for ch0 */

#define R_OSPI_B_BMCTL1_PBUFCLRCH1                (1 << 11)  /* Prefetch Buffer Clear for ch1 */

/* CMCTLCH Register bit definitions */
#define R_OSPI_B_CMCTLCH_XIPENCODE_SHIFT          (0)  /* XiP Mode Enter Code */
#define R_OSPI_B_CMCTLCH_XIPENCODE_MASK           0xff

#define R_OSPI_B_CMCTLCH_XIPEXCODE_SHIFT          (8)  /* XiP Mode Exit Code */
#define R_OSPI_B_CMCTLCH_XIPEXCODE_MASK           0xff00

#define R_OSPI_B_CMCTLCH_XIPEN                    (1 << 16)  /* XiP Mode Enable */

/* CDCTL0 Register bit definitions */
#define R_OSPI_B_CDCTL0_TRREQ                     (1 << 0)  /* Transaction Request */

#define R_OSPI_B_CDCTL0_PERMD                     (1 << 1)  /* Periodic Mode */

#define R_OSPI_B_CDCTL0_CSSEL                     (1 << 3)  /* Chip Select */

#define R_OSPI_B_CDCTL0_TRNUM_SHIFT               (4)  /* Transaction Number */
#define R_OSPI_B_CDCTL0_TRNUM_MASK                0x30
#  define R_OSPI_B_CDCTL0_TRNUM_00                        (0 << R_OSPI_B_CDCTL0_TRNUM_SHIFT)  /* Issue 1 command (using command buffer 0) */
#  define R_OSPI_B_CDCTL0_TRNUM_01                        (1 << R_OSPI_B_CDCTL0_TRNUM_SHIFT)  /* Issue 2 commands (using command buffer 0-1) */
#  define R_OSPI_B_CDCTL0_TRNUM_10                        (2 << R_OSPI_B_CDCTL0_TRNUM_SHIFT)  /* Issue 3 commands (using command buffer 0-2) */
#  define R_OSPI_B_CDCTL0_TRNUM_11                        (3 << R_OSPI_B_CDCTL0_TRNUM_SHIFT)  /* Issue 4 commands (using command buffer 0-3) */

#define R_OSPI_B_CDCTL0_PERITV_SHIFT              (16)  /* Periodic Transaction Interval */
#define R_OSPI_B_CDCTL0_PERITV_MASK               0x1f0000

#define R_OSPI_B_CDCTL0_PERREP_SHIFT              (24)  /* Periodic Transaction Repeat */
#define R_OSPI_B_CDCTL0_PERREP_MASK               0xf000000

/* CDCTL1 Register bit definitions */
#define R_OSPI_B_CDCTL1_PEREXP_SHIFT              (0)  /* Periodic Transaction Expected Value */
#define R_OSPI_B_CDCTL1_PEREXP_MASK               0xffffffff

/* CDCTL2 Register bit definitions */
#define R_OSPI_B_CDCTL2_PERMSK_SHIFT              (0)  /* Periodic Transaction Masked Value */
#define R_OSPI_B_CDCTL2_PERMSK_MASK               0xffffffff

/* CDTBUF Register bit definitions */
#define R_OSPI_B_CDTBUF_CMDSIZE_SHIFT             (0)  /* Command Size */
#define R_OSPI_B_CDTBUF_CMDSIZE_MASK              0x3
#  define R_OSPI_B_CDTBUF_CMDSIZE_00                      (0 << R_OSPI_B_CDTBUF_CMDSIZE_SHIFT)  /* 0 bytes (no command phase) */
#  define R_OSPI_B_CDTBUF_CMDSIZE_01                      (1 << R_OSPI_B_CDTBUF_CMDSIZE_SHIFT)  /* 1 byte */
#  define R_OSPI_B_CDTBUF_CMDSIZE_10                      (2 << R_OSPI_B_CDTBUF_CMDSIZE_SHIFT)  /* 2 bytes */

#define R_OSPI_B_CDTBUF_ADDSIZE_SHIFT             (2)  /* Address Size */
#define R_OSPI_B_CDTBUF_ADDSIZE_MASK              0x1c
#  define R_OSPI_B_CDTBUF_ADDSIZE_000                     (0 << R_OSPI_B_CDTBUF_ADDSIZE_SHIFT)  /* 0 bytes (no address phase)  */
#  define R_OSPI_B_CDTBUF_ADDSIZE_001                     (1 << R_OSPI_B_CDTBUF_ADDSIZE_SHIFT)  /* 1 byte  */
#  define R_OSPI_B_CDTBUF_ADDSIZE_010                     (2 << R_OSPI_B_CDTBUF_ADDSIZE_SHIFT)  /* 2 bytes  */
#  define R_OSPI_B_CDTBUF_ADDSIZE_011                     (3 << R_OSPI_B_CDTBUF_ADDSIZE_SHIFT)  /* 3 bytes  */
#  define R_OSPI_B_CDTBUF_ADDSIZE_100                     (4 << R_OSPI_B_CDTBUF_ADDSIZE_SHIFT)  /* 4 bytes  */

#define R_OSPI_B_CDTBUF_DATASIZE_SHIFT            (5)  /* Write/Read Data Size */
#define R_OSPI_B_CDTBUF_DATASIZE_MASK             0x1e0

#define R_OSPI_B_CDTBUF_LATE_SHIFT                (9)  /* Latency Cycle */
#define R_OSPI_B_CDTBUF_LATE_MASK                 0x3e00

#define R_OSPI_B_CDTBUF_TRTYPE                    (1 << 15)  /* Transaction Type */

#define R_OSPI_B_CDTBUF_CMD_SHIFT                 (16)  /* Command (1-2 bytes) */
#define R_OSPI_B_CDTBUF_CMD_MASK                  0xffff0000

/* CDABUF Register bit definitions */
#define R_OSPI_B_CDABUF_ADD_SHIFT                 (0)  /* Address */
#define R_OSPI_B_CDABUF_ADD_MASK                  0xffffffff

/* CDD0BUF Register bit definitions */
#define R_OSPI_B_CDD0BUF_DATA_SHIFT               (0)  /* Write/Read Data */
#define R_OSPI_B_CDD0BUF_DATA_MASK                0xffffffff

/* CDD1BUF Register bit definitions */
#define R_OSPI_B_CDD1BUF_DATA_SHIFT               (0)  /* Write/Read Data */
#define R_OSPI_B_CDD1BUF_DATA_MASK                0xffffffff

/* LPCTL0 Register bit definitions */
#define R_OSPI_B_LPCTL0_PATREQ                    (1 << 0)  /* Pattern Request */

#define R_OSPI_B_LPCTL0_CSSEL                     (1 << 3)  /* Chip Select */

#define R_OSPI_B_LPCTL0_XDPIN_SHIFT               (4)  /* XiP Disable Pattern Pin */
#define R_OSPI_B_LPCTL0_XDPIN_MASK                0x30
#  define R_OSPI_B_LPCTL0_XDPIN_00                        (0 << R_OSPI_B_LPCTL0_XDPIN_SHIFT)  /* 1 pin */
#  define R_OSPI_B_LPCTL0_XDPIN_01                        (1 << R_OSPI_B_LPCTL0_XDPIN_SHIFT)  /* 2 pins */
#  define R_OSPI_B_LPCTL0_XDPIN_10                        (2 << R_OSPI_B_LPCTL0_XDPIN_SHIFT)  /* 4 pins */
#  define R_OSPI_B_LPCTL0_XDPIN_11                        (3 << R_OSPI_B_LPCTL0_XDPIN_SHIFT)  /* 8 pins */

#define R_OSPI_B_LPCTL0_XD1LEN_SHIFT              (16)  /* XiP Disable Pattern 1st Phase Length */
#define R_OSPI_B_LPCTL0_XD1LEN_MASK               0x1f0000

#define R_OSPI_B_LPCTL0_XD1VAL                    (1 << 23)  /* XiP Disable Pattern 1st Phase Value */

#define R_OSPI_B_LPCTL0_XD2LEN_SHIFT              (24)  /* XiP Disable Pattern 2nd Phase Length */
#define R_OSPI_B_LPCTL0_XD2LEN_MASK               0x1f000000

#define R_OSPI_B_LPCTL0_XD2VAL                    (1 << 31)  /* XiP Disable Pattern 2nd Phase Value */

/* LPCTL1 Register bit definitions */
#define R_OSPI_B_LPCTL1_PATREQ_SHIFT              (0)  /* Pattern Request */
#define R_OSPI_B_LPCTL1_PATREQ_MASK               0x3
#  define R_OSPI_B_LPCTL1_PATREQ_00                       (0 << R_OSPI_B_LPCTL1_PATREQ_SHIFT)  /* No request  */
#  define R_OSPI_B_LPCTL1_PATREQ_01                       (1 << R_OSPI_B_LPCTL1_PATREQ_SHIFT)  /* Request Reset pattern */
#  define R_OSPI_B_LPCTL1_PATREQ_10                       (2 << R_OSPI_B_LPCTL1_PATREQ_SHIFT)  /* Request CS-only pattern */
#  define R_OSPI_B_LPCTL1_PATREQ_11                       (3 << R_OSPI_B_LPCTL1_PATREQ_SHIFT)  /* Setting prohibited */

#define R_OSPI_B_LPCTL1_CSSEL                     (1 << 3)  /* Chip select */

#define R_OSPI_B_LPCTL1_RSTREP_SHIFT              (4)  /* Reset Pattern Repeat */
#define R_OSPI_B_LPCTL1_RSTREP_MASK               0x30
#  define R_OSPI_B_LPCTL1_RSTREP_00                       (0 << R_OSPI_B_LPCTL1_RSTREP_SHIFT)  /* 4 times (specified on Reset Signaling Protocol) */
#  define R_OSPI_B_LPCTL1_RSTREP_01                       (1 << R_OSPI_B_LPCTL1_RSTREP_SHIFT)  /* 5 times */
#  define R_OSPI_B_LPCTL1_RSTREP_10                       (2 << R_OSPI_B_LPCTL1_RSTREP_SHIFT)  /* 6 times */
#  define R_OSPI_B_LPCTL1_RSTREP_11                       (3 << R_OSPI_B_LPCTL1_RSTREP_SHIFT)  /* 7 times */

#define R_OSPI_B_LPCTL1_RSTWID_SHIFT              (8)  /* Reset Pattern Width */
#define R_OSPI_B_LPCTL1_RSTWID_MASK               0x700

#define R_OSPI_B_LPCTL1_RSTSU_SHIFT               (12)  /* Reset Pattern Data Output Setup Time */
#define R_OSPI_B_LPCTL1_RSTSU_MASK                0x7000

/* LIOCTL Register bit definitions */
#define R_OSPI_B_LIOCTL_WPCS1                     (1 << 1)  /* WP Drive for Slave 1 */

#define R_OSPI_B_LIOCTL_RSTCS0                    (1 << 16)  /* Reset Drive */

/* CCCTL0CS Register bit definitions */
#define R_OSPI_B_CCCTL0CS_CAEN                    (1 << 0)  /* Automatic Calibration Enable */

#define R_OSPI_B_CCCTL0CS_CANOWR                  (1 << 1)  /* Calibration No Write Mode */

#define R_OSPI_B_CCCTL0CS_CAITV_SHIFT             (8)  /* Calibration Interval */
#define R_OSPI_B_CCCTL0CS_CAITV_MASK              0x1f00

#define R_OSPI_B_CCCTL0CS_CASFTSTA_SHIFT          (16)  /* Calibration DS Shift Start Value */
#define R_OSPI_B_CCCTL0CS_CASFTSTA_MASK           0x1f0000

#define R_OSPI_B_CCCTL0CS_CASFTEND_SHIFT          (24)  /* Calibration DS Shift End Value */
#define R_OSPI_B_CCCTL0CS_CASFTEND_MASK           0x1f000000

/* CCCTL1CS Register bit definitions */
#define R_OSPI_B_CCCTL1CS_CACMDSIZE_SHIFT         (0)  /* Command Size */
#define R_OSPI_B_CCCTL1CS_CACMDSIZE_MASK          0x3
#  define R_OSPI_B_CCCTL1CS_CACMDSIZE_00                  (0 << R_OSPI_B_CCCTL1CS_CACMDSIZE_SHIFT)  /* 0 bytes (no command phase)  */
#  define R_OSPI_B_CCCTL1CS_CACMDSIZE_01                  (1 << R_OSPI_B_CCCTL1CS_CACMDSIZE_SHIFT)  /* 1 byte */
#  define R_OSPI_B_CCCTL1CS_CACMDSIZE_10                  (2 << R_OSPI_B_CCCTL1CS_CACMDSIZE_SHIFT)  /* 2 bytes */
#  define R_OSPI_B_CCCTL1CS_CACMDSIZE_11                  (3 << R_OSPI_B_CCCTL1CS_CACMDSIZE_SHIFT)  /* Setting prohibited */

#define R_OSPI_B_CCCTL1CS_CAADDSIZE_SHIFT         (2)  /* Address Size */
#define R_OSPI_B_CCCTL1CS_CAADDSIZE_MASK          0x1c
#  define R_OSPI_B_CCCTL1CS_CAADDSIZE_000                 (0 << R_OSPI_B_CCCTL1CS_CAADDSIZE_SHIFT)  /* 0 bytes (no address phase)  */
#  define R_OSPI_B_CCCTL1CS_CAADDSIZE_001                 (1 << R_OSPI_B_CCCTL1CS_CAADDSIZE_SHIFT)  /* 1 byte */
#  define R_OSPI_B_CCCTL1CS_CAADDSIZE_010                 (2 << R_OSPI_B_CCCTL1CS_CAADDSIZE_SHIFT)  /* 2 bytes */
#  define R_OSPI_B_CCCTL1CS_CAADDSIZE_011                 (3 << R_OSPI_B_CCCTL1CS_CAADDSIZE_SHIFT)  /* 3 bytes */
#  define R_OSPI_B_CCCTL1CS_CAADDSIZE_100                 (4 << R_OSPI_B_CCCTL1CS_CAADDSIZE_SHIFT)  /* 4 bytes */

#define R_OSPI_B_CCCTL1CS_CADATASIZE_SHIFT        (5)  /* Write/Read Data Size */
#define R_OSPI_B_CCCTL1CS_CADATASIZE_MASK         0x1e0

#define R_OSPI_B_CCCTL1CS_CAWRLATE_SHIFT          (16)  /* Write Latency Cycle */
#define R_OSPI_B_CCCTL1CS_CAWRLATE_MASK           0x1f0000

#define R_OSPI_B_CCCTL1CS_CARDLATE_SHIFT          (24)  /* Read Latency Cycle */
#define R_OSPI_B_CCCTL1CS_CARDLATE_MASK           0x1f000000

/* CCCTL2CS Register bit definitions */
#define R_OSPI_B_CCCTL2CS_CAWRCMD_SHIFT           (0)  /* Calibration Pattern Write Command */
#define R_OSPI_B_CCCTL2CS_CAWRCMD_MASK            0xffff

#define R_OSPI_B_CCCTL2CS_CARDCMD_SHIFT           (16)  /* Calibration Pattern Read Command */
#define R_OSPI_B_CCCTL2CS_CARDCMD_MASK            0xffff0000

/* CCCTL3CS Register bit definitions */
#define R_OSPI_B_CCCTL3CS_CAADD_SHIFT             (0)  /* Calibration Pattern Address */
#define R_OSPI_B_CCCTL3CS_CAADD_MASK              0xffffffff

/* CCCTL4CS Register bit definitions */
#define R_OSPI_B_CCCTL4CS_CADATA_SHIFT            (0)  /* Calibration Pattern Data */
#define R_OSPI_B_CCCTL4CS_CADATA_MASK             0xffffffff

/* CCCTL5CS Register bit definitions */
#define R_OSPI_B_CCCTL5CS_CADATA_SHIFT            (0)  /* Calibration Pattern Data */
#define R_OSPI_B_CCCTL5CS_CADATA_MASK             0xffffffff

/* CCCTL6CS Register bit definitions */
#define R_OSPI_B_CCCTL6CS_CADATA_SHIFT            (0)  /* Calibration Pattern Data */
#define R_OSPI_B_CCCTL6CS_CADATA_MASK             0xffffffff

/* CCCTL7CS Register bit definitions */
#define R_OSPI_B_CCCTL7CS_CADATA_SHIFT            (0)  /* Calibration Pattern Data */
#define R_OSPI_B_CCCTL7CS_CADATA_MASK             0xffffffff

/* COMSTT Register bit definitions */
#define R_OSPI_B_COMSTT_MEMACCCH0                 (1 << 0)  /* Memory Access Ongoing from Channel 0 */

#define R_OSPI_B_COMSTT_MEMACCCH1                 (1 << 1)  /* Memory Access Ongoing from Channel 1 */

#define R_OSPI_B_COMSTT_PBUFNECH0                 (1 << 4)  /* Prefetch Buffer Not Empty for Channel 0 */

#define R_OSPI_B_COMSTT_PBUFNECH1                 (1 << 5)  /* Prefetch Buffer Not Empty for Channel 1 */

#define R_OSPI_B_COMSTT_WRBUFNECH0                (1 << 6)  /* Write Buffer Not Empty for Channel 0 */

#define R_OSPI_B_COMSTT_WRBUFNECH1                (1 << 7)  /* Write Buffer Not Empty for Channel 1 */

#define R_OSPI_B_COMSTT_ECSCS1                    (1 << 20)  /* ECS Monitor for Slave 1 */

#define R_OSPI_B_COMSTT_INTCS1                    (1 << 21)  /* INT Monitor for Slave 1 */

#define R_OSPI_B_COMSTT_RSTOCS1                   (1 << 22)  /* RSTO Monitor for Slave 1 */

/* CASTTCS Register bit definitions */
#define R_OSPI_B_CASTTCS_CASUC_SHIFT              (0)  /* Calibration Success */
#define R_OSPI_B_CASTTCS_CASUC_MASK               0xffffffff

/* INTS Register bit definitions */
#define R_OSPI_B_INTS_CMDCMP                      (1 << 0)  /* Command Completed */

#define R_OSPI_B_INTS_PATCMP                      (1 << 1)  /* Pattern Completed */

#define R_OSPI_B_INTS_PERTO                       (1 << 3)  /* Periodic Transaction Timeout */

#define R_OSPI_B_INTS_DSTOCS0                     (1 << 4)  /* DS Timeout for Slave 0 */

#define R_OSPI_B_INTS_DSTOCS1                     (1 << 5)  /* DS Timeout for Slave 1 */

#define R_OSPI_B_INTS_ECSCS1                      (1 << 9)  /* ECC Error Detection for Slave 1 */

#define R_OSPI_B_INTS_INTCS1                      (1 << 13)  /* Interrupt Detection for Slave 1 */

#define R_OSPI_B_INTS_BUSERRCH0                   (1 << 20)  /* System Bus Error for Channel 0 */

#define R_OSPI_B_INTS_BUSERRCH1                   (1 << 21)  /* System Bus Error for Channel 1 */

#define R_OSPI_B_INTS_CAFAILCS0                   (1 << 28)  /* Calibration Failed for Slave 0 */

#define R_OSPI_B_INTS_CAFAILCS1                   (1 << 29)  /* Calibration Failed for Slave 1 */

#define R_OSPI_B_INTS_CASUCCS0                    (1 << 30)  /* Calibration Success for Slave 0 */

#define R_OSPI_B_INTS_CASUCCS1                    (1 << 31)  /* Calibration Success for Slave 1 */

/* INTC Register bit definitions */
#define R_OSPI_B_INTC_CMDCMPC                     (1 << 0)  /* Command Completed Interrupt Clear */

#define R_OSPI_B_INTC_PATCMPC                     (1 << 1)  /* Pattern Completed Interrupt Clear */

#define R_OSPI_B_INTC_PERTOC                      (1 << 3)  /* Periodic Transaction Timeout Interrupt Clear */

#define R_OSPI_B_INTC_DSTOCS0C                    (1 << 4)  /* DS Timeout for Slave 0 Interrupt Clear */

#define R_OSPI_B_INTC_DSTOCS1C                    (1 << 5)  /* DS Timeout for Slave 1 Interrupt Clear */

#define R_OSPI_B_INTC_ECSCS1C                     (1 << 9)  /* ECC Error Detection for Slave 1 Interrupt Clear */

#define R_OSPI_B_INTC_INTCS1C                     (1 << 13)  /* Interrupt Detection for Slave 1 Interrupt Clear */

#define R_OSPI_B_INTC_BUSERRCH0C                  (1 << 20)  /* System Bus Error for ch0 Interrupt Clear */

#define R_OSPI_B_INTC_BUSERRCH1C                  (1 << 21)  /* System Bus Error for ch1 Interrupt Clear */

#define R_OSPI_B_INTC_CAFAILCS0C                  (1 << 28)  /* Calibration Failed for Slave 0 Interrupt Clear */

#define R_OSPI_B_INTC_CAFAILCS1C                  (1 << 29)  /* Calibration Failed for Slave 1 Interrupt Clear */

#define R_OSPI_B_INTC_CASUCCS0C                   (1 << 30)  /* Calibration Success for Slave 0 Interrupt Clear */

#define R_OSPI_B_INTC_CASUCCS1C                   (1 << 31)  /* Calibration Success for Slave 1 Interrupt Clear */

/* INTE Register bit definitions */
#define R_OSPI_B_INTE_CMDCMPE                     (1 << 0)  /* Command Completed Interrupt Enable */

#define R_OSPI_B_INTE_PATCMPE                     (1 << 1)  /* Pattern Completed Interrupt Enable */

#define R_OSPI_B_INTE_PERTOE                      (1 << 3)  /* Periodic Transaction Timeout Interrupt Enable */

#define R_OSPI_B_INTE_DSTOCS0E                    (1 << 4)  /* DS Timeout for Slave 0 Interrupt Enable */

#define R_OSPI_B_INTE_DSTOCS1E                    (1 << 5)  /* DS Timeout for Slave 1 Interrupt Enable */

#define R_OSPI_B_INTE_ECSCS1E                     (1 << 9)  /* ECC Error Detection for Slave 1 Interrupt Enable */

#define R_OSPI_B_INTE_INTCS1E                     (1 << 13)  /* Interrupt Detection for Slave 1 Interrupt Enable */

#define R_OSPI_B_INTE_BUSERRCH0E                  (1 << 20)  /* System Bus Error for ch0 Interrupt Enable */

#define R_OSPI_B_INTE_BUSERRCH1E                  (1 << 21)  /* System Bus Error for ch1 Interrupt Enable */

#define R_OSPI_B_INTE_CAFAILCS0E                  (1 << 28)  /* Calibration Failed for Slave 0 Interrupt Enable */

#define R_OSPI_B_INTE_CAFAILCS1E                  (1 << 29)  /* Calibration Failed for Slave 1 Interrupt Enable */

#define R_OSPI_B_INTE_CASUCCS0E                   (1 << 30)  /* Calibration Success for Slave 0 Interrupt Enable */

#define R_OSPI_B_INTE_CASUCCS1E                   (1 << 31)  /* Calibration Success for Slave 1 Interrupt Enable */


/* Maximum number of channels */

#define OSPI_B_MAX_CHANNELS    4

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_OSPI_B_H */
