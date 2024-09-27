#!/bin/sh

set -e

for lang in {c,go,rust}; do
    python3 build/split_man.py src/manual/manual.rst.in src/manual/manual_$lang.rst $lang
done

sphinx-build -b html src obj || { echo "failed!"; exit 1; }

[ $# != 0 ] || #pass an argument to prevent the server from launching
    python3 -m http.server -d obj
