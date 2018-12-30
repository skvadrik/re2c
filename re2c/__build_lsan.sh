#!/bin/sh

builddir=__build_lsan
rm -rf $builddir
mkdir $builddir

cd $builddir
../configure --enable-debug CXXFLAGS="-fsanitize=leak" LDFLAGS="-fsanitize=leak" && \
make -j5
cd ..
