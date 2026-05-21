/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_iic.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_IIC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_IIC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* IIC Base Address */
#ifndef R_IIC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_IIC_BASE           0x4025e000
#else
#define R_IIC_BASE           0x5025e000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_IIC_CH_STRIDE    0x00000100
#define R_IIC_CH_BASE(ch)   (R_IIC_BASE + ((uint32_t)(ch) * R_IIC_CH_STRIDE))

/* IIC Register Offsets */

#define R_IIC_ICCR1_OFFSET                        0x00000000  /* I2C Bus Control Register 1  */
#define R_IIC_ICCR2_OFFSET                        0x00000001  /* I2C Bus Control Register 2 */
#define R_IIC_ICMR1_OFFSET                        0x00000002  /* I2C Bus Mode Register 1 */
#define R_IIC_ICMR2_OFFSET                        0x00000003  /* I2C Bus Mode Register 2 */
#define R_IIC_ICMR3_OFFSET                        0x00000004  /* I2C Bus Mode Register 3 */
#define R_IIC_ICFER_OFFSET                        0x00000005  /* I2C Bus Function Enable Register  */
#define R_IIC_ICSER_OFFSET                        0x00000006  /* I2C Bus Status Enable Register */
#define R_IIC_ICIER_OFFSET                        0x00000007  /* I2C Bus Interrupt Enable Register */
#define R_IIC_ICSR1_OFFSET                        0x00000008  /* I2C Bus Status Register 1 */
#define R_IIC_ICSR2_OFFSET                        0x00000009  /* I2C Bus Status Register 2 */
/* SAR[%s] Registers () */
#define R_IIC_SAR_OFFSET(m)                       (0x0000000a + ((m) * 0x00000002))  /* Slave Address Registers */
#define R_IIC_ICBRL_OFFSET                        0x00000010  /* I2C Bus Bit Rate Low-Level Register */
#define R_IIC_ICBRH_OFFSET                        0x00000011  /* I2C Bus Bit Rate High-Level Register  */
#define R_IIC_ICDRT_OFFSET                        0x00000012  /* I2C Bus Transmit Data Register */
#define R_IIC_ICDRR_OFFSET                        0x00000013  /* I2C Bus Receive Data Register */
#define R_IIC_ICWUR_OFFSET                        0x00000016  /* I2C Bus Wake Up Unit Register */
#define R_IIC_ICWUR2_OFFSET                       0x00000017  /* I2C Bus Wake up Unit Register 2 */

/* IIC Register Addresses */

#define R_IIC_ICCR1(n)                            (R_IIC_CH_BASE(n) + R_IIC_ICCR1_OFFSET)
#define R_IIC_ICCR2(n)                            (R_IIC_CH_BASE(n) + R_IIC_ICCR2_OFFSET)
#define R_IIC_ICMR1(n)                            (R_IIC_CH_BASE(n) + R_IIC_ICMR1_OFFSET)
#define R_IIC_ICMR2(n)                            (R_IIC_CH_BASE(n) + R_IIC_ICMR2_OFFSET)
#define R_IIC_ICMR3(n)                            (R_IIC_CH_BASE(n) + R_IIC_ICMR3_OFFSET)
#define R_IIC_ICFER(n)                            (R_IIC_CH_BASE(n) + R_IIC_ICFER_OFFSET)
#define R_IIC_ICSER(n)                            (R_IIC_CH_BASE(n) + R_IIC_ICSER_OFFSET)
#define R_IIC_ICIER(n)                            (R_IIC_CH_BASE(n) + R_IIC_ICIER_OFFSET)
#define R_IIC_ICSR1(n)                            (R_IIC_CH_BASE(n) + R_IIC_ICSR1_OFFSET)
#define R_IIC_ICSR2(n)                            (R_IIC_CH_BASE(n) + R_IIC_ICSR2_OFFSET)
#define R_IIC_SAR(n, m)                           (R_IIC_CH_BASE(n) + R_IIC_SAR_OFFSET(m))
#define R_IIC_ICBRL(n)                            (R_IIC_CH_BASE(n) + R_IIC_ICBRL_OFFSET)
#define R_IIC_ICBRH(n)                            (R_IIC_CH_BASE(n) + R_IIC_ICBRH_OFFSET)
#define R_IIC_ICDRT(n)                            (R_IIC_CH_BASE(n) + R_IIC_ICDRT_OFFSET)
#define R_IIC_ICDRR(n)                            (R_IIC_CH_BASE(n) + R_IIC_ICDRR_OFFSET)
#define R_IIC_ICWUR(n)                            (R_IIC_CH_BASE(n) + R_IIC_ICWUR_OFFSET)
#define R_IIC_ICWUR2(n)                           (R_IIC_CH_BASE(n) + R_IIC_ICWUR2_OFFSET)

/* Register bit definitions */
/* ICCR1 Register bit definitions */
#define R_IIC_ICCR1_ICE                           (1 << 7)  /* I2C Bus Interface Enable */

#define R_IIC_ICCR1_IICRST                        (1 << 6)  /* I2C Bus Interface Internal ResetNote:If an internal reset is initiated using the IICRST bit for a bus hang-up occurred during communication with the master device in slave mode, the states may become different between the slave device and the master device (due to the difference in the bit counter information). */

#define R_IIC_ICCR1_CLO                           (1 << 5)  /* Extra SCL Clock Cycle Output */

#define R_IIC_ICCR1_SOWP                          (1 << 4)  /* SCLO/SDAO Write Protect */

#define R_IIC_ICCR1_SCLO                          (1 << 3)  /* SCL Output Control/Monitor */

#define R_IIC_ICCR1_SDAO                          (1 << 2)  /* SDA Output Control/Monitor */

#define R_IIC_ICCR1_SCLI                          (1 << 1)  /* SCL Line Monitor */

#define R_IIC_ICCR1_SDAI                          (1 << 0)  /* SDA Line Monitor */

/* ICCR2 Register bit definitions */
#define R_IIC_ICCR2_BBSY                          (1 << 7)  /* Bus Busy Detection Flag */

#define R_IIC_ICCR2_MST                           (1 << 6)  /* Master/Slave Mode */

#define R_IIC_ICCR2_TRS                           (1 << 5)  /* Transmit/Receive Mode  */

#define R_IIC_ICCR2_SP                            (1 << 3)  /* Stop Condition Issuance RequestNote: Writing to the SP bit is not possible while the setting of the BBSY flag is 0 (bus free state).Note: Do not set the SP bit to 1 while a restart condition is being issued. */

#define R_IIC_ICCR2_RS                            (1 << 2)  /* Restart Condition Issuance RequestNote: Do not set the RS bit to 1 while issuing a stop condition. */

#define R_IIC_ICCR2_ST                            (1 << 1)  /* Start Condition Issuance RequestSet the ST bit to 1 (start condition issuance request) when the BBSY flag is set to 0 (bus free state). */

/* ICMR1 Register bit definitions */
#define R_IIC_ICMR1_MTWP                          (1 << 7)  /* MST/TRS Write Protect */

#define R_IIC_ICMR1_CKS_SHIFT                     (4)  /* Internal Reference Clock (fIIC) Selection ( fIIC = PCLKB / 2^CKS ) */
#define R_IIC_ICMR1_CKS_MASK                      0x70
#  define R_IIC_ICMR1_CKS_000                             (0 << R_IIC_ICMR1_CKS_SHIFT)  /* PCLKB/1 clock */
#  define R_IIC_ICMR1_CKS_001                             (1 << R_IIC_ICMR1_CKS_SHIFT)  /* PCLKB/2 clock */
#  define R_IIC_ICMR1_CKS_010                             (2 << R_IIC_ICMR1_CKS_SHIFT)  /* PCLKB/4 clock */
#  define R_IIC_ICMR1_CKS_011                             (3 << R_IIC_ICMR1_CKS_SHIFT)  /* PCLKB/8 clock */
#  define R_IIC_ICMR1_CKS_100                             (4 << R_IIC_ICMR1_CKS_SHIFT)  /* PCLKB/16 clock */
#  define R_IIC_ICMR1_CKS_101                             (5 << R_IIC_ICMR1_CKS_SHIFT)  /* PCLKB/32 clock */
#  define R_IIC_ICMR1_CKS_110                             (6 << R_IIC_ICMR1_CKS_SHIFT)  /* PCLKB/64 clock */
#  define R_IIC_ICMR1_CKS_111                             (7 << R_IIC_ICMR1_CKS_SHIFT)  /* PCLKB/128 clock */

#define R_IIC_ICMR1_BCWP                          (1 << 3)  /* BC Write Protect(This bit is read as 1.) */

#define R_IIC_ICMR1_BC_SHIFT                      (0)  /* Bit Counter */
#define R_IIC_ICMR1_BC_MASK                       0x7
#  define R_IIC_ICMR1_BC_000                              (0 << R_IIC_ICMR1_BC_SHIFT)  /* 9 bits */
#  define R_IIC_ICMR1_BC_001                              (1 << R_IIC_ICMR1_BC_SHIFT)  /* 2 bits */
#  define R_IIC_ICMR1_BC_010                              (2 << R_IIC_ICMR1_BC_SHIFT)  /* 3 bits */
#  define R_IIC_ICMR1_BC_011                              (3 << R_IIC_ICMR1_BC_SHIFT)  /* 4 bits */
#  define R_IIC_ICMR1_BC_100                              (4 << R_IIC_ICMR1_BC_SHIFT)  /* 5 bits */
#  define R_IIC_ICMR1_BC_101                              (5 << R_IIC_ICMR1_BC_SHIFT)  /* 6 bits */
#  define R_IIC_ICMR1_BC_110                              (6 << R_IIC_ICMR1_BC_SHIFT)  /* 7 bits */
#  define R_IIC_ICMR1_BC_111                              (7 << R_IIC_ICMR1_BC_SHIFT)  /* 8 bits */

/* ICMR2 Register bit definitions */
#define R_IIC_ICMR2_DLCS                          (1 << 7)  /* SDA Output Delay Clock Source Select */

#define R_IIC_ICMR2_SDDL_SHIFT                    (4)  /* SDA Output Delay Counter */
#define R_IIC_ICMR2_SDDL_MASK                     0x70
#  define R_IIC_ICMR2_SDDL_000                            (0 << R_IIC_ICMR2_SDDL_SHIFT)  /* No output delay */
#  define R_IIC_ICMR2_SDDL_001                            (1 << R_IIC_ICMR2_SDDL_SHIFT)  /* 1 fIIC cycle  (ICMR2.DLCS=0) / 1  or 2 fIIC cycles (ICMR2.DLCS=1) */
#  define R_IIC_ICMR2_SDDL_010                            (2 << R_IIC_ICMR2_SDDL_SHIFT)  /* 2 fIIC cycles (ICMR2.DLCS=0) /  3 or 4 fIIC cycles (ICMR2.DLCS=1) */
#  define R_IIC_ICMR2_SDDL_011                            (3 << R_IIC_ICMR2_SDDL_SHIFT)  /* 3 fIIC cycles (ICMR2.DLCS=0) /  5 or 6 fIIC cycles (ICMR2.DLCS=1) */
#  define R_IIC_ICMR2_SDDL_100                            (4 << R_IIC_ICMR2_SDDL_SHIFT)  /* 4 fIIC cycles (ICMR2.DLCS=0) /  7 or 8 fIIC cycles (ICMR2.DLCS=1) */
#  define R_IIC_ICMR2_SDDL_101                            (5 << R_IIC_ICMR2_SDDL_SHIFT)  /* 5 fIIC cycles (ICMR2.DLCS=0) /  9 or 10 fIIC cycles (ICMR2.DLCS=1) */
#  define R_IIC_ICMR2_SDDL_110                            (6 << R_IIC_ICMR2_SDDL_SHIFT)  /* 6 fIIC cycles (ICMR2.DLCS=0) / 11 or 12 fIIC cycles (ICMR2.DLCS=1) */
#  define R_IIC_ICMR2_SDDL_111                            (7 << R_IIC_ICMR2_SDDL_SHIFT)  /* 7 fIIC cycles (ICMR2.DLCS=0) / 13 or 14 fIIC cycles (ICMR2.DLCS=1) */

#define R_IIC_ICMR2_TMOH                          (1 << 2)  /* Timeout H Count Control */

#define R_IIC_ICMR2_TMOL                          (1 << 1)  /* Timeout L Count Control */

#define R_IIC_ICMR2_TMOS                          (1 << 0)  /* Timeout Detection Time Select */

/* ICMR3 Register bit definitions */
#define R_IIC_ICMR3_SMBS                          (1 << 7)  /* SMBus/I2C Bus Selection */

#define R_IIC_ICMR3_WAIT                          (1 << 6)  /* WAITNote: When the value of the WAIT bit is to be read, be sure to read the ICDRR beforehand. */

#define R_IIC_ICMR3_RDRFS                         (1 << 5)  /* RDRF Flag Set Timing Selection */

#define R_IIC_ICMR3_ACKWP                         (1 << 4)  /* ACKBT Write Protect */

#define R_IIC_ICMR3_ACKBT                         (1 << 3)  /* Transmit Acknowledge */

#define R_IIC_ICMR3_ACKBR                         (1 << 2)  /* Receive Acknowledge */

#define R_IIC_ICMR3_NF_SHIFT                      (0)  /* Noise Filter Stage Selection */
#define R_IIC_ICMR3_NF_MASK                       0x3
#  define R_IIC_ICMR3_NF_00                               (0 << R_IIC_ICMR3_NF_SHIFT)  /* Noise of up to one fIIC cycle is filtered out (single-stage filter). */
#  define R_IIC_ICMR3_NF_01                               (1 << R_IIC_ICMR3_NF_SHIFT)  /* Noise of up to two fIIC cycles is filtered out (2-stage filter). */
#  define R_IIC_ICMR3_NF_10                               (2 << R_IIC_ICMR3_NF_SHIFT)  /* Noise of up to three fIIC cycles is filtered out (3-stage filter). */
#  define R_IIC_ICMR3_NF_11                               (3 << R_IIC_ICMR3_NF_SHIFT)  /* Noise of up to four fIIC cycles is filtered out (4-stage filter) */

/* ICFER Register bit definitions */
#define R_IIC_ICFER_FMPE                          (1 << 7)  /* Fast-mode Plus Enable */

#define R_IIC_ICFER_SCLE                          (1 << 6)  /* SCL Synchronous Circuit Enable */

#define R_IIC_ICFER_NFE                           (1 << 5)  /* Digital Noise Filter Circuit Enable */

#define R_IIC_ICFER_NACKE                         (1 << 4)  /* NACK Reception Transfer Suspension Enable */

#define R_IIC_ICFER_SALE                          (1 << 3)  /* Slave Arbitration-Lost Detection Enable */

#define R_IIC_ICFER_NALE                          (1 << 2)  /* NACK Transmission Arbitration-Lost Detection Enable */

#define R_IIC_ICFER_MALE                          (1 << 1)  /* Master Arbitration-Lost Detection Enable  */

#define R_IIC_ICFER_TMOE                          (1 << 0)  /* Timeout Function Enable */

/* ICSER Register bit definitions */
#define R_IIC_ICSER_HOAE                          (1 << 7)  /* Host Address Enable */

#define R_IIC_ICSER_DIDE                          (1 << 5)  /* Device-ID Address Detection Enable */

#define R_IIC_ICSER_GCAE                          (1 << 3)  /* General Call Address Enable */

#define R_IIC_ICSER_SAR2E                         (1 << 2)  /* Slave Address Register 2 Enable */

#define R_IIC_ICSER_SAR1E                         (1 << 1)  /* Slave Address Register 1 Enable */

#define R_IIC_ICSER_SAR0E                         (1 << 0)  /* Slave Address Register 0 Enable */

/* ICIER Register bit definitions */
#define R_IIC_ICIER_TIE                           (1 << 7)  /* Transmit Data Empty Interrupt Request Enable */

#define R_IIC_ICIER_TEIE                          (1 << 6)  /* Transmit End Interrupt Request  Enable */

#define R_IIC_ICIER_RIE                           (1 << 5)  /* Receive Data Full Interrupt Request Enable */

#define R_IIC_ICIER_NAKIE                         (1 << 4)  /* NACK Reception Interrupt Request Enable */

#define R_IIC_ICIER_SPIE                          (1 << 3)  /* Stop Condition Detection Interrupt Request Enable */

#define R_IIC_ICIER_STIE                          (1 << 2)  /* Start Condition Detection Interrupt Request Enable */

#define R_IIC_ICIER_ALIE                          (1 << 1)  /* Arbitration-Lost Interrupt Request Enable */

#define R_IIC_ICIER_TMOIE                         (1 << 0)  /* Timeout Interrupt Request Enable */

/* ICSR1 Register bit definitions */
#define R_IIC_ICSR1_HOA                           (1 << 7)  /* Host Address Detection Flag  */

#define R_IIC_ICSR1_DID                           (1 << 5)  /* Device-ID Address Detection Flag */

#define R_IIC_ICSR1_GCA                           (1 << 3)  /* General Call Address Detection Flag */

#define R_IIC_ICSR1_AAS2                          (1 << 2)  /* Slave Address 2 Detection Flag */

#define R_IIC_ICSR1_AAS1                          (1 << 1)  /* Slave Address 1 Detection Flag */

#define R_IIC_ICSR1_AAS0                          (1 << 0)  /* Slave Address 0 Detection Flag */

/* ICSR2 Register bit definitions */
#define R_IIC_ICSR2_TDRE                          (1 << 7)  /* Transmit Data Empty Flag */

#define R_IIC_ICSR2_TEND                          (1 << 6)  /* Transmit End Flag */

#define R_IIC_ICSR2_RDRF                          (1 << 5)  /* Receive Data Full Flag */

#define R_IIC_ICSR2_NACKF                         (1 << 4)  /* NACK Detection Flag */

#define R_IIC_ICSR2_STOP                          (1 << 3)  /* Stop Condition Detection Flag */

#define R_IIC_ICSR2_START                         (1 << 2)  /* Start Condition Detection Flag  */

#define R_IIC_ICSR2_AL                            (1 << 1)  /* Arbitration-Lost Flag */

#define R_IIC_ICSR2_TMOF                          (1 << 0)  /* Timeout Detection Flag */

/* ICBRL Register bit definitions */
#define R_IIC_ICBRL_BRL_SHIFT                     (0)  /* Bit Rate Low-Level Period(Low-level period of SCL clock) */
#define R_IIC_ICBRL_BRL_MASK                      0x1f

/* ICBRH Register bit definitions */
#define R_IIC_ICBRH_BRH_SHIFT                     (0)  /* Bit Rate High-Level Period(High-level period of SCL clock) */
#define R_IIC_ICBRH_BRH_MASK                      0x1f

/* ICDRT Register bit definitions */
#define R_IIC_ICDRT_ICDRT_SHIFT                   (0)  /* 8-bit read-write register that stores transmit data. */
#define R_IIC_ICDRT_ICDRT_MASK                    0xff

/* ICDRR Register bit definitions */
#define R_IIC_ICDRR_ICDRR_SHIFT                   (0)  /* 8-bit register that stores the received data */
#define R_IIC_ICDRR_ICDRR_MASK                    0xff

/* ICWUR Register bit definitions */
#define R_IIC_ICWUR_WUE                           (1 << 7)  /* Wakeup Function Enable */

#define R_IIC_ICWUR_WUIE                          (1 << 6)  /* Wakeup Interrupt Request Enable */

#define R_IIC_ICWUR_WUF                           (1 << 5)  /* Wakeup Event Occurrence Flag */

#define R_IIC_ICWUR_WUACK                         (1 << 4)  /* ACK bit for Wakeup Mode */

#define R_IIC_ICWUR_WUAFA                         (1 << 0)  /* Wakeup Analog Filter Additional Selection */

/* ICWUR2 Register bit definitions */
#define R_IIC_ICWUR2_WUSYF                        (1 << 2)  /* Wake-up Function Synchronous Operation Status Flag */

#define R_IIC_ICWUR2_WUASYF                       (1 << 1)  /* Wake-up Function Asynchronous Operation Status Flag */

#define R_IIC_ICWUR2_WUSEN                        (1 << 0)  /* Wake-up Function Synchronous Enable */


/* Maximum number of channels */

#define IIC_MAX_CHANNELS    3

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_IIC_H */
