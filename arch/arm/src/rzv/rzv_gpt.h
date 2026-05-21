#ifndef __ARCH_ARM_SRC_RZV_RZV_GPT_H
#define __ARCH_ARM_SRC_RZV_RZV_GPT_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#ifdef CONFIG_RZV_PWM
#  include <nuttx/timers/pwm.h>
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef CONFIG_RZV_PWM
FAR struct pwm_lowerhalf_s *rzv_gpt_initialize(int channel);
#endif

#endif /* __ARCH_ARM_SRC_RZV_RZV_GPT_H */
