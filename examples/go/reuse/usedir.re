//go:generate re2go $INPUT -o $OUTPUT
package main

// This example shows how to combine reusable re2c blocks: two blocks
// ('colors' and 'fish') are merged into one. The 'salmon' rule occurs
// in both blocks; the 'fish' block takes priority because it is used
// earlier. Default rule * occurs in all three blocks; the local (not
// inherited) definition takes priority.

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
	var cur, mar int
	/*!re2c
		re2c:yyfill:enable = 0;
		re2c:define:YYCTYPE   = byte;
		re2c:define:YYPEEK    = "str[cur]";
		re2c:define:YYSKIP    = "cur += 1";
		re2c:define:YYBACKUP  = "mar = cur";
		re2c:define:YYRESTORE = "cur = mar";

		!use:fish;
		!use:colors;
		* { return Dunno }  // overrides inherited '*' rules
	*/
}

func main() {
	assert_eq := func(x, y int) { if x != y { panic("error") } }
	assert_eq(lex("salmon"), Fish);
	assert_eq(lex("what?"), Dunno);
}
