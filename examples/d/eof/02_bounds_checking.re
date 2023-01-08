// re2d $INPUT -o $OUTPUT
module bounds_checking02;
import core.stdc.stdlib;
import core.stdc.string;

/*!max:re2c*/

int lex(in string str, ulong len) {
    // Make a copy of the string with YYMAXFILL zeroes at the end.
    char *buf = cast(char*) malloc(len + YYMAXFILL);
    memcpy(buf, cast(const(void*)) str, len);
    memset(buf + len, 0, YYMAXFILL);

    const(char) *YYCURSOR = buf, YYLIMIT = buf + len + YYMAXFILL;
    int count = 0;

loop:
    /*!re2c
        re2c:api:style = free-form;
        re2c:define:YYCTYPE = char;
        re2c:define:YYPEEK = '*YYCURSOR';
        re2c:define:YYSKIP = 'YYCURSOR++;';
        re2c:define:YYLESSTHAN = 'YYLIMIT <= YYCURSOR';
        re2c:define:YYFILL  = "goto fail;";

        str = ['] ([^'\\] | [\\][^])* ['];

        [\x00] {
            // Check that it is the sentinel, not some unexpected null.
            if (YYCURSOR - 1 == buf + len) goto exit; else goto fail;
        }
        str  { ++count; goto loop; }
        [ ]+ { goto loop; }
        *    { goto fail; }
    */

fail:
    count = -1;

exit:
    free(buf);
    return count;
}

void TEST(immutable char[] s, int r){
    assert(lex(s,s.length)==r);
}

unittest{
    TEST("", 0);
    TEST("'qu\0tes' 'are' 'fine: \\'' ", 3);
    TEST("'unterminated\\'", -1);
    TEST("'unexpected \0 null\\'", -1);
}

extern(C) void main()
{
    static foreach(u; __traits(getUnitTests, __traits(parent, main)))
        u();
}


