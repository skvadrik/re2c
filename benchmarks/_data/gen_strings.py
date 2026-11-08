#!/usr/bin/env python3

# Generate the `small` samples used by the string lexer benchmark for `--vectorize-loops`
# (benchmarks/c/src/re2c/vec_00__strings.re). The output is deterministic: synthetic inputs use a
# fixed-seed PRNG, and the C/C++ source sample is a snapshot of files from a fixed re2c commit.
#
# Usage (from the benchmarks/_data directory):
#
#     ./gen_strings.py
#
# The `big` files are produced from `small` by gen.py, as for all other benchmarks.

import os
import random
import subprocess

# Approximate size of each synthetic sample.
SIZE = 64 * 1024

# Alphabet of string contents: printable ASCII without double quote and backslash, plus a few
# UTF-8 encoded letters (bytes >= 0x80 must be handled by the vectorized character class check).
ASCII = [chr(c) for c in range(0x20, 0x7f) if chr(c) not in '"\\']
UTF8 = ['é', 'ß', 'ж', '€', '中']
ESCAPES = ['\\"', '\\\\', '\\n', '\\t', '\\/', '\\u00e9']

WORDS = ["id", "name", "email", "url", "description", "tags", "created_at", "count", "enabled",
    "owner", "title", "status", "path", "size", "version"]


def text(rng, n, utf8=0.0, escapes=0.0):
    out = []
    while len(out) < n:
        r = rng.random()
        if r < escapes:
            out.append(ESCAPES[int(rng.random() * len(ESCAPES))])
        elif r < escapes + utf8:
            out.append(UTF8[int(rng.random() * len(UTF8))])
        else:
            out.append(ASCII[int(rng.random() * len(ASCII))])
    return ''.join(out)


def length(rng, lo, hi):
    return lo + int(rng.random() * (hi - lo + 1))


# A list of string literals separated by commas, several per line.
def strings(rng, lo, hi, utf8=0.0, escapes=0.0):
    out = []
    size = 0
    while size < SIZE:
        s = '"' + text(rng, length(rng, lo, hi), utf8, escapes) + '"'
        s += ',\n' if rng.random() < 0.2 else ', '
        out.append(s)
        size += len(s.encode('utf-8'))
    return ''.join(out).rstrip(' \n') + '\n'


# Pretty-printed JSON-like records with keys, short and long string values, numbers and literals.
def json(rng):
    out = ['[\n']
    size = 0
    while size < SIZE:
        fields = []
        for key in WORDS:
            r = rng.random()
            if key in ("id", "count", "size"):
                val = str(int(rng.random() * 1000000))
            elif key == "enabled":
                val = "true" if r < 0.5 else "false"
            elif key == "url":
                val = '"https://example.org/' + text(rng, length(rng, 10, 60)).replace(' ', '/') + '"'
            elif key == "description":
                val = '"' + text(rng, length(rng, 40, 400), 0.02, 0.01) + '"'
            elif key == "tags":
                val = '[' + ', '.join('"' + text(rng, length(rng, 3, 12)) + '"'
                    for _ in range(length(rng, 0, 5))) + ']'
            elif r < 0.1:
                val = "null"
            else:
                val = '"' + text(rng, length(rng, 3, 30), 0.02) + '"'
            fields.append('    "' + key + '": ' + val)
        rec = '  {\n' + ',\n'.join(fields) + '\n  },\n'
        out.append(rec)
        size += len(rec.encode('utf-8'))
    out.append('  {}\n]\n')
    return ''.join(out)


# Snapshot of real C++ source code from re2c release 4.6.
CSOURCE_COMMIT = "e485c5d572ab8a9f895b2a3c98e5239bf59254c8"
CSOURCE_FILES = [
    "src/parse/ast.cc",
    "lib/regexec_dfa_multipass.cc",
    "src/codegen/pass1_analyze.cc",
]


def csource():
    out = []
    for f in CSOURCE_FILES:
        p = subprocess.run(["git", "show", CSOURCE_COMMIT + ":" + f],
            stdout=subprocess.PIPE, check=True)
        out.append(p.stdout.decode('utf-8'))
    return ''.join(out)


def write(name, contents):
    os.makedirs(name, exist_ok=True)
    with open(os.path.join(name, "small"), "wb") as f:
        f.write(contents.encode('utf-8'))


def main():
    write("strshort", strings(random.Random(1), 0, 24))
    write("strmedium", strings(random.Random(2), 32, 128, 0.01))
    write("strlong", strings(random.Random(3), 256, 4096, 0.01))
    write("strescape", strings(random.Random(4), 32, 256, 0.02, 0.15))
    write("json", json(random.Random(5)))
    write("csource", csource())


if __name__ == "__main__":
    main()
