#!/usr/bin/env bash

set -e

bench() {
    cd "$1/$2/"

#    ./__verify.sh

    ./__bench.sh       1> log._ 2>&1
    ./__bench_unopt.sh 1> log.unopt 2>&1
    ./__bench_b.sh     1> log.b 2>&1

    cd ../..
}

bench http rfc7230
bench http simple
bench uri  rfc3986
bench uri  simple

