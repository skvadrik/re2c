#!/bin/sh

builddir=__build_asan
rm -rf $builddir
mkdir $builddir

cd $builddir
../configure CXXFLAGS="-fsanitize=address" LDFLAGS="-fsanitize=address" && \
make -j5
cd ..
