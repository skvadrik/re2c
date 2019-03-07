#!/bin/sh

builddir=__build_asan
rm -rf $builddir
mkdir $builddir

cd $builddir
../configure \
    --enable-debug \
    --enable-libs \
    CXXFLAGS="-fsanitize=address" \
    LDFLAGS="-fsanitize=address" \
    && make -j5
cd ..
