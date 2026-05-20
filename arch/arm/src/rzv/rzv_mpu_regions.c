/****************************************************************************
 * arch/arm/src/rzv/rzv_mpu_regions.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * RZ/V2H Cortex-R8 MPU region table — NuttX port of the FreeRTOS FSP
 * reference in refs/px4-freertos-posix-renesas-fsp/src/runtime/mpu_region_table.c
 *
 * Narrow port: region table verbatim, wired into CR8 startup.
 * No IPC-specific region added — FreeRTOS region 9 (16 MiB at 0x43000000,
 * Strongly-Ordered Shareable) already covers the IPC raw SHM carveout at
 * 0x43800000–0x4381FFFF. Software cache ops in rzv_ipc_raw.c are kept as
 * defence-in-depth.
 *
 * Region layout (matches FreeRTOS g_mpu_region_table_array):
 *  CR8_0:
 *   0: ITCM         0x00000000  128 KiB  Normal, outer-NC / inner-NC
 *   1: DTCM         0x00020000  128 KiB  Normal, outer-NC / inner-NC, XN
 *   2: SRAM-cache   0x08180000  128 KiB  Normal, outer-NC / inner-WB
 *   3: SRAM-NC      0x081A0000  128 KiB  Normal, outer-NC / inner-NC
 *   4: Peripheral   0x10000000  256 MiB  Device Shareable, XN
 *   5: xSPI         0x20000000  256 MiB  Normal, outer-NC / inner-WB, RO
 *   6: DDR-cache    0x40800000    8 MiB  Normal, outer-NC / inner-WB
 *   7: DDR-NC       0x41800000    8 MiB  Normal, outer-NC / inner-NC
 *   8: OA RSCTBL+MHU SHMEM 0x42F00000  8 KiB  Normal-NC, Shareable
 *   9: OA VRING     0x43000000   16 MiB  Normal-NC, Shareable
 *                               ↑ covers IPC raw SHM at 0x43800000
 *  10: DDR-cache2   0x41000000    8 MiB  Normal, outer-NC / inner-WB
 *  11-15: unused (disabled)
 *
 *  CR8_1:
 *   Regions 0-5, 8-10, 11-15: identical to CR8_0 except:
 *   2: SRAM-cache   0x081C0000
 *   3: SRAM-NC      0x081E0000
 *   6: DDR-cache    0x41800000
 *   7: DDR-NC       0x42800000
 *  10: DDR-cache2   0x42000000
 *
 * This file is compiled only when CONFIG_RZV_MPU_PORT_FSP=y.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#ifdef CONFIG_RZV_MPU_PORT_FSP

#include <stdint.h>
#include "mpu.h"
#include "barriers.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* ARMv7-R DRSR size encoding: bits[5:1] = (log2(size) - 1).
 * BSP uses (n << 1) where n = log2(size)-1.  Map FSP sizes to log2.
 */
#define RZV_MPU_LOG2_128KB    17u  /* 2^17 = 128 KiB */
#define RZV_MPU_LOG2_8KB      13u  /* 2^13 =   8 KiB */
#define RZV_MPU_LOG2_8MB      23u  /* 2^23 =   8 MiB */
#define RZV_MPU_LOG2_16MB     24u  /* 2^24 =  16 MiB */
#define RZV_MPU_LOG2_256MB    28u  /* 2^28 = 256 MiB */

/* DRACR attribute bit fields (ARMv7-R PMSA) */
#define DRACR_AP_RWRW         (0x3u << 8)   /* Full R/W priv+user */
#define DRACR_AP_RORO         (0x6u << 8)   /* Read-only priv+user */
#define DRACR_XN              (1u   << 12)  /* Execute-never */
#define DRACR_TEX_SHIFT       3u
#define DRACR_C               (1u   << 1)
#define DRACR_B               (1u   << 0)
#define DRACR_S               (1u   << 2)   /* Shareable */

/* Attribute bundles matching FreeRTOS BSP macros */

/* Normal, outer-NC / inner-NC = TEX=001, C=0, B=0 */
#define ATTR_NORMAL_NC        (DRACR_AP_RWRW | (1u << DRACR_TEX_SHIFT))

/* Normal, outer-NC / inner-WB = TEX=100, C=0, B=1 */
#define ATTR_NORMAL_WB        (DRACR_AP_RWRW | (4u << DRACR_TEX_SHIFT) | DRACR_B)

/* Normal, outer-NC / inner-NC + Shareable */
#define ATTR_NORMAL_NC_S      (ATTR_NORMAL_NC | DRACR_S)

/* Normal, outer-NC / inner-NC, XN (DTCM) */
#define ATTR_NORMAL_NC_XN     (ATTR_NORMAL_NC | DRACR_XN)

/* Device Shareable, XN (peripheral) = TEX=000, C=0, B=1, S=1 */
#define ATTR_DEVICE_S_XN      (DRACR_AP_RWRW | DRACR_B | DRACR_S | DRACR_XN)

/* Normal WB, read-only (xSPI flash) */
#define ATTR_NORMAL_WB_RO     (DRACR_AP_RORO | (4u << DRACR_TEX_SHIFT) | DRACR_B)

/* DRSR enable bit */
#define DRSR_EN               (1u << 0)

/* Build DRSR value: size field = (log2-1) << 1 | EN */
#define DRSR_VAL(log2sz)      (((uint32_t)((log2sz) - 1u) << 1u) | DRSR_EN)

/****************************************************************************
 * Private Types
 ****************************************************************************/

struct rzv_mpu_region_s
{
  uint32_t rgnr;   /* Region number */
  uint32_t drbar;  /* Data Region Base Address Register value */
  uint32_t drsr;   /* Data Region Size and Enable Register value */
  uint32_t dracr;  /* Data Region Access Control Register value */
};

/****************************************************************************
 * Private Data — one table per core
 ****************************************************************************/

static const struct rzv_mpu_region_s g_rzv_mpu_cr8_0[] =
{
  /* region 0: ITCM */
  { 0u, 0x00000000u, DRSR_VAL(RZV_MPU_LOG2_128KB), ATTR_NORMAL_NC },
  /* region 1: DTCM */
  { 1u, 0x00020000u, DRSR_VAL(RZV_MPU_LOG2_128KB), ATTR_NORMAL_NC_XN },
  /* region 2: CR8_0 RCPU-SRAM cacheable */
  { 2u, 0x08180000u, DRSR_VAL(RZV_MPU_LOG2_128KB), ATTR_NORMAL_WB },
  /* region 3: CR8_0 RCPU-SRAM non-cacheable */
  { 3u, 0x081A0000u, DRSR_VAL(RZV_MPU_LOG2_128KB), ATTR_NORMAL_NC },
  /* region 4: Peripheral 256 MiB */
  { 4u, 0x10000000u, DRSR_VAL(RZV_MPU_LOG2_256MB), ATTR_DEVICE_S_XN },
  /* region 5: xSPI flash 256 MiB, read-only */
  { 5u, 0x20000000u, DRSR_VAL(RZV_MPU_LOG2_256MB), ATTR_NORMAL_WB_RO },
  /* region 6: DDR cacheable 8 MiB */
  { 6u, 0x40800000u, DRSR_VAL(RZV_MPU_LOG2_8MB),   ATTR_NORMAL_WB },
  /* region 7: DDR non-cacheable 8 MiB */
  { 7u, 0x41800000u, DRSR_VAL(RZV_MPU_LOG2_8MB),   ATTR_NORMAL_NC },
  /* region 8: OpenAMP RSCTBL + MHU SHMEM 8 KiB, non-cacheable Shareable */
  { 8u, 0x42F00000u, DRSR_VAL(RZV_MPU_LOG2_8KB),   ATTR_NORMAL_NC_S },
  /* region 9: OpenAMP VRING 16 MiB, non-cacheable Shareable
   * NOTE: 0x43000000 + 16 MiB = 0x44000000; covers IPC raw SHM at 0x43800000
   */
  { 9u, 0x43000000u, DRSR_VAL(RZV_MPU_LOG2_16MB),  ATTR_NORMAL_NC_S },
  /* region 10: DDR cacheable extension 8 MiB */
  { 10u, 0x41000000u, DRSR_VAL(RZV_MPU_LOG2_8MB),  ATTR_NORMAL_WB },
  /* regions 11-15: unused — leave MPU region disabled (DRSR EN=0) */
  { 11u, 0u, 0u, 0u },
  { 12u, 0u, 0u, 0u },
  { 13u, 0u, 0u, 0u },
  { 14u, 0u, 0u, 0u },
  { 15u, 0u, 0u, 0u },
};

/* Suppress unused-variable warning when CONFIG_RZV_MPU_CR8_CORE_NUM=0 */

static const struct rzv_mpu_region_s g_rzv_mpu_cr8_1[]
  __attribute__((unused)) =
{
  /* region 0: ITCM */
  { 0u, 0x00000000u, DRSR_VAL(RZV_MPU_LOG2_128KB), ATTR_NORMAL_NC },
  /* region 1: DTCM */
  { 1u, 0x00020000u, DRSR_VAL(RZV_MPU_LOG2_128KB), ATTR_NORMAL_NC_XN },
  /* region 2: CR8_1 RCPU-SRAM cacheable */
  { 2u, 0x081C0000u, DRSR_VAL(RZV_MPU_LOG2_128KB), ATTR_NORMAL_WB },
  /* region 3: CR8_1 RCPU-SRAM non-cacheable */
  { 3u, 0x081E0000u, DRSR_VAL(RZV_MPU_LOG2_128KB), ATTR_NORMAL_NC },
  /* region 4: Peripheral 256 MiB */
  { 4u, 0x10000000u, DRSR_VAL(RZV_MPU_LOG2_256MB), ATTR_DEVICE_S_XN },
  /* region 5: xSPI flash 256 MiB, read-only */
  { 5u, 0x20000000u, DRSR_VAL(RZV_MPU_LOG2_256MB), ATTR_NORMAL_WB_RO },
  /* region 6: DDR cacheable 8 MiB (CR8_1 offset) */
  { 6u, 0x41800000u, DRSR_VAL(RZV_MPU_LOG2_8MB),   ATTR_NORMAL_WB },
  /* region 7: DDR non-cacheable 8 MiB (CR8_1 offset) */
  { 7u, 0x42800000u, DRSR_VAL(RZV_MPU_LOG2_8MB),   ATTR_NORMAL_NC },
  /* region 8: OpenAMP RSCTBL + MHU SHMEM 8 KiB, non-cacheable Shareable */
  { 8u, 0x42F00000u, DRSR_VAL(RZV_MPU_LOG2_8KB),   ATTR_NORMAL_NC_S },
  /* region 9: OpenAMP VRING 16 MiB, non-cacheable Shareable */
  { 9u, 0x43000000u, DRSR_VAL(RZV_MPU_LOG2_16MB),  ATTR_NORMAL_NC_S },
  /* region 10: DDR cacheable extension 8 MiB (CR8_1 offset) */
  { 10u, 0x42000000u, DRSR_VAL(RZV_MPU_LOG2_8MB),  ATTR_NORMAL_WB },
  /* regions 11-15: unused */
  { 11u, 0u, 0u, 0u },
  { 12u, 0u, 0u, 0u },
  { 13u, 0u, 0u, 0u },
  { 14u, 0u, 0u, 0u },
  { 15u, 0u, 0u, 0u },
};

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_mpu_init
 *
 * Description:
 *   Programme the ARMv7-R MPU with the RZ/V2H region table.
 *   Called from rzv_start.c::arm_boot() after caches are invalidated
 *   but before they are enabled.
 *
 *   Selects the CR8_0 or CR8_1 table based on CONFIG_RZV_MPU_CR8_CORE_NUM.
 *   After all regions are written, enables the MPU via mpu_control(true).
 *
 ****************************************************************************/

void rzv_mpu_init(void)
{
  const struct rzv_mpu_region_s *tbl;
  uint32_t                       nregs;
  uint32_t                       i;

#if defined(CONFIG_RZV_MPU_CR8_CORE_NUM) && (CONFIG_RZV_MPU_CR8_CORE_NUM == 1)
  tbl   = g_rzv_mpu_cr8_1;
  nregs = sizeof(g_rzv_mpu_cr8_1) / sizeof(g_rzv_mpu_cr8_1[0]);
#else
  /* Default to CR8_0 table */
  tbl   = g_rzv_mpu_cr8_0;
  nregs = sizeof(g_rzv_mpu_cr8_0) / sizeof(g_rzv_mpu_cr8_0[0]);
#endif

  /* Disable MPU before reprogramming regions */

  mpu_control(false);
  ARM_DSB();
  ARM_ISB();

  for (i = 0; i < nregs; i++)
    {
      mpu_set_rgnr(tbl[i].rgnr);
      mpu_set_drbar(tbl[i].drbar);
      mpu_set_drsr(tbl[i].drsr);
      mpu_set_dracr(tbl[i].dracr);
    }

  ARM_DSB();
  ARM_ISB();

  /* Enable MPU with background-region enabled (SCTLR.BR=1) so
   * privileged accesses to unmapped regions are still permitted
   * (matches FreeRTOS default; NuttX mpu_control sets SCTLR_BR).
   */

  mpu_control(true);
  ARM_DSB();
  ARM_ISB();
}

#endif /* CONFIG_RZV_MPU_PORT_FSP */
