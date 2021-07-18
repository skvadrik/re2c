//go:generate re2go $INPUT -o $OUTPUT

// This example shows how to combine reusable re2c blocks: two blocks
// ('colors' and 'fish') are merged into one. The 'salmon' rule occurs
// in both blocks; the 'fish' block takes priority because it is used
// earlier. Default rule * occurs in all three blocks; the local (not
// inherited) definition takes priority.

package main

import "testing"

const (
	Color = iota
	Fish
	Dunno
)

/*!rules:re2c:colors
	*                            { panic("eh!") }
	"red" | "salmon" | "magenta" { return Color }
*/

/*!rules:re2c:fish
	*                            { panic("oh!") }
	"haddock" | "salmon" | "eel" { return Fish }
*/

func lex(str string) int {
	var cursor, marker int
	/*!re2c
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE   = byte;
	re2c:define:YYPEEK    = "str[cursor]";
	re2c:define:YYSKIP    = "cursor += 1";
	re2c:define:YYBACKUP  = "marker = cursor";
	re2c:define:YYRESTORE = "cursor = marker";

	!use:fish;
	!use:colors;
	* { return Dunno }
	*/
}

func TestLex(t *testing.T) {
	if lex("salmon") != Fish || lex("what?") != Dunno {
		t.Errorf("lex failed")
	}
}
