/****************************************************************************
 * boards/arm/ra8/evk-ra8p1/src/ra8p1_i3c.c
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

#include <debug.h>
#include <errno.h>

#include "ra_i3c.h"
#include "evk-ra8p1.h"

#ifdef CONFIG_RA_I3C

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_i3c_initialize
 *
 * Description:
 *   Initialize and register the I3C driver.
 *
 ****************************************************************************/

int board_i3c_initialize(void)
{
#ifdef CONFIG_RA_I3C0
  int ret;

  ret = ra_i3cbus_initialize(0);
  if (ret < 0)
    {
      i3cerr("ERROR: Failed to initialize I3C0: %d\n", ret);
      return ret;
    }

  i3cinfo("I3C0 initialized successfully\n");
#endif

  return OK;
}

#endif /* CONFIG_RA_I3C */
