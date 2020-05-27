#include <assert.h>
#include <stdio.h>
#include <string.h>

#define SIZE 4096

typedef struct {
    char buf[SIZE + 1], *lim, *cur, *tok, yych;
    unsigned yyaccept;
    int state;
} Input;

static void init(Input *in)
{
    in->cur = in->tok = in->lim = in->buf + SIZE;
    in->lim[0] = 0; // append sentinel symbol
    in->yych = 0;
    in->yyaccept = 0;
    in->state = -1;
}

static int fill(Input *in)
{
    const size_t shift = in->tok - in->buf;
    const size_t free = SIZE - (in->lim - in->tok);

    if (free < 1) return 1; // not enough space in buffer

    memmove(in->buf, in->tok, SIZE - shift);
    in->lim -= shift;
    in->cur -= shift;
    in->tok -= shift;

    const size_t read = fread(in->lim, 1, free, stdin);
    in->lim += read;
    in->lim[0] = 0; // append sentinel symbol

    return 0;
}

typedef enum {OK, SYNTAX_ERROR, UNEXPECTED_EOF, NEED_MORE_INPUT} Status;

#define YYGETSTATE()  in->state
#define YYSETSTATE(s) in->state = s
#define YYFILL()      return NEED_MORE_INPUT
static Status lex(Input *in, unsigned *words)
{
    /*!getstate:re2c*/
loop:
    in->tok = in->cur;
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:define:YYCURSOR = in->cur;
        re2c:define:YYLIMIT = in->lim;
        re2c:variable:yych = in->yych;
        re2c:eof = 0;

        *         { return SYNTAX_ERROR; }
        $         { return UNEXPECTED_EOF; }
        "stop"    { return OK; }
        [\n ]+    { goto loop; }
        [a-zA-Z]+ { *words = *words + 1; goto loop; }
    */
}

int main()
{
    unsigned words = 0;
    Input in;
    init(&in);

    for (;;) {
        const Status st = lex(&in, &words);
        if (st == OK) {
            printf("word count: %u\n", words);
            break;
        }
        else if (st == SYNTAX_ERROR) {
            printf("error: unexpected symbol\n");
            return 1;
        }
        else if (st == UNEXPECTED_EOF) {
            printf("error: unexpected end of input\n");
            return 2;
        }
        else if (fill(&in) != 0) {
            printf("error: not enough space in buffer\n");
            return 3;
        }
    }

    return 0;
}