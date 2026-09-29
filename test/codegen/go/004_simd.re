//go:generate re2go --vectorize-loops $INPUT -o $OUTPUT
package main

import (
	"fmt"
	"math/rand"
	"simd/archsimd"
)

var (
	input  []byte
	cursor int
	limit  int
	marker int
)

func fill(need int) int { return 0 }

func lexSimd() int {
	/*!re2c
	re2c:vectorize:loops = 1;
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYCURSOR = cursor;
	re2c:YYLIMIT = limit;
	re2c:YYINPUT = input;
	re2c:YYMARKER = marker;
	re2c:YYFILL = "fill(0)";
	re2c:YYFILL:naked = 1;

	[0-9]+      { return 1 }
	[a-zA-Z_][a-zA-Z0-9_]* { return 2 }
	[ \t]+      { return 3 }
	"\x00"      { return 0 }
	*           { return -1 }
	*/
}

func lexScalar() int {
	/*!re2c
	re2c:vectorize:loops = 0;
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:YYCURSOR = cursor;
	re2c:YYLIMIT = limit;
	re2c:YYINPUT = input;
	re2c:YYMARKER = marker;
	re2c:YYFILL = "fill(0)";
	re2c:YYFILL:naked = 1;

	[0-9]+      { return 1 }
	[a-zA-Z_][a-zA-Z0-9_]* { return 2 }
	[ \t]+      { return 3 }
	"\x00"      { return 0 }
	*           { return -1 }
	*/
}

func lexAll(lex func() int, data []byte) (tokens []int, spans []int) {
	buf := make([]byte, len(data)+128)
	copy(buf, data)
	input, cursor, limit, marker = buf, 0, len(buf), 0
	for {
		start := cursor
		tok := lex()
		tokens = append(tokens, tok)
		spans = append(spans, cursor-start)
		if tok == 0 || tok == -1 {
			return
		}
	}
}

func main() {
	alphabet := "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_ \t"
	rng := rand.New(rand.NewSource(411))
	check := func(b []byte) {
		t1, s1 := lexAll(lexSimd, b)
		t2, s2 := lexAll(lexScalar, b)
		if len(t1) != len(t2) {
			panic(fmt.Sprintf("token count mismatch on %q", string(b)))
		}
		for k := range t1 {
			if t1[k] != t2[k] || s1[k] != s2[k] {
				panic(fmt.Sprintf("mismatch on %q at token %d: simd=(%d,%d) scalar=(%d,%d)",
					string(b), k, t1[k], s1[k], t2[k], s2[k]))
			}
		}
	}
	// Boundary-focused: pure runs of every length around the 32-byte vector width, plus
	// alternating patterns that force repeated SIMD/scalar hand-off.
	checked := 0
	for _, cls := range []byte{'0', 'a', ' ', '\t', '_'} {
		for n := 0; n <= 200; n++ {
			b := make([]byte, n)
			for j := range b {
				b[j] = cls
			}
			check(b)
			checked++
		}
	}
	for n := 1; n <= 200; n++ {
		b := make([]byte, 0, n)
		for j := 0; j < n; j++ {
			if j%2 == 0 {
				b = append(b, '7')
			} else {
				b = append(b, 'x')
			}
		}
		check(b)
		for j := 0; j < n; j++ {
			switch j % 3 {
			case 0:
				b[j] = '7'
			case 1:
				b[j] = ' '
			default:
				b[j] = 'x'
			}
		}
		check(b)
		checked += 2
	}
	for i := 0; i < 5000; i++ {
		n := rng.Intn(300)
		var b []byte
		for j := 0; j < n; j++ {
			b = append(b, alphabet[rng.Intn(len(alphabet))])
		}
		check(b)
		checked++
	}
	fmt.Printf("OK: %d inputs bit-exact\n", checked)
}
