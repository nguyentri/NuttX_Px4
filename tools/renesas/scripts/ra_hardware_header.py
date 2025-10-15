#!/usr/bin/env python3
import sys
import xml.etree.ElementTree as ET
from argparse import ArgumentParser
import os
import re

# Global map of peripheral name -> element (populated in main)
GLOBAL_PERIPHERALS = {}

# Global map of CMSIS register info: peripheral -> register -> {size, fields}
CMSIS_REGISTER_DB = {}

# Map SVD peripheral names to CMSIS typedef names (when they differ)
SVD_TO_CMSIS_NAME_MAP = {
    'SYSC': 'SYSTEM',
    # Add more mappings as needed
}

def parse_cmsis_typedef_structs(cmsis_header_path):
    """
    Parse vendor CMSIS device header to extract register sizes and bitfield info.
    Returns: dict { 'PERIPHERAL_NAME': { 'REG_NAME': {'size': bytes, 'fields': {...}} } }
    """
    print(f"Parsing CMSIS header for register size/bitfield corrections: {cmsis_header_path}")

    with open(cmsis_header_path, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()

    cmsis_db = {}

    # Find all R_<PERIPH>_Type typedef locations
    typedef_locations = []
    for match in re.finditer(r'\} R_(\w+?)_Type\s*;', content):
        periph_name = match.group(1).upper()
        end_pos = match.end()
        typedef_locations.append((periph_name, end_pos))

    # For each typedef, extract the struct body by finding matching braces backward
    for periph_name, end_pos in typedef_locations:
        # Search backward for 'typedef struct'
        search_start = max(0, end_pos - 500000)  # Search up to 500KB backward
        typedef_start_match = None
        for m in re.finditer(r'typedef\s+struct', content[search_start:end_pos]):
            typedef_start_match = m

        if not typedef_start_match:
            continue

        typedef_start = search_start + typedef_start_match.start()

        # Find the opening brace after 'typedef struct'
        brace_start = content.find('{', typedef_start, end_pos)
        if brace_start < 0:
            continue

        # Find matching closing brace (start count at 1 since we've found the opening brace)
        brace_count = 1
        struct_end = brace_start
        for i in range(brace_start + 1, end_pos):
            if content[i] == '{':
                brace_count += 1
            elif content[i] == '}':
                brace_count -= 1
                if brace_count == 0:
                    struct_end = i
                    break

        struct_body = content[brace_start+1:struct_end]

        # Skip numbered peripheral instances like PORT0, SCI0 - use base name
        if periph_name and periph_name[-1].isdigit():
            base_name = periph_name.rstrip('0123456789')
        else:
            base_name = periph_name

        # Parse the struct body to extract register info
        registers = parse_cmsis_struct_registers(struct_body)

        if base_name not in cmsis_db:
            cmsis_db[base_name] = {}

        # Merge registers from this instance
        cmsis_db[base_name].update(registers)

    print(f"  Extracted CMSIS data for {len(cmsis_db)} peripherals")
    return cmsis_db

def parse_cmsis_struct_registers(struct_body):
    """
    Parse CMSIS struct body and extract register names, sizes, and bitfields.
    Returns: dict { 'REG_NAME': {'size': bytes, 'fields': {field_name: {lsb, msb, width, ...}}} }
    """
    registers = {}

    # Note: Do NOT remove comments here - we need the [msb..lsb] info from bitfield comments!

    # Find union blocks (most registers are in unions with bitfield structs)
    # Pattern: union { __IOM uint32_t REGNAME; struct { ... } REGNAME_b; };
    union_pattern = r'union\s*\{(.*?)\}\s*;'

    for union_match in re.finditer(union_pattern, struct_body, re.DOTALL):
        union_body = union_match.group(1)

        # Extract main register declaration: __IOM uint32_t REGNAME; or REGNAME[N];
        reg_decl_pattern = r'(__IOM|__IM|__OM|__IO)?\s*(uint\d+_t|int\d+_t)\s+(\w+)(?:\[\d+\])?\s*;'
        reg_match = re.search(reg_decl_pattern, union_body)

        if not reg_match:
            continue

        reg_type = reg_match.group(2)  # uint32_t, uint16_t, uint8_t
        reg_name = reg_match.group(3).upper()

        # Skip bitfield struct names (end with _b) and RESERVED
        if reg_name.endswith('_B') or 'RESERVED' in reg_name:
            continue

        # Extract size from type
        type_match = re.search(r'(\d+)', reg_type)
        if not type_match:
            continue
        type_bits = int(type_match.group(1))
        size_bytes = type_bits // 8

        # Find bitfield struct: struct { ... } REGNAME_b; or REGNAME_b[N];
        bitfield_pattern = r'struct\s*\{(.*?)\}\s*\w+_b(?:\[\d+\])?\s*;'
        bitfield_match = re.search(bitfield_pattern, union_body, re.DOTALL)

        fields = {}
        if bitfield_match:
            bitfield_body = bitfield_match.group(1)
            fields = parse_cmsis_bitfields(bitfield_body)

        registers[reg_name] = {
            'size': size_bytes,
            'fields': fields
        }

    return registers

def parse_cmsis_bitfields(struct_body):
    """
    Parse bitfield struct members from CMSIS header.
    Returns: dict { 'FIELD_NAME': {'lsb': int, 'msb': int, 'width': int, 'mask': int, 'description': str} }
    """
    fields = {}

    # Pattern: __IOM uint32_t FIELDNAME : width; /*!< [msb..lsb] description */
    # Handle both /* and /*!< comment styles, including multi-line comments
    # The description part can span multiple lines with * continuation
    field_pattern = r'(__IOM|__IM|__OM)?\s*uint\d+_t\s+(\w+)\s*:\s*(\d+)\s*;\s*/\*!?<?[^\[]*\[(\d+)\.\.(\d+)\](.*?)\*/'

    for match in re.finditer(field_pattern, struct_body, re.DOTALL):
        field_name = match.group(2).upper()
        width = int(match.group(3))
        msb = int(match.group(4))
        lsb = int(match.group(5))
        desc = match.group(6) or ''

        # Skip unnamed padding fields
        if not field_name or field_name.startswith('_'):
            continue

        # Clean up description - remove line breaks and extra * characters
        desc = re.sub(r'\s*\*\s*', ' ', desc)
        desc = re.sub(r'\s+', ' ', desc)

        mask = ((1 << width) - 1) << lsb

        fields[field_name] = {
            'lsb': lsb,
            'msb': msb,
            'width': width,
            'mask': mask,
            'description': desc.strip()
        }

    return fields

def parse_svd(svd_file):
    tree = ET.parse(svd_file)
    return tree.getroot()

def extract_register_info(reg, periph_name=None, cmsis_db=None):
    info = {}
    name_elem = reg.find('name')
    if name_elem is not None:
        info['name'] = name_elem.text
    desc_elem = reg.find('description')
    if desc_elem is not None:
        info['description'] = desc_elem.text
    offset_elem = reg.find('addressOffset')
    if offset_elem is not None:
        info['offset'] = int(offset_elem.text, 16) if offset_elem.text else 0
    dim_elem = reg.find('dim')
    if dim_elem is not None:
        info['dim'] = int(dim_elem.text)
        dim_inc_elem = reg.find('dimIncrement')
        info['dim_inc'] = int(dim_inc_elem.text, 16) if dim_inc_elem is not None and dim_inc_elem.text else 0
        dim_idx_elem = reg.find('dimIndex')
        info['dim_index'] = dim_idx_elem.text if dim_idx_elem is not None else ''
    else:
        info['dim'] = 1
        info['dim_inc'] = 0
        info['dim_index'] = ''
    info['fields'] = {}
    fields_elem = reg.find('fields')
    if fields_elem is not None:
        for field in fields_elem:
            f_name = field.find('name')
            f_desc = field.find('description')
            lsb_elem = field.find('lsb')
            msb_elem = field.find('msb')
            if f_name is not None and lsb_elem is not None and msb_elem is not None:
                lsb = int(lsb_elem.text)
                msb = int(msb_elem.text)
                width = msb - lsb + 1
                mask = ((1 << width) - 1) << lsb
                f_info = {
                    'lsb': lsb,
                    'msb': msb,
                    'width': width,
                    'mask': mask,
                    'description': f_desc.text if f_desc is not None else ''
                }
                enums = []
                enum_vals_elem = field.find('enumeratedValues')
                if enum_vals_elem is not None:
                    for ev in enum_vals_elem.findall('enumeratedValue'):
                        ev_name = ev.find('name')
                        ev_desc = ev.find('description')
                        ev_val = ev.find('value')
                        if ev_name is not None and ev_val is not None:
                            val_str = ev_val.text
                            if val_str.startswith('#'):
                                val_str = val_str[1:]

                            # Handle binary string values (like "0010" which should be 2, not 10)
                            try:
                                width = f_info.get('width', 0)
                                val = parse_enum_value(val_str, width)
                            except Exception:
                                val = 0
                            enums.append((ev_name.text, val, ev_desc.text if ev_desc is not None else ''))
                if enums:
                    f_info['enums'] = enums
                info['fields'][f_name.text] = f_info

    # Apply CMSIS corrections if available
    if cmsis_db and periph_name:
        reg_name_clean = info.get('name', '').upper().replace('%S', '').replace('%s', '').replace('[]', '').replace('[%s]', '')
        periph_upper = periph_name.upper()

        # Map SVD peripheral name to CMSIS typedef name if needed
        cmsis_periph_name = SVD_TO_CMSIS_NAME_MAP.get(periph_upper, periph_upper)

        if cmsis_periph_name in cmsis_db and reg_name_clean in cmsis_db[cmsis_periph_name]:
            cmsis_reg = cmsis_db[cmsis_periph_name][reg_name_clean]

            # Correct register size if CMSIS has different/larger size
            svd_size_elem = reg.find('size')
            svd_size_bits = int(svd_size_elem.text) if svd_size_elem is not None and svd_size_elem.text else 32
            svd_size_bytes = svd_size_bits // 8
            cmsis_size_bytes = cmsis_reg.get('size', svd_size_bytes)

            if cmsis_size_bytes != svd_size_bytes:
                print(f"  CMSIS correction: {periph_name}.{reg_name_clean} size {svd_size_bits} bits -> {cmsis_size_bytes * 8} bits")
                info['size_override'] = cmsis_size_bytes

            # Merge CMSIS bitfields with SVD fields
            cmsis_fields = cmsis_reg.get('fields', {})
            if cmsis_fields:
                # Add missing fields from CMSIS
                for cf_name, cf_info in cmsis_fields.items():
                    if cf_name not in info['fields']:
                        print(f"  CMSIS adds field: {periph_name}.{reg_name_clean}.{cf_name}")
                        info['fields'][cf_name] = cf_info
                    else:
                        # Field exists in SVD - use CMSIS bit positions if they differ
                        svd_field = info['fields'][cf_name]
                        if svd_field['lsb'] != cf_info['lsb'] or svd_field['msb'] != cf_info['msb']:
                            print(f"  CMSIS corrects field: {periph_name}.{reg_name_clean}.{cf_name} [{svd_field['msb']}..{svd_field['lsb']}] -> [{cf_info['msb']}..{cf_info['lsb']}]")
                            info['fields'][cf_name].update({
                                'lsb': cf_info['lsb'],
                                'msb': cf_info['msb'],
                                'width': cf_info['width'],
                                'mask': cf_info['mask']
                            })

    return info


def to_int(val):
    """Convert val to int safely. Accepts int, hex/dec strings, or None."""
    if isinstance(val, int):
        return val
    if val is None:
        return 0
    if isinstance(val, str):
        s = val.strip()
        if s == '':
            return 0
        try:
            # int(..., 0) will handle 0x prefixes as well as decimal
            return int(s, 0)
        except ValueError:
            # Fallback: try to remove common prefixes then parse as hex
            try:
                if s.lower().startswith('0x'):
                    return int(s, 16)
            except Exception:
                pass
    # final fallback
    return int(val)


def parse_enum_value(val, width=0):
    """Parse an enumerated value string into an int with a field-width-aware heuristic.

    Heuristic rules:
      - If the value is an int already, return it.
      - Strip leading '#' if present (some SVDs use '#0010').
      - If the string is 0x... and the hex value fits in the field width, use hex.
      - If the string is 0x... but the hex value does NOT fit the field width, and
        the characters after 0x are only 0/1 and their binary value fits the field,
        interpret the suffix as binary (this handles mis-notated binary values like '0x10').
      - If the string looks like a plain binary string (only 0/1, length>=2), parse as binary.
      - Otherwise fall back to int(..., 0) and finally 0 on failure.
    """
    if isinstance(val, int):
        return val
    if val is None:
        return 0
    s = str(val).strip()
    if s == '':
        return 0
    if s.startswith('#'):
        s = s[1:]

    # compute mask for width if available
    mask = (1 << width) - 1 if width and width > 0 else None

    # Handle 0x... prefixed values specially
    if len(s) > 2 and s[:2].lower() == '0x':
        tail = s[2:]
        hex_val = None
        try:
            hex_val = int(s, 16)
        except Exception:
            hex_val = None

        bin_val = None
        if tail and all(c in '01' for c in tail):
            try:
                bin_val = int(tail, 2)
            except Exception:
                bin_val = None

        # Prefer hex if it fits the field
        if hex_val is not None and (mask is None or (hex_val & ~mask) == 0):
            return hex_val

        # If hex doesn't fit but binary interpretation does, use binary
        if bin_val is not None and (mask is None or (bin_val & ~mask) == 0):
            return bin_val

        # Fallback: return hex if available, else try auto-detect
        if hex_val is not None:
            return hex_val
        try:
            return int(s, 0)
        except Exception:
            return 0

    # Plain binary-like strings, e.g., '0010'
    if s.isdigit() and len(s) >= 2 and all(c in '01' for c in s):
        try:
            v = int(s, 2)
            return v
        except Exception:
            pass

    try:
        return int(s, 0)
    except Exception:
        # final attempt: hex parse
        try:
            if s.lower().startswith('0x'):
                return int(s, 16)
        except Exception:
            pass
    return 0


def sanitize_symbol(name):
    """Sanitize a string to be a valid macro identifier fragment (module-level).

    Replaces non-alphanumeric characters with underscore and uppercases the result.
    """
    if name is None:
        return ''
    s = re.sub(r'[^0-9A-Za-z]+', '_', str(name))
    s = s.strip('_')
    return s.upper()


def expand_dim_indices(dim_index):
    """Return a list of index strings for a dimIndex range.

    Supports formats like '0-7', '00-07', 'A-H', and hex ranges like 'A-F'.
    Falls back to splitting on commas or returns the original string.
    """
    if not dim_index:
        return []
    if '-' not in dim_index:
        # single index or comma-separated
        parts = [p.strip() for p in dim_index.split(',') if p.strip()]
        return parts
    start_s, end_s = dim_index.split('-', 1)
    start_s = start_s.strip()
    end_s = end_s.strip()
    # try decimal/auto base
    try:
        start = int(start_s, 0)
        end = int(end_s, 0)
        pad = max(len(start_s), len(end_s))
        return [f"{i:0{pad}d}" for i in range(start, end + 1)]
    except ValueError:
        pass
    # try hex (without 0x)
    try:
        start = int(start_s, 16)
        end = int(end_s, 16)
        pad = max(len(start_s), len(end_s))
        # use uppercase hex digits with zero padding
        return [format(i, 'X').zfill(pad) for i in range(start, end + 1)]
    except ValueError:
        pass
    # try letters
    if len(start_s) == 1 and len(end_s) == 1 and start_s.isalpha() and end_s.isalpha():
        start = ord(start_s)
        end = ord(end_s)
        return [chr(i) for i in range(start, end + 1)]
    # fallback: return the two endpoints
    return [start_s, end_s]

def generate_offsets(peripheral_name, reg_list, has_channel=False, channel_stride=0):
    output = []
    # Also return a mapping of clean register base name -> offset macro base name
    # This allows generate_register_addresses to refer to the exact macro name
    # chosen here (for example when we append an _IDX suffix for indexed arrays).
    offset_name_map = {}

    # Special handling for PFS: generate parameterized macros instead of individual pin offsets
    if peripheral_name.upper() == 'PFS':
        output.append("/* PFS Register Offsets - Use R_PFS_OFFSET(port, pin) macro */")
        output.append("#define R_PFS_OFFSET(port, pin)    ((port) * 0x40 + (pin) * 0x04)")
        output.append("#define R_PFS_HA_OFFSET(port, pin) ((port) * 0x40 + (pin) * 0x04)")
        output.append("#define R_PFS_BY_OFFSET(port, pin) ((port) * 0x40 + (pin) * 0x04)")
        output.append("")

        # Helper to convert offset values
        def to_int(val):
            if isinstance(val, int):
                return val
            if val is None:
                return 0
            if isinstance(val, str):
                s = val.strip()
                if s == '':
                    return 0
                try:
                    return int(s, 0)
                except ValueError:
                    try:
                        if s.lower().startswith('0x'):
                            return int(s, 16)
                    except Exception:
                        pass
            return int(val)

        # Add special PFS registers (non-pin related)
        sar_seen = False  # Track if we've already output a SAR register
        for reg_info in sorted(reg_list, key=lambda x: x.get('base_offset', 0)):
            reg_base = reg_info.get('name', '')

            # Skip all PmnPFS registers (including _HA and _BY variants)
            # Pattern: P followed by port (0-9, A-B), pin (0-9, 00-15), then PFS[_HA|_BY]
            # Examples to skip: P000PFS, P000PFS_HA, P000PFS_BY, P00PFS_HA, PA0PFS, PB07PFS_BY
            if reg_base.startswith('P') and 'PFS' in reg_base:
                # Check if it's a pin-specific register (has digit or letter after P)
                after_p = reg_base[1:]  # Everything after 'P'
                # If it starts with a digit (port number) or letter (A, B for ports 10, 11)
                if after_p and (after_p[0].isdigit() or after_p[0] in 'ABCD'):
                    # This is a pin-specific register like P000PFS, P10PFS_HA, PA0PFS_BY
                    # Skip it - we use parameterized macros instead
                    continue

            reg_offset = to_int(reg_info.get('offset', 0))
            desc = reg_info['description']
            dim = reg_info.get('dim', 1)
            dim_index = reg_info.get('dim_index', '')

            if dim > 1 and dim_index and 'SAR' in reg_base:
                # Handle P%sSAR registers - only output base offset ONCE, use parameterized macro for addresses
                if not sar_seen:
                    sar_seen = True
                    # Only define the first one (base offset for parameterized macro)
                    clean_name = reg_base.replace('%s', '0').replace('%S', '0')
                    output.append("")
                    output.append(f"/* Port Security Attribution register offset */")
                    output.append(f"#define R_{peripheral_name.upper()}_{clean_name.upper()}_OFFSET              {reg_offset:#010x}")
                # Skip subsequent SAR register groups - already covered by parameterized macro
            elif 'PFENET' in reg_base:
                clean_name = reg_base.replace('[%s]', '').replace('[%S]', '').replace('%s', '').replace('%S', '').replace('[]', '')
                output.append(f"/* Ethernet Control Register */")
                output.append(f"#define R_{peripheral_name.upper()}_{clean_name.upper()}_OFFSET             {reg_offset:#010x}")
            elif 'PWPR' in reg_base:
                clean_name = reg_base.replace('[%s]', '').replace('[%S]', '').replace('%s', '').replace('%S', '').replace('[]', '')
                output.append("")
                output.append(f"/* Write-Protect Register for Secure */")
                output.append(f"#define R_{peripheral_name.upper()}_{clean_name.upper()}_OFFSET             {reg_offset:#010x}")
            else:
                clean_name = reg_base.replace('[%s]', '').replace('[%S]', '').replace('%s', '').replace('%S', '').replace('[]', '')
                output.append(f"#define R_{peripheral_name.upper()}_{clean_name.upper()}_OFFSET     {reg_offset:#010x}  /* {desc} */")

    # Original logic for non-PFS peripherals
    def to_int(val):
        """Convert val to int safely. Accepts int, hex/dec strings, or None."""
        if isinstance(val, int):
            return val
        if val is None:
            return 0
        if isinstance(val, str):
            s = val.strip()
            if s == '':
                return 0
            try:
                # int(..., 0) will handle 0x prefixes as well as decimal
                return int(s, 0)
            except ValueError:
                # Fallback: try to remove common prefixes then parse as hex
                try:
                    if s.lower().startswith('0x'):
                        return int(s, 16)
                except Exception:
                    pass
        # final fallback
        return int(val)
    # Helper function for consistent padding
    def pad_define(macro_name, value_str, min_width=50):
        """Pad macro definition for alignment"""
        define_part = f"#define {macro_name}"
        padding = max(1, min_width - len(define_part))
        return f"{define_part}{' ' * padding}{value_str}"

    # Track defined offset macros to avoid duplicates
    # Store both parameterized (with (m)) and non-parameterized base names
    defined_offsets = set()
    defined_base_names = set()  # Track base names without (m) suffix

    for reg_info in sorted(reg_list, key=lambda x: x.get('base_offset', 0)):
        dim = reg_info.get('dim', 1)
        reg_base = reg_info.get('name', '')
        reg_offset = to_int(reg_info.get('offset', 0))
        dim_inc = to_int(reg_info.get('dim_inc', 0))
        dim_index = reg_info['dim_index']
        desc = reg_info['description']

        # Normalize register name: replace %s (lowercase), %S (uppercase), [] patterns
        # These are placeholders in SVD that need to be expanded or removed
        has_placeholder = '%s' in reg_base.lower() or '[]' in reg_base or '[%s]' in reg_base.lower()

        if dim > 1 or (dim == 1 and has_placeholder and dim_index):
            # Multiple registers OR single register with placeholder that needs expansion
            # Preserve original register base (with placeholders) so we can create
            # a stable 'x' placeholder variant when avoiding collisions.
            orig_name = reg_base
            clean_name = reg_base.replace('[%s]', '').replace('[%S]', '').replace('%s', '').replace('%S', '').replace('[]', '')

            # Generate comment showing the range
            output.append(f"/* {reg_base} Registers ({dim_index}) */")

            if dim_inc > 0 and dim > 1:
                # Array with stride - generate parameterized offset macro
                macro_name = f"R_{peripheral_name.upper()}_{clean_name.upper()}_OFFSET(m)"
                base_name = f"R_{peripheral_name.upper()}_{clean_name.upper()}_OFFSET"
                # If a non-parameterized base name already exists, avoid collision by appending a suffix
                safe_clean = None
                if base_name in defined_offsets or base_name in defined_base_names:
                    # Previously we appended _IDX to avoid collisions. That created
                    # a lot of churn in headers. Instead, use a stable 'x' placeholder
                    # in the base macro name for indexed registers (RXRSSxR style)
                    # so that the non-parameterized scalar base remains unchanged.
                    # Use the original register name (which may contain %s/[] placeholders)
                    # to construct the 'x' variant. Replace known placeholder tokens
                    # (%s, %S, [], [%s], [%S]) with 'x'. Then sanitize the result.
                    safe_fragment = orig_name.replace('%s', 'x').replace('%S', 'x').replace('[%s]', 'x').replace('[%S]', 'x').replace('[]', 'x')
                    safe_clean = sanitize_symbol(safe_fragment)
                    # Ensure uniqueness: if this safe_clean is already used, append
                    # numeric suffixes until we find an unused variant (safe_clean_2, _3, ...)
                    candidate = safe_clean
                    suffix = 1
                    while f"R_{peripheral_name.upper()}_{candidate}_OFFSET" in defined_base_names or f"R_{peripheral_name.upper()}_{candidate}_OFFSET" in defined_offsets:
                        suffix += 1
                        candidate = f"{safe_clean}_{suffix}"
                    safe_clean = candidate
                    macro_name = f"R_{peripheral_name.upper()}_{safe_clean}_OFFSET(m)"
                    base_name = f"R_{peripheral_name.upper()}_{safe_clean}_OFFSET"

                if macro_name not in defined_offsets:
                    defined_offsets.add(macro_name)
                    defined_base_names.add(base_name)  # Mark base name as used by parameterized version
                    # Record mapping from the stripped clean base to the actual offset macro base name
                    # so generate_register_addresses can find the correct offset macro even
                    # when the macro base was created from the 'x' placeholder variant.
                    offset_name_map[clean_name.upper()] = base_name
                    # Also map the safe placeholder variant key for completeness.
                    if safe_clean:
                        offset_name_map[safe_clean.upper()] = base_name
                    value_str = f"({reg_offset:#010x} + ((m) * {dim_inc:#010x}))"
                    output.append(f"{pad_define(macro_name, value_str)}  /* {desc} */")
            else:
                # Single offset with placeholder
                macro_name = f"R_{peripheral_name.upper()}_{clean_name.upper()}_OFFSET"
                # If a parameterized base already exists, prefer parameterized naming to avoid duplicate base
                if macro_name in defined_base_names:
                    # skip creating a conflicting non-parameterized macro
                    continue
                # Skip if a parameterized version already exists
                if macro_name not in defined_offsets and macro_name not in defined_base_names:
                    defined_offsets.add(macro_name)
                    output.append(f"{pad_define(macro_name, f'{reg_offset:#010x}')}  /* {desc} */")
                    offset_name_map[clean_name.upper()] = macro_name
        else:
            # Single register without placeholder - clean up any stray placeholders just in case
            clean_name = reg_base.replace('[%s]', '').replace('[%S]', '').replace('%s', '').replace('%S', '').replace('[]', '')
            macro_name = f"R_{peripheral_name.upper()}_{clean_name.upper()}_OFFSET"

            # Skip if already defined OR if a parameterized version exists
            if macro_name in defined_offsets or macro_name in defined_base_names:
                continue

            defined_offsets.add(macro_name)
            output.append(f"{pad_define(macro_name, f'{reg_offset:#010x}')}  /* {desc} */")
            offset_name_map[clean_name.upper()] = macro_name
    return output, offset_name_map

    # Special-case: CANFD RX message buffers are organized in blocks; generate
    # compact helper macros that compute per-buffer offsets rather than emitting
    # individual repeated offset groups. This keeps headers small and matches
    # the manual style used in canonical headers.
    if peripheral_name.upper() == 'CANFD':
        output.append('/* Common helpers for message buffers */')
        output.append('#define CANFD_RX_MB_STRIDE                        0x4C      /* 0x004C × b */')
        output.append('#define CANFD_RX_MB_BLOCK_SEL(b)                  (((b) < 8) ? 0U : 1U)')
        output.append('#define CANFD_RX_MB_BLOCK_OFF(b)                  (CANFD_RX_MB_BLOCK_SEL(b) * 0x400) /* 0x0D20-0x0920 = 0x400 */')
        output.append('#define CANFD_RX_MB_INDEX_IN_BLOCK(b)             ((b) - (CANFD_RX_MB_BLOCK_SEL(b) * 8))')
        output.append('')
        output.append('/* Base offsets per block (block 0: b=0..7, block 1: b=8..15) */')
        output.append('#define CANFD_CFDRMID_BLOCK_BASE                    0x0920    /* CFDRMIDb */')
        output.append('#define CANFD_CFDRMPTR_BLOCK_BASE                   0x0924    /* CFDRMPTRb */')
        output.append('#define CANFD_CFDRMFDSTS_BLOCK_BASE                 0x0928    /* CFDRMFDSTSb */')
        output.append('#define CANFD_CFDRMDF_BLOCK_BASE                    0x092C    /* CFDRMDFb_p */')
        output.append('')
        output.append('/* Per-register offsets inside a block */')
        output.append('#define CANFD_CFDRMID_OFF_IN_BLOCK                  0x0000')
        output.append('#define CANFD_CFDRMPTR_OFF_IN_BLOCK                 0x0004')
        output.append('#define CANFD_CFDRMFDSTS_OFF_IN_BLOCK               0x0008')
        output.append('#define CANFD_CFDRMDF_OFF_IN_BLOCK                  0x000C')
        output.append('')
        output.append('#define R_CANFD_CFDRMID_IDX_OFFSET(b) \\')
        output.append('    ( (CANFD_CFDRMID_BLOCK_BASE + CANFD_RX_MB_BLOCK_OFF(b)) + (CANFD_RX_MB_INDEX_IN_BLOCK(b) * CANFD_RX_MB_STRIDE) + CANFD_CFDRMID_OFF_IN_BLOCK )')
        output.append('')
        output.append('#define R_CANFD_CFDRMPTR_IDX_OFFSET(b) \\')
        output.append('    ( (CANFD_CFDRMPTR_BLOCK_BASE + CANFD_RX_MB_BLOCK_OFF(b)) + (CANFD_RX_MB_INDEX_IN_BLOCK(b) * CANFD_RX_MB_STRIDE) + CANFD_CFDRMPTR_OFF_IN_BLOCK )')
        output.append('')
        output.append('#define R_CANFD_CFDRMFDSTS_IDX_OFFSET(b) \\')
        output.append('    ( (CANFD_CFDRMFDSTS_BLOCK_BASE + CANFD_RX_MB_BLOCK_OFF(b)) + (CANFD_RX_MB_INDEX_IN_BLOCK(b) * CANFD_RX_MB_STRIDE) + CANFD_CFDRMFDSTS_OFF_IN_BLOCK )')
        output.append('')
        output.append('#define R_CANFD_CFDRMDF_IDX_OFFSET(b, p) \\')
        output.append('    ( (CANFD_CFDRMDF_BLOCK_BASE + CANFD_RX_MB_BLOCK_OFF(b)) + \\')
        output.append('      (CANFD_RX_MB_INDEX_IN_BLOCK(b) * CANFD_RX_MB_STRIDE) + \\')
        output.append('      CANFD_CFDRMDF_OFF_IN_BLOCK + ((p) * 0x4) )')
        output.append('')

        # Map clean register base names to our index-offset macros so the
        # address generator emits address macros that reference the idx macros.
        offset_name_map['CFDRMID'] = 'R_CANFD_CFDRMID_IDX_OFFSET'
        offset_name_map['CFDRMPTR'] = 'R_CANFD_CFDRMPTR_IDX_OFFSET'
        offset_name_map['CFDRMFDSTS'] = 'R_CANFD_CFDRMFDSTS_IDX_OFFSET'
        offset_name_map['CFDRMDF'] = 'R_CANFD_CFDRMDF_IDX_OFFSET'

        return output, offset_name_map

def generate_register_addresses(peripheral_name, reg_list, has_channel=False, channel_stride=0, num_instances=1, offset_map=None):
    """Generate register address definitions from offsets.

    Creates #define statements for register addresses by combining base address with offsets.
    Example: #define R_MSTP_MSTPCRA  (R_MSTP_BASE + R_MSTP_MSTPCRA_OFFSET)

    For PFS peripheral, generates parameterized macros instead:
    Example: #define R_PFS(port,pin)  (R_PFS_BASE + (port)*0x40 + (pin)*0x04)

    Args:
        num_instances: Number of peripheral instances (e.g., 10 for PORT0-PORT9)
                      Only use channel-based macros if num_instances > 1
    """
    output = []

    # Check if this peripheral actually has multiple instances
    # Only use channel-based macros if num_instances > 1
    use_channel_macros = has_channel and channel_stride > 0 and num_instances > 1

    # Special handling for PFS peripheral - use parameterized macros
    if peripheral_name.upper() == 'PFS':
        output.append("/* PFS Register Parameterized Macros */")
        output.append("")
        output.append("/* PmnPFS - Pin Function Select Register */")
        output.append("#define R_PFS(port,pin)                 (R_PFS_BASE + (port)*R_PFS_PSEL_PORT_OFFSET + (pin)*R_PFS_PSEL_PIN_OFFSET)")
        output.append("")
        output.append("/* Alternate register formats */")
        output.append("#define R_PFS_HA(port,pin)              (R_PFS_BASE + (port)*R_PFS_PSEL_PORT_OFFSET + (pin)*R_PFS_PSEL_PIN_OFFSET)")
        output.append("#define R_PFS_BY(port,pin)              (R_PFS_BASE + (port)*R_PFS_PSEL_PORT_OFFSET + (pin)*R_PFS_PSEL_PIN_OFFSET)")
        output.append("")
        output.append("/* Other PFS registers */")
        output.append("#define R_PFS_PFENET                    (R_PFS_BASE + R_PFS_PFENET_OFFSET)")
        output.append("#define R_PFS_PWPR                      (R_PFS_BASE + R_PFS_PWPR_S_OFFSET)")
        output.append("")
        output.append("/* Port Security Attribution Registers */")
        output.append("#define R_PFS_PMSAR(port)               (R_PFS_BASE + R_PFS_P0SAR_OFFSET + (port)*0x04)")
        return output

    def to_int(val):
        """Convert val to int safely. Accepts int, hex/dec strings, or None."""
        if isinstance(val, int):
            return val
        if val is None:
            return 0
        if isinstance(val, str):
            s = val.strip()
            if s == '':
                return 0
            try:
                return int(s, 0)
            except ValueError:
                try:
                    if s.lower().startswith('0x'):
                        return int(s, 16)
                except Exception:
                    pass
        return int(val)

    # Helper function for consistent padding
    def pad_define(macro_name, value_str, min_width=50):
        """Pad macro definition for alignment"""
        define_part = f"#define {macro_name}"
        padding = max(1, min_width - len(define_part))
        return f"{define_part}{' ' * padding}{value_str}"

    # Track defined address macros to avoid duplicates
    # Also track base names that have parameterized versions
    defined_addresses = set()
    parameterized_bases = set()
    # Normalized offset_map for lookup
    offset_map = offset_map or {}

    for reg_info in sorted(reg_list, key=lambda x: x.get('base_offset', 0)):
        dim = reg_info.get('dim', 1)
        reg_base = reg_info.get('name', '')
        reg_offset = to_int(reg_info.get('offset', 0))
        dim_inc = to_int(reg_info.get('dim_inc', 0))
        dim_index = reg_info['dim_index']

        # Normalize register name: replace %s (lowercase), %S (uppercase), [] patterns
        has_placeholder = '%s' in reg_base.lower() or '[]' in reg_base or '[%s]' in reg_base.lower()

        if dim > 1 or (dim == 1 and has_placeholder and dim_index):
            # Multiple registers OR single register with placeholder that needs expansion
            # Generate parameterized macro instead of expanding
            clean_name = reg_base.replace('[%s]', '').replace('[%S]', '').replace('%s', '').replace('%S', '').replace('[]', '')

            # Generate parameterized macro - use different parameter names based on peripheral type
            if peripheral_name.upper() == 'ICU':
                param_name = 'p'
            elif peripheral_name.upper() == 'PORT':
                param_name = 'port'
            elif peripheral_name.upper().endswith('_B'):
                param_name = 'n'
            else:
                param_name = 'n'

            # Determine the fragment to use for address macro names. If an offset
            # macro base was chosen by generate_offsets (possibly using an 'x'
            # placeholder), prefer the fragment from that offset macro so the
            # address macro name matches the offset macro base.
            offset_macro_base = offset_map.get(clean_name.upper(), f"R_{peripheral_name.upper()}_{clean_name.upper()}_OFFSET")
            prefix = f"R_{peripheral_name.upper()}_"
            frag = None
            if offset_macro_base.startswith(prefix) and offset_macro_base.endswith('_OFFSET'):
                frag = offset_macro_base[len(prefix):-len('_OFFSET')]
            else:
                frag = clean_name.upper()
            frag_upper = frag.upper()

            if dim_inc > 0 and dim > 1:
                # Array with stride - generate parameterized macro with two parameters
                # First parameter for channel, second for register index
                if use_channel_macros:
                    # Multi-channel peripheral with register arrays
                    macro_name = f"R_{peripheral_name.upper()}_{frag_upper}({param_name}, m)"
                    if macro_name not in defined_addresses:
                        defined_addresses.add(macro_name)
                        parameterized_bases.add(clean_name.upper())
                        # Use offset_map if available to reference the exact offset macro name
                        value_str = f"(R_{peripheral_name.upper()}_CH_BASE({param_name}) + {offset_macro_base}(m))"
                        output.append(pad_define(macro_name, value_str))
                else:
                    # Single channel with register array
                    macro_name = f"R_{peripheral_name.upper()}_{frag_upper}(m)"
                    if macro_name not in defined_addresses:
                        defined_addresses.add(macro_name)
                        parameterized_bases.add(clean_name.upper())
                        value_str = f"(R_{peripheral_name.upper()}_BASE + {offset_macro_base}(m))"
                        output.append(pad_define(macro_name, value_str))
            else:
                # Single register with placeholder - check if peripheral has channels
                if use_channel_macros:
                    # Multi-channel peripheral
                    macro_name = f"R_{peripheral_name.upper()}_{frag_upper}({param_name})"
                    if macro_name not in defined_addresses:
                        defined_addresses.add(macro_name)
                        parameterized_bases.add(clean_name.upper())
                        value_str = f"(R_{peripheral_name.upper()}_CH_BASE({param_name}) + {offset_macro_base})"
                        output.append(pad_define(macro_name, value_str))
                else:
                    # Single channel peripheral with placeholder
                    macro_name = f"R_{peripheral_name.upper()}_{frag_upper}"
                    if macro_name not in defined_addresses and clean_name.upper() not in parameterized_bases:
                        defined_addresses.add(macro_name)
                        parameterized_bases.add(clean_name.upper())  # Mark to prevent later duplicates
                        value_str = f"(R_{peripheral_name.upper()}_BASE + {offset_macro_base})"
                        output.append(pad_define(macro_name, value_str))
        else:
            # Single register without placeholder - clean up any stray placeholders just in case
            clean_name = reg_base.replace('[%s]', '').replace('[%S]', '').replace('%s', '').replace('%S', '').replace('[]', '')

            # Skip if there's a parameterized version
            if clean_name.upper() in parameterized_bases:
                continue

            # Check if peripheral has multiple instances
            if use_channel_macros:
                # Multi-channel peripheral
                param_name = 'port' if peripheral_name.upper() == 'PORT' else 'n'
                macro_name = f"R_{peripheral_name.upper()}_{clean_name.upper()}({param_name})"
                if macro_name not in defined_addresses:
                    defined_addresses.add(macro_name)
                    value_str = f"(R_{peripheral_name.upper()}_CH_BASE({param_name}) + R_{peripheral_name.upper()}_{clean_name.upper()}_OFFSET)"
                    output.append(pad_define(macro_name, value_str))
            else:
                # Single instance peripheral
                macro_name = f"R_{peripheral_name.upper()}_{clean_name.upper()}"
                if macro_name not in defined_addresses:
                    defined_addresses.add(macro_name)
                    value_str = f"(R_{peripheral_name.upper()}_BASE + R_{peripheral_name.upper()}_{clean_name.upper()}_OFFSET)"
                    output.append(pad_define(macro_name, value_str))

    return output

def generate_bit_defs(peripheral_name, reg_list, has_channel=False):
    """Generate bit field definitions with consistent padding for alignment."""
    output = []

    # Helper function to calculate proper padding for macro names
    def get_padded_define(macro_name, value_str, min_width=40):
        """Return properly padded #define line without comment."""
        define_part = f"#define {macro_name}"
        # Calculate padding to align values at column min_width
        padding = max(1, min_width - len(define_part))
        return f"{define_part}{' ' * padding}{value_str}"

    # Helper: sanitize a string to be a valid macro identifier fragment
    def sanitize_symbol(name):
        # Replace any non-alphanumeric characters with underscore, strip leading/trailing underscores
        if name is None:
            return ''
        s = re.sub(r'[^0-9A-Za-z]+', '_', str(name))
        s = s.strip('_')
        return s.upper()

    # Special handling for PFS peripheral - only generate common bit definitions
    if peripheral_name.upper() == 'PFS':
        output.append("/* PFS Common Bit Definitions (applicable to all PmnPFS registers) */")
        output.append("")

        # Find the first PFS register with fields (usually P00PFS or similar)
        for reg_info in reg_list:
            reg_name = reg_info.get('name', '')
            fields = reg_info.get('fields', {})

            # Look for a PmnPFS register (not _HA, not _BY, has fields)
            if fields and 'PFS' in reg_name.upper() and '_HA' not in reg_name.upper() and '_BY' not in reg_name.upper():
                # Generate common bit definitions using R_PFS prefix
                for f_name, f_info in fields.items():
                    lsb = f_info['lsb']
                    mask = f_info['mask']
                    width = f_info['width']
                    desc = f_info['description']
                    safe_field = sanitize_symbol(f_name)
                    if width == 1:
                        macro_name = f"R_PFS_{safe_field}"
                        output.append(f"{get_padded_define(macro_name, f'(1 << {lsb})', 40)}  /* {desc} */")
                    else:
                        # SHIFT definition
                        macro_name = f"R_PFS_{safe_field}_SHIFT"
                        output.append(f"{get_padded_define(macro_name, f'({lsb})', 40)}  /* {desc} */")
                        # MASK definition
                        macro_name = f"R_PFS_{safe_field}_MASK"
                        output.append(f"{get_padded_define(macro_name, f'{hex(mask)}', 40)}")
                        # Enum values
                        if 'enums' in f_info:
                            for en_name, en_val, en_desc in f_info['enums']:
                                shift_val = f"R_PFS_{safe_field}_SHIFT"
                                enum_macro = f"R_PFS_{safe_field}_{sanitize_symbol(en_name)}"
                                output.append(f"#  define {enum_macro:38}({en_val} << {shift_val})  /* {en_desc} */")
                    output.append("")

                # Only process the first valid PFS register, then break
                break

        # Add PWPR register bit definitions if present
        for reg_info in reg_list:
            reg_name = reg_info.get('name', '')
            fields = reg_info.get('fields', {})
            if 'PWPR' in reg_name.upper() and fields:
                output.append("/* PWPR - Write-Protect Register */")
                output.append("")
                for f_name, f_info in fields.items():
                    lsb = f_info['lsb']
                    desc = f_info['description']
                    safe_field = sanitize_symbol(f_name)
                    macro_name = f"R_PWPR_{safe_field}"
                    output.append(f"{get_padded_define(macro_name, f'({lsb})', 40)}  /* {desc} */")
                output.append("")
                break

        return output

    # Standard processing for non-PFS peripherals
    for reg_info in reg_list:
        reg_name = reg_info.get('name', '')
        fields = reg_info.get('fields', {})
        if not fields:
            continue

        # Normalize register name for macros when peripheral has channels
        macro_reg_name = reg_name
        if has_channel:
            # remove %s patterns
            macro_reg_name = macro_reg_name.replace('%s', '')
            # Only strip trailing digits if this register has dim > 1 (is actually an array)
            # Don't strip digits from register names like SCKDIVCR2, HOCOCR2, etc.
            dim = reg_info.get('dim', 1)
            if dim > 1:
                # strip trailing digits (e.g., REG0 -> REG)
                while len(macro_reg_name) > 0 and macro_reg_name[-1].isdigit():
                    macro_reg_name = macro_reg_name[:-1]

        # Sanitize macro register name to remove brackets, spaces and other non-id chars
        macro_reg_name = sanitize_symbol(macro_reg_name)

        output.append(f"/* {macro_reg_name} Register bit definitions */")
        for f_name, f_info in fields.items():
            lsb = f_info['lsb']
            mask = f_info['mask']
            width = f_info['width']
            desc = f_info['description']
            safe_field = sanitize_symbol(f_name)
            # Ensure all generated bit macros use the R_ prefix to match project convention
            pref = 'R_'  # prefix for register bit macros
            if width == 1:
                macro_name = f"{pref}{peripheral_name.upper()}_{macro_reg_name}_{safe_field}"
                output.append(f"{get_padded_define(macro_name, f'(1 << {lsb})', 50)}  /* {desc} */")
            else:
                # SHIFT definition
                macro_name = f"{pref}{peripheral_name.upper()}_{macro_reg_name}_{safe_field}_SHIFT"
                output.append(f"{get_padded_define(macro_name, f'({lsb})', 50)}  /* {desc} */")
                # MASK definition
                macro_name = f"{pref}{peripheral_name.upper()}_{macro_reg_name}_{safe_field}_MASK"
                output.append(f"{get_padded_define(macro_name, f'{hex(mask)}', 50)}")
                # Enum values
                if 'enums' in f_info:
                    for en_name, en_val, en_desc in f_info['enums']:
                        shift_val = f"{pref}{peripheral_name.upper()}_{macro_reg_name}_{safe_field}_SHIFT"
                        # Prefix enum macro with R_ and include field name to prevent redefinitions
                        enum_macro = f"{pref}{peripheral_name.upper()}_{macro_reg_name}_{safe_field}_{sanitize_symbol(en_name)}"

                        # Parse enumerated value with heuristic
                        try:
                            parsed_val = parse_enum_value(en_val, width)
                        except Exception:
                            try:
                                parsed_val = int(str(en_val).strip(), 0)
                            except Exception:
                                parsed_val = 0

                        output.append(f"#  define {enum_macro:48}({parsed_val} << {shift_val})  /* {en_desc} */")
            output.append("")
    return output


def compute_channel_stride(reg_list):
    """Guess a reasonable channel stride from registers with dim>1.

    Returns the first non-zero dim_inc found, or 0 if none.
    """
    for reg in reg_list:
        try:
            dim = reg.get('dim', 1)
            dim_inc = int(reg.get('dim_inc', 0))
            if dim > 1 and dim_inc:
                return dim_inc
        except Exception:
            continue
    return 0
def detect_max_channels(reg_list):
    """Detect maximum channel count and whether the peripheral is channel-like.

    Returns (max_ch, has_channel)
    """
    max_ch = 0
    has_channel = False
    for reg in reg_list:
        name = reg.get('name', '')
        dim = reg.get('dim', 1)
        if '%' in name or any(k in name.upper() for k in ('CH', 'ADDR', 'CHANNEL')) or dim > 1:
            has_channel = True
            max_ch = max(max_ch, int(dim))
    return max_ch, has_channel


def get_base_peripheral_name(peripheral_name):
    """Extract base peripheral name without channel number or _NS suffix.

    Examples:
        CANFD0 -> CANFD
        CANFD1_NS -> CANFD
        SCI0_B -> SCI_B
        GPT320 -> GPT32
        DMAC00 -> DMAC (double-digit channel)
        GPT3210 -> GPT32 (double-digit channel 10)
        DAC120 -> DAC12 (single-digit channel after "12")
        ADC_B_NS -> ADC_B
    """
    import re
    # Remove _NS suffix first
    name = peripheral_name
    is_nonsecure = name.endswith('_NS')
    if is_nonsecure:
        name = name[:-3]

    # Special case: PORT with letter suffix (PORTA, PORTB, PORTC, PORTD)
    # These represent channels 10, 11, 12, 13 (0xA, 0xB, 0xC, 0xD in hex)
    # Should be grouped with PORT0-PORT9
    match = re.match(r'^(PORT)([A-D])$', name)
    if match:
        base = match.group(1)
        return base, is_nonsecure

    # Try to strip trailing single digit with suffix (SCI0_B -> SCI_B)
    match = re.match(r'^(.+?)(\d)(_[A-Z]+)$', name)
    if match:
        base = match.group(1) + match.group(3)
        return base, is_nonsecure

    # Check if name ends with 4 digits (e.g., GPT3210 -> GPT32, strip last 2 digits)
    # This handles peripherals with channel numbers >= 10
    match = re.match(r'^(.+?)(\d{4})$', name)
    if match:
        base_part = match.group(1)
        four_digits = match.group(2)
        # Keep first 2 digits, strip last 2 (channel number)
        base = base_part + four_digits[:2]
        return base, is_nonsecure

    # Try to strip trailing two digits that look like channel numbers
    # Example: DMAC00 -> DMAC (no digit before 00)
    # Example: GPT320 -> GPT32 (has digit '2' before '0')
    match = re.match(r'^(.+?)(\d)(\d)$', name)
    if match:
        base = match.group(1)
        tens_digit = match.group(2)
        ones_digit = match.group(3)

        # If base doesn't end with a digit, these 2 digits are a double-digit channel
        if base and not base[-1].isdigit():
            return base, is_nonsecure
        else:
            # Base ends in a digit, keep the base AND tens digit, strip only ones
            base_with_tens = base + tens_digit
            return base_with_tens, is_nonsecure

    # Try to strip trailing single digit (e.g., CANFD0 -> CANFD)
    match = re.match(r'^(.+?)(\d)$', name)
    if match:
        base = match.group(1)
        return base, is_nonsecure

    # No channel number found, return the name without _NS
    return name, is_nonsecure
def generate_content(peripheral_name, base_addr, offsets, reg_addrs, bit_defs, max_ch, has_channel=False, channel_stride=0, base_addr_ns=None, num_instances=1):
    """Assemble the header file content for a peripheral.

    Args:
        peripheral_name: Base peripheral name (without channel number or _NS)
        base_addr: Secure base address (or default if no NS variant)
        offsets: Register offset definitions
        reg_addrs: Register address definitions
        bit_defs: Bit field definitions
        max_ch: Maximum channel count
        has_channel: Whether peripheral has channels
        channel_stride: Stride between channels
        base_addr_ns: Non-secure base address (optional, for TZ builds)
    """
    lines = []
    lines.append('/****************************************************************************')
    lines.append(f' * arch/arm/src/ra8/hardware/{mcu}/ra_{peripheral_name.lower()}.h')
    lines.append(' *')
    lines.append(' * Licensed to the Apache Software Foundation (ASF) under one or more')
    lines.append(' * contributor license agreements.  See the NOTICE file distributed with')
    lines.append(' * this work for additional information regarding copyright ownership.  The')
    lines.append(' * ASF licenses this file to you under the Apache License, Version 2.0 (the')
    lines.append(' * "License"); you may not use this file except in compliance with the')
    lines.append(' * License.  You may obtain a copy of the License at')
    lines.append(' *')
    lines.append(' *   http://www.apache.org/licenses/LICENSE-2.0')
    lines.append(' *')
    lines.append(' * Unless required by applicable law or agreed to in writing, software')
    lines.append(' * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT')
    lines.append(' * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the')
    lines.append(' * License for the specific language governing permissions and limitations')
    lines.append(' * under the License.')
    lines.append(' *')
    lines.append(' ****************************************************************************/')
    lines.append('')
    lines.append(f'#ifndef __ARCH_ARM_SRC_RA8_HARDWARE_{MCU}_{peripheral_name.upper()}_H')
    lines.append(f'#define __ARCH_ARM_SRC_RA8_HARDWARE_{MCU}_{peripheral_name.upper()}_H')
    lines.append('')
    lines.append('/****************************************************************************')
    lines.append(' * Included Files')
    lines.append(' ****************************************************************************/')
    lines.append('')
    lines.append('/****************************************************************************')
    lines.append(' * Pre-processor Definitions')
    lines.append(' ****************************************************************************/')
    lines.append('')
    lines.append(f'/* {peripheral_name.upper()} Base Address */')
    lines.append(f'#ifndef R_{peripheral_name.upper()}_BASE')

    # Generate conditional base address if we have both secure and non-secure variants
    if base_addr_ns is not None and base_addr_ns != base_addr:
        lines.append('#if !defined(CONFIG_RA_TZ_NONSECURE_BUILD) || (CONFIG_RA_TZ_NONSECURE_BUILD == 0)')
        lines.append(f'#define R_{peripheral_name.upper()}_BASE           {base_addr:#010x}')
        lines.append('#else')
        lines.append(f'#define R_{peripheral_name.upper()}_BASE           {base_addr_ns:#010x}')
        lines.append('#endif')
    else:
        lines.append(f'#define R_{peripheral_name.upper()}_BASE           {base_addr:#010x}')

    lines.append('#endif')

    lines.append('')

    # Add PFS-specific constants for parameterized macros
    if peripheral_name.upper() == 'PFS':
        lines.append('/* PFS Register Array Strides */')
        lines.append('#define R_PFS_PSEL_PORT_OFFSET          0x40')
        lines.append('#define R_PFS_PSEL_PIN_OFFSET           0x04')
        lines.append('')

    # Only emit channel stride/base macros when the peripheral actually has multiple instances
    # (e.g., PORT0..PORT9 or CANFD0..CANFD1). Do not emit for single-instance peripherals that
    # merely have register arrays or placeholders.
    if num_instances > 1:
        stride = channel_stride or 0
        if stride:
            lines.append('/* Channel stride for multi-channel peripherals */')
            lines.append(f'#define R_{peripheral_name.upper()}_CH_STRIDE    {stride:#010x}')
        lines.append(f'#define R_{peripheral_name.upper()}_CH_BASE(ch)   (R_{peripheral_name.upper()}_BASE + ((uint32_t)(ch) * R_{peripheral_name.upper()}_CH_STRIDE))')
        lines.append('')

    lines.append(f'/* {peripheral_name.upper()} Register Offsets */')
    lines.append('')
    for line in offsets:
        lines.append(line)

    lines.append('')
    lines.append(f'/* {peripheral_name.upper()} Register Addresses */')
    lines.append('')
    for line in reg_addrs:
        lines.append(line)

    lines.append('')
    lines.append('/* Register bit definitions */')
    for line in bit_defs:
        lines.append(line)

    if max_ch > 0:
        lines.append('')
        lines.append('/* Maximum number of channels */')
        lines.append('')
        # Special case for PFS: max channels is 12 (ports 0-9, A=10, B=11)
        if peripheral_name.upper() == 'PFS':
            lines.append(f'#define {peripheral_name.upper()}_MAX_CHANNELS    12')
        else:
            lines.append(f'#define {peripheral_name.upper()}_MAX_CHANNELS    {max_ch}')

    lines.append('')
    lines.append(f'#endif /* __ARCH_ARM_SRC_RA8_HARDWARE_{MCU}_{peripheral_name.upper()}_H */')
    lines.append('')
    return '\n'.join(lines)


def resolve_peripheral_with_registers(peripheral):
    """Resolve a peripheral element to one that contains registers by following derivedFrom links."""
    seen = set()
    p = peripheral
    while p is not None:
        name_elem = p.find('name')
        pname = name_elem.text if name_elem is not None else None
        if pname in seen:
            break
        seen.add(pname)
        registers = p.find('registers')
        if registers is not None and len(list(registers)) > 0:
            return p
        # follow derivedFrom attribute
        derived = p.get('derivedFrom')
        if not derived:
            # also check for derivedFrom children? but use attribute for now
            break
        # look up the referenced peripheral in the global map
        p = GLOBAL_PERIPHERALS.get(derived)
    return peripheral

def process_peripheral_group(base_name, variants, output_dir=None, cmsis_db=None):
    """Process a group of related peripherals (e.g., CANFD0, CANFD1, CANFD0_NS, CANFD1_NS).

    Generates a single merged header file with conditional base addresses.
    """
    # Pick a representative peripheral to extract register structure
    # Prefer secure channel 0, fallback to any available
    representative = None
    if variants['secure']:
        representative = variants['secure'][0]
    elif variants['nonsecure']:
        representative = variants['nonsecure'][0]
    else:
        return  # No peripherals in group

    p_name_elem = representative.find('name')
    if p_name_elem is None:
        return

    # Extract base addresses for secure and non-secure variants
    base_addr_secure = None
    base_addr_nonsecure = None

    if variants['secure']:
        base_elem = variants['secure'][0].find('baseAddress')
        if base_elem is not None and base_elem.text:
            base_addr_secure = to_int(base_elem.text)

    if variants['nonsecure']:
        base_elem = variants['nonsecure'][0].find('baseAddress')
        if base_elem is not None and base_elem.text:
            base_addr_nonsecure = to_int(base_elem.text)

    # Use secure as default, or nonsecure if no secure variant
    base_addr = base_addr_secure if base_addr_secure is not None else base_addr_nonsecure
    if base_addr is None:
        return

    # Extract register info from representative peripheral
    reg_list = []
    resolved_p = resolve_peripheral_with_registers(representative)
    registers = resolved_p.find('registers') if resolved_p is not None else None
    if registers is not None:
        for reg in registers:
            reg_info = extract_register_info(reg, periph_name=base_name, cmsis_db=cmsis_db)
            reg_info['offset'] = to_int(reg_info.get('offset', 0))
            reg_info['dim_inc'] = to_int(reg_info.get('dim_inc', 0))
            reg_info['base_offset'] = reg_info['offset']
            reg_list.append(reg_info)

    # Detect channels from register list
    max_ch_from_regs, has_channel_from_regs = detect_max_channels(reg_list)
    channel_stride_from_regs = compute_channel_stride(reg_list)

    # Also check if we have multiple peripheral instances (e.g., DMAC00, DMAC01, ...)
    # which indicates channels even if registers don't have '%' or 'CH'
    num_secure = len(variants['secure'])
    num_nonsecure = len(variants['nonsecure'])
    num_instances = max(num_secure, num_nonsecure)

    has_channel = has_channel_from_regs or (num_instances > 1)
    max_ch = max(max_ch_from_regs, num_instances)

    # Calculate channel stride from peripheral base addresses if multiple instances
    # Prefer channel stride derived from peripheral instance base addresses when
    # multiple instances are present (e.g., SPI0_B, SPI1_B). Fall back to
    # register-based dim_inc only when instance base spacing isn't available.
    channel_stride = channel_stride_from_regs
    if num_instances > 1:
        # Calculate stride from base addresses of the grouped instances
        base_addrs = []
        for p in (variants['secure'] if variants['secure'] else variants['nonsecure']):
            base_elem = p.find('baseAddress')
            if base_elem is not None and base_elem.text:
                base_addrs.append(to_int(base_elem.text))
        if len(base_addrs) >= 2:
            base_addrs.sort()
            base_stride = base_addrs[1] - base_addrs[0]
            # If a sensible base-address stride exists, prefer it over dim_inc
            if base_stride:
                channel_stride = base_stride

    offsets, offset_map = generate_offsets(base_name, reg_list, has_channel=has_channel, channel_stride=channel_stride)
    reg_addrs = generate_register_addresses(base_name, reg_list, has_channel=has_channel, channel_stride=channel_stride, num_instances=num_instances, offset_map=offset_map)
    bit_defs = generate_bit_defs(base_name, reg_list, has_channel=has_channel)

    content = generate_content(
        base_name,
        base_addr,
        offsets,
        reg_addrs,
        bit_defs,
        max_ch,
        has_channel=has_channel,
        channel_stride=channel_stride,
        base_addr_ns=base_addr_nonsecure,
        num_instances=num_instances
    )

    filename = f"ra_{base_name.lower()}.h"
    if output_dir:
        os.makedirs(output_dir, exist_ok=True)
        filename = os.path.join(output_dir, filename)
    with open(filename, 'w') as f:
        f.write(content)

    # Report what was merged
    merged_names = []
    for p in variants['secure']:
        pn = p.find('name')
        if pn is not None:
            merged_names.append(pn.text)
    for p in variants['nonsecure']:
        pn = p.find('name')
        if pn is not None:
            merged_names.append(pn.text)
    print(f"Generated {filename} (merged: {', '.join(merged_names)})")


def process_peripheral(peripheral, output_dir=None, print_to_stdout=False, cmsis_db=None):
    p_name_elem = peripheral.find('name')
    if p_name_elem is None:
        return
    p_name = p_name_elem.text
    base_elem = peripheral.find('baseAddress')
    base_addr = to_int(base_elem.text) if base_elem is not None and base_elem.text else 0x0

    reg_list = []
    # Resolve derivedFrom chains to find actual registers
    resolved_p = resolve_peripheral_with_registers(peripheral)
    registers = resolved_p.find('registers') if resolved_p is not None else None

    # Get base peripheral name (strip off _NS suffix and channel numbers for CMSIS lookup)
    base_p_name, _ = get_base_peripheral_name(p_name)

    if registers is not None:
        for reg in registers:
            reg_info = extract_register_info(reg, periph_name=base_p_name, cmsis_db=cmsis_db)
            # normalize numeric fields
            reg_info['offset'] = to_int(reg_info.get('offset', 0))
            reg_info['dim_inc'] = to_int(reg_info.get('dim_inc', 0))
            reg_info['base_offset'] = reg_info['offset']
            reg_list.append(reg_info)

    # detect channels and channel stride
    max_ch, has_channel = detect_max_channels(reg_list)
    channel_stride = compute_channel_stride(reg_list)

    offsets, offset_map = generate_offsets(p_name, reg_list, has_channel=has_channel, channel_stride=channel_stride)
    reg_addrs = generate_register_addresses(p_name, reg_list, has_channel=has_channel, channel_stride=channel_stride, num_instances=1, offset_map=offset_map)
    bit_defs = generate_bit_defs(p_name, reg_list, has_channel=has_channel)

    content = generate_content(p_name, base_addr, offsets, reg_addrs, bit_defs, max_ch, has_channel=has_channel, channel_stride=channel_stride, num_instances=1)

    if print_to_stdout:
        print(content)
        return

    filename = f"ra_{p_name.lower()}.h"
    if output_dir:
        os.makedirs(output_dir, exist_ok=True)
        filename = os.path.join(output_dir, filename)
    with open(filename, 'w') as f:
        f.write(content)
    print(f"Generated {filename}")

def main():
    parser = ArgumentParser(description="Generate NuttX headers from SVD")
    parser.add_argument("svd_file", help="Path to SVD file")
    parser.add_argument("peripheral", nargs='?', help="Specific peripheral name to generate for (omit for all)")
    parser.add_argument("--mcu", help="MCU name (e.g. RA8P1)", required=True)
    parser.add_argument("--output-dir", help="Output directory (default: current directory)")
    parser.add_argument("--group", action="store_true", help="Group multi-channel peripherals into single headers")
    parser.add_argument("--cmsis-header", help="Path to vendor CMSIS device header for register size/field corrections")
    args = parser.parse_args()

    # Use MCU value from arguments (allows overriding default)
    global MCU, mcu
    MCU = args.mcu
    mcu = MCU.lower()

    # Parse CMSIS header if provided
    cmsis_db = None
    if args.cmsis_header:
        print(f"Parsing CMSIS header: {args.cmsis_header}")
        cmsis_db = parse_cmsis_typedef_structs(args.cmsis_header)
        print(f"Found {len(cmsis_db)} peripherals in CMSIS header")

    root = parse_svd(args.svd_file)
    peripherals = root.findall('.//peripheral')
    # build global peripheral map
    for p in peripherals:
        p_name_elem = p.find('name')
        if p_name_elem is not None and p_name_elem.text:
            GLOBAL_PERIPHERALS[p_name_elem.text] = p

    if args.peripheral:
        peripheral = None
        for p in peripherals:
            p_name_elem = p.find('name')
            if p_name_elem is not None and p_name_elem.text == args.peripheral:
                peripheral = p
                break
        if peripheral is None:
            sys.exit(f"Peripheral '{args.peripheral}' not found")
        process_peripheral(peripheral, args.output_dir, cmsis_db=cmsis_db)
    else:
        output_dir = args.output_dir or '.'
        if args.group:
            # Group peripherals by base name
            groups = {}
            for p in peripherals:
                p_name_elem = p.find('name')
                if p_name_elem is None:
                    continue
                p_name = p_name_elem.text
                base_name, is_ns = get_base_peripheral_name(p_name)
                if base_name not in groups:
                    groups[base_name] = {'secure': [], 'nonsecure': []}
                if is_ns:
                    groups[base_name]['nonsecure'].append(p)
                else:
                    groups[base_name]['secure'].append(p)

            # Process each group
            for base_name, variants in groups.items():
                process_peripheral_group(base_name, variants, output_dir, cmsis_db=cmsis_db)
        else:
            for p in peripherals:
                process_peripheral(p, output_dir, cmsis_db=cmsis_db)

if __name__ == "__main__":
    main()