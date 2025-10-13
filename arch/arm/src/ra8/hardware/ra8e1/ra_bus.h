/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_bus.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_BUS_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_BUS_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* BUS Base Address */
#ifndef R_BUS_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_BUS_BASE           0x40003000
#else
#define R_BUS_BASE           0x50003000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_BUS_CH_STRIDE    0x00000010
#define R_BUS_CH_BASE(ch)   (R_BUS_BASE + ((uint32_t)(ch) * R_BUS_CH_STRIDE))

/* BUS Register Offsets */

#define R_BUS_CS0CR_OFFSET                        0x00000802  /* CS0 Control Register */
/* CS%sCR Registers (1-7) */
#define R_BUS_CSCR_OFFSET                         0x00000812  /* CS%s Control Register */
#define R_BUS_CSCR_INCREMENT                      0x00000010
#define R_BUS_BUSOAD_OFFSET                       0x00001000  /* BUS Operation After Detection Register */
#define R_BUS_BUSOADPT_OFFSET                     0x00001004  /* BUS Operation After Detection Protect Register */
#define R_BUS_MSAOAD_OFFSET                       0x00001010  /* Master Security Attribution Operation After Detection Register */
#define R_BUS_MSAPT_OFFSET                        0x00001014  /* Master Security Attribution Protect Register */
#define R_BUS_BUSSABT1FHBI_OFFSET                 0x00001200  /* Bus Slave Arbitration Control Register 1(x = FHBI, S1BI) */
#define R_BUS_BUSSABT0FLBI_OFFSET                 0x00001210  /* Bus Slave Arbitration Control Register 0 */
#define R_BUS_BUSSABT1S1BI_OFFSET                 0x00001220  /* Bus Slave Arbitration Control Register 1(x = FHBI, S1BI) */
#define R_BUS_BUSSABT0STBYSBI_OFFSET              0x00001248  /* Bus Slave Arbitration Control Register 0 */
#define R_BUS_BUSSABT0EOBI_OFFSET                 0x00001258  /* Bus Slave Arbitration Control Register 0 */
#define R_BUS_BUSSABT0PBBI_OFFSET                 0x00001260  /* Bus Slave Arbitration Control Register 0 */
#define R_BUS_BUSSABT0PABI_OFFSET                 0x00001268  /* Bus Slave Arbitration Control Register 0 */
#define R_BUS_BUSSABT0PIBI_OFFSET                 0x00001270  /* Bus Slave Arbitration Control Register 0 */
#define R_BUS_BUSSABT0PSBI_OFFSET                 0x00001278  /* Bus Slave Arbitration Control Register 0 */
#define R_BUS_BUSDIVBYP_OFFSET                    0x00001300  /* Bus Divider Bypass Register */
/* BUS%sERRRW Registers (4-5) */
#define R_BUS_BUSERRRW_OFFSET                     0x00001804  /* BUS Error Read Write (n = 4, 5) */
#define R_BUS_BUSERRRW_INCREMENT                  0x00000010
/* BUS%sERRADD Registers (4-5) */
#define R_BUS_BUSERRADD_OFFSET                    0x00001830  /* BUS Error Address Register (n = 4, 5) */
#define R_BUS_BUSERRADD_INCREMENT                 0x00000010
/* BMSA%sERRADD Registers (4-5) */
#define R_BUS_BMSAERRADD_OFFSET                   0x00001900  /* Bus Master Security Attribution Unit Error Address */
#define R_BUS_BMSAERRADD_INCREMENT                0x00000010
/* BMSA%sERRRW Registers (4-5) */
#define R_BUS_BMSAERRRW_OFFSET                    0x00001904  /* BUS Master Security Attribution Unit Error Read Write (n = 4, 5) */
#define R_BUS_BMSAERRRW_INCREMENT                 0x00000010
/* BUS%sERRSTAT Registers (1-5) */
#define R_BUS_BUSERRSTAT_OFFSET                   0x00001a00  /* BUS Error Status Register */
#define R_BUS_BUSERRSTAT_INCREMENT                0x00000010
/* BUS%sERRCLR Registers (1-5) */
#define R_BUS_BUSERRCLR_OFFSET                    0x00001a08  /* BUS Error Clear Register */
#define R_BUS_BUSERRCLR_INCREMENT                 0x00000010
#define R_BUS_MBWERRSTAT_OFFSET                   0x00001b00  /* Master Bufferable Write Error Status Register */
#define R_BUS_MBWERRCLR_OFFSET                    0x00001b08  /* Master Bufferable Write Error Clear Register */
#define R_BUS_SBWERRSTAT_OFFSET                   0x00001b20  /* Slave Bufferable Write Error Status Register */
#define R_BUS_SBWERRCLR_OFFSET                    0x00001b28  /* Slave Bufferable Write Error Clear Register */

/* BUS Register Addresses */

#define R_BUS_CS0CR                               (R_BUS_BASE + R_BUS_CS0CR_OFFSET)
#define R_BUS_CSCR(n)                             (R_BUS_BASE + R_BUS_CSCR_OFFSET + (n)*0x00000010)
#define R_BUS_BUSOAD                              (R_BUS_BASE + R_BUS_BUSOAD_OFFSET)
#define R_BUS_BUSOADPT                            (R_BUS_BASE + R_BUS_BUSOADPT_OFFSET)
#define R_BUS_MSAOAD                              (R_BUS_BASE + R_BUS_MSAOAD_OFFSET)
#define R_BUS_MSAPT                               (R_BUS_BASE + R_BUS_MSAPT_OFFSET)
#define R_BUS_BUSSABT1FHBI                        (R_BUS_BASE + R_BUS_BUSSABT1FHBI_OFFSET)
#define R_BUS_BUSSABT0FLBI                        (R_BUS_BASE + R_BUS_BUSSABT0FLBI_OFFSET)
#define R_BUS_BUSSABT1S1BI                        (R_BUS_BASE + R_BUS_BUSSABT1S1BI_OFFSET)
#define R_BUS_BUSSABT0STBYSBI                     (R_BUS_BASE + R_BUS_BUSSABT0STBYSBI_OFFSET)
#define R_BUS_BUSSABT0EOBI                        (R_BUS_BASE + R_BUS_BUSSABT0EOBI_OFFSET)
#define R_BUS_BUSSABT0PBBI                        (R_BUS_BASE + R_BUS_BUSSABT0PBBI_OFFSET)
#define R_BUS_BUSSABT0PABI                        (R_BUS_BASE + R_BUS_BUSSABT0PABI_OFFSET)
#define R_BUS_BUSSABT0PIBI                        (R_BUS_BASE + R_BUS_BUSSABT0PIBI_OFFSET)
#define R_BUS_BUSSABT0PSBI                        (R_BUS_BASE + R_BUS_BUSSABT0PSBI_OFFSET)
#define R_BUS_BUSDIVBYP                           (R_BUS_BASE + R_BUS_BUSDIVBYP_OFFSET)
#define R_BUS_BUSERRRW(n)                         (R_BUS_BASE + R_BUS_BUSERRRW_OFFSET + (n)*0x00000010)
#define R_BUS_BUSERRADD(n)                        (R_BUS_BASE + R_BUS_BUSERRADD_OFFSET + (n)*0x00000010)
#define R_BUS_BMSAERRADD(n)                       (R_BUS_BASE + R_BUS_BMSAERRADD_OFFSET + (n)*0x00000010)
#define R_BUS_BMSAERRRW(n)                        (R_BUS_BASE + R_BUS_BMSAERRRW_OFFSET + (n)*0x00000010)
#define R_BUS_BUSERRSTAT(n)                       (R_BUS_BASE + R_BUS_BUSERRSTAT_OFFSET + (n)*0x00000010)
#define R_BUS_BUSERRCLR(n)                        (R_BUS_BASE + R_BUS_BUSERRCLR_OFFSET + (n)*0x00000010)
#define R_BUS_MBWERRSTAT                          (R_BUS_BASE + R_BUS_MBWERRSTAT_OFFSET)
#define R_BUS_MBWERRCLR                           (R_BUS_BASE + R_BUS_MBWERRCLR_OFFSET)
#define R_BUS_SBWERRSTAT                          (R_BUS_BASE + R_BUS_SBWERRSTAT_OFFSET)
#define R_BUS_SBWERRCLR                           (R_BUS_BASE + R_BUS_SBWERRCLR_OFFSET)

/* Register bit definitions */
/* CS0CR Register bit definitions */
#define R_BUS_CS0CR_EXENB                         (1 << 0)  /* Operation Enable */

#define R_BUS_CS0CR_BSIZE_SHIFT                   (4)  /* External Bus Width Select */
#define R_BUS_CS0CR_BSIZE_MASK                    0x30
#  define R_BUS_CS0CR_BSIZE_00                            (0 << R_BUS_CS0CR_BSIZE_SHIFT)  /* 16-bit bus space */
#  define R_BUS_CS0CR_BSIZE_10                            (2 << R_BUS_CS0CR_BSIZE_SHIFT)  /* 8-bit bus space */

#define R_BUS_CS0CR_EMODE                         (1 << 8)  /* Endian Mode */

#define R_BUS_CS0CR_MPXEN                         (1 << 12)  /* Address/Data Multiplexed I/O Interface Select */

/* CSCR Register bit definitions */
#define R_BUS_CSCR_EXENB                          (1 << 0)  /* Operation Enable */

#define R_BUS_CSCR_BSIZE_SHIFT                    (4)  /* External Bus Width Select */
#define R_BUS_CSCR_BSIZE_MASK                     0x30
#  define R_BUS_CSCR_BSIZE_00                             (0 << R_BUS_CSCR_BSIZE_SHIFT)  /* 16-bit bus space */
#  define R_BUS_CSCR_BSIZE_10                             (2 << R_BUS_CSCR_BSIZE_SHIFT)  /* 8-bit bus space */

#define R_BUS_CSCR_EMODE                          (1 << 8)  /* Endian Mode */

#define R_BUS_CSCR_MPXEN                          (1 << 12)  /* Address/Data Multiplexed I/O Interface Select */

/* BUSOAD Register bit definitions */
#define R_BUS_BUSOAD_ILERROAD                     (1 << 0)  /* Illegal address access error operation after detection */

#define R_BUS_BUSOAD_SLERROAD                     (1 << 1)  /* Slave bus error operation after detection */

#define R_BUS_BUSOAD_BWERROAD                     (1 << 2)  /* Bufferable write error operation after detection */

/* BUSOADPT Register bit definitions */
#define R_BUS_BUSOADPT_PROTECT                    (1 << 0)  /* Protection of register */

#define R_BUS_BUSOADPT_KEY_SHIFT                  (8)  /* Key code */
#define R_BUS_BUSOADPT_KEY_MASK                   0xff00

/* MSAOAD Register bit definitions */
#define R_BUS_MSAOAD_OAD                          (1 << 0)  /* Operation after detection */

#define R_BUS_MSAOAD_KEY_SHIFT                    (8)  /* Key Code */
#define R_BUS_MSAOAD_KEY_MASK                     0xff00

/* MSAPT Register bit definitions */
#define R_BUS_MSAPT_PROTECT                       (1 << 0)  /* Protection of register */

#define R_BUS_MSAPT_KEY_SHIFT                     (8)  /* Key Code */
#define R_BUS_MSAPT_KEY_MASK                      0xff00

/* BUSSABT1FHBI Register bit definitions */
#define R_BUS_BUSSABT1FHBI_ARBS_SHIFT             (0)  /* Arbitration Select for <slave> */
#define R_BUS_BUSSABT1FHBI_ARBS_MASK              0x3
#  define R_BUS_BUSSABT1FHBI_ARBS_00                      (0 << R_BUS_BUSSABT1FHBI_ARBS_SHIFT)  /* Fixed priority */
#  define R_BUS_BUSSABT1FHBI_ARBS_01                      (1 << R_BUS_BUSSABT1FHBI_ARBS_SHIFT)  /* Setting prohibited */
#  define R_BUS_BUSSABT1FHBI_ARBS_10                      (2 << R_BUS_BUSSABT1FHBI_ARBS_SHIFT)  /* Combination of round-robin and fixed priority */
#  define R_BUS_BUSSABT1FHBI_ARBS_11                      (3 << R_BUS_BUSSABT1FHBI_ARBS_SHIFT)  /* Round-robin */

/* BUSSABT0FLBI Register bit definitions */
#define R_BUS_BUSSABT0FLBI_ARBS                   (1 << 0)  /* Arbitration Select for <slave> */

/* BUSSABT1S1BI Register bit definitions */
#define R_BUS_BUSSABT1S1BI_ARBS_SHIFT             (0)  /* Arbitration Select for <slave> */
#define R_BUS_BUSSABT1S1BI_ARBS_MASK              0x3
#  define R_BUS_BUSSABT1S1BI_ARBS_00                      (0 << R_BUS_BUSSABT1S1BI_ARBS_SHIFT)  /* Fixed priority */
#  define R_BUS_BUSSABT1S1BI_ARBS_01                      (1 << R_BUS_BUSSABT1S1BI_ARBS_SHIFT)  /* Setting prohibited */
#  define R_BUS_BUSSABT1S1BI_ARBS_10                      (2 << R_BUS_BUSSABT1S1BI_ARBS_SHIFT)  /* Combination of round-robin and fixed priority */
#  define R_BUS_BUSSABT1S1BI_ARBS_11                      (3 << R_BUS_BUSSABT1S1BI_ARBS_SHIFT)  /* Round-robin */

/* BUSSABT0STBYSBI Register bit definitions */
#define R_BUS_BUSSABT0STBYSBI_ARBS                (1 << 0)  /* Arbitration Select for <slave> */

/* BUSSABT0EOBI Register bit definitions */
#define R_BUS_BUSSABT0EOBI_ARBS                   (1 << 0)  /* Arbitration Select for <slave> */

/* BUSSABT0PBBI Register bit definitions */
#define R_BUS_BUSSABT0PBBI_ARBS                   (1 << 0)  /* Arbitration Select for <slave> */

/* BUSSABT0PABI Register bit definitions */
#define R_BUS_BUSSABT0PABI_ARBS                   (1 << 0)  /* Arbitration Select for <slave> */

/* BUSSABT0PIBI Register bit definitions */
#define R_BUS_BUSSABT0PIBI_ARBS                   (1 << 0)  /* Arbitration Select for <slave> */

/* BUSSABT0PSBI Register bit definitions */
#define R_BUS_BUSSABT0PSBI_ARBS                   (1 << 0)  /* Arbitration Select for <slave> */

/* BUSDIVBYP Register bit definitions */
#define R_BUS_BUSDIVBYP_EDMABPE                   (1 << 0)  /* Divider for EDMACBI bypass enable */

#define R_BUS_BUSDIVBYP_CPU0SBPE                  (1 << 16)  /* Divider for CPUSAHBI bypass enable */

#define R_BUS_BUSDIVBYP_GDSSBPE                   (1 << 3)  /* Divider for GDSSBI bypass enable. */

/* BUSERRRW Register bit definitions */
#define R_BUS_BUSERRRW_RWSTAT                     (1 << 0)  /* Error access Read/Write Status */

/* BUSERRADD Register bit definitions */
#define R_BUS_BUSERRADD_BERAD_SHIFT               (0)  /* Bus Error Address */
#define R_BUS_BUSERRADD_BERAD_MASK                0xffffffff

/* BMSAERRADD Register bit definitions */
#define R_BUS_BMSAERRADD_MSERAD_SHIFT             (0)  /* Bus Master Security Attribution Unit Error Address */
#define R_BUS_BMSAERRADD_MSERAD_MASK              0xffffffff

/* BMSAERRRW Register bit definitions */
#define R_BUS_BMSAERRRW_MSARWSTAT                 (1 << 0)  /* Master Security Attribution Unit error access Read/Write Status */

/* BUSERRSTAT Register bit definitions */
#define R_BUS_BUSERRSTAT_SLERRSTAT                (1 << 0)  /* Slave Bus Error Status */

#define R_BUS_BUSERRSTAT_MMERRSTAT                (1 << 3)  /* Master MPU Error Status */

#define R_BUS_BUSERRSTAT_ILERRSTAT                (1 << 4)  /* Illegal Address Access Error Status */

#define R_BUS_BUSERRSTAT_MSERRSTAT                (1 << 5)  /* Master Security Attribution Unit Error Status */

/* BUSERRCLR Register bit definitions */
#define R_BUS_BUSERRCLR_SLERRCLR                  (1 << 0)  /* Slave Bus Error Clear */

#define R_BUS_BUSERRCLR_MMERRCLR                  (1 << 3)  /* Master MPU Error Clear */

#define R_BUS_BUSERRCLR_ILERRCLR                  (1 << 4)  /* Illegal Address Access Error Clear */

#define R_BUS_BUSERRCLR_MSERRCLR                  (1 << 5)  /* Master Security Attribution Unit Error Clear */

/* BUSERRSTAT Register bit definitions */
#define R_BUS_BUSERRSTAT_SLERRSTAT                (1 << 0)  /* Slave Bus Error Status */

#define R_BUS_BUSERRSTAT_MMERRSTAT                (1 << 3)  /* Master MPU Error Status */

#define R_BUS_BUSERRSTAT_ILERRSTAT                (1 << 4)  /* Illegal Address Access Error Status */

#define R_BUS_BUSERRSTAT_MSERRSTAT                (1 << 5)  /* Master Security Attribution Unit Error Status */

/* BUSERRCLR Register bit definitions */
#define R_BUS_BUSERRCLR_SLERRCLR                  (1 << 0)  /* Slave Bus Error Clear */

#define R_BUS_BUSERRCLR_MMERRCLR                  (1 << 3)  /* Master MPU Error Clear */

#define R_BUS_BUSERRCLR_ILERRCLR                  (1 << 4)  /* Illegal Address Access Error Clear */

#define R_BUS_BUSERRCLR_MSERRCLR                  (1 << 5)  /* Master Security Attribution Unit Error Clear */

/* MBWERRSTAT Register bit definitions */
#define R_BUS_MBWERRSTAT_MBWERR0                  (1 << 0)  /* Master Bufferable Write Error */

#define R_BUS_MBWERRSTAT_MBWERR1                  (1 << 1)  /* Master Bufferable Write Error */

#define R_BUS_MBWERRSTAT_MBWERR8                  (1 << 8)  /* Master Bufferable Write Error */

#define R_BUS_MBWERRSTAT_MBWERR16                 (1 << 16)  /* Master Bufferable Write Error */

#define R_BUS_MBWERRSTAT_MBWERR21                 (1 << 21)  /* Master Bufferable Write Error */

/* MBWERRCLR Register bit definitions */
#define R_BUS_MBWERRCLR_MBWECLR0                  (1 << 0)  /* Master Bufferable Write Error Clear */

#define R_BUS_MBWERRCLR_MBWECLR1                  (1 << 1)  /* Master Bufferable Write Error Clear */

#define R_BUS_MBWERRCLR_MBWECLR8                  (1 << 8)  /* Master Bufferable Write Error Clear */

#define R_BUS_MBWERRCLR_MBWECLR16                 (1 << 16)  /* Master Bufferable Write Error Clear */

#define R_BUS_MBWERRCLR_MBWECLR21                 (1 << 21)  /* Master Bufferable Write Error Clear */

/* SBWERRSTAT Register bit definitions */
#define R_BUS_SBWERRSTAT_SBWERR0                  (1 << 0)  /* Slave Bufferable Write Error */

#define R_BUS_SBWERRSTAT_SBWERR1                  (1 << 1)  /* Slave Bufferable Write Error */

#define R_BUS_SBWERRSTAT_SBWERR2                  (1 << 2)  /* Slave Bufferable Write Error */

#define R_BUS_SBWERRSTAT_SBWERR4                  (1 << 4)  /* Slave Bufferable Write Error */

#define R_BUS_SBWERRSTAT_SBWERR5                  (1 << 5)  /* Slave Bufferable Write Error */

#define R_BUS_SBWERRSTAT_SBWERR7                  (1 << 7)  /* Slave Bufferable Write Error */

#define R_BUS_SBWERRSTAT_SBWERR8                  (1 << 8)  /* Slave Bufferable Write Error */

#define R_BUS_SBWERRSTAT_SBWERR9                  (1 << 9)  /* Slave Bufferable Write Error */

#define R_BUS_SBWERRSTAT_SBWERR10                 (1 << 10)  /* Slave Bufferable Write Error */

#define R_BUS_SBWERRSTAT_SBWERR11                 (1 << 11)  /* Slave Bufferable Write Error */

#define R_BUS_SBWERRSTAT_SBWERR12                 (1 << 12)  /* Slave Bufferable Write Error */

/* SBWERRCLR Register bit definitions */
#define R_BUS_SBWERRCLR_SBWECLR0                  (1 << 0)  /* Slave Bufferable Write Error Clear */

#define R_BUS_SBWERRCLR_SBWECLR1                  (1 << 1)  /* Slave Bufferable Write Error Clear */

#define R_BUS_SBWERRCLR_SBWECLR2                  (1 << 2)  /* Slave Bufferable Write Error Clear */

#define R_BUS_SBWERRCLR_SBWECLR4                  (1 << 4)  /* Slave Bufferable Write Error Clear */

#define R_BUS_SBWERRCLR_SBWECLR5                  (1 << 5)  /* Slave Bufferable Write Error Clear */

#define R_BUS_SBWERRCLR_SBWECLR7                  (1 << 7)  /* Slave Bufferable Write Error Clear */

#define R_BUS_SBWERRCLR_SBWECLR8                  (1 << 8)  /* Slave Bufferable Write Error Clear */

#define R_BUS_SBWERRCLR_SBWECLR9                  (1 << 9)  /* Slave Bufferable Write Error Clear */

#define R_BUS_SBWERRCLR_SBWECLR10                 (1 << 10)  /* Slave Bufferable Write Error Clear */

#define R_BUS_SBWERRCLR_SBWECLR11                 (1 << 11)  /* Slave Bufferable Write Error Clear */

#define R_BUS_SBWERRCLR_SBWECLR12                 (1 << 12)  /* Slave Bufferable Write Error Clear */


/* Maximum number of channels */

#define BUS_MAX_CHANNELS    7

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_BUS_H */
