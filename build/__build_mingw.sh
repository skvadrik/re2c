#!/bin/sh

builddir=__build_mingw
rm -rf $builddir
mkdir $builddir

cd $builddir
# '-static' tells libtool not to build shared libraries (DLLs)
# (they would be of no use anyway because libtool ignores '-static-libstdc++
# -static-libgcc' options and produces non-portable DLLs)
../configure LDFLAGS="-static -static-libstdc++ -static-libgcc" \
    --enable-debug \
    --enable-libs \
    --host i686-w64-mingw32 \
    && make -j$(nproc) \
    && ../build/copy_wine_libs_on_nixos.sh
cd ..
