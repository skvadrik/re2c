//go:generate re2go $INPUT -o $OUTPUT -ir --input-encoding utf8
package main

/*!rules:re2c
	re2c:yyfill:enable = 0;
	re2c:define:YYPEEK = "str[cursor]";
	re2c:define:YYSKIP = "cursor += 1";
	re2c:define:YYBACKUP  = "marker = cursor";
	re2c:define:YYRESTORE = "cursor = marker";

	end = [\x00];
	vowel = "a" | "э" | "ы" | "о" | "у";

	*                   { return 1 }
	vowel "г" vowel end { return 0 }
*/

func LexUtf8(str string) int {
	var cursor, marker int
	/*!use:re2c
	re2c:define:YYCTYPE = byte;
	re2c:flags:8 = 1;

	"\U00012014" end { return 2 }
	*/
}

func LexUtf16(str []uint16) int {
	var cursor, marker int
	/*!use:re2c
	re2c:define:YYCTYPE = uint16;
	re2c:flags:x = 1;

	"\U00012014" end { return 2 }
	*/
}

func LexUcs2(str []uint16) int {
	var cursor, marker int
	/*!use:re2c
	re2c:define:YYCTYPE = uint16;
	re2c:flags:w = 1;
	*/
}

func LexUtf32(str []uint32) int {
	var cursor, marker int
	/*!use:re2c
	re2c:define:YYCTYPE = uint32;
	re2c:flags:u = 1;

	"\U00012014" end { return 2 }
	*/
}

func main() {
	if LexUtf8("ыгы\000") != 0 ||
		LexUtf8(string([]byte{0xf0, 0x92, 0x80, 0x94, 0})) != 2 {
		panic("UTF8 failed")
	}
	if LexUtf16([]uint16{0x44b, 0x433, 0x44b, 0}) != 0 ||
		LexUtf16([]uint16{0xd808, 0xdc14, 0}) != 2 {
		panic("UTF16 failed")
	}
	if LexUcs2([]uint16{0x44b, 0x433, 0x44b, 0}) != 0 {
		panic("UCS2 failed")
	}
	if LexUtf32([]uint32{0x44b, 0x433, 0x44b, 0}) != 0 ||
		LexUtf32([]uint32{0x12014, 0}) != 2 {
		panic("UTF32 failed")
	}
}
