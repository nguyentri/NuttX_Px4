/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_crc.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_CRC_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_CRC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* CRC Base Addresses ****************************************************/

#ifndef RZV_CRC0_BASE
#  define RZV_CRC0_BASE               0x13000800
#endif
#ifndef RZV_CRC_BASE
#  define RZV_CRC_BASE                RZV_CRC0_BASE
#endif

/* CRC Register Offsets ***************************************************/

/* CRCCR%s Registers (0-1) */
#define RZV_CRC_CRCCR_OFFSET(m)                 (0x00000000 + ((m) * 0x00000001))  /* CRCCR Register %s */
#define RZV_CRC_CRCDIR_OFFSET                            0x0004  /* CRCDIR */
#define RZV_CRC_CRCDIR_BY_OFFSET                         0x0008  /* CRCDIR_BY */
#define RZV_CRC_CRCDOR_OFFSET                            0x0009  /* CRCDOR */
#define RZV_CRC_CRCDOR_HA_OFFSET                         0x000D  /* CRCDOR_HA */
#define RZV_CRC_CRCDOR_BY_OFFSET                         0x000F  /* CRCDOR_BY */
#define RZV_CRC_CRCSAR_OFFSET                            0x0010  /* CRCSAR */

/* CRC Register Addresses **************************************************/

#define RZV_CRC_CRCCR(m)                        (RZV_CRC_BASE + RZV_CRC_CRCCR_OFFSET(m))
#define RZV_CRC_CRCDIR                               (RZV_CRC_BASE + RZV_CRC_CRCDIR_OFFSET)
#define RZV_CRC_CRCDIR_BY                            (RZV_CRC_BASE + RZV_CRC_CRCDIR_BY_OFFSET)
#define RZV_CRC_CRCDOR                               (RZV_CRC_BASE + RZV_CRC_CRCDOR_OFFSET)
#define RZV_CRC_CRCDOR_HA                            (RZV_CRC_BASE + RZV_CRC_CRCDOR_HA_OFFSET)
#define RZV_CRC_CRCDOR_BY                            (RZV_CRC_BASE + RZV_CRC_CRCDOR_BY_OFFSET)
#define RZV_CRC_CRCSAR                               (RZV_CRC_BASE + RZV_CRC_CRCSAR_OFFSET)

/* CRC CRCCR0 Register Bit Definitions *******************************/

#define CRC_CRCCR0_GPS_SHIFT                    (0)      /* Bits 0-2: Gps */
#define CRC_CRCCR0_GPS_MASK                     (0x7 << CRC_CRCCR0_GPS_SHIFT)

#define CRC_CRCCR0_LMS                          (1 << 6)  /* Lms */

#define CRC_CRCCR0_DORCLR                       (1 << 7)  /* Dorclr */

/* CRC CRCCR1 Register Bit Definitions *******************************/

#define CRC_CRCCR1_CRCSWR                       (1 << 6)  /* Crcswr */

#define CRC_CRCCR1_CRCSEN                       (1 << 7)  /* Crcsen */

/* CRC CRCDIR Register Bit Definitions *******************************/

#define CRC_CRCDIR_CRCDIR_SHIFT                 (0)      /* Bits 0-31: Crcdir */
#define CRC_CRCDIR_CRCDIR_MASK                  (0xffffffff << CRC_CRCDIR_CRCDIR_SHIFT)

#define CRC_CRCDIR_BY_CRCDIR_BY_SHIFT           (0)      /* Bits 0-7: By Crcdir By */
#define CRC_CRCDIR_BY_CRCDIR_BY_MASK            (0xff << CRC_CRCDIR_BY_CRCDIR_BY_SHIFT)

/* CRC CRCDOR Register Bit Definitions *******************************/

#define CRC_CRCDOR_CRCDOR_SHIFT                 (0)      /* Bits 0-31: Crcdor */
#define CRC_CRCDOR_CRCDOR_MASK                  (0xffffffff << CRC_CRCDOR_CRCDOR_SHIFT)

#define CRC_CRCDOR_HA_CRCDOR_HA_SHIFT           (0)      /* Bits 0-15: Ha Crcdor Ha */
#define CRC_CRCDOR_HA_CRCDOR_HA_MASK            (0xffff << CRC_CRCDOR_HA_CRCDOR_HA_SHIFT)

#define CRC_CRCDOR_BY_CRCDOR_BY_SHIFT           (0)      /* Bits 0-7: By Crcdor By */
#define CRC_CRCDOR_BY_CRCDOR_BY_MASK            (0xff << CRC_CRCDOR_BY_CRCDOR_BY_SHIFT)

/* CRC CRCSAR Register Bit Definitions *******************************/

#define CRC_CRCSAR_CRCSA_SHIFT                  (0)      /* Bits 0-15: Crcsa */
#define CRC_CRCSAR_CRCSA_MASK                   (0xffff << CRC_CRCSAR_CRCSA_SHIFT)

/* CRC Channel definitions */
#define RZV_CRC_CHANNEL_0          0

/* Maximum number of CRC channels */
#define RZV_CRC_MAX_CHANNELS       1

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_CRC_H */
