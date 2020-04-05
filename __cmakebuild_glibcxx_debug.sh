#!/bin/sh

builddir=__build_glibcxx_debug
rm -rf $builddir
mkdir $builddir

cd $builddir
cmake .. \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DRE2C_BUILD_LIBS=yes \
    -DCMAKE_CXX_FLAGS="-D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC" \
    && cmake --build . -j$(nproc)
cd ..
