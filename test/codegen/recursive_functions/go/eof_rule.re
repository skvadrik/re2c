//go:generate re2go $INPUT -o $OUTPUT --recursive-functions -i
package main

type State struct {
	str   string
	cur   uint
	mar   uint
	lim   uint
	count int
}

/*!re2c
	re2c:eof = 0;
	re2c:define:YYFN       = ["do_lex;int", "st;*State"];
	re2c:define:YYCTYPE    = byte;
	re2c:define:YYPEEK     = "st.str[st.cur]";
	re2c:define:YYSKIP     = "st.cur += 1";
	re2c:define:YYBACKUP   = "st.mar = st.cur";
	re2c:define:YYRESTORE  = "st.cur = st.mar";
	re2c:define:YYLESSTHAN = "st.lim <= st.cur";
	re2c:yyfill:enable = 0;

	str = ['] ([^'\\] | [\\][^])* ['];

	*    { return -1 }
	$    { return st.count }
	str  { st.count += 1; return do_lex(st) }
	[ ]+ { return do_lex(st) }
*/

// Expects a null-terminated string.
func lex(str string) int {
	st := &State{
		str: str,
		cur: 0,
		mar: 0,
		lim: uint(len(str) - 1), // lim points at the terminating null
		count: 0}
	return do_lex(st)
}

func main() {
	assert_eq := func(x, y int) { if x != y { panic("error") } }
	assert_eq(lex("\000"), 0)
	assert_eq(lex("'qu\000tes' 'are' 'fine: \\'' \000"), 3)
	assert_eq(lex("'unterminated\\'\000"), -1)
}
