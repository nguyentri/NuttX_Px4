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

#ifdef CONFIG_SERIAL_TERMIOS
#  include <termios.h>
#endif

#include "arm_internal.h"
#include "chip.h"
#include "rzv_clock.h"
#include "rzv_icu.h"
#include "rzv_serial.h"   /* provides rzv2h_serial_setup() declaration */
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

/* Baud-rate error tolerance (x1000 = 0.001% units).
 * Default 1500 = 1.5%. PX4 high-baud links (921600, 3Mbaud) may need 2500.
 * TODO: expose via Kconfig CONFIG_RZV_SCI_BAUD_ERROR_X_1000.
 */
#ifndef CONFIG_RZV_SCI_BAUD_ERROR_X_1000
#  define CONFIG_RZV_SCI_BAUD_ERROR_X_1000 1500
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
  bool      pinmux_done; /* true once rzv2h_serial_setup() has run */

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
static int  rzv_dma_setup_tx(struct uart_dev_s *dev);  /* was rzv_uart_s *priv */
static void rzv_dma_shutdown_tx(struct rzv_uart_s *priv);
static void rzv_dma_send(struct uart_dev_s *dev, const char *buffer, size_t len);
static void rzv_dma_txint(struct uart_dev_s *dev, bool enable);
static void rzv_dma_txavailable(struct uart_dev_s *dev);
#endif

#ifdef CONFIG_SERIAL_RXDMA
static void rzv_dma_rxcallback(void *handle, int event, void *user_data);
static int  rzv_dma_setup_rx(struct uart_dev_s *dev);  /* was rzv_uart_s *priv */
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

  /* SCI clock source is P5CLK (BSP_FEATURE_SCI_CLOCK), not P0CLK.
   * Use rzv_clock_get_rate(RZV_CLOCK_P5CLK) directly.
   */

  freq_hz = rzv_clock_get_rate(RZV_CLOCK_P5CLK);
  if (freq_hz == 0)
    {
      freq_hz = RZV_CLOCK_P5CLK_HZ; /* Fallback to compile-time constant */
    }

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

/* MDDR valid range is 128-255 (SCI_B_UART_MDDR_MIN=128,
 * SCI_B_UART_MDDR_MAX=256 used for division). Initialize to 128 (no
 * effective modulation) not 256 (invalid 9-bit value that masks to 0).
 */
#define SCI_B_UART_MDDR_MIN  128u
#define SCI_B_UART_MDDR_MAX  256u

  /* Initialize with default values for calculation */

  p_baud_setting->brr = 255;
  p_baud_setting->brme = 0;
  p_baud_setting->mddr = SCI_B_UART_MDDR_MIN; /* Start: no modulation (BRME=0) */

  /* Find the best BRR (bit rate register) value by trying all divisors */

  for (uint32_t select_16_base_clk_cycles = 0;
       select_16_base_clk_cycles <= 1 &&
       (hit_bit_err > CONFIG_RZV_SCI_BAUD_ERROR_X_1000);
       select_16_base_clk_cycles++)
    {
      for (uint32_t i = 0; i < 13; i++)
        {
          /* Skip divisors that don't match the clock cycle requirement */

          /* XOR of (:1) bit-fields with uint8_t cast — safe because
           * abcs and abcse are each 1-bit fields, their OR is 0 or 1, and
           * select_16_base_clk_cycles is 0 or 1.  The cast to uint8_t makes
           * the integer promotion visible.
           */

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

                  /* try MDDR modulation to reduce bit error.
                   * Formula:
                   *   mddr = err_divisor / (freq_hz / SCI_B_UART_MDDR_MAX)
                   * Only valid when mddr >= SCI_B_UART_MDDR_MIN (128).
                   * Adjusted bit error with MDDR:
                   *   adj_err = ((bit_err + 100000) * mddr / 256) - 100000
                   */

                  uint8_t mddr;
                  int32_t adj_bit_err = bit_err;
                  mddr = (uint8_t)(err_divisor / (freq_hz / SCI_B_UART_MDDR_MAX));

                  if (mddr >= SCI_B_UART_MDDR_MIN)
                    {
                      /* Adjust bit error for MDDR modulation */

                      adj_bit_err = (((bit_err + 100000) * (int32_t)mddr) /
                                     (int32_t)SCI_B_UART_MDDR_MAX) - 100000;
                      if (adj_bit_err < 0)
                        {
                          adj_bit_err = -adj_bit_err;
                        }
                    }
                  else
                    {
                      /* break out of the inner loop when mddr is
                       * below the minimum threshold rather than clamping to
                       * MIN and continuing.  Clamping lets NuttX compare
                       * adj_bit_err with the unclamped original (bit_err)
                       * which can pick a worse BRR setting that "looks
                       * better" due to the MDDR=MIN adjustment.
                       * Skip this temp_brr entirely.
                       */

                      break; /* mddr too low — no valid modulation for this BRR */
                    }

                  /* If this is the best error so far, save these settings */

                  if (adj_bit_err < hit_bit_err)
                    {
                      p_baud_setting->bgdm = g_async_baud[i].bgdm;
                      p_baud_setting->abcs = g_async_baud[i].abcs;
                      p_baud_setting->abcse = g_async_baud[i].abcse;
                      p_baud_setting->cks = g_async_baud[i].cks;
                      p_baud_setting->brr = (uint8_t)temp_brr;
                      p_baud_setting->mddr = mddr;
                      p_baud_setting->brme = (mddr > SCI_B_UART_MDDR_MIN) ? 1 : 0;
                      hit_bit_err = adj_bit_err;
                    }

                  /* removed unconditional break here.
                   * When modulation is active (mddr >= MIN), continue
                   * decrementing temp_brr to find the optimal BRR/MDDR combo.
                   * The M8 break above handles the mddr < MIN exit path.
                   */
                }
            }
        }
    }

  /* Return error if the percent error exceeds configured tolerance */

  if (hit_bit_err > CONFIG_RZV_SCI_BAUD_ERROR_X_1000)
    {
      serr("ERROR: Baud rate %lu error too high: %ld.%02ld%% (max %u.%03u%%)\n",
           (unsigned long)baudrate,
           (long)(hit_bit_err / 1000),
           (long)((hit_bit_err % 1000) / 10),
           CONFIG_RZV_SCI_BAUD_ERROR_X_1000 / 1000,
           CONFIG_RZV_SCI_BAUD_ERROR_X_1000 % 1000);
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

  /* FIFO mode enable lives in CCR3.FM (bit 20), NOT FCR.FM (bit 7
   * which is RESERVED). Set CCR3.FM before programming FCR trigger levels.
   * CCR3 was already written above; RMW to add FM bit.
   */

  rzv_sci_modifyreg(priv, RZV_SCI_CCR_OFFSET(3), 0, SCI_CCR3_FM);

  /* clear FIFO flags (FFCLR.DRC=1) before programming FCR.
   * Clears stale DR/parity/framing bits from a prior session so they are
   * not reported on the first receive in the new session.
   */

  rzv_sci_putreg(priv, RZV_SCI_FFCLR_OFFSET, SCI_FFCLR_DRC);

  /* Configure FIFO Control Register (FCR) — triggers and RTS threshold only.
   * SCI_FCR_FM removed (reserved bit).
   */

  fcr = (CONFIG_RZV_SCI_FIFO_RX_TRIGGER << SCI_FCR_RTRG_SHIFT) |
        (CONFIG_RZV_SCI_FIFO_TX_TRIGGER << SCI_FCR_TTRG_SHIFT) |
        ((priv->fifo_depth - 1) << SCI_FCR_RSTRG_SHIFT);

  rzv_sci_putreg(priv, RZV_SCI_FCR_OFFSET, fcr);

  /* Reset FIFOs: TFRST and RFRST are write-only auto-clearing trigger bits.
   * Reading FCR back always yields 0 for these bits.
   * poll FRSR.FNUM==0 (RX FIFO empty) and FTSR.T==0 (TX FIFO empty)
   * instead of spinning on FCR read (which would be an infinite loop).
   */

  rzv_sci_modifyreg(priv, RZV_SCI_FCR_OFFSET, 0,
                    SCI_FCR_TFRST | SCI_FCR_RFRST);

  /* Wait for TX FIFO to drain (FTSR.T == 0) */

  while ((rzv_sci_getreg(priv, RZV_SCI_FTSR_OFFSET) & SCI_FTSR_T_MASK) != 0)
    {
      /* Typically clears within 1 bus cycle */
    }

  /* Wait for RX FIFO to drain (FRSR.FNUM == 0) */

  while ((rzv_sci_getreg(priv, RZV_SCI_FRSR_OFFSET) & SCI_FRSR_FNUM_MASK) != 0)
    {
      /* Typically clears within 1 bus cycle */
    }
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
  /* user_data is dev (struct uart_dev_s *), not priv.
   * The former offsetof arithmetic was bogus: priv is a separate static struct,
   * not embedded inside uart_dev_s, so the offset subtraction gave a garbage ptr.
   */

  struct uart_dev_s *dev = (struct uart_dev_s *)user_data;
  struct rzv_uart_s *priv = (struct rzv_uart_s *)dev->priv;

  priv->dma_tx_active = false;

  /* Notify upper layer that DMA transfer is complete */

  uart_xmitchars_done(dev);
}

static int rzv_dma_setup_tx(struct uart_dev_s *dev)
{
  struct rzv_uart_s *priv = (struct rzv_uart_s *)dev->priv;
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
   * pass dev (not priv) as user_data so callback can get dev directly.
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
  dma_config.user_data      = dev;  /* was priv — incorrect */

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

  if (priv->dma_tx_active || priv->dma_tx_chn < 0)
    {
      return;
    }

  /* Update source buffer and byte count for the pre-configured TX channel.
   * rzv_dmac_channel_set_buffer() updates N[0].SA/TB and calls
   * up_clean_dcache() to ensure DMA reads coherent TX data.
   * Cache line alignment (32 bytes on Cortex-R8) is the caller's
   * responsibility; UART TX buffers sourced from uart_xmitchars are
   * kernel stack/heap and satisfy this on RDK-RZV2H.
   */

  if (rzv_dmac_channel_set_buffer(priv->dma_tx_chn,
                                  (uint32_t)(uintptr_t)buffer,
                                  (uint32_t)len) < 0)
    {
      return;
    }

  priv->dma_tx_active = true;

  rzv_dmac_channel_start(priv->dma_tx_chn);
}

static void rzv_dma_txint(struct uart_dev_s *dev, bool enable)
{
  /* in DMA TX mode the upper half calls txint(false) to suppress
   * TXI emission, but this no-op means TXI can still fire while DMA runs.
   * Combined with the C4 callback bug (now fixed), this caused DMA TX to
   * be effectively broken end-to-end.
   * TODO: implement TXI suppression in DMA mode by masking CCR0.TIE
   * when enable==false, re-enabling when enable==true.  Currently left as
   * no-op because the upper half's uart_xmitchars_dma path does not require
   * TXI to be masked (DMA completion triggers uart_xmitchars_done instead),
   * and the residual TXI will be a no-op after the FIFO drains.
   */
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
  /* user_data is dev (struct uart_dev_s *), not priv. */

  struct uart_dev_s *dev = (struct uart_dev_s *)user_data;

  /* Notify upper layer that data is available */

  uart_recvchars(dev);
}

static int rzv_dma_setup_rx(struct uart_dev_s *dev)
{
  struct rzv_uart_s *priv = (struct rzv_uart_s *)dev->priv;
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
  dma_config.user_data      = dev;  /* was priv — pass dev for direct cast in callback */

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

  /* run pinmux only once per channel.
   * Reconfiguring GPIO mid-transfer (e.g., on every TCSETS) can glitch the
   * TX/RX lines and cause framing errors on the peer.
   * Gate rzv2h_serial_setup() behind priv->pinmux_done so it runs exactly
   * once — on first open or first earlyserialinit call for this channel.
   */

  if (!priv->pinmux_done)
    {
      /* declaration comes from rzv_serial.h (now #included) */

      rzv2h_serial_setup();
      priv->pinmux_done = true;
    }

  /* Enable clock for this SCI channel */

  rzv_clock_enable(priv->clk_id);

  /* Deassert module reset */

  rzv_module_unreset(priv->clk_id);

  /* CRITICAL: Wait for module power-up after clock enable before register access.
   * replaced busy volatile-loop with up_udelay(10) — portable and
   * accurate. Timer must be running at this point (called from rzv_setup, not
   * early init path).
   */

  up_udelay(10);

  /* Disable transmit and receive */

  /* set CCR0=IDSEL before configuring CCR1-3.  Write IDSE first so
   * the channel is in the correct idle state while subsequent CCR writes are
   * made.  TE/RE remain 0 (channel disabled).
   */

  rzv_sci_putreg(priv, RZV_SCI_CCR_OFFSET(0), SCI_CCR0_IDSE);

  /* wait for CESR.RIST==0 and CESR.TIST==0 after CCR0=IDSE
   * to avoid a race when the channel is reopened (e.g., TCSETS baud change
   * while data is in flight).
   * CESR is a byte register at CESR_OFFSET; getreg32 reads the low byte safely.
   */

  while ((rzv_sci_getreg(priv, RZV_SCI_CESR_OFFSET) &
         (SCI_CESR_RIST | SCI_CESR_TIST)) != 0)
    {
      /* Waits for in-progress RX/TX frames to complete before reconfiguring */
    }

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

  /* IDSEL lives in CCR0 bit 10 (SCI_CCR0_IDSE), NOT CCR3.
   * The former SCI_CCR3_IDSEL write hit reserved CCR3 bit 10 — removed.
   * SCI_CCR0_IDSE is set together with TE|RE below.
   */

  rzv_sci_putreg(priv, RZV_SCI_CCR_OFFSET(3), ccr3);

  /* Configure parity.
   * CCR1 PE=bit8, PM=bit9 — now correct per updated header.
   * SPB2IO at bit5 (serial break I/O direction) is set for normal operation.
   * Removed invalid SCI_CCR1_STOP, SCI_CCR1_LSBF (now live in CCR3).
   */

  ccr1 = rzv_sci_getreg(priv, RZV_SCI_CCR_OFFSET(1));
  ccr1 &= ~(SCI_CCR1_PE | SCI_CCR1_PM | SCI_CCR1_SPB2IO);

  if (priv->parity == 1)
    {
      ccr1 |= SCI_CCR1_PE | SCI_CCR1_PM;  /* Odd parity: PE=1, PM=1 */
    }
  else if (priv->parity == 2)
    {
      ccr1 |= SCI_CCR1_PE;  /* Even parity: PE=1, PM=0 */
    }

  /* SPB2IO=1: TXD pin drives the break signal (normal UART) */

  ccr1 |= SCI_CCR1_SPB2IO;

  rzv_sci_putreg(priv, RZV_SCI_CCR_OFFSET(1), ccr1);

  /* CRITICAL: Calculate baud rate using sophisticated algorithm
   * Supports BGDM, ABCS, ABCSE, CKS, and BRME/MDDR for optimal accuracy
   */

  ret = rzv_calculate_baud_setting(priv->baud, &baud_setting);
  if (ret < 0)
    {
      serr("ERROR: Failed to calculate baud rate for %lu bps\n",
           (unsigned long)priv->baud);

      /* roll back clock enable and module unreset before returning.
       * Without cleanup, the next open sees a half-initialised channel:
       * clock is on, module is out of reset, but CCR0=0 (TE/RE not set).
       * This blocks reopen and can cause spurious interrupts from line noise.
       */

      rzv_sci_putreg(priv, RZV_SCI_CCR_OFFSET(0), 0);
      rzv_clock_disable(priv->clk_id);
      return ret;
    }

  /* Configure CCR2 with calculated baud rate settings.
   * use SCI_CCR2_BUILD() for a single write covering all fields at
   * their correct positions in CCR2_b layout (BCP=0 default,
   * BGDM=4, ABCS=5, ABCSE=6, BRR=[15:8], BRME=16, CKS=[21:20], MDDR=[31:24]).
   */

  ccr2 = SCI_CCR2_BUILD(baud_setting.mddr, baud_setting.cks,
                         baud_setting.brme, baud_setting.brr,
                         baud_setting.abcse, baud_setting.abcs,
                         baud_setting.bgdm, 0 /* BCP=0 async */);

  rzv_sci_putreg(priv, RZV_SCI_CCR_OFFSET(2), ccr2);

  /* clear all status/error flags (CFCLR) before enabling TE/RE.
   * Clears residual ORER/PER/FER from a prior session so they are not
   * re-reported on the first receive call. CFCLR=0x9D070010 (CLEAR_ALL_MASK):
   * RDRFC(31)|TDREC(29)|FERC(28)|PERC(27)|MFFC(26)|ORERC(24)|
   * DFERC(18)|DPERC(17)|DCMFC(16)|ERSC(4) = 0x9D070010
   */

  rzv_sci_putreg(priv, RZV_SCI_CFCLR_OFFSET, 0x9D070010u);

  /* Enable transmit and receive.
   * include SCI_CCR0_IDSE (idle-state edge detect) which was
   * incorrectly being written to CCR3 as SCI_CCR3_IDSEL before.
   */

  rzv_sci_putreg(priv, RZV_SCI_CCR_OFFSET(0),
                 SCI_CCR0_TE | SCI_CCR0_RE | SCI_CCR0_IDSE);

  /* CRITICAL: Wait for RIST bit before starting reception
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
  uint32_t ccr0;

  /* clearing TE before TEND==1 leaves the SCI state machine in an
   * abnormal state on the next TE=1.
   * Sequence: disable TIE/TEIE → wait CSR.TEND==1 → disable FIFO resets
   * → clear TE → wait CESR.TIST==0 → clear RE → disable clock.
   */

  /* Step 1: disable TX/TX-end interrupts to stop re-triggering */

  ccr0 = rzv_sci_getreg(priv, RZV_SCI_CCR_OFFSET(0));
  ccr0 &= ~(SCI_CCR0_TIE | SCI_CCR0_TEIE);
  rzv_sci_putreg(priv, RZV_SCI_CCR_OFFSET(0), ccr0);

  /* Step 2: wait for transmit to complete (TEND == 1) */

  while ((rzv_sci_getreg(priv, RZV_SCI_CSR_OFFSET) & SCI_CSR_TEND) == 0)
    {
      /* Wait for shift register to drain */
    }

#ifdef CONFIG_RZV_SCI_FIFO_MODE
  /* Step 3: reset TX FIFO before clearing TE */

  rzv_sci_modifyreg(priv, RZV_SCI_FCR_OFFSET, 0, SCI_FCR_TFRST);
#endif

  /* Step 4: clear TE (and RE) */

  rzv_sci_putreg(priv, RZV_SCI_CCR_OFFSET(0), 0);

  /* Step 5: wait for CESR.TIST==0 (TX stopped) and CESR.RIST==0 */

  while ((rzv_sci_getreg(priv, RZV_SCI_CESR_OFFSET) &
         (SCI_CESR_TIST | SCI_CESR_RIST)) != 0)
    {
      /* Wait for channel stop */
    }

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

  /* RSCI channels own dedicated GIC SPI lines (RZV_IRQ_SCI_* in
   * rzv2h_irq.h).  They are NOT selectable through the INTR8SEL window,
   * so rzv_icu_attach() cannot be used here: programming INTR8SEL with an
   * ELC SC event code routes an unrelated source (e.g. GPT OVF) and the
   * UART interrupts never fire.  Attach directly to the fixed INTIDs.
   *
   * GIC sense per FSP bsp_irq_sense.h: RXI/TXI edge, ERI/TEI level.
   */

  priv->irq_rxi = RZV_IRQ_SCI_RXI(priv->channel);
  priv->irq_txi = RZV_IRQ_SCI_TXI(priv->channel);
  priv->irq_tei = RZV_IRQ_SCI_TEI(priv->channel);
  priv->irq_eri = RZV_IRQ_SCI_ERI(priv->channel);

  ret = irq_attach(priv->irq_rxi, rzv_interrupt, dev);
  if (ret < 0)
    {
      serr("ERROR: Failed to attach RX interrupt for SCI%d\n", priv->channel);
      goto errout;
    }

  ret = irq_attach(priv->irq_txi, rzv_interrupt, dev);
  if (ret < 0)
    {
      serr("ERROR: Failed to attach TX interrupt for SCI%d\n", priv->channel);
      goto errout_rxi;
    }

  ret = irq_attach(priv->irq_tei, rzv_interrupt, dev);
  if (ret < 0)
    {
      serr("ERROR: Failed to attach TEI interrupt for SCI%d\n", priv->channel);
      goto errout_txi;
    }

  ret = irq_attach(priv->irq_eri, rzv_interrupt, dev);
  if (ret < 0)
    {
      serr("ERROR: Failed to attach ERI interrupt for SCI%d\n", priv->channel);
      goto errout_tei;
    }

  /* Configure GIC trigger type, then enable the four lines */

  rzv_gic_set_irq_type(priv->irq_rxi, true);   /* edge */
  rzv_gic_set_irq_type(priv->irq_txi, true);   /* edge */
  rzv_gic_set_irq_type(priv->irq_tei, false);  /* level */
  rzv_gic_set_irq_type(priv->irq_eri, false);  /* level */

  up_enable_irq(priv->irq_rxi);
  up_enable_irq(priv->irq_txi);
  up_enable_irq(priv->irq_tei);
  up_enable_irq(priv->irq_eri);

  sinfo("SCI%d: Attached interrupts RXI=%d TXI=%d TEI=%d ERI=%d\n",
        priv->channel, priv->irq_rxi, priv->irq_txi,
        priv->irq_tei, priv->irq_eri);

#ifdef CONFIG_SERIAL_TXDMA
  /* Configure DMA channel for TX if enabled */
  if (priv->dma_tx_chn >= 0)
    {
      ret = rzv_dma_setup_tx(dev);  /* was priv */
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
      ret = rzv_dma_setup_rx(dev);  /* was priv */
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
  irq_detach(priv->irq_tei);
  priv->irq_tei = -1;

errout_txi:
  irq_detach(priv->irq_txi);
  priv->irq_txi = -1;

errout_rxi:
  irq_detach(priv->irq_rxi);
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

  /* Disable interrupts and receiver/transmitter in the SCI peripheral.
   * also clear RE and TE so the channel no longer asserts ERI
   * from line noise after detach.  The channel is fully quiesced here;
   * rzv_shutdown() is called shortly after to gate the clock.
   */

  rzv_sci_putreg(priv, RZV_SCI_CCR_OFFSET(0),
                rzv_sci_getreg(priv, RZV_SCI_CCR_OFFSET(0)) &
                ~(SCI_CCR0_RIE | SCI_CCR0_TIE | SCI_CCR0_TEIE |
                  SCI_CCR0_RE  | SCI_CCR0_TE));

  /* Disable and detach the four dedicated GIC SPI lines */

  if (priv->irq_rxi >= 0)
    {
      up_disable_irq(priv->irq_rxi);
      irq_detach(priv->irq_rxi);
      priv->irq_rxi = -1;
    }

  if (priv->irq_txi >= 0)
    {
      up_disable_irq(priv->irq_txi);
      irq_detach(priv->irq_txi);
      priv->irq_txi = -1;
    }

  if (priv->irq_tei >= 0)
    {
      up_disable_irq(priv->irq_tei);
      irq_detach(priv->irq_tei);
      priv->irq_tei = -1;
    }

  if (priv->irq_eri >= 0)
    {
      up_disable_irq(priv->irq_eri);
      irq_detach(priv->irq_eri);
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

  /* Save error status bits for error recovery
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

  /* ISR processes one event per entry (no loop).
   * If TXI and RDRF assert simultaneously, only one path is handled;
   * the ELC edge-trigger will re-assert the unhandled event on the next
   * IRQ cycle, so both events will be serviced without data loss.
   * This is acceptable for ELC edge-triggered mode (no missed wakeup).
   * If level-triggered mode is ever used, add a loop here:
   *   while (csr & active_flags) { handle; csr = re-read; }
   */

  /* Handle incoming characters (Receive Data Full) */

  if ((csr & SCI_CSR_RDRF) && (ccr0 & SCI_CCR0_RIE))
    {
      uart_recvchars(dev);

      /* explicit CFCLR.RDRFC write removed — it is redundant.
       * uart_recvchars() calls rzv_receive() which reads RDR; reading RDR
       * auto-clears RDRF per SCI-B hardware spec.  The extra CFCLR write
       * was harmless but misleading (implied RDRF needed manual clearing).
       */
    }

  /* Handle outgoing characters (Transmit Data Empty — TXI source).
   * distinguish TXI (TDRE+TIE) from TEI (TEND+TEIE) to avoid
   * double uart_xmitchars dispatch. TXI = data register empty, refill it.
   * TEI = all bytes shifted out, disable TEIE to stop the TEI loop.
   */

  if ((csr & SCI_CSR_TDRE) && (ccr0 & SCI_CCR0_TIE))
    {
      /* TXI: transmit buffer empty — refill from SW FIFO */

      uart_xmitchars(dev);

      /* Clear TDRE flag (write-1-clear via CFCLR) */

      rzv_sci_putreg(priv, RZV_SCI_CFCLR_OFFSET, SCI_CFCLR_TDREC);
    }
  else if ((csr & SCI_CSR_TEND) && (ccr0 & SCI_CCR0_TEIE))
    {
      /* TEI: all data shifted out — disable TEIE to stop continuous interrupt.
       * TEND auto-clears on next TDR write; no CFCLR needed.
       */

      rzv_sci_modifyreg(priv, RZV_SCI_CCR_OFFSET(0), SCI_CCR0_TEIE, 0);
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
  struct inode      *inode  = filep->f_inode;
  struct uart_dev_s *dev    = inode->i_private;
  int ret = OK;

#ifdef CONFIG_SERIAL_TERMIOS
  struct rzv_uart_s *priv   = (struct rzv_uart_s *)dev->priv;
#else
  (void)dev;  /* suppress unused-variable when TERMIOS is off */
#endif

  switch (cmd)
    {
#ifdef CONFIG_SERIAL_TERMIOS
    /* TCGETS/TCSETS for runtime baud/parity/bits/stop
     * reconfiguration required by PX4 MAVLink baud renegotiation.
     */

    case TCGETS:
      {
        struct termios *termiosp = (struct termios *)(uintptr_t)arg;

        if (!termiosp)
          {
            ret = -EINVAL;
            break;
          }

        memset(termiosp, 0, sizeof(struct termios));

        /* Return parity settings */

        termiosp->c_cflag = ((priv->parity != 0) ? PARENB : 0) |
                            ((priv->parity == 1) ? PARODD : 0);

        /* Return stop bits */

        termiosp->c_cflag |= (priv->stopbits2) ? CSTOPB : 0;

        /* Return character size */

        switch (priv->bits)
          {
          case 7:
            termiosp->c_cflag |= CS7;
            break;
          default:
          case 8:
            termiosp->c_cflag |= CS8;
            break;
          }

        /* Return baud rate */

        cfsetispeed(termiosp, priv->baud);
        cfsetospeed(termiosp, priv->baud);
      }
      break;

    case TCSETS:
      {
        struct termios *termiosp = (struct termios *)(uintptr_t)arg;
        irqstate_t flags;
        uint32_t baud;
        uint8_t parity;
        uint8_t nbits;
        bool stop2;

        if (!termiosp)
          {
            ret = -EINVAL;
            break;
          }

        /* Decode baud rate */

        baud = cfgetispeed(termiosp);

        /* Decode character size */

        switch (termiosp->c_cflag & CSIZE)
          {
          case CS7:
            nbits = 7;
            break;
          default:
          case CS8:
            nbits = 8;
            break;
          }

        /* Decode parity */

        if ((termiosp->c_cflag & PARENB) != 0)
          {
            parity = (termiosp->c_cflag & PARODD) ? 1 : 2;
          }
        else
          {
            parity = 0;
          }

        /* Decode stop bits */

        stop2 = (termiosp->c_cflag & CSTOPB) != 0;

        /* do NOT call setup() inside critical section.
         * rzv_setup() invokes rzv_clock_enable, rzv2h_serial_setup,
         * up_udelay(10), and polling loops on CESR.RIST/TIST — all of
         * which can block indefinitely or take internal locks, causing
         * deadlock or infinite spin with IRQs disabled.
         * Only protect the priv-struct field write with critical section;
         * the heavy hardware setup runs with interrupts enabled.
         */

        flags = enter_critical_section();
        priv->baud      = baud;
        priv->parity    = parity;
        priv->bits      = nbits;
        priv->stopbits2 = stop2;
        leave_critical_section(flags);

        ret = dev->ops->setup(dev);
      }
      break;
#endif /* CONFIG_SERIAL_TERMIOS */

    default:
      ret = -ENOTTY;
      break;
    }

  return ret;
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

  /* Use saved error status
   * Combine current CSR with saved error bits to ensure
   * error conditions are not lost between interrupt and receive.
   * csr already has live error bits; OR with priv->sr is redundant
   * unless priv->sr holds bits from a prior ISR call that weren't yet read.
   * priv->sr is set only when the ISR sees an error, cleared here after
   * reporting — this creates a 1-ISR window where the same error could be
   * reported twice if csr still shows the flag. Acceptable; error recovery
   * is idempotent.
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

#ifdef CONFIG_RZV_SCI_FIFO_MODE
  /* when FIFO mode active, consult FRSR.R (bytes in RX FIFO)
   * rather than CSR.RDRF which only reflects a single-character threshold.
   */

  if (priv->fifo_depth > 0)
    {
      uint32_t frsr = rzv_sci_getreg(priv, RZV_SCI_FRSR_OFFSET);
      return ((frsr & SCI_FRSR_R_MASK) >> SCI_FRSR_R_SHIFT) > 0;
    }
#endif

  /* Non-FIFO mode: check RDRF bit in CSR */

  return (rzv_sci_getreg(priv, RZV_SCI_CSR_OFFSET) & SCI_CSR_RDRF) != 0;
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
  /* do NOT call rzv_shutdown on the console channel.
   * rzv_shutdown gates the clock; any up_putc() between shutdown and the
   * rzv_setup call below will hang on TDRE poll with clock off.
   *
   * Non-console channels are NOT shut down here either: at this point
   * their module clocks have never been enabled, and rzv_shutdown()
   * busy-waits on CSR.TEND which reads 0 with the clock gated — an
   * unconditional boot hang.  Unopened channels are already in reset
   * state; rzv_setup() fully reinitializes them on first open.
   */

  /* Configure console channel */

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
  /* Drop output until the low-level console is up (rzv_lowsetup() sets this).
   * Prevents an infinite spin in rzv_txready() when early boot code emits
   * syslog/clkinfo before the console SCI channel is clocked and enabled.
   */

  extern volatile bool g_rzv_console_ready;
  if (!g_rzv_console_ready)
    {
      return ch;
    }

  /* Wait for transmit buffer to be ready */

  while (!rzv_txready(&CONSOLE_DEV));

  /* Send the character */

  rzv_send(&CONSOLE_DEV, ch);

  return ch;
#else
  return 0;
#endif
}

#elif !defined(CONFIG_RZV_UART_SCIF)
/* No SCI devices configured AND SCIF driver not in use -> provide stubs.
 * If CONFIG_RZV_UART_SCIF=y, rzv_scif.c provides arm_serialinit / up_putc.
 */

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

#endif /* CONFIG_RZV_SCIx enabled / SCIF fallback */

#endif /* USE_SERIALDRIVER */
