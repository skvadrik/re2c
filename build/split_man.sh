if [ $# -ne 3 ]; then
    echo "usage: $0 <input> <output> <lang>"
    exit 1
fi

input="$1"
output="$2"
lang="$3"

case $lang in
    c)
        src_ext=c
        hdr_ext=h
        lang_name=C
        disclaimer="Note: examples are in C++ (but can be easily adapted to C)."
        ;;
    go)
        src_ext=go
        hdr_ext=go
        lang_name=Go
        disclaimer="Note: This manual is for Go, but it refers to re2c as the general program."
        ;;
    rust)
        src_ext=rs
        hdr_ext=rs
        lang_name=Rust
        disclaimer="Note: This manual is for Rust, but it refers to re2c as the general program."
        ;;
    *)
        echo "*** $0: unknown lang: $lang"
        exit 1
        ;;
esac

LANG=C sed \
    -e "s/RE2C_LANG_NAME/$lang_name/g" \
    -e "s/RE2C_LANG/$lang/g" \
    -e "s/RE2C_SOURCE_EXT/$src_ext/g" \
    -e "s/RE2C_HEADER_EXT/$hdr_ext/g" \
    -e "s/RE2C_DISCLAIMER/$disclaimer/g" \
    "$input" > "$output"
