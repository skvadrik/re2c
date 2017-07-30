
for f in ../.dat/*.dat; do

    d=../`basename ${f%.dat}`
    mkdir -p $d

    i=0
    while read l; do

        [ -z "$l" ] && continue
        set $l
        [ "$1" == SAME ] && continue

        i=$((i + 1))
        x=`printf '%02d' $i`.i--flex-syntax.re
        regexp=`printf "%s" "$1" | sed \
            -e 's/\[^/[^\\\\x00/g' \
            -e 's/\./[^\\\\x00]/g' \
            -e 's/()/("")/g'`

        cat template | sed "s/<<<<REGEXP>>>>/$regexp/" > $d/$x

    done < $f
done

