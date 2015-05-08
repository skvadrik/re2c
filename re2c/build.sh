#!/bin/sh

builddir=.build
rm -rf $builddir
mkdir $builddir

cd $builddir
../configure --enable-docs --enable-silent-rules && \
make bootstrap -j5
cd ..
