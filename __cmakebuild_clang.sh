#!/bin/sh

builddir=__build_clang
rm -rf $builddir
mkdir $builddir

cd $builddir
cmake .. \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DRE2C_BUILD_LIBS=yes \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ \
    && cmake --build . -j$(nproc)
cd ..
