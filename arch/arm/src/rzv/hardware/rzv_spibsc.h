/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_spibsc.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SPIBSC_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SPIBSC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SPIBSC Base Addresses *************************************************/

#ifndef RZV_SPIBSC0_BASE
#  define RZV_SPIBSC0_BASE            0x40060000
#endif
#ifndef RZV_SPIBSC_BASE
#  define RZV_SPIBSC_BASE             RZV_SPIBSC0_BASE
#endif

/* SPIBSC Register Offsets ************************************************/

/* PHYADJ%s Registers (1-2) */
#define RZV_SPIBSC_PHYADJ_OFFSET(m)             (0x00000068 + ((m) * 0x00000004))  /* PHYADJ Register %s */
/* PHYOFFSET%s Registers (1-2) */
#define RZV_SPIBSC_PHYOFFSET_OFFSET(m)          (0x00000078 + ((m) * 0x00000004))  /* PHYOFFSET Register %s */
#define RZV_SPIBSC_CMNCR_OFFSET                          0x0000  /* CMNCR */
#define RZV_SPIBSC_SSLDR_OFFSET                          0x0004  /* SSLDR */
#define RZV_SPIBSC_DRCR_OFFSET                           0x000C  /* DRCR */
#define RZV_SPIBSC_DRCMR_OFFSET                          0x0010  /* DRCMR */
#define RZV_SPIBSC_DREAR_OFFSET                          0x0014  /* DREAR */
#define RZV_SPIBSC_DROPR_OFFSET                          0x0018  /* DROPR */
#define RZV_SPIBSC_DRENR_OFFSET                          0x001C  /* DRENR */
#define RZV_SPIBSC_SMCR_OFFSET                           0x0020  /* SMCR */
#define RZV_SPIBSC_SMCMR_OFFSET                          0x0024  /* SMCMR */
#define RZV_SPIBSC_SMADR_OFFSET                          0x0028  /* SMADR */
#define RZV_SPIBSC_SMOPR_OFFSET                          0x002C  /* SMOPR */
#define RZV_SPIBSC_SMENR_OFFSET                          0x0030  /* SMENR */
#define RZV_SPIBSC_H_OFFSET                              0x0038  /* H */
#define RZV_SPIBSC_H_OFFSET                              0x003A  /* H */
#define RZV_SPIBSC_H_OFFSET                              0x003C  /* H */
#define RZV_SPIBSC_H_OFFSET                              0x003E  /* H */
#define RZV_SPIBSC_CMNSR_OFFSET                          0x0040  /* CMNSR */
#define RZV_SPIBSC_DRDMCR_OFFSET                         0x0050  /* DRDMCR */
#define RZV_SPIBSC_DRDRENR_OFFSET                        0x0054  /* DRDRENR */
#define RZV_SPIBSC_SMDMCR_OFFSET                         0x0058  /* SMDMCR */
#define RZV_SPIBSC_SMDRENR_OFFSET                        0x005C  /* SMDRENR */
#define RZV_SPIBSC_PHYCNT_OFFSET                         0x0074  /* PHYCNT */
#define RZV_SPIBSC_PHYINT_OFFSET                         0x0080  /* PHYINT */

/* SPIBSC Register Addresses ***********************************************/

#define RZV_SPIBSC_PHYADJ(m)                    (RZV_SPIBSC_BASE + RZV_SPIBSC_PHYADJ_OFFSET(m))
#define RZV_SPIBSC_PHYOFFSET(m)                 (RZV_SPIBSC_BASE + RZV_SPIBSC_PHYOFFSET_OFFSET(m))
#define RZV_SPIBSC_CMNCR                             (RZV_SPIBSC_BASE + RZV_SPIBSC_CMNCR_OFFSET)
#define RZV_SPIBSC_SSLDR                             (RZV_SPIBSC_BASE + RZV_SPIBSC_SSLDR_OFFSET)
#define RZV_SPIBSC_DRCR                              (RZV_SPIBSC_BASE + RZV_SPIBSC_DRCR_OFFSET)
#define RZV_SPIBSC_DRCMR                             (RZV_SPIBSC_BASE + RZV_SPIBSC_DRCMR_OFFSET)
#define RZV_SPIBSC_DREAR                             (RZV_SPIBSC_BASE + RZV_SPIBSC_DREAR_OFFSET)
#define RZV_SPIBSC_DROPR                             (RZV_SPIBSC_BASE + RZV_SPIBSC_DROPR_OFFSET)
#define RZV_SPIBSC_DRENR                             (RZV_SPIBSC_BASE + RZV_SPIBSC_DRENR_OFFSET)
#define RZV_SPIBSC_SMCR                              (RZV_SPIBSC_BASE + RZV_SPIBSC_SMCR_OFFSET)
#define RZV_SPIBSC_SMCMR                             (RZV_SPIBSC_BASE + RZV_SPIBSC_SMCMR_OFFSET)
#define RZV_SPIBSC_SMADR                             (RZV_SPIBSC_BASE + RZV_SPIBSC_SMADR_OFFSET)
#define RZV_SPIBSC_SMOPR                             (RZV_SPIBSC_BASE + RZV_SPIBSC_SMOPR_OFFSET)
#define RZV_SPIBSC_SMENR                             (RZV_SPIBSC_BASE + RZV_SPIBSC_SMENR_OFFSET)
#define RZV_SPIBSC_H                                 (RZV_SPIBSC_BASE + RZV_SPIBSC_H_OFFSET)
#define RZV_SPIBSC_H                                 (RZV_SPIBSC_BASE + RZV_SPIBSC_H_OFFSET)
#define RZV_SPIBSC_H                                 (RZV_SPIBSC_BASE + RZV_SPIBSC_H_OFFSET)
#define RZV_SPIBSC_H                                 (RZV_SPIBSC_BASE + RZV_SPIBSC_H_OFFSET)
#define RZV_SPIBSC_CMNSR                             (RZV_SPIBSC_BASE + RZV_SPIBSC_CMNSR_OFFSET)
#define RZV_SPIBSC_DRDMCR                            (RZV_SPIBSC_BASE + RZV_SPIBSC_DRDMCR_OFFSET)
#define RZV_SPIBSC_DRDRENR                           (RZV_SPIBSC_BASE + RZV_SPIBSC_DRDRENR_OFFSET)
#define RZV_SPIBSC_SMDMCR                            (RZV_SPIBSC_BASE + RZV_SPIBSC_SMDMCR_OFFSET)
#define RZV_SPIBSC_SMDRENR                           (RZV_SPIBSC_BASE + RZV_SPIBSC_SMDRENR_OFFSET)
#define RZV_SPIBSC_PHYCNT                            (RZV_SPIBSC_BASE + RZV_SPIBSC_PHYCNT_OFFSET)
#define RZV_SPIBSC_PHYINT                            (RZV_SPIBSC_BASE + RZV_SPIBSC_PHYINT_OFFSET)

/* SPIBSC PHYADJ Register Bit Definitions (Parameterized) ******************/

#define SPIBSC_PHYADJ_ADJ_SHIFT                           (0)      /* Bits 0-31: Adj1 */
#define SPIBSC_PHYADJ_ADJ_MASK(m)                         (0xffffffff << SPIBSC_PHYADJ_ADJ_SHIFT)
#define SPIBSC_PHYADJ_ADJ(m,val)                          (((val) << SPIBSC_PHYADJ_ADJ_SHIFT) & SPIBSC_PHYADJ_ADJ_MASK(m))

/* SPIBSC PHYOFFSET Register Bit Definitions (Parameterized) ***************/

#define SPIBSC_PHYOFFSET_DDRTMG_SHIFT                     (28)      /* Bits 28-29: Ddrtmg */
#define SPIBSC_PHYOFFSET_DDRTMG_MASK(m)                   (0x3 << SPIBSC_PHYOFFSET_DDRTMG_SHIFT)
#define SPIBSC_PHYOFFSET_DDRTMG(m,val)                    (((val) << SPIBSC_PHYOFFSET_DDRTMG_SHIFT) & SPIBSC_PHYOFFSET_DDRTMG_MASK(m))

/* SPIBSC CMNCR Register Bit Definitions *****************************/

/* MOIIO fields (parameterized for indices 0-3) */
#define SPIBSC_CMNCR_MOIIO_SHIFT(n)                       ((unsigned)(16 + ((n) * 2)))  /* Bits for MOIIOn */
#define SPIBSC_CMNCR_MOIIO_MASK(n)                        (0x3u << SPIBSC_CMNCR_MOIIO_SHIFT(n))
#define SPIBSC_CMNCR_MOIIO_VAL(n,v)                       (((unsigned)(v) & 0x3u) << SPIBSC_CMNCR_MOIIO_SHIFT(n))

#define SPIBSC_CMNCR_BSZ_SHIFT                  (0)      /* Bits 0-1: Bsz */
#define SPIBSC_CMNCR_BSZ_MASK                   (0x3 << SPIBSC_CMNCR_BSZ_SHIFT)

#define SPIBSC_CMNCR_IO0FV_SHIFT                (8)      /* Bits 8-9: Io0Fv */
#define SPIBSC_CMNCR_IO0FV_MASK                 (0x3 << SPIBSC_CMNCR_IO0FV_SHIFT)

#define SPIBSC_CMNCR_IO2FV_SHIFT                (12)      /* Bits 12-13: Io2Fv */
#define SPIBSC_CMNCR_IO2FV_MASK                 (0x3 << SPIBSC_CMNCR_IO2FV_SHIFT)

#define SPIBSC_CMNCR_IO3FV_SHIFT                (14)      /* Bits 14-15: Io3Fv */
#define SPIBSC_CMNCR_IO3FV_MASK                 (0x3 << SPIBSC_CMNCR_IO3FV_SHIFT)

#define SPIBSC_CMNCR_MD                         (1 << 31)  /* Md */

/* SPIBSC CMNSR Register Bit Definitions *****************************/

#define SPIBSC_CMNSR_TEND                       (1 << 0)  /* Tend */

#define SPIBSC_CMNSR_SSLF                       (1 << 1)  /* Sslf */

/* SPIBSC DRCMR Register Bit Definitions *****************************/

#define SPIBSC_DRCMR_OCMD_SHIFT                 (0)      /* Bits 0-7: Ocmd */
#define SPIBSC_DRCMR_OCMD_MASK                  (0xff << SPIBSC_DRCMR_OCMD_SHIFT)

#define SPIBSC_DRCMR_CMD_SHIFT                  (16)      /* Bits 16-23: Cmd */
#define SPIBSC_DRCMR_CMD_MASK                   (0xff << SPIBSC_DRCMR_CMD_SHIFT)

/* SPIBSC DRCR Register Bit Definitions ******************************/

#define SPIBSC_DRCR_SSLE                        (1 << 0)  /* Ssle */

#define SPIBSC_DRCR_RBE                         (1 << 8)  /* Rbe */

#define SPIBSC_DRCR_RCF                         (1 << 9)  /* Rcf */

#define SPIBSC_DRCR_RBURST_SHIFT                (16)      /* Bits 16-20: Rburst */
#define SPIBSC_DRCR_RBURST_MASK                 (0x1f << SPIBSC_DRCR_RBURST_SHIFT)

#define SPIBSC_DRCR_SSLN                        (1 << 24)  /* Ssln */

/* SPIBSC DRDMCR Register Bit Definitions ****************************/

#define SPIBSC_DRDMCR_DMCYC_SHIFT               (0)      /* Bits 0-4: Dmcyc */
#define SPIBSC_DRDMCR_DMCYC_MASK                (0x1f << SPIBSC_DRDMCR_DMCYC_SHIFT)

/* SPIBSC DREAR Register Bit Definitions *****************************/

#define SPIBSC_DREAR_EAC_SHIFT                  (0)      /* Bits 0-2: Eac */
#define SPIBSC_DREAR_EAC_MASK                   (0x7 << SPIBSC_DREAR_EAC_SHIFT)

#define SPIBSC_DREAR_EAV_SHIFT                  (16)      /* Bits 16-23: Eav */
#define SPIBSC_DREAR_EAV_MASK                   (0xff << SPIBSC_DREAR_EAV_SHIFT)

/* SPIBSC DRENR Register Bit Definitions *****************************/

#define SPIBSC_DRENR_OPDE_SHIFT                 (4)      /* Bits 4-7: Opde */
#define SPIBSC_DRENR_OPDE_MASK                  (0xf << SPIBSC_DRENR_OPDE_SHIFT)

#define SPIBSC_DRENR_ADE_SHIFT                  (8)      /* Bits 8-11: Ade */
#define SPIBSC_DRENR_ADE_MASK                   (0xf << SPIBSC_DRENR_ADE_SHIFT)

#define SPIBSC_DRENR_OCDE                       (1 << 12)  /* Ocde */

#define SPIBSC_DRENR_CDE                        (1 << 14)  /* Cde */

#define SPIBSC_DRENR_DME                        (1 << 15)  /* Dme */

#define SPIBSC_DRENR_DRDB_SHIFT                 (16)      /* Bits 16-17: Drdb */
#define SPIBSC_DRENR_DRDB_MASK                  (0x3 << SPIBSC_DRENR_DRDB_SHIFT)

#define SPIBSC_DRENR_OPDB_SHIFT                 (20)      /* Bits 20-21: Opdb */
#define SPIBSC_DRENR_OPDB_MASK                  (0x3 << SPIBSC_DRENR_OPDB_SHIFT)

#define SPIBSC_DRENR_ADB_SHIFT                  (24)      /* Bits 24-25: Adb */
#define SPIBSC_DRENR_ADB_MASK                   (0x3 << SPIBSC_DRENR_ADB_SHIFT)

#define SPIBSC_DRENR_OCDB_SHIFT                 (28)      /* Bits 28-29: Ocdb */
#define SPIBSC_DRENR_OCDB_MASK                  (0x3 << SPIBSC_DRENR_OCDB_SHIFT)

#define SPIBSC_DRENR_CDB_SHIFT                  (30)      /* Bits 30-31: Cdb */
#define SPIBSC_DRENR_CDB_MASK                   (0x3 << SPIBSC_DRENR_CDB_SHIFT)

#define SPIBSC_DRENR_DRDRE                      (1 << 0)  /* Drdre */

#define SPIBSC_DRENR_OPDRE4                     (1 << 4)  /* Opdre */

#define SPIBSC_DRENR_ADDRE8                     (1 << 8)  /* Addre */

#define SPIBSC_DRENR_HYPE12_SHIFT               (12)      /* Bits 12-14: Hype */
#define SPIBSC_DRENR_HYPE12_MASK                (0x7 << SPIBSC_DRENR_HYPE12_SHIFT)

#define SPIBSC_DRENR_SPIDRE                     (1 << 0)  /* Spidre */

#define SPIBSC_DRENR_OPDRE4                     (1 << 4)  /* Opdre */

#define SPIBSC_DRENR_ADDRE8                     (1 << 8)  /* Addre */

#define SPIBSC_DRENR_HYPE12_SHIFT               (12)      /* Bits 12-14: Hype */
#define SPIBSC_DRENR_HYPE12_MASK                (0x7 << SPIBSC_DRENR_HYPE12_SHIFT)

/* SPIBSC DROPR Register Bit Definitions *****************************/

/* OPD fields (parameterized for indices 0-3) */
#define SPIBSC_DROPR_OPD_SHIFT(n)                         ((unsigned)(0 + ((n) * 8)))  /* Bits for OPDn */
#define SPIBSC_DROPR_OPD_MASK(n)                          (0xffu << SPIBSC_DROPR_OPD_SHIFT(n))
#define SPIBSC_DROPR_OPD_VAL(n,v)                         (((unsigned)(v) & 0xffu) << SPIBSC_DROPR_OPD_SHIFT(n))

/* SPIBSC PHYCNT Register Bit Definitions ****************************/

#define SPIBSC_PHYCNT_PHYMEM_SHIFT              (0)      /* Bits 0-1: Phymem */
#define SPIBSC_PHYCNT_PHYMEM_MASK               (0x3 << SPIBSC_PHYCNT_PHYMEM_SHIFT)

#define SPIBSC_PHYCNT_WBUF                      (1 << 2)  /* Wbuf */

#define SPIBSC_PHYCNT_WBUF2                     (1 << 4)  /* Wbuf2 */

#define SPIBSC_PHYCNT_CKSEL_SHIFT               (16)      /* Bits 16-17: Cksel */
#define SPIBSC_PHYCNT_CKSEL_MASK                (0x3 << SPIBSC_PHYCNT_CKSEL_SHIFT)

#define SPIBSC_PHYCNT_HS                        (1 << 18)  /* Hs */

#define SPIBSC_PHYCNT_OCT                       (1 << 20)  /* Oct */

#define SPIBSC_PHYCNT_EXDS                      (1 << 21)  /* Exds */

#define SPIBSC_PHYCNT_OCTA_SHIFT                (22)      /* Bits 22-23: Octa */
#define SPIBSC_PHYCNT_OCTA_MASK                 (0x3 << SPIBSC_PHYCNT_OCTA_SHIFT)

#define SPIBSC_PHYCNT_ALT_ALIGN                 (1 << 30)  /* Alt Align */

#define SPIBSC_PHYCNT_CAL                       (1 << 31)  /* Cal */

/* SPIBSC PHYINT Register Bit Definitions ****************************/

#define SPIBSC_PHYINT_INT                       (1 << 0)  /* Int */

#define SPIBSC_PHYINT_WPVAL                     (1 << 1)  /* Wpval */

#define SPIBSC_PHYINT_RSTVAL                    (1 << 2)  /* Rstval */

#define SPIBSC_PHYINT_INTEN                     (1 << 24)  /* Inten */

#define SPIBSC_PHYINT_WPEN                      (1 << 25)  /* Wpen */

#define SPIBSC_PHYINT_RSTEN                     (1 << 26)  /* Rsten */

/* SPIBSC SMADR Register Bit Definitions *****************************/

#define SPIBSC_SMADR_ADR_SHIFT                  (0)      /* Bits 0-31: Adr */
#define SPIBSC_SMADR_ADR_MASK                   (0xffffffff << SPIBSC_SMADR_ADR_SHIFT)

/* SPIBSC SMCMR Register Bit Definitions *****************************/

#define SPIBSC_SMCMR_OCMD_SHIFT                 (0)      /* Bits 0-7: Ocmd */
#define SPIBSC_SMCMR_OCMD_MASK                  (0xff << SPIBSC_SMCMR_OCMD_SHIFT)

#define SPIBSC_SMCMR_CMD_SHIFT                  (16)      /* Bits 16-23: Cmd */
#define SPIBSC_SMCMR_CMD_MASK                   (0xff << SPIBSC_SMCMR_CMD_SHIFT)

/* SPIBSC SMCR Register Bit Definitions ******************************/

#define SPIBSC_SMCR_SPIE                        (1 << 0)  /* Spie */

#define SPIBSC_SMCR_SPIWE                       (1 << 1)  /* Spiwe */

#define SPIBSC_SMCR_SPIRE                       (1 << 2)  /* Spire */

#define SPIBSC_SMCR_SSLKP                       (1 << 8)  /* Sslkp */

/* SPIBSC SMDMCR Register Bit Definitions ****************************/

#define SPIBSC_SMDMCR_DMCYC_SHIFT               (0)      /* Bits 0-4: Dmcyc */
#define SPIBSC_SMDMCR_DMCYC_MASK                (0x1f << SPIBSC_SMDMCR_DMCYC_SHIFT)

/* SPIBSC SMENR Register Bit Definitions *****************************/

#define SPIBSC_SMENR_SPIDE_SHIFT                (0)      /* Bits 0-3: Spide */
#define SPIBSC_SMENR_SPIDE_MASK                 (0xf << SPIBSC_SMENR_SPIDE_SHIFT)

#define SPIBSC_SMENR_OPDE_SHIFT                 (4)      /* Bits 4-7: Opde */
#define SPIBSC_SMENR_OPDE_MASK                  (0xf << SPIBSC_SMENR_OPDE_SHIFT)

#define SPIBSC_SMENR_ADE_SHIFT                  (8)      /* Bits 8-11: Ade */
#define SPIBSC_SMENR_ADE_MASK                   (0xf << SPIBSC_SMENR_ADE_SHIFT)

#define SPIBSC_SMENR_OCDE                       (1 << 12)  /* Ocde */

#define SPIBSC_SMENR_CDE                        (1 << 14)  /* Cde */

#define SPIBSC_SMENR_DME                        (1 << 15)  /* Dme */

#define SPIBSC_SMENR_SPIDB_SHIFT                (16)      /* Bits 16-17: Spidb */
#define SPIBSC_SMENR_SPIDB_MASK                 (0x3 << SPIBSC_SMENR_SPIDB_SHIFT)

#define SPIBSC_SMENR_OPDB_SHIFT                 (20)      /* Bits 20-21: Opdb */
#define SPIBSC_SMENR_OPDB_MASK                  (0x3 << SPIBSC_SMENR_OPDB_SHIFT)

#define SPIBSC_SMENR_ADB_SHIFT                  (24)      /* Bits 24-25: Adb */
#define SPIBSC_SMENR_ADB_MASK                   (0x3 << SPIBSC_SMENR_ADB_SHIFT)

#define SPIBSC_SMENR_OCDB_SHIFT                 (28)      /* Bits 28-29: Ocdb */
#define SPIBSC_SMENR_OCDB_MASK                  (0x3 << SPIBSC_SMENR_OCDB_SHIFT)

#define SPIBSC_SMENR_CDB_SHIFT                  (30)      /* Bits 30-31: Cdb */
#define SPIBSC_SMENR_CDB_MASK                   (0x3 << SPIBSC_SMENR_CDB_SHIFT)

/* SPIBSC SMOPR Register Bit Definitions *****************************/

/* OPD fields (parameterized for indices 0-3) */
#define SPIBSC_SMOPR_OPD_SHIFT(n)                         ((unsigned)(0 + ((n) * 8)))  /* Bits for OPDn */
#define SPIBSC_SMOPR_OPD_MASK(n)                          (0xffu << SPIBSC_SMOPR_OPD_SHIFT(n))
#define SPIBSC_SMOPR_OPD_VAL(n,v)                         (((unsigned)(v) & 0xffu) << SPIBSC_SMOPR_OPD_SHIFT(n))

/* SPIBSC SMRDR0 Register Bit Definitions ****************************/

#define SPIBSC_SMRDR0_RDATA0_SHIFT              (0)      /* Bits 0-31: Rdata0 */
#define SPIBSC_SMRDR0_RDATA0_MASK               (0xffffffff << SPIBSC_SMRDR0_RDATA0_SHIFT)

/* SPIBSC SMRDR1 Register Bit Definitions ****************************/

#define SPIBSC_SMRDR1_RDATA1_SHIFT              (0)      /* Bits 0-31: Rdata1 */
#define SPIBSC_SMRDR1_RDATA1_MASK               (0xffffffff << SPIBSC_SMRDR1_RDATA1_SHIFT)

/* SPIBSC SMWDR0 Register Bit Definitions ****************************/

#define SPIBSC_SMWDR0_WDATA0_SHIFT              (0)      /* Bits 0-31: Wdata0 */
#define SPIBSC_SMWDR0_WDATA0_MASK               (0xffffffff << SPIBSC_SMWDR0_WDATA0_SHIFT)

/* SPIBSC SMWDR1 Register Bit Definitions ****************************/

#define SPIBSC_SMWDR1_WDATA1_SHIFT              (0)      /* Bits 0-31: Wdata1 */
#define SPIBSC_SMWDR1_WDATA1_MASK               (0xffffffff << SPIBSC_SMWDR1_WDATA1_SHIFT)

/* SPIBSC SSLDR Register Bit Definitions *****************************/

#define SPIBSC_SSLDR_SCKDL_SHIFT                (0)      /* Bits 0-2: Sckdl */
#define SPIBSC_SSLDR_SCKDL_MASK                 (0x7 << SPIBSC_SSLDR_SCKDL_SHIFT)

#define SPIBSC_SSLDR_SLNDL_SHIFT                (8)      /* Bits 8-10: Slndl */
#define SPIBSC_SSLDR_SLNDL_MASK                 (0x7 << SPIBSC_SSLDR_SLNDL_SHIFT)

#define SPIBSC_SSLDR_SPNDL_SHIFT                (16)      /* Bits 16-18: Spndl */
#define SPIBSC_SSLDR_SPNDL_MASK                 (0x7 << SPIBSC_SSLDR_SPNDL_SHIFT)

/* SPIBSC Channel definitions */
#define RZV_SPIBSC_CHANNEL_0       0

/* Maximum number of SPIBSC channels */
#define RZV_SPIBSC_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SPIBSC_H */
