/****************************************************************************
 * arch/arm/src/rzv/rzv_ipc.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 ****************************************************************************/

#include <nuttx/config.h>

#ifdef CONFIG_RZV_OPENAMP

#include "rzv_ipc.h"
#include "rzv_openamp.h"
#include "rzv_rproc.h"

int rzv_ipc_initialize(void)
{
  /* rzv_openamp_initialize() covers: resource table init, MHU IRQ attach,
   * and rptun_initialize() (which wires the notify callback and spawns the
   * RPTUN worker thread).  rzv_ipcc_initialize() is called separately by
   * the board layer and registers the rpmsg watcher before rptun fires.
   */

  return rzv_openamp_initialize();
}

#endif /* CONFIG_RZV_OPENAMP */
