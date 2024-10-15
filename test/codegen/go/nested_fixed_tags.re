//go:generate re2go $INPUT -o $OUTPUT -i
package main

func assert_eq(x, y int) { if x != y { panic("error") } }

/*!re2c
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE     = byte;
	re2c:define:YYPEEK      = "str[cur]";
	re2c:define:YYSKIP      = "cur += 1";
	re2c:define:YYBACKUP    = "mar = cur";
	re2c:define:YYRESTORE   = "cur = mar";
	re2c:define:YYSTAGP     = "@@{tag} = cur";
	re2c:define:YYSTAGN     = "@@{tag} = -1";
	re2c:define:YYSHIFTSTAG = "@@{tag} += @@{shift}";
*/

func lex_tags(str string) int {
	var cur, mar, x, y int
	/*!stags:re2c:b1 format = 'var @@ int'; separator = "\n\t"; */
	/*!re2c:b1
		re2c:tags = 1;
		([b] @x [a] @y)? { if x == -1 { return -1 } else { return y - x } }
	*/
}

/*!maxnmatch:re2c*/

func lex_captures(str string) int {
	var cur, yynmatch int
	yypmatch := make([]int, 2*YYMAXNMATCH)
	/*!stags:re2c:b2 format = 'var @@ int'; separator = "\n\t"; */
	/*!re2c:b2
		re2c:posix-captures = 1;
		(([a]))? {
			assert_eq(yynmatch, 3)
			return yypmatch[4]
		}
	*/
}

func main() {
	assert_eq(lex_tags("\000"), -1)
	assert_eq(lex_tags("ba\000"), 1)
	assert_eq(lex_captures("\000"), -1)
	assert_eq(lex_captures("a\000"), 0)
}
