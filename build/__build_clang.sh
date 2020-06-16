#!/bin/sh

builddir=__build_clang
rm -rf $builddir
mkdir $builddir

cd $builddir
../configure \
    --enable-debug \
    --enable-libs \
    CC=clang \
    CXX=clang++ \
    && make -j$(nproc)
cd ..
