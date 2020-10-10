#include "ragel/common.c"

const char *delim = "\n";

%%{
    machine datetime;

    year     = ([1-9][0-9]*)? [0-9]{4};
    month    = [1][0-2] | [0][1-9];
    day      = [3][0-1] | [0][1-9] | [1-2][0-9];
    hours    = [2][0-3] | [0-1][0-9];
    minutes  = [0-5][0-9];
    seconds  = [0-5][0-9];
    timezone = [Z] | [+\-] ([2][0-3] | [0-1][0-9]) [:][0-5][0-9];
    dateTime =
        year     >{ y1 = p; } %{ y2 = p; } '-'
        month    >{ m1 = p; } %{ m2 = p; } '-'
        day      >{ d1 = p; } %{ d2 = p; } 'T'
        hours    >{ h1 = p; } %{ h2 = p; } ':'
        minutes  >{ M1 = p; } %{ M2 = p; } ':'
        seconds  >{ s1 = p; } %{ s2 = p; }
        timezone >{ z1 = p; } %{ z2 = p; } [\n]
    >{
        OUTS("{'year'='");
        outs(out, y1, y2);
        OUTS("', 'month'='");
        outs(out, m1, m2);
        OUTS("', 'day'='");
        outs(out, d1, d2);
        OUTS("', 'hours'='");
        outs(out, h1, h2);
        OUTS("', 'minutes'='");
        outs(out, M1, M2);
        OUTS("', 'seconds'='");
        outs(out, s1, s2);
        OUTS("', 'tz'='");
        outs(out, z1, z2);
        OUTS("'}\n");
    };

    main := dateTime*;
}%%

%% write data;

static void prolog(Output *out) {}
static void epilog(Output *out) {}

static void lex(Input *in, Output *out)
{
    char *p = in->p;
    char *pe = in->pe;
    const char
        *s1, *y1, *h1, *m1, *d1, *M1, *z1,
        *s2, *y2, *h2, *m2, *d2, *M2, *z2;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;
}
