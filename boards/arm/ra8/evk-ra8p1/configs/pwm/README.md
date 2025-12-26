# EVK-RA8P1 – PWM NSH Application

This configuration builds NuttX NSH with support for **PWM (Pulse Width Modulation)** using GPT timers on the Renesas **EVK-RA8P1** board.

## Location

`nuttx/boards/arm/ra8/evk-ra8p1/configs/pwm/`

## Features Enabled

- `CONFIG_PWM=y` - PWM Driver
- `CONFIG_RA_GPT=y` - GPT Timer Support
- `CONFIG_EXAMPLES_PWM=y` - PWM Example Application

## Hardware Setup

- Signal: PWM Output
- EVK-RA8P1 Pins:
  - Motor 1: P912 (GPT3A)
  - Motor 2: P915 (GPT5A)
  - Motor 3: P903 (GPT11A)
  - Motor 4: P515 (GPT13A)
- External device: LED or Oscilloscope

## Build

```bash
cd nuttx
./tools/configure.sh evk-ra8p1:pwm
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

Run the following commands to verify functionality for each motor:

**Motor 1 (GPT3 - P912):**

```bash
nsh> pwm -p /dev/pwm0 -f 1000 -d 50
```

**Motor 2 (GPT5 - P915):**

```bash
nsh> pwm -p /dev/pwm1 -f 1000 -d 50
```

**Motor 3 (GPT11 - P903):**

```bash
nsh> pwm -p /dev/pwm2 -f 1000 -d 50
```

**Motor 4 (GPT13 - P515):**

```bash
nsh> pwm -p /dev/pwm3 -f 1000 -d 50
```

(Sets 1kHz frequency, 50% duty cycle for 5 seconds)

To run all motors sequentially:

```bash
nsh> pwm -p /dev/pwm0 -f 1000 -d 50; pwm -p /dev/pwm1 -f 1000 -d 50; pwm -p /dev/pwm2 -f 1000 -d 50; pwm -p /dev/pwm3 -f 1000 -d 50
```

## Files of Interest

- defconfig
- `src/ra8p1_pwm.c`
- `src/ra8p1_bringup.c`

## Troubleshooting

- Ensure correct config selected
- Use `ls /dev` to confirm driver node exists (`/dev/pwm0`)
