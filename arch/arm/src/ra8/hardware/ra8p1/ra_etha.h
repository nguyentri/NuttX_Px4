/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_etha.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ETHA_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ETHA_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ETHA Base Address */
#ifndef R_ETHA_BASE
#define R_ETHA_BASE           0x503ca000
#endif

/* Channel stride for multi-channel peripherals */
#define R_ETHA_CH_STRIDE    0x00002000
#define R_ETHA_CH_BASE(ch)   (R_ETHA_BASE + ((uint32_t)(ch) * R_ETHA_CH_STRIDE))

/* ETHA Register Offsets */

#define R_ETHA_EAMC_OFFSET                        0x00000000  /* Mode Configuration Register */
#define R_ETHA_EAMS_OFFSET                        0x00000004  /* Mode Status Register */
#define R_ETHA_EAIRC_OFFSET                       0x00000010  /* IPV Remapping Configuration Register [802.1Q] */
#define R_ETHA_EATDQSC_OFFSET                     0x00000014  /* TX Descriptor Queue Security Configuration Register */
#define R_ETHA_EATDQC_OFFSET                      0x00000018  /* TX Descriptor Queue Configuration Register */
#define R_ETHA_EATDQAC_OFFSET                     0x0000001c  /* TX Descriptor Queue Arbitration Configuration Register */
#define R_ETHA_EATPEC_OFFSET                      0x00000020  /* TX Preemption Configuration Register */
/* EATMFSC%s Registers (0-7) */
#define R_ETHA_EATMFSC_OFFSET(m)                  (0x00000040 + ((m) * 0x00000004))  /* Transmission Maximum Frame Size Configuration Register %s */
/* EATDQDC%s Registers (0-7) */
#define R_ETHA_EATDQDC_OFFSET(m)                  (0x00000060 + ((m) * 0x00000004))  /* Transmission Descriptor Queue Depth Configuration Register %s */
/* EATDQM%s Registers (0-7) */
#define R_ETHA_EATDQM_OFFSET(m)                   (0x00000080 + ((m) * 0x00000004))  /* Transmission Descriptor Queue %s Monitoring Register */
/* EATDQMLM%s Registers (0-7) */
#define R_ETHA_EATDQMLM_OFFSET(m)                 (0x000000a0 + ((m) * 0x00000004))  /* Transmission Descriptor Queue %s Max Level Monitoring Register */
#define R_ETHA_EACTQC_OFFSET                      0x00000100  /* Cut-Through Queue Configuration Register */
#define R_ETHA_EACTDQDC_OFFSET                    0x00000104  /* Cut-Through Descriptor Queue Depth Configuration Register */
#define R_ETHA_EACTDQM_OFFSET                     0x00000108  /* Cut-Through Descriptor Queue Monitoring Register */
#define R_ETHA_EACTDQMLM_OFFSET                   0x0000010c  /* Cut-Through Descriptor Queue Max Level Monitoring Register */
#define R_ETHA_EAVCC_OFFSET                       0x00000130  /* VLAN Control Configuration Register */
#define R_ETHA_EAVTC_OFFSET                       0x00000134  /* VLAN TAG Configuration Register */
#define R_ETHA_EARTFC_OFFSET                      0x00000138  /* Reception TAG Filtering Configuration Register */
#define R_ETHA_EACAEC_OFFSET                      0x00000200  /* CBS Admin Enable Configuration Register */
#define R_ETHA_EACC_OFFSET                        0x00000204  /* CBS Configuration Register */
/* EACAIVC%s Registers (0-7) */
#define R_ETHA_EACAIVC_OFFSET(m)                  (0x00000220 + ((m) * 0x00000004))  /* CBS Admin Increment Value Configuration Register %s */
#define R_ETHA_EACAULCQ_OFFSET                    0x00000240  /* CBS Admin Upper Limit Configuration Register q */
#define R_ETHA_EACOEM_OFFSET                      0x00000260  /* CBS Oper Enable Monitoring Register */
/* EACOIVM%s Registers (0-7) */
#define R_ETHA_EACOIVM_OFFSET(m)                  (0x00000280 + ((m) * 0x00000004))  /* CBS Oper Increment Value Monitoring Register %s */
/* EACOULM%s Registers (0-7) */
#define R_ETHA_EACOULM_OFFSET(m)                  (0x000002a0 + ((m) * 0x00000004))  /* CBS Oper Upper Limit Monitoring Register %s */
#define R_ETHA_EACGSM_OFFSET                      0x000002c0  /* CBS Gate State Monitoring Register */
#define R_ETHA_EATASC_OFFSET                      0x00000300  /* TAS Configuration Register */
#define R_ETHA_EATASIGSC_OFFSET                   0x00000304  /* TAS Initial Gate State Configuration Register */
/* EATASENC%s Registers (0-7) */
#define R_ETHA_EATASENC_OFFSET(m)                 (0x00000320 + ((m) * 0x00000004))  /* TAS Entry Number Configuration Register %s */
#define R_ETHA_EATASCTENC_OFFSET                  0x00000340  /* TAS Cut-Through Entry Number Configuration Register */
/* EATASENM%s Registers (0-7) */
#define R_ETHA_EATASENM_OFFSET(m)                 (0x00000360 + ((m) * 0x00000004))  /* TAS Entry Number Monitoring Register %s */
#define R_ETHA_EATASCTENM_OFFSET                  0x00000380  /* TAS Cut-Through Entry Number Monitoring Register */
#define R_ETHA_EATASCSTC0_OFFSET                  0x000003a0  /* TAS Cycle Start Time Configuration Register 0 */
#define R_ETHA_EATASCSTC1_OFFSET                  0x000003a4  /* TAS Cycle Start Time Configuration Register 1 */
#define R_ETHA_EATASCSTM0_OFFSET                  0x000003a8  /* TAS Cycle Start Time Monitoring Register 0 */
#define R_ETHA_EATASCSTM1_OFFSET                  0x000003ac  /* TAS Cycle Start Time Monitoring Register 1 */
#define R_ETHA_EATASCTC_OFFSET                    0x000003b0  /* TAS Cycle Time Configuration Register */
#define R_ETHA_EATASCTM_OFFSET                    0x000003b4  /* TAS Cycle Time Monitoring Register */
#define R_ETHA_EATASGL0_OFFSET                    0x000003c0  /* TAS Gate Learn Register 0 */
#define R_ETHA_EATASGL1_OFFSET                    0x000003c4  /* TAS Gate Learn Register 1 */
#define R_ETHA_EATASGLR_OFFSET                    0x000003c8  /* TAS Gate Learn Result Register */
#define R_ETHA_EATASGR_OFFSET                     0x000003d0  /* TAS Gate Read Register */
#define R_ETHA_EATASGRR_OFFSET                    0x000003d4  /* TAS Gate Read Result Register */
#define R_ETHA_EATASHCC_OFFSET                    0x000003e0  /* TAS Hardware Calibration Configuration Register */
#define R_ETHA_EATASRIRM_OFFSET                   0x000003e4  /* TAS RAM Initialization Register Monitoring Register */
#define R_ETHA_EATASSM_OFFSET                     0x000003e8  /* TAS Status Monitoring Register */
#define R_ETHA_EAUSMFSECN_OFFSET                  0x00000400  /* Under Minimum Frame Size Error Counter Register */
#define R_ETHA_EATFECN_OFFSET                     0x00000404  /* TAG Filtering Error Counter Register */
#define R_ETHA_EAFSECN_OFFSET                     0x00000408  /* Frame Size Error Counter Register */
#define R_ETHA_EADQOECN_OFFSET                    0x0000040c  /* Descriptor Queue Overflow Error Counter Register */
#define R_ETHA_EADQSECN_OFFSET                    0x00000410  /* Descriptor Queue Security Error Counter Register */
#define R_ETHA_EAEIS0_OFFSET                      0x00000500  /* Error Interrupt Status Register 0 */
#define R_ETHA_EAEIE0_OFFSET                      0x00000504  /* Error Interrupt Enable Register 0 */
#define R_ETHA_EAEID0_OFFSET                      0x00000508  /* Error Interrupt Disable Register 0 */
#define R_ETHA_EAEIS1_OFFSET                      0x00000510  /* Error Interrupt Status Register 1 */
#define R_ETHA_EAEIE1_OFFSET                      0x00000514  /* Error Interrupt Enable Register 1 */
#define R_ETHA_EAEID1_OFFSET                      0x00000518  /* Error Interrupt Disable Register 1 */
#define R_ETHA_EAEIS2_OFFSET                      0x00000520  /* Error Interrupt Status Register 2 */
#define R_ETHA_EAEIE2_OFFSET                      0x00000524  /* Error Interrupt Enable Register 2 */
#define R_ETHA_EAEID2_OFFSET                      0x00000528  /* Error Interrupt Disable Register 2 */

/* ETHA Register Addresses */

#define R_ETHA_EAMC(n)                            (R_ETHA_CH_BASE(n) + R_ETHA_EAMC_OFFSET)
#define R_ETHA_EAMS(n)                            (R_ETHA_CH_BASE(n) + R_ETHA_EAMS_OFFSET)
#define R_ETHA_EAIRC(n)                           (R_ETHA_CH_BASE(n) + R_ETHA_EAIRC_OFFSET)
#define R_ETHA_EATDQSC(n)                         (R_ETHA_CH_BASE(n) + R_ETHA_EATDQSC_OFFSET)
#define R_ETHA_EATDQC(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EATDQC_OFFSET)
#define R_ETHA_EATDQAC(n)                         (R_ETHA_CH_BASE(n) + R_ETHA_EATDQAC_OFFSET)
#define R_ETHA_EATPEC(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EATPEC_OFFSET)
#define R_ETHA_EATMFSC(n, m)                      (R_ETHA_CH_BASE(n) + R_ETHA_EATMFSC_OFFSET(m))
#define R_ETHA_EATDQDC(n, m)                      (R_ETHA_CH_BASE(n) + R_ETHA_EATDQDC_OFFSET(m))
#define R_ETHA_EATDQM(n, m)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATDQM_OFFSET(m))
#define R_ETHA_EATDQMLM(n, m)                     (R_ETHA_CH_BASE(n) + R_ETHA_EATDQMLM_OFFSET(m))
#define R_ETHA_EACTQC(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EACTQC_OFFSET)
#define R_ETHA_EACTDQDC(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACTDQDC_OFFSET)
#define R_ETHA_EACTDQM(n)                         (R_ETHA_CH_BASE(n) + R_ETHA_EACTDQM_OFFSET)
#define R_ETHA_EACTDQMLM(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EACTDQMLM_OFFSET)
#define R_ETHA_EAVCC(n)                           (R_ETHA_CH_BASE(n) + R_ETHA_EAVCC_OFFSET)
#define R_ETHA_EAVTC(n)                           (R_ETHA_CH_BASE(n) + R_ETHA_EAVTC_OFFSET)
#define R_ETHA_EARTFC(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EARTFC_OFFSET)
#define R_ETHA_EACAEC(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EACAEC_OFFSET)
#define R_ETHA_EACC(n)                            (R_ETHA_CH_BASE(n) + R_ETHA_EACC_OFFSET)
#define R_ETHA_EACAIVC(n, m)                      (R_ETHA_CH_BASE(n) + R_ETHA_EACAIVC_OFFSET(m))
#define R_ETHA_EACAULCQ(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACAULCQ_OFFSET)
#define R_ETHA_EACOEM(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EACOEM_OFFSET)
#define R_ETHA_EACOIVM(n, m)                      (R_ETHA_CH_BASE(n) + R_ETHA_EACOIVM_OFFSET(m))
#define R_ETHA_EACOULM(n, m)                      (R_ETHA_CH_BASE(n) + R_ETHA_EACOULM_OFFSET(m))
#define R_ETHA_EACGSM(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EACGSM_OFFSET)
#define R_ETHA_EATASC(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EATASC_OFFSET)
#define R_ETHA_EATASIGSC(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATASIGSC_OFFSET)
#define R_ETHA_EATASENC(n, m)                     (R_ETHA_CH_BASE(n) + R_ETHA_EATASENC_OFFSET(m))
#define R_ETHA_EATASCTENC(n)                      (R_ETHA_CH_BASE(n) + R_ETHA_EATASCTENC_OFFSET)
#define R_ETHA_EATASENM(n, m)                     (R_ETHA_CH_BASE(n) + R_ETHA_EATASENM_OFFSET(m))
#define R_ETHA_EATASCTENM(n)                      (R_ETHA_CH_BASE(n) + R_ETHA_EATASCTENM_OFFSET)
#define R_ETHA_EATASCSTC0(n)                      (R_ETHA_CH_BASE(n) + R_ETHA_EATASCSTC0_OFFSET)
#define R_ETHA_EATASCSTC1(n)                      (R_ETHA_CH_BASE(n) + R_ETHA_EATASCSTC1_OFFSET)
#define R_ETHA_EATASCSTM0(n)                      (R_ETHA_CH_BASE(n) + R_ETHA_EATASCSTM0_OFFSET)
#define R_ETHA_EATASCSTM1(n)                      (R_ETHA_CH_BASE(n) + R_ETHA_EATASCSTM1_OFFSET)
#define R_ETHA_EATASCTC(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EATASCTC_OFFSET)
#define R_ETHA_EATASCTM(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EATASCTM_OFFSET)
#define R_ETHA_EATASGL0(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EATASGL0_OFFSET)
#define R_ETHA_EATASGL1(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EATASGL1_OFFSET)
#define R_ETHA_EATASGLR(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EATASGLR_OFFSET)
#define R_ETHA_EATASGR(n)                         (R_ETHA_CH_BASE(n) + R_ETHA_EATASGR_OFFSET)
#define R_ETHA_EATASGRR(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EATASGRR_OFFSET)
#define R_ETHA_EATASHCC(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EATASHCC_OFFSET)
#define R_ETHA_EATASRIRM(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATASRIRM_OFFSET)
#define R_ETHA_EATASSM(n)                         (R_ETHA_CH_BASE(n) + R_ETHA_EATASSM_OFFSET)
#define R_ETHA_EAUSMFSECN(n)                      (R_ETHA_CH_BASE(n) + R_ETHA_EAUSMFSECN_OFFSET)
#define R_ETHA_EATFECN(n)                         (R_ETHA_CH_BASE(n) + R_ETHA_EATFECN_OFFSET)
#define R_ETHA_EAFSECN(n)                         (R_ETHA_CH_BASE(n) + R_ETHA_EAFSECN_OFFSET)
#define R_ETHA_EADQOECN(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EADQOECN_OFFSET)
#define R_ETHA_EADQSECN(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EADQSECN_OFFSET)
#define R_ETHA_EAEIS0(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EAEIS0_OFFSET)
#define R_ETHA_EAEIE0(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EAEIE0_OFFSET)
#define R_ETHA_EAEID0(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EAEID0_OFFSET)
#define R_ETHA_EAEIS1(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EAEIS1_OFFSET)
#define R_ETHA_EAEIE1(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EAEIE1_OFFSET)
#define R_ETHA_EAEID1(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EAEID1_OFFSET)
#define R_ETHA_EAEIS2(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EAEIS2_OFFSET)
#define R_ETHA_EAEIE2(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EAEIE2_OFFSET)
#define R_ETHA_EAEID2(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EAEID2_OFFSET)

/* Register bit definitions */
/* EAMC Register bit definitions */
#define R_ETHA_EAMC_OPC_SHIFT                     (0)  /* Operating Mode Command */
#define R_ETHA_EAMC_OPC_MASK                      0x3
#  define R_ETHA_EAMC_OPC_00                              (0 << R_ETHA_EAMC_OPC_SHIFT)  /* Enter RESET mode */
#  define R_ETHA_EAMC_OPC_01                              (1 << R_ETHA_EAMC_OPC_SHIFT)  /* Enter DISABLE mode */
#  define R_ETHA_EAMC_OPC_10                              (2 << R_ETHA_EAMC_OPC_SHIFT)  /* Enter CONFIG mode */
#  define R_ETHA_EAMC_OPC_11                              (3 << R_ETHA_EAMC_OPC_SHIFT)  /* Enter OPERATION mode */

/* EAMS Register bit definitions */
#define R_ETHA_EAMS_OPS_SHIFT                     (0)  /* Operating Mode Status Flag */
#define R_ETHA_EAMS_OPS_MASK                      0x3
#  define R_ETHA_EAMS_OPS_00                              (0 << R_ETHA_EAMS_OPS_SHIFT)  /* RESET mode */
#  define R_ETHA_EAMS_OPS_01                              (1 << R_ETHA_EAMS_OPS_SHIFT)  /* DISABLE mode */
#  define R_ETHA_EAMS_OPS_10                              (2 << R_ETHA_EAMS_OPS_SHIFT)  /* CONFIG mode */
#  define R_ETHA_EAMS_OPS_11                              (3 << R_ETHA_EAMS_OPS_SHIFT)  /* OPERATION mode */

/* EAIRC Register bit definitions */
#define R_ETHA_EAIRC_IPVR0_SHIFT                  (0)  /* IPV Remapping 0 */
#define R_ETHA_EAIRC_IPVR0_MASK                   0x7

#define R_ETHA_EAIRC_IPVR1_SHIFT                  (4)  /* IPV Remapping 1 */
#define R_ETHA_EAIRC_IPVR1_MASK                   0x70

#define R_ETHA_EAIRC_IPVR2_SHIFT                  (8)  /* IPV Remapping 2 */
#define R_ETHA_EAIRC_IPVR2_MASK                   0x700

#define R_ETHA_EAIRC_IPVR3_SHIFT                  (12)  /* IPV Remapping 3 */
#define R_ETHA_EAIRC_IPVR3_MASK                   0x7000

#define R_ETHA_EAIRC_IPVR4_SHIFT                  (16)  /* IPV Remapping 4 */
#define R_ETHA_EAIRC_IPVR4_MASK                   0x70000

#define R_ETHA_EAIRC_IPVR5_SHIFT                  (20)  /* IPV Remapping 5 */
#define R_ETHA_EAIRC_IPVR5_MASK                   0x700000

#define R_ETHA_EAIRC_IPVR6_SHIFT                  (24)  /* IPV Remapping 6 */
#define R_ETHA_EAIRC_IPVR6_MASK                   0x7000000

#define R_ETHA_EAIRC_IPVR7_SHIFT                  (28)  /* IPV Remapping 7 */
#define R_ETHA_EAIRC_IPVR7_MASK                   0x70000000

/* EATDQSC Register bit definitions */
#define R_ETHA_EATDQSC_TDQSL0                     (1 << 0)  /* TX Descriptor Queue n Security Level (n = 0 to 7) */

#define R_ETHA_EATDQSC_TDQSL1                     (1 << 1)  /* TX Descriptor Queue n Security Level (n = 0 to 7) */

#define R_ETHA_EATDQSC_TDQSL2                     (1 << 2)  /* TX Descriptor Queue n Security Level (n = 0 to 7) */

#define R_ETHA_EATDQSC_TDQSL3                     (1 << 3)  /* TX Descriptor Queue n Security Level (n = 0 to 7) */

#define R_ETHA_EATDQSC_TDQSL4                     (1 << 4)  /* TX Descriptor Queue n Security Level (n = 0 to 7) */

#define R_ETHA_EATDQSC_TDQSL5                     (1 << 5)  /* TX Descriptor Queue n Security Level (n = 0 to 7) */

#define R_ETHA_EATDQSC_TDQSL6                     (1 << 6)  /* TX Descriptor Queue n Security Level (n = 0 to 7) */

#define R_ETHA_EATDQSC_TDQSL7                     (1 << 7)  /* TX Descriptor Queue n Security Level (n = 0 to 7) */

/* EATDQC Register bit definitions */
#define R_ETHA_EATDQC_TDQD0                       (1 << 0)  /* TX Descriptor Queue n Disable (n = 0 to 7) */

#define R_ETHA_EATDQC_TDQD1                       (1 << 1)  /* TX Descriptor Queue n Disable (n = 0 to 7) */

#define R_ETHA_EATDQC_TDQD2                       (1 << 2)  /* TX Descriptor Queue n Disable (n = 0 to 7) */

#define R_ETHA_EATDQC_TDQD3                       (1 << 3)  /* TX Descriptor Queue n Disable (n = 0 to 7) */

#define R_ETHA_EATDQC_TDQD4                       (1 << 4)  /* TX Descriptor Queue n Disable (n = 0 to 7) */

#define R_ETHA_EATDQC_TDQD5                       (1 << 5)  /* TX Descriptor Queue n Disable (n = 0 to 7) */

#define R_ETHA_EATDQC_TDQD6                       (1 << 6)  /* TX Descriptor Queue n Disable (n = 0 to 7) */

#define R_ETHA_EATDQC_TDQD7                       (1 << 7)  /* TX Descriptor Queue n Disable (n = 0 to 7) */

#define R_ETHA_EATDQC_TCTDQD                      (1 << 8)  /* TX Cut-Through Descriptor Queue Disable */

#define R_ETHA_EATDQC_TDQP0                       (1 << 16)  /* TX Descriptor Queue n Pause (n = 0 to 7) */

#define R_ETHA_EATDQC_TDQP1                       (1 << 17)  /* TX Descriptor Queue n Pause (n = 0 to 7) */

#define R_ETHA_EATDQC_TDQP2                       (1 << 18)  /* TX Descriptor Queue n Pause (n = 0 to 7) */

#define R_ETHA_EATDQC_TDQP3                       (1 << 19)  /* TX Descriptor Queue n Pause (n = 0 to 7) */

#define R_ETHA_EATDQC_TDQP4                       (1 << 20)  /* TX Descriptor Queue n Pause (n = 0 to 7) */

#define R_ETHA_EATDQC_TDQP5                       (1 << 21)  /* TX Descriptor Queue n Pause (n = 0 to 7) */

#define R_ETHA_EATDQC_TDQP6                       (1 << 22)  /* TX Descriptor Queue n Pause (n = 0 to 7) */

#define R_ETHA_EATDQC_TDQP7                       (1 << 23)  /* TX Descriptor Queue n Pause (n = 0 to 7) */

/* EATDQAC Register bit definitions */
#define R_ETHA_EATDQAC_TDQA0_SHIFT                (0)  /* TX Descriptor Queue Arbitration 0 */
#define R_ETHA_EATDQAC_TDQA0_MASK                 0xf
#  define R_ETHA_EATDQAC_TDQA0_0                          (0 << R_ETHA_EATDQAC_TDQA0_SHIFT)  /* Queue 0 strict arbitration */

#define R_ETHA_EATDQAC_TDQA1_SHIFT                (4)  /* TX Descriptor Queue Arbitration 1 */
#define R_ETHA_EATDQAC_TDQA1_MASK                 0xf0
#  define R_ETHA_EATDQAC_TDQA1_0                          (0 << R_ETHA_EATDQAC_TDQA1_SHIFT)  /* Queue 1 strict arbitration */

#define R_ETHA_EATDQAC_TDQA2_SHIFT                (8)  /* TX Descriptor Queue Arbitration 2 */
#define R_ETHA_EATDQAC_TDQA2_MASK                 0xf00
#  define R_ETHA_EATDQAC_TDQA2_0                          (0 << R_ETHA_EATDQAC_TDQA2_SHIFT)  /* Queue 2 strict arbitration */

#define R_ETHA_EATDQAC_TDQA3_SHIFT                (12)  /* TX Descriptor Queue Arbitration 3 */
#define R_ETHA_EATDQAC_TDQA3_MASK                 0xf000
#  define R_ETHA_EATDQAC_TDQA3_0                          (0 << R_ETHA_EATDQAC_TDQA3_SHIFT)  /* Queue 3 strict arbitration */

#define R_ETHA_EATDQAC_TDQA4_SHIFT                (16)  /* TX Descriptor Queue Arbitration 4 */
#define R_ETHA_EATDQAC_TDQA4_MASK                 0xf0000
#  define R_ETHA_EATDQAC_TDQA4_0                          (0 << R_ETHA_EATDQAC_TDQA4_SHIFT)  /* Queue 4 strict arbitration */

#define R_ETHA_EATDQAC_TDQA5_SHIFT                (20)  /* TX Descriptor Queue Arbitration 5 */
#define R_ETHA_EATDQAC_TDQA5_MASK                 0xf00000
#  define R_ETHA_EATDQAC_TDQA5_0                          (0 << R_ETHA_EATDQAC_TDQA5_SHIFT)  /* Queue 5 strict arbitration */

#define R_ETHA_EATDQAC_TDQA6_SHIFT                (24)  /* TX Descriptor Queue Arbitration 6 */
#define R_ETHA_EATDQAC_TDQA6_MASK                 0xf000000
#  define R_ETHA_EATDQAC_TDQA6_0                          (0 << R_ETHA_EATDQAC_TDQA6_SHIFT)  /* Queue 6 strict arbitration */

#define R_ETHA_EATDQAC_TDQA7_SHIFT                (28)  /* TX Descriptor Queue Arbitration 7 */
#define R_ETHA_EATDQAC_TDQA7_MASK                 0xf0000000
#  define R_ETHA_EATDQAC_TDQA7_0                          (0 << R_ETHA_EATDQAC_TDQA7_SHIFT)  /* Queue 7 strict arbitration */

/* EATPEC Register bit definitions */
#define R_ETHA_EATPEC_TTQ0                        (1 << 0)  /* Transmission Type Queue n (n = 0 to 7) */

#define R_ETHA_EATPEC_TTQ1                        (1 << 1)  /* Transmission Type Queue n (n = 0 to 7) */

#define R_ETHA_EATPEC_TTQ2                        (1 << 2)  /* Transmission Type Queue n (n = 0 to 7) */

#define R_ETHA_EATPEC_TTQ3                        (1 << 3)  /* Transmission Type Queue n (n = 0 to 7) */

#define R_ETHA_EATPEC_TTQ4                        (1 << 4)  /* Transmission Type Queue n (n = 0 to 7) */

#define R_ETHA_EATPEC_TTQ5                        (1 << 5)  /* Transmission Type Queue n (n = 0 to 7) */

#define R_ETHA_EATPEC_TTQ6                        (1 << 6)  /* Transmission Type Queue n (n = 0 to 7) */

#define R_ETHA_EATPEC_TTQ7                        (1 << 7)  /* Transmission Type Queue n (n = 0 to 7) */

#define R_ETHA_EATPEC_AFS_SHIFT                   (16)  /* Additional Fragment Size */
#define R_ETHA_EATPEC_AFS_MASK                    0x30000
#  define R_ETHA_EATPEC_AFS_00                            (0 << R_ETHA_EATPEC_AFS_SHIFT)  /* 0 byte is added to minimum fragment size (minimum fragment size = 64 bytes) */
#  define R_ETHA_EATPEC_AFS_01                            (1 << R_ETHA_EATPEC_AFS_SHIFT)  /* 64 bytes are added to minimum fragment size (minimum fragment size = 128 bytes) */
#  define R_ETHA_EATPEC_AFS_10                            (2 << R_ETHA_EATPEC_AFS_SHIFT)  /* 128 bytes are added to minimum fragment size (minimum fragment size = 192 bytes) */
#  define R_ETHA_EATPEC_AFS_11                            (3 << R_ETHA_EATPEC_AFS_SHIFT)  /* 192 bytes are added to minimum fragment size (minimum fragment size = 256 bytes) */

#define R_ETHA_EATPEC_TTQ8                        (1 << 8)  /* TTQ8 */

#define R_ETHA_EATPEC_TTQ9                        (1 << 9)  /* TTQ9 */

/* EATMFSC Register bit definitions */
#define R_ETHA_EATMFSC_MFS_SHIFT                  (0)  /* Maximum Frame Size */
#define R_ETHA_EATMFSC_MFS_MASK                   0xffff

/* EATDQDC Register bit definitions */
#define R_ETHA_EATDQDC_DQD_SHIFT                  (0)  /* Descriptor Queue Depth */
#define R_ETHA_EATDQDC_DQD_MASK                   0x3ff

/* EATDQM Register bit definitions */
#define R_ETHA_EATDQM_DNQ_SHIFT                   (0)  /* Descriptor Number in Queue */
#define R_ETHA_EATDQM_DNQ_MASK                    0x3ff

/* EATDQMLM Register bit definitions */
#define R_ETHA_EATDQMLM_DMLQ_SHIFT                (0)  /* Descriptor Max Level in Queue */
#define R_ETHA_EATDQMLM_DMLQ_MASK                 0x3ff

/* EACTQC Register bit definitions */
#define R_ETHA_EACTQC_CTQD_SHIFT                  (0)  /* Cut-Through Queue Delay (clk Cycle Number) */
#define R_ETHA_EACTQC_CTQD_MASK                   0xffff

/* EACTDQDC Register bit definitions */
#define R_ETHA_EACTDQDC_CTDQD_SHIFT               (0)  /* Cut-Through Descriptor Queue Depth */
#define R_ETHA_EACTDQDC_CTDQD_MASK                0xf

/* EACTDQM Register bit definitions */
#define R_ETHA_EACTDQM_CTQDN_SHIFT                (0)  /* Cut-Though Queue Descriptor Number */
#define R_ETHA_EACTDQM_CTQDN_MASK                 0x3ff

/* EACTDQMLM Register bit definitions */
#define R_ETHA_EACTDQMLM_CTDMLQ_SHIFT             (0)  /* Cut-Through Descriptor Max Level in Queue */
#define R_ETHA_EACTDQMLM_CTDMLQ_MASK              0xf

/* EAVCC Register bit definitions */
#define R_ETHA_EAVCC_VIM                          (1 << 0)  /* VLAN Ingress Mode */

#define R_ETHA_EAVCC_VEM_SHIFT                    (16)  /* VLAN Egress Mode */
#define R_ETHA_EAVCC_VEM_MASK                     0x70000
#  define R_ETHA_EAVCC_VEM_000                            (0 << R_ETHA_EAVCC_VEM_SHIFT)  /* No VLAN mode */
#  define R_ETHA_EAVCC_VEM_001                            (1 << R_ETHA_EAVCC_VEM_SHIFT)  /* C-TAG VLAN mode */
#  define R_ETHA_EAVCC_VEM_010                            (2 << R_ETHA_EAVCC_VEM_SHIFT)  /* HW C-TAG VLAN mode */
#  define R_ETHA_EAVCC_VEM_011                            (3 << R_ETHA_EAVCC_VEM_SHIFT)  /* SC-TAG VLAN mode */
#  define R_ETHA_EAVCC_VEM_100                            (4 << R_ETHA_EAVCC_VEM_SHIFT)  /* HW SC-TAG VLAN mode */

/* EAVTC Register bit definitions */
#define R_ETHA_EAVTC_CTV_SHIFT                    (0)  /* C-TAG VLAN */
#define R_ETHA_EAVTC_CTV_MASK                     0xfff

#define R_ETHA_EAVTC_CTP_SHIFT                    (12)  /* C-TAG PCP */
#define R_ETHA_EAVTC_CTP_MASK                     0x7000

#define R_ETHA_EAVTC_CTD                          (1 << 15)  /* C-TAG DEI */

#define R_ETHA_EAVTC_STV_SHIFT                    (16)  /* S-TAG VLAN */
#define R_ETHA_EAVTC_STV_MASK                     0xfff0000

#define R_ETHA_EAVTC_STP_SHIFT                    (28)  /* S-TAG PCP */
#define R_ETHA_EAVTC_STP_MASK                     0x70000000

#define R_ETHA_EAVTC_STD                          (1 << 31)  /* S-TAG DEI */

/* EARTFC Register bit definitions */
#define R_ETHA_EARTFC_NT                          (1 << 0)  /* No TAG */

#define R_ETHA_EARTFC_RT                          (1 << 1)  /* R-TAG */

#define R_ETHA_EARTFC_CST                         (1 << 2)  /* CoS-TAG */

#define R_ETHA_EARTFC_CSRT                        (1 << 3)  /* CoSR-TAG */

#define R_ETHA_EARTFC_CT                          (1 << 4)  /* C-TAG */

#define R_ETHA_EARTFC_CRT                         (1 << 5)  /* CR-TAG */

#define R_ETHA_EARTFC_SCT                         (1 << 6)  /* SC-TAG */

#define R_ETHA_EARTFC_SCRT                        (1 << 7)  /* SCR-TAG */

#define R_ETHA_EARTFC_UT                          (1 << 8)  /* Unknown TAG */

/* EACAEC Register bit definitions */
#define R_ETHA_EACAEC_CE0                         (1 << 0)  /* CBS Enable n (n = 0 to 7) */

#define R_ETHA_EACAEC_CE1                         (1 << 1)  /* CBS Enable n (n = 0 to 7) */

#define R_ETHA_EACAEC_CE2                         (1 << 2)  /* CBS Enable n (n = 0 to 7) */

#define R_ETHA_EACAEC_CE3                         (1 << 3)  /* CBS Enable n (n = 0 to 7) */

#define R_ETHA_EACAEC_CE4                         (1 << 4)  /* CBS Enable n (n = 0 to 7) */

#define R_ETHA_EACAEC_CE5                         (1 << 5)  /* CBS Enable n (n = 0 to 7) */

#define R_ETHA_EACAEC_CE6                         (1 << 6)  /* CBS Enable n (n = 0 to 7) */

#define R_ETHA_EACAEC_CE7                         (1 << 7)  /* CBS Enable n (n = 0 to 7) */

/* EACC Register bit definitions */
#define R_ETHA_EACC_CC7 TO CC0_SHIFT              (0)  /* Configuration Change n (n = 0 to 7) */
#define R_ETHA_EACC_CC7 TO CC0_MASK               0xff
#  define R_ETHA_EACC_CC7 TO CC0_0                        (0 << R_ETHA_EACC_CC7 TO CC0_SHIFT)  /* No effect */
#  define R_ETHA_EACC_CC7 TO CC0_1                        (1 << R_ETHA_EACC_CC7 TO CC0_SHIFT)  /* The Admin settings of CBS i are copied to its Oper settings (EACAEC.CEi, EACAIVCq.CIV, and EACAULCq.CUL are respectively copied to EACOEM.CEi, EACOIVMq.CIV, and EACOULMq.CUL) */

#define R_ETHA_EACC_CC0                           (1 << 0)  /* CC0 */

#define R_ETHA_EACC_CC1                           (1 << 1)  /* CC1 */

#define R_ETHA_EACC_CC2                           (1 << 2)  /* CC2 */

#define R_ETHA_EACC_CC3                           (1 << 3)  /* CC3 */

#define R_ETHA_EACC_CC4                           (1 << 4)  /* CC4 */

#define R_ETHA_EACC_CC5                           (1 << 5)  /* CC5 */

#define R_ETHA_EACC_CC6                           (1 << 6)  /* CC6 */

#define R_ETHA_EACC_CC7                           (1 << 7)  /* CC7 */

/* EACAIVC Register bit definitions */
#define R_ETHA_EACAIVC_CIV_SHIFT                  (0)  /* Credit Increment Value */
#define R_ETHA_EACAIVC_CIV_MASK                   0xfffff

/* EACAULCQ Register bit definitions */
#define R_ETHA_EACAULCQ_CUL_SHIFT                 (0)  /* Credit Upper Limit */
#define R_ETHA_EACAULCQ_CUL_MASK                  0x7fffffff

/* EACOEM Register bit definitions */
#define R_ETHA_EACOEM_CE0                         (1 << 0)  /* CBS Enable n (n = 0 to 7) */

#define R_ETHA_EACOEM_CE1                         (1 << 1)  /* CBS Enable n (n = 0 to 7) */

#define R_ETHA_EACOEM_CE2                         (1 << 2)  /* CBS Enable n (n = 0 to 7) */

#define R_ETHA_EACOEM_CE3                         (1 << 3)  /* CBS Enable n (n = 0 to 7) */

#define R_ETHA_EACOEM_CE4                         (1 << 4)  /* CBS Enable n (n = 0 to 7) */

#define R_ETHA_EACOEM_CE5                         (1 << 5)  /* CBS Enable n (n = 0 to 7) */

#define R_ETHA_EACOEM_CE6                         (1 << 6)  /* CBS Enable n (n = 0 to 7) */

#define R_ETHA_EACOEM_CE7                         (1 << 7)  /* CBS Enable n (n = 0 to 7) */

/* EACOIVM Register bit definitions */
#define R_ETHA_EACOIVM_CIV_SHIFT                  (0)  /* Credit Increment Value */
#define R_ETHA_EACOIVM_CIV_MASK                   0xfffff

/* EACOULM Register bit definitions */
#define R_ETHA_EACOULM_CUL_SHIFT                  (0)  /* Credit Upper Limit */
#define R_ETHA_EACOULM_CUL_MASK                   0x7fffffff

/* EACGSM Register bit definitions */
#define R_ETHA_EACGSM_CGS0                        (1 << 0)  /* CBS Gate State n (n = 0 to 7) */

#define R_ETHA_EACGSM_CGS1                        (1 << 1)  /* CBS Gate State n (n = 0 to 7) */

#define R_ETHA_EACGSM_CGS2                        (1 << 2)  /* CBS Gate State n (n = 0 to 7) */

#define R_ETHA_EACGSM_CGS3                        (1 << 3)  /* CBS Gate State n (n = 0 to 7) */

#define R_ETHA_EACGSM_CGS4                        (1 << 4)  /* CBS Gate State n (n = 0 to 7) */

#define R_ETHA_EACGSM_CGS5                        (1 << 5)  /* CBS Gate State n (n = 0 to 7) */

#define R_ETHA_EACGSM_CGS6                        (1 << 6)  /* CBS Gate State n (n = 0 to 7) */

#define R_ETHA_EACGSM_CGS7                        (1 << 7)  /* CBS Gate State n (n = 0 to 7) */

/* EATASC Register bit definitions */
#define R_ETHA_EATASC_TASE                        (1 << 0)  /* TAS Enable */

#define R_ETHA_EATASC_TASCC                       (1 << 1)  /* TAS Configuration Change */

#define R_ETHA_EATASC_TASCI                       (1 << 2)  /* TAS Configuration Impossible */

#define R_ETHA_EATASC_TASTS                       (1 << 8)  /* TAS Timer Select */

#define R_ETHA_EATASC_TASCA_SHIFT                 (16)  /* TAS Configuration Address */
#define R_ETHA_EATASC_TASCA_MASK                  0xff0000

/* EATASIGSC Register bit definitions */
#define R_ETHA_EATASIGSC_TASIGS0                  (1 << 0)  /* TAS Initial Gate State n (n = 0 to 7) */

#define R_ETHA_EATASIGSC_TASIGS1                  (1 << 1)  /* TAS Initial Gate State n (n = 0 to 7) */

#define R_ETHA_EATASIGSC_TASIGS2                  (1 << 2)  /* TAS Initial Gate State n (n = 0 to 7) */

#define R_ETHA_EATASIGSC_TASIGS3                  (1 << 3)  /* TAS Initial Gate State n (n = 0 to 7) */

#define R_ETHA_EATASIGSC_TASIGS4                  (1 << 4)  /* TAS Initial Gate State n (n = 0 to 7) */

#define R_ETHA_EATASIGSC_TASIGS5                  (1 << 5)  /* TAS Initial Gate State n (n = 0 to 7) */

#define R_ETHA_EATASIGSC_TASIGS6                  (1 << 6)  /* TAS Initial Gate State n (n = 0 to 7) */

#define R_ETHA_EATASIGSC_TASIGS7                  (1 << 7)  /* TAS Initial Gate State n (n = 0 to 7) */

#define R_ETHA_EATASIGSC_TASCTIGS                 (1 << 8)  /* TAS Cut-Through Initial Gate State */

/* EATASENC Register bit definitions */
#define R_ETHA_EATASENC_TASAEN_SHIFT              (0)  /* TAS Admin Entry Number */
#define R_ETHA_EATASENC_TASAEN_MASK               0x1ff

/* EATASCTENC Register bit definitions */
#define R_ETHA_EATASCTENC_TASCTAEN_SHIFT          (0)  /* TAS Admin Cut-Through Entry Number */
#define R_ETHA_EATASCTENC_TASCTAEN_MASK           0x1ff

/* EATASENM Register bit definitions */
#define R_ETHA_EATASENM_TASOEN_SHIFT              (0)  /* TAS Oper Entry Number */
#define R_ETHA_EATASENM_TASOEN_MASK               0x1ff

/* EATASCTENM Register bit definitions */
#define R_ETHA_EATASCTENM_TASCTOEN_SHIFT          (0)  /* TAS Cut-Through Oper Entry Number */
#define R_ETHA_EATASCTENM_TASCTOEN_MASK           0x1ff

/* EATASCSTC0 Register bit definitions */
#define R_ETHA_EATASCSTC0_TASACSTP0_SHIFT         (0)  /* TAS Admin Cycle Start Time Part 0 */
#define R_ETHA_EATASCSTC0_TASACSTP0_MASK          0xffffffff

/* EATASCSTC1 Register bit definitions */
#define R_ETHA_EATASCSTC1_TASACSTP1_SHIFT         (0)  /* TAS Admin Cycle Start Time Part 1 */
#define R_ETHA_EATASCSTC1_TASACSTP1_MASK          0xffffffff

/* EATASCSTM0 Register bit definitions */
#define R_ETHA_EATASCSTM0_TASOCSTP0_SHIFT         (0)  /* TAS Oper Cycle Start Time Part 0 */
#define R_ETHA_EATASCSTM0_TASOCSTP0_MASK          0xffffffff

/* EATASCSTM1 Register bit definitions */
#define R_ETHA_EATASCSTM1_TASOCSTP1_SHIFT         (0)  /* TAS Oper Cycle Start Time Part 1 */
#define R_ETHA_EATASCSTM1_TASOCSTP1_MASK          0xffffffff

/* EATASCTC Register bit definitions */
#define R_ETHA_EATASCTC_TASACT_SHIFT              (0)  /* TAS Admin Cycle Time */
#define R_ETHA_EATASCTC_TASACT_MASK               0xffffffff

/* EATASCTM Register bit definitions */
#define R_ETHA_EATASCTM_TASOCT_SHIFT              (0)  /* TAS Oper Cycle Time */
#define R_ETHA_EATASCTM_TASOCT_MASK               0xffffffff

/* EATASGL0 Register bit definitions */
#define R_ETHA_EATASGL0_TASGAL_SHIFT              (0)  /* TAS Gate Address Learn */
#define R_ETHA_EATASGL0_TASGAL_MASK               0xff

/* EATASGL1 Register bit definitions */
#define R_ETHA_EATASGL1_TASGTL_SHIFT              (0)  /* TAS Gate Time Learn */
#define R_ETHA_EATASGL1_TASGTL_MASK               0xfffffff

#define R_ETHA_EATASGL1_TASGSL                    (1 << 28)  /* TAS Gate State Learn */

/* EATASGLR Register bit definitions */
#define R_ETHA_EATASGLR_GL                        (1 << 31)  /* Gate Learn */

/* EATASGR Register bit definitions */
#define R_ETHA_EATASGR_TASGAR_SHIFT               (0)  /* TAS Gate Address Read */
#define R_ETHA_EATASGR_TASGAR_MASK                0xff

/* EATASGRR Register bit definitions */
#define R_ETHA_EATASGRR_TASGTR_SHIFT              (0)  /* TAS Gate Time Read */
#define R_ETHA_EATASGRR_TASGTR_MASK               0xfffffff

#define R_ETHA_EATASGRR_TASGSR                    (1 << 28)  /* TAS Gate State Read */

#define R_ETHA_EATASGRR_GR                        (1 << 31)  /* Gate Read */

#define R_ETHA_EATASGRR_TASREF                    (1 << 29)  /* TASREF */

/* EATASHCC Register bit definitions */
#define R_ETHA_EATASHCC_TASJ_SHIFT                (0)  /* TAS Jitter */
#define R_ETHA_EATASHCC_TASJ_MASK                 0xffff

/* EATASRIRM Register bit definitions */
#define R_ETHA_EATASRIRM_TASRIOG                  (1 << 0)  /* TAS RAM Initialization Ongoing */

#define R_ETHA_EATASRIRM_TASRR                    (1 << 1)  /* TAS RAM Ready */

/* EATASSM Register bit definitions */
#define R_ETHA_EATASSM_TASGS0                     (1 << 0)  /* TAS Gate n State (n = 0 to 7) */

#define R_ETHA_EATASSM_TASGS1                     (1 << 1)  /* TAS Gate n State (n = 0 to 7) */

#define R_ETHA_EATASSM_TASGS2                     (1 << 2)  /* TAS Gate n State (n = 0 to 7) */

#define R_ETHA_EATASSM_TASGS3                     (1 << 3)  /* TAS Gate n State (n = 0 to 7) */

#define R_ETHA_EATASSM_TASGS4                     (1 << 4)  /* TAS Gate n State (n = 0 to 7) */

#define R_ETHA_EATASSM_TASGS5                     (1 << 5)  /* TAS Gate n State (n = 0 to 7) */

#define R_ETHA_EATASSM_TASGS6                     (1 << 6)  /* TAS Gate n State (n = 0 to 7) */

#define R_ETHA_EATASSM_TASGS7                     (1 << 7)  /* TAS Gate n State (n = 0 to 7) */

#define R_ETHA_EATASSM_TASCTGS                    (1 << 8)  /* TAS Cut-Through Gate State */

#define R_ETHA_EATASSM_TASSO                      (1 << 16)  /* TAS Scheduler Ongoing */

/* EAUSMFSECN Register bit definitions */
#define R_ETHA_EAUSMFSECN_USMFSEN_SHIFT           (0)  /* Under Minimum Frame Size Error Number */
#define R_ETHA_EAUSMFSECN_USMFSEN_MASK            0xffff

/* EATFECN Register bit definitions */
#define R_ETHA_EATFECN_TFEN_SHIFT                 (0)  /* TAG Filtering Error Number */
#define R_ETHA_EATFECN_TFEN_MASK                  0xffff

/* EAFSECN Register bit definitions */
#define R_ETHA_EAFSECN_FSEN_SHIFT                 (0)  /* Frame Size Error Number */
#define R_ETHA_EAFSECN_FSEN_MASK                  0xffff

/* EADQOECN Register bit definitions */
#define R_ETHA_EADQOECN_DQOEN_SHIFT               (0)  /* Descriptor Queue Overflow Error Number */
#define R_ETHA_EADQOECN_DQOEN_MASK                0xffff

/* EADQSECN Register bit definitions */
#define R_ETHA_EADQSECN_DQSEN_SHIFT               (0)  /* Descriptor Queue Security Error Number */
#define R_ETHA_EADQSECN_DQSEN_MASK                0xffff

/* EAEIS0 Register bit definitions */
#define R_ETHA_EAEIS0_USMFSES                     (1 << 5)  /* Under Switch Minimum Frame Size Error Status Flag */

#define R_ETHA_EAEIS0_TFES                        (1 << 6)  /* TAG Filtering Error Status Flag */

#define R_ETHA_EAEIS0_FSES7 TO FSES0_SHIFT        (8)  /* Frame Size Error Status Flag n (n = 0 to 7) */
#define R_ETHA_EAEIS0_FSES7 TO FSES0_MASK         0xff00

#define R_ETHA_EAEIS0_DECCES                      (1 << 0)  /* DECCES */

#define R_ETHA_EAEIS0_TECCES                      (1 << 1)  /* TECCES */

#define R_ETHA_EAEIS0_PECCES                      (1 << 2)  /* PECCES */

#define R_ETHA_EAEIS0_DSECCES                     (1 << 3)  /* DSECCES */

#define R_ETHA_EAEIS0_L23UECCES                   (1 << 4)  /* L23UECCES */

#define R_ETHA_EAEIS0_FSES0                       (1 << 8)  /* FSES0 */

#define R_ETHA_EAEIS0_FSES1                       (1 << 9)  /* FSES1 */

#define R_ETHA_EAEIS0_FSES2                       (1 << 10)  /* FSES2 */

#define R_ETHA_EAEIS0_FSES3                       (1 << 11)  /* FSES3 */

#define R_ETHA_EAEIS0_FSES4                       (1 << 12)  /* FSES4 */

#define R_ETHA_EAEIS0_FSES5                       (1 << 13)  /* FSES5 */

#define R_ETHA_EAEIS0_FSES6                       (1 << 14)  /* FSES6 */

#define R_ETHA_EAEIS0_FSES7                       (1 << 15)  /* FSES7 */

#define R_ETHA_EAEIS0_TASGEES0                    (1 << 16)  /* TASGEES0 */

#define R_ETHA_EAEIS0_TASGEES1                    (1 << 17)  /* TASGEES1 */

#define R_ETHA_EAEIS0_TASGEES2                    (1 << 18)  /* TASGEES2 */

#define R_ETHA_EAEIS0_TASGEES3                    (1 << 19)  /* TASGEES3 */

#define R_ETHA_EAEIS0_TASGEES4                    (1 << 20)  /* TASGEES4 */

#define R_ETHA_EAEIS0_TASGEES5                    (1 << 21)  /* TASGEES5 */

#define R_ETHA_EAEIS0_TASGEES6                    (1 << 22)  /* TASGEES6 */

#define R_ETHA_EAEIS0_TASGEES7                    (1 << 23)  /* TASGEES7 */

#define R_ETHA_EAEIS0_TASCTGEES                   (1 << 24)  /* TASCTGEES */

/* EAEIE0 Register bit definitions */
#define R_ETHA_EAEIE0_USMFSEE                     (1 << 5)  /* Under Switch Minimum Frame Size Error Enable */

#define R_ETHA_EAEIE0_TFEE                        (1 << 6)  /* TAG Filtering Error Enable */

#define R_ETHA_EAEIE0_FSEE7 TO FSEE0_SHIFT        (8)  /* Frame Size Error Enable n (n = 0 to 7) */
#define R_ETHA_EAEIE0_FSEE7 TO FSEE0_MASK         0xff00
#  define R_ETHA_EAEIE0_FSEE7 TO FSEE0_0                  (0 << R_ETHA_EAEIE0_FSEE7 TO FSEE0_SHIFT)  /* Interrupt disabled for descriptor queue i */
#  define R_ETHA_EAEIE0_FSEE7 TO FSEE0_1                  (1 << R_ETHA_EAEIE0_FSEE7 TO FSEE0_SHIFT)  /* Interrupt enabled for descriptor queue i */

#define R_ETHA_EAEIE0_DECCEE                      (1 << 0)  /* DECCEE */

#define R_ETHA_EAEIE0_TECCEE                      (1 << 1)  /* TECCEE */

#define R_ETHA_EAEIE0_PECCEE                      (1 << 2)  /* PECCEE */

#define R_ETHA_EAEIE0_DSECCEE                     (1 << 3)  /* DSECCEE */

#define R_ETHA_EAEIE0_L23UECCEE                   (1 << 4)  /* L23UECCEE */

#define R_ETHA_EAEIE0_FSEE0                       (1 << 8)  /* FSEE0 */

#define R_ETHA_EAEIE0_FSEE1                       (1 << 9)  /* FSEE1 */

#define R_ETHA_EAEIE0_FSEE2                       (1 << 10)  /* FSEE2 */

#define R_ETHA_EAEIE0_FSEE3                       (1 << 11)  /* FSEE3 */

#define R_ETHA_EAEIE0_FSEE4                       (1 << 12)  /* FSEE4 */

#define R_ETHA_EAEIE0_FSEE5                       (1 << 13)  /* FSEE5 */

#define R_ETHA_EAEIE0_FSEE6                       (1 << 14)  /* FSEE6 */

#define R_ETHA_EAEIE0_FSEE7                       (1 << 15)  /* FSEE7 */

#define R_ETHA_EAEIE0_TASGEEE0                    (1 << 16)  /* TASGEEE0 */

#define R_ETHA_EAEIE0_TASGEEE1                    (1 << 17)  /* TASGEEE1 */

#define R_ETHA_EAEIE0_TASGEEE2                    (1 << 18)  /* TASGEEE2 */

#define R_ETHA_EAEIE0_TASGEEE3                    (1 << 19)  /* TASGEEE3 */

#define R_ETHA_EAEIE0_TASGEEE4                    (1 << 20)  /* TASGEEE4 */

#define R_ETHA_EAEIE0_TASGEEE5                    (1 << 21)  /* TASGEEE5 */

#define R_ETHA_EAEIE0_TASGEEE6                    (1 << 22)  /* TASGEEE6 */

#define R_ETHA_EAEIE0_TASGEEE7                    (1 << 23)  /* TASGEEE7 */

#define R_ETHA_EAEIE0_TASCTGEEE                   (1 << 24)  /* TASCTGEEE */

/* EAEID0 Register bit definitions */
#define R_ETHA_EAEID0_USMFSED                     (1 << 5)  /* Under Switch Minimum Frame Size Error Disable */

#define R_ETHA_EAEID0_TFED                        (1 << 6)  /* TAG Filtering Error Disable */

#define R_ETHA_EAEID0_FSED7 TO FSED0_SHIFT        (8)  /* Frame Size Error Disable n (n = 0 to 7) */
#define R_ETHA_EAEID0_FSED7 TO FSED0_MASK         0xff00

#define R_ETHA_EAEID0_DECCED                      (1 << 0)  /* DECCED */

#define R_ETHA_EAEID0_TECCED                      (1 << 1)  /* TECCED */

#define R_ETHA_EAEID0_PECCED                      (1 << 2)  /* PECCED */

#define R_ETHA_EAEID0_DSECCED                     (1 << 3)  /* DSECCED */

#define R_ETHA_EAEID0_L23UECCED                   (1 << 4)  /* L23UECCED */

#define R_ETHA_EAEID0_FSED0                       (1 << 8)  /* FSED0 */

#define R_ETHA_EAEID0_FSED1                       (1 << 9)  /* FSED1 */

#define R_ETHA_EAEID0_FSED2                       (1 << 10)  /* FSED2 */

#define R_ETHA_EAEID0_FSED3                       (1 << 11)  /* FSED3 */

#define R_ETHA_EAEID0_FSED4                       (1 << 12)  /* FSED4 */

#define R_ETHA_EAEID0_FSED5                       (1 << 13)  /* FSED5 */

#define R_ETHA_EAEID0_FSED6                       (1 << 14)  /* FSED6 */

#define R_ETHA_EAEID0_FSED7                       (1 << 15)  /* FSED7 */

#define R_ETHA_EAEID0_TASGEED0                    (1 << 16)  /* TASGEED0 */

#define R_ETHA_EAEID0_TASGEED1                    (1 << 17)  /* TASGEED1 */

#define R_ETHA_EAEID0_TASGEED2                    (1 << 18)  /* TASGEED2 */

#define R_ETHA_EAEID0_TASGEED3                    (1 << 19)  /* TASGEED3 */

#define R_ETHA_EAEID0_TASGEED4                    (1 << 20)  /* TASGEED4 */

#define R_ETHA_EAEID0_TASGEED5                    (1 << 21)  /* TASGEED5 */

#define R_ETHA_EAEID0_TASGEED6                    (1 << 22)  /* TASGEED6 */

#define R_ETHA_EAEID0_TASGEED7                    (1 << 23)  /* TASGEED7 */

#define R_ETHA_EAEID0_TASCTGEED                   (1 << 24)  /* TASCTGEED */

/* EAEIS1 Register bit definitions */
#define R_ETHA_EAEIS1_CULES7 TO CULES0_SHIFT      (0)  /* CBS n Upper Limit Error Status Flag (n = 0 to 7) */
#define R_ETHA_EAEIS1_CULES7 TO CULES0_MASK       0xff

#define R_ETHA_EAEIS1_TASGES7 TO TASGES0_SHIFT    (16)  /* TAS Gate n Error Status Flag (n = 0 to 7) */
#define R_ETHA_EAEIS1_TASGES7 TO TASGES0_MASK     0xff0000

#define R_ETHA_EAEIS1_TASCTGES                    (1 << 24)  /* TAS Cut-Through Gate Error Status Flag */

#define R_ETHA_EAEIS1_CULES0                      (1 << 0)  /* CULES0 */

#define R_ETHA_EAEIS1_CULES1                      (1 << 1)  /* CULES1 */

#define R_ETHA_EAEIS1_CULES2                      (1 << 2)  /* CULES2 */

#define R_ETHA_EAEIS1_CULES3                      (1 << 3)  /* CULES3 */

#define R_ETHA_EAEIS1_CULES4                      (1 << 4)  /* CULES4 */

#define R_ETHA_EAEIS1_CULES5                      (1 << 5)  /* CULES5 */

#define R_ETHA_EAEIS1_CULES6                      (1 << 6)  /* CULES6 */

#define R_ETHA_EAEIS1_CULES7                      (1 << 7)  /* CULES7 */

#define R_ETHA_EAEIS1_TASGES0                     (1 << 16)  /* TASGES0 */

#define R_ETHA_EAEIS1_TASGES1                     (1 << 17)  /* TASGES1 */

#define R_ETHA_EAEIS1_TASGES2                     (1 << 18)  /* TASGES2 */

#define R_ETHA_EAEIS1_TASGES3                     (1 << 19)  /* TASGES3 */

#define R_ETHA_EAEIS1_TASGES4                     (1 << 20)  /* TASGES4 */

#define R_ETHA_EAEIS1_TASGES5                     (1 << 21)  /* TASGES5 */

#define R_ETHA_EAEIS1_TASGES6                     (1 << 22)  /* TASGES6 */

#define R_ETHA_EAEIS1_TASGES7                     (1 << 23)  /* TASGES7 */

/* EAEIE1 Register bit definitions */
#define R_ETHA_EAEIE1_CULEE7 TO CULEE0_SHIFT      (0)  /* CBS n Upper Limit Error Enable (n = 0 to 7) */
#define R_ETHA_EAEIE1_CULEE7 TO CULEE0_MASK       0xff
#  define R_ETHA_EAEIE1_CULEE7 TO CULEE0_0                (0 << R_ETHA_EAEIE1_CULEE7 TO CULEE0_SHIFT)  /* Interrupt disabled for descriptor queue i */
#  define R_ETHA_EAEIE1_CULEE7 TO CULEE0_1                (1 << R_ETHA_EAEIE1_CULEE7 TO CULEE0_SHIFT)  /* Interrupt enabled for descriptor queue i */

#define R_ETHA_EAEIE1_TASGEE7 TO TASGEE0_SHIFT    (16)  /* TAS Gate n Error Enable (n = 0 to 7) */
#define R_ETHA_EAEIE1_TASGEE7 TO TASGEE0_MASK     0xff0000
#  define R_ETHA_EAEIE1_TASGEE7 TO TASGEE0_0              (0 << R_ETHA_EAEIE1_TASGEE7 TO TASGEE0_SHIFT)  /* Interrupt disabled for descriptor queue i */
#  define R_ETHA_EAEIE1_TASGEE7 TO TASGEE0_1              (1 << R_ETHA_EAEIE1_TASGEE7 TO TASGEE0_SHIFT)  /* Interrupt enabled for descriptor queue i */

#define R_ETHA_EAEIE1_TASCTGEE                    (1 << 24)  /* TAS Cut-through Gate Error Enable */

#define R_ETHA_EAEIE1_CULEE0                      (1 << 0)  /* CULEE0 */

#define R_ETHA_EAEIE1_CULEE1                      (1 << 1)  /* CULEE1 */

#define R_ETHA_EAEIE1_CULEE2                      (1 << 2)  /* CULEE2 */

#define R_ETHA_EAEIE1_CULEE3                      (1 << 3)  /* CULEE3 */

#define R_ETHA_EAEIE1_CULEE4                      (1 << 4)  /* CULEE4 */

#define R_ETHA_EAEIE1_CULEE5                      (1 << 5)  /* CULEE5 */

#define R_ETHA_EAEIE1_CULEE6                      (1 << 6)  /* CULEE6 */

#define R_ETHA_EAEIE1_CULEE7                      (1 << 7)  /* CULEE7 */

#define R_ETHA_EAEIE1_TASGEE0                     (1 << 16)  /* TASGEE0 */

#define R_ETHA_EAEIE1_TASGEE1                     (1 << 17)  /* TASGEE1 */

#define R_ETHA_EAEIE1_TASGEE2                     (1 << 18)  /* TASGEE2 */

#define R_ETHA_EAEIE1_TASGEE3                     (1 << 19)  /* TASGEE3 */

#define R_ETHA_EAEIE1_TASGEE4                     (1 << 20)  /* TASGEE4 */

#define R_ETHA_EAEIE1_TASGEE5                     (1 << 21)  /* TASGEE5 */

#define R_ETHA_EAEIE1_TASGEE6                     (1 << 22)  /* TASGEE6 */

#define R_ETHA_EAEIE1_TASGEE7                     (1 << 23)  /* TASGEE7 */

/* EAEID1 Register bit definitions */
#define R_ETHA_EAEID1_CULED7 TO CULED0_SHIFT      (0)  /* CBS n Upper Limit Error Disable (n = 0 to 7) */
#define R_ETHA_EAEID1_CULED7 TO CULED0_MASK       0xff

#define R_ETHA_EAEID1_TASGED7 TO TASGED0_SHIFT    (16)  /* TAS Gate n Error Disable (n = 0 to 7) */
#define R_ETHA_EAEID1_TASGED7 TO TASGED0_MASK     0xff0000

#define R_ETHA_EAEID1_TASCTGED                    (1 << 24)  /* TAS Cut-through Gate Error Disable */

#define R_ETHA_EAEID1_CULED0                      (1 << 0)  /* CULED0 */

#define R_ETHA_EAEID1_CULED1                      (1 << 1)  /* CULED1 */

#define R_ETHA_EAEID1_CULED2                      (1 << 2)  /* CULED2 */

#define R_ETHA_EAEID1_CULED3                      (1 << 3)  /* CULED3 */

#define R_ETHA_EAEID1_CULED4                      (1 << 4)  /* CULED4 */

#define R_ETHA_EAEID1_CULED5                      (1 << 5)  /* CULED5 */

#define R_ETHA_EAEID1_CULED6                      (1 << 6)  /* CULED6 */

#define R_ETHA_EAEID1_CULED7                      (1 << 7)  /* CULED7 */

#define R_ETHA_EAEID1_TASGED0                     (1 << 16)  /* TASGED0 */

#define R_ETHA_EAEID1_TASGED1                     (1 << 17)  /* TASGED1 */

#define R_ETHA_EAEID1_TASGED2                     (1 << 18)  /* TASGED2 */

#define R_ETHA_EAEID1_TASGED3                     (1 << 19)  /* TASGED3 */

#define R_ETHA_EAEID1_TASGED4                     (1 << 20)  /* TASGED4 */

#define R_ETHA_EAEID1_TASGED5                     (1 << 21)  /* TASGED5 */

#define R_ETHA_EAEID1_TASGED6                     (1 << 22)  /* TASGED6 */

#define R_ETHA_EAEID1_TASGED7                     (1 << 23)  /* TASGED7 */

/* EAEIS2 Register bit definitions */
#define R_ETHA_EAEIS2_DQOES7 TO DQOES0_SHIFT      (0)  /* Descriptor Queue n Overflow Error Status Flag (n = 0 to 7) */
#define R_ETHA_EAEIS2_DQOES7 TO DQOES0_MASK       0xff

#define R_ETHA_EAEIS2_CTDQOES                     (1 << 8)  /* Cut-Through Descriptor Queue Overflow Error Status Flag */

#define R_ETHA_EAEIS2_DQSES7 TO DQSES0_SHIFT      (16)  /* Descriptor Queue n Security Error Status Flag (n = 0 to 7) */
#define R_ETHA_EAEIS2_DQSES7 TO DQSES0_MASK       0xff0000

#define R_ETHA_EAEIS2_DQOES0                      (1 << 0)  /* DQOES0 */

#define R_ETHA_EAEIS2_DQOES1                      (1 << 1)  /* DQOES1 */

#define R_ETHA_EAEIS2_DQOES2                      (1 << 2)  /* DQOES2 */

#define R_ETHA_EAEIS2_DQOES3                      (1 << 3)  /* DQOES3 */

#define R_ETHA_EAEIS2_DQOES4                      (1 << 4)  /* DQOES4 */

#define R_ETHA_EAEIS2_DQOES5                      (1 << 5)  /* DQOES5 */

#define R_ETHA_EAEIS2_DQOES6                      (1 << 6)  /* DQOES6 */

#define R_ETHA_EAEIS2_DQOES7                      (1 << 7)  /* DQOES7 */

#define R_ETHA_EAEIS2_DQSES0                      (1 << 16)  /* DQSES0 */

#define R_ETHA_EAEIS2_DQSES1                      (1 << 17)  /* DQSES1 */

#define R_ETHA_EAEIS2_DQSES2                      (1 << 18)  /* DQSES2 */

#define R_ETHA_EAEIS2_DQSES3                      (1 << 19)  /* DQSES3 */

#define R_ETHA_EAEIS2_DQSES4                      (1 << 20)  /* DQSES4 */

#define R_ETHA_EAEIS2_DQSES5                      (1 << 21)  /* DQSES5 */

#define R_ETHA_EAEIS2_DQSES6                      (1 << 22)  /* DQSES6 */

#define R_ETHA_EAEIS2_DQSES7                      (1 << 23)  /* DQSES7 */

/* EAEIE2 Register bit definitions */
#define R_ETHA_EAEIE2_DQOEE7 TO DQOEE0_SHIFT      (0)  /* Descriptor Queue n Overflow Error Enable (n = 0 to 7) */
#define R_ETHA_EAEIE2_DQOEE7 TO DQOEE0_MASK       0xff
#  define R_ETHA_EAEIE2_DQOEE7 TO DQOEE0_0                (0 << R_ETHA_EAEIE2_DQOEE7 TO DQOEE0_SHIFT)  /* Interrupt disabled for descriptor queue i */
#  define R_ETHA_EAEIE2_DQOEE7 TO DQOEE0_1                (1 << R_ETHA_EAEIE2_DQOEE7 TO DQOEE0_SHIFT)  /* Interrupt enabled for descriptor queue i */

#define R_ETHA_EAEIE2_CTDQOEE                     (1 << 8)  /* Cut-Through Descriptor Queue Overflow Error Enable */

#define R_ETHA_EAEIE2_DQSEE7 TO DQSEE0_SHIFT      (16)  /* Descriptor Queue n Security Error Enable (n = 0 to 7) */
#define R_ETHA_EAEIE2_DQSEE7 TO DQSEE0_MASK       0xff0000
#  define R_ETHA_EAEIE2_DQSEE7 TO DQSEE0_0                (0 << R_ETHA_EAEIE2_DQSEE7 TO DQSEE0_SHIFT)  /* Interrupt disabled for descriptor queue i */
#  define R_ETHA_EAEIE2_DQSEE7 TO DQSEE0_1                (1 << R_ETHA_EAEIE2_DQSEE7 TO DQSEE0_SHIFT)  /* Interrupt enabled for descriptor queue i */

#define R_ETHA_EAEIE2_DQOEE0                      (1 << 0)  /* DQOEE0 */

#define R_ETHA_EAEIE2_DQOEE1                      (1 << 1)  /* DQOEE1 */

#define R_ETHA_EAEIE2_DQOEE2                      (1 << 2)  /* DQOEE2 */

#define R_ETHA_EAEIE2_DQOEE3                      (1 << 3)  /* DQOEE3 */

#define R_ETHA_EAEIE2_DQOEE4                      (1 << 4)  /* DQOEE4 */

#define R_ETHA_EAEIE2_DQOEE5                      (1 << 5)  /* DQOEE5 */

#define R_ETHA_EAEIE2_DQOEE6                      (1 << 6)  /* DQOEE6 */

#define R_ETHA_EAEIE2_DQOEE7                      (1 << 7)  /* DQOEE7 */

#define R_ETHA_EAEIE2_DQSEE0                      (1 << 16)  /* DQSEE0 */

#define R_ETHA_EAEIE2_DQSEE1                      (1 << 17)  /* DQSEE1 */

#define R_ETHA_EAEIE2_DQSEE2                      (1 << 18)  /* DQSEE2 */

#define R_ETHA_EAEIE2_DQSEE3                      (1 << 19)  /* DQSEE3 */

#define R_ETHA_EAEIE2_DQSEE4                      (1 << 20)  /* DQSEE4 */

#define R_ETHA_EAEIE2_DQSEE5                      (1 << 21)  /* DQSEE5 */

#define R_ETHA_EAEIE2_DQSEE6                      (1 << 22)  /* DQSEE6 */

#define R_ETHA_EAEIE2_DQSEE7                      (1 << 23)  /* DQSEE7 */

/* EAEID2 Register bit definitions */
#define R_ETHA_EAEID2_DQOED7 TO DQOED0_SHIFT      (0)  /* Descriptor Queue n Overflow Error Disable (n = 0 to 7) */
#define R_ETHA_EAEID2_DQOED7 TO DQOED0_MASK       0xff

#define R_ETHA_EAEID2_CTDQOED                     (1 << 8)  /* Cut-Through Descriptor Queue Overflow Error Disable */

#define R_ETHA_EAEID2_DQSED7 TO DQSED0_SHIFT      (16)  /* Descriptor Queue n Security Error Disable (n = 0 to 7) */
#define R_ETHA_EAEID2_DQSED7 TO DQSED0_MASK       0xff0000

#define R_ETHA_EAEID2_DQOED0                      (1 << 0)  /* DQOED0 */

#define R_ETHA_EAEID2_DQOED1                      (1 << 1)  /* DQOED1 */

#define R_ETHA_EAEID2_DQOED2                      (1 << 2)  /* DQOED2 */

#define R_ETHA_EAEID2_DQOED3                      (1 << 3)  /* DQOED3 */

#define R_ETHA_EAEID2_DQOED4                      (1 << 4)  /* DQOED4 */

#define R_ETHA_EAEID2_DQOED5                      (1 << 5)  /* DQOED5 */

#define R_ETHA_EAEID2_DQOED6                      (1 << 6)  /* DQOED6 */

#define R_ETHA_EAEID2_DQOED7                      (1 << 7)  /* DQOED7 */

#define R_ETHA_EAEID2_DQSED0                      (1 << 16)  /* DQSED0 */

#define R_ETHA_EAEID2_DQSED1                      (1 << 17)  /* DQSED1 */

#define R_ETHA_EAEID2_DQSED2                      (1 << 18)  /* DQSED2 */

#define R_ETHA_EAEID2_DQSED3                      (1 << 19)  /* DQSED3 */

#define R_ETHA_EAEID2_DQSED4                      (1 << 20)  /* DQSED4 */

#define R_ETHA_EAEID2_DQSED5                      (1 << 21)  /* DQSED5 */

#define R_ETHA_EAEID2_DQSED6                      (1 << 22)  /* DQSED6 */

#define R_ETHA_EAEID2_DQSED7                      (1 << 23)  /* DQSED7 */


/* Maximum number of channels */

#define ETHA_MAX_CHANNELS    8

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ETHA_H */
