#!/bin/sh

builddir=__build_check_headers
rm -rf $builddir
mkdir $builddir

cd $builddir

cmake .. \
    -DCMAKE_BUILD_TYPE=Debug \
    -DRE2C_BUILD_LIBS=yes \
    && cmake --build . -j$(nproc)

for h in $(find ../src/ ../lib/ -name '*.h*'); do
    echo "CHECKING $h"
    g++ -I. -I.. -c $h -o foo.o || exit 1
done

rm -f foo.o

cd ..
