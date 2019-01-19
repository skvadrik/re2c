#!/bin/sh

builddir=__build
rm -rf $builddir
mkdir $builddir

cd $builddir
../configure \
    --enable-debug \
    --enable-libs \
    && make -j5
cd ..
