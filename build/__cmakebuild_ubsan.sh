#!/bin/sh

builddir=__build_ubsan
rm -rf $builddir
mkdir $builddir

cd $builddir
cmake .. \
    -DCMAKE_BUILD_TYPE=Ubsan \
    -DRE2C_BUILD_LIBS=yes \
    -DCMAKE_CXX_FLAGS="-O2" \
    && cmake --build . -j$(nproc)
cd ..
