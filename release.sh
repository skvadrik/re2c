#!/bin/bash

set -e

if [[ $# -ne 1 ]]
then
    echo "usage: ./release.sh <version>"
    exit 1
fi
version="$1"

branch=`git rev-parse --abbrev-ref HEAD`
if [[ $branch != "master" ]]
then
    echo "must be on branch 'master'"
    exit 1
fi

# edit version in re2c/configure.in
lcontext="AC_INIT\(\[re2c\],\["
rcontext="\],\[re2c-general@lists\.sourceforge\.net\]\)"
old="[0-9]+(\.[0-9]+)*(\.dev)?"
new=$version
sed -i -E "s/$lcontext$old$rcontext/$lcontext$new$rcontext/" re2c/configure.ac

# distcheck
builddir=.build
cd re2c && ./distcheck.sh $builddir && cd ..

# commit release
git commit -a -m "Release $version."
git tag $version
for r in `git remote`
do
    git push $r master
    git push --tags $r master
done

