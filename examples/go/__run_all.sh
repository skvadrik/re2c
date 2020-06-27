
root_dir=$(pwd)
export RE2C=$root_dir/../../__build/re2c

for f in $(find -name '*.re'); do
    echo $f

    gofile="example.go"
    gotest="example_test.go"
    cp "$f" "$gofile"
    go generate "$gofile"

    cat "$gotest" \
        | egrep -v 'warning: rule .*matches empty string \[-Wmatch-empty-string\]' \
        | egrep -v 'warning: tag .* degree of nondeterminism \[-Wnondeterministic-tags\]' \
        > "$gotest.1"
    mv "$gotest.1" "$gotest"

    go test "$gotest" || { echo "*** error ***"; exit 1; }
    rm -f "$gofile" "$gotest"
done

echo "All good."
