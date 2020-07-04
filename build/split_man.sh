if [ $# -ne 3 ]; then
    echo "usage: $0 <input> <output> <lang>"
    exit 1
fi

input="$1"
output="$2"
lang="$3"

case $lang in
    c) ext=h ;;
    go) ext=go ;;
    *) echo "*** $0: unknown lang: $lang"; exit 1 ;;
esac

LANG=C sed \
    -e "s/RE2C_LANG/$lang/g" \
    -e "s/RE2C_HEADER_EXT/$ext/g" \
    "$input" > "$output"
