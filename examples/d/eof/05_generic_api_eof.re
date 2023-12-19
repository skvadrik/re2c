// re2d $INPUT -o $OUTPUT
module main;

import core.stdc.stdlib;
import core.stdc.string;

private int lex(immutable char[] s) {
    // For the sake of example create a string without terminating null.
    char *buf = cast(char*) malloc(s.length);
    memcpy(buf, cast(const(void*)) s, s.length);

    const(char)* cur = buf, lim = buf + s.length, mar;
    int count = 0;

    for (;;) {
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:eof = 0;
        re2c:api = custom;

        re2c:define:YYCTYPE    = char;
        re2c:define:YYLESSTHAN = "cur >= lim";
        re2c:define:YYPEEK     = "cur < lim ? *cur : 0";  // fake null
        re2c:define:YYSKIP     = "++cur;";
        re2c:define:YYBACKUP   = "mar = cur;";
        re2c:define:YYRESTORE  = "cur = mar;";

        str = ['] ([^'\\] | [\\][^])* ['];

        *    { count = -1; break; }
        $    { break;{} }
        str  { ++count; continue; }
        [ ]+ { continue; }
    */
    }

    free(buf);
    return count;
}

void main() {
    assert(lex("") == 0);
    assert(lex("'qu\0tes' 'are' 'fine: \\'' ") == 3);
    assert(lex("'unterminated\\'") == -1);
}
