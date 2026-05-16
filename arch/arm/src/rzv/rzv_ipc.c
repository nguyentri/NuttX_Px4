/****************************************************************************
 * arch/arm/src/rzv/rzv_ipc.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 ****************************************************************************/

#include <nuttx/config.h>

#ifdef CONFIG_RZV_OPENAMP

#include "rzv_ipc.h"
#include "rzv_rproc.h"

int rzv_ipc_initialize(void)
{
  return rzv_rproc_initialize();
}

#endif /* CONFIG_RZV_OPENAMP */
