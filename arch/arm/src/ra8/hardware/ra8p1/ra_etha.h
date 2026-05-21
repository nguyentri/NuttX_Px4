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
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_ETHA_BASE           0x403ca000
#else
#define R_ETHA_BASE           0x503ca000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_ETHA_CH_STRIDE    0x00002000
#define R_ETHA_CH_BASE(ch)   (R_ETHA_BASE + ((uint32_t)(ch) * R_ETHA_CH_STRIDE))

/* ETHA Register Offsets */

#define R_ETHA_EAMC_OFFSET                        0x00000000  /* Ethernet Agent Mode Configuration Register (EAMC) */
#define R_ETHA_EAMS_OFFSET                        0x00000004  /* Ethernet Agent Mode Status Register (EAMS) */
#define R_ETHA_EAIRC_OFFSET                       0x00000010  /* Ethernet Agent IPV Remapping Configuration Register [802.1Q] (EAIRC) */
#define R_ETHA_EATDQSC_OFFSET                     0x00000014  /* Ethernet Agent TX Descriptor Queue Security Configuration Register (EATDQSC) */
#define R_ETHA_EATDQC_OFFSET                      0x00000018  /* Ethernet Agent TX Descriptor Queue Configuration Register (EATDQC) */
#define R_ETHA_EATDQAC_OFFSET                     0x0000001c  /* Ethernet Agent TX Descriptor Queue Arbitration Configuration Register (EATDQAC) */
#define R_ETHA_EATPEC_OFFSET                      0x00000020  /* Ethernet Agent TX Pre-Emption Configuration Register (EATPEC) */
#define R_ETHA_EATMFSC0_OFFSET                    0x00000040  /* Ethernet Agent Transmission Maximum Frame Size Configuration Register q (EATMFSCq) (q = 0 to 7) */
#define R_ETHA_EATMFSC1_OFFSET                    0x00000044  /* Ethernet Agent Transmission Maximum Frame Size Configuration Register q (EATMFSCq) (q = 0 to 7) */
#define R_ETHA_EATMFSC2_OFFSET                    0x00000048  /* Ethernet Agent Transmission Maximum Frame Size Configuration Register q (EATMFSCq) (q = 0 to 7) */
#define R_ETHA_EATMFSC3_OFFSET                    0x0000004c  /* Ethernet Agent Transmission Maximum Frame Size Configuration Register q (EATMFSCq) (q = 0 to 7) */
#define R_ETHA_EATMFSC4_OFFSET                    0x00000050  /* Ethernet Agent Transmission Maximum Frame Size Configuration Register q (EATMFSCq) (q = 0 to 7) */
#define R_ETHA_EATMFSC5_OFFSET                    0x00000054  /* Ethernet Agent Transmission Maximum Frame Size Configuration Register q (EATMFSCq) (q = 0 to 7) */
#define R_ETHA_EATMFSC6_OFFSET                    0x00000058  /* Ethernet Agent Transmission Maximum Frame Size Configuration Register q (EATMFSCq) (q = 0 to 7) */
#define R_ETHA_EATMFSC7_OFFSET                    0x0000005c  /* Ethernet Agent Transmission Maximum Frame Size Configuration Register q (EATMFSCq) (q = 0 to 7) */
#define R_ETHA_EATDQDC0_OFFSET                    0x00000060  /* Ethernet Agent Transmission Descriptor Queue Depth Configuration Register q (EATDQDCq) (q = 0 to 7) */
#define R_ETHA_EATDQDC1_OFFSET                    0x00000064  /* Ethernet Agent Transmission Descriptor Queue Depth Configuration Register q (EATDQDCq) (q = 0 to 7) */
#define R_ETHA_EATDQDC2_OFFSET                    0x00000068  /* Ethernet Agent Transmission Descriptor Queue Depth Configuration Register q (EATDQDCq) (q = 0 to 7) */
#define R_ETHA_EATDQDC3_OFFSET                    0x0000006c  /* Ethernet Agent Transmission Descriptor Queue Depth Configuration Register q (EATDQDCq) (q = 0 to 7) */
#define R_ETHA_EATDQDC4_OFFSET                    0x00000070  /* Ethernet Agent Transmission Descriptor Queue Depth Configuration Register q (EATDQDCq) (q = 0 to 7) */
#define R_ETHA_EATDQDC5_OFFSET                    0x00000074  /* Ethernet Agent Transmission Descriptor Queue Depth Configuration Register q (EATDQDCq) (q = 0 to 7) */
#define R_ETHA_EATDQDC6_OFFSET                    0x00000078  /* Ethernet Agent Transmission Descriptor Queue Depth Configuration Register q (EATDQDCq) (q = 0 to 7) */
#define R_ETHA_EATDQDC7_OFFSET                    0x0000007c  /* Ethernet Agent Transmission Descriptor Queue Depth Configuration Register q (EATDQDCq) (q = 0 to 7) */
#define R_ETHA_EATDQM0_OFFSET                     0x00000080  /* Ethernet Agent Transmission Descriptor Queue q Monitoring Register (EATDQMq) (q = 0 to 7) */
#define R_ETHA_EATDQM1_OFFSET                     0x00000084  /* Ethernet Agent Transmission Descriptor Queue q Monitoring Register (EATDQMq) (q = 0 to 7) */
#define R_ETHA_EATDQM2_OFFSET                     0x00000088  /* Ethernet Agent Transmission Descriptor Queue q Monitoring Register (EATDQMq) (q = 0 to 7) */
#define R_ETHA_EATDQM3_OFFSET                     0x0000008c  /* Ethernet Agent Transmission Descriptor Queue q Monitoring Register (EATDQMq) (q = 0 to 7) */
#define R_ETHA_EATDQM4_OFFSET                     0x00000090  /* Ethernet Agent Transmission Descriptor Queue q Monitoring Register (EATDQMq) (q = 0 to 7) */
#define R_ETHA_EATDQM5_OFFSET                     0x00000094  /* Ethernet Agent Transmission Descriptor Queue q Monitoring Register (EATDQMq) (q = 0 to 7) */
#define R_ETHA_EATDQM6_OFFSET                     0x00000098  /* Ethernet Agent Transmission Descriptor Queue q Monitoring Register (EATDQMq) (q = 0 to 7) */
#define R_ETHA_EATDQM7_OFFSET                     0x0000009c  /* Ethernet Agent Transmission Descriptor Queue q Monitoring Register (EATDQMq) (q = 0 to 7) */
#define R_ETHA_EATDQMLM0_OFFSET                   0x000000a0  /* Ethernet Agent Transmission Descriptor Queue q Max Level Monitoring Register (EATDQMLMq) (q = 0 to 7) */
#define R_ETHA_EATDQMLM1_OFFSET                   0x000000a4  /* Ethernet Agent Transmission Descriptor Queue q Max Level Monitoring Register (EATDQMLMq) (q = 0 to 7) */
#define R_ETHA_EATDQMLM2_OFFSET                   0x000000a8  /* Ethernet Agent Transmission Descriptor Queue q Max Level Monitoring Register (EATDQMLMq) (q = 0 to 7) */
#define R_ETHA_EATDQMLM3_OFFSET                   0x000000ac  /* Ethernet Agent Transmission Descriptor Queue q Max Level Monitoring Register (EATDQMLMq) (q = 0 to 7) */
#define R_ETHA_EATDQMLM4_OFFSET                   0x000000b0  /* Ethernet Agent Transmission Descriptor Queue q Max Level Monitoring Register (EATDQMLMq) (q = 0 to 7) */
#define R_ETHA_EATDQMLM5_OFFSET                   0x000000b4  /* Ethernet Agent Transmission Descriptor Queue q Max Level Monitoring Register (EATDQMLMq) (q = 0 to 7) */
#define R_ETHA_EATDQMLM6_OFFSET                   0x000000b8  /* Ethernet Agent Transmission Descriptor Queue q Max Level Monitoring Register (EATDQMLMq) (q = 0 to 7) */
#define R_ETHA_EATDQMLM7_OFFSET                   0x000000bc  /* Ethernet Agent Transmission Descriptor Queue q Max Level Monitoring Register (EATDQMLMq) (q = 0 to 7) */
#define R_ETHA_EACTQC_OFFSET                      0x00000100  /* Ethernet Agent Cut-Through Queue Configuration Register (EACTQC) */
#define R_ETHA_EACTDQDC_OFFSET                    0x00000104  /* Ethernet Agent Cut-Through Descriptor Queue Depth Configuration Register (EACTDQDC) */
#define R_ETHA_EACTDQM_OFFSET                     0x00000108  /* Ethernet Agent Cut-Through Descriptor Queue Monitoring Register (EACTDQM) */
#define R_ETHA_EACTDQMLM_OFFSET                   0x0000010c  /* Ethernet Agent Cut-Through Descriptor Queue Max Level Monitoring Register (EACTDQMLM) */
#define R_ETHA_EAVCC_OFFSET                       0x00000130  /* Ethernet Agent VLAN Control Configuration Register (EAVCC) */
#define R_ETHA_EAVTC_OFFSET                       0x00000134  /* Ethernet Agent VLAN TAG Configuration Register (EAVTC) */
#define R_ETHA_EARTFC_OFFSET                      0x00000138  /* Ethernet Agent Reception TAG Filtering Configuration Register (EARTFC) */
#define R_ETHA_EACAEC_OFFSET                      0x00000200  /* Ethernet Agent CBS Admin Enable Configuration Register (EACAEC) */
#define R_ETHA_EACC_OFFSET                        0x00000204  /* Ethernet Agent CBS Configuration Register (EACC) */
#define R_ETHA_EACAIVC0_OFFSET                    0x00000220  /* Ethernet Agent CBS Admin Increment Value Configuration Register q (EACAIVCq) (q = 0 to 7) */
#define R_ETHA_EACAIVC1_OFFSET                    0x00000224  /* Ethernet Agent CBS Admin Increment Value Configuration Register q (EACAIVCq) (q = 0 to 7) */
#define R_ETHA_EACAIVC2_OFFSET                    0x00000228  /* Ethernet Agent CBS Admin Increment Value Configuration Register q (EACAIVCq) (q = 0 to 7) */
#define R_ETHA_EACAIVC3_OFFSET                    0x0000022c  /* Ethernet Agent CBS Admin Increment Value Configuration Register q (EACAIVCq) (q = 0 to 7) */
#define R_ETHA_EACAIVC4_OFFSET                    0x00000230  /* Ethernet Agent CBS Admin Increment Value Configuration Register q (EACAIVCq) (q = 0 to 7) */
#define R_ETHA_EACAIVC5_OFFSET                    0x00000234  /* Ethernet Agent CBS Admin Increment Value Configuration Register q (EACAIVCq) (q = 0 to 7) */
#define R_ETHA_EACAIVC6_OFFSET                    0x00000238  /* Ethernet Agent CBS Admin Increment Value Configuration Register q (EACAIVCq) (q = 0 to 7) */
#define R_ETHA_EACAIVC7_OFFSET                    0x0000023c  /* Ethernet Agent CBS Admin Increment Value Configuration Register q (EACAIVCq) (q = 0 to 7) */
#define R_ETHA_EACAULC0_OFFSET                    0x00000240  /* Ethernet Agent CBS Admin Upper Limit Configuration Register q (EACAULCq) (q = 0 to 7) */
#define R_ETHA_EACAULC1_OFFSET                    0x00000244  /* Ethernet Agent CBS Admin Upper Limit Configuration Register q (EACAULCq) (q = 0 to 7) */
#define R_ETHA_EACAULC2_OFFSET                    0x00000248  /* Ethernet Agent CBS Admin Upper Limit Configuration Register q (EACAULCq) (q = 0 to 7) */
#define R_ETHA_EACAULC3_OFFSET                    0x0000024c  /* Ethernet Agent CBS Admin Upper Limit Configuration Register q (EACAULCq) (q = 0 to 7) */
#define R_ETHA_EACAULC4_OFFSET                    0x00000250  /* Ethernet Agent CBS Admin Upper Limit Configuration Register q (EACAULCq) (q = 0 to 7) */
#define R_ETHA_EACAULC5_OFFSET                    0x00000254  /* Ethernet Agent CBS Admin Upper Limit Configuration Register q (EACAULCq) (q = 0 to 7) */
#define R_ETHA_EACAULC6_OFFSET                    0x00000258  /* Ethernet Agent CBS Admin Upper Limit Configuration Register q (EACAULCq) (q = 0 to 7) */
#define R_ETHA_EACAULC7_OFFSET                    0x0000025c  /* Ethernet Agent CBS Admin Upper Limit Configuration Register q (EACAULCq) (q = 0 to 7) */
#define R_ETHA_EACOEM_OFFSET                      0x00000260  /* Ethernet Agent CBS Oper Enable Monitoring Register (EACOEM) */
#define R_ETHA_EACOIVM0_OFFSET                    0x00000280  /* Ethernet Agent CBS Oper Increment Value Monitoring Register q (EACOIVMq) (q = 0 to 7) */
#define R_ETHA_EACOIVM1_OFFSET                    0x00000284  /* Ethernet Agent CBS Oper Increment Value Monitoring Register q (EACOIVMq) (q = 0 to 7) */
#define R_ETHA_EACOIVM2_OFFSET                    0x00000288  /* Ethernet Agent CBS Oper Increment Value Monitoring Register q (EACOIVMq) (q = 0 to 7) */
#define R_ETHA_EACOIVM3_OFFSET                    0x0000028c  /* Ethernet Agent CBS Oper Increment Value Monitoring Register q (EACOIVMq) (q = 0 to 7) */
#define R_ETHA_EACOIVM4_OFFSET                    0x00000290  /* Ethernet Agent CBS Oper Increment Value Monitoring Register q (EACOIVMq) (q = 0 to 7) */
#define R_ETHA_EACOIVM5_OFFSET                    0x00000294  /* Ethernet Agent CBS Oper Increment Value Monitoring Register q (EACOIVMq) (q = 0 to 7) */
#define R_ETHA_EACOIVM6_OFFSET                    0x00000298  /* Ethernet Agent CBS Oper Increment Value Monitoring Register q (EACOIVMq) (q = 0 to 7) */
#define R_ETHA_EACOIVM7_OFFSET                    0x0000029c  /* Ethernet Agent CBS Oper Increment Value Monitoring Register q (EACOIVMq) (q = 0 to 7) */
#define R_ETHA_EACOULM0_OFFSET                    0x000002a0  /* Ethernet Agent CBS Oper Upper Limit Monitoring Register q (EACOULMq) (q = 0 to 7) */
#define R_ETHA_EACOULM1_OFFSET                    0x000002a4  /* Ethernet Agent CBS Oper Upper Limit Monitoring Register q (EACOULMq) (q = 0 to 7) */
#define R_ETHA_EACOULM2_OFFSET                    0x000002a8  /* Ethernet Agent CBS Oper Upper Limit Monitoring Register q (EACOULMq) (q = 0 to 7) */
#define R_ETHA_EACOULM3_OFFSET                    0x000002ac  /* Ethernet Agent CBS Oper Upper Limit Monitoring Register q (EACOULMq) (q = 0 to 7) */
#define R_ETHA_EACOULM4_OFFSET                    0x000002b0  /* Ethernet Agent CBS Oper Upper Limit Monitoring Register q (EACOULMq) (q = 0 to 7) */
#define R_ETHA_EACOULM5_OFFSET                    0x000002b4  /* Ethernet Agent CBS Oper Upper Limit Monitoring Register q (EACOULMq) (q = 0 to 7) */
#define R_ETHA_EACOULM6_OFFSET                    0x000002b8  /* Ethernet Agent CBS Oper Upper Limit Monitoring Register q (EACOULMq) (q = 0 to 7) */
#define R_ETHA_EACOULM7_OFFSET                    0x000002bc  /* Ethernet Agent CBS Oper Upper Limit Monitoring Register q (EACOULMq) (q = 0 to 7) */
#define R_ETHA_EACGSM_OFFSET                      0x000002c0  /* Ethernet Agent CBS Gate State Monitoring Register (EACGSM) */
#define R_ETHA_EATASC_OFFSET                      0x00000300  /* Ethernet Agent TAS Configuration Register (EATASC) */
#define R_ETHA_EATASIGSC_OFFSET                   0x00000304  /* Ethernet Agent TAS Initial Gate State Configuration Register (EATASIGSC) */
#define R_ETHA_EATASENC0_OFFSET                   0x00000320  /* Ethernet Agent TAS Entry Number Configuration Register i (EATASENCi) (i = 0 to 8) */
#define R_ETHA_EATASENC1_OFFSET                   0x00000324  /* Ethernet Agent TAS Entry Number Configuration Register i (EATASENCi) (i = 0 to 8) */
#define R_ETHA_EATASENC2_OFFSET                   0x00000328  /* Ethernet Agent TAS Entry Number Configuration Register i (EATASENCi) (i = 0 to 8) */
#define R_ETHA_EATASENC3_OFFSET                   0x0000032c  /* Ethernet Agent TAS Entry Number Configuration Register i (EATASENCi) (i = 0 to 8) */
#define R_ETHA_EATASENC4_OFFSET                   0x00000330  /* Ethernet Agent TAS Entry Number Configuration Register i (EATASENCi) (i = 0 to 8) */
#define R_ETHA_EATASENC5_OFFSET                   0x00000334  /* Ethernet Agent TAS Entry Number Configuration Register i (EATASENCi) (i = 0 to 8) */
#define R_ETHA_EATASENC6_OFFSET                   0x00000338  /* Ethernet Agent TAS Entry Number Configuration Register i (EATASENCi) (i = 0 to 8) */
#define R_ETHA_EATASENC7_OFFSET                   0x0000033c  /* Ethernet Agent TAS Entry Number Configuration Register i (EATASENCi) (i = 0 to 8) */
#define R_ETHA_EATASCTENC_OFFSET                  0x00000340  /* Ethernet Agent TAS Cut-Through Entry Number Configuration Register (EATASCTENC) */
#define R_ETHA_EATASENM0_OFFSET                   0x00000360  /* Ethernet Agent TAS Entry Number Monitoring Register i (EATASENMi) (i = 0 to 8) */
#define R_ETHA_EATASENM1_OFFSET                   0x00000364  /* Ethernet Agent TAS Entry Number Monitoring Register i (EATASENMi) (i = 0 to 8) */
#define R_ETHA_EATASENM2_OFFSET                   0x00000368  /* Ethernet Agent TAS Entry Number Monitoring Register i (EATASENMi) (i = 0 to 8) */
#define R_ETHA_EATASENM3_OFFSET                   0x0000036c  /* Ethernet Agent TAS Entry Number Monitoring Register i (EATASENMi) (i = 0 to 8) */
#define R_ETHA_EATASENM4_OFFSET                   0x00000370  /* Ethernet Agent TAS Entry Number Monitoring Register i (EATASENMi) (i = 0 to 8) */
#define R_ETHA_EATASENM5_OFFSET                   0x00000374  /* Ethernet Agent TAS Entry Number Monitoring Register i (EATASENMi) (i = 0 to 8) */
#define R_ETHA_EATASENM6_OFFSET                   0x00000378  /* Ethernet Agent TAS Entry Number Monitoring Register i (EATASENMi) (i = 0 to 8) */
#define R_ETHA_EATASENM7_OFFSET                   0x0000037c  /* Ethernet Agent TAS Entry Number Monitoring Register i (EATASENMi) (i = 0 to 8) */
#define R_ETHA_EATASCTENM_OFFSET                  0x00000380  /* Ethernet Agent TAS Cut-Through Entry Number Monitoring Register (EATASCTENM) */
#define R_ETHA_EATASCSTC0_OFFSET                  0x000003a0  /* Ethernet Agent TAS Cycle Start Time Configuration Register 0 (EATASCSTC0) */
#define R_ETHA_EATASCSTC1_OFFSET                  0x000003a4  /* Ethernet Agent TAS Cycle Start Time Configuration Register 1 (EATASCSTC1) */
#define R_ETHA_EATASCSTM0_OFFSET                  0x000003a8  /* Ethernet Agent TAS Cycle Start Time Monitoring Register 0 (EATASCSTM0) */
#define R_ETHA_EATASCSTM1_OFFSET                  0x000003ac  /* Ethernet Agent TAS Cycle Start Time Monitoring Register 1 (EATASCSTM1) */
#define R_ETHA_EATASCTC_OFFSET                    0x000003b0  /* Ethernet Agent TAS Cycle Time Configuration Register (EATASCTC) */
#define R_ETHA_EATASCTM_OFFSET                    0x000003b4  /* Ethernet Agent TAS Cycle Time Monitoring Register (EATASCTM) */
#define R_ETHA_EATASGL0_OFFSET                    0x000003c0  /* Ethernet Agent TAS Gate Learn Register 0 (EATASGL0) */
#define R_ETHA_EATASGL1_OFFSET                    0x000003c4  /* Ethernet Agent TAS Gate Learn Register 1 (EATASGL1) */
#define R_ETHA_EATASGLR_OFFSET                    0x000003c8  /* Ethernet Agent TAS Gate Learn Result Register (EATASGLR) */
#define R_ETHA_EATASGR_OFFSET                     0x000003d0  /* Ethernet Agent TAS Gate Read Register (EATASGR) */
#define R_ETHA_EATASGRR_OFFSET                    0x000003d4  /* Ethernet Agent TAS Gate Read Result Register (EATASGRR) */
#define R_ETHA_EATASHCC_OFFSET                    0x000003e0  /* Ethernet Agent TAS Hardware Calibration Configuration Register (EATASHCC) */
#define R_ETHA_EATASRIRM_OFFSET                   0x000003e4  /* Ethernet Agent TAS RAM Initialization Register Monitoring Register (EATASRIRM) */
#define R_ETHA_EATASSM_OFFSET                     0x000003e8  /* Ethernet Agent TAS Status Monitoring Register (EATASSM) */
#define R_ETHA_EAUSMFSECN_OFFSET                  0x00000400  /* Ethernet Agent Switch Minimum Frame Size Error Counter Register (EAUSMFSECN) */
#define R_ETHA_EATFECN_OFFSET                     0x00000404  /* Ethernet Agent TAG Filtering Error Counter Register (EATFECN) */
#define R_ETHA_EAFSECN_OFFSET                     0x00000408  /* Ethernet Agent Frame Size Error Counter Register (EAFSECN) */
#define R_ETHA_EADQOECN_OFFSET                    0x0000040c  /* Ethernet Agent Descriptor Queue Overflow Error Counter Register (EADQOECN) */
#define R_ETHA_EADQSECN_OFFSET                    0x00000410  /* Ethernet Agent Descriptor Queue Security Error Counter Register (EADQSECN) */
#define R_ETHA_EAEIS0_OFFSET                      0x00000500  /* Ethernet Agent Error Interrupt Status Register 0 (EAEIS0) */
#define R_ETHA_EAEIE0_OFFSET                      0x00000504  /* Ethernet Agent Error Interrupt Enable Register 0 (EAEIE0) */
#define R_ETHA_EAEID0_OFFSET                      0x00000508  /* Ethernet Agent Error Interrupt Disable Register 0 (EAEID0) */
#define R_ETHA_EAEIS1_OFFSET                      0x00000510  /* Ethernet Agent Error Interrupt Status Register 1 (EAEIS1) */
#define R_ETHA_EAEIE1_OFFSET                      0x00000514  /* Ethernet Agent Error Interrupt Enable Register 1 (EAEIE1) */
#define R_ETHA_EAEID1_OFFSET                      0x00000518  /* Ethernet Agent Error Interrupt Disable Register 1 (EAEID1) */
#define R_ETHA_EAEIS2_OFFSET                      0x00000520  /* Ethernet Agent Error Interrupt Status Register 2 (EAEIS2) */
#define R_ETHA_EAEIE2_OFFSET                      0x00000524  /* Ethernet Agent Error Interrupt Enable Register 2 (EAEIE2) */
#define R_ETHA_EAEID2_OFFSET                      0x00000528  /* Ethernet Agent Error Interrupt Disable Register 2 (EAEID2) */
#define R_ETHA_EASCR_OFFSET                       0x00000580  /* Ethernet Agent Security Configuration Register (EASCR) */

/* ETHA Register Addresses */

#define R_ETHA_EAMC(n)                            (R_ETHA_CH_BASE(n) + R_ETHA_EAMC_OFFSET)
#define R_ETHA_EAMS(n)                            (R_ETHA_CH_BASE(n) + R_ETHA_EAMS_OFFSET)
#define R_ETHA_EAIRC(n)                           (R_ETHA_CH_BASE(n) + R_ETHA_EAIRC_OFFSET)
#define R_ETHA_EATDQSC(n)                         (R_ETHA_CH_BASE(n) + R_ETHA_EATDQSC_OFFSET)
#define R_ETHA_EATDQC(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EATDQC_OFFSET)
#define R_ETHA_EATDQAC(n)                         (R_ETHA_CH_BASE(n) + R_ETHA_EATDQAC_OFFSET)
#define R_ETHA_EATPEC(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EATPEC_OFFSET)
#define R_ETHA_EATMFSC0(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EATMFSC0_OFFSET)
#define R_ETHA_EATMFSC1(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EATMFSC1_OFFSET)
#define R_ETHA_EATMFSC2(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EATMFSC2_OFFSET)
#define R_ETHA_EATMFSC3(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EATMFSC3_OFFSET)
#define R_ETHA_EATMFSC4(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EATMFSC4_OFFSET)
#define R_ETHA_EATMFSC5(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EATMFSC5_OFFSET)
#define R_ETHA_EATMFSC6(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EATMFSC6_OFFSET)
#define R_ETHA_EATMFSC7(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EATMFSC7_OFFSET)
#define R_ETHA_EATDQDC0(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EATDQDC0_OFFSET)
#define R_ETHA_EATDQDC1(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EATDQDC1_OFFSET)
#define R_ETHA_EATDQDC2(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EATDQDC2_OFFSET)
#define R_ETHA_EATDQDC3(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EATDQDC3_OFFSET)
#define R_ETHA_EATDQDC4(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EATDQDC4_OFFSET)
#define R_ETHA_EATDQDC5(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EATDQDC5_OFFSET)
#define R_ETHA_EATDQDC6(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EATDQDC6_OFFSET)
#define R_ETHA_EATDQDC7(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EATDQDC7_OFFSET)
#define R_ETHA_EATDQM0(n)                         (R_ETHA_CH_BASE(n) + R_ETHA_EATDQM0_OFFSET)
#define R_ETHA_EATDQM1(n)                         (R_ETHA_CH_BASE(n) + R_ETHA_EATDQM1_OFFSET)
#define R_ETHA_EATDQM2(n)                         (R_ETHA_CH_BASE(n) + R_ETHA_EATDQM2_OFFSET)
#define R_ETHA_EATDQM3(n)                         (R_ETHA_CH_BASE(n) + R_ETHA_EATDQM3_OFFSET)
#define R_ETHA_EATDQM4(n)                         (R_ETHA_CH_BASE(n) + R_ETHA_EATDQM4_OFFSET)
#define R_ETHA_EATDQM5(n)                         (R_ETHA_CH_BASE(n) + R_ETHA_EATDQM5_OFFSET)
#define R_ETHA_EATDQM6(n)                         (R_ETHA_CH_BASE(n) + R_ETHA_EATDQM6_OFFSET)
#define R_ETHA_EATDQM7(n)                         (R_ETHA_CH_BASE(n) + R_ETHA_EATDQM7_OFFSET)
#define R_ETHA_EATDQMLM0(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATDQMLM0_OFFSET)
#define R_ETHA_EATDQMLM1(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATDQMLM1_OFFSET)
#define R_ETHA_EATDQMLM2(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATDQMLM2_OFFSET)
#define R_ETHA_EATDQMLM3(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATDQMLM3_OFFSET)
#define R_ETHA_EATDQMLM4(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATDQMLM4_OFFSET)
#define R_ETHA_EATDQMLM5(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATDQMLM5_OFFSET)
#define R_ETHA_EATDQMLM6(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATDQMLM6_OFFSET)
#define R_ETHA_EATDQMLM7(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATDQMLM7_OFFSET)
#define R_ETHA_EACTQC(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EACTQC_OFFSET)
#define R_ETHA_EACTDQDC(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACTDQDC_OFFSET)
#define R_ETHA_EACTDQM(n)                         (R_ETHA_CH_BASE(n) + R_ETHA_EACTDQM_OFFSET)
#define R_ETHA_EACTDQMLM(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EACTDQMLM_OFFSET)
#define R_ETHA_EAVCC(n)                           (R_ETHA_CH_BASE(n) + R_ETHA_EAVCC_OFFSET)
#define R_ETHA_EAVTC(n)                           (R_ETHA_CH_BASE(n) + R_ETHA_EAVTC_OFFSET)
#define R_ETHA_EARTFC(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EARTFC_OFFSET)
#define R_ETHA_EACAEC(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EACAEC_OFFSET)
#define R_ETHA_EACC(n)                            (R_ETHA_CH_BASE(n) + R_ETHA_EACC_OFFSET)
#define R_ETHA_EACAIVC0(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACAIVC0_OFFSET)
#define R_ETHA_EACAIVC1(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACAIVC1_OFFSET)
#define R_ETHA_EACAIVC2(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACAIVC2_OFFSET)
#define R_ETHA_EACAIVC3(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACAIVC3_OFFSET)
#define R_ETHA_EACAIVC4(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACAIVC4_OFFSET)
#define R_ETHA_EACAIVC5(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACAIVC5_OFFSET)
#define R_ETHA_EACAIVC6(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACAIVC6_OFFSET)
#define R_ETHA_EACAIVC7(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACAIVC7_OFFSET)
#define R_ETHA_EACAULC0(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACAULC0_OFFSET)
#define R_ETHA_EACAULC1(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACAULC1_OFFSET)
#define R_ETHA_EACAULC2(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACAULC2_OFFSET)
#define R_ETHA_EACAULC3(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACAULC3_OFFSET)
#define R_ETHA_EACAULC4(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACAULC4_OFFSET)
#define R_ETHA_EACAULC5(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACAULC5_OFFSET)
#define R_ETHA_EACAULC6(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACAULC6_OFFSET)
#define R_ETHA_EACAULC7(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACAULC7_OFFSET)
#define R_ETHA_EACOEM(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EACOEM_OFFSET)
#define R_ETHA_EACOIVM0(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACOIVM0_OFFSET)
#define R_ETHA_EACOIVM1(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACOIVM1_OFFSET)
#define R_ETHA_EACOIVM2(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACOIVM2_OFFSET)
#define R_ETHA_EACOIVM3(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACOIVM3_OFFSET)
#define R_ETHA_EACOIVM4(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACOIVM4_OFFSET)
#define R_ETHA_EACOIVM5(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACOIVM5_OFFSET)
#define R_ETHA_EACOIVM6(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACOIVM6_OFFSET)
#define R_ETHA_EACOIVM7(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACOIVM7_OFFSET)
#define R_ETHA_EACOULM0(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACOULM0_OFFSET)
#define R_ETHA_EACOULM1(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACOULM1_OFFSET)
#define R_ETHA_EACOULM2(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACOULM2_OFFSET)
#define R_ETHA_EACOULM3(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACOULM3_OFFSET)
#define R_ETHA_EACOULM4(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACOULM4_OFFSET)
#define R_ETHA_EACOULM5(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACOULM5_OFFSET)
#define R_ETHA_EACOULM6(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACOULM6_OFFSET)
#define R_ETHA_EACOULM7(n)                        (R_ETHA_CH_BASE(n) + R_ETHA_EACOULM7_OFFSET)
#define R_ETHA_EACGSM(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EACGSM_OFFSET)
#define R_ETHA_EATASC(n)                          (R_ETHA_CH_BASE(n) + R_ETHA_EATASC_OFFSET)
#define R_ETHA_EATASIGSC(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATASIGSC_OFFSET)
#define R_ETHA_EATASENC0(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATASENC0_OFFSET)
#define R_ETHA_EATASENC1(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATASENC1_OFFSET)
#define R_ETHA_EATASENC2(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATASENC2_OFFSET)
#define R_ETHA_EATASENC3(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATASENC3_OFFSET)
#define R_ETHA_EATASENC4(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATASENC4_OFFSET)
#define R_ETHA_EATASENC5(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATASENC5_OFFSET)
#define R_ETHA_EATASENC6(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATASENC6_OFFSET)
#define R_ETHA_EATASENC7(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATASENC7_OFFSET)
#define R_ETHA_EATASCTENC(n)                      (R_ETHA_CH_BASE(n) + R_ETHA_EATASCTENC_OFFSET)
#define R_ETHA_EATASENM0(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATASENM0_OFFSET)
#define R_ETHA_EATASENM1(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATASENM1_OFFSET)
#define R_ETHA_EATASENM2(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATASENM2_OFFSET)
#define R_ETHA_EATASENM3(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATASENM3_OFFSET)
#define R_ETHA_EATASENM4(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATASENM4_OFFSET)
#define R_ETHA_EATASENM5(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATASENM5_OFFSET)
#define R_ETHA_EATASENM6(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATASENM6_OFFSET)
#define R_ETHA_EATASENM7(n)                       (R_ETHA_CH_BASE(n) + R_ETHA_EATASENM7_OFFSET)
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
#define R_ETHA_EASCR(n)                           (R_ETHA_CH_BASE(n) + R_ETHA_EASCR_OFFSET)

/* Register bit definitions */
/* EAMC Register bit definitions */
#define R_ETHA_EAMC_OPC_SHIFT                     (0)  /*  */
#define R_ETHA_EAMC_OPC_MASK                      0x3

/* EAMS Register bit definitions */
#define R_ETHA_EAMS_OPS_SHIFT                     (0)  /*  */
#define R_ETHA_EAMS_OPS_MASK                      0x3

/* EAIRC Register bit definitions */
#define R_ETHA_EAIRC_IPVR0_SHIFT                  (0)  /*  */
#define R_ETHA_EAIRC_IPVR0_MASK                   0x7

#define R_ETHA_EAIRC_IPVR1_SHIFT                  (4)  /*  */
#define R_ETHA_EAIRC_IPVR1_MASK                   0x70

#define R_ETHA_EAIRC_IPVR2_SHIFT                  (8)  /*  */
#define R_ETHA_EAIRC_IPVR2_MASK                   0x700

#define R_ETHA_EAIRC_IPVR3_SHIFT                  (12)  /*  */
#define R_ETHA_EAIRC_IPVR3_MASK                   0x7000

#define R_ETHA_EAIRC_IPVR4_SHIFT                  (16)  /*  */
#define R_ETHA_EAIRC_IPVR4_MASK                   0x70000

#define R_ETHA_EAIRC_IPVR5_SHIFT                  (20)  /*  */
#define R_ETHA_EAIRC_IPVR5_MASK                   0x700000

#define R_ETHA_EAIRC_IPVR6_SHIFT                  (24)  /*  */
#define R_ETHA_EAIRC_IPVR6_MASK                   0x7000000

#define R_ETHA_EAIRC_IPVR7_SHIFT                  (28)  /*  */
#define R_ETHA_EAIRC_IPVR7_MASK                   0x70000000

/* EATDQSC Register bit definitions */
#define R_ETHA_EATDQSC_TDQSL0                     (1 << 0)  /*  */

#define R_ETHA_EATDQSC_TDQSL1                     (1 << 1)  /*  */

#define R_ETHA_EATDQSC_TDQSL2                     (1 << 2)  /*  */

#define R_ETHA_EATDQSC_TDQSL3                     (1 << 3)  /*  */

#define R_ETHA_EATDQSC_TDQSL4                     (1 << 4)  /*  */

#define R_ETHA_EATDQSC_TDQSL5                     (1 << 5)  /*  */

#define R_ETHA_EATDQSC_TDQSL6                     (1 << 6)  /*  */

#define R_ETHA_EATDQSC_TDQSL7                     (1 << 7)  /*  */

/* EATDQC Register bit definitions */
#define R_ETHA_EATDQC_TDQD0                       (1 << 0)  /*  */

#define R_ETHA_EATDQC_TDQD1                       (1 << 1)  /*  */

#define R_ETHA_EATDQC_TDQD2                       (1 << 2)  /*  */

#define R_ETHA_EATDQC_TDQD3                       (1 << 3)  /*  */

#define R_ETHA_EATDQC_TDQD4                       (1 << 4)  /*  */

#define R_ETHA_EATDQC_TDQD5                       (1 << 5)  /*  */

#define R_ETHA_EATDQC_TDQD6                       (1 << 6)  /*  */

#define R_ETHA_EATDQC_TDQD7                       (1 << 7)  /*  */

#define R_ETHA_EATDQC_TCTDQD                      (1 << 8)  /*  */

#define R_ETHA_EATDQC_TDQP0                       (1 << 16)  /*  */

#define R_ETHA_EATDQC_TDQP1                       (1 << 17)  /*  */

#define R_ETHA_EATDQC_TDQP2                       (1 << 18)  /*  */

#define R_ETHA_EATDQC_TDQP3                       (1 << 19)  /*  */

#define R_ETHA_EATDQC_TDQP4                       (1 << 20)  /*  */

#define R_ETHA_EATDQC_TDQP5                       (1 << 21)  /*  */

#define R_ETHA_EATDQC_TDQP6                       (1 << 22)  /*  */

#define R_ETHA_EATDQC_TDQP7                       (1 << 23)  /*  */

/* EATDQAC Register bit definitions */
#define R_ETHA_EATDQAC_TDQA0_SHIFT                (0)  /*  */
#define R_ETHA_EATDQAC_TDQA0_MASK                 0xf

#define R_ETHA_EATDQAC_TDQA1_SHIFT                (4)  /*  */
#define R_ETHA_EATDQAC_TDQA1_MASK                 0xf0

#define R_ETHA_EATDQAC_TDQA2_SHIFT                (8)  /*  */
#define R_ETHA_EATDQAC_TDQA2_MASK                 0xf00

#define R_ETHA_EATDQAC_TDQA3_SHIFT                (12)  /*  */
#define R_ETHA_EATDQAC_TDQA3_MASK                 0xf000

#define R_ETHA_EATDQAC_TDQA4_SHIFT                (16)  /*  */
#define R_ETHA_EATDQAC_TDQA4_MASK                 0xf0000

#define R_ETHA_EATDQAC_TDQA5_SHIFT                (20)  /*  */
#define R_ETHA_EATDQAC_TDQA5_MASK                 0xf00000

#define R_ETHA_EATDQAC_TDQA6_SHIFT                (24)  /*  */
#define R_ETHA_EATDQAC_TDQA6_MASK                 0xf000000

#define R_ETHA_EATDQAC_TDQA7_SHIFT                (28)  /*  */
#define R_ETHA_EATDQAC_TDQA7_MASK                 0xf0000000

/* EATPEC Register bit definitions */
#define R_ETHA_EATPEC_TTQ0                        (1 << 0)  /*  */

#define R_ETHA_EATPEC_TTQ1                        (1 << 1)  /*  */

#define R_ETHA_EATPEC_TTQ2                        (1 << 2)  /*  */

#define R_ETHA_EATPEC_TTQ3                        (1 << 3)  /*  */

#define R_ETHA_EATPEC_TTQ4                        (1 << 4)  /*  */

#define R_ETHA_EATPEC_TTQ5                        (1 << 5)  /*  */

#define R_ETHA_EATPEC_TTQ6                        (1 << 6)  /*  */

#define R_ETHA_EATPEC_TTQ7                        (1 << 7)  /*  */

#define R_ETHA_EATPEC_TTQ8                        (1 << 8)  /*  */

#define R_ETHA_EATPEC_TTQ9                        (1 << 9)  /*  */

#define R_ETHA_EATPEC_AFS_SHIFT                   (16)  /*  */
#define R_ETHA_EATPEC_AFS_MASK                    0x30000

/* EATMFSC0 Register bit definitions */
#define R_ETHA_EATMFSC0_MFS_SHIFT                 (0)  /*  */
#define R_ETHA_EATMFSC0_MFS_MASK                  0xffff

/* EATMFSC1 Register bit definitions */
#define R_ETHA_EATMFSC1_MFS_SHIFT                 (0)  /*  */
#define R_ETHA_EATMFSC1_MFS_MASK                  0xffff

/* EATMFSC2 Register bit definitions */
#define R_ETHA_EATMFSC2_MFS_SHIFT                 (0)  /*  */
#define R_ETHA_EATMFSC2_MFS_MASK                  0xffff

/* EATMFSC3 Register bit definitions */
#define R_ETHA_EATMFSC3_MFS_SHIFT                 (0)  /*  */
#define R_ETHA_EATMFSC3_MFS_MASK                  0xffff

/* EATMFSC4 Register bit definitions */
#define R_ETHA_EATMFSC4_MFS_SHIFT                 (0)  /*  */
#define R_ETHA_EATMFSC4_MFS_MASK                  0xffff

/* EATMFSC5 Register bit definitions */
#define R_ETHA_EATMFSC5_MFS_SHIFT                 (0)  /*  */
#define R_ETHA_EATMFSC5_MFS_MASK                  0xffff

/* EATMFSC6 Register bit definitions */
#define R_ETHA_EATMFSC6_MFS_SHIFT                 (0)  /*  */
#define R_ETHA_EATMFSC6_MFS_MASK                  0xffff

/* EATMFSC7 Register bit definitions */
#define R_ETHA_EATMFSC7_MFS_SHIFT                 (0)  /*  */
#define R_ETHA_EATMFSC7_MFS_MASK                  0xffff

/* EATDQDC0 Register bit definitions */
#define R_ETHA_EATDQDC0_DQD_SHIFT                 (0)  /*  */
#define R_ETHA_EATDQDC0_DQD_MASK                  0x7ff

/* EATDQDC1 Register bit definitions */
#define R_ETHA_EATDQDC1_DQD_SHIFT                 (0)  /*  */
#define R_ETHA_EATDQDC1_DQD_MASK                  0x7ff

/* EATDQDC2 Register bit definitions */
#define R_ETHA_EATDQDC2_DQD_SHIFT                 (0)  /*  */
#define R_ETHA_EATDQDC2_DQD_MASK                  0x7ff

/* EATDQDC3 Register bit definitions */
#define R_ETHA_EATDQDC3_DQD_SHIFT                 (0)  /*  */
#define R_ETHA_EATDQDC3_DQD_MASK                  0x7ff

/* EATDQDC4 Register bit definitions */
#define R_ETHA_EATDQDC4_DQD_SHIFT                 (0)  /*  */
#define R_ETHA_EATDQDC4_DQD_MASK                  0x7ff

/* EATDQDC5 Register bit definitions */
#define R_ETHA_EATDQDC5_DQD_SHIFT                 (0)  /*  */
#define R_ETHA_EATDQDC5_DQD_MASK                  0x7ff

/* EATDQDC6 Register bit definitions */
#define R_ETHA_EATDQDC6_DQD_SHIFT                 (0)  /*  */
#define R_ETHA_EATDQDC6_DQD_MASK                  0x7ff

/* EATDQDC7 Register bit definitions */
#define R_ETHA_EATDQDC7_DQD_SHIFT                 (0)  /*  */
#define R_ETHA_EATDQDC7_DQD_MASK                  0x7ff

/* EATDQM0 Register bit definitions */
#define R_ETHA_EATDQM0_DNQ_SHIFT                  (0)  /*  */
#define R_ETHA_EATDQM0_DNQ_MASK                   0x7ff

/* EATDQM1 Register bit definitions */
#define R_ETHA_EATDQM1_DNQ_SHIFT                  (0)  /*  */
#define R_ETHA_EATDQM1_DNQ_MASK                   0x7ff

/* EATDQM2 Register bit definitions */
#define R_ETHA_EATDQM2_DNQ_SHIFT                  (0)  /*  */
#define R_ETHA_EATDQM2_DNQ_MASK                   0x7ff

/* EATDQM3 Register bit definitions */
#define R_ETHA_EATDQM3_DNQ_SHIFT                  (0)  /*  */
#define R_ETHA_EATDQM3_DNQ_MASK                   0x7ff

/* EATDQM4 Register bit definitions */
#define R_ETHA_EATDQM4_DNQ_SHIFT                  (0)  /*  */
#define R_ETHA_EATDQM4_DNQ_MASK                   0x7ff

/* EATDQM5 Register bit definitions */
#define R_ETHA_EATDQM5_DNQ_SHIFT                  (0)  /*  */
#define R_ETHA_EATDQM5_DNQ_MASK                   0x7ff

/* EATDQM6 Register bit definitions */
#define R_ETHA_EATDQM6_DNQ_SHIFT                  (0)  /*  */
#define R_ETHA_EATDQM6_DNQ_MASK                   0x7ff

/* EATDQM7 Register bit definitions */
#define R_ETHA_EATDQM7_DNQ_SHIFT                  (0)  /*  */
#define R_ETHA_EATDQM7_DNQ_MASK                   0x7ff

/* EATDQMLM0 Register bit definitions */
#define R_ETHA_EATDQMLM0_DMLQ_SHIFT               (0)  /*  */
#define R_ETHA_EATDQMLM0_DMLQ_MASK                0x7ff

/* EATDQMLM1 Register bit definitions */
#define R_ETHA_EATDQMLM1_DMLQ_SHIFT               (0)  /*  */
#define R_ETHA_EATDQMLM1_DMLQ_MASK                0x7ff

/* EATDQMLM2 Register bit definitions */
#define R_ETHA_EATDQMLM2_DMLQ_SHIFT               (0)  /*  */
#define R_ETHA_EATDQMLM2_DMLQ_MASK                0x7ff

/* EATDQMLM3 Register bit definitions */
#define R_ETHA_EATDQMLM3_DMLQ_SHIFT               (0)  /*  */
#define R_ETHA_EATDQMLM3_DMLQ_MASK                0x7ff

/* EATDQMLM4 Register bit definitions */
#define R_ETHA_EATDQMLM4_DMLQ_SHIFT               (0)  /*  */
#define R_ETHA_EATDQMLM4_DMLQ_MASK                0x7ff

/* EATDQMLM5 Register bit definitions */
#define R_ETHA_EATDQMLM5_DMLQ_SHIFT               (0)  /*  */
#define R_ETHA_EATDQMLM5_DMLQ_MASK                0x7ff

/* EATDQMLM6 Register bit definitions */
#define R_ETHA_EATDQMLM6_DMLQ_SHIFT               (0)  /*  */
#define R_ETHA_EATDQMLM6_DMLQ_MASK                0x7ff

/* EATDQMLM7 Register bit definitions */
#define R_ETHA_EATDQMLM7_DMLQ_SHIFT               (0)  /*  */
#define R_ETHA_EATDQMLM7_DMLQ_MASK                0x7ff

/* EACTQC Register bit definitions */
#define R_ETHA_EACTQC_CTQD_SHIFT                  (0)  /*  */
#define R_ETHA_EACTQC_CTQD_MASK                   0xffff

/* EACTDQDC Register bit definitions */
#define R_ETHA_EACTDQDC_CTDQD_SHIFT               (0)  /*  */
#define R_ETHA_EACTDQDC_CTDQD_MASK                0xf

/* EACTDQM Register bit definitions */
#define R_ETHA_EACTDQM_CTQDN_SHIFT                (0)  /*  */
#define R_ETHA_EACTDQM_CTQDN_MASK                 0x3ff

/* EACTDQMLM Register bit definitions */
#define R_ETHA_EACTDQMLM_CTDMLQ_SHIFT             (0)  /*  */
#define R_ETHA_EACTDQMLM_CTDMLQ_MASK              0xf

/* EAVCC Register bit definitions */
#define R_ETHA_EAVCC_VIM                          (1 << 0)  /*  */

#define R_ETHA_EAVCC_VEM_SHIFT                    (16)  /*  */
#define R_ETHA_EAVCC_VEM_MASK                     0x70000

/* EAVTC Register bit definitions */
#define R_ETHA_EAVTC_CTV_SHIFT                    (0)  /*  */
#define R_ETHA_EAVTC_CTV_MASK                     0xfff

#define R_ETHA_EAVTC_CTP_SHIFT                    (12)  /*  */
#define R_ETHA_EAVTC_CTP_MASK                     0x7000

#define R_ETHA_EAVTC_CTD                          (1 << 15)  /*  */

#define R_ETHA_EAVTC_STV_SHIFT                    (16)  /*  */
#define R_ETHA_EAVTC_STV_MASK                     0xfff0000

#define R_ETHA_EAVTC_STP_SHIFT                    (28)  /*  */
#define R_ETHA_EAVTC_STP_MASK                     0x70000000

#define R_ETHA_EAVTC_STD                          (1 << 31)  /*  */

/* EARTFC Register bit definitions */
#define R_ETHA_EARTFC_NT                          (1 << 0)  /*  */

#define R_ETHA_EARTFC_RT                          (1 << 1)  /*  */

#define R_ETHA_EARTFC_CST                         (1 << 2)  /*  */

#define R_ETHA_EARTFC_CSRT                        (1 << 3)  /*  */

#define R_ETHA_EARTFC_CT                          (1 << 4)  /*  */

#define R_ETHA_EARTFC_CRT                         (1 << 5)  /*  */

#define R_ETHA_EARTFC_SCT                         (1 << 6)  /*  */

#define R_ETHA_EARTFC_SCRT                        (1 << 7)  /*  */

#define R_ETHA_EARTFC_UT                          (1 << 8)  /*  */

/* EACAEC Register bit definitions */
#define R_ETHA_EACAEC_CE0                         (1 << 0)  /*  */

#define R_ETHA_EACAEC_CE1                         (1 << 1)  /*  */

#define R_ETHA_EACAEC_CE2                         (1 << 2)  /*  */

#define R_ETHA_EACAEC_CE3                         (1 << 3)  /*  */

#define R_ETHA_EACAEC_CE4                         (1 << 4)  /*  */

#define R_ETHA_EACAEC_CE5                         (1 << 5)  /*  */

#define R_ETHA_EACAEC_CE6                         (1 << 6)  /*  */

#define R_ETHA_EACAEC_CE7                         (1 << 7)  /*  */

/* EACC Register bit definitions */
#define R_ETHA_EACC_CC0                           (1 << 0)  /*  */

#define R_ETHA_EACC_CC1                           (1 << 1)  /*  */

#define R_ETHA_EACC_CC2                           (1 << 2)  /*  */

#define R_ETHA_EACC_CC3                           (1 << 3)  /*  */

#define R_ETHA_EACC_CC4                           (1 << 4)  /*  */

#define R_ETHA_EACC_CC5                           (1 << 5)  /*  */

#define R_ETHA_EACC_CC6                           (1 << 6)  /*  */

#define R_ETHA_EACC_CC7                           (1 << 7)  /*  */

/* EACAIVC0 Register bit definitions */
#define R_ETHA_EACAIVC0_CIV_SHIFT                 (0)  /*  */
#define R_ETHA_EACAIVC0_CIV_MASK                  0xfffff

/* EACAIVC1 Register bit definitions */
#define R_ETHA_EACAIVC1_CIV_SHIFT                 (0)  /*  */
#define R_ETHA_EACAIVC1_CIV_MASK                  0xfffff

/* EACAIVC2 Register bit definitions */
#define R_ETHA_EACAIVC2_CIV_SHIFT                 (0)  /*  */
#define R_ETHA_EACAIVC2_CIV_MASK                  0xfffff

/* EACAIVC3 Register bit definitions */
#define R_ETHA_EACAIVC3_CIV_SHIFT                 (0)  /*  */
#define R_ETHA_EACAIVC3_CIV_MASK                  0xfffff

/* EACAIVC4 Register bit definitions */
#define R_ETHA_EACAIVC4_CIV_SHIFT                 (0)  /*  */
#define R_ETHA_EACAIVC4_CIV_MASK                  0xfffff

/* EACAIVC5 Register bit definitions */
#define R_ETHA_EACAIVC5_CIV_SHIFT                 (0)  /*  */
#define R_ETHA_EACAIVC5_CIV_MASK                  0xfffff

/* EACAIVC6 Register bit definitions */
#define R_ETHA_EACAIVC6_CIV_SHIFT                 (0)  /*  */
#define R_ETHA_EACAIVC6_CIV_MASK                  0xfffff

/* EACAIVC7 Register bit definitions */
#define R_ETHA_EACAIVC7_CIV_SHIFT                 (0)  /*  */
#define R_ETHA_EACAIVC7_CIV_MASK                  0xfffff

/* EACAULC0 Register bit definitions */
#define R_ETHA_EACAULC0_CUL_SHIFT                 (0)  /*  */
#define R_ETHA_EACAULC0_CUL_MASK                  0x7fffffff

/* EACAULC1 Register bit definitions */
#define R_ETHA_EACAULC1_CUL_SHIFT                 (0)  /*  */
#define R_ETHA_EACAULC1_CUL_MASK                  0x7fffffff

/* EACAULC2 Register bit definitions */
#define R_ETHA_EACAULC2_CUL_SHIFT                 (0)  /*  */
#define R_ETHA_EACAULC2_CUL_MASK                  0x7fffffff

/* EACAULC3 Register bit definitions */
#define R_ETHA_EACAULC3_CUL_SHIFT                 (0)  /*  */
#define R_ETHA_EACAULC3_CUL_MASK                  0x7fffffff

/* EACAULC4 Register bit definitions */
#define R_ETHA_EACAULC4_CUL_SHIFT                 (0)  /*  */
#define R_ETHA_EACAULC4_CUL_MASK                  0x7fffffff

/* EACAULC5 Register bit definitions */
#define R_ETHA_EACAULC5_CUL_SHIFT                 (0)  /*  */
#define R_ETHA_EACAULC5_CUL_MASK                  0x7fffffff

/* EACAULC6 Register bit definitions */
#define R_ETHA_EACAULC6_CUL_SHIFT                 (0)  /*  */
#define R_ETHA_EACAULC6_CUL_MASK                  0x7fffffff

/* EACAULC7 Register bit definitions */
#define R_ETHA_EACAULC7_CUL_SHIFT                 (0)  /*  */
#define R_ETHA_EACAULC7_CUL_MASK                  0x7fffffff

/* EACOEM Register bit definitions */
#define R_ETHA_EACOEM_CE0                         (1 << 0)  /*  */

#define R_ETHA_EACOEM_CE1                         (1 << 1)  /*  */

#define R_ETHA_EACOEM_CE2                         (1 << 2)  /*  */

#define R_ETHA_EACOEM_CE3                         (1 << 3)  /*  */

#define R_ETHA_EACOEM_CE4                         (1 << 4)  /*  */

#define R_ETHA_EACOEM_CE5                         (1 << 5)  /*  */

#define R_ETHA_EACOEM_CE6                         (1 << 6)  /*  */

#define R_ETHA_EACOEM_CE7                         (1 << 7)  /*  */

/* EACOIVM0 Register bit definitions */
#define R_ETHA_EACOIVM0_CIV_SHIFT                 (0)  /*  */
#define R_ETHA_EACOIVM0_CIV_MASK                  0xfffff

/* EACOIVM1 Register bit definitions */
#define R_ETHA_EACOIVM1_CIV_SHIFT                 (0)  /*  */
#define R_ETHA_EACOIVM1_CIV_MASK                  0xfffff

/* EACOIVM2 Register bit definitions */
#define R_ETHA_EACOIVM2_CIV_SHIFT                 (0)  /*  */
#define R_ETHA_EACOIVM2_CIV_MASK                  0xfffff

/* EACOIVM3 Register bit definitions */
#define R_ETHA_EACOIVM3_CIV_SHIFT                 (0)  /*  */
#define R_ETHA_EACOIVM3_CIV_MASK                  0xfffff

/* EACOIVM4 Register bit definitions */
#define R_ETHA_EACOIVM4_CIV_SHIFT                 (0)  /*  */
#define R_ETHA_EACOIVM4_CIV_MASK                  0xfffff

/* EACOIVM5 Register bit definitions */
#define R_ETHA_EACOIVM5_CIV_SHIFT                 (0)  /*  */
#define R_ETHA_EACOIVM5_CIV_MASK                  0xfffff

/* EACOIVM6 Register bit definitions */
#define R_ETHA_EACOIVM6_CIV_SHIFT                 (0)  /*  */
#define R_ETHA_EACOIVM6_CIV_MASK                  0xfffff

/* EACOIVM7 Register bit definitions */
#define R_ETHA_EACOIVM7_CIV_SHIFT                 (0)  /*  */
#define R_ETHA_EACOIVM7_CIV_MASK                  0xfffff

/* EACOULM0 Register bit definitions */
#define R_ETHA_EACOULM0_CUL_SHIFT                 (0)  /*  */
#define R_ETHA_EACOULM0_CUL_MASK                  0x7fffffff

/* EACOULM1 Register bit definitions */
#define R_ETHA_EACOULM1_CUL_SHIFT                 (0)  /*  */
#define R_ETHA_EACOULM1_CUL_MASK                  0x7fffffff

/* EACOULM2 Register bit definitions */
#define R_ETHA_EACOULM2_CUL_SHIFT                 (0)  /*  */
#define R_ETHA_EACOULM2_CUL_MASK                  0x7fffffff

/* EACOULM3 Register bit definitions */
#define R_ETHA_EACOULM3_CUL_SHIFT                 (0)  /*  */
#define R_ETHA_EACOULM3_CUL_MASK                  0x7fffffff

/* EACOULM4 Register bit definitions */
#define R_ETHA_EACOULM4_CUL_SHIFT                 (0)  /*  */
#define R_ETHA_EACOULM4_CUL_MASK                  0x7fffffff

/* EACOULM5 Register bit definitions */
#define R_ETHA_EACOULM5_CUL_SHIFT                 (0)  /*  */
#define R_ETHA_EACOULM5_CUL_MASK                  0x7fffffff

/* EACOULM6 Register bit definitions */
#define R_ETHA_EACOULM6_CUL_SHIFT                 (0)  /*  */
#define R_ETHA_EACOULM6_CUL_MASK                  0x7fffffff

/* EACOULM7 Register bit definitions */
#define R_ETHA_EACOULM7_CUL_SHIFT                 (0)  /*  */
#define R_ETHA_EACOULM7_CUL_MASK                  0x7fffffff

/* EACGSM Register bit definitions */
#define R_ETHA_EACGSM_CGS0                        (1 << 0)  /*  */

#define R_ETHA_EACGSM_CGS1                        (1 << 1)  /*  */

#define R_ETHA_EACGSM_CGS2                        (1 << 2)  /*  */

#define R_ETHA_EACGSM_CGS3                        (1 << 3)  /*  */

#define R_ETHA_EACGSM_CGS4                        (1 << 4)  /*  */

#define R_ETHA_EACGSM_CGS5                        (1 << 5)  /*  */

#define R_ETHA_EACGSM_CGS6                        (1 << 6)  /*  */

#define R_ETHA_EACGSM_CGS7                        (1 << 7)  /*  */

/* EATASC Register bit definitions */
#define R_ETHA_EATASC_TASE                        (1 << 0)  /*  */

#define R_ETHA_EATASC_TASCC                       (1 << 1)  /*  */

#define R_ETHA_EATASC_TASCI                       (1 << 2)  /*  */

#define R_ETHA_EATASC_TASTS                       (1 << 8)  /*  */

#define R_ETHA_EATASC_TASCA_SHIFT                 (16)  /*  */
#define R_ETHA_EATASC_TASCA_MASK                  0xff0000

/* EATASIGSC Register bit definitions */
#define R_ETHA_EATASIGSC_TASIGS0                  (1 << 0)  /*  */

#define R_ETHA_EATASIGSC_TASIGS1                  (1 << 1)  /*  */

#define R_ETHA_EATASIGSC_TASIGS2                  (1 << 2)  /*  */

#define R_ETHA_EATASIGSC_TASIGS3                  (1 << 3)  /*  */

#define R_ETHA_EATASIGSC_TASIGS4                  (1 << 4)  /*  */

#define R_ETHA_EATASIGSC_TASIGS5                  (1 << 5)  /*  */

#define R_ETHA_EATASIGSC_TASIGS6                  (1 << 6)  /*  */

#define R_ETHA_EATASIGSC_TASIGS7                  (1 << 7)  /*  */

#define R_ETHA_EATASIGSC_TASCTIGS                 (1 << 8)  /*  */

/* EATASENC0 Register bit definitions */
#define R_ETHA_EATASENC0_TASAEN_SHIFT             (0)  /*  */
#define R_ETHA_EATASENC0_TASAEN_MASK              0x1ff

/* EATASENC1 Register bit definitions */
#define R_ETHA_EATASENC1_TASAEN_SHIFT             (0)  /*  */
#define R_ETHA_EATASENC1_TASAEN_MASK              0x1ff

/* EATASENC2 Register bit definitions */
#define R_ETHA_EATASENC2_TASAEN_SHIFT             (0)  /*  */
#define R_ETHA_EATASENC2_TASAEN_MASK              0x1ff

/* EATASENC3 Register bit definitions */
#define R_ETHA_EATASENC3_TASAEN_SHIFT             (0)  /*  */
#define R_ETHA_EATASENC3_TASAEN_MASK              0x1ff

/* EATASENC4 Register bit definitions */
#define R_ETHA_EATASENC4_TASAEN_SHIFT             (0)  /*  */
#define R_ETHA_EATASENC4_TASAEN_MASK              0x1ff

/* EATASENC5 Register bit definitions */
#define R_ETHA_EATASENC5_TASAEN_SHIFT             (0)  /*  */
#define R_ETHA_EATASENC5_TASAEN_MASK              0x1ff

/* EATASENC6 Register bit definitions */
#define R_ETHA_EATASENC6_TASAEN_SHIFT             (0)  /*  */
#define R_ETHA_EATASENC6_TASAEN_MASK              0x1ff

/* EATASENC7 Register bit definitions */
#define R_ETHA_EATASENC7_TASAEN_SHIFT             (0)  /*  */
#define R_ETHA_EATASENC7_TASAEN_MASK              0x1ff

/* EATASCTENC Register bit definitions */
#define R_ETHA_EATASCTENC_TASCTAEN_SHIFT          (0)  /*  */
#define R_ETHA_EATASCTENC_TASCTAEN_MASK           0x1ff

/* EATASENM0 Register bit definitions */
#define R_ETHA_EATASENM0_TASOEN_SHIFT             (0)  /*  */
#define R_ETHA_EATASENM0_TASOEN_MASK              0x1ff

/* EATASENM1 Register bit definitions */
#define R_ETHA_EATASENM1_TASOEN_SHIFT             (0)  /*  */
#define R_ETHA_EATASENM1_TASOEN_MASK              0x1ff

/* EATASENM2 Register bit definitions */
#define R_ETHA_EATASENM2_TASOEN_SHIFT             (0)  /*  */
#define R_ETHA_EATASENM2_TASOEN_MASK              0x1ff

/* EATASENM3 Register bit definitions */
#define R_ETHA_EATASENM3_TASOEN_SHIFT             (0)  /*  */
#define R_ETHA_EATASENM3_TASOEN_MASK              0x1ff

/* EATASENM4 Register bit definitions */
#define R_ETHA_EATASENM4_TASOEN_SHIFT             (0)  /*  */
#define R_ETHA_EATASENM4_TASOEN_MASK              0x1ff

/* EATASENM5 Register bit definitions */
#define R_ETHA_EATASENM5_TASOEN_SHIFT             (0)  /*  */
#define R_ETHA_EATASENM5_TASOEN_MASK              0x1ff

/* EATASENM6 Register bit definitions */
#define R_ETHA_EATASENM6_TASOEN_SHIFT             (0)  /*  */
#define R_ETHA_EATASENM6_TASOEN_MASK              0x1ff

/* EATASENM7 Register bit definitions */
#define R_ETHA_EATASENM7_TASOEN_SHIFT             (0)  /*  */
#define R_ETHA_EATASENM7_TASOEN_MASK              0x1ff

/* EATASCTENM Register bit definitions */
#define R_ETHA_EATASCTENM_TASCTOEN_SHIFT          (0)  /*  */
#define R_ETHA_EATASCTENM_TASCTOEN_MASK           0x1ff

/* EATASCSTC0 Register bit definitions */
#define R_ETHA_EATASCSTC0_TASACSTP0_SHIFT         (0)  /*  */
#define R_ETHA_EATASCSTC0_TASACSTP0_MASK          0xffffffff

/* EATASCSTC1 Register bit definitions */
#define R_ETHA_EATASCSTC1_TASACSTP1_SHIFT         (0)  /*  */
#define R_ETHA_EATASCSTC1_TASACSTP1_MASK          0xffffffff

/* EATASCSTM0 Register bit definitions */
#define R_ETHA_EATASCSTM0_TASOCSTP0_SHIFT         (0)  /*  */
#define R_ETHA_EATASCSTM0_TASOCSTP0_MASK          0xffffffff

/* EATASCSTM1 Register bit definitions */
#define R_ETHA_EATASCSTM1_TASOCSTP1_SHIFT         (0)  /*  */
#define R_ETHA_EATASCSTM1_TASOCSTP1_MASK          0xffffffff

/* EATASCTC Register bit definitions */
#define R_ETHA_EATASCTC_TASACT_SHIFT              (0)  /*  */
#define R_ETHA_EATASCTC_TASACT_MASK               0xffffffff

/* EATASCTM Register bit definitions */
#define R_ETHA_EATASCTM_TASOCT_SHIFT              (0)  /*  */
#define R_ETHA_EATASCTM_TASOCT_MASK               0xffffffff

/* EATASGL0 Register bit definitions */
#define R_ETHA_EATASGL0_TASGAL_SHIFT              (0)  /*  */
#define R_ETHA_EATASGL0_TASGAL_MASK               0xff

/* EATASGL1 Register bit definitions */
#define R_ETHA_EATASGL1_TASGTL_SHIFT              (0)  /*  */
#define R_ETHA_EATASGL1_TASGTL_MASK               0xfffffff

#define R_ETHA_EATASGL1_TASGSL                    (1 << 28)  /*  */

/* EATASGLR Register bit definitions */
#define R_ETHA_EATASGLR_GL                        (1 << 31)  /*  */

/* EATASGR Register bit definitions */
#define R_ETHA_EATASGR_TASGAR_SHIFT               (0)  /*  */
#define R_ETHA_EATASGR_TASGAR_MASK                0xff

/* EATASGRR Register bit definitions */
#define R_ETHA_EATASGRR_TASGTR_SHIFT              (0)  /*  */
#define R_ETHA_EATASGRR_TASGTR_MASK               0xfffffff

#define R_ETHA_EATASGRR_TASGSR                    (1 << 28)  /*  */

#define R_ETHA_EATASGRR_TASREF                    (1 << 29)  /*  */

#define R_ETHA_EATASGRR_GR                        (1 << 31)  /*  */

/* EATASHCC Register bit definitions */
#define R_ETHA_EATASHCC_TASJ_SHIFT                (0)  /*  */
#define R_ETHA_EATASHCC_TASJ_MASK                 0xffff

/* EATASRIRM Register bit definitions */
#define R_ETHA_EATASRIRM_TASRIOG                  (1 << 0)  /*  */

#define R_ETHA_EATASRIRM_TASRR                    (1 << 1)  /*  */

/* EATASSM Register bit definitions */
#define R_ETHA_EATASSM_TASGS0                     (1 << 0)  /*  */

#define R_ETHA_EATASSM_TASGS1                     (1 << 1)  /*  */

#define R_ETHA_EATASSM_TASGS2                     (1 << 2)  /*  */

#define R_ETHA_EATASSM_TASGS3                     (1 << 3)  /*  */

#define R_ETHA_EATASSM_TASGS4                     (1 << 4)  /*  */

#define R_ETHA_EATASSM_TASGS5                     (1 << 5)  /*  */

#define R_ETHA_EATASSM_TASGS6                     (1 << 6)  /*  */

#define R_ETHA_EATASSM_TASGS7                     (1 << 7)  /*  */

#define R_ETHA_EATASSM_TASCTGS                    (1 << 8)  /*  */

#define R_ETHA_EATASSM_TASSO                      (1 << 16)  /*  */

/* EAUSMFSECN Register bit definitions */
#define R_ETHA_EAUSMFSECN_USMFSEN_SHIFT           (0)  /*  */
#define R_ETHA_EAUSMFSECN_USMFSEN_MASK            0xffff

/* EATFECN Register bit definitions */
#define R_ETHA_EATFECN_TFEN_SHIFT                 (0)  /*  */
#define R_ETHA_EATFECN_TFEN_MASK                  0xffff

/* EAFSECN Register bit definitions */
#define R_ETHA_EAFSECN_FSEN_SHIFT                 (0)  /*  */
#define R_ETHA_EAFSECN_FSEN_MASK                  0xffff

/* EADQOECN Register bit definitions */
#define R_ETHA_EADQOECN_DQOEN_SHIFT               (0)  /*  */
#define R_ETHA_EADQOECN_DQOEN_MASK                0xffff

/* EADQSECN Register bit definitions */
#define R_ETHA_EADQSECN_DQSEN_SHIFT               (0)  /*  */
#define R_ETHA_EADQSECN_DQSEN_MASK                0xffff

/* EAEIS0 Register bit definitions */
#define R_ETHA_EAEIS0_DECCES                      (1 << 0)  /*  */

#define R_ETHA_EAEIS0_TECCES                      (1 << 1)  /*  */

#define R_ETHA_EAEIS0_PECCES                      (1 << 2)  /*  */

#define R_ETHA_EAEIS0_DSECCES                     (1 << 3)  /*  */

#define R_ETHA_EAEIS0_L23UECCES                   (1 << 4)  /*  */

#define R_ETHA_EAEIS0_USMFSES                     (1 << 5)  /*  */

#define R_ETHA_EAEIS0_TFES                        (1 << 6)  /*  */

#define R_ETHA_EAEIS0_FSES0                       (1 << 8)  /*  */

#define R_ETHA_EAEIS0_FSES1                       (1 << 9)  /*  */

#define R_ETHA_EAEIS0_FSES2                       (1 << 10)  /*  */

#define R_ETHA_EAEIS0_FSES3                       (1 << 11)  /*  */

#define R_ETHA_EAEIS0_FSES4                       (1 << 12)  /*  */

#define R_ETHA_EAEIS0_FSES5                       (1 << 13)  /*  */

#define R_ETHA_EAEIS0_FSES6                       (1 << 14)  /*  */

#define R_ETHA_EAEIS0_FSES7                       (1 << 15)  /*  */

#define R_ETHA_EAEIS0_TASGEES0                    (1 << 16)  /*  */

#define R_ETHA_EAEIS0_TASGEES1                    (1 << 17)  /*  */

#define R_ETHA_EAEIS0_TASGEES2                    (1 << 18)  /*  */

#define R_ETHA_EAEIS0_TASGEES3                    (1 << 19)  /*  */

#define R_ETHA_EAEIS0_TASGEES4                    (1 << 20)  /*  */

#define R_ETHA_EAEIS0_TASGEES5                    (1 << 21)  /*  */

#define R_ETHA_EAEIS0_TASGEES6                    (1 << 22)  /*  */

#define R_ETHA_EAEIS0_TASGEES7                    (1 << 23)  /*  */

#define R_ETHA_EAEIS0_TASCTGEES                   (1 << 24)  /*  */

/* EAEIE0 Register bit definitions */
#define R_ETHA_EAEIE0_DECCEE                      (1 << 0)  /*  */

#define R_ETHA_EAEIE0_TECCEE                      (1 << 1)  /*  */

#define R_ETHA_EAEIE0_PECCEE                      (1 << 2)  /*  */

#define R_ETHA_EAEIE0_DSECCEE                     (1 << 3)  /*  */

#define R_ETHA_EAEIE0_L23UECCEE                   (1 << 4)  /*  */

#define R_ETHA_EAEIE0_USMFSEE                     (1 << 5)  /*  */

#define R_ETHA_EAEIE0_TFEE                        (1 << 6)  /*  */

#define R_ETHA_EAEIE0_FSEE0                       (1 << 8)  /*  */

#define R_ETHA_EAEIE0_FSEE1                       (1 << 9)  /*  */

#define R_ETHA_EAEIE0_FSEE2                       (1 << 10)  /*  */

#define R_ETHA_EAEIE0_FSEE3                       (1 << 11)  /*  */

#define R_ETHA_EAEIE0_FSEE4                       (1 << 12)  /*  */

#define R_ETHA_EAEIE0_FSEE5                       (1 << 13)  /*  */

#define R_ETHA_EAEIE0_FSEE6                       (1 << 14)  /*  */

#define R_ETHA_EAEIE0_FSEE7                       (1 << 15)  /*  */

#define R_ETHA_EAEIE0_TASGEEE0                    (1 << 16)  /*  */

#define R_ETHA_EAEIE0_TASGEEE1                    (1 << 17)  /*  */

#define R_ETHA_EAEIE0_TASGEEE2                    (1 << 18)  /*  */

#define R_ETHA_EAEIE0_TASGEEE3                    (1 << 19)  /*  */

#define R_ETHA_EAEIE0_TASGEEE4                    (1 << 20)  /*  */

#define R_ETHA_EAEIE0_TASGEEE5                    (1 << 21)  /*  */

#define R_ETHA_EAEIE0_TASGEEE6                    (1 << 22)  /*  */

#define R_ETHA_EAEIE0_TASGEEE7                    (1 << 23)  /*  */

#define R_ETHA_EAEIE0_TASCTGEEE                   (1 << 24)  /*  */

/* EAEID0 Register bit definitions */
#define R_ETHA_EAEID0_DECCED                      (1 << 0)  /*  */

#define R_ETHA_EAEID0_TECCED                      (1 << 1)  /*  */

#define R_ETHA_EAEID0_PECCED                      (1 << 2)  /*  */

#define R_ETHA_EAEID0_DSECCED                     (1 << 3)  /*  */

#define R_ETHA_EAEID0_L23UECCED                   (1 << 4)  /*  */

#define R_ETHA_EAEID0_USMFSED                     (1 << 5)  /*  */

#define R_ETHA_EAEID0_TFED                        (1 << 6)  /*  */

#define R_ETHA_EAEID0_FSED0                       (1 << 8)  /*  */

#define R_ETHA_EAEID0_FSED1                       (1 << 9)  /*  */

#define R_ETHA_EAEID0_FSED2                       (1 << 10)  /*  */

#define R_ETHA_EAEID0_FSED3                       (1 << 11)  /*  */

#define R_ETHA_EAEID0_FSED4                       (1 << 12)  /*  */

#define R_ETHA_EAEID0_FSED5                       (1 << 13)  /*  */

#define R_ETHA_EAEID0_FSED6                       (1 << 14)  /*  */

#define R_ETHA_EAEID0_FSED7                       (1 << 15)  /*  */

#define R_ETHA_EAEID0_TASGEED0                    (1 << 16)  /*  */

#define R_ETHA_EAEID0_TASGEED1                    (1 << 17)  /*  */

#define R_ETHA_EAEID0_TASGEED2                    (1 << 18)  /*  */

#define R_ETHA_EAEID0_TASGEED3                    (1 << 19)  /*  */

#define R_ETHA_EAEID0_TASGEED4                    (1 << 20)  /*  */

#define R_ETHA_EAEID0_TASGEED5                    (1 << 21)  /*  */

#define R_ETHA_EAEID0_TASGEED6                    (1 << 22)  /*  */

#define R_ETHA_EAEID0_TASGEED7                    (1 << 23)  /*  */

#define R_ETHA_EAEID0_TASCTGEED                   (1 << 24)  /*  */

/* EAEIS1 Register bit definitions */
#define R_ETHA_EAEIS1_CULES0                      (1 << 0)  /*  */

#define R_ETHA_EAEIS1_CULES1                      (1 << 1)  /*  */

#define R_ETHA_EAEIS1_CULES2                      (1 << 2)  /*  */

#define R_ETHA_EAEIS1_CULES3                      (1 << 3)  /*  */

#define R_ETHA_EAEIS1_CULES4                      (1 << 4)  /*  */

#define R_ETHA_EAEIS1_CULES5                      (1 << 5)  /*  */

#define R_ETHA_EAEIS1_CULES6                      (1 << 6)  /*  */

#define R_ETHA_EAEIS1_CULES7                      (1 << 7)  /*  */

#define R_ETHA_EAEIS1_TASGES0                     (1 << 16)  /*  */

#define R_ETHA_EAEIS1_TASGES1                     (1 << 17)  /*  */

#define R_ETHA_EAEIS1_TASGES2                     (1 << 18)  /*  */

#define R_ETHA_EAEIS1_TASGES3                     (1 << 19)  /*  */

#define R_ETHA_EAEIS1_TASGES4                     (1 << 20)  /*  */

#define R_ETHA_EAEIS1_TASGES5                     (1 << 21)  /*  */

#define R_ETHA_EAEIS1_TASGES6                     (1 << 22)  /*  */

#define R_ETHA_EAEIS1_TASGES7                     (1 << 23)  /*  */

#define R_ETHA_EAEIS1_TASCTGES                    (1 << 24)  /*  */

/* EAEIE1 Register bit definitions */
#define R_ETHA_EAEIE1_CULEE0                      (1 << 0)  /*  */

#define R_ETHA_EAEIE1_CULEE1                      (1 << 1)  /*  */

#define R_ETHA_EAEIE1_CULEE2                      (1 << 2)  /*  */

#define R_ETHA_EAEIE1_CULEE3                      (1 << 3)  /*  */

#define R_ETHA_EAEIE1_CULEE4                      (1 << 4)  /*  */

#define R_ETHA_EAEIE1_CULEE5                      (1 << 5)  /*  */

#define R_ETHA_EAEIE1_CULEE6                      (1 << 6)  /*  */

#define R_ETHA_EAEIE1_CULEE7                      (1 << 7)  /*  */

#define R_ETHA_EAEIE1_TASGEE0                     (1 << 16)  /*  */

#define R_ETHA_EAEIE1_TASGEE1                     (1 << 17)  /*  */

#define R_ETHA_EAEIE1_TASGEE2                     (1 << 18)  /*  */

#define R_ETHA_EAEIE1_TASGEE3                     (1 << 19)  /*  */

#define R_ETHA_EAEIE1_TASGEE4                     (1 << 20)  /*  */

#define R_ETHA_EAEIE1_TASGEE5                     (1 << 21)  /*  */

#define R_ETHA_EAEIE1_TASGEE6                     (1 << 22)  /*  */

#define R_ETHA_EAEIE1_TASGEE7                     (1 << 23)  /*  */

#define R_ETHA_EAEIE1_TASCTGEE                    (1 << 24)  /*  */

/* EAEID1 Register bit definitions */
#define R_ETHA_EAEID1_CULED0                      (1 << 0)  /*  */

#define R_ETHA_EAEID1_CULED1                      (1 << 1)  /*  */

#define R_ETHA_EAEID1_CULED2                      (1 << 2)  /*  */

#define R_ETHA_EAEID1_CULED3                      (1 << 3)  /*  */

#define R_ETHA_EAEID1_CULED4                      (1 << 4)  /*  */

#define R_ETHA_EAEID1_CULED5                      (1 << 5)  /*  */

#define R_ETHA_EAEID1_CULED6                      (1 << 6)  /*  */

#define R_ETHA_EAEID1_CULED7                      (1 << 7)  /*  */

#define R_ETHA_EAEID1_TASGED0                     (1 << 16)  /*  */

#define R_ETHA_EAEID1_TASGED1                     (1 << 17)  /*  */

#define R_ETHA_EAEID1_TASGED2                     (1 << 18)  /*  */

#define R_ETHA_EAEID1_TASGED3                     (1 << 19)  /*  */

#define R_ETHA_EAEID1_TASGED4                     (1 << 20)  /*  */

#define R_ETHA_EAEID1_TASGED5                     (1 << 21)  /*  */

#define R_ETHA_EAEID1_TASGED6                     (1 << 22)  /*  */

#define R_ETHA_EAEID1_TASGED7                     (1 << 23)  /*  */

#define R_ETHA_EAEID1_TASCTGED                    (1 << 24)  /*  */

/* EAEIS2 Register bit definitions */
#define R_ETHA_EAEIS2_DQOES0                      (1 << 0)  /*  */

#define R_ETHA_EAEIS2_DQOES1                      (1 << 1)  /*  */

#define R_ETHA_EAEIS2_DQOES2                      (1 << 2)  /*  */

#define R_ETHA_EAEIS2_DQOES3                      (1 << 3)  /*  */

#define R_ETHA_EAEIS2_DQOES4                      (1 << 4)  /*  */

#define R_ETHA_EAEIS2_DQOES5                      (1 << 5)  /*  */

#define R_ETHA_EAEIS2_DQOES6                      (1 << 6)  /*  */

#define R_ETHA_EAEIS2_DQOES7                      (1 << 7)  /*  */

#define R_ETHA_EAEIS2_CTDQOES                     (1 << 8)  /*  */

#define R_ETHA_EAEIS2_DQSES0                      (1 << 16)  /*  */

#define R_ETHA_EAEIS2_DQSES1                      (1 << 17)  /*  */

#define R_ETHA_EAEIS2_DQSES2                      (1 << 18)  /*  */

#define R_ETHA_EAEIS2_DQSES3                      (1 << 19)  /*  */

#define R_ETHA_EAEIS2_DQSES4                      (1 << 20)  /*  */

#define R_ETHA_EAEIS2_DQSES5                      (1 << 21)  /*  */

#define R_ETHA_EAEIS2_DQSES6                      (1 << 22)  /*  */

#define R_ETHA_EAEIS2_DQSES7                      (1 << 23)  /*  */

/* EAEIE2 Register bit definitions */
#define R_ETHA_EAEIE2_DQOEE0                      (1 << 0)  /*  */

#define R_ETHA_EAEIE2_DQOEE1                      (1 << 1)  /*  */

#define R_ETHA_EAEIE2_DQOEE2                      (1 << 2)  /*  */

#define R_ETHA_EAEIE2_DQOEE3                      (1 << 3)  /*  */

#define R_ETHA_EAEIE2_DQOEE4                      (1 << 4)  /*  */

#define R_ETHA_EAEIE2_DQOEE5                      (1 << 5)  /*  */

#define R_ETHA_EAEIE2_DQOEE6                      (1 << 6)  /*  */

#define R_ETHA_EAEIE2_DQOEE7                      (1 << 7)  /*  */

#define R_ETHA_EAEIE2_CTDQOEE                     (1 << 8)  /*  */

#define R_ETHA_EAEIE2_DQSEE0                      (1 << 16)  /*  */

#define R_ETHA_EAEIE2_DQSEE1                      (1 << 17)  /*  */

#define R_ETHA_EAEIE2_DQSEE2                      (1 << 18)  /*  */

#define R_ETHA_EAEIE2_DQSEE3                      (1 << 19)  /*  */

#define R_ETHA_EAEIE2_DQSEE4                      (1 << 20)  /*  */

#define R_ETHA_EAEIE2_DQSEE5                      (1 << 21)  /*  */

#define R_ETHA_EAEIE2_DQSEE6                      (1 << 22)  /*  */

#define R_ETHA_EAEIE2_DQSEE7                      (1 << 23)  /*  */

/* EAEID2 Register bit definitions */
#define R_ETHA_EAEID2_DQOED0                      (1 << 0)  /*  */

#define R_ETHA_EAEID2_DQOED1                      (1 << 1)  /*  */

#define R_ETHA_EAEID2_DQOED2                      (1 << 2)  /*  */

#define R_ETHA_EAEID2_DQOED3                      (1 << 3)  /*  */

#define R_ETHA_EAEID2_DQOED4                      (1 << 4)  /*  */

#define R_ETHA_EAEID2_DQOED5                      (1 << 5)  /*  */

#define R_ETHA_EAEID2_DQOED6                      (1 << 6)  /*  */

#define R_ETHA_EAEID2_DQOED7                      (1 << 7)  /*  */

#define R_ETHA_EAEID2_CTDQOED                     (1 << 8)  /*  */

#define R_ETHA_EAEID2_DQSED0                      (1 << 16)  /*  */

#define R_ETHA_EAEID2_DQSED1                      (1 << 17)  /*  */

#define R_ETHA_EAEID2_DQSED2                      (1 << 18)  /*  */

#define R_ETHA_EAEID2_DQSED3                      (1 << 19)  /*  */

#define R_ETHA_EAEID2_DQSED4                      (1 << 20)  /*  */

#define R_ETHA_EAEID2_DQSED5                      (1 << 21)  /*  */

#define R_ETHA_EAEID2_DQSED6                      (1 << 22)  /*  */

#define R_ETHA_EAEID2_DQSED7                      (1 << 23)  /*  */

/* EASCR Register bit definitions */
#define R_ETHA_EASCR_MRSL                         (1 << 0)  /*  */

#define R_ETHA_EASCR_TRSL                         (1 << 1)  /*  */

#define R_ETHA_EASCR_MCRSL                        (1 << 2)  /*  */

#define R_ETHA_EASCR_TGRSL                        (1 << 3)  /*  */

#define R_ETHA_EASCR_TASRSL                       (1 << 4)  /*  */

#define R_ETHA_EASCR_EIRSL                        (1 << 5)  /*  */

#define R_ETHA_EASCR_CRSL                         (1 << 6)  /*  */

#define R_ETHA_EASCR_DQRSL0                       (1 << 16)  /*  */

#define R_ETHA_EASCR_DQRSL1                       (1 << 17)  /*  */

#define R_ETHA_EASCR_DQRSL2                       (1 << 18)  /*  */

#define R_ETHA_EASCR_DQRSL3                       (1 << 19)  /*  */

#define R_ETHA_EASCR_DQRSL4                       (1 << 20)  /*  */

#define R_ETHA_EASCR_DQRSL5                       (1 << 21)  /*  */

#define R_ETHA_EASCR_DQRSL6                       (1 << 22)  /*  */

#define R_ETHA_EASCR_DQRSL7                       (1 << 23)  /*  */


/* Maximum number of channels */

#define ETHA_MAX_CHANNELS    2

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ETHA_H */
