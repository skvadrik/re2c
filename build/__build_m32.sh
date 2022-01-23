#!/bin/sh

builddir=__build_m32
rm -rf $builddir
mkdir $builddir

toolchain="i686-unknown-linux-gnu"

cd $builddir
../configure \
    --enable-debug \
    --enable-libs \
    CXX="${toolchain}-g++" \
    LD="${toolchain}-ld" \
    && make -j$(nproc)
cd ..
