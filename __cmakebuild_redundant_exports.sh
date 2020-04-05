#!/bin/sh

builddir=__build_redundant_exports
rm -rf $builddir
mkdir $builddir

cd $builddir
cmake .. \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DRE2C_BUILD_LIBS=yes \
    -DCMAKE_C_FLAGS="-ffunction-sections -fdata-sections" \
    -DCMAKE_CXX_FLAGS="-ffunction-sections -fdata-sections" \
    -DCMAKE_EXE_LINKER_FLAGS="-Wl,--gc-sections -Wl,--print-gc-sections" \
    -DCMAKE_SHARED_LINKER_FLAGS="-Wl,--gc-sections -Wl,--print-gc-sections" \
    && cmake --build . -j$(nproc)
cd ..
