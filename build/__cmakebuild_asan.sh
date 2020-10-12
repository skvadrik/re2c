#!/bin/sh

builddir=__build_asan
rm -rf $builddir
mkdir $builddir

cd $builddir
cmake .. \
    -DCMAKE_BUILD_TYPE=Asan \
    -DRE2C_BUILD_LIBS=yes \
    -DCMAKE_CXX_FLAGS="-O2" \
    && cmake --build . -j$(nproc)
cd ..
