/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_gpio.c
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

#include "ra_gpio.h"
#include <arch/board/board.h>

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra8p1_gpio_initialize
 *
 * Description:
 *   Initialize all board GPIO pins using centralized configuration
 *
 ****************************************************************************/

int ra8p1_gpio_initialize(void)
{
  const uint32_t gpio_list[] = RA8_GPIO_INIT_LIST;
  return ra_gpioconfiglist(gpio_list, sizeof(gpio_list) / sizeof(uint32_t));
}
