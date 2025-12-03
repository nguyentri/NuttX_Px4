/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_canfd.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CANFD_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CANFD_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* CANFD Base Address */
#ifndef R_CANFD_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_CANFD_BASE           0x40380000
#else
#define R_CANFD_BASE           0x50380000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_CANFD_CH_STRIDE    0x00002000
#define R_CANFD_CH_BASE(ch)   (R_CANFD_BASE + ((uint32_t)(ch) * R_CANFD_CH_STRIDE))

/* CANFD Register Offsets */

#define R_CANFD_CFDC_OFFSET                       0x00000000  /* Channel Control/Status */
#define R_CANFD_CFDGCFG_OFFSET                    0x00000014  /* Global Configuration Register */
#define R_CANFD_CFDGCTR_OFFSET                    0x00000018  /* Global Control Register */
#define R_CANFD_CFDGSTS_OFFSET                    0x0000001c  /* Global Status Register */
#define R_CANFD_CFDGERFL_OFFSET                   0x00000020  /* Global Error Flag Register */
#define R_CANFD_CFDGTSC_OFFSET                    0x00000024  /* Global Timestamp Counter Register */
#define R_CANFD_CFDGAFLECTR_OFFSET                0x00000028  /* Global Acceptance Filter List Entry Control Register */
#define R_CANFD_CFDGAFLCFG0_OFFSET                0x0000002c  /* Global Acceptance Filter List Configuration Register 0 */
#define R_CANFD_CFDRMNB_OFFSET                    0x00000030  /* RX Message Buffer Number Register */
#define R_CANFD_CFDRMND0_OFFSET                   0x00000034  /* RX Message Buffer New Data Register 0 */
#define R_CANFD_CFDRMIEC_OFFSET                   0x00000038  /* RX Message Buffer Interrupt Enable Configuration Register */
/* CFDRFCC[%s] Registers () */
#define R_CANFD_CFDRFCC_OFFSET(m)                 (0x0000003c + ((m) * 0x00000004))  /* RX FIFO Configuration / Control Registers */
/* CFDRFSTS[%s] Registers () */
#define R_CANFD_CFDRFSTS_OFFSET(m)                (0x00000044 + ((m) * 0x00000004))  /* RX FIFO Status Registers */
/* CFDRFPCTR[%s] Registers () */
#define R_CANFD_CFDRFPCTR_OFFSET(m)               (0x0000004c + ((m) * 0x00000004))  /* RX FIFO Pointer Control Registers */
#define R_CANFD_CFDCFCC_OFFSET                    0x00000054  /* Common FIFO Configuration / Control Registers */
#define R_CANFD_CFDCFSTS_OFFSET                   0x00000058  /* Common FIFO Status Registers */
#define R_CANFD_CFDCFPCTR_OFFSET                  0x0000005c  /* Common FIFO Pointer Control Registers */
#define R_CANFD_CFDFESTS_OFFSET                   0x00000060  /* FIFO Empty Status Register */
#define R_CANFD_CFDFFSTS_OFFSET                   0x00000064  /* FIFO Full Status Register */
#define R_CANFD_CFDFMSTS_OFFSET                   0x00000068  /* FIFO Message Lost Status Register */
#define R_CANFD_CFDRFISTS_OFFSET                  0x0000006c  /* RX FIFO Interrupt Flag Status Register */
/* CFDTMC[%s] Registers () */
#define R_CANFD_CFDTMC_OFFSET(m)                  (0x00000070 + ((m) * 0x00000001))  /* TX Message Buffer Control Registers */
/* CFDTMSTS[%s] Registers () */
#define R_CANFD_CFDTMSTS_OFFSET(m)                (0x00000074 + ((m) * 0x00000001))  /* TX Message Buffer Status Registers */
#define R_CANFD_CFDTMTRSTS_OFFSET                 0x00000078  /* TX Message Buffer Transmission Request Status Register */
#define R_CANFD_CFDTMTARSTS_OFFSET                0x0000007c  /* TX Message Buffer Transmission Abort Request Status Register */
#define R_CANFD_CFDTMTCSTS_OFFSET                 0x00000080  /* TX Message Buffer Transmission Completion Status Register */
#define R_CANFD_CFDTMTASTS_OFFSET                 0x00000084  /* TX Message Buffer Transmission Abort Status Register */
#define R_CANFD_CFDTMIEC_OFFSET                   0x00000088  /* TX Message Buffer Interrupt Enable Configuration Register */
#define R_CANFD_CFDTXQCC0_OFFSET                  0x0000008c  /* TX Queue Configuration / Control Registers 0 */
#define R_CANFD_CFDTXQSTS0_OFFSET                 0x00000090  /* TX Queue Status Registers 0 */
#define R_CANFD_CFDTXQPCTR0_OFFSET                0x00000094  /* TX Queue Pointer Control Registers 0 */
#define R_CANFD_CFDTHLCC_OFFSET                   0x00000098  /* TX History List Configuration / Control Register */
#define R_CANFD_CFDTHLSTS_OFFSET                  0x0000009c  /* TX History List Status Register */
#define R_CANFD_CFDTHLPCTR_OFFSET                 0x000000a0  /* TX History List Pointer Control Registers */
#define R_CANFD_CFDGTINTSTS0_OFFSET               0x000000a4  /* Global TX Interrupt Status Register 0 */
#define R_CANFD_CFDGTSTCFG_OFFSET                 0x000000a8  /* Global Test Configuration Register */
#define R_CANFD_CFDGTSTCTR_OFFSET                 0x000000ac  /* Global Test Control Register */
#define R_CANFD_CFDGFDCFG_OFFSET                  0x000000b0  /* Global FD Configuration register */
#define R_CANFD_CFDGLOCKK_OFFSET                  0x000000b8  /* Global Lock Key Register */
#define R_CANFD_CFDGAFLIGNENT_OFFSET              0x000000c0  /* Global AFL Ignore Entry Register */
#define R_CANFD_CFDGAFLIGNCTR_OFFSET              0x000000c4  /* Global AFL Ignore Control Register */
#define R_CANFD_CFDCDTCT_OFFSET                   0x000000c8  /* DMA Transfer Control Register */
#define R_CANFD_CFDCDTSTS_OFFSET                  0x000000cc  /* DMA Transfer Status Register */
#define R_CANFD_CFDGRSTC_OFFSET                   0x000000d8  /* Global SW reset Register */
#define R_CANFD_CFDC2_OFFSET                      0x00000100  /* Channel Configuration Registers */
/* CFDGAFL[%s] Registers () */
#define R_CANFD_CFDGAFL_OFFSET(m)                 (0x00000120 + ((m) * 0x00000010))  /* Global Acceptance Filter List Registers */
/* CFDRPGACC[%s] Registers () */
#define R_CANFD_CFDRPGACC_OFFSET(m)               (0x00000280 + ((m) * 0x00000004))  /* RAM Test Page Access Registers */
/* CFDRF[%s] Registers () */
#define R_CANFD_CFDRF_OFFSET(m)                   (0x00000520 + ((m) * 0x0000004c))  /* RX FIFO Access Registers */
#define R_CANFD_CFDCF_OFFSET                      0x000005b8  /* Common FIFO Access Registers */
/* CFDTM[%s] Registers () */
#define R_CANFD_CFDTM_OFFSET(m)                   (0x00000604 + ((m) * 0x0000004c))  /* TX Message Buffer Access Registers */
#define R_CANFD_CFDTHL_OFFSET                     0x00000740  /* Channel TX History List */
/* CFDRM[%s] Registers () */
#define R_CANFD_CFDRM_OFFSET(m)                   (0x00000920 + ((m) * 0x00000400))  /* RX Message Buffer Access Clusters */

/* CANFD Register Addresses */

#define R_CANFD_CFDC(n)                           (R_CANFD_CH_BASE(n) + R_CANFD_CFDC_OFFSET)
#define R_CANFD_CFDGCFG(n)                        (R_CANFD_CH_BASE(n) + R_CANFD_CFDGCFG_OFFSET)
#define R_CANFD_CFDGCTR(n)                        (R_CANFD_CH_BASE(n) + R_CANFD_CFDGCTR_OFFSET)
#define R_CANFD_CFDGSTS(n)                        (R_CANFD_CH_BASE(n) + R_CANFD_CFDGSTS_OFFSET)
#define R_CANFD_CFDGERFL(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDGERFL_OFFSET)
#define R_CANFD_CFDGTSC(n)                        (R_CANFD_CH_BASE(n) + R_CANFD_CFDGTSC_OFFSET)
#define R_CANFD_CFDGAFLECTR(n)                    (R_CANFD_CH_BASE(n) + R_CANFD_CFDGAFLECTR_OFFSET)
#define R_CANFD_CFDGAFLCFG0(n)                    (R_CANFD_CH_BASE(n) + R_CANFD_CFDGAFLCFG0_OFFSET)
#define R_CANFD_CFDRMNB(n)                        (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMNB_OFFSET)
#define R_CANFD_CFDRMND0(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMND0_OFFSET)
#define R_CANFD_CFDRMIEC(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDRMIEC_OFFSET)
#define R_CANFD_CFDRFCC(n, m)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFCC_OFFSET(m))
#define R_CANFD_CFDRFSTS(n, m)                    (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFSTS_OFFSET(m))
#define R_CANFD_CFDRFPCTR(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFPCTR_OFFSET(m))
#define R_CANFD_CFDCFCC(n)                        (R_CANFD_CH_BASE(n) + R_CANFD_CFDCFCC_OFFSET)
#define R_CANFD_CFDCFSTS(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDCFSTS_OFFSET)
#define R_CANFD_CFDCFPCTR(n)                      (R_CANFD_CH_BASE(n) + R_CANFD_CFDCFPCTR_OFFSET)
#define R_CANFD_CFDFESTS(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDFESTS_OFFSET)
#define R_CANFD_CFDFFSTS(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDFFSTS_OFFSET)
#define R_CANFD_CFDFMSTS(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDFMSTS_OFFSET)
#define R_CANFD_CFDRFISTS(n)                      (R_CANFD_CH_BASE(n) + R_CANFD_CFDRFISTS_OFFSET)
#define R_CANFD_CFDTMC(n, m)                      (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMC_OFFSET(m))
#define R_CANFD_CFDTMSTS(n, m)                    (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMSTS_OFFSET(m))
#define R_CANFD_CFDTMTRSTS(n)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMTRSTS_OFFSET)
#define R_CANFD_CFDTMTARSTS(n)                    (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMTARSTS_OFFSET)
#define R_CANFD_CFDTMTCSTS(n)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMTCSTS_OFFSET)
#define R_CANFD_CFDTMTASTS(n)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMTASTS_OFFSET)
#define R_CANFD_CFDTMIEC(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDTMIEC_OFFSET)
#define R_CANFD_CFDTXQCC0(n)                      (R_CANFD_CH_BASE(n) + R_CANFD_CFDTXQCC0_OFFSET)
#define R_CANFD_CFDTXQSTS0(n)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDTXQSTS0_OFFSET)
#define R_CANFD_CFDTXQPCTR0(n)                    (R_CANFD_CH_BASE(n) + R_CANFD_CFDTXQPCTR0_OFFSET)
#define R_CANFD_CFDTHLCC(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDTHLCC_OFFSET)
#define R_CANFD_CFDTHLSTS(n)                      (R_CANFD_CH_BASE(n) + R_CANFD_CFDTHLSTS_OFFSET)
#define R_CANFD_CFDTHLPCTR(n)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDTHLPCTR_OFFSET)
#define R_CANFD_CFDGTINTSTS0(n)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDGTINTSTS0_OFFSET)
#define R_CANFD_CFDGTSTCFG(n)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDGTSTCFG_OFFSET)
#define R_CANFD_CFDGTSTCTR(n)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDGTSTCTR_OFFSET)
#define R_CANFD_CFDGFDCFG(n)                      (R_CANFD_CH_BASE(n) + R_CANFD_CFDGFDCFG_OFFSET)
#define R_CANFD_CFDGLOCKK(n)                      (R_CANFD_CH_BASE(n) + R_CANFD_CFDGLOCKK_OFFSET)
#define R_CANFD_CFDGAFLIGNENT(n)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDGAFLIGNENT_OFFSET)
#define R_CANFD_CFDGAFLIGNCTR(n)                  (R_CANFD_CH_BASE(n) + R_CANFD_CFDGAFLIGNCTR_OFFSET)
#define R_CANFD_CFDCDTCT(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDCDTCT_OFFSET)
#define R_CANFD_CFDCDTSTS(n)                      (R_CANFD_CH_BASE(n) + R_CANFD_CFDCDTSTS_OFFSET)
#define R_CANFD_CFDGRSTC(n)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDGRSTC_OFFSET)
#define R_CANFD_CFDC2(n)                          (R_CANFD_CH_BASE(n) + R_CANFD_CFDC2_OFFSET)
#define R_CANFD_CFDGAFL(n, m)                     (R_CANFD_CH_BASE(n) + R_CANFD_CFDGAFL_OFFSET(m))
#define R_CANFD_CFDRPGACC(n, m)                   (R_CANFD_CH_BASE(n) + R_CANFD_CFDRPGACC_OFFSET(m))
#define R_CANFD_CFDRF(n, m)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDRF_OFFSET(m))
#define R_CANFD_CFDCF(n)                          (R_CANFD_CH_BASE(n) + R_CANFD_CFDCF_OFFSET)
#define R_CANFD_CFDTM(n, m)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDTM_OFFSET(m))
#define R_CANFD_CFDTHL(n)                         (R_CANFD_CH_BASE(n) + R_CANFD_CFDTHL_OFFSET)
#define R_CANFD_CFDRM(n, m)                       (R_CANFD_CH_BASE(n) + R_CANFD_CFDRM_OFFSET(m))

/* Register bit definitions */
/* CFDGCFG Register bit definitions */
#define R_CANFD_CFDGCFG_TPRI                      (1 << 0)  /* Transmission Priority */

#define R_CANFD_CFDGCFG_DCE                       (1 << 1)  /* DLC Check Enable */

#define R_CANFD_CFDGCFG_DRE                       (1 << 2)  /* DLC Replacement Enable */

#define R_CANFD_CFDGCFG_MME                       (1 << 3)  /* Mirror Mode Enable */

#define R_CANFD_CFDGCFG_DCS                       (1 << 4)  /* Data Link Controller Clock Select */

#define R_CANFD_CFDGCFG_CMPOC                     (1 << 5)  /* CAN-FD message Payload overflow configuration */

#define R_CANFD_CFDGCFG_TSP_SHIFT                 (8)  /* Timestamp Prescaler */
#define R_CANFD_CFDGCFG_TSP_MASK                  0xf00

#define R_CANFD_CFDGCFG_TSSS                      (1 << 12)  /* Timestamp Source Select */

#define R_CANFD_CFDGCFG_ITRCP_SHIFT               (16)  /* Interval Timer Reference Clock Prescaler */
#define R_CANFD_CFDGCFG_ITRCP_MASK                0xffff0000

/* CFDGCTR Register bit definitions */
#define R_CANFD_CFDGCTR_GMDC_SHIFT                (0)  /* Global Mode Control */
#define R_CANFD_CFDGCTR_GMDC_MASK                 0x3
#  define R_CANFD_CFDGCTR_GMDC_00                         (0 << R_CANFD_CFDGCTR_GMDC_SHIFT)  /* Global Operation Mode Request */
#  define R_CANFD_CFDGCTR_GMDC_01                         (1 << R_CANFD_CFDGCTR_GMDC_SHIFT)  /* Global Reset Mode Request */
#  define R_CANFD_CFDGCTR_GMDC_10                         (2 << R_CANFD_CFDGCTR_GMDC_SHIFT)  /* Global Halt Mode Request */
#  define R_CANFD_CFDGCTR_GMDC_11                         (3 << R_CANFD_CFDGCTR_GMDC_SHIFT)  /* Keep Current Value */

#define R_CANFD_CFDGCTR_GSLPR                     (1 << 2)  /* Global Sleep Request */

#define R_CANFD_CFDGCTR_DEIE                      (1 << 8)  /* DLC check Interrupt Enable */

#define R_CANFD_CFDGCTR_MEIE                      (1 << 9)  /* Message lost Error Interrupt Enable */

#define R_CANFD_CFDGCTR_THLEIE                    (1 << 10)  /* TX History List Entry Lost Interrupt Enable */

#define R_CANFD_CFDGCTR_CMPOFIE                   (1 << 11)  /* CAN-FD message payload overflow Flag Interrupt enable */

#define R_CANFD_CFDGCTR_TSRST                     (1 << 16)  /* Timestamp Reset */

/* CFDGSTS Register bit definitions */
#define R_CANFD_CFDGSTS_GRSTSTS                   (1 << 0)  /* Global Reset Status */

#define R_CANFD_CFDGSTS_GHLTSTS                   (1 << 1)  /* Global Halt Status */

#define R_CANFD_CFDGSTS_GSLPSTS                   (1 << 2)  /* Global Sleep Status */

#define R_CANFD_CFDGSTS_GRAMINIT                  (1 << 3)  /* Global RAM Initialisation */

/* CFDGERFL Register bit definitions */
#define R_CANFD_CFDGERFL_DEF                      (1 << 0)  /* DLC Error Flag */

#define R_CANFD_CFDGERFL_MES                      (1 << 1)  /* Message Lost Error Status */

#define R_CANFD_CFDGERFL_THLES                    (1 << 2)  /* TX History List Entry Lost Error Status */

#define R_CANFD_CFDGERFL_CMPOF                    (1 << 3)  /* CAN-FD message payload overflow Flag */

#define R_CANFD_CFDGERFL_EEF0                     (1 << 16)  /* ECC Error Flag for Channel 0 */

/* CFDGTSC Register bit definitions */
#define R_CANFD_CFDGTSC_TS_SHIFT                  (0)  /* Timestamp Value */
#define R_CANFD_CFDGTSC_TS_MASK                   0xffff

/* CFDGAFLECTR Register bit definitions */
#define R_CANFD_CFDGAFLECTR_AFLPN_SHIFT           (0)  /* Acceptance Filter List Page Number */
#define R_CANFD_CFDGAFLECTR_AFLPN_MASK            0xf

#define R_CANFD_CFDGAFLECTR_AFLDAE                (1 << 8)  /* Acceptance Filter List Data Access Enable */

/* CFDGAFLCFG0 Register bit definitions */
#define R_CANFD_CFDGAFLCFG0_RNC1_SHIFT            (0)  /* Rule Number for Channel 1 */
#define R_CANFD_CFDGAFLCFG0_RNC1_MASK             0x1ff

#define R_CANFD_CFDGAFLCFG0_RNC0_SHIFT            (16)  /* Rule Number for Channel 0 */
#define R_CANFD_CFDGAFLCFG0_RNC0_MASK             0x1ff0000

/* CFDRMNB Register bit definitions */
#define R_CANFD_CFDRMNB_NRXMB_SHIFT               (0)  /* Number of RX Message Buffers */
#define R_CANFD_CFDRMNB_NRXMB_MASK                0xff

#define R_CANFD_CFDRMNB_RMPLS_SHIFT               (8)  /* Reception Message Buffer Payload Data Size */
#define R_CANFD_CFDRMNB_RMPLS_MASK                0x700
#  define R_CANFD_CFDRMNB_RMPLS_000                       (0 << R_CANFD_CFDRMNB_RMPLS_SHIFT)  /* 8 Bytes */
#  define R_CANFD_CFDRMNB_RMPLS_001                       (1 << R_CANFD_CFDRMNB_RMPLS_SHIFT)  /* 12 Bytes */
#  define R_CANFD_CFDRMNB_RMPLS_010                       (2 << R_CANFD_CFDRMNB_RMPLS_SHIFT)  /* 16 Bytes */
#  define R_CANFD_CFDRMNB_RMPLS_011                       (3 << R_CANFD_CFDRMNB_RMPLS_SHIFT)  /* 20 Bytes */
#  define R_CANFD_CFDRMNB_RMPLS_100                       (4 << R_CANFD_CFDRMNB_RMPLS_SHIFT)  /* 24 Bytes */
#  define R_CANFD_CFDRMNB_RMPLS_101                       (5 << R_CANFD_CFDRMNB_RMPLS_SHIFT)  /* 32 Bytes */
#  define R_CANFD_CFDRMNB_RMPLS_110                       (6 << R_CANFD_CFDRMNB_RMPLS_SHIFT)  /* 48 Bytes */
#  define R_CANFD_CFDRMNB_RMPLS_111                       (7 << R_CANFD_CFDRMNB_RMPLS_SHIFT)  /* 64 Bytes */

/* CFDRMND0 Register bit definitions */
#define R_CANFD_CFDRMND0_RMNSU_SHIFT              (0)  /* RX Message Buffer New Data Status */
#define R_CANFD_CFDRMND0_RMNSU_MASK               0xffffffff
#  define R_CANFD_CFDRMND0_RMNSU_0                        (0 << R_CANFD_CFDRMND0_RMNSU_SHIFT)  /* New Data not stored in corresponding RX Message Buffer */
#  define R_CANFD_CFDRMND0_RMNSU_1                        (1 << R_CANFD_CFDRMND0_RMNSU_SHIFT)  /* New Data stored in corresponding RX Message Buffer */

#define R_CANFD_CFDRMND0_RMNSU_SHIFT              (0)  /* RX Message Buffer New Data Status */
#define R_CANFD_CFDRMND0_RMNSU_MASK               0xffffffff

/* CFDRMIEC Register bit definitions */
#define R_CANFD_CFDRMIEC_RMIE_SHIFT               (0)  /* RX Message Buffer Interrupt Enable */
#define R_CANFD_CFDRMIEC_RMIE_MASK                0xffffffff

/* CFDRFCC Register bit definitions */
#define R_CANFD_CFDRFCC_RFE                       (1 << 0)  /* RX FIFO Enable */

#define R_CANFD_CFDRFCC_RFIE                      (1 << 1)  /* RX FIFO Interrupt Enable */

#define R_CANFD_CFDRFCC_RFPLS_SHIFT               (4)  /* Rx FIFO Payload Data Size configuration */
#define R_CANFD_CFDRFCC_RFPLS_MASK                0x70
#  define R_CANFD_CFDRFCC_RFPLS_000                       (0 << R_CANFD_CFDRFCC_RFPLS_SHIFT)  /* 8 Bytes */
#  define R_CANFD_CFDRFCC_RFPLS_001                       (1 << R_CANFD_CFDRFCC_RFPLS_SHIFT)  /* 12 Bytes */
#  define R_CANFD_CFDRFCC_RFPLS_010                       (2 << R_CANFD_CFDRFCC_RFPLS_SHIFT)  /* 16 Bytes */
#  define R_CANFD_CFDRFCC_RFPLS_011                       (3 << R_CANFD_CFDRFCC_RFPLS_SHIFT)  /* 20 Bytes */
#  define R_CANFD_CFDRFCC_RFPLS_100                       (4 << R_CANFD_CFDRFCC_RFPLS_SHIFT)  /* 24 Bytes */
#  define R_CANFD_CFDRFCC_RFPLS_101                       (5 << R_CANFD_CFDRFCC_RFPLS_SHIFT)  /* 32 Bytes */
#  define R_CANFD_CFDRFCC_RFPLS_110                       (6 << R_CANFD_CFDRFCC_RFPLS_SHIFT)  /* 48 Bytes */
#  define R_CANFD_CFDRFCC_RFPLS_111                       (7 << R_CANFD_CFDRFCC_RFPLS_SHIFT)  /* 64 Bytes */

#define R_CANFD_CFDRFCC_RFDC_SHIFT                (8)  /* RX FIFO Depth Configuration */
#define R_CANFD_CFDRFCC_RFDC_MASK                 0x700
#  define R_CANFD_CFDRFCC_RFDC_000                        (0 << R_CANFD_CFDRFCC_RFDC_SHIFT)  /* FIFO Depth = 0 Messages */
#  define R_CANFD_CFDRFCC_RFDC_001                        (1 << R_CANFD_CFDRFCC_RFDC_SHIFT)  /* FIFO Depth = 4 Messages */
#  define R_CANFD_CFDRFCC_RFDC_010                        (2 << R_CANFD_CFDRFCC_RFDC_SHIFT)  /* FIFO Depth = 8 Messages */
#  define R_CANFD_CFDRFCC_RFDC_011                        (3 << R_CANFD_CFDRFCC_RFDC_SHIFT)  /* FIFO Depth = 16 Messages */
#  define R_CANFD_CFDRFCC_RFDC_100                        (4 << R_CANFD_CFDRFCC_RFDC_SHIFT)  /* FIFO Depth = 32 Messages */
#  define R_CANFD_CFDRFCC_RFDC_101                        (5 << R_CANFD_CFDRFCC_RFDC_SHIFT)  /* FIFO Depth = 48 Messages */
#  define R_CANFD_CFDRFCC_RFDC_110                        (6 << R_CANFD_CFDRFCC_RFDC_SHIFT)  /* Reserved */
#  define R_CANFD_CFDRFCC_RFDC_111                        (7 << R_CANFD_CFDRFCC_RFDC_SHIFT)  /* Reserved */

#define R_CANFD_CFDRFCC_RFIM                      (1 << 12)  /* RX FIFO Interrupt Mode */

#define R_CANFD_CFDRFCC_RFIGCV_SHIFT              (13)  /* RX FIFO Interrupt Generation Counter Value */
#define R_CANFD_CFDRFCC_RFIGCV_MASK               0xe000
#  define R_CANFD_CFDRFCC_RFIGCV_000                      (0 << R_CANFD_CFDRFCC_RFIGCV_SHIFT)  /* Interrupt generated when FIFO is 1/8th Full */
#  define R_CANFD_CFDRFCC_RFIGCV_001                      (1 << R_CANFD_CFDRFCC_RFIGCV_SHIFT)  /* Interrupt generated when FIFO is 1/4th Full */
#  define R_CANFD_CFDRFCC_RFIGCV_010                      (2 << R_CANFD_CFDRFCC_RFIGCV_SHIFT)  /* Interrupt generated when FIFO is 3/8th Full */
#  define R_CANFD_CFDRFCC_RFIGCV_011                      (3 << R_CANFD_CFDRFCC_RFIGCV_SHIFT)  /* Interrupt generated when FIFO is 1/2 Full */
#  define R_CANFD_CFDRFCC_RFIGCV_100                      (4 << R_CANFD_CFDRFCC_RFIGCV_SHIFT)  /* Interrupt generated when FIFO is 5/8th Full */
#  define R_CANFD_CFDRFCC_RFIGCV_101                      (5 << R_CANFD_CFDRFCC_RFIGCV_SHIFT)  /* Interrupt generated when FIFO is 3/4th Full */
#  define R_CANFD_CFDRFCC_RFIGCV_110                      (6 << R_CANFD_CFDRFCC_RFIGCV_SHIFT)  /* Interrupt generated when FIFO is 7/8th Full */
#  define R_CANFD_CFDRFCC_RFIGCV_111                      (7 << R_CANFD_CFDRFCC_RFIGCV_SHIFT)  /* Interrupt generated when FIFO is Full */

/* CFDRFSTS Register bit definitions */
#define R_CANFD_CFDRFSTS_RFEMP                    (1 << 0)  /* RX FIFO Empty */

#define R_CANFD_CFDRFSTS_RFFLL                    (1 << 1)  /* RX FIFO Full */

#define R_CANFD_CFDRFSTS_RFMLT                    (1 << 2)  /* RX FIFO Message Lost */

#define R_CANFD_CFDRFSTS_RFIF                     (1 << 3)  /* RX FIFO Interrupt Flag */

#define R_CANFD_CFDRFSTS_RFMC_SHIFT               (8)  /* RX FIFO Message Count */
#define R_CANFD_CFDRFSTS_RFMC_MASK                0xff00

/* CFDRFPCTR Register bit definitions */
#define R_CANFD_CFDRFPCTR_RFPC_SHIFT              (0)  /* RX FIFO Pointer Control */
#define R_CANFD_CFDRFPCTR_RFPC_MASK               0xff

/* CFDCFCC Register bit definitions */
#define R_CANFD_CFDCFCC_CFE                       (1 << 0)  /* Common FIFO Enable */

#define R_CANFD_CFDCFCC_CFRXIE                    (1 << 1)  /* Common FIFO RX Interrupt Enable */

#define R_CANFD_CFDCFCC_CFTXIE                    (1 << 2)  /* Common FIFO TX Interrupt Enable */

#define R_CANFD_CFDCFCC_CFPLS_SHIFT               (4)  /* Common FIFO Payload Data size configuration */
#define R_CANFD_CFDCFCC_CFPLS_MASK                0x70
#  define R_CANFD_CFDCFCC_CFPLS_000                       (0 << R_CANFD_CFDCFCC_CFPLS_SHIFT)  /* 8 bytes */
#  define R_CANFD_CFDCFCC_CFPLS_001                       (1 << R_CANFD_CFDCFCC_CFPLS_SHIFT)  /* 12 bytes */
#  define R_CANFD_CFDCFCC_CFPLS_010                       (2 << R_CANFD_CFDCFCC_CFPLS_SHIFT)  /* 16 bytes */
#  define R_CANFD_CFDCFCC_CFPLS_011                       (3 << R_CANFD_CFDCFCC_CFPLS_SHIFT)  /* 20 bytes */
#  define R_CANFD_CFDCFCC_CFPLS_100                       (4 << R_CANFD_CFDCFCC_CFPLS_SHIFT)  /* 24 bytes */
#  define R_CANFD_CFDCFCC_CFPLS_101                       (5 << R_CANFD_CFDCFCC_CFPLS_SHIFT)  /* 32 bytes */
#  define R_CANFD_CFDCFCC_CFPLS_110                       (6 << R_CANFD_CFDCFCC_CFPLS_SHIFT)  /* 48 bytes */
#  define R_CANFD_CFDCFCC_CFPLS_111                       (7 << R_CANFD_CFDCFCC_CFPLS_SHIFT)  /* 64 bytes */

#define R_CANFD_CFDCFCC_CFM_SHIFT                 (8)  /* Common FIFO Mode */
#define R_CANFD_CFDCFCC_CFM_MASK                  0x300
#  define R_CANFD_CFDCFCC_CFM_00                          (0 << R_CANFD_CFDCFCC_CFM_SHIFT)  /* RX FIFO Mode */
#  define R_CANFD_CFDCFCC_CFM_01                          (1 << R_CANFD_CFDCFCC_CFM_SHIFT)  /* TX FIFO Mode */
#  define R_CANFD_CFDCFCC_CFM_10                          (2 << R_CANFD_CFDCFCC_CFM_SHIFT)  /* Reserved */
#  define R_CANFD_CFDCFCC_CFM_11                          (3 << R_CANFD_CFDCFCC_CFM_SHIFT)  /* Reserved */

#define R_CANFD_CFDCFCC_CFITSS                    (1 << 10)  /* Common FIFO Interval Timer Source Select */

#define R_CANFD_CFDCFCC_CFITR                     (1 << 11)  /* Common FIFO Interval Timer Resolution */

#define R_CANFD_CFDCFCC_CFIM                      (1 << 12)  /* Common FIFO Interrupt Mode */

#define R_CANFD_CFDCFCC_CFIGCV_SHIFT              (13)  /* Common FIFO Interrupt Generation Counter Value */
#define R_CANFD_CFDCFCC_CFIGCV_MASK               0xe000
#  define R_CANFD_CFDCFCC_CFIGCV_000                      (0 << R_CANFD_CFDCFCC_CFIGCV_SHIFT)  /* Interrupt generated when FIFO is 1/8th Full */
#  define R_CANFD_CFDCFCC_CFIGCV_001                      (1 << R_CANFD_CFDCFCC_CFIGCV_SHIFT)  /* Interrupt generated when FIFO is 1/4th Full */
#  define R_CANFD_CFDCFCC_CFIGCV_010                      (2 << R_CANFD_CFDCFCC_CFIGCV_SHIFT)  /* Interrupt generated when FIFO is 3/8th Full */
#  define R_CANFD_CFDCFCC_CFIGCV_011                      (3 << R_CANFD_CFDCFCC_CFIGCV_SHIFT)  /* Interrupt generated when FIFO is 1/2 Full */
#  define R_CANFD_CFDCFCC_CFIGCV_100                      (4 << R_CANFD_CFDCFCC_CFIGCV_SHIFT)  /* Interrupt generated when FIFO is 5/8th Full */
#  define R_CANFD_CFDCFCC_CFIGCV_101                      (5 << R_CANFD_CFDCFCC_CFIGCV_SHIFT)  /* Interrupt generated when FIFO is 3/4th Full */
#  define R_CANFD_CFDCFCC_CFIGCV_110                      (6 << R_CANFD_CFDCFCC_CFIGCV_SHIFT)  /* Interrupt generated when FIFO is 7/8th Full */
#  define R_CANFD_CFDCFCC_CFIGCV_111                      (7 << R_CANFD_CFDCFCC_CFIGCV_SHIFT)  /* Interrupt generated when FIFO is Full */

#define R_CANFD_CFDCFCC_CFTML_SHIFT               (16)  /* Common FIFO TX Message Buffer Link */
#define R_CANFD_CFDCFCC_CFTML_MASK                0x1f0000

#define R_CANFD_CFDCFCC_CFDC_SHIFT                (21)  /* Common FIFO Depth Configuration */
#define R_CANFD_CFDCFCC_CFDC_MASK                 0xe00000
#  define R_CANFD_CFDCFCC_CFDC_000                        (0 << R_CANFD_CFDCFCC_CFDC_SHIFT)  /* FIFO Depth = 0 Messages */
#  define R_CANFD_CFDCFCC_CFDC_001                        (1 << R_CANFD_CFDCFCC_CFDC_SHIFT)  /* FIFO Depth = 4 Messages */
#  define R_CANFD_CFDCFCC_CFDC_010                        (2 << R_CANFD_CFDCFCC_CFDC_SHIFT)  /* FIFO Depth = 8 Messages */
#  define R_CANFD_CFDCFCC_CFDC_011                        (3 << R_CANFD_CFDCFCC_CFDC_SHIFT)  /* FIFO Depth = 16 Messages */
#  define R_CANFD_CFDCFCC_CFDC_100                        (4 << R_CANFD_CFDCFCC_CFDC_SHIFT)  /* FIFO Depth = 32 Messages */
#  define R_CANFD_CFDCFCC_CFDC_101                        (5 << R_CANFD_CFDCFCC_CFDC_SHIFT)  /* FIFO Depth = 48 Messages */
#  define R_CANFD_CFDCFCC_CFDC_110                        (6 << R_CANFD_CFDCFCC_CFDC_SHIFT)  /* Reserved */
#  define R_CANFD_CFDCFCC_CFDC_111                        (7 << R_CANFD_CFDCFCC_CFDC_SHIFT)  /* Reserved */

#define R_CANFD_CFDCFCC_CFITT_SHIFT               (24)  /* Common FIFO Interval Transmission Time */
#define R_CANFD_CFDCFCC_CFITT_MASK                0xff000000

/* CFDCFSTS Register bit definitions */
#define R_CANFD_CFDCFSTS_CFEMP                    (1 << 0)  /* Common FIFO Empty */

#define R_CANFD_CFDCFSTS_CFFLL                    (1 << 1)  /* Common FIFO Full */

#define R_CANFD_CFDCFSTS_CFMLT                    (1 << 2)  /* Common FIFO Message Lost */

#define R_CANFD_CFDCFSTS_CFRXIF                   (1 << 3)  /* Common RX FIFO Interrupt Flag */

#define R_CANFD_CFDCFSTS_CFTXIF                   (1 << 4)  /* Common TX FIFO Interrupt Flag */

#define R_CANFD_CFDCFSTS_CFMC_SHIFT               (8)  /* Common FIFO Message Count */
#define R_CANFD_CFDCFSTS_CFMC_MASK                0xff00

/* CFDCFPCTR Register bit definitions */
#define R_CANFD_CFDCFPCTR_CFPC_SHIFT              (0)  /* Common FIFO Pointer Control */
#define R_CANFD_CFDCFPCTR_CFPC_MASK               0xff

/* CFDFESTS Register bit definitions */
#define R_CANFD_CFDFESTS_RFXEMP_SHIFT             (0)  /* RX FIF0 Empty Status */
#define R_CANFD_CFDFESTS_RFXEMP_MASK              0x3
#  define R_CANFD_CFDFESTS_RFXEMP_0                       (0 << R_CANFD_CFDFESTS_RFXEMP_SHIFT)  /* Corresponding FIFO not Empty */
#  define R_CANFD_CFDFESTS_RFXEMP_1                       (1 << R_CANFD_CFDFESTS_RFXEMP_SHIFT)  /* Corresponding FIFO Empty */

#define R_CANFD_CFDFESTS_CFXEMP                   (1 << 8)  /* Common FIF0 Empty Status */

/* CFDFFSTS Register bit definitions */
#define R_CANFD_CFDFFSTS_RFXFLL_SHIFT             (0)  /* RX FIF0 Full Status */
#define R_CANFD_CFDFFSTS_RFXFLL_MASK              0x3
#  define R_CANFD_CFDFFSTS_RFXFLL_0                       (0 << R_CANFD_CFDFFSTS_RFXFLL_SHIFT)  /* Corresponding FIFO not Full */
#  define R_CANFD_CFDFFSTS_RFXFLL_1                       (1 << R_CANFD_CFDFFSTS_RFXFLL_SHIFT)  /* Corresponding FIFO Full */

#define R_CANFD_CFDFFSTS_CFXFLL                   (1 << 8)  /* Common FIF0 Full Status */

/* CFDFMSTS Register bit definitions */
#define R_CANFD_CFDFMSTS_RFXMLT_SHIFT             (0)  /* RX FIFO Msg Lost Status */
#define R_CANFD_CFDFMSTS_RFXMLT_MASK              0x3
#  define R_CANFD_CFDFMSTS_RFXMLT_0                       (0 << R_CANFD_CFDFMSTS_RFXMLT_SHIFT)  /* Corresponding FIFO Msg Lost flag not set */
#  define R_CANFD_CFDFMSTS_RFXMLT_1                       (1 << R_CANFD_CFDFMSTS_RFXMLT_SHIFT)  /* Corresponding FIFO Msg Lost flag set */

#define R_CANFD_CFDFMSTS_CFXMLT                   (1 << 8)  /* Common FIFO Msg Lost Status */

/* CFDRFISTS Register bit definitions */
#define R_CANFD_CFDRFISTS_RFXIF_SHIFT             (0)  /* RX FIFO[x] Interrupt Flag Status */
#define R_CANFD_CFDRFISTS_RFXIF_MASK              0x3
#  define R_CANFD_CFDRFISTS_RFXIF_0                       (0 << R_CANFD_CFDRFISTS_RFXIF_SHIFT)  /* Corresponding RX FIFO interrupt flag not set */
#  define R_CANFD_CFDRFISTS_RFXIF_1                       (1 << R_CANFD_CFDRFISTS_RFXIF_SHIFT)  /* Corresponding RX FIFO interrupt flag set */

/* CFDTMC Register bit definitions */
#define R_CANFD_CFDTMC_TMTR                       (1 << 0)  /* TX Message Buffer Transmission Request */

#define R_CANFD_CFDTMC_TMTAR                      (1 << 1)  /* TX Message Buffer Transmission abort Request */

#define R_CANFD_CFDTMC_TMOM                       (1 << 2)  /* TX Message Buffer One-shot Mode */

/* CFDTMSTS Register bit definitions */
#define R_CANFD_CFDTMSTS_TMTSTS                   (1 << 0)  /* TX Message Buffer Transmission Status */

#define R_CANFD_CFDTMSTS_TMTRF_SHIFT              (1)  /* TX Message Buffer Transmission Result Flag */
#define R_CANFD_CFDTMSTS_TMTRF_MASK               0x6
#  define R_CANFD_CFDTMSTS_TMTRF_00                       (0 << R_CANFD_CFDTMSTS_TMTRF_SHIFT)  /* No Result */
#  define R_CANFD_CFDTMSTS_TMTRF_01                       (1 << R_CANFD_CFDTMSTS_TMTRF_SHIFT)  /* Transmission aborted from the TX MB */
#  define R_CANFD_CFDTMSTS_TMTRF_10                       (2 << R_CANFD_CFDTMSTS_TMTRF_SHIFT)  /* Transmission successful from the TX MB & Transmission abort was not requested */
#  define R_CANFD_CFDTMSTS_TMTRF_11                       (3 << R_CANFD_CFDTMSTS_TMTRF_SHIFT)  /* Transmission successful from the TX MB & Transmission abort was requested */

#define R_CANFD_CFDTMSTS_TMTRM                    (1 << 3)  /* TX Message Buffer Transmission Request Mirrored */

#define R_CANFD_CFDTMSTS_TMTARM                   (1 << 4)  /* TX Message Buffer Transmission abort Request Mirrored */

/* CFDTMTRSTS Register bit definitions */
#define R_CANFD_CFDTMTRSTS_CFDTMTRSTSG_SHIFT      (0)  /* TX Message Buffer Transmission Request Status */
#define R_CANFD_CFDTMTRSTS_CFDTMTRSTSG_MASK       0xf
#  define R_CANFD_CFDTMTRSTS_CFDTMTRSTSG_0                (0 << R_CANFD_CFDTMTRSTS_CFDTMTRSTSG_SHIFT)  /* Transmission not requested for corresponding TX Message Buffer */
#  define R_CANFD_CFDTMTRSTS_CFDTMTRSTSG_1                (1 << R_CANFD_CFDTMTRSTS_CFDTMTRSTSG_SHIFT)  /* Transmission requested for corresponding TX Message Buffer */

#define R_CANFD_CFDTMTRSTS_CFDTMTRSTSG_SHIFT      (0)  /* TX Message Buffer Transmission Request Status */
#define R_CANFD_CFDTMTRSTS_CFDTMTRSTSG_MASK       0xf

/* CFDTMTARSTS Register bit definitions */
#define R_CANFD_CFDTMTARSTS_CFDTMTARSTSG_SHIFT    (0)  /* TX Message Buffer Transmission abort Request Status */
#define R_CANFD_CFDTMTARSTS_CFDTMTARSTSG_MASK     0xf
#  define R_CANFD_CFDTMTARSTS_CFDTMTARSTSG_0              (0 << R_CANFD_CFDTMTARSTS_CFDTMTARSTSG_SHIFT)  /* Transmission abort not requested for corresponding TX Message Buffer */
#  define R_CANFD_CFDTMTARSTS_CFDTMTARSTSG_1              (1 << R_CANFD_CFDTMTARSTS_CFDTMTARSTSG_SHIFT)  /* Transmission abort requested for corresponding TX Message Buffer */

#define R_CANFD_CFDTMTARSTS_CFDTMTARSTSG_SHIFT    (0)  /* TX Message Buffer Transmission abort Request Status */
#define R_CANFD_CFDTMTARSTS_CFDTMTARSTSG_MASK     0xf

/* CFDTMTCSTS Register bit definitions */
#define R_CANFD_CFDTMTCSTS_CFDTMTCSTSG_SHIFT      (0)  /* TX Message Buffer Transmission Completion Status */
#define R_CANFD_CFDTMTCSTS_CFDTMTCSTSG_MASK       0xf
#  define R_CANFD_CFDTMTCSTS_CFDTMTCSTSG_0                (0 << R_CANFD_CFDTMTCSTS_CFDTMTCSTSG_SHIFT)  /* Transmission not complete for corresponding TX Message Buffer */
#  define R_CANFD_CFDTMTCSTS_CFDTMTCSTSG_1                (1 << R_CANFD_CFDTMTCSTS_CFDTMTCSTSG_SHIFT)  /* Transmission completed for corresponding TX Message Buffer */

#define R_CANFD_CFDTMTCSTS_CFDTMTCSTSG_SHIFT      (0)  /* TX Message Buffer Transmission Completion Status */
#define R_CANFD_CFDTMTCSTS_CFDTMTCSTSG_MASK       0xf

/* CFDTMTASTS Register bit definitions */
#define R_CANFD_CFDTMTASTS_CFDTMTASTSG_SHIFT      (0)  /* TX Message Buffer Transmission abort Status */
#define R_CANFD_CFDTMTASTS_CFDTMTASTSG_MASK       0xf
#  define R_CANFD_CFDTMTASTS_CFDTMTASTSG_0                (0 << R_CANFD_CFDTMTASTS_CFDTMTASTSG_SHIFT)  /* Transmission not aborted for corresponding TX Message Buffer */
#  define R_CANFD_CFDTMTASTS_CFDTMTASTSG_1                (1 << R_CANFD_CFDTMTASTS_CFDTMTASTSG_SHIFT)  /* Transmission aborted for corresponding TX Message Buffer */

#define R_CANFD_CFDTMTASTS_CFDTMTASTSG_SHIFT      (0)  /* TX Message Buffer Transmission abort Status */
#define R_CANFD_CFDTMTASTS_CFDTMTASTSG_MASK       0xf

/* CFDTMIEC Register bit definitions */
#define R_CANFD_CFDTMIEC_TMIEG_SHIFT              (0)  /* TX Message Buffer Interrupt Enable */
#define R_CANFD_CFDTMIEC_TMIEG_MASK               0xf
#  define R_CANFD_CFDTMIEC_TMIEG_0                        (0 << R_CANFD_CFDTMIEC_TMIEG_SHIFT)  /* TX Message Buffer Interrupt disabled for corresponding TX message buffer */
#  define R_CANFD_CFDTMIEC_TMIEG_1                        (1 << R_CANFD_CFDTMIEC_TMIEG_SHIFT)  /* TX Message Buffer Interrupt enabled for corresponding TX message buffer */

#define R_CANFD_CFDTMIEC_TMIEG_SHIFT              (0)  /* TX Message Buffer Interrupt Enable */
#define R_CANFD_CFDTMIEC_TMIEG_MASK               0xf

/* CFDTXQCC0 Register bit definitions */
#define R_CANFD_CFDTXQCC0_TXQE                    (1 << 0)  /* TX Queue Enable */

#define R_CANFD_CFDTXQCC0_TXQTXIE                 (1 << 5)  /* TX Queue TX Interrupt Enable */

#define R_CANFD_CFDTXQCC0_TXQIM                   (1 << 7)  /* TX Queue Interrupt Mode */

#define R_CANFD_CFDTXQCC0_TXQDC_SHIFT             (8)  /* TX Queue Depth Configuration */
#define R_CANFD_CFDTXQCC0_TXQDC_MASK              0x300
#  define R_CANFD_CFDTXQCC0_TXQDC_0X00                    (0 << R_CANFD_CFDTXQCC0_TXQDC_SHIFT)  /* 0 messages */
#  define R_CANFD_CFDTXQCC0_TXQDC_0X01                    (1 << R_CANFD_CFDTXQCC0_TXQDC_SHIFT)  /* Reserved */
#  define R_CANFD_CFDTXQCC0_TXQDC_0X10                    (2 << R_CANFD_CFDTXQCC0_TXQDC_SHIFT)  /* 3 messages */
#  define R_CANFD_CFDTXQCC0_TXQDC_0X11                    (3 << R_CANFD_CFDTXQCC0_TXQDC_SHIFT)  /* 4 messages */

/* CFDTXQSTS0 Register bit definitions */
#define R_CANFD_CFDTXQSTS0_TXQEMP                 (1 << 0)  /* TX Queue Empty */

#define R_CANFD_CFDTXQSTS0_TXQFLL                 (1 << 1)  /* TX Queue Full */

#define R_CANFD_CFDTXQSTS0_TXQTXIF                (1 << 2)  /* TX Queue TX Interrupt Flag */

#define R_CANFD_CFDTXQSTS0_TXQMC_SHIFT            (8)  /* TX Queue Message Count */
#define R_CANFD_CFDTXQSTS0_TXQMC_MASK             0x3f00

/* CFDTXQPCTR0 Register bit definitions */
#define R_CANFD_CFDTXQPCTR0_TXQPC_SHIFT           (0)  /* TX Queue Pointer Control */
#define R_CANFD_CFDTXQPCTR0_TXQPC_MASK            0xff

/* CFDTHLCC Register bit definitions */
#define R_CANFD_CFDTHLCC_THLE                     (1 << 0)  /* TX History List Enable */

#define R_CANFD_CFDTHLCC_THLIE                    (1 << 8)  /* TX History List Interrupt Enable */

#define R_CANFD_CFDTHLCC_THLIM                    (1 << 9)  /* TX History List Interrupt Mode */

#define R_CANFD_CFDTHLCC_THLDTE                   (1 << 10)  /* TX History List Dedicated TX Enable */

/* CFDTHLSTS Register bit definitions */
#define R_CANFD_CFDTHLSTS_THLEMP                  (1 << 0)  /* TX History List Empty */

#define R_CANFD_CFDTHLSTS_THLFLL                  (1 << 1)  /* TX History List Full */

#define R_CANFD_CFDTHLSTS_THLELT                  (1 << 2)  /* TX History List Entry Lost */

#define R_CANFD_CFDTHLSTS_THLIF                   (1 << 3)  /* TX History List Interrupt Flag */

#define R_CANFD_CFDTHLSTS_THLMC_SHIFT             (8)  /* TX History List Message Count */
#define R_CANFD_CFDTHLSTS_THLMC_MASK              0x3f00

/* CFDTHLPCTR Register bit definitions */
#define R_CANFD_CFDTHLPCTR_THLPC_SHIFT            (0)  /* TX History List Pointer Control */
#define R_CANFD_CFDTHLPCTR_THLPC_MASK             0xff

/* CFDGTINTSTS0 Register bit definitions */
#define R_CANFD_CFDGTINTSTS0_TSIF0                (1 << 0)  /* TX Successful Interrupt Flag Channel 0 */

#define R_CANFD_CFDGTINTSTS0_TAIF0                (1 << 1)  /* TX Abort Interrupt Flag Channel 0 */

#define R_CANFD_CFDGTINTSTS0_TQIF0                (1 << 2)  /* TX Queue Interrupt Flag Channel 0 */

#define R_CANFD_CFDGTINTSTS0_CFTIF0               (1 << 3)  /* COM FIFO TX/GW Mode Interrupt Flag Channel 0 */

#define R_CANFD_CFDGTINTSTS0_THIF0                (1 << 4)  /* TX History List Interrupt Channel 0 */

/* CFDGTSTCFG Register bit definitions */
#define R_CANFD_CFDGTSTCFG_RTMPS_SHIFT            (16)  /* RAM Test Mode Page Select */
#define R_CANFD_CFDGTSTCFG_RTMPS_MASK             0x3ff0000

/* CFDGTSTCTR Register bit definitions */
#define R_CANFD_CFDGTSTCTR_RTME                   (1 << 2)  /* RAM Test Mode Enable */

/* CFDGFDCFG Register bit definitions */
#define R_CANFD_CFDGFDCFG_RPED                    (1 << 0)  /* RES bit Protocol exception disable */

#define R_CANFD_CFDGFDCFG_TSCCFG_SHIFT            (8)  /* Timestamp capture configuration */
#define R_CANFD_CFDGFDCFG_TSCCFG_MASK             0x300
#  define R_CANFD_CFDGFDCFG_TSCCFG_00                     (0 << R_CANFD_CFDGFDCFG_TSCCFG_SHIFT)  /* Timestamp capture at the sample point of SOF (start of frame) */
#  define R_CANFD_CFDGFDCFG_TSCCFG_01                     (1 << R_CANFD_CFDGFDCFG_TSCCFG_SHIFT)  /* Timestamp capture at frame valid indication */
#  define R_CANFD_CFDGFDCFG_TSCCFG_10                     (2 << R_CANFD_CFDGFDCFG_TSCCFG_SHIFT)  /* Timestamp capture at the sample point of RES bit */
#  define R_CANFD_CFDGFDCFG_TSCCFG_11                     (3 << R_CANFD_CFDGFDCFG_TSCCFG_SHIFT)  /* reserved */

/* CFDGLOCKK Register bit definitions */
#define R_CANFD_CFDGLOCKK_LOCK_SHIFT              (0)  /* Lock Key */
#define R_CANFD_CFDGLOCKK_LOCK_MASK               0xffff

/* CFDGAFLIGNENT Register bit definitions */
#define R_CANFD_CFDGAFLIGNENT_IRN_SHIFT           (0)  /* Ignore Rule Number */
#define R_CANFD_CFDGAFLIGNENT_IRN_MASK            0x1f

/* CFDGAFLIGNCTR Register bit definitions */
#define R_CANFD_CFDGAFLIGNCTR_IREN                (1 << 0)  /* Ignore Rule Enable */

#define R_CANFD_CFDGAFLIGNCTR_KEY_SHIFT           (8)  /* Key code */
#define R_CANFD_CFDGAFLIGNCTR_KEY_MASK            0xff00

/* CFDCDTCT Register bit definitions */
#define R_CANFD_CFDCDTCT_RFDMAE0                  (1 << 0)  /* DMA Transfer Enable for RXFIFO 0 */

#define R_CANFD_CFDCDTCT_RFDMAE1                  (1 << 1)  /* DMA Transfer Enable for RXFIFO 1 */

#define R_CANFD_CFDCDTCT_CFDMAE0                  (1 << 8)  /* DMA Transfer Enable for Common FIFO 0 of channel 0 */

/* CFDCDTSTS Register bit definitions */
#define R_CANFD_CFDCDTSTS_RFDMASTS0               (1 << 0)  /* DMA Transfer Status for RX FIFO 0 */

#define R_CANFD_CFDCDTSTS_RFDMASTS1               (1 << 1)  /* DMA Transfer Status for RX FIFO 1 */

#define R_CANFD_CFDCDTSTS_CFDMASTS0               (1 << 8)  /* DMA Transfer Status only for Common FIFO 0 of channel 0 */

/* CFDGRSTC Register bit definitions */
#define R_CANFD_CFDGRSTC_SRST                     (1 << 0)  /* SW reset */

#define R_CANFD_CFDGRSTC_KEY_SHIFT                (8)  /* Key code */
#define R_CANFD_CFDGRSTC_KEY_MASK                 0xff00

/* CFDRPGACC Register bit definitions */
#define R_CANFD_CFDRPGACC_RDTA_SHIFT              (0)  /* RAM Data Test Access */
#define R_CANFD_CFDRPGACC_RDTA_MASK               0xffffffff

/* CFDTM (TX Message Buffer) ID Register bit definitions */
#define R_CANFD_CFDTM_ID_TMID                 (0)   /* TX Message Buffer ID */
#define R_CANFD_CFDTM_ID_TMID_MASK                 (0x1FFFFFFF)
#define R_CANFD_CFDTM_ID_TMRTR                    (1 << 30)  /* TX Message Buffer RTR */
#define R_CANFD_CFDTM_ID_TMIDE                    (1 << 31)  /* TX Message Buffer IDE */

/* CFDTM (TX Message Buffer) PTR Register bit definitions */
#define R_CANFD_CFDTM_PTR_TMDLC               (28)  /* TX Message Buffer DLC */
#define R_CANFD_CFDTM_PTR_TMDLC_MASK               (0xF0000000)

/* CFDRM (RX Message Buffer/FIFO) ID Register bit definitions */
#define R_CANFD_CFDRM_ID_RMID                 (0)   /* RX Message Buffer ID */
#define R_CANFD_CFDRM_ID_RMID_MASK                 (0x1FFFFFFF)
#define R_CANFD_CFDRM_ID_RMRTR                    (1 << 30)  /* RX Message Buffer RTR */
#define R_CANFD_CFDRM_ID_RMIDE                    (1 << 31)  /* RX Message Buffer IDE */

/* CFDRM (RX Message Buffer/FIFO) PTR Register bit definitions */
#define R_CANFD_CFDRM_PTR_RMDLC               (28)  /* RX Message Buffer DLC */
#define R_CANFD_CFDRM_PTR_RMDLC_MASK               (0xF0000000)

/* Maximum number of channels */

#define CANFD_MAX_CHANNELS    64

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_CANFD_H */
