#include "ragel/base.h"

namespace ragel_submatch_38__rep_23_rep_19_rep_17 {

const char *delim = "\n";

%%{
    machine aaa;

    # using disambiguation operator <: causes incorrect parse,
    # because some actions are removed while they are still needed
    #
    # without <: results are also incorrect due to action collision
    #
    # also, without <: ragel hangs

    aaa =
        ([a]{23} %{
            OUTS(s, p);
            OUTC('.');
            s = p;
        })* >{ s = p; }
        <:
        ([a]{19} %{
            OUTS(s, p);
            OUTC('.');
            s = p;
        })*
        <:
        ([a]{17} %{
            OUTS(s, p);
            OUTC('.');
            s = p;
        })*
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

} // namespace ragel_submatch_38__rep_23_rep_19_rep_17
