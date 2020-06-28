
> "$2"
echo "extern const char *help;" >> "$2"
echo "const char *help =" >> "$2"
MANPAGER=cat MANWIDTH=100 man "$1" \
    | tail -n +6 \
    | head -n -1 \
    | sed -E -e 's/\x1b\x5b[0-9]+m//g' \
    | sed 's/\\x/\\\\x/g' \
    | sed -E 's/"/\\"/g' \
    | sed -E 's/(.*)/"\1\\n"/' \
    >> "$2"
echo ";" >> "$2"
