#!/bin/sh

set -e

for lang in {c,d,go,hs,java,js,ocaml,py,rust,v,zig}; do
    python3 build/split_man.py src/manual/manual.rst.in src/manual/manual_re2$lang.rst
    # rename page to keep old links working
    mv src/manual/manual_re2$lang.rst src/manual/manual_$lang.rst
done

sphinx-build -b html src obj || { echo "failed!"; exit 1; }

[ $# != 0 ] || #pass an argument to prevent the server from launching
    python3 -m http.server -d obj
