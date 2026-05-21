# EVK-RA8P1 – OSPI-B NSH Application

This configuration builds NuttX NSH with support for **OSPI (Octal SPI)** Flash on the Renesas **EVK-RA8P1** board.

## Location

`nuttx/boards/arm/ra8/evk-ra8p1/configs/ospi-b/`

## Features Enabled

- `CONFIG_RA_OSPI=y` - OSPI Driver
- `CONFIG_MTD=y` - MTD Support
- `CONFIG_RA8P1_OSPI_EXAMPLE=y` - OSPI Example

## Hardware Setup

- Signal: OSPI Bus
- EVK-RA8P1 Pin: On-board OSPI Flash
- External device: None (On-board)

## Build

```bash
cd nuttx
./tools/configure.sh evk-ra8p1:ospi-b
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
nsh> ospi_test
```

(Or check for MTD device)

```bash
nsh> ls /dev/mtd*
```

## Files of Interest

- defconfig
- `src/ra8p1_ospi_b.c`
- `src/ra8p1_bringup.c`

## Troubleshooting

- Ensure correct config selected
- Use `ls /dev` to confirm driver node exists
