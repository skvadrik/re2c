// re2c $INPUT -o $OUTPUT -i
#include <assert.h>
#include <string.h>

/*!re2c
    re2c:api:style      = free-form;
    re2c:define:YYCTYPE = char;
    re2c:yyfill:enable  = 0;
    re2c:eof            = 0;
*/

int lex1(const char *s)
{
    const char *YYCURSOR = s, *YYLIMIT = s + strlen(s), *YYMARKER;
    do {
    /*!re2c
        [^]* "a" { continue; }
        $        { return 0; }
    */
    } while (1);
}

int lex2(const char *s)
{
    const char *YYCURSOR = s, *YYLIMIT = s + strlen(s), *YYMARKER;
    do {
    /*!re2c
        [^\n]* "a" { continue; }
        $          { return 0; }
    */
    } while (1);
}

int lex3(const char *s)
{
    const char *YYCURSOR = s, *YYLIMIT = s + strlen(s), *YYMARKER;
    do {
    /*!re2c
        [^\n]* "a" { continue; }
        $          { return 0; }
        *          { return 1; }
    */
    } while (1);
}

int lex4(const char *s)
{
    const char *YYCURSOR = s, *YYLIMIT = s + strlen(s), *YYMARKER;
    do {
    /*!re2c
        [^\n]* "a" { continue; }
        $          { return 0; }
        ""         { return 1; }
    */
    } while (1);
}

int lex5(const char *s)
{
    const char *YYCURSOR = s, *YYLIMIT = s + strlen(s), *YYMARKER;
    do {
    /*!re2c
        [^\n]* "a" { continue; }
        $          { return 0; }
        ""         { return 1; }
        *          { return 2; }
    */
    } while (1);
}

int main()
{
    assert(lex1("") == 0);
    assert(lex1("a") == 0);

    assert(lex2("") == 0);
    assert(lex2("a") == 0);

    assert(lex3("") == 0);
    assert(lex3("a") == 0);
    assert(lex3("a\n") == 1);
    assert(lex3("b") == 1);

    assert(lex4("") == 0);
    assert(lex4("a") == 0);
    assert(lex4("a\n") == 1);
    assert(lex4("b") == 1);

    assert(lex5("") == 0);
    assert(lex5("a") == 0);
    assert(lex5("a\n") == 2);
    assert(lex5("b") == 2);

    return 0;
}
