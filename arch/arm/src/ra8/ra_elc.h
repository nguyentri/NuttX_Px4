/****************************************************************************
 * arch/arm/src/ra8/ra_elc.h
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

#ifndef __ARCH_ARM_SRC_RA8_RA_ELC_H
#define __ARCH_ARM_SRC_RA8_RA_ELC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>

#include "chip.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ELC driver magic number for open state verification */

#define RA_ELC_OPEN_MAGIC    0x00454C43  /* "ELC" in ASCII */

/****************************************************************************
 * Public Types
 ****************************************************************************/

#ifndef __ASSEMBLY__

/* ELC peripheral enumeration - destination for event signals
 * These are indices into the ELSR register array (ELSR0-ELSR26 for RA8P1)
 */

enum ra_elc_peripheral_e
{
  RA_ELC_PERIPHERAL_GPT_A   = 0,   /* GPT A event input - ELSR0 */
  RA_ELC_PERIPHERAL_GPT_B   = 1,   /* GPT B event input - ELSR1 */
  RA_ELC_PERIPHERAL_GPT_C   = 2,   /* GPT C event input - ELSR2 */
  RA_ELC_PERIPHERAL_GPT_D   = 3,   /* GPT D event input - ELSR3 */
  RA_ELC_PERIPHERAL_GPT_E   = 4,   /* GPT E event input - ELSR4 */
  RA_ELC_PERIPHERAL_GPT_F   = 5,   /* GPT F event input - ELSR5 */
  RA_ELC_PERIPHERAL_GPT_G   = 6,   /* GPT G event input - ELSR6 */
  RA_ELC_PERIPHERAL_GPT_H   = 7,   /* GPT H event input - ELSR7 */
  RA_ELC_PERIPHERAL_DAC0    = 8,   /* DAC0 event input - ELSR8 */
  RA_ELC_PERIPHERAL_DAC1    = 9,   /* DAC1 event input - ELSR9 */
  RA_ELC_PERIPHERAL_IOPORT1 = 10,  /* IOPORT1 event input - ELSR10 */
  RA_ELC_PERIPHERAL_IOPORT2 = 11,  /* IOPORT2 event input - ELSR11 */
  RA_ELC_PERIPHERAL_IOPORT3 = 12,  /* IOPORT3 event input - ELSR12 */
  RA_ELC_PERIPHERAL_IOPORT4 = 13,  /* IOPORT4 event input - ELSR13 */
  RA_ELC_PERIPHERAL_ADC0    = 14,  /* ADC0 scan trigger A - ELSR14 */
  RA_ELC_PERIPHERAL_ADC0_B  = 15,  /* ADC0 scan trigger B - ELSR15 */
  RA_ELC_PERIPHERAL_ADC0_C  = 16,  /* ADC0 scan trigger C - ELSR16 */
  RA_ELC_PERIPHERAL_ADC1    = 17,  /* ADC1 scan trigger A - ELSR17 */
  RA_ELC_PERIPHERAL_ADC1_B  = 18,  /* ADC1 scan trigger B - ELSR18 */
  RA_ELC_PERIPHERAL_ADC1_C  = 19,  /* ADC1 scan trigger C - ELSR19 */
  RA_ELC_PERIPHERAL_ADC2    = 20,  /* ADC2 scan trigger A - ELSR20 */
  RA_ELC_PERIPHERAL_ADC2_B  = 21,  /* ADC2 scan trigger B - ELSR21 */
  RA_ELC_PERIPHERAL_ADC2_C  = 22,  /* ADC2 scan trigger C - ELSR22 */
  RA_ELC_PERIPHERAL_I3C     = 23,  /* I3C event input - ELSR23 */
  RA_ELC_PERIPHERAL_GPTP0   = 24,  /* gPTP 0 event input - ELSR24 */
  RA_ELC_PERIPHERAL_GPTP1   = 25,  /* gPTP 1 event input - ELSR25 */
  RA_ELC_PERIPHERAL_MAX     = 26,  /* Maximum peripheral index */
};

typedef enum ra_elc_peripheral_e ra_elc_peripheral_t;

/* ELC software event enumeration */

enum ra_elc_software_event_e
{
  RA_ELC_SOFTWARE_EVENT_0 = 0,  /* Software event 0 */
  RA_ELC_SOFTWARE_EVENT_1 = 1,  /* Software event 1 */
  RA_ELC_SOFTWARE_EVENT_2 = 2,  /* Software event 2 */
  RA_ELC_SOFTWARE_EVENT_3 = 3,  /* Software event 3 */
};

typedef enum ra_elc_software_event_e ra_elc_software_event_t;

/* ELC event signal type - these are source events from peripherals
 * Event numbers are defined in ra8p1_irq.h as RA_ELC_* macros
 */

typedef uint16_t ra_elc_event_t;

/* ELC link configuration structure */

struct ra_elc_link_s
{
  ra_elc_peripheral_t peripheral;  /* Target peripheral */
  ra_elc_event_t      event;       /* Source event signal */
};

/* ELC configuration structure for initialization */

struct ra_elc_config_s
{
  uint8_t                      nlinks;   /* Number of links in the array */
  const struct ra_elc_link_s  *links;    /* Array of link configurations */
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Name: ra_elc_initialize
 *
 * Description:
 *   Initialize the Event Link Controller (ELC) module.
 *   This function enables the ELC module clock and prepares it for use.
 *   Call this function once during system initialization before using
 *   any other ELC functions.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_elc_initialize(void);

/****************************************************************************
 * Name: ra_elc_uninitialize
 *
 * Description:
 *   Uninitialize the Event Link Controller (ELC) module.
 *   This function disables all ELC links and turns off the ELC module clock.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_elc_uninitialize(void);

/****************************************************************************
 * Name: ra_elc_enable
 *
 * Description:
 *   Enable the global operation of the Event Link Controller.
 *   After enabling, configured event links will be active.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_elc_enable(void);

/****************************************************************************
 * Name: ra_elc_disable
 *
 * Description:
 *   Disable the global operation of the Event Link Controller.
 *   After disabling, no event links will be processed.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_elc_disable(void);

/****************************************************************************
 * Name: ra_elc_link_set
 *
 * Description:
 *   Create a single event link between a source event and a target
 *   peripheral. The event signal will be routed to the specified
 *   peripheral whenever the source event occurs.
 *
 * Input Parameters:
 *   peripheral - Target peripheral to receive the event signal
 *   event      - Source event signal (use RA_ELC_* macros from ra8p1_irq.h)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 * Example:
 *   Link GPT0 counter overflow to ADC0 scan trigger:
 *   ra_elc_link_set(RA_ELC_PERIPHERAL_ADC0, RA_ELC_GPT0_COUNTER_OVERFLOW);
 *
 ****************************************************************************/

int ra_elc_link_set(ra_elc_peripheral_t peripheral, ra_elc_event_t event);

/****************************************************************************
 * Name: ra_elc_link_break
 *
 * Description:
 *   Break (disable) an existing event link for the specified peripheral.
 *   After calling this function, no events will be routed to the peripheral.
 *
 * Input Parameters:
 *   peripheral - Peripheral whose event link should be broken
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_elc_link_break(ra_elc_peripheral_t peripheral);

/****************************************************************************
 * Name: ra_elc_software_event_generate
 *
 * Description:
 *   Generate a software event. This can be used to trigger peripherals
 *   that are linked to software event sources (RA_ELC_ELC_SOFTWARE_EVENT_x).
 *
 * Input Parameters:
 *   event_num - Software event number (0-3)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 * Note:
 *   The peripheral must be linked to the corresponding software event
 *   (e.g., RA_ELC_ELC_SOFTWARE_EVENT_0 = 0x0CC) before this call will
 *   have any effect.
 *
 ****************************************************************************/

int ra_elc_software_event_generate(ra_elc_software_event_t event_num);

/****************************************************************************
 * Name: ra_elc_configure
 *
 * Description:
 *   Configure multiple ELC links at once. This is useful for setting up
 *   multiple event links during initialization.
 *
 * Input Parameters:
 *   config - Pointer to configuration structure containing link array
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_elc_configure(const struct ra_elc_config_s *config);

/****************************************************************************
 * Name: ra_elc_link_get
 *
 * Description:
 *   Get the current event linked to a peripheral.
 *
 * Input Parameters:
 *   peripheral - Peripheral to query
 *   event      - Pointer to store the current event value
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int ra_elc_link_get(ra_elc_peripheral_t peripheral, ra_elc_event_t *event);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_RA8_RA_ELC_H */
