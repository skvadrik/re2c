// re2c $INPUT -o $OUTPUT 
#include <stdio.h>

int scan(const char *p)
{
#define YYCTYPE char
    const char *YYCURSOR = p;
    const char *YYMARKER;

/*!re2c
    re2c:yyfill:enable = 0;

    escaped_char = "\\b";

    [<] ([x] | escaped_char | [y])* [>] { return YYCURSOR - p; }
    ("a" | escaped_char)* { return YYCURSOR - p; }
    . { return 0; }
*/
}

int main()
{
    const char *str = "aaa\\baaa";
    int res = scan(str);
    printf("%d: %s\n", res, str + res);
    return 0;
}

