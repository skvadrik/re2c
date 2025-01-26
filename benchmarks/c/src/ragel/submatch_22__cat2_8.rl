#include "ragel/base.h"

namespace ragel_submatch_22__cat2_8 {

const char *delim = "\n";

%%{
    machine abcd;

    abcd =
        [a]* >{ a0 = p; } ([a]{8}[b]*) >{ b0 = p; }
        [a]* >{ a1 = p; } ([a]{8}[b]*) >{ b1 = p; }
        [\n] >{
            OUTS(a0, b0); OUTC('.'); OUTS(b0, a1); OUTC('.');
            OUTS(a1, b1); OUTC('.'); OUTS(b1, p + 1);
        };

    main := abcd*;
}%%

%% write data;

static int lex(Input *in, int count) {
    char *p = in->p;
    char *pe = in->pe;
    const char
        *a0, *a1,
        *b0, *b1;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;

    return count;
}

RAGEL_BENCH_AND_TEST()

} // namespace ragel_submatch_22__cat2_8
