#!/bin/sh

builddir=__build_iwyu
rm -rf $builddir
mkdir $builddir

cd $builddir
../configure \
    --enable-libs \
    --enable-debug \
    CXX=include-what-you-use \
    CXXFLAGS="-Xiwyu --check_also='*.re' -Xiwyu --check_also='*.y' -Xiwyu --no_comments" \
    && make -k 2>log
cd ..
