# EVK-RA8P1 – NSH Application

This configuration builds the standard **NuttX Shell (NSH)** for the Renesas **EVK-RA8P1** board.

## Location

`nuttx/boards/arm/ra8/evk-ra8p1/configs/nsh/`

## Features Enabled

- `CONFIG_NSH_LIBRARY=y` - NSH Library
- `CONFIG_NSH_CONSOLE=y` - Serial Console (SCI0)
- `CONFIG_SERIAL=y` - Serial Driver

## Hardware Setup

- Signal: UART RX/TX
- EVK-RA8P1 Pin: P602 (RX), P603 (TX) (SCI0)
- External device: USB-Serial Adapter (or on-board debugger VCOM)
- Power/Jumper notes: Ensure VCOM jumpers are set if using USB-C debug port.

## Build

```bash
cd nuttx
./tools/configure.sh evk-ra8p1:nsh
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
nsh> help
nsh> uname -a
```

## Files of Interest

- defconfig
- `src/ra8p1_bringup.c`

## Troubleshooting

- Ensure correct config selected
- Verify baud rate (115200)
