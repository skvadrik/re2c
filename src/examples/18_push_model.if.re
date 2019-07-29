#include <stdio.h>
#include <string.h>

/*!max:re2c*/
static const size_t SIZE = 4096;

struct input_t {
    char buf[SIZE + YYMAXFILL];
    char *lim;
    char *cur;
    char *tok;
    int state;
    unsigned need;
    unsigned yyaccept;
    char yych;

    input_t()
        : buf()
        , lim(buf + SIZE)
        , cur(lim)
        , tok(lim)
        , state(-1)
        , need(0)
        , yyaccept(0)
        , yych(0)
    {}

    bool fill()
    {
        const size_t free = tok - buf;
        if (free < need) return false;

        memmove(buf, tok, buf - tok + SIZE);
        lim -= free;
        cur -= free;
        tok -= free;
        lim += fread(lim, 1, free, stdin);
        if (lim < buf + SIZE) {
            memset(lim, 0, YYMAXFILL);
            lim += YYMAXFILL;
        }
        return true;
    }
};

enum status_t { OK, FAIL, NEED_MORE_INPUT };

static status_t lex(input_t &in, unsigned &words)
{
#   define YYGETSTATE()  in.state
#   define YYSETSTATE(s) in.state = s
#   define YYFILL(n)     do { in.need = n; return NEED_MORE_INPUT; } while (0)
    /*!getstate:re2c*/
loop:
    in.tok = in.cur;
    /*!re2c
        re2c:define:YYCTYPE  = char;
        re2c:define:YYCURSOR = in.cur;
        re2c:define:YYLIMIT  = in.lim;
        re2c:variable:yych   = in.yych;

        *         { return FAIL; }
        [\x00]    { return OK; }
        [\n ]+    { goto loop; }
        [a-zA-Z]+ { ++words; goto loop; }
    */
}

int main()
{
    input_t in;
    unsigned words = 0;

    while (true) {
        const status_t st = lex(in, words);

        // end of input: print result
        if (st == OK) {
            printf("\nword count: %u\n", words);
            break;

        // unexpected error: abort
        } else if (st == FAIL) {
            printf("\nerror\n");
            return 1;

        // get more input and continue
        } else if (!in.fill()) {
            printf("\nsmall buffer\n");
            return 2;
        }
    }

    return 0;
}
