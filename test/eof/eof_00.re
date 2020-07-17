// re2c $INPUT -o $OUTPUT -i
#include <stdio.h>
#include <string.h>

/*!max:re2c*/
static const size_t SIZE = 4096;

struct input_t {
    char buf[SIZE + YYMAXFILL];
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
        tok -= free;
        lim += fread(lim, 1, free, stdin);
        if (lim < buf + SIZE) {
            eof = true;
            memset(lim, 0, YYMAXFILL);
            lim += YYMAXFILL;
        }
        return true;
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
            re2c:define:YYFILL = "if (!in.fill(@@)) return false;";
            re2c:define:YYFILL:naked = 1;

            end = "\x00";
            wsp = [\n]+;
            sstr = ["] ([^"\\] | "\\" [^])* ["];
            dstr = ['] ([^'\\] | "\\" [^])* ['];
            num = [+-]? ("0" | [1-9][0-9]*);
            num1 = "1" | "12" | "12345" | "123456" | "1234567" | "12345678" | "123456789";
            word = [_a-zA-Z][_a-zA-Z0-9]*;
            day = 'monday' | 'tuesday' | 'wednesday' | 'thursday' | 'friday' | 'saturday' | 'sunday';

            *   { return false; }
            end { return YYMAXFILL == in.lim - in.tok; }
            wsp { continue; }
            sstr { ++count; continue; }
            dstr { ++count; continue; }
            num1 { ++count; continue; }
            num  { ++count; continue; }
            day  { ++count; continue; }
            word { ++count; continue; }
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
