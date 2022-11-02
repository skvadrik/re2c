#!/usr/bin/python

# This file generates unicode names for character classes for re2c.
# Run it on the command line with
#   python3 generate_unicode_files.py
# It uses the built-in unicode data files in Python, which may not be fully up-to-date.
# Be sure to update your version of Python to the latest.
#

import unicodedata
from datetime import datetime
import sys

MAX_CODEPOINT = 0x10FFFF


def main():

    catmap = dict()
    for codepoint in range(MAX_CODEPOINT):
        try:
            ch = chr(codepoint)
        except ValueError as ve:
            continue
        cat = unicodedata.category(ch)
        if cat not in catmap:
            catmap[cat] = list()
        catmap[cat].append(codepoint)

    add_single_char_entries(catmap)

    write_file(catmap, "unicode_categories.re",
               "// Unicode character classes for re2c\n")


def add_single_char_entries(map):

    # create another map with single-char parent entries, with all child values appended
    parent_entries = dict()
    for cat, values in map.items():
        single_char = cat[0:1]
        if single_char not in parent_entries:
            parent_entries[single_char] = list()
        parent_entries[single_char].extend(values)

    #print(parent_entries)

    # sort the values and add to the main map
    for single_char, values in parent_entries.items():
        values.sort()
        map[single_char] = values


def write_file(map, filename, title):
    file = open(filename, "w")
    file.write(title)
    file.write(
        f"// Generated on {datetime.now()} by Python version {sys.version} Unicode version {unicodedata.unidata_version}\n")
    file.write("/*!re2c\n")

    for cat, values in sorted(map.items()):
        file.write(f"{cat} = [")
        # consolidate values into ranges
        prev_codepoint = -99
        is_range = False
        for codepoint in values:
            if codepoint == prev_codepoint + 1:
                is_range = True
                prev_codepoint = codepoint
                continue
            if is_range:
                file.write("-" + as_hex(prev_codepoint))
                is_range = False
            file.write(as_hex(codepoint))
            prev_codepoint = codepoint
        # catch the last one
        if is_range:
            file.write("-" + as_hex(prev_codepoint))

        file.write("];\n")
    file.write("*/")
    file.close()


def as_hex(codepoint):
    if codepoint <= 0xFF:
        return format(f"\\x{codepoint:02x}")
    if codepoint <= 0xFFFF:
        return format(f"\\u{codepoint:04x}")
    return format(f"\\U{codepoint:08x}")


if __name__ == "__main__":
    main()
