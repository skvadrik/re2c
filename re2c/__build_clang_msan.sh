#!/bin/sh

builddir=__build_clang_msan
rm -rf $builddir
mkdir $builddir

cd $builddir
../configure CC=clang CXX=clang++ CFLAGS="-fsanitize=memory" CXXFLAGS="-fsanitize=memory" LDFLAGS="-fsanitize=memory" && \
make -j5
cd ..
