#!/bin/sh

builddir=__build_mingw
rm -rf $builddir
mkdir $builddir

cd $builddir
../configure LDFLAGS="-static-libstdc++ -static-libgcc" \
    --enable-debug \
    --enable-libs \
    --host i686-w64-mingw32 \
    && make -j5 LIBTOOL="dlibtool"
cd ..
