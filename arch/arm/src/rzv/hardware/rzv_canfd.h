/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_canfd.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_CANFD_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_CANFD_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* CANFD Base Addresses **************************************************/

#ifndef RZV_CANFD0_BASE
#  define RZV_CANFD0_BASE             0x12440000
#endif
#ifndef RZV_CANFD1_BASE
#  define RZV_CANFD1_BASE             0x12440010
#endif
#ifndef RZV_CANFD2_BASE
#  define RZV_CANFD2_BASE             0x12440020
#endif
#ifndef RZV_CANFD3_BASE
#  define RZV_CANFD3_BASE             0x12440030
#endif
#ifndef RZV_CANFD4_BASE
#  define RZV_CANFD4_BASE             0x12440040
#endif
#ifndef RZV_CANFD5_BASE
#  define RZV_CANFD5_BASE             0x12440050
#endif

/* CANFD Register Offsets *************************************************/

#define RZV_CANFD_NCFG_OFFSET                            0x0000  /* NCFG */
#define RZV_CANFD_CTR_OFFSET                             0x0004  /* CTR */
#define RZV_CANFD_STS_OFFSET                             0x0008  /* STS */
#define RZV_CANFD_ERFL_OFFSET                            0x000C  /* ERFL */

/* CANFD Register Addresses ************************************************/

#define RZV_CANFD_NCFG(ch)                           (RZV_CANFD##ch##_BASE + RZV_CANFD_NCFG_OFFSET)
#define RZV_CANFD_CTR(ch)                            (RZV_CANFD##ch##_BASE + RZV_CANFD_CTR_OFFSET)
#define RZV_CANFD_STS(ch)                            (RZV_CANFD##ch##_BASE + RZV_CANFD_STS_OFFSET)
#define RZV_CANFD_ERFL(ch)                           (RZV_CANFD##ch##_BASE + RZV_CANFD_ERFL_OFFSET)

/* CANFD CFDC2_BLCT Register Bit Definitions *************************/

#define CANFD_CFDC2_BLCT_BLCE                   (1 << 0)  /* Blce */

#define CANFD_CFDC2_BLCT_BLCLD                  (1 << 8)  /* Blcld */

/* CANFD CFDC2_DCFG Register Bit Definitions *************************/

#define CANFD_CFDC2_DCFG_DBRP_SHIFT             (0)      /* Bits 0-7: Dbrp */
#define CANFD_CFDC2_DCFG_DBRP_MASK              (0xff << CANFD_CFDC2_DCFG_DBRP_SHIFT)

#define CANFD_CFDC2_DCFG_DTSEG1_SHIFT           (8)      /* Bits 8-12: Dtseg1 */
#define CANFD_CFDC2_DCFG_DTSEG1_MASK            (0x1f << CANFD_CFDC2_DCFG_DTSEG1_SHIFT)

#define CANFD_CFDC2_DCFG_DTSEG2_SHIFT           (16)      /* Bits 16-19: Dtseg2 */
#define CANFD_CFDC2_DCFG_DTSEG2_MASK            (0xf << CANFD_CFDC2_DCFG_DTSEG2_SHIFT)

#define CANFD_CFDC2_DCFG_DSJW_SHIFT             (24)      /* Bits 24-27: Dsjw */
#define CANFD_CFDC2_DCFG_DSJW_MASK              (0xf << CANFD_CFDC2_DCFG_DSJW_SHIFT)

/* CANFD CFDC2_FDCFG Register Bit Definitions ************************/

#define CANFD_CFDC2_FDCFG_EOCCFG_SHIFT          (0)      /* Bits 0-2: Eoccfg */
#define CANFD_CFDC2_FDCFG_EOCCFG_MASK           (0x7 << CANFD_CFDC2_FDCFG_EOCCFG_SHIFT)

#define CANFD_CFDC2_FDCFG_TDCOC                 (1 << 8)  /* Tdcoc */

#define CANFD_CFDC2_FDCFG_TDCE                  (1 << 9)  /* Tdce */

#define CANFD_CFDC2_FDCFG_ESIC                  (1 << 10)  /* Esic */

#define CANFD_CFDC2_FDCFG_TDCO_SHIFT            (16)      /* Bits 16-23: Tdco */
#define CANFD_CFDC2_FDCFG_TDCO_MASK             (0xff << CANFD_CFDC2_FDCFG_TDCO_SHIFT)

#define CANFD_CFDC2_FDCFG_GWEN                  (1 << 24)  /* Gwen */

#define CANFD_CFDC2_FDCFG_GWFDF                 (1 << 25)  /* Gwfdf */

#define CANFD_CFDC2_FDCFG_GWBRS                 (1 << 26)  /* Gwbrs */

#define CANFD_CFDC2_FDCFG_FDOE                  (1 << 28)  /* Fdoe */

#define CANFD_CFDC2_FDCFG_REFE                  (1 << 29)  /* Refe */

#define CANFD_CFDC2_FDCFG_CLOE                  (1 << 30)  /* Cloe */

#define CANFD_CFDC2_FDCFG_CFDTE                 (1 << 31)  /* Cfdte */

/* CANFD CFDC2_FDCRC Register Bit Definitions ************************/

#define CANFD_CFDC2_FDCRC_CRCREG_SHIFT          (0)      /* Bits 0-20: Crcreg */
#define CANFD_CFDC2_FDCRC_CRCREG_MASK           (0x1fffff << CANFD_CFDC2_FDCRC_CRCREG_SHIFT)

#define CANFD_CFDC2_FDCRC_SCNT_SHIFT            (25)      /* Bits 25-28: Scnt */
#define CANFD_CFDC2_FDCRC_SCNT_MASK             (0xf << CANFD_CFDC2_FDCRC_SCNT_SHIFT)

/* CANFD CFDCDTCT Register Bit Definitions ***************************/

/* CFDMAE fields (parameterized for indices 0-5) */
#define CANFD_CFDCDTCT_CFDMAE(n)                          (1u << (8 + ((unsigned)(n) * 1)))  /* Cfdmae0 */

/* RFDMAE fields (parameterized for indices 0-7) */
#define CANFD_CFDCDTCT_RFDMAE(n)                          (1u << (0 + ((unsigned)(n) * 1)))  /* Rfdmae0 */

/* CANFD CFDCDTTCT Register Bit Definitions **************************/

/* CFDMAE fields (parameterized for indices 0-5) */
#define CANFD_CFDCDTTCT_CFDMAE(n)                         (1u << (16 + ((unsigned)(n) * 1)))  /* Cfdmae0 */

#define CANFD_CFDCDTTCT_TQ0DMAE0                (1 << 0)  /* Tq0Dmae0 */

#define CANFD_CFDCDTTCT_TQ0DMAE1                (1 << 1)  /* Tq0Dmae1 */

#define CANFD_CFDCDTTCT_TQ0DMAE2                (1 << 2)  /* Tq0Dmae2 */

#define CANFD_CFDCDTTCT_TQ0DMAE3                (1 << 3)  /* Tq0Dmae3 */

#define CANFD_CFDCDTTCT_TQ0DMAE4                (1 << 4)  /* Tq0Dmae4 */

#define CANFD_CFDCDTTCT_TQ0DMAE5                (1 << 5)  /* Tq0Dmae5 */

#define CANFD_CFDCDTTCT_TQ3DMAE0                (1 << 8)  /* Tq3Dmae0 */

#define CANFD_CFDCDTTCT_TQ3DMAE1                (1 << 9)  /* Tq3Dmae1 */

#define CANFD_CFDCDTTCT_TQ3DMAE2                (1 << 10)  /* Tq3Dmae2 */

#define CANFD_CFDCDTTCT_TQ3DMAE3                (1 << 11)  /* Tq3Dmae3 */

#define CANFD_CFDCDTTCT_TQ3DMAE4                (1 << 12)  /* Tq3Dmae4 */

#define CANFD_CFDCDTTCT_TQ3DMAE5                (1 << 13)  /* Tq3Dmae5 */

/* CANFD CFDCFCC Register Bit Definitions ****************************/

#define CANFD_CFDCFCC_CFE                       (1 << 0)  /* Cfe */

#define CANFD_CFDCFCC_CFRXIE                    (1 << 1)  /* Cfrxie */

#define CANFD_CFDCFCC_CFTXIE                    (1 << 2)  /* Cftxie */

#define CANFD_CFDCFCC_CFPLS_SHIFT               (4)      /* Bits 4-6: Cfpls */
#define CANFD_CFDCFCC_CFPLS_MASK                (0x7 << CANFD_CFDCFCC_CFPLS_SHIFT)

#define CANFD_CFDCFCC_CFM_SHIFT                 (8)      /* Bits 8-9: Cfm */
#define CANFD_CFDCFCC_CFM_MASK                  (0x3 << CANFD_CFDCFCC_CFM_SHIFT)

#define CANFD_CFDCFCC_CFITSS                    (1 << 10)  /* Cfitss */

#define CANFD_CFDCFCC_CFITR                     (1 << 11)  /* Cfitr */

#define CANFD_CFDCFCC_CFIM                      (1 << 12)  /* Cfim */

#define CANFD_CFDCFCC_CFIGCV_SHIFT              (13)      /* Bits 13-15: Cfigcv */
#define CANFD_CFDCFCC_CFIGCV_MASK               (0x7 << CANFD_CFDCFCC_CFIGCV_SHIFT)

#define CANFD_CFDCFCC_CFTML_SHIFT               (16)      /* Bits 16-20: Cftml */
#define CANFD_CFDCFCC_CFTML_MASK                (0x1f << CANFD_CFDCFCC_CFTML_SHIFT)

#define CANFD_CFDCFCC_CFDC_SHIFT                (21)      /* Bits 21-23: Cfdc */
#define CANFD_CFDCFCC_CFDC_MASK                 (0x7 << CANFD_CFDCFCC_CFDC_SHIFT)

#define CANFD_CFDCFCC_CFITT_SHIFT               (24)      /* Bits 24-31: Cfitt */
#define CANFD_CFDCFCC_CFITT_MASK                (0xff << CANFD_CFDCFCC_CFITT_SHIFT)

/* CANFD CFDCFCCE Register Bit Definitions ***************************/

#define CANFD_CFDCFCCE_CFFIE                    (1 << 0)  /* Cffie */

#define CANFD_CFDCFCCE_CFOFRXIE                 (1 << 1)  /* Cfofrxie */

#define CANFD_CFDCFCCE_CFOFTXIE                 (1 << 2)  /* Cfoftxie */

#define CANFD_CFDCFCCE_CFMOWM                   (1 << 8)  /* Cfmowm */

#define CANFD_CFDCFCCE_CFBME                    (1 << 16)  /* Cfbme */

/* CANFD CFDCF_DF Register Bit Definitions ***************************/

#define CANFD_CFDCF_DF_CFDB_SHIFT               (0)      /* Bits 0-7: Cfdb */
#define CANFD_CFDCF_DF_CFDB_MASK                (0xff << CANFD_CFDCF_DF_CFDB_SHIFT)

/* CANFD CFDCF_ID Register Bit Definitions ***************************/

#define CANFD_CFDCF_ID_CFID_SHIFT               (0)      /* Bits 0-28: Cfid */
#define CANFD_CFDCF_ID_CFID_MASK                (0x1fffffff << CANFD_CFDCF_ID_CFID_SHIFT)

#define CANFD_CFDCF_ID_THLEN29                  (1 << 29)  /* Thlen */

#define CANFD_CFDCF_ID_CFRTR                    (1 << 30)  /* Cfrtr */

#define CANFD_CFDCF_ID_CFIDE                    (1 << 31)  /* Cfide */

#define CANFD_CFDCF_ID_THLEN29                  (1 << 29)  /* Thlen */

/* CANFD CFDCF_PTR Register Bit Definitions **************************/

#define CANFD_CFDCF_PTR_CFTS_SHIFT              (0)      /* Bits 0-15: Cfts */
#define CANFD_CFDCF_PTR_CFTS_MASK               (0xffff << CANFD_CFDCF_PTR_CFTS_SHIFT)

#define CANFD_CFDCF_PTR_CFDLC_SHIFT             (28)      /* Bits 28-31: Cfdlc */
#define CANFD_CFDCF_PTR_CFDLC_MASK              (0xf << CANFD_CFDCF_PTR_CFDLC_SHIFT)

/* CANFD CFDGAFLCFG Register Bit Definitions *************************/

#define CANFD_CFDGAFLCFG_RNC1_SHIFT             (0)      /* Bits 0-8: Rnc1 */
#define CANFD_CFDGAFLCFG_RNC1_MASK              (0x1ff << CANFD_CFDGAFLCFG_RNC1_SHIFT)

#define CANFD_CFDGAFLCFG_RNC0_SHIFT             (16)      /* Bits 16-24: Rnc0 */
#define CANFD_CFDGAFLCFG_RNC0_MASK              (0x1ff << CANFD_CFDGAFLCFG_RNC0_SHIFT)

/* CANFD CFDGAFL_ID Register Bit Definitions *************************/

#define CANFD_CFDGAFL_ID_GAFLID_SHIFT           (0)      /* Bits 0-28: Gaflid */
#define CANFD_CFDGAFL_ID_GAFLID_MASK            (0x1fffffff << CANFD_CFDGAFL_ID_GAFLID_SHIFT)

#define CANFD_CFDGAFL_ID_GAFLLB                 (1 << 29)  /* Gafllb */

#define CANFD_CFDGAFL_ID_GAFLRTR                (1 << 30)  /* Gaflrtr */

#define CANFD_CFDGAFL_ID_GAFLIDE                (1 << 31)  /* Gaflide */

/* CANFD CFDGAFL_M Register Bit Definitions **************************/

#define CANFD_CFDGAFL_M_GAFLIDM_SHIFT           (0)      /* Bits 0-28: Gaflidm */
#define CANFD_CFDGAFL_M_GAFLIDM_MASK            (0x1fffffff << CANFD_CFDGAFL_M_GAFLIDM_SHIFT)

#define CANFD_CFDGAFL_M_GAFLIFL1                (1 << 29)  /* Gaflifl1 */

#define CANFD_CFDGAFL_M_GAFLRTRM                (1 << 30)  /* Gaflrtrm */

#define CANFD_CFDGAFL_M_GAFLIDEM                (1 << 31)  /* Gaflidem */

/* CANFD CFDGAFL_P0 Register Bit Definitions *************************/

/* GAFLSRD fields (parameterized for indices 0-2) */
#define CANFD_CFDGAFL_P0_GAFLSRD(n)                       (1u << (4 + ((unsigned)(n) * 1)))  /* Gaflsrd0 */

#define CANFD_CFDGAFL_P0_GAFLDLC_SHIFT          (0)      /* Bits 0-3: Gafldlc */
#define CANFD_CFDGAFL_P0_GAFLDLC_MASK           (0xf << CANFD_CFDGAFL_P0_GAFLDLC_SHIFT)

#define CANFD_CFDGAFL_P0_GAFLIFL0               (1 << 7)  /* Gaflifl0 */

#define CANFD_CFDGAFL_P0_GAFLRMDP_SHIFT         (8)      /* Bits 8-12: Gaflrmdp */
#define CANFD_CFDGAFL_P0_GAFLRMDP_MASK          (0x1f << CANFD_CFDGAFL_P0_GAFLRMDP_SHIFT)

#define CANFD_CFDGAFL_P0_GAFLRMV                (1 << 15)  /* Gaflrmv */

#define CANFD_CFDGAFL_P0_GAFLPTR_SHIFT          (16)      /* Bits 16-31: Gaflptr */
#define CANFD_CFDGAFL_P0_GAFLPTR_MASK           (0xffff << CANFD_CFDGAFL_P0_GAFLPTR_SHIFT)

/* CANFD CFDGAFL_P1 Register Bit Definitions *************************/

#define CANFD_CFDGAFL_P1_GAFLFDP_SHIFT          (0)      /* Bits 0-25: Gaflfdp */
#define CANFD_CFDGAFL_P1_GAFLFDP_MASK           (0x3ffffff << CANFD_CFDGAFL_P1_GAFLFDP_SHIFT)

/* CANFD CFDGCFG Register Bit Definitions ****************************/

#define CANFD_CFDGCFG_TPRI                      (1 << 0)  /* Tpri */

#define CANFD_CFDGCFG_DCE                       (1 << 1)  /* Dce */

#define CANFD_CFDGCFG_DRE                       (1 << 2)  /* Dre */

#define CANFD_CFDGCFG_MME                       (1 << 3)  /* Mme */

#define CANFD_CFDGCFG_DCS                       (1 << 4)  /* Dcs */

#define CANFD_CFDGCFG_CMPOC                     (1 << 5)  /* Cmpoc */

#define CANFD_CFDGCFG_TSP_SHIFT                 (8)      /* Bits 8-11: Tsp */
#define CANFD_CFDGCFG_TSP_MASK                  (0xf << CANFD_CFDGCFG_TSP_SHIFT)

#define CANFD_CFDGCFG_TSSS                      (1 << 12)  /* Tsss */

#define CANFD_CFDGCFG_TSBTCS_SHIFT              (13)      /* Bits 13-15: Tsbtcs */
#define CANFD_CFDGCFG_TSBTCS_MASK               (0x7 << CANFD_CFDGCFG_TSBTCS_SHIFT)

#define CANFD_CFDGCFG_ITRCP_SHIFT               (16)      /* Bits 16-31: Itrcp */
#define CANFD_CFDGCFG_ITRCP_MASK                (0xffff << CANFD_CFDGCFG_ITRCP_SHIFT)

/* CANFD CFDGFCMC Register Bit Definitions ***************************/

#define CANFD_CFDGFCMC_FLXC0                    (1 << 0)  /* Flxc0 */

#define CANFD_CFDGFCMC_FLXC1                    (1 << 1)  /* Flxc1 */

#define CANFD_CFDGFCMC_FLXC3                    (1 << 2)  /* Flxc3 */

/* CANFD CFDGFDCFG Register Bit Definitions **************************/

#define CANFD_CFDGFDCFG_RPED                    (1 << 0)  /* Rped */

#define CANFD_CFDGFDCFG_TSCCFG_SHIFT            (8)      /* Bits 8-9: Tsccfg */
#define CANFD_CFDGFDCFG_TSCCFG_MASK             (0x3 << CANFD_CFDGFDCFG_TSCCFG_SHIFT)

/* CANFD CFDGFTBAC Register Bit Definitions **************************/

#define CANFD_CFDGFTBAC_FLXMB0_SHIFT            (0)      /* Bits 0-3: Flxmb0 */
#define CANFD_CFDGFTBAC_FLXMB0_MASK             (0xf << CANFD_CFDGFTBAC_FLXMB0_SHIFT)

#define CANFD_CFDGFTBAC_FLXMB1_SHIFT            (8)      /* Bits 8-11: Flxmb1 */
#define CANFD_CFDGFTBAC_FLXMB1_MASK             (0xf << CANFD_CFDGFTBAC_FLXMB1_SHIFT)

#define CANFD_CFDGFTBAC_FLXMB3_SHIFT            (16)      /* Bits 16-19: Flxmb3 */
#define CANFD_CFDGFTBAC_FLXMB3_MASK             (0xf << CANFD_CFDGFTBAC_FLXMB3_SHIFT)

/* CANFD CFDGIPV Register Bit Definitions ****************************/

#define CANFD_CFDGIPV_IPV_SHIFT                 (0)      /* Bits 0-7: Ipv */
#define CANFD_CFDGIPV_IPV_MASK                  (0xff << CANFD_CFDGIPV_IPV_SHIFT)

#define CANFD_CFDGIPV_IPT_SHIFT                 (8)      /* Bits 8-9: Ipt */
#define CANFD_CFDGIPV_IPT_MASK                  (0x3 << CANFD_CFDGIPV_IPT_SHIFT)

#define CANFD_CFDGIPV_PSI_SHIFT                 (16)      /* Bits 16-29: Psi */
#define CANFD_CFDGIPV_PSI_MASK                  (0x3fff << CANFD_CFDGIPV_PSI_SHIFT)

/* CANFD CFDGLOCKK Register Bit Definitions **************************/

#define CANFD_CFDGLOCKK_LOCK_SHIFT              (0)      /* Bits 0-15: Lock */
#define CANFD_CFDGLOCKK_LOCK_MASK               (0xffff << CANFD_CFDGLOCKK_LOCK_SHIFT)

/* CANFD CFDGRSTC Register Bit Definitions ***************************/

#define CANFD_CFDGRSTC_SRST                     (1 << 0)  /* Srst */

#define CANFD_CFDGRSTC_KEY_SHIFT                (8)      /* Bits 8-15: Key */
#define CANFD_CFDGRSTC_KEY_MASK                 (0xff << CANFD_CFDGRSTC_KEY_SHIFT)

/* CANFD CFDGTINTSTS0 Register Bit Definitions ***********************/

/* CFOTIF fields (parameterized for indices 0-3) */
#define CANFD_CFDGTINTSTS0_CFOTIF(n)                      (1u << (6 + ((unsigned)(n) * 8)))  /* Cfotif0 */

/* CFTIF fields (parameterized for indices 0-3) */
#define CANFD_CFDGTINTSTS0_CFTIF(n)                       (1u << (3 + ((unsigned)(n) * 8)))  /* Cftif0 */

/* TAIF fields (parameterized for indices 0-3) */
#define CANFD_CFDGTINTSTS0_TAIF(n)                        (1u << (1 + ((unsigned)(n) * 8)))  /* Taif0 */

/* THIF fields (parameterized for indices 0-3) */
#define CANFD_CFDGTINTSTS0_THIF(n)                        (1u << (4 + ((unsigned)(n) * 8)))  /* Thif0 */

/* TQIF fields (parameterized for indices 0-3) */
#define CANFD_CFDGTINTSTS0_TQIF(n)                        (1u << (2 + ((unsigned)(n) * 8)))  /* Tqif0 */

/* TQOFIF fields (parameterized for indices 0-3) */
#define CANFD_CFDGTINTSTS0_TQOFIF(n)                      (1u << (5 + ((unsigned)(n) * 8)))  /* Tqofif0 */

/* TSIF fields (parameterized for indices 0-3) */
#define CANFD_CFDGTINTSTS0_TSIF(n)                        (1u << (0 + ((unsigned)(n) * 8)))  /* Tsif0 */

/* CANFD CFDGTINTSTS1 Register Bit Definitions ***********************/

#define CANFD_CFDGTINTSTS1_TSIF4                (1 << 0)  /* Tsif4 */

#define CANFD_CFDGTINTSTS1_TAIF4                (1 << 1)  /* Taif4 */

#define CANFD_CFDGTINTSTS1_TQIF4                (1 << 2)  /* Tqif4 */

#define CANFD_CFDGTINTSTS1_CFTIF4               (1 << 3)  /* Cftif4 */

#define CANFD_CFDGTINTSTS1_THIF4                (1 << 4)  /* Thif4 */

#define CANFD_CFDGTINTSTS1_TQOFIF4              (1 << 5)  /* Tqofif4 */

#define CANFD_CFDGTINTSTS1_CFOTIF4              (1 << 6)  /* Cfotif4 */

#define CANFD_CFDGTINTSTS1_TSIF5                (1 << 8)  /* Tsif5 */

#define CANFD_CFDGTINTSTS1_TAIF5                (1 << 9)  /* Taif5 */

#define CANFD_CFDGTINTSTS1_TQIF5                (1 << 10)  /* Tqif5 */

#define CANFD_CFDGTINTSTS1_CFTIF5               (1 << 11)  /* Cftif5 */

#define CANFD_CFDGTINTSTS1_THIF5                (1 << 12)  /* Thif5 */

#define CANFD_CFDGTINTSTS1_TQOFIF5              (1 << 13)  /* Tqofif5 */

#define CANFD_CFDGTINTSTS1_CFOTIF5              (1 << 14)  /* Cfotif5 */

/* CANFD CFDGTSC Register Bit Definitions ****************************/

#define CANFD_CFDGTSC_TS_SHIFT                  (0)      /* Bits 0-15: Ts */
#define CANFD_CFDGTSC_TS_MASK                   (0xffff << CANFD_CFDGTSC_TS_SHIFT)

/* CANFD CFDGTSTCFG Register Bit Definitions *************************/

#define CANFD_CFDGTSTCFG_C0ICBCE                (1 << 0)  /* C0Icbce */

#define CANFD_CFDGTSTCFG_C1ICBCE                (1 << 1)  /* C1Icbce */

#define CANFD_CFDGTSTCFG_C2ICBCE                (1 << 2)  /* C2Icbce */

#define CANFD_CFDGTSTCFG_C3ICBCE                (1 << 3)  /* C3Icbce */

#define CANFD_CFDGTSTCFG_C4ICBCE                (1 << 4)  /* C4Icbce */

#define CANFD_CFDGTSTCFG_C5ICBCE                (1 << 5)  /* C5Icbce */

#define CANFD_CFDGTSTCFG_RTMPS_SHIFT            (16)      /* Bits 16-25: Rtmps */
#define CANFD_CFDGTSTCFG_RTMPS_MASK             (0x3ff << CANFD_CFDGTSTCFG_RTMPS_SHIFT)

/* CANFD CFDRFCC Register Bit Definitions ****************************/

#define CANFD_CFDRFCC_RFE                       (1 << 0)  /* Rfe */

#define CANFD_CFDRFCC_RFIE                      (1 << 1)  /* Rfie */

#define CANFD_CFDRFCC_RFPLS_SHIFT               (4)      /* Bits 4-6: Rfpls */
#define CANFD_CFDRFCC_RFPLS_MASK                (0x7 << CANFD_CFDRFCC_RFPLS_SHIFT)

#define CANFD_CFDRFCC_RFDC_SHIFT                (8)      /* Bits 8-10: Rfdc */
#define CANFD_CFDRFCC_RFDC_MASK                 (0x7 << CANFD_CFDRFCC_RFDC_SHIFT)

#define CANFD_CFDRFCC_RFIM                      (1 << 12)  /* Rfim */

#define CANFD_CFDRFCC_RFIGCV_SHIFT              (13)      /* Bits 13-15: Rfigcv */
#define CANFD_CFDRFCC_RFIGCV_MASK               (0x7 << CANFD_CFDRFCC_RFIGCV_SHIFT)

#define CANFD_CFDRFCC_RFFIE                     (1 << 16)  /* Rffie */

/* CANFD CFDRF_DF Register Bit Definitions ***************************/

#define CANFD_CFDRF_DF_RFDB_SHIFT               (0)      /* Bits 0-7: Rfdb */
#define CANFD_CFDRF_DF_RFDB_MASK                (0xff << CANFD_CFDRF_DF_RFDB_SHIFT)

/* CANFD CFDRF_ID Register Bit Definitions ***************************/

#define CANFD_CFDRF_ID_RFID_SHIFT               (0)      /* Bits 0-28: Rfid */
#define CANFD_CFDRF_ID_RFID_MASK                (0x1fffffff << CANFD_CFDRF_ID_RFID_SHIFT)

#define CANFD_CFDRF_ID_RFRTR                    (1 << 30)  /* Rfrtr */

#define CANFD_CFDRF_ID_RFIDE                    (1 << 31)  /* Rfide */

/* CANFD CFDRF_PTR Register Bit Definitions **************************/

#define CANFD_CFDRF_PTR_RFTS_SHIFT              (0)      /* Bits 0-15: Rfts */
#define CANFD_CFDRF_PTR_RFTS_MASK               (0xffff << CANFD_CFDRF_PTR_RFTS_SHIFT)

#define CANFD_CFDRF_PTR_RFDLC_SHIFT             (28)      /* Bits 28-31: Rfdlc */
#define CANFD_CFDRF_PTR_RFDLC_MASK              (0xf << CANFD_CFDRF_PTR_RFDLC_SHIFT)

/* CANFD CFDRMNB Register Bit Definitions ****************************/

#define CANFD_CFDRMNB_NRXMB_SHIFT               (0)      /* Bits 0-7: Nrxmb */
#define CANFD_CFDRMNB_NRXMB_MASK                (0xff << CANFD_CFDRMNB_NRXMB_SHIFT)

#define CANFD_CFDRMNB_RMPLS_SHIFT               (8)      /* Bits 8-10: Rmpls */
#define CANFD_CFDRMNB_RMPLS_MASK                (0x7 << CANFD_CFDRMNB_RMPLS_SHIFT)

/* CANFD CFDRMND Register Bit Definitions ****************************/

#define CANFD_CFDRMND_RMNS_SHIFT                (0)      /* Bits 0-31: Rmns */
#define CANFD_CFDRMND_RMNS_MASK                 (0xffffffff << CANFD_CFDRMND_RMNS_SHIFT)

/* CANFD CFDRM_DF Register Bit Definitions ***************************/

#define CANFD_CFDRM_DF_RMDB_SHIFT               (0)      /* Bits 0-7: Rmdb */
#define CANFD_CFDRM_DF_RMDB_MASK                (0xff << CANFD_CFDRM_DF_RMDB_SHIFT)

/* CANFD CFDRM_ID Register Bit Definitions ***************************/

#define CANFD_CFDRM_ID_RMID_SHIFT               (0)      /* Bits 0-28: Rmid */
#define CANFD_CFDRM_ID_RMID_MASK                (0x1fffffff << CANFD_CFDRM_ID_RMID_SHIFT)

#define CANFD_CFDRM_ID_RMRTR                    (1 << 30)  /* Rmrtr */

#define CANFD_CFDRM_ID_RMIDE                    (1 << 31)  /* Rmide */

/* CANFD CFDRM_PTR Register Bit Definitions **************************/

#define CANFD_CFDRM_PTR_RMTS_SHIFT              (0)      /* Bits 0-15: Rmts */
#define CANFD_CFDRM_PTR_RMTS_MASK               (0xffff << CANFD_CFDRM_PTR_RMTS_SHIFT)

#define CANFD_CFDRM_PTR_RMDLC_SHIFT             (28)      /* Bits 28-31: Rmdlc */
#define CANFD_CFDRM_PTR_RMDLC_MASK              (0xf << CANFD_CFDRM_PTR_RMDLC_SHIFT)

/* CANFD CFDRPGACC Register Bit Definitions **************************/

#define CANFD_CFDRPGACC_RDTA_SHIFT              (0)      /* Bits 0-31: Rdta */
#define CANFD_CFDRPGACC_RDTA_MASK               (0xffffffff << CANFD_CFDRPGACC_RDTA_SHIFT)

/* CANFD CFDTHL Register Bit Definitions *****************************/

#define CANFD_CFDTHL_ACC0_BT_SHIFT              (0)      /* Bits 0-2: Acc0 Bt */
#define CANFD_CFDTHL_ACC0_BT_MASK               (0x7 << CANFD_CFDTHL_ACC0_BT_SHIFT)

#define CANFD_CFDTHL_ACC0_BN_SHIFT              (3)      /* Bits 3-9: Acc0 Bn */
#define CANFD_CFDTHL_ACC0_BN_MASK               (0x7f << CANFD_CFDTHL_ACC0_BN_SHIFT)

/* CANFD CFDTHLCC Register Bit Definitions ***************************/

#define CANFD_CFDTHLCC_THLE                     (1 << 0)  /* Thle */

#define CANFD_CFDTHLCC_THLIE                    (1 << 8)  /* Thlie */

#define CANFD_CFDTHLCC_THLIM                    (1 << 9)  /* Thlim */

#define CANFD_CFDTHLCC_THLDTE                   (1 << 10)  /* Thldte */

#define CANFD_CFDTHLCC_THLDGE                   (1 << 11)  /* Thldge */

/* CANFD CFDTHL_ACC0 Register Bit Definitions ************************/

#define CANFD_CFDTHL_ACC0_TGW                   (1 << 15)  /* Tgw */

#define CANFD_CFDTHL_ACC0_TMTS_SHIFT            (16)      /* Bits 16-31: Tmts */
#define CANFD_CFDTHL_ACC0_TMTS_MASK             (0xffff << CANFD_CFDTHL_ACC0_TMTS_SHIFT)

/* CANFD CFDTHL_ACC1 Register Bit Definitions ************************/

#define CANFD_CFDTHL_ACC1_TID_SHIFT             (0)      /* Bits 0-15: Tid */
#define CANFD_CFDTHL_ACC1_TID_MASK              (0xffff << CANFD_CFDTHL_ACC1_TID_SHIFT)

#define CANFD_CFDTHL_ACC1_TIFL_SHIFT            (16)      /* Bits 16-17: Tifl */
#define CANFD_CFDTHL_ACC1_TIFL_MASK             (0x3 << CANFD_CFDTHL_ACC1_TIFL_SHIFT)

/* CANFD CFDTMC Register Bit Definitions *****************************/

#define CANFD_CFDTMC_TMTR                       (1 << 0)  /* Tmtr */

#define CANFD_CFDTMC_TMTAR                      (1 << 1)  /* Tmtar */

#define CANFD_CFDTMC_TMOM                       (1 << 2)  /* Tmom */

/* CANFD CFDTMIEC Register Bit Definitions ***************************/

#define CANFD_CFDTMIEC_TMIE_SHIFT               (0)      /* Bits 0-15: Tmie */
#define CANFD_CFDTMIEC_TMIE_MASK                (0xffff << CANFD_CFDTMIEC_TMIE_SHIFT)

/* CANFD CFDTM_DF Register Bit Definitions ***************************/

#define CANFD_CFDTM_DF_TMDB_SHIFT               (0)      /* Bits 0-7: Tmdb */
#define CANFD_CFDTM_DF_TMDB_MASK                (0xff << CANFD_CFDTM_DF_TMDB_SHIFT)

/* CANFD CFDTM_ID Register Bit Definitions ***************************/

#define CANFD_CFDTM_ID_TMID_SHIFT               (0)      /* Bits 0-28: Tmid */
#define CANFD_CFDTM_ID_TMID_MASK                (0x1fffffff << CANFD_CFDTM_ID_TMID_SHIFT)

#define CANFD_CFDTM_ID_TMRTR                    (1 << 30)  /* Tmrtr */

#define CANFD_CFDTM_ID_TMIDE                    (1 << 31)  /* Tmide */

/* CANFD CFDTM_PTR Register Bit Definitions **************************/

#define CANFD_CFDTM_PTR_TMDLC_SHIFT             (28)      /* Bits 28-31: Tmdlc */
#define CANFD_CFDTM_PTR_TMDLC_MASK              (0xf << CANFD_CFDTM_PTR_TMDLC_SHIFT)

/* CANFD CFDTXQCC0 Register Bit Definitions **************************/

#define CANFD_CFDTXQCC0_TXQE                    (1 << 0)  /* Txqe */

#define CANFD_CFDTXQCC0_TXQGWE                  (1 << 1)  /* Txqgwe */

#define CANFD_CFDTXQCC0_TXQOWE                  (1 << 2)  /* Txqowe */

#define CANFD_CFDTXQCC0_TXQTXIE                 (1 << 5)  /* Txqtxie */

#define CANFD_CFDTXQCC0_TXQIM                   (1 << 7)  /* Txqim */

#define CANFD_CFDTXQCC0_TXQDC_SHIFT             (8)      /* Bits 8-12: Txqdc */
#define CANFD_CFDTXQCC0_TXQDC_MASK              (0x1f << CANFD_CFDTXQCC0_TXQDC_SHIFT)

#define CANFD_CFDTXQCC0_TXQFIE                  (1 << 16)  /* Txqfie */

#define CANFD_CFDTXQCC0_TXQOFRXIE               (1 << 17)  /* Txqofrxie */

#define CANFD_CFDTXQCC0_TXQOFTXIE               (1 << 18)  /* Txqoftxie */

/* CANFD CFDTXQCC1 Register Bit Definitions **************************/

#define CANFD_CFDTXQCC1_TXQE                    (1 << 0)  /* Txqe */

#define CANFD_CFDTXQCC1_TXQGWE                  (1 << 1)  /* Txqgwe */

#define CANFD_CFDTXQCC1_TXQOWE                  (1 << 2)  /* Txqowe */

#define CANFD_CFDTXQCC1_TXQTXIE                 (1 << 5)  /* Txqtxie */

#define CANFD_CFDTXQCC1_TXQIM                   (1 << 7)  /* Txqim */

#define CANFD_CFDTXQCC1_TXQDC_SHIFT             (8)      /* Bits 8-12: Txqdc */
#define CANFD_CFDTXQCC1_TXQDC_MASK              (0x1f << CANFD_CFDTXQCC1_TXQDC_SHIFT)

#define CANFD_CFDTXQCC1_TXQFIE                  (1 << 16)  /* Txqfie */

#define CANFD_CFDTXQCC1_TXQOFRXIE               (1 << 17)  /* Txqofrxie */

#define CANFD_CFDTXQCC1_TXQOFTXIE               (1 << 18)  /* Txqoftxie */

/* CANFD CFDTXQCC2 Register Bit Definitions **************************/

#define CANFD_CFDTXQCC2_TXQE                    (1 << 0)  /* Txqe */

#define CANFD_CFDTXQCC2_TXQGWE                  (1 << 1)  /* Txqgwe */

#define CANFD_CFDTXQCC2_TXQOWE                  (1 << 2)  /* Txqowe */

#define CANFD_CFDTXQCC2_TXQTXIE                 (1 << 5)  /* Txqtxie */

#define CANFD_CFDTXQCC2_TXQIM                   (1 << 7)  /* Txqim */

#define CANFD_CFDTXQCC2_TXQDC_SHIFT             (8)      /* Bits 8-12: Txqdc */
#define CANFD_CFDTXQCC2_TXQDC_MASK              (0x1f << CANFD_CFDTXQCC2_TXQDC_SHIFT)

#define CANFD_CFDTXQCC2_TXQFIE                  (1 << 16)  /* Txqfie */

#define CANFD_CFDTXQCC2_TXQOFRXIE               (1 << 17)  /* Txqofrxie */

#define CANFD_CFDTXQCC2_TXQOFTXIE               (1 << 18)  /* Txqoftxie */

/* CANFD CFDTXQCC3 Register Bit Definitions **************************/

#define CANFD_CFDTXQCC3_TXQE                    (1 << 0)  /* Txqe */

#define CANFD_CFDTXQCC3_TXQOWE                  (1 << 2)  /* Txqowe */

#define CANFD_CFDTXQCC3_TXQTXIE                 (1 << 5)  /* Txqtxie */

#define CANFD_CFDTXQCC3_TXQIM                   (1 << 7)  /* Txqim */

#define CANFD_CFDTXQCC3_TXQDC_SHIFT             (8)      /* Bits 8-12: Txqdc */
#define CANFD_CFDTXQCC3_TXQDC_MASK              (0x1f << CANFD_CFDTXQCC3_TXQDC_SHIFT)

#define CANFD_CFDTXQCC3_TXQOFTXIE               (1 << 18)  /* Txqoftxie */

/* CANFD CFDTXQPCTR0 Register Bit Definitions ************************/

#define CANFD_CFDTXQPCTR0_TXQPC_SHIFT           (0)      /* Bits 0-7: Txqpc */
#define CANFD_CFDTXQPCTR0_TXQPC_MASK            (0xff << CANFD_CFDTXQPCTR0_TXQPC_SHIFT)

/* CANFD CFDTXQPCTR1 Register Bit Definitions ************************/

#define CANFD_CFDTXQPCTR1_TXQPC_SHIFT           (0)      /* Bits 0-7: Txqpc */
#define CANFD_CFDTXQPCTR1_TXQPC_MASK            (0xff << CANFD_CFDTXQPCTR1_TXQPC_SHIFT)

/* CANFD CFDTXQPCTR2 Register Bit Definitions ************************/

#define CANFD_CFDTXQPCTR2_TXQPC_SHIFT           (0)      /* Bits 0-7: Txqpc */
#define CANFD_CFDTXQPCTR2_TXQPC_MASK            (0xff << CANFD_CFDTXQPCTR2_TXQPC_SHIFT)

/* CANFD CFDTXQPCTR3 Register Bit Definitions ************************/

#define CANFD_CFDTXQPCTR3_TXQPC_SHIFT           (0)      /* Bits 0-7: Txqpc */
#define CANFD_CFDTXQPCTR3_TXQPC_MASK            (0xff << CANFD_CFDTXQPCTR3_TXQPC_SHIFT)

/* CANFD CFDTXQSTS0 Register Bit Definitions *************************/

#define CANFD_CFDTXQSTS0_TXQEMP                 (1 << 0)  /* Txqemp */

#define CANFD_CFDTXQSTS0_TXQFLL                 (1 << 1)  /* Txqfll */

#define CANFD_CFDTXQSTS0_TXQTXIF                (1 << 2)  /* Txqtxif */

#define CANFD_CFDTXQSTS0_TXQMC_SHIFT            (8)      /* Bits 8-13: Txqmc */
#define CANFD_CFDTXQSTS0_TXQMC_MASK             (0x3f << CANFD_CFDTXQSTS0_TXQMC_SHIFT)

#define CANFD_CFDTXQSTS0_TXQFIF                 (1 << 16)  /* Txqfif */

#define CANFD_CFDTXQSTS0_TXQOFRXIF              (1 << 17)  /* Txqofrxif */

#define CANFD_CFDTXQSTS0_TXQOFTXIF              (1 << 18)  /* Txqoftxif */

#define CANFD_CFDTXQSTS0_TXQMLT                 (1 << 19)  /* Txqmlt */

#define CANFD_CFDTXQSTS0_TXQMOW                 (1 << 20)  /* Txqmow */

/* CANFD CFDTXQSTS1 Register Bit Definitions *************************/

#define CANFD_CFDTXQSTS1_TXQEMP                 (1 << 0)  /* Txqemp */

#define CANFD_CFDTXQSTS1_TXQFLL                 (1 << 1)  /* Txqfll */

#define CANFD_CFDTXQSTS1_TXQTXIF                (1 << 2)  /* Txqtxif */

#define CANFD_CFDTXQSTS1_TXQMC_SHIFT            (8)      /* Bits 8-13: Txqmc */
#define CANFD_CFDTXQSTS1_TXQMC_MASK             (0x3f << CANFD_CFDTXQSTS1_TXQMC_SHIFT)

#define CANFD_CFDTXQSTS1_TXQFIF                 (1 << 16)  /* Txqfif */

#define CANFD_CFDTXQSTS1_TXQOFRXIF              (1 << 17)  /* Txqofrxif */

#define CANFD_CFDTXQSTS1_TXQOFTXIF              (1 << 18)  /* Txqoftxif */

#define CANFD_CFDTXQSTS1_TXQMLT                 (1 << 19)  /* Txqmlt */

#define CANFD_CFDTXQSTS1_TXQMOW                 (1 << 20)  /* Txqmow */

/* CANFD CFDTXQSTS2 Register Bit Definitions *************************/

#define CANFD_CFDTXQSTS2_TXQEMP                 (1 << 0)  /* Txqemp */

#define CANFD_CFDTXQSTS2_TXQFLL                 (1 << 1)  /* Txqfll */

#define CANFD_CFDTXQSTS2_TXQTXIF                (1 << 2)  /* Txqtxif */

#define CANFD_CFDTXQSTS2_TXQMC_SHIFT            (8)      /* Bits 8-13: Txqmc */
#define CANFD_CFDTXQSTS2_TXQMC_MASK             (0x3f << CANFD_CFDTXQSTS2_TXQMC_SHIFT)

#define CANFD_CFDTXQSTS2_TXQFIF                 (1 << 16)  /* Txqfif */

#define CANFD_CFDTXQSTS2_TXQOFRXIF              (1 << 17)  /* Txqofrxif */

#define CANFD_CFDTXQSTS2_TXQOFTXIF              (1 << 18)  /* Txqoftxif */

#define CANFD_CFDTXQSTS2_TXQMLT                 (1 << 19)  /* Txqmlt */

#define CANFD_CFDTXQSTS2_TXQMOW                 (1 << 20)  /* Txqmow */

/* CANFD CFDTXQSTS3 Register Bit Definitions *************************/

#define CANFD_CFDTXQSTS3_TXQEMP                 (1 << 0)  /* Txqemp */

#define CANFD_CFDTXQSTS3_TXQFLL                 (1 << 1)  /* Txqfll */

#define CANFD_CFDTXQSTS3_TXQTXIF                (1 << 2)  /* Txqtxif */

#define CANFD_CFDTXQSTS3_TXQMC_SHIFT            (8)      /* Bits 8-13: Txqmc */
#define CANFD_CFDTXQSTS3_TXQMC_MASK             (0x3f << CANFD_CFDTXQSTS3_TXQMC_SHIFT)

#define CANFD_CFDTXQSTS3_TXQOFTXIF              (1 << 18)  /* Txqoftxif */

#define CANFD_CFDTXQSTS3_TXQMOW                 (1 << 20)  /* Txqmow */

/* CANFD CTR Register Bit Definitions ********************************/

#define CANFD_CTR_CHMDC_SHIFT                   (0)      /* Bits 0-1: Chmdc */
#define CANFD_CTR_CHMDC_MASK                    (0x3 << CANFD_CTR_CHMDC_SHIFT)

#define CANFD_CTR_CSLPR                         (1 << 2)  /* Cslpr */

#define CANFD_CTR_RTBO                          (1 << 3)  /* Rtbo */

#define CANFD_CTR_BEIE                          (1 << 8)  /* Beie */

#define CANFD_CTR_EWIE                          (1 << 9)  /* Ewie */

#define CANFD_CTR_EPIE                          (1 << 10)  /* Epie */

#define CANFD_CTR_BOEIE                         (1 << 11)  /* Boeie */

#define CANFD_CTR_BORIE                         (1 << 12)  /* Borie */

#define CANFD_CTR_OLIE                          (1 << 13)  /* Olie */

#define CANFD_CTR_BLIE                          (1 << 14)  /* Blie */

#define CANFD_CTR_ALIE                          (1 << 15)  /* Alie */

#define CANFD_CTR_TAIE                          (1 << 16)  /* Taie */

#define CANFD_CTR_EOCOIE                        (1 << 17)  /* Eocoie */

#define CANFD_CTR_SOCOIE                        (1 << 18)  /* Socoie */

#define CANFD_CTR_TDCVFIE                       (1 << 19)  /* Tdcvfie */

#define CANFD_CTR_BOM_SHIFT                     (21)      /* Bits 21-22: Bom */
#define CANFD_CTR_BOM_MASK                      (0x3 << CANFD_CTR_BOM_SHIFT)

#define CANFD_CTR_ERRD                          (1 << 23)  /* Errd */

#define CANFD_CTR_CTME                          (1 << 24)  /* Ctme */

#define CANFD_CTR_CTMS_SHIFT                    (25)      /* Bits 25-26: Ctms */
#define CANFD_CTR_CTMS_MASK                     (0x3 << CANFD_CTR_CTMS_SHIFT)

#define CANFD_CTR_CRCT                          (1 << 30)  /* Crct */

#define CANFD_CTR_ROM                           (1 << 31)  /* Rom */

#define CANFD_CTR_EOCCLR                        (1 << 0)  /* Eocclr */

#define CANFD_CTR_SOCCLR                        (1 << 1)  /* Socclr */

#define CANFD_CTR_TMESI                         (1 << 0)  /* Tmesi */

#define CANFD_CTR_TMBRS                         (1 << 1)  /* Tmbrs */

#define CANFD_CTR_TMFDF                         (1 << 2)  /* Tmfdf */

#define CANFD_CTR_TMIFL_SHIFT                   (8)      /* Bits 8-9: Tmifl */
#define CANFD_CTR_TMIFL_MASK                    (0x3 << CANFD_CTR_TMIFL_SHIFT)

#define CANFD_CTR_TMPTR_SHIFT                   (16)      /* Bits 16-31: Tmptr */
#define CANFD_CTR_TMPTR_MASK                    (0xffff << CANFD_CTR_TMPTR_SHIFT)

#define CANFD_CTR_GMDC_SHIFT                    (0)      /* Bits 0-1: Gmdc */
#define CANFD_CTR_GMDC_MASK                     (0x3 << CANFD_CTR_GMDC_SHIFT)

#define CANFD_CTR_GSLPR                         (1 << 2)  /* Gslpr */

#define CANFD_CTR_DEIE                          (1 << 8)  /* Deie */

#define CANFD_CTR_MEIE                          (1 << 9)  /* Meie */

#define CANFD_CTR_THLEIE                        (1 << 10)  /* Thleie */

#define CANFD_CTR_CMPOFIE                       (1 << 11)  /* Cmpofie */

#define CANFD_CTR_QOWEIE                        (1 << 12)  /* Qoweie */

#define CANFD_CTR_QMEIE                         (1 << 14)  /* Qmeie */

#define CANFD_CTR_MOWEIE                        (1 << 15)  /* Moweie */

#define CANFD_CTR_TSRST                         (1 << 16)  /* Tsrst */

#define CANFD_CTR_AFLPN_SHIFT                   (0)      /* Bits 0-5: Aflpn */
#define CANFD_CTR_AFLPN_MASK                    (0x3f << CANFD_CTR_AFLPN_SHIFT)

#define CANFD_CTR_AFLDAE                        (1 << 8)  /* Afldae */

#define CANFD_CTR_RFPC_SHIFT                    (0)      /* Bits 0-7: Rfpc */
#define CANFD_CTR_RFPC_MASK                     (0xff << CANFD_CTR_RFPC_SHIFT)

#define CANFD_CTR_CFPC_SHIFT                    (0)      /* Bits 0-7: Cfpc */
#define CANFD_CTR_CFPC_MASK                     (0xff << CANFD_CTR_CFPC_SHIFT)

#define CANFD_CTR_THLPC_SHIFT                   (0)      /* Bits 0-7: Thlpc */
#define CANFD_CTR_THLPC_MASK                    (0xff << CANFD_CTR_THLPC_SHIFT)

#define CANFD_CTR_ICBCTME                       (1 << 0)  /* Icbctme */

#define CANFD_CTR_RTME                          (1 << 2)  /* Rtme */

/* CANFD ERFL Register Bit Definitions *******************************/

/* EEF fields (parameterized for indices 0-5) */
#define CANFD_ERFL_EEF(n)                                 (1u << (16 + ((unsigned)(n) * 1)))  /* Eef0 */

#define CANFD_ERFL_BEF                          (1 << 0)  /* Bef */

#define CANFD_ERFL_EWF                          (1 << 1)  /* Ewf */

#define CANFD_ERFL_EPF                          (1 << 2)  /* Epf */

#define CANFD_ERFL_BOEF                         (1 << 3)  /* Boef */

#define CANFD_ERFL_BORF                         (1 << 4)  /* Borf */

#define CANFD_ERFL_OVLF                         (1 << 5)  /* Ovlf */

#define CANFD_ERFL_BLF                          (1 << 6)  /* Blf */

#define CANFD_ERFL_ALF                          (1 << 7)  /* Alf */

#define CANFD_ERFL_SERR                         (1 << 8)  /* Serr */

#define CANFD_ERFL_FERR                         (1 << 9)  /* Ferr */

#define CANFD_ERFL_AERR                         (1 << 10)  /* Aerr */

#define CANFD_ERFL_CERR                         (1 << 11)  /* Cerr */

#define CANFD_ERFL_B1ERR                        (1 << 12)  /* B1Err */

#define CANFD_ERFL_B0ERR                        (1 << 13)  /* B0Err */

#define CANFD_ERFL_ADERR                        (1 << 14)  /* Aderr */

#define CANFD_ERFL_CRCREG_SHIFT                 (16)      /* Bits 16-30: Crcreg */
#define CANFD_ERFL_CRCREG_MASK                  (0x7fff << CANFD_ERFL_CRCREG_SHIFT)

#define CANFD_ERFL_DEF                          (1 << 0)  /* Def */

#define CANFD_ERFL_MES                          (1 << 1)  /* Mes */

#define CANFD_ERFL_THLES                        (1 << 2)  /* Thles */

#define CANFD_ERFL_CMPOF                        (1 << 3)  /* Cmpof */

#define CANFD_ERFL_QOWES                        (1 << 4)  /* Qowes */

#define CANFD_ERFL_QMES                         (1 << 6)  /* Qmes */

#define CANFD_ERFL_MOWES                        (1 << 7)  /* Mowes */

/* CANFD NCFG Register Bit Definitions *******************************/

#define CANFD_NCFG_NBRP_SHIFT                   (0)      /* Bits 0-9: Nbrp */
#define CANFD_NCFG_NBRP_MASK                    (0x3ff << CANFD_NCFG_NBRP_SHIFT)

#define CANFD_NCFG_NSJW_SHIFT                   (10)      /* Bits 10-16: Nsjw */
#define CANFD_NCFG_NSJW_MASK                    (0x7f << CANFD_NCFG_NSJW_SHIFT)

#define CANFD_NCFG_NTSEG1_SHIFT                 (17)      /* Bits 17-24: Ntseg1 */
#define CANFD_NCFG_NTSEG1_MASK                  (0xff << CANFD_NCFG_NTSEG1_SHIFT)

#define CANFD_NCFG_NTSEG2_SHIFT                 (25)      /* Bits 25-31: Ntseg2 */
#define CANFD_NCFG_NTSEG2_MASK                  (0x7f << CANFD_NCFG_NTSEG2_SHIFT)

/* CANFD STS Register Bit Definitions ********************************/

/* RFDMASTS fields (parameterized for indices 0-7) */
#define CANFD_STS_RFDMASTS(n)                             (1u << (0 + ((unsigned)(n) * 1)))  /* Rfdmasts0 */

#define CANFD_STS_CRSTSTS                       (1 << 0)  /* Crststs */

#define CANFD_STS_CHLTSTS                       (1 << 1)  /* Chltsts */

#define CANFD_STS_CSLPSTS                       (1 << 2)  /* Cslpsts */

#define CANFD_STS_EPSTS                         (1 << 3)  /* Epsts */

#define CANFD_STS_BOSTS                         (1 << 4)  /* Bosts */

#define CANFD_STS_TRMSTS                        (1 << 5)  /* Trmsts */

#define CANFD_STS_RECSTS                        (1 << 6)  /* Recsts */

#define CANFD_STS_COMSTS                        (1 << 7)  /* Comsts */

#define CANFD_STS_ESIF                          (1 << 8)  /* Esif */

#define CANFD_STS_REC_SHIFT                     (16)      /* Bits 16-23: Rec */
#define CANFD_STS_REC_MASK                      (0xff << CANFD_STS_REC_SHIFT)

#define CANFD_STS_TEC_SHIFT                     (24)      /* Bits 24-31: Tec */
#define CANFD_STS_TEC_MASK                      (0xff << CANFD_STS_TEC_SHIFT)

#define CANFD_STS_TDCR_SHIFT                    (0)      /* Bits 0-7: Tdcr */
#define CANFD_STS_TDCR_MASK                     (0xff << CANFD_STS_TDCR_SHIFT)

#define CANFD_STS_EOCO                          (1 << 8)  /* Eoco */

#define CANFD_STS_SOCO                          (1 << 9)  /* Soco */

#define CANFD_STS_TDCVF                         (1 << 15)  /* Tdcvf */

#define CANFD_STS_EOC_SHIFT                     (16)      /* Bits 16-23: Eoc */
#define CANFD_STS_EOC_MASK                      (0xff << CANFD_STS_EOC_SHIFT)

#define CANFD_STS_SOC_SHIFT                     (24)      /* Bits 24-31: Soc */
#define CANFD_STS_SOC_MASK                      (0xff << CANFD_STS_SOC_SHIFT)

#define CANFD_STS_BLC_SHIFT                     (3)      /* Bits 3-31: Blc */
#define CANFD_STS_BLC_MASK                      (0x1fffffff << CANFD_STS_BLC_SHIFT)

#define CANFD_STS_RMESI                         (1 << 0)  /* Rmesi */

#define CANFD_STS_RMBRS                         (1 << 1)  /* Rmbrs */

#define CANFD_STS_RMFDF                         (1 << 2)  /* Rmfdf */

#define CANFD_STS_RMIFL_SHIFT                   (8)      /* Bits 8-9: Rmifl */
#define CANFD_STS_RMIFL_MASK                    (0x3 << CANFD_STS_RMIFL_SHIFT)

#define CANFD_STS_RMPTR_SHIFT                   (16)      /* Bits 16-31: Rmptr */
#define CANFD_STS_RMPTR_MASK                    (0xffff << CANFD_STS_RMPTR_SHIFT)

#define CANFD_STS_RFESI                         (1 << 0)  /* Rfesi */

#define CANFD_STS_RFBRS                         (1 << 1)  /* Rfbrs */

#define CANFD_STS_RFFDF                         (1 << 2)  /* Rffdf */

#define CANFD_STS_RFIFL_SHIFT                   (8)      /* Bits 8-9: Rfifl */
#define CANFD_STS_RFIFL_MASK                    (0x3 << CANFD_STS_RFIFL_SHIFT)

#define CANFD_STS_RFPTR_SHIFT                   (16)      /* Bits 16-31: Rfptr */
#define CANFD_STS_RFPTR_MASK                    (0xffff << CANFD_STS_RFPTR_SHIFT)

#define CANFD_STS_CFESI                         (1 << 0)  /* Cfesi */

#define CANFD_STS_CFBRS                         (1 << 1)  /* Cfbrs */

#define CANFD_STS_CFFDF                         (1 << 2)  /* Cffdf */

#define CANFD_STS_CFIFL_SHIFT                   (8)      /* Bits 8-9: Cfifl */
#define CANFD_STS_CFIFL_MASK                    (0x3 << CANFD_STS_CFIFL_SHIFT)

#define CANFD_STS_CFPTR_SHIFT                   (16)      /* Bits 16-31: Cfptr */
#define CANFD_STS_CFPTR_MASK                    (0xffff << CANFD_STS_CFPTR_SHIFT)

#define CANFD_STS_GRSTSTS                       (1 << 0)  /* Grststs */

#define CANFD_STS_GHLTSTS                       (1 << 1)  /* Ghltsts */

#define CANFD_STS_GSLPSTS                       (1 << 2)  /* Gslpsts */

#define CANFD_STS_GRAMINIT                      (1 << 3)  /* Graminit */

#define CANFD_STS_RFEMP                         (1 << 0)  /* Rfemp */

#define CANFD_STS_RFFLL                         (1 << 1)  /* Rffll */

#define CANFD_STS_RFMLT                         (1 << 2)  /* Rfmlt */

#define CANFD_STS_RFIF                          (1 << 3)  /* Rfif */

#define CANFD_STS_RFMC_SHIFT                    (8)      /* Bits 8-15: Rfmc */
#define CANFD_STS_RFMC_MASK                     (0xff << CANFD_STS_RFMC_SHIFT)

#define CANFD_STS_RFFIF                         (1 << 16)  /* Rffif */

#define CANFD_STS_CFEMP                         (1 << 0)  /* Cfemp */

#define CANFD_STS_CFFLL                         (1 << 1)  /* Cffll */

#define CANFD_STS_CFMLT                         (1 << 2)  /* Cfmlt */

#define CANFD_STS_CFRXIF                        (1 << 3)  /* Cfrxif */

#define CANFD_STS_CFTXIF                        (1 << 4)  /* Cftxif */

#define CANFD_STS_CFMC_SHIFT                    (8)      /* Bits 8-15: Cfmc */
#define CANFD_STS_CFMC_MASK                     (0xff << CANFD_STS_CFMC_SHIFT)

#define CANFD_STS_CFFIF                         (1 << 16)  /* Cffif */

#define CANFD_STS_CFOFRXIF                      (1 << 17)  /* Cfofrxif */

#define CANFD_STS_CFOFTXIF                      (1 << 18)  /* Cfoftxif */

#define CANFD_STS_CFMOW                         (1 << 24)  /* Cfmow */

#define CANFD_STS_RFXEMP_SHIFT                  (0)      /* Bits 0-7: Rfxemp */
#define CANFD_STS_RFXEMP_MASK                   (0xff << CANFD_STS_RFXEMP_SHIFT)

#define CANFD_STS_CFXEMP_SHIFT                  (8)      /* Bits 8-25: Cfxemp */
#define CANFD_STS_CFXEMP_MASK                   (0x3ffff << CANFD_STS_CFXEMP_SHIFT)

#define CANFD_STS_RFXFLL_SHIFT                  (0)      /* Bits 0-7: Rfxfll */
#define CANFD_STS_RFXFLL_MASK                   (0xff << CANFD_STS_RFXFLL_SHIFT)

#define CANFD_STS_CFXFLL_SHIFT                  (8)      /* Bits 8-25: Cfxfll */
#define CANFD_STS_CFXFLL_MASK                   (0x3ffff << CANFD_STS_CFXFLL_SHIFT)

#define CANFD_STS_RFXMLT_SHIFT                  (0)      /* Bits 0-7: Rfxmlt */
#define CANFD_STS_RFXMLT_MASK                   (0xff << CANFD_STS_RFXMLT_SHIFT)

#define CANFD_STS_CFXMLT_SHIFT                  (8)      /* Bits 8-25: Cfxmlt */
#define CANFD_STS_CFXMLT_MASK                   (0x3ffff << CANFD_STS_CFXMLT_SHIFT)

#define CANFD_STS_RFXIF_SHIFT                   (0)      /* Bits 0-7: Rfxif */
#define CANFD_STS_RFXIF_MASK                    (0xff << CANFD_STS_RFXIF_SHIFT)

#define CANFD_STS_RFXFFLL16_SHIFT               (16)      /* Bits 16-23: Rfxffll */
#define CANFD_STS_RFXFFLL16_MASK                (0xff << CANFD_STS_RFXFFLL16_SHIFT)

#define CANFD_STS_CFXRXIF_SHIFT                 (0)      /* Bits 0-17: Cfxrxif */
#define CANFD_STS_CFXRXIF_MASK                  (0x3ffff << CANFD_STS_CFXRXIF_SHIFT)

#define CANFD_STS_CFXTXIF_SHIFT                 (0)      /* Bits 0-17: Cfxtxif */
#define CANFD_STS_CFXTXIF_MASK                  (0x3ffff << CANFD_STS_CFXTXIF_SHIFT)

#define CANFD_STS_CFXOFRXIF_SHIFT               (0)      /* Bits 0-17: Cfxofrxif */
#define CANFD_STS_CFXOFRXIF_MASK                (0x3ffff << CANFD_STS_CFXOFRXIF_SHIFT)

#define CANFD_STS_CFXOFTXIF_SHIFT               (0)      /* Bits 0-17: Cfxoftxif */
#define CANFD_STS_CFXOFTXIF_MASK                (0x3ffff << CANFD_STS_CFXOFTXIF_SHIFT)

#define CANFD_STS_CFXMOW_SHIFT                  (0)      /* Bits 0-17: Cfxmow */
#define CANFD_STS_CFXMOW_MASK                   (0x3ffff << CANFD_STS_CFXMOW_SHIFT)

#define CANFD_STS_RFXFFLL0_SHIFT                (0)      /* Bits 0-7: Rfxffll */
#define CANFD_STS_RFXFFLL0_MASK                 (0xff << CANFD_STS_RFXFFLL0_SHIFT)

#define CANFD_STS_CFXFFLL_SHIFT                 (8)      /* Bits 8-25: Cfxffll */
#define CANFD_STS_CFXFFLL_MASK                  (0x3ffff << CANFD_STS_CFXFFLL_SHIFT)

#define CANFD_STS_TMTSTS                        (1 << 0)  /* Tmtsts */

#define CANFD_STS_TMTRF_SHIFT                   (1)      /* Bits 1-2: Tmtrf */
#define CANFD_STS_TMTRF_MASK                    (0x3 << CANFD_STS_TMTRF_SHIFT)

#define CANFD_STS_TMTRM                         (1 << 3)  /* Tmtrm */

#define CANFD_STS_TMTARM                        (1 << 4)  /* Tmtarm */

#define CANFD_STS_TMTRSTS_SHIFT                 (0)      /* Bits 0-15: Tmtrsts */
#define CANFD_STS_TMTRSTS_MASK                  (0xffff << CANFD_STS_TMTRSTS_SHIFT)

#define CANFD_STS_TMTARSTS_SHIFT                (0)      /* Bits 0-15: Tmtarsts */
#define CANFD_STS_TMTARSTS_MASK                 (0xffff << CANFD_STS_TMTARSTS_SHIFT)

#define CANFD_STS_TMTCSTS_SHIFT                 (0)      /* Bits 0-15: Tmtcsts */
#define CANFD_STS_TMTCSTS_MASK                  (0xffff << CANFD_STS_TMTCSTS_SHIFT)

#define CANFD_STS_TMTASTS_SHIFT                 (0)      /* Bits 0-15: Tmtasts */
#define CANFD_STS_TMTASTS_MASK                  (0xffff << CANFD_STS_TMTASTS_SHIFT)

#define CANFD_STS_TXQxEMP_SHIFT                 (0)      /* Bits 0-23: Txqxemp */
#define CANFD_STS_TXQxEMP_MASK                  (0xffffff << CANFD_STS_TXQxEMP_SHIFT)

#define CANFD_STS_TXQ0FULL_SHIFT                (0)      /* Bits 0-2: Txq0Full */
#define CANFD_STS_TXQ0FULL_MASK                 (0x7 << CANFD_STS_TXQ0FULL_SHIFT)

#define CANFD_STS_TXQ1FULL_SHIFT                (4)      /* Bits 4-6: Txq1Full */
#define CANFD_STS_TXQ1FULL_MASK                 (0x7 << CANFD_STS_TXQ1FULL_SHIFT)

#define CANFD_STS_TXQ2FULL_SHIFT                (8)      /* Bits 8-10: Txq2Full */
#define CANFD_STS_TXQ2FULL_MASK                 (0x7 << CANFD_STS_TXQ2FULL_SHIFT)

#define CANFD_STS_TXQ3FULL_SHIFT                (12)      /* Bits 12-14: Txq3Full */
#define CANFD_STS_TXQ3FULL_MASK                 (0x7 << CANFD_STS_TXQ3FULL_SHIFT)

#define CANFD_STS_TXQ4FULL_SHIFT                (16)      /* Bits 16-18: Txq4Full */
#define CANFD_STS_TXQ4FULL_MASK                 (0x7 << CANFD_STS_TXQ4FULL_SHIFT)

#define CANFD_STS_TXQ5FULL_SHIFT                (20)      /* Bits 20-22: Txq5Full */
#define CANFD_STS_TXQ5FULL_MASK                 (0x7 << CANFD_STS_TXQ5FULL_SHIFT)

#define CANFD_STS_TXQ0ML_SHIFT                  (0)      /* Bits 0-2: Txq0Ml */
#define CANFD_STS_TXQ0ML_MASK                   (0x7 << CANFD_STS_TXQ0ML_SHIFT)

#define CANFD_STS_TXQ1ML_SHIFT                  (4)      /* Bits 4-6: Txq1Ml */
#define CANFD_STS_TXQ1ML_MASK                   (0x7 << CANFD_STS_TXQ1ML_SHIFT)

#define CANFD_STS_TXQ2ML_SHIFT                  (8)      /* Bits 8-10: Txq2Ml */
#define CANFD_STS_TXQ2ML_MASK                   (0x7 << CANFD_STS_TXQ2ML_SHIFT)

#define CANFD_STS_TXQ3ML_SHIFT                  (12)      /* Bits 12-14: Txq3Ml */
#define CANFD_STS_TXQ3ML_MASK                   (0x7 << CANFD_STS_TXQ3ML_SHIFT)

#define CANFD_STS_TXQ4ML_SHIFT                  (16)      /* Bits 16-18: Txq4Ml */
#define CANFD_STS_TXQ4ML_MASK                   (0x7 << CANFD_STS_TXQ4ML_SHIFT)

#define CANFD_STS_TXQ5ML_SHIFT                  (20)      /* Bits 20-22: Txq5Ml */
#define CANFD_STS_TXQ5ML_MASK                   (0x7 << CANFD_STS_TXQ5ML_SHIFT)

#define CANFD_STS_TXQ0OW_SHIFT                  (0)      /* Bits 0-3: Txq0Ow */
#define CANFD_STS_TXQ0OW_MASK                   (0xf << CANFD_STS_TXQ0OW_SHIFT)

#define CANFD_STS_TXQ1OW_SHIFT                  (4)      /* Bits 4-7: Txq1Ow */
#define CANFD_STS_TXQ1OW_MASK                   (0xf << CANFD_STS_TXQ1OW_SHIFT)

#define CANFD_STS_TXQ0ISF_SHIFT                 (0)      /* Bits 0-3: Txq0Isf */
#define CANFD_STS_TXQ0ISF_MASK                  (0xf << CANFD_STS_TXQ0ISF_SHIFT)

#define CANFD_STS_TXQ1ISF_SHIFT                 (4)      /* Bits 4-7: Txq1Isf */
#define CANFD_STS_TXQ1ISF_MASK                  (0xf << CANFD_STS_TXQ1ISF_SHIFT)

#define CANFD_STS_TXQ2ISF_SHIFT                 (8)      /* Bits 8-11: Txq2Isf */
#define CANFD_STS_TXQ2ISF_MASK                  (0xf << CANFD_STS_TXQ2ISF_SHIFT)

#define CANFD_STS_TXQ3ISF_SHIFT                 (12)      /* Bits 12-15: Txq3Isf */
#define CANFD_STS_TXQ3ISF_MASK                  (0xf << CANFD_STS_TXQ3ISF_SHIFT)

#define CANFD_STS_TXQ4ISF_SHIFT                 (16)      /* Bits 16-19: Txq4Isf */
#define CANFD_STS_TXQ4ISF_MASK                  (0xf << CANFD_STS_TXQ4ISF_SHIFT)

#define CANFD_STS_TXQ5ISF_SHIFT                 (20)      /* Bits 20-23: Txq5Isf */
#define CANFD_STS_TXQ5ISF_MASK                  (0xf << CANFD_STS_TXQ5ISF_SHIFT)

#define CANFD_STS_TXQ0OFTISF_SHIFT              (0)      /* Bits 0-3: Txq0Oftisf */
#define CANFD_STS_TXQ0OFTISF_MASK               (0xf << CANFD_STS_TXQ0OFTISF_SHIFT)

#define CANFD_STS_TXQ1OFTISF_SHIFT              (4)      /* Bits 4-7: Txq1Oftisf */
#define CANFD_STS_TXQ1OFTISF_MASK               (0xf << CANFD_STS_TXQ1OFTISF_SHIFT)

#define CANFD_STS_TXQ2OFTISF_SHIFT              (8)      /* Bits 8-11: Txq2Oftisf */
#define CANFD_STS_TXQ2OFTISF_MASK               (0xf << CANFD_STS_TXQ2OFTISF_SHIFT)

#define CANFD_STS_TXQ3OFTISF_SHIFT              (12)      /* Bits 12-15: Txq3Oftisf */
#define CANFD_STS_TXQ3OFTISF_MASK               (0xf << CANFD_STS_TXQ3OFTISF_SHIFT)

#define CANFD_STS_TXQ4OFTISF_SHIFT              (16)      /* Bits 16-19: Txq4Oftisf */
#define CANFD_STS_TXQ4OFTISF_MASK               (0xf << CANFD_STS_TXQ4OFTISF_SHIFT)

#define CANFD_STS_TXQ5OFTISF_SHIFT              (20)      /* Bits 20-23: Txq5Oftisf */
#define CANFD_STS_TXQ5OFTISF_MASK               (0xf << CANFD_STS_TXQ5OFTISF_SHIFT)

#define CANFD_STS_TXQ0OFRISF_SHIFT              (0)      /* Bits 0-2: Txq0Ofrisf */
#define CANFD_STS_TXQ0OFRISF_MASK               (0x7 << CANFD_STS_TXQ0OFRISF_SHIFT)

#define CANFD_STS_TXQ1OFRISF_SHIFT              (4)      /* Bits 4-6: Txq1Ofrisf */
#define CANFD_STS_TXQ1OFRISF_MASK               (0x7 << CANFD_STS_TXQ1OFRISF_SHIFT)

#define CANFD_STS_TXQ2OFRISF_SHIFT              (8)      /* Bits 8-10: Txq2Ofrisf */
#define CANFD_STS_TXQ2OFRISF_MASK               (0x7 << CANFD_STS_TXQ2OFRISF_SHIFT)

#define CANFD_STS_TXQ3OFRISF_SHIFT              (12)      /* Bits 12-14: Txq3Ofrisf */
#define CANFD_STS_TXQ3OFRISF_MASK               (0x7 << CANFD_STS_TXQ3OFRISF_SHIFT)

#define CANFD_STS_TXQ4OFRISF_SHIFT              (16)      /* Bits 16-18: Txq4Ofrisf */
#define CANFD_STS_TXQ4OFRISF_MASK               (0x7 << CANFD_STS_TXQ4OFRISF_SHIFT)

#define CANFD_STS_TXQ5OFRISF_SHIFT              (20)      /* Bits 20-22: Txq5Ofrisf */
#define CANFD_STS_TXQ5OFRISF_MASK               (0x7 << CANFD_STS_TXQ5OFRISF_SHIFT)

#define CANFD_STS_TXQ0FSF_SHIFT                 (0)      /* Bits 0-3: Txq0Fsf */
#define CANFD_STS_TXQ0FSF_MASK                  (0xf << CANFD_STS_TXQ0FSF_SHIFT)

#define CANFD_STS_TXQ1FSF_SHIFT                 (4)      /* Bits 4-7: Txq1Fsf */
#define CANFD_STS_TXQ1FSF_MASK                  (0xf << CANFD_STS_TXQ1FSF_SHIFT)

#define CANFD_STS_TXQ2FSF_SHIFT                 (8)      /* Bits 8-11: Txq2Fsf */
#define CANFD_STS_TXQ2FSF_MASK                  (0xf << CANFD_STS_TXQ2FSF_SHIFT)

#define CANFD_STS_TXQ3FSF_SHIFT                 (12)      /* Bits 12-15: Txq3Fsf */
#define CANFD_STS_TXQ3FSF_MASK                  (0xf << CANFD_STS_TXQ3FSF_SHIFT)

#define CANFD_STS_TXQ4FSF_SHIFT                 (16)      /* Bits 16-19: Txq4Fsf */
#define CANFD_STS_TXQ4FSF_MASK                  (0xf << CANFD_STS_TXQ4FSF_SHIFT)

#define CANFD_STS_TXQ5FSF_SHIFT                 (20)      /* Bits 20-23: Txq5Fsf */
#define CANFD_STS_TXQ5FSF_MASK                  (0xf << CANFD_STS_TXQ5FSF_SHIFT)

#define CANFD_STS_THLEMP                        (1 << 0)  /* Thlemp */

#define CANFD_STS_THLFLL                        (1 << 1)  /* Thlfll */

#define CANFD_STS_THLELT                        (1 << 2)  /* Thlelt */

#define CANFD_STS_THLIF                         (1 << 3)  /* Thlif */

#define CANFD_STS_THLMC_SHIFT                   (8)      /* Bits 8-13: Thlmc */
#define CANFD_STS_THLMC_MASK                    (0x3f << CANFD_STS_THLMC_SHIFT)

#define CANFD_STS_CFDMASTS08                    (1 << 8)  /* Cfdmasts0 */

#define CANFD_STS_CFDMASTS19                    (1 << 9)  /* Cfdmasts1 */

#define CANFD_STS_CFDMASTS210                   (1 << 10)  /* Cfdmasts2 */

#define CANFD_STS_CFDMASTS311                   (1 << 11)  /* Cfdmasts3 */

#define CANFD_STS_CFDMASTS412                   (1 << 12)  /* Cfdmasts4 */

#define CANFD_STS_CFDMASTS513                   (1 << 13)  /* Cfdmasts5 */

#define CANFD_STS_TQ0DMASTS0                    (1 << 0)  /* Tq0Dmasts0 */

#define CANFD_STS_TQ0DMASTS1                    (1 << 1)  /* Tq0Dmasts1 */

#define CANFD_STS_TQ0DMASTS2                    (1 << 2)  /* Tq0Dmasts2 */

#define CANFD_STS_TQ0DMASTS3                    (1 << 3)  /* Tq0Dmasts3 */

#define CANFD_STS_TQ0DMASTS4                    (1 << 4)  /* Tq0Dmasts4 */

#define CANFD_STS_TQ0DMASTS5                    (1 << 5)  /* Tq0Dmasts5 */

#define CANFD_STS_TQ3DMASTS0                    (1 << 8)  /* Tq3Dmasts0 */

#define CANFD_STS_TQ3DMASTS1                    (1 << 9)  /* Tq3Dmasts1 */

#define CANFD_STS_TQ3DMASTS2                    (1 << 10)  /* Tq3Dmasts2 */

#define CANFD_STS_TQ3DMASTS3                    (1 << 11)  /* Tq3Dmasts3 */

#define CANFD_STS_TQ3DMASTS4                    (1 << 12)  /* Tq3Dmasts4 */

#define CANFD_STS_TQ3DMASTS5                    (1 << 13)  /* Tq3Dmasts5 */

#define CANFD_STS_CFDMASTS016                   (1 << 16)  /* Cfdmasts0 */

#define CANFD_STS_CFDMASTS117                   (1 << 17)  /* Cfdmasts1 */

#define CANFD_STS_CFDMASTS218                   (1 << 18)  /* Cfdmasts2 */

#define CANFD_STS_CFDMASTS319                   (1 << 19)  /* Cfdmasts3 */

#define CANFD_STS_CFDMASTS420                   (1 << 20)  /* Cfdmasts4 */

#define CANFD_STS_CFDMASTS521                   (1 << 21)  /* Cfdmasts5 */

#define CANFD_STS_QFIF_SHIFT                    (0)      /* Bits 0-2: Qfif */
#define CANFD_STS_QFIF_MASK                     (0x7 << CANFD_STS_QFIF_SHIFT)

#define CANFD_STS_BQFIF_SHIFT                   (4)      /* Bits 4-5: Bqfif */
#define CANFD_STS_BQFIF_MASK                    (0x3 << CANFD_STS_BQFIF_SHIFT)

#define CANFD_STS_QOFRIF_SHIFT                  (8)      /* Bits 8-10: Qofrif */
#define CANFD_STS_QOFRIF_MASK                   (0x7 << CANFD_STS_QOFRIF_SHIFT)

#define CANFD_STS_BQOFRIF_SHIFT                 (12)      /* Bits 12-13: Bqofrif */
#define CANFD_STS_BQOFRIF_MASK                  (0x3 << CANFD_STS_BQOFRIF_SHIFT)

#define CANFD_STS_CFRIF_SHIFT                   (16)      /* Bits 16-18: Cfrif */
#define CANFD_STS_CFRIF_MASK                    (0x7 << CANFD_STS_CFRIF_SHIFT)

#define CANFD_STS_CFRFIF_SHIFT                  (24)      /* Bits 24-26: Cfrfif */
#define CANFD_STS_CFRFIF_MASK                   (0x7 << CANFD_STS_CFRFIF_SHIFT)

#define CANFD_STS_CFOFRIF_SHIFT                 (28)      /* Bits 28-30: Cfofrif */
#define CANFD_STS_CFOFRIF_MASK                  (0x7 << CANFD_STS_CFOFRIF_SHIFT)

/* CANFD Channel definitions */
#define RZV_CANFD_CHANNEL_0        0
#define RZV_CANFD_CHANNEL_1        1
#define RZV_CANFD_CHANNEL_2        2
#define RZV_CANFD_CHANNEL_3        3
#define RZV_CANFD_CHANNEL_4        4
#define RZV_CANFD_CHANNEL_5        5

/* Maximum number of CANFD channels */
#define RZV_CANFD_MAX_CHANNELS     6

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_CANFD_H */
