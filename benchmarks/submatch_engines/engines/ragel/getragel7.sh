set -e

if [ -e ragel7 ] ; then
    echo "ragel7 is already installed, quitting"
    exit 0
fi

COLM_DIR=colm-0.13.0.7
RAGEL_DIR=ragel-7.0.0.12

wget http://www.colm.net/files/colm/"$COLM_DIR".tar.gz -O - | tar zx \
    && cd "$COLM_DIR" \
    && ./configure --prefix=$(pwd)/install \
    && make -j$(nproc) \
    && make install \
    && cd ..

wget http://www.colm.net/files/ragel/"$RAGEL_DIR".tar.gz -O - | tar zx \
    && cd "$RAGEL_DIR" \
    && ./configure --prefix=$(pwd)/install --with-colm="$(pwd)/../$COLM_DIR/install" \
    && make -j$(nproc) \
    && make install \
    && cd ..

ln -s "$RAGEL_DIR"/install/bin/ragel ragel7
