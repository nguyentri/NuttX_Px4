/****************************************************************************
 * arch/arm/src/rzv/rzv_lowputc.c
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

/* complete rewrite from SCIF (RA-style 8/16-bit) to SCI-B (32-bit).
 * Previous code used 8/16-bit accessors at offsets that collided with RDR/TDR
 * in SCI-B, causing bus faults and TDR corruption on every early-boot byte.
 *
 * Strategy: trust bootloader pre-config (SPL leaves SCI3 at 115200 8N1 with
 * P3_4/P3_5 muxed) and just poll CSR.TDRE + write TDR.  If CCR0.TE==0
 * (bootloader did NOT configure the channel), perform a minimal init:
 *   CPG on → pinmux → CCR0=0 → CCR2 from hard-coded BRR table → CCR0=TE.
 * No FIFO, no IRQ, no DMA. <80 lines of active code.
 *
 * TODO: confirm with board bring-up that bootloader leaves SCI3
 * configured at 115200 8N1.  If not, the fallback init path below will engage.
 * SCI is clocked from P5CLK (100 MHz on RZ/V2H per hardware manual), NOT P0CLK.
 * BRR value below recalculated for 100 MHz P5CLK at 115200 baud.
 * TODO: confirm P5CLK = 100 MHz at board bring-up; if different,
 * recalculate LOWPUTC_CCR2_115200 accordingly.
 */

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <stdbool.h>

#include "arm_internal.h"
#include "rzv_lowputc.h"
#include "rzv_clock.h"
#include "rzv_gpio.h"
#include "hardware/rzv_sci.h"

/****************************************************************************
 * Public Data
 ****************************************************************************/

/* Guards up_putc()/early console output against being used before the console
 * SCI channel is clocked and its transmitter enabled.  Set true at the end of
 * rzv_lowsetup() (both the bootloader-pre-configured and full-init paths).
 * Lives in .bss, so rzv_ram_init() must run before rzv_lowsetup() (see
 * arm_boot() ordering) or this flag would be zeroed after being set.
 */

volatile bool g_rzv_console_ready = false;

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Select console channel by CONFIG_SCIx_SERIAL_CONSOLE.
 *
 * SCI4 (P7_0=TXD, P7_1=RXD) is the confirmed console for the NuttX nsh
 * sample configs: it maps to UART4 on the RDK 40-pin header (RDK-RZ/V2H pinout /
 * FSP pin_data.c), so it is physically reachable during bring-up.
 * SCI3 (P3_4/P3_5) remains the PX4 flight console (see boards/renesas/...),
 * but its routing to the RDK debug header is UNCONFIRMED — do not default to
 * it here.
 */

#if defined(CONFIG_SCI4_SERIAL_CONSOLE)
#  define CONSOLE_BASE   RZV_SCI4_BASE
#  define CONSOLE_CLK_ID RZV_CPG_CLK_SCI4
/* SCI4: P7_0 = TXD, P7_1 = RXD per board.h BOARD_P7_0/P7_1_GPIO */
#  define CONSOLE_TXD_GPIO  GPIO_TXD4_MOSI4_SDA4_P7_0_M1
#  define CONSOLE_RXD_GPIO  GPIO_RXD4_MISO4_SCL4_P7_1_M1
#elif defined(CONFIG_SCI3_SERIAL_CONSOLE)
#  define CONSOLE_BASE   RZV_SCI3_BASE
#  define CONSOLE_CLK_ID RZV_CPG_CLK_SCI3
/* SCI3: P3_4 = TXD, P3_5 = RXD per board.h BOARD_SCI3_TXD/RXD_GPIO */
#  define CONSOLE_TXD_GPIO  GPIO_TXD_MOSI4_SDA3_P3_4_M2
#  define CONSOLE_RXD_GPIO  GPIO_RXD_MISO3_SCL3_P3_5_M2
#elif defined(CONFIG_SCI0_SERIAL_CONSOLE)
#  define CONSOLE_BASE   RZV_SCI0_BASE
#  define CONSOLE_CLK_ID RZV_CPG_CLK_SCI0
#  define CONSOLE_TXD_GPIO  GPIO_TXD0_MOSI0_DA0_P5_0_M1
#  define CONSOLE_RXD_GPIO  GPIO_RXD0_MISO0_SCL0_P5_1_M1
#else
/* Default to SCI3 when no console is explicitly selected.
 * The PX4 flight defconfig sets CONFIG_SERIAL_CONSOLE=y but no channel-
 * specific CONFIG_SCIx_SERIAL_CONSOLE, and its src/init.c muxes the SCI3
 * console pins — so the default MUST stay SCI3 to preserve the flight
 * early-console behaviour.  The nsh sample configs opt into SCI4 explicitly
 * via CONFIG_SCI4_SERIAL_CONSOLE above.
 */
#  define CONSOLE_BASE   RZV_SCI3_BASE
#  define CONSOLE_CLK_ID RZV_CPG_CLK_SCI3
#  define CONSOLE_TXD_GPIO  GPIO_TXD_MOSI4_SDA3_P3_4_M2
#  define CONSOLE_RXD_GPIO  GPIO_RXD_MISO3_SCL3_P3_5_M2
#endif

/* CCR2 value for 115200 baud at 100 MHz P5CLK, async mode.
 * SCI clock source is P5CLK (100 MHz per RZV_CLOCK_P5CLK_HZ), not P0CLK.
 * Previous comment claimed "120 MHz P0CLK" — incorrect per RZ/V2H hardware manual
 * and rzv_clock.h (SCI clock = P5CLK = 100 MHz).
 * 100 MHz / bgdm=1 / cks=0: divisor=32, BRR=floor(100e6/32/115200)-1 = 26
 *   actual_baud = 100e6/(32*(26+1)) = 115740 Hz, error = +0.47%
 *   mddr = 256*26/26.127 ≈ 255 → negligible modulation
 * Layout: BGDM=bit4, BRR=[15:8], BRME=bit16, MDDR=[31:24].
 * TODO: verify at board bring-up; recalculate if P5CLK differs from 100 MHz.
 */
#define LOWPUTC_CCR2_115200  \
  ((255u << 24) | (1u << 16) | (26u << 8) | (1u << 4))

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_lowsetup
 *
 * Description:
 *   Called at the very beginning of _start before RAM init.
 *   Brings up the console SCI channel for early debug output.
 *   Trusts bootloader pre-config; performs minimal init only if needed.
 *
 ****************************************************************************/

void rzv_lowsetup(void)
{
  uint32_t ccr0;

  /* Check whether transmitter is already enabled (bootloader pre-config) */

  ccr0 = getreg32(CONSOLE_BASE + RZV_SCI_CCR0_OFFSET);

  if (ccr0 & SCI_CCR0_TE)
    {
      /* Bootloader left SCI configured and running — nothing to do */

      g_rzv_console_ready = true;
      return;
    }

  /* Bootloader did NOT configure the channel — perform minimal init.
   *
   * TODO: verify CPG clock-on is safe before RAM is initialized.
   * rzv_clock_enable() touches CPG registers but does not use RAM/BSS.
   */

  rzv_clock_enable(CONSOLE_CLK_ID);
  rzv_module_unreset(CONSOLE_CLK_ID);

  /* Configure GPIO pins for SCI TX/RX */

  rzv_gpioconfig(CONSOLE_TXD_GPIO | RZV_GPIO_PERIPH);
  rzv_gpioconfig(CONSOLE_RXD_GPIO | RZV_GPIO_PERIPH);

  /* Disable channel: CCR0=0, then wait for CESR.RIST/TIST to clear */

  putreg32(0, CONSOLE_BASE + RZV_SCI_CCR0_OFFSET);

  while ((getreg32(CONSOLE_BASE + RZV_SCI_CESR_OFFSET) &
         (SCI_CESR_RIST | SCI_CESR_TIST)) != 0)
    {
    }

  /* Set async 8N1 mode in CCR3: MOD=000 (async), CHR=00 (8-bit), STP=0 (1) */

  putreg32(SCI_CCR3_MOD_ASYNC | SCI_CCR3_CHR_8BIT,
           CONSOLE_BASE + RZV_SCI_CCR3_OFFSET);

  /* Program baud rate (single write, all fields at correct positions) */

  putreg32(LOWPUTC_CCR2_115200, CONSOLE_BASE + RZV_SCI_CCR2_OFFSET);

  /* Enable transmitter (TE) and IDSE.  RE not needed for early output. */

  putreg32(SCI_CCR0_TE | SCI_CCR0_IDSE,
           CONSOLE_BASE + RZV_SCI_CCR0_OFFSET);

  g_rzv_console_ready = true;
}

/****************************************************************************
 * Name: rzv_lowputc
 *
 * Description:
 *   Output one byte to the console SCI channel.
 *   Polls CSR.TDRE (Transmit Data Empty) before writing TDR.
 *
 ****************************************************************************/

void rzv_lowputc(char ch)
{
  /* Wait for transmit data register to be empty */

  while ((getreg32(CONSOLE_BASE + RZV_SCI_CSR_OFFSET) &
         SCI_CSR_TDRE) == 0)
    {
    }

  /* Write character.  TDR is 32-bit; 8-bit data goes in TDAT[7:0]. */

  putreg32((uint32_t)(uint8_t)ch, CONSOLE_BASE + RZV_SCI_TDR_OFFSET);
}

/****************************************************************************
 * Name: rzv_earlyserialinit
 *
 * Description:
 *   Called before arm_serialinit.  Console already set up by rzv_lowsetup.
 *
 ****************************************************************************/

void rzv_earlyserialinit(void)
{
  /* Console UART already initialized via rzv_lowsetup.
   * Full driver init happens in arm_earlyserialinit (rzv_serial.c).
   */
}

/****************************************************************************
 * Name: arm_lowputc
 *
 * Description:
 *   Lowest-level output (used by assertion handlers and panic).
 *
 ****************************************************************************/

void arm_lowputc(char ch)
{
  rzv_lowputc(ch);
}
