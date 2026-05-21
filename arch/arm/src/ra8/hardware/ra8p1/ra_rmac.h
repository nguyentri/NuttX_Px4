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

#define R_RMAC_MPSM_OFFSET                        0x00000000  /* MAC PHY Station Management Register (MPSM) */
#define R_RMAC_MPIC_OFFSET                        0x00000004  /* MAC PHY Interfaces Configuration Register (MPIC) */
#define R_RMAC_MPIM_OFFSET                        0x00000008  /* MAC PHY Interfaces Monitoring Register (MPIM) */
#define R_RMAC_MIOC_OFFSET                        0x00000010  /* RMAC IO Configuration Registers Register (MIOC) */
#define R_RMAC_MTFFC_OFFSET                       0x00000020  /* MAC Transmission Frame Format Configuration Register (MTFFC) */
#define R_RMAC_MTPFC_OFFSET                       0x00000024  /* MAC Transmission Pause or PFC Frame Configuration Register (MTPFC) */
#define R_RMAC_MTPFC2_OFFSET                      0x00000028  /* MAC Transmission Pause or PFC Frame configuration2 Register (MTPFC2) */
#define R_RMAC_MTPFC30_OFFSET                     0x00000030  /* MAC Transmission Pause or PFC Frame Configuration Register 3 (MTPFC3t) (t = 0, 1) */
#define R_RMAC_MTPFC31_OFFSET                     0x00000034  /* MAC Transmission Pause or PFC Frame Configuration Register 3 (MTPFC3t) (t = 0, 1) */
#define R_RMAC_MTATC0_OFFSET                      0x00000050  /* MAC Transmission Automatic Timestamp Configuration Register (MTATCt) (t = 0, 1) */
#define R_RMAC_MTATC1_OFFSET                      0x00000054  /* MAC Transmission Automatic Timestamp Configuration Register (MTATCt) (t = 0, 1) */
#define R_RMAC_MTIM_OFFSET                        0x00000060  /* MAC Transmission Interfaces Monitoring Register (MTIM) */
#define R_RMAC_MRGC_OFFSET                        0x00000080  /* MAC Reception General Configuration Register (MRGC) */
#define R_RMAC_MRMAC0_OFFSET                      0x00000084  /* MAC Reception MAC Address Configuration Register 0 (MRMAC0) */
#define R_RMAC_MRMAC1_OFFSET                      0x00000088  /* MAC Reception MAC Address Configuration Register 1 (MRMAC1) */
#define R_RMAC_MRAFC_OFFSET                       0x0000008c  /* MAC Reception Address Filter Configuration Register (MRAFC) */
#define R_RMAC_MRSCE_OFFSET                       0x00000090  /* MAC Reception Storm Configuration for e-Frames Register (MRSCE) */
#define R_RMAC_MRSCP_OFFSET                       0x00000094  /* MAC Reception Storm Configuration for p-Frames Register (MRSCP) */
#define R_RMAC_MRSCC_OFFSET                       0x00000098  /* MAC Reception Storm Counter Configuration Register (MRSCC) */
#define R_RMAC_MRFSCE_OFFSET                      0x0000009c  /* MAC Reception Frame Size Configuration for e-Frames Register (MRFSCE) */
#define R_RMAC_MRFSCP_OFFSET                      0x000000a0  /* MAC Reception Frame Size Configuration for p-Frames Register (MRFSCP) */
#define R_RMAC_MTRC_OFFSET                        0x000000a4  /* MAC Timestamp Reception Configuration Register (MTRC) */
#define R_RMAC_MRPFM_OFFSET                       0x000000ac  /* MAC Reception Pause or PFC Frame Monitoring Register (MRPFM) */
#define R_RMAC_MPFC0_OFFSET                       0x00000100  /* MAC PTP Filtering Register Configuration Register t (MPFCt) (t = 0 to 15) */
#define R_RMAC_MPFC1_OFFSET                       0x00000104  /* MAC PTP Filtering Register Configuration Register t (MPFCt) (t = 0 to 15) */
#define R_RMAC_MPFC2_OFFSET                       0x00000108  /* MAC PTP Filtering Register Configuration Register t (MPFCt) (t = 0 to 15) */
#define R_RMAC_MPFC3_OFFSET                       0x0000010c  /* MAC PTP Filtering Register Configuration Register t (MPFCt) (t = 0 to 15) */
#define R_RMAC_MPFC4_OFFSET                       0x00000110  /* MAC PTP Filtering Register Configuration Register t (MPFCt) (t = 0 to 15) */
#define R_RMAC_MPFC5_OFFSET                       0x00000114  /* MAC PTP Filtering Register Configuration Register t (MPFCt) (t = 0 to 15) */
#define R_RMAC_MPFC6_OFFSET                       0x00000118  /* MAC PTP Filtering Register Configuration Register t (MPFCt) (t = 0 to 15) */
#define R_RMAC_MPFC7_OFFSET                       0x0000011c  /* MAC PTP Filtering Register Configuration Register t (MPFCt) (t = 0 to 15) */
#define R_RMAC_MPFC8_OFFSET                       0x00000120  /* MAC PTP Filtering Register Configuration Register t (MPFCt) (t = 0 to 15) */
#define R_RMAC_MPFC9_OFFSET                       0x00000124  /* MAC PTP Filtering Register Configuration Register t (MPFCt) (t = 0 to 15) */
#define R_RMAC_MPFC10_OFFSET                      0x00000128  /* MAC PTP Filtering Register Configuration Register t (MPFCt) (t = 0 to 15) */
#define R_RMAC_MPFC11_OFFSET                      0x0000012c  /* MAC PTP Filtering Register Configuration Register t (MPFCt) (t = 0 to 15) */
#define R_RMAC_MPFC12_OFFSET                      0x00000130  /* MAC PTP Filtering Register Configuration Register t (MPFCt) (t = 0 to 15) */
#define R_RMAC_MPFC13_OFFSET                      0x00000134  /* MAC PTP Filtering Register Configuration Register t (MPFCt) (t = 0 to 15) */
#define R_RMAC_MPFC14_OFFSET                      0x00000138  /* MAC PTP Filtering Register Configuration Register t (MPFCt) (t = 0 to 15) */
#define R_RMAC_MPFC15_OFFSET                      0x0000013c  /* MAC PTP Filtering Register Configuration Register t (MPFCt) (t = 0 to 15) */
#define R_RMAC_MLVC_OFFSET                        0x00000180  /* MAC Link Verification Configuration Register (MLVC) */
#define R_RMAC_MEEEC_OFFSET                       0x00000184  /* MAC Energy Efficient Ethernet Configuration Register (MEEEC) */
#define R_RMAC_MLBC_OFFSET                        0x00000188  /* MAC Loopback Configuration Register (MLBC) */
#define R_RMAC_MXGMIIC_OFFSET                     0x00000190  /* XGMII Configuration Register (MXGMIIC) */
#define R_RMAC_MPCH_OFFSET                        0x00000194  /* XGMII PCH Configuration Register (MPCH) */
#define R_RMAC_MANM_OFFSET                        0x0000019c  /* Auto-Negotiation Message Register (MANM) */
#define R_RMAC_MEIS_OFFSET                        0x00000200  /* MAC Error Interrupt Status Register (MEIS) */
#define R_RMAC_MEIE_OFFSET                        0x00000204  /* MAC Error Interrupt Enable Register (MEIE) */
#define R_RMAC_MEID_OFFSET                        0x00000208  /* MAC Error Interrupt Disable Register (MEID) */
#define R_RMAC_MMIS0_OFFSET                       0x00000210  /* MAC Monitoring Interrupt Status Register 0 (MMIS0) */
#define R_RMAC_MMIE0_OFFSET                       0x00000214  /* MAC Monitoring Interrupt Enable Register 0 (MMIE0) */
#define R_RMAC_MMID0_OFFSET                       0x00000218  /* MAC Monitoring Interrupt Disable Register 0 (MMID0) */
#define R_RMAC_MMIS1_OFFSET                       0x00000220  /* MAC Monitoring Interrupt Status Register 1 (MMIS1) */
#define R_RMAC_MMIE1_OFFSET                       0x00000224  /* MAC Monitoring Interrupt Enable Register 1 (MMIE1) */
#define R_RMAC_MMID1_OFFSET                       0x00000228  /* MAC Monitoring Interrupt Disable Register 1 (MMID1) */
#define R_RMAC_MMIS2_OFFSET                       0x00000230  /* MAC Monitoring Interrupt Status Register 2 (MMIS2) */
#define R_RMAC_MMIE2_OFFSET                       0x00000234  /* MAC Monitoring Interrupt Enable Register 2 (MMIE2) */
#define R_RMAC_MMID2_OFFSET                       0x00000238  /* MAC Monitoring Interrupt Disable Register 2 (MMID2) */
#define R_RMAC_MMPFTCT_OFFSET                     0x00000300  /* MAC Manual Pause Frame Transmit Counter Register (MMPFTCT) */
#define R_RMAC_MAPFTCT_OFFSET                     0x00000304  /* MAC Automatic Pause Frame Transmit Counter Register (MAPFTCT) */
#define R_RMAC_MPFRCT_OFFSET                      0x00000308  /* MAC Pause Frame Receive Counter Register (MPFRCT) */
#define R_RMAC_MFCICT_OFFSET                      0x0000030c  /* MAC False Carrier Indication Counter Register (MFCICT) */
#define R_RMAC_MEEECT_OFFSET                      0x00000310  /* MAC Energy Efficient Ethernet Counter Register (MEEECT) */
#define R_RMAC_MMPCFTCT0_OFFSET                   0x00000320  /* MAC Manual PFC Frame Transmit Counter Register (MMPCFTCTt) (t = 0, 1) */
#define R_RMAC_MMPCFTCT1_OFFSET                   0x00000324  /* MAC Manual PFC Frame Transmit Counter Register (MMPCFTCTt) (t = 0, 1) */
#define R_RMAC_MAPCFTCT0_OFFSET                   0x00000330  /* MAC Automatic PFC Frame Transmit Counter Register (MAPCFTCTt) (t = 0, 1) */
#define R_RMAC_MAPCFTCT1_OFFSET                   0x00000334  /* MAC Automatic PFC Frame Transmit Counter Register (MAPCFTCTt) (t = 0, 1) */
#define R_RMAC_MPCFRCT0_OFFSET                    0x00000340  /* Bit	Symbol	Bit Name	Description	R/W */
#define R_RMAC_MPCFRCT1_OFFSET                    0x00000344  /* Bit	Symbol	Bit Name	Description	R/W */
#define R_RMAC_MPCFRCT2_OFFSET                    0x00000348  /* Bit	Symbol	Bit Name	Description	R/W */
#define R_RMAC_MPCFRCT3_OFFSET                    0x0000034c  /* Bit	Symbol	Bit Name	Description	R/W */
#define R_RMAC_MPCFRCT4_OFFSET                    0x00000350  /* Bit	Symbol	Bit Name	Description	R/W */
#define R_RMAC_MPCFRCT5_OFFSET                    0x00000354  /* Bit	Symbol	Bit Name	Description	R/W */
#define R_RMAC_MPCFRCT6_OFFSET                    0x00000358  /* Bit	Symbol	Bit Name	Description	R/W */
#define R_RMAC_MPCFRCT7_OFFSET                    0x0000035c  /* Bit	Symbol	Bit Name	Description	R/W */
#define R_RMAC_MROVFC_OFFSET                      0x00000360  /* Receive Overflow Counter Register (MROVFC) */
#define R_RMAC_MRHCRCEC_OFFSET                    0x00000364  /* Reception Header-CRC(PCH CRC) Error Counter Register (MRHCRCEC) */
#define R_RMAC_MRGFCE_OFFSET                      0x00000408  /* RMAC Received Good Frame Counter E-Frames Register (MRGFCE) */
#define R_RMAC_MRGFCP_OFFSET                      0x0000040c  /* RMAC Received Good Frame Counter P-Frames Register (MRGFCP) */
#define R_RMAC_MRBFC_OFFSET                       0x00000410  /*  Register (MRBFC) */
#define R_RMAC_MRMFC_OFFSET                       0x00000414  /* RMAC Received Good Multicast Frame Counter Register (MRMFC) */
#define R_RMAC_MRUFC_OFFSET                       0x00000418  /* RMAC Received Good Unicast Frame Counter Register (MRUFC) */
#define R_RMAC_MRPEFC_OFFSET                      0x0000041c  /*  Register (MRPEFC) */
#define R_RMAC_MRNEFC_OFFSET                      0x00000420  /*  Register (MRNEFC) */
#define R_RMAC_MRFMEFC_OFFSET                     0x00000424  /*  Register (MRFMEFC) */
#define R_RMAC_MRFFMEFC_OFFSET                    0x00000428  /*  Register (MRFFMEFC) */
#define R_RMAC_MRCFCEFC_OFFSET                    0x0000042c  /*  Register (MRCFCEFC) */
#define R_RMAC_MRFCEFC_OFFSET                     0x00000430  /*  Register (MRFCEFC) */
#define R_RMAC_MRRCFEFC_OFFSET                    0x00000434  /*  Register (MRRCFEFC) */
#define R_RMAC_MRFC_OFFSET                        0x00000438  /*  Register (MRFC) */
#define R_RMAC_MRGUEFC_OFFSET                     0x0000043c  /* RMAC Received Good Undersize Error Frame Count Register (MRGUEFC) */
#define R_RMAC_MRBUEFC_OFFSET                     0x00000440  /* RMAC Received bad Undersize Error Frame Count Register (MRBUEFC) */
#define R_RMAC_MRGOEFC_OFFSET                     0x00000444  /*  Register (MRGOEFC) */
#define R_RMAC_MRBOEFC_OFFSET                     0x00000448  /*  Register (MRBOEFC) */
#define R_RMAC_MRXBCEU_OFFSET                     0x0000044c  /*  Register (MRXBCEU) */
#define R_RMAC_MRXBCEL_OFFSET                     0x00000450  /*  Register (MRXBCEL) */
#define R_RMAC_MRXBCPU_OFFSET                     0x00000454  /*  Register (MRXBCPU) */
#define R_RMAC_MRXBCPL_OFFSET                     0x00000458  /*  Register (MRXBCPL) */
#define R_RMAC_MTGFCE_OFFSET                      0x00000508  /* RMAC Transmitted Good Frame Counter E-Frames Register (MTGFCE) */
#define R_RMAC_MTGFCP_OFFSET                      0x0000050c  /* RMAC Transmitted Good Frame Counter P-Frames Register (MTGFCP) */
#define R_RMAC_MTBFC_OFFSET                       0x00000510  /*  Register (MTBFC) */
#define R_RMAC_MTMFC_OFFSET                       0x00000514  /* RMAC Transmitted Multicast Frame Counter Register (MTMFC) */
#define R_RMAC_MTUFC_OFFSET                       0x00000518  /*  Register (MTUFC) */
#define R_RMAC_MTEFC_OFFSET                       0x0000051c  /*  Register (MTEFC) */
#define R_RMAC_MTXBCEU_OFFSET                     0x00000520  /*  Register (MTXBCEU) */
#define R_RMAC_MTXBCEL_OFFSET                     0x00000524  /*  Register (MTXBCEL) */
#define R_RMAC_MTXBCPU_OFFSET                     0x00000528  /* RMAC Transmitted Byte Counter P-Frames Upper Side Register (MTXBCPU) */
#define R_RMAC_MTXBCPL_OFFSET                     0x0000052c  /* RMAC Transmitted Byte Counter P-Frames Lower Side Register (MTXBCPL) */

/* RMAC Register Addresses */

#define R_RMAC_MPSM(n)                            (R_RMAC_CH_BASE(n) + R_RMAC_MPSM_OFFSET)
#define R_RMAC_MPIC(n)                            (R_RMAC_CH_BASE(n) + R_RMAC_MPIC_OFFSET)
#define R_RMAC_MPIM(n)                            (R_RMAC_CH_BASE(n) + R_RMAC_MPIM_OFFSET)
#define R_RMAC_MIOC(n)                            (R_RMAC_CH_BASE(n) + R_RMAC_MIOC_OFFSET)
#define R_RMAC_MTFFC(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MTFFC_OFFSET)
#define R_RMAC_MTPFC(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MTPFC_OFFSET)
#define R_RMAC_MTPFC2(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MTPFC2_OFFSET)
#define R_RMAC_MTPFC30(n)                         (R_RMAC_CH_BASE(n) + R_RMAC_MTPFC30_OFFSET)
#define R_RMAC_MTPFC31(n)                         (R_RMAC_CH_BASE(n) + R_RMAC_MTPFC31_OFFSET)
#define R_RMAC_MTATC0(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MTATC0_OFFSET)
#define R_RMAC_MTATC1(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MTATC1_OFFSET)
#define R_RMAC_MTIM(n)                            (R_RMAC_CH_BASE(n) + R_RMAC_MTIM_OFFSET)
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
#define R_RMAC_MPFC0(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MPFC0_OFFSET)
#define R_RMAC_MPFC1(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MPFC1_OFFSET)
#define R_RMAC_MPFC2(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MPFC2_OFFSET)
#define R_RMAC_MPFC3(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MPFC3_OFFSET)
#define R_RMAC_MPFC4(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MPFC4_OFFSET)
#define R_RMAC_MPFC5(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MPFC5_OFFSET)
#define R_RMAC_MPFC6(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MPFC6_OFFSET)
#define R_RMAC_MPFC7(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MPFC7_OFFSET)
#define R_RMAC_MPFC8(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MPFC8_OFFSET)
#define R_RMAC_MPFC9(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MPFC9_OFFSET)
#define R_RMAC_MPFC10(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MPFC10_OFFSET)
#define R_RMAC_MPFC11(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MPFC11_OFFSET)
#define R_RMAC_MPFC12(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MPFC12_OFFSET)
#define R_RMAC_MPFC13(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MPFC13_OFFSET)
#define R_RMAC_MPFC14(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MPFC14_OFFSET)
#define R_RMAC_MPFC15(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MPFC15_OFFSET)
#define R_RMAC_MLVC(n)                            (R_RMAC_CH_BASE(n) + R_RMAC_MLVC_OFFSET)
#define R_RMAC_MEEEC(n)                           (R_RMAC_CH_BASE(n) + R_RMAC_MEEEC_OFFSET)
#define R_RMAC_MLBC(n)                            (R_RMAC_CH_BASE(n) + R_RMAC_MLBC_OFFSET)
#define R_RMAC_MXGMIIC(n)                         (R_RMAC_CH_BASE(n) + R_RMAC_MXGMIIC_OFFSET)
#define R_RMAC_MPCH(n)                            (R_RMAC_CH_BASE(n) + R_RMAC_MPCH_OFFSET)
#define R_RMAC_MANM(n)                            (R_RMAC_CH_BASE(n) + R_RMAC_MANM_OFFSET)
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
#define R_RMAC_MMPCFTCT0(n)                       (R_RMAC_CH_BASE(n) + R_RMAC_MMPCFTCT0_OFFSET)
#define R_RMAC_MMPCFTCT1(n)                       (R_RMAC_CH_BASE(n) + R_RMAC_MMPCFTCT1_OFFSET)
#define R_RMAC_MAPCFTCT0(n)                       (R_RMAC_CH_BASE(n) + R_RMAC_MAPCFTCT0_OFFSET)
#define R_RMAC_MAPCFTCT1(n)                       (R_RMAC_CH_BASE(n) + R_RMAC_MAPCFTCT1_OFFSET)
#define R_RMAC_MPCFRCT0(n)                        (R_RMAC_CH_BASE(n) + R_RMAC_MPCFRCT0_OFFSET)
#define R_RMAC_MPCFRCT1(n)                        (R_RMAC_CH_BASE(n) + R_RMAC_MPCFRCT1_OFFSET)
#define R_RMAC_MPCFRCT2(n)                        (R_RMAC_CH_BASE(n) + R_RMAC_MPCFRCT2_OFFSET)
#define R_RMAC_MPCFRCT3(n)                        (R_RMAC_CH_BASE(n) + R_RMAC_MPCFRCT3_OFFSET)
#define R_RMAC_MPCFRCT4(n)                        (R_RMAC_CH_BASE(n) + R_RMAC_MPCFRCT4_OFFSET)
#define R_RMAC_MPCFRCT5(n)                        (R_RMAC_CH_BASE(n) + R_RMAC_MPCFRCT5_OFFSET)
#define R_RMAC_MPCFRCT6(n)                        (R_RMAC_CH_BASE(n) + R_RMAC_MPCFRCT6_OFFSET)
#define R_RMAC_MPCFRCT7(n)                        (R_RMAC_CH_BASE(n) + R_RMAC_MPCFRCT7_OFFSET)
#define R_RMAC_MROVFC(n)                          (R_RMAC_CH_BASE(n) + R_RMAC_MROVFC_OFFSET)
#define R_RMAC_MRHCRCEC(n)                        (R_RMAC_CH_BASE(n) + R_RMAC_MRHCRCEC_OFFSET)
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
#define R_RMAC_MPSM_PSME                          (1 << 0)  /*  */

#define R_RMAC_MPSM_RESERVED                      (1 << 15)  /* This bit is read as 0. The write value should be 0. */

#define R_RMAC_MPSM_MFF                           (1 << 2)  /*  */

#define R_RMAC_MPSM_PDA_SHIFT                     (3)  /*  */
#define R_RMAC_MPSM_PDA_MASK                      0xf8

#define R_RMAC_MPSM_PRA_SHIFT                     (8)  /*  */
#define R_RMAC_MPSM_PRA_MASK                      0x1f00

#define R_RMAC_MPSM_POP_SHIFT                     (13)  /*  */
#define R_RMAC_MPSM_POP_MASK                      0x6000

#define R_RMAC_MPSM_PRD_SHIFT                     (16)  /*  */
#define R_RMAC_MPSM_PRD_MASK                      0xffff0000

/* MPIC Register bit definitions */
#define R_RMAC_MPIC_PIS_SHIFT                     (0)  /*  */
#define R_RMAC_MPIC_PIS_MASK                      0x7

#define R_RMAC_MPIC_LSC_SHIFT                     (3)  /*  */
#define R_RMAC_MPIC_LSC_MASK                      0x38

#define R_RMAC_MPIC_RESERVED                      (1 << 31)  /* This bit is read as 0. The write value should be 0. */

#define R_RMAC_MPIC_PIP                           (1 << 8)  /*  */

#define R_RMAC_MPIC_PIPP                          (1 << 9)  /*  */

#define R_RMAC_MPIC_PLSPP                         (1 << 10)  /*  */

#define R_RMAC_MPIC_PSMCS_SHIFT                   (16)  /*  */
#define R_RMAC_MPIC_PSMCS_MASK                    0x7f0000

#define R_RMAC_MPIC_PSMDP                         (1 << 23)  /*  */

#define R_RMAC_MPIC_PSMHT_SHIFT                   (24)  /*  */
#define R_RMAC_MPIC_PSMHT_MASK                    0x7000000

#define R_RMAC_MPIC_PSMCT_SHIFT                   (28)  /*  */
#define R_RMAC_MPIC_PSMCT_MASK                    0x70000000

/* MPIM Register bit definitions */
#define R_RMAC_MPIM_PLS                           (1 << 0)  /*  */

#define R_RMAC_MPIM_LPIA                          (1 << 1)  /*  */

#define R_RMAC_MPIM_RESERVED                      (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MIOC Register bit definitions */
#define R_RMAC_MIOC_MIOC_SHIFT                    (0)  /*  */
#define R_RMAC_MIOC_MIOC_MASK                     0xffffffff

/* MTFFC Register bit definitions */
#define R_RMAC_MTFFC_DPAD                         (1 << 0)  /*  */

#define R_RMAC_MTFFC_FCM                          (1 << 1)  /*  */

#define R_RMAC_MTFFC_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MTPFC Register bit definitions */
#define R_RMAC_MTPFC_PT_SHIFT                     (0)  /*  */
#define R_RMAC_MTPFC_PT_MASK                      0xffff

#define R_RMAC_MTPFC_PFRT_SHIFT                   (16)  /*  */
#define R_RMAC_MTPFC_PFRT_MASK                    0xff0000

#define R_RMAC_MTPFC_RESERVED                     (1 << 25)  /* This bit is read as 0. The write value should be 0. */

#define R_RMAC_MTPFC_PFM                          (1 << 26)  /*  */

#define R_RMAC_MTPFC_PFRLV_SHIFT                  (27)  /*  */
#define R_RMAC_MTPFC_PFRLV_MASK                   0xf8000000

/* MTPFC2 Register bit definitions */
#define R_RMAC_MTPFC2_PFCTTZ_SHIFT                (0)  /*  */
#define R_RMAC_MTPFC2_PFCTTZ_MASK                 0x3

#define R_RMAC_MTPFC2_RESERVED                    (1 << 31)  /* This bit is read as 0. The write value should be 0. */

#define R_RMAC_MTPFC2_MPFCFR0                     (1 << 8)  /*  */

#define R_RMAC_MTPFC2_MPFCFR1                     (1 << 9)  /*  */

#define R_RMAC_MTPFC2_PFTTZ                       (1 << 16)  /*  */

#define R_RMAC_MTPFC2_MPFR                        (1 << 17)  /*  */

/* MTPFC30 Register bit definitions */
#define R_RMAC_MTPFC30_PFCPG_SHIFT                (0)  /*  */
#define R_RMAC_MTPFC30_PFCPG_MASK                 0xff

#define R_RMAC_MTPFC30_RESERVED                   (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MTPFC31 Register bit definitions */
#define R_RMAC_MTPFC31_PFCPG_SHIFT                (0)  /*  */
#define R_RMAC_MTPFC31_PFCPG_MASK                 0xff

#define R_RMAC_MTPFC31_RESERVED                   (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MTATC0 Register bit definitions */
#define R_RMAC_MTATC0_TRTP_SHIFT                  (0)  /*  */
#define R_RMAC_MTATC0_TRTP_MASK                   0xff

#define R_RMAC_MTATC0_TRTL_SHIFT                  (8)  /*  */
#define R_RMAC_MTATC0_TRTL_MASK                   0x700

#define R_RMAC_MTATC0_RESERVED                    (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MTATC1 Register bit definitions */
#define R_RMAC_MTATC1_TRTP_SHIFT                  (0)  /*  */
#define R_RMAC_MTATC1_TRTP_MASK                   0xff

#define R_RMAC_MTATC1_TRTL_SHIFT                  (8)  /*  */
#define R_RMAC_MTATC1_TRTL_MASK                   0x700

#define R_RMAC_MTATC1_RESERVED                    (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MTIM Register bit definitions */
#define R_RMAC_MTIM_TS                            (1 << 0)  /*  */

#define R_RMAC_MTIM_RESERVED                      (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MRGC Register bit definitions */
#define R_RMAC_MRGC_RCPT                          (1 << 0)  /*  */

#define R_RMAC_MRGC_PFRC                          (1 << 1)  /*  */

#define R_RMAC_MRGC_PFRTZ                         (1 << 2)  /*  */

#define R_RMAC_MRGC_MPDE                          (1 << 3)  /*  */

#define R_RMAC_MRGC_RFCFE                         (1 << 4)  /*  */

#define R_RMAC_MRGC_RESERVED                      (1 << 31)  /* This bit is read as 0. The write value should be 0. */

#define R_RMAC_MRGC_PFCRC_SHIFT                   (16)  /*  */
#define R_RMAC_MRGC_PFCRC_MASK                    0xff0000

/* MRMAC0 Register bit definitions */
#define R_RMAC_MRMAC0_MAU_SHIFT                   (0)  /*  */
#define R_RMAC_MRMAC0_MAU_MASK                    0xffff

#define R_RMAC_MRMAC0_RESERVED                    (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MRMAC1 Register bit definitions */
#define R_RMAC_MRMAC1_MAL_SHIFT                   (0)  /*  */
#define R_RMAC_MRMAC1_MAL_MASK                    0xffffffff

/* MRAFC Register bit definitions */
#define R_RMAC_MRAFC_UCENE                        (1 << 0)  /*  */

#define R_RMAC_MRAFC_MCENE                        (1 << 1)  /*  */

#define R_RMAC_MRAFC_BCENE                        (1 << 2)  /*  */

#define R_RMAC_MRAFC_MSTENE                       (1 << 3)  /*  */

#define R_RMAC_MRAFC_BSTENE                       (1 << 4)  /*  */

#define R_RMAC_MRAFC_MCACE                        (1 << 5)  /*  */

#define R_RMAC_MRAFC_BCACE                        (1 << 6)  /*  */

#define R_RMAC_MRAFC_NDAREE                       (1 << 7)  /*  */

#define R_RMAC_MRAFC_SDSFREE                      (1 << 8)  /*  */

#define R_RMAC_MRAFC_NSAREE                       (1 << 9)  /*  */

#define R_RMAC_MRAFC_MSAREE                       (1 << 10)  /*  */

#define R_RMAC_MRAFC_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

#define R_RMAC_MRAFC_UCENP                        (1 << 16)  /*  */

#define R_RMAC_MRAFC_MCENP                        (1 << 17)  /*  */

#define R_RMAC_MRAFC_BCENP                        (1 << 18)  /*  */

#define R_RMAC_MRAFC_MSTENP                       (1 << 19)  /*  */

#define R_RMAC_MRAFC_BSTENP                       (1 << 20)  /*  */

#define R_RMAC_MRAFC_MCACP                        (1 << 21)  /*  */

#define R_RMAC_MRAFC_BCACP                        (1 << 22)  /*  */

#define R_RMAC_MRAFC_NDAREP                       (1 << 23)  /*  */

#define R_RMAC_MRAFC_SDSFREP                      (1 << 24)  /*  */

#define R_RMAC_MRAFC_NSAREP                       (1 << 25)  /*  */

#define R_RMAC_MRAFC_MSAREP                       (1 << 26)  /*  */

/* MRSCE Register bit definitions */
#define R_RMAC_MRSCE_CMFE_SHIFT                   (0)  /*  */
#define R_RMAC_MRSCE_CMFE_MASK                    0xffff

#define R_RMAC_MRSCE_CBFE_SHIFT                   (16)  /*  */
#define R_RMAC_MRSCE_CBFE_MASK                    0xffff0000

/* MRSCP Register bit definitions */
#define R_RMAC_MRSCP_CMFP_SHIFT                   (0)  /*  */
#define R_RMAC_MRSCP_CMFP_MASK                    0xffff

#define R_RMAC_MRSCP_CBFP_SHIFT                   (16)  /*  */
#define R_RMAC_MRSCP_CBFP_MASK                    0xffff0000

/* MRSCC Register bit definitions */
#define R_RMAC_MRSCC_MSCCE                        (1 << 0)  /*  */

#define R_RMAC_MRSCC_BSCCE                        (1 << 1)  /*  */

#define R_RMAC_MRSCC_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

#define R_RMAC_MRSCC_MSCCP                        (1 << 16)  /*  */

#define R_RMAC_MRSCC_BSCCP                        (1 << 17)  /*  */

/* MRFSCE Register bit definitions */
#define R_RMAC_MRFSCE_EMXS_SHIFT                  (0)  /*  */
#define R_RMAC_MRFSCE_EMXS_MASK                   0xffff

#define R_RMAC_MRFSCE_EMNS_SHIFT                  (16)  /*  */
#define R_RMAC_MRFSCE_EMNS_MASK                   0xffff0000

/* MRFSCP Register bit definitions */
#define R_RMAC_MRFSCP_PMXS_SHIFT                  (0)  /*  */
#define R_RMAC_MRFSCP_PMXS_MASK                   0xffff

#define R_RMAC_MRFSCP_PMNS_SHIFT                  (16)  /*  */
#define R_RMAC_MRFSCP_PMNS_MASK                   0xffff0000

/* MTRC Register bit definitions */
#define R_RMAC_MTRC_TRHFME0                       (1 << 0)  /*  */

#define R_RMAC_MTRC_TRHFME1                       (1 << 1)  /*  */

#define R_RMAC_MTRC_RESERVED                      (1 << 31)  /* This bit is read as 0. The write value should be 0. */

#define R_RMAC_MTRC_TRDDE                         (1 << 24)  /*  */

#define R_RMAC_MTRC_TRDDP                         (1 << 25)  /*  */

#define R_RMAC_MTRC_TCTSE                         (1 << 26)  /*  */

#define R_RMAC_MTRC_TCTSP                         (1 << 27)  /*  */

#define R_RMAC_MTRC_DTN                           (1 << 28)  /*  */

/* MRPFM Register bit definitions */
#define R_RMAC_MRPFM_PTCA                         (1 << 0)  /*  */

#define R_RMAC_MRPFM_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

#define R_RMAC_MRPFM_PFCTCA_SHIFT                 (16)  /*  */
#define R_RMAC_MRPFM_PFCTCA_MASK                  0xff0000

/* MPFC0 Register bit definitions */
#define R_RMAC_MPFC0_PFBN_SHIFT                   (0)  /*  */
#define R_RMAC_MPFC0_PFBN_MASK                    0xff

#define R_RMAC_MPFC0_PFBV_SHIFT                   (8)  /*  */
#define R_RMAC_MPFC0_PFBV_MASK                    0xff00

#define R_RMAC_MPFC0_TEF0                         (1 << 16)  /*  */

#define R_RMAC_MPFC0_TEF1                         (1 << 17)  /*  */

#define R_RMAC_MPFC0_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPFC1 Register bit definitions */
#define R_RMAC_MPFC1_PFBN_SHIFT                   (0)  /*  */
#define R_RMAC_MPFC1_PFBN_MASK                    0xff

#define R_RMAC_MPFC1_PFBV_SHIFT                   (8)  /*  */
#define R_RMAC_MPFC1_PFBV_MASK                    0xff00

#define R_RMAC_MPFC1_TEF0                         (1 << 16)  /*  */

#define R_RMAC_MPFC1_TEF1                         (1 << 17)  /*  */

#define R_RMAC_MPFC1_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPFC2 Register bit definitions */
#define R_RMAC_MPFC2_PFBN_SHIFT                   (0)  /*  */
#define R_RMAC_MPFC2_PFBN_MASK                    0xff

#define R_RMAC_MPFC2_PFBV_SHIFT                   (8)  /*  */
#define R_RMAC_MPFC2_PFBV_MASK                    0xff00

#define R_RMAC_MPFC2_TEF0                         (1 << 16)  /*  */

#define R_RMAC_MPFC2_TEF1                         (1 << 17)  /*  */

#define R_RMAC_MPFC2_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPFC3 Register bit definitions */
#define R_RMAC_MPFC3_PFBN_SHIFT                   (0)  /*  */
#define R_RMAC_MPFC3_PFBN_MASK                    0xff

#define R_RMAC_MPFC3_PFBV_SHIFT                   (8)  /*  */
#define R_RMAC_MPFC3_PFBV_MASK                    0xff00

#define R_RMAC_MPFC3_TEF0                         (1 << 16)  /*  */

#define R_RMAC_MPFC3_TEF1                         (1 << 17)  /*  */

#define R_RMAC_MPFC3_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPFC4 Register bit definitions */
#define R_RMAC_MPFC4_PFBN_SHIFT                   (0)  /*  */
#define R_RMAC_MPFC4_PFBN_MASK                    0xff

#define R_RMAC_MPFC4_PFBV_SHIFT                   (8)  /*  */
#define R_RMAC_MPFC4_PFBV_MASK                    0xff00

#define R_RMAC_MPFC4_TEF0                         (1 << 16)  /*  */

#define R_RMAC_MPFC4_TEF1                         (1 << 17)  /*  */

#define R_RMAC_MPFC4_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPFC5 Register bit definitions */
#define R_RMAC_MPFC5_PFBN_SHIFT                   (0)  /*  */
#define R_RMAC_MPFC5_PFBN_MASK                    0xff

#define R_RMAC_MPFC5_PFBV_SHIFT                   (8)  /*  */
#define R_RMAC_MPFC5_PFBV_MASK                    0xff00

#define R_RMAC_MPFC5_TEF0                         (1 << 16)  /*  */

#define R_RMAC_MPFC5_TEF1                         (1 << 17)  /*  */

#define R_RMAC_MPFC5_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPFC6 Register bit definitions */
#define R_RMAC_MPFC6_PFBN_SHIFT                   (0)  /*  */
#define R_RMAC_MPFC6_PFBN_MASK                    0xff

#define R_RMAC_MPFC6_PFBV_SHIFT                   (8)  /*  */
#define R_RMAC_MPFC6_PFBV_MASK                    0xff00

#define R_RMAC_MPFC6_TEF0                         (1 << 16)  /*  */

#define R_RMAC_MPFC6_TEF1                         (1 << 17)  /*  */

#define R_RMAC_MPFC6_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPFC7 Register bit definitions */
#define R_RMAC_MPFC7_PFBN_SHIFT                   (0)  /*  */
#define R_RMAC_MPFC7_PFBN_MASK                    0xff

#define R_RMAC_MPFC7_PFBV_SHIFT                   (8)  /*  */
#define R_RMAC_MPFC7_PFBV_MASK                    0xff00

#define R_RMAC_MPFC7_TEF0                         (1 << 16)  /*  */

#define R_RMAC_MPFC7_TEF1                         (1 << 17)  /*  */

#define R_RMAC_MPFC7_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPFC8 Register bit definitions */
#define R_RMAC_MPFC8_PFBN_SHIFT                   (0)  /*  */
#define R_RMAC_MPFC8_PFBN_MASK                    0xff

#define R_RMAC_MPFC8_PFBV_SHIFT                   (8)  /*  */
#define R_RMAC_MPFC8_PFBV_MASK                    0xff00

#define R_RMAC_MPFC8_TEF0                         (1 << 16)  /*  */

#define R_RMAC_MPFC8_TEF1                         (1 << 17)  /*  */

#define R_RMAC_MPFC8_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPFC9 Register bit definitions */
#define R_RMAC_MPFC9_PFBN_SHIFT                   (0)  /*  */
#define R_RMAC_MPFC9_PFBN_MASK                    0xff

#define R_RMAC_MPFC9_PFBV_SHIFT                   (8)  /*  */
#define R_RMAC_MPFC9_PFBV_MASK                    0xff00

#define R_RMAC_MPFC9_TEF0                         (1 << 16)  /*  */

#define R_RMAC_MPFC9_TEF1                         (1 << 17)  /*  */

#define R_RMAC_MPFC9_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPFC10 Register bit definitions */
#define R_RMAC_MPFC10_PFBN_SHIFT                  (0)  /*  */
#define R_RMAC_MPFC10_PFBN_MASK                   0xff

#define R_RMAC_MPFC10_PFBV_SHIFT                  (8)  /*  */
#define R_RMAC_MPFC10_PFBV_MASK                   0xff00

#define R_RMAC_MPFC10_TEF0                        (1 << 16)  /*  */

#define R_RMAC_MPFC10_TEF1                        (1 << 17)  /*  */

#define R_RMAC_MPFC10_RESERVED                    (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPFC11 Register bit definitions */
#define R_RMAC_MPFC11_PFBN_SHIFT                  (0)  /*  */
#define R_RMAC_MPFC11_PFBN_MASK                   0xff

#define R_RMAC_MPFC11_PFBV_SHIFT                  (8)  /*  */
#define R_RMAC_MPFC11_PFBV_MASK                   0xff00

#define R_RMAC_MPFC11_TEF0                        (1 << 16)  /*  */

#define R_RMAC_MPFC11_TEF1                        (1 << 17)  /*  */

#define R_RMAC_MPFC11_RESERVED                    (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPFC12 Register bit definitions */
#define R_RMAC_MPFC12_PFBN_SHIFT                  (0)  /*  */
#define R_RMAC_MPFC12_PFBN_MASK                   0xff

#define R_RMAC_MPFC12_PFBV_SHIFT                  (8)  /*  */
#define R_RMAC_MPFC12_PFBV_MASK                   0xff00

#define R_RMAC_MPFC12_TEF0                        (1 << 16)  /*  */

#define R_RMAC_MPFC12_TEF1                        (1 << 17)  /*  */

#define R_RMAC_MPFC12_RESERVED                    (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPFC13 Register bit definitions */
#define R_RMAC_MPFC13_PFBN_SHIFT                  (0)  /*  */
#define R_RMAC_MPFC13_PFBN_MASK                   0xff

#define R_RMAC_MPFC13_PFBV_SHIFT                  (8)  /*  */
#define R_RMAC_MPFC13_PFBV_MASK                   0xff00

#define R_RMAC_MPFC13_TEF0                        (1 << 16)  /*  */

#define R_RMAC_MPFC13_TEF1                        (1 << 17)  /*  */

#define R_RMAC_MPFC13_RESERVED                    (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPFC14 Register bit definitions */
#define R_RMAC_MPFC14_PFBN_SHIFT                  (0)  /*  */
#define R_RMAC_MPFC14_PFBN_MASK                   0xff

#define R_RMAC_MPFC14_PFBV_SHIFT                  (8)  /*  */
#define R_RMAC_MPFC14_PFBV_MASK                   0xff00

#define R_RMAC_MPFC14_TEF0                        (1 << 16)  /*  */

#define R_RMAC_MPFC14_TEF1                        (1 << 17)  /*  */

#define R_RMAC_MPFC14_RESERVED                    (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPFC15 Register bit definitions */
#define R_RMAC_MPFC15_PFBN_SHIFT                  (0)  /*  */
#define R_RMAC_MPFC15_PFBN_MASK                   0xff

#define R_RMAC_MPFC15_PFBV_SHIFT                  (8)  /*  */
#define R_RMAC_MPFC15_PFBV_MASK                   0xff00

#define R_RMAC_MPFC15_TEF0                        (1 << 16)  /*  */

#define R_RMAC_MPFC15_TEF1                        (1 << 17)  /*  */

#define R_RMAC_MPFC15_RESERVED                    (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MLVC Register bit definitions */
#define R_RMAC_MLVC_LVT_SHIFT                     (0)  /*  */
#define R_RMAC_MLVC_LVT_MASK                      0x7f

#define R_RMAC_MLVC_RESERVED                      (1 << 31)  /* This bit is read as 0. The write value should be 0. */

#define R_RMAC_MLVC_PASE                          (1 << 8)  /*  */

#define R_RMAC_MLVC_PLV                           (1 << 16)  /*  */

/* MEEEC Register bit definitions */
#define R_RMAC_MEEEC_LPITR                        (1 << 0)  /*  */

#define R_RMAC_MEEEC_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MLBC Register bit definitions */
#define R_RMAC_MLBC_LBME                          (1 << 0)  /*  */

#define R_RMAC_MLBC_RESERVED                      (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MXGMIIC Register bit definitions */
#define R_RMAC_MXGMIIC_LFS_TXRFS                  (1 << 0)  /*  */

#define R_RMAC_MXGMIIC_LFS_TXIDLE                 (1 << 1)  /*  */

#define R_RMAC_MXGMIIC_RESERVED                   (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPCH Register bit definitions */
#define R_RMAC_MPCH_TXPCH_M                       (1 << 0)  /*  */

#define R_RMAC_MPCH_RESERVED                      (1 << 31)  /* This bit is read as 0. The write value should be 0. */

#define R_RMAC_MPCH_TXPCH_ETYPE_SHIFT             (2)  /*  */
#define R_RMAC_MPCH_TXPCH_ETYPE_MASK              0xc

#define R_RMAC_MPCH_TXPCH_PID_SHIFT               (4)  /*  */
#define R_RMAC_MPCH_TXPCH_PID_MASK                0xf0

#define R_RMAC_MPCH_IETPTE                        (1 << 8)  /*  */

#define R_RMAC_MPCH_CTPTE                         (1 << 9)  /*  */

#define R_RMAC_MPCH_IETRIOD                       (1 << 10)  /*  */

#define R_RMAC_MPCH_CTRIOD                        (1 << 11)  /*  */

#define R_RMAC_MPCH_RXPCH_TSM                     (1 << 16)  /*  */

#define R_RMAC_MPCH_RPHCRCD                       (1 << 17)  /*  */

/* MANM Register bit definitions */
#define R_RMAC_MANM_RX_AN_MES_SHIFT               (0)  /*  */
#define R_RMAC_MANM_RX_AN_MES_MASK                0xffff

/* MEIS Register bit definitions */
#define R_RMAC_MEIS_TSLS                          (1 << 0)  /*  */

#define R_RMAC_MEIS_TIES                          (1 << 1)  /*  */

#define R_RMAC_MEIS_PRES                          (1 << 2)  /*  */

#define R_RMAC_MEIS_PFRROS                        (1 << 3)  /*  */

#define R_RMAC_MEIS_FCDS                          (1 << 4)  /*  */

#define R_RMAC_MEIS_TCES                          (1 << 5)  /*  */

#define R_RMAC_MEIS_TBCIS                         (1 << 6)  /*  */

#define R_RMAC_MEIS_BFES                          (1 << 7)  /*  */

#define R_RMAC_MEIS_FCES                          (1 << 8)  /*  */

#define R_RMAC_MEIS_REOES                         (1 << 9)  /*  */

#define R_RMAC_MEIS_RPOES                         (1 << 10)  /*  */

#define R_RMAC_MEIS_RPCRES                        (1 << 11)  /*  */

#define R_RMAC_MEIS_CTLES0                        (1 << 12)  /*  */

#define R_RMAC_MEIS_CTLES1                        (1 << 13)  /*  */

#define R_RMAC_MEIS_RESERVED                      (1 << 31)  /* This bit is read as 0. The write value should be 0. */

#define R_RMAC_MEIS_PDES                          (1 << 20)  /*  */

#define R_RMAC_MEIS_PNAES                         (1 << 21)  /*  */

#define R_RMAC_MEIS_FCMCES                        (1 << 22)  /*  */

#define R_RMAC_MEIS_FFMES                         (1 << 23)  /*  */

#define R_RMAC_MEIS_CFCES                         (1 << 24)  /*  */

#define R_RMAC_MEIS_FRCES                         (1 << 25)  /*  */

#define R_RMAC_MEIS_RPOOMS                        (1 << 26)  /*  */

#define R_RMAC_MEIS_FFS                           (1 << 27)  /*  */

#define R_RMAC_MEIS_FUES                          (1 << 28)  /*  */

#define R_RMAC_MEIS_FOES                          (1 << 29)  /*  */

/* MEIE Register bit definitions */
#define R_RMAC_MEIE_TSLE                          (1 << 0)  /*  */

#define R_RMAC_MEIE_TIEE                          (1 << 1)  /*  */

#define R_RMAC_MEIE_PMSEE                         (1 << 2)  /*  */

#define R_RMAC_MEIE_PFRROE                        (1 << 3)  /*  */

#define R_RMAC_MEIE_FCDE                          (1 << 4)  /*  */

#define R_RMAC_MEIE_TCEE                          (1 << 5)  /*  */

#define R_RMAC_MEIE_TBCIE                         (1 << 6)  /*  */

#define R_RMAC_MEIE_BFEE                          (1 << 7)  /*  */

#define R_RMAC_MEIE_FCEE                          (1 << 8)  /*  */

#define R_RMAC_MEIE_REOEE                         (1 << 9)  /*  */

#define R_RMAC_MEIE_RPOEE                         (1 << 10)  /*  */

#define R_RMAC_MEIE_RPCREE                        (1 << 11)  /*  */

#define R_RMAC_MEIE_CTLEE0                        (1 << 12)  /*  */

#define R_RMAC_MEIE_CTLEE1                        (1 << 13)  /*  */

#define R_RMAC_MEIE_RESERVED                      (1 << 31)  /* This bit is read as 0. The write value should be 0. */

#define R_RMAC_MEIE_PDEE                          (1 << 20)  /*  */

#define R_RMAC_MEIE_PNAEE                         (1 << 21)  /*  */

#define R_RMAC_MEIE_FCMCEE                        (1 << 22)  /*  */

#define R_RMAC_MEIE_FFMEE                         (1 << 23)  /*  */

#define R_RMAC_MEIE_CFCEE                         (1 << 24)  /*  */

#define R_RMAC_MEIE_FRCEE                         (1 << 25)  /*  */

#define R_RMAC_MEIE_RPOOME                        (1 << 26)  /*  */

#define R_RMAC_MEIE_FFE                           (1 << 27)  /*  */

#define R_RMAC_MEIE_FUEE                          (1 << 28)  /*  */

#define R_RMAC_MEIE_FOEE                          (1 << 29)  /*  */

/* MEID Register bit definitions */
#define R_RMAC_MEID_TSLD                          (1 << 0)  /*  */

#define R_RMAC_MEID_TIED                          (1 << 1)  /*  */

#define R_RMAC_MEID_PRED                          (1 << 2)  /*  */

#define R_RMAC_MEID_PFRROD                        (1 << 3)  /*  */

#define R_RMAC_MEID_FCDD                          (1 << 4)  /*  */

#define R_RMAC_MEID_TCED                          (1 << 5)  /*  */

#define R_RMAC_MEID_TBCID                         (1 << 6)  /*  */

#define R_RMAC_MEID_BFED                          (1 << 7)  /*  */

#define R_RMAC_MEID_FCED                          (1 << 8)  /*  */

#define R_RMAC_MEID_REOED                         (1 << 9)  /*  */

#define R_RMAC_MEID_RPOED                         (1 << 10)  /*  */

#define R_RMAC_MEID_RPCRED                        (1 << 11)  /*  */

#define R_RMAC_MEID_CTLED0                        (1 << 12)  /*  */

#define R_RMAC_MEID_CTLED1                        (1 << 13)  /*  */

#define R_RMAC_MEID_RESERVED                      (1 << 31)  /* This bit is read as 0. The write value should be 0. */

#define R_RMAC_MEID_PDED                          (1 << 20)  /*  */

#define R_RMAC_MEID_PNAED                         (1 << 21)  /*  */

#define R_RMAC_MEID_FCMCED                        (1 << 22)  /*  */

#define R_RMAC_MEID_FFMED                         (1 << 23)  /*  */

#define R_RMAC_MEID_CFCED                         (1 << 24)  /*  */

#define R_RMAC_MEID_FRCED                         (1 << 25)  /*  */

#define R_RMAC_MEID_RPOOMD                        (1 << 26)  /*  */

#define R_RMAC_MEID_FFD                           (1 << 27)  /*  */

#define R_RMAC_MEID_FUED                          (1 << 28)  /*  */

#define R_RMAC_MEID_FOED                          (1 << 29)  /*  */

/* MMIS0 Register bit definitions */
#define R_RMAC_MMIS0_PLSCS                        (1 << 0)  /*  */

#define R_RMAC_MMIS0_PIDS                         (1 << 1)  /*  */

#define R_RMAC_MMIS0_LVSS                         (1 << 2)  /*  */

#define R_RMAC_MMIS0_LVFS                         (1 << 3)  /*  */

#define R_RMAC_MMIS0_VFRS                         (1 << 4)  /*  */

#define R_RMAC_MMIS0_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

#define R_RMAC_MMIS0_ANDETS                       (1 << 6)  /*  */

#define R_RMAC_MMIS0_XLFDS                        (1 << 8)  /*  */

#define R_RMAC_MMIS0_XLFES                        (1 << 9)  /*  */

#define R_RMAC_MMIS0_XLFSDS                       (1 << 10)  /*  */

#define R_RMAC_MMIS0_XRFSDS                       (1 << 11)  /*  */

#define R_RMAC_MMIS0_XLISDS                       (1 << 12)  /*  */

/* MMIE0 Register bit definitions */
#define R_RMAC_MMIE0_PLSCE                        (1 << 0)  /*  */

#define R_RMAC_MMIE0_PIDE                         (1 << 1)  /*  */

#define R_RMAC_MMIE0_LVSE                         (1 << 2)  /*  */

#define R_RMAC_MMIE0_LVFE                         (1 << 3)  /*  */

#define R_RMAC_MMIE0_VFRE                         (1 << 4)  /*  */

#define R_RMAC_MMIE0_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

#define R_RMAC_MMIE0_ANDETE                       (1 << 6)  /*  */

#define R_RMAC_MMIE0_XLFDE                        (1 << 8)  /*  */

#define R_RMAC_MMIE0_XLFEE                        (1 << 9)  /*  */

#define R_RMAC_MMIE0_XLFSDE                       (1 << 10)  /*  */

#define R_RMAC_MMIE0_XRFSDE                       (1 << 11)  /*  */

#define R_RMAC_MMIE0_XLISDE                       (1 << 12)  /*  */

/* MMID0 Register bit definitions */
#define R_RMAC_MMID0_PLSCD                        (1 << 0)  /*  */

#define R_RMAC_MMID0_PIDD                         (1 << 1)  /*  */

#define R_RMAC_MMID0_LVSD                         (1 << 2)  /*  */

#define R_RMAC_MMID0_LVFD                         (1 << 3)  /*  */

#define R_RMAC_MMID0_VFRD                         (1 << 4)  /*  */

#define R_RMAC_MMID0_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

#define R_RMAC_MMID0_ANDETD                       (1 << 6)  /*  */

#define R_RMAC_MMID0_XLFDD                        (1 << 8)  /*  */

#define R_RMAC_MMID0_XLFED                        (1 << 9)  /*  */

#define R_RMAC_MMID0_XLFSDD                       (1 << 10)  /*  */

#define R_RMAC_MMID0_XRFSDD                       (1 << 11)  /*  */

#define R_RMAC_MMID0_XLISDD                       (1 << 12)  /*  */

/* MMIS1 Register bit definitions */
#define R_RMAC_MMIS1_PRACS                        (1 << 0)  /*  */

#define R_RMAC_MMIS1_PWACS                        (1 << 1)  /*  */

#define R_RMAC_MMIS1_PAACS                        (1 << 2)  /*  */

#define R_RMAC_MMIS1_PPRACS                       (1 << 3)  /*  */

#define R_RMAC_MMIS1_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MMIE1 Register bit definitions */
#define R_RMAC_MMIE1_PRACE                        (1 << 0)  /*  */

#define R_RMAC_MMIE1_PWACE                        (1 << 1)  /*  */

#define R_RMAC_MMIE1_PAACE                        (1 << 2)  /*  */

#define R_RMAC_MMIE1_PPRACE                       (1 << 3)  /*  */

#define R_RMAC_MMIE1_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MMID1 Register bit definitions */
#define R_RMAC_MMID1_PRACD                        (1 << 0)  /*  */

#define R_RMAC_MMID1_PWACD                        (1 << 1)  /*  */

#define R_RMAC_MMID1_PAACD                        (1 << 2)  /*  */

#define R_RMAC_MMID1_PPRACD                       (1 << 3)  /*  */

#define R_RMAC_MMID1_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MMIS2 Register bit definitions */
#define R_RMAC_MMIS2_MPDIS                        (1 << 0)  /*  */

#define R_RMAC_MMIS2_LPIAIS                       (1 << 1)  /*  */

#define R_RMAC_MMIS2_LPIDIS                       (1 << 2)  /*  */

#define R_RMAC_MMIS2_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MMIE2 Register bit definitions */
#define R_RMAC_MMIE2_MPDIE                        (1 << 0)  /*  */

#define R_RMAC_MMIE2_LPIAIE                       (1 << 1)  /*  */

#define R_RMAC_MMIE2_LPIDIE                       (1 << 2)  /*  */

#define R_RMAC_MMIE2_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MMID2 Register bit definitions */
#define R_RMAC_MMID2_MPDID                        (1 << 0)  /*  */

#define R_RMAC_MMID2_LPIAID                       (1 << 1)  /*  */

#define R_RMAC_MMID2_LPIDID                       (1 << 2)  /*  */

#define R_RMAC_MMID2_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MMPFTCT Register bit definitions */
#define R_RMAC_MMPFTCT_MPFTC_SHIFT                (0)  /*  */
#define R_RMAC_MMPFTCT_MPFTC_MASK                 0xffff

#define R_RMAC_MMPFTCT_RESERVED                   (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MAPFTCT Register bit definitions */
#define R_RMAC_MAPFTCT_APFTC_SHIFT                (0)  /*  */
#define R_RMAC_MAPFTCT_APFTC_MASK                 0xffff

#define R_RMAC_MAPFTCT_RESERVED                   (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPFRCT Register bit definitions */
#define R_RMAC_MPFRCT_PFRC_SHIFT                  (0)  /*  */
#define R_RMAC_MPFRCT_PFRC_MASK                   0xffff

#define R_RMAC_MPFRCT_RESERVED                    (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MFCICT Register bit definitions */
#define R_RMAC_MFCICT_FCIC_SHIFT                  (0)  /*  */
#define R_RMAC_MFCICT_FCIC_MASK                   0xffff

#define R_RMAC_MFCICT_RESERVED                    (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MEEECT Register bit definitions */
#define R_RMAC_MEEECT_EEERC_SHIFT                 (0)  /*  */
#define R_RMAC_MEEECT_EEERC_MASK                  0xffff

#define R_RMAC_MEEECT_RESERVED                    (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MMPCFTCT0 Register bit definitions */
#define R_RMAC_MMPCFTCT0_MPCFCTC_SHIFT            (0)  /*  */
#define R_RMAC_MMPCFTCT0_MPCFCTC_MASK             0xffff

#define R_RMAC_MMPCFTCT0_RESERVED                 (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MMPCFTCT1 Register bit definitions */
#define R_RMAC_MMPCFTCT1_MPCFCTC_SHIFT            (0)  /*  */
#define R_RMAC_MMPCFTCT1_MPCFCTC_MASK             0xffff

#define R_RMAC_MMPCFTCT1_RESERVED                 (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MAPCFTCT0 Register bit definitions */
#define R_RMAC_MAPCFTCT0_APCFCTC_SHIFT            (0)  /*  */
#define R_RMAC_MAPCFTCT0_APCFCTC_MASK             0xffff

#define R_RMAC_MAPCFTCT0_RESERVED                 (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MAPCFTCT1 Register bit definitions */
#define R_RMAC_MAPCFTCT1_APCFCTC_SHIFT            (0)  /*  */
#define R_RMAC_MAPCFTCT1_APCFCTC_MASK             0xffff

#define R_RMAC_MAPCFTCT1_RESERVED                 (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPCFRCT0 Register bit definitions */
#define R_RMAC_MPCFRCT0_PCFCRC_SHIFT              (0)  /*  */
#define R_RMAC_MPCFRCT0_PCFCRC_MASK               0xffff

#define R_RMAC_MPCFRCT0_RESERVED                  (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPCFRCT1 Register bit definitions */
#define R_RMAC_MPCFRCT1_PCFCRC_SHIFT              (0)  /*  */
#define R_RMAC_MPCFRCT1_PCFCRC_MASK               0xffff

#define R_RMAC_MPCFRCT1_RESERVED                  (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPCFRCT2 Register bit definitions */
#define R_RMAC_MPCFRCT2_PCFCRC_SHIFT              (0)  /*  */
#define R_RMAC_MPCFRCT2_PCFCRC_MASK               0xffff

#define R_RMAC_MPCFRCT2_RESERVED                  (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPCFRCT3 Register bit definitions */
#define R_RMAC_MPCFRCT3_PCFCRC_SHIFT              (0)  /*  */
#define R_RMAC_MPCFRCT3_PCFCRC_MASK               0xffff

#define R_RMAC_MPCFRCT3_RESERVED                  (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPCFRCT4 Register bit definitions */
#define R_RMAC_MPCFRCT4_PCFCRC_SHIFT              (0)  /*  */
#define R_RMAC_MPCFRCT4_PCFCRC_MASK               0xffff

#define R_RMAC_MPCFRCT4_RESERVED                  (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPCFRCT5 Register bit definitions */
#define R_RMAC_MPCFRCT5_PCFCRC_SHIFT              (0)  /*  */
#define R_RMAC_MPCFRCT5_PCFCRC_MASK               0xffff

#define R_RMAC_MPCFRCT5_RESERVED                  (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPCFRCT6 Register bit definitions */
#define R_RMAC_MPCFRCT6_PCFCRC_SHIFT              (0)  /*  */
#define R_RMAC_MPCFRCT6_PCFCRC_MASK               0xffff

#define R_RMAC_MPCFRCT6_RESERVED                  (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MPCFRCT7 Register bit definitions */
#define R_RMAC_MPCFRCT7_PCFCRC_SHIFT              (0)  /*  */
#define R_RMAC_MPCFRCT7_PCFCRC_MASK               0xffff

#define R_RMAC_MPCFRCT7_RESERVED                  (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MROVFC Register bit definitions */
#define R_RMAC_MROVFC_ROVFC_SHIFT                 (0)  /*  */
#define R_RMAC_MROVFC_ROVFC_MASK                  0xffffffff

/* MRHCRCEC Register bit definitions */
#define R_RMAC_MRHCRCEC_RHCRCEC_SHIFT             (0)  /*  */
#define R_RMAC_MRHCRCEC_RHCRCEC_MASK              0xffff

#define R_RMAC_MRHCRCEC_RESERVED                  (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MRGFCE Register bit definitions */
#define R_RMAC_MRGFCE_RGFNE_SHIFT                 (0)  /*  */
#define R_RMAC_MRGFCE_RGFNE_MASK                  0xffffffff

/* MRGFCP Register bit definitions */
#define R_RMAC_MRGFCP_RGFNP_SHIFT                 (0)  /*  */
#define R_RMAC_MRGFCP_RGFNP_MASK                  0xffffffff

/* MRBFC Register bit definitions */
#define R_RMAC_MRBFC_RBFN_SHIFT                   (0)  /*  */
#define R_RMAC_MRBFC_RBFN_MASK                    0xffffffff

/* MRMFC Register bit definitions */
#define R_RMAC_MRMFC_RMFN_SHIFT                   (0)  /*  */
#define R_RMAC_MRMFC_RMFN_MASK                    0xffffffff

/* MRUFC Register bit definitions */
#define R_RMAC_MRUFC_RUFN_SHIFT                   (0)  /*  */
#define R_RMAC_MRUFC_RUFN_MASK                    0xffffffff

/* MRPEFC Register bit definitions */
#define R_RMAC_MRPEFC_RPEFN_SHIFT                 (0)  /*  */
#define R_RMAC_MRPEFC_RPEFN_MASK                  0xffff

#define R_RMAC_MRPEFC_RESERVED                    (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MRNEFC Register bit definitions */
#define R_RMAC_MRNEFC_RNEFN_SHIFT                 (0)  /*  */
#define R_RMAC_MRNEFC_RNEFN_MASK                  0xffff

#define R_RMAC_MRNEFC_RESERVED                    (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MRFMEFC Register bit definitions */
#define R_RMAC_MRFMEFC_RFMEFN_SHIFT               (0)  /*  */
#define R_RMAC_MRFMEFC_RFMEFN_MASK                0xffffffff

/* MRFFMEFC Register bit definitions */
#define R_RMAC_MRFFMEFC_RFFMEFN_SHIFT             (0)  /*  */
#define R_RMAC_MRFFMEFC_RFFMEFN_MASK              0xffff

#define R_RMAC_MRFFMEFC_RESERVED                  (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MRCFCEFC Register bit definitions */
#define R_RMAC_MRCFCEFC_RCFCEFN_SHIFT             (0)  /*  */
#define R_RMAC_MRCFCEFC_RCFCEFN_MASK              0xffff

#define R_RMAC_MRCFCEFC_RESERVED                  (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MRFCEFC Register bit definitions */
#define R_RMAC_MRFCEFC_RFCEFN_SHIFT               (0)  /*  */
#define R_RMAC_MRFCEFC_RFCEFN_MASK                0xffff

#define R_RMAC_MRFCEFC_RESERVED                   (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MRRCFEFC Register bit definitions */
#define R_RMAC_MRRCFEFC_RRCFEFN_SHIFT             (0)  /*  */
#define R_RMAC_MRRCFEFC_RRCFEFN_MASK              0xffff

#define R_RMAC_MRRCFEFC_RESERVED                  (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MRFC Register bit definitions */
#define R_RMAC_MRFC_RFN_SHIFT                     (0)  /*  */
#define R_RMAC_MRFC_RFN_MASK                      0xffffffff

/* MRGUEFC Register bit definitions */
#define R_RMAC_MRGUEFC_RUEFN_SHIFT                (0)  /*  */
#define R_RMAC_MRGUEFC_RUEFN_MASK                 0xffffffff

/* MRBUEFC Register bit definitions */
#define R_RMAC_MRBUEFC_RUEFN_SHIFT                (0)  /*  */
#define R_RMAC_MRBUEFC_RUEFN_MASK                 0xffffffff

/* MRGOEFC Register bit definitions */
#define R_RMAC_MRGOEFC_RGOEFN_SHIFT               (0)  /*  */
#define R_RMAC_MRGOEFC_RGOEFN_MASK                0xffffffff

/* MRBOEFC Register bit definitions */
#define R_RMAC_MRBOEFC_RBOEFN_SHIFT               (0)  /*  */
#define R_RMAC_MRBOEFC_RBOEFN_MASK                0xffffffff

/* MRXBCEU Register bit definitions */
#define R_RMAC_MRXBCEU_RBNEU_SHIFT                (0)  /*  */
#define R_RMAC_MRXBCEU_RBNEU_MASK                 0xffffffff

/* MRXBCEL Register bit definitions */
#define R_RMAC_MRXBCEL_RBNEL_SHIFT                (0)  /*  */
#define R_RMAC_MRXBCEL_RBNEL_MASK                 0xffffffff

/* MRXBCPU Register bit definitions */
#define R_RMAC_MRXBCPU_RBNPU_SHIFT                (0)  /*  */
#define R_RMAC_MRXBCPU_RBNPU_MASK                 0xffffffff

/* MRXBCPL Register bit definitions */
#define R_RMAC_MRXBCPL_RBNPL_SHIFT                (0)  /*  */
#define R_RMAC_MRXBCPL_RBNPL_MASK                 0xffffffff

/* MTGFCE Register bit definitions */
#define R_RMAC_MTGFCE_TGFNE_SHIFT                 (0)  /*  */
#define R_RMAC_MTGFCE_TGFNE_MASK                  0xffffffff

/* MTGFCP Register bit definitions */
#define R_RMAC_MTGFCP_TGFNP_SHIFT                 (0)  /*  */
#define R_RMAC_MTGFCP_TGFNP_MASK                  0xffffffff

/* MTBFC Register bit definitions */
#define R_RMAC_MTBFC_TBFN_SHIFT                   (0)  /*  */
#define R_RMAC_MTBFC_TBFN_MASK                    0xffffffff

/* MTMFC Register bit definitions */
#define R_RMAC_MTMFC_TMFN_SHIFT                   (0)  /*  */
#define R_RMAC_MTMFC_TMFN_MASK                    0xffffffff

/* MTUFC Register bit definitions */
#define R_RMAC_MTUFC_TUFN_SHIFT                   (0)  /*  */
#define R_RMAC_MTUFC_TUFN_MASK                    0xffffffff

/* MTEFC Register bit definitions */
#define R_RMAC_MTEFC_TEFN_SHIFT                   (0)  /*  */
#define R_RMAC_MTEFC_TEFN_MASK                    0xffff

#define R_RMAC_MTEFC_RESERVED                     (1 << 31)  /* This bit is read as 0. The write value should be 0. */

/* MTXBCEU Register bit definitions */
#define R_RMAC_MTXBCEU_TBNEU_SHIFT                (0)  /*  */
#define R_RMAC_MTXBCEU_TBNEU_MASK                 0xffffffff

/* MTXBCEL Register bit definitions */
#define R_RMAC_MTXBCEL_TBNEL_SHIFT                (0)  /*  */
#define R_RMAC_MTXBCEL_TBNEL_MASK                 0xffffffff

/* MTXBCPU Register bit definitions */
#define R_RMAC_MTXBCPU_TBNPU_SHIFT                (0)  /*  */
#define R_RMAC_MTXBCPU_TBNPU_MASK                 0xffffffff

/* MTXBCPL Register bit definitions */
#define R_RMAC_MTXBCPL_TBNPL_SHIFT                (0)  /*  */
#define R_RMAC_MTXBCPL_TBNPL_MASK                 0xffffffff


/* Maximum number of channels */

#define RMAC_MAX_CHANNELS    2

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_RMAC_H */
