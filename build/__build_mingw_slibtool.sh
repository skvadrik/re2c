#!/bin/sh

builddir=__build_mingw_slibtool
rm -rf $builddir
mkdir $builddir

cd $builddir
# slibtool fails to build final EXEs because of symbol collisions:
# libre2c is statically linked with libgcc, and slibtool passes -lre2c
# before some object file that also contains definitions from libgcc
#
# however, slibtool manages to correctly build self-contained libre2c.dll
# (unlike libtool, which ignores '-static-libstdc++ -static-libgcc' and
# produces non-portable DLL)
../configure LDFLAGS="-static-libstdc++ -static-libgcc" \
    --enable-debug \
    --enable-libs \
    --host i686-w64-mingw32 \
    && make -j$(nproc) LIBTOOL="slibtool" \
    && ../build/copy_wine_libs_on_nixos.sh
cd ..
