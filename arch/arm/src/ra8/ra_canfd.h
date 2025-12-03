/****************************************************************************
 * arch/arm/src/ra8/ra_canfd.h
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

#ifndef __ARCH_ARM_SRC_RA8_RA_CANFD_H
#define __ARCH_ARM_SRC_RA8_RA_CANFD_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>
#include <nuttx/can/can.h>

#ifdef CONFIG_RA_CANFD

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Maximum number of CANFD channels */

#define RA_CANFD_NUM_CHANNELS         2

/* Maximum data length for CAN FD frames */

#define RA_CANFD_MAX_DATA_LENGTH      64

/* Number of TX message buffers per channel */

#define RA_CANFD_TX_MB_COUNT          4

/* Number of RX FIFO entries */

#define RA_CANFD_RX_FIFO_DEPTH        16

/* Number of common FIFOs */

#define RA_CANFD_NUM_COMMON_FIFOS     1

/* Number of RX FIFOs */

#define RA_CANFD_NUM_RX_FIFOS         2

/* Number of AFL (Acceptance Filter List) rules per channel */

#define RA_CANFD_AFL_RULES_PER_CH     16

/* CAN FD Payload Size options */

#define RA_CANFD_PAYLOAD_8            0   /* 8 bytes */
#define RA_CANFD_PAYLOAD_12           1   /* 12 bytes */
#define RA_CANFD_PAYLOAD_16           2   /* 16 bytes */
#define RA_CANFD_PAYLOAD_20           3   /* 20 bytes */
#define RA_CANFD_PAYLOAD_24           4   /* 24 bytes */
#define RA_CANFD_PAYLOAD_32           5   /* 32 bytes */
#define RA_CANFD_PAYLOAD_48           6   /* 48 bytes */
#define RA_CANFD_PAYLOAD_64           7   /* 64 bytes */

/* CAN frame options (flags for can_frame.options) */

#define RA_CANFD_FRAME_OPTION_ERROR   0x01  /* Error state set (ESI) */
#define RA_CANFD_FRAME_OPTION_BRS     0x02  /* Bit Rate Switching enabled */
#define RA_CANFD_FRAME_OPTION_FD      0x04  /* CAN FD frame (FDF) */

/* CANFD Operation modes */

#define RA_CANFD_MODE_NORMAL          0   /* Normal operation */
#define RA_CANFD_MODE_RESET           1   /* Reset mode */
#define RA_CANFD_MODE_HALT            2   /* Halt mode */
#define RA_CANFD_MODE_SLEEP           5   /* Sleep mode */
#define RA_CANFD_MODE_GLOBAL_OP       0x80  /* Global operation mode */
#define RA_CANFD_MODE_GLOBAL_RESET    0x81  /* Global reset mode */
#define RA_CANFD_MODE_GLOBAL_HALT     0x82  /* Global halt mode */
#define RA_CANFD_MODE_GLOBAL_SLEEP    0x85  /* Global sleep mode */

/* CANFD Test modes */

#define RA_CANFD_TEST_DISABLED        0   /* Test mode disabled */
#define RA_CANFD_TEST_LISTEN          3   /* Listen only mode */
#define RA_CANFD_TEST_LOOPBACK_EXT    5   /* External loopback */
#define RA_CANFD_TEST_LOOPBACK_INT    7   /* Internal loopback */
#define RA_CANFD_TEST_INTERNAL_BUS    0x80 /* Internal CAN bus test */

/* CANFD Clock source */

#define RA_CANFD_CLK_PLL              0   /* PLL clock source */
#define RA_CANFD_CLK_MAIN_OSC         1   /* Main oscillator */

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* CAN bit timing configuration */

struct ra_canfd_timing_s
{
  uint32_t bitrate;       /* Bit rate in bps */
  uint32_t samplep;       /* Sample point in percentage (0-100) */
  uint8_t  presdiv;       /* Prescaler divisor (1-256) */
  uint8_t  propseg;       /* Propagation segment (1-8) */
  uint8_t  pseg1;         /* Phase segment 1 (1-8) */
  uint8_t  pseg2;         /* Phase segment 2 (1-8) */
  uint8_t  sjw;           /* Synchronization Jump Width (1-4) */
};

/* Acceptance Filter List entry */

struct ra_canfd_afl_entry_s
{
  uint32_t id;            /* CAN ID to match */
  uint32_t mask;          /* ID mask */
  uint8_t  id_mode;       /* 0=Standard, 1=Extended */
  uint8_t  frame_type;    /* 0=Data, 1=Remote */
  uint8_t  rx_fifo;       /* Target RX FIFO (bitmask) */
  uint8_t  rx_mb;         /* Target RX message buffer */
  uint8_t  minimum_dlc;   /* Minimum DLC to accept */
};

/* CANFD channel configuration */

struct ra_canfd_config_s
{
  uint32_t base;                          /* Channel base address */
  uint8_t  channel;                       /* Channel number (0 or 1) */
  uint32_t tx_pin;                        /* TX GPIO pin configuration */
  uint32_t rx_pin;                        /* RX GPIO pin configuration */
  int  tx_irq_event;                  /* TX interrupt ELC event */
  int  rx_fifo_irq_event;             /* RX FIFO interrupt ELC event */
  int  error_irq_event;               /* Error interrupt ELC event */
  int  global_err_irq_event;          /* Global error ELC event */
  struct ra_canfd_timing_s nominal_timing; /* Nominal bit timing */
  struct ra_canfd_timing_s data_timing;    /* Data phase bit timing (FD) */
  uint8_t  afl_rule_count;                /* Number of AFL rules */
  const struct ra_canfd_afl_entry_s *afl; /* AFL rule entries */
  bool     fd_enable;                     /* Enable CAN FD mode */
  bool     brs_enable;                    /* Enable bit rate switch */
  uint8_t  payload_size;                  /* Payload size setting */
  uint32_t bitrate;
  uint32_t dbitrate;
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************
 * Name: ra_canfd_initialize
 *
 * Description:
 *   Initialize the CANFD driver for a given channel.
 *
 * Input Parameters:
 *   channel - CANFD channel number (0 or 1)
 *
 * Returned Value:
 *   OK on success; a negated errno on failure.
 *
 ****************************************************************************/

int ra_canfd_initialize(int channel);

/****************************************************************************
 * Name: ra_canfd_register
 *
 * Description:
 *   Register the CANFD character device driver.
 *
 * Input Parameters:
 *   devpath - Path to the device (e.g., "/dev/can0")
 *   channel - CANFD channel number (0 or 1)
 *
 * Returned Value:
 *   OK on success; a negated errno on failure.
 *
 ****************************************************************************/

int ra_canfd_register(const char *devpath, int channel);

/****************************************************************************
 * Name: ra_canfd_uninitialize
 *
 * Description:
 *   Uninitialize the CANFD driver.
 *
 * Input Parameters:
 *   channel - CANFD channel number (0 or 1)
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

void ra_canfd_uninitialize(int channel);

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_RA_CANFD */

#endif /* __ARCH_ARM_SRC_RA8_RA_CANFD_H */
