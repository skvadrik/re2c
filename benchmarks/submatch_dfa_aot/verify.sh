#!/bin/bash

set -e

# optional argument --small to use small data file
[ $# -eq 1 -a "$1" == "--small" ] && datafile=small || datafile=big

# one benchmark may have different flavours
# they differ only in the suffix that starts with dash
stem_bench() {
    egrep -o '^[0-9a-z_]+'
}

# a few different benchmarks may share the same data
# everything up to the first underscore is the data stem
stem_data() {
    egrep -o '^[0-9a-z]+'
}

run() {
    engine="$1"
    prog="$2"
    data="data/$(echo $prog | stem_data)/$datafile"
    log="logs/$engine/$prog"
    mkdir -p "logs/$engine"
    "bin/$engine/$prog" < "$data" >"$log"
}

# build
make -j$(nproc)
make data -j$(nproc)
mkdir -p logs
make clean-logs

# select benchmarks
progs="$(find bin -type f | fgrep -v -f known_failures)"

# run, logging the output
for prog in $progs; do
    engine="$(echo $prog | cut -d'/' -f2)"
    binary="$(echo $prog | cut -d'/' -f3)"
    run "$engine" "$binary"
done

# group by benchmark and compare logs
failed=0
for bench in $(find logs -type f -exec basename {} \; | stem_bench | sort | uniq); do
    logs=( $(find logs -name $bench[.-]*) )
    for i in $(seq 2 ${#logs[@]}) ; do
        cmp ${logs[i-2]} ${logs[i-1]} || failed=1
    done
done
[ $failed -eq 0 ] && echo "OK" || echo "FAIL"
