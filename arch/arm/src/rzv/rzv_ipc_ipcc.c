/****************************************************************************
 * arch/arm/src/rzv/rzv_ipc_ipcc.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * real cleanup — unregister rpmsg cb, NULL upper, mutex guard
 *           against UAF on concurrent dispatch (IPC-API-001, IPC-API-007).
 *
 ****************************************************************************/

#include <nuttx/config.h>

#ifdef CONFIG_RZV_IPC_IPCC

#include <errno.h>
#include <stdbool.h>
#include <string.h>

#include <nuttx/ipcc.h>
#include <nuttx/mm/circbuf.h>
#include <nuttx/mutex.h>

#include "rzv_ipc.h"
#include "rzv_openamp.h"
#include "rzv_rpmsg.h"

#ifndef CONFIG_RZV_IPCC_RXBUFSIZE
#  define CONFIG_RZV_IPCC_RXBUFSIZE 2048
#endif

#ifndef CONFIG_RZV_IPCC_TXBUFSIZE
#  define CONFIG_RZV_IPCC_TXBUFSIZE 2048
#endif

struct rzv_ipcc_state_s
{
  struct ipcc_lower_s lower;
  bool registered;
};

static struct rzv_ipcc_state_s g_rzv_ipcc;

/* Mutex protecting lower.upper and the rpmsg dispatch path.
 * Dispatch (rptun thread) → lock → check upper → call rxnotify → unlock.
 * Cleanup (close path)    → lock → detach rpmsg → NULL upper → unlock.
 * Static initialiser (mutex_t = sem_t with count 1) — no nxmutex_destroy
 * needed for a module-lifetime object.
 */

static mutex_t g_rzv_ipcc_lock = NXMUTEX_INITIALIZER;

/****************************************************************************
 * Name: rzv_ipcc_rxnotify
 *
 * Description:
 *   Called from RPMsg dispatch context (rptun thread) when a packet
 *   arrives.  Guards upper-half dereference with the mutex + NULL check
 *   to prevent UAF after rzv_ipcc_cleanup() NULLs lower.upper
 *   (IPC-API-007).
 *
 ****************************************************************************/

static void rzv_ipcc_rxnotify(FAR void *arg)
{
  FAR struct rzv_ipcc_state_s *priv = arg;
  FAR struct ipcc_driver_s    *upper;

  nxmutex_lock(&g_rzv_ipcc_lock);

  /* Re-read after lock — cleanup may have NULLed it.
   * Cast through void * to read the pointer atomically without a
   * discarded-volatile warning while still defeating optimisation.
   */

  upper = (FAR struct ipcc_driver_s *)
          (*(FAR void * volatile *)&priv->lower.upper);
  if (upper != NULL)
    {
      ipcc_rxfree_notify(upper);
    }

  nxmutex_unlock(&g_rzv_ipcc_lock);
}

static ssize_t rzv_ipcc_read(FAR struct ipcc_lower_s *ipcc,
                             FAR char *buffer, size_t buflen)
{
  UNUSED(ipcc);
  return rzv_rpmsg_receive(buffer, buflen);
}

static ssize_t rzv_ipcc_write(FAR struct ipcc_lower_s *ipcc,
                              FAR const char *buffer, size_t buflen)
{
  UNUSED(ipcc);
  return rzv_rpmsg_send(buffer, buflen);
}

#ifdef CONFIG_IPCC_BUFFERED
static ssize_t rzv_ipcc_buffer_data(FAR struct ipcc_lower_s *ipcc,
                                    FAR struct circbuf_s *rxbuf)
{
  char tmp[RZV_OPENAMP_RPMSG_BUFFER_SIZE];
  ssize_t nread;

  nread = rzv_rpmsg_receive(tmp, sizeof(tmp));
  if (nread <= 0)
    {
      return nread;
    }

  nread = circbuf_write(rxbuf, tmp, nread);
  if (nread <= 0)
    {
      ipcc->overflow = 1;
      return 0;
    }

  ipcc->overflow = 0;
  return nread;
}

static ssize_t rzv_ipcc_write_notify(FAR struct ipcc_lower_s *ipcc)
{
  char tmp[RZV_OPENAMP_RPMSG_BUFFER_SIZE];
  ssize_t nread;

  nread = circbuf_read(&ipcc->txbuf, tmp, sizeof(tmp));
  if (nread <= 0)
    {
      return nread;
    }

  return rzv_rpmsg_send(tmp, nread);
}
#endif /* CONFIG_IPCC_BUFFERED */

/****************************************************************************
 * Name: rzv_ipcc_cleanup
 *
 * Description:
 *   Real teardown for the IPCC lower half.  Called by the upper half on
 *   the last close before it frees its state (ipcc.h:138-155 contract:
 *   cleanup is called before the upper-half priv is freed).
 *
 *   1. Lock against concurrent dispatch.
 *   2. Detach rpmsg watcher and destroy endpoint if live.
 *   3. NULL lower.upper with a volatile store + DMB so the ISR/dispatch
 *      path cannot chase a stale pointer.
 *   4. Mark not registered so the next open re-initialises cleanly.
 *
 ****************************************************************************/

static int rzv_ipcc_cleanup(FAR struct ipcc_lower_s *lower)
{
  FAR struct rzv_ipcc_state_s *priv =
    (FAR struct rzv_ipcc_state_s *)lower;

  nxmutex_lock(&g_rzv_ipcc_lock);

  rzv_rpmsg_detach();

  /* Volatile NULL store + DMB — prevents dispatch from dereferencing
   * upper after this point (IPC-API-007).
   */

  *(FAR void * volatile *)&lower->upper = NULL;
  __asm__ __volatile__("dmb ish" : : : "memory");

  priv->registered = false;

  nxmutex_unlock(&g_rzv_ipcc_lock);
  return OK;
}

static const struct ipcc_ops_s g_rzv_ipcc_ops =
{
  .read         = rzv_ipcc_read,
  .write        = rzv_ipcc_write,
#ifdef CONFIG_IPCC_BUFFERED
  .buffer_data  = rzv_ipcc_buffer_data,
  .write_notify = rzv_ipcc_write_notify,
#endif
  .cleanup      = rzv_ipcc_cleanup,
};

/****************************************************************************
 * Name: rzv_ipcc_initialize
 *
 * Description:
 *   Register the IPCC lower half with the NuttX IPCC driver.  Idempotent.
 *   Called from the board init path (e.g. rdk_rzv2h_bringup).
 *
 *   Ordering: rzv_rpmsg_initialize() registers the rpmsg device watcher
 *   BEFORE rzv_openamp_initialize() calls rptun_initialize(), so the
 *   device_created callback is guaranteed not to be missed.
 *
 ****************************************************************************/

int rzv_ipcc_initialize(void)
{
  int ret;

  if (g_rzv_ipcc.registered)
    {
      return OK;
    }

  memset(&g_rzv_ipcc, 0, sizeof(g_rzv_ipcc));
  g_rzv_ipcc.lower.ops = g_rzv_ipcc_ops;
  g_rzv_ipcc.lower.chan = 0;

  /* Register rpmsg watcher first (before rptun device starts) */

  ret = rzv_rpmsg_initialize(rzv_ipcc_rxnotify, &g_rzv_ipcc);
  if (ret < 0)
    {
      return ret;
    }

#ifdef CONFIG_IPCC_BUFFERED
  ret = ipcc_register(&g_rzv_ipcc.lower, CONFIG_RZV_IPCC_RXBUFSIZE,
                      CONFIG_RZV_IPCC_TXBUFSIZE);
#else
  ret = ipcc_register(&g_rzv_ipcc.lower);
#endif
  if (ret < 0)
    {
      return ret;
    }

  g_rzv_ipcc.registered = true;
  return OK;
}

#endif /* CONFIG_RZV_IPC_IPCC */
