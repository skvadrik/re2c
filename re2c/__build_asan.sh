#!/bin/sh

builddir=__build_asan
rm -rf $builddir
mkdir $builddir

cd $builddir
../configure --enable-debug CXXFLAGS="-fsanitize=address" LDFLAGS="-fsanitize=address" && \
make -j5
cd ..
