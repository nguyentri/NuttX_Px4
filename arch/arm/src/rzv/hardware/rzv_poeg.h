/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_poega.h
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

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_POEGA_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_POEGA_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* POEGA POEGGn Register Bit Definitions *****************************/

#define POEGA_POEGGn_PIDF                       (1 << 0)  /* Pidf */

#define POEGA_POEGGn_IOCF                       (1 << 1)  /* Iocf */

#define POEGA_POEGGn_SSF                        (1 << 3)  /* Ssf */

#define POEGA_POEGGn_PIDE                       (1 << 4)  /* Pide */

#define POEGA_POEGGn_IOCE                       (1 << 5)  /* Ioce */

#define POEGA_POEGGn_ST                         (1 << 16)  /* St */

#define POEGA_POEGGn_INV                        (1 << 28)  /* Inv */

#define RZV_POEG_CHANNEL_0    0
#define RZV_POEG_CHANNEL_1    1
#define RZV_POEG_CHANNEL_2    2
#define RZV_POEG_CHANNEL_3    3

/* Maximum number of POEG channels *******************************************/

#define RZV_POEG_MAX_CHANNELS 4

/* POEG Event Detection Types ***********************************************/

#define POEG_EVENT_PORT_INPUT   (1 << 0)  /* Port input detection */
#define POEG_EVENT_SHORT_CIRCUIT (1 << 1) /* Output short-circuit detection */
#define POEG_EVENT_SOFTWARE     (1 << 2)  /* Software stop */

/* POEG Status Flags ********************************************************/

#define POEG_STATUS_PORT_INPUT_DETECTED     POEG_POEGG_PIDF
#define POEG_STATUS_SHORT_CIRCUIT_DETECTED  POEG_POEGG_IOCF
#define POEG_STATUS_SOFTWARE_STOP           POEG_POEGG_SSF
#define POEG_STATUS_GPT_STOPPED             POEG_POEGG_ST

/* POEG Enable Flags ********************************************************/

#define POEG_ENABLE_PORT_INPUT_DETECTION    POEG_POEGG_PIDE
#define POEG_ENABLE_SHORT_CIRCUIT_DETECTION POEG_POEGG_IOCE
#define POEG_ENABLE_NOISE_FILTER            POEG_POEGG_NFEN

/* POEG Configuration Flags *************************************************/

#define POEG_CONFIG_INVERT_INPUT            POEG_POEGG_INV

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_POEGA_H */
