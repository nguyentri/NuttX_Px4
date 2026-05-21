# EVK-RA8P1 – POEG NSH Application

This configuration builds NuttX NSH with support for **POEG (Port Output Enable for GPT)** on the Renesas **EVK-RA8P1** board.

## Location

`nuttx/boards/arm/ra8/evk-ra8p1/configs/poeg/`

## Features Enabled

- `CONFIG_RA_POEG=y` - POEG Driver
- `CONFIG_RA_ELC=y` - Event Link Controller (required for POEG)
- `CONFIG_PWM=y` - PWM (controlled by POEG)

## Hardware Setup

No external HW required for basic configuration. POEG is used to disable PWM outputs on specific events (e.g., comparator trip).

## Build

```bash
cd nuttx
./tools/configure.sh evk-ra8p1:poeg
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
nsh> ls /dev/poeg*
```

(Note: POEG might not expose a standard dev node but works in background with PWM)

## Files of Interest

- defconfig
- `src/ra8p1_opeg.c`
- `src/ra8p1_bringup.c`

## Troubleshooting

- Ensure correct config selected
- Verify ELC configuration
