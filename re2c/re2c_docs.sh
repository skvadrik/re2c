#!/bin/sh

# generate re2c.1 from re2c.ad
a2x -f manpage re2c.ad

# generate htdocs/manual.html from re2c.ad
asciidoc -o htdocs/manual.html re2c.ad
