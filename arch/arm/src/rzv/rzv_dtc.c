/****************************************************************************
 * arch/arm/src/rzv/rzv_dtc.c
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
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/irq.h>
#include <nuttx/arch.h>
#include <nuttx/kmalloc.h>

#include <arch/board/board.h>

#include "arm_internal.h"
#include "chip.h"
#include "rzv_dtc.h"
#include "rzv_icu.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define DTC_OPEN_ID             (0x44544300)  /* "DTC" in ASCII */
#define DTC_ALIGNMENT_CHECK(addr, size) \
  (((uintptr_t)(addr) & ((size) - 1)) == 0)

/* DTC Control Register values */

#define DTC_DTCCR_RRS_ENABLE    (0x18)
#define DTC_DTCCR_RRS_DISABLE   (0x08)

#define RZV_DTC_SET_VECTOR_RETRIES 3

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* DTC context control structure */

typedef struct rzv_dtc_ctrl_s
{
  uint32_t             open_id;        /* Open identifier */
  bool                 in_use;         /* Context in use flag */
  rzv_dtc_config_t     config;         /* Configuration */
  rzv_dtc_info_t       info;           /* Transfer information */
  int                  irq;            /* IRQ number */
  bool                 slot_allocated; /* True if we allocated an ICU slot for trigger */
  int                  trigger_irq;    /* IRQ number allocated for elc_src -> slot mapping */
} rzv_dtc_ctrl_t;

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* DTC context control blocks */

rzv_dtc_ctrl_t g_dtc_contexts[RZV_DTC_MAX_CONTEXTS];

/* DTC vector table (aligned to 1024 bytes) */

rzv_dtc_info_t *g_dtc_vector_table[RZV_DTC_VECTOR_TABLE_ENTRIES]
  __attribute__((section(".dtc_vector_table")))
  __attribute__((aligned(RZV_DTC_VECTOR_TABLE_ALIGN)));

/* DTC module initialized flag */

static bool g_dtc_initialized = false;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_dtc_validate_config
 *
 * Description:
 *   Validate DTC configuration parameters
 *
 * Input Parameters:
 *   config - DTC configuration
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

static int rzv_dtc_validate_config(const rzv_dtc_config_t *config)
{
  /* Check configuration pointer */

  if (config == NULL)
    {
      return -EINVAL;
    }

  /* Check transfer mode */

  if (config->mode > RZV_DTC_MODE_BLOCK)
    {
      return -EINVAL;
    }

  /* Check transfer size */

  if (config->size > RZV_DTC_SIZE_LONG)
    {
      return -EINVAL;
    }

  /* Check address modes */

  if (config->src_addr_mode > RZV_DTC_ADDR_DECR ||
      config->dest_addr_mode > RZV_DTC_ADDR_DECR)
    {
      return -EINVAL;
    }

  /* Check addresses are not null */

  if (config->src_addr == 0 || config->dest_addr == 0)
    {
      return -EINVAL;
    }

  /* Check alignment based on transfer size */

  uint32_t align_mask = (1 << config->size) - 1;
  if ((config->src_addr & align_mask) || (config->dest_addr & align_mask))
    {
      return -EINVAL;
    }

  /* Check transfer count limits */

  switch (config->mode)
    {
      case RZV_DTC_MODE_NORMAL:
        if (config->transfer_count == 0 ||
            config->transfer_count > RZV_DTC_MAX_NORMAL_LENGTH)
          {
            return -EINVAL;
          }
        break;

      case RZV_DTC_MODE_REPEAT:
        if (config->transfer_count == 0 ||
            config->transfer_count > RZV_DTC_MAX_REPEAT_LENGTH)
          {
            return -EINVAL;
          }
        break;

      case RZV_DTC_MODE_BLOCK:
        if (config->transfer_count == 0 ||
            config->transfer_count > RZV_DTC_MAX_BLOCK_LENGTH ||
            config->block_count == 0 ||
            config->block_count > RZV_DTC_MAX_BLOCK_COUNT)
          {
            return -EINVAL;
          }
        break;
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_dtc_setup_transfer_info
 *
 * Description:
 *   Setup DTC transfer information structure
 *
 * Input Parameters:
 *   ctrl - DTC control block
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

static int rzv_dtc_setup_transfer_info(rzv_dtc_ctrl_t *ctrl)
{
  rzv_dtc_info_t *info = &ctrl->info;
  const rzv_dtc_config_t *config = &ctrl->config;

  /* Clear transfer information */

  memset(info, 0, sizeof(rzv_dtc_info_t));

  /* Setup Mode Register A - source addressing only */

  info->mra = (config->mode << RZV_DTC_MRA_MD_SHIFT) |
              (config->size << RZV_DTC_MRA_SZ_SHIFT) |
              (config->src_addr_mode << RZV_DTC_MRA_SM_SHIFT);

  /* Setup Mode Register B - destination addressing */

  info->mrb = (config->dest_addr_mode << RZV_DTC_MRB_DM_SHIFT);

  /* Setup addresses */

  info->sar = config->src_addr;
  info->dar = config->dest_addr;

  /* Setup transfer counts */

  switch (config->mode)
    {
      case RZV_DTC_MODE_NORMAL:
        info->cra = config->transfer_count;
        info->crb = 0;
        break;

      case RZV_DTC_MODE_REPEAT:
        info->cra = config->transfer_count;
        info->crb = 0;
        break;

      case RZV_DTC_MODE_BLOCK:
        info->cra = config->transfer_count;
        info->crb = config->block_count;
        break;
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_dtc_interrupt_handler
 *
 * Description:
 *   DTC interrupt handler
 *
 * Input Parameters:
 *   irq - IRQ number
 *   context - Interrupt context
 *   arg - Argument passed to handler
 *
 * Returned Value:
 *   OK on success
 *
 ****************************************************************************/

static int rzv_dtc_interrupt_handler(int irq, void *context, void *arg)
{
  rzv_dtc_ctrl_t *ctrl = (rzv_dtc_ctrl_t *)arg;

  if (ctrl && ctrl->config.callback)
    {
      /* Read remaining count to determine if transfer completed */

      uint32_t remaining = rzv_dtc_get_remaining_count(ctrl);

      if (remaining == 0)
        {
          ctrl->config.callback(ctrl, RZV_DTC_EVENT_END, ctrl->config.user_data);
        }
      else
        {
          ctrl->config.callback(ctrl, RZV_DTC_EVENT_ERROR, ctrl->config.user_data);
        }
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_dtc_find_free_context
 *
 * Description:
 *   Find a free DTC context
 *
 * Returned Value:
 *   Pointer to free context or NULL if none available
 *
 ****************************************************************************/

static rzv_dtc_ctrl_t *rzv_dtc_find_free_context(void)
{
  for (int i = 0; i < RZV_DTC_MAX_CONTEXTS; i++)
    {
      if (!g_dtc_contexts[i].in_use)
        {
          return &g_dtc_contexts[i];
        }
    }

  return NULL;
}

/****************************************************************************
 * Name: rzv_dtc_wait_for_completion
 *
 * Description:
 *   Wait for DTC transfer to complete
 *
 * Input Parameters:
 *   irq_slot - IRQ slot number associated with the DTC transfer
 *
 * Returned Value:
 *   OK on success, -ETIMEDOUT on timeout
 *
 ****************************************************************************/

#define RZV_DTC_WAIT_USEC_TIMEOUT (1000000) /* 1 second */

static int rzv_dtc_wait_for_completion(int irq_slot)
{
  unsigned int waited = 0;
  uint32_t val;
  uint32_t vecn_mask = RZV_DTC_DTCSTS_VECN_MASK;
  uint32_t act_mask  = RZV_DTC_DTCSTS_ACT;

  /* Read initial value */

  val = getreg16(RZV_DTC_DTCSTS);

  /* Wait while ACT is set and vector number matches the slot */

  while ((val & act_mask) && ((val & vecn_mask) == (uint32_t)irq_slot))
    {
      /* Check for timeout */

      if (waited >= RZV_DTC_WAIT_USEC_TIMEOUT)
        {
          return -ETIMEDOUT;
        }

      up_udelay(10);
      waited += 10;
      val = getreg16(RZV_DTC_DTCSTS);
    }

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: rzv_dtc_initialize
 *
 * Description:
 *   Initialize DTC module
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

int rzv_dtc_initialize(void)
{
  if (g_dtc_initialized)
    {
      return OK;
    }

  /* Clear all contexts */

  memset(g_dtc_contexts, 0, sizeof(g_dtc_contexts));

  /* Clear vector table */

  memset(g_dtc_vector_table, 0, sizeof(g_dtc_vector_table));

  /* Set vector table base address */

  putreg32((uint32_t)g_dtc_vector_table, RZV_DTC_DTCVBR);

  /* Start the DTC module by setting DTCST.DTCST = 1 */

  putreg8(1, RZV_DTC_DTCST);

  g_dtc_initialized = true;

  return OK;
}

/****************************************************************************
 * Name: rzv_dtc_open
 *
 * Description:
 *   Open DTC transfer channel
 *
 * Input Parameters:
 *   handle - Pointer to store handle
 *   config - DTC configuration
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

int rzv_dtc_open(rzv_dtc_handle_t *handle, const rzv_dtc_config_t *config)
{
  rzv_dtc_ctrl_t *ctrl;
  int ret;

  if (handle == NULL || config == NULL)
    {
      return -EINVAL;
    }

  /* Initialize module if needed */

  ret = rzv_dtc_initialize();
  if (ret < 0)
    {
      return ret;
    }

  /* Validate configuration */

  ret = rzv_dtc_validate_config(config);
  if (ret < 0)
    {
      return ret;
    }

  /* Find free context */

  ctrl = rzv_dtc_find_free_context();
  if (ctrl == NULL)
    {
      return -ENOMEM;
    }

  /* Initialize control defaults for this context */

  ctrl->slot_allocated = false;
  ctrl->trigger_irq = -1;
  ctrl->irq = -1;

  /* Copy configuration */

  memcpy(&ctrl->config, config, sizeof(rzv_dtc_config_t));

  /* Setup transfer information */

  ret = rzv_dtc_setup_transfer_info(ctrl);
  if (ret < 0)
    {
      return ret;
    }

  /* Setup hardware trigger if used */

  if (!config->software_trigger && (config->irq_src >= 0 || config->elc_src >= 0))
    {
      int icu_slot = -1;
      int irq_num = -1;

      /* Prefer direct IRQ number if provided */

      if (config->irq_src >= 0)
        {
          irq_num = config->irq_src;
          icu_slot = irq_num - RZV_IRQ_FIRST;
        }
      else if (config->elc_src >= 0)
        {
          /* Allocate a dynamic ICU slot for this ELC event */

          irq_num = rzv_icu_allocate_dynamic_irq(config->elc_src);
          if (irq_num < 0)
            {
              return irq_num;
            }

          ctrl->slot_allocated = true;
          ctrl->trigger_irq = irq_num;
          icu_slot = irq_num - RZV_IRQ_FIRST;
        }

      if (icu_slot >= 0 && icu_slot < RZV_DTC_VECTOR_TABLE_ENTRIES)
        {
          /* Set DTC vector for this ICU slot */

          ret = rzv_dtc_set_vector(icu_slot, &ctrl->info);
          if (ret < 0)
            {
              if (ctrl->slot_allocated)
                {
                  rzv_icu_free_dynamic_irq(ctrl->trigger_irq);
                }
              return ret;
            }

          ctrl->irq = irq_num;

          /* Attach interrupt handler if callback provided */

          if (config->callback)
            {
              ret = irq_attach(irq_num, rzv_dtc_interrupt_handler, ctrl);
              if (ret < 0)
                {
                  rzv_dtc_clear_vector(icu_slot);
                  if (ctrl->slot_allocated)
                    {
                      rzv_icu_free_dynamic_irq(ctrl->trigger_irq);
                    }
                  return ret;
                }
            }
        }
    }

  /* Mark context as in use */

  ctrl->in_use = true;
  ctrl->open_id = DTC_OPEN_ID;

  *handle = ctrl;
  return OK;
}

/****************************************************************************
 * Name: rzv_dtc_close
 *
 * Description:
 *   Close DTC transfer channel
 *
 * Input Parameters:
 *   handle - DTC handle
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

int rzv_dtc_close(rzv_dtc_handle_t handle)
{
  rzv_dtc_ctrl_t *ctrl = (rzv_dtc_ctrl_t *)handle;

  if (ctrl == NULL)
    {
      return -EINVAL;
    }

  if (!ctrl->in_use || ctrl->open_id != DTC_OPEN_ID)
    {
      return -EINVAL;
    }

  /* Disable DTC transfer */

  rzv_dtc_disable(handle);

  /* Detach interrupt if attached */

  if (ctrl->irq >= 0)
    {
      int icu_slot = ctrl->irq - RZV_IRQ_FIRST;

      if (ctrl->config.callback)
        {
          irq_detach(ctrl->irq);
        }

      /* Clear vector table entry */

      rzv_dtc_clear_vector(icu_slot);

      /* Free ICU slot if we allocated it */

      if (ctrl->slot_allocated && ctrl->trigger_irq >= 0)
        {
          rzv_icu_free_dynamic_irq(ctrl->trigger_irq);
        }
    }

  /* Mark context as free */

  ctrl->in_use = false;
  ctrl->open_id = 0;

  return OK;
}

/****************************************************************************
 * Name: rzv_dtc_enable
 *
 * Description:
 *   Enable DTC transfer channel
 *
 * Input Parameters:
 *   handle - DTC handle
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

int rzv_dtc_enable(rzv_dtc_handle_t handle)
{
  rzv_dtc_ctrl_t *ctrl = (rzv_dtc_ctrl_t *)handle;

  if (ctrl == NULL || !ctrl->in_use)
    {
      return -EINVAL;
    }

  /* Enable IRQ if hardware triggered */

  if (ctrl->irq >= 0)
    {
      up_enable_irq(ctrl->irq);
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_dtc_disable
 *
 * Description:
 *   Disable DTC transfer channel
 *
 * Input Parameters:
 *   handle - DTC handle
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

int rzv_dtc_disable(rzv_dtc_handle_t handle)
{
  rzv_dtc_ctrl_t *ctrl = (rzv_dtc_ctrl_t *)handle;

  if (ctrl == NULL || !ctrl->in_use)
    {
      return -EINVAL;
    }

  /* Disable IRQ if hardware triggered */

  if (ctrl->irq >= 0)
    {
      up_disable_irq(ctrl->irq);
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_dtc_software_start
 *
 * Description:
 *   Start DTC transfer by software trigger
 *
 * Input Parameters:
 *   handle - DTC handle
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

int rzv_dtc_software_start(rzv_dtc_handle_t handle)
{
  rzv_dtc_ctrl_t *ctrl = (rzv_dtc_ctrl_t *)handle;

  if (ctrl == NULL || !ctrl->in_use)
    {
      return -EINVAL;
    }

  if (!ctrl->config.software_trigger)
    {
      return -ENOTSUP;
    }

  /* Software start not directly supported by hardware in standard way */
  /* Application must trigger via interrupt source or use DMAC instead */

  return -ENOTSUP;
}

/****************************************************************************
 * Name: rzv_dtc_reset
 *
 * Description:
 *   Reset DTC transfer parameters
 *
 * Input Parameters:
 *   handle - DTC handle
 *   src_addr - New source address
 *   dest_addr - New destination address
 *   transfer_count - New transfer count
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

int rzv_dtc_reset(rzv_dtc_handle_t handle, uint32_t src_addr,
                  uint32_t dest_addr, uint32_t transfer_count)
{
  rzv_dtc_ctrl_t *ctrl = (rzv_dtc_ctrl_t *)handle;

  if (ctrl == NULL || !ctrl->in_use)
    {
      return -EINVAL;
    }

  /* Validate addresses */

  if (src_addr == 0 || dest_addr == 0 || transfer_count == 0)
    {
      return -EINVAL;
    }

  /* Check alignment */

  uint32_t align_mask = (1 << ctrl->config.size) - 1;
  if ((src_addr & align_mask) || (dest_addr & align_mask))
    {
      return -EINVAL;
    }

  /* Check transfer count limits */

  switch (ctrl->config.mode)
    {
      case RZV_DTC_MODE_NORMAL:
        if (transfer_count > RZV_DTC_MAX_NORMAL_LENGTH)
          {
            return -EINVAL;
          }
        break;

      case RZV_DTC_MODE_REPEAT:
        if (transfer_count > RZV_DTC_MAX_REPEAT_LENGTH)
          {
            return -EINVAL;
          }
        break;

      case RZV_DTC_MODE_BLOCK:
        if (transfer_count > RZV_DTC_MAX_BLOCK_LENGTH)
          {
            return -EINVAL;
          }
        break;
    }

  /* Update configuration */

  ctrl->config.src_addr = src_addr;
  ctrl->config.dest_addr = dest_addr;
  ctrl->config.transfer_count = transfer_count;

  /* Update transfer info */

  ctrl->info.sar = src_addr;
  ctrl->info.dar = dest_addr;
  ctrl->info.cra = transfer_count;

  /* If hardware triggered, update vector table */

  if (ctrl->irq >= 0)
    {
      int icu_slot = ctrl->irq - RZV_IRQ_FIRST;
      rzv_dtc_set_vector(icu_slot, &ctrl->info);
    }

  return OK;
}

/****************************************************************************
 * Name: rzv_dtc_get_remaining_count
 *
 * Description:
 *   Get remaining transfer count
 *
 * Input Parameters:
 *   handle - DTC handle
 *
 * Returned Value:
 *   Remaining count, or 0 if transfer is complete or error
 *
 ****************************************************************************/

uint32_t rzv_dtc_get_remaining_count(rzv_dtc_handle_t handle)
{
  rzv_dtc_ctrl_t *ctrl = (rzv_dtc_ctrl_t *)handle;

  if (ctrl == NULL || !ctrl->in_use)
    {
      return 0;
    }

  /* Return the current count from transfer info */

  return ctrl->info.cra;
}

/****************************************************************************
 * Name: rzv_dtc_set_vector
 *
 * Description:
 *   Set DTC vector table entry
 *
 * Input Parameters:
 *   icu_slot - ICU slot number
 *   transfer_info - Transfer information structure
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

int rzv_dtc_set_vector(int icu_slot, rzv_dtc_info_t *transfer_info)
{
  if (icu_slot < 0 || icu_slot >= RZV_DTC_VECTOR_TABLE_ENTRIES)
    {
      return -EINVAL;
    }

  if (transfer_info == NULL)
    {
      return -EINVAL;
    }

  /* Disable interrupts while updating vector table */

  irqstate_t flags = enter_critical_section();

  /* Set vector table entry to point to transfer info */

  g_dtc_vector_table[icu_slot] = transfer_info;

  /* Ensure write completes */

  ARM_DSB();
  ARM_ISB();

  leave_critical_section(flags);

  return OK;
}

/****************************************************************************
 * Name: rzv_dtc_clear_vector
 *
 * Description:
 *   Clear DTC vector table entry
 *
 * Input Parameters:
 *   icu_slot - ICU slot number
 *
 * Returned Value:
 *   OK on success; a negated errno on failure
 *
 ****************************************************************************/

int rzv_dtc_clear_vector(int icu_slot)
{
  if (icu_slot < 0 || icu_slot >= RZV_DTC_VECTOR_TABLE_ENTRIES)
    {
      return -EINVAL;
    }

  /* Disable interrupts while updating vector table */

  irqstate_t flags = enter_critical_section();

  /* Clear vector table entry */

  g_dtc_vector_table[icu_slot] = NULL;

  /* Ensure write completes */

  ARM_DSB();
  ARM_ISB();

  leave_critical_section(flags);

  return OK;
}