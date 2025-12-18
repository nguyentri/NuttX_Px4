/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_ssi.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SSI_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SSI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SSI Base Addresses ****************************************************/

#ifndef RZV_SSI0_BASE
#  define RZV_SSI0_BASE               0x40049C00
#endif
#ifndef RZV_SSI1_BASE
#  define RZV_SSI1_BASE               0x4004A000
#endif
#ifndef RZV_SSI2_BASE
#  define RZV_SSI2_BASE               0x4004A400
#endif
#ifndef RZV_SSI3_BASE
#  define RZV_SSI3_BASE               0x4004A800
#endif

/* SSI Register Offsets ***************************************************/

#define RZV_SSI_SSICR_OFFSET                             0x0000  /* SSICR */
#define RZV_SSI_SSISR_OFFSET                             0x0004  /* SSISR */
#define RZV_SSI_SSIFCR_OFFSET                            0x0010  /* SSIFCR */
#define RZV_SSI_SSIFSR_OFFSET                            0x0014  /* SSIFSR */
#define RZV_SSI_H_OFFSET                                 0x0018  /* H */
#define RZV_SSI_SSIOFR_OFFSET                            0x001A  /* SSIOFR */
#define RZV_SSI_SSISCR_OFFSET                            0x001E  /* SSISCR */

/* SSI Register Addresses **************************************************/

#define RZV_SSI_SSICR(ch)                            (RZV_SSI##ch##_BASE + RZV_SSI_SSICR_OFFSET)
#define RZV_SSI_SSISR(ch)                            (RZV_SSI##ch##_BASE + RZV_SSI_SSISR_OFFSET)
#define RZV_SSI_SSIFCR(ch)                           (RZV_SSI##ch##_BASE + RZV_SSI_SSIFCR_OFFSET)
#define RZV_SSI_SSIFSR(ch)                           (RZV_SSI##ch##_BASE + RZV_SSI_SSIFSR_OFFSET)
#define RZV_SSI_H(ch)                                (RZV_SSI##ch##_BASE + RZV_SSI_H_OFFSET)
#define RZV_SSI_SSIOFR(ch)                           (RZV_SSI##ch##_BASE + RZV_SSI_SSIOFR_OFFSET)
#define RZV_SSI_SSISCR(ch)                           (RZV_SSI##ch##_BASE + RZV_SSI_SSISCR_OFFSET)

/* SSI SSICR Register Bit Definitions ********************************/

#define SSI_SSICR_REN                           (1 << 0)  /* Ren */

#define SSI_SSICR_TEN                           (1 << 1)  /* Ten */

#define SSI_SSICR_MUEN                          (1 << 3)  /* Muen */

#define SSI_SSICR_CKDV_SHIFT                    (4)      /* Bits 4-7: Ckdv */
#define SSI_SSICR_CKDV_MASK                     (0xf << SSI_SSICR_CKDV_SHIFT)

#define SSI_SSICR_DEL                           (1 << 8)  /* Del */

#define SSI_SSICR_PDTA                          (1 << 9)  /* Pdta */

#define SSI_SSICR_SDTA                          (1 << 10)  /* Sdta */

#define SSI_SSICR_SPDP                          (1 << 11)  /* Spdp */

#define SSI_SSICR_LRCKP                         (1 << 12)  /* Lrckp */

#define SSI_SSICR_BCKP                          (1 << 13)  /* Bckp */

#define SSI_SSICR_MST                           (1 << 14)  /* Mst */

#define SSI_SSICR_SWL_SHIFT                     (16)      /* Bits 16-18: Swl */
#define SSI_SSICR_SWL_MASK                      (0x7 << SSI_SSICR_SWL_SHIFT)

#define SSI_SSICR_DWL_SHIFT                     (19)      /* Bits 19-21: Dwl */
#define SSI_SSICR_DWL_MASK                      (0x7 << SSI_SSICR_DWL_SHIFT)

#define SSI_SSICR_FRM_SHIFT                     (22)      /* Bits 22-23: Frm */
#define SSI_SSICR_FRM_MASK                      (0x3 << SSI_SSICR_FRM_SHIFT)

#define SSI_SSICR_IIEN                          (1 << 25)  /* Iien */

#define SSI_SSICR_ROIEN                         (1 << 26)  /* Roien */

#define SSI_SSICR_RUIEN                         (1 << 27)  /* Ruien */

#define SSI_SSICR_TOIEN                         (1 << 28)  /* Toien */

#define SSI_SSICR_TUIEN                         (1 << 29)  /* Tuien */

#define SSI_SSICR_CKS                           (1 << 30)  /* Cks */

/* SSI SSIFCR Register Bit Definitions *******************************/

#define SSI_SSIFCR_RFRST                        (1 << 0)  /* Rfrst */

#define SSI_SSIFCR_TFRST                        (1 << 1)  /* Tfrst */

#define SSI_SSIFCR_RIE                          (1 << 2)  /* Rie */

#define SSI_SSIFCR_TIE                          (1 << 3)  /* Tie */

#define SSI_SSIFCR_RXDNCE                       (1 << 8)  /* Rxdnce */

#define SSI_SSIFCR_LRCKNCE                      (1 << 9)  /* Lrcknce */

#define SSI_SSIFCR_BCKNCE                       (1 << 10)  /* Bcknce */

#define SSI_SSIFCR_BSW                          (1 << 11)  /* Bsw */

#define SSI_SSIFCR_SSIRST                       (1 << 16)  /* Ssirst */

#define SSI_SSIFCR_AUCKE                        (1 << 31)  /* Aucke */

/* SSI SSIFRDR Register Bit Definitions ******************************/

#define SSI_SSIFRDR_SSIFRDR_SHIFT               (0)      /* Bits 0-31: Ssifrdr */
#define SSI_SSIFRDR_SSIFRDR_MASK                (0xffffffff << SSI_SSIFRDR_SSIFRDR_SHIFT)

/* SSI SSIFSR Register Bit Definitions *******************************/

#define SSI_SSIFSR_RDF                          (1 << 0)  /* Rdf */

#define SSI_SSIFSR_RDC_SHIFT                    (8)      /* Bits 8-13: Rdc */
#define SSI_SSIFSR_RDC_MASK                     (0x3f << SSI_SSIFSR_RDC_SHIFT)

#define SSI_SSIFSR_TDE                          (1 << 16)  /* Tde */

#define SSI_SSIFSR_TDC_SHIFT                    (24)      /* Bits 24-29: Tdc */
#define SSI_SSIFSR_TDC_MASK                     (0x3f << SSI_SSIFSR_TDC_SHIFT)

/* SSI SSIFTDR Register Bit Definitions ******************************/

#define SSI_SSIFTDR_SSIFTDR_SHIFT               (0)      /* Bits 0-31: Ssiftdr */
#define SSI_SSIFTDR_SSIFTDR_MASK                (0xffffffff << SSI_SSIFTDR_SSIFTDR_SHIFT)

/* SSI SSIOFR Register Bit Definitions *******************************/

#define SSI_SSIOFR_OMOD_SHIFT                   (0)      /* Bits 0-1: Omod */
#define SSI_SSIOFR_OMOD_MASK                    (0x3 << SSI_SSIOFR_OMOD_SHIFT)

#define SSI_SSIOFR_LRCONT                       (1 << 8)  /* Lrcont */

#define SSI_SSIOFR_BCKSTP                       (1 << 9)  /* Bckstp */

/* SSI SSISCR Register Bit Definitions *******************************/

#define SSI_SSISCR_RDFS_SHIFT                   (0)      /* Bits 0-4: Rdfs */
#define SSI_SSISCR_RDFS_MASK                    (0x1f << SSI_SSISCR_RDFS_SHIFT)

#define SSI_SSISCR_TDES_SHIFT                   (8)      /* Bits 8-12: Tdes */
#define SSI_SSISCR_TDES_MASK                    (0x1f << SSI_SSISCR_TDES_SHIFT)

/* SSI SSISR Register Bit Definitions ********************************/

#define SSI_SSISR_IIRQ                          (1 << 25)  /* Iirq */

#define SSI_SSISR_ROIRQ                         (1 << 26)  /* Roirq */

#define SSI_SSISR_RUIRQ                         (1 << 27)  /* Ruirq */

#define SSI_SSISR_TOIRQ                         (1 << 28)  /* Toirq */

#define SSI_SSISR_TUIRQ                         (1 << 29)  /* Tuirq */

/* SSI Channel definitions */
#define RZV_SSI_CHANNEL_0          0
#define RZV_SSI_CHANNEL_1          1
#define RZV_SSI_CHANNEL_2          2
#define RZV_SSI_CHANNEL_3          3

/* Maximum number of SSI channels */
#define RZV_SSI_MAX_CHANNELS       4

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SSI_H */
