/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_cpu_dbg.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CPU_DBG_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CPU_DBG_H

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
#define R_CPU_DBG_DBGAUTH0_OFFSET                 0x00000020  /* Debug Authentication Control Register0 */
#define R_CPU_DBG_TRPORTCR_OFFSET                 0x00000030  /* Trace Port Control Register */
#define R_CPU_DBG_TRPORTSZ_OFFSET                 0x00000038  /* Trace Port Size Control Register */
#define R_CPU_DBG_CACHEDBGCR_OFFSET               0x00000040  /* Cache Debug Control Register */
#define R_CPU_DBG_DBGNVMCR_OFFSET                 0x00000050  /* Debug Non-volatile Memory Control Register */
#define R_CPU_DBG_ALCTRL_OFFSET                   0x00000100  /* Authentication Level Control Register */
#define R_CPU_DBG_FSBLSTAT_OFFSET                 0x00000200  /* First Stage Boot Loader Status Register */

/* CPU_DBG Register Addresses */

#define R_CPU_DBG_DBGSTR                          (R_CPU_DBG_BASE + R_CPU_DBG_DBGSTR_OFFSET)
#define R_CPU_DBG_DBGSTOPCR                       (R_CPU_DBG_BASE + R_CPU_DBG_DBGSTOPCR_OFFSET)
#define R_CPU_DBG_DBGAUTH0                        (R_CPU_DBG_BASE + R_CPU_DBG_DBGAUTH0_OFFSET)
#define R_CPU_DBG_TRPORTCR                        (R_CPU_DBG_BASE + R_CPU_DBG_TRPORTCR_OFFSET)
#define R_CPU_DBG_TRPORTSZ                        (R_CPU_DBG_BASE + R_CPU_DBG_TRPORTSZ_OFFSET)
#define R_CPU_DBG_CACHEDBGCR                      (R_CPU_DBG_BASE + R_CPU_DBG_CACHEDBGCR_OFFSET)
#define R_CPU_DBG_DBGNVMCR                        (R_CPU_DBG_BASE + R_CPU_DBG_DBGNVMCR_OFFSET)
#define R_CPU_DBG_ALCTRL                          (R_CPU_DBG_BASE + R_CPU_DBG_ALCTRL_OFFSET)
#define R_CPU_DBG_FSBLSTAT                        (R_CPU_DBG_BASE + R_CPU_DBG_FSBLSTAT_OFFSET)

/* Register bit definitions */
/* DBGSTR Register bit definitions */
#define R_CPU_DBG_DBGSTR_CDBGPWRUPREQ             (1 << 28)  /* Debug power-up request */

#define R_CPU_DBG_DBGSTR_CDBGPWRUPACK             (1 << 29)  /* Debug power-up acknowledge */

/* DBGSTOPCR Register bit definitions */
#define R_CPU_DBG_DBGSTOPCR_DBGSTOP_IWDT          (1 << 0)  /* Mask bit for IWDT reset/interrupt in the OCD run mode */

#define R_CPU_DBG_DBGSTOPCR_DBGSTOP_WDT0          (1 << 1)  /* Mask bit for WDT0 reset/interrupt in the OCD run mode */

#define R_CPU_DBG_DBGSTOPCR_DBGSTOP_WDT1          (1 << 2)  /* Mask bit for WDT1 reset/interrupt in the OCD run mode */

#define R_CPU_DBG_DBGSTOPCR_DBGSTOP_PVD           (1 << 17)  /* Mask bit for PVDn (n! = 0) reset/interrupt */

#define R_CPU_DBG_DBGSTOPCR_DBGSTOP_NVMERR        (1 << 26)  /* Mask bit for MRAM ECC error reset/interrupt */

#define R_CPU_DBG_DBGSTOPCR_DBGSTOP_CTERR0        (1 << 28)  /* Mask bit for Cache/TCM ECC error reset of CPU0 */

#define R_CPU_DBG_DBGSTOPCR_DBGSTOP_CTERR1        (1 << 29)  /* This bit is reserved. It can be R/W but has no effect. */

/* DBGAUTH0 Register bit definitions */
#define R_CPU_DBG_DBGAUTH0_DBGEN0                 (1 << 0)  /* CPU0 invasive debug enable */

#define R_CPU_DBG_DBGAUTH0_DBGEN1                 (1 << 1)  /* CPU1 invasive debug enable */

#define R_CPU_DBG_DBGAUTH0_NIDEN0                 (1 << 4)  /* CPU0 non-invasive debug enable */

#define R_CPU_DBG_DBGAUTH0_NIDEN1                 (1 << 5)  /* CPU1 non-invasive debug enable */

#define R_CPU_DBG_DBGAUTH0_DEVICEEN               (1 << 16)  /* APB-AP (AP1) authentication */

#define R_CPU_DBG_DBGAUTH0_SWDBG                  (1 << 31)  /* Software control of debug function */

/* TRPORTCR Register bit definitions */
#define R_CPU_DBG_TRPORTCR_OE                     (1 << 0)  /* OE bit should be enabled before trace clock is enabled. */

#define R_CPU_DBG_TRPORTCR_DRV_SHIFT              (2)  /* Port drive capability control indicates trace port buffer speed. */
#define R_CPU_DBG_TRPORTCR_DRV_MASK               0xc
#  define R_CPU_DBG_TRPORTCR_DRV_00                       (0 << R_CPU_DBG_TRPORTCR_DRV_SHIFT)  /* Low */
#  define R_CPU_DBG_TRPORTCR_DRV_01                       (1 << R_CPU_DBG_TRPORTCR_DRV_SHIFT)  /* Middle */
#  define R_CPU_DBG_TRPORTCR_DRV_10                       (2 << R_CPU_DBG_TRPORTCR_DRV_SHIFT)  /* High-Speed high-drive */
#  define R_CPU_DBG_TRPORTCR_DRV_11                       (3 << R_CPU_DBG_TRPORTCR_DRV_SHIFT)  /* High */

#define R_CPU_DBG_TRPORTCR_PORTSEL_SHIFT          (8)  /* Port select. Only A port setting is supported. */
#define R_CPU_DBG_TRPORTCR_PORTSEL_MASK           0x300
#  define R_CPU_DBG_TRPORTCR_PORTSEL_00                   (0 << R_CPU_DBG_TRPORTCR_PORTSEL_SHIFT)  /* A port */
#  define R_CPU_DBG_TRPORTCR_PORTSEL_01                   (1 << R_CPU_DBG_TRPORTCR_PORTSEL_SHIFT)  /* B port */

#define R_CPU_DBG_TRPORTCR_SWOSEL                 (1 << 16)  /* Select SWO between CPU0 and CPU1 */

/* TRPORTSZ Register bit definitions */
#define R_CPU_DBG_TRPORTSZ_PORTSIZE_SHIFT         (0)  /* Indicates how many pins of TRACEDATA are available. */
#define R_CPU_DBG_TRPORTSZ_PORTSIZE_MASK          0xffffffff

/* CACHEDBGCR Register bit definitions */
#define R_CPU_DBG_CACHEDBGCR_L1RSTDIS             (1 << 0)  /* Disable L1 cache automatic invalidation of CPU0 */

/* DBGNVMCR Register bit definitions */
#define R_CPU_DBG_DBGNVMCR_NVMWE                  (1 << 0)  /* Non-volatile memory write enable  */

/* ALCTRL Register bit definitions */
#define R_CPU_DBG_ALCTRL_AL_SHIFT                 (0)  /* AL monitor */
#define R_CPU_DBG_ALCTRL_AL_MASK                  0xff
#  define R_CPU_DBG_ALCTRL_AL_0X00                        (0 << R_CPU_DBG_ALCTRL_AL_SHIFT)  /* AL0 */
#  define R_CPU_DBG_ALCTRL_AL_0X05                        (5 << R_CPU_DBG_ALCTRL_AL_SHIFT)  /* AL1 */
#  define R_CPU_DBG_ALCTRL_AL_0XA5                        (165 << R_CPU_DBG_ALCTRL_AL_SHIFT)  /* AL2 */

#define R_CPU_DBG_ALCTRL_FAILCNT_SHIFT            (30)  /* Number of times responding to incorrect response data */
#define R_CPU_DBG_ALCTRL_FAILCNT_MASK             0xc0000000
#  define R_CPU_DBG_ALCTRL_FAILCNT_00                     (0 << R_CPU_DBG_ALCTRL_FAILCNT_SHIFT)  /* No responding to incorrect response data */
#  define R_CPU_DBG_ALCTRL_FAILCNT_01                     (1 << R_CPU_DBG_ALCTRL_FAILCNT_SHIFT)  /* First time of responding to incorrect response data */
#  define R_CPU_DBG_ALCTRL_FAILCNT_10                     (2 << R_CPU_DBG_ALCTRL_FAILCNT_SHIFT)  /* Second time of responding to incorrect response data */
#  define R_CPU_DBG_ALCTRL_FAILCNT_11                     (3 << R_CPU_DBG_ALCTRL_FAILCNT_SHIFT)  /* Third time of responding to incorrect response data */

/* FSBLSTAT Register bit definitions */
#define R_CPU_DBG_FSBLSTAT_CS                     (1 << 0)  /* FSBL completion status */

#define R_CPU_DBG_FSBLSTAT_RS                     (1 << 1)  /* FSBL result status */

#define R_CPU_DBG_FSBLSTAT_FSBLCLK_SHIFT          (8)  /* System clock frequency selection during FSBL execution */
#define R_CPU_DBG_FSBLSTAT_FSBLCLK_MASK           0x700


/* Maximum number of channels */

#define CPU_DBG_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CPU_DBG_H */
