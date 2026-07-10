/*
 * arch/arm/src/rzv/rzv_poeg.c
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
 */

/****************************************************************************
 * POEG (Port Output Enable for GPT) driver for R9A09G057H (RZ/V2H).
 *
 * The POEG module forces GPT GTIOCA/GTIOCB outputs to a safe state
 * (inactive) when a hardware fault is detected (port input, I/O short
 * circuit, or software trigger).  This implements the PX4 arming safety
 * requirement: outputs must be forced safe within < 1 PWM cycle on fault.
 *
 * Hardware topology (R9A09G057H):
 *   POEG unit 0 (channels A-D) → protects GPT0-7  (unit0, 0x13010xxx)
 *   POEG unit 1 (channels A-D) → protects GPT10-17 (unit1, 0x13020xxx)
 *
 * Source: RZ/V2H hardware manual POEG chapter and spec.
 *
 * Usage:
 *   1. Call rzv_poeg_configure() once per POEG channel needed.
 *   2. To trigger software stop: rzv_poeg_software_stop().
 *   3. To release software stop: rzv_poeg_software_release().
 *   4. GPT GTINTAD.GRP field must be set to associate a GPT channel
 *      with a POEG group — done in rzv_gpt_start via GTINTAD config.
 *
 * Kconfig: CONFIG_RZV_POEG — disabled by default (opt-in per spec).
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#ifdef CONFIG_RZV_POEG

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>

#include <nuttx/arch.h>

#include "arm_internal.h"
#include "rzv_poeg.h"
#include "hardware/rzv_poeg.h"

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/* Validate unit and channel parameters at the API boundary. */
static int poeg_validate(uint8_t unit, uint8_t channel)
{
  if (unit >= RZV_POEG_MAX_UNITS)
    {
      return -EINVAL;
    }

  if (channel >= RZV_POEG_MAX_CHANNELS)
    {
      return -EINVAL;
    }

  return OK;
}

/* Return the POEGGn register address for a given unit/channel. */
static uintptr_t poeg_reg_addr(uint8_t unit, uint8_t channel)
{
  return RZV_POEG_POEGGn(unit, channel);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_poeg_configure
 *
 * Description:
 *   Configure a POEG channel.  Clears any pending fault flags then enables
 *   the requested detection sources.
 *
 * Parameters:
 *   unit     - POEG unit (0 = covers GPT0-7, 1 = covers GPT10-17)
 *   channel  - POEG channel within unit (RZV_POEG_CHANNEL_A .. _D)
 *   events   - Bitmask of POEG_EVENT_* flags to enable (0 = disable all)
 *   invert   - true to invert port input polarity
 *   nf_en    - true to enable noise filter on port input
 *
 * Returns:
 *   OK on success, negative errno on failure.
 *
 ****************************************************************************/

int rzv_poeg_configure(uint8_t unit, uint8_t channel,
                       uint32_t events, bool invert, bool nf_en)
{
  int ret = poeg_validate(unit, channel);

  if (ret < 0)
    {
      return ret;
    }

  uintptr_t reg = poeg_reg_addr(unit, channel);
  uint32_t  val = 0;

  /* Enable requested detection sources. */
  if (events & POEG_EVENT_PORT_INPUT)
    {
      val |= POEG_POEGGn_PIDE;
    }

  if (events & POEG_EVENT_SHORT_CIRCUIT)
    {
      val |= POEG_POEGGn_IOCE;
    }

  /* Optional polarity inversion. */
  if (invert)
    {
      val |= POEG_POEGGn_INV;
    }

  /* Optional noise filter on port input. */
  if (nf_en)
    {
      val |= POEG_POEGGn_NFEN;
    }

  /* Write configuration.  Clear flags implicitly (bits 0-1,3 must be 0 to
   * clear; writing 0 to status fields clears them per the hardware spec). */
  putreg32(val, reg);

  return OK;
}

/****************************************************************************
 * Name: rzv_poeg_software_stop
 *
 * Description:
 *   Trigger a software GPT output stop via POEG.  This sets SSF in POEGGn
 *   which immediately forces all associated GPT outputs to inactive state.
 *   Used by PX4 arming logic to safe motors on disarm.
 *
 * Parameters:
 *   unit    - POEG unit (0 or 1)
 *   channel - POEG channel (RZV_POEG_CHANNEL_A .. _D)
 *
 * Returns:
 *   OK on success, negative errno on failure.
 *
 ****************************************************************************/

int rzv_poeg_software_stop(uint8_t unit, uint8_t channel)
{
  int ret = poeg_validate(unit, channel);

  if (ret < 0)
    {
      return ret;
    }

  uintptr_t reg = poeg_reg_addr(unit, channel);

  /* Set SSF (software stop flag) — RMW to preserve enable bits. */
  uint32_t val = getreg32(reg);
  val |= POEG_POEGGn_SSF;
  putreg32(val, reg);

  return OK;
}

/****************************************************************************
 * Name: rzv_poeg_software_release
 *
 * Description:
 *   Release software stop by clearing SSF in POEGGn.  GPT outputs resume
 *   normal operation on the next counter start.
 *
 * Parameters:
 *   unit    - POEG unit (0 or 1)
 *   channel - POEG channel (RZV_POEG_CHANNEL_A .. _D)
 *
 * Returns:
 *   OK on success, negative errno on failure.
 *
 ****************************************************************************/

int rzv_poeg_software_release(uint8_t unit, uint8_t channel)
{
  int ret = poeg_validate(unit, channel);

  if (ret < 0)
    {
      return ret;
    }

  uintptr_t reg = poeg_reg_addr(unit, channel);

  /* Clear only SSF (software stop flag). Preserve PIDF and IOCF so that
   * hardware fault state remains visible to the caller (e.g. PX4 arming
   * logic).  Caller must explicitly clear PIDF/IOCF via rzv_poeg_clear_flags
   * after diagnosing the fault condition. */
  uint32_t val = getreg32(reg);
  val &= ~POEG_POEGGn_SSF;
  putreg32(val, reg);

  return OK;
}

/****************************************************************************
 * Name: rzv_poeg_get_status
 *
 * Description:
 *   Read the POEGGn register and return the raw value.  Callers can test
 *   POEG_STATUS_ANY_FAULT or individual flag bits.
 *
 * Parameters:
 *   unit    - POEG unit (0 or 1)
 *   channel - POEG channel (RZV_POEG_CHANNEL_A .. _D)
 *   status  - Output: raw POEGGn register value
 *
 * Returns:
 *   OK on success, negative errno on failure.
 *
 ****************************************************************************/

int rzv_poeg_get_status(uint8_t unit, uint8_t channel, uint32_t *status)
{
  if (status == NULL)
    {
      return -EINVAL;
    }

  int ret = poeg_validate(unit, channel);

  if (ret < 0)
    {
      return ret;
    }

  *status = getreg32(poeg_reg_addr(unit, channel));
  return OK;
}

/****************************************************************************
 * Name: rzv_poeg_clear_flags
 *
 * Description:
 *   Clear latched fault flags (PIDF, IOCF, SSF) without modifying enable
 *   bits.  Hardware requires writing 0 to the flag bits to clear them.
 *
 * Parameters:
 *   unit    - POEG unit (0 or 1)
 *   channel - POEG channel (RZV_POEG_CHANNEL_A .. _D)
 *
 * Returns:
 *   OK on success, negative errno on failure.
 *
 ****************************************************************************/

int rzv_poeg_clear_flags(uint8_t unit, uint8_t channel)
{
  int ret = poeg_validate(unit, channel);

  if (ret < 0)
    {
      return ret;
    }

  uintptr_t reg = poeg_reg_addr(unit, channel);

  /* RMW: preserve enable/config bits, clear all status flags. */
  uint32_t val = getreg32(reg);
  val &= ~(POEG_POEGGn_PIDF | POEG_POEGGn_IOCF | POEG_POEGGn_SSF);
  putreg32(val, reg);

  return OK;
}

#endif /* CONFIG_RZV_POEG */
