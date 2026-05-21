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

/* BUS Register Offsets */

/* CSa[%s] Registers () */
#define R_BUS_CSA_OFFSET(m)                       (0x00000000 + ((m) * 0x00000010))  /* CS Registers */
/* CSb[%s] Registers () */
#define R_BUS_CSB_OFFSET(m)                       (0x00000800 + ((m) * 0x00000010))  /* CS Registers */
#define R_BUS_CSRECEN_OFFSET                      0x00000880  /* CS Recovery Cycle Insertion Enable Register */
#define R_BUS_SDRAM_OFFSET                        0x00000c00  /* SDRAM Registers */
#define R_BUS_OAD_OFFSET                          0x00001000  /* Bus Operation After Detection Registers */
/* BUSM[%s] Registers () */
#define R_BUS_BUSM_OFFSET(m)                      (0x00001000 + ((m) * 0x00000004))  /* Master Bus Control Registers */
#define R_BUS_BUSMABT_OFFSET                      0x00001100  /* Bus Master Arbitration Control Register. */
/* BUSS[%s] Registers () */
#define R_BUS_BUSS_OFFSET(m)                      (0x00001100 + ((m) * 0x00000004))  /* Slave Bus Control Register Array */
#define R_BUS_BUSSABT0_OFFSET                     0x00001200  /* Bus Slave Arbitration Control 0 Registers */
#define R_BUS_BUSSABT1_OFFSET                     0x00001200  /* Bus Slave Arbitration Control 1 Registers */
#define R_BUS_BUSDIVBYP_OFFSET                    0x00001300  /* Bus Divider Bypass Register. */
#define R_BUS_BUSTHRPUT_OFFSET                    0x00001400  /* Graphic Bus Throughput Control Register */
/* BUSERRa[%s] Registers () */
#define R_BUS_BUSERRA_OFFSET(m)                   (0x00001800 + ((m) * 0x00000010))  /* Bus Error Registers */
/* BTZFERR[%s] Registers () */
#define R_BUS_BTZFERR_OFFSET(m)                   (0x00001900 + ((m) * 0x00000010))  /* Bus TZF Error Registers */
/* BMSAERR[%s] Registers () */
#define R_BUS_BMSAERR_OFFSET(m)                   (0x00001900 + ((m) * 0x00000010))  /* Bus Master Security Attribution Unit Error Address and Read/Write Status registers. */
/* BUSERRb[%s] Registers () */
#define R_BUS_BUSERRB_OFFSET(m)                   (0x00001a00 + ((m) * 0x00000010))  /* Bus Error Registers */
#define R_BUS_DMACDTCERR_OFFSET                   0x00001a00  /* DMAC/DTC Error Registers */
#define R_BUS_MBWERR_OFFSET                       0x00001b00  /* Master Bufferable Write Error Registers */

/* BUS Register Addresses */

#define R_BUS_CSA(m)                              (R_BUS_BASE + R_BUS_CSA_OFFSET(m))
#define R_BUS_CSB(m)                              (R_BUS_BASE + R_BUS_CSB_OFFSET(m))
#define R_BUS_CSRECEN                             (R_BUS_BASE + R_BUS_CSRECEN_OFFSET)
#define R_BUS_SDRAM                               (R_BUS_BASE + R_BUS_SDRAM_OFFSET)
#define R_BUS_OAD                                 (R_BUS_BASE + R_BUS_OAD_OFFSET)
#define R_BUS_BUSM(m)                             (R_BUS_BASE + R_BUS_BUSM_OFFSET(m))
#define R_BUS_BUSMABT                             (R_BUS_BASE + R_BUS_BUSMABT_OFFSET)
#define R_BUS_BUSS(m)                             (R_BUS_BASE + R_BUS_BUSS_OFFSET(m))
#define R_BUS_BUSSABT0                            (R_BUS_BASE + R_BUS_BUSSABT0_OFFSET)
#define R_BUS_BUSSABT1                            (R_BUS_BASE + R_BUS_BUSSABT1_OFFSET)
#define R_BUS_BUSDIVBYP                           (R_BUS_BASE + R_BUS_BUSDIVBYP_OFFSET)
#define R_BUS_BUSTHRPUT                           (R_BUS_BASE + R_BUS_BUSTHRPUT_OFFSET)
#define R_BUS_BUSERRA(m)                          (R_BUS_BASE + R_BUS_BUSERRA_OFFSET(m))
#define R_BUS_BTZFERR(m)                          (R_BUS_BASE + R_BUS_BTZFERR_OFFSET(m))
#define R_BUS_BMSAERR(m)                          (R_BUS_BASE + R_BUS_BMSAERR_OFFSET(m))
#define R_BUS_BUSERRB(m)                          (R_BUS_BASE + R_BUS_BUSERRB_OFFSET(m))
#define R_BUS_DMACDTCERR                          (R_BUS_BASE + R_BUS_DMACDTCERR_OFFSET)
#define R_BUS_MBWERR                              (R_BUS_BASE + R_BUS_MBWERR_OFFSET)

/* Register bit definitions */
/* CSRECEN Register bit definitions */
#define R_BUS_CSRECEN_RCVENM_S                    (1 << 8)  /* Multiplexed Bus Recovery Cycle Insertion Enable */

#define R_BUS_CSRECEN_RCVEN_S                     (1 << 0)  /* Separate Bus Recovery Cycle Insertion Enable */

#define R_BUS_CSRECEN_RCVEN0                      (1 << 0)  /* Separate Bus Recovery Cycle Insertion Enable */

#define R_BUS_CSRECEN_RCVEN1                      (1 << 1)  /* Separate Bus Recovery Cycle Insertion Enable */

#define R_BUS_CSRECEN_RCVEN2                      (1 << 2)  /* Separate Bus Recovery Cycle Insertion Enable */

#define R_BUS_CSRECEN_RCVEN3                      (1 << 3)  /* Separate Bus Recovery Cycle Insertion Enable */

#define R_BUS_CSRECEN_RCVEN4                      (1 << 4)  /* Separate Bus Recovery Cycle Insertion Enable */

#define R_BUS_CSRECEN_RCVEN5                      (1 << 5)  /* Separate Bus Recovery Cycle Insertion Enable */

#define R_BUS_CSRECEN_RCVEN6                      (1 << 6)  /* Separate Bus Recovery Cycle Insertion Enable */

#define R_BUS_CSRECEN_RCVEN7                      (1 << 7)  /* Separate Bus Recovery Cycle Insertion Enable */

#define R_BUS_CSRECEN_RCVENM0                     (1 << 8)  /* Multiplexed Bus Recovery Cycle Insertion Enable */

#define R_BUS_CSRECEN_RCVENM1                     (1 << 9)  /* Multiplexed Bus Recovery Cycle Insertion Enable */

#define R_BUS_CSRECEN_RCVENM2                     (1 << 10)  /* Multiplexed Bus Recovery Cycle Insertion Enable */

#define R_BUS_CSRECEN_RCVENM3                     (1 << 11)  /* Multiplexed Bus Recovery Cycle Insertion Enable */

#define R_BUS_CSRECEN_RCVENM4                     (1 << 12)  /* Multiplexed Bus Recovery Cycle Insertion Enable */

#define R_BUS_CSRECEN_RCVENM5                     (1 << 13)  /* Multiplexed Bus Recovery Cycle Insertion Enable */

#define R_BUS_CSRECEN_RCVENM6                     (1 << 14)  /* Multiplexed Bus Recovery Cycle Insertion Enable */

#define R_BUS_CSRECEN_RCVENM7                     (1 << 15)  /* Multiplexed Bus Recovery Cycle Insertion Enable */

/* BUSMABT Register bit definitions */
#define R_BUS_BUSMABT_ARBS                        (1 << 0)  /* Arbitration Select for GDSSBI. */

/* BUSDIVBYP Register bit definitions */
#define R_BUS_BUSDIVBYP_CPU0SBPE                  (1 << 16)  /* Divider for CPUSAHBI bypass enable. */

#define R_BUS_BUSDIVBYP_GDSSBPE                   (1 << 3)  /* Divider for GDSSBI bypass enable. */

#define R_BUS_BUSDIVBYP_EDMABPE                   (1 << 0)  /* Divider for EDMACBI bypass enable. */

/* BUSTHRPUT Register bit definitions */
#define R_BUS_BUSTHRPUT_DIS                       (1 << 0)  /* Bandwidth Control Function */


/* Maximum number of channels */

#define BUS_MAX_CHANNELS    18

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_BUS_H */
