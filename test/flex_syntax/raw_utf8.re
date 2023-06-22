//go:generate re2go $INPUT -o $OUTPUT --utf8 --input-encoding utf8 --flex-syntax -i
package main

func parse(str string) int {
  var cur, mar int
  for {
	/*!re2c
	re2c:yyfill:enable    = 0;
	re2c:define:YYCTYPE   = byte;
	re2c:define:YYPEEK    = "str[cur]";
	re2c:define:YYSKIP    = "cur += 1";
	re2c:define:YYBACKUP  = "mar = cur";
	re2c:define:YYRESTORE = "cur = mar";

	güncellen?me { return 0 }
	aü?b         { return 1 }
	cüüü*d       { return 2 }
	e[ü]f        { return 3 }
	[\000]       { return -1 }
	*            { continue }
	*/
  }
}

func main() {
	assert_eq := func(x, y int) { if x != y { panic("error") } }
	assert_eq(parse("<html><body><p><em>Son güncelleme: 5/5/2020</em></p></body></html>\000"), 0)
	assert_eq(parse("ab"), 1)
	assert_eq(parse("aüb"), 1)
	assert_eq(parse("cüüüüd"), 2)
	assert_eq(parse("eüf"), 3)
}
