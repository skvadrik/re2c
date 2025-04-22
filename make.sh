#!/usr/bin/env bash

source ./utils.sh

for lang in {c,d,go,hs,java,js,ocaml,py,rust,swift,v,zig}; do
    python3 build/split_man.py src/manual/manual.rst.in src/manual/manual_re2$lang.rst
    # rename page to keep old links working
    mv src/manual/manual_re2$lang.rst src/manual/manual_$lang.rst
done

sphinx-build -b html src obj

cp --recursive playground obj

if [[ $# -eq 0 ]]; then
    #pass an argument to prevent the server from launching
    python3 -m http.server --directory obj
fi
