set -ex

if [ -e ragel7 ] ; then
    echo "ragel7 is already installed, quitting"
    exit 0
fi

COLM_DIR=colm-0.14.7
RAGEL_DIR=ragel-7.0.4

wget http://www.colm.net/files/colm/"$COLM_DIR".tar.gz -O - | tar zx \
    && cd "$COLM_DIR" \
    && sed -i 's|^#!/bin/bash|#!/usr/bin/env bash|' src/colm-wrap.sh \
    && ./configure \
        --prefix=$(pwd)/install \
        --disable-manual \
    && make -j$(nproc) \
    && make install \
    && cd ..

wget http://www.colm.net/files/ragel/"$RAGEL_DIR".tar.gz -O - | tar zx \
    && cd "$RAGEL_DIR" \
    && ./configure \
        --prefix=$(pwd)/install \
        --with-colm="$(pwd)/../$COLM_DIR/install" \
        --disable-manual \
    && make -j$(nproc) \
    && make install \
    && cd ..

ln -s "$RAGEL_DIR"/install/bin/ragel ragel7
