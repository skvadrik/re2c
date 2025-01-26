#include "ragel/base.h"

namespace ragel_submatch_34__rep_alt_13_11_7 {

const char *delim = "\n";

%%{
    machine aaa;

    aaa = (([a]{13}|[a]{11}|[a]{7}) %{
            OUTS(s, p);
            OUTC('.');
            s = p;
        })* >{ s = p; }
        [\n] >{ OUTC('\n'); };

    main := aaa*;
}%%

%% write data;

static int lex(Input *in, int count) {
    char *p = in->p;
    char *pe = in->pe;
    const char *s;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;

    return count;
}

RAGEL_BENCH_AND_TEST()

} // namespace ragel_submatch_34__rep_alt_13_11_7
