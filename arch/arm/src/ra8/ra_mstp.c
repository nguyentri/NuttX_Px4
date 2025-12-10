/****************************************************************************
 * arch/arm/src/ra8/ra_mstp.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
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

#include "arm_internal.h"
#include "chip.h"
#include "hardware/ra_memorymap.h"
#include "ra_mstp.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Module stop control register definitions */
#define RA_MSTP_REG_A     0
#define RA_MSTP_REG_B     1
#define RA_MSTP_REG_C     2
#define RA_MSTP_REG_D     3
#define RA_MSTP_REG_E     4

/****************************************************************************
 * Private Data
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_mstp_get_regaddr
 *
 * Description:
 *   Get MSTP register address from module ID
 *
 ****************************************************************************/

static uint32_t ra_mstp_get_regaddr(ra_mstp_module_t module)
{
  /* MSTPCRA: NPU, DMAC, DTC */
  if (module >= RA_MSTP_NPU && module <= RA_MSTP_DTC)
    {
      return R_MSTP_MSTPCRA;
    }
  /* MSTPCRB: SCI, SPI, OSPI, USB, IIC, CAN, etc. */
  else if (module >= RA_MSTP_SCI0 && module <= RA_MSTP_CAN1)
    {
      return R_MSTP_MSTPCRB;
    }
  /* MSTPCRC: CANFD, MIPI, Graphics, ELC, etc. */
  else if (module >= RA_MSTP_LAYER3_SWITCH && module <= RA_MSTP_CAC)
    {
      return R_MSTP_MSTPCRC;
    }
  /* MSTPCRD: ADC, DAC, ACMP, POEG, AGT, RTC */
  else if (module >= RA_MSTP_ACMPHS0 && module <= RA_MSTP_AGT1)
    {
      return R_MSTP_MSTPCRD;
    }
  /* MSTPCRE: GPT timers, ULPT */
  else if (module >= RA_MSTP_GPT0 && module <= RA_MSTP_ULPT1)
    {
      return R_MSTP_MSTPCRE;
    }
  else
    {
      return 0; /* Invalid module */
    }
}

/****************************************************************************
 * Name: ra_mstp_get_bitmask
 *
 * Description:
 *   Get bit mask for specific module
 *
 ****************************************************************************/

static uint32_t ra_mstp_get_bitmask(ra_mstp_module_t module)
{
  switch (module)
    {
      /* MSTPCRA register modules */
      case RA_MSTP_NPU:           return R_MSTP_MSTPCRA_MSTPA16;
#ifndef CONFIG_RA_CPU_CORE
      case RA_MSTP_DMAC:          return R_MSTP_MSTPCRA_MSTPA22;
#elif (CONFIG_RA_CPU_CORE == 0)
      case RA_MSTP_DMAC:          return R_MSTP_MSTPCRA_MSTPA22;
#else
      case RA_MSTP_DMAC:          return R_MSTP_MSTPCRA_MSTPA23;
#endif
      case RA_MSTP_DTC:           return R_MSTP_MSTPCRA_MSTPA22;

      /* MSTPCRB register modules */
      case RA_MSTP_SCI0:          return R_MSTP_MSTPCRB_MSTPB31;
      case RA_MSTP_SCI1:          return R_MSTP_MSTPCRB_MSTPB30;
      case RA_MSTP_SCI2:          return R_MSTP_MSTPCRB_MSTPB29;
      case RA_MSTP_SCI3:          return R_MSTP_MSTPCRB_MSTPB28;
      case RA_MSTP_SCI4:          return R_MSTP_MSTPCRB_MSTPB27;
      case RA_MSTP_SCI5:          return R_MSTP_MSTPCRB_MSTPB26;
      case RA_MSTP_SCI6:          return R_MSTP_MSTPCRB_MSTPB25;
      case RA_MSTP_SCI7:          return R_MSTP_MSTPCRB_MSTPB24;
      case RA_MSTP_SCI8:          return R_MSTP_MSTPCRB_MSTPB23;
      case RA_MSTP_SCI9:          return R_MSTP_MSTPCRB_MSTPB22;
      case RA_MSTP_SPI0:          return R_MSTP_MSTPCRB_MSTPB19;
      case RA_MSTP_SPI1:          return R_MSTP_MSTPCRB_MSTPB18;
      case RA_MSTP_OSPI1:         return R_MSTP_MSTPCRB_MSTPB17;
      case RA_MSTP_OSPI0:         return R_MSTP_MSTPCRB_MSTPB16;
      case RA_MSTP_EPTPC:         return R_MSTP_MSTPCRB_MSTPB13;
      case RA_MSTP_USBHS:         return R_MSTP_MSTPCRB_MSTPB12;
      case RA_MSTP_USBFS:         return R_MSTP_MSTPCRB_MSTPB11;
      case RA_MSTP_IIC0:          return R_MSTP_MSTPCRB_MSTPB9;
      case RA_MSTP_IIC1:          return R_MSTP_MSTPCRB_MSTPB8;
      case RA_MSTP_IIC2:          return R_MSTP_MSTPCRB_MSTPB7;
      case RA_MSTP_QSPI:          return R_MSTP_MSTPCRB_MSTPB6;
      case RA_MSTP_IRDA:          return R_MSTP_MSTPCRB_MSTPB5;
      case RA_MSTP_I3C:           return R_MSTP_MSTPCRB_MSTPB4;
      case RA_MSTP_CEC:           return R_MSTP_MSTPCRB_MSTPB3;
      case RA_MSTP_CAN0:          return R_MSTP_MSTPCRB_MSTPB2;
      case RA_MSTP_CAN1:          return R_MSTP_MSTPCRB_MSTPB1;

      /* MSTPCRC register modules */
      case RA_MSTP_LAYER3_SWITCH: return R_MSTP_MSTPCRC_MSTPC30;
      case RA_MSTP_ETHER_PHY_CLK: return R_MSTP_MSTPCRC_MSTPC28;
      case RA_MSTP_CANFD0:        return R_MSTP_MSTPCRC_MSTPC27;
      case RA_MSTP_CANFD1:        return R_MSTP_MSTPCRC_MSTPC26;
      case RA_MSTP_PDM:           return R_MSTP_MSTPCRC_MSTPC24;
      case RA_MSTP_IIRFA:         return R_MSTP_MSTPCRC_MSTPC21;
      case RA_MSTP_TFU:           return R_MSTP_MSTPCRC_MSTPC20;
      case RA_MSTP_MIPI_CSI:      return R_MSTP_MSTPCRC_MSTPC17;
      case RA_MSTP_CEU:           return R_MSTP_MSTPCRC_MSTPC16;
      case RA_MSTP_VIN:           return R_MSTP_MSTPCRC_MSTPC16;
      case RA_MSTP_MACL:          return R_MSTP_MSTPCRC_MSTPC15;
      case RA_MSTP_ELC:           return R_MSTP_MSTPCRC_MSTPC14;
      case RA_MSTP_DOC:           return R_MSTP_MSTPCRC_MSTPC13;
      case RA_MSTP_SDHI:          return R_MSTP_MSTPCRC_MSTPC12;
      case RA_MSTP_MIPI_DSI:      return R_MSTP_MSTPCRC_MSTPC10;
      case RA_MSTP_SRC:           return R_MSTP_MSTPCRC_MSTPC9;
      case RA_MSTP_SSIE0:         return R_MSTP_MSTPCRC_MSTPC8;
      case RA_MSTP_SSIE1:         return R_MSTP_MSTPCRC_MSTPC7;
      case RA_MSTP_DRW:           return R_MSTP_MSTPCRC_MSTPC6;
      case RA_MSTP_JPEG:          return R_MSTP_MSTPCRC_MSTPC5;
      case RA_MSTP_GLCDC:         return R_MSTP_MSTPCRC_MSTPC4;
      case RA_MSTP_CTSU:          return R_MSTP_MSTPCRC_MSTPC3;
      case RA_MSTP_PDC:           return R_MSTP_MSTPCRC_MSTPC2;
      case RA_MSTP_CRC:           return R_MSTP_MSTPCRC_MSTPC1;
      case RA_MSTP_CAC:           return R_MSTP_MSTPCRC_MSTPC0;

      /* MSTPCRD register modules */
      case RA_MSTP_ACMPHS0:       return R_MSTP_MSTPCRD_MSTPD28;
      case RA_MSTP_ACMPHS1:       return R_MSTP_MSTPCRD_MSTPD27;
      case RA_MSTP_ACMPHS2:       return R_MSTP_MSTPCRD_MSTPD26;
      case RA_MSTP_ACMPHS3:       return R_MSTP_MSTPCRD_MSTPD25;
      case RA_MSTP_RTC:           return R_MSTP_MSTPCRD_MSTPD23;
      case RA_MSTP_TSN:           return R_MSTP_MSTPCRD_MSTPD22;
      case RA_MSTP_ADC0:          return R_MSTP_MSTPCRD_MSTPD21;
      case RA_MSTP_ADC1:          return R_MSTP_MSTPCRD_MSTPD20;
      case RA_MSTP_DAC0:          return R_MSTP_MSTPCRD_MSTPD20;
      case RA_MSTP_DAC1:          return R_MSTP_MSTPCRD_MSTPD19;
      case RA_MSTP_POEG0:         return R_MSTP_MSTPCRD_MSTPD14;
      case RA_MSTP_POEG1:         return R_MSTP_MSTPCRD_MSTPD13;
      case RA_MSTP_POEG2:         return R_MSTP_MSTPCRD_MSTPD12;
      case RA_MSTP_POEG3:         return R_MSTP_MSTPCRD_MSTPD11;
      case RA_MSTP_GPT_PDG:       return R_MSTP_MSTPCRD_MSTPD6;
      case RA_MSTP_AGT0:          return R_MSTP_MSTPCRD_MSTPD5;
      case RA_MSTP_AGT1:          return R_MSTP_MSTPCRD_MSTPD4;

      /* MSTPCRE register modules */
      case RA_MSTP_GPT0:          return R_MSTP_MSTPCRE_MSTPE31;
      case RA_MSTP_GPT1:          return R_MSTP_MSTPCRE_MSTPE30;
      case RA_MSTP_GPT2:          return R_MSTP_MSTPCRE_MSTPE29;
      case RA_MSTP_GPT3:          return R_MSTP_MSTPCRE_MSTPE28;
      case RA_MSTP_GPT4:          return R_MSTP_MSTPCRE_MSTPE27;
      case RA_MSTP_GPT5:          return R_MSTP_MSTPCRE_MSTPE26;
      case RA_MSTP_GPT6:          return R_MSTP_MSTPCRE_MSTPE25;
      case RA_MSTP_GPT7:          return R_MSTP_MSTPCRE_MSTPE24;
      case RA_MSTP_GPT8:          return R_MSTP_MSTPCRE_MSTPE23;
      case RA_MSTP_GPT9:          return R_MSTP_MSTPCRE_MSTPE22;
      case RA_MSTP_GPT10:         return R_MSTP_MSTPCRE_MSTPE21;
      case RA_MSTP_GPT11:         return R_MSTP_MSTPCRE_MSTPE20;
      case RA_MSTP_GPT12:         return R_MSTP_MSTPCRE_MSTPE19;
      case RA_MSTP_GPT13:         return R_MSTP_MSTPCRE_MSTPE18;
      case RA_MSTP_ULPT0:         return R_MSTP_MSTPCRE_MSTPE9;
      case RA_MSTP_ULPT1:         return R_MSTP_MSTPCRE_MSTPE8;

      default:
        return 0;
    }
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: ra_mstp_initialize
 *
 * Description:
 *   Initialize the MSTP driver
 *
 ****************************************************************************/

void ra_mstp_initialize(void)
{
  /* All modules start in stopped state by default in hardware */
  /* No additional initialization required */
}

/****************************************************************************
 * Name: ra_mstp_start
 *
 * Description:
 *   Start (enable clock for) a peripheral module
 *
 ****************************************************************************/

int ra_mstp_start(ra_mstp_module_t module)
{
  uint32_t regaddr;
  uint32_t bitmask;

  regaddr = ra_mstp_get_regaddr(module);
  if (regaddr == 0)
    {
      return -EINVAL;
    }

  bitmask = ra_mstp_get_bitmask(module);
  if (bitmask == 0)
    {
      return -EINVAL;
    }

  /* Clear the stop bit to start the module */
  modifyreg32(regaddr, bitmask, 0);

  return OK;
}

/****************************************************************************
 * Name: ra_mstp_stop
 *
 * Description:
 *   Stop (disable clock for) a peripheral module
 *
 ****************************************************************************/

int ra_mstp_stop(ra_mstp_module_t module)
{
  uint32_t regaddr;
  uint32_t bitmask;

  regaddr = ra_mstp_get_regaddr(module);
  if (regaddr == 0)
    {
      return -EINVAL;
    }

  bitmask = ra_mstp_get_bitmask(module);
  if (bitmask == 0)
    {
      return -EINVAL;
    }

  /* Set the stop bit to stop the module */
  modifyreg32(regaddr, 0, bitmask);

  return OK;
}

/****************************************************************************
 * Name: ra_mstp_is_stopped
 *
 * Description:
 *   Check if a peripheral module is stopped
 *
 ****************************************************************************/

bool ra_mstp_is_stopped(ra_mstp_module_t module)
{
  uint32_t regaddr;
  uint32_t bitmask;
  uint32_t regval;

  regaddr = ra_mstp_get_regaddr(module);
  if (regaddr == 0)
    {
      return true; /* Invalid module is considered stopped */
    }

  bitmask = ra_mstp_get_bitmask(module);
  if (bitmask == 0)
    {
      return true; /* Invalid module is considered stopped */
    }

  regval = getreg32(regaddr);
  return (regval & bitmask) != 0;
}

/****************************************************************************
 * Name: ra_mstp_start_multiple
 *
 * Description:
 *   Start multiple modules atomically
 *
 ****************************************************************************/

int ra_mstp_start_multiple(const ra_mstp_module_t *modules, int count)
{
  uint32_t rega_mask = 0;
  uint32_t regb_mask = 0;
  uint32_t regc_mask = 0;
  uint32_t regd_mask = 0;
  uint32_t rege_mask = 0;
  int i;

  if (modules == NULL || count <= 0)
    {
      return -EINVAL;
    }

  /* Build masks for each register */
  for (i = 0; i < count; i++)
    {
      uint32_t regaddr = ra_mstp_get_regaddr(modules[i]);
      uint32_t bitmask = ra_mstp_get_bitmask(modules[i]);

      if (regaddr == 0 || bitmask == 0)
        {
          return -EINVAL;
        }

      if (regaddr == R_MSTP_MSTPCRA)
        {
          rega_mask |= bitmask;
        }
      else if (regaddr == R_MSTP_MSTPCRB)
        {
          regb_mask |= bitmask;
        }
      else if (regaddr == R_MSTP_MSTPCRC)
        {
          regc_mask |= bitmask;
        }
      else if (regaddr == R_MSTP_MSTPCRD)
        {
          regd_mask |= bitmask;
        }
      else if (regaddr == R_MSTP_MSTPCRE)
        {
          rege_mask |= bitmask;
        }
    }

  /* Apply masks atomically */
  if (rega_mask != 0)
    {
      modifyreg32(R_MSTP_MSTPCRA, rega_mask, 0);
    }

  if (regb_mask != 0)
    {
      modifyreg32(R_MSTP_MSTPCRB, regb_mask, 0);
    }

  if (regc_mask != 0)
    {
      modifyreg32(R_MSTP_MSTPCRC, regc_mask, 0);
    }

  if (regd_mask != 0)
    {
      modifyreg32(R_MSTP_MSTPCRD, regd_mask, 0);
    }

  if (rege_mask != 0)
    {
      modifyreg32(R_MSTP_MSTPCRE, rege_mask, 0);
    }

  return OK;
}

/****************************************************************************
 * Name: ra_mstp_stop_multiple
 *
 * Description:
 *   Stop multiple modules atomically
 *
 ****************************************************************************/

int ra_mstp_stop_multiple(const ra_mstp_module_t *modules, int count)
{
  uint32_t rega_mask = 0;
  uint32_t regb_mask = 0;
  uint32_t regc_mask = 0;
  uint32_t regd_mask = 0;
  uint32_t rege_mask = 0;
  int i;

  if (modules == NULL || count <= 0)
    {
      return -EINVAL;
    }

  /* Build masks for each register */
  for (i = 0; i < count; i++)
    {
      uint32_t regaddr = ra_mstp_get_regaddr(modules[i]);
      uint32_t bitmask = ra_mstp_get_bitmask(modules[i]);

      if (regaddr == 0 || bitmask == 0)
        {
          return -EINVAL;
        }

      if (regaddr == R_MSTP_MSTPCRA)
        {
          rega_mask |= bitmask;
        }
      else if (regaddr == R_MSTP_MSTPCRB)
        {
          regb_mask |= bitmask;
        }
      else if (regaddr == R_MSTP_MSTPCRC)
        {
          regc_mask |= bitmask;
        }
      else if (regaddr == R_MSTP_MSTPCRD)
        {
          regd_mask |= bitmask;
        }
      else if (regaddr == R_MSTP_MSTPCRE)
        {
          rege_mask |= bitmask;
        }
    }

  /* Apply masks atomically */
  if (rega_mask != 0)
    {
      modifyreg32(R_MSTP_MSTPCRA, 0, rega_mask);
    }

  if (regb_mask != 0)
    {
      modifyreg32(R_MSTP_MSTPCRB, 0, regb_mask);
    }

  if (regc_mask != 0)
    {
      modifyreg32(R_MSTP_MSTPCRC, 0, regc_mask);
    }

  if (regd_mask != 0)
    {
      modifyreg32(R_MSTP_MSTPCRD, 0, regd_mask);
    }

  if (rege_mask != 0)
    {
      modifyreg32(R_MSTP_MSTPCRE, 0, rege_mask);
    }

  return OK;
}

/****************************************************************************
 * Name: ra_mstp_get_status
 *
 * Description:
 *   Get the current MSTP register status
 *
 ****************************************************************************/

void ra_mstp_get_status(ra_mstp_status_t *status)
{
  if (status != NULL)
    {
      status->mstpcra = getreg32(R_MSTP_MSTPCRA);
      status->mstpcrb = getreg32(R_MSTP_MSTPCRB);
      status->mstpcrc = getreg32(R_MSTP_MSTPCRC);
      status->mstpcrd = getreg32(R_MSTP_MSTPCRD);
      status->mstpcre = getreg32(R_MSTP_MSTPCRE);
    }
}
