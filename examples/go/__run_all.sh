for f in $(find -name '*.re'); do
    echo $f
    gofile="${f%.re}.go"
    gotest="example_test.go"

    cat "$gofile" \
        | egrep -v 'warning: rule .*matches empty string \[-Wmatch-empty-string\]' \
        | egrep -v 'warning: tag .* degree of nondeterminism \[-Wnondeterministic-tags\]' \
        > "$gotest"

    GOPATH=$GOPATH:"$(pwd)/$(dirname $gofile)" \
        go test "$gotest" || { echo "*** error ***"; exit 1; }
    rm -f "$gotest"
done

echo "All good."
