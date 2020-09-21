// re2c $INPUT -o $OUTPUT -i
#include <assert.h>
#include <string.h>

static int lex(const char *str, unsigned int &count)
{
    const char *YYCURSOR = str;
    const char *YYLIMIT  = YYCURSOR + strlen(str);
    count = 0;
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:yyfill:enable  = 0;
        re2c:eof = 0;

        wsp   = [ \n]+;
        char1 = [a-zA-Z_];
        char  = char1 | [0-9];
        word  = char1 char+;
    */
loop:
    /*!re2c
        *          { return 1; }
        $          { return 0; }
        "" / char1 { goto word; }
        wsp        { goto loop; }
    */
word:
    /*!re2c
        *    { return 2; }
        $    { return 0; }
        word { ++count; goto loop; }
    */
}

int main()
{
    unsigned int count;
    assert(lex("aa bb cc", count) == 0 && count == 3);
    assert(lex("aa 1b cc", count) == 1);
    assert(lex("aa b cc", count) == 2);
    return 0;
}
