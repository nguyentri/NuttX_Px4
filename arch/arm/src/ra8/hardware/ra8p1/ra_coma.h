/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_coma.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_COMA_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_COMA_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* COMA Base Address */
#ifndef R_COMA_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_COMA_BASE           0x403c9000
#else
#define R_COMA_BASE           0x503c9000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_COMA_CH_STRIDE    0x00000004
#define R_COMA_CH_BASE(ch)   (R_COMA_BASE + ((uint32_t)(ch) * R_COMA_CH_STRIDE))

/* COMA Register Offsets */

#define R_COMA_RIPV_OFFSET     0x00000000  /* IP Version Register */
#define R_COMA_RRC_OFFSET     0x00000004  /* Reset Configuration Register */
#define R_COMA_RCEC_OFFSET     0x00000008  /* Clock Enable Configuration Register */
#define R_COMA_RCDC_OFFSET     0x0000000c  /* Clock Disable Configuration Register */
/* CABPIBWMC%s Registers (0-7) */
#define R_COMA_CABPIBWMC0_OFFSET     0x00000020  /* Buffer Pool IPV Based Watermark Configuration Register 0 */
#define R_COMA_CABPIBWMC1_OFFSET     0x00000024  /* Buffer Pool IPV Based Watermark Configuration Register 1 */
#define R_COMA_CABPIBWMC2_OFFSET     0x00000028  /* Buffer Pool IPV Based Watermark Configuration Register 2 */
#define R_COMA_CABPIBWMC3_OFFSET     0x0000002c  /* Buffer Pool IPV Based Watermark Configuration Register 3 */
#define R_COMA_CABPIBWMC4_OFFSET     0x00000030  /* Buffer Pool IPV Based Watermark Configuration Register 4 */
#define R_COMA_CABPIBWMC5_OFFSET     0x00000034  /* Buffer Pool IPV Based Watermark Configuration Register 5 */
#define R_COMA_CABPIBWMC6_OFFSET     0x00000038  /* Buffer Pool IPV Based Watermark Configuration Register 6 */
#define R_COMA_CABPIBWMC7_OFFSET     0x0000003c  /* Buffer Pool IPV Based Watermark Configuration Register 7 */
#define R_COMA_CABPWMLC_OFFSET     0x00000040  /* Buffer Pool Watermark Level Configuration Register */
#define R_COMA_CABPPFLCI_OFFSET     0x00000050  /* Buffer Pointer Pause Frame Level i Configuration Register */
/* CABPPWMLC%s Registers (0-2) */
#define R_COMA_CABPPWMLC0_OFFSET     0x00000060  /* Port 0 Buffer Pool Watermark Level Configuration Register */
#define R_COMA_CABPPWMLC1_OFFSET     0x00000064  /* Port 1 Buffer Pool Watermark Level Configuration Register */
#define R_COMA_CABPPWMLC2_OFFSET     0x00000068  /* Port 2 Buffer Pool Watermark Level Configuration Register */
/* CABPPPFLC0%s Registers (0-1) */
#define R_COMA_CABPPPFLC00_OFFSET     0x000000a0  /* Port i Buffer Pointer Pause Frame Level 0 Configuration Register  */
#define R_COMA_CABPPPFLC01_OFFSET     0x000000a4  /* Port i Buffer Pointer Pause Frame Level 1 Configuration Register  */
/* CABPPPFLC1%s Registers (0-1) */
#define R_COMA_CABPPPFLC10_OFFSET     0x000000a8  /* Port i Buffer Pointer Pause Frame Level 0 Configuration Register  */
#define R_COMA_CABPPPFLC11_OFFSET     0x000000ac  /* Port i Buffer Pointer Pause Frame Level 1 Configuration Register  */
/* CABPPPFLC2%s Registers (0-1) */
#define R_COMA_CABPPPFLC20_OFFSET     0x000000b0  /* Port i Buffer Pointer Pause Frame Level 0 Configuration Register  */
#define R_COMA_CABPPPFLC21_OFFSET     0x000000b4  /* Port i Buffer Pointer Pause Frame Level 1 Configuration Register  */
/* CABPULC%s Registers (0-2) */
#define R_COMA_CABPULC0_OFFSET     0x00000100  /* Port 0 Buffer Pointer Utilization Level Configuration Register i */
#define R_COMA_CABPULC1_OFFSET     0x00000104  /* Port 1 Buffer Pointer Utilization Level Configuration Register i */
#define R_COMA_CABPULC2_OFFSET     0x00000108  /* Port 2 Buffer Pointer Utilization Level Configuration Register i */
#define R_COMA_CABPIRM_OFFSET     0x00000140  /* Buffer Pool Initialization Register Monitoring Register */
#define R_COMA_CABPPCM_OFFSET     0x00000144  /* Buffer Pool Pointer Count Monitoring Register */
#define R_COMA_CABPLCM_OFFSET     0x00000148  /* Buffer Pool Pointer Least Count Monitoring Register */
/* CABPCPM%s Registers (0-2) */
#define R_COMA_CABPCPM0_OFFSET     0x00000180  /* Port 0 Buffer Pointer Count Monitoring Register */
#define R_COMA_CABPCPM1_OFFSET     0x00000184  /* Port 1 Buffer Pointer Count Monitoring Register */
#define R_COMA_CABPCPM2_OFFSET     0x00000188  /* Port 2 Buffer Pointer Count Monitoring Register */
/* CABPMCPM%s Registers (0-2) */
#define R_COMA_CABPMCPM0_OFFSET     0x00000200  /* Port 0 Buffer Pointer Maximum Count Monitoring Register */
#define R_COMA_CABPMCPM1_OFFSET     0x00000204  /* Port 1 Buffer Pointer Maximum Count Monitoring Register */
#define R_COMA_CABPMCPM2_OFFSET     0x00000208  /* Port 2 Buffer Pointer Maximum Count Monitoring Register */
#define R_COMA_CARDNM_OFFSET     0x00000300  /* Rejected Descriptor Number Monitoring Register */
#define R_COMA_CARDMNM_OFFSET     0x00000304  /* Rejected Descriptor Maximum Number Monitoring Register */
#define R_COMA_CARDCN_OFFSET     0x00000310  /* Rejected Descriptor Counter Register */
#define R_COMA_CAEIS0_OFFSET     0x00000400  /* Error Interrupt Status Register 0 */
#define R_COMA_CAEIE0_OFFSET     0x00000404  /* Error Interrupt Enable Register 0 */
#define R_COMA_CAEID0_OFFSET     0x00000408  /* Error Interrupt Disable Register 0 */
#define R_COMA_CAEIS1_OFFSET     0x00000410  /* Error Interrupt Status Register 1 */
#define R_COMA_CAEIE1_OFFSET     0x00000414  /* Error Interrupt Enable Register 1 */
#define R_COMA_CAEID1_OFFSET     0x00000418  /* Error Interrupt Disable Register 1 */
#define R_COMA_CAMIS0_OFFSET     0x00000440  /* Monitoring Interrupt Status Register 0 */
#define R_COMA_CAMIE0_OFFSET     0x00000444  /* Monitoring Interrupt Enable Register 0 */
#define R_COMA_CAMID0_OFFSET     0x00000448  /* Monitoring Interrupt Disable Register 0 */
#define R_COMA_CAMIS1_OFFSET     0x00000450  /* Monitoring Interrupt Status Register 1 */
#define R_COMA_CAMIE1_OFFSET     0x00000454  /* Monitoring Interrupt Enable Register 1 */
#define R_COMA_CAMID1_OFFSET     0x00000458  /* Monitoring Interrupt Disable Register 1 */

/* COMA Register Addresses */

#define R_COMA_RIPV                 (R_COMA_BASE + R_COMA_RIPV_OFFSET)
#define R_COMA_RRC                 (R_COMA_BASE + R_COMA_RRC_OFFSET)
#define R_COMA_RCEC                 (R_COMA_BASE + R_COMA_RCEC_OFFSET)
#define R_COMA_RCDC                 (R_COMA_BASE + R_COMA_RCDC_OFFSET)
#define R_COMA_CABPIBWMC0                 (R_COMA_BASE + R_COMA_CABPIBWMC0_OFFSET)
#define R_COMA_CABPIBWMC1                 (R_COMA_BASE + R_COMA_CABPIBWMC1_OFFSET)
#define R_COMA_CABPIBWMC2                 (R_COMA_BASE + R_COMA_CABPIBWMC2_OFFSET)
#define R_COMA_CABPIBWMC3                 (R_COMA_BASE + R_COMA_CABPIBWMC3_OFFSET)
#define R_COMA_CABPIBWMC4                 (R_COMA_BASE + R_COMA_CABPIBWMC4_OFFSET)
#define R_COMA_CABPIBWMC5                 (R_COMA_BASE + R_COMA_CABPIBWMC5_OFFSET)
#define R_COMA_CABPIBWMC6                 (R_COMA_BASE + R_COMA_CABPIBWMC6_OFFSET)
#define R_COMA_CABPIBWMC7                 (R_COMA_BASE + R_COMA_CABPIBWMC7_OFFSET)
#define R_COMA_CABPWMLC                 (R_COMA_BASE + R_COMA_CABPWMLC_OFFSET)
#define R_COMA_CABPPFLCI                 (R_COMA_BASE + R_COMA_CABPPFLCI_OFFSET)
#define R_COMA_CABPPWMLC0                 (R_COMA_BASE + R_COMA_CABPPWMLC0_OFFSET)
#define R_COMA_CABPPWMLC1                 (R_COMA_BASE + R_COMA_CABPPWMLC1_OFFSET)
#define R_COMA_CABPPWMLC2                 (R_COMA_BASE + R_COMA_CABPPWMLC2_OFFSET)
#define R_COMA_CABPPPFLC00                 (R_COMA_BASE + R_COMA_CABPPPFLC00_OFFSET)
#define R_COMA_CABPPPFLC01                 (R_COMA_BASE + R_COMA_CABPPPFLC01_OFFSET)
#define R_COMA_CABPPPFLC10                 (R_COMA_BASE + R_COMA_CABPPPFLC10_OFFSET)
#define R_COMA_CABPPPFLC11                 (R_COMA_BASE + R_COMA_CABPPPFLC11_OFFSET)
#define R_COMA_CABPPPFLC20                 (R_COMA_BASE + R_COMA_CABPPPFLC20_OFFSET)
#define R_COMA_CABPPPFLC21                 (R_COMA_BASE + R_COMA_CABPPPFLC21_OFFSET)
#define R_COMA_CABPULC0                 (R_COMA_BASE + R_COMA_CABPULC0_OFFSET)
#define R_COMA_CABPULC1                 (R_COMA_BASE + R_COMA_CABPULC1_OFFSET)
#define R_COMA_CABPULC2                 (R_COMA_BASE + R_COMA_CABPULC2_OFFSET)
#define R_COMA_CABPIRM                 (R_COMA_BASE + R_COMA_CABPIRM_OFFSET)
#define R_COMA_CABPPCM                 (R_COMA_BASE + R_COMA_CABPPCM_OFFSET)
#define R_COMA_CABPLCM                 (R_COMA_BASE + R_COMA_CABPLCM_OFFSET)
#define R_COMA_CABPCPM0                 (R_COMA_BASE + R_COMA_CABPCPM0_OFFSET)
#define R_COMA_CABPCPM1                 (R_COMA_BASE + R_COMA_CABPCPM1_OFFSET)
#define R_COMA_CABPCPM2                 (R_COMA_BASE + R_COMA_CABPCPM2_OFFSET)
#define R_COMA_CABPMCPM0                 (R_COMA_BASE + R_COMA_CABPMCPM0_OFFSET)
#define R_COMA_CABPMCPM1                 (R_COMA_BASE + R_COMA_CABPMCPM1_OFFSET)
#define R_COMA_CABPMCPM2                 (R_COMA_BASE + R_COMA_CABPMCPM2_OFFSET)
#define R_COMA_CARDNM                 (R_COMA_BASE + R_COMA_CARDNM_OFFSET)
#define R_COMA_CARDMNM                 (R_COMA_BASE + R_COMA_CARDMNM_OFFSET)
#define R_COMA_CARDCN                 (R_COMA_BASE + R_COMA_CARDCN_OFFSET)
#define R_COMA_CAEIS0                 (R_COMA_BASE + R_COMA_CAEIS0_OFFSET)
#define R_COMA_CAEIE0                 (R_COMA_BASE + R_COMA_CAEIE0_OFFSET)
#define R_COMA_CAEID0                 (R_COMA_BASE + R_COMA_CAEID0_OFFSET)
#define R_COMA_CAEIS1                 (R_COMA_BASE + R_COMA_CAEIS1_OFFSET)
#define R_COMA_CAEIE1                 (R_COMA_BASE + R_COMA_CAEIE1_OFFSET)
#define R_COMA_CAEID1                 (R_COMA_BASE + R_COMA_CAEID1_OFFSET)
#define R_COMA_CAMIS0                 (R_COMA_BASE + R_COMA_CAMIS0_OFFSET)
#define R_COMA_CAMIE0                 (R_COMA_BASE + R_COMA_CAMIE0_OFFSET)
#define R_COMA_CAMID0                 (R_COMA_BASE + R_COMA_CAMID0_OFFSET)
#define R_COMA_CAMIS1                 (R_COMA_BASE + R_COMA_CAMIS1_OFFSET)
#define R_COMA_CAMIE1                 (R_COMA_BASE + R_COMA_CAMIE1_OFFSET)
#define R_COMA_CAMID1                 (R_COMA_BASE + R_COMA_CAMID1_OFFSET)

/* Register bit definitions */
/* RIPV Register bit definitions */
#define R_COMA_RIPV_TIPV_SHIFT                    (0)  /* Top Module IP Version Number */
#define R_COMA_RIPV_TIPV_MASK                     0xf

#define R_COMA_RIPV_GWIPV_SHIFT                   (4)  /* Gateway CPU Agent IP Version Number */
#define R_COMA_RIPV_GWIPV_MASK                    0xf0

#define R_COMA_RIPV_FWIPV_SHIFT                   (8)  /* Forwarding Engine IP Version Number */
#define R_COMA_RIPV_FWIPV_MASK                    0xf00

#define R_COMA_RIPV_EAIPV_SHIFT                   (12)  /* Ethernet Agent IP Version Number */
#define R_COMA_RIPV_EAIPV_MASK                    0xf000

#define R_COMA_RIPV_FBIPV_SHIFT                   (16)  /* Fabric Bus IP Version Number */
#define R_COMA_RIPV_FBIPV_MASK                    0xf0000

#define R_COMA_RIPV_CAIPV_SHIFT                   (20)  /* Ethernet Common Agent IP Version Number */
#define R_COMA_RIPV_CAIPV_MASK                    0xf00000

/* RRC Register bit definitions */
#define R_COMA_RRC_RR                             (1 << 0)  /* Software Reset */

/* RCEC Register bit definitions */
#define R_COMA_RCEC_ACE0                          (1 << 0)  /* Agent i Clock Enable (i = 0 to 2) */

#define R_COMA_RCEC_ACE1                          (1 << 1)  /* Agent i Clock Enable (i = 0 to 2) */

#define R_COMA_RCEC_ACE2                          (1 << 2)  /* Agent i Clock Enable (i = 0 to 2) */

#define R_COMA_RCEC_RCE                           (1 << 16)  /* Clock Enable */

#define R_COMA_RCEC_ACE_SHIFT                     (0)  /* Agent Clock Enable */
#define R_COMA_RCEC_ACE_MASK                      0x7f

/* RCDC Register bit definitions */
#define R_COMA_RCDC_ACD2 TO ACD0_SHIFT            (0)  /* Agent i Clock Disable (i = 0 to 2) */
#define R_COMA_RCDC_ACD2 TO ACD0_MASK             0x7
#  define R_COMA_RCDC_ACD2 TO ACD0_0                      (0 << R_COMA_RCDC_ACD2 TO ACD0_SHIFT)  /* No effect */
#  define R_COMA_RCDC_ACD2 TO ACD0_1                      (1 << R_COMA_RCDC_ACD2 TO ACD0_SHIFT)  /* Clears bit i in RCEC.ACEi register */

#define R_COMA_RCDC_RCD                           (1 << 16)  /* Clock Disable */

#define R_COMA_RCDC_ACD_SHIFT                     (0)  /* Agent Clock Disable */
#define R_COMA_RCDC_ACD_MASK                      0x7f

/* CABPIBWMC Register bit definitions */
#define R_COMA_CABPIBWMC_IBUWMPN_SHIFT            (0)  /* IPV Based Unsecure Watermark Pointer Number */
#define R_COMA_CABPIBWMC_IBUWMPN_MASK             0x3ff

#define R_COMA_CABPIBWMC_IBSWMPN_SHIFT            (16)  /* IPV Based Secure Watermark Pointer Number */
#define R_COMA_CABPIBWMC_IBSWMPN_MASK             0x3ff0000

/* CABPWMLC Register bit definitions */
#define R_COMA_CABPWMLC_WMFL_SHIFT                (0)  /* Watermark Flush Level */
#define R_COMA_CABPWMLC_WMFL_MASK                 0x1fff

#define R_COMA_CABPWMLC_WMCL_SHIFT                (16)  /* Watermark Critical Level */
#define R_COMA_CABPWMLC_WMCL_MASK                 0x1fff0000

/* CABPPFLCI Register bit definitions */
#define R_COMA_CABPPFLCI_PDL_SHIFT                (0)  /* Pause De-Assertion Level */
#define R_COMA_CABPPFLCI_PDL_MASK                 0x3ff

#define R_COMA_CABPPFLCI_PAL_SHIFT                (16)  /* Pause Assertion Level */
#define R_COMA_CABPPFLCI_PAL_MASK                 0x3ff0000

/* CABPPWMLC Register bit definitions */
#define R_COMA_CABPPWMLC_PWMFL_SHIFT              (0)  /* Watermark Flush Level */
#define R_COMA_CABPPWMLC_PWMFL_MASK               0x3ff

#define R_COMA_CABPPWMLC_PWMCL_SHIFT              (16)  /* Watermark Critical Level */
#define R_COMA_CABPPWMLC_PWMCL_MASK               0x3ff0000

/* CABPPPFLC Register bit definitions */
#define R_COMA_CABPPPFLC_PPDL_SHIFT               (0)  /* Pause De-Assertion Level */
#define R_COMA_CABPPPFLC_PPDL_MASK                0x3ff

#define R_COMA_CABPPPFLC_PPAL_SHIFT               (16)  /* Pause Assertion Level */
#define R_COMA_CABPPPFLC_PPAL_MASK                0x3ff0000

/* CABPPPFLC Register bit definitions */
#define R_COMA_CABPPPFLC_PPDL_SHIFT               (0)  /* Pause De-Assertion Level */
#define R_COMA_CABPPPFLC_PPDL_MASK                0x3ff

#define R_COMA_CABPPPFLC_PPAL_SHIFT               (16)  /* Pause Assertion Level */
#define R_COMA_CABPPPFLC_PPAL_MASK                0x3ff0000

/* CABPPPFLC Register bit definitions */
#define R_COMA_CABPPPFLC_PPDL_SHIFT               (0)  /* Pause De-Assertion Level */
#define R_COMA_CABPPPFLC_PPDL_MASK                0x3ff

#define R_COMA_CABPPPFLC_PPAL_SHIFT               (16)  /* Pause Assertion Level */
#define R_COMA_CABPPPFLC_PPAL_MASK                0x3ff0000

/* CABPULC Register bit definitions */
#define R_COMA_CABPULC_MXNPN_SHIFT                (0)  /* Maximum Number of Pointer */
#define R_COMA_CABPULC_MXNPN_MASK                 0x3ff

#define R_COMA_CABPULC_MNNPN_SHIFT                (16)  /* Minimum Number of Pointer */
#define R_COMA_CABPULC_MNNPN_MASK                 0x3ff0000

/* CABPIRM Register bit definitions */
#define R_COMA_CABPIRM_BPIOG                      (1 << 0)  /* Buffer Pool Initialization Ongoing */

#define R_COMA_CABPIRM_BPR                        (1 << 1)  /* Buffer Pool Ready */

/* CABPPCM Register bit definitions */
#define R_COMA_CABPPCM_RPC_SHIFT                  (0)  /* Remaining Pointer Count */
#define R_COMA_CABPPCM_RPC_MASK                   0x1fff

#define R_COMA_CABPPCM_TPC_SHIFT                  (16)  /* Total Pointer Count */
#define R_COMA_CABPPCM_TPC_MASK                   0x1fff0000

/* CABPLCM Register bit definitions */
#define R_COMA_CABPLCM_LRC_SHIFT                  (0)  /* Least Remaining Pointer Count */
#define R_COMA_CABPLCM_LRC_MASK                   0x1fff

/* CABPCPM Register bit definitions */
#define R_COMA_CABPCPM_RPCP_SHIFT                 (0)  /* Received Pointer Count */
#define R_COMA_CABPCPM_RPCP_MASK                  0x1fff

/* CABPMCPM Register bit definitions */
#define R_COMA_CABPMCPM_RPMCP_SHIFT               (0)  /* Received Pointer Maximum Count */
#define R_COMA_CABPMCPM_RPMCP_MASK                0x1fff

/* CARDNM Register bit definitions */
#define R_COMA_CARDNM_RDNRR_SHIFT                 (0)  /* Rejected Descriptor Number in Reject RAM */
#define R_COMA_CARDNM_RDNRR_MASK                  0x1fff

/* CARDMNM Register bit definitions */
#define R_COMA_CARDMNM_RDMNRR_SHIFT               (0)  /* Rejected Descriptor Maximum Number in Reject RAM */
#define R_COMA_CARDMNM_RDMNRR_MASK                0x1fff

/* CARDCN Register bit definitions */
#define R_COMA_CARDCN_RDN_SHIFT                   (0)  /* Rejected Descriptor Number */
#define R_COMA_CARDCN_RDN_MASK                    0xffffffff

/* CAEIS0 Register bit definitions */
#define R_COMA_CAEIS0_BPOPS                       (1 << 8)  /* Buffer Pool Out of Pointer Status Flag */

#define R_COMA_CAEIS0_WMCLOS                      (1 << 9)  /* Watermark Critical Level Overtook Status Flag */

#define R_COMA_CAEIS0_WMFLOS                      (1 << 10)  /* Watermark Flush Level Overtook Status Flag */

#define R_COMA_CAEIS0_PECCES                      (1 << 0)  /* Pointer ECC Error Interrupt Status */

#define R_COMA_CAEIS0_DSECCES                     (1 << 1)  /* Descriptor ECC Error Interrupt Status */

#define R_COMA_CAEIS0_BPECCES                     (1 << 2)  /* Buffer Pool ECC Error Interrupt Status */

#define R_COMA_CAEIS0_EEIPLN_SHIFT                (16)  /* ECC Error Inducing Pointer Loss Number */
#define R_COMA_CAEIS0_EEIPLN_MASK                 0xf0000

/* CAEIE0 Register bit definitions */
#define R_COMA_CAEIE0_BPOPE                       (1 << 8)  /* Buffer Pool Out of Pointer Enable */

#define R_COMA_CAEIE0_WMCLOE                      (1 << 9)  /* Watermark Critical Level Overtook Enable */

#define R_COMA_CAEIE0_WMFLOE                      (1 << 10)  /* Watermark Flush Level Overtook Enable */

#define R_COMA_CAEIE0_PECCEE                      (1 << 0)  /* Pointer ECC Error Interrupt Enable */

#define R_COMA_CAEIE0_DSECCEE                     (1 << 1)  /* Descriptor ECC Error Interrupt Enable */

#define R_COMA_CAEIE0_BPECCEE                     (1 << 2)  /* Buffer Pool ECC Error Interrupt Enable */

/* CAEID0 Register bit definitions */
#define R_COMA_CAEID0_BPOPD                       (1 << 8)  /* Buffer Pool Out of Pointer Disable */

#define R_COMA_CAEID0_WMCLOD                      (1 << 9)  /* Watermark Critical Level Overtook Disable */

#define R_COMA_CAEID0_WMFLOD                      (1 << 10)  /* Watermark Flush Level Overtook Disable */

#define R_COMA_CAEID0_PECCED                      (1 << 0)  /* Pointer ECC Error Interrupt Disable */

#define R_COMA_CAEID0_DSECCED                     (1 << 1)  /* Descriptor ECC Error Interrupt Disable */

#define R_COMA_CAEID0_BPECCED                     (1 << 2)  /* Buffer Pool ECC Error Interrupt Disable */

/* CAEIS1 Register bit definitions */
#define R_COMA_CAEIS1_PWMCLOS2 TO PWMCLOS0_SHIFT  (0)  /* Port n Watermark Critical Level Overtook Status Flag (n = 0 to 2) */
#define R_COMA_CAEIS1_PWMCLOS2 TO PWMCLOS0_MASK   0x7

#define R_COMA_CAEIS1_PWMFLOS2 TO PWMFLOS0_SHIFT  (16)  /* Port n Watermark Flush Level Overtook Status Flag (n = 0 to 2) */
#define R_COMA_CAEIS1_PWMFLOS2 TO PWMFLOS0_MASK   0x70000

#define R_COMA_CAEIS1_PWMCLOS_SHIFT               (0)  /* Port Watermark Critical Level Overtook Status */
#define R_COMA_CAEIS1_PWMCLOS_MASK                0x7f

#define R_COMA_CAEIS1_PWMFLOS_SHIFT               (16)  /* Port Watermark Flush Level Overtook Status */
#define R_COMA_CAEIS1_PWMFLOS_MASK                0x7f0000

/* CAEIE1 Register bit definitions */
#define R_COMA_CAEIE1_PWMCLOE2 TO PWMCLOE0_SHIFT  (0)  /* Port n Watermark Critical Level Overtook Enable (n = 0 to 2) */
#define R_COMA_CAEIE1_PWMCLOE2 TO PWMCLOE0_MASK   0x7

#define R_COMA_CAEIE1_PWMFLOE2 TO PWMFLOE0_SHIFT  (16)  /* Port n Watermark Flush Level Overtook Enable (n = 0 to 2) */
#define R_COMA_CAEIE1_PWMFLOE2 TO PWMFLOE0_MASK   0x70000

#define R_COMA_CAEIE1_PWMCLOE_SHIFT               (0)  /* Port Watermark Critical Level Overtook Enable */
#define R_COMA_CAEIE1_PWMCLOE_MASK                0x7f

#define R_COMA_CAEIE1_PWMFLOE_SHIFT               (16)  /* Port Watermark Flush Level Overtook Enable */
#define R_COMA_CAEIE1_PWMFLOE_MASK                0x7f0000

/* CAEID1 Register bit definitions */
#define R_COMA_CAEID1_PWMCLOD2 TO PWMCLOD0_SHIFT  (0)  /* Port n Watermark Critical Level Overtook Disable (n = 0 to 2) */
#define R_COMA_CAEID1_PWMCLOD2 TO PWMCLOD0_MASK   0x7

#define R_COMA_CAEID1_PWMFLOD2 TO PWMFLOD0_SHIFT  (16)  /* Port n Watermark Flush Level Overtook Disable (n = 0 to 2) */
#define R_COMA_CAEID1_PWMFLOD2 TO PWMFLOD0_MASK   0x70000

#define R_COMA_CAEID1_PWMCLOD_SHIFT               (0)  /* Port Watermark Critical Level Overtook Disable */
#define R_COMA_CAEID1_PWMCLOD_MASK                0x7f

#define R_COMA_CAEID1_PWMFLOD_SHIFT               (16)  /* Port Watermark Flush Level Overtook Disable */
#define R_COMA_CAEID1_PWMFLOD_MASK                0x7f0000

/* CAMIS0 Register bit definitions */
#define R_COMA_CAMIS0_PFS1 TO PFS0_SHIFT          (0)  /* Pause Frame Status Flag n (n= 0 to 1) */
#define R_COMA_CAMIS0_PFS1 TO PFS0_MASK           0x3

#define R_COMA_CAMIS0_PFS_SHIFT                   (0)  /* Pause Frame Status */
#define R_COMA_CAMIS0_PFS_MASK                    0x3

/* CAMIE0 Register bit definitions */
#define R_COMA_CAMIE0_PFE1 TO PFE0_SHIFT          (0)  /* Pause Frame Enable n (n = 0 to 1) */
#define R_COMA_CAMIE0_PFE1 TO PFE0_MASK           0x3

#define R_COMA_CAMIE0_PFE_SHIFT                   (0)  /* Pause Frame Enable */
#define R_COMA_CAMIE0_PFE_MASK                    0x3

/* CAMID0 Register bit definitions */
#define R_COMA_CAMID0_PFD1 TO PFD0_SHIFT          (0)  /* Pause Frame Disable n (n = 0 to 1) */
#define R_COMA_CAMID0_PFD1 TO PFD0_MASK           0x3

#define R_COMA_CAMID0_PFD_SHIFT                   (0)  /* Pause Frame Disable */
#define R_COMA_CAMID0_PFD_MASK                    0x3

/* CAMIS1 Register bit definitions */
#define R_COMA_CAMIS1_PPFS00                      (1 << 0)  /* Port 0 Pause Frame Status Flag 0 */

#define R_COMA_CAMIS1_PPFS01                      (1 << 1)  /* Port 0 Pause Frame Status Flag 1 */

#define R_COMA_CAMIS1_PPFS10                      (1 << 2)  /* Port 1 Pause Frame Status Flag 0 */

#define R_COMA_CAMIS1_PPFS11                      (1 << 3)  /* Port 1 Pause Frame Status Flag 1 */

#define R_COMA_CAMIS1_PPFS20                      (1 << 4)  /* Port 2 Pause Frame Status Flag 0 */

#define R_COMA_CAMIS1_PPFS21                      (1 << 5)  /* Port 2 Pause Frame Status Flag 1 */

#define R_COMA_CAMIS1_PPFS_SHIFT                  (0)  /* Port Pause Frame Status */
#define R_COMA_CAMIS1_PPFS_MASK                   0x3fff

/* CAMIE1 Register bit definitions */
#define R_COMA_CAMIE1_PPFE00                      (1 << 0)  /* Port 0 Pause Frame Enable 0 */

#define R_COMA_CAMIE1_PPFE01                      (1 << 1)  /* Port 0 Pause Frame Enable 1 */

#define R_COMA_CAMIE1_PPFE10                      (1 << 2)  /* Port 1 Pause Frame Enable 0 */

#define R_COMA_CAMIE1_PPFE11                      (1 << 3)  /* Port 1 Pause Frame Enable 1 */

#define R_COMA_CAMIE1_PPFE20                      (1 << 4)  /* Port 2 Pause Frame Enable 0 */

#define R_COMA_CAMIE1_PPFE21                      (1 << 5)  /* Port 2 Pause Frame Enable 1 */

#define R_COMA_CAMIE1_PPFE_SHIFT                  (0)  /* Port Pause Frame Enable */
#define R_COMA_CAMIE1_PPFE_MASK                   0x3fff

/* CAMID1 Register bit definitions */
#define R_COMA_CAMID1_PPFD00                      (1 << 0)  /* Port 0 Pause Frame Disable 0 */

#define R_COMA_CAMID1_PPFD01                      (1 << 1)  /* Port 0 Pause Frame Disable 1 */

#define R_COMA_CAMID1_PPFD10                      (1 << 2)  /* Port 1 Pause Frame Disable 0 */

#define R_COMA_CAMID1_PPFD11                      (1 << 3)  /* Port 1 Pause Frame Disable 1 */

#define R_COMA_CAMID1_PPFD20                      (1 << 4)  /* Port 2 Pause Frame Disable 0 */

#define R_COMA_CAMID1_PPFD21                      (1 << 5)  /* Port 2 Pause Frame Disable 1 */

#define R_COMA_CAMID1_PPFD_SHIFT                  (0)  /* Port Pause Frame Disable */
#define R_COMA_CAMID1_PPFD_MASK                   0x3fff


/* Maximum number of channels */

#define COMA_MAX_CHANNELS    8

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_COMA_H */
