#!/usr/bin/env bash

set -e

usage() {
    echo "usage: ./release.sh <version> <builddir> [--ignore-examples]"
    exit 1
}

[[ $# -ge 2 ]] || usage
version="$1"
builddir="$2"
ignore_examples=0
if [[ $# -eq 3 ]]; then
    if [[ "$3" == "--ignore-examples" ]]; then
        ignore_examples=1
    else
        usage
    fi
fi

branch=`git rev-parse --abbrev-ref HEAD`
if [[ $branch != "master" ]]; then
    echo "must be on branch 'master'"
    exit 1
fi

# check that examples work
if [[ $ignore_examples -ne 1 ]]; then
    for lang in c d go haskell java js ocaml python rust swift v zig; do
        ( cd examples/$lang && ./__run_all.sh \
            || { echo "$lang examples failed"; exit 1; } )
    done
fi

# checks for which there are no scripts yet
echo 'RUNME: cppcheck --enable=all --inconclusive --std=posix --quiet --force -I. src/'
echo 'RUNME: uselex `find <objdir> -type f -name '"'*.o'"'`'
echo 'RUNME: configure CFLAGS="-ffunction-sections -fdata-sections" LDFLAGS="-Wl,--gc-sections -Wl,--print-gc-sections"'

# update version
old="[0-9]+(\.[0-9]+)*(\.dev)?"
new=$version
# edit version in configure.ac
lcontext="AC_INIT\(\[re2c\],\["
rcontext="\],\[re2c-general@lists\.sourceforge\.net\]\)"
sed -i -E "s/$lcontext$old$rcontext/$lcontext$new$rcontext/" configure.ac
# edit version in CMakeLists.txt
lcontext="project\(re2c VERSION "
rcontext=" "
sed -i -E "s/$lcontext$old$rcontext/$lcontext$new$rcontext/" CMakeLists.txt

# distcheck
build/__distcheck.sh "$builddir"

# commit release
git commit -a -m "Release $version."
git tag $version
for r in `git remote`
do
    git push $r master
    git push --tags $r master
done

