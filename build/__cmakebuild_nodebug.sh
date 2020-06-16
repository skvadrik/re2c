#!/bin/sh

builddir=__build_nodebug
rm -rf $builddir
mkdir $builddir

cd $builddir
cmake .. \
    -DRE2C_BUILD_LIBS=yes \
    && cmake --build . -j$(nproc)
cd ..
