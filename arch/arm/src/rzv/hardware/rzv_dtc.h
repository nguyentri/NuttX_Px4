/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_dtc.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_DTC_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_DTC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* DTC/XDTC Base Address - RZV2H uses XDTC (eXtended DTC)
 * Note: XDTC is integrated into the BSC (Bus State Controller)
 * Base address derived from FSP reference
 */

#define RZV_DTCBSC_BASE              0x11400400UL  /* DTC/BSC Control Base */
#define RZV_DTC_BASE                 RZV_DTCBSC_BASE

/* DTC Register Offsets */

#define RZV_DTC_DTCCR_OFFSET         0x0000  /* DTC Control Register */
#define RZV_DTC_DTCVBR_OFFSET        0x0004  /* DTC Vector Base Register */
#define RZV_DTC_DTCADMOD_OFFSET      0x0008  /* DTC Address Mode Register */
#define RZV_DTC_DTCST_OFFSET         0x000C  /* DTC Module Start Register */
#define RZV_DTC_DTCSTS_OFFSET        0x000E  /* DTC Status Register */
#define RZV_DTC_DTCIBR_OFFSET        0x0010  /* DTC Index Table Base Register */
#define RZV_DTC_DTCOR_OFFSET         0x0014  /* DTC Operation After Read Register */
#define RZV_DTC_DTCSQE_OFFSET        0x0016  /* DTC Sequence Transfer Enable Register */

/* DTC Register Addresses */

#define RZV_DTC_DTCCR                (RZV_DTC_BASE + RZV_DTC_DTCCR_OFFSET)
#define RZV_DTC_DTCVBR               (RZV_DTC_BASE + RZV_DTC_DTCVBR_OFFSET)
#define RZV_DTC_DTCADMOD             (RZV_DTC_BASE + RZV_DTC_DTCADMOD_OFFSET)
#define RZV_DTC_DTCST                (RZV_DTC_BASE + RZV_DTC_DTCST_OFFSET)
#define RZV_DTC_DTCSTS               (RZV_DTC_BASE + RZV_DTC_DTCSTS_OFFSET)
#define RZV_DTC_DTCIBR               (RZV_DTC_BASE + RZV_DTC_DTCIBR_OFFSET)
#define RZV_DTC_DTCOR                (RZV_DTC_BASE + RZV_DTC_DTCOR_OFFSET)
#define RZV_DTC_DTCSQE               (RZV_DTC_BASE + RZV_DTC_DTCSQE_OFFSET)

/* DTC Control Register (DTCCR) Bit Definitions */

#define RZV_DTC_DTCCR_RRS            (1 << 4)  /* DTC Transfer Information Read Skip Enable */

/* DTC Module Start Register (DTCST) Bit Definitions */

#define RZV_DTC_DTCST_DTCST          (1 << 0)  /* DTC Module Start */

/* DTC Status Register (DTCSTS) Bit Definitions */

#define RZV_DTC_DTCSTS_ACT           (1 << 15) /* DTC Active Flag */
#define RZV_DTC_DTCSTS_VECN_SHIFT    0         /* Vector Number Field */
#define RZV_DTC_DTCSTS_VECN_MASK     (0xFF << RZV_DTC_DTCSTS_VECN_SHIFT)

/* DTC Address Mode Register (DTCADMOD) Bit Definitions */

#define RZV_DTC_DTCADMOD_SHORT       (1 << 0)  /* Short Address Mode */

/* DTC Transfer Information Structure Layout
 * The DTC transfer information is stored in a 16-byte structure
 * with the following layout (little-endian):
 */

/* Mode Register A (MRA) - Offset 0x03 - Source Address Control */

#define RZV_DTC_MRA_MD_SHIFT         (6)       /* Transfer Mode */
#define RZV_DTC_MRA_MD_MASK          (0x3 << RZV_DTC_MRA_MD_SHIFT)
#define RZV_DTC_MRA_MD_NORMAL        (0x0 << RZV_DTC_MRA_MD_SHIFT)
#define RZV_DTC_MRA_MD_REPEAT        (0x1 << RZV_DTC_MRA_MD_SHIFT)
#define RZV_DTC_MRA_MD_BLOCK         (0x2 << RZV_DTC_MRA_MD_SHIFT)

#define RZV_DTC_MRA_SZ_SHIFT         (4)       /* Transfer Data Size */
#define RZV_DTC_MRA_SZ_MASK          (0x3 << RZV_DTC_MRA_SZ_SHIFT)
#define RZV_DTC_MRA_SZ_BYTE          (0x0 << RZV_DTC_MRA_SZ_SHIFT)
#define RZV_DTC_MRA_SZ_WORD          (0x1 << RZV_DTC_MRA_SZ_SHIFT)
#define RZV_DTC_MRA_SZ_LONG          (0x2 << RZV_DTC_MRA_SZ_SHIFT)

#define RZV_DTC_MRA_SM_SHIFT         (2)       /* Source Address Mode */
#define RZV_DTC_MRA_SM_MASK          (0x3 << RZV_DTC_MRA_SM_SHIFT)
#define RZV_DTC_MRA_SM_FIXED         (0x0 << RZV_DTC_MRA_SM_SHIFT)
#define RZV_DTC_MRA_SM_INCREMENT     (0x2 << RZV_DTC_MRA_SM_SHIFT)
#define RZV_DTC_MRA_SM_DECREMENT     (0x3 << RZV_DTC_MRA_SM_SHIFT)

/* Mode Register B (MRB) - Offset 0x02 - Destination Address Control */

#define RZV_DTC_MRB_CHNE             (1 << 7)  /* Chain Transfer Enable */
#define RZV_DTC_MRB_CHNS             (1 << 6)  /* Chain Transfer Select */
#define RZV_DTC_MRB_DISEL            (1 << 5)  /* DTC Interrupt Select */
#define RZV_DTC_MRB_DTS              (1 << 4)  /* DTC Transfer Mode Select */

#define RZV_DTC_MRB_DM_SHIFT         (2)       /* Destination Address Mode */
#define RZV_DTC_MRB_DM_MASK          (0x3 << RZV_DTC_MRB_DM_SHIFT)
#define RZV_DTC_MRB_DM_FIXED         (0x0 << RZV_DTC_MRB_DM_SHIFT)
#define RZV_DTC_MRB_DM_INCREMENT     (0x2 << RZV_DTC_MRB_DM_SHIFT)
#define RZV_DTC_MRB_DM_DECREMENT     (0x3 << RZV_DTC_MRB_DM_SHIFT)

/* DTC Configuration Limits */

#define RZV_DTC_MAX_NORMAL_LENGTH    (0x10000)  /* 65536 transfers max */
#define RZV_DTC_MAX_REPEAT_LENGTH    (0x400)    /* 1024 transfers max */
#define RZV_DTC_MAX_BLOCK_LENGTH     (0x400)    /* 1024 transfers max */

/* Vector Table Configuration */

#define RZV_DTC_VECTOR_TABLE_ALIGN   (1024)     /* 1KB alignment required */
#define RZV_DTC_VECTOR_TABLE_ENTRIES (512)      /* RZV2H supports more vectors */
#define RZV_DTC_TRANSFER_INFO_SIZE   (16)       /* 16 bytes per transfer info */

/* DTC Context Limits */

#define RZV_DTC_MAX_CONTEXTS         (32)       /* Maximum simultaneous DTC contexts */
#define RZV_DTC_MAX_TRANSFER_COUNT   (0x10000)  /* Maximum transfers in normal mode */
#define RZV_DTC_MAX_BLOCK_COUNT      (0x100)    /* Maximum block count */

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_DTC_H */
