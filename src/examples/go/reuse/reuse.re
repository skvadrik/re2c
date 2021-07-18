//go:generate re2go $INPUT -o $OUTPUT --input-encoding utf8

// This example supports multiple input encodings: UTF-8 and UTF-32.
// Both lexers are generated from the same rules block, and the use
// blocks add only encoding-specific configurations.

package main

import "testing"

/*!rules:re2c
	re2c:yyfill:enable = 0;
	re2c:define:YYPEEK    = "str[cursor]";
	re2c:define:YYSKIP    = "cursor += 1";
	re2c:define:YYBACKUP  = "marker = cursor";
	re2c:define:YYRESTORE = "cursor = marker";

	"∀x ∃y" { return 0; }
	*       { return 1; }
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

func TestLex(t *testing.T) {
	s8 := []uint8{0xe2, 0x88, 0x80, 0x78, 0x20, 0xe2, 0x88, 0x83, 0x79};
	if lexUTF8(s8) != 0 {
		t.Errorf("utf8 failed")
	}

	s32 := []uint32{0x2200, 0x78, 0x20, 0x2203, 0x79};
	if lexUTF32(s32) != 0 {
		t.Errorf("utf32 failed")
	}
}
