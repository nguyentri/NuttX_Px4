/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8e1/ra_cpu_dbg.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_CPU_DBG_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_CPU_DBG_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* CPU_DBG Base Address */
#ifndef R_CPU_DBG_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_CPU_DBG_BASE           0x4001b000
#else
#define R_CPU_DBG_BASE           0x5001b000
#endif
#endif

/* CPU_DBG Register Offsets */

#define R_CPU_DBG_DBGSTR_OFFSET                   0x00000000  /* Debug Status Register */
#define R_CPU_DBG_DBGSTOPCR_OFFSET                0x00000010  /* Debug Stop Control Register */
#define R_CPU_DBG_DBGAUTH0_OFFSET                 0x00000020  /* Debug Authentication Control Register 0 */
#define R_CPU_DBG_DBGAUTH1_OFFSET                 0x00000024  /* Debug Authentication Control Register 1 */
#define R_CPU_DBG_TRPORTCR_OFFSET                 0x00000030  /* Trace Port Control Register */
#define R_CPU_DBG_CACHEDBGCR_OFFSET               0x00000040  /* Cache Debug Control Register */
#define R_CPU_DBG_DBGMOCOEN_OFFSET                0x00000300  /* MOCO Enable Request Register for Debug */
#define R_CPU_DBG_DBGFCLKSEL_OFFSET               0x00000310  /* Flash Sequencer Clock Select Register for Debug */

/* CPU_DBG Register Addresses */

#define R_CPU_DBG_DBGSTR                          (R_CPU_DBG_BASE + R_CPU_DBG_DBGSTR_OFFSET)
#define R_CPU_DBG_DBGSTOPCR                       (R_CPU_DBG_BASE + R_CPU_DBG_DBGSTOPCR_OFFSET)
#define R_CPU_DBG_DBGAUTH0                        (R_CPU_DBG_BASE + R_CPU_DBG_DBGAUTH0_OFFSET)
#define R_CPU_DBG_DBGAUTH1                        (R_CPU_DBG_BASE + R_CPU_DBG_DBGAUTH1_OFFSET)
#define R_CPU_DBG_TRPORTCR                        (R_CPU_DBG_BASE + R_CPU_DBG_TRPORTCR_OFFSET)
#define R_CPU_DBG_CACHEDBGCR                      (R_CPU_DBG_BASE + R_CPU_DBG_CACHEDBGCR_OFFSET)
#define R_CPU_DBG_DBGMOCOEN                       (R_CPU_DBG_BASE + R_CPU_DBG_DBGMOCOEN_OFFSET)
#define R_CPU_DBG_DBGFCLKSEL                      (R_CPU_DBG_BASE + R_CPU_DBG_DBGFCLKSEL_OFFSET)

/* Register bit definitions */
/* DBGSTR Register bit definitions */
#define R_CPU_DBG_DBGSTR_CDBGPWRUPREQ             (1 << 28)  /* Debug power-up request */

#define R_CPU_DBG_DBGSTR_CDBGPWRUPACK             (1 << 29)  /* Debug power-up acknowledge */

/* DBGSTOPCR Register bit definitions */
#define R_CPU_DBG_DBGSTOPCR_DBGSTOP_IWDT          (1 << 0)  /* Mask bit for IWDT reset/interrupt in the OCD run mode */

#define R_CPU_DBG_DBGSTOPCR_DBGSTOP_WDT0          (1 << 1)  /* Mask bit for WDT reset/interrupt in the OCD run mode */

#define R_CPU_DBG_DBGSTOPCR_DBGSTOP_PVD           (1 << 17)  /* Mask bit for PVDn (n = 1, 2) reset/interrupt */

#define R_CPU_DBG_DBGSTOPCR_DBGSTOP_RER           (1 << 24)  /*  */

/* DBGAUTH0 Register bit definitions */
#define R_CPU_DBG_DBGAUTH0_DBGEN0                 (1 << 0)  /* CPU invasive debug enable */

#define R_CPU_DBG_DBGAUTH0_NIDEN0                 (1 << 4)  /* CPU non-invasive debug enable */

#define R_CPU_DBG_DBGAUTH0_DBGENAP                (1 << 8)  /* CPU AHB-AP (AP0) debug enable */

#define R_CPU_DBG_DBGAUTH0_DEVICEEN               (1 << 16)  /* APB-AP (AP1) authentication */

#define R_CPU_DBG_DBGAUTH0_SWDBG                  (1 << 31)  /* Software control of debug function */

/* DBGAUTH1 Register bit definitions */
#define R_CPU_DBG_DBGAUTH1_SPIDENAP               (1 << 8)  /* CPU AHB-AP (AP0) debug enable */

/* TRPORTCR Register bit definitions */
#define R_CPU_DBG_TRPORTCR_OE                     (1 << 0)  /* Data Out Enable bit indicates whether Trace Clock, Trace Data, and SWO outputs are enabled. */

#define R_CPU_DBG_TRPORTCR_DRV_SHIFT              (2)  /* Port Drive Capability Control indicates trace port buffer speed: */
#define R_CPU_DBG_TRPORTCR_DRV_MASK               0xc
#  define R_CPU_DBG_TRPORTCR_DRV_00                       (0 << R_CPU_DBG_TRPORTCR_DRV_SHIFT)  /* Low-drive */
#  define R_CPU_DBG_TRPORTCR_DRV_01                       (1 << R_CPU_DBG_TRPORTCR_DRV_SHIFT)  /* Middle-drive */
#  define R_CPU_DBG_TRPORTCR_DRV_10                       (2 << R_CPU_DBG_TRPORTCR_DRV_SHIFT)  /* High-speed high-drive */
#  define R_CPU_DBG_TRPORTCR_DRV_11                       (3 << R_CPU_DBG_TRPORTCR_DRV_SHIFT)  /* High-drive */

/* CACHEDBGCR Register bit definitions */
#define R_CPU_DBG_CACHEDBGCR_L1RSTDIS             (1 << 0)  /* Disable L1 cache automatic invalidation */

/* DBGMOCOEN Register bit definitions */
#define R_CPU_DBG_DBGMOCOEN_MOCOEN                (1 << 0)  /* MOCO enable request */

/* DBGFCLKSEL Register bit definitions */
#define R_CPU_DBG_DBGFCLKSEL_FCLKSEL              (1 << 0)  /* Flash sequencer clock select */


/* Maximum number of channels */

#define CPU_DBG_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_CPU_DBG_H */
