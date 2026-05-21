# EVK-RA8P1 – USB PCDC NSH Application

This configuration builds NuttX NSH with support for **USB CDC/ACM (Virtual Serial Port)** on the Renesas **EVK-RA8P1** board.

## Location

`nuttx/boards/arm/ra8/evk-ra8p1/configs/usb-pcdc/`

## Features Enabled

- `CONFIG_USBDEV=y` - USB Device Support
- `CONFIG_CDCACM=y` - CDC/ACM Class Driver
- `CONFIG_RA_USBFS=y` - USB Full Speed Controller

## Hardware Setup

- Signal: USB Data
- EVK-RA8P1 Pin: USB Device Port (USB-F)
- External device: PC Host
- Power/Jumper notes: Ensure USB cable is connected to the USB Device port, not just the Debug port.

## Build

```bash
cd nuttx
./tools/configure.sh evk-ra8p1:usb-pcdc
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

Connect USB-serial (Debug) for NSH, or connect to the new USB CDC device:

```text
115200 8N1
```

(The NSH console might be on the USB CDC port depending on configuration, check `CONFIG_CDCACM_CONSOLE`)

## NSH Test Commands

Run the following commands to verify functionality:

```bash
nsh> sercon
```

(If enabled, to switch console to USB)

## Files of Interest

- defconfig
- `src/ra8p1_usb.c`
- `src/ra8p1_bringup.c`

## Troubleshooting

- Ensure USB cable is connected to the correct port
- Check host PC for new COM port / ttyACM device
