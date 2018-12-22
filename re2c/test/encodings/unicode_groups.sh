#!/bin/bash

if [[ $# -ne 2 ]]; then
    echo "usage: ./unicode_groups.sh SRCDIR BLDDIR"
    exit 1
fi

srcdir="$1"
blddir="$2"

for fre in unicode_{blocks,group_*}.{8,x,u}--encoding-policy\({ignore,substitute,fail}\).re
do
    echo $fre
    fc=${fre/.re/.c}
    fe=${fre/.re/}
    policy=`printf "%s" "$fre" | sed -E -e 's/[^.]+.([a-z0-9]+)--encoding-policy\((ignore|substitute|fail)\).*/-\1 --encoding-policy \2/'`

    # compile re2c source
    $blddir/re2c $policy $fre -o$fc --no-version --no-generation-date

    read line < $fc
    if [[ $line == "re2c: error:"* ]]
    then
        echo "*** re2c error, skipping ***"
        continue
    fi

    # compile C source
    g++ -W -Wall -Wextra \
        -I $srcdir \
        -I $blddir \
        -I $srcdir/src/re/encoding/utf8 \
        -I $srcdir/src/re/encoding/utf16 \
        $srcdir/src/re/encoding/utf8/utf8.cc \
        $srcdir/src/re/encoding/utf16/utf16.cc \
        $fc \
        -o $fe

    # execute (runs silently if OK, otherwize report an error)
    ./$fe

    rm -f $fe
done

echo "note: run-time failures for surrogates with '--encoding-policy substitute' are OK"
echo "note: compile-time failures for surrogates with '--encoding-policy fail' are OK"
