/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_esc_ini.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ESC_INI_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ESC_INI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ESC_INI Base Address */
#ifndef R_ESC_INI_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_ESC_INI_BASE           0x403a4000
#else
#define R_ESC_INI_BASE           0x503a4000
#endif
#endif

/* ESC_INI Register Offsets */

#define R_ESC_INI_ESCRST_OFFSET     0x00000000  /* ESC Reset Control Register */
#define R_ESC_INI_PHYLINK_OFFSET     0x00000010  /* PHY LINK Polarity Setting Register */
#define R_ESC_INI_ESCICR_OFFSET     0x00000014  /* ESC Interrupt Control Register */
#define R_ESC_INI_ECATOFFADR_OFFSET     0x00000018  /* EtherCAT PHY Offset Address Register */
#define R_ESC_INI_ECATOPMOD_OFFSET     0x0000001c  /* EtherCAT Operation Mode Register */
#define R_ESC_INI_ECATDBGC_OFFSET     0x00000020  /* EtherCAT Debug Control Register */

/* ESC_INI Register Addresses */

#define R_ESC_INI_ESCRST                 (R_ESC_INI_BASE + R_ESC_INI_ESCRST_OFFSET)
#define R_ESC_INI_PHYLINK                 (R_ESC_INI_BASE + R_ESC_INI_PHYLINK_OFFSET)
#define R_ESC_INI_ESCICR                 (R_ESC_INI_BASE + R_ESC_INI_ESCICR_OFFSET)
#define R_ESC_INI_ECATOFFADR                 (R_ESC_INI_BASE + R_ESC_INI_ECATOFFADR_OFFSET)
#define R_ESC_INI_ECATOPMOD                 (R_ESC_INI_BASE + R_ESC_INI_ECATOPMOD_OFFSET)
#define R_ESC_INI_ECATDBGC                 (R_ESC_INI_BASE + R_ESC_INI_ECATDBGC_OFFSET)

/* Register bit definitions */
/* ESCRST Register bit definitions */
#define R_ESC_INI_ESCRST_ESCRST                   (1 << 0)  /* ESC Reset */

#define R_ESC_INI_ESCRST_PHYRST                   (1 << 1)  /* PHY Reset */

/* PHYLINK Register bit definitions */
#define R_ESC_INI_PHYLINK_LINKPOL0                (1 << 0)  /* CAT0_LINKSTA Pin Polarity */

#define R_ESC_INI_PHYLINK_LINKPOL1                (1 << 1)  /* CAT1_LINKSTA Pin Polarity */

/* ESCICR Register bit definitions */
#define R_ESC_INI_ESCICR_SYNC0C                   (1 << 0)  /*  */

#define R_ESC_INI_ESCICR_SYNC1C                   (1 << 1)  /*  */

#define R_ESC_INI_ESCICR_ESCIC                    (1 << 2)  /*  */

#define R_ESC_INI_ESCICR_LAT0S                    (1 << 4)  /* Select DC Latch Trigger 0 for ESC */

#define R_ESC_INI_ESCICR_LAT1S                    (1 << 5)  /* Select DC Latch Trigger 1 for ESC */

/* ECATOFFADR Register bit definitions */
#define R_ESC_INI_ECATOFFADR_OADD_SHIFT           (0)  /*  */
#define R_ESC_INI_ECATOFFADR_OADD_MASK            0x1f

/* ECATOPMOD Register bit definitions */
#define R_ESC_INI_ECATOPMOD_EEPROMSIZE            (1 << 0)  /*  */

/* ECATDBGC Register bit definitions */
#define R_ESC_INI_ECATDBGC_TXSFT0_SHIFT           (0)  /* Port 0 TX Signal Delay Setting */
#define R_ESC_INI_ECATDBGC_TXSFT0_MASK            0x3
#  define R_ESC_INI_ECATDBGC_TXSFT0_00                    (0 << R_ESC_INI_ECATDBGC_TXSFT0_SHIFT)  /* 0 ns */
#  define R_ESC_INI_ECATDBGC_TXSFT0_01                    (1 << R_ESC_INI_ECATDBGC_TXSFT0_SHIFT)  /* 10 ns */
#  define R_ESC_INI_ECATDBGC_TXSFT0_10                    (2 << R_ESC_INI_ECATDBGC_TXSFT0_SHIFT)  /* 20 ns */
#  define R_ESC_INI_ECATDBGC_TXSFT0_11                    (3 << R_ESC_INI_ECATDBGC_TXSFT0_SHIFT)  /* 30 ns */

#define R_ESC_INI_ECATDBGC_TXSFT1_SHIFT           (2)  /* Port 1 TX Signal Delay Setting */
#define R_ESC_INI_ECATDBGC_TXSFT1_MASK            0xc
#  define R_ESC_INI_ECATDBGC_TXSFT1_00                    (0 << R_ESC_INI_ECATDBGC_TXSFT1_SHIFT)  /* 0 ns */
#  define R_ESC_INI_ECATDBGC_TXSFT1_01                    (1 << R_ESC_INI_ECATDBGC_TXSFT1_SHIFT)  /* 10 ns */
#  define R_ESC_INI_ECATDBGC_TXSFT1_10                    (2 << R_ESC_INI_ECATDBGC_TXSFT1_SHIFT)  /* 20 ns */
#  define R_ESC_INI_ECATDBGC_TXSFT1_11                    (3 << R_ESC_INI_ECATDBGC_TXSFT1_SHIFT)  /* 30 ns */


/* Maximum number of channels */

#define ESC_INI_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_ESC_INI_H */
