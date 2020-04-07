#!/bin/sh

builddir=__build_mingw
rm -rf $builddir
mkdir $builddir

cd $builddir
cmake .. \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DRE2C_BUILD_LIBS=yes \
    -DBUILD_SHARED_LIBS=no \
    -DCMAKE_EXE_LINKER_FLAGS="-static -static-libstdc++ -static-libgcc" \
    -DCMAKE_TOOLCHAIN_FILE=cmake/Toolchain-cross-mingw32-linux.cmake \
    && cmake --build . -j$(nproc)
cd ..
