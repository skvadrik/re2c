#include <assert.h>
#include <string.h>

#define YYPEEK() *cur
#define YYSKIP() if (++cur > lim) return -1
static int lex(const char *str)
{
    const char *cur = str;
    const char *lim = str + strlen(str) + 1;
    int count = 0;

loop:
    /*!re2c
    re2c:define:YYCTYPE = char;
    re2c:yyfill:enable = 0;
    re2c:flags:input = custom;

    *                         { return -1; }
    [\x00]                    { return cur == lim ? count : -1; }
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
