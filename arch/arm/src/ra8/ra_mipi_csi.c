/****************************************************************************
 * arch/arm/src/ra8/ra_mipi_csi.c
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

#include <errno.h>
#include <poll.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <nuttx/arch.h>
#include <debug.h>
#include <nuttx/fs/fs.h>
#include <nuttx/i2c/i2c_master.h>
#include <nuttx/irq.h>
#include <nuttx/mutex.h>
#include <nuttx/semaphore.h>

#include "arm_internal.h"
#include "chip.h"
#include <arch/chip/ra8p1_irq.h>
#include "hardware/ra8p1/ra_mipi_csi.h"
#include "hardware/ra8p1/ra_vin.h"
#include "ra_icu.h"
#include "ra_i2c.h"
#include "ra_mipi_csi.h"
#include "ra_mstp.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#ifndef CONFIG_RA_MIPI_CSI_DEFAULT_WIDTH
#  define CONFIG_RA_MIPI_CSI_DEFAULT_WIDTH   640
#endif

#ifndef CONFIG_RA_MIPI_CSI_DEFAULT_HEIGHT
#  define CONFIG_RA_MIPI_CSI_DEFAULT_HEIGHT  480
#endif

#ifndef CONFIG_RA_MIPI_CSI_MAX_WIDTH
#  define CONFIG_RA_MIPI_CSI_MAX_WIDTH       1024
#endif

#ifndef CONFIG_RA_MIPI_CSI_MAX_HEIGHT
#  define CONFIG_RA_MIPI_CSI_MAX_HEIGHT      600
#endif

#ifndef CONFIG_RA_MIPI_CSI_FB_BASE
#  define CONFIG_RA_MIPI_CSI_FB_BASE         0x60000000
#endif

#ifndef CONFIG_RA_MIPI_CSI_I2C_BUS
#  define CONFIG_RA_MIPI_CSI_I2C_BUS         0
#endif

#ifndef CONFIG_RA_MIPI_CSI_DATA_LANES
#  define CONFIG_RA_MIPI_CSI_DATA_LANES      2
#endif

#ifndef CONFIG_RA_MIPI_CSI_VIRTUAL_CHANNEL
#  define CONFIG_RA_MIPI_CSI_VIRTUAL_CHANNEL 0
#endif

#ifndef CONFIG_RA_MIPI_CSI_POLLWAITERS
#  define CONFIG_RA_MIPI_CSI_POLLWAITERS     4
#endif

#define OV5640_I2C_ADDR                        0x3c
#define OV5640_I2C_FREQ                        400000

#define BYTES_PER_PIXEL                        3
#define FB_COUNT                               2

#define OV5640_REG_END                         0xffff
#define OV5640_REG_DELAY                       0xaaaa

#define CAM_FMT_RGB888                         0

#ifdef CONFIG_DEBUG_CAMERA
#  define camerr    _err
#  define camwarn   _warn
#  define caminfo   _info
#else
#  define camerr(x...)
#  define camwarn(x...)
#  define caminfo(x...)
#endif

/****************************************************************************
 * Private Types
 ****************************************************************************/

enum ra_camera_state_e
{
  CAMERA_STOPPED = 0,
  CAMERA_STREAMING
};

struct ov5640_reg_s
{
  uint16_t reg;
  uint8_t  val;
};

struct ra_mipi_csi_s
{
  struct i2c_master_s *i2c;
  mutex_t              lock;
  sem_t                frame_sem;
  uint8_t             *fb[FB_COUNT];
  uint16_t             width;
  uint16_t             height;
  size_t               frame_size;
  uint32_t             frame_count;
  uint8_t              ready_fb;
  enum ra_camera_state_e state;
  int                  open_count;
  int                  vin_irq;
  int                  csi_irq;
#ifndef CONFIG_DISABLE_POLL
  struct pollfd       *poll_fds[CONFIG_RA_MIPI_CSI_POLLWAITERS];
#endif
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static int     ra_camera_open(struct file *filep);
static int     ra_camera_close(struct file *filep);
static ssize_t ra_camera_read(struct file *filep, char *buffer, size_t buflen);
static int     ra_camera_ioctl(struct file *filep, int cmd, unsigned long arg);
#ifndef CONFIG_DISABLE_POLL
static int     ra_camera_poll(struct file *filep, struct pollfd *fds,
                              bool setup);
#endif

static int  ra_mipi_csi_isr(int irq, void *context, void *arg);
static int  ra_vin_isr(int irq, void *context, void *arg);
static void ra_camera_pollnotify(struct ra_mipi_csi_s *priv,
                                 pollevent_t events);
static int  ra_camera_start_stream(struct ra_mipi_csi_s *priv);
static void ra_camera_stop_stream(struct ra_mipi_csi_s *priv);
static int  ra_camera_hw_setup(struct ra_mipi_csi_s *priv);
static void ra_camera_hw_shutdown(struct ra_mipi_csi_s *priv);
static void ra_mipi_csi_hw_init(void);
static void ra_vin_hw_init(struct ra_mipi_csi_s *priv);
static int  ra_ov5640_init(struct ra_mipi_csi_s *priv);
static int  ra_ov5640_stream_on(struct ra_mipi_csi_s *priv);
static int  ra_ov5640_stream_off(struct ra_mipi_csi_s *priv);
static int  ra_ov5640_write(struct ra_mipi_csi_s *priv, uint16_t reg,
                            uint8_t val);
static int  ra_ov5640_read(struct ra_mipi_csi_s *priv, uint16_t reg,
                           uint8_t *val);
static int  ra_ov5640_write_array(struct ra_mipi_csi_s *priv,
                                  const struct ov5640_reg_s *regs);
static int  ra_ov5640_configure_clocks(struct ra_mipi_csi_s *priv);
static int  ra_ov5640_set_resolution(struct ra_mipi_csi_s *priv,
                                     uint16_t width, uint16_t height);
static int  ra_ov5640_set_virtual_channel(struct ra_mipi_csi_s *priv,
                                          uint8_t channel);
static int  ra_ov5640_set_fps(struct ra_mipi_csi_s *priv);

/****************************************************************************
 * Private Data
 ****************************************************************************/

static struct ra_mipi_csi_s g_mipi_csi;

static const struct file_operations g_camera_fops =
{
  .open  = ra_camera_open,
  .close = ra_camera_close,
  .read  = ra_camera_read,
  .write = NULL,
  .seek  = NULL,
  .ioctl = ra_camera_ioctl,
#ifndef CONFIG_DISABLE_POLL
  .poll  = ra_camera_poll,
#else
  .poll  = NULL,
#endif
};

/****************************************************************************
 * OV5640 Register Tables
 ****************************************************************************/

static const struct ov5640_reg_s g_ov5640_init_regs[] =
{
  {0x3008, 0x42}, {0x3103, 0x13}, {0x3103, 0x03}, {0x3000, 0x00},
  {0x3004, 0xff}, {0x3002, 0x1c}, {0x3006, 0xc3}, {0x300e, 0x45},
  {0x302e, 0x08}, {0x3034, 0x18}, {0x501f, 0x00}, {0x4300, 0x32},
  {0x3618, 0x00}, {0x3612, 0x29}, {0x3709, 0x52}, {0x370c, 0x03},
  {0x3820, 0x40}, {0x3821, 0x01}, {0x3630, 0x36}, {0x3631, 0x0e},
  {0x3632, 0xe2}, {0x3633, 0x12}, {0x3621, 0xe0}, {0x3704, 0xa0},
  {0x3703, 0x5a}, {0x3715, 0x78}, {0x3717, 0x01}, {0x370b, 0x60},
  {0x3705, 0x1a}, {0x3905, 0x02}, {0x3906, 0x10}, {0x3901, 0x0a},
  {0x3731, 0x12}, {0x3600, 0x08}, {0x3601, 0x33}, {0x302d, 0x60},
  {0x3620, 0x52}, {0x371b, 0x20}, {0x471c, 0x50}, {0x3a13, 0x43},
  {0x3a18, 0x00}, {0x3a19, 0xf8}, {0x3635, 0x13}, {0x3636, 0x03},
  {0x3634, 0x40}, {0x3622, 0x01}, {0x4001, 0x02}, {0x4004, 0x02},
  {0x4005, 0x1a}, {0x5001, 0xa3}, {0x3503, 0x07}, {0x3500, 0x00},
  {0x3501, 0xff}, {0x3502, 0x00}, {0x350a, 0x00}, {0x350b, 0x20},
  {0x3a0f, 0x30}, {0x3a10, 0x28}, {0x3a1b, 0x30}, {0x3a1e, 0x26},
  {0x3a11, 0x60}, {0x3a1f, 0x14}, {0x3406, 0x01}, {0x3400, 0x07},
  {0x3401, 0x70}, {0x3402, 0x04}, {0x3403, 0x00}, {0x3404, 0x05},
  {0x3405, 0xc0}, {0x5480, 0x01}, {0x5481, 0x08}, {0x5482, 0x14},
  {0x5483, 0x28}, {0x5484, 0x51}, {0x5485, 0x65}, {0x5486, 0x71},
  {0x5487, 0x7d}, {0x5488, 0x87}, {0x5489, 0x91}, {0x548a, 0x9a},
  {0x548b, 0xaa}, {0x548c, 0xb8}, {0x548d, 0xcd}, {0x548e, 0xdd},
  {0x548f, 0xea}, {0x5490, 0x1d}, {0x5580, 0x06}, {0x5583, 0x40},
  {0x5584, 0x10}, {0x5589, 0x10}, {0x558a, 0x00}, {0x558b, 0xf8},
  {0x5800, 0x23}, {0x5801, 0x14}, {0x5802, 0x0f}, {0x5803, 0x0f},
  {0x5804, 0x12}, {0x5805, 0x26}, {0x5806, 0x0c}, {0x5807, 0x08},
  {0x5808, 0x05}, {0x5809, 0x05}, {0x580a, 0x08}, {0x580b, 0x0d},
  {0x580c, 0x08}, {0x580d, 0x03}, {0x580e, 0x00}, {0x580f, 0x00},
  {0x5810, 0x03}, {0x5811, 0x09}, {0x5812, 0x07}, {0x5813, 0x03},
  {0x5814, 0x00}, {0x5815, 0x01}, {0x5816, 0x03}, {0x5817, 0x08},
  {0x5818, 0x0d}, {0x5819, 0x08}, {0x581a, 0x05}, {0x581b, 0x06},
  {0x581c, 0x08}, {0x581d, 0x0e}, {0x581e, 0x29}, {0x581f, 0x17},
  {0x5820, 0x11}, {0x5821, 0x11}, {0x5822, 0x15}, {0x5823, 0x28},
  {0x5824, 0x46}, {0x5825, 0x26}, {0x5826, 0x08}, {0x5827, 0x26},
  {0x5828, 0x64}, {0x5829, 0x26}, {0x582a, 0x24}, {0x582b, 0x22},
  {0x582c, 0x24}, {0x582d, 0x24}, {0x582e, 0x06}, {0x582f, 0x22},
  {0x5830, 0x40}, {0x5831, 0x42}, {0x5832, 0x24}, {0x5833, 0x26},
  {0x5834, 0x24}, {0x5835, 0x22}, {0x5836, 0x22}, {0x5837, 0x26},
  {0x5838, 0x44}, {0x5839, 0x24}, {0x583a, 0x26}, {0x583b, 0x28},
  {0x583c, 0x42}, {0x583d, 0xce}, {0x503d, 0x00}, {0x4741, 0x00},
  {OV5640_REG_END, 0x00}
};

static const struct ov5640_reg_s g_ov5640_stream_on[] =
{
  {0x3008, 0x02},
  {0x4202, 0x00},
  {OV5640_REG_END, 0x00}
};

static const struct ov5640_reg_s g_ov5640_stream_off[] =
{
  {0x4202, 0x0f},
  {OV5640_REG_END, 0x00}
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

#ifndef CONFIG_DISABLE_POLL
static void ra_camera_pollnotify(struct ra_mipi_csi_s *priv,
                                 pollevent_t events)
{
  for (int i = 0; i < CONFIG_RA_MIPI_CSI_POLLWAITERS; i++)
    {
      struct pollfd *fds = priv->poll_fds[i];

      if (fds != NULL)
        {
          fds->revents |= events;
          if (fds->priv != NULL)
            {
              nxsem_post((sem_t *)fds->priv);
            }
        }
    }
}
#endif

static void ra_vin_update_ready(struct ra_mipi_csi_s *priv)
{
  uint32_t ms = getreg32(R_VIN_MS);
  uint32_t fms = (ms & R_VIN_MS_FMS_MASK) >> R_VIN_MS_FMS_SHIFT;

  switch (fms)
    {
      case 0:
        priv->ready_fb = 0;
        break;
      case 1:
        priv->ready_fb = 1;
        break;
      case 2:
        priv->ready_fb = 0;
        break;
      default:
        break;
    }
}

static int ra_vin_isr(int irq, void *context, void *arg)
{
  struct ra_mipi_csi_s *priv = arg;
  uint32_t status = getreg32(R_VIN_INTS);

  if (status & (R_VIN_INTS_EFS | R_VIN_INTS_FMS))
    {
      ra_vin_update_ready(priv);
      priv->frame_count++;
      nxsem_post(&priv->frame_sem);
#ifndef CONFIG_DISABLE_POLL
      ra_camera_pollnotify(priv, POLLIN);
#endif
    }

  if (status & R_VIN_INTS_FOS)
    {
      camwarn("VIN FIFO overflow\n");
    }

  putreg32(status, R_VIN_INTS);
  return OK;
}

static int ra_mipi_csi_isr(int irq, void *context, void *arg)
{
  uint32_t status = getreg32(R_MIPI_CSI_MIST);
  if (status != 0)
    {
      putreg32(status, R_MIPI_CSI_MIST);
      putreg32(R_MIPI_CSI_RXSC_RACTDETC, R_MIPI_CSI_RXSC);
    }

  return OK;
}

static int ra_ov5640_write(struct ra_mipi_csi_s *priv, uint16_t reg,
                           uint8_t val)
{
  uint8_t buf[3] =
  {
    reg >> 8,
    reg & 0xff,
    val
  };

  struct i2c_msg_s msg =
  {
    .frequency = OV5640_I2C_FREQ,
    .addr      = OV5640_I2C_ADDR,
    .flags     = 0,
    .buffer    = buf,
    .length    = sizeof(buf)
  };

  return I2C_TRANSFER(priv->i2c, &msg, 1);
}

static int ra_ov5640_read(struct ra_mipi_csi_s *priv, uint16_t reg,
                          uint8_t *val)
{
  uint8_t addr_buf[2] =
  {
    reg >> 8,
    reg & 0xff
  };

  struct i2c_msg_s msgs[2] =
  {
    {
      .frequency = OV5640_I2C_FREQ,
      .addr      = OV5640_I2C_ADDR,
      .flags     = 0,
      .buffer    = addr_buf,
      .length    = sizeof(addr_buf)
    },
    {
      .frequency = OV5640_I2C_FREQ,
      .addr      = OV5640_I2C_ADDR,
      .flags     = I2C_M_READ,
      .buffer    = val,
      .length    = 1
    }
  };

  return I2C_TRANSFER(priv->i2c, msgs, 2);
}

static int ra_ov5640_write_array(struct ra_mipi_csi_s *priv,
                                 const struct ov5640_reg_s *regs)
{
  while (regs->reg != OV5640_REG_END)
    {
      if (regs->reg == OV5640_REG_DELAY)
        {
          up_mdelay(regs->val);
          regs++;
          continue;
        }

      int ret = ra_ov5640_write(priv, regs->reg, regs->val);
      if (ret < 0)
        {
          camerr("I2C write failed reg=%04x\n", regs->reg);
          return ret;
        }

      regs++;
    }

  return OK;
}

static int ra_ov5640_configure_clocks(struct ra_mipi_csi_s *priv)
{
  int ret = ra_ov5640_write(priv, 0x3035, (1 << 4) | 2);
  if (ret < 0)
    {
      return ret;
    }

  ret = ra_ov5640_write(priv, 0x3036, 123);
  if (ret < 0)
    {
      return ret;
    }

  ret = ra_ov5640_write(priv, 0x3037, 0x11);
  if (ret < 0)
    {
      return ret;
    }

  return ra_ov5640_write(priv, 0x3108, 0x01);
}

static int ra_ov5640_set_virtual_channel(struct ra_mipi_csi_s *priv,
                                         uint8_t channel)
{
  uint8_t regval;
  int ret = ra_ov5640_read(priv, 0x4814, &regval);
  if (ret < 0)
    {
      return ret;
    }

  regval &= ~(3 << 6);
  regval |= ((channel & 0x3) << 6);
  return ra_ov5640_write(priv, 0x4814, regval);
}

static int ra_ov5640_set_resolution(struct ra_mipi_csi_s *priv,
                                    uint16_t width, uint16_t height)
{
  if (width == 0 || height == 0 ||
      width > CONFIG_RA_MIPI_CSI_MAX_WIDTH ||
      height > CONFIG_RA_MIPI_CSI_MAX_HEIGHT)
    {
      return -EINVAL;
    }

  int ret = ra_ov5640_write(priv, 0x3808, (width >> 8) & 0xff);
  if (ret >= 0)
    {
      ret = ra_ov5640_write(priv, 0x3809, width & 0xff);
    }
  if (ret >= 0)
    {
      ret = ra_ov5640_write(priv, 0x380a, (height >> 8) & 0xff);
    }
  if (ret >= 0)
    {
      ret = ra_ov5640_write(priv, 0x380b, height & 0xff);
    }
  if (ret < 0)
    {
      return ret;
    }

  priv->width = width;
  priv->height = height;
  priv->frame_size = (size_t)width * height * BYTES_PER_PIXEL;
  return OK;
}

static int ra_ov5640_set_fps(struct ra_mipi_csi_s *priv)
{
  uint16_t hts = (priv->width >= 1024) ? 0x0d78 : 0x0780;
  uint16_t vts = (priv->height >= 600) ? 0x06a4 : 0x03e8;
  int ret = ra_ov5640_write(priv, 0x380c, (hts >> 8) & 0xff);
  if (ret >= 0)
    {
      ret = ra_ov5640_write(priv, 0x380d, hts & 0xff);
    }
  if (ret >= 0)
    {
      ret = ra_ov5640_write(priv, 0x380e, (vts >> 8) & 0xff);
    }
  if (ret >= 0)
    {
      ret = ra_ov5640_write(priv, 0x380f, vts & 0xff);
    }
  return ret;
}

static int ra_ov5640_init(struct ra_mipi_csi_s *priv)
{
  caminfo("Initializing OV5640\n");

  int ret = ra_ov5640_write_array(priv, g_ov5640_init_regs);
  if (ret < 0)
    {
      return ret;
    }

  up_mdelay(50);

  ret = ra_ov5640_configure_clocks(priv);
  if (ret < 0)
    {
      return ret;
    }

  ret = ra_ov5640_set_resolution(priv,
                                 CONFIG_RA_MIPI_CSI_DEFAULT_WIDTH,
                                 CONFIG_RA_MIPI_CSI_DEFAULT_HEIGHT);
  if (ret < 0)
    {
      return ret;
    }

  ret = ra_ov5640_set_fps(priv);
  if (ret < 0)
    {
      return ret;
    }

  return ra_ov5640_set_virtual_channel(priv,
                                       CONFIG_RA_MIPI_CSI_VIRTUAL_CHANNEL);
}

static int ra_ov5640_stream_on(struct ra_mipi_csi_s *priv)
{
  return ra_ov5640_write_array(priv, g_ov5640_stream_on);
}

static int ra_ov5640_stream_off(struct ra_mipi_csi_s *priv)
{
  return ra_ov5640_write_array(priv, g_ov5640_stream_off);
}

static void ra_mipi_csi_hw_init(void)
{
  ra_mstp_start(RA_MSTP_MIPI_CSI);

  putreg32(R_MIPI_CSI_RTCT_VSRST, R_MIPI_CSI_RTCT);
  up_udelay(10);
  putreg32(0, R_MIPI_CSI_RTCT);

  uint32_t lanes = (CONFIG_RA_MIPI_CSI_DATA_LANES == 2) ?
                   R_MIPI_CSI_MCT0_VDLN_0X2 : R_MIPI_CSI_MCT0_VDLN_0X1;
  putreg32(lanes, R_MIPI_CSI_MCT0);

  putreg32((0x80 << R_MIPI_CSI_MCT2_FRRCLK_SHIFT) |
           (0x80 << R_MIPI_CSI_MCT2_FRRSKW_SHIFT),
           R_MIPI_CSI_MCT2);

  putreg32(0, R_MIPI_CSI_EPCT);
  putreg32(0, R_MIPI_CSI_EMCT);

  putreg32(0xffffffff, R_MIPI_CSI_DTEL);
  putreg32(0xffffffff, R_MIPI_CSI_DTEH);

  putreg32(R_MIPI_CSI_RXIE_RACTDETE, R_MIPI_CSI_RXIE);

  putreg32(R_MIPI_CSI_VCIE_FSRE | R_MIPI_CSI_VCIE_FERE,
           R_MIPI_CSI_VCIE(CONFIG_RA_MIPI_CSI_VIRTUAL_CHANNEL));
}

static void ra_vin_hw_init(struct ra_mipi_csi_s *priv)
{
  ra_mstp_start(RA_MSTP_VIN);

  putreg32(0, R_VIN_MC);
  putreg32((CONFIG_RA_MIPI_CSI_VIRTUAL_CHANNEL <<
            R_VIN_CSI_IFMD_VC_SEL_SHIFT) |
           R_VIN_CSI_IFMD_DT_0X24,
           R_VIN_CSI_IFMD);
  putreg32(0, R_VIN_CSIFLD);
  putreg32(R_VIN_DMR_DTMD_00, R_VIN_DMR);

  putreg32(0, R_VIN_SLPRC);
  putreg32(priv->height - 1, R_VIN_ELPRC);
  putreg32(0, R_VIN_SPPRC);
  putreg32(priv->width - 1, R_VIN_EPPRC);
  putreg32(priv->width, R_VIN_IS);

  putreg32((uint32_t)priv->fb[0], R_VIN_MB1);
  putreg32((uint32_t)priv->fb[1], R_VIN_MB2);
  putreg32((uint32_t)priv->fb[0], R_VIN_MB3);

  putreg32(R_VIN_MC_IM_01 | R_VIN_MC_INF_110, R_VIN_MC);
  putreg32(R_VIN_IE_EFE | R_VIN_IE_FME | R_VIN_IE_FOE, R_VIN_IE);
  putreg32(0, R_VIN_FC);
}

static int ra_camera_hw_setup(struct ra_mipi_csi_s *priv)
{
  priv->fb[0] = (uint8_t *)CONFIG_RA_MIPI_CSI_FB_BASE;
  priv->fb[1] = priv->fb[0] +
    (CONFIG_RA_MIPI_CSI_MAX_WIDTH * CONFIG_RA_MIPI_CSI_MAX_HEIGHT *
     BYTES_PER_PIXEL);

  priv->ready_fb = 0;
  priv->frame_count = 0;
  priv->state = CAMERA_STOPPED;
  nxsem_reset(&priv->frame_sem, 0);

  ra_mipi_csi_hw_init();
  ra_vin_hw_init(priv);

  int ret = ra_ov5640_init(priv);
  if (ret < 0)
    {
      camerr("OV5640 init failed: %d\n", ret);
      return ret;
    }

  return OK;
}

static void ra_camera_hw_shutdown(struct ra_mipi_csi_s *priv)
{
  ra_camera_stop_stream(priv);
  ra_mstp_stop(RA_MSTP_VIN);
  ra_mstp_stop(RA_MSTP_MIPI_CSI);
}

static int ra_camera_start_stream(struct ra_mipi_csi_s *priv)
{
  if (priv->state == CAMERA_STREAMING)
    {
      return OK;
    }

  int ret = ra_ov5640_stream_on(priv);
  if (ret < 0)
    {
      return ret;
    }

  uint32_t regval = getreg32(R_VIN_MC);
  regval |= R_VIN_MC_ST;
  putreg32(regval, R_VIN_MC);
  up_udelay(1);
  regval |= R_VIN_MC_ME;
  putreg32(regval, R_VIN_MC);

  putreg32(R_VIN_FC_CC, R_VIN_FC);
  putreg32(R_MIPI_CSI_MCT3_RXEN, R_MIPI_CSI_MCT3);

  if (priv->vin_irq > 0)
    {
      up_enable_irq(priv->vin_irq);
    }
  if (priv->csi_irq > 0)
    {
      up_enable_irq(priv->csi_irq);
    }

  priv->state = CAMERA_STREAMING;
  return OK;
}

static void ra_camera_stop_stream(struct ra_mipi_csi_s *priv)
{
  if (priv->state == CAMERA_STOPPED)
    {
      return;
    }

  ra_ov5640_stream_off(priv);
  putreg32(0, R_MIPI_CSI_MCT3);
  putreg32(0, R_VIN_FC);

  uint32_t regval = getreg32(R_VIN_MC);
  regval &= ~(R_VIN_MC_ME | R_VIN_MC_ST);
  putreg32(regval, R_VIN_MC);

  if (priv->vin_irq > 0)
    {
      up_disable_irq(priv->vin_irq);
    }
  if (priv->csi_irq > 0)
    {
      up_disable_irq(priv->csi_irq);
    }

  priv->state = CAMERA_STOPPED;
}

/****************************************************************************
 * Character Driver Methods
 ****************************************************************************/

static int ra_camera_open(struct file *filep)
{
  struct ra_mipi_csi_s *priv = filep->f_inode->i_private;
  int ret = OK;

  nxmutex_lock(&priv->lock);

  if (priv->open_count == 0)
    {
      ret = ra_camera_hw_setup(priv);
      if (ret < 0)
        {
          goto errout;
        }
    }

  priv->open_count++;

errout:
  nxmutex_unlock(&priv->lock);
  return ret;
}

static int ra_camera_close(struct file *filep)
{
  struct ra_mipi_csi_s *priv = filep->f_inode->i_private;

  nxmutex_lock(&priv->lock);

  if (priv->open_count > 0)
    {
      priv->open_count--;
    }

  if (priv->open_count == 0)
    {
      ra_camera_hw_shutdown(priv);
    }

  nxmutex_unlock(&priv->lock);
  return OK;
}

static ssize_t ra_camera_read(struct file *filep, char *buffer,
                              size_t buflen)
{
  struct ra_mipi_csi_s *priv = filep->f_inode->i_private;

  if (buflen < priv->frame_size)
    {
      return -EINVAL;
    }

  nxmutex_lock(&priv->lock);
  int ret = ra_camera_start_stream(priv);
  nxmutex_unlock(&priv->lock);
  if (ret < 0)
    {
      return ret;
    }

  ret = nxsem_wait_uninterruptible(&priv->frame_sem);
  if (ret < 0)
    {
      return ret;
    }

  memcpy(buffer, priv->fb[priv->ready_fb], priv->frame_size);
  return priv->frame_size;
}

static int ra_camera_ioctl(struct file *filep, int cmd, unsigned long arg)
{
  struct ra_mipi_csi_s *priv = filep->f_inode->i_private;
  int ret = OK;

  nxmutex_lock(&priv->lock);

  switch (cmd)
    {
      case CAM_CMD_SET_RESOLUTION:
        {
          struct cam_frame_info_s *res = (struct cam_frame_info_s *)arg;
          if (res == NULL)
            {
              ret = -EINVAL;
              break;
            }

          ra_camera_stop_stream(priv);
          ret = ra_ov5640_set_resolution(priv, res->width, res->height);
          if (ret >= 0)
            {
              ret = ra_ov5640_set_fps(priv);
            }
          if (ret >= 0)
            {
              ra_vin_hw_init(priv);
            }
        }
        break;

      case CAM_CMD_START_STREAM:
        ret = ra_camera_start_stream(priv);
        break;

      case CAM_CMD_STOP_STREAM:
        ra_camera_stop_stream(priv);
        break;

      case CAM_CMD_GET_FRAME_INFO:
        {
          struct cam_frame_info_s *info = (struct cam_frame_info_s *)arg;
          if (info == NULL)
            {
              ret = -EINVAL;
              break;
            }

          info->width  = priv->width;
          info->height = priv->height;
          info->size   = priv->frame_size;
          info->format = CAM_FMT_RGB888;
        }
        break;

      default:
        ret = -ENOTTY;
        break;
    }

  nxmutex_unlock(&priv->lock);
  return ret;
}

#ifndef CONFIG_DISABLE_POLL
static int ra_camera_poll(struct file *filep, struct pollfd *fds, bool setup)
{
  struct ra_mipi_csi_s *priv = filep->f_inode->i_private;

  if (!setup)
    {
      for (int i = 0; i < CONFIG_RA_MIPI_CSI_POLLWAITERS; i++)
        {
          if (priv->poll_fds[i] == fds)
            {
              priv->poll_fds[i] = NULL;
              fds->priv = NULL;
              break;
            }
        }

      return OK;
    }

  for (int i = 0; i < CONFIG_RA_MIPI_CSI_POLLWAITERS; i++)
    {
      if (priv->poll_fds[i] == NULL)
        {
          priv->poll_fds[i] = fds;
          fds->priv = &priv->frame_sem;
          break;
        }
      if (i == CONFIG_RA_MIPI_CSI_POLLWAITERS - 1)
        {
          return -ENOMEM;
        }
    }

  int sval;
  nxsem_get_value(&priv->frame_sem, &sval);
  if (sval > 0)
    {
      fds->revents |= POLLIN;
      return OK;
    }

  nxmutex_lock(&priv->lock);
  ra_camera_start_stream(priv);
  nxmutex_unlock(&priv->lock);
  return OK;
}
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

int ra_mipi_csi_initialize(void)
{
  struct ra_mipi_csi_s *priv = &g_mipi_csi;
  int ret;

  memset(priv, 0, sizeof(*priv));

  nxmutex_init(&priv->lock);
  nxsem_init(&priv->frame_sem, 0, 0);

  priv->width = CONFIG_RA_MIPI_CSI_DEFAULT_WIDTH;
  priv->height = CONFIG_RA_MIPI_CSI_DEFAULT_HEIGHT;
  priv->frame_size = (size_t)priv->width * priv->height * BYTES_PER_PIXEL;

  priv->i2c = ra_i2cbus_initialize(CONFIG_RA_MIPI_CSI_I2C_BUS);
  if (priv->i2c == NULL)
    {
      camerr("Failed to init I2C bus\n");
      return -ENODEV;
    }

  priv->csi_irq = ra_icu_attach(RA_ELC_MIPICSI_RX, ra_mipi_csi_isr,
                                priv, false);
  priv->vin_irq = ra_icu_attach(RA_ELC_VIN_IRQ, ra_vin_isr,
                                priv, false);

  ret = register_driver("/dev/camera0", &g_camera_fops, 0666, priv);
  if (ret < 0)
    {
      camerr("Failed to register camera: %d\n", ret);
      if (priv->csi_irq > 0)
        {
          ra_icu_detach(priv->csi_irq);
        }
      if (priv->vin_irq > 0)
        {
          ra_icu_detach(priv->vin_irq);
        }
      ra_i2cbus_uninitialize(priv->i2c);
      priv->i2c = NULL;
      return ret;
    }

  caminfo("MIPI-CSI driver ready on /dev/camera0\n");
  return OK;
}
