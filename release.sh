#!/bin/bash

set -e

echo 'RUNME: configure CXX=include-what-you-use CXXFLAGS="--check-also" && make -k 2>log && python2 `which fix_inclydes.py` < log'
echo 'RUNME: cppcheck --enable=all --inconclusive --std=posix --quiet --force -I. src/'
echo 'RUNME: for h in $(find src/ -name ''*.h*''); do echo "CHECKING $h"; g++ -I. -c $h -o foo.o; done'
echo "RUNME: uselex `find <objdir> -type f -name '*.o'`"
echo 'RUNME: configure CFLAGS="-ffunction-sections -fdata-sections" LDFLAGS="-Wl,--gc-sections -Wl,--print-gc-sections"'
echo 'RUNME: configure CXX=clang++'
echo 'RUNME: configure CXXFLAGS="-m32"'
echo 'RUNME: configure --host i686-w64-mingw32, test with wine: make wtests'
echo 'RUNME: configure CXXFLAGS="-fsanitize=address"'
echo 'RUNME: configure CXXFLAGS="-fsanitize=undefined"'
echo 'RUNME: valgrind: make vtests'
echo 'RUNME: skeleton: ./run_tests.sh --skeleton'

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
cd re2c && ./__distcheck.sh $builddir && cd ..

# commit release
git commit -a -m "Release $version."
git tag $version
for r in `git remote`
do
    git push $r master
    git push --tags $r master
done

