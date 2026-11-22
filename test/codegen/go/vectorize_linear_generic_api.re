//go:generate re2go $INPUT -o $OUTPUT -i --api generic
package main

import "fmt"

type opaqueStream struct {
	raw   string
	idx   int
	end   int
	saved int
}

var (
	widePeeks2 int
	widePeeks4 int
	widePeeks8 int
)

func (s *opaqueStream) peek2() uint16 {
	widePeeks2++
	return uint16(s.raw[s.idx]) | uint16(s.raw[s.idx+1])<<8
}

func (s *opaqueStream) peek4() uint32 {
	widePeeks4++
	return uint32(s.raw[s.idx]) |
		uint32(s.raw[s.idx+1])<<8 |
		uint32(s.raw[s.idx+2])<<16 |
		uint32(s.raw[s.idx+3])<<24
}

func (s *opaqueStream) peek8() uint64 {
	widePeeks8++
	return uint64(s.raw[s.idx]) |
		uint64(s.raw[s.idx+1])<<8 |
		uint64(s.raw[s.idx+2])<<16 |
		uint64(s.raw[s.idx+3])<<24 |
		uint64(s.raw[s.idx+4])<<32 |
		uint64(s.raw[s.idx+5])<<40 |
		uint64(s.raw[s.idx+6])<<48 |
		uint64(s.raw[s.idx+7])<<56
}

func (s *opaqueStream) peek1() byte {
	if s.idx < s.end {
		return s.raw[s.idx]
	}
	return 0
}

/*!rules:re2c:headers
	"ok:"                { return 1, s.idx }
	"date:"              { return 2, s.idx }
	"content-length:"    { return 3, s.idx }
	"content-type:"      { return 4, s.idx }
	"transfer-encoding:" { return 5, s.idx }
	"connection:"        { return 6, s.idx }
	[a-z-]+ ":"          { return 7, s.idx }
	*                    { return 0, s.idx }
*/

func lexFnScalar(buf string) (int, int) {
	s := opaqueStream{raw: buf, end: len(buf)}
	YYPEEK := func() byte { return s.peek1() }
	YYSKIP := func() { s.idx++ }
	YYBACKUP := func() { s.saved = s.idx }
	YYRESTORE := func() { s.idx = s.saved }
	/*!local:re2c
		re2c:api:style = functions;
		re2c:YYCTYPE = byte;
		re2c:yyfill:enable = 0;
		re2c:vectorize:linear = 0;
		!use:headers;
	*/
}

func lexFnLinear(buf string) (int, int) {
	s := opaqueStream{raw: buf, end: len(buf)}
	YYPEEK := func() byte { return s.peek1() }
	YYPEEK2 := func() uint16 { return s.peek2() }
	YYPEEK4 := func() uint32 { return s.peek4() }
	YYPEEK8 := func() uint64 { return s.peek8() }
	YYSKIP := func() { s.idx++ }
	YYBACKUP := func() { s.saved = s.idx }
	YYRESTORE := func() { s.idx = s.saved }
	YYLESSTHAN := func(n int) bool { return (s.end - s.idx) < n }
	YYSHIFT := func(n int) { s.idx += n }
	/*!local:re2c
		re2c:api:style = functions;
		re2c:YYCTYPE = byte;
		re2c:yyfill:enable = 0;
		re2c:YYLESSTHAN = YYLESSTHAN;
		re2c:vectorize:linear = 1;
		!use:headers;
	*/
}

func lexFfScalar(buf string) (int, int) {
	s := opaqueStream{raw: buf, end: len(buf)}
	/*!local:re2c
		re2c:api:style = free-form;
		re2c:YYCTYPE = byte;
		re2c:YYPEEK = "s.peek1()";
		re2c:YYSKIP = "s.idx++";
		re2c:YYBACKUP = "s.saved = s.idx";
		re2c:YYRESTORE = "s.idx = s.saved";
		re2c:yyfill:enable = 0;
		re2c:vectorize:linear = 0;
		!use:headers;
	*/
}

func lexFfLinear(buf string) (int, int) {
	s := opaqueStream{raw: buf, end: len(buf)}
	/*!local:re2c
		re2c:api:style = free-form;
		re2c:YYCTYPE = byte;
		re2c:YYPEEK = "s.peek1()";
		re2c:YYPEEK2 = "s.peek2()";
		re2c:YYPEEK4 = "s.peek4()";
		re2c:YYPEEK8 = "s.peek8()";
		re2c:YYSKIP = "s.idx++";
		re2c:YYBACKUP = "s.saved = s.idx";
		re2c:YYRESTORE = "s.idx = s.saved";
		re2c:YYLESSTHAN = "(s.end - s.idx) < @@";
		re2c:YYSHIFT = "s.idx += @@";
		re2c:yyfill:enable = 0;
		re2c:vectorize:linear = 1;
		!use:headers;
	*/
}

func lexFillFnScalar(buf string) (int, int) {
	s := opaqueStream{raw: buf, end: len(buf)}
	YYPEEK := func() byte { return s.peek1() }
	YYSKIP := func() { s.idx++ }
	YYBACKUP := func() { s.saved = s.idx }
	YYRESTORE := func() { s.idx = s.saved }
	YYLESSTHAN := func(n int) bool { return (s.end - s.idx) < n }
	YYFILL := func(n int) { _ = n }
	/*!local:re2c
		re2c:api:style = functions;
		re2c:YYCTYPE = byte;
		re2c:YYFILL = "YYFILL(@@)";
		re2c:YYFILL:naked = 1;
		re2c:yyfill:enable = 1;
		re2c:vectorize:linear = 0;
		!use:headers;
	*/
}

func lexFillFnLinear(buf string) (int, int) {
	s := opaqueStream{raw: buf, end: len(buf)}
	YYPEEK := func() byte { return s.peek1() }
	YYPEEK2 := func() uint16 { return s.peek2() }
	YYPEEK4 := func() uint32 { return s.peek4() }
	YYPEEK8 := func() uint64 { return s.peek8() }
	YYSKIP := func() { s.idx++ }
	YYBACKUP := func() { s.saved = s.idx }
	YYRESTORE := func() { s.idx = s.saved }
	YYLESSTHAN := func(n int) bool { return (s.end - s.idx) < n }
	YYSHIFT := func(n int) { s.idx += n }
	YYFILL := func(n int) { _ = n }
	/*!local:re2c
		re2c:api:style = functions;
		re2c:YYCTYPE = byte;
		re2c:YYFILL = "YYFILL(@@)";
		re2c:YYFILL:naked = 1;
		re2c:yyfill:enable = 1;
		re2c:vectorize:linear = 1;
		!use:headers;
	*/
}

func lexFillFfScalar(buf string) (int, int) {
	s := opaqueStream{raw: buf, end: len(buf)}
	/*!local:re2c
		re2c:api:style = free-form;
		re2c:YYCTYPE = byte;
		re2c:YYPEEK = "s.peek1()";
		re2c:YYSKIP = "s.idx++";
		re2c:YYBACKUP = "s.saved = s.idx";
		re2c:YYRESTORE = "s.idx = s.saved";
		re2c:YYLESSTHAN = "(s.end - s.idx) < @@";
		re2c:YYFILL = "_ = @@";
		re2c:YYFILL:naked = 1;
		re2c:yyfill:enable = 1;
		re2c:vectorize:linear = 0;
		!use:headers;
	*/
}

func lexFillFfLinear(buf string) (int, int) {
	s := opaqueStream{raw: buf, end: len(buf)}
	/*!local:re2c
		re2c:api:style = free-form;
		re2c:YYCTYPE = byte;
		re2c:YYPEEK = "s.peek1()";
		re2c:YYPEEK2 = "s.peek2()";
		re2c:YYPEEK4 = "s.peek4()";
		re2c:YYPEEK8 = "s.peek8()";
		re2c:YYSKIP = "s.idx++";
		re2c:YYBACKUP = "s.saved = s.idx";
		re2c:YYRESTORE = "s.idx = s.saved";
		re2c:YYLESSTHAN = "(s.end - s.idx) < @@";
		re2c:YYSHIFT = "s.idx += @@";
		re2c:YYFILL = "_ = @@";
		re2c:YYFILL:naked = 1;
		re2c:yyfill:enable = 1;
		re2c:vectorize:linear = 1;
		!use:headers;
	*/
}

func check(src string) {
	fns := []func(string) (int, int){
		lexFnScalar,
		lexFnLinear,
		lexFfScalar,
		lexFfLinear,
		lexFillFnScalar,
		lexFillFnLinear,
		lexFillFfScalar,
		lexFillFfLinear,
	}
	r0, e0 := fns[0](src)
	for i := 1; i < len(fns); i++ {
		ri, ei := fns[i](src)
		if ri != r0 || ei != e0 {
			panic(fmt.Sprintf("variant %d on %q: got (%d,%d), want (%d,%d)", i, src, ri, ei, r0, e0))
		}
	}
}

func checkVariantHits(name string, fn func(string) (int, int), words []string, expectWide bool) {
	widePeeks2, widePeeks4, widePeeks8 = 0, 0, 0
	for _, w := range words {
		_, _ = fn(w)
	}
	if expectWide {
		if widePeeks2 <= 0 || widePeeks4 <= 0 || widePeeks8 <= 0 {
			panic(fmt.Sprintf("%s: expected positive wide peek counts, got (%d, %d, %d)",
				name, widePeeks2, widePeeks4, widePeeks8))
		}
	} else {
		if widePeeks2 != 0 || widePeeks4 != 0 || widePeeks8 != 0 {
			panic(fmt.Sprintf("%s: expected zero wide peek counts, got (%d, %d, %d)",
				name, widePeeks2, widePeeks4, widePeeks8))
		}
	}
}

func main() {
	words := []string{
		"ok:",
		"date:",
		"content-length:",
		"content-type:",
		"transfer-encoding:",
		"connection:",
		"content-language:",
		"x-custom:",
	}
	for _, w := range words {
		for p := 0; p <= len(w); p++ {
			prefix := w[:p]
			check(prefix)
			check(prefix + "z")
			check(prefix + ":")
			check(prefix + "!")
			if p < len(w) {
				mut := []byte(w)
				mut[p] ^= 1
				check(string(mut))
			}
		}
	}
	checkVariantHits("lexFnScalar", lexFnScalar, words, false)
	checkVariantHits("lexFfScalar", lexFfScalar, words, false)
	checkVariantHits("lexFillFnScalar", lexFillFnScalar, words, false)
	checkVariantHits("lexFillFfScalar", lexFillFfScalar, words, false)
	checkVariantHits("lexFnLinear", lexFnLinear, words, true)
	checkVariantHits("lexFfLinear", lexFfLinear, words, true)
	checkVariantHits("lexFillFnLinear", lexFillFnLinear, words, true)
	checkVariantHits("lexFillFfLinear", lexFillFfLinear, words, true)
}
