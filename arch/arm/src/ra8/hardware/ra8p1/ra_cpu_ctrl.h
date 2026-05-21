/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_cpu_ctrl.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CPU_CTRL_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CPU_CTRL_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* CPU_CTRL Base Address */
#ifndef R_CPU_CTRL_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_CPU_CTRL_BASE           0x4000f000
#else
#define R_CPU_CTRL_BASE           0x5000f000
#endif
#endif

/* CPU_CTRL Register Offsets */

/* CPU%sLCKUPCR Registers () */
#define R_CPU_CTRL_CPULCKUPCR_OFFSET(m)           (0x00000030 + ((m) * 0x00000004))  /* CPU%s Lockup Control Register */
/* CPU%sINITVTOR Registers () */
#define R_CPU_CTRL_CPUINITVTOR_OFFSET(m)          (0x00000040 + ((m) * 0x00000004))  /* CPU%s Initial Vector Base Address Register */
/* CPU%sWAITCR Registers () */
#define R_CPU_CTRL_CPUWAITCR_OFFSET(m)            (0x00000050 + ((m) * 0x00000004))  /* CPU%s CPUWAIT Control Register */
/* CPU%sACTCSR Registers () */
#define R_CPU_CTRL_CPUACTCSR_OFFSET(m)            (0x00000060 + ((m) * 0x00000004))  /* CPU%s Activation Control and Status Register */
#define R_CPU_CTRL_CPU0LMECR_OFFSET               0x00000070  /* CPU0 Local Memory Error Control Register */
#define R_CPU_CTRL_CPUIDR_OFFSET                  0x00000078  /* CPU Identification Register */
/* CPU%sSTATM Registers () */
#define R_CPU_CTRL_CPUSTATM_OFFSET(m)             (0x00000080 + ((m) * 0x00000004))  /* CPU%s Status Monitor Register */
#define R_CPU_CTRL_SECEXTMON_OFFSET               0x00000090  /* CPU SECEXT Monitor Register */
#define R_CPU_CTRL_NSCPUCR_OFFSET                 0x00000094  /* Non-secure CPU Control Register */
/* CPU%sLOCKCR Registers () */
#define R_CPU_CTRL_CPULOCKCR_OFFSET(m)            (0x00000400 + ((m) * 0x00000004))  /* CPU%s Function Lock Control Register */
/* CPU%sLOCKCRNS Registers () */
#define R_CPU_CTRL_CPULOCKCRNS_OFFSET(m)          (0x00000500 + ((m) * 0x00000004))  /* CPU%s Non-secure Function Lock Control Register */
/* CPU%sCRPT Registers () */
#define R_CPU_CTRL_CPUCRPT_OFFSET(m)              (0x00000840 + ((m) * 0x00000004))  /* CPU%s Control Register Protection Register */

/* CPU_CTRL Register Addresses */

#define R_CPU_CTRL_CPULCKUPCR(m)                  (R_CPU_CTRL_BASE + R_CPU_CTRL_CPULCKUPCR_OFFSET(m))
#define R_CPU_CTRL_CPUINITVTOR(m)                 (R_CPU_CTRL_BASE + R_CPU_CTRL_CPUINITVTOR_OFFSET(m))
#define R_CPU_CTRL_CPUWAITCR(m)                   (R_CPU_CTRL_BASE + R_CPU_CTRL_CPUWAITCR_OFFSET(m))
#define R_CPU_CTRL_CPUACTCSR(m)                   (R_CPU_CTRL_BASE + R_CPU_CTRL_CPUACTCSR_OFFSET(m))
#define R_CPU_CTRL_CPU0LMECR                      (R_CPU_CTRL_BASE + R_CPU_CTRL_CPU0LMECR_OFFSET)
#define R_CPU_CTRL_CPUIDR                         (R_CPU_CTRL_BASE + R_CPU_CTRL_CPUIDR_OFFSET)
#define R_CPU_CTRL_CPUSTATM(m)                    (R_CPU_CTRL_BASE + R_CPU_CTRL_CPUSTATM_OFFSET(m))
#define R_CPU_CTRL_SECEXTMON                      (R_CPU_CTRL_BASE + R_CPU_CTRL_SECEXTMON_OFFSET)
#define R_CPU_CTRL_NSCPUCR                        (R_CPU_CTRL_BASE + R_CPU_CTRL_NSCPUCR_OFFSET)
#define R_CPU_CTRL_CPULOCKCR(m)                   (R_CPU_CTRL_BASE + R_CPU_CTRL_CPULOCKCR_OFFSET(m))
#define R_CPU_CTRL_CPULOCKCRNS(m)                 (R_CPU_CTRL_BASE + R_CPU_CTRL_CPULOCKCRNS_OFFSET(m))
#define R_CPU_CTRL_CPUCRPT(m)                     (R_CPU_CTRL_BASE + R_CPU_CTRL_CPUCRPT_OFFSET(m))

/* Register bit definitions */
/* CPULCKUPCR Register bit definitions */
#define R_CPU_CTRL_CPULCKUPCR_OAD                 (1 << 0)  /* Operation after detection of CPUn lockup */

/* CPUINITVTOR Register bit definitions */
#define R_CPU_CTRL_CPUINITVTOR_CPUNINITVTOR_SHIFT (0)  /* CPUn Initial Vector Base Address */
#define R_CPU_CTRL_CPUINITVTOR_CPUNINITVTOR_MASK  0xffffffff

/* CPUWAITCR Register bit definitions */
#define R_CPU_CTRL_CPUWAITCR_CPUWAIT              (1 << 0)  /* Writing 1 to stall the CPUn when it is out of reset */

/* CPUACTCSR Register bit definitions */
#define R_CPU_CTRL_CPUACTCSR_ACTREQ               (1 << 0)  /* CPUn activation request */

#define R_CPU_CTRL_CPUACTCSR_ACT                  (1 << 7)  /* CPUn activation state */

#define R_CPU_CTRL_CPUACTCSR_KEY_SHIFT            (8)  /* Key code */
#define R_CPU_CTRL_CPUACTCSR_KEY_MASK             0xff00

/* CPU0LMECR Register bit definitions */
#define R_CPU_CTRL_CPU0LMECR_SYRSTEN              (1 << 0)  /* System Reset request enable */

/* CPUIDR Register bit definitions */
#define R_CPU_CTRL_CPUIDR_CPUID                   (1 << 0)  /* CPU Identification */

/* CPUSTATM Register bit definitions */
#define R_CPU_CTRL_CPUSTATM_SLEEPING              (1 << 0)  /* Sleeping State */

#define R_CPU_CTRL_CPUSTATM_SLEEPDEEP             (1 << 1)  /* Indicates that the processor is at a Deep Sleep mode */

#define R_CPU_CTRL_CPUSTATM_SAHBSTP               (1 << 4)  /* S-AHB Status Flag */

/* SECEXTMON Register bit definitions */
#define R_CPU_CTRL_SECEXTMON_SECEXT_S             (1 << 0)  /* CPU%s Security Extension */

#define R_CPU_CTRL_SECEXTMON_SECEXT0              (1 << 0)  /* CPU0 Security Extension */

#define R_CPU_CTRL_SECEXTMON_SECEXT1              (1 << 1)  /* CPU1 Security Extension */

/* NSCPUCR Register bit definitions */
#define R_CPU_CTRL_NSCPUCR_RSTREQEN               (1 << 0)  /* System Reset Request Enable */

/* CPULOCKCR Register bit definitions */
#define R_CPU_CTRL_CPULOCKCR_LCKSVTAIR            (1 << 0)  /* Disables writes to secure registers VTOR_S, AIRCR.PRIS, AIRCR.BFHFNMINS */

#define R_CPU_CTRL_CPULOCKCR_LCKSMPU              (1 << 1)  /* Disables writes to registers that are associated with the Secure MPU region */

#define R_CPU_CTRL_CPULOCKCR_LCKSAU               (1 << 2)  /* Disables writes to registers that are associated with the SAU region */

#define R_CPU_CTRL_CPULOCKCR_LCKITGU              (1 << 3)  /* Disables writes to registers that are associated with the ITCM interface */

#define R_CPU_CTRL_CPULOCKCR_LCKDTGU              (1 << 4)  /* Disables writes to registers that are associated with the DTCM interface */

#define R_CPU_CTRL_CPULOCKCR_LCKDCAIC             (1 << 5)  /* Disable access to the instruction cache direct cache access registers DCAICLR and DCAICRR */

/* CPULOCKCRNS Register bit definitions */
#define R_CPU_CTRL_CPULOCKCRNS_LCKNSVTOR          (1 << 0)  /* Disables writes to the VTOR_NS register */

#define R_CPU_CTRL_CPULOCKCRNS_LCKNSMPU           (1 << 1)  /* Disables writes to registers that are associated with the Non-secure MPU region */

/* CPUCRPT Register bit definitions */
#define R_CPU_CTRL_CPUCRPT_PROTECT                (1 << 0)  /* Protection of register */

#define R_CPU_CTRL_CPUCRPT_KEY_SHIFT              (8)  /* Key to enable/disable writing to PROTECT */
#define R_CPU_CTRL_CPUCRPT_KEY_MASK               0xff00


/* Maximum number of channels */

#define CPU_CTRL_MAX_CHANNELS    2

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CPU_CTRL_H */
