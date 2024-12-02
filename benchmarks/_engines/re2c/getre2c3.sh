set -ex

if [ -e re2c3 ] ; then
    echo "re2c3 is already installed, quitting"
    exit 0
fi

RE2C_DIR=re2c-3.0

wget https://github.com/skvadrik/re2c/releases/download/3.0/re2c-3.0.tar.xz \
    && tar xf re2c-3.0.tar.xz \
    && rm re2c-3.0.tar.xz \
    && cd "$RE2C_DIR" \
    && ./configure \
        --disable-golang \
        --disable-rust \
        --prefix=$(pwd)/install \
    && make -j$(nproc) \
    && make install \
    && cd ..

ln -s "$RE2C_DIR"/install/bin/re2c re2c3
