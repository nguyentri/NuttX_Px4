/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_intc_gic.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_INTC_GIC_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_INTC_GIC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* INTC_GIC Base Addresses ***********************************************/

#ifndef RZV_INTC_GIC0_BASE
#  define RZV_INTC_GIC0_BASE          0x12C10100
#endif
#ifndef RZV_INTC_GIC_BASE
#  define RZV_INTC_GIC_BASE           RZV_INTC_GIC0_BASE
#endif

/* INTC_GIC Register Offsets **********************************************/

/* GICD_CIR%s Registers (0-3) */
#define RZV_INTC_GIC_GICD_CIR_OFFSET(m)         (0x00001ed0 + ((m) * 0x00000004))  /* GICD_CIR Register %s */
#define RZV_INTC_GIC_GICC_ICCICR_OFFSET                  0x0000  /* GICC_ICCICR */
#define RZV_INTC_GIC_GICC_ICCPMR_OFFSET                  0x0004  /* GICC_ICCPMR */
#define RZV_INTC_GIC_GICC_ICCBPR_OFFSET                  0x0008  /* GICC_ICCBPR */
#define RZV_INTC_GIC_GICC_ICCIAR_OFFSET                  0x000C  /* GICC_ICCIAR */
#define RZV_INTC_GIC_GICC_ICCEOIR_OFFSET                 0x0010  /* GICC_ICCEOIR */
#define RZV_INTC_GIC_GICC_ICCRPR_OFFSET                  0x0014  /* GICC_ICCRPR */
#define RZV_INTC_GIC_GICC_ICCHPIR_OFFSET                 0x0018  /* GICC_ICCHPIR */
#define RZV_INTC_GIC_GICC_ICCIIDR_OFFSET                 0x00FC  /* GICC_ICCIIDR */
#define RZV_INTC_GIC_GICD_ICDDCR_OFFSET                  0x0F00  /* GICD_ICDDCR */
#define RZV_INTC_GIC_GICD_ICDICTR_OFFSET                 0x0F04  /* GICD_ICDICTR */
#define RZV_INTC_GIC_GICD_ICDIIDR_OFFSET                 0x0F08  /* GICD_ICDIIDR */
#define RZV_INTC_GIC_GICD_PPI_OFFSET                     0x1BE0  /* GICD_PPI */
#define RZV_INTC_GIC_GICD_SPI_OFFSET                     0x1BE4  /* GICD_SPI */
#define RZV_INTC_GIC_GICD_ICDSGIR_OFFSET                 0x1DE0  /* GICD_ICDSGIR */
#define RZV_INTC_GIC_GICD_PIR4_OFFSET                    0x1EB0  /* GICD_PIR4 */
#define RZV_INTC_GIC_GICD_PIR0_OFFSET                    0x1EC0  /* GICD_PIR0 */
#define RZV_INTC_GIC_GICD_PIR1_OFFSET                    0x1EC4  /* GICD_PIR1 */
#define RZV_INTC_GIC_GICD_PIR2_OFFSET                    0x1EC8  /* GICD_PIR2 */
#define RZV_INTC_GIC_GICD_PIR3_OFFSET                    0x1ECC  /* GICD_PIR3 */

/* INTC_GIC Register Addresses *********************************************/

#define RZV_INTC_GIC_GICD_CIR(m)                (RZV_INTC_GIC_BASE + RZV_INTC_GIC_GICD_CIR_OFFSET(m))
#define RZV_INTC_GIC_GICC_ICCICR                     (RZV_INTC_GIC_BASE + RZV_INTC_GIC_GICC_ICCICR_OFFSET)
#define RZV_INTC_GIC_GICC_ICCPMR                     (RZV_INTC_GIC_BASE + RZV_INTC_GIC_GICC_ICCPMR_OFFSET)
#define RZV_INTC_GIC_GICC_ICCBPR                     (RZV_INTC_GIC_BASE + RZV_INTC_GIC_GICC_ICCBPR_OFFSET)
#define RZV_INTC_GIC_GICC_ICCIAR                     (RZV_INTC_GIC_BASE + RZV_INTC_GIC_GICC_ICCIAR_OFFSET)
#define RZV_INTC_GIC_GICC_ICCEOIR                    (RZV_INTC_GIC_BASE + RZV_INTC_GIC_GICC_ICCEOIR_OFFSET)
#define RZV_INTC_GIC_GICC_ICCRPR                     (RZV_INTC_GIC_BASE + RZV_INTC_GIC_GICC_ICCRPR_OFFSET)
#define RZV_INTC_GIC_GICC_ICCHPIR                    (RZV_INTC_GIC_BASE + RZV_INTC_GIC_GICC_ICCHPIR_OFFSET)
#define RZV_INTC_GIC_GICC_ICCIIDR                    (RZV_INTC_GIC_BASE + RZV_INTC_GIC_GICC_ICCIIDR_OFFSET)
#define RZV_INTC_GIC_GICD_ICDDCR                     (RZV_INTC_GIC_BASE + RZV_INTC_GIC_GICD_ICDDCR_OFFSET)
#define RZV_INTC_GIC_GICD_ICDICTR                    (RZV_INTC_GIC_BASE + RZV_INTC_GIC_GICD_ICDICTR_OFFSET)
#define RZV_INTC_GIC_GICD_ICDIIDR                    (RZV_INTC_GIC_BASE + RZV_INTC_GIC_GICD_ICDIIDR_OFFSET)
#define RZV_INTC_GIC_GICD_PPI                        (RZV_INTC_GIC_BASE + RZV_INTC_GIC_GICD_PPI_OFFSET)
#define RZV_INTC_GIC_GICD_SPI                        (RZV_INTC_GIC_BASE + RZV_INTC_GIC_GICD_SPI_OFFSET)
#define RZV_INTC_GIC_GICD_ICDSGIR                    (RZV_INTC_GIC_BASE + RZV_INTC_GIC_GICD_ICDSGIR_OFFSET)
#define RZV_INTC_GIC_GICD_PIR4                       (RZV_INTC_GIC_BASE + RZV_INTC_GIC_GICD_PIR4_OFFSET)
#define RZV_INTC_GIC_GICD_PIR0                       (RZV_INTC_GIC_BASE + RZV_INTC_GIC_GICD_PIR0_OFFSET)
#define RZV_INTC_GIC_GICD_PIR1                       (RZV_INTC_GIC_BASE + RZV_INTC_GIC_GICD_PIR1_OFFSET)
#define RZV_INTC_GIC_GICD_PIR2                       (RZV_INTC_GIC_BASE + RZV_INTC_GIC_GICD_PIR2_OFFSET)
#define RZV_INTC_GIC_GICD_PIR3                       (RZV_INTC_GIC_BASE + RZV_INTC_GIC_GICD_PIR3_OFFSET)

/* INTC_GIC GICD_CIR Register Bit Definitions (Parameterized) **************/

#define INTC_GIC_GICD_CIR_ID_SHIFT                        (0)      /* Bits 0-7: Id */
#define INTC_GIC_GICD_CIR_ID_MASK(m)                      (0xff << INTC_GIC_GICD_CIR_ID_SHIFT)
#define INTC_GIC_GICD_CIR_ID(m,val)                       (((val) << INTC_GIC_GICD_CIR_ID_SHIFT) & INTC_GIC_GICD_CIR_ID_MASK(m))

/* INTC_GIC GICC_ICCBPR Register Bit Definitions *********************/

#define INTC_GIC_GICC_ICCBPR_BP_SHIFT           (0)      /* Bits 0-2: Bp */
#define INTC_GIC_GICC_ICCBPR_BP_MASK            (0x7 << INTC_GIC_GICC_ICCBPR_BP_SHIFT)

/* INTC_GIC GICC_ICCEOIR Register Bit Definitions ********************/

#define INTC_GIC_GICC_ICCEOIR_EOIINTID_SHIFT    (0)      /* Bits 0-9: Eoiintid */
#define INTC_GIC_GICC_ICCEOIR_EOIINTID_MASK     (0x3ff << INTC_GIC_GICC_ICCEOIR_EOIINTID_SHIFT)

#define INTC_GIC_GICC_ICCEOIR_CPUID_SHIFT       (10)      /* Bits 10-12: Cpuid */
#define INTC_GIC_GICC_ICCEOIR_CPUID_MASK        (0x7 << INTC_GIC_GICC_ICCEOIR_CPUID_SHIFT)

/* INTC_GIC GICC_ICCHPIR Register Bit Definitions ********************/

#define INTC_GIC_GICC_ICCHPIR_PENDINTID_SHIFT   (0)      /* Bits 0-9: Pendintid */
#define INTC_GIC_GICC_ICCHPIR_PENDINTID_MASK    (0x3ff << INTC_GIC_GICC_ICCHPIR_PENDINTID_SHIFT)

#define INTC_GIC_GICC_ICCHPIR_CPUID_SHIFT       (10)      /* Bits 10-12: Cpuid */
#define INTC_GIC_GICC_ICCHPIR_CPUID_MASK        (0x7 << INTC_GIC_GICC_ICCHPIR_CPUID_SHIFT)

/* INTC_GIC GICC_ICCIAR Register Bit Definitions *********************/

#define INTC_GIC_GICC_ICCIAR_ACKINTID_SHIFT     (0)      /* Bits 0-9: Ackintid */
#define INTC_GIC_GICC_ICCIAR_ACKINTID_MASK      (0x3ff << INTC_GIC_GICC_ICCIAR_ACKINTID_SHIFT)

#define INTC_GIC_GICC_ICCIAR_CPUID_SHIFT        (10)      /* Bits 10-12: Cpuid */
#define INTC_GIC_GICC_ICCIAR_CPUID_MASK         (0x7 << INTC_GIC_GICC_ICCIAR_CPUID_SHIFT)

/* INTC_GIC GICC_ICCICR Register Bit Definitions *********************/

#define INTC_GIC_GICC_ICCICR_EN                 (1 << 0)  /* En */

/* INTC_GIC GICC_ICCIIDR Register Bit Definitions ********************/

#define INTC_GIC_GICC_ICCIIDR_I_SHIFT           (0)      /* Bits 0-11: I */
#define INTC_GIC_GICC_ICCIIDR_I_MASK            (0xfff << INTC_GIC_GICC_ICCIIDR_I_SHIFT)

#define INTC_GIC_GICC_ICCIIDR_RN_SHIFT          (12)      /* Bits 12-15: Rn */
#define INTC_GIC_GICC_ICCIIDR_RN_MASK           (0xf << INTC_GIC_GICC_ICCIIDR_RN_SHIFT)

#define INTC_GIC_GICC_ICCIIDR_AV_SHIFT          (16)      /* Bits 16-19: Av */
#define INTC_GIC_GICC_ICCIIDR_AV_MASK           (0xf << INTC_GIC_GICC_ICCIIDR_AV_SHIFT)

#define INTC_GIC_GICC_ICCIIDR_P_SHIFT           (20)      /* Bits 20-31: P */
#define INTC_GIC_GICC_ICCIIDR_P_MASK            (0xfff << INTC_GIC_GICC_ICCIIDR_P_SHIFT)

/* INTC_GIC GICC_ICCPMR Register Bit Definitions *********************/

#define INTC_GIC_GICC_ICCPMR_P_SHIFT            (0)      /* Bits 0-7: P */
#define INTC_GIC_GICC_ICCPMR_P_MASK             (0xff << INTC_GIC_GICC_ICCPMR_P_SHIFT)

/* INTC_GIC GICC_ICCRPR Register Bit Definitions *********************/

#define INTC_GIC_GICC_ICCRPR_P_SHIFT            (0)      /* Bits 0-7: P */
#define INTC_GIC_GICC_ICCRPR_P_MASK             (0xff << INTC_GIC_GICC_ICCRPR_P_SHIFT)

/* INTC_GIC GICD_ICDDCR Register Bit Definitions *********************/

#define INTC_GIC_GICD_ICDDCR_EN                 (1 << 0)  /* En */

/* INTC_GIC GICD_ICDICTR Register Bit Definitions ********************/

#define INTC_GIC_GICD_ICDICTR_IT_SHIFT          (0)      /* Bits 0-4: It */
#define INTC_GIC_GICD_ICDICTR_IT_MASK           (0x1f << INTC_GIC_GICD_ICDICTR_IT_SHIFT)

#define INTC_GIC_GICD_ICDICTR_CN_SHIFT          (5)      /* Bits 5-7: Cn */
#define INTC_GIC_GICD_ICDICTR_CN_MASK           (0x7 << INTC_GIC_GICD_ICDICTR_CN_SHIFT)

/* INTC_GIC GICD_ICDIIDR Register Bit Definitions ********************/

#define INTC_GIC_GICD_ICDIIDR_IN_SHIFT          (0)      /* Bits 0-11: In */
#define INTC_GIC_GICD_ICDIIDR_IN_MASK           (0xfff << INTC_GIC_GICD_ICDIIDR_IN_SHIFT)

#define INTC_GIC_GICD_ICDIIDR_RN_SHIFT          (12)      /* Bits 12-23: Rn */
#define INTC_GIC_GICD_ICDIIDR_RN_MASK           (0xfff << INTC_GIC_GICD_ICDIIDR_RN_SHIFT)

#define INTC_GIC_GICD_ICDIIDR_IV_SHIFT          (24)      /* Bits 24-31: Iv */
#define INTC_GIC_GICD_ICDIIDR_IV_MASK           (0xff << INTC_GIC_GICD_ICDIIDR_IV_SHIFT)

/* INTC_GIC GICD_ICDSGIR Register Bit Definitions ********************/

#define INTC_GIC_GICD_ICDSGIR_SGIINTID_SHIFT    (0)      /* Bits 0-3: Sgiintid */
#define INTC_GIC_GICD_ICDSGIR_SGIINTID_MASK     (0xf << INTC_GIC_GICD_ICDSGIR_SGIINTID_SHIFT)

#define INTC_GIC_GICD_ICDSGIR_SATT              (1 << 15)  /* Satt */

#define INTC_GIC_GICD_ICDSGIR_CPUTL_SHIFT       (16)      /* Bits 16-23: Cputl */
#define INTC_GIC_GICD_ICDSGIR_CPUTL_MASK        (0xff << INTC_GIC_GICD_ICDSGIR_CPUTL_SHIFT)

#define INTC_GIC_GICD_ICDSGIR_TLF_SHIFT         (24)      /* Bits 24-25: Tlf */
#define INTC_GIC_GICD_ICDSGIR_TLF_MASK          (0x3 << INTC_GIC_GICD_ICDSGIR_TLF_SHIFT)

/* INTC_GIC GICD_PIR0 Register Bit Definitions ***********************/

#define INTC_GIC_GICD_PIR0_ID_SHIFT             (0)      /* Bits 0-7: Id */
#define INTC_GIC_GICD_PIR0_ID_MASK              (0xff << INTC_GIC_GICD_PIR0_ID_SHIFT)

/* INTC_GIC GICD_PIR1 Register Bit Definitions ***********************/

#define INTC_GIC_GICD_PIR1_ID_SHIFT             (0)      /* Bits 0-7: Id */
#define INTC_GIC_GICD_PIR1_ID_MASK              (0xff << INTC_GIC_GICD_PIR1_ID_SHIFT)

/* INTC_GIC GICD_PIR2 Register Bit Definitions ***********************/

#define INTC_GIC_GICD_PIR2_ID_SHIFT             (0)      /* Bits 0-7: Id */
#define INTC_GIC_GICD_PIR2_ID_MASK              (0xff << INTC_GIC_GICD_PIR2_ID_SHIFT)

/* INTC_GIC GICD_PIR3 Register Bit Definitions ***********************/

#define INTC_GIC_GICD_PIR3_ID_SHIFT             (0)      /* Bits 0-7: Id */
#define INTC_GIC_GICD_PIR3_ID_MASK              (0xff << INTC_GIC_GICD_PIR3_ID_SHIFT)

/* INTC_GIC GICD_PIR4 Register Bit Definitions ***********************/

#define INTC_GIC_GICD_PIR4_ID_SHIFT             (0)      /* Bits 0-7: Id */
#define INTC_GIC_GICD_PIR4_ID_MASK              (0xff << INTC_GIC_GICD_PIR4_ID_SHIFT)

/* INTC_GIC GICD_PPI Register Bit Definitions ************************/

/* PPI fields (parameterized for indices 0-4) */
#define INTC_GIC_GICD_PPI_PPI(n)                          (1u << (11 + ((unsigned)(n) * 1)))  /* Ppi0 */

/* INTC_GIC GICD_SPI Register Bit Definitions ************************/

#define INTC_GIC_GICD_SPI_SPI_SHIFT             (0)      /* Bits 0-31: Spi */
#define INTC_GIC_GICD_SPI_SPI_MASK              (0xffffffff << INTC_GIC_GICD_SPI_SPI_SHIFT)

/* INTC_GIC GIC_GICD Register Bit Definitions ************************/

#define INTC_GIC_GIC_GICD_ICDABRn_AB_SHIFT      (0)      /* Bits 0-31: Icdabrn Ab */
#define INTC_GIC_GIC_GICD_ICDABRn_AB_MASK       (0xffffffff << INTC_GIC_GIC_GICD_ICDABRn_AB_SHIFT)

/* INTC_GIC GIC_GICD_ICDICERn Register Bit Definitions ***************/

#define INTC_GIC_GIC_GICD_ICDICERn_CEB_SHIFT    (0)      /* Bits 0-31: Ceb */
#define INTC_GIC_GIC_GICD_ICDICERn_CEB_MASK     (0xffffffff << INTC_GIC_GIC_GICD_ICDICERn_CEB_SHIFT)

/* INTC_GIC GIC_GICD_ICDICFRn_INT Register Bit Definitions ***********/

/* CON fields (parameterized for indices 0-15) */
#define INTC_GIC_GIC_GICD_ICDICFRn_INT_CON_SHIFT(n)       ((unsigned)(0 + ((n) * 2)))  /* Bits for CONn */
#define INTC_GIC_GIC_GICD_ICDICFRn_INT_CON_MASK(n)        (0x3u << INTC_GIC_GIC_GICD_ICDICFRn_INT_CON_SHIFT(n))
#define INTC_GIC_GIC_GICD_ICDICFRn_INT_CON_VAL(n,v)       (((unsigned)(v) & 0x3u) << INTC_GIC_GIC_GICD_ICDICFRn_INT_CON_SHIFT(n))

/* INTC_GIC GIC_GICD_ICDICPRn Register Bit Definitions ***************/

#define INTC_GIC_GIC_GICD_ICDICPRn_CPB_SHIFT    (0)      /* Bits 0-31: Cpb */
#define INTC_GIC_GIC_GICD_ICDICPRn_CPB_MASK     (0xffffffff << INTC_GIC_GIC_GICD_ICDICPRn_CPB_SHIFT)

/* INTC_GIC GIC_GICD_ICDIPRn Register Bit Definitions ****************/

/* PBO fields (parameterized for indices 0-3) */
#define INTC_GIC_GIC_GICD_ICDIPRn_PBO_SHIFT(n)            ((unsigned)(0 + ((n) * 8)))  /* Bits for PBOn */
#define INTC_GIC_GIC_GICD_ICDIPRn_PBO_MASK(n)             (0xffu << INTC_GIC_GIC_GICD_ICDIPRn_PBO_SHIFT(n))
#define INTC_GIC_GIC_GICD_ICDIPRn_PBO_VAL(n,v)            (((unsigned)(v) & 0xffu) << INTC_GIC_GIC_GICD_ICDIPRn_PBO_SHIFT(n))

/* INTC_GIC GIC_GICD_ICDIPTRn_CPU Register Bit Definitions ***********/

/* TBO fields (parameterized for indices 0-3) */
#define INTC_GIC_GIC_GICD_ICDIPTRn_CPU_TBO_SHIFT(n)       ((unsigned)(0 + ((n) * 8)))  /* Bits for TBOn */
#define INTC_GIC_GIC_GICD_ICDIPTRn_CPU_TBO_MASK(n)        (0xffu << INTC_GIC_GIC_GICD_ICDIPTRn_CPU_TBO_SHIFT(n))
#define INTC_GIC_GIC_GICD_ICDIPTRn_CPU_TBO_VAL(n,v)       (((unsigned)(v) & 0xffu) << INTC_GIC_GIC_GICD_ICDIPTRn_CPU_TBO_SHIFT(n))

/* INTC_GIC GIC_GICD_ICDISERn Register Bit Definitions ***************/

#define INTC_GIC_GIC_GICD_ICDISERn_SEB_SHIFT    (0)      /* Bits 0-31: Seb */
#define INTC_GIC_GIC_GICD_ICDISERn_SEB_MASK     (0xffffffff << INTC_GIC_GIC_GICD_ICDISERn_SEB_SHIFT)

/* INTC_GIC GIC_GICD_ICDISPRn Register Bit Definitions ***************/

#define INTC_GIC_GIC_GICD_ICDISPRn_CPB_SHIFT    (0)      /* Bits 0-31: Cpb */
#define INTC_GIC_GIC_GICD_ICDISPRn_CPB_MASK     (0xffffffff << INTC_GIC_GIC_GICD_ICDISPRn_CPB_SHIFT)

/* INTC_GIC Channel definitions */
#define RZV_INTC_GIC_CHANNEL_0     0

/* Maximum number of INTC_GIC channels */
#define RZV_INTC_GIC_MAX_CHANNELS  1

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_INTC_GIC_H */
