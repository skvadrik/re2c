#include "ragel/base.h"

namespace ragel_lex_01__numbers2 {

const char *delim = "\n";

%%{
    machine lex_numbers;

    bin = [0][bB][01]+;
    oct = [0][0-7]*;
    dec = [1-9][0-9]*;
    hex = [0][xX][0-9a-fA-F]+;
    float = ([0-9]*[.][0-9]+ | [1-9][0-9]*) ([eE][+\-]?[1-9][0-9]*)?;
    eol = [\n];

    main := |*
        bin   eol { OUTX(ts, te, 2); };
        oct   eol { OUTX(ts, te, 8); };
        dec   eol { OUTX(ts, te, 10); };
        hex   eol { OUTX(ts, te, 16); };
        float eol { OUTX(ts, te, 1); };
    *|;
}%%

%% write data;

static int lex(Input *in, int count) {
    char *p = in->p;
    char *ts = in->ts;
    char *te = in->te;
    char *pe = in->pe;
    int act = in->act;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->ts = ts;
    in->te = te;
    in->pe = pe;
    in->act = act;

    return count;
}

RAGEL_BENCH_AND_TEST()

} // namespace ragel_lex_01__numbers2
