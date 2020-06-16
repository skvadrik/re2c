#!/bin/sh

builddir=__build_asan
rm -rf $builddir
mkdir $builddir

cd $builddir
cmake .. \
    -DCMAKE_BUILD_TYPE=Debug \
    -DRE2C_BUILD_LIBS=yes \
    -DCMAKE_CXX_FLAGS="-O2 -fsanitize=address" \
    -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address" \
    -DCMAKE_SHARED_LINKER_FLAGS="-fsanitize=address" \
    && cmake --build . -j$(nproc)
cd ..
