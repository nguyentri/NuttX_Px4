/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_ipc.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_IPC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_IPC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* IPC Base Address */
#ifndef R_IPC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_IPC_BASE           0x40020000
#else
#define R_IPC_BASE           0x50020000
#endif
#endif

/* IPC Register Offsets */

/* IPCSEM[%s] Registers () */
#define R_IPC_IPCSEM_OFFSET(m)                    (0x00000000 + ((m) * 0x00000004))  /* Semaphore Registers */
/* IPC%sNMI Registers () */
#define R_IPC_IPCNMI_OFFSET(m)                    (0x00000080 + ((m) * 0x00000010))  /* Inter-Processor NMI Registers */
/* IPC%s Registers () */
#define R_IPC_IPC_OFFSET(m)                       (0x000000c0 + ((m) * 0x00000040))  /* Inter-Processor Registers */

/* IPC Register Addresses */

#define R_IPC_IPCSEM(m)                           (R_IPC_BASE + R_IPC_IPCSEM_OFFSET(m))
#define R_IPC_IPCNMI(m)                           (R_IPC_BASE + R_IPC_IPCNMI_OFFSET(m))
#define R_IPC_IPC(m)                              (R_IPC_BASE + R_IPC_IPC_OFFSET(m))

/* Register bit definitions */
/* IPCSEM Register bit definitions */
#define R_IPC_IPCSEM_LOCK                         (1 << 0)  /* Indicates the shared resource is locked */


/* Maximum number of channels */

#define IPC_MAX_CHANNELS    16

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_IPC_H */
