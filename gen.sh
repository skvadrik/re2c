#!/bin/sh

srcdir="src"
objdir="obj"

rm -rf "$objdir"
cp -R "$srcdir" "$objdir"

for f in `find "$objdir" -type f -name "*.rst"`
do
    rst2html.py --link-stylesheet --stylesheet="css/default.css" "$f" > "${f%.rst}.html"
done
