README for EVK-RA8P1 IPC Configuration
======================================

This configuration demonstrates the Inter-Processor Communication (IPC) driver
for the Renesas RA8P1 dual-core MCU on the EVK-RA8P1 development board.

Overview
--------
The IPC driver provides hardware-based communication between the two Cortex-M85
cores in the RA8P1 MCU. It includes:

  - 16 hardware semaphores for resource synchronization
  - Inter-core NMI (Non-Maskable Interrupt) generation
  - 4 message channels (2 per core pair) with 32-bit data transfer
  - FIFO-based communication with status monitoring

Features Enabled
----------------
  - IPC driver with debug output (CONFIG_RA_IPC=y)
  - Channel 0 and 1 enabled
  - NMI support for critical notifications
  - Basic test application included

Building
--------
From the NuttX root directory:

  $ cd ~/px4_ra8/PX4-Autopilot/platforms/nuttx/NuttX/nuttx
  $ ./tools/configure.sh evk-ra8p1:ipc
  $ make

This will generate:
  - nuttx.bin     : Binary image for flashing
  - nuttx.hex     : Intel HEX format
  - nuttx         : ELF executable with debug symbols

Flashing
--------
Using J-Link:
  $ JLinkExe -device R7KA8P1KF -if SWD -speed 4000 -autoconnect 1
  J-Link> loadbin nuttx.bin 0x00000000
  J-Link> r
  J-Link> g
  J-Link> exit

Serial Console
--------------
The configuration uses SCI2 (UART) for the NSH console:
  - Baudrate: 115200
  - Data bits: 8
  - Parity: None
  - Stop bits: 1

Connect to /dev/ttyUSB0 (or appropriate port):
  $ minicom -D /dev/ttyUSB0 -b 115200

Or using picocom:
  $ picocom -b 115200 /dev/ttyUSB0

Debug Output
------------
Additional debug output is available via SEGGER RTT:
  - RTT channel 0 for system logs
  - Use JLinkRTTClient or JLinkRTTViewer to view

Usage
-----
The IPC driver is automatically initialized during board bringup.

Testing:
  The configuration includes basic IPC functionality tests that run
  automatically during initialization. Check the console output for
  test results.

API Usage:
  See arch/arm/src/ra8/ra_ipc.h for the complete API documentation.

  Example - Semaphore:
    ret = ra_ipc_semaphore_take(0);
    /* critical section */
    ra_ipc_semaphore_give(0);

  Example - Channel communication:
    /* Register callback */
    ra_ipc_channel_register(0, my_callback);

    /* Send data */
    ra_ipc_channel_write(0, 0x12345678);

    /* Callback will be invoked when data arrives */

  Example - NMI:
    ra_ipc_nmi_enable(my_nmi_handler);
    /* From other core: */
    ra_ipc_nmi_request_set();

Future Integration
------------------
This IPC driver provides the foundation for:
  - OpenAMP integration
  - RPMsg communication protocol
  - Dual-core application development
  - Asymmetric multiprocessing (AMP) configurations

Notes
-----
  - IPC is only available on RA8P1 (dual-core) MCU
  - Each core must be flashed with appropriate firmware
  - Proper synchronization is required for shared resources
  - NMI cannot be disabled once enabled by hardware

References
----------
  - RA8P1 User's Manual (Hardware)
  - FSP IPC examples in .refs/lpm_ek_ra8p1_ep
  - NuttX IPCC driver in drivers/ipcc/
  - OpenAMP documentation

For More Information
--------------------
  See the main driver implementation:
    - arch/arm/src/ra8/ra_ipc.c
    - arch/arm/src/ra8/ra_ipc.h
    - arch/arm/src/ra8/hardware/ra8p1/ra_ipc.h

  Board-specific code:
    - boards/arm/ra8/evk-ra8p1/src/ra8p1_ipc.c
