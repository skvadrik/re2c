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

static const char *lex(const input_t & input)
{
    const char *YYCURSOR = input.str;
    const char *const YYLIMIT = input.str + input.len + YYMAXFILL;
    const char *YYMARKER;
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:define:YYFILL = "return \"err\";";
        re2c:define:YYFILL:naked = 1;

        end = "\x00";
        str = "'" [^']* "'";

        *       { return "err"; }
        str end { return "str"; }
    */
}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i) {
        input_t arg(argv[i]);
        printf("%s: %s\n", lex(arg), arg.str);
    }
    return 0;
}
