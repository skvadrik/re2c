#!/bin/bash

log="log"

grep ':  ' "$log" | grep -E ' [0-9]+\.[0-9]{2} | - ' -o > "${log}1"

while read l; do
    for i in $(seq 7); do
        read l1
        l="$l;$l1"
    done
    echo $l | sed 's/-/nan/' >> "${log}2"
done < "${log}1"

heading="test;Alg;LG;RE2;OS;OS_GTOP;Kuklewicz;OS_naive;OS_lazy;Cox"

column -t "${log}2" > "${log}3"

realworld=(
    "HTTP  6204,198"
    "HTTP-small  574,40"
    "URI  3149,102"
    "URI-small  234,18"
    "IPv6  2343,61"
    "IPv4  235,5"
    "IPv4-small  57,4"
    "IPv4-tiny  37,4"
    "date  154,7"
    "date-small  65,6"
    "date-tiny  47,6"
)

artificial=(
    '\texttt{(a\{2\}|a\{3\}|a\{5\})*}'
    '\texttt{(a\{7\}|a\{11\}|a\{13\})*}'
    '\texttt{(a\{17\}|a\{19\}|a\{23\})*}'
    '\texttt{(a\{29\}|a\{31\}|a\{37\})*}'
    '\texttt{(((a)\{2\})|((a)\{3\})|((a)\{5\}))*}'
    '\texttt{(((a)\{7\})|((a)\{11\})|((a)\{13\}))*}'
    '\texttt{(((a)\{17\})|((a)\{19\})|((a)\{23\}))*}'
    '\texttt{(((a)\{29\})|((a)\{31\})|((a)\{37\}))*}'
    '\texttt{((((((((((a*)*)*)*)*)*)*)*)*)*)*}'
    '\texttt{(a*)(a*)(a*)(a*)(a*)(a*)(a*)(a*)}'
    '\texttt{(((a*)(a*)(a*))*((a*)(a*)(a*))*)*}'
    '\texttt{(((((a*)*)*((a*)*)*((a*)*)*)*)*)*}'
    '\texttt{(((((a*)*(a*))*(a*))*(a*))*(a*))*}'
    '\texttt{((a*)((a*)((a*)((a*)(a*)*)*)*)*)*}'
    '\texttt{(a*)|(a*)|(a*)|(a*)|(a*)|(a*)|(a*)}'
    '\texttt{((a*)|(a*)|(a*))((a*)|(a*)|(a*))}'
    '\texttt{((a*)|(a*))((a*)|(a*))((a*)|(a*))}'
    '\texttt{((a*)|(a*)|(a*))*|((a*)|(a*)|(a*))*}'
    '\texttt{(((((a*)*)*|((a*)*)*|((a*)*)*)*)*)*}'
    '\texttt{((a*)|((a*)(a*))|((a*)(a*)(a*)))*}'
    '\texttt{(((a*)(a*)(a*))|((a*)(a*))|(a*))*}'
)

pathological=(
    '\texttt{((a?)\{0,125\})*}'
    '\texttt{((a?)\{0,250\})*}'
    '\texttt{((a?)\{0,500\})*}'
    '\texttt{((a?)\{0,1000\})*}'
    '\texttt{((a?)\{0,2000\})*}'
)

process() {
    local -n tests=$3
    result="$4"
    echo $heading > "$result"
    for i in $(seq $1 $2); do
        echo -n "$i;${tests[$((i-$1))]};" >> "$result"
        sed "${i}q;d" "${log}3" >> "$result"
    done
}

process 1  11 realworld    data_realworld
process 12 32 artificial   data_artificial
process 33 37 pathological data_pathological

rm "${log}1" "${log}2" "${log}3"
