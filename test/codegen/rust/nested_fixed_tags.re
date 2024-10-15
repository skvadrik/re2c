// re2rust $INPUT -o $OUTPUT

const NONE: usize = std::usize::MAX;

/*!re2c
    re2c:define:YYCTYPE     = u8;
    re2c:define:YYPEEK      = "*str.get_unchecked(cur)";
    re2c:define:YYSKIP      = "cur += 1;";
    re2c:define:YYBACKUP    = "mar = cur;";
    re2c:define:YYRESTORE   = "cur = mar;";
    re2c:define:YYSTAGP     = "@@{tag} = cur;";
    re2c:define:YYSTAGN     = "@@{tag} = NONE;";
    re2c:define:YYSHIFTSTAG = "@@{tag} -= -@@{shift}isize as usize;";
    re2c:yyfill:enable = 0;
*/

fn lex_tags(str: &[u8]) -> i32 {
    let (mut cur, mut mar) = (0, 0);
    let (mut x, y);
    /*!stags:re2c:b1 format = 'let mut @@{tag} = NONE;'; */
    /*!re2c:b1
        re2c:tags = 1;
        ([b] @x [a] @y)? { return if x == NONE { -1 } else { (y - x) as i32 }; }
    */
}

/*!maxnmatch:re2c*/

fn lex_captures(str: &[u8]) -> i32 {
    let mut cur = 0;
    let yynmatch: usize;
    let mut yypmatch = [0; YYMAXNMATCH*2];
    /*!stags:re2c:b2 format = 'let mut @@{tag} = NONE;'; */
    /*!re2c:b2
        re2c:posix-captures = 1;
        (([a]))? {
            assert_eq!(yynmatch, 3);
            return if yypmatch[4] == NONE { -1 } else { yypmatch[4] as i32 };
        }
    */
}

fn main() {
    assert_eq!(lex_tags(b"\0"), -1);
    assert_eq!(lex_tags(b"ba\0"), 1);
    assert_eq!(lex_captures(b"\0"), -1);
    assert_eq!(lex_captures(b"a\0"), 0);
}
