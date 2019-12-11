#!/bin/bash

test $# -ne 1 && { echo "usage: ./__run.sh <path-to-re2c>"; exit 1; }
re2c="$1"

# run <regex> <string> <match> [re2c-flags]
run() {
    f="test_"`date +%y%m%d%H%M%S`
    fail=0

    cat template | sed "s/<<<<REGEXP>>>>/$1/" > $f.re \
        && echo "$3" > $f.expected \
        && $re2c -iF --posix-captures $4 $f.re -o$f.cpp \
        && g++ -W $f.cpp -o$f \
        && ./$f "$2" > $f.actual \
        && diff $f.expected $f.actual \
        || fail=1

    rm $f*
    [ $fail == 1 ] && { echo "$1 failed"; exit 1; }
}

for f in ../.dat/*.dat; do
    i=0
    n=`grep -cv "^$" $f` # nonempty lines

    printf "%s\n" `basename $f`
    while read l; do

        [ -z "$l" ] && continue
        set $l
        [ "$1" == SAME ] || regexp=`printf "%s" "$1" | sed \
            -e 's/\[^/[^\\\\x00/g' \
            -e 's/\./[^\\\\x00]/g' \
            -e 's/()/("")/g'`
        string="${2#NULL}"
        match="$3"
        i=$((i + 1))

        printf "\r%3d / %-3d" $i $n
        run "$regexp" "$string" "$match"
        run "$regexp" "$string" "$match" "--no-lookahead"
        run "$regexp" "$string" "$match" "--stadfa"

    done < $f
    printf "\n"
done

