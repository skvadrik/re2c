#!/usr/bin/env bash

source ./utils.sh

if [[ $# -eq 0 ]]; then
  echo "Usage: $0 <git-branch-name> [--no-svg] [--no-playground]"
  exit 1
fi

branch="$1"
remote=`git config branch.master.remote`

gen_svg=1
gen_playground=1
while [[ $# -gt 1 ]]; do
    if [[ "$2" == "--no-svg" ]]; then
        gen_svg=0
        shift
    elif [[ "$2" == "--no-playground" ]]; then
        gen_playground=0
        shift
    else
        echo "Error: unknown argument: $2"
        exit 1
    fi
done

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
git archive --remote=. "remotes/$remote/$branch" examples/**/*.{re,c,h,d,go,hs,java,js,ml,py,rs,swift,v,zig,inc} | tar --directory=src -xpf -
git archive --remote=. "remotes/$remote/$branch" benchmarks/c/results | tar --directory=src -xpf -
git archive --remote=. "remotes/$remote/$branch" benchmarks/c/libre2c/{jit,nfa}/results | tar --directory=src -xpf -
git archive --remote=. "remotes/$remote/$branch" benchmarks/_scripts/json2pgfplot.py | tar --directory=build --strip-components=2 -xpf -
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
    path="$2"
    j2pp_args="$3"
    j2pp="$(pwd)/build/json2pgfplot.py"
    (
        cd "src/benchmarks/$path"
        echo "Generating SVG for $benchmark benchmark..."
        pick_latest_result
        python3 "$j2pp" \
            --variant $benchmark \
            --font comicneue \
            $j2pp_args \
            results.json \
            results.tex
        pdflatex -halt-on-error -file-line-error results.tex < /dev/null > results.log
        pdf2svg results.pdf results_1.svg 1
        rm results.{aux,log,pdf,tex}
    )
}

if [[ "$gen_svg" -ne 0 ]]; then
    gen_bar_charts_for_benchmark "aot" "c" ""
    gen_bar_charts_for_benchmark "jit" "c/libre2c/jit" "--relative-to ''"
    gen_bar_charts_for_benchmark "nfa" "c/libre2c/nfa" "--relative-to LG"
fi

if [[ "$gen_playground" -ne 0 ]]; then
    echo "Build playground"
    playground/build.sh "$branch"
fi

echo "The script has finished successfully"
