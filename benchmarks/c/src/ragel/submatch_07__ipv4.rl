#include "ragel/base.h"

namespace ragel_submatch_07__ipv4 {

const char *delim = "\n";

%%{
    machine ipv4;

    oct  = [0-9]{1,3};
    dot  = [.];
    ipv4 =
        oct >{ p1 = p; } dot
        oct >{ p2 = p; } dot
        oct >{ p3 = p; } dot
        oct >{ p4 = p; } [\n]
    >{
        OUTS(p1, p2 - 1);
        OUTC(',');
        OUTS(p2, p3 - 1);
        OUTC(',');
        OUTS(p3, p4 - 1);
        OUTC(',');
        OUTS(p4, p);
        OUTC('\n');
    };

    main := ipv4*;
}%%

%% write data;

static int lex(Input *in, int count) {
    char *p = in->p;
    char *pe = in->pe;
    const char *p1, *p2, *p3, *p4;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;

    return count;
}

RAGEL_BENCH_AND_TEST()

} // namespace ragel_submatch_07__ipv4
