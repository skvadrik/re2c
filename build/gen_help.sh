#!/usr/bin/env sh

{
    # We can safely export the following variables unless we source this file
    export TERM=dumb
    export MANPAGER=cat
    export MANWIDTH=80

    echo "extern const char *help;"
    echo "const char *help ="

    # Here is how it works:
    #
    # 1. 'col -b' removes backspaces, 'col -x' replaces tabs with spaces
    # 2. Drop lines from the top up to USAGE word
    # 3. Drop two lines from the bottom
    # 4. Escape \x by \\x
    # 5. Escape " by \"
    # 6. Wrap each line in double quotes " and adding a newline character \n
    man "$1"                        \
        | col -bx                   \
        | grep -A 1000 USAGE        \
        | sed '$d' | sed '$d'       \
        | sed 's/\\x/\\\\x/g'       \
        | sed -E 's/"/\\"/g'        \
        | sed -E 's/(.*)/"\1\\n"/'

    echo ";"
} > "$2"
