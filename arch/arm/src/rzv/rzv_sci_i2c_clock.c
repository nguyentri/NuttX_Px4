/****************************************************************************
 * arch/arm/src/rzv/rzv_sci_i2c_clock.c
 *
 * SCI-B Simple-I2C baud rate calculator.
 * Integer port of FSP r_sci_b_i2c_calculate_clock (not in public FSP tree;
 * derived from sci_b_i2c_open_hw_master:718-723 and SCI-B UM Section 23.3).
 *
 * Formula (SCI-B I2C mode, BCP=4):
 *   SCL_hz = PCLK / (8 * BCP * (1 << (2*cks)) * (BRR + 1))
 *   where BCP=4 (fixed per FSP CCR2 write at line 718).
 *
 * With MDDR fractional correction:
 *   SCL_actual = SCL_nominal * (MDDR / 256)   [MDDR range 128..255]
 *
 * Licensed under Apache License 2.0 — see top-level NOTICE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <debug.h>

#include "rzv_sci_i2c_internal.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* BCP is fixed at 4 in I2C mode (FSP r_sci_b_i2c.c:718) */

#define SCI_I2C_BCP             4u

/* MDDR minimum — values below 128 are not allowed by HW */

#define SCI_I2C_MDDR_MIN        128u

/* Maximum BRR register value */

#define SCI_I2C_BRR_MAX         255u

/* Acceptable frequency error threshold: 2% (in parts-per-million) */

#define SCI_I2C_ERR_PPM_MAX     20000u  /* 2% = 20000 ppm */

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: sci_i2c_div_shift
 *
 * Description:
 *   Return the clock divider ratio for CKS value n.
 *   CKS=0 → 1, CKS=1 → 4, CKS=2 → 16, CKS=3 → 64.
 *   Matches SCI-B UM Table 23.5 (PCLK / (1 << (2*cks))).
 *
 ****************************************************************************/

static uint32_t sci_i2c_div_shift(uint8_t cks)
{
  /* 1 << (2 * cks): cks=0→1, cks=1→4, cks=2→16, cks=3→64 */

  return 1u << (2u * (uint32_t)cks);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: sci_i2c_calc_clock
 *
 * Description:
 *   Compute CCR2 clock settings for a target SCL frequency.
 *   Tries CKS = 0..3, picks the (cks, brr) pair with minimum |error|.
 *   If residual error > 2%, enables MDDR fractional correction.
 *
 * Input Parameters:
 *   pclk_hz - Peripheral clock in Hz (from CPG or CONFIG_RZV_SCI_PCLK_HZ)
 *   scl_hz  - Target SCL frequency in Hz (e.g. 100000 or 400000)
 *   out     - Filled with BRR, CKS, MDDR, BRME, SNFR values
 *
 * Returned Value:
 *   0 on success, -EINVAL if no valid setting found.
 *
 ****************************************************************************/

int sci_i2c_calc_clock(uint32_t pclk_hz, uint32_t scl_hz,
                       struct sci_i2c_clock_s *out)
{
  uint8_t  best_cks  = 0;
  uint8_t  best_brr  = 0;
  uint32_t best_err  = UINT32_MAX;
  bool     found     = false;

  if (scl_hz == 0 || pclk_hz == 0)
    {
      return -EINVAL;
    }

  /* Walk CKS 0..3 to find (cks, brr) with minimum frequency error.
   *
   * SCL = PCLK / (8 * BCP * div * (BRR + 1))
   *     = PCLK / (8 * 4 * div * (BRR + 1))
   *     = PCLK / (32 * div * (BRR + 1))
   *
   * BRR = PCLK / (32 * div * scl) - 1
   */

  for (uint8_t cks = 0; cks <= 3; cks++)
    {
      uint32_t div = sci_i2c_div_shift(cks);

      /* Denominator: 32 * div * scl — use 64-bit to avoid overflow */

      uint64_t denom = (uint64_t)32u * div * scl_hz;
      if (denom == 0)
        {
          continue;
        }

      /* BRR = round(PCLK / denom) - 1  (#6 fix: avoid *1000 dance)
       * Use: brr = (pclk + denom/2) / denom - 1
       * Check pclk >= denom first to avoid underflow.
       */

      if ((uint64_t)pclk_hz < denom)
        {
          continue; /* Would give BRR < 0 */
        }

      uint64_t brr64 = ((uint64_t)pclk_hz + denom / 2u) / denom;
      if (brr64 == 0)
        {
          continue; /* Underflow guard */
        }

      brr64 -= 1u; /* Subtract 1 per formula */
      if (brr64 > SCI_I2C_BRR_MAX)
        {
          continue;
        }

      uint8_t brr = (uint8_t)brr64;

      /* Actual frequency with this BRR */

      uint32_t actual = (uint32_t)(pclk_hz / (32u * div * (brr + 1u)));

      /* Error in ppm */

      uint32_t err;
      if (actual >= scl_hz)
        {
          err = (actual - scl_hz) * 1000000u / scl_hz;
        }
      else
        {
          err = (scl_hz - actual) * 1000000u / scl_hz;
        }

      if (err < best_err)
        {
          best_err = err;
          best_cks = cks;
          best_brr = brr;
          found    = true;
        }
    }

  if (!found)
    {
      i2cerr("SCI-I2C: no valid BRR for pclk=%u scl=%u\n",
             (unsigned)pclk_hz, (unsigned)scl_hz);
      return -EINVAL;
    }

  out->cks  = best_cks;
  out->brr  = best_brr;
  out->brme = false;
  out->mddr = 0;

  /* Noise filter: SNFR=1 (1-clock filter) for I2C per FSP CCR1 write:730 */

  out->snfr = 1u;

  /* SDA output delay: IICDL=0 (no extra delay) — ICR field, separate from
   * NFCS (#5 fix: cycles_value and snfr are distinct per FSP clock_settings).
   * FSP uses pextend->clock_settings.cycles_value for ICR.IICDL.
   */

  out->cycles_value = 0u;

  /* Apply MDDR fractional correction if error exceeds threshold.
   * MDDR = round(256 * nominal_scl / actual_scl) — must be in [128..255].
   *
   * actual_scl = PCLK / (32 * div * (BRR+1))
   * target_scl is scl_hz
   * mddr = round(256 * scl_hz / actual_scl)
   */

  if (best_err > SCI_I2C_ERR_PPM_MAX)
    {
      uint32_t div    = sci_i2c_div_shift(best_cks);
      uint32_t actual = pclk_hz / (32u * div * ((uint32_t)best_brr + 1u));

      if (actual > 0)
        {
          uint32_t mddr32 = (256u * scl_hz + actual / 2u) / actual;
          if (mddr32 >= SCI_I2C_MDDR_MIN && mddr32 <= 255u)
            {
              out->mddr = (uint8_t)mddr32;
              out->brme = true;
            }
        }
    }

  i2cinfo("SCI-I2C clock: pclk=%u scl=%u → cks=%u brr=%u mddr=%u err=%uppm\n",
          (unsigned)pclk_hz, (unsigned)scl_hz,
          best_cks, best_brr, out->mddr, (unsigned)best_err);

  return 0;
}
