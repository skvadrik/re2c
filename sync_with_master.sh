#!/bin/sh

set -e

# Clean up some folders to remove stale files.
rm -rf src/benchmarks/submatch_*/*

# Sync with master (pull manpage files, benchmark results, etc.).
# Most of the synced files are treated as source code and committed to Git,
# except for a few helper scripts.
remote=$(git config branch.master.remote) \
    && git fetch $remote \
    && { git archive --remote=. remotes/$remote/master doc/manual \
        | tar -C src/ --strip-components=1 -xpf -; } \
    && { git archive --remote=. remotes/$remote/master examples/**/*.{re,c,h,go,txt} \
        | tar -C src/ -xpf -; } \
    && { git archive --remote=. remotes/$remote/master \
            benchmarks/submatch_{dfa_aot,dfa_jit,nfa}/results \
        | tar -C src/ -xpf -; } \
    && { git archive --remote=. remotes/$remote/master benchmarks/json2pgfplot.py \
        | tar -C build/ --strip-components=1 -xpf -; } \
    && { git archive --remote=. remotes/$remote/master build/split_man.sh \
        | tar -xpf -; } \
    && { git archive --remote=. remotes/$remote/master CHANGELOG \
        | tar -C src/releases/changelog/ -xpf -; } \
    && mv src/releases/changelog/CHANGELOG src/releases/changelog/changelog.rst

for lang in {c,go}; do
    build/split_man.sh src/manual/manual.rst.in src/manual/manual_$lang.rst $lang
done

# Find benchmark results (files of the form results_YYYYMMDD.json template) and
# pick the latest result (the one with numerically greatest date component).
pick_latest_result() {
    latest=$(ls "results/results_"*".json" \
        | sed -E 's/.*results_([0-9]+)\.json/\1/' \
        | sort -n \
        | head -n 1)
    cp "results/results_$latest.json" "results.json"
    cp "results/env_$latest.rst" "env.rst"
    echo "**The results may be out of date!**" >> "env.rst"
    rm -rf "results"
}

# For a given bennchmark, render JSON results as a PGF plot (TeX), then compile
# it to PDF and further convert to SVG. The PDF may contain multiple pages
# (lexer generator benchmarks have file size charts in addition to time charts).
gen_bar_charts_for_benchmark() {
    benchmark="$1"
    pagecount="$2"
    j2pp_args="$3"
    ( cd "src/benchmarks/$benchmark" \
        && echo "Generating SVG for $benchmark benchmark..." \
        && pick_latest_result \
        && ../../../build/json2pgfplot.py $j2pp_args --font comicneue \
            results.json results.tex \
        && pdflatex results.tex < /dev/null > results.log \
        && for page in $(seq 1 $pagecount); do \
            pdf2svg results.pdf results_$page.svg $page; done \
        && rm results.{aux,log,pdf,tex} \
    )
}

gen_bar_charts_for_benchmark submatch_dfa_aot 2 ""
gen_bar_charts_for_benchmark submatch_dfa_jit 1 "--relative-to tdfa1-P"
gen_bar_charts_for_benchmark submatch_nfa     1 "--relative-to LG"
