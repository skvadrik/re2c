#!/bin/sh

set -e

[ $# -ne 1 ] && { echo "usage: $0 <branch>"; exit 1; }

branch="$1"
remote=$(git config branch.master.remote)

git branch -a --remote | egrep -q "^  $remote/$branch\$" || {
    echo "branch $branch not found in remote $remote"
    exit 1
}

# Clean up some folders to remove stale files.
rm -rf src/benchmarks/submatch_*/*

# Sync with branch (pull manpage files, benchmark results, etc.).
# Most of the synced files are treated as source code and committed to Git,
# except for a few helper scripts.
git fetch $remote \
    && { git archive --remote=. remotes/$remote/$branch BUILD.md \
        | tar -C src/build -xpf - \
        && mv src/build/BUILD.md src/build/build.md; } \
    && { git archive --remote=. remotes/$remote/$branch doc/manual \
        | tar -C src/ --strip-components=1 -xpf -; } \
    && { git archive --remote=. remotes/$remote/$branch examples/**/*.{re,c,h,go,rs,txt,inc} \
        | tar -C src/ -xpf -; } \
    && { git archive --remote=. remotes/$remote/$branch \
            benchmarks/submatch_{dfa_aot,dfa_jit,nfa}/results \
        | tar -C src/ -xpf -; } \
    && { git archive --remote=. remotes/$remote/$branch benchmarks/json2pgfplot.py \
        | tar -C build/ --strip-components=1 -xpf -; } \
    && { git archive --remote=. remotes/$remote/$branch build/split_man.py \
        | tar -xpf -; } \
    && { git archive --remote=. remotes/$remote/$branch CHANGELOG \
        | tar -C src/releases/changelog/ -xpf -; } \
    && mv src/releases/changelog/CHANGELOG src/releases/changelog/changelog.rst

# Find benchmark results (files of the form results_YYYYMMDD.json template) and
# pick the latest result (the one with numerically greatest date component).
pick_latest_result() {
    latest=$(ls "results/results_"*".json" \
        | sed -E 's/.*results_([0-9]+)\.json/\1/' \
        | sort -n \
        | tail -n 1)
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
    j2pp_args="$2"
    ( cd "src/benchmarks/submatch_$benchmark" \
        && echo "Generating SVG for $benchmark benchmark..." \
        && pick_latest_result \
        && python3 ../../../build/json2pgfplot.py \
            --variant $benchmark \
            --font comicneue \
            $j2pp_args \
            results.json results.tex \
        && pdflatex results.tex < /dev/null > results.log \
        && pdf2svg results.pdf results_1.svg 1 \
        && rm results.{aux,log,pdf,tex} \
    )
}

gen_bar_charts_for_benchmark dfa_aot ""
gen_bar_charts_for_benchmark dfa_jit "--relative-to ''"
gen_bar_charts_for_benchmark nfa     "--relative-to LG"
