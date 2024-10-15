// re2c $INPUT -o $OUTPUT -ir --case-ranges
#include <assert.h>

#define YYCTYPE char

/*!rules:re2c
    re2c:yyfill:enable = 0;

    *          { return -1; }
    [a-zA-Z]   { return 0; }
    [0-9]      { return 1; }
    [!@#$%^&*] { return 2; }
*/

static int lex1(const char *YYCURSOR)
{
    /*!use:re2c*/
}

static int lex2(const char *YYCURSOR)
{
    /*!use:re2c
    re2c:flags:case-ranges = 0;
    */
}

static int lex3(const char *YYCURSOR)
{
    /*!use:re2c
    re2c:flags:case-ranges = 1;
    */
}

#define TEST(s, i) assert(\
    lex1(s) == i && \
    lex2(s) == i && \
    lex3(s) == i \
);

int main()
{
    TEST("a", 0);
    TEST("0", 1);
    TEST("!", 2);
    TEST("", -1);
    return 0;
}
