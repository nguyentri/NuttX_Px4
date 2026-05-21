/****************************************************************************
 * arch/arm/src/ra8/hardware/ra8p1/ra_rtc.h
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

#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_RTC_H
#define __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_RTC_H

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
#define R_RTC_BCNT0_OFFSET                        0x00000002  /* Binary Counter 0 */
#define R_RTC_RSECCNT_OFFSET                      0x00000002  /* Second Counter */
#define R_RTC_BCNT1_OFFSET                        0x00000004  /* Binary Counter 1 */
#define R_RTC_RMINCNT_OFFSET                      0x00000004  /* Minute Counter */
#define R_RTC_BCNT2_OFFSET                        0x00000006  /* Binary Counter 2 */
#define R_RTC_RHRCNT_OFFSET                       0x00000006  /* Hour Counter */
#define R_RTC_BCNT3_OFFSET                        0x00000008  /* Binary Counter 3 */
#define R_RTC_RWKCNT_OFFSET                       0x00000008  /* Day-of-Week Counter */
#define R_RTC_RDAYCNT_OFFSET                      0x0000000a  /* Day Counter */
#define R_RTC_RMONCNT_OFFSET                      0x0000000c  /* Month Counter */
#define R_RTC_RYRCNT_OFFSET                       0x0000000e  /* Year Counter */
#define R_RTC_BCNT0AR_OFFSET                      0x00000010  /* Binary Counter 0 Alarm Register */
#define R_RTC_RSECAR_OFFSET                       0x00000010  /* Second Alarm Register */
#define R_RTC_BCNT1AR_OFFSET                      0x00000012  /* Binary Counter 1 Alarm Register */
#define R_RTC_RMINAR_OFFSET                       0x00000012  /* Minute Alarm Register */
#define R_RTC_BCNT2AR_OFFSET                      0x00000014  /* Binary Counter 2 Alarm Register */
#define R_RTC_RHRAR_OFFSET                        0x00000014  /* Hour Alarm Register */
#define R_RTC_BCNT3AR_OFFSET                      0x00000016  /* Binary Counter 3 Alarm Register */
#define R_RTC_RWKAR_OFFSET                        0x00000016  /* Day-of-Week Alarm Register */
#define R_RTC_BCNT0AER_OFFSET                     0x00000018  /* Binary Counter 0 Alarm Enable Register */
#define R_RTC_RDAYAR_OFFSET                       0x00000018  /* Date Alarm Register */
#define R_RTC_BCNT1AER_OFFSET                     0x0000001a  /* Binary Counter 1 Alarm Enable Register */
#define R_RTC_RMONAR_OFFSET                       0x0000001a  /* Month Alarm Register */
#define R_RTC_BCNT2AER_OFFSET                     0x0000001c  /* Binary Counter 2 Alarm Enable Register */
#define R_RTC_RYRAR_OFFSET                        0x0000001c  /* Year Alarm Register */
#define R_RTC_BCNT3AER_OFFSET                     0x0000001e  /* Binary Counter 3 Alarm Enable Register */
#define R_RTC_RYRAREN_OFFSET                      0x0000001e  /* Year Alarm Enable Register */
#define R_RTC_RCR1_OFFSET                         0x00000022  /* RTC Control Register 1 */
#define R_RTC_RCR2_OFFSET                         0x00000024  /* RTC Control Register 2 */
#define R_RTC_RCR4_OFFSET                         0x00000028  /* RTC Control Register 4 */
#define R_RTC_RFRH_OFFSET                         0x0000002a  /* Frequency Register H */
#define R_RTC_RFRL_OFFSET                         0x0000002c  /* Frequency Register L */
#define R_RTC_RADJ_OFFSET                         0x0000002e  /* Time Error Adjustment Register */
#define R_RTC_RADJ2_OFFSET                        0x00000030  /* Time Error Adjustment Register 2 */
/* RTCCR[%s] Registers () */
#define R_RTC_RTCCR_OFFSET(m)                     (0x00000040 + ((m) * 0x00000002))  /* Time Capture Control Register */
/* CP[%s] Registers () */
#define R_RTC_CP_OFFSET(m)                        (0x00000050 + ((m) * 0x00000010))  /* Capture registers */

/* RTC Register Addresses */

#define R_RTC_R64CNT                              (R_RTC_BASE + R_RTC_R64CNT_OFFSET)
#define R_RTC_BCNT0                               (R_RTC_BASE + R_RTC_BCNT0_OFFSET)
#define R_RTC_RSECCNT                             (R_RTC_BASE + R_RTC_RSECCNT_OFFSET)
#define R_RTC_BCNT1                               (R_RTC_BASE + R_RTC_BCNT1_OFFSET)
#define R_RTC_RMINCNT                             (R_RTC_BASE + R_RTC_RMINCNT_OFFSET)
#define R_RTC_BCNT2                               (R_RTC_BASE + R_RTC_BCNT2_OFFSET)
#define R_RTC_RHRCNT                              (R_RTC_BASE + R_RTC_RHRCNT_OFFSET)
#define R_RTC_BCNT3                               (R_RTC_BASE + R_RTC_BCNT3_OFFSET)
#define R_RTC_RWKCNT                              (R_RTC_BASE + R_RTC_RWKCNT_OFFSET)
#define R_RTC_RDAYCNT                             (R_RTC_BASE + R_RTC_RDAYCNT_OFFSET)
#define R_RTC_RMONCNT                             (R_RTC_BASE + R_RTC_RMONCNT_OFFSET)
#define R_RTC_RYRCNT                              (R_RTC_BASE + R_RTC_RYRCNT_OFFSET)
#define R_RTC_BCNT0AR                             (R_RTC_BASE + R_RTC_BCNT0AR_OFFSET)
#define R_RTC_RSECAR                              (R_RTC_BASE + R_RTC_RSECAR_OFFSET)
#define R_RTC_BCNT1AR                             (R_RTC_BASE + R_RTC_BCNT1AR_OFFSET)
#define R_RTC_RMINAR                              (R_RTC_BASE + R_RTC_RMINAR_OFFSET)
#define R_RTC_BCNT2AR                             (R_RTC_BASE + R_RTC_BCNT2AR_OFFSET)
#define R_RTC_RHRAR                               (R_RTC_BASE + R_RTC_RHRAR_OFFSET)
#define R_RTC_BCNT3AR                             (R_RTC_BASE + R_RTC_BCNT3AR_OFFSET)
#define R_RTC_RWKAR                               (R_RTC_BASE + R_RTC_RWKAR_OFFSET)
#define R_RTC_BCNT0AER                            (R_RTC_BASE + R_RTC_BCNT0AER_OFFSET)
#define R_RTC_RDAYAR                              (R_RTC_BASE + R_RTC_RDAYAR_OFFSET)
#define R_RTC_BCNT1AER                            (R_RTC_BASE + R_RTC_BCNT1AER_OFFSET)
#define R_RTC_RMONAR                              (R_RTC_BASE + R_RTC_RMONAR_OFFSET)
#define R_RTC_BCNT2AER                            (R_RTC_BASE + R_RTC_BCNT2AER_OFFSET)
#define R_RTC_RYRAR                               (R_RTC_BASE + R_RTC_RYRAR_OFFSET)
#define R_RTC_BCNT3AER                            (R_RTC_BASE + R_RTC_BCNT3AER_OFFSET)
#define R_RTC_RYRAREN                             (R_RTC_BASE + R_RTC_RYRAREN_OFFSET)
#define R_RTC_RCR1                                (R_RTC_BASE + R_RTC_RCR1_OFFSET)
#define R_RTC_RCR2                                (R_RTC_BASE + R_RTC_RCR2_OFFSET)
#define R_RTC_RCR4                                (R_RTC_BASE + R_RTC_RCR4_OFFSET)
#define R_RTC_RFRH                                (R_RTC_BASE + R_RTC_RFRH_OFFSET)
#define R_RTC_RFRL                                (R_RTC_BASE + R_RTC_RFRL_OFFSET)
#define R_RTC_RADJ                                (R_RTC_BASE + R_RTC_RADJ_OFFSET)
#define R_RTC_RADJ2                               (R_RTC_BASE + R_RTC_RADJ2_OFFSET)
#define R_RTC_RTCCR(m)                            (R_RTC_BASE + R_RTC_RTCCR_OFFSET(m))
#define R_RTC_CP(m)                               (R_RTC_BASE + R_RTC_CP_OFFSET(m))

/* Register bit definitions */
/* R64CNT Register bit definitions */
#define R_RTC_R64CNT_R64OVF                       (1 << 7)  /* This bit indicates the overflow of F1HZ only when using time error adjustment function in
low-consumption clock mode. */

#define R_RTC_R64CNT_F_SHZ                        (1 << 0)  /* %sHz Flag */

#define R_RTC_R64CNT_F64HZ                        (1 << 0)  /* 64Hz Flag */

#define R_RTC_R64CNT_F32HZ                        (1 << 1)  /* 32Hz Flag */

#define R_RTC_R64CNT_F16HZ                        (1 << 2)  /* 16Hz Flag */

#define R_RTC_R64CNT_F8HZ                         (1 << 3)  /* 8Hz Flag */

#define R_RTC_R64CNT_F4HZ                         (1 << 4)  /* 4Hz Flag */

#define R_RTC_R64CNT_F2HZ                         (1 << 5)  /* 2Hz Flag */

#define R_RTC_R64CNT_F1HZ                         (1 << 6)  /* 1Hz Flag */

/* BCNT0 Register bit definitions */
#define R_RTC_BCNT0_BCNT0_SHIFT                   (0)  /* The BCNT0 counter is a readable/writable 32-bit binary counter b7 to b0. */
#define R_RTC_BCNT0_BCNT0_MASK                    0xff

/* RSECCNT Register bit definitions */
#define R_RTC_RSECCNT_SEC10_SHIFT                 (4)  /* 10-Second Count Counts from 0 to 5 for 60-second counting. */
#define R_RTC_RSECCNT_SEC10_MASK                  0x70

#define R_RTC_RSECCNT_SEC1_SHIFT                  (0)  /* 1-Second Count Counts from 0 to 9 every second. When a carry is generated, 1 is added to the tens place. */
#define R_RTC_RSECCNT_SEC1_MASK                   0xf

/* BCNT1 Register bit definitions */
#define R_RTC_BCNT1_BCNT1_SHIFT                   (0)  /* The BCNT1 counter is a readable/writable 32-bit binary counter b15 to b8. */
#define R_RTC_BCNT1_BCNT1_MASK                    0xff

/* RMINCNT Register bit definitions */
#define R_RTC_RMINCNT_MIN10_SHIFT                 (4)  /* 10-Minute Count Counts from 0 to 5 for 60-minute counting. */
#define R_RTC_RMINCNT_MIN10_MASK                  0x70

#define R_RTC_RMINCNT_MIN1_SHIFT                  (0)  /* 1-Minute Count Counts from 0 to 9 every minute. When a carry is generated, 1 is added to the tens place. */
#define R_RTC_RMINCNT_MIN1_MASK                   0xf

/* BCNT2 Register bit definitions */
#define R_RTC_BCNT2_BCNT2_SHIFT                   (0)  /* The BCNT2 counter is a readable/writable 32-bit binary counter b23 to b16. */
#define R_RTC_BCNT2_BCNT2_MASK                    0xff

/* RHRCNT Register bit definitions */
#define R_RTC_RHRCNT_PM                           (1 << 6)  /* Time Counter Setting for a.m./p.m. */

#define R_RTC_RHRCNT_HR10_SHIFT                   (4)  /* 10-Hour Count Counts from 0 to 2 once per carry from the ones place. */
#define R_RTC_RHRCNT_HR10_MASK                    0x30

#define R_RTC_RHRCNT_HR1_SHIFT                    (0)  /* 1-Hour Count Counts from 0 to 9 once per hour. When a carry is generated, 1 is added to the tens place. */
#define R_RTC_RHRCNT_HR1_MASK                     0xf

/* BCNT3 Register bit definitions */
#define R_RTC_BCNT3_BCNT3_SHIFT                   (0)  /* The BCNT3 counter is a readable/writable 32-bit binary counter b31 to b24. */
#define R_RTC_BCNT3_BCNT3_MASK                    0xff

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
#  define R_RTC_RWKCNT_DAYW_111                           (7 << R_RTC_RWKCNT_DAYW_SHIFT)  /* Setting Prohibited  */

/* RDAYCNT Register bit definitions */
#define R_RTC_RDAYCNT_DATE10_SHIFT                (4)  /* 10-Day Count Counts from 0 to 3 once per carry from the ones place. */
#define R_RTC_RDAYCNT_DATE10_MASK                 0x30

#define R_RTC_RDAYCNT_DATE1_SHIFT                 (0)  /* 1-Day Count Counts from 0 to 9 once per day. When a carry is generated, 1 is added to the tens place. */
#define R_RTC_RDAYCNT_DATE1_MASK                  0xf

/* RMONCNT Register bit definitions */
#define R_RTC_RMONCNT_MON10                       (1 << 4)  /* 10-Month Count Counts from 0 to 1 once per carry from the ones place. */

#define R_RTC_RMONCNT_MON1_SHIFT                  (0)  /* 1-Month Count Counts from 0 to 9 once per month. When a carry is generated, 1 is added to the tens place. */
#define R_RTC_RMONCNT_MON1_MASK                   0xf

/* RYRCNT Register bit definitions */
#define R_RTC_RYRCNT_YR10_SHIFT                   (4)  /* 10-Year Count Counts from 0 to 9 once per carry from ones place. When a carry is generated in the tens place, 1 is added to the hundreds place. */
#define R_RTC_RYRCNT_YR10_MASK                    0xf0

#define R_RTC_RYRCNT_YR1_SHIFT                    (0)  /* 1-Year Count Counts from 0 to 9 once per year. When a carry is generated, 1 is added to the tens place. */
#define R_RTC_RYRCNT_YR1_MASK                     0xf

/* BCNT0AR Register bit definitions */
#define R_RTC_BCNT0AR_BCNT0AR_SHIFT               (0)  /* he BCNT0AR counter is a readable/writable alarm register corresponding to 32-bit binary counter b7 to b0. */
#define R_RTC_BCNT0AR_BCNT0AR_MASK                0xff

/* RSECAR Register bit definitions */
#define R_RTC_RSECAR_ENB                          (1 << 7)  /* Compare enable */

#define R_RTC_RSECAR_SEC10_SHIFT                  (4)  /* 10-Seconds Value for the tens place of seconds */
#define R_RTC_RSECAR_SEC10_MASK                   0x70

#define R_RTC_RSECAR_SEC1_SHIFT                   (0)  /* 1-Second Value for the ones place of seconds */
#define R_RTC_RSECAR_SEC1_MASK                    0xf

/* BCNT1AR Register bit definitions */
#define R_RTC_BCNT1AR_BCNT1AR_SHIFT               (0)  /* he BCNT1AR counter is a readable/writable alarm register corresponding to 32-bit binary counter b15 to b8. */
#define R_RTC_BCNT1AR_BCNT1AR_MASK                0xff

/* RMINAR Register bit definitions */
#define R_RTC_RMINAR_ENB                          (1 << 7)  /* Compare enable */

#define R_RTC_RMINAR_MIN10_SHIFT                  (4)  /* 10-Minute Count Value for the tens place of minutes */
#define R_RTC_RMINAR_MIN10_MASK                   0x70

#define R_RTC_RMINAR_MIN1_SHIFT                   (0)  /* 1-Minute Count Value for the ones place of minutes */
#define R_RTC_RMINAR_MIN1_MASK                    0xf

/* BCNT2AR Register bit definitions */
#define R_RTC_BCNT2AR_BCNT2AR_SHIFT               (0)  /* The BCNT2AR counter is a readable/writable 32-bit binary counter b23 to b16. */
#define R_RTC_BCNT2AR_BCNT2AR_MASK                0xff

/* RHRAR Register bit definitions */
#define R_RTC_RHRAR_ENB                           (1 << 7)  /* Compare enable */

#define R_RTC_RHRAR_PM                            (1 << 6)  /* Time Counter Setting for a.m./p.m. */

#define R_RTC_RHRAR_HR10_SHIFT                    (4)  /* 10-Hour Count Value for the tens place of hours */
#define R_RTC_RHRAR_HR10_MASK                     0x30

#define R_RTC_RHRAR_HR1_SHIFT                     (0)  /* 1-Hour Count Value for the ones place of hours */
#define R_RTC_RHRAR_HR1_MASK                      0xf

/* BCNT3AR Register bit definitions */
#define R_RTC_BCNT3AR_BCNT3AR_SHIFT               (0)  /* The BCNT3AR counter is a readable/writable 32-bit binary counter b31 to b24. */
#define R_RTC_BCNT3AR_BCNT3AR_MASK                0xff

/* RWKAR Register bit definitions */
#define R_RTC_RWKAR_ENB                           (1 << 7)  /* Compare enable */

#define R_RTC_RWKAR_DAYW_SHIFT                    (0)  /* Day-of-Week Counting */
#define R_RTC_RWKAR_DAYW_MASK                     0x7
#  define R_RTC_RWKAR_DAYW_000                            (0 << R_RTC_RWKAR_DAYW_SHIFT)  /* Sunday */
#  define R_RTC_RWKAR_DAYW_001                            (1 << R_RTC_RWKAR_DAYW_SHIFT)  /* Monday */
#  define R_RTC_RWKAR_DAYW_010                            (2 << R_RTC_RWKAR_DAYW_SHIFT)  /* Tuesday */
#  define R_RTC_RWKAR_DAYW_011                            (3 << R_RTC_RWKAR_DAYW_SHIFT)  /* Wednesday */
#  define R_RTC_RWKAR_DAYW_100                            (4 << R_RTC_RWKAR_DAYW_SHIFT)  /* Thursday */
#  define R_RTC_RWKAR_DAYW_101                            (5 << R_RTC_RWKAR_DAYW_SHIFT)  /* Friday */
#  define R_RTC_RWKAR_DAYW_110                            (6 << R_RTC_RWKAR_DAYW_SHIFT)  /* Saturday */
#  define R_RTC_RWKAR_DAYW_111                            (7 << R_RTC_RWKAR_DAYW_SHIFT)  /* Setting Prohibited  */

/* BCNT0AER Register bit definitions */
#define R_RTC_BCNT0AER_ENB_SHIFT                  (0)  /* The BCNT0AER register is a readable/writable register for setting the alarm enable corresponding to 32-bit binary counter b7 to b0. */
#define R_RTC_BCNT0AER_ENB_MASK                   0xff

/* RDAYAR Register bit definitions */
#define R_RTC_RDAYAR_ENB                          (1 << 7)  /* Compare enable */

#define R_RTC_RDAYAR_DATE10_SHIFT                 (4)  /* 10 Days Value for the tens place of days */
#define R_RTC_RDAYAR_DATE10_MASK                  0x30

#define R_RTC_RDAYAR_DATE1_SHIFT                  (0)  /* 1 Day Value for the ones place of days */
#define R_RTC_RDAYAR_DATE1_MASK                   0xf

/* BCNT1AER Register bit definitions */
#define R_RTC_BCNT1AER_ENB_SHIFT                  (0)  /* The BCNT1AER register is a readable/writable register for setting the alarm enable corresponding to 32-bit binary counter b15 to b8. */
#define R_RTC_BCNT1AER_ENB_MASK                   0xff

/* RMONAR Register bit definitions */
#define R_RTC_RMONAR_ENB                          (1 << 7)  /* Compare enable */

#define R_RTC_RMONAR_MON10                        (1 << 4)  /* 10 Months Value for the tens place of months */

#define R_RTC_RMONAR_MON1_SHIFT                   (0)  /* 1 Month Value for the ones place of months */
#define R_RTC_RMONAR_MON1_MASK                    0xf

/* BCNT2AER Register bit definitions */
#define R_RTC_BCNT2AER_ENB_SHIFT                  (0)  /* The BCNT2AER register is a readable/writable register for setting the alarm enable corresponding to 32-bit binary counter b23 to b16. */
#define R_RTC_BCNT2AER_ENB_MASK                   0xff

/* RYRAR Register bit definitions */
#define R_RTC_RYRAR_YR10_SHIFT                    (4)  /* 10 Years Value for the tens place of years */
#define R_RTC_RYRAR_YR10_MASK                     0xf0

#define R_RTC_RYRAR_YR1_SHIFT                     (0)  /* 1 Year Value for the ones place of years */
#define R_RTC_RYRAR_YR1_MASK                      0xf

/* BCNT3AER Register bit definitions */
#define R_RTC_BCNT3AER_ENB_SHIFT                  (0)  /* The BCNT3AER register is a readable/writable register for setting the alarm enable corresponding to 32-bit binary counter b31 to b24.  */
#define R_RTC_BCNT3AER_ENB_MASK                   0xff

/* RYRAREN Register bit definitions */
#define R_RTC_RYRAREN_ENB                         (1 << 7)  /* Compare enable */

/* RCR1 Register bit definitions */
#define R_RTC_RCR1_PES_SHIFT                      (4)  /* Periodic Interrupt Select */
#define R_RTC_RCR1_PES_MASK                       0xf0
#  define R_RTC_RCR1_PES_0110                             (6 << R_RTC_RCR1_PES_SHIFT)  /* A periodic interrupt is generated every 1/256 second((RCR4.RCKSEL = 0)./A periodic interrupt is generated every 1/128 second((RCR4.RCKSEL = 1). */
#  define R_RTC_RCR1_PES_0111                             (7 << R_RTC_RCR1_PES_SHIFT)  /* A periodic interrupt is generated every 1/128 second. */
#  define R_RTC_RCR1_PES_1000                             (8 << R_RTC_RCR1_PES_SHIFT)  /* A periodic interrupt is generated every 1/64 second. */
#  define R_RTC_RCR1_PES_1001                             (9 << R_RTC_RCR1_PES_SHIFT)  /* A periodic interrupt is generated every 1/32 second. */
#  define R_RTC_RCR1_PES_1010                             (10 << R_RTC_RCR1_PES_SHIFT)  /* A periodic interrupt is generated every 1/16 second. */
#  define R_RTC_RCR1_PES_1011                             (11 << R_RTC_RCR1_PES_SHIFT)  /* A periodic interrupt is generated every 1/8 second. */
#  define R_RTC_RCR1_PES_1100                             (12 << R_RTC_RCR1_PES_SHIFT)  /* A periodic interrupt is generated every 1/4 second. */
#  define R_RTC_RCR1_PES_1101                             (13 << R_RTC_RCR1_PES_SHIFT)  /* A periodic interrupt is generated every 1/2 second. */
#  define R_RTC_RCR1_PES_1110                             (14 << R_RTC_RCR1_PES_SHIFT)  /* A periodic interrupt is generated every 1 second. */
#  define R_RTC_RCR1_PES_1111                             (15 << R_RTC_RCR1_PES_SHIFT)  /* A periodic interrupt is generated every 2 seconds. */

#define R_RTC_RCR1_RTCOS                          (1 << 3)  /* RTCOUT Output Select */

#define R_RTC_RCR1_PIE                            (1 << 2)  /* Periodic Interrupt Enable */

#define R_RTC_RCR1_CIE                            (1 << 1)  /* Carry Interrupt Enable */

#define R_RTC_RCR1_AIE                            (1 << 0)  /* Alarm Interrupt Enable */

/* RCR2 Register bit definitions */
#define R_RTC_RCR2_CNTMD                          (1 << 7)  /* Count Mode Select */

#define R_RTC_RCR2_HR24                           (1 << 6)  /* Hours Mode */

#define R_RTC_RCR2_AADJP                          (1 << 5)  /* Automatic Adjustment Period Select (When the LOCO clock is selected, the setting of this bit is disabled.) */

#define R_RTC_RCR2_AADJE                          (1 << 4)  /* Automatic Adjustment Enable (When the LOCO clock is selected, the setting of this bit is disabled.) */

#define R_RTC_RCR2_RTCOE                          (1 << 3)  /* RTCOUT Output Enable */

#define R_RTC_RCR2_ADJ30                          (1 << 2)  /* 30-Second Adjustment */

#define R_RTC_RCR2_RESET                          (1 << 1)  /* RTC Software Reset */

#define R_RTC_RCR2_START                          (1 << 0)  /* Start */

/* RCR4 Register bit definitions */
#define R_RTC_RCR4_RCKSEL                         (1 << 0)  /* Count Source Select */

#define R_RTC_RCR4_ROPSEL                         (1 << 7)  /* RTC Operation Mode Select */

/* RFRH Register bit definitions */
#define R_RTC_RFRH_RFC16                          (1 << 0)  /* Frequency Comparison Value (b16) To generate the operating clock from the LOCOclock, this bit sets the comparison value of the 128-Hz clock cycle. */

/* RFRL Register bit definitions */
#define R_RTC_RFRL_RFC_SHIFT                      (0)  /* Frequency Comparison Value(b15-b0) To generate the operating clock from the main clock, this bit sets the comparison value of the 128-Hz clock cycle. */
#define R_RTC_RFRL_RFC_MASK                       0xffff

/* RADJ Register bit definitions */
#define R_RTC_RADJ_PMADJ_SHIFT                    (6)  /* Plus-Minus */
#define R_RTC_RADJ_PMADJ_MASK                     0xc0
#  define R_RTC_RADJ_PMADJ_00                             (0 << R_RTC_RADJ_PMADJ_SHIFT)  /* Adjustment is not performed. */
#  define R_RTC_RADJ_PMADJ_01                             (1 << R_RTC_RADJ_PMADJ_SHIFT)  /* Adjustment is performed by the addition to the prescaler. */
#  define R_RTC_RADJ_PMADJ_10                             (2 << R_RTC_RADJ_PMADJ_SHIFT)  /* Adjustment is performed by the subtraction from the prescaler. */
#  define R_RTC_RADJ_PMADJ_11                             (3 << R_RTC_RADJ_PMADJ_SHIFT)  /* Setting prohibited */

#define R_RTC_RADJ_ADJ_SHIFT                      (0)  /* Adjustment Value These bits specify the adjustment value from the prescaler. */
#define R_RTC_RADJ_ADJ_MASK                       0x3f

/* RADJ2 Register bit definitions */
#define R_RTC_RADJ2_FADJ_SHIFT                    (5)  /* Fractional Adjust Value */
#define R_RTC_RADJ2_FADJ_MASK                     0xffe0


/* Maximum number of channels */

#define RTC_MAX_CHANNELS    3

#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_RA8P1_RTC_H */
