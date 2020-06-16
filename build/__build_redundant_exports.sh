#!/bin/sh

builddir=__build_redundant_exports
rm -rf $builddir
mkdir $builddir

cd $builddir
../configure \
    --enable-debug \
    --enable-libs \
    CFLAGS="-ffunction-sections -fdata-sections" \
    LDFLAGS="-Wl,--gc-sections -Wl,--print-gc-sections" \
    && make -j$(nproc)
cd ..
