#include <locale.h>
#include <stdio.h>
#include <string.h>

/*!max:re2c*/

struct input_t {
    size_t len;
    char *str;

    input_t(const char *s)
        : len(strlen(s) + 1)
        , str(new char[len + YYMAXFILL])
    {
        memcpy(str, s, len);
        memset(str + len, 'a', YYMAXFILL);
    }
    ~input_t()
    {
        delete[]str;
    }
};

static void lex(const input_t & input)
{
    const char *YYCURSOR = input.str;
    const char *const YYLIMIT = input.str + input.len + YYMAXFILL;
    const char *YYMARKER, *YYCTXMARKER;
    wchar_t c = '"';
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:define:YYFILL = "goto err;";
        re2c:define:YYFILL:naked = 1;

        end = "\x00";
        q = "\"";
        e = "\\";
    */

    /*!re2c
        * { goto err; }
        q { goto str; }
    */

str:
    printf("%lc", c);
    /*!re2c
        *                   { goto err; }
        . \ (e | q)         { c = YYCURSOR[-1]; goto str; }
        e "a"               { c = '\a'; goto str; }
        e "b"               { c = '\b'; goto str; }
        e "f"               { c = '\f'; goto str; }
        e "n"               { c = '\n'; goto str; }
        e "r"               { c = '\r'; goto str; }
        e "t"               { c = '\t'; goto str; }
        e "v"               { c = '\v'; goto str; }
        e e                 { c = '\\'; goto str; }
        e "'"               { c = '\''; goto str; }
        e q                 { c = '"';  goto str; }
        e "?"               { c = '?';  goto str; }
        e / [0-7]           { c = 0; goto oct; }
        e "x" / [0-9a-fA-F] { c = 0; goto hex; }
        q end               {
            printf("\"\n");
            return;
        }
    */

oct:
    /*!re2c
        ""    { goto str; }
        [0-7] { c = (c << 3) + (YYCURSOR[-1] - '0'); goto oct; }
    */

hex:
    /*!re2c
        ""    { goto str; }
        [0-9] { c = (c << 4) + (YYCURSOR[-1] - '0');      goto hex; }
        [a-f] { c = (c << 4) + (YYCURSOR[-1] - 'a' + 10); goto hex; }
        [A-F] { c = (c << 4) + (YYCURSOR[-1] - 'A' + 10); goto hex; }
    */

err:
    printf("... error :[\n");
}

int main(int argc, char **argv)
{
    if (!setlocale(LC_CTYPE, "en_US.utf8")) {
        printf("setlocale failed: en_US.utf8\n");
        return 1;
    }
    for (int i = 1; i < argc; ++i) {
        input_t arg(argv[i]);
        lex(arg);
    }
    return 0;
}
