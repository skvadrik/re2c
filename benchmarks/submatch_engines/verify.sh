#!/bin/bash

set -e

# optional argument --small to use small data file
[ $# -eq 1 -a "$1" == "--small" ] && datafile=small || datafile=big

stem() {
    egrep -o '^[0-9a-z_]+'
}

run() {
    engine="$1"
    prog="$2"
    data="data/$(echo $prog | stem)/$datafile"
    log="logs/$engine/$prog"
    mkdir -p "logs/$engine"
    "bin/$engine/$prog" < "$data" >"$log"
}

# build
make -j$(nproc)
make data -j$(nproc)
make clean-logs

# run, logging the output
for prog in $(find bin -type f); do
    engine="$(echo $prog | cut -d'/' -f2)"
    binary="$(echo $prog | cut -d'/' -f3)"
    run "$engine" "$binary"
done

# group by benchmark and compare logs
failed=0
for bench in $(find logs -type f -exec basename {} \; | stem | sort | uniq); do
    logs=( $(find logs -name $bench[.-]*) )
    for i in $(seq 2 ${#logs[@]}) ; do
        cmp ${logs[i-2]} ${logs[i-1]} || failed=1
    done
done
[ $failed -eq 0 ] && echo "OK" || echo "FAIL"
