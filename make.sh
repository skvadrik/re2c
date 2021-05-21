#!/bin/sh

for lang in {c,go}; do
    build/split_man.sh src/manual/manual.rst.in src/manual/manual_$lang.rst $lang
done

sphinx-build -b html src obj

[ $# != 0 ] || #pass an argument to prevent the server from launching
    runhaskell launch.hs
