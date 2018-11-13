#!/bin/bash

test $# -ne 1 && { echo "usage: ./__run.sh <path-to-re2c>"; exit 1; }
re2c="$1"

while true; do

    f=""
    while true; do
        read l || { echo "all done!"; exit 0; }

        # empty line: end of group
        test -z "$l" && break

        # test name followed by regexp
        IFS=$'\t'; set $l; f="$1.i--flex-syntax"; r="$2"

        # generate .re files from __patterns file
        printf "%%{\n$r {}\n * {}\n%%}" > $f.re

        # generate .c files from .re files
        $re2c $f.re -Fi -W --no-generation-date --no-version -o$f.c 2>warnings \
            && cat warnings >> $f.c && rm warnings \
            || echo "failed on $f.re"
    done

    # check that all .c files in the same group are equal
    set `echo $f | grep -oE '^[0-9]+'`*.c
    if [ $# -gt 1 ] ; then
        x=$1; shift 1
        for y in $@; do
            diff $x $y || { echo "failed on $x, $y"; exit 1; }
        done
    fi

done < __patterns
