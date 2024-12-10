#include "ragel/base.h"

namespace ragel_submatch_25__cat4_4 {

const char *delim = "\n";

%%{
    machine abcd;

    abcd =
        [a]* >{ a0 = p; } ([a]{4}[b]*) >{ b0 = p; }
        [a]* >{ a1 = p; } ([a]{4}[b]*) >{ b1 = p; }
        [a]* >{ a2 = p; } ([a]{4}[b]*) >{ b2 = p; }
        [a]* >{ a3 = p; } ([a]{4}[b]*) >{ b3 = p; }
        [\n] >{
            OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
            OUTS(a1, b1); OUTC('.'); OUTS(b1, a2); OUTC('.');
            OUTS(a2, b2); OUTC('.'); OUTS(b2, a3); OUTC('.');
            OUTS(a3, b3); OUTC('.'); OUTS(b3, p + 1);
        };

    main := abcd*;
}%%

%% write data;

static int lex(Input *in, int count) {
    char *p = in->p;
    char *pe = in->pe;
    const char
        *a0, *a1, *a2, *a3,
        *b0, *b1, *b2, *b3;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;

    return count;
}

RAGEL_BENCH()
RAGEL_TEST()

} // namespace ragel_submatch_25__cat4_4
