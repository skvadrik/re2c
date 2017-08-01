#!/bin/sh

builddir=__build
rm -rf $builddir
mkdir $builddir

cd $builddir
../configure && \
make -j5
cd ..
