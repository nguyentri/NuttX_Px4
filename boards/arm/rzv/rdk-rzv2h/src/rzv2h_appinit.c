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
 *   Perform application-specific initialization.  This is called from the
 *   board-level bring-up code.  Provide a minimal stub that returns
 *   success; later board-specific initialization can be added here.
 *
 ****************************************************************************/

int board_app_initialize(uintptr_t arg)
{
  /* Nothing special to do yet */
  return 0;
}
