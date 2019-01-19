#!/bin/sh

builddir=__build_mingw
rm -rf $builddir
mkdir $builddir

cd $builddir
../configure \
    --enable-debug \
    --enable-libs \
    --host i686-w64-mingw32 \
    && make -j5
cd ..
