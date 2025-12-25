# EVK-RA8P1 – Mbed Crypto NSH Application

This configuration builds NuttX NSH with support for **Mbed TLS / Crypto** on the Renesas **EVK-RA8P1** board.

## Location

`nuttx/boards/arm/ra8/evk-ra8p1/configs/mbed_crypto/`

## Features Enabled

- `CONFIG_CRYPTO=y` - Crypto Subsystem
- `CONFIG_MBEDTLS=y` - Mbed TLS Library

## Hardware Setup

No external HW required. Uses internal SCE9 Protected Mode (if enabled) or software implementation.

## Build

```bash
cd nuttx
./tools/configure.sh evk-ra8p1:mbed_crypto
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
nsh> mbedtls_test
```

(Or specific crypto test commands if enabled)

## Files of Interest

- defconfig
- `src/ra8p1_mbed_crypto.c`
- `src/ra8p1_bringup.c`

## Troubleshooting

- Ensure correct config selected
