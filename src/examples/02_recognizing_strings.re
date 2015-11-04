#include <stdio.h>
#include <string.h>

/*!max:re2c*/

struct input_t {
    size_t len;
    char *str;

    input_t(const char *s)
        : len(strlen(s))
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

static bool lex(const input_t & input)
{
    const char *YYCURSOR = input.str;
    const char *const YYLIMIT = input.str + input.len + YYMAXFILL;
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:define:YYFILL = "return false;";
        re2c:define:YYFILL:naked = 1;

        sstr = "'"  [^']* "'";
        dstr = "\"" [^"]* "\"";

        *             { return false; }
        (sstr | dstr) { return YYLIMIT - YYCURSOR == YYMAXFILL; }
    */
}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i) {
        input_t arg(argv[i]);
        printf("%s: %s\n", lex(arg) ? "str" : "err", argv[i]);
    }
    return 0;
}
