#!/usr/bin/env python3

import argparse
import json
import math
import sys
from collections import OrderedDict


plot_preamble = """
\\documentclass[tikz]{standalone}

\\usepackage[utf8]{inputenc}
\\usepackage{amsmath, amssymb, amsfonts}
\\usepackage{xcolor}
\\usepackage{tikz, pgfplots, pgfplotstable}
\\usepackage{pifont}

\\definecolor{colorX}{HTML}{A1CAF1}
\\definecolor{colorY}{HTML}{FBCEB1}
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
    width=\\plotwidth*1.15,
    bar width=\\barwidth,
    xshift=\\xplotshift,
    yshift=\\yplotshift,
    xmax=\\xmax,
    xmin=0,
    ymax=0.7,
    ymin=0.3 - \\nrows,
    ytick=data,
    ytick style={draw=none},
    yticklabels=\\empty,
    title=\\empty,
    clip=false,
    visualization depends on={x > \\xmax \\as \\xoverflow},
    visualization depends on={x > \\xmax ? -x + \\xmax : 0 \\as \\xshift},
    nodes near coords={
        \\ifdim \\xoverflow pt=1pt \\!\\ding{220}\\! \\scriptsize \\fi
        \\pgfmathprintnumber[assume math mode=true]{\\pgfplotspointmeta}
    },
    nodes near coords style={shift={(axis direction cs:\\xshift,0)}},
    nodes near coords style={/pgf/number format/.cd,
        fixed relative,
        precision = 10,
        1000 sep = {\\,}
    },%s}}
"""

plot_labels_and_title = """
    yticklabels from table={\\table}{algo},
    every axis title/.style={below %s, at={(-0.08in,0)}},
    title=\\title,
"""

plot_begin_picture = """
\\begin{tikzpicture}

\\begin{scope}[xshift=-0.2in, yshift=%sin * 0.75]
%s
\\end{scope}
"""

plot_middle = """
\\def\\xplotshift{%lfin}
\\def\\yplotshift{%lfin}
\\def\\nrows{%d},
\\def\\title{%s},
\\def\\xmax{%lf}

\\pgfplotstableread {%s} \\table

\\begin{axis}[styleX,%s]
    \\clip(current axis.south west) rectangle(current axis.north east);
    \\addplot[fill=%s] table[x=value, y expr=-\\coordindex] from \\table;
\\end{axis}
"""

plot_end_picture = """
\\end{tikzpicture}
"""

plot_end = """
\\end{document}
"""


VARIANTS = ['dfa_aot', 'dfa_jit', 'nfa']


def parse_args():
    variants = ', '.join(VARIANTS)

    parser = argparse.ArgumentParser()
    parser.add_argument("input", help="input JSON file")
    parser.add_argument("output", help="output TeX file")
    parser.add_argument("--variant",
        help="variant of the benchmark, one of %s" % variants)
    parser.add_argument("--relative-to",
        help="output CPU time relative to the specified algorithm")
    parser.add_argument("--font",
        help="use the specified font (supported fonts: cmbright, comicneue)")

    args = parser.parse_args()
    if args.variant not in VARIANTS:
        sys.exit("please specify --variant (possible values: %s)" % variants)

    return args


# Generate benchmark title from benchmark name.
def gen_title(oldname, remove_suffix):
    if remove_suffix:
        # cut off the last sub-word after the dash
        oldname = oldname[:oldname.rfind("-")]

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


class Params:
    def __init__(self, args):
        self.barwidth = 0.08

        if args.variant == 'dfa_aot':
            self.override_params_dfa_aot()
        elif args.variant == 'dfa_jit':
            self.override_params_dfa_jit()
        elif args.variant == 'nfa':
            self.override_params_nfa()

        self.font = ''
        if args.font == 'comicneue':
            self.font = plot_font_comicneue
        elif args.font == 'cmbright':
            self.font = plot_font_cmbright
        elif args.font:
            sys.exit('error: unsupported font: "%s"' % font)

        if args.relative_to: # override only if set
            self.relative_to = args.relative_to

    def override_params_dfa_aot(self):
        self.plotwidth = 1.5
        self.xshift = 2 * self.plotwidth
        self.header = """
            \\node[anchor=west] (x0) at (0.15in,0) {\\small\\bf{gcc (time)}};
            \\node[anchor=west] (x1) at (1.65in,0) {\\small\\bf{gcc (size)}};
            \\node[anchor=west] (x2) at (3.15in,0) {\\small\\bf{clang (time)}};
            \\node[anchor=west] (x3) at (4.65in,0) {\\small\\bf{clang (size)}};
        """
        self.title_suffix = True
        self.relative_to = None
        self.title_annotate = False
        self.global_styles = ""
        self.local_styles = plot_labels_and_title % 'left'

    def override_params_dfa_jit(self):
        self.plotwidth = 2.7
        self.xshift = self.plotwidth
        self.header = """
            \\node[anchor=west] (x0) at (0.15in,0) {\\small\\bf{regcomp (time)}};
            \\node[anchor=west] (x1) at (2.85in,0) {\\small\\bf{regexec (time)}};
        """
        self.title_suffix = True
        self.relative_to = ''
        self.title_annotate = False
        self.global_styles = ""
        self.local_styles = plot_labels_and_title % 'left'

    def override_params_nfa(self):
        self.plotwidth = 2.5
        self.xshift = self.plotwidth + 1
        self.header = ""
        self.only_1st_col_with_labels = False
        self.title_suffix = False
        self.relative_to = 'LG'
        self.title_annotate = True
        self.global_styles = plot_labels_and_title % 'right'
        self.local_styles = ""


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
def group_benchmarks(benchmarks, params):
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

        relto = index_of_algo(group, params.relative_to)
        (_, cputime0, binsize0, captures, regsize) = group[relto]

        timetbl = None
        if cputime0 != None:
            table = 'algo value\n'
            for (algo, time, _, _, _) in group:
                time = time / (cputime0 if params.relative_to != None else 1)
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

        title = gen_title(name, params.title_suffix)
        nrows = len(group)
        benchgroups[name] = (title, timetbl, sizetbl, nrows, regsize, captures)

        nbench += nrows
        maxrows = max(maxrows, nrows)

    avgtime /= nbench
    avgsize /= nbench
    factor = 10 if params.relative_to != None else 3
    maxtime = min(maxtime, factor * avgtime)
    maxsize = min(maxsize, factor * avgsize)

    params.plotheight = 0.15 + maxrows * params.barwidth * 0.75
    params.maxtime = maxtime
    params.maxsize = maxsize

    return benchgroups


# Generate a Tikz picture with a PGF plot for each benchmark group. Crop
# very long bars, so that they do not squash other bars to the left.
def generate_plot(benchgroups, params):
    plot = plot_preamble
    plot += params.font
    plot += plot_begin % (params.plotwidth, params.barwidth, params.global_styles)
    plot += plot_begin_picture % (params.plotheight, params.header)

    i = 0
    for name, benchgroup in benchgroups.items():
        even = i % 2 == 0
        i += 1
        (title, timetbl, sizetbl, nrows, regsize, captures) = benchgroup

        xshift = 0 if even else params.xshift
        yshift = -params.plotheight * (i if even else i - 1)
        title = '\\textbf{%s}' % title
        if params.title_annotate and regsize != None and captures != None:
            title += ' \\, (%d symbol%s, %d capture%s)' % (
                regsize, 's' if regsize > 1 else '',
                captures, 's' if captures > 1 else '')

        # Generate CPU time plots.
        if timetbl != None:
            plot += plot_middle % (xshift, yshift, nrows, title, params.maxtime,
                timetbl, params.local_styles if even else '', 'colorX')

        # Generate binary size plots.
        if sizetbl != None:
            xshift += params.plotwidth
            plot += plot_middle % (xshift, yshift, nrows, title, params.maxsize,
                sizetbl, '', 'colorY')

    plot += plot_end_picture
    plot += plot_end

    return plot


def main():
    args = parse_args()

    with open(args.input) as f:
        input = json.load(f)

    params = Params(args)
    groups = group_benchmarks(input['benchmarks'], params)
    plot = generate_plot(groups, params)

    with open(args.output, 'w') as f:
        f.write(plot)


if __name__ == "__main__":
    main()
