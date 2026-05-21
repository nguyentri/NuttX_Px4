/****************************************************************************
 * arch/arm/src/ra8/ra_cac.h
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

#ifndef __ARCH_ARM_SRC_RA8_RA_CAC_H
#define __ARCH_ARM_SRC_RA8_RA_CAC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/fs/ioctl.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* IOCTL Commands - Use character driver base (0x0400) + offset for CAC */

#define CACIOC_START        (_DIOCBASE + 0x80)  /* Arg: None */
#define CACIOC_STOP         (_DIOCBASE + 0x81)  /* Arg: None */
#define CACIOC_GET_STATUS   (_DIOCBASE + 0x82)  /* Arg: uint32_t* pointer to status */
#define CACIOC_SET_CONFIG   (_DIOCBASE + 0x83)  /* Arg: struct ra_cac_config_s* */
#define CACIOC_READ_COUNTER (_DIOCBASE + 0x84)  /* Arg: uint16_t* pointer to CACNTBR value */

/* Status Flags */
#define RA_CAC_STATUS_FERRF (1 << 0) /* Frequency Error */
#define RA_CAC_STATUS_MENDF (1 << 1) /* Measurement End */
#define RA_CAC_STATUS_OVFF  (1 << 2) /* Overflow */

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* CAC Configuration Structure */
struct ra_cac_config_s
{
  uint8_t  meas_clock;      /* Measurement Target Clock Select (FMCS) */
  uint8_t  meas_div;        /* Measurement Target Clock Division (TCSS) */
  uint8_t  meas_edge;       /* Valid Edge Select (EDGES) for measurement clock */
  uint8_t  ref_clock;       /* Measurement Reference Clock Select (RSCS) */
  uint8_t  ref_div;         /* Measurement Reference Clock Division (RCDS) */
  uint8_t  ref_digfilter;   /* Digital Filter Selection (DFS) */
  uint8_t  ref_edge;        /* Reference Edge Select (for CACREF pin or internal) */
  bool     ref_use_external; /* Reference Signal Select (RPS): false=Internal clock, true=CACREF pin */
  bool     ref_input_enable; /* CACREF Pin Input Enable (CACREFE) - must be true if ref_use_external=true */

  uint16_t upper_limit;     /* CAULVR */
  uint16_t lower_limit;     /* CALLVR */
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: ra_cac_initialize
 *
 * Description:
 *   Initialize the CAC driver and register the /dev/cac0 device.
 *
 ****************************************************************************/

int ra_cac_initialize(void);

#endif /* __ARCH_ARM_SRC_RA8_RA_CAC_H */
