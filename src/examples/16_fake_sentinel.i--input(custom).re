#include <stdio.h>
#include <string.h>

static int lex(const char *cur, const char *lim)
{
    const char *mar, *tok = cur;
#   define YYCTYPE     char
#   define YYPEEK()    (cur < lim ? *cur : 0)
#   define YYSKIP()    ++cur
#   define YYBACKUP()  mar = cur
#   define YYRESTORE() cur = mar
    /*!re2c
        re2c:yyfill:enable = 0;

        * { printf("error\n"); return 1; }
        [0-9a-zA-Z]+ [;] [\x00] {
            printf("%.*s\n", (int) (cur - tok) - 1, tok);
            return 0;
        }
    */
}

int main(int argc, char **argv)
{
    if (argc != 2) return 1;

    char *s = argv[1];
    size_t l = strlen(s);
    s[l] = ';'; // overwrite terminating NULL
    return lex(s, s + l + 1);
}
