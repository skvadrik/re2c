#!/usr/bin/env python3

"""
Generates language-specific manpages by replacing placeholder tokens in the
input manpage.
"""

import sys

if len(sys.argv) != 4:
    print('usage:', sys.argv[0], '<input> <output> <lang>')
    exit(1)

input = sys.argv[1]
output = sys.argv[2]
lang = sys.argv[3].lower().encode('utf-8')

if lang == b'c':
    src_ext = b'c'
    hdr_ext = b'h'
    lang_name = b'C'
    disclaimer = b'Note: examples are in C++ (but can be easily adapted to C).'
elif lang == b'go':
    src_ext = b'go'
    hdr_ext = b'go'
    lang_name = b'Go'
    disclaimer = b'Note: This manual is for Go, but it refers to re2c as the general program.'
elif lang == b'rust':
    src_ext = b'rs'
    hdr_ext = b'rs'
    lang_name = b'Rust'
    disclaimer = b'Note: This manual is for Rust, but it refers to re2c as the general program.'
else:
    print('***', sys.argv[0], ': unknown lang:', lang)
    exit(1)

with open(input, 'rb') as input_file:
    file_bytes = input_file.read()

file_bytes = file_bytes.replace(b'RE2C_LANG_NAME', lang_name)
file_bytes = file_bytes.replace(b'RE2C_LANG', lang)
file_bytes = file_bytes.replace(b'RE2C_SOURCE_EXT', src_ext)
file_bytes = file_bytes.replace(b'RE2C_HEADER_EXT', hdr_ext)
file_bytes = file_bytes.replace(b'RE2C_DISCLAIMER', disclaimer)

with open(output, 'wb') as output_file:
    output_file.write(file_bytes)
