#!/bin/sh

builddir=__build_clang_msan
rm -rf $builddir
mkdir $builddir

cd $builddir
../configure \
    --enable-debug \
    --enable-libs \
    CC=clang \
    CXX=clang++ \
    CFLAGS="-fsanitize=memory -fsanitize-memory-track-origins=2" \
    CXXFLAGS="-fsanitize=memory -fsanitize-memory-track-origins=2" \
    LDFLAGS="-fsanitize=memory -fsanitize-memory-track-origins=2" \
    && make -j$(nproc)
cd ..
