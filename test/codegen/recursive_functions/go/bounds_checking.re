//go:generate re2go $INPUT -o $OUTPUT --recursive-functions -i
package main

import "strings"

/*!max:re2c*/

type State struct {
	buf   string
	cur   uint
	mar   uint
	lim   uint
	count int
}

/*!re2c
	re2c:define:YYFN       = ["do_lex;int", "st;*State"];
	re2c:define:YYCTYPE    = byte;
	re2c:define:YYPEEK     = "st.buf[st.cur]";
	re2c:define:YYSKIP     = "st.cur += 1";
	re2c:define:YYLESSTHAN = "st.lim - st.cur < @@";
	re2c:define:YYFILL     = "return -1";

	str = ['] ([^'\\] | [\\][^])* ['];

	[\x00] { return st.count }
	str    { st.count += 1; return do_lex(st) }
	[ ]+   { return do_lex(st) }
	*      { return -1 }
*/

// Expects YYMAXFILL-padded string.
func lex(str string) int {
	st := &State{
		// Pad string with YYMAXFILL zeroes at the end.
		buf: str + strings.Repeat("\000", int(YYMAXFILL)),
		cur: 0,
		mar: 0,
		lim: uint(len(str)) + YYMAXFILL,
		count: 0}
	return do_lex(st)
}

func main() {
	assert_eq := func(x, y int) { if x != y { panic("error") } }
	assert_eq(lex(""), 0)
	assert_eq(lex("'qu\000tes' 'are' 'fine: \\'' "), 3)
	assert_eq(lex("'unterminated\\'"), -1)
	assert_eq(lex("'unexpected \000 null\\'"), -1)
}
