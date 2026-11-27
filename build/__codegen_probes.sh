#!/bin/sh

# Code generation probes (see build/codegen_probes.py), run on the re2c binary
# built by build/__build.sh.

re2c=__build/re2c

# The registry and templates probes only read the sources; every other probe,
# as well as the self-test, runs re2c. The help needs nothing.
need_re2c=yes
self_test=no
help=no
prev=
for arg in "$@"; do
    case "$prev,$arg" in
        --only,registry | --only,templates \
            | *,--only=registry | *,--only=templates) need_re2c=no ;;
        --only,* | *,--only=*) need_re2c=yes ;;
        *,--self-test) self_test=yes ;;
        *,-h | *,--help) help=yes ;;
    esac
    prev=$arg
done
[ "$self_test" = yes ] && need_re2c=yes
[ "$help" = yes ] && need_re2c=no

if [ "$need_re2c" = yes ] && [ ! -x "$re2c" ]; then
    echo "*** $re2c not found, run build/__build.sh first ***"
    exit 2
fi

python3 build/codegen_probes.py --re2c "$re2c" "$@"
