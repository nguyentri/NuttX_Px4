/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_pfs.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_PFS_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_PFS_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* PFS Base Address */
#ifndef R_PFS_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_PFS_BASE           0x40400800
#else
#define R_PFS_BASE           0x50400800
#endif
#endif

/* PFS Register Array Strides */
#define R_PFS_PSEL_PORT_OFFSET          0x40
#define R_PFS_PSEL_PIN_OFFSET           0x04

/* PFS Register Offsets */

/* PFS Register Offsets - Use R_PFS_OFFSET(port, pin) macro */
#define R_PFS_OFFSET(port, pin)    ((port) * 0x40 + (pin) * 0x04)
#define R_PFS_HA_OFFSET(port, pin) ((port) * 0x40 + (pin) * 0x04)
#define R_PFS_BY_OFFSET(port, pin) ((port) * 0x40 + (pin) * 0x04)

/* Ethernet Control Register */
#define R_PFS_PFENET_OFFSET             0x00000500

/* Write-Protect Register for Secure */
#define R_PFS_PWPR_S_OFFSET             0x00000514

/* Port Security Attribution register offset */
#define R_PFS_P0SAR_OFFSET              0x00000530
/* P00%sPFS Registers (0-9) */
#define R_PFS_P00PFS_OFFSET(m)                    (0x00000000 + ((m) * 0x00000004))  /* Port 00%s Pin Function Select Register */
/* P00%sPFS_HA Registers (0-9) */
#define R_PFS_P00PFS_HA_OFFSET(m)                 (0x00000000 + ((m) * 0x00000004))  /* Port 00%s Pin Function Select Register */
/* P00%sPFS_BY Registers (0-9) */
#define R_PFS_P00PFS_BY_OFFSET(m)                 (0x00000000 + ((m) * 0x00000004))  /* Port 00%s Pin Function Select Register */
/* P0%sPFS Registers (10-15) */
#define R_PFS_P0PFS_OFFSET(m)                     (0x00000028 + ((m) * 0x00000004))  /* Port 0%s Pin Function Select Register */
/* P0%sPFS_HA Registers (10-15) */
#define R_PFS_P0PFS_HA_OFFSET(m)                  (0x00000028 + ((m) * 0x00000004))  /* Port 0%s Pin Function Select Register */
/* P0%sPFS_BY Registers (10-15) */
#define R_PFS_P0PFS_BY_OFFSET(m)                  (0x00000028 + ((m) * 0x00000004))  /* Port 0%s Pin Function Select Register */
/* P10%sPFS Registers (0-9) */
#define R_PFS_P10PFS_OFFSET(m)                    (0x00000040 + ((m) * 0x00000004))  /* Port 10%s Pin Function Select Register */
/* P10%sPFS_HA Registers (0-9) */
#define R_PFS_P10PFS_HA_OFFSET(m)                 (0x00000040 + ((m) * 0x00000004))  /* Port 10%s Pin Function Select Register */
/* P10%sPFS_BY Registers (0-9) */
#define R_PFS_P10PFS_BY_OFFSET(m)                 (0x00000040 + ((m) * 0x00000004))  /* Port 10%s Pin Function Select Register */
/* P1%sPFS Registers (10-15) */
#define R_PFS_P1PFS_OFFSET(m)                     (0x00000068 + ((m) * 0x00000004))  /* Port 1%s Pin Function Select Register */
/* P1%sPFS_HA Registers (10-15) */
#define R_PFS_P1PFS_HA_OFFSET(m)                  (0x00000068 + ((m) * 0x00000004))  /* Port 1%s Pin Function Select Register */
/* P1%sPFS_BY Registers (10-15) */
#define R_PFS_P1PFS_BY_OFFSET(m)                  (0x00000068 + ((m) * 0x00000004))  /* Port 1%s Pin Function Select Register */
#define R_PFS_P200PFS_OFFSET                      0x00000080  /* Port 200 Pin Function Select Register */
#define R_PFS_P200PFS_HA_OFFSET                   0x00000080  /* Port 200 Pin Function Select Register */
#define R_PFS_P200PFS_BY_OFFSET                   0x00000080  /* Port 200 Pin Function Select Register */
#define R_PFS_P201PFS_OFFSET                      0x00000084  /* Port 201 Pin Function Select Register */
#define R_PFS_P201PFS_HA_OFFSET                   0x00000084  /* Port 201 Pin Function Select Register */
#define R_PFS_P201PFS_BY_OFFSET                   0x00000084  /* Port 201 Pin Function Select Register */
/* P20%sPFS Registers (2-7) */
#define R_PFS_P20PFS_OFFSET(m)                    (0x00000088 + ((m) * 0x00000004))  /* Port 20%s Pin Function Select Register */
/* P20%sPFS_HA Registers (2-7) */
#define R_PFS_P20PFS_HA_OFFSET(m)                 (0x00000088 + ((m) * 0x00000004))  /* Port 20%s Pin Function Select Register */
/* P20%sPFS_BY Registers (2-7) */
#define R_PFS_P20PFS_BY_OFFSET(m)                 (0x00000088 + ((m) * 0x00000004))  /* Port 20%s Pin Function Select Register */
#define R_PFS_P208PFS_OFFSET                      0x000000a0  /* Port 208 Pin Function Select Register */
#define R_PFS_P208PFS_HA_OFFSET                   0x000000a0  /* Port 208 Pin Function Select Register */
#define R_PFS_P208PFS_BY_OFFSET                   0x000000a0  /* Port 208 Pin Function Select Register */
#define R_PFS_P209PFS_OFFSET                      0x000000a4  /* Port 209 Pin Function Select Register */
#define R_PFS_P209PFS_HA_OFFSET                   0x000000a4  /* Port 209 Pin Function Select Register */
#define R_PFS_P209PFS_BY_OFFSET                   0x000000a4  /* Port 209 Pin Function Select Register */
#define R_PFS_P210PFS_OFFSET                      0x000000a8  /* Port 210 Pin Function Select Register */
#define R_PFS_P210PFS_HA_OFFSET                   0x000000a8  /* Port 210 Pin Function Select Register */
#define R_PFS_P210PFS_BY_OFFSET                   0x000000a8  /* Port 210 Pin Function Select Register */
#define R_PFS_P211PFS_OFFSET                      0x000000ac  /* Port 211 Pin Function Select Register */
#define R_PFS_P211PFS_HA_OFFSET                   0x000000ac  /* Port 211 Pin Function Select Register */
#define R_PFS_P211PFS_BY_OFFSET                   0x000000ac  /* Port 211 Pin Function Select Register */
/* P2%sPFS Registers (12-15) */
#define R_PFS_P2PFS_OFFSET(m)                     (0x000000b0 + ((m) * 0x00000004))  /* Port 2%s Pin Function Select Register */
/* P2%sPFS_HA Registers (12-15) */
#define R_PFS_P2PFS_HA_OFFSET(m)                  (0x000000b0 + ((m) * 0x00000004))  /* Port 2%s Pin Function Select Register */
/* P2%sPFS_BY Registers (12-15) */
#define R_PFS_P2PFS_BY_OFFSET(m)                  (0x000000b0 + ((m) * 0x00000004))  /* Port 2%s Pin Function Select Register */
/* P30%sPFS Registers (0-9) */
#define R_PFS_P30PFS_OFFSET(m)                    (0x000000c0 + ((m) * 0x00000004))  /* Port 30%s Pin Function Select Register */
/* P30%sPFS_HA Registers (0-9) */
#define R_PFS_P30PFS_HA_OFFSET(m)                 (0x000000c0 + ((m) * 0x00000004))  /* Port 30%s Pin Function Select Register */
/* P30%sPFS_BY Registers (0-9) */
#define R_PFS_P30PFS_BY_OFFSET(m)                 (0x000000c0 + ((m) * 0x00000004))  /* Port 30%s Pin Function Select Register */
/* P3%sPFS Registers (10-15) */
#define R_PFS_P3PFS_OFFSET(m)                     (0x000000e8 + ((m) * 0x00000004))  /* Port 3%s Pin Function Select Register */
/* P3%sPFS_HA Registers (10-15) */
#define R_PFS_P3PFS_HA_OFFSET(m)                  (0x000000e8 + ((m) * 0x00000004))  /* Port 3%s Pin Function Select Register */
/* P3%sPFS_BY Registers (10-15) */
#define R_PFS_P3PFS_BY_OFFSET(m)                  (0x000000e8 + ((m) * 0x00000004))  /* Port 3%s Pin Function Select Register */
/* P40%sPFS Registers (0-9) */
#define R_PFS_P40PFS_OFFSET(m)                    (0x00000100 + ((m) * 0x00000004))  /* Port 40%s Pin Function Select Register */
/* P40%sPFS_HA Registers (0-9) */
#define R_PFS_P40PFS_HA_OFFSET(m)                 (0x00000100 + ((m) * 0x00000004))  /* Port 40%s Pin Function Select Register */
/* P40%sPFS_BY Registers (0-9) */
#define R_PFS_P40PFS_BY_OFFSET(m)                 (0x00000100 + ((m) * 0x00000004))  /* Port 40%s Pin Function Select Register */
/* P4%sPFS Registers (10-15) */
#define R_PFS_P4PFS_OFFSET(m)                     (0x00000128 + ((m) * 0x00000004))  /* Port 4%s Pin Function Select Register */
/* P4%sPFS_HA Registers (10-15) */
#define R_PFS_P4PFS_HA_OFFSET(m)                  (0x00000128 + ((m) * 0x00000004))  /* Port 4%s Pin Function Select Register */
/* P4%sPFS_BY Registers (10-15) */
#define R_PFS_P4PFS_BY_OFFSET(m)                  (0x00000128 + ((m) * 0x00000004))  /* Port 4%s Pin Function Select Register */
/* P50%sPFS Registers (0-9) */
#define R_PFS_P50PFS_OFFSET(m)                    (0x00000140 + ((m) * 0x00000004))  /* Port 50%s Pin Function Select Register */
/* P50%sPFS_HA Registers (0-9) */
#define R_PFS_P50PFS_HA_OFFSET(m)                 (0x00000140 + ((m) * 0x00000004))  /* Port 50%s Pin Function Select Register */
/* P50%sPFS_BY Registers (0-9) */
#define R_PFS_P50PFS_BY_OFFSET(m)                 (0x00000140 + ((m) * 0x00000004))  /* Port 50%s Pin Function Select Register */
/* P5%sPFS Registers (10-15) */
#define R_PFS_P5PFS_OFFSET(m)                     (0x00000168 + ((m) * 0x00000004))  /* Port 5%s Pin Function Select Register */
/* P5%sPFS_HA Registers (10-15) */
#define R_PFS_P5PFS_HA_OFFSET(m)                  (0x00000168 + ((m) * 0x00000004))  /* Port 5%s Pin Function Select Register */
/* P5%sPFS_BY Registers (10-15) */
#define R_PFS_P5PFS_BY_OFFSET(m)                  (0x00000168 + ((m) * 0x00000004))  /* Port 5%s Pin Function Select Register */
/* P60%sPFS Registers (0-9) */
#define R_PFS_P60PFS_OFFSET(m)                    (0x00000180 + ((m) * 0x00000004))  /* Port 60%s Pin Function Select Register */
/* P60%sPFS_HA Registers (0-9) */
#define R_PFS_P60PFS_HA_OFFSET(m)                 (0x00000180 + ((m) * 0x00000004))  /* Port 60%s Pin Function Select Register */
/* P60%sPFS_BY Registers (0-9) */
#define R_PFS_P60PFS_BY_OFFSET(m)                 (0x00000180 + ((m) * 0x00000004))  /* Port 60%s Pin Function Select Register */
/* P6%sPFS Registers (10-15) */
#define R_PFS_P6PFS_OFFSET(m)                     (0x000001a8 + ((m) * 0x00000004))  /* Port 6%s Pin Function Select Register */
/* P6%sPFS_HA Registers (10-15) */
#define R_PFS_P6PFS_HA_OFFSET(m)                  (0x000001a8 + ((m) * 0x00000004))  /* Port 6%s Pin Function Select Register */
/* P6%sPFS_BY Registers (10-15) */
#define R_PFS_P6PFS_BY_OFFSET(m)                  (0x000001a8 + ((m) * 0x00000004))  /* Port 6%s Pin Function Select Register */
/* P70%sPFS Registers (0-9) */
#define R_PFS_P70PFS_OFFSET(m)                    (0x000001c0 + ((m) * 0x00000004))  /* Port 70%s Pin Function Select Register */
/* P70%sPFS_HA Registers (0-9) */
#define R_PFS_P70PFS_HA_OFFSET(m)                 (0x000001c0 + ((m) * 0x00000004))  /* Port 70%s Pin Function Select Register */
/* P70%sPFS_BY Registers (0-9) */
#define R_PFS_P70PFS_BY_OFFSET(m)                 (0x000001c0 + ((m) * 0x00000004))  /* Port 70%s Pin Function Select Register */
/* P7%sPFS Registers (10-15) */
#define R_PFS_P7PFS_OFFSET(m)                     (0x000001e8 + ((m) * 0x00000004))  /* Port 7%s Pin Function Select Register */
/* P7%sPFS_HA Registers (10-15) */
#define R_PFS_P7PFS_HA_OFFSET(m)                  (0x000001e8 + ((m) * 0x00000004))  /* Port 7%s Pin Function Select Register */
/* P7%sPFS_BY Registers (10-15) */
#define R_PFS_P7PFS_BY_OFFSET(m)                  (0x000001e8 + ((m) * 0x00000004))  /* Port 7%s Pin Function Select Register */
/* P80%sPFS Registers (0-9) */
#define R_PFS_P80PFS_OFFSET(m)                    (0x00000200 + ((m) * 0x00000004))  /* Port 80%s Pin Function Select Register */
/* P80%sPFS_HA Registers (0-9) */
#define R_PFS_P80PFS_HA_OFFSET(m)                 (0x00000200 + ((m) * 0x00000004))  /* Port 80%s Pin Function Select Register */
/* P80%sPFS_BY Registers (0-9) */
#define R_PFS_P80PFS_BY_OFFSET(m)                 (0x00000200 + ((m) * 0x00000004))  /* Port 80%s Pin Function Select Register */
/* P8%sPFS Registers (10-13) */
#define R_PFS_P8PFS_OFFSET(m)                     (0x00000228 + ((m) * 0x00000004))  /* Port 8%s Pin Function Select Register */
/* P8%sPFS_HA Registers (10-13) */
#define R_PFS_P8PFS_HA_OFFSET(m)                  (0x00000228 + ((m) * 0x00000004))  /* Port 8%s Pin Function Select Register */
/* P8%sPFS_BY Registers (10-13) */
#define R_PFS_P8PFS_BY_OFFSET(m)                  (0x00000228 + ((m) * 0x00000004))  /* Port 8%s Pin Function Select Register */
#define R_PFS_P814PFS_OFFSET                      0x00000238  /* Port 814 Pin Function Select Register */
#define R_PFS_P814PFS_HA_OFFSET                   0x00000238  /* Port 814 Pin Function Select Register */
#define R_PFS_P814PFS_BY_OFFSET                   0x00000238  /* Port 814 Pin Function Select Register */
#define R_PFS_P815PFS_OFFSET                      0x0000023c  /* Port 815 Pin Function Select Register */
#define R_PFS_P815PFS_HA_OFFSET                   0x0000023c  /* Port 815 Pin Function Select Register */
#define R_PFS_P815PFS_BY_OFFSET                   0x0000023c  /* Port 815 Pin Function Select Register */
/* P90%sPFS Registers (0-9) */
#define R_PFS_P90PFS_OFFSET(m)                    (0x00000240 + ((m) * 0x00000004))  /* Port 90%s Pin Function Select Register */
/* P90%sPFS_HA Registers (0-9) */
#define R_PFS_P90PFS_HA_OFFSET(m)                 (0x00000240 + ((m) * 0x00000004))  /* Port 90%s Pin Function Select Register */
/* P90%sPFS_BY Registers (0-9) */
#define R_PFS_P90PFS_BY_OFFSET(m)                 (0x00000240 + ((m) * 0x00000004))  /* Port 90%s Pin Function Select Register */
/* P9%sPFS Registers (10-15) */
#define R_PFS_P9PFS_OFFSET(m)                     (0x00000268 + ((m) * 0x00000004))  /* Port 9%s Pin Function Select Register */
/* P9%sPFS_HA Registers (10-15) */
#define R_PFS_P9PFS_HA_OFFSET(m)                  (0x00000268 + ((m) * 0x00000004))  /* Port 9%s Pin Function Select Register */
/* P9%sPFS_BY Registers (10-15) */
#define R_PFS_P9PFS_BY_OFFSET(m)                  (0x00000268 + ((m) * 0x00000004))  /* Port 9%s Pin Function Select Register */
/* PA0%sPFS Registers (0-9) */
#define R_PFS_PA0PFS_OFFSET(m)                    (0x00000280 + ((m) * 0x00000004))  /* Port A0%s Pin Function Select Register */
/* PA0%sPFS_HA Registers (0-9) */
#define R_PFS_PA0PFS_HA_OFFSET(m)                 (0x00000280 + ((m) * 0x00000004))  /* Port A0%s Pin Function Select Register */
/* PA0%sPFS_BY Registers (0-9) */
#define R_PFS_PA0PFS_BY_OFFSET(m)                 (0x00000280 + ((m) * 0x00000004))  /* Port A0%s Pin Function Select Register */
/* PA%sPFS Registers (10-15) */
#define R_PFS_PAPFS_OFFSET(m)                     (0x000002a8 + ((m) * 0x00000004))  /* Port An Pin Function Select Register */
/* PA%sPFS_HA Registers (10-15) */
#define R_PFS_PAPFS_HA_OFFSET(m)                  (0x000002a8 + ((m) * 0x00000004))  /* Port An Pin Function Select Register */
/* PA%sPFS_BY Registers (10-15) */
#define R_PFS_PAPFS_BY_OFFSET(m)                  (0x000002a8 + ((m) * 0x00000004))  /* Port An Pin Function Select Register */
/* PB0%sPFS Registers (0-7) */
#define R_PFS_PB0PFS_OFFSET(m)                    (0x000002c0 + ((m) * 0x00000004))  /* Port B0%s Pin Function Select Register */
/* PB0%sPFS_HA Registers (0-7) */
#define R_PFS_PB0PFS_HA_OFFSET(m)                 (0x000002c0 + ((m) * 0x00000004))  /* Port B0%s Pin Function Select Register */
/* PB0%sPFS_BY Registers (0-7) */
#define R_PFS_PB0PFS_BY_OFFSET(m)                 (0x000002c0 + ((m) * 0x00000004))  /* Port B0%s Pin Function Select Register */
/* PC0%sPFS Registers (0-9) */
#define R_PFS_PC0PFS_OFFSET(m)                    (0x00000300 + ((m) * 0x00000004))  /* Port C0%s Pin Function Select Register */
/* PC0%sPFS_HA Registers (0-9) */
#define R_PFS_PC0PFS_HA_OFFSET(m)                 (0x00000300 + ((m) * 0x00000004))  /* Port C0%s Pin Function Select Register */
/* PC0%sPFS_BY Registers (0-9) */
#define R_PFS_PC0PFS_BY_OFFSET(m)                 (0x00000300 + ((m) * 0x00000004))  /* Port C0%s Pin Function Select Register */
/* PC%sPFS Registers (10-15) */
#define R_PFS_PCPFS_OFFSET(m)                     (0x00000328 + ((m) * 0x00000004))  /* Port Cn Pin Function Select Register */
/* PC%sPFS_HA Registers (10-15) */
#define R_PFS_PCPFS_HA_OFFSET(m)                  (0x00000328 + ((m) * 0x00000004))  /* Port Cn Pin Function Select Register */
/* PC%sPFS_BY Registers (10-15) */
#define R_PFS_PCPFS_BY_OFFSET(m)                  (0x00000328 + ((m) * 0x00000004))  /* Port Cn Pin Function Select Register */
/* PD0%sPFS Registers (0-7) */
#define R_PFS_PD0PFS_OFFSET(m)                    (0x00000340 + ((m) * 0x00000004))  /* Port D0%s Pin Function Select Register */
/* PD0%sPFS_HA Registers (0-7) */
#define R_PFS_PD0PFS_HA_OFFSET(m)                 (0x00000340 + ((m) * 0x00000004))  /* Port D0%s Pin Function Select Register */
/* PD0%sPFS_BY Registers (0-7) */
#define R_PFS_PD0PFS_BY_OFFSET(m)                 (0x00000340 + ((m) * 0x00000004))  /* Port D0%s Pin Function Select Register */
#define R_PFS_PFENET_OFFSET                       0x00000500  /* Ethernet Control Register */
#define R_PFS_PWPR_S_OFFSET                       0x00000514  /* Write-Protect Register for Secure */
/* P%sSAR Registers (0-9) */
#define R_PFS_PSAR_OFFSET(m)                      (0x00000530 + ((m) * 0x00000004))  /* Port Security Attribution Register */
/* P%sSAR Registers (A-B) */
#define R_PFS_PXSAR_OFFSET(m)                     (0x00000558 + ((m) * 0x00000004))  /* Port Security Attribution Register */

/* PFS Register Addresses */

/* PFS Register Parameterized Macros */

/* PmnPFS - Pin Function Select Register */
#define R_PFS(port,pin)                 (R_PFS_BASE + (port)*R_PFS_PSEL_PORT_OFFSET + (pin)*R_PFS_PSEL_PIN_OFFSET)

/* Alternate register formats */
#define R_PFS_HA(port,pin)              (R_PFS_BASE + (port)*R_PFS_PSEL_PORT_OFFSET + (pin)*R_PFS_PSEL_PIN_OFFSET)
#define R_PFS_BY(port,pin)              (R_PFS_BASE + (port)*R_PFS_PSEL_PORT_OFFSET + (pin)*R_PFS_PSEL_PIN_OFFSET)

/* Other PFS registers */
#define R_PFS_PFENET                    (R_PFS_BASE + R_PFS_PFENET_OFFSET)
#define R_PFS_PWPR                      (R_PFS_BASE + R_PFS_PWPR_S_OFFSET)

/* Port Security Attribution Registers */
#define R_PFS_PMSAR(port)               (R_PFS_BASE + R_PFS_P0SAR_OFFSET + (port)*0x04)

/* Register bit definitions */
/* PFS Common Bit Definitions (applicable to all PmnPFS registers) */

#define R_PFS_PODR                      (1 << 0)  /* Port Output Data */

#define R_PFS_PIDR                      (1 << 1)  /* Pmn State */

#define R_PFS_PDR                       (1 << 2)  /* Port Direction */

#define R_PFS_PCR                       (1 << 4)  /* Pull-up Control */

#define R_PFS_NCODR                     (1 << 6)  /* N-Channel Open-Drain Control */

#define R_PFS_DSCR_SHIFT                (10)  /* Port Drive Capability */
#define R_PFS_DSCR_MASK                 0xc00
#  define R_PFS_DSCR_00                         (0 << R_PFS_DSCR_SHIFT)  /* Low drive */
#  define R_PFS_DSCR_01                         (1 << R_PFS_DSCR_SHIFT)  /* Middle drive */
#  define R_PFS_DSCR_10                         (2 << R_PFS_DSCR_SHIFT)  /* High-speed high-drive */
#  define R_PFS_DSCR_11                         (3 << R_PFS_DSCR_SHIFT)  /* High drive */

#define R_PFS_EOFR_SHIFT                (12)  /* Event on Falling/Event on Rising */
#define R_PFS_EOFR_MASK                 0x3000
#  define R_PFS_EOFR_00                         (0 << R_PFS_EOFR_SHIFT)  /* Don't care */
#  define R_PFS_EOFR_01                         (1 << R_PFS_EOFR_SHIFT)  /* Detect rising edge */
#  define R_PFS_EOFR_10                         (2 << R_PFS_EOFR_SHIFT)  /* Detect falling edge */
#  define R_PFS_EOFR_11                         (3 << R_PFS_EOFR_SHIFT)  /* Detect both edges */

#define R_PFS_ISEL                      (1 << 14)  /* IRQ Input Enable */

#define R_PFS_ASEL                      (1 << 15)  /* Analog Input Enable */

#define R_PFS_PMR                       (1 << 16)  /* Port Mode Control */

#define R_PFS_PSEL_SHIFT                (24)  /* Peripheral Select */
#define R_PFS_PSEL_MASK                 0x1f000000

/* PWPR - Write-Protect Register */

#define R_PWPR_PFSWE                    (6)  /* PmnPFS Register Write Enable */
#define R_PWPR_B0WI                     (7)  /* PFSWE Bit Write Disable */


/* Maximum number of channels */

#define PFS_MAX_CHANNELS    12

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_PFS_H */
