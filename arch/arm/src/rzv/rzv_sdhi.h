/****************************************************************************
 * arch/arm/src/rzv/rzv_sdhi.h
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

/* Public API for the RZ/V2H SDHI lower-half driver.
 * Caller (board glue) uses rzv_sdhi_initialize() to obtain a struct sdio_dev_s
 * pointer, then passes it to mmcsd_slotinitialize().
 */

#ifndef __ARCH_ARM_SRC_RZV_RZV_SDHI_H
#define __ARCH_ARM_SRC_RZV_RZV_SDHI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/sdio.h>

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef CONFIG_RZV_SDHI

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
 * Name: rzv_sdhi_initialize
 *
 * Description:
 *   Initialize the RZ/V2H SDHI controller for the specified slot.
 *   Returns an SDIO lower-half interface suitable for mmcsd_slotinitialize().
 *
 * Input Parameters:
 *   slot - SDHI slot number (0 = SD0 / RDK-RZV2H SD card connector)
 *
 * Returned Value:
 *   Pointer to struct sdio_dev_s on success; NULL on failure.
 *
 ****************************************************************************/

struct sdio_dev_s *rzv_sdhi_initialize(int slot);

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_RZV_SDHI */
#endif /* __ARCH_ARM_SRC_RZV_RZV_SDHI_H */
