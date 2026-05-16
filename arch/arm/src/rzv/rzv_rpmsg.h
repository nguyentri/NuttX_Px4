/****************************************************************************
 * arch/arm/src/rzv/rzv_rpmsg.h
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 ****************************************************************************/

#ifndef __ARCH_ARM_SRC_RZV_RZV_RPMSG_H
#define __ARCH_ARM_SRC_RZV_RZV_RPMSG_H

#include <nuttx/config.h>

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

typedef void (*rzv_rpmsg_rxnotify_t)(FAR void *arg);

int rzv_rpmsg_initialize(rzv_rpmsg_rxnotify_t rxnotify, FAR void *arg);
void rzv_rpmsg_detach(void);
bool rzv_rpmsg_ready(void);
ssize_t rzv_rpmsg_send(FAR const char *buffer, size_t buflen);
ssize_t rzv_rpmsg_receive(FAR char *buffer, size_t buflen);

#endif /* __ARCH_ARM_SRC_RZV_RZV_RPMSG_H */
