# EVK-RA8P1 – SCI-SPI NSH Application

This configuration builds NuttX NSH with support for **SPI over SCI (Serial Communications Interface)** on the Renesas **EVK-RA8P1** board.

## Location

`nuttx/boards/arm/ra8/evk-ra8p1/configs/sci-spi/`

## Features Enabled

- `CONFIG_RA_SCI_SPI=y` - SCI SPI Driver
- `CONFIG_SPI=y` - SPI Subsystem

## Hardware Setup

- Signal: SPI MOSI/MISO/CLK/CS
- EVK-RA8P1 Pin: SCI pins configured as SPI (Verify against board schematic)
- External device: SPI Peripheral

## Build

```bash
cd nuttx
./tools/configure.sh evk-ra8p1:sci-spi
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
nsh> ls /dev/spi*
```

## Files of Interest

- defconfig
- `src/ra8p1_sci_spi.c`
- `src/ra8p1_bringup.c`

## Troubleshooting

- Ensure correct config selected
- Check pinmux in board sources
