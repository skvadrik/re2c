// re2d $INPUT -o $OUTPUT
module main;

import core.stdc.stdlib;
import core.stdc.string;

private int lex(immutable char[] s) {
    // For the sake of example create a string without terminating null.
    char *buf = cast(char*) malloc(s.length);
    memcpy(buf, cast(const(void*)) s, s.length);

    const(char) *cur = buf, lim = buf + s.length;
    int count = 0;

    for (;;) {
    /*!re2c
        re2c:api = generic;
        re2c:yyfill:enable = 0;
        re2c:YYCTYPE = char;
        re2c:YYPEEK = "cur < lim ? *cur : 0";  // fake null
        re2c:YYSKIP = "++cur;";

        *      { count = -1; break; }
        [\x00] { break;{} }
        [a-z]+ { ++count; continue;{} }
        [ ]+   { continue; }
    */
    }

    free(buf);
    return count;
}

void main() {
    assert(lex("") == 0);
    assert(lex("one two three ") == 3);
    assert(lex("f0ur") == -1);
}
