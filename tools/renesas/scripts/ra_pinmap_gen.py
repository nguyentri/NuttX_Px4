#!/usr/bin/env python3
"""
Pin Mapping Generator for Renesas {MCU} Microcontroller
Generates pin mapping header file from SVD and CSV data

The SVD file provides register definitions and bit positions,
while the CSV file provides the actual pin-to-function mappings.
"""

import csv
import re
import xml.etree.ElementTree as ET
import sys
from collections import defaultdict
from pathlib import Path

# Define PSEL mappings based on current pinmap header
PSEL_MAPPINGS = {
    'AGT': 'PFS_PSEL_AGT',
    'AGTIO': 'PFS_PSEL_AGT',
    'AGTO': 'PFS_PSEL_AGT',
    'AGTOB': 'PFS_PSEL_AGT',
    'AGTOA': 'PFS_PSEL_AGT',
    'AGTEE': 'PFS_PSEL_AGT',
    'GPT': 'PFS_PSEL_GPT',
    'GTIOC': 'PFS_PSEL_GPT',
    'GTETRG': 'PFS_PSEL_GPT',
    'GTADSM': 'PFS_PSEL_GPT',
    'SCI': 'PFS_PSEL_SCI',
    'RXD': 'PFS_PSEL_SCI',
    'TXD': 'PFS_PSEL_SCI',
    'SCK': 'PFS_PSEL_SCI',
    'CTS': 'PFS_PSEL_SCI',
    'DE': 'PFS_PSEL_SCI',
    'SPI': 'PFS_PSEL_SPI',
    'MISO': 'PFS_PSEL_SPI',
    'MOSI': 'PFS_PSEL_SPI',
    'RSPCK': 'PFS_PSEL_SPI',
    'SSL': 'PFS_PSEL_SPI',
    'I2C': 'PFS_PSEL_IIC',
    'SDA': 'PFS_PSEL_IIC',
    'SCL': 'PFS_PSEL_IIC',
    'CAN': 'PFS_PSEL_CAN',
    'CRX': 'PFS_PSEL_CAN',
    'CTX': 'PFS_PSEL_CAN',
    'USB': 'PFS_PSEL_USBFS',
    'ETHERNET': 'PFS_PSEL_ETHERNET',
    'ET0': 'PFS_PSEL_ETHERNET',
    'RMII': 'PFS_PSEL_ETHERNET',
    'REF50CK': 'PFS_PSEL_ETHERNET',
    'SSI': 'PFS_PSEL_SSIE',
    'AUDIO_CLK': 'PFS_PSEL_CLKOUT_ACMPLP_RTC',
    'RTC': 'PFS_PSEL_CLKOUT_ACMPLP_RTC',
    'DAC': 'PFS_PSEL_DAC',
    'DA': 'PFS_PSEL_DAC',
    'OPAMP': 'PFS_PSEL_OPAMP',
    'IVCMP': 'PFS_PSEL_OPAMP',
    'IVREF': 'PFS_PSEL_OPAMP',
    'VCOUT': 'PFS_PSEL_OPAMP',
    'XSPI': 'PFS_PSEL_XSPI',
    'OM': 'PFS_PSEL_XSPI',
    'ULPT': 'PFS_PSEL_ULPT',
    'CEU': 'PFS_PSEL_CEU',
    'VIO': 'PFS_PSEL_CEU',
    'ADTRG': 'PFS_PSEL_CAC_ADC14'
}

def get_psel_value(function_name):
    """Get the appropriate PSEL value for a function"""
    function_upper = function_name.upper()

    # Check for exact matches first
    for key, value in PSEL_MAPPINGS.items():
        if key in function_upper:
            return value

    return None

def clean_function_name(func_name):
    """Clean function name to make it a valid C identifier with proper formatting"""
    # Remove spaces, slashes, and hyphens, replace with underscores
    cleaned = re.sub(r'[-/\s]+', '_', func_name)
    # Remove any remaining invalid characters
    cleaned = re.sub(r'[^A-Za-z0-9_]', '', cleaned)
    return cleaned

def create_function_mapping(func_name):
    """Create proper function mapping for different peripheral types"""
    # Handle SCI functions specially to match the current format
    if '/' in func_name and ('RXD' in func_name or 'TXD' in func_name):
        # For SCI functions like "RXD2_A / MISO2_A / SCL2_A"
        parts = [part.strip() for part in func_name.split('/')]
        if len(parts) >= 3:
            # Extract the common suffix (A, B, C, etc.)
            main_part = parts[0].strip()  # RXD2_A
            if 'RXD' in main_part:
                # Create the combined name: RXD2_MISO2_SCL2_A
                base_num = main_part.split('_')[0][-1]  # Extract number
                suffix = main_part.split('_')[1]       # Extract A/B/C
                func_type = main_part.split('_')[0][:-1]  # Extract RXD
                return f"{func_type}{base_num}_MISO{base_num}_SCL{base_num}_{suffix}"
            elif 'TXD' in main_part:
                # Create the combined name: TXD2_MOSI2_SDA2_A
                base_num = main_part.split('_')[0][-1]  # Extract number
                suffix = main_part.split('_')[1]       # Extract A/B/C
                func_type = main_part.split('_')[0][:-1]  # Extract TXD
                return f"{func_type}{base_num}_MOSI{base_num}_SDA{base_num}_{suffix}"

        # Fallback to first part if parsing fails
        return parts[0].strip().replace(' ', '_')

    # For other functions, use the original cleaning
    return clean_function_name(func_name)

def parse_svd_file(svd_path):
    """Parse SVD file to extract PFS register bit positions"""
    tree = ET.parse(svd_path)
    root = tree.getroot()

    bit_positions = {}

    # Find the PFS peripheral
    for peripheral in root.findall(".//peripheral"):
        name = peripheral.find('name')
        if name is not None and name.text == 'PFS':
            # Find the first PFS register to extract bit field positions
            for register in peripheral.findall(".//register"):
                reg_name = register.find('name')
                if reg_name is not None and 'PFS' in reg_name.text and reg_name.text.endswith('PFS'):
                    # Extract bit field positions from this register
                    for field in register.findall(".//field"):
                        field_name = field.find('name')
                        lsb = field.find('lsb')
                        msb = field.find('msb')
                        if field_name is not None and lsb is not None:
                            lsb_val = int(lsb.text)
                            msb_val = int(msb.text) if msb is not None else lsb_val

                            # Store the base bit position
                            bit_positions[f'R_PFS_{field_name.text}'] = lsb_val

                            # For multi-bit fields, also store individual bit positions
                            if msb_val > lsb_val:
                                for bit_num in range(lsb_val, msb_val + 1):
                                    bit_offset = bit_num - lsb_val
                                    bit_positions[f'R_PFS_{field_name.text}{bit_offset}'] = bit_num
                    break
            break

    return bit_positions

def parse_csv_data(csv_path):
    """Parse the CSV file and extract pin mapping data

    Handles two CSV formats:
    1. Tab-delimited (RA8E1): Pin\tFunctions
    2. Comma-delimited (RA8P1): Pin,Col1,IRQ,Functions...
    """
    pins_data = {}

    with open(csv_path, 'r') as file:
        # Read first line to detect format
        first_line = file.readline()
        file.seek(0)

        # Detect delimiter: if has many commas, it's comma-delimited (RA8P1 format)
        # Otherwise it's tab-delimited (RA8E1 format)
        is_multi_column = first_line.count(',') > 2

        if is_multi_column:
            # RA8P1 format: comma-delimited with multiple columns
            csv_reader = csv.reader(file, delimiter=',')

            for row in csv_reader:
                if len(row) < 2:
                    continue

                pin_name = row[0].strip()

                # Skip header row, port headers, and empty pins
                if pin_name in ("I/O ports", "", "—") or not pin_name.startswith('P'):
                    continue

                # Handle both P609 and PA12 formats
                if pin_name[1].isalpha():
                    # Format like PA12 - map letters to port numbers (A=10, B=11, etc.)
                    port_num = ord(pin_name[1]) - ord('A') + 10
                    pin_num = int(pin_name[2:4])
                else:
                    # Format like P609
                    match = re.match(r"P(\d)(\d{2})", pin_name)
                    if not match:
                        continue
                    port_num = int(match.group(1))
                    pin_num = int(match.group(2))

                # Parse functions from columns 1 onwards
                func_list = []
                for col_idx in range(1, len(row)):
                    func = row[col_idx].strip()
                    if func and func != "—":
                        # Split on '/' to get individual functions
                        sub_funcs = [f.strip() for f in func.split('/')]
                        func_list.extend(sub_funcs)

                pins_data[pin_name] = {
                    'port': port_num,
                    'pin': pin_num,
                    'functions': func_list
                }
        else:
            # RA8E1 format: tab-delimited
            csv_reader = csv.reader(file, delimiter='\t')

            for row in csv_reader:
                if len(row) < 2:
                    continue

                pin_name, functions = row[0].strip(), row[1].strip()

                # Skip header row and port headers
                if pin_name == "Pin" or pin_name.startswith("PORT"):
                    continue

                if not pin_name.startswith('P') or not functions:
                    continue

                # Extract pin number
                match = re.match(r"P(\d)(\d{2})", pin_name)
                if not match:
                    continue

                port_num = int(match.group(1))
                pin_num = int(match.group(2))

                # Parse functions
                func_list = []
                if functions != "(No alternative functions listed)":
                    # Split by comma first, then handle complex function names
                    for func in functions.split(','):
                        func = func.strip()
                        if func:
                            func_list.append(func)

                pins_data[pin_name] = {
                    'port': port_num,
                    'pin': pin_num,
                    'functions': func_list
                }

    return pins_data

def generate_header(csv_path, mcu_override=None):
    """Generate the complete header file matching the exact manual output"""
    # Parse CSV file
    pins_data = parse_csv_data(csv_path)

    # Derive MCU name from override or CSV filename (e.g., ra8e1_pin_map.csv -> RA8E1)
    if mcu_override:
        mcu_name = mcu_override.upper()
        mcu_name_lower = mcu_override.lower()
    else:
        csv_basename = Path(csv_path).stem  # ra8e1_pin_map
        mcu_name = csv_basename.split('_')[0].upper()  # RA8E1
        mcu_name_lower = csv_basename.split('_')[0].lower()  # ra8e1

    # Calculate the maximum port number from the pins data
    max_port = max(data['port'] for data in pins_data.values()) if pins_data else 9
    port_max = max_port + 1

    # Collect definitions
    alt_func_defs = []
    irq_defs = []
    analog_defs = []
    func_counts = defaultdict(int)  # For numbering non-SCI functions

    HEADER_GUARD = f"__ARCH_ARM_SRC_RA_HARDWARE_{mcu_name}_PINMAP_H"

    # Process each pin to generate alternative function definitions
    for pin_name, data in sorted(pins_data.items()):
        port = data['port']
        pin = data['pin']

        for func in data['functions']:
            # Generate IRQ Definitions - match exact format from manual file
            if 'IRQ' in func:
                irq_match = re.search(r'IRQ(\d+)', func)
                if irq_match:
                    irq_num = irq_match.group(1)
                    ds_suffix = "_DS" if "-DS" in func else ""
                    # Match the exact spacing from manual file
                    irq_def = f"#define GPIO_IRQ{irq_num}_{pin_name}{ds_suffix}                      (gpio_pinset_t)(PORT{port} | PIN{pin} | R_PFS_PCR | R_PFS_ISEL)"
                    if irq_def not in irq_defs:
                        irq_defs.append(irq_def)

            # Generate Analog Definitions - preserve the exact format including slashes
            elif func.startswith('AN') or func.startswith('DA'):
                # Sanitize function name to create valid macro (replace slashes/spaces with underscores)
                clean_analog = clean_function_name(func)
                analog_def = f"#define GPIO_{clean_analog}_1                        (gpio_pinset_t)(PORT{port} | PIN{pin} | R_PFS_ASEL)"
                if analog_def not in analog_defs:
                    analog_defs.append(analog_def)

            # Generate Alternative Function Definitions
            else:
                psel = get_psel_value(func)
                if psel:
                    # Use the new function mapping for shortened names
                    clean_func = create_function_mapping(func)

                    # Check if this is a SCI function (already has A/B/C suffix)
                    if ('RXD' in clean_func or 'TXD' in clean_func) and clean_func.endswith(('_A', '_B', '_C')):
                        # SCI functions already have their suffix, use as-is
                        alt_func_def = f"#define GPIO_{clean_func}                         (gpio_pinset_t)(PORT{port} | PIN{pin} | {psel})"
                    else:
                        # Other functions use numbered suffixes
                        func_counts[clean_func] += 1
                        count = func_counts[clean_func]
                        alt_func_def = f"#define GPIO_{clean_func}_{count}                         (gpio_pinset_t)(PORT{port} | PIN{pin} | {psel})"

                    alt_func_defs.append(alt_func_def)

    # Print the header file with exact manual format
    print(f"""/****************************************************************************
 * arch/arm/src/ra8/hardware/{mcu_name_lower}/ra_pinmap.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef {HEADER_GUARD}
#define {HEADER_GUARD}

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Port Number definitions */
#define PORT0                                   (0 << 28)
#define PORT1                                   (1 << 28)
#define PORT2                                   (2 << 28)
#define PORT3                                   (3 << 28)
#define PORT4                                   (4 << 28)
#define PORT5                                   (5 << 28)
#define PORT6                                   (6 << 28)
#define PORT7                                   (7 << 28)
#define PORT8                                   (8 << 28)
#define PORT9                                   (9 << 28)
#define PORT10                                  (10 << 28)
#define PORT11                                  (11 << 28)
#define PORT12                                  (12 << 28)
#define PORT13                                  (13 << 28)
#define PORT14                                  (14 << 28)
#define PORT15                                  (15 << 28)
#define PORT_MAX                                ({port_max})

/* Pin Number definitions */
#define PIN0                                   (0 << 24)
#define PIN1                                   (1 << 24)
#define PIN2                                   (2 << 24)
#define PIN3                                   (3 << 24)
#define PIN4                                   (4 << 24)
#define PIN5                                   (5 << 24)
#define PIN6                                   (6 << 24)
#define PIN7                                   (7 << 24)
#define PIN8                                   (8 << 24)
#define PIN9                                   (9 << 24)
#define PIN10                                  (10 << 24)
#define PIN11                                  (11 << 24)
#define PIN12                                  (12 << 24)
#define PIN13                                  (13 << 24)
#define PIN14                                  (14 << 24)
#define PIN15                                  (15 << 24)
#define PIN_MAX                                (16)

/* IRQ Pin Definitions */
#define IRQ0                                   (0)
#define IRQ1                                   (1)
#define IRQ2                                   (2)
#define IRQ3                                   (3)
#define IRQ4                                   (4)
#define IRQ5                                   (5)
#define IRQ6                                   (6)
#define IRQ7                                   (7)
#define IRQ8                                   (8)
#define IRQ9                                   (9)
#define IRQ10                                  (10)
#define IRQ11                                  (11)
#define IRQ12                                  (12)
#define IRQ13                                  (13)
#define IRQ14                                  (14)
#define IRQ15                                  (15)
#define MAX_GPIO_IRQS                          (16)

/* PSEL configuration Bit Fields for cfg field in gpio_pinset_t struct */
#define R_PFS_PSEL_SHIFT_CFG                    (16)   /* PSEL position in gpio_pinset_t.cfg (bits 20-16) */
#define PFS_PSEL_HIZ                            (0x00 << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_AGT                            (0x01 << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_GPT                            (0x02 << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_AGT1                           (0x03 << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_SCI                            (0x04 << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_SCI1                           (0x05 << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_SPI                            (0x06 << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_IIC                            (0x07 << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_KINT                           (0x08 << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_CLKOUT_ACMPLP_RTC              (0x09 << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_CAC_ADC14                      (0x0a << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_CTSU                           (0x0c << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_SLCDC                          (0x0d << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_CAN                            (0x10 << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_SSIE                           (0x12 << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_USBFS                          (0x13 << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_DAC                            (0x14 << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_TRACE                          (0x15 << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_DEBUG                          (0x16 << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_OPAMP                          (0x17 << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_XSPI                           (0x18 << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_ETHERNET                       (0x19 << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_CEU                            (0x1A << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_OSPI                           (0x1B << R_PFS_PSEL_SHIFT_CFG)
#define PFS_PSEL_ULPT                           (0x1C << R_PFS_PSEL_SHIFT_CFG)

/* GPIO Configuration for gpio_pinset_t.cfg field */
#define GPIO_OUTPUT                   		(R_PFS_PDR)           /* Output direction */
#define GPIO_INPUT                    		(0)                   /* Input direction (default) */
#define GPIO_PULLUP                   		(R_PFS_PCR)           /* Enable pull-up */
#define GPIO_OPENDRAIN                		(R_PFS_NCODR)         /* Open drain output */
#define GPIO_LOW_DRIVE                		(R_PFS_DSCR_00)       /* Low drive strength (default) */
#define GPIO_MIDDLE_DRIVE             		(R_PFS_DSCR_01)       /* Middle drive strength */
#define GPIO_HIGH_DRIVE               		(R_PFS_DSCR_11)       /* High drive strength */
#define GPIO_ANALOG                   		(R_PFS_ASEL)          /* Analog mode */
#define GPIO_IRQ                      		(R_PFS_ISEL)          /* IRQ input enable */
#define GPIO_PERIPHERAL               		(R_PFS_PMR)           /* Peripheral mode (PMR) */
#define GPIO_OUTPUT_HIGH              		(R_PFS_PODR)          /* Output high */
#define GPIO_OUTPUT_LOW               		(0)                   /* Output low (default) */

/* Alternative Function Pin Definitions */
{chr(10).join(sorted(alt_func_defs))}

/* External Interrupt Pin Definitions */
{chr(10).join(sorted(list(set(irq_defs))))}

/* Analog Input Definitions */
{chr(10).join(sorted(list(set(analog_defs))))}

/* General Purpose GPIO Pin Definitions */
""")

    # Generate GPIO pin definitions in exact manual order
    for pin_name, data in sorted(pins_data.items()):
        port = data['port']
        pin = data['pin']

        print(f"/* {pin_name} Pin Definitions */")
        print(f"#define GPIO_{pin_name}_OUTPUT_HIGH               (gpio_pinset_t)(PORT{port} | PIN{pin} | GPIO_OUTPUT | GPIO_LOW_DRIVE | GPIO_OUTPUT_HIGH)")
        print(f"#define GPIO_{pin_name}_OUTPUT_LOW                (gpio_pinset_t)(PORT{port} | PIN{pin} | GPIO_OUTPUT | GPIO_LOW_DRIVE | GPIO_OUTPUT_LOW)")
        print(f"#define GPIO_{pin_name}_INPUT                     (gpio_pinset_t)(PORT{port} | PIN{pin} | GPIO_INPUT)")
        print(f"#define GPIO_{pin_name}_INPUT_PULLUP              (gpio_pinset_t)(PORT{port} | PIN{pin} | GPIO_INPUT | R_PFS_PCR)")

        # Add analog capability if the pin has ANxxx function
        if any(f.startswith('AN') or f.startswith('DA') for f in data['functions']):
            print(f"#define GPIO_{pin_name}_ANALOG                    (gpio_pinset_t)(PORT{port} | PIN{pin} | R_PFS_ASEL)")

        print("")

    # Note: Peripheral mode is detected automatically when PSEL != 0

    print(f"""
/* Note: Peripheral mode is detected automatically when PSEL != 0 */

#endif /* {HEADER_GUARD} */""")

if __name__ == "__main__":
    import sys

    # Default paths
    csv_path = '/home/a5094159/projects/nuttx_ra_px4/ra8p1_pinmap.csv'
    mcu_override = "RA8P1"  # Override MCU name if needed

    # csv_path = '/home/a5094159/projects/nuttx_ra_px4/ra8e1_pinmap.csv'
    # mcu_override = "RA8E1"  # Override MCU name if needed

    # Allow command line override
    if len(sys.argv) > 1:
        csv_path = sys.argv[1]
    if len(sys.argv) > 2:
        mcu_override = sys.argv[2]

    generate_header(csv_path, mcu_override)
