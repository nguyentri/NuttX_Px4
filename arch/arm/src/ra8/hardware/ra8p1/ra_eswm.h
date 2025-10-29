/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_eswm.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ESWM_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ESWM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ESWM Base Address */
#ifndef R_ESWM_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_ESWM_BASE           0x403c8000
#else
#define R_ESWM_BASE           0x503c8000
#endif
#endif

/* ESWM Register Offsets */

#define R_ESWM_TPEMIMC0_OFFSET                    0x00000000  /* Error and Monitoring Interrupt Mapping Configuration Register 0 */
#define R_ESWM_TPEMIMC1_OFFSET                    0x00000004  /* Error and Monitoring Interrupt Mapping Configuration Register 1 */
#define R_ESWM_TPEMIMC2_OFFSET                    0x00000008  /* Error and Monitoring Interrupt Mapping Configuration Register 2 */
#define R_ESWM_TPEMIMC3_OFFSET                    0x0000000c  /* Error and Monitoring Interrupt Mapping Configuration Register 3 */
#define R_ESWM_TPEMIMC4_OFFSET                    0x00000010  /* Error and Monitoring Interrupt Mapping Configuration Register 4 */
/* TPEMIMC6%s Registers (0-4) */
#define R_ESWM_TPEMIMC6_OFFSET(m)                 (0x00000080 + ((m) * 0x00000004))  /* Error and Monitoring Interrupt Mapping Configuration Register 6%s */
/* TPEMIMC7%s Registers (0-4) */
#define R_ESWM_TPEMIMC7_OFFSET(m)                 (0x00000100 + ((m) * 0x00000004))  /* Error and Monitoring Interrupt Mapping Configuration Register 7%s */
#define R_ESWM_TSIM_OFFSET                        0x00000700  /* Summarized Interrupt Mirroring Register */
#define R_ESWM_TFIM_OFFSET                        0x00000704  /* MFWD Interrupt Mirroring Register */
#define R_ESWM_TCIM_OFFSET                        0x00000708  /* COMA Interrupt Mirroring Register */
#define R_ESWM_TGIM0_OFFSET                       0x00000710  /* GWCA0 Interrupt Mirroring Register */
#define R_ESWM_TEIM0_OFFSET                       0x00000720  /* ETHA0 Interrupt Mirroring Register */
#define R_ESWM_TEIM1_OFFSET                       0x00000724  /* ETHA1 Interrupt Mirroring Register */
#define R_ESWM_MIIRR_OFFSET                       0x00019400  /* Media Interface Reset Register */
/* MIICR%s Registers (0-1) */
#define R_ESWM_MIICR_OFFSET(m)                    (0x00019404 + ((m) * 0x00000004))  /* Media Interface Control Register %s */
#define R_ESWM_MCCESR_OFFSET                      0x00019410  /* Media Clock Capture Event Select Register */
#define R_ESWM_TASSTSR_OFFSET                     0x00019420  /* TAS Status Monitor Signal Select Register */

/* ESWM Register Addresses */

#define R_ESWM_TPEMIMC0                           (R_ESWM_BASE + R_ESWM_TPEMIMC0_OFFSET)
#define R_ESWM_TPEMIMC1                           (R_ESWM_BASE + R_ESWM_TPEMIMC1_OFFSET)
#define R_ESWM_TPEMIMC2                           (R_ESWM_BASE + R_ESWM_TPEMIMC2_OFFSET)
#define R_ESWM_TPEMIMC3                           (R_ESWM_BASE + R_ESWM_TPEMIMC3_OFFSET)
#define R_ESWM_TPEMIMC4                           (R_ESWM_BASE + R_ESWM_TPEMIMC4_OFFSET)
#define R_ESWM_TPEMIMC6(m)                        (R_ESWM_BASE + R_ESWM_TPEMIMC6_OFFSET(m))
#define R_ESWM_TPEMIMC7(m)                        (R_ESWM_BASE + R_ESWM_TPEMIMC7_OFFSET(m))
#define R_ESWM_TSIM                               (R_ESWM_BASE + R_ESWM_TSIM_OFFSET)
#define R_ESWM_TFIM                               (R_ESWM_BASE + R_ESWM_TFIM_OFFSET)
#define R_ESWM_TCIM                               (R_ESWM_BASE + R_ESWM_TCIM_OFFSET)
#define R_ESWM_TGIM0                              (R_ESWM_BASE + R_ESWM_TGIM0_OFFSET)
#define R_ESWM_TEIM0                              (R_ESWM_BASE + R_ESWM_TEIM0_OFFSET)
#define R_ESWM_TEIM1                              (R_ESWM_BASE + R_ESWM_TEIM1_OFFSET)
#define R_ESWM_MIIRR                              (R_ESWM_BASE + R_ESWM_MIIRR_OFFSET)
#define R_ESWM_MIICR(m)                           (R_ESWM_BASE + R_ESWM_MIICR_OFFSET(m))
#define R_ESWM_MCCESR                             (R_ESWM_BASE + R_ESWM_MCCESR_OFFSET)
#define R_ESWM_TASSTSR                            (R_ESWM_BASE + R_ESWM_TASSTSR_OFFSET)

/* Register bit definitions */
/* TPEMIMC0 Register bit definitions */
#define R_ESWM_TPEMIMC0_SEIM                      (1 << 0)  /* Switch Error Interrupt Mapping */

#define R_ESWM_TPEMIMC0_SEIGM                     (1 << 1)  /* Switch Error Interrupt GWCA Mapping */

#define R_ESWM_TPEMIMC0_SEICM_SHIFT               (4)  /* Switch Error Interrupt Core Mapping */
#define R_ESWM_TPEMIMC0_SEICM_MASK                0x70

#define R_ESWM_TPEMIMC0_SSIM_S                    (1 << 16)  /* Switch Status Interrupt %s Mapping */

#define R_ESWM_TPEMIMC0_SSIGM_S                   (1 << 17)  /* Switch Status Interrupt %s GWCA Mapping */

#define R_ESWM_TPEMIMC0_SSICM_S_SHIFT             (20)  /* Switch Status Interrupt %s Core Mapping */
#define R_ESWM_TPEMIMC0_SSICM_S_MASK              0x700000

#define R_ESWM_TPEMIMC0_SSIM0                     (1 << 16)  /* Switch Status Interrupt 0 Mapping */

#define R_ESWM_TPEMIMC0_SSIGM0                    (1 << 17)  /* Switch Status Interrupt 0 GWCA Mapping */

#define R_ESWM_TPEMIMC0_SSICM0_SHIFT              (20)  /* Switch Status Interrupt 0 Core Mapping */
#define R_ESWM_TPEMIMC0_SSICM0_MASK               0x700000

#define R_ESWM_TPEMIMC0_SSIM1                     (1 << 24)  /* Switch Status Interrupt 1 Mapping */

#define R_ESWM_TPEMIMC0_SSIGM1                    (1 << 25)  /* Switch Status Interrupt 1 GWCA Mapping */

#define R_ESWM_TPEMIMC0_SSICM1_SHIFT              (28)  /* Switch Status Interrupt 1 Core Mapping */
#define R_ESWM_TPEMIMC0_SSICM1_MASK               0x70000000

/* TPEMIMC1 Register bit definitions */
#define R_ESWM_TPEMIMC1_FEIM                      (1 << 0)  /* MFWD Error Interrupt Mapping */

#define R_ESWM_TPEMIMC1_FEIGM                     (1 << 1)  /* MFWD Error Interrupt GWCA Mapping */

#define R_ESWM_TPEMIMC1_FEICM_SHIFT               (4)  /* MFWD Error Interrupt Core Mapping */
#define R_ESWM_TPEMIMC1_FEICM_MASK                0x70

#define R_ESWM_TPEMIMC1_FSIM                      (1 << 8)  /* MFWD Status Interrupt Mapping */

#define R_ESWM_TPEMIMC1_FSIGM                     (1 << 9)  /* MFWD Status Interrupt GWCA Mapping */

#define R_ESWM_TPEMIMC1_FSICM_SHIFT               (12)  /* MFWD Status Interrupt Core Mapping */
#define R_ESWM_TPEMIMC1_FSICM_MASK                0x7000

#define R_ESWM_TPEMIMC1_CEIM                      (1 << 16)  /* COMA Error Interrupt Mapping */

#define R_ESWM_TPEMIMC1_CEIGM                     (1 << 17)  /* COMA Error Interrupt GWCA Mapping */

#define R_ESWM_TPEMIMC1_CEICM_SHIFT               (20)  /* COMA Error Interrupt Core Mapping */
#define R_ESWM_TPEMIMC1_CEICM_MASK                0x700000

#define R_ESWM_TPEMIMC1_CSIM                      (1 << 24)  /* COMA Status Interrupt Mapping */

#define R_ESWM_TPEMIMC1_CSIGM                     (1 << 25)  /* COMA Status Interrupt GWCA Mapping */

#define R_ESWM_TPEMIMC1_CSICM_SHIFT               (28)  /* COMA Status Interrupt Core Mapping */
#define R_ESWM_TPEMIMC1_CSICM_MASK                0x70000000

/* TPEMIMC2 Register bit definitions */
#define R_ESWM_TPEMIMC2_GEIM0                     (1 << 0)  /* GWCA0 Error Interrupt Mapping */

#define R_ESWM_TPEMIMC2_GEIGM0                    (1 << 1)  /* GWCA0 Error Interrupt GWCA Mapping */

#define R_ESWM_TPEMIMC2_GEICM0_SHIFT              (4)  /* GWCA0 Error Interrupt Core Mapping */
#define R_ESWM_TPEMIMC2_GEICM0_MASK               0x70

#define R_ESWM_TPEMIMC2_GSIM0                     (1 << 8)  /* GWCA0 Status Interrupt Mapping */

#define R_ESWM_TPEMIMC2_GSIGM0                    (1 << 9)  /* GWCA0 Status Interrupt GWCA Mapping */

#define R_ESWM_TPEMIMC2_GSICM0_SHIFT              (12)  /* GWCA0 Status Interrupt Core Mapping */
#define R_ESWM_TPEMIMC2_GSICM0_MASK               0x7000

/* TPEMIMC3 Register bit definitions */
#define R_ESWM_TPEMIMC3_EEIM0                     (1 << 0)  /* ETHA0 Error Interrupt Mapping */

#define R_ESWM_TPEMIMC3_EEIGM0                    (1 << 1)  /* ETHA0 Error Interrupt GWCA Mapping */

#define R_ESWM_TPEMIMC3_EEICM0_SHIFT              (4)  /* ETHA0 Error Interrupt Core Mapping */
#define R_ESWM_TPEMIMC3_EEICM0_MASK               0x70

#define R_ESWM_TPEMIMC3_ESIM0                     (1 << 8)  /* ETHA0 Status Interrupt Mapping */

#define R_ESWM_TPEMIMC3_ESIGM0                    (1 << 9)  /* ETHA0 Status Interrupt GWCA Mapping */

#define R_ESWM_TPEMIMC3_ESICM0_SHIFT              (12)  /* ETHA0 Status Interrupt Core Mapping */
#define R_ESWM_TPEMIMC3_ESICM0_MASK               0x7000

#define R_ESWM_TPEMIMC3_RSIM0                     (1 << 16)  /* RMAC0 Status Interrupt Mapping */

#define R_ESWM_TPEMIMC3_RSIGM0                    (1 << 17)  /* RMAC0 Status Interrupt GWCA Mapping */

#define R_ESWM_TPEMIMC3_RSICM0_SHIFT              (20)  /* RMAC0 Status Interrupt Core Mapping */
#define R_ESWM_TPEMIMC3_RSICM0_MASK               0x700000

/* TPEMIMC4 Register bit definitions */
#define R_ESWM_TPEMIMC4_EEIM1                     (1 << 0)  /* ETHA1 Error Interrupt Mapping */

#define R_ESWM_TPEMIMC4_EEIGM1                    (1 << 1)  /* ETHA1 Error Interrupt GWCA Mapping */

#define R_ESWM_TPEMIMC4_EEICM1_SHIFT              (4)  /* ETHA1 Error Interrupt Core Mapping */
#define R_ESWM_TPEMIMC4_EEICM1_MASK               0x70

#define R_ESWM_TPEMIMC4_ESIM1                     (1 << 8)  /* ETHA1 Status Interrupt Mapping */

#define R_ESWM_TPEMIMC4_ESIGM1                    (1 << 9)  /* ETHA1 Status Interrupt GWCA Mapping */

#define R_ESWM_TPEMIMC4_ESICM1_SHIFT              (12)  /* ETHA1 Status Interrupt Core Mapping */
#define R_ESWM_TPEMIMC4_ESICM1_MASK               0x7000

#define R_ESWM_TPEMIMC4_RSIM1                     (1 << 16)  /* RMAC1 Status Interrupt Mapping */

#define R_ESWM_TPEMIMC4_RSIGM1                    (1 << 17)  /* RMAC1 Status Interrupt GWCA Mapping */

#define R_ESWM_TPEMIMC4_RSICM1_SHIFT              (20)  /* RMAC1 Status Interrupt Core Mapping */
#define R_ESWM_TPEMIMC4_RSICM1_MASK               0x700000

/* TPEMIMC Register bit definitions */
#define R_ESWM_TPEMIMC_GTSIM0                     (1 << 0)  /* GWCA0 Timestamp Interrupt Mapping */

#define R_ESWM_TPEMIMC_GTSICM0_SHIFT              (1)  /* GWCA0 Timestamp Interrupt Core Mapping */
#define R_ESWM_TPEMIMC_GTSICM0_MASK               0xe

/* TPEMIMC Register bit definitions */
#define R_ESWM_TPEMIMC_GDICM0_SHIFT               (0)  /* GWCA0 Data Interrupt Core Mapping */
#define R_ESWM_TPEMIMC_GDICM0_MASK                0x7

/* TSIM Register bit definitions */
#define R_ESWM_TSIM_FIM                           (1 << 0)  /* MFWD Interrupt Mirroring */

#define R_ESWM_TSIM_CIM                           (1 << 1)  /* COMA Interrupt Mirroring */

#define R_ESWM_TSIM_GIM_S                         (1 << 2)  /* GWCA%s Interrupt Monitoring */

#define R_ESWM_TSIM_EIM_S                         (1 << 4)  /* ETHA%s Interrupt Monitoring */

#define R_ESWM_TSIM_GIM0                          (1 << 2)  /* GWCA0 Interrupt Monitoring */

#define R_ESWM_TSIM_GIM1                          (1 << 3)  /* GWCA1 Interrupt Monitoring */

#define R_ESWM_TSIM_EIM0                          (1 << 4)  /* ETHA0 Interrupt Monitoring */

#define R_ESWM_TSIM_EIM1                          (1 << 5)  /* ETHA1 Interrupt Monitoring */

#define R_ESWM_TSIM_EIM2                          (1 << 6)  /* ETHA2 Interrupt Monitoring */

/* TFIM Register bit definitions */
#define R_ESWM_TFIM_FWEISIM_S                     (1 << 0)  /* FWEIS%s Interrupt Mirroring */

#define R_ESWM_TFIM_FWMISIM0                      (1 << 9)  /* FWMIS0 Interrupt Mirroring */

#define R_ESWM_TFIM_FWEISIM0                      (1 << 0)  /* FWEIS0 Interrupt Mirroring */

#define R_ESWM_TFIM_FWEISIM1                      (1 << 1)  /* FWEIS1 Interrupt Mirroring */

#define R_ESWM_TFIM_FWEISIM2                      (1 << 2)  /* FWEIS2 Interrupt Mirroring */

#define R_ESWM_TFIM_FWEISIM3                      (1 << 3)  /* FWEIS3 Interrupt Mirroring */

#define R_ESWM_TFIM_FWEISIM4                      (1 << 4)  /* FWEIS4 Interrupt Mirroring */

#define R_ESWM_TFIM_FWEISIM5                      (1 << 5)  /* FWEIS5 Interrupt Mirroring */

#define R_ESWM_TFIM_FWEISIM6                      (1 << 6)  /* FWEIS6 Interrupt Mirroring */

#define R_ESWM_TFIM_FWEISIM7                      (1 << 7)  /* FWEIS7 Interrupt Mirroring */

#define R_ESWM_TFIM_FWEISIM8                      (1 << 8)  /* FWEIS8 Interrupt Mirroring */

/* TCIM Register bit definitions */
#define R_ESWM_TCIM_RSSISIM                       (1 << 0)  /* RSSIS Interrupt Mirroring */

#define R_ESWM_TCIM_CAEISIM_S                     (1 << 1)  /* CAEIS%s Interrupt Mirroring */

#define R_ESWM_TCIM_CAMISIM_S                     (1 << 3)  /* CAMIS%s Interrupt Mirroring */

#define R_ESWM_TCIM_CAEISIM0                      (1 << 1)  /* CAEIS0 Interrupt Mirroring */

#define R_ESWM_TCIM_CAEISIM1                      (1 << 2)  /* CAEIS1 Interrupt Mirroring */

#define R_ESWM_TCIM_CAMISIM0                      (1 << 3)  /* CAMIS0 Interrupt Mirroring */

#define R_ESWM_TCIM_CAMISIM1                      (1 << 4)  /* CAMIS1 Interrupt Mirroring */

/* TGIM0 Register bit definitions */
#define R_ESWM_TGIM0_GWDISIM                      (1 << 0)  /* GWDIS Interrupt Mirroring */

#define R_ESWM_TGIM0_GWTSDISIM                    (1 << 1)  /* GWTSDIS Interrupt Mirroring */

#define R_ESWM_TGIM0_GWEISIM_S                    (1 << 2)  /* GWEIS%s Interrupt Mirroring */

#define R_ESWM_TGIM0_GWEISIM0                     (1 << 2)  /* GWEIS0 Interrupt Mirroring */

#define R_ESWM_TGIM0_GWEISIM1                     (1 << 3)  /* GWEIS1 Interrupt Mirroring */

#define R_ESWM_TGIM0_GWEISIM2                     (1 << 4)  /* GWEIS2 Interrupt Mirroring */

#define R_ESWM_TGIM0_GWEISIM3                     (1 << 5)  /* GWEIS3 Interrupt Mirroring */

#define R_ESWM_TGIM0_GWEISIM4                     (1 << 6)  /* GWEIS4 Interrupt Mirroring */

#define R_ESWM_TGIM0_GWEISIM5                     (1 << 7)  /* GWEIS5 Interrupt Mirroring */

/* TEIM0 Register bit definitions */
#define R_ESWM_TEIM0_EAEISIM_S                    (1 << 0)  /* EAEIS%s Interrupt Mirroring */

#define R_ESWM_TEIM0_MEISIM                       (1 << 3)  /* MEIS Interrupt Mirroring */

#define R_ESWM_TEIM0_MMISIM                       (1 << 4)  /* MMIS0 Interrupt Mirroring */

#define R_ESWM_TEIM0_EAEISIM0                     (1 << 0)  /* EAEIS0 Interrupt Mirroring */

#define R_ESWM_TEIM0_EAEISIM1                     (1 << 1)  /* EAEIS1 Interrupt Mirroring */

#define R_ESWM_TEIM0_EAEISIM2                     (1 << 2)  /* EAEIS2 Interrupt Mirroring */

/* TEIM1 Register bit definitions */
#define R_ESWM_TEIM1_EAEISIM_S                    (1 << 0)  /* EAEIS%s Interrupt Mirroring */

#define R_ESWM_TEIM1_MEISIM                       (1 << 3)  /* MEIS Interrupt Mirroring */

#define R_ESWM_TEIM1_MMISIM                       (1 << 4)  /* MMIS0 Interrupt Mirroring */

#define R_ESWM_TEIM1_EAEISIM0                     (1 << 0)  /* EAEIS0 Interrupt Mirroring */

#define R_ESWM_TEIM1_EAEISIM1                     (1 << 1)  /* EAEIS1 Interrupt Mirroring */

#define R_ESWM_TEIM1_EAEISIM2                     (1 << 2)  /* EAEIS2 Interrupt Mirroring */

/* MIIRR Register bit definitions */
#define R_ESWM_MIIRR_RGRST_S                      (1 << 0)  /* RGMII%s Interface Reset */

#define R_ESWM_MIIRR_RMRST_S                      (1 << 8)  /* RMII%s Interface Reset */

#define R_ESWM_MIIRR_RGRST0                       (1 << 0)  /* RGMII0 Interface Reset */

#define R_ESWM_MIIRR_RGRST1                       (1 << 1)  /* RGMII1 Interface Reset */

#define R_ESWM_MIIRR_RMRST0                       (1 << 8)  /* RMII0 Interface Reset */

#define R_ESWM_MIIRR_RMRST1                       (1 << 9)  /* RMII1 Interface Reset */

/* MIICR Register bit definitions */
#define R_ESWM_MIICR_MIISEL_SHIFT                 (0)  /* MII Select */
#define R_ESWM_MIICR_MIISEL_MASK                  0x3
#  define R_ESWM_MIICR_MIISEL_00                          (0 << R_ESWM_MIICR_MIISEL_SHIFT)  /* MII/GMII */
#  define R_ESWM_MIICR_MIISEL_01                          (1 << R_ESWM_MIICR_MIISEL_SHIFT)  /* RGMII */
#  define R_ESWM_MIICR_MIISEL_10                          (2 << R_ESWM_MIICR_MIISEL_SHIFT)  /* RMII */
#  define R_ESWM_MIICR_MIISEL_11                          (3 << R_ESWM_MIICR_MIISEL_SHIFT)  /* Setting prohibited */

#define R_ESWM_MIICR_DIVSTP                       (1 << 8)  /* Clock Divider Stop */

#define R_ESWM_MIICR_TXCIDE                       (1 << 12)  /* TXC Internal Delay Enable in RGMII */

/* MCCESR Register bit definitions */
#define R_ESWM_MCCESR_MCCES_S                     (1 << 0)  /* Media Clock Capture Event Select %s */

#define R_ESWM_MCCESR_MCCES0                      (1 << 0)  /* Media Clock Capture Event Select 0 */

#define R_ESWM_MCCESR_MCCES1                      (1 << 1)  /* Media Clock Capture Event Select 1 */

/* TASSTSR Register bit definitions */
#define R_ESWM_TASSTSR_MSS_S_SHIFT                (0)  /* Select signal to output ET_TAS_STA%s pin from race_etha0_tas_gate_state[8:0] and race_etha1_tas_gate_state[8:0] */
#define R_ESWM_TASSTSR_MSS_S_MASK                 0x1f

#define R_ESWM_TASSTSR_MSS0_SHIFT                 (0)  /* Select signal to output ET_TAS_STA pin from race_etha0_tas_gate_state[8 0] and race_etha1_tas_gate_state[8:0] */
#define R_ESWM_TASSTSR_MSS0_MASK                  0x1f

#define R_ESWM_TASSTSR_MSS1_SHIFT                 (8)  /* Select signal to output ET_TAS_STA pin from race_etha0_tas_gate_state[ :0] and race_etha1_tas_gate_state[8:0] */
#define R_ESWM_TASSTSR_MSS1_MASK                  0x1f00

#define R_ESWM_TASSTSR_MSS2_SHIFT                 (16)  /* Select signal to output ET_TAS_STA pin from race_etha0_tas_gate_state 8:0] and race_etha1_tas_gate_state[8:0] */
#define R_ESWM_TASSTSR_MSS2_MASK                  0x1f0000

#define R_ESWM_TASSTSR_MSS3_SHIFT                 (24)  /* Select signal to output ET_TAS_STA pin from race_etha0_tas_gate_state 8:0] and race_etha1_tas_gate_state[8:0] */
#define R_ESWM_TASSTSR_MSS3_MASK                  0x1f000000


/* Maximum number of channels */

#define ESWM_MAX_CHANNELS    5

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ESWM_H */
