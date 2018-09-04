#!/bin/sh

builddir=__build_clang
rm -rf $builddir
mkdir $builddir

cd $builddir
../configure CC=clang CXX=clang++ && \
make -j5
cd ..
