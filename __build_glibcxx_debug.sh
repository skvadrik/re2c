#!/bin/sh

builddir=__build_glibcxx_debug
rm -rf $builddir
mkdir $builddir

cd $builddir
../configure \
    --enable-debug \
    --enable-libs \
    CXXFLAGS="-D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC" \
    && make -j$(nproc)
cd ..
