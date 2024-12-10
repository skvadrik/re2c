#!/usr/bin/env python3

"""
Encodes the contents of a syntax file as C++ source code.
"""

import os
import sys

if len(sys.argv) != 3:
    print('usage:', sys.argv[0], '<input> <output>')
    exit(1)

input = sys.argv[1]
output = sys.argv[2]

with open(output, 'w') as output_file:
    name = os.path.splitext(os.path.basename(output))[0].upper()
    output_file.write("static constexpr const char* " + name + " =\n")

    # write input file line by line as a string, escaping characters as needed
    with open(input, 'r') as input_file:
        for l in input_file:
            l_out = l[:-1].translate(str.maketrans({
                '\\': '\\\\',
                '"':  '\\"'
            }))
            output_file.write('    "' + l_out + '\\n"\n')

    output_file.write("    ;\n")
