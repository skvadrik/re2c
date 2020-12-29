# helper script to run the benchmark from toplevel build directory
set -e

cd benchmarks/submatch_dfa_aot
./verify.sh --small
./run.sh 5
cd ../..
