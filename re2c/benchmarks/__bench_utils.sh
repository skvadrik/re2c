
re2c="../../re2c"

compile() {
    name="${1}_${2}"
    opts="$3"

    [ -e ${re2c} ] || { echo "*** no re2c ***"; exit 1; }

    ${re2c} ${opts}                -W ${name}.re        -o ${name}_lookahead.c    && ls -l --block-size=K ${name}_lookahead.c
    ${re2c} ${opts} --no-lookahead -W ${name}.re        -o ${name}_no_lookahead.c && ls -l --block-size=K ${name}_no_lookahead.c
    ${re2c} ${opts}                -W ${name}_notags.re -o ${name}_notags.c       && ls -l --block-size=K ${name}_notags.c
}

run() {
    name1="$1"
    name2="$2"
    name="${name1}_${name2}"
    input="../gen/${name1}.dat"

    [ -e ${input} ] || { echo "*** no input file ***"; exit 1; }

    strip ${name}
    cmd="./${name} ${input}"
    for i in `seq 1`; do $cmd >/dev/null 2>&1; done # warmup

    npass=4
    total=0
    for i in `seq $npass`; do
        t="`TIMEFORMAT='%E'; time ( $cmd 2>/dev/null ) 2>&1 1>/dev/null`"
        echo "t:" $t
        total=`echo $total + $t | bc -l`
    done
    average=`echo "$total / $npass" | bc -l`
    echo "time: $average"

    ls -l --block-size=K ${name}
}

#cflags="-Wall -O2"
cflags="-O2"

run_all() {
    name1="$1"
    name2="$2"
    name="${name1}_${name2}"

    echo "---------------- WARMUP (GCC -O2 lookahead) ----------------"
    gcc     $cflags ${name}_lookahead.c    -o${name} && run ${name1} ${name2}
    echo "---------------- END WARMUP ----------------"

    echo "---------------- GCC -O2 lookahead ----------------"
    gcc     $cflags ${name}_lookahead.c    -o${name} && run ${name1} ${name2}
    echo "---------------- GCC -O2 no-lookahead ----------------"
    gcc     $cflags ${name}_no_lookahead.c -o${name} && run ${name1} ${name2}
    echo "---------------- GCC -O2 notags ----------------"
    gcc     $cflags ${name}_notags.c       -o${name} && run ${name1} ${name2}

    echo "---------------- CLANG -O2 lookahead ----------------"
    clang   $cflags ${name}_lookahead.c    -o${name} && run ${name1} ${name2}
    echo "---------------- CLANG -O2 no-lookahead ----------------"
    clang   $cflags ${name}_no_lookahead.c -o${name} && run ${name1} ${name2}
    echo "---------------- CLANG -O2 notags ----------------"
    clang   $cflags ${name}_notags.c       -o${name} && run ${name1} ${name2}

    echo "---------------- TCC -O2 lookahead ----------------"
    tcc     $cflags ${name}_lookahead.c    -o${name} && run ${name1} ${name2}
    echo "---------------- TCC -O2 no-lookahead ----------------"
    tcc     $cflags ${name}_no_lookahead.c -o${name} && run ${name1} ${name2}
    echo "---------------- TCC -O2 notags ----------------"
    tcc     $cflags ${name}_notags.c       -o${name} && run ${name1} ${name2}

    echo "---------------- PCC -O2 lookahead ----------------"
    pcc     $cflags ${name}_lookahead.c    -o${name} && run ${name1} ${name2}
    echo "---------------- PCC -O2 no-lookahead ----------------"
    pcc     $cflags ${name}_no_lookahead.c -o${name} && run ${name1} ${name2}
    echo "---------------- PCC -O2 notags ----------------"
    pcc     $cflags ${name}_notags.c       -o${name} && run ${name1} ${name2}

#    echo "---------------- NWCC -O2 lookahead ----------------"
#    nwcc    $cflags ${name}_lookahead.c    -o${name} && run ${name1} ${name2}
#    echo "---------------- NWCC -O2 no-lookahead ----------------"
#    nwcc    $cflags ${name}_no_lookahead.c -o${name} && run ${name1} ${name2}
#    echo "---------------- NWCC -O2 notags ----------------"
#    nwcc    $cflags ${name}_notags.c       -o${name} && run ${name1} ${name2}

    rm ${name}_lookahead.c
    rm ${name}_no_lookahead.c
    rm ${name}_notags.c
    rm ${name}
}

verify() {
    name1="$1"
    name2="$2"
    name=${name1}_${name2}
    input="../gen/${name1}.dat.short"
    output="${name1}.dat.short"

    [ -e ${input} ] || { echo "*** no input file ***"; exit 1; }
    [ -e ${re2c} ] || { echo "*** no re2c ***"; exit 1; }

    ${re2c}                -W ${name}.re        -o ${name}_lookahead.c
    ${re2c} --no-lookahead -W ${name}.re        -o ${name}_no_lookahead.c
    ${re2c}                -W ${name}_notags.re -o ${name}_notags.c

    g++ -Wall -O2 -DVERIFY ${name}_lookahead.c    -o${name} && ./${name} ${input} > ${output} && diff -q ${input} ${output} || echo "lookahead failed"
    g++ -Wall -O2 -DVERIFY ${name}_no_lookahead.c -o${name} && ./${name} ${input} > ${output} && diff -q ${input} ${output} || echo "non-lookahead failed"
    g++ -Wall -O2 -DVERIFY ${name}_notags.c       -o${name} && ./${name} ${input} > ${output} && diff -q ${input} ${output} || echo "notags failed"

    rm ${name}_lookahead.c
    rm ${name}_no_lookahead.c
    rm ${name}_notags.c
    rm ${name}
    rm ${output}
}
