/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_mhu.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_MHU_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_MHU_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* MHU Base Addresses ****************************************************/

#ifndef RZV_MHU0_BASE
#  define RZV_MHU0_BASE               0x10480000
#endif
#ifndef RZV_MHU0_BASE
#  define RZV_MHU0_BASE               0x10480800
#endif
#ifndef RZV_MHU0_BASE
#  define RZV_MHU0_BASE               0x10481000
#endif
#ifndef RZV_MHU1_BASE
#  define RZV_MHU1_BASE               0x10480020
#endif
#ifndef RZV_MHU1_BASE
#  define RZV_MHU1_BASE               0x10480810
#endif
#ifndef RZV_MHU1_BASE
#  define RZV_MHU1_BASE               0x10481020
#endif
#ifndef RZV_MHU10_BASE
#  define RZV_MHU10_BASE              0x10480140
#endif
#ifndef RZV_MHU10_BASE
#  define RZV_MHU10_BASE              0x104808A0
#endif
#ifndef RZV_MHU10_BASE
#  define RZV_MHU10_BASE              0x10481140
#endif
#ifndef RZV_MHU11_BASE
#  define RZV_MHU11_BASE              0x10480160
#endif
#ifndef RZV_MHU11_BASE
#  define RZV_MHU11_BASE              0x104808B0
#endif
#ifndef RZV_MHU11_BASE
#  define RZV_MHU11_BASE              0x10481160
#endif
#ifndef RZV_MHU12_BASE
#  define RZV_MHU12_BASE              0x10480180
#endif
#ifndef RZV_MHU12_BASE
#  define RZV_MHU12_BASE              0x104808C0
#endif
#ifndef RZV_MHU12_BASE
#  define RZV_MHU12_BASE              0x10481180
#endif
#ifndef RZV_MHU13_BASE
#  define RZV_MHU13_BASE              0x104801A0
#endif
#ifndef RZV_MHU13_BASE
#  define RZV_MHU13_BASE              0x104808D0
#endif
#ifndef RZV_MHU13_BASE
#  define RZV_MHU13_BASE              0x104811A0
#endif
#ifndef RZV_MHU14_BASE
#  define RZV_MHU14_BASE              0x104801C0
#endif
#ifndef RZV_MHU14_BASE
#  define RZV_MHU14_BASE              0x104808E0
#endif
#ifndef RZV_MHU14_BASE
#  define RZV_MHU14_BASE              0x104811C0
#endif
#ifndef RZV_MHU15_BASE
#  define RZV_MHU15_BASE              0x104801E0
#endif
#ifndef RZV_MHU15_BASE
#  define RZV_MHU15_BASE              0x104808F0
#endif
#ifndef RZV_MHU15_BASE
#  define RZV_MHU15_BASE              0x104811E0
#endif
#ifndef RZV_MHU16_BASE
#  define RZV_MHU16_BASE              0x10480200
#endif
#ifndef RZV_MHU16_BASE
#  define RZV_MHU16_BASE              0x10480900
#endif
#ifndef RZV_MHU16_BASE
#  define RZV_MHU16_BASE              0x10481200
#endif
#ifndef RZV_MHU17_BASE
#  define RZV_MHU17_BASE              0x10480220
#endif
#ifndef RZV_MHU17_BASE
#  define RZV_MHU17_BASE              0x10480910
#endif
#ifndef RZV_MHU17_BASE
#  define RZV_MHU17_BASE              0x10481220
#endif
#ifndef RZV_MHU18_BASE
#  define RZV_MHU18_BASE              0x10480240
#endif
#ifndef RZV_MHU18_BASE
#  define RZV_MHU18_BASE              0x10480920
#endif
#ifndef RZV_MHU18_BASE
#  define RZV_MHU18_BASE              0x10481240
#endif
#ifndef RZV_MHU19_BASE
#  define RZV_MHU19_BASE              0x10480260
#endif
#ifndef RZV_MHU19_BASE
#  define RZV_MHU19_BASE              0x10480930
#endif
#ifndef RZV_MHU19_BASE
#  define RZV_MHU19_BASE              0x10481260
#endif
#ifndef RZV_MHU2_BASE
#  define RZV_MHU2_BASE               0x10480040
#endif
#ifndef RZV_MHU2_BASE
#  define RZV_MHU2_BASE               0x10480820
#endif
#ifndef RZV_MHU2_BASE
#  define RZV_MHU2_BASE               0x10481040
#endif
#ifndef RZV_MHU20_BASE
#  define RZV_MHU20_BASE              0x10480280
#endif
#ifndef RZV_MHU20_BASE
#  define RZV_MHU20_BASE              0x10480940
#endif
#ifndef RZV_MHU20_BASE
#  define RZV_MHU20_BASE              0x10481280
#endif
#ifndef RZV_MHU21_BASE
#  define RZV_MHU21_BASE              0x104802A0
#endif
#ifndef RZV_MHU21_BASE
#  define RZV_MHU21_BASE              0x10480950
#endif
#ifndef RZV_MHU21_BASE
#  define RZV_MHU21_BASE              0x104812A0
#endif
#ifndef RZV_MHU22_BASE
#  define RZV_MHU22_BASE              0x104802C0
#endif
#ifndef RZV_MHU22_BASE
#  define RZV_MHU22_BASE              0x10480960
#endif
#ifndef RZV_MHU22_BASE
#  define RZV_MHU22_BASE              0x104812C0
#endif
#ifndef RZV_MHU23_BASE
#  define RZV_MHU23_BASE              0x104802E0
#endif
#ifndef RZV_MHU23_BASE
#  define RZV_MHU23_BASE              0x10480970
#endif
#ifndef RZV_MHU23_BASE
#  define RZV_MHU23_BASE              0x104812E0
#endif
#ifndef RZV_MHU24_BASE
#  define RZV_MHU24_BASE              0x10480300
#endif
#ifndef RZV_MHU24_BASE
#  define RZV_MHU24_BASE              0x10480980
#endif
#ifndef RZV_MHU24_BASE
#  define RZV_MHU24_BASE              0x10481300
#endif
#ifndef RZV_MHU25_BASE
#  define RZV_MHU25_BASE              0x10480320
#endif
#ifndef RZV_MHU25_BASE
#  define RZV_MHU25_BASE              0x10480990
#endif
#ifndef RZV_MHU25_BASE
#  define RZV_MHU25_BASE              0x10481320
#endif
#ifndef RZV_MHU26_BASE
#  define RZV_MHU26_BASE              0x10480340
#endif
#ifndef RZV_MHU26_BASE
#  define RZV_MHU26_BASE              0x104809A0
#endif
#ifndef RZV_MHU26_BASE
#  define RZV_MHU26_BASE              0x10481340
#endif
#ifndef RZV_MHU27_BASE
#  define RZV_MHU27_BASE              0x10480360
#endif
#ifndef RZV_MHU27_BASE
#  define RZV_MHU27_BASE              0x104809B0
#endif
#ifndef RZV_MHU27_BASE
#  define RZV_MHU27_BASE              0x10481360
#endif
#ifndef RZV_MHU28_BASE
#  define RZV_MHU28_BASE              0x10480380
#endif
#ifndef RZV_MHU28_BASE
#  define RZV_MHU28_BASE              0x10481380
#endif
#ifndef RZV_MHU29_BASE
#  define RZV_MHU29_BASE              0x104803A0
#endif
#ifndef RZV_MHU29_BASE
#  define RZV_MHU29_BASE              0x104813A0
#endif
#ifndef RZV_MHU3_BASE
#  define RZV_MHU3_BASE               0x10480060
#endif
#ifndef RZV_MHU3_BASE
#  define RZV_MHU3_BASE               0x10480830
#endif
#ifndef RZV_MHU3_BASE
#  define RZV_MHU3_BASE               0x10481060
#endif
#ifndef RZV_MHU30_BASE
#  define RZV_MHU30_BASE              0x104803C0
#endif
#ifndef RZV_MHU30_BASE
#  define RZV_MHU30_BASE              0x104813C0
#endif
#ifndef RZV_MHU31_BASE
#  define RZV_MHU31_BASE              0x104803E0
#endif
#ifndef RZV_MHU31_BASE
#  define RZV_MHU31_BASE              0x104813E0
#endif
#ifndef RZV_MHU32_BASE
#  define RZV_MHU32_BASE              0x10480400
#endif
#ifndef RZV_MHU32_BASE
#  define RZV_MHU32_BASE              0x10481400
#endif
#ifndef RZV_MHU33_BASE
#  define RZV_MHU33_BASE              0x10480420
#endif
#ifndef RZV_MHU33_BASE
#  define RZV_MHU33_BASE              0x10481420
#endif
#ifndef RZV_MHU34_BASE
#  define RZV_MHU34_BASE              0x10480440
#endif
#ifndef RZV_MHU34_BASE
#  define RZV_MHU34_BASE              0x10481440
#endif
#ifndef RZV_MHU35_BASE
#  define RZV_MHU35_BASE              0x10480460
#endif
#ifndef RZV_MHU35_BASE
#  define RZV_MHU35_BASE              0x10481460
#endif
#ifndef RZV_MHU36_BASE
#  define RZV_MHU36_BASE              0x10480480
#endif
#ifndef RZV_MHU36_BASE
#  define RZV_MHU36_BASE              0x10481480
#endif
#ifndef RZV_MHU37_BASE
#  define RZV_MHU37_BASE              0x104804A0
#endif
#ifndef RZV_MHU37_BASE
#  define RZV_MHU37_BASE              0x104814A0
#endif
#ifndef RZV_MHU38_BASE
#  define RZV_MHU38_BASE              0x104804C0
#endif
#ifndef RZV_MHU38_BASE
#  define RZV_MHU38_BASE              0x104814C0
#endif
#ifndef RZV_MHU39_BASE
#  define RZV_MHU39_BASE              0x104804E0
#endif
#ifndef RZV_MHU39_BASE
#  define RZV_MHU39_BASE              0x104814E0
#endif
#ifndef RZV_MHU4_BASE
#  define RZV_MHU4_BASE               0x10480080
#endif
#ifndef RZV_MHU4_BASE
#  define RZV_MHU4_BASE               0x10480840
#endif
#ifndef RZV_MHU4_BASE
#  define RZV_MHU4_BASE               0x10481080
#endif
#ifndef RZV_MHU40_BASE
#  define RZV_MHU40_BASE              0x10480500
#endif
#ifndef RZV_MHU40_BASE
#  define RZV_MHU40_BASE              0x10481500
#endif
#ifndef RZV_MHU41_BASE
#  define RZV_MHU41_BASE              0x10480520
#endif
#ifndef RZV_MHU41_BASE
#  define RZV_MHU41_BASE              0x10481520
#endif
#ifndef RZV_MHU5_BASE
#  define RZV_MHU5_BASE               0x104800A0
#endif
#ifndef RZV_MHU5_BASE
#  define RZV_MHU5_BASE               0x10480850
#endif
#ifndef RZV_MHU5_BASE
#  define RZV_MHU5_BASE               0x104810A0
#endif
#ifndef RZV_MHU6_BASE
#  define RZV_MHU6_BASE               0x104800C0
#endif
#ifndef RZV_MHU6_BASE
#  define RZV_MHU6_BASE               0x10480860
#endif
#ifndef RZV_MHU6_BASE
#  define RZV_MHU6_BASE               0x104810C0
#endif
#ifndef RZV_MHU7_BASE
#  define RZV_MHU7_BASE               0x104800E0
#endif
#ifndef RZV_MHU7_BASE
#  define RZV_MHU7_BASE               0x10480870
#endif
#ifndef RZV_MHU7_BASE
#  define RZV_MHU7_BASE               0x104810E0
#endif
#ifndef RZV_MHU8_BASE
#  define RZV_MHU8_BASE               0x10480100
#endif
#ifndef RZV_MHU8_BASE
#  define RZV_MHU8_BASE               0x10480880
#endif
#ifndef RZV_MHU8_BASE
#  define RZV_MHU8_BASE               0x10481100
#endif
#ifndef RZV_MHU9_BASE
#  define RZV_MHU9_BASE               0x10480120
#endif
#ifndef RZV_MHU9_BASE
#  define RZV_MHU9_BASE               0x10480890
#endif
#ifndef RZV_MHU9_BASE
#  define RZV_MHU9_BASE               0x10481120
#endif

/* MHU Register Addresses **************************************************/

/* MHU MSG_INT_CLRn Register Bit Definitions *************************/

#define MHU_MSG_INT_CLRn_CLEAR                  (1 << 0)  /* Clear */

/* MHU MSG_INT_SETn Register Bit Definitions *************************/

#define MHU_MSG_INT_SETn_SET                    (1 << 0)  /* Set */

/* MHU MSG_INT_STSn Register Bit Definitions *************************/

#define MHU_MSG_INT_STSn_STAT                   (1 << 0)  /* Stat */

/* MHU RSP_INT_CLRn Register Bit Definitions *************************/

#define MHU_RSP_INT_CLRn_CLEAR                  (1 << 0)  /* Clear */

/* MHU RSP_INT_SETn Register Bit Definitions *************************/

#define MHU_RSP_INT_SETn_SET                    (1 << 0)  /* Set */

/* MHU RSP_INT_STSn Register Bit Definitions *************************/

#define MHU_RSP_INT_STSn_STAT                   (1 << 0)  /* Stat */

/* MHU SW_INT_CLRn Register Bit Definitions **************************/

#define MHU_SW_INT_CLRn_CLEAR                   (1 << 0)  /* Clear */

/* MHU SW_INT_SETn Register Bit Definitions **************************/

#define MHU_SW_INT_SETn_SET                     (1 << 0)  /* Set */

/* MHU SW_INT_STSn Register Bit Definitions **************************/

#define MHU_SW_INT_STSn_STAT                    (1 << 0)  /* Stat */

/* MHU Channel definitions */
#define RZV_MHU_CHANNEL_0          0
#define RZV_MHU_CHANNEL_0          0
#define RZV_MHU_CHANNEL_0          0
#define RZV_MHU_CHANNEL_1          1
#define RZV_MHU_CHANNEL_1          1
#define RZV_MHU_CHANNEL_1          1
#define RZV_MHU_CHANNEL_10         10
#define RZV_MHU_CHANNEL_10         10
#define RZV_MHU_CHANNEL_10         10
#define RZV_MHU_CHANNEL_11         11
#define RZV_MHU_CHANNEL_11         11
#define RZV_MHU_CHANNEL_11         11
#define RZV_MHU_CHANNEL_12         12
#define RZV_MHU_CHANNEL_12         12
#define RZV_MHU_CHANNEL_12         12
#define RZV_MHU_CHANNEL_13         13
#define RZV_MHU_CHANNEL_13         13
#define RZV_MHU_CHANNEL_13         13
#define RZV_MHU_CHANNEL_14         14
#define RZV_MHU_CHANNEL_14         14
#define RZV_MHU_CHANNEL_14         14
#define RZV_MHU_CHANNEL_15         15
#define RZV_MHU_CHANNEL_15         15
#define RZV_MHU_CHANNEL_15         15
#define RZV_MHU_CHANNEL_16         16
#define RZV_MHU_CHANNEL_16         16
#define RZV_MHU_CHANNEL_16         16
#define RZV_MHU_CHANNEL_17         17
#define RZV_MHU_CHANNEL_17         17
#define RZV_MHU_CHANNEL_17         17
#define RZV_MHU_CHANNEL_18         18
#define RZV_MHU_CHANNEL_18         18
#define RZV_MHU_CHANNEL_18         18
#define RZV_MHU_CHANNEL_19         19
#define RZV_MHU_CHANNEL_19         19
#define RZV_MHU_CHANNEL_19         19
#define RZV_MHU_CHANNEL_2          2
#define RZV_MHU_CHANNEL_2          2
#define RZV_MHU_CHANNEL_2          2
#define RZV_MHU_CHANNEL_20         20
#define RZV_MHU_CHANNEL_20         20
#define RZV_MHU_CHANNEL_20         20
#define RZV_MHU_CHANNEL_21         21
#define RZV_MHU_CHANNEL_21         21
#define RZV_MHU_CHANNEL_21         21
#define RZV_MHU_CHANNEL_22         22
#define RZV_MHU_CHANNEL_22         22
#define RZV_MHU_CHANNEL_22         22
#define RZV_MHU_CHANNEL_23         23
#define RZV_MHU_CHANNEL_23         23
#define RZV_MHU_CHANNEL_23         23
#define RZV_MHU_CHANNEL_24         24
#define RZV_MHU_CHANNEL_24         24
#define RZV_MHU_CHANNEL_24         24
#define RZV_MHU_CHANNEL_25         25
#define RZV_MHU_CHANNEL_25         25
#define RZV_MHU_CHANNEL_25         25
#define RZV_MHU_CHANNEL_26         26
#define RZV_MHU_CHANNEL_26         26
#define RZV_MHU_CHANNEL_26         26
#define RZV_MHU_CHANNEL_27         27
#define RZV_MHU_CHANNEL_27         27
#define RZV_MHU_CHANNEL_27         27
#define RZV_MHU_CHANNEL_28         28
#define RZV_MHU_CHANNEL_28         28
#define RZV_MHU_CHANNEL_29         29
#define RZV_MHU_CHANNEL_29         29
#define RZV_MHU_CHANNEL_3          3
#define RZV_MHU_CHANNEL_3          3
#define RZV_MHU_CHANNEL_3          3
#define RZV_MHU_CHANNEL_30         30
#define RZV_MHU_CHANNEL_30         30
#define RZV_MHU_CHANNEL_31         31
#define RZV_MHU_CHANNEL_31         31
#define RZV_MHU_CHANNEL_32         32
#define RZV_MHU_CHANNEL_32         32
#define RZV_MHU_CHANNEL_33         33
#define RZV_MHU_CHANNEL_33         33
#define RZV_MHU_CHANNEL_34         34
#define RZV_MHU_CHANNEL_34         34
#define RZV_MHU_CHANNEL_35         35
#define RZV_MHU_CHANNEL_35         35
#define RZV_MHU_CHANNEL_36         36
#define RZV_MHU_CHANNEL_36         36
#define RZV_MHU_CHANNEL_37         37
#define RZV_MHU_CHANNEL_37         37
#define RZV_MHU_CHANNEL_38         38
#define RZV_MHU_CHANNEL_38         38
#define RZV_MHU_CHANNEL_39         39
#define RZV_MHU_CHANNEL_39         39
#define RZV_MHU_CHANNEL_4          4
#define RZV_MHU_CHANNEL_4          4
#define RZV_MHU_CHANNEL_4          4
#define RZV_MHU_CHANNEL_40         40
#define RZV_MHU_CHANNEL_40         40
#define RZV_MHU_CHANNEL_41         41
#define RZV_MHU_CHANNEL_41         41
#define RZV_MHU_CHANNEL_5          5
#define RZV_MHU_CHANNEL_5          5
#define RZV_MHU_CHANNEL_5          5
#define RZV_MHU_CHANNEL_6          6
#define RZV_MHU_CHANNEL_6          6
#define RZV_MHU_CHANNEL_6          6
#define RZV_MHU_CHANNEL_7          7
#define RZV_MHU_CHANNEL_7          7
#define RZV_MHU_CHANNEL_7          7
#define RZV_MHU_CHANNEL_8          8
#define RZV_MHU_CHANNEL_8          8
#define RZV_MHU_CHANNEL_8          8
#define RZV_MHU_CHANNEL_9          9
#define RZV_MHU_CHANNEL_9          9
#define RZV_MHU_CHANNEL_9          9

/* Maximum number of MHU channels */
#define RZV_MHU_MAX_CHANNELS       112

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_MHU_H */
