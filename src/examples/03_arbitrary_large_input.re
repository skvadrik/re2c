#include <limits.h>
#include <stdio.h>
#include <string.h>

/*!max:re2c*/
static const size_t SIZE = 1024;

struct input_t {
    char buf[SIZE + YYMAXFILL];
    char *lim;
    char *cur;
    char *mar;
    char *tok;
    bool eof;

    FILE *const file;

    input_t(FILE *f)
        : buf()
        , lim(buf + SIZE)
        , cur(lim)
        , mar(lim)
        , tok(lim)
        , eof(false)
        , file(f)
    {}
    bool fill(size_t need)
    {
        if (eof) {
            return false;
        }

        const size_t free = tok - buf;
        if (free < need) {
            return false;
        }

        memmove(buf, tok, lim - tok);
        lim -= free;
        cur -= free;
        mar -= free;
        tok -= free;
        lim += fread(lim, 1, free, file);
        if (lim < buf + SIZE) {
            eof = true;
            memset(lim, 'a', YYMAXFILL);
            lim += YYMAXFILL;
        }
        return true;
    }
};

static int lex(input_t & input)
{
    int count = 0;
    for (;;) {
        input.tok = input.cur;
        /*!re2c
            re2c:define:YYCTYPE = char;
            re2c:define:YYCURSOR = input.cur;
            re2c:define:YYMARKER = input.mar;
            re2c:define:YYLIMIT = input.lim;
            re2c:define:YYFILL = "if (!input.fill(@@)) return -1;";
            re2c:define:YYFILL:naked = 1;

            end = "a";
            str = "\"" ([^"\\] | "\\" ["\\])* "\"";
            wsp = [ \t\n\r]+;

            *   { return -1; }
            end { return (input.lim - input.tok == YYMAXFILL) ? count : -1; }
            wsp { continue; }
            str {
                if (count == INT_MAX) {
                    return -2;
                }
                ++count;
                continue;
            }
        */
    }
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf ("usage: ./example <filename>\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        printf("error: cannot open file: %s\n", argv[1]);
        return 1;
    }

    input_t input(file);
    const int count = lex(input);
    switch (count) {
        case -1: printf("lexing error\n"); break;
        case -2: printf("lines overflow\n"); break;
        default: printf("glorious %d strings!\n", count); break;
    }

    fclose(file);
    return 0;
}
