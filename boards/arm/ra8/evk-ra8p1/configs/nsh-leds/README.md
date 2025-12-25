# NSH-LEDS Configuration for EVK-RA8P1

This configuration demonstrates LED and button functionality on the Renesas EVK-RA8P1 board.

## Features

- **Serial Console**: SCI0 UART (115200 baud, 8N1) on pins P602 (RX) and P603 (TX)
- **User LEDs**: Three LEDs with different control modes:
  - LED1 (Blue): Controllable via SW1 button and NSH commands
  - LED2 (Red): Controllable via NSH commands
  - LED3 (Green): Auto-blinks at 1Hz (background task)
- **User Button**: SW1 with interrupt-driven handler and 50ms debouncing
- **Debug Output**: RTT channel 0 for syslog messages

## Hardware Setup

### LEDs

- **LED1 (Blue)**: P600 - Active HIGH
- **LED2 (Red)**: PA07 - Active HIGH
- **LED3 (Green)**: P303 - Active HIGH (auto-blinks at 1Hz)

### Button

- **SW1**: P009 - IRQ13, falling edge interrupt, 50ms debounce, toggles LED1

### Console

- **SCI0 UART**: P602 (RX), P603 (TX) at 115200 baud

## NSH LED Commands

The userled driver provides the following commands for LED1 and LED2:

**Note**: LED3 (Green) auto-blinks in the background and cannot be controlled via NSH commands.

### List Available LEDs

```bash
nsh> leds list
Supported LEDs: 0 1
LED set: 00
```

### Get LED Status

```bash
nsh> leds get 0     # Get status of LED1 (Blue)
LED 0: OFF

nsh> leds get 1     # Get status of LED2 (Red)
LED 1: OFF
```

### Turn LED On/Off

```bash
nsh> leds set 0 on   # Turn on LED1 (Blue)
nsh> leds set 0 off  # Turn off LED1 (Blue)

nsh> leds set 1 on   # Turn on LED2 (Red)
nsh> leds set 1 off  # Turn off LED2 (Red)
```

### Control Multiple LEDs at Once

```bash
nsh> leds setall 0   # Turn off LED1 and LED2 (bit pattern: 00)
nsh> leds setall 1   # Turn on LED1 only (bit pattern: 01)
nsh> leds setall 2   # Turn on LED2 only (bit pattern: 10)
nsh> leds setall 3   # Turn on both LED1 and LED2 (bit pattern: 11)
```

## Button Functionality

Pressing SW1 will:

1. Toggle LED1 (Blue) on/off
2. Print a message via syslog: `SW1 pressed! LED1 (Blue) is now ON/OFF`

The button handler includes 50ms software debouncing to prevent false triggers from mechanical bounce.

## LED Behavior Summary

| LED | Color | Control Method | Default State |
|-----|-------|----------------|---------------|
| LED1 | Blue | SW1 button toggle OR NSH commands | OFF |
| LED2 | Red | NSH commands only | OFF |
| LED3 | Green | Auto-blink (1Hz, cannot be controlled) | Blinking |

## Device Files

- `/dev/console` - Serial console (SCI0 UART)
- `/dev/ttyS0` - SCI0 UART device
- `/dev/userleds` - LED control device

## Building

```bash
cd nuttx
make distclean
./tools/configure.sh evk-ra8p1:nsh-leds
make
```

## Flashing and Running

1. Flash the firmware using J-Link or your preferred method
2. Connect to SCI0 UART at 115200 baud
3. Press RESET
4. Type commands at the NSH prompt

## Example Session

```text
NuttShell (NSH) NuttX-12.x.x
nsh> leds list
Supported LEDs: 0 1
LED set: 00

nsh> leds set 0 on
nsh> leds get 0
LED 0: ON

nsh> # Press SW1 button - LED1 will toggle
SW1 pressed! LED1 (Blue) is now OFF

nsh> # Press SW1 again
SW1 pressed! LED1 (Blue) is now ON

nsh> leds setall 3
nsh> # Both LED1 and LED2 now on (LED3 continues blinking)

nsh> leds setall 0
nsh> # LED1 and LED2 now off (LED3 continues blinking)

nsh> leds set 1 on
nsh> # LED2 (Red) now on
```

## Notes

- LEDs are **Active HIGH**: GPIO high = LED on, GPIO low = LED off
- The LED driver handles the inversion automatically
- SW1 button and NSH commands can both control LED1 (last action wins)
- LED3 (Green) blinks continuously at 1Hz in the background via work queue
- SW1 includes 50ms software debouncing to prevent false triggers
- LED2 (Red) is only controllable via NSH commands
- RTT output can be viewed with J-Link RTT Viewer on channel 0

## Runtime Behavior

On boot:

1. All LEDs initialize to OFF
2. LED3 starts auto-blinking at 1Hz immediately
3. SW1 button interrupt is configured
4. NSH prompt appears

During operation:

- LED3 blinks continuously (independent of user actions)
- SW1 press toggles LED1 instantly
- NSH commands provide fine-grained control of LED1 and LED2
- All three behaviors operate independently
