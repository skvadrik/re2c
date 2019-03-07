#!/bin/sh -e

pdflatex -shell-escape tdfa.tex </dev/null > tdfa.build_log
bibtex tdfa
pdflatex -shell-escape tdfa.tex </dev/null > tdfa.build_log
pdflatex -shell-escape tdfa.tex </dev/null > tdfa.build_log
