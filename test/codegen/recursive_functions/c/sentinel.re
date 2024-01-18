// re2c $INPUT -o $OUTPUT --recursive-functions -i
#include <assert.h>

/*!re2c
re2c:define:YYFN = ["lex", "int", "YYCURSOR", "const char*", "count", "int"];
re2c:define:YYCTYPE = char;
re2c:yyfill:enable = 0;

*      { return -1; }
[\x00] { return count; }
[a-z]+ { return lex(YYCURSOR, ++count); }
[ ]+   { return lex(YYCURSOR, count); }

*/

int main()
{
    assert(lex("", 0) == 0);
    assert(lex("one two three", 0) == 3);
    assert(lex("f0ur", 0) == -1);
    return 0;
}
