// re2d $INPUT -o $OUTPUT -i
module main;

/*!re2c
    re2c:yyfill:enable = 0;
    re2c:define:YYCTYPE     = "char";
    re2c:define:YYPEEK      = "*cur";
    re2c:define:YYSKIP      = "++cur;";
    re2c:define:YYBACKUP    = "mar = cur;";
    re2c:define:YYRESTORE   = "cur = mar;";
    re2c:define:YYSTAGP     = "@@{tag} = cur;";
    re2c:define:YYSTAGN     = "@@{tag} = null;";
    re2c:define:YYSHIFTSTAG = "@@{tag} += @@{shift};";
*/

private long lex_tags(const(char)* str) {
    const(char)* cur = str, mar, x, y;
    /*!stags:re2c:b1 format = 'const(char)* @@;\n'; */
    /*!re2c:b1
        re2c:tags = 1;
        ([b] @x [a] @y)? { return x == null ? -1 : (y - x); }
    */
}

/*!maxnmatch:re2c*/

private long lex_captures(const(char)* str) {
    const(char)* cur = str;
    uint yynmatch;
    const(char)*[2*YYMAXNMATCH] yypmatch; 
    /*!stags:re2c:b2 format = 'const(char)* @@;\n'; */
    /*!re2c:b2
        re2c:posix-captures = 1;
        (([a]))? { return yypmatch[4] == null ? -1 : yypmatch[4] - str; }
    */
}

void main() {
    assert(lex_tags("") == -1);
    assert(lex_tags("ba") == 1);
    assert(lex_captures("") == -1);
    assert(lex_captures("a") == 0);
}
