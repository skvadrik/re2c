// re2c $INPUT -o $OUTPUT -i --vectorize-linear
#include <assert.h>
#include <string.h>

#define YYCTYPE unsigned char

// The default API needs neither YYPEEKN nor YYSKIPN. Without YYFILL, the multi-character reads are
// guarded by YYLIMIT.
static int lex(const char *s)
{
    const char *YYCURSOR = s, *YYLIMIT = s + strlen(s), *YYMARKER;
    /*!re2c
    re2c:yyfill:enable = 0;
    re2c:YYLIMIT = YYLIMIT;

    *             { return -1; }
    "SELECT"      { return 1; }
    "\x89PNG\r\n\x1a\n" { return 2; }
    */
}

int main()
{
    assert(lex("SELECT") == 1);
    assert(lex("\x89PNG\r\n\x1a\n") == 2);
    assert(lex("UNKNOWN") == -1);
    assert(lex("DE") == -1);
    assert(lex("SE") == -1);
    assert(lex("D") == -1);
    assert(lex("") == -1);
    return 0;
}
