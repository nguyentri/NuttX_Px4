/****************************************************************************
 * arch/arm/src/ra8/ra_mipi_csi.h
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

#ifndef __ARCH_ARM_SRC_RA8_RA_MIPI_CSI_H
#define __ARCH_ARM_SRC_RA8_RA_MIPI_CSI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/fs/ioctl.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* IOCTL Commands */

#define CAM_CMD_SET_RESOLUTION  _IOC(0x0001, 0)
#define CAM_CMD_START_STREAM    _IOC(0x0002, 0)
#define CAM_CMD_STOP_STREAM     _IOC(0x0003, 0)
#define CAM_CMD_GET_FRAME_INFO  _IOC(0x0004, 0)

/* Frame Info Structure */

struct cam_frame_info_s
{
  uint32_t width;
  uint32_t height;
  uint32_t format; /* 0: RGB888, 1: RGB565 */
  uint32_t size;
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifndef __ASSEMBLY__

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Name: ra_mipi_csi_initialize
 *
 * Description:
 *   Initialize the MIPI-CSI and VIN driver.
 *
 ****************************************************************************/

int ra_mipi_csi_initialize(void);

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_RA8_RA_MIPI_CSI_H */
