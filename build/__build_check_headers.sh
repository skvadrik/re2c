#!/bin/sh

builddir=__build_check_headers
rm -rf $builddir
mkdir $builddir

cd $builddir

../configure \
    --enable-debug \
    --enable-libs \
    && make -j$(nproc)

for h in $(find ../src/ ../lib/ -name '*.h*'); do
    echo "CHECKING $h"
    g++ -I. -I.. -c $h -o foo.o || exit 1
done

rm -f foo.o

cd ..
