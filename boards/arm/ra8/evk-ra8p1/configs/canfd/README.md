v# EVK-RA8P1 – CAN-FD NSH Application

This configuration builds NuttX NSH with support for **CAN-FD** on the Renesas **EVK-RA8P1** board.

## Location

`nuttx/boards/arm/ra8/evk-ra8p1/configs/canfd/`

## Features Enabled

- `CONFIG_RA_CANFD=y` - CAN-FD Driver
- `CONFIG_RA_CANFD1=y` - CAN-FD Channel 1
- `CONFIG_EXAMPLES_CAN=y` - CAN Example Application

## Hardware Setup

- Signal: CAN High / CAN Low
- EVK-RA8P1 Pin: CAN1 is typically routed to the CAN connector on the EVK.
- External device: CAN Analyzer or another CAN node.
- Power/Jumper notes: Ensure CAN transceiver jumpers are set correctly.

## Build

```bash
cd nuttx
./tools/configure.sh evk-ra8p1:canfd
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
nsh> can
```

Expected output:

```text
user_start: CAN example
...
```

## Files of Interest

- defconfig
- `src/ra8p1_canfd.c`
- `src/ra8p1_bringup.c`

## Troubleshooting

- Ensure correct config selected
- Check pinmux in board sources
- Confirm clock / power domain enabled
- Use `ls /dev` to confirm driver node exists
- Use `ifconfig` to check network interfaces if using SocketCAN (though this config uses character device)
