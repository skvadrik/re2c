// re2c $INPUT -o $OUTPUT -i --tags
#include <stdio.h>
#include <string.h>

static inline unsigned parse_oct(const char *s, const char *e)
{
    unsigned oct = 0;
    for (; s != e; ++s) {
        oct = oct * 10 + *s - '0';
    }
    return oct;
}

/*!max:re2c*/

/* at least maximal lexeme length plus YYMAXFILL */
static const size_t SIZE = YYMAXFILL * 2;

struct input_t {
    char buf[SIZE + YYMAXFILL];
    char *lim;
    char *cur;
    char *mar;
    char *tok;
    /*!stags:re2c format = "char *@@;"; */
    bool eof;

    input_t()
        : buf()
        , lim(buf + SIZE)
        , cur(lim)
        , mar(lim)
        , tok(lim)
        /*!stags:re2c format = ", @@(0)"; */
        , eof(false)
    {}
    bool fill(size_t need)
    {
        if (eof) {
            printf("\nfill: underflow - 1\n");
            return false;
        }
        const size_t free = tok - buf;
        if (free < need) {
            printf("\nfill: underflow - 2\n");
            return false;
        }
        memmove(buf, tok, lim - tok);
        lim -= free;
        cur -= free;
        mar -= free;
        tok -= free;
        /*!stags:re2c format = "@@ -= free;"; */
        lim += fread(lim, 1, free, stdin);
        if (lim < buf + SIZE) {
            eof = true;
            memset(lim, 0, YYMAXFILL);
            lim += YYMAXFILL;
        }
        return true;
    }
};

static bool lex(input_t & in)
{
loop:
    in.tok = in.cur;
    const char *p1, *p2, *p3;
    /*!re2c
        re2c:define:YYCTYPE = char;
        re2c:define:YYCURSOR = in.cur;
        re2c:define:YYLIMIT = in.lim;
        re2c:define:YYMARKER = in.mar;
        re2c:define:YYFILL = "if (!in.fill(@@)) return false;";
        re2c:define:YYFILL:naked = 1;
        re2c:tags:expression = "in.@@";

        end = "\x00";
        oct = [0-9]{1,3};
        d   = ".";

        *   { return false; }
        end { return YYMAXFILL == in.lim - in.tok; }
          oct @p1
        d oct @p2
        d oct @p3
        d oct [\n] {
            printf("> %u.%u.%u.%u\n",
                parse_oct(in.tok, p1),
                parse_oct(p1 + 1, p2),
                parse_oct(p2 + 1, p3),
                parse_oct(p3 + 1, in.cur - 1));
            goto loop;
        }
    */
}

int main()
{
    input_t in;
    if (!lex(in)) {
        printf("error\n");
    }

    return 0;
}
