#!/bin/sh

builddir=__build_iwyu
rm -rf $builddir
mkdir $builddir

cd $builddir
cmake .. \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_CXX_FLAGS="-O2" \
    -DRE2C_BUILD_LIBS=yes \
    -DCMAKE_CXX_INCLUDE_WHAT_YOU_USE="include-what-you-use;-Xiwyu;--check_also='*.re';-Xiwyu;--check_also='*.y';-Xiwyu;--no_comments" \
    && cmake --build . -j$(nproc) 2>log
cd ..
