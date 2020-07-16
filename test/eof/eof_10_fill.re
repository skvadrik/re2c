// re2c $INPUT -o $OUTPUT 
#include <stdio.h>
#include <string.h>

#define SIZE 4096

typedef struct {
    FILE *file;
    char buf[SIZE + 1], *lim, *cur, *tok;
    int eof;
} Input;

static int fill(Input *in)
{
    if (in->eof) {
        return 1;
    }
    const size_t free = in->tok - in->buf;
    if (free < 1) {
        return 2;
    }
    memmove(in->buf, in->tok, in->lim - in->tok);
    in->lim -= free;
    in->cur -= free;
    in->tok -= free;
    in->lim += fread(in->lim, 1, free, in->file);
    in->lim[0] = 0;
    in->eof |= in->lim < in->buf + SIZE;
    return 0;
}

static void init(Input *in, FILE *file)
{
    in->file = file;
    in->cur = in->tok = in->lim = in->buf + SIZE;
    in->eof = 0;
    fill(in);
}

#define YYFILL() fill(in)
static int lex(Input *in)
{
    int count = 0;
loop:
    in->tok = in->cur;
    /*!re2c
    re2c:define:YYCTYPE = char;
    re2c:define:YYCURSOR = in->cur;
    re2c:define:YYLIMIT = in->lim;
    re2c:eof = 0;

    *                         { return -1; }
    $                         { return count; }
    [a-z]+                    { ++count; goto loop; }
    ['] ([^'] | [\\]['])* ['] { ++count; goto loop; }
    [ ]+                      { goto loop; }

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
