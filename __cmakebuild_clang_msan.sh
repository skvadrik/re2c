#!/bin/sh

builddir=__build_clang_msan
rm -rf $builddir
mkdir $builddir

cd $builddir
cmake .. \
    -DCMAKE_BUILD_TYPE=Debug \
    -DRE2C_BUILD_LIBS=yes \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DCMAKE_CXX_FLAGS="-O2 -fsanitize=memory -fsanitize-memory-track-origins=2" \
    -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=memory -fsanitize-memory-track-origins=2" \
    -DCMAKE_SHARED_LINKER_FLAGS="-fsanitize=memory -fsanitize-memory-track-origins=2" \
    && cmake --build . -j$(nproc)
cd ..
