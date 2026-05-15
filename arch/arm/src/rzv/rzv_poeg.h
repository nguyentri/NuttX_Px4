/****************************************************************************
 * arch/arm/src/rzv/rzv_poeg.h
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

#ifndef __ARCH_ARM_SRC_RZV_RZV_POEG_H
#define __ARCH_ARM_SRC_RZV_RZV_POEG_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdbool.h>
#include <stdint.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* POEG event detection enable flags (for rzv_poeg_configure events param) */
#define POEG_EVENT_PORT_INPUT       (1u << 0)  /* Enable port-input fault detect */
#define POEG_EVENT_SHORT_CIRCUIT    (1u << 1)  /* Enable I/O short-circuit detect */

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef CONFIG_RZV_POEG

/**
 * rzv_poeg_configure - Configure a POEG channel.
 * @unit:    POEG unit: 0 = GPT0-7, 1 = GPT10-17
 * @channel: Channel within unit (0=A, 1=B, 2=C, 3=D)
 * @events:  OR of POEG_EVENT_* flags to enable; 0 = software-stop only
 * @invert:  true to invert port input polarity
 * @nf_en:   true to enable noise filter on port input
 * Returns 0 on success, negative errno on error.
 */
int rzv_poeg_configure(uint8_t unit, uint8_t channel,
                       uint32_t events, bool invert, bool nf_en);

/**
 * rzv_poeg_software_stop - Assert software GPT output stop immediately.
 * Forces all GPT outputs associated with this POEG channel to safe state.
 */
int rzv_poeg_software_stop(uint8_t unit, uint8_t channel);

/**
 * rzv_poeg_software_release - Release software stop, allow GPT to restart.
 */
int rzv_poeg_software_release(uint8_t unit, uint8_t channel);

/**
 * rzv_poeg_get_status - Read raw POEGGn register value.
 * @status: out — raw register value; test against POEG_POEGGn_* bits.
 */
int rzv_poeg_get_status(uint8_t unit, uint8_t channel, uint32_t *status);

/**
 * rzv_poeg_clear_flags - Clear latched PIDF/IOCF/SSF fault flags.
 */
int rzv_poeg_clear_flags(uint8_t unit, uint8_t channel);

#endif /* CONFIG_RZV_POEG */

#endif /* __ARCH_ARM_SRC_RZV_RZV_POEG_H */
