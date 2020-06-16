#!/bin/sh

builddir=__build_redundant_exports
rm -rf $builddir
mkdir $builddir

cd $builddir
cmake .. \
    -DCMAKE_BUILD_TYPE=Debug \
    -DRE2C_BUILD_LIBS=yes \
    -DCMAKE_CXX_FLAGS="-O2 -ffunction-sections -fdata-sections" \
    -DCMAKE_EXE_LINKER_FLAGS="-Wl,--gc-sections -Wl,--print-gc-sections" \
    -DCMAKE_SHARED_LINKER_FLAGS="-Wl,--gc-sections -Wl,--print-gc-sections" \
    && cmake --build . -j$(nproc)
cd ..
