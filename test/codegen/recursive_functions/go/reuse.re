//go:generate re2go $INPUT -o $OUTPUT --input-encoding utf8 --recursive-functions -i
package main

// This example supports multiple input encodings: UTF-8 and UTF-32.
// Both lexers are generated from the same rules block, and the use
// blocks add only encoding-specific configurations.
/*!rules:re2c
	re2c:yyfill:enable = 0;
	re2c:define:YYPEEK    = "str[cur]";
	re2c:define:YYSKIP    = "cur += 1";
	re2c:define:YYBACKUP  = "mar = cur";
	re2c:define:YYRESTORE = "cur = mar";

	"∀x ∃y" { return 0; }
	*       { return 1; }
*/

/*!use:re2c
	re2c:encoding:utf8 = 1;
	re2c:define:YYCTYPE = uint8;
	re2c:define:YYFN = ["lexUTF8;int", "str;[]uint8", "cur;uint", "mar;uint"];
*/

/*!use:re2c
	re2c:encoding:utf32 = 1;
	re2c:define:YYCTYPE = uint32;
	re2c:define:YYFN = ["lexUTF32;int", "str;[]uint32", "cur;uint", "mar;uint"];
*/

func main() {
	assert_eq := func(x, y int) { if x != y { panic("error") } }
	assert_eq(lexUTF8([]uint8{0xe2, 0x88, 0x80, 0x78, 0x20, 0xe2, 0x88, 0x83, 0x79}, 0, 0), 0)
	assert_eq(lexUTF32([]uint32{0x2200, 0x78, 0x20, 0x2203, 0x79}, 0, 0), 0)
}
