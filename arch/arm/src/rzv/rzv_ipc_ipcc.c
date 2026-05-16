/****************************************************************************
 * arch/arm/src/rzv/rzv_ipc_ipcc.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 ****************************************************************************/

#include <nuttx/config.h>

#ifdef CONFIG_RZV_IPC_IPCC

#include <errno.h>
#include <stdbool.h>
#include <string.h>

#include <nuttx/ipcc.h>
#include <nuttx/mm/circbuf.h>

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

static void rzv_ipcc_rxnotify(FAR void *arg)
{
  FAR struct rzv_ipcc_state_s *priv = arg;

  if (priv->lower.upper != NULL)
    {
      ipcc_rxfree_notify(priv->lower.upper);
    }
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
#endif

static int rzv_ipcc_cleanup(FAR struct ipcc_lower_s *ipcc)
{
  UNUSED(ipcc);
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
