# EVK-RA8P1 – ADC-B Hardware Trigger NSH Application

This configuration builds NuttX NSH with support for **ADC-B Hardware Triggering** using GPT timers on the Renesas **EVK-RA8P1** board.

## Location

`nuttx/boards/arm/ra8/evk-ra8p1/configs/adc-b-hwtrigger/`

## Features Enabled

- `CONFIG_RA_ADC_B=y` - ADC-B Driver
- `CONFIG_RA_GPT=y` - GPT Timer (for trigger generation)
- `CONFIG_RA8P1_ADC_HW_TRIGGER_EXAMPLE=y` - Hardware Trigger Example
- `CONFIG_RA_ELC=y` - Event Link Controller

## Hardware Setup

No external HW required. The example uses internal GPT timer events to trigger ADC conversions via the ELC.

## Build

```bash
cd nuttx
./tools/configure.sh evk-ra8p1:adc-b-hwtrigger
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
nsh> adc_hw_trigger
```

Expected output:

```text
Starting ADC Hardware Trigger Example
Timer started, waiting for triggers...
ADC Conversion Complete: Value = 2048
...
```

## Files of Interest

- defconfig
- `src/ra8p1_adc_b_hwtrigger.c`
- `src/ra8p1_bringup.c`

## Troubleshooting

- Ensure ELC and GPT clocks are enabled
- Verify ELC link configuration between GPT and ADC
