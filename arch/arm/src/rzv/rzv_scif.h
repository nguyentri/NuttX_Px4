/****************************************************************************
 * arch/arm/src/rzv/rzv_scif.h
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

#ifndef __ARCH_ARM_SRC_RZV_SCIF_H
#define __ARCH_ARM_SRC_RZV_SCIF_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SCIFA Base Addresses for RZV2H */

#ifndef RZV_SCIFA0_BASE
#  define RZV_SCIFA0_BASE              0x11C01400UL
#endif

/* Additional SCIFA channels (define as needed) */
/* RZV2H datasheet indicates only SCIFA0 for console UART */

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

#ifndef __ASSEMBLY__

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: arm_serialinit
 *
 * Description:
 *   Initialize serial drivers and register them with the serial upper half.
 *   This function is called from up_initialize() during boot.
 *
 ****************************************************************************/

void arm_serialinit(void);

/****************************************************************************
 * Name: up_putc
 *
 * Description:
 *   Provide priority, low-level access to the console for debug output.
 *   This function blocks until character transmission is complete.
 *
 * Input Parameters:
 *   ch - Character to output
 *
 * Returned Value:
 *   Sent character
 *
 ****************************************************************************/

int up_putc(int ch);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_RZV_SCIF_H */
