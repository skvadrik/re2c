#!/bin/bash

source ./utils.sh

if [[ $# -eq 0 ]]; then
  echo "Usage: $0 <git-branch-name>"
  exit 1
fi

branch="$1"
remote=`git config branch.master.remote`

if ! git ls-remote --heads "$remote" "$branch" | grep --quiet "$branch"; then
    echo "branch $branch not found in remote $remote"
    exit 1
fi

# Clean up some folders to remove stale files.
rm -rf src/benchmarks/submatch_*/*

# Sync with branch (pull manpage files, benchmark results, etc.).
# Most of the synced files are treated as source code and committed to Git,
# except for a few helper scripts.
mkdir -p build
git fetch $remote
git archive --remote=. "remotes/$remote/$branch" BUILD.md | tar --directory=src/build -xpf -
mv src/build/BUILD.md src/build/build.md
git archive --remote=. "remotes/$remote/$branch" LICENSE | tar --directory=src -xpf -
git archive --remote=. "remotes/$remote/$branch" doc/manual | tar --directory=src --strip-components=1 -xpf -
git archive --remote=. "remotes/$remote/$branch" examples/**/*.{re,c,h,d,go,hs,java,js,ml,py,rs,v,zig,inc} | tar --directory=src -xpf -
git archive --remote=. "remotes/$remote/$branch" benchmarks/submatch_{dfa_aot,dfa_jit,nfa}/results | tar --directory=src -xpf -
git archive --remote=. "remotes/$remote/$branch" benchmarks/json2pgfplot.py | tar --directory=build --strip-components=1 -xpf -
git archive --remote=. "remotes/$remote/$branch" build/split_man.py | tar -xpf -
git archive --remote=. "remotes/$remote/$branch" CHANGELOG | tar --directory=src/releases/changelog -xpf -
mv src/releases/changelog/CHANGELOG src/releases/changelog/changelog.rst

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
    (
        cd "src/benchmarks/submatch_$benchmark"
        echo "Generating SVG for $benchmark benchmark..."
        pick_latest_result
        python3 ../../../build/json2pgfplot.py \
            --variant $benchmark \
            --font comicneue \
            $j2pp_args \
            results.json \
            results.tex
        pdflatex -halt-on-error -file-line-error results.tex
        pdf2svg results.pdf results_1.svg 1
        rm results.{aux,log,pdf,tex}
    )
}

gen_bar_charts_for_benchmark dfa_aot ""
gen_bar_charts_for_benchmark dfa_jit "--relative-to ''"
gen_bar_charts_for_benchmark nfa     "--relative-to LG"

echo "Build playground"
playground/build.sh "$branch"

echo "The script has finished successfully"
