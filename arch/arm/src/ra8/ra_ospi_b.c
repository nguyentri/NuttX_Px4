/****************************************************************************
 * arch/arm/src/ra8/ra_ospi_b.c
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
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <debug.h>

#include <nuttx/arch.h>
#include <nuttx/kmalloc.h>
#include <nuttx/mutex.h>
#include <nuttx/spi/qspi.h>

#include "arm_internal.h"
#include "ra_ospi_b.h"
#include "ra_mstp.h"
#include "ra_gpio.h"
#include "ra_icu.h"
#include "ra_dmac.h"
#include "ra_clock.h"
#include "hardware/ra_memorymap.h"
#include <arch/board/board.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define RA_OSPI_TIMEOUT_US        1000000

/* OSPI_B memory-mapped address space */

#define RA_OSPI_B_MMAP_BASE_CS0   0x80000000
#define RA_OSPI_B_MMAP_BASE_CS1   0x90000000
#define RA_OSPI_B_MMAP_SIZE       0x10000000  /* 256MB per CS */

/* Protocol mode definitions */

#define RA_OSPI_PRTMD_1S_1S_1S    0x000  /* SPI mode: 1-bit CMD, 1-bit ADDR, 1-bit DATA */
#define RA_OSPI_PRTMD_1S_2S_2S    0x048  /* Dual I/O: 1-bit CMD, 2-bit ADDR, 2-bit DATA */
#define RA_OSPI_PRTMD_2S_2S_2S    0x049  /* Dual mode: 2-bit all phases */
#define RA_OSPI_PRTMD_1S_4S_4S    0x090  /* Quad I/O: 1-bit CMD, 4-bit ADDR, 4-bit DATA */
#define RA_OSPI_PRTMD_4S_4S_4S    0x092  /* Quad mode: 4-bit all phases */
#define RA_OSPI_PRTMD_4S_4D_4D    0x3B2  /* Quad DDR: 4-bit CMD SDR, 4-bit DDR ADDR/DATA */
#define RA_OSPI_PRTMD_8D_8D_8D    0x3FF  /* Octal DDR: 8-bit DDR all phases (OPI mode) */

/* Default read/write commands for SPI mode */

#define RA_OSPI_CMD_READ_SPI      0x03    /* Read Data (SPI) */
#define RA_OSPI_CMD_FAST_READ     0x0B    /* Fast Read (SPI) */
#define RA_OSPI_CMD_READ_DUAL     0x3B    /* Dual Output Fast Read */
#define RA_OSPI_CMD_READ_QUAD     0x6B    /* Quad Output Fast Read */
#define RA_OSPI_CMD_READ_OPI      0xEC13  /* Read (OPI 8D-8D-8D) - command + inverse */
#define RA_OSPI_CMD_PP_SPI        0x02    /* Page Program (SPI) */
#define RA_OSPI_CMD_PP_OPI        0x12ED  /* Page Program (OPI 8D-8D-8D) */

/* Flash status commands */

#define RA_OSPI_CMD_WREN          0x06    /* Write Enable */
#define RA_OSPI_CMD_WRDI          0x04    /* Write Disable */
#define RA_OSPI_CMD_RDSR          0x05    /* Read Status Register */
#define RA_OSPI_CMD_RDID          0x9F    /* Read JEDEC ID */
#define RA_OSPI_CMD_RESET_EN      0x66    /* Reset Enable */
#define RA_OSPI_CMD_RESET         0x99    /* Reset Device */

/* Flash status register bits */

#define RA_OSPI_SR_WIP            (1 << 0)  /* Write In Progress */
#define RA_OSPI_SR_WEL            (1 << 1)  /* Write Enable Latch */

/* CS minimum idle time (in clock cycles) */

#define RA_OSPI_CS_MIN_IDLE       7

/* Default latency cycles */

#define RA_OSPI_DEFAULT_LATENCY   0

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* Protocol mode enumeration */

enum ra_ospi_protocol_e
{
  RA_OSPI_PROTOCOL_1S_1S_1S = 0,  /* Standard SPI mode */
  RA_OSPI_PROTOCOL_1S_4S_4S,      /* Quad I/O mode */
  RA_OSPI_PROTOCOL_4S_4S_4S,      /* Quad mode */
  RA_OSPI_PROTOCOL_8D_8D_8D,      /* Octal DDR mode (OPI) */
};

struct ra_ospi_priv_s
{
  struct qspi_dev_s qspi;
  uint32_t base;
  uint32_t mmap_base;             /* Memory-mapped base address */
  mutex_t lock;
  sem_t cmdsem;                   /* Command completion semaphore */
  sem_t patsem;                   /* Pattern completion semaphore */
  sem_t dmasem;                   /* DMA completion semaphore */
  uint32_t frequency;             /* Requested frequency */
  uint32_t actual_frequency;      /* Actual OSPI clock frequency */
  int mode;
  int nbits;
  uint8_t cs;                     /* Chip select (0 or 1) */
  enum ra_ospi_protocol_e proto;  /* Current protocol mode */
  uint8_t addrlen;                /* Address length in bytes (3 or 4) */
  uint8_t read_latency;           /* Read latency cycles */
  uint8_t write_latency;          /* Write latency cycles */
  int irq_cmp;                    /* Command completion IRQ number */
  int irq_err;                    /* Error IRQ number */
  bool use_interrupts;            /* Use interrupt mode vs polling */
  bool xip_mode;                  /* XIP mode active */
  bool initialized;               /* Driver initialization state */
#ifdef CONFIG_RA_DMAC
  ra_dmac_handle_t dma_rx;        /* RX DMA handle */
  ra_dmac_handle_t dma_tx;        /* TX DMA handle */
  bool use_dma;                   /* Use DMA for transfers */
  volatile bool dma_complete;     /* DMA transfer complete flag */
  int dma_channel;                /* Assigned DMA channel (-1 = dynamic) */
#endif
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static int ra_ospi_lock(struct qspi_dev_s *dev, bool lock);
static uint32_t ra_ospi_setfrequency(struct qspi_dev_s *dev,
                                     uint32_t frequency);
static void ra_ospi_setmode(struct qspi_dev_s *dev, enum qspi_mode_e mode);
static void ra_ospi_setbits(struct qspi_dev_s *dev, int nbits);
static int ra_ospi_command(struct qspi_dev_s *dev,
                           struct qspi_cmdinfo_s *cmdinfo);
static int ra_ospi_memory(struct qspi_dev_s *dev,
                          struct qspi_meminfo_s *meminfo);
static void *ra_ospi_alloc(struct qspi_dev_s *dev, size_t buflen);
static void ra_ospi_free(struct qspi_dev_s *dev, void *buffer);

/* Internal helper functions */

static int ra_ospi_configure_protocol(struct ra_ospi_priv_s *priv);
static int ra_ospi_configure_commands(struct ra_ospi_priv_s *priv);
static int ra_ospi_flash_reset(struct ra_ospi_priv_s *priv);
static int ra_ospi_wait_ready(struct ra_ospi_priv_s *priv);
static int ra_ospi_interrupt(int irq, void *context, void *arg);
static uint32_t ra_ospi_get_clock_frequency(int port);
static int ra_ospi_autocalibrate(struct ra_ospi_priv_s *priv);
static int ra_ospi_manual_command(struct ra_ospi_priv_s *priv,
                                  uint16_t cmd, uint8_t cmdsize,
                                  uint32_t addr, uint8_t addrsize,
                                  uint8_t *data, size_t datalen,
                                  uint8_t latency, bool is_write);

#ifdef CONFIG_RA_DMAC
static void ra_ospi_get_dma_channel(struct ra_ospi_priv_s *priv, int *channel);
static int ra_ospi_dma_setup(struct ra_ospi_priv_s *priv);
static void ra_ospi_dma_callback(void *handle, int event, void *user_data);
static int ra_ospi_dma_transfer(struct ra_ospi_priv_s *priv,
                                uintptr_t dest, uintptr_t src,
                                size_t len, bool is_write);
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const struct qspi_ops_s g_ra_ospi_ops =
{
  .lock         = ra_ospi_lock,
  .setfrequency = ra_ospi_setfrequency,
  .setmode      = ra_ospi_setmode,
  .setbits      = ra_ospi_setbits,
  .command      = ra_ospi_command,
  .memory       = ra_ospi_memory,
  .alloc        = ra_ospi_alloc,
  .free         = ra_ospi_free,
};

static struct ra_ospi_priv_s g_ra_ospi0_priv =
{
  .qspi =
  {
    .ops = &g_ra_ospi_ops
  },
  .base       = R_OSPI_B_CH_BASE(0),
  .mmap_base  = RA_OSPI_B_MMAP_BASE_CS0,
  .lock       = NXMUTEX_INITIALIZER,
  .cmdsem     = SEM_INITIALIZER(0),
  .patsem     = SEM_INITIALIZER(0),
#ifdef CONFIG_RA_DMAC
  .dmasem     = SEM_INITIALIZER(0),
#endif
  .cs         = 0,
  .proto      = RA_OSPI_PROTOCOL_1S_1S_1S,
  .addrlen    = 4,
  .read_latency  = RA_OSPI_DEFAULT_LATENCY,
  .write_latency = RA_OSPI_DEFAULT_LATENCY,
  .irq_cmp    = -1,
  .irq_err    = -1,
  .use_interrupts = true,
  .xip_mode   = false,
  .initialized = false,
#ifdef CONFIG_RA_DMAC
  .dma_rx     = NULL,
  .dma_tx     = NULL,
  .use_dma    = true,
  .dma_complete = false,
#endif
};

static struct ra_ospi_priv_s g_ra_ospi1_priv =
{
  .qspi =
  {
    .ops = &g_ra_ospi_ops
  },
  .base       = R_OSPI_B_CH_BASE(1),
  .mmap_base  = RA_OSPI_B_MMAP_BASE_CS1,
  .lock       = NXMUTEX_INITIALIZER,
  .cmdsem     = SEM_INITIALIZER(0),
  .patsem     = SEM_INITIALIZER(0),
#ifdef CONFIG_RA_DMAC
  .dmasem     = SEM_INITIALIZER(0),
#endif
  .cs         = 1,
  .proto      = RA_OSPI_PROTOCOL_1S_1S_1S,
  .addrlen    = 4,
  .read_latency  = RA_OSPI_DEFAULT_LATENCY,
  .write_latency = RA_OSPI_DEFAULT_LATENCY,
  .irq_cmp    = -1,
  .irq_err    = -1,
  .use_interrupts = true,
  .xip_mode   = false,
  .initialized = false,
#ifdef CONFIG_RA_DMAC
  .dma_rx     = NULL,
  .dma_tx     = NULL,
  .use_dma    = true,
  .dma_complete = false,
#endif
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_ospi_getreg / ra_ospi_putreg
 *
 * Description:
 *   Register access helpers
 *
 ****************************************************************************/

static inline uint32_t ra_ospi_getreg(struct ra_ospi_priv_s *priv,
                                      uint32_t offset)
{
  return getreg32(priv->base + offset);
}

static inline void ra_ospi_putreg(struct ra_ospi_priv_s *priv,
                                  uint32_t offset, uint32_t value)
{
  putreg32(value, priv->base + offset);
}

static inline void ra_ospi_modifyreg(struct ra_ospi_priv_s *priv,
                                     uint32_t offset,
                                     uint32_t clearbits, uint32_t setbits)
{
  uint32_t regval = ra_ospi_getreg(priv, offset);
  regval = (regval & ~clearbits) | setbits;
  ra_ospi_putreg(priv, offset, regval);
}

/****************************************************************************
 * Name: ra_ospi_interrupt
 *
 * Description:
 *   OSPI interrupt handler for command completion and errors
 *
 ****************************************************************************/

static int ra_ospi_interrupt(int irq, void *context, void *arg)
{
  struct ra_ospi_priv_s *priv = (struct ra_ospi_priv_s *)arg;
  uint32_t ints;

  DEBUGASSERT(priv != NULL);

  /* Read interrupt status */

  ints = ra_ospi_getreg(priv, R_OSPI_B_INTS_OFFSET);

  /* Handle command completion */

  if (ints & R_OSPI_B_INTS_CMDCMP)
    {
      /* Clear interrupt */

      ra_ospi_putreg(priv, R_OSPI_B_INTC_OFFSET, R_OSPI_B_INTC_CMDCMPC);

      /* Wake up waiting thread */

      nxsem_post(&priv->cmdsem);
    }

  /* Handle pattern completion */

  if (ints & R_OSPI_B_INTS_PATCMP)
    {
      ra_ospi_putreg(priv, R_OSPI_B_INTC_OFFSET, R_OSPI_B_INTC_PATCMPC);
      nxsem_post(&priv->patsem);
    }

  /* Handle errors */

  if (ints & (R_OSPI_B_INTS_DSTOCS0 | R_OSPI_B_INTS_DSTOCS1 |
              R_OSPI_B_INTS_BUSERRCH0 | R_OSPI_B_INTS_BUSERRCH1 |
              R_OSPI_B_INTS_CAFAILCS0 | R_OSPI_B_INTS_CAFAILCS1))
    {
      spierr("OSPI_B: Error interrupt INTS=0x%08lx\n", ints);

      /* Clear error interrupts */

      ra_ospi_putreg(priv, R_OSPI_B_INTC_OFFSET,
                     R_OSPI_B_INTC_DSTOCS0C | R_OSPI_B_INTC_DSTOCS1C |
                     R_OSPI_B_INTC_BUSERRCH0C | R_OSPI_B_INTC_BUSERRCH1C |
                     R_OSPI_B_INTC_CAFAILCS0C | R_OSPI_B_INTC_CAFAILCS1C);

      /* Wake up with error status */

      nxsem_post(&priv->cmdsem);
      nxsem_post(&priv->patsem);
    }

  return OK;
}

/****************************************************************************
 * Name: ra_ospi_wait_cmdcmp
 *
 * Description:
 *   Wait for command completion using interrupts or polling
 *
 ****************************************************************************/

static int ra_ospi_wait_cmdcmp(struct ra_ospi_priv_s *priv)
{
  uint32_t regval;
  int ret;

  /* Wait for TRREQ to be cleared (command accepted) - always poll this */

  int retries = RA_OSPI_TIMEOUT_US;
  while (retries > 0)
    {
      regval = ra_ospi_getreg(priv, R_OSPI_B_CDCTL0_OFFSET);
      if ((regval & R_OSPI_B_CDCTL0_TRREQ) == 0)
        {
          break;
        }
      up_udelay(1);
      retries--;
    }

  if (retries == 0)
    {
      spierr("OSPI_B: TRREQ timeout\n");
      return -ETIMEDOUT;
    }

  /* Use interrupt-based waiting if enabled */

  if (priv->use_interrupts && priv->irq_cmp >= 0)
    {
      /* Wait for interrupt with timeout (1 second) */

      struct timespec abstime;
      clock_gettime(CLOCK_REALTIME, &abstime);
      abstime.tv_sec += 1;

      ret = nxsem_timedwait_uninterruptible(&priv->cmdsem, &abstime);
      if (ret < 0)
        {
          spierr("OSPI_B: Command wait failed: %d\n", ret);
          return ret;
        }

      /* Check for errors */

      regval = ra_ospi_getreg(priv, R_OSPI_B_INTS_OFFSET);
      if (regval & (R_OSPI_B_INTS_DSTOCS0 | R_OSPI_B_INTS_BUSERRCH0))
        {
          spierr("OSPI_B: Command error INTS=0x%08lx\n", regval);
          return -EIO;
        }

      return OK;
    }

  /* Fallback to polling mode */

  retries = RA_OSPI_TIMEOUT_US;
  while (retries > 0)
    {
      regval = ra_ospi_getreg(priv, R_OSPI_B_INTS_OFFSET);
      if (regval & R_OSPI_B_INTS_CMDCMP)
        {
          ra_ospi_putreg(priv, R_OSPI_B_INTC_OFFSET, R_OSPI_B_INTC_CMDCMPC);
          return OK;
        }

      if (regval & (R_OSPI_B_INTS_DSTOCS0 | R_OSPI_B_INTS_BUSERRCH0))
        {
          spierr("OSPI_B: Command error INTS=0x%08lx\n", regval);
          ra_ospi_putreg(priv, R_OSPI_B_INTC_OFFSET,
                         R_OSPI_B_INTC_DSTOCS0C | R_OSPI_B_INTC_BUSERRCH0C);
          return -EIO;
        }

      up_udelay(1);
      retries--;
    }

  spierr("OSPI_B: CMDCMP timeout\n");
  return -ETIMEDOUT;
}

/****************************************************************************
 * Name: ra_ospi_wait_patcmp
 *
 * Description:
 *   Wait for pattern (reset) completion using interrupts or polling
 *
 ****************************************************************************/

static int ra_ospi_wait_patcmp(struct ra_ospi_priv_s *priv)
{
  uint32_t regval;
  int ret;

  /* Use interrupt-based waiting if enabled */

  if (priv->use_interrupts && priv->irq_cmp >= 0)
    {
      struct timespec abstime;
      clock_gettime(CLOCK_REALTIME, &abstime);
      abstime.tv_sec += 1;

      ret = nxsem_timedwait_uninterruptible(&priv->patsem, &abstime);
      if (ret < 0)
        {
          spierr("OSPI_B: Pattern wait failed: %d\n", ret);
          return ret;
        }

      return OK;
    }

  /* Fallback to polling */

  int retries = RA_OSPI_TIMEOUT_US;
  while (retries > 0)
    {
      regval = ra_ospi_getreg(priv, R_OSPI_B_INTS_OFFSET);
      if (regval & R_OSPI_B_INTS_PATCMP)
        {
          ra_ospi_putreg(priv, R_OSPI_B_INTC_OFFSET, R_OSPI_B_INTC_PATCMPC);
          return OK;
        }
      up_udelay(1);
      retries--;
    }

  return -ETIMEDOUT;
}

/****************************************************************************
 * Name: ra_ospi_manual_command
 *
 * Description:
 *   Execute a command using manual mode via CDxBUF registers
 *
 * Input Parameters:
 *   priv     - OSPI driver private data
 *   cmd      - Command byte(s)
 *   cmdsize  - Command size (1 or 2 bytes)
 *   addr     - Address value
 *   addrsize - Address size in bytes (0-4)
 *   data     - Data buffer for read/write
 *   datalen  - Data length in bytes
 *   latency  - Latency cycles (dummy cycles)
 *   is_write - true for write, false for read
 *
 ****************************************************************************/

static int ra_ospi_manual_command(struct ra_ospi_priv_s *priv,
                                  uint16_t cmd, uint8_t cmdsize,
                                  uint32_t addr, uint8_t addrsize,
                                  uint8_t *data, size_t datalen,
                                  uint8_t latency, bool is_write)
{
  uint32_t cdtbuf = 0;
  uint32_t cdctl0 = 0;
  uint32_t data0 = 0;
  uint32_t data1 = 0;
  int ret;

  /* Build CDTBUF register value */

  /* Command size field (bits 1:0) */

  if (cmdsize == 2)
    {
      cdtbuf |= R_OSPI_B_CDTBUF_CMDSIZE_10;  /* 2-byte command */
    }
  else if (cmdsize == 1)
    {
      cdtbuf |= R_OSPI_B_CDTBUF_CMDSIZE_01;  /* 1-byte command */
    }
  else
    {
      cdtbuf |= R_OSPI_B_CDTBUF_CMDSIZE_00;  /* No command */
    }

  /* Address size field (bits 4:2)
   * Per datasheet: command is placed in upper byte(s) of CMD field
   * For 1-byte command: place in bits [31:24] of CDTBUF
   * For 2-byte command: place in bits [31:16] of CDTBUF
   */

  cdtbuf |= ((addrsize & 0x7) << R_OSPI_B_CDTBUF_ADDSIZE_SHIFT);

  /* Data size field (bits 8:5) - number of bytes (0-8 for manual mode) */

  if (datalen > 8)
    {
      datalen = 8;  /* Max 8 bytes in manual mode (CDD0BUF + CDD1BUF) */
    }
  cdtbuf |= ((datalen & 0xf) << R_OSPI_B_CDTBUF_DATASIZE_SHIFT);

  /* Latency cycles (bits 13:9) */

  cdtbuf |= ((latency & 0x1f) << R_OSPI_B_CDTBUF_LATE_SHIFT);

  /* Transaction type: bit 15 = 1 for write, 0 for read */

  if (is_write)
    {
      cdtbuf |= R_OSPI_B_CDTBUF_TRTYPE;
    }

  /* Command value in upper 16 bits
   * For 1-byte commands: shift to bits [31:24], leave [23:16] as 0
   * For 2-byte commands: place in bits [31:16]
   */

  if (cmdsize == 1)
    {
      cdtbuf |= ((uint32_t)(cmd & 0xff) << 24);
    }
  else if (cmdsize == 2)
    {
      cdtbuf |= ((uint32_t)cmd << 16);
    }

  /* Write command buffer registers */

  ra_ospi_putreg(priv, R_OSPI_B_CDTBUF_OFFSET(0), cdtbuf);

  /* Write address if present */

  if (addrsize > 0)
    {
      ra_ospi_putreg(priv, R_OSPI_B_CDABUF_OFFSET(0), addr);
    }

  /* Write data for write operations */

  if (is_write && data != NULL && datalen > 0)
    {
      /* Pack data into CDD0BUF (first 4 bytes) and CDD1BUF (next 4 bytes) */

      if (datalen <= 4)
        {
          memcpy(&data0, data, datalen);
        }
      else
        {
          memcpy(&data0, data, 4);
          memcpy(&data1, data + 4, datalen - 4);
        }
      ra_ospi_putreg(priv, R_OSPI_B_CDD0BUF_OFFSET(0), data0);
      if (datalen > 4)
        {
          ra_ospi_putreg(priv, R_OSPI_B_CDD1BUF_OFFSET(0), data1);
        }
    }

  /* Configure CDCTL0 and trigger transaction
   * TRNUM = 0 (single command in buffer 0)
   * CSSEL = chip select
   * TRREQ = 1 (trigger transaction)
   */

  cdctl0 = R_OSPI_B_CDCTL0_TRREQ | R_OSPI_B_CDCTL0_TRNUM_00;
  if (priv->cs == 1)
    {
      cdctl0 |= R_OSPI_B_CDCTL0_CSSEL;
    }

  ra_ospi_putreg(priv, R_OSPI_B_CDCTL0_OFFSET, cdctl0);

  /* Wait for completion */

  ret = ra_ospi_wait_cmdcmp(priv);
  if (ret < 0)
    {
      spierr("OSPI_B: manual command failed ret=%d\n", ret);
      return ret;
    }

  /* Read data for read operations */

  if (!is_write && data != NULL && datalen > 0)
    {
      data0 = ra_ospi_getreg(priv, R_OSPI_B_CDD0BUF_OFFSET(0));
      if (datalen <= 4)
        {
          memcpy(data, &data0, datalen);
        }
      else
        {
          memcpy(data, &data0, 4);
          data1 = ra_ospi_getreg(priv, R_OSPI_B_CDD1BUF_OFFSET(0));
          memcpy(data + 4, &data1, datalen - 4);
        }
    }

  return OK;
}

/****************************************************************************
 * Name: ra_ospi_flash_reset
 *
 * Description:
 *   Reset the flash device using xSPI reset signaling protocol
 *
 ****************************************************************************/

static int ra_ospi_flash_reset(struct ra_ospi_priv_s *priv)
{
  uint32_t lpctl1;
  int ret;

  spiinfo("OSPI_B: Issuing flash reset\n");

  /* Configure LPCTL1 for reset pattern:
   * PATREQ[1:0] = 01 (Request Reset pattern)
   * CSSEL = chip select
   * RSTREP[1:0] = 00 (4 times - per xSPI reset signaling protocol)
   * RSTWID = minimum width
   * RSTSU = setup time
   */

  lpctl1 = R_OSPI_B_LPCTL1_PATREQ_01;  /* Reset pattern request */
  lpctl1 |= (0 << R_OSPI_B_LPCTL1_RSTREP_SHIFT);  /* 4 repetitions */
  lpctl1 |= (4 << R_OSPI_B_LPCTL1_RSTWID_SHIFT);  /* Reset width */
  lpctl1 |= (4 << R_OSPI_B_LPCTL1_RSTSU_SHIFT);   /* Setup time */
  if (priv->cs == 1)
    {
      lpctl1 |= R_OSPI_B_LPCTL1_CSSEL;
    }

  ra_ospi_putreg(priv, R_OSPI_B_LPCTL1_OFFSET, lpctl1);

  /* Wait for pattern completion */

  ret = ra_ospi_wait_patcmp(priv);
  if (ret < 0)
    {
      spierr("OSPI_B: Reset pattern timeout\n");

      /* Try software reset via commands as fallback */

      ret = ra_ospi_manual_command(priv, RA_OSPI_CMD_RESET_EN, 1,
                                   0, 0, NULL, 0, 0, true);
      if (ret == OK)
        {
          up_udelay(50);
          ret = ra_ospi_manual_command(priv, RA_OSPI_CMD_RESET, 1,
                                       0, 0, NULL, 0, 0, true);
        }
    }

  /* Clear LPCTL1 */

  ra_ospi_putreg(priv, R_OSPI_B_LPCTL1_OFFSET, 0);

  /* Wait for reset recovery (tRST typically 10-50ms) */

  up_mdelay(50);

  return ret;
}

/****************************************************************************
 * Name: ra_ospi_configure_protocol
 *
 * Description:
 *   Configure LIOCFGCS register for protocol mode (1S-1S-1S, 8D-8D-8D, etc.)
 *
 ****************************************************************************/

static int ra_ospi_configure_protocol(struct ra_ospi_priv_s *priv)
{
  uint32_t liocfgcs = 0;
  uint32_t prtmd;

  /* Select protocol mode encoding */

  switch (priv->proto)
    {
      case RA_OSPI_PROTOCOL_1S_1S_1S:
        prtmd = RA_OSPI_PRTMD_1S_1S_1S;
        break;

      case RA_OSPI_PROTOCOL_1S_4S_4S:
        prtmd = RA_OSPI_PRTMD_1S_4S_4S;
        break;

      case RA_OSPI_PROTOCOL_4S_4S_4S:
        prtmd = RA_OSPI_PRTMD_4S_4S_4S;
        break;

      case RA_OSPI_PROTOCOL_8D_8D_8D:
        prtmd = RA_OSPI_PRTMD_8D_8D_8D;
        break;

      default:
        prtmd = RA_OSPI_PRTMD_1S_1S_1S;
        break;
    }

  /* Build LIOCFGCS register value */

  liocfgcs = (prtmd & R_OSPI_B_LIOCFGCS_PRTMD_MASK);

  /* CS minimum idle time */

  liocfgcs |= ((RA_OSPI_CS_MIN_IDLE << R_OSPI_B_LIOCFGCS_CSMIN_SHIFT)
               & R_OSPI_B_LIOCFGCS_CSMIN_MASK);

  /* For DDR modes (8D-8D-8D), configure latency mode and data strobe */

  if (priv->proto == RA_OSPI_PROTOCOL_8D_8D_8D)
    {
      liocfgcs |= R_OSPI_B_LIOCFGCS_LATEMD;   /* Latency mode enabled */
      liocfgcs |= R_OSPI_B_LIOCFGCS_WRMSKMD;  /* Write mask mode for OPI */
    }
  else
    {
      /* SDR modes: configure SDR sampling */

      liocfgcs |= R_OSPI_B_LIOCFGCS_SDRDRV;    /* SDR drive on falling edge */
      liocfgcs |= R_OSPI_B_LIOCFGCS_SDRSMPMD;  /* SDR sample on rising edge */
    }

  /* Write to appropriate CS register */

  ra_ospi_putreg(priv, R_OSPI_B_LIOCFGCS_OFFSET(priv->cs), liocfgcs);

  spiinfo("OSPI_B: LIOCFGCS[%d]=0x%08lx proto=%d\n",
          priv->cs, liocfgcs, priv->proto);

  return OK;
}

/****************************************************************************
 * Name: ra_ospi_configure_commands
 *
 * Description:
 *   Configure CMCFG0CS, CMCFG1CS, CMCFG2CS for memory-mapped read/write
 *
 ****************************************************************************/

static int ra_ospi_configure_commands(struct ra_ospi_priv_s *priv)
{
  uint32_t cmcfg0 = 0;
  uint32_t cmcfg1 = 0;
  uint32_t cmcfg2 = 0;
  uint16_t rdcmd;
  uint16_t wrcmd;

  /* CMCFG0CS: Frame format and address size */

  if (priv->proto == RA_OSPI_PROTOCOL_8D_8D_8D)
    {
      /* OPI mode: 2-byte commands, 8D-8D-8D profile */

      cmcfg0 = R_OSPI_B_CMCFG0CS_FFMT_01;  /* 8D-8D-8D profile 1.0 format */
      rdcmd = RA_OSPI_CMD_READ_OPI;        /* 0xEC13 for OPI read */
      wrcmd = RA_OSPI_CMD_PP_OPI;          /* 0x12ED for OPI write */
    }
  else
    {
      /* SPI mode: 1-byte commands, normal format */

      cmcfg0 = R_OSPI_B_CMCFG0CS_FFMT_00;  /* Normal format */
      rdcmd = RA_OSPI_CMD_READ_SPI;        /* 0x03 for SPI read */
      wrcmd = RA_OSPI_CMD_PP_SPI;          /* 0x02 for SPI write */
    }

  /* Address size configuration */

  switch (priv->addrlen)
    {
      case 1:
        cmcfg0 |= R_OSPI_B_CMCFG0CS_ADDSIZE_00;
        break;
      case 2:
        cmcfg0 |= R_OSPI_B_CMCFG0CS_ADDSIZE_01;
        break;
      case 3:
        cmcfg0 |= R_OSPI_B_CMCFG0CS_ADDSIZE_10;
        break;
      case 4:
      default:
        cmcfg0 |= R_OSPI_B_CMCFG0CS_ADDSIZE_11;
        break;
    }

  /* CMCFG1CS: Read command and latency */

  cmcfg1 = ((rdcmd << R_OSPI_B_CMCFG1CS_RDCMD_SHIFT)
            & R_OSPI_B_CMCFG1CS_RDCMD_MASK);
  cmcfg1 |= ((priv->read_latency << R_OSPI_B_CMCFG1CS_RDLATE_SHIFT)
             & R_OSPI_B_CMCFG1CS_RDLATE_MASK);

  /* CMCFG2CS: Write command and latency */

  cmcfg2 = ((wrcmd << R_OSPI_B_CMCFG2CS_WRCMD_SHIFT)
            & R_OSPI_B_CMCFG2CS_WRCMD_MASK);
  cmcfg2 |= ((priv->write_latency << R_OSPI_B_CMCFG2CS_WRLATE_SHIFT)
             & R_OSPI_B_CMCFG2CS_WRLATE_MASK);

  /* Write configuration registers */

  ra_ospi_putreg(priv, R_OSPI_B_CMCFG0CS_OFFSET(priv->cs), cmcfg0);
  ra_ospi_putreg(priv, R_OSPI_B_CMCFG1CS_OFFSET(priv->cs), cmcfg1);
  ra_ospi_putreg(priv, R_OSPI_B_CMCFG2CS_OFFSET(priv->cs), cmcfg2);

  spiinfo("OSPI_B: CMCFG0CS[%d]=0x%08lx CMCFG1CS=0x%08lx CMCFG2CS=0x%08lx\n",
          priv->cs, cmcfg0, cmcfg1, cmcfg2);

  return OK;
}

/****************************************************************************
 * Name: ra_ospi_configure_bridge
 *
 * Description:
 *   Configure BMCTL0, BMCTL1, BMCFGCH for memory-mapped access
 *
 ****************************************************************************/

static int ra_ospi_configure_bridge(struct ra_ospi_priv_s *priv)
{
  uint32_t bmctl0;
  uint32_t bmcfgch = 0;

  /* BMCTL0: Enable read/write access for the appropriate CS
   * CH0CS0ACC[1:0] = 11 (read/write enable for channel 0, CS0)
   * CH0CS1ACC[1:0] = 11 (read/write enable for channel 0, CS1)
   */

  bmctl0 = ra_ospi_getreg(priv, R_OSPI_B_BMCTL0_OFFSET);

  if (priv->cs == 0)
    {
      bmctl0 &= ~R_OSPI_B_BMCTL0_CH0CS0ACC_MASK;
      bmctl0 |= R_OSPI_B_BMCTL0_CH0CS0ACC_11;  /* Read/write enable */
    }
  else
    {
      bmctl0 &= ~R_OSPI_B_BMCTL0_CH0CS1ACC_MASK;
      bmctl0 |= R_OSPI_B_BMCTL0_CH0CS1ACC_11;  /* Read/write enable */
    }

  ra_ospi_putreg(priv, R_OSPI_B_BMCTL0_OFFSET, bmctl0);

  /* BMCFGCH: Bridge map configuration for channel
   * WRMD = 0 (wait for write completion before response)
   * MWRCOMB = 1 (enable write combination for better performance)
   * MWRSIZE = page size (typically 256 bytes = 0x100)
   * PREEN = 1 (enable prefetch for read performance)
   * CMBTIM = combination timer value
   */

  bmcfgch = R_OSPI_B_BMCFGCH_MWRCOMB;     /* Enable write combination */
  bmcfgch |= R_OSPI_B_BMCFGCH_PREEN;       /* Enable prefetch */
  bmcfgch |= (0x100 << R_OSPI_B_BMCFGCH_MWRSIZE_SHIFT);  /* 256-byte write size */
  bmcfgch |= (0x0f << R_OSPI_B_BMCFGCH_CMBTIM_SHIFT);    /* Combination timeout */

  ra_ospi_putreg(priv, R_OSPI_B_BMCFGCH_OFFSET(0), bmcfgch);

  spiinfo("OSPI_B: BMCTL0=0x%08lx BMCFGCH[0]=0x%08lx\n", bmctl0, bmcfgch);

  return OK;
}

/****************************************************************************
 * Name: ra_ospi_configure_wrapper
 *
 * Description:
 *   Configure WRAPCFG for data strobe timing
 *
 ****************************************************************************/

static int ra_ospi_configure_wrapper(struct ra_ospi_priv_s *priv)
{
  uint32_t wrapcfg = 0;

  /* WRAPCFG: Data strobe shift configuration
   * DSSFTCS0[4:0] = Data strobe shift for CS0 (default 0)
   * DSSFTCS1[4:0] = Data strobe shift for CS1 (default 0)
   * Values adjusted during calibration for optimal timing
   */

  /* Start with no shift, calibration will adjust if needed */

  ra_ospi_putreg(priv, R_OSPI_B_WRAPCFG_OFFSET, wrapcfg);

  spiinfo("OSPI_B: WRAPCFG=0x%08lx\n", wrapcfg);

  return OK;
}

/****************************************************************************
 * Name: ra_ospi_wait_ready
 *
 * Description:
 *   Wait for the OSPI bus to be idle (no ongoing memory access)
 *
 ****************************************************************************/

static int ra_ospi_wait_ready(struct ra_ospi_priv_s *priv)
{
  uint32_t regval;
  int retries = RA_OSPI_TIMEOUT_US;

  while (retries > 0)
    {
      regval = ra_ospi_getreg(priv, R_OSPI_B_COMSTT_OFFSET);

      /* Check if no memory access is ongoing */

      if ((regval & (R_OSPI_B_COMSTT_MEMACCCH0 |
                     R_OSPI_B_COMSTT_WRBUFNECH0)) == 0)
        {
          return OK;
        }

      up_udelay(1);
      retries--;
    }

  return -ETIMEDOUT;
}

/****************************************************************************
 * Name: ra_ospi_flush_prefetch
 *
 * Description:
 *   Clear prefetch buffer before write operations
 *
 ****************************************************************************/

static void ra_ospi_flush_prefetch(struct ra_ospi_priv_s *priv)
{
  /* Set PBUFCLRCH0 to clear prefetch buffer */

  ra_ospi_putreg(priv, R_OSPI_B_BMCTL1_OFFSET, R_OSPI_B_BMCTL1_PBUFCLRCH0);

  /* Wait a few cycles for buffer clear */

  up_udelay(1);

  /* Clear the bit */

  ra_ospi_putreg(priv, R_OSPI_B_BMCTL1_OFFSET, 0);
}

/****************************************************************************
 * Name: ra_ospi_push_write_buffer
 *
 * Description:
 *   Push any pending write data to flash
 *
 ****************************************************************************/

static void ra_ospi_push_write_buffer(struct ra_ospi_priv_s *priv)
{
  uint32_t comstt;

  /* Check if write buffer has data */

  comstt = ra_ospi_getreg(priv, R_OSPI_B_COMSTT_OFFSET);
  if (comstt & R_OSPI_B_COMSTT_WRBUFNECH0)
    {
      /* Set MWRPUSHCH0 to push write data */

      ra_ospi_putreg(priv, R_OSPI_B_BMCTL1_OFFSET, R_OSPI_B_BMCTL1_MWRPUSHCH0);

      /* Wait for write buffer to empty */

      ra_ospi_wait_ready(priv);

      /* Clear the bit */

      ra_ospi_putreg(priv, R_OSPI_B_BMCTL1_OFFSET, 0);
    }
}

/****************************************************************************
 * Name: ra_ospi_lock
 *
 * Description:
 *   Lock/unlock the QSPI device
 *
 ****************************************************************************/

static int ra_ospi_lock(struct qspi_dev_s *dev, bool lock)
{
  struct ra_ospi_priv_s *priv = (struct ra_ospi_priv_s *)dev;

  if (lock)
    {
      return nxmutex_lock(&priv->lock);
    }
  else
    {
      return nxmutex_unlock(&priv->lock);
    }
}

/****************************************************************************
 * Name: ra_ospi_get_clock_frequency
 *
 * Description:
 *   Get the actual OSPI clock frequency from the system configuration
 *
 ****************************************************************************/

static uint32_t ra_ospi_get_clock_frequency(int port)
{
  /* OSPI clock is derived from OCTACLK peripheral clock
   * Query the actual frequency from the clock system
   */

  uint32_t octaclk_freq;

  UNUSED(port);  /* Port parameter not used, frequency same for both ports */

  /* Get OCTACLK frequency from clock management system */

  octaclk_freq = ra_get_peripheral_clock(RA_PCLK_OCTACLK);

  if (octaclk_freq == 0)
    {
      /* Fallback if clock API returns 0 (OSPI not configured) */

      spiwarn("OSPI_B: OCTACLK not configured, using default 100MHz\n");
      octaclk_freq = 100000000;
    }

  spiinfo("OSPI_B: OCTACLK frequency = %lu Hz\n", octaclk_freq);

  return octaclk_freq;
}

/****************************************************************************
 * Name: ra_ospi_setfrequency
 *
 * Description:
 *   Set the OSPI clock frequency. The OSPI clock is derived from OCTACLK
 *   which is configured at system initialization. This function validates
 *   the requested frequency against the actual hardware configuration.
 *
 *   Note: The OSPI_B peripheral uses the OCTACLK peripheral clock which
 *   is typically derived from PLL2P with a configurable divider set in
 *   the system clock configuration (OCTACKDIVCR register).
 *
 ****************************************************************************/

static uint32_t ra_ospi_setfrequency(struct qspi_dev_s *dev,
                                     uint32_t frequency)
{
  struct ra_ospi_priv_s *priv = (struct ra_ospi_priv_s *)dev;
  uint32_t actual_freq;

  /* Store requested frequency */

  priv->frequency = frequency;

  /* Get actual configured OCTACLK frequency from clock system */

  actual_freq = ra_ospi_get_clock_frequency(priv->cs);
  priv->actual_frequency = actual_freq;

  /* Validate requested vs actual frequency */

  if (frequency > actual_freq)
    {
      spiwarn("OSPI_B: Requested %lu Hz exceeds actual %lu Hz\n",
              (unsigned long)frequency, (unsigned long)actual_freq);
      spiwarn("OSPI_B: Adjust CONFIG_RA_OCTACLK_SOURCE/DIV to meet requirement\n");
    }
  else if (frequency < (actual_freq / 2))
    {
      spiinfo("OSPI_B: Requested %lu Hz is much lower than actual %lu Hz\n",
              (unsigned long)frequency, (unsigned long)actual_freq);
      spiinfo("OSPI_B: Consider reducing OCTACLK divider for better performance\n");
    }

  spiinfo("OSPI_B: Frequency set - Requested: %lu Hz, Actual: %lu Hz\n",
          (unsigned long)frequency, (unsigned long)actual_freq);

  return actual_freq;
}

/****************************************************************************
 * Name: ra_ospi_setmode
 *
 * Description:
 *   Set the SPI mode (CPOL/CPHA)
 *
 ****************************************************************************/

static void ra_ospi_setmode(struct qspi_dev_s *dev, enum qspi_mode_e mode)
{
  struct ra_ospi_priv_s *priv = (struct ra_ospi_priv_s *)dev;

  priv->mode = mode;

  /* Note: OSPI_B is designed for xSPI protocol which uses Mode 0 (CPOL=0,
   * CPHA=0) by default. Mode configuration is implicit in the protocol
   * mode (SPI vs OPI) rather than explicit CPOL/CPHA registers.
   */

  spiinfo("OSPI_B: Set mode %d\n", mode);
}

/****************************************************************************
 * Name: ra_ospi_setbits
 *
 * Description:
 *   Set the number of bits per word
 *
 ****************************************************************************/

static void ra_ospi_setbits(struct qspi_dev_s *dev, int nbits)
{
  struct ra_ospi_priv_s *priv = (struct ra_ospi_priv_s *)dev;

  priv->nbits = nbits;

  /* Note: For OSPI_B, the "bits" concept maps to protocol mode:
   * 1 bit = SPI (1S-1S-1S)
   * 4 bits = QSPI (4S-4S-4S)
   * 8 bits = OPI (8D-8D-8D)
   */

  if (nbits == 8)
    {
      priv->proto = RA_OSPI_PROTOCOL_8D_8D_8D;
    }
  else if (nbits == 4)
    {
      priv->proto = RA_OSPI_PROTOCOL_4S_4S_4S;
    }
  else
    {
      priv->proto = RA_OSPI_PROTOCOL_1S_1S_1S;
    }

  /* Reconfigure protocol if already initialized */

  if (priv->initialized)
    {
      ra_ospi_configure_protocol(priv);
      ra_ospi_configure_commands(priv);
    }

  spiinfo("OSPI_B: Set bits %d -> proto %d\n", nbits, priv->proto);
}

/****************************************************************************
 * Name: ra_ospi_command
 *
 * Description:
 *   Execute a QSPI command (manual mode)
 *
 ****************************************************************************/

static int ra_ospi_command(struct qspi_dev_s *dev,
                           struct qspi_cmdinfo_s *cmdinfo)
{
  struct ra_ospi_priv_s *priv = (struct ra_ospi_priv_s *)dev;
  uint16_t cmd;
  uint8_t cmdsize;
  uint32_t addr = 0;
  uint8_t addrsize = 0;
  uint8_t *data = NULL;
  size_t datalen = 0;
  uint8_t latency = 0;
  bool is_write;

  DEBUGASSERT(priv != NULL && cmdinfo != NULL);

  /* Wait for bus idle before command */

  ra_ospi_wait_ready(priv);

  /* Determine command size based on protocol and command value */

  if (priv->proto == RA_OSPI_PROTOCOL_8D_8D_8D)
    {
      /* OPI mode uses 2-byte commands (command + inverse) */

      cmdsize = 2;
      cmd = cmdinfo->cmd;
    }
  else
    {
      /* SPI mode uses 1-byte commands */

      cmdsize = 1;
      cmd = cmdinfo->cmd & 0xff;
    }

  /* Extract address information */

  if (QSPICMD_ISADDRESS(cmdinfo->flags))
    {
      addr = cmdinfo->addr;
      addrsize = cmdinfo->addrlen;
      if (addrsize == 0)
        {
          addrsize = priv->addrlen;  /* Use default */
        }
    }

  /* Extract data information */

  if (QSPICMD_ISDATA(cmdinfo->flags))
    {
      data = (uint8_t *)cmdinfo->buffer;
      datalen = cmdinfo->buflen;
    }

  /* Determine read/write direction */

  is_write = QSPICMD_ISWRITE(cmdinfo->flags);

  /* For read commands with dummy cycles, use read latency */

  if (!is_write && QSPICMD_ISDATA(cmdinfo->flags))
    {
      latency = priv->read_latency;
    }

  spiinfo("OSPI_B: cmd=0x%04x addr=0x%08lx addrlen=%d datalen=%zu %s\n",
          cmd, addr, addrsize, datalen, is_write ? "WRITE" : "READ");

  /* Execute manual command */

  return ra_ospi_manual_command(priv, cmd, cmdsize, addr, addrsize,
                                data, datalen, latency, is_write);
}

/****************************************************************************
 * Name: ra_ospi_memory
 *
 * Description:
 *   Perform memory-mapped read/write operations
 *
 ****************************************************************************/

static int ra_ospi_memory(struct qspi_dev_s *dev,
                          struct qspi_meminfo_s *meminfo)
{
  struct ra_ospi_priv_s *priv = (struct ra_ospi_priv_s *)dev;
  uintptr_t mmap_addr;
  uint8_t *buffer;
  size_t remaining;
  size_t chunk;
  int ret = OK;

  DEBUGASSERT(priv != NULL && meminfo != NULL);
  DEBUGASSERT(meminfo->buffer != NULL || meminfo->buflen == 0);

  spiinfo("OSPI_B: memory %s addr=0x%08lx len=%lu\n",
          QSPIMEM_ISWRITE(meminfo->flags) ? "WRITE" : "READ",
          (unsigned long)meminfo->addr, (unsigned long)meminfo->buflen);

  /* Calculate memory-mapped address */

  mmap_addr = priv->mmap_base + meminfo->addr;
  buffer = (uint8_t *)meminfo->buffer;
  remaining = meminfo->buflen;

  /* Wait for bus idle */

  ret = ra_ospi_wait_ready(priv);
  if (ret < 0)
    {
      spierr("OSPI_B: Bus not ready\n");
      return ret;
    }

  if (QSPIMEM_ISWRITE(meminfo->flags))
    {
      /* Memory-mapped write operation */

      /* Clear prefetch buffer before write */

      ra_ospi_flush_prefetch(priv);

      /* Note: For flash write, the upper layer should have already:
       * 1. Issued Write Enable command
       * 2. Ensured address alignment for page program
       *
       * We perform the write in chunks up to page size (typically 256 bytes)
       */

#ifdef CONFIG_RA_DMAC
      /* Use DMA for large transfers if configured and available */

      if (priv->use_dma && priv->dma_tx != NULL && remaining >= 64)
        {
          /* DMA-accelerated write */

          ret = ra_ospi_dma_transfer(priv, mmap_addr, (uintptr_t)buffer,
                                     remaining, true);
          if (ret == OK)
            {
              /* Push write buffer to ensure data is sent */

              ra_ospi_push_write_buffer(priv);

              /* Wait for write completion */

              ret = ra_ospi_wait_ready(priv);
            }
          else
            {
              spierr("OSPI_B: DMA write failed, falling back to CPU copy\n");

              /* Fall through to CPU copy on DMA failure */

              goto cpu_write;
            }
        }
      else
#endif
        {
#ifdef CONFIG_RA_DMAC
cpu_write:
#endif
          /* CPU-based write */

          while (remaining > 0)
            {
              /* Calculate page-aligned chunk size */

              chunk = remaining;
              if (chunk > 256)
                {
                  chunk = 256;
                }

              /* Copy data to memory-mapped region */

              memcpy((void *)mmap_addr, buffer, chunk);

              /* Push write buffer to ensure data is sent */

              ra_ospi_push_write_buffer(priv);

              /* Wait for write completion at memory level
               * Note: Flash write completion must be checked by upper layer
               * via status register polling
               */

              ret = ra_ospi_wait_ready(priv);
              if (ret < 0)
                {
                  spierr("OSPI_B: Write wait failed\n");
                  break;
                }

              mmap_addr += chunk;
              buffer += chunk;
              remaining -= chunk;
            }
        }
    }
  else
    {
      /* Memory-mapped read operation */

      /* Clear prefetch buffer for fresh read */

      ra_ospi_flush_prefetch(priv);

#ifdef CONFIG_RA_DMAC
      /* Use DMA for large transfers if configured and available */

      if (priv->use_dma && priv->dma_rx != NULL && remaining >= 64)
        {
          /* DMA-accelerated read */

          ret = ra_ospi_dma_transfer(priv, (uintptr_t)buffer, mmap_addr,
                                     remaining, false);
          if (ret < 0)
            {
              spierr("OSPI_B: DMA read failed, falling back to CPU copy\n");

              /* Fall through to CPU copy on DMA failure */

              goto cpu_read;
            }
        }
      else
#endif
        {
#ifdef CONFIG_RA_DMAC
cpu_read:
#endif
          /* CPU-based read */

          /* Read from memory-mapped region
           * The OSPI_B hardware handles command generation automatically
           */

          while (remaining > 0)
            {
              /* Read in chunks to avoid potential bus issues */

              chunk = remaining;
              if (chunk > 4096)
                {
                  chunk = 4096;
                }

              memcpy(buffer, (void *)mmap_addr, chunk);

              mmap_addr += chunk;
              buffer += chunk;
              remaining -= chunk;
            }
        }
    }

  return ret;
}

/****************************************************************************
 * Name: ra_ospi_alloc / ra_ospi_free
 *
 * Description:
 *   Allocate/free a DMA-capable buffer
 *
 ****************************************************************************/

static void *ra_ospi_alloc(struct qspi_dev_s *dev, size_t buflen)
{
  /* For OSPI_B, regular memory works fine as there's no DMA requirement
   * for the basic operations. DMA support would require aligned buffers.
   */

  return kmm_malloc(buflen);
}

static void ra_ospi_free(struct qspi_dev_s *dev, void *buffer)
{
  kmm_free(buffer);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_ospi_initialize
 *
 * Description:
 *   Initialize the OSPI_B peripheral
 *
 * Input Parameters:
 *   port - OSPI port number (0 or 1)
 *
 * Returned Value:
 *   A pointer to the QSPI device structure, or NULL on failure
 *
 ****************************************************************************/

struct qspi_dev_s *ra_ospi_initialize(int port)
{
  struct ra_ospi_priv_s *priv;
  uint32_t comcfg;
  int ret;

  spiinfo("OSPI_B: Initializing port %d\n", port);

  /* Select device structure based on port */

  if (port == 0)
    {
      priv = &g_ra_ospi0_priv;

      /* Enable OSPI0 module clock via MSTP */

      ra_mstp_start(RA_MSTP_OSPI0);
    }
  else if (port == 1)
    {
      priv = &g_ra_ospi1_priv;

      /* Enable OSPI1 module clock via MSTP */

      ra_mstp_start(RA_MSTP_OSPI1);
    }
  else
    {
      spierr("OSPI_B: Invalid port %d\n", port);
      return NULL;
    }

  /* Check if already initialized */

  if (priv->initialized)
    {
      spiinfo("OSPI_B: Port %d already initialized\n", port);
      return &priv->qspi;
    }

  /* Small delay after enabling module clock */

  up_udelay(10);

  /* Step 1: Configure wrapper timing (WRAPCFG)
   * This sets data strobe shift values for proper timing
   */

  ret = ra_ospi_configure_wrapper(priv);
  if (ret < 0)
    {
      spierr("OSPI_B: WRAPCFG configuration failed\n");
      return NULL;
    }

  /* Step 2: Configure common settings (COMCFG)
   * Channel arbitration mode
   */

  comcfg = R_OSPI_B_COMCFG_ARBMD_00;  /* Round-robin arbitration */
  ra_ospi_putreg(priv, R_OSPI_B_COMCFG_OFFSET, comcfg);

  spiinfo("OSPI_B: COMCFG=0x%08lx\n", comcfg);

  /* Step 3: Configure protocol mode (LIOCFGCS)
   * Start in SPI mode (1S-1S-1S) for compatibility
   */

  priv->proto = RA_OSPI_PROTOCOL_1S_1S_1S;
  ret = ra_ospi_configure_protocol(priv);
  if (ret < 0)
    {
      spierr("OSPI_B: LIOCFGCS configuration failed\n");
      return NULL;
    }

  /* Step 4: Configure command mapping (CMCFG0/1/2)
   * Set up read/write commands for memory-mapped access
   */

  ret = ra_ospi_configure_commands(priv);
  if (ret < 0)
    {
      spierr("OSPI_B: CMCFG configuration failed\n");
      return NULL;
    }

  /* Step 5: Configure bridge mapping (BMCTL0, BMCFGCH)
   * Enable memory-mapped access
   */

  ret = ra_ospi_configure_bridge(priv);
  if (ret < 0)
    {
      spierr("OSPI_B: BMCTL configuration failed\n");
      return NULL;
    }

  /* Step 6: Setup interrupts if enabled */

  ra_ospi_putreg(priv, R_OSPI_B_INTC_OFFSET, 0xffffffff);

  if (priv->use_interrupts)
    {
      /* Attach interrupt handlers */

      if (port == 0)
        {
          priv->irq_cmp = ra_icu_attach(RA_ELC_XSPI_CMP,
                                        ra_ospi_interrupt, priv, true);
          priv->irq_err = ra_icu_attach(RA_ELC_XSPI_ERR,
                                        ra_ospi_interrupt, priv, true);
        }
      else
        {
          priv->irq_cmp = ra_icu_attach(RA_ELC_XSPI1_CMP,
                                        ra_ospi_interrupt, priv, true);
          priv->irq_err = ra_icu_attach(RA_ELC_XSPI1_ERR,
                                        ra_ospi_interrupt, priv, true);
        }

      if (priv->irq_cmp < 0 || priv->irq_err < 0)
        {
          spierr("OSPI_B: Failed to attach interrupts, using polling\n");
          priv->use_interrupts = false;
          priv->irq_cmp = -1;
          priv->irq_err = -1;
        }
      else
        {
          /* Enable command completion and error interrupts */

          ra_ospi_putreg(priv, R_OSPI_B_INTE_OFFSET,
                         R_OSPI_B_INTE_CMDCMPE | R_OSPI_B_INTE_PATCMPE |
                         R_OSPI_B_INTE_DSTOCS0E | R_OSPI_B_INTE_BUSERRCH0E |
                         R_OSPI_B_INTE_CAFAILCS0E);

          spiinfo("OSPI_B: Interrupts enabled (cmp=%d, err=%d)\n",
                  priv->irq_cmp, priv->irq_err);
        }
    }
  else
    {
      ra_ospi_putreg(priv, R_OSPI_B_INTE_OFFSET, 0);
    }

  /* Step 7: Issue flash reset using reset signaling protocol */

  ret = ra_ospi_flash_reset(priv);
  if (ret < 0)
    {
      /* Warning only - some flash may not support reset protocol */

      spiwarn("OSPI_B: Flash reset failed (may be OK)\n");
    }

  /* Step 8: Get actual clock frequency */

  priv->actual_frequency = ra_ospi_get_clock_frequency(port);
  spiinfo("OSPI_B: Clock frequency = %lu Hz\n", priv->actual_frequency);

  /* Step 9: Perform auto-calibration for high-speed modes if needed */

  if (priv->actual_frequency > 50000000 && priv->proto == RA_OSPI_PROTOCOL_8D_8D_8D)
    {
      ret = ra_ospi_autocalibrate(priv);
      if (ret < 0)
        {
          spiwarn("OSPI_B: Auto-calibration failed, may have timing issues\n");
        }
    }

#ifdef CONFIG_RA_DMAC
  /* Step 10: Setup DMA if configured */

  if (priv->use_dma)
    {
      ret = ra_ospi_dma_setup(priv);
      if (ret < 0)
        {
          spiwarn("OSPI_B: DMA setup failed, falling back to CPU transfers\n");
          priv->use_dma = false;
        }
      else
        {
          spiinfo("OSPI_B: DMA setup successful\n");
        }
    }
#endif

  /* Mark as initialized */

  priv->initialized = true;

  spiinfo("OSPI_B: Port %d initialization complete\n", port);

  return &priv->qspi;
}

/****************************************************************************
 * Name: ra_ospi_set_protocol
 *
 * Description:
 *   Change the OSPI protocol mode (SPI, QSPI, OPI)
 *
 * Input Parameters:
 *   dev   - QSPI device structure
 *   proto - Protocol mode to set
 *
 * Returned Value:
 *   OK on success, negative errno on failure
 *
 ****************************************************************************/

int ra_ospi_set_protocol(struct qspi_dev_s *dev, int proto)
{
  struct ra_ospi_priv_s *priv = (struct ra_ospi_priv_s *)dev;
  int ret;

  DEBUGASSERT(priv != NULL);

  /* Wait for bus idle before changing protocol */

  ret = ra_ospi_wait_ready(priv);
  if (ret < 0)
    {
      return ret;
    }

  /* Set new protocol mode */

  switch (proto)
    {
      case 0:
        priv->proto = RA_OSPI_PROTOCOL_1S_1S_1S;
        break;
      case 1:
        priv->proto = RA_OSPI_PROTOCOL_1S_4S_4S;
        break;
      case 4:
        priv->proto = RA_OSPI_PROTOCOL_4S_4S_4S;
        break;
      case 8:
        priv->proto = RA_OSPI_PROTOCOL_8D_8D_8D;
        break;
      default:
        return -EINVAL;
    }

  /* Reconfigure LIOCFGCS and CMCFG registers */

  ret = ra_ospi_configure_protocol(priv);
  if (ret < 0)
    {
      return ret;
    }

  ret = ra_ospi_configure_commands(priv);
  if (ret < 0)
    {
      return ret;
    }

  spiinfo("OSPI_B: Protocol changed to %d\n", priv->proto);

  return OK;
}

/****************************************************************************
 * Name: ra_ospi_autocalibrate
 *
 * Description:
 *   Perform automatic DQS calibration for high-speed OPI modes
 *
 * Input Parameters:
 *   priv - OSPI driver private data
 *
 * Returned Value:
 *   OK on success, negative errno on failure
 *
 * Note:
 *   This is a placeholder for FSP-style auto-calibration.
 *   Full implementation requires:
 *   1. Writing calibration pattern to flash
 *   2. Configuring CCCTL registers for auto-calibration
 *   3. Sweeping DS shift values and verifying read-back
 *   4. Setting optimal WRAPCFG.DSSFTCS value
 *
 ****************************************************************************/

static int ra_ospi_autocalibrate(struct ra_ospi_priv_s *priv)
{
  /* TODO: Implement full auto-calibration sequence from FSP reference
   * For now, use default WRAPCFG values which work at lower frequencies
   */

  spiinfo("OSPI_B: Auto-calibration not yet implemented, using defaults\n");
  return -ENOSYS;
}

/****************************************************************************
 * Name: ra_ospi_set_latency
 *
 * Description:
 *   Set the read/write latency cycles
 *
 * Input Parameters:
 *   dev           - QSPI device structure
 *   read_latency  - Read latency cycles (dummy cycles)
 *   write_latency - Write latency cycles
 *
 * Returned Value:
 *   OK on success, negative errno on failure
 *
 ****************************************************************************/

int ra_ospi_set_latency(struct qspi_dev_s *dev,
                        uint8_t read_latency, uint8_t write_latency)
{
  struct ra_ospi_priv_s *priv = (struct ra_ospi_priv_s *)dev;

  DEBUGASSERT(priv != NULL);

  priv->read_latency = read_latency;
  priv->write_latency = write_latency;

  /* Update command configuration with new latency */

  return ra_ospi_configure_commands(priv);
}

/****************************************************************************
 * Name: ra_ospi_xip_enable
 *
 * Description:
 *   Enable XIP (Execute-in-Place) mode for continuous read optimization
 *
 * Input Parameters:
 *   dev - QSPI device structure
 *
 * Returned Value:
 *   OK on success, negative errno on failure
 *
 ****************************************************************************/

int ra_ospi_xip_enable(struct qspi_dev_s *dev)
{
  struct ra_ospi_priv_s *priv = (struct ra_ospi_priv_s *)dev;

  DEBUGASSERT(priv != NULL);

  if (priv->xip_mode)
    {
      return OK;  /* Already in XIP mode */
    }

  /* Enable XIP mode via CMCTLCH register
   * This allows continuous read without sending command each time
   */

  ra_ospi_modifyreg(priv, R_OSPI_B_CMCTLCH_OFFSET(priv->cs),
                    0, R_OSPI_B_CMCTLCH_XIPEN);

  priv->xip_mode = true;

  spiinfo("OSPI_B: XIP mode enabled\n");

  return OK;
}

/****************************************************************************
 * Name: ra_ospi_xip_disable
 *
 * Description:
 *   Disable XIP (Execute-in-Place) mode
 *
 * Input Parameters:
 *   dev - QSPI device structure
 *
 * Returned Value:
 *   OK on success, negative errno on failure
 *
 ****************************************************************************/

int ra_ospi_xip_disable(struct qspi_dev_s *dev)
{
  struct ra_ospi_priv_s *priv = (struct ra_ospi_priv_s *)dev;

  DEBUGASSERT(priv != NULL);

  if (!priv->xip_mode)
    {
      return OK;  /* Already disabled */
    }

  /* Disable XIP mode */

  ra_ospi_modifyreg(priv, R_OSPI_B_CMCTLCH_OFFSET(priv->cs),
                    R_OSPI_B_CMCTLCH_XIPEN, 0);

  priv->xip_mode = false;

  spiinfo("OSPI_B: XIP mode disabled\n");

  return OK;
}

#ifdef CONFIG_RA_DMAC

/****************************************************************************
 * Name: ra_ospi_dma_callback
 *
 * Description:
 *   DMA transfer completion callback
 *
 ****************************************************************************/

static void ra_ospi_dma_callback(void *handle, int event, void *user_data)
{
  struct ra_ospi_priv_s *priv = (struct ra_ospi_priv_s *)user_data;

  if (event == RA_DMAC_EVENT_COMPLETE)
    {
      priv->dma_complete = true;
      nxsem_post(&priv->dmasem);
    }
  else if (event == RA_DMAC_EVENT_ERROR)
    {
      spierr("OSPI_B: DMA transfer error\n");
      priv->dma_complete = true;
      nxsem_post(&priv->dmasem);
    }
}

/****************************************************************************
 * Name: ra_ospi_get_dma_channel
 *
 * Description:
 *   Get DMA channel assignment from Kconfig for the specified OSPI port
 *
 ****************************************************************************/

static void ra_ospi_get_dma_channel(struct ra_ospi_priv_s *priv, int *channel)
{
  /* Default to dynamic allocation */
  *channel = -1;

  /* Determine which OSPI port (0 or 1) based on chip select */
  if (priv->cs == 0)
    {
#ifdef CONFIG_RA_DMAC_QSPI0_CHANNEL
      *channel = CONFIG_RA_DMAC_QSPI0_CHANNEL;
#endif
    }
  else if (priv->cs == 1)
    {
#ifdef CONFIG_RA_DMAC_QSPI1_CHANNEL
      *channel = CONFIG_RA_DMAC_QSPI1_CHANNEL;
#endif
    }

  spiinfo("OSPI_B (CS%d) DMA channel: %d\n", priv->cs, *channel);
}

/****************************************************************************
 * Name: ra_ospi_dma_setup
 *
 * Description:
 *   Setup DMA channels for OSPI transfers
 *
 ****************************************************************************/

static int ra_ospi_dma_setup(struct ra_ospi_priv_s *priv)
{
  ra_dmac_config_t dma_config;
  int ret;

  /* Initialize DMAC module if not already done */

  ret = ra_dmac_initialize();
  if (ret < 0)
    {
      spierr("OSPI_B: Failed to initialize DMAC: %d\n", ret);
      return ret;
    }

  /* Get DMA channel assignment from Kconfig */
  ra_ospi_get_dma_channel(priv, &priv->dma_channel);

  ret = ra_dmac_initialize();
  if (ret < 0)
    {
      spierr("OSPI_B: Failed to initialize DMAC: %d\n", ret);
      return ret;
    }

  /* Configure TX DMA for memory-to-peripheral transfers */

  memset(&dma_config, 0, sizeof(dma_config));
  dma_config.mode = RA_DMAC_MODE_NORMAL;
  dma_config.repeat_area = RA_DMAC_REPEAT_AREA_NONE;
  dma_config.size = RA_DMAC_SIZE_8BIT;
  dma_config.src_addr_mode = RA_DMAC_ADDR_INCR;
  dma_config.dest_addr_mode = RA_DMAC_ADDR_FIXED;
  dma_config.trigger = RA_DMAC_TRIGGER_SW;
  dma_config.callback = ra_ospi_dma_callback;
  dma_config.user_data = priv;

  /* ELC event links (these may need board-specific configuration) */

  dma_config.elc_end = 0;  /* DMA end event */
  dma_config.elc_err = 0;  /* DMA error event */
  dma_config.elc_src = 0;  /* Software trigger */

  /* Use assigned channel if configured, otherwise use dynamic allocation */
  if (priv->dma_channel >= 0)
    {
      ret = ra_dmac_open_channel(&priv->dma_tx, &dma_config, priv->dma_channel);
      spiinfo("OSPI_B TX DMA using assigned channel %d\n", priv->dma_channel);
    }
  else
    {
      ret = ra_dmac_open(&priv->dma_tx, &dma_config);
      spiinfo("OSPI_B TX DMA using dynamic channel allocation\n");
    }

  if (ret < 0)
    {
      spierr("OSPI_B: Failed to open TX DMA channel: %d\n", ret);
      return ret;
    }

  /* Configure RX DMA for peripheral-to-memory transfers */

  dma_config.src_addr_mode = RA_DMAC_ADDR_FIXED;
  dma_config.dest_addr_mode = RA_DMAC_ADDR_INCR;

  /* Use same channel for RX (if assigned) */
  if (priv->dma_channel >= 0)
    {
      ret = ra_dmac_open_channel(&priv->dma_rx, &dma_config, priv->dma_channel);
      spiinfo("OSPI_B RX DMA using assigned channel %d\n", priv->dma_channel);
    }
  else
    {
      ret = ra_dmac_open(&priv->dma_rx, &dma_config);
      spiinfo("OSPI_B RX DMA using dynamic channel allocation\n");
    }

  if (ret < 0)
    {
      spierr("OSPI_B: Failed to open RX DMA channel: %d\n", ret);
      ra_dmac_close(priv->dma_tx);
      priv->dma_tx = NULL;
      return ret;
    }

  spiinfo("OSPI_B: DMA channels configured successfully (channel=%d)\n", priv->dma_channel);

  return OK;
}

/****************************************************************************
 * Name: ra_ospi_dma_transfer
 *
 * Description:
 *   Perform DMA transfer for OSPI memory-mapped operations
 *
 * Input Parameters:
 *   priv     - OSPI private data
 *   dest     - Destination address
 *   src      - Source address
 *   len      - Transfer length in bytes
 *   is_write - true for write, false for read
 *
 * Returned Value:
 *   OK on success, negative errno on failure
 *
 ****************************************************************************/

static int ra_ospi_dma_transfer(struct ra_ospi_priv_s *priv,
                                uintptr_t dest, uintptr_t src,
                                size_t len, bool is_write)
{
  ra_dmac_handle_t dma_handle;
  struct timespec timeout;
  int ret;

  DEBUGASSERT(priv != NULL);
  DEBUGASSERT(len > 0);

  /* Select appropriate DMA channel */

  dma_handle = is_write ? priv->dma_tx : priv->dma_rx;

  if (dma_handle == NULL)
    {
      spierr("OSPI_B: DMA not initialized\n");
      return -EINVAL;
    }

  /* Reset DMA transfer with new addresses */

  ret = ra_dmac_reset(dma_handle, src, dest, len);
  if (ret < 0)
    {
      spierr("OSPI_B: DMA reset failed: %d\n", ret);
      return ret;
    }

  /* Clear completion flag */

  priv->dma_complete = false;

  /* Enable DMA channel */

  ret = ra_dmac_enable(dma_handle);
  if (ret < 0)
    {
      spierr("OSPI_B: DMA enable failed: %d\n", ret);
      return ret;
    }

  /* Start DMA transfer */

  ret = ra_dmac_software_start(dma_handle);
  if (ret < 0)
    {
      spierr("OSPI_B: DMA start failed: %d\n", ret);
      ra_dmac_disable(dma_handle);
      return ret;
    }

  /* Wait for DMA completion with timeout */

  clock_gettime(CLOCK_REALTIME, &timeout);
  timeout.tv_sec += 5;  /* 5 second timeout */

  ret = nxsem_timedwait_uninterruptible(&priv->dmasem, &timeout);
  if (ret < 0)
    {
      spierr("OSPI_B: DMA timeout or error: %d\n", ret);
      ra_dmac_disable(dma_handle);
      return ret;
    }

  /* Disable DMA channel */

  ra_dmac_disable(dma_handle);

  /* Check if transfer completed successfully */

  if (!priv->dma_complete)
    {
      spierr("OSPI_B: DMA transfer incomplete\n");
      return -EIO;
    }

  spiinfo("OSPI_B: DMA transfer complete (%zu bytes)\n", len);

  return OK;
}

/****************************************************************************
 * Name: ra_ospi_set_dma
 *
 * Description:
 *   Enable or disable DMA for OSPI transfers
 *
 ****************************************************************************/

int ra_ospi_set_dma(struct qspi_dev_s *dev, bool enable_dma)
{
  struct ra_ospi_priv_s *priv = (struct ra_ospi_priv_s *)dev;
  int ret = OK;

  DEBUGASSERT(priv != NULL);

  if (enable_dma && !priv->use_dma)
    {
      /* Enable DMA - setup if not already done */

      if (priv->dma_tx == NULL || priv->dma_rx == NULL)
        {
          ret = ra_ospi_dma_setup(priv);
          if (ret < 0)
            {
              spierr("OSPI_B: DMA setup failed: %d\n", ret);
              return ret;
            }
        }

      priv->use_dma = true;
      spiinfo("OSPI_B: DMA enabled\n");
    }
  else if (!enable_dma && priv->use_dma)
    {
      /* Disable DMA */

      priv->use_dma = false;
      spiinfo("OSPI_B: DMA disabled\n");
    }

  return ret;
}

#endif /* CONFIG_RA_DMAC */
