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

/* CS%sMOD Registers (0-7) */
#define R_BUS_CS0MOD_OFFSET     0x00000002  /* CS0 Mode Register (n = 0 to 7) */
#define R_BUS_CS1MOD_OFFSET     0x00000012  /* CS1 Mode Register (n = 0 to 7) */
#define R_BUS_CS2MOD_OFFSET     0x00000022  /* CS2 Mode Register (n = 0 to 7) */
#define R_BUS_CS3MOD_OFFSET     0x00000032  /* CS3 Mode Register (n = 0 to 7) */
#define R_BUS_CS4MOD_OFFSET     0x00000042  /* CS4 Mode Register (n = 0 to 7) */
#define R_BUS_CS5MOD_OFFSET     0x00000052  /* CS5 Mode Register (n = 0 to 7) */
#define R_BUS_CS6MOD_OFFSET     0x00000062  /* CS6 Mode Register (n = 0 to 7) */
#define R_BUS_CS7MOD_OFFSET     0x00000072  /* CS7 Mode Register (n = 0 to 7) */
/* CS%sWCR1 Registers (0-7) */
#define R_BUS_CS0WCR1_OFFSET     0x00000004  /* CS0 Wait Control Register 1 (n = 0 to 7) */
#define R_BUS_CS1WCR1_OFFSET     0x00000014  /* CS1 Wait Control Register 1 (n = 0 to 7) */
#define R_BUS_CS2WCR1_OFFSET     0x00000024  /* CS2 Wait Control Register 1 (n = 0 to 7) */
#define R_BUS_CS3WCR1_OFFSET     0x00000034  /* CS3 Wait Control Register 1 (n = 0 to 7) */
#define R_BUS_CS4WCR1_OFFSET     0x00000044  /* CS4 Wait Control Register 1 (n = 0 to 7) */
#define R_BUS_CS5WCR1_OFFSET     0x00000054  /* CS5 Wait Control Register 1 (n = 0 to 7) */
#define R_BUS_CS6WCR1_OFFSET     0x00000064  /* CS6 Wait Control Register 1 (n = 0 to 7) */
#define R_BUS_CS7WCR1_OFFSET     0x00000074  /* CS7 Wait Control Register 1 (n = 0 to 7) */
/* CS%sWCR2 Registers (0-7) */
#define R_BUS_CS0WCR2_OFFSET     0x00000008  /* CS0 Wait Control Register 2 (n = 0 to 7) */
#define R_BUS_CS1WCR2_OFFSET     0x00000018  /* CS1 Wait Control Register 2 (n = 0 to 7) */
#define R_BUS_CS2WCR2_OFFSET     0x00000028  /* CS2 Wait Control Register 2 (n = 0 to 7) */
#define R_BUS_CS3WCR2_OFFSET     0x00000038  /* CS3 Wait Control Register 2 (n = 0 to 7) */
#define R_BUS_CS4WCR2_OFFSET     0x00000048  /* CS4 Wait Control Register 2 (n = 0 to 7) */
#define R_BUS_CS5WCR2_OFFSET     0x00000058  /* CS5 Wait Control Register 2 (n = 0 to 7) */
#define R_BUS_CS6WCR2_OFFSET     0x00000068  /* CS6 Wait Control Register 2 (n = 0 to 7) */
#define R_BUS_CS7WCR2_OFFSET     0x00000078  /* CS7 Wait Control Register 2 (n = 0 to 7) */
#define R_BUS_CS0CR_OFFSET     0x00000802  /* CS0 Control Register */
/* CS%sREC Registers (0-7) */
#define R_BUS_CS0REC_OFFSET     0x0000080a  /* CS0 Recovery Cycle Register (n = 0 to 7) */
#define R_BUS_CS1REC_OFFSET     0x0000081a  /* CS1 Recovery Cycle Register (n = 0 to 7) */
#define R_BUS_CS2REC_OFFSET     0x0000082a  /* CS2 Recovery Cycle Register (n = 0 to 7) */
#define R_BUS_CS3REC_OFFSET     0x0000083a  /* CS3 Recovery Cycle Register (n = 0 to 7) */
#define R_BUS_CS4REC_OFFSET     0x0000084a  /* CS4 Recovery Cycle Register (n = 0 to 7) */
#define R_BUS_CS5REC_OFFSET     0x0000085a  /* CS5 Recovery Cycle Register (n = 0 to 7) */
#define R_BUS_CS6REC_OFFSET     0x0000086a  /* CS6 Recovery Cycle Register (n = 0 to 7) */
#define R_BUS_CS7REC_OFFSET     0x0000087a  /* CS7 Recovery Cycle Register (n = 0 to 7) */
/* CS%sCR Registers (1-7) */
#define R_BUS_CS1CR_OFFSET     0x00000812  /* CS1 Control Register */
#define R_BUS_CS2CR_OFFSET     0x00000822  /* CS2 Control Register */
#define R_BUS_CS3CR_OFFSET     0x00000832  /* CS3 Control Register */
#define R_BUS_CS4CR_OFFSET     0x00000842  /* CS4 Control Register */
#define R_BUS_CS5CR_OFFSET     0x00000852  /* CS5 Control Register */
#define R_BUS_CS6CR_OFFSET     0x00000862  /* CS6 Control Register */
#define R_BUS_CS7CR_OFFSET     0x00000872  /* CS7 Control Register */
#define R_BUS_CSRECEN_OFFSET     0x00000880  /* CS Recovery Cycle Insertion Enable Register */
#define R_BUS_SDCCR_OFFSET     0x00000c00  /* SDC Control Register */
#define R_BUS_SDCMOD_OFFSET     0x00000c01  /* SDC Mode Register */
#define R_BUS_SDAMOD_OFFSET     0x00000c02  /* SDRAM Access Mode Register */
#define R_BUS_SDSELF_OFFSET     0x00000c10  /* SDRAM Self-Refresh Control Register */
#define R_BUS_SDRFCR_OFFSET     0x00000c14  /* SDRAM Refresh Control Register */
#define R_BUS_SDRFEN_OFFSET     0x00000c16  /* SDRAM Auto-Refresh Control Register */
#define R_BUS_SDICR_OFFSET     0x00000c20  /* SDRAM Initialization Sequence Control Register */
#define R_BUS_SDIR_OFFSET     0x00000c24  /* SDRAM Initialization Register */
#define R_BUS_SDADR_OFFSET     0x00000c40  /* SDRAM Address Register */
#define R_BUS_SDTR_OFFSET     0x00000c44  /* SDRAM Timing Register */
#define R_BUS_SDMOD_OFFSET     0x00000c48  /* SDRAM Mode Register */
#define R_BUS_SDSR_OFFSET     0x00000c50  /* SDRAM Status Register */
#define R_BUS_BUSOAD_OFFSET     0x00001000  /* BUS Operation After Detection Register */
#define R_BUS_BUSOADPT_OFFSET     0x00001004  /* BUS Operation After Detection Protect Register */
#define R_BUS_MSAOAD_OFFSET     0x00001010  /* Master Security Attribution Operation After Detection Register */
#define R_BUS_MSAPT_OFFSET     0x00001014  /* Master Security Attribution Protect Register */
#define R_BUS_BUSMABTGRAPHBI_OFFSET     0x00001100  /* Bus Master Arbitration Control Register */
#define R_BUS_BUSSABT1MRC0BI_OFFSET     0x00001200  /* Bus Slave Arbitration Control Register 1 */
#define R_BUS_BUSSABT0MRE0BI_OFFSET     0x00001208  /* Bus Slave Arbitration Control Register 0 */
#define R_BUS_BUSSABT0S0BI_OFFSET     0x00001220  /* Bus Slave Arbitration Control Register 0 */
#define R_BUS_BUSSABT0S1BI_OFFSET     0x00001228  /* Bus Slave Arbitration Control Register 0 */
#define R_BUS_BUSSABT0S2BI_OFFSET     0x00001230  /* Bus Slave Arbitration Control Register 0 */
#define R_BUS_BUSSABT0S3BI_OFFSET     0x00001238  /* Bus Slave Arbitration Control Register 0 */
#define R_BUS_BUSSABT0ECBI_OFFSET     0x00001250  /* Bus Slave Arbitration Control Register 0 */
#define R_BUS_BUSSABT0OSPI0BI_OFFSET     0x00001258  /* Bus Slave Arbitration Control Register 0 */
#define R_BUS_BUSSABT0OSPI1BI_OFFSET     0x00001260  /* Bus Slave Arbitration Control Register 0 */
#define R_BUS_BUSSABT0CPU0SAHBI_OFFSET     0x00001268  /* Bus Slave Arbitration Control Register 0 */
#define R_BUS_BUSSABT0CPU1TCMBI_OFFSET     0x00001270  /* Bus Slave Arbitration Control Register 0 */
#define R_BUS_BUSSABT0PBBI_OFFSET     0x00001278  /* Bus Slave Arbitration Control Register 0 */
#define R_BUS_BUSSABT0PABI_OFFSET     0x00001280  /* Bus Slave Arbitration Control Register 0 */
#define R_BUS_BUSSABT0PIBI_OFFSET     0x00001288  /* Bus Slave Arbitration Control Register 0 */
#define R_BUS_BUSSABT0PSBI_OFFSET     0x00001290  /* Bus Slave Arbitration Control Register 0 */
#define R_BUS_BUSERRSTATCPU0_OFFSET     0x00001a00  /* BUS Error Status Register */
#define R_BUS_BUSERRCLRCPU0_OFFSET     0x00001a04  /* BUS Error Clear Register */
#define R_BUS_BUSIRQENCPU0_OFFSET     0x00001a08  /* BUS Error Interrupt Enable Register */
#define R_BUS_BUSERRSTATCPU1_OFFSET     0x00001a10  /* BUS Error Status Register */
#define R_BUS_BUSERRCLRCPU1_OFFSET     0x00001a14  /* BUS Error Clear Register */
#define R_BUS_BUSIRQENCPU1_OFFSET     0x00001a18  /* BUS Error Interrupt Enable Register */
#define R_BUS_BUSERRSTATDMAC0_OFFSET     0x00001a20  /* BUS Error Status Register */
#define R_BUS_BUSERRCLRDMAC0_OFFSET     0x00001a24  /* BUS Error Clear Register */
#define R_BUS_BUSIRQENDMAC0_OFFSET     0x00001a28  /* BUS Error Interrupt Enable Register */
#define R_BUS_BUSERRSTATDMAC1_OFFSET     0x00001a30  /* BUS Error Status Register */
#define R_BUS_BUSERRCLRDMAC1_OFFSET     0x00001a34  /* BUS Error Clear Register */
#define R_BUS_BUSIRQENDMAC1_OFFSET     0x00001a38  /* BUS Error Interrupt Enable Register */
#define R_BUS_BUSERRSTATNPU_OFFSET     0x00001a40  /* BUS Error Status Register */
#define R_BUS_BUSERRCLRNPU_OFFSET     0x00001a44  /* BUS Error Clear Register */
#define R_BUS_BUSIRQENNPU_OFFSET     0x00001a48  /* BUS Error Interrupt Enable Register */
#define R_BUS_BUSERRSTATEDMAC_OFFSET     0x00001a50  /* BUS Error Status Register */
#define R_BUS_BUSERRCLREDMAC_OFFSET     0x00001a54  /* BUS Error Clear Register */
#define R_BUS_BUSIRQENEDMAC_OFFSET     0x00001a58  /* BUS Error Interrupt Enable Register */
#define R_BUS_BUSERRSTATGLCDC_OFFSET     0x00001a60  /* BUS Error Status Register */
#define R_BUS_BUSERRCLRGLCDC_OFFSET     0x00001a64  /* BUS Error Clear Register */
#define R_BUS_BUSIRQENGLCDC_OFFSET     0x00001a68  /* BUS Error Interrupt Enable Register */
#define R_BUS_BUSERRSTATTDRW_OFFSET     0x00001a70  /* BUS Error Status Register */
#define R_BUS_BUSERRCLRTDRW_OFFSET     0x00001a74  /* BUS Error Clear Register */
#define R_BUS_BUSIRQENTDRW_OFFSET     0x00001a78  /* BUS Error Interrupt Enable Register */
#define R_BUS_BUSERRSTATMIPI0_OFFSET     0x00001a80  /* BUS Error Status Register */
#define R_BUS_BUSERRCLRMIPI0_OFFSET     0x00001a84  /* BUS Error Clear Register */
#define R_BUS_BUSIRQENMIPI0_OFFSET     0x00001a88  /* BUS Error Interrupt Enable Register */
#define R_BUS_BUSERRSTATMIPI1_OFFSET     0x00001a90  /* BUS Error Status Register */
#define R_BUS_BUSERRCLRMIPI1_OFFSET     0x00001a94  /* BUS Error Clear Register */
#define R_BUS_BUSIRQENMIPI1_OFFSET     0x00001a98  /* BUS Error Interrupt Enable Register */
#define R_BUS_BUSERRSTATCEU_OFFSET     0x00001aa0  /* BUS Error Status Register */
#define R_BUS_BUSERRCLRCEU_OFFSET     0x00001aa4  /* BUS Error Clear Register */
#define R_BUS_BUSIRQENCEU_OFFSET     0x00001aa8  /* BUS Error Interrupt Enable Register */
#define R_BUS_MBWERRSTAT_OFFSET     0x00001b00  /* Master Bufferable Write Error Status Register */
#define R_BUS_MBWERRCLR_OFFSET     0x00001b08  /* Master Bufferable Write Error Clear Register */

/* BUS Register Addresses */

#define R_BUS_CS0MOD                 (R_BUS_BASE + R_BUS_CS0MOD_OFFSET)
#define R_BUS_CS1MOD                 (R_BUS_BASE + R_BUS_CS1MOD_OFFSET)
#define R_BUS_CS2MOD                 (R_BUS_BASE + R_BUS_CS2MOD_OFFSET)
#define R_BUS_CS3MOD                 (R_BUS_BASE + R_BUS_CS3MOD_OFFSET)
#define R_BUS_CS4MOD                 (R_BUS_BASE + R_BUS_CS4MOD_OFFSET)
#define R_BUS_CS5MOD                 (R_BUS_BASE + R_BUS_CS5MOD_OFFSET)
#define R_BUS_CS6MOD                 (R_BUS_BASE + R_BUS_CS6MOD_OFFSET)
#define R_BUS_CS7MOD                 (R_BUS_BASE + R_BUS_CS7MOD_OFFSET)
#define R_BUS_CS0WCR1                 (R_BUS_BASE + R_BUS_CS0WCR1_OFFSET)
#define R_BUS_CS1WCR1                 (R_BUS_BASE + R_BUS_CS1WCR1_OFFSET)
#define R_BUS_CS2WCR1                 (R_BUS_BASE + R_BUS_CS2WCR1_OFFSET)
#define R_BUS_CS3WCR1                 (R_BUS_BASE + R_BUS_CS3WCR1_OFFSET)
#define R_BUS_CS4WCR1                 (R_BUS_BASE + R_BUS_CS4WCR1_OFFSET)
#define R_BUS_CS5WCR1                 (R_BUS_BASE + R_BUS_CS5WCR1_OFFSET)
#define R_BUS_CS6WCR1                 (R_BUS_BASE + R_BUS_CS6WCR1_OFFSET)
#define R_BUS_CS7WCR1                 (R_BUS_BASE + R_BUS_CS7WCR1_OFFSET)
#define R_BUS_CS0WCR2                 (R_BUS_BASE + R_BUS_CS0WCR2_OFFSET)
#define R_BUS_CS1WCR2                 (R_BUS_BASE + R_BUS_CS1WCR2_OFFSET)
#define R_BUS_CS2WCR2                 (R_BUS_BASE + R_BUS_CS2WCR2_OFFSET)
#define R_BUS_CS3WCR2                 (R_BUS_BASE + R_BUS_CS3WCR2_OFFSET)
#define R_BUS_CS4WCR2                 (R_BUS_BASE + R_BUS_CS4WCR2_OFFSET)
#define R_BUS_CS5WCR2                 (R_BUS_BASE + R_BUS_CS5WCR2_OFFSET)
#define R_BUS_CS6WCR2                 (R_BUS_BASE + R_BUS_CS6WCR2_OFFSET)
#define R_BUS_CS7WCR2                 (R_BUS_BASE + R_BUS_CS7WCR2_OFFSET)
#define R_BUS_CS0CR                 (R_BUS_BASE + R_BUS_CS0CR_OFFSET)
#define R_BUS_CS0REC                 (R_BUS_BASE + R_BUS_CS0REC_OFFSET)
#define R_BUS_CS1REC                 (R_BUS_BASE + R_BUS_CS1REC_OFFSET)
#define R_BUS_CS2REC                 (R_BUS_BASE + R_BUS_CS2REC_OFFSET)
#define R_BUS_CS3REC                 (R_BUS_BASE + R_BUS_CS3REC_OFFSET)
#define R_BUS_CS4REC                 (R_BUS_BASE + R_BUS_CS4REC_OFFSET)
#define R_BUS_CS5REC                 (R_BUS_BASE + R_BUS_CS5REC_OFFSET)
#define R_BUS_CS6REC                 (R_BUS_BASE + R_BUS_CS6REC_OFFSET)
#define R_BUS_CS7REC                 (R_BUS_BASE + R_BUS_CS7REC_OFFSET)
#define R_BUS_CS1CR                 (R_BUS_BASE + R_BUS_CS1CR_OFFSET)
#define R_BUS_CS2CR                 (R_BUS_BASE + R_BUS_CS2CR_OFFSET)
#define R_BUS_CS3CR                 (R_BUS_BASE + R_BUS_CS3CR_OFFSET)
#define R_BUS_CS4CR                 (R_BUS_BASE + R_BUS_CS4CR_OFFSET)
#define R_BUS_CS5CR                 (R_BUS_BASE + R_BUS_CS5CR_OFFSET)
#define R_BUS_CS6CR                 (R_BUS_BASE + R_BUS_CS6CR_OFFSET)
#define R_BUS_CS7CR                 (R_BUS_BASE + R_BUS_CS7CR_OFFSET)
#define R_BUS_CSRECEN                 (R_BUS_BASE + R_BUS_CSRECEN_OFFSET)
#define R_BUS_SDCCR                 (R_BUS_BASE + R_BUS_SDCCR_OFFSET)
#define R_BUS_SDCMOD                 (R_BUS_BASE + R_BUS_SDCMOD_OFFSET)
#define R_BUS_SDAMOD                 (R_BUS_BASE + R_BUS_SDAMOD_OFFSET)
#define R_BUS_SDSELF                 (R_BUS_BASE + R_BUS_SDSELF_OFFSET)
#define R_BUS_SDRFCR                 (R_BUS_BASE + R_BUS_SDRFCR_OFFSET)
#define R_BUS_SDRFEN                 (R_BUS_BASE + R_BUS_SDRFEN_OFFSET)
#define R_BUS_SDICR                 (R_BUS_BASE + R_BUS_SDICR_OFFSET)
#define R_BUS_SDIR                 (R_BUS_BASE + R_BUS_SDIR_OFFSET)
#define R_BUS_SDADR                 (R_BUS_BASE + R_BUS_SDADR_OFFSET)
#define R_BUS_SDTR                 (R_BUS_BASE + R_BUS_SDTR_OFFSET)
#define R_BUS_SDMOD                 (R_BUS_BASE + R_BUS_SDMOD_OFFSET)
#define R_BUS_SDSR                 (R_BUS_BASE + R_BUS_SDSR_OFFSET)
#define R_BUS_BUSOAD                 (R_BUS_BASE + R_BUS_BUSOAD_OFFSET)
#define R_BUS_BUSOADPT                 (R_BUS_BASE + R_BUS_BUSOADPT_OFFSET)
#define R_BUS_MSAOAD                 (R_BUS_BASE + R_BUS_MSAOAD_OFFSET)
#define R_BUS_MSAPT                 (R_BUS_BASE + R_BUS_MSAPT_OFFSET)
#define R_BUS_BUSMABTGRAPHBI                 (R_BUS_BASE + R_BUS_BUSMABTGRAPHBI_OFFSET)
#define R_BUS_BUSSABT1MRC0BI                 (R_BUS_BASE + R_BUS_BUSSABT1MRC0BI_OFFSET)
#define R_BUS_BUSSABT0MRE0BI                 (R_BUS_BASE + R_BUS_BUSSABT0MRE0BI_OFFSET)
#define R_BUS_BUSSABT0S0BI                 (R_BUS_BASE + R_BUS_BUSSABT0S0BI_OFFSET)
#define R_BUS_BUSSABT0S1BI                 (R_BUS_BASE + R_BUS_BUSSABT0S1BI_OFFSET)
#define R_BUS_BUSSABT0S2BI                 (R_BUS_BASE + R_BUS_BUSSABT0S2BI_OFFSET)
#define R_BUS_BUSSABT0S3BI                 (R_BUS_BASE + R_BUS_BUSSABT0S3BI_OFFSET)
#define R_BUS_BUSSABT0ECBI                 (R_BUS_BASE + R_BUS_BUSSABT0ECBI_OFFSET)
#define R_BUS_BUSSABT0OSPI0BI                 (R_BUS_BASE + R_BUS_BUSSABT0OSPI0BI_OFFSET)
#define R_BUS_BUSSABT0OSPI1BI                 (R_BUS_BASE + R_BUS_BUSSABT0OSPI1BI_OFFSET)
#define R_BUS_BUSSABT0CPU0SAHBI                 (R_BUS_BASE + R_BUS_BUSSABT0CPU0SAHBI_OFFSET)
#define R_BUS_BUSSABT0CPU1TCMBI                 (R_BUS_BASE + R_BUS_BUSSABT0CPU1TCMBI_OFFSET)
#define R_BUS_BUSSABT0PBBI                 (R_BUS_BASE + R_BUS_BUSSABT0PBBI_OFFSET)
#define R_BUS_BUSSABT0PABI                 (R_BUS_BASE + R_BUS_BUSSABT0PABI_OFFSET)
#define R_BUS_BUSSABT0PIBI                 (R_BUS_BASE + R_BUS_BUSSABT0PIBI_OFFSET)
#define R_BUS_BUSSABT0PSBI                 (R_BUS_BASE + R_BUS_BUSSABT0PSBI_OFFSET)
#define R_BUS_BUSERRSTATCPU0                 (R_BUS_BASE + R_BUS_BUSERRSTATCPU0_OFFSET)
#define R_BUS_BUSERRCLRCPU0                 (R_BUS_BASE + R_BUS_BUSERRCLRCPU0_OFFSET)
#define R_BUS_BUSIRQENCPU0                 (R_BUS_BASE + R_BUS_BUSIRQENCPU0_OFFSET)
#define R_BUS_BUSERRSTATCPU1                 (R_BUS_BASE + R_BUS_BUSERRSTATCPU1_OFFSET)
#define R_BUS_BUSERRCLRCPU1                 (R_BUS_BASE + R_BUS_BUSERRCLRCPU1_OFFSET)
#define R_BUS_BUSIRQENCPU1                 (R_BUS_BASE + R_BUS_BUSIRQENCPU1_OFFSET)
#define R_BUS_BUSERRSTATDMAC0                 (R_BUS_BASE + R_BUS_BUSERRSTATDMAC0_OFFSET)
#define R_BUS_BUSERRCLRDMAC0                 (R_BUS_BASE + R_BUS_BUSERRCLRDMAC0_OFFSET)
#define R_BUS_BUSIRQENDMAC0                 (R_BUS_BASE + R_BUS_BUSIRQENDMAC0_OFFSET)
#define R_BUS_BUSERRSTATDMAC1                 (R_BUS_BASE + R_BUS_BUSERRSTATDMAC1_OFFSET)
#define R_BUS_BUSERRCLRDMAC1                 (R_BUS_BASE + R_BUS_BUSERRCLRDMAC1_OFFSET)
#define R_BUS_BUSIRQENDMAC1                 (R_BUS_BASE + R_BUS_BUSIRQENDMAC1_OFFSET)
#define R_BUS_BUSERRSTATNPU                 (R_BUS_BASE + R_BUS_BUSERRSTATNPU_OFFSET)
#define R_BUS_BUSERRCLRNPU                 (R_BUS_BASE + R_BUS_BUSERRCLRNPU_OFFSET)
#define R_BUS_BUSIRQENNPU                 (R_BUS_BASE + R_BUS_BUSIRQENNPU_OFFSET)
#define R_BUS_BUSERRSTATEDMAC                 (R_BUS_BASE + R_BUS_BUSERRSTATEDMAC_OFFSET)
#define R_BUS_BUSERRCLREDMAC                 (R_BUS_BASE + R_BUS_BUSERRCLREDMAC_OFFSET)
#define R_BUS_BUSIRQENEDMAC                 (R_BUS_BASE + R_BUS_BUSIRQENEDMAC_OFFSET)
#define R_BUS_BUSERRSTATGLCDC                 (R_BUS_BASE + R_BUS_BUSERRSTATGLCDC_OFFSET)
#define R_BUS_BUSERRCLRGLCDC                 (R_BUS_BASE + R_BUS_BUSERRCLRGLCDC_OFFSET)
#define R_BUS_BUSIRQENGLCDC                 (R_BUS_BASE + R_BUS_BUSIRQENGLCDC_OFFSET)
#define R_BUS_BUSERRSTATTDRW                 (R_BUS_BASE + R_BUS_BUSERRSTATTDRW_OFFSET)
#define R_BUS_BUSERRCLRTDRW                 (R_BUS_BASE + R_BUS_BUSERRCLRTDRW_OFFSET)
#define R_BUS_BUSIRQENTDRW                 (R_BUS_BASE + R_BUS_BUSIRQENTDRW_OFFSET)
#define R_BUS_BUSERRSTATMIPI0                 (R_BUS_BASE + R_BUS_BUSERRSTATMIPI0_OFFSET)
#define R_BUS_BUSERRCLRMIPI0                 (R_BUS_BASE + R_BUS_BUSERRCLRMIPI0_OFFSET)
#define R_BUS_BUSIRQENMIPI0                 (R_BUS_BASE + R_BUS_BUSIRQENMIPI0_OFFSET)
#define R_BUS_BUSERRSTATMIPI1                 (R_BUS_BASE + R_BUS_BUSERRSTATMIPI1_OFFSET)
#define R_BUS_BUSERRCLRMIPI1                 (R_BUS_BASE + R_BUS_BUSERRCLRMIPI1_OFFSET)
#define R_BUS_BUSIRQENMIPI1                 (R_BUS_BASE + R_BUS_BUSIRQENMIPI1_OFFSET)
#define R_BUS_BUSERRSTATCEU                 (R_BUS_BASE + R_BUS_BUSERRSTATCEU_OFFSET)
#define R_BUS_BUSERRCLRCEU                 (R_BUS_BASE + R_BUS_BUSERRCLRCEU_OFFSET)
#define R_BUS_BUSIRQENCEU                 (R_BUS_BASE + R_BUS_BUSIRQENCEU_OFFSET)
#define R_BUS_MBWERRSTAT                 (R_BUS_BASE + R_BUS_MBWERRSTAT_OFFSET)
#define R_BUS_MBWERRCLR                 (R_BUS_BASE + R_BUS_MBWERRCLR_OFFSET)

/* Register bit definitions */
/* CSMOD Register bit definitions */
#define R_BUS_CSMOD_WRMOD                         (1 << 0)  /* Write Access Mode Select */

#define R_BUS_CSMOD_EWENB                         (1 << 3)  /* External Wait Enable */

#define R_BUS_CSMOD_PRENB                         (1 << 8)  /* Page Read Access Enable */

#define R_BUS_CSMOD_PWENB                         (1 << 9)  /* Page Write Access Enable */

#define R_BUS_CSMOD_PRMOD                         (1 << 15)  /* Page Read Access Mode Select */

/* CSWCR Register bit definitions */
#define R_BUS_CSWCR_CSPWWAIT_SHIFT                (0)  /* Page Write Cycle Wait Select */
#define R_BUS_CSWCR_CSPWWAIT_MASK                 0x7

#define R_BUS_CSWCR_CSPRWAIT_SHIFT                (8)  /* Page Read Cycle Wait Select */
#define R_BUS_CSWCR_CSPRWAIT_MASK                 0x700

#define R_BUS_CSWCR_CSWWAIT_SHIFT                 (16)  /* Normal Write Cycle Wait Select */
#define R_BUS_CSWCR_CSWWAIT_MASK                  0x1f0000

#define R_BUS_CSWCR_CSRWAIT_SHIFT                 (24)  /* Normal Read Cycle Wait Select */
#define R_BUS_CSWCR_CSRWAIT_MASK                  0x1f000000

/* CSWCR Register bit definitions */
#define R_BUS_CSWCR_CSROFF_SHIFT                  (0)  /* Read Access CS Extension Cycle Select */
#define R_BUS_CSWCR_CSROFF_MASK                   0x7

#define R_BUS_CSWCR_CSWOFF_SHIFT                  (4)  /* Write Access CS Extension Cycle Select */
#define R_BUS_CSWCR_CSWOFF_MASK                   0x70

#define R_BUS_CSWCR_WDOFF_SHIFT                   (8)  /* Write Data Output Extension Cycle Select */
#define R_BUS_CSWCR_WDOFF_MASK                    0x700

#define R_BUS_CSWCR_AWAIT_SHIFT                   (12)  /* Address Cycle Wait Select */
#define R_BUS_CSWCR_AWAIT_MASK                    0x3000

#define R_BUS_CSWCR_RDON_SHIFT                    (16)  /* RD Assert Wait Select */
#define R_BUS_CSWCR_RDON_MASK                     0x70000

#define R_BUS_CSWCR_WRON_SHIFT                    (20)  /* WR Assert Wait Select */
#define R_BUS_CSWCR_WRON_MASK                     0x700000

#define R_BUS_CSWCR_WDON_SHIFT                    (24)  /* Write Data Output Wait Select */
#define R_BUS_CSWCR_WDON_MASK                     0x7000000

#define R_BUS_CSWCR_CSON_SHIFT                    (28)  /* CS Assert Wait Select */
#define R_BUS_CSWCR_CSON_MASK                     0x70000000

/* CS0CR Register bit definitions */
#define R_BUS_CS0CR_EXENB                         (1 << 0)  /* Operation Enable */

#define R_BUS_CS0CR_BSIZE_SHIFT                   (4)  /* External Bus Width Select */
#define R_BUS_CS0CR_BSIZE_MASK                    0x30
#  define R_BUS_CS0CR_BSIZE_00                            (0 << R_BUS_CS0CR_BSIZE_SHIFT)  /* 16-bit bus space */
#  define R_BUS_CS0CR_BSIZE_01                            (1 << R_BUS_CS0CR_BSIZE_SHIFT)  /* 32-bit bus space */
#  define R_BUS_CS0CR_BSIZE_10                            (2 << R_BUS_CS0CR_BSIZE_SHIFT)  /* 8-bit bus space */

#define R_BUS_CS0CR_EMODE                         (1 << 8)  /* Endian Mode */

#define R_BUS_CS0CR_MPXEN                         (1 << 12)  /* Address/Data Multiplexed I/O Interface Select */

/* CSREC Register bit definitions */
#define R_BUS_CSREC_RRCV_SHIFT                    (0)  /* Read Recovery */
#define R_BUS_CSREC_RRCV_MASK                     0xf

#define R_BUS_CSREC_WRCV_SHIFT                    (8)  /* Write Recovery */
#define R_BUS_CSREC_WRCV_MASK                     0xf00

/* CSCR Register bit definitions */
#define R_BUS_CSCR_EXENB                          (1 << 0)  /* Operation Enable */

#define R_BUS_CSCR_BSIZE_SHIFT                    (4)  /* External Bus Width Select */
#define R_BUS_CSCR_BSIZE_MASK                     0x30
#  define R_BUS_CSCR_BSIZE_00                             (0 << R_BUS_CSCR_BSIZE_SHIFT)  /* 16-bit bus space */
#  define R_BUS_CSCR_BSIZE_01                             (1 << R_BUS_CSCR_BSIZE_SHIFT)  /* 32-bit bus space */
#  define R_BUS_CSCR_BSIZE_10                             (2 << R_BUS_CSCR_BSIZE_SHIFT)  /* 8-bit bus space */

#define R_BUS_CSCR_EMODE                          (1 << 8)  /* Endian Mode */

#define R_BUS_CSCR_MPXEN                          (1 << 12)  /* Address/Data Multiplexed I/O Interface Select */

/* CSRECEN Register bit definitions */
#define R_BUS_CSRECEN_RCVEN0                      (1 << 0)  /* Separate Bus Recovery Cycle Insertion Enable 0 */

#define R_BUS_CSRECEN_RCVEN1                      (1 << 1)  /* Separate Bus Recovery Cycle Insertion Enable 1 */

#define R_BUS_CSRECEN_RCVEN2                      (1 << 2)  /* Separate Bus Recovery Cycle Insertion Enable 2 */

#define R_BUS_CSRECEN_RCVEN3                      (1 << 3)  /* Separate Bus Recovery Cycle Insertion Enable 3 */

#define R_BUS_CSRECEN_RCVEN4                      (1 << 4)  /* Separate Bus Recovery Cycle Insertion Enable 4 */

#define R_BUS_CSRECEN_RCVEN5                      (1 << 5)  /* Separate Bus Recovery Cycle Insertion Enable 5 */

#define R_BUS_CSRECEN_RCVEN6                      (1 << 6)  /* Separate Bus Recovery Cycle Insertion Enable 6 */

#define R_BUS_CSRECEN_RCVEN7                      (1 << 7)  /* Separate Bus Recovery Cycle Insertion Enable 7 */

#define R_BUS_CSRECEN_RCVENM0                     (1 << 8)  /* Multiplexed Bus Recovery Cycle Insertion Enable 0 */

#define R_BUS_CSRECEN_RCVENM1                     (1 << 9)  /* Multiplexed Bus Recovery Cycle Insertion Enable 1 */

#define R_BUS_CSRECEN_RCVENM2                     (1 << 10)  /* Multiplexed Bus Recovery Cycle Insertion Enable 2 */

#define R_BUS_CSRECEN_RCVENM3                     (1 << 11)  /* Multiplexed Bus Recovery Cycle Insertion Enable 3 */

#define R_BUS_CSRECEN_RCVENM4                     (1 << 12)  /* Multiplexed Bus Recovery Cycle Insertion Enable 4 */

#define R_BUS_CSRECEN_RCVENM5                     (1 << 13)  /* Multiplexed Bus Recovery Cycle Insertion Enable 5 */

#define R_BUS_CSRECEN_RCVENM6                     (1 << 14)  /* Multiplexed Bus Recovery Cycle Insertion Enable 6 */

#define R_BUS_CSRECEN_RCVENM7                     (1 << 15)  /* Multiplexed Bus Recovery Cycle Insertion Enable 7 */

/* SDCCR Register bit definitions */
#define R_BUS_SDCCR_EXENB                         (1 << 0)  /* Operation Enable */

#define R_BUS_SDCCR_BSIZE_SHIFT                   (4)  /* SDRAM Bus Width Select */
#define R_BUS_SDCCR_BSIZE_MASK                    0x30
#  define R_BUS_SDCCR_BSIZE_00                            (0 << R_BUS_SDCCR_BSIZE_SHIFT)  /* 16-bit bus space */
#  define R_BUS_SDCCR_BSIZE_01                            (1 << R_BUS_SDCCR_BSIZE_SHIFT)  /* 32-bit bus space */
#  define R_BUS_SDCCR_BSIZE_10                            (2 << R_BUS_SDCCR_BSIZE_SHIFT)  /* 8-bit bus space */

/* SDCMOD Register bit definitions */
#define R_BUS_SDCMOD_EMODE                        (1 << 0)  /* Endian Mode */

/* SDAMOD Register bit definitions */
#define R_BUS_SDAMOD_BE                           (1 << 0)  /* Continuous Access Enable */

/* SDSELF Register bit definitions */
#define R_BUS_SDSELF_SFEN                         (1 << 0)  /* SDRAM Self-Refresh Enable */

/* SDRFCR Register bit definitions */
#define R_BUS_SDRFCR_RFC_SHIFT                    (0)  /* Auto-Refresh Request Interval Setting */
#define R_BUS_SDRFCR_RFC_MASK                     0xfff

#define R_BUS_SDRFCR_REFW_SHIFT                   (12)  /* Auto-Refresh Cycle/Self-Refresh Clearing Cycle Count Setting */
#define R_BUS_SDRFCR_REFW_MASK                    0xf000

/* SDRFEN Register bit definitions */
#define R_BUS_SDRFEN_RFEN                         (1 << 0)  /* Auto-Refresh Operation Enable */

/* SDICR Register bit definitions */
#define R_BUS_SDICR_INIRQ                         (1 << 0)  /* Initialization Sequence Start */

/* SDIR Register bit definitions */
#define R_BUS_SDIR_ARFI_SHIFT                     (0)  /* Initialization Auto-Refresh Interval */
#define R_BUS_SDIR_ARFI_MASK                      0xf

#define R_BUS_SDIR_ARFC_SHIFT                     (4)  /* Initialization Auto-Refresh Count */
#define R_BUS_SDIR_ARFC_MASK                      0xf0

#define R_BUS_SDIR_PRC_SHIFT                      (8)  /* Initialization Precharge Cycle Count */
#define R_BUS_SDIR_PRC_MASK                       0x700

/* SDADR Register bit definitions */
#define R_BUS_SDADR_MXC_SHIFT                     (0)  /* Address Multiplex Select */
#define R_BUS_SDADR_MXC_MASK                      0x3
#  define R_BUS_SDADR_MXC_00                              (0 << R_BUS_SDADR_MXC_SHIFT)  /* 8-bit shift */
#  define R_BUS_SDADR_MXC_01                              (1 << R_BUS_SDADR_MXC_SHIFT)  /* 9-bit shift */
#  define R_BUS_SDADR_MXC_10                              (2 << R_BUS_SDADR_MXC_SHIFT)  /* 10-bit shift */
#  define R_BUS_SDADR_MXC_11                              (3 << R_BUS_SDADR_MXC_SHIFT)  /* 11-bit shift */

/* SDTR Register bit definitions */
#define R_BUS_SDTR_CL_SHIFT                       (0)  /* SDRAMC Column Latency */
#define R_BUS_SDTR_CL_MASK                        0x7
#  define R_BUS_SDTR_CL_000                               (0 << R_BUS_SDTR_CL_SHIFT)  /* Setting prohibited */
#  define R_BUS_SDTR_CL_001                               (1 << R_BUS_SDTR_CL_SHIFT)  /* 1 cycle */
#  define R_BUS_SDTR_CL_010                               (2 << R_BUS_SDTR_CL_SHIFT)  /* 2 cycles */
#  define R_BUS_SDTR_CL_011                               (3 << R_BUS_SDTR_CL_SHIFT)  /* 3 cycles */

#define R_BUS_SDTR_WR                             (1 << 8)  /* Write Recovery Interval */

#define R_BUS_SDTR_RP_SHIFT                       (9)  /* Row Precharge Interval */
#define R_BUS_SDTR_RP_MASK                        0xe00
#  define R_BUS_SDTR_RP_000                               (0 << R_BUS_SDTR_RP_SHIFT)  /* 1 cycle */
#  define R_BUS_SDTR_RP_001                               (1 << R_BUS_SDTR_RP_SHIFT)  /* 2 cycles */
#  define R_BUS_SDTR_RP_010                               (2 << R_BUS_SDTR_RP_SHIFT)  /* 3 cycles */
#  define R_BUS_SDTR_RP_011                               (3 << R_BUS_SDTR_RP_SHIFT)  /* 4 cycles */
#  define R_BUS_SDTR_RP_100                               (4 << R_BUS_SDTR_RP_SHIFT)  /* 5 cycles */
#  define R_BUS_SDTR_RP_101                               (5 << R_BUS_SDTR_RP_SHIFT)  /* 6 cycles */
#  define R_BUS_SDTR_RP_110                               (6 << R_BUS_SDTR_RP_SHIFT)  /* 7 cycles */
#  define R_BUS_SDTR_RP_111                               (7 << R_BUS_SDTR_RP_SHIFT)  /* 8 cycles */

#define R_BUS_SDTR_RCD_SHIFT                      (12)  /* Row Column Latency */
#define R_BUS_SDTR_RCD_MASK                       0x3000
#  define R_BUS_SDTR_RCD_00                               (0 << R_BUS_SDTR_RCD_SHIFT)  /* 1 cycle */
#  define R_BUS_SDTR_RCD_01                               (1 << R_BUS_SDTR_RCD_SHIFT)  /* 2 cycles */
#  define R_BUS_SDTR_RCD_10                               (2 << R_BUS_SDTR_RCD_SHIFT)  /* 3 cycles */
#  define R_BUS_SDTR_RCD_11                               (3 << R_BUS_SDTR_RCD_SHIFT)  /* 4 cycles */

#define R_BUS_SDTR_RAI_SHIFT                      (16)  /* Row Active Interval */
#define R_BUS_SDTR_RAI_MASK                       0x70000
#  define R_BUS_SDTR_RAI_000                              (0 << R_BUS_SDTR_RAI_SHIFT)  /* 1 cycle */
#  define R_BUS_SDTR_RAI_001                              (1 << R_BUS_SDTR_RAI_SHIFT)  /* 2 cycles */
#  define R_BUS_SDTR_RAI_010                              (2 << R_BUS_SDTR_RAI_SHIFT)  /* 3 cycles */
#  define R_BUS_SDTR_RAI_011                              (3 << R_BUS_SDTR_RAI_SHIFT)  /* 4 cycles */
#  define R_BUS_SDTR_RAI_100                              (4 << R_BUS_SDTR_RAI_SHIFT)  /* 5 cycles */
#  define R_BUS_SDTR_RAI_101                              (5 << R_BUS_SDTR_RAI_SHIFT)  /* 6 cycles */
#  define R_BUS_SDTR_RAI_110                              (6 << R_BUS_SDTR_RAI_SHIFT)  /* 7 cycles */
#  define R_BUS_SDTR_RAI_111                              (7 << R_BUS_SDTR_RAI_SHIFT)  /* Setting prohibited */

/* SDMOD Register bit definitions */
#define R_BUS_SDMOD_MR_SHIFT                      (0)  /* Mode Register Setting */
#define R_BUS_SDMOD_MR_MASK                       0x7fff

/* SDSR Register bit definitions */
#define R_BUS_SDSR_MRSST                          (1 << 0)  /* Mode Register Setting Status */

#define R_BUS_SDSR_INIST                          (1 << 3)  /* Initialization Status */

#define R_BUS_SDSR_SRFST                          (1 << 4)  /* Self-Refresh Transition/Recovery Status */

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

/* BUSMABTGRAPHBI Register bit definitions */
#define R_BUS_BUSMABTGRAPHBI_ARBS                 (1 << 0)  /* Arbitration Select */

/* BUSSABT1MRC0BI Register bit definitions */
#define R_BUS_BUSSABT1MRC0BI_ARBS_SHIFT           (0)  /* Arbitration Select */
#define R_BUS_BUSSABT1MRC0BI_ARBS_MASK            0x3
#  define R_BUS_BUSSABT1MRC0BI_ARBS_00                    (0 << R_BUS_BUSSABT1MRC0BI_ARBS_SHIFT)  /* Fixed priority */
#  define R_BUS_BUSSABT1MRC0BI_ARBS_01                    (1 << R_BUS_BUSSABT1MRC0BI_ARBS_SHIFT)  /* Setting prohibited */
#  define R_BUS_BUSSABT1MRC0BI_ARBS_10                    (2 << R_BUS_BUSSABT1MRC0BI_ARBS_SHIFT)  /* Combination of round-robin and fixed priority */
#  define R_BUS_BUSSABT1MRC0BI_ARBS_11                    (3 << R_BUS_BUSSABT1MRC0BI_ARBS_SHIFT)  /* Round-robin */

/* BUSSABT0MRE0BI Register bit definitions */
#define R_BUS_BUSSABT0MRE0BI_ARBS                 (1 << 0)  /* Arbitration Select for <slave> */

/* BUSSABT0S0BI Register bit definitions */
#define R_BUS_BUSSABT0S0BI_ARBS                   (1 << 0)  /* Arbitration Select for <slave> */

/* BUSSABT0S1BI Register bit definitions */
#define R_BUS_BUSSABT0S1BI_ARBS                   (1 << 0)  /* Arbitration Select for <slave> */

/* BUSSABT0S2BI Register bit definitions */
#define R_BUS_BUSSABT0S2BI_ARBS                   (1 << 0)  /* Arbitration Select for <slave> */

/* BUSSABT0S3BI Register bit definitions */
#define R_BUS_BUSSABT0S3BI_ARBS                   (1 << 0)  /* Arbitration Select for <slave> */

/* BUSSABT0ECBI Register bit definitions */
#define R_BUS_BUSSABT0ECBI_ARBS                   (1 << 0)  /* Arbitration Select for <slave> */

/* BUSSABT0OSPI0BI Register bit definitions */
#define R_BUS_BUSSABT0OSPI0BI_ARBS                (1 << 0)  /* Arbitration Select for <slave> */

/* BUSSABT0OSPI1BI Register bit definitions */
#define R_BUS_BUSSABT0OSPI1BI_ARBS                (1 << 0)  /* Arbitration Select for <slave> */

/* BUSSABT0CPU0SAHBI Register bit definitions */
#define R_BUS_BUSSABT0CPU0SAHBI_ARBS              (1 << 0)  /* Arbitration Select for <slave> */

/* BUSSABT0CPU1TCMBI Register bit definitions */
#define R_BUS_BUSSABT0CPU1TCMBI_ARBS              (1 << 0)  /* Arbitration Select for <slave> */

/* BUSSABT0PBBI Register bit definitions */
#define R_BUS_BUSSABT0PBBI_ARBS                   (1 << 0)  /* Arbitration Select for <slave> */

/* BUSSABT0PABI Register bit definitions */
#define R_BUS_BUSSABT0PABI_ARBS                   (1 << 0)  /* Arbitration Select for <slave> */

/* BUSSABT0PIBI Register bit definitions */
#define R_BUS_BUSSABT0PIBI_ARBS                   (1 << 0)  /* Arbitration Select for <slave> */

/* BUSSABT0PSBI Register bit definitions */
#define R_BUS_BUSSABT0PSBI_ARBS                   (1 << 0)  /* Arbitration Select for <slave> */

/* BUSERRSTATCPU0 Register bit definitions */
#define R_BUS_BUSERRSTATCPU0_SLERRSTAT            (1 << 0)  /* Slave Bus Error Status */

#define R_BUS_BUSERRSTATCPU0_MMERRSTAT            (1 << 3)  /* Master MPU Error Status */

#define R_BUS_BUSERRSTATCPU0_ILERRSTAT            (1 << 4)  /* Illegal Address Access Error Status */

#define R_BUS_BUSERRSTATCPU0_MSERRSTAT            (1 << 5)  /* Master Security Attribution Unit Error Status */

/* BUSERRCLRCPU0 Register bit definitions */
#define R_BUS_BUSERRCLRCPU0_SLERRCLR              (1 << 0)  /* Slave Bus Error Clear */

#define R_BUS_BUSERRCLRCPU0_MMERRCLR              (1 << 3)  /* Master MPU Error Clear */

#define R_BUS_BUSERRCLRCPU0_ILERRCLR              (1 << 4)  /* Illegal Address Access Error Clear */

#define R_BUS_BUSERRCLRCPU0_MSERRCLR              (1 << 5)  /* Master Security Attribution Unit Error Clear */

/* BUSIRQENCPU0 Register bit definitions */
#define R_BUS_BUSIRQENCPU0_EN                     (1 << 0)  /* Interrupt enable after bus error detected */

/* BUSERRSTATCPU1 Register bit definitions */
#define R_BUS_BUSERRSTATCPU1_SLERRSTAT            (1 << 0)  /* Slave Bus Error Status */

#define R_BUS_BUSERRSTATCPU1_MMERRSTAT            (1 << 3)  /* Master MPU Error Status */

#define R_BUS_BUSERRSTATCPU1_ILERRSTAT            (1 << 4)  /* Illegal Address Access Error Status */

#define R_BUS_BUSERRSTATCPU1_MSERRSTAT            (1 << 5)  /* Master Security Attribution Unit Error Status */

/* BUSERRCLRCPU1 Register bit definitions */
#define R_BUS_BUSERRCLRCPU1_SLERRCLR              (1 << 0)  /* Slave Bus Error Clear */

#define R_BUS_BUSERRCLRCPU1_MMERRCLR              (1 << 3)  /* Master MPU Error Clear */

#define R_BUS_BUSERRCLRCPU1_ILERRCLR              (1 << 4)  /* Illegal Address Access Error Clear */

#define R_BUS_BUSERRCLRCPU1_MSERRCLR              (1 << 5)  /* Master Security Attribution Unit Error Clear */

/* BUSIRQENCPU1 Register bit definitions */
#define R_BUS_BUSIRQENCPU1_EN                     (1 << 0)  /* Interrupt enable after bus error detected */

/* BUSERRSTATDMAC0 Register bit definitions */
#define R_BUS_BUSERRSTATDMAC0_SLERRSTAT           (1 << 0)  /* Slave Bus Error Status */

#define R_BUS_BUSERRSTATDMAC0_MMERRSTAT           (1 << 3)  /* Master MPU Error Status */

#define R_BUS_BUSERRSTATDMAC0_ILERRSTAT           (1 << 4)  /* Illegal Address Access Error Status */

#define R_BUS_BUSERRSTATDMAC0_MSERRSTAT           (1 << 5)  /* Master Security Attribution Unit Error Status */

/* BUSERRCLRDMAC0 Register bit definitions */
#define R_BUS_BUSERRCLRDMAC0_SLERRCLR             (1 << 0)  /* Slave Bus Error Clear */

#define R_BUS_BUSERRCLRDMAC0_MMERRCLR             (1 << 3)  /* Master MPU Error Clear */

#define R_BUS_BUSERRCLRDMAC0_ILERRCLR             (1 << 4)  /* Illegal Address Access Error Clear */

#define R_BUS_BUSERRCLRDMAC0_MSERRCLR             (1 << 5)  /* Master Security Attribution Unit Error Clear */

/* BUSIRQENDMAC0 Register bit definitions */
#define R_BUS_BUSIRQENDMAC0_EN                    (1 << 0)  /* Interrupt enable after bus error detected */

/* BUSERRSTATDMAC1 Register bit definitions */
#define R_BUS_BUSERRSTATDMAC1_SLERRSTAT           (1 << 0)  /* Slave Bus Error Status */

#define R_BUS_BUSERRSTATDMAC1_MMERRSTAT           (1 << 3)  /* Master MPU Error Status */

#define R_BUS_BUSERRSTATDMAC1_ILERRSTAT           (1 << 4)  /* Illegal Address Access Error Status */

#define R_BUS_BUSERRSTATDMAC1_MSERRSTAT           (1 << 5)  /* Master Security Attribution Unit Error Status */

/* BUSERRCLRDMAC1 Register bit definitions */
#define R_BUS_BUSERRCLRDMAC1_SLERRCLR             (1 << 0)  /* Slave Bus Error Clear */

#define R_BUS_BUSERRCLRDMAC1_MMERRCLR             (1 << 3)  /* Master MPU Error Clear */

#define R_BUS_BUSERRCLRDMAC1_ILERRCLR             (1 << 4)  /* Illegal Address Access Error Clear */

#define R_BUS_BUSERRCLRDMAC1_MSERRCLR             (1 << 5)  /* Master Security Attribution Unit Error Clear */

/* BUSIRQENDMAC1 Register bit definitions */
#define R_BUS_BUSIRQENDMAC1_EN                    (1 << 0)  /* Interrupt enable after bus error detected */

/* BUSERRSTATNPU Register bit definitions */
#define R_BUS_BUSERRSTATNPU_SLERRSTAT             (1 << 0)  /* Slave Bus Error Status */

#define R_BUS_BUSERRSTATNPU_MMERRSTAT             (1 << 3)  /* Master MPU Error Status */

#define R_BUS_BUSERRSTATNPU_ILERRSTAT             (1 << 4)  /* Illegal Address Access Error Status */

#define R_BUS_BUSERRSTATNPU_MSERRSTAT             (1 << 5)  /* Master Security Attribution Unit Error Status */

/* BUSERRCLRNPU Register bit definitions */
#define R_BUS_BUSERRCLRNPU_SLERRCLR               (1 << 0)  /* Slave Bus Error Clear */

#define R_BUS_BUSERRCLRNPU_MMERRCLR               (1 << 3)  /* Master MPU Error Clear */

#define R_BUS_BUSERRCLRNPU_ILERRCLR               (1 << 4)  /* Illegal Address Access Error Clear */

#define R_BUS_BUSERRCLRNPU_MSERRCLR               (1 << 5)  /* Master Security Attribution Unit Error Clear */

/* BUSIRQENNPU Register bit definitions */
#define R_BUS_BUSIRQENNPU_EN                      (1 << 0)  /* Interrupt enable after bus error detected */

/* BUSERRSTATEDMAC Register bit definitions */
#define R_BUS_BUSERRSTATEDMAC_SLERRSTAT           (1 << 0)  /* Slave Bus Error Status */

#define R_BUS_BUSERRSTATEDMAC_MMERRSTAT           (1 << 3)  /* Master MPU Error Status */

#define R_BUS_BUSERRSTATEDMAC_ILERRSTAT           (1 << 4)  /* Illegal Address Access Error Status */

#define R_BUS_BUSERRSTATEDMAC_MSERRSTAT           (1 << 5)  /* Master Security Attribution Unit Error Status */

/* BUSERRCLREDMAC Register bit definitions */
#define R_BUS_BUSERRCLREDMAC_SLERRCLR             (1 << 0)  /* Slave Bus Error Clear */

#define R_BUS_BUSERRCLREDMAC_MMERRCLR             (1 << 3)  /* Master MPU Error Clear */

#define R_BUS_BUSERRCLREDMAC_ILERRCLR             (1 << 4)  /* Illegal Address Access Error Clear */

#define R_BUS_BUSERRCLREDMAC_MSERRCLR             (1 << 5)  /* Master Security Attribution Unit Error Clear */

/* BUSIRQENEDMAC Register bit definitions */
#define R_BUS_BUSIRQENEDMAC_EN                    (1 << 0)  /* Interrupt enable after bus error detected */

/* BUSERRSTATGLCDC Register bit definitions */
#define R_BUS_BUSERRSTATGLCDC_SLERRSTAT           (1 << 0)  /* Slave Bus Error Status */

#define R_BUS_BUSERRSTATGLCDC_MMERRSTAT           (1 << 3)  /* Master MPU Error Status */

#define R_BUS_BUSERRSTATGLCDC_ILERRSTAT           (1 << 4)  /* Illegal Address Access Error Status */

#define R_BUS_BUSERRSTATGLCDC_MSERRSTAT           (1 << 5)  /* Master Security Attribution Unit Error Status */

/* BUSERRCLRGLCDC Register bit definitions */
#define R_BUS_BUSERRCLRGLCDC_SLERRCLR             (1 << 0)  /* Slave Bus Error Clear */

#define R_BUS_BUSERRCLRGLCDC_MMERRCLR             (1 << 3)  /* Master MPU Error Clear */

#define R_BUS_BUSERRCLRGLCDC_ILERRCLR             (1 << 4)  /* Illegal Address Access Error Clear */

#define R_BUS_BUSERRCLRGLCDC_MSERRCLR             (1 << 5)  /* Master Security Attribution Unit Error Clear */

/* BUSIRQENGLCDC Register bit definitions */
#define R_BUS_BUSIRQENGLCDC_EN                    (1 << 0)  /* Interrupt enable after bus error detected */

/* BUSERRSTATTDRW Register bit definitions */
#define R_BUS_BUSERRSTATTDRW_SLERRSTAT            (1 << 0)  /* Slave Bus Error Status */

#define R_BUS_BUSERRSTATTDRW_MMERRSTAT            (1 << 3)  /* Master MPU Error Status */

#define R_BUS_BUSERRSTATTDRW_ILERRSTAT            (1 << 4)  /* Illegal Address Access Error Status */

#define R_BUS_BUSERRSTATTDRW_MSERRSTAT            (1 << 5)  /* Master Security Attribution Unit Error Status */

/* BUSERRCLRTDRW Register bit definitions */
#define R_BUS_BUSERRCLRTDRW_SLERRCLR              (1 << 0)  /* Slave Bus Error Clear */

#define R_BUS_BUSERRCLRTDRW_MMERRCLR              (1 << 3)  /* Master MPU Error Clear */

#define R_BUS_BUSERRCLRTDRW_ILERRCLR              (1 << 4)  /* Illegal Address Access Error Clear */

#define R_BUS_BUSERRCLRTDRW_MSERRCLR              (1 << 5)  /* Master Security Attribution Unit Error Clear */

/* BUSIRQENTDRW Register bit definitions */
#define R_BUS_BUSIRQENTDRW_EN                     (1 << 0)  /* Interrupt enable after bus error detected */

/* BUSERRSTATMIPI0 Register bit definitions */
#define R_BUS_BUSERRSTATMIPI0_SLERRSTAT           (1 << 0)  /* Slave Bus Error Status */

#define R_BUS_BUSERRSTATMIPI0_MMERRSTAT           (1 << 3)  /* Master MPU Error Status */

#define R_BUS_BUSERRSTATMIPI0_ILERRSTAT           (1 << 4)  /* Illegal Address Access Error Status */

#define R_BUS_BUSERRSTATMIPI0_MSERRSTAT           (1 << 5)  /* Master Security Attribution Unit Error Status */

/* BUSERRCLRMIPI0 Register bit definitions */
#define R_BUS_BUSERRCLRMIPI0_SLERRCLR             (1 << 0)  /* Slave Bus Error Clear */

#define R_BUS_BUSERRCLRMIPI0_MMERRCLR             (1 << 3)  /* Master MPU Error Clear */

#define R_BUS_BUSERRCLRMIPI0_ILERRCLR             (1 << 4)  /* Illegal Address Access Error Clear */

#define R_BUS_BUSERRCLRMIPI0_MSERRCLR             (1 << 5)  /* Master Security Attribution Unit Error Clear */

/* BUSIRQENMIPI0 Register bit definitions */
#define R_BUS_BUSIRQENMIPI0_EN                    (1 << 0)  /* Interrupt enable after bus error detected */

/* BUSERRSTATMIPI1 Register bit definitions */
#define R_BUS_BUSERRSTATMIPI1_SLERRSTAT           (1 << 0)  /* Slave Bus Error Status */

#define R_BUS_BUSERRSTATMIPI1_MMERRSTAT           (1 << 3)  /* Master MPU Error Status */

#define R_BUS_BUSERRSTATMIPI1_ILERRSTAT           (1 << 4)  /* Illegal Address Access Error Status */

#define R_BUS_BUSERRSTATMIPI1_MSERRSTAT           (1 << 5)  /* Master Security Attribution Unit Error Status */

/* BUSERRCLRMIPI1 Register bit definitions */
#define R_BUS_BUSERRCLRMIPI1_SLERRCLR             (1 << 0)  /* Slave Bus Error Clear */

#define R_BUS_BUSERRCLRMIPI1_MMERRCLR             (1 << 3)  /* Master MPU Error Clear */

#define R_BUS_BUSERRCLRMIPI1_ILERRCLR             (1 << 4)  /* Illegal Address Access Error Clear */

#define R_BUS_BUSERRCLRMIPI1_MSERRCLR             (1 << 5)  /* Master Security Attribution Unit Error Clear */

/* BUSIRQENMIPI1 Register bit definitions */
#define R_BUS_BUSIRQENMIPI1_EN                    (1 << 0)  /* Interrupt enable after bus error detected */

/* BUSERRSTATCEU Register bit definitions */
#define R_BUS_BUSERRSTATCEU_SLERRSTAT             (1 << 0)  /* Slave Bus Error Status */

#define R_BUS_BUSERRSTATCEU_MMERRSTAT             (1 << 3)  /* Master MPU Error Status */

#define R_BUS_BUSERRSTATCEU_ILERRSTAT             (1 << 4)  /* Illegal Address Access Error Status */

#define R_BUS_BUSERRSTATCEU_MSERRSTAT             (1 << 5)  /* Master Security Attribution Unit Error Status */

/* BUSERRCLRCEU Register bit definitions */
#define R_BUS_BUSERRCLRCEU_SLERRCLR               (1 << 0)  /* Slave Bus Error Clear */

#define R_BUS_BUSERRCLRCEU_MMERRCLR               (1 << 3)  /* Master MPU Error Clear */

#define R_BUS_BUSERRCLRCEU_ILERRCLR               (1 << 4)  /* Illegal Address Access Error Clear */

#define R_BUS_BUSERRCLRCEU_MSERRCLR               (1 << 5)  /* Master Security Attribution Unit Error Clear */

/* BUSIRQENCEU Register bit definitions */
#define R_BUS_BUSIRQENCEU_EN                      (1 << 0)  /* Interrupt enable after bus error detected */

/* MBWERRSTAT Register bit definitions */
#define R_BUS_MBWERRSTAT_MBWERR0                  (1 << 0)  /* Master Bufferable Write Error */

#define R_BUS_MBWERRSTAT_MBWERR1                  (1 << 1)  /* Master Bufferable Write Error */

#define R_BUS_MBWERRSTAT_MBWERR8                  (1 << 8)  /* Master Bufferable Write Error */

#define R_BUS_MBWERRSTAT_MBWERR9                  (1 << 9)  /* Master Bufferable Write Error */

#define R_BUS_MBWERRSTAT_MBWERR16                 (1 << 16)  /* Master Bufferable Write Error */

#define R_BUS_MBWERRSTAT_MBWERR17                 (1 << 17)  /* Master Bufferable Write Error */

#define R_BUS_MBWERRSTAT_MBWERR18                 (1 << 18)  /* Master Bufferable Write Error */

#define R_BUS_MBWERRSTAT_MBWERR19                 (1 << 19)  /* Master Bufferable Write Error */

#define R_BUS_MBWERRSTAT_MBWERR20                 (1 << 20)  /* Master Bufferable Write Error */

#define R_BUS_MBWERRSTAT_MBWERR21                 (1 << 21)  /* Master Bufferable Write Error */

/* MBWERRCLR Register bit definitions */
#define R_BUS_MBWERRCLR_MBWECLR0                  (1 << 0)  /* Master Bufferable Write Error Clear */

#define R_BUS_MBWERRCLR_MBWECLR1                  (1 << 1)  /* Master Bufferable Write Error Clear */

#define R_BUS_MBWERRCLR_MBWECLR8                  (1 << 8)  /* Master Bufferable Write Error Clear */

#define R_BUS_MBWERRCLR_MBWECLR9                  (1 << 9)  /* Master Bufferable Write Error Clear */

#define R_BUS_MBWERRCLR_MBWECLR16                 (1 << 16)  /* Master Bufferable Write Error Clear */

#define R_BUS_MBWERRCLR_MBWECLR17                 (1 << 17)  /* Master Bufferable Write Error Clear */

#define R_BUS_MBWERRCLR_MBWECLR18                 (1 << 18)  /* Master Bufferable Write Error Clear */

#define R_BUS_MBWERRCLR_MBWECLR19                 (1 << 19)  /* Master Bufferable Write Error Clear */

#define R_BUS_MBWERRCLR_MBWECLR20                 (1 << 20)  /* Master Bufferable Write Error Clear */

#define R_BUS_MBWERRCLR_MBWECLR21                 (1 << 21)  /* Master Bufferable Write Error Clear */


/* Maximum number of channels */

#define BUS_MAX_CHANNELS    8

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_BUS_H */
