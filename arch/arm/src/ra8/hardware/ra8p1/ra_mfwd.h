/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_mfwd.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MFWD_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MFWD_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* MFWD Base Address */
#ifndef R_MFWD_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_MFWD_BASE           0x403c0000
#else
#define R_MFWD_BASE           0x503c0000
#endif
#endif

/* MFWD Register Offsets */

#define R_MFWD_FWGC_OFFSET                        0x00000000  /* General Configuration Register */
#define R_MFWD_FWTTC0_OFFSET                      0x00000010  /* TAG TPID Configuration Register 0 */
#define R_MFWD_FWTTC1_OFFSET                      0x00000014  /* TAG TPID Configuration Register 1 */
#define R_MFWD_FWCEPTC_OFFSET                     0x00000020  /* CPU Exceptional Path Target Configuration Register */
#define R_MFWD_FWCEPRC0_OFFSET                    0x00000024  /* CPU Exceptional Path Reason Configuration Register 0 */
#define R_MFWD_FWCEPRC1_OFFSET                    0x00000028  /* CPU Exceptional Path Reason Configuration Register 1 */
#define R_MFWD_FWCEPRC2_OFFSET                    0x0000002c  /* CPU Exceptional Path Reason Configuration Register 2 */
#define R_MFWD_FWCLPTC_OFFSET                     0x00000030  /* CPU Learning Path Target Configuration Register */
#define R_MFWD_FWCLPRC_OFFSET                     0x00000034  /* CPU Learning Path Reason Configuration Register */
#define R_MFWD_FWCMPTC_OFFSET                     0x00000040  /* CPU Mirroring Path Target Configuration Register */
#define R_MFWD_FWEMPTC_OFFSET                     0x00000044  /* Ethernet Mirroring Path Target Configuration Register */
#define R_MFWD_FWSDMPTC_OFFSET                    0x00000050  /* Source-Destination Mirroring Path Target Configuration Register */
#define R_MFWD_FWSDMPVC_OFFSET                    0x00000054  /* Source-Destination Mirroring Path Vector Configuration Register */
/* FWLBWMC%s Registers (0-2) */
#define R_MFWD_FWLBWMC_OFFSET(m)                  (0x00000080 + ((m) * 0x00000004))  /* Level Based Watermark Configuration Register %s */
/* FWPC0%s Registers (0-2) */
#define R_MFWD_FWPC0_OFFSET(m)                    (0x00000100 + ((m) * 0x00000010))  /* Port Configuration Register 0%s */
/* FWPC1%s Registers (0-2) */
#define R_MFWD_FWPC1_OFFSET(m)                    (0x00000104 + ((m) * 0x00000010))  /* Port Configuration Register 1%s */
/* FWPC2%s Registers (0-2) */
#define R_MFWD_FWPC2_OFFSET(m)                    (0x00000108 + ((m) * 0x00000010))  /* Port Configuration Register 2%s */
/* FWCTGC0%s Registers (0-7) */
#define R_MFWD_FWCTGC0_OFFSET(m)                  (0x00000400 + ((m) * 0x00000040))  /* Cut-Through General Configuration Register 0%s */
/* FWCTGC1%s Registers (0-7) */
#define R_MFWD_FWCTGC1_OFFSET(m)                  (0x00000404 + ((m) * 0x00000040))  /* Cut-Through General Configuration Register 1%s */
/* FWCTTC0%s Registers (0-7) */
#define R_MFWD_FWCTTC0_OFFSET(m)                  (0x00000408 + ((m) * 0x00000040))  /* Cut-Through Target Configuration Register 0%s */
/* FWCTTC1%s Registers (0-7) */
#define R_MFWD_FWCTTC1_OFFSET(m)                  (0x0000040c + ((m) * 0x00000040))  /* Cut-Through Target Configuration Register 1%s */
/* FWCTTC20%s Registers (0-7) */
#define R_MFWD_FWCTTC20_OFFSET(m)                 (0x00000410 + ((m) * 0x00000040))  /* Cut-Through Target Configuration Register 20%s */
/* FWCTSC0%s Registers (0-7) */
#define R_MFWD_FWCTSC0_OFFSET(m)                  (0x00000420 + ((m) * 0x00000040))  /* Cut-Through Separation Configuration Register 0%s */
/* FWCTSC1%s Registers (0-7) */
#define R_MFWD_FWCTSC1_OFFSET(m)                  (0x00000424 + ((m) * 0x00000040))  /* Cut-Through Separation Configuration Register 1%s */
/* FWCTSC2%s Registers (0-7) */
#define R_MFWD_FWCTSC2_OFFSET(m)                  (0x00000428 + ((m) * 0x00000040))  /* Cut-Through Separation Configuration Register 2%s */
/* FWCTSC3%s Registers (0-7) */
#define R_MFWD_FWCTSC3_OFFSET(m)                  (0x0000042c + ((m) * 0x00000040))  /* Cut-Through Separation Configuration Register 3%s */
/* FWCTSC4%s Registers (0-7) */
#define R_MFWD_FWCTSC4_OFFSET(m)                  (0x00000430 + ((m) * 0x00000040))  /* Cut-Through Separation Configuration Register 4%s */
/* FWTWBFC%s Registers (0-15) */
#define R_MFWD_FWTWBFC_OFFSET(m)                  (0x00001000 + ((m) * 0x00000010))  /* Two-Byte Filter Configuration Register %s */
/* FWTWBFVC%s Registers (0-15) */
#define R_MFWD_FWTWBFVC_OFFSET(m)                 (0x00001004 + ((m) * 0x00000010))  /* Two-Byte Filter Value Configuration Register %s */
/* FWTHBFC%s Registers (0-15) */
#define R_MFWD_FWTHBFC_OFFSET(m)                  (0x00001400 + ((m) * 0x00000010))  /* Three-Byte Filter Configuration Register %s */
/* FWTHBFV0C%s Registers (0-15) */
#define R_MFWD_FWTHBFV0C_OFFSET(m)                (0x00001404 + ((m) * 0x00000010))  /* Three-Byte Filter Value 0 Configuration Register %s */
/* FWTHBFV1C%s Registers (0-15) */
#define R_MFWD_FWTHBFV1C_OFFSET(m)                (0x00001408 + ((m) * 0x00000010))  /* Three-Byte Filter Value 1 Configuration Register %s */
/* FWFOBFC%s Registers (0-15) */
#define R_MFWD_FWFOBFC_OFFSET(m)                  (0x00001800 + ((m) * 0x00000010))  /* Four-Byte Filter Configuration Register %s */
/* FWFOBFV0C%s Registers (0-15) */
#define R_MFWD_FWFOBFV0C_OFFSET(m)                (0x00001804 + ((m) * 0x00000010))  /* Four-Byte Filter Value 0 Configuration Register %s */
/* FWFOBFV1C%s Registers (0-15) */
#define R_MFWD_FWFOBFV1C_OFFSET(m)                (0x00001808 + ((m) * 0x00000010))  /* Four-Byte Filter Value 1 Configuration Register %s */
/* FWRFC%s Registers (0-1) */
#define R_MFWD_FWRFC_OFFSET(m)                    (0x00001c00 + ((m) * 0x00000010))  /* Range Filter Configuration Register %s */
/* FWRFVC%s Registers (0-1) */
#define R_MFWD_FWRFVC_OFFSET(m)                   (0x00001c04 + ((m) * 0x00000010))  /* Range Filter Value Configuration Register %s */
/* FWCFC%s Registers (0-15) */
#define R_MFWD_FWCFC_OFFSET(m)                    (0x00002000 + ((m) * 0x00000040))  /* Cascade Filter Configuration Register %s */
/* FWCFMC%s0 Registers (0-15) */
#define R_MFWD_FWCFMC0_OFFSET(m)                  (0x00002004 + ((m) * 0x00000040))  /* Cascade Filter Mapping Configuration Register %s0 */
/* FWCFMC%s1 Registers (0-15) */
#define R_MFWD_FWCFMC1_OFFSET(m)                  (0x00002008 + ((m) * 0x00000040))  /* Cascade Filter Mapping Configuration Register %s1 */
/* FWCFMC%s2 Registers (0-15) */
#define R_MFWD_FWCFMC2_OFFSET(m)                  (0x0000200c + ((m) * 0x00000040))  /* Cascade Filter Mapping Configuration Register %s2 */
/* FWCFMC%s3 Registers (0-15) */
#define R_MFWD_FWCFMC3_OFFSET(m)                  (0x00002010 + ((m) * 0x00000040))  /* Cascade Filter Mapping Configuration Register %s3 */
/* FWCFMC%s4 Registers (0-15) */
#define R_MFWD_FWCFMC4_OFFSET(m)                  (0x00002014 + ((m) * 0x00000040))  /* Cascade Filter Mapping Configuration Register %s4 */
/* FWCFMC%s5 Registers (0-15) */
#define R_MFWD_FWCFMC5_OFFSET(m)                  (0x00002018 + ((m) * 0x00000040))  /* Cascade Filter Mapping Configuration Register %s5 */
/* FWCFMC%s6 Registers (0-15) */
#define R_MFWD_FWCFMC6_OFFSET(m)                  (0x0000201c + ((m) * 0x00000040))  /* Cascade Filter Mapping Configuration Register %s6 */
#define R_MFWD_FWIP4SC_OFFSET                     0x00004008  /* IPv4 Stream Configuration Register */
#define R_MFWD_FWIP6SC_OFFSET                     0x00004018  /* IPv6 Stream Configuration Register */
#define R_MFWD_FWIP6OC_OFFSET                     0x0000401c  /* IPv6 Offset Configuration Register */
#define R_MFWD_FWL2SC_OFFSET                      0x00004020  /* Layer 2 Stream Configuration Register */
#define R_MFWD_FWSFHEC_OFFSET                     0x00004030  /* Stream Filter Hash Equation Configuration Register */
#define R_MFWD_FWSHCR0_OFFSET                     0x00004040  /* Software Hash Calculation Request Register 0 */
#define R_MFWD_FWSHCR1_OFFSET                     0x00004044  /* Software Hash Calculation Request Register 1 */
#define R_MFWD_FWSHCR2_OFFSET                     0x00004048  /* Software Hash Calculation Request Register 2 */
#define R_MFWD_FWSHCR3_OFFSET                     0x0000404c  /* Software Hash Calculation Request Register 3 */
#define R_MFWD_FWSHCR4_OFFSET                     0x00004050  /* Software Hash Calculation Request Register 4 */
#define R_MFWD_FWSHCR5_OFFSET                     0x00004054  /* Software Hash Calculation Request Register 5 */
#define R_MFWD_FWSHCR6_OFFSET                     0x00004058  /* Software Hash Calculation Request Register 6 */
#define R_MFWD_FWSHCR7_OFFSET                     0x0000405c  /* Software Hash Calculation Request Register 7 */
#define R_MFWD_FWSHCR8_OFFSET                     0x00004060  /* Software Hash Calculation Request Register 8 */
#define R_MFWD_FWSHCR9_OFFSET                     0x00004064  /* Software Hash Calculation Request Register 9 */
#define R_MFWD_FWSHCR10_OFFSET                    0x00004068  /* Software Hash Calculation Request Register 10 */
#define R_MFWD_FWSHCR11_OFFSET                    0x0000406c  /* Software Hash Calculation Request Register 11 */
#define R_MFWD_FWSHCR12_OFFSET                    0x00004070  /* Software Hash Calculation Request Register 12 */
#define R_MFWD_FWSHCR13_OFFSET                    0x00004074  /* Software Hash Calculation Request Register 13 */
#define R_MFWD_FWSHCRR_OFFSET                     0x00004078  /* Software Hash Calculation Request Result Register */
#define R_MFWD_FWLTHHEC_OFFSET                    0x00004090  /* L3 Hash Entry Configuration Register */
#define R_MFWD_FWLTHHC_OFFSET                     0x00004094  /* L3 Hash Configuration Register */
#define R_MFWD_FWLTHTL0_OFFSET                    0x000040a0  /* L3 Table Learn Register 0 */
#define R_MFWD_FWLTHTL1_OFFSET                    0x000040a4  /* L3 Table Learn Register 1 */
#define R_MFWD_FWLTHTL2_OFFSET                    0x000040a8  /* L3 Table Learn Register 2 */
#define R_MFWD_FWLTHTL3_OFFSET                    0x000040ac  /* L3 Table Learn Register 3 */
#define R_MFWD_FWLTHTL4_OFFSET                    0x000040b0  /* L3 Table Learn Register 4 */
#define R_MFWD_FWLTHTL5_OFFSET                    0x000040b4  /* L3 Table Learn Register 5 */
#define R_MFWD_FWLTHTL6_OFFSET                    0x000040b8  /* L3 Table Learn Register 6 */
#define R_MFWD_FWLTHTL7_OFFSET                    0x000040bc  /* L3 Table Learn Register 7 */
#define R_MFWD_FWLTHTL80_OFFSET                   0x000040c0  /* L3 Table Learn Register 80 */
#define R_MFWD_FWLTHTL9_OFFSET                    0x000040d0  /* L3 Table Learn Register 9 */
#define R_MFWD_FWLTHTLR_OFFSET                    0x000040d4  /* L3 Table Learn Result Register */
#define R_MFWD_FWLTHTIM_OFFSET                    0x000040e0  /* L3 Table Initialization Monitoring Register */
#define R_MFWD_FWLTHTEM_OFFSET                    0x000040e4  /* L3 Table Entry Monitoring Register */
#define R_MFWD_FWLTHTS0_OFFSET                    0x00004100  /* L3 Table Search Register 0 */
#define R_MFWD_FWLTHTS1_OFFSET                    0x00004104  /* L3 Table Search Register 1 */
#define R_MFWD_FWLTHTS2_OFFSET                    0x00004108  /* L3 Table Search Register 2 */
#define R_MFWD_FWLTHTS3_OFFSET                    0x0000410c  /* L3 Table Search Register 3 */
#define R_MFWD_FWLTHTS4_OFFSET                    0x00004110  /* L3 Table Search Register 4 */
#define R_MFWD_FWLTHTSR0_OFFSET                   0x00004120  /* L3 Table Search Result Register 0 */
#define R_MFWD_FWLTHTSR1_OFFSET                   0x00004124  /* L3 Table Search Result Register 1 */
#define R_MFWD_FWLTHTSR2_OFFSET                   0x00004128  /* L3 Table Search Result Register 2 */
#define R_MFWD_FWLTHTSR3_OFFSET                   0x0000412c  /* L3 Table Search Result Register 3 */
#define R_MFWD_FWLTHTSR40_OFFSET                  0x00004130  /* L3 Table Search Result Register 40 */
#define R_MFWD_FWLTHTSR5_OFFSET                   0x00004140  /* L3 Table Search Result Register 5 */
#define R_MFWD_FWLTHTR_OFFSET                     0x00004150  /* L3 Table Read Register */
#define R_MFWD_FWLTHTRR0_OFFSET                   0x00004154  /* L3 Table Read Result Register 0 */
#define R_MFWD_FWLTHTRR1_OFFSET                   0x00004158  /* L3 Table Read Result Register 1 */
#define R_MFWD_FWLTHTRR2_OFFSET                   0x0000415c  /* L3 Table Read Result Register 2 */
#define R_MFWD_FWLTHTRR3_OFFSET                   0x00004160  /* L3 Table Read Result Register 3 */
#define R_MFWD_FWLTHTRR4_OFFSET                   0x00004164  /* L3 Table Read Result Register 4 */
#define R_MFWD_FWLTHTRR5_OFFSET                   0x00004168  /* L3 Table Read Result Register 5 */
#define R_MFWD_FWLTHTRR6_OFFSET                   0x0000416c  /* L3 Table Read Result Register 6 */
#define R_MFWD_FWLTHTRR7_OFFSET                   0x00004170  /* L3 Table Read Result Register 7 */
#define R_MFWD_FWLTHTRR8_OFFSET                   0x00004174  /* L3 Table Read Result Register 8 */
#define R_MFWD_FWLTHTRR90_OFFSET                  0x00004180  /* L3 Table Read Result Register 90 */
#define R_MFWD_FWLTHTRR10_OFFSET                  0x00004190  /* L3 Table Read Result Register 10 */
#define R_MFWD_FWMACHEC_OFFSET                    0x00004620  /* MAC Hash Entry Configuration Register */
#define R_MFWD_FWMACHC_OFFSET                     0x00004624  /* MAC Hash Configuration Register */
#define R_MFWD_FWMACTL0_OFFSET                    0x00004630  /* MAC Table Learn Register 0 */
#define R_MFWD_FWMACTL1_OFFSET                    0x00004634  /* MAC Table Learn Register 1 */
#define R_MFWD_FWMACTL2_OFFSET                    0x00004638  /* MAC Table Learn Register 2 */
#define R_MFWD_FWMACTL3_OFFSET                    0x0000463c  /* MAC Table Learn Register 3 */
#define R_MFWD_FWMACTL40_OFFSET                   0x00004640  /* MAC Table Learn Register 40 */
#define R_MFWD_FWMACTL5_OFFSET                    0x00004650  /* MAC Table Learn Register 5 */
#define R_MFWD_FWMACTLR_OFFSET                    0x00004654  /* MAC Table Learn Result Register */
#define R_MFWD_FWMACTIM_OFFSET                    0x00004660  /* MAC Table Initialization Monitoring Register */
#define R_MFWD_FWMACTEM_OFFSET                    0x00004664  /* MAC Table Entry Monitoring Register */
#define R_MFWD_FWMACTS0_OFFSET                    0x00004670  /* MAC Table Search Register 0 */
#define R_MFWD_FWMACTS1_OFFSET                    0x00004674  /* MAC Table Search Register 1 */
#define R_MFWD_FWMACTSR0_OFFSET                   0x00004678  /* MAC Table Search Result Register 0 */
#define R_MFWD_FWMACTSR1_OFFSET                   0x0000467c  /* MAC Table Search Result Register 1 */
#define R_MFWD_FWMACTSR20_OFFSET                  0x00004680  /* MAC Table Search Result Register 20 */
#define R_MFWD_FWMACTSR3_OFFSET                   0x00004690  /* MAC Table Search Result Register 3 */
#define R_MFWD_FWMACTR_OFFSET                     0x000046a0  /* MAC Table Read Register */
#define R_MFWD_FWMACTRR0_OFFSET                   0x000046a4  /* MAC Table Read Result Register 0 */
#define R_MFWD_FWMACTRR1_OFFSET                   0x000046a8  /* MAC Table Read Result Register 1 */
#define R_MFWD_FWMACTRR2_OFFSET                   0x000046ac  /* MAC Table Read Result Register 2 */
#define R_MFWD_FWMACTRR3_OFFSET                   0x000046b0  /* MAC Table Read Result Register 3 */
#define R_MFWD_FWMACTRR4_OFFSET                   0x000046b4  /* MAC Table Read Result Register 4 */
#define R_MFWD_FWMACTRR50_OFFSET                  0x000046c0  /* MAC Table Read Result Register 50 */
#define R_MFWD_FWMACTRR6_OFFSET                   0x000046d0  /* MAC Table Read Result Register 6 */
#define R_MFWD_FWMACAGUSPC_OFFSET                 0x00004880  /* MAC Aging US Prescaler Configuration Register */
#define R_MFWD_FWMACAGC_OFFSET                    0x00004884  /* MAC Aging Configuration Register */
#define R_MFWD_FWMACAGM0_OFFSET                   0x00004888  /* MAC Aging Monitoring Register 0 */
#define R_MFWD_FWMACAGM1_OFFSET                   0x0000488c  /* MAC Aging Monitoring Register 1 */
#define R_MFWD_FWVLANTEC_OFFSET                   0x00004900  /* VLAN Table Entry Configuration Register */
#define R_MFWD_FWVLANTL0_OFFSET                   0x00004910  /* VLAN Table Learn Register 0 */
#define R_MFWD_FWVLANTL1_OFFSET                   0x00004914  /* VLAN Table Learn Register 1 */
#define R_MFWD_FWVLANTL2_OFFSET                   0x00004918  /* VLAN Table Learn Register 2 */
#define R_MFWD_FWVLANTL30_OFFSET                  0x00004920  /* VLAN Table Learn Register 30 */
#define R_MFWD_FWVLANTL4_OFFSET                   0x00004930  /* VLAN Table Learn Register 4 */
#define R_MFWD_FWVLANTLR_OFFSET                   0x00004934  /* VLAN Table Learn Result Register */
#define R_MFWD_FWVLANTIM_OFFSET                   0x00004940  /* VLAN Table Initialization Monitoring Register */
#define R_MFWD_FWVLANTEM_OFFSET                   0x00004944  /* VLAN Table Entry Monitoring Register */
#define R_MFWD_FWVLANTS_OFFSET                    0x00004950  /* VLAN Table Search Register */
#define R_MFWD_FWVLANTSR0_OFFSET                  0x00004954  /* VLAN Table Search Result Register 0 */
#define R_MFWD_FWVLANTSR1_OFFSET                  0x00004958  /* VLAN Table Search Result Register 1 */
#define R_MFWD_FWVLANTSR20_OFFSET                 0x00004960  /* VLAN Table Search Result Register 20 */
#define R_MFWD_FWVLANTSR3_OFFSET                  0x00004970  /* VLAN Table Search Result Register 3 */
/* FWPBFC%s Registers (0-2) */
#define R_MFWD_FWPBFC_OFFSET(m)                   (0x00004a00 + ((m) * 0x00000010))  /* Port Based Forwarding Configuration Register %s */
/* FWPBFCSDC0%s Registers (0-2) */
#define R_MFWD_FWPBFCSDC0_OFFSET(m)               (0x00004a04 + ((m) * 0x00000010))  /* Port Based Forwarding CSD Configuration Register 0%s */
#define R_MFWD_FWL23URL0_OFFSET                   0x00004e00  /* Layer 2/Layer 3 Update Rule Learn Register 0 */
#define R_MFWD_FWL23URL1_OFFSET                   0x00004e04  /* Layer 2/Layer 3 Update Rule Learn Register 1 */
#define R_MFWD_FWL23URL2_OFFSET                   0x00004e08  /* Layer 2/Layer 3 Update Rule Learn Register 2 */
#define R_MFWD_FWL23URL3_OFFSET                   0x00004e0c  /* Layer 2/Layer 3 Update Rule Learn Register 3 */
#define R_MFWD_FWL23URLR_OFFSET                   0x00004e10  /* Layer 2/Layer 3 Update Rule Learn Result Register */
#define R_MFWD_FWL23UTIM_OFFSET                   0x00004e20  /* Layer 2/Layer 3 Update Table Initialization Monitoring Register */
#define R_MFWD_FWL23URR_OFFSET                    0x00004e30  /* Layer 2/Layer 3 Update Rule Read Register */
#define R_MFWD_FWL23URRR0_OFFSET                  0x00004e34  /* Layer 2/Layer 3 Update Rule Read Result Register 0 */
#define R_MFWD_FWL23URRR1_OFFSET                  0x00004e38  /* Layer 2/Layer 3 Update Rule Read Result Register 1 */
#define R_MFWD_FWL23URRR2_OFFSET                  0x00004e3c  /* Layer 2/Layer 3 Update Rule Read Result Register 2 */
#define R_MFWD_FWL23URRR3_OFFSET                  0x00004e40  /* Layer 2/Layer 3 Update Rule Read Result Register 3 */
/* FWL23URMC%s Registers (0-31) */
#define R_MFWD_FWL23URMC_OFFSET(m)                (0x00004f00 + ((m) * 0x00000004))  /* Layer 2/Layer 3 Update ReMapping Configuration Register %s */
/* FWPMFGC%s Registers (0-15) */
#define R_MFWD_FWPMFGC_OFFSET(m)                  (0x00005000 + ((m) * 0x00000004))  /* PSFP MSDU Filter Global Configuration Register %s */
/* FWPMTRFC%s Registers (0-31) */
#define R_MFWD_FWPMTRFC_OFFSET(m)                 (0x00005600 + ((m) * 0x00000020))  /* PSFP Meter Filter Configuration Register %s */
/* FWPMTRCBSC%s Registers (0-31) */
#define R_MFWD_FWPMTRCBSC_OFFSET(m)               (0x00005604 + ((m) * 0x00000020))  /* PSFP Meter CBS Configuration Register %s */
/* FWPMTRCIRC%s Registers (0-31) */
#define R_MFWD_FWPMTRCIRC_OFFSET(m)               (0x00005608 + ((m) * 0x00000020))  /* PSFP Meter CIR Configuration Register %s */
/* FWPMTREBSC%s Registers (0-7) */
#define R_MFWD_FWPMTREBSC_OFFSET(m)               (0x0000560c + ((m) * 0x00000020))  /* PSFP Meter EBS Configuration Register %s */
/* FWPMTREIRC%s Registers (0-7) */
#define R_MFWD_FWPMTREIRC_OFFSET(m)               (0x00005610 + ((m) * 0x00000020))  /* PSFP Meter EIR Configuration Register %s */
/* FWPMTRFM%s Registers (0-31) */
#define R_MFWD_FWPMTRFM_OFFSET(m)                 (0x00005614 + ((m) * 0x00000020))  /* PSFP Meter Filter Monitoring Register %s */
#define R_MFWD_FWFTL0_OFFSET                      0x00006000  /* FRER Table Learn Register 0 */
#define R_MFWD_FWFTL1_OFFSET                      0x00006004  /* FRER Table Learn Register 1 */
#define R_MFWD_FWFTLR_OFFSET                      0x00006008  /* FRER Table Learn Result Register */
#define R_MFWD_FWFTOC_OFFSET                      0x00006010  /* FRER Timeout Configuration Register */
#define R_MFWD_FWFTOPC_OFFSET                     0x00006014  /* FRER Timeout Prescaler Configuration Register 0 */
#define R_MFWD_FWFTIM_OFFSET                      0x00006020  /* FRER Table Initialization Monitoring Register */
#define R_MFWD_FWFTR_OFFSET                       0x00006030  /* FRER Table Read Register */
#define R_MFWD_FWFTRR0_OFFSET                     0x00006034  /* FRER Table Read Result Register 0 */
#define R_MFWD_FWFTRR1_OFFSET                     0x00006038  /* FRER Table Read Result Register 1 */
#define R_MFWD_FWFTRR2_OFFSET                     0x0000603c  /* FRER Table Read Result Register 2 */
/* FWSEQNGC%s Registers (0-31) */
#define R_MFWD_FWSEQNGC_OFFSET(m)                 (0x00006100 + ((m) * 0x00000008))  /* Sequence Number Generation Configuration Register %s */
/* FWSEQNGM%s Registers (0-31) */
#define R_MFWD_FWSEQNGM_OFFSET(m)                 (0x00006104 + ((m) * 0x00000008))  /* Sequence Number Generation Monitoring Register %s */
#define R_MFWD_FWSEQNRC_OFFSET                    0x00006200  /* Sequence Number Reset Configuration Register */
/* FWCTFDCN%s Registers (0-1) */
#define R_MFWD_FWCTFDCN_OFFSET(m)                 (0x00006300 + ((m) * 0x00000020))  /* Cut-Through Forwarded Descriptor Counter Register %s */
/* FWLTHFDCN%s Registers (0-2) */
#define R_MFWD_FWLTHFDCN_OFFSET(m)                (0x00006304 + ((m) * 0x00000020))  /* Layer 3 Forwarded Descriptor Counter Register %s */
/* FWLTWFDCN%s Registers (0-2) */
#define R_MFWD_FWLTWFDCN_OFFSET(m)                (0x0000630c + ((m) * 0x00000020))  /* Layer 2 Forwarded Descriptor Counter Register %s */
/* FWPBFDCN%s Registers (0-2) */
#define R_MFWD_FWPBFDCN_OFFSET(m)                 (0x00006310 + ((m) * 0x00000020))  /* Port Based Forwarded Descriptor Counter Register %s */
/* FWMHLCN%s Registers (0-2) */
#define R_MFWD_FWMHLCN_OFFSET(m)                  (0x00006314 + ((m) * 0x00000020))  /* MAC Hardware Learn Counter Register %s */
#define R_MFWD_FWDDFDCN0_OFFSET                   0x00006340  /* Direct Descriptor Forwarded Descriptor Counter Register 0 */
/* FWWMRDCN%s Registers (0-2) */
#define R_MFWD_FWWMRDCN_OFFSET(m)                 (0x00006504 + ((m) * 0x00000020))  /* Watermark Rejected Descriptor Counter Register %s */
/* FWCTRDCN%s Registers (0-1) */
#define R_MFWD_FWCTRDCN_OFFSET(m)                 (0x00006508 + ((m) * 0x00000020))  /* Cut-Through Rejected Descriptor Counter Register %s */
/* FWLTHRDCN%s Registers (0-2) */
#define R_MFWD_FWLTHRDCN_OFFSET(m)                (0x0000650c + ((m) * 0x00000020))  /* Layer 3 Rejected Descriptor Counter Register %s */
/* FWLTWRDCN%s Registers (0-2) */
#define R_MFWD_FWLTWRDCN_OFFSET(m)                (0x00006514 + ((m) * 0x00000020))  /* Layer 2 Rejected Descriptor Counter Register %s */
/* FWPBRDCN%s Registers (0-2) */
#define R_MFWD_FWPBRDCN_OFFSET(m)                 (0x00006518 + ((m) * 0x00000020))  /* Port Based Rejected Descriptor Counter Register %s */
#define R_MFWD_FWDDRDCN0_OFFSET                   0x00006548  /* Direct Descriptor Rejected Descriptor Counter Register 0 */
/* FWPMFDCN%s Registers (0-15) */
#define R_MFWD_FWPMFDCN_OFFSET(m)                 (0x00006700 + ((m) * 0x00000004))  /* PSFP MSDU Filtered Descriptor Counter Register %s */
/* FWPMGDCN%s Registers (0-31) */
#define R_MFWD_FWPMGDCN_OFFSET(m)                 (0x00006800 + ((m) * 0x00000010))  /* PSFP Meter Green Descriptor Counter Register %s */
/* FWPMYDCN%s Registers (0-7) */
#define R_MFWD_FWPMYDCN_OFFSET(m)                 (0x00006804 + ((m) * 0x00000010))  /* PSFP Meter Yellow Descriptor Counter Register */
/* FWPMRDCN%s Registers (0-31) */
#define R_MFWD_FWPMRDCN_OFFSET(m)                 (0x00006808 + ((m) * 0x00000010))  /* PSFP Meter Red Descriptor Counter Register %s */
/* FWFRPPCN%s Registers (0-127) */
#define R_MFWD_FWFRPPCN_OFFSET(m)                 (0x00006a00 + ((m) * 0x00000008))  /* FRER Passed Packet Counter Register %s */
/* FWFRDPCN%s Registers (0-127) */
#define R_MFWD_FWFRDPCN_OFFSET(m)                 (0x00006a04 + ((m) * 0x00000008))  /* FRER Discarded Packet Counter Register %s */
/* FWEIS0%s Registers (0-2) */
#define R_MFWD_FWEIS0_OFFSET(m)                   (0x00007900 + ((m) * 0x00000010))  /* Error Interrupt Status Register 0%s */
/* FWEIE0%s Registers (0-2) */
#define R_MFWD_FWEIE0_OFFSET(m)                   (0x00007904 + ((m) * 0x00000010))  /* Error Interrupt Enable Register 0%s */
/* FWEID0%s Registers (0-2) */
#define R_MFWD_FWEID0_OFFSET(m)                   (0x00007908 + ((m) * 0x00000010))  /* Error Interrupt Disable Register 0%s */
#define R_MFWD_FWEIS1_OFFSET                      0x00007a00  /* Error Interrupt Status Register 1 */
#define R_MFWD_FWEIE1_OFFSET                      0x00007a04  /* Error Interrupt Enable Register 1 */
#define R_MFWD_FWEID1_OFFSET                      0x00007a08  /* Error Interrupt Disable Register 1 */
#define R_MFWD_FWEIS2_OFFSET                      0x00007a10  /* Error Interrupt Status Register 2 */
#define R_MFWD_FWEIE2_OFFSET                      0x00007a14  /* Error Interrupt Enable Register 2 */
#define R_MFWD_FWEID2_OFFSET                      0x00007a18  /* Error Interrupt Disable Register 2 */
#define R_MFWD_FWEIS5_OFFSET                      0x00007a40  /* Error Interrupt Status Register 5 */
#define R_MFWD_FWEIE5_OFFSET                      0x00007a44  /* Error Interrupt Enable Register 5 */
#define R_MFWD_FWEID5_OFFSET                      0x00007a48  /* Error Interrupt Disable Register 5 */
/* FWEIS6%s Registers (0-3) */
#define R_MFWD_FWEIS6_OFFSET(m)                   (0x00007a50 + ((m) * 0x00000010))  /* Error Interrupt Status Register 6%s */
/* FWEIE6%s Registers (0-3) */
#define R_MFWD_FWEIE6_OFFSET(m)                   (0x00007a54 + ((m) * 0x00000010))  /* Error Interrupt Enable Register 6%s */
/* FWEID6%s Registers (0-3) */
#define R_MFWD_FWEID6_OFFSET(m)                   (0x00007a58 + ((m) * 0x00000010))  /* Error Interrupt Disable Register 6%s */
/* FWEIS7%s Registers (0-3) */
#define R_MFWD_FWEIS7_OFFSET(m)                   (0x00007a90 + ((m) * 0x00000010))  /* Error Interrupt Status Register 7%s */
/* FWEIE7%s Registers (0-3) */
#define R_MFWD_FWEIE7_OFFSET(m)                   (0x00007a94 + ((m) * 0x00000010))  /* Error Interrupt Enable Register 7%s */
/* FWEID7%s Registers (0-3) */
#define R_MFWD_FWEID7_OFFSET(m)                   (0x00007a98 + ((m) * 0x00000010))  /* Error Interrupt Disable Register 7%s */
/* FWEIS8%s Registers (0-3) */
#define R_MFWD_FWEIS8_OFFSET(m)                   (0x00007ad0 + ((m) * 0x00000010))  /* Error Interrupt Status Register 8%s */
/* FWEIE8%s Registers (0-3) */
#define R_MFWD_FWEIE8_OFFSET(m)                   (0x00007ad4 + ((m) * 0x00000010))  /* Error Interrupt Enable Register 8%s */
/* FWEID8%s Registers (0-3) */
#define R_MFWD_FWEID8_OFFSET(m)                   (0x00007ad8 + ((m) * 0x00000010))  /* Error Interrupt Disable Register 8%s */
#define R_MFWD_FWMIS0_OFFSET                      0x00007c00  /* Monitoring Interrupt Status Register 0 */
#define R_MFWD_FWMIE0_OFFSET                      0x00007c04  /* Monitoring Interrupt Enable Register 0 */
#define R_MFWD_FWMID0_OFFSET                      0x00007c08  /* Monitoring Interrupt Disable Register 0 */

/* MFWD Register Addresses */

#define R_MFWD_FWGC                               (R_MFWD_BASE + R_MFWD_FWGC_OFFSET)
#define R_MFWD_FWTTC0                             (R_MFWD_BASE + R_MFWD_FWTTC0_OFFSET)
#define R_MFWD_FWTTC1                             (R_MFWD_BASE + R_MFWD_FWTTC1_OFFSET)
#define R_MFWD_FWCEPTC                            (R_MFWD_BASE + R_MFWD_FWCEPTC_OFFSET)
#define R_MFWD_FWCEPRC0                           (R_MFWD_BASE + R_MFWD_FWCEPRC0_OFFSET)
#define R_MFWD_FWCEPRC1                           (R_MFWD_BASE + R_MFWD_FWCEPRC1_OFFSET)
#define R_MFWD_FWCEPRC2                           (R_MFWD_BASE + R_MFWD_FWCEPRC2_OFFSET)
#define R_MFWD_FWCLPTC                            (R_MFWD_BASE + R_MFWD_FWCLPTC_OFFSET)
#define R_MFWD_FWCLPRC                            (R_MFWD_BASE + R_MFWD_FWCLPRC_OFFSET)
#define R_MFWD_FWCMPTC                            (R_MFWD_BASE + R_MFWD_FWCMPTC_OFFSET)
#define R_MFWD_FWEMPTC                            (R_MFWD_BASE + R_MFWD_FWEMPTC_OFFSET)
#define R_MFWD_FWSDMPTC                           (R_MFWD_BASE + R_MFWD_FWSDMPTC_OFFSET)
#define R_MFWD_FWSDMPVC                           (R_MFWD_BASE + R_MFWD_FWSDMPVC_OFFSET)
#define R_MFWD_FWLBWMC(m)                         (R_MFWD_BASE + R_MFWD_FWLBWMC_OFFSET(m))
#define R_MFWD_FWPC0(m)                           (R_MFWD_BASE + R_MFWD_FWPC0_OFFSET(m))
#define R_MFWD_FWPC1(m)                           (R_MFWD_BASE + R_MFWD_FWPC1_OFFSET(m))
#define R_MFWD_FWPC2(m)                           (R_MFWD_BASE + R_MFWD_FWPC2_OFFSET(m))
#define R_MFWD_FWCTGC0(m)                         (R_MFWD_BASE + R_MFWD_FWCTGC0_OFFSET(m))
#define R_MFWD_FWCTGC1(m)                         (R_MFWD_BASE + R_MFWD_FWCTGC1_OFFSET(m))
#define R_MFWD_FWCTTC0(m)                         (R_MFWD_BASE + R_MFWD_FWCTTC0_OFFSET(m))
#define R_MFWD_FWCTTC1(m)                         (R_MFWD_BASE + R_MFWD_FWCTTC1_OFFSET(m))
#define R_MFWD_FWCTTC20(m)                        (R_MFWD_BASE + R_MFWD_FWCTTC20_OFFSET(m))
#define R_MFWD_FWCTSC0(m)                         (R_MFWD_BASE + R_MFWD_FWCTSC0_OFFSET(m))
#define R_MFWD_FWCTSC1(m)                         (R_MFWD_BASE + R_MFWD_FWCTSC1_OFFSET(m))
#define R_MFWD_FWCTSC2(m)                         (R_MFWD_BASE + R_MFWD_FWCTSC2_OFFSET(m))
#define R_MFWD_FWCTSC3(m)                         (R_MFWD_BASE + R_MFWD_FWCTSC3_OFFSET(m))
#define R_MFWD_FWCTSC4(m)                         (R_MFWD_BASE + R_MFWD_FWCTSC4_OFFSET(m))
#define R_MFWD_FWTWBFC(m)                         (R_MFWD_BASE + R_MFWD_FWTWBFC_OFFSET(m))
#define R_MFWD_FWTWBFVC(m)                        (R_MFWD_BASE + R_MFWD_FWTWBFVC_OFFSET(m))
#define R_MFWD_FWTHBFC(m)                         (R_MFWD_BASE + R_MFWD_FWTHBFC_OFFSET(m))
#define R_MFWD_FWTHBFV0C(m)                       (R_MFWD_BASE + R_MFWD_FWTHBFV0C_OFFSET(m))
#define R_MFWD_FWTHBFV1C(m)                       (R_MFWD_BASE + R_MFWD_FWTHBFV1C_OFFSET(m))
#define R_MFWD_FWFOBFC(m)                         (R_MFWD_BASE + R_MFWD_FWFOBFC_OFFSET(m))
#define R_MFWD_FWFOBFV0C(m)                       (R_MFWD_BASE + R_MFWD_FWFOBFV0C_OFFSET(m))
#define R_MFWD_FWFOBFV1C(m)                       (R_MFWD_BASE + R_MFWD_FWFOBFV1C_OFFSET(m))
#define R_MFWD_FWRFC(m)                           (R_MFWD_BASE + R_MFWD_FWRFC_OFFSET(m))
#define R_MFWD_FWRFVC(m)                          (R_MFWD_BASE + R_MFWD_FWRFVC_OFFSET(m))
#define R_MFWD_FWCFC(m)                           (R_MFWD_BASE + R_MFWD_FWCFC_OFFSET(m))
#define R_MFWD_FWCFMC0(m)                         (R_MFWD_BASE + R_MFWD_FWCFMC0_OFFSET(m))
#define R_MFWD_FWCFMC1(m)                         (R_MFWD_BASE + R_MFWD_FWCFMC1_OFFSET(m))
#define R_MFWD_FWCFMC2(m)                         (R_MFWD_BASE + R_MFWD_FWCFMC2_OFFSET(m))
#define R_MFWD_FWCFMC3(m)                         (R_MFWD_BASE + R_MFWD_FWCFMC3_OFFSET(m))
#define R_MFWD_FWCFMC4(m)                         (R_MFWD_BASE + R_MFWD_FWCFMC4_OFFSET(m))
#define R_MFWD_FWCFMC5(m)                         (R_MFWD_BASE + R_MFWD_FWCFMC5_OFFSET(m))
#define R_MFWD_FWCFMC6(m)                         (R_MFWD_BASE + R_MFWD_FWCFMC6_OFFSET(m))
#define R_MFWD_FWIP4SC                            (R_MFWD_BASE + R_MFWD_FWIP4SC_OFFSET)
#define R_MFWD_FWIP6SC                            (R_MFWD_BASE + R_MFWD_FWIP6SC_OFFSET)
#define R_MFWD_FWIP6OC                            (R_MFWD_BASE + R_MFWD_FWIP6OC_OFFSET)
#define R_MFWD_FWL2SC                             (R_MFWD_BASE + R_MFWD_FWL2SC_OFFSET)
#define R_MFWD_FWSFHEC                            (R_MFWD_BASE + R_MFWD_FWSFHEC_OFFSET)
#define R_MFWD_FWSHCR0                            (R_MFWD_BASE + R_MFWD_FWSHCR0_OFFSET)
#define R_MFWD_FWSHCR1                            (R_MFWD_BASE + R_MFWD_FWSHCR1_OFFSET)
#define R_MFWD_FWSHCR2                            (R_MFWD_BASE + R_MFWD_FWSHCR2_OFFSET)
#define R_MFWD_FWSHCR3                            (R_MFWD_BASE + R_MFWD_FWSHCR3_OFFSET)
#define R_MFWD_FWSHCR4                            (R_MFWD_BASE + R_MFWD_FWSHCR4_OFFSET)
#define R_MFWD_FWSHCR5                            (R_MFWD_BASE + R_MFWD_FWSHCR5_OFFSET)
#define R_MFWD_FWSHCR6                            (R_MFWD_BASE + R_MFWD_FWSHCR6_OFFSET)
#define R_MFWD_FWSHCR7                            (R_MFWD_BASE + R_MFWD_FWSHCR7_OFFSET)
#define R_MFWD_FWSHCR8                            (R_MFWD_BASE + R_MFWD_FWSHCR8_OFFSET)
#define R_MFWD_FWSHCR9                            (R_MFWD_BASE + R_MFWD_FWSHCR9_OFFSET)
#define R_MFWD_FWSHCR10                           (R_MFWD_BASE + R_MFWD_FWSHCR10_OFFSET)
#define R_MFWD_FWSHCR11                           (R_MFWD_BASE + R_MFWD_FWSHCR11_OFFSET)
#define R_MFWD_FWSHCR12                           (R_MFWD_BASE + R_MFWD_FWSHCR12_OFFSET)
#define R_MFWD_FWSHCR13                           (R_MFWD_BASE + R_MFWD_FWSHCR13_OFFSET)
#define R_MFWD_FWSHCRR                            (R_MFWD_BASE + R_MFWD_FWSHCRR_OFFSET)
#define R_MFWD_FWLTHHEC                           (R_MFWD_BASE + R_MFWD_FWLTHHEC_OFFSET)
#define R_MFWD_FWLTHHC                            (R_MFWD_BASE + R_MFWD_FWLTHHC_OFFSET)
#define R_MFWD_FWLTHTL0                           (R_MFWD_BASE + R_MFWD_FWLTHTL0_OFFSET)
#define R_MFWD_FWLTHTL1                           (R_MFWD_BASE + R_MFWD_FWLTHTL1_OFFSET)
#define R_MFWD_FWLTHTL2                           (R_MFWD_BASE + R_MFWD_FWLTHTL2_OFFSET)
#define R_MFWD_FWLTHTL3                           (R_MFWD_BASE + R_MFWD_FWLTHTL3_OFFSET)
#define R_MFWD_FWLTHTL4                           (R_MFWD_BASE + R_MFWD_FWLTHTL4_OFFSET)
#define R_MFWD_FWLTHTL5                           (R_MFWD_BASE + R_MFWD_FWLTHTL5_OFFSET)
#define R_MFWD_FWLTHTL6                           (R_MFWD_BASE + R_MFWD_FWLTHTL6_OFFSET)
#define R_MFWD_FWLTHTL7                           (R_MFWD_BASE + R_MFWD_FWLTHTL7_OFFSET)
#define R_MFWD_FWLTHTL80                          (R_MFWD_BASE + R_MFWD_FWLTHTL80_OFFSET)
#define R_MFWD_FWLTHTL9                           (R_MFWD_BASE + R_MFWD_FWLTHTL9_OFFSET)
#define R_MFWD_FWLTHTLR                           (R_MFWD_BASE + R_MFWD_FWLTHTLR_OFFSET)
#define R_MFWD_FWLTHTIM                           (R_MFWD_BASE + R_MFWD_FWLTHTIM_OFFSET)
#define R_MFWD_FWLTHTEM                           (R_MFWD_BASE + R_MFWD_FWLTHTEM_OFFSET)
#define R_MFWD_FWLTHTS0                           (R_MFWD_BASE + R_MFWD_FWLTHTS0_OFFSET)
#define R_MFWD_FWLTHTS1                           (R_MFWD_BASE + R_MFWD_FWLTHTS1_OFFSET)
#define R_MFWD_FWLTHTS2                           (R_MFWD_BASE + R_MFWD_FWLTHTS2_OFFSET)
#define R_MFWD_FWLTHTS3                           (R_MFWD_BASE + R_MFWD_FWLTHTS3_OFFSET)
#define R_MFWD_FWLTHTS4                           (R_MFWD_BASE + R_MFWD_FWLTHTS4_OFFSET)
#define R_MFWD_FWLTHTSR0                          (R_MFWD_BASE + R_MFWD_FWLTHTSR0_OFFSET)
#define R_MFWD_FWLTHTSR1                          (R_MFWD_BASE + R_MFWD_FWLTHTSR1_OFFSET)
#define R_MFWD_FWLTHTSR2                          (R_MFWD_BASE + R_MFWD_FWLTHTSR2_OFFSET)
#define R_MFWD_FWLTHTSR3                          (R_MFWD_BASE + R_MFWD_FWLTHTSR3_OFFSET)
#define R_MFWD_FWLTHTSR40                         (R_MFWD_BASE + R_MFWD_FWLTHTSR40_OFFSET)
#define R_MFWD_FWLTHTSR5                          (R_MFWD_BASE + R_MFWD_FWLTHTSR5_OFFSET)
#define R_MFWD_FWLTHTR                            (R_MFWD_BASE + R_MFWD_FWLTHTR_OFFSET)
#define R_MFWD_FWLTHTRR0                          (R_MFWD_BASE + R_MFWD_FWLTHTRR0_OFFSET)
#define R_MFWD_FWLTHTRR1                          (R_MFWD_BASE + R_MFWD_FWLTHTRR1_OFFSET)
#define R_MFWD_FWLTHTRR2                          (R_MFWD_BASE + R_MFWD_FWLTHTRR2_OFFSET)
#define R_MFWD_FWLTHTRR3                          (R_MFWD_BASE + R_MFWD_FWLTHTRR3_OFFSET)
#define R_MFWD_FWLTHTRR4                          (R_MFWD_BASE + R_MFWD_FWLTHTRR4_OFFSET)
#define R_MFWD_FWLTHTRR5                          (R_MFWD_BASE + R_MFWD_FWLTHTRR5_OFFSET)
#define R_MFWD_FWLTHTRR6                          (R_MFWD_BASE + R_MFWD_FWLTHTRR6_OFFSET)
#define R_MFWD_FWLTHTRR7                          (R_MFWD_BASE + R_MFWD_FWLTHTRR7_OFFSET)
#define R_MFWD_FWLTHTRR8                          (R_MFWD_BASE + R_MFWD_FWLTHTRR8_OFFSET)
#define R_MFWD_FWLTHTRR90                         (R_MFWD_BASE + R_MFWD_FWLTHTRR90_OFFSET)
#define R_MFWD_FWLTHTRR10                         (R_MFWD_BASE + R_MFWD_FWLTHTRR10_OFFSET)
#define R_MFWD_FWMACHEC                           (R_MFWD_BASE + R_MFWD_FWMACHEC_OFFSET)
#define R_MFWD_FWMACHC                            (R_MFWD_BASE + R_MFWD_FWMACHC_OFFSET)
#define R_MFWD_FWMACTL0                           (R_MFWD_BASE + R_MFWD_FWMACTL0_OFFSET)
#define R_MFWD_FWMACTL1                           (R_MFWD_BASE + R_MFWD_FWMACTL1_OFFSET)
#define R_MFWD_FWMACTL2                           (R_MFWD_BASE + R_MFWD_FWMACTL2_OFFSET)
#define R_MFWD_FWMACTL3                           (R_MFWD_BASE + R_MFWD_FWMACTL3_OFFSET)
#define R_MFWD_FWMACTL40                          (R_MFWD_BASE + R_MFWD_FWMACTL40_OFFSET)
#define R_MFWD_FWMACTL5                           (R_MFWD_BASE + R_MFWD_FWMACTL5_OFFSET)
#define R_MFWD_FWMACTLR                           (R_MFWD_BASE + R_MFWD_FWMACTLR_OFFSET)
#define R_MFWD_FWMACTIM                           (R_MFWD_BASE + R_MFWD_FWMACTIM_OFFSET)
#define R_MFWD_FWMACTEM                           (R_MFWD_BASE + R_MFWD_FWMACTEM_OFFSET)
#define R_MFWD_FWMACTS0                           (R_MFWD_BASE + R_MFWD_FWMACTS0_OFFSET)
#define R_MFWD_FWMACTS1                           (R_MFWD_BASE + R_MFWD_FWMACTS1_OFFSET)
#define R_MFWD_FWMACTSR0                          (R_MFWD_BASE + R_MFWD_FWMACTSR0_OFFSET)
#define R_MFWD_FWMACTSR1                          (R_MFWD_BASE + R_MFWD_FWMACTSR1_OFFSET)
#define R_MFWD_FWMACTSR20                         (R_MFWD_BASE + R_MFWD_FWMACTSR20_OFFSET)
#define R_MFWD_FWMACTSR3                          (R_MFWD_BASE + R_MFWD_FWMACTSR3_OFFSET)
#define R_MFWD_FWMACTR                            (R_MFWD_BASE + R_MFWD_FWMACTR_OFFSET)
#define R_MFWD_FWMACTRR0                          (R_MFWD_BASE + R_MFWD_FWMACTRR0_OFFSET)
#define R_MFWD_FWMACTRR1                          (R_MFWD_BASE + R_MFWD_FWMACTRR1_OFFSET)
#define R_MFWD_FWMACTRR2                          (R_MFWD_BASE + R_MFWD_FWMACTRR2_OFFSET)
#define R_MFWD_FWMACTRR3                          (R_MFWD_BASE + R_MFWD_FWMACTRR3_OFFSET)
#define R_MFWD_FWMACTRR4                          (R_MFWD_BASE + R_MFWD_FWMACTRR4_OFFSET)
#define R_MFWD_FWMACTRR50                         (R_MFWD_BASE + R_MFWD_FWMACTRR50_OFFSET)
#define R_MFWD_FWMACTRR6                          (R_MFWD_BASE + R_MFWD_FWMACTRR6_OFFSET)
#define R_MFWD_FWMACAGUSPC                        (R_MFWD_BASE + R_MFWD_FWMACAGUSPC_OFFSET)
#define R_MFWD_FWMACAGC                           (R_MFWD_BASE + R_MFWD_FWMACAGC_OFFSET)
#define R_MFWD_FWMACAGM0                          (R_MFWD_BASE + R_MFWD_FWMACAGM0_OFFSET)
#define R_MFWD_FWMACAGM1                          (R_MFWD_BASE + R_MFWD_FWMACAGM1_OFFSET)
#define R_MFWD_FWVLANTEC                          (R_MFWD_BASE + R_MFWD_FWVLANTEC_OFFSET)
#define R_MFWD_FWVLANTL0                          (R_MFWD_BASE + R_MFWD_FWVLANTL0_OFFSET)
#define R_MFWD_FWVLANTL1                          (R_MFWD_BASE + R_MFWD_FWVLANTL1_OFFSET)
#define R_MFWD_FWVLANTL2                          (R_MFWD_BASE + R_MFWD_FWVLANTL2_OFFSET)
#define R_MFWD_FWVLANTL30                         (R_MFWD_BASE + R_MFWD_FWVLANTL30_OFFSET)
#define R_MFWD_FWVLANTL4                          (R_MFWD_BASE + R_MFWD_FWVLANTL4_OFFSET)
#define R_MFWD_FWVLANTLR                          (R_MFWD_BASE + R_MFWD_FWVLANTLR_OFFSET)
#define R_MFWD_FWVLANTIM                          (R_MFWD_BASE + R_MFWD_FWVLANTIM_OFFSET)
#define R_MFWD_FWVLANTEM                          (R_MFWD_BASE + R_MFWD_FWVLANTEM_OFFSET)
#define R_MFWD_FWVLANTS                           (R_MFWD_BASE + R_MFWD_FWVLANTS_OFFSET)
#define R_MFWD_FWVLANTSR0                         (R_MFWD_BASE + R_MFWD_FWVLANTSR0_OFFSET)
#define R_MFWD_FWVLANTSR1                         (R_MFWD_BASE + R_MFWD_FWVLANTSR1_OFFSET)
#define R_MFWD_FWVLANTSR20                        (R_MFWD_BASE + R_MFWD_FWVLANTSR20_OFFSET)
#define R_MFWD_FWVLANTSR3                         (R_MFWD_BASE + R_MFWD_FWVLANTSR3_OFFSET)
#define R_MFWD_FWPBFC(m)                          (R_MFWD_BASE + R_MFWD_FWPBFC_OFFSET(m))
#define R_MFWD_FWPBFCSDC0(m)                      (R_MFWD_BASE + R_MFWD_FWPBFCSDC0_OFFSET(m))
#define R_MFWD_FWL23URL0                          (R_MFWD_BASE + R_MFWD_FWL23URL0_OFFSET)
#define R_MFWD_FWL23URL1                          (R_MFWD_BASE + R_MFWD_FWL23URL1_OFFSET)
#define R_MFWD_FWL23URL2                          (R_MFWD_BASE + R_MFWD_FWL23URL2_OFFSET)
#define R_MFWD_FWL23URL3                          (R_MFWD_BASE + R_MFWD_FWL23URL3_OFFSET)
#define R_MFWD_FWL23URLR                          (R_MFWD_BASE + R_MFWD_FWL23URLR_OFFSET)
#define R_MFWD_FWL23UTIM                          (R_MFWD_BASE + R_MFWD_FWL23UTIM_OFFSET)
#define R_MFWD_FWL23URR                           (R_MFWD_BASE + R_MFWD_FWL23URR_OFFSET)
#define R_MFWD_FWL23URRR0                         (R_MFWD_BASE + R_MFWD_FWL23URRR0_OFFSET)
#define R_MFWD_FWL23URRR1                         (R_MFWD_BASE + R_MFWD_FWL23URRR1_OFFSET)
#define R_MFWD_FWL23URRR2                         (R_MFWD_BASE + R_MFWD_FWL23URRR2_OFFSET)
#define R_MFWD_FWL23URRR3                         (R_MFWD_BASE + R_MFWD_FWL23URRR3_OFFSET)
#define R_MFWD_FWL23URMC(m)                       (R_MFWD_BASE + R_MFWD_FWL23URMC_OFFSET(m))
#define R_MFWD_FWPMFGC(m)                         (R_MFWD_BASE + R_MFWD_FWPMFGC_OFFSET(m))
#define R_MFWD_FWPMTRFC(m)                        (R_MFWD_BASE + R_MFWD_FWPMTRFC_OFFSET(m))
#define R_MFWD_FWPMTRCBSC(m)                      (R_MFWD_BASE + R_MFWD_FWPMTRCBSC_OFFSET(m))
#define R_MFWD_FWPMTRCIRC(m)                      (R_MFWD_BASE + R_MFWD_FWPMTRCIRC_OFFSET(m))
#define R_MFWD_FWPMTREBSC(m)                      (R_MFWD_BASE + R_MFWD_FWPMTREBSC_OFFSET(m))
#define R_MFWD_FWPMTREIRC(m)                      (R_MFWD_BASE + R_MFWD_FWPMTREIRC_OFFSET(m))
#define R_MFWD_FWPMTRFM(m)                        (R_MFWD_BASE + R_MFWD_FWPMTRFM_OFFSET(m))
#define R_MFWD_FWFTL0                             (R_MFWD_BASE + R_MFWD_FWFTL0_OFFSET)
#define R_MFWD_FWFTL1                             (R_MFWD_BASE + R_MFWD_FWFTL1_OFFSET)
#define R_MFWD_FWFTLR                             (R_MFWD_BASE + R_MFWD_FWFTLR_OFFSET)
#define R_MFWD_FWFTOC                             (R_MFWD_BASE + R_MFWD_FWFTOC_OFFSET)
#define R_MFWD_FWFTOPC                            (R_MFWD_BASE + R_MFWD_FWFTOPC_OFFSET)
#define R_MFWD_FWFTIM                             (R_MFWD_BASE + R_MFWD_FWFTIM_OFFSET)
#define R_MFWD_FWFTR                              (R_MFWD_BASE + R_MFWD_FWFTR_OFFSET)
#define R_MFWD_FWFTRR0                            (R_MFWD_BASE + R_MFWD_FWFTRR0_OFFSET)
#define R_MFWD_FWFTRR1                            (R_MFWD_BASE + R_MFWD_FWFTRR1_OFFSET)
#define R_MFWD_FWFTRR2                            (R_MFWD_BASE + R_MFWD_FWFTRR2_OFFSET)
#define R_MFWD_FWSEQNGC(m)                        (R_MFWD_BASE + R_MFWD_FWSEQNGC_OFFSET(m))
#define R_MFWD_FWSEQNGM(m)                        (R_MFWD_BASE + R_MFWD_FWSEQNGM_OFFSET(m))
#define R_MFWD_FWSEQNRC                           (R_MFWD_BASE + R_MFWD_FWSEQNRC_OFFSET)
#define R_MFWD_FWCTFDCN(m)                        (R_MFWD_BASE + R_MFWD_FWCTFDCN_OFFSET(m))
#define R_MFWD_FWLTHFDCN(m)                       (R_MFWD_BASE + R_MFWD_FWLTHFDCN_OFFSET(m))
#define R_MFWD_FWLTWFDCN(m)                       (R_MFWD_BASE + R_MFWD_FWLTWFDCN_OFFSET(m))
#define R_MFWD_FWPBFDCN(m)                        (R_MFWD_BASE + R_MFWD_FWPBFDCN_OFFSET(m))
#define R_MFWD_FWMHLCN(m)                         (R_MFWD_BASE + R_MFWD_FWMHLCN_OFFSET(m))
#define R_MFWD_FWDDFDCN0                          (R_MFWD_BASE + R_MFWD_FWDDFDCN0_OFFSET)
#define R_MFWD_FWWMRDCN(m)                        (R_MFWD_BASE + R_MFWD_FWWMRDCN_OFFSET(m))
#define R_MFWD_FWCTRDCN(m)                        (R_MFWD_BASE + R_MFWD_FWCTRDCN_OFFSET(m))
#define R_MFWD_FWLTHRDCN(m)                       (R_MFWD_BASE + R_MFWD_FWLTHRDCN_OFFSET(m))
#define R_MFWD_FWLTWRDCN(m)                       (R_MFWD_BASE + R_MFWD_FWLTWRDCN_OFFSET(m))
#define R_MFWD_FWPBRDCN(m)                        (R_MFWD_BASE + R_MFWD_FWPBRDCN_OFFSET(m))
#define R_MFWD_FWDDRDCN0                          (R_MFWD_BASE + R_MFWD_FWDDRDCN0_OFFSET)
#define R_MFWD_FWPMFDCN(m)                        (R_MFWD_BASE + R_MFWD_FWPMFDCN_OFFSET(m))
#define R_MFWD_FWPMGDCN(m)                        (R_MFWD_BASE + R_MFWD_FWPMGDCN_OFFSET(m))
#define R_MFWD_FWPMYDCN(m)                        (R_MFWD_BASE + R_MFWD_FWPMYDCN_OFFSET(m))
#define R_MFWD_FWPMRDCN(m)                        (R_MFWD_BASE + R_MFWD_FWPMRDCN_OFFSET(m))
#define R_MFWD_FWFRPPCN(m)                        (R_MFWD_BASE + R_MFWD_FWFRPPCN_OFFSET(m))
#define R_MFWD_FWFRDPCN(m)                        (R_MFWD_BASE + R_MFWD_FWFRDPCN_OFFSET(m))
#define R_MFWD_FWEIS0(m)                          (R_MFWD_BASE + R_MFWD_FWEIS0_OFFSET(m))
#define R_MFWD_FWEIE0(m)                          (R_MFWD_BASE + R_MFWD_FWEIE0_OFFSET(m))
#define R_MFWD_FWEID0(m)                          (R_MFWD_BASE + R_MFWD_FWEID0_OFFSET(m))
#define R_MFWD_FWEIS1                             (R_MFWD_BASE + R_MFWD_FWEIS1_OFFSET)
#define R_MFWD_FWEIE1                             (R_MFWD_BASE + R_MFWD_FWEIE1_OFFSET)
#define R_MFWD_FWEID1                             (R_MFWD_BASE + R_MFWD_FWEID1_OFFSET)
#define R_MFWD_FWEIS2                             (R_MFWD_BASE + R_MFWD_FWEIS2_OFFSET)
#define R_MFWD_FWEIE2                             (R_MFWD_BASE + R_MFWD_FWEIE2_OFFSET)
#define R_MFWD_FWEID2                             (R_MFWD_BASE + R_MFWD_FWEID2_OFFSET)
#define R_MFWD_FWEIS5                             (R_MFWD_BASE + R_MFWD_FWEIS5_OFFSET)
#define R_MFWD_FWEIE5                             (R_MFWD_BASE + R_MFWD_FWEIE5_OFFSET)
#define R_MFWD_FWEID5                             (R_MFWD_BASE + R_MFWD_FWEID5_OFFSET)
#define R_MFWD_FWEIS6(m)                          (R_MFWD_BASE + R_MFWD_FWEIS6_OFFSET(m))
#define R_MFWD_FWEIE6(m)                          (R_MFWD_BASE + R_MFWD_FWEIE6_OFFSET(m))
#define R_MFWD_FWEID6(m)                          (R_MFWD_BASE + R_MFWD_FWEID6_OFFSET(m))
#define R_MFWD_FWEIS7(m)                          (R_MFWD_BASE + R_MFWD_FWEIS7_OFFSET(m))
#define R_MFWD_FWEIE7(m)                          (R_MFWD_BASE + R_MFWD_FWEIE7_OFFSET(m))
#define R_MFWD_FWEID7(m)                          (R_MFWD_BASE + R_MFWD_FWEID7_OFFSET(m))
#define R_MFWD_FWEIS8(m)                          (R_MFWD_BASE + R_MFWD_FWEIS8_OFFSET(m))
#define R_MFWD_FWEIE8(m)                          (R_MFWD_BASE + R_MFWD_FWEIE8_OFFSET(m))
#define R_MFWD_FWEID8(m)                          (R_MFWD_BASE + R_MFWD_FWEID8_OFFSET(m))
#define R_MFWD_FWMIS0                             (R_MFWD_BASE + R_MFWD_FWMIS0_OFFSET)
#define R_MFWD_FWMIE0                             (R_MFWD_BASE + R_MFWD_FWMIE0_OFFSET)
#define R_MFWD_FWMID0                             (R_MFWD_BASE + R_MFWD_FWMID0_OFFSET)

/* Register bit definitions */
/* FWGC Register bit definitions */
#define R_MFWD_FWGC_SVM_SHIFT                     (0)  /* Switch VLAN Mode */
#define R_MFWD_FWGC_SVM_MASK                      0x3
#  define R_MFWD_FWGC_SVM_00                              (0 << R_MFWD_FWGC_SVM_SHIFT)  /* No VLAN mode (VLAN not used for forwarding) */
#  define R_MFWD_FWGC_SVM_01                              (1 << R_MFWD_FWGC_SVM_SHIFT)  /* C-TAG mode (C-TAG used for forwarding) */
#  define R_MFWD_FWGC_SVM_10                              (2 << R_MFWD_FWGC_SVM_SHIFT)  /* SC-TAG mode (S-TAG used for forwarding) */
#  define R_MFWD_FWGC_SVM_11                              (3 << R_MFWD_FWGC_SVM_SHIFT)  /* Reserved */

/* FWTTC0 Register bit definitions */
#define R_MFWD_FWTTC0_CTT_SHIFT                   (0)  /* C-TAG TPID */
#define R_MFWD_FWTTC0_CTT_MASK                    0xffff

#define R_MFWD_FWTTC0_STT_SHIFT                   (16)  /* S-TAG TPID */
#define R_MFWD_FWTTC0_STT_MASK                    0xffff0000

/* FWTTC1 Register bit definitions */
#define R_MFWD_FWTTC1_RTT_SHIFT                   (0)  /* R-TAG TPID */
#define R_MFWD_FWTTC1_RTT_MASK                    0xffff

/* FWCEPTC Register bit definitions */
#define R_MFWD_FWCEPTC_EPCSD_SHIFT                (0)  /* Exceptional Path CPU Sub Destination */
#define R_MFWD_FWCEPTC_EPCSD_MASK                 0x7f

#define R_MFWD_FWCEPTC_EPIPV_SHIFT                (12)  /* Exceptional Path Internal Priority Value */
#define R_MFWD_FWCEPTC_EPIPV_MASK                 0x7000

#define R_MFWD_FWCEPTC_EPCS_SHIFT                 (16)  /* Exceptional Path CPU Select */
#define R_MFWD_FWCEPTC_EPCS_MASK                  0x30000

#define R_MFWD_FWCEPTC_EPSL                       (1 << 24)  /* Exceptional Path Security Level */

/* FWCEPRC0 Register bit definitions */
#define R_MFWD_FWCEPRC0_EPHYEEF                   (1 << 0)  /* Ethernet PHY Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_EPCRCEEF                  (1 << 1)  /* Ethernet PCH CRC Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_ENIBEEF                   (1 << 2)  /* Ethernet Nibble Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_EFCSEEF                   (1 << 3)  /* Ethernet FCS Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_EFFMEEF                   (1 << 4)  /* Ethernet Final Fragment Missing Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_ECFSEEF                   (1 << 5)  /* Ethernet C-Fragment SMD Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_ECFFCEEF                  (1 << 6)  /* Ethernet C-Fragment FRAG_COUNT Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_ERFFEF                    (1 << 7)  /* Ethernet RMAC Frame Filtered Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_ERPOOEF                   (1 << 8)  /* Ethernet Reception Partially Out of Operation Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_EBOEEF                    (1 << 9)  /* Ethernet Buffer Overflow Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_EUEEF                     (1 << 10)  /* Ethernet Undersize Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_EOEEF                     (1 << 11)  /* Ethernet Oversize Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_ETFEF                     (1 << 12)  /* Ethernet TAG Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_GAREEEF                   (1 << 16)  /* GWCA AXI RAM ECC Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_GAXEEF                    (1 << 17)  /* GWCA AXI Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_GSEQEEF                   (1 << 18)  /* GWCA Sequence Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_GTFEF                     (1 << 20)  /* GWCA TAG Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_GDNEEF                    (1 << 21)  /* GWCA Descriptor Number Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_DDEEF                     (1 << 24)  /* Direct Descriptor Error Exceptional Forwarding */

#define R_MFWD_FWCEPRC0_DDFSFEF                   (1 << 26)  /* Direct Descriptor Format Security Filtering Exceptional Forwarding */

/* FWCEPRC1 Register bit definitions */
#define R_MFWD_FWCEPRC1_FMSDUFEF                  (1 << 0)  /* MSDU Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC1_FMTRFEF                   (1 << 2)  /* Meter Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC1_FIFFEF                    (1 << 8)  /* Individual FRER Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC1_FSFFEF                    (1 << 9)  /* Sequence FRER Filtering Exceptional Forwarding */

/* FWCEPRC2 Register bit definitions */
#define R_MFWD_FWCEPRC2_FLTHUFEF                  (1 << 0)  /* Layer 3 Unknown Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FDMACUFEF                 (1 << 3)  /* Destination MAC Unknown Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FSMACUFEF                 (1 << 4)  /* Source MAC Unknown Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FVLANUFEF                 (1 << 5)  /* VLAN Unknown Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FDDNTFEF                  (1 << 8)  /* Direct Descriptor No Target Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FLTHNTFEF                 (1 << 9)  /* Layer 3 No Target Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FLTWNTFEF                 (1 << 11)  /* Layer 2 No Target Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FPBNTFEF                  (1 << 12)  /* Port Based No Target Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FLTHSLFEF                 (1 << 16)  /* Layer 3 Source Lock Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FDMACSLFEF                (1 << 19)  /* Destination MAC Source Lock Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FSMACSLFEF                (1 << 20)  /* Source MAC Source Lock Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FVLANSLFEF                (1 << 21)  /* VLAN Source Lock Filtering Exceptional Forwarding */

#define R_MFWD_FWCEPRC2_FWMFEF                    (1 << 26)  /* Watermark Filtering Exceptional Forwarding */

/* FWCLPTC Register bit definitions */
#define R_MFWD_FWCLPTC_LPCSD_SHIFT                (0)  /* Learning Path CPU Sub Destination */
#define R_MFWD_FWCLPTC_LPCSD_MASK                 0x7f

#define R_MFWD_FWCLPTC_LPIPV_SHIFT                (12)  /* Learning Path Internal Priority Value */
#define R_MFWD_FWCLPTC_LPIPV_MASK                 0x7000

#define R_MFWD_FWCLPTC_LPCS_SHIFT                 (16)  /* Learning Path CPU Select */
#define R_MFWD_FWCLPTC_LPCS_MASK                  0x30000

#define R_MFWD_FWCLPTC_LPSL                       (1 << 24)  /* Learning Path Security Level */

/* FWCLPRC Register bit definitions */
#define R_MFWD_FWCLPRC_USIDLF                     (1 << 0)  /* Unknown Stream ID Learning Forwarding */

#define R_MFWD_FWCLPRC_UDMACLF                    (1 << 4)  /* Unknown Destination MAC Learning Forwarding */

#define R_MFWD_FWCLPRC_USMACLF                    (1 << 5)  /* Unknown Source MAC Learning Forwarding */

#define R_MFWD_FWCLPRC_UPSMACLF                   (1 << 6)  /* Unknown Port for Source MAC Learning Forwarding */

#define R_MFWD_FWCLPRC_UVLANLF                    (1 << 7)  /* Unknown VLAN Learning Forwarding */

/* FWCMPTC Register bit definitions */
#define R_MFWD_FWCMPTC_CMPCSD_SHIFT               (0)  /* CPU Mirroring Path CPU Sub Destination */
#define R_MFWD_FWCMPTC_CMPCSD_MASK                0x7f

#define R_MFWD_FWCMPTC_CMPIPV_SHIFT               (12)  /* CPU Mirroring Path Internal Priority Value */
#define R_MFWD_FWCMPTC_CMPIPV_MASK                0x7000

#define R_MFWD_FWCMPTC_CMPIPU                     (1 << 15)  /* CPU Mirroring Path Internal Priority Update */

#define R_MFWD_FWCMPTC_CMPCS_SHIFT                (16)  /* CPU Mirroring Path CPU Select */
#define R_MFWD_FWCMPTC_CMPCS_MASK                 0x30000

#define R_MFWD_FWCMPTC_CMPSL                      (1 << 24)  /* CPU Mirroring Path Security Level */

/* FWEMPTC Register bit definitions */
#define R_MFWD_FWEMPTC_EMPIPV_SHIFT               (12)  /* Ethernet Mirroring Path Internal Priority Value */
#define R_MFWD_FWEMPTC_EMPIPV_MASK                0x7000

#define R_MFWD_FWEMPTC_EMPIPU                     (1 << 15)  /* Ethernet Mirroring Path Internal Priority Update */

#define R_MFWD_FWEMPTC_EMPPS_SHIFT                (16)  /* Ethernet Mirroring Path CPU Select */
#define R_MFWD_FWEMPTC_EMPPS_MASK                 0x30000

#define R_MFWD_FWEMPTC_EMPSL                      (1 << 24)  /* Ethernet Mirroring Path Security Level */

/* FWSDMPTC Register bit definitions */
#define R_MFWD_FWSDMPTC_SDMPCSD_SHIFT             (0)  /* Source-Destination Mirroring Path CPU Sub Destination */
#define R_MFWD_FWSDMPTC_SDMPCSD_MASK              0x7f

#define R_MFWD_FWSDMPTC_SDMPIPV_SHIFT             (12)  /* Source-Destination Mirroring Path Internal Priority Value */
#define R_MFWD_FWSDMPTC_SDMPIPV_MASK              0x7000

#define R_MFWD_FWSDMPTC_SDMPIPU                   (1 << 15)  /* Source-Destination Mirroring Path Internal Priority Update */

#define R_MFWD_FWSDMPTC_SDMPPS_SHIFT              (16)  /* Source-Destination Mirroring Path CPU Select */
#define R_MFWD_FWSDMPTC_SDMPPS_MASK               0x30000

#define R_MFWD_FWSDMPTC_SDMPSL                    (1 << 24)  /* Source-Destination Mirroring Path Security Level */

/* FWSDMPVC Register bit definitions */
#define R_MFWD_FWSDMPVC_SDMDV_SHIFT               (0)  /* Source-Destination Mirroring Destination Vector */
#define R_MFWD_FWSDMPVC_SDMDV_MASK                0x7f

#define R_MFWD_FWSDMPVC_SDMSV_SHIFT               (16)  /* Source-Destination Mirroring Source Vector */
#define R_MFWD_FWSDMPVC_SDMSV_MASK                0x7f0000

/* FWLBWMC Register bit definitions */
#define R_MFWD_FWLBWMC_WMCLPR_SHIFT               (0)  /* Watermark Critical Level Priority Rejected */
#define R_MFWD_FWLBWMC_WMCLPR_MASK                0xffff
#  define R_MFWD_FWLBWMC_WMCLPR_0                         (0 << R_MFWD_FWLBWMC_WMCLPR_SHIFT)  /* Frames coming for port i and that should be forwarded with {DEI,IPV} equal to j are forwarded. */
#  define R_MFWD_FWLBWMC_WMCLPR_1                         (1 << R_MFWD_FWLBWMC_WMCLPR_SHIFT)  /* Frames coming for port i and that should be forwarded with {DEI,IPV} equal to j are discarded when watermark critical level is set for port i (WM.CREITICAL[i] is set [COMA]). */

#define R_MFWD_FWLBWMC_WMFLPR_SHIFT               (16)  /* Watermark Flush Level Priority Rejected */
#define R_MFWD_FWLBWMC_WMFLPR_MASK                0xffff0000
#  define R_MFWD_FWLBWMC_WMFLPR_0                         (0 << R_MFWD_FWLBWMC_WMFLPR_SHIFT)  /* Frames coming for port i and that should be forwarded with {DEI,IPV} equal to j are forwarded. */
#  define R_MFWD_FWLBWMC_WMFLPR_1                         (1 << R_MFWD_FWLBWMC_WMFLPR_SHIFT)  /* Frames coming for port i and that should be forwarded with {DEI,IPV} equal to j are discarded when watermark flush level is set for port i (WM.FLUSH[i] is set [COMA]). */

/* FWPC Register bit definitions */
#define R_MFWD_FWPC_LTHTA                         (1 << 0)  /* L3 Table Active */

#define R_MFWD_FWPC_LTHRUS                        (1 << 1)  /* L3 Reject Unknown Streams */

#define R_MFWD_FWPC_LTHRUSS                       (1 << 2)  /* L3 Reject Unknown Secure Streams */

#define R_MFWD_FWPC_IP4UE                         (1 << 3)  /* IPv4 UDP Enabled */

#define R_MFWD_FWPC_IP4TE                         (1 << 4)  /* IPv4 TCP Enabled */

#define R_MFWD_FWPC_IP4OE                         (1 << 5)  /* IPv4 Other Enabled */

#define R_MFWD_FWPC_IP6UE                         (1 << 6)  /* IPv6 UDP Enabled */

#define R_MFWD_FWPC_IP6TE                         (1 << 7)  /* IPv6 TCP Enabled */

#define R_MFWD_FWPC_IP6OE                         (1 << 8)  /* IPv6 Other Enabled */

#define R_MFWD_FWPC_L2SE                          (1 << 9)  /* L2 Stream Enable */

#define R_MFWD_FWPC_MACDSA                        (1 << 20)  /* MAC Destination Search Active */

#define R_MFWD_FWPC_MACRUDA                       (1 << 21)  /* MAC Reject Unknown Destination Addresses */

#define R_MFWD_FWPC_MACRUDSA                      (1 << 22)  /* MAC Reject Unknown Destination Secure Addresses */

#define R_MFWD_FWPC_MACSSA                        (1 << 23)  /* MAC Source Search Active */

#define R_MFWD_FWPC_MACRUSA                       (1 << 24)  /* MAC Reject Unknown Source Addresses */

#define R_MFWD_FWPC_MACRUSSA                      (1 << 25)  /* MAC Reject Unknown Source Secure Addresses */

#define R_MFWD_FWPC_MACHLA                        (1 << 26)  /* MAC Hardware Learning Active */

#define R_MFWD_FWPC_MACHMA                        (1 << 27)  /* MAC Hardware Migration Active */

#define R_MFWD_FWPC_VLANSA                        (1 << 28)  /* VLAN Search Active */

#define R_MFWD_FWPC_VLANRU                        (1 << 29)  /* VLAN Reject Unknown */

#define R_MFWD_FWPC_VLANRUS                       (1 << 30)  /* VLAN Reject Unknown Secure */

/* FWPC Register bit definitions */
#define R_MFWD_FWPC_DDE                           (1 << 0)  /* Direct Descriptor Enable */

#define R_MFWD_FWPC_DDSL                          (1 << 1)  /* Direct Descriptor Security Level */

#define R_MFWD_FWPC_LTHFM_SHIFT                   (16)  /* Layer 3 Forwarding Mask */
#define R_MFWD_FWPC_LTHFM_MASK                    0x7f0000
#  define R_MFWD_FWPC_LTHFM_0                             (0 << R_MFWD_FWPC_LTHFM_SHIFT)  /* Frames forwarded by Layer 3 forwarding can be forwarded to port j. */
#  define R_MFWD_FWPC_LTHFM_1                             (1 << R_MFWD_FWPC_LTHFM_SHIFT)  /* Frames forwarded by Layer 3 forwarding cannot be forwarded to port j. */

/* FWPC Register bit definitions */
#define R_MFWD_FWPC_LTWFM_SHIFT                   (16)  /* Layer 2 Forwarding Mask */
#define R_MFWD_FWPC_LTWFM_MASK                    0x7f0000
#  define R_MFWD_FWPC_LTWFM_0                             (0 << R_MFWD_FWPC_LTWFM_SHIFT)  /* Frames forwarded by Layer 2 forwarding can be forwarded to port j. */
#  define R_MFWD_FWPC_LTWFM_1                             (1 << R_MFWD_FWPC_LTWFM_SHIFT)  /* Frames forwarded by Layer 2 forwarding cannot be forwarded to port j. */

/* FWCTGC Register bit definitions */
#define R_MFWD_FWCTGC_CTMDE                       (1 << 0)  /* Cut-Through MAC Destination Enable */

#define R_MFWD_FWCTGC_CTMSE                       (1 << 1)  /* Cut-Through MAC Source Enable */

#define R_MFWD_FWCTGC_CTCVE                       (1 << 2)  /* Cut-Through C-TAG VLAN Enable */

#define R_MFWD_FWCTGC_CTCPE                       (1 << 3)  /* Cut-Through C-TAG PCP Enable */

#define R_MFWD_FWCTGC_CTCDE                       (1 << 4)  /* Cut-Through C-TAG DEI Enable */

#define R_MFWD_FWCTGC_CTSVE                       (1 << 5)  /* Cut-Through S-TAG VLAN Enable */

#define R_MFWD_FWCTGC_CTSPE                       (1 << 6)  /* Cut-Through S-TAG PCP Enable */

#define R_MFWD_FWCTGC_CTSDE                       (1 << 7)  /* Cut-Through S-TAG DEI Enable */

#define R_MFWD_FWCTGC_CTETE                       (1 << 8)  /* Cut-Through Ethernet Type Enable */

#define R_MFWD_FWCTGC_CTFI                        (1 << 11)  /* Cut-Through FCS In */

#define R_MFWD_FWCTGC_CTVCTRL_SHIFT               (12)  /* Cut-Through VLAN Control [GWCA] [ETHA] */
#define R_MFWD_FWCTGC_CTVCTRL_MASK                0x3000
#  define R_MFWD_FWCTGC_CTVCTRL_00                        (0 << R_MFWD_FWCTGC_CTVCTRL_SHIFT)  /* The ingress matching separation rule i frame is a No TAG frame. */
#  define R_MFWD_FWCTGC_CTVCTRL_01                        (1 << R_MFWD_FWCTGC_CTVCTRL_SHIFT)  /* The ingress matching separation rule i frame is a C-TAG frame. */
#  define R_MFWD_FWCTGC_CTVCTRL_10                        (2 << R_MFWD_FWCTGC_CTVCTRL_SHIFT)  /* The ingress matching separation rule i frame is a SC-TAG frame. */
#  define R_MFWD_FWCTGC_CTVCTRL_11                        (3 << R_MFWD_FWCTGC_CTVCTRL_SHIFT)  /* The ingress matching separation rule i frame is a CoS TAG frame. */

#define R_MFWD_FWCTGC_CTRTGI                      (1 << 14)  /* Cut-Through R-TAG In [GWCA] [ETHA] */

/* FWCTGC Register bit definitions */
#define R_MFWD_FWCTGC_CTMT_SHIFT                  (0)  /* Cut-Through Maximum time */
#define R_MFWD_FWCTGC_CTMT_MASK                   0x3ffffff

/* FWCTTC Register bit definitions */
#define R_MFWD_FWCTTC_CTDV_SHIFT                  (0)  /* Cut-through Destination Vector */
#define R_MFWD_FWCTTC_CTDV_MASK                   0x7f

#define R_MFWD_FWCTTC_CTDFM_SHIFT                 (16)  /* Cut-through Destination Forwarding Mode */
#define R_MFWD_FWCTTC_CTDFM_MASK                  0xf0000
#  define R_MFWD_FWCTTC_CTDFM_0                           (0 << R_MFWD_FWCTTC_CTDFM_SHIFT)  /* Frame is forwarded in Cut-through mode. */
#  define R_MFWD_FWCTTC_CTDFM_1                           (1 << R_MFWD_FWCTTC_CTDFM_SHIFT)  /* Frame is forwarded in Store and forward mode. */

/* FWCTTC Register bit definitions */
#define R_MFWD_FWCTTC_CTIPV_SHIFT                 (12)  /* Cut-through Internal Priority Value */
#define R_MFWD_FWCTTC_CTIPV_MASK                  0x7000

#define R_MFWD_FWCTTC_CTIPU                       (1 << 15)  /* Cut-through Internal Priority Update */

#define R_MFWD_FWCTTC_CTCME                       (1 << 16)  /* Cut-through CPU Mirroring Enable */

#define R_MFWD_FWCTTC_CTEME                       (1 << 17)  /* Cut-through Ethernet Mirroring Enable */

/* FWCTTC Register bit definitions */
#define R_MFWD_FWCTTC_CTCSD_SHIFT                 (0)  /* Cut-Through CPU Sub Destination */
#define R_MFWD_FWCTTC_CTCSD_MASK                  0x7f

/* FWCTSC Register bit definitions */
#define R_MFWD_FWCTSC_CTDMAU_SHIFT                (0)  /* Cut-Through Destination MAC Address Upper Part */
#define R_MFWD_FWCTSC_CTDMAU_MASK                 0xffffffff

/* FWCTSC Register bit definitions */
#define R_MFWD_FWCTSC_CTSMAU_SHIFT                (0)  /* Cut-Through Source MAC Address Upper Part */
#define R_MFWD_FWCTSC_CTSMAU_MASK                 0xffff

#define R_MFWD_FWCTSC_CTDMAL_SHIFT                (16)  /* Cut-Through Destination MAC Address Lower Part */
#define R_MFWD_FWCTSC_CTDMAL_MASK                 0xffff0000

/* FWCTSC Register bit definitions */
#define R_MFWD_FWCTSC_CTSMAL_SHIFT                (0)  /* Cut-Through Source MAC Address Lower Part */
#define R_MFWD_FWCTSC_CTSMAL_MASK                 0xffffffff

/* FWCTSC Register bit definitions */
#define R_MFWD_FWCTSC_CTCV_SHIFT                  (0)  /* Cut-Through C-TAG VLAN */
#define R_MFWD_FWCTSC_CTCV_MASK                   0xfff

#define R_MFWD_FWCTSC_CTCP_SHIFT                  (12)  /* Cut-Through C-TAG PCP */
#define R_MFWD_FWCTSC_CTCP_MASK                   0x7000

#define R_MFWD_FWCTSC_CTCD                        (1 << 15)  /* Cut-Through C-TAG DEI */

#define R_MFWD_FWCTSC_CTSV_SHIFT                  (16)  /* Cut-Through S-TAG VLAN */
#define R_MFWD_FWCTSC_CTSV_MASK                   0xfff0000

#define R_MFWD_FWCTSC_CTSP_SHIFT                  (28)  /* Cut-Through S-TAG PCP */
#define R_MFWD_FWCTSC_CTSP_MASK                   0x70000000

#define R_MFWD_FWCTSC_CTSD                        (1 << 31)  /* Cut-Through S-TAG DEI */

/* FWCTSC Register bit definitions */
#define R_MFWD_FWCTSC_CTET_SHIFT                  (0)  /* Cut-Through Ethernet Type */
#define R_MFWD_FWCTSC_CTET_MASK                   0xffff

#define R_MFWD_FWCTSC_CTSPN_SHIFT                 (16)  /* Cut-Through Source Port Number */
#define R_MFWD_FWCTSC_CTSPN_MASK                  0x30000

/* FWTWBFC Register bit definitions */
#define R_MFWD_FWTWBFC_TWBFUM_SHIFT               (0)  /* Two-Byte Filter Unit Mode */
#define R_MFWD_FWTWBFC_TWBFUM_MASK                0x3
#  define R_MFWD_FWTWBFC_TWBFUM_00                        (0 << R_MFWD_FWTWBFC_TWBFUM_SHIFT)  /* Mask mode */
#  define R_MFWD_FWTWBFC_TWBFUM_01                        (1 << R_MFWD_FWTWBFC_TWBFUM_SHIFT)  /* Expand mode */
#  define R_MFWD_FWTWBFC_TWBFUM_10                        (2 << R_MFWD_FWTWBFC_TWBFUM_SHIFT)  /* Precise mode */
#  define R_MFWD_FWTWBFC_TWBFUM_11                        (3 << R_MFWD_FWTWBFC_TWBFUM_SHIFT)  /* Reserved */

#define R_MFWD_FWTWBFC_TWBFM                      (1 << 8)  /* Two-Byte Filtering Mode */

#define R_MFWD_FWTWBFC_TWBFOV_SHIFT               (16)  /* Two-Byte Filter Offset Value */
#define R_MFWD_FWTWBFC_TWBFOV_MASK                0xff0000

/* FWTWBFVC Register bit definitions */
#define R_MFWD_FWTWBFVC_TWBFV0_SHIFT              (0)  /* Two-Byte Filter Value 0 */
#define R_MFWD_FWTWBFVC_TWBFV0_MASK               0xffff

#define R_MFWD_FWTWBFVC_TWBFV1_SHIFT              (16)  /* Two-Byte Filter Value 1 */
#define R_MFWD_FWTWBFVC_TWBFV1_MASK               0xffff0000

/* FWTHBFC Register bit definitions */
#define R_MFWD_FWTHBFC_THBFUM_SHIFT               (0)  /* Three-Byte Filter Unit Mode */
#define R_MFWD_FWTHBFC_THBFUM_MASK                0x3
#  define R_MFWD_FWTHBFC_THBFUM_00                        (0 << R_MFWD_FWTHBFC_THBFUM_SHIFT)  /* Mask mode */
#  define R_MFWD_FWTHBFC_THBFUM_01                        (1 << R_MFWD_FWTHBFC_THBFUM_SHIFT)  /* Expand mode */
#  define R_MFWD_FWTHBFC_THBFUM_10                        (2 << R_MFWD_FWTHBFC_THBFUM_SHIFT)  /* Precise mode */
#  define R_MFWD_FWTHBFC_THBFUM_11                        (3 << R_MFWD_FWTHBFC_THBFUM_SHIFT)  /* Reserved */

#define R_MFWD_FWTHBFC_THBFOV_SHIFT               (16)  /* Three-Byte Filter Offset Value */
#define R_MFWD_FWTHBFC_THBFOV_MASK                0xff0000

/* FWTHBFV0C Register bit definitions */
#define R_MFWD_FWTHBFV0C_THBFV0_SHIFT             (0)  /* Three-Byte Filter Value 0 */
#define R_MFWD_FWTHBFV0C_THBFV0_MASK              0xffffff

/* FWTHBFV1C Register bit definitions */
#define R_MFWD_FWTHBFV1C_THBFV1_SHIFT             (0)  /* Three-Byte Filter Value 1 */
#define R_MFWD_FWTHBFV1C_THBFV1_MASK              0xffffff

/* FWFOBFC Register bit definitions */
#define R_MFWD_FWFOBFC_FOBFUM_SHIFT               (0)  /* Four-Byte Filter Unit Mode */
#define R_MFWD_FWFOBFC_FOBFUM_MASK                0x3
#  define R_MFWD_FWFOBFC_FOBFUM_00                        (0 << R_MFWD_FWFOBFC_FOBFUM_SHIFT)  /* Mask mode */
#  define R_MFWD_FWFOBFC_FOBFUM_01                        (1 << R_MFWD_FWFOBFC_FOBFUM_SHIFT)  /* Expand mode */
#  define R_MFWD_FWFOBFC_FOBFUM_10                        (2 << R_MFWD_FWFOBFC_FOBFUM_SHIFT)  /* Precise mode */
#  define R_MFWD_FWFOBFC_FOBFUM_11                        (3 << R_MFWD_FWFOBFC_FOBFUM_SHIFT)  /* Reserved */

#define R_MFWD_FWFOBFC_FOBFOV_SHIFT               (16)  /* Four-Byte Filter Offset Value */
#define R_MFWD_FWFOBFC_FOBFOV_MASK                0xff0000

/* FWFOBFV0C Register bit definitions */
#define R_MFWD_FWFOBFV0C_FOBFV0_SHIFT             (0)  /* Four-Byte Filter Value 0 */
#define R_MFWD_FWFOBFV0C_FOBFV0_MASK              0xffffffff

/* FWFOBFV1C Register bit definitions */
#define R_MFWD_FWFOBFV1C_FOBFV1_SHIFT             (0)  /* Four-Byte Filter Value 1 */
#define R_MFWD_FWFOBFV1C_FOBFV1_MASK              0xffffffff

/* FWRFC Register bit definitions */
#define R_MFWD_FWRFC_RFM                          (1 << 8)  /* Range Filtering Mode */

#define R_MFWD_FWRFC_RFOV_SHIFT                   (16)  /* Range Filter Offset Value */
#define R_MFWD_FWRFC_RFOV_MASK                    0xff0000

/* FWRFVC Register bit definitions */
#define R_MFWD_FWRFVC_RFSV_S_SHIFT                (0)  /* Range Filter Start Value %s */
#define R_MFWD_FWRFVC_RFSV_S_MASK                 0xff

#define R_MFWD_FWRFVC_RFRV_SHIFT                  (16)  /* Range Filter Range Value */
#define R_MFWD_FWRFVC_RFRV_MASK                   0xf0000

/* FWCFC Register bit definitions */
#define R_MFWD_FWCFC_CFEFFV_SHIFT                 (0)  /* Cascade Filter E-Frame Filter Valid */
#define R_MFWD_FWCFC_CFEFFV_MASK                  0x7f

#define R_MFWD_FWCFC_CFPFFV_SHIFT                 (16)  /* Cascade Filter P-Frame Filter Valid */
#define R_MFWD_FWCFC_CFPFFV_MASK                  0xf0000

/* FWCFMC Register bit definitions */
#define R_MFWD_FWCFMC_CFFN_SHIFT                  (0)  /* Cascade Filter Filter Number */
#define R_MFWD_FWCFMC_CFFN_MASK                   0x7f

#define R_MFWD_FWCFMC_CFFV                        (1 << 15)  /* Cascade Filter Valid */

/* FWCFMC Register bit definitions */
#define R_MFWD_FWCFMC_CFFN_SHIFT                  (0)  /* Cascade Filter Filter Number */
#define R_MFWD_FWCFMC_CFFN_MASK                   0x7f

#define R_MFWD_FWCFMC_CFFV                        (1 << 15)  /* Cascade Filter Valid */

/* FWCFMC Register bit definitions */
#define R_MFWD_FWCFMC_CFFN_SHIFT                  (0)  /* Cascade Filter Filter Number */
#define R_MFWD_FWCFMC_CFFN_MASK                   0x7f

#define R_MFWD_FWCFMC_CFFV                        (1 << 15)  /* Cascade Filter Valid */

/* FWCFMC Register bit definitions */
#define R_MFWD_FWCFMC_CFFN_SHIFT                  (0)  /* Cascade Filter Filter Number */
#define R_MFWD_FWCFMC_CFFN_MASK                   0x7f

#define R_MFWD_FWCFMC_CFFV                        (1 << 15)  /* Cascade Filter Valid */

/* FWCFMC Register bit definitions */
#define R_MFWD_FWCFMC_CFFN_SHIFT                  (0)  /* Cascade Filter Filter Number */
#define R_MFWD_FWCFMC_CFFN_MASK                   0x7f

#define R_MFWD_FWCFMC_CFFV                        (1 << 15)  /* Cascade Filter Valid */

/* FWCFMC Register bit definitions */
#define R_MFWD_FWCFMC_CFFN_SHIFT                  (0)  /* Cascade Filter Filter Number */
#define R_MFWD_FWCFMC_CFFN_MASK                   0x7f

#define R_MFWD_FWCFMC_CFFV                        (1 << 15)  /* Cascade Filter Valid */

/* FWCFMC Register bit definitions */
#define R_MFWD_FWCFMC_CFFN_SHIFT                  (0)  /* Cascade Filter Filter Number */
#define R_MFWD_FWCFMC_CFFN_MASK                   0x7f

#define R_MFWD_FWCFMC_CFFV                        (1 << 15)  /* Cascade Filter Valid */

/* FWIP4SC Register bit definitions */
#define R_MFWD_FWIP4SC_IP4IMDH                    (1 << 0)  /* IPv4 Include MAC Destination in Hash */

#define R_MFWD_FWIP4SC_IP4IMSH                    (1 << 1)  /* IPv4 Include MAC Source in Hash */

#define R_MFWD_FWIP4SC_IP4ISVH                    (1 << 2)  /* IPv4 Include S-TAG VLAN ID in Hash */

#define R_MFWD_FWIP4SC_IP4ISPH                    (1 << 3)  /* IPv4 Include S-TAG PCP in Hash */

#define R_MFWD_FWIP4SC_IP4ISDH                    (1 << 4)  /* IPv4 Include S-TAG DEI in Hash */

#define R_MFWD_FWIP4SC_IP4ICVH                    (1 << 5)  /* IPv4 Include C-TAG VLAN ID in Hash */

#define R_MFWD_FWIP4SC_IP4ICPH                    (1 << 6)  /* IPv4 Include C-TAG PCP in Hash */

#define R_MFWD_FWIP4SC_IP4ICDH                    (1 << 7)  /* IPv4 Include C-TAG DEI in Hash */

#define R_MFWD_FWIP4SC_IP4IISH                    (1 << 8)  /* IPv4 Include IP Source in Hash */

#define R_MFWD_FWIP4SC_IP4IIDH                    (1 << 9)  /* IPv4 Include IP Destination in Hash */

#define R_MFWD_FWIP4SC_IP4IPH                     (1 << 10)  /* IPv4 Include Protocol in Hash */

#define R_MFWD_FWIP4SC_IP4ISPTH                   (1 << 11)  /* IPv4 Include Source Port in Hash */

#define R_MFWD_FWIP4SC_IP4IDPTH                   (1 << 12)  /* IPv4 Include Destination Port in Hash */

#define R_MFWD_FWIP4SC_IP4ISVS                    (1 << 16)  /* IPv4 Include S-TAG VLAN ID in Stream */

#define R_MFWD_FWIP4SC_IP4ISPS                    (1 << 17)  /* IPv4 Include S-TAG PCP in Stream */

#define R_MFWD_FWIP4SC_IP4ISDS                    (1 << 18)  /* IPv4 Include S-TAG DEI in Stream */

#define R_MFWD_FWIP4SC_IP4ICVS                    (1 << 19)  /* IPv4 Include C-TAG VLAN ID in Stream */

#define R_MFWD_FWIP4SC_IP4ICPS                    (1 << 20)  /* IPv4 Include C-TAG PCP in Stream */

#define R_MFWD_FWIP4SC_IP4ICDS                    (1 << 21)  /* IPv4 Include C-TAG DEI in Stream */

#define R_MFWD_FWIP4SC_IP4IISS                    (1 << 22)  /* IPv4 Include IP Source in Stream */

#define R_MFWD_FWIP4SC_IP4IIDS                    (1 << 23)  /* IPv4 Include IP Destination in Stream */

#define R_MFWD_FWIP4SC_IP4IDPTS                   (1 << 24)  /* IPv4 Include Destination Port in Stream */

/* FWIP6SC Register bit definitions */
#define R_MFWD_FWIP6SC_IP6IMDH                    (1 << 0)  /* IPv6 Include MAC Destination in Hash */

#define R_MFWD_FWIP6SC_IP6IMSH                    (1 << 1)  /* IPv6 Include MAC Source in Hash */

#define R_MFWD_FWIP6SC_IP6ISVH                    (1 << 2)  /* IPv6 Include S-TAG VLAN ID in Hash */

#define R_MFWD_FWIP6SC_IP6ISPH                    (1 << 3)  /* IPv6 Include S-TAG PCP in Hash */

#define R_MFWD_FWIP6SC_IP6ISDH                    (1 << 4)  /* IPv6 Include S-TAG DEI in Hash */

#define R_MFWD_FWIP6SC_IP6ICVH                    (1 << 5)  /* IPv6 Include C-TAG VLAN ID in Hash */

#define R_MFWD_FWIP6SC_IP6ICPH                    (1 << 6)  /* IPv6 Include C-TAG PCP in Hash */

#define R_MFWD_FWIP6SC_IP6ICDH                    (1 << 7)  /* IPv6 Include C-TAG DEI in Hash */

#define R_MFWD_FWIP6SC_IP6IISH                    (1 << 8)  /* IPv6 Include IP Source in Hash */

#define R_MFWD_FWIP6SC_IP6IIDH                    (1 << 9)  /* IPv6 Include IP Destination in Hash */

#define R_MFWD_FWIP6SC_IP6IPH                     (1 << 10)  /* IPv6 Include Protocol in Hash */

#define R_MFWD_FWIP6SC_IP6ISPTH                   (1 << 11)  /* IPv6 Include Source Port in Hash */

#define R_MFWD_FWIP6SC_IP6IDPTH                   (1 << 12)  /* IPv6 Include Destination Port in Hash */

#define R_MFWD_FWIP6SC_IP6ISVS                    (1 << 16)  /* IPv6 Include S-TAG VLAN ID in Stream */

#define R_MFWD_FWIP6SC_IP6ISPS                    (1 << 17)  /* IPv6 Include S-TAG PCP in Stream */

#define R_MFWD_FWIP6SC_IP6ISDS                    (1 << 18)  /* IPv6 Include S-TAG DEI in Stream */

#define R_MFWD_FWIP6SC_IP6ICVS                    (1 << 19)  /* IPv6 Include C-TAG VLAN ID in Stream */

#define R_MFWD_FWIP6SC_IP6ICPS                    (1 << 20)  /* IPv6 Include C-TAG PCP in Stream */

#define R_MFWD_FWIP6SC_IP6ICDS                    (1 << 21)  /* IPv6 Include C-TAG DEI in Stream */

#define R_MFWD_FWIP6SC_IP6II0S                    (1 << 22)  /* IPv6 Include IP 0 in Stream */

#define R_MFWD_FWIP6SC_IP6II1S                    (1 << 23)  /* IPv6 Include IP 1 in Stream */

#define R_MFWD_FWIP6SC_IP6IDPTS                   (1 << 24)  /* IPv6 Include Destination Port in Stream */

/* FWIP6OC Register bit definitions */
#define R_MFWD_FWIP6OC_IP6IPOM_S                  (1 << 0)  /* IPv6 IP Offset mode %s */

#define R_MFWD_FWIP6OC_IP6IPO_S_SHIFT             (4)  /* IPv6 IP Offset %s */
#define R_MFWD_FWIP6OC_IP6IPO_S_MASK              0xf0

/* FWL2SC Register bit definitions */
#define R_MFWD_FWL2SC_L2IMDS                      (1 << 0)  /* Layer 2 Include MAC Destination in Stream */

#define R_MFWD_FWL2SC_L2IMSS                      (1 << 1)  /* Layer 2 Include MAC Source in Stream */

#define R_MFWD_FWL2SC_L2ISVS                      (1 << 2)  /* Layer 2 Include S-TAG VLAN ID in Stream */

#define R_MFWD_FWL2SC_L2ISPS                      (1 << 3)  /* Layer 2 Include S-TAG PCP ID in Stream */

#define R_MFWD_FWL2SC_L2ISDS                      (1 << 4)  /* Layer 2 Include S-TAG DEI in Stream */

#define R_MFWD_FWL2SC_L2ICVS                      (1 << 5)  /* Layer 2 Include C-TAG VLAN ID in Stream */

#define R_MFWD_FWL2SC_L2ICPS                      (1 << 6)  /* Layer 2 Include C-TAG PCP ID in Stream */

#define R_MFWD_FWL2SC_L2ICDS                      (1 << 7)  /* Layer 2 Include C-TAG DEI in Stream */

/* FWSFHEC Register bit definitions */
#define R_MFWD_FWSFHEC_IP4HE_SHIFT                (0)  /* Stream Filter Hash Equation */
#define R_MFWD_FWSFHEC_IP4HE_MASK                 0xffff

#define R_MFWD_FWSFHEC_IP6HE_SHIFT                (16)  /* Stream Filter Hash Equation */
#define R_MFWD_FWSFHEC_IP6HE_MASK                 0xffff0000

/* FWSHCR0 Register bit definitions */
#define R_MFWD_FWSHCR0_SHCMDP0_SHIFT              (0)  /* Software Hash Calculation MAC Destination Part 0 */
#define R_MFWD_FWSHCR0_SHCMDP0_MASK               0xffffffff

/* FWSHCR1 Register bit definitions */
#define R_MFWD_FWSHCR1_SHCMSP0_SHIFT              (0)  /* Software Hash Calculation MAC Source Part 0 */
#define R_MFWD_FWSHCR1_SHCMSP0_MASK               0xffff

#define R_MFWD_FWSHCR1_SHCMDP1_SHIFT              (16)  /* Software Hash Calculation MAC Destination Part 1 */
#define R_MFWD_FWSHCR1_SHCMDP1_MASK               0xffff0000

/* FWSHCR2 Register bit definitions */
#define R_MFWD_FWSHCR2_SHCMSP1_SHIFT              (0)  /* Software Hash Calculation MAC Source Part 1 */
#define R_MFWD_FWSHCR2_SHCMSP1_MASK               0xffffffff

/* FWSHCR3 Register bit definitions */
#define R_MFWD_FWSHCR3_SHCCV_SHIFT                (0)  /* Software Hash Calculation C-TAG VLAN */
#define R_MFWD_FWSHCR3_SHCCV_MASK                 0xfff

#define R_MFWD_FWSHCR3_SHCCD                      (1 << 12)  /* Software Hash Calculation C-TAG DEI */

#define R_MFWD_FWSHCR3_SHCCP_SHIFT                (13)  /* Software Hash Calculation C-TAG PCP */
#define R_MFWD_FWSHCR3_SHCCP_MASK                 0xe000

#define R_MFWD_FWSHCR3_SHCSV_SHIFT                (16)  /* Software Hash Calculation S-TAG VLANs */
#define R_MFWD_FWSHCR3_SHCSV_MASK                 0xfff0000

#define R_MFWD_FWSHCR3_SHCSD                      (1 << 28)  /* Software Hash Calculation S-TAG DEI */

#define R_MFWD_FWSHCR3_SHCSP_SHIFT                (29)  /* Software Hash Calculation S-TAG PCP */
#define R_MFWD_FWSHCR3_SHCSP_MASK                 0xe0000000

/* FWSHCR4 Register bit definitions */
#define R_MFWD_FWSHCR4_SHCP_SHIFT                 (0)  /* Software Hash Calculation Protocol (NextHeader for IPv6) */
#define R_MFWD_FWSHCR4_SHCP_MASK                  0xff

#define R_MFWD_FWSHCR4_SHCFF                      (1 << 16)  /* Software Hash Calculation Frame Format */

/* FWSHCR5 Register bit definitions */
#define R_MFWD_FWSHCR5_SHCISP0_SHIFT              (0)  /* Software Hash Calculation IP Source Part 0 */
#define R_MFWD_FWSHCR5_SHCISP0_MASK               0xffffffff

/* FWSHCR6 Register bit definitions */
#define R_MFWD_FWSHCR6_SHCISP1_SHIFT              (0)  /* Software Hash Calculation IP Source Part 1 */
#define R_MFWD_FWSHCR6_SHCISP1_MASK               0xffffffff

/* FWSHCR7 Register bit definitions */
#define R_MFWD_FWSHCR7_SHCISP2_SHIFT              (0)  /* Software Hash Calculation IP Source Part 2 */
#define R_MFWD_FWSHCR7_SHCISP2_MASK               0xffffffff

/* FWSHCR8 Register bit definitions */
#define R_MFWD_FWSHCR8_SHCISP3_SHIFT              (0)  /* Software Hash Calculation IP Source Part 3 */
#define R_MFWD_FWSHCR8_SHCISP3_MASK               0xffffffff

/* FWSHCR9 Register bit definitions */
#define R_MFWD_FWSHCR9_SHCIDP0_SHIFT              (0)  /* Software Hash Calculation IP Destination Part 0 */
#define R_MFWD_FWSHCR9_SHCIDP0_MASK               0xffffffff

/* FWSHCR10 Register bit definitions */
#define R_MFWD_FWSHCR10_SHCIDP1_SHIFT             (0)  /* Software Hash Calculation IP Destination Part 1 */
#define R_MFWD_FWSHCR10_SHCIDP1_MASK              0xffffffff

/* FWSHCR11 Register bit definitions */
#define R_MFWD_FWSHCR11_SHCIDP2_SHIFT             (0)  /* Software Hash Calculation IP Destination Part 2 */
#define R_MFWD_FWSHCR11_SHCIDP2_MASK              0xffffffff

/* FWSHCR12 Register bit definitions */
#define R_MFWD_FWSHCR12_SHCIDP3_SHIFT             (0)  /* Software Hash Calculation IP Destination Part 3 */
#define R_MFWD_FWSHCR12_SHCIDP3_MASK              0xffffffff

/* FWSHCR13 Register bit definitions */
#define R_MFWD_FWSHCR13_SHCDP_SHIFT               (0)  /* Software Hash Calculation Destination Port */
#define R_MFWD_FWSHCR13_SHCDP_MASK                0xffff

#define R_MFWD_FWSHCR13_SHCSP_SHIFT               (16)  /* Software Hash Calculation Source Port */
#define R_MFWD_FWSHCR13_SHCSP_MASK                0xffff0000

/* FWSHCRR Register bit definitions */
#define R_MFWD_FWSHCRR_SHCR_SHIFT                 (0)  /* Software Hash Calculation Result */
#define R_MFWD_FWSHCRR_SHCR_MASK                  0xffff

#define R_MFWD_FWSHCRR_SHC                        (1 << 31)  /* Software Hash Calculation */

/* FWLTHHEC Register bit definitions */
#define R_MFWD_FWLTHHEC_LTHHMC_SHIFT              (0)  /* L3 Hash Maximum Collision */
#define R_MFWD_FWLTHHEC_LTHHMC_MASK               0x3ff

#define R_MFWD_FWLTHHEC_LTHHMUE_SHIFT             (16)  /* L3 Hash Maximum Unsecure Entry */
#define R_MFWD_FWLTHHEC_LTHHMUE_MASK              0x7ff0000

/* FWLTHHC Register bit definitions */
#define R_MFWD_FWLTHHC_LTHHE_SHIFT                (0)  /* L3 Hash Equation */
#define R_MFWD_FWLTHHC_LTHHE_MASK                 0x3ff

/* FWLTHTL0 Register bit definitions */
#define R_MFWD_FWLTHTL0_LTHSLP0_SHIFT             (0)  /* L3 Stream Learn Part 0 */
#define R_MFWD_FWLTHTL0_LTHSLP0_MASK              0x7

#define R_MFWD_FWLTHTL0_LTHSLL                    (1 << 8)  /* L3 Security Level Learn */

#define R_MFWD_FWLTHTL0_LTHED                     (1 << 16)  /* L3 Entry Delete */

/* FWLTHTL1 Register bit definitions */
#define R_MFWD_FWLTHTL1_LTHSLP1_SHIFT             (0)  /* L3 Stream Learn Part 1 */
#define R_MFWD_FWLTHTL1_LTHSLP1_MASK              0xffffffff

/* FWLTHTL2 Register bit definitions */
#define R_MFWD_FWLTHTL2_LTHSLP2_SHIFT             (0)  /* L3 Stream Learn Part 2 */
#define R_MFWD_FWLTHTL2_LTHSLP2_MASK              0xffffffff

/* FWLTHTL3 Register bit definitions */
#define R_MFWD_FWLTHTL3_LTHSLP3_SHIFT             (0)  /* L3 Stream Learn Part 3 */
#define R_MFWD_FWLTHTL3_LTHSLP3_MASK              0xffffffff

/* FWLTHTL4 Register bit definitions */
#define R_MFWD_FWLTHTL4_LTHSLP4_SHIFT             (0)  /* L3 Stream Learn Part 4 */
#define R_MFWD_FWLTHTL4_LTHSLP4_MASK              0xffffffff

/* FWLTHTL5 Register bit definitions */
#define R_MFWD_FWLTHTL5_LTHMSDUNL_SHIFT           (16)  /* L3 MSDU Number Learn */
#define R_MFWD_FWLTHTL5_LTHMSDUNL_MASK            0xf0000

#define R_MFWD_FWLTHTL5_LTHMSDUVL                 (1 << 31)  /* L3 MSDU Valid Learn */

/* FWLTHTL6 Register bit definitions */
#define R_MFWD_FWLTHTL6_LTHFRERNL_SHIFT           (0)  /* L3 FRER Number Learn */
#define R_MFWD_FWLTHTL6_LTHFRERNL_MASK            0x7f

#define R_MFWD_FWLTHTL6_LTHFRERVL                 (1 << 15)  /* L3 FRER Valid Learn */

#define R_MFWD_FWLTHTL6_LTHMTRNL_SHIFT            (16)  /* L3 MeTeR Number Learn */
#define R_MFWD_FWLTHTL6_LTHMTRNL_MASK             0x1f0000

#define R_MFWD_FWLTHTL6_LTHMTRVL                  (1 << 31)  /* L3 MeTeR Valid Learn */

/* FWLTHTL7 Register bit definitions */
#define R_MFWD_FWLTHTL7_LTHRNL_SHIFT              (0)  /* L3 Routing Number Learn */
#define R_MFWD_FWLTHTL7_LTHRNL_MASK               0xff

#define R_MFWD_FWLTHTL7_LTHRVL                    (1 << 15)  /* L3 Routing Valid Learn */

#define R_MFWD_FWLTHTL7_LTHSLVL_SHIFT             (16)  /* L3 Source Lock Vector Learn */
#define R_MFWD_FWLTHTL7_LTHSLVL_MASK              0x7f0000

/* FWLTHTL80 Register bit definitions */
#define R_MFWD_FWLTHTL80_LTHCSDL_SHIFT            (0)  /* L3 CPU Sub-Destination Learn */
#define R_MFWD_FWLTHTL80_LTHCSDL_MASK             0x7f

/* FWLTHTL9 Register bit definitions */
#define R_MFWD_FWLTHTL9_LTHDVL_SHIFT              (0)  /* L3 Destination Vector Learn */
#define R_MFWD_FWLTHTL9_LTHDVL_MASK               0x7f

#define R_MFWD_FWLTHTL9_LTHIPVL_SHIFT             (16)  /* L3 Internal Priority Value Learn */
#define R_MFWD_FWLTHTL9_LTHIPVL_MASK              0x70000

#define R_MFWD_FWLTHTL9_LTHIPUL                   (1 << 19)  /* L3 Internal Priority Update Learn */

#define R_MFWD_FWLTHTL9_LTHEMEL                   (1 << 20)  /* L3 Ethernet Mirroring Enable Learn */

#define R_MFWD_FWLTHTL9_LTHCMEL                   (1 << 21)  /* L3 CPU Mirroring Enable Learn */

/* FWLTHTLR Register bit definitions */
#define R_MFWD_FWLTHTLR_LTHLF                     (1 << 0)  /* L3 Learn Fail */

#define R_MFWD_FWLTHTLR_LTHLSF                    (1 << 1)  /* L3 Learn Security Fail */

#define R_MFWD_FWLTHTLR_LTHLEF                    (1 << 2)  /* L3 Learn ECC Fail */

#define R_MFWD_FWLTHTLR_LTHLO                     (1 << 3)  /* L3 Learn Overwrite */

#define R_MFWD_FWLTHTLR_LTHLCN_SHIFT              (16)  /* L3 Learn Collision Number */
#define R_MFWD_FWLTHTLR_LTHLCN_MASK               0x3ff0000

#define R_MFWD_FWLTHTLR_LTHTL                     (1 << 31)  /* L3 Table Learn */

/* FWLTHTIM Register bit definitions */
#define R_MFWD_FWLTHTIM_LTHTIOG                   (1 << 0)  /* L3 Table Initialization Ongoing */

#define R_MFWD_FWLTHTIM_LTHTR                     (1 << 1)  /* L3 Table Ready */

/* FWLTHTEM Register bit definitions */
#define R_MFWD_FWLTHTEM_LTHTEN_SHIFT              (0)  /* L3 Table Entry Number */
#define R_MFWD_FWLTHTEM_LTHTEN_MASK               0x7ff

#define R_MFWD_FWLTHTEM_LTHTUEN_SHIFT             (16)  /* L3 Table Unsecure Entry Number */
#define R_MFWD_FWLTHTEM_LTHTUEN_MASK              0x7ff0000

/* FWLTHTS0 Register bit definitions */
#define R_MFWD_FWLTHTS0_LTHSSP0_SHIFT             (0)  /* L3 Stream Search Part 0 */
#define R_MFWD_FWLTHTS0_LTHSSP0_MASK              0x7

#define R_MFWD_FWLTHTS0_LTHSSPFS                  (1 << 24)  /* L3 Stream Search Perfect Filter Select */

/* FWLTHTS1 Register bit definitions */
#define R_MFWD_FWLTHTS1_LTHSSP1_SHIFT             (0)  /* L3 Stream Search Part 1 */
#define R_MFWD_FWLTHTS1_LTHSSP1_MASK              0xffffffff

/* FWLTHTS2 Register bit definitions */
#define R_MFWD_FWLTHTS2_LTHSSP2_SHIFT             (0)  /* L3 Stream Search Part 2 */
#define R_MFWD_FWLTHTS2_LTHSSP2_MASK              0xffffffff

/* FWLTHTS3 Register bit definitions */
#define R_MFWD_FWLTHTS3_LTHSSP3_SHIFT             (0)  /* L3 Stream Search Part 3 */
#define R_MFWD_FWLTHTS3_LTHSSP3_MASK              0xffffffff

/* FWLTHTS4 Register bit definitions */
#define R_MFWD_FWLTHTS4_LTHSSP4_SHIFT             (0)  /* L3 Stream Search Part 4 */
#define R_MFWD_FWLTHTS4_LTHSSP4_MASK              0xffffffff

/* FWLTHTSR0 Register bit definitions */
#define R_MFWD_FWLTHTSR0_LTHSEF                   (1 << 0)  /* L3 Search ECC Fail */

#define R_MFWD_FWLTHTSR0_LTHSNF                   (1 << 1)  /* L3 Search Not found */

#define R_MFWD_FWLTHTSR0_LTHSLS                   (1 << 8)  /* L3 Security Level Search */

#define R_MFWD_FWLTHTSR0_LTHSCN_SHIFT             (16)  /* L3 Search Collision Number */
#define R_MFWD_FWLTHTSR0_LTHSCN_MASK              0x3ff0000

#define R_MFWD_FWLTHTSR0_LTHTS                    (1 << 31)  /* L3 Table Search */

/* FWLTHTSR1 Register bit definitions */
#define R_MFWD_FWLTHTSR1_LTHMSDUNS_SHIFT          (16)  /* L3 MSDU Number Search */
#define R_MFWD_FWLTHTSR1_LTHMSDUNS_MASK           0xf0000

#define R_MFWD_FWLTHTSR1_LTHMSDUVS                (1 << 31)  /* L3 MSDU Valid Search */

/* FWLTHTSR2 Register bit definitions */
#define R_MFWD_FWLTHTSR2_LTHFRERNS_SHIFT          (0)  /* L3 FRER Number Search */
#define R_MFWD_FWLTHTSR2_LTHFRERNS_MASK           0x3f

#define R_MFWD_FWLTHTSR2_LTHFRERVS                (1 << 15)  /* L3 FRER Valid Search */

#define R_MFWD_FWLTHTSR2_LTHMTRNS_SHIFT           (16)  /* L3 MeTeR Number Search */
#define R_MFWD_FWLTHTSR2_LTHMTRNS_MASK            0x1f0000

#define R_MFWD_FWLTHTSR2_LTHMTRVS                 (1 << 31)  /* L3 MeTeR Valid Search */

/* FWLTHTSR3 Register bit definitions */
#define R_MFWD_FWLTHTSR3_LTHRNS_SHIFT             (0)  /* L3 Routing Number Search */
#define R_MFWD_FWLTHTSR3_LTHRNS_MASK              0xff

#define R_MFWD_FWLTHTSR3_LTHRVS                   (1 << 15)  /* L3 Routing Valid Search */

#define R_MFWD_FWLTHTSR3_LTHSLVS_SHIFT            (16)  /* L3 Source Lock Vector Search */
#define R_MFWD_FWLTHTSR3_LTHSLVS_MASK             0x7f0000

/* FWLTHTSR40 Register bit definitions */
#define R_MFWD_FWLTHTSR40_LTHCSDS_SHIFT           (0)  /* L3 CPU Sub-Destination Search */
#define R_MFWD_FWLTHTSR40_LTHCSDS_MASK            0x7f

/* FWLTHTSR5 Register bit definitions */
#define R_MFWD_FWLTHTSR5_LTHDVS_SHIFT             (0)  /* L3 Destination Vector Search */
#define R_MFWD_FWLTHTSR5_LTHDVS_MASK              0x7f

#define R_MFWD_FWLTHTSR5_LTHIPVS_SHIFT            (16)  /* L3 Internal Priority Value Search */
#define R_MFWD_FWLTHTSR5_LTHIPVS_MASK             0x70000

#define R_MFWD_FWLTHTSR5_LTHIPUS                  (1 << 19)  /* L3 Internal Priority Update Search */

#define R_MFWD_FWLTHTSR5_LTHEMES                  (1 << 20)  /* L3 Ethernet Mirroring Enable Search */

#define R_MFWD_FWLTHTSR5_LTHCMES                  (1 << 21)  /* L3 CPU Mirroring Enable Search */

/* FWLTHTR Register bit definitions */
#define R_MFWD_FWLTHTR_LTHAR_SHIFT                (0)  /* L3 Address Read */
#define R_MFWD_FWLTHTR_LTHAR_MASK                 0x3ff

/* FWLTHTRR0 Register bit definitions */
#define R_MFWD_FWLTHTRR0_LTHREF                   (1 << 0)  /* L3 Read ECC Fail */

#define R_MFWD_FWLTHTRR0_LTHEVR                   (1 << 1)  /* L3 Entry Valid Read */

#define R_MFWD_FWLTHTRR0_LTHTR                    (1 << 31)  /* L3 Table Read */

/* FWLTHTRR1 Register bit definitions */
#define R_MFWD_FWLTHTRR1_LTHSRP0_SHIFT            (0)  /* L3 Stream Read Part 0 */
#define R_MFWD_FWLTHTRR1_LTHSRP0_MASK             0x7

#define R_MFWD_FWLTHTRR1_LTHSLR                   (1 << 8)  /* L3 Security Level Read */

/* FWLTHTRR2 Register bit definitions */
#define R_MFWD_FWLTHTRR2_LTHSRP1_SHIFT            (0)  /* L3 Stream Read Part 1 */
#define R_MFWD_FWLTHTRR2_LTHSRP1_MASK             0xffffffff

/* FWLTHTRR3 Register bit definitions */
#define R_MFWD_FWLTHTRR3_LTHSRP2_SHIFT            (0)  /* L3 Stream Read Part 2 */
#define R_MFWD_FWLTHTRR3_LTHSRP2_MASK             0xffffffff

/* FWLTHTRR4 Register bit definitions */
#define R_MFWD_FWLTHTRR4_LTHSRP3_SHIFT            (0)  /* L3 Stream Read Part 3 */
#define R_MFWD_FWLTHTRR4_LTHSRP3_MASK             0xffffffff

/* FWLTHTRR5 Register bit definitions */
#define R_MFWD_FWLTHTRR5_LTHSRP4_SHIFT            (0)  /* L3 Stream Read Part 4 */
#define R_MFWD_FWLTHTRR5_LTHSRP4_MASK             0xffffffff

/* FWLTHTRR6 Register bit definitions */
#define R_MFWD_FWLTHTRR6_LTHMSDUNR_SHIFT          (16)  /* L3 MSDU Number Read */
#define R_MFWD_FWLTHTRR6_LTHMSDUNR_MASK           0xf0000

#define R_MFWD_FWLTHTRR6_LTHMSDUVR                (1 << 31)  /* L3 MSDU Valid Read */

/* FWLTHTRR7 Register bit definitions */
#define R_MFWD_FWLTHTRR7_LTHFRERNR_SHIFT          (0)  /* L3 FRER Number Read */
#define R_MFWD_FWLTHTRR7_LTHFRERNR_MASK           0x3f

#define R_MFWD_FWLTHTRR7_LTHFRERVR                (1 << 15)  /* L3 FRER Valid Read */

#define R_MFWD_FWLTHTRR7_LTHMTRNR_SHIFT           (16)  /* L3 MeTeR Number Read */
#define R_MFWD_FWLTHTRR7_LTHMTRNR_MASK            0x1f0000

#define R_MFWD_FWLTHTRR7_LTHMTRVR                 (1 << 31)  /* L3 MeTeR Valid Read */

/* FWLTHTRR8 Register bit definitions */
#define R_MFWD_FWLTHTRR8_LTHRNR_SHIFT             (0)  /* L3 Routing Number Read */
#define R_MFWD_FWLTHTRR8_LTHRNR_MASK              0xff

#define R_MFWD_FWLTHTRR8_LTHRVR                   (1 << 15)  /* L3 Routing Valid Read */

#define R_MFWD_FWLTHTRR8_LTHSLVR_SHIFT            (16)  /* L3 Source Lock Vector Read */
#define R_MFWD_FWLTHTRR8_LTHSLVR_MASK             0x7f0000

/* FWLTHTRR90 Register bit definitions */
#define R_MFWD_FWLTHTRR90_LTHCSDR_SHIFT           (0)  /* L3 CPU Sub-Destination Read */
#define R_MFWD_FWLTHTRR90_LTHCSDR_MASK            0x7f

/* FWLTHTRR10 Register bit definitions */
#define R_MFWD_FWLTHTRR10_LTHDVR_SHIFT            (0)  /* L3 Destination Vector Read */
#define R_MFWD_FWLTHTRR10_LTHDVR_MASK             0x7f

#define R_MFWD_FWLTHTRR10_LTHIPVR_SHIFT           (16)  /* L3 Internal Priority Value Read */
#define R_MFWD_FWLTHTRR10_LTHIPVR_MASK            0x70000

#define R_MFWD_FWLTHTRR10_LTHIPUR                 (1 << 19)  /* L3 Internal Priority Update Read */

#define R_MFWD_FWLTHTRR10_LTHEMER                 (1 << 20)  /* L3 Ethernet Mirroring Enable Read */

#define R_MFWD_FWLTHTRR10_LTHCMER                 (1 << 21)  /* L3 CPU Mirroring Enable Read */

/* FWMACHEC Register bit definitions */
#define R_MFWD_FWMACHEC_MACHMC_SHIFT              (0)  /* MAC Hash Maximum Collision */
#define R_MFWD_FWMACHEC_MACHMC_MASK               0x7ff

#define R_MFWD_FWMACHEC_MACHMUE_SHIFT             (16)  /* MAC Hash Maximum Unsecure Entry */
#define R_MFWD_FWMACHEC_MACHMUE_MASK              0xfff0000

/* FWMACHC Register bit definitions */
#define R_MFWD_FWMACHC_MACHE_SHIFT                (0)  /* MAC Hash Equation */
#define R_MFWD_FWMACHC_MACHE_MASK                 0x7ff

/* FWMACTL0 Register bit definitions */
#define R_MFWD_FWMACTL0_MACSLL                    (1 << 8)  /* MAC Security Level Learn */

#define R_MFWD_FWMACTL0_MACDEL                    (1 << 9)  /* MAC Dynamic Entry Limit */

#define R_MFWD_FWMACTL0_MACHLDL                   (1 << 10)  /* MAC Hardware Learning Disable Learn */

#define R_MFWD_FWMACTL0_MACED                     (1 << 16)  /* MAC Entry Delete */

/* FWMACTL1 Register bit definitions */
#define R_MFWD_FWMACTL1_MACMALP0_SHIFT            (0)  /* MAC MAC address Learn Part 0 */
#define R_MFWD_FWMACTL1_MACMALP0_MASK             0xffff

/* FWMACTL2 Register bit definitions */
#define R_MFWD_FWMACTL2_MACMALP1_SHIFT            (0)  /* MAC MAC address Learn Part 1 */
#define R_MFWD_FWMACTL2_MACMALP1_MASK             0xffffffff

/* FWMACTL3 Register bit definitions */
#define R_MFWD_FWMACTL3_MACSSLVL_SHIFT            (0)  /* MAC Source Source Lock Vector Learn */
#define R_MFWD_FWMACTL3_MACSSLVL_MASK             0x7f

#define R_MFWD_FWMACTL3_MACDSLVL_SHIFT            (16)  /* MAC Destination Source Lock Vector Learn */
#define R_MFWD_FWMACTL3_MACDSLVL_MASK             0x7f0000

/* FWMACTL40 Register bit definitions */
#define R_MFWD_FWMACTL40_MACCSDL_SHIFT            (0)  /* MAC CPU Sub-Destination Learn */
#define R_MFWD_FWMACTL40_MACCSDL_MASK             0x7f

/* FWMACTL5 Register bit definitions */
#define R_MFWD_FWMACTL5_MACDVL_SHIFT              (0)  /* MAC Destination Vector Learn */
#define R_MFWD_FWMACTL5_MACDVL_MASK               0x7f

#define R_MFWD_FWMACTL5_MACIPVL_SHIFT             (16)  /* MAC Internal Priority Value Learn */
#define R_MFWD_FWMACTL5_MACIPVL_MASK              0x70000

#define R_MFWD_FWMACTL5_MACIPUL                   (1 << 19)  /* MAC Internal Priority Update Learn */

#define R_MFWD_FWMACTL5_MACEMEL                   (1 << 20)  /* MAC Ethernet Mirroring Enable Learn */

#define R_MFWD_FWMACTL5_MACCMEL                   (1 << 21)  /* MAC CPU Mirroring Enable Learn */

/* FWMACTLR Register bit definitions */
#define R_MFWD_FWMACTLR_MACLF                     (1 << 0)  /* MAC Learn Fail */

#define R_MFWD_FWMACTLR_MACLSF                    (1 << 1)  /* MAC Learn Security Fail */

#define R_MFWD_FWMACTLR_MACLEF                    (1 << 2)  /* MAC Learn ECC Fail */

#define R_MFWD_FWMACTLR_MACLO                     (1 << 3)  /* MAC Learn Overwrite */

#define R_MFWD_FWMACTLR_MACLCN_SHIFT              (16)  /* MAC Learn Collision Number */
#define R_MFWD_FWMACTLR_MACLCN_MASK               0x3ff0000

#define R_MFWD_FWMACTLR_MACTL                     (1 << 31)  /* MAC Table Learn */

/* FWMACTIM Register bit definitions */
#define R_MFWD_FWMACTIM_MACTIOG                   (1 << 0)  /* MAC Table Initialization Ongoing */

#define R_MFWD_FWMACTIM_MACTR                     (1 << 1)  /* MAC Table Ready */

/* FWMACTEM Register bit definitions */
#define R_MFWD_FWMACTEM_MACTEN_SHIFT              (0)  /* MAC Table Entry Number */
#define R_MFWD_FWMACTEM_MACTEN_MASK               0x7ff

#define R_MFWD_FWMACTEM_MACTUEN_SHIFT             (16)  /* MAC Table Unsecure Entry Number */
#define R_MFWD_FWMACTEM_MACTUEN_MASK              0x7ff0000

/* FWMACTS0 Register bit definitions */
#define R_MFWD_FWMACTS0_MACMASP0_SHIFT            (0)  /* MAC MAC Address Search Part 0 */
#define R_MFWD_FWMACTS0_MACMASP0_MASK             0xffff

/* FWMACTS1 Register bit definitions */
#define R_MFWD_FWMACTS1_MACMASP1_SHIFT            (0)  /* MAC MAC Address Search Part 1 */
#define R_MFWD_FWMACTS1_MACMASP1_MASK             0xffffffff

/* FWMACTSR0 Register bit definitions */
#define R_MFWD_FWMACTSR0_MACSEF                   (1 << 0)  /* MAC Search ECC Fail */

#define R_MFWD_FWMACTSR0_MACSNF                   (1 << 1)  /* MAC Search Not found */

#define R_MFWD_FWMACTSR0_MACSLS                   (1 << 8)  /* MAC Security Level Search */

#define R_MFWD_FWMACTSR0_MACDES                   (1 << 9)  /* MAC Dynamic Entry Search */

#define R_MFWD_FWMACTSR0_MACHLDS                  (1 << 10)  /* MAC Hardware Learning Disable Search */

#define R_MFWD_FWMACTSR0_MACSCN_SHIFT             (16)  /* MAC Search Collision Number */
#define R_MFWD_FWMACTSR0_MACSCN_MASK              0x3ff0000

#define R_MFWD_FWMACTSR0_MACTS                    (1 << 31)  /* MAC Table Search */

/* FWMACTSR1 Register bit definitions */
#define R_MFWD_FWMACTSR1_MACSSLVS_SHIFT           (0)  /* MAC Source Source Lock Vector Search */
#define R_MFWD_FWMACTSR1_MACSSLVS_MASK            0x7f

#define R_MFWD_FWMACTSR1_MACDSLVS_SHIFT           (16)  /* MAC Destination Source Lock Vector Search */
#define R_MFWD_FWMACTSR1_MACDSLVS_MASK            0x7f0000

/* FWMACTSR20 Register bit definitions */
#define R_MFWD_FWMACTSR20_MACCSDS_SHIFT           (0)  /* MAC CPU Sub-Destination Search */
#define R_MFWD_FWMACTSR20_MACCSDS_MASK            0x7f

/* FWMACTSR3 Register bit definitions */
#define R_MFWD_FWMACTSR3_MACDVS_SHIFT             (0)  /* MAC Destination Vector Search */
#define R_MFWD_FWMACTSR3_MACDVS_MASK              0x7f

#define R_MFWD_FWMACTSR3_MACIPVS_SHIFT            (16)  /* MAC Internal Priority Value Search */
#define R_MFWD_FWMACTSR3_MACIPVS_MASK             0x70000

#define R_MFWD_FWMACTSR3_MACIPUS                  (1 << 19)  /* MAC Internal Priority Update Search */

#define R_MFWD_FWMACTSR3_MACEMES                  (1 << 20)  /* MAC Ethernet Mirroring Enable Search */

#define R_MFWD_FWMACTSR3_MACCMES                  (1 << 21)  /* MAC CPU Mirroring Enable Search */

/* FWMACTR Register bit definitions */
#define R_MFWD_FWMACTR_MACAR_SHIFT                (0)  /* MAC Address Read */
#define R_MFWD_FWMACTR_MACAR_MASK                 0x3ff

/* FWMACTRR0 Register bit definitions */
#define R_MFWD_FWMACTRR0_MACEVR                   (1 << 0)  /* MAC Entry Valid Read */

#define R_MFWD_FWMACTRR0_MACREF                   (1 << 1)  /* MAC Read ECC Fail */

#define R_MFWD_FWMACTRR0_MACTR                    (1 << 31)  /* MAC Table Read */

/* FWMACTRR1 Register bit definitions */
#define R_MFWD_FWMACTRR1_MACSLR                   (1 << 8)  /* MAC Security Level Read */

#define R_MFWD_FWMACTRR1_MACDER                   (1 << 9)  /* MAC Dynamic Entry Read */

#define R_MFWD_FWMACTRR1_MACHLDR                  (1 << 10)  /* MAC Hardware Learn Disable Read */

#define R_MFWD_FWMACTRR1_MACABR                   (1 << 11)  /* MAC Aging Bit Read */

/* FWMACTRR2 Register bit definitions */
#define R_MFWD_FWMACTRR2_MACMARP0_SHIFT           (0)  /* MAC MAC address Read Part 0 */
#define R_MFWD_FWMACTRR2_MACMARP0_MASK            0xffff

/* FWMACTRR3 Register bit definitions */
#define R_MFWD_FWMACTRR3_MACMARP1_SHIFT           (0)  /* MAC MAC address Read Part 1 */
#define R_MFWD_FWMACTRR3_MACMARP1_MASK            0xffffffff

/* FWMACTRR4 Register bit definitions */
#define R_MFWD_FWMACTRR4_MACSSLVR_SHIFT           (0)  /* MAC Source Source Lock Vector Read */
#define R_MFWD_FWMACTRR4_MACSSLVR_MASK            0x7f

#define R_MFWD_FWMACTRR4_MACDSLVR_SHIFT           (16)  /* MAC Destination Source Lock Vector Read */
#define R_MFWD_FWMACTRR4_MACDSLVR_MASK            0x7f0000

/* FWMACTRR50 Register bit definitions */
#define R_MFWD_FWMACTRR50_MACCSDR_SHIFT           (0)  /* MAC CPU Sub-Destination Read */
#define R_MFWD_FWMACTRR50_MACCSDR_MASK            0x7f

/* FWMACTRR6 Register bit definitions */
#define R_MFWD_FWMACTRR6_MACDVR_SHIFT             (0)  /* MAC Destination Vector Read */
#define R_MFWD_FWMACTRR6_MACDVR_MASK              0x7f

#define R_MFWD_FWMACTRR6_MACIPVR_SHIFT            (16)  /* MAC Internal Priority Value Read */
#define R_MFWD_FWMACTRR6_MACIPVR_MASK             0x70000

#define R_MFWD_FWMACTRR6_MACIPUR                  (1 << 19)  /* MAC Internal Priority Update Read */

#define R_MFWD_FWMACTRR6_MACEMER                  (1 << 20)  /* MAC Ethernet Mirroring Enable Read */

#define R_MFWD_FWMACTRR6_MACCMER                  (1 << 21)  /* MAC CPU Mirroring Enable Read */

/* FWMACAGUSPC Register bit definitions */
#define R_MFWD_FWMACAGUSPC_MACAGUSP_SHIFT         (0)  /* MAC Aging US prescaler */
#define R_MFWD_FWMACAGUSPC_MACAGUSP_MASK          0x3ff

/* FWMACAGC Register bit definitions */
#define R_MFWD_FWMACAGC_MACAGT_SHIFT              (0)  /* MAC Aging Time */
#define R_MFWD_FWMACAGC_MACAGT_MASK               0xffff

#define R_MFWD_FWMACAGC_MACAGE                    (1 << 16)  /* MAC Aging Enable */

#define R_MFWD_FWMACAGC_MACAGSL                   (1 << 17)  /* MAC Aging Security Level */

#define R_MFWD_FWMACAGC_MACAGPM                   (1 << 18)  /* MAC Aging Polling Mode */

#define R_MFWD_FWMACAGC_MACDES                    (1 << 24)  /* MAC Dynamic Entry Suppression */

#define R_MFWD_FWMACAGC_MACAGOG                   (1 << 28)  /* MAC Aging OnGoing */

#define R_MFWD_FWMACAGC_MACDESOG                  (1 << 29)  /* MAC Dynamic Entry Suppression OnGoing */

/* FWMACAGM0 Register bit definitions */
#define R_MFWD_FWMACAGM0_AGMACAP0_SHIFT           (0)  /* Aged MAC Address Part 0 */
#define R_MFWD_FWMACAGM0_AGMACAP0_MASK            0xffff

/* FWMACAGM1 Register bit definitions */
#define R_MFWD_FWMACAGM1_AGMACAP1_SHIFT           (0)  /* Aged MAC Address Part 1 */
#define R_MFWD_FWMACAGM1_AGMACAP1_MASK            0xffffffff

/* FWVLANTEC Register bit definitions */
#define R_MFWD_FWVLANTEC_VLANTMUE_SHIFT           (16)  /* VLAN Table Maximum Unsecure Entry */
#define R_MFWD_FWVLANTEC_VLANTMUE_MASK            0x1fff0000

/* FWVLANTL0 Register bit definitions */
#define R_MFWD_FWVLANTL0_VLANSLL                  (1 << 8)  /* VLAN Security Level Learn */

#define R_MFWD_FWVLANTL0_VLANHLDL                 (1 << 10)  /* VLAN Hardware Learning Disable Learn */

#define R_MFWD_FWVLANTL0_VLANED                   (1 << 16)  /* VLAN Entry Delete */

/* FWVLANTL1 Register bit definitions */
#define R_MFWD_FWVLANTL1_VLANVIDL_SHIFT           (0)  /* VLAN VID Learn */
#define R_MFWD_FWVLANTL1_VLANVIDL_MASK            0xfff

/* FWVLANTL2 Register bit definitions */
#define R_MFWD_FWVLANTL2_VLANSLVL_SHIFT           (0)  /* VLAN Source Lock Vector Learn */
#define R_MFWD_FWVLANTL2_VLANSLVL_MASK            0x7f

/* FWVLANTL30 Register bit definitions */
#define R_MFWD_FWVLANTL30_VLANCSDL_SHIFT          (0)  /* VLAN CPU Sub-Destination Learn */
#define R_MFWD_FWVLANTL30_VLANCSDL_MASK           0x7f

/* FWVLANTL4 Register bit definitions */
#define R_MFWD_FWVLANTL4_VLANDVL_SHIFT            (0)  /* VLAN Destination Vector Learn */
#define R_MFWD_FWVLANTL4_VLANDVL_MASK             0x7f

#define R_MFWD_FWVLANTL4_VLANIPVL_SHIFT           (16)  /* VLAN Internal Priority Value Learn */
#define R_MFWD_FWVLANTL4_VLANIPVL_MASK            0x70000

#define R_MFWD_FWVLANTL4_VLANIPUL                 (1 << 19)  /* VLAN Internal Priority Update Learn */

#define R_MFWD_FWVLANTL4_VLANEMEL                 (1 << 20)  /* VLAN Ethernet Mirroring Enable Learn */

#define R_MFWD_FWVLANTL4_VLANCMEL                 (1 << 21)  /* VLAN CPU Mirroring Enable Learn */

/* FWVLANTLR Register bit definitions */
#define R_MFWD_FWVLANTLR_VLANLF                   (1 << 0)  /* VLAN Learn Fail */

#define R_MFWD_FWVLANTLR_VLANLSF                  (1 << 1)  /* VLAN Learn Security Fail */

#define R_MFWD_FWVLANTLR_VLANLEF                  (1 << 2)  /* VLAN Learn ECC Fail */

#define R_MFWD_FWVLANTLR_VLANLO                   (1 << 3)  /* VLAN Learn Overwrite */

#define R_MFWD_FWVLANTLR_VLANTL                   (1 << 31)  /* VLAN Table Learn */

/* FWVLANTIM Register bit definitions */
#define R_MFWD_FWVLANTIM_VLANTIOG                 (1 << 0)  /* VLAN Table Initialization Ongoing */

#define R_MFWD_FWVLANTIM_VLANTR                   (1 << 1)  /* VLAN Table Ready */

/* FWVLANTEM Register bit definitions */
#define R_MFWD_FWVLANTEM_VLANTEN_SHIFT            (0)  /* VLAN Table Entry Number */
#define R_MFWD_FWVLANTEM_VLANTEN_MASK             0x1fff

#define R_MFWD_FWVLANTEM_VLANTUEN_SHIFT           (16)  /* VLAN Table Unsecure Entry Number */
#define R_MFWD_FWVLANTEM_VLANTUEN_MASK            0x1fff0000

/* FWVLANTS Register bit definitions */
#define R_MFWD_FWVLANTS_VLANVIDS_SHIFT            (0)  /* VLAN VID Search */
#define R_MFWD_FWVLANTS_VLANVIDS_MASK             0xfff

/* FWVLANTSR0 Register bit definitions */
#define R_MFWD_FWVLANTSR0_VLANSEF                 (1 << 0)  /* VLAN Search ECC Fail */

#define R_MFWD_FWVLANTSR0_VLANSNF                 (1 << 1)  /* VLAN Search Not found */

#define R_MFWD_FWVLANTSR0_VLANSLS                 (1 << 8)  /* VLAN Security Level Search */

#define R_MFWD_FWVLANTSR0_VLANHLDS                (1 << 10)  /* VLAN Hardware Learning Disable Search */

#define R_MFWD_FWVLANTSR0_VLANTS                  (1 << 31)  /* VLAN Table Search */

/* FWVLANTSR1 Register bit definitions */
#define R_MFWD_FWVLANTSR1_VLANSLVS_SHIFT          (0)  /* VLAN Source Lock Vector Search */
#define R_MFWD_FWVLANTSR1_VLANSLVS_MASK           0x7f

/* FWVLANTSR20 Register bit definitions */
#define R_MFWD_FWVLANTSR20_VLANCSDS_SHIFT         (0)  /* VLAN CPU Sub-Destination Search */
#define R_MFWD_FWVLANTSR20_VLANCSDS_MASK          0x7f

/* FWVLANTSR3 Register bit definitions */
#define R_MFWD_FWVLANTSR3_VLANDVS_SHIFT           (0)  /* VLAN Destination Vector Search */
#define R_MFWD_FWVLANTSR3_VLANDVS_MASK            0x7f

#define R_MFWD_FWVLANTSR3_VLANIPVS_SHIFT          (16)  /* VLAN Internal Priority Value Search */
#define R_MFWD_FWVLANTSR3_VLANIPVS_MASK           0x70000

#define R_MFWD_FWVLANTSR3_VLANIPUS                (1 << 19)  /* VLAN Internal Priority Update Search */

#define R_MFWD_FWVLANTSR3_VLANEMES                (1 << 20)  /* VLAN Ethernet Mirroring Enable Search */

#define R_MFWD_FWVLANTSR3_VLANCMES                (1 << 21)  /* VLAN CPU Mirroring Enable Search */

/* FWPBFC Register bit definitions */
#define R_MFWD_FWPBFC_PBDV_SHIFT                  (0)  /* Port Based Destination Vector */
#define R_MFWD_FWPBFC_PBDV_MASK                   0x7f

#define R_MFWD_FWPBFC_PBIPV_SHIFT                 (16)  /* Port Based Internal Priority Value */
#define R_MFWD_FWPBFC_PBIPV_MASK                  0x70000

#define R_MFWD_FWPBFC_PBIPU                       (1 << 19)  /* Port Based Internal Priority Update */

#define R_MFWD_FWPBFC_PBEME                       (1 << 20)  /* Port Based Ethernet Mirroring Enabled */

#define R_MFWD_FWPBFC_PBCME                       (1 << 21)  /* Port Based CPU Mirroring Enabled */

#define R_MFWD_FWPBFC_PBSL                        (1 << 22)  /* Port Based Security Level */

#define R_MFWD_FWPBFC_IP4PDE                      (1 << 23)  /* IPv4 Priority Decode Enable */

#define R_MFWD_FWPBFC_IP4PDM                      (1 << 24)  /* IPv4 Priority Decode Mode */

#define R_MFWD_FWPBFC_IP6PDE                      (1 << 25)  /* IPv6 Priority Decode Enable */

#define R_MFWD_FWPBFC_FAIFP                       (1 << 26)  /* Force All Input Frame Priority Enable */

/* FWPBFCSDC Register bit definitions */
#define R_MFWD_FWPBFCSDC_PBCSD_SHIFT              (0)  /* Port Based CPU Sub Destination */
#define R_MFWD_FWPBFCSDC_PBCSD_MASK               0x7f

/* FWL23URL0 Register bit definitions */
#define R_MFWD_FWL23URL0_L23URNL_SHIFT            (0)  /* Layer 2/Layer 3 Update Routing Number Learn */
#define R_MFWD_FWL23URL0_L23URNL_MASK             0xff

#define R_MFWD_FWL23URL0_L23URPVL_SHIFT           (16)  /* Layer 2/Layer 3 Update Routing Port Valid Learn */
#define R_MFWD_FWL23URL0_L23URPVL_MASK            0x7f0000

/* FWL23URL1 Register bit definitions */
#define R_MFWD_FWL23URL1_L23UMDALP0_SHIFT         (0)  /* Layer 2/Layer 3 Update MAC Destination Address Learn Part 0 */
#define R_MFWD_FWL23URL1_L23UMDALP0_MASK          0xffff

#define R_MFWD_FWL23URL1_L23UTTLUL                (1 << 16)  /* Layer 2/Layer 3 Update Time To Live Update Learn */

#define R_MFWD_FWL23URL1_L23UMDAUL                (1 << 17)  /* Layer 2/Layer 3 Update MAC Destination Address Update Learn */

#define R_MFWD_FWL23URL1_L23UMSAUL                (1 << 18)  /* Layer 2/Layer 3 Update MAC Source Address Update Learn */

#define R_MFWD_FWL23URL1_L23UCVIDUL               (1 << 19)  /* Layer 2/Layer 3 Update C-TAG VID Update Learn */

#define R_MFWD_FWL23URL1_L23UCPCPUL               (1 << 20)  /* Layer 2/Layer 3 Update C-TAG PCP Update Learn */

#define R_MFWD_FWL23URL1_L23UCDEIUL               (1 << 21)  /* Layer 2/Layer 3 Update C-TAG DEI Update Learn */

#define R_MFWD_FWL23URL1_L23USVIDUL               (1 << 22)  /* Layer 2/Layer 3 Update S-TAG VID Update Learn */

#define R_MFWD_FWL23URL1_L23USPCPUL               (1 << 23)  /* Layer 2/Layer 3 Update S-TAG PCP Update Learn */

#define R_MFWD_FWL23URL1_L23USDEIUL               (1 << 24)  /* Layer 2/Layer 3 Update S-TAG DEI Update Learn */

#define R_MFWD_FWL23URL1_L23URTUL_SHIFT           (25)  /* Layer 2/Layer 3 Update R-TAG Update Learn */
#define R_MFWD_FWL23URL1_L23URTUL_MASK            0x6000000

/* FWL23URL2 Register bit definitions */
#define R_MFWD_FWL23URL2_L23UMDALP1_SHIFT         (0)  /* Layer 2/Layer 3 Update MAC Destination Address Learn Part 1 */
#define R_MFWD_FWL23URL2_L23UMDALP1_MASK          0xffffffff

/* FWL23URL3 Register bit definitions */
#define R_MFWD_FWL23URL3_L23UCVIDL_SHIFT          (0)  /* Layer 2/Layer 3 Update C-TAG VID Learn */
#define R_MFWD_FWL23URL3_L23UCVIDL_MASK           0xfff

#define R_MFWD_FWL23URL3_L23UCPCPL_SHIFT          (12)  /* Layer 2/Layer 3 Update C-TAG PCP Learn */
#define R_MFWD_FWL23URL3_L23UCPCPL_MASK           0x7000

#define R_MFWD_FWL23URL3_L23UCDEIL                (1 << 15)  /* Layer 2/Layer 3 Update C-TAG DEI Learn */

#define R_MFWD_FWL23URL3_L23USVIDL_SHIFT          (16)  /* Layer 2/Layer 3 Update S-TAG VID Learn */
#define R_MFWD_FWL23URL3_L23USVIDL_MASK           0xfff0000

#define R_MFWD_FWL23URL3_L23USPCPL_SHIFT          (28)  /* Layer 2/Layer 3 Update S-TAG PCP Learn */
#define R_MFWD_FWL23URL3_L23USPCPL_MASK           0x70000000

#define R_MFWD_FWL23URL3_L23USDEIL                (1 << 31)  /* Layer 2/Layer 3 Update S-TAG DEI Learn */

/* FWL23URLR Register bit definitions */
#define R_MFWD_FWL23URLR_L23ULF                   (1 << 0)  /* Layer 2/Layer 3 Update Learn Fail */

#define R_MFWD_FWL23URLR_L23URL                   (1 << 31)  /* Layer 2/Layer 3 Update Rule Learn */

/* FWL23UTIM Register bit definitions */
#define R_MFWD_FWL23UTIM_L23UTIOG                 (1 << 0)  /* Layer 2/Layer 3 Update Table Initialization Ongoing */

#define R_MFWD_FWL23UTIM_L23UTR                   (1 << 1)  /* Layer 2/Layer 3 Update Table Ready */

/* FWL23URR Register bit definitions */
#define R_MFWD_FWL23URR_L23RNR_SHIFT              (0)  /* Layer 2/Layer 3 Routing Number Read */
#define R_MFWD_FWL23URR_L23RNR_MASK               0xff

/* FWL23URRR0 Register bit definitions */
#define R_MFWD_FWL23URRR0_L23URPVR_SHIFT          (0)  /* Layer 2/Layer 3 Update Routing Port Valid Read */
#define R_MFWD_FWL23URRR0_L23URPVR_MASK           0x7f

#define R_MFWD_FWL23URRR0_L23UREF                 (1 << 16)  /* Layer 2/Layer 3 Update Read ECC Fail */

#define R_MFWD_FWL23URRR0_L23URR                  (1 << 31)  /* Layer 2/Layer 3 Update Rule Read */

/* FWL23URRR1 Register bit definitions */
#define R_MFWD_FWL23URRR1_L23UMDARP0_SHIFT        (0)  /* Layer 2/Layer 3 MAC Destination Address Read Part 0 */
#define R_MFWD_FWL23URRR1_L23UMDARP0_MASK         0xffff

#define R_MFWD_FWL23URRR1_L23UTTLUR               (1 << 16)  /* Layer 2/Layer 3 Time To Live Update Read */

#define R_MFWD_FWL23URRR1_L23UMDAUR               (1 << 17)  /* Layer 2/Layer 3 MAC Destination Address Update Read */

#define R_MFWD_FWL23URRR1_L23UMSAUR               (1 << 18)  /* Layer 2/Layer 3 MAC Source Address Update Read */

#define R_MFWD_FWL23URRR1_L23UCVIDUR              (1 << 19)  /* Layer 2/Layer 3 C-TAG VID Update Read */

#define R_MFWD_FWL23URRR1_L23UCPCPUR              (1 << 20)  /* Layer 2/Layer 3 C-TAG PCP Update Read */

#define R_MFWD_FWL23URRR1_L23UCDEIUR              (1 << 21)  /* Layer 2/Layer 3 C-TAG DEI Update Read */

#define R_MFWD_FWL23URRR1_L23USVIDUR              (1 << 22)  /* Layer 2/Layer 3 S-TAG VID Update Read */

#define R_MFWD_FWL23URRR1_L23USPCPUR              (1 << 23)  /* Layer 2/Layer 3 S-TAG PCP Update Read */

#define R_MFWD_FWL23URRR1_L23USDEIUR              (1 << 24)  /* Layer 2/Layer 3 S-TAG DEI Update Read */

#define R_MFWD_FWL23URRR1_L23URTUR_SHIFT          (25)  /* Layer 2/Layer 3 R-TAG Update Read */
#define R_MFWD_FWL23URRR1_L23URTUR_MASK           0x6000000

/* FWL23URRR2 Register bit definitions */
#define R_MFWD_FWL23URRR2_L23UMDARP1_SHIFT        (0)  /* Layer 2/Layer 3 MAC Destination Address Read Part 1 */
#define R_MFWD_FWL23URRR2_L23UMDARP1_MASK         0xffffffff

/* FWL23URRR3 Register bit definitions */
#define R_MFWD_FWL23URRR3_L23UCVIDR_SHIFT         (0)  /* Layer 2/Layer 3 Update MAC C-TAG VID Read */
#define R_MFWD_FWL23URRR3_L23UCVIDR_MASK          0xfff

#define R_MFWD_FWL23URRR3_L23UCPCPR_SHIFT         (12)  /* Layer 2/Layer 3 Update MAC C-TAG PCP Read */
#define R_MFWD_FWL23URRR3_L23UCPCPR_MASK          0x7000

#define R_MFWD_FWL23URRR3_L23UCDEIR               (1 << 15)  /* Layer 2/Layer 3 Update MAC C-TAG DEI Read */

#define R_MFWD_FWL23URRR3_L23USVIDR_SHIFT         (16)  /* Layer 2/Layer 3 Update MAC S-TAG VID Read */
#define R_MFWD_FWL23URRR3_L23USVIDR_MASK          0xfff0000

#define R_MFWD_FWL23URRR3_L23USPCPR_SHIFT         (28)  /* Layer 2/Layer 3 Update MAC S-TAG PCP Read */
#define R_MFWD_FWL23URRR3_L23USPCPR_MASK          0x70000000

#define R_MFWD_FWL23URRR3_L23USDEIR               (1 << 31)  /* Layer 2/Layer 3 Update MAC S-TAG DEI Read */

/* FWL23URMC Register bit definitions */
#define R_MFWD_FWL23URMC_RMRN_SHIFT               (0)  /* ReMaping Rule Number */
#define R_MFWD_FWL23URMC_RMRN_MASK                0xff

#define R_MFWD_FWL23URMC_RMDPN_SHIFT              (12)  /* ReMaping Destination Port Number */
#define R_MFWD_FWL23URMC_RMDPN_MASK               0x7000

#define R_MFWD_FWL23URMC_RMNRN_SHIFT              (16)  /* ReMaping New Rule Number */
#define R_MFWD_FWL23URMC_RMNRN_MASK               0xff0000

#define R_MFWD_FWL23URMC_RME                      (1 << 28)  /* ReMaping Enable */

/* FWPMFGC Register bit definitions */
#define R_MFWD_FWPMFGC_MSDUV_SHIFT                (0)  /* MSDU Value */
#define R_MFWD_FWPMFGC_MSDUV_MASK                 0xffff

#define R_MFWD_FWPMFGC_MFM                        (1 << 31)  /* MSDU Filter Mode */

/* FWPMTRFC Register bit definitions */
#define R_MFWD_FWPMTRFC_MTRFE                     (1 << 0)  /* Meter Filter Enable */

#define R_MFWD_FWPMTRFC_MTRFM_SHIFT               (1)  /* Meter Filter Mode */
#define R_MFWD_FWPMTRFC_MTRFM_MASK                0x6
#  define R_MFWD_FWPMTRFC_MTRFM_00                        (0 << R_MFWD_FWPMTRFC_MTRFM_SHIFT)  /* Normal mode */
#  define R_MFWD_FWPMTRFC_MTRFM_01                        (1 << R_MFWD_FWPMTRFC_MTRFM_SHIFT)  /* Throttle mode */
#  define R_MFWD_FWPMTRFC_MTRFM_10                        (2 << R_MFWD_FWPMTRFC_MTRFM_SHIFT)  /* ATS mode */
#  define R_MFWD_FWPMTRFC_MTRFM_11                        (3 << R_MFWD_FWPMTRFC_MTRFM_SHIFT)  /* ATS throttle mode */

#define R_MFWD_FWPMTRFC_MTRFRFD                   (1 << 3)  /* Meter Filter Red Frame Drop */

#define R_MFWD_FWPMTRFC_MTRCF                     (1 << 4)  /* Meter Coupling Flag */

#define R_MFWD_FWPMTRFC_MTRCM_SHIFT               (16)  /* Meter Color Mode */
#define R_MFWD_FWPMTRFC_MTRCM_MASK                0xffff0000

/* FWPMTRCBSC Register bit definitions */
#define R_MFWD_FWPMTRCBSC_CBS_SHIFT               (0)  /* CBS */
#define R_MFWD_FWPMTRCBSC_CBS_MASK                0x3ffff

/* FWPMTRCIRC Register bit definitions */
#define R_MFWD_FWPMTRCIRC_CIR_SHIFT               (0)  /* CIR */
#define R_MFWD_FWPMTRCIRC_CIR_MASK                0xfffff

/* FWPMTREBSC Register bit definitions */
#define R_MFWD_FWPMTREBSC_EBS_SHIFT               (0)  /* EBS */
#define R_MFWD_FWPMTREBSC_EBS_MASK                0x3ffff

/* FWPMTREIRC Register bit definitions */
#define R_MFWD_FWPMTREIRC_EIR_SHIFT               (0)  /* EIR */
#define R_MFWD_FWPMTREIRC_EIR_MASK                0xfffff

/* FWPMTRFM Register bit definitions */
#define R_MFWD_FWPMTRFM_MTRARDN_SHIFT             (0)  /* MeTeR ATS RAM Descriptor Number */
#define R_MFWD_FWPMTRFM_MTRARDN_MASK              0x1f

#define R_MFWD_FWPMTRFM_MTRARDNMN_SHIFT           (16)  /* MeTeR ATS RAM Descriptor Number Maximum Number i */
#define R_MFWD_FWPMTRFM_MTRARDNMN_MASK            0x1f0000

/* FWFTL0 Register bit definitions */
#define R_MFWD_FWFTL0_FEAL_SHIFT                  (0)  /* FRER Entry Address Learn */
#define R_MFWD_FWFTL0_FEAL_MASK                   0x7f

#define R_MFWD_FWFTL0_FSRPL_SHIFT                 (16)  /* FRER Sequence Recovery Pointer Learn */
#define R_MFWD_FWFTL0_FSRPL_MASK                  0x7f0000

/* FWFTL1 Register bit definitions */
#define R_MFWD_FWFTL1_FSHLL_SHIFT                 (0)  /* FRER Sequence History Length Learn */
#define R_MFWD_FWFTL1_FSHLL_MASK                  0xf

#define R_MFWD_FWFTL1_FTNSL                       (1 << 8)  /* FRER Take No Sequence Learn */

#define R_MFWD_FWFTL1_FSRPVL                      (1 << 9)  /* FRER Sequence Recovery Pointer Valid Learn */

#define R_MFWD_FWFTL1_FSRRTL_SHIFT                (16)  /* FRER Sequence Recovery Remaining Ticks Learn */
#define R_MFWD_FWFTL1_FSRRTL_MASK                 0x3ff0000

/* FWFTLR Register bit definitions */
#define R_MFWD_FWFTLR_FLF                         (1 << 0)  /* FRER Learn Fail */

#define R_MFWD_FWFTLR_FTL                         (1 << 31)  /* FRER Table Learn */

/* FWFTOC Register bit definitions */
#define R_MFWD_FWFTOC_TOT_SHIFT                   (0)  /* Timeout Time (ms) */
#define R_MFWD_FWFTOC_TOT_MASK                    0xffff

#define R_MFWD_FWFTOC_TOCE                        (1 << 16)  /* Timeout Check Enable */

#define R_MFWD_FWFTOC_TOOG                        (1 << 17)  /* Timeout Ongoing */

/* FWFTOPC Register bit definitions */
#define R_MFWD_FWFTOPC_USP_SHIFT                  (0)  /* Microsecond Prescaler */
#define R_MFWD_FWFTOPC_USP_MASK                   0x3ff

/* FWFTIM Register bit definitions */
#define R_MFWD_FWFTIM_FTIOG                       (1 << 0)  /* FRER Table Initialization Ongoing */

#define R_MFWD_FWFTIM_FTR                         (1 << 1)  /* FRER Table Ready */

/* FWFTR Register bit definitions */
#define R_MFWD_FWFTR_FEAR_SHIFT                   (0)  /* FRER Entry Address Read */
#define R_MFWD_FWFTR_FEAR_MASK                    0x7f

/* FWFTRR0 Register bit definitions */
#define R_MFWD_FWFTRR0_FSHLR_SHIFT                (0)  /* FRER Sequence History Length Read */
#define R_MFWD_FWFTRR0_FSHLR_MASK                 0xf

#define R_MFWD_FWFTRR0_FTNSR                      (1 << 8)  /* FRER Take No Sequence Read */

#define R_MFWD_FWFTRR0_FSRPVR                     (1 << 9)  /* FRER Sequence Recovery Pointer Valid Read */

#define R_MFWD_FWFTRR0_FSRRTR_SHIFT               (16)  /* FRER Set Recovery Remaining Ticks Read */
#define R_MFWD_FWFTRR0_FSRRTR_MASK                0x3ff0000

#define R_MFWD_FWFTRR0_FTREF                      (1 << 30)  /* FRER Table Read ECC Fail */

#define R_MFWD_FWFTRR0_FTR                        (1 << 31)  /* FRER Table Read */

/* FWFTRR1 Register bit definitions */
#define R_MFWD_FWFTRR1_FSHR_SHIFT                 (0)  /* FRER Sequence History Read */
#define R_MFWD_FWFTRR1_FSHR_MASK                  0x7fff

#define R_MFWD_FWFTRR1_FSRPR_SHIFT                (16)  /* FRER Sequence Recovery Pointer Read */
#define R_MFWD_FWFTRR1_FSRPR_MASK                 0x7f0000

/* FWFTRR2 Register bit definitions */
#define R_MFWD_FWFTRR2_FRSNR_SHIFT                (0)  /* FRER Recovery Sequence Number Read */
#define R_MFWD_FWFTRR2_FRSNR_MASK                 0xffff

#define R_MFWD_FWFTRR2_FRRTR_SHIFT                (16)  /* FRER Recovery Remaining Ticks Read */
#define R_MFWD_FWFTRR2_FRRTR_MASK                 0x3ff0000

/* FWSEQNGC Register bit definitions */
#define R_MFWD_FWSEQNGC_SEQNGRN_SHIFT             (0)  /* SEQuence Number Generation Routing Number */
#define R_MFWD_FWSEQNGC_SEQNGRN_MASK              0xff

#define R_MFWD_FWSEQNGC_SEQNGE                    (1 << 16)  /* SEQuence Number Generation Emable */

/* FWSEQNGM Register bit definitions */
#define R_MFWD_FWSEQNGM_SEQN_SHIFT                (0)  /* SEQuence Number */
#define R_MFWD_FWSEQNGM_SEQN_MASK                 0xffff

/* FWSEQNRC Register bit definitions */
#define R_MFWD_FWSEQNRC_SEQNR_SHIFT               (0)  /* Sequence Number Generation Reset */
#define R_MFWD_FWSEQNRC_SEQNR_MASK                0xffffffff

/* FWCTFDCN Register bit definitions */
#define R_MFWD_FWCTFDCN_CTFDN_SHIFT               (0)  /* Cut-Through Forwarded Descriptor Number */
#define R_MFWD_FWCTFDCN_CTFDN_MASK                0xffffffff

/* FWLTHFDCN Register bit definitions */
#define R_MFWD_FWLTHFDCN_LTHFDN_SHIFT             (0)  /* Layer 3 Forwarded Descriptor Number */
#define R_MFWD_FWLTHFDCN_LTHFDN_MASK              0xffffffff

/* FWLTWFDCN Register bit definitions */
#define R_MFWD_FWLTWFDCN_LTWFDN_SHIFT             (0)  /* Layer 2 Forwarded Descriptor Number */
#define R_MFWD_FWLTWFDCN_LTWFDN_MASK              0xffffffff

/* FWPBFDCN Register bit definitions */
#define R_MFWD_FWPBFDCN_PBFDN_SHIFT               (0)  /* Port Based Forwarded Descriptor Number */
#define R_MFWD_FWPBFDCN_PBFDN_MASK                0xffffffff

/* FWMHLCN Register bit definitions */
#define R_MFWD_FWMHLCN_MHLN_SHIFT                 (0)  /* MAC Hardware Learn Number */
#define R_MFWD_FWMHLCN_MHLN_MASK                  0xffffffff

/* FWDDFDCN0 Register bit definitions */
#define R_MFWD_FWDDFDCN0_DDFDN_SHIFT              (0)  /* Direct Descriptor Forwarded Descriptor Number */
#define R_MFWD_FWDDFDCN0_DDFDN_MASK               0xffffffff

/* FWWMRDCN Register bit definitions */
#define R_MFWD_FWWMRDCN_WMRDN_SHIFT               (0)  /* Watermark rejected Descriptor Number */
#define R_MFWD_FWWMRDCN_WMRDN_MASK                0xffff

/* FWCTRDCN Register bit definitions */
#define R_MFWD_FWCTRDCN_CTRDN_SHIFT               (0)  /* Cut-through rejected Descriptor Number */
#define R_MFWD_FWCTRDCN_CTRDN_MASK                0xffff

/* FWLTHRDCN Register bit definitions */
#define R_MFWD_FWLTHRDCN_LTHRDN_SHIFT             (0)  /* Layer 3 rejected Descriptor Number */
#define R_MFWD_FWLTHRDCN_LTHRDN_MASK              0xffff

/* FWLTWRDCN Register bit definitions */
#define R_MFWD_FWLTWRDCN_LTWRDN_SHIFT             (0)  /* Layer 2 rejected Descriptor Number */
#define R_MFWD_FWLTWRDCN_LTWRDN_MASK              0xffff

/* FWPBRDCN Register bit definitions */
#define R_MFWD_FWPBRDCN_PBRDN_SHIFT               (0)  /* Port Based rejected Descriptor Number */
#define R_MFWD_FWPBRDCN_PBRDN_MASK                0xffff

/* FWDDRDCN0 Register bit definitions */
#define R_MFWD_FWDDRDCN0_DDRDN_SHIFT              (0)  /* Direct Descriptor rejected Descriptor Number */
#define R_MFWD_FWDDRDCN0_DDRDN_MASK               0xffff

/* FWPMFDCN Register bit definitions */
#define R_MFWD_FWPMFDCN_PMFDN_SHIFT               (0)  /* PSFP MSDU Filtered Descriptor Number */
#define R_MFWD_FWPMFDCN_PMFDN_MASK                0xffff

/* FWPMGDCN Register bit definitions */
#define R_MFWD_FWPMGDCN_PMGDN_SHIFT               (0)  /* PSFP Meter Green Descriptor Number */
#define R_MFWD_FWPMGDCN_PMGDN_MASK                0xffff

/* FWPMYDCN Register bit definitions */
#define R_MFWD_FWPMYDCN_PMYDN_SHIFT               (0)  /* PSFP Meter Yellow Descriptor Number */
#define R_MFWD_FWPMYDCN_PMYDN_MASK                0xffff

/* FWPMRDCN Register bit definitions */
#define R_MFWD_FWPMRDCN_PMRDN_SHIFT               (0)  /* PSFP Meter Red Descriptor Number */
#define R_MFWD_FWPMRDCN_PMRDN_MASK                0xffff

/* FWFRPPCN Register bit definitions */
#define R_MFWD_FWFRPPCN_PPC_SHIFT                 (0)  /* Passed Packet Count */
#define R_MFWD_FWFRPPCN_PPC_MASK                  0xffff

/* FWFRDPCN Register bit definitions */
#define R_MFWD_FWFRDPCN_DPC_SHIFT                 (0)  /* Discarded Packet Count */
#define R_MFWD_FWFRDPCN_DPC_MASK                  0xffff

/* FWEIS Register bit definitions */
#define R_MFWD_FWEIS_LTHSPFS                      (1 << 0)  /* Layer 3 Source Port Filtering Status */

#define R_MFWD_FWEIS_LTHNTFS                      (1 << 2)  /* Layer 3 No Target Filtering Status */

#define R_MFWD_FWEIS_LTHUFS                       (1 << 3)  /* Layer 3 Unknown Filtering Status */

#define R_MFWD_FWEIS_LTWDSPFS                     (1 << 10)  /* Layer 2 Destination Source Port Filtering Status */

#define R_MFWD_FWEIS_LTWSSPFS                     (1 << 11)  /* Layer 2 Source Source Port Filtering Status */

#define R_MFWD_FWEIS_LTWVSPFS                     (1 << 12)  /* Layer 2 VLAN Source Port Filtering Status */

#define R_MFWD_FWEIS_LTWNTFS                      (1 << 13)  /* Layer 2 No Target Filtering Status */

#define R_MFWD_FWEIS_LTWSUFS                      (1 << 14)  /* Layer 2 Source Unknown Filtering Status */

#define R_MFWD_FWEIS_LTWDUFS                      (1 << 15)  /* Layer 2 Destination Unknown Filtering Status */

#define R_MFWD_FWEIS_LTWVUFS                      (1 << 16)  /* Layer 2 VLAN Unknown Filtering Status */

#define R_MFWD_FWEIS_PBNTFS                       (1 << 17)  /* Port Based No Target Filtering Status */

#define R_MFWD_FWEIS_SMHLFS                       (1 << 18)  /* Source MAC Hardware Learning Fail Status */

#define R_MFWD_FWEIS_SMHMFS                       (1 << 19)  /* Source MAC Hardware Migration Fail Status */

#define R_MFWD_FWEIS_WMCFS                        (1 << 22)  /* Watermark Critical Filtering Status */

#define R_MFWD_FWEIS_WMFFS                        (1 << 23)  /* Watermark Flush Filtering Status */

#define R_MFWD_FWEIS_WMISFS                       (1 << 24)  /* Watermark IPV Secure Filtering Status */

#define R_MFWD_FWEIS_WMIUFS                       (1 << 25)  /* Watermark IPV Unsecure Filtering Status */

#define R_MFWD_FWEIS_DDES                         (1 << 26)  /* Direct Descriptor Error Status i */

#define R_MFWD_FWEIS_DDSES                        (1 << 28)  /* Direct Descriptor Security Error Status */

#define R_MFWD_FWEIS_DDNTFS                       (1 << 29)  /* Direct Descriptor No Target Filtering Status */

/* FWEIE Register bit definitions */
#define R_MFWD_FWEIE_LTHSPFE                      (1 << 0)  /* Layer 3 Source Port Filtering Enable */

#define R_MFWD_FWEIE_LTHNTFE                      (1 << 2)  /* Layer 3 No Target Filtering Enable */

#define R_MFWD_FWEIE_LTHUFE                       (1 << 3)  /* Layer 3 Unknown Filtering Enable */

#define R_MFWD_FWEIE_LTWDSPFE                     (1 << 10)  /* Layer 2 Destination Source Port Filtering Enable */

#define R_MFWD_FWEIE_LTWSSPFE                     (1 << 11)  /* Layer 2 Source Source Port Filtering Enable */

#define R_MFWD_FWEIE_LTWVSPFE                     (1 << 12)  /* Layer 2 VLAN Source Port Filtering Enable */

#define R_MFWD_FWEIE_LTWNTFE                      (1 << 13)  /* Layer 2 No Target Filtering Enable */

#define R_MFWD_FWEIE_LTWSUFE                      (1 << 14)  /* Layer 2 Source Unknown Filtering Enable */

#define R_MFWD_FWEIE_LTWDUFE                      (1 << 15)  /* Layer 2 Destination Unknown Filtering Enable */

#define R_MFWD_FWEIE_LTWVUFE                      (1 << 16)  /* Layer 2 VLAN Unknown Filtering Enable */

#define R_MFWD_FWEIE_PBNTFE                       (1 << 17)  /* Port Based No Target Filtering Enable */

#define R_MFWD_FWEIE_SMHLFE                       (1 << 18)  /* Source MAC Hardware Learning Fail Enable */

#define R_MFWD_FWEIE_SMHMFE                       (1 << 19)  /* Source MAC Hardware Migration Fail Enable */

#define R_MFWD_FWEIE_WMCFE                        (1 << 22)  /* Watermark Critical Filtering Enable */

#define R_MFWD_FWEIE_WMFFE                        (1 << 23)  /* Watermark Flush Filtering Enable */

#define R_MFWD_FWEIE_WMISFE                       (1 << 24)  /* Watermark IPV Secure Filtering Enable */

#define R_MFWD_FWEIE_WMIUFE                       (1 << 25)  /* Watermark IPV Unsecure Filtering Enable */

#define R_MFWD_FWEIE_DDEE                         (1 << 26)  /* Direct Descriptor Error Enable */

#define R_MFWD_FWEIE_DDFEE                        (1 << 27)  /* Direct Descriptor Format Error Enable */

#define R_MFWD_FWEIE_DDSEE                        (1 << 28)  /* Direct Descriptor Security Error Enable */

#define R_MFWD_FWEIE_DDNTFE                       (1 << 29)  /* Direct Descriptor No Target Filtering Enable */

/* FWEID Register bit definitions */
#define R_MFWD_FWEID_LTHSPFD                      (1 << 0)  /* Layer 3 Source Port Filtering Disable */

#define R_MFWD_FWEID_LTHNTFD                      (1 << 2)  /* Layer 3 No Target Filtering Disable */

#define R_MFWD_FWEID_LTHUFD                       (1 << 3)  /* Layer 3 Unknown Filtering Disable */

#define R_MFWD_FWEID_LTWDSPFD                     (1 << 10)  /* Layer 2 Destination Source Port Filtering Disable */

#define R_MFWD_FWEID_LTWSSPFD                     (1 << 11)  /* Layer 2 Source Source Port Filtering Disable */

#define R_MFWD_FWEID_LTWVSPFD                     (1 << 12)  /* Layer 2 VLAN Source Port Filtering Disable */

#define R_MFWD_FWEID_LTWNTFD                      (1 << 13)  /* Layer 2 No Target Filtering Disable */

#define R_MFWD_FWEID_LTWSUFD                      (1 << 14)  /* Layer 2 Source Unknown Filtering Disable */

#define R_MFWD_FWEID_LTWDUFD                      (1 << 15)  /* Layer 2 Destination Unknown Filtering Disable */

#define R_MFWD_FWEID_LTWVUFD                      (1 << 16)  /* Layer 2 VLAN Unknown Filtering Disable */

#define R_MFWD_FWEID_PBNTFD                       (1 << 17)  /* Port Based No Target Filtering Disable */

#define R_MFWD_FWEID_SMHLFD                       (1 << 18)  /* Source MAC Hardware Learning Fail Disable */

#define R_MFWD_FWEID_SMHMFD                       (1 << 19)  /* Source MAC Hardware Migration Fail Disable */

#define R_MFWD_FWEID_WMCFD                        (1 << 22)  /* Watermark Critical Filtering Disable */

#define R_MFWD_FWEID_WMFFD                        (1 << 23)  /* Watermark Flush Filtering Disable */

#define R_MFWD_FWEID_WMISFD                       (1 << 24)  /* Watermark IPV Secure Filtering Disable */

#define R_MFWD_FWEID_WMIUFD                       (1 << 25)  /* Watermark IPV Unsecure Filtering Disable */

#define R_MFWD_FWEID_DDED                         (1 << 26)  /* Direct Descriptor Error Disable */

#define R_MFWD_FWEID_DDFED                        (1 << 27)  /* Direct Descriptor Format Error Disable */

#define R_MFWD_FWEID_DDSED                        (1 << 28)  /* Direct Descriptor Security Error Disable */

#define R_MFWD_FWEID_DDNTFD                       (1 << 29)  /* Direct Descriptor No Target Filtering Disable */

/* FWEIS1 Register bit definitions */
#define R_MFWD_FWEIS1_LTHTEES                     (1 << 0)  /* L3 Table ECC Error Status */

#define R_MFWD_FWEIS1_LTHTSES                     (1 << 1)  /* L3 Table Security Error Status */

#define R_MFWD_FWEIS1_MACTEES                     (1 << 4)  /* MAC Table ECC Error Status */

#define R_MFWD_FWEIS1_MACTSES                     (1 << 5)  /* MAC Table Security Error Status */

#define R_MFWD_FWEIS1_VLANTEES                    (1 << 6)  /* VLAN Table ECC Error Status */

#define R_MFWD_FWEIS1_VLANTSES                    (1 << 7)  /* VLAN Table Security Error Status */

#define R_MFWD_FWEIS1_L23UEES                     (1 << 8)  /* Layer 2/Layer 3 Update ECC Error Status */

#define R_MFWD_FWEIS1_AREES                       (1 << 16)  /* ATS RAM ECC Error Status */

/* FWEIE1 Register bit definitions */
#define R_MFWD_FWEIE1_LTHTEEE                     (1 << 0)  /* L3 Table ECC Error Enable */

#define R_MFWD_FWEIE1_LTHTSEE                     (1 << 1)  /* L3 Table Security Error Enable */

#define R_MFWD_FWEIE1_MACTEEE                     (1 << 4)  /* MAC Table ECC Error Enable */

#define R_MFWD_FWEIE1_MACTSEE                     (1 << 5)  /* MAC Table Security Error Enable */

#define R_MFWD_FWEIE1_VLANTEEE                    (1 << 6)  /* VLAN Table ECC Error Enable */

#define R_MFWD_FWEIE1_VLANTSEE                    (1 << 7)  /* VLAN Table Security Error Enable */

#define R_MFWD_FWEIE1_L23UEEE                     (1 << 8)  /* Layer 2/Layer 3 Update ECC Error Enable */

#define R_MFWD_FWEIE1_AREEE                       (1 << 16)  /* ATS RAM ECC Error Enable */

/* FWEID1 Register bit definitions */
#define R_MFWD_FWEID1_LTHTEED                     (1 << 0)  /* L3 Table ECC Error Disable */

#define R_MFWD_FWEID1_LTHTSED                     (1 << 1)  /* L3 Table Security Error Disable */

#define R_MFWD_FWEID1_MACTEED                     (1 << 4)  /* MAC Table ECC Error Disable */

#define R_MFWD_FWEID1_MACTSED                     (1 << 5)  /* MAC Table Security Error Disable */

#define R_MFWD_FWEID1_VLANTEED                    (1 << 6)  /* VLAN Table ECC Error Disable */

#define R_MFWD_FWEID1_VLANTSED                    (1 << 7)  /* VLAN Table Security Error Disable */

#define R_MFWD_FWEID1_L23UEED                     (1 << 8)  /* Layer 2/Layer 3 Update ECC Error Disable */

#define R_MFWD_FWEID1_AREED                       (1 << 16)  /* ATS RAM ECC Error Disable */

/* FWEIS2 Register bit definitions */
#define R_MFWD_FWEIS2_PMFS_SHIFT                  (0)  /* PSFP MSDU Filtering Status */
#define R_MFWD_FWEIS2_PMFS_MASK                   0xffff

/* FWEIE2 Register bit definitions */
#define R_MFWD_FWEIE2_PMFE_SHIFT                  (0)  /* PSFP MSDU Filtering Enable */
#define R_MFWD_FWEIE2_PMFE_MASK                   0xffff
#  define R_MFWD_FWEIE2_PMFE_0                            (0 << R_MFWD_FWEIE2_PMFE_SHIFT)  /* Interrupt disabled. */
#  define R_MFWD_FWEIE2_PMFE_1                            (1 << R_MFWD_FWEIE2_PMFE_SHIFT)  /* Interrupt Enabled. */

/* FWEID2 Register bit definitions */
#define R_MFWD_FWEID2_PMFD_SHIFT                  (0)  /* PSFP MSDU Filtering Disable */
#define R_MFWD_FWEID2_PMFD_MASK                   0xffff

/* FWEIS5 Register bit definitions */
#define R_MFWD_FWEIS5_PMRFS_SHIFT                 (0)  /* PSFP Meter Filtering Status */
#define R_MFWD_FWEIS5_PMRFS_MASK                  0xffffffff

/* FWEIE5 Register bit definitions */
#define R_MFWD_FWEIE5_PMRFE_SHIFT                 (0)  /* PSFP Meter Filtering Enable */
#define R_MFWD_FWEIE5_PMRFE_MASK                  0xffffffff

/* FWEID5 Register bit definitions */
#define R_MFWD_FWEID5_PMRFD_SHIFT                 (0)  /* PSFP Meter Filtering Disable */
#define R_MFWD_FWEID5_PMRFD_MASK                  0xffffffff

/* FWEIS Register bit definitions */
#define R_MFWD_FWEIS_FFS_SHIFT                    (0)  /* FRER Filtering Status */
#define R_MFWD_FWEIS_FFS_MASK                     0xffffffff

/* FWEIE Register bit definitions */
#define R_MFWD_FWEIE_FFE_SHIFT                    (0)  /* FRER Filtering Enable */
#define R_MFWD_FWEIE_FFE_MASK                     0xffffffff

/* FWEID Register bit definitions */
#define R_MFWD_FWEID_FFD_SHIFT                    (0)  /* FRER Filtering Disable */
#define R_MFWD_FWEID_FFD_MASK                     0xffffffff

/* FWEIS Register bit definitions */
#define R_MFWD_FWEIS_FOORS_SHIFT                  (0)  /* FRER Out Of Range Status */
#define R_MFWD_FWEIS_FOORS_MASK                   0xffffffff

/* FWEIE Register bit definitions */
#define R_MFWD_FWEIE_FOORE_SHIFT                  (0)  /* FRER Out Of Range Enable */
#define R_MFWD_FWEIE_FOORE_MASK                   0xffffffff

/* FWEID Register bit definitions */
#define R_MFWD_FWEID_FOORD_SHIFT                  (0)  /* FRER Out Of Range Disable */
#define R_MFWD_FWEID_FOORD_MASK                   0xffffffff

/* FWEIS Register bit definitions */
#define R_MFWD_FWEIS_TOS_SHIFT                    (0)  /* Timeout Status */
#define R_MFWD_FWEIS_TOS_MASK                     0xffffffff

/* FWEIE Register bit definitions */
#define R_MFWD_FWEIE_TOE_SHIFT                    (0)  /* Timeout Enable */
#define R_MFWD_FWEIE_TOE_MASK                     0xffffffff

/* FWEID Register bit definitions */
#define R_MFWD_FWEID_TOD_SHIFT                    (0)  /* Timeout Disable */
#define R_MFWD_FWEID_TOD_MASK                     0xffffffff

/* FWMIS0 Register bit definitions */
#define R_MFWD_FWMIS0_LTHTFS                      (1 << 0)  /* L3 Table Full Status */

#define R_MFWD_FWMIS0_MACTFS                      (1 << 2)  /* MAC Table Full Status */

#define R_MFWD_FWMIS0_VLANTFS                     (1 << 3)  /* VLAN Table Full Status */

#define R_MFWD_FWMIS0_MACADAS                     (1 << 17)  /* MAC Address Deleted Aging Status */

/* FWMIE0 Register bit definitions */
#define R_MFWD_FWMIE0_LTHTFE                      (1 << 0)  /* L3 Table Full Enable */

#define R_MFWD_FWMIE0_MACTFE                      (1 << 2)  /* MAC Table Full Enable */

#define R_MFWD_FWMIE0_VLANTFE                     (1 << 3)  /* VLAN Table Full Enable */

#define R_MFWD_FWMIE0_MACADAE                     (1 << 17)  /* MAC Address Deleted Aging Enable */

/* FWMID0 Register bit definitions */
#define R_MFWD_FWMID0_LTHTFD                      (1 << 0)  /* L3 Table Full Disable */

#define R_MFWD_FWMID0_MACTFD                      (1 << 2)  /* MAC Table Full Disable */

#define R_MFWD_FWMID0_VLANTFD                     (1 << 3)  /* VLAN Table Full Disable */

#define R_MFWD_FWMID0_MACADAD                     (1 << 17)  /* MAC Address Deleted Aging Disable */


/* Maximum number of channels */

#define MFWD_MAX_CHANNELS    128

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_MFWD_H */
