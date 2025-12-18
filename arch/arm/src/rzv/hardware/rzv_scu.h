/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_scu.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SCU_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SCU_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SCU Base Addresses ****************************************************/

#ifndef RZV_SCU0_BASE
#  define RZV_SCU0_BASE               0x12C10000
#endif
#ifndef RZV_SCU_BASE
#  define RZV_SCU_BASE                RZV_SCU0_BASE
#endif

/* SCU Register Offsets ***************************************************/

/* FPPFEAR%s Registers (0-3) */
#define RZV_SCU_FPPFEAR_OFFSET(m)               (0x00000084 + ((m) * 0x00000008))  /* FPPFEAR Register %s */
/* FPPFSAR%s Registers (0-3) */
#define RZV_SCU_FPPFSAR_OFFSET(m)               (0x00000080 + ((m) * 0x00000008))  /* FPPFSAR Register %s */
#define RZV_SCU_SCUCR_OFFSET                             0x0000  /* SCUCR */
#define RZV_SCU_SCUCFR_OFFSET                            0x0004  /* SCUCFR */
#define RZV_SCU_SCUCPSR_OFFSET                           0x0008  /* SCUCPSR */
#define RZV_SCU_SCUIR_OFFSET                             0x000C  /* SCUIR */
#define RZV_SCU_MFSAR_OFFSET                             0x0040  /* MFSAR */
#define RZV_SCU_MFEAR_OFFSET                             0x0044  /* MFEAR */
#define RZV_SCU_PFSAR_OFFSET                             0x0048  /* PFSAR */
#define RZV_SCU_PFEAR_OFFSET                             0x004C  /* PFEAR */
#define RZV_SCU_SCUACR_OFFSET                            0x0050  /* SCUACR */
#define RZV_SCU_SCUEBFER_OFFSET                          0x0060  /* SCUEBFER */
#define RZV_SCU_SCUEBSER_OFFSET                          0x0064  /* SCUEBSER */
#define RZV_SCU_SCUDTROR_OFFSET                          0x0070  /* SCUDTROR */
#define RZV_SCU_SCUDTRDVR_OFFSET                         0x0074  /* SCUDTRDVR */
#define RZV_SCU_SCUDTRECR_OFFSET                         0x0078  /* SCUDTRECR */
#define RZV_SCU_ECCFER_OFFSET                            0x007C  /* ECCFER */

/* SCU Register Addresses **************************************************/

#define RZV_SCU_FPPFEAR(m)                      (RZV_SCU_BASE + RZV_SCU_FPPFEAR_OFFSET(m))
#define RZV_SCU_FPPFSAR(m)                      (RZV_SCU_BASE + RZV_SCU_FPPFSAR_OFFSET(m))
#define RZV_SCU_SCUCR                                (RZV_SCU_BASE + RZV_SCU_SCUCR_OFFSET)
#define RZV_SCU_SCUCFR                               (RZV_SCU_BASE + RZV_SCU_SCUCFR_OFFSET)
#define RZV_SCU_SCUCPSR                              (RZV_SCU_BASE + RZV_SCU_SCUCPSR_OFFSET)
#define RZV_SCU_SCUIR                                (RZV_SCU_BASE + RZV_SCU_SCUIR_OFFSET)
#define RZV_SCU_MFSAR                                (RZV_SCU_BASE + RZV_SCU_MFSAR_OFFSET)
#define RZV_SCU_MFEAR                                (RZV_SCU_BASE + RZV_SCU_MFEAR_OFFSET)
#define RZV_SCU_PFSAR                                (RZV_SCU_BASE + RZV_SCU_PFSAR_OFFSET)
#define RZV_SCU_PFEAR                                (RZV_SCU_BASE + RZV_SCU_PFEAR_OFFSET)
#define RZV_SCU_SCUACR                               (RZV_SCU_BASE + RZV_SCU_SCUACR_OFFSET)
#define RZV_SCU_SCUEBFER                             (RZV_SCU_BASE + RZV_SCU_SCUEBFER_OFFSET)
#define RZV_SCU_SCUEBSER                             (RZV_SCU_BASE + RZV_SCU_SCUEBSER_OFFSET)
#define RZV_SCU_SCUDTROR                             (RZV_SCU_BASE + RZV_SCU_SCUDTROR_OFFSET)
#define RZV_SCU_SCUDTRDVR                            (RZV_SCU_BASE + RZV_SCU_SCUDTRDVR_OFFSET)
#define RZV_SCU_SCUDTRECR                            (RZV_SCU_BASE + RZV_SCU_SCUDTRECR_OFFSET)
#define RZV_SCU_ECCFER                               (RZV_SCU_BASE + RZV_SCU_ECCFER_OFFSET)

/* SCU FPPFEAR Register Bit Definitions (Parameterized) ********************/

#define SCU_FPPFEAR_FEA_SHIFT                             (20)      /* Bits 20-31: Fea */
#define SCU_FPPFEAR_FEA_MASK(m)                           (0xfff << SCU_FPPFEAR_FEA_SHIFT)
#define SCU_FPPFEAR_FEA(m,val)                            (((val) << SCU_FPPFEAR_FEA_SHIFT) & SCU_FPPFEAR_FEA_MASK(m))

/* SCU FPPFSAR Register Bit Definitions (Parameterized) ********************/

#define SCU_FPPFSAR_FSA_SHIFT                             (20)      /* Bits 20-31: Fsa */
#define SCU_FPPFSAR_FSA_MASK(m)                           (0xfff << SCU_FPPFSAR_FSA_SHIFT)
#define SCU_FPPFSAR_FSA(m,val)                            (((val) << SCU_FPPFSAR_FSA_SHIFT) & SCU_FPPFSAR_FSA_MASK(m))

/* SCU ECCFER Register Bit Definitions *******************************/

/* EFEDC fields (parameterized for indices 0-3) */
#define SCU_ECCFER_EFEDC(n)                               (1u << (0 + ((unsigned)(n) * 1)))  /* Efedc0 */

#define SCU_ECCFER_EFED                         (1 << 8)  /* Efed */

/* SCU MFEAR Register Bit Definitions ********************************/

#define SCU_MFEAR_FEA_SHIFT                     (20)      /* Bits 20-31: Fea */
#define SCU_MFEAR_FEA_MASK                      (0xfff << SCU_MFEAR_FEA_SHIFT)

/* SCU MFSAR Register Bit Definitions ********************************/

#define SCU_MFSAR_FSA_SHIFT                     (20)      /* Bits 20-31: Fsa */
#define SCU_MFSAR_FSA_MASK                      (0xfff << SCU_MFSAR_FSA_SHIFT)

/* SCU PFEAR Register Bit Definitions ********************************/

#define SCU_PFEAR_FEA_SHIFT                     (20)      /* Bits 20-31: Fea */
#define SCU_PFEAR_FEA_MASK                      (0xfff << SCU_PFEAR_FEA_SHIFT)

/* SCU PFSAR Register Bit Definitions ********************************/

#define SCU_PFSAR_FSA_SHIFT                     (20)      /* Bits 20-31: Fsa */
#define SCU_PFSAR_FSA_MASK                      (0xfff << SCU_PFSAR_FSA_SHIFT)

/* SCU SCUACR Register Bit Definitions *******************************/

#define SCU_SCUACR_C0SCUA                       (1 << 0)  /* C0Scua */

#define SCU_SCUACR_C1SCUA                       (1 << 1)  /* C1Scua */

#define SCU_SCUACR_C2SCUA                       (1 << 2)  /* C2Scua */

#define SCU_SCUACR_C3SCUA                       (1 << 3)  /* C3Scua */

/* SCU SCUCFR Register Bit Definitions *******************************/

/* CSC fields (parameterized for indices 0-3) */
#define SCU_SCUCFR_CSC_SHIFT(n)                           ((unsigned)(8 + ((n) * 4)))  /* Bits for CSCn */
#define SCU_SCUCFR_CSC_MASK(n)                            (0xfu << SCU_SCUCFR_CSC_SHIFT(n))
#define SCU_SCUCFR_CSC_VAL(n,v)                           (((unsigned)(v) & 0xfu) << SCU_SCUCFR_CSC_SHIFT(n))

#define SCU_SCUCFR_NC_SHIFT                     (0)      /* Bits 0-1: Nc */
#define SCU_SCUCFR_NC_MASK                      (0x3 << SCU_SCUCFR_NC_SHIFT)

#define SCU_SCUCFR_CCM_SHIFT                    (4)      /* Bits 4-7: Ccm */
#define SCU_SCUCFR_CCM_MASK                     (0xf << SCU_SCUCFR_CCM_SHIFT)

#define SCU_SCUCFR_M                            (1 << 31)  /* M */

/* SCU SCUCPSR Register Bit Definitions ******************************/

#define SCU_SCUCPSR_C0S_SHIFT                   (0)      /* Bits 0-1: C0S */
#define SCU_SCUCPSR_C0S_MASK                    (0x3 << SCU_SCUCPSR_C0S_SHIFT)

#define SCU_SCUCPSR_C1S_SHIFT                   (8)      /* Bits 8-9: C1S */
#define SCU_SCUCPSR_C1S_MASK                    (0x3 << SCU_SCUCPSR_C1S_SHIFT)

#define SCU_SCUCPSR_C2S_SHIFT                   (16)      /* Bits 16-17: C2S */
#define SCU_SCUCPSR_C2S_MASK                    (0x3 << SCU_SCUCPSR_C2S_SHIFT)

#define SCU_SCUCPSR_C3S_SHIFT                   (24)      /* Bits 24-25: C3S */
#define SCU_SCUCPSR_C3S_MASK                    (0x3 << SCU_SCUCPSR_C3S_SHIFT)

/* SCU SCUCR Register Bit Definitions ********************************/

#define SCU_SCUCR_SCUE                          (1 << 0)  /* Scue */

#define SCU_SCUCR_AFE                           (1 << 1)  /* Afe */

#define SCU_SCUCR_SCUREE                        (1 << 2)  /* Scuree */

#define SCU_SCUCR_SCUSLE                        (1 << 3)  /* Scusle */

#define SCU_SCUCR_SCUSE                         (1 << 5)  /* Scuse */

#define SCU_SCUCR_ICSE                          (1 << 6)  /* Icse */

#define SCU_SCUCR_ECCCEM0                       (1 << 12)  /* Ecccem0 */

#define SCU_SCUCR_ECCCEM1                       (1 << 13)  /* Ecccem1 */

#define SCU_SCUCR_ECCCEMP                       (1 << 14)  /* Ecccemp */

#define SCU_SCUCR_ECCCEACP                      (1 << 15)  /* Eccceacp */

#define SCU_SCUCR_ECCCEC0FPP                    (1 << 16)  /* Ecccec0Fpp */

#define SCU_SCUCR_ECCCEC1FPP                    (1 << 17)  /* Ecccec1Fpp */

#define SCU_SCUCR_ECCCEC2FPP                    (1 << 18)  /* Ecccec2Fpp */

#define SCU_SCUCR_ECCCEC3FPP                    (1 << 19)  /* Ecccec3Fpp */

#define SCU_SCUCR_ECCCEAXITCM                   (1 << 20)  /* Eccceaxitcm */

/* SCU SCUDTRDVR Register Bit Definitions ****************************/

#define SCU_SCUDTRDVR_VM_SHIFT                  (17)      /* Bits 17-21: Vm */
#define SCU_SCUDTRDVR_VM_MASK                   (0x1f << SCU_SCUDTRDVR_VM_SHIFT)

#define SCU_SCUDTRDVR_VALID                     (1 << 22)  /* Valid */

/* SCU SCUDTRECR Register Bit Definitions ****************************/

#define SCU_SCUDTRECR_CHUNK_SHIFT               (0)      /* Bits 0-6: Chunk */
#define SCU_SCUDTRECR_CHUNK_MASK                (0x7f << SCU_SCUDTRECR_CHUNK_SHIFT)

/* SCU SCUDTROR Register Bit Definitions *****************************/

#define SCU_SCUDTROR_RW                         (1 << 0)  /* Rw */

#define SCU_SCUDTROR_SCURS_SHIFT                (5)      /* Bits 5-13: Scurs */
#define SCU_SCUDTROR_SCURS_MASK                 (0x1ff << SCU_SCUDTROR_SCURS_SHIFT)

#define SCU_SCUDTROR_SCURC_SHIFT                (24)      /* Bits 24-25: Scurc */
#define SCU_SCUDTROR_SCURC_MASK                 (0x3 << SCU_SCUDTROR_SCURC_SHIFT)

#define SCU_SCUDTROR_SCURW_SHIFT                (30)      /* Bits 30-31: Scurw */
#define SCU_SCUDTROR_SCURW_MASK                 (0x3 << SCU_SCUDTROR_SCURW_SHIFT)

/* SCU SCUEBFER Register Bit Definitions *****************************/

/* WFC fields (parameterized for indices 0-3) */
#define SCU_SCUEBFER_WFC_SHIFT(n)                         ((unsigned)(16 + ((n) * 4)))  /* Bits for WFCn */
#define SCU_SCUEBFER_WFC_MASK(n)                          (0xfu << SCU_SCUEBFER_WFC_SHIFT(n))
#define SCU_SCUEBFER_WFC_VAL(n,v)                         (((unsigned)(v) & 0xfu) << SCU_SCUEBFER_WFC_SHIFT(n))

#define SCU_SCUEBFER_STS                        (1 << 0)  /* Sts */

/* SCU SCUEBSER Register Bit Definitions *****************************/

#define SCU_SCUEBSER_STS_SHIFT                  (0)      /* Bits 0-1: Sts */
#define SCU_SCUEBSER_STS_MASK                   (0x3 << SCU_SCUEBSER_STS_SHIFT)

#define SCU_SCUEBSER_INDEX_SHIFT                (5)      /* Bits 5-13: Index */
#define SCU_SCUEBSER_INDEX_MASK                 (0x1ff << SCU_SCUEBSER_INDEX_SHIFT)

#define SCU_SCUEBSER_WAYS_SHIFT                 (16)      /* Bits 16-31: Ways */
#define SCU_SCUEBSER_WAYS_MASK                  (0xffff << SCU_SCUEBSER_WAYS_SHIFT)

/* SCU SCUIR Register Bit Definitions ********************************/

#define SCU_SCUIR_C0W_SHIFT                     (0)      /* Bits 0-3: C0W */
#define SCU_SCUIR_C0W_MASK                      (0xf << SCU_SCUIR_C0W_SHIFT)

#define SCU_SCUIR_C1W_SHIFT                     (4)      /* Bits 4-7: C1W */
#define SCU_SCUIR_C1W_MASK                      (0xf << SCU_SCUIR_C1W_SHIFT)

#define SCU_SCUIR_C2W_SHIFT                     (8)      /* Bits 8-11: C2W */
#define SCU_SCUIR_C2W_MASK                      (0xf << SCU_SCUIR_C2W_SHIFT)

#define SCU_SCUIR_C3W_SHIFT                     (12)      /* Bits 12-15: C3W */
#define SCU_SCUIR_C3W_MASK                      (0xf << SCU_SCUIR_C3W_SHIFT)

/* SCU Channel definitions */
#define RZV_SCU_CHANNEL_0          0

/* Maximum number of SCU channels */
#define RZV_SCU_MAX_CHANNELS       1

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_SCU_H */
