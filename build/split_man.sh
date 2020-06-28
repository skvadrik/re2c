if [ $# -ne 3 ]; then
    echo "usage: $0 <input> <output> <lang>"
    exit 1
fi

input="$1"
output="$2"
lang="$3"

LANG=C sed "s/RE2C_LANG/$lang/g" "$input" > "$output"
