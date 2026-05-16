/****************************************************************************
 * arch/arm/src/rzv/rzv_rproc.h
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 ****************************************************************************/

#ifndef __ARCH_ARM_SRC_RZV_RZV_RPROC_H
#define __ARCH_ARM_SRC_RZV_RZV_RPROC_H

#include <nuttx/config.h>
#include <stdint.h>

typedef void (*rzv_rproc_notify_t)(FAR void *arg, uint32_t notifyid);

int rzv_rproc_initialize(void);
int rzv_rproc_register_callback(rzv_rproc_notify_t callback, FAR void *arg);
int rzv_rproc_notify(uint32_t notifyid);

#endif /* __ARCH_ARM_SRC_RZV_RZV_RPROC_H */
