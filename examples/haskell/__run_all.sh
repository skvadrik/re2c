root_dir=$(pwd)

for f in $(find -name '*.re'); do
    cd $(dirname $f)

    hsfile="$(basename ${f%.re}.hs)"
    hstest="example.hs"

    cat "$hsfile" \
        | egrep -v 'warning: rule .*matches empty string \[-Wmatch-empty-string\]' \
        | egrep -v 'warning: tag .* degree of nondeterminism \[-Wnondeterministic-tags\]' \
        > "$hstest"

    # If the autogenerated message appears more than once in the file, then
    # it must have autogenerated header appended at the end. Cut it off.
    msg='Generated by re2hs'
    if [ $(grep -c "$msg" "$hstest") -gt 1 ]; then
        # Get the line of the second message occurrence.
        l=$(grep -n "$msg" "$hstest" | tail -n +2 | cut -d : -f 1)
        # Cut off everything past that line.
        head -n $l "$hstest" > "$hstest".mod && mv "$hstest".mod "$hstest"
    fi

    echo "$f"
    # header test requires special handling for Haskell - temporarily rename it to State.hs
    if $(grep -q -- '--header' "$hstest"); then
        ln -s lexer/state.hs State.hs \
            && ghc "$hstest" -O2 -Wall -o example && ./example \
            || { echo "*** error ***"; exit 1; }
        rm State.hs
    else
        ghc "$hstest" -O2 -Wall -o example && ./example \
            || { echo "*** error ***"; exit 1; }
    fi

    rm -f "$hstest" example $(find -name '*.o' -o -name '*.hi')
    cd $root_dir
done

echo "All good."
