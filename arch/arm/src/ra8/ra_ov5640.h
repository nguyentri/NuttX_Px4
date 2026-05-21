/****************************************************************************
 * arch/arm/src/ra8/ra_ov5640.h
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

#ifndef __ARCH_ARM_SRC_RA8_RA_OV5640_H
#define __ARCH_ARM_SRC_RA8_RA_OV5640_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/i2c/i2c_master.h>

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

int ra_ov5640_init(struct i2c_master_s *i2c, uint16_t width, uint16_t height, uint8_t channel);
int ra_ov5640_stream_on(struct i2c_master_s *i2c);
int ra_ov5640_stream_off(struct i2c_master_s *i2c);
int ra_ov5640_set_resolution(struct i2c_master_s *i2c, uint16_t width, uint16_t height);
int ra_ov5640_set_fps(struct i2c_master_s *i2c, uint16_t width, uint16_t height);
int ra_ov5640_set_virtual_channel(struct i2c_master_s *i2c, uint8_t channel);

#endif /* __ARCH_ARM_SRC_RA8_RA_OV5640_H */
