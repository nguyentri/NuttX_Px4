/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1_memorymap.h
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

#ifndef __ARCH_ARM_SRC_RA_HARDWARE_RA8P1_MEMORYMAP_H
#define __ARCH_ARM_SRC_RA_HARDWARE_RA8P1_MEMORYMAP_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Registers Base Addresses - Updated based on R7FA8E1AF CMSIS header */

 #define R_ACMPHS0_BASE            0x40236000UL
 #define R_ACMPHS0_NS_BASE         0x50236000UL
 #define R_ACMPHS1_BASE            0x40236100UL
 #define R_ACMPHS1_NS_BASE         0x50236100UL
 #define R_ACMPHS2_BASE            0x40236200UL
 #define R_ACMPHS2_NS_BASE         0x50236200UL
 #define R_ACMPHS3_BASE            0x40236300UL
 #define R_ACMPHS3_NS_BASE         0x50236300UL
 #define R_ADC_B_BASE              0x40338000UL
 #define R_ADC_B_NS_BASE           0x50338000UL
 #define R_AGT0_BASE               0x40221000UL
 #define R_AGT0_NS_BASE            0x50221000UL
 #define R_AGT1_BASE               0x40221100UL
 #define R_AGT1_NS_BASE            0x50221100UL
 #define R_BUS_BASE                0x40003000UL
 #define R_BUS_NS_BASE             0x50003000UL
 #define R_CAC_BASE                0x40202400UL
 #define R_CACHE_BASE              0x4001C000UL
 #define R_CACHE_NS_BASE           0x5001C000UL
 #define R_CAC_NS_BASE             0x50202400UL
 #define R_CANFD0_BASE             0x40380000UL
 #define R_CANFD0_NS_BASE          0x50380000UL
 #define R_CANFD1_BASE             0x40382000UL
 #define R_CANFD1_NS_BASE          0x50380200UL
 #define R_CEU_BASE                0x40348000UL
 #define R_CEU_NS_BASE             0x50348000UL
 #define R_COMA_BASE               0x403C9000UL
 #define R_COMA_NS_BASE            0x503C9000UL
 #define R_CPSCU_BASE              0x40008000UL
 #define R_CPSCU_NS_BASE           0x50008000UL
 #define R_CPU_CTRL_BASE           0x4000F000UL
 #define R_CPU_CTRL_NS_BASE        0x5000F000UL
 #define R_CPU_DBG_BASE            0x4001B000UL
 #define R_CPU_OCD_BASE            0x40011000UL
 #define R_CRC_BASE                0x40310000UL
 #define R_CRC_NS_BASE             0x50310000UL
 #define R_DAC120_BASE             0x40233000UL
 #define R_DAC120_NS_BASE          0x50233000UL
 #define R_DAC121_BASE             0x40233100UL
 #define R_DAC121_NS_BASE          0x50233100UL
 #define R_DMA0_BASE               0x4000A800UL
 #define R_DMA0_NS_BASE            0x5000A800UL
 #define R_DMAC00_BASE             0x4000A000UL
 #define R_DMAC00_NS_BASE          0x5000A000UL
 #define R_DMAC01_BASE             0x4000A040UL
 #define R_DMAC01_NS_BASE          0x5000A040UL
 #define R_DMAC02_BASE             0x4000A080UL
 #define R_DMAC02_NS_BASE          0x5000A080UL
 #define R_DMAC03_BASE             0x4000A0C0UL
 #define R_DMAC03_NS_BASE          0x5000A0C0UL
 #define R_DMAC04_BASE             0x4000A100UL
 #define R_DMAC04_NS_BASE          0x5000A100UL
 #define R_DMAC05_BASE             0x4000A140UL
 #define R_DMAC05_NS_BASE          0x5000A140UL
 #define R_DMAC06_BASE             0x4000A180UL
 #define R_DMAC06_NS_BASE          0x5000A180UL
 #define R_DMAC07_BASE             0x4000A1C0UL
 #define R_DMAC07_NS_BASE          0x5000A1C0UL
 #define R_DOC_B_BASE              0x40311000UL
 #define R_DOC_B_NS_BASE           0x50311000UL
 #define R_DOTF0_BASE              0x40268800UL
 #define R_DOTF0_NS_BASE           0x50268800UL
 #define R_DOTF1_BASE              0x40268900UL
 #define R_DOTF1_NS_BASE           0x50268900UL
 #define R_DRW_BASE                0x40444000UL
 #define R_DRW_NS_BASE             0x50444000UL
 #define R_DTC0_BASE               0x4000AC00UL
 #define R_DTC0_NS_BASE            0x5000AC00UL
 #define R_ECCMB0_BASE             0x4036F200UL
 #define R_ECCMB0_NS_BASE          0x5036F200UL
 #define R_ECCMB1_BASE             0x4036F300UL
 #define R_ECCMB1_NS_BASE          0x5036F300UL
 #define R_ELC_BASE                0x40201000UL
 #define R_ELC_NS_BASE             0x50201000UL
 #define R_ESC_BASE                0x403A0000UL
 #define R_ESC_INI_BASE            0x403A4000UL
 #define R_ESC_INI_NS_BASE         0x503A4000UL
 #define R_ESC_NS_BASE             0x503A0000UL
 #define R_ESWM_BASE               0x403C8000UL
 #define R_ESWM_NS_BASE            0x503C8000UL
 #define R_ETHA0_NS_BASE           0x503CA000UL
 #define R_ETHA1_NS_BASE           0x503CC000UL
 #define R_FACI_BASE               0x4011E000UL
 #define R_FCACHE_BASE             0x4001C100UL
 #define R_FCACHE_NS_BASE          0x5001C100UL
 #define R_GLCDC_BASE              0x40342000UL
 #define R_GLCDC_NS_BASE           0x50342000UL
 #define R_GPT320_BASE             0x40322000UL
 #define R_GPT320_NS_BASE          0x50322000UL
 #define R_GPT321_BASE             0x40322100UL
 #define R_GPT3210_BASE            0x40322A00UL
 #define R_GPT3210_NS_BASE         0x50322A00UL
 #define R_GPT3211_BASE            0x40322B00UL
 #define R_GPT3211_NS_BASE         0x50322B00UL
 #define R_GPT3212_BASE            0x40322C00UL
 #define R_GPT3212_NS_BASE         0x50322C00UL
 #define R_GPT3213_BASE            0x40322D00UL
 #define R_GPT3213_NS_BASE         0x50322D00UL
 #define R_GPT321_NS_BASE          0x50322100UL
 #define R_GPT322_BASE             0x40322200UL
 #define R_GPT322_NS_BASE          0x50322200UL
 #define R_GPT323_BASE             0x40322300UL
 #define R_GPT323_NS_BASE          0x50322300UL
 #define R_GPT324_BASE             0x40322400UL
 #define R_GPT324_NS_BASE          0x50322400UL
 #define R_GPT325_BASE             0x40322500UL
 #define R_GPT325_NS_BASE          0x50322500UL
 #define R_GPT326_BASE             0x40322600UL
 #define R_GPT326_NS_BASE          0x50322600UL
 #define R_GPT327_BASE             0x40322700UL
 #define R_GPT327_NS_BASE          0x50322700UL
 #define R_GPT328_BASE             0x40322800UL
 #define R_GPT328_NS_BASE          0x50322800UL
 #define R_GPT329_BASE             0x40322900UL
 #define R_GPT329_NS_BASE          0x50322900UL
 #define R_GPTP_BASE               0x403E0000UL
 #define R_GPTP_NS_BASE            0x503E0000UL
 #define R_GPT_GTCLK_BASE          0x40323F10UL
 #define R_GPT_GTCLK_NS_BASE       0x50323F10UL
 #define R_GPT_OPS_BASE            0x40323F00UL
 #define R_GPT_OPS_NS_BASE         0x50323F00UL
 #define R_GWCA0_BASE              0x403CE000UL
 #define R_GWCA0_NS_BASE           0x503CE000UL
 #define R_I3C_BASE                0x4035F000UL
 #define R_I3C_NS_BASE             0x5035F000UL
 #define R_ICU_BASE                0x4000C000UL
 #define R_ICU_COMMON_BASE         0x40006000UL
 #define R_ICU_COMMON_NS_BASE      0x50006000UL
 #define R_ICU_NS_BASE             0x5000C000UL
 #define R_IIC0_BASE               0x4025E000UL
 #define R_IIC0WU_BASE             0x4025E014UL
 #define R_IIC0WU_NS_BASE          0x5025E014UL
 #define R_IIC0_NS_BASE            0x5025E000UL
 #define R_IIC1_BASE               0x4025E100UL
 #define R_IIC1_NS_BASE            0x5025E100UL
 #define R_IIC2_BASE               0x4025E200UL
 #define R_IIC2_NS_BASE            0x5025E200UL
 #define R_IPC_BASE                0x40020000UL
 #define R_IPC_NS_BASE             0x50020000UL
 #define R_IWDT_BASE               0x40202200UL
 #define R_IWDT_NS_BASE            0x50202200UL
 #define R_MFWD_BASE               0x403C0000UL
 #define R_MFWD_NS_BASE            0x503C0000UL
 #define R_MIPI_CSI0_BASE          0x40347000UL
 #define R_MIPI_CSI0_NS_BASE       0x50347000UL
 #define R_MIPI_DSI_BASE           0x40346000UL
 #define R_MIPI_DSI_NS_BASE        0x50346000UL
 #define R_MIPI_PHY0_BASE          0x40346C00UL
 #define R_MIPI_PHY0_NS_BASE       0x50346C00UL
 #define R_MRAM_BASE               0x4013C000UL
 #define R_MRAM_NS_BASE            0x5013C000UL
 #define R_MSTP_BASE               0x40203000UL
 #define R_MSTP_NS_BASE            0x50203000UL
 #define R_OSPI0_B_BASE            0x40268000UL
 #define R_OSPI0_B_NS_BASE         0x50268000UL
 #define R_OSPI1_B_BASE            0x40268400UL
 #define R_OSPI1_B_NS_BASE         0x50268400UL
 #define R_PDG_BASE                0x40324000UL
 #define R_PDG_NS_BASE             0x50324000UL
 #define R_PDMIF_BASE              0x40256000UL
 #define R_PDMIF_NS_BASE           0x50256000UL
 #define R_PFS_BASE                0x40400800UL
 #define R_PFS_NS_BASE             0x50400800UL
 #define R_POEG_BASE               0x40212000UL
 #define R_POEG_NS_BASE            0x50212000UL
 #define R_PORT0_BASE              0x40400000UL
 #define R_PORT0_NS_BASE           0x50400000UL
 #define R_PORT1_BASE              0x40400020UL
 #define R_PORT1_NS_BASE           0x50400020UL
 #define R_PORT2_BASE              0x40400040UL
 #define R_PORT2_NS_BASE           0x50400040UL
 #define R_PORT3_BASE              0x40400060UL
 #define R_PORT3_NS_BASE           0x50400060UL
 #define R_PORT4_BASE              0x40400080UL
 #define R_PORT4_NS_BASE           0x50400080UL
 #define R_PORT5_BASE              0x404000A0UL
 #define R_PORT5_NS_BASE           0x504000A0UL
 #define R_PORT6_BASE              0x404000C0UL
 #define R_PORT6_NS_BASE           0x504000C0UL
 #define R_PORT7_BASE              0x404000E0UL
 #define R_PORT7_NS_BASE           0x504000E0UL
 #define R_PORT8_BASE              0x40400100UL
 #define R_PORT8_NS_BASE           0x50400100UL
 #define R_PORT9_BASE              0x40400120UL
 #define R_PORT9_NS_BASE           0x50400120UL
 #define R_PORTA_BASE              0x40400140UL
 #define R_PORTA_NS_BASE           0x50400140UL
 #define R_PORTB_BASE              0x40400160UL
 #define R_PORTB_NS_BASE           0x50400160UL
 #define R_PORTC_BASE              0x40400180UL
 #define R_PORTC_NS_BASE           0x50400180UL
 #define R_PORTD_BASE              0x404001A0UL
 #define R_PORTD_NS_BASE           0x504001A0UL
 #define R_PSCU_BASE               0x40204000UL
 #define R_PSCU_NS_BASE            0x50204000UL
 #define R_RMAC0_BASE              0x403CB000UL
 #define R_RMAC0_NS_BASE           0x503CB000UL
 #define R_RMAC1_BASE              0x403CD000UL
 #define R_RMAC1_NS_BASE           0x503CD000UL
 #define R_RMPU_BASE               0x40000000UL
 #define R_RMPU_NS_BASE            0x50000000UL
 #define R_RTC_BASE                0x40202000UL
 #define R_RTC_NS_BASE             0x50202000UL
 #define R_SCI0_B_BASE             0x40358000UL
 #define R_SCI0_B_NS_BASE          0x50358000UL
 #define R_SCI1_B_BASE             0x40358100UL
 #define R_SCI1_B_NS_BASE          0x50358100UL
 #define R_SCI2_B_BASE             0x40358200UL
 #define R_SCI2_B_NS_BASE          0x50358200UL
 #define R_SCI3_B_BASE             0x40358300UL
 #define R_SCI3_B_NS_BASE          0x50358300UL
 #define R_SCI4_B_BASE             0x40358400UL
 #define R_SCI4_B_NS_BASE          0x50358400UL
 #define R_SCI5_B_BASE             0x40358500UL
 #define R_SCI5_B_NS_BASE          0x50358500UL
 #define R_SCI6_B_BASE             0x40358600UL
 #define R_SCI6_B_NS_BASE          0x50358600UL
 #define R_SCI7_B_BASE             0x40358700UL
 #define R_SCI7_B_NS_BASE          0x50358700UL
 #define R_SCI8_B_BASE             0x40358800UL
 #define R_SCI8_B_NS_BASE          0x50358800UL
 #define R_SCI9_B_BASE             0x40358900UL
 #define R_SCI9_B_NS_BASE          0x50358900UL
 #define R_SDHI0_BASE              0x40252000UL
 #define R_SDHI0_NS_BASE           0x50252000UL
 #define R_SDHI1_BASE              0x40252400UL
 #define R_SDHI1_NS_BASE           0x50252400UL
 #define R_SPI0_B_BASE             0x4035C000UL
 #define R_SPI0_B_NS_BASE          0x5035C000UL
 #define R_SPI1_B_BASE             0x4035C100UL
 #define R_SPI1_B_NS_BASE          0x5035C100UL
 #define R_SRAM_BASE               0x40002000UL
 #define R_SRAM_NS_BASE            0x50002000UL
 #define R_SSIE0_BASE              0x4025D000UL
 #define R_SSIE0_NS_BASE           0x5025D000UL
 #define R_SSIE1_BASE              0x4025D100UL
 #define R_SSIE1_NS_BASE           0x5025D100UL
 #define R_SYSC_BASE               0x4001E000UL
 #define R_SYSC_NS_BASE            0x5001E000UL
 #define R_TCM_BASE                0x4001C800UL
 #define R_TCM_NS_BASE             0x5001C800UL
 #define R_TSD_BASE                0x02C1EDA0UL
 #define R_TSD_NS_BASE             0x12C1EDA0UL
 #define R_TSN_BASE                0x40235000UL
 #define R_TSN_NS_BASE             0x50235000UL
 #define R_ULPT0_BASE              0x40220000UL
 #define R_ULPT0_NS_BASE           0x50220000UL
 #define R_ULPT1_BASE              0x40220100UL
 #define R_ULPT1_NS_BASE           0x50220100UL
 #define R_USBFS_BASE              0x40250000UL
 #define R_USBFS_NS_BASE           0x50250000UL
 #define R_USBHS_BASE              0x40351000UL
 #define R_USBHS_NS_BASE           0x50351000UL
 #define R_VIN0_BASE               0x40347400UL
 #define R_VIN0_NS_BASE            0x50347400UL
 #define R_WDT0_BASE               0x40202600UL
 #define R_WDT0_NS_BASE            0x50202600UL
 #define R_WDT1_BASE               0x40202700UL
 #define R_WDT1_NS_BASE            0x50202700UL

/****************************************************************************
 * Public Types
 ****************************************************************************/

#ifndef __ASSEMBLY__

/****************************************************************************
 * Public Data
 ****************************************************************************/

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */

#endif /* __ARCH_ARM_SRC_RA_HARDWARE_RA8P1_MEMORYMAP_H */