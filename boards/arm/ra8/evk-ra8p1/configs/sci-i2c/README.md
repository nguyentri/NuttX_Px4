README
======

This configuration enables I2C/IIC support for the EVK-RA8P1 board.

Configuration Details
---------------------

NSH Configuration:
  - NSH shell enabled
  - Command console on UART (SCI2)
  - Debug logging via RTT

I2C Configuration:
  - I2C1 enabled (P205/P206 pins)
  - Standard mode (100 kHz)
  - I2C tools enabled for testing
  - Full debug logging enabled

Building
--------

  cd nuttx
  ./tools/configure.sh evk-ra8p1:i2c
  make clean
  make -j$(nproc)

Flashing
--------

  # Using J-Link
  JLinkExe -device R7KA8P1KF -if SWD -speed 4000
  > loadfile nuttx.hex
  > r
  > g

Testing I2C
-----------

From NSH shell:

  # Scan I2C bus 1
  nsh> i2c dev 1 scan

  # Read from device at address 0x1D, register 0x00
  nsh> i2c dev 1 0x1d get -r 0x00

  # Write value 0x55 to device at address 0x1D, register 0x00
  nsh> i2c dev 1 0x1d set -r 0x00 0x55

Pin Configuration
-----------------

I2C1:
  - SCL1: P205 (Port 2, Pin 05)
  - SDA1: P206 (Port 2, Pin 06)

These pins are configured with:
  - Drive strength: Medium
  - Peripheral function: IIC
  - Pull-up: External pull-ups required (typically 4.7kΩ to 3.3V)

Hardware Setup
--------------

1. Connect I2C device to EVK-RA8P1:
   - I2C device VCC → 3.3V
   - I2C device GND → GND
   - I2C device SCL → P205
   - I2C device SDA → P206

2. Add pull-up resistors (4.7kΩ) on SCL and SDA lines to 3.3V
   (Some boards have on-board pull-ups)

3. Connect USB cable for power and debugging

Supported Features
------------------

  ✓ I2C Master mode
  ✓ 7-bit addressing
  ✓ Standard mode (100 kHz)
  ✓ Fast mode (400 kHz)
  ✓ Multi-byte transfers
  ✓ Restart conditions
  ✓ Error detection (NACK, timeout, arbitration loss)
  ✓ Interrupt-driven transfers
  ✓ I2C tools for testing

Not Yet Tested
--------------

  ? 10-bit addressing
  ? Fast Mode Plus (1 MHz)
  ? DTC/DMAC transfers
  ? I2C Slave mode
  ? Multi-master scenarios

Known Issues
------------

None currently. This is the initial implementation based on FSP driver.

References
----------

- FSP Sample: iic_master_ek_ra8p1_ep
- RA8P1 Hardware Manual: Section "I2C Bus Interface (IIC)"
- NuttX I2C Documentation: nuttx/include/nuttx/i2c/i2c_master.h
