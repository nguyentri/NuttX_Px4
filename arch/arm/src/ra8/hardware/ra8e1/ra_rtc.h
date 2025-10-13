/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8e1/ra_rtc.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_RTC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_RTC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* RTC Base Address */
#ifndef R_RTC_BASE
#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)
#define R_RTC_BASE           0x40202000
#else
#define R_RTC_BASE           0x50202000
#endif
#endif

/* RTC Register Offsets */

#define R_RTC_R64CNT_OFFSET                       0x00000000  /* 64-Hz Counter */
/* BCNT%s Registers (0-3) */
#define R_RTC_BCNT_OFFSET(m)                      (0x00000002 + ((m) * 0x00000002))  /* Binary Counter %s */
#define R_RTC_RSECCNT_OFFSET                      0x00000002  /* Second Counter (in Calendar Count Mode) */
#define R_RTC_RMINCNT_OFFSET                      0x00000004  /* Minute Counter (in Calendar Count Mode) */
#define R_RTC_RHRCNT_OFFSET                       0x00000006  /* Hour Counter (in Calendar Count Mode) */
#define R_RTC_RWKCNT_OFFSET                       0x00000008  /* Day-of-Week Counter (in Calendar Count Mode) */
#define R_RTC_RDAYCNT_OFFSET                      0x0000000a  /* Day Counter */
#define R_RTC_RMONCNT_OFFSET                      0x0000000c  /* Month Counter */
#define R_RTC_RYRCNT_OFFSET                       0x0000000e  /* Year Counter */
/* BCNT%sAR Registers (0-3) */
#define R_RTC_BCNTAR_OFFSET(m)                    (0x00000010 + ((m) * 0x00000002))  /* Binary Counter %s Alarm Register */
#define R_RTC_RSECAR_OFFSET                       0x00000010  /* Second Alarm Register (in Calendar Count Mode) */
#define R_RTC_RMINAR_OFFSET                       0x00000012  /* Minute Alarm Register (in Calendar Count Mode) */
#define R_RTC_RHRAR_OFFSET                        0x00000014  /* Hour Alarm Register (in Calendar Count Mode) */
#define R_RTC_RWKAR_OFFSET                        0x00000016  /* Day-of-Week Alarm Register (in Calendar Count Mode) */
/* BCNT%sAER Registers (0-3) */
#define R_RTC_BCNTAER_OFFSET(m)                   (0x00000018 + ((m) * 0x00000002))  /* Binary Counter %s Alarm Enable Register */
#define R_RTC_RDAYAR_OFFSET                       0x00000018  /* Date Alarm Register (in Calendar Count Mode) */
#define R_RTC_RMONAR_OFFSET                       0x0000001a  /* Month Alarm Register (in Calendar Count Mode) */
#define R_RTC_RYRAR_OFFSET                        0x0000001c  /* Year Alarm Register (in Calendar Count Mode) */
#define R_RTC_RYRAREN_OFFSET                      0x0000001e  /* Year Alarm Enable Register (in Calendar Count Mode) */
#define R_RTC_RCR1_OFFSET                         0x00000022  /* RTC Control Register 1 */
#define R_RTC_RCR2_OFFSET                         0x00000024  /* RTC Control Register 2 (in Calendar Count Mode) */
#define R_RTC_RCR2_BCNT_OFFSET                    0x00000024  /* RTC Control Register 2 (in Binary Count Mode) */
#define R_RTC_RCR4_OFFSET                         0x00000028  /* RTC Control Register 4 */
#define R_RTC_RFRH_OFFSET                         0x0000002a  /* Frequency Register H */
#define R_RTC_RFRL_OFFSET                         0x0000002c  /* Frequency Register L */
#define R_RTC_RADJ_OFFSET                         0x0000002e  /* Time Error Adjustment Register */
/* RTCCR%s Registers (0-2) */
#define R_RTC_RTCCR_OFFSET(m)                     (0x00000040 + ((m) * 0x00000002))  /* Time Capture Control Register %s */
/* BCNT0CP%s Registers (0-2) */
#define R_RTC_BCNT0CP_OFFSET(m)                   (0x00000052 + ((m) * 0x00000010))  /* BCNT0 Capture Register %s */
/* RSECCP%s Registers (0-2) */
#define R_RTC_RSECCP_OFFSET(m)                    (0x00000052 + ((m) * 0x00000010))  /* Second Capture Register %s */
/* BCNT1CP%s Registers (0-2) */
#define R_RTC_BCNT1CP_OFFSET(m)                   (0x00000054 + ((m) * 0x00000010))  /* BCNT1 Capture Register %s */
/* RMINCP%s Registers (0-2) */
#define R_RTC_RMINCP_OFFSET(m)                    (0x00000054 + ((m) * 0x00000010))  /* Minute Capture Register %s */
/* BCNT2CP%s Registers (0-2) */
#define R_RTC_BCNT2CP_OFFSET(m)                   (0x00000056 + ((m) * 0x00000010))  /* BCNT2 Capture Register %s */
/* RHRCP%s Registers (0-2) */
#define R_RTC_RHRCP_OFFSET(m)                     (0x00000056 + ((m) * 0x00000010))  /* Hour Capture Register %s */
/* BCNT3CP%s Registers (0-2) */
#define R_RTC_BCNT3CP_OFFSET(m)                   (0x0000005a + ((m) * 0x00000010))  /* BCNT3 Capture Register %s */
/* RDAYCP%s Registers (0-2) */
#define R_RTC_RDAYCP_OFFSET(m)                    (0x0000005a + ((m) * 0x00000010))  /* Date Capture Register %s */
/* RMONCP%s Registers (0-2) */
#define R_RTC_RMONCP_OFFSET(m)                    (0x0000005c + ((m) * 0x00000010))  /* Month Capture Register %s */

/* RTC Register Addresses */

#define R_RTC_R64CNT                              (R_RTC_BASE + R_RTC_R64CNT_OFFSET)
#define R_RTC_BCNT(m)                             (R_RTC_BASE + R_RTC_BCNT_OFFSET(m))
#define R_RTC_RSECCNT                             (R_RTC_BASE + R_RTC_RSECCNT_OFFSET)
#define R_RTC_RMINCNT                             (R_RTC_BASE + R_RTC_RMINCNT_OFFSET)
#define R_RTC_RHRCNT                              (R_RTC_BASE + R_RTC_RHRCNT_OFFSET)
#define R_RTC_RWKCNT                              (R_RTC_BASE + R_RTC_RWKCNT_OFFSET)
#define R_RTC_RDAYCNT                             (R_RTC_BASE + R_RTC_RDAYCNT_OFFSET)
#define R_RTC_RMONCNT                             (R_RTC_BASE + R_RTC_RMONCNT_OFFSET)
#define R_RTC_RYRCNT                              (R_RTC_BASE + R_RTC_RYRCNT_OFFSET)
#define R_RTC_BCNTAR(m)                           (R_RTC_BASE + R_RTC_BCNTAR_OFFSET(m))
#define R_RTC_RSECAR                              (R_RTC_BASE + R_RTC_RSECAR_OFFSET)
#define R_RTC_RMINAR                              (R_RTC_BASE + R_RTC_RMINAR_OFFSET)
#define R_RTC_RHRAR                               (R_RTC_BASE + R_RTC_RHRAR_OFFSET)
#define R_RTC_RWKAR                               (R_RTC_BASE + R_RTC_RWKAR_OFFSET)
#define R_RTC_BCNTAER(m)                          (R_RTC_BASE + R_RTC_BCNTAER_OFFSET(m))
#define R_RTC_RDAYAR                              (R_RTC_BASE + R_RTC_RDAYAR_OFFSET)
#define R_RTC_RMONAR                              (R_RTC_BASE + R_RTC_RMONAR_OFFSET)
#define R_RTC_RYRAR                               (R_RTC_BASE + R_RTC_RYRAR_OFFSET)
#define R_RTC_RYRAREN                             (R_RTC_BASE + R_RTC_RYRAREN_OFFSET)
#define R_RTC_RCR1                                (R_RTC_BASE + R_RTC_RCR1_OFFSET)
#define R_RTC_RCR2                                (R_RTC_BASE + R_RTC_RCR2_OFFSET)
#define R_RTC_RCR2_BCNT                           (R_RTC_BASE + R_RTC_RCR2_BCNT_OFFSET)
#define R_RTC_RCR4                                (R_RTC_BASE + R_RTC_RCR4_OFFSET)
#define R_RTC_RFRH                                (R_RTC_BASE + R_RTC_RFRH_OFFSET)
#define R_RTC_RFRL                                (R_RTC_BASE + R_RTC_RFRL_OFFSET)
#define R_RTC_RADJ                                (R_RTC_BASE + R_RTC_RADJ_OFFSET)
#define R_RTC_RTCCR(m)                            (R_RTC_BASE + R_RTC_RTCCR_OFFSET(m))
#define R_RTC_BCNT0CP(m)                          (R_RTC_BASE + R_RTC_BCNT0CP_OFFSET(m))
#define R_RTC_RSECCP(m)                           (R_RTC_BASE + R_RTC_RSECCP_OFFSET(m))
#define R_RTC_BCNT1CP(m)                          (R_RTC_BASE + R_RTC_BCNT1CP_OFFSET(m))
#define R_RTC_RMINCP(m)                           (R_RTC_BASE + R_RTC_RMINCP_OFFSET(m))
#define R_RTC_BCNT2CP(m)                          (R_RTC_BASE + R_RTC_BCNT2CP_OFFSET(m))
#define R_RTC_RHRCP(m)                            (R_RTC_BASE + R_RTC_RHRCP_OFFSET(m))
#define R_RTC_BCNT3CP(m)                          (R_RTC_BASE + R_RTC_BCNT3CP_OFFSET(m))
#define R_RTC_RDAYCP(m)                           (R_RTC_BASE + R_RTC_RDAYCP_OFFSET(m))
#define R_RTC_RMONCP(m)                           (R_RTC_BASE + R_RTC_RMONCP_OFFSET(m))

/* Register bit definitions */
/* R64CNT Register bit definitions */
#define R_RTC_R64CNT_F64HZ                        (1 << 0)  /* 64-Hz Flag */

#define R_RTC_R64CNT_F32HZ                        (1 << 1)  /* 32-Hz Flag */

#define R_RTC_R64CNT_F16HZ                        (1 << 2)  /* 16-Hz Flag */

#define R_RTC_R64CNT_F8HZ                         (1 << 3)  /* 8-Hz Flag */

#define R_RTC_R64CNT_F4HZ                         (1 << 4)  /* 4-Hz Flag */

#define R_RTC_R64CNT_F2HZ                         (1 << 5)  /* 2-Hz Flag */

#define R_RTC_R64CNT_F1HZ                         (1 << 6)  /* 1-Hz Flag */

#define R_RTC_R64CNT_R64OVF                       (1 << 7)  /* This bit indicates the overflow of F1HZ only when using time error adjustment function inlow-consumption clock mode. */

/* BCNT Register bit definitions */
#define R_RTC_BCNT_BCNT_SHIFT                     (0)  /* Binary Counter */
#define R_RTC_BCNT_BCNT_MASK                      0xff

/* RSECCNT Register bit definitions */
#define R_RTC_RSECCNT_SEC1_SHIFT                  (0)  /* 1-Second Count */
#define R_RTC_RSECCNT_SEC1_MASK                   0xf

#define R_RTC_RSECCNT_SEC10_SHIFT                 (4)  /* 10-Second Count */
#define R_RTC_RSECCNT_SEC10_MASK                  0x70

/* RMINCNT Register bit definitions */
#define R_RTC_RMINCNT_MIN1_SHIFT                  (0)  /* 1-Minute Count */
#define R_RTC_RMINCNT_MIN1_MASK                   0xf

#define R_RTC_RMINCNT_MIN10_SHIFT                 (4)  /* 10-Minute Count */
#define R_RTC_RMINCNT_MIN10_MASK                  0x70

/* RHRCNT Register bit definitions */
#define R_RTC_RHRCNT_HR1_SHIFT                    (0)  /* 1-Hour Count */
#define R_RTC_RHRCNT_HR1_MASK                     0xf

#define R_RTC_RHRCNT_HR10_SHIFT                   (4)  /* 10-Hour Count */
#define R_RTC_RHRCNT_HR10_MASK                    0x30

#define R_RTC_RHRCNT_PM                           (1 << 6)  /* AM/PM select for time counter setting. */

/* RWKCNT Register bit definitions */
#define R_RTC_RWKCNT_DAYW_SHIFT                   (0)  /* Day-of-Week Counting */
#define R_RTC_RWKCNT_DAYW_MASK                    0x7
#  define R_RTC_RWKCNT_DAYW_000                           (0 << R_RTC_RWKCNT_DAYW_SHIFT)  /* Sunday */
#  define R_RTC_RWKCNT_DAYW_001                           (1 << R_RTC_RWKCNT_DAYW_SHIFT)  /* Monday */
#  define R_RTC_RWKCNT_DAYW_010                           (2 << R_RTC_RWKCNT_DAYW_SHIFT)  /* Tuesday */
#  define R_RTC_RWKCNT_DAYW_011                           (3 << R_RTC_RWKCNT_DAYW_SHIFT)  /* Wednesday */
#  define R_RTC_RWKCNT_DAYW_100                           (4 << R_RTC_RWKCNT_DAYW_SHIFT)  /* Thursday */
#  define R_RTC_RWKCNT_DAYW_101                           (5 << R_RTC_RWKCNT_DAYW_SHIFT)  /* Friday */
#  define R_RTC_RWKCNT_DAYW_110                           (6 << R_RTC_RWKCNT_DAYW_SHIFT)  /* Saturday */
#  define R_RTC_RWKCNT_DAYW_111                           (7 << R_RTC_RWKCNT_DAYW_SHIFT)  /* Setting prohibited */

/* RDAYCNT Register bit definitions */
#define R_RTC_RDAYCNT_DATE1_SHIFT                 (0)  /* 1-Day Count */
#define R_RTC_RDAYCNT_DATE1_MASK                  0xf

#define R_RTC_RDAYCNT_DATE10_SHIFT                (4)  /* 10-Day Count */
#define R_RTC_RDAYCNT_DATE10_MASK                 0x30

/* RMONCNT Register bit definitions */
#define R_RTC_RMONCNT_MON1_SHIFT                  (0)  /* 1-Month Count */
#define R_RTC_RMONCNT_MON1_MASK                   0xf

#define R_RTC_RMONCNT_MON10                       (1 << 4)  /* 10-Month Count */

/* RYRCNT Register bit definitions */
#define R_RTC_RYRCNT_YR1_SHIFT                    (0)  /* 1-Year Count */
#define R_RTC_RYRCNT_YR1_MASK                     0xf

#define R_RTC_RYRCNT_YR10_SHIFT                   (4)  /* 10-Year Count */
#define R_RTC_RYRCNT_YR10_MASK                    0xf0

/* BCNTAR Register bit definitions */
#define R_RTC_BCNTAR_BCNTAR_SHIFT                 (0)  /* Alarm register associated with the 32-bit binary counter */
#define R_RTC_BCNTAR_BCNTAR_MASK                  0xff

/* RSECAR Register bit definitions */
#define R_RTC_RSECAR_SEC1_SHIFT                   (0)  /* 1 Second */
#define R_RTC_RSECAR_SEC1_MASK                    0xf

#define R_RTC_RSECAR_SEC10_SHIFT                  (4)  /* 10 Seconds */
#define R_RTC_RSECAR_SEC10_MASK                   0x70

#define R_RTC_RSECAR_ENB                          (1 << 7)  /* ENB */

/* RMINAR Register bit definitions */
#define R_RTC_RMINAR_MIN1_SHIFT                   (0)  /* 1 Minute */
#define R_RTC_RMINAR_MIN1_MASK                    0xf

#define R_RTC_RMINAR_MIN10_SHIFT                  (4)  /* 10 Minutes */
#define R_RTC_RMINAR_MIN10_MASK                   0x70

#define R_RTC_RMINAR_ENB                          (1 << 7)  /* ENB */

/* RHRAR Register bit definitions */
#define R_RTC_RHRAR_HR1_SHIFT                     (0)  /* 1 Hour */
#define R_RTC_RHRAR_HR1_MASK                      0xf

#define R_RTC_RHRAR_HR10_SHIFT                    (4)  /* 10 Hours */
#define R_RTC_RHRAR_HR10_MASK                     0x30

#define R_RTC_RHRAR_PM                            (1 << 6)  /* AM/PM select for alarm setting. */

#define R_RTC_RHRAR_ENB                           (1 << 7)  /* ENB */

/* RWKAR Register bit definitions */
#define R_RTC_RWKAR_DAYW_SHIFT                    (0)  /* Day-of-Week Setting */
#define R_RTC_RWKAR_DAYW_MASK                     0x7
#  define R_RTC_RWKAR_DAYW_000                            (0 << R_RTC_RWKAR_DAYW_SHIFT)  /* Sunday */
#  define R_RTC_RWKAR_DAYW_001                            (1 << R_RTC_RWKAR_DAYW_SHIFT)  /* Monday */
#  define R_RTC_RWKAR_DAYW_010                            (2 << R_RTC_RWKAR_DAYW_SHIFT)  /* Tuesday */
#  define R_RTC_RWKAR_DAYW_011                            (3 << R_RTC_RWKAR_DAYW_SHIFT)  /* Wednesday */
#  define R_RTC_RWKAR_DAYW_100                            (4 << R_RTC_RWKAR_DAYW_SHIFT)  /* Thursday */
#  define R_RTC_RWKAR_DAYW_101                            (5 << R_RTC_RWKAR_DAYW_SHIFT)  /* Friday */
#  define R_RTC_RWKAR_DAYW_110                            (6 << R_RTC_RWKAR_DAYW_SHIFT)  /* Saturday */
#  define R_RTC_RWKAR_DAYW_111                            (7 << R_RTC_RWKAR_DAYW_SHIFT)  /* Setting prohibited */

#define R_RTC_RWKAR_ENB                           (1 << 7)  /* ENB */

/* BCNTAER Register bit definitions */
#define R_RTC_BCNTAER_ENB_SHIFT                   (0)  /* Setting the alarm enable associated with the 32-bit binary counter */
#define R_RTC_BCNTAER_ENB_MASK                    0xff

/* RDAYAR Register bit definitions */
#define R_RTC_RDAYAR_DATE1_SHIFT                  (0)  /* 1 Day */
#define R_RTC_RDAYAR_DATE1_MASK                   0xf

#define R_RTC_RDAYAR_DATE10_SHIFT                 (4)  /* 10 Days */
#define R_RTC_RDAYAR_DATE10_MASK                  0x30

#define R_RTC_RDAYAR_ENB                          (1 << 7)  /* ENB */

/* RMONAR Register bit definitions */
#define R_RTC_RMONAR_MON1_SHIFT                   (0)  /* 1 Month */
#define R_RTC_RMONAR_MON1_MASK                    0xf

#define R_RTC_RMONAR_MON10                        (1 << 4)  /* 10 Months */

#define R_RTC_RMONAR_ENB                          (1 << 7)  /* ENB */

/* RYRAR Register bit definitions */
#define R_RTC_RYRAR_YR1_SHIFT                     (0)  /* 1 Year */
#define R_RTC_RYRAR_YR1_MASK                      0xf

#define R_RTC_RYRAR_YR10_SHIFT                    (4)  /* 10 Years */
#define R_RTC_RYRAR_YR10_MASK                     0xf0

/* RYRAREN Register bit definitions */
#define R_RTC_RYRAREN_ENB                         (1 << 7)  /* ENB */

/* RCR1 Register bit definitions */
#define R_RTC_RCR1_AIE                            (1 << 0)  /* Alarm Interrupt Enable */

#define R_RTC_RCR1_CIE                            (1 << 1)  /* Carry Interrupt Enable */

#define R_RTC_RCR1_PIE                            (1 << 2)  /* Periodic Interrupt Enable */

#define R_RTC_RCR1_RTCOS                          (1 << 3)  /* RTCOUT Output Select */

#define R_RTC_RCR1_PES_SHIFT                      (4)  /* Periodic Interrupt Select */
#define R_RTC_RCR1_PES_MASK                       0xf0
#  define R_RTC_RCR1_PES_0X6                              (6 << R_RTC_RCR1_PES_SHIFT)  /* Generate periodic interrupt every 1/256 second */
#  define R_RTC_RCR1_PES_0X7                              (7 << R_RTC_RCR1_PES_SHIFT)  /* Generate periodic interrupt every 1/128 second */
#  define R_RTC_RCR1_PES_0X8                              (8 << R_RTC_RCR1_PES_SHIFT)  /* Generate periodic interrupt every 1/64 second */
#  define R_RTC_RCR1_PES_0X9                              (9 << R_RTC_RCR1_PES_SHIFT)  /* Generate periodic interrupt every 1/32 second */
#  define R_RTC_RCR1_PES_0XA                              (10 << R_RTC_RCR1_PES_SHIFT)  /* Generate periodic interrupt every 1/16 second */
#  define R_RTC_RCR1_PES_0XB                              (11 << R_RTC_RCR1_PES_SHIFT)  /* Generate periodic interrupt every 1/8 second */
#  define R_RTC_RCR1_PES_0XC                              (12 << R_RTC_RCR1_PES_SHIFT)  /* Generate periodic interrupt every 1/4 second */
#  define R_RTC_RCR1_PES_0XD                              (13 << R_RTC_RCR1_PES_SHIFT)  /* Generate periodic interrupt every 1/2 second */
#  define R_RTC_RCR1_PES_0XE                              (14 << R_RTC_RCR1_PES_SHIFT)  /* Generate periodic interrupt every 1 second */
#  define R_RTC_RCR1_PES_0XF                              (15 << R_RTC_RCR1_PES_SHIFT)  /* Generate periodic interrupt every 2 seconds */

/* RCR2 Register bit definitions */
#define R_RTC_RCR2_START                          (1 << 0)  /* Start */

#define R_RTC_RCR2_RESET                          (1 << 1)  /* RTC Software Reset */

#define R_RTC_RCR2_ADJ30                          (1 << 2)  /* 30-Second Adjustment */

#define R_RTC_RCR2_RTCOE                          (1 << 3)  /* RTCOUT Output Enable */

#define R_RTC_RCR2_AADJE                          (1 << 4)  /* Automatic Adjustment Enable */

#define R_RTC_RCR2_AADJP                          (1 << 5)  /* Automatic Adjustment Period Select */

#define R_RTC_RCR2_HR24                           (1 << 6)  /* Hours Mode */

#define R_RTC_RCR2_CNTMD                          (1 << 7)  /* Count Mode Select */

/* RCR2_BCNT Register bit definitions */
#define R_RTC_RCR2_BCNT_START                     (1 << 0)  /* Start */

#define R_RTC_RCR2_BCNT_RESET                     (1 << 1)  /* RTC Software Reset */

#define R_RTC_RCR2_BCNT_RTCOE                     (1 << 3)  /* RTCOUT Output Enable */

#define R_RTC_RCR2_BCNT_AADJE                     (1 << 4)  /* Automatic Adjustment Enable */

#define R_RTC_RCR2_BCNT_AADJP                     (1 << 5)  /* Automatic Adjustment Period Select */

#define R_RTC_RCR2_BCNT_CNTMD                     (1 << 7)  /* Count Mode Select */

/* RCR4 Register bit definitions */
#define R_RTC_RCR4_RCKSEL                         (1 << 0)  /* Count Source Select */

#define R_RTC_RCR4_ROPSEL                         (1 << 7)  /* RTC Operation Mode Select */

/* RFRH Register bit definitions */
#define R_RTC_RFRH_RFC16                          (1 << 0)  /* Write 0 before writing to the RFRL register after a cold start. */

/* RFRL Register bit definitions */
#define R_RTC_RFRL_RFC_SHIFT                      (0)  /* Frequency Comparison Value */
#define R_RTC_RFRL_RFC_MASK                       0xffff

/* RADJ Register bit definitions */
#define R_RTC_RADJ_ADJ_SHIFT                      (0)  /* Adjustment Value */
#define R_RTC_RADJ_ADJ_MASK                       0x3f

#define R_RTC_RADJ_PMADJ_SHIFT                    (6)  /* Plus-Minus */
#define R_RTC_RADJ_PMADJ_MASK                     0xc0
#  define R_RTC_RADJ_PMADJ_00                             (0 << R_RTC_RADJ_PMADJ_SHIFT)  /* Do not perform adjustment. */
#  define R_RTC_RADJ_PMADJ_01                             (1 << R_RTC_RADJ_PMADJ_SHIFT)  /* Adjustment is performed by the addition to the prescaler */
#  define R_RTC_RADJ_PMADJ_10                             (2 << R_RTC_RADJ_PMADJ_SHIFT)  /* Adjustment is performed by the subtraction from the prescaler */
#  define R_RTC_RADJ_PMADJ_11                             (3 << R_RTC_RADJ_PMADJ_SHIFT)  /* Setting prohibited. */

/* RTCCR Register bit definitions */
#define R_RTC_RTCCR_TCCT_SHIFT                    (0)  /* Time Capture Control */
#define R_RTC_RTCCR_TCCT_MASK                     0x3
#  define R_RTC_RTCCR_TCCT_00                             (0 << R_RTC_RTCCR_TCCT_SHIFT)  /* Do not detect events */
#  define R_RTC_RTCCR_TCCT_01                             (1 << R_RTC_RTCCR_TCCT_SHIFT)  /* Detect rising edge */
#  define R_RTC_RTCCR_TCCT_10                             (2 << R_RTC_RTCCR_TCCT_SHIFT)  /* Detect falling edge */
#  define R_RTC_RTCCR_TCCT_11                             (3 << R_RTC_RTCCR_TCCT_SHIFT)  /* Detect both edges */

#define R_RTC_RTCCR_TCST                          (1 << 2)  /* Time Capture Status */

#define R_RTC_RTCCR_TCNF_SHIFT                    (4)  /* Time Capture Noise Filter Control */
#define R_RTC_RTCCR_TCNF_MASK                     0x30
#  define R_RTC_RTCCR_TCNF_00                             (0 << R_RTC_RTCCR_TCNF_SHIFT)  /* Turn noise filter off */
#  define R_RTC_RTCCR_TCNF_01                             (1 << R_RTC_RTCCR_TCNF_SHIFT)  /* Setting prohibited */
#  define R_RTC_RTCCR_TCNF_10                             (2 << R_RTC_RTCCR_TCNF_SHIFT)  /* Turn noise filter on (count source) */
#  define R_RTC_RTCCR_TCNF_11                             (3 << R_RTC_RTCCR_TCNF_SHIFT)  /* Turn noise filter on (count source by divided by 32) */

#define R_RTC_RTCCR_TCEN                          (1 << 7)  /* Time Capture Event Input Pin Enable */

/* RSECCP Register bit definitions */
#define R_RTC_RSECCP_SEC1_SHIFT                   (0)  /* 1-Second Capture */
#define R_RTC_RSECCP_SEC1_MASK                    0xf

#define R_RTC_RSECCP_SEC10_SHIFT                  (4)  /* 10-Second Capture */
#define R_RTC_RSECCP_SEC10_MASK                   0x70

/* RMINCP Register bit definitions */
#define R_RTC_RMINCP_MIN1_SHIFT                   (0)  /* 1-Minute Capture */
#define R_RTC_RMINCP_MIN1_MASK                    0xf

#define R_RTC_RMINCP_MIN10_SHIFT                  (4)  /* 10-Minute Capture */
#define R_RTC_RMINCP_MIN10_MASK                   0x70

/* RHRCP Register bit definitions */
#define R_RTC_RHRCP_HR1_SHIFT                     (0)  /* 1-Hour Capture */
#define R_RTC_RHRCP_HR1_MASK                      0xf

#define R_RTC_RHRCP_HR10_SHIFT                    (4)  /* 10-Hour Capture */
#define R_RTC_RHRCP_HR10_MASK                     0x30

#define R_RTC_RHRCP_PM                            (1 << 6)  /* PM */

/* RDAYCP Register bit definitions */
#define R_RTC_RDAYCP_DATE1_SHIFT                  (0)  /* 1-Day Capture */
#define R_RTC_RDAYCP_DATE1_MASK                   0xf

#define R_RTC_RDAYCP_DATE10_SHIFT                 (4)  /* 10-Day Capture */
#define R_RTC_RDAYCP_DATE10_MASK                  0x30

/* RMONCP Register bit definitions */
#define R_RTC_RMONCP_MON1_SHIFT                   (0)  /* 1-Month Capture */
#define R_RTC_RMONCP_MON1_MASK                    0xf

#define R_RTC_RMONCP_MON10                        (1 << 4)  /* 10-Month Capture */


/* Maximum number of channels */

#define RTC_MAX_CHANNELS    4

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8E1_RTC_H */
