#!/bin/sh

builddir=__build
rm -rf $builddir
mkdir $builddir

cd $builddir
cmake .. \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_CXX_FLAGS="-O2" \
    -DRE2C_BUILD_LIBS=yes \
    && cmake --build . -j$(nproc)
cd ..
