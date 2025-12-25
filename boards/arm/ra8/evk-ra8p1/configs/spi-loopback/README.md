# EVK-RA8P1 – SPI Loopback NSH Application

This configuration builds NuttX NSH with support for **SPI Loopback Test** on the Renesas **EVK-RA8P1** board.

## Location

`nuttx/boards/arm/ra8/evk-ra8p1/configs/spi-loopback/`

## Features Enabled

- `CONFIG_RA_SPI=y` - SPI Driver
- `CONFIG_RA8P1_SPI_LOOPBACK_EXAMPLE=y` - SPI Loopback Example
- `CONFIG_SPI_EXCHANGE=y` - SPI Exchange Support

## Hardware Setup

- Signal: SPI MISO/MOSI
- EVK-RA8P1 Pin: Connect MOSI to MISO on the configured SPI port (e.g., SPI0 or SPI1).
- External device: Jumper wire.

## Build

```bash
cd nuttx
./tools/configure.sh evk-ra8p1:spi-loopback
make -j
```

## Flash

Example (J-Link):

```bash
JLinkExe -device R7KA8P1KF -if SWD -speed 4000
loadfile nuttx.hex
r
g
```

## Console

Connect USB-serial:

```text
115200 8N1
```

## NSH Test Commands

Run the following commands to verify functionality:

```bash
nsh> spi_loopback
```

Expected output:

```text
SPI Loopback Test
Sent: 0xAA, Received: 0xAA
Test PASSED
```

## Files of Interest

- defconfig
- `src/ra8p1_spi_loopback.c`
- `src/ra8p1_bringup.c`

## Troubleshooting

- Ensure MOSI and MISO are connected
- Verify SPI port configuration
