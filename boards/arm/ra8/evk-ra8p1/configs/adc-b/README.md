# EVK-RA8P1 – ADC-B NSH Application

This configuration builds NuttX NSH with support for **ADC-B (Analog-to-Digital Converter)** on the Renesas **EVK-RA8P1** board.

## Location

`nuttx/boards/arm/ra8/evk-ra8p1/configs/adc-b/`

## Features Enabled

- `CONFIG_RA_ADC_B=y` - ADC-B Driver
- `CONFIG_RA_ADC_BATTERY_VOLTAGE=y` - Battery Voltage Monitoring
- `CONFIG_RA_ADC_BATTERY_CURRENT=y` - Battery Current Monitoring
- `CONFIG_RA_ADC_ARDUINO=y` - Arduino Header Analog Pins

## Hardware Setup

No external HW required for basic battery monitoring (internal signals).
For Arduino pins:

- Signal: Analog Input
- EVK-RA8P1 Pin: Arduino Header (J20) pins A0-A5

## Build

```bash
cd nuttx
./tools/configure.sh evk-ra8p1:adc-b
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
nsh> ls /dev/adc*
/dev/adc0
```

(Note: Specific ADC test commands depend on the enabled application examples or custom logic reading from `/dev/adc0`)

## Files of Interest

- defconfig
- `src/ra8p1_adc_b.c`
- `src/ra8p1_bringup.c`

## Troubleshooting

- Ensure correct config selected
- Check pinmux in board sources
- Use `ls /dev` to confirm driver node exists
