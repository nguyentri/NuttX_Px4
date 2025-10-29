/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_debug.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DEBUG_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DEBUG_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* DEBUG Base Address */
#ifndef R_DEBUG_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_DEBUG_BASE           0x4001b000
#else
#define R_DEBUG_BASE           0x5001b000
#endif
#endif

/* DEBUG Register Offsets */

#define R_DEBUG_DBGSTR_OFFSET                     0x00000000  /* Debug Status Register */
#define R_DEBUG_DBGSTOPCR_OFFSET                  0x00000010  /* Debug Stop Control Register */
#define R_DEBUG_DBGAUTH0_OFFSET                   0x00000020  /* Debug Authentication Control Register0 */
#define R_DEBUG_TRPORTCR_OFFSET                   0x00000030  /* Trace Port Control Register */
#define R_DEBUG_TRPORTSZ_OFFSET                   0x00000038  /* Trace Port Size Control Register */
#define R_DEBUG_CACHEDBGCR_OFFSET                 0x00000040  /* Cache Debug Control Register */
#define R_DEBUG_DBGNVMCR_OFFSET                   0x00000050  /* Debug Non-volatile Memory Control Register */
#define R_DEBUG_ALCTRL_OFFSET                     0x00000100  /* Authentication Level Control Register */
#define R_DEBUG_FSBLSTAT_OFFSET                   0x00000200  /* First Stage Boot Loader Status Register */

/* DEBUG Register Addresses */

#define R_DEBUG_DBGSTR                            (R_DEBUG_BASE + R_DEBUG_DBGSTR_OFFSET)
#define R_DEBUG_DBGSTOPCR                         (R_DEBUG_BASE + R_DEBUG_DBGSTOPCR_OFFSET)
#define R_DEBUG_DBGAUTH0                          (R_DEBUG_BASE + R_DEBUG_DBGAUTH0_OFFSET)
#define R_DEBUG_TRPORTCR                          (R_DEBUG_BASE + R_DEBUG_TRPORTCR_OFFSET)
#define R_DEBUG_TRPORTSZ                          (R_DEBUG_BASE + R_DEBUG_TRPORTSZ_OFFSET)
#define R_DEBUG_CACHEDBGCR                        (R_DEBUG_BASE + R_DEBUG_CACHEDBGCR_OFFSET)
#define R_DEBUG_DBGNVMCR                          (R_DEBUG_BASE + R_DEBUG_DBGNVMCR_OFFSET)
#define R_DEBUG_ALCTRL                            (R_DEBUG_BASE + R_DEBUG_ALCTRL_OFFSET)
#define R_DEBUG_FSBLSTAT                          (R_DEBUG_BASE + R_DEBUG_FSBLSTAT_OFFSET)

/* Register bit definitions */
/* DBGSTR Register bit definitions */
#define R_DEBUG_DBGSTR_CDBGPWRUPREQ               (1 << 28)  /* Debug power-up request */

#define R_DEBUG_DBGSTR_CDBGPWRUPACK               (1 << 29)  /* Debug power-up acknowledge */

/* DBGSTOPCR Register bit definitions */
#define R_DEBUG_DBGSTOPCR_DBGSTOP_RPER            (1 << 24)  /* Mask bit for SRAM parity error */

#define R_DEBUG_DBGSTOPCR_DBGSTOP_TIM             (1 << 14)  /* Mask bit for RTC, TAU reset/interrupt */

#define R_DEBUG_DBGSTOPCR_DBGSTOP_SIR             (1 << 15)  /* Mask bit for SAU, IICA, PORT_IRQ0-5 reset/interrupt */

#define R_DEBUG_DBGSTOPCR_DBGSTOP_LVD_S           (1 << 16)  /* Mask bit for LVD reset/interrupt */

#define R_DEBUG_DBGSTOPCR_DBGSTOP_RECCR           (1 << 25)  /* Mask bit for SRAM ECC error */

#define R_DEBUG_DBGSTOPCR_DBGSTOP_IWDT            (1 << 0)  /* Mask bit for IWDT reset/interrupt */

#define R_DEBUG_DBGSTOPCR_DBGSTOP_WDT             (1 << 1)  /* Mask bit for WDT reset/interrupt  */

#define R_DEBUG_DBGSTOPCR_DBGSTOP_WDT1            (1 << 2)  /* Mask bit for WDT1 reset/interrupt in the OCD run mode */

#define R_DEBUG_DBGSTOPCR_DBGSTOP_NVMERR          (1 << 26)  /* Mask bit for MRAM ECC error reset/interrupt */

#define R_DEBUG_DBGSTOPCR_DBGSTOP_CTERR0          (1 << 28)  /* Mask bit for CPU0's Cache/TCM ECC error reset */

#define R_DEBUG_DBGSTOPCR_DBGSTOP_CTERR1          (1 << 29)  /* This bit is reserved. It can be R/W but no effect */

#define R_DEBUG_DBGSTOPCR_DBGSTOP_CPER            (1 << 31)  /* Mask bit for Cache SRAM parity error reset/interrupt */

#define R_DEBUG_DBGSTOPCR_DBGSTOP_LVD0            (1 << 16)  /* Mask bit for LVD reset/interrupt */

#define R_DEBUG_DBGSTOPCR_DBGSTOP_LVD1            (1 << 17)  /* Mask bit for LVD reset/interrupt */

#define R_DEBUG_DBGSTOPCR_DBGSTOP_LVD2            (1 << 18)  /* Mask bit for LVD reset/interrupt */

/* DBGAUTH0 Register bit definitions */
#define R_DEBUG_DBGAUTH0_DBGEN0                   (1 << 0)  /* CPU0 invasive debug enable */

#define R_DEBUG_DBGAUTH0_DBGEN1                   (1 << 1)  /* CPU1 invasive debug enable */

#define R_DEBUG_DBGAUTH0_NIDEN0                   (1 << 4)  /* CPU0 non-invasive debug enable */

#define R_DEBUG_DBGAUTH0_NIDEN1                   (1 << 5)  /* CPU1 non-invasive debug enable */

#define R_DEBUG_DBGAUTH0_DEVICEEN                 (1 << 16)  /* APB-AP (AP1) authentication */

#define R_DEBUG_DBGAUTH0_SWDBG                    (1 << 31)  /* Software control of debug function */

/* CACHEDBGCR Register bit definitions */
#define R_DEBUG_CACHEDBGCR_L1RSTDIS               (1 << 0)  /* Disable L1 cache automatic invalidation of CPU0 */

/* TRPORTCR Register bit definitions */
#define R_DEBUG_TRPORTCR_OE                       (1 << 0)  /* Data Out Enable bit indicates whether Trace Clock, Trace Data and SWO outputs are enabled or not. */

#define R_DEBUG_TRPORTCR_DRV_SHIFT                (2)  /* Port Drive Capability Control indicate trace port buffer speed */
#define R_DEBUG_TRPORTCR_DRV_MASK                 0xc
#  define R_DEBUG_TRPORTCR_DRV_00                         (0 << R_DEBUG_TRPORTCR_DRV_SHIFT)  /* Low */
#  define R_DEBUG_TRPORTCR_DRV_01                         (1 << R_DEBUG_TRPORTCR_DRV_SHIFT)  /* Middle */
#  define R_DEBUG_TRPORTCR_DRV_10                         (2 << R_DEBUG_TRPORTCR_DRV_SHIFT)  /* High-Speed high-drive */
#  define R_DEBUG_TRPORTCR_DRV_11                         (3 << R_DEBUG_TRPORTCR_DRV_SHIFT)  /* High */

#define R_DEBUG_TRPORTCR_PORTSEL_SHIFT            (8)  /* None */
#define R_DEBUG_TRPORTCR_PORTSEL_MASK             0x300
#  define R_DEBUG_TRPORTCR_PORTSEL_00                     (0 << R_DEBUG_TRPORTCR_PORTSEL_SHIFT)  /* A port */
#  define R_DEBUG_TRPORTCR_PORTSEL_01                     (1 << R_DEBUG_TRPORTCR_PORTSEL_SHIFT)  /* B port */

#define R_DEBUG_TRPORTCR_SWOSEL                   (1 << 16)  /* Select SWO between CPU0 and CPU1 */

/* ALCTRL Register bit definitions */
#define R_DEBUG_ALCTRL_AL_SHIFT                   (0)  /* AL monitor */
#define R_DEBUG_ALCTRL_AL_MASK                    0xff

#define R_DEBUG_ALCTRL_FAILCNT_SHIFT              (30)  /* Number of times responding incorrect response data */
#define R_DEBUG_ALCTRL_FAILCNT_MASK               0xc0000000
#  define R_DEBUG_ALCTRL_FAILCNT_00                       (0 << R_DEBUG_ALCTRL_FAILCNT_SHIFT)  /* No responding incorrect response data */
#  define R_DEBUG_ALCTRL_FAILCNT_01                       (1 << R_DEBUG_ALCTRL_FAILCNT_SHIFT)  /* First time of responding incorrect response data */
#  define R_DEBUG_ALCTRL_FAILCNT_10                       (2 << R_DEBUG_ALCTRL_FAILCNT_SHIFT)  /* Second time of responding incorrect response data */
#  define R_DEBUG_ALCTRL_FAILCNT_11                       (3 << R_DEBUG_ALCTRL_FAILCNT_SHIFT)  /* Third time of responding incorrect response data */

/* FSBLSTAT Register bit definitions */
#define R_DEBUG_FSBLSTAT_CS                       (1 << 0)  /* FSBL completion status. */

#define R_DEBUG_FSBLSTAT_RS                       (1 << 1)  /* FSBL result status. */

#define R_DEBUG_FSBLSTAT_FSBLCLK_SHIFT            (8)  /* System clock frequency selection during FSBL execution */
#define R_DEBUG_FSBLSTAT_FSBLCLK_MASK             0x700

/* TRPORTSZ Register bit definitions */
#define R_DEBUG_TRPORTSZ_PORTSIZE_SHIFT           (0)  /* Indicates how many pins of TRACEDATA are available. */
#define R_DEBUG_TRPORTSZ_PORTSIZE_MASK            0xffffffff

/* DBGNVMCR Register bit definitions */
#define R_DEBUG_DBGNVMCR_NVMWE                    (1 << 0)  /* Non-volatile memory write enable */


/* Maximum number of channels */

#define DEBUG_MAX_CHANNELS    1

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_DEBUG_H */
