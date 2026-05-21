/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_tzc.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_TZC_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_TZC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* TZC Register Offsets **************************************************/

/* CID%s Registers (0-3) */
#define RZV_TZC_CID_OFFSET(m)                  (0x00000fec + ((m) * 0x00000004))  /* CID Register %s */
/* FAIL_ADDRESS_HIGH%s Registers (0-3) */
#define RZV_TZC_FAIL_ADDRESS_HIGH_OFFSET(m)    (0x00000020 + ((m) * 0x00000010))  /* FAIL_ADDRESS_HIGH Register %s */
/* FAIL_ADDRESS_LOW%s Registers (0-3) */
#define RZV_TZC_FAIL_ADDRESS_LOW_OFFSET(m)     (0x0000001c + ((m) * 0x00000010))  /* FAIL_ADDRESS_LOW Register %s */
/* FAIL_CONTROL%s Registers (0-3) */
#define RZV_TZC_FAIL_CONTROL_OFFSET(m)         (0x00000024 + ((m) * 0x00000010))  /* FAIL_CONTROL Register %s */
/* FAIL_ID%s Registers (0-3) */
#define RZV_TZC_FAIL_ID_OFFSET(m)              (0x00000028 + ((m) * 0x00000010))  /* FAIL_ID Register %s */
/* REGION_ATTRIBUTES%s Registers (0-8) */
#define RZV_TZC_REGION_ATTRIBUTES_OFFSET(m)    (0x0000010c + ((m) * 0x00000020))  /* REGION_ATTRIBUTES Register %s */
/* REGION_BASE_HIGH%s Registers (0-8) */
#define RZV_TZC_REGION_BASE_HIGH_OFFSET(m)     (0x00000100 + ((m) * 0x00000020))  /* REGION_BASE_HIGH Register %s */
/* REGION_BASE_LOW%s Registers (0-8) */
#define RZV_TZC_REGION_BASE_LOW_OFFSET(m)      (0x000000fc + ((m) * 0x00000020))  /* REGION_BASE_LOW Register %s */
/* REGION_ID_ACCESS%s Registers (0-8) */
#define RZV_TZC_REGION_ID_ACCESS_OFFSET(m)     (0x00000110 + ((m) * 0x00000020))  /* REGION_ID_ACCESS Register %s */
/* REGION_TOP_HIGH%s Registers (0-8) */
#define RZV_TZC_REGION_TOP_HIGH_OFFSET(m)      (0x00000108 + ((m) * 0x00000020))  /* REGION_TOP_HIGH Register %s */
/* REGION_TOP_LOW%s Registers (0-8) */
#define RZV_TZC_REGION_TOP_LOW_OFFSET(m)       (0x00000104 + ((m) * 0x00000020))  /* REGION_TOP_LOW Register %s */
#define RZV_TZC_BUILD_CONFIG_OFFSET                     0x0000  /* BUILD_CONFIG */
#define RZV_TZC_ACTION_OFFSET                           0x0004  /* Action Register */
#define RZV_TZC_GATE_KEEPER_OFFSET                      0x0008  /* GATE_KEEPER */
#define RZV_TZC_SPECULATION_CTRL_OFFSET                 0x000C  /* SPECULATION_CTRL */
#define RZV_TZC_INT_STATUS_OFFSET                       0x0010  /* INT_STATUS */
#define RZV_TZC_PID4_OFFSET                             0x0FCC  /* PID4 */
#define RZV_TZC_PID5_OFFSET                             0x0FD0  /* PID5 */
#define RZV_TZC_PID6_OFFSET                             0x0FD4  /* PID6 */
#define RZV_TZC_PID7_OFFSET                             0x0FD8  /* PID7 */
#define RZV_TZC_PID0_OFFSET                             0x0FDC  /* PID0 */
#define RZV_TZC_PID1_OFFSET                             0x0FE0  /* PID1 */
#define RZV_TZC_PID2_OFFSET                             0x0FE4  /* PID2 */
#define RZV_TZC_PID3_OFFSET                             0x0FE8  /* PID3 */

/* TZC CID Register Bit Definitions (Parameterized) ***********************/

#define TZC_CID_CPI_SHIFT                                (0)      /* Bits 0-7: Cpi0 */
#define TZC_CID_CPI_MASK(m)                              (0xff << TZC_CID_CPI_SHIFT)
#define TZC_CID_CPI(m,val)                               (((val) << TZC_CID_CPI_SHIFT) & TZC_CID_CPI_MASK(m))

/* TZC FAIL_ADDRESS_HIGH Register Bit Definitions (Parameterized) *********/

#define TZC_FAIL_ADDRESS_HIGH_ASH(m)                     (1 << 0)  /* Ash */

/* TZC FAIL_ADDRESS_LOW Register Bit Definitions (Parameterized) **********/

#define TZC_FAIL_ADDRESS_LOW_ASL_SHIFT                   (0)      /* Bits 0-31: Asl */
#define TZC_FAIL_ADDRESS_LOW_ASL_MASK(m)                 (0xffffffff << TZC_FAIL_ADDRESS_LOW_ASL_SHIFT)
#define TZC_FAIL_ADDRESS_LOW_ASL(m,val)                  (((val) << TZC_FAIL_ADDRESS_LOW_ASL_SHIFT) & TZC_FAIL_ADDRESS_LOW_ASL_MASK(m))

/* TZC FAIL_CONTROL Register Bit Definitions (Parameterized) **************/

#define TZC_FAIL_CONTROL_PL(m)                           (1 << 20)  /* Pl */
#define TZC_FAIL_CONTROL_NS(m)                           (1 << 21)  /* Ns */
#define TZC_FAIL_CONTROL_DC(m)                           (1 << 24)  /* Dc */

/* TZC FAIL_ID Register Bit Definitions (Parameterized) *******************/

#define TZC_FAIL_ID_ID(m)                                (1 << 0)  /* Id */
#define TZC_FAIL_ID_VNET_SHIFT                           (24)      /* Bits 24-27: Vnet */
#define TZC_FAIL_ID_VNET_MASK(m)                         (0xf << TZC_FAIL_ID_VNET_SHIFT)
#define TZC_FAIL_ID_VNET(m,val)                          (((val) << TZC_FAIL_ID_VNET_SHIFT) & TZC_FAIL_ID_VNET_MASK(m))

/* TZC REGION_ATTRIBUTES Register Bit Definitions (Parameterized) *********/

#define TZC_REGION_ATTRIBUTES_FE_SHIFT                   (0)      /* Bits 0-3: Fe */
#define TZC_REGION_ATTRIBUTES_FE_MASK(m)                 (0xf << TZC_REGION_ATTRIBUTES_FE_SHIFT)
#define TZC_REGION_ATTRIBUTES_FE(m,val)                  (((val) << TZC_REGION_ATTRIBUTES_FE_SHIFT) & TZC_REGION_ATTRIBUTES_FE_MASK(m))
#define TZC_REGION_ATTRIBUTES_SRE(m)                     (1 << 30)  /* Sre */
#define TZC_REGION_ATTRIBUTES_SWE(m)                     (1 << 31)  /* Swe */

/* TZC REGION_BASE_HIGH Register Bit Definitions (Parameterized) **********/

#define TZC_REGION_BASE_HIGH_BAH(m)                      (1 << 0)  /* Bah */

/* TZC REGION_BASE_LOW Register Bit Definitions (Parameterized) ***********/

#define TZC_REGION_BASE_LOW_BAL_SHIFT                    (12)      /* Bits 12-31: Bal */
#define TZC_REGION_BASE_LOW_BAL_MASK(m)                  (0xfffff << TZC_REGION_BASE_LOW_BAL_SHIFT)
#define TZC_REGION_BASE_LOW_BAL(m,val)                   (((val) << TZC_REGION_BASE_LOW_BAL_SHIFT) & TZC_REGION_BASE_LOW_BAL_MASK(m))

/* TZC REGION_ID_ACCESS Register Bit Definitions (Parameterized) **********/

#define TZC_REGION_ID_ACCESS_NRE_SHIFT                   (0)      /* Bits 0-15: Nre */
#define TZC_REGION_ID_ACCESS_NRE_MASK(m)                 (0xffff << TZC_REGION_ID_ACCESS_NRE_SHIFT)
#define TZC_REGION_ID_ACCESS_NRE(m,val)                  (((val) << TZC_REGION_ID_ACCESS_NRE_SHIFT) & TZC_REGION_ID_ACCESS_NRE_MASK(m))
#define TZC_REGION_ID_ACCESS_NWE_SHIFT                   (16)      /* Bits 16-31: Nwe */
#define TZC_REGION_ID_ACCESS_NWE_MASK(m)                 (0xffff << TZC_REGION_ID_ACCESS_NWE_SHIFT)
#define TZC_REGION_ID_ACCESS_NWE(m,val)                  (((val) << TZC_REGION_ID_ACCESS_NWE_SHIFT) & TZC_REGION_ID_ACCESS_NWE_MASK(m))

/* TZC REGION_TOP_HIGH Register Bit Definitions (Parameterized) ***********/

#define TZC_REGION_TOP_HIGH_TAH(m)                       (1 << 0)  /* Tah */

/* TZC REGION_TOP_LOW Register Bit Definitions (Parameterized) ************/

#define TZC_REGION_TOP_LOW_TAL_SHIFT                     (12)      /* Bits 12-31: Tal */
#define TZC_REGION_TOP_LOW_TAL_MASK(m)                   (0xfffff << TZC_REGION_TOP_LOW_TAL_SHIFT)
#define TZC_REGION_TOP_LOW_TAL(m,val)                    (((val) << TZC_REGION_TOP_LOW_TAL_SHIFT) & TZC_REGION_TOP_LOW_TAL_MASK(m))

/* TZC ACTION Register Bit Definitions ******************************/

#define TZC_ACTION_RV_SHIFT                    (0)      /* Bits 0-1: Rv */
#define TZC_ACTION_RV_MASK                     (0x3 << TZC_ACTION_RV_SHIFT)

/* TZC BUILD_CONFIG Register Bit Definitions ************************/

#define TZC_BUILD_CONFIG_NOR_SHIFT             (0)      /* Bits 0-4: Nor */
#define TZC_BUILD_CONFIG_NOR_MASK              (0x1f << TZC_BUILD_CONFIG_NOR_SHIFT)

#define TZC_BUILD_CONFIG_ADDRW_SHIFT           (8)      /* Bits 8-13: Addrw */
#define TZC_BUILD_CONFIG_ADDRW_MASK            (0x3f << TZC_BUILD_CONFIG_ADDRW_SHIFT)

#define TZC_BUILD_CONFIG_NOF_SHIFT             (24)      /* Bits 24-25: Nof */
#define TZC_BUILD_CONFIG_NOF_MASK              (0x3 << TZC_BUILD_CONFIG_NOF_SHIFT)

/* TZC GATE_KEEPER Register Bit Definitions *************************/

#define TZC_GATE_KEEPER_OR_SHIFT               (0)      /* Bits 0-3: Or */
#define TZC_GATE_KEEPER_OR_MASK                (0xf << TZC_GATE_KEEPER_OR_SHIFT)

#define TZC_GATE_KEEPER_OS_SHIFT               (16)      /* Bits 16-19: Os */
#define TZC_GATE_KEEPER_OS_MASK                (0xf << TZC_GATE_KEEPER_OS_SHIFT)

/* TZC INT_CLEAR Register Bit Definitions ***************************/

#define TZC_INT_CLEAR_CLEAR_SHIFT              (0)      /* Bits 0-3: Clear */
#define TZC_INT_CLEAR_CLEAR_MASK               (0xf << TZC_INT_CLEAR_CLEAR_SHIFT)

/* TZC INT_STATUS Register Bit Definitions **************************/

#define TZC_INT_STATUS_STS_SHIFT               (0)      /* Bits 0-3: Sts */
#define TZC_INT_STATUS_STS_MASK                (0xf << TZC_INT_STATUS_STS_SHIFT)

#define TZC_INT_STATUS_OVERRUN_SHIFT           (8)      /* Bits 8-11: Overrun */
#define TZC_INT_STATUS_OVERRUN_MASK            (0xf << TZC_INT_STATUS_OVERRUN_SHIFT)

#define TZC_INT_STATUS_OVERLAP_SHIFT           (16)      /* Bits 16-19: Overlap */
#define TZC_INT_STATUS_OVERLAP_MASK            (0xf << TZC_INT_STATUS_OVERLAP_SHIFT)

/* TZC PID0 Register Bit Definitions ********************************/

#define TZC_PID0_JEP106_SHIFT                  (0)      /* Bits 0-3: Jep106 */
#define TZC_PID0_JEP106_MASK                   (0xf << TZC_PID0_JEP106_SHIFT)

#define TZC_PID0_CNT4KB_SHIFT                  (4)      /* Bits 4-7: Cnt4Kb */
#define TZC_PID0_CNT4KB_MASK                   (0xf << TZC_PID0_CNT4KB_SHIFT)

/* TZC PID1 Register Bit Definitions ********************************/

#define TZC_PID1_JEP106_SHIFT                  (0)      /* Bits 0-3: Jep106 */
#define TZC_PID1_JEP106_MASK                   (0xf << TZC_PID1_JEP106_SHIFT)

#define TZC_PID1_CNT4KB_SHIFT                  (4)      /* Bits 4-7: Cnt4Kb */
#define TZC_PID1_CNT4KB_MASK                   (0xf << TZC_PID1_CNT4KB_SHIFT)

/* TZC PID2 Register Bit Definitions ********************************/

#define TZC_PID2_JEP106_SHIFT                  (0)      /* Bits 0-3: Jep106 */
#define TZC_PID2_JEP106_MASK                   (0xf << TZC_PID2_JEP106_SHIFT)

#define TZC_PID2_CNT4KB_SHIFT                  (4)      /* Bits 4-7: Cnt4Kb */
#define TZC_PID2_CNT4KB_MASK                   (0xf << TZC_PID2_CNT4KB_SHIFT)

/* TZC PID3 Register Bit Definitions ********************************/

#define TZC_PID3_JEP106_SHIFT                  (0)      /* Bits 0-3: Jep106 */
#define TZC_PID3_JEP106_MASK                   (0xf << TZC_PID3_JEP106_SHIFT)

#define TZC_PID3_CNT4KB_SHIFT                  (4)      /* Bits 4-7: Cnt4Kb */
#define TZC_PID3_CNT4KB_MASK                   (0xf << TZC_PID3_CNT4KB_SHIFT)

/* TZC PID4 Register Bit Definitions ********************************/

#define TZC_PID4_JEP106_SHIFT                  (0)      /* Bits 0-3: Jep106 */
#define TZC_PID4_JEP106_MASK                   (0xf << TZC_PID4_JEP106_SHIFT)

#define TZC_PID4_CNT4KB_SHIFT                  (4)      /* Bits 4-7: Cnt4Kb */
#define TZC_PID4_CNT4KB_MASK                   (0xf << TZC_PID4_CNT4KB_SHIFT)

/* TZC PID5 Register Bit Definitions ********************************/

#define TZC_PID5_JEP106_SHIFT                  (0)      /* Bits 0-3: Jep106 */
#define TZC_PID5_JEP106_MASK                   (0xf << TZC_PID5_JEP106_SHIFT)

#define TZC_PID5_CNT4KB_SHIFT                  (4)      /* Bits 4-7: Cnt4Kb */
#define TZC_PID5_CNT4KB_MASK                   (0xf << TZC_PID5_CNT4KB_SHIFT)

/* TZC PID6 Register Bit Definitions ********************************/

#define TZC_PID6_JEP106_SHIFT                  (0)      /* Bits 0-3: Jep106 */
#define TZC_PID6_JEP106_MASK                   (0xf << TZC_PID6_JEP106_SHIFT)

#define TZC_PID6_CNT4KB_SHIFT                  (4)      /* Bits 4-7: Cnt4Kb */
#define TZC_PID6_CNT4KB_MASK                   (0xf << TZC_PID6_CNT4KB_SHIFT)

/* TZC PID7 Register Bit Definitions ********************************/

#define TZC_PID7_JEP106_SHIFT                  (0)      /* Bits 0-3: Jep106 */
#define TZC_PID7_JEP106_MASK                   (0xf << TZC_PID7_JEP106_SHIFT)

#define TZC_PID7_CNT4KB_SHIFT                  (4)      /* Bits 4-7: Cnt4Kb */
#define TZC_PID7_CNT4KB_MASK                   (0xf << TZC_PID7_CNT4KB_SHIFT)

/* TZC SPECULATION_CTRL Register Bit Definitions ********************/

#define TZC_SPECULATION_CTRL_RSD               (1 << 0)  /* Rsd */

#define TZC_SPECULATION_CTRL_WSD               (1 << 1)  /* Wsd */

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_TZC_H */
