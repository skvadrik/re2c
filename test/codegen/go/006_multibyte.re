//go:generate re2go $INPUT -o $OUTPUT -s -i --vectorize-linear
package main

import "encoding/binary"

var str string
var cursor int
var marker int

func YYPEEKN(cur int, n int) uint64 {
	if cur+n > len(str) {
		return 0
	}
	var buf [8]byte
	copy(buf[:], str[cur:cur+n])
	return binary.LittleEndian.Uint64(buf[:])
}

func YYSKIPN(cur int, n int) {
	cursor += n
}

func Lex(s string) int {
	str = s
	cursor = 0
	marker = 0

	/*!re2c
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE = byte;
	re2c:define:YYCURSOR = cursor;
	re2c:define:YYPEEK = "str[cursor]";
	re2c:define:YYSKIP = "cursor += 1";
	re2c:define:YYBACKUP  = "marker = cursor";
	re2c:define:YYRESTORE = "cursor = marker";

	end = [\x00];

	* { return -1 }
	"SELECT" end { return 1 }
	"INSERT" end { return 2 }
	"UPDATE" end { return 3 }
	"DELETE" end { return 4 }
	*/
}

func main() {
	if Lex("SELECT\000") != 1 { panic("SELECT") }
	if Lex("INSERT\000") != 2 { panic("INSERT") }
	if Lex("UPDATE\000") != 3 { panic("UPDATE") }
	if Lex("DELETE\000") != 4 { panic("DELETE") }
	if Lex("UNKNOWN\000") != -1 { panic("UNKNOWN") }
}
