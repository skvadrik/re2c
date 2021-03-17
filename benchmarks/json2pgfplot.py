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

\\def\\plotwidth{%lfin}
\\def\\barwidth{%lfin}

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
    xmax=\\xmax,
    ytick=data,
    yticklabels from table={\\table}{algo},
    every axis title/.style={below right, at={(-0.5in,-0.1in)}},
    title=\\title,
    enlarge y limits=\\enlargelim,
}}

\\pgfplotsset{styleXabs/.style={
    nodes near coords,
}}

\\pgfplotsset{styleXrel/.style={
    clip=false,
    visualization depends on={x > \\xmax \\as \\xoverflow},
    visualization depends on={x > \\xmax ? -x + \\xmax - 1 : 0 \\as \\xshift},
    every node near coord/.style={shift={(axis direction cs:\\xshift,0)}},
    nodes near coords={\\ifdim \\xoverflow pt=1pt \\textbf{...} \\fi
        \\pgfmathprintnumber{\\pgfplotspointmeta}},
}}
"""


plot_begin_picture = """
\\begin{tikzpicture}
"""


plot_middle = """
\\def\\enlargelim{%lf}
\\def\\xplotshift{%lfin}
\\def\\yplotshift{%lfin}
\\def\\xmin{%lf}
\\def\\xmax{%lf}
\\def\\title{%s},

\\pgfplotstableread {%s} \\table

\\begin{axis}[styleX, styleX%s]
    \\clip(current axis.south west) rectangle(current axis.north east);
    \\addplot[fill=lightgray] table[x=value, y expr=-\\coordindex] from \\table;
\\end{axis}
"""


plot_end_picture = """
\\end{tikzpicture}
"""


plot_end = """
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
#       ["cpu_time": <number>,]
#       ["bin_size": <number>,]
#       ["captures": <number>,]
#       ["regsize": <number>,] ...
#     }, ...
#   ], ...
# }
#
def group_benchmarks(benchmarks, relative):
    benchcount = len(benchmarks)

    groups = OrderedDict()
    for bench in benchmarks:
        name, algo = bench['name'].split('_')
        cputime = bench['cpu_time'] if 'cpu_time' in bench else None
        binsize = bench['bin_size'] if 'bin_size' in bench else None
        captures = bench['captures'] if 'captures' in bench else None
        regsize = bench['regsize'] if 'regsize' in bench else None
        groups.setdefault(name, []).append(
            (algo, cputime, binsize, captures, regsize))

    benchgroups = OrderedDict()
    for name in groups:
        group = groups[name]
        (_, cputime0, binsize0, captures, regsize) = group[0]

        group_time = None
        if cputime0 != None:
            maxtime = 0
            table = 'algo value\n'
            for (algo, time, _, _, _) in group:
                time = time / (cputime0 if relative else 1)
                maxtime = max(maxtime, time)
                table += '{%s} %lf\n' % (algo, time)
            group_time = (table, maxtime)

        group_size = None
        if binsize0 != None:
            maxsize = 0
            table = 'algo value\n'
            for (algo, _, size, _, _) in group:
                maxsize = max(maxsize, size)
                table += '{%s} %lf\n' % (algo, size)
            group_size = (table, maxsize)

        title = gen_title(name)
        benchgroups[title] = (group_time, group_size, len(group),
            captures, regsize)

    return benchgroups


# Generate a Tikz picture with a PGF plot for each benchmark group.
# If the relative mode is on, cut off outliers (very long bars), so that they
# do not completely squash other bars to the left.
def generate_plot(benchgroups, relative):
    # Compute global maximum values.
    maxrows = 0
    maxgrouptime = 0
    maxgroupsize = 0
    for _, (group_time, group_size, nrows, _, _) in benchgroups.items():
        maxrows = max(maxrows, nrows)
        if group_time != None:
            (_, maxtime) = group_time
            maxgrouptime = max(maxgrouptime, maxtime)
        if group_size != None:
            (_, maxsize) = group_size
            maxgroupsize = max(maxgroupsize, maxsize)

    # Plot width is approximately half the usual page width.
    plotwidth = 3.5
    # Bar width is chosen impirically so that it looks good.
    barwidth = 0.08
    # Plot height is roughly bar width times maximum group size.
    plotheight = 0.15 + maxrows * barwidth * 0.75

    plot_time = ''
    plot_size = ''
    i = 0
    for name, benchgroup in benchgroups.items():
        even = i % 2 == 0
        i += 1
        (group_time, group_size, nrows, regsize, captures) = benchgroup

        enlargelim = 1 / nrows
        xshift = 0 if even else plotwidth
        yshift = -plotheight * (i if even else i - 1)
        title = '\\textbf{%s}' % name
        if regsize != None and captures != None:
            title += ' \\, (%d sym, %d cap)' % (regsize, captures)

        # Generate CPU time plots.
        if group_time != None:
            (table, maxtime) = group_time
            xmax = (min(maxgrouptime, 100) if relative else maxgrouptime) * 1.1
            xmin = -(xmax if relative else maxtime) / 50
            style = 'rel' if relative else 'abs'

            plot_time += plot_middle % (enlargelim,
                xshift, yshift, xmin, xmax, title, table, style)

        # Generate binary size plots.
        if group_size != None:
            (table, maxsize) = group_size
            xmax = maxgroupsize * 1.1
            xmin = -maxtime / 50

            plot_size += plot_middle % (enlargelim,
                xshift, yshift, xmin, xmax, title, table, 'abs')

    # Glue plots together in one TeX document
    plot = plot_begin % (plotwidth, barwidth)
    if plot_time != '':
        plot += plot_begin_picture + plot_time + plot_end_picture
    if plot_size != '':
        plot += plot_begin_picture + plot_size + plot_end_picture
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
