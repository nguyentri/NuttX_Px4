/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_rmac.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_RMAC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_RMAC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* RMAC Base Address */
#ifndef R_RMAC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_RMAC_BASE           0x403cb000
#else
#define R_RMAC_BASE           0x503cb000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_RMAC_CH_STRIDE    0x00002000
#define R_RMAC_CH_BASE(ch)   (R_RMAC_BASE + ((uint32_t)(ch) * R_RMAC_CH_STRIDE))

/* RMAC Register Offsets */

#define R_RMAC_MPSM_OFFSET                        0x00000000  /* PHY Station Management Register */
#define R_RMAC_MPIC_OFFSET                        0x00000004  /* PHY Interfaces Configuration Register */
#define R_RMAC_MPIM_OFFSET                        0x00000008  /* PHY Interfaces Monitoring Register */
#define R_RMAC_MIOC_OFFSET                        0x00000010  /* I/O Configuration Register */
#define R_RMAC_MTFFC_OFFSET                       0x00000020  /* Transmission Frame Format Configuration Register */
#define R_RMAC_MTPFC_OFFSET                       0x00000024  /* Transmission Pause or PFC Frame Configuration Register */
#define R_RMAC_MTPFC2_OFFSET                      0x00000028  /* Transmission Pause or PFC Frame Configuration Register 2 */
#define R_RMAC_MTPFC3T_OFFSET                     0x00000030  /* Transmission Pause or PFC Frame Configuration Register 3 for Priority Group t */
#define R_RMAC_MRGC_OFFSET                        0x00000080  /* Reception General Configuration Register */
#define R_RMAC_MRMAC0_OFFSET                      0x00000084  /* Reception MAC Address Configuration Register 0 */
#define R_RMAC_MRMAC1_OFFSET                      0x00000088  /* Reception MAC Address Configuration Register 1 */
#define R_RMAC_MRAFC_OFFSET                       0x0000008c  /* Reception Address Filter Configuration Register */
#define R_RMAC_MRSCE_OFFSET                       0x00000090  /* Reception Storm Configuration for E-Frames Register */
#define R_RMAC_MRSCP_OFFSET                       0x00000094  /* Reception Storm Configuration for P-Frames Register */
#define R_RMAC_MRSCC_OFFSET                       0x00000098  /* Reception Storm Counter Configuration Register */
#define R_RMAC_MRFSCE_OFFSET                      0x0000009c  /* Reception Frame Size Configuration for E-Frames Register */
#define R_RMAC_MRFSCP_OFFSET                      0x000000a0  /* Reception Frame Size Configuration for P-Frames Register */
#define R_RMAC_MTRC_OFFSET                        0x000000a4  /* Timestamp Reception Configuration Register */
#define R_RMAC_MRPFM_OFFSET                       0x000000ac  /* Reception Pause or PFC Frame Monitoring Register */
/* MPFC%s Registers (0-15) */
#define R_RMAC_MPFC_OFFSET(m)                     (0x00000100 + ((m) * 0x00000004))  /* PTP Filtering Register Configuration Register %s */
#define R_RMAC_MLVC_OFFSET                        0x00000180  /* Link Verification Configuration Register */
#define R_RMAC_MEEEC_OFFSET                       0x00000184  /* Energy Efficient Ethernet Configuration Register */
#define R_RMAC_MLBC_OFFSET                        0x00000188  /* Loopback Configuration Register */
#define R_RMAC_MEIS_OFFSET                        0x00000200  /* Error Interrupt Status Register */
#define R_RMAC_MEIE_OFFSET                        0x00000204  /* Error Interrupt Enable Register */
#define R_RMAC_MEID_OFFSET                        0x00000208  /* Error Interrupt Disable Register */
#define R_RMAC_MMIS0_OFFSET                       0x00000210  /* Monitoring Interrupt Status Register 0 */
#define R_RMAC_MMIE0_OFFSET                       0x00000214  /* Monitoring Interrupt Enable Register 0 */
#define R_RMAC_MMID0_OFFSET                       0x00000218  /* Monitoring Interrupt Disable Register 0 */
#define R_RMAC_MMIS1_OFFSET                       0x00000220  /* Monitoring Interrupt Status Register 1 */
#define R_RMAC_MMIE1_OFFSET                       0x00000224  /* Monitoring Interrupt Enable Register 1 */
#define R_RMAC_MMID1_OFFSET                       0x00000228  /* Monitoring Interrupt Disable Register 1 */
#define R_RMAC_MMIS2_OFFSET                       0x00000230  /* Monitoring Interrupt Status Register 2 */
#define R_RMAC_MMIE2_OFFSET                       0x00000234  /* Monitoring Interrupt Enable Register 2 */
#define R_RMAC_MMID2_OFFSET                       0x00000238  /* Monitoring Interrupt Disable Register 2 */
#define R_RMAC_MMPFTCT_OFFSET                     0x00000300  /* Manual Pause Frame Transmit Counter Register */
#define R_RMAC_MAPFTCT_OFFSET                     0x00000304  /* Automatic Pause Frame Transmit Counter Register */
#define R_RMAC_MPFRCT_OFFSET                      0x00000308  /* Pause Frame Receive Counter Register */
#define R_RMAC_MFCICT_OFFSET                      0x0000030c  /* False Carrier Indication Counter Register */
#define R_RMAC_MEEECT_OFFSET                      0x00000310  /* Energy Efficient Ethernet Counter Register */
/* MMPCFTCT%s Registers (0-1) */
#define R_RMAC_MMPCFTCT_OFFSET(m)                 (0x00000320 + ((m) * 0x00000004))  /* Manual PFC Frame Transmit Counter Register */
/* MAPCFTCT%s Registers (0-1) */
#define R_RMAC_MAPCFTCT_OFFSET(m)                 (0x00000330 + ((m) * 0x00000004))  /* Automatic PFC Frame Transmit Counter Register */
/* MPCFRCT%s Registers (0-1) */
#define R_RMAC_MPCFRCT_OFFSET(m)                  (0x00000340 + ((m) * 0x00000004))  /* PFC Frame Receive Counter Register */
#define R_RMAC_MROVFC_OFFSET                      0x00000360  /* Receive Overflow Counter Register */
#define R_RMAC_MRGFCE_OFFSET                      0x00000408  /* Received Good Frame Counter E-Frames Register */
#define R_RMAC_MRGFCP_OFFSET                      0x0000040c  /* Received Good Frame Counter P-Frames Register */
#define R_RMAC_MRBFC_OFFSET                       0x00000410  /* Received Good Broadcast Frame Counter Register */
#define R_RMAC_MRMFC_OFFSET                       0x00000414  /* Received Good Multicast Frame Counter Register */
#define R_RMAC_MRUFC_OFFSET                       0x00000418  /* Received Good Unicast Frame Counter Register */
#define R_RMAC_MRPEFC_OFFSET                      0x0000041c  /* Received PHY Error Frame Count Register */
#define R_RMAC_MRNEFC_OFFSET                      0x00000420  /* Received Nibble Error Frame Count Register */
#define R_RMAC_MRFMEFC_OFFSET                     0x00000424  /* Received FCS/mCRC Error Frame Count Register */
#define R_RMAC_MRFFMEFC_OFFSET                    0x00000428  /* Received Final Fragment Missing Error Frame Count Register */
#define R_RMAC_MRCFCEFC_OFFSET                    0x0000042c  /* Received C-Fragment Count Error Frame Count Register */
#define R_RMAC_MRFCEFC_OFFSET                     0x00000430  /* Received Fragment Count Error Frame Count Register */
#define R_RMAC_MRRCFEFC_OFFSET                    0x00000434  /* Received RMAC Filter Error Frame Count Register */
#define R_RMAC_MRFC_OFFSET                        0x00000438  /* Received Frame Count Register */
#define R_RMAC_MRGUEFC_OFFSET                     0x0000043c  /* Received Good Undersize Error Frame Count Register */
#define R_RMAC_MRBUEFC_OFFSET                     0x00000440  /* Received Bad Undersize Error Frame Count Register */
#define R_RMAC_MRGOEFC_OFFSET                     0x00000444  /* Received Good Oversize Error Frame Count Register */
#define R_RMAC_MRBOEFC_OFFSET                     0x00000448  /* Received Bad Oversize Error Frame Count Register */
#define R_RMAC_MRXBCEU_OFFSET                     0x0000044c  /* Received Byte Counter E-Frames Upper Side Register */
#define R_RMAC_MRXBCEL_OFFSET                     0x00000450  /* Received Byte Counter E-Frames Lower Side Register */
#define R_RMAC_MRXBCPU_OFFSET                     0x00000454  /* Received Byte Counter P-Frames Upper Side Register */
#define R_RMAC_MRXBCPL_OFFSET                     0x00000458  /* Received Byte Counter P-Frames Lower Side Register */
#define R_RMAC_MTGFCE_OFFSET                      0x00000508  /* Transmitted Good Frame Counter E-Frames Register */
#define R_RMAC_MTGFCP_OFFSET                      0x0000050c  /* Transmitted Good Frame Counter P-Frames Register */
#define R_RMAC_MTBFC_OFFSET                       0x00000510  /* Transmitted Broadcast Frame Counter Register */
#define R_RMAC_MTMFC_OFFSET                       0x00000514  /* Transmitted Multicast Frame Counter Register */
#define R_RMAC_MTUFC_OFFSET                       0x00000518  /* Transmitted Unicast Frame Counter Register */
#define R_RMAC_MTEFC_OFFSET                       0x0000051c  /* Transmitted Error Frame Counter Register */
#define R_RMAC_MTXBCEU_OFFSET                     0x00000520  /* Transmitted Byte Counter E-Frames Upper Side Register */
#define R_RMAC_MTXBCEL_OFFSET                     0x00000524  /* Transmitted Byte Counter E-Frames Lower Side Register */
#define R_RMAC_MTXBCPU_OFFSET                     0x00000528  /* Transmitted Byte Counter P-Frames Upper Side Register */
#define R_RMAC_MTXBCPL_OFFSET                     0x0000052c  /* Transmitted Byte Counter P-Frames Lower Side Register */

/* RMAC Register Addresses */

#define R_RMAC_MPSM(n)                            (R_RMAC_CH_BASE(n) + R_RMAC_MPSM_OFFSET)
#define R_RMAC_MPIC(n)                            (R_RMAC_CH_BASE(n) + R_RMAC_MPIC_OFFSET)
#define R_RMAC_MPIM(n)                            (R_RMAC_CH_BASE(n) + R_RMAC_MPIM_OFFSET)
#define R_RMAC_MIOC(n)                            (R_RMAC_CH_BASE(n) + R_RMAC_MIOC_OFFSET)
#define R_RMAC_MTFFC(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MTFFC_OFFSET)
#define R_RMAC_MTPFC(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MTPFC_OFFSET)
#define R_RMAC_MTPFC2(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MTPFC2_OFFSET)
#define R_RMAC_MTPFC3T(n)                         (R_RMAC_CH_BASE(n) + R_RMAC_MTPFC3T_OFFSET)
#define R_RMAC_MRGC(n)                            (R_RMAC_CH_BASE(n) + R_RMAC_MRGC_OFFSET)
#define R_RMAC_MRMAC0(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MRMAC0_OFFSET)
#define R_RMAC_MRMAC1(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MRMAC1_OFFSET)
#define R_RMAC_MRAFC(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MRAFC_OFFSET)
#define R_RMAC_MRSCE(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MRSCE_OFFSET)
#define R_RMAC_MRSCP(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MRSCP_OFFSET)
#define R_RMAC_MRSCC(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MRSCC_OFFSET)
#define R_RMAC_MRFSCE(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MRFSCE_OFFSET)
#define R_RMAC_MRFSCP(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MRFSCP_OFFSET)
#define R_RMAC_MTRC(n)                            (R_RMAC_CH_BASE(n) + R_RMAC_MTRC_OFFSET)
#define R_RMAC_MRPFM(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MRPFM_OFFSET)
#define R_RMAC_MPFC(n, m)                         (R_RMAC_CH_BASE(n) + R_RMAC_MPFC_OFFSET(m))
#define R_RMAC_MLVC(n)                            (R_RMAC_CH_BASE(n) + R_RMAC_MLVC_OFFSET)
#define R_RMAC_MEEEC(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MEEEC_OFFSET)
#define R_RMAC_MLBC(n)                            (R_RMAC_CH_BASE(n) + R_RMAC_MLBC_OFFSET)
#define R_RMAC_MEIS(n)                            (R_RMAC_CH_BASE(n) + R_RMAC_MEIS_OFFSET)
#define R_RMAC_MEIE(n)                            (R_RMAC_CH_BASE(n) + R_RMAC_MEIE_OFFSET)
#define R_RMAC_MEID(n)                            (R_RMAC_CH_BASE(n) + R_RMAC_MEID_OFFSET)
#define R_RMAC_MMIS0(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MMIS0_OFFSET)
#define R_RMAC_MMIE0(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MMIE0_OFFSET)
#define R_RMAC_MMID0(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MMID0_OFFSET)
#define R_RMAC_MMIS1(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MMIS1_OFFSET)
#define R_RMAC_MMIE1(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MMIE1_OFFSET)
#define R_RMAC_MMID1(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MMID1_OFFSET)
#define R_RMAC_MMIS2(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MMIS2_OFFSET)
#define R_RMAC_MMIE2(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MMIE2_OFFSET)
#define R_RMAC_MMID2(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MMID2_OFFSET)
#define R_RMAC_MMPFTCT(n)                         (R_RMAC_CH_BASE(n) + R_RMAC_MMPFTCT_OFFSET)
#define R_RMAC_MAPFTCT(n)                         (R_RMAC_CH_BASE(n) + R_RMAC_MAPFTCT_OFFSET)
#define R_RMAC_MPFRCT(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MPFRCT_OFFSET)
#define R_RMAC_MFCICT(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MFCICT_OFFSET)
#define R_RMAC_MEEECT(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MEEECT_OFFSET)
#define R_RMAC_MMPCFTCT(n, m)                     (R_RMAC_CH_BASE(n) + R_RMAC_MMPCFTCT_OFFSET(m))
#define R_RMAC_MAPCFTCT(n, m)                     (R_RMAC_CH_BASE(n) + R_RMAC_MAPCFTCT_OFFSET(m))
#define R_RMAC_MPCFRCT(n, m)                      (R_RMAC_CH_BASE(n) + R_RMAC_MPCFRCT_OFFSET(m))
#define R_RMAC_MROVFC(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MROVFC_OFFSET)
#define R_RMAC_MRGFCE(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MRGFCE_OFFSET)
#define R_RMAC_MRGFCP(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MRGFCP_OFFSET)
#define R_RMAC_MRBFC(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MRBFC_OFFSET)
#define R_RMAC_MRMFC(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MRMFC_OFFSET)
#define R_RMAC_MRUFC(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MRUFC_OFFSET)
#define R_RMAC_MRPEFC(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MRPEFC_OFFSET)
#define R_RMAC_MRNEFC(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MRNEFC_OFFSET)
#define R_RMAC_MRFMEFC(n)                         (R_RMAC_CH_BASE(n) + R_RMAC_MRFMEFC_OFFSET)
#define R_RMAC_MRFFMEFC(n)                        (R_RMAC_CH_BASE(n) + R_RMAC_MRFFMEFC_OFFSET)
#define R_RMAC_MRCFCEFC(n)                        (R_RMAC_CH_BASE(n) + R_RMAC_MRCFCEFC_OFFSET)
#define R_RMAC_MRFCEFC(n)                         (R_RMAC_CH_BASE(n) + R_RMAC_MRFCEFC_OFFSET)
#define R_RMAC_MRRCFEFC(n)                        (R_RMAC_CH_BASE(n) + R_RMAC_MRRCFEFC_OFFSET)
#define R_RMAC_MRFC(n)                            (R_RMAC_CH_BASE(n) + R_RMAC_MRFC_OFFSET)
#define R_RMAC_MRGUEFC(n)                         (R_RMAC_CH_BASE(n) + R_RMAC_MRGUEFC_OFFSET)
#define R_RMAC_MRBUEFC(n)                         (R_RMAC_CH_BASE(n) + R_RMAC_MRBUEFC_OFFSET)
#define R_RMAC_MRGOEFC(n)                         (R_RMAC_CH_BASE(n) + R_RMAC_MRGOEFC_OFFSET)
#define R_RMAC_MRBOEFC(n)                         (R_RMAC_CH_BASE(n) + R_RMAC_MRBOEFC_OFFSET)
#define R_RMAC_MRXBCEU(n)                         (R_RMAC_CH_BASE(n) + R_RMAC_MRXBCEU_OFFSET)
#define R_RMAC_MRXBCEL(n)                         (R_RMAC_CH_BASE(n) + R_RMAC_MRXBCEL_OFFSET)
#define R_RMAC_MRXBCPU(n)                         (R_RMAC_CH_BASE(n) + R_RMAC_MRXBCPU_OFFSET)
#define R_RMAC_MRXBCPL(n)                         (R_RMAC_CH_BASE(n) + R_RMAC_MRXBCPL_OFFSET)
#define R_RMAC_MTGFCE(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MTGFCE_OFFSET)
#define R_RMAC_MTGFCP(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MTGFCP_OFFSET)
#define R_RMAC_MTBFC(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MTBFC_OFFSET)
#define R_RMAC_MTMFC(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MTMFC_OFFSET)
#define R_RMAC_MTUFC(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MTUFC_OFFSET)
#define R_RMAC_MTEFC(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MTEFC_OFFSET)
#define R_RMAC_MTXBCEU(n)                         (R_RMAC_CH_BASE(n) + R_RMAC_MTXBCEU_OFFSET)
#define R_RMAC_MTXBCEL(n)                         (R_RMAC_CH_BASE(n) + R_RMAC_MTXBCEL_OFFSET)
#define R_RMAC_MTXBCPU(n)                         (R_RMAC_CH_BASE(n) + R_RMAC_MTXBCPU_OFFSET)
#define R_RMAC_MTXBCPL(n)                         (R_RMAC_CH_BASE(n) + R_RMAC_MTXBCPL_OFFSET)

/* Register bit definitions */
/* MPSM Register bit definitions */
#define R_RMAC_MPSM_PSME                          (1 << 0)  /* PHY Station Management Enable */

#define R_RMAC_MPSM_MFF                           (1 << 2)  /* Management Frame Format */

#define R_RMAC_MPSM_PDA_SHIFT                     (3)  /* PHY Device Address */
#define R_RMAC_MPSM_PDA_MASK                      0xf8

#define R_RMAC_MPSM_PRA_SHIFT                     (8)  /* PHY Register Address */
#define R_RMAC_MPSM_PRA_MASK                      0x1f00

#define R_RMAC_MPSM_POP_SHIFT                     (13)  /* PHY Operation Code */
#define R_RMAC_MPSM_POP_MASK                      0x6000
#  define R_RMAC_MPSM_POP_01                              (1 << R_RMAC_MPSM_POP_SHIFT)  /* Write Frame */
#  define R_RMAC_MPSM_POP_10                              (2 << R_RMAC_MPSM_POP_SHIFT)  /* Read Frame */

#define R_RMAC_MPSM_PRD_SHIFT                     (16)  /* PHY Register Data */
#define R_RMAC_MPSM_PRD_MASK                      0xffff0000

/* MPIC Register bit definitions */
#define R_RMAC_MPIC_PIS_SHIFT                     (0)  /* PHY Interface Select */
#define R_RMAC_MPIC_PIS_MASK                      0x7
#  define R_RMAC_MPIC_PIS_000                             (0 << R_RMAC_MPIC_PIS_SHIFT)  /* MII */
#  define R_RMAC_MPIC_PIS_010                             (2 << R_RMAC_MPIC_PIS_SHIFT)  /* GMII */
#  define R_RMAC_MPIC_PIS_100                             (4 << R_RMAC_MPIC_PIS_SHIFT)  /* Reserved */
#  define R_RMAC_MPIC_PIS_101                             (5 << R_RMAC_MPIC_PIS_SHIFT)  /* Reserved */
#  define R_RMAC_MPIC_PIS_110                             (6 << R_RMAC_MPIC_PIS_SHIFT)  /* Reserved */
#  define R_RMAC_MPIC_PIS_111                             (7 << R_RMAC_MPIC_PIS_SHIFT)  /* Reserved */

#define R_RMAC_MPIC_LSC_SHIFT                     (3)  /* Link Speed Configuration */
#define R_RMAC_MPIC_LSC_MASK                      0x38
#  define R_RMAC_MPIC_LSC_000                             (0 << R_RMAC_MPIC_LSC_SHIFT)  /* 10mbps */
#  define R_RMAC_MPIC_LSC_001                             (1 << R_RMAC_MPIC_LSC_SHIFT)  /* 100mbps */
#  define R_RMAC_MPIC_LSC_010                             (2 << R_RMAC_MPIC_LSC_SHIFT)  /* 1gbps */
#  define R_RMAC_MPIC_LSC_011                             (3 << R_RMAC_MPIC_LSC_SHIFT)  /* Reserved */
#  define R_RMAC_MPIC_LSC_110                             (6 << R_RMAC_MPIC_LSC_SHIFT)  /* Reserved */
#  define R_RMAC_MPIC_LSC_111                             (7 << R_RMAC_MPIC_LSC_SHIFT)  /* Reserved */

#define R_RMAC_MPIC_PIP                           (1 << 8)  /* PHY Interrupt Polarity */

#define R_RMAC_MPIC_PIPP                          (1 << 9)  /* PHY Interrupt Pin Plugged */

#define R_RMAC_MPIC_PLSPP                         (1 << 10)  /* PHY Link Status Pin Plugged */

#define R_RMAC_MPIC_PSMCS_SHIFT                   (16)  /* PHY Station Management Clock Selection */
#define R_RMAC_MPIC_PSMCS_MASK                    0x7f0000

#define R_RMAC_MPIC_PSMDP                         (1 << 23)  /* PHY Station Management Disable Preamble */

#define R_RMAC_MPIC_PSMHT_SHIFT                   (24)  /* PHY Station Management Hold Time Adjustment */
#define R_RMAC_MPIC_PSMHT_MASK                    0x7000000
#  define R_RMAC_MPIC_PSMHT_000                           (0 << R_RMAC_MPIC_PSMHT_SHIFT)  /* No adjusted hold time (i.e. change MDO at the rising edge of MDC) */
#  define R_RMAC_MPIC_PSMHT_001                           (1 << R_RMAC_MPIC_PSMHT_SHIFT)  /* 1 clk cycle extra hold time */

#define R_RMAC_MPIC_PSMCT_SHIFT                   (28)  /* PHY Station Management Capture Time Adjustment */
#define R_RMAC_MPIC_PSMCT_MASK                    0x70000000
#  define R_RMAC_MPIC_PSMCT_000                           (0 << R_RMAC_MPIC_PSMCT_SHIFT)  /* No adjusted capture time (i.e. capture MDI at the rising edge of MDC) */
#  define R_RMAC_MPIC_PSMCT_001                           (1 << R_RMAC_MPIC_PSMCT_SHIFT)  /* Capture before 1 clk cycle */

/* MPIM Register bit definitions */
#define R_RMAC_MPIM_PLS                           (1 << 0)  /* PHY Link Status Flag */

#define R_RMAC_MPIM_LPIA                          (1 << 1)  /* LPI Active */

/* MIOC Register bit definitions */
#define R_RMAC_MIOC_MIOC0                         (1 << 0)  /* I/O Configuration 0 */

#define R_RMAC_MIOC_MIOC_SHIFT                    (0)  /* MIOC */
#define R_RMAC_MIOC_MIOC_MASK                     0xffffffff

/* MTFFC Register bit definitions */
#define R_RMAC_MTFFC_DPAD                         (1 << 0)  /* Data Padding Disable */

#define R_RMAC_MTFFC_FCM                          (1 << 1)  /* Flow Control Mode */

/* MTPFC Register bit definitions */
#define R_RMAC_MTPFC_PT_SHIFT                     (0)  /* Pause Time */
#define R_RMAC_MTPFC_PT_MASK                      0xffff

#define R_RMAC_MTPFC_PFRT_SHIFT                   (16)  /* Pause Frame Retransmission Time */
#define R_RMAC_MTPFC_PFRT_MASK                    0xff0000

#define R_RMAC_MTPFC_PFM                          (1 << 26)  /* Pause Frame Mode */

#define R_RMAC_MTPFC_PFRLV_SHIFT                  (27)  /* Pause or PFC Frame Retry Limit Value */
#define R_RMAC_MTPFC_PFRLV_MASK                   0xf8000000

/* MTPFC2 Register bit definitions */
#define R_RMAC_MTPFC2_PFCTTZ1_TO_PFCTTZ0_SHIFT    (0)  /* PFC Frame n Transmission with TIME = 0 (n = 0, 1) */
#define R_RMAC_MTPFC2_PFCTTZ1_TO_PFCTTZ0_MASK     0x3
#  define R_RMAC_MTPFC2_PFCTTZ1_TO_PFCTTZ0_0              (0 << R_RMAC_MTPFC2_PFCTTZ1_TO_PFCTTZ0_SHIFT)  /* The transmission of PFC frames with TIME value zero is disabled. */
#  define R_RMAC_MTPFC2_PFCTTZ1_TO_PFCTTZ0_1              (1 << R_RMAC_MTPFC2_PFCTTZ1_TO_PFCTTZ0_SHIFT)  /* The transmission of PFC frames with TIME value zero is enabled. */

#define R_RMAC_MTPFC2_MPFCFR1_TO_MPFCFR0_SHIFT    (8)  /* Manual PFC Frame n Request (n = 0, 1) */
#define R_RMAC_MTPFC2_MPFCFR1_TO_MPFCFR0_MASK     0x300

#define R_RMAC_MTPFC2_PFTTZ                       (1 << 16)  /* Pause Frame Transmission with TIME = 0 */

#define R_RMAC_MTPFC2_MPFR                        (1 << 17)  /* Manual Pause Frame Request */

#define R_RMAC_MTPFC2_PFCTTZ_SHIFT                (0)  /* PFCTTZ */
#define R_RMAC_MTPFC2_PFCTTZ_MASK                 0x3

#define R_RMAC_MTPFC2_MPFCFR0                     (1 << 8)  /* MPFCFR0 */

#define R_RMAC_MTPFC2_MPFCFR1                     (1 << 9)  /* MPFCFR1 */

/* MTPFC3T Register bit definitions */
#define R_RMAC_MTPFC3T_PFCPG0                     (1 << 0)  /* PFC Priority Enable n (n = 0 to 7) */

#define R_RMAC_MTPFC3T_PFCPG1                     (1 << 1)  /* PFC Priority Enable n (n = 0 to 7) */

#define R_RMAC_MTPFC3T_PFCPG2                     (1 << 2)  /* PFC Priority Enable n (n = 0 to 7) */

#define R_RMAC_MTPFC3T_PFCPG3                     (1 << 3)  /* PFC Priority Enable n (n = 0 to 7) */

#define R_RMAC_MTPFC3T_PFCPG4                     (1 << 4)  /* PFC Priority Enable n (n = 0 to 7) */

#define R_RMAC_MTPFC3T_PFCPG5                     (1 << 5)  /* PFC Priority Enable n (n = 0 to 7) */

#define R_RMAC_MTPFC3T_PFCPG6                     (1 << 6)  /* PFC Priority Enable n (n = 0 to 7) */

#define R_RMAC_MTPFC3T_PFCPG7                     (1 << 7)  /* PFC Priority Enable n (n = 0 to 7) */

/* MRGC Register bit definitions */
#define R_RMAC_MRGC_RCPT                          (1 << 0)  /* Receive CRC Pass Through */

#define R_RMAC_MRGC_PFRC                          (1 << 1)  /* Pause Frame Reception Control */

#define R_RMAC_MRGC_PFRTZ                         (1 << 2)  /* Pause or PFC Frame Reception with Time = 0 */

#define R_RMAC_MRGC_MPDE                          (1 << 3)  /* Magic Packet Detection Enable */

#define R_RMAC_MRGC_RFCFE                         (1 << 4)  /* Reception Flow Control Forwarding Enable */

#define R_RMAC_MRGC_PFCRC0                        (1 << 16)  /* PFC Frame Reception Control n (n = 0 to 7) */

#define R_RMAC_MRGC_PFCRC1                        (1 << 17)  /* PFC Frame Reception Control n (n = 0 to 7) */

#define R_RMAC_MRGC_PFCRC2                        (1 << 18)  /* PFC Frame Reception Control n (n = 0 to 7) */

#define R_RMAC_MRGC_PFCRC3                        (1 << 19)  /* PFC Frame Reception Control n (n = 0 to 7) */

#define R_RMAC_MRGC_PFCRC4                        (1 << 20)  /* PFC Frame Reception Control n (n = 0 to 7) */

#define R_RMAC_MRGC_PFCRC5                        (1 << 21)  /* PFC Frame Reception Control n (n = 0 to 7) */

#define R_RMAC_MRGC_PFCRC6                        (1 << 22)  /* PFC Frame Reception Control n (n = 0 to 7) */

#define R_RMAC_MRGC_PFCRC7                        (1 << 23)  /* PFC Frame Reception Control n (n = 0 to 7) */

#define R_RMAC_MRGC_PFCRC_SHIFT                   (16)  /* PFCRC */
#define R_RMAC_MRGC_PFCRC_MASK                    0xff0000

/* MRMAC0 Register bit definitions */
#define R_RMAC_MRMAC0_MAU_SHIFT                   (0)  /* MAC Address Upper Part */
#define R_RMAC_MRMAC0_MAU_MASK                    0xffff

/* MRMAC1 Register bit definitions */
#define R_RMAC_MRMAC1_MAL_SHIFT                   (0)  /* MAC Address Lower Part */
#define R_RMAC_MRMAC1_MAL_MASK                    0xffffffff

/* MRAFC Register bit definitions */
#define R_RMAC_MRAFC_UCENE                        (1 << 0)  /* Unicast Reception Enable E-Frames */

#define R_RMAC_MRAFC_MCENE                        (1 << 1)  /* Multicast Reception Enable E-Frames */

#define R_RMAC_MRAFC_BCENE                        (1 << 2)  /* Broadcast Reception Enable E-Frames */

#define R_RMAC_MRAFC_MSTENE                       (1 << 3)  /* Multicast Storm Filter Reception Enable E-Frames */

#define R_RMAC_MRAFC_BSTENE                       (1 << 4)  /* Broadcast Storm Filter Reception Enable E-Frames */

#define R_RMAC_MRAFC_MCACE                        (1 << 5)  /* Multicast Storm Autoclear E-Frames */

#define R_RMAC_MRAFC_BCACE                        (1 << 6)  /* Broadcast Storm Autoclear E-Frames */

#define R_RMAC_MRAFC_NDAREE                       (1 << 7)  /* Null Destination Address Reception Enable E-Frames */

#define R_RMAC_MRAFC_SDSFREE                      (1 << 8)  /* Same DA and SA Frames Reception Enable E-Frames */

#define R_RMAC_MRAFC_NSAREE                       (1 << 9)  /* Null Source Address Reception Enable E-Frames */

#define R_RMAC_MRAFC_MSAREE                       (1 << 10)  /* Multicast Source Address Reception Enable E-Frames */

#define R_RMAC_MRAFC_UCENP                        (1 << 16)  /* Unicast Reception Enable P-Frames */

#define R_RMAC_MRAFC_MCENP                        (1 << 17)  /* Multicast Reception Enable P-Frames */

#define R_RMAC_MRAFC_BCENP                        (1 << 18)  /* Broadcast Reception Enable P-Frames */

#define R_RMAC_MRAFC_MSTENP                       (1 << 19)  /* Multicast Storm Filter Reception Enable P-Frames */

#define R_RMAC_MRAFC_BSTENP                       (1 << 20)  /* Broadcast Storm Filter Reception Enable P-Frames */

#define R_RMAC_MRAFC_MCACP                        (1 << 21)  /* Multicast Storm Autoclear P-Frames */

#define R_RMAC_MRAFC_BCACP                        (1 << 22)  /* Broadcast Storm Autoclear P-Frames */

#define R_RMAC_MRAFC_NDAREP                       (1 << 23)  /* Null Destination Address Reception Enable P-Frames */

#define R_RMAC_MRAFC_SDSFREP                      (1 << 24)  /* Same DA and SA Frames Reception Enable P-Frames */

#define R_RMAC_MRAFC_NSAREP                       (1 << 25)  /* Null Source Address Reception Enable P-Frames */

#define R_RMAC_MRAFC_MSAREP                       (1 << 26)  /* Multicast Source Address Reception Enable P-Frames */

/* MRSCE Register bit definitions */
#define R_RMAC_MRSCE_CMFE_SHIFT                   (0)  /* Consecutive Multicast Frame Reception Count Setting for E-Frames */
#define R_RMAC_MRSCE_CMFE_MASK                    0xffff

#define R_RMAC_MRSCE_CBFE_SHIFT                   (16)  /* Consecutive Broadcast Frame Reception Count Setting for E-Frames */
#define R_RMAC_MRSCE_CBFE_MASK                    0xffff0000

/* MRSCP Register bit definitions */
#define R_RMAC_MRSCP_CMFP_SHIFT                   (0)  /* Consecutive Multicast Frame Reception Count Setting for P-Frames */
#define R_RMAC_MRSCP_CMFP_MASK                    0xffff

#define R_RMAC_MRSCP_CBFP_SHIFT                   (16)  /* Consecutive Broadcast Frame Reception Count Setting for P-Frames */
#define R_RMAC_MRSCP_CBFP_MASK                    0xffff0000

/* MRSCC Register bit definitions */
#define R_RMAC_MRSCC_MSCCE                        (1 << 0)  /* Multicast Storm Counter Clear E-Frames */

#define R_RMAC_MRSCC_BSCCE                        (1 << 1)  /* Broadcast Storm Counter Clear E-Frames */

#define R_RMAC_MRSCC_MSCCP                        (1 << 16)  /* Multicast Storm Counter Clear P-Frames */

#define R_RMAC_MRSCC_BSCCP                        (1 << 17)  /* Broadcast Storm Counter Clear P-Frames */

/* MRFSCE Register bit definitions */
#define R_RMAC_MRFSCE_EMXS_SHIFT                  (0)  /* E-Frame Maximum Size */
#define R_RMAC_MRFSCE_EMXS_MASK                   0xffff

#define R_RMAC_MRFSCE_EMNS_SHIFT                  (16)  /* E-Frame Minimum Size */
#define R_RMAC_MRFSCE_EMNS_MASK                   0xffff0000

/* MRFSCP Register bit definitions */
#define R_RMAC_MRFSCP_PMXS_SHIFT                  (0)  /* P-Frame Maximum Size */
#define R_RMAC_MRFSCP_PMXS_MASK                   0xffff

#define R_RMAC_MRFSCP_PMNS_SHIFT                  (16)  /* P-Frame Minimum Size */
#define R_RMAC_MRFSCP_PMNS_MASK                   0xffff0000

/* MTRC Register bit definitions */
#define R_RMAC_MTRC_TRHFME0                       (1 << 0)  /* Timestamp Reception Hardware Filter Match Enable n (n = 0 to 1) */

#define R_RMAC_MTRC_TRHFME1                       (1 << 1)  /* Timestamp Reception Hardware Filter Match Enable n (n = 0 to 1) */

#define R_RMAC_MTRC_TRDDE                         (1 << 24)  /* Timestamp Reception Default Disable E-Frame */

#define R_RMAC_MTRC_TRDDP                         (1 << 25)  /* Timestamp Reception Default Disable P-Frame */

#define R_RMAC_MTRC_TCTSE                         (1 << 26)  /* Timestamp Capture on TX Side E-Frame */

#define R_RMAC_MTRC_TCTSP                         (1 << 27)  /* Timestamp Capture on TX Side P-Frame */

#define R_RMAC_MTRC_DTN                           (1 << 28)  /* Default Timer Number */

/* MRPFM Register bit definitions */
#define R_RMAC_MRPFM_PTCA                         (1 << 0)  /* Pause Time Counting Active */

#define R_RMAC_MRPFM_PFCTCA0                      (1 << 16)  /* PFC Time Counting Active n (n = 0 to 7) */

#define R_RMAC_MRPFM_PFCTCA1                      (1 << 17)  /* PFC Time Counting Active n (n = 0 to 7) */

#define R_RMAC_MRPFM_PFCTCA2                      (1 << 18)  /* PFC Time Counting Active n (n = 0 to 7) */

#define R_RMAC_MRPFM_PFCTCA3                      (1 << 19)  /* PFC Time Counting Active n (n = 0 to 7) */

#define R_RMAC_MRPFM_PFCTCA4                      (1 << 20)  /* PFC Time Counting Active n (n = 0 to 7) */

#define R_RMAC_MRPFM_PFCTCA5                      (1 << 21)  /* PFC Time Counting Active n (n = 0 to 7) */

#define R_RMAC_MRPFM_PFCTCA6                      (1 << 22)  /* PFC Time Counting Active n (n = 0 to 7) */

#define R_RMAC_MRPFM_PFCTCA7                      (1 << 23)  /* PFC Time Counting Active n (n = 0 to 7) */

#define R_RMAC_MRPFM_PFCTCA_SHIFT                 (16)  /* PFCTCA */
#define R_RMAC_MRPFM_PFCTCA_MASK                  0xff0000

/* MPFC Register bit definitions */
#define R_RMAC_MPFC_PFBN_SHIFT                    (0)  /* PTP Filtering Byte Number */
#define R_RMAC_MPFC_PFBN_MASK                     0xff

#define R_RMAC_MPFC_PFBV_SHIFT                    (8)  /* PTP Filtering Byte Value */
#define R_RMAC_MPFC_PFBV_MASK                     0xff00

#define R_RMAC_MPFC_TEF1_TO_TEF0_SHIFT            (16)  /* Timer Enable for Filtering n (n = 0 to 1) */
#define R_RMAC_MPFC_TEF1_TO_TEF0_MASK             0x30000

/* MLVC Register bit definitions */
#define R_RMAC_MLVC_LVT_SHIFT                     (0)  /* Link Verification Timer */
#define R_RMAC_MLVC_LVT_MASK                      0x7f

#define R_RMAC_MLVC_PASE                          (1 << 8)  /* Preemption Auto Response Enable */

#define R_RMAC_MLVC_PLV                           (1 << 16)  /* Preemption Link Verification */

/* MEEEC Register bit definitions */
#define R_RMAC_MEEEC_LPITR                        (1 << 0)  /* LPI Transmit Request */

/* MLBC Register bit definitions */
#define R_RMAC_MLBC_LBME                          (1 << 0)  /* Loopback Mode Enable */

/* MEIS Register bit definitions */
#define R_RMAC_MEIS_TSLS                          (1 << 0)  /* Transmission Stream Lost Status Flag */

#define R_RMAC_MEIS_PRES                          (1 << 2)  /* Pause or PFC Frame Reception Error Status Flag */

#define R_RMAC_MEIS_PFRROS                        (1 << 3)  /* Pause or PFC Frame Retransmit Retry Over Status Flag */

#define R_RMAC_MEIS_FCDS                          (1 << 4)  /* False Carrier Detection Status Flag */

#define R_RMAC_MEIS_TCES                          (1 << 5)  /* TX CRC Error Status Flag */

#define R_RMAC_MEIS_TBCIS                         (1 << 6)  /* TX Bad CRC Insertion Status Flag */

#define R_RMAC_MEIS_BFES                          (1 << 7)  /* Bad Fragment Error Status Flag */

#define R_RMAC_MEIS_FCES                          (1 << 8)  /* Frame Count Error Status Flag */

#define R_RMAC_MEIS_REOES                         (1 << 9)  /* E-Frame Overflow Error Status Flag */

#define R_RMAC_MEIS_RPOES                         (1 << 10)  /* P-Frame Overflow Error Status Flag */

#define R_RMAC_MEIS_CTLES1_TO_CTLES0_SHIFT        (12)  /* Captured Timestamp Lost Error Status Flag n (n = 0 to 1) */
#define R_RMAC_MEIS_CTLES1_TO_CTLES0_MASK         0x3000

#define R_RMAC_MEIS_PDES                          (1 << 20)  /* PHY Data Error Status Flag */

#define R_RMAC_MEIS_PNAES                         (1 << 21)  /* PHY Nibble Alignment Error Status Flag */

#define R_RMAC_MEIS_FCMCES                        (1 << 22)  /* FCS/mCRC Error Status Flag */

#define R_RMAC_MEIS_FFMES                         (1 << 23)  /* Final Fragment Missing Error Status Flag */

#define R_RMAC_MEIS_CFCES                         (1 << 24)  /* C Fragment Count Error Status Flag */

#define R_RMAC_MEIS_FRCES                         (1 << 25)  /* Fragment Count Error Status Flag */

#define R_RMAC_MEIS_RPOOMS                        (1 << 26)  /* Reception Partially out of Operation Mode Status Flag */

#define R_RMAC_MEIS_FFS                           (1 << 27)  /* Frame Filtered Status Flag */

#define R_RMAC_MEIS_FUES                          (1 << 28)  /* Undersize Error Status Flag */

#define R_RMAC_MEIS_FOES                          (1 << 29)  /* Oversize Error Status Flag */

#define R_RMAC_MEIS_TIES                          (1 << 1)  /* TIES */

#define R_RMAC_MEIS_RPCRES                        (1 << 11)  /* RPCRES */

#define R_RMAC_MEIS_CTLES0                        (1 << 12)  /* CTLES0 */

#define R_RMAC_MEIS_CTLES1                        (1 << 13)  /* CTLES1 */

/* MEIE Register bit definitions */
#define R_RMAC_MEIE_TSLE                          (1 << 0)  /* Transmission Stream Lost Enable */

#define R_RMAC_MEIE_PREE                          (1 << 2)  /* Pause or PFC Frame Reception Error Enable */

#define R_RMAC_MEIE_PFRROE                        (1 << 3)  /* Pause or PFC Frame Retransmit Retry Over Enable */

#define R_RMAC_MEIE_FCDE                          (1 << 4)  /* False Carrier Detection Enable */

#define R_RMAC_MEIE_TCEE                          (1 << 5)  /* Tx CRC Error Enable */

#define R_RMAC_MEIE_TBCIE                         (1 << 6)  /* TX Bad CRC Insertion Enable */

#define R_RMAC_MEIE_BFEE                          (1 << 7)  /* Bad Fragment Error Enable */

#define R_RMAC_MEIE_FCEE                          (1 << 8)  /* Frame Count Error Enable */

#define R_RMAC_MEIE_REOEE                         (1 << 9)  /* E-Frame Overflow Error Enable */

#define R_RMAC_MEIE_RPOEE                         (1 << 10)  /* P-Frame Overflow Error Enable */

#define R_RMAC_MEIE_CTLEE1_TO_CTLEE0_SHIFT        (12)  /* Captured Timestamp Lost Error Enable n (n = 0 to 1) */
#define R_RMAC_MEIE_CTLEE1_TO_CTLEE0_MASK         0x3000

#define R_RMAC_MEIE_PDEE                          (1 << 20)  /* PHY Data Error Enable */

#define R_RMAC_MEIE_PNAEE                         (1 << 21)  /* PHY Nibble Alignment Error Enable */

#define R_RMAC_MEIE_FCMCEE                        (1 << 22)  /* FCS/mCRC Error Enable */

#define R_RMAC_MEIE_FFMEE                         (1 << 23)  /* Final Fragment Missing Error Enable */

#define R_RMAC_MEIE_CFCEE                         (1 << 24)  /* C Fragment Count Error Enable */

#define R_RMAC_MEIE_FRCEE                         (1 << 25)  /* Fragment Count Error Enable */

#define R_RMAC_MEIE_RPOOME                        (1 << 26)  /* Reception Partially out of Operation Mode Enable */

#define R_RMAC_MEIE_FFE                           (1 << 27)  /* Frame Filtered Enable */

#define R_RMAC_MEIE_FUEE                          (1 << 28)  /* Undersize Error Enable */

#define R_RMAC_MEIE_FOEE                          (1 << 29)  /* Oversize Error Enable */

#define R_RMAC_MEIE_TIEE                          (1 << 1)  /* TIEE */

#define R_RMAC_MEIE_PMSEE                         (1 << 2)  /* PMSEE */

#define R_RMAC_MEIE_RPCREE                        (1 << 11)  /* RPCREE */

#define R_RMAC_MEIE_CTLEE0                        (1 << 12)  /* CTLEE0 */

#define R_RMAC_MEIE_CTLEE1                        (1 << 13)  /* CTLEE1 */

/* MEID Register bit definitions */
#define R_RMAC_MEID_TSLD                          (1 << 0)  /* Transmission Stream Lost Disable */

#define R_RMAC_MEID_PRED                          (1 << 2)  /* Pause or PFC Frame Reception Error Disable */

#define R_RMAC_MEID_PFRROD                        (1 << 3)  /* Pause or PFC Frame Retransmit Retry Over Disable */

#define R_RMAC_MEID_FCDD                          (1 << 4)  /* False Carrier Detection Disable */

#define R_RMAC_MEID_TCED                          (1 << 5)  /* Tx CRC Error Disable */

#define R_RMAC_MEID_TBCID                         (1 << 6)  /* TX Bad CRC Insertion Disable */

#define R_RMAC_MEID_BFED                          (1 << 7)  /* Bad Fragment Error Disable */

#define R_RMAC_MEID_FCED                          (1 << 8)  /* Frame Count Error Disable */

#define R_RMAC_MEID_REOED                         (1 << 9)  /* E-Frame Overflow Error Disable */

#define R_RMAC_MEID_RPOED                         (1 << 10)  /* P-Frame Overflow Error Disable */

#define R_RMAC_MEID_CTLED1_TO_CTLED0_SHIFT        (12)  /* Captured Timestamp Lost Error Disable n (n = 0 to 1) */
#define R_RMAC_MEID_CTLED1_TO_CTLED0_MASK         0x3000

#define R_RMAC_MEID_PDED                          (1 << 20)  /* PHY Data Error Disable */

#define R_RMAC_MEID_PNAED                         (1 << 21)  /* PHY Nibble Alignment Error Disable */

#define R_RMAC_MEID_FCMCED                        (1 << 22)  /* FCS/mCRC Error Disable */

#define R_RMAC_MEID_FFMED                         (1 << 23)  /* Final Fragment Missing Error Disable */

#define R_RMAC_MEID_CFCED                         (1 << 24)  /* C Fragment Count Error Disable */

#define R_RMAC_MEID_FRCED                         (1 << 25)  /* Fragment Count Error Disable */

#define R_RMAC_MEID_RPOOMD                        (1 << 26)  /* Reception Partially out of Operation Mode Disable */

#define R_RMAC_MEID_FFD                           (1 << 27)  /* Frame Filtered Disable */

#define R_RMAC_MEID_FUED                          (1 << 28)  /* Undersize Error Disable */

#define R_RMAC_MEID_FOED                          (1 << 29)  /* Oversize Error Disable */

#define R_RMAC_MEID_TIED                          (1 << 1)  /* TIED */

#define R_RMAC_MEID_RPCRED                        (1 << 11)  /* RPCRED */

#define R_RMAC_MEID_CTLED0                        (1 << 12)  /* CTLED0 */

#define R_RMAC_MEID_CTLED1                        (1 << 13)  /* CTLED1 */

/* MMIS0 Register bit definitions */
#define R_RMAC_MMIS0_PLSCS                        (1 << 0)  /* PHY Link Signal Change Status Flag */

#define R_RMAC_MMIS0_PIDS                         (1 << 1)  /* PHY Interrupt Detection Status Flag */

#define R_RMAC_MMIS0_LVSS                         (1 << 2)  /* Link Verification Succeed Status Flag */

#define R_RMAC_MMIS0_LVFS                         (1 << 3)  /* Link Verification Failed Status Flag */

#define R_RMAC_MMIS0_VFRS                         (1 << 4)  /* Verify Frame Reception Status Flag */

#define R_RMAC_MMIS0_ANDETS                       (1 << 6)  /* ANDETS */

#define R_RMAC_MMIS0_XLFDS                        (1 << 8)  /* XLFDS */

#define R_RMAC_MMIS0_XLFES                        (1 << 9)  /* XLFES */

#define R_RMAC_MMIS0_XLFSDS                       (1 << 10)  /* XLFSDS */

#define R_RMAC_MMIS0_XRFSDS                       (1 << 11)  /* XRFSDS */

#define R_RMAC_MMIS0_XLISDS                       (1 << 12)  /* XLISDS */

/* MMIE0 Register bit definitions */
#define R_RMAC_MMIE0_PLSCE                        (1 << 0)  /* PHY Link Signal Change Enable */

#define R_RMAC_MMIE0_PIDE                         (1 << 1)  /* PHY Interrupt Detection Enable */

#define R_RMAC_MMIE0_LVSE                         (1 << 2)  /* Link Verification Succeed Enable */

#define R_RMAC_MMIE0_LVFE                         (1 << 3)  /* Link Verification Failed Enable */

#define R_RMAC_MMIE0_VFRE                         (1 << 4)  /* Verify Frame Reception Enable */

#define R_RMAC_MMIE0_ANDETE                       (1 << 6)  /* ANDETE */

#define R_RMAC_MMIE0_XLFDE                        (1 << 8)  /* XLFDE */

#define R_RMAC_MMIE0_XLFEE                        (1 << 9)  /* XLFEE */

#define R_RMAC_MMIE0_XLFSDE                       (1 << 10)  /* XLFSDE */

#define R_RMAC_MMIE0_XRFSDE                       (1 << 11)  /* XRFSDE */

#define R_RMAC_MMIE0_XLISDE                       (1 << 12)  /* XLISDE */

/* MMID0 Register bit definitions */
#define R_RMAC_MMID0_PLSCD                        (1 << 0)  /* PHY Link Signal Change Disable */

#define R_RMAC_MMID0_PIDD                         (1 << 1)  /* PHY Interrupt Detection Disable */

#define R_RMAC_MMID0_LVSD                         (1 << 2)  /* Link Verification Succeed Disable */

#define R_RMAC_MMID0_LVFD                         (1 << 3)  /* Link Verification Failed Disable */

#define R_RMAC_MMID0_VFRD                         (1 << 4)  /* Verify Frame Reception Disable */

#define R_RMAC_MMID0_ANDETD                       (1 << 6)  /* ANDETD */

#define R_RMAC_MMID0_XLFDD                        (1 << 8)  /* XLFDD */

#define R_RMAC_MMID0_XLFED                        (1 << 9)  /* XLFED */

#define R_RMAC_MMID0_XLFSDD                       (1 << 10)  /* XLFSDD */

#define R_RMAC_MMID0_XRFSDD                       (1 << 11)  /* XRFSDD */

#define R_RMAC_MMID0_XLISDD                       (1 << 12)  /* XLISDD */

/* MMIS1 Register bit definitions */
#define R_RMAC_MMIS1_PRACS                        (1 << 0)  /* PHY Read Access Completed Status Flag */

#define R_RMAC_MMIS1_PWACS                        (1 << 1)  /* PHY Write Access Completed Status Flag */

#define R_RMAC_MMIS1_PAACS                        (1 << 2)  /* PHY Address Access Completed Status Flag */

#define R_RMAC_MMIS1_PPRACS                       (1 << 3)  /* PHY Post-Read Access Completed Status Flag */

/* MMIE1 Register bit definitions */
#define R_RMAC_MMIE1_PRACE                        (1 << 0)  /* PHY Read Access Completed Enable */

#define R_RMAC_MMIE1_PWACE                        (1 << 1)  /* PHY Write Access Completed Enable */

#define R_RMAC_MMIE1_PAACE                        (1 << 2)  /* PHY Address Access Completed Enable */

#define R_RMAC_MMIE1_PPRACE                       (1 << 3)  /* PHY Post-Read Access Completed Enable */

/* MMID1 Register bit definitions */
#define R_RMAC_MMID1_PRACD                        (1 << 0)  /* PHY Read Access Completed Disable */

#define R_RMAC_MMID1_PWACD                        (1 << 1)  /* PHY Write Access Completed Disable */

#define R_RMAC_MMID1_PAACD                        (1 << 2)  /* PHY Address Access Completed Disable */

#define R_RMAC_MMID1_PPRACD                       (1 << 3)  /* PHY Post-Read Access Completed Disable */

/* MMIS2 Register bit definitions */
#define R_RMAC_MMIS2_MPDIS                        (1 << 0)  /* Magic Packet Detection Interrupt Status Flag */

#define R_RMAC_MMIS2_LPIAIS                       (1 << 1)  /* LPI Assertion Interrupt Status Flag */

#define R_RMAC_MMIS2_LPIDIS                       (1 << 2)  /* LPI De-Assertion Interrupt Status Flag */

/* MMIE2 Register bit definitions */
#define R_RMAC_MMIE2_MPDIE                        (1 << 0)  /* Magic Packet Detection Interrupt Enable */

#define R_RMAC_MMIE2_LPIAIE                       (1 << 1)  /* LPI Assertion Interrupt Enable */

#define R_RMAC_MMIE2_LPIDIE                       (1 << 2)  /* LPI De-Assertion Interrupt Enable */

/* MMID2 Register bit definitions */
#define R_RMAC_MMID2_MPDID                        (1 << 0)  /* Magic Packet Detection Interrupt Disable */

#define R_RMAC_MMID2_LPIAID                       (1 << 1)  /* LPI Assertion Interrupt Disable */

#define R_RMAC_MMID2_LPIDID                       (1 << 2)  /* LPI De-Assertion Interrupt Disable */

/* MMPFTCT Register bit definitions */
#define R_RMAC_MMPFTCT_MPFTC_SHIFT                (0)  /* Manual Pause frame Transmit Counter */
#define R_RMAC_MMPFTCT_MPFTC_MASK                 0xffff

/* MAPFTCT Register bit definitions */
#define R_RMAC_MAPFTCT_APFTC_SHIFT                (0)  /* Automatic pause Frame Counter */
#define R_RMAC_MAPFTCT_APFTC_MASK                 0xffff

/* MPFRCT Register bit definitions */
#define R_RMAC_MPFRCT_PFRC_SHIFT                  (0)  /* Pause Frame Receive Counter */
#define R_RMAC_MPFRCT_PFRC_MASK                   0xffff

/* MFCICT Register bit definitions */
#define R_RMAC_MFCICT_FCIC_SHIFT                  (0)  /* False Carrier Indication Counter */
#define R_RMAC_MFCICT_FCIC_MASK                   0xffff

/* MEEECT Register bit definitions */
#define R_RMAC_MEEECT_EEERC_SHIFT                 (0)  /* Energy Efficient Ethernet Receive Counter */
#define R_RMAC_MEEECT_EEERC_MASK                  0xffff

/* MMPCFTCT Register bit definitions */
#define R_RMAC_MMPCFTCT_MPCFCTC_SHIFT             (0)  /* Manual PFC frame Transmit Counter */
#define R_RMAC_MMPCFTCT_MPCFCTC_MASK              0xffff

/* MAPCFTCT Register bit definitions */
#define R_RMAC_MAPCFTCT_APCFCTC_SHIFT             (0)  /* Automatic PFC Frame Counter */
#define R_RMAC_MAPCFTCT_APCFCTC_MASK              0xffff

/* MPCFRCT Register bit definitions */
#define R_RMAC_MPCFRCT_PCFCRC_SHIFT               (0)  /* PFC Frame Receive Counter */
#define R_RMAC_MPCFRCT_PCFCRC_MASK                0xffff

/* MROVFC Register bit definitions */
#define R_RMAC_MROVFC_ROVFC_SHIFT                 (0)  /* Receive overflow counter */
#define R_RMAC_MROVFC_ROVFC_MASK                  0xffffffff

/* MRGFCE Register bit definitions */
#define R_RMAC_MRGFCE_RGFNE_SHIFT                 (0)  /* Received good frame number E-frames */
#define R_RMAC_MRGFCE_RGFNE_MASK                  0xffffffff

/* MRGFCP Register bit definitions */
#define R_RMAC_MRGFCP_GFNP_SHIFT                  (0)  /* Received good frame number P-frames */
#define R_RMAC_MRGFCP_GFNP_MASK                   0xffffffff

#define R_RMAC_MRGFCP_RGFNP_SHIFT                 (0)  /* RGFNP */
#define R_RMAC_MRGFCP_RGFNP_MASK                  0xffffffff

/* MRBFC Register bit definitions */
#define R_RMAC_MRBFC_RBFN_SHIFT                   (0)  /* Received good broadcast frame number */
#define R_RMAC_MRBFC_RBFN_MASK                    0xffffffff

/* MRMFC Register bit definitions */
#define R_RMAC_MRMFC_RMFN_SHIFT                   (0)  /* Received good multicast frame number */
#define R_RMAC_MRMFC_RMFN_MASK                    0xffffffff

/* MRUFC Register bit definitions */
#define R_RMAC_MRUFC_RUFN_SHIFT                   (0)  /* Received good unicast frame number */
#define R_RMAC_MRUFC_RUFN_MASK                    0xffffffff

/* MRPEFC Register bit definitions */
#define R_RMAC_MRPEFC_RPEFN_SHIFT                 (0)  /* Received PHY error frame number */
#define R_RMAC_MRPEFC_RPEFN_MASK                  0xffff

/* MRNEFC Register bit definitions */
#define R_RMAC_MRNEFC_RNEFN_SHIFT                 (0)  /* Received nibble error frame number */
#define R_RMAC_MRNEFC_RNEFN_MASK                  0xffff

/* MRFMEFC Register bit definitions */
#define R_RMAC_MRFMEFC_RFMEFN_SHIFT               (0)  /* Received FCS/mCRC error frame number */
#define R_RMAC_MRFMEFC_RFMEFN_MASK                0xffffffff

/* MRFFMEFC Register bit definitions */
#define R_RMAC_MRFFMEFC_RFFMEFN_SHIFT             (0)  /* Received final fragment missing error frame number */
#define R_RMAC_MRFFMEFC_RFFMEFN_MASK              0xffff

/* MRCFCEFC Register bit definitions */
#define R_RMAC_MRCFCEFC_RCFCEFN_SHIFT             (0)  /* Received C-fragment count error frame number */
#define R_RMAC_MRCFCEFC_RCFCEFN_MASK              0xffff

/* MRFCEFC Register bit definitions */
#define R_RMAC_MRFCEFC_RFCEFN_SHIFT               (0)  /* Received fragment count error frame number */
#define R_RMAC_MRFCEFC_RFCEFN_MASK                0xffff

/* MRRCFEFC Register bit definitions */
#define R_RMAC_MRRCFEFC_RRCFEFN_SHIFT             (0)  /* Received RMAC filter error frame number */
#define R_RMAC_MRRCFEFC_RRCFEFN_MASK              0xffff

/* MRFC Register bit definitions */
#define R_RMAC_MRFC_RFN_SHIFT                     (0)  /* Received frame number */
#define R_RMAC_MRFC_RFN_MASK                      0xffffffff

/* MRGUEFC Register bit definitions */
#define R_RMAC_MRGUEFC_RUEFN_SHIFT                (0)  /* Received good undersize error frame number */
#define R_RMAC_MRGUEFC_RUEFN_MASK                 0xffffffff

/* MRBUEFC Register bit definitions */
#define R_RMAC_MRBUEFC_RUEFN_SHIFT                (0)  /* Received bad undersize error frame number */
#define R_RMAC_MRBUEFC_RUEFN_MASK                 0xffffffff

/* MRGOEFC Register bit definitions */
#define R_RMAC_MRGOEFC_RGOEFN_SHIFT               (0)  /* Received good oversize error frame number */
#define R_RMAC_MRGOEFC_RGOEFN_MASK                0xffffffff

/* MRBOEFC Register bit definitions */
#define R_RMAC_MRBOEFC_RBOEFN_SHIFT               (0)  /* Received bad oversize error frame number */
#define R_RMAC_MRBOEFC_RBOEFN_MASK                0xffffffff

/* MRXBCEU Register bit definitions */
#define R_RMAC_MRXBCEU_RBNEU_SHIFT                (0)  /* Received byte number E-frames upper side */
#define R_RMAC_MRXBCEU_RBNEU_MASK                 0xffffffff

/* MRXBCEL Register bit definitions */
#define R_RMAC_MRXBCEL_RBNEL_SHIFT                (0)  /* Received byte number E-frames lower side */
#define R_RMAC_MRXBCEL_RBNEL_MASK                 0xffffffff

/* MRXBCPU Register bit definitions */
#define R_RMAC_MRXBCPU_RBNPU_SHIFT                (0)  /* Received byte number P-frames upper side */
#define R_RMAC_MRXBCPU_RBNPU_MASK                 0xffffffff

/* MRXBCPL Register bit definitions */
#define R_RMAC_MRXBCPL_RBNPL_SHIFT                (0)  /* Received byte number P-frames lower side */
#define R_RMAC_MRXBCPL_RBNPL_MASK                 0xffffffff

/* MTGFCE Register bit definitions */
#define R_RMAC_MTGFCE_TGFNE_SHIFT                 (0)  /* Transmitted good frame number E-frames */
#define R_RMAC_MTGFCE_TGFNE_MASK                  0xffffffff

/* MTGFCP Register bit definitions */
#define R_RMAC_MTGFCP_TGFNP_SHIFT                 (0)  /* Transmitted good frame number P-frames */
#define R_RMAC_MTGFCP_TGFNP_MASK                  0xffffffff

/* MTBFC Register bit definitions */
#define R_RMAC_MTBFC_TBFN_SHIFT                   (0)  /* Transmitted broadcast frame number */
#define R_RMAC_MTBFC_TBFN_MASK                    0xffffffff

/* MTMFC Register bit definitions */
#define R_RMAC_MTMFC_TMFN_SHIFT                   (0)  /* Transmitted multicast frame number */
#define R_RMAC_MTMFC_TMFN_MASK                    0xffffffff

/* MTUFC Register bit definitions */
#define R_RMAC_MTUFC_TUFN_SHIFT                   (0)  /* Transmitted unicast frame number */
#define R_RMAC_MTUFC_TUFN_MASK                    0xffffffff

/* MTEFC Register bit definitions */
#define R_RMAC_MTEFC_TEFN_SHIFT                   (0)  /* Transmitted error frame number */
#define R_RMAC_MTEFC_TEFN_MASK                    0xffff

/* MTXBCEU Register bit definitions */
#define R_RMAC_MTXBCEU_TBNEU_SHIFT                (0)  /* Transmitted byte number E-frames upper side */
#define R_RMAC_MTXBCEU_TBNEU_MASK                 0xffffffff

/* MTXBCEL Register bit definitions */
#define R_RMAC_MTXBCEL_TBNEL_SHIFT                (0)  /* Transmitted byte number E-frames lower side */
#define R_RMAC_MTXBCEL_TBNEL_MASK                 0xffffffff

/* MTXBCPU Register bit definitions */
#define R_RMAC_MTXBCPU_TBNPU_SHIFT                (0)  /* Transmitted byte number P-frames upper side */
#define R_RMAC_MTXBCPU_TBNPU_MASK                 0xffffffff

/* MTXBCPL Register bit definitions */
#define R_RMAC_MTXBCPL_TBNPL_SHIFT                (0)  /* Transmitted byte number P-frames lower side */
#define R_RMAC_MTXBCPL_TBNPL_MASK                 0xffffffff


/* Maximum number of channels */

#define RMAC_MAX_CHANNELS    16

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_RMAC_H */
