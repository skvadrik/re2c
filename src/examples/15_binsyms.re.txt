#include <stdlib.h>
#include <stdio.h>

static void lex(const char *cur, const char *lim)
{
    const char *mar, *tok;
#   define YYCTYPE     char
#   define YYPEEK()    *cur
#   define YYSKIP()    if (++cur == lim) return;
#   define YYBACKUP()  mar = cur
#   define YYRESTORE() cur = mar
loop:
    tok = cur;
    /*!re2c
        re2c:yyfill:enable = 0;

        * { goto loop; }
        "__" [a-zA-Z0-9_]+ {
            printf("%.*s\n", (int) (cur - tok), tok);
            goto loop;
        }
    */
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "no input files\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        fprintf(stderr, "cannot open file\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    const size_t fsize = (size_t) ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char*) malloc(fsize);
    fread(buffer, 1, fsize, file);
    lex(buffer, buffer + fsize);

    free(buffer);
    fclose(file);
    return 0;
}
