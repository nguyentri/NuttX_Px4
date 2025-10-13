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

/* Channel stride for multi-channel peripherals */
#define R_GWCA_CH_STRIDE    0x00000004
#define R_GWCA_CH_BASE(ch)   (R_GWCA_BASE + ((uint32_t)(ch) * R_GWCA_CH_STRIDE))

/* GWCA Register Offsets */

#define R_GWCA_GWMC_OFFSET     0x00000000  /* Mode Configuration Register */
#define R_GWCA_GWMS_OFFSET     0x00000004  /* Mode Status Register */
#define R_GWCA_GWIRC_OFFSET     0x00000010  /* IPV Remapping Configuration Register [802.1Q] */
#define R_GWCA_GWRDQSC_OFFSET     0x00000014  /* RX Descriptor Queue Security Configuration Register */
#define R_GWCA_GWRDQC_OFFSET     0x00000018  /* RX Descriptor Queue Control Register */
#define R_GWCA_GWRDQAC_OFFSET     0x0000001c  /* RX Descriptor Queue Arbitration Control Register */
#define R_GWCA_GWRGC_OFFSET     0x00000020  /* RX General Configuration Register */
/* GWRMFSC%s Registers (0-7) */
#define R_GWCA_GWRMFSC0_OFFSET     0x00000040  /* Reception Maximum Frame Size Configuration Register 0 */
#define R_GWCA_GWRMFSC1_OFFSET     0x00000044  /* Reception Maximum Frame Size Configuration Register 1 */
#define R_GWCA_GWRMFSC2_OFFSET     0x00000048  /* Reception Maximum Frame Size Configuration Register 2 */
#define R_GWCA_GWRMFSC3_OFFSET     0x0000004c  /* Reception Maximum Frame Size Configuration Register 3 */
#define R_GWCA_GWRMFSC4_OFFSET     0x00000050  /* Reception Maximum Frame Size Configuration Register 4 */
#define R_GWCA_GWRMFSC5_OFFSET     0x00000054  /* Reception Maximum Frame Size Configuration Register 5 */
#define R_GWCA_GWRMFSC6_OFFSET     0x00000058  /* Reception Maximum Frame Size Configuration Register 6 */
#define R_GWCA_GWRMFSC7_OFFSET     0x0000005c  /* Reception Maximum Frame Size Configuration Register 7 */
/* GWRDQDC%s Registers (0-7) */
#define R_GWCA_GWRDQDC0_OFFSET     0x00000060  /* Reception Descriptor Queue 0 Depth Configuration Register */
#define R_GWCA_GWRDQDC1_OFFSET     0x00000064  /* Reception Descriptor Queue 1 Depth Configuration Register */
#define R_GWCA_GWRDQDC2_OFFSET     0x00000068  /* Reception Descriptor Queue 2 Depth Configuration Register */
#define R_GWCA_GWRDQDC3_OFFSET     0x0000006c  /* Reception Descriptor Queue 3 Depth Configuration Register */
#define R_GWCA_GWRDQDC4_OFFSET     0x00000070  /* Reception Descriptor Queue 4 Depth Configuration Register */
#define R_GWCA_GWRDQDC5_OFFSET     0x00000074  /* Reception Descriptor Queue 5 Depth Configuration Register */
#define R_GWCA_GWRDQDC6_OFFSET     0x00000078  /* Reception Descriptor Queue 6 Depth Configuration Register */
#define R_GWCA_GWRDQDC7_OFFSET     0x0000007c  /* Reception Descriptor Queue 7 Depth Configuration Register */
/* GWRDQM%s Registers (0-7) */
#define R_GWCA_GWRDQM0_OFFSET     0x00000080  /* RX Descriptor Queue 0 Monitoring Register */
#define R_GWCA_GWRDQM1_OFFSET     0x00000084  /* RX Descriptor Queue 1 Monitoring Register */
#define R_GWCA_GWRDQM2_OFFSET     0x00000088  /* RX Descriptor Queue 2 Monitoring Register */
#define R_GWCA_GWRDQM3_OFFSET     0x0000008c  /* RX Descriptor Queue 3 Monitoring Register */
#define R_GWCA_GWRDQM4_OFFSET     0x00000090  /* RX Descriptor Queue 4 Monitoring Register */
#define R_GWCA_GWRDQM5_OFFSET     0x00000094  /* RX Descriptor Queue 5 Monitoring Register */
#define R_GWCA_GWRDQM6_OFFSET     0x00000098  /* RX Descriptor Queue 6 Monitoring Register */
#define R_GWCA_GWRDQM7_OFFSET     0x0000009c  /* RX Descriptor Queue 7 Monitoring Register */
/* GWRDQMLM%s Registers (0-7) */
#define R_GWCA_GWRDQMLM0_OFFSET     0x000000a0  /* RX Descriptor Queue 0 Max Level Monitoring Register */
#define R_GWCA_GWRDQMLM1_OFFSET     0x000000a4  /* RX Descriptor Queue 1 Max Level Monitoring Register */
#define R_GWCA_GWRDQMLM2_OFFSET     0x000000a8  /* RX Descriptor Queue 2 Max Level Monitoring Register */
#define R_GWCA_GWRDQMLM3_OFFSET     0x000000ac  /* RX Descriptor Queue 3 Max Level Monitoring Register */
#define R_GWCA_GWRDQMLM4_OFFSET     0x000000b0  /* RX Descriptor Queue 4 Max Level Monitoring Register */
#define R_GWCA_GWRDQMLM5_OFFSET     0x000000b4  /* RX Descriptor Queue 5 Max Level Monitoring Register */
#define R_GWCA_GWRDQMLM6_OFFSET     0x000000b8  /* RX Descriptor Queue 6 Max Level Monitoring Register */
#define R_GWCA_GWRDQMLM7_OFFSET     0x000000bc  /* RX Descriptor Queue 7 Max Level Monitoring Register */
#define R_GWCA_GWMTIRM_OFFSET     0x00000100  /* Multicast Table Initialization Register Monitoring Register */
#define R_GWCA_GWMSTLS_OFFSET     0x00000104  /* Multicast Table Learning Setting Register */
#define R_GWCA_GWMSTLR_OFFSET     0x00000108  /* Multicast Table Learning Result Register */
#define R_GWCA_GWMSTSS_OFFSET     0x0000010c  /* Multicast Table Searching Setting Register */
#define R_GWCA_GWMSTSR_OFFSET     0x00000110  /* Multicast Table Searching Result Register */
#define R_GWCA_GWMAC0_OFFSET     0x00000120  /* MAC Address Configuration Register 0 */
#define R_GWCA_GWMAC1_OFFSET     0x00000124  /* MAC Address Configuration Register 1 */
#define R_GWCA_GWVCC_OFFSET     0x00000130  /* VLAN Control Configuration Register */
#define R_GWCA_GWVTC_OFFSET     0x00000134  /* VLAN TAG Configuration Register */
#define R_GWCA_GWTTFC_OFFSET     0x00000138  /* Transmission TAG Filtering Configuration Register */
/* GWTDCAC%s0 Registers (0-1) */
#define R_GWCA_GWTDCAC00_OFFSET     0x00000140  /* Timestamp Descriptor Chain 0 Address Configuration Register 0 */
#define R_GWCA_GWTDCAC10_OFFSET     0x00000148  /* Timestamp Descriptor Chain 1 Address Configuration Register 0 */
/* GWTDCAC%s1 Registers (0-1) */
#define R_GWCA_GWTDCAC01_OFFSET     0x00000144  /* Timestamp Descriptor Chain 0 Address Configuration Register 1 */
#define R_GWCA_GWTDCAC11_OFFSET     0x0000014c  /* Timestamp Descriptor Chain 1 Address Configuration Register 1 */
/* GWTSDCC%s Registers (0-1) */
#define R_GWCA_GWTSDCC0_OFFSET     0x00000160  /* Timestamp Descriptor Chain 0 Configuration Register */
#define R_GWCA_GWTSDCC1_OFFSET     0x00000164  /* Timestamp Descriptor Chain 1 Configuration Register */
#define R_GWCA_GWTSNM_OFFSET     0x00000180  /* Timestamp Number Monitoring Register */
#define R_GWCA_GWTSMNM_OFFSET     0x00000184  /* Timestamp Maximum Number Monitoring Register */
#define R_GWCA_GWAC_OFFSET     0x00000190  /* AXI Control Register */
#define R_GWCA_GWDCBAC0_OFFSET     0x00000194  /* Descriptor Chain Base Address Configuration Register 0 */
#define R_GWCA_GWDCBAC1_OFFSET     0x00000198  /* Descriptor Chain Base Address Configuration Register 1 */
#define R_GWCA_GWMDNC_OFFSET     0x000001a0  /* Maximum Descriptor Number Configuration Register */
#define R_GWCA_GWTRC0_OFFSET     0x00000200  /* Transmission Request Configuration Register  */
#define R_GWCA_GWTRC1_OFFSET     0x00000204  /* Transmission Request Configuration Register  */
#define R_GWCA_GWTPCP_OFFSET     0x00000300  /* Transmission Pause Configuration Register p (p = 0 to 1) */
#define R_GWCA_GWARIRM_OFFSET     0x00000380  /* AXI RAM Initialization Register Monitoring Register */
/* GWDCC%s Registers (0-63) */
#define R_GWCA_GWDCC00_OFFSET     0x00000400  /* Descriptor Chain 00 Configuration Register */
#define R_GWCA_GWDCC01_OFFSET     0x00000404  /* Descriptor Chain 01 Configuration Register */
#define R_GWCA_GWDCC02_OFFSET     0x00000408  /* Descriptor Chain 02 Configuration Register */
#define R_GWCA_GWDCC03_OFFSET     0x0000040c  /* Descriptor Chain 03 Configuration Register */
#define R_GWCA_GWDCC04_OFFSET     0x00000410  /* Descriptor Chain 04 Configuration Register */
#define R_GWCA_GWDCC05_OFFSET     0x00000414  /* Descriptor Chain 05 Configuration Register */
#define R_GWCA_GWDCC06_OFFSET     0x00000418  /* Descriptor Chain 06 Configuration Register */
#define R_GWCA_GWDCC07_OFFSET     0x0000041c  /* Descriptor Chain 07 Configuration Register */
#define R_GWCA_GWDCC08_OFFSET     0x00000420  /* Descriptor Chain 08 Configuration Register */
#define R_GWCA_GWDCC09_OFFSET     0x00000424  /* Descriptor Chain 09 Configuration Register */
#define R_GWCA_GWDCC10_OFFSET     0x00000428  /* Descriptor Chain 10 Configuration Register */
#define R_GWCA_GWDCC11_OFFSET     0x0000042c  /* Descriptor Chain 11 Configuration Register */
#define R_GWCA_GWDCC12_OFFSET     0x00000430  /* Descriptor Chain 12 Configuration Register */
#define R_GWCA_GWDCC13_OFFSET     0x00000434  /* Descriptor Chain 13 Configuration Register */
#define R_GWCA_GWDCC14_OFFSET     0x00000438  /* Descriptor Chain 14 Configuration Register */
#define R_GWCA_GWDCC15_OFFSET     0x0000043c  /* Descriptor Chain 15 Configuration Register */
#define R_GWCA_GWDCC16_OFFSET     0x00000440  /* Descriptor Chain 16 Configuration Register */
#define R_GWCA_GWDCC17_OFFSET     0x00000444  /* Descriptor Chain 17 Configuration Register */
#define R_GWCA_GWDCC18_OFFSET     0x00000448  /* Descriptor Chain 18 Configuration Register */
#define R_GWCA_GWDCC19_OFFSET     0x0000044c  /* Descriptor Chain 19 Configuration Register */
#define R_GWCA_GWDCC20_OFFSET     0x00000450  /* Descriptor Chain 20 Configuration Register */
#define R_GWCA_GWDCC21_OFFSET     0x00000454  /* Descriptor Chain 21 Configuration Register */
#define R_GWCA_GWDCC22_OFFSET     0x00000458  /* Descriptor Chain 22 Configuration Register */
#define R_GWCA_GWDCC23_OFFSET     0x0000045c  /* Descriptor Chain 23 Configuration Register */
#define R_GWCA_GWDCC24_OFFSET     0x00000460  /* Descriptor Chain 24 Configuration Register */
#define R_GWCA_GWDCC25_OFFSET     0x00000464  /* Descriptor Chain 25 Configuration Register */
#define R_GWCA_GWDCC26_OFFSET     0x00000468  /* Descriptor Chain 26 Configuration Register */
#define R_GWCA_GWDCC27_OFFSET     0x0000046c  /* Descriptor Chain 27 Configuration Register */
#define R_GWCA_GWDCC28_OFFSET     0x00000470  /* Descriptor Chain 28 Configuration Register */
#define R_GWCA_GWDCC29_OFFSET     0x00000474  /* Descriptor Chain 29 Configuration Register */
#define R_GWCA_GWDCC30_OFFSET     0x00000478  /* Descriptor Chain 30 Configuration Register */
#define R_GWCA_GWDCC31_OFFSET     0x0000047c  /* Descriptor Chain 31 Configuration Register */
#define R_GWCA_GWDCC32_OFFSET     0x00000480  /* Descriptor Chain 32 Configuration Register */
#define R_GWCA_GWDCC33_OFFSET     0x00000484  /* Descriptor Chain 33 Configuration Register */
#define R_GWCA_GWDCC34_OFFSET     0x00000488  /* Descriptor Chain 34 Configuration Register */
#define R_GWCA_GWDCC35_OFFSET     0x0000048c  /* Descriptor Chain 35 Configuration Register */
#define R_GWCA_GWDCC36_OFFSET     0x00000490  /* Descriptor Chain 36 Configuration Register */
#define R_GWCA_GWDCC37_OFFSET     0x00000494  /* Descriptor Chain 37 Configuration Register */
#define R_GWCA_GWDCC38_OFFSET     0x00000498  /* Descriptor Chain 38 Configuration Register */
#define R_GWCA_GWDCC39_OFFSET     0x0000049c  /* Descriptor Chain 39 Configuration Register */
#define R_GWCA_GWDCC40_OFFSET     0x000004a0  /* Descriptor Chain 40 Configuration Register */
#define R_GWCA_GWDCC41_OFFSET     0x000004a4  /* Descriptor Chain 41 Configuration Register */
#define R_GWCA_GWDCC42_OFFSET     0x000004a8  /* Descriptor Chain 42 Configuration Register */
#define R_GWCA_GWDCC43_OFFSET     0x000004ac  /* Descriptor Chain 43 Configuration Register */
#define R_GWCA_GWDCC44_OFFSET     0x000004b0  /* Descriptor Chain 44 Configuration Register */
#define R_GWCA_GWDCC45_OFFSET     0x000004b4  /* Descriptor Chain 45 Configuration Register */
#define R_GWCA_GWDCC46_OFFSET     0x000004b8  /* Descriptor Chain 46 Configuration Register */
#define R_GWCA_GWDCC47_OFFSET     0x000004bc  /* Descriptor Chain 47 Configuration Register */
#define R_GWCA_GWDCC48_OFFSET     0x000004c0  /* Descriptor Chain 48 Configuration Register */
#define R_GWCA_GWDCC49_OFFSET     0x000004c4  /* Descriptor Chain 49 Configuration Register */
#define R_GWCA_GWDCC50_OFFSET     0x000004c8  /* Descriptor Chain 50 Configuration Register */
#define R_GWCA_GWDCC51_OFFSET     0x000004cc  /* Descriptor Chain 51 Configuration Register */
#define R_GWCA_GWDCC52_OFFSET     0x000004d0  /* Descriptor Chain 52 Configuration Register */
#define R_GWCA_GWDCC53_OFFSET     0x000004d4  /* Descriptor Chain 53 Configuration Register */
#define R_GWCA_GWDCC54_OFFSET     0x000004d8  /* Descriptor Chain 54 Configuration Register */
#define R_GWCA_GWDCC55_OFFSET     0x000004dc  /* Descriptor Chain 55 Configuration Register */
#define R_GWCA_GWDCC56_OFFSET     0x000004e0  /* Descriptor Chain 56 Configuration Register */
#define R_GWCA_GWDCC57_OFFSET     0x000004e4  /* Descriptor Chain 57 Configuration Register */
#define R_GWCA_GWDCC58_OFFSET     0x000004e8  /* Descriptor Chain 58 Configuration Register */
#define R_GWCA_GWDCC59_OFFSET     0x000004ec  /* Descriptor Chain 59 Configuration Register */
#define R_GWCA_GWDCC60_OFFSET     0x000004f0  /* Descriptor Chain 60 Configuration Register */
#define R_GWCA_GWDCC61_OFFSET     0x000004f4  /* Descriptor Chain 61 Configuration Register */
#define R_GWCA_GWDCC62_OFFSET     0x000004f8  /* Descriptor Chain 62 Configuration Register */
#define R_GWCA_GWDCC63_OFFSET     0x000004fc  /* Descriptor Chain 63 Configuration Register */
#define R_GWCA_GWAARSS_OFFSET     0x00000800  /* AXI Address RAM Searching Setting Register */
#define R_GWCA_GWAARSR0_OFFSET     0x00000804  /* AXI Address RAM Searching Result Register 0 */
#define R_GWCA_GWAARSR1_OFFSET     0x00000808  /* AXI Address RAM Searching Result Register 1 */
/* GWIDAUAS%s Registers (0-3) */
#define R_GWCA_GWIDAUAS0_OFFSET     0x00000840  /* Incremental Data Area 0 Used Area Size Register */
#define R_GWCA_GWIDAUAS1_OFFSET     0x00000844  /* Incremental Data Area 1 Used Area Size Register */
#define R_GWCA_GWIDAUAS2_OFFSET     0x00000848  /* Incremental Data Area 2 Used Area Size Register */
#define R_GWCA_GWIDAUAS3_OFFSET     0x0000084c  /* Incremental Data Area 3 Used Area Size Register */
/* GWIDASM%s Registers (0-3) */
#define R_GWCA_GWIDASM0_OFFSET     0x00000880  /* Incremental Data Area 0 Size Monitoring Register */
#define R_GWCA_GWIDASM1_OFFSET     0x00000884  /* Incremental Data Area 1 Size Monitoring Register */
#define R_GWCA_GWIDASM2_OFFSET     0x00000888  /* Incremental Data Area 2 Size Monitoring Register */
#define R_GWCA_GWIDASM3_OFFSET     0x0000088c  /* Incremental Data Area 3 Size Monitoring Register */
/* GWIDASAM%s0 Registers (0-3) */
#define R_GWCA_GWIDASAM00_OFFSET     0x00000900  /* Incremental Data Area 0 Start Address Monitoring Register 0 */
#define R_GWCA_GWIDASAM10_OFFSET     0x00000908  /* Incremental Data Area 1 Start Address Monitoring Register 0 */
#define R_GWCA_GWIDASAM20_OFFSET     0x00000910  /* Incremental Data Area 2 Start Address Monitoring Register 0 */
#define R_GWCA_GWIDASAM30_OFFSET     0x00000918  /* Incremental Data Area 3 Start Address Monitoring Register 0 */
/* GWIDASAM%s1 Registers (0-3) */
#define R_GWCA_GWIDASAM01_OFFSET     0x00000904  /* Incremental Data Area 0 Start Address Monitoring Register 1 */
#define R_GWCA_GWIDASAM11_OFFSET     0x0000090c  /* Incremental Data Area 1 Start Address Monitoring Register 1 */
#define R_GWCA_GWIDASAM21_OFFSET     0x00000914  /* Incremental Data Area 2 Start Address Monitoring Register 1 */
#define R_GWCA_GWIDASAM31_OFFSET     0x0000091c  /* Incremental Data Area 3 Start Address Monitoring Register 1 */
/* GWIDACAM%s0 Registers (0-3) */
#define R_GWCA_GWIDACAM00_OFFSET     0x00000980  /* Incremental Data Area 0 Current Address Monitoring Register 0 */
#define R_GWCA_GWIDACAM10_OFFSET     0x00000988  /* Incremental Data Area 1 Current Address Monitoring Register 0 */
#define R_GWCA_GWIDACAM20_OFFSET     0x00000990  /* Incremental Data Area 2 Current Address Monitoring Register 0 */
#define R_GWCA_GWIDACAM30_OFFSET     0x00000998  /* Incremental Data Area 3 Current Address Monitoring Register 0 */
/* GWIDACAM%s1 Registers (0-3) */
#define R_GWCA_GWIDACAM01_OFFSET     0x00000984  /* Incremental Data Area 0 Current Address Monitoring Register 1 */
#define R_GWCA_GWIDACAM11_OFFSET     0x0000098c  /* Incremental Data Area 1 Current Address Monitoring Register 1 */
#define R_GWCA_GWIDACAM21_OFFSET     0x00000994  /* Incremental Data Area 2 Current Address Monitoring Register 1 */
#define R_GWCA_GWIDACAM31_OFFSET     0x0000099c  /* Incremental Data Area 3 Current Address Monitoring Register 1 */
#define R_GWCA_GWGRLC_OFFSET     0x00000a00  /* Global Rate Limiter Configuration Register */
#define R_GWCA_GWGRLULC_OFFSET     0x00000a04  /* Global Rate Limiter Upper Limit Configuration Register */
/* GWRLC%s Registers (0-7) */
#define R_GWCA_GWRLC0_OFFSET     0x00000a80  /* Rate Limiter 0 Configuration Register */
#define R_GWCA_GWRLC1_OFFSET     0x00000a88  /* Rate Limiter 1 Configuration Register */
#define R_GWCA_GWRLC2_OFFSET     0x00000a90  /* Rate Limiter 2 Configuration Register */
#define R_GWCA_GWRLC3_OFFSET     0x00000a98  /* Rate Limiter 3 Configuration Register */
#define R_GWCA_GWRLC4_OFFSET     0x00000aa0  /* Rate Limiter 4 Configuration Register */
#define R_GWCA_GWRLC5_OFFSET     0x00000aa8  /* Rate Limiter 5 Configuration Register */
#define R_GWCA_GWRLC6_OFFSET     0x00000ab0  /* Rate Limiter 6 Configuration Register */
#define R_GWCA_GWRLC7_OFFSET     0x00000ab8  /* Rate Limiter 7 Configuration Register */
/* GWRLULC%s Registers (0-7) */
#define R_GWCA_GWRLULC0_OFFSET     0x00000a84  /* Rate Limiter 0 Upper Limit Configuration Register */
#define R_GWCA_GWRLULC1_OFFSET     0x00000a8c  /* Rate Limiter 1 Upper Limit Configuration Register */
#define R_GWCA_GWRLULC2_OFFSET     0x00000a94  /* Rate Limiter 2 Upper Limit Configuration Register */
#define R_GWCA_GWRLULC3_OFFSET     0x00000a9c  /* Rate Limiter 3 Upper Limit Configuration Register */
#define R_GWCA_GWRLULC4_OFFSET     0x00000aa4  /* Rate Limiter 4 Upper Limit Configuration Register */
#define R_GWCA_GWRLULC5_OFFSET     0x00000aac  /* Rate Limiter 5 Upper Limit Configuration Register */
#define R_GWCA_GWRLULC6_OFFSET     0x00000ab4  /* Rate Limiter 6 Upper Limit Configuration Register */
#define R_GWCA_GWRLULC7_OFFSET     0x00000abc  /* Rate Limiter 7 Upper Limit Configuration Register */
#define R_GWCA_GWIDPC_OFFSET     0x00000b80  /* Interrupt Delay Prescaler Configuration Register */
#define R_GWCA_GWRDCN_OFFSET     0x00001000  /* Received Data Counter Register */
#define R_GWCA_GWTDCN_OFFSET     0x00001004  /* Transmitted Data Counter Register */
#define R_GWCA_GWTSCN_OFFSET     0x00001008  /* Timestamp Counter Register */
#define R_GWCA_GWTSOVFECN_OFFSET     0x0000100c  /* Timestamp Overflow Error Counter Register */
#define R_GWCA_GWUSMFSECN_OFFSET     0x00001010  /* Under Minimum Frame Size Error Counter Register */
#define R_GWCA_GWTFECN_OFFSET     0x00001014  /* TAG Filtering Error Counter Register */
#define R_GWCA_GWSEQECN_OFFSET     0x00001018  /* Sequence Error Counter Register */
#define R_GWCA_GWTXDNECN_OFFSET     0x00001020  /* TX Descriptor Number Error Counter Register */
#define R_GWCA_GWFSECN_OFFSET     0x00001024  /* Frame Size Error Counter Register */
#define R_GWCA_GWTDFECN_OFFSET     0x00001028  /* Timestamp Descriptor Full Error Counter Register */
#define R_GWCA_GWTSDNECN_OFFSET     0x0000102c  /* Timestamp Descriptor Number Error Counter Register */
#define R_GWCA_GWDQOECN_OFFSET     0x00001030  /* Descriptor Queue Overflow Error Counter Register */
#define R_GWCA_GWDQSECN_OFFSET     0x00001034  /* Descriptor Queue Security Error Counter Register */
#define R_GWCA_GWDFECN_OFFSET     0x00001038  /* Descriptor Full Error Counter Register */
#define R_GWCA_GWDSECN_OFFSET     0x0000103c  /* Descriptor Security Error Counter Register */
#define R_GWCA_GWDSZECN_OFFSET     0x00001040  /* Data Size Error Counter Register */
#define R_GWCA_GWDCTECN_OFFSET     0x00001044  /* Descriptor Chain Type Error Counter Register */
#define R_GWCA_GWRXDNECN_OFFSET     0x00001048  /* RX Descriptor Number Error Counter Register */
#define R_GWCA_GWDIS0_OFFSET     0x00001100  /* Data Interrupt Status Register  */
#define R_GWCA_GWDIE0_OFFSET     0x00001104  /* Data Interrupt Enable Register  */
#define R_GWCA_GWDID0_OFFSET     0x00001108  /* Data Interrupt Disable Register  */
#define R_GWCA_GWDIDS0_OFFSET     0x0000110c  /* Data Interrupt Delayed Status Register  */
#define R_GWCA_GWDIS1_OFFSET     0x00001110  /* Data Interrupt Status Register  */
#define R_GWCA_GWDIE1_OFFSET     0x00001114  /* Data Interrupt Enable Register  */
#define R_GWCA_GWDID1_OFFSET     0x00001118  /* Data Interrupt Disable Register  */
#define R_GWCA_GWDIDS1_OFFSET     0x0000111c  /* Data Interrupt Delayed Status Register  */
#define R_GWCA_GWTSDIS_OFFSET     0x00001180  /* Timestamp Data Interrupt Status Register */
#define R_GWCA_GWTSDIE_OFFSET     0x00001184  /* Timestamp Data Interrupt Enable Register */
#define R_GWCA_GWTSDID_OFFSET     0x00001188  /* Timestamp Data Interrupt Disable Register */
#define R_GWCA_GWEIS0_OFFSET     0x00001190  /* Error Interrupt Status Register 0 */
#define R_GWCA_GWEIE0_OFFSET     0x00001194  /* Error Interrupt Enable Register 0 */
#define R_GWCA_GWEID0_OFFSET     0x00001198  /* Error Interrupt Disable Register 0 */
#define R_GWCA_GWEIS1_OFFSET     0x000011a0  /* Error Interrupt Status Register 1 */
#define R_GWCA_GWEIE1_OFFSET     0x000011a4  /* Error Interrupt Enable Register 1 */
#define R_GWCA_GWEID1_OFFSET     0x000011a8  /* Error Interrupt Disable Register 1 */
#define R_GWCA_GWEIS20_OFFSET     0x00001200  /* Error Interrupt Status Register 2 */
#define R_GWCA_GWEIE20_OFFSET     0x00001204  /* Error Interrupt Enable Register 2 */
#define R_GWCA_GWEID20_OFFSET     0x00001208  /* Error Interrupt Disable Register 2 */
#define R_GWCA_GWEIS21_OFFSET     0x00001210  /* Error Interrupt Status Register 2 */
#define R_GWCA_GWEIE21_OFFSET     0x00001214  /* Error Interrupt Enable Register 2 */
#define R_GWCA_GWEID21_OFFSET     0x00001218  /* Error Interrupt Disable Register 2 */
#define R_GWCA_GWEIS3_OFFSET     0x00001280  /* Error Interrupt Status Register 3 */
#define R_GWCA_GWEIE3_OFFSET     0x00001284  /* Error Interrupt Enable Register 3 */
#define R_GWCA_GWEID3_OFFSET     0x00001288  /* Error Interrupt Disable Register 3 */
#define R_GWCA_GWEIS4_OFFSET     0x00001290  /* Error Interrupt Status Register 4 */
#define R_GWCA_GWEIE4_OFFSET     0x00001294  /* Error Interrupt Enable Register 4 */
#define R_GWCA_GWEID4_OFFSET     0x00001298  /* Error Interrupt Disable Register 4 */
#define R_GWCA_GWEIS5_OFFSET     0x000012a0  /* Error Interrupt Status Register 5 */
#define R_GWCA_GWEIE5_OFFSET     0x000012a4  /* Error Interrupt Enable Register 5 */
#define R_GWCA_GWEID5_OFFSET     0x000012a8  /* Error Interrupt Disable Register 5 */
/* GWIDC%s Registers (0-63) */
#define R_GWCA_GWIDC00_OFFSET     0x0000c000  /* Interrupt Delay 00 Configuration Register */
#define R_GWCA_GWIDC01_OFFSET     0x0000c004  /* Interrupt Delay 01 Configuration Register */
#define R_GWCA_GWIDC02_OFFSET     0x0000c008  /* Interrupt Delay 02 Configuration Register */
#define R_GWCA_GWIDC03_OFFSET     0x0000c00c  /* Interrupt Delay 03 Configuration Register */
#define R_GWCA_GWIDC04_OFFSET     0x0000c010  /* Interrupt Delay 04 Configuration Register */
#define R_GWCA_GWIDC05_OFFSET     0x0000c014  /* Interrupt Delay 05 Configuration Register */
#define R_GWCA_GWIDC06_OFFSET     0x0000c018  /* Interrupt Delay 06 Configuration Register */
#define R_GWCA_GWIDC07_OFFSET     0x0000c01c  /* Interrupt Delay 07 Configuration Register */
#define R_GWCA_GWIDC08_OFFSET     0x0000c020  /* Interrupt Delay 08 Configuration Register */
#define R_GWCA_GWIDC09_OFFSET     0x0000c024  /* Interrupt Delay 09 Configuration Register */
#define R_GWCA_GWIDC10_OFFSET     0x0000c028  /* Interrupt Delay 10 Configuration Register */
#define R_GWCA_GWIDC11_OFFSET     0x0000c02c  /* Interrupt Delay 11 Configuration Register */
#define R_GWCA_GWIDC12_OFFSET     0x0000c030  /* Interrupt Delay 12 Configuration Register */
#define R_GWCA_GWIDC13_OFFSET     0x0000c034  /* Interrupt Delay 13 Configuration Register */
#define R_GWCA_GWIDC14_OFFSET     0x0000c038  /* Interrupt Delay 14 Configuration Register */
#define R_GWCA_GWIDC15_OFFSET     0x0000c03c  /* Interrupt Delay 15 Configuration Register */
#define R_GWCA_GWIDC16_OFFSET     0x0000c040  /* Interrupt Delay 16 Configuration Register */
#define R_GWCA_GWIDC17_OFFSET     0x0000c044  /* Interrupt Delay 17 Configuration Register */
#define R_GWCA_GWIDC18_OFFSET     0x0000c048  /* Interrupt Delay 18 Configuration Register */
#define R_GWCA_GWIDC19_OFFSET     0x0000c04c  /* Interrupt Delay 19 Configuration Register */
#define R_GWCA_GWIDC20_OFFSET     0x0000c050  /* Interrupt Delay 20 Configuration Register */
#define R_GWCA_GWIDC21_OFFSET     0x0000c054  /* Interrupt Delay 21 Configuration Register */
#define R_GWCA_GWIDC22_OFFSET     0x0000c058  /* Interrupt Delay 22 Configuration Register */
#define R_GWCA_GWIDC23_OFFSET     0x0000c05c  /* Interrupt Delay 23 Configuration Register */
#define R_GWCA_GWIDC24_OFFSET     0x0000c060  /* Interrupt Delay 24 Configuration Register */
#define R_GWCA_GWIDC25_OFFSET     0x0000c064  /* Interrupt Delay 25 Configuration Register */
#define R_GWCA_GWIDC26_OFFSET     0x0000c068  /* Interrupt Delay 26 Configuration Register */
#define R_GWCA_GWIDC27_OFFSET     0x0000c06c  /* Interrupt Delay 27 Configuration Register */
#define R_GWCA_GWIDC28_OFFSET     0x0000c070  /* Interrupt Delay 28 Configuration Register */
#define R_GWCA_GWIDC29_OFFSET     0x0000c074  /* Interrupt Delay 29 Configuration Register */
#define R_GWCA_GWIDC30_OFFSET     0x0000c078  /* Interrupt Delay 30 Configuration Register */
#define R_GWCA_GWIDC31_OFFSET     0x0000c07c  /* Interrupt Delay 31 Configuration Register */
#define R_GWCA_GWIDC32_OFFSET     0x0000c080  /* Interrupt Delay 32 Configuration Register */
#define R_GWCA_GWIDC33_OFFSET     0x0000c084  /* Interrupt Delay 33 Configuration Register */
#define R_GWCA_GWIDC34_OFFSET     0x0000c088  /* Interrupt Delay 34 Configuration Register */
#define R_GWCA_GWIDC35_OFFSET     0x0000c08c  /* Interrupt Delay 35 Configuration Register */
#define R_GWCA_GWIDC36_OFFSET     0x0000c090  /* Interrupt Delay 36 Configuration Register */
#define R_GWCA_GWIDC37_OFFSET     0x0000c094  /* Interrupt Delay 37 Configuration Register */
#define R_GWCA_GWIDC38_OFFSET     0x0000c098  /* Interrupt Delay 38 Configuration Register */
#define R_GWCA_GWIDC39_OFFSET     0x0000c09c  /* Interrupt Delay 39 Configuration Register */
#define R_GWCA_GWIDC40_OFFSET     0x0000c0a0  /* Interrupt Delay 40 Configuration Register */
#define R_GWCA_GWIDC41_OFFSET     0x0000c0a4  /* Interrupt Delay 41 Configuration Register */
#define R_GWCA_GWIDC42_OFFSET     0x0000c0a8  /* Interrupt Delay 42 Configuration Register */
#define R_GWCA_GWIDC43_OFFSET     0x0000c0ac  /* Interrupt Delay 43 Configuration Register */
#define R_GWCA_GWIDC44_OFFSET     0x0000c0b0  /* Interrupt Delay 44 Configuration Register */
#define R_GWCA_GWIDC45_OFFSET     0x0000c0b4  /* Interrupt Delay 45 Configuration Register */
#define R_GWCA_GWIDC46_OFFSET     0x0000c0b8  /* Interrupt Delay 46 Configuration Register */
#define R_GWCA_GWIDC47_OFFSET     0x0000c0bc  /* Interrupt Delay 47 Configuration Register */
#define R_GWCA_GWIDC48_OFFSET     0x0000c0c0  /* Interrupt Delay 48 Configuration Register */
#define R_GWCA_GWIDC49_OFFSET     0x0000c0c4  /* Interrupt Delay 49 Configuration Register */
#define R_GWCA_GWIDC50_OFFSET     0x0000c0c8  /* Interrupt Delay 50 Configuration Register */
#define R_GWCA_GWIDC51_OFFSET     0x0000c0cc  /* Interrupt Delay 51 Configuration Register */
#define R_GWCA_GWIDC52_OFFSET     0x0000c0d0  /* Interrupt Delay 52 Configuration Register */
#define R_GWCA_GWIDC53_OFFSET     0x0000c0d4  /* Interrupt Delay 53 Configuration Register */
#define R_GWCA_GWIDC54_OFFSET     0x0000c0d8  /* Interrupt Delay 54 Configuration Register */
#define R_GWCA_GWIDC55_OFFSET     0x0000c0dc  /* Interrupt Delay 55 Configuration Register */
#define R_GWCA_GWIDC56_OFFSET     0x0000c0e0  /* Interrupt Delay 56 Configuration Register */
#define R_GWCA_GWIDC57_OFFSET     0x0000c0e4  /* Interrupt Delay 57 Configuration Register */
#define R_GWCA_GWIDC58_OFFSET     0x0000c0e8  /* Interrupt Delay 58 Configuration Register */
#define R_GWCA_GWIDC59_OFFSET     0x0000c0ec  /* Interrupt Delay 59 Configuration Register */
#define R_GWCA_GWIDC60_OFFSET     0x0000c0f0  /* Interrupt Delay 60 Configuration Register */
#define R_GWCA_GWIDC61_OFFSET     0x0000c0f4  /* Interrupt Delay 61 Configuration Register */
#define R_GWCA_GWIDC62_OFFSET     0x0000c0f8  /* Interrupt Delay 62 Configuration Register */
#define R_GWCA_GWIDC63_OFFSET     0x0000c0fc  /* Interrupt Delay 63 Configuration Register */

/* GWCA Register Addresses */

#define R_GWCA_GWMC                 (R_GWCA_BASE + R_GWCA_GWMC_OFFSET)
#define R_GWCA_GWMS                 (R_GWCA_BASE + R_GWCA_GWMS_OFFSET)
#define R_GWCA_GWIRC                 (R_GWCA_BASE + R_GWCA_GWIRC_OFFSET)
#define R_GWCA_GWRDQSC                 (R_GWCA_BASE + R_GWCA_GWRDQSC_OFFSET)
#define R_GWCA_GWRDQC                 (R_GWCA_BASE + R_GWCA_GWRDQC_OFFSET)
#define R_GWCA_GWRDQAC                 (R_GWCA_BASE + R_GWCA_GWRDQAC_OFFSET)
#define R_GWCA_GWRGC                 (R_GWCA_BASE + R_GWCA_GWRGC_OFFSET)
#define R_GWCA_GWRMFSC0                 (R_GWCA_BASE + R_GWCA_GWRMFSC0_OFFSET)
#define R_GWCA_GWRMFSC1                 (R_GWCA_BASE + R_GWCA_GWRMFSC1_OFFSET)
#define R_GWCA_GWRMFSC2                 (R_GWCA_BASE + R_GWCA_GWRMFSC2_OFFSET)
#define R_GWCA_GWRMFSC3                 (R_GWCA_BASE + R_GWCA_GWRMFSC3_OFFSET)
#define R_GWCA_GWRMFSC4                 (R_GWCA_BASE + R_GWCA_GWRMFSC4_OFFSET)
#define R_GWCA_GWRMFSC5                 (R_GWCA_BASE + R_GWCA_GWRMFSC5_OFFSET)
#define R_GWCA_GWRMFSC6                 (R_GWCA_BASE + R_GWCA_GWRMFSC6_OFFSET)
#define R_GWCA_GWRMFSC7                 (R_GWCA_BASE + R_GWCA_GWRMFSC7_OFFSET)
#define R_GWCA_GWRDQDC0                 (R_GWCA_BASE + R_GWCA_GWRDQDC0_OFFSET)
#define R_GWCA_GWRDQDC1                 (R_GWCA_BASE + R_GWCA_GWRDQDC1_OFFSET)
#define R_GWCA_GWRDQDC2                 (R_GWCA_BASE + R_GWCA_GWRDQDC2_OFFSET)
#define R_GWCA_GWRDQDC3                 (R_GWCA_BASE + R_GWCA_GWRDQDC3_OFFSET)
#define R_GWCA_GWRDQDC4                 (R_GWCA_BASE + R_GWCA_GWRDQDC4_OFFSET)
#define R_GWCA_GWRDQDC5                 (R_GWCA_BASE + R_GWCA_GWRDQDC5_OFFSET)
#define R_GWCA_GWRDQDC6                 (R_GWCA_BASE + R_GWCA_GWRDQDC6_OFFSET)
#define R_GWCA_GWRDQDC7                 (R_GWCA_BASE + R_GWCA_GWRDQDC7_OFFSET)
#define R_GWCA_GWRDQM0                 (R_GWCA_BASE + R_GWCA_GWRDQM0_OFFSET)
#define R_GWCA_GWRDQM1                 (R_GWCA_BASE + R_GWCA_GWRDQM1_OFFSET)
#define R_GWCA_GWRDQM2                 (R_GWCA_BASE + R_GWCA_GWRDQM2_OFFSET)
#define R_GWCA_GWRDQM3                 (R_GWCA_BASE + R_GWCA_GWRDQM3_OFFSET)
#define R_GWCA_GWRDQM4                 (R_GWCA_BASE + R_GWCA_GWRDQM4_OFFSET)
#define R_GWCA_GWRDQM5                 (R_GWCA_BASE + R_GWCA_GWRDQM5_OFFSET)
#define R_GWCA_GWRDQM6                 (R_GWCA_BASE + R_GWCA_GWRDQM6_OFFSET)
#define R_GWCA_GWRDQM7                 (R_GWCA_BASE + R_GWCA_GWRDQM7_OFFSET)
#define R_GWCA_GWRDQMLM0                 (R_GWCA_BASE + R_GWCA_GWRDQMLM0_OFFSET)
#define R_GWCA_GWRDQMLM1                 (R_GWCA_BASE + R_GWCA_GWRDQMLM1_OFFSET)
#define R_GWCA_GWRDQMLM2                 (R_GWCA_BASE + R_GWCA_GWRDQMLM2_OFFSET)
#define R_GWCA_GWRDQMLM3                 (R_GWCA_BASE + R_GWCA_GWRDQMLM3_OFFSET)
#define R_GWCA_GWRDQMLM4                 (R_GWCA_BASE + R_GWCA_GWRDQMLM4_OFFSET)
#define R_GWCA_GWRDQMLM5                 (R_GWCA_BASE + R_GWCA_GWRDQMLM5_OFFSET)
#define R_GWCA_GWRDQMLM6                 (R_GWCA_BASE + R_GWCA_GWRDQMLM6_OFFSET)
#define R_GWCA_GWRDQMLM7                 (R_GWCA_BASE + R_GWCA_GWRDQMLM7_OFFSET)
#define R_GWCA_GWMTIRM                 (R_GWCA_BASE + R_GWCA_GWMTIRM_OFFSET)
#define R_GWCA_GWMSTLS                 (R_GWCA_BASE + R_GWCA_GWMSTLS_OFFSET)
#define R_GWCA_GWMSTLR                 (R_GWCA_BASE + R_GWCA_GWMSTLR_OFFSET)
#define R_GWCA_GWMSTSS                 (R_GWCA_BASE + R_GWCA_GWMSTSS_OFFSET)
#define R_GWCA_GWMSTSR                 (R_GWCA_BASE + R_GWCA_GWMSTSR_OFFSET)
#define R_GWCA_GWMAC0                 (R_GWCA_BASE + R_GWCA_GWMAC0_OFFSET)
#define R_GWCA_GWMAC1                 (R_GWCA_BASE + R_GWCA_GWMAC1_OFFSET)
#define R_GWCA_GWVCC                 (R_GWCA_BASE + R_GWCA_GWVCC_OFFSET)
#define R_GWCA_GWVTC                 (R_GWCA_BASE + R_GWCA_GWVTC_OFFSET)
#define R_GWCA_GWTTFC                 (R_GWCA_BASE + R_GWCA_GWTTFC_OFFSET)
#define R_GWCA_GWTDCAC00                 (R_GWCA_BASE + R_GWCA_GWTDCAC00_OFFSET)
#define R_GWCA_GWTDCAC10                 (R_GWCA_BASE + R_GWCA_GWTDCAC10_OFFSET)
#define R_GWCA_GWTDCAC01                 (R_GWCA_BASE + R_GWCA_GWTDCAC01_OFFSET)
#define R_GWCA_GWTDCAC11                 (R_GWCA_BASE + R_GWCA_GWTDCAC11_OFFSET)
#define R_GWCA_GWTSDCC0                 (R_GWCA_BASE + R_GWCA_GWTSDCC0_OFFSET)
#define R_GWCA_GWTSDCC1                 (R_GWCA_BASE + R_GWCA_GWTSDCC1_OFFSET)
#define R_GWCA_GWTSNM                 (R_GWCA_BASE + R_GWCA_GWTSNM_OFFSET)
#define R_GWCA_GWTSMNM                 (R_GWCA_BASE + R_GWCA_GWTSMNM_OFFSET)
#define R_GWCA_GWAC                 (R_GWCA_BASE + R_GWCA_GWAC_OFFSET)
#define R_GWCA_GWDCBAC0                 (R_GWCA_BASE + R_GWCA_GWDCBAC0_OFFSET)
#define R_GWCA_GWDCBAC1                 (R_GWCA_BASE + R_GWCA_GWDCBAC1_OFFSET)
#define R_GWCA_GWMDNC                 (R_GWCA_BASE + R_GWCA_GWMDNC_OFFSET)
#define R_GWCA_GWTRC0                 (R_GWCA_BASE + R_GWCA_GWTRC0_OFFSET)
#define R_GWCA_GWTRC1                 (R_GWCA_BASE + R_GWCA_GWTRC1_OFFSET)
#define R_GWCA_GWTPCP                 (R_GWCA_BASE + R_GWCA_GWTPCP_OFFSET)
#define R_GWCA_GWARIRM                 (R_GWCA_BASE + R_GWCA_GWARIRM_OFFSET)
#define R_GWCA_GWDCC00                 (R_GWCA_BASE + R_GWCA_GWDCC00_OFFSET)
#define R_GWCA_GWDCC01                 (R_GWCA_BASE + R_GWCA_GWDCC01_OFFSET)
#define R_GWCA_GWDCC02                 (R_GWCA_BASE + R_GWCA_GWDCC02_OFFSET)
#define R_GWCA_GWDCC03                 (R_GWCA_BASE + R_GWCA_GWDCC03_OFFSET)
#define R_GWCA_GWDCC04                 (R_GWCA_BASE + R_GWCA_GWDCC04_OFFSET)
#define R_GWCA_GWDCC05                 (R_GWCA_BASE + R_GWCA_GWDCC05_OFFSET)
#define R_GWCA_GWDCC06                 (R_GWCA_BASE + R_GWCA_GWDCC06_OFFSET)
#define R_GWCA_GWDCC07                 (R_GWCA_BASE + R_GWCA_GWDCC07_OFFSET)
#define R_GWCA_GWDCC08                 (R_GWCA_BASE + R_GWCA_GWDCC08_OFFSET)
#define R_GWCA_GWDCC09                 (R_GWCA_BASE + R_GWCA_GWDCC09_OFFSET)
#define R_GWCA_GWDCC10                 (R_GWCA_BASE + R_GWCA_GWDCC10_OFFSET)
#define R_GWCA_GWDCC11                 (R_GWCA_BASE + R_GWCA_GWDCC11_OFFSET)
#define R_GWCA_GWDCC12                 (R_GWCA_BASE + R_GWCA_GWDCC12_OFFSET)
#define R_GWCA_GWDCC13                 (R_GWCA_BASE + R_GWCA_GWDCC13_OFFSET)
#define R_GWCA_GWDCC14                 (R_GWCA_BASE + R_GWCA_GWDCC14_OFFSET)
#define R_GWCA_GWDCC15                 (R_GWCA_BASE + R_GWCA_GWDCC15_OFFSET)
#define R_GWCA_GWDCC16                 (R_GWCA_BASE + R_GWCA_GWDCC16_OFFSET)
#define R_GWCA_GWDCC17                 (R_GWCA_BASE + R_GWCA_GWDCC17_OFFSET)
#define R_GWCA_GWDCC18                 (R_GWCA_BASE + R_GWCA_GWDCC18_OFFSET)
#define R_GWCA_GWDCC19                 (R_GWCA_BASE + R_GWCA_GWDCC19_OFFSET)
#define R_GWCA_GWDCC20                 (R_GWCA_BASE + R_GWCA_GWDCC20_OFFSET)
#define R_GWCA_GWDCC21                 (R_GWCA_BASE + R_GWCA_GWDCC21_OFFSET)
#define R_GWCA_GWDCC22                 (R_GWCA_BASE + R_GWCA_GWDCC22_OFFSET)
#define R_GWCA_GWDCC23                 (R_GWCA_BASE + R_GWCA_GWDCC23_OFFSET)
#define R_GWCA_GWDCC24                 (R_GWCA_BASE + R_GWCA_GWDCC24_OFFSET)
#define R_GWCA_GWDCC25                 (R_GWCA_BASE + R_GWCA_GWDCC25_OFFSET)
#define R_GWCA_GWDCC26                 (R_GWCA_BASE + R_GWCA_GWDCC26_OFFSET)
#define R_GWCA_GWDCC27                 (R_GWCA_BASE + R_GWCA_GWDCC27_OFFSET)
#define R_GWCA_GWDCC28                 (R_GWCA_BASE + R_GWCA_GWDCC28_OFFSET)
#define R_GWCA_GWDCC29                 (R_GWCA_BASE + R_GWCA_GWDCC29_OFFSET)
#define R_GWCA_GWDCC30                 (R_GWCA_BASE + R_GWCA_GWDCC30_OFFSET)
#define R_GWCA_GWDCC31                 (R_GWCA_BASE + R_GWCA_GWDCC31_OFFSET)
#define R_GWCA_GWDCC32                 (R_GWCA_BASE + R_GWCA_GWDCC32_OFFSET)
#define R_GWCA_GWDCC33                 (R_GWCA_BASE + R_GWCA_GWDCC33_OFFSET)
#define R_GWCA_GWDCC34                 (R_GWCA_BASE + R_GWCA_GWDCC34_OFFSET)
#define R_GWCA_GWDCC35                 (R_GWCA_BASE + R_GWCA_GWDCC35_OFFSET)
#define R_GWCA_GWDCC36                 (R_GWCA_BASE + R_GWCA_GWDCC36_OFFSET)
#define R_GWCA_GWDCC37                 (R_GWCA_BASE + R_GWCA_GWDCC37_OFFSET)
#define R_GWCA_GWDCC38                 (R_GWCA_BASE + R_GWCA_GWDCC38_OFFSET)
#define R_GWCA_GWDCC39                 (R_GWCA_BASE + R_GWCA_GWDCC39_OFFSET)
#define R_GWCA_GWDCC40                 (R_GWCA_BASE + R_GWCA_GWDCC40_OFFSET)
#define R_GWCA_GWDCC41                 (R_GWCA_BASE + R_GWCA_GWDCC41_OFFSET)
#define R_GWCA_GWDCC42                 (R_GWCA_BASE + R_GWCA_GWDCC42_OFFSET)
#define R_GWCA_GWDCC43                 (R_GWCA_BASE + R_GWCA_GWDCC43_OFFSET)
#define R_GWCA_GWDCC44                 (R_GWCA_BASE + R_GWCA_GWDCC44_OFFSET)
#define R_GWCA_GWDCC45                 (R_GWCA_BASE + R_GWCA_GWDCC45_OFFSET)
#define R_GWCA_GWDCC46                 (R_GWCA_BASE + R_GWCA_GWDCC46_OFFSET)
#define R_GWCA_GWDCC47                 (R_GWCA_BASE + R_GWCA_GWDCC47_OFFSET)
#define R_GWCA_GWDCC48                 (R_GWCA_BASE + R_GWCA_GWDCC48_OFFSET)
#define R_GWCA_GWDCC49                 (R_GWCA_BASE + R_GWCA_GWDCC49_OFFSET)
#define R_GWCA_GWDCC50                 (R_GWCA_BASE + R_GWCA_GWDCC50_OFFSET)
#define R_GWCA_GWDCC51                 (R_GWCA_BASE + R_GWCA_GWDCC51_OFFSET)
#define R_GWCA_GWDCC52                 (R_GWCA_BASE + R_GWCA_GWDCC52_OFFSET)
#define R_GWCA_GWDCC53                 (R_GWCA_BASE + R_GWCA_GWDCC53_OFFSET)
#define R_GWCA_GWDCC54                 (R_GWCA_BASE + R_GWCA_GWDCC54_OFFSET)
#define R_GWCA_GWDCC55                 (R_GWCA_BASE + R_GWCA_GWDCC55_OFFSET)
#define R_GWCA_GWDCC56                 (R_GWCA_BASE + R_GWCA_GWDCC56_OFFSET)
#define R_GWCA_GWDCC57                 (R_GWCA_BASE + R_GWCA_GWDCC57_OFFSET)
#define R_GWCA_GWDCC58                 (R_GWCA_BASE + R_GWCA_GWDCC58_OFFSET)
#define R_GWCA_GWDCC59                 (R_GWCA_BASE + R_GWCA_GWDCC59_OFFSET)
#define R_GWCA_GWDCC60                 (R_GWCA_BASE + R_GWCA_GWDCC60_OFFSET)
#define R_GWCA_GWDCC61                 (R_GWCA_BASE + R_GWCA_GWDCC61_OFFSET)
#define R_GWCA_GWDCC62                 (R_GWCA_BASE + R_GWCA_GWDCC62_OFFSET)
#define R_GWCA_GWDCC63                 (R_GWCA_BASE + R_GWCA_GWDCC63_OFFSET)
#define R_GWCA_GWAARSS                 (R_GWCA_BASE + R_GWCA_GWAARSS_OFFSET)
#define R_GWCA_GWAARSR0                 (R_GWCA_BASE + R_GWCA_GWAARSR0_OFFSET)
#define R_GWCA_GWAARSR1                 (R_GWCA_BASE + R_GWCA_GWAARSR1_OFFSET)
#define R_GWCA_GWIDAUAS0                 (R_GWCA_BASE + R_GWCA_GWIDAUAS0_OFFSET)
#define R_GWCA_GWIDAUAS1                 (R_GWCA_BASE + R_GWCA_GWIDAUAS1_OFFSET)
#define R_GWCA_GWIDAUAS2                 (R_GWCA_BASE + R_GWCA_GWIDAUAS2_OFFSET)
#define R_GWCA_GWIDAUAS3                 (R_GWCA_BASE + R_GWCA_GWIDAUAS3_OFFSET)
#define R_GWCA_GWIDASM0                 (R_GWCA_BASE + R_GWCA_GWIDASM0_OFFSET)
#define R_GWCA_GWIDASM1                 (R_GWCA_BASE + R_GWCA_GWIDASM1_OFFSET)
#define R_GWCA_GWIDASM2                 (R_GWCA_BASE + R_GWCA_GWIDASM2_OFFSET)
#define R_GWCA_GWIDASM3                 (R_GWCA_BASE + R_GWCA_GWIDASM3_OFFSET)
#define R_GWCA_GWIDASAM00                 (R_GWCA_BASE + R_GWCA_GWIDASAM00_OFFSET)
#define R_GWCA_GWIDASAM10                 (R_GWCA_BASE + R_GWCA_GWIDASAM10_OFFSET)
#define R_GWCA_GWIDASAM20                 (R_GWCA_BASE + R_GWCA_GWIDASAM20_OFFSET)
#define R_GWCA_GWIDASAM30                 (R_GWCA_BASE + R_GWCA_GWIDASAM30_OFFSET)
#define R_GWCA_GWIDASAM01                 (R_GWCA_BASE + R_GWCA_GWIDASAM01_OFFSET)
#define R_GWCA_GWIDASAM11                 (R_GWCA_BASE + R_GWCA_GWIDASAM11_OFFSET)
#define R_GWCA_GWIDASAM21                 (R_GWCA_BASE + R_GWCA_GWIDASAM21_OFFSET)
#define R_GWCA_GWIDASAM31                 (R_GWCA_BASE + R_GWCA_GWIDASAM31_OFFSET)
#define R_GWCA_GWIDACAM00                 (R_GWCA_BASE + R_GWCA_GWIDACAM00_OFFSET)
#define R_GWCA_GWIDACAM10                 (R_GWCA_BASE + R_GWCA_GWIDACAM10_OFFSET)
#define R_GWCA_GWIDACAM20                 (R_GWCA_BASE + R_GWCA_GWIDACAM20_OFFSET)
#define R_GWCA_GWIDACAM30                 (R_GWCA_BASE + R_GWCA_GWIDACAM30_OFFSET)
#define R_GWCA_GWIDACAM01                 (R_GWCA_BASE + R_GWCA_GWIDACAM01_OFFSET)
#define R_GWCA_GWIDACAM11                 (R_GWCA_BASE + R_GWCA_GWIDACAM11_OFFSET)
#define R_GWCA_GWIDACAM21                 (R_GWCA_BASE + R_GWCA_GWIDACAM21_OFFSET)
#define R_GWCA_GWIDACAM31                 (R_GWCA_BASE + R_GWCA_GWIDACAM31_OFFSET)
#define R_GWCA_GWGRLC                 (R_GWCA_BASE + R_GWCA_GWGRLC_OFFSET)
#define R_GWCA_GWGRLULC                 (R_GWCA_BASE + R_GWCA_GWGRLULC_OFFSET)
#define R_GWCA_GWRLC0                 (R_GWCA_BASE + R_GWCA_GWRLC0_OFFSET)
#define R_GWCA_GWRLC1                 (R_GWCA_BASE + R_GWCA_GWRLC1_OFFSET)
#define R_GWCA_GWRLC2                 (R_GWCA_BASE + R_GWCA_GWRLC2_OFFSET)
#define R_GWCA_GWRLC3                 (R_GWCA_BASE + R_GWCA_GWRLC3_OFFSET)
#define R_GWCA_GWRLC4                 (R_GWCA_BASE + R_GWCA_GWRLC4_OFFSET)
#define R_GWCA_GWRLC5                 (R_GWCA_BASE + R_GWCA_GWRLC5_OFFSET)
#define R_GWCA_GWRLC6                 (R_GWCA_BASE + R_GWCA_GWRLC6_OFFSET)
#define R_GWCA_GWRLC7                 (R_GWCA_BASE + R_GWCA_GWRLC7_OFFSET)
#define R_GWCA_GWRLULC0                 (R_GWCA_BASE + R_GWCA_GWRLULC0_OFFSET)
#define R_GWCA_GWRLULC1                 (R_GWCA_BASE + R_GWCA_GWRLULC1_OFFSET)
#define R_GWCA_GWRLULC2                 (R_GWCA_BASE + R_GWCA_GWRLULC2_OFFSET)
#define R_GWCA_GWRLULC3                 (R_GWCA_BASE + R_GWCA_GWRLULC3_OFFSET)
#define R_GWCA_GWRLULC4                 (R_GWCA_BASE + R_GWCA_GWRLULC4_OFFSET)
#define R_GWCA_GWRLULC5                 (R_GWCA_BASE + R_GWCA_GWRLULC5_OFFSET)
#define R_GWCA_GWRLULC6                 (R_GWCA_BASE + R_GWCA_GWRLULC6_OFFSET)
#define R_GWCA_GWRLULC7                 (R_GWCA_BASE + R_GWCA_GWRLULC7_OFFSET)
#define R_GWCA_GWIDPC                 (R_GWCA_BASE + R_GWCA_GWIDPC_OFFSET)
#define R_GWCA_GWRDCN                 (R_GWCA_BASE + R_GWCA_GWRDCN_OFFSET)
#define R_GWCA_GWTDCN                 (R_GWCA_BASE + R_GWCA_GWTDCN_OFFSET)
#define R_GWCA_GWTSCN                 (R_GWCA_BASE + R_GWCA_GWTSCN_OFFSET)
#define R_GWCA_GWTSOVFECN                 (R_GWCA_BASE + R_GWCA_GWTSOVFECN_OFFSET)
#define R_GWCA_GWUSMFSECN                 (R_GWCA_BASE + R_GWCA_GWUSMFSECN_OFFSET)
#define R_GWCA_GWTFECN                 (R_GWCA_BASE + R_GWCA_GWTFECN_OFFSET)
#define R_GWCA_GWSEQECN                 (R_GWCA_BASE + R_GWCA_GWSEQECN_OFFSET)
#define R_GWCA_GWTXDNECN                 (R_GWCA_BASE + R_GWCA_GWTXDNECN_OFFSET)
#define R_GWCA_GWFSECN                 (R_GWCA_BASE + R_GWCA_GWFSECN_OFFSET)
#define R_GWCA_GWTDFECN                 (R_GWCA_BASE + R_GWCA_GWTDFECN_OFFSET)
#define R_GWCA_GWTSDNECN                 (R_GWCA_BASE + R_GWCA_GWTSDNECN_OFFSET)
#define R_GWCA_GWDQOECN                 (R_GWCA_BASE + R_GWCA_GWDQOECN_OFFSET)
#define R_GWCA_GWDQSECN                 (R_GWCA_BASE + R_GWCA_GWDQSECN_OFFSET)
#define R_GWCA_GWDFECN                 (R_GWCA_BASE + R_GWCA_GWDFECN_OFFSET)
#define R_GWCA_GWDSECN                 (R_GWCA_BASE + R_GWCA_GWDSECN_OFFSET)
#define R_GWCA_GWDSZECN                 (R_GWCA_BASE + R_GWCA_GWDSZECN_OFFSET)
#define R_GWCA_GWDCTECN                 (R_GWCA_BASE + R_GWCA_GWDCTECN_OFFSET)
#define R_GWCA_GWRXDNECN                 (R_GWCA_BASE + R_GWCA_GWRXDNECN_OFFSET)
#define R_GWCA_GWDIS0                 (R_GWCA_BASE + R_GWCA_GWDIS0_OFFSET)
#define R_GWCA_GWDIE0                 (R_GWCA_BASE + R_GWCA_GWDIE0_OFFSET)
#define R_GWCA_GWDID0                 (R_GWCA_BASE + R_GWCA_GWDID0_OFFSET)
#define R_GWCA_GWDIDS0                 (R_GWCA_BASE + R_GWCA_GWDIDS0_OFFSET)
#define R_GWCA_GWDIS1                 (R_GWCA_BASE + R_GWCA_GWDIS1_OFFSET)
#define R_GWCA_GWDIE1                 (R_GWCA_BASE + R_GWCA_GWDIE1_OFFSET)
#define R_GWCA_GWDID1                 (R_GWCA_BASE + R_GWCA_GWDID1_OFFSET)
#define R_GWCA_GWDIDS1                 (R_GWCA_BASE + R_GWCA_GWDIDS1_OFFSET)
#define R_GWCA_GWTSDIS                 (R_GWCA_BASE + R_GWCA_GWTSDIS_OFFSET)
#define R_GWCA_GWTSDIE                 (R_GWCA_BASE + R_GWCA_GWTSDIE_OFFSET)
#define R_GWCA_GWTSDID                 (R_GWCA_BASE + R_GWCA_GWTSDID_OFFSET)
#define R_GWCA_GWEIS0                 (R_GWCA_BASE + R_GWCA_GWEIS0_OFFSET)
#define R_GWCA_GWEIE0                 (R_GWCA_BASE + R_GWCA_GWEIE0_OFFSET)
#define R_GWCA_GWEID0                 (R_GWCA_BASE + R_GWCA_GWEID0_OFFSET)
#define R_GWCA_GWEIS1                 (R_GWCA_BASE + R_GWCA_GWEIS1_OFFSET)
#define R_GWCA_GWEIE1                 (R_GWCA_BASE + R_GWCA_GWEIE1_OFFSET)
#define R_GWCA_GWEID1                 (R_GWCA_BASE + R_GWCA_GWEID1_OFFSET)
#define R_GWCA_GWEIS20                 (R_GWCA_BASE + R_GWCA_GWEIS20_OFFSET)
#define R_GWCA_GWEIE20                 (R_GWCA_BASE + R_GWCA_GWEIE20_OFFSET)
#define R_GWCA_GWEID20                 (R_GWCA_BASE + R_GWCA_GWEID20_OFFSET)
#define R_GWCA_GWEIS21                 (R_GWCA_BASE + R_GWCA_GWEIS21_OFFSET)
#define R_GWCA_GWEIE21                 (R_GWCA_BASE + R_GWCA_GWEIE21_OFFSET)
#define R_GWCA_GWEID21                 (R_GWCA_BASE + R_GWCA_GWEID21_OFFSET)
#define R_GWCA_GWEIS3                 (R_GWCA_BASE + R_GWCA_GWEIS3_OFFSET)
#define R_GWCA_GWEIE3                 (R_GWCA_BASE + R_GWCA_GWEIE3_OFFSET)
#define R_GWCA_GWEID3                 (R_GWCA_BASE + R_GWCA_GWEID3_OFFSET)
#define R_GWCA_GWEIS4                 (R_GWCA_BASE + R_GWCA_GWEIS4_OFFSET)
#define R_GWCA_GWEIE4                 (R_GWCA_BASE + R_GWCA_GWEIE4_OFFSET)
#define R_GWCA_GWEID4                 (R_GWCA_BASE + R_GWCA_GWEID4_OFFSET)
#define R_GWCA_GWEIS5                 (R_GWCA_BASE + R_GWCA_GWEIS5_OFFSET)
#define R_GWCA_GWEIE5                 (R_GWCA_BASE + R_GWCA_GWEIE5_OFFSET)
#define R_GWCA_GWEID5                 (R_GWCA_BASE + R_GWCA_GWEID5_OFFSET)
#define R_GWCA_GWIDC00                 (R_GWCA_BASE + R_GWCA_GWIDC00_OFFSET)
#define R_GWCA_GWIDC01                 (R_GWCA_BASE + R_GWCA_GWIDC01_OFFSET)
#define R_GWCA_GWIDC02                 (R_GWCA_BASE + R_GWCA_GWIDC02_OFFSET)
#define R_GWCA_GWIDC03                 (R_GWCA_BASE + R_GWCA_GWIDC03_OFFSET)
#define R_GWCA_GWIDC04                 (R_GWCA_BASE + R_GWCA_GWIDC04_OFFSET)
#define R_GWCA_GWIDC05                 (R_GWCA_BASE + R_GWCA_GWIDC05_OFFSET)
#define R_GWCA_GWIDC06                 (R_GWCA_BASE + R_GWCA_GWIDC06_OFFSET)
#define R_GWCA_GWIDC07                 (R_GWCA_BASE + R_GWCA_GWIDC07_OFFSET)
#define R_GWCA_GWIDC08                 (R_GWCA_BASE + R_GWCA_GWIDC08_OFFSET)
#define R_GWCA_GWIDC09                 (R_GWCA_BASE + R_GWCA_GWIDC09_OFFSET)
#define R_GWCA_GWIDC10                 (R_GWCA_BASE + R_GWCA_GWIDC10_OFFSET)
#define R_GWCA_GWIDC11                 (R_GWCA_BASE + R_GWCA_GWIDC11_OFFSET)
#define R_GWCA_GWIDC12                 (R_GWCA_BASE + R_GWCA_GWIDC12_OFFSET)
#define R_GWCA_GWIDC13                 (R_GWCA_BASE + R_GWCA_GWIDC13_OFFSET)
#define R_GWCA_GWIDC14                 (R_GWCA_BASE + R_GWCA_GWIDC14_OFFSET)
#define R_GWCA_GWIDC15                 (R_GWCA_BASE + R_GWCA_GWIDC15_OFFSET)
#define R_GWCA_GWIDC16                 (R_GWCA_BASE + R_GWCA_GWIDC16_OFFSET)
#define R_GWCA_GWIDC17                 (R_GWCA_BASE + R_GWCA_GWIDC17_OFFSET)
#define R_GWCA_GWIDC18                 (R_GWCA_BASE + R_GWCA_GWIDC18_OFFSET)
#define R_GWCA_GWIDC19                 (R_GWCA_BASE + R_GWCA_GWIDC19_OFFSET)
#define R_GWCA_GWIDC20                 (R_GWCA_BASE + R_GWCA_GWIDC20_OFFSET)
#define R_GWCA_GWIDC21                 (R_GWCA_BASE + R_GWCA_GWIDC21_OFFSET)
#define R_GWCA_GWIDC22                 (R_GWCA_BASE + R_GWCA_GWIDC22_OFFSET)
#define R_GWCA_GWIDC23                 (R_GWCA_BASE + R_GWCA_GWIDC23_OFFSET)
#define R_GWCA_GWIDC24                 (R_GWCA_BASE + R_GWCA_GWIDC24_OFFSET)
#define R_GWCA_GWIDC25                 (R_GWCA_BASE + R_GWCA_GWIDC25_OFFSET)
#define R_GWCA_GWIDC26                 (R_GWCA_BASE + R_GWCA_GWIDC26_OFFSET)
#define R_GWCA_GWIDC27                 (R_GWCA_BASE + R_GWCA_GWIDC27_OFFSET)
#define R_GWCA_GWIDC28                 (R_GWCA_BASE + R_GWCA_GWIDC28_OFFSET)
#define R_GWCA_GWIDC29                 (R_GWCA_BASE + R_GWCA_GWIDC29_OFFSET)
#define R_GWCA_GWIDC30                 (R_GWCA_BASE + R_GWCA_GWIDC30_OFFSET)
#define R_GWCA_GWIDC31                 (R_GWCA_BASE + R_GWCA_GWIDC31_OFFSET)
#define R_GWCA_GWIDC32                 (R_GWCA_BASE + R_GWCA_GWIDC32_OFFSET)
#define R_GWCA_GWIDC33                 (R_GWCA_BASE + R_GWCA_GWIDC33_OFFSET)
#define R_GWCA_GWIDC34                 (R_GWCA_BASE + R_GWCA_GWIDC34_OFFSET)
#define R_GWCA_GWIDC35                 (R_GWCA_BASE + R_GWCA_GWIDC35_OFFSET)
#define R_GWCA_GWIDC36                 (R_GWCA_BASE + R_GWCA_GWIDC36_OFFSET)
#define R_GWCA_GWIDC37                 (R_GWCA_BASE + R_GWCA_GWIDC37_OFFSET)
#define R_GWCA_GWIDC38                 (R_GWCA_BASE + R_GWCA_GWIDC38_OFFSET)
#define R_GWCA_GWIDC39                 (R_GWCA_BASE + R_GWCA_GWIDC39_OFFSET)
#define R_GWCA_GWIDC40                 (R_GWCA_BASE + R_GWCA_GWIDC40_OFFSET)
#define R_GWCA_GWIDC41                 (R_GWCA_BASE + R_GWCA_GWIDC41_OFFSET)
#define R_GWCA_GWIDC42                 (R_GWCA_BASE + R_GWCA_GWIDC42_OFFSET)
#define R_GWCA_GWIDC43                 (R_GWCA_BASE + R_GWCA_GWIDC43_OFFSET)
#define R_GWCA_GWIDC44                 (R_GWCA_BASE + R_GWCA_GWIDC44_OFFSET)
#define R_GWCA_GWIDC45                 (R_GWCA_BASE + R_GWCA_GWIDC45_OFFSET)
#define R_GWCA_GWIDC46                 (R_GWCA_BASE + R_GWCA_GWIDC46_OFFSET)
#define R_GWCA_GWIDC47                 (R_GWCA_BASE + R_GWCA_GWIDC47_OFFSET)
#define R_GWCA_GWIDC48                 (R_GWCA_BASE + R_GWCA_GWIDC48_OFFSET)
#define R_GWCA_GWIDC49                 (R_GWCA_BASE + R_GWCA_GWIDC49_OFFSET)
#define R_GWCA_GWIDC50                 (R_GWCA_BASE + R_GWCA_GWIDC50_OFFSET)
#define R_GWCA_GWIDC51                 (R_GWCA_BASE + R_GWCA_GWIDC51_OFFSET)
#define R_GWCA_GWIDC52                 (R_GWCA_BASE + R_GWCA_GWIDC52_OFFSET)
#define R_GWCA_GWIDC53                 (R_GWCA_BASE + R_GWCA_GWIDC53_OFFSET)
#define R_GWCA_GWIDC54                 (R_GWCA_BASE + R_GWCA_GWIDC54_OFFSET)
#define R_GWCA_GWIDC55                 (R_GWCA_BASE + R_GWCA_GWIDC55_OFFSET)
#define R_GWCA_GWIDC56                 (R_GWCA_BASE + R_GWCA_GWIDC56_OFFSET)
#define R_GWCA_GWIDC57                 (R_GWCA_BASE + R_GWCA_GWIDC57_OFFSET)
#define R_GWCA_GWIDC58                 (R_GWCA_BASE + R_GWCA_GWIDC58_OFFSET)
#define R_GWCA_GWIDC59                 (R_GWCA_BASE + R_GWCA_GWIDC59_OFFSET)
#define R_GWCA_GWIDC60                 (R_GWCA_BASE + R_GWCA_GWIDC60_OFFSET)
#define R_GWCA_GWIDC61                 (R_GWCA_BASE + R_GWCA_GWIDC61_OFFSET)
#define R_GWCA_GWIDC62                 (R_GWCA_BASE + R_GWCA_GWIDC62_OFFSET)
#define R_GWCA_GWIDC63                 (R_GWCA_BASE + R_GWCA_GWIDC63_OFFSET)

/* Register bit definitions */
/* GWMC Register bit definitions */
#define R_GWCA_GWMC_OPC_SHIFT                     (0)  /* Operating Mode Command */
#define R_GWCA_GWMC_OPC_MASK                      0x3
#  define R_GWCA_GWMC_OPC_00                              (0 << R_GWCA_GWMC_OPC_SHIFT)  /* Enter RESET mode */
#  define R_GWCA_GWMC_OPC_01                              (1 << R_GWCA_GWMC_OPC_SHIFT)  /* Enter DISABLE mode */
#  define R_GWCA_GWMC_OPC_10                              (2 << R_GWCA_GWMC_OPC_SHIFT)  /* Enter CONFIG mode */
#  define R_GWCA_GWMC_OPC_11                              (3 << R_GWCA_GWMC_OPC_SHIFT)  /* Enter OPERATION mode */

/* GWMS Register bit definitions */
#define R_GWCA_GWMS_OPS_SHIFT                     (0)  /* Operating Mode Status */
#define R_GWCA_GWMS_OPS_MASK                      0x3
#  define R_GWCA_GWMS_OPS_00                              (0 << R_GWCA_GWMS_OPS_SHIFT)  /* RESET mode */
#  define R_GWCA_GWMS_OPS_01                              (1 << R_GWCA_GWMS_OPS_SHIFT)  /* DISABLE mode */
#  define R_GWCA_GWMS_OPS_10                              (2 << R_GWCA_GWMS_OPS_SHIFT)  /* CONFIG mode */
#  define R_GWCA_GWMS_OPS_11                              (3 << R_GWCA_GWMS_OPS_SHIFT)  /* OPERATION mode */

/* GWIRC Register bit definitions */
#define R_GWCA_GWIRC_IPVR0_SHIFT                  (0)  /* IPV remapping 0 */
#define R_GWCA_GWIRC_IPVR0_MASK                   0x7

#define R_GWCA_GWIRC_IPVR1_SHIFT                  (4)  /* IPV remapping 1 */
#define R_GWCA_GWIRC_IPVR1_MASK                   0x70

#define R_GWCA_GWIRC_IPVR2_SHIFT                  (8)  /* IPV remapping 2 */
#define R_GWCA_GWIRC_IPVR2_MASK                   0x700

#define R_GWCA_GWIRC_IPVR3_SHIFT                  (12)  /* IPV remapping 3 */
#define R_GWCA_GWIRC_IPVR3_MASK                   0x7000

#define R_GWCA_GWIRC_IPVR4_SHIFT                  (16)  /* IPV remapping 4 */
#define R_GWCA_GWIRC_IPVR4_MASK                   0x70000

#define R_GWCA_GWIRC_IPVR5_SHIFT                  (20)  /* IPV remapping 5 */
#define R_GWCA_GWIRC_IPVR5_MASK                   0x700000

#define R_GWCA_GWIRC_IPVR6_SHIFT                  (24)  /* IPV remapping 6 */
#define R_GWCA_GWIRC_IPVR6_MASK                   0x7000000

#define R_GWCA_GWIRC_IPVR7_SHIFT                  (28)  /* IPV remapping 7 */
#define R_GWCA_GWIRC_IPVR7_MASK                   0x70000000

/* GWRDQSC Register bit definitions */
#define R_GWCA_GWRDQSC_RDQSL0                     (1 << 0)  /* RX Descriptor Queue i Security Level (The variable i corresponds to the bit number.) */

#define R_GWCA_GWRDQSC_RDQSL1                     (1 << 1)  /* RX Descriptor Queue i Security Level (The variable i corresponds to the bit number.) */

#define R_GWCA_GWRDQSC_RDQSL2                     (1 << 2)  /* RX Descriptor Queue i Security Level (The variable i corresponds to the bit number.) */

#define R_GWCA_GWRDQSC_RDQSL3                     (1 << 3)  /* RX Descriptor Queue i Security Level (The variable i corresponds to the bit number.) */

#define R_GWCA_GWRDQSC_RDQSL4                     (1 << 4)  /* RX Descriptor Queue i Security Level (The variable i corresponds to the bit number.) */

#define R_GWCA_GWRDQSC_RDQSL5                     (1 << 5)  /* RX Descriptor Queue i Security Level (The variable i corresponds to the bit number.) */

#define R_GWCA_GWRDQSC_RDQSL6                     (1 << 6)  /* RX Descriptor Queue i Security Level (The variable i corresponds to the bit number.) */

#define R_GWCA_GWRDQSC_RDQSL7                     (1 << 7)  /* RX Descriptor Queue i Security Level (The variable i corresponds to the bit number.) */

/* GWRDQC Register bit definitions */
#define R_GWCA_GWRDQC_RDQD0                       (1 << 0)  /* RX Descriptor Queue i Disable (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWRDQC_RDQD1                       (1 << 1)  /* RX Descriptor Queue i Disable (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWRDQC_RDQD2                       (1 << 2)  /* RX Descriptor Queue i Disable (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWRDQC_RDQD3                       (1 << 3)  /* RX Descriptor Queue i Disable (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWRDQC_RDQD4                       (1 << 4)  /* RX Descriptor Queue i Disable (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWRDQC_RDQD5                       (1 << 5)  /* RX Descriptor Queue i Disable (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWRDQC_RDQD6                       (1 << 6)  /* RX Descriptor Queue i Disable (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWRDQC_RDQD7                       (1 << 7)  /* RX Descriptor Queue i Disable (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWRDQC_RDQP0                       (1 << 16)  /* RX Descriptor Queue i Pause (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWRDQC_RDQP1                       (1 << 17)  /* RX Descriptor Queue i Pause (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWRDQC_RDQP2                       (1 << 18)  /* RX Descriptor Queue i Pause (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWRDQC_RDQP3                       (1 << 19)  /* RX Descriptor Queue i Pause (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWRDQC_RDQP4                       (1 << 20)  /* RX Descriptor Queue i Pause (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWRDQC_RDQP5                       (1 << 21)  /* RX Descriptor Queue i Pause (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWRDQC_RDQP6                       (1 << 22)  /* RX Descriptor Queue i Pause (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWRDQC_RDQP7                       (1 << 23)  /* RX Descriptor Queue i Pause (The variable i corresponds to the bit position number.) */

/* GWRDQAC Register bit definitions */
#define R_GWCA_GWRDQAC_RDQA0_SHIFT                (0)  /* RX Descriptor Queue 0 Arbitration */
#define R_GWCA_GWRDQAC_RDQA0_MASK                 0xf
#  define R_GWCA_GWRDQAC_RDQA0_0                          (0 << R_GWCA_GWRDQAC_RDQA0_SHIFT)  /* Queue i strict arbitration */

#define R_GWCA_GWRDQAC_RDQA1_SHIFT                (4)  /* RX Descriptor Queue 1 Arbitration */
#define R_GWCA_GWRDQAC_RDQA1_MASK                 0xf0
#  define R_GWCA_GWRDQAC_RDQA1_0                          (0 << R_GWCA_GWRDQAC_RDQA1_SHIFT)  /* Queue i strict arbitration */

#define R_GWCA_GWRDQAC_RDQA2_SHIFT                (8)  /* RX Descriptor Queue 2 Arbitration */
#define R_GWCA_GWRDQAC_RDQA2_MASK                 0xf00
#  define R_GWCA_GWRDQAC_RDQA2_0                          (0 << R_GWCA_GWRDQAC_RDQA2_SHIFT)  /* Queue i strict arbitration */

#define R_GWCA_GWRDQAC_RDQA3_SHIFT                (12)  /* RX Descriptor Queue 3 Arbitration */
#define R_GWCA_GWRDQAC_RDQA3_MASK                 0xf000
#  define R_GWCA_GWRDQAC_RDQA3_0                          (0 << R_GWCA_GWRDQAC_RDQA3_SHIFT)  /* Queue i strict arbitration */

#define R_GWCA_GWRDQAC_RDQA4_SHIFT                (16)  /* RX Descriptor Queue 4 Arbitration */
#define R_GWCA_GWRDQAC_RDQA4_MASK                 0xf0000
#  define R_GWCA_GWRDQAC_RDQA4_0                          (0 << R_GWCA_GWRDQAC_RDQA4_SHIFT)  /* Queue i strict arbitration */

#define R_GWCA_GWRDQAC_RDQA5_SHIFT                (20)  /* RX Descriptor Queue 5 Arbitration */
#define R_GWCA_GWRDQAC_RDQA5_MASK                 0xf00000
#  define R_GWCA_GWRDQAC_RDQA5_0                          (0 << R_GWCA_GWRDQAC_RDQA5_SHIFT)  /* Queue i strict arbitration */

#define R_GWCA_GWRDQAC_RDQA6_SHIFT                (24)  /* RX Descriptor Queue 6 Arbitration */
#define R_GWCA_GWRDQAC_RDQA6_MASK                 0xf000000
#  define R_GWCA_GWRDQAC_RDQA6_0                          (0 << R_GWCA_GWRDQAC_RDQA6_SHIFT)  /* Queue i strict arbitration */

#define R_GWCA_GWRDQAC_RDQA7_SHIFT                (28)  /* RX Descriptor Queue 7 Arbitration */
#define R_GWCA_GWRDQAC_RDQA7_MASK                 0xf0000000
#  define R_GWCA_GWRDQAC_RDQA7_0                          (0 << R_GWCA_GWRDQAC_RDQA7_SHIFT)  /* Queue i strict arbitration */

/* GWRGC Register bit definitions */
#define R_GWCA_GWRGC_RCPT                         (1 << 0)  /* Receive CRC Pass Through [802.3] */

/* GWRMFSC Register bit definitions */
#define R_GWCA_GWRMFSC_MFS_SHIFT                  (0)  /* Maximum Frame Size */
#define R_GWCA_GWRMFSC_MFS_MASK                   0xffff

/* GWRDQDC Register bit definitions */
#define R_GWCA_GWRDQDC_DQD_SHIFT                  (0)  /* Descriptor Queue Depth */
#define R_GWCA_GWRDQDC_DQD_MASK                   0x3ff

/* GWRDQM Register bit definitions */
#define R_GWCA_GWRDQM_DNQ_SHIFT                   (0)  /* Descriptor Number in Queue */
#define R_GWCA_GWRDQM_DNQ_MASK                    0x3ff

/* GWRDQMLM Register bit definitions */
#define R_GWCA_GWRDQMLM_DMLQ_SHIFT                (0)  /* Descriptor Max Level in Queue */
#define R_GWCA_GWRDQMLM_DMLQ_MASK                 0x3ff

/* GWMTIRM Register bit definitions */
#define R_GWCA_GWMTIRM_MTIOG                      (1 << 0)  /* Multicast Table Initialization Ongoing */

#define R_GWCA_GWMTIRM_MTR                        (1 << 1)  /* Multicast Table Ready */

/* GWMSTLS Register bit definitions */
#define R_GWCA_GWMSTLS_MNRCNL_SHIFT               (0)  /* Multicast Next Descriptor Chain Number Learn */
#define R_GWCA_GWMSTLS_MNRCNL_MASK                0x7f

#define R_GWCA_GWMSTLS_MNL_SHIFT                  (8)  /* Multicast Number Learn */
#define R_GWCA_GWMSTLS_MNL_MASK                   0x700

#define R_GWCA_GWMSTLS_MSENL_SHIFT                (16)  /* Multicast Setting Entry Number Learn */
#define R_GWCA_GWMSTLS_MSENL_MASK                 0x7f0000

/* GWMSTLR Register bit definitions */
#define R_GWCA_GWMSTLR_MTLF                       (1 << 0)  /* Multicast Table Learning Fail */

#define R_GWCA_GWMSTLR_MTL                        (1 << 31)  /* Multicast Table Learning */

/* GWMSTSS Register bit definitions */
#define R_GWCA_GWMSTSS_MSENS_SHIFT                (0)  /* Multicast Setting Entry Number Search */
#define R_GWCA_GWMSTSS_MSENS_MASK                 0x7f

/* GWMSTSR Register bit definitions */
#define R_GWCA_GWMSTSR_MNRCNR_SHIFT               (0)  /* Multicast Next RX Descriptor Chain Number Result */
#define R_GWCA_GWMSTSR_MNRCNR_MASK                0x7f

#define R_GWCA_GWMSTSR_MNR_SHIFT                  (8)  /* Multicast Number Result */
#define R_GWCA_GWMSTSR_MNR_MASK                   0x700

#define R_GWCA_GWMSTSR_MTS                        (1 << 31)  /* Multicast Table Searching */

#define R_GWCA_GWMSTSR_MTSEF                      (1 << 16)  /* MTSEF */

/* GWMAC0 Register bit definitions */
#define R_GWCA_GWMAC0_MAU_SHIFT                   (0)  /* MAC Address Upper Part */
#define R_GWCA_GWMAC0_MAU_MASK                    0xffff

#define R_GWCA_GWMAC0_MAUP_SHIFT                  (0)  /* MAUP */
#define R_GWCA_GWMAC0_MAUP_MASK                   0xffff

/* GWMAC1 Register bit definitions */
#define R_GWCA_GWMAC1_MAL_SHIFT                   (0)  /* MAC Address Lower Part */
#define R_GWCA_GWMAC1_MAL_MASK                    0xffffffff

#define R_GWCA_GWMAC1_MADP_SHIFT                  (0)  /* MADP */
#define R_GWCA_GWMAC1_MADP_MASK                   0xffffffff

/* GWVCC Register bit definitions */
#define R_GWCA_GWVCC_VIM                          (1 << 0)  /* VLAN Ingress Mode */

#define R_GWCA_GWVCC_VEM_SHIFT                    (16)  /* VLAN Egress Mode */
#define R_GWCA_GWVCC_VEM_MASK                     0x70000
#  define R_GWCA_GWVCC_VEM_000                            (0 << R_GWCA_GWVCC_VEM_SHIFT)  /* No VLAN mode, frames are transmitted with no VLAN. */
#  define R_GWCA_GWVCC_VEM_001                            (1 << R_GWCA_GWVCC_VEM_SHIFT)  /* C-TAG VLAN mode, frames are transmitted with ingress C-TAG if there is one stored in the Local RAM. */
#  define R_GWCA_GWVCC_VEM_010                            (2 << R_GWCA_GWVCC_VEM_SHIFT)  /* HW C-TAG VLAN mode, frames are transmitted with the C-TAG stored in local RAM. */
#  define R_GWCA_GWVCC_VEM_011                            (3 << R_GWCA_GWVCC_VEM_SHIFT)  /* SC-TAG VLAN mode, frames are transmitted with ingress C-TAG and S-TAG if they were stored in the Local RAM. */
#  define R_GWCA_GWVCC_VEM_100                            (4 << R_GWCA_GWVCC_VEM_SHIFT)  /* HW SC-TAG VLAN mode, frames are transmitted with the C-TAG and S-TAG stored in local RAM. */

#define R_GWCA_GWVCC_CTVUM                        (1 << 8)  /* CTVUM */

/* GWVTC Register bit definitions */
#define R_GWCA_GWVTC_CTV_SHIFT                    (0)  /* C-TAG VLAN */
#define R_GWCA_GWVTC_CTV_MASK                     0xfff

#define R_GWCA_GWVTC_CTP_SHIFT                    (12)  /* C-TAG PCP */
#define R_GWCA_GWVTC_CTP_MASK                     0x7000

#define R_GWCA_GWVTC_CTD                          (1 << 15)  /* C-TAG DEI */

#define R_GWCA_GWVTC_STV_SHIFT                    (16)  /* S-TAG VLAN */
#define R_GWCA_GWVTC_STV_MASK                     0xfff0000

#define R_GWCA_GWVTC_STP_SHIFT                    (28)  /* S-TAG PCP */
#define R_GWCA_GWVTC_STP_MASK                     0x70000000

#define R_GWCA_GWVTC_STD                          (1 << 31)  /* S-TAG DEI */

/* GWTTFC Register bit definitions */
#define R_GWCA_GWTTFC_NT                          (1 << 0)  /* No Tag */

#define R_GWCA_GWTTFC_RT                          (1 << 1)  /* R-TAG */

#define R_GWCA_GWTTFC_CST                         (1 << 2)  /* CoS-TAG */

#define R_GWCA_GWTTFC_CSRT                        (1 << 3)  /* CoSR-TAG */

#define R_GWCA_GWTTFC_CT                          (1 << 4)  /* C-TAG */

#define R_GWCA_GWTTFC_CRT                         (1 << 5)  /* CR-TAG */

#define R_GWCA_GWTTFC_SCT                         (1 << 6)  /* SC-TAG */

#define R_GWCA_GWTTFC_SCRT                        (1 << 7)  /* SCR-TAG */

#define R_GWCA_GWTTFC_UT                          (1 << 8)  /* Unknown TAG */

/* GWTDCAC Register bit definitions */
#define R_GWCA_GWTDCAC_TSCCAU_SHIFT               (0)  /* TS Descriptor Chain s Current Address Upper Part */
#define R_GWCA_GWTDCAC_TSCCAU_MASK                0xff

/* GWTDCAC Register bit definitions */
#define R_GWCA_GWTDCAC_TSCCAL_SHIFT               (0)  /* TS Descriptor Chain s Current Address Lower Part */
#define R_GWCA_GWTDCAC_TSCCAL_MASK                0xffffffff

/* GWTSDCC Register bit definitions */
#define R_GWCA_GWTSDCC_TE                         (1 << 0)  /* Timer Enable */

#define R_GWCA_GWTSDCC_DCS                        (1 << 1)  /* Descriptor Chain Select */

#define R_GWCA_GWTSDCC_OSID_SHIFT                 (8)  /* OS ID */
#define R_GWCA_GWTSDCC_OSID_MASK                  0x700

/* GWTSNM Register bit definitions */
#define R_GWCA_GWTSNM_TNTR_SHIFT                  (0)  /* Timestamp Number in Timestamp RAM */
#define R_GWCA_GWTSNM_TNTR_MASK                   0xff

/* GWTSMNM Register bit definitions */
#define R_GWCA_GWTSMNM_TMNTR_SHIFT                (0)  /* Timestamp Maximum Number in Timestamp RAM */
#define R_GWCA_GWTSMNM_TMNTR_MASK                 0xff

/* GWAC Register bit definitions */
#define R_GWCA_GWAC_AMPR                          (1 << 0)  /* AXI Master Pause Request */

#define R_GWCA_GWAC_AMP                           (1 << 1)  /* AXI Master Paused */

/* GWDCBAC0 Register bit definitions */
#define R_GWCA_GWDCBAC0_DCBAU_SHIFT               (0)  /* Descriptor Chain Base Address Upper Part */
#define R_GWCA_GWDCBAC0_DCBAU_MASK                0xff

#define R_GWCA_GWDCBAC0_DCBAUP_SHIFT              (0)  /* DCBAUP */
#define R_GWCA_GWDCBAC0_DCBAUP_MASK               0xff

/* GWDCBAC1 Register bit definitions */
#define R_GWCA_GWDCBAC1_DCBAL_SHIFT               (0)  /* Descriptor Chain Base Address Lower Part */
#define R_GWCA_GWDCBAC1_DCBAL_MASK                0xffffffff

#define R_GWCA_GWDCBAC1_DCBADP_SHIFT              (0)  /* DCBADP */
#define R_GWCA_GWDCBAC1_DCBADP_MASK               0xffffffff

/* GWMDNC Register bit definitions */
#define R_GWCA_GWMDNC_RXDMN_SHIFT                 (0)  /* RX Descriptor Maximum Number */
#define R_GWCA_GWMDNC_RXDMN_MASK                  0x1f

#define R_GWCA_GWMDNC_TXDMN_SHIFT                 (8)  /* TX Descriptor Maximum Number */
#define R_GWCA_GWMDNC_TXDMN_MASK                  0x1f00

#define R_GWCA_GWMDNC_TSDMN_SHIFT                 (16)  /* Timestamp Descriptor Maximum Number */
#define R_GWCA_GWMDNC_TSDMN_MASK                  0x30000

/* GWTPCP Register bit definitions */
#define R_GWCA_GWTPCP_PPPL0                       (1 << 0)  /* Per Priority Pause Level i (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWTPCP_PPPL1                       (1 << 1)  /* Per Priority Pause Level i (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWTPCP_PPPL2                       (1 << 2)  /* Per Priority Pause Level i (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWTPCP_PPPL3                       (1 << 3)  /* Per Priority Pause Level i (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWTPCP_PPPL4                       (1 << 4)  /* Per Priority Pause Level i (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWTPCP_PPPL5                       (1 << 5)  /* Per Priority Pause Level i (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWTPCP_PPPL6                       (1 << 6)  /* Per Priority Pause Level i (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWTPCP_PPPL7                       (1 << 7)  /* Per Priority Pause Level i (The variable i corresponds to the bit position number.) */

/* GWARIRM Register bit definitions */
#define R_GWCA_GWARIRM_ARIOG                      (1 << 0)  /* AXI RAM Initialization Ongoing */

#define R_GWCA_GWARIRM_ARR                        (1 << 1)  /* AXI RAM Ready */

/* GWDCC Register bit definitions */
#define R_GWCA_GWDCC_SM_SHIFT                     (0)  /* Synchronization Mode */
#define R_GWCA_GWDCC_SM_MASK                      0x3
#  define R_GWCA_GWDCC_SM_00                              (0 << R_GWCA_GWDCC_SM_SHIFT)  /* Normal mode (full descriptor write back) */
#  define R_GWCA_GWDCC_SM_01                              (1 << R_GWCA_GWDCC_SM_SHIFT)  /* No-write-back mode (no descriptor write back) */
#  define R_GWCA_GWDCC_SM_10                              (2 << R_GWCA_GWDCC_SM_SHIFT)  /* Keep-DT mode (no update of DT field at descriptor write back) */
#  define R_GWCA_GWDCC_SM_11                              (3 << R_GWCA_GWDCC_SM_SHIFT)  /* Reserved */

#define R_GWCA_GWDCC_EDE                          (1 << 8)  /* Extended Descriptor Enable */

#define R_GWCA_GWDCC_ETS                          (1 << 9)  /* Enable Timestamp Storage */

#define R_GWCA_GWDCC_SL                           (1 << 10)  /* Security Level */

#define R_GWCA_GWDCC_DQT                          (1 << 11)  /* Descriptor Queue Type */

#define R_GWCA_GWDCC_DCP_SHIFT                    (16)  /* Descriptor Chain Priority */
#define R_GWCA_GWDCC_DCP_MASK                     0x70000
#  define R_GWCA_GWDCC_DCP_000                            (0 << R_GWCA_GWDCC_DCP_SHIFT)  /* Lowest priority */
#  define R_GWCA_GWDCC_DCP_111                            (7 << R_GWCA_GWDCC_DCP_SHIFT)  /* Highest priority */

#define R_GWCA_GWDCC_BALR                         (1 << 24)  /* Base Address Load Request */

#define R_GWCA_GWDCC_OSID_SHIFT                   (28)  /* OS ID */
#define R_GWCA_GWDCC_OSID_MASK                    0x70000000

/* GWAARSS Register bit definitions */
#define R_GWCA_GWAARSS_AARA_SHIFT                 (0)  /* AXI Address RAM Address */
#define R_GWCA_GWAARSS_AARA_MASK                  0x7f

/* GWAARSR0 Register bit definitions */
#define R_GWCA_GWAARSR0_ACARU_SHIFT               (0)  /* AXI Current Address Result Upper Part */
#define R_GWCA_GWAARSR0_ACARU_MASK                0xff

#define R_GWCA_GWAARSR0_AARS                      (1 << 31)  /* AXI Address RAM Searching */

#define R_GWCA_GWAARSR0_AARSEF                    (1 << 16)  /* AARSEF */

#define R_GWCA_GWAARSR0_AARSSF                    (1 << 17)  /* AARSSF */

/* GWAARSR1 Register bit definitions */
#define R_GWCA_GWAARSR1_ACARL_SHIFT               (0)  /* AXI Current Address Result Lower Part */
#define R_GWCA_GWAARSR1_ACARL_MASK                0xffffffff

#define R_GWCA_GWAARSR1_ACARD_SHIFT               (0)  /* ACARD */
#define R_GWCA_GWAARSR1_ACARD_MASK                0xffffffff

/* GWIDAUAS Register bit definitions */
#define R_GWCA_GWIDAUAS_IDAUAS_SHIFT              (0)  /* Incremental Data Area Used Size of RX Descriptor Chain i */
#define R_GWCA_GWIDAUAS_IDAUAS_MASK               0xffffff

/* GWIDASM Register bit definitions */
#define R_GWCA_GWIDASM_IDAS_SHIFT                 (0)  /* Incremental Data Area Size of RX Descriptor Chain i */
#define R_GWCA_GWIDASM_IDAS_MASK                  0xffffff

/* GWIDASAM Register bit definitions */
#define R_GWCA_GWIDASAM_IDASAU_SHIFT              (0)  /* Incremental Data Area Start Address Upper Part of RX Descriptor Chain i */
#define R_GWCA_GWIDASAM_IDASAU_MASK               0xff

/* GWIDASAM Register bit definitions */
#define R_GWCA_GWIDASAM_IDASAL_SHIFT              (0)  /* Incremental Data Area Start Address Lower Part of RX Descriptor Chain i */
#define R_GWCA_GWIDASAM_IDASAL_MASK               0xffffffff

/* GWIDACAM Register bit definitions */
#define R_GWCA_GWIDACAM_IDACAU_SHIFT              (0)  /* Incremental Data Area Current Address Upper Part of RX Descriptor Chain i */
#define R_GWCA_GWIDACAM_IDACAU_MASK               0xff

/* GWIDACAM Register bit definitions */
#define R_GWCA_GWIDACAM_IDACAL_SHIFT              (0)  /* Incremental Data Area Current Address Lower Part of RX Descriptor Chain i */
#define R_GWCA_GWIDACAM_IDACAL_MASK               0xffffffff

/* GWGRLC Register bit definitions */
#define R_GWCA_GWGRLC_GRLIV_SHIFT                 (0)  /* Global Rate Limiter Incremental Value */
#define R_GWCA_GWGRLC_GRLIV_MASK                  0xffff

#define R_GWCA_GWGRLC_GRLE                        (1 << 16)  /* Global Rate Limiter Enable */

#define R_GWCA_GWGRLC_GRLULRS                     (1 << 17)  /* Global Rate Limiter Upper Limit Reached Status Flag */

/* GWGRLULC Register bit definitions */
#define R_GWCA_GWGRLULC_GRLUL_SHIFT               (0)  /* Global Rate Limiter Upper Limit */
#define R_GWCA_GWGRLULC_GRLUL_MASK                0xffffff

/* GWRLC Register bit definitions */
#define R_GWCA_GWRLC_RLIV_SHIFT                   (0)  /* Rate Limiter Incremental Value */
#define R_GWCA_GWRLC_RLIV_MASK                    0xfff

#define R_GWCA_GWRLC_RLE                          (1 << 16)  /* Rate Limiter Enable */

/* GWRLULC Register bit definitions */
#define R_GWCA_GWRLULC_RLUL_SHIFT                 (0)  /* Rate Limiter Upper Limit */
#define R_GWCA_GWRLULC_RLUL_MASK                  0xffffff

/* GWIDPC Register bit definitions */
#define R_GWCA_GWIDPC_IDPV_SHIFT                  (0)  /* Interrupt Delay Prescaler Value */
#define R_GWCA_GWIDPC_IDPV_MASK                   0x3ff

/* GWRDCN Register bit definitions */
#define R_GWCA_GWRDCN_RDN_SHIFT                   (0)  /* Received Data Number */
#define R_GWCA_GWRDCN_RDN_MASK                    0xffffffff

/* GWTDCN Register bit definitions */
#define R_GWCA_GWTDCN_TDN_SHIFT                   (0)  /* Transmitted Data Number */
#define R_GWCA_GWTDCN_TDN_MASK                    0xffffffff

/* GWTSCN Register bit definitions */
#define R_GWCA_GWTSCN_TN_SHIFT                    (0)  /* Timestamp Number */
#define R_GWCA_GWTSCN_TN_MASK                     0xffffffff

/* GWTSOVFECN Register bit definitions */
#define R_GWCA_GWTSOVFECN_TSOVFEN_SHIFT           (0)  /* Timestamp Overflow Error Number */
#define R_GWCA_GWTSOVFECN_TSOVFEN_MASK            0xffff

/* GWUSMFSECN Register bit definitions */
#define R_GWCA_GWUSMFSECN_USMFSEN_SHIFT           (0)  /* Under Switch Minimum Frame Size Error Number */
#define R_GWCA_GWUSMFSECN_USMFSEN_MASK            0xffff

/* GWTFECN Register bit definitions */
#define R_GWCA_GWTFECN_TFEN_SHIFT                 (0)  /* TAG Filtering Error Number */
#define R_GWCA_GWTFECN_TFEN_MASK                  0xffff

/* GWSEQECN Register bit definitions */
#define R_GWCA_GWSEQECN_SEQEN_SHIFT               (0)  /* Sequence Error Number */
#define R_GWCA_GWSEQECN_SEQEN_MASK                0xffff

/* GWTXDNECN Register bit definitions */
#define R_GWCA_GWTXDNECN_TXDNEN_SHIFT             (0)  /* TX Descriptor Number Error Number */
#define R_GWCA_GWTXDNECN_TXDNEN_MASK              0xffff

/* GWFSECN Register bit definitions */
#define R_GWCA_GWFSECN_FSEN_SHIFT                 (0)  /* Frame Size Error Number */
#define R_GWCA_GWFSECN_FSEN_MASK                  0xffff

/* GWTDFECN Register bit definitions */
#define R_GWCA_GWTDFECN_TDFEN_SHIFT               (0)  /* Timestamp Descriptor Full Error Number */
#define R_GWCA_GWTDFECN_TDFEN_MASK                0xffff

/* GWTSDNECN Register bit definitions */
#define R_GWCA_GWTSDNECN_TSDNEN_SHIFT             (0)  /* Timestamp Descriptor Number Error Number */
#define R_GWCA_GWTSDNECN_TSDNEN_MASK              0xffff

/* GWDQOECN Register bit definitions */
#define R_GWCA_GWDQOECN_DQOEN_SHIFT               (0)  /* Descriptor Queue Overflow Error Number */
#define R_GWCA_GWDQOECN_DQOEN_MASK                0xffff

/* GWDQSECN Register bit definitions */
#define R_GWCA_GWDQSECN_DQSEN_SHIFT               (0)  /* Descriptor Queue Security Error Number */
#define R_GWCA_GWDQSECN_DQSEN_MASK                0xffff

/* GWDFECN Register bit definitions */
#define R_GWCA_GWDFECN_DFEN_SHIFT                 (0)  /* Descriptor Full Error Number */
#define R_GWCA_GWDFECN_DFEN_MASK                  0xffff

/* GWDSECN Register bit definitions */
#define R_GWCA_GWDSECN_DSEN_SHIFT                 (0)  /* Descriptor Security Error Number */
#define R_GWCA_GWDSECN_DSEN_MASK                  0xffff

/* GWDSZECN Register bit definitions */
#define R_GWCA_GWDSZECN_DSZEN_SHIFT               (0)  /* Data Size Error Number */
#define R_GWCA_GWDSZECN_DSZEN_MASK                0xffff

/* GWDCTECN Register bit definitions */
#define R_GWCA_GWDCTECN_DCTEN_SHIFT               (0)  /* Descriptor Chain Type Error Number */
#define R_GWCA_GWDCTECN_DCTEN_MASK                0xffff

/* GWRXDNECN Register bit definitions */
#define R_GWCA_GWRXDNECN_RXDNEN_SHIFT             (0)  /* RX Descriptor Number Error Number */
#define R_GWCA_GWRXDNECN_RXDNEN_MASK              0xffff

/* GWTSDIS Register bit definitions */
#define R_GWCA_GWTSDIS_TSDIS1 TO TSDIS0_SHIFT     (0)  /* Timestamp Data i Interrupt Status Flag */
#define R_GWCA_GWTSDIS_TSDIS1 TO TSDIS0_MASK      0x3

#define R_GWCA_GWTSDIS_TSDIS0                     (1 << 0)  /* TSDIS0 */

#define R_GWCA_GWTSDIS_TSDIS1                     (1 << 1)  /* TSDIS1 */

/* GWTSDIE Register bit definitions */
#define R_GWCA_GWTSDIE_TSDIE0                     (1 << 0)  /* Timestamp Data i Interrupt Enable */

#define R_GWCA_GWTSDIE_TSDIE1                     (1 << 1)  /* Timestamp Data i Interrupt Enable */

/* GWTSDID Register bit definitions */
#define R_GWCA_GWTSDID_TSDID1 TO TSDID0_SHIFT     (0)  /* Timestamp Data i Interrupt Disable */
#define R_GWCA_GWTSDID_TSDID1 TO TSDID0_MASK      0x3

#define R_GWCA_GWTSDID_TSDID0                     (1 << 0)  /* TSDID0 */

#define R_GWCA_GWTSDID_TSDID1                     (1 << 1)  /* TSDID1 */

/* GWEIS0 Register bit definitions */
#define R_GWCA_GWEIS0_AES                         (1 << 0)  /* AXI Error Status Flag */

#define R_GWCA_GWEIS0_TSOVFES                     (1 << 9)  /* Timestamp Overflow Error Status Flag */

#define R_GWCA_GWEIS0_USMFSES                     (1 << 10)  /* Under Switch Minimum Frame Size Error Status Flag */

#define R_GWCA_GWEIS0_TFES                        (1 << 11)  /* TAG Filtering Error Status Flag */

#define R_GWCA_GWEIS0_SEQES                       (1 << 12)  /* Sequence Error Status Flag */

#define R_GWCA_GWEIS0_TXDNES                      (1 << 14)  /* TX Descriptor Number Error Status Flag */

#define R_GWCA_GWEIS0_TSHES                       (1 << 15)  /* Timestamp Hardware Error Status Flag */

#define R_GWCA_GWEIS0_FSES7 TO FSES0_SHIFT        (16)  /* Frame Size Error Status Flag i */
#define R_GWCA_GWEIS0_FSES7 TO FSES0_MASK         0xff0000

#define R_GWCA_GWEIS0_TDFES1 TO TDFES0_SHIFT      (24)  /* Timestamp Descriptor i Full Error Status Flag */
#define R_GWCA_GWEIS0_TDFES1 TO TDFES0_MASK       0x3000000

#define R_GWCA_GWEIS0_TSDNES1 TO TSDNES0_SHIFT    (28)  /* Timestamp Descriptor i Number Error Status Flag */
#define R_GWCA_GWEIS0_TSDNES1 TO TSDNES0_MASK     0x30000000

#define R_GWCA_GWEIS0_DECCES                      (1 << 1)  /* DECCES */

#define R_GWCA_GWEIS0_TECCES                      (1 << 2)  /* TECCES */

#define R_GWCA_GWEIS0_PECCES                      (1 << 3)  /* PECCES */

#define R_GWCA_GWEIS0_DSECCES                     (1 << 4)  /* DSECCES */

#define R_GWCA_GWEIS0_MECCES                      (1 << 5)  /* MECCES */

#define R_GWCA_GWEIS0_AECCES                      (1 << 6)  /* AECCES */

#define R_GWCA_GWEIS0_TSECCES                     (1 << 7)  /* TSECCES */

#define R_GWCA_GWEIS0_L23UECCES                   (1 << 8)  /* L23UECCES */

#define R_GWCA_GWEIS0_FSES0                       (1 << 16)  /* FSES0 */

#define R_GWCA_GWEIS0_FSES1                       (1 << 17)  /* FSES1 */

#define R_GWCA_GWEIS0_FSES2                       (1 << 18)  /* FSES2 */

#define R_GWCA_GWEIS0_FSES3                       (1 << 19)  /* FSES3 */

#define R_GWCA_GWEIS0_FSES4                       (1 << 20)  /* FSES4 */

#define R_GWCA_GWEIS0_FSES5                       (1 << 21)  /* FSES5 */

#define R_GWCA_GWEIS0_FSES6                       (1 << 22)  /* FSES6 */

#define R_GWCA_GWEIS0_FSES7                       (1 << 23)  /* FSES7 */

#define R_GWCA_GWEIS0_TDFES0                      (1 << 24)  /* TDFES0 */

#define R_GWCA_GWEIS0_TDFES1                      (1 << 25)  /* TDFES1 */

#define R_GWCA_GWEIS0_TSDNES0                     (1 << 28)  /* TSDNES0 */

#define R_GWCA_GWEIS0_TSDNES1                     (1 << 29)  /* TSDNES1 */

/* GWEIE0 Register bit definitions */
#define R_GWCA_GWEIE0_AEE                         (1 << 0)  /* AXI Error Enable */

#define R_GWCA_GWEIE0_TSOVFEE                     (1 << 9)  /* Timestamp Overflow Error Enable */

#define R_GWCA_GWEIE0_USMFSEE                     (1 << 10)  /* Under Minimum Frame Size Error Enable */

#define R_GWCA_GWEIE0_TFEE                        (1 << 11)  /* TAG Filtering Error Enable */

#define R_GWCA_GWEIE0_SEQEE                       (1 << 12)  /* Sequence Error Enable */

#define R_GWCA_GWEIE0_TXDNEE                      (1 << 14)  /* TX Descriptor Number Error Enable */

#define R_GWCA_GWEIE0_TSHEE                       (1 << 15)  /* Timestamp Hardware Error Enable */

#define R_GWCA_GWEIE0_FSEE0                       (1 << 16)  /* Frame Size Error Enable i (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWEIE0_FSEE1                       (1 << 17)  /* Frame Size Error Enable i (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWEIE0_FSEE2                       (1 << 18)  /* Frame Size Error Enable i (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWEIE0_FSEE3                       (1 << 19)  /* Frame Size Error Enable i (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWEIE0_FSEE4                       (1 << 20)  /* Frame Size Error Enable i (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWEIE0_FSEE5                       (1 << 21)  /* Frame Size Error Enable i (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWEIE0_FSEE6                       (1 << 22)  /* Frame Size Error Enable i (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWEIE0_FSEE7                       (1 << 23)  /* Frame Size Error Enable i (The variable i corresponds to the bit position number.) */

#define R_GWCA_GWEIE0_TDFEE0                      (1 << 24)  /* Timestamp Descriptor i Full Error Enable */

#define R_GWCA_GWEIE0_TDFEE1                      (1 << 25)  /* Timestamp Descriptor i Full Error Enable */

#define R_GWCA_GWEIE0_TSDNEE0                     (1 << 28)  /* Timestamp Descriptor i Number Error Enable */

#define R_GWCA_GWEIE0_TSDNEE1                     (1 << 29)  /* Timestamp Descriptor i Number Error Enable */

#define R_GWCA_GWEIE0_DECCEE                      (1 << 1)  /* DECCEE */

#define R_GWCA_GWEIE0_TECCEE                      (1 << 2)  /* TECCEE */

#define R_GWCA_GWEIE0_PECCEE                      (1 << 3)  /* PECCEE */

#define R_GWCA_GWEIE0_DSECCEE                     (1 << 4)  /* DSECCEE */

#define R_GWCA_GWEIE0_MECCEE                      (1 << 5)  /* MECCEE */

#define R_GWCA_GWEIE0_AECCEE                      (1 << 6)  /* AECCEE */

#define R_GWCA_GWEIE0_TSECCEE                     (1 << 7)  /* TSECCEE */

#define R_GWCA_GWEIE0_L23UECCEE                   (1 << 8)  /* L23UECCEE */

/* GWEID0 Register bit definitions */
#define R_GWCA_GWEID0_AED                         (1 << 0)  /* AXI Error Disable */

#define R_GWCA_GWEID0_TSOVFED                     (1 << 9)  /* Timestamp Overflow Error Disable */

#define R_GWCA_GWEID0_USMFSED                     (1 << 10)  /* Under Minimum Frame Size Error Disable */

#define R_GWCA_GWEID0_TFED                        (1 << 11)  /* TAG Filtering Error Disable */

#define R_GWCA_GWEID0_SEQED                       (1 << 12)  /* Sequence Error Disable */

#define R_GWCA_GWEID0_TXDNED                      (1 << 14)  /* TX Descriptor Number Error Disable */

#define R_GWCA_GWEID0_TSHED                       (1 << 15)  /* Timestamp Hardware Full Error Disable */

#define R_GWCA_GWEID0_FSED7 TO FSED0_SHIFT        (16)  /* Frame Size Error Disable i */
#define R_GWCA_GWEID0_FSED7 TO FSED0_MASK         0xff0000

#define R_GWCA_GWEID0_TDFED1 TO TDFED0_SHIFT      (24)  /* Timestamp Descriptor i Full Error Disable */
#define R_GWCA_GWEID0_TDFED1 TO TDFED0_MASK       0x3000000

#define R_GWCA_GWEID0_TSDNED1 TO TSDNED0_SHIFT    (28)  /* Timestamp Descriptor i Number Error Disable */
#define R_GWCA_GWEID0_TSDNED1 TO TSDNED0_MASK     0x30000000

#define R_GWCA_GWEID0_TECCED                      (1 << 1)  /* TECCED */

#define R_GWCA_GWEID0_DECCED                      (1 << 2)  /* DECCED */

#define R_GWCA_GWEID0_PECCED                      (1 << 3)  /* PECCED */

#define R_GWCA_GWEID0_DSECCED                     (1 << 4)  /* DSECCED */

#define R_GWCA_GWEID0_MECCED                      (1 << 5)  /* MECCED */

#define R_GWCA_GWEID0_AECCED                      (1 << 6)  /* AECCED */

#define R_GWCA_GWEID0_TSECCED                     (1 << 7)  /* TSECCED */

#define R_GWCA_GWEID0_L23UECCED                   (1 << 8)  /* L23UECCED */

#define R_GWCA_GWEID0_IIPED                       (1 << 13)  /* IIPED */

#define R_GWCA_GWEID0_FSED0                       (1 << 16)  /* FSED0 */

#define R_GWCA_GWEID0_FSED1                       (1 << 17)  /* FSED1 */

#define R_GWCA_GWEID0_FSED2                       (1 << 18)  /* FSED2 */

#define R_GWCA_GWEID0_FSED3                       (1 << 19)  /* FSED3 */

#define R_GWCA_GWEID0_FSED4                       (1 << 20)  /* FSED4 */

#define R_GWCA_GWEID0_FSED5                       (1 << 21)  /* FSED5 */

#define R_GWCA_GWEID0_FSED6                       (1 << 22)  /* FSED6 */

#define R_GWCA_GWEID0_FSED7                       (1 << 23)  /* FSED7 */

#define R_GWCA_GWEID0_TDFED0                      (1 << 24)  /* TDFED0 */

#define R_GWCA_GWEID0_TDFED1                      (1 << 25)  /* TDFED1 */

#define R_GWCA_GWEID0_TSDNED0                     (1 << 28)  /* TSDNED0 */

#define R_GWCA_GWEID0_TSDNED1                     (1 << 29)  /* TSDNED1 */

/* GWEIS1 Register bit definitions */
#define R_GWCA_GWEIS1_DQOES7 TO DQOES0_SHIFT      (0)  /* Descriptor Queue i Overflow Error Status Flag */
#define R_GWCA_GWEIS1_DQOES7 TO DQOES0_MASK       0xff

#define R_GWCA_GWEIS1_DQSES7 TO DQSES0_SHIFT      (16)  /* Descriptor Queue i Security Error Status Flag (The variable i corresponds to the bit position number.) */
#define R_GWCA_GWEIS1_DQSES7 TO DQSES0_MASK       0xff0000

#define R_GWCA_GWEIS1_DQOES0                      (1 << 0)  /* DQOES0 */

#define R_GWCA_GWEIS1_DQOES1                      (1 << 1)  /* DQOES1 */

#define R_GWCA_GWEIS1_DQOES2                      (1 << 2)  /* DQOES2 */

#define R_GWCA_GWEIS1_DQOES3                      (1 << 3)  /* DQOES3 */

#define R_GWCA_GWEIS1_DQOES4                      (1 << 4)  /* DQOES4 */

#define R_GWCA_GWEIS1_DQOES5                      (1 << 5)  /* DQOES5 */

#define R_GWCA_GWEIS1_DQOES6                      (1 << 6)  /* DQOES6 */

#define R_GWCA_GWEIS1_DQOES7                      (1 << 7)  /* DQOES7 */

#define R_GWCA_GWEIS1_DQSES0                      (1 << 16)  /* DQSES0 */

#define R_GWCA_GWEIS1_DQSES1                      (1 << 17)  /* DQSES1 */

#define R_GWCA_GWEIS1_DQSES2                      (1 << 18)  /* DQSES2 */

#define R_GWCA_GWEIS1_DQSES3                      (1 << 19)  /* DQSES3 */

#define R_GWCA_GWEIS1_DQSES4                      (1 << 20)  /* DQSES4 */

#define R_GWCA_GWEIS1_DQSES5                      (1 << 21)  /* DQSES5 */

#define R_GWCA_GWEIS1_DQSES6                      (1 << 22)  /* DQSES6 */

#define R_GWCA_GWEIS1_DQSES7                      (1 << 23)  /* DQSES7 */

/* GWEIE1 Register bit definitions */
#define R_GWCA_GWEIE1_DQOEE0                      (1 << 0)  /* Descriptor Queue i Overflow Error Enable */

#define R_GWCA_GWEIE1_DQOEE1                      (1 << 1)  /* Descriptor Queue i Overflow Error Enable */

#define R_GWCA_GWEIE1_DQOEE2                      (1 << 2)  /* Descriptor Queue i Overflow Error Enable */

#define R_GWCA_GWEIE1_DQOEE3                      (1 << 3)  /* Descriptor Queue i Overflow Error Enable */

#define R_GWCA_GWEIE1_DQOEE4                      (1 << 4)  /* Descriptor Queue i Overflow Error Enable */

#define R_GWCA_GWEIE1_DQOEE5                      (1 << 5)  /* Descriptor Queue i Overflow Error Enable */

#define R_GWCA_GWEIE1_DQOEE6                      (1 << 6)  /* Descriptor Queue i Overflow Error Enable */

#define R_GWCA_GWEIE1_DQOEE7                      (1 << 7)  /* Descriptor Queue i Overflow Error Enable */

#define R_GWCA_GWEIE1_DQSEE0                      (1 << 16)  /* Descriptor Queue i Security Error Enable */

#define R_GWCA_GWEIE1_DQSEE1                      (1 << 17)  /* Descriptor Queue i Security Error Enable */

#define R_GWCA_GWEIE1_DQSEE2                      (1 << 18)  /* Descriptor Queue i Security Error Enable */

#define R_GWCA_GWEIE1_DQSEE3                      (1 << 19)  /* Descriptor Queue i Security Error Enable */

#define R_GWCA_GWEIE1_DQSEE4                      (1 << 20)  /* Descriptor Queue i Security Error Enable */

#define R_GWCA_GWEIE1_DQSEE5                      (1 << 21)  /* Descriptor Queue i Security Error Enable */

#define R_GWCA_GWEIE1_DQSEE6                      (1 << 22)  /* Descriptor Queue i Security Error Enable */

#define R_GWCA_GWEIE1_DQSEE7                      (1 << 23)  /* Descriptor Queue i Security Error Enable */

/* GWEID1 Register bit definitions */
#define R_GWCA_GWEID1_DQOED7 TO DQOED0_SHIFT      (0)  /* Descriptor Queue i Overflow Error Disable */
#define R_GWCA_GWEID1_DQOED7 TO DQOED0_MASK       0xff

#define R_GWCA_GWEID1_DQSED7 TO DQSED0_SHIFT      (16)  /* Descriptor Queue i Security Error Disable (The variable i corresponds to the bit position number.) */
#define R_GWCA_GWEID1_DQSED7 TO DQSED0_MASK       0xff0000

#define R_GWCA_GWEID1_DQOED0                      (1 << 0)  /* DQOED0 */

#define R_GWCA_GWEID1_DQOED1                      (1 << 1)  /* DQOED1 */

#define R_GWCA_GWEID1_DQOED2                      (1 << 2)  /* DQOED2 */

#define R_GWCA_GWEID1_DQOED3                      (1 << 3)  /* DQOED3 */

#define R_GWCA_GWEID1_DQOED4                      (1 << 4)  /* DQOED4 */

#define R_GWCA_GWEID1_DQOED5                      (1 << 5)  /* DQOED5 */

#define R_GWCA_GWEID1_DQOED6                      (1 << 6)  /* DQOED6 */

#define R_GWCA_GWEID1_DQOED7                      (1 << 7)  /* DQOED7 */

#define R_GWCA_GWEID1_DQSED0                      (1 << 16)  /* DQSED0 */

#define R_GWCA_GWEID1_DQSED1                      (1 << 17)  /* DQSED1 */

#define R_GWCA_GWEID1_DQSED2                      (1 << 18)  /* DQSED2 */

#define R_GWCA_GWEID1_DQSED3                      (1 << 19)  /* DQSED3 */

#define R_GWCA_GWEID1_DQSED4                      (1 << 20)  /* DQSED4 */

#define R_GWCA_GWEID1_DQSED5                      (1 << 21)  /* DQSED5 */

#define R_GWCA_GWEID1_DQSED6                      (1 << 22)  /* DQSED6 */

#define R_GWCA_GWEID1_DQSED7                      (1 << 23)  /* DQSED7 */

/* GWEIS3 Register bit definitions */
#define R_GWCA_GWEIS3_IAOES3 TO IAOES0_SHIFT      (0)  /* Incremental Area i Overflow Error Status Flag */
#define R_GWCA_GWEIS3_IAOES3 TO IAOES0_MASK       0xf

#define R_GWCA_GWEIS3_IAOES0                      (1 << 0)  /* IAOES0 */

#define R_GWCA_GWEIS3_IAOES1                      (1 << 1)  /* IAOES1 */

#define R_GWCA_GWEIS3_IAOES2                      (1 << 2)  /* IAOES2 */

#define R_GWCA_GWEIS3_IAOES3                      (1 << 3)  /* IAOES3 */

#define R_GWCA_GWEIS3_IAOES4                      (1 << 4)  /* IAOES4 */

/* GWEIE3 Register bit definitions */
#define R_GWCA_GWEIE3_IAOEE0                      (1 << 0)  /* Incremental Area i Overflow Error Enable */

#define R_GWCA_GWEIE3_IAOEE1                      (1 << 1)  /* Incremental Area i Overflow Error Enable */

#define R_GWCA_GWEIE3_IAOEE2                      (1 << 2)  /* Incremental Area i Overflow Error Enable */

#define R_GWCA_GWEIE3_IAOEE3                      (1 << 3)  /* Incremental Area i Overflow Error Enable */

#define R_GWCA_GWEIE3_IAOEE4                      (1 << 4)  /* IAOEE4 */

/* GWEID3 Register bit definitions */
#define R_GWCA_GWEID3_IAOED3 TO IAOED0_SHIFT      (0)  /* Incremental Area i Overflow Error Disable */
#define R_GWCA_GWEID3_IAOED3 TO IAOED0_MASK       0xf

#define R_GWCA_GWEID3_IAOED0                      (1 << 0)  /* IAOED0 */

#define R_GWCA_GWEID3_IAOED1                      (1 << 1)  /* IAOED1 */

#define R_GWCA_GWEID3_IAOED2                      (1 << 2)  /* IAOED2 */

#define R_GWCA_GWEID3_IAOED3                      (1 << 3)  /* IAOED3 */

#define R_GWCA_GWEID3_IAOED4                      (1 << 4)  /* IAOED4 */

/* GWEIS4 Register bit definitions */
#define R_GWCA_GWEIS4_DSSES                       (1 << 0)  /* Descriptor Security Error Status Flag */

#define R_GWCA_GWEIS4_DSSEIOS                     (1 << 1)  /* Descriptor Security Error Interrupt Overflow Status Flag */

#define R_GWCA_GWEIS4_DSSECN_SHIFT                (8)  /* Descriptor Security Error Chain Number */
#define R_GWCA_GWEIS4_DSSECN_MASK                 0x3f00

#define R_GWCA_GWEIS4_DSES                        (1 << 16)  /* Data Size Error Status Flag */

#define R_GWCA_GWEIS4_DSEIOS                      (1 << 17)  /* Data Size Error Interrupt Overflow Status Flag */

#define R_GWCA_GWEIS4_DSECN_SHIFT                 (24)  /* Data Size Error Chain Number */
#define R_GWCA_GWEIS4_DSECN_MASK                  0x3f000000

/* GWEIE4 Register bit definitions */
#define R_GWCA_GWEIE4_DSSEE                       (1 << 0)  /* Descriptor Security Error Enable */

#define R_GWCA_GWEIE4_DSSEIOE                     (1 << 1)  /* Descriptor Security Error Interrupt Overflow Enable */

#define R_GWCA_GWEIE4_DSEE                        (1 << 16)  /* Data Size Error Enable */

#define R_GWCA_GWEIE4_DSEIOE                      (1 << 17)  /* Data Size Error Interrupt Overflow Interrupt Enable */

/* GWEID4 Register bit definitions */
#define R_GWCA_GWEID4_DSSED                       (1 << 0)  /* Descriptor Security Error Disable */

#define R_GWCA_GWEID4_DSSEIOD                     (1 << 1)  /* Descriptor Security Error Interrupt Overflow Disable */

#define R_GWCA_GWEID4_DSED                        (1 << 16)  /* Data Size Error Disable */

#define R_GWCA_GWEID4_DSEIOD                      (1 << 17)  /* Data Size Error Interrupt Overflow Disable */

/* GWEIS5 Register bit definitions */
#define R_GWCA_GWEIS5_DCTES                       (1 << 0)  /* Descriptor Chain Type Error Status Flag */

#define R_GWCA_GWEIS5_DCTEIOS                     (1 << 1)  /* Descriptor Chain Type Error Interrupt Overflow Status Flag */

#define R_GWCA_GWEIS5_DCTECN_SHIFT                (8)  /* Descriptor Chain Type Error Chain Number */
#define R_GWCA_GWEIS5_DCTECN_MASK                 0x3f00

#define R_GWCA_GWEIS5_RXDNES                      (1 << 16)  /* RX Descriptor Number Error Status Flag */

#define R_GWCA_GWEIS5_RXDNEIOS                    (1 << 17)  /* RX Descriptor Number Error Interrupt Overflow Status Flag */

#define R_GWCA_GWEIS5_RXDNECN_SHIFT               (24)  /* RX Descriptor Number Error Chain Number */
#define R_GWCA_GWEIS5_RXDNECN_MASK                0x3f000000

/* GWEIE5 Register bit definitions */
#define R_GWCA_GWEIE5_DCTEE                       (1 << 0)  /* Descriptor Chain Type Error Enable */

#define R_GWCA_GWEIE5_DCTEIOE                     (1 << 1)  /* Descriptor Chain Type Error Interrupt Overflow Enable */

#define R_GWCA_GWEIE5_RXDNEE                      (1 << 16)  /* RX Descriptor Number Error Enable */

#define R_GWCA_GWEIE5_RXDNEIOE                    (1 << 17)  /* RX Descriptor Number Error Interrupt Overflow Enable */

/* GWEID5 Register bit definitions */
#define R_GWCA_GWEID5_DCTED                       (1 << 0)  /* Descriptor Chain Type Error Disable */

#define R_GWCA_GWEID5_DCTEIOD                     (1 << 1)  /* Descriptor Chain Type Error Interrupt Overflow Disable */

#define R_GWCA_GWEID5_RXDNED                      (1 << 15)  /* RX Descriptor Number Error Disable */

#define R_GWCA_GWEID5_RXDNEIOD                    (1 << 16)  /* RX Descriptor Number Error Interrupt Overflow Disable */

/* GWIDC Register bit definitions */
#define R_GWCA_GWIDC_IDV_SHIFT                    (0)  /* Interrupt Delay Value */
#define R_GWCA_GWIDC_IDV_MASK                     0xfff


/* Maximum number of channels */

#define GWCA_MAX_CHANNELS    64

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GWCA_H */
