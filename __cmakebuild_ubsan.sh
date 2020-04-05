#!/bin/sh

builddir=__build_ubsan
rm -rf $builddir
mkdir $builddir

cd $builddir
cmake .. \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DRE2C_BUILD_LIBS=yes \
    -DCMAKE_CXX_FLAGS="-fsanitize=undefined" \
    -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=undefined" \
    -DCMAKE_SHARED_LINKER_FLAGS="-fsanitize=undefined" \
    && cmake --build . -j$(nproc)
cd ..
