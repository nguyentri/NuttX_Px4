/****************************************************************************
 * arch/arm/src/rzv/rzv_icu.h
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

/* RZV2H Interrupt Architecture Overview
 *
 * The RZV2H uses a multi-layered interrupt system:
 *
 * 1. **Peripherals** generate interrupt events (ELC events 0x0-0x3FF)
 *
 * 2. **ICU (Interrupt Control Unit)** - Handles external interrupt preprocessing
 *    - NMI, IRQ0-15, TINT0-31 status and configuration
 *    - Base: 0x10400000 (INTC base; ICU regs at INTC offsets 0x0000-0x004C)
 *    - Does NOT route peripheral events to GIC
 *
 * 3. **INTC (Interrupt Controller)** - Routes events to CPU cores
 *    - INTR8SEL[0-42] registers: Map ELC events → GIC SPI interrupts
 *    - Base: 0x10400000
 *    - This is what NuttX ICU driver manages for dynamic allocation
 *
 * 4. **GIC (Generic Interrupt Controller)** - CPU-level interrupt management
 *    - Receives SPI interrupts from INTC
 *    - Handles priority, masking, acknowledgment
 *
 * Interrupt Flow:
 *   Peripheral Event → INTC INTR8SEL[slot] → GIC SPI[353+slot] → CPU → Handler
 *
 * Slot→IRQ mapping:
 *   ICU_FIXED_INTSEL_COUNT = 353 (first SELECT SPI INTID per RZ/V2H UM).
 *   INTR8SEL slot N → GIC SPI INTID (353+N) → NuttX IRQ index == GIC INTID.
 *   rzv_icu_attach() returns NuttX IRQ (= GIC INTID = 353+N); callers must
 *   use that value for up_enable_irq/up_disable_irq and irq_detach.
 *   Do NOT add RZV_IRQ_FIRST — it was already double-counted.
 *
 * Usage Example:
 *   int irq = rzv_icu_attach(RZV_ELC_SCI0_RXI, uart_handler, &dev, true);
 *   // Later:
 *   rzv_icu_detach(irq);
 */

#ifndef __ARCH_ARM_SRC_RZV_ICU_H
#define __ARCH_ARM_SRC_RZV_ICU_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>
#include <nuttx/irq.h>

/****************************************************************************
 * Public Data
 ****************************************************************************/

/* ICU detection modes */

#define RZV_ICU_IRQ_LEVEL_LOW        0x00  /* Level-triggered (low) */
#define RZV_ICU_IRQ_EDGE_FALLING     0x01  /* Edge-triggered (falling) */
#define RZV_ICU_IRQ_EDGE_RISING      0x02  /* Edge-triggered (rising) */
#define RZV_ICU_IRQ_EDGE_BOTH        0x03  /* Edge-triggered (both) */

/* ICU filter clock selections */

#define RZV_ICU_FILTER_PCLK_DIV_1    0x00  /* PCLKB */
#define RZV_ICU_FILTER_PCLK_DIV_8    0x01  /* PCLKB/8 */
#define RZV_ICU_FILTER_PCLK_DIV_32   0x02  /* PCLKB/32 */
#define RZV_ICU_FILTER_PCLK_DIV_64   0x03  /* PCLKB/64 */


/* Bit Rate Calculation Constants ******************************************/

/* PCLK frequency (assumed 200 MHz for RZV2H) */
#define RIIC_PCLK_FREQ           200000000

/* Standard mode (100 kHz) bit rate settings */
#define RIIC_BRH_100K            0x1F
#define RIIC_BRL_100K            0x1F
#define RIIC_CKS_100K            0x02  /* PCLK/4 */

/* Fast mode (400 kHz) bit rate settings */
#define RIIC_BRH_400K            0x0B
#define RIIC_BRL_400K            0x11
#define RIIC_CKS_400K            0x01  /* PCLK/2 */

/* Fast mode plus (1 MHz) bit rate settings */
#define RIIC_BRH_1M              0x02
#define RIIC_BRL_1M              0x05
#define RIIC_CKS_1M              0x00  /* PCLK/1 */


/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/* ICU Core API */

/****************************************************************************
 * Name: rzv_icu_initialize
 *
 * Description:
 *   Initialize the ICU driver. Must be called once during system startup
 *   before any other ICU functions. Clears all slot allocations and
 *   prepares the driver for runtime interrupt registration.
 *
 ****************************************************************************/

void rzv_icu_initialize(void);

/****************************************************************************
 * Name: rzv_icu_clear_irq
 *
 * Description:
 *   Clear interrupt request status. On RZV2H with GIC, this is handled
 *   automatically by the hardware and peripheral drivers.
 *
 * Input Parameters:
 *   irq - IRQ number
 *
 ****************************************************************************/

void rzv_icu_clear_irq(int irq);

/****************************************************************************
 * Name: rzv_icu_attach
 *
 * Description:
 *   Attach an interrupt handler to a peripheral event at runtime.
 *   Automatically allocates a slot, configures event routing via INTR8SEL,
 *   and optionally enables the interrupt.
 *
 * Input Parameters:
 *   event      - ELC event number (RZV_ELC_* from rzv2h_irq.h)
 *   handler    - Interrupt handler function
 *   arg        - Argument to pass to handler
 *   irq_enable - If true, enable the IRQ immediately
 *
 * Returned Value:
 *   On success, returns NuttX IRQ (GIC INTID = 353 + slot).
 *   On failure, returns a negated errno value:
 *     -ENOMEM: No more slots available
 *
 * Example:
 *   int irq = rzv_icu_attach(RZV_ELC_SCI0_RXI, uart_rx_isr, &g_uart0, true);
 *
 ****************************************************************************/

int rzv_icu_attach(int event, xcpt_t handler, void *arg, bool irq_enable);

/****************************************************************************
 * Name: rzv_icu_detach
 *
 * Description:
 *   Detach an interrupt handler and free the allocated slot.
 *   Disables the IRQ and clears the event routing configuration.
 *
 * Input Parameters:
 *   icu_irq - IRQ number returned by rzv_icu_attach()
 *
 * Returned Value:
 *   OK on success; negated errno on failure
 *
 ****************************************************************************/

int rzv_icu_detach(int icu_irq);

/****************************************************************************
 * Name: rzv_icu_set_priority
 *
 * Description:
 *   Set interrupt priority for a dynamically allocated ICU IRQ.
 *   Controls GIC priority for precise interrupt prioritization.
 *
 * Input Parameters:
 *   icu_irq  - IRQ number returned by rzv_icu_attach()
 *   priority - Priority level (0-31, where 0 = highest priority)
 *              GIC implements 5-bit priority in bits[7:3]
 *
 * Returned Value:
 *   OK on success; negated errno on failure:
 *     -EINVAL: Invalid IRQ number or priority out of range
 *     -ENOSYS: Priority control not enabled (CONFIG_ARCH_IRQPRIO)
 *
 * Example:
 *   int irq = rzv_icu_attach(RZV_ELC_GTM0_GTMTINT, timer_isr, &dev, false);
 *   rzv_icu_set_priority(irq, 5);  // High priority
 *   up_enable_irq(irq);
 *
 ****************************************************************************/

int rzv_icu_set_priority(int icu_irq, int priority);

/****************************************************************************
 * Name: rzv_icu_set_event
 *
 * Description:
 *   Configure a specific slot to route an ELC event to a GIC interrupt.
 *   Normally called internally by rzv_icu_attach(), but can be used
 *   directly for advanced use cases.
 *
 * Input Parameters:
 *   icu_slot - Slot number (0-95)
 *   event    - ELC event number to route to this slot
 *
 * Returned Value:
 *   OK on success; negated errno on failure
 *
 ****************************************************************************/

int rzv_icu_set_event(int icu_slot, int event);

/****************************************************************************
 * Name: rzv_icu_filter_config
 *
 * Description:
 *   Configure external interrupt pin trigger and filter settings.
 *   Used for TINT (external interrupt) pins.
 *
 * Input Parameters:
 *   icu_irq       - TINT pin number (0-31)
 *   mode          - Trigger mode (RZV_ICU_IRQ_*)
 *   filter_enable - Enable digital noise filter
 *   filter_clock  - Filter clock divider (RZV_ICU_FILTER_PCLK_DIV_*)
 *
 * Returned Value:
 *   OK on success; negated errno on failure
 *
 ****************************************************************************/

int rzv_icu_filter_config(int icu_irq, uint8_t mode, bool filter_enable, uint8_t filter_clock);

/****************************************************************************
 * IRQ Control Functions
 *
 * Description:
 *   Functions to configure and manage external IRQ0-15 pins handled by
 *   the ICU module. These are independent of event routing done by INTC.
 *
 ****************************************************************************/

/* Set IRQ detection method (edge/level sensitivity) */

int rzv_icu_set_irq_detect(int irq_num, uint8_t mode);

/* Configure IRQ digital filter */

int rzv_icu_set_irq_filter(int irq_num, uint8_t filter_clock);

/* Get/clear IRQ status */

uint16_t rzv_icu_get_irq_status(void);
void rzv_icu_clear_irq_status(uint16_t irq_mask);

/****************************************************************************
 * NMI Control Functions
 *
 * Description:
 *   Functions to manage Non-Maskable Interrupt (NMI) in the ICU module.
 *
 ****************************************************************************/

void rzv_icu_clear_nmi_status(uint16_t mask);
bool rzv_icu_get_nmi_status(void);
int rzv_icu_set_nmi_filter(bool filter_enable, uint8_t filter_clock);

/* Legacy NMI functions (placeholders) */

void rzv_icu_enable_nmi(uint16_t mask);
void rzv_icu_disable_nmi(uint16_t mask);

/****************************************************************************
 * Wakeup Control Functions
 *
 * Description:
 *   Functions for wakeup interrupt management (future implementation).
 *
 ****************************************************************************/

void rzv_icu_enable_wakeup(uint32_t mask);
void rzv_icu_disable_wakeup(uint32_t mask);

/****************************************************************************
 * Name: rzv_gic_set_irq_type
 *
 * Description:
 *   Configure GIC ICDICFR edge/level type for a SPI interrupt.
 * GIC must be configured for edge when ICU IITSR is set to
 *   edge mode; otherwise the GIC line hangs on first edge assertion.
 *
 * Input Parameters:
 *   irq  - GIC INTID (NuttX IRQ number)
 *   edge - true = edge-triggered, false = level-sensitive
 *
 ****************************************************************************/

void rzv_gic_set_irq_type(int irq, bool edge);

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RZV_ICU_H */