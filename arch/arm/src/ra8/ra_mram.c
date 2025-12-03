/****************************************************************************
 * arch/arm/src/ra8/ra_mram.c
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
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <debug.h>
#include <inttypes.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/clock.h>
#include <nuttx/mtd/mtd.h>
#include <nuttx/fs/ioctl.h>

#include "arm_internal.h"
#include "barriers.h"
#include "ra_mram.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* MRAM Programming Size - 32 bytes per write operation */

#define MRAM_WRITE_SIZE                32

/* MRAM erase state is 0xFF (like traditional flash) */

#define MRAM_ERASED_STATE              0xff

/* MACI Command Area - used for MRAM operations */

#define R_MACI_BASE                    0x40120000UL

/* Timeout values in microseconds */

#define MRAM_TIMEOUT_WRITE_US          1000      /* 1ms for write */
#define MRAM_TIMEOUT_ERASE_US          5000      /* 5ms for block erase */
#define MRAM_TIMEOUT_INIT_US           10000     /* 10ms for init */

/* MRMS Status bits - using MRCPS (Program Status) register */

#define MRMS_STS_PRGERRC           (1 << 0)  /* Program error */
#define MRMS_STS_ECCERRC           (1 << 1)  /* ECC error */
#define MRMS_STS_ABUFEMP           (1 << 5)  /* Address buffer empty */
#define MRMS_STS_ABUFFULL          (1 << 6)  /* Address buffer full */
#define MRMS_STS_PRGBSYC           (1 << 7)  /* Program busy */

/* MRMS Control bits - using MENTRYR (Entry) and MRCPC (Program Control) */

#define MRMS_CTL_KEY               0xAA00U   /* Key code for MENTRYR */
#define MRMS_CTL_PE_MODE           0x0080U   /* P/E mode enable */
#define MRMS_MRCPC_KEY             0x8600U   /* Key code for program control */
#define MRMS_MRCPC_ENABLE          0x0001U   /* Program enable bit */

/* MRMS MRCPFB bits */

#define MRMS_PFBCTL_PFBE           (1 << 0)  /* Pre-fetch buffer enable */

/* Error mask for status checking */

#define MRMS_ERROR_MASK            (MRMS_STS_PRGERRC | MRMS_STS_ECCERRC)

/****************************************************************************
 * Private Types
 ****************************************************************************/

struct ra_mram_dev_s
{
  struct mtd_dev_s mtd;        /* MTD interface */
  uint32_t base;               /* MRAM base address */
  uint32_t size;               /* MRAM size */
  uint32_t blocksize;          /* Block size (programming unit) */
  uint32_t erasesize;          /* Erase block size */
  uint32_t nblocks;            /* Number of erase blocks */
  bool     data_flash;         /* True if data partition */
  bool     initialized;        /* True if initialized */
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* Low-level MRAM operations */

static void ra_mram_init_timeouts(void);
static void ra_mram_clear_pfb(void);
static void ra_mram_set_pfb(bool enable);
static int  ra_mram_wait_ready(uint32_t timeout_us);
static int  ra_mram_check_errors(void);
static void ra_mram_stop(void);
static void ra_mram_reset(void);
static int  ra_mram_program_control(uint32_t addr, uint32_t cmd);
static int  ra_mram_write_data(uint32_t addr, const uint8_t *data,
                               size_t len);
static int  ra_mram_erase_block_internal(uint32_t addr);

/* MTD interface functions */

static int ra_mram_erase(struct mtd_dev_s *dev, off_t startblock,
                         size_t nblocks);
static ssize_t ra_mram_bread(struct mtd_dev_s *dev, off_t startblock,
                             size_t nblocks, uint8_t *buffer);
static ssize_t ra_mram_bwrite(struct mtd_dev_s *dev, off_t startblock,
                              size_t nblocks, const uint8_t *buffer);
static ssize_t ra_mram_read(struct mtd_dev_s *dev, off_t offset,
                            size_t nbytes, uint8_t *buffer);
#ifdef CONFIG_MTD_BYTE_WRITE
static ssize_t ra_mram_write(struct mtd_dev_s *dev, off_t offset,
                             size_t nbytes, const uint8_t *buffer);
#endif
static int ra_mram_ioctl(struct mtd_dev_s *dev, int cmd,
                         unsigned long arg);

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Code MRAM MTD device - main MRAM for code storage */

static struct ra_mram_dev_s g_code_mram =
{
  .mtd =
  {
    .erase  = ra_mram_erase,
    .bread  = ra_mram_bread,
    .bwrite = ra_mram_bwrite,
    .read   = ra_mram_read,
#ifdef CONFIG_MTD_BYTE_WRITE
    .write  = ra_mram_write,
#endif
    .ioctl  = ra_mram_ioctl,
    .name   = "ra8_code_mram",
  },
  .base        = RA_MRAM_CODE_START,
  .size        = RA_MRAM_CODE_SIZE - RA_MRAM_DATA_SIZE,  /* Reserve data area */
  .blocksize   = RA_MRAM_PROGRAMMING_SIZE,
  .erasesize   = RA_MRAM_CODE_BLOCK_SIZE,
  .nblocks     = (RA_MRAM_CODE_SIZE - RA_MRAM_DATA_SIZE) /
                 RA_MRAM_CODE_BLOCK_SIZE,
  .data_flash  = false,
  .initialized = false,
};

/* Data MRAM MTD device - reserved area at end for parameter storage */

static struct ra_mram_dev_s g_data_mram =
{
  .mtd =
  {
    .erase  = ra_mram_erase,
    .bread  = ra_mram_bread,
    .bwrite = ra_mram_bwrite,
    .read   = ra_mram_read,
#ifdef CONFIG_MTD_BYTE_WRITE
    .write  = ra_mram_write,
#endif
    .ioctl  = ra_mram_ioctl,
    .name   = "ra8_data_mram",
  },
  .base        = RA_MRAM_DATA_START,
  .size        = RA_MRAM_DATA_SIZE,
  .blocksize   = RA_MRAM_PROGRAMMING_SIZE,
  .erasesize   = RA_MRAM_DATA_BLOCK_SIZE,
  .nblocks     = RA_MRAM_DATA_SIZE / RA_MRAM_DATA_BLOCK_SIZE,
  .data_flash  = true,
  .initialized = false,
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_mram_init_timeouts
 *
 * Description:
 *   Initialize MRAM timing parameters based on system clock.
 *   This configures the frequency notification register for optimal operation.
 *
 ****************************************************************************/

static void ra_mram_init_timeouts(void)
{
  /* Set MRAM frequency notification for proper access timing
   * Value of 0x03 is suitable for system clocks up to 200MHz
   */

  putreg32(0x00000003, R_MRMS_MRCFREQ);

  /* Memory barrier to ensure register writes complete */

  ARM_DSB();
}

/****************************************************************************
 * Name: ra_mram_clear_pfb
 *
 * Description:
 *   Clear the pre-fetch buffer. Must be called before write operations.
 *
 ****************************************************************************/

static void ra_mram_clear_pfb(void)
{
  uint32_t regval;

  /* Disable pre-fetch buffer using MRCPFB register */

  regval = getreg32(R_MRMS_MRCPFB);
  regval &= ~MRMS_PFBCTL_PFBE;
  putreg32(regval, R_MRMS_MRCPFB);

  ARM_DSB();
  ARM_ISB();
}

/****************************************************************************
 * Name: ra_mram_set_pfb
 *
 * Description:
 *   Enable or disable the pre-fetch buffer.
 *
 ****************************************************************************/

static void ra_mram_set_pfb(bool enable)
{
  uint32_t regval;

  regval = getreg32(R_MRMS_MRCPFB);
  if (enable)
    {
      regval |= MRMS_PFBCTL_PFBE;
    }
  else
    {
      regval &= ~MRMS_PFBCTL_PFBE;
    }
  putreg32(regval, R_MRMS_MRCPFB);

  ARM_DSB();
}

/****************************************************************************
 * Name: ra_mram_wait_ready
 *
 * Description:
 *   Wait for MRAM controller to become ready.
 *
 * Input Parameters:
 *   timeout_us - Timeout in microseconds
 *
 * Returned Value:
 *   OK on success, -ETIMEDOUT on timeout
 *
 ****************************************************************************/

static int ra_mram_wait_ready(uint32_t timeout_us)
{
  uint32_t status;
  uint32_t elapsed = 0;

  while (elapsed < timeout_us)
    {
      /* Read program status register */

      status = getreg32(R_MRMS_MRCPS);

      /* Check if MRAM is ready (PRGBSYC bit clear = not busy) */

      if ((status & MRMS_STS_PRGBSYC) == 0)
        {
          return OK;
        }

      /* Small delay to avoid hammering the bus */

      up_udelay(1);
      elapsed++;
    }

  ferr("ERROR: MRAM timeout waiting for ready (status=0x%08" PRIx32 ")\n",
       status);
  return -ETIMEDOUT;
}

/****************************************************************************
 * Name: ra_mram_check_errors
 *
 * Description:
 *   Check for MRAM operation errors.
 *
 * Returned Value:
 *   OK on success, negative errno on error
 *
 ****************************************************************************/

static int ra_mram_check_errors(void)
{
  uint32_t status;

  /* Read program status register */

  status = getreg32(R_MRMS_MRCPS);

  if (status & MRMS_STS_PRGERRC)
    {
      ferr("ERROR: MRAM program error (status=0x%08" PRIx32 ")\n", status);
      return -EIO;
    }

  if (status & MRMS_STS_ECCERRC)
    {
      ferr("ERROR: MRAM ECC error (status=0x%08" PRIx32 ")\n", status);
      return -EIO;
    }

  /* Also check extra MRAM status register for additional errors */

  status = getreg32(R_MRMS_MSTATR);

  if (status & R_MRMS_MSTATR_PRGERR)
    {
      ferr("ERROR: Extra MRAM program error (status=0x%08" PRIx32 ")\n",
           status);
      return -EIO;
    }

  if (status & R_MRMS_MSTATR_ILGLERR)
    {
      ferr("ERROR: Extra MRAM illegal error (status=0x%08" PRIx32 ")\n",
           status);
      return -EIO;
    }

  return OK;
}

/****************************************************************************
 * Name: ra_mram_stop
 *
 * Description:
 *   Issue stop command to MRAM controller to abort current operation.
 *   Uses MACI forced stop command.
 *
 ****************************************************************************/

static void ra_mram_stop(void)
{
  /* Write forced stop command to MACI command area */

  putreg8(MRAM_MACI_CMD_FORCED_STOP, R_MRAM_CMD_BASE);
  ARM_DSB();
}

/****************************************************************************
 * Name: ra_mram_reset
 *
 * Description:
 *   Reset MRAM controller and clear error status.
 *
 ****************************************************************************/

static void ra_mram_reset(void)
{
  /* Issue stop command first */

  ra_mram_stop();

  /* Clear status by writing status clear command */

  putreg8(MRAM_MACI_CMD_STATUS_CLEAR, R_MRAM_CMD_BASE);
  ARM_DSB();

  /* Exit P/E mode - transition to read mode */

  putreg32(R_MRMS_MENTRYR_READ_MODE, R_MRMS_MENTRYR);
  ARM_DSB();

  /* Wait for reset to complete */

  up_udelay(10);
}

/****************************************************************************
 * Name: ra_mram_program_control
 *
 * Description:
 *   Set up MRAM programming control for the specified address.
 *   This follows the FSP pattern from r_mram.c:
 *   1. Enter P/E mode via MENTRYR
 *   2. Enable programming via MRCPC0
 *   3. Set start address via MSADDR
 *
 * Input Parameters:
 *   addr - Target address for the operation
 *   cmd  - Not used, kept for interface compatibility
 *
 * Returned Value:
 *   OK on success, negative errno on error
 *
 ****************************************************************************/

static int ra_mram_program_control(uint32_t addr, uint32_t cmd)
{
  int ret;

  UNUSED(cmd);

  /* Wait for MRAM to be ready */

  ret = ra_mram_wait_ready(MRAM_TIMEOUT_INIT_US);
  if (ret < 0)
    {
      return ret;
    }

  /* Clear pre-fetch buffer before write operation */

  ra_mram_clear_pfb();

  /* Enter P/E mode - write key + PE_MODE to MENTRYR */

  putreg32(R_MRMS_MENTRYR_TRANSITION, R_MRMS_MENTRYR);
  ARM_DSB();

  /* Enable programming - write key + enable to MRCPC0 (non-secure) */

  putreg32(MRMS_MRCPC_KEY | MRMS_MRCPC_ENABLE, R_MRMS_MRCPC0);
  ARM_DSB();

  /* Set start address for the programming operation */

  putreg32(addr, R_MRMS_MSADDR);
  ARM_DSB();

  return OK;
}

/****************************************************************************
 * Name: ra_mram_write_data
 *
 * Description:
 *   Write data to MRAM. Data is written 32 bytes at a time following
 *   the FSP programming sequence:
 *   1. Enter P/E mode and enable programming
 *   2. Write 32 bytes to target address
 *   3. Wait for completion
 *   4. Check errors
 *   5. Flush and exit P/E mode
 *
 * Input Parameters:
 *   addr - Target address (must be 32-byte aligned)
 *   data - Pointer to data buffer
 *   len  - Number of bytes to write (must be multiple of 32)
 *
 * Returned Value:
 *   OK on success, negative errno on error
 *
 ****************************************************************************/

static int ra_mram_write_data(uint32_t addr, const uint8_t *data, size_t len)
{
  irqstate_t flags;
  const uint32_t *src;
  volatile uint32_t *dest;
  size_t remaining;
  size_t write_count;
  int ret;
  int i;

  DEBUGASSERT((addr % MRAM_WRITE_SIZE) == 0);
  DEBUGASSERT((len % MRAM_WRITE_SIZE) == 0);

  remaining = len;
  src = (const uint32_t *)data;

  while (remaining > 0)
    {
      write_count = MRAM_WRITE_SIZE;

      /* Disable interrupts during critical programming sequence */

      flags = enter_critical_section();

      /* Set up programming control - enter P/E mode, enable programming */

      ret = ra_mram_program_control(addr, 0);
      if (ret < 0)
        {
          leave_critical_section(flags);
          ferr("ERROR: Program control setup failed: %d\n", ret);
          return ret;
        }

      /* Write 32 bytes (8 x 32-bit words) to the target address
       * MRAM is memory-mapped, write directly to the target address
       */

      dest = (volatile uint32_t *)addr;
      for (i = 0; i < (MRAM_WRITE_SIZE / sizeof(uint32_t)); i++)
        {
          *dest++ = *src++;
        }

      ARM_DSB();

      /* Wait for programming to complete */

      ret = ra_mram_wait_ready(MRAM_TIMEOUT_WRITE_US);

      /* Flush the write buffer */

      putreg32(R_MRMS_MRCFLR_FLUSH, R_MRMS_MRCFLR);
      ARM_DSB();

      /* Exit P/E mode */

      putreg32(R_MRMS_MENTRYR_READ_MODE, R_MRMS_MENTRYR);
      ARM_DSB();

      leave_critical_section(flags);

      if (ret < 0)
        {
          ferr("ERROR: Write timeout at 0x%08" PRIx32 "\n", addr);
          ra_mram_reset();
          return ret;
        }

      /* Check for errors */

      ret = ra_mram_check_errors();
      if (ret < 0)
        {
          ferr("ERROR: Write error at 0x%08" PRIx32 "\n", addr);
          ra_mram_reset();
          return ret;
        }

      addr += write_count;
      remaining -= write_count;
    }

  /* Re-enable pre-fetch buffer after write */

  ra_mram_set_pfb(true);

  return OK;
}

/****************************************************************************
 * Name: ra_mram_erase_block_internal
 *
 * Description:
 *   Erase a block by writing 0xFF pattern (MRAM doesn't need traditional
 *   erase, but we simulate it for MTD compatibility).
 *
 * Input Parameters:
 *   addr - Start address of block to erase
 *
 * Returned Value:
 *   OK on success, negative errno on error
 *
 ****************************************************************************/

static int ra_mram_erase_block_internal(uint32_t addr)
{
  uint8_t erase_buffer[MRAM_WRITE_SIZE];
  size_t offset;
  int ret;

  /* Fill buffer with erased state (0xFF) */

  memset(erase_buffer, MRAM_ERASED_STATE, sizeof(erase_buffer));

  /* Write 0xFF pattern to entire block
   * Block size is typically 8KB for RA8P1 MRAM
   */

  for (offset = 0; offset < RA_MRAM_CODE_BLOCK_SIZE; offset += MRAM_WRITE_SIZE)
    {
      ret = ra_mram_write_data(addr + offset, erase_buffer, MRAM_WRITE_SIZE);
      if (ret < 0)
        {
          ferr("ERROR: Erase failed at 0x%08" PRIx32 "\n", addr + offset);
          return ret;
        }
    }

  return OK;
}

/****************************************************************************
 * Name: ra_mram_erase
 *
 * Description:
 *   Erase the specified number of blocks starting from startblock.
 *   For MRAM, this writes 0xFF pattern to the blocks.
 *
 ****************************************************************************/

static int ra_mram_erase(struct mtd_dev_s *dev, off_t startblock,
                         size_t nblocks)
{
  struct ra_mram_dev_s *priv = (struct ra_mram_dev_s *)dev;
  size_t blocksleft = nblocks;
  uint32_t addr;
  int ret = OK;

  finfo("startblock: %08lx nblocks: %d erasesize: %" PRIu32 "\n",
        (long)startblock, (int)nblocks, priv->erasesize);

  /* Validate parameters */

  if (startblock + nblocks > priv->nblocks)
    {
      ferr("ERROR: Erase beyond end of MRAM\n");
      return -EINVAL;
    }

  while (blocksleft-- > 0)
    {
      addr = priv->base + startblock * priv->erasesize;

      finfo("Erasing block %ld at 0x%08" PRIx32 "\n",
            (long)startblock, addr);

      /* Erase the block by writing 0xFF pattern */

      ret = ra_mram_erase_block_internal(addr);
      if (ret < 0)
        {
          ferr("ERROR: Block erase failed at 0x%08" PRIx32 ": %d\n",
               addr, ret);
          return ret;
        }

      startblock++;
    }

  return OK;
}

/****************************************************************************
 * Name: ra_mram_bread
 *
 * Description:
 *   Read the specified number of blocks from the MRAM.
 *   MRAM is memory-mapped, so this is just a memcpy.
 *
 ****************************************************************************/

static ssize_t ra_mram_bread(struct mtd_dev_s *dev, off_t startblock,
                             size_t nblocks, uint8_t *buffer)
{
  struct ra_mram_dev_s *priv = (struct ra_mram_dev_s *)dev;
  ssize_t nbytes;
  uint32_t addr;

  finfo("startblock: %08lx nblocks: %d\n", (long)startblock, (int)nblocks);

  /* Validate parameters */

  if (startblock * priv->blocksize + nblocks * priv->blocksize > priv->size)
    {
      ferr("ERROR: Read beyond end of MRAM\n");
      return -EINVAL;
    }

  /* Calculate source address and read bytes */

  addr = priv->base + startblock * priv->blocksize;
  nbytes = nblocks * priv->blocksize;

  /* MRAM is memory-mapped, just copy the data */

  memcpy(buffer, (void *)addr, nbytes);

  return nblocks;
}

/****************************************************************************
 * Name: ra_mram_bwrite
 *
 * Description:
 *   Write the specified number of blocks to the MRAM.
 *
 ****************************************************************************/

static ssize_t ra_mram_bwrite(struct mtd_dev_s *dev, off_t startblock,
                              size_t nblocks, const uint8_t *buffer)
{
  struct ra_mram_dev_s *priv = (struct ra_mram_dev_s *)dev;
  size_t nbytes;
  uint32_t addr;
  int ret;

  finfo("startblock: %08lx nblocks: %d\n", (long)startblock, (int)nblocks);

  /* Validate parameters */

  if (startblock * priv->blocksize + nblocks * priv->blocksize > priv->size)
    {
      ferr("ERROR: Write beyond end of MRAM\n");
      return -EINVAL;
    }

  /* Calculate destination address */

  addr = priv->base + startblock * priv->blocksize;
  nbytes = nblocks * priv->blocksize;

  /* Perform the write operation */

  ret = ra_mram_write_data(addr, buffer, nbytes);
  if (ret < 0)
    {
      ferr("ERROR: Write failed: %d\n", ret);
      return ret;
    }

  return nblocks;
}

/****************************************************************************
 * Name: ra_mram_read
 *
 * Description:
 *   Read the specified number of bytes from the MRAM.
 *   MRAM is memory-mapped, so this is just a memcpy.
 *
 ****************************************************************************/

static ssize_t ra_mram_read(struct mtd_dev_s *dev, off_t offset,
                            size_t nbytes, uint8_t *buffer)
{
  struct ra_mram_dev_s *priv = (struct ra_mram_dev_s *)dev;

  finfo("offset: %08lx nbytes: %d\n", (long)offset, (int)nbytes);

  /* Validate parameters */

  if (offset + nbytes > priv->size)
    {
      ferr("ERROR: Read beyond end of MRAM\n");
      return -EINVAL;
    }

  /* MRAM is memory-mapped, just copy the data */

  memcpy(buffer, (void *)(priv->base + offset), nbytes);

  return nbytes;
}

/****************************************************************************
 * Name: ra_mram_write
 *
 * Description:
 *   Write the specified number of bytes to the MRAM.
 *   Handles unaligned writes by aligning to 32-byte boundaries.
 *
 ****************************************************************************/

#ifdef CONFIG_MTD_BYTE_WRITE
static ssize_t ra_mram_write(struct mtd_dev_s *dev, off_t offset,
                             size_t nbytes, const uint8_t *buffer)
{
  struct ra_mram_dev_s *priv = (struct ra_mram_dev_s *)dev;
  uint8_t aligned_buffer[MRAM_WRITE_SIZE];
  uint32_t addr;
  size_t remaining = nbytes;
  size_t written = 0;
  size_t chunk;
  size_t pre_offset;
  int ret;

  finfo("offset: %08lx nbytes: %d\n", (long)offset, (int)nbytes);

  /* Validate parameters */

  if (offset + nbytes > priv->size)
    {
      ferr("ERROR: Write beyond end of MRAM\n");
      return -EINVAL;
    }

  while (remaining > 0)
    {
      /* Calculate aligned address */

      addr = priv->base + offset;
      pre_offset = addr % MRAM_WRITE_SIZE;

      if (pre_offset != 0)
        {
          /* Handle unaligned start - read existing data first */

          uint32_t aligned_addr = addr - pre_offset;

          memcpy(aligned_buffer, (void *)aligned_addr, MRAM_WRITE_SIZE);

          /* Calculate how much to write in this chunk */

          chunk = MRAM_WRITE_SIZE - pre_offset;
          if (chunk > remaining)
            {
              chunk = remaining;
            }

          /* Copy new data into aligned buffer */

          memcpy(aligned_buffer + pre_offset, buffer, chunk);

          /* Write the aligned buffer */

          ret = ra_mram_write_data(aligned_addr, aligned_buffer,
                                   MRAM_WRITE_SIZE);
          if (ret < 0)
            {
              ferr("ERROR: Unaligned write failed at 0x%08" PRIx32 ": %d\n",
                   addr, ret);
              return ret;
            }
        }
      else if (remaining >= MRAM_WRITE_SIZE)
        {
          /* Handle aligned full blocks */

          chunk = (remaining / MRAM_WRITE_SIZE) * MRAM_WRITE_SIZE;

          ret = ra_mram_write_data(addr, buffer, chunk);
          if (ret < 0)
            {
              ferr("ERROR: Aligned write failed at 0x%08" PRIx32 ": %d\n",
                   addr, ret);
              return ret;
            }
        }
      else
        {
          /* Handle trailing partial block */

          memcpy(aligned_buffer, (void *)addr, MRAM_WRITE_SIZE);
          memcpy(aligned_buffer, buffer, remaining);
          chunk = remaining;

          ret = ra_mram_write_data(addr, aligned_buffer, MRAM_WRITE_SIZE);
          if (ret < 0)
            {
              ferr("ERROR: Trailing write failed at 0x%08" PRIx32 ": %d\n",
                   addr, ret);
              return ret;
            }
        }

      offset += chunk;
      buffer += chunk;
      written += chunk;
      remaining -= chunk;
    }

  return written;
}
#endif /* CONFIG_MTD_BYTE_WRITE */

/****************************************************************************
 * Name: ra_mram_ioctl
 *
 * Description:
 *   Handle MTD ioctl commands.
 *
 ****************************************************************************/

static int ra_mram_ioctl(struct mtd_dev_s *dev, int cmd, unsigned long arg)
{
  struct ra_mram_dev_s *priv = (struct ra_mram_dev_s *)dev;
  int ret = -EINVAL;

  finfo("cmd: %d arg: %lu\n", cmd, arg);

  switch (cmd)
    {
      case MTDIOC_GEOMETRY:
        {
          struct mtd_geometry_s *geo =
            (struct mtd_geometry_s *)((uintptr_t)arg);
          if (geo)
            {
              /* Report geometry based on programming size */

              geo->blocksize    = priv->blocksize;
              geo->erasesize    = priv->erasesize;
              geo->neraseblocks = priv->nblocks;
              ret = OK;

              finfo("blocksize: %" PRId32 " erasesize: %" PRId32
                    " neraseblocks: %" PRId32 "\n",
                    geo->blocksize, geo->erasesize, geo->neraseblocks);
            }
        }
        break;

      case MTDIOC_BULKERASE:
        {
          /* Erase the entire device */

          finfo("MTDIOC_BULKERASE\n");
          ret = ra_mram_erase(dev, 0, priv->nblocks);
        }
        break;

      case BIOC_XIPBASE:
        {
          void **ppv = (void **)((uintptr_t)arg);

          if (ppv)
            {
              /* Return the base address for XIP access */

              *ppv = (void *)priv->base;
              ret = OK;

              finfo("XIP base: 0x%08" PRIx32 "\n", priv->base);
            }
        }
        break;

      case MTDIOC_ERASESTATE:
        {
          uint8_t *result = (uint8_t *)((uintptr_t)arg);
          if (result)
            {
              *result = MRAM_ERASED_STATE;
              ret = OK;
            }
        }
        break;

      default:
        ret = -ENOTTY; /* Bad/unsupported command */
        break;
    }

  return ret;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_mram_initialize
 *
 * Description:
 *   Initialize and return the MTD device for the specified MRAM region.
 *   Call this function to get access to either the code MRAM or data MRAM
 *   partition.
 *
 * Input Parameters:
 *   data_flash - true for data partition (parameter storage)
 *                false for code partition (OTA, bootloader)
 *
 * Returned Value:
 *   Pointer to MTD device structure on success, NULL on failure.
 *
 ****************************************************************************/

struct mtd_dev_s *ra_mram_initialize(bool data_flash)
{
  struct ra_mram_dev_s *priv;
  irqstate_t flags;

  finfo("data_flash: %d\n", data_flash);

  /* Select the appropriate MRAM device */

  if (data_flash)
    {
      priv = &g_data_mram;
    }
  else
    {
      priv = &g_code_mram;
    }

  /* Check if already initialized */

  if (priv->initialized)
    {
      finfo("MRAM already initialized\n");
      return &priv->mtd;
    }

  /* Initialize with interrupts disabled */

  flags = enter_critical_section();

  /* Initialize MRAM timing parameters */

  ra_mram_init_timeouts();

  /* Enable pre-fetch buffer for read performance */

  ra_mram_set_pfb(true);

  /* Reset any pending errors */

  ra_mram_reset();

  /* Mark as initialized */

  priv->initialized = true;

  leave_critical_section(flags);

  finfo("MRAM %s initialized: base=0x%08" PRIx32 " size=%" PRIu32
        " blocksize=%" PRIu32 " erasesize=%" PRIu32 " nblocks=%" PRIu32 "\n",
        data_flash ? "data" : "code",
        priv->base, priv->size, priv->blocksize, priv->erasesize,
        priv->nblocks);

  return &priv->mtd;
}

/****************************************************************************
 * Name: ra_mram_erasestate
 *
 * Description:
 *   Return the erase state of the MRAM (value that appears after erase).
 *   For MRAM this is 0xFF to maintain compatibility with traditional flash.
 *
 * Returned Value:
 *   The erase state (0xFF).
 *
 ****************************************************************************/

uint8_t ra_mram_erasestate(void)
{
  return MRAM_ERASED_STATE;
}

/****************************************************************************
 * Name: up_progmem_neraseblocks
 *
 * Description:
 *   Return total number of erase blocks in code MRAM.
 *   This function provides progmem compatibility for bootloader/OTA.
 *
 ****************************************************************************/

#ifdef CONFIG_RA_MRAM_PROGMEM
size_t up_progmem_neraseblocks(void)
{
  return g_code_mram.nblocks;
}

/****************************************************************************
 * Name: up_progmem_isuniform
 *
 * Description:
 *   Check if MRAM has uniform block sizes.
 *
 * Returned Value:
 *   true - MRAM blocks are uniform
 *
 ****************************************************************************/

bool up_progmem_isuniform(void)
{
  return true;
}

/****************************************************************************
 * Name: up_progmem_pagesize
 *
 * Description:
 *   Return page size (programming unit).
 *
 * Input Parameters:
 *   page - Page number (unused, all pages same size)
 *
 * Returned Value:
 *   Programming size (32 bytes for RA8P1 MRAM)
 *
 ****************************************************************************/

size_t up_progmem_pagesize(size_t page)
{
  UNUSED(page);
  return MRAM_WRITE_SIZE;
}

/****************************************************************************
 * Name: up_progmem_erasesize
 *
 * Description:
 *   Return erase block size for the specified block.
 *
 * Input Parameters:
 *   block - Block number
 *
 * Returned Value:
 *   Erase block size
 *
 ****************************************************************************/

size_t up_progmem_erasesize(size_t block)
{
  UNUSED(block);
  return RA_MRAM_CODE_BLOCK_SIZE;
}

/****************************************************************************
 * Name: up_progmem_getpage
 *
 * Description:
 *   Get page number for the given address.
 *
 * Input Parameters:
 *   addr - MRAM address
 *
 * Returned Value:
 *   Page number or negative error
 *
 ****************************************************************************/

ssize_t up_progmem_getpage(size_t addr)
{
  if (addr < RA_MRAM_CODE_START ||
      addr >= RA_MRAM_CODE_START + g_code_mram.size)
    {
      return -EFAULT;
    }

  return (addr - RA_MRAM_CODE_START) / MRAM_WRITE_SIZE;
}

/****************************************************************************
 * Name: up_progmem_getaddress
 *
 * Description:
 *   Get address for the given page.
 *
 * Input Parameters:
 *   page - Page number
 *
 * Returned Value:
 *   Address or SIZE_MAX on error
 *
 ****************************************************************************/

size_t up_progmem_getaddress(size_t page)
{
  if (page >= g_code_mram.size / MRAM_WRITE_SIZE)
    {
      return SIZE_MAX;
    }

  return RA_MRAM_CODE_START + page * MRAM_WRITE_SIZE;
}

/****************************************************************************
 * Name: up_progmem_eraseblock
 *
 * Description:
 *   Erase the specified block.
 *
 * Input Parameters:
 *   block - Block number to erase
 *
 * Returned Value:
 *   Block size on success, negative error on failure
 *
 ****************************************************************************/

ssize_t up_progmem_eraseblock(size_t block)
{
  uint32_t addr;
  int ret;

  if (block >= g_code_mram.nblocks)
    {
      return -EFAULT;
    }

  addr = RA_MRAM_CODE_START + block * RA_MRAM_CODE_BLOCK_SIZE;

  ret = ra_mram_erase_block_internal(addr);
  if (ret < 0)
    {
      return ret;
    }

  return RA_MRAM_CODE_BLOCK_SIZE;
}

/****************************************************************************
 * Name: up_progmem_ispageerased
 *
 * Description:
 *   Check if the specified page is erased.
 *
 * Input Parameters:
 *   page - Page number
 *
 * Returned Value:
 *   true if erased, false otherwise
 *
 ****************************************************************************/

bool up_progmem_ispageerased(size_t page)
{
  const uint8_t *p;
  size_t addr;
  size_t i;

  addr = up_progmem_getaddress(page);
  if (addr == SIZE_MAX)
    {
      return false;
    }

  p = (const uint8_t *)addr;
  for (i = 0; i < MRAM_WRITE_SIZE; i++)
    {
      if (p[i] != MRAM_ERASED_STATE)
        {
          return false;
        }
    }

  return true;
}

/****************************************************************************
 * Name: up_progmem_write
 *
 * Description:
 *   Write data to program memory.
 *
 * Input Parameters:
 *   addr   - Target address
 *   buf    - Data buffer
 *   count  - Number of bytes
 *
 * Returned Value:
 *   Number of bytes written or negative error
 *
 ****************************************************************************/

ssize_t up_progmem_write(size_t addr, const void *buf, size_t count)
{
  int ret;

  if (addr < RA_MRAM_CODE_START ||
      addr + count > RA_MRAM_CODE_START + g_code_mram.size)
    {
      return -EFAULT;
    }

  /* Handle alignment - must write in 32-byte chunks */

  if ((addr % MRAM_WRITE_SIZE) != 0 || (count % MRAM_WRITE_SIZE) != 0)
    {
      /* For unaligned writes, use the byte write function if available */

#ifdef CONFIG_MTD_BYTE_WRITE
      return ra_mram_write(&g_code_mram.mtd, addr - RA_MRAM_CODE_START,
                           count, buf);
#else
      return -EINVAL;
#endif
    }

  ret = ra_mram_write_data(addr, buf, count);
  if (ret < 0)
    {
      return ret;
    }

  return count;
}

/****************************************************************************
 * Name: up_progmem_erasestate
 *
 * Description:
 *   Return the erase state for program memory.
 *
 * Returned Value:
 *   Erased state value (0xFF)
 *
 ****************************************************************************/

uint8_t up_progmem_erasestate(void)
{
  return MRAM_ERASED_STATE;
}
#endif /* CONFIG_RA_MRAM_PROGMEM */