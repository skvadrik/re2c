//go:generate re2go $INPUT -o $OUTPUT --api simple
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

func lex(yyinput string) int {
	var yycursor, yymarker int
	/*!re2c
		re2c:yyfill:enable = 0;
		re2c:YYCTYPE = byte;

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
