#!/bin/sh

builddir=__build_nodebug
rm -rf $builddir
mkdir $builddir

cd $builddir
../configure \
    --enable-libs \
    && make -j$(nproc)
cd ..
