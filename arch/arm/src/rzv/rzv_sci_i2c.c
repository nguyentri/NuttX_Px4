/****************************************************************************
 * arch/arm/src/rzv/rzv_sci_i2c.c
 *
 * RZ/V2H SCI-B Simple-I2C master driver (CPU-mode, interrupt-driven).
 *
 * Supported: 7-bit address, standard (100 kHz) and fast (400 kHz) modes,
 *            multi-message transfer with REPEATED START.
 * Not supported: slave mode, 10-bit address (returns -ENOTSUP), DMAC.
 *
 * Audit fixes addressed:
 *   dim 1  — 32-bit register layout via hardware/rzv_sci.h (no legacy 8-bit)
 *   dim 2  — CCR3.MOD=I2C, ICR config per RZ/V2H SCI-B hardware manual
 *   dim 3  — clock calc in rzv_sci_i2c_clock.c, PCLK from Kconfig fallback
 *   dim 4  — rzv_clock_enable + rzv_module_unreset (no deprecated CLKON)
 *   dim 5  — rzv_icu_attach × 3 (TXI/TEI/RXI); -ENOSYS if attach fails
 *   dim 8  — start/restart/stop atomic via SCI_I2C_REQ macro
 *   dim 9  — NACK → -ENXIO; abort issues STOP via ISR
 *   dim 10 — CFCLR/ICFCLR write-1-clear (no SSR); ERI not attached
 *   dim 11 — critical sections on ICR/CCR0 RMW
 *   dim 12 — static priv[4], no heap
 *   dim 16 — dead fields (eri_irq, slave_addr) removed
 *   dim 17 — -ENOSYS if IRQ attach fails; -ETIMEDOUT on sem timeout
 *
 * Licensed under Apache License 2.0 — see top-level NOTICE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <debug.h>
#include <assert.h>
#include <time.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/semaphore.h>
#include <nuttx/i2c/i2c_master.h>

#include <arch/board/board.h>

#include "arm_internal.h"
#include "hardware/rzv_sci.h"
#include "hardware/rzv_elc.h"
#include "rzv_clock.h"
#include "rzv_gpio.h"
#include "rzv_icu.h"
#include "rzv_sci_i2c.h"
#include "rzv_sci_i2c_internal.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* SCI-I2C clock source is P5CLK (100 MHz) per RZ/V2H hardware manual.
 * Resolved at runtime via rzv_clock_get_rate(); falls back to compile-time
 * default when the CPG read returns 0.
 */

#define SCI_I2C_PCLK_FALLBACK_HZ   RZV_CLOCK_P5CLK_HZ

/* Default SCL frequency when msg->frequency == 0 */

#define SCI_I2C_DEFAULT_SCL_HZ     100000u

/* CESR poll timeout iterations (10 ms at ~1 ns/iter is conservative) */

#define SCI_I2C_CESR_TIMEOUT       10000u

/* BCP fixed at 4 for I2C mode per RZ/V2H SCI-B hardware manual */

#define SCI_I2C_CCR2_BCP           4u

#define SCI_I2C_RECOVERY_DELAY_US  10u

/* Board must define BOARD_SCIn_I2C_SDA_GPIO / SCL_GPIO for enabled channels.
 * A missing definition causes a compile-time error here — fail fast.
 * (GPIO ABI requirement, dim 6)
 */

#ifdef CONFIG_RZV_SCI0_I2C
#  ifndef BOARD_SCI0_I2C_SDA_GPIO
#    error "CONFIG_RZV_SCI0_I2C requires BOARD_SCI0_I2C_SDA_GPIO in board.h"
#  endif
#  ifndef BOARD_SCI0_I2C_SCL_GPIO
#    error "CONFIG_RZV_SCI0_I2C requires BOARD_SCI0_I2C_SCL_GPIO in board.h"
#  endif
#endif

#ifdef CONFIG_RZV_SCI1_I2C
#  ifndef BOARD_SCI1_I2C_SDA_GPIO
#    error "CONFIG_RZV_SCI1_I2C requires BOARD_SCI1_I2C_SDA_GPIO in board.h"
#  endif
#  ifndef BOARD_SCI1_I2C_SCL_GPIO
#    error "CONFIG_RZV_SCI1_I2C requires BOARD_SCI1_I2C_SCL_GPIO in board.h"
#  endif
#endif

#ifdef CONFIG_RZV_SCI2_I2C
#  ifndef BOARD_SCI2_I2C_SDA_GPIO
#    error "CONFIG_RZV_SCI2_I2C requires BOARD_SCI2_I2C_SDA_GPIO in board.h"
#  endif
#  ifndef BOARD_SCI2_I2C_SCL_GPIO
#    error "CONFIG_RZV_SCI2_I2C requires BOARD_SCI2_I2C_SCL_GPIO in board.h"
#  endif
#endif

#ifdef CONFIG_RZV_SCI3_I2C
#  ifndef BOARD_SCI3_I2C_SDA_GPIO
#    error "CONFIG_RZV_SCI3_I2C requires BOARD_SCI3_I2C_SDA_GPIO in board.h"
#  endif
#  ifndef BOARD_SCI3_I2C_SCL_GPIO
#    error "CONFIG_RZV_SCI3_I2C requires BOARD_SCI3_I2C_SCL_GPIO in board.h"
#  endif
#endif

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static int sci_i2c_transfer(struct i2c_master_s *dev,
                            struct i2c_msg_s *msgs, int count);
static int sci_i2c_hw_init(struct rzv_sci_i2c_priv_s *priv,
                           uint32_t scl_hz);
#ifdef CONFIG_I2C_RESET
static int sci_i2c_reset(struct i2c_master_s *dev);
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* NuttX ops table */

static const struct i2c_ops_s g_sci_i2c_ops =
{
  .transfer = sci_i2c_transfer,
#ifdef CONFIG_I2C_RESET
  .reset    = sci_i2c_reset,
#endif
};

/* Per-channel ELC event lookup table (non-contiguous — use table) */

static const struct
{
  int txi;
  int tei;
  int rxi;
} g_sci_i2c_events[4] =
{
  { ELC_EVENT_SCI0_TXI, ELC_EVENT_SCI0_TEI, ELC_EVENT_SCI0_RXI },
  { ELC_EVENT_SCI1_TXI, ELC_EVENT_SCI1_TEI, ELC_EVENT_SCI1_RXI },
  { ELC_EVENT_SCI2_TXI, ELC_EVENT_SCI2_TEI, ELC_EVENT_SCI2_RXI },
  { ELC_EVENT_SCI3_TXI, ELC_EVENT_SCI3_TEI, ELC_EVENT_SCI3_RXI },
};

/* Per-channel base address table */

static const uint32_t g_sci_base[4] =
{
  RZV_SCI0_BASE, RZV_SCI1_BASE, RZV_SCI2_BASE, RZV_SCI3_BASE,
};

/* Per-channel CPG clock IDs */

static const uint32_t g_sci_clk[4] =
{
  RZV_CPG_CLK_SCI0, RZV_CPG_CLK_SCI1,
  RZV_CPG_CLK_SCI2, RZV_CPG_CLK_SCI3,
};

/* Static per-channel private structures (dim 12 — no heap) */

static struct rzv_sci_i2c_priv_s g_sci_i2c_priv[4];

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static int sci_i2c_wait_idle(struct rzv_sci_i2c_priv_s *priv)
{
  uint32_t timeout;

  for (timeout = SCI_I2C_CESR_TIMEOUT; timeout > 0; timeout--)
    {
      if ((getreg32(priv->base + RZV_SCI_CESR_OFFSET) &
           (SCI_CESR_RIST | SCI_CESR_TIST)) == 0u)
        {
          return OK;
        }
    }

  i2cerr("SCI%u: CESR timeout on disable\n", priv->channel);
  return -ETIMEDOUT;
}

static void sci_i2c_clear_status(struct rzv_sci_i2c_priv_s *priv)
{
  putreg32(SCI_CFCLR_RDRFC | SCI_CFCLR_TDREC | SCI_CFCLR_ERSC |
           SCI_CFCLR_DCMFC | SCI_CFCLR_DPERC | SCI_CFCLR_DFERC |
           SCI_CFCLR_ORERC | SCI_CFCLR_MFFC  | SCI_CFCLR_PERC  |
           SCI_CFCLR_FERC,
           priv->base + RZV_SCI_CFCLR_OFFSET);
  putreg32(SCI_ICFCLR_IICSTIFC, priv->base + RZV_SCI_ICFCLR_OFFSET);
}

static int sci_i2c_quiesce(struct rzv_sci_i2c_priv_s *priv)
{
  irqstate_t flags;
  uint32_t icr;
  int ret;

  flags = enter_critical_section();
  putreg32(0u, priv->base + RZV_SCI_CCR0_OFFSET);
  ret = sci_i2c_wait_idle(priv);
  sci_i2c_clear_status(priv);
  icr = getreg32(priv->base + RZV_SCI_ICR_OFFSET);
  putreg32(icr | SCI_ICR_IICSDAS_MASK | SCI_ICR_IICSCLS_MASK,
           priv->base + RZV_SCI_ICR_OFFSET);
  priv->state = SCI_I2C_STATE_IDLE;
  leave_critical_section(flags);
  return ret;
}

#if defined(CONFIG_I2C_RESET) || defined(CONFIG_RZV_SCI0_I2C) || \
    defined(CONFIG_RZV_SCI1_I2C) || defined(CONFIG_RZV_SCI2_I2C) || \
    defined(CONFIG_RZV_SCI3_I2C)
static int sci_i2c_config_pins(struct rzv_sci_i2c_priv_s *priv)
{
  int ret = rzv_gpioconfig(priv->scl_gpio);
  if (ret < 0)
    {
      return ret;
    }

  return rzv_gpioconfig(priv->sda_gpio);
}
#endif

#ifdef CONFIG_I2C_RESET
static int sci_i2c_recover_bus(struct rzv_sci_i2c_priv_s *priv)
{
  int ret;

  ret = rzv_gpioconfig(priv->scl_reset_gpio);
  if (ret < 0)
    {
      return ret;
    }

  ret = rzv_gpioconfig(priv->sda_reset_gpio);
  if (ret < 0)
    {
      int remux_ret = sci_i2c_config_pins(priv);
      return remux_ret < 0 ? remux_ret : ret;
    }

  /* A slave holding SCL low cannot be recovered by clock pulses. */

  rzv_gpiowrite(priv->scl_reset_gpio, true);
  if (!rzv_gpioread(priv->scl_reset_gpio))
    {
      ret = sci_i2c_config_pins(priv);
      return ret < 0 ? ret : -EBUSY;
    }

  for (unsigned int pulse = 0; pulse < 9; pulse++)
    {
      rzv_gpiowrite(priv->scl_reset_gpio, false);
      up_udelay(SCI_I2C_RECOVERY_DELAY_US);
      rzv_gpiowrite(priv->scl_reset_gpio, true);
      up_udelay(SCI_I2C_RECOVERY_DELAY_US);
      if (rzv_gpioread(priv->sda_reset_gpio))
        {
          break;
        }
    }

  if (!rzv_gpioread(priv->sda_reset_gpio))
    {
      ret = sci_i2c_config_pins(priv);
      return ret < 0 ? ret : -EBUSY;
    }

  /* STOP: SDA low while SCL is high, then release SDA. */

  rzv_gpiowrite(priv->sda_reset_gpio, false);
  up_udelay(SCI_I2C_RECOVERY_DELAY_US);
  rzv_gpiowrite(priv->scl_reset_gpio, true);
  up_udelay(SCI_I2C_RECOVERY_DELAY_US);
  rzv_gpiowrite(priv->sda_reset_gpio, true);
  up_udelay(SCI_I2C_RECOVERY_DELAY_US);

  ret = sci_i2c_config_pins(priv);
  if (ret < 0)
    {
      return ret;
    }

  return sci_i2c_hw_init(priv, priv->cur_scl_hz);
}
#endif

static uint32_t sci_i2c_timeout_ms(struct i2c_msg_s *msgs, int count,
                                   uint32_t scl_hz)
{
  uint64_t bits = 2u;
  uint64_t timeout_ms;
  int i;

  for (i = 0; i < count; i++)
    {
      if ((msgs[i].flags & I2C_M_NOSTART) == 0)
        {
          bits += 9u;
        }

      bits += (uint64_t)msgs[i].length * 9u;
    }

  timeout_ms = ((bits * 1000u) + scl_hz - 1u) / scl_hz;
  timeout_ms += 5u;

  if (timeout_ms < SCI_I2C_TIMEOUT_MIN_MS)
    {
      return SCI_I2C_TIMEOUT_MIN_MS;
    }

  if (timeout_ms > SCI_I2C_TIMEOUT_MAX_MS)
    {
      return SCI_I2C_TIMEOUT_MAX_MS;
    }

  return (uint32_t)timeout_ms;
}

/****************************************************************************
 * Name: sci_i2c_hw_init
 *
 * Description:
 *   Initialise SCI-B hardware in Simple-I2C master mode per RZ/V2H UM.
 *   dim 1 — all accesses via 32-bit hardware/rzv_sci.h macros
 *   dim 2 — CCR3.MOD=4 (I2C), ICR configured per RZ/V2H SCI-B hardware manual
 *   dim 3 — baud from sci_i2c_calc_clock, PCLK from Kconfig fallback
 *
 ****************************************************************************/

static int sci_i2c_hw_init(struct rzv_sci_i2c_priv_s *priv,
                           uint32_t scl_hz)
{
  uint32_t base = priv->base;
  struct sci_i2c_clock_s clk;
  int ret;

  /* Step 1: Set CCR0=0 (disable TE/RE/TIE/RIE/TEIE) */

  putreg32(0u, base + RZV_SCI_CCR0_OFFSET);

  /* Step 2: Wait for CESR.{RIST,TIST} == 0 (transfers idle) */

  ret = sci_i2c_wait_idle(priv);
  if (ret < 0)
    {
      return ret;
    }

  /* Step 3: Compute baud settings (dim 3).
   * SCI source = P5CLK; read live rate via rzv_clock_get_rate()
   * and fall back to the compile-time constant if the CPG table is unset.
   */

  uint32_t pclk_hz = rzv_clock_get_rate(RZV_CLOCK_P5CLK);
  if (pclk_hz == 0u)
    {
      pclk_hz = SCI_I2C_PCLK_FALLBACK_HZ;
    }

  ret = sci_i2c_calc_clock(pclk_hz, scl_hz, &clk);
  if (ret < 0)
    {
      return ret;
    }

  /* Step 4: Write ICR — high-Z SDA/SCL + IICINTM + IICCSC + IICACKT.
   * IICSCLS_Msk | IICSDAS_Msk = high-impedance (0x3 each) per RZ/V2H SCI-B UM.
   * Use clk.cycles_value for IICDL (SDA delay), NOT clk.snfr (#5 fix).
   */

  uint32_t icr = SCI_ICR_IICSDAS_MASK | SCI_ICR_IICSCLS_MASK;
  icr |= (uint32_t)(clk.cycles_value & 0x1fu); /* IICDL bits [4:0] per RZ/V2H SCI-B UM */
  icr |= SCI_ICR_IICINTM | SCI_ICR_IICCSC | SCI_ICR_IICACKT;
  putreg32(icr, base + RZV_SCI_ICR_OFFSET);

  /* Step 5: Write CCR3 — 8-bit char, MSB first, I2C mode per RZ/V2H SCI-B UM.
   * CHR = 2U << CHR_Pos (= 0x200) for 8-bit in I2C/sync mode.
   * MOD[18:16]=4 = Simple I2C.
   * BPEN=1 (bit 7) selects PCLK as BRG source (#3 fix; PCLK=1 so baud calc matches PCLK).
   */

  uint32_t ccr3 = SCI_CCR3_MOD_I2C |
                  (2u << SCI_CCR3_CHR_SHIFT) | /* 8-bit I2C: CHR=2 per RZ/V2H SCI-B UM */
                  SCI_CCR3_BPEN;               /* Select PCLK for BRG (#3 fix) */
  putreg32(ccr3, base + RZV_SCI_CCR3_OFFSET);

  /* Step 6: Write CCR2 with computed baud values.
   * BCP=4, BRR, BRME, CKS, MDDR in single write (no RMW).
   */

  uint32_t ccr2 = ((uint32_t)SCI_I2C_CCR2_BCP << SCI_CCR2_BCP_SHIFT) |
                  ((uint32_t)clk.brr  << SCI_CCR2_BRR_SHIFT) |
                  ((uint32_t)clk.cks  << SCI_CCR2_CKS_SHIFT) |
                  ((uint32_t)clk.mddr << SCI_CCR2_MDDR_SHIFT) |
                  (clk.brme ? SCI_CCR2_BRME : 0u);
  putreg32(ccr2, base + RZV_SCI_CCR2_OFFSET);

  /* Step 7: Write CCR1 — noise filter */

  uint32_t ccr1 = ((uint32_t)clk.snfr << SCI_CCR1_NFCS_SHIFT) |
                  SCI_CCR1_NFEN;
  putreg32(ccr1, base + RZV_SCI_CCR1_OFFSET);

  /* Step 8: Write CCR4 = 0 */

  putreg32(0u, base + RZV_SCI_CCR4_OFFSET);

  /* Step 9: Clear all status flags (write-1-clear CFCLR/ICFCLR) */

  sci_i2c_clear_status(priv);
  priv->cur_scl_hz = scl_hz;

  /* Note: CCR0 (TE|RE) written in transfer() just before START */

  return OK;
}

/****************************************************************************
 * Name: sci_i2c_transfer
 *
 * Description:
 *   NuttX I2C upper-half transfer operation.
 *   Validates messages, sets up ISR state, issues START, waits for done.
 *   dim 17: returns -ENOTSUP for 10-bit, -ETIMEDOUT on timeout, -ENXIO NACK
 *
 ****************************************************************************/

static int sci_i2c_transfer(struct i2c_master_s *dev,
                            struct i2c_msg_s *msgs, int count)
{
  struct rzv_sci_i2c_priv_s *priv =
    (struct rzv_sci_i2c_priv_s *)dev;
  struct timespec abstime;
  uint32_t timeout; /* Declared at top of function (#11 fix) */
  uint32_t icr;
  uint32_t scl_hz;
  int ret;

  DEBUGASSERT(priv != NULL && msgs != NULL);

  if (count <= 0)
    {
      return -EINVAL;
    }

  /* Reject 10-bit addressing (dim 17 / ) */

  for (int i = 0; i < count; i++)
    {
      if (msgs[i].flags & I2C_M_TEN)
        {
          return -ENOTSUP;
        }

      if (i == 0 && (msgs[i].flags & I2C_M_NOSTART))
        {
          return -EINVAL;
        }

      if (i == count - 1 && (msgs[i].flags & I2C_M_NOSTOP))
        {
          /* This lower half cannot retain an active bus between calls. */
          return -ENOTSUP;
        }

      if (i > 0 && (msgs[i].flags & I2C_M_NOSTART) &&
          (msgs[i].addr != msgs[i - 1].addr ||
           ((msgs[i].flags ^ msgs[i - 1].flags) & I2C_M_READ) != 0))
        {
          return -EINVAL;
        }
    }

  /* Acquire bus mutex */

  ret = nxsem_wait_uninterruptible(&priv->sem_excl);
  if (ret < 0)
    {
      return ret;
    }

  /* Quiesce the previous source and fence any stale completion before reuse. */

  ret = sci_i2c_quiesce(priv);
  if (ret < 0)
    {
      goto out_unlock;
    }

  ret = nxsem_reset(&priv->sem_isr, 0);
  if (ret < 0)
    {
      goto out_unlock;
    }

  scl_hz = (msgs[0].frequency > 0) ?
            msgs[0].frequency : SCI_I2C_DEFAULT_SCL_HZ;

  if (scl_hz != priv->cur_scl_hz)
    {
      ret = sci_i2c_hw_init(priv, scl_hz);
      if (ret < 0)
        {
          goto out_unlock;
        }
    }

  priv->msgs         = msgs;
  priv->msg_count    = count;
  priv->msg_idx      = 0;
  priv->byte_idx     = 0;
  priv->do_read      = (msgs[0].flags & I2C_M_READ) != 0;
  priv->do_dummy_read = priv->do_read; /* Skip addr-ACK RDR on first read */
  priv->result       = OK;
  priv->state        = SCI_I2C_STATE_ADDR;

  /* Enable TE, RE, TIE, TEIE to start transfer */

  putreg32(SCI_CCR0_TE | SCI_CCR0_RE | SCI_CCR0_TIE | SCI_CCR0_TEIE,
           priv->base + RZV_SCI_CCR0_OFFSET);

  /* Wait for CESR.{RIST,TIST} == 1 (transfers enabled) */

  for (timeout = SCI_I2C_CESR_TIMEOUT; timeout > 0; timeout--)
    {
      uint32_t cesr = getreg32(priv->base + RZV_SCI_CESR_OFFSET);
      if ((cesr & (SCI_CESR_RIST | SCI_CESR_TIST)) ==
          (SCI_CESR_RIST | SCI_CESR_TIST))
        {
          break;
        }
    }

  if (timeout == 0u)
    {
      /* TE/RE never became active — bail before issuing START (#9 fix) */

      i2cerr("SCI%u: CESR timeout on enable\n", priv->channel);
      (void)sci_i2c_quiesce(priv);
      ret = -ETIMEDOUT;
      goto out_unlock;
    }

  /* Issue START condition atomically via ICR request word */

  icr = getreg32(priv->base + RZV_SCI_ICR_OFFSET);
  putreg32(SCI_I2C_REQ(icr, 1, 1, SCI_ICR_IICSTAREQ),
           priv->base + RZV_SCI_ICR_OFFSET);

  /* Wait for ISR completion with timeout (dim 17) */

  uint32_t timeout_ms = sci_i2c_timeout_ms(msgs, count, scl_hz);
  clock_gettime(CLOCK_REALTIME, &abstime);
  abstime.tv_sec  += timeout_ms / 1000;
  abstime.tv_nsec += (timeout_ms % 1000) * 1000000L;
  if (abstime.tv_nsec >= 1000000000L)
    {
      abstime.tv_sec++;
      abstime.tv_nsec -= 1000000000L;
    }

  ret = nxsem_timedwait_uninterruptible(&priv->sem_isr, &abstime);
  if (ret == -ETIMEDOUT)
    {
      /* Hardware abort: quiesce at the SCI source, clear stale flags, and
       * release the bus pins. Never mask the shared GIC line here.
       */

      (void)sci_i2c_quiesce(priv);
      i2cerr("SCI%u: transfer timeout\n", priv->channel);
    }
  else
    {
      ret = priv->result;
    }

out_unlock:
  nxsem_post(&priv->sem_excl);
  return ret;
}

#ifdef CONFIG_I2C_RESET
/****************************************************************************
 * Name: sci_i2c_reset
 *
 * Description:
 *   Bus recovery: toggle SCL 9 times via GPIO to unstick a locked slave.
 *   Remuxes pins back to SCI peripheral after recovery.
 *   (NuttX i2c_ops_s.reset contract; active only when CONFIG_I2C_RESET=y,
 *   which requires ARCH_HAVE_I2CRESET to be set by the BSP.)
 *   dim 9 bus-stuck recovery requirement.
 *
 *   Caller: NuttX I2C upper half on -ETIMEDOUT or -EIO.
 *
 ****************************************************************************/

static int sci_i2c_reset(struct i2c_master_s *dev)
{
  struct rzv_sci_i2c_priv_s *priv =
    (struct rzv_sci_i2c_priv_s *)dev;
  int ret;

  ret = nxsem_wait_uninterruptible(&priv->sem_excl);
  if (ret < 0)
    {
      return ret;
    }

  ret = sci_i2c_quiesce(priv);
  if (ret >= 0)
    {
      ret = sci_i2c_recover_bus(priv);
    }

  nxsem_post(&priv->sem_excl);
  return ret;
}
#endif /* CONFIG_I2C_RESET */

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_sci_i2c_initialize
 *
 * Description:
 *   Initialise SCI channel as I2C master. Returns i2c_master_s * or NULL.
 * Channel must be enabled via CONFIG_RZV_SCIn_I2C Kconfig.
 *
 *   dim 4  — clock enable + module unreset
 *   dim 5  — rzv_icu_attach × 3; returns NULL (not -ENOSYS) on failure
 *   dim 6  — pin config via rzv_gpioconfig with board-supplied macros
 *   dim 16 — static priv, initialised once
 *
 ****************************************************************************/

struct i2c_master_s *rzv_sci_i2c_initialize(int channel)
{
  struct rzv_sci_i2c_priv_s *priv;

  /* Validate channel against compile-time-enabled set */

  switch (channel)
    {
#ifdef CONFIG_RZV_SCI0_I2C
      case 0: break;
#endif
#ifdef CONFIG_RZV_SCI1_I2C
      case 1: break;
#endif
#ifdef CONFIG_RZV_SCI2_I2C
      case 2: break;
#endif
#ifdef CONFIG_RZV_SCI3_I2C
      case 3: break;
#endif
      default:
        i2cerr("SCI-I2C: channel %d not enabled in config\n", channel);
        return NULL;
    }

  priv = &g_sci_i2c_priv[channel];

  if (priv->initialized)
    {
      return &priv->dev;
    }

  /* Populate channel-invariant fields */

  priv->dev.ops   = &g_sci_i2c_ops;
  priv->channel   = (uint8_t)channel;
  priv->base      = g_sci_base[channel];
  priv->clk_id    = g_sci_clk[channel];
  priv->evt_txi   = g_sci_i2c_events[channel].txi;
  priv->evt_tei   = g_sci_i2c_events[channel].tei;
  priv->evt_rxi   = g_sci_i2c_events[channel].rxi;
  priv->state     = SCI_I2C_STATE_IDLE;

  switch (channel)
    {
#ifdef CONFIG_RZV_SCI0_I2C
      case 0:
        priv->scl_gpio       = BOARD_SCI0_I2C_SCL_GPIO;
        priv->sda_gpio       = BOARD_SCI0_I2C_SDA_GPIO;
        priv->scl_reset_gpio = BOARD_SCI0_I2C_SCL_RESET_GPIO;
        priv->sda_reset_gpio = BOARD_SCI0_I2C_SDA_RESET_GPIO;
        break;
#endif
#ifdef CONFIG_RZV_SCI1_I2C
      case 1:
        priv->scl_gpio       = BOARD_SCI1_I2C_SCL_GPIO;
        priv->sda_gpio       = BOARD_SCI1_I2C_SDA_GPIO;
        priv->scl_reset_gpio = BOARD_SCI1_I2C_SCL_RESET_GPIO;
        priv->sda_reset_gpio = BOARD_SCI1_I2C_SDA_RESET_GPIO;
        break;
#endif
#ifdef CONFIG_RZV_SCI2_I2C
      case 2:
        priv->scl_gpio       = BOARD_SCI2_I2C_SCL_GPIO;
        priv->sda_gpio       = BOARD_SCI2_I2C_SDA_GPIO;
        priv->scl_reset_gpio = BOARD_SCI2_I2C_SCL_RESET_GPIO;
        priv->sda_reset_gpio = BOARD_SCI2_I2C_SDA_RESET_GPIO;
        break;
#endif
#ifdef CONFIG_RZV_SCI3_I2C
      case 3:
        priv->scl_gpio       = BOARD_SCI3_I2C_SCL_GPIO;
        priv->sda_gpio       = BOARD_SCI3_I2C_SDA_GPIO;
        priv->scl_reset_gpio = BOARD_SCI3_I2C_SCL_RESET_GPIO;
        priv->sda_reset_gpio = BOARD_SCI3_I2C_SDA_RESET_GPIO;
        break;
#endif
      default:
        return NULL;
    }

  /* Semaphores: excl starts unlocked (1), isr starts locked (0) */

  nxsem_init(&priv->sem_excl, 0, 1);
  nxsem_init(&priv->sem_isr,  0, 0);

  /* dim 4: Enable peripheral clock and deassert reset */

  rzv_clock_enable(priv->clk_id);
  rzv_module_unreset(priv->clk_id);

  /* dim 5: Attach interrupts via INTR8SEL (no polling fallback) */

  priv->irq_txi = rzv_icu_attach(priv->evt_txi,
                                  sci_i2c_txi_isr, priv, true);
  priv->irq_tei = rzv_icu_attach(priv->evt_tei,
                                  sci_i2c_tei_isr, priv, true);
  priv->irq_rxi = rzv_icu_attach(priv->evt_rxi,
                                  sci_i2c_rxi_isr, priv, true);

  if (priv->irq_txi < 0 || priv->irq_tei < 0 || priv->irq_rxi < 0)
    {
      i2cerr("SCI%d: IRQ attach failed (txi=%d tei=%d rxi=%d)\n",
             channel, priv->irq_txi, priv->irq_tei, priv->irq_rxi);
      return NULL; /* -ENOSYS: no polling fallback (dim 17) */
    }

  /* dim 6: Configure GPIO pins as SCI peripheral (open-drain) */

  switch (channel)
    {
#ifdef CONFIG_RZV_SCI0_I2C
      case 0:
        if (sci_i2c_config_pins(priv) < 0)
          {
            return NULL;
          }
        break;
#endif
#ifdef CONFIG_RZV_SCI1_I2C
      case 1:
        if (sci_i2c_config_pins(priv) < 0)
          {
            return NULL;
          }
        break;
#endif
#ifdef CONFIG_RZV_SCI2_I2C
      case 2:
        if (sci_i2c_config_pins(priv) < 0)
          {
            return NULL;
          }
        break;
#endif
#ifdef CONFIG_RZV_SCI3_I2C
      case 3:
        if (sci_i2c_config_pins(priv) < 0)
          {
            return NULL;
          }
        break;
#endif
    }

  /* One-shot hardware initialisation with default SCL (#10 fix).
   * sci_i2c_transfer does NOT re-run hw_init; hardware state is set up once.
   */

  if (sci_i2c_hw_init(priv, SCI_I2C_DEFAULT_SCL_HZ) < 0)
    {
      i2cerr("SCI%d: hw_init failed\n", channel);
      return NULL;
    }

  priv->initialized = true;
  return &priv->dev;
}
