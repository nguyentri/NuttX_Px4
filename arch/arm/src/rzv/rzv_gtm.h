/****************************************************************************
 * arch/arm/src/rzv/rzv_gtm.h
 *
 * Public API for RZV GTM (OS Timer) support.
 */

#ifndef __ARCH_ARM_SRC_RZV_RZV_GTM_H
#define __ARCH_ARM_SRC_RZV_RZV_GTM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* Initialize a GTM channel and register an IRQ handler.
 * handler: function of signature int handler(int irq, void *context, void *arg)
 * arg: user argument passed back to the handler
 * Returns 0 on success or a negative errno.
 */
int rzv_gtm_init_channel(int ch, int (*handler)(int, void *, void *), void *arg);

/* Deinitialize a GTM channel and detach any allocated IRQ slot. */
int rzv_gtm_deinit_channel(int ch);

/* Set the timer period (OSTM compare) in raw counts. */
int rzv_gtm_set_period(int ch, uint32_t period_counts);

/* Start the GTM OS Timer channel. */
int rzv_gtm_start(int ch);

/* Stop the GTM OS Timer channel. */
int rzv_gtm_stop(int ch);

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_ARM_SRC_RZV_RZV_GTM_H */

