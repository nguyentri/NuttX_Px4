/****************************************************************************
 * arch/arm/src/rzv/rzv_sci_i2c_internal.h
 *
 * Private types and prototypes shared between rzv_sci_i2c.c,
 * rzv_sci_i2c_isr.c, and rzv_sci_i2c_clock.c.
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

#ifndef __ARCH_ARM_SRC_RZV_RZV_SCI_I2C_INTERNAL_H
#define __ARCH_ARM_SRC_RZV_RZV_SCI_I2C_INTERNAL_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>
#include <nuttx/semaphore.h>
#include <nuttx/i2c/i2c_master.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Transfer timeout bounds (ms) */

#define SCI_I2C_TIMEOUT_MIN_MS      10u
#define SCI_I2C_TIMEOUT_MAX_MS      1000u

/* TDR mask: upper 24 bits must be 0xFF on write (DATA_REG_MASK) */

#define SCI_I2C_TDR_UPPER_MASK      UINT32_C(0xFFFFFF00)

/* Data direction for address byte */

#define SCI_I2C_WRITE_BIT           0x00u
#define SCI_I2C_READ_BIT            0x01u

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* Transfer state machine */

enum sci_i2c_state_e
{
  SCI_I2C_STATE_IDLE = 0,      /* No transfer in progress */
  SCI_I2C_STATE_ADDR,          /* Sending address byte */
  SCI_I2C_STATE_TXDATA,        /* Sending data bytes */
  SCI_I2C_STATE_RXDATA,        /* Receiving data bytes (in TXI, CPU-mode) */
  SCI_I2C_STATE_STOP,          /* STOP issued, awaiting STIF */
  SCI_I2C_STATE_START_PENDING, /* STOP complete; issue next START */
  SCI_I2C_STATE_RESTART_PENDING, /* RESTART issued, awaiting STIF (#16 fix) */
  SCI_I2C_STATE_DONE,          /* Transfer complete (success or error) */
};

/* Per-channel private structure (static, no heap allocation) */

struct rzv_sci_i2c_priv_s
{
  /* NuttX I2C master — MUST be first so casts work */

  struct i2c_master_s       dev;

  /* Channel configuration (compile-time) */

  uint8_t                   channel;    /* SCI channel */
  uint32_t                  base;       /* SCI base address */
  uint32_t                  clk_id;    /* RZV_CPG_CLK_SCIn */
  int                       evt_txi;   /* ELC event for TXI */
  int                       evt_tei;   /* ELC event for TEI */
  int                       evt_rxi;   /* ELC event for RXI */

  /* Allocated IRQ numbers (from rzv_icu_attach) */

  int                       irq_txi;
  int                       irq_tei;
  int                       irq_rxi;

  /* Pin descriptors for peripheral operation and GPIO bus recovery */

  uint32_t                  scl_gpio;
  uint32_t                  sda_gpio;
  uint32_t                  scl_reset_gpio;
  uint32_t                  sda_reset_gpio;

  /* Exclusive-access semaphore (mutex) and completion semaphore */

  sem_t                     sem_excl;  /* 1 = unlocked */
  sem_t                     sem_isr;   /* 0 = waiting; ISR posts */

  /* Current transfer context (ISR writes, transfer() reads) */

  struct i2c_msg_s         *msgs;      /* Array of messages */
  int                       msg_count; /* Total message count */
  int                       msg_idx;   /* Current message index */
  uint32_t                  byte_idx;  /* Byte index within current msg */
  bool                      do_read;       /* Current msg is read */
  bool                      do_dummy_read; /* Skip first RDR read (addr ACK) */
  int                       result;    /* Transfer result code */
  volatile enum sci_i2c_state_e state;
  uint32_t                  cur_scl_hz;

  bool                      initialized;
};

/****************************************************************************
 * Public Data
 ****************************************************************************/

/* Clock-settings struct — packed into CCR2/CCR1/ICR */

struct sci_i2c_clock_s
{
  uint8_t  brr;          /* BRR value [0..255] */
  uint8_t  cks;          /* Clock source divider index [0..3] */
  uint8_t  mddr;         /* MDDR fractional value [128..255]; 0 = disabled */
  bool     brme;         /* Bit rate modulation enable */
  uint8_t  snfr;         /* CCR1.NFCS noise filter clock select [0..7] */
  uint8_t  cycles_value; /* ICR.IICDL SDA delay cycles [0..31] (#5 fix) */
};

/****************************************************************************
 * Function Prototypes (cross-file, not public API)
 ****************************************************************************/

/* rzv_sci_i2c_clock.c */

int  sci_i2c_calc_clock(uint32_t pclk_hz, uint32_t scl_hz,
                        struct sci_i2c_clock_s *out);

/* rzv_sci_i2c_isr.c */

int  sci_i2c_txi_isr(int irq, void *context, void *arg);
int  sci_i2c_tei_isr(int irq, void *context, void *arg);
int  sci_i2c_rxi_isr(int irq, void *context, void *arg);

#endif /* __ARCH_ARM_SRC_RZV_RZV_SCI_I2C_INTERNAL_H */
