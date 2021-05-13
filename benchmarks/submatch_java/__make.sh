set -e

LIBRE2C_INCLUDE_PATH=../../lib
LIBRE2C_SOURCE_PATH=./libre2c

if [ -z "$LIBRE2C_LIBRARY_PATH" ]; then
    echo "LIBRE2C_LIBRARY_PATH must be set to a directory containing libre2c.so"
    exit 1
fi

builddir=_build
mkdir -p "$builddir"

# Generate header for libre2c_jni.
javac -d "$builddir" -h "$builddir" "$LIBRE2C_SOURCE_PATH"/RE2C.java

# Build libre2c_jni.
g++ -fPIC -Wall -O3 -g -shared \
    -I"$JAVA_HOME/include" \
    -I"$JAVA_HOME/include/linux" \
    -I"$LIBRE2C_INCLUDE_PATH" \
    -I"$builddir" \
    -L"$LIBRE2C_LIBRARY_PATH" -lre2c \
    -o "$builddir"/libre2c_jni.so \
    "$LIBRE2C_SOURCE_PATH"/RE2C.cpp

# Run libre2c_jni tests.
LD_LIBRARY_PATH="$LIBRE2C_LIBRARY_PATH" \
java \
    -Djava.library.path="$builddir" \
    -cp "$builddir" \
    re2c.RE2C

# Compile ReTdfa.
javac \
    -d "$builddir" \
    -encoding UTF8 \
    -cp "$builddir" \
    ReTdfa.java

# Run ReTdfa.
command=(
    taskset --cpu-list 1
    java
    -Dfile.encoding=UTF8
    -Djava.library.path="$builddir"
    -cp .:"$builddir"
    -Xmx1000m
    -Xss10m
    ReTdfa
)
LD_LIBRARY_PATH=".:$LIBRE2C_LIBRARY_PATH" ${command[@]}

