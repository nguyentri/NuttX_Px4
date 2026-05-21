/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_gwca.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GWCA_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GWCA_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GWCA Base Address */
#ifndef R_GWCA_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_GWCA_BASE           0x403ce000
#else
#define R_GWCA_BASE           0x503ce000
#endif
#endif

/* GWCA Register Offsets */

#define R_GWCA_GWMC_OFFSET                        0x00000000  /* GWCA Mode Configuration Register (GWMC) */
#define R_GWCA_GWMS_OFFSET                        0x00000004  /* GWCA Mode Status Register (GWMS) */
#define R_GWCA_GWIRC_OFFSET                       0x00000010  /* GWCA IPV Remapping Configuration Register [802.1Q] (GWIRC) */
#define R_GWCA_GWRDQSC_OFFSET                     0x00000014  /* GWCA RX Descriptor Queue Security Configuration Register (GWRDQSC) */
#define R_GWCA_GWRDQC_OFFSET                      0x00000018  /* GWCA RX Descriptor Queue Control Register (GWRDQC) */
#define R_GWCA_GWRDQAC_OFFSET                     0x0000001c  /* GWCA RX Descriptor Queue Arbitration Control Register (GWRDQAC) */
#define R_GWCA_GWRGC_OFFSET                       0x00000020  /* GWCA RX General Configuration Register (GWRGC) */
#define R_GWCA_GWRMFSC0_OFFSET                    0x00000040  /* GWCA Reception Maximum Frame Size Configuration Register q (GWRMFSCq) (q = 0 to 7) */
#define R_GWCA_GWRMFSC1_OFFSET                    0x00000044  /* GWCA Reception Maximum Frame Size Configuration Register q (GWRMFSCq) (q = 0 to 7) */
#define R_GWCA_GWRMFSC2_OFFSET                    0x00000048  /* GWCA Reception Maximum Frame Size Configuration Register q (GWRMFSCq) (q = 0 to 7) */
#define R_GWCA_GWRMFSC3_OFFSET                    0x0000004c  /* GWCA Reception Maximum Frame Size Configuration Register q (GWRMFSCq) (q = 0 to 7) */
#define R_GWCA_GWRMFSC4_OFFSET                    0x00000050  /* GWCA Reception Maximum Frame Size Configuration Register q (GWRMFSCq) (q = 0 to 7) */
#define R_GWCA_GWRMFSC5_OFFSET                    0x00000054  /* GWCA Reception Maximum Frame Size Configuration Register q (GWRMFSCq) (q = 0 to 7) */
#define R_GWCA_GWRMFSC6_OFFSET                    0x00000058  /* GWCA Reception Maximum Frame Size Configuration Register q (GWRMFSCq) (q = 0 to 7) */
#define R_GWCA_GWRMFSC7_OFFSET                    0x0000005c  /* GWCA Reception Maximum Frame Size Configuration Register q (GWRMFSCq) (q = 0 to 7) */
#define R_GWCA_GWRDQDC0_OFFSET                    0x00000060  /* GWCA Reception Descriptor Queue Depth Configuration Register q (GWRDQDCq) (q = 0 to 7) */
#define R_GWCA_GWRDQDC1_OFFSET                    0x00000064  /* GWCA Reception Descriptor Queue Depth Configuration Register q (GWRDQDCq) (q = 0 to 7) */
#define R_GWCA_GWRDQDC2_OFFSET                    0x00000068  /* GWCA Reception Descriptor Queue Depth Configuration Register q (GWRDQDCq) (q = 0 to 7) */
#define R_GWCA_GWRDQDC3_OFFSET                    0x0000006c  /* GWCA Reception Descriptor Queue Depth Configuration Register q (GWRDQDCq) (q = 0 to 7) */
#define R_GWCA_GWRDQDC4_OFFSET                    0x00000070  /* GWCA Reception Descriptor Queue Depth Configuration Register q (GWRDQDCq) (q = 0 to 7) */
#define R_GWCA_GWRDQDC5_OFFSET                    0x00000074  /* GWCA Reception Descriptor Queue Depth Configuration Register q (GWRDQDCq) (q = 0 to 7) */
#define R_GWCA_GWRDQDC6_OFFSET                    0x00000078  /* GWCA Reception Descriptor Queue Depth Configuration Register q (GWRDQDCq) (q = 0 to 7) */
#define R_GWCA_GWRDQDC7_OFFSET                    0x0000007c  /* GWCA Reception Descriptor Queue Depth Configuration Register q (GWRDQDCq) (q = 0 to 7) */
#define R_GWCA_GWRDQM0_OFFSET                     0x00000080  /* GWCA RX Descriptor Queue q Monitoring Register (GWRDQMq) (q = 0 to 7) */
#define R_GWCA_GWRDQM1_OFFSET                     0x00000084  /* GWCA RX Descriptor Queue q Monitoring Register (GWRDQMq) (q = 0 to 7) */
#define R_GWCA_GWRDQM2_OFFSET                     0x00000088  /* GWCA RX Descriptor Queue q Monitoring Register (GWRDQMq) (q = 0 to 7) */
#define R_GWCA_GWRDQM3_OFFSET                     0x0000008c  /* GWCA RX Descriptor Queue q Monitoring Register (GWRDQMq) (q = 0 to 7) */
#define R_GWCA_GWRDQM4_OFFSET                     0x00000090  /* GWCA RX Descriptor Queue q Monitoring Register (GWRDQMq) (q = 0 to 7) */
#define R_GWCA_GWRDQM5_OFFSET                     0x00000094  /* GWCA RX Descriptor Queue q Monitoring Register (GWRDQMq) (q = 0 to 7) */
#define R_GWCA_GWRDQM6_OFFSET                     0x00000098  /* GWCA RX Descriptor Queue q Monitoring Register (GWRDQMq) (q = 0 to 7) */
#define R_GWCA_GWRDQM7_OFFSET                     0x0000009c  /* GWCA RX Descriptor Queue q Monitoring Register (GWRDQMq) (q = 0 to 7) */
#define R_GWCA_GWRDQMLM0_OFFSET                   0x000000a0  /* GWCA RX Descriptor Queue q Max Level Monitoring Register (GWRDQMLMq) (q = 0 to 7) */
#define R_GWCA_GWRDQMLM1_OFFSET                   0x000000a4  /* GWCA RX Descriptor Queue q Max Level Monitoring Register (GWRDQMLMq) (q = 0 to 7) */
#define R_GWCA_GWRDQMLM2_OFFSET                   0x000000a8  /* GWCA RX Descriptor Queue q Max Level Monitoring Register (GWRDQMLMq) (q = 0 to 7) */
#define R_GWCA_GWRDQMLM3_OFFSET                   0x000000ac  /* GWCA RX Descriptor Queue q Max Level Monitoring Register (GWRDQMLMq) (q = 0 to 7) */
#define R_GWCA_GWRDQMLM4_OFFSET                   0x000000b0  /* GWCA RX Descriptor Queue q Max Level Monitoring Register (GWRDQMLMq) (q = 0 to 7) */
#define R_GWCA_GWRDQMLM5_OFFSET                   0x000000b4  /* GWCA RX Descriptor Queue q Max Level Monitoring Register (GWRDQMLMq) (q = 0 to 7) */
#define R_GWCA_GWRDQMLM6_OFFSET                   0x000000b8  /* GWCA RX Descriptor Queue q Max Level Monitoring Register (GWRDQMLMq) (q = 0 to 7) */
#define R_GWCA_GWRDQMLM7_OFFSET                   0x000000bc  /* GWCA RX Descriptor Queue q Max Level Monitoring Register (GWRDQMLMq) (q = 0 to 7) */
#define R_GWCA_GWMTIRM_OFFSET                     0x00000100  /* GWCA Multicast Table Initialization Register Monitoring Register (GWMTIRM) */
#define R_GWCA_GWMSTLS_OFFSET                     0x00000104  /* GWCA Multicast Table Learning Setting Register (GWMSTLS) */
#define R_GWCA_GWMSTLR_OFFSET                     0x00000108  /* GWCA Multicast Table Learning Result Register (GWMSTLR) */
#define R_GWCA_GWMSTSS_OFFSET                     0x0000010c  /* GWCA Multicast Table Searching Setting Register (GWMSTSS) */
#define R_GWCA_GWMSTSR_OFFSET                     0x00000110  /* GWCA Multicast Table Searching Result Register (GWMSTSR) */
#define R_GWCA_GWMAC0_OFFSET                      0x00000120  /* GWCA MAC Address Configuration Register 0 (GWMAC0) */
#define R_GWCA_GWMAC1_OFFSET                      0x00000124  /* GWCA MAC Address Configuration Register 1 (GWMAC1) */
#define R_GWCA_GWVCC_OFFSET                       0x00000130  /* GWCA VLAN Control Configuration Register (GWVCC) */
#define R_GWCA_GWVTC_OFFSET                       0x00000134  /* GWCA VLAN TAG Configuration Register (GWVTC) */
#define R_GWCA_GWTTFC_OFFSET                      0x00000138  /* GWCA Transmission TAG Filtering Configuration Register (GWTTFC) */
#define R_GWCA_GWTDCAC00_OFFSET                   0x00000140  /* GWCA Timestamp Descriptor Chain Address Configuration Register 0s (GWTDCAC0s) (s = 0, 1) */
#define R_GWCA_GWTDCAC10_OFFSET                   0x00000144  /* GWCA Timestamp Descriptor Chain Address Configuration Register 1s (GWTDCAC1s) (s = 0, 1) */
#define R_GWCA_GWTDCAC01_OFFSET                   0x00000148  /* GWCA Timestamp Descriptor Chain Address Configuration Register 0s (GWTDCAC0s) (s = 0, 1) */
#define R_GWCA_GWTDCAC11_OFFSET                   0x0000014c  /* GWCA Timestamp Descriptor Chain Address Configuration Register 1s (GWTDCAC1s) (s = 0, 1) */
#define R_GWCA_GWTSDCC0_OFFSET                    0x00000160  /* GWCA Timestamp Descriptor Chain Configuration Register s (GWTSDCCs) (s = 0, 1) */
#define R_GWCA_GWTSDCC1_OFFSET                    0x00000164  /* GWCA Timestamp Descriptor Chain Configuration Register s (GWTSDCCs) (s = 0, 1) */
#define R_GWCA_GWTSNM_OFFSET                      0x00000180  /* GWCA Timestamp Number Monitoring Register (GWTSNM) */
#define R_GWCA_GWTSMNM_OFFSET                     0x00000184  /* GWCA Timestamp Maximum Number Monitoring Register (GWTSMNM) */
#define R_GWCA_GWAC_OFFSET                        0x00000190  /* GWCA AXI Control Register (GWAC) */
#define R_GWCA_GWDCBAC0_OFFSET                    0x00000194  /* GWCA Descriptor Chain Base Address Configuration Register 0 (GWDCBAC0) */
#define R_GWCA_GWDCBAC1_OFFSET                    0x00000198  /* GWCA Descriptor Chain Base Address Configuration Register 1 (GWDCBAC1) */
#define R_GWCA_GWMDNC_OFFSET                      0x000001a0  /* GWCA Maximum Descriptor Number Configuration Register (GWMDNC) */
#define R_GWCA_GWTRC0_OFFSET                      0x00000200  /* GWCA Transmission Request Configuration Register i (GWTRCi) (i = 0, 1) */
#define R_GWCA_GWTRC1_OFFSET                      0x00000204  /* GWCA Transmission Request Configuration Register i (GWTRCi) (i = 0, 1) */
#define R_GWCA_GWTPC0_OFFSET                      0x00000300  /* GWCA Transmission Pause Configuration Register p (GWTPCp) (p = 0, 1) */
#define R_GWCA_GWTPC1_OFFSET                      0x00000304  /* GWCA Transmission Pause Configuration Register p (GWTPCp) (p = 0, 1) */
#define R_GWCA_GWARIRM_OFFSET                     0x00000380  /* GWCA AXI RAM Initialization Register Monitoring Register (GWARIRM) */
#define R_GWCA_GWDCC0_OFFSET                      0x00000400  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC1_OFFSET                      0x00000404  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC2_OFFSET                      0x00000408  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC3_OFFSET                      0x0000040c  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC4_OFFSET                      0x00000410  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC5_OFFSET                      0x00000414  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC6_OFFSET                      0x00000418  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC7_OFFSET                      0x0000041c  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC8_OFFSET                      0x00000420  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC9_OFFSET                      0x00000424  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC10_OFFSET                     0x00000428  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC11_OFFSET                     0x0000042c  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC12_OFFSET                     0x00000430  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC13_OFFSET                     0x00000434  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC14_OFFSET                     0x00000438  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC15_OFFSET                     0x0000043c  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC16_OFFSET                     0x00000440  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC17_OFFSET                     0x00000444  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC18_OFFSET                     0x00000448  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC19_OFFSET                     0x0000044c  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC20_OFFSET                     0x00000450  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC21_OFFSET                     0x00000454  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC22_OFFSET                     0x00000458  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC23_OFFSET                     0x0000045c  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC24_OFFSET                     0x00000460  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC25_OFFSET                     0x00000464  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC26_OFFSET                     0x00000468  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC27_OFFSET                     0x0000046c  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC28_OFFSET                     0x00000470  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC29_OFFSET                     0x00000474  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC30_OFFSET                     0x00000478  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC31_OFFSET                     0x0000047c  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC32_OFFSET                     0x00000480  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC33_OFFSET                     0x00000484  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC34_OFFSET                     0x00000488  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC35_OFFSET                     0x0000048c  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC36_OFFSET                     0x00000490  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC37_OFFSET                     0x00000494  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC38_OFFSET                     0x00000498  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC39_OFFSET                     0x0000049c  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC40_OFFSET                     0x000004a0  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC41_OFFSET                     0x000004a4  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC42_OFFSET                     0x000004a8  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC43_OFFSET                     0x000004ac  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC44_OFFSET                     0x000004b0  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC45_OFFSET                     0x000004b4  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC46_OFFSET                     0x000004b8  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC47_OFFSET                     0x000004bc  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC48_OFFSET                     0x000004c0  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC49_OFFSET                     0x000004c4  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC50_OFFSET                     0x000004c8  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC51_OFFSET                     0x000004cc  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC52_OFFSET                     0x000004d0  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC53_OFFSET                     0x000004d4  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC54_OFFSET                     0x000004d8  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC55_OFFSET                     0x000004dc  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC56_OFFSET                     0x000004e0  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC57_OFFSET                     0x000004e4  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC58_OFFSET                     0x000004e8  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC59_OFFSET                     0x000004ec  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC60_OFFSET                     0x000004f0  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC61_OFFSET                     0x000004f4  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC62_OFFSET                     0x000004f8  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWDCC63_OFFSET                     0x000004fc  /* GWCA Descriptor Chain Configuration Register i (GWDCCi) (i = 0 to 63) */
#define R_GWCA_GWAARSS_OFFSET                     0x00000800  /* GWCA AXI Address RAM Searching Setting Register (GWAARSS) */
#define R_GWCA_GWAARSR0_OFFSET                    0x00000804  /* GWCA AXI Address RAM Searching Result Register 0 (GWAARSR0) */
#define R_GWCA_GWAARSR1_OFFSET                    0x00000808  /* GWCA AXI Address RAM Searching Result Register 1 (GWAARSR1) */
#define R_GWCA_GWIDAUAS0_OFFSET                   0x00000840  /* GWCA Incremental Data Area Used Area Size Register i (GWIDAUASi) (i = 0 to 3) */
#define R_GWCA_GWIDAUAS1_OFFSET                   0x00000844  /* GWCA Incremental Data Area Used Area Size Register i (GWIDAUASi) (i = 0 to 3) */
#define R_GWCA_GWIDAUAS2_OFFSET                   0x00000848  /* GWCA Incremental Data Area Used Area Size Register i (GWIDAUASi) (i = 0 to 3) */
#define R_GWCA_GWIDAUAS3_OFFSET                   0x0000084c  /* GWCA Incremental Data Area Used Area Size Register i (GWIDAUASi) (i = 0 to 3) */
#define R_GWCA_GWIDASM0_OFFSET                    0x00000880  /* GWCA Incremental Data Area Size Monitoring Register i (GWIDASMi) (i = 0 to 3) */
#define R_GWCA_GWIDASM1_OFFSET                    0x00000884  /* GWCA Incremental Data Area Size Monitoring Register i (GWIDASMi) (i = 0 to 3) */
#define R_GWCA_GWIDASM2_OFFSET                    0x00000888  /* GWCA Incremental Data Area Size Monitoring Register i (GWIDASMi) (i = 0 to 3) */
#define R_GWCA_GWIDASM3_OFFSET                    0x0000088c  /* GWCA Incremental Data Area Size Monitoring Register i (GWIDASMi) (i = 0 to 3) */
#define R_GWCA_GWIDASAM00_OFFSET                  0x00000900  /* GWCA Incremental Data Area Start Address Monitoring Register 0i (GWIDASAM0i) (i = 0 to 3) */
#define R_GWCA_GWIDASAM10_OFFSET                  0x00000904  /* GWCA Incremental Data Area Start Address Monitoring Register 1i (GWIDASAM1i) (i = 0 to 3) */
#define R_GWCA_GWIDASAM01_OFFSET                  0x00000908  /* GWCA Incremental Data Area Start Address Monitoring Register 0i (GWIDASAM0i) (i = 0 to 3) */
#define R_GWCA_GWIDASAM11_OFFSET                  0x0000090c  /* GWCA Incremental Data Area Start Address Monitoring Register 1i (GWIDASAM1i) (i = 0 to 3) */
#define R_GWCA_GWIDASAM02_OFFSET                  0x00000910  /* GWCA Incremental Data Area Start Address Monitoring Register 0i (GWIDASAM0i) (i = 0 to 3) */
#define R_GWCA_GWIDASAM12_OFFSET                  0x00000914  /* GWCA Incremental Data Area Start Address Monitoring Register 1i (GWIDASAM1i) (i = 0 to 3) */
#define R_GWCA_GWIDASAM03_OFFSET                  0x00000918  /* GWCA Incremental Data Area Start Address Monitoring Register 0i (GWIDASAM0i) (i = 0 to 3) */
#define R_GWCA_GWIDASAM13_OFFSET                  0x0000091c  /* GWCA Incremental Data Area Start Address Monitoring Register 1i (GWIDASAM1i) (i = 0 to 3) */
#define R_GWCA_GWIDACAM00_OFFSET                  0x00000980  /* GWCA Incremental Data Area Current Address Monitoring Register 0i (GWIDACAM0i) (i = 0 to 3) */
#define R_GWCA_GWIDACAM10_OFFSET                  0x00000984  /* GWCA Incremental Data Area Current Address Monitoring Register 1i (GWIDACAM1i) (i = 0 to 3) */
#define R_GWCA_GWIDACAM01_OFFSET                  0x00000988  /* GWCA Incremental Data Area Current Address Monitoring Register 0i (GWIDACAM0i) (i = 0 to 3) */
#define R_GWCA_GWIDACAM11_OFFSET                  0x0000098c  /* GWCA Incremental Data Area Current Address Monitoring Register 1i (GWIDACAM1i) (i = 0 to 3) */
#define R_GWCA_GWIDACAM02_OFFSET                  0x00000990  /* GWCA Incremental Data Area Current Address Monitoring Register 0i (GWIDACAM0i) (i = 0 to 3) */
#define R_GWCA_GWIDACAM12_OFFSET                  0x00000994  /* GWCA Incremental Data Area Current Address Monitoring Register 1i (GWIDACAM1i) (i = 0 to 3) */
#define R_GWCA_GWIDACAM03_OFFSET                  0x00000998  /* GWCA Incremental Data Area Current Address Monitoring Register 0i (GWIDACAM0i) (i = 0 to 3) */
#define R_GWCA_GWIDACAM13_OFFSET                  0x0000099c  /* GWCA Incremental Data Area Current Address Monitoring Register 1i (GWIDACAM1i) (i = 0 to 3) */
#define R_GWCA_GWGRLC_OFFSET                      0x00000a00  /* GWCA Global Rate Limiter Configuration Register (GWGRLC) */
#define R_GWCA_GWGRLULC_OFFSET                    0x00000a04  /* GWCA Global Rate Limiter Upper Limit Configuration Register (GWGRLULC) */
#define R_GWCA_GWRLC0_OFFSET                      0x00000a80  /* GWCA Rate Limiter Configuration Register i (GWRLCi) (i = 0 to 7) */
#define R_GWCA_GWRLULC0_OFFSET                    0x00000a84  /* GWCA Rate Limiter Upper Limit Configuration Register i (GWRLULCi) (i = 0 to 7) */
#define R_GWCA_GWRLC1_OFFSET                      0x00000a88  /* GWCA Rate Limiter Configuration Register i (GWRLCi) (i = 0 to 7) */
#define R_GWCA_GWRLULC1_OFFSET                    0x00000a8c  /* GWCA Rate Limiter Upper Limit Configuration Register i (GWRLULCi) (i = 0 to 7) */
#define R_GWCA_GWRLC2_OFFSET                      0x00000a90  /* GWCA Rate Limiter Configuration Register i (GWRLCi) (i = 0 to 7) */
#define R_GWCA_GWRLULC2_OFFSET                    0x00000a94  /* GWCA Rate Limiter Upper Limit Configuration Register i (GWRLULCi) (i = 0 to 7) */
#define R_GWCA_GWRLC3_OFFSET                      0x00000a98  /* GWCA Rate Limiter Configuration Register i (GWRLCi) (i = 0 to 7) */
#define R_GWCA_GWRLULC3_OFFSET                    0x00000a9c  /* GWCA Rate Limiter Upper Limit Configuration Register i (GWRLULCi) (i = 0 to 7) */
#define R_GWCA_GWRLC4_OFFSET                      0x00000aa0  /* GWCA Rate Limiter Configuration Register i (GWRLCi) (i = 0 to 7) */
#define R_GWCA_GWRLULC4_OFFSET                    0x00000aa4  /* GWCA Rate Limiter Upper Limit Configuration Register i (GWRLULCi) (i = 0 to 7) */
#define R_GWCA_GWRLC5_OFFSET                      0x00000aa8  /* GWCA Rate Limiter Configuration Register i (GWRLCi) (i = 0 to 7) */
#define R_GWCA_GWRLULC5_OFFSET                    0x00000aac  /* GWCA Rate Limiter Upper Limit Configuration Register i (GWRLULCi) (i = 0 to 7) */
#define R_GWCA_GWRLC6_OFFSET                      0x00000ab0  /* GWCA Rate Limiter Configuration Register i (GWRLCi) (i = 0 to 7) */
#define R_GWCA_GWRLULC6_OFFSET                    0x00000ab4  /* GWCA Rate Limiter Upper Limit Configuration Register i (GWRLULCi) (i = 0 to 7) */
#define R_GWCA_GWRLC7_OFFSET                      0x00000ab8  /* GWCA Rate Limiter Configuration Register i (GWRLCi) (i = 0 to 7) */
#define R_GWCA_GWRLULC7_OFFSET                    0x00000abc  /* GWCA Rate Limiter Upper Limit Configuration Register i (GWRLULCi) (i = 0 to 7) */
#define R_GWCA_GWIDPC_OFFSET                      0x00000b80  /* GWCA Interrupt Delay Prescaler Configuration Register (GWIDPC) */
#define R_GWCA_GWIDC0_OFFSET                      0x00000c00  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC1_OFFSET                      0x00000c04  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC2_OFFSET                      0x00000c08  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC3_OFFSET                      0x00000c0c  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC4_OFFSET                      0x00000c10  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC5_OFFSET                      0x00000c14  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC6_OFFSET                      0x00000c18  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC7_OFFSET                      0x00000c1c  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC8_OFFSET                      0x00000c20  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC9_OFFSET                      0x00000c24  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC10_OFFSET                     0x00000c28  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC11_OFFSET                     0x00000c2c  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC12_OFFSET                     0x00000c30  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC13_OFFSET                     0x00000c34  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC14_OFFSET                     0x00000c38  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC15_OFFSET                     0x00000c3c  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC16_OFFSET                     0x00000c40  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC17_OFFSET                     0x00000c44  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC18_OFFSET                     0x00000c48  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC19_OFFSET                     0x00000c4c  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC20_OFFSET                     0x00000c50  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC21_OFFSET                     0x00000c54  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC22_OFFSET                     0x00000c58  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC23_OFFSET                     0x00000c5c  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC24_OFFSET                     0x00000c60  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC25_OFFSET                     0x00000c64  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC26_OFFSET                     0x00000c68  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC27_OFFSET                     0x00000c6c  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC28_OFFSET                     0x00000c70  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC29_OFFSET                     0x00000c74  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC30_OFFSET                     0x00000c78  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC31_OFFSET                     0x00000c7c  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC32_OFFSET                     0x00000c80  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC33_OFFSET                     0x00000c84  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC34_OFFSET                     0x00000c88  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC35_OFFSET                     0x00000c8c  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC36_OFFSET                     0x00000c90  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC37_OFFSET                     0x00000c94  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC38_OFFSET                     0x00000c98  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC39_OFFSET                     0x00000c9c  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC40_OFFSET                     0x00000ca0  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC41_OFFSET                     0x00000ca4  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC42_OFFSET                     0x00000ca8  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC43_OFFSET                     0x00000cac  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC44_OFFSET                     0x00000cb0  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC45_OFFSET                     0x00000cb4  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC46_OFFSET                     0x00000cb8  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC47_OFFSET                     0x00000cbc  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC48_OFFSET                     0x00000cc0  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC49_OFFSET                     0x00000cc4  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC50_OFFSET                     0x00000cc8  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC51_OFFSET                     0x00000ccc  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC52_OFFSET                     0x00000cd0  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC53_OFFSET                     0x00000cd4  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC54_OFFSET                     0x00000cd8  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC55_OFFSET                     0x00000cdc  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC56_OFFSET                     0x00000ce0  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC57_OFFSET                     0x00000ce4  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC58_OFFSET                     0x00000ce8  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC59_OFFSET                     0x00000cec  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC60_OFFSET                     0x00000cf0  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC61_OFFSET                     0x00000cf4  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC62_OFFSET                     0x00000cf8  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC63_OFFSET                     0x00000cfc  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWIDC64_OFFSET                     0x00000d00  /* GWCA Interrupt Delay Configuration Register (GWIDCi) (i = 0 to 64) */
#define R_GWCA_GWRDCN_OFFSET                      0x00001000  /* GWCA Received Data Counter Register (GWRDCN) */
#define R_GWCA_GWTDCN_OFFSET                      0x00001004  /* GWCA Transmitted Data Counter Register (GWTDCN) */
#define R_GWCA_GWTSCN_OFFSET                      0x00001008  /* GWCA Timestamp Counter Register (GWTSCN) */
#define R_GWCA_GWTSOVFECN_OFFSET                  0x0000100c  /* GWCA Timestamp Overflow Error Counter Register (GWTSOVFECN) */
#define R_GWCA_GWUSMFSECN_OFFSET                  0x00001010  /* GWCA Under Switch Minimum Frame Size Error Counter Register (GWUSMFSECN) */
#define R_GWCA_GWTFECN_OFFSET                     0x00001014  /* GWCA TAG Filtering Error Counter Register (GWTFECN) */
#define R_GWCA_GWSEQECN_OFFSET                    0x00001018  /* GWCA Sequence Error Counter Register (GWSEQECN) */
#define R_GWCA_GWTXDNECN_OFFSET                   0x00001020  /* GWCA TX Descriptor Number Error Counter Register (GWTXDNECN) */
#define R_GWCA_GWFSECN_OFFSET                     0x00001024  /* GWCA Frame Size Error Counter Register (GWFSECN) */
#define R_GWCA_GWTDFECN_OFFSET                    0x00001028  /* GWCA Timestamp Descriptor Full Error Counter Register (GWTDFECN) */
#define R_GWCA_GWTSDNECN_OFFSET                   0x0000102c  /* GWCA Timestamp Descriptor Number Error Counter Register (GWTSDNECN) */
#define R_GWCA_GWDQOECN_OFFSET                    0x00001030  /* GWCA Descriptor Queue Overflow Error Counter Register (GWDQOECN) */
#define R_GWCA_GWDQSECN_OFFSET                    0x00001034  /* GWCA Descriptor Queue Security Error Counter Register (GWDQSECN) */
#define R_GWCA_GWDFECN_OFFSET                     0x00001038  /* GWCA Descriptor Full Error Counter Register (GWDFECN) */
#define R_GWCA_GWDSECN_OFFSET                     0x0000103c  /* GWCA Descriptor Security Error Counter Register (GWDSECN) */
#define R_GWCA_GWDSZECN_OFFSET                    0x00001040  /* GWCA Data Size Error Counter Register (GWDSZECN) */
#define R_GWCA_GWDCTECN_OFFSET                    0x00001044  /* GWCA Descriptor Chain Type Error Counter Register (GWDCTECN) */
#define R_GWCA_GWRXDNECN_OFFSET                   0x00001048  /* GWCA RX Descriptor Number Error Counter Register (GWRXDNECN) */
#define R_GWCA_GWDIS0_OFFSET                      0x00001100  /* GWCA Data Interrupt Status Register i (GWDISi) (i = 0, 1) */
#define R_GWCA_GWDIE0_OFFSET                      0x00001104  /* GWCA Data Interrupt Enable Register i (GWDIEi) (i = 0, 1) */
#define R_GWCA_GWDID0_OFFSET                      0x00001108  /* GWCA Data Interrupt Disable Register i (GWDIDi) (i = 0, 1) */
#define R_GWCA_GWDIDS0_OFFSET                     0x0000110c  /* GWCA Data Interrupt Delayed Status Register i (GWDIDSi) (i = 0, 1) */
#define R_GWCA_GWDIS1_OFFSET                      0x00001110  /* GWCA Data Interrupt Status Register i (GWDISi) (i = 0, 1) */
#define R_GWCA_GWDIE1_OFFSET                      0x00001114  /* GWCA Data Interrupt Enable Register i (GWDIEi) (i = 0, 1) */
#define R_GWCA_GWDID1_OFFSET                      0x00001118  /* GWCA Data Interrupt Disable Register i (GWDIDi) (i = 0, 1) */
#define R_GWCA_GWDIDS1_OFFSET                     0x0000111c  /* GWCA Data Interrupt Delayed Status Register i (GWDIDSi) (i = 0, 1) */
#define R_GWCA_GWTSDIS_OFFSET                     0x00001180  /* GWCA Timestamp Data Interrupt Status Register (GWTSDIS) */
#define R_GWCA_GWTSDIE_OFFSET                     0x00001184  /* GWCA Timestamp Data Interrupt Enable Register (GWTSDIE) */
#define R_GWCA_GWTSDID_OFFSET                     0x00001188  /* GWCA Timestamp Data Interrupt Disable Register (GWTSDID) */
#define R_GWCA_GWEIS0_OFFSET                      0x00001190  /* GWCA Error Interrupt Status Register 0 (GWEIS0) */
#define R_GWCA_GWEIE0_OFFSET                      0x00001194  /* GWCA Error Interrupt Enable Register 0 (GWEIE0) */
#define R_GWCA_GWEID0_OFFSET                      0x00001198  /* GWCA Error Interrupt Disable Register 0 (GWEID0) */
#define R_GWCA_GWEIS1_OFFSET                      0x000011a0  /* GWCA Error Interrupt Status Register 1 (GWEIS1) */
#define R_GWCA_GWEIE1_OFFSET                      0x000011a4  /* GWCA Error Interrupt Enable Register 1 (GWEIE1) */
#define R_GWCA_GWEID1_OFFSET                      0x000011a8  /* GWCA Error Interrupt Disable Register 1 (GWEID1) */
#define R_GWCA_GWEIS20_OFFSET                     0x00001200  /* GWCA Error Interrupt Status Register 2i (GWEIS2i) (i = 0, 1) */
#define R_GWCA_GWEIE20_OFFSET                     0x00001204  /* GWCA Error Interrupt Enable Register 2i (GWEIE2i) (i = 0, 1) */
#define R_GWCA_GWEID20_OFFSET                     0x00001208  /* GWCA Error Interrupt Disable Register 2i (GWEID2i) (i = 0, 1) */
#define R_GWCA_GWEIS21_OFFSET                     0x00001210  /* GWCA Error Interrupt Status Register 2i (GWEIS2i) (i = 0, 1) */
#define R_GWCA_GWEIE21_OFFSET                     0x00001214  /* GWCA Error Interrupt Enable Register 2i (GWEIE2i) (i = 0, 1) */
#define R_GWCA_GWEID21_OFFSET                     0x00001218  /* GWCA Error Interrupt Disable Register 2i (GWEID2i) (i = 0, 1) */
#define R_GWCA_GWEIS3_OFFSET                      0x00001280  /* GWCA Error Interrupt Status Register 3 (GWEIS3) */
#define R_GWCA_GWEIE3_OFFSET                      0x00001284  /* GWCA Error Interrupt Enable Register 3 (GWEIE3) */
#define R_GWCA_GWEID3_OFFSET                      0x00001288  /* GWCA Error Interrupt Disable Register 3 (GWEID3) */
#define R_GWCA_GWEIS4_OFFSET                      0x00001290  /* GWCA Error Interrupt Status Register 4 (GWEIS4) */
#define R_GWCA_GWEIE4_OFFSET                      0x00001294  /* GWCA Error Interrupt Enable Register 4 (GWEIE4) */
#define R_GWCA_GWEID4_OFFSET                      0x00001298  /* GWCA Error Interrupt Disable Register 4 (GWEID4) */
#define R_GWCA_GWEIS5_OFFSET                      0x000012a0  /* GWCA Error Interrupt Status Register 5 (GWEIS5) */
#define R_GWCA_GWEIE5_OFFSET                      0x000012a4  /* GWCA Error Interrupt Enable Register 5 (GWEIE5) */
#define R_GWCA_GWEID5_OFFSET                      0x000012a8  /* GWCA Error Interrupt Disable Register 5 (GWEID5) */

/* GWCA Register Addresses */

#define R_GWCA_GWMC                               (R_GWCA_BASE + R_GWCA_GWMC_OFFSET)
#define R_GWCA_GWMS                               (R_GWCA_BASE + R_GWCA_GWMS_OFFSET)
#define R_GWCA_GWIRC                              (R_GWCA_BASE + R_GWCA_GWIRC_OFFSET)
#define R_GWCA_GWRDQSC                            (R_GWCA_BASE + R_GWCA_GWRDQSC_OFFSET)
#define R_GWCA_GWRDQC                             (R_GWCA_BASE + R_GWCA_GWRDQC_OFFSET)
#define R_GWCA_GWRDQAC                            (R_GWCA_BASE + R_GWCA_GWRDQAC_OFFSET)
#define R_GWCA_GWRGC                              (R_GWCA_BASE + R_GWCA_GWRGC_OFFSET)
#define R_GWCA_GWRMFSC0                           (R_GWCA_BASE + R_GWCA_GWRMFSC0_OFFSET)
#define R_GWCA_GWRMFSC1                           (R_GWCA_BASE + R_GWCA_GWRMFSC1_OFFSET)
#define R_GWCA_GWRMFSC2                           (R_GWCA_BASE + R_GWCA_GWRMFSC2_OFFSET)
#define R_GWCA_GWRMFSC3                           (R_GWCA_BASE + R_GWCA_GWRMFSC3_OFFSET)
#define R_GWCA_GWRMFSC4                           (R_GWCA_BASE + R_GWCA_GWRMFSC4_OFFSET)
#define R_GWCA_GWRMFSC5                           (R_GWCA_BASE + R_GWCA_GWRMFSC5_OFFSET)
#define R_GWCA_GWRMFSC6                           (R_GWCA_BASE + R_GWCA_GWRMFSC6_OFFSET)
#define R_GWCA_GWRMFSC7                           (R_GWCA_BASE + R_GWCA_GWRMFSC7_OFFSET)
#define R_GWCA_GWRDQDC0                           (R_GWCA_BASE + R_GWCA_GWRDQDC0_OFFSET)
#define R_GWCA_GWRDQDC1                           (R_GWCA_BASE + R_GWCA_GWRDQDC1_OFFSET)
#define R_GWCA_GWRDQDC2                           (R_GWCA_BASE + R_GWCA_GWRDQDC2_OFFSET)
#define R_GWCA_GWRDQDC3                           (R_GWCA_BASE + R_GWCA_GWRDQDC3_OFFSET)
#define R_GWCA_GWRDQDC4                           (R_GWCA_BASE + R_GWCA_GWRDQDC4_OFFSET)
#define R_GWCA_GWRDQDC5                           (R_GWCA_BASE + R_GWCA_GWRDQDC5_OFFSET)
#define R_GWCA_GWRDQDC6                           (R_GWCA_BASE + R_GWCA_GWRDQDC6_OFFSET)
#define R_GWCA_GWRDQDC7                           (R_GWCA_BASE + R_GWCA_GWRDQDC7_OFFSET)
#define R_GWCA_GWRDQM0                            (R_GWCA_BASE + R_GWCA_GWRDQM0_OFFSET)
#define R_GWCA_GWRDQM1                            (R_GWCA_BASE + R_GWCA_GWRDQM1_OFFSET)
#define R_GWCA_GWRDQM2                            (R_GWCA_BASE + R_GWCA_GWRDQM2_OFFSET)
#define R_GWCA_GWRDQM3                            (R_GWCA_BASE + R_GWCA_GWRDQM3_OFFSET)
#define R_GWCA_GWRDQM4                            (R_GWCA_BASE + R_GWCA_GWRDQM4_OFFSET)
#define R_GWCA_GWRDQM5                            (R_GWCA_BASE + R_GWCA_GWRDQM5_OFFSET)
#define R_GWCA_GWRDQM6                            (R_GWCA_BASE + R_GWCA_GWRDQM6_OFFSET)
#define R_GWCA_GWRDQM7                            (R_GWCA_BASE + R_GWCA_GWRDQM7_OFFSET)
#define R_GWCA_GWRDQMLM0                          (R_GWCA_BASE + R_GWCA_GWRDQMLM0_OFFSET)
#define R_GWCA_GWRDQMLM1                          (R_GWCA_BASE + R_GWCA_GWRDQMLM1_OFFSET)
#define R_GWCA_GWRDQMLM2                          (R_GWCA_BASE + R_GWCA_GWRDQMLM2_OFFSET)
#define R_GWCA_GWRDQMLM3                          (R_GWCA_BASE + R_GWCA_GWRDQMLM3_OFFSET)
#define R_GWCA_GWRDQMLM4                          (R_GWCA_BASE + R_GWCA_GWRDQMLM4_OFFSET)
#define R_GWCA_GWRDQMLM5                          (R_GWCA_BASE + R_GWCA_GWRDQMLM5_OFFSET)
#define R_GWCA_GWRDQMLM6                          (R_GWCA_BASE + R_GWCA_GWRDQMLM6_OFFSET)
#define R_GWCA_GWRDQMLM7                          (R_GWCA_BASE + R_GWCA_GWRDQMLM7_OFFSET)
#define R_GWCA_GWMTIRM                            (R_GWCA_BASE + R_GWCA_GWMTIRM_OFFSET)
#define R_GWCA_GWMSTLS                            (R_GWCA_BASE + R_GWCA_GWMSTLS_OFFSET)
#define R_GWCA_GWMSTLR                            (R_GWCA_BASE + R_GWCA_GWMSTLR_OFFSET)
#define R_GWCA_GWMSTSS                            (R_GWCA_BASE + R_GWCA_GWMSTSS_OFFSET)
#define R_GWCA_GWMSTSR                            (R_GWCA_BASE + R_GWCA_GWMSTSR_OFFSET)
#define R_GWCA_GWMAC0                             (R_GWCA_BASE + R_GWCA_GWMAC0_OFFSET)
#define R_GWCA_GWMAC1                             (R_GWCA_BASE + R_GWCA_GWMAC1_OFFSET)
#define R_GWCA_GWVCC                              (R_GWCA_BASE + R_GWCA_GWVCC_OFFSET)
#define R_GWCA_GWVTC                              (R_GWCA_BASE + R_GWCA_GWVTC_OFFSET)
#define R_GWCA_GWTTFC                             (R_GWCA_BASE + R_GWCA_GWTTFC_OFFSET)
#define R_GWCA_GWTDCAC00                          (R_GWCA_BASE + R_GWCA_GWTDCAC00_OFFSET)
#define R_GWCA_GWTDCAC10                          (R_GWCA_BASE + R_GWCA_GWTDCAC10_OFFSET)
#define R_GWCA_GWTDCAC01                          (R_GWCA_BASE + R_GWCA_GWTDCAC01_OFFSET)
#define R_GWCA_GWTDCAC11                          (R_GWCA_BASE + R_GWCA_GWTDCAC11_OFFSET)
#define R_GWCA_GWTSDCC0                           (R_GWCA_BASE + R_GWCA_GWTSDCC0_OFFSET)
#define R_GWCA_GWTSDCC1                           (R_GWCA_BASE + R_GWCA_GWTSDCC1_OFFSET)
#define R_GWCA_GWTSNM                             (R_GWCA_BASE + R_GWCA_GWTSNM_OFFSET)
#define R_GWCA_GWTSMNM                            (R_GWCA_BASE + R_GWCA_GWTSMNM_OFFSET)
#define R_GWCA_GWAC                               (R_GWCA_BASE + R_GWCA_GWAC_OFFSET)
#define R_GWCA_GWDCBAC0                           (R_GWCA_BASE + R_GWCA_GWDCBAC0_OFFSET)
#define R_GWCA_GWDCBAC1                           (R_GWCA_BASE + R_GWCA_GWDCBAC1_OFFSET)
#define R_GWCA_GWMDNC                             (R_GWCA_BASE + R_GWCA_GWMDNC_OFFSET)
#define R_GWCA_GWTRC0                             (R_GWCA_BASE + R_GWCA_GWTRC0_OFFSET)
#define R_GWCA_GWTRC1                             (R_GWCA_BASE + R_GWCA_GWTRC1_OFFSET)
#define R_GWCA_GWTPC0                             (R_GWCA_BASE + R_GWCA_GWTPC0_OFFSET)
#define R_GWCA_GWTPC1                             (R_GWCA_BASE + R_GWCA_GWTPC1_OFFSET)
#define R_GWCA_GWARIRM                            (R_GWCA_BASE + R_GWCA_GWARIRM_OFFSET)
#define R_GWCA_GWDCC0                             (R_GWCA_BASE + R_GWCA_GWDCC0_OFFSET)
#define R_GWCA_GWDCC1                             (R_GWCA_BASE + R_GWCA_GWDCC1_OFFSET)
#define R_GWCA_GWDCC2                             (R_GWCA_BASE + R_GWCA_GWDCC2_OFFSET)
#define R_GWCA_GWDCC3                             (R_GWCA_BASE + R_GWCA_GWDCC3_OFFSET)
#define R_GWCA_GWDCC4                             (R_GWCA_BASE + R_GWCA_GWDCC4_OFFSET)
#define R_GWCA_GWDCC5                             (R_GWCA_BASE + R_GWCA_GWDCC5_OFFSET)
#define R_GWCA_GWDCC6                             (R_GWCA_BASE + R_GWCA_GWDCC6_OFFSET)
#define R_GWCA_GWDCC7                             (R_GWCA_BASE + R_GWCA_GWDCC7_OFFSET)
#define R_GWCA_GWDCC8                             (R_GWCA_BASE + R_GWCA_GWDCC8_OFFSET)
#define R_GWCA_GWDCC9                             (R_GWCA_BASE + R_GWCA_GWDCC9_OFFSET)
#define R_GWCA_GWDCC10                            (R_GWCA_BASE + R_GWCA_GWDCC10_OFFSET)
#define R_GWCA_GWDCC11                            (R_GWCA_BASE + R_GWCA_GWDCC11_OFFSET)
#define R_GWCA_GWDCC12                            (R_GWCA_BASE + R_GWCA_GWDCC12_OFFSET)
#define R_GWCA_GWDCC13                            (R_GWCA_BASE + R_GWCA_GWDCC13_OFFSET)
#define R_GWCA_GWDCC14                            (R_GWCA_BASE + R_GWCA_GWDCC14_OFFSET)
#define R_GWCA_GWDCC15                            (R_GWCA_BASE + R_GWCA_GWDCC15_OFFSET)
#define R_GWCA_GWDCC16                            (R_GWCA_BASE + R_GWCA_GWDCC16_OFFSET)
#define R_GWCA_GWDCC17                            (R_GWCA_BASE + R_GWCA_GWDCC17_OFFSET)
#define R_GWCA_GWDCC18                            (R_GWCA_BASE + R_GWCA_GWDCC18_OFFSET)
#define R_GWCA_GWDCC19                            (R_GWCA_BASE + R_GWCA_GWDCC19_OFFSET)
#define R_GWCA_GWDCC20                            (R_GWCA_BASE + R_GWCA_GWDCC20_OFFSET)
#define R_GWCA_GWDCC21                            (R_GWCA_BASE + R_GWCA_GWDCC21_OFFSET)
#define R_GWCA_GWDCC22                            (R_GWCA_BASE + R_GWCA_GWDCC22_OFFSET)
#define R_GWCA_GWDCC23                            (R_GWCA_BASE + R_GWCA_GWDCC23_OFFSET)
#define R_GWCA_GWDCC24                            (R_GWCA_BASE + R_GWCA_GWDCC24_OFFSET)
#define R_GWCA_GWDCC25                            (R_GWCA_BASE + R_GWCA_GWDCC25_OFFSET)
#define R_GWCA_GWDCC26                            (R_GWCA_BASE + R_GWCA_GWDCC26_OFFSET)
#define R_GWCA_GWDCC27                            (R_GWCA_BASE + R_GWCA_GWDCC27_OFFSET)
#define R_GWCA_GWDCC28                            (R_GWCA_BASE + R_GWCA_GWDCC28_OFFSET)
#define R_GWCA_GWDCC29                            (R_GWCA_BASE + R_GWCA_GWDCC29_OFFSET)
#define R_GWCA_GWDCC30                            (R_GWCA_BASE + R_GWCA_GWDCC30_OFFSET)
#define R_GWCA_GWDCC31                            (R_GWCA_BASE + R_GWCA_GWDCC31_OFFSET)
#define R_GWCA_GWDCC32                            (R_GWCA_BASE + R_GWCA_GWDCC32_OFFSET)
#define R_GWCA_GWDCC33                            (R_GWCA_BASE + R_GWCA_GWDCC33_OFFSET)
#define R_GWCA_GWDCC34                            (R_GWCA_BASE + R_GWCA_GWDCC34_OFFSET)
#define R_GWCA_GWDCC35                            (R_GWCA_BASE + R_GWCA_GWDCC35_OFFSET)
#define R_GWCA_GWDCC36                            (R_GWCA_BASE + R_GWCA_GWDCC36_OFFSET)
#define R_GWCA_GWDCC37                            (R_GWCA_BASE + R_GWCA_GWDCC37_OFFSET)
#define R_GWCA_GWDCC38                            (R_GWCA_BASE + R_GWCA_GWDCC38_OFFSET)
#define R_GWCA_GWDCC39                            (R_GWCA_BASE + R_GWCA_GWDCC39_OFFSET)
#define R_GWCA_GWDCC40                            (R_GWCA_BASE + R_GWCA_GWDCC40_OFFSET)
#define R_GWCA_GWDCC41                            (R_GWCA_BASE + R_GWCA_GWDCC41_OFFSET)
#define R_GWCA_GWDCC42                            (R_GWCA_BASE + R_GWCA_GWDCC42_OFFSET)
#define R_GWCA_GWDCC43                            (R_GWCA_BASE + R_GWCA_GWDCC43_OFFSET)
#define R_GWCA_GWDCC44                            (R_GWCA_BASE + R_GWCA_GWDCC44_OFFSET)
#define R_GWCA_GWDCC45                            (R_GWCA_BASE + R_GWCA_GWDCC45_OFFSET)
#define R_GWCA_GWDCC46                            (R_GWCA_BASE + R_GWCA_GWDCC46_OFFSET)
#define R_GWCA_GWDCC47                            (R_GWCA_BASE + R_GWCA_GWDCC47_OFFSET)
#define R_GWCA_GWDCC48                            (R_GWCA_BASE + R_GWCA_GWDCC48_OFFSET)
#define R_GWCA_GWDCC49                            (R_GWCA_BASE + R_GWCA_GWDCC49_OFFSET)
#define R_GWCA_GWDCC50                            (R_GWCA_BASE + R_GWCA_GWDCC50_OFFSET)
#define R_GWCA_GWDCC51                            (R_GWCA_BASE + R_GWCA_GWDCC51_OFFSET)
#define R_GWCA_GWDCC52                            (R_GWCA_BASE + R_GWCA_GWDCC52_OFFSET)
#define R_GWCA_GWDCC53                            (R_GWCA_BASE + R_GWCA_GWDCC53_OFFSET)
#define R_GWCA_GWDCC54                            (R_GWCA_BASE + R_GWCA_GWDCC54_OFFSET)
#define R_GWCA_GWDCC55                            (R_GWCA_BASE + R_GWCA_GWDCC55_OFFSET)
#define R_GWCA_GWDCC56                            (R_GWCA_BASE + R_GWCA_GWDCC56_OFFSET)
#define R_GWCA_GWDCC57                            (R_GWCA_BASE + R_GWCA_GWDCC57_OFFSET)
#define R_GWCA_GWDCC58                            (R_GWCA_BASE + R_GWCA_GWDCC58_OFFSET)
#define R_GWCA_GWDCC59                            (R_GWCA_BASE + R_GWCA_GWDCC59_OFFSET)
#define R_GWCA_GWDCC60                            (R_GWCA_BASE + R_GWCA_GWDCC60_OFFSET)
#define R_GWCA_GWDCC61                            (R_GWCA_BASE + R_GWCA_GWDCC61_OFFSET)
#define R_GWCA_GWDCC62                            (R_GWCA_BASE + R_GWCA_GWDCC62_OFFSET)
#define R_GWCA_GWDCC63                            (R_GWCA_BASE + R_GWCA_GWDCC63_OFFSET)
#define R_GWCA_GWAARSS                            (R_GWCA_BASE + R_GWCA_GWAARSS_OFFSET)
#define R_GWCA_GWAARSR0                           (R_GWCA_BASE + R_GWCA_GWAARSR0_OFFSET)
#define R_GWCA_GWAARSR1                           (R_GWCA_BASE + R_GWCA_GWAARSR1_OFFSET)
#define R_GWCA_GWIDAUAS0                          (R_GWCA_BASE + R_GWCA_GWIDAUAS0_OFFSET)
#define R_GWCA_GWIDAUAS1                          (R_GWCA_BASE + R_GWCA_GWIDAUAS1_OFFSET)
#define R_GWCA_GWIDAUAS2                          (R_GWCA_BASE + R_GWCA_GWIDAUAS2_OFFSET)
#define R_GWCA_GWIDAUAS3                          (R_GWCA_BASE + R_GWCA_GWIDAUAS3_OFFSET)
#define R_GWCA_GWIDASM0                           (R_GWCA_BASE + R_GWCA_GWIDASM0_OFFSET)
#define R_GWCA_GWIDASM1                           (R_GWCA_BASE + R_GWCA_GWIDASM1_OFFSET)
#define R_GWCA_GWIDASM2                           (R_GWCA_BASE + R_GWCA_GWIDASM2_OFFSET)
#define R_GWCA_GWIDASM3                           (R_GWCA_BASE + R_GWCA_GWIDASM3_OFFSET)
#define R_GWCA_GWIDASAM00                         (R_GWCA_BASE + R_GWCA_GWIDASAM00_OFFSET)
#define R_GWCA_GWIDASAM10                         (R_GWCA_BASE + R_GWCA_GWIDASAM10_OFFSET)
#define R_GWCA_GWIDASAM01                         (R_GWCA_BASE + R_GWCA_GWIDASAM01_OFFSET)
#define R_GWCA_GWIDASAM11                         (R_GWCA_BASE + R_GWCA_GWIDASAM11_OFFSET)
#define R_GWCA_GWIDASAM02                         (R_GWCA_BASE + R_GWCA_GWIDASAM02_OFFSET)
#define R_GWCA_GWIDASAM12                         (R_GWCA_BASE + R_GWCA_GWIDASAM12_OFFSET)
#define R_GWCA_GWIDASAM03                         (R_GWCA_BASE + R_GWCA_GWIDASAM03_OFFSET)
#define R_GWCA_GWIDASAM13                         (R_GWCA_BASE + R_GWCA_GWIDASAM13_OFFSET)
#define R_GWCA_GWIDACAM00                         (R_GWCA_BASE + R_GWCA_GWIDACAM00_OFFSET)
#define R_GWCA_GWIDACAM10                         (R_GWCA_BASE + R_GWCA_GWIDACAM10_OFFSET)
#define R_GWCA_GWIDACAM01                         (R_GWCA_BASE + R_GWCA_GWIDACAM01_OFFSET)
#define R_GWCA_GWIDACAM11                         (R_GWCA_BASE + R_GWCA_GWIDACAM11_OFFSET)
#define R_GWCA_GWIDACAM02                         (R_GWCA_BASE + R_GWCA_GWIDACAM02_OFFSET)
#define R_GWCA_GWIDACAM12                         (R_GWCA_BASE + R_GWCA_GWIDACAM12_OFFSET)
#define R_GWCA_GWIDACAM03                         (R_GWCA_BASE + R_GWCA_GWIDACAM03_OFFSET)
#define R_GWCA_GWIDACAM13                         (R_GWCA_BASE + R_GWCA_GWIDACAM13_OFFSET)
#define R_GWCA_GWGRLC                             (R_GWCA_BASE + R_GWCA_GWGRLC_OFFSET)
#define R_GWCA_GWGRLULC                           (R_GWCA_BASE + R_GWCA_GWGRLULC_OFFSET)
#define R_GWCA_GWRLC0                             (R_GWCA_BASE + R_GWCA_GWRLC0_OFFSET)
#define R_GWCA_GWRLULC0                           (R_GWCA_BASE + R_GWCA_GWRLULC0_OFFSET)
#define R_GWCA_GWRLC1                             (R_GWCA_BASE + R_GWCA_GWRLC1_OFFSET)
#define R_GWCA_GWRLULC1                           (R_GWCA_BASE + R_GWCA_GWRLULC1_OFFSET)
#define R_GWCA_GWRLC2                             (R_GWCA_BASE + R_GWCA_GWRLC2_OFFSET)
#define R_GWCA_GWRLULC2                           (R_GWCA_BASE + R_GWCA_GWRLULC2_OFFSET)
#define R_GWCA_GWRLC3                             (R_GWCA_BASE + R_GWCA_GWRLC3_OFFSET)
#define R_GWCA_GWRLULC3                           (R_GWCA_BASE + R_GWCA_GWRLULC3_OFFSET)
#define R_GWCA_GWRLC4                             (R_GWCA_BASE + R_GWCA_GWRLC4_OFFSET)
#define R_GWCA_GWRLULC4                           (R_GWCA_BASE + R_GWCA_GWRLULC4_OFFSET)
#define R_GWCA_GWRLC5                             (R_GWCA_BASE + R_GWCA_GWRLC5_OFFSET)
#define R_GWCA_GWRLULC5                           (R_GWCA_BASE + R_GWCA_GWRLULC5_OFFSET)
#define R_GWCA_GWRLC6                             (R_GWCA_BASE + R_GWCA_GWRLC6_OFFSET)
#define R_GWCA_GWRLULC6                           (R_GWCA_BASE + R_GWCA_GWRLULC6_OFFSET)
#define R_GWCA_GWRLC7                             (R_GWCA_BASE + R_GWCA_GWRLC7_OFFSET)
#define R_GWCA_GWRLULC7                           (R_GWCA_BASE + R_GWCA_GWRLULC7_OFFSET)
#define R_GWCA_GWIDPC                             (R_GWCA_BASE + R_GWCA_GWIDPC_OFFSET)
#define R_GWCA_GWIDC0                             (R_GWCA_BASE + R_GWCA_GWIDC0_OFFSET)
#define R_GWCA_GWIDC1                             (R_GWCA_BASE + R_GWCA_GWIDC1_OFFSET)
#define R_GWCA_GWIDC2                             (R_GWCA_BASE + R_GWCA_GWIDC2_OFFSET)
#define R_GWCA_GWIDC3                             (R_GWCA_BASE + R_GWCA_GWIDC3_OFFSET)
#define R_GWCA_GWIDC4                             (R_GWCA_BASE + R_GWCA_GWIDC4_OFFSET)
#define R_GWCA_GWIDC5                             (R_GWCA_BASE + R_GWCA_GWIDC5_OFFSET)
#define R_GWCA_GWIDC6                             (R_GWCA_BASE + R_GWCA_GWIDC6_OFFSET)
#define R_GWCA_GWIDC7                             (R_GWCA_BASE + R_GWCA_GWIDC7_OFFSET)
#define R_GWCA_GWIDC8                             (R_GWCA_BASE + R_GWCA_GWIDC8_OFFSET)
#define R_GWCA_GWIDC9                             (R_GWCA_BASE + R_GWCA_GWIDC9_OFFSET)
#define R_GWCA_GWIDC10                            (R_GWCA_BASE + R_GWCA_GWIDC10_OFFSET)
#define R_GWCA_GWIDC11                            (R_GWCA_BASE + R_GWCA_GWIDC11_OFFSET)
#define R_GWCA_GWIDC12                            (R_GWCA_BASE + R_GWCA_GWIDC12_OFFSET)
#define R_GWCA_GWIDC13                            (R_GWCA_BASE + R_GWCA_GWIDC13_OFFSET)
#define R_GWCA_GWIDC14                            (R_GWCA_BASE + R_GWCA_GWIDC14_OFFSET)
#define R_GWCA_GWIDC15                            (R_GWCA_BASE + R_GWCA_GWIDC15_OFFSET)
#define R_GWCA_GWIDC16                            (R_GWCA_BASE + R_GWCA_GWIDC16_OFFSET)
#define R_GWCA_GWIDC17                            (R_GWCA_BASE + R_GWCA_GWIDC17_OFFSET)
#define R_GWCA_GWIDC18                            (R_GWCA_BASE + R_GWCA_GWIDC18_OFFSET)
#define R_GWCA_GWIDC19                            (R_GWCA_BASE + R_GWCA_GWIDC19_OFFSET)
#define R_GWCA_GWIDC20                            (R_GWCA_BASE + R_GWCA_GWIDC20_OFFSET)
#define R_GWCA_GWIDC21                            (R_GWCA_BASE + R_GWCA_GWIDC21_OFFSET)
#define R_GWCA_GWIDC22                            (R_GWCA_BASE + R_GWCA_GWIDC22_OFFSET)
#define R_GWCA_GWIDC23                            (R_GWCA_BASE + R_GWCA_GWIDC23_OFFSET)
#define R_GWCA_GWIDC24                            (R_GWCA_BASE + R_GWCA_GWIDC24_OFFSET)
#define R_GWCA_GWIDC25                            (R_GWCA_BASE + R_GWCA_GWIDC25_OFFSET)
#define R_GWCA_GWIDC26                            (R_GWCA_BASE + R_GWCA_GWIDC26_OFFSET)
#define R_GWCA_GWIDC27                            (R_GWCA_BASE + R_GWCA_GWIDC27_OFFSET)
#define R_GWCA_GWIDC28                            (R_GWCA_BASE + R_GWCA_GWIDC28_OFFSET)
#define R_GWCA_GWIDC29                            (R_GWCA_BASE + R_GWCA_GWIDC29_OFFSET)
#define R_GWCA_GWIDC30                            (R_GWCA_BASE + R_GWCA_GWIDC30_OFFSET)
#define R_GWCA_GWIDC31                            (R_GWCA_BASE + R_GWCA_GWIDC31_OFFSET)
#define R_GWCA_GWIDC32                            (R_GWCA_BASE + R_GWCA_GWIDC32_OFFSET)
#define R_GWCA_GWIDC33                            (R_GWCA_BASE + R_GWCA_GWIDC33_OFFSET)
#define R_GWCA_GWIDC34                            (R_GWCA_BASE + R_GWCA_GWIDC34_OFFSET)
#define R_GWCA_GWIDC35                            (R_GWCA_BASE + R_GWCA_GWIDC35_OFFSET)
#define R_GWCA_GWIDC36                            (R_GWCA_BASE + R_GWCA_GWIDC36_OFFSET)
#define R_GWCA_GWIDC37                            (R_GWCA_BASE + R_GWCA_GWIDC37_OFFSET)
#define R_GWCA_GWIDC38                            (R_GWCA_BASE + R_GWCA_GWIDC38_OFFSET)
#define R_GWCA_GWIDC39                            (R_GWCA_BASE + R_GWCA_GWIDC39_OFFSET)
#define R_GWCA_GWIDC40                            (R_GWCA_BASE + R_GWCA_GWIDC40_OFFSET)
#define R_GWCA_GWIDC41                            (R_GWCA_BASE + R_GWCA_GWIDC41_OFFSET)
#define R_GWCA_GWIDC42                            (R_GWCA_BASE + R_GWCA_GWIDC42_OFFSET)
#define R_GWCA_GWIDC43                            (R_GWCA_BASE + R_GWCA_GWIDC43_OFFSET)
#define R_GWCA_GWIDC44                            (R_GWCA_BASE + R_GWCA_GWIDC44_OFFSET)
#define R_GWCA_GWIDC45                            (R_GWCA_BASE + R_GWCA_GWIDC45_OFFSET)
#define R_GWCA_GWIDC46                            (R_GWCA_BASE + R_GWCA_GWIDC46_OFFSET)
#define R_GWCA_GWIDC47                            (R_GWCA_BASE + R_GWCA_GWIDC47_OFFSET)
#define R_GWCA_GWIDC48                            (R_GWCA_BASE + R_GWCA_GWIDC48_OFFSET)
#define R_GWCA_GWIDC49                            (R_GWCA_BASE + R_GWCA_GWIDC49_OFFSET)
#define R_GWCA_GWIDC50                            (R_GWCA_BASE + R_GWCA_GWIDC50_OFFSET)
#define R_GWCA_GWIDC51                            (R_GWCA_BASE + R_GWCA_GWIDC51_OFFSET)
#define R_GWCA_GWIDC52                            (R_GWCA_BASE + R_GWCA_GWIDC52_OFFSET)
#define R_GWCA_GWIDC53                            (R_GWCA_BASE + R_GWCA_GWIDC53_OFFSET)
#define R_GWCA_GWIDC54                            (R_GWCA_BASE + R_GWCA_GWIDC54_OFFSET)
#define R_GWCA_GWIDC55                            (R_GWCA_BASE + R_GWCA_GWIDC55_OFFSET)
#define R_GWCA_GWIDC56                            (R_GWCA_BASE + R_GWCA_GWIDC56_OFFSET)
#define R_GWCA_GWIDC57                            (R_GWCA_BASE + R_GWCA_GWIDC57_OFFSET)
#define R_GWCA_GWIDC58                            (R_GWCA_BASE + R_GWCA_GWIDC58_OFFSET)
#define R_GWCA_GWIDC59                            (R_GWCA_BASE + R_GWCA_GWIDC59_OFFSET)
#define R_GWCA_GWIDC60                            (R_GWCA_BASE + R_GWCA_GWIDC60_OFFSET)
#define R_GWCA_GWIDC61                            (R_GWCA_BASE + R_GWCA_GWIDC61_OFFSET)
#define R_GWCA_GWIDC62                            (R_GWCA_BASE + R_GWCA_GWIDC62_OFFSET)
#define R_GWCA_GWIDC63                            (R_GWCA_BASE + R_GWCA_GWIDC63_OFFSET)
#define R_GWCA_GWIDC64                            (R_GWCA_BASE + R_GWCA_GWIDC64_OFFSET)
#define R_GWCA_GWRDCN                             (R_GWCA_BASE + R_GWCA_GWRDCN_OFFSET)
#define R_GWCA_GWTDCN                             (R_GWCA_BASE + R_GWCA_GWTDCN_OFFSET)
#define R_GWCA_GWTSCN                             (R_GWCA_BASE + R_GWCA_GWTSCN_OFFSET)
#define R_GWCA_GWTSOVFECN                         (R_GWCA_BASE + R_GWCA_GWTSOVFECN_OFFSET)
#define R_GWCA_GWUSMFSECN                         (R_GWCA_BASE + R_GWCA_GWUSMFSECN_OFFSET)
#define R_GWCA_GWTFECN                            (R_GWCA_BASE + R_GWCA_GWTFECN_OFFSET)
#define R_GWCA_GWSEQECN                           (R_GWCA_BASE + R_GWCA_GWSEQECN_OFFSET)
#define R_GWCA_GWTXDNECN                          (R_GWCA_BASE + R_GWCA_GWTXDNECN_OFFSET)
#define R_GWCA_GWFSECN                            (R_GWCA_BASE + R_GWCA_GWFSECN_OFFSET)
#define R_GWCA_GWTDFECN                           (R_GWCA_BASE + R_GWCA_GWTDFECN_OFFSET)
#define R_GWCA_GWTSDNECN                          (R_GWCA_BASE + R_GWCA_GWTSDNECN_OFFSET)
#define R_GWCA_GWDQOECN                           (R_GWCA_BASE + R_GWCA_GWDQOECN_OFFSET)
#define R_GWCA_GWDQSECN                           (R_GWCA_BASE + R_GWCA_GWDQSECN_OFFSET)
#define R_GWCA_GWDFECN                            (R_GWCA_BASE + R_GWCA_GWDFECN_OFFSET)
#define R_GWCA_GWDSECN                            (R_GWCA_BASE + R_GWCA_GWDSECN_OFFSET)
#define R_GWCA_GWDSZECN                           (R_GWCA_BASE + R_GWCA_GWDSZECN_OFFSET)
#define R_GWCA_GWDCTECN                           (R_GWCA_BASE + R_GWCA_GWDCTECN_OFFSET)
#define R_GWCA_GWRXDNECN                          (R_GWCA_BASE + R_GWCA_GWRXDNECN_OFFSET)
#define R_GWCA_GWDIS0                             (R_GWCA_BASE + R_GWCA_GWDIS0_OFFSET)
#define R_GWCA_GWDIE0                             (R_GWCA_BASE + R_GWCA_GWDIE0_OFFSET)
#define R_GWCA_GWDID0                             (R_GWCA_BASE + R_GWCA_GWDID0_OFFSET)
#define R_GWCA_GWDIDS0                            (R_GWCA_BASE + R_GWCA_GWDIDS0_OFFSET)
#define R_GWCA_GWDIS1                             (R_GWCA_BASE + R_GWCA_GWDIS1_OFFSET)
#define R_GWCA_GWDIE1                             (R_GWCA_BASE + R_GWCA_GWDIE1_OFFSET)
#define R_GWCA_GWDID1                             (R_GWCA_BASE + R_GWCA_GWDID1_OFFSET)
#define R_GWCA_GWDIDS1                            (R_GWCA_BASE + R_GWCA_GWDIDS1_OFFSET)
#define R_GWCA_GWTSDIS                            (R_GWCA_BASE + R_GWCA_GWTSDIS_OFFSET)
#define R_GWCA_GWTSDIE                            (R_GWCA_BASE + R_GWCA_GWTSDIE_OFFSET)
#define R_GWCA_GWTSDID                            (R_GWCA_BASE + R_GWCA_GWTSDID_OFFSET)
#define R_GWCA_GWEIS0                             (R_GWCA_BASE + R_GWCA_GWEIS0_OFFSET)
#define R_GWCA_GWEIE0                             (R_GWCA_BASE + R_GWCA_GWEIE0_OFFSET)
#define R_GWCA_GWEID0                             (R_GWCA_BASE + R_GWCA_GWEID0_OFFSET)
#define R_GWCA_GWEIS1                             (R_GWCA_BASE + R_GWCA_GWEIS1_OFFSET)
#define R_GWCA_GWEIE1                             (R_GWCA_BASE + R_GWCA_GWEIE1_OFFSET)
#define R_GWCA_GWEID1                             (R_GWCA_BASE + R_GWCA_GWEID1_OFFSET)
#define R_GWCA_GWEIS20                            (R_GWCA_BASE + R_GWCA_GWEIS20_OFFSET)
#define R_GWCA_GWEIE20                            (R_GWCA_BASE + R_GWCA_GWEIE20_OFFSET)
#define R_GWCA_GWEID20                            (R_GWCA_BASE + R_GWCA_GWEID20_OFFSET)
#define R_GWCA_GWEIS21                            (R_GWCA_BASE + R_GWCA_GWEIS21_OFFSET)
#define R_GWCA_GWEIE21                            (R_GWCA_BASE + R_GWCA_GWEIE21_OFFSET)
#define R_GWCA_GWEID21                            (R_GWCA_BASE + R_GWCA_GWEID21_OFFSET)
#define R_GWCA_GWEIS3                             (R_GWCA_BASE + R_GWCA_GWEIS3_OFFSET)
#define R_GWCA_GWEIE3                             (R_GWCA_BASE + R_GWCA_GWEIE3_OFFSET)
#define R_GWCA_GWEID3                             (R_GWCA_BASE + R_GWCA_GWEID3_OFFSET)
#define R_GWCA_GWEIS4                             (R_GWCA_BASE + R_GWCA_GWEIS4_OFFSET)
#define R_GWCA_GWEIE4                             (R_GWCA_BASE + R_GWCA_GWEIE4_OFFSET)
#define R_GWCA_GWEID4                             (R_GWCA_BASE + R_GWCA_GWEID4_OFFSET)
#define R_GWCA_GWEIS5                             (R_GWCA_BASE + R_GWCA_GWEIS5_OFFSET)
#define R_GWCA_GWEIE5                             (R_GWCA_BASE + R_GWCA_GWEIE5_OFFSET)
#define R_GWCA_GWEID5                             (R_GWCA_BASE + R_GWCA_GWEID5_OFFSET)

/* Register bit definitions */
/* GWMC Register bit definitions */
#define R_GWCA_GWMC_OPC_SHIFT                     (0)  /*  */
#define R_GWCA_GWMC_OPC_MASK                      0x3

/* GWMS Register bit definitions */
#define R_GWCA_GWMS_OPS_SHIFT                     (0)  /*  */
#define R_GWCA_GWMS_OPS_MASK                      0x3

/* GWIRC Register bit definitions */
#define R_GWCA_GWIRC_IPVR0_SHIFT                  (0)  /*  */
#define R_GWCA_GWIRC_IPVR0_MASK                   0x7

#define R_GWCA_GWIRC_IPVR1_SHIFT                  (4)  /*  */
#define R_GWCA_GWIRC_IPVR1_MASK                   0x70

#define R_GWCA_GWIRC_IPVR2_SHIFT                  (8)  /*  */
#define R_GWCA_GWIRC_IPVR2_MASK                   0x700

#define R_GWCA_GWIRC_IPVR3_SHIFT                  (12)  /*  */
#define R_GWCA_GWIRC_IPVR3_MASK                   0x7000

#define R_GWCA_GWIRC_IPVR4_SHIFT                  (16)  /*  */
#define R_GWCA_GWIRC_IPVR4_MASK                   0x70000

#define R_GWCA_GWIRC_IPVR5_SHIFT                  (20)  /*  */
#define R_GWCA_GWIRC_IPVR5_MASK                   0x700000

#define R_GWCA_GWIRC_IPVR6_SHIFT                  (24)  /*  */
#define R_GWCA_GWIRC_IPVR6_MASK                   0x7000000

#define R_GWCA_GWIRC_IPVR7_SHIFT                  (28)  /*  */
#define R_GWCA_GWIRC_IPVR7_MASK                   0x70000000

/* GWRDQSC Register bit definitions */
#define R_GWCA_GWRDQSC_RDQSL0                     (1 << 0)  /*  */

#define R_GWCA_GWRDQSC_RDQSL1                     (1 << 1)  /*  */

#define R_GWCA_GWRDQSC_RDQSL2                     (1 << 2)  /*  */

#define R_GWCA_GWRDQSC_RDQSL3                     (1 << 3)  /*  */

#define R_GWCA_GWRDQSC_RDQSL4                     (1 << 4)  /*  */

#define R_GWCA_GWRDQSC_RDQSL5                     (1 << 5)  /*  */

#define R_GWCA_GWRDQSC_RDQSL6                     (1 << 6)  /*  */

#define R_GWCA_GWRDQSC_RDQSL7                     (1 << 7)  /*  */

/* GWRDQC Register bit definitions */
#define R_GWCA_GWRDQC_RDQD0                       (1 << 0)  /*  */

#define R_GWCA_GWRDQC_RDQD1                       (1 << 1)  /*  */

#define R_GWCA_GWRDQC_RDQD2                       (1 << 2)  /*  */

#define R_GWCA_GWRDQC_RDQD3                       (1 << 3)  /*  */

#define R_GWCA_GWRDQC_RDQD4                       (1 << 4)  /*  */

#define R_GWCA_GWRDQC_RDQD5                       (1 << 5)  /*  */

#define R_GWCA_GWRDQC_RDQD6                       (1 << 6)  /*  */

#define R_GWCA_GWRDQC_RDQD7                       (1 << 7)  /*  */

#define R_GWCA_GWRDQC_RDQP0                       (1 << 16)  /*  */

#define R_GWCA_GWRDQC_RDQP1                       (1 << 17)  /*  */

#define R_GWCA_GWRDQC_RDQP2                       (1 << 18)  /*  */

#define R_GWCA_GWRDQC_RDQP3                       (1 << 19)  /*  */

#define R_GWCA_GWRDQC_RDQP4                       (1 << 20)  /*  */

#define R_GWCA_GWRDQC_RDQP5                       (1 << 21)  /*  */

#define R_GWCA_GWRDQC_RDQP6                       (1 << 22)  /*  */

#define R_GWCA_GWRDQC_RDQP7                       (1 << 23)  /*  */

/* GWRDQAC Register bit definitions */
#define R_GWCA_GWRDQAC_RDQA0_SHIFT                (0)  /*  */
#define R_GWCA_GWRDQAC_RDQA0_MASK                 0xf

#define R_GWCA_GWRDQAC_RDQA1_SHIFT                (4)  /*  */
#define R_GWCA_GWRDQAC_RDQA1_MASK                 0xf0

#define R_GWCA_GWRDQAC_RDQA2_SHIFT                (8)  /*  */
#define R_GWCA_GWRDQAC_RDQA2_MASK                 0xf00

#define R_GWCA_GWRDQAC_RDQA3_SHIFT                (12)  /*  */
#define R_GWCA_GWRDQAC_RDQA3_MASK                 0xf000

#define R_GWCA_GWRDQAC_RDQA4_SHIFT                (16)  /*  */
#define R_GWCA_GWRDQAC_RDQA4_MASK                 0xf0000

#define R_GWCA_GWRDQAC_RDQA5_SHIFT                (20)  /*  */
#define R_GWCA_GWRDQAC_RDQA5_MASK                 0xf00000

#define R_GWCA_GWRDQAC_RDQA6_SHIFT                (24)  /*  */
#define R_GWCA_GWRDQAC_RDQA6_MASK                 0xf000000

#define R_GWCA_GWRDQAC_RDQA7_SHIFT                (28)  /*  */
#define R_GWCA_GWRDQAC_RDQA7_MASK                 0xf0000000

/* GWRGC Register bit definitions */
#define R_GWCA_GWRGC_RCPT                         (1 << 0)  /*  */

/* GWRMFSC0 Register bit definitions */
#define R_GWCA_GWRMFSC0_MFS_SHIFT                 (0)  /*  */
#define R_GWCA_GWRMFSC0_MFS_MASK                  0xffff

/* GWRMFSC1 Register bit definitions */
#define R_GWCA_GWRMFSC1_MFS_SHIFT                 (0)  /*  */
#define R_GWCA_GWRMFSC1_MFS_MASK                  0xffff

/* GWRMFSC2 Register bit definitions */
#define R_GWCA_GWRMFSC2_MFS_SHIFT                 (0)  /*  */
#define R_GWCA_GWRMFSC2_MFS_MASK                  0xffff

/* GWRMFSC3 Register bit definitions */
#define R_GWCA_GWRMFSC3_MFS_SHIFT                 (0)  /*  */
#define R_GWCA_GWRMFSC3_MFS_MASK                  0xffff

/* GWRMFSC4 Register bit definitions */
#define R_GWCA_GWRMFSC4_MFS_SHIFT                 (0)  /*  */
#define R_GWCA_GWRMFSC4_MFS_MASK                  0xffff

/* GWRMFSC5 Register bit definitions */
#define R_GWCA_GWRMFSC5_MFS_SHIFT                 (0)  /*  */
#define R_GWCA_GWRMFSC5_MFS_MASK                  0xffff

/* GWRMFSC6 Register bit definitions */
#define R_GWCA_GWRMFSC6_MFS_SHIFT                 (0)  /*  */
#define R_GWCA_GWRMFSC6_MFS_MASK                  0xffff

/* GWRMFSC7 Register bit definitions */
#define R_GWCA_GWRMFSC7_MFS_SHIFT                 (0)  /*  */
#define R_GWCA_GWRMFSC7_MFS_MASK                  0xffff

/* GWRDQDC0 Register bit definitions */
#define R_GWCA_GWRDQDC0_DQD_SHIFT                 (0)  /*  */
#define R_GWCA_GWRDQDC0_DQD_MASK                  0x7ff

/* GWRDQDC1 Register bit definitions */
#define R_GWCA_GWRDQDC1_DQD_SHIFT                 (0)  /*  */
#define R_GWCA_GWRDQDC1_DQD_MASK                  0x7ff

/* GWRDQDC2 Register bit definitions */
#define R_GWCA_GWRDQDC2_DQD_SHIFT                 (0)  /*  */
#define R_GWCA_GWRDQDC2_DQD_MASK                  0x7ff

/* GWRDQDC3 Register bit definitions */
#define R_GWCA_GWRDQDC3_DQD_SHIFT                 (0)  /*  */
#define R_GWCA_GWRDQDC3_DQD_MASK                  0x7ff

/* GWRDQDC4 Register bit definitions */
#define R_GWCA_GWRDQDC4_DQD_SHIFT                 (0)  /*  */
#define R_GWCA_GWRDQDC4_DQD_MASK                  0x7ff

/* GWRDQDC5 Register bit definitions */
#define R_GWCA_GWRDQDC5_DQD_SHIFT                 (0)  /*  */
#define R_GWCA_GWRDQDC5_DQD_MASK                  0x7ff

/* GWRDQDC6 Register bit definitions */
#define R_GWCA_GWRDQDC6_DQD_SHIFT                 (0)  /*  */
#define R_GWCA_GWRDQDC6_DQD_MASK                  0x7ff

/* GWRDQDC7 Register bit definitions */
#define R_GWCA_GWRDQDC7_DQD_SHIFT                 (0)  /*  */
#define R_GWCA_GWRDQDC7_DQD_MASK                  0x7ff

/* GWRDQM0 Register bit definitions */
#define R_GWCA_GWRDQM0_DNQ_SHIFT                  (0)  /*  */
#define R_GWCA_GWRDQM0_DNQ_MASK                   0x7ff

/* GWRDQM1 Register bit definitions */
#define R_GWCA_GWRDQM1_DNQ_SHIFT                  (0)  /*  */
#define R_GWCA_GWRDQM1_DNQ_MASK                   0x7ff

/* GWRDQM2 Register bit definitions */
#define R_GWCA_GWRDQM2_DNQ_SHIFT                  (0)  /*  */
#define R_GWCA_GWRDQM2_DNQ_MASK                   0x7ff

/* GWRDQM3 Register bit definitions */
#define R_GWCA_GWRDQM3_DNQ_SHIFT                  (0)  /*  */
#define R_GWCA_GWRDQM3_DNQ_MASK                   0x7ff

/* GWRDQM4 Register bit definitions */
#define R_GWCA_GWRDQM4_DNQ_SHIFT                  (0)  /*  */
#define R_GWCA_GWRDQM4_DNQ_MASK                   0x7ff

/* GWRDQM5 Register bit definitions */
#define R_GWCA_GWRDQM5_DNQ_SHIFT                  (0)  /*  */
#define R_GWCA_GWRDQM5_DNQ_MASK                   0x7ff

/* GWRDQM6 Register bit definitions */
#define R_GWCA_GWRDQM6_DNQ_SHIFT                  (0)  /*  */
#define R_GWCA_GWRDQM6_DNQ_MASK                   0x7ff

/* GWRDQM7 Register bit definitions */
#define R_GWCA_GWRDQM7_DNQ_SHIFT                  (0)  /*  */
#define R_GWCA_GWRDQM7_DNQ_MASK                   0x7ff

/* GWRDQMLM0 Register bit definitions */
#define R_GWCA_GWRDQMLM0_DMLQ_SHIFT               (0)  /*  */
#define R_GWCA_GWRDQMLM0_DMLQ_MASK                0x7ff

/* GWRDQMLM1 Register bit definitions */
#define R_GWCA_GWRDQMLM1_DMLQ_SHIFT               (0)  /*  */
#define R_GWCA_GWRDQMLM1_DMLQ_MASK                0x7ff

/* GWRDQMLM2 Register bit definitions */
#define R_GWCA_GWRDQMLM2_DMLQ_SHIFT               (0)  /*  */
#define R_GWCA_GWRDQMLM2_DMLQ_MASK                0x7ff

/* GWRDQMLM3 Register bit definitions */
#define R_GWCA_GWRDQMLM3_DMLQ_SHIFT               (0)  /*  */
#define R_GWCA_GWRDQMLM3_DMLQ_MASK                0x7ff

/* GWRDQMLM4 Register bit definitions */
#define R_GWCA_GWRDQMLM4_DMLQ_SHIFT               (0)  /*  */
#define R_GWCA_GWRDQMLM4_DMLQ_MASK                0x7ff

/* GWRDQMLM5 Register bit definitions */
#define R_GWCA_GWRDQMLM5_DMLQ_SHIFT               (0)  /*  */
#define R_GWCA_GWRDQMLM5_DMLQ_MASK                0x7ff

/* GWRDQMLM6 Register bit definitions */
#define R_GWCA_GWRDQMLM6_DMLQ_SHIFT               (0)  /*  */
#define R_GWCA_GWRDQMLM6_DMLQ_MASK                0x7ff

/* GWRDQMLM7 Register bit definitions */
#define R_GWCA_GWRDQMLM7_DMLQ_SHIFT               (0)  /*  */
#define R_GWCA_GWRDQMLM7_DMLQ_MASK                0x7ff

/* GWMTIRM Register bit definitions */
#define R_GWCA_GWMTIRM_MTIOG                      (1 << 0)  /*  */

#define R_GWCA_GWMTIRM_MTR                        (1 << 1)  /*  */

/* GWMSTLS Register bit definitions */
#define R_GWCA_GWMSTLS_MNRCNL_SHIFT               (0)  /*  */
#define R_GWCA_GWMSTLS_MNRCNL_MASK                0x7f

#define R_GWCA_GWMSTLS_MNL_SHIFT                  (8)  /*  */
#define R_GWCA_GWMSTLS_MNL_MASK                   0x700

#define R_GWCA_GWMSTLS_MSENL_SHIFT                (16)  /*  */
#define R_GWCA_GWMSTLS_MSENL_MASK                 0x7f0000

/* GWMSTLR Register bit definitions */
#define R_GWCA_GWMSTLR_MTLF                       (1 << 0)  /*  */

#define R_GWCA_GWMSTLR_MTL                        (1 << 31)  /*  */

/* GWMSTSS Register bit definitions */
#define R_GWCA_GWMSTSS_MSENS_SHIFT                (0)  /*  */
#define R_GWCA_GWMSTSS_MSENS_MASK                 0x7f

/* GWMSTSR Register bit definitions */
#define R_GWCA_GWMSTSR_MNRCNR_SHIFT               (0)  /*  */
#define R_GWCA_GWMSTSR_MNRCNR_MASK                0x7f

#define R_GWCA_GWMSTSR_MNR_SHIFT                  (8)  /*  */
#define R_GWCA_GWMSTSR_MNR_MASK                   0x700

#define R_GWCA_GWMSTSR_MTSEF                      (1 << 16)  /*  */

#define R_GWCA_GWMSTSR_MTS                        (1 << 31)  /*  */

/* GWMAC0 Register bit definitions */
#define R_GWCA_GWMAC0_MAUP_SHIFT                  (0)  /*  */
#define R_GWCA_GWMAC0_MAUP_MASK                   0xffff

/* GWMAC1 Register bit definitions */
#define R_GWCA_GWMAC1_MADP_SHIFT                  (0)  /*  */
#define R_GWCA_GWMAC1_MADP_MASK                   0xffffffff

/* GWVCC Register bit definitions */
#define R_GWCA_GWVCC_VIM                          (1 << 0)  /*  */

#define R_GWCA_GWVCC_CTVUM                        (1 << 8)  /*  */

#define R_GWCA_GWVCC_VEM_SHIFT                    (16)  /*  */
#define R_GWCA_GWVCC_VEM_MASK                     0x70000

/* GWVTC Register bit definitions */
#define R_GWCA_GWVTC_CTV_SHIFT                    (0)  /*  */
#define R_GWCA_GWVTC_CTV_MASK                     0xfff

#define R_GWCA_GWVTC_CTP_SHIFT                    (12)  /*  */
#define R_GWCA_GWVTC_CTP_MASK                     0x7000

#define R_GWCA_GWVTC_CTD                          (1 << 15)  /*  */

#define R_GWCA_GWVTC_STV_SHIFT                    (16)  /*  */
#define R_GWCA_GWVTC_STV_MASK                     0xfff0000

#define R_GWCA_GWVTC_STP_SHIFT                    (28)  /*  */
#define R_GWCA_GWVTC_STP_MASK                     0x70000000

#define R_GWCA_GWVTC_STD                          (1 << 31)  /*  */

/* GWTTFC Register bit definitions */
#define R_GWCA_GWTTFC_NT                          (1 << 0)  /*  */

#define R_GWCA_GWTTFC_RT                          (1 << 1)  /*  */

#define R_GWCA_GWTTFC_CST                         (1 << 2)  /*  */

#define R_GWCA_GWTTFC_CSRT                        (1 << 3)  /*  */

#define R_GWCA_GWTTFC_CT                          (1 << 4)  /*  */

#define R_GWCA_GWTTFC_CRT                         (1 << 5)  /*  */

#define R_GWCA_GWTTFC_SCT                         (1 << 6)  /*  */

#define R_GWCA_GWTTFC_SCRT                        (1 << 7)  /*  */

#define R_GWCA_GWTTFC_UT                          (1 << 8)  /*  */

/* GWTDCAC00 Register bit definitions */
#define R_GWCA_GWTDCAC00_TSCCAUP_SHIFT            (0)  /*  */
#define R_GWCA_GWTDCAC00_TSCCAUP_MASK             0xff

/* GWTDCAC10 Register bit definitions */
#define R_GWCA_GWTDCAC10_TSCCADP_SHIFT            (0)  /*  */
#define R_GWCA_GWTDCAC10_TSCCADP_MASK             0xffffffff

/* GWTDCAC01 Register bit definitions */
#define R_GWCA_GWTDCAC01_TSCCAUP_SHIFT            (0)  /*  */
#define R_GWCA_GWTDCAC01_TSCCAUP_MASK             0xff

/* GWTDCAC11 Register bit definitions */
#define R_GWCA_GWTDCAC11_TSCCADP_SHIFT            (0)  /*  */
#define R_GWCA_GWTDCAC11_TSCCADP_MASK             0xffffffff

/* GWTSDCC0 Register bit definitions */
#define R_GWCA_GWTSDCC0_TE                        (1 << 0)  /*  */

#define R_GWCA_GWTSDCC0_DCS_SHIFT                 (1)  /*  */
#define R_GWCA_GWTSDCC0_DCS_MASK                  0x6

#define R_GWCA_GWTSDCC0_OSID_SHIFT                (8)  /*  */
#define R_GWCA_GWTSDCC0_OSID_MASK                 0x700

/* GWTSDCC1 Register bit definitions */
#define R_GWCA_GWTSDCC1_TE                        (1 << 0)  /*  */

#define R_GWCA_GWTSDCC1_DCS_SHIFT                 (1)  /*  */
#define R_GWCA_GWTSDCC1_DCS_MASK                  0x6

#define R_GWCA_GWTSDCC1_OSID_SHIFT                (8)  /*  */
#define R_GWCA_GWTSDCC1_OSID_MASK                 0x700

/* GWTSNM Register bit definitions */
#define R_GWCA_GWTSNM_TNTR_SHIFT                  (0)  /*  */
#define R_GWCA_GWTSNM_TNTR_MASK                   0xff

/* GWTSMNM Register bit definitions */
#define R_GWCA_GWTSMNM_TMNTR_SHIFT                (0)  /*  */
#define R_GWCA_GWTSMNM_TMNTR_MASK                 0xff

/* GWAC Register bit definitions */
#define R_GWCA_GWAC_AMPR                          (1 << 0)  /*  */

#define R_GWCA_GWAC_AMP                           (1 << 1)  /*  */

/* GWDCBAC0 Register bit definitions */
#define R_GWCA_GWDCBAC0_DCBAUP_SHIFT              (0)  /*  */
#define R_GWCA_GWDCBAC0_DCBAUP_MASK               0xff

/* GWDCBAC1 Register bit definitions */
#define R_GWCA_GWDCBAC1_DCBADP_SHIFT              (0)  /*  */
#define R_GWCA_GWDCBAC1_DCBADP_MASK               0xffffffff

/* GWMDNC Register bit definitions */
#define R_GWCA_GWMDNC_RXDMN_SHIFT                 (0)  /*  */
#define R_GWCA_GWMDNC_RXDMN_MASK                  0x1f

#define R_GWCA_GWMDNC_TXDMN_SHIFT                 (8)  /*  */
#define R_GWCA_GWMDNC_TXDMN_MASK                  0x1f00

#define R_GWCA_GWMDNC_TSDMN_SHIFT                 (16)  /*  */
#define R_GWCA_GWMDNC_TSDMN_MASK                  0x30000

/* GWTPC0 Register bit definitions */
#define R_GWCA_GWTPC0_PPPL0                       (1 << 0)  /*  */

#define R_GWCA_GWTPC0_PPPL1                       (1 << 1)  /*  */

#define R_GWCA_GWTPC0_PPPL2                       (1 << 2)  /*  */

#define R_GWCA_GWTPC0_PPPL3                       (1 << 3)  /*  */

#define R_GWCA_GWTPC0_PPPL4                       (1 << 4)  /*  */

#define R_GWCA_GWTPC0_PPPL5                       (1 << 5)  /*  */

#define R_GWCA_GWTPC0_PPPL6                       (1 << 6)  /*  */

#define R_GWCA_GWTPC0_PPPL7                       (1 << 7)  /*  */

#define R_GWCA_GWTPC0_PPPL8                       (1 << 8)  /*  */

/* GWTPC1 Register bit definitions */
#define R_GWCA_GWTPC1_PPPL0                       (1 << 0)  /*  */

#define R_GWCA_GWTPC1_PPPL1                       (1 << 1)  /*  */

#define R_GWCA_GWTPC1_PPPL2                       (1 << 2)  /*  */

#define R_GWCA_GWTPC1_PPPL3                       (1 << 3)  /*  */

#define R_GWCA_GWTPC1_PPPL4                       (1 << 4)  /*  */

#define R_GWCA_GWTPC1_PPPL5                       (1 << 5)  /*  */

#define R_GWCA_GWTPC1_PPPL6                       (1 << 6)  /*  */

#define R_GWCA_GWTPC1_PPPL7                       (1 << 7)  /*  */

#define R_GWCA_GWTPC1_PPPL8                       (1 << 8)  /*  */

/* GWARIRM Register bit definitions */
#define R_GWCA_GWARIRM_ARIOG                      (1 << 0)  /*  */

#define R_GWCA_GWARIRM_ARR                        (1 << 1)  /*  */

/* GWDCC0 Register bit definitions */
#define R_GWCA_GWDCC0_SM_SHIFT                    (0)  /*  */
#define R_GWCA_GWDCC0_SM_MASK                     0x3

#define R_GWCA_GWDCC0_EDE                         (1 << 8)  /*  */

#define R_GWCA_GWDCC0_ETS                         (1 << 9)  /*  */

#define R_GWCA_GWDCC0_SL                          (1 << 10)  /*  */

#define R_GWCA_GWDCC0_DQT                         (1 << 11)  /*  */

#define R_GWCA_GWDCC0_DCP_SHIFT                   (16)  /*  */
#define R_GWCA_GWDCC0_DCP_MASK                    0x70000

#define R_GWCA_GWDCC0_BALR                        (1 << 24)  /*  */

#define R_GWCA_GWDCC0_OSID_SHIFT                  (28)  /*  */
#define R_GWCA_GWDCC0_OSID_MASK                   0x70000000

/* GWDCC1 Register bit definitions */
#define R_GWCA_GWDCC1_SM_SHIFT                    (0)  /*  */
#define R_GWCA_GWDCC1_SM_MASK                     0x3

#define R_GWCA_GWDCC1_EDE                         (1 << 8)  /*  */

#define R_GWCA_GWDCC1_ETS                         (1 << 9)  /*  */

#define R_GWCA_GWDCC1_SL                          (1 << 10)  /*  */

#define R_GWCA_GWDCC1_DQT                         (1 << 11)  /*  */

#define R_GWCA_GWDCC1_DCP_SHIFT                   (16)  /*  */
#define R_GWCA_GWDCC1_DCP_MASK                    0x70000

#define R_GWCA_GWDCC1_BALR                        (1 << 24)  /*  */

#define R_GWCA_GWDCC1_OSID_SHIFT                  (28)  /*  */
#define R_GWCA_GWDCC1_OSID_MASK                   0x70000000

/* GWDCC2 Register bit definitions */
#define R_GWCA_GWDCC2_SM_SHIFT                    (0)  /*  */
#define R_GWCA_GWDCC2_SM_MASK                     0x3

#define R_GWCA_GWDCC2_EDE                         (1 << 8)  /*  */

#define R_GWCA_GWDCC2_ETS                         (1 << 9)  /*  */

#define R_GWCA_GWDCC2_SL                          (1 << 10)  /*  */

#define R_GWCA_GWDCC2_DQT                         (1 << 11)  /*  */

#define R_GWCA_GWDCC2_DCP_SHIFT                   (16)  /*  */
#define R_GWCA_GWDCC2_DCP_MASK                    0x70000

#define R_GWCA_GWDCC2_BALR                        (1 << 24)  /*  */

#define R_GWCA_GWDCC2_OSID_SHIFT                  (28)  /*  */
#define R_GWCA_GWDCC2_OSID_MASK                   0x70000000

/* GWDCC3 Register bit definitions */
#define R_GWCA_GWDCC3_SM_SHIFT                    (0)  /*  */
#define R_GWCA_GWDCC3_SM_MASK                     0x3

#define R_GWCA_GWDCC3_EDE                         (1 << 8)  /*  */

#define R_GWCA_GWDCC3_ETS                         (1 << 9)  /*  */

#define R_GWCA_GWDCC3_SL                          (1 << 10)  /*  */

#define R_GWCA_GWDCC3_DQT                         (1 << 11)  /*  */

#define R_GWCA_GWDCC3_DCP_SHIFT                   (16)  /*  */
#define R_GWCA_GWDCC3_DCP_MASK                    0x70000

#define R_GWCA_GWDCC3_BALR                        (1 << 24)  /*  */

#define R_GWCA_GWDCC3_OSID_SHIFT                  (28)  /*  */
#define R_GWCA_GWDCC3_OSID_MASK                   0x70000000

/* GWDCC4 Register bit definitions */
#define R_GWCA_GWDCC4_SM_SHIFT                    (0)  /*  */
#define R_GWCA_GWDCC4_SM_MASK                     0x3

#define R_GWCA_GWDCC4_EDE                         (1 << 8)  /*  */

#define R_GWCA_GWDCC4_ETS                         (1 << 9)  /*  */

#define R_GWCA_GWDCC4_SL                          (1 << 10)  /*  */

#define R_GWCA_GWDCC4_DQT                         (1 << 11)  /*  */

#define R_GWCA_GWDCC4_DCP_SHIFT                   (16)  /*  */
#define R_GWCA_GWDCC4_DCP_MASK                    0x70000

#define R_GWCA_GWDCC4_BALR                        (1 << 24)  /*  */

#define R_GWCA_GWDCC4_OSID_SHIFT                  (28)  /*  */
#define R_GWCA_GWDCC4_OSID_MASK                   0x70000000

/* GWDCC5 Register bit definitions */
#define R_GWCA_GWDCC5_SM_SHIFT                    (0)  /*  */
#define R_GWCA_GWDCC5_SM_MASK                     0x3

#define R_GWCA_GWDCC5_EDE                         (1 << 8)  /*  */

#define R_GWCA_GWDCC5_ETS                         (1 << 9)  /*  */

#define R_GWCA_GWDCC5_SL                          (1 << 10)  /*  */

#define R_GWCA_GWDCC5_DQT                         (1 << 11)  /*  */

#define R_GWCA_GWDCC5_DCP_SHIFT                   (16)  /*  */
#define R_GWCA_GWDCC5_DCP_MASK                    0x70000

#define R_GWCA_GWDCC5_BALR                        (1 << 24)  /*  */

#define R_GWCA_GWDCC5_OSID_SHIFT                  (28)  /*  */
#define R_GWCA_GWDCC5_OSID_MASK                   0x70000000

/* GWDCC6 Register bit definitions */
#define R_GWCA_GWDCC6_SM_SHIFT                    (0)  /*  */
#define R_GWCA_GWDCC6_SM_MASK                     0x3

#define R_GWCA_GWDCC6_EDE                         (1 << 8)  /*  */

#define R_GWCA_GWDCC6_ETS                         (1 << 9)  /*  */

#define R_GWCA_GWDCC6_SL                          (1 << 10)  /*  */

#define R_GWCA_GWDCC6_DQT                         (1 << 11)  /*  */

#define R_GWCA_GWDCC6_DCP_SHIFT                   (16)  /*  */
#define R_GWCA_GWDCC6_DCP_MASK                    0x70000

#define R_GWCA_GWDCC6_BALR                        (1 << 24)  /*  */

#define R_GWCA_GWDCC6_OSID_SHIFT                  (28)  /*  */
#define R_GWCA_GWDCC6_OSID_MASK                   0x70000000

/* GWDCC7 Register bit definitions */
#define R_GWCA_GWDCC7_SM_SHIFT                    (0)  /*  */
#define R_GWCA_GWDCC7_SM_MASK                     0x3

#define R_GWCA_GWDCC7_EDE                         (1 << 8)  /*  */

#define R_GWCA_GWDCC7_ETS                         (1 << 9)  /*  */

#define R_GWCA_GWDCC7_SL                          (1 << 10)  /*  */

#define R_GWCA_GWDCC7_DQT                         (1 << 11)  /*  */

#define R_GWCA_GWDCC7_DCP_SHIFT                   (16)  /*  */
#define R_GWCA_GWDCC7_DCP_MASK                    0x70000

#define R_GWCA_GWDCC7_BALR                        (1 << 24)  /*  */

#define R_GWCA_GWDCC7_OSID_SHIFT                  (28)  /*  */
#define R_GWCA_GWDCC7_OSID_MASK                   0x70000000

/* GWDCC8 Register bit definitions */
#define R_GWCA_GWDCC8_SM_SHIFT                    (0)  /*  */
#define R_GWCA_GWDCC8_SM_MASK                     0x3

#define R_GWCA_GWDCC8_EDE                         (1 << 8)  /*  */

#define R_GWCA_GWDCC8_ETS                         (1 << 9)  /*  */

#define R_GWCA_GWDCC8_SL                          (1 << 10)  /*  */

#define R_GWCA_GWDCC8_DQT                         (1 << 11)  /*  */

#define R_GWCA_GWDCC8_DCP_SHIFT                   (16)  /*  */
#define R_GWCA_GWDCC8_DCP_MASK                    0x70000

#define R_GWCA_GWDCC8_BALR                        (1 << 24)  /*  */

#define R_GWCA_GWDCC8_OSID_SHIFT                  (28)  /*  */
#define R_GWCA_GWDCC8_OSID_MASK                   0x70000000

/* GWDCC9 Register bit definitions */
#define R_GWCA_GWDCC9_SM_SHIFT                    (0)  /*  */
#define R_GWCA_GWDCC9_SM_MASK                     0x3

#define R_GWCA_GWDCC9_EDE                         (1 << 8)  /*  */

#define R_GWCA_GWDCC9_ETS                         (1 << 9)  /*  */

#define R_GWCA_GWDCC9_SL                          (1 << 10)  /*  */

#define R_GWCA_GWDCC9_DQT                         (1 << 11)  /*  */

#define R_GWCA_GWDCC9_DCP_SHIFT                   (16)  /*  */
#define R_GWCA_GWDCC9_DCP_MASK                    0x70000

#define R_GWCA_GWDCC9_BALR                        (1 << 24)  /*  */

#define R_GWCA_GWDCC9_OSID_SHIFT                  (28)  /*  */
#define R_GWCA_GWDCC9_OSID_MASK                   0x70000000

/* GWDCC10 Register bit definitions */
#define R_GWCA_GWDCC10_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC10_SM_MASK                    0x3

#define R_GWCA_GWDCC10_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC10_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC10_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC10_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC10_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC10_DCP_MASK                   0x70000

#define R_GWCA_GWDCC10_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC10_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC10_OSID_MASK                  0x70000000

/* GWDCC11 Register bit definitions */
#define R_GWCA_GWDCC11_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC11_SM_MASK                    0x3

#define R_GWCA_GWDCC11_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC11_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC11_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC11_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC11_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC11_DCP_MASK                   0x70000

#define R_GWCA_GWDCC11_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC11_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC11_OSID_MASK                  0x70000000

/* GWDCC12 Register bit definitions */
#define R_GWCA_GWDCC12_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC12_SM_MASK                    0x3

#define R_GWCA_GWDCC12_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC12_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC12_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC12_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC12_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC12_DCP_MASK                   0x70000

#define R_GWCA_GWDCC12_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC12_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC12_OSID_MASK                  0x70000000

/* GWDCC13 Register bit definitions */
#define R_GWCA_GWDCC13_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC13_SM_MASK                    0x3

#define R_GWCA_GWDCC13_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC13_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC13_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC13_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC13_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC13_DCP_MASK                   0x70000

#define R_GWCA_GWDCC13_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC13_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC13_OSID_MASK                  0x70000000

/* GWDCC14 Register bit definitions */
#define R_GWCA_GWDCC14_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC14_SM_MASK                    0x3

#define R_GWCA_GWDCC14_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC14_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC14_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC14_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC14_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC14_DCP_MASK                   0x70000

#define R_GWCA_GWDCC14_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC14_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC14_OSID_MASK                  0x70000000

/* GWDCC15 Register bit definitions */
#define R_GWCA_GWDCC15_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC15_SM_MASK                    0x3

#define R_GWCA_GWDCC15_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC15_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC15_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC15_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC15_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC15_DCP_MASK                   0x70000

#define R_GWCA_GWDCC15_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC15_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC15_OSID_MASK                  0x70000000

/* GWDCC16 Register bit definitions */
#define R_GWCA_GWDCC16_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC16_SM_MASK                    0x3

#define R_GWCA_GWDCC16_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC16_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC16_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC16_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC16_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC16_DCP_MASK                   0x70000

#define R_GWCA_GWDCC16_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC16_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC16_OSID_MASK                  0x70000000

/* GWDCC17 Register bit definitions */
#define R_GWCA_GWDCC17_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC17_SM_MASK                    0x3

#define R_GWCA_GWDCC17_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC17_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC17_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC17_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC17_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC17_DCP_MASK                   0x70000

#define R_GWCA_GWDCC17_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC17_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC17_OSID_MASK                  0x70000000

/* GWDCC18 Register bit definitions */
#define R_GWCA_GWDCC18_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC18_SM_MASK                    0x3

#define R_GWCA_GWDCC18_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC18_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC18_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC18_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC18_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC18_DCP_MASK                   0x70000

#define R_GWCA_GWDCC18_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC18_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC18_OSID_MASK                  0x70000000

/* GWDCC19 Register bit definitions */
#define R_GWCA_GWDCC19_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC19_SM_MASK                    0x3

#define R_GWCA_GWDCC19_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC19_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC19_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC19_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC19_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC19_DCP_MASK                   0x70000

#define R_GWCA_GWDCC19_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC19_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC19_OSID_MASK                  0x70000000

/* GWDCC20 Register bit definitions */
#define R_GWCA_GWDCC20_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC20_SM_MASK                    0x3

#define R_GWCA_GWDCC20_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC20_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC20_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC20_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC20_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC20_DCP_MASK                   0x70000

#define R_GWCA_GWDCC20_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC20_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC20_OSID_MASK                  0x70000000

/* GWDCC21 Register bit definitions */
#define R_GWCA_GWDCC21_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC21_SM_MASK                    0x3

#define R_GWCA_GWDCC21_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC21_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC21_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC21_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC21_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC21_DCP_MASK                   0x70000

#define R_GWCA_GWDCC21_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC21_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC21_OSID_MASK                  0x70000000

/* GWDCC22 Register bit definitions */
#define R_GWCA_GWDCC22_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC22_SM_MASK                    0x3

#define R_GWCA_GWDCC22_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC22_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC22_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC22_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC22_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC22_DCP_MASK                   0x70000

#define R_GWCA_GWDCC22_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC22_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC22_OSID_MASK                  0x70000000

/* GWDCC23 Register bit definitions */
#define R_GWCA_GWDCC23_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC23_SM_MASK                    0x3

#define R_GWCA_GWDCC23_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC23_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC23_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC23_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC23_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC23_DCP_MASK                   0x70000

#define R_GWCA_GWDCC23_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC23_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC23_OSID_MASK                  0x70000000

/* GWDCC24 Register bit definitions */
#define R_GWCA_GWDCC24_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC24_SM_MASK                    0x3

#define R_GWCA_GWDCC24_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC24_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC24_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC24_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC24_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC24_DCP_MASK                   0x70000

#define R_GWCA_GWDCC24_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC24_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC24_OSID_MASK                  0x70000000

/* GWDCC25 Register bit definitions */
#define R_GWCA_GWDCC25_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC25_SM_MASK                    0x3

#define R_GWCA_GWDCC25_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC25_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC25_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC25_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC25_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC25_DCP_MASK                   0x70000

#define R_GWCA_GWDCC25_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC25_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC25_OSID_MASK                  0x70000000

/* GWDCC26 Register bit definitions */
#define R_GWCA_GWDCC26_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC26_SM_MASK                    0x3

#define R_GWCA_GWDCC26_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC26_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC26_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC26_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC26_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC26_DCP_MASK                   0x70000

#define R_GWCA_GWDCC26_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC26_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC26_OSID_MASK                  0x70000000

/* GWDCC27 Register bit definitions */
#define R_GWCA_GWDCC27_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC27_SM_MASK                    0x3

#define R_GWCA_GWDCC27_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC27_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC27_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC27_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC27_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC27_DCP_MASK                   0x70000

#define R_GWCA_GWDCC27_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC27_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC27_OSID_MASK                  0x70000000

/* GWDCC28 Register bit definitions */
#define R_GWCA_GWDCC28_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC28_SM_MASK                    0x3

#define R_GWCA_GWDCC28_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC28_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC28_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC28_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC28_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC28_DCP_MASK                   0x70000

#define R_GWCA_GWDCC28_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC28_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC28_OSID_MASK                  0x70000000

/* GWDCC29 Register bit definitions */
#define R_GWCA_GWDCC29_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC29_SM_MASK                    0x3

#define R_GWCA_GWDCC29_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC29_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC29_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC29_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC29_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC29_DCP_MASK                   0x70000

#define R_GWCA_GWDCC29_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC29_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC29_OSID_MASK                  0x70000000

/* GWDCC30 Register bit definitions */
#define R_GWCA_GWDCC30_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC30_SM_MASK                    0x3

#define R_GWCA_GWDCC30_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC30_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC30_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC30_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC30_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC30_DCP_MASK                   0x70000

#define R_GWCA_GWDCC30_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC30_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC30_OSID_MASK                  0x70000000

/* GWDCC31 Register bit definitions */
#define R_GWCA_GWDCC31_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC31_SM_MASK                    0x3

#define R_GWCA_GWDCC31_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC31_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC31_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC31_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC31_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC31_DCP_MASK                   0x70000

#define R_GWCA_GWDCC31_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC31_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC31_OSID_MASK                  0x70000000

/* GWDCC32 Register bit definitions */
#define R_GWCA_GWDCC32_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC32_SM_MASK                    0x3

#define R_GWCA_GWDCC32_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC32_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC32_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC32_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC32_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC32_DCP_MASK                   0x70000

#define R_GWCA_GWDCC32_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC32_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC32_OSID_MASK                  0x70000000

/* GWDCC33 Register bit definitions */
#define R_GWCA_GWDCC33_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC33_SM_MASK                    0x3

#define R_GWCA_GWDCC33_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC33_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC33_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC33_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC33_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC33_DCP_MASK                   0x70000

#define R_GWCA_GWDCC33_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC33_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC33_OSID_MASK                  0x70000000

/* GWDCC34 Register bit definitions */
#define R_GWCA_GWDCC34_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC34_SM_MASK                    0x3

#define R_GWCA_GWDCC34_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC34_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC34_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC34_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC34_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC34_DCP_MASK                   0x70000

#define R_GWCA_GWDCC34_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC34_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC34_OSID_MASK                  0x70000000

/* GWDCC35 Register bit definitions */
#define R_GWCA_GWDCC35_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC35_SM_MASK                    0x3

#define R_GWCA_GWDCC35_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC35_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC35_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC35_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC35_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC35_DCP_MASK                   0x70000

#define R_GWCA_GWDCC35_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC35_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC35_OSID_MASK                  0x70000000

/* GWDCC36 Register bit definitions */
#define R_GWCA_GWDCC36_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC36_SM_MASK                    0x3

#define R_GWCA_GWDCC36_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC36_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC36_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC36_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC36_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC36_DCP_MASK                   0x70000

#define R_GWCA_GWDCC36_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC36_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC36_OSID_MASK                  0x70000000

/* GWDCC37 Register bit definitions */
#define R_GWCA_GWDCC37_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC37_SM_MASK                    0x3

#define R_GWCA_GWDCC37_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC37_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC37_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC37_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC37_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC37_DCP_MASK                   0x70000

#define R_GWCA_GWDCC37_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC37_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC37_OSID_MASK                  0x70000000

/* GWDCC38 Register bit definitions */
#define R_GWCA_GWDCC38_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC38_SM_MASK                    0x3

#define R_GWCA_GWDCC38_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC38_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC38_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC38_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC38_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC38_DCP_MASK                   0x70000

#define R_GWCA_GWDCC38_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC38_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC38_OSID_MASK                  0x70000000

/* GWDCC39 Register bit definitions */
#define R_GWCA_GWDCC39_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC39_SM_MASK                    0x3

#define R_GWCA_GWDCC39_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC39_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC39_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC39_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC39_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC39_DCP_MASK                   0x70000

#define R_GWCA_GWDCC39_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC39_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC39_OSID_MASK                  0x70000000

/* GWDCC40 Register bit definitions */
#define R_GWCA_GWDCC40_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC40_SM_MASK                    0x3

#define R_GWCA_GWDCC40_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC40_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC40_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC40_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC40_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC40_DCP_MASK                   0x70000

#define R_GWCA_GWDCC40_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC40_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC40_OSID_MASK                  0x70000000

/* GWDCC41 Register bit definitions */
#define R_GWCA_GWDCC41_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC41_SM_MASK                    0x3

#define R_GWCA_GWDCC41_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC41_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC41_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC41_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC41_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC41_DCP_MASK                   0x70000

#define R_GWCA_GWDCC41_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC41_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC41_OSID_MASK                  0x70000000

/* GWDCC42 Register bit definitions */
#define R_GWCA_GWDCC42_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC42_SM_MASK                    0x3

#define R_GWCA_GWDCC42_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC42_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC42_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC42_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC42_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC42_DCP_MASK                   0x70000

#define R_GWCA_GWDCC42_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC42_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC42_OSID_MASK                  0x70000000

/* GWDCC43 Register bit definitions */
#define R_GWCA_GWDCC43_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC43_SM_MASK                    0x3

#define R_GWCA_GWDCC43_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC43_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC43_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC43_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC43_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC43_DCP_MASK                   0x70000

#define R_GWCA_GWDCC43_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC43_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC43_OSID_MASK                  0x70000000

/* GWDCC44 Register bit definitions */
#define R_GWCA_GWDCC44_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC44_SM_MASK                    0x3

#define R_GWCA_GWDCC44_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC44_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC44_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC44_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC44_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC44_DCP_MASK                   0x70000

#define R_GWCA_GWDCC44_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC44_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC44_OSID_MASK                  0x70000000

/* GWDCC45 Register bit definitions */
#define R_GWCA_GWDCC45_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC45_SM_MASK                    0x3

#define R_GWCA_GWDCC45_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC45_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC45_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC45_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC45_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC45_DCP_MASK                   0x70000

#define R_GWCA_GWDCC45_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC45_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC45_OSID_MASK                  0x70000000

/* GWDCC46 Register bit definitions */
#define R_GWCA_GWDCC46_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC46_SM_MASK                    0x3

#define R_GWCA_GWDCC46_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC46_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC46_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC46_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC46_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC46_DCP_MASK                   0x70000

#define R_GWCA_GWDCC46_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC46_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC46_OSID_MASK                  0x70000000

/* GWDCC47 Register bit definitions */
#define R_GWCA_GWDCC47_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC47_SM_MASK                    0x3

#define R_GWCA_GWDCC47_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC47_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC47_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC47_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC47_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC47_DCP_MASK                   0x70000

#define R_GWCA_GWDCC47_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC47_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC47_OSID_MASK                  0x70000000

/* GWDCC48 Register bit definitions */
#define R_GWCA_GWDCC48_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC48_SM_MASK                    0x3

#define R_GWCA_GWDCC48_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC48_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC48_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC48_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC48_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC48_DCP_MASK                   0x70000

#define R_GWCA_GWDCC48_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC48_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC48_OSID_MASK                  0x70000000

/* GWDCC49 Register bit definitions */
#define R_GWCA_GWDCC49_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC49_SM_MASK                    0x3

#define R_GWCA_GWDCC49_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC49_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC49_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC49_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC49_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC49_DCP_MASK                   0x70000

#define R_GWCA_GWDCC49_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC49_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC49_OSID_MASK                  0x70000000

/* GWDCC50 Register bit definitions */
#define R_GWCA_GWDCC50_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC50_SM_MASK                    0x3

#define R_GWCA_GWDCC50_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC50_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC50_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC50_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC50_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC50_DCP_MASK                   0x70000

#define R_GWCA_GWDCC50_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC50_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC50_OSID_MASK                  0x70000000

/* GWDCC51 Register bit definitions */
#define R_GWCA_GWDCC51_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC51_SM_MASK                    0x3

#define R_GWCA_GWDCC51_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC51_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC51_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC51_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC51_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC51_DCP_MASK                   0x70000

#define R_GWCA_GWDCC51_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC51_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC51_OSID_MASK                  0x70000000

/* GWDCC52 Register bit definitions */
#define R_GWCA_GWDCC52_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC52_SM_MASK                    0x3

#define R_GWCA_GWDCC52_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC52_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC52_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC52_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC52_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC52_DCP_MASK                   0x70000

#define R_GWCA_GWDCC52_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC52_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC52_OSID_MASK                  0x70000000

/* GWDCC53 Register bit definitions */
#define R_GWCA_GWDCC53_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC53_SM_MASK                    0x3

#define R_GWCA_GWDCC53_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC53_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC53_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC53_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC53_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC53_DCP_MASK                   0x70000

#define R_GWCA_GWDCC53_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC53_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC53_OSID_MASK                  0x70000000

/* GWDCC54 Register bit definitions */
#define R_GWCA_GWDCC54_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC54_SM_MASK                    0x3

#define R_GWCA_GWDCC54_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC54_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC54_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC54_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC54_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC54_DCP_MASK                   0x70000

#define R_GWCA_GWDCC54_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC54_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC54_OSID_MASK                  0x70000000

/* GWDCC55 Register bit definitions */
#define R_GWCA_GWDCC55_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC55_SM_MASK                    0x3

#define R_GWCA_GWDCC55_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC55_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC55_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC55_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC55_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC55_DCP_MASK                   0x70000

#define R_GWCA_GWDCC55_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC55_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC55_OSID_MASK                  0x70000000

/* GWDCC56 Register bit definitions */
#define R_GWCA_GWDCC56_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC56_SM_MASK                    0x3

#define R_GWCA_GWDCC56_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC56_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC56_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC56_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC56_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC56_DCP_MASK                   0x70000

#define R_GWCA_GWDCC56_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC56_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC56_OSID_MASK                  0x70000000

/* GWDCC57 Register bit definitions */
#define R_GWCA_GWDCC57_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC57_SM_MASK                    0x3

#define R_GWCA_GWDCC57_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC57_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC57_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC57_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC57_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC57_DCP_MASK                   0x70000

#define R_GWCA_GWDCC57_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC57_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC57_OSID_MASK                  0x70000000

/* GWDCC58 Register bit definitions */
#define R_GWCA_GWDCC58_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC58_SM_MASK                    0x3

#define R_GWCA_GWDCC58_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC58_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC58_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC58_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC58_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC58_DCP_MASK                   0x70000

#define R_GWCA_GWDCC58_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC58_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC58_OSID_MASK                  0x70000000

/* GWDCC59 Register bit definitions */
#define R_GWCA_GWDCC59_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC59_SM_MASK                    0x3

#define R_GWCA_GWDCC59_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC59_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC59_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC59_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC59_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC59_DCP_MASK                   0x70000

#define R_GWCA_GWDCC59_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC59_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC59_OSID_MASK                  0x70000000

/* GWDCC60 Register bit definitions */
#define R_GWCA_GWDCC60_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC60_SM_MASK                    0x3

#define R_GWCA_GWDCC60_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC60_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC60_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC60_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC60_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC60_DCP_MASK                   0x70000

#define R_GWCA_GWDCC60_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC60_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC60_OSID_MASK                  0x70000000

/* GWDCC61 Register bit definitions */
#define R_GWCA_GWDCC61_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC61_SM_MASK                    0x3

#define R_GWCA_GWDCC61_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC61_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC61_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC61_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC61_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC61_DCP_MASK                   0x70000

#define R_GWCA_GWDCC61_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC61_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC61_OSID_MASK                  0x70000000

/* GWDCC62 Register bit definitions */
#define R_GWCA_GWDCC62_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC62_SM_MASK                    0x3

#define R_GWCA_GWDCC62_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC62_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC62_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC62_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC62_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC62_DCP_MASK                   0x70000

#define R_GWCA_GWDCC62_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC62_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC62_OSID_MASK                  0x70000000

/* GWDCC63 Register bit definitions */
#define R_GWCA_GWDCC63_SM_SHIFT                   (0)  /*  */
#define R_GWCA_GWDCC63_SM_MASK                    0x3

#define R_GWCA_GWDCC63_EDE                        (1 << 8)  /*  */

#define R_GWCA_GWDCC63_ETS                        (1 << 9)  /*  */

#define R_GWCA_GWDCC63_SL                         (1 << 10)  /*  */

#define R_GWCA_GWDCC63_DQT                        (1 << 11)  /*  */

#define R_GWCA_GWDCC63_DCP_SHIFT                  (16)  /*  */
#define R_GWCA_GWDCC63_DCP_MASK                   0x70000

#define R_GWCA_GWDCC63_BALR                       (1 << 24)  /*  */

#define R_GWCA_GWDCC63_OSID_SHIFT                 (28)  /*  */
#define R_GWCA_GWDCC63_OSID_MASK                  0x70000000

/* GWAARSS Register bit definitions */
#define R_GWCA_GWAARSS_AARA_SHIFT                 (0)  /*  */
#define R_GWCA_GWAARSS_AARA_MASK                  0x7f

/* GWAARSR0 Register bit definitions */
#define R_GWCA_GWAARSR0_ACARU_SHIFT               (0)  /*  */
#define R_GWCA_GWAARSR0_ACARU_MASK                0xff

#define R_GWCA_GWAARSR0_AARSEF                    (1 << 16)  /*  */

#define R_GWCA_GWAARSR0_AARSSF                    (1 << 17)  /*  */

#define R_GWCA_GWAARSR0_AARS                      (1 << 31)  /*  */

/* GWAARSR1 Register bit definitions */
#define R_GWCA_GWAARSR1_ACARD_SHIFT               (0)  /*  */
#define R_GWCA_GWAARSR1_ACARD_MASK                0xffffffff

/* GWIDAUAS0 Register bit definitions */
#define R_GWCA_GWIDAUAS0_IDAUAS_SHIFT             (0)  /*  */
#define R_GWCA_GWIDAUAS0_IDAUAS_MASK              0xffffff

/* GWIDAUAS1 Register bit definitions */
#define R_GWCA_GWIDAUAS1_IDAUAS_SHIFT             (0)  /*  */
#define R_GWCA_GWIDAUAS1_IDAUAS_MASK              0xffffff

/* GWIDAUAS2 Register bit definitions */
#define R_GWCA_GWIDAUAS2_IDAUAS_SHIFT             (0)  /*  */
#define R_GWCA_GWIDAUAS2_IDAUAS_MASK              0xffffff

/* GWIDAUAS3 Register bit definitions */
#define R_GWCA_GWIDAUAS3_IDAUAS_SHIFT             (0)  /*  */
#define R_GWCA_GWIDAUAS3_IDAUAS_MASK              0xffffff

/* GWIDASM0 Register bit definitions */
#define R_GWCA_GWIDASM0_IDAS_SHIFT                (0)  /*  */
#define R_GWCA_GWIDASM0_IDAS_MASK                 0xffffff

/* GWIDASM1 Register bit definitions */
#define R_GWCA_GWIDASM1_IDAS_SHIFT                (0)  /*  */
#define R_GWCA_GWIDASM1_IDAS_MASK                 0xffffff

/* GWIDASM2 Register bit definitions */
#define R_GWCA_GWIDASM2_IDAS_SHIFT                (0)  /*  */
#define R_GWCA_GWIDASM2_IDAS_MASK                 0xffffff

/* GWIDASM3 Register bit definitions */
#define R_GWCA_GWIDASM3_IDAS_SHIFT                (0)  /*  */
#define R_GWCA_GWIDASM3_IDAS_MASK                 0xffffff

/* GWIDASAM00 Register bit definitions */
#define R_GWCA_GWIDASAM00_IDASAU_SHIFT            (0)  /*  */
#define R_GWCA_GWIDASAM00_IDASAU_MASK             0xff

/* GWIDASAM10 Register bit definitions */
#define R_GWCA_GWIDASAM10_IDASAL_SHIFT            (0)  /*  */
#define R_GWCA_GWIDASAM10_IDASAL_MASK             0xffffffff

/* GWIDASAM01 Register bit definitions */
#define R_GWCA_GWIDASAM01_IDASAU_SHIFT            (0)  /*  */
#define R_GWCA_GWIDASAM01_IDASAU_MASK             0xff

/* GWIDASAM11 Register bit definitions */
#define R_GWCA_GWIDASAM11_IDASAL_SHIFT            (0)  /*  */
#define R_GWCA_GWIDASAM11_IDASAL_MASK             0xffffffff

/* GWIDASAM02 Register bit definitions */
#define R_GWCA_GWIDASAM02_IDASAU_SHIFT            (0)  /*  */
#define R_GWCA_GWIDASAM02_IDASAU_MASK             0xff

/* GWIDASAM12 Register bit definitions */
#define R_GWCA_GWIDASAM12_IDASAL_SHIFT            (0)  /*  */
#define R_GWCA_GWIDASAM12_IDASAL_MASK             0xffffffff

/* GWIDASAM03 Register bit definitions */
#define R_GWCA_GWIDASAM03_IDASAU_SHIFT            (0)  /*  */
#define R_GWCA_GWIDASAM03_IDASAU_MASK             0xff

/* GWIDASAM13 Register bit definitions */
#define R_GWCA_GWIDASAM13_IDASAL_SHIFT            (0)  /*  */
#define R_GWCA_GWIDASAM13_IDASAL_MASK             0xffffffff

/* GWIDACAM00 Register bit definitions */
#define R_GWCA_GWIDACAM00_IDACAU_SHIFT            (0)  /*  */
#define R_GWCA_GWIDACAM00_IDACAU_MASK             0xff

/* GWIDACAM10 Register bit definitions */
#define R_GWCA_GWIDACAM10_IDACAL_SHIFT            (0)  /*  */
#define R_GWCA_GWIDACAM10_IDACAL_MASK             0xffffffff

/* GWIDACAM01 Register bit definitions */
#define R_GWCA_GWIDACAM01_IDACAU_SHIFT            (0)  /*  */
#define R_GWCA_GWIDACAM01_IDACAU_MASK             0xff

/* GWIDACAM11 Register bit definitions */
#define R_GWCA_GWIDACAM11_IDACAL_SHIFT            (0)  /*  */
#define R_GWCA_GWIDACAM11_IDACAL_MASK             0xffffffff

/* GWIDACAM02 Register bit definitions */
#define R_GWCA_GWIDACAM02_IDACAU_SHIFT            (0)  /*  */
#define R_GWCA_GWIDACAM02_IDACAU_MASK             0xff

/* GWIDACAM12 Register bit definitions */
#define R_GWCA_GWIDACAM12_IDACAL_SHIFT            (0)  /*  */
#define R_GWCA_GWIDACAM12_IDACAL_MASK             0xffffffff

/* GWIDACAM03 Register bit definitions */
#define R_GWCA_GWIDACAM03_IDACAU_SHIFT            (0)  /*  */
#define R_GWCA_GWIDACAM03_IDACAU_MASK             0xff

/* GWIDACAM13 Register bit definitions */
#define R_GWCA_GWIDACAM13_IDACAL_SHIFT            (0)  /*  */
#define R_GWCA_GWIDACAM13_IDACAL_MASK             0xffffffff

/* GWGRLC Register bit definitions */
#define R_GWCA_GWGRLC_GRLIV_SHIFT                 (0)  /*  */
#define R_GWCA_GWGRLC_GRLIV_MASK                  0xffff

#define R_GWCA_GWGRLC_GRLE                        (1 << 16)  /*  */

#define R_GWCA_GWGRLC_GRLULRS                     (1 << 17)  /*  */

/* GWGRLULC Register bit definitions */
#define R_GWCA_GWGRLULC_GRLUL_SHIFT               (0)  /*  */
#define R_GWCA_GWGRLULC_GRLUL_MASK                0xffffff

/* GWRLC0 Register bit definitions */
#define R_GWCA_GWRLC0_RLIV_SHIFT                  (0)  /*  */
#define R_GWCA_GWRLC0_RLIV_MASK                   0xfff

#define R_GWCA_GWRLC0_RLE                         (1 << 16)  /*  */

/* GWRLULC0 Register bit definitions */
#define R_GWCA_GWRLULC0_RLUL_SHIFT                (0)  /*  */
#define R_GWCA_GWRLULC0_RLUL_MASK                 0xffffff

/* GWRLC1 Register bit definitions */
#define R_GWCA_GWRLC1_RLIV_SHIFT                  (0)  /*  */
#define R_GWCA_GWRLC1_RLIV_MASK                   0xfff

#define R_GWCA_GWRLC1_RLE                         (1 << 16)  /*  */

/* GWRLULC1 Register bit definitions */
#define R_GWCA_GWRLULC1_RLUL_SHIFT                (0)  /*  */
#define R_GWCA_GWRLULC1_RLUL_MASK                 0xffffff

/* GWRLC2 Register bit definitions */
#define R_GWCA_GWRLC2_RLIV_SHIFT                  (0)  /*  */
#define R_GWCA_GWRLC2_RLIV_MASK                   0xfff

#define R_GWCA_GWRLC2_RLE                         (1 << 16)  /*  */

/* GWRLULC2 Register bit definitions */
#define R_GWCA_GWRLULC2_RLUL_SHIFT                (0)  /*  */
#define R_GWCA_GWRLULC2_RLUL_MASK                 0xffffff

/* GWRLC3 Register bit definitions */
#define R_GWCA_GWRLC3_RLIV_SHIFT                  (0)  /*  */
#define R_GWCA_GWRLC3_RLIV_MASK                   0xfff

#define R_GWCA_GWRLC3_RLE                         (1 << 16)  /*  */

/* GWRLULC3 Register bit definitions */
#define R_GWCA_GWRLULC3_RLUL_SHIFT                (0)  /*  */
#define R_GWCA_GWRLULC3_RLUL_MASK                 0xffffff

/* GWRLC4 Register bit definitions */
#define R_GWCA_GWRLC4_RLIV_SHIFT                  (0)  /*  */
#define R_GWCA_GWRLC4_RLIV_MASK                   0xfff

#define R_GWCA_GWRLC4_RLE                         (1 << 16)  /*  */

/* GWRLULC4 Register bit definitions */
#define R_GWCA_GWRLULC4_RLUL_SHIFT                (0)  /*  */
#define R_GWCA_GWRLULC4_RLUL_MASK                 0xffffff

/* GWRLC5 Register bit definitions */
#define R_GWCA_GWRLC5_RLIV_SHIFT                  (0)  /*  */
#define R_GWCA_GWRLC5_RLIV_MASK                   0xfff

#define R_GWCA_GWRLC5_RLE                         (1 << 16)  /*  */

/* GWRLULC5 Register bit definitions */
#define R_GWCA_GWRLULC5_RLUL_SHIFT                (0)  /*  */
#define R_GWCA_GWRLULC5_RLUL_MASK                 0xffffff

/* GWRLC6 Register bit definitions */
#define R_GWCA_GWRLC6_RLIV_SHIFT                  (0)  /*  */
#define R_GWCA_GWRLC6_RLIV_MASK                   0xfff

#define R_GWCA_GWRLC6_RLE                         (1 << 16)  /*  */

/* GWRLULC6 Register bit definitions */
#define R_GWCA_GWRLULC6_RLUL_SHIFT                (0)  /*  */
#define R_GWCA_GWRLULC6_RLUL_MASK                 0xffffff

/* GWRLC7 Register bit definitions */
#define R_GWCA_GWRLC7_RLIV_SHIFT                  (0)  /*  */
#define R_GWCA_GWRLC7_RLIV_MASK                   0xfff

#define R_GWCA_GWRLC7_RLE                         (1 << 16)  /*  */

/* GWRLULC7 Register bit definitions */
#define R_GWCA_GWRLULC7_RLUL_SHIFT                (0)  /*  */
#define R_GWCA_GWRLULC7_RLUL_MASK                 0xffffff

/* GWIDPC Register bit definitions */
#define R_GWCA_GWIDPC_IDPV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDPC_IDPV_MASK                   0x3ff

/* GWIDC0 Register bit definitions */
#define R_GWCA_GWIDC0_IDV_SHIFT                   (0)  /*  */
#define R_GWCA_GWIDC0_IDV_MASK                    0xfff

/* GWIDC1 Register bit definitions */
#define R_GWCA_GWIDC1_IDV_SHIFT                   (0)  /*  */
#define R_GWCA_GWIDC1_IDV_MASK                    0xfff

/* GWIDC2 Register bit definitions */
#define R_GWCA_GWIDC2_IDV_SHIFT                   (0)  /*  */
#define R_GWCA_GWIDC2_IDV_MASK                    0xfff

/* GWIDC3 Register bit definitions */
#define R_GWCA_GWIDC3_IDV_SHIFT                   (0)  /*  */
#define R_GWCA_GWIDC3_IDV_MASK                    0xfff

/* GWIDC4 Register bit definitions */
#define R_GWCA_GWIDC4_IDV_SHIFT                   (0)  /*  */
#define R_GWCA_GWIDC4_IDV_MASK                    0xfff

/* GWIDC5 Register bit definitions */
#define R_GWCA_GWIDC5_IDV_SHIFT                   (0)  /*  */
#define R_GWCA_GWIDC5_IDV_MASK                    0xfff

/* GWIDC6 Register bit definitions */
#define R_GWCA_GWIDC6_IDV_SHIFT                   (0)  /*  */
#define R_GWCA_GWIDC6_IDV_MASK                    0xfff

/* GWIDC7 Register bit definitions */
#define R_GWCA_GWIDC7_IDV_SHIFT                   (0)  /*  */
#define R_GWCA_GWIDC7_IDV_MASK                    0xfff

/* GWIDC8 Register bit definitions */
#define R_GWCA_GWIDC8_IDV_SHIFT                   (0)  /*  */
#define R_GWCA_GWIDC8_IDV_MASK                    0xfff

/* GWIDC9 Register bit definitions */
#define R_GWCA_GWIDC9_IDV_SHIFT                   (0)  /*  */
#define R_GWCA_GWIDC9_IDV_MASK                    0xfff

/* GWIDC10 Register bit definitions */
#define R_GWCA_GWIDC10_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC10_IDV_MASK                   0xfff

/* GWIDC11 Register bit definitions */
#define R_GWCA_GWIDC11_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC11_IDV_MASK                   0xfff

/* GWIDC12 Register bit definitions */
#define R_GWCA_GWIDC12_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC12_IDV_MASK                   0xfff

/* GWIDC13 Register bit definitions */
#define R_GWCA_GWIDC13_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC13_IDV_MASK                   0xfff

/* GWIDC14 Register bit definitions */
#define R_GWCA_GWIDC14_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC14_IDV_MASK                   0xfff

/* GWIDC15 Register bit definitions */
#define R_GWCA_GWIDC15_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC15_IDV_MASK                   0xfff

/* GWIDC16 Register bit definitions */
#define R_GWCA_GWIDC16_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC16_IDV_MASK                   0xfff

/* GWIDC17 Register bit definitions */
#define R_GWCA_GWIDC17_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC17_IDV_MASK                   0xfff

/* GWIDC18 Register bit definitions */
#define R_GWCA_GWIDC18_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC18_IDV_MASK                   0xfff

/* GWIDC19 Register bit definitions */
#define R_GWCA_GWIDC19_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC19_IDV_MASK                   0xfff

/* GWIDC20 Register bit definitions */
#define R_GWCA_GWIDC20_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC20_IDV_MASK                   0xfff

/* GWIDC21 Register bit definitions */
#define R_GWCA_GWIDC21_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC21_IDV_MASK                   0xfff

/* GWIDC22 Register bit definitions */
#define R_GWCA_GWIDC22_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC22_IDV_MASK                   0xfff

/* GWIDC23 Register bit definitions */
#define R_GWCA_GWIDC23_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC23_IDV_MASK                   0xfff

/* GWIDC24 Register bit definitions */
#define R_GWCA_GWIDC24_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC24_IDV_MASK                   0xfff

/* GWIDC25 Register bit definitions */
#define R_GWCA_GWIDC25_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC25_IDV_MASK                   0xfff

/* GWIDC26 Register bit definitions */
#define R_GWCA_GWIDC26_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC26_IDV_MASK                   0xfff

/* GWIDC27 Register bit definitions */
#define R_GWCA_GWIDC27_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC27_IDV_MASK                   0xfff

/* GWIDC28 Register bit definitions */
#define R_GWCA_GWIDC28_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC28_IDV_MASK                   0xfff

/* GWIDC29 Register bit definitions */
#define R_GWCA_GWIDC29_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC29_IDV_MASK                   0xfff

/* GWIDC30 Register bit definitions */
#define R_GWCA_GWIDC30_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC30_IDV_MASK                   0xfff

/* GWIDC31 Register bit definitions */
#define R_GWCA_GWIDC31_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC31_IDV_MASK                   0xfff

/* GWIDC32 Register bit definitions */
#define R_GWCA_GWIDC32_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC32_IDV_MASK                   0xfff

/* GWIDC33 Register bit definitions */
#define R_GWCA_GWIDC33_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC33_IDV_MASK                   0xfff

/* GWIDC34 Register bit definitions */
#define R_GWCA_GWIDC34_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC34_IDV_MASK                   0xfff

/* GWIDC35 Register bit definitions */
#define R_GWCA_GWIDC35_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC35_IDV_MASK                   0xfff

/* GWIDC36 Register bit definitions */
#define R_GWCA_GWIDC36_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC36_IDV_MASK                   0xfff

/* GWIDC37 Register bit definitions */
#define R_GWCA_GWIDC37_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC37_IDV_MASK                   0xfff

/* GWIDC38 Register bit definitions */
#define R_GWCA_GWIDC38_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC38_IDV_MASK                   0xfff

/* GWIDC39 Register bit definitions */
#define R_GWCA_GWIDC39_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC39_IDV_MASK                   0xfff

/* GWIDC40 Register bit definitions */
#define R_GWCA_GWIDC40_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC40_IDV_MASK                   0xfff

/* GWIDC41 Register bit definitions */
#define R_GWCA_GWIDC41_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC41_IDV_MASK                   0xfff

/* GWIDC42 Register bit definitions */
#define R_GWCA_GWIDC42_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC42_IDV_MASK                   0xfff

/* GWIDC43 Register bit definitions */
#define R_GWCA_GWIDC43_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC43_IDV_MASK                   0xfff

/* GWIDC44 Register bit definitions */
#define R_GWCA_GWIDC44_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC44_IDV_MASK                   0xfff

/* GWIDC45 Register bit definitions */
#define R_GWCA_GWIDC45_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC45_IDV_MASK                   0xfff

/* GWIDC46 Register bit definitions */
#define R_GWCA_GWIDC46_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC46_IDV_MASK                   0xfff

/* GWIDC47 Register bit definitions */
#define R_GWCA_GWIDC47_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC47_IDV_MASK                   0xfff

/* GWIDC48 Register bit definitions */
#define R_GWCA_GWIDC48_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC48_IDV_MASK                   0xfff

/* GWIDC49 Register bit definitions */
#define R_GWCA_GWIDC49_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC49_IDV_MASK                   0xfff

/* GWIDC50 Register bit definitions */
#define R_GWCA_GWIDC50_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC50_IDV_MASK                   0xfff

/* GWIDC51 Register bit definitions */
#define R_GWCA_GWIDC51_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC51_IDV_MASK                   0xfff

/* GWIDC52 Register bit definitions */
#define R_GWCA_GWIDC52_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC52_IDV_MASK                   0xfff

/* GWIDC53 Register bit definitions */
#define R_GWCA_GWIDC53_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC53_IDV_MASK                   0xfff

/* GWIDC54 Register bit definitions */
#define R_GWCA_GWIDC54_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC54_IDV_MASK                   0xfff

/* GWIDC55 Register bit definitions */
#define R_GWCA_GWIDC55_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC55_IDV_MASK                   0xfff

/* GWIDC56 Register bit definitions */
#define R_GWCA_GWIDC56_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC56_IDV_MASK                   0xfff

/* GWIDC57 Register bit definitions */
#define R_GWCA_GWIDC57_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC57_IDV_MASK                   0xfff

/* GWIDC58 Register bit definitions */
#define R_GWCA_GWIDC58_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC58_IDV_MASK                   0xfff

/* GWIDC59 Register bit definitions */
#define R_GWCA_GWIDC59_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC59_IDV_MASK                   0xfff

/* GWIDC60 Register bit definitions */
#define R_GWCA_GWIDC60_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC60_IDV_MASK                   0xfff

/* GWIDC61 Register bit definitions */
#define R_GWCA_GWIDC61_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC61_IDV_MASK                   0xfff

/* GWIDC62 Register bit definitions */
#define R_GWCA_GWIDC62_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC62_IDV_MASK                   0xfff

/* GWIDC63 Register bit definitions */
#define R_GWCA_GWIDC63_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC63_IDV_MASK                   0xfff

/* GWIDC64 Register bit definitions */
#define R_GWCA_GWIDC64_IDV_SHIFT                  (0)  /*  */
#define R_GWCA_GWIDC64_IDV_MASK                   0xfff

/* GWRDCN Register bit definitions */
#define R_GWCA_GWRDCN_RDN_SHIFT                   (0)  /*  */
#define R_GWCA_GWRDCN_RDN_MASK                    0xffffffff

/* GWTDCN Register bit definitions */
#define R_GWCA_GWTDCN_TDN_SHIFT                   (0)  /*  */
#define R_GWCA_GWTDCN_TDN_MASK                    0xffffffff

/* GWTSCN Register bit definitions */
#define R_GWCA_GWTSCN_TN_SHIFT                    (0)  /*  */
#define R_GWCA_GWTSCN_TN_MASK                     0xffffffff

/* GWTSOVFECN Register bit definitions */
#define R_GWCA_GWTSOVFECN_TSOVFEN_SHIFT           (0)  /*  */
#define R_GWCA_GWTSOVFECN_TSOVFEN_MASK            0xffff

/* GWUSMFSECN Register bit definitions */
#define R_GWCA_GWUSMFSECN_USMFSEN_SHIFT           (0)  /*  */
#define R_GWCA_GWUSMFSECN_USMFSEN_MASK            0xffff

/* GWTFECN Register bit definitions */
#define R_GWCA_GWTFECN_TFEN_SHIFT                 (0)  /*  */
#define R_GWCA_GWTFECN_TFEN_MASK                  0xffff

/* GWSEQECN Register bit definitions */
#define R_GWCA_GWSEQECN_SEQEN_SHIFT               (0)  /*  */
#define R_GWCA_GWSEQECN_SEQEN_MASK                0xffff

/* GWTXDNECN Register bit definitions */
#define R_GWCA_GWTXDNECN_TXDNEN_SHIFT             (0)  /*  */
#define R_GWCA_GWTXDNECN_TXDNEN_MASK              0xffff

/* GWFSECN Register bit definitions */
#define R_GWCA_GWFSECN_FSEN_SHIFT                 (0)  /*  */
#define R_GWCA_GWFSECN_FSEN_MASK                  0xffff

/* GWTDFECN Register bit definitions */
#define R_GWCA_GWTDFECN_TDFEN_SHIFT               (0)  /*  */
#define R_GWCA_GWTDFECN_TDFEN_MASK                0xffff

/* GWTSDNECN Register bit definitions */
#define R_GWCA_GWTSDNECN_TSDNEN_SHIFT             (0)  /*  */
#define R_GWCA_GWTSDNECN_TSDNEN_MASK              0xffff

/* GWDQOECN Register bit definitions */
#define R_GWCA_GWDQOECN_DQOEN_SHIFT               (0)  /*  */
#define R_GWCA_GWDQOECN_DQOEN_MASK                0xffff

/* GWDQSECN Register bit definitions */
#define R_GWCA_GWDQSECN_DQSEN_SHIFT               (0)  /*  */
#define R_GWCA_GWDQSECN_DQSEN_MASK                0xffff

/* GWDFECN Register bit definitions */
#define R_GWCA_GWDFECN_DFEN_SHIFT                 (0)  /*  */
#define R_GWCA_GWDFECN_DFEN_MASK                  0xffff

/* GWDSECN Register bit definitions */
#define R_GWCA_GWDSECN_DSEN_SHIFT                 (0)  /*  */
#define R_GWCA_GWDSECN_DSEN_MASK                  0xffff

/* GWDSZECN Register bit definitions */
#define R_GWCA_GWDSZECN_DSZEN_SHIFT               (0)  /*  */
#define R_GWCA_GWDSZECN_DSZEN_MASK                0xffff

/* GWDCTECN Register bit definitions */
#define R_GWCA_GWDCTECN_DCTEN_SHIFT               (0)  /*  */
#define R_GWCA_GWDCTECN_DCTEN_MASK                0xffff

/* GWRXDNECN Register bit definitions */
#define R_GWCA_GWRXDNECN_RXDNEN_SHIFT             (0)  /*  */
#define R_GWCA_GWRXDNECN_RXDNEN_MASK              0xffff

/* GWTSDIS Register bit definitions */
#define R_GWCA_GWTSDIS_TSDIS0                     (1 << 0)  /*  */

#define R_GWCA_GWTSDIS_TSDIS1                     (1 << 1)  /*  */

/* GWTSDIE Register bit definitions */
#define R_GWCA_GWTSDIE_TSDIE0                     (1 << 0)  /*  */

#define R_GWCA_GWTSDIE_TSDIE1                     (1 << 1)  /*  */

/* GWTSDID Register bit definitions */
#define R_GWCA_GWTSDID_TSDID0                     (1 << 0)  /*  */

#define R_GWCA_GWTSDID_TSDID1                     (1 << 1)  /*  */

/* GWEIS0 Register bit definitions */
#define R_GWCA_GWEIS0_AES                         (1 << 0)  /*  */

#define R_GWCA_GWEIS0_DECCES                      (1 << 1)  /*  */

#define R_GWCA_GWEIS0_TECCES                      (1 << 2)  /*  */

#define R_GWCA_GWEIS0_PECCES                      (1 << 3)  /*  */

#define R_GWCA_GWEIS0_DSECCES                     (1 << 4)  /*  */

#define R_GWCA_GWEIS0_MECCES                      (1 << 5)  /*  */

#define R_GWCA_GWEIS0_AECCES                      (1 << 6)  /*  */

#define R_GWCA_GWEIS0_TSECCES                     (1 << 7)  /*  */

#define R_GWCA_GWEIS0_L23UECCES                   (1 << 8)  /*  */

#define R_GWCA_GWEIS0_TSOVFES                     (1 << 9)  /*  */

#define R_GWCA_GWEIS0_USMFSES                     (1 << 10)  /*  */

#define R_GWCA_GWEIS0_TFES                        (1 << 11)  /*  */

#define R_GWCA_GWEIS0_SEQES                       (1 << 12)  /*  */

#define R_GWCA_GWEIS0_TXDNES                      (1 << 14)  /*  */

#define R_GWCA_GWEIS0_TSHES                       (1 << 15)  /*  */

#define R_GWCA_GWEIS0_FSES0                       (1 << 16)  /*  */

#define R_GWCA_GWEIS0_FSES1                       (1 << 17)  /*  */

#define R_GWCA_GWEIS0_FSES2                       (1 << 18)  /*  */

#define R_GWCA_GWEIS0_FSES3                       (1 << 19)  /*  */

#define R_GWCA_GWEIS0_FSES4                       (1 << 20)  /*  */

#define R_GWCA_GWEIS0_FSES5                       (1 << 21)  /*  */

#define R_GWCA_GWEIS0_FSES6                       (1 << 22)  /*  */

#define R_GWCA_GWEIS0_FSES7                       (1 << 23)  /*  */

#define R_GWCA_GWEIS0_TDFES0                      (1 << 24)  /*  */

#define R_GWCA_GWEIS0_TDFES1                      (1 << 25)  /*  */

#define R_GWCA_GWEIS0_TSDNES0                     (1 << 28)  /*  */

#define R_GWCA_GWEIS0_TSDNES1                     (1 << 29)  /*  */

/* GWEIE0 Register bit definitions */
#define R_GWCA_GWEIE0_AEE                         (1 << 0)  /*  */

#define R_GWCA_GWEIE0_DECCEE                      (1 << 1)  /*  */

#define R_GWCA_GWEIE0_TECCEE                      (1 << 2)  /*  */

#define R_GWCA_GWEIE0_PECCEE                      (1 << 3)  /*  */

#define R_GWCA_GWEIE0_DSECCEE                     (1 << 4)  /*  */

#define R_GWCA_GWEIE0_MECCEE                      (1 << 5)  /*  */

#define R_GWCA_GWEIE0_AECCEE                      (1 << 6)  /*  */

#define R_GWCA_GWEIE0_TSECCEE                     (1 << 7)  /*  */

#define R_GWCA_GWEIE0_L23UECCEE                   (1 << 8)  /*  */

#define R_GWCA_GWEIE0_TSOVFEE                     (1 << 9)  /*  */

#define R_GWCA_GWEIE0_USMFSEE                     (1 << 10)  /*  */

#define R_GWCA_GWEIE0_TFEE                        (1 << 11)  /*  */

#define R_GWCA_GWEIE0_SEQEE                       (1 << 12)  /*  */

#define R_GWCA_GWEIE0_TXDNEE                      (1 << 14)  /*  */

#define R_GWCA_GWEIE0_TSHEE                       (1 << 15)  /*  */

#define R_GWCA_GWEIE0_FSEE0                       (1 << 16)  /*  */

#define R_GWCA_GWEIE0_FSEE1                       (1 << 17)  /*  */

#define R_GWCA_GWEIE0_FSEE2                       (1 << 18)  /*  */

#define R_GWCA_GWEIE0_FSEE3                       (1 << 19)  /*  */

#define R_GWCA_GWEIE0_FSEE4                       (1 << 20)  /*  */

#define R_GWCA_GWEIE0_FSEE5                       (1 << 21)  /*  */

#define R_GWCA_GWEIE0_FSEE6                       (1 << 22)  /*  */

#define R_GWCA_GWEIE0_FSEE7                       (1 << 23)  /*  */

#define R_GWCA_GWEIE0_TDFEE0                      (1 << 24)  /*  */

#define R_GWCA_GWEIE0_TDFEE1                      (1 << 25)  /*  */

#define R_GWCA_GWEIE0_TSDNEE0                     (1 << 28)  /*  */

#define R_GWCA_GWEIE0_TSDNEE1                     (1 << 29)  /*  */

/* GWEID0 Register bit definitions */
#define R_GWCA_GWEID0_AED                         (1 << 0)  /*  */

#define R_GWCA_GWEID0_TECCED                      (1 << 1)  /*  */

#define R_GWCA_GWEID0_DECCED                      (1 << 2)  /*  */

#define R_GWCA_GWEID0_PECCED                      (1 << 3)  /*  */

#define R_GWCA_GWEID0_DSECCED                     (1 << 4)  /*  */

#define R_GWCA_GWEID0_MECCED                      (1 << 5)  /*  */

#define R_GWCA_GWEID0_AECCED                      (1 << 6)  /*  */

#define R_GWCA_GWEID0_TSECCED                     (1 << 7)  /*  */

#define R_GWCA_GWEID0_L23UECCED                   (1 << 8)  /*  */

#define R_GWCA_GWEID0_TSOVFED                     (1 << 9)  /*  */

#define R_GWCA_GWEID0_USMFSED                     (1 << 10)  /*  */

#define R_GWCA_GWEID0_TFED                        (1 << 11)  /*  */

#define R_GWCA_GWEID0_SEQED                       (1 << 12)  /*  */

#define R_GWCA_GWEID0_IIPED                       (1 << 13)  /*  */

#define R_GWCA_GWEID0_TXDNED                      (1 << 14)  /*  */

#define R_GWCA_GWEID0_TSHED                       (1 << 15)  /*  */

#define R_GWCA_GWEID0_FSED0                       (1 << 16)  /*  */

#define R_GWCA_GWEID0_FSED1                       (1 << 17)  /*  */

#define R_GWCA_GWEID0_FSED2                       (1 << 18)  /*  */

#define R_GWCA_GWEID0_FSED3                       (1 << 19)  /*  */

#define R_GWCA_GWEID0_FSED4                       (1 << 20)  /*  */

#define R_GWCA_GWEID0_FSED5                       (1 << 21)  /*  */

#define R_GWCA_GWEID0_FSED6                       (1 << 22)  /*  */

#define R_GWCA_GWEID0_FSED7                       (1 << 23)  /*  */

#define R_GWCA_GWEID0_TDFED0                      (1 << 24)  /*  */

#define R_GWCA_GWEID0_TDFED1                      (1 << 25)  /*  */

#define R_GWCA_GWEID0_TSDNED0                     (1 << 28)  /*  */

#define R_GWCA_GWEID0_TSDNED1                     (1 << 29)  /*  */

/* GWEIS1 Register bit definitions */
#define R_GWCA_GWEIS1_DQOES0                      (1 << 0)  /*  */

#define R_GWCA_GWEIS1_DQOES1                      (1 << 1)  /*  */

#define R_GWCA_GWEIS1_DQOES2                      (1 << 2)  /*  */

#define R_GWCA_GWEIS1_DQOES3                      (1 << 3)  /*  */

#define R_GWCA_GWEIS1_DQOES4                      (1 << 4)  /*  */

#define R_GWCA_GWEIS1_DQOES5                      (1 << 5)  /*  */

#define R_GWCA_GWEIS1_DQOES6                      (1 << 6)  /*  */

#define R_GWCA_GWEIS1_DQOES7                      (1 << 7)  /*  */

#define R_GWCA_GWEIS1_DQSES0                      (1 << 16)  /*  */

#define R_GWCA_GWEIS1_DQSES1                      (1 << 17)  /*  */

#define R_GWCA_GWEIS1_DQSES2                      (1 << 18)  /*  */

#define R_GWCA_GWEIS1_DQSES3                      (1 << 19)  /*  */

#define R_GWCA_GWEIS1_DQSES4                      (1 << 20)  /*  */

#define R_GWCA_GWEIS1_DQSES5                      (1 << 21)  /*  */

#define R_GWCA_GWEIS1_DQSES6                      (1 << 22)  /*  */

#define R_GWCA_GWEIS1_DQSES7                      (1 << 23)  /*  */

/* GWEIE1 Register bit definitions */
#define R_GWCA_GWEIE1_DQOEE0                      (1 << 0)  /*  */

#define R_GWCA_GWEIE1_DQOEE1                      (1 << 1)  /*  */

#define R_GWCA_GWEIE1_DQOEE2                      (1 << 2)  /*  */

#define R_GWCA_GWEIE1_DQOEE3                      (1 << 3)  /*  */

#define R_GWCA_GWEIE1_DQOEE4                      (1 << 4)  /*  */

#define R_GWCA_GWEIE1_DQOEE5                      (1 << 5)  /*  */

#define R_GWCA_GWEIE1_DQOEE6                      (1 << 6)  /*  */

#define R_GWCA_GWEIE1_DQOEE7                      (1 << 7)  /*  */

#define R_GWCA_GWEIE1_DQSEE0                      (1 << 16)  /*  */

#define R_GWCA_GWEIE1_DQSEE1                      (1 << 17)  /*  */

#define R_GWCA_GWEIE1_DQSEE2                      (1 << 18)  /*  */

#define R_GWCA_GWEIE1_DQSEE3                      (1 << 19)  /*  */

#define R_GWCA_GWEIE1_DQSEE4                      (1 << 20)  /*  */

#define R_GWCA_GWEIE1_DQSEE5                      (1 << 21)  /*  */

#define R_GWCA_GWEIE1_DQSEE6                      (1 << 22)  /*  */

#define R_GWCA_GWEIE1_DQSEE7                      (1 << 23)  /*  */

/* GWEID1 Register bit definitions */
#define R_GWCA_GWEID1_DQOED0                      (1 << 0)  /*  */

#define R_GWCA_GWEID1_DQOED1                      (1 << 1)  /*  */

#define R_GWCA_GWEID1_DQOED2                      (1 << 2)  /*  */

#define R_GWCA_GWEID1_DQOED3                      (1 << 3)  /*  */

#define R_GWCA_GWEID1_DQOED4                      (1 << 4)  /*  */

#define R_GWCA_GWEID1_DQOED5                      (1 << 5)  /*  */

#define R_GWCA_GWEID1_DQOED6                      (1 << 6)  /*  */

#define R_GWCA_GWEID1_DQOED7                      (1 << 7)  /*  */

#define R_GWCA_GWEID1_DQSED0                      (1 << 16)  /*  */

#define R_GWCA_GWEID1_DQSED1                      (1 << 17)  /*  */

#define R_GWCA_GWEID1_DQSED2                      (1 << 18)  /*  */

#define R_GWCA_GWEID1_DQSED3                      (1 << 19)  /*  */

#define R_GWCA_GWEID1_DQSED4                      (1 << 20)  /*  */

#define R_GWCA_GWEID1_DQSED5                      (1 << 21)  /*  */

#define R_GWCA_GWEID1_DQSED6                      (1 << 22)  /*  */

#define R_GWCA_GWEID1_DQSED7                      (1 << 23)  /*  */

/* GWEIS3 Register bit definitions */
#define R_GWCA_GWEIS3_IAOES0                      (1 << 0)  /*  */

#define R_GWCA_GWEIS3_IAOES1                      (1 << 1)  /*  */

#define R_GWCA_GWEIS3_IAOES2                      (1 << 2)  /*  */

#define R_GWCA_GWEIS3_IAOES3                      (1 << 3)  /*  */

#define R_GWCA_GWEIS3_IAOES4                      (1 << 4)  /*  */

/* GWEIE3 Register bit definitions */
#define R_GWCA_GWEIE3_IAOEE0                      (1 << 0)  /*  */

#define R_GWCA_GWEIE3_IAOEE1                      (1 << 1)  /*  */

#define R_GWCA_GWEIE3_IAOEE2                      (1 << 2)  /*  */

#define R_GWCA_GWEIE3_IAOEE3                      (1 << 3)  /*  */

#define R_GWCA_GWEIE3_IAOEE4                      (1 << 4)  /*  */

/* GWEID3 Register bit definitions */
#define R_GWCA_GWEID3_IAOED0                      (1 << 0)  /*  */

#define R_GWCA_GWEID3_IAOED1                      (1 << 1)  /*  */

#define R_GWCA_GWEID3_IAOED2                      (1 << 2)  /*  */

#define R_GWCA_GWEID3_IAOED3                      (1 << 3)  /*  */

#define R_GWCA_GWEID3_IAOED4                      (1 << 4)  /*  */

/* GWEIS4 Register bit definitions */
#define R_GWCA_GWEIS4_DSSES                       (1 << 0)  /*  */

#define R_GWCA_GWEIS4_DSSEIOS                     (1 << 1)  /*  */

#define R_GWCA_GWEIS4_DSSECN_SHIFT                (8)  /*  */
#define R_GWCA_GWEIS4_DSSECN_MASK                 0x3f00

#define R_GWCA_GWEIS4_DSES                        (1 << 16)  /*  */

#define R_GWCA_GWEIS4_DSEIOS                      (1 << 17)  /*  */

#define R_GWCA_GWEIS4_DSECN_SHIFT                 (24)  /*  */
#define R_GWCA_GWEIS4_DSECN_MASK                  0x3f000000

/* GWEIE4 Register bit definitions */
#define R_GWCA_GWEIE4_DSSEE                       (1 << 0)  /*  */

#define R_GWCA_GWEIE4_DSSEIOE                     (1 << 1)  /*  */

#define R_GWCA_GWEIE4_DSEE                        (1 << 16)  /*  */

#define R_GWCA_GWEIE4_DSEIOE                      (1 << 17)  /*  */

/* GWEID4 Register bit definitions */
#define R_GWCA_GWEID4_DSSED                       (1 << 0)  /*  */

#define R_GWCA_GWEID4_DSSEIOD                     (1 << 1)  /*  */

#define R_GWCA_GWEID4_DSED                        (1 << 16)  /*  */

#define R_GWCA_GWEID4_DSEIOD                      (1 << 17)  /*  */

/* GWEIS5 Register bit definitions */
#define R_GWCA_GWEIS5_DCTES                       (1 << 0)  /*  */

#define R_GWCA_GWEIS5_DCTEIOS                     (1 << 1)  /*  */

#define R_GWCA_GWEIS5_DCTECN_SHIFT                (8)  /*  */
#define R_GWCA_GWEIS5_DCTECN_MASK                 0x3f00

#define R_GWCA_GWEIS5_RXDNES                      (1 << 16)  /*  */

#define R_GWCA_GWEIS5_RXDNEIOS                    (1 << 17)  /*  */

/* GWEIE5 Register bit definitions */
#define R_GWCA_GWEIE5_DCTEE                       (1 << 0)  /*  */

#define R_GWCA_GWEIE5_DCTEIOE                     (1 << 1)  /*  */

#define R_GWCA_GWEIE5_RXDNEE                      (1 << 16)  /*  */

#define R_GWCA_GWEIE5_RXDNEIOE                    (1 << 17)  /*  */

/* GWEID5 Register bit definitions */
#define R_GWCA_GWEID5_DCTED                       (1 << 0)  /*  */

#define R_GWCA_GWEID5_DCTEIOD                     (1 << 1)  /*  */

#define R_GWCA_GWEID5_RXDNED                      (1 << 15)  /*  */

#define R_GWCA_GWEID5_RXDNEIOD                    (1 << 16)  /*  */

/* =========================================================================
 * Array-indexed register access macros
 * These provide computed register addresses for queue-based registers
 * ========================================================================= */

/* GWDCC - Descriptor Chain Configuration (64 queues, 4-byte stride from 0x400) */
#define R_GWCA_GWDCC(i)       (R_GWCA_BASE + 0x00000400 + ((i) * 4))

/* GWDCBAC - Descriptor Chain Base Address Configuration
 * For RA8P1, descriptors share a global base address configuration.
 * Individual queues use GWDCC for configuration.
 * Use GWDCBAC0/1 for upper/lower 64-bit base address.
 */

/* Common GWDCC bit definitions (same for all queues) */
#define R_GWCA_GWDCC_SM_MASK            0x3
#define R_GWCA_GWDCC_SM_SHIFT           (0)
#define R_GWCA_GWDCC_EDE                (1 << 8)   /* Entry Data Enable */
#define R_GWCA_GWDCC_ETS                (1 << 9)   /* Enable Timestamp */
#define R_GWCA_GWDCC_SL                 (1 << 10)  /* Security Level */
#define R_GWCA_GWDCC_DQT                (1 << 11)  /* Descriptor Queue Type: 0=TX, 1=RX */
#define R_GWCA_GWDCC_DCP_SHIFT          (16)
#define R_GWCA_GWDCC_DCP_MASK           0x70000
#define R_GWCA_GWDCC_BALR               (1 << 24)  /* Base Address Low Register valid */
#define R_GWCA_GWDCC_OSID_SHIFT         (28)
#define R_GWCA_GWDCC_OSID_MASK          0x70000000

/* Maximum number of channels */

#define GWCA_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GWCA_H */
