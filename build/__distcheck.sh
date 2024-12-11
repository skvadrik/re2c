#!/bin/sh

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
    rm -rf "$builddir"
    mkdir "$builddir"
    cd "$builddir"

    # stage 1
    mkdir stage1
    ../configure --prefix "$(pwd)/stage1" \
        && $make_prog -j"$(nproc)" \
        && $make_prog install

    # stage 2
    # 'make' implies 'make docs'; running both in parallel may cause data races
    # configure without --enable-debug, this is the release binary
    ../configure \
            --enable-docs \
            --enable-libs \
            --enable-syntax \
            --enable-lexers RE2C_FOR_BUILD="$(pwd)/stage1/bin/re2c" \
        && $make_prog bootstrap -j"$(nproc)" \
        && $make_prog distcheck -j"$(nproc)"
    cd ..
done

cd "$builddir"
tarball=$(find . -name 're2c-*.tar.xz')
test -f "$tarball" && tar -xf "$tarball" \
    || { echo "*** failed to extract tarball ***" && exit 1; }

# test `make docs` in release tarball
cd "${tarball%.tar.xz}" && ./configure --enable-docs && make -j"$(nproc)" && make clean && cd .. \
    || { echo "*** failed to build docs ***" && exit 1; }

# test that the release tarball builds with CMake
cd "${tarball%.tar.xz}" && cmake . && make -j"$(nproc)" && cd .. \
    || { echo "*** failed to build with cmake ***" && exit 1; }

cd ..
