# EVK-RA8P1 – IWDT NSH Application

This configuration builds NuttX NSH with support for **IWDT (Independent Watchdog Timer)** on the Renesas **EVK-RA8P1** board.

## Location

`nuttx/boards/arm/ra8/evk-ra8p1/configs/iwdt/`

## Features Enabled

- `CONFIG_RA_IWDT=y` - Independent Watchdog Driver
- `CONFIG_WATCHDOG=y` - Watchdog Subsystem
- `CONFIG_EXAMPLES_WATCHDOG=y` - Watchdog Example

## Hardware Setup

No external HW required.

## Build

```bash
cd nuttx
./tools/configure.sh evk-ra8p1:iwdt
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
nsh> wdog
```

Expected output:

```text
Watchdog example
...
```

## Files of Interest

- defconfig
- `src/ra8p1_iwdt.c`
- `src/ra8p1_bringup.c`

## Troubleshooting

- Ensure correct config selected
- Use `ls /dev` to confirm driver node exists (`/dev/watchdog0`)
