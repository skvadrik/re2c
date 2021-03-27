#!/bin/bash

set -e

if [ $# -ne 1 ]
then
    echo "usage: ./distcheck.sh <builddir>"
    exit 1
fi
builddir="$1"

autoreconf -i -W all

# try to be portable on various MAKEs
for make_prog in make bmake
do
    rm -rf $builddir
    mkdir $builddir
    cd $builddir
    # 'make' implies 'make docs'; running both in parallel may cause data races
    # configure without --enable-debug, this is the release binary
    ../configure --enable-docs --enable-libs \
        && $make_prog bootstrap -j$(nproc) \
        && $make_prog distcheck -j$(nproc)
    cd ..
done

# test that the release tarball builds with CMake
cd $builddir
tarball=$(find . -name 're2c-*.tar.xz')
test -f "$tarball" && tar -xf "$tarball" \
    || { echo "*** failed to find tarball ***" && exit 1; }
cd "${tarball%.tar.xz}" && cmake . && make -j$(nproc) && cd .. \
    || { echo "*** failed to build with cmake ***" && exit 1; }
cd ..
