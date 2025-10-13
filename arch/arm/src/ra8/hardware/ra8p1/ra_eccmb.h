/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_eccmb.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ECCMB_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ECCMB_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ECCMB Base Address */
#ifndef R_ECCMB_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_ECCMB_BASE           0x4036f200
#else
#define R_ECCMB_BASE           0x5036f200
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_ECCMB_CH_STRIDE    0x00000100
#define R_ECCMB_CH_BASE(ch)   (R_ECCMB_BASE + ((uint32_t)(ch) * R_ECCMB_CH_STRIDE))

/* ECCMB Register Offsets */

#define R_ECCMB_EC710CTL_OFFSET     0x00000000  /* ECC Control Register */
#define R_ECCMB_EC710TMC_OFFSET     0x00000004  /* ECC Test Mode Control Register */
#define R_ECCMB_EC710TED_OFFSET     0x0000000c  /* ECC Test Substitute Data Register */
#define R_ECCMB_EC710EAD0_OFFSET     0x00000010  /* ECC Error Address Register */

/* ECCMB Register Addresses */

#define R_ECCMB_EC710CTL                 (R_ECCMB_BASE + R_ECCMB_EC710CTL_OFFSET)
#define R_ECCMB_EC710TMC                 (R_ECCMB_BASE + R_ECCMB_EC710TMC_OFFSET)
#define R_ECCMB_EC710TED                 (R_ECCMB_BASE + R_ECCMB_EC710TED_OFFSET)
#define R_ECCMB_EC710EAD0                 (R_ECCMB_BASE + R_ECCMB_EC710EAD0_OFFSET)

/* Register bit definitions */
/* EC710CTL Register bit definitions */
#define R_ECCMB_EC710CTL_ECEMF                    (1 << 0)  /* ECC Error Message Flag */

#define R_ECCMB_EC710CTL_ECER1F                   (1 << 1)  /* ECC Error Detection and Correction Flag */

#define R_ECCMB_EC710CTL_ECER2F                   (1 << 2)  /* 2-bit ECC Error Detection Flag */

#define R_ECCMB_EC710CTL_EC1EDIC                  (1 << 3)  /* ECC 1-bit Error Detection Interrupt Control */

#define R_ECCMB_EC710CTL_EC2EDIC                  (1 << 4)  /* ECC 2-bit Error Detection Interrupt Control */

#define R_ECCMB_EC710CTL_EC1ECP                   (1 << 5)  /* ECC 1-bit Error Correction Permission */

#define R_ECCMB_EC710CTL_ECERVF                   (1 << 6)  /* ECC Error Judgment Enable Flag */

#define R_ECCMB_EC710CTL_ECER1C                   (1 << 9)  /* Accumulating ECC Error Detection and Correction Flag Clear */

#define R_ECCMB_EC710CTL_ECER2C                   (1 << 10)  /* 2-bit ECC Error Detection Flag Clear */

#define R_ECCMB_EC710CTL_ECOVFF                   (1 << 11)  /* ECC Overflow Detection Flag */

#define R_ECCMB_EC710CTL_EMCA_SHIFT               (14)  /* Access Control to ECC Mode Select bit */
#define R_ECCMB_EC710CTL_EMCA_MASK                0xc000

#define R_ECCMB_EC710CTL_ECSEDF0                  (1 << 16)  /* ECC Single bit Error Address Detection Flag */

#define R_ECCMB_EC710CTL_ECDEDF0                  (1 << 17)  /* ECC Dual Bit Error Address Detection Flag */

/* EC710TMC Register bit definitions */
#define R_ECCMB_EC710TMC_ECDCS                    (1 << 1)  /* ECC Decode Input Select */

#define R_ECCMB_EC710TMC_ECTMCE                   (1 << 7)  /* ECC Test Mode Control Enable */

#define R_ECCMB_EC710TMC_ETMA_SHIFT               (14)  /* ECC Test Mode Bit Access Control */
#define R_ECCMB_EC710TMC_ETMA_MASK                0xc000

/* EC710TED Register bit definitions */
#define R_ECCMB_EC710TED_ECEDB_SHIFT              (0)  /* ECC Test Substitute Data */
#define R_ECCMB_EC710TED_ECEDB_MASK               0xffffffff

/* EC710EAD0 Register bit definitions */
#define R_ECCMB_EC710EAD0_ECEAD_SHIFT             (0)  /* ECC Error Address */
#define R_ECCMB_EC710EAD0_ECEAD_MASK              0x3ff


/* Maximum number of channels */

#define ECCMB_MAX_CHANNELS    2

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ECCMB_H */
