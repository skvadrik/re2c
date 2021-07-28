if [ $# -ne 3 ]; then
    echo "usage: $0 <input> <output> <lang>"
    exit 1
fi

input="$1"
output="$2"
lang="$3"

case $lang in
    c)  ext=h
        lang_name=C
        disclaimer=
        ;;
    go) ext=go
        lang_name=Go
        disclaimer="Note: This manual includes examples for Go, but it refers to re2c (rather than re2go) as the name of the program in general."
        ;;
    *)  echo "*** $0: unknown lang: $lang"
        exit 1
        ;;
esac

LANG=C sed \
    -e "s/RE2C_LANG_NAME/$lang_name/g" \
    -e "s/RE2C_LANG/$lang/g" \
    -e "s/RE2C_HEADER_EXT/$ext/g" \
    -e "s/RE2C_DISCLAIMER/$disclaimer/g" \
    "$input" > "$output"
