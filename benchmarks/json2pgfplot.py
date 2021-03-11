#!/bin/env python3

import argparse
import json
from collections import OrderedDict


plot_begin = """
\\documentclass[tikz]{standalone}

\\usepackage[utf8]{inputenc}
\\usepackage{amsmath, amssymb, amsfonts}
\\usepackage{tikz, pgfplots, pgfplotstable}

\\begin{document}
\\begin{tikzpicture}

\\def\\plotwidth{%lfin}
\\def\\barwidth{%lfin}
\\def\\xmax{%lf}

\\pgfplotsset{styleX/.style={
    font=\\scriptsize,
    xbar,
    axis y line*=none,
    axis x line=none,
    nodes near coords style={/pgf/number format/.cd,1000 sep={\\,}},
    y=0.12in,
    width=(\\plotwidth * 0.75),
    bar width=\\barwidth,
    xshift=\\xplotshift,
    yshift=\\yplotshift,
    xmin=\\xmin,
    ytick=data,
    yticklabels from table={\\table}{alg},
    every axis title/.style={below right, at={(-0.5in,-0.1in)}},
    title=\\title,
    enlarge y limits=\\enlargelim,
}}

\\pgfplotsset{styleXabs/.style={
    nodes near coords,
}}

\\pgfplotsset{styleXrel/.style={
    xmax=\\xmax,
    clip=false,
    visualization depends on={x > \\xmax \\as \\xoverflow},
    visualization depends on={x > \\xmax ? -x + \\xmax - 1 : 0 \\as \\xshift},
    every node near coord/.style={shift={(axis direction cs:\\xshift,0)}},
    nodes near coords={\\ifdim \\xoverflow pt=1pt \\textbf{...} \\fi
        \\pgfmathprintnumber{\\pgfplotspointmeta}},
}}
"""

plot_middle = """
\\def\\enlargelim{%lf}
\\def\\xplotshift{%lfin}
\\def\\yplotshift{%lfin}
\\def\\xmin{%lf}
\\def\\title{\\textbf{%s} \\, (%d symbols, %d captures)},

\\pgfplotstableread {%s} \\table

\\begin{axis}[styleX, styleX%s]
    \\clip(current axis.south west) rectangle(current axis.north east);
    \\addplot[fill=lightgray] table[x=time, y expr=-\\coordindex] from \\table;
\\end{axis}
"""

plot_end = """
\\end{tikzpicture}
\\end{document}
"""

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("input", help="input JSON file")
    parser.add_argument("output", help="output TeX file")
    parser.add_argument("--relative", action="store_true",
        help="output CPU time relative to the first algorithm")
    return parser.parse_args()

# Generate benchmark title from benchmark name.
def gen_title(oldname):
    # Name begins with a letter, so it must be a plain language word.
    if oldname[0].isalpha():
        return oldname

    # Name begins with something else than a letter, treat it as a regexp and
    # render as a TeX math formula. This requires adding a few metacharacters.
    newname = ""
    for char in oldname:
        if char in "{*+?":
            # Repetition counters must be in superscript.
            newname += "^"
        newname += char
    return "$\\boldsymbol{" + newname + "}$"

# Split benchmarks into groups by regexp (the first component of the name).
# If the relative mode is on, normalize CPU time by the time of the first
# benchmark in each group.
#
# Expected JSON fomat:
# {
#   "benchmarks": [
#     {
#       "name": <string>,
#       "cpu_time": <number>,
#       "captures": <number>,
#       "regsize": <number>, ...
#     }, ...
#   ], ...
# }
#
def group_benchmarks(benchmarks, relative):
    benchcount = len(benchmarks)
    benchgroups = OrderedDict()

    i = 0
    while i < benchcount:
        bench0 = benchmarks[i]
        name0, _ = bench0["name"].split('_')
        time0 = bench0["cpu_time"]
        captures = bench0["captures"]
        regsize = bench0["regsize"]
        maxtime = 0
        table = "alg time\n"

        j = i
        while j < benchcount:
            bench = benchmarks[j]
            name, alg = bench["name"].split('_')
            if name != name0:
                break
            time = bench["cpu_time"]
            if relative:
                time = time / time0
            table += "{%s} %lf\n" % (alg, time)
            maxtime = max(maxtime, time)
            j += 1

        nrows = j - i
        title = gen_title(name0)
        benchgroups[title] = (table, nrows, maxtime, captures, regsize)
        i = j

    return benchgroups

# Generate a Tikz picture with a PGF plot for each benchmark group.
# If the relative mode is on, cut off outliers (very long bars), so that they
# do not completely squash other bars to the left.
def generate_plot(benchgroups, relative):
    maxrows = 0
    maxgrouptime = 0
    for _, (_, nrows, maxtime, _, _) in benchgroups.items():
        maxrows = max(maxrows, nrows)
        maxgrouptime = max(maxgrouptime, maxtime)

    # Plot width is approximately half the usual page width.
    plotwidth = 3.5
    # Bar width is chosen impirically so that it looks good.
    barwidth = 0.08
    # Plot height is roughly bar width times maximum group size.
    plotheight = 0.15 + maxrows * barwidth * 0.75
    # Maximum X value is set only in relative mode. Cutoff value is chosen
    # arbitrarily to make the bars not too thin.
    xmax = min(maxgrouptime + 0.1, 100)

    plot = plot_begin % (plotwidth, barwidth, xmax)

    i = 0
    for name, benchgroup in benchgroups.items():
        even = i % 2 == 0
        i += 1

        (table, nrows, maxtime, captures, regsize) = benchgroup

        enlargelim = 1 / nrows
        xshift = 0 if even else plotwidth
        yshift = -plotheight * (i if even else i - 1)
        xmin = -(xmax if relative else maxtime) / 50
        style = "rel" if relative else "abs"

        plot += plot_middle % (enlargelim,
            xshift, yshift, xmin, name, regsize, captures, table, style)

    plot += plot_end
    return plot

def main():
    args = parse_args()

    with open(args.input) as f:
        input = json.load(f)

    benchgroups = group_benchmarks(input['benchmarks'], args.relative)
    plot = generate_plot(benchgroups, args.relative)

    with open(args.output, 'w') as f:
        f.write(plot)

if __name__ == "__main__":
    main()
