#include "ragel/base.h"

namespace ragel_submatch_35__rep_alt_23_19_17 {

const char *delim = "\n";

%%{
    machine aaa;

    aaa = (([a]{23}|[a]{19}|[a]{17}) %{
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

} // namespace ragel_submatch_35__rep_alt_23_19_17
