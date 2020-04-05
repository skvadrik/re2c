#!/bin/sh

builddir=__build_lsan
rm -rf $builddir
mkdir $builddir

cd $builddir
cmake .. \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DRE2C_BUILD_LIBS=yes \
    -DCMAKE_CXX_FLAGS="-fsanitize=leak" \
    -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=leak" \
    -DCMAKE_SHARED_LINKER_FLAGS="-fsanitize=leak" \
    && cmake --build . -j$(nproc)
cd ..
