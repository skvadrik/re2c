// re2d $INPUT -o $OUTPUT
module generic_api_sentinel04;
import core.stdc.stdlib;
import core.stdc.string;

static int lex(in string str, ulong len) {
    // For the sake of example create a string without terminating null.
    char *buf = cast(char*) malloc(len);
    memcpy(buf, cast(const(void*)) str, len);

    const(char) *cur = buf, lim = buf + len;
    int count = 0;

    for (;;) {
    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:api = custom;
        re2c:api:style = free-form;
        re2c:define:YYCTYPE = char;
        re2c:define:YYPEEK = "cur < lim ? *cur : 0";  // fake null
        re2c:define:YYSKIP = "++cur;";

        *      { count = -1; break; }
        [\x00] { break;{} }
        [a-z]+ { ++count; continue;{} }
        [ ]+   { continue; }
    */
    }

    free(buf);
    return count;
}

void TEST(immutable char[] s, int r){
    assert(lex(s,s.length)==r);
}

unittest{
    TEST("", 0);
    TEST("one two three ", 3);
    TEST("f0ur", -1);
}

extern(C) void main()
{
    static foreach(u; __traits(getUnitTests, __traits(parent, main)))
        u();
}
