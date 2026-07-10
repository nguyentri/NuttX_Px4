/****************************************************************************
 * arch/arm/src/rzv/rzv_ipc_raw.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Generic raw IPCC lower-half driver: MHU doorbell + SHM ring.
 *
 * Design:
 *   - One instance = one directional link (TX ring + RX ring in SHM).
 *   - TX ring: this core writes; peer reads.  Layout: first shm_size/2 bytes.
 *   - RX ring: peer writes; this core reads. Layout: second shm_size/2 bytes.
 *   - Ring header: 64-byte cacheline-padded struct (head/tail/mask/flags).
 *   - Entries follow the header contiguously.
 *   - Cache ops: up_clean_dcache before TX kick; up_invalidate_dcache in ISR.
 *   - TX-ACK timeout via nxsem_tickwait_uninterruptible (see desc.tx_ack_timeout_ms).
 *   - No malloc anywhere in driver lifetime.
 *
 * Concurrency model:
 * - TX: serialised per-instance via txlock mutex.
 *   - RX: single reader (task context). ISR posts rxsem; task drains ring.
 *   - TX-ACK: ISR posts txsem; task unblocks and returns to caller.
 *   - Ring indices (head/tail) are volatile uint32_t; dmb ish orders stores.
 *
 * Cycle-2 fixes applied:
 * — loopback ISR now posts both rxsem and txsem.
 * per-instance txlock mutex serialises concurrent writers.
 * txsem drained (reset to 0) before each MHU kick to prevent
 *             stale ACK false-match.
 * read() returns -EMSGSIZE when buflen < entry_size; head
 *             pointer is NOT advanced so the entry is not lost.
 * register() validates entry_size % RZV_CACHELINE_BYTES == 0.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#ifdef CONFIG_RZV_IPC_RAW

#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include <nuttx/arch.h>
#include <nuttx/cache.h>
#include <nuttx/clock.h>
#include <nuttx/ipcc.h>
#include <nuttx/mutex.h>
#include <nuttx/semaphore.h>

#include "rzv_ipc_raw.h"
#include "rzv_mhu_core.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Maximum simultaneously registered raw IPCC instances.
 * CR8↔CR8 + CR8↔CM33 + loopback = 3 maximum.
 */

#define RZV_IPC_RAW_MAX_INSTANCES   4u

/* ABI version written into ring header flags[7:0] */

#define RZV_IPC_RING_ABI_VER        0x01u

/* Cacheline size on Cortex-R8 / Cortex-M33 */

#define RZV_CACHELINE_BYTES         64u

/* Compile-time check: ring header must be exactly one cacheline */

#define RZV_IPC_RING_HDR_SIZE       64u

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* Ring header — exactly 64 bytes (one cacheline).
 * Placed at the start of each half of the SHM region.
 * MUST match the CM33 firmware ABI documented in rzv_ipc_channels.h.
 */

struct rzv_ipc_ring_hdr_s
{
  volatile uint32_t head;     /* consumer read index (mod mask+1)  */
  volatile uint32_t tail;     /* producer write index (mod mask+1) */
  volatile uint32_t mask;     /* ring_entries - 1                  */
  volatile uint32_t flags;    /* ABI version in bits[7:0]          */
  uint8_t           pad[48];  /* cacheline pad to 64 bytes total   */
};

_Static_assert(sizeof(struct rzv_ipc_ring_hdr_s) == RZV_IPC_RING_HDR_SIZE,
               "rzv_ipc_ring_hdr_s must be exactly 64 bytes");

/* Per-instance driver state — no dynamic allocation */

struct rzv_ipc_raw_s
{
  /* NuttX IPCC lower-half base (must be first — cast-compatible) */

  struct ipcc_lower_s            lower;

  /* Link descriptor (pointer; caller owns storage) */

  FAR const struct rzv_ipc_link_desc *desc;

  /* TX ring pointers (this side is producer) */

  FAR struct rzv_ipc_ring_hdr_s *tx_hdr;
  FAR uint8_t                   *tx_data;

  /* RX ring pointers (this side is consumer) */

  FAR struct rzv_ipc_ring_hdr_s *rx_hdr;
  FAR uint8_t                   *rx_data;

  /* Synchronization */

  mutex_t txlock;  /* serialise concurrent writers (one TX at a time) */
  sem_t   rxsem;   /* posted by rx_isr when new data arrives                 */
  sem_t   txsem;   /* posted by tx_ack_isr when peer ACKs                    */

  bool    in_use;
};

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Static instance pool — no heap allocation */

static struct rzv_ipc_raw_s g_rzv_ipc_raw_pool[RZV_IPC_RAW_MAX_INSTANCES];

/****************************************************************************
 * Private Helper — ring pointer arithmetic
 ****************************************************************************/

static inline uint32_t ring_next(uint32_t idx, uint32_t mask)
{
  return (idx + 1u) & mask;
}

static inline bool ring_full(FAR const struct rzv_ipc_ring_hdr_s *h)
{
  /* Full when tail+1 == head (one slot reserved) */

  return ring_next(h->tail, h->mask) == h->head;
}

static inline bool ring_empty(FAR const struct rzv_ipc_ring_hdr_s *h)
{
  return h->head == h->tail;
}

/* Byte offset of entry n within the data area */

static inline uint32_t entry_off(uint32_t idx, uint32_t mask,
                                  uint32_t entry_size)
{
  return (idx & mask) * entry_size;
}

/****************************************************************************
 * Name: rzv_ipc_raw_rx_isr
 *
 * Description:
 *   RX interrupt handler.  Called when peer writes to the TX channel and
 *   kicks our RX.  We invalidate the RX ring header so head/tail reads
 *   see coherent values, then post rxsem so the blocked reader can drain.
 *
 ****************************************************************************/

static int rzv_ipc_raw_rx_isr(int irq, FAR void *context, FAR void *arg)
{
  FAR struct rzv_ipc_raw_s *priv = arg;

  UNUSED(irq);
  UNUSED(context);

  /* Spurious check */

  if ((rzv_mhu_msg_sts(priv->desc->mhu_base,
                       priv->desc->rx_chan) & 1u) == 0)
    {
      return OK;
    }

  /* Invalidate RX ring header so we see fresh head/tail from peer.
   * Full entry invalidation happens in rzv_ipc_raw_read() before copy.
   */

  up_invalidate_dcache((uintptr_t)priv->rx_hdr,
                       (uintptr_t)priv->rx_hdr + RZV_IPC_RING_HDR_SIZE);

  /* Clear MHU interrupt before posting sem (avoids re-entry) */

  rzv_mhu_clear(priv->desc->mhu_base, priv->desc->rx_chan);

  nxsem_post(&priv->rxsem);

  return OK;
}

/****************************************************************************
 * Name: rzv_ipc_raw_tx_ack_isr
 *
 * Description:
 *   TX-ACK interrupt handler.  Called when peer writes to the RSP register
 *   of our TX channel, acknowledging receipt.  Post txsem to unblock
 *   the waiting writer.
 *
 ****************************************************************************/

static int rzv_ipc_raw_tx_ack_isr(int irq, FAR void *context, FAR void *arg)
{
  FAR struct rzv_ipc_raw_s *priv = arg;

  UNUSED(irq);
  UNUSED(context);

  if ((rzv_mhu_rsp_sts(priv->desc->mhu_base,
                       priv->desc->tx_chan) & 1u) == 0)
    {
      return OK;
    }

  rzv_mhu_rsp_clear(priv->desc->mhu_base, priv->desc->tx_chan);
  nxsem_post(&priv->txsem);

  return OK;
}

/****************************************************************************
 * Name: rzv_ipc_raw_loopback_isr
 *
 * Description:
 * combined ISR for loopback (tx_chan == rx_chan).
 *   A single channel's MSG interrupt fires for both the incoming data kick
 *   and, after the receiver ACKs via RSP, the TX-ACK.  This ISR checks
 *   both MSG and RSP status bits and posts the appropriate semaphore(s).
 *
 *   Sequence:
 *     1. Writer kicks MSG → ISR fires, MSG bit set → post rxsem.
 *     2. Reader handles RX, writes RSP ACK via rzv_mhu_ack().
 *     3. ISR fires again, RSP bit set → post txsem (unblocks writer).
 *
 ****************************************************************************/

static int rzv_ipc_raw_loopback_isr(int irq, FAR void *context,
                                     FAR void *arg)
{
  FAR struct rzv_ipc_raw_s *priv = arg;
  uint32_t                  chan  = priv->desc->rx_chan;  /* tx_chan == rx_chan */

  UNUSED(irq);
  UNUSED(context);

  /* Check MSG (incoming data kick) */

  if ((rzv_mhu_msg_sts(priv->desc->mhu_base, chan) & 1u) != 0)
    {
      up_invalidate_dcache((uintptr_t)priv->rx_hdr,
                           (uintptr_t)priv->rx_hdr + RZV_IPC_RING_HDR_SIZE);
      rzv_mhu_clear(priv->desc->mhu_base, chan);
      nxsem_post(&priv->rxsem);
    }

  /* Check RSP (TX-ACK from same-channel loopback receiver) */

  if ((rzv_mhu_rsp_sts(priv->desc->mhu_base, chan) & 1u) != 0)
    {
      rzv_mhu_rsp_clear(priv->desc->mhu_base, chan);
      nxsem_post(&priv->txsem);
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_ipc_raw_read
 *
 * Description:
 *   Lower-half read op.  Non-blocking: returns 0 if ring is empty.
 *   Copies exactly entry_size bytes from the next ring entry.
 *
 * if buflen < entry_size, return -EMSGSIZE without advancing
 *   head — the entry is preserved for a retry with a large-enough buffer.
 *   This is consistent with SOCK_DGRAM semantics used by NuttX IPCC.
 *
 ****************************************************************************/

static ssize_t rzv_ipc_raw_read(FAR struct ipcc_lower_s *lower,
                                 FAR char *buffer, size_t buflen)
{
  FAR struct rzv_ipc_raw_s *priv =
    (FAR struct rzv_ipc_raw_s *)lower;
  FAR const struct rzv_ipc_link_desc *d = priv->desc;
  uint32_t head;
  uintptr_t src;

  /* Invalidate RX ring header before reading indices */

  up_invalidate_dcache((uintptr_t)priv->rx_hdr,
                       (uintptr_t)priv->rx_hdr + RZV_IPC_RING_HDR_SIZE);

  if (ring_empty(priv->rx_hdr))
    {
      return 0;
    }

  /* reject undersized buffer; leave head intact so entry survives */

  if (buflen < d->entry_size)
    {
      return -EMSGSIZE;
    }

  /* Validate peer-supplied head index before use */

  head = priv->rx_hdr->head & priv->rx_hdr->mask;

  src  = (uintptr_t)priv->rx_data + entry_off(head, priv->rx_hdr->mask,
                                               d->entry_size);

  /* Invalidate entry payload */

  up_invalidate_dcache(src, src + d->entry_size);

  memcpy(buffer, (FAR void *)src, d->entry_size);

  /* Advance head with memory barrier so peer sees updated value */

  priv->rx_hdr->head = (head + 1u) & priv->rx_hdr->mask;
  __asm__ __volatile__("dmb ish" : : : "memory");

  /* Clean updated head back to memory */

  up_clean_dcache((uintptr_t)priv->rx_hdr,
                  (uintptr_t)priv->rx_hdr + RZV_IPC_RING_HDR_SIZE);

  /* ACK to peer via RSP channel */

  rzv_mhu_ack(d->mhu_base, d->rx_chan, 1u);

  return (ssize_t)d->entry_size;
}

/****************************************************************************
 * Name: rzv_ipc_raw_write
 *
 * Description:
 *   Lower-half write op.  Enqueues one entry if TX ring has space, kicks
 *   peer via MHU, then waits for TX-ACK with timeout.
 *   Returns -EAGAIN if ring full, -ETIMEDOUT if ACK not received in time.
 *
 * entire TX critical section is guarded by txlock mutex to
 *              prevent concurrent writers racing on tail.
 * txsem is reset to 0 before the MHU kick so a stale ACK
 *              from a previous send cannot masquerade as the current ACK.
 *
 ****************************************************************************/

static ssize_t rzv_ipc_raw_write(FAR struct ipcc_lower_s *lower,
                                  FAR const char *buffer, size_t buflen)
{
  FAR struct rzv_ipc_raw_s *priv =
    (FAR struct rzv_ipc_raw_s *)lower;
  FAR const struct rzv_ipc_link_desc *d = priv->desc;
  uint32_t tail;
  uint32_t copy;
  uintptr_t dst;
  int       ret;

  /* serialise concurrent writers */

  ret = nxmutex_lock(&priv->txlock);
  if (ret < 0)
    {
      return ret;
    }

  /* Invalidate TX ring header to read fresh peer-consumed head */

  up_invalidate_dcache((uintptr_t)priv->tx_hdr,
                       (uintptr_t)priv->tx_hdr + RZV_IPC_RING_HDR_SIZE);

  if (ring_full(priv->tx_hdr))
    {
      nxmutex_unlock(&priv->txlock);
      return -EAGAIN;
    }

  tail = priv->tx_hdr->tail & priv->tx_hdr->mask;
  copy = (buflen < d->entry_size) ? (uint32_t)buflen : d->entry_size;
  dst  = (uintptr_t)priv->tx_data + entry_off(tail, priv->tx_hdr->mask,
                                               d->entry_size);

  memcpy((FAR void *)dst, buffer, copy);

  /* Zero-pad remainder of entry to avoid stale data leaks */

  if (copy < d->entry_size)
    {
      memset((FAR void *)(dst + copy), 0, d->entry_size - copy);
    }

  /* Clean entry payload to memory before advancing tail */

  up_clean_dcache(dst, dst + d->entry_size);

  /* Advance tail */

  priv->tx_hdr->tail = (tail + 1u) & priv->tx_hdr->mask;
  __asm__ __volatile__("dmb ish" : : : "memory");

  /* Clean updated tail to memory */

  up_clean_dcache((uintptr_t)priv->tx_hdr,
                  (uintptr_t)priv->tx_hdr + RZV_IPC_RING_HDR_SIZE);

  /* drain stale ACKs before kick so we wait for the real ACK */

  nxsem_reset(&priv->txsem, 0);

  /* Kick peer */

  rzv_mhu_send(d->mhu_base, d->tx_chan, 1u);

  /* Wait for TX-ACK from peer */

  if (d->tx_ack_timeout_ms == 0)
    {
      ret = nxsem_wait_uninterruptible(&priv->txsem);
    }
  else
    {
      ret = nxsem_tickwait_uninterruptible(&priv->txsem,
              MSEC2TICK(d->tx_ack_timeout_ms));
    }

  nxmutex_unlock(&priv->txlock);

  if (ret == -ETIMEDOUT)
    {
      return -ETIMEDOUT;
    }

  if (ret < 0)
    {
      return ret;
    }

  return (ssize_t)copy;
}

/****************************************************************************
 * Name: rzv_ipc_raw_cleanup
 ****************************************************************************/

static int rzv_ipc_raw_cleanup(FAR struct ipcc_lower_s *lower)
{
  FAR struct rzv_ipc_raw_s *priv =
    (FAR struct rzv_ipc_raw_s *)lower;

  /* Detach interrupts */

  up_disable_irq(priv->desc->rx_irq);
  irq_detach(priv->desc->rx_irq);

  /* Only detach TX-ACK IRQ if different from RX (non-loopback) */

  if (priv->desc->tx_irq != priv->desc->rx_irq)
    {
      up_disable_irq(priv->desc->tx_irq);
      irq_detach(priv->desc->tx_irq);
    }

  nxmutex_destroy(&priv->txlock);
  nxsem_destroy(&priv->rxsem);
  nxsem_destroy(&priv->txsem);

  priv->in_use = false;
  return OK;
}

/* Lower-half ops table — non-buffered path only.
 * The raw driver does not use CONFIG_IPCC_BUFFERED because it manages its
 * own ring; the upper half's circbuf would add needless double-copy.
 */

static const struct ipcc_ops_s g_rzv_ipc_raw_ops =
{
  .read         = rzv_ipc_raw_read,
  .write        = rzv_ipc_raw_write,
  .cleanup      = rzv_ipc_raw_cleanup,

  /* buffer_data and write_notify intentionally NULL:
   * raw driver manages its own SHM ring; buffered path not used.
   * TODO(IPC-NEXT): add buffered path if upper-half poll semantics
   *                 require circbuf integration.
   */

  .buffer_data  = NULL,
  .write_notify = NULL,
};

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_ipc_raw_register
 ****************************************************************************/

int rzv_ipc_raw_register(FAR const char *path,
                          FAR const struct rzv_ipc_link_desc *desc)
{
  FAR struct rzv_ipc_raw_s *priv = NULL;
  uint32_t half;
  int      ret;
  uint32_t i;

  /* Validate descriptor */

  if (path == NULL || desc == NULL)
    {
      return -EINVAL;
    }

  if (desc->ring_entries == 0 ||
      (desc->ring_entries & (desc->ring_entries - 1)) != 0)
    {
      return -EINVAL;  /* ring_entries must be power of two */
    }

  if (desc->entry_size == 0 || desc->shm_size == 0)
    {
      return -EINVAL;
    }

  /* entry_size must be an integer multiple of the cacheline size.
   * Sub-cacheline cache ops can clobber adjacent entries' dirty state.
   */

  if ((desc->entry_size & (RZV_CACHELINE_BYTES - 1u)) != 0)
    {
      return -EINVAL;  /* entry_size must be cacheline-aligned */
    }

  /* Allocate from static pool */

  for (i = 0; i < RZV_IPC_RAW_MAX_INSTANCES; i++)
    {
      if (!g_rzv_ipc_raw_pool[i].in_use)
        {
          priv = &g_rzv_ipc_raw_pool[i];
          break;
        }
    }

  if (priv == NULL)
    {
      return -ENOMEM;
    }

  /* Wire descriptor and compute ring pointers.
   * SHM layout: [low half: ring hdr (64B) | entries] [high half: hdr | entries].
   * Each half = shm_size / 2.  The two cores share one shm_base, so the
   * responder must mirror the halves: the initiator's TX (low) is the
   * responder's RX, and vice versa.  Without this swap both cores would
   * write the low half and read the high half, so no data would cross.
   * The loopback descriptor uses initiator=true and is unaffected.
   */

  half = desc->shm_size / 2u;

  priv->desc = desc;

  {
    uintptr_t lo = (uintptr_t)desc->shm_base;
    uintptr_t hi = (uintptr_t)desc->shm_base + half;
    uintptr_t tx = desc->initiator ? lo : hi;
    uintptr_t rx = desc->initiator ? hi : lo;

    priv->tx_hdr  = (FAR struct rzv_ipc_ring_hdr_s *)tx;
    priv->tx_data = (FAR uint8_t *)(tx + RZV_IPC_RING_HDR_SIZE);
    priv->rx_hdr  = (FAR struct rzv_ipc_ring_hdr_s *)rx;
    priv->rx_data = (FAR uint8_t *)(rx + RZV_IPC_RING_HDR_SIZE);
  }

  /* Initiator zeros ring headers so both sides start from a known state.
   * Responder must NOT zero — it would clobber initiator's setup.
   *
   * BOOT-ORDER CONTRACT: the initiator (CR8_0 for Link 1; CR8_1 for Link 3)
   * must run rzv_ipc_raw_register() before its responder peer issues the first
   * read()/write(), otherwise the responder reads an uninitialised ring `mask`.
   * This holds today via boot order (CR8_0 → CR8_1 → CM33). There is no
   * handshake flag; if that ordering ever changes, add a responder spin on
   * rx_hdr->flags == RZV_IPC_RING_ABI_VER before first use.
   */

  if (desc->initiator)
    {
      memset((FAR void *)priv->tx_hdr, 0, RZV_IPC_RING_HDR_SIZE);
      memset((FAR void *)priv->rx_hdr, 0, RZV_IPC_RING_HDR_SIZE);

      priv->tx_hdr->mask  = desc->ring_entries - 1u;
      priv->tx_hdr->flags = RZV_IPC_RING_ABI_VER;
      priv->rx_hdr->mask  = desc->ring_entries - 1u;
      priv->rx_hdr->flags = RZV_IPC_RING_ABI_VER;

      __asm__ __volatile__("dmb ish" : : : "memory");

      up_clean_dcache((uintptr_t)priv->tx_hdr,
                      (uintptr_t)priv->tx_hdr + RZV_IPC_RING_HDR_SIZE);
      up_clean_dcache((uintptr_t)priv->rx_hdr,
                      (uintptr_t)priv->rx_hdr + RZV_IPC_RING_HDR_SIZE);
    }
  else
    {
      /* Responder: just invalidate so we read peer-initialised values */

      up_invalidate_dcache((uintptr_t)priv->tx_hdr,
                           (uintptr_t)priv->tx_hdr + RZV_IPC_RING_HDR_SIZE);
      up_invalidate_dcache((uintptr_t)priv->rx_hdr,
                           (uintptr_t)priv->rx_hdr + RZV_IPC_RING_HDR_SIZE);
    }

  /* init per-instance TX mutex */

  nxmutex_init(&priv->txlock);

  /* Semaphores — initialise to 0 (waiter blocks until ISR posts) */

  nxsem_init(&priv->rxsem, 0, 0);
  nxsem_init(&priv->txsem, 0, 0);

  /* Attach ISRs.
   *
   * two sub-cases for the loopback configuration:
   *
   *   (a) tx_chan == rx_chan AND tx_irq == rx_irq (old single-vector design):
   *       Use the combined loopback ISR which checks both MSG and RSP bits on
   *       each invocation.  This handles hardware where MSG and RSP share a
   *       GIC line.
   *
   *   (b) tx_chan == rx_chan AND tx_irq != rx_irq (current loopback on ch16):
   *       MSG and RSP are routed to separate GIC SPIs even though the same
   *       channel is used for TX and RX.  Use the normal two-ISR path —
   *       rx_irq (MSG, post rxsem) and tx_irq (RSP, post txsem) are wired
   *       independently.
   *
   *   (c) tx_chan != rx_chan (normal two-channel link): standard two-ISR path.
   *
   * Cleanup mirrors the same tx_irq==rx_irq test in rzv_ipc_raw_cleanup().
   */

  if (desc->tx_irq == desc->rx_irq)
    {
      /* Case (a): single GIC line for both MSG and RSP — combined ISR */

      ret = rzv_mhu_attach_isr(desc->rx_irq, rzv_ipc_raw_loopback_isr, priv);
      if (ret < 0)
        {
          goto err_sem;
        }
    }
  else
    {
      /* Cases (b) and (c): separate RX (MSG) and TX-ACK (RSP) ISRs */

      ret = rzv_mhu_attach_isr(desc->rx_irq, rzv_ipc_raw_rx_isr, priv);
      if (ret < 0)
        {
          goto err_sem;
        }

      ret = rzv_mhu_attach_isr(desc->tx_irq, rzv_ipc_raw_tx_ack_isr, priv);
      if (ret < 0)
        {
          up_disable_irq(desc->rx_irq);
          irq_detach(desc->rx_irq);
          goto err_sem;
        }
    }

  /* Wire lower-half ops */

  priv->lower.ops  = g_rzv_ipc_raw_ops;
  priv->lower.chan = (int)(desc->tx_chan);

  /* Register with IPCC upper half.
   * When CONFIG_IPCC_BUFFERED is set globally (inherited from the CA55
   * rptun path), ipcc_register() takes rxbuflen + txbuflen args.  The raw
   * driver manages its own SHM ring so we pass 0-byte buffers here; the
   * upper-half circbuf is unused because buffer_data / write_notify are NULL.
   *
   * TODO(IPC-NEXT): decouple ipcc-multi from IPCC_BUFFERED so that raw
   *                 links can select the non-buffered registration path.
   */

#ifdef CONFIG_IPCC_BUFFERED
  ret = ipcc_register(&priv->lower, 0, 0);
#else
  ret = ipcc_register(&priv->lower);
#endif
  if (ret < 0)
    {
      up_disable_irq(desc->rx_irq);
      irq_detach(desc->rx_irq);
      if (desc->tx_irq != desc->rx_irq)
        {
          up_disable_irq(desc->tx_irq);
          irq_detach(desc->tx_irq);
        }

      goto err_mutex_sem;
    }

  priv->in_use = true;
  return OK;

err_sem:
  nxmutex_destroy(&priv->txlock);
err_mutex_sem:
  nxsem_destroy(&priv->rxsem);
  nxsem_destroy(&priv->txsem);
  return ret;
}

#endif /* CONFIG_RZV_IPC_RAW */
