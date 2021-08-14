#!/usr/bin/env sh

set -e

[ $# -ne 1 ] && { echo "usage: $0 <re2c-root>"; exit 1; }

rootdir="$1"

rm -rf benchmarks && mkdir -p benchmarks/{dfa_aot,dfa_jit}

# DFA AOT benchmark
cd benchmarks/dfa_aot
resultsdir="${rootdir}"/benchmarks/submatch_dfa_aot/results
results=$(find "${resultsdir}" -name 'results_*.json' | tail -n 1)
"${resultsdir}"/split_results.sh "${results}"
cd ../..
for jsonfile in benchmarks/dfa_aot/*; do
    texfile="$(echo ${jsonfile} | sed -E 's/.*results_[0-9]*_(.*)\.json/benchmark_dfa_aot_\1.tex/')"
    "${resultsdir}/../../json2pgfplot.py" --variant dfa_aot "${jsonfile}" "${texfile}"
done

# DFA JIT benchmark
cd benchmarks/dfa_jit
resultsdir="${rootdir}"/benchmarks/submatch_dfa_jit/results
results=$(find "${resultsdir}" -name 'results_*.json' | tail -n 1)
cp "${results}" .
cd ../..
texfile="benchmark_dfa_jit.tex"
"${resultsdir}/../../json2pgfplot.py" --variant dfa_jit "${results}" "${texfile}"

# Java benchmark
for flavour in sparse dense; do
    resultsdir="${rootdir}"/benchmarks/submatch_java/results
    cp "$(find ${resultsdir} -name '*_'${flavour}'.tex' | tail -n 1)" "benchmark_java_${flavour}.tex"
done
