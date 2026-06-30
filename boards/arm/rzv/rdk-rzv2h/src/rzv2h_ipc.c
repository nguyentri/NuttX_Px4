/****************************************************************************
 * boards/arm/rzv/rdk-rzv2h/src/rzv2h_ipc.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Board-level IPC initialisation for RDK-RZ/V2H.
 *
 * Three inter-core links, enabled independently by Kconfig:
 *
 *   /dev/ipcc0  — CR8↔CA55 via rptun/OpenAMP  (CONFIG_RZV_OPENAMP)
 *   /dev/ipcc1  — CR8_0↔CR8_1 raw MHU+SHM    (CONFIG_RZV_IPC_CR8_CR8)
 *   /dev/ipcc2  — CR8_0↔CM33  raw MHU+SHM    (CONFIG_RZV_IPC_CR8_CM33)
 *   /dev/ipccLB — CR8_0 self-loopback         (CONFIG_RZV_IPC_CR8_CR8_LOOPBACK)
 *
 * The existing CA55 rptun path (/dev/ipcc0) is UNCHANGED.
 * Raw links are additive; their Kconfig symbols are absent from :ipcc
 * and :nsh defconfigs, so those builds remain byte-identical.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#if defined(CONFIG_RZV_OPENAMP) || defined(CONFIG_RZV_IPC_RAW)

#include <errno.h>
#include <syslog.h>

#include "rdk-rzv2h.h"
#include "rzv_ipc.h"

#ifdef CONFIG_RZV_IPC_RAW
#  include "rzv_ipc_raw.h"
#  include "rzv_ipc_channels.h"
#endif

/****************************************************************************
 * Private Data — raw link descriptors (static const; no heap)
 ****************************************************************************/

#ifdef CONFIG_RZV_IPC_CR8_CR8
static const struct rzv_ipc_link_desc g_cr8_cr8_desc =
{
  .mhu_base          = RZV_IPC_CR8CR8_MHU_BASE,
#  ifdef CONFIG_RZV_IPC_ROLE_INITIATOR
  /* Initiator (CR8_0): TX kicks ch4, RX listens on ch9. */
  .tx_chan           = RZV_IPC_CR8CR8_TX_CHAN,
  .rx_chan           = RZV_IPC_CR8CR8_RX_CHAN,
  .tx_irq            = RZV_IPC_CR8CR8_TX_IRQ,
  .rx_irq            = RZV_IPC_CR8CR8_RX_IRQ,
  .initiator         = true,
#  else
  /* Responder (CR8_1): mirror — TX kicks ch9, RX listens on ch4, and IRQs
   * swap accordingly. The driver mirrors the SHM ring halves for the
   * responder, so TX/RX rings line up with the initiator.
   */
  .tx_chan           = RZV_IPC_CR8CR8_RX_CHAN,
  .rx_chan           = RZV_IPC_CR8CR8_TX_CHAN,
  .tx_irq            = RZV_IPC_CR8CR8_RESP_TX_IRQ,
  .rx_irq            = RZV_IPC_CR8CR8_RESP_RX_IRQ,
  .initiator         = false,
#  endif
  .shm_base          = RZV_IPC_CR8CR8_SHM_BASE,
  .shm_size          = RZV_IPC_CR8CR8_SHM_SIZE,
  .ring_entries      = RZV_IPC_CR8CR8_RING_ENTRIES,
  .entry_size        = RZV_IPC_CR8CR8_RING_ENTRY_SZ,
  /* CR8↔CR8: both cores trusted; no TX-ACK timeout needed.
   * Use the global CONFIG_RZV_IPC_TX_TIMEOUT_MS (may be 0 = infinite).
   */
  .tx_ack_timeout_ms = CONFIG_RZV_IPC_TX_TIMEOUT_MS,
};
#endif /* CONFIG_RZV_IPC_CR8_CR8 */

#ifdef CONFIG_RZV_IPC_CR8_CM33
static const struct rzv_ipc_link_desc g_cr8_cm33_desc =
{
  .mhu_base          = RZV_IPC_CR8CM33_MHU_BASE,
  .tx_chan           = RZV_IPC_CR8CM33_TX_CHAN,
  .rx_chan           = RZV_IPC_CR8CM33_RX_CHAN,
  .tx_irq            = RZV_IPC_CR8CM33_TX_IRQ,
  .rx_irq            = RZV_IPC_CR8CM33_RX_IRQ,
  .shm_base          = RZV_IPC_CR8CM33_SHM_BASE,
  .shm_size          = RZV_IPC_CR8CM33_SHM_SIZE,
  .ring_entries      = RZV_IPC_CR8CM33_RING_ENTRIES,
  .entry_size        = RZV_IPC_CR8CM33_RING_ENTRY_SZ,
  .initiator         = true,   /* CR8_0 is always initiator for CM33 link */

  /* CM33 firmware may be absent; mandatory TX-ACK timeout.
   * Use global Kconfig value; must not be 0 for this link — if someone
   * sets CONFIG_RZV_IPC_TX_TIMEOUT_MS=0, clamp to 100 ms here.
   */
  .tx_ack_timeout_ms = (CONFIG_RZV_IPC_TX_TIMEOUT_MS > 0)
                         ? CONFIG_RZV_IPC_TX_TIMEOUT_MS : 100u,
};
#endif /* CONFIG_RZV_IPC_CR8_CM33 */

#ifdef CONFIG_RZV_IPC_CR8_1_CM33
/* ESC relay leg: CR8_1 (initiator) ↔ CM33 (responder), /dev/ipcc3. */
static const struct rzv_ipc_link_desc g_cr8_1_cm33_desc =
{
  .mhu_base          = RZV_IPC_CR8_1_CM33_MHU_BASE,
#ifdef CONFIG_RZV2H_BUILD_CM33
  /* CM33 = responder: mirror channels/IRQs. The driver mirrors the SHM ring
   * halves for the responder (initiator=false), so TX/RX line up with CR8_1.
   */
  .tx_chan           = RZV_IPC_CR8_1_CM33_RX_CHAN,   /* ch22: CM33 → CR8_1 */
  .rx_chan           = RZV_IPC_CR8_1_CM33_TX_CHAN,   /* ch21: CR8_1 → CM33 */
  .tx_irq            = RZV_IPC_CR8_1_CM33_RESP_TX_IRQ,
  .rx_irq            = RZV_IPC_CR8_1_CM33_RESP_RX_IRQ,
  .initiator         = false,
#else
  /* CR8_1 = initiator: TX kicks ch21, RX listens on ch22. */
  .tx_chan           = RZV_IPC_CR8_1_CM33_TX_CHAN,   /* ch21: CR8_1 → CM33 */
  .rx_chan           = RZV_IPC_CR8_1_CM33_RX_CHAN,   /* ch22: CM33 → CR8_1 */
  .tx_irq            = RZV_IPC_CR8_1_CM33_TX_IRQ,
  .rx_irq            = RZV_IPC_CR8_1_CM33_RX_IRQ,
  .initiator         = true,
#endif
  .shm_base          = RZV_IPC_CR8_1_CM33_SHM_BASE,
  .shm_size          = RZV_IPC_CR8_1_CM33_SHM_SIZE,
  .ring_entries      = RZV_IPC_CR8_1_CM33_RING_ENTRIES,
  .entry_size        = RZV_IPC_CR8_1_CM33_RING_ENTRY_SZ,

  /* CM33 firmware may be absent (from CR8_1's view); mandatory TX-ACK
   * timeout (clamp 0 → 100 ms).
   */
  .tx_ack_timeout_ms = (CONFIG_RZV_IPC_TX_TIMEOUT_MS > 0)
                         ? CONFIG_RZV_IPC_TX_TIMEOUT_MS : 100u,
};
#endif /* CONFIG_RZV_IPC_CR8_1_CM33 */

#ifdef CONFIG_RZV_IPC_CR8_CR8_LOOPBACK
static const struct rzv_ipc_link_desc g_cr8_loopback_desc =
{
  .mhu_base          = RZV_IPC_LOOPBACK_MHU_BASE,
  .tx_chan           = RZV_IPC_LOOPBACK_TX_CHAN,
  .rx_chan           = RZV_IPC_LOOPBACK_RX_CHAN,
  .tx_irq            = RZV_IPC_LOOPBACK_TX_IRQ,
  .rx_irq            = RZV_IPC_LOOPBACK_RX_IRQ,
  .shm_base          = RZV_IPC_LOOPBACK_SHM_BASE,
  .shm_size          = RZV_IPC_LOOPBACK_SHM_SIZE,
  .ring_entries      = RZV_IPC_LOOPBACK_RING_ENTRIES,
  .entry_size        = RZV_IPC_LOOPBACK_RING_ENTRY_SZ,
  .initiator         = true,
  .tx_ack_timeout_ms = CONFIG_RZV_IPC_TX_TIMEOUT_MS,
};
#endif /* CONFIG_RZV_IPC_CR8_CR8_LOOPBACK */

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_ipc_initialize
 *
 * Description:
 *   Called from rzv2h_bringup.c late-init.  Registers all enabled IPC
 *   devices in order: CA55 rptun first (established convention), then
 *   raw links.
 *
 ****************************************************************************/

int board_ipc_initialize(void)
{
  int ret;

  /* --- Link 0: CA55 ↔ CR8 rptun/OpenAMP (/dev/ipcc0) --- */

#ifdef CONFIG_RZV_OPENAMP
  ret = rzv_ipc_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: RZ/V2H IPC init failed: %d\n", ret);
      return ret;
    }

#  ifdef CONFIG_RZV_IPC_IPCC
  ret = rzv_ipcc_initialize();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: RZ/V2H IPCC init failed: %d\n", ret);
      return ret;
    }

  syslog(LOG_INFO, "RZ/V2H IPCC registered at /dev/ipcc0\n");
#  endif
#endif /* CONFIG_RZV_OPENAMP */

  /* --- Link 1: CR8_0 ↔ CR8_1 raw IPCC (/dev/ipcc1) --- */

#ifdef CONFIG_RZV_IPC_CR8_CR8
  ret = rzv_ipc_raw_register("/dev/ipcc1", &g_cr8_cr8_desc);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: CR8↔CR8 IPCC init failed: %d\n", ret);
      return ret;
    }

  syslog(LOG_INFO, "RZ/V2H raw IPCC registered at /dev/ipcc1 (CR8↔CR8, %s)\n",
#  ifdef CONFIG_RZV_IPC_ROLE_INITIATOR
         "initiator"
#  else
         "responder"
#  endif
        );
#endif /* CONFIG_RZV_IPC_CR8_CR8 */

  /* --- Link 2: CR8_0 ↔ CM33 raw IPCC (/dev/ipcc2) --- */

#ifdef CONFIG_RZV_IPC_CR8_CM33
  ret = rzv_ipc_raw_register("/dev/ipcc2", &g_cr8_cm33_desc);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: CR8↔CM33 IPCC init failed: %d\n", ret);
      return ret;
    }

  syslog(LOG_INFO,
         "RZ/V2H raw IPCC registered at /dev/ipcc2 (CR8-CM33, "
         "TX timeout %lu ms)\n",
         (unsigned long)g_cr8_cm33_desc.tx_ack_timeout_ms);
#endif /* CONFIG_RZV_IPC_CR8_CM33 */

  /* --- Link 3: CR8_1 ↔ CM33 raw IPCC (/dev/ipcc3, ESC relay leg) --- */

#ifdef CONFIG_RZV_IPC_CR8_1_CM33
  ret = rzv_ipc_raw_register("/dev/ipcc3", &g_cr8_1_cm33_desc);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: CR8_1↔CM33 IPCC init failed: %d\n", ret);
      return ret;
    }

  syslog(LOG_INFO,
         "RZ/V2H raw IPCC registered at /dev/ipcc3 (CR8_1-CM33, "
         "TX timeout %lu ms)\n",
         (unsigned long)g_cr8_1_cm33_desc.tx_ack_timeout_ms);
#endif /* CONFIG_RZV_IPC_CR8_1_CM33 */

  /* --- Loopback: CR8_0 self-test (/dev/ipccLB) --- */

#ifdef CONFIG_RZV_IPC_CR8_CR8_LOOPBACK
  ret = rzv_ipc_raw_register("/dev/ipccLB", &g_cr8_loopback_desc);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: CR8 loopback IPCC init failed: %d\n", ret);
      return ret;
    }

  syslog(LOG_INFO, "RZ/V2H raw IPCC registered at /dev/ipccLB (loopback)\n");
#endif /* CONFIG_RZV_IPC_CR8_CR8_LOOPBACK */

  return 0;
}

#endif /* CONFIG_RZV_OPENAMP || CONFIG_RZV_IPC_RAW */
