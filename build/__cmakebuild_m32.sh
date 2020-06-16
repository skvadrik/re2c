#!/bin/sh

builddir=__build_m32
rm -rf $builddir
mkdir $builddir

cd $builddir
cmake .. \
    -DCMAKE_BUILD_TYPE=Debug \
    -DRE2C_BUILD_LIBS=yes \
    -DCMAKE_CXX_FLAGS="-O2 -m32" \
    -DCMAKE_EXE_LINKER_FLAGS="-m32" \
    -DCMAKE_SHARED_LINKER_FLAGS="-m32" \
    && cmake --build . -j$(nproc)
cd ..
