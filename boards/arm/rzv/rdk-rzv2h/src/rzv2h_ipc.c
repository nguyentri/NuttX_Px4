/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_ipc.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 ****************************************************************************/

#include <nuttx/config.h>

#ifdef CONFIG_RZV_OPENAMP

#include <syslog.h>

#include "rdk-rzv2h.h"
#include "rzv_ipc.h"

int board_ipc_initialize(void)
{
  int ret;

  ret = rzv_ipc_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: RZ/V2H IPC init failed: %d\n", ret);
      return ret;
    }

#ifdef CONFIG_RZV_IPC_IPCC
  ret = rzv_ipcc_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: RZ/V2H IPCC init failed: %d\n", ret);
      return ret;
    }

  syslog(LOG_INFO, "RZ/V2H IPCC registered at /dev/ipcc0\n");
#endif

  return 0;
}

#endif /* CONFIG_RZV_OPENAMP */
