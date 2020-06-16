#!/bin/sh

builddir=__build_ubsan
rm -rf $builddir
mkdir $builddir

cd $builddir
../configure \
    --enable-debug \
    --enable-libs \
    CXXFLAGS="-fsanitize=undefined" \
    LDFLAGS="-fsanitize=undefined" \
    && make -j$(nproc)
cd ..
