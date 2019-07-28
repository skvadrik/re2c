#include <assert.h>
#include <stdlib.h>
#include <string.h>

/*!max:re2c*/

static int lex(const char *str)
{
    const size_t len = strlen(str);
    char *buf = malloc(len + YYMAXFILL);
    memcpy(buf, str, len);
    memset(buf + len, 0, YYMAXFILL);

    const char *YYCURSOR = buf;
    const char *YYLIMIT = buf + len + YYMAXFILL;
    int count = 0;

loop:
    /*!re2c
    re2c:define:YYCTYPE = char;
    re2c:define:YYFILL:naked = 1;
    re2c:define:YYFILL = "goto error;";

    *                         { goto error; }
    [\x00]                    { if (YYCURSOR == YYLIMIT) goto end; else goto error; }
    [a-z]+                    { ++count; goto loop; }
    ['] ([^'] | [\\]['])* ['] { ++count; goto loop; }
    [ ]+                      { goto loop; }

    */
error:
    count = -1;
end:
    free(buf);
    return count;
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
