set -e

if [ -e re2c ] ; then
    echo "re2c is already installed, quitting"
    exit 0
fi

RE2C_DIR=re2c-dev

mkdir re2c-dev \
    && cd "$RE2C_DIR" \
    && ../../../../../configure --enable-debug \
    && make -j$(nproc) \
    && cd ..

ln -s "$RE2C_DIR"/re2c re2c
