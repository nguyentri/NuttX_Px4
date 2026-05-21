/****************************************************************************
 * arch/arm/src/rzv/rzv_openamp.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Phase 01: single resource table, vring stride 0x100000, dcache clean.
 * Phase 03: rptun device registration (ops + rptun_initialize call).
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#ifdef CONFIG_RZV_OPENAMP

#include <errno.h>
#include <string.h>

#include <nuttx/cache.h>
#include <nuttx/rptun/rptun.h>

#include "rzv_openamp.h"
#include "rzv_rpmsg.h"
#include "rzv_rproc.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* OpenAMP resource type code used in the resource table. */

#define RSC_VDEV       3u  /* VIRTIO_DEV entry — the only entry we advertise */

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* Single resource table for one vdev with two vrings.
 * Layout uses struct rptun_rsc_s from NuttX rptun.h directly.
 *
 * We advertise num=1 with a single offset pointing at rpmsg_vdev.
 * Layout intent (rsc_table.c option-a):
 * the log_trace slot in rptun_rsc_s is at a lower offset but is NOT
 * referenced by any offset[] entry, so the CA55 OpenAMP parser never
 * touches it.  This avoids a zeroed RSC_CARVEOUT (type=0) being parsed
 * when offset[0] pointed at log_trace (C2 fix).
 *
 * An RSC_RPROC_MEM entry is omitted: rptun_rsc_s has no rproc_mem
 * field (slave-only, CA55 owns memory).
 *   offset[0] = offsetof(rptun_rsc_s, rpmsg_vdev)  — the single vdev entry
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* Resource table pinned to OPENAMP_RSCTBL region (@0x42F00000).
 * The .resource_table section is NOT NOLOAD — the ELF loader writes the
 * zero-initializer at boot so the region is not garbage on first attach.
 * rzv_openamp_resource_table_init() populates it at runtime and then
 * cleans the D-cache so CA55 sees the coherent content.
 * (NEW-dropping NOLOAD ensures defined DDR content at boot.)
 */

static struct rptun_rsc_s g_rzv_resources
  __attribute__((section(".resource_table"), aligned(4096)));

/****************************************************************************
 * Private — rptun ops (slave: CR8 is REMOTE, CA55 is master/host)
 ****************************************************************************/

static FAR const char *rzv_rptun_get_cpuname(FAR struct rptun_dev_s *dev)
{
  UNUSED(dev);
  return "ca55";
}

static FAR struct rptun_rsc_s *rzv_rptun_get_resource(
                                  FAR struct rptun_dev_s *dev)
{
  UNUSED(dev);
  return &g_rzv_resources;
}

static bool rzv_rptun_is_autostart(FAR struct rptun_dev_s *dev)
{
  UNUSED(dev);
  return true;
}

static bool rzv_rptun_is_master(FAR struct rptun_dev_s *dev)
{
  UNUSED(dev);
  return false; /* CR8 is slave/remote */
}

static int rzv_rptun_notify(FAR struct rptun_dev_s *dev, uint32_t vqid)
{
  UNUSED(dev);
  return rzv_rproc_notify(vqid);
}

static int rzv_rptun_register_callback(FAR struct rptun_dev_s *dev,
                                       rptun_callback_t callback,
                                       FAR void *arg)
{
  UNUSED(dev);
  return rzv_rproc_register_callback(callback, arg);
}

static const struct rptun_ops_s g_rzv_rptun_ops =
{
  .get_cpuname       = rzv_rptun_get_cpuname,
  .get_firmware      = NULL,   /* slave: no firmware to load */
  .get_addrenv       = NULL,
  .get_resource      = rzv_rptun_get_resource,
  .is_autostart      = rzv_rptun_is_autostart,
  .is_master         = rzv_rptun_is_master,
  .config            = NULL,
  .start             = NULL,   /* slave does not boot master */
  .stop              = NULL,
  .notify            = rzv_rptun_notify,
  .register_callback = rzv_rptun_register_callback,
  .reset             = NULL,
  .panic             = NULL,
};

static struct rptun_dev_s g_rzv_rptun_dev;

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_openamp_resource_table_init
 *
 * Description:
 *   Populate the single resource table at 0x42F00000 with one vdev entry
 *   covering two vrings.  Called from rzv_rproc_initialize() before the
 *   MHU IRQ is enabled.
 *
 *   After writing, clean the D-cache so CA55 Linux remoteproc sees a
 *   coherent copy when it maps the table.
 *   TODO(IPC-MEM-003): replace software clean with MPU non-cacheable
 *   region once mpu_region_table.c is ported from refs/.
 *
 ****************************************************************************/

void rzv_openamp_resource_table_init(void)
{
  struct rptun_rsc_s *rsc = &g_rzv_resources;

  memset(rsc, 0, sizeof(*rsc));

  /* Resource table header: single entry (num=1) — only the rpmsg vdev.
   * C2 fix: do not point any offset[] at the log_trace slot (type=0 =
   * RSC_CARVEOUT, not "skip").  num=1 with offset[0] → rpmsg_vdev is
   * the YAGNI-compatible option from the Stage-2 review recommendation.
   */

  rsc->rsc_tbl_hdr.ver       = 1;
  rsc->rsc_tbl_hdr.num       = 1;
  rsc->rsc_tbl_hdr.reserved[0] = 0;
  rsc->rsc_tbl_hdr.reserved[1] = 0;

  /* Single offset entry: the rpmsg vdev. */

  rsc->offset[0] = (uint32_t)offsetof(struct rptun_rsc_s, rpmsg_vdev);

  /* rpmsg vdev entry */

  rsc->rpmsg_vdev.type         = RSC_VDEV;
  rsc->rpmsg_vdev.id           = RZV_OPENAMP_VIRTIO_ID_RPMSG;
  rsc->rpmsg_vdev.notifyid     = RZV_OPENAMP_NOTIFYID_VDEV;
  rsc->rpmsg_vdev.dfeatures    = RZV_OPENAMP_RPMSG_FEATURES;
  rsc->rpmsg_vdev.gfeatures    = 0;
  rsc->rpmsg_vdev.config_len   = 0;
  rsc->rpmsg_vdev.status       = 0;
  rsc->rpmsg_vdev.num_of_vrings = RZV_OPENAMP_NUM_VRINGS;

  /* vring0: TX (CR8 → CA55) */

  rsc->rpmsg_vring0.da       = RZV_OPENAMP_VRING0_BASE;
  rsc->rpmsg_vring0.align    = RZV_OPENAMP_VRING_ALIGN;
  rsc->rpmsg_vring0.num      = RZV_OPENAMP_RPMSG_NUM_BUFS;
  rsc->rpmsg_vring0.notifyid = RZV_OPENAMP_NOTIFYID_VRING0;
  rsc->rpmsg_vring0.reserved = 0;

  /* vring1: RX (CA55 → CR8), stride 0x100000 from vring0 */

  rsc->rpmsg_vring1.da       = RZV_OPENAMP_VRING1_BASE;
  rsc->rpmsg_vring1.align    = RZV_OPENAMP_VRING_ALIGN;
  rsc->rpmsg_vring1.num      = RZV_OPENAMP_RPMSG_NUM_BUFS;
  rsc->rpmsg_vring1.notifyid = RZV_OPENAMP_NOTIFYID_VRING1;
  rsc->rpmsg_vring1.reserved = 0;

  /* config: zeroed — slave does not provide buffer-size config */

  /* Clean D-cache: ensure CA55 sees the resource table contents
   * (software coherence fallback; MPU non-cacheable preferred long-term).
   */

  up_clean_dcache((uintptr_t)rsc,
                  (uintptr_t)rsc + sizeof(struct rptun_rsc_s));
}

/****************************************************************************
 * Name: rzv_openamp_initialize
 *
 * Description:
 *   Initialize OpenAMP stack: resource table, MHU IRQ, rptun device.
 *   Must be called once at boot (e.g. from board_late_initialize).
 *   rpmsg_register_callback() is called BEFORE rptun_initialize() so the
 *   device_created event is not missed.
 *
 ****************************************************************************/

int rzv_openamp_initialize(void)
{
  int ret;

  /* Step 1: init resource table and attach MHU IRQ */

  ret = rzv_rproc_initialize();
  if (ret < 0)
    {
      return ret;
    }

  /* Step 2: register rpmsg device_created/destroy watchers before
   * rptun_initialize() fires them (ordering fix for IPC-RPMSG-001).
   */

  /* rzv_rpmsg_initialize() is called from rzv_ipcc_initialize() which
   * runs after us; if standalone OpenAMP is used without IPCC, call it
   * here.  The IPCC path already covers it.
   */

  /* Step 3: register rptun device — this spawns the RPTUN worker thread
   * (CONFIG_RPTUN_THREAD=y) and eventually calls register_callback which
   * wires rzv_rproc_register_callback → g_notify (phase 02 hook).
   */

  g_rzv_rptun_dev.ops = &g_rzv_rptun_ops;

  ret = rptun_initialize(&g_rzv_rptun_dev);
  if (ret < 0)
    {
      return ret;
    }

  return OK;
}

#endif /* CONFIG_RZV_OPENAMP */
