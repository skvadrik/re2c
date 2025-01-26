#include "ragel/base.h"

namespace ragel_submatch_28__cat8_2 {

const char *delim = "\n";

%%{
    machine abcd;

    abcd =
        [a]* >{ a0 = p; } ([a][a][b]*) >{ b0 = p; }
        [a]* >{ a1 = p; } ([a][a][b]*) >{ b1 = p; }
        [a]* >{ a2 = p; } ([a][a][b]*) >{ b2 = p; }
        [a]* >{ a3 = p; } ([a][a][b]*) >{ b3 = p; }
        [a]* >{ a4 = p; } ([a][a][b]*) >{ b4 = p; }
        [a]* >{ a5 = p; } ([a][a][b]*) >{ b5 = p; }
        [a]* >{ a6 = p; } ([a][a][b]*) >{ b6 = p; }
        [a]* >{ a7 = p; } ([a][a][b]*) >{ b7 = p; }
        [\n] >{
            OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
            OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
            OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
            OUTS(a3, b3); OUTC('.'); OUTS(b3, a4); OUTC('.');
            OUTS(a4, b4); OUTC('.'); OUTS(b4, a5); OUTC('.');
            OUTS(a5, b5); OUTC('.'); OUTS(b5, a6); OUTC('.');
            OUTS(a6, b6); OUTC('.'); OUTS(b6, a7); OUTC('.');
            OUTS(a7, b7); OUTC('.'); OUTS(b7, p + 1);
        };

    main := abcd*;
}%%

%% write data;

static int lex(Input *in, int count) {
    char *p = in->p;
    char *pe = in->pe;
    const char
        *a0, *a1, *a2, *a3, *a4, *a5, *a6, *a7,
        *b0, *b1, *b2, *b3, *b4, *b5, *b6, *b7;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;

    return count;
}

RAGEL_BENCH_AND_TEST()

} // namespace ragel_submatch_28__cat8_2
