/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <debug.h>

#include <nuttx/board.h>
#include <arch/board/board.h>

#include "rdk-rzv2h.h"


/****************************************************************************
 * Name: board_app_initialize
 *
 * Description:
 *   Perform application-specific initialization.  Called through
 *   boardctl(BOARDIOC_INIT) when CONFIG_NSH_ARCHINIT is set.
 *
 *   Without this call the board bring-up (procfs mount, LED/button
 *   drivers, peripheral registration) never runs in configurations that
 *   do not set CONFIG_BOARD_LATE_INITIALIZE.
 *
 ****************************************************************************/

int board_app_initialize(uintptr_t arg)
{
#ifdef CONFIG_BOARD_LATE_INITIALIZE
  /* Board initialization already performed by board_late_initialize() */

  return 0;
#else
  return board_bringup();
#endif
}
