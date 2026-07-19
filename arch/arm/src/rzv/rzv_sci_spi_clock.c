/****************************************************************************
 * arch/arm/src/rzv/rzv_sci_spi_clock.c
 *
 * SCI-B SPI baud rate calculator.
 * Mirrors rzv_sci_i2c_clock.c structure with SPI-specific formula.
 *
 * Formula (SCI-B Simple-SPI mode, no BCP multiplier unlike I2C):
 *   SCL_hz = PCLK / (2 * (1 << (2*cks)) * (BRR + 1))
 *
 * With MDDR fractional correction:
 *   SCL_actual = SCL_nominal * (MDDR / 256)   [MDDR range 128..255]
 *
 * Review fixes:
 *   #10 CRIT — bounds-check prevents (0 - 1) underflow to 0xFFFFFFFF (#10)
 *   #2  CRIT — uses PCLK from rzv_clock_get_rate (caller supplies pclk_hz)
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

#include "hardware/rzv_sci_spi.h"
#include "rzv_sci_spi_internal.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* MDDR minimum — values below 128 are not allowed by HW */

#define SCI_SPI_MDDR_MIN        128u

/* Maximum BRR register value */

#define SCI_SPI_BRR_MAX         255u

/* Acceptable frequency error threshold: 2% (in parts-per-million) */

#define SCI_SPI_ERR_PPM_MAX     20000u   /* 2% = 20000 ppm */

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: sci_spi_div_shift
 *
 * Description:
 *   Return clock divider ratio for CKS value n.
 *   CKS=0 → 1, CKS=1 → 4, CKS=2 → 16, CKS=3 → 64.
 *   Matches SCI-B UM Table (PCLK / (1 << (2*cks))).
 *
 ****************************************************************************/

static uint32_t sci_spi_div_shift(uint8_t cks)
{
  return 1u << (2u * (uint32_t)cks);
}

static uint32_t sci_spi_error_ppm(uint32_t actual, uint32_t target)
{
  uint64_t delta;
  uint64_t error;

  delta = actual >= target ? (uint64_t)actual - target :
          (uint64_t)target - actual;
  error = delta * 1000000u / target;
  return error > UINT32_MAX ? UINT32_MAX : (uint32_t)error;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_sci_spi_calc_bitrate
 *
 * Description:
 *   Compute CCR2 clock settings for a target SPI bit rate.
 *   Tries CKS = 0..3, picks the (cks, brr) pair with minimum |error|.
 *   Uses MDDR fractional correction when it improves the selected rate.
 *
 *   SPI formula (no BCP factor unlike I2C):
 *     actual = PCLK / (2 * div * (BRR + 1))
 *     BRR    = PCLK / (2 * div * bitrate) - 1
 *
 * Input Parameters:
 *   pclk_hz - Peripheral clock in Hz (caller resolves from CPG)
 *   bitrate - Target SPI bit rate in Hz
 *   brr     - Output: BRR register value [0..255]
 *   cks     - Output: CKS field value [0..3]
 *   mddr    - Output: MDDR value [128..255] if BRME=1, else 0
 *
 * Returned Value:
 *   0 on success, -EINVAL if no supported setting is within ±2%.
 *
 ****************************************************************************/

int rzv_sci_spi_calc_bitrate(uint32_t pclk_hz, uint32_t bitrate,
                              uint8_t *brr, uint8_t *cks, uint8_t *mddr)
{
  uint8_t  best_cks  = 0;
  uint8_t  best_brr  = 0;
  uint8_t  best_mddr = 0;
  uint32_t best_err  = UINT32_MAX;
  bool     found     = false;
  uint8_t  k;

  /* (#10 fix) Reject degenerate inputs up front */

  if (bitrate < RZV_SCI_SPI_MIN_FREQUENCY ||
      bitrate > RZV_SCI_SPI_MAX_FREQUENCY || pclk_hz == 0u)
    {
      return -EINVAL;
    }

  /* Walk CKS 0..3 to find (cks, brr) with minimum frequency error.
   *
   * actual = PCLK / (2 * div * (BRR + 1))
   * BRR    = PCLK / (2 * div * bitrate) - 1
   */

  for (k = 0; k <= 3; k++)
    {
      uint32_t div = sci_spi_div_shift(k);

      /* Denominator: 2 * div * bitrate — use 64-bit to avoid overflow */

      uint64_t denom = (uint64_t)2u * div * bitrate;
      if (denom == 0u)
        {
          continue;
        }

      /* (#10 fix) Skip if pclk < denom — would give BRR < 0 */

      if ((uint64_t)pclk_hz < denom)
        {
          continue;
        }

      /* BRR = round(PCLK / denom) - 1 */

      uint64_t brr64 = ((uint64_t)pclk_hz + denom / 2u) / denom;
      if (brr64 == 0u)
        {
          continue; /* Underflow guard */
        }

      brr64 -= 1u;
      if (brr64 > SCI_SPI_BRR_MAX)
        {
          continue;
        }

      uint8_t  b      = (uint8_t)brr64;
      uint32_t actual = (uint32_t)(pclk_hz / (2u * div * (b + 1u)));

      uint32_t err = sci_spi_error_ppm(actual, bitrate);

      if (err < best_err)
        {
          best_err = err;
          best_cks = k;
          best_brr = b;
          best_mddr = 0;
          found    = true;
        }

      if (actual >= bitrate)
        {
          uint32_t modulation =
            (uint32_t)(((uint64_t)256u * bitrate + actual / 2u) / actual);

          if (modulation >= SCI_SPI_MDDR_MIN && modulation <= 255u)
            {
              uint32_t modulated =
                (uint32_t)(((uint64_t)actual * modulation) / 256u);

              err = sci_spi_error_ppm(modulated, bitrate);
              if (err < best_err)
                {
                  best_err = err;
                  best_cks = k;
                  best_brr = b;
                  best_mddr = (uint8_t)modulation;
                  found = true;
                }
            }
        }

      if (b > 0u)
        {
          uint8_t higher_brr = b - 1u;
          uint32_t higher_actual =
            (uint32_t)(pclk_hz / (2u * div * ((uint32_t)higher_brr + 1u)));
          uint32_t modulation =
            (uint32_t)(((uint64_t)256u * bitrate + higher_actual / 2u) /
                       higher_actual);

          if (modulation >= SCI_SPI_MDDR_MIN && modulation <= 255u)
            {
              uint32_t modulated =
                (uint32_t)(((uint64_t)higher_actual * modulation) / 256u);

              err = sci_spi_error_ppm(modulated, bitrate);
              if (err < best_err)
                {
                  best_err = err;
                  best_cks = k;
                  best_brr = higher_brr;
                  best_mddr = (uint8_t)modulation;
                  found = true;
                }
            }
        }
    }

  if (!found)
    {
      spierr("SCI-SPI: no valid BRR pclk=%u bitrate=%u\n",
             (unsigned)pclk_hz, (unsigned)bitrate);
      return -EINVAL;
    }

  if (best_err > SCI_SPI_ERR_PPM_MAX)
    {
      return -EINVAL;
    }

  *cks  = best_cks;
  *brr  = best_brr;
  *mddr = best_mddr;

  spiinfo("SCI-SPI clock: pclk=%u bitrate=%u → cks=%u brr=%u mddr=%u"
          " err=%uppm\n",
          (unsigned)pclk_hz, (unsigned)bitrate,
          best_cks, best_brr, *mddr, (unsigned)best_err);

  return 0;
}

/****************************************************************************
 * Name: rzv_sci_spi_actual_bitrate
 ****************************************************************************/

uint32_t rzv_sci_spi_actual_bitrate(uint32_t pclk_hz, uint8_t brr,
                                    uint8_t cks, uint8_t mddr)
{
  uint32_t div = sci_spi_div_shift(cks);
  uint32_t actual = pclk_hz / (2u * div * ((uint32_t)brr + 1u));

  if (mddr != 0u)
    {
      actual = (uint32_t)(((uint64_t)actual * mddr) / 256u);
    }

  return actual;
}
