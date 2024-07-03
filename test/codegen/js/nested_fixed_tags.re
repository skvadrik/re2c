// re2js $INPUT -o $OUTPUT

const assert = require('assert');

/*!maxnmatch:re2c*/

/*!re2c
    re2c:api = custom;
    re2c:define:YYPEEK      = "str.charCodeAt(cur)";
    re2c:define:YYSKIP      = "cur += 1";
    re2c:define:YYBACKUP    = "mar = cur";
    re2c:define:YYRESTORE   = "cur = mar";
    re2c:define:YYSTAGP     = "@@{tag} = cur";
    re2c:define:YYSTAGN     = "@@{tag} = -1";
    re2c:define:YYSHIFTSTAG = "@@{tag} += @@{shift}";
    re2c:yyfill:enable = 0;
*/

function lex_tags(str) {
    var cur = 0
    /*!re2c
        re2c:tags = 1;
        ([b] @x [a] @y)? { return x == -1 ? -1 : y - x }
    */
}

function lex_captures(str) {
    var cur = 0
    var yypmatch = Array(YYMAXNMATCH * 2).fill(-1)
    /*!re2c
        re2c:posix-captures = 1;
        (([a]))? { return yypmatch[4] }
    */
}

assert.equal(lex_tags("\0"), -1)
assert.equal(lex_tags("ba\0"), 1)
assert.equal(lex_captures("\0"), -1)
assert.equal(lex_captures("a\0"), 0)
