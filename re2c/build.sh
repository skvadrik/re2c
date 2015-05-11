#!/bin/sh

builddir=.build
rm -rf $builddir
mkdir $builddir

cd $builddir
../configure --enable-silent-rules && \
make -j5
cd ..
