#!/bin/sh

builddir=__build_m32
rm -rf $builddir
mkdir $builddir

cd $builddir
../configure \
    --enable-debug \
    --enable-libs \
    CXXFLAGS="-m32" \
    LDFLAGS="-m32" \
    && make -j$(nproc)
cd ..
