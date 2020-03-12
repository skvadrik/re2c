#!/bin/bash

log="log"

grep ':  ' "$log" | grep -E ' [0-9]+\.[0-9]{2} | - ' -o > "${log}1"

rm "${log}2"
while read l; do
    for i in $(seq 8); do
        read l1
        l="$l;$l1"
    done
    echo $l | sed 's/-/nan/' >> "${log}2"
done < "${log}1"

cp "${log}2" data

rm "${log}1" "${log}2"
