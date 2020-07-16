//go:generate re2go $INPUT -o $OUTPUT -r --input-encoding utf8
package main

import "testing"

/*!rules:re2c
	re2c:yyfill:enable = 0;
	re2c:define:YYPEEK    = "str[cursor]";
	re2c:define:YYSKIP    = "cursor += 1";
	re2c:define:YYBACKUP  = "marker = cursor";
	re2c:define:YYRESTORE = "cursor = marker";

	"∀x ∃y: p(x, y)" { return 0; }
	*                { return 1; }
*/

func lexUTF8(str []uint8) int {
	var cursor, marker int
	/*!use:re2c
	re2c:flags:8 = 1;
	re2c:define:YYCTYPE = uint8;
	*/
}

func lexUTF32(str []uint32) int {
	var cursor, marker int
	/*!use:re2c
	re2c:flags:u = 1;
	re2c:define:YYCTYPE = uint32;
	*/
}

func TestLexUTF8(t *testing.T) {
	s_utf8 := []uint8{
		0xe2, 0x88, 0x80, 0x78, 0x20, 0xe2, 0x88, 0x83, 0x79,
		0x3a, 0x20, 0x70, 0x28, 0x78, 0x2c, 0x20, 0x79, 0x29};

	if lexUTF8(s_utf8) != 0 {
		t.Errorf("utf8 failed")
	}
}

func TestLexUTF32(t *testing.T) {
	s_utf32 := []uint32{
		0x00002200, 0x00000078, 0x00000020, 0x00002203, 0x00000079,
		0x0000003a, 0x00000020, 0x00000070, 0x00000028, 0x00000078,
		0x0000002c, 0x00000020, 0x00000079, 0x00000029};

	if lexUTF32(s_utf32) != 0 {
		t.Errorf("utf32 failed")
	}
}
