/****************************************************************************
 * arch/arm/src/ra8/ra_ov5640.c
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
#include <stdint.h>
#include <debug.h>
#include <nuttx/arch.h>
#include <nuttx/i2c/i2c_master.h>

#include "ra_ov5640.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define OV5640_I2C_ADDR                        0x3c
#define OV5640_I2C_FREQ                        400000

#define OV5640_REG_END                         0xffff
#define OV5640_REG_DELAY                       0xaaaa

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

struct ov5640_reg_s
{
  uint16_t reg;
  uint8_t  val;
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

static int ra_ov5640_write(struct i2c_master_s *i2c, uint16_t reg,
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

  return I2C_TRANSFER(i2c, &msg, 1);
}

static int ra_ov5640_read(struct i2c_master_s *i2c, uint16_t reg,
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

  return I2C_TRANSFER(i2c, msgs, 2);
}

static int ra_ov5640_write_array(struct i2c_master_s *i2c,
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

      int ret = ra_ov5640_write(i2c, regs->reg, regs->val);
      if (ret < 0)
        {
          camerr("I2C write failed reg=%04x\n", regs->reg);
          return ret;
        }

      regs++;
    }

  return OK;
}

static int ra_ov5640_configure_clocks(struct i2c_master_s *i2c)
{
  int ret = ra_ov5640_write(i2c, 0x3035, (1 << 4) | 2);
  if (ret < 0)
    {
      return ret;
    }

  ret = ra_ov5640_write(i2c, 0x3036, 123);
  if (ret < 0)
    {
      return ret;
    }

  ret = ra_ov5640_write(i2c, 0x3037, 0x11);
  if (ret < 0)
    {
      return ret;
    }

  return ra_ov5640_write(i2c, 0x3108, 0x01);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

int ra_ov5640_set_virtual_channel(struct i2c_master_s *i2c,
                                  uint8_t channel)
{
  uint8_t regval;
  int ret = ra_ov5640_read(i2c, 0x4814, &regval);
  if (ret < 0)
    {
      return ret;
    }

  regval &= ~(3 << 6);
  regval |= ((channel & 0x3) << 6);
  return ra_ov5640_write(i2c, 0x4814, regval);
}

int ra_ov5640_set_resolution(struct i2c_master_s *i2c,
                             uint16_t width, uint16_t height)
{
  if (width == 0 || height == 0)
    {
      return -EINVAL;
    }

  int ret = ra_ov5640_write(i2c, 0x3808, (width >> 8) & 0xff);
  if (ret >= 0)
    {
      ret = ra_ov5640_write(i2c, 0x3809, width & 0xff);
    }
  if (ret >= 0)
    {
      ret = ra_ov5640_write(i2c, 0x380a, (height >> 8) & 0xff);
    }
  if (ret >= 0)
    {
      ret = ra_ov5640_write(i2c, 0x380b, height & 0xff);
    }

  return ret;
}

int ra_ov5640_set_fps(struct i2c_master_s *i2c, uint16_t width, uint16_t height)
{
  uint16_t hts = (width >= 1024) ? 0x0d78 : 0x0780;
  uint16_t vts = (height >= 600) ? 0x06a4 : 0x03e8;
  int ret = ra_ov5640_write(i2c, 0x380c, (hts >> 8) & 0xff);
  if (ret >= 0)
    {
      ret = ra_ov5640_write(i2c, 0x380d, hts & 0xff);
    }
  if (ret >= 0)
    {
      ret = ra_ov5640_write(i2c, 0x380e, (vts >> 8) & 0xff);
    }
  if (ret >= 0)
    {
      ret = ra_ov5640_write(i2c, 0x380f, vts & 0xff);
    }
  return ret;
}

int ra_ov5640_init(struct i2c_master_s *i2c, uint16_t width, uint16_t height, uint8_t channel)
{
  caminfo("Initializing OV5640\n");

  int ret = ra_ov5640_write_array(i2c, g_ov5640_init_regs);
  if (ret < 0)
    {
      return ret;
    }

  up_mdelay(50);

  ret = ra_ov5640_configure_clocks(i2c);
  if (ret < 0)
    {
      return ret;
    }

  ret = ra_ov5640_set_resolution(i2c, width, height);
  if (ret < 0)
    {
      return ret;
    }

  ret = ra_ov5640_set_fps(i2c, width, height);
  if (ret < 0)
    {
      return ret;
    }

  return ra_ov5640_set_virtual_channel(i2c, channel);
}

int ra_ov5640_stream_on(struct i2c_master_s *i2c)
{
  return ra_ov5640_write_array(i2c, g_ov5640_stream_on);
}

int ra_ov5640_stream_off(struct i2c_master_s *i2c)
{
  return ra_ov5640_write_array(i2c, g_ov5640_stream_off);
}
