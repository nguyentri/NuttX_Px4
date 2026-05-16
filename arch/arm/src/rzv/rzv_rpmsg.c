/****************************************************************************
 * arch/arm/src/rzv/rzv_rpmsg.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 ****************************************************************************/

#include <nuttx/config.h>

#ifdef CONFIG_RZV_OPENAMP

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <nuttx/irq.h>
#include <nuttx/rptun/openamp.h>
#include <openamp/rpmsg.h>

#include "rzv_openamp.h"
#include "rzv_rpmsg.h"

#ifndef CONFIG_RZV_RPMSG_RX_QUEUE_DEPTH
#  define CONFIG_RZV_RPMSG_RX_QUEUE_DEPTH 8
#endif

struct rzv_rpmsg_packet_s
{
  uint16_t len;
  uint16_t pos;
  char data[RZV_OPENAMP_RPMSG_BUFFER_SIZE];
};

struct rzv_rpmsg_state_s
{
  struct rpmsg_endpoint ept;
  struct rzv_rpmsg_packet_s rx[CONFIG_RZV_RPMSG_RX_QUEUE_DEPTH];
  rzv_rpmsg_rxnotify_t rxnotify;
  FAR void *rxarg;
  uint8_t head;
  uint8_t tail;
  bool ready;
};

static struct rzv_rpmsg_state_s g_rpmsg;

static uint8_t rzv_rpmsg_next(uint8_t index)
{
  return (uint8_t)((index + 1) % CONFIG_RZV_RPMSG_RX_QUEUE_DEPTH);
}

static int rzv_rpmsg_ept_cb(FAR struct rpmsg_endpoint *ept, FAR void *data,
                            size_t len, uint32_t src, FAR void *priv)
{
  FAR struct rzv_rpmsg_state_s *state = priv;
  irqstate_t flags;
  uint8_t next;

  UNUSED(ept);
  UNUSED(src);

  if (len > RZV_OPENAMP_RPMSG_BUFFER_SIZE)
    {
      return -EMSGSIZE;
    }

  flags = enter_critical_section();
  next = rzv_rpmsg_next(state->head);
  if (next == state->tail)
    {
      leave_critical_section(flags);
      return -ENOMEM;
    }

  memcpy(state->rx[state->head].data, data, len);
  state->rx[state->head].len = len;
  state->rx[state->head].pos = 0;
  state->head = next;
  leave_critical_section(flags);

  if (state->rxnotify != NULL)
    {
      state->rxnotify(state->rxarg);
    }

  return 0;
}

static void rzv_rpmsg_device_created(FAR struct rpmsg_device *rdev,
                                     FAR void *priv)
{
  FAR struct rzv_rpmsg_state_s *state = priv;

  state->ept.priv = state;
  if (rpmsg_create_ept(&state->ept, rdev, RZV_OPENAMP_RPC_EPT_NAME,
                       RZV_OPENAMP_APP_EPT_ADDR, RPMSG_ADDR_ANY,
                       rzv_rpmsg_ept_cb, NULL) == 0)
    {
      state->ready = true;
    }
}

static void rzv_rpmsg_device_destroy(FAR struct rpmsg_device *rdev,
                                     FAR void *priv)
{
  FAR struct rzv_rpmsg_state_s *state = priv;

  UNUSED(rdev);

  if (state->ready)
    {
      rpmsg_destroy_ept(&state->ept);
      state->ready = false;
    }
}

int rzv_rpmsg_initialize(rzv_rpmsg_rxnotify_t rxnotify, FAR void *arg)
{
  memset(&g_rpmsg, 0, sizeof(g_rpmsg));
  g_rpmsg.rxnotify = rxnotify;
  g_rpmsg.rxarg = arg;

  return rpmsg_register_callback(&g_rpmsg, rzv_rpmsg_device_created,
                                 rzv_rpmsg_device_destroy, NULL, NULL);
}

/****************************************************************************
 * Name: rzv_rpmsg_detach
 *
 * Description:
 *   Idempotent teardown: destroy the endpoint if live, then unregister the
 *   rpmsg device watcher.  Must be called with g_rzv_ipcc_lock held
 *   (see rzv_ipc_ipcc.c).  Uses the identical 4-arg tuple as
 *   rzv_rpmsg_initialize() to guarantee symmetry (IPC-API-001).
 *
 ****************************************************************************/

void rzv_rpmsg_detach(void)
{
  if (g_rpmsg.ready)
    {
      rpmsg_destroy_ept(&g_rpmsg.ept);
      g_rpmsg.ready = false;
    }

  rpmsg_unregister_callback(&g_rpmsg, rzv_rpmsg_device_created,
                            rzv_rpmsg_device_destroy, NULL, NULL);
}

bool rzv_rpmsg_ready(void)
{
  return g_rpmsg.ready;
}

ssize_t rzv_rpmsg_send(FAR const char *buffer, size_t buflen)
{
  int ret;

  if (buffer == NULL || buflen == 0)
    {
      return 0;
    }

  if (buflen > RZV_OPENAMP_RPMSG_BUFFER_SIZE)
    {
      return -EMSGSIZE;
    }

  if (!g_rpmsg.ready)
    {
      return -ENODEV;
    }

  ret = rpmsg_trysend(&g_rpmsg.ept, buffer, buflen);
  if (ret < 0)
    {
      return ret;
    }

  return buflen;
}

ssize_t rzv_rpmsg_receive(FAR char *buffer, size_t buflen)
{
  FAR struct rzv_rpmsg_packet_s *packet;
  irqstate_t flags;
  size_t nread;

  if (buffer == NULL || buflen == 0)
    {
      return 0;
    }

  flags = enter_critical_section();
  if (g_rpmsg.tail == g_rpmsg.head)
    {
      leave_critical_section(flags);
      return 0;
    }

  packet = &g_rpmsg.rx[g_rpmsg.tail];
  nread = packet->len - packet->pos;
  if (nread > buflen)
    {
      nread = buflen;
    }

  memcpy(buffer, &packet->data[packet->pos], nread);
  packet->pos += nread;
  if (packet->pos >= packet->len)
    {
      g_rpmsg.tail = rzv_rpmsg_next(g_rpmsg.tail);
    }

  leave_critical_section(flags);
  return nread;
}

#endif /* CONFIG_RZV_OPENAMP */
