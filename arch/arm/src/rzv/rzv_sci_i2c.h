/****************************************************************************
 * arch/arm/src/rzv/rzv_sci_i2c.h
 *
 * Public API for the RZ/V2H SCI-B Simple-I2C master driver.
 *
 * Board integration ABI
 * ---------------------
 * For each CONFIG_RZV_SCIn_I2C=y channel, the board header (board.h) MUST
 * define the following GPIO pinset macros using the encoding
 * (port[31:28] | pin[27:24] | mode[23:16] | psel[3:0]):
 *
 *   #define BOARD_SCIn_I2C_SDA_GPIO   GPIO_TXDn_MOSIn_SDAn_Pxx_Mm
 *   #define BOARD_SCIn_I2C_SCL_GPIO   GPIO_RXDn_MISOn_SCLn_Pxx_Mm
 *
 * The SCI RXD pin becomes SCL; the TXD pin becomes SDA (open-drain).
 * Use the BOARD_SCIn_* prefix, not BOARD_I2Cn_* (those are RIIC).
 *
 * Missing macros for an enabled channel produce a compile-time #error.
 *
 * Licensed under Apache License 2.0 — see top-level NOTICE.
 *
 ****************************************************************************/

#ifndef __ARCH_ARM_SRC_RZV_RZV_SCI_I2C_H
#define __ARCH_ARM_SRC_RZV_RZV_SCI_I2C_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/i2c/i2c_master.h>

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef CONFIG_RZV_SCI_I2C

/****************************************************************************
 * Name: rzv_sci_i2c_initialize
 *
 * Description:
 *   Initialise a SCI channel as Simple-I2C master.
 *
 * Input Parameters:
 *   channel - SCI channel index (0..3); must match an enabled
 *             CONFIG_RZV_SCIn_I2C Kconfig option.
 *
 * Returned Value:
 *   Pointer to struct i2c_master_s on success.
 *   NULL if channel not enabled, IRQ attach fails, or clock error.
 *
 * Notes:
 *   - Call once per channel; subsequent calls return the same pointer.
 * - Pass the returned pointer to i2c_register() (board glue).
 *   - Driver is CPU-mode only (no DMAC); returns -ENOSYS for polling path.
 *   - 10-bit address messages return -ENOTSUP from transfer().
 *
 ****************************************************************************/

struct i2c_master_s *rzv_sci_i2c_initialize(int channel);

#endif /* CONFIG_RZV_SCI_I2C */

#endif /* __ARCH_ARM_SRC_RZV_RZV_SCI_I2C_H */
