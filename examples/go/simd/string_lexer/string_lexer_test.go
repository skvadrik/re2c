//go:build goexperiment.simd && amd64

package main

import (
	"bytes"
	"go/ast"
	"go/parser"
	"go/token"
	"math/rand/v2"
	"simd/archsimd"
	"strconv"
	"strings"
	"testing"
)

func requireAVX2(tb testing.TB) {
	tb.Helper()
	if !archsimd.X86.AVX2() {
		tb.Skip("AVX2 is not available")
	}
}

// referenceLexString is a hand-written reference implementation used to
// cross-check both generated lexers.
func referenceLexString(s []byte) int {
	if len(s) == 0 || s[0] != '"' {
		return -1
	}
	for i := 1; i < len(s); i++ {
		switch s[i] {
		case '"':
			return i - 1
		case 0, '\n', '\r':
			return -1
		case '\\':
			i++
			if i >= len(s) {
				return -1
			}
			switch s[i] {
			case '\\', '"', '/', 'b', 'f', 'n', 'r', 't':
			default:
				return -1
			}
		}
	}
	return -1
}

func checkParity(t *testing.T, s []byte) {
	t.Helper()
	want := referenceLexString(s)
	if got := LexStringScalar(s); got != want {
		t.Fatalf("LexStringScalar(%q) = %d, want %d", s, got, want)
	}
	if got := LexStringSIMD(s); got != want {
		t.Fatalf("LexStringSIMD(%q) = %d, want %d", s, got, want)
	}
}

// checkParityPadded checks the input both as is and followed by padding, so
// that short strings also run through the vector loop (its length guard
// depends on the size of the whole buffer, not on the size of the string).
func checkParityPadded(t *testing.T, s []byte) {
	t.Helper()
	checkParity(t, s)
	padded := append(append([]byte(nil), s...), strings.Repeat("p", 64)...)
	checkParity(t, padded)
}

func TestParityFixed(t *testing.T) {
	requireAVX2(t)
	tests := []string{
		`""`,
		`"short"`,
		`"` + strings.Repeat("A", 31) + `"`,
		`"` + strings.Repeat("B", 32) + `"`,
		`"` + strings.Repeat("C", 256) + `"`,
		`"text with \n and \"quotes\" and \t end"`,
		`"` + strings.Repeat("X", 31) + `\"` + strings.Repeat("Y", 31) + `"`,
		"\"text before \n after\"",
		"\"unterminated string with a sentinel\x00",
		`"unterminated`,
		`"trailing backslash\`,
		`no opening quote"`,
		``,
	}
	for _, s := range tests {
		checkParityPadded(t, []byte(s))
	}
}

// TestParityBoundaries places every interesting byte at every position of
// strings of every length around the 32-byte vector width.
func TestParityBoundaries(t *testing.T) {
	requireAVX2(t)
	special := []string{"\"", "\\", "\x00", "\n", "\r", "\\n", "\\\"", "\\\\", "\\x", "\x01", "!", "#", "[", "]", "\x7f", "\x80", "\xff"}
	for n := 0; n <= 140; n++ {
		body := bytes.Repeat([]byte{'x'}, n)
		checkParityPadded(t, append(append([]byte{'"'}, body...), '"'))
		checkParityPadded(t, append([]byte{'"'}, body...))
		for p := 0; p <= n; p++ {
			for _, c := range special {
				s := []byte{'"'}
				s = append(s, body[:p]...)
				s = append(s, c...)
				s = append(s, body[p:]...)
				checkParityPadded(t, s)
				checkParityPadded(t, append(s, '"'))
			}
		}
	}
}

func randomString(r *rand.Rand, maxLen int) []byte {
	// Mostly ordinary bytes, with a small share of the bytes that stop the
	// fast-forward loop (quote, backslash, NUL, LF, CR).
	const ordinary = "abcdefghijklmnopqrstuvwxyz0123456789 !#$%&'()*+,-./:;<=>?@[]^_`{|}~\x01\x7f\x80\xc3\xa9\xff"
	const escapes = "\\\"/bfnrtux"
	n := r.IntN(maxLen + 1)
	s := make([]byte, 0, n+2)
	s = append(s, '"')
	for len(s) <= n {
		switch k := r.IntN(100); {
		case k < 2:
			s = append(s, '\\', escapes[r.IntN(len(escapes))])
		case k == 2 && r.IntN(4) == 0:
			s = append(s, "\x00\n\r"[r.IntN(3)])
		default:
			s = append(s, ordinary[r.IntN(len(ordinary))])
		}
	}
	if r.IntN(10) != 0 {
		s = append(s, '"')
	}
	return s
}

func TestParityRandom(t *testing.T) {
	requireAVX2(t)
	r := rand.New(rand.NewPCG(411, 585))
	for i := 0; i < 200000; i++ {
		checkParityPadded(t, randomString(r, 300))
	}
}

func FuzzParity(f *testing.F) {
	requireAVX2(f)
	r := rand.New(rand.NewPCG(1, 2))
	for i := 0; i < 64; i++ {
		f.Add(randomString(r, 200))
	}
	f.Fuzz(func(t *testing.T, s []byte) {
		checkParityPadded(t, s)
	})
}

// TestScalarBaselineIsNotVectorized checks the generated code: the SIMD lexer
// must contain the vector loop and the scalar baseline must not.
func TestScalarBaselineIsNotVectorized(t *testing.T) {
	file, err := parser.ParseFile(token.NewFileSet(), "string_lexer.go", nil, 0)
	if err != nil {
		t.Fatal(err)
	}
	usesSIMD := map[string]bool{}
	for _, decl := range file.Decls {
		fn, ok := decl.(*ast.FuncDecl)
		if !ok {
			continue
		}
		ast.Inspect(fn, func(n ast.Node) bool {
			if id, ok := n.(*ast.Ident); ok && id.Name == "archsimd" {
				usesSIMD[fn.Name.Name] = true
			}
			return true
		})
	}
	if !usesSIMD["LexStringSIMD"] {
		t.Error("LexStringSIMD does not contain a vector loop")
	}
	if usesSIMD["LexStringScalar"] {
		t.Error("LexStringScalar contains a vector loop")
	}
}

func TestZeroAllocs(t *testing.T) {
	requireAVX2(t)
	s := []byte(`"` + strings.Repeat("abcdefgh", 100) + `"`)
	if n := testing.AllocsPerRun(1000, func() { LexStringSIMD(s) }); n != 0 {
		t.Fatalf("LexStringSIMD allocates: %v allocs/op", n)
	}
}

// Benchmarks.
//
// Each regime is a corpus of string literals stored back to back in a single
// buffer (separated by a comma), as a lexer would see them in a JSON document.
// Throughput is measured in bytes of string literals (quotes included).
//
// With "inbuf" slicing each string is lexed from its start to the end of the
// whole buffer, so the vector loop length guard passes and the loop has to
// find the closing quote. With "isolated" slicing each string is lexed as a
// slice of its own, so strings shorter than the guard (33 bytes) never enter
// the vector loop.

type corpus struct {
	buf    []byte
	starts []int
	ends   []int
	bytes  int64
}

func (c *corpus) add(body string) {
	c.buf = append(c.buf, ',')
	c.starts = append(c.starts, len(c.buf))
	c.buf = append(c.buf, '"')
	c.buf = append(c.buf, body...)
	c.buf = append(c.buf, '"')
	c.ends = append(c.ends, len(c.buf))
	c.bytes += int64(len(body) + 2)
}

const letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"

func text(r *rand.Rand, n int, escapeEvery int) string {
	const words = "the quick brown fox jumps over lazy dog lorem ipsum dolor sit amet réseau naïve 東京 "
	var sb strings.Builder
	for sb.Len() < n {
		if escapeEvery > 0 && r.IntN(escapeEvery) == 0 {
			sb.WriteString([]string{`\n`, `\"`, `\\`, `\t`, `\/`}[r.IntN(5)])
			continue
		}
		sb.WriteByte(words[r.IntN(len(words))])
	}
	return sb.String()
}

func ident(r *rand.Rand, n int) string {
	b := make([]byte, n)
	for i := range b {
		b[i] = letters[r.IntN(len(letters))]
	}
	return string(b)
}

type regime struct {
	name     string
	isolated bool
	corpus   *corpus
}

func regimes() []regime {
	r := rand.New(rand.NewPCG(411, 585))
	const target = 1 << 20 // about 1 MiB of string literals per regime

	short := &corpus{}
	for short.bytes < target {
		short.add(ident(r, r.IntN(31))) // 0..30 bytes: below the 33-byte guard
	}
	medium := &corpus{}
	for medium.bytes < target {
		medium.add(text(r, 32+r.IntN(225), 0)) // 32..256 bytes
	}
	long := &corpus{}
	for long.bytes < target {
		long.add(text(r, 4096, 0))
	}
	huge := &corpus{}
	huge.add(strings.Repeat(strings.Repeat("Champ_Donnees_Pour_Benchmark_SIMD_1234567890_", 20), 1000))
	escapes := &corpus{}
	for escapes.bytes < target {
		escapes.add(text(r, 64+r.IntN(193), 6)) // an escape every ~6 bytes
	}
	mix := &corpus{}
	for mix.bytes < target {
		switch k := r.IntN(100); {
		case k < 60: // object keys
			mix.add(ident(r, 2+r.IntN(15)))
		case k < 85: // short text values
			mix.add(text(r, 16+r.IntN(105), 40))
		case k < 95: // longer prose
			mix.add(text(r, 200+r.IntN(801), 80))
		default: // base64-like blobs
			mix.add(ident(r, 1024+r.IntN(3073)))
		}
	}
	result := []regime{
		{"short-isolated", true, short},
		{"short-inbuf", false, short},
		{"medium", false, medium},
		{"long", false, long},
		{"huge", false, huge},
		{"escapes", false, escapes},
		{"mix-isolated", true, mix},
		{"mix-inbuf", false, mix},
	}
	// The LCG and periodic escape positions match the C vec-regime benchmarks.
	for _, n := range []int{0, 1, 2, 3, 4, 5, 6, 7, 8, 16, 24, 31, 32, 33, 64, 256, -1, 1024} {
		periods := []int{0}
		if n == 1024 {
			periods = []int{8, 32, 64}
		}
		for _, k := range periods {
			c := &corpus{}
			seed := uint32(585)
			for i := 0; i < 4096; i++ {
				length := n
				if n < 0 {
					length = i % 66
				}
				body := make([]byte, 0, length)
				for j := 0; j < length; j++ {
					seed = seed*1664525 + 1013904223
					if k > 0 && j%k == k-2 {
						body = append(body, '\\', 'n')
						j++
					} else {
						body = append(body, 'a'+byte((seed>>24)%26))
					}
				}
				c.add(string(body))
			}
			name := "fixed" + strconv.Itoa(n)
			if k > 0 {
				name = "escape" + strconv.Itoa(k)
			}
			if n < 0 {
				result = append(result, regime{"end-buffer", true, c})
				name = "stream"
			}
			result = append(result, regime{name, false, c})
		}
	}
	return result
}

func lexAll(lex func([]byte) int, re *regime) int {
	c := re.corpus
	sum := 0
	for i, start := range c.starts {
		end := len(c.buf)
		if re.isolated {
			end = c.ends[i]
		}
		sum += lex(c.buf[start:end])
	}
	return sum
}

func TestBenchmarkRegimes(t *testing.T) {
	first, second := regimes(), regimes()
	if len(first) != 29 || len(second) != len(first) {
		t.Fatalf("regime counts: got %d and %d, want 29", len(first), len(second))
	}
	for index, re := range first {
		t.Run(re.name, func(t *testing.T) {
			c := re.corpus
			if !bytes.Equal(c.buf, second[index].corpus.buf) {
				t.Fatal("corpus generation is not deterministic")
			}
			if index < 8 {
				return // Existing variable-length distributions.
			}
			if len(c.starts) != 4096 || len(c.ends) != 4096 {
				t.Fatal("expected 4096 literals")
			}
			n, k := -1, 0
			var err error
			if strings.HasPrefix(re.name, "fixed") {
				n, err = strconv.Atoi(strings.TrimPrefix(re.name, "fixed"))
			} else if strings.HasPrefix(re.name, "escape") {
				k, err = strconv.Atoi(strings.TrimPrefix(re.name, "escape"))
				n = 1024
			}
			if err != nil {
				t.Fatal(err)
			}
			var size int64
			for i, start := range c.starts {
				input := c.buf[start:c.ends[i]]
				want := n
				if n < 0 {
					want = i % 66
				}
				if len(input) != want+2 || referenceLexString(input) != want {
					t.Fatalf("literal %d: expected valid body of %d bytes", i, want)
				}
				for j, value := range input[1 : len(input)-1] {
					expectedEscape := k > 0 && j%k == k-2
					if (value == '\\') != expectedEscape {
						t.Fatalf("literal %d: wrong escape position %d", i, j)
					}
				}
				size += int64(len(input))
			}
			if size != c.bytes {
				t.Fatalf("byte count: got %d, want %d", c.bytes, size)
			}
		})
	}
}

var sink int

func BenchmarkLexString(b *testing.B) {
	requireAVX2(b)
	impls := []struct {
		name string
		lex  func([]byte) int
	}{
		{"scalar", LexStringScalar},
		{"simd", LexStringSIMD},
	}
	for _, re := range regimes() {
		want := lexAll(referenceLexString, &re)
		for _, impl := range impls {
			b.Run("regime="+re.name+"/impl="+impl.name, func(b *testing.B) {
				for i, start := range re.corpus.starts {
					end := len(re.corpus.buf)
					if re.isolated {
						end = re.corpus.ends[i]
					}
					input := re.corpus.buf[start:end]
					if got, want := impl.lex(input), referenceLexString(input); got != want {
						b.Fatalf("literal %d: got %d, want %d", i, got, want)
					}
				}
				// Every string in the corpus is valid, so the sum of the
				// lengths is a checksum of the work actually done.
				if got := lexAll(impl.lex, &re); got != want {
					b.Fatalf("checksum mismatch: got %d, want %d", got, want)
				}
				b.SetBytes(re.corpus.bytes)
				s := 0
				for b.Loop() {
					s = lexAll(impl.lex, &re)
					if s != want {
						b.Fatalf("timed pass: got %d, want %d", s, want)
					}
				}
				sink = s
			})
		}
	}
}
