/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_gpt.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* GPT Base Address */
#ifndef R_GPT_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_GPT_BASE           0x40322000
#else
#define R_GPT_BASE           0x50322000
#endif
#endif

/* Channel stride for multi-channel peripherals */
#define R_GPT_CH_STRIDE    0x00000100
#define R_GPT_CH_BASE(ch)   (R_GPT_BASE + ((uint32_t)(ch) * R_GPT_CH_STRIDE))

/* GPT Register Offsets */

#define R_GPT_GTWP_OFFSET                         0x00000000  /* General PWM Timer Write-Protection Register */
#define R_GPT_GTSTR_OFFSET                        0x00000004  /* General PWM Timer Software Start Register */
#define R_GPT_GTSTP_OFFSET                        0x00000008  /* General PWM Timer Software Stop Register */
#define R_GPT_GTCLR_OFFSET                        0x0000000c  /* General PWM Timer Software Clear Register */
#define R_GPT_GTSSR_OFFSET                        0x00000010  /* General PWM Timer Start Source Select Register */
#define R_GPT_GTPSR_OFFSET                        0x00000014  /* General PWM Timer Stop Source Select Register */
#define R_GPT_GTCSR_OFFSET                        0x00000018  /* General PWM Timer Clear Source Select Register */
#define R_GPT_GTUPSR_OFFSET                       0x0000001c  /* General PWM Timer Up Count Source Select Register */
#define R_GPT_GTDNSR_OFFSET                       0x00000020  /* General PWM Timer Down Count Source Select Register */
#define R_GPT_GTICASR_OFFSET                      0x00000024  /* General PWM Timer Input Capture Source Select Register A */
#define R_GPT_GTICBSR_OFFSET                      0x00000028  /* General PWM Timer Input Capture Source Select Register B */
#define R_GPT_GTCR_OFFSET                         0x0000002c  /* General PWM Timer Control Register */
#define R_GPT_GTUDDTYC_OFFSET                     0x00000030  /* General PWM Timer Count Direction and Duty Setting Register */
#define R_GPT_GTIOR_OFFSET                        0x00000034  /* General PWM Timer I/O Control Register */
#define R_GPT_GTINTAD_OFFSET                      0x00000038  /* General PWM Timer Interrupt Output Setting Register */
#define R_GPT_GTST_OFFSET                         0x0000003c  /* General PWM Timer Status Register */
#define R_GPT_GTBER_OFFSET                        0x00000040  /* General PWM Timer Buffer Enable Register */
#define R_GPT_GTITC_OFFSET                        0x00000044  /* General PWM Timer Interrupt and A/D Converter Start Request Skipping Setting Register */
#define R_GPT_GTCNT_OFFSET                        0x00000048  /* General PWM Timer Counter */
/* GTCCR[%s] Registers () */
#define R_GPT_GTCCR_OFFSET(m)                     (0x0000004c + ((m) * 0x00000004))  /* General PWM Timer Compare Capture Register */
#define R_GPT_GTPR_OFFSET                         0x00000064  /* General PWM Timer Cycle Setting Register */
#define R_GPT_GTPBR_OFFSET                        0x00000068  /* General PWM Timer Cycle Setting Buffer Register */
#define R_GPT_GTPDBR_OFFSET                       0x0000006c  /* General PWM Timer Cycle Setting Double-Buffer Register */
#define R_GPT_GTADTRA_OFFSET                      0x00000070  /* A/D Converter Start Request Timing Register A */
#define R_GPT_GTADTBRA_OFFSET                     0x00000074  /* A/D Converter Start Request Timing Buffer Register A */
#define R_GPT_GTADTDBRA_OFFSET                    0x00000078  /* A/D Converter Start Request Timing Double-Buffer Register A */
#define R_GPT_GTADTRB_OFFSET                      0x0000007c  /* A/D Converter Start Request Timing Register B */
#define R_GPT_GTADTBRB_OFFSET                     0x00000080  /* A/D Converter Start Request Timing Buffer Register B */
#define R_GPT_GTADTDBRB_OFFSET                    0x00000084  /* A/D Converter Start Request Timing Double-Buffer Register B */
#define R_GPT_GTDTCR_OFFSET                       0x00000088  /* General PWM Timer Dead Time Control Register */
#define R_GPT_GTDVU_OFFSET                        0x0000008c  /* General PWM Timer Dead Time Value Register U */
#define R_GPT_GTDVD_OFFSET                        0x00000090  /* General PWM Timer Dead Time Value Register D */
#define R_GPT_GTDBU_OFFSET                        0x00000094  /* General PWM Timer Dead Time Buffer Register U */
#define R_GPT_GTDBD_OFFSET                        0x00000098  /* General PWM Timer Dead Time Buffer Register D */
#define R_GPT_GTSOS_OFFSET                        0x0000009c  /* General PWM Timer Output Protection Function Status Register */
#define R_GPT_GTSOTR_OFFSET                       0x000000a0  /* General PWM Timer Output Protection Function Temporary Release Register */
#define R_GPT_GTADSMR_OFFSET                      0x000000a4  /* General PWM Timer A/D Conversion Start Request Signal Monitoring Register */
#define R_GPT_GTEITC_OFFSET                       0x000000a8  /* General PWM Timer Extended Interrupt Skipping Counter Control Register */
#define R_GPT_GTEITLI1_OFFSET                     0x000000ac  /* General PWM Timer Extended Interrupt Skipping Setting Register 1 */
#define R_GPT_GTEITLI2_OFFSET                     0x000000b0  /* General PWM Timer Extended Interrupt Skipping Setting Register 2 */
#define R_GPT_GTEITLB_OFFSET                      0x000000b4  /* General PWM Timer Extended Buffer Transfer Skipping Setting Register */
#define R_GPT_GTICLF_OFFSET                       0x000000b8  /* General PWM Timer Inter Channel Logical Operation Function Setting Register */
#define R_GPT_GTPC_OFFSET                         0x000000bc  /* General PWM Timer Period Count Register */
#define R_GPT_GTADCMSC_OFFSET                     0x000000c0  /* General PWM Timer A/D Conversion Start Request Compare Match Skipping Control Register */
#define R_GPT_GTADCMSS_OFFSET                     0x000000c4  /* General PWM Timer A/D Conversion Start Request Compare Match Skipping Setting Register */
#define R_GPT_GTSECSR_OFFSET                      0x000000d0  /* General PWM Timer Operation Enable Bit Simultaneous Control Channel Select Register */
#define R_GPT_GTSECR_OFFSET                       0x000000d4  /* General PWM Timer Operation Enable Bit Simultaneous Control Register */
#define R_GPT_GTBER2_OFFSET                       0x000000e0  /* General PWM Timer Buffer Enable Register 2 */
#define R_GPT_GTOLBR_OFFSET                       0x000000e4  /* General PWM Timer Output Level Buffer Register */
#define R_GPT_GTICCR_OFFSET                       0x000000ec  /* General PWM Timer Inter Channel Cooperation Input Capture Control
        Register */

/* GPT Register Addresses */

#define R_GPT_GTWP(n)                             (R_GPT_CH_BASE(n) + R_GPT_GTWP_OFFSET)
#define R_GPT_GTSTR(n)                            (R_GPT_CH_BASE(n) + R_GPT_GTSTR_OFFSET)
#define R_GPT_GTSTP(n)                            (R_GPT_CH_BASE(n) + R_GPT_GTSTP_OFFSET)
#define R_GPT_GTCLR(n)                            (R_GPT_CH_BASE(n) + R_GPT_GTCLR_OFFSET)
#define R_GPT_GTSSR(n)                            (R_GPT_CH_BASE(n) + R_GPT_GTSSR_OFFSET)
#define R_GPT_GTPSR(n)                            (R_GPT_CH_BASE(n) + R_GPT_GTPSR_OFFSET)
#define R_GPT_GTCSR(n)                            (R_GPT_CH_BASE(n) + R_GPT_GTCSR_OFFSET)
#define R_GPT_GTUPSR(n)                           (R_GPT_CH_BASE(n) + R_GPT_GTUPSR_OFFSET)
#define R_GPT_GTDNSR(n)                           (R_GPT_CH_BASE(n) + R_GPT_GTDNSR_OFFSET)
#define R_GPT_GTICASR(n)                          (R_GPT_CH_BASE(n) + R_GPT_GTICASR_OFFSET)
#define R_GPT_GTICBSR(n)                          (R_GPT_CH_BASE(n) + R_GPT_GTICBSR_OFFSET)
#define R_GPT_GTCR(n)                             (R_GPT_CH_BASE(n) + R_GPT_GTCR_OFFSET)
#define R_GPT_GTUDDTYC(n)                         (R_GPT_CH_BASE(n) + R_GPT_GTUDDTYC_OFFSET)
#define R_GPT_GTIOR(n)                            (R_GPT_CH_BASE(n) + R_GPT_GTIOR_OFFSET)
#define R_GPT_GTINTAD(n)                          (R_GPT_CH_BASE(n) + R_GPT_GTINTAD_OFFSET)
#define R_GPT_GTST(n)                             (R_GPT_CH_BASE(n) + R_GPT_GTST_OFFSET)
#define R_GPT_GTBER(n)                            (R_GPT_CH_BASE(n) + R_GPT_GTBER_OFFSET)
#define R_GPT_GTITC(n)                            (R_GPT_CH_BASE(n) + R_GPT_GTITC_OFFSET)
#define R_GPT_GTCNT(n)                            (R_GPT_CH_BASE(n) + R_GPT_GTCNT_OFFSET)
#define R_GPT_GTCCR(n, m)                         (R_GPT_CH_BASE(n) + R_GPT_GTCCR_OFFSET(m))
#define R_GPT_GTPR(n)                             (R_GPT_CH_BASE(n) + R_GPT_GTPR_OFFSET)
#define R_GPT_GTPBR(n)                            (R_GPT_CH_BASE(n) + R_GPT_GTPBR_OFFSET)
#define R_GPT_GTPDBR(n)                           (R_GPT_CH_BASE(n) + R_GPT_GTPDBR_OFFSET)
#define R_GPT_GTADTRA(n)                          (R_GPT_CH_BASE(n) + R_GPT_GTADTRA_OFFSET)
#define R_GPT_GTADTBRA(n)                         (R_GPT_CH_BASE(n) + R_GPT_GTADTBRA_OFFSET)
#define R_GPT_GTADTDBRA(n)                        (R_GPT_CH_BASE(n) + R_GPT_GTADTDBRA_OFFSET)
#define R_GPT_GTADTRB(n)                          (R_GPT_CH_BASE(n) + R_GPT_GTADTRB_OFFSET)
#define R_GPT_GTADTBRB(n)                         (R_GPT_CH_BASE(n) + R_GPT_GTADTBRB_OFFSET)
#define R_GPT_GTADTDBRB(n)                        (R_GPT_CH_BASE(n) + R_GPT_GTADTDBRB_OFFSET)
#define R_GPT_GTDTCR(n)                           (R_GPT_CH_BASE(n) + R_GPT_GTDTCR_OFFSET)
#define R_GPT_GTDVU(n)                            (R_GPT_CH_BASE(n) + R_GPT_GTDVU_OFFSET)
#define R_GPT_GTDVD(n)                            (R_GPT_CH_BASE(n) + R_GPT_GTDVD_OFFSET)
#define R_GPT_GTDBU(n)                            (R_GPT_CH_BASE(n) + R_GPT_GTDBU_OFFSET)
#define R_GPT_GTDBD(n)                            (R_GPT_CH_BASE(n) + R_GPT_GTDBD_OFFSET)
#define R_GPT_GTSOS(n)                            (R_GPT_CH_BASE(n) + R_GPT_GTSOS_OFFSET)
#define R_GPT_GTSOTR(n)                           (R_GPT_CH_BASE(n) + R_GPT_GTSOTR_OFFSET)
#define R_GPT_GTADSMR(n)                          (R_GPT_CH_BASE(n) + R_GPT_GTADSMR_OFFSET)
#define R_GPT_GTEITC(n)                           (R_GPT_CH_BASE(n) + R_GPT_GTEITC_OFFSET)
#define R_GPT_GTEITLI1(n)                         (R_GPT_CH_BASE(n) + R_GPT_GTEITLI1_OFFSET)
#define R_GPT_GTEITLI2(n)                         (R_GPT_CH_BASE(n) + R_GPT_GTEITLI2_OFFSET)
#define R_GPT_GTEITLB(n)                          (R_GPT_CH_BASE(n) + R_GPT_GTEITLB_OFFSET)
#define R_GPT_GTICLF(n)                           (R_GPT_CH_BASE(n) + R_GPT_GTICLF_OFFSET)
#define R_GPT_GTPC(n)                             (R_GPT_CH_BASE(n) + R_GPT_GTPC_OFFSET)
#define R_GPT_GTADCMSC(n)                         (R_GPT_CH_BASE(n) + R_GPT_GTADCMSC_OFFSET)
#define R_GPT_GTADCMSS(n)                         (R_GPT_CH_BASE(n) + R_GPT_GTADCMSS_OFFSET)
#define R_GPT_GTSECSR(n)                          (R_GPT_CH_BASE(n) + R_GPT_GTSECSR_OFFSET)
#define R_GPT_GTSECR(n)                           (R_GPT_CH_BASE(n) + R_GPT_GTSECR_OFFSET)
#define R_GPT_GTBER2(n)                           (R_GPT_CH_BASE(n) + R_GPT_GTBER2_OFFSET)
#define R_GPT_GTOLBR(n)                           (R_GPT_CH_BASE(n) + R_GPT_GTOLBR_OFFSET)
#define R_GPT_GTICCR(n)                           (R_GPT_CH_BASE(n) + R_GPT_GTICCR_OFFSET)

/* Register bit definitions */
/* GTWP Register bit definitions */
#define R_GPT_GTWP_PRKEY_SHIFT                    (8)  /* GTWP Key Code */
#define R_GPT_GTWP_PRKEY_MASK                     0xff00
#  define R_GPT_GTWP_PRKEY_0XA5                           (165 << R_GPT_GTWP_PRKEY_SHIFT)  /* Written to these bits, the WP bits write is permitted.  */

#define R_GPT_GTWP_WP                             (1 << 0)  /* Register Write Disable */

#define R_GPT_GTWP_STRWP                          (1 << 1)  /* GTSTR.CSTRT Bit Write Disable */

#define R_GPT_GTWP_STPWP                          (1 << 2)  /* GTSTP.CSTOP Bit Write Disable */

#define R_GPT_GTWP_CLRWP                          (1 << 3)  /* GTCLR.CCLR Bit Write Disable */

#define R_GPT_GTWP_CMNWP                          (1 << 4)  /* Common Register Write Disabled */

/* GTSTR Register bit definitions */
#define R_GPT_GTSTR_CSTRT_S                       (1 << 0)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT0                        (1 << 0)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT1                        (1 << 1)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT2                        (1 << 2)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT3                        (1 << 3)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT4                        (1 << 4)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT5                        (1 << 5)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT6                        (1 << 6)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT7                        (1 << 7)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT8                        (1 << 8)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT9                        (1 << 9)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT10                       (1 << 10)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT11                       (1 << 11)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT12                       (1 << 12)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT13                       (1 << 13)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT14                       (1 << 14)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT15                       (1 << 15)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT16                       (1 << 16)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT17                       (1 << 17)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT18                       (1 << 18)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT19                       (1 << 19)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT20                       (1 << 20)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT21                       (1 << 21)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT22                       (1 << 22)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT23                       (1 << 23)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT24                       (1 << 24)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT25                       (1 << 25)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT26                       (1 << 26)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT27                       (1 << 27)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT28                       (1 << 28)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT29                       (1 << 29)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT30                       (1 << 30)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

#define R_GPT_GTSTR_CSTRT31                       (1 << 31)  /* Channel GTCNT Count StartRead data shows each channel's counter status (GTCR.CST bit). 0 means counter stop. 1 means counter running. */

/* GTSTP Register bit definitions */
#define R_GPT_GTSTP_CSTOP_S                       (1 << 0)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP0                        (1 << 0)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP1                        (1 << 1)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP2                        (1 << 2)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP3                        (1 << 3)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP4                        (1 << 4)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP5                        (1 << 5)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP6                        (1 << 6)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP7                        (1 << 7)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP8                        (1 << 8)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP9                        (1 << 9)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP10                       (1 << 10)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP11                       (1 << 11)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP12                       (1 << 12)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP13                       (1 << 13)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP14                       (1 << 14)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP15                       (1 << 15)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP16                       (1 << 16)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP17                       (1 << 17)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP18                       (1 << 18)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP19                       (1 << 19)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP20                       (1 << 20)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP21                       (1 << 21)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP22                       (1 << 22)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP23                       (1 << 23)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP24                       (1 << 24)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP25                       (1 << 25)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP26                       (1 << 26)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP27                       (1 << 27)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP28                       (1 << 28)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP29                       (1 << 29)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP30                       (1 << 30)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

#define R_GPT_GTSTP_CSTOP31                       (1 << 31)  /* Channel GTCNT Count StopRead data shows each channel's counter status (GTCR.CST bit). 0 means counter runnning. 1 means counter stop. */

/* GTCLR Register bit definitions */
#define R_GPT_GTCLR_CCLR_S                        (1 << 0)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR0                         (1 << 0)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR1                         (1 << 1)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR2                         (1 << 2)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR3                         (1 << 3)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR4                         (1 << 4)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR5                         (1 << 5)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR6                         (1 << 6)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR7                         (1 << 7)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR8                         (1 << 8)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR9                         (1 << 9)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR10                        (1 << 10)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR11                        (1 << 11)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR12                        (1 << 12)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR13                        (1 << 13)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR14                        (1 << 14)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR15                        (1 << 15)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR16                        (1 << 16)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR17                        (1 << 17)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR18                        (1 << 18)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR19                        (1 << 19)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR20                        (1 << 20)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR21                        (1 << 21)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR22                        (1 << 22)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR23                        (1 << 23)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR24                        (1 << 24)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR25                        (1 << 25)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR26                        (1 << 26)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR27                        (1 << 27)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR28                        (1 << 28)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR29                        (1 << 29)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR30                        (1 << 30)  /* Channel GTCNT Count Clear */

#define R_GPT_GTCLR_CCLR31                        (1 << 31)  /* Channel GTCNT Count Clear */

/* GTSSR Register bit definitions */
#define R_GPT_GTSSR_CSTRT                         (1 << 31)  /* Software Source Counter Start Enable */

#define R_GPT_GTSSR_SSELC_S                       (1 << 16)  /* ELC_GPT Event Source Counter Start Enable */

#define R_GPT_GTSSR_SSCBFAH                       (1 << 15)  /* GTIOCB Pin Falling Input during GTIOCA Value High Source Counter Start Enable */

#define R_GPT_GTSSR_SSCBFAL                       (1 << 14)  /* GTIOCB Pin Falling Input during GTIOCA Value Low Source Counter Start Enable */

#define R_GPT_GTSSR_SSCBRAH                       (1 << 13)  /* GTIOCB Pin Rising Input during GTIOCA Value High Source Counter Start Enable */

#define R_GPT_GTSSR_SSCBRAL                       (1 << 12)  /* GTIOCB Pin Rising Input during GTIOCA Value Low Source Counter Start Enable */

#define R_GPT_GTSSR_SSCAFBH                       (1 << 11)  /* GTIOCA Pin Falling Input during GTIOCB Value High Source Counter Start Enable */

#define R_GPT_GTSSR_SSCAFBL                       (1 << 10)  /* GTIOCA Pin Falling Input during GTIOCB Value Low Source Counter Start Enable */

#define R_GPT_GTSSR_SSCARBH                       (1 << 9)  /* GTIOCA Pin Rising Input during GTIOCB Value High Source Counter Start Enable */

#define R_GPT_GTSSR_SSCARBL                       (1 << 8)  /* GTIOCA Pin Rising Input during GTIOCB Value Low Source Counter Start Enable */

#define R_GPT_GTSSR_SSGTRG_SF                     (1 << 1)  /* GTETRG Pin Falling Input Source Counter Start Enable */

#define R_GPT_GTSSR_SSGTRG_SR                     (1 << 0)  /* GTETRG Pin Rising Input Source Counter Start Enable */

#define R_GPT_GTSSR_SSGTRGAR                      (1 << 0)  /* GTETRG Pin Rising Input Source Counter Start Enable */

#define R_GPT_GTSSR_SSGTRGAF                      (1 << 1)  /* GTETRG Pin Falling Input Source Counter Start Enable */

#define R_GPT_GTSSR_SSGTRGBR                      (1 << 2)  /* GTETRG Pin Rising Input Source Counter Start Enable */

#define R_GPT_GTSSR_SSGTRGBF                      (1 << 3)  /* GTETRG Pin Falling Input Source Counter Start Enable */

#define R_GPT_GTSSR_SSGTRGCR                      (1 << 4)  /* GTETRG Pin Rising Input Source Counter Start Enable */

#define R_GPT_GTSSR_SSGTRGCF                      (1 << 5)  /* GTETRG Pin Falling Input Source Counter Start Enable */

#define R_GPT_GTSSR_SSGTRGDR                      (1 << 6)  /* GTETRG Pin Rising Input Source Counter Start Enable */

#define R_GPT_GTSSR_SSGTRGDF                      (1 << 7)  /* GTETRG Pin Falling Input Source Counter Start Enable */

#define R_GPT_GTSSR_SSELCA                        (1 << 16)  /* ELC_GPT Event Source Counter Start Enable */

#define R_GPT_GTSSR_SSELCB                        (1 << 17)  /* ELC_GPT Event Source Counter Start Enable */

#define R_GPT_GTSSR_SSELCC                        (1 << 18)  /* ELC_GPT Event Source Counter Start Enable */

#define R_GPT_GTSSR_SSELCD                        (1 << 19)  /* ELC_GPT Event Source Counter Start Enable */

#define R_GPT_GTSSR_SSELCE                        (1 << 20)  /* ELC_GPT Event Source Counter Start Enable */

#define R_GPT_GTSSR_SSELCF                        (1 << 21)  /* ELC_GPT Event Source Counter Start Enable */

#define R_GPT_GTSSR_SSELCG                        (1 << 22)  /* ELC_GPT Event Source Counter Start Enable */

#define R_GPT_GTSSR_SSELCH                        (1 << 23)  /* ELC_GPT Event Source Counter Start Enable */

/* GTPSR Register bit definitions */
#define R_GPT_GTPSR_CSTOP                         (1 << 31)  /* Software Source Counter Stop Enable */

#define R_GPT_GTPSR_PSELC_S                       (1 << 16)  /* ELC_GPTA Event Source Counter Stop Enable */

#define R_GPT_GTPSR_PSCBFAH                       (1 << 15)  /* GTIOCB Pin Falling Input during GTIOCA Value High Source Counter Stop Enable */

#define R_GPT_GTPSR_PSCBFAL                       (1 << 14)  /* GTIOCB Pin Falling Input during GTIOCA Value Low Source Counter Stop Enable */

#define R_GPT_GTPSR_PSCBRAH                       (1 << 13)  /* GTIOCB Pin Rising Input during GTIOCA Value High Source Counter Stop Enable */

#define R_GPT_GTPSR_PSCBRAL                       (1 << 12)  /* GTIOCB Pin Rising Input during GTIOCA Value Low Source Counter Stop Enable */

#define R_GPT_GTPSR_PSCAFBH                       (1 << 11)  /* GTIOCA Pin Falling Input during GTIOCB Value High Source Counter Stop Enable */

#define R_GPT_GTPSR_PSCAFBL                       (1 << 10)  /* GTIOCA Pin Falling Input during GTIOCB Value Low Source Counter Stop Enable */

#define R_GPT_GTPSR_PSCARBH                       (1 << 9)  /* GTIOCA Pin Rising Input during GTIOCB Value High Source Counter Stop Enable */

#define R_GPT_GTPSR_PSCARBL                       (1 << 8)  /* GTIOCA Pin Rising Input during GTIOCB Value Low Source Counter Stop Enable */

#define R_GPT_GTPSR_PSGTRG_SF                     (1 << 1)  /* GTETRG Pin Falling Input Source Counter Stop Enable */

#define R_GPT_GTPSR_PSGTRG_SR                     (1 << 0)  /* GTETRG Pin Rising Input Source Counter Stop Enable */

#define R_GPT_GTPSR_PSGTRGAR                      (1 << 0)  /* GTETRG Pin Rising Input Source Counter Stop Enable */

#define R_GPT_GTPSR_PSGTRGAF                      (1 << 1)  /* GTETRG Pin Falling Input Source Counter Stop Enable */

#define R_GPT_GTPSR_PSGTRGBR                      (1 << 2)  /* GTETRG Pin Rising Input Source Counter Stop Enable */

#define R_GPT_GTPSR_PSGTRGBF                      (1 << 3)  /* GTETRG Pin Falling Input Source Counter Stop Enable */

#define R_GPT_GTPSR_PSGTRGCR                      (1 << 4)  /* GTETRG Pin Rising Input Source Counter Stop Enable */

#define R_GPT_GTPSR_PSGTRGCF                      (1 << 5)  /* GTETRG Pin Falling Input Source Counter Stop Enable */

#define R_GPT_GTPSR_PSGTRGDR                      (1 << 6)  /* GTETRG Pin Rising Input Source Counter Stop Enable */

#define R_GPT_GTPSR_PSGTRGDF                      (1 << 7)  /* GTETRG Pin Falling Input Source Counter Stop Enable */

#define R_GPT_GTPSR_PSELCA                        (1 << 16)  /* ELC_GPTA Event Source Counter Stop Enable */

#define R_GPT_GTPSR_PSELCB                        (1 << 17)  /* ELC_GPTA Event Source Counter Stop Enable */

#define R_GPT_GTPSR_PSELCC                        (1 << 18)  /* ELC_GPTA Event Source Counter Stop Enable */

#define R_GPT_GTPSR_PSELCD                        (1 << 19)  /* ELC_GPTA Event Source Counter Stop Enable */

#define R_GPT_GTPSR_PSELCE                        (1 << 20)  /* ELC_GPTA Event Source Counter Stop Enable */

#define R_GPT_GTPSR_PSELCF                        (1 << 21)  /* ELC_GPTA Event Source Counter Stop Enable */

#define R_GPT_GTPSR_PSELCG                        (1 << 22)  /* ELC_GPTA Event Source Counter Stop Enable */

#define R_GPT_GTPSR_PSELCH                        (1 << 23)  /* ELC_GPTA Event Source Counter Stop Enable */

/* GTCSR Register bit definitions */
#define R_GPT_GTCSR_CCLR                          (1 << 31)  /* Software Source Counter Clear Enable */

#define R_GPT_GTCSR_CP1CCE                        (1 << 27)  /* Complementary PWM mode1 Crest Source Counter Clear Enable (This bit is only available in GPT324 to GPT329.
                In GPT320 to GPT323, this bit is read as 0. The write value should be 0.) */

#define R_GPT_GTCSR_CSCMSC_SHIFT                  (24)  /* Compare Match/Input Capture/Synchronous counter clearing Source Counter Clear Enable. */
#define R_GPT_GTCSR_CSCMSC_MASK                   0x7000000
#  define R_GPT_GTCSR_CSCMSC_000                          (0 << R_GPT_GTCSR_CSCMSC_SHIFT)  /* Counter clear disabled by Compare match/ Input capture/ Synchronous counter clearing group */
#  define R_GPT_GTCSR_CSCMSC_001                          (1 << R_GPT_GTCSR_CSCMSC_SHIFT)  /* Counter clear enabled at the GTCCRA register compare match/ Input capture */
#  define R_GPT_GTCSR_CSCMSC_010                          (2 << R_GPT_GTCSR_CSCMSC_SHIFT)  /* Counter clear enabled at the GTCCRB register compare match/ Input capture */
#  define R_GPT_GTCSR_CSCMSC_011                          (3 << R_GPT_GTCSR_CSCMSC_SHIFT)  /* Counter clear enabled at the GTCCRC register compare match */
#  define R_GPT_GTCSR_CSCMSC_100                          (4 << R_GPT_GTCSR_CSCMSC_SHIFT)  /* Counter clear enabled at the GTCCRD register compare match */
#  define R_GPT_GTCSR_CSCMSC_101                          (5 << R_GPT_GTCSR_CSCMSC_SHIFT)  /* Counter clear enabled at the GTCCRE register compare match */
#  define R_GPT_GTCSR_CSCMSC_110                          (6 << R_GPT_GTCSR_CSCMSC_SHIFT)  /* Counter clear enabled at the GTCCRF register compare match */
#  define R_GPT_GTCSR_CSCMSC_111                          (7 << R_GPT_GTCSR_CSCMSC_SHIFT)  /* Counter clear enabled at the synchronous counter clearing group */

#define R_GPT_GTCSR_CSELC_S                       (1 << 16)  /* ELC_GPTA Event Source Counter Clear Enable */

#define R_GPT_GTCSR_CSCBFAH                       (1 << 15)  /* GTIOCB Pin Falling Input during GTIOCA Value High Source Counter Clear Enable */

#define R_GPT_GTCSR_CSCBFAL                       (1 << 14)  /* GTIOCB Pin Falling Input during GTIOCA Value Low Source Counter Clear Enable */

#define R_GPT_GTCSR_CSCBRAH                       (1 << 13)  /* GTIOCB Pin Rising Input during GTIOCA Value High Source Counter Clear Enable */

#define R_GPT_GTCSR_CSCBRAL                       (1 << 12)  /* GTIOCB Pin Rising Input during GTIOCA Value Low Source Counter Clear Enable */

#define R_GPT_GTCSR_CSCAFBH                       (1 << 11)  /* GTIOCA Pin Falling Input during GTIOCB Value High Source Counter Clear Enable */

#define R_GPT_GTCSR_CSCAFBL                       (1 << 10)  /* GTIOCA Pin Falling Input during GTIOCB Value Low Source Counter Clear Enable */

#define R_GPT_GTCSR_CSCARBH                       (1 << 9)  /* GTIOCA Pin Rising Input during GTIOCB Value High Source Counter Clear Enable */

#define R_GPT_GTCSR_CSCARBL                       (1 << 8)  /* GTIOCA Pin Rising Input during GTIOCB Value Low Source Counter Clear Enable */

#define R_GPT_GTCSR_CSGTRG_SF                     (1 << 1)  /* GTETRG Pin Falling Input Source Counter Clear Enable */

#define R_GPT_GTCSR_CSGTRG_SR                     (1 << 0)  /* GTETRG Pin Rising Input Source Counter Clear Enable */

#define R_GPT_GTCSR_CSGTRGAR                      (1 << 0)  /* GTETRG Pin Rising Input Source Counter Clear Enable */

#define R_GPT_GTCSR_CSGTRGAF                      (1 << 1)  /* GTETRG Pin Falling Input Source Counter Clear Enable */

#define R_GPT_GTCSR_CSGTRGBR                      (1 << 2)  /* GTETRG Pin Rising Input Source Counter Clear Enable */

#define R_GPT_GTCSR_CSGTRGBF                      (1 << 3)  /* GTETRG Pin Falling Input Source Counter Clear Enable */

#define R_GPT_GTCSR_CSGTRGCR                      (1 << 4)  /* GTETRG Pin Rising Input Source Counter Clear Enable */

#define R_GPT_GTCSR_CSGTRGCF                      (1 << 5)  /* GTETRG Pin Falling Input Source Counter Clear Enable */

#define R_GPT_GTCSR_CSGTRGDR                      (1 << 6)  /* GTETRG Pin Rising Input Source Counter Clear Enable */

#define R_GPT_GTCSR_CSGTRGDF                      (1 << 7)  /* GTETRG Pin Falling Input Source Counter Clear Enable */

#define R_GPT_GTCSR_CSELCA                        (1 << 16)  /* ELC_GPTA Event Source Counter Clear Enable */

#define R_GPT_GTCSR_CSELCB                        (1 << 17)  /* ELC_GPTA Event Source Counter Clear Enable */

#define R_GPT_GTCSR_CSELCC                        (1 << 18)  /* ELC_GPTA Event Source Counter Clear Enable */

#define R_GPT_GTCSR_CSELCD                        (1 << 19)  /* ELC_GPTA Event Source Counter Clear Enable */

#define R_GPT_GTCSR_CSELCE                        (1 << 20)  /* ELC_GPTA Event Source Counter Clear Enable */

#define R_GPT_GTCSR_CSELCF                        (1 << 21)  /* ELC_GPTA Event Source Counter Clear Enable */

#define R_GPT_GTCSR_CSELCG                        (1 << 22)  /* ELC_GPTA Event Source Counter Clear Enable */

#define R_GPT_GTCSR_CSELCH                        (1 << 23)  /* ELC_GPTA Event Source Counter Clear Enable */

/* GTUPSR Register bit definitions */
#define R_GPT_GTUPSR_USILVL_SHIFT                 (24)  /* External Input Level Source Count-Up Enable */
#define R_GPT_GTUPSR_USILVL_MASK                  0xf000000
#  define R_GPT_GTUPSR_USILVL_0000                        (0 << R_GPT_GTUPSR_USILVL_SHIFT)  /* Disables count-up by external input level */
#  define R_GPT_GTUPSR_USILVL_0010                        (2 << R_GPT_GTUPSR_USILVL_SHIFT)  /* Enables count-up by GTIOCnA pin input level 0 */
#  define R_GPT_GTUPSR_USILVL_0011                        (3 << R_GPT_GTUPSR_USILVL_SHIFT)  /* Enables count-up by GTIOCnA pin input level 1 */
#  define R_GPT_GTUPSR_USILVL_0100                        (4 << R_GPT_GTUPSR_USILVL_SHIFT)  /* Enables count-up by GTIOCnB pin input level 0 */
#  define R_GPT_GTUPSR_USILVL_0101                        (5 << R_GPT_GTUPSR_USILVL_SHIFT)  /* Enables count-up by GTIOCnB pin input level 1 */
#  define R_GPT_GTUPSR_USILVL_1000                        (8 << R_GPT_GTUPSR_USILVL_SHIFT)  /* Enables count-up by GTETRGA pin input level 0 */
#  define R_GPT_GTUPSR_USILVL_1001                        (9 << R_GPT_GTUPSR_USILVL_SHIFT)  /* Enables count-up by GTETRGA pin input level 1 */
#  define R_GPT_GTUPSR_USILVL_1010                        (10 << R_GPT_GTUPSR_USILVL_SHIFT)  /* Enables count-up by GTETRGB pin input level 0 */
#  define R_GPT_GTUPSR_USILVL_1011                        (11 << R_GPT_GTUPSR_USILVL_SHIFT)  /* Enables count-up by GTETRGB pin input level 1 */
#  define R_GPT_GTUPSR_USILVL_1100                        (12 << R_GPT_GTUPSR_USILVL_SHIFT)  /* Enables count-up by GTETRGC pin input level 0 */
#  define R_GPT_GTUPSR_USILVL_1101                        (13 << R_GPT_GTUPSR_USILVL_SHIFT)  /* Enables count-up by GTETRGC pin input level 1 */
#  define R_GPT_GTUPSR_USILVL_1110                        (14 << R_GPT_GTUPSR_USILVL_SHIFT)  /* Enables count-up by GTETRGD pin input level 0 */
#  define R_GPT_GTUPSR_USILVL_1111                        (15 << R_GPT_GTUPSR_USILVL_SHIFT)  /* Enables count-up by GTETRGD pin input level 1 */

#define R_GPT_GTUPSR_USELC_S                      (1 << 16)  /* ELC_GPT Event Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USCBFAH                      (1 << 15)  /* GTIOCB Pin Falling Input during GTIOCA Value High Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USCBFAL                      (1 << 14)  /* GTIOCB Pin Falling Input during GTIOCA Value Low Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USCBRAH                      (1 << 13)  /* GTIOCB Pin Rising Input during GTIOCA Value High Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USCBRAL                      (1 << 12)  /* GTIOCB Pin Rising Input during GTIOCA Value Low Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USCAFBH                      (1 << 11)  /* GTIOCA Pin Falling Input during GTIOCB Value High Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USCAFBL                      (1 << 10)  /* GTIOCA Pin Falling Input during GTIOCB Value Low Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USCARBH                      (1 << 9)  /* GTIOCA Pin Rising Input during GTIOCB Value High Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USCARBL                      (1 << 8)  /* GTIOCA Pin Rising Input during GTIOCB Value Low Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USGTRG_SF                    (1 << 1)  /* GTETRG Pin Falling Input Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USGTRG_SR                    (1 << 0)  /* GTETRG Pin Rising Input Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USGTRGAR                     (1 << 0)  /* GTETRG Pin Rising Input Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USGTRGAF                     (1 << 1)  /* GTETRG Pin Falling Input Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USGTRGBR                     (1 << 2)  /* GTETRG Pin Rising Input Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USGTRGBF                     (1 << 3)  /* GTETRG Pin Falling Input Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USGTRGCR                     (1 << 4)  /* GTETRG Pin Rising Input Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USGTRGCF                     (1 << 5)  /* GTETRG Pin Falling Input Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USGTRGDR                     (1 << 6)  /* GTETRG Pin Rising Input Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USGTRGDF                     (1 << 7)  /* GTETRG Pin Falling Input Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USELCA                       (1 << 16)  /* ELC_GPT Event Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USELCB                       (1 << 17)  /* ELC_GPT Event Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USELCC                       (1 << 18)  /* ELC_GPT Event Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USELCD                       (1 << 19)  /* ELC_GPT Event Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USELCE                       (1 << 20)  /* ELC_GPT Event Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USELCF                       (1 << 21)  /* ELC_GPT Event Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USELCG                       (1 << 22)  /* ELC_GPT Event Source Counter Count Up Enable */

#define R_GPT_GTUPSR_USELCH                       (1 << 23)  /* ELC_GPT Event Source Counter Count Up Enable */

/* GTDNSR Register bit definitions */
#define R_GPT_GTDNSR_DSILVL_SHIFT                 (24)  /* External Input Level Source Count-Down Enable */
#define R_GPT_GTDNSR_DSILVL_MASK                  0xf000000
#  define R_GPT_GTDNSR_DSILVL_0000                        (0 << R_GPT_GTDNSR_DSILVL_SHIFT)  /* Disables count-down by external input level */
#  define R_GPT_GTDNSR_DSILVL_0010                        (2 << R_GPT_GTDNSR_DSILVL_SHIFT)  /* Enables count-down by GTIOCnA pin input level 0 */
#  define R_GPT_GTDNSR_DSILVL_0011                        (3 << R_GPT_GTDNSR_DSILVL_SHIFT)  /* Enables count-down by GTIOCnA pin input level 1 */
#  define R_GPT_GTDNSR_DSILVL_0100                        (4 << R_GPT_GTDNSR_DSILVL_SHIFT)  /* Enables count-down by GTIOCnB pin input level 0 */
#  define R_GPT_GTDNSR_DSILVL_0101                        (5 << R_GPT_GTDNSR_DSILVL_SHIFT)  /* Enables count-down by GTIOCnB pin input level 1 */
#  define R_GPT_GTDNSR_DSILVL_1000                        (8 << R_GPT_GTDNSR_DSILVL_SHIFT)  /* Enables count-down by GTETRGA pin input level 0 */
#  define R_GPT_GTDNSR_DSILVL_1001                        (9 << R_GPT_GTDNSR_DSILVL_SHIFT)  /* Enables count-down by GTETRGA pin input level 1 */
#  define R_GPT_GTDNSR_DSILVL_1010                        (10 << R_GPT_GTDNSR_DSILVL_SHIFT)  /* Enables count-down by GTETRGB pin input level 0 */
#  define R_GPT_GTDNSR_DSILVL_1011                        (11 << R_GPT_GTDNSR_DSILVL_SHIFT)  /* Enables count-down by GTETRGB pin input level 1 */
#  define R_GPT_GTDNSR_DSILVL_1100                        (12 << R_GPT_GTDNSR_DSILVL_SHIFT)  /* Enables count-down by GTETRGC pin input level 0 */
#  define R_GPT_GTDNSR_DSILVL_1101                        (13 << R_GPT_GTDNSR_DSILVL_SHIFT)  /* Enables count-down by GTETRGC pin input level 1 */
#  define R_GPT_GTDNSR_DSILVL_1110                        (14 << R_GPT_GTDNSR_DSILVL_SHIFT)  /* Enables count-down by GTETRGD pin input level 0 */
#  define R_GPT_GTDNSR_DSILVL_1111                        (15 << R_GPT_GTDNSR_DSILVL_SHIFT)  /* Enables count-down by GTETRGD pin input level 1 */

#define R_GPT_GTDNSR_DSELC_S                      (1 << 16)  /* ELC_GPT Event Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSCBFAH                      (1 << 15)  /* GTIOCB Pin Falling Input during GTIOCA Value High Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSCBFAL                      (1 << 14)  /* GTIOCB Pin Falling Input during GTIOCA Value Low Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSCBRAH                      (1 << 13)  /* GTIOCB Pin Rising Input during GTIOCA Value High Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSCBRAL                      (1 << 12)  /* GTIOCB Pin Rising Input during GTIOCA Value Low Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSCAFBH                      (1 << 11)  /* GTIOCA Pin Falling Input during GTIOCB Value High Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSCAFBL                      (1 << 10)  /* GTIOCA Pin Falling Input during GTIOCB Value Low Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSCARBH                      (1 << 9)  /* GTIOCA Pin Rising Input during GTIOCB Value High Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSCARBL                      (1 << 8)  /* GTIOCA Pin Rising Input during GTIOCB Value Low Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSGTRG_SF                    (1 << 1)  /* GTETRG Pin Falling Input Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSGTRG_SR                    (1 << 0)  /* GTETRG Pin Rising Input Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSGTRGAR                     (1 << 0)  /* GTETRG Pin Rising Input Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSGTRGAF                     (1 << 1)  /* GTETRG Pin Falling Input Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSGTRGBR                     (1 << 2)  /* GTETRG Pin Rising Input Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSGTRGBF                     (1 << 3)  /* GTETRG Pin Falling Input Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSGTRGCR                     (1 << 4)  /* GTETRG Pin Rising Input Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSGTRGCF                     (1 << 5)  /* GTETRG Pin Falling Input Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSGTRGDR                     (1 << 6)  /* GTETRG Pin Rising Input Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSGTRGDF                     (1 << 7)  /* GTETRG Pin Falling Input Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSELCA                       (1 << 16)  /* ELC_GPT Event Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSELCB                       (1 << 17)  /* ELC_GPT Event Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSELCC                       (1 << 18)  /* ELC_GPT Event Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSELCD                       (1 << 19)  /* ELC_GPT Event Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSELCE                       (1 << 20)  /* ELC_GPT Event Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSELCF                       (1 << 21)  /* ELC_GPT Event Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSELCG                       (1 << 22)  /* ELC_GPT Event Source Counter Count Down Enable */

#define R_GPT_GTDNSR_DSELCH                       (1 << 23)  /* ELC_GPT Event Source Counter Count Down Enable */

/* GTICASR Register bit definitions */
#define R_GPT_GTICASR_ASOC                        (1 << 24)  /* Other channel Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASELC_S                     (1 << 16)  /* ELC_GPT Event Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASCBFAH                     (1 << 15)  /* GTIOCB Pin Falling Input during GTIOCA Value High Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASCBFAL                     (1 << 14)  /* GTIOCB Pin Falling Input during GTIOCA Value Low Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASCBRAH                     (1 << 13)  /* GTIOCB Pin Rising Input during GTIOCA Value High Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASCBRAL                     (1 << 12)  /* GTIOCB Pin Rising Input during GTIOCA Value Low Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASCAFBH                     (1 << 11)  /* GTIOCA Pin Falling Input during GTIOCB Value High Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASCAFBL                     (1 << 10)  /* GTIOCA Pin Falling Input during GTIOCB Value Low Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASCARBH                     (1 << 9)  /* GTIOCA Pin Rising Input during GTIOCB Value High Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASCARBL                     (1 << 8)  /* GTIOCA Pin Rising Input during GTIOCB Value Low Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASGTRG_SF                   (1 << 1)  /* GTETRG Pin Falling Input Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASGTRG_SR                   (1 << 0)  /* GTETRG Pin Rising Input Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASGTRGAR                    (1 << 0)  /* GTETRG Pin Rising Input Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASGTRGAF                    (1 << 1)  /* GTETRG Pin Falling Input Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASGTRGBR                    (1 << 2)  /* GTETRG Pin Rising Input Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASGTRGBF                    (1 << 3)  /* GTETRG Pin Falling Input Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASGTRGCR                    (1 << 4)  /* GTETRG Pin Rising Input Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASGTRGCF                    (1 << 5)  /* GTETRG Pin Falling Input Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASGTRGDR                    (1 << 6)  /* GTETRG Pin Rising Input Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASGTRGDF                    (1 << 7)  /* GTETRG Pin Falling Input Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASELCA                      (1 << 16)  /* ELC_GPT Event Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASELCB                      (1 << 17)  /* ELC_GPT Event Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASELCC                      (1 << 18)  /* ELC_GPT Event Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASELCD                      (1 << 19)  /* ELC_GPT Event Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASELCE                      (1 << 20)  /* ELC_GPT Event Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASELCF                      (1 << 21)  /* ELC_GPT Event Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASELCG                      (1 << 22)  /* ELC_GPT Event Source GTCCRA Input Capture Enable */

#define R_GPT_GTICASR_ASELCH                      (1 << 23)  /* ELC_GPT Event Source GTCCRA Input Capture Enable */

/* GTICBSR Register bit definitions */
#define R_GPT_GTICBSR_BSOC                        (1 << 24)  /* Other channel Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSELC_S                     (1 << 16)  /* ELC_GPT Event Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSCBFAH                     (1 << 15)  /* GTIOCB Pin Falling Input during GTIOCA Value High Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSCBFAL                     (1 << 14)  /* GTIOCB Pin Falling Input during GTIOCA Value Low Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSCBRAH                     (1 << 13)  /* GTIOCB Pin Rising Input during GTIOCA Value High Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSCBRAL                     (1 << 12)  /* GTIOCB Pin Rising Input during GTIOCA Value Low Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSCAFBH                     (1 << 11)  /* GTIOCA Pin Falling Input during GTIOCB Value High Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSCAFBL                     (1 << 10)  /* GTIOCA Pin Falling Input during GTIOCB Value Low Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSCARBH                     (1 << 9)  /* GTIOCA Pin Rising Input during GTIOCB Value High Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSCARBL                     (1 << 8)  /* GTIOCA Pin Rising Input during GTIOCB Value Low Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSGTRG_SF                   (1 << 1)  /* GTETRG Pin Falling Input Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSGTRG_SR                   (1 << 0)  /* GTETRG Pin Rising Input Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSGTRGAR                    (1 << 0)  /* GTETRG Pin Rising Input Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSGTRGAF                    (1 << 1)  /* GTETRG Pin Falling Input Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSGTRGBR                    (1 << 2)  /* GTETRG Pin Rising Input Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSGTRGBF                    (1 << 3)  /* GTETRG Pin Falling Input Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSGTRGCR                    (1 << 4)  /* GTETRG Pin Rising Input Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSGTRGCF                    (1 << 5)  /* GTETRG Pin Falling Input Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSGTRGDR                    (1 << 6)  /* GTETRG Pin Rising Input Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSGTRGDF                    (1 << 7)  /* GTETRG Pin Falling Input Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSELCA                      (1 << 16)  /* ELC_GPT Event Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSELCB                      (1 << 17)  /* ELC_GPT Event Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSELCC                      (1 << 18)  /* ELC_GPT Event Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSELCD                      (1 << 19)  /* ELC_GPT Event Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSELCE                      (1 << 20)  /* ELC_GPT Event Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSELCF                      (1 << 21)  /* ELC_GPT Event Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSELCG                      (1 << 22)  /* ELC_GPT Event Source GTCCRB Input Capture Enable */

#define R_GPT_GTICBSR_BSELCH                      (1 << 23)  /* ELC_GPT Event Source GTCCRB Input Capture Enable */

/* GTCR Register bit definitions */
#define R_GPT_GTCR_CKEG_SHIFT                     (27)  /* Clock Edge Select */
#define R_GPT_GTCR_CKEG_MASK                      0x18000000
#  define R_GPT_GTCR_CKEG_00                              (0 << R_GPT_GTCR_CKEG_SHIFT)  /* Select rising edge of GTETRG for clock count */
#  define R_GPT_GTCR_CKEG_01                              (1 << R_GPT_GTCR_CKEG_SHIFT)  /* Select falling edge of GTETRG for clock count */

#define R_GPT_GTCR_TPCS_SHIFT                     (23)  /* Timer Prescaler Select */
#define R_GPT_GTCR_TPCS_MASK                      0x7800000
#  define R_GPT_GTCR_TPCS_0000                            (0 << R_GPT_GTCR_TPCS_SHIFT)  /* PCLK/1 */
#  define R_GPT_GTCR_TPCS_0001                            (1 << R_GPT_GTCR_TPCS_SHIFT)  /* PCLK/2 */
#  define R_GPT_GTCR_TPCS_0010                            (2 << R_GPT_GTCR_TPCS_SHIFT)  /* PCLK/4 */
#  define R_GPT_GTCR_TPCS_0011                            (3 << R_GPT_GTCR_TPCS_SHIFT)  /* PCLK/8 */
#  define R_GPT_GTCR_TPCS_0100                            (4 << R_GPT_GTCR_TPCS_SHIFT)  /* PCLK/16 */
#  define R_GPT_GTCR_TPCS_0101                            (5 << R_GPT_GTCR_TPCS_SHIFT)  /* PCLK/32 */
#  define R_GPT_GTCR_TPCS_0110                            (6 << R_GPT_GTCR_TPCS_SHIFT)  /* PCLK/64 */
#  define R_GPT_GTCR_TPCS_1000                            (8 << R_GPT_GTCR_TPCS_SHIFT)  /* PCLK/256 */
#  define R_GPT_GTCR_TPCS_1010                            (10 << R_GPT_GTCR_TPCS_SHIFT)  /* PCLK/1024 */
#  define R_GPT_GTCR_TPCS_1100                            (12 << R_GPT_GTCR_TPCS_SHIFT)  /* GTETRGA */
#  define R_GPT_GTCR_TPCS_1101                            (13 << R_GPT_GTCR_TPCS_SHIFT)  /* GTETRGB */
#  define R_GPT_GTCR_TPCS_1110                            (14 << R_GPT_GTCR_TPCS_SHIFT)  /* GTETRGC */
#  define R_GPT_GTCR_TPCS_1111                            (15 << R_GPT_GTCR_TPCS_SHIFT)  /* GTETRGD */

#define R_GPT_GTCR_MD_SHIFT                       (16)  /* Mode Select */
#define R_GPT_GTCR_MD_MASK                        0xf0000
#  define R_GPT_GTCR_MD_0000                              (0 << R_GPT_GTCR_MD_SHIFT)  /* Saw-wave PWM mode 1(single buffer or double buffer possible) */
#  define R_GPT_GTCR_MD_0001                              (1 << R_GPT_GTCR_MD_SHIFT)  /* Saw-wave one-shot pulse mode (fixed buffer operation) */
#  define R_GPT_GTCR_MD_0010                              (2 << R_GPT_GTCR_MD_SHIFT)  /* Saw-wave PWM mode 2(single buffer or double buffer possible) */
#  define R_GPT_GTCR_MD_0011                              (3 << R_GPT_GTCR_MD_SHIFT)  /* Setting prohibited */
#  define R_GPT_GTCR_MD_0100                              (4 << R_GPT_GTCR_MD_SHIFT)  /* Triangle-wave PWM mode 1 (32-bit transfer at trough) (single buffer or double buffer possible) */
#  define R_GPT_GTCR_MD_0101                              (5 << R_GPT_GTCR_MD_SHIFT)  /* Triangle-wave PWM mode 2 (32-bit transfer at crest and trough) (single buffer or double buffer possible) */
#  define R_GPT_GTCR_MD_0110                              (6 << R_GPT_GTCR_MD_SHIFT)  /* Triangle-wave PWM mode 3 (64-bit transfer at trough) (fixed buffer operation) */
#  define R_GPT_GTCR_MD_0111                              (7 << R_GPT_GTCR_MD_SHIFT)  /* Setting prohibited */
#  define R_GPT_GTCR_MD_1000                              (8 << R_GPT_GTCR_MD_SHIFT)  /* Setting prohibited */
#  define R_GPT_GTCR_MD_1001                              (9 << R_GPT_GTCR_MD_SHIFT)  /* Setting prohibited */
#  define R_GPT_GTCR_MD_1010                              (10 << R_GPT_GTCR_MD_SHIFT)  /* Setting prohibited */
#  define R_GPT_GTCR_MD_1011                              (11 << R_GPT_GTCR_MD_SHIFT)  /* Setting prohibited */
#  define R_GPT_GTCR_MD_1100                              (12 << R_GPT_GTCR_MD_SHIFT)  /* Complementary PWM mode 1(transfer at crest) */
#  define R_GPT_GTCR_MD_1101                              (13 << R_GPT_GTCR_MD_SHIFT)  /* Complementary PWM mode 2(transfer at trough) */
#  define R_GPT_GTCR_MD_1110                              (14 << R_GPT_GTCR_MD_SHIFT)  /* Complementary PWM mode 3(transfer at crest and trough) */
#  define R_GPT_GTCR_MD_1111                              (15 << R_GPT_GTCR_MD_SHIFT)  /* Complementary PWM mode 4(immediate transfer) */

#define R_GPT_GTCR_SSCEN                          (1 << 15)  /* Synchronous Set/Clear Enable */

#define R_GPT_GTCR_CPSCD                          (1 << 12)  /* Complementary PWM Mode Synchronous Clear Disable */

#define R_GPT_GTCR_SSCGRP_SHIFT                   (10)  /* Synchronous Set/Clear Group Select */
#define R_GPT_GTCR_SSCGRP_MASK                    0xc00
#  define R_GPT_GTCR_SSCGRP_00                            (0 << R_GPT_GTCR_SSCGRP_SHIFT)  /* Select synchronous set/clear group A */
#  define R_GPT_GTCR_SSCGRP_01                            (1 << R_GPT_GTCR_SSCGRP_SHIFT)  /* Select synchronous set/clear group B */
#  define R_GPT_GTCR_SSCGRP_10                            (2 << R_GPT_GTCR_SSCGRP_SHIFT)  /* Select synchronous set/clear group C */
#  define R_GPT_GTCR_SSCGRP_11                            (3 << R_GPT_GTCR_SSCGRP_SHIFT)  /* Select synchronous set/clear group D */

#define R_GPT_GTCR_SCGTIOC                        (1 << 9)  /* GTIOC input Source Synchronous Clear Enable */

#define R_GPT_GTCR_ICDS                           (1 << 8)  /* Input Capture Operation Select During Count Stop */

#define R_GPT_GTCR_BINV                           (1 << 5)  /* GTIOCnB input/output pin polarity reversal control */

#define R_GPT_GTCR_AINV                           (1 << 4)  /* GTIOCnA input/output pin polarity reversal control */

#define R_GPT_GTCR_CST                            (1 << 0)  /* Count Start */

/* GTUDDTYC Register bit definitions */
#define R_GPT_GTUDDTYC_OABDTYT                    (1 << 28)  /* GTIOCnA,B pin output 0%/100% duty setting reflection timing setting */

#define R_GPT_GTUDDTYC_OBDTYR                     (1 << 27)  /* GTIOCB Output Value Selecting after Releasing  0 percent/100 percent Duty Setting */

#define R_GPT_GTUDDTYC_OBDTYF                     (1 << 26)  /* Forcible GTIOCB Output Duty Setting */

#define R_GPT_GTUDDTYC_OBDTY_SHIFT                (24)  /* GTIOCB Output Duty Setting */
#define R_GPT_GTUDDTYC_OBDTY_MASK                 0x3000000
#  define R_GPT_GTUDDTYC_OBDTY_00                         (0 << R_GPT_GTUDDTYC_OBDTY_SHIFT)  /* GTIOCB pin duty is depend on compare match */
#  define R_GPT_GTUDDTYC_OBDTY_01                         (1 << R_GPT_GTUDDTYC_OBDTY_SHIFT)  /* GTIOCB pin duty is depend on compare match */
#  define R_GPT_GTUDDTYC_OBDTY_10                         (2 << R_GPT_GTUDDTYC_OBDTY_SHIFT)  /* GTIOCB pin duty 0 percent */
#  define R_GPT_GTUDDTYC_OBDTY_11                         (3 << R_GPT_GTUDDTYC_OBDTY_SHIFT)  /* GTIOCB pin duty 100 percent */

#define R_GPT_GTUDDTYC_OADTYR                     (1 << 19)  /* GTIOCA Output Value Selecting after Releasing  0 percent/100 percent Duty Setting */

#define R_GPT_GTUDDTYC_OADTYF                     (1 << 18)  /* Forcible GTIOCA Output Duty Setting */

#define R_GPT_GTUDDTYC_OADTY_SHIFT                (16)  /* GTIOCA Output Duty Setting */
#define R_GPT_GTUDDTYC_OADTY_MASK                 0x30000
#  define R_GPT_GTUDDTYC_OADTY_00                         (0 << R_GPT_GTUDDTYC_OADTY_SHIFT)  /* GTIOCA pin duty is depend on compare match */
#  define R_GPT_GTUDDTYC_OADTY_01                         (1 << R_GPT_GTUDDTYC_OADTY_SHIFT)  /* GTIOCA pin duty is depend on compare match */
#  define R_GPT_GTUDDTYC_OADTY_10                         (2 << R_GPT_GTUDDTYC_OADTY_SHIFT)  /* GTIOCA pin duty 0 percent */
#  define R_GPT_GTUDDTYC_OADTY_11                         (3 << R_GPT_GTUDDTYC_OADTY_SHIFT)  /* GTIOCA pin duty 100 percent */

#define R_GPT_GTUDDTYC_UDF                        (1 << 1)  /* Forcible Count Direction Setting */

#define R_GPT_GTUDDTYC_UD                         (1 << 0)  /* Count Direction Setting */

/* GTIOR Register bit definitions */
#define R_GPT_GTIOR_NFCSB_SHIFT                   (30)  /* Noise Filter B Sampling Clock Select */
#define R_GPT_GTIOR_NFCSB_MASK                    0xc0000000
#  define R_GPT_GTIOR_NFCSB_00                            (0 << R_GPT_GTIOR_NFCSB_SHIFT)  /* PCLK/1 */
#  define R_GPT_GTIOR_NFCSB_01                            (1 << R_GPT_GTIOR_NFCSB_SHIFT)  /* PCLK/4 */
#  define R_GPT_GTIOR_NFCSB_10                            (2 << R_GPT_GTIOR_NFCSB_SHIFT)  /* PCLK/16 */
#  define R_GPT_GTIOR_NFCSB_11                            (3 << R_GPT_GTIOR_NFCSB_SHIFT)  /* PCLK/64 */

#define R_GPT_GTIOR_NFBEN                         (1 << 29)  /* Noise Filter B Enable */

#define R_GPT_GTIOR_OBEOCD                        (1 << 27)  /* GTCCRB Compare Match Cycle End Output Invalidate.(This bit is only available in GPT324 to GPT329.
                 In GPT320 to GPT323, this bit is read as 0. The write value should be 0.) */

#define R_GPT_GTIOR_OBDF_SHIFT                    (25)  /* GTIOCB Pin Disable Value Setting */
#define R_GPT_GTIOR_OBDF_MASK                     0x6000000
#  define R_GPT_GTIOR_OBDF_00                             (0 << R_GPT_GTIOR_OBDF_SHIFT)  /* Output disable is prohibited. */
#  define R_GPT_GTIOR_OBDF_01                             (1 << R_GPT_GTIOR_OBDF_SHIFT)  /* GTIOCB pin is set to Hi-Z when output disable is performed. */
#  define R_GPT_GTIOR_OBDF_10                             (2 << R_GPT_GTIOR_OBDF_SHIFT)  /* GTIOCB pin is set to 0 when output disable is performed. */
#  define R_GPT_GTIOR_OBDF_11                             (3 << R_GPT_GTIOR_OBDF_SHIFT)  /* GTIOCB pin is set to 1 when output disable is performed. */

#define R_GPT_GTIOR_OBE                           (1 << 24)  /* GTIOCB Pin Output Enable */

#define R_GPT_GTIOR_OBHLD                         (1 << 23)  /* GTIOCB Pin Output Setting at the Start/Stop Count */

#define R_GPT_GTIOR_OBDFLT                        (1 << 22)  /* GTIOCB Pin Output Value Setting at the Count Stop */

#define R_GPT_GTIOR_GTIOB_SHIFT                   (16)  /* GTIOCB Pin Function Select */
#define R_GPT_GTIOR_GTIOB_MASK                    0x1f0000
#  define R_GPT_GTIOR_GTIOB_00000                         (0 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is Low. Output retained at cycle end. Output retained at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_00001                         (1 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is Low. Output retained at cycle end. Low output at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_00010                         (2 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is Low. Output retained at cycle end. High output at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_00011                         (3 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is Low. Output retained at cycle end. Output toggled at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_00100                         (4 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is Low. Low output at cycle end. Output retained at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_00101                         (5 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is Low. Low output at cycle end. Low output at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_00110                         (6 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is Low. Low output at cycle end. High output at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_00111                         (7 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is Low. Low output at cycle end. Output toggled at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_01000                         (8 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is Low. High output at cycle end. Output retained at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_01001                         (9 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is Low. High output at cycle end. Low output at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_01010                         (10 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is Low. High output at cycle end. High output at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_01011                         (11 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is Low. High output at cycle end. Output toggled at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_01100                         (12 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is Low. Output toggled at cycle end. Output retained at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_01101                         (13 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is Low. Output toggled at cycle end. Low output at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_01110                         (14 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is Low. Output toggled at cycle end. High output at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_01111                         (15 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is Low. Output toggled at cycle end. Output toggled at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_10000                         (16 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is High. Output retained at cycle end. Output retained at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_10001                         (17 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is High. Output retained at cycle end. Low output at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_10010                         (18 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is High. Output retained at cycle end. High output at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_10011                         (19 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is High. Output retained at cycle end. Output toggled at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_10100                         (20 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is High. Low output at cycle end. Output retained at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_10101                         (21 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is High. Low output at cycle end. Low output at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_10110                         (22 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is High. Low output at cycle end. High output at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_10111                         (23 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is High. Low output at cycle end. Output toggled at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_11000                         (24 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is High. High output at cycle end. Output retained at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_11001                         (25 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is High. High output at cycle end. Low output at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_11010                         (26 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is High. High output at cycle end. High output at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_11011                         (27 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is High. High output at cycle end. Output toggled at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_11100                         (28 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is High. Output toggled at cycle end. Output retained at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_11101                         (29 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is High. Output toggled at cycle end. Low output at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_11110                         (30 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is High. Output toggled at cycle end. High output at GTCCRB compare match. */
#  define R_GPT_GTIOR_GTIOB_11111                         (31 << R_GPT_GTIOR_GTIOB_SHIFT)  /* Initial output is High. Output toggled at cycle end. Output toggled at GTCCRB compare match. */

#define R_GPT_GTIOR_NFCSA_SHIFT                   (14)  /* Noise Filter A Sampling Clock Select */
#define R_GPT_GTIOR_NFCSA_MASK                    0xc000
#  define R_GPT_GTIOR_NFCSA_00                            (0 << R_GPT_GTIOR_NFCSA_SHIFT)  /* PCLK/1 */
#  define R_GPT_GTIOR_NFCSA_01                            (1 << R_GPT_GTIOR_NFCSA_SHIFT)  /* PCLK/4 */
#  define R_GPT_GTIOR_NFCSA_10                            (2 << R_GPT_GTIOR_NFCSA_SHIFT)  /* PCLK/16 */
#  define R_GPT_GTIOR_NFCSA_11                            (3 << R_GPT_GTIOR_NFCSA_SHIFT)  /* PCLK/64 */

#define R_GPT_GTIOR_NFAEN                         (1 << 13)  /* Noise Filter A Enable */

#define R_GPT_GTIOR_PSYE                          (1 << 12)  /* PWM Synchronous output Enable */

#define R_GPT_GTIOR_OAEOCD                        (1 << 11)  /* GTCCRA Compare Match Cycle End Output Invalidate.(This bit is only available in GPT324 to GPT329.
                 In GPT320 to GPT323, this bit is read as 0. The write value should be 0.) */

#define R_GPT_GTIOR_OADF_SHIFT                    (9)  /* GTIOCA Pin Disable Value Setting */
#define R_GPT_GTIOR_OADF_MASK                     0x600
#  define R_GPT_GTIOR_OADF_00                             (0 << R_GPT_GTIOR_OADF_SHIFT)  /* Output disable is prohibited. */
#  define R_GPT_GTIOR_OADF_01                             (1 << R_GPT_GTIOR_OADF_SHIFT)  /* GTIOCA pin is set to Hi-Z when output disable is performed. */
#  define R_GPT_GTIOR_OADF_10                             (2 << R_GPT_GTIOR_OADF_SHIFT)  /* GTIOCA pin is set to 0 when output disable is performed. */
#  define R_GPT_GTIOR_OADF_11                             (3 << R_GPT_GTIOR_OADF_SHIFT)  /* GTIOCA pin is set to 1 when output disable is performed. */

#define R_GPT_GTIOR_OAE                           (1 << 8)  /* GTIOCA Pin Output Enable */

#define R_GPT_GTIOR_OAHLD                         (1 << 7)  /* GTIOCA Pin Output Setting at the Start/Stop Count */

#define R_GPT_GTIOR_OADFLT                        (1 << 6)  /* GTIOCA Pin Output Value Setting at the Count Stop */

#define R_GPT_GTIOR_CPSCIR                        (1 << 5)  /* Complementary PWM Mode Initial Output at Synchronous Clear Disable.(This bit is only available in GPT324 to GPT329.
                In GPT320 to GPT323, this bit is read as 0. The write value should be 0.) */

#define R_GPT_GTIOR_GTIOA_SHIFT                   (0)  /* GTIOCA Pin Function Select */
#define R_GPT_GTIOR_GTIOA_MASK                    0x1f
#  define R_GPT_GTIOR_GTIOA_00000                         (0 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is Low. Output retained at cycle end. Output retained at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_00001                         (1 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is Low. Output retained at cycle end. Low output at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_00010                         (2 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is Low. Output retained at cycle end. High output at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_00011                         (3 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is Low. Output retained at cycle end. Output toggled at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_00100                         (4 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is Low. Low output at cycle end. Output retained at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_00101                         (5 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is Low. Low output at cycle end. Low output at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_00110                         (6 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is Low. Low output at cycle end. High output at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_00111                         (7 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is Low. Low output at cycle end. Output toggled at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_01000                         (8 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is Low. High output at cycle end. Output retained at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_01001                         (9 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is Low. High output at cycle end. Low output at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_01010                         (10 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is Low. High output at cycle end. High output at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_01011                         (11 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is Low. High output at cycle end. Output toggled at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_01100                         (12 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is Low. Output toggled at cycle end. Output retained at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_01101                         (13 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is Low. Output toggled at cycle end. Low output at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_01110                         (14 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is Low. Output toggled at cycle end. High output at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_01111                         (15 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is Low. Output toggled at cycle end. Output toggled at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_10000                         (16 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is High. Output retained at cycle end. Output retained at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_10001                         (17 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is High. Output retained at cycle end. Low output at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_10010                         (18 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is High. Output retained at cycle end. High output at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_10011                         (19 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is High. Output retained at cycle end. Output toggled at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_10100                         (20 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is High. Low output at cycle end. Output retained at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_10101                         (21 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is High. Low output at cycle end. Low output at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_10110                         (22 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is High. Low output at cycle end. High output at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_10111                         (23 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is High. Low output at cycle end. Output toggled at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_11000                         (24 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is High. High output at cycle end. Output retained at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_11001                         (25 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is High. High output at cycle end. Low output at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_11010                         (26 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is High. High output at cycle end. High output at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_11011                         (27 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is High. High output at cycle end. Output toggled at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_11100                         (28 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is High. Output toggled at cycle end. Output retained at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_11101                         (29 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is High. Output toggled at cycle end. Low output at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_11110                         (30 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is High. Output toggled at cycle end. High output at GTCCRA compare match. */
#  define R_GPT_GTIOR_GTIOA_11111                         (31 << R_GPT_GTIOR_GTIOA_SHIFT)  /* Initial output is High. Output toggled at cycle end. Output toggled at GTCCRA compare match. */

/* GTINTAD Register bit definitions */
#define R_GPT_GTINTAD_GTINTPC                     (1 << 31)  /* Period Count Function Finish Interrupt Enable */

#define R_GPT_GTINTAD_GRPABL                      (1 << 30)  /* Same Time Output Level Low Disable Request Enable */

#define R_GPT_GTINTAD_GRPABH                      (1 << 29)  /* Same Time Output Level High Disable Request Enable */

#define R_GPT_GTINTAD_GRPDTE                      (1 << 28)  /* Dead Time Error Output Disable Request Enable */

#define R_GPT_GTINTAD_GRP_SHIFT                   (24)  /* Output Disable Source Select */
#define R_GPT_GTINTAD_GRP_MASK                    0x3000000
#  define R_GPT_GTINTAD_GRP_00                            (0 << R_GPT_GTINTAD_GRP_SHIFT)  /* Group A output disable request */
#  define R_GPT_GTINTAD_GRP_01                            (1 << R_GPT_GTINTAD_GRP_SHIFT)  /* Group B output disable request */
#  define R_GPT_GTINTAD_GRP_10                            (2 << R_GPT_GTINTAD_GRP_SHIFT)  /* Group C output disable request */
#  define R_GPT_GTINTAD_GRP_11                            (3 << R_GPT_GTINTAD_GRP_SHIFT)  /* Group D output disable request */

#define R_GPT_GTINTAD_ADTR_SDEN                   (1 << 17)  /* GTADTRn Register Compare Match (Down-Counting) A/D Conversion Start Request Enable */

#define R_GPT_GTINTAD_ADTR_SUEN                   (1 << 16)  /* GTADTRn Register Compare Match (Up-Counting) A/D Conversion Start Request Enable */

#define R_GPT_GTINTAD_SCFPU                       (1 << 15)  /* Underflow Source Synchronous Clear Enable */

#define R_GPT_GTINTAD_SCFPO                       (1 << 14)  /* Overflow Source Synchronous Clear Enable */

#define R_GPT_GTINTAD_SCF_S                       (1 << 8)  /* GTCCRn Register Compare Match/Input Capture Source Synchronous Clear Enable */

#define R_GPT_GTINTAD_GTINTPR_SHIFT               (6)  /* GTPR Register Compare Match Interrupt Enable */
#define R_GPT_GTINTAD_GTINTPR_MASK                0xc0
#  define R_GPT_GTINTAD_GTINTPR_00                        (0 << R_GPT_GTINTAD_GTINTPR_SHIFT)  /* Interrupt request is disabled. */
#  define R_GPT_GTINTAD_GTINTPR_01                        (1 << R_GPT_GTINTAD_GTINTPR_SHIFT)  /* In saw-wave mode, interrupt requests are enabled at overflows. In triangle-wave
                mode, interrupt requests are enabled at crests. */
#  define R_GPT_GTINTAD_GTINTPR_10                        (2 << R_GPT_GTINTAD_GTINTPR_SHIFT)  /* In saw-wave mode, interrupt requests are enabled at underflows. In triangle-wave
                mode, interrupt requests are enabled at troughs. */
#  define R_GPT_GTINTAD_GTINTPR_11                        (3 << R_GPT_GTINTAD_GTINTPR_SHIFT)  /* In saw-wave mode, interrupt requests are enabled at both overflows and
                underflows. In triangle-wave mode, interrupt requests are enabled at both crests
                and troughs. */

#define R_GPT_GTINTAD_GTINT_S                     (1 << 0)  /* GTCCR%s Register Compare Match/Input Capture Interrupt Enable */

#define R_GPT_GTINTAD_GTINTA                      (1 << 0)  /* GTCCRA Register Compare Match/Input Capture Interrupt Enable */

#define R_GPT_GTINTAD_GTINTB                      (1 << 1)  /* GTCCRB Register Compare Match/Input Capture Interrupt Enable */

#define R_GPT_GTINTAD_GTINTC                      (1 << 2)  /* GTCCRC Register Compare Match/Input Capture Interrupt Enable */

#define R_GPT_GTINTAD_GTINTD                      (1 << 3)  /* GTCCRD Register Compare Match/Input Capture Interrupt Enable */

#define R_GPT_GTINTAD_GTINTE                      (1 << 4)  /* GTCCRE Register Compare Match/Input Capture Interrupt Enable */

#define R_GPT_GTINTAD_GTINTF                      (1 << 5)  /* GTCCRF Register Compare Match/Input Capture Interrupt Enable */

#define R_GPT_GTINTAD_SCFA                        (1 << 8)  /* GTCCRn Register Compare Match/Input Capture Source Synchronous Clear Enable */

#define R_GPT_GTINTAD_SCFB                        (1 << 9)  /* GTCCRn Register Compare Match/Input Capture Source Synchronous Clear Enable */

#define R_GPT_GTINTAD_SCFC                        (1 << 10)  /* GTCCRn Register Compare Match/Input Capture Source Synchronous Clear Enable */

#define R_GPT_GTINTAD_SCFD                        (1 << 11)  /* GTCCRn Register Compare Match/Input Capture Source Synchronous Clear Enable */

#define R_GPT_GTINTAD_SCFE                        (1 << 12)  /* GTCCRn Register Compare Match/Input Capture Source Synchronous Clear Enable */

#define R_GPT_GTINTAD_SCFF                        (1 << 13)  /* GTCCRn Register Compare Match/Input Capture Source Synchronous Clear Enable */

#define R_GPT_GTINTAD_ADTRAUEN                    (1 << 16)  /* GTADTRn Register Compare Match (Up-Counting) A/D Conversion Start Request Enable */

#define R_GPT_GTINTAD_ADTRADEN                    (1 << 17)  /* GTADTRn Register Compare Match (Down-Counting) A/D Conversion Start Request Enable */

#define R_GPT_GTINTAD_ADTRBUEN                    (1 << 18)  /* GTADTRn Register Compare Match (Up-Counting) A/D Conversion Start Request Enable */

#define R_GPT_GTINTAD_ADTRBDEN                    (1 << 19)  /* GTADTRn Register Compare Match (Down-Counting) A/D Conversion Start Request Enable */

/* GTST Register bit definitions */
#define R_GPT_GTST_PCF                            (1 << 31)  /* Period Count Function Finish Flag */

#define R_GPT_GTST_OABLF                          (1 << 30)  /* Same Time Output Level Low Disable Request Enable */

#define R_GPT_GTST_OABHF                          (1 << 29)  /* Same Time Output Level High Disable Request Enable */

#define R_GPT_GTST_DTEF                           (1 << 28)  /* Dead Time Error Flag */

#define R_GPT_GTST_ODF                            (1 << 24)  /* Output Disable Flag */

#define R_GPT_GTST_ADTRBDF                        (1 << 19)  /* GTADTRB Compare Match(Down-Counting) A/D Convertor Start Request Flag */

#define R_GPT_GTST_ADTRBUF                        (1 << 18)  /* GTADTRB Compare Match(Up-Counting) A/D Convertor Start Request Flag */

#define R_GPT_GTST_ADTRADF                        (1 << 17)  /* GTADTRA Compare Match(Down-Counting) A/D Convertor Start Request Flag */

#define R_GPT_GTST_ADTRAUF                        (1 << 16)  /* GTADTRA Compare Match (Up-Counting) A/D Converter Start Request Interrupt Enable */

#define R_GPT_GTST_TUCF                           (1 << 15)  /* Count Direction Flag */

#define R_GPT_GTST_ITCNT_SHIFT                    (8)  /* GTCIV/GTCIU Interrupt Skipping Count Counter(Counter for counting the number of times a timer interrupt has been skipped.) */
#define R_GPT_GTST_ITCNT_MASK                     0x700

#define R_GPT_GTST_TCFPU                          (1 << 7)  /* Underflow Flag */

#define R_GPT_GTST_TCFPO                          (1 << 6)  /* Overflow Flag */

#define R_GPT_GTST_TCFF                           (1 << 5)  /* Input Compare Match Flag F */

#define R_GPT_GTST_TCFE                           (1 << 4)  /* Input Compare Match Flag E */

#define R_GPT_GTST_TCFD                           (1 << 3)  /* Input Compare Match Flag D */

#define R_GPT_GTST_TCFC                           (1 << 2)  /* Input Compare Match Flag C */

#define R_GPT_GTST_TCFB                           (1 << 1)  /* Input Capture/Compare Match Flag B */

#define R_GPT_GTST_TCFA                           (1 << 0)  /* Input Capture/Compare Match Flag A */

/* GTBER Register bit definitions */
#define R_GPT_GTBER_ADTDB                         (1 << 30)  /* GTADTRB Double Buffer Operation */

#define R_GPT_GTBER_ADTTB_SHIFT                   (28)  /* GTADTRB Buffer Transfer Timing Select in the Triangle wavesNOTE: In the Saw waves, values other than 0 0: Transfer at an underflow (in down-counting) or overflow (in up-counting) is performed. */
#define R_GPT_GTBER_ADTTB_MASK                    0x30000000
#  define R_GPT_GTBER_ADTTB_00                            (0 << R_GPT_GTBER_ADTTB_SHIFT)  /* No transfer */
#  define R_GPT_GTBER_ADTTB_01                            (1 << R_GPT_GTBER_ADTTB_SHIFT)  /* Transfer at crest */
#  define R_GPT_GTBER_ADTTB_10                            (2 << R_GPT_GTBER_ADTTB_SHIFT)  /* Transfer at trough */
#  define R_GPT_GTBER_ADTTB_11                            (3 << R_GPT_GTBER_ADTTB_SHIFT)  /* Transfer at both crest and trough */

#define R_GPT_GTBER_ADTDA                         (1 << 26)  /* GTADTRA Double Buffer Operation */

#define R_GPT_GTBER_ADTTA_SHIFT                   (24)  /* GTADTRA Buffer Transfer Timing Select  in the Triangle wavesNOTE: In the Saw waves, values other than 0 0: Transfer at an underflow (in down-counting) or overflow (in up-counting) is performed. */
#define R_GPT_GTBER_ADTTA_MASK                    0x3000000
#  define R_GPT_GTBER_ADTTA_00                            (0 << R_GPT_GTBER_ADTTA_SHIFT)  /* No transfer */
#  define R_GPT_GTBER_ADTTA_01                            (1 << R_GPT_GTBER_ADTTA_SHIFT)  /* Transfer at crest */
#  define R_GPT_GTBER_ADTTA_10                            (2 << R_GPT_GTBER_ADTTA_SHIFT)  /* Transfer at trough */
#  define R_GPT_GTBER_ADTTA_11                            (3 << R_GPT_GTBER_ADTTA_SHIFT)  /* Transfer at both crest and trough */

#define R_GPT_GTBER_CCRSWT                        (1 << 22)  /* GTCCRA and GTCCRB Forcible Buffer OperationThis bit is read as 0. */

#define R_GPT_GTBER_PR_SHIFT                      (20)  /* GTPR Buffer Operation */
#define R_GPT_GTBER_PR_MASK                       0x300000
#  define R_GPT_GTBER_PR_00                               (0 << R_GPT_GTBER_PR_SHIFT)  /* Buffer operation is not performed */
#  define R_GPT_GTBER_PR_01                               (1 << R_GPT_GTBER_PR_SHIFT)  /* Single buffer operation (GTPBR --> GTPR) */

#define R_GPT_GTBER_CCRB_SHIFT                    (18)  /* GTCCRB Buffer Operation */
#define R_GPT_GTBER_CCRB_MASK                     0xc0000
#  define R_GPT_GTBER_CCRB_00                             (0 << R_GPT_GTBER_CCRB_SHIFT)  /* Buffer operation is not performed */
#  define R_GPT_GTBER_CCRB_01                             (1 << R_GPT_GTBER_CCRB_SHIFT)  /* Single buffer operation (GTCCRB <--> GTCCRE) */
#  define R_GPT_GTBER_CCRB_10                             (2 << R_GPT_GTBER_CCRB_SHIFT)  /* Double buffer operation (GTCCRB <--> GTCCRE <--> GTCCRF) */
#  define R_GPT_GTBER_CCRB_11                             (3 << R_GPT_GTBER_CCRB_SHIFT)  /* Double buffer operation (GTCCRB <--> GTCCRE <--> GTCCRF) */

#define R_GPT_GTBER_CCRA_SHIFT                    (16)  /* GTCCRA Buffer Operation */
#define R_GPT_GTBER_CCRA_MASK                     0x30000
#  define R_GPT_GTBER_CCRA_00                             (0 << R_GPT_GTBER_CCRA_SHIFT)  /* Buffer operation is not performed */
#  define R_GPT_GTBER_CCRA_01                             (1 << R_GPT_GTBER_CCRA_SHIFT)  /* Single buffer operation (GTCCRA <--> GTCCRC) */
#  define R_GPT_GTBER_CCRA_10                             (2 << R_GPT_GTBER_CCRA_SHIFT)  /* Double buffer operation (GTCCRA <--> GTCCRC <--> GTCCRD) */
#  define R_GPT_GTBER_CCRA_11                             (3 << R_GPT_GTBER_CCRA_SHIFT)  /* Double buffer operation (GTCCRA <--> GTCCRC <--> GTCCRD) */

#define R_GPT_GTBER_DBRTEC_S                      (1 << 8)  /* GTCCRn Register Double Buffer Repeat Operation Enable */

#define R_GPT_GTBER_BD3                           (1 << 3)  /* BD[3]: GTDV Buffer Operation DisableBD[2] */

#define R_GPT_GTBER_BD2                           (1 << 2)  /* BD[2]: GTADTR Buffer Operation DisableBD */

#define R_GPT_GTBER_BD1                           (1 << 1)  /* BD[1]: GTPR Buffer Operation Disable */

#define R_GPT_GTBER_BD0                           (1 << 0)  /* BD[0]: GTCCR Buffer Operation Disable */

#define R_GPT_GTBER_DBRTECA                       (1 << 8)  /* GTCCRn Register Double Buffer Repeat Operation Enable */

#define R_GPT_GTBER_DBRTECB                       (1 << 10)  /* GTCCRn Register Double Buffer Repeat Operation Enable */

/* GTITC Register bit definitions */
#define R_GPT_GTITC_ADTBL                         (1 << 14)  /* GTADTRB A/D Converter Start Request Link */

#define R_GPT_GTITC_ADTAL                         (1 << 12)  /* GTADTRA A/D Converter Start Request Link */

#define R_GPT_GTITC_IVTT_SHIFT                    (8)  /* GPT_OVF/GPT_UDF Interrupt Skipping Count Select */
#define R_GPT_GTITC_IVTT_MASK                     0x700
#  define R_GPT_GTITC_IVTT_000                            (0 << R_GPT_GTITC_IVTT_SHIFT)  /* No skipping */
#  define R_GPT_GTITC_IVTT_001                            (1 << R_GPT_GTITC_IVTT_SHIFT)  /* Skipping count of 1 */
#  define R_GPT_GTITC_IVTT_010                            (2 << R_GPT_GTITC_IVTT_SHIFT)  /* Skipping count of 2 */
#  define R_GPT_GTITC_IVTT_011                            (3 << R_GPT_GTITC_IVTT_SHIFT)  /* Skipping count of 3 */
#  define R_GPT_GTITC_IVTT_100                            (4 << R_GPT_GTITC_IVTT_SHIFT)  /* Skipping count of 4 */
#  define R_GPT_GTITC_IVTT_101                            (5 << R_GPT_GTITC_IVTT_SHIFT)  /* Skipping count of 5 */
#  define R_GPT_GTITC_IVTT_110                            (6 << R_GPT_GTITC_IVTT_SHIFT)  /* Skipping count of 6 */
#  define R_GPT_GTITC_IVTT_111                            (7 << R_GPT_GTITC_IVTT_SHIFT)  /* Skipping count of 7. */

#define R_GPT_GTITC_IVTC_SHIFT                    (6)  /* GPT_OVF/GPT_UDF Interrupt Skipping Function Select */
#define R_GPT_GTITC_IVTC_MASK                     0xc0
#  define R_GPT_GTITC_IVTC_00                             (0 << R_GPT_GTITC_IVTC_SHIFT)  /* Do not perform skipping */
#  define R_GPT_GTITC_IVTC_01                             (1 << R_GPT_GTITC_IVTC_SHIFT)  /* Count and skip both overflow and underflow for saw waves and crest for triangle waves */
#  define R_GPT_GTITC_IVTC_10                             (2 << R_GPT_GTITC_IVTC_SHIFT)  /* Count and skip both overflow and underflow for saw waves and trough for triangle waves */
#  define R_GPT_GTITC_IVTC_11                             (3 << R_GPT_GTITC_IVTC_SHIFT)  /* Count and skip both overflow and underflow for saw waves and both crest and trough for triangle waves. */

#define R_GPT_GTITC_ITLF                          (1 << 5)  /* GTCCRF Compare Match Interrupt Link */

#define R_GPT_GTITC_ITLE                          (1 << 4)  /* GTCCRE Compare Match Interrupt Link */

#define R_GPT_GTITC_ITLD                          (1 << 3)  /* GTCCRD Compare Match Interrupt Link */

#define R_GPT_GTITC_ITLC                          (1 << 2)  /* GTCCRC Compare Match Interrupt Link */

#define R_GPT_GTITC_ITLB                          (1 << 1)  /* GTCCRB Compare Match/Input Capture Interrupt Link */

#define R_GPT_GTITC_ITLA                          (1 << 0)  /* GTCCRA Compare Match/Input Capture Interrupt Link */

/* GTCNT Register bit definitions */
#define R_GPT_GTCNT_GTCNT_SHIFT                   (0)  /* Counter  */
#define R_GPT_GTCNT_GTCNT_MASK                    0xffffffff

/* GTCCR Register bit definitions */
#define R_GPT_GTCCR_GTCCR_SHIFT                   (0)  /* Compare Capture Register A */
#define R_GPT_GTCCR_GTCCR_MASK                    0xffffffff

/* GTPR Register bit definitions */
#define R_GPT_GTPR_GTPR_SHIFT                     (0)  /* Cycle Setting Register */
#define R_GPT_GTPR_GTPR_MASK                      0xffffffff

/* GTPBR Register bit definitions */
#define R_GPT_GTPBR_GTPBR_SHIFT                   (0)  /* Cycle Setting Buffer Register */
#define R_GPT_GTPBR_GTPBR_MASK                    0xffffffff

/* GTPDBR Register bit definitions */
#define R_GPT_GTPDBR_GTPDBR_SHIFT                 (0)  /* Cycle Setting Double-Buffer Register */
#define R_GPT_GTPDBR_GTPDBR_MASK                  0xffffffff

/* GTADTRA Register bit definitions */
#define R_GPT_GTADTRA_GTADTRA_SHIFT               (0)  /* A/D Converter Start Request Timing Register A */
#define R_GPT_GTADTRA_GTADTRA_MASK                0xffffffff

/* GTADTRB Register bit definitions */
#define R_GPT_GTADTRB_GTADTRB_SHIFT               (0)  /* A/D Converter Start Request Timing Register B */
#define R_GPT_GTADTRB_GTADTRB_MASK                0xffffffff

/* GTADTBRA Register bit definitions */
#define R_GPT_GTADTBRA_GTADTBRA_SHIFT             (0)  /* A/D Converter Start Request Timing Buffer Register A */
#define R_GPT_GTADTBRA_GTADTBRA_MASK              0xffffffff

/* GTADTBRB Register bit definitions */
#define R_GPT_GTADTBRB_GTADTBRB_SHIFT             (0)  /* A/D Converter Start Request Timing Buffer Register B */
#define R_GPT_GTADTBRB_GTADTBRB_MASK              0xffffffff

/* GTADTDBRA Register bit definitions */
#define R_GPT_GTADTDBRA_GTADTDBRA_SHIFT           (0)  /* A/D Converter Start Request Timing Double-Buffer Register A */
#define R_GPT_GTADTDBRA_GTADTDBRA_MASK            0xffffffff

/* GTADTDBRB Register bit definitions */
#define R_GPT_GTADTDBRB_GTADTDBRB_SHIFT           (0)  /* A/D Converter Start Request Timing Double-Buffer Register B */
#define R_GPT_GTADTDBRB_GTADTDBRB_MASK            0xffffffff

/* GTDTCR Register bit definitions */
#define R_GPT_GTDTCR_TDFER                        (1 << 8)  /* GTDVD Setting */

#define R_GPT_GTDTCR_TDBDE                        (1 << 5)  /* GTDVD Buffer Operation Enable */

#define R_GPT_GTDTCR_TDBUE                        (1 << 4)  /* GTDVU Buffer Operation Enable */

#define R_GPT_GTDTCR_TDE                          (1 << 0)  /* Negative-Phase Waveform Setting */

/* GTDVU Register bit definitions */
#define R_GPT_GTDVU_GTDVU_SHIFT                   (0)  /* Dead Time Value Register U */
#define R_GPT_GTDVU_GTDVU_MASK                    0xffffffff

/* GTDVD Register bit definitions */
#define R_GPT_GTDVD_GTDVD_SHIFT                   (0)  /* Dead Time Value Register D */
#define R_GPT_GTDVD_GTDVD_MASK                    0xffffffff

/* GTDBU Register bit definitions */
#define R_GPT_GTDBU_GTDVU_SHIFT                   (0)  /* Dead Time Buffer Register U */
#define R_GPT_GTDBU_GTDVU_MASK                    0xffffffff

/* GTDBD Register bit definitions */
#define R_GPT_GTDBD_GTDBD_SHIFT                   (0)  /* Dead Time Buffer Register D */
#define R_GPT_GTDBD_GTDBD_MASK                    0xffffffff

/* GTSOS Register bit definitions */
#define R_GPT_GTSOS_SOS_SHIFT                     (0)  /* Output Protection Function Status */
#define R_GPT_GTSOS_SOS_MASK                      0x3
#  define R_GPT_GTSOS_SOS_00                              (0 << R_GPT_GTSOS_SOS_SHIFT)  /* Normal operation */
#  define R_GPT_GTSOS_SOS_01                              (1 << R_GPT_GTSOS_SOS_SHIFT)  /* Protected state (GTCCRA = 0 is set during transfer at trough or crest) */
#  define R_GPT_GTSOS_SOS_10                              (2 << R_GPT_GTSOS_SOS_SHIFT)  /* Protected state (GTCCRA >= GTPR is set during transfer at trough) */
#  define R_GPT_GTSOS_SOS_11                              (3 << R_GPT_GTSOS_SOS_SHIFT)  /* Protected state (GTCCRA >= GTPR is set during transfer at crest) */

/* GTSOTR Register bit definitions */
#define R_GPT_GTSOTR_SOTR                         (1 << 0)  /* Output Protection Function Temporary Release */

/* GTADSMR Register bit definitions */
#define R_GPT_GTADSMR_ADSMS0_SHIFT                (0)  /* A/D Conversion Start Request Signal Monitor 0 Selection */
#define R_GPT_GTADSMR_ADSMS0_MASK                 0x3
#  define R_GPT_GTADSMR_ADSMS0_00                         (0 << R_GPT_GTADSMR_ADSMS0_SHIFT)  /* A/D conversion start request signal generated by the GTADTRA register during up-counting. */
#  define R_GPT_GTADSMR_ADSMS0_01                         (1 << R_GPT_GTADSMR_ADSMS0_SHIFT)  /* A/D conversion start request signal generated by the GTADTRA register during down-counting. */
#  define R_GPT_GTADSMR_ADSMS0_10                         (2 << R_GPT_GTADSMR_ADSMS0_SHIFT)  /* A/D conversion start request signal generated by the GTADTRB register during up-counting. */
#  define R_GPT_GTADSMR_ADSMS0_11                         (3 << R_GPT_GTADSMR_ADSMS0_SHIFT)  /* A/D conversion start request signal generated by the GTADTRB register during down-counting. */

#define R_GPT_GTADSMR_ADSMEN0                     (1 << 8)  /* A/D Conversion Start Request Signal Monitor 0 Output Enabling */

#define R_GPT_GTADSMR_ADSMS1_SHIFT                (16)  /* A/D Conversion Start Request Signal Monitor 1 Selection */
#define R_GPT_GTADSMR_ADSMS1_MASK                 0x30000
#  define R_GPT_GTADSMR_ADSMS1_00                         (0 << R_GPT_GTADSMR_ADSMS1_SHIFT)  /* A/D conversion start request signal generated by the GTADTRA register during up-counting. */
#  define R_GPT_GTADSMR_ADSMS1_01                         (1 << R_GPT_GTADSMR_ADSMS1_SHIFT)  /* A/D conversion start request signal generated by the GTADTRA register during down-counting. */
#  define R_GPT_GTADSMR_ADSMS1_10                         (2 << R_GPT_GTADSMR_ADSMS1_SHIFT)  /* A/D conversion start request signal generated by the GTADTRB register during up-counting. */
#  define R_GPT_GTADSMR_ADSMS1_11                         (3 << R_GPT_GTADSMR_ADSMS1_SHIFT)  /* A/D conversion start request signal generated by the GTADTRB register during down-counting. */

#define R_GPT_GTADSMR_ADSMEN1                     (1 << 24)  /* A/D Conversion Start Request Signal Monitor 1 Output Enabling */

/* GTEITC Register bit definitions */
#define R_GPT_GTEITC_EIVTC1_SHIFT                 (0)  /* Extended Interrupt Skipping Counter 1 Count Source Select */
#define R_GPT_GTEITC_EIVTC1_MASK                  0x3
#  define R_GPT_GTEITC_EIVTC1_00                          (0 << R_GPT_GTEITC_EIVTC1_SHIFT)  /* Not counted (not skipped) */
#  define R_GPT_GTEITC_EIVTC1_01                          (1 << R_GPT_GTEITC_EIVTC1_SHIFT)  /* Counting both at overflow or underflow in saw-wave mode, and counting crests in triangle-wave mode or complementary PWM mode */
#  define R_GPT_GTEITC_EIVTC1_10                          (2 << R_GPT_GTEITC_EIVTC1_SHIFT)  /* Counting both at overflow or underflow in saw-wave mode, and counting troughs in triangle-wave mode or complementary PWM mode */
#  define R_GPT_GTEITC_EIVTC1_11                          (3 << R_GPT_GTEITC_EIVTC1_SHIFT)  /* Counting both at overflow or underflow in saw-wave mode, and counting both crests and troughs in triangle-wave mode or complementary PWM mode */

#define R_GPT_GTEITC_EIVTT1_SHIFT                 (4)  /* Extended Interrupt Skipping 1 Skipping Count Setting */
#define R_GPT_GTEITC_EIVTT1_MASK                  0xf0

#define R_GPT_GTEITC_EITCNT1_SHIFT                (12)  /* Extended Interrupt Skipping Counter 1 */
#define R_GPT_GTEITC_EITCNT1_MASK                 0xf000

#define R_GPT_GTEITC_EIVTC2_SHIFT                 (16)  /* Extended Interrupt Skipping Counter 2 Count Source select */
#define R_GPT_GTEITC_EIVTC2_MASK                  0x30000
#  define R_GPT_GTEITC_EIVTC2_00                          (0 << R_GPT_GTEITC_EIVTC2_SHIFT)  /* Not counted (not skipped) */
#  define R_GPT_GTEITC_EIVTC2_01                          (1 << R_GPT_GTEITC_EIVTC2_SHIFT)  /* Counting both at overflow or underflow in saw-wave mode, and counting crests in triangle-wave mode or complementary PWM mode */
#  define R_GPT_GTEITC_EIVTC2_10                          (2 << R_GPT_GTEITC_EIVTC2_SHIFT)  /* Counting both at overflow or underflow in saw-wave mode, and counting troughs in triangle-wave mode or complementary PWM mode */
#  define R_GPT_GTEITC_EIVTC2_11                          (3 << R_GPT_GTEITC_EIVTC2_SHIFT)  /* Counting both at overflow or underflow in saw-wave mode, and counting both crests and troughs in triangle-wave mode or complementary PWM mode */

#define R_GPT_GTEITC_EIVTT2_SHIFT                 (20)  /* Extended Interrupt Skipping 2 Skipping Count Setting */
#define R_GPT_GTEITC_EIVTT2_MASK                  0xf00000

#define R_GPT_GTEITC_EITCNT2IV_SHIFT              (24)  /* Extended Interrupt Skipping Counter 2 Initial Value */
#define R_GPT_GTEITC_EITCNT2IV_MASK               0xf000000

#define R_GPT_GTEITC_EITCNT2_SHIFT                (28)  /* Extended Interrupt Skipping Counter 2 */
#define R_GPT_GTEITC_EITCNT2_MASK                 0xf0000000

/* GTEITLI1 Register bit definitions */
#define R_GPT_GTEITLI1_EITLA_SHIFT                (0)  /* GTCCRA Register Compare Match/Input Capture Interrupt Extended Skipping Function Select */
#define R_GPT_GTEITLI1_EITLA_MASK                 0x7

#define R_GPT_GTEITLI1_EITLB_SHIFT                (4)  /* GTCCRB Register Compare Match/Input Capture Interrupt Extended Skipping Function Select */
#define R_GPT_GTEITLI1_EITLB_MASK                 0x70

#define R_GPT_GTEITLI1_EITLC_SHIFT                (8)  /* GTCCRC Register Compare Match Interrupt Extended Skipping Function Select */
#define R_GPT_GTEITLI1_EITLC_MASK                 0x700

#define R_GPT_GTEITLI1_EITLD_SHIFT                (12)  /* GTCCRD Register Compare Match Interrupt Extended Skipping Function Select */
#define R_GPT_GTEITLI1_EITLD_MASK                 0x7000

#define R_GPT_GTEITLI1_EITLE_SHIFT                (16)  /* GTCCRE Register Compare Match Interrupt Extended Skipping Function Select */
#define R_GPT_GTEITLI1_EITLE_MASK                 0x70000

#define R_GPT_GTEITLI1_EITLF_SHIFT                (20)  /* GTCCRF Register Compare Match Interrupt Extended Skipping Function Select */
#define R_GPT_GTEITLI1_EITLF_MASK                 0x700000

#define R_GPT_GTEITLI1_EITLV_SHIFT                (24)  /* Overflow Interrupt Extended Skipping Function Select */
#define R_GPT_GTEITLI1_EITLV_MASK                 0x7000000

#define R_GPT_GTEITLI1_EITLU_SHIFT                (28)  /* Underflow Interrupt Extended Skipping Function Select */
#define R_GPT_GTEITLI1_EITLU_MASK                 0x70000000

/* GTEITLI2 Register bit definitions */
#define R_GPT_GTEITLI2_EADTAL_SHIFT               (0)  /* GTADTRA Register A/D Conversion Start Request Extended Skipping Function Select */
#define R_GPT_GTEITLI2_EADTAL_MASK                0x7

#define R_GPT_GTEITLI2_EADTBL_SHIFT               (4)  /* GTADTRB Register A/D Conversion Start Request Extended Skipping Function Select */
#define R_GPT_GTEITLI2_EADTBL_MASK                0x70

/* GTEITLB Register bit definitions */
#define R_GPT_GTEITLB_EBTLCA_SHIFT                (0)  /* GTCCRA Register Buffer Transfer Extended Skipping Function Select */
#define R_GPT_GTEITLB_EBTLCA_MASK                 0x7

#define R_GPT_GTEITLB_EBTLCB_SHIFT                (4)  /* GTCCRB Register Buffer Transfer Extended Skipping Function Select */
#define R_GPT_GTEITLB_EBTLCB_MASK                 0x70

#define R_GPT_GTEITLB_EBTLPR_SHIFT                (8)  /* GTPR Register Buffer Transfer Extended Skipping Function Select */
#define R_GPT_GTEITLB_EBTLPR_MASK                 0x700

#define R_GPT_GTEITLB_EBTLADA_SHIFT               (16)  /* GTADTRA Register Buffer Transfer Extended Skipping Function Select */
#define R_GPT_GTEITLB_EBTLADA_MASK                0x70000

#define R_GPT_GTEITLB_EBTLADB_SHIFT               (20)  /* GTADTRB Register Buffer Transfer Extended Skipping Function Select */
#define R_GPT_GTEITLB_EBTLADB_MASK                0x700000

#define R_GPT_GTEITLB_EBTLDVU_SHIFT               (24)  /* GTDVU Register Buffer Transfer Extended Skipping Function Select */
#define R_GPT_GTEITLB_EBTLDVU_MASK                0x7000000

#define R_GPT_GTEITLB_EBTLDVD_SHIFT               (28)  /* GTDVD Register Buffer Transfer Extended Skipping Function Select */
#define R_GPT_GTEITLB_EBTLDVD_MASK                0x70000000

/* GTICLF Register bit definitions */
#define R_GPT_GTICLF_ICLFA_SHIFT                  (0)  /* GTIOCnA Output Logical Operation Function Select */
#define R_GPT_GTICLF_ICLFA_MASK                   0x7
#  define R_GPT_GTICLF_ICLFA_000                          (0 << R_GPT_GTICLF_ICLFA_SHIFT)  /* A (no delay) */
#  define R_GPT_GTICLF_ICLFA_001                          (1 << R_GPT_GTICLF_ICLFA_SHIFT)  /* NOT A (no delay) */
#  define R_GPT_GTICLF_ICLFA_010                          (2 << R_GPT_GTICLF_ICLFA_SHIFT)  /* C (1PCLKGPT delay) */
#  define R_GPT_GTICLF_ICLFA_011                          (3 << R_GPT_GTICLF_ICLFA_SHIFT)  /* NOT C (1PCLKGPT delay) */
#  define R_GPT_GTICLF_ICLFA_100                          (4 << R_GPT_GTICLF_ICLFA_SHIFT)  /* A AND C (1PCLKGPT delay) */
#  define R_GPT_GTICLF_ICLFA_101                          (5 << R_GPT_GTICLF_ICLFA_SHIFT)  /* A OR C (1PCLKGPT delay) */
#  define R_GPT_GTICLF_ICLFA_110                          (6 << R_GPT_GTICLF_ICLFA_SHIFT)  /* A EXOR C (1PCLKGPT delay) */
#  define R_GPT_GTICLF_ICLFA_111                          (7 << R_GPT_GTICLF_ICLFA_SHIFT)  /* A NOR C (1PCLKGPT delay) */

#define R_GPT_GTICLF_ICLFSELC_SHIFT               (4)  /* Inter Channel Signal C Select */
#define R_GPT_GTICLF_ICLFSELC_MASK                0x3f0
#  define R_GPT_GTICLF_ICLFSELC_0X00                      (0 << R_GPT_GTICLF_ICLFSELC_SHIFT)  /* GTIOC0A */
#  define R_GPT_GTICLF_ICLFSELC_0X01                      (1 << R_GPT_GTICLF_ICLFSELC_SHIFT)  /* GTIOC0B */
#  define R_GPT_GTICLF_ICLFSELC_0X02                      (2 << R_GPT_GTICLF_ICLFSELC_SHIFT)  /* GTIOC1A */
#  define R_GPT_GTICLF_ICLFSELC_0X03                      (3 << R_GPT_GTICLF_ICLFSELC_SHIFT)  /* GTIOC1B */
#  define R_GPT_GTICLF_ICLFSELC_0X04                      (4 << R_GPT_GTICLF_ICLFSELC_SHIFT)  /* GTIOC2A */
#  define R_GPT_GTICLF_ICLFSELC_0X05                      (5 << R_GPT_GTICLF_ICLFSELC_SHIFT)  /* GTIOC2B */
#  define R_GPT_GTICLF_ICLFSELC_0X06                      (6 << R_GPT_GTICLF_ICLFSELC_SHIFT)  /* GTIOC3A */
#  define R_GPT_GTICLF_ICLFSELC_0X07                      (7 << R_GPT_GTICLF_ICLFSELC_SHIFT)  /* GTIOC3B */
#  define R_GPT_GTICLF_ICLFSELC_0X08                      (8 << R_GPT_GTICLF_ICLFSELC_SHIFT)  /* GTIOC4A */
#  define R_GPT_GTICLF_ICLFSELC_0X09                      (9 << R_GPT_GTICLF_ICLFSELC_SHIFT)  /* GTIOC4B */
#  define R_GPT_GTICLF_ICLFSELC_0X0A                      (10 << R_GPT_GTICLF_ICLFSELC_SHIFT)  /* GTIOC5A */
#  define R_GPT_GTICLF_ICLFSELC_0X0B                      (11 << R_GPT_GTICLF_ICLFSELC_SHIFT)  /* GTIOC5B */
#  define R_GPT_GTICLF_ICLFSELC_0X0C                      (12 << R_GPT_GTICLF_ICLFSELC_SHIFT)  /* GTIOC6A */
#  define R_GPT_GTICLF_ICLFSELC_0X0D                      (13 << R_GPT_GTICLF_ICLFSELC_SHIFT)  /* GTIOC6B */
#  define R_GPT_GTICLF_ICLFSELC_0X0E                      (14 << R_GPT_GTICLF_ICLFSELC_SHIFT)  /* GTIOC7A */
#  define R_GPT_GTICLF_ICLFSELC_0X0F                      (15 << R_GPT_GTICLF_ICLFSELC_SHIFT)  /* GTIOC7B */
#  define R_GPT_GTICLF_ICLFSELC_0X10                      (16 << R_GPT_GTICLF_ICLFSELC_SHIFT)  /* GTIOC8A */
#  define R_GPT_GTICLF_ICLFSELC_0X11                      (17 << R_GPT_GTICLF_ICLFSELC_SHIFT)  /* GTIOC8B */
#  define R_GPT_GTICLF_ICLFSELC_0X12                      (18 << R_GPT_GTICLF_ICLFSELC_SHIFT)  /* GTIOC9A */
#  define R_GPT_GTICLF_ICLFSELC_0X13                      (19 << R_GPT_GTICLF_ICLFSELC_SHIFT)  /* GTIOC9B */

#define R_GPT_GTICLF_ICLFB_SHIFT                  (16)  /* GTIOCnB Output Logical Operation Function Select */
#define R_GPT_GTICLF_ICLFB_MASK                   0x70000
#  define R_GPT_GTICLF_ICLFB_000                          (0 << R_GPT_GTICLF_ICLFB_SHIFT)  /* B (no delay) */
#  define R_GPT_GTICLF_ICLFB_001                          (1 << R_GPT_GTICLF_ICLFB_SHIFT)  /* NOT B (no delay) */
#  define R_GPT_GTICLF_ICLFB_010                          (2 << R_GPT_GTICLF_ICLFB_SHIFT)  /* D (1PCLKGPT delay) */
#  define R_GPT_GTICLF_ICLFB_011                          (3 << R_GPT_GTICLF_ICLFB_SHIFT)  /* NOT D (1PCLKGPT delay) */
#  define R_GPT_GTICLF_ICLFB_100                          (4 << R_GPT_GTICLF_ICLFB_SHIFT)  /* B AND D (1PCLKGPT delay) */
#  define R_GPT_GTICLF_ICLFB_101                          (5 << R_GPT_GTICLF_ICLFB_SHIFT)  /* B OR D (1PCLKGPTn delay) */
#  define R_GPT_GTICLF_ICLFB_110                          (6 << R_GPT_GTICLF_ICLFB_SHIFT)  /* B EXOR D (1PCLKGPT delay) */
#  define R_GPT_GTICLF_ICLFB_111                          (7 << R_GPT_GTICLF_ICLFB_SHIFT)  /* B NOR D (1PCLKGPT delay) */

#define R_GPT_GTICLF_ICLFSELD_SHIFT               (20)  /* Inter Channel Signal D Select */
#define R_GPT_GTICLF_ICLFSELD_MASK                0x3f00000
#  define R_GPT_GTICLF_ICLFSELD_0X00                      (0 << R_GPT_GTICLF_ICLFSELD_SHIFT)  /* GTIOC0A */
#  define R_GPT_GTICLF_ICLFSELD_0X01                      (1 << R_GPT_GTICLF_ICLFSELD_SHIFT)  /* GTIOC0B */
#  define R_GPT_GTICLF_ICLFSELD_0X02                      (2 << R_GPT_GTICLF_ICLFSELD_SHIFT)  /* GTIOC1A */
#  define R_GPT_GTICLF_ICLFSELD_0X03                      (3 << R_GPT_GTICLF_ICLFSELD_SHIFT)  /* GTIOC1B */
#  define R_GPT_GTICLF_ICLFSELD_0X04                      (4 << R_GPT_GTICLF_ICLFSELD_SHIFT)  /* GTIOC2A */
#  define R_GPT_GTICLF_ICLFSELD_0X05                      (5 << R_GPT_GTICLF_ICLFSELD_SHIFT)  /* GTIOC2B */
#  define R_GPT_GTICLF_ICLFSELD_0X06                      (6 << R_GPT_GTICLF_ICLFSELD_SHIFT)  /* GTIOC3A */
#  define R_GPT_GTICLF_ICLFSELD_0X07                      (7 << R_GPT_GTICLF_ICLFSELD_SHIFT)  /* GTIOC3B */
#  define R_GPT_GTICLF_ICLFSELD_0X08                      (8 << R_GPT_GTICLF_ICLFSELD_SHIFT)  /* GTIOC4A */
#  define R_GPT_GTICLF_ICLFSELD_0X09                      (9 << R_GPT_GTICLF_ICLFSELD_SHIFT)  /* GTIOC4B */
#  define R_GPT_GTICLF_ICLFSELD_0X0A                      (10 << R_GPT_GTICLF_ICLFSELD_SHIFT)  /* GTIOC5A */
#  define R_GPT_GTICLF_ICLFSELD_0X0B                      (11 << R_GPT_GTICLF_ICLFSELD_SHIFT)  /* GTIOC5B */
#  define R_GPT_GTICLF_ICLFSELD_0X0C                      (12 << R_GPT_GTICLF_ICLFSELD_SHIFT)  /* GTIOC6A */
#  define R_GPT_GTICLF_ICLFSELD_0X0D                      (13 << R_GPT_GTICLF_ICLFSELD_SHIFT)  /* GTIOC6B */
#  define R_GPT_GTICLF_ICLFSELD_0X0E                      (14 << R_GPT_GTICLF_ICLFSELD_SHIFT)  /* GTIOC7A */
#  define R_GPT_GTICLF_ICLFSELD_0X0F                      (15 << R_GPT_GTICLF_ICLFSELD_SHIFT)  /* GTIOC7B */
#  define R_GPT_GTICLF_ICLFSELD_0X10                      (16 << R_GPT_GTICLF_ICLFSELD_SHIFT)  /* GTIOC8A */
#  define R_GPT_GTICLF_ICLFSELD_0X11                      (17 << R_GPT_GTICLF_ICLFSELD_SHIFT)  /* GTIOC8B */
#  define R_GPT_GTICLF_ICLFSELD_0X12                      (18 << R_GPT_GTICLF_ICLFSELD_SHIFT)  /* GTIOC9A */
#  define R_GPT_GTICLF_ICLFSELD_0X13                      (19 << R_GPT_GTICLF_ICLFSELD_SHIFT)  /* GTIOC9B */

/* GTPC Register bit definitions */
#define R_GPT_GTPC_PCEN                           (1 << 0)  /* Period Count Function Enable */

#define R_GPT_GTPC_ASTP                           (1 << 8)  /* Automatic Stop Function Enable */

#define R_GPT_GTPC_PCNT_SHIFT                     (16)  /* Period Counter */
#define R_GPT_GTPC_PCNT_MASK                      0xfff0000

/* GTADCMSC Register bit definitions */
#define R_GPT_GTADCMSC_ADCMSCNT_S_SHIFT           (12)  /* A/D Conversion Start Request Compare Match Skipping Counter %s */
#define R_GPT_GTADCMSC_ADCMSCNT_S_MASK            0xf000

#define R_GPT_GTADCMSC_ADCMSCNT_SIV_SHIFT         (8)  /* A/D Conversion Start Request Compare Match Skipping Counter %s Initial Value */
#define R_GPT_GTADCMSC_ADCMSCNT_SIV_MASK          0xf00

#define R_GPT_GTADCMSC_ADCMST_S_SHIFT             (4)  /* A/D Conversion Start Request Compare Match Skipping %s Skipping Count Setting */
#define R_GPT_GTADCMSC_ADCMST_S_MASK              0xf0

#define R_GPT_GTADCMSC_ADCMSC_S_SHIFT             (0)  /* A/D Conversion Start Request Compare Match Skipping Counter %s Count Source Select */
#define R_GPT_GTADCMSC_ADCMSC_S_MASK              0x3
#  define R_GPT_GTADCMSC_ADCMSC_S_00                      (0 << R_GPT_GTADCMSC_ADCMSC_S_SHIFT)  /* Not counted (not skipped) */
#  define R_GPT_GTADCMSC_ADCMSC_S_01                      (1 << R_GPT_GTADCMSC_ADCMSC_S_SHIFT)  /* Counting GTADTRA register compare match */
#  define R_GPT_GTADCMSC_ADCMSC_S_10                      (2 << R_GPT_GTADCMSC_ADCMSC_S_SHIFT)  /* Counting GTADTRB register compare match */
#  define R_GPT_GTADCMSC_ADCMSC_S_11                      (3 << R_GPT_GTADCMSC_ADCMSC_S_SHIFT)  /* Counting both GTADTRA register compare match and GTADTRB register compare match */

#define R_GPT_GTADCMSC_ADCMSC1_SHIFT              (0)  /* A/D Conversion Start Request Compare Match Skipping Counter 1 Count Source Select */
#define R_GPT_GTADCMSC_ADCMSC1_MASK               0x3

#define R_GPT_GTADCMSC_ADCMST1_SHIFT              (4)  /* A/D Conversion Start Request Compare Match Skipping 1 Skipping Count Setting */
#define R_GPT_GTADCMSC_ADCMST1_MASK               0xf0

#define R_GPT_GTADCMSC_ADCMSCNT1IV_SHIFT          (8)  /* A/D Conversion Start Request Compare Match Skipping Counter 1 Initial Value */
#define R_GPT_GTADCMSC_ADCMSCNT1IV_MASK           0xf00

#define R_GPT_GTADCMSC_ADCMSCNT1_SHIFT            (12)  /* A/D Conversion Start Request Compare Match Skipping Counter 1 */
#define R_GPT_GTADCMSC_ADCMSCNT1_MASK             0xf000

#define R_GPT_GTADCMSC_ADCMSC2_SHIFT              (16)  /* A/D Conversion Start Request Compare Match Skipping Counter 2 Count Source Select */
#define R_GPT_GTADCMSC_ADCMSC2_MASK               0x30000

#define R_GPT_GTADCMSC_ADCMST2_SHIFT              (20)  /* A/D Conversion Start Request Compare Match Skipping 2 Skipping Count Setting */
#define R_GPT_GTADCMSC_ADCMST2_MASK               0xf00000

#define R_GPT_GTADCMSC_ADCMSCNT2IV_SHIFT          (24)  /* A/D Conversion Start Request Compare Match Skipping Counter 2 Initial Value */
#define R_GPT_GTADCMSC_ADCMSCNT2IV_MASK           0xf000000

#define R_GPT_GTADCMSC_ADCMSCNT2_SHIFT            (28)  /* A/D Conversion Start Request Compare Match Skipping Counter 2 */
#define R_GPT_GTADCMSC_ADCMSCNT2_MASK             0xf0000000

/* GTADCMSS Register bit definitions */
#define R_GPT_GTADCMSS_ADCMSAL_SHIFT              (0)  /* GTADTRA Register A/D Conversion Start Request Compare Match Skipping Function Select */
#define R_GPT_GTADCMSS_ADCMSAL_MASK               0x7

#define R_GPT_GTADCMSS_ADCMSBL_SHIFT              (4)  /* GTADTRB Register A/D Conversion Start Request Compare Match Skipping Function Select */
#define R_GPT_GTADCMSS_ADCMSBL_MASK               0x70

#define R_GPT_GTADCMSS_ADCMBSA_SHIFT              (16)  /* GTADTRA Register Buffer Transfer by A/D Conversion Start Request Compare Match Skipping Function Select */
#define R_GPT_GTADCMSS_ADCMBSA_MASK               0x70000

#define R_GPT_GTADCMSS_ADCMBSB_SHIFT              (20)  /* GTADTRB Register Buffer Transfer by A/D Conversion Start Request Compare Match Skipping Function Select */
#define R_GPT_GTADCMSS_ADCMBSB_MASK               0x700000

/* GTSECSR Register bit definitions */
#define R_GPT_GTSECSR_SECSEL0                     (1 << 0)  /* Channel 0 Operation Enable Bit Simultaneous Control Channel Select */

#define R_GPT_GTSECSR_SECSEL1                     (1 << 1)  /* Channel 1 Operation Enable Bit Simultaneous Control Channel Select */

#define R_GPT_GTSECSR_SECSEL2                     (1 << 2)  /* Channel 2 Operation Enable Bit Simultaneous Control Channel Select */

#define R_GPT_GTSECSR_SECSEL3                     (1 << 3)  /* Channel 3 Operation Enable Bit Simultaneous Control Channel Select */

#define R_GPT_GTSECSR_SECSEL4                     (1 << 4)  /* Channel 4 Operation Enable Bit Simultaneous Control Channel Select */

#define R_GPT_GTSECSR_SECSEL5                     (1 << 5)  /* Channel 5 Operation Enable Bit Simultaneous Control Channel Select */

#define R_GPT_GTSECSR_SECSEL6                     (1 << 6)  /* Channel 6 Operation Enable Bit Simultaneous Control Channel Select */

#define R_GPT_GTSECSR_SECSEL7                     (1 << 7)  /* Channel 7 Operation Enable Bit Simultaneous Control Channel Select */

#define R_GPT_GTSECSR_SECSEL8                     (1 << 8)  /* Channel 8 Operation Enable Bit Simultaneous Control Channel Select */

#define R_GPT_GTSECSR_SECSEL9                     (1 << 9)  /* Channel 9 Operation Enable Bit Simultaneous Control Channel Select */

/* GTSECR Register bit definitions */
#define R_GPT_GTSECR_SBDCE                        (1 << 0)  /* GTCCR Register Buffer Operation Simultaneous Enable */

#define R_GPT_GTSECR_SBDPE                        (1 << 1)  /* GTPR Register Buffer Operation Simultaneous Enable */

#define R_GPT_GTSECR_SBDAE                        (1 << 2)  /* GTADTR Register Buffer Operation Simultaneous Enable */

#define R_GPT_GTSECR_SBDDE                        (1 << 3)  /* GTDV Register Buffer Operation Simultaneous Enable */

#define R_GPT_GTSECR_SBDCD                        (1 << 8)  /* GTCCR Register Buffer Operation Simultaneous Disable */

#define R_GPT_GTSECR_SBDPD                        (1 << 9)  /* GTPR Register Buffer Operation Simultaneous Disable */

#define R_GPT_GTSECR_SBDAD                        (1 << 10)  /* GTADTR Register Buffer Operation Simultaneous Disable */

#define R_GPT_GTSECR_SBDDD                        (1 << 11)  /* GTDV Register Buffer Operation Simultaneous Disable */

#define R_GPT_GTSECR_SPCE                         (1 << 16)  /* Period Count Function Simultaneous Enable */

#define R_GPT_GTSECR_SSCE                         (1 << 17)  /* Synchronous Set/Clear Simultaneous Enable */

#define R_GPT_GTSECR_SPCD                         (1 << 24)  /* Period Count Function Simultaneous Disable */

#define R_GPT_GTSECR_SSCD                         (1 << 25)  /* Synchronous Set/Clear Simultaneous Disable */

/* GTBER2 Register bit definitions */
#define R_GPT_GTBER2_CCTCA                        (1 << 0)  /* Counter Clear Source GTCCRA Register Buffer Transfer Disable */

#define R_GPT_GTBER2_CCTCB                        (1 << 1)  /* Counter Clear Source GTCCRB Register Buffer Transfer Disable */

#define R_GPT_GTBER2_CCTPR                        (1 << 2)  /* Counter Clear Source GTPR Register Buffer Transfer Disable */

#define R_GPT_GTBER2_CCTADA                       (1 << 3)  /* Counter Clear Source GTADTRA Register Buffer Transfer Disable */

#define R_GPT_GTBER2_CCTADB                       (1 << 4)  /* Counter Clear Source GTADTRB Register Buffer Transfer Disable */

#define R_GPT_GTBER2_CCTDV                        (1 << 5)  /* Counter Clear Source GTDVU/GTDVD Register Buffer Transfer Disable */

#define R_GPT_GTBER2_CMTCA_SHIFT                  (8)  /* Compare Match Source GTCCRA Register Buffer Transfer Enable */
#define R_GPT_GTBER2_CMTCA_MASK                   0x300
#  define R_GPT_GTBER2_CMTCA_0X00                         (0 << R_GPT_GTBER2_CMTCA_SHIFT)  /* Disable GTCCRA register Buffer Transfer by compare match of GTCCRA register
                and GTCCRB register. */
#  define R_GPT_GTBER2_CMTCA_0X01                         (1 << R_GPT_GTBER2_CMTCA_SHIFT)  /* Enable GTCCRA register Buffer Transfer by compare match of GTCCRA register. */
#  define R_GPT_GTBER2_CMTCA_0X02                         (2 << R_GPT_GTBER2_CMTCA_SHIFT)  /* Enable GTCCRA register Buffer Transfer by compare match of GTCCRB register. */
#  define R_GPT_GTBER2_CMTCA_0X03                         (3 << R_GPT_GTBER2_CMTCA_SHIFT)  /* Enable GTCCRA register Buffer Transfer by compare match of GTCCRA register
                and GTCCRB register. */

#define R_GPT_GTBER2_CMTCB_SHIFT                  (10)  /* Compare Match Source GTCCRB Register Buffer Transfer Enable */
#define R_GPT_GTBER2_CMTCB_MASK                   0xc00
#  define R_GPT_GTBER2_CMTCB_0X00                         (0 << R_GPT_GTBER2_CMTCB_SHIFT)  /* Disable GTCCRB register Buffer Transfer by compare match of GTCCRA register
                and GTCCRB register. */
#  define R_GPT_GTBER2_CMTCB_0X01                         (1 << R_GPT_GTBER2_CMTCB_SHIFT)  /* Enable GTCCRB register Buffer Transfer by compare match of GTCCRA register. */
#  define R_GPT_GTBER2_CMTCB_0X02                         (2 << R_GPT_GTBER2_CMTCB_SHIFT)  /* Enable GTCCRB register Buffer Transfer by compare match of GTCCRB register. */
#  define R_GPT_GTBER2_CMTCB_0X03                         (3 << R_GPT_GTBER2_CMTCB_SHIFT)  /* Enable GTCCRB register Buffer Transfer by compare match of GTCCRA register
                and GTCCRB register. */

#define R_GPT_GTBER2_CMTADA                       (1 << 13)  /* Compare Match Source GTADTRA Register Buffer Transfer Enable */

#define R_GPT_GTBER2_CMTADB                       (1 << 14)  /* Compare Match Source GTADTRA Register Buffer Transfer Enable */

#define R_GPT_GTBER2_CPTCA                        (1 << 16)  /* Overflow/Underflow Source GTCCRA Register Buffer Transfer Disable */

#define R_GPT_GTBER2_CPTCB                        (1 << 17)  /* Overflow/Underflow Source GTCCRB Register Buffer Transfer Disable */

#define R_GPT_GTBER2_CPTPR                        (1 << 18)  /* Overflow/Underflow Source GTPR Register Buffer Transfer Disable */

#define R_GPT_GTBER2_CPTADA                       (1 << 19)  /* Overflow/Underflow Source GTADTRA Register Buffer Transfer Disable */

#define R_GPT_GTBER2_CPTADB                       (1 << 20)  /* Overflow/Underflow Source GTADTRB Register Buffer Transfer Disable */

#define R_GPT_GTBER2_CPTDV                        (1 << 21)  /* Overflow/Underflow Source GTDVU/GTDVD Register Buffer Transfer Disable */

#define R_GPT_GTBER2_CP3DB                        (1 << 24)  /* Complementary PWM mode 3,4 Double Buffer select */

#define R_GPT_GTBER2_CPBTD                        (1 << 25)  /* Complementary PWM mode Buffer Transfer Disable */

#define R_GPT_GTBER2_OLTTA_SHIFT                  (26)  /* GTIOCnA Output Level Buffer Transfer Timing Select */
#define R_GPT_GTBER2_OLTTA_MASK                   0xc000000
#  define R_GPT_GTBER2_OLTTA_0X00                         (0 << R_GPT_GTBER2_OLTTA_SHIFT)  /* No transfer */
#  define R_GPT_GTBER2_OLTTA_0X01                         (1 << R_GPT_GTBER2_OLTTA_SHIFT)  /* Triangle waves, complementary PWM mode: Transfer at crest
                Saw waves: Transfer at the end of period */
#  define R_GPT_GTBER2_OLTTA_0X02                         (2 << R_GPT_GTBER2_OLTTA_SHIFT)  /* Triangle waves, complementary PWM mode: Transfer at trough
                Saw waves: Transfer by compare match of GTCCRA register */
#  define R_GPT_GTBER2_OLTTA_0X03                         (3 << R_GPT_GTBER2_OLTTA_SHIFT)  /* Triangle waves, complementary PWM mode: Transfer at both crest and trough
                Saw waves: Setting prohibited */

#define R_GPT_GTBER2_OLTTB_SHIFT                  (28)  /* GTIOCnB Output Level Buffer Transfer Timing Select */
#define R_GPT_GTBER2_OLTTB_MASK                   0x30000000
#  define R_GPT_GTBER2_OLTTB_0X00                         (0 << R_GPT_GTBER2_OLTTB_SHIFT)  /* No transfer */
#  define R_GPT_GTBER2_OLTTB_0X01                         (1 << R_GPT_GTBER2_OLTTB_SHIFT)  /* Triangle waves, complementary PWM mode: Transfer at crest
                Saw waves: Transfer at the end of period */
#  define R_GPT_GTBER2_OLTTB_0X02                         (2 << R_GPT_GTBER2_OLTTB_SHIFT)  /* Triangle waves, complementary PWM mode: Transfer at trough
                Saw waves: Transfer by compare match of GTCCRB register */
#  define R_GPT_GTBER2_OLTTB_0X03                         (3 << R_GPT_GTBER2_OLTTB_SHIFT)  /* Triangle waves, complementary PWM mode: Transfer at both crest and trough
                Saw waves: Setting prohibited */

/* GTOLBR Register bit definitions */
#define R_GPT_GTOLBR_GTIOAB_SHIFT                 (0)  /* GTIOA buffer bits */
#define R_GPT_GTOLBR_GTIOAB_MASK                  0x1f

#define R_GPT_GTOLBR_GTIOBB_SHIFT                 (16)  /* GTIOBB buffer bits */
#define R_GPT_GTOLBR_GTIOBB_MASK                  0x1f0000

/* GTICCR Register bit definitions */
#define R_GPT_GTICCR_ICAFA                        (1 << 0)  /* Forwarding GTCCRA register Compare Match/Input Capture to Other Channel GTCCRA
            Input Capture Source Enable */

#define R_GPT_GTICCR_ICAFB                        (1 << 1)  /* Forwarding GTCCRB register Compare Match/Input Capture to Other Channel GTCCRA
            Input Capture Source Enable */

#define R_GPT_GTICCR_ICAFC                        (1 << 2)  /* Forwarding GTCCRC register Compare Match Capture to Other Channel GTCCRA
            Input Capture Source Enable */

#define R_GPT_GTICCR_ICAFD                        (1 << 3)  /* Forwarding GTCCRD register Compare Match Capture to Other Channel GTCCRA
            Input Capture Source Enable */

#define R_GPT_GTICCR_ICAFE                        (1 << 4)  /* Forwarding GTCCRE register Compare Match Capture to Other Channel GTCCRA
            Input Capture Source Enable */

#define R_GPT_GTICCR_ICAFF                        (1 << 5)  /* Forwarding GTCCRF register Compare Match Capture to Other Channel GTCCRA
            Input Capture Source Enable */

#define R_GPT_GTICCR_ICAFPO                       (1 << 6)  /* Forwarding Overflow to Other Channel GTCCRA Input Capture Source Enable */

#define R_GPT_GTICCR_ICAFPU                       (1 << 7)  /* Forwarding Underflow to Other Channel GTCCRA Input Capture Source Enable */

#define R_GPT_GTICCR_ICACLK                       (1 << 8)  /* Forwarding Count Clock to Other Channel GTCCRA Input Capture Source Enable */

#define R_GPT_GTICCR_ICAGRP_SHIFT                 (14)  /* GTCCRA Input Capture Group Select */
#define R_GPT_GTICCR_ICAGRP_MASK                  0xc000
#  define R_GPT_GTICCR_ICAGRP_0X00                        (0 << R_GPT_GTICCR_ICAGRP_SHIFT)  /* Select group A */
#  define R_GPT_GTICCR_ICAGRP_0X01                        (1 << R_GPT_GTICCR_ICAGRP_SHIFT)  /* Select group B */
#  define R_GPT_GTICCR_ICAGRP_0X02                        (2 << R_GPT_GTICCR_ICAGRP_SHIFT)  /* Select group C */
#  define R_GPT_GTICCR_ICAGRP_0X03                        (3 << R_GPT_GTICCR_ICAGRP_SHIFT)  /* Select group D */

#define R_GPT_GTICCR_ICBFA                        (1 << 16)  /* Forwarding GTCCRA register Compare Match/Input Capture to Other Channel GTCCRB
            Input Capture Source Enable */

#define R_GPT_GTICCR_ICBFB                        (1 << 17)  /* Forwarding GTCCRB register Compare Match/Input Capture to Other Channel GTCCRB
            Input Capture Source Enable */

#define R_GPT_GTICCR_ICBFC                        (1 << 18)  /* Forwarding GTCCRC register Compare Match Capture to Other Channel GTCCRB
            Input Capture Source Enable */

#define R_GPT_GTICCR_ICBFD                        (1 << 19)  /* Forwarding GTCCRD register Compare Match Capture to Other Channel GTCCRB
            Input Capture Source Enable */

#define R_GPT_GTICCR_ICBFE                        (1 << 20)  /* Forwarding GTCCRE register Compare Match Capture to Other Channel GTCCRb
            Input Capture Source Enable */

#define R_GPT_GTICCR_ICBFF                        (1 << 21)  /* Forwarding GTCCRF register Compare Match Capture to Other Channel GTCCRB
            Input Capture Source Enable */

#define R_GPT_GTICCR_ICBFPO                       (1 << 22)  /* Forwarding Overflow to Other Channel GTCCRB Input Capture Source Enable */

#define R_GPT_GTICCR_ICBFPU                       (1 << 23)  /* Forwarding Underflow to Other Channel GTCCRB Input Capture Source Enable */

#define R_GPT_GTICCR_ICBCLK                       (1 << 24)  /* Forwarding Count Clock to Other Channel GTCCRB Input Capture Source Enable */

#define R_GPT_GTICCR_ICBGRP_SHIFT                 (30)  /* GTCCRB Input Capture Group Select */
#define R_GPT_GTICCR_ICBGRP_MASK                  0xc0000000
#  define R_GPT_GTICCR_ICBGRP_0X00                        (0 << R_GPT_GTICCR_ICBGRP_SHIFT)  /* Select group A */
#  define R_GPT_GTICCR_ICBGRP_0X01                        (1 << R_GPT_GTICCR_ICBGRP_SHIFT)  /* Select group B */
#  define R_GPT_GTICCR_ICBGRP_0X02                        (2 << R_GPT_GTICCR_ICBGRP_SHIFT)  /* Select group C */
#  define R_GPT_GTICCR_ICBGRP_0X03                        (3 << R_GPT_GTICCR_ICBGRP_SHIFT)  /* Select group D */


/* Maximum number of channels */

#define GPT_MAX_CHANNELS    14

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_GPT_H */
