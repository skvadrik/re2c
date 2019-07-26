#include <assert.h>
#include <string.h>

static int lex(const char *str)
{
    const char *YYCURSOR = str;
    const char *YYLIMIT = str + strlen(str);
    int count = 0;

loop:
    /*!re2c
    re2c:define:YYCTYPE = char;
    re2c:yyfill:enable = 0;
    re2c:eof = 0;

    *                         { return -1; }
    $                         { return count; }
    [a-z]+                    { ++count; goto loop; }
    ['] ([^'] | [\\]['])* ['] { ++count; goto loop; }
    [ ]+                      { goto loop; }

    */
}

int main()
{
    assert(lex("") == 0);
    assert(lex("one two three") == 3);
    assert(lex("one two 123?") == -1);
    assert(lex("one 'two' 'th\\'ree' '123?' ''") == 5);
    assert(lex("one 'two' 'three") == -1);
    return 0;
}
