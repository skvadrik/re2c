// re2v $INPUT -o $OUTPUT -i

/*!re2c
    re2c:yyfill:enable = 0;
    re2c:define:YYCTYPE     = u8;
    re2c:define:YYPEEK      = "str[cur]";
    re2c:define:YYSKIP      = "cur += 1";
    re2c:define:YYBACKUP    = "mar = cur";
    re2c:define:YYRESTORE   = "cur = mar";
    re2c:define:YYSTAGP     = "@@{tag} = cur";
    re2c:define:YYSTAGN     = "@@{tag} = -1";
    re2c:define:YYSHIFTSTAG = "@@{tag} += @@{shift}";
*/

fn lex_tags(str string) int {
    mut cur, mut mar := 0, 0
    mut x, mut y := 0, 0
    /*!stags:re2c:b1 format = 'mut @@ := -1'; separator = "\n\t"; */
    /*!re2c:b1
        re2c:tags = 1;
        ([b] @x [a] @y)? { return if x == -1 { -1 } else { y - x } }
    */
}

/*!maxnmatch:re2c*/

fn lex_captures(str string) int {
    mut cur := 0
    mut yypmatch := []int{len: yymaxnmatch * 2}
    mut yynmatch := 0
    /*!stags:re2c:b2 format = 'mut @@ := -1'; separator = "\n\t"; */
    /*!re2c:b2
        re2c:posix-captures = 1;
        (([a]))? {
            if yynmatch != 3 { panic("wrong yynmatch!") }
            return yypmatch[4]
        }
    */
}

fn main() {
    assert_eq := fn (result int, expect int) { if result != expect { panic("error") } } 
    assert_eq(lex_tags("\0"), -1)
    assert_eq(lex_tags("ba\0"), 1)
    assert_eq(lex_captures("\0"), -1)
    assert_eq(lex_captures("a\0"), 0)
}
