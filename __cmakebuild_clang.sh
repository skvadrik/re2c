#!/bin/sh

builddir=__build_clang
rm -rf $builddir
mkdir $builddir

cd $builddir
cmake .. \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_CXX_FLAGS="-O2" \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DRE2C_BUILD_LIBS=yes \
    && cmake --build . -j$(nproc)
cd ..
