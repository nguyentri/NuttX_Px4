/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_npu.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_NPU_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_NPU_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* NPU Base Address */
#ifndef R_NPU_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_NPU_BASE           0x40140000
#else
#define R_NPU_BASE           0x50140000
#endif
#endif

/* NPU Register Offsets */

#define R_NPU_ID_OFFSET                           0x00000000  /* ID register */
#define R_NPU_STATUS_OFFSET                       0x00000004  /* Register describes the current operating status of the NPU */
#define R_NPU_CMD_OFFSET                          0x00000008  /* Command register, reads as last written command */
#define R_NPU_RESET_OFFSET                        0x0000000c  /* Request Reset and new security mode */
#define R_NPU_QBASE0_OFFSET                       0x00000010  /* Base address of Command-queue bits[31:0]. The address is 4-byte-aligned */
#define R_NPU_QBASE1_OFFSET                       0x00000014  /* Address extension bits[47:32] for queue base */
#define R_NPU_QREAD_OFFSET                        0x00000018  /* Read offset in the command stream in bytes. Multiples of 4 in the range 0-16 MB */
#define R_NPU_QCONFIG_OFFSET                      0x0000001c  /* AXI configuration for the command stream in the range 0-3. Same encoding as for REGIONCFG */
#define R_NPU_QSIZE_OFFSET                        0x00000020  /* Size of the command stream in bytes. Multiples of 4 in the range 0-16 MB */
#define R_NPU_PROT_OFFSET                         0x00000024  /* Protection level configured for the NPU when acting as an AXI master */
#define R_NPU_CONFIG_OFFSET                       0x00000028  /* RTL configuration */
#define R_NPU_LOCK_OFFSET                         0x0000002c  /* Lock register. This register is designed for driver use and does not affect NPU functionality */
#define R_NPU_REGIONCFG_OFFSET                    0x0000003c  /* Base pointer configuration. Bits[2*k+1:2*k] give the memory type for REGION[k] */
#define R_NPU_AXI_LIMIT0_OFFSET                   0x00000040  /* AXI limits for port 0 counter 0 */
#define R_NPU_AXI_LIMIT1_OFFSET                   0x00000044  /* AXI limits for port 0 counter 1 */
#define R_NPU_AXI_LIMIT2_OFFSET                   0x00000048  /* AXI limits for port 1 counter 2 */
#define R_NPU_AXI_LIMIT3_OFFSET                   0x0000004c  /* AXI limits for port 1 counter 3 */
#define R_NPU_BASEP0_OFFSET                       0x00000080  /* Lower 32 bits of the Base pointer for region index 0 */
#define R_NPU_BASEP1_OFFSET                       0x00000084  /* Upper 32 bits of the Base pointer for region index 0 */
#define R_NPU_BASEP2_OFFSET                       0x00000088  /* Lower 32 bits of the Base pointer for region index 1 */
#define R_NPU_BASEP3_OFFSET                       0x0000008c  /* Upper 32 bits of the Base pointer for region index 1 */
#define R_NPU_BASEP4_OFFSET                       0x00000090  /* Lower 32 bits of the Base pointer for region index 2 */
#define R_NPU_BASEP5_OFFSET                       0x00000094  /* Upper 32 bits of the Base pointer for region index 2 */
#define R_NPU_BASEP6_OFFSET                       0x00000098  /* Lower 32 bits of the Base pointer for region index 3 */
#define R_NPU_BASEP7_OFFSET                       0x0000009c  /* Upper 32 bits of the Base pointer for region index 3 */
#define R_NPU_BASEP8_OFFSET                       0x000000a0  /* Lower 32 bits of the Base pointer for region index 4 */
#define R_NPU_BASEP9_OFFSET                       0x000000a4  /* Upper 32 bits of the Base pointer for region index 4 */
#define R_NPU_BASEP10_OFFSET                      0x000000a8  /* Lower 32 bits of the Base pointer for region index 5 */
#define R_NPU_BASEP11_OFFSET                      0x000000ac  /* Upper 32 bits of the Base pointer for region index 5 */
#define R_NPU_BASEP12_OFFSET                      0x000000b0  /* Lower 32 bits of the Base pointer for region index 6 */
#define R_NPU_BASEP13_OFFSET                      0x000000b4  /* Upper 32 bits of the Base pointer for region index 6 */
#define R_NPU_BASEP14_OFFSET                      0x000000b8  /* Lower 32 bits of the Base pointer for region index 7 */
#define R_NPU_BASEP15_OFFSET                      0x000000bc  /* Upper 32 bits of the Base pointer for region index 7 */
#define R_NPU_PMCR_OFFSET                         0x00000180  /* PMU master control register */
#define R_NPU_PMCNTENSET_OFFSET                   0x00000184  /* Count-enable set register */
#define R_NPU_PMCNTENCLR_OFFSET                   0x00000188  /* Count-enable clear register */
#define R_NPU_PMOVSSET_OFFSET                     0x0000018c  /* Overflow-flag status set register */
#define R_NPU_PMOVSCLR_OFFSET                     0x00000190  /* Overflow-flag status clear register */
#define R_NPU_PMINTSET_OFFSET                     0x00000194  /* Interrupt-enable set register */
#define R_NPU_PMINTCLR_OFFSET                     0x00000198  /* Interrupt-enable clear register */
#define R_NPU_PMCCNTR_LO_OFFSET                   0x000001a0  /* Performance-monitor cycle count low register */
#define R_NPU_PMCCNTR_HI_OFFSET                   0x000001a4  /* Performance-monitor cycle count high register */
#define R_NPU_PMCAXI_CHAN_OFFSET                  0x000001ac  /* Set which AXI channel monitor */
/* PMU_EVCNTR%s Registers (0-3) */
#define R_NPU_PMU_EVCNTR_OFFSET(m)                (0x00000300 + ((m) * 0x00000004))  /* Performance-monitor event counters %s */
/* PMU_EVTYPER%s Registers (0-3) */
#define R_NPU_PMU_EVTYPER_OFFSET(m)               (0x00000380 + ((m) * 0x00000004))  /* Performance-monitor event-type control counters %s */
#define R_NPU_PID4_OFFSET                         0x00000fd0  /* Peripheral ID byte 4 (Arm=code 4) */
#define R_NPU_PID5_OFFSET                         0x00000fd4  /* Peripheral ID byte 5 (reserved) */
#define R_NPU_PID6_OFFSET                         0x00000fd8  /* Peripheral ID byte 6 (reserved) */
#define R_NPU_PID7_OFFSET                         0x00000fdc  /* Peripheral ID byte 7 (reserved) */
#define R_NPU_PID0_OFFSET                         0x00000fe0  /* Peripheral ID byte 0. This is bits[7:0] of the part number. */
#define R_NPU_PID1_OFFSET                         0x00000fe4  /* Peripheral ID byte 1. This is bits[11:8] of the part number in bits[3:0], and bits[3:0] of the Arm ID in bits[7:4]. */
#define R_NPU_PID2_OFFSET                         0x00000fe8  /* Peripheral ID byte 2. This is bits[6:4] of the Arm ID in bits[2:0], and bit 3 indicates format B. */
#define R_NPU_PID3_OFFSET                         0x00000fec  /* Peripheral ID byte 3. */
#define R_NPU_CID0_OFFSET                         0x00000ff0  /* Component ID byte 0. */
#define R_NPU_CID1_OFFSET                         0x00000ff4  /* Component ID byte 1. */
#define R_NPU_CID2_OFFSET                         0x00000ff8  /* Component ID byte 2. */
#define R_NPU_CID3_OFFSET                         0x00000ffc  /* Component ID byte 3. */

/* NPU Register Addresses */

#define R_NPU_ID                                  (R_NPU_BASE + R_NPU_ID_OFFSET)
#define R_NPU_STATUS                              (R_NPU_BASE + R_NPU_STATUS_OFFSET)
#define R_NPU_CMD                                 (R_NPU_BASE + R_NPU_CMD_OFFSET)
#define R_NPU_RESET                               (R_NPU_BASE + R_NPU_RESET_OFFSET)
#define R_NPU_QBASE0                              (R_NPU_BASE + R_NPU_QBASE0_OFFSET)
#define R_NPU_QBASE1                              (R_NPU_BASE + R_NPU_QBASE1_OFFSET)
#define R_NPU_QREAD                               (R_NPU_BASE + R_NPU_QREAD_OFFSET)
#define R_NPU_QCONFIG                             (R_NPU_BASE + R_NPU_QCONFIG_OFFSET)
#define R_NPU_QSIZE                               (R_NPU_BASE + R_NPU_QSIZE_OFFSET)
#define R_NPU_PROT                                (R_NPU_BASE + R_NPU_PROT_OFFSET)
#define R_NPU_CONFIG                              (R_NPU_BASE + R_NPU_CONFIG_OFFSET)
#define R_NPU_LOCK                                (R_NPU_BASE + R_NPU_LOCK_OFFSET)
#define R_NPU_REGIONCFG                           (R_NPU_BASE + R_NPU_REGIONCFG_OFFSET)
#define R_NPU_AXI_LIMIT0                          (R_NPU_BASE + R_NPU_AXI_LIMIT0_OFFSET)
#define R_NPU_AXI_LIMIT1                          (R_NPU_BASE + R_NPU_AXI_LIMIT1_OFFSET)
#define R_NPU_AXI_LIMIT2                          (R_NPU_BASE + R_NPU_AXI_LIMIT2_OFFSET)
#define R_NPU_AXI_LIMIT3                          (R_NPU_BASE + R_NPU_AXI_LIMIT3_OFFSET)
#define R_NPU_BASEP0                              (R_NPU_BASE + R_NPU_BASEP0_OFFSET)
#define R_NPU_BASEP1                              (R_NPU_BASE + R_NPU_BASEP1_OFFSET)
#define R_NPU_BASEP2                              (R_NPU_BASE + R_NPU_BASEP2_OFFSET)
#define R_NPU_BASEP3                              (R_NPU_BASE + R_NPU_BASEP3_OFFSET)
#define R_NPU_BASEP4                              (R_NPU_BASE + R_NPU_BASEP4_OFFSET)
#define R_NPU_BASEP5                              (R_NPU_BASE + R_NPU_BASEP5_OFFSET)
#define R_NPU_BASEP6                              (R_NPU_BASE + R_NPU_BASEP6_OFFSET)
#define R_NPU_BASEP7                              (R_NPU_BASE + R_NPU_BASEP7_OFFSET)
#define R_NPU_BASEP8                              (R_NPU_BASE + R_NPU_BASEP8_OFFSET)
#define R_NPU_BASEP9                              (R_NPU_BASE + R_NPU_BASEP9_OFFSET)
#define R_NPU_BASEP10                             (R_NPU_BASE + R_NPU_BASEP10_OFFSET)
#define R_NPU_BASEP11                             (R_NPU_BASE + R_NPU_BASEP11_OFFSET)
#define R_NPU_BASEP12                             (R_NPU_BASE + R_NPU_BASEP12_OFFSET)
#define R_NPU_BASEP13                             (R_NPU_BASE + R_NPU_BASEP13_OFFSET)
#define R_NPU_BASEP14                             (R_NPU_BASE + R_NPU_BASEP14_OFFSET)
#define R_NPU_BASEP15                             (R_NPU_BASE + R_NPU_BASEP15_OFFSET)
#define R_NPU_PMCR                                (R_NPU_BASE + R_NPU_PMCR_OFFSET)
#define R_NPU_PMCNTENSET                          (R_NPU_BASE + R_NPU_PMCNTENSET_OFFSET)
#define R_NPU_PMCNTENCLR                          (R_NPU_BASE + R_NPU_PMCNTENCLR_OFFSET)
#define R_NPU_PMOVSSET                            (R_NPU_BASE + R_NPU_PMOVSSET_OFFSET)
#define R_NPU_PMOVSCLR                            (R_NPU_BASE + R_NPU_PMOVSCLR_OFFSET)
#define R_NPU_PMINTSET                            (R_NPU_BASE + R_NPU_PMINTSET_OFFSET)
#define R_NPU_PMINTCLR                            (R_NPU_BASE + R_NPU_PMINTCLR_OFFSET)
#define R_NPU_PMCCNTR_LO                          (R_NPU_BASE + R_NPU_PMCCNTR_LO_OFFSET)
#define R_NPU_PMCCNTR_HI                          (R_NPU_BASE + R_NPU_PMCCNTR_HI_OFFSET)
#define R_NPU_PMCAXI_CHAN                         (R_NPU_BASE + R_NPU_PMCAXI_CHAN_OFFSET)
#define R_NPU_PMU_EVCNTR(m)                       (R_NPU_BASE + R_NPU_PMU_EVCNTR_OFFSET(m))
#define R_NPU_PMU_EVTYPER(m)                      (R_NPU_BASE + R_NPU_PMU_EVTYPER_OFFSET(m))
#define R_NPU_PID4                                (R_NPU_BASE + R_NPU_PID4_OFFSET)
#define R_NPU_PID5                                (R_NPU_BASE + R_NPU_PID5_OFFSET)
#define R_NPU_PID6                                (R_NPU_BASE + R_NPU_PID6_OFFSET)
#define R_NPU_PID7                                (R_NPU_BASE + R_NPU_PID7_OFFSET)
#define R_NPU_PID0                                (R_NPU_BASE + R_NPU_PID0_OFFSET)
#define R_NPU_PID1                                (R_NPU_BASE + R_NPU_PID1_OFFSET)
#define R_NPU_PID2                                (R_NPU_BASE + R_NPU_PID2_OFFSET)
#define R_NPU_PID3                                (R_NPU_BASE + R_NPU_PID3_OFFSET)
#define R_NPU_CID0                                (R_NPU_BASE + R_NPU_CID0_OFFSET)
#define R_NPU_CID1                                (R_NPU_BASE + R_NPU_CID1_OFFSET)
#define R_NPU_CID2                                (R_NPU_BASE + R_NPU_CID2_OFFSET)
#define R_NPU_CID3                                (R_NPU_BASE + R_NPU_CID3_OFFSET)

/* Register bit definitions */
/* ID Register bit definitions */
#define R_NPU_ID_ARCH_MAJOR_REV_SHIFT             (28)  /* This is the major architecture version number, a in the architecture version a.b */
#define R_NPU_ID_ARCH_MAJOR_REV_MASK              0xf0000000

#define R_NPU_ID_ARCH_MINOR_REV_SHIFT             (20)  /* This is the minor architecture version number, b in the architecture version a.b */
#define R_NPU_ID_ARCH_MINOR_REV_MASK              0xff00000

#define R_NPU_ID_ARCH_PATCH_REV_SHIFT             (16)  /* This is the patch number of the architecture version a.b */
#define R_NPU_ID_ARCH_PATCH_REV_MASK              0xf0000

#define R_NPU_ID_PRODUCT_MAJOR_SHIFT              (12)  /* This is the X-part of the ML00X product number */
#define R_NPU_ID_PRODUCT_MAJOR_MASK               0xf000

#define R_NPU_ID_VERSION_MAJOR_SHIFT              (8)  /* This is the n for the R-part of an RnPn release number */
#define R_NPU_ID_VERSION_MAJOR_MASK               0xf00

#define R_NPU_ID_VERSION_MINOR_SHIFT              (4)  /* This is the n for the P-part of an RnPn release number */
#define R_NPU_ID_VERSION_MINOR_MASK               0xf0

#define R_NPU_ID_VERSION_STATUS_SHIFT             (0)  /* This is the version of the product */
#define R_NPU_ID_VERSION_STATUS_MASK              0xf

#define R_NPU_ID_VERSION_STATUS_SHIFT             (0)  /* This is the version of the product */
#define R_NPU_ID_VERSION_STATUS_MASK              0xf

#define R_NPU_ID_VERSION_MINOR_SHIFT              (4)  /* This is the n for the P-part of an RnPn release number */
#define R_NPU_ID_VERSION_MINOR_MASK               0xf0

#define R_NPU_ID_VERSION_MAJOR_SHIFT              (8)  /* This is the n for the R-part of an RnPn release number */
#define R_NPU_ID_VERSION_MAJOR_MASK               0xf00

#define R_NPU_ID_PRODUCT_MAJOR_SHIFT              (12)  /* This is the X-part of the ML00X product number */
#define R_NPU_ID_PRODUCT_MAJOR_MASK               0xf000

#define R_NPU_ID_ARCH_PATCH_REV_SHIFT             (16)  /* This is the patch number of the architecture version a.b */
#define R_NPU_ID_ARCH_PATCH_REV_MASK              0xf0000

#define R_NPU_ID_ARCH_MINOR_REV_SHIFT             (20)  /* This is the minor architecture version number, b in the architecture version a.b */
#define R_NPU_ID_ARCH_MINOR_REV_MASK              0xff00000

#define R_NPU_ID_ARCH_MAJOR_REV_SHIFT             (28)  /* This is the major architecture version number, a in the architecture version a.b */
#define R_NPU_ID_ARCH_MAJOR_REV_MASK              0xf0000000

/* STATUS Register bit definitions */
#define R_NPU_STATUS_IRQ_HISTORY_MASK_SHIFT       (16)  /* IRQ History mask */
#define R_NPU_STATUS_IRQ_HISTORY_MASK_MASK        0xffff0000

#define R_NPU_STATUS_FAULTING_CHANNEL_SHIFT       (12)  /* Faulting channel on a bus abort. Read: 0=Cmd, 1=IFM, 2=Weights, 3=Scale+Bias, 4=Mem2Mem; Write: 8=OFM, 9=Mem2Mem */
#define R_NPU_STATUS_FAULTING_CHANNEL_MASK        0xf000

#define R_NPU_STATUS_FAULTING_INTERFACE           (1 << 11)  /* Faulting interface on bus abort. 0=AXI-M0, 1=AXI-M1 */

#define R_NPU_STATUS_ECC_FAULT                    (1 << 8)  /* ECC state for internal RAMs: 0=no fault, 1=ECC fault signalled. Can only be cleared by reset. */

#define R_NPU_STATUS_PMU_IRQ_RAISED               (1 << 6)  /* 0=No PMU IRQ, 1=PMU IRQ raised. Cleared by using command register bit 1 */

#define R_NPU_STATUS_CMD_END_REACHED              (1 << 5)  /* 0=Not reached, 1=Reached. Cleared by writing QBASE or QSIZE when the NPU is in stopped state. */

#define R_NPU_STATUS_CMD_PARSE_ERROR              (1 << 4)  /* 0=No error, 1=Command-stream parsing error detected. Can only be cleared by a reset. */

#define R_NPU_STATUS_RESET_STATUS                 (1 << 3)  /* Reset is ongoing and only this register can be read (other registers read as 0 and writes are ignored). A value of 0 means the NPU is not being reset and can be accessed as normal. */

#define R_NPU_STATUS_BUS_STATUS                   (1 << 2)  /* 0=OK, 1=Bus abort detected and processing halted (the NPU has reached IDLE state and does not start to process any more commands/AXI transactions). Can only be cleared by a reset. */

#define R_NPU_STATUS_IRQ_RAISED                   (1 << 1)  /* Raw IRQ status: 0 = IRQ not raised, 1 = IRQ raised. IRQ is cleared using command register bit 1. */

#define R_NPU_STATUS_STATE                        (1 << 0)  /* NPU state; 0 = Stopped, 1 = Running */

#define R_NPU_STATUS_STATE                        (1 << 0)  /* NPU state; 0 = Stopped, 1 = Running */

#define R_NPU_STATUS_IRQ_RAISED                   (1 << 1)  /* Raw IRQ status: 0 = IRQ not raised, 1 = IRQ raised. IRQ is cleared using command register bit 1. */

#define R_NPU_STATUS_BUS_STATUS                   (1 << 2)  /* 0=OK, 1=Bus abort detected and processing halted (the NPU has reached IDLE state and does not start to process any more commands/AXI transactions). Can only be cleared by a reset. */

#define R_NPU_STATUS_RESET_STATUS                 (1 << 3)  /* Reset is ongoing and only this register can be read (other registers read as 0 and writes are ignored). A value of 0 means the NPU is not being reset and can be accessed as normal. */

#define R_NPU_STATUS_CMD_PARSE_ERROR              (1 << 4)  /* 0=No error, 1=Command-stream parsing error detected. Can only be cleared by a reset. */

#define R_NPU_STATUS_CMD_END_REACHED              (1 << 5)  /* 0=Not reached, 1=Reached. Cleared by writing QBASE or QSIZE when the NPU is in stopped state. */

#define R_NPU_STATUS_PMU_IRQ_RAISED               (1 << 6)  /* 0=No PMU IRQ, 1=PMU IRQ raised. Cleared by using command register bit 1 */

#define R_NPU_STATUS_ECC_FAULT                    (1 << 8)  /* ECC state for internal RAMs: 0=no fault, 1=ECC fault signalled. Can only be cleared by reset. */

#define R_NPU_STATUS_FAULTING_INTERFACE           (1 << 11)  /* Faulting interface on bus abort. 0=AXI-M0, 1=AXI-M1 */

#define R_NPU_STATUS_FAULTING_CHANNEL_SHIFT       (12)  /* Faulting channel on a bus abort. Read: 0=Cmd, 1=IFM, 2=Weights, 3=Scale+Bias, 4=Mem2Mem; Write: 8=OFM, 9=Mem2Mem */
#define R_NPU_STATUS_FAULTING_CHANNEL_MASK        0xf000

#define R_NPU_STATUS_IRQ_HISTORY_MASK_SHIFT       (16)  /* IRQ History mask */
#define R_NPU_STATUS_IRQ_HISTORY_MASK_MASK        0xffff0000

/* CMD Register bit definitions */
#define R_NPU_CMD_CLEAR_IRQ_HISTORY_SHIFT         (16)  /* Clears the IRQ history mask */
#define R_NPU_CMD_CLEAR_IRQ_HISTORY_MASK          0xffff0000

#define R_NPU_CMD_POWER_Q_ENABLE                  (1 << 3)  /* Write 1 to this bit to enable power off using the Power Q-interface */

#define R_NPU_CMD_CLOCK_Q_ENABLE                  (1 << 2)  /* Write 1 to this bit to enable clock off using the Clock Q-interface and enable the main clock gate */

#define R_NPU_CMD_CLEAR_IRQ                       (1 << 1)  /* Write 1 to clear the IRQ status in the STATUS register. Writing 0 has no effect */

#define R_NPU_CMD_TRANSITION_TO_RUNNING_STATE     (1 << 0)  /* Write 1 to transition the NPU to running state. Writing 0 has no effect */

#define R_NPU_CMD_TRANSITION_TO_RUNNING_STATE     (1 << 0)  /* Write 1 to transition the NPU to running state. Writing 0 has no effect */

#define R_NPU_CMD_CLEAR_IRQ                       (1 << 1)  /* Write 1 to clear the IRQ status in the STATUS register. Writing 0 has no effect */

#define R_NPU_CMD_CLOCK_Q_ENABLE                  (1 << 2)  /* Write 1 to this bit to enable clock off using the Clock Q-interface and enable the main clock gate */

#define R_NPU_CMD_POWER_Q_ENABLE                  (1 << 3)  /* Write 1 to this bit to enable power off using the Power Q-interface */

#define R_NPU_CMD_CLEAR_IRQ_HISTORY_SHIFT         (16)  /* Clears the IRQ history mask */
#define R_NPU_CMD_CLEAR_IRQ_HISTORY_MASK          0xffff0000

/* RESET Register bit definitions */
#define R_NPU_RESET_PENDING_CSL                   (1 << 1)  /* Current security level: 0=Secure, 1=Non secure */

#define R_NPU_RESET_PENDING_CPL                   (1 << 0)  /* Current privilege level: 0=User, 1=Privileged */

#define R_NPU_RESET_PENDING_CPL                   (1 << 0)  /* Current privilege level: 0=User, 1=Privileged */

#define R_NPU_RESET_PENDING_CSL                   (1 << 1)  /* Current security level: 0=Secure, 1=Non secure */

/* QBASE0 Register bit definitions */
#define R_NPU_QBASE0_QBASE0_SHIFT                 (0)  /* The 4-byte-aligned lower bytes of the base address value for the command stream */
#define R_NPU_QBASE0_QBASE0_MASK                  0xffffffff

/* QBASE1 Register bit definitions */
#define R_NPU_QBASE1_QBASE1_SHIFT                 (0)  /* The 4-byte-aligned upper bytes of the base address value for the command stream */
#define R_NPU_QBASE1_QBASE1_MASK                  0xffffffff

/* QREAD Register bit definitions */
#define R_NPU_QREAD_QREAD_SHIFT                   (0)  /* The read offset of the current command under execution */
#define R_NPU_QREAD_QREAD_MASK                    0xffffffff

/* QCONFIG Register bit definitions */
#define R_NPU_QCONFIG_QCONFIG_SHIFT               (0)  /* AXI configuration for the command stream in the range 0-3 */
#define R_NPU_QCONFIG_QCONFIG_MASK                0xffffffff

/* QSIZE Register bit definitions */
#define R_NPU_QSIZE_QSIZE_SHIFT                   (0)  /* Size of the next command stream to be executed by the NPU */
#define R_NPU_QSIZE_QSIZE_MASK                    0xffffffff

/* PROT Register bit definitions */
#define R_NPU_PROT_ACTIVE_CSL                     (1 << 1)  /* Current security level: 0=Secure, 1=Non-secure */

#define R_NPU_PROT_ACTIVE_CPL                     (1 << 0)  /* Current privilege level: 0=User, 1=Privileged */

#define R_NPU_PROT_ACTIVE_CPL                     (1 << 0)  /* Current privilege level: 0=User, 1=Privileged */

#define R_NPU_PROT_ACTIVE_CSL                     (1 << 1)  /* Current security level: 0=Secure, 1=Non-secure */

/* CONFIG Register bit definitions */
#define R_NPU_CONFIG_PRODUCT_SHIFT                (28)  /* Product configuration */
#define R_NPU_CONFIG_PRODUCT_MASK                 0xf0000000

#define R_NPU_CONFIG_CUSTOM_DMA                   (1 << 27)  /* Custom DMA configuration */

#define R_NPU_CONFIG_SHRAM_SIZE_SHIFT             (8)  /* Size in KB of SHRAM in the range 8-48. */
#define R_NPU_CONFIG_SHRAM_SIZE_MASK              0xff00

#define R_NPU_CONFIG_CMD_STREAM_VERSION_SHIFT     (4)  /* Command-stream version accepted by this NPU. */
#define R_NPU_CONFIG_CMD_STREAM_VERSION_MASK      0xf0

#define R_NPU_CONFIG_MACS_PER_CC_SHIFT            (0)  /* The log2(macs/clock cycle). Valid encoding range is 5-8 for 32-256 MACs/clock cycle. */
#define R_NPU_CONFIG_MACS_PER_CC_MASK             0xf

#define R_NPU_CONFIG_MACS_PER_CC_SHIFT            (0)  /* The log2(macs/clock cycle). Valid encoding range is 5-8 for 32-256 MACs/clock cycle. */
#define R_NPU_CONFIG_MACS_PER_CC_MASK             0xf

#define R_NPU_CONFIG_CMD_STREAM_VERSION_SHIFT     (4)  /* Command-stream version accepted by this NPU. */
#define R_NPU_CONFIG_CMD_STREAM_VERSION_MASK      0xf0

#define R_NPU_CONFIG_SHRAM_SIZE_SHIFT             (8)  /* Size in KB of SHRAM in the range 8-48. */
#define R_NPU_CONFIG_SHRAM_SIZE_MASK              0xff00

#define R_NPU_CONFIG_CUSTOM_DMA                   (1 << 27)  /* Custom DMA configuration */

#define R_NPU_CONFIG_PRODUCT_SHIFT                (28)  /* Product configuration */
#define R_NPU_CONFIG_PRODUCT_MASK                 0xf0000000

/* LOCK Register bit definitions */
#define R_NPU_LOCK_LOCK_SHIFT                     (0)  /* 32-bit value for the LOCK configuration */
#define R_NPU_LOCK_LOCK_MASK                      0xffffffff

/* REGIONCFG Register bit definitions */
#define R_NPU_REGIONCFG_REGION7_SHIFT             (14)  /* Bits for the Region7 configuration */
#define R_NPU_REGIONCFG_REGION7_MASK              0xc000

#define R_NPU_REGIONCFG_REGION6_SHIFT             (12)  /* Bits for the Region6 configuration */
#define R_NPU_REGIONCFG_REGION6_MASK              0x3000

#define R_NPU_REGIONCFG_REGION5_SHIFT             (10)  /* Bits for the Region5 configuration */
#define R_NPU_REGIONCFG_REGION5_MASK              0xc00

#define R_NPU_REGIONCFG_REGION4_SHIFT             (8)  /* Bits for the Region4 configuration */
#define R_NPU_REGIONCFG_REGION4_MASK              0x300

#define R_NPU_REGIONCFG_REGION3_SHIFT             (6)  /* Bits for the Region3 configuration */
#define R_NPU_REGIONCFG_REGION3_MASK              0xc0

#define R_NPU_REGIONCFG_REGION2_SHIFT             (4)  /* Bits for the Region2 configuration */
#define R_NPU_REGIONCFG_REGION2_MASK              0x30

#define R_NPU_REGIONCFG_REGION1_SHIFT             (2)  /* Bits for the Region1 configuration */
#define R_NPU_REGIONCFG_REGION1_MASK              0xc

#define R_NPU_REGIONCFG_REGION0_SHIFT             (0)  /* Bits for the Region0 configuration */
#define R_NPU_REGIONCFG_REGION0_MASK              0x3

#define R_NPU_REGIONCFG_REGION0_SHIFT             (0)  /* Bits for the Region0 configuration */
#define R_NPU_REGIONCFG_REGION0_MASK              0x3

#define R_NPU_REGIONCFG_REGION1_SHIFT             (2)  /* Bits for the Region1 configuration */
#define R_NPU_REGIONCFG_REGION1_MASK              0xc

#define R_NPU_REGIONCFG_REGION2_SHIFT             (4)  /* Bits for the Region2 configuration */
#define R_NPU_REGIONCFG_REGION2_MASK              0x30

#define R_NPU_REGIONCFG_REGION3_SHIFT             (6)  /* Bits for the Region3 configuration */
#define R_NPU_REGIONCFG_REGION3_MASK              0xc0

#define R_NPU_REGIONCFG_REGION4_SHIFT             (8)  /* Bits for the Region4 configuration */
#define R_NPU_REGIONCFG_REGION4_MASK              0x300

#define R_NPU_REGIONCFG_REGION5_SHIFT             (10)  /* Bits for the Region5 configuration */
#define R_NPU_REGIONCFG_REGION5_MASK              0xc00

#define R_NPU_REGIONCFG_REGION6_SHIFT             (12)  /* Bits for the Region6 configuration */
#define R_NPU_REGIONCFG_REGION6_MASK              0x3000

#define R_NPU_REGIONCFG_REGION7_SHIFT             (14)  /* Bits for the Region7 configuration */
#define R_NPU_REGIONCFG_REGION7_MASK              0xc000

/* AXI_LIMIT0 Register bit definitions */
#define R_NPU_AXI_LIMIT0_MAX_OUTSTANDING_WRITE_M1_SHIFT (24)  /* Maximum number of outstanding AXI write transactions - 1 in range 0-15 */
#define R_NPU_AXI_LIMIT0_MAX_OUTSTANDING_WRITE_M1_MASK 0xff000000

#define R_NPU_AXI_LIMIT0_MAX_OUTSTANDING_READ_M1_SHIFT (16)  /* Maximum number of outstanding AXI read transactions - 1 in range 0-31 */
#define R_NPU_AXI_LIMIT0_MAX_OUTSTANDING_READ_M1_MASK 0xff0000

#define R_NPU_AXI_LIMIT0_MEMTYPE_SHIFT            (4)  /* Memtype */
#define R_NPU_AXI_LIMIT0_MEMTYPE_MASK             0xf0

#define R_NPU_AXI_LIMIT0_MAX_BEATS_SHIFT          (0)  /* Burst-split alignment: 0=64 bytes, 1=128 bytes, 2=256 bytes, 3=reserved */
#define R_NPU_AXI_LIMIT0_MAX_BEATS_MASK           0x3

#define R_NPU_AXI_LIMIT0_MAX_BEATS_SHIFT          (0)  /* Burst-split alignment: 0=64 bytes, 1=128 bytes, 2=256 bytes, 3=reserved */
#define R_NPU_AXI_LIMIT0_MAX_BEATS_MASK           0x3

#define R_NPU_AXI_LIMIT0_MEMTYPE_SHIFT            (4)  /* Memtype */
#define R_NPU_AXI_LIMIT0_MEMTYPE_MASK             0xf0

#define R_NPU_AXI_LIMIT0_MAX_OUTSTANDING_READ_M1_SHIFT (16)  /* Maximum number of outstanding AXI read transactions - 1 in range 0-31 */
#define R_NPU_AXI_LIMIT0_MAX_OUTSTANDING_READ_M1_MASK 0xff0000

#define R_NPU_AXI_LIMIT0_MAX_OUTSTANDING_WRITE_M1_SHIFT (24)  /* Maximum number of outstanding AXI write transactions - 1 in range 0-15 */
#define R_NPU_AXI_LIMIT0_MAX_OUTSTANDING_WRITE_M1_MASK 0xff000000

/* AXI_LIMIT1 Register bit definitions */
#define R_NPU_AXI_LIMIT1_MAX_OUTSTANDING_WRITE_M1_SHIFT (24)  /* Maximum number of outstanding AXI write transactions - 1 in range 0-15 */
#define R_NPU_AXI_LIMIT1_MAX_OUTSTANDING_WRITE_M1_MASK 0xff000000

#define R_NPU_AXI_LIMIT1_MAX_OUTSTANDING_READ_M1_SHIFT (16)  /* Maximum number of outstanding AXI read transactions - 1 in range 0-31 */
#define R_NPU_AXI_LIMIT1_MAX_OUTSTANDING_READ_M1_MASK 0xff0000

#define R_NPU_AXI_LIMIT1_MEMTYPE_SHIFT            (4)  /* Memtype */
#define R_NPU_AXI_LIMIT1_MEMTYPE_MASK             0xf0

#define R_NPU_AXI_LIMIT1_MAX_BEATS_SHIFT          (0)  /* Burst-split alignment: 0=64 bytes, 1=128 bytes, 2=256 bytes, 3=reserved */
#define R_NPU_AXI_LIMIT1_MAX_BEATS_MASK           0x3

#define R_NPU_AXI_LIMIT1_MAX_BEATS_SHIFT          (0)  /* Burst-split alignment: 0=64 bytes, 1=128 bytes, 2=256 bytes, 3=reserved */
#define R_NPU_AXI_LIMIT1_MAX_BEATS_MASK           0x3

#define R_NPU_AXI_LIMIT1_MEMTYPE_SHIFT            (4)  /* Memtype */
#define R_NPU_AXI_LIMIT1_MEMTYPE_MASK             0xf0

#define R_NPU_AXI_LIMIT1_MAX_OUTSTANDING_READ_M1_SHIFT (16)  /* Maximum number of outstanding AXI read transactions - 1 in range 0-31 */
#define R_NPU_AXI_LIMIT1_MAX_OUTSTANDING_READ_M1_MASK 0xff0000

#define R_NPU_AXI_LIMIT1_MAX_OUTSTANDING_WRITE_M1_SHIFT (24)  /* Maximum number of outstanding AXI write transactions - 1 in range 0-15 */
#define R_NPU_AXI_LIMIT1_MAX_OUTSTANDING_WRITE_M1_MASK 0xff000000

/* AXI_LIMIT2 Register bit definitions */
#define R_NPU_AXI_LIMIT2_MAX_OUTSTANDING_WRITE_M1_SHIFT (24)  /* Maximum number of outstanding AXI write transactions - 1 in range 0-15 */
#define R_NPU_AXI_LIMIT2_MAX_OUTSTANDING_WRITE_M1_MASK 0xff000000

#define R_NPU_AXI_LIMIT2_MAX_OUTSTANDING_READ_M1_SHIFT (16)  /* Maximum number of outstanding AXI read transactions - 1 in range 0-31 */
#define R_NPU_AXI_LIMIT2_MAX_OUTSTANDING_READ_M1_MASK 0xff0000

#define R_NPU_AXI_LIMIT2_MEMTYPE_SHIFT            (4)  /* Memtype */
#define R_NPU_AXI_LIMIT2_MEMTYPE_MASK             0xf0

#define R_NPU_AXI_LIMIT2_MAX_BEATS_SHIFT          (0)  /* Burst-split alignment: 0=64 bytes, 1=128 bytes, 2=256 bytes, 3=reserved */
#define R_NPU_AXI_LIMIT2_MAX_BEATS_MASK           0x3

#define R_NPU_AXI_LIMIT2_MAX_BEATS_SHIFT          (0)  /* Burst-split alignment: 0=64 bytes, 1=128 bytes, 2=256 bytes, 3=reserved */
#define R_NPU_AXI_LIMIT2_MAX_BEATS_MASK           0x3

#define R_NPU_AXI_LIMIT2_MEMTYPE_SHIFT            (4)  /* Memtype */
#define R_NPU_AXI_LIMIT2_MEMTYPE_MASK             0xf0

#define R_NPU_AXI_LIMIT2_MAX_OUTSTANDING_READ_M1_SHIFT (16)  /* Maximum number of outstanding AXI read transactions - 1 in range 0-31 */
#define R_NPU_AXI_LIMIT2_MAX_OUTSTANDING_READ_M1_MASK 0xff0000

#define R_NPU_AXI_LIMIT2_MAX_OUTSTANDING_WRITE_M1_SHIFT (24)  /* Maximum number of outstanding AXI write transactions - 1 in range 0-15 */
#define R_NPU_AXI_LIMIT2_MAX_OUTSTANDING_WRITE_M1_MASK 0xff000000

/* AXI_LIMIT3 Register bit definitions */
#define R_NPU_AXI_LIMIT3_MAX_OUTSTANDING_WRITE_M1_SHIFT (24)  /* Maximum number of outstanding AXI write transactions - 1 in range 0-15 */
#define R_NPU_AXI_LIMIT3_MAX_OUTSTANDING_WRITE_M1_MASK 0xff000000

#define R_NPU_AXI_LIMIT3_MAX_OUTSTANDING_READ_M1_SHIFT (16)  /* Maximum number of outstanding AXI read transactions - 1 in range 0-31 */
#define R_NPU_AXI_LIMIT3_MAX_OUTSTANDING_READ_M1_MASK 0xff0000

#define R_NPU_AXI_LIMIT3_MEMTYPE_SHIFT            (4)  /* Memtype */
#define R_NPU_AXI_LIMIT3_MEMTYPE_MASK             0xf0

#define R_NPU_AXI_LIMIT3_MAX_BEATS_SHIFT          (0)  /* Burst-split alignment: 0=64 bytes, 1=128 bytes, 2=256 bytes, 3=reserved */
#define R_NPU_AXI_LIMIT3_MAX_BEATS_MASK           0x3

#define R_NPU_AXI_LIMIT3_MAX_BEATS_SHIFT          (0)  /* Burst-split alignment: 0=64 bytes, 1=128 bytes, 2=256 bytes, 3=reserved */
#define R_NPU_AXI_LIMIT3_MAX_BEATS_MASK           0x3

#define R_NPU_AXI_LIMIT3_MEMTYPE_SHIFT            (4)  /* Memtype */
#define R_NPU_AXI_LIMIT3_MEMTYPE_MASK             0xf0

#define R_NPU_AXI_LIMIT3_MAX_OUTSTANDING_READ_M1_SHIFT (16)  /* Maximum number of outstanding AXI read transactions - 1 in range 0-31 */
#define R_NPU_AXI_LIMIT3_MAX_OUTSTANDING_READ_M1_MASK 0xff0000

#define R_NPU_AXI_LIMIT3_MAX_OUTSTANDING_WRITE_M1_SHIFT (24)  /* Maximum number of outstanding AXI write transactions - 1 in range 0-15 */
#define R_NPU_AXI_LIMIT3_MAX_OUTSTANDING_WRITE_M1_MASK 0xff000000

/* BASEP0 Register bit definitions */
#define R_NPU_BASEP0_ADDR_WORD_SHIFT              (0)  /* The low word of the 64-bit address */
#define R_NPU_BASEP0_ADDR_WORD_MASK               0xffffffff

#define R_NPU_BASEP0_ADDR_WORD_SHIFT              (0)  /* The low word of the 64-bit address */
#define R_NPU_BASEP0_ADDR_WORD_MASK               0xffffffff

/* BASEP1 Register bit definitions */
#define R_NPU_BASEP1_ADDR_WORD_SHIFT              (0)  /* The high word of the 64-bit address */
#define R_NPU_BASEP1_ADDR_WORD_MASK               0xffffffff

#define R_NPU_BASEP1_ADDR_WORD_SHIFT              (0)  /* The high word of the 64-bit address */
#define R_NPU_BASEP1_ADDR_WORD_MASK               0xffffffff

/* BASEP2 Register bit definitions */
#define R_NPU_BASEP2_ADDR_WORD_SHIFT              (0)  /* The low word of the 64-bit address */
#define R_NPU_BASEP2_ADDR_WORD_MASK               0xffffffff

#define R_NPU_BASEP2_ADDR_WORD_SHIFT              (0)  /* The low word of the 64-bit address */
#define R_NPU_BASEP2_ADDR_WORD_MASK               0xffffffff

/* BASEP3 Register bit definitions */
#define R_NPU_BASEP3_ADDR_WORD_SHIFT              (0)  /* The high word of the 64-bit address */
#define R_NPU_BASEP3_ADDR_WORD_MASK               0xffffffff

#define R_NPU_BASEP3_ADDR_WORD_SHIFT              (0)  /* The high word of the 64-bit address */
#define R_NPU_BASEP3_ADDR_WORD_MASK               0xffffffff

/* BASEP4 Register bit definitions */
#define R_NPU_BASEP4_ADDR_WORD_SHIFT              (0)  /* The low word of the 64-bit address */
#define R_NPU_BASEP4_ADDR_WORD_MASK               0xffffffff

#define R_NPU_BASEP4_ADDR_WORD_SHIFT              (0)  /* The low word of the 64-bit address */
#define R_NPU_BASEP4_ADDR_WORD_MASK               0xffffffff

/* BASEP5 Register bit definitions */
#define R_NPU_BASEP5_ADDR_WORD_SHIFT              (0)  /* The high word of the 64-bit address */
#define R_NPU_BASEP5_ADDR_WORD_MASK               0xffffffff

#define R_NPU_BASEP5_ADDR_WORD_SHIFT              (0)  /* The high word of the 64-bit address */
#define R_NPU_BASEP5_ADDR_WORD_MASK               0xffffffff

/* BASEP6 Register bit definitions */
#define R_NPU_BASEP6_ADDR_WORD_SHIFT              (0)  /* The low word of the 64-bit address */
#define R_NPU_BASEP6_ADDR_WORD_MASK               0xffffffff

#define R_NPU_BASEP6_ADDR_WORD_SHIFT              (0)  /* The low word of the 64-bit address */
#define R_NPU_BASEP6_ADDR_WORD_MASK               0xffffffff

/* BASEP7 Register bit definitions */
#define R_NPU_BASEP7_ADDR_WORD_SHIFT              (0)  /* The high word of the 64-bit address */
#define R_NPU_BASEP7_ADDR_WORD_MASK               0xffffffff

#define R_NPU_BASEP7_ADDR_WORD_SHIFT              (0)  /* The high word of the 64-bit address */
#define R_NPU_BASEP7_ADDR_WORD_MASK               0xffffffff

/* BASEP8 Register bit definitions */
#define R_NPU_BASEP8_ADDR_WORD_SHIFT              (0)  /* The low word of the 64-bit address */
#define R_NPU_BASEP8_ADDR_WORD_MASK               0xffffffff

#define R_NPU_BASEP8_ADDR_WORD_SHIFT              (0)  /* The low word of the 64-bit address */
#define R_NPU_BASEP8_ADDR_WORD_MASK               0xffffffff

/* BASEP9 Register bit definitions */
#define R_NPU_BASEP9_ADDR_WORD_SHIFT              (0)  /* The high word of the 64-bit address */
#define R_NPU_BASEP9_ADDR_WORD_MASK               0xffffffff

#define R_NPU_BASEP9_ADDR_WORD_SHIFT              (0)  /* The high word of the 64-bit address */
#define R_NPU_BASEP9_ADDR_WORD_MASK               0xffffffff

/* BASEP10 Register bit definitions */
#define R_NPU_BASEP10_ADDR_WORD_SHIFT             (0)  /* The low word of the 64-bit address */
#define R_NPU_BASEP10_ADDR_WORD_MASK              0xffffffff

#define R_NPU_BASEP10_ADDR_WORD_SHIFT             (0)  /* The low word of the 64-bit address */
#define R_NPU_BASEP10_ADDR_WORD_MASK              0xffffffff

/* BASEP11 Register bit definitions */
#define R_NPU_BASEP11_ADDR_WORD_SHIFT             (0)  /* The high word of the 64-bit address */
#define R_NPU_BASEP11_ADDR_WORD_MASK              0xffffffff

#define R_NPU_BASEP11_ADDR_WORD_SHIFT             (0)  /* The high word of the 64-bit address */
#define R_NPU_BASEP11_ADDR_WORD_MASK              0xffffffff

/* BASEP12 Register bit definitions */
#define R_NPU_BASEP12_ADDR_WORD_SHIFT             (0)  /* The low word of the 64-bit address */
#define R_NPU_BASEP12_ADDR_WORD_MASK              0xffffffff

#define R_NPU_BASEP12_ADDR_WORD_SHIFT             (0)  /* The low word of the 64-bit address */
#define R_NPU_BASEP12_ADDR_WORD_MASK              0xffffffff

/* BASEP13 Register bit definitions */
#define R_NPU_BASEP13_ADDR_WORD_SHIFT             (0)  /* The high word of the 64-bit address */
#define R_NPU_BASEP13_ADDR_WORD_MASK              0xffffffff

#define R_NPU_BASEP13_ADDR_WORD_SHIFT             (0)  /* The high word of the 64-bit address */
#define R_NPU_BASEP13_ADDR_WORD_MASK              0xffffffff

/* BASEP14 Register bit definitions */
#define R_NPU_BASEP14_ADDR_WORD_SHIFT             (0)  /* The low word of the 64-bit address */
#define R_NPU_BASEP14_ADDR_WORD_MASK              0xffffffff

#define R_NPU_BASEP14_ADDR_WORD_SHIFT             (0)  /* The low word of the 64-bit address */
#define R_NPU_BASEP14_ADDR_WORD_MASK              0xffffffff

/* BASEP15 Register bit definitions */
#define R_NPU_BASEP15_ADDR_WORD_SHIFT             (0)  /* The high word of the 64-bit address */
#define R_NPU_BASEP15_ADDR_WORD_MASK              0xffffffff

#define R_NPU_BASEP15_ADDR_WORD_SHIFT             (0)  /* The high word of the 64-bit address */
#define R_NPU_BASEP15_ADDR_WORD_MASK              0xffffffff

/* PID4 Register bit definitions */
#define R_NPU_PID4_PID4_SHIFT                     (0)  /* Byte 4 of the Peripheral ID (Lower 8 bits valid) */
#define R_NPU_PID4_PID4_MASK                      0xffffffff

/* PID5 Register bit definitions */
#define R_NPU_PID5_PID5_SHIFT                     (0)  /* Byte 5 of the Peripheral ID (Lower 8 bits valid) */
#define R_NPU_PID5_PID5_MASK                      0xffffffff

/* PID6 Register bit definitions */
#define R_NPU_PID6_PID6_SHIFT                     (0)  /* Byte 6 of the Peripheral ID (Lower 8 bits valid) */
#define R_NPU_PID6_PID6_MASK                      0xffffffff

/* PID7 Register bit definitions */
#define R_NPU_PID7_PID7_SHIFT                     (0)  /* Byte 7 of the Peripheral ID (Lower 8 bits valid) */
#define R_NPU_PID7_PID7_MASK                      0xffffffff

/* PID0 Register bit definitions */
#define R_NPU_PID0_PID0_SHIFT                     (0)  /* Byte 0 of the Peripheral ID (Lower 8 bits valid) */
#define R_NPU_PID0_PID0_MASK                      0xffffffff

/* PID1 Register bit definitions */
#define R_NPU_PID1_PID1_SHIFT                     (0)  /* Byte 1 of the Peripheral ID (Lower 8 bits valid) */
#define R_NPU_PID1_PID1_MASK                      0xffffffff

/* PID2 Register bit definitions */
#define R_NPU_PID2_PID2_SHIFT                     (0)  /* Byte 2 of the Peripheral ID (Lower 8 bits valid) */
#define R_NPU_PID2_PID2_MASK                      0xffffffff

/* PID3 Register bit definitions */
#define R_NPU_PID3_PID3_SHIFT                     (0)  /* Byte 3 of the Peripheral ID (Lower 8 bits valid) */
#define R_NPU_PID3_PID3_MASK                      0xffffffff

/* CID0 Register bit definitions */
#define R_NPU_CID0_CID0_SHIFT                     (0)  /* Byte 0 of the Component ID (Lower 8 bits valid) */
#define R_NPU_CID0_CID0_MASK                      0xffffffff

/* CID1 Register bit definitions */
#define R_NPU_CID1_CID1_SHIFT                     (0)  /* Byte 1 of the Component ID (Lower 8 bits valid) */
#define R_NPU_CID1_CID1_MASK                      0xffffffff

/* CID2 Register bit definitions */
#define R_NPU_CID2_CID2_SHIFT                     (0)  /* Byte 2 of the Component ID (Lower 8 bits valid) */
#define R_NPU_CID2_CID2_MASK                      0xffffffff

/* CID3 Register bit definitions */
#define R_NPU_CID3_CID3_SHIFT                     (0)  /* Byte 3 of the Component ID (Lower 8 bits valid) */
#define R_NPU_CID3_CID3_MASK                      0xffffffff

/* PMCR Register bit definitions */
#define R_NPU_PMCR_NUM_EVENT_CNT_SHIFT            (11)  /* Number of event counters available for performance measurement */
#define R_NPU_PMCR_NUM_EVENT_CNT_MASK             0xf800

#define R_NPU_PMCR_MASK_EN                        (1 << 3)  /* PMU can be enabled/disabled by command stream operationNPU_OP_PMU_MASK */

#define R_NPU_PMCR_CYCLE_CNT_RST                  (1 << 2)  /* Reset cycle counter */

#define R_NPU_PMCR_EVENT_CNT_RST                  (1 << 1)  /* Reset event counter */

#define R_NPU_PMCR_CNT_EN                         (1 << 0)  /* Enable counter */

#define R_NPU_PMCR_CNT_EN                         (1 << 0)  /* Enable counter */

#define R_NPU_PMCR_EVENT_CNT_RST                  (1 << 1)  /* Reset event counter */

#define R_NPU_PMCR_CYCLE_CNT_RST                  (1 << 2)  /* Reset cycle counter */

#define R_NPU_PMCR_MASK_EN                        (1 << 3)  /* PMU can be enabled/disabled by command stream operationNPU_OP_PMU_MASK */

#define R_NPU_PMCR_NUM_EVENT_CNT_SHIFT            (11)  /* Number of event counters available for performance measurement */
#define R_NPU_PMCR_NUM_EVENT_CNT_MASK             0xf800

/* PMCNTENSET Register bit definitions */
#define R_NPU_PMCNTENSET_CYCLE_CNT                (1 << 31)  /* PMCCNTR enable bit */

#define R_NPU_PMCNTENSET_EVENT_CNT_3              (1 << 3)  /* Event-counter enable bit for PMU_EVCNTR3 */

#define R_NPU_PMCNTENSET_EVENT_CNT_2              (1 << 2)  /* Event-counter enable bit for PMU_EVCNTR2 */

#define R_NPU_PMCNTENSET_EVENT_CNT_1              (1 << 1)  /* Event-counter enable bit for PMU_EVCNTR1 */

#define R_NPU_PMCNTENSET_EVENT_CNT_0              (1 << 0)  /* Event-counter enable bit for PMU_EVCNTR0 */

/* PMCNTENCLR Register bit definitions */
#define R_NPU_PMCNTENCLR_CYCLE_CNT                (1 << 31)  /* PMCCNTR disable bit */

#define R_NPU_PMCNTENCLR_EVENT_CNT_3              (1 << 3)  /* Event-counter disable bit for PMU_EVCNTR3 */

#define R_NPU_PMCNTENCLR_EVENT_CNT_2              (1 << 2)  /* Event-counter disable bit for PMU_EVCNTR2 */

#define R_NPU_PMCNTENCLR_EVENT_CNT_1              (1 << 1)  /* Event-counter disable bit for PMU_EVCNTR1 */

#define R_NPU_PMCNTENCLR_EVENT_CNT_0              (1 << 0)  /* Event-counter disable bit for PMU_EVCNTR0 */

/* PMOVSSET Register bit definitions */
#define R_NPU_PMOVSSET_CYCLE_CNT_OVF              (1 << 31)  /* PMCCNTR overflow set bit */

#define R_NPU_PMOVSSET_EVENT_CNT_3_OVF            (1 << 3)  /* Event-counter overflow set bit for PMU_EVCNTR3 */

#define R_NPU_PMOVSSET_EVENT_CNT_2_OVF            (1 << 2)  /* Event-counter overflow set bit for PMU_EVCNTR2 */

#define R_NPU_PMOVSSET_EVENT_CNT_1_OVF            (1 << 1)  /* Event-counter overflow set bit for PMU_EVCNTR1 */

#define R_NPU_PMOVSSET_EVENT_CNT_0_OVF            (1 << 0)  /* Event-counter overflow set bit for PMU_EVCNTR0 */

/* PMOVSCLR Register bit definitions */
#define R_NPU_PMOVSCLR_CYCLE_CNT_OVF              (1 << 31)  /* PMCCNTR overflow clear bit */

#define R_NPU_PMOVSCLR_EVENT_CNT_3_OVF            (1 << 3)  /* Event-counter overflow clear bit for PMU_EVCNTR3 */

#define R_NPU_PMOVSCLR_EVENT_CNT_2_OVF            (1 << 2)  /* Event-counter overflow clear bit for PMU_EVCNTR2 */

#define R_NPU_PMOVSCLR_EVENT_CNT_1_OVF            (1 << 1)  /* Event-counter overflow clear bit for PMU_EVCNTR1 */

#define R_NPU_PMOVSCLR_EVENT_CNT_0_OVF            (1 << 0)  /* Event-counter overflow clear bit for PMU_EVCNTR0 */

/* PMINTSET Register bit definitions */
#define R_NPU_PMINTSET_CYCLE_CNT_INT              (1 << 31)  /* PMCCNTR overflow interrupt-request enable bit */

#define R_NPU_PMINTSET_EVENT_CNT_3_INT            (1 << 3)  /* Event-counter overflow interrupt-request enable bit for PMU_EVCNTR3 */

#define R_NPU_PMINTSET_EVENT_CNT_2_INT            (1 << 2)  /* Event-counter overflow interrupt-request enable bit for PMU_EVCNTR2 */

#define R_NPU_PMINTSET_EVENT_CNT_1_INT            (1 << 1)  /* Event-counter overflow interrupt-request enable bit for PMU_EVCNTR1 */

#define R_NPU_PMINTSET_EVENT_CNT_0_INT            (1 << 0)  /* Event-counter overflow interrupt-request enable bit for PMU_EVCNTR0 */

/* PMINTCLR Register bit definitions */
#define R_NPU_PMINTCLR_CYCLE_CNT_INT              (1 << 31)  /* PMCCNTR overflow interrupt-request disable bit */

#define R_NPU_PMINTCLR_EVENT_CNT_3_INT            (1 << 3)  /* Event-counter overflow interrupt-request disable bit for PMU_EVCNTR3 */

#define R_NPU_PMINTCLR_EVENT_CNT_2_INT            (1 << 2)  /* Event-counter overflow interrupt-request disable bit for PMU_EVCNTR2 */

#define R_NPU_PMINTCLR_EVENT_CNT_1_INT            (1 << 1)  /* Event-counter overflow interrupt-request disable bit for PMU_EVCNTR1 */

#define R_NPU_PMINTCLR_EVENT_CNT_0_INT            (1 << 0)  /* Event-counter overflow interrupt-request disable bit for PMU_EVCNTR0 */

/* PMCCNTR_LO Register bit definitions */
#define R_NPU_PMCCNTR_LO_CYCLE_CNT_LO_SHIFT       (0)  /* Cycle count low */
#define R_NPU_PMCCNTR_LO_CYCLE_CNT_LO_MASK        0xffffffff

/* PMCCNTR_HI Register bit definitions */
#define R_NPU_PMCCNTR_HI_CYCLE_CNT_HI_SHIFT       (0)  /* Cycle count high */
#define R_NPU_PMCCNTR_HI_CYCLE_CNT_HI_MASK        0xffffffff

/* PMCAXI_CHAN Register bit definitions */
#define R_NPU_PMCAXI_CHAN_BW_CH_SEL_EN            (1 << 10)  /* Enable bandwidth channel selector: 0=AXI bw events measured for all channels, 1=AXI bw events measured for channel specified by CH_SEL */

#define R_NPU_PMCAXI_CHAN_AXI_CNT_SEL_SHIFT       (8)  /* Select AXI counter to monitor for latency measurements (0=AXI0 counter0, 1=AXI0 counter1, 2=AXI1 counter 2, 3=AXI1 counter3) */
#define R_NPU_PMCAXI_CHAN_AXI_CNT_SEL_MASK        0x300

#define R_NPU_PMCAXI_CHAN_CH_SEL_SHIFT            (0)  /* Specify the type of traffic for bandwidth or latency measurements (Read: 0=command traffic, 1=IFM traffic, 2=Weight traffic, 3=Scale+Bias, 4=Mem2Mem traffic - read direction; Write: 8=OFM traffic, 9=Mem2Mem traffic - write direction) */
#define R_NPU_PMCAXI_CHAN_CH_SEL_MASK             0xf

/* PMU_EVCNTR Register bit definitions */
#define R_NPU_PMU_EVCNTR_PMEVCNTR_SHIFT           (0)  /* Performance-monitor event counters. */
#define R_NPU_PMU_EVCNTR_PMEVCNTR_MASK            0xffffffff

/* PMU_EVTYPER Register bit definitions */
#define R_NPU_PMU_EVTYPER_EV_TYPE_SHIFT           (0)  /* Event type. */
#define R_NPU_PMU_EVTYPER_EV_TYPE_MASK            0xffffffff


/* Maximum number of channels */

#define NPU_MAX_CHANNELS    4

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_NPU_H */
