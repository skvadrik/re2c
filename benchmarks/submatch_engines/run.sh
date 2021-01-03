#!/bin/bash

set -e

if [ $# -lt 1 ]; then
    echo "usage: $0 <repetitions> [benchmark ...]"
    exit 1
fi

# number of times to run one benchmark
repcount="$1"

# filter to run selected benchmarks
shift 1
filter="$@"

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
    data="data/$(echo $prog | stem_data)/big"
    log="logs/$engine/$prog"
    mkdir -p "logs/$engine"
    echo > "$log"
    for f in $(seq $repcount); do
        "bin/$engine/$prog" -t < "$data" >/dev/null 2>>"$log"
    done
}

# build
make -j$(nproc)
make data -j$(nproc)
make clean-logs

# select benchmarks to run
progs="$(find bin -type f)"
if [ -n "$filter" ]; then
    echo "$progs" > tmp.1
    echo "$filter" | tr ' ' '\n' > tmp.2
    progs="$(fgrep -f tmp.2 tmp.1)"
    rm tmp.1 tmp.2
fi

# run
for prog in $progs; do
    engine="$(echo $prog | cut -d'/' -f2)"
    binary="$(echo $prog | cut -d'/' -f3)"
    run "$engine" "$binary"
done

# calculate average time
timings=logs/timings
echo > "$timings"
for engine in {kleenex,ragel,re2c} ; do
    for log in logs/"$engine"/* ; do
        # average speed
        avg=$(awk '!/^$/ { total += $3; lines += 1 } END { print total/lines }' "$log")

        # binary size
        cp bin/"$engine"/"$(basename $log)" tmp
        strip tmp
        binsize=$(stat -c%s tmp)
        rm tmp

        printf "%-40s%-10s%-10.2lf%-10d\n" "$(basename $log)" "$engine" "$avg" "$binsize" >> "$timings"
    done
done

# group by benchmarks, then sort by time
results=logs/results
echo > "$results"
for bench in $(cat $timings | stem_bench | sort | uniq); do
    egrep -o "^$bench[.-].*" "$timings" | sort -k3n,3 >> "$results"
    echo >> "$results"
done
rm "$timings"

cat logs/results
