root_dir=$(pwd)

for f in $(find -name '*.re'); do
    echo $f
    cd $(dirname $f)

    cat $(basename ${f%.re}.go) \
        | egrep -v 'warning: rule .*matches empty string \[-Wmatch-empty-string\]' \
        | egrep -v 'warning: tag .* degree of nondeterminism \[-Wnondeterministic-tags\]' \
        > x.go

    test -z "$(grep 're2c: error:' x.go)" || continue

    go run x.go >/dev/null || { echo "*** error ***"; exit 1; }

    cd $root_dir
done
rm -f x.go

echo "All good."
