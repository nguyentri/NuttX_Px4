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
#include <nuttx/rptun/rptun.h>   /* rptun_callback_t */

int rzv_rproc_initialize(void);
int rzv_rproc_register_callback(rptun_callback_t callback, FAR void *arg);
int rzv_rproc_notify(uint32_t notifyid);

#endif /* __ARCH_ARM_SRC_RZV_RZV_RPROC_H */
