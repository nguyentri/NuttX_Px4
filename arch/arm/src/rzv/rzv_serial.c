/****************************************************************************
 * arch/arm/src/rzv/rzv_serial.c
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/serial/serial.h>

#include "arm_internal.h"
#include "chip.h"
#include "rzv_clock.h"
#include "rzv_icu.h"
#include "hardware/rzv_sci.h"
#include <arch/rzv/rzv2h_irq.h>

#if defined(CONFIG_SERIAL_TXDMA) || defined(CONFIG_SERIAL_RXDMA)
#  include "rzv_dmac.h"
#endif

#ifdef USE_SERIALDRIVER

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* FIFO Mode Configuration */
#if defined(CONFIG_RZV_SCI_FIFO_MODE)
/* Set Trigger levels and release reset
 * For RZV2H SCI-B with 16-byte FIFO:
 * RTRG: RX trigger level (configurable via Kconfig, default: 1 for low latency)
 * TTRG: TX trigger level (configurable via Kconfig, default: 15 for efficiency)
 * RSTRG: RTS flow control trigger (set to 15 = fifo_depth - 1)
 *
 * RX interrupt triggers when: count >= RTRG or timeout after 15 bit times
 * TX interrupt triggers when: count <= TTRG (free space available)
 */
#ifndef CONFIG_RZV_SCI_FIFO_RX_TRIGGER
#  define CONFIG_RZV_SCI_FIFO_RX_TRIGGER 1  /* Default: trigger on 1 byte */
#endif
#ifndef CONFIG_RZV_SCI_FIFO_TX_TRIGGER
#  define CONFIG_RZV_SCI_FIFO_TX_TRIGGER 15 /* Default: trigger when <=15 in FIFO */
#endif
#endif

/* DMA buffer sizes */
#ifdef CONFIG_SERIAL_RXDMA
#  ifndef CONFIG_RZV_SERIAL_RXDMA_BUFFER_SIZE
#    define CONFIG_RZV_SERIAL_RXDMA_BUFFER_SIZE 256
#  endif
#endif

/* Console configuration */

#if defined(CONFIG_SCI0_SERIAL_CONSOLE)
#  define CONSOLE_DEV     g_sci0port  /* SCI0 is console */
#  define TTYS0_DEV       g_sci0port  /* SCI0 is ttyS0 */
#  define SCI0_ASSIGNED   1
#elif defined(CONFIG_SCI1_SERIAL_CONSOLE)
#  define CONSOLE_DEV     g_sci1port  /* SCI1 is console */
#  define TTYS0_DEV       g_sci1port  /* SCI1 is ttyS0 */
#  define SCI1_ASSIGNED   1
#elif defined(CONFIG_SCI2_SERIAL_CONSOLE)
#  define CONSOLE_DEV     g_sci2port  /* SCI2 is console */
#  define TTYS0_DEV       g_sci2port  /* SCI2 is ttyS0 */
#  define SCI2_ASSIGNED   1
#elif defined(CONFIG_SCI3_SERIAL_CONSOLE)
#  define CONSOLE_DEV     g_sci3port  /* SCI3 is console */
#  define TTYS0_DEV       g_sci3port  /* SCI3 is ttyS0 */
#  define SCI3_ASSIGNED   1
#elif defined(CONFIG_SCI4_SERIAL_CONSOLE)
#  define CONSOLE_DEV     g_sci4port  /* SCI4 is console */
#  define TTYS0_DEV       g_sci4port  /* SCI4 is ttyS0 */
#  define SCI4_ASSIGNED   1
#elif defined(CONFIG_SCI5_SERIAL_CONSOLE)
#  define CONSOLE_DEV     g_sci5port  /* SCI5 is console */
#  define TTYS0_DEV       g_sci5port  /* SCI5 is ttyS0 */
#  define SCI5_ASSIGNED   1
#elif defined(CONFIG_SCI6_SERIAL_CONSOLE)
#  define CONSOLE_DEV     g_sci6port  /* SCI6 is console */
#  define TTYS0_DEV       g_sci6port  /* SCI6 is ttyS0 */
#  define SCI6_ASSIGNED   1
#elif defined(CONFIG_SCI7_SERIAL_CONSOLE)
#  define CONSOLE_DEV     g_sci7port  /* SCI7 is console */
#  define TTYS0_DEV       g_sci7port  /* SCI7 is ttyS0 */
#  define SCI7_ASSIGNED   1
#elif defined(CONFIG_SCI8_SERIAL_CONSOLE)
#  define CONSOLE_DEV     g_sci8port  /* SCI8 is console */
#  define TTYS0_DEV       g_sci8port  /* SCI8 is ttyS0 */
#  define SCI8_ASSIGNED   1
#elif defined(CONFIG_SCI9_SERIAL_CONSOLE)
#  define CONSOLE_DEV     g_sci9port  /* SCI9 is console */
#  define TTYS0_DEV       g_sci9port  /* SCI9 is ttyS0 */
#  define SCI9_ASSIGNED   1
#endif

/* Pick ttys1-9 */

#if defined(CONFIG_RZV_SCI0) && !defined(SCI0_ASSIGNED)
#  define TTYS1_DEV       g_sci0port  /* SCI0 is ttyS1 */
#  define SCI0_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI1) && !defined(SCI1_ASSIGNED)
#  define TTYS1_DEV       g_sci1port  /* SCI1 is ttyS1 */
#  define SCI1_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI2) && !defined(SCI2_ASSIGNED)
#  define TTYS1_DEV       g_sci2port  /* SCI2 is ttyS1 */
#  define SCI2_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI3) && !defined(SCI3_ASSIGNED)
#  define TTYS1_DEV       g_sci3port  /* SCI3 is ttyS1 */
#  define SCI3_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI4) && !defined(SCI4_ASSIGNED)
#  define TTYS1_DEV       g_sci4port  /* SCI4 is ttyS1 */
#  define SCI4_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI5) && !defined(SCI5_ASSIGNED)
#  define TTYS1_DEV       g_sci5port  /* SCI5 is ttyS1 */
#  define SCI5_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI6) && !defined(SCI6_ASSIGNED)
#  define TTYS1_DEV       g_sci6port  /* SCI6 is ttyS1 */
#  define SCI6_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI7) && !defined(SCI7_ASSIGNED)
#  define TTYS1_DEV       g_sci7port  /* SCI7 is ttyS1 */
#  define SCI7_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI8) && !defined(SCI8_ASSIGNED)
#  define TTYS1_DEV       g_sci8port  /* SCI8 is ttyS1 */
#  define SCI8_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI9) && !defined(SCI9_ASSIGNED)
#  define TTYS1_DEV       g_sci9port  /* SCI9 is ttyS1 */
#  define SCI9_ASSIGNED   1
#endif

#if defined(CONFIG_RZV_SCI0) && !defined(SCI0_ASSIGNED)
#  define TTYS2_DEV       g_sci0port  /* SCI0 is ttyS2 */
#  define SCI0_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI1) && !defined(SCI1_ASSIGNED)
#  define TTYS2_DEV       g_sci1port  /* SCI1 is ttyS2 */
#  define SCI1_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI2) && !defined(SCI2_ASSIGNED)
#  define TTYS2_DEV       g_sci2port  /* SCI2 is ttyS2 */
#  define SCI2_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI3) && !defined(SCI3_ASSIGNED)
#  define TTYS2_DEV       g_sci3port  /* SCI3 is ttyS2 */
#  define SCI3_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI4) && !defined(SCI4_ASSIGNED)
#  define TTYS2_DEV       g_sci4port  /* SCI4 is ttyS2 */
#  define SCI4_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI5) && !defined(SCI5_ASSIGNED)
#  define TTYS2_DEV       g_sci5port  /* SCI5 is ttyS2 */
#  define SCI5_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI6) && !defined(SCI6_ASSIGNED)
#  define TTYS2_DEV       g_sci6port  /* SCI6 is ttyS2 */
#  define SCI6_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI7) && !defined(SCI7_ASSIGNED)
#  define TTYS2_DEV       g_sci7port  /* SCI7 is ttyS2 */
#  define SCI7_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI8) && !defined(SCI8_ASSIGNED)
#  define TTYS2_DEV       g_sci8port  /* SCI8 is ttyS2 */
#  define SCI8_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI9) && !defined(SCI9_ASSIGNED)
#  define TTYS2_DEV       g_sci9port  /* SCI9 is ttyS2 */
#  define SCI9_ASSIGNED   1
#endif

#if defined(CONFIG_RZV_SCI0) && !defined(SCI0_ASSIGNED)
#  define TTYS3_DEV       g_sci0port  /* SCI0 is ttyS3 */
#  define SCI0_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI1) && !defined(SCI1_ASSIGNED)
#  define TTYS3_DEV       g_sci1port  /* SCI1 is ttyS3 */
#  define SCI1_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI2) && !defined(SCI2_ASSIGNED)
#  define TTYS3_DEV       g_sci2port  /* SCI2 is ttyS3 */
#  define SCI2_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI3) && !defined(SCI3_ASSIGNED)
#  define TTYS3_DEV       g_sci3port  /* SCI3 is ttyS3 */
#  define SCI3_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI4) && !defined(SCI4_ASSIGNED)
#  define TTYS3_DEV       g_sci4port  /* SCI4 is ttyS3 */
#  define SCI4_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI5) && !defined(SCI5_ASSIGNED)
#  define TTYS3_DEV       g_sci5port  /* SCI5 is ttyS3 */
#  define SCI5_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI6) && !defined(SCI6_ASSIGNED)
#  define TTYS3_DEV       g_sci6port  /* SCI6 is ttyS3 */
#  define SCI6_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI7) && !defined(SCI7_ASSIGNED)
#  define TTYS3_DEV       g_sci7port  /* SCI7 is ttyS3 */
#  define SCI7_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI8) && !defined(SCI8_ASSIGNED)
#  define TTYS3_DEV       g_sci8port  /* SCI8 is ttyS3 */
#  define SCI8_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI9) && !defined(SCI9_ASSIGNED)
#  define TTYS3_DEV       g_sci9port  /* SCI9 is ttyS3 */
#  define SCI9_ASSIGNED   1
#endif

#if defined(CONFIG_RZV_SCI0) && !defined(SCI0_ASSIGNED)
#  define TTYS4_DEV       g_sci0port  /* SCI0 is ttyS4 */
#  define SCI0_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI1) && !defined(SCI1_ASSIGNED)
#  define TTYS4_DEV       g_sci1port  /* SCI1 is ttyS4 */
#  define SCI1_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI2) && !defined(SCI2_ASSIGNED)
#  define TTYS4_DEV       g_sci2port  /* SCI2 is ttyS4 */
#  define SCI2_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI3) && !defined(SCI3_ASSIGNED)
#  define TTYS4_DEV       g_sci3port  /* SCI3 is ttyS4 */
#  define SCI3_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI4) && !defined(SCI4_ASSIGNED)
#  define TTYS4_DEV       g_sci4port  /* SCI4 is ttyS4 */
#  define SCI4_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI5) && !defined(SCI5_ASSIGNED)
#  define TTYS4_DEV       g_sci5port  /* SCI5 is ttyS4 */
#  define SCI5_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI6) && !defined(SCI6_ASSIGNED)
#  define TTYS4_DEV       g_sci6port  /* SCI6 is ttyS4 */
#  define SCI6_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI7) && !defined(SCI7_ASSIGNED)
#  define TTYS4_DEV       g_sci7port  /* SCI7 is ttyS4 */
#  define SCI7_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI8) && !defined(SCI8_ASSIGNED)
#  define TTYS4_DEV       g_sci8port  /* SCI8 is ttyS4 */
#  define SCI8_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI9) && !defined(SCI9_ASSIGNED)
#  define TTYS4_DEV       g_sci9port  /* SCI9 is ttyS4 */
#  define SCI9_ASSIGNED   1
#endif

#if defined(CONFIG_RZV_SCI0) && !defined(SCI0_ASSIGNED)
#  define TTYS5_DEV       g_sci0port  /* SCI0 is ttyS5 */
#  define SCI0_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI1) && !defined(SCI1_ASSIGNED)
#  define TTYS5_DEV       g_sci1port  /* SCI1 is ttyS5 */
#  define SCI1_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI2) && !defined(SCI2_ASSIGNED)
#  define TTYS5_DEV       g_sci2port  /* SCI2 is ttyS5 */
#  define SCI2_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI3) && !defined(SCI3_ASSIGNED)
#  define TTYS5_DEV       g_sci3port  /* SCI3 is ttyS5 */
#  define SCI3_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI4) && !defined(SCI4_ASSIGNED)
#  define TTYS5_DEV       g_sci4port  /* SCI4 is ttyS5 */
#  define SCI4_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI5) && !defined(SCI5_ASSIGNED)
#  define TTYS5_DEV       g_sci5port  /* SCI5 is ttyS5 */
#  define SCI5_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI6) && !defined(SCI6_ASSIGNED)
#  define TTYS5_DEV       g_sci6port  /* SCI6 is ttyS5 */
#  define SCI6_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI7) && !defined(SCI7_ASSIGNED)
#  define TTYS5_DEV       g_sci7port  /* SCI7 is ttyS5 */
#  define SCI7_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI8) && !defined(SCI8_ASSIGNED)
#  define TTYS5_DEV       g_sci8port  /* SCI8 is ttyS5 */
#  define SCI8_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI9) && !defined(SCI9_ASSIGNED)
#  define TTYS5_DEV       g_sci9port  /* SCI9 is ttyS5 */
#  define SCI9_ASSIGNED   1
#endif

#if defined(CONFIG_RZV_SCI0) && !defined(SCI0_ASSIGNED)
#  define TTYS6_DEV       g_sci0port  /* SCI0 is ttyS6 */
#  define SCI0_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI1) && !defined(SCI1_ASSIGNED)
#  define TTYS6_DEV       g_sci1port  /* SCI1 is ttyS6 */
#  define SCI1_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI2) && !defined(SCI2_ASSIGNED)
#  define TTYS6_DEV       g_sci2port  /* SCI2 is ttyS6 */
#  define SCI2_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI3) && !defined(SCI3_ASSIGNED)
#  define TTYS6_DEV       g_sci3port  /* SCI3 is ttyS6 */
#  define SCI3_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI4) && !defined(SCI4_ASSIGNED)
#  define TTYS6_DEV       g_sci4port  /* SCI4 is ttyS6 */
#  define SCI4_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI5) && !defined(SCI5_ASSIGNED)
#  define TTYS6_DEV       g_sci5port  /* SCI5 is ttyS6 */
#  define SCI5_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI6) && !defined(SCI6_ASSIGNED)
#  define TTYS6_DEV       g_sci6port  /* SCI6 is ttyS6 */
#  define SCI6_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI7) && !defined(SCI7_ASSIGNED)
#  define TTYS6_DEV       g_sci7port  /* SCI7 is ttyS6 */
#  define SCI7_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI8) && !defined(SCI8_ASSIGNED)
#  define TTYS6_DEV       g_sci8port  /* SCI8 is ttyS6 */
#  define SCI8_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI9) && !defined(SCI9_ASSIGNED)
#  define TTYS6_DEV       g_sci9port  /* SCI9 is ttyS6 */
#  define SCI9_ASSIGNED   1
#endif

#if defined(CONFIG_RZV_SCI0) && !defined(SCI0_ASSIGNED)
#  define TTYS7_DEV       g_sci0port  /* SCI0 is ttyS7 */
#  define SCI0_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI1) && !defined(SCI1_ASSIGNED)
#  define TTYS7_DEV       g_sci1port  /* SCI1 is ttyS7 */
#  define SCI1_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI2) && !defined(SCI2_ASSIGNED)
#  define TTYS7_DEV       g_sci2port  /* SCI2 is ttyS7 */
#  define SCI2_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI3) && !defined(SCI3_ASSIGNED)
#  define TTYS7_DEV       g_sci3port  /* SCI3 is ttyS7 */
#  define SCI3_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI4) && !defined(SCI4_ASSIGNED)
#  define TTYS7_DEV       g_sci4port  /* SCI4 is ttyS7 */
#  define SCI4_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI5) && !defined(SCI5_ASSIGNED)
#  define TTYS7_DEV       g_sci5port  /* SCI5 is ttyS7 */
#  define SCI5_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI6) && !defined(SCI6_ASSIGNED)
#  define TTYS7_DEV       g_sci6port  /* SCI6 is ttyS7 */
#  define SCI6_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI7) && !defined(SCI7_ASSIGNED)
#  define TTYS7_DEV       g_sci7port  /* SCI7 is ttyS7 */
#  define SCI7_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI8) && !defined(SCI8_ASSIGNED)
#  define TTYS7_DEV       g_sci8port  /* SCI8 is ttyS7 */
#  define SCI8_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI9) && !defined(SCI9_ASSIGNED)
#  define TTYS7_DEV       g_sci9port  /* SCI9 is ttyS7 */
#  define SCI9_ASSIGNED   1
#endif

#if defined(CONFIG_RZV_SCI0) && !defined(SCI0_ASSIGNED)
#  define TTYS8_DEV       g_sci0port  /* SCI0 is ttyS8 */
#  define SCI0_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI1) && !defined(SCI1_ASSIGNED)
#  define TTYS8_DEV       g_sci1port  /* SCI1 is ttyS8 */
#  define SCI1_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI2) && !defined(SCI2_ASSIGNED)
#  define TTYS8_DEV       g_sci2port  /* SCI2 is ttyS8 */
#  define SCI2_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI3) && !defined(SCI3_ASSIGNED)
#  define TTYS8_DEV       g_sci3port  /* SCI3 is ttyS8 */
#  define SCI3_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI4) && !defined(SCI4_ASSIGNED)
#  define TTYS8_DEV       g_sci4port  /* SCI4 is ttyS8 */
#  define SCI4_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI5) && !defined(SCI5_ASSIGNED)
#  define TTYS8_DEV       g_sci5port  /* SCI5 is ttyS8 */
#  define SCI5_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI6) && !defined(SCI6_ASSIGNED)
#  define TTYS8_DEV       g_sci6port  /* SCI6 is ttyS8 */
#  define SCI6_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI7) && !defined(SCI7_ASSIGNED)
#  define TTYS8_DEV       g_sci7port  /* SCI7 is ttyS8 */
#  define SCI7_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI8) && !defined(SCI8_ASSIGNED)
#  define TTYS8_DEV       g_sci8port  /* SCI8 is ttyS8 */
#  define SCI8_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI9) && !defined(SCI9_ASSIGNED)
#  define TTYS8_DEV       g_sci9port  /* SCI9 is ttyS8 */
#  define SCI9_ASSIGNED   1
#endif

#if defined(CONFIG_RZV_SCI0) && !defined(SCI0_ASSIGNED)
#  define TTYS9_DEV       g_sci0port  /* SCI0 is ttyS9 */
#  define SCI0_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI1) && !defined(SCI1_ASSIGNED)
#  define TTYS9_DEV       g_sci1port  /* SCI1 is ttyS9 */
#  define SCI1_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI2) && !defined(SCI2_ASSIGNED)
#  define TTYS9_DEV       g_sci2port  /* SCI2 is ttyS9 */
#  define SCI2_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI3) && !defined(SCI3_ASSIGNED)
#  define TTYS9_DEV       g_sci3port  /* SCI3 is ttyS9 */
#  define SCI3_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI4) && !defined(SCI4_ASSIGNED)
#  define TTYS9_DEV       g_sci4port  /* SCI4 is ttyS9 */
#  define SCI4_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI5) && !defined(SCI5_ASSIGNED)
#  define TTYS9_DEV       g_sci5port  /* SCI5 is ttyS9 */
#  define SCI5_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI6) && !defined(SCI6_ASSIGNED)
#  define TTYS9_DEV       g_sci6port  /* SCI6 is ttyS9 */
#  define SCI6_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI7) && !defined(SCI7_ASSIGNED)
#  define TTYS9_DEV       g_sci7port  /* SCI7 is ttyS9 */
#  define SCI7_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI8) && !defined(SCI8_ASSIGNED)
#  define TTYS9_DEV       g_sci8port  /* SCI8 is ttyS9 */
#  define SCI8_ASSIGNED   1
#elif defined(CONFIG_RZV_SCI9) && !defined(SCI9_ASSIGNED)
#  define TTYS9_DEV       g_sci9port  /* SCI9 is ttyS9 */
#  define SCI9_ASSIGNED   1
#endif

/****************************************************************************
 * Private Types
 ****************************************************************************/

struct rzv_uart_s
{
  uintptr_t uartbase;   /* Base address of UART registers */
  uint32_t  baud;       /* Configured baud rate */
  uint32_t  clk_id;     /* Clock identifier */
  uint32_t  sr;         /* Saved status bits for error recovery */
  uint8_t   channel;    /* SCI channel number (0-9) */
  int       irq_rxi;    /* Dynamically allocated RX interrupt (ICU slot) */
  int       irq_txi;    /* Dynamically allocated TX interrupt (ICU slot) */
  int       irq_tei;    /* Dynamically allocated TX end interrupt (ICU slot) */
  int       irq_eri;    /* Dynamically allocated error interrupt (ICU slot) */
  uint16_t  evt_rxi;    /* ELC event code for RX interrupt */
  uint16_t  evt_txi;    /* ELC event code for TX interrupt */
  uint16_t  evt_tei;    /* ELC event code for TX end interrupt */
  uint16_t  evt_eri;    /* ELC event code for error interrupt */
  uint8_t   parity;     /* 0=none, 1=odd, 2=even */
  uint8_t   bits;       /* Number of bits (7 or 8) */
  bool      stopbits2;  /* True: 2 stop bits */
  uint8_t   fifo_depth; /* FIFO depth: 0=no FIFO, 16=FIFO supported */

#ifdef CONFIG_SERIAL_TXDMA
  int               dma_tx_chn;    /* DMAC channel for TX (-1 = not configured) */
  rzv_dmac_handle_t dma_tx_handle; /* DMAC handle for TX */
  bool              dma_tx_active; /* DMA transfer in progress */
#endif

#ifdef CONFIG_SERIAL_RXDMA
  int               dma_rx_chn;    /* DMAC channel for RX (-1 = not configured) */
  rzv_dmac_handle_t dma_rx_handle; /* DMAC handle for RX */
  uint8_t          *rx_dma_buf;    /* Buffer for RX DMAC */
  size_t            rx_dma_size;   /* Size of RX DMAC buffer */
  size_t            rx_dma_pos;    /* Current read position */
  bool              dma_rx_active; /* DMA transfer in progress */
#endif
};

/* Baud rate calculation structure */

struct baud_setting
{
  uint8_t bgdm;    /* Baud rate generator double-speed mode */
  uint8_t abcs;    /* Asynchronous mode base clock select */
  uint8_t abcse;   /* Asynchronous mode extended base clock select */
  uint8_t cks;     /* Clock select (n value) */
  uint8_t brr;     /* Bit rate register value */
  uint8_t brme;    /* Bit rate modulation enable */
  uint16_t mddr;   /* Modulation duty register (128-256) */
};

struct common_baudrate_settings_s
{
  uint32_t baud;
  uint8_t bgdm;
  uint8_t abcs;
  uint8_t abcse;
  uint8_t cks;
  uint8_t brr;
  uint16_t mddr;
};

struct clock_baud_table_s
{
  uint32_t clock_freq;
  const struct common_baudrate_settings_s *settings;
  uint32_t num_settings;
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Baud rate calculation */

#if defined(CONFIG_RZV_SCI0) || defined(CONFIG_RZV_SCI1) || \
  defined(CONFIG_RZV_SCI2) || defined(CONFIG_RZV_SCI3) || \
  defined(CONFIG_RZV_SCI4) || defined(CONFIG_RZV_SCI5) || \
  defined(CONFIG_RZV_SCI6) || defined(CONFIG_RZV_SCI7) || \
  defined(CONFIG_RZV_SCI8) || defined(CONFIG_RZV_SCI9)

static int rzv_calculate_baud_setting(uint32_t baudrate,
                                     struct baud_setting *p_baud_setting);

/* Serial driver methods */

static int  rzv_setup(struct uart_dev_s *dev);
static void rzv_shutdown(struct uart_dev_s *dev);
static int  rzv_attach(struct uart_dev_s *dev);
static void rzv_detach(struct uart_dev_s *dev);
static int  rzv_interrupt(int irq, void *context, void *arg);
static int  rzv_ioctl(struct file *filep, int cmd, unsigned long arg);
static int  rzv_receive(struct uart_dev_s *dev, unsigned int *status);
static void rzv_rxint(struct uart_dev_s *dev, bool enable);
static bool rzv_rxavailable(struct uart_dev_s *dev);
static void rzv_send(struct uart_dev_s *dev, int ch);
static void rzv_txint(struct uart_dev_s *dev, bool enable);
static bool rzv_txready(struct uart_dev_s *dev);
static bool rzv_txempty(struct uart_dev_s *dev);

#ifdef CONFIG_RZV_SCI_FIFO_MODE
static void rzv_fifo_configure(struct rzv_uart_s *priv);
#endif

#ifdef CONFIG_SERIAL_TXDMA
static void rzv_dma_txcallback(void *handle, int event, void *user_data);
static int  rzv_dma_setup_tx(struct rzv_uart_s *priv);
static void rzv_dma_shutdown_tx(struct rzv_uart_s *priv);
static void rzv_dma_send(struct uart_dev_s *dev, const char *buffer, size_t len);
static void rzv_dma_txint(struct uart_dev_s *dev, bool enable);
static void rzv_dma_txavailable(struct uart_dev_s *dev);
#endif

#ifdef CONFIG_SERIAL_RXDMA
static void rzv_dma_rxcallback(void *handle, int event, void *user_data);
static int  rzv_dma_setup_rx(struct rzv_uart_s *priv);
static void rzv_dma_shutdown_rx(struct rzv_uart_s *priv);
static void rzv_dma_rxavailable(struct uart_dev_s *dev);
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const struct uart_ops_s g_uart_ops =
{
  .setup          = rzv_setup,
  .shutdown       = rzv_shutdown,
  .attach         = rzv_attach,
  .detach         = rzv_detach,
  .ioctl          = rzv_ioctl,
  .receive        = rzv_receive,
  .rxint          = rzv_rxint,
  .rxavailable    = rzv_rxavailable,
#ifdef CONFIG_SERIAL_IFLOWCONTROL
  .rxflowcontrol  = NULL,
#endif
  .send           = rzv_send,
#ifdef CONFIG_SERIAL_TXDMA
  .dmasend        = (void *)rzv_dma_send,
  .dmatxavail     = rzv_dma_txavailable,
  .txint          = rzv_dma_txint,
#else
  .txint          = rzv_txint,
#endif
#ifdef CONFIG_SERIAL_RXDMA
  .dmarxavail     = rzv_dma_rxavailable,
#endif
  .txready        = rzv_txready,
  .txempty        = rzv_txempty,
};

/* Baud rate divisor information (UART mode) */

static const struct
{
  uint8_t bgdm : 1;    /* Baud rate generator double-speed mode */
  uint8_t abcs : 1;    /* Asynchronous mode base clock select */
  uint8_t abcse : 1;   /* Asynchronous mode extended base clock select */
  uint8_t cks : 2;     /* Clock select (n value) */
} g_async_baud[13] =
{
  {0, 0, 1, 0},  /* divisor: 6 * 16 = 96 */
  {1, 1, 0, 0},  /* divisor: 8 * 8 = 64 */
  {1, 0, 0, 0},  /* divisor: 8 * 16 = 128 (double-speed) */
  {0, 0, 1, 1},  /* divisor: 6 * 4 * 16 = 384 */
  {0, 0, 0, 0},  /* divisor: 8 * 16 = 128 */
  {1, 0, 0, 1},  /* divisor: 8 * 8 * 16 = 1024 (double-speed) */
  {0, 0, 1, 2},  /* divisor: 6 * 16 * 16 = 1536 */
  {0, 0, 0, 1},  /* divisor: 8 * 16 * 16 = 2048 */
  {1, 0, 0, 2},  /* divisor: 8 * 8 * 16 * 16 = 16384 (double-speed) */
  {0, 0, 1, 3},  /* divisor: 6 * 16 * 16 * 16 = 24576 */
  {0, 0, 0, 2},  /* divisor: 8 * 16 * 16 * 16 = 32768 */
  {1, 0, 0, 3},  /* divisor: 8 * 8 * 16 * 16 * 16 = 262144 (double-speed) */
  {0, 0, 0, 3}   /* divisor: 8 * 16 * 16 * 16 * 16 = 524288 */
};

static const uint16_t g_div_coefficient[13] =
{
  6, 8, 16, 24, 32, 64, 96, 128, 256, 384, 512, 1024, 2048
};

/* Baud rate settings for 120MHz PCLK (common for RZV2H) */

static const struct common_baudrate_settings_s g_baud_120mhz[] =
{
  /*  baud,  bgdm, abcs, abcse, cks, brr, mddr */
  {   9600,    1,    0,    0,     1,  102,  135 },  /* Error: 0.004% */
  {  19200,    0,    0,    0,     0,  102,  135 },  /* Error: 0.004% */
  {  38400,    1,    0,    0,     0,  102,  135 },  /* Error: 0.004% */
  {  57600,    1,    0,    0,     0,   87,  173 },  /* Error: 0.009% */
  { 115200,    1,    0,    0,     0,   43,  173 },  /* Error: 0.009% */
  { 230400,    1,    0,    0,     0,   21,  173 },  /* Error: 0.009% */
  { 460800,    1,    0,    0,     0,   10,  173 },  /* Error: 0.009% */
  { 921600,    1,    0,    0,     0,    6,  220 },  /* Error: 0.092% */
  {1843200,    1,    0,    0,     0,    3,  251 },  /* Error: 0.262% */
};

static const struct clock_baud_table_s g_common_baud_settings[] =
{
  { 120000000, g_baud_120mhz, sizeof(g_baud_120mhz) / sizeof(g_baud_120mhz[0]) },
};

#define NUM_CLOCK_BAUD_TABLES \
  (sizeof(g_common_baud_settings) / sizeof(g_common_baud_settings[0]))

/* I/O buffers */

#ifdef CONFIG_RZV_SCI0
static char g_sci0rxbuffer[CONFIG_SCI0_RXBUFSIZE];
static char g_sci0txbuffer[CONFIG_SCI0_TXBUFSIZE];
#endif

#ifdef CONFIG_RZV_SCI1
static char g_sci1rxbuffer[CONFIG_SCI1_RXBUFSIZE];
static char g_sci1txbuffer[CONFIG_SCI1_TXBUFSIZE];
#endif

/* SCI0 configuration */

#ifdef CONFIG_RZV_SCI0
static struct rzv_uart_s g_sci0priv =
{
  .uartbase  = RZV_SCI0_BASE,
  .baud      = CONFIG_SCI0_BAUD,
  .clk_id    = RZV_CPG_CLK_SCI0,
  .sr        = 0,
  .channel   = 0,
  .irq_rxi   = -1,  /* Allocated dynamically via ICU */
  .irq_txi   = -1,
  .irq_tei   = -1,
  .irq_eri   = -1,
  .evt_rxi   = RZV_ELC_SC_ELCRDRF_0,
  .evt_txi   = RZV_ELC_SC_ELCTDRE_0,
  .evt_tei   = RZV_ELC_SC_ELCTEND_0,
  .evt_eri   = RZV_ELC_SC_ELCER_0,
  .parity    = CONFIG_SCI0_PARITY,
  .bits      = CONFIG_SCI0_BITS,
  .stopbits2 = CONFIG_SCI0_2STOP,
  .fifo_depth= 0,
#ifdef CONFIG_SERIAL_TXDMA
  .dma_tx_chn = -1,  /* Not configured by default */
  .dma_tx_active = false,
#endif
#ifdef CONFIG_SERIAL_RXDMA
  .dma_rx_chn = -1,  /* Not configured by default */
  .rx_dma_buf = NULL,
  .rx_dma_size = 0,
  .rx_dma_pos = 0,
  .dma_rx_active = false,
#endif
};

static uart_dev_t g_sci0port =
{
  .recv     =
  {
    .size   = CONFIG_SCI0_RXBUFSIZE,
    .buffer = g_sci0rxbuffer,
  },
  .xmit     =
  {
    .size   = CONFIG_SCI0_TXBUFSIZE,
    .buffer = g_sci0txbuffer,
  },
  .ops      = &g_uart_ops,
  .priv     = &g_sci0priv,
};
#endif

/* SCI1 configuration */

#ifdef CONFIG_RZV_SCI1
static struct rzv_uart_s g_sci1priv =
{
  .uartbase  = RZV_SCI1_BASE,
  .baud      = CONFIG_SCI1_BAUD,
  .clk_id    = RZV_CPG_CLK_SCI1,
  .sr        = 0,
  .channel   = 1,
  .irq_rxi   = -1,  /* Allocated dynamically via ICU */
  .irq_txi   = -1,
  .irq_tei   = -1,
  .irq_eri   = -1,
  .evt_rxi   = RZV_ELC_SC_ELCRDRF_1,
  .evt_txi   = RZV_ELC_SC_ELCTDRE_1,
  .evt_tei   = RZV_ELC_SC_ELCTEND_1,
  .evt_eri   = RZV_ELC_SC_ELCER_1,
  .parity    = CONFIG_SCI1_PARITY,
  .bits      = CONFIG_SCI1_BITS,
  .stopbits2 = CONFIG_SCI1_2STOP,
  .fifo_depth= 0,
#ifdef CONFIG_SERIAL_TXDMA
  .dma_tx_chn = -1,
  .dma_tx_active = false,
#endif
#ifdef CONFIG_SERIAL_RXDMA
  .dma_rx_chn = -1,
  .rx_dma_buf = NULL,
  .rx_dma_size = 0,
  .rx_dma_pos = 0,
  .dma_rx_active = false,
#endif
};

static uart_dev_t g_sci1port =
{
  .recv     =
  {
    .size   = CONFIG_SCI1_RXBUFSIZE,
    .buffer = g_sci1rxbuffer,
  },
  .xmit     =
  {
    .size   = CONFIG_SCI1_TXBUFSIZE,
    .buffer = g_sci1txbuffer,
  },
  .ops      = &g_uart_ops,
  .priv     = &g_sci1priv,
};
#endif

/* SCI2 configuration */

#ifdef CONFIG_RZV_SCI2
static char g_sci2rxbuffer[CONFIG_SCI2_RXBUFSIZE];
static char g_sci2txbuffer[CONFIG_SCI2_TXBUFSIZE];

static struct rzv_uart_s g_sci2priv =
{
  .uartbase  = RZV_SCI2_BASE,
  .baud      = CONFIG_SCI2_BAUD,
  .clk_id    = RZV_CPG_CLK_SCI2,
  .sr        = 0,
  .channel   = 2,
  .irq_rxi   = -1,
  .irq_txi   = -1,
  .irq_tei   = -1,
  .irq_eri   = -1,
  .evt_rxi   = RZV_ELC_SC_ELCRDRF_2,
  .evt_txi   = RZV_ELC_SC_ELCTDRE_2,
  .evt_tei   = RZV_ELC_SC_ELCTEND_2,
  .evt_eri   = RZV_ELC_SC_ELCER_2,
  .parity    = CONFIG_SCI2_PARITY,
  .bits      = CONFIG_SCI2_BITS,
  .stopbits2 = CONFIG_SCI2_2STOP,
  .fifo_depth= 0,
#ifdef CONFIG_SERIAL_TXDMA
  .dma_tx_chn = -1,
  .dma_tx_active = false,
#endif
#ifdef CONFIG_SERIAL_RXDMA
  .dma_rx_chn = -1,
  .rx_dma_buf = NULL,
  .rx_dma_size = 0,
  .rx_dma_pos = 0,
  .dma_rx_active = false,
#endif
};

static uart_dev_t g_sci2port =
{
  .recv     =
  {
    .size   = CONFIG_SCI2_RXBUFSIZE,
    .buffer = g_sci2rxbuffer,
  },
  .xmit     =
  {
    .size   = CONFIG_SCI2_TXBUFSIZE,
    .buffer = g_sci2txbuffer,
  },
  .ops      = &g_uart_ops,
  .priv     = &g_sci2priv,
};
#endif

/* SCI3 configuration */

#ifdef CONFIG_RZV_SCI3
static char g_sci3rxbuffer[CONFIG_SCI3_RXBUFSIZE];
static char g_sci3txbuffer[CONFIG_SCI3_TXBUFSIZE];

static struct rzv_uart_s g_sci3priv =
{
  .uartbase  = RZV_SCI3_BASE,
  .baud      = CONFIG_SCI3_BAUD,
  .clk_id    = RZV_CPG_CLK_SCI3,
  .sr        = 0,
  .channel   = 3,
  .irq_rxi   = -1,
  .irq_txi   = -1,
  .irq_tei   = -1,
  .irq_eri   = -1,
  .evt_rxi   = RZV_ELC_SC_ELCRDRF_3,
  .evt_txi   = RZV_ELC_SC_ELCTDRE_3,
  .evt_tei   = RZV_ELC_SC_ELCTEND_3,
  .evt_eri   = RZV_ELC_SC_ELCER_3,
  .parity    = CONFIG_SCI3_PARITY,
  .bits      = CONFIG_SCI3_BITS,
  .stopbits2 = CONFIG_SCI3_2STOP,
  .fifo_depth= 0,
#ifdef CONFIG_SERIAL_TXDMA
  .dma_tx_chn = -1,
  .dma_tx_active = false,
#endif
#ifdef CONFIG_SERIAL_RXDMA
  .dma_rx_chn = -1,
  .rx_dma_buf = NULL,
  .rx_dma_size = 0,
  .rx_dma_pos = 0,
  .dma_rx_active = false,
#endif
};

static uart_dev_t g_sci3port =
{
  .recv     =
  {
    .size   = CONFIG_SCI3_RXBUFSIZE,
    .buffer = g_sci3rxbuffer,
  },
  .xmit     =
  {
    .size   = CONFIG_SCI3_TXBUFSIZE,
    .buffer = g_sci3txbuffer,
  },
  .ops      = &g_uart_ops,
  .priv     = &g_sci3priv,
};
#endif

/* SCI4 configuration */

#ifdef CONFIG_RZV_SCI4
static char g_sci4rxbuffer[CONFIG_SCI4_RXBUFSIZE];
static char g_sci4txbuffer[CONFIG_SCI4_TXBUFSIZE];

static struct rzv_uart_s g_sci4priv =
{
  .uartbase  = RZV_SCI4_BASE,
  .baud      = CONFIG_SCI4_BAUD,
  .clk_id    = RZV_CPG_CLK_SCI4,
  .sr        = 0,
  .channel   = 4,
  .irq_rxi   = -1,
  .irq_txi   = -1,
  .irq_tei   = -1,
  .irq_eri   = -1,
  .evt_rxi   = RZV_ELC_SC_ELCRDRF_4,
  .evt_txi   = RZV_ELC_SC_ELCTDRE_4,
  .evt_tei   = RZV_ELC_SC_ELCTEND_4,
  .evt_eri   = RZV_ELC_SC_ELCER_4,
  .parity    = CONFIG_SCI4_PARITY,
  .bits      = CONFIG_SCI4_BITS,
  .stopbits2 = CONFIG_SCI4_2STOP,
  .fifo_depth= 0,
#ifdef CONFIG_SERIAL_TXDMA
  .dma_tx_chn = -1,
  .dma_tx_active = false,
#endif
#ifdef CONFIG_SERIAL_RXDMA
  .dma_rx_chn = -1,
  .rx_dma_buf = NULL,
  .rx_dma_size = 0,
  .rx_dma_pos = 0,
  .dma_rx_active = false,
#endif
};

static uart_dev_t g_sci4port =
{
  .recv     =
  {
    .size   = CONFIG_SCI4_RXBUFSIZE,
    .buffer = g_sci4rxbuffer,
  },
  .xmit     =
  {
    .size   = CONFIG_SCI4_TXBUFSIZE,
    .buffer = g_sci4txbuffer,
  },
  .ops      = &g_uart_ops,
  .priv     = &g_sci4priv,
};
#endif

/* SCI5 configuration */

#ifdef CONFIG_RZV_SCI5
static char g_sci5rxbuffer[CONFIG_SCI5_RXBUFSIZE];
static char g_sci5txbuffer[CONFIG_SCI5_TXBUFSIZE];

static struct rzv_uart_s g_sci5priv =
{
  .uartbase  = RZV_SCI5_BASE,
  .baud      = CONFIG_SCI5_BAUD,
  .clk_id    = RZV_CPG_CLK_SCI5,
  .sr        = 0,
  .channel   = 5,
  .irq_rxi   = -1,
  .irq_txi   = -1,
  .irq_tei   = -1,
  .irq_eri   = -1,
  .evt_rxi   = RZV_ELC_SC_ELCRDRF_5,
  .evt_txi   = RZV_ELC_SC_ELCTDRE_5,
  .evt_tei   = RZV_ELC_SC_ELCTEND_5,
  .evt_eri   = RZV_ELC_SC_ELCER_5,
  .parity    = CONFIG_SCI5_PARITY,
  .bits      = CONFIG_SCI5_BITS,
  .stopbits2 = CONFIG_SCI5_2STOP,
  .fifo_depth= 0,
#ifdef CONFIG_SERIAL_TXDMA
  .dma_tx_chn = -1,
  .dma_tx_active = false,
#endif
#ifdef CONFIG_SERIAL_RXDMA
  .dma_rx_chn = -1,
  .rx_dma_buf = NULL,
  .rx_dma_size = 0,
  .rx_dma_pos = 0,
  .dma_rx_active = false,
#endif
};

static uart_dev_t g_sci5port =
{
  .recv     =
  {
    .size   = CONFIG_SCI5_RXBUFSIZE,
    .buffer = g_sci5rxbuffer,
  },
  .xmit     =
  {
    .size   = CONFIG_SCI5_TXBUFSIZE,
    .buffer = g_sci5txbuffer,
  },
  .ops      = &g_uart_ops,
  .priv     = &g_sci5priv,
};
#endif

/* SCI6 configuration */

#ifdef CONFIG_RZV_SCI6
static char g_sci6rxbuffer[CONFIG_SCI6_RXBUFSIZE];
static char g_sci6txbuffer[CONFIG_SCI6_TXBUFSIZE];

static struct rzv_uart_s g_sci6priv =
{
  .uartbase  = RZV_SCI6_BASE,
  .baud      = CONFIG_SCI6_BAUD,
  .clk_id    = RZV_CPG_CLK_SCI6,
  .sr        = 0,
  .channel   = 6,
  .irq_rxi   = -1,
  .irq_txi   = -1,
  .irq_tei   = -1,
  .irq_eri   = -1,
  .evt_rxi   = RZV_ELC_SC_ELCRDRF_6,
  .evt_txi   = RZV_ELC_SC_ELCTDRE_6,
  .evt_tei   = RZV_ELC_SC_ELCTEND_6,
  .evt_eri   = RZV_ELC_SC_ELCER_6,
  .parity    = CONFIG_SCI6_PARITY,
  .bits      = CONFIG_SCI6_BITS,
  .stopbits2 = CONFIG_SCI6_2STOP,
  .fifo_depth= 0,
#ifdef CONFIG_SERIAL_TXDMA
  .dma_tx_chn = -1,
  .dma_tx_active = false,
#endif
#ifdef CONFIG_SERIAL_RXDMA
  .dma_rx_chn = -1,
  .rx_dma_buf = NULL,
  .rx_dma_size = 0,
  .rx_dma_pos = 0,
  .dma_rx_active = false,
#endif
};

static uart_dev_t g_sci6port =
{
  .recv     =
  {
    .size   = CONFIG_SCI6_RXBUFSIZE,
    .buffer = g_sci6rxbuffer,
  },
  .xmit     =
  {
    .size   = CONFIG_SCI6_TXBUFSIZE,
    .buffer = g_sci6txbuffer,
  },
  .ops      = &g_uart_ops,
  .priv     = &g_sci6priv,
};
#endif

/* SCI7 configuration */

#ifdef CONFIG_RZV_SCI7
static char g_sci7rxbuffer[CONFIG_SCI7_RXBUFSIZE];
static char g_sci7txbuffer[CONFIG_SCI7_TXBUFSIZE];

static struct rzv_uart_s g_sci7priv =
{
  .uartbase  = RZV_SCI7_BASE,
  .baud      = CONFIG_SCI7_BAUD,
  .clk_id    = RZV_CPG_CLK_SCI7,
  .sr        = 0,
  .channel   = 7,
  .irq_rxi   = -1,
  .irq_txi   = -1,
  .irq_tei   = -1,
  .irq_eri   = -1,
  .evt_rxi   = RZV_ELC_SC_ELCRDRF_7,
  .evt_txi   = RZV_ELC_SC_ELCTDRE_7,
  .evt_tei   = RZV_ELC_SC_ELCTEND_7,
  .evt_eri   = RZV_ELC_SC_ELCER_7,
  .parity    = CONFIG_SCI7_PARITY,
  .bits      = CONFIG_SCI7_BITS,
  .stopbits2 = CONFIG_SCI7_2STOP,
  .fifo_depth= 0,
#ifdef CONFIG_SERIAL_TXDMA
  .dma_tx_chn = -1,
  .dma_tx_active = false,
#endif
#ifdef CONFIG_SERIAL_RXDMA
  .dma_rx_chn = -1,
  .rx_dma_buf = NULL,
  .rx_dma_size = 0,
  .rx_dma_pos = 0,
  .dma_rx_active = false,
#endif
};

static uart_dev_t g_sci7port =
{
  .recv     =
  {
    .size   = CONFIG_SCI7_RXBUFSIZE,
    .buffer = g_sci7rxbuffer,
  },
  .xmit     =
  {
    .size   = CONFIG_SCI7_TXBUFSIZE,
    .buffer = g_sci7txbuffer,
  },
  .ops      = &g_uart_ops,
  .priv     = &g_sci7priv,
};
#endif

/* SCI8 configuration */

#ifdef CONFIG_RZV_SCI8
static char g_sci8rxbuffer[CONFIG_SCI8_RXBUFSIZE];
static char g_sci8txbuffer[CONFIG_SCI8_TXBUFSIZE];

static struct rzv_uart_s g_sci8priv =
{
  .uartbase  = RZV_SCI8_BASE,
  .baud      = CONFIG_SCI8_BAUD,
  .clk_id    = RZV_CPG_CLK_SCI8,
  .sr        = 0,
  .channel   = 8,
  .irq_rxi   = -1,
  .irq_txi   = -1,
  .irq_tei   = -1,
  .irq_eri   = -1,
  .evt_rxi   = RZV_ELC_SC_ELCRDRF_8,
  .evt_txi   = RZV_ELC_SC_ELCTDRE_8,
  .evt_tei   = RZV_ELC_SC_ELCTEND_8,
  .evt_eri   = RZV_ELC_SC_ELCER_8,
  .parity    = CONFIG_SCI8_PARITY,
  .bits      = CONFIG_SCI8_BITS,
  .stopbits2 = CONFIG_SCI8_2STOP,
  .fifo_depth= 0,
#ifdef CONFIG_SERIAL_TXDMA
  .dma_tx_chn = -1,
  .dma_tx_active = false,
#endif
#ifdef CONFIG_SERIAL_RXDMA
  .dma_rx_chn = -1,
  .rx_dma_buf = NULL,
  .rx_dma_size = 0,
  .rx_dma_pos = 0,
  .dma_rx_active = false,
#endif
};

static uart_dev_t g_sci8port =
{
  .recv     =
  {
    .size   = CONFIG_SCI8_RXBUFSIZE,
    .buffer = g_sci8rxbuffer,
  },
  .xmit     =
  {
    .size   = CONFIG_SCI8_TXBUFSIZE,
    .buffer = g_sci8txbuffer,
  },
  .ops      = &g_uart_ops,
  .priv     = &g_sci8priv,
};
#endif

/* SCI9 configuration */

#ifdef CONFIG_RZV_SCI9
static char g_sci9rxbuffer[CONFIG_SCI9_RXBUFSIZE];
static char g_sci9txbuffer[CONFIG_SCI9_TXBUFSIZE];

static struct rzv_uart_s g_sci9priv =
{
  .uartbase  = RZV_SCI9_BASE,
  .baud      = CONFIG_SCI9_BAUD,
  .clk_id    = RZV_CPG_CLK_SCI9,
  .sr        = 0,
  .channel   = 9,
  .irq_rxi   = -1,
  .irq_txi   = -1,
  .irq_tei   = -1,
  .irq_eri   = -1,
  .evt_rxi   = RZV_ELC_SC_ELCRDRF_9,
  .evt_txi   = RZV_ELC_SC_ELCTDRE_9,
  .evt_tei   = RZV_ELC_SC_ELCTEND_9,
  .evt_eri   = RZV_ELC_SC_ELCER_9,
  .parity    = CONFIG_SCI9_PARITY,
  .bits      = CONFIG_SCI9_BITS,
  .stopbits2 = CONFIG_SCI9_2STOP,
  .fifo_depth= 0,
#ifdef CONFIG_SERIAL_TXDMA
  .dma_tx_chn = -1,
  .dma_tx_active = false,
#endif
#ifdef CONFIG_SERIAL_RXDMA
  .dma_rx_chn = -1,
  .rx_dma_buf = NULL,
  .rx_dma_size = 0,
  .rx_dma_pos = 0,
  .dma_rx_active = false,
#endif
};

static uart_dev_t g_sci9port =
{
  .recv     =
  {
    .size   = CONFIG_SCI9_RXBUFSIZE,
    .buffer = g_sci9rxbuffer,
  },
  .xmit     =
  {
    .size   = CONFIG_SCI9_TXBUFSIZE,
    .buffer = g_sci9txbuffer,
  },
  .ops      = &g_uart_ops,
  .priv     = &g_sci9priv,
};
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_calculate_baud_setting
 *
 * Description:
 *   Calculate baud rate register settings for SCI_B UART.
 *   Based on Renesas R_SCI_B_UART_BaudCalculate algorithm.
 *   Supports BGDM, ABCS, ABCSE, CKS, and BRME/MDDR for optimal accuracy.
 *
 * Input Parameters:
 *   baudrate - Desired baud rate (bps)
 *   p_baud_setting - Output structure for baud rate settings
 *
 * Returned Value:
 *   0 on success, -EINVAL on error (baud rate error > 1.5%)
 *
 ****************************************************************************/

static int rzv_calculate_baud_setting(uint32_t baudrate,
                                     struct baud_setting *p_baud_setting)
{
  uint32_t freq_hz;
  int32_t hit_bit_err = 100000; /* 100% error as starting point */
  uint32_t divisor;

  /* Get PCLK frequency */

  freq_hz = rzv_get_pclk_frequency();

  if (baudrate == 0 || freq_hz == 0)
    {
      return -EINVAL;
    }

  /* First check common baud rate lookup table for exact matches */

  for (uint32_t i = 0; i < NUM_CLOCK_BAUD_TABLES; i++)
    {
      if (g_common_baud_settings[i].clock_freq == freq_hz)
        {
          /* Found matching clock frequency table */

          const struct common_baudrate_settings_s *settings =
            g_common_baud_settings[i].settings;
          uint32_t num_settings = g_common_baud_settings[i].num_settings;

          for (uint32_t j = 0; j < num_settings; j++)
            {
              if (settings[j].baud == baudrate)
                {
                  /* Exact match found in lookup table */

                  p_baud_setting->bgdm = settings[j].bgdm;
                  p_baud_setting->abcs = settings[j].abcs;
                  p_baud_setting->abcse = settings[j].abcse;
                  p_baud_setting->cks = settings[j].cks;
                  p_baud_setting->brr = settings[j].brr;
                  p_baud_setting->brme = (settings[j].mddr != 128) ? 1 : 0;
                  p_baud_setting->mddr = settings[j].mddr;

                  sinfo("Baud %lu: BRR=%u MDDR=%u BGDM=%u ABCS=%u "
                        "ABCSE=%u CKS=%u (table)\n",
                        (unsigned long)baudrate,
                        p_baud_setting->brr, p_baud_setting->mddr,
                        p_baud_setting->bgdm, p_baud_setting->abcs,
                        p_baud_setting->abcse, p_baud_setting->cks);

                  return 0;
                }
            }

          break; /* Found clock table but no matching baud rate */
        }
    }

  /* Initialize with default values for calculation */

  p_baud_setting->brr = 255;
  p_baud_setting->brme = 0;
  p_baud_setting->mddr = 256; /* Default: no bit rate modulation */

  /* Find the best BRR (bit rate register) value by trying all divisors */

  for (uint32_t select_16_base_clk_cycles = 0;
       select_16_base_clk_cycles <= 1 && (hit_bit_err > 1500);
       select_16_base_clk_cycles++)
    {
      for (uint32_t i = 0; i < 13; i++)
        {
          /* Skip divisors that don't match the clock cycle requirement */

          if (((uint8_t)select_16_base_clk_cycles) ^
              (g_async_baud[i].abcs | g_async_baud[i].abcse))
            {
              continue;
            }

          divisor = (uint32_t)g_div_coefficient[i] * baudrate;
          uint32_t temp_brr = freq_hz / divisor;

          if (temp_brr <= 256) /* BRR can be 0-255 */
            {
              while (temp_brr > 0)
                {
                  temp_brr -= 1;

                  /* Calculate the bit rate error. Formula:
                   * bit rate error[%] =
                   *   {(PCLK / (baud * div * (BRR + 1)) - 1} x 100
                   */

                  int32_t err_divisor = (int32_t)(divisor * (temp_brr + 1));
                  int64_t bit_err_calc =
                    (((int64_t)freq_hz) * 100000) / err_divisor - 100000;
                  int32_t bit_err = (int32_t)bit_err_calc;

                  /* Take the absolute value of the bit rate error */

                  if (bit_err < 0)
                    {
                      bit_err = -bit_err;
                    }

                  /* If this is the best error so far, save these settings */

                  if (bit_err < hit_bit_err)
                    {
                      p_baud_setting->bgdm = g_async_baud[i].bgdm;
                      p_baud_setting->abcs = g_async_baud[i].abcs;
                      p_baud_setting->abcse = g_async_baud[i].abcse;
                      p_baud_setting->cks = g_async_baud[i].cks;
                      p_baud_setting->brr = (uint8_t)temp_brr;
                      p_baud_setting->mddr = 256; /* No modulation */
                      hit_bit_err = bit_err;
                    }

                  break; /* Use first valid BRR for this divisor */
                }
            }
        }
    }

  /* Return error if the percent error is too large (>1.5%) */

  if (hit_bit_err > 1500)
    {
      serr("ERROR: Baud rate %lu error too high: %ld.%02ld%%\n",
           (unsigned long)baudrate,
           (long)(hit_bit_err / 1000),
           (long)((hit_bit_err % 1000) / 10));
      return -EINVAL;
    }

  sinfo("Baud %lu: BRR=%u BGDM=%u ABCS=%u ABCSE=%u CKS=%u "
        "error=%ld.%02ld%%\n",
        (unsigned long)baudrate, p_baud_setting->brr, p_baud_setting->bgdm,
        p_baud_setting->abcs, p_baud_setting->abcse, p_baud_setting->cks,
        (long)(hit_bit_err / 1000), (long)((hit_bit_err % 1000) / 10));

  return 0;
}

/****************************************************************************
 * Name: rzv_sci_getreg
 ****************************************************************************/

static inline uint32_t rzv_sci_getreg(struct rzv_uart_s *priv,
                                      unsigned int offset)
{
  return getreg32(priv->uartbase + offset);
}

/****************************************************************************
 * Name: rzv_sci_putreg
 ****************************************************************************/

static inline void rzv_sci_putreg(struct rzv_uart_s *priv,
                                  unsigned int offset, uint32_t value)
{
  putreg32(value, priv->uartbase + offset);
}

/****************************************************************************
 * Name: rzv_sci_modifyreg
 ****************************************************************************/

static inline void rzv_sci_modifyreg(struct rzv_uart_s *priv,
                                     unsigned int offset,
                                     uint32_t clearbits,
                                     uint32_t setbits)
{
  uint32_t regval = rzv_sci_getreg(priv, offset);
  regval &= ~clearbits;
  regval |= setbits;
  rzv_sci_putreg(priv, offset, regval);
}

/****************************************************************************
 * Name: rzv_fifo_configure
 *
 * Description:
 *   Configure SCI FIFO mode with trigger levels
 *
 ****************************************************************************/

#ifdef CONFIG_RZV_SCI_FIFO_MODE
static void rzv_fifo_configure(struct rzv_uart_s *priv)
{
  uint32_t fcr;

  /* Configure FIFO Control Register (FCR)
   * - RTRG: RX FIFO trigger level
   * - TTRG: TX FIFO trigger level
   * - RSTRG: RTS trigger level
   * - Enable FIFOs (FM=1)
   */

  fcr = (CONFIG_RZV_SCI_FIFO_RX_TRIGGER << SCI_FCR_RTRG_SHIFT) |
        (CONFIG_RZV_SCI_FIFO_TX_TRIGGER << SCI_FCR_TTRG_SHIFT) |
        ((priv->fifo_depth - 1) << SCI_FCR_RSTRG_SHIFT) |
        SCI_FCR_FM;  /* Enable FIFO mode */

  rzv_sci_putreg(priv, RZV_SCI_FCR_OFFSET, fcr);

  /* Reset FIFOs */

  rzv_sci_modifyreg(priv, RZV_SCI_FCR_OFFSET, 0,
                   SCI_FCR_TFRST | SCI_FCR_RFRST);

  /* Wait for FIFO reset to complete */

  while ((rzv_sci_getreg(priv, RZV_SCI_FCR_OFFSET) &
         (SCI_FCR_TFRST | SCI_FCR_RFRST)) != 0);
}
#endif

/****************************************************************************
 * Name: rzv_dma_txcallback
 *
 * Description:
 *   DMA TX completion callback
 *
 ****************************************************************************/

#ifdef CONFIG_SERIAL_TXDMA
static void rzv_dma_txcallback(void *handle, int event, void *user_data)
{
  struct rzv_uart_s *priv = (struct rzv_uart_s *)user_data;
  struct uart_dev_s *dev = (struct uart_dev_s *)((char *)user_data -
                            offsetof(struct uart_dev_s, priv));

  priv->dma_tx_active = false;

  /* Notify upper layer that DMA transfer is complete */

  uart_xmitchars_done(dev);
}

static int rzv_dma_setup_tx(struct rzv_uart_s *priv)
{
  struct rzv_dmac_config_s dma_config;

  if (priv->dma_tx_chn < 0)
    {
      return -EINVAL;  /* No DMA channel configured */
    }

  /* Initialize DMA channel */

  int ret = rzv_dmac_channel_initialize(priv->dma_tx_chn);
  if (ret < 0)
    {
      return ret;
    }

  /* Configure DMA for UART TX
   * - Source: memory (increment)
   * - Destination: UART TDR register (fixed)
   * - Trigger: UART TX event (hardware)
   */

  memset(&dma_config, 0, sizeof(dma_config));
  dma_config.mode           = RZV_DMAC_MODE_REGISTER;
  dma_config.src_size       = RZV_DMAC_SIZE_1BYTE;
  dma_config.dst_size       = RZV_DMAC_SIZE_1BYTE;
  dma_config.src_addr_mode  = RZV_DMAC_ADDR_INCREMENT;
  dma_config.dst_addr_mode  = RZV_DMAC_ADDR_FIXED;
  dma_config.trigger        = RZV_DMAC_TRIGGER_HW;
  dma_config.detect_mode    = RZV_DMAC_DETECT_RISING_EDGE;
  dma_config.dst_addr       = priv->uartbase + RZV_SCI_TDR_OFFSET;
  dma_config.elc_event      = priv->evt_txi;
  dma_config.callback       = rzv_dma_txcallback;
  dma_config.user_data      = priv;

  ret = rzv_dmac_channel_configure(priv->dma_tx_chn, &dma_config);
  if (ret < 0)
    {
      return ret;
    }

  priv->dma_tx_active = false;
  return OK;
}

static void rzv_dma_shutdown_tx(struct rzv_uart_s *priv)
{
  if (priv->dma_tx_chn >= 0)
    {
      rzv_dmac_channel_stop(priv->dma_tx_chn);
    }
}

static void rzv_dma_send(struct uart_dev_s *dev, const char *buffer,
                        size_t len)
{
  struct rzv_uart_s *priv = (struct rzv_uart_s *)dev->priv;
  struct rzv_dmac_config_s dma_config;

  if (priv->dma_tx_active || priv->dma_tx_chn < 0)
    {
      return;
    }

  /* Update DMA source address and length */

  memset(&dma_config, 0, sizeof(dma_config));
  dma_config.src_addr = (uint32_t)buffer;
  dma_config.length   = len;

  rzv_dmac_channel_configure(priv->dma_tx_chn, &dma_config);

  priv->dma_tx_active = true;

  /* Start DMA transfer */

  rzv_dmac_channel_start(priv->dma_tx_chn);
}

static void rzv_dma_txint(struct uart_dev_s *dev, bool enable)
{
  /* DMA mode doesn't use TX interrupts directly */
}

static void rzv_dma_txavailable(struct uart_dev_s *dev)
{
  struct rzv_uart_s *priv = (struct rzv_uart_s *)dev->priv;

  if (!priv->dma_tx_active)
    {
      uart_xmitchars_dma(dev);
    }
}
#endif /* CONFIG_SERIAL_TXDMA */

/****************************************************************************
 * Name: rzv_dma_rxcallback
 *
 * Description:
 *   DMA RX completion callback
 *
 ****************************************************************************/

#ifdef CONFIG_SERIAL_RXDMA
static void rzv_dma_rxcallback(void *handle, int event, void *user_data)
{
  struct rzv_uart_s *priv = (struct rzv_uart_s *)user_data;
  struct uart_dev_s *dev = (struct uart_dev_s *)((char *)user_data -
                            offsetof(struct uart_dev_s, priv));

  /* Notify upper layer that data is available */

  uart_recvchars(dev);
}

static int rzv_dma_setup_rx(struct rzv_uart_s *priv)
{
  struct rzv_dmac_config_s dma_config;

  if (priv->dma_rx_chn < 0)
    {
      return -EINVAL;
    }

  /* Allocate DMA buffer */

  priv->rx_dma_buf = kmm_malloc(CONFIG_RZV_SERIAL_RXDMA_BUFFER_SIZE);
  if (!priv->rx_dma_buf)
    {
      return -ENOMEM;
    }

  priv->rx_dma_size = CONFIG_RZV_SERIAL_RXDMA_BUFFER_SIZE;
  priv->rx_dma_pos = 0;

  /* Initialize DMA channel */

  int ret = rzv_dmac_channel_initialize(priv->dma_rx_chn);
  if (ret < 0)
    {
      kmm_free(priv->rx_dma_buf);
      return ret;
    }

  /* Configure DMA for UART RX
   * - Source: UART RDR register (fixed)
   * - Destination: memory (increment)
   * - Trigger: UART RX event (hardware)
   */

  memset(&dma_config, 0, sizeof(dma_config));
  dma_config.mode           = RZV_DMAC_MODE_REGISTER;
  dma_config.src_size       = RZV_DMAC_SIZE_1BYTE;
  dma_config.dst_size       = RZV_DMAC_SIZE_1BYTE;
  dma_config.src_addr_mode  = RZV_DMAC_ADDR_FIXED;
  dma_config.dst_addr_mode  = RZV_DMAC_ADDR_INCREMENT;
  dma_config.trigger        = RZV_DMAC_TRIGGER_HW;
  dma_config.detect_mode    = RZV_DMAC_DETECT_RISING_EDGE;
  dma_config.src_addr       = priv->uartbase + RZV_SCI_RDR_OFFSET;
  dma_config.dst_addr       = (uint32_t)priv->rx_dma_buf;
  dma_config.length         = priv->rx_dma_size;
  dma_config.elc_event      = priv->evt_rxi;
  dma_config.callback       = rzv_dma_rxcallback;
  dma_config.user_data      = priv;

  ret = rzv_dmac_channel_configure(priv->dma_rx_chn, &dma_config);
  if (ret < 0)
    {
      kmm_free(priv->rx_dma_buf);
      return ret;
    }

  priv->dma_rx_active = true;

  /* Start DMA reception */

  rzv_dmac_channel_start(priv->dma_rx_chn);

  return OK;
}

static void rzv_dma_shutdown_rx(struct rzv_uart_s *priv)
{
  if (priv->dma_rx_chn >= 0)
    {
      rzv_dmac_channel_stop(priv->dma_rx_chn);

      if (priv->rx_dma_buf)
        {
          kmm_free(priv->rx_dma_buf);
          priv->rx_dma_buf = NULL;
        }
    }
}

static void rzv_dma_rxavailable(struct uart_dev_s *dev)
{
  struct rzv_uart_s *priv = (struct rzv_uart_s *)dev->priv;
  size_t dma_pos;

  if (priv->dma_rx_active)
    {
      /* Get current DMA position */

      dma_pos = priv->rx_dma_size -
               rzv_dmac_get_remaining_count(priv->dma_rx_chn);

      if (dma_pos != priv->rx_dma_pos)
        {
          /* New data available, notify upper layer */

          uart_recvchars(dev);
          priv->rx_dma_pos = dma_pos;
        }
    }
}
#endif /* CONFIG_SERIAL_RXDMA */

/****************************************************************************
 * Name: rzv_setup
 *
 * Description:
 *   Configure the UART baud, bits, parity, etc. This method is called the
 *   first time that the serial port is opened.
 *
 ****************************************************************************/

static int rzv_setup(struct uart_dev_s *dev)
{
  struct rzv_uart_s *priv = (struct rzv_uart_s *)dev->priv;
  uint32_t ccr2;
  uint32_t ccr3;
  uint32_t ccr1;

  struct baud_setting baud_setting;
  int ret;

  /* Enable clock for this SCI channel */

  rzv_clock_enable(priv->clk_id);

  /* Deassert module reset */

  rzv_module_unreset(priv->clk_id);

  /* CRITICAL: Wait for module power-up (P1 fix)
   * Hardware requires delay after clock enable before register access
   */

  for (volatile int i = 0; i < 1000; i++)
    {
      /* Delay ~10 us at typical CPU frequencies */
    }

  /* Disable transmit and receive */

  rzv_sci_putreg(priv, RZV_SCI_CCR_OFFSET(0), 0);

  /* Configure character length */

  ccr3 = rzv_sci_getreg(priv, RZV_SCI_CCR_OFFSET(3));
  ccr3 &= ~SCI_CCR3_CHR_MASK;

  if (priv->bits == 7)
    {
      ccr3 |= SCI_CCR3_CHR_7BIT;
    }
  else
    {
      ccr3 |= SCI_CCR3_CHR_8BIT;
    }

  /* Configure stop bits */

  if (priv->stopbits2)
    {
      ccr3 |= SCI_CCR3_STP_2BIT;
    }
  else
    {
      ccr3 &= ~SCI_CCR3_STP;
    }

  /* Set asynchronous mode */

  ccr3 = (ccr3 & ~SCI_CCR3_MOD_MASK) | SCI_CCR3_MOD_ASYNC;

  /* IDSEL: Idle detection select (P2 fix)
   * Use edge detection for idle (typical for UART)
   */
  ccr3 |= SCI_CCR3_IDSEL;

  rzv_sci_putreg(priv, RZV_SCI_CCR_OFFSET(3), ccr3);

  /* Configure parity */

  ccr1 = rzv_sci_getreg(priv, RZV_SCI_CCR_OFFSET(1));
  ccr1 &= ~(SCI_CCR1_PE | SCI_CCR1_PM);

  if (priv->parity == 1)
    {
      ccr1 |= SCI_CCR1_PE;  /* Odd parity */
    }
  else if (priv->parity == 2)
    {
      ccr1 |= SCI_CCR1_PE | SCI_CCR1_PM;  /* Even parity */
    }

  /* SPB2IO: Serial Port Break I/O (P2 fix)
   * Set to output mode to enable break signal transmission
   */
  ccr1 |= SCI_CCR1_SPB2IO;

  rzv_sci_putreg(priv, RZV_SCI_CCR_OFFSET(1), ccr1);

  /* CRITICAL: Calculate baud rate using sophisticated algorithm (P0 fix)
   * Supports BGDM, ABCS, ABCSE, CKS, and BRME/MDDR for optimal accuracy
   */

  ret = rzv_calculate_baud_setting(priv->baud, &baud_setting);
  if (ret < 0)
    {
      serr("ERROR: Failed to calculate baud rate for %lu bps\n",
           (unsigned long)priv->baud);
      return ret;
    }

  /* Configure CCR2 with calculated baud rate settings */

  ccr2 = rzv_sci_getreg(priv, RZV_SCI_CCR_OFFSET(2));
  ccr2 &= ~(SCI_CCR2_BRR_MASK | SCI_CCR2_CKS_MASK |
            SCI_CCR2_MDDR_MASK | SCI_CCR2_BGDM | SCI_CCR2_ABCS |
            SCI_CCR2_ABCSE | SCI_CCR2_BFME);

  ccr2 |= (baud_setting.bgdm ? SCI_CCR2_BGDM : 0) |
          (baud_setting.abcs ? SCI_CCR2_ABCS : 0) |
          (baud_setting.abcse ? SCI_CCR2_ABCSE : 0) |
          (baud_setting.brme ? SCI_CCR2_BFME : 0) |
          ((uint32_t)baud_setting.cks << SCI_CCR2_CKS_SHIFT) |
          ((uint32_t)baud_setting.brr << SCI_CCR2_BRR_SHIFT) |
          ((uint32_t)baud_setting.mddr << SCI_CCR2_MDDR_SHIFT);

  rzv_sci_putreg(priv, RZV_SCI_CCR_OFFSET(2), ccr2);

  /* Enable transmit and receive */

  rzv_sci_putreg(priv, RZV_SCI_CCR_OFFSET(0), SCI_CCR0_TE | SCI_CCR0_RE);

  /* CRITICAL: Wait for RIST bit before starting reception (P0 fix)
   * SCI_B hardware requires receiver to stabilize before data transfer
   * Prevents corruption of first received bytes
   */

  while ((rzv_sci_getreg(priv, RZV_SCI_CESR_OFFSET) & SCI_CESR_RIST) == 0)
    {
      /* Polling loop - typically completes in 1-2 us */
    }

  /* Configure FIFO if supported (RZV2H SCI-B has 16-byte FIFOs) */

#ifdef CONFIG_RZV_SCI_FIFO_MODE
  priv->fifo_depth = 16;  /* RZV2H SCI_B has 16-byte FIFOs */
  rzv_fifo_configure(priv);
#else
  priv->fifo_depth = 0;
#endif

  sinfo("SCI%d: Configured at %lu baud (BRR=%u, MDDR=%u, "
        "BGDM=%u, ABCS=%u, ABCSE=%u, CKS=%u)\n",
        priv->channel, (unsigned long)priv->baud,
        baud_setting.brr, baud_setting.mddr,
        baud_setting.bgdm, baud_setting.abcs, baud_setting.abcse,
        baud_setting.cks);

  return OK;
}

/****************************************************************************
 * Name: rzv_shutdown
 *
 * Description:
 *   Disable the UART. This method is called when the serial
 *   port is closed
 *
 ****************************************************************************/

static void rzv_shutdown(struct uart_dev_s *dev)
{
  struct rzv_uart_s *priv = (struct rzv_uart_s *)dev->priv;

  /* Disable transmit and receive */

  rzv_sci_putreg(priv, RZV_SCI_CCR_OFFSET(0), 0);

  /* Disable clock */

  rzv_clock_disable(priv->clk_id);
}

/****************************************************************************
 * Name: rzv_attach
 *
 * Description:
 *   Configure the UART to operation in interrupt driven mode. This method
 *   is called when the serial port is opened.  Normally, this is just after
 *   the setup() method is called, however, the serial console may operate
 *   in a non-interrupt driven mode during the boot phase.
 *
 *   Uses dynamic ICU slot allocation for RX/TX/TEI/ERI interrupts.
 *
 ****************************************************************************/

static int rzv_attach(struct uart_dev_s *dev)
{
  struct rzv_uart_s *priv = (struct rzv_uart_s *)dev->priv;
  int ret = OK;

  /* Attach RX interrupt using ICU dynamic slot allocation */

  priv->irq_rxi = rzv_icu_attach(priv->evt_rxi, rzv_interrupt, dev, true);
  if (priv->irq_rxi < 0)
    {
      serr("ERROR: Failed to attach RX interrupt for SCI%d\n", priv->channel);
      ret = priv->irq_rxi;
      goto errout;
    }

  /* Attach TX interrupt using ICU dynamic slot allocation */

  priv->irq_txi = rzv_icu_attach(priv->evt_txi, rzv_interrupt, dev, true);
  if (priv->irq_txi < 0)
    {
      serr("ERROR: Failed to attach TX interrupt for SCI%d\n", priv->channel);
      ret = priv->irq_txi;
      goto errout_rxi;
    }

  /* Attach TX end interrupt using ICU dynamic slot allocation */

  priv->irq_tei = rzv_icu_attach(priv->evt_tei, rzv_interrupt, dev, true);
  if (priv->irq_tei < 0)
    {
      serr("ERROR: Failed to attach TEI interrupt for SCI%d\n", priv->channel);
      ret = priv->irq_tei;
      goto errout_txi;
    }

  /* Attach error interrupt using ICU dynamic slot allocation */

  priv->irq_eri = rzv_icu_attach(priv->evt_eri, rzv_interrupt, dev, true);
  if (priv->irq_eri < 0)
    {
      serr("ERROR: Failed to attach ERI interrupt for SCI%d\n", priv->channel);
      ret = priv->irq_eri;
      goto errout_tei;
    }

  sinfo("SCI%d: Attached interrupts RXI=%d TXI=%d TEI=%d ERI=%d\n",
        priv->channel, priv->irq_rxi, priv->irq_txi,
        priv->irq_tei, priv->irq_eri);

#ifdef CONFIG_SERIAL_TXDMA
  /* Configure DMA channel for TX if enabled */
  if (priv->dma_tx_chn >= 0)
    {
      ret = rzv_dma_setup_tx(priv);
      if (ret < 0)
        {
          syslog(LOG_ERR, "UART%d: TX DMA setup failed: %d\n",
                 priv->channel, ret);
          /* Continue without DMA */
          priv->dma_tx_chn = -1;
        }
    }
#endif

#ifdef CONFIG_SERIAL_RXDMA
  /* Configure DMA channel for RX if enabled */
  if (priv->dma_rx_chn >= 0)
    {
      ret = rzv_dma_setup_rx(priv);
      if (ret < 0)
        {
          syslog(LOG_ERR, "UART%d: RX DMA setup failed: %d\n",
                 priv->channel, ret);
          /* Continue without DMA */
          priv->dma_rx_chn = -1;
        }
    }
#endif

  return OK;

errout_tei:
  rzv_icu_detach(priv->irq_tei);
  priv->irq_tei = -1;
errout_txi:
  rzv_icu_detach(priv->irq_txi);
  priv->irq_txi = -1;
errout_rxi:
  rzv_icu_detach(priv->irq_rxi);
  priv->irq_rxi = -1;
errout:
  return ret;
}

/****************************************************************************
 * Name: rzv_detach
 *
 * Description:
 *   Detach UART interrupts. This method is called when the serial port is
 *   closed normally just before the shutdown method is called. The
 *   exception is the serial console which is never shutdown.
 *
 *   Releases dynamically allocated ICU interrupt slots.
 *
 ****************************************************************************/

static void rzv_detach(struct uart_dev_s *dev)
{
  struct rzv_uart_s *priv = (struct rzv_uart_s *)dev->priv;

#ifdef CONFIG_SERIAL_TXDMA
  /* Shutdown TX DMA */
  rzv_dma_shutdown_tx(priv);
#endif

#ifdef CONFIG_SERIAL_RXDMA
  /* Shutdown RX DMA */
  rzv_dma_shutdown_rx(priv);
#endif

  /* Disable interrupts in the SCI peripheral */

  rzv_sci_putreg(priv, RZV_SCI_CCR_OFFSET(0),
                rzv_sci_getreg(priv, RZV_SCI_CCR_OFFSET(0)) &
                ~(SCI_CCR0_RIE | SCI_CCR0_TIE | SCI_CCR0_TEIE));

  /* Detach and release ICU interrupt slots */

  if (priv->irq_rxi >= 0)
    {
      rzv_icu_detach(priv->irq_rxi);
      priv->irq_rxi = -1;
    }

  if (priv->irq_txi >= 0)
    {
      rzv_icu_detach(priv->irq_txi);
      priv->irq_txi = -1;
    }

  if (priv->irq_tei >= 0)
    {
      rzv_icu_detach(priv->irq_tei);
      priv->irq_tei = -1;
    }

  if (priv->irq_eri >= 0)
    {
      rzv_icu_detach(priv->irq_eri);
      priv->irq_eri = -1;
    }
}

/****************************************************************************
 * Name: rzv_interrupt
 *
 * Description:
 *   This is the UART interrupt handler. It will be invoked when an
 *   interrupt is received on the 'irq'. It should call uart_xmitchars or
 *   uart_recvchars to perform the appropriate data transfers.
 *
 *   Handles RXI, TXI, TEI, and ERI interrupts from the SCI peripheral.
 *
 ****************************************************************************/

static int rzv_interrupt(int irq, void *context, void *arg)
{
  struct uart_dev_s *dev = (struct uart_dev_s *)arg;
  struct rzv_uart_s *priv;
  uint32_t csr;
  uint32_t ccr0;

  DEBUGASSERT(dev != NULL && dev->priv != NULL);
  priv = (struct rzv_uart_s *)dev->priv;

  /* Read the Communication Status Register (CSR) */

  csr = rzv_sci_getreg(priv, RZV_SCI_CSR_OFFSET);
  ccr0 = rzv_sci_getreg(priv, RZV_SCI_CCR_OFFSET(0));

  /* Save error status bits for error recovery (P2 fix)
   * Store framing error, parity error, and overrun error flags
   */
  if (csr & (SCI_CSR_FER | SCI_CSR_PER | SCI_CSR_ORER))
    {
      priv->sr = csr & (SCI_CSR_FER | SCI_CSR_PER | SCI_CSR_ORER);
    }

  /* Check for errors (overrun, framing, parity) */

  if (csr & (SCI_CSR_ORER | SCI_CSR_PER | SCI_CSR_FER))
    {
      /* Clear error flags using CFCLR register */

      uint32_t cfclr = 0;

      if (csr & SCI_CSR_ORER)
        {
          cfclr |= SCI_CFCLR_ORERC;
          serr("SCI%d: Overrun error\n", priv->channel);
        }

      if (csr & SCI_CSR_FER)
        {
          cfclr |= SCI_CFCLR_FERC;
          serr("SCI%d: Framing error\n", priv->channel);
        }

      if (csr & SCI_CSR_PER)
        {
          cfclr |= SCI_CFCLR_PERC;
          serr("SCI%d: Parity error\n", priv->channel);
        }

      /* Clear the error flags */

      rzv_sci_putreg(priv, RZV_SCI_CFCLR_OFFSET, cfclr);
    }

  /* Handle incoming characters (Receive Data Full) */

  if ((csr & SCI_CSR_RDRF) && (ccr0 & SCI_CCR0_RIE))
    {
      uart_recvchars(dev);

      /* Clear RX data full flag */

      rzv_sci_putreg(priv, RZV_SCI_CFCLR_OFFSET, SCI_CFCLR_RDRFC);
    }

  /* Handle outgoing characters (Transmit Data Empty or Transmit End) */

  if (((csr & SCI_CSR_TDRE) && (ccr0 & SCI_CCR0_TIE)) ||
      ((csr & SCI_CSR_TEND) && (ccr0 & SCI_CCR0_TEIE)))
    {
      uart_xmitchars(dev);

      /* Clear TX data empty flag */

      if (csr & SCI_CSR_TDRE)
        {
          rzv_sci_putreg(priv, RZV_SCI_CFCLR_OFFSET, SCI_CFCLR_TDREC);
        }

      /* Clear transmit end flag */

      if (csr & SCI_CSR_TEND)
        {
          rzv_sci_putreg(priv, RZV_SCI_CFCLR_OFFSET, SCI_CFCLR_TDREC);
        }
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_ioctl
 *
 * Description:
 *   All ioctl calls will be routed through this method
 *
 ****************************************************************************/

static int rzv_ioctl(struct file *filep, int cmd, unsigned long arg)
{
  return -ENOTTY;
}

/****************************************************************************
 * Name: rzv_receive
 *
 * Description:
 *   Called (usually) from the interrupt level to receive one
 *   character from the UART. Error bits associated with the
 *   receipt are provided in the return 'status'.
 *
 ****************************************************************************/

static int rzv_receive(struct uart_dev_s *dev, unsigned int *status)
{
  struct rzv_uart_s *priv = (struct rzv_uart_s *)dev->priv;
  uint32_t rdr;
  uint32_t csr;

  /* Read Communication Status Register for error flags */

  csr = rzv_sci_getreg(priv, RZV_SCI_CSR_OFFSET);

  /* Read receive data register */

  rdr = rzv_sci_getreg(priv, RZV_SCI_RDR_OFFSET);

  /* Use saved error status (P2 fix)
   * Combine current CSR with saved error bits to ensure
   * error conditions are not lost between interrupt and receive
   */

  *status = csr | priv->sr;

  /* Clear saved error status after reporting */
  priv->sr = 0;

  return (rdr & SCI_RDR_RDAT_MASK) >> SCI_RDR_RDAT_SHIFT;
}

/****************************************************************************
 * Name: rzv_rxint
 *
 * Description:
 *   Call to enable or disable RX interrupts
 *
 ****************************************************************************/

static void rzv_rxint(struct uart_dev_s *dev, bool enable)
{
  struct rzv_uart_s *priv = (struct rzv_uart_s *)dev->priv;

  if (enable)
    {
      rzv_sci_modifyreg(priv, RZV_SCI_CCR_OFFSET(0), 0, SCI_CCR0_RIE);
    }
  else
    {
      rzv_sci_modifyreg(priv, RZV_SCI_CCR_OFFSET(0), SCI_CCR0_RIE, 0);
    }
}

/****************************************************************************
 * Name: rzv_rxavailable
 *
 * Description:
 *   Return true if the receive register is not empty
 *
 ****************************************************************************/

static bool rzv_rxavailable(struct uart_dev_s *dev)
{
  struct rzv_uart_s *priv = (struct rzv_uart_s *)dev->priv;
  uint32_t csr;

  /* Check the RDRF (Receive Data Full) bit in CSR */

  csr = rzv_sci_getreg(priv, RZV_SCI_CSR_OFFSET);
  return (csr & SCI_CSR_RDRF) != 0;
}

/****************************************************************************
 * Name: rzv_send
 *
 * Description:
 *   This method will send one byte on the UART.
 *
 ****************************************************************************/

static void rzv_send(struct uart_dev_s *dev, int ch)
{
  struct rzv_uart_s *priv = (struct rzv_uart_s *)dev->priv;

  /* Write the character to the transmit data register */

  rzv_sci_putreg(priv, RZV_SCI_TDR_OFFSET,
                 (ch << SCI_TDR_TDAT_SHIFT) & SCI_TDR_TDAT_MASK);
}

/****************************************************************************
 * Name: rzv_txint
 *
 * Description:
 *   Call to enable or disable TX interrupts
 *
 ****************************************************************************/

static void rzv_txint(struct uart_dev_s *dev, bool enable)
{
  struct rzv_uart_s *priv = (struct rzv_uart_s *)dev->priv;
  irqstate_t flags;

  /* Use critical section to prevent race with TX interrupt handler */

  flags = enter_critical_section();

  if (enable)
    {
      rzv_sci_modifyreg(priv, RZV_SCI_CCR_OFFSET(0), 0,
                       SCI_CCR0_TIE | SCI_CCR0_TEIE);
    }
  else
    {
      rzv_sci_modifyreg(priv, RZV_SCI_CCR_OFFSET(0),
                       SCI_CCR0_TIE | SCI_CCR0_TEIE, 0);
    }

  leave_critical_section(flags);
}

/****************************************************************************
 * Name: rzv_txready
 *
 * Description:
 *   Return true if the transmit data register is empty
 *
 ****************************************************************************/

static bool rzv_txready(struct uart_dev_s *dev)
{
  struct rzv_uart_s *priv = (struct rzv_uart_s *)dev->priv;
  uint32_t csr;

  /* Check the TDRE (Transmit Data Empty) bit in CSR */

  csr = rzv_sci_getreg(priv, RZV_SCI_CSR_OFFSET);
  return (csr & SCI_CSR_TDRE) != 0;
}

/****************************************************************************
 * Name: rzv_txempty
 *
 * Description:
 *   Return true if the transmit is complete (TEND flag set)
 *
 ****************************************************************************/

static bool rzv_txempty(struct uart_dev_s *dev)
{
  struct rzv_uart_s *priv = (struct rzv_uart_s *)dev->priv;
  uint32_t csr;

  /* Check the TEND (Transmit End) bit in CSR */

  csr = rzv_sci_getreg(priv, RZV_SCI_CSR_OFFSET);
  return (csr & SCI_CSR_TEND) != 0;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: arm_earlyserialinit
 *
 * Description:
 *   Performs the low level UART initialization early in debug so that the
 *   serial console will be available during bootup. This must be called
 *   before arm_serialinit.
 *
 ****************************************************************************/

void arm_earlyserialinit(void)
{
  /* Disable all UARTs */

#ifdef TTYS0_DEV
  rzv_shutdown(&TTYS0_DEV);
#endif
#ifdef TTYS1_DEV
  rzv_shutdown(&TTYS1_DEV);
#endif
#ifdef TTYS2_DEV
  rzv_shutdown(&TTYS2_DEV);
#endif
#ifdef TTYS3_DEV
  rzv_shutdown(&TTYS3_DEV);
#endif
#ifdef TTYS4_DEV
  rzv_shutdown(&TTYS4_DEV);
#endif
#ifdef TTYS5_DEV
  rzv_shutdown(&TTYS5_DEV);
#endif
#ifdef TTYS6_DEV
  rzv_shutdown(&TTYS6_DEV);
#endif
#ifdef TTYS7_DEV
  rzv_shutdown(&TTYS7_DEV);
#endif
#ifdef TTYS8_DEV
  rzv_shutdown(&TTYS8_DEV);
#endif
#ifdef TTYS9_DEV
  rzv_shutdown(&TTYS9_DEV);
#endif

  /* Configuration whichever one is the console */

#ifdef CONSOLE_DEV
  CONSOLE_DEV.isconsole = true;
  rzv_setup(&CONSOLE_DEV);
#endif
}

/****************************************************************************
 * Name: arm_serialinit
 *
 * Description:
 *   Register serial console and serial ports. This assumes
 *   that arm_earlyserialinit was called previously.
 *
 ****************************************************************************/

void arm_serialinit(void)
{
#ifdef CONFIG_ARCH_BOARD_RDK_RZV2H
#ifdef CONSOLE_DEV
  uart_register("/dev/console", &CONSOLE_DEV);
#endif
#ifdef CONFIG_RZV_SCI0
  uart_register("/dev/ttyS0", &g_sci0port);
#endif
#ifdef CONFIG_RZV_SCI1
  uart_register("/dev/ttyS1", &g_sci1port);
#endif
#ifdef CONFIG_RZV_SCI2
  uart_register("/dev/ttyS2", &g_sci2port);
#endif
#ifdef CONFIG_RZV_SCI3
  uart_register("/dev/ttyS3", &g_sci3port);
#endif
#ifdef CONFIG_RZV_SCI4
  uart_register("/dev/ttyS4", &g_sci4port);
#endif
#ifdef CONFIG_RZV_SCI5
  uart_register("/dev/ttyS5", &g_sci5port);
#endif
#ifdef CONFIG_RZV_SCI6
  uart_register("/dev/ttyS6", &g_sci6port);
#endif
#ifdef CONFIG_RZV_SCI7
  uart_register("/dev/ttyS7", &g_sci7port);
#endif
#ifdef CONFIG_RZV_SCI8
  uart_register("/dev/ttyS8", &g_sci8port);
#endif
#ifdef CONFIG_RZV_SCI9
  uart_register("/dev/ttyS9", &g_sci9port);
#endif
#else
#  ifdef CONSOLE_DEV
  uart_register("/dev/console", &CONSOLE_DEV);
#  endif
#  ifdef TTYS0_DEV
  uart_register("/dev/ttyS0", &TTYS0_DEV);
#  endif
#  ifdef TTYS1_DEV
  uart_register("/dev/ttyS1", &TTYS1_DEV);
#  endif
#  ifdef TTYS2_DEV
  uart_register("/dev/ttyS2", &TTYS2_DEV);
#  endif
#  ifdef TTYS3_DEV
  uart_register("/dev/ttyS3", &TTYS3_DEV);
#  endif
#  ifdef TTYS4_DEV
  uart_register("/dev/ttyS4", &TTYS4_DEV);
#  endif
#  ifdef TTYS5_DEV
  uart_register("/dev/ttyS5", &TTYS5_DEV);
#  endif
#  ifdef TTYS6_DEV
  uart_register("/dev/ttyS6", &TTYS6_DEV);
#  endif
#  ifdef TTYS7_DEV
  uart_register("/dev/ttyS7", &TTYS7_DEV);
#  endif
#  ifdef TTYS8_DEV
  uart_register("/dev/ttyS8", &TTYS8_DEV);
#  endif
#  ifdef TTYS9_DEV
  uart_register("/dev/ttyS9", &TTYS9_DEV);
#  endif
#endif
}

/****************************************************************************
 * Name: up_putc
 *
 * Description:
 *   Provide priority, low-level access to support OS debug writes
 *
 ****************************************************************************/

int up_putc(int ch)
{
#ifdef CONSOLE_DEV
  /* Wait for transmit buffer to be ready */

  while (!rzv_txready(&CONSOLE_DEV));

  /* Send the character */

  rzv_send(&CONSOLE_DEV, ch);

  return ch;
#else
  return 0;
#endif
}

#else /* No SCI devices configured */

/****************************************************************************
 * Name: arm_serialinit
 *
 * Description:
 *   Stub for when no serial devices are configured.
 *   This is still needed when USE_SERIALDRIVER is defined but no
 *   SCI ports are enabled (e.g., using RTT console).
 *
 ****************************************************************************/

void arm_serialinit(void)
{
  /* Nothing to do - no serial devices configured */
}

/****************************************************************************
 * Name: up_putc
 *
 * Description:
 *   Stub for when no serial devices are configured.
 *
 ****************************************************************************/

int up_putc(int ch)
{
  /* No console device available */

  return 0;
}

#endif /* CONFIG_RZV_SCIx enabled */

#endif /* USE_SERIALDRIVER */
