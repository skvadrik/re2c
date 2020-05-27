#include <stdio.h>
#include <string.h>

/*!max:re2c*/
#define SIZE 4096

typedef struct {
    FILE *file;
    char buf[SIZE + YYMAXFILL], *lim, *cur, *mar, *tok;
    int eof;
} Input;

static int fill(Input *in, size_t need)
{
    if (in->eof) {
        return 1;
    }
    const size_t free = in->tok - in->buf;
    if (free < need) {
        return 2;
    }
    memmove(in->buf, in->tok, in->lim - in->tok);
    in->lim -= free;
    in->cur -= free;
    in->mar -= free;
    in->tok -= free;
    in->lim += fread(in->lim, 1, free, in->file);
    if (in->lim < in->buf + SIZE) {
        in->eof = 1;
        memset(in->lim, 0, YYMAXFILL);
        in->lim += YYMAXFILL;
    }
    return 0;
}

static void init(Input *in, FILE *file)
{
    in->file = file;
    in->cur = in->mar = in->tok = in->lim = in->buf + SIZE;
    in->eof = 0;
    fill(in, 1);
}

#define YYFILL(n) if (fill(in, n) != 0) return -1
static int lex(Input *in)
{
    int count = 0;
loop:
    in->tok = in->cur;
    /*!re2c
    re2c:define:YYCTYPE = char;
    re2c:define:YYCURSOR = in->cur;
    re2c:define:YYMARKER = in->mar;
    re2c:define:YYLIMIT = in->lim;

    *                           { return -1; }
    [\x00]                      { return (YYMAXFILL == in->lim - in->tok) ? count : -1; }
    [a-z]+                      { ++count; goto loop; }
    ['] ([^'\\] | [\\][^])* ['] { ++count; goto loop; }
    [ ]+                        { goto loop; }

    */
}

int main()
{
    FILE *f = fopen("input.txt", "rb");
    if (!f) return 1;

    Input in;
    init(&in, f);
    printf("count: %d\n", lex(&in));

    fclose(f);
    return 0;
}
