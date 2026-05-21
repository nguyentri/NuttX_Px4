/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_xspi.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_XSPI_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_XSPI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* XSPI Base Addresses ***************************************************/

#ifndef RZV_XSPI0_BASE
#  define RZV_XSPI0_BASE              0x11030000
#endif
#ifndef RZV_XSPI_BASE
#  define RZV_XSPI_BASE               RZV_XSPI0_BASE
#endif

/* XSPI Register Offsets **************************************************/

/* CCCTL%s Registers (0-7) */
#define RZV_XSPI_CCCTL_OFFSET(m)                (0x00000020 + ((m) * 0x00000004))  /* CCCTL Register %s */
/* CDCTL%s Registers (0-2) */
#define RZV_XSPI_CDCTL_OFFSET(m)                (0x00000084 + ((m) * 0x00000004))  /* CDCTL Register %s */
/* CDD%s Registers (0-1) */
#define RZV_XSPI_CDD_OFFSET(m)                  (0x00000018 + ((m) * 0x00000004))  /* CDD Register %s */
/* CMCFG%s Registers (0-2) */
#define RZV_XSPI_CMCFG_OFFSET(m)                (0x00000000 + ((m) * 0x00000004))  /* CMCFG Register %s */
/* LPCTL%s Registers (0-1) */
#define RZV_XSPI_LPCTL_OFFSET(m)                (0x000000d4 + ((m) * 0x00000004))  /* LPCTL Register %s */
#define RZV_XSPI_CDT_OFFSET                              0x0010  /* CDT */
#define RZV_XSPI_CDA_OFFSET                              0x0014  /* CDA */
#define RZV_XSPI_WRAPCFG_OFFSET                          0x0040  /* WRAPCFG */
#define RZV_XSPI_COMCFG_OFFSET                           0x0044  /* COMCFG */
#define RZV_XSPI_BMCFG_OFFSET                            0x0048  /* BMCFG */
#define RZV_XSPI_BMCFGCH1_OFFSET                         0x004C  /* BMCFGCH1 */
#define RZV_XSPI_BMCTL0_OFFSET                           0x0078  /* BMCTL0 */
#define RZV_XSPI_BMCTL1_OFFSET                           0x007C  /* BMCTL1 */
#define RZV_XSPI_CMCTL_OFFSET                            0x0080  /* CMCTL */
#define RZV_XSPI_CMCTLCH1_OFFSET                         0x0084  /* CMCTLCH1 */
#define RZV_XSPI_LIOCTL_OFFSET                           0x00DC  /* LIOCTL */
#define RZV_XSPI_VERSTT_OFFSET                           0x0114  /* VERSTT */
#define RZV_XSPI_COMSTT_OFFSET                           0x0118  /* COMSTT */
#define RZV_XSPI_INTS_OFFSET                             0x011C  /* INTS */
#define RZV_XSPI_INTE_OFFSET                             0x0120  /* INTE */

/* XSPI Register Addresses *************************************************/

#define RZV_XSPI_CCCTL(m)                       (RZV_XSPI_BASE + RZV_XSPI_CCCTL_OFFSET(m))
#define RZV_XSPI_CDCTL(m)                       (RZV_XSPI_BASE + RZV_XSPI_CDCTL_OFFSET(m))
#define RZV_XSPI_CDD(m)                         (RZV_XSPI_BASE + RZV_XSPI_CDD_OFFSET(m))
#define RZV_XSPI_CMCFG(m)                       (RZV_XSPI_BASE + RZV_XSPI_CMCFG_OFFSET(m))
#define RZV_XSPI_LPCTL(m)                       (RZV_XSPI_BASE + RZV_XSPI_LPCTL_OFFSET(m))
#define RZV_XSPI_CDT                                 (RZV_XSPI_BASE + RZV_XSPI_CDT_OFFSET)
#define RZV_XSPI_CDA                                 (RZV_XSPI_BASE + RZV_XSPI_CDA_OFFSET)
#define RZV_XSPI_WRAPCFG                             (RZV_XSPI_BASE + RZV_XSPI_WRAPCFG_OFFSET)
#define RZV_XSPI_COMCFG                              (RZV_XSPI_BASE + RZV_XSPI_COMCFG_OFFSET)
#define RZV_XSPI_BMCFG                               (RZV_XSPI_BASE + RZV_XSPI_BMCFG_OFFSET)
#define RZV_XSPI_BMCFGCH1                            (RZV_XSPI_BASE + RZV_XSPI_BMCFGCH1_OFFSET)
#define RZV_XSPI_BMCTL0                              (RZV_XSPI_BASE + RZV_XSPI_BMCTL0_OFFSET)
#define RZV_XSPI_BMCTL1                              (RZV_XSPI_BASE + RZV_XSPI_BMCTL1_OFFSET)
#define RZV_XSPI_CMCTL                               (RZV_XSPI_BASE + RZV_XSPI_CMCTL_OFFSET)
#define RZV_XSPI_CMCTLCH1                            (RZV_XSPI_BASE + RZV_XSPI_CMCTLCH1_OFFSET)
#define RZV_XSPI_LIOCTL                              (RZV_XSPI_BASE + RZV_XSPI_LIOCTL_OFFSET)
#define RZV_XSPI_VERSTT                              (RZV_XSPI_BASE + RZV_XSPI_VERSTT_OFFSET)
#define RZV_XSPI_COMSTT                              (RZV_XSPI_BASE + RZV_XSPI_COMSTT_OFFSET)
#define RZV_XSPI_INTS                                (RZV_XSPI_BASE + RZV_XSPI_INTS_OFFSET)
#define RZV_XSPI_INTE                                (RZV_XSPI_BASE + RZV_XSPI_INTE_OFFSET)

/* XSPI CCCTL Register Bit Definitions (Parameterized) *********************/

#define XSPI_CCCTL_CAEN(m)                                (1 << 0)  /* Caen */
#define XSPI_CCCTL_CANOWR(m)                              (1 << 1)  /* Canowr */
#define XSPI_CCCTL_CAITV_SHIFT                            (8)      /* Bits 8-12: Caitv */
#define XSPI_CCCTL_CAITV_MASK(m)                          (0x1f << XSPI_CCCTL_CAITV_SHIFT)
#define XSPI_CCCTL_CAITV(m,val)                           (((val) << XSPI_CCCTL_CAITV_SHIFT) & XSPI_CCCTL_CAITV_MASK(m))
#define XSPI_CCCTL_CASFTSTA_SHIFT                         (16)      /* Bits 16-20: Casftsta */
#define XSPI_CCCTL_CASFTSTA_MASK(m)                       (0x1f << XSPI_CCCTL_CASFTSTA_SHIFT)
#define XSPI_CCCTL_CASFTSTA(m,val)                        (((val) << XSPI_CCCTL_CASFTSTA_SHIFT) & XSPI_CCCTL_CASFTSTA_MASK(m))
#define XSPI_CCCTL_CASFTEND_SHIFT                         (24)      /* Bits 24-28: Casftend */
#define XSPI_CCCTL_CASFTEND_MASK(m)                       (0x1f << XSPI_CCCTL_CASFTEND_SHIFT)
#define XSPI_CCCTL_CASFTEND(m,val)                        (((val) << XSPI_CCCTL_CASFTEND_SHIFT) & XSPI_CCCTL_CASFTEND_MASK(m))

/* XSPI CDCTL Register Bit Definitions (Parameterized) *********************/

#define XSPI_CDCTL_TRREQ(m)                               (1 << 0)  /* Trreq */
#define XSPI_CDCTL_PERMD(m)                               (1 << 1)  /* Permd */
#define XSPI_CDCTL_CSSEL(m)                               (1 << 3)  /* Cssel */
#define XSPI_CDCTL_TRNUM_SHIFT                            (4)      /* Bits 4-5: Trnum */
#define XSPI_CDCTL_TRNUM_MASK(m)                          (0x3 << XSPI_CDCTL_TRNUM_SHIFT)
#define XSPI_CDCTL_TRNUM(m,val)                           (((val) << XSPI_CDCTL_TRNUM_SHIFT) & XSPI_CDCTL_TRNUM_MASK(m))
#define XSPI_CDCTL_PERITV_SHIFT                           (16)      /* Bits 16-20: Peritv */
#define XSPI_CDCTL_PERITV_MASK(m)                         (0x1f << XSPI_CDCTL_PERITV_SHIFT)
#define XSPI_CDCTL_PERITV(m,val)                          (((val) << XSPI_CDCTL_PERITV_SHIFT) & XSPI_CDCTL_PERITV_MASK(m))
#define XSPI_CDCTL_PERREP_SHIFT                           (24)      /* Bits 24-27: Perrep */
#define XSPI_CDCTL_PERREP_MASK(m)                         (0xf << XSPI_CDCTL_PERREP_SHIFT)
#define XSPI_CDCTL_PERREP(m,val)                          (((val) << XSPI_CDCTL_PERREP_SHIFT) & XSPI_CDCTL_PERREP_MASK(m))

/* XSPI CDD Register Bit Definitions (Parameterized) ***********************/

#define XSPI_CDD_DATA_SHIFT                               (0)      /* Bits 0-31: Data */
#define XSPI_CDD_DATA_MASK(m)                             (0xffffffff << XSPI_CDD_DATA_SHIFT)
#define XSPI_CDD_DATA(m,val)                              (((val) << XSPI_CDD_DATA_SHIFT) & XSPI_CDD_DATA_MASK(m))

/* XSPI CMCFG Register Bit Definitions (Parameterized) *********************/

#define XSPI_CMCFG_FFMT_SHIFT                             (0)      /* Bits 0-1: Ffmt */
#define XSPI_CMCFG_FFMT_MASK(m)                           (0x3 << XSPI_CMCFG_FFMT_SHIFT)
#define XSPI_CMCFG_FFMT(m,val)                            (((val) << XSPI_CMCFG_FFMT_SHIFT) & XSPI_CMCFG_FFMT_MASK(m))
#define XSPI_CMCFG_ADDSIZE_SHIFT                          (2)      /* Bits 2-3: Addsize */
#define XSPI_CMCFG_ADDSIZE_MASK(m)                        (0x3 << XSPI_CMCFG_ADDSIZE_SHIFT)
#define XSPI_CMCFG_ADDSIZE(m,val)                         (((val) << XSPI_CMCFG_ADDSIZE_SHIFT) & XSPI_CMCFG_ADDSIZE_MASK(m))
#define XSPI_CMCFG_WPBSTMD(m)                             (1 << 4)  /* Wpbstmd */
#define XSPI_CMCFG_ARYAMD(m)                              (1 << 5)  /* Aryamd */
#define XSPI_CMCFG_ADDRPEN_SHIFT                          (16)      /* Bits 16-23: Addrpen */
#define XSPI_CMCFG_ADDRPEN_MASK(m)                        (0xff << XSPI_CMCFG_ADDRPEN_SHIFT)
#define XSPI_CMCFG_ADDRPEN(m,val)                         (((val) << XSPI_CMCFG_ADDRPEN_SHIFT) & XSPI_CMCFG_ADDRPEN_MASK(m))
#define XSPI_CMCFG_ADDRPCD_SHIFT                          (24)      /* Bits 24-31: Addrpcd */
#define XSPI_CMCFG_ADDRPCD_MASK(m)                        (0xff << XSPI_CMCFG_ADDRPCD_SHIFT)
#define XSPI_CMCFG_ADDRPCD(m,val)                         (((val) << XSPI_CMCFG_ADDRPCD_SHIFT) & XSPI_CMCFG_ADDRPCD_MASK(m))

/* XSPI LPCTL Register Bit Definitions (Parameterized) *********************/

#define XSPI_LPCTL_PATREQ(m)                              (1 << 0)  /* Patreq */
#define XSPI_LPCTL_CSSEL(m)                               (1 << 3)  /* Cssel */
#define XSPI_LPCTL_XDPIN_SHIFT                            (4)      /* Bits 4-5: Xdpin */
#define XSPI_LPCTL_XDPIN_MASK(m)                          (0x3 << XSPI_LPCTL_XDPIN_SHIFT)
#define XSPI_LPCTL_XDPIN(m,val)                           (((val) << XSPI_LPCTL_XDPIN_SHIFT) & XSPI_LPCTL_XDPIN_MASK(m))
#define XSPI_LPCTL_XD1LEN_SHIFT                           (16)      /* Bits 16-20: Xd1Len */
#define XSPI_LPCTL_XD1LEN_MASK(m)                         (0x1f << XSPI_LPCTL_XD1LEN_SHIFT)
#define XSPI_LPCTL_XD1LEN(m,val)                          (((val) << XSPI_LPCTL_XD1LEN_SHIFT) & XSPI_LPCTL_XD1LEN_MASK(m))
#define XSPI_LPCTL_XD1VAL(m)                              (1 << 23)  /* Xd1Val */
#define XSPI_LPCTL_XD2LEN_SHIFT                           (24)      /* Bits 24-28: Xd2Len */
#define XSPI_LPCTL_XD2LEN_MASK(m)                         (0x1f << XSPI_LPCTL_XD2LEN_SHIFT)
#define XSPI_LPCTL_XD2LEN(m,val)                          (((val) << XSPI_LPCTL_XD2LEN_SHIFT) & XSPI_LPCTL_XD2LEN_MASK(m))
#define XSPI_LPCTL_XD2VAL(m)                              (1 << 31)  /* Xd2Val */

/* XSPI BMCFG Register Bit Definitions *******************************/

#define XSPI_BMCFG_WRMD                         (1 << 0)  /* Wrmd */

#define XSPI_BMCFG_MWRCOMB                      (1 << 7)  /* Mwrcomb */

#define XSPI_BMCFG_MWRSIZE_SHIFT                (8)      /* Bits 8-15: Mwrsize */
#define XSPI_BMCFG_MWRSIZE_MASK                 (0xff << XSPI_BMCFG_MWRSIZE_SHIFT)

#define XSPI_BMCFG_PREEN                        (1 << 16)  /* Preen */

#define XSPI_BMCFG_CMBTIM_SHIFT                 (24)      /* Bits 24-31: Cmbtim */
#define XSPI_BMCFG_CMBTIM_MASK                  (0xff << XSPI_BMCFG_CMBTIM_SHIFT)

/* XSPI BMCTL0 Register Bit Definitions ******************************/

#define XSPI_BMCTL0_CS0ACC_SHIFT                (0)      /* Bits 0-1: Cs0Acc */
#define XSPI_BMCTL0_CS0ACC_MASK                 (0x3 << XSPI_BMCTL0_CS0ACC_SHIFT)

#define XSPI_BMCTL0_CS1ACC_SHIFT                (2)      /* Bits 2-3: Cs1Acc */
#define XSPI_BMCTL0_CS1ACC_MASK                 (0x3 << XSPI_BMCTL0_CS1ACC_SHIFT)

#define XSPI_BMCTL0_CH1CS0ACC_SHIFT             (4)      /* Bits 4-5: Ch1Cs0Acc */
#define XSPI_BMCTL0_CH1CS0ACC_MASK              (0x3 << XSPI_BMCTL0_CH1CS0ACC_SHIFT)

#define XSPI_BMCTL0_CH1CS1ACC_SHIFT             (6)      /* Bits 6-7: Ch1Cs1Acc */
#define XSPI_BMCTL0_CH1CS1ACC_MASK              (0x3 << XSPI_BMCTL0_CH1CS1ACC_SHIFT)

/* XSPI BMCTL1 Register Bit Definitions ******************************/

#define XSPI_BMCTL1_MWRPUSH                     (1 << 8)  /* Mwrpush */

#define XSPI_BMCTL1_MWRPUSHCH1                  (1 << 9)  /* Mwrpushch1 */

#define XSPI_BMCTL1_PBUFCLR                     (1 << 10)  /* Pbufclr */

#define XSPI_BMCTL1_PBUFCLRCH1                  (1 << 11)  /* Pbufclrch1 */

/* XSPI CASTTCS Register Bit Definitions *****************************/

#define XSPI_CASTTCS_CASUC_SHIFT                (0)      /* Bits 0-31: Casuc */
#define XSPI_CASTTCS_CASUC_MASK                 (0xffffffff << XSPI_CASTTCS_CASUC_SHIFT)

/* XSPI CDA Register Bit Definitions *********************************/

#define XSPI_CDA_ADD_SHIFT                      (0)      /* Bits 0-31: Add */
#define XSPI_CDA_ADD_MASK                       (0xffffffff << XSPI_CDA_ADD_SHIFT)

/* XSPI CDT Register Bit Definitions *********************************/

#define XSPI_CDT_CMDSIZE_SHIFT                  (0)      /* Bits 0-1: Cmdsize */
#define XSPI_CDT_CMDSIZE_MASK                   (0x3 << XSPI_CDT_CMDSIZE_SHIFT)

#define XSPI_CDT_ADDSIZE_SHIFT                  (2)      /* Bits 2-4: Addsize */
#define XSPI_CDT_ADDSIZE_MASK                   (0x7 << XSPI_CDT_ADDSIZE_SHIFT)

#define XSPI_CDT_DATASIZE_SHIFT                 (5)      /* Bits 5-8: Datasize */
#define XSPI_CDT_DATASIZE_MASK                  (0xf << XSPI_CDT_DATASIZE_SHIFT)

#define XSPI_CDT_LATE_SHIFT                     (9)      /* Bits 9-13: Late */
#define XSPI_CDT_LATE_MASK                      (0x1f << XSPI_CDT_LATE_SHIFT)

#define XSPI_CDT_TRTYPE                         (1 << 15)  /* Trtype */

#define XSPI_CDT_CMD_SHIFT                      (16)      /* Bits 16-31: Cmd */
#define XSPI_CDT_CMD_MASK                       (0xffff << XSPI_CDT_CMD_SHIFT)

/* XSPI CMCTL Register Bit Definitions *******************************/

#define XSPI_CMCTL_XIPENCODE_SHIFT              (0)      /* Bits 0-7: Xipencode */
#define XSPI_CMCTL_XIPENCODE_MASK               (0xff << XSPI_CMCTL_XIPENCODE_SHIFT)

#define XSPI_CMCTL_XIPEXCODE_SHIFT              (8)      /* Bits 8-15: Xipexcode */
#define XSPI_CMCTL_XIPEXCODE_MASK               (0xff << XSPI_CMCTL_XIPEXCODE_SHIFT)

#define XSPI_CMCTL_XIPEN                        (1 << 16)  /* Xipen */

/* XSPI COMCFG Register Bit Definitions ******************************/

#define XSPI_COMCFG_ARBMD_SHIFT                 (0)      /* Bits 0-1: Arbmd */
#define XSPI_COMCFG_ARBMD_MASK                  (0x3 << XSPI_COMCFG_ARBMD_SHIFT)

#define XSPI_COMCFG_OEASTEX                     (1 << 16)  /* Oeastex */

#define XSPI_COMCFG_OENEGEX                     (1 << 17)  /* Oenegex */

/* XSPI COMSTT Register Bit Definitions ******************************/

#define XSPI_COMSTT_MEMACC                      (1 << 0)  /* Memacc */

#define XSPI_COMSTT_MEMACCCH1                   (1 << 1)  /* Memaccch1 */

#define XSPI_COMSTT_PBUFNE                      (1 << 4)  /* Pbufne */

#define XSPI_COMSTT_PBUFNECH1                   (1 << 5)  /* Pbufnech1 */

#define XSPI_COMSTT_WRBUFNE                     (1 << 6)  /* Wrbufne */

#define XSPI_COMSTT_WRBUFNECH1                  (1 << 7)  /* Wrbufnech1 */

#define XSPI_COMSTT_ECSCS0                      (1 << 16)  /* Ecscs0 */

#define XSPI_COMSTT_INTCS0                      (1 << 17)  /* Intcs0 */

#define XSPI_COMSTT_RSTOCS0                     (1 << 18)  /* Rstocs0 */

#define XSPI_COMSTT_ECSCS1                      (1 << 20)  /* Ecscs1 */

#define XSPI_COMSTT_INTCS1                      (1 << 21)  /* Intcs1 */

#define XSPI_COMSTT_RSTOCS1                     (1 << 22)  /* Rstocs1 */

/* XSPI INTC Register Bit Definitions ********************************/

#define XSPI_INTC_CMDCMPC                       (1 << 0)  /* Cmdcmpc */

#define XSPI_INTC_PATCMPC                       (1 << 1)  /* Patcmpc */

#define XSPI_INTC_INICMPC                       (1 << 2)  /* Inicmpc */

#define XSPI_INTC_PERTOC                        (1 << 3)  /* Pertoc */

#define XSPI_INTC_DSTOCS0C                      (1 << 4)  /* Dstocs0C */

#define XSPI_INTC_DSTOCS1C                      (1 << 5)  /* Dstocs1C */

#define XSPI_INTC_ECSCS0C                       (1 << 8)  /* Ecscs0C */

#define XSPI_INTC_ECSCS1C                       (1 << 9)  /* Ecscs1C */

#define XSPI_INTC_INTCS0C                       (1 << 12)  /* Intcs0C */

#define XSPI_INTC_INTCS1C                       (1 << 13)  /* Intcs1C */

#define XSPI_INTC_BUSERRC                       (1 << 20)  /* Buserrc */

#define XSPI_INTC_BUSERRCH1C                    (1 << 21)  /* Buserrch1C */

#define XSPI_INTC_CAFAILCS0C                    (1 << 28)  /* Cafailcs0C */

#define XSPI_INTC_CAFAILCS1C                    (1 << 29)  /* Cafailcs1C */

#define XSPI_INTC_CASUCCS0C                     (1 << 30)  /* Casuccs0C */

#define XSPI_INTC_CASUCCS1C                     (1 << 31)  /* Casuccs1C */

/* XSPI INTE Register Bit Definitions ********************************/

#define XSPI_INTE_CMDCMPE                       (1 << 0)  /* Cmdcmpe */

#define XSPI_INTE_PATCMPE                       (1 << 1)  /* Patcmpe */

#define XSPI_INTE_INICMPE                       (1 << 2)  /* Inicmpe */

#define XSPI_INTE_PERTOE                        (1 << 3)  /* Pertoe */

#define XSPI_INTE_DSTOCS0E                      (1 << 4)  /* Dstocs0E */

#define XSPI_INTE_DSTOCS1E                      (1 << 5)  /* Dstocs1E */

#define XSPI_INTE_ECSCS0E                       (1 << 8)  /* Ecscs0E */

#define XSPI_INTE_ECSCS1E                       (1 << 9)  /* Ecscs1E */

#define XSPI_INTE_INTCS0E                       (1 << 12)  /* Intcs0E */

#define XSPI_INTE_INTCS1E                       (1 << 13)  /* Intcs1E */

#define XSPI_INTE_BUSERRE                       (1 << 20)  /* Buserre */

#define XSPI_INTE_BUSERRCH1E                    (1 << 21)  /* Buserrch1E */

#define XSPI_INTE_CAFAILCS0E                    (1 << 28)  /* Cafailcs0E */

#define XSPI_INTE_CAFAILCS1E                    (1 << 29)  /* Cafailcs1E */

#define XSPI_INTE_CASUCCS0E                     (1 << 30)  /* Casuccs0E */

#define XSPI_INTE_CASUCCS1E                     (1 << 31)  /* Casuccs1E */

/* XSPI INTS Register Bit Definitions ********************************/

#define XSPI_INTS_CMDCMP                        (1 << 0)  /* Cmdcmp */

#define XSPI_INTS_PATCMP                        (1 << 1)  /* Patcmp */

#define XSPI_INTS_INICMP                        (1 << 2)  /* Inicmp */

#define XSPI_INTS_PERTO                         (1 << 3)  /* Perto */

#define XSPI_INTS_DSTOCS0                       (1 << 4)  /* Dstocs0 */

#define XSPI_INTS_DSTOCS1                       (1 << 5)  /* Dstocs1 */

#define XSPI_INTS_ECSCS0                        (1 << 8)  /* Ecscs0 */

#define XSPI_INTS_ECSCS1                        (1 << 9)  /* Ecscs1 */

#define XSPI_INTS_INTCS0                        (1 << 12)  /* Intcs0 */

#define XSPI_INTS_INTCS1                        (1 << 13)  /* Intcs1 */

#define XSPI_INTS_BUSERR                        (1 << 20)  /* Buserr */

#define XSPI_INTS_BUSERRCH1                     (1 << 21)  /* Buserrch1 */

#define XSPI_INTS_CAFAILCS0                     (1 << 28)  /* Cafailcs0 */

#define XSPI_INTS_CAFAILCS1                     (1 << 29)  /* Cafailcs1 */

#define XSPI_INTS_CASUCCS0                      (1 << 30)  /* Casuccs0 */

#define XSPI_INTS_CASUCCS1                      (1 << 31)  /* Casuccs1 */

/* XSPI LIOCFGCS Register Bit Definitions ****************************/

#define XSPI_LIOCFGCS_PRTMD_SHIFT               (0)      /* Bits 0-9: Prtmd */
#define XSPI_LIOCFGCS_PRTMD_MASK                (0x3ff << XSPI_LIOCFGCS_PRTMD_SHIFT)

#define XSPI_LIOCFGCS_LATEMD                    (1 << 10)  /* Latemd */

#define XSPI_LIOCFGCS_WRMSKMD                   (1 << 11)  /* Wrmskmd */

#define XSPI_LIOCFGCS_CSMIN_SHIFT               (16)      /* Bits 16-19: Csmin */
#define XSPI_LIOCFGCS_CSMIN_MASK                (0xf << XSPI_LIOCFGCS_CSMIN_SHIFT)

#define XSPI_LIOCFGCS_CSASTEX                   (1 << 20)  /* Csastex */

#define XSPI_LIOCFGCS_CSNEGEX                   (1 << 21)  /* Csnegex */

#define XSPI_LIOCFGCS_SDRDRV                    (1 << 22)  /* Sdrdrv */

#define XSPI_LIOCFGCS_SDRSMPMD                  (1 << 23)  /* Sdrsmpmd */

#define XSPI_LIOCFGCS_SDRSMPSFT_SHIFT           (24)      /* Bits 24-27: Sdrsmpsft */
#define XSPI_LIOCFGCS_SDRSMPSFT_MASK            (0xf << XSPI_LIOCFGCS_SDRSMPSFT_SHIFT)

#define XSPI_LIOCFGCS_DDRSMPEX_SHIFT            (28)      /* Bits 28-31: Ddrsmpex */
#define XSPI_LIOCFGCS_DDRSMPEX_MASK             (0xf << XSPI_LIOCFGCS_DDRSMPEX_SHIFT)

/* XSPI LIOCTL Register Bit Definitions ******************************/

#define XSPI_LIOCTL_WPCS0                       (1 << 0)  /* Wpcs0 */

#define XSPI_LIOCTL_WPCS1                       (1 << 1)  /* Wpcs1 */

#define XSPI_LIOCTL_RSTCS0                      (1 << 16)  /* Rstcs0 */

#define XSPI_LIOCTL_RSTCS1                      (1 << 17)  /* Rstcs1 */

/* XSPI VERSTT Register Bit Definitions ******************************/

#define XSPI_VERSTT_VER_SHIFT                   (0)      /* Bits 0-31: Ver */
#define XSPI_VERSTT_VER_MASK                    (0xffffffff << XSPI_VERSTT_VER_SHIFT)

/* XSPI WRAPCFG Register Bit Definitions *****************************/

#define XSPI_WRAPCFG_DSSFTCS0_SHIFT             (8)      /* Bits 8-12: Dssftcs0 */
#define XSPI_WRAPCFG_DSSFTCS0_MASK              (0x1f << XSPI_WRAPCFG_DSSFTCS0_SHIFT)

#define XSPI_WRAPCFG_DSSFTCS1_SHIFT             (24)      /* Bits 24-28: Dssftcs1 */
#define XSPI_WRAPCFG_DSSFTCS1_MASK              (0x1f << XSPI_WRAPCFG_DSSFTCS1_SHIFT)

/* XSPI Channel definitions */
#define RZV_XSPI_CHANNEL_0         0

/* Maximum number of XSPI channels */
#define RZV_XSPI_MAX_CHANNELS      1

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_XSPI_H */
