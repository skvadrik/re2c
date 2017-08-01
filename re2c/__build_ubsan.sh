#!/bin/sh

builddir=__build_ubsan
rm -rf $builddir
mkdir $builddir

cd $builddir
../configure CXXFLAGS="-fsanitize=undefined" LDFLAGS="-fsanitize=undefined" && \
make -j5
cd ..
