This is a program that regenerates re2c Unicode definitions. It is based on the
official Unicode database - a collection of (mostly) text files that define
various Unicode categories, properties, scripts, etc.

Build with `make`. This will:
  - download the necessary files from unicode.org in the current directory
  - build the `generate` program from sources
  - run `generate` and dump the following files in the current directory:
    * unicode_categories.re

To move Unicode files to their final destinations, use `make install`.

To clean, use `make clean`.

Note: simple line-by-line `git diff` may be very hard to read due to small
differences on very long lines, use word-based diff (tweak the regex if needed):
`git diff --word-diff=color --word-diff-regex='[a-zA-Z0-9]+|-'`.
