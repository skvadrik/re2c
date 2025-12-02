root_dir=$(pwd)

for f in $(find -name '*.re'); do
    grep -q 'func main' $f || continue # skip incomplete tests
    [ "$f" == "./signed_yyctype.re" ] && continue # expected compilation error

    echo $f
    cd $(dirname $f)

    cat $(basename ${f%.re}.go) \
        | egrep -v 'warning: rule .*matches empty string \[-Wmatch-empty-string\]' \
        | egrep -v 'warning: tag .* degree of nondeterminism \[-Wnondeterministic-tags\]' \
        > x.go

    go run x.go >/dev/null || { echo "*** error ***"; exit 1; }

    rm -f x.go
    cd $root_dir
done

echo "All good."
