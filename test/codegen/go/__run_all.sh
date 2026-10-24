here=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)

guard_vet() {
    label=$1
    src=$2
    need=$3
    dir=$(mktemp -d) || { echo "guard: cannot create a temporary directory"; return 1; }
    if [ ! -d "$dir" ]; then
        echo "guard: temporary directory was not created"
        return 1
    fi
    cp "$src" "$dir/lex.go"
    printf 'module example.com/%s\ngo 1.24\n' "$label" > "$dir/go.mod"
    printf 'package main\nimport "testing"\nfunc TestGuard(t *testing.T) {}\n' > "$dir/lex_test.go"
    if ! grep -F -q -- "$need" "$dir/lex.go"; then
        echo "guard: $label missing pattern $need"
        rm -rf "$dir"
        return 1
    fi
    if ! test_out=$(cd "$dir" && GOWORK=off go test -count=1 -buildvcs=false -run TestGuard . 2>&1); then
        echo "guard: $label go test failed"
        printf '%s\n' "$test_out"
        rm -rf "$dir"
        return 1
    fi
    if ! vet_out=$(cd "$dir" && GOWORK=off go vet -buildvcs=false . 2>&1); then
        echo "guard: $label go vet failed"
        printf '%s\n' "$vet_out"
        rm -rf "$dir"
        return 1
    fi
    if [ -n "$vet_out" ]; then
        echo "guard: $label go vet not silent"
        printf '%s\n' "$vet_out"
        rm -rf "$dir"
        return 1
    fi
    echo "guard: $label go test passed; go vet silent"
    rm -rf "$dir"
}

guard_width() {
    src=$1
    dir=$(mktemp -d) || { echo "guard: cannot create a temporary directory"; return 1; }
    if [ ! -d "$dir" ]; then
        echo "guard: temporary directory was not created"
        return 1
    fi
    cp "$src" "$dir/lex.go"
    printf 'module example.com/width\ngo 1.24\n' > "$dir/go.mod"
    if ! grep -q 'type byte = uint16' "$dir/lex.go"; then
        echo "guard: width source missing shadowed byte"
        rm -rf "$dir"
        return 1
    fi
    if build_out=$(cd "$dir" && GOWORK=off go build -buildvcs=false -o /dev/null . 2>&1); then
        echo "guard: width compiled, expected failure"
        rm -rf "$dir"
        return 1
    fi
    case "$build_out" in
        *index*)
            echo "guard: width refused at compilation"
            printf '%s\n' "$build_out"
            ;;
        *)
            echo "guard: width failed without an index diagnostic"
            printf '%s\n' "$build_out"
            rm -rf "$dir"
            return 1
            ;;
    esac
    rm -rf "$dir"
}

guard_check() {
    status=0
    guard_vet byte "$here/vectorize_linear_basic.go" 'int(^uint8(0))>>8+int(^byte(0))>>8' || status=1
    guard_vet uint8 "$here/vectorize_linear_conversion_parity.go" 'int(^uint8(0))>>8+int(^uint8(0))>>8' || status=1
    guard_width "$here/vectorize_linear_width.go" || status=1
    if [ "$status" -ne 0 ]; then
        echo "guard: FAILED"
        return 1
    fi
    echo "guard: PASSED"
}

if [ "${1:-}" = "--guard" ]; then
    guard_check
    exit $?
fi

root_dir=$(pwd)

for f in $(find -name '*.re'); do
    grep -q 'func main' $f || continue # skip incomplete tests
    case $(basename "$f") in
        vectorize_linear_width.re|vectorize_linear_generic.re) continue ;;
    esac

    echo $f
    cd $(dirname $f)

    cat $(basename ${f%.re}.go) \
        | egrep -v 'warning: rule .*matches empty string \[-Wmatch-empty-string\]' \
        | egrep -v 'warning: tag .* degree of nondeterminism \[-Wnondeterministic-tags\]' \
        > x.go


    go run x.go >/dev/null || { echo "*** error ***"; exit 1; }

    rm -f x.go
    cd $root_dir
done

echo "All good."
guard_check
