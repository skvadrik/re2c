#!/bin/env python3

import argparse
import json
import math
import sys
from collections import OrderedDict


plot_preamble = """
\\documentclass[tikz]{standalone}

\\usepackage[utf8]{inputenc}
\\usepackage{amsmath, amssymb, amsfonts}
\\usepackage{tikz, pgfplots, pgfplotstable}
"""

# Use Comic Neue font.
plot_font_comicneue = """
\\usepackage{comicneue}
\\usepackage[T1]{fontenc}
\\renewcommand{\\familydefault}{\\sfdefault}
"""

# Use Computer Modern Bright font.
plot_font_cmbright = """
\\usepackage{cmbright}
\\usepackage[T1]{fontenc}
\\renewcommand{\\familydefault}{\\sfdefault}
"""

# Counterintuitively, 'assume math mode' tricks pgfmathprintnumber into not
# setting math mode, which is needed because Comic Neue does not support math.
#
# Use 'fixed relative' number format with very high precision (the numbers have
# been previously rounded to a few non-zero digits in the fractional part, so
# the trailing zeroes will will not be printed).
plot_begin = """
\\begin{document}

\\def\\plotwidth{%lfin}
\\def\\barwidth{%lfin}

\\pgfplotsset{styleX/.style={
    font=\\scriptsize,
    xbar,
    axis y line*=none,
    axis x line=none,
    y=0.12in,
    width=(\\plotwidth * 0.75),
    bar width=\\barwidth,
    xshift=\\xplotshift,
    yshift=\\yplotshift,
    xmax=\\xmax,
    xmin=-\\xmax/50,
    ymax=0.7,
    ymin=0.3 - \\nrows,
    ytick=data,
    yticklabels from table={\\table}{algo},
    every axis title/.style={below right, at={(-0.5in,0)}},
    title=\\title,
    clip=false,
    visualization depends on={x > \\xmax \\as \\xoverflow},
    visualization depends on={x > \\xmax ? -x + \\xmax : 0 \\as \\xshift},
    nodes near coords={
        \\ifdim \\xoverflow pt=1pt \\!\\Large{...}\\scriptsize\\! \\fi
        \\pgfmathprintnumber[assume math mode=true]{\\pgfplotspointmeta}
    },
    nodes near coords style={shift={(axis direction cs:\\xshift,0)}},
    nodes near coords style={/pgf/number format/.cd,
        fixed relative,
        precision = 10,
        1000 sep = {\\,}
    },
}}
"""

plot_begin_picture = """
\\begin{tikzpicture}
\\def\\xmax{%lf}
"""

plot_middle = """
\\def\\xplotshift{%lfin}
\\def\\yplotshift{%lfin}
\\def\\nrows{%d},
\\def\\title{%s},

\\pgfplotstableread {%s} \\table

\\begin{axis}[styleX]
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
    parser.add_argument("--relative-to",
        help="output CPU time relative to the specified algorithm")
    parser.add_argument("--font",
        help="use the specified font (supported fonts: cmbright, comicneue)")
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


# Find index of a group which algorithm contains the given string (stem).
def index_of_algo(group, stem):
    if stem == None:
        return 0;

    for i in range(len(group)):
        (algo, _, _, _, _) = group[i]
        if stem in algo:
            return i

    return 0


# Time format: keep integer part precise, round fractional part relative to the
# exponent (similar to PGFPLOTS's "fixed relative, precision = 2" numer format,
# but doesn't round integer part). This is to reduce visual noise on the plot.
#
# Examples: 1004, 195, 13, 3.8, 0.85, 0.017, 0.0048
#
def time_format(time):
    order = math.floor(math.log(time, 10))
    if order > 0:
        return '%.0lf'
    else:
        return '%%.%dlf' % (-order + 1)


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
def group_benchmarks(benchmarks, relative_to):
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

    maxtime = 0
    avgtime = 0
    maxsize = 0
    avgsize = 0
    maxrows = 0
    nbench = 0

    benchgroups = OrderedDict()
    for name in groups:
        group = groups[name]

        relto = index_of_algo(group, relative_to)
        (_, cputime0, binsize0, captures, regsize) = group[relto]

        timetbl = None
        if cputime0 != None:
            table = 'algo value\n'
            for (algo, time, _, _, _) in group:
                time = time / (cputime0 if relative_to != None else 1)
                maxtime = max(maxtime, time)
                avgtime += time
                table += ('{%s} ' + time_format(time) + '\n') % (algo, time)
            timetbl = table

        sizetbl = None
        if binsize0 != None:
            table = 'algo value\n'
            for (algo, _, size, _, _) in group:
                maxsize = max(maxsize, size)
                avgsize += size
                table += '{%s} %lf\n' % (algo, size)
            sizetbl = table

        title = gen_title(name)
        nrows = len(group)
        benchgroups[title] = (timetbl, sizetbl, nrows, regsize, captures)

        nbench += nrows
        maxrows = max(maxrows, nrows)

    avgtime /= nbench
    avgsize /= nbench
    maxtime = min(maxtime, 5 * avgtime)
    maxsize = min(maxsize, 5 * avgsize)

    return benchgroups, maxtime, maxsize, maxrows


# Generate a Tikz picture with a PGF plot for each benchmark group. Crop
# very long bars, so that they do not squash other bars to the left.
def generate_plot(groups, font):
    (benchgroups, maxtime, maxsize, maxrows) = groups

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
        (timetbl, sizetbl, nrows, regsize, captures) = benchgroup

        xshift = 0 if even else plotwidth
        yshift = -plotheight * (i if even else i - 1)
        title = '\\textbf{%s}' % name
        if regsize != None and captures != None:
            title += ' \\, (%d symbol%s, %d capture%s)' % (
                regsize, 's' if regsize > 1 else '',
                captures, 's' if captures > 1 else '')

        # Generate CPU time plots.
        if timetbl != None:
            plot_time += plot_middle % (xshift, yshift, nrows, title, timetbl)

        # Generate binary size plots.
        if sizetbl != None:
            plot_size += plot_middle % (xshift, yshift, nrows, title, sizetbl)

    # Glue plots together in one TeX document
    plot = plot_preamble

    if font == 'comicneue':
        plot += plot_font_comicneue
    elif font == 'cmbright':
        plot += plot_font_cmbright
    elif font != None:
        sys.exit('error: unsupported font: "%s"' % font)

    plot += plot_begin % (plotwidth, barwidth)

    if plot_time != '':
        plot += (plot_begin_picture % maxtime) + plot_time + plot_end_picture
    if plot_size != '':
        plot += (plot_begin_picture % maxsize) + plot_size + plot_end_picture

    plot += plot_end

    return plot


def main():
    args = parse_args()

    with open(args.input) as f:
        input = json.load(f)

    groups = group_benchmarks(input['benchmarks'], args.relative_to)
    plot = generate_plot(groups, args.font)

    with open(args.output, 'w') as f:
        f.write(plot)


if __name__ == "__main__":
    main()
