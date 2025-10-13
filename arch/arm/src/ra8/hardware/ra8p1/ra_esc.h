/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_esc.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ESC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ESC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ESC Base Address */
#ifndef R_ESC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_ESC_BASE           0x403a0000
#else
#define R_ESC_BASE           0x503a0000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_ESC_CH_STRIDE    0x00000002
#define R_ESC_CH_BASE(ch)   (R_ESC_BASE + ((uint32_t)(ch) * R_ESC_CH_STRIDE))

/* ESC Register Offsets */

#define R_ESC_TYPE_OFFSET     0x00000000  /* Type Register */
#define R_ESC_REVISION_OFFSET     0x00000001  /* Revision Register */
#define R_ESC_BUILD_OFFSET     0x00000002  /* Build Register */
#define R_ESC_FMMU_NUM_OFFSET     0x00000004  /* FMMU Supported Register */
#define R_ESC_SYNC_MANAGER_OFFSET     0x00000005  /* SyncManager Supported Register */
#define R_ESC_RAM_SIZE_OFFSET     0x00000006  /* RAM Size Register */
#define R_ESC_PORT_DESC_OFFSET     0x00000007  /* Port Descriptor Register */
#define R_ESC_FEATURE_OFFSET     0x00000008  /* ESC Features Supported Register */
#define R_ESC_STATION_ADR_OFFSET     0x00000010  /* Configured Station Address Register */
#define R_ESC_STATION_ALIAS_OFFSET     0x00000012  /* Configured Station Alias Register */
#define R_ESC_WR_REG_ENABLE_OFFSET     0x00000020  /* Write Register Enable Register */
#define R_ESC_WR_REG_PROTECT_OFFSET     0x00000021  /* Write Register Protection Register */
#define R_ESC_ESC_WR_ENABLE_OFFSET     0x00000030  /* ESC Write Enable Register */
#define R_ESC_ESC_WR_PROTECT_OFFSET     0x00000031  /* ESC Write Protection Register */
#define R_ESC_ESC_RESET_ECAT_R_OFFSET     0x00000040  /* ESC Reset ECAT Register for read */
#define R_ESC_ESC_RESET_ECAT_W_OFFSET     0x00000040  /* ESC Reset ECAT Register for write */
#define R_ESC_ESC_RESET_PDI_R_OFFSET     0x00000041  /* ESC Reset PDI Register for read */
#define R_ESC_ESC_RESET_PDI_W_OFFSET     0x00000041  /* ESC Reset PDI Register for write */
#define R_ESC_ESC_DL_CONTROL_OFFSET     0x00000100  /* ESC DL Control Register */
#define R_ESC_PHYSICAL_RW_OFFSET_OFFSET     0x00000108  /* Physical Read/Write Offset Register */
#define R_ESC_ESC_DL_STATUS_OFFSET     0x00000110  /* ESC DL Status Register */
#define R_ESC_AL_CONTROL_OFFSET     0x00000120  /* AL Control Register */
#define R_ESC_AL_STATUS_OFFSET     0x00000130  /* AL Status Register */
#define R_ESC_AL_STATUS_CODE_OFFSET     0x00000134  /* AL Status Code Register */
#define R_ESC_RUN_LED_OVERRIDE_OFFSET     0x00000138  /* RUN LED Override Register */
#define R_ESC_ERR_LED_OVERRIDE_OFFSET     0x00000139  /* ERR LED Override Register */
#define R_ESC_PDI_CONTROL_OFFSET     0x00000140  /* PDI Control Register */
#define R_ESC_ESC_CONFIG_OFFSET     0x00000141  /* ESC Configuration Register */
#define R_ESC_PDI_CONFIG_OFFSET     0x00000150  /* PDI Configuration Register */
#define R_ESC_SYNC_LATCH_CONFIG_OFFSET     0x00000151  /* SYNC/LATCH PDI Configuration Register */
#define R_ESC_EXT_PDI_CONFIG_OFFSET     0x00000152  /* Extended PDI Configuration Register */
#define R_ESC_ECAT_EVENT_MASK_OFFSET     0x00000200  /* ECAT Event Mask Register */
#define R_ESC_AL_EVENT_MASK_OFFSET     0x00000204  /* AL Event Mask Register */
#define R_ESC_ECAT_EVENT_REQ_OFFSET     0x00000210  /* ECAT Event Request Register */
#define R_ESC_AL_EVENT_REQ_OFFSET     0x00000220  /* AL Event Request Register */
/* RX_ERR_COUNT%s Registers (0-1) */
#define R_ESC_RX_ERR_COUNT0_OFFSET     0x00000300  /* RX Error Counter 0 Register (n = 0 to 1) */
#define R_ESC_RX_ERR_COUNT1_OFFSET     0x00000302  /* RX Error Counter 1 Register (n = 0 to 1) */
/* FWD_RX_ERR_COUNT%s Registers (0-1) */
#define R_ESC_FWD_RX_ERR_COUNT0_OFFSET     0x00000308  /* Forwarded RX Error Counter 0 Register (n = 0 to 1) */
#define R_ESC_FWD_RX_ERR_COUNT1_OFFSET     0x00000309  /* Forwarded RX Error Counter 1 Register (n = 0 to 1) */
#define R_ESC_ECAT_PROC_ERR_COUNT_OFFSET     0x0000030c  /* ECAT Processing Unit Error Counter Register */
#define R_ESC_PDI_ERR_COUNT_OFFSET     0x0000030d  /* PDI Error Counter Register */
/* LOST_LINK_COUNT%s Registers (0-1) */
#define R_ESC_LOST_LINK_COUNT0_OFFSET     0x00000310  /* Lost Link Counter 0 Register (n = 0 to 1) */
#define R_ESC_LOST_LINK_COUNT1_OFFSET     0x00000311  /* Lost Link Counter 1 Register (n = 0 to 1) */
#define R_ESC_WD_DIVIDE_OFFSET     0x00000400  /* Watchdog Divider Register */
#define R_ESC_WDT_PDI_OFFSET     0x00000410  /* Watchdog Time PDI Register */
#define R_ESC_WDT_DATA_OFFSET     0x00000420  /* Watchdog Time Process Data Register */
#define R_ESC_WDS_DATA_OFFSET     0x00000440  /* Watchdog Status Process Data Register */
#define R_ESC_WDC_DATA_OFFSET     0x00000442  /* Watchdog Counter Process Data Register */
#define R_ESC_WDC_PDI_OFFSET     0x00000443  /* Watchdog Counter PDI Register */
#define R_ESC_EEP_CONF_OFFSET     0x00000500  /* EEPROM Configuration Register */
#define R_ESC_EEP_STATE_OFFSET     0x00000501  /* EEPROM PDI Access State Register */
#define R_ESC_EEP_CONT_STAT_OFFSET     0x00000502  /* EEPROM Control/Status Register */
#define R_ESC_EEP_ADR_OFFSET     0x00000504  /* EEPROM Address Register */
#define R_ESC_EEP_DATA_OFFSET     0x00000508  /* EEPROM Data Register */
#define R_ESC_MII_CONT_STAT_OFFSET     0x00000510  /* MII Management Control/Status Register */
#define R_ESC_PHY_ADR_OFFSET     0x00000512  /* PHY Address Register */
#define R_ESC_PHY_REG_ADR_OFFSET     0x00000513  /* PHY Register Address Register */
#define R_ESC_PHY_DATA_OFFSET     0x00000514  /* PHY Data Register */
#define R_ESC_MII_ECAT_ACS_STAT_OFFSET     0x00000516  /* MII Management ECAT Access State Register */
#define R_ESC_MII_PDI_ACS_STAT_OFFSET     0x00000517  /* MII Management PDI Access State Register */
/* FMMU%s_L_START_ADR Registers (0-7) */
#define R_ESC_FMMU0_L_START_ADR_OFFSET     0x00000600  /* FMMU Logical Start Address 0 Register (n = 0 to 7) */
#define R_ESC_FMMU1_L_START_ADR_OFFSET     0x00000610  /* FMMU Logical Start Address 1 Register (n = 0 to 7) */
#define R_ESC_FMMU2_L_START_ADR_OFFSET     0x00000620  /* FMMU Logical Start Address 2 Register (n = 0 to 7) */
#define R_ESC_FMMU3_L_START_ADR_OFFSET     0x00000630  /* FMMU Logical Start Address 3 Register (n = 0 to 7) */
#define R_ESC_FMMU4_L_START_ADR_OFFSET     0x00000640  /* FMMU Logical Start Address 4 Register (n = 0 to 7) */
#define R_ESC_FMMU5_L_START_ADR_OFFSET     0x00000650  /* FMMU Logical Start Address 5 Register (n = 0 to 7) */
#define R_ESC_FMMU6_L_START_ADR_OFFSET     0x00000660  /* FMMU Logical Start Address 6 Register (n = 0 to 7) */
#define R_ESC_FMMU7_L_START_ADR_OFFSET     0x00000670  /* FMMU Logical Start Address 7 Register (n = 0 to 7) */
/* FMMU%s_LEN Registers (0-7) */
#define R_ESC_FMMU0_LEN_OFFSET     0x00000604  /* FMMU Length 0 Register (n = 0 to 7) */
#define R_ESC_FMMU1_LEN_OFFSET     0x00000614  /* FMMU Length 1 Register (n = 0 to 7) */
#define R_ESC_FMMU2_LEN_OFFSET     0x00000624  /* FMMU Length 2 Register (n = 0 to 7) */
#define R_ESC_FMMU3_LEN_OFFSET     0x00000634  /* FMMU Length 3 Register (n = 0 to 7) */
#define R_ESC_FMMU4_LEN_OFFSET     0x00000644  /* FMMU Length 4 Register (n = 0 to 7) */
#define R_ESC_FMMU5_LEN_OFFSET     0x00000654  /* FMMU Length 5 Register (n = 0 to 7) */
#define R_ESC_FMMU6_LEN_OFFSET     0x00000664  /* FMMU Length 6 Register (n = 0 to 7) */
#define R_ESC_FMMU7_LEN_OFFSET     0x00000674  /* FMMU Length 7 Register (n = 0 to 7) */
/* FMMU%s_L_START_BIT Registers (0-7) */
#define R_ESC_FMMU0_L_START_BIT_OFFSET     0x00000606  /* FMMU Logical Start Bit 0 Register (n = 0 to 7) */
#define R_ESC_FMMU1_L_START_BIT_OFFSET     0x00000616  /* FMMU Logical Start Bit 1 Register (n = 0 to 7) */
#define R_ESC_FMMU2_L_START_BIT_OFFSET     0x00000626  /* FMMU Logical Start Bit 2 Register (n = 0 to 7) */
#define R_ESC_FMMU3_L_START_BIT_OFFSET     0x00000636  /* FMMU Logical Start Bit 3 Register (n = 0 to 7) */
#define R_ESC_FMMU4_L_START_BIT_OFFSET     0x00000646  /* FMMU Logical Start Bit 4 Register (n = 0 to 7) */
#define R_ESC_FMMU5_L_START_BIT_OFFSET     0x00000656  /* FMMU Logical Start Bit 5 Register (n = 0 to 7) */
#define R_ESC_FMMU6_L_START_BIT_OFFSET     0x00000666  /* FMMU Logical Start Bit 6 Register (n = 0 to 7) */
#define R_ESC_FMMU7_L_START_BIT_OFFSET     0x00000676  /* FMMU Logical Start Bit 7 Register (n = 0 to 7) */
/* FMMU%s_L_STOP_BIT Registers (0-7) */
#define R_ESC_FMMU0_L_STOP_BIT_OFFSET     0x00000607  /* FMMU Logical Stop Bit 0 Register (n = 0 to 7) */
#define R_ESC_FMMU1_L_STOP_BIT_OFFSET     0x00000617  /* FMMU Logical Stop Bit 1 Register (n = 0 to 7) */
#define R_ESC_FMMU2_L_STOP_BIT_OFFSET     0x00000627  /* FMMU Logical Stop Bit 2 Register (n = 0 to 7) */
#define R_ESC_FMMU3_L_STOP_BIT_OFFSET     0x00000637  /* FMMU Logical Stop Bit 3 Register (n = 0 to 7) */
#define R_ESC_FMMU4_L_STOP_BIT_OFFSET     0x00000647  /* FMMU Logical Stop Bit 4 Register (n = 0 to 7) */
#define R_ESC_FMMU5_L_STOP_BIT_OFFSET     0x00000657  /* FMMU Logical Stop Bit 5 Register (n = 0 to 7) */
#define R_ESC_FMMU6_L_STOP_BIT_OFFSET     0x00000667  /* FMMU Logical Stop Bit 6 Register (n = 0 to 7) */
#define R_ESC_FMMU7_L_STOP_BIT_OFFSET     0x00000677  /* FMMU Logical Stop Bit 7 Register (n = 0 to 7) */
/* FMMU%s_P_START_ADR Registers (0-7) */
#define R_ESC_FMMU0_P_START_ADR_OFFSET     0x00000608  /* FMMU Physical Start Address 0 Register (n = 0 to 7) */
#define R_ESC_FMMU1_P_START_ADR_OFFSET     0x00000618  /* FMMU Physical Start Address 1 Register (n = 0 to 7) */
#define R_ESC_FMMU2_P_START_ADR_OFFSET     0x00000628  /* FMMU Physical Start Address 2 Register (n = 0 to 7) */
#define R_ESC_FMMU3_P_START_ADR_OFFSET     0x00000638  /* FMMU Physical Start Address 3 Register (n = 0 to 7) */
#define R_ESC_FMMU4_P_START_ADR_OFFSET     0x00000648  /* FMMU Physical Start Address 4 Register (n = 0 to 7) */
#define R_ESC_FMMU5_P_START_ADR_OFFSET     0x00000658  /* FMMU Physical Start Address 5 Register (n = 0 to 7) */
#define R_ESC_FMMU6_P_START_ADR_OFFSET     0x00000668  /* FMMU Physical Start Address 6 Register (n = 0 to 7) */
#define R_ESC_FMMU7_P_START_ADR_OFFSET     0x00000678  /* FMMU Physical Start Address 7 Register (n = 0 to 7) */
/* FMMU%s_P_START_BIT Registers (0-7) */
#define R_ESC_FMMU0_P_START_BIT_OFFSET     0x0000060a  /* FMMU Physical Start Bit 0 Register (n = 0 to 7) */
#define R_ESC_FMMU1_P_START_BIT_OFFSET     0x0000061a  /* FMMU Physical Start Bit 1 Register (n = 0 to 7) */
#define R_ESC_FMMU2_P_START_BIT_OFFSET     0x0000062a  /* FMMU Physical Start Bit 2 Register (n = 0 to 7) */
#define R_ESC_FMMU3_P_START_BIT_OFFSET     0x0000063a  /* FMMU Physical Start Bit 3 Register (n = 0 to 7) */
#define R_ESC_FMMU4_P_START_BIT_OFFSET     0x0000064a  /* FMMU Physical Start Bit 4 Register (n = 0 to 7) */
#define R_ESC_FMMU5_P_START_BIT_OFFSET     0x0000065a  /* FMMU Physical Start Bit 5 Register (n = 0 to 7) */
#define R_ESC_FMMU6_P_START_BIT_OFFSET     0x0000066a  /* FMMU Physical Start Bit 6 Register (n = 0 to 7) */
#define R_ESC_FMMU7_P_START_BIT_OFFSET     0x0000067a  /* FMMU Physical Start Bit 7 Register (n = 0 to 7) */
/* FMMU%s_TYPE Registers (0-7) */
#define R_ESC_FMMU0_TYPE_OFFSET     0x0000060b  /* FMMU Type 0 Register (n = 0 to 7) */
#define R_ESC_FMMU1_TYPE_OFFSET     0x0000061b  /* FMMU Type 1 Register (n = 0 to 7) */
#define R_ESC_FMMU2_TYPE_OFFSET     0x0000062b  /* FMMU Type 2 Register (n = 0 to 7) */
#define R_ESC_FMMU3_TYPE_OFFSET     0x0000063b  /* FMMU Type 3 Register (n = 0 to 7) */
#define R_ESC_FMMU4_TYPE_OFFSET     0x0000064b  /* FMMU Type 4 Register (n = 0 to 7) */
#define R_ESC_FMMU5_TYPE_OFFSET     0x0000065b  /* FMMU Type 5 Register (n = 0 to 7) */
#define R_ESC_FMMU6_TYPE_OFFSET     0x0000066b  /* FMMU Type 6 Register (n = 0 to 7) */
#define R_ESC_FMMU7_TYPE_OFFSET     0x0000067b  /* FMMU Type 7 Register (n = 0 to 7) */
/* FMMU%s_ACT Registers (0-7) */
#define R_ESC_FMMU0_ACT_OFFSET     0x0000060c  /* FMMU Activate 0 Register (n = 0 to 7) */
#define R_ESC_FMMU1_ACT_OFFSET     0x0000061c  /* FMMU Activate 1 Register (n = 0 to 7) */
#define R_ESC_FMMU2_ACT_OFFSET     0x0000062c  /* FMMU Activate 2 Register (n = 0 to 7) */
#define R_ESC_FMMU3_ACT_OFFSET     0x0000063c  /* FMMU Activate 3 Register (n = 0 to 7) */
#define R_ESC_FMMU4_ACT_OFFSET     0x0000064c  /* FMMU Activate 4 Register (n = 0 to 7) */
#define R_ESC_FMMU5_ACT_OFFSET     0x0000065c  /* FMMU Activate 5 Register (n = 0 to 7) */
#define R_ESC_FMMU6_ACT_OFFSET     0x0000066c  /* FMMU Activate 6 Register (n = 0 to 7) */
#define R_ESC_FMMU7_ACT_OFFSET     0x0000067c  /* FMMU Activate 7 Register (n = 0 to 7) */
/* SM%s_P_START_ADR Registers (0-7) */
#define R_ESC_SM0_P_START_ADR_OFFSET     0x00000800  /* SyncManager Physical Start Address 0 Register (n = 0 to 7) */
#define R_ESC_SM1_P_START_ADR_OFFSET     0x00000808  /* SyncManager Physical Start Address 1 Register (n = 0 to 7) */
#define R_ESC_SM2_P_START_ADR_OFFSET     0x00000810  /* SyncManager Physical Start Address 2 Register (n = 0 to 7) */
#define R_ESC_SM3_P_START_ADR_OFFSET     0x00000818  /* SyncManager Physical Start Address 3 Register (n = 0 to 7) */
#define R_ESC_SM4_P_START_ADR_OFFSET     0x00000820  /* SyncManager Physical Start Address 4 Register (n = 0 to 7) */
#define R_ESC_SM5_P_START_ADR_OFFSET     0x00000828  /* SyncManager Physical Start Address 5 Register (n = 0 to 7) */
#define R_ESC_SM6_P_START_ADR_OFFSET     0x00000830  /* SyncManager Physical Start Address 6 Register (n = 0 to 7) */
#define R_ESC_SM7_P_START_ADR_OFFSET     0x00000838  /* SyncManager Physical Start Address 7 Register (n = 0 to 7) */
/* SM%s_LEN Registers (0-7) */
#define R_ESC_SM0_LEN_OFFSET     0x00000802  /* SyncManager Length 0 Register (n = 0 to 7) */
#define R_ESC_SM1_LEN_OFFSET     0x0000080a  /* SyncManager Length 1 Register (n = 0 to 7) */
#define R_ESC_SM2_LEN_OFFSET     0x00000812  /* SyncManager Length 2 Register (n = 0 to 7) */
#define R_ESC_SM3_LEN_OFFSET     0x0000081a  /* SyncManager Length 3 Register (n = 0 to 7) */
#define R_ESC_SM4_LEN_OFFSET     0x00000822  /* SyncManager Length 4 Register (n = 0 to 7) */
#define R_ESC_SM5_LEN_OFFSET     0x0000082a  /* SyncManager Length 5 Register (n = 0 to 7) */
#define R_ESC_SM6_LEN_OFFSET     0x00000832  /* SyncManager Length 6 Register (n = 0 to 7) */
#define R_ESC_SM7_LEN_OFFSET     0x0000083a  /* SyncManager Length 7 Register (n = 0 to 7) */
/* SM%s_CONTROL Registers (0-7) */
#define R_ESC_SM0_CONTROL_OFFSET     0x00000804  /* SyncManager Control 0 Register (n = 0 to 7) */
#define R_ESC_SM1_CONTROL_OFFSET     0x0000080c  /* SyncManager Control 1 Register (n = 0 to 7) */
#define R_ESC_SM2_CONTROL_OFFSET     0x00000814  /* SyncManager Control 2 Register (n = 0 to 7) */
#define R_ESC_SM3_CONTROL_OFFSET     0x0000081c  /* SyncManager Control 3 Register (n = 0 to 7) */
#define R_ESC_SM4_CONTROL_OFFSET     0x00000824  /* SyncManager Control 4 Register (n = 0 to 7) */
#define R_ESC_SM5_CONTROL_OFFSET     0x0000082c  /* SyncManager Control 5 Register (n = 0 to 7) */
#define R_ESC_SM6_CONTROL_OFFSET     0x00000834  /* SyncManager Control 6 Register (n = 0 to 7) */
#define R_ESC_SM7_CONTROL_OFFSET     0x0000083c  /* SyncManager Control 7 Register (n = 0 to 7) */
/* SM%s_STATUS Registers (0-7) */
#define R_ESC_SM0_STATUS_OFFSET     0x00000805  /* SyncManager Status 0 Register (n = 0 to 7) */
#define R_ESC_SM1_STATUS_OFFSET     0x0000080d  /* SyncManager Status 1 Register (n = 0 to 7) */
#define R_ESC_SM2_STATUS_OFFSET     0x00000815  /* SyncManager Status 2 Register (n = 0 to 7) */
#define R_ESC_SM3_STATUS_OFFSET     0x0000081d  /* SyncManager Status 3 Register (n = 0 to 7) */
#define R_ESC_SM4_STATUS_OFFSET     0x00000825  /* SyncManager Status 4 Register (n = 0 to 7) */
#define R_ESC_SM5_STATUS_OFFSET     0x0000082d  /* SyncManager Status 5 Register (n = 0 to 7) */
#define R_ESC_SM6_STATUS_OFFSET     0x00000835  /* SyncManager Status 6 Register (n = 0 to 7) */
#define R_ESC_SM7_STATUS_OFFSET     0x0000083d  /* SyncManager Status 7 Register (n = 0 to 7) */
/* SM%s_ACT Registers (0-7) */
#define R_ESC_SM0_ACT_OFFSET     0x00000806  /* SyncManager Activate 0 Register (n = 0 to 7) */
#define R_ESC_SM1_ACT_OFFSET     0x0000080e  /* SyncManager Activate 1 Register (n = 0 to 7) */
#define R_ESC_SM2_ACT_OFFSET     0x00000816  /* SyncManager Activate 2 Register (n = 0 to 7) */
#define R_ESC_SM3_ACT_OFFSET     0x0000081e  /* SyncManager Activate 3 Register (n = 0 to 7) */
#define R_ESC_SM4_ACT_OFFSET     0x00000826  /* SyncManager Activate 4 Register (n = 0 to 7) */
#define R_ESC_SM5_ACT_OFFSET     0x0000082e  /* SyncManager Activate 5 Register (n = 0 to 7) */
#define R_ESC_SM6_ACT_OFFSET     0x00000836  /* SyncManager Activate 6 Register (n = 0 to 7) */
#define R_ESC_SM7_ACT_OFFSET     0x0000083e  /* SyncManager Activate 7 Register (n = 0 to 7) */
/* SM%s_PDI_CONT Registers (0-7) */
#define R_ESC_SM0_PDI_CONT_OFFSET     0x00000807  /* SyncManager PDI Control 0 Register (n = 0 to 7) */
#define R_ESC_SM1_PDI_CONT_OFFSET     0x0000080f  /* SyncManager PDI Control 1 Register (n = 0 to 7) */
#define R_ESC_SM2_PDI_CONT_OFFSET     0x00000817  /* SyncManager PDI Control 2 Register (n = 0 to 7) */
#define R_ESC_SM3_PDI_CONT_OFFSET     0x0000081f  /* SyncManager PDI Control 3 Register (n = 0 to 7) */
#define R_ESC_SM4_PDI_CONT_OFFSET     0x00000827  /* SyncManager PDI Control 4 Register (n = 0 to 7) */
#define R_ESC_SM5_PDI_CONT_OFFSET     0x0000082f  /* SyncManager PDI Control 5 Register (n = 0 to 7) */
#define R_ESC_SM6_PDI_CONT_OFFSET     0x00000837  /* SyncManager PDI Control 6 Register (n = 0 to 7) */
#define R_ESC_SM7_PDI_CONT_OFFSET     0x0000083f  /* SyncManager PDI Control 7 Register (n = 0 to 7) */
#define R_ESC_DC_RCV_TIME_PORT0_OFFSET     0x00000900  /* Receive Time Port 0 Register */
#define R_ESC_DC_RCV_TIME_PORT1_OFFSET     0x00000904  /* Receive Time Port 1 Register */
#define R_ESC_DC_RCV_TIME_PORT2_OFFSET     0x00000908  /* Receive Time Port 2 Register */
#define R_ESC_DC_SYS_TIME_L_OFFSET     0x00000910  /* System Time Register L */
#define R_ESC_DC_SYS_TIME_H_OFFSET     0x00000914  /* System Time Register H */
#define R_ESC_DC_RCV_TIME_UNIT_L_OFFSET     0x00000918  /* Receive Time ECAT Processing Unit Register L */
#define R_ESC_DC_RCV_TIME_UNIT_H_OFFSET     0x0000091c  /* Receive Time ECAT Processing Unit Register H */
#define R_ESC_DC_SYS_TIME_OFFSET_L_OFFSET     0x00000920  /* System Time Offset Register L */
#define R_ESC_DC_SYS_TIME_OFFSET_H_OFFSET     0x00000924  /* System Time Offset Register H */
#define R_ESC_DC_SYS_TIME_DELAY_OFFSET     0x00000928  /* System Time Delay Register */
#define R_ESC_DC_SYS_TIME_DIFF_OFFSET     0x0000092c  /* System Time Difference Register */
#define R_ESC_DC_SPEED_COUNT_START_OFFSET     0x00000930  /* Speed Counter Start Register */
#define R_ESC_DC_SPEED_COUNT_DIFF_OFFSET     0x00000932  /* Speed Counter Difference Register */
#define R_ESC_DC_SYS_TIME_DIFF_FIL_DEPTH_OFFSET     0x00000934  /* System Time Difference Filter Depth Register */
#define R_ESC_DC_SPEED_COUNT_FIL_DEPTH_OFFSET     0x00000935  /* Speed Counter Filter Depth Register */
#define R_ESC_DC_CYC_CONT_OFFSET     0x00000980  /* Cyclic Unit Control Register */
#define R_ESC_DC_ACT_OFFSET     0x00000981  /* Activation Register */
#define R_ESC_DC_PULSE_LEN_OFFSET     0x00000982  /* SYNC Signal Pulse Length Register */
#define R_ESC_DC_ACT_STAT_OFFSET     0x00000984  /* Activation Status Register */
#define R_ESC_DC_SYNC0_STAT_OFFSET     0x0000098e  /* SYNC0 Status Register */
#define R_ESC_DC_SYNC1_STAT_OFFSET     0x0000098f  /* SYNC1 Status Register */
#define R_ESC_DC_CYC_START_TIME_L_OFFSET     0x00000990  /* Start Time Cyclic Operation/Next SYNC0 Pulse Register L */
#define R_ESC_DC_CYC_START_TIME_H_OFFSET     0x00000994  /* Start Time Cyclic Operation/Next SYNC0 Pulse Register H */
#define R_ESC_DC_NEXT_SYNC1_PULSE_L_OFFSET     0x00000998  /* Next SYNC1 Pulse Register L */
#define R_ESC_DC_NEXT_SYNC1_PULSE_H_OFFSET     0x0000099c  /* Next SYNC1 Pulse Register H */
#define R_ESC_DC_SYNC0_CYC_TIME_OFFSET     0x000009a0  /* SYNC0 Cycle Time Register */
#define R_ESC_DC_SYNC1_CYC_TIME_OFFSET     0x000009a4  /* SYNC1 Cycle Time Register */
#define R_ESC_DC_LATCH0_CONT_OFFSET     0x000009a8  /* Latch 0 Control Register */
#define R_ESC_DC_LATCH1_CONT_OFFSET     0x000009a9  /* Latch 1 Control Register */
#define R_ESC_DC_LATCH0_STAT_OFFSET     0x000009ae  /* Latch 0 Status Register */
#define R_ESC_DC_LATCH1_STAT_OFFSET     0x000009af  /* Latch 1 Status Register */
#define R_ESC_DC_LATCH0_TIME_POS_L_OFFSET     0x000009b0  /* Latch 0 Time Positive Edge Register L */
#define R_ESC_DC_LATCH0_TIME_POS_H_OFFSET     0x000009b4  /* Latch 0 Time Positive Edge Register H */
#define R_ESC_DC_LATCH0_TIME_NEG_L_OFFSET     0x000009b8  /* Latch 0 Time Negative Edge Register L */
#define R_ESC_DC_LATCH0_TIME_NEG_H_OFFSET     0x000009bc  /* Latch 0 Time Negative Edge Register H */
#define R_ESC_DC_LATCH1_TIME_POS_L_OFFSET     0x000009c0  /* Latch 1 Time Positive Edge Register L */
#define R_ESC_DC_LATCH1_TIME_POS_H_OFFSET     0x000009c4  /* Latch 1 Time Positive Edge Register H */
#define R_ESC_DC_LATCH1_TIME_NEG_L_OFFSET     0x000009c8  /* Latch 1 Time Negative Edge Register L */
#define R_ESC_DC_LATCH1_TIME_NEG_H_OFFSET     0x000009cc  /* Latch 1 Time Negative Edge Register H */
#define R_ESC_DC_ECAT_CNG_EV_TIME_OFFSET     0x000009f0  /* Buffer Change Event Time Register */
#define R_ESC_DC_PDI_START_EV_TIME_OFFSET     0x000009f8  /* PDI Buffer Start Event Time Register */
#define R_ESC_DC_PDI_CNG_EV_TIME_OFFSET     0x000009fc  /* PDI Buffer Change Event Time Register */
#define R_ESC_PRODUCT_ID_L_OFFSET     0x00000e00  /* Product ID Register L */
#define R_ESC_PRODUCT_ID_H_OFFSET     0x00000e04  /* Product ID Register H */
#define R_ESC_VENDOR_ID_L_OFFSET     0x00000e08  /* Vendor ID Register L */

/* ESC Register Addresses */

#define R_ESC_TYPE                 (R_ESC_BASE + R_ESC_TYPE_OFFSET)
#define R_ESC_REVISION                 (R_ESC_BASE + R_ESC_REVISION_OFFSET)
#define R_ESC_BUILD                 (R_ESC_BASE + R_ESC_BUILD_OFFSET)
#define R_ESC_FMMU_NUM                 (R_ESC_BASE + R_ESC_FMMU_NUM_OFFSET)
#define R_ESC_SYNC_MANAGER                 (R_ESC_BASE + R_ESC_SYNC_MANAGER_OFFSET)
#define R_ESC_RAM_SIZE                 (R_ESC_BASE + R_ESC_RAM_SIZE_OFFSET)
#define R_ESC_PORT_DESC                 (R_ESC_BASE + R_ESC_PORT_DESC_OFFSET)
#define R_ESC_FEATURE                 (R_ESC_BASE + R_ESC_FEATURE_OFFSET)
#define R_ESC_STATION_ADR                 (R_ESC_BASE + R_ESC_STATION_ADR_OFFSET)
#define R_ESC_STATION_ALIAS                 (R_ESC_BASE + R_ESC_STATION_ALIAS_OFFSET)
#define R_ESC_WR_REG_ENABLE                 (R_ESC_BASE + R_ESC_WR_REG_ENABLE_OFFSET)
#define R_ESC_WR_REG_PROTECT                 (R_ESC_BASE + R_ESC_WR_REG_PROTECT_OFFSET)
#define R_ESC_ESC_WR_ENABLE                 (R_ESC_BASE + R_ESC_ESC_WR_ENABLE_OFFSET)
#define R_ESC_ESC_WR_PROTECT                 (R_ESC_BASE + R_ESC_ESC_WR_PROTECT_OFFSET)
#define R_ESC_ESC_RESET_ECAT_R                 (R_ESC_BASE + R_ESC_ESC_RESET_ECAT_R_OFFSET)
#define R_ESC_ESC_RESET_ECAT_W                 (R_ESC_BASE + R_ESC_ESC_RESET_ECAT_W_OFFSET)
#define R_ESC_ESC_RESET_PDI_R                 (R_ESC_BASE + R_ESC_ESC_RESET_PDI_R_OFFSET)
#define R_ESC_ESC_RESET_PDI_W                 (R_ESC_BASE + R_ESC_ESC_RESET_PDI_W_OFFSET)
#define R_ESC_ESC_DL_CONTROL                 (R_ESC_BASE + R_ESC_ESC_DL_CONTROL_OFFSET)
#define R_ESC_PHYSICAL_RW_OFFSET                 (R_ESC_BASE + R_ESC_PHYSICAL_RW_OFFSET_OFFSET)
#define R_ESC_ESC_DL_STATUS                 (R_ESC_BASE + R_ESC_ESC_DL_STATUS_OFFSET)
#define R_ESC_AL_CONTROL                 (R_ESC_BASE + R_ESC_AL_CONTROL_OFFSET)
#define R_ESC_AL_STATUS                 (R_ESC_BASE + R_ESC_AL_STATUS_OFFSET)
#define R_ESC_AL_STATUS_CODE                 (R_ESC_BASE + R_ESC_AL_STATUS_CODE_OFFSET)
#define R_ESC_RUN_LED_OVERRIDE                 (R_ESC_BASE + R_ESC_RUN_LED_OVERRIDE_OFFSET)
#define R_ESC_ERR_LED_OVERRIDE                 (R_ESC_BASE + R_ESC_ERR_LED_OVERRIDE_OFFSET)
#define R_ESC_PDI_CONTROL                 (R_ESC_BASE + R_ESC_PDI_CONTROL_OFFSET)
#define R_ESC_ESC_CONFIG                 (R_ESC_BASE + R_ESC_ESC_CONFIG_OFFSET)
#define R_ESC_PDI_CONFIG                 (R_ESC_BASE + R_ESC_PDI_CONFIG_OFFSET)
#define R_ESC_SYNC_LATCH_CONFIG                 (R_ESC_BASE + R_ESC_SYNC_LATCH_CONFIG_OFFSET)
#define R_ESC_EXT_PDI_CONFIG                 (R_ESC_BASE + R_ESC_EXT_PDI_CONFIG_OFFSET)
#define R_ESC_ECAT_EVENT_MASK                 (R_ESC_BASE + R_ESC_ECAT_EVENT_MASK_OFFSET)
#define R_ESC_AL_EVENT_MASK                 (R_ESC_BASE + R_ESC_AL_EVENT_MASK_OFFSET)
#define R_ESC_ECAT_EVENT_REQ                 (R_ESC_BASE + R_ESC_ECAT_EVENT_REQ_OFFSET)
#define R_ESC_AL_EVENT_REQ                 (R_ESC_BASE + R_ESC_AL_EVENT_REQ_OFFSET)
#define R_ESC_RX_ERR_COUNT0                 (R_ESC_BASE + R_ESC_RX_ERR_COUNT0_OFFSET)
#define R_ESC_RX_ERR_COUNT1                 (R_ESC_BASE + R_ESC_RX_ERR_COUNT1_OFFSET)
#define R_ESC_FWD_RX_ERR_COUNT0                 (R_ESC_BASE + R_ESC_FWD_RX_ERR_COUNT0_OFFSET)
#define R_ESC_FWD_RX_ERR_COUNT1                 (R_ESC_BASE + R_ESC_FWD_RX_ERR_COUNT1_OFFSET)
#define R_ESC_ECAT_PROC_ERR_COUNT                 (R_ESC_BASE + R_ESC_ECAT_PROC_ERR_COUNT_OFFSET)
#define R_ESC_PDI_ERR_COUNT                 (R_ESC_BASE + R_ESC_PDI_ERR_COUNT_OFFSET)
#define R_ESC_LOST_LINK_COUNT0                 (R_ESC_BASE + R_ESC_LOST_LINK_COUNT0_OFFSET)
#define R_ESC_LOST_LINK_COUNT1                 (R_ESC_BASE + R_ESC_LOST_LINK_COUNT1_OFFSET)
#define R_ESC_WD_DIVIDE                 (R_ESC_BASE + R_ESC_WD_DIVIDE_OFFSET)
#define R_ESC_WDT_PDI                 (R_ESC_BASE + R_ESC_WDT_PDI_OFFSET)
#define R_ESC_WDT_DATA                 (R_ESC_BASE + R_ESC_WDT_DATA_OFFSET)
#define R_ESC_WDS_DATA                 (R_ESC_BASE + R_ESC_WDS_DATA_OFFSET)
#define R_ESC_WDC_DATA                 (R_ESC_BASE + R_ESC_WDC_DATA_OFFSET)
#define R_ESC_WDC_PDI                 (R_ESC_BASE + R_ESC_WDC_PDI_OFFSET)
#define R_ESC_EEP_CONF                 (R_ESC_BASE + R_ESC_EEP_CONF_OFFSET)
#define R_ESC_EEP_STATE                 (R_ESC_BASE + R_ESC_EEP_STATE_OFFSET)
#define R_ESC_EEP_CONT_STAT                 (R_ESC_BASE + R_ESC_EEP_CONT_STAT_OFFSET)
#define R_ESC_EEP_ADR                 (R_ESC_BASE + R_ESC_EEP_ADR_OFFSET)
#define R_ESC_EEP_DATA                 (R_ESC_BASE + R_ESC_EEP_DATA_OFFSET)
#define R_ESC_MII_CONT_STAT                 (R_ESC_BASE + R_ESC_MII_CONT_STAT_OFFSET)
#define R_ESC_PHY_ADR                 (R_ESC_BASE + R_ESC_PHY_ADR_OFFSET)
#define R_ESC_PHY_REG_ADR                 (R_ESC_BASE + R_ESC_PHY_REG_ADR_OFFSET)
#define R_ESC_PHY_DATA                 (R_ESC_BASE + R_ESC_PHY_DATA_OFFSET)
#define R_ESC_MII_ECAT_ACS_STAT                 (R_ESC_BASE + R_ESC_MII_ECAT_ACS_STAT_OFFSET)
#define R_ESC_MII_PDI_ACS_STAT                 (R_ESC_BASE + R_ESC_MII_PDI_ACS_STAT_OFFSET)
#define R_ESC_FMMU0_L_START_ADR                 (R_ESC_BASE + R_ESC_FMMU0_L_START_ADR_OFFSET)
#define R_ESC_FMMU1_L_START_ADR                 (R_ESC_BASE + R_ESC_FMMU1_L_START_ADR_OFFSET)
#define R_ESC_FMMU2_L_START_ADR                 (R_ESC_BASE + R_ESC_FMMU2_L_START_ADR_OFFSET)
#define R_ESC_FMMU3_L_START_ADR                 (R_ESC_BASE + R_ESC_FMMU3_L_START_ADR_OFFSET)
#define R_ESC_FMMU4_L_START_ADR                 (R_ESC_BASE + R_ESC_FMMU4_L_START_ADR_OFFSET)
#define R_ESC_FMMU5_L_START_ADR                 (R_ESC_BASE + R_ESC_FMMU5_L_START_ADR_OFFSET)
#define R_ESC_FMMU6_L_START_ADR                 (R_ESC_BASE + R_ESC_FMMU6_L_START_ADR_OFFSET)
#define R_ESC_FMMU7_L_START_ADR                 (R_ESC_BASE + R_ESC_FMMU7_L_START_ADR_OFFSET)
#define R_ESC_FMMU0_LEN                 (R_ESC_BASE + R_ESC_FMMU0_LEN_OFFSET)
#define R_ESC_FMMU1_LEN                 (R_ESC_BASE + R_ESC_FMMU1_LEN_OFFSET)
#define R_ESC_FMMU2_LEN                 (R_ESC_BASE + R_ESC_FMMU2_LEN_OFFSET)
#define R_ESC_FMMU3_LEN                 (R_ESC_BASE + R_ESC_FMMU3_LEN_OFFSET)
#define R_ESC_FMMU4_LEN                 (R_ESC_BASE + R_ESC_FMMU4_LEN_OFFSET)
#define R_ESC_FMMU5_LEN                 (R_ESC_BASE + R_ESC_FMMU5_LEN_OFFSET)
#define R_ESC_FMMU6_LEN                 (R_ESC_BASE + R_ESC_FMMU6_LEN_OFFSET)
#define R_ESC_FMMU7_LEN                 (R_ESC_BASE + R_ESC_FMMU7_LEN_OFFSET)
#define R_ESC_FMMU0_L_START_BIT                 (R_ESC_BASE + R_ESC_FMMU0_L_START_BIT_OFFSET)
#define R_ESC_FMMU1_L_START_BIT                 (R_ESC_BASE + R_ESC_FMMU1_L_START_BIT_OFFSET)
#define R_ESC_FMMU2_L_START_BIT                 (R_ESC_BASE + R_ESC_FMMU2_L_START_BIT_OFFSET)
#define R_ESC_FMMU3_L_START_BIT                 (R_ESC_BASE + R_ESC_FMMU3_L_START_BIT_OFFSET)
#define R_ESC_FMMU4_L_START_BIT                 (R_ESC_BASE + R_ESC_FMMU4_L_START_BIT_OFFSET)
#define R_ESC_FMMU5_L_START_BIT                 (R_ESC_BASE + R_ESC_FMMU5_L_START_BIT_OFFSET)
#define R_ESC_FMMU6_L_START_BIT                 (R_ESC_BASE + R_ESC_FMMU6_L_START_BIT_OFFSET)
#define R_ESC_FMMU7_L_START_BIT                 (R_ESC_BASE + R_ESC_FMMU7_L_START_BIT_OFFSET)
#define R_ESC_FMMU0_L_STOP_BIT                 (R_ESC_BASE + R_ESC_FMMU0_L_STOP_BIT_OFFSET)
#define R_ESC_FMMU1_L_STOP_BIT                 (R_ESC_BASE + R_ESC_FMMU1_L_STOP_BIT_OFFSET)
#define R_ESC_FMMU2_L_STOP_BIT                 (R_ESC_BASE + R_ESC_FMMU2_L_STOP_BIT_OFFSET)
#define R_ESC_FMMU3_L_STOP_BIT                 (R_ESC_BASE + R_ESC_FMMU3_L_STOP_BIT_OFFSET)
#define R_ESC_FMMU4_L_STOP_BIT                 (R_ESC_BASE + R_ESC_FMMU4_L_STOP_BIT_OFFSET)
#define R_ESC_FMMU5_L_STOP_BIT                 (R_ESC_BASE + R_ESC_FMMU5_L_STOP_BIT_OFFSET)
#define R_ESC_FMMU6_L_STOP_BIT                 (R_ESC_BASE + R_ESC_FMMU6_L_STOP_BIT_OFFSET)
#define R_ESC_FMMU7_L_STOP_BIT                 (R_ESC_BASE + R_ESC_FMMU7_L_STOP_BIT_OFFSET)
#define R_ESC_FMMU0_P_START_ADR                 (R_ESC_BASE + R_ESC_FMMU0_P_START_ADR_OFFSET)
#define R_ESC_FMMU1_P_START_ADR                 (R_ESC_BASE + R_ESC_FMMU1_P_START_ADR_OFFSET)
#define R_ESC_FMMU2_P_START_ADR                 (R_ESC_BASE + R_ESC_FMMU2_P_START_ADR_OFFSET)
#define R_ESC_FMMU3_P_START_ADR                 (R_ESC_BASE + R_ESC_FMMU3_P_START_ADR_OFFSET)
#define R_ESC_FMMU4_P_START_ADR                 (R_ESC_BASE + R_ESC_FMMU4_P_START_ADR_OFFSET)
#define R_ESC_FMMU5_P_START_ADR                 (R_ESC_BASE + R_ESC_FMMU5_P_START_ADR_OFFSET)
#define R_ESC_FMMU6_P_START_ADR                 (R_ESC_BASE + R_ESC_FMMU6_P_START_ADR_OFFSET)
#define R_ESC_FMMU7_P_START_ADR                 (R_ESC_BASE + R_ESC_FMMU7_P_START_ADR_OFFSET)
#define R_ESC_FMMU0_P_START_BIT                 (R_ESC_BASE + R_ESC_FMMU0_P_START_BIT_OFFSET)
#define R_ESC_FMMU1_P_START_BIT                 (R_ESC_BASE + R_ESC_FMMU1_P_START_BIT_OFFSET)
#define R_ESC_FMMU2_P_START_BIT                 (R_ESC_BASE + R_ESC_FMMU2_P_START_BIT_OFFSET)
#define R_ESC_FMMU3_P_START_BIT                 (R_ESC_BASE + R_ESC_FMMU3_P_START_BIT_OFFSET)
#define R_ESC_FMMU4_P_START_BIT                 (R_ESC_BASE + R_ESC_FMMU4_P_START_BIT_OFFSET)
#define R_ESC_FMMU5_P_START_BIT                 (R_ESC_BASE + R_ESC_FMMU5_P_START_BIT_OFFSET)
#define R_ESC_FMMU6_P_START_BIT                 (R_ESC_BASE + R_ESC_FMMU6_P_START_BIT_OFFSET)
#define R_ESC_FMMU7_P_START_BIT                 (R_ESC_BASE + R_ESC_FMMU7_P_START_BIT_OFFSET)
#define R_ESC_FMMU0_TYPE                 (R_ESC_BASE + R_ESC_FMMU0_TYPE_OFFSET)
#define R_ESC_FMMU1_TYPE                 (R_ESC_BASE + R_ESC_FMMU1_TYPE_OFFSET)
#define R_ESC_FMMU2_TYPE                 (R_ESC_BASE + R_ESC_FMMU2_TYPE_OFFSET)
#define R_ESC_FMMU3_TYPE                 (R_ESC_BASE + R_ESC_FMMU3_TYPE_OFFSET)
#define R_ESC_FMMU4_TYPE                 (R_ESC_BASE + R_ESC_FMMU4_TYPE_OFFSET)
#define R_ESC_FMMU5_TYPE                 (R_ESC_BASE + R_ESC_FMMU5_TYPE_OFFSET)
#define R_ESC_FMMU6_TYPE                 (R_ESC_BASE + R_ESC_FMMU6_TYPE_OFFSET)
#define R_ESC_FMMU7_TYPE                 (R_ESC_BASE + R_ESC_FMMU7_TYPE_OFFSET)
#define R_ESC_FMMU0_ACT                 (R_ESC_BASE + R_ESC_FMMU0_ACT_OFFSET)
#define R_ESC_FMMU1_ACT                 (R_ESC_BASE + R_ESC_FMMU1_ACT_OFFSET)
#define R_ESC_FMMU2_ACT                 (R_ESC_BASE + R_ESC_FMMU2_ACT_OFFSET)
#define R_ESC_FMMU3_ACT                 (R_ESC_BASE + R_ESC_FMMU3_ACT_OFFSET)
#define R_ESC_FMMU4_ACT                 (R_ESC_BASE + R_ESC_FMMU4_ACT_OFFSET)
#define R_ESC_FMMU5_ACT                 (R_ESC_BASE + R_ESC_FMMU5_ACT_OFFSET)
#define R_ESC_FMMU6_ACT                 (R_ESC_BASE + R_ESC_FMMU6_ACT_OFFSET)
#define R_ESC_FMMU7_ACT                 (R_ESC_BASE + R_ESC_FMMU7_ACT_OFFSET)
#define R_ESC_SM0_P_START_ADR                 (R_ESC_BASE + R_ESC_SM0_P_START_ADR_OFFSET)
#define R_ESC_SM1_P_START_ADR                 (R_ESC_BASE + R_ESC_SM1_P_START_ADR_OFFSET)
#define R_ESC_SM2_P_START_ADR                 (R_ESC_BASE + R_ESC_SM2_P_START_ADR_OFFSET)
#define R_ESC_SM3_P_START_ADR                 (R_ESC_BASE + R_ESC_SM3_P_START_ADR_OFFSET)
#define R_ESC_SM4_P_START_ADR                 (R_ESC_BASE + R_ESC_SM4_P_START_ADR_OFFSET)
#define R_ESC_SM5_P_START_ADR                 (R_ESC_BASE + R_ESC_SM5_P_START_ADR_OFFSET)
#define R_ESC_SM6_P_START_ADR                 (R_ESC_BASE + R_ESC_SM6_P_START_ADR_OFFSET)
#define R_ESC_SM7_P_START_ADR                 (R_ESC_BASE + R_ESC_SM7_P_START_ADR_OFFSET)
#define R_ESC_SM0_LEN                 (R_ESC_BASE + R_ESC_SM0_LEN_OFFSET)
#define R_ESC_SM1_LEN                 (R_ESC_BASE + R_ESC_SM1_LEN_OFFSET)
#define R_ESC_SM2_LEN                 (R_ESC_BASE + R_ESC_SM2_LEN_OFFSET)
#define R_ESC_SM3_LEN                 (R_ESC_BASE + R_ESC_SM3_LEN_OFFSET)
#define R_ESC_SM4_LEN                 (R_ESC_BASE + R_ESC_SM4_LEN_OFFSET)
#define R_ESC_SM5_LEN                 (R_ESC_BASE + R_ESC_SM5_LEN_OFFSET)
#define R_ESC_SM6_LEN                 (R_ESC_BASE + R_ESC_SM6_LEN_OFFSET)
#define R_ESC_SM7_LEN                 (R_ESC_BASE + R_ESC_SM7_LEN_OFFSET)
#define R_ESC_SM0_CONTROL                 (R_ESC_BASE + R_ESC_SM0_CONTROL_OFFSET)
#define R_ESC_SM1_CONTROL                 (R_ESC_BASE + R_ESC_SM1_CONTROL_OFFSET)
#define R_ESC_SM2_CONTROL                 (R_ESC_BASE + R_ESC_SM2_CONTROL_OFFSET)
#define R_ESC_SM3_CONTROL                 (R_ESC_BASE + R_ESC_SM3_CONTROL_OFFSET)
#define R_ESC_SM4_CONTROL                 (R_ESC_BASE + R_ESC_SM4_CONTROL_OFFSET)
#define R_ESC_SM5_CONTROL                 (R_ESC_BASE + R_ESC_SM5_CONTROL_OFFSET)
#define R_ESC_SM6_CONTROL                 (R_ESC_BASE + R_ESC_SM6_CONTROL_OFFSET)
#define R_ESC_SM7_CONTROL                 (R_ESC_BASE + R_ESC_SM7_CONTROL_OFFSET)
#define R_ESC_SM0_STATUS                 (R_ESC_BASE + R_ESC_SM0_STATUS_OFFSET)
#define R_ESC_SM1_STATUS                 (R_ESC_BASE + R_ESC_SM1_STATUS_OFFSET)
#define R_ESC_SM2_STATUS                 (R_ESC_BASE + R_ESC_SM2_STATUS_OFFSET)
#define R_ESC_SM3_STATUS                 (R_ESC_BASE + R_ESC_SM3_STATUS_OFFSET)
#define R_ESC_SM4_STATUS                 (R_ESC_BASE + R_ESC_SM4_STATUS_OFFSET)
#define R_ESC_SM5_STATUS                 (R_ESC_BASE + R_ESC_SM5_STATUS_OFFSET)
#define R_ESC_SM6_STATUS                 (R_ESC_BASE + R_ESC_SM6_STATUS_OFFSET)
#define R_ESC_SM7_STATUS                 (R_ESC_BASE + R_ESC_SM7_STATUS_OFFSET)
#define R_ESC_SM0_ACT                 (R_ESC_BASE + R_ESC_SM0_ACT_OFFSET)
#define R_ESC_SM1_ACT                 (R_ESC_BASE + R_ESC_SM1_ACT_OFFSET)
#define R_ESC_SM2_ACT                 (R_ESC_BASE + R_ESC_SM2_ACT_OFFSET)
#define R_ESC_SM3_ACT                 (R_ESC_BASE + R_ESC_SM3_ACT_OFFSET)
#define R_ESC_SM4_ACT                 (R_ESC_BASE + R_ESC_SM4_ACT_OFFSET)
#define R_ESC_SM5_ACT                 (R_ESC_BASE + R_ESC_SM5_ACT_OFFSET)
#define R_ESC_SM6_ACT                 (R_ESC_BASE + R_ESC_SM6_ACT_OFFSET)
#define R_ESC_SM7_ACT                 (R_ESC_BASE + R_ESC_SM7_ACT_OFFSET)
#define R_ESC_SM0_PDI_CONT                 (R_ESC_BASE + R_ESC_SM0_PDI_CONT_OFFSET)
#define R_ESC_SM1_PDI_CONT                 (R_ESC_BASE + R_ESC_SM1_PDI_CONT_OFFSET)
#define R_ESC_SM2_PDI_CONT                 (R_ESC_BASE + R_ESC_SM2_PDI_CONT_OFFSET)
#define R_ESC_SM3_PDI_CONT                 (R_ESC_BASE + R_ESC_SM3_PDI_CONT_OFFSET)
#define R_ESC_SM4_PDI_CONT                 (R_ESC_BASE + R_ESC_SM4_PDI_CONT_OFFSET)
#define R_ESC_SM5_PDI_CONT                 (R_ESC_BASE + R_ESC_SM5_PDI_CONT_OFFSET)
#define R_ESC_SM6_PDI_CONT                 (R_ESC_BASE + R_ESC_SM6_PDI_CONT_OFFSET)
#define R_ESC_SM7_PDI_CONT                 (R_ESC_BASE + R_ESC_SM7_PDI_CONT_OFFSET)
#define R_ESC_DC_RCV_TIME_PORT0                 (R_ESC_BASE + R_ESC_DC_RCV_TIME_PORT0_OFFSET)
#define R_ESC_DC_RCV_TIME_PORT1                 (R_ESC_BASE + R_ESC_DC_RCV_TIME_PORT1_OFFSET)
#define R_ESC_DC_RCV_TIME_PORT2                 (R_ESC_BASE + R_ESC_DC_RCV_TIME_PORT2_OFFSET)
#define R_ESC_DC_SYS_TIME_L                 (R_ESC_BASE + R_ESC_DC_SYS_TIME_L_OFFSET)
#define R_ESC_DC_SYS_TIME_H                 (R_ESC_BASE + R_ESC_DC_SYS_TIME_H_OFFSET)
#define R_ESC_DC_RCV_TIME_UNIT_L                 (R_ESC_BASE + R_ESC_DC_RCV_TIME_UNIT_L_OFFSET)
#define R_ESC_DC_RCV_TIME_UNIT_H                 (R_ESC_BASE + R_ESC_DC_RCV_TIME_UNIT_H_OFFSET)
#define R_ESC_DC_SYS_TIME_OFFSET_L                 (R_ESC_BASE + R_ESC_DC_SYS_TIME_OFFSET_L_OFFSET)
#define R_ESC_DC_SYS_TIME_OFFSET_H                 (R_ESC_BASE + R_ESC_DC_SYS_TIME_OFFSET_H_OFFSET)
#define R_ESC_DC_SYS_TIME_DELAY                 (R_ESC_BASE + R_ESC_DC_SYS_TIME_DELAY_OFFSET)
#define R_ESC_DC_SYS_TIME_DIFF                 (R_ESC_BASE + R_ESC_DC_SYS_TIME_DIFF_OFFSET)
#define R_ESC_DC_SPEED_COUNT_START                 (R_ESC_BASE + R_ESC_DC_SPEED_COUNT_START_OFFSET)
#define R_ESC_DC_SPEED_COUNT_DIFF                 (R_ESC_BASE + R_ESC_DC_SPEED_COUNT_DIFF_OFFSET)
#define R_ESC_DC_SYS_TIME_DIFF_FIL_DEPTH                 (R_ESC_BASE + R_ESC_DC_SYS_TIME_DIFF_FIL_DEPTH_OFFSET)
#define R_ESC_DC_SPEED_COUNT_FIL_DEPTH                 (R_ESC_BASE + R_ESC_DC_SPEED_COUNT_FIL_DEPTH_OFFSET)
#define R_ESC_DC_CYC_CONT                 (R_ESC_BASE + R_ESC_DC_CYC_CONT_OFFSET)
#define R_ESC_DC_ACT                 (R_ESC_BASE + R_ESC_DC_ACT_OFFSET)
#define R_ESC_DC_PULSE_LEN                 (R_ESC_BASE + R_ESC_DC_PULSE_LEN_OFFSET)
#define R_ESC_DC_ACT_STAT                 (R_ESC_BASE + R_ESC_DC_ACT_STAT_OFFSET)
#define R_ESC_DC_SYNC0_STAT                 (R_ESC_BASE + R_ESC_DC_SYNC0_STAT_OFFSET)
#define R_ESC_DC_SYNC1_STAT                 (R_ESC_BASE + R_ESC_DC_SYNC1_STAT_OFFSET)
#define R_ESC_DC_CYC_START_TIME_L                 (R_ESC_BASE + R_ESC_DC_CYC_START_TIME_L_OFFSET)
#define R_ESC_DC_CYC_START_TIME_H                 (R_ESC_BASE + R_ESC_DC_CYC_START_TIME_H_OFFSET)
#define R_ESC_DC_NEXT_SYNC1_PULSE_L                 (R_ESC_BASE + R_ESC_DC_NEXT_SYNC1_PULSE_L_OFFSET)
#define R_ESC_DC_NEXT_SYNC1_PULSE_H                 (R_ESC_BASE + R_ESC_DC_NEXT_SYNC1_PULSE_H_OFFSET)
#define R_ESC_DC_SYNC0_CYC_TIME                 (R_ESC_BASE + R_ESC_DC_SYNC0_CYC_TIME_OFFSET)
#define R_ESC_DC_SYNC1_CYC_TIME                 (R_ESC_BASE + R_ESC_DC_SYNC1_CYC_TIME_OFFSET)
#define R_ESC_DC_LATCH0_CONT                 (R_ESC_BASE + R_ESC_DC_LATCH0_CONT_OFFSET)
#define R_ESC_DC_LATCH1_CONT                 (R_ESC_BASE + R_ESC_DC_LATCH1_CONT_OFFSET)
#define R_ESC_DC_LATCH0_STAT                 (R_ESC_BASE + R_ESC_DC_LATCH0_STAT_OFFSET)
#define R_ESC_DC_LATCH1_STAT                 (R_ESC_BASE + R_ESC_DC_LATCH1_STAT_OFFSET)
#define R_ESC_DC_LATCH0_TIME_POS_L                 (R_ESC_BASE + R_ESC_DC_LATCH0_TIME_POS_L_OFFSET)
#define R_ESC_DC_LATCH0_TIME_POS_H                 (R_ESC_BASE + R_ESC_DC_LATCH0_TIME_POS_H_OFFSET)
#define R_ESC_DC_LATCH0_TIME_NEG_L                 (R_ESC_BASE + R_ESC_DC_LATCH0_TIME_NEG_L_OFFSET)
#define R_ESC_DC_LATCH0_TIME_NEG_H                 (R_ESC_BASE + R_ESC_DC_LATCH0_TIME_NEG_H_OFFSET)
#define R_ESC_DC_LATCH1_TIME_POS_L                 (R_ESC_BASE + R_ESC_DC_LATCH1_TIME_POS_L_OFFSET)
#define R_ESC_DC_LATCH1_TIME_POS_H                 (R_ESC_BASE + R_ESC_DC_LATCH1_TIME_POS_H_OFFSET)
#define R_ESC_DC_LATCH1_TIME_NEG_L                 (R_ESC_BASE + R_ESC_DC_LATCH1_TIME_NEG_L_OFFSET)
#define R_ESC_DC_LATCH1_TIME_NEG_H                 (R_ESC_BASE + R_ESC_DC_LATCH1_TIME_NEG_H_OFFSET)
#define R_ESC_DC_ECAT_CNG_EV_TIME                 (R_ESC_BASE + R_ESC_DC_ECAT_CNG_EV_TIME_OFFSET)
#define R_ESC_DC_PDI_START_EV_TIME                 (R_ESC_BASE + R_ESC_DC_PDI_START_EV_TIME_OFFSET)
#define R_ESC_DC_PDI_CNG_EV_TIME                 (R_ESC_BASE + R_ESC_DC_PDI_CNG_EV_TIME_OFFSET)
#define R_ESC_PRODUCT_ID_L                 (R_ESC_BASE + R_ESC_PRODUCT_ID_L_OFFSET)
#define R_ESC_PRODUCT_ID_H                 (R_ESC_BASE + R_ESC_PRODUCT_ID_H_OFFSET)
#define R_ESC_VENDOR_ID_L                 (R_ESC_BASE + R_ESC_VENDOR_ID_L_OFFSET)

/* Register bit definitions */
/* TYPE Register bit definitions */
#define R_ESC_TYPE_TYPE_SHIFT                     (0)  /* Type of the EtherCAT slave controller */
#define R_ESC_TYPE_TYPE_MASK                      0xff

/* REVISION Register bit definitions */
#define R_ESC_REVISION_REV_SHIFT                  (0)  /* Revision of the EtherCAT slave controller */
#define R_ESC_REVISION_REV_MASK                   0xff

/* BUILD Register bit definitions */
#define R_ESC_BUILD_BUILD_SHIFT                   (0)  /* Build number of the EtherCAT slave controller */
#define R_ESC_BUILD_BUILD_MASK                    0xff

/* FMMU_NUM Register bit definitions */
#define R_ESC_FMMU_NUM_NUMFMMU_SHIFT              (0)  /* Number of FMMU channels supported in the EtherCAT slave controller */
#define R_ESC_FMMU_NUM_NUMFMMU_MASK               0xff

/* SYNC_MANAGER Register bit definitions */
#define R_ESC_SYNC_MANAGER_NUMSYNC_SHIFT          (0)  /* Number of SyncManager channels supported in the EtherCAT slave controller */
#define R_ESC_SYNC_MANAGER_NUMSYNC_MASK           0xff

/* RAM_SIZE Register bit definitions */
#define R_ESC_RAM_SIZE_RAMSIZE_SHIFT              (0)  /* Process data RAM size supported in the EtherCAT slave controller (unit: KB) */
#define R_ESC_RAM_SIZE_RAMSIZE_MASK               0xff

/* PORT_DESC Register bit definitions */
#define R_ESC_PORT_DESC_P0_SHIFT                  (0)  /* Port 0 configuration */
#define R_ESC_PORT_DESC_P0_MASK                   0x3
#  define R_ESC_PORT_DESC_P0_00                           (0 << R_ESC_PORT_DESC_P0_SHIFT)  /* Not implemented */
#  define R_ESC_PORT_DESC_P0_01                           (1 << R_ESC_PORT_DESC_P0_SHIFT)  /* Not configured (SII EEPROM) */
#  define R_ESC_PORT_DESC_P0_10                           (2 << R_ESC_PORT_DESC_P0_SHIFT)  /* EBUS */
#  define R_ESC_PORT_DESC_P0_11                           (3 << R_ESC_PORT_DESC_P0_SHIFT)  /* MII */

#define R_ESC_PORT_DESC_P1_SHIFT                  (2)  /* Port 1 configuration */
#define R_ESC_PORT_DESC_P1_MASK                   0xc
#  define R_ESC_PORT_DESC_P1_00                           (0 << R_ESC_PORT_DESC_P1_SHIFT)  /* Not implemented */
#  define R_ESC_PORT_DESC_P1_01                           (1 << R_ESC_PORT_DESC_P1_SHIFT)  /* Not configured (SII EEPROM) */
#  define R_ESC_PORT_DESC_P1_10                           (2 << R_ESC_PORT_DESC_P1_SHIFT)  /* EBUS */
#  define R_ESC_PORT_DESC_P1_11                           (3 << R_ESC_PORT_DESC_P1_SHIFT)  /* MII */

#define R_ESC_PORT_DESC_P2_SHIFT                  (4)  /* Port 2 configuration */
#define R_ESC_PORT_DESC_P2_MASK                   0x30
#  define R_ESC_PORT_DESC_P2_00                           (0 << R_ESC_PORT_DESC_P2_SHIFT)  /* Not implemented */
#  define R_ESC_PORT_DESC_P2_01                           (1 << R_ESC_PORT_DESC_P2_SHIFT)  /* Not configured (SII EEPROM) */
#  define R_ESC_PORT_DESC_P2_10                           (2 << R_ESC_PORT_DESC_P2_SHIFT)  /* EBUS */
#  define R_ESC_PORT_DESC_P2_11                           (3 << R_ESC_PORT_DESC_P2_SHIFT)  /* MII */

#define R_ESC_PORT_DESC_P3_SHIFT                  (6)  /* Port 3 configuration */
#define R_ESC_PORT_DESC_P3_MASK                   0xc0
#  define R_ESC_PORT_DESC_P3_00                           (0 << R_ESC_PORT_DESC_P3_SHIFT)  /* Not implemented */
#  define R_ESC_PORT_DESC_P3_01                           (1 << R_ESC_PORT_DESC_P3_SHIFT)  /* Not configured (SII EEPROM) */
#  define R_ESC_PORT_DESC_P3_10                           (2 << R_ESC_PORT_DESC_P3_SHIFT)  /* EBUS */
#  define R_ESC_PORT_DESC_P3_11                           (3 << R_ESC_PORT_DESC_P3_SHIFT)  /* MII */

/* FEATURE Register bit definitions */
#define R_ESC_FEATURE_FMMU                        (1 << 0)  /* FMMU Operation */

#define R_ESC_FEATURE_DC                          (1 << 2)  /* Distributed Clock */

#define R_ESC_FEATURE_DCWID                       (1 << 3)  /* Distributed Clock Width */

#define R_ESC_FEATURE_LINKDECMII                  (1 << 6)  /* Enhanced Link Detection in MII */

#define R_ESC_FEATURE_FCS                         (1 << 7)  /* Separate handling of FCS errors */

#define R_ESC_FEATURE_DCSYNC                      (1 << 8)  /* Enhanced DC SYNC activation */

#define R_ESC_FEATURE_LRW                         (1 << 9)  /* EtherCAT LRW command support */

#define R_ESC_FEATURE_RWSUPP                      (1 << 10)  /* EtherCAT read/write command support (BRW, APRW, FPRW) */

#define R_ESC_FEATURE_FSCONFIG                    (1 << 11)  /* Fixed FMMU/SyncManager configuration */

/* STATION_ADR Register bit definitions */
#define R_ESC_STATION_ADR_NODADDR_SHIFT           (0)  /* Node Addressing Address Indication */
#define R_ESC_STATION_ADR_NODADDR_MASK            0xffff

/* STATION_ALIAS Register bit definitions */
#define R_ESC_STATION_ALIAS_NODALIADDR_SHIFT      (0)  /* Alias Address Indication */
#define R_ESC_STATION_ALIAS_NODALIADDR_MASK       0xffff

/* WR_REG_ENABLE Register bit definitions */
#define R_ESC_WR_REG_ENABLE_ENABLE                (1 << 0)  /* Register Write Protection Unlock */

/* WR_REG_PROTECT Register bit definitions */
#define R_ESC_WR_REG_PROTECT_PROTECT              (1 << 0)  /* Register Write Protection Specification */

/* ESC_WR_ENABLE Register bit definitions */
#define R_ESC_ESC_WR_ENABLE_ENABLE                (1 << 0)  /* Register/Memory Write Protection Unlock */

/* ESC_WR_PROTECT Register bit definitions */
#define R_ESC_ESC_WR_PROTECT_PROTECT              (1 << 0)  /* Register/Memory Write Protection Specification */

/* ESC_RESET_ECAT_R Register bit definitions */
#define R_ESC_ESC_RESET_ECAT_R_RESET_ECAT_SHIFT   (0)  /* Reset Progress Status */
#define R_ESC_ESC_RESET_ECAT_R_RESET_ECAT_MASK    0x3
#  define R_ESC_ESC_RESET_ECAT_R_RESET_ECAT_01            (1 << R_ESC_ESC_RESET_ECAT_R_RESET_ECAT_SHIFT)  /* After writing 0x52 */
#  define R_ESC_ESC_RESET_ECAT_R_RESET_ECAT_10            (2 << R_ESC_ESC_RESET_ECAT_R_RESET_ECAT_SHIFT)  /* After writing 0x45 (if 0x52 was written before) */
#  define R_ESC_ESC_RESET_ECAT_R_RESET_ECAT_00            (0 << R_ESC_ESC_RESET_ECAT_R_RESET_ECAT_SHIFT)  /* Others */

/* ESC_RESET_ECAT_W Register bit definitions */
#define R_ESC_ESC_RESET_ECAT_W_RESET_ECAT_SHIFT   (0)  /* Software Reset Setting */
#define R_ESC_ESC_RESET_ECAT_W_RESET_ECAT_MASK    0xff

/* ESC_RESET_PDI_R Register bit definitions */
#define R_ESC_ESC_RESET_PDI_R_RESET_PDI_SHIFT     (0)  /* Reset Progress Status */
#define R_ESC_ESC_RESET_PDI_R_RESET_PDI_MASK      0x3
#  define R_ESC_ESC_RESET_PDI_R_RESET_PDI_01              (1 << R_ESC_ESC_RESET_PDI_R_RESET_PDI_SHIFT)  /* After writing 0x52 */
#  define R_ESC_ESC_RESET_PDI_R_RESET_PDI_10              (2 << R_ESC_ESC_RESET_PDI_R_RESET_PDI_SHIFT)  /* After writing 0x45 (if 0x52 was written before) */
#  define R_ESC_ESC_RESET_PDI_R_RESET_PDI_00              (0 << R_ESC_ESC_RESET_PDI_R_RESET_PDI_SHIFT)  /* Others */

/* ESC_RESET_PDI_W Register bit definitions */
#define R_ESC_ESC_RESET_PDI_W_RESET_PDI_SHIFT     (0)  /* Software Reset Setting */
#define R_ESC_ESC_RESET_PDI_W_RESET_PDI_MASK      0xff

/* ESC_DL_CONTROL Register bit definitions */
#define R_ESC_ESC_DL_CONTROL_FWDRULE              (1 << 0)  /* Forwarding Rule */

#define R_ESC_ESC_DL_CONTROL_TEMPUSE              (1 << 1)  /* Temporary Use of Bits 15 to 8 Settings */

#define R_ESC_ESC_DL_CONTROL_LP0_SHIFT            (8)  /* Loop Port 0 Configuration */
#define R_ESC_ESC_DL_CONTROL_LP0_MASK             0x300
#  define R_ESC_ESC_DL_CONTROL_LP0_00                     (0 << R_ESC_ESC_DL_CONTROL_LP0_SHIFT)  /* Auto */
#  define R_ESC_ESC_DL_CONTROL_LP0_01                     (1 << R_ESC_ESC_DL_CONTROL_LP0_SHIFT)  /* Auto close */
#  define R_ESC_ESC_DL_CONTROL_LP0_10                     (2 << R_ESC_ESC_DL_CONTROL_LP0_SHIFT)  /* Open */
#  define R_ESC_ESC_DL_CONTROL_LP0_11                     (3 << R_ESC_ESC_DL_CONTROL_LP0_SHIFT)  /* Closed */

#define R_ESC_ESC_DL_CONTROL_LP1_SHIFT            (10)  /* Loop Port 1 Configuration */
#define R_ESC_ESC_DL_CONTROL_LP1_MASK             0xc00
#  define R_ESC_ESC_DL_CONTROL_LP1_00                     (0 << R_ESC_ESC_DL_CONTROL_LP1_SHIFT)  /* Auto */
#  define R_ESC_ESC_DL_CONTROL_LP1_01                     (1 << R_ESC_ESC_DL_CONTROL_LP1_SHIFT)  /* Auto close */
#  define R_ESC_ESC_DL_CONTROL_LP1_10                     (2 << R_ESC_ESC_DL_CONTROL_LP1_SHIFT)  /* Open */
#  define R_ESC_ESC_DL_CONTROL_LP1_11                     (3 << R_ESC_ESC_DL_CONTROL_LP1_SHIFT)  /* Closed */

#define R_ESC_ESC_DL_CONTROL_LP2_SHIFT            (12)  /* Loop Port 2 Configuration */
#define R_ESC_ESC_DL_CONTROL_LP2_MASK             0x3000
#  define R_ESC_ESC_DL_CONTROL_LP2_00                     (0 << R_ESC_ESC_DL_CONTROL_LP2_SHIFT)  /* Auto */
#  define R_ESC_ESC_DL_CONTROL_LP2_01                     (1 << R_ESC_ESC_DL_CONTROL_LP2_SHIFT)  /* Auto close */
#  define R_ESC_ESC_DL_CONTROL_LP2_10                     (2 << R_ESC_ESC_DL_CONTROL_LP2_SHIFT)  /* Open */
#  define R_ESC_ESC_DL_CONTROL_LP2_11                     (3 << R_ESC_ESC_DL_CONTROL_LP2_SHIFT)  /* Closed */

#define R_ESC_ESC_DL_CONTROL_LP3_SHIFT            (14)  /* Loop Port 3 Configuration */
#define R_ESC_ESC_DL_CONTROL_LP3_MASK             0xc000
#  define R_ESC_ESC_DL_CONTROL_LP3_00                     (0 << R_ESC_ESC_DL_CONTROL_LP3_SHIFT)  /* Auto */
#  define R_ESC_ESC_DL_CONTROL_LP3_01                     (1 << R_ESC_ESC_DL_CONTROL_LP3_SHIFT)  /* Auto close */
#  define R_ESC_ESC_DL_CONTROL_LP3_10                     (2 << R_ESC_ESC_DL_CONTROL_LP3_SHIFT)  /* Open */
#  define R_ESC_ESC_DL_CONTROL_LP3_11                     (3 << R_ESC_ESC_DL_CONTROL_LP3_SHIFT)  /* Closed */

#define R_ESC_ESC_DL_CONTROL_RXFIFO_SHIFT         (16)  /* RX FIFO Size */
#define R_ESC_ESC_DL_CONTROL_RXFIFO_MASK          0x70000
#  define R_ESC_ESC_DL_CONTROL_RXFIFO_00X                 (0 << R_ESC_ESC_DL_CONTROL_RXFIFO_SHIFT)  /* Shortened by 40 ns */
#  define R_ESC_ESC_DL_CONTROL_RXFIFO_01X                 (0 << R_ESC_ESC_DL_CONTROL_RXFIFO_SHIFT)  /* Shortened by 40 ns */
#  define R_ESC_ESC_DL_CONTROL_RXFIFO_110                 (6 << R_ESC_ESC_DL_CONTROL_RXFIFO_SHIFT)  /* No change */
#  define R_ESC_ESC_DL_CONTROL_RXFIFO_111                 (7 << R_ESC_ESC_DL_CONTROL_RXFIFO_SHIFT)  /* Default */

#define R_ESC_ESC_DL_CONTROL_STAALIAS             (1 << 24)  /* Station Alias Status */

/* PHYSICAL_RW_OFFSET Register bit definitions */
#define R_ESC_PHYSICAL_RW_OFFSET_RWOFFSET_SHIFT   (0)  /* Offset between Read and Write Addresses */
#define R_ESC_PHYSICAL_RW_OFFSET_RWOFFSET_MASK    0xffff

/* ESC_DL_STATUS Register bit definitions */
#define R_ESC_ESC_DL_STATUS_PDIOPE                (1 << 0)  /* PDI/EEPROM Load State Indication */

#define R_ESC_ESC_DL_STATUS_PDIWDST               (1 << 1)  /* PDI Watchdog Timer Status */

#define R_ESC_ESC_DL_STATUS_ENHLINKD              (1 << 2)  /* Enhanced Link Detection Indication */

#define R_ESC_ESC_DL_STATUS_PHYP0                 (1 << 4)  /* Port 0 Link State Indication */

#define R_ESC_ESC_DL_STATUS_PHYP1                 (1 << 5)  /* Port 1 Link State Indication */

#define R_ESC_ESC_DL_STATUS_PHYP2                 (1 << 6)  /* Port 2 Link State Indication */

#define R_ESC_ESC_DL_STATUS_PHYP3                 (1 << 7)  /* Port 3 Link State Indication */

#define R_ESC_ESC_DL_STATUS_LP0                   (1 << 8)  /* Loop Port 0 State Indication */

#define R_ESC_ESC_DL_STATUS_COMP0                 (1 << 9)  /* Port 0 Communication State Indication */

#define R_ESC_ESC_DL_STATUS_LP1                   (1 << 10)  /* Loop Port 1 State Indication */

#define R_ESC_ESC_DL_STATUS_COMP1                 (1 << 11)  /* Port 1 Communication State Indication */

#define R_ESC_ESC_DL_STATUS_LP2                   (1 << 12)  /* Loop Port 2 State Indication */

#define R_ESC_ESC_DL_STATUS_COMP2                 (1 << 13)  /* Port 2 Communication State Indication */

#define R_ESC_ESC_DL_STATUS_LP3                   (1 << 14)  /* Loop Port 3 State Indication */

#define R_ESC_ESC_DL_STATUS_COMP3                 (1 << 15)  /* Port 3 Communication State Indication */

/* AL_CONTROL Register bit definitions */
#define R_ESC_AL_CONTROL_INISTATE_SHIFT           (0)  /* Change the state transition of the device state machine. */
#define R_ESC_AL_CONTROL_INISTATE_MASK            0xf
#  define R_ESC_AL_CONTROL_INISTATE_0X1                   (0 << R_ESC_AL_CONTROL_INISTATE_SHIFT)  /* Initial state request */
#  define R_ESC_AL_CONTROL_INISTATE_0X2                   (0 << R_ESC_AL_CONTROL_INISTATE_SHIFT)  /* Pre-operational state request */
#  define R_ESC_AL_CONTROL_INISTATE_0X3                   (0 << R_ESC_AL_CONTROL_INISTATE_SHIFT)  /* Bootstrap state request */
#  define R_ESC_AL_CONTROL_INISTATE_0X4                   (0 << R_ESC_AL_CONTROL_INISTATE_SHIFT)  /* Safe-operational state request */
#  define R_ESC_AL_CONTROL_INISTATE_0X8                   (0 << R_ESC_AL_CONTROL_INISTATE_SHIFT)  /* Operational state request */

#define R_ESC_AL_CONTROL_ERRINDACK                (1 << 4)  /* Error Indication Acknowledge (Response) */

#define R_ESC_AL_CONTROL_DEVICEID                 (1 << 5)  /* Device ID Request */

/* AL_STATUS Register bit definitions */
#define R_ESC_AL_STATUS_ACTSTATE_SHIFT            (0)  /* State Machine State Indication */
#define R_ESC_AL_STATUS_ACTSTATE_MASK             0xf
#  define R_ESC_AL_STATUS_ACTSTATE_0X1                    (0 << R_ESC_AL_STATUS_ACTSTATE_SHIFT)  /* Initial state */
#  define R_ESC_AL_STATUS_ACTSTATE_0X2                    (0 << R_ESC_AL_STATUS_ACTSTATE_SHIFT)  /* Pre-operational state */
#  define R_ESC_AL_STATUS_ACTSTATE_0X3                    (0 << R_ESC_AL_STATUS_ACTSTATE_SHIFT)  /* Request bootstrap state */
#  define R_ESC_AL_STATUS_ACTSTATE_0X4                    (0 << R_ESC_AL_STATUS_ACTSTATE_SHIFT)  /* Safe-operational state */
#  define R_ESC_AL_STATUS_ACTSTATE_0X8                    (0 << R_ESC_AL_STATUS_ACTSTATE_SHIFT)  /* Operational state */

#define R_ESC_AL_STATUS_ERR                       (1 << 4)  /* Error State Indication */

#define R_ESC_AL_STATUS_DEVICEID                  (1 << 5)  /* Device ID Load State Indication */

/* AL_STATUS_CODE Register bit definitions */
#define R_ESC_AL_STATUS_CODE_STATUSCODE_SHIFT     (0)  /* AL status code */
#define R_ESC_AL_STATUS_CODE_STATUSCODE_MASK      0xffff

/* RUN_LED_OVERRIDE Register bit definitions */
#define R_ESC_RUN_LED_OVERRIDE_LEDCODE_SHIFT      (0)  /* LED Code Indication (FSM state: Bits [3:0] of the AL Status register, AL_STATUS) */
#define R_ESC_RUN_LED_OVERRIDE_LEDCODE_MASK       0xf
#  define R_ESC_RUN_LED_OVERRIDE_LEDCODE_0X0              (0 << R_ESC_RUN_LED_OVERRIDE_LEDCODE_SHIFT)  /* Off (FSM: 1-Init) */
#  define R_ESC_RUN_LED_OVERRIDE_LEDCODE_0XD              (0 << R_ESC_RUN_LED_OVERRIDE_LEDCODE_SHIFT)  /* Blinking (FSM: 2-PreOp) */
#  define R_ESC_RUN_LED_OVERRIDE_LEDCODE_0XE              (0 << R_ESC_RUN_LED_OVERRIDE_LEDCODE_SHIFT)  /* Flickering (FSM: 3-Bootstrap) */
#  define R_ESC_RUN_LED_OVERRIDE_LEDCODE_0XF              (0 << R_ESC_RUN_LED_OVERRIDE_LEDCODE_SHIFT)  /* On (FSM: 8-Op) */

#define R_ESC_RUN_LED_OVERRIDE_OVERRIDEEN         (1 << 4)  /* Override Setting */

/* ERR_LED_OVERRIDE Register bit definitions */
#define R_ESC_ERR_LED_OVERRIDE_LEDCODE_SHIFT      (0)  /* LED Code Indication */
#define R_ESC_ERR_LED_OVERRIDE_LEDCODE_MASK       0xf
#  define R_ESC_ERR_LED_OVERRIDE_LEDCODE_0X0              (0 << R_ESC_ERR_LED_OVERRIDE_LEDCODE_SHIFT)  /* Off */
#  define R_ESC_ERR_LED_OVERRIDE_LEDCODE_0XD              (0 << R_ESC_ERR_LED_OVERRIDE_LEDCODE_SHIFT)  /* Blinking */
#  define R_ESC_ERR_LED_OVERRIDE_LEDCODE_0XE              (0 << R_ESC_ERR_LED_OVERRIDE_LEDCODE_SHIFT)  /* Flickering */
#  define R_ESC_ERR_LED_OVERRIDE_LEDCODE_0XF              (0 << R_ESC_ERR_LED_OVERRIDE_LEDCODE_SHIFT)  /* On */

#define R_ESC_ERR_LED_OVERRIDE_OVERRIDEEN         (1 << 4)  /* Override Setting */

/* PDI_CONTROL Register bit definitions */
#define R_ESC_PDI_CONTROL_PDI_SHIFT               (0)  /* Process Data Interface. In this LSI, the following value is indicated. */
#define R_ESC_PDI_CONTROL_PDI_MASK                0xff
#  define R_ESC_PDI_CONTROL_PDI_0X80                      (0 << R_ESC_PDI_CONTROL_PDI_SHIFT)  /* On-chip bus */

/* ESC_CONFIG Register bit definitions */
#define R_ESC_ESC_CONFIG_DEVEMU                   (1 << 0)  /* Device emulation (control of AL status) */

#define R_ESC_ESC_CONFIG_ENLALLP                  (1 << 1)  /* Sets enhanced link detection for all ports */

#define R_ESC_ESC_CONFIG_DCSYNC                   (1 << 2)  /* Sets the SYNC output unit for distributed clocks (fixed to 1 in this LSI) */

#define R_ESC_ESC_CONFIG_DCLATCH                  (1 << 3)  /* Sets the latch input unit for distributed clocks */

#define R_ESC_ESC_CONFIG_ENLP0                    (1 << 4)  /* Port 0 Enhanced Link Detection Setting */

#define R_ESC_ESC_CONFIG_ENLP1                    (1 << 5)  /* Port 1 Enhanced Link Detection Setting */

#define R_ESC_ESC_CONFIG_ENLP2                    (1 << 6)  /* Port 2 Enhanced Link Detection Setting */

#define R_ESC_ESC_CONFIG_ENLP3                    (1 << 7)  /* Port 3 Enhanced Link Detection Setting */

/* PDI_CONFIG Register bit definitions */
#define R_ESC_PDI_CONFIG_ONCHIPBUSCLK_SHIFT       (0)  /* On-Chip Bus Clock Indication */
#define R_ESC_PDI_CONFIG_ONCHIPBUSCLK_MASK        0x1f

#define R_ESC_PDI_CONFIG_ONCHIPBUS_SHIFT          (5)  /* On-Chip Bus Type Indication */
#define R_ESC_PDI_CONFIG_ONCHIPBUS_MASK           0xe0

/* SYNC_LATCH_CONFIG Register bit definitions */
#define R_ESC_SYNC_LATCH_CONFIG_SYNC0OUT_SHIFT    (0)  /* SYNC0 Output Driver and Polarity Indication */
#define R_ESC_SYNC_LATCH_CONFIG_SYNC0OUT_MASK     0x3

#define R_ESC_SYNC_LATCH_CONFIG_SYNCLAT0          (1 << 2)  /* SYNC0/LATCH0 Indication */

#define R_ESC_SYNC_LATCH_CONFIG_SYNC0MAP          (1 << 3)  /* SYNC0 State Mapping Indication */

#define R_ESC_SYNC_LATCH_CONFIG_SYNC1OUT_SHIFT    (4)  /* SYNC1 Output Driver and Polarity Indication */
#define R_ESC_SYNC_LATCH_CONFIG_SYNC1OUT_MASK     0x30

#define R_ESC_SYNC_LATCH_CONFIG_SYNCLAT1          (1 << 6)  /* SYNC1/LATCH1 Indication */

#define R_ESC_SYNC_LATCH_CONFIG_SYNC1MAP          (1 << 7)  /* SYNC1 State Mapping Indication */

/* EXT_PDI_CONFIG Register bit definitions */
#define R_ESC_EXT_PDI_CONFIG_DATABUSWID_SHIFT     (0)  /* PDI Data Bus Width Indication */
#define R_ESC_EXT_PDI_CONFIG_DATABUSWID_MASK      0x3
#  define R_ESC_EXT_PDI_CONFIG_DATABUSWID_00              (0 << R_ESC_EXT_PDI_CONFIG_DATABUSWID_SHIFT)  /* 4 bytes */
#  define R_ESC_EXT_PDI_CONFIG_DATABUSWID_01              (1 << R_ESC_EXT_PDI_CONFIG_DATABUSWID_SHIFT)  /* 1 byte */
#  define R_ESC_EXT_PDI_CONFIG_DATABUSWID_10              (2 << R_ESC_EXT_PDI_CONFIG_DATABUSWID_SHIFT)  /* 2 bytes */
#  define R_ESC_EXT_PDI_CONFIG_DATABUSWID_11              (3 << R_ESC_EXT_PDI_CONFIG_DATABUSWID_SHIFT)  /* Reserved */

/* ECAT_EVENT_MASK Register bit definitions */
#define R_ESC_ECAT_EVENT_MASK_ECATEVMASK_SHIFT    (0)  /* Event Request Mask Setting */
#define R_ESC_ECAT_EVENT_MASK_ECATEVMASK_MASK     0xffff
#  define R_ESC_ECAT_EVENT_MASK_ECATEVMASK_0              (0 << R_ESC_ECAT_EVENT_MASK_ECATEVMASK_SHIFT)  /* The corresponding bit of the ECAT Event Request register (ECAT_EVENT_REQ at 0x0210) is not mapped */
#  define R_ESC_ECAT_EVENT_MASK_ECATEVMASK_1              (1 << R_ESC_ECAT_EVENT_MASK_ECATEVMASK_SHIFT)  /* The corresponding bit of the ECAT Event Request register is mapped */

/* AL_EVENT_MASK Register bit definitions */
#define R_ESC_AL_EVENT_MASK_ALEVMASK_SHIFT        (0)  /* Event Request Mask Setting */
#define R_ESC_AL_EVENT_MASK_ALEVMASK_MASK         0xffffffff
#  define R_ESC_AL_EVENT_MASK_ALEVMASK_0                  (0 << R_ESC_AL_EVENT_MASK_ALEVMASK_SHIFT)  /* The corresponding bit of the AL Event Request register (AL_EVENT_REQ at 0x0220) is not mapped */
#  define R_ESC_AL_EVENT_MASK_ALEVMASK_1                  (1 << R_ESC_AL_EVENT_MASK_ALEVMASK_SHIFT)  /* The corresponding bit of the AL Event Request register is mapped */

/* ECAT_EVENT_REQ Register bit definitions */
#define R_ESC_ECAT_EVENT_REQ_DCLATCH              (1 << 0)  /* DC Latch Event State Indication */

#define R_ESC_ECAT_EVENT_REQ_DLSTA                (1 << 2)  /* DL Status Event State Indication */

#define R_ESC_ECAT_EVENT_REQ_ALSTA                (1 << 3)  /* AL Status Event State Indication */

#define R_ESC_ECAT_EVENT_REQ_SMSTA0               (1 << 4)  /* Mirror value of SyncManager 0 Status Indication */

#define R_ESC_ECAT_EVENT_REQ_SMSTA1               (1 << 5)  /* Mirror value of SyncManager 1 Status Indication */

#define R_ESC_ECAT_EVENT_REQ_SMSTA2               (1 << 6)  /* Mirror value of SyncManager 2 Status Indication */

#define R_ESC_ECAT_EVENT_REQ_SMSTA3               (1 << 7)  /* Mirror value of SyncManager 3 Status Indication */

#define R_ESC_ECAT_EVENT_REQ_SMSTA4               (1 << 8)  /* Mirror value of SyncManager 4 Status Indication */

#define R_ESC_ECAT_EVENT_REQ_SMSTA5               (1 << 9)  /* Mirror value of SyncManager 5 Status Indication */

#define R_ESC_ECAT_EVENT_REQ_SMSTA6               (1 << 10)  /* Mirror value of SyncManager 6 Status Indication */

#define R_ESC_ECAT_EVENT_REQ_SMSTA7               (1 << 11)  /* Mirror value of SyncManager 7 Status Indication */

/* AL_EVENT_REQ Register bit definitions */
#define R_ESC_AL_EVENT_REQ_ALCTRL                 (1 << 0)  /* AL Control Event State Indication */

#define R_ESC_AL_EVENT_REQ_DCLATCH                (1 << 1)  /* DC Latch Event State Indication */

#define R_ESC_AL_EVENT_REQ_DCSYNC0STA             (1 << 2)  /* DC SYNC0 State Indication */

#define R_ESC_AL_EVENT_REQ_DCSYNC1STA             (1 << 3)  /* DC SYNC1 State Indication */

#define R_ESC_AL_EVENT_REQ_SYNCACT                (1 << 4)  /* SyncManager Activation Indication */

#define R_ESC_AL_EVENT_REQ_WDPD                   (1 << 6)  /* Watchdog Process Data Indication */

#define R_ESC_AL_EVENT_REQ_SMINT0                 (1 << 8)  /* SyncManager 0 interrupt (bit 0 or 1 of the SyncManager status register (0x0805)) */

#define R_ESC_AL_EVENT_REQ_SMINT1                 (1 << 9)  /* SyncManager 1 interrupt (bit 0 or 1 of the SyncManager status register (0x080D)) */

#define R_ESC_AL_EVENT_REQ_SMINT2                 (1 << 10)  /* SyncManager 2 interrupt (bit 0 or 1 of the SyncManager status register (0x0815)) */

#define R_ESC_AL_EVENT_REQ_SMINT3                 (1 << 11)  /* SyncManager 3 interrupt (bit 0 or 1 of the SyncManager status register (0x081D)) */

#define R_ESC_AL_EVENT_REQ_SMINT4                 (1 << 12)  /* SyncManager 4 interrupt (bit 0 or 1 of the SyncManager status register (0x0825)) */

#define R_ESC_AL_EVENT_REQ_SMINT5                 (1 << 13)  /* SyncManager 5 interrupt (bit 0 or 1 of the SyncManager status register (0x082D)) */

#define R_ESC_AL_EVENT_REQ_SMINT6                 (1 << 14)  /* SyncManager 6 interrupt (bit 0 or 1 of the SyncManager status register (0x0835)) */

#define R_ESC_AL_EVENT_REQ_SMINT7                 (1 << 15)  /* SyncManager 7 interrupt (bit 0 or 1 of the SyncManager status register (0x083D)) */

/* RX_ERR_COUNT Register bit definitions */
#define R_ESC_RX_ERR_COUNT_INVFRMCNT_SHIFT        (0)  /* Invalid Frame Counter Value Indication */
#define R_ESC_RX_ERR_COUNT_INVFRMCNT_MASK         0xff

#define R_ESC_RX_ERR_COUNT_RXERRCNT_SHIFT         (8)  /* RX Frame Error Counter Value Indication */
#define R_ESC_RX_ERR_COUNT_RXERRCNT_MASK          0xff00

/* FWD_RX_ERR_COUNT Register bit definitions */
#define R_ESC_FWD_RX_ERR_COUNT_FWDERRCNT_SHIFT    (0)  /* Forwarded Error Counter Value Indication */
#define R_ESC_FWD_RX_ERR_COUNT_FWDERRCNT_MASK     0xff

/* ECAT_PROC_ERR_COUNT Register bit definitions */
#define R_ESC_ECAT_PROC_ERR_COUNT_EPUERRCNT_SHIFT (0)  /* Processing Unit Error Counter Value Indication */
#define R_ESC_ECAT_PROC_ERR_COUNT_EPUERRCNT_MASK  0xff

/* PDI_ERR_COUNT Register bit definitions */
#define R_ESC_PDI_ERR_COUNT_PDIERRCNT_SHIFT       (0)  /* PDI Error Counter Value Indication */
#define R_ESC_PDI_ERR_COUNT_PDIERRCNT_MASK        0xff

/* LOST_LINK_COUNT Register bit definitions */
#define R_ESC_LOST_LINK_COUNT_LOSTLINKCNT_SHIFT   (0)  /* Lost Link Counter Value Indication */
#define R_ESC_LOST_LINK_COUNT_LOSTLINKCNT_MASK    0xff

/* WD_DIVIDE Register bit definitions */
#define R_ESC_WD_DIVIDE_WDDIV_SHIFT               (0)  /* Watchdog Clock Frequency Divisor Setting */
#define R_ESC_WD_DIVIDE_WDDIV_MASK                0xffff

/* WDT_PDI Register bit definitions */
#define R_ESC_WDT_PDI_WDTIMPDI_SHIFT              (0)  /* Watchdog Overflow Time Setting */
#define R_ESC_WDT_PDI_WDTIMPDI_MASK               0xffff

/* WDT_DATA Register bit definitions */
#define R_ESC_WDT_DATA_WDTIMPD_SHIFT              (0)  /* Watchdog Overflow Time Setting */
#define R_ESC_WDT_DATA_WDTIMPD_MASK               0xffff

/* WDS_DATA Register bit definitions */
#define R_ESC_WDS_DATA_WDSTAPD                    (1 << 0)  /* Watchdog State Indication */

/* WDC_DATA Register bit definitions */
#define R_ESC_WDC_DATA_WDCNTPD_SHIFT              (0)  /* Watchdog Counter Value Indication */
#define R_ESC_WDC_DATA_WDCNTPD_MASK               0xff

/* WDC_PDI Register bit definitions */
#define R_ESC_WDC_PDI_WDCNTPDI_SHIFT              (0)  /* Watchdog Counter Value Indication */
#define R_ESC_WDC_PDI_WDCNTPDI_MASK               0xff

/* EEP_CONF Register bit definitions */
#define R_ESC_EEP_CONF_CTRLPDI                    (1 << 0)  /* PDI EEPROM Control */

#define R_ESC_EEP_CONF_FORCEECAT                  (1 << 1)  /* EEPROM Access Right Change */

/* EEP_STATE Register bit definitions */
#define R_ESC_EEP_STATE_PDIACCESS                 (1 << 0)  /* EEPROM Access Right Setting */

/* EEP_CONT_STAT Register bit definitions */
#define R_ESC_EEP_CONT_STAT_ECATWREN              (1 << 0)  /* ECAT Write Enable */

#define R_ESC_EEP_CONT_STAT_READBYTE              (1 << 6)  /* EEPROM Read Byte Indication */

#define R_ESC_EEP_CONT_STAT_PROMSIZE              (1 << 7)  /* EEPROM Algorithm Indication */

#define R_ESC_EEP_CONT_STAT_COMMAND_SHIFT         (8)  /* Command */
#define R_ESC_EEP_CONT_STAT_COMMAND_MASK          0x700
#  define R_ESC_EEP_CONT_STAT_COMMAND_000                 (0 << R_ESC_EEP_CONT_STAT_COMMAND_SHIFT)  /* No command/EEPROM idle (clear error bits) */
#  define R_ESC_EEP_CONT_STAT_COMMAND_001                 (1 << R_ESC_EEP_CONT_STAT_COMMAND_SHIFT)  /* Read */
#  define R_ESC_EEP_CONT_STAT_COMMAND_010                 (2 << R_ESC_EEP_CONT_STAT_COMMAND_SHIFT)  /* Write */
#  define R_ESC_EEP_CONT_STAT_COMMAND_100                 (4 << R_ESC_EEP_CONT_STAT_COMMAND_SHIFT)  /* Reload */

#define R_ESC_EEP_CONT_STAT_CKSUMERR              (1 << 11)  /* Checksum Error Indication */

#define R_ESC_EEP_CONT_STAT_LOADSTA               (1 << 12)  /* EEPROM Loading Status Indication */

#define R_ESC_EEP_CONT_STAT_ACKCMDERR             (1 << 13)  /* Acknowledge/Command Error Indication */

#define R_ESC_EEP_CONT_STAT_WRENERR               (1 << 14)  /* Write Enable Error Indication */

#define R_ESC_EEP_CONT_STAT_BUSY                  (1 << 15)  /* EEPROM Interface State Indication */

/* EEP_ADR Register bit definitions */
#define R_ESC_EEP_ADR_ADDRESS_SHIFT               (0)  /* EEPROM Address Setting */
#define R_ESC_EEP_ADR_ADDRESS_MASK                0xffffffff

/* EEP_DATA Register bit definitions */
#define R_ESC_EEP_DATA_LODATA_SHIFT               (0)  /* Data to be written to the EEPROM or data read from the EEPROM (lower 2 bytes) */
#define R_ESC_EEP_DATA_LODATA_MASK                0xffff

#define R_ESC_EEP_DATA_HIDATA_SHIFT               (16)  /* Data read from the EEPROM (upper 2 bytes) */
#define R_ESC_EEP_DATA_HIDATA_MASK                0xffff0000

/* MII_CONT_STAT Register bit definitions */
#define R_ESC_MII_CONT_STAT_WREN                  (1 << 0)  /* Write Enable */

#define R_ESC_MII_CONT_STAT_PDICTRL               (1 << 1)  /* PDI Control Indication */

#define R_ESC_MII_CONT_STAT_MILINK                (1 << 2)  /* MI Link Detection */

#define R_ESC_MII_CONT_STAT_PHYOFFSET_SHIFT       (3)  /* PHY Address Offset Indication */
#define R_ESC_MII_CONT_STAT_PHYOFFSET_MASK        0xf8

#define R_ESC_MII_CONT_STAT_COMMAND_SHIFT         (8)  /* Command */
#define R_ESC_MII_CONT_STAT_COMMAND_MASK          0x300
#  define R_ESC_MII_CONT_STAT_COMMAND_00                  (0 << R_ESC_MII_CONT_STAT_COMMAND_SHIFT)  /* No command/MI idle (clear error bits) */
#  define R_ESC_MII_CONT_STAT_COMMAND_01                  (1 << R_ESC_MII_CONT_STAT_COMMAND_SHIFT)  /* Read */
#  define R_ESC_MII_CONT_STAT_COMMAND_10                  (2 << R_ESC_MII_CONT_STAT_COMMAND_SHIFT)  /* Write */

#define R_ESC_MII_CONT_STAT_READERR               (1 << 13)  /* Read Error Indication */

#define R_ESC_MII_CONT_STAT_CMDERR                (1 << 14)  /* Command Error Indication */

#define R_ESC_MII_CONT_STAT_BUSY                  (1 << 15)  /* MII Management State Indication */

/* PHY_ADR Register bit definitions */
#define R_ESC_PHY_ADR_PHYADDR_SHIFT               (0)  /* PHY Address Setting */
#define R_ESC_PHY_ADR_PHYADDR_MASK                0x1f

/* PHY_REG_ADR Register bit definitions */
#define R_ESC_PHY_REG_ADR_PHYREGADDR_SHIFT        (0)  /* Address of PHY register */
#define R_ESC_PHY_REG_ADR_PHYREGADDR_MASK         0x1f

/* PHY_DATA Register bit definitions */
#define R_ESC_PHY_DATA_PHYREGDATA_SHIFT           (0)  /* PHY Register Data Indication/Setting */
#define R_ESC_PHY_DATA_PHYREGDATA_MASK            0xffff

/* MII_ECAT_ACS_STAT Register bit definitions */
#define R_ESC_MII_ECAT_ACS_STAT_ACSMII            (1 << 0)  /* MII Management Interface Access Right Setting */

/* MII_PDI_ACS_STAT Register bit definitions */
#define R_ESC_MII_PDI_ACS_STAT_ACSMII             (1 << 0)  /* Right of access to the MII management interface */

#define R_ESC_MII_PDI_ACS_STAT_FORPDI             (1 << 1)  /* Forced change of access by the PDI (forced change of bit 0) */

/* FMMU_L_START_ADR Register bit definitions */
#define R_ESC_FMMU_L_START_ADR_LSTAADR_SHIFT      (0)  /* Logical Start Address Setting */
#define R_ESC_FMMU_L_START_ADR_LSTAADR_MASK       0xffffffff

/* FMMU_LEN Register bit definitions */
#define R_ESC_FMMU_LEN_FMMULEN_SHIFT              (0)  /* Area Size Specification */
#define R_ESC_FMMU_LEN_FMMULEN_MASK               0xffff

/* FMMU_L_START_BIT Register bit definitions */
#define R_ESC_FMMU_L_START_BIT_LSTABIT_SHIFT      (0)  /* Start Bit Setting */
#define R_ESC_FMMU_L_START_BIT_LSTABIT_MASK       0x7

/* FMMU_L_STOP_BIT Register bit definitions */
#define R_ESC_FMMU_L_STOP_BIT_LSTPBIT_SHIFT       (0)  /* Last Bit Setting */
#define R_ESC_FMMU_L_STOP_BIT_LSTPBIT_MASK        0x7

/* FMMU_P_START_ADR Register bit definitions */
#define R_ESC_FMMU_P_START_ADR_PHYSTAADR_SHIFT    (0)  /* Physical Start Address Setting */
#define R_ESC_FMMU_P_START_ADR_PHYSTAADR_MASK     0xffff

/* FMMU_P_START_BIT Register bit definitions */
#define R_ESC_FMMU_P_START_BIT_PHYSTABIT_SHIFT    (0)  /* Physical Start Bit Setting */
#define R_ESC_FMMU_P_START_BIT_PHYSTABIT_MASK     0x7

/* FMMU_TYPE Register bit definitions */
#define R_ESC_FMMU_TYPE_READ                      (1 << 0)  /* Read Access Mapping Setting */

#define R_ESC_FMMU_TYPE_WRITE                     (1 << 1)  /* Write Access Mapping Setting */

/* FMMU_ACT Register bit definitions */
#define R_ESC_FMMU_ACT_ACTIVATE                   (1 << 0)  /* FMMU Enable/Disable */

/* SM_P_START_ADR Register bit definitions */
#define R_ESC_SM_P_START_ADR_SMSTAADDR_SHIFT      (0)  /* Physical Start Address Setting */
#define R_ESC_SM_P_START_ADR_SMSTAADDR_MASK       0xffff

/* SM_LEN Register bit definitions */
#define R_ESC_SM_LEN_SMLEN_SHIFT                  (0)  /* Area Size Setting */
#define R_ESC_SM_LEN_SMLEN_MASK                   0xffff

/* SM_CONTROL Register bit definitions */
#define R_ESC_SM_CONTROL_OPEMODE_SHIFT            (0)  /* Operating Mode Setting */
#define R_ESC_SM_CONTROL_OPEMODE_MASK             0x3
#  define R_ESC_SM_CONTROL_OPEMODE_00                     (0 << R_ESC_SM_CONTROL_OPEMODE_SHIFT)  /* Buffer mode (3-buffer mode) */
#  define R_ESC_SM_CONTROL_OPEMODE_10                     (2 << R_ESC_SM_CONTROL_OPEMODE_SHIFT)  /* Mailbox mode (single buffer mode) */

#define R_ESC_SM_CONTROL_DIR_SHIFT                (2)  /* Transfer Direction Setting */
#define R_ESC_SM_CONTROL_DIR_MASK                 0xc
#  define R_ESC_SM_CONTROL_DIR_00                         (0 << R_ESC_SM_CONTROL_DIR_SHIFT)  /* Read (ECAT: read access; PDI: write access) */
#  define R_ESC_SM_CONTROL_DIR_01                         (1 << R_ESC_SM_CONTROL_DIR_SHIFT)  /* Write (ECAT: write access; PDI: read access) */

#define R_ESC_SM_CONTROL_IRQECAT                  (1 << 4)  /* ECAT Event Interrupt Setting */

#define R_ESC_SM_CONTROL_IRQPDI                   (1 << 5)  /* AL Event Interrupt Setting */

#define R_ESC_SM_CONTROL_WDTRGEN                  (1 << 6)  /* Watchdog Trigger Setting */

/* SM_STATUS Register bit definitions */
#define R_ESC_SM_STATUS_INTWR                     (1 << 0)  /* Write Complete Interrupt State Indication */

#define R_ESC_SM_STATUS_INTRD                     (1 << 1)  /* Read Complete Interrupt State Indication */

#define R_ESC_SM_STATUS_MAILBOX                   (1 << 3)  /* Mailbox Status Indication */

#define R_ESC_SM_STATUS_BUFFERED_SHIFT            (4)  /* Buffer Status Indication */
#define R_ESC_SM_STATUS_BUFFERED_MASK             0x30
#  define R_ESC_SM_STATUS_BUFFERED_00                     (0 << R_ESC_SM_STATUS_BUFFERED_SHIFT)  /* 1st buffer */
#  define R_ESC_SM_STATUS_BUFFERED_01                     (1 << R_ESC_SM_STATUS_BUFFERED_SHIFT)  /* 2nd buffer */
#  define R_ESC_SM_STATUS_BUFFERED_10                     (2 << R_ESC_SM_STATUS_BUFFERED_SHIFT)  /* 3rd buffer */
#  define R_ESC_SM_STATUS_BUFFERED_11                     (3 << R_ESC_SM_STATUS_BUFFERED_SHIFT)  /* No buffer written */

#define R_ESC_SM_STATUS_RDBUF                     (1 << 6)  /* Read State Indication */

#define R_ESC_SM_STATUS_WRBUF                     (1 << 7)  /* Write State Indication */

/* SM_ACT Register bit definitions */
#define R_ESC_SM_ACT_SMEN                         (1 << 0)  /* SyncManager Enable/Disable */

#define R_ESC_SM_ACT_REPEATREQ                    (1 << 1)  /* Repeat Request */

#define R_ESC_SM_ACT_LATCHECAT                    (1 << 6)  /* ECAT Latch Event Specification */

#define R_ESC_SM_ACT_LATCHPDI                     (1 << 7)  /* PDI Latch Event Specification */

/* SM_PDI_CONT Register bit definitions */
#define R_ESC_SM_PDI_CONT_DEACTIVE                (1 << 0)  /* SyncManager Operation Indication/Setting */

#define R_ESC_SM_PDI_CONT_REPEATACK               (1 << 1)  /* Repeat Acknowledge */

/* DC_RCV_TIME_PORT Register bit definitions */
#define R_ESC_DC_RCV_TIME_PORT_RCVTIME0_SHIFT     (0)  /* Receive Time Indication/Latch */
#define R_ESC_DC_RCV_TIME_PORT_RCVTIME0_MASK      0xffffffff

/* DC_RCV_TIME_PORT Register bit definitions */
#define R_ESC_DC_RCV_TIME_PORT_RCVTIME1_SHIFT     (0)  /* Receive Time Indication */
#define R_ESC_DC_RCV_TIME_PORT_RCVTIME1_MASK      0xffffffff

/* DC_RCV_TIME_PORT Register bit definitions */
#define R_ESC_DC_RCV_TIME_PORT_RCVTIME2_SHIFT     (0)  /* Receive Time Indication */
#define R_ESC_DC_RCV_TIME_PORT_RCVTIME2_MASK      0xffffffff

/* DC_SYS_TIME_L Register bit definitions */
#define R_ESC_DC_SYS_TIME_L_SYSTIME_SHIFT         (0)  /* System Time Indication */
#define R_ESC_DC_SYS_TIME_L_SYSTIME_MASK          0xffffffff

/* DC_SYS_TIME_H Register bit definitions */
#define R_ESC_DC_SYS_TIME_H_SYSTIME_SHIFT         (0)  /* System Time Indication */
#define R_ESC_DC_SYS_TIME_H_SYSTIME_MASK          0xffffffff

/* DC_RCV_TIME_UNIT_L Register bit definitions */
#define R_ESC_DC_RCV_TIME_UNIT_L_RCVTIMEEPU_SHIFT (0)  /* Receive Time Indication */
#define R_ESC_DC_RCV_TIME_UNIT_L_RCVTIMEEPU_MASK  0xffffffff

/* DC_RCV_TIME_UNIT_H Register bit definitions */
#define R_ESC_DC_RCV_TIME_UNIT_H_RCVTIMEEPU_SHIFT (0)  /* Receive Time Indication */
#define R_ESC_DC_RCV_TIME_UNIT_H_RCVTIMEEPU_MASK  0xffffffff

/* DC_SYS_TIME_OFFSET_L Register bit definitions */
#define R_ESC_DC_SYS_TIME_OFFSET_L_SYSTIMOFST_SHIFT (0)  /* System Time and Local Time Difference Indication */
#define R_ESC_DC_SYS_TIME_OFFSET_L_SYSTIMOFST_MASK 0xffffffff

/* DC_SYS_TIME_OFFSET_H Register bit definitions */
#define R_ESC_DC_SYS_TIME_OFFSET_H_SYSTIMOFST_SHIFT (0)  /* System Time and Local Time Difference Indication */
#define R_ESC_DC_SYS_TIME_OFFSET_H_SYSTIMOFST_MASK 0xffffffff

/* DC_SYS_TIME_DELAY Register bit definitions */
#define R_ESC_DC_SYS_TIME_DELAY_SYSTIMDLY_SHIFT   (0)  /* Propagation Delay Indication */
#define R_ESC_DC_SYS_TIME_DELAY_SYSTIMDLY_MASK    0xffffffff

/* DC_SYS_TIME_DIFF Register bit definitions */
#define R_ESC_DC_SYS_TIME_DIFF_DIFF_SHIFT         (0)  /* System Time Mean Difference Indication */
#define R_ESC_DC_SYS_TIME_DIFF_DIFF_MASK          0x7fffffff

#define R_ESC_DC_SYS_TIME_DIFF_LCP                (1 << 31)  /* System Time Greater/Less Indication */

/* DC_SPEED_COUNT_START Register bit definitions */
#define R_ESC_DC_SPEED_COUNT_START_SPDCNTSTRT_SHIFT (0)  /* Drift Correction Bandwidth Setting */
#define R_ESC_DC_SPEED_COUNT_START_SPDCNTSTRT_MASK 0x7fff

/* DC_SPEED_COUNT_DIFF Register bit definitions */
#define R_ESC_DC_SPEED_COUNT_DIFF_SPDCNTDIFF_SHIFT (0)  /* Clock Period Deviation Indication */
#define R_ESC_DC_SPEED_COUNT_DIFF_SPDCNTDIFF_MASK 0xffff

/* DC_SYS_TIME_DIFF_FIL_DEPTH Register bit definitions */
#define R_ESC_DC_SYS_TIME_DIFF_FIL_DEPTH_SYSTIMDEP_SHIFT (0)  /* Filter Depth Setting */
#define R_ESC_DC_SYS_TIME_DIFF_FIL_DEPTH_SYSTIMDEP_MASK 0xf

/* DC_SPEED_COUNT_FIL_DEPTH Register bit definitions */
#define R_ESC_DC_SPEED_COUNT_FIL_DEPTH_CLKPERDEP_SHIFT (0)  /* Filter Depth Setting */
#define R_ESC_DC_SPEED_COUNT_FIL_DEPTH_CLKPERDEP_MASK 0xf

/* DC_CYC_CONT Register bit definitions */
#define R_ESC_DC_CYC_CONT_SYNCOUT                 (1 << 0)  /* SYNC Output Unit Control Setting */

#define R_ESC_DC_CYC_CONT_LATCH0                  (1 << 4)  /* Latch Input Unit 0 Control Setting */

#define R_ESC_DC_CYC_CONT_LATCH1                  (1 << 5)  /* Latch Input Unit 1 Control Setting */

/* DC_ACT Register bit definitions */
#define R_ESC_DC_ACT_SYNCACT                      (1 << 0)  /* Sync Output Unit Activation */

#define R_ESC_DC_ACT_SYNC0                        (1 << 1)  /* SYNC0 Output Setting */

#define R_ESC_DC_ACT_SYNC1                        (1 << 2)  /* SYNC1 Output Setting */

#define R_ESC_DC_ACT_AUTOACT                      (1 << 3)  /* SYNC Output Unit Activation */

#define R_ESC_DC_ACT_EXTSTARTTIME                 (1 << 4)  /* Start Time Cyclic Operation Extension */

#define R_ESC_DC_ACT_STARTTIME                    (1 << 5)  /* Start Time Plausibility */

#define R_ESC_DC_ACT_NEARFUTURE                   (1 << 6)  /* Near Future Range Setting */

#define R_ESC_DC_ACT_DBGPULSE                     (1 << 7)  /* Debug Pulse Setting */

/* DC_PULSE_LEN Register bit definitions */
#define R_ESC_DC_PULSE_LEN_PULSELEN_SHIFT         (0)  /* SYNC Signal Pulse Length Indication */
#define R_ESC_DC_PULSE_LEN_PULSELEN_MASK          0xffff
#  define R_ESC_DC_PULSE_LEN_PULSELEN_0                   (0 << R_ESC_DC_PULSE_LEN_PULSELEN_SHIFT)  /* Acknowledge mode. In this mode, SYNC signal is cleared by reading the SYNC0 or SYNC1 status register (DC_SYNC0/1_STAT at 0x098E, 0x098F). */

/* DC_ACT_STAT Register bit definitions */
#define R_ESC_DC_ACT_STAT_SYNC0ACT                (1 << 0)  /* SYNC0 Status Indication */

#define R_ESC_DC_ACT_STAT_SYNC1ACT                (1 << 1)  /* SYNC1 Status Indication */

#define R_ESC_DC_ACT_STAT_STARTTIME               (1 << 2)  /* Plausibility Result Indication */

/* DC_SYNC0_STAT Register bit definitions */
#define R_ESC_DC_SYNC0_STAT_SYNC0STA              (1 << 0)  /* SYNC0 State Indication */

/* DC_SYNC1_STAT Register bit definitions */
#define R_ESC_DC_SYNC1_STAT_SYNC1STA              (1 << 0)  /* SYNC1 State Indication */

/* DC_CYC_START_TIME_L Register bit definitions */
#define R_ESC_DC_CYC_START_TIME_L_STATIM_SHIFT    (0)  /* Start Time Setting/System Time Indication */
#define R_ESC_DC_CYC_START_TIME_L_STATIM_MASK     0xffffffff

/* DC_CYC_START_TIME_H Register bit definitions */
#define R_ESC_DC_CYC_START_TIME_H_STATIM_SHIFT    (0)  /* Start Time Setting/System Time Indication */
#define R_ESC_DC_CYC_START_TIME_H_STATIM_MASK     0xffffffff

/* DC_NEXT_SYNC1_PULSE_L Register bit definitions */
#define R_ESC_DC_NEXT_SYNC1_PULSE_L_SYNC1PULSE_SHIFT (0)  /* SYNC1 Pulse System Time Indication */
#define R_ESC_DC_NEXT_SYNC1_PULSE_L_SYNC1PULSE_MASK 0xffffffff

/* DC_NEXT_SYNC1_PULSE_H Register bit definitions */
#define R_ESC_DC_NEXT_SYNC1_PULSE_H_SYNC1PULSE_SHIFT (0)  /* SYNC1 Pulse System Time Indication */
#define R_ESC_DC_NEXT_SYNC1_PULSE_H_SYNC1PULSE_MASK 0xffffffff

/* DC_SYNC0_CYC_TIME Register bit definitions */
#define R_ESC_DC_SYNC0_CYC_TIME_SYNC0CYC_SHIFT    (0)  /* Time Between Consecutive SYNC0 Pulses */
#define R_ESC_DC_SYNC0_CYC_TIME_SYNC0CYC_MASK     0xffffffff

/* DC_SYNC1_CYC_TIME Register bit definitions */
#define R_ESC_DC_SYNC1_CYC_TIME_SYNC1CYC_SHIFT    (0)  /* Time between SYNC1 and SYNC0 Pulses */
#define R_ESC_DC_SYNC1_CYC_TIME_SYNC1CYC_MASK     0xffffffff

/* DC_LATCH0_CONT Register bit definitions */
#define R_ESC_DC_LATCH0_CONT_POSEDGE              (1 << 0)  /* Latch 0 Positive Edge Function Setting */

#define R_ESC_DC_LATCH0_CONT_NEGEDGE              (1 << 1)  /* Latch 0 Negative Edge Function Setting */

/* DC_LATCH1_CONT Register bit definitions */
#define R_ESC_DC_LATCH1_CONT_POSEDGE              (1 << 0)  /* Latch 1 Positive Edge Function Setting */

#define R_ESC_DC_LATCH1_CONT_NEGEDGE              (1 << 1)  /* Latch 1 Negative Edge Function Setting */

/* DC_LATCH0_STAT Register bit definitions */
#define R_ESC_DC_LATCH0_STAT_EVENTPOS             (1 << 0)  /* Latch 0 Positive Edge Event Indication */

#define R_ESC_DC_LATCH0_STAT_EVENTNEG             (1 << 1)  /* Latch 0 Negative Edge Event Indication */

#define R_ESC_DC_LATCH0_STAT_PINSTATE             (1 << 2)  /* Latch 0 Input Pin State Indication */

/* DC_LATCH1_STAT Register bit definitions */
#define R_ESC_DC_LATCH1_STAT_EVENTPOS             (1 << 0)  /* Latch 1 Positive Edge Event Indication */

#define R_ESC_DC_LATCH1_STAT_EVENTNEG             (1 << 1)  /* Latch 1 Negative Edge Event Indication */

#define R_ESC_DC_LATCH1_STAT_PINSTATE             (1 << 2)  /* Latch 1 Input Pin State Indication */

/* DC_LATCH0_TIME_POS_L Register bit definitions */
#define R_ESC_DC_LATCH0_TIME_POS_L_SYSTIME_SHIFT  (0)  /* System Time Indication */
#define R_ESC_DC_LATCH0_TIME_POS_L_SYSTIME_MASK   0xffffffff

/* DC_LATCH0_TIME_POS_H Register bit definitions */
#define R_ESC_DC_LATCH0_TIME_POS_H_SYSTIME_SHIFT  (0)  /* System Time Indication */
#define R_ESC_DC_LATCH0_TIME_POS_H_SYSTIME_MASK   0xffffffff

/* DC_LATCH0_TIME_NEG_L Register bit definitions */
#define R_ESC_DC_LATCH0_TIME_NEG_L_SYSTIME_SHIFT  (0)  /* System Time Indication */
#define R_ESC_DC_LATCH0_TIME_NEG_L_SYSTIME_MASK   0xffffffff

/* DC_LATCH0_TIME_NEG_H Register bit definitions */
#define R_ESC_DC_LATCH0_TIME_NEG_H_SYSTIME_SHIFT  (0)  /* System Time Indication */
#define R_ESC_DC_LATCH0_TIME_NEG_H_SYSTIME_MASK   0xffffffff

/* DC_LATCH1_TIME_POS_L Register bit definitions */
#define R_ESC_DC_LATCH1_TIME_POS_L_SYSTIME_SHIFT  (0)  /* System Time Indication */
#define R_ESC_DC_LATCH1_TIME_POS_L_SYSTIME_MASK   0xffffffff

/* DC_LATCH1_TIME_POS_H Register bit definitions */
#define R_ESC_DC_LATCH1_TIME_POS_H_SYSTIME_SHIFT  (0)  /* System Time Indication */
#define R_ESC_DC_LATCH1_TIME_POS_H_SYSTIME_MASK   0xffffffff

/* DC_LATCH1_TIME_NEG_L Register bit definitions */
#define R_ESC_DC_LATCH1_TIME_NEG_L_SYSTIME_SHIFT  (0)  /* System Time Indication */
#define R_ESC_DC_LATCH1_TIME_NEG_L_SYSTIME_MASK   0xffffffff

/* DC_LATCH1_TIME_NEG_H Register bit definitions */
#define R_ESC_DC_LATCH1_TIME_NEG_H_SYSTIME_SHIFT  (0)  /* System Time Indication */
#define R_ESC_DC_LATCH1_TIME_NEG_H_SYSTIME_MASK   0xffffffff

/* DC_ECAT_CNG_EV_TIME Register bit definitions */
#define R_ESC_DC_ECAT_CNG_EV_TIME_ECATCHANGE_SHIFT (0)  /* Local Time Indication */
#define R_ESC_DC_ECAT_CNG_EV_TIME_ECATCHANGE_MASK 0xffffffff

/* DC_PDI_START_EV_TIME Register bit definitions */
#define R_ESC_DC_PDI_START_EV_TIME_PDISTART_SHIFT (0)  /* Local Time Indication */
#define R_ESC_DC_PDI_START_EV_TIME_PDISTART_MASK  0xffffffff

/* DC_PDI_CNG_EV_TIME Register bit definitions */
#define R_ESC_DC_PDI_CNG_EV_TIME_PDICHANGE_SHIFT  (0)  /* Local Time Indication */
#define R_ESC_DC_PDI_CNG_EV_TIME_PDICHANGE_MASK   0xffffffff

/* PRODUCT_ID_L Register bit definitions */
#define R_ESC_PRODUCT_ID_L_PROID_SHIFT            (0)  /* Product ID Indication */
#define R_ESC_PRODUCT_ID_L_PROID_MASK             0xffffffff

/* PRODUCT_ID_H Register bit definitions */
#define R_ESC_PRODUCT_ID_H_PROID_SHIFT            (0)  /* Product ID Indication */
#define R_ESC_PRODUCT_ID_H_PROID_MASK             0xffffffff

/* VENDOR_ID_L Register bit definitions */
#define R_ESC_VENDOR_ID_L_VENDORID_SHIFT          (0)  /* Vendor ID Indication */
#define R_ESC_VENDOR_ID_L_VENDORID_MASK           0xffffffff


/* Maximum number of channels */

#define ESC_MAX_CHANNELS    8

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ESC_H */
