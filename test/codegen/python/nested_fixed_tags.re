# re2py $INPUT -o $OUTPUT

NONE = -1

/*!maxnmatch:re2c*/

/*!re2c
    re2c:define:YYPEEK      = "str[cur]";
    re2c:define:YYSKIP      = "cur += 1";
    re2c:define:YYBACKUP    = "mar = cur";
    re2c:define:YYRESTORE   = "cur = mar";
    re2c:define:YYSTAGP     = "@@{tag} = cur";
    re2c:define:YYSTAGN     = "@@{tag} = NONE";
    re2c:define:YYSHIFTSTAG = "@@{tag} += @@{shift}";
    re2c:yyfill:enable = 0;
    re2c:indent:top = 1;
*/

def lex_tags(str):
    cur = 0
    /*!re2c
        re2c:tags = 1;
        ([b] @x [a] @y)? { return NONE if x == NONE else y - x }
    */

def lex_captures(str):
    cur = 0
    yypmatch = [NONE] * (YYMAXNMATCH * 2)
    /*!re2c
        re2c:posix-captures = 1;
        (([a]))? { return yypmatch[4] }
    */

assert lex_tags(b"\0") == -1
assert lex_tags(b"ba\0") == 1
assert lex_captures(b"\0") == -1
assert lex_captures(b"a\0") == 0
