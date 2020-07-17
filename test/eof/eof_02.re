// re2c $INPUT -o $OUTPUT -i
#include <stdio.h>
#include <string.h>

static const size_t SIZE = 4096;

struct input_t {
    char buf[SIZE + 1];
    char *lim;
    char *cur;
    char *tok;
    bool eof;

    input_t()
        : buf()
        , lim(buf + SIZE)
        , cur(lim)
        , tok(lim)
        , eof(false)
    {
        fill();
    }
    int fill()
    {
        if (eof) {
            return 1;
        }
        const size_t free = tok - buf;
        if (free < 1) {
            return 2;
        }
        memmove(buf, tok, lim - tok);
        lim -= free;
        cur -= free;
        tok -= free;
        lim += fread(lim, 1, free, stdin);
        lim[0] = 255;
        if (lim < buf + SIZE) {
            eof = true;
        }
        return 0;
    }
};

static bool lex(input_t & in, unsigned int &count)
{
    for (count = 0;;) {
        in.tok = in.cur;
        /*!re2c
            re2c:define:YYCTYPE = char;
            re2c:define:YYCURSOR = in.cur;
            re2c:define:YYLIMIT = in.lim;
            re2c:define:YYFILL = "in.fill";
            re2c:eof = 255;

            wsp = [\n]+;
            num = [0-9]+;

            *    { return false; }
            $    { return true; }
            wsp  { continue; }
            num  { ++count; continue; }
        */
    }
}

int main()
{
    input_t in;
    unsigned int count;
    if (lex(in, count)) {
        printf("glorious %u numbers!\n", count);
    } else {
        printf("error\n");
    }

    return 0;
}
