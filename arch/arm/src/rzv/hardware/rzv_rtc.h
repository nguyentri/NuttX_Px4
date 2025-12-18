/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_rtc.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_RTC_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_RTC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* RTC Base Addresses ****************************************************/

#ifndef RZV_RTC0_BASE
#  define RZV_RTC0_BASE               0x11C00800
#endif
#ifndef RZV_RTC0_BASE
#  define RZV_RTC0_BASE               0x11C00C00
#endif

/* RTC Register Offsets ***************************************************/

/* BCNT%s Registers (0-3) */
#define RZV_RTC_BCNT_OFFSET(m)                  (0x00000003 + ((m) * 0x00000003))  /* BCNT Register %s */
/* RCR%s Registers (1-2) */
#define RZV_RTC_RCR_OFFSET(m)                   (0x0000002f + ((m) * 0x00000002))  /* RCR Register %s */
#define RZV_RTC_R64CNT_OFFSET                            0x0000  /* 64 Hz Counter */
#define RZV_RTC_RSECCNT_OFFSET                           0x0002  /* Second Counter */
#define RZV_RTC_RMINCNT_OFFSET                           0x0005  /* Minute Counter */
#define RZV_RTC_RHRCNT_OFFSET                            0x0008  /* Hour Counter */
#define RZV_RTC_RWKCNT_OFFSET                            0x000B  /* Day-of-Week Counter */
#define RZV_RTC_RDAYCNT_OFFSET                           0x000E  /* Day Counter */
#define RZV_RTC_RMONCNT_OFFSET                           0x0010  /* Month Counter */
#define RZV_RTC_RYRCNT_OFFSET                            0x0012  /* Year Counter */
#define RZV_RTC_RSECAR_OFFSET                            0x0014  /* Second Alarm Register */
#define RZV_RTC_BCNT0AR_OFFSET                           0x0015  /* BCNT0AR */
#define RZV_RTC_RMINAR_OFFSET                            0x0017  /* Minute Alarm Register */
#define RZV_RTC_BCNT1AR_OFFSET                           0x0018  /* BCNT1AR */
#define RZV_RTC_RHRAR_OFFSET                             0x001A  /* Hour Alarm Register */
#define RZV_RTC_BCNT2AR_OFFSET                           0x001B  /* BCNT2AR */
#define RZV_RTC_RWKAR_OFFSET                             0x001D  /* Day-of-Week Alarm Register */
#define RZV_RTC_BCNT3AR_OFFSET                           0x001E  /* BCNT3AR */
#define RZV_RTC_RDAYAR_OFFSET                            0x0020  /* Day Alarm Register */
#define RZV_RTC_BCNT0AER_OFFSET                          0x0021  /* BCNT0AER */
#define RZV_RTC_RMONAR_OFFSET                            0x0023  /* Month Alarm Register */
#define RZV_RTC_BCNT1AER_OFFSET                          0x0024  /* BCNT1AER */
#define RZV_RTC_RYRAR_OFFSET                             0x0026  /* Year Alarm Register */
#define RZV_RTC_BCNT2AER_OFFSET                          0x0028  /* BCNT2AER */
#define RZV_RTC_RYRAREN_OFFSET                           0x002A  /* Year Alarm Enable Register */
#define RZV_RTC_BCNT3AER_OFFSET                          0x002B  /* BCNT3AER */
#define RZV_RTC_RSR_OFFSET                               0x002D  /* RSR */
#define RZV_RTC_RADJ_OFFSET                              0x003B  /* Time Error Adjustment Register */

/* RTC Register Addresses **************************************************/

#define RZV_RTC_BCNT(ch,m)                      (RZV_RTC##ch##_BASE + RZV_RTC_BCNT_OFFSET(m))
#define RZV_RTC_RCR(ch,m)                       (RZV_RTC##ch##_BASE + RZV_RTC_RCR_OFFSET(m))
#define RZV_RTC_R64CNT(ch)                           (RZV_RTC##ch##_BASE + RZV_RTC_R64CNT_OFFSET)
#define RZV_RTC_RSECCNT(ch)                          (RZV_RTC##ch##_BASE + RZV_RTC_RSECCNT_OFFSET)
#define RZV_RTC_RMINCNT(ch)                          (RZV_RTC##ch##_BASE + RZV_RTC_RMINCNT_OFFSET)
#define RZV_RTC_RHRCNT(ch)                           (RZV_RTC##ch##_BASE + RZV_RTC_RHRCNT_OFFSET)
#define RZV_RTC_RWKCNT(ch)                           (RZV_RTC##ch##_BASE + RZV_RTC_RWKCNT_OFFSET)
#define RZV_RTC_RDAYCNT(ch)                          (RZV_RTC##ch##_BASE + RZV_RTC_RDAYCNT_OFFSET)
#define RZV_RTC_RMONCNT(ch)                          (RZV_RTC##ch##_BASE + RZV_RTC_RMONCNT_OFFSET)
#define RZV_RTC_RYRCNT(ch)                           (RZV_RTC##ch##_BASE + RZV_RTC_RYRCNT_OFFSET)
#define RZV_RTC_RSECAR(ch)                           (RZV_RTC##ch##_BASE + RZV_RTC_RSECAR_OFFSET)
#define RZV_RTC_BCNT0AR(ch)                          (RZV_RTC##ch##_BASE + RZV_RTC_BCNT0AR_OFFSET)
#define RZV_RTC_RMINAR(ch)                           (RZV_RTC##ch##_BASE + RZV_RTC_RMINAR_OFFSET)
#define RZV_RTC_BCNT1AR(ch)                          (RZV_RTC##ch##_BASE + RZV_RTC_BCNT1AR_OFFSET)
#define RZV_RTC_RHRAR(ch)                            (RZV_RTC##ch##_BASE + RZV_RTC_RHRAR_OFFSET)
#define RZV_RTC_BCNT2AR(ch)                          (RZV_RTC##ch##_BASE + RZV_RTC_BCNT2AR_OFFSET)
#define RZV_RTC_RWKAR(ch)                            (RZV_RTC##ch##_BASE + RZV_RTC_RWKAR_OFFSET)
#define RZV_RTC_BCNT3AR(ch)                          (RZV_RTC##ch##_BASE + RZV_RTC_BCNT3AR_OFFSET)
#define RZV_RTC_RDAYAR(ch)                           (RZV_RTC##ch##_BASE + RZV_RTC_RDAYAR_OFFSET)
#define RZV_RTC_BCNT0AER(ch)                         (RZV_RTC##ch##_BASE + RZV_RTC_BCNT0AER_OFFSET)
#define RZV_RTC_RMONAR(ch)                           (RZV_RTC##ch##_BASE + RZV_RTC_RMONAR_OFFSET)
#define RZV_RTC_BCNT1AER(ch)                         (RZV_RTC##ch##_BASE + RZV_RTC_BCNT1AER_OFFSET)
#define RZV_RTC_RYRAR(ch)                            (RZV_RTC##ch##_BASE + RZV_RTC_RYRAR_OFFSET)
#define RZV_RTC_BCNT2AER(ch)                         (RZV_RTC##ch##_BASE + RZV_RTC_BCNT2AER_OFFSET)
#define RZV_RTC_RYRAREN(ch)                          (RZV_RTC##ch##_BASE + RZV_RTC_RYRAREN_OFFSET)
#define RZV_RTC_BCNT3AER(ch)                         (RZV_RTC##ch##_BASE + RZV_RTC_BCNT3AER_OFFSET)
#define RZV_RTC_RSR(ch)                              (RZV_RTC##ch##_BASE + RZV_RTC_RSR_OFFSET)
#define RZV_RTC_RADJ(ch)                             (RZV_RTC##ch##_BASE + RZV_RTC_RADJ_OFFSET)

/* RTC BCNT Register Bit Definitions (Parameterized) ***********************/

#define RTC_BCNT_BCNT_SHIFT                               (0)      /* Bits 0-7: Bcnt */
#define RTC_BCNT_BCNT_MASK(m)                             (0xff << RTC_BCNT_BCNT_SHIFT)
#define RTC_BCNT_BCNT(m,val)                              (((val) << RTC_BCNT_BCNT_SHIFT) & RTC_BCNT_BCNT_MASK(m))

/* RTC RCR Register Bit Definitions (Parameterized) ************************/

#define RTC_RCR_AIE(m)                                    (1 << 0)  /* Aie */
#define RTC_RCR_CIE(m)                                    (1 << 1)  /* Cie */
#define RTC_RCR_PIE(m)                                    (1 << 2)  /* Pie */
#define RTC_RCR_PES_SHIFT                                 (4)      /* Bits 4-7: Pes */
#define RTC_RCR_PES_MASK(m)                               (0xf << RTC_RCR_PES_SHIFT)
#define RTC_RCR_PES(m,val)                                (((val) << RTC_RCR_PES_SHIFT) & RTC_RCR_PES_MASK(m))

/* RTC BCNT0AER Register Bit Definitions *****************************/

#define RTC_BCNT0AER_ENB_SHIFT                  (0)      /* Bits 0-7: Enb */
#define RTC_BCNT0AER_ENB_MASK                   (0xff << RTC_BCNT0AER_ENB_SHIFT)

/* RTC BCNT0AR Register Bit Definitions ******************************/

#define RTC_BCNT0AR_BCNTAR_SHIFT                (0)      /* Bits 0-7: Bcntar */
#define RTC_BCNT0AR_BCNTAR_MASK                 (0xff << RTC_BCNT0AR_BCNTAR_SHIFT)

/* RTC BCNT1AER Register Bit Definitions *****************************/

#define RTC_BCNT1AER_ENB_SHIFT                  (0)      /* Bits 0-7: Enb */
#define RTC_BCNT1AER_ENB_MASK                   (0xff << RTC_BCNT1AER_ENB_SHIFT)

/* RTC BCNT1AR Register Bit Definitions ******************************/

#define RTC_BCNT1AR_BCNTAR_SHIFT                (0)      /* Bits 0-7: Bcntar */
#define RTC_BCNT1AR_BCNTAR_MASK                 (0xff << RTC_BCNT1AR_BCNTAR_SHIFT)

/* RTC BCNT2AER Register Bit Definitions *****************************/

#define RTC_BCNT2AER_ENB_SHIFT                  (0)      /* Bits 0-7: Enb */
#define RTC_BCNT2AER_ENB_MASK                   (0xff << RTC_BCNT2AER_ENB_SHIFT)

/* RTC BCNT2AR Register Bit Definitions ******************************/

#define RTC_BCNT2AR_BCNTAR_SHIFT                (0)      /* Bits 0-7: Bcntar */
#define RTC_BCNT2AR_BCNTAR_MASK                 (0xff << RTC_BCNT2AR_BCNTAR_SHIFT)

/* RTC BCNT3AER Register Bit Definitions *****************************/

#define RTC_BCNT3AER_ENB_SHIFT                  (0)      /* Bits 0-7: Enb */
#define RTC_BCNT3AER_ENB_MASK                   (0xff << RTC_BCNT3AER_ENB_SHIFT)

/* RTC BCNT3AR Register Bit Definitions ******************************/

#define RTC_BCNT3AR_BCNTAR_SHIFT                (0)      /* Bits 0-7: Bcntar */
#define RTC_BCNT3AR_BCNTAR_MASK                 (0xff << RTC_BCNT3AR_BCNTAR_SHIFT)

/* RTC R64CNT Register Bit Definitions *******************************/

#define RTC_R64CNT_F64HZ                        (1 << 0)  /* F64Hz */

#define RTC_R64CNT_F32HZ                        (1 << 1)  /* F32Hz */

#define RTC_R64CNT_F16HZ                        (1 << 2)  /* F16Hz */

#define RTC_R64CNT_F8HZ                         (1 << 3)  /* F8Hz */

#define RTC_R64CNT_F4HZ                         (1 << 4)  /* F4Hz */

#define RTC_R64CNT_F2HZ                         (1 << 5)  /* F2Hz */

#define RTC_R64CNT_F1HZ                         (1 << 6)  /* F1Hz */

/* RTC RADJ Register Bit Definitions *********************************/

#define RTC_RADJ_ADJ_SHIFT                      (0)      /* Bits 0-5: Adj */
#define RTC_RADJ_ADJ_MASK                       (0x3f << RTC_RADJ_ADJ_SHIFT)

#define RTC_RADJ_PMADJ_SHIFT                    (6)      /* Bits 6-7: Pmadj */
#define RTC_RADJ_PMADJ_MASK                     (0x3 << RTC_RADJ_PMADJ_SHIFT)

/* RTC RDAYAR Register Bit Definitions *******************************/

#define RTC_RDAYAR_DATE1_SHIFT                  (0)      /* Bits 0-3: Date1 */
#define RTC_RDAYAR_DATE1_MASK                   (0xf << RTC_RDAYAR_DATE1_SHIFT)

#define RTC_RDAYAR_DATE10_SHIFT                 (4)      /* Bits 4-5: Date10 */
#define RTC_RDAYAR_DATE10_MASK                  (0x3 << RTC_RDAYAR_DATE10_SHIFT)

#define RTC_RDAYAR_ENB                          (1 << 7)  /* Enb */

/* RTC RDAYCNT Register Bit Definitions ******************************/

#define RTC_RDAYCNT_DATE1_SHIFT                 (0)      /* Bits 0-3: Date1 */
#define RTC_RDAYCNT_DATE1_MASK                  (0xf << RTC_RDAYCNT_DATE1_SHIFT)

#define RTC_RDAYCNT_DATE10_SHIFT                (4)      /* Bits 4-5: Date10 */
#define RTC_RDAYCNT_DATE10_MASK                 (0x3 << RTC_RDAYCNT_DATE10_SHIFT)

/* RTC RHRAR Register Bit Definitions ********************************/

#define RTC_RHRAR_HR1_SHIFT                     (0)      /* Bits 0-3: Hr1 */
#define RTC_RHRAR_HR1_MASK                      (0xf << RTC_RHRAR_HR1_SHIFT)

#define RTC_RHRAR_HR10_SHIFT                    (4)      /* Bits 4-5: Hr10 */
#define RTC_RHRAR_HR10_MASK                     (0x3 << RTC_RHRAR_HR10_SHIFT)

#define RTC_RHRAR_PM                            (1 << 6)  /* Pm */

#define RTC_RHRAR_ENB                           (1 << 7)  /* Enb */

/* RTC RHRCNT Register Bit Definitions *******************************/

#define RTC_RHRCNT_HR1_SHIFT                    (0)      /* Bits 0-3: Hr1 */
#define RTC_RHRCNT_HR1_MASK                     (0xf << RTC_RHRCNT_HR1_SHIFT)

#define RTC_RHRCNT_HR10_SHIFT                   (4)      /* Bits 4-5: Hr10 */
#define RTC_RHRCNT_HR10_MASK                    (0x3 << RTC_RHRCNT_HR10_SHIFT)

#define RTC_RHRCNT_PM                           (1 << 6)  /* Pm */

/* RTC RMINAR Register Bit Definitions *******************************/

#define RTC_RMINAR_MIN1_SHIFT                   (0)      /* Bits 0-3: Min1 */
#define RTC_RMINAR_MIN1_MASK                    (0xf << RTC_RMINAR_MIN1_SHIFT)

#define RTC_RMINAR_MIN10_SHIFT                  (4)      /* Bits 4-6: Min10 */
#define RTC_RMINAR_MIN10_MASK                   (0x7 << RTC_RMINAR_MIN10_SHIFT)

#define RTC_RMINAR_ENB                          (1 << 7)  /* Enb */

/* RTC RMINCNT Register Bit Definitions ******************************/

#define RTC_RMINCNT_MIN1_SHIFT                  (0)      /* Bits 0-3: Min1 */
#define RTC_RMINCNT_MIN1_MASK                   (0xf << RTC_RMINCNT_MIN1_SHIFT)

#define RTC_RMINCNT_MIN10_SHIFT                 (4)      /* Bits 4-6: Min10 */
#define RTC_RMINCNT_MIN10_MASK                  (0x7 << RTC_RMINCNT_MIN10_SHIFT)

/* RTC RMONAR Register Bit Definitions *******************************/

#define RTC_RMONAR_MON1_SHIFT                   (0)      /* Bits 0-3: Mon1 */
#define RTC_RMONAR_MON1_MASK                    (0xf << RTC_RMONAR_MON1_SHIFT)

#define RTC_RMONAR_MON10                        (1 << 4)  /* Mon10 */

#define RTC_RMONAR_ENB                          (1 << 7)  /* Enb */

/* RTC RMONCNT Register Bit Definitions ******************************/

#define RTC_RMONCNT_MON1_SHIFT                  (0)      /* Bits 0-3: Mon1 */
#define RTC_RMONCNT_MON1_MASK                   (0xf << RTC_RMONCNT_MON1_SHIFT)

#define RTC_RMONCNT_MON10                       (1 << 4)  /* Mon10 */

/* RTC RSECAR Register Bit Definitions *******************************/

#define RTC_RSECAR_SEC1_SHIFT                   (0)      /* Bits 0-3: Sec1 */
#define RTC_RSECAR_SEC1_MASK                    (0xf << RTC_RSECAR_SEC1_SHIFT)

#define RTC_RSECAR_SEC10_SHIFT                  (4)      /* Bits 4-6: Sec10 */
#define RTC_RSECAR_SEC10_MASK                   (0x7 << RTC_RSECAR_SEC10_SHIFT)

#define RTC_RSECAR_ENB                          (1 << 7)  /* Enb */

/* RTC RSECCNT Register Bit Definitions ******************************/

#define RTC_RSECCNT_SEC1_SHIFT                  (0)      /* Bits 0-3: Sec1 */
#define RTC_RSECCNT_SEC1_MASK                   (0xf << RTC_RSECCNT_SEC1_SHIFT)

#define RTC_RSECCNT_SEC10_SHIFT                 (4)      /* Bits 4-6: Sec10 */
#define RTC_RSECCNT_SEC10_MASK                  (0x7 << RTC_RSECCNT_SEC10_SHIFT)

/* RTC RSR Register Bit Definitions **********************************/

#define RTC_RSR_AF                              (1 << 0)  /* Af */

#define RTC_RSR_CF                              (1 << 1)  /* Cf */

#define RTC_RSR_PF                              (1 << 2)  /* Pf */

/* RTC RWKAR Register Bit Definitions ********************************/

#define RTC_RWKAR_DAYW_SHIFT                    (0)      /* Bits 0-2: Dayw */
#define RTC_RWKAR_DAYW_MASK                     (0x7 << RTC_RWKAR_DAYW_SHIFT)

#define RTC_RWKAR_ENB                           (1 << 7)  /* Enb */

/* RTC RWKCNT Register Bit Definitions *******************************/

#define RTC_RWKCNT_DAYW_SHIFT                   (0)      /* Bits 0-2: Dayw */
#define RTC_RWKCNT_DAYW_MASK                    (0x7 << RTC_RWKCNT_DAYW_SHIFT)

/* RTC RYRAR Register Bit Definitions ********************************/

#define RTC_RYRAR_YR1_SHIFT                     (0)      /* Bits 0-3: Yr1 */
#define RTC_RYRAR_YR1_MASK                      (0xf << RTC_RYRAR_YR1_SHIFT)

#define RTC_RYRAR_YR10_SHIFT                    (4)      /* Bits 4-7: Yr10 */
#define RTC_RYRAR_YR10_MASK                     (0xf << RTC_RYRAR_YR10_SHIFT)

/* RTC RYRAREN Register Bit Definitions ******************************/

#define RTC_RYRAREN_ENB                         (1 << 7)  /* Enb */

/* RTC RYRCNT Register Bit Definitions *******************************/

#define RTC_RYRCNT_YR1_SHIFT                    (0)      /* Bits 0-3: Yr1 */
#define RTC_RYRCNT_YR1_MASK                     (0xf << RTC_RYRCNT_YR1_SHIFT)

#define RTC_RYRCNT_YR10_SHIFT                   (4)      /* Bits 4-7: Yr10 */
#define RTC_RYRCNT_YR10_MASK                    (0xf << RTC_RYRCNT_YR10_SHIFT)

/* RTC Channel definitions */
#define RZV_RTC_CHANNEL_0          0
#define RZV_RTC_CHANNEL_0          0

/* Maximum number of RTC channels */
#define RZV_RTC_MAX_CHANNELS       2

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_RTC_H */
