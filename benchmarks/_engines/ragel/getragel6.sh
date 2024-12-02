set -e

if [ -e ragel6 ] ; then
    echo "ragel6 is already installed, quitting"
    exit 0
fi

RAGEL_DIR=ragel-6.10

wget http://www.colm.net/files/ragel/"$RAGEL_DIR".tar.gz -O - | tar zx \
    && cd "$RAGEL_DIR" \
    && ./configure --prefix=$(pwd)/install \
    && make -j$(nproc) \
    && cd ..

ln -s "$RAGEL_DIR"/ragel/ragel ragel6
