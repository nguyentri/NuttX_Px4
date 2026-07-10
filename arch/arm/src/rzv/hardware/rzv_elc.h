/****************************************************************************
 * arch/arm/src/rzv/hardware/rzv_elc.h
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

/* RZV2H ELC (Event Link Controller) Event ID Header
 *
 * All RZV_ELC_* numeric values come from rzv2h_irq.h which was derived from
 * the RZV2H Hardware User Manual Table 13.4.
 *
 * This header provides:
 *   1. ELC_EVENT_* aliases (enum-style defines) so that driver code written
 *      against those names compiles under NuttX.
 * 2. Per-peripheral event groups for -09 drivers.
 *
 * Usage:
 *   #include "hardware/rzv_elc.h"
 *   rzv_icu_attach(RZV_ELC_GTM0_GTMTINT, handler, arg, true);
 *   // or alias:
 *   rzv_icu_attach(ELC_EVENT_GTM0_INT, handler, arg, true);
 *
 * Consumers: (DMAC), (UART/SCI), (SCI-I2C),
 * (SPI), (GPT), (GTM/HRT).
 */

#ifndef __ARCH_ARM_SRC_RZV_HARDWARE_RZV_ELC_H
#define __ARCH_ARM_SRC_RZV_HARDWARE_RZV_ELC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/* All RZV_ELC_* numeric IDs are in rzv2h_irq.h */

#include <arch/rzv/rzv2h_irq.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* -------------------------------------------------------------------------
 * ELC_EVENT_* aliases (RZV2H event IDs)
 * -------------------------------------------------------------------------
 */

/* External pin interrupts (IRQ0-15) */

#define ELC_EVENT_IRQ0                RZV_ELC_IRQ0
#define ELC_EVENT_IRQ1                RZV_ELC_IRQ1
#define ELC_EVENT_IRQ2                RZV_ELC_IRQ2
#define ELC_EVENT_IRQ3                RZV_ELC_IRQ3
#define ELC_EVENT_IRQ4                RZV_ELC_IRQ4
#define ELC_EVENT_IRQ5                RZV_ELC_IRQ5
#define ELC_EVENT_IRQ6                RZV_ELC_IRQ6
#define ELC_EVENT_IRQ7                RZV_ELC_IRQ7
#define ELC_EVENT_IRQ8                RZV_ELC_IRQ8
#define ELC_EVENT_IRQ9                RZV_ELC_IRQ9
#define ELC_EVENT_IRQ10               RZV_ELC_IRQ10
#define ELC_EVENT_IRQ11               RZV_ELC_IRQ11
#define ELC_EVENT_IRQ12               RZV_ELC_IRQ12
#define ELC_EVENT_IRQ13               RZV_ELC_IRQ13
#define ELC_EVENT_IRQ14               RZV_ELC_IRQ14
#define ELC_EVENT_IRQ15               RZV_ELC_IRQ15

/* TINT0-31 (GPIO trigger input pins)
 * Note: TINT pins are NOT ELC events routed via INTR8SEL.
 * They are handled via INTC TSSR/TITSR registers → GIC SPI directly.
 * (GPIO) owns TINT routing; no ELC_EVENT_TINT* aliases here.
 * GPIO_TINT0_IRQn = 355 (first TINT SPI = 355).
 */
#define RZV_INTC_TINT_SPI_BASE        (355)  /* GPIO_TINT0_IRQn */
#define RZV_ICU_TINT_TO_IRQ(n)        (RZV_IRQ_FIRST + RZV_INTC_TINT_SPI_BASE + (n))

/* GTM timer interrupts (— HRT) */

#define ELC_EVENT_GTM0_INT            RZV_ELC_GTM0_GTMTINT
#define ELC_EVENT_GTM1_INT            RZV_ELC_GTM1_GTMTINT
#define ELC_EVENT_GTM2_INT            RZV_ELC_GTM2_GTMTINT
#define ELC_EVENT_GTM3_INT            RZV_ELC_GTM3_GTMTINT
#define ELC_EVENT_GTM4_INT            RZV_ELC_GTM4_GTMTINT
#define ELC_EVENT_GTM5_INT            RZV_ELC_GTM5_GTMTINT
#define ELC_EVENT_GTM6_INT            RZV_ELC_GTM6_GTMTINT
#define ELC_EVENT_GTM7_INT            RZV_ELC_GTM7_GTMTINT

/* DMAC1 completion */

#define ELC_EVENT_DMAC1_END0          RZV_ELC_DMAC1_DMAEND_0
#define ELC_EVENT_DMAC1_END1          RZV_ELC_DMAC1_DMAEND_1
#define ELC_EVENT_DMAC1_END2          RZV_ELC_DMAC1_DMAEND_2
#define ELC_EVENT_DMAC1_END3          RZV_ELC_DMAC1_DMAEND_3
#define ELC_EVENT_DMAC1_END4          RZV_ELC_DMAC1_DMAEND_4
#define ELC_EVENT_DMAC1_END5          RZV_ELC_DMAC1_DMAEND_5
#define ELC_EVENT_DMAC1_END6          RZV_ELC_DMAC1_DMAEND_6
#define ELC_EVENT_DMAC1_END7          RZV_ELC_DMAC1_DMAEND_7
#define ELC_EVENT_DMAC1_END8          RZV_ELC_DMAC1_DMAEND_8
#define ELC_EVENT_DMAC1_END9          RZV_ELC_DMAC1_DMAEND_9
#define ELC_EVENT_DMAC1_END10         RZV_ELC_DMAC1_DMAEND_10
#define ELC_EVENT_DMAC1_END11         RZV_ELC_DMAC1_DMAEND_11
#define ELC_EVENT_DMAC1_END12         RZV_ELC_DMAC1_DMAEND_12
#define ELC_EVENT_DMAC1_END13         RZV_ELC_DMAC1_DMAEND_13
#define ELC_EVENT_DMAC1_END14         RZV_ELC_DMAC1_DMAEND_14
#define ELC_EVENT_DMAC1_END15         RZV_ELC_DMAC1_DMAEND_15

/* RSCI/SCI-B UART events (/06) */

#define ELC_EVENT_SCI0_ERI            RZV_ELC_SC_ELCER_0    /* RSCI0 receive error */
#define ELC_EVENT_SCI0_RXI            RZV_ELC_SC_ELCRDRF_0  /* RSCI0 receive data full */
#define ELC_EVENT_SCI0_TXI            RZV_ELC_SC_ELCTDRE_0  /* RSCI0 transmit data empty */
#define ELC_EVENT_SCI0_TEI            RZV_ELC_SC_ELCTEND_0  /* RSCI0 transmit end */

#define ELC_EVENT_SCI1_ERI            RZV_ELC_SC_ELCER_1
#define ELC_EVENT_SCI1_RXI            RZV_ELC_SC_ELCRDRF_1
#define ELC_EVENT_SCI1_TXI            RZV_ELC_SC_ELCTDRE_1
#define ELC_EVENT_SCI1_TEI            RZV_ELC_SC_ELCTEND_1

#define ELC_EVENT_SCI2_ERI            RZV_ELC_SC_ELCER_2
#define ELC_EVENT_SCI2_RXI            RZV_ELC_SC_ELCRDRF_2
#define ELC_EVENT_SCI2_TXI            RZV_ELC_SC_ELCTDRE_2
#define ELC_EVENT_SCI2_TEI            RZV_ELC_SC_ELCTEND_2

#define ELC_EVENT_SCI3_ERI            RZV_ELC_SC_ELCER_3
#define ELC_EVENT_SCI3_RXI            RZV_ELC_SC_ELCRDRF_3
#define ELC_EVENT_SCI3_TXI            RZV_ELC_SC_ELCTDRE_3
#define ELC_EVENT_SCI3_TEI            RZV_ELC_SC_ELCTEND_3

#define ELC_EVENT_SCI4_ERI            RZV_ELC_SC_ELCER_4
#define ELC_EVENT_SCI4_RXI            RZV_ELC_SC_ELCRDRF_4
#define ELC_EVENT_SCI4_TXI            RZV_ELC_SC_ELCTDRE_4
#define ELC_EVENT_SCI4_TEI            RZV_ELC_SC_ELCTEND_4

/* RIIC/I2C events */

#define ELC_EVENT_RIIC0_ERI           RZV_ELC_RIIC_CH0_IIC_ELCERRP
#define ELC_EVENT_RIIC0_TXI           RZV_ELC_RIIC_CH0_IIC_ELCTDREP
#define ELC_EVENT_RIIC0_RXI           RZV_ELC_RIIC_CH0_IIC_ELCRDRFP
#define ELC_EVENT_RIIC0_TEI           RZV_ELC_RIIC_CH0_IIC_ELCTENDP

#define ELC_EVENT_RIIC1_ERI           RZV_ELC_RIIC_CH1_IIC_ELCERRP
#define ELC_EVENT_RIIC1_TXI           RZV_ELC_RIIC_CH1_IIC_ELCTDREP
#define ELC_EVENT_RIIC1_RXI           RZV_ELC_RIIC_CH1_IIC_ELCRDRFP
#define ELC_EVENT_RIIC1_TEI           RZV_ELC_RIIC_CH1_IIC_ELCTENDP

/* SCIF UART events (if using SCIF instead of SCI-B) */

#define ELC_EVENT_SCIF_TEI            RZV_ELC_UB1_TEI_N
#define ELC_EVENT_SCIF_RXI            RZV_ELC_UB1_RXI_EDGE_N
#define ELC_EVENT_SCIF_TXI            RZV_ELC_UB1_TXI_EDGE_N

/* -------------------------------------------------------------------------
 * SELECT interrupt GIC SPI constants (for -09 reference)
 * BSP_FEATURE_ICU_FIXED_INTSEL_COUNT = 353
 * -------------------------------------------------------------------------
 */

/* First GIC SPI used for INTR8SEL SELECT interrupts */
#define RZV_INTC_SEL_SPI_BASE         (353)

/* NuttX IRQ number for SELECT slot N:
 *   RZV_ICU_SLOT_TO_IRQ(n) = RZV_IRQ_FIRST + RZV_INTC_SEL_SPI_BASE + (n)
 */
#define RZV_ICU_SLOT_TO_IRQ(n)        (RZV_IRQ_FIRST + RZV_INTC_SEL_SPI_BASE + (n))

#endif /* __ARCH_ARM_SRC_RZV_HARDWARE_RZV_ELC_H */
