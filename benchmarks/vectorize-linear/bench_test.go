package linear_test

import (
	"encoding/json"
	"os"
	"strings"
	"testing"

	"re2c.local/vectorize-linear/generated"
)

type fixture struct {
	Name, Family string
	Records      []string
	Traces       [][][2]int
}

func load(tb testing.TB) []fixture {
	tb.Helper()
	data, err := os.ReadFile("generated/fixtures.json")
	if err != nil {
		tb.Fatal(err)
	}
	var fixtures []fixture
	if err := json.Unmarshal(data, &fixtures); err != nil {
		tb.Fatal(err)
	}
	for i := range fixtures {
		for j := range fixtures[i].Records {
			fixtures[i].Records[j] += strings.Repeat("\x00", 64)
		}
	}
	return fixtures
}

func scan(f fixture, lex func(string, int) (int, int)) uint64 {
	digest := uint64(14695981039346656037)
	for _, input := range f.Records {
		for pos := 0; ; {
			kind, next := lex(input, pos)
			if kind == 0 {
				break
			}
			digest = (digest ^ uint64(kind)) * 1099511628211
			digest = (digest ^ uint64(next-pos)) * 1099511628211
			pos = next
		}
	}
	return digest
}

func check(tb testing.TB, f fixture, v generated.Variant) {
	tb.Helper()
	for r, input := range f.Records {
		pos := 0
		for i, want := range f.Traces[r] {
			kind, next := v.Lex(input, pos)
			if kind != want[0] || next-pos != want[1] {
				tb.Fatalf("%s/%s record=%d token=%d: got (%d,%d), want %v", f.Name, v.Name, r, i, kind, next-pos, want)
			}
			pos = next
		}
		kind, next := v.Lex(input, pos)
		if kind != 0 || next != len(input)-64 || pos != next {
			tb.Fatalf("%s/%s record=%d: invalid end (%d,%d), pos=%d", f.Name, v.Name, r, kind, next, pos)
		}
	}
}

func TestTokenTraces(t *testing.T) {
	for _, f := range load(t) {
		for _, v := range generated.Variants {
			if f.Family == v.Family {
				t.Run(f.Name+"/"+v.Name, func(t *testing.T) { check(t, f, v) })
			}
		}
	}
}

var sink uint64

func BenchmarkLinear(b *testing.B) {
	for _, f := range load(b) {
		for _, v := range generated.Variants {
			if f.Family != v.Family || strings.HasSuffix(f.Name, "_edges") {
				continue
			}
			b.Run(f.Name+"/"+v.Name, func(b *testing.B) {
				check(b, f, v)
				var size int64
				for _, input := range f.Records {
					size += int64(len(input) - 64)
				}
				b.SetBytes(size)
				b.ReportAllocs()
				want := scan(f, v.Lex)
				for b.Loop() {
					sink = scan(f, v.Lex)
					if sink != want {
						b.Fatal("digest mismatch")
					}
				}
			})
		}
	}
}
