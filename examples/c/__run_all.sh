
root_dir=$(pwd)

for f in $(find -name '*.re'); do
    echo $f
    cd $(dirname $f)

    cat $(basename ${f%.re}.c) \
        | egrep -v 'warning: rule .*matches empty string \[-Wmatch-empty-string\]' \
        | egrep -v 'warning: tag .* degree of nondeterminism \[-Wnondeterministic-tags\]' \
        > x.c

    g++ x.c -Wall -ox && ./x 2>/dev/null || { echo "*** error ***"; exit 1; }

    rm -f x.c x
    cd $root_dir
done

echo "All good."
