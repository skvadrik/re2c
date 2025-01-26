#include "ragel/base.h"

namespace ragel_submatch_33__rep_alt_5_3_2 {

const char *delim = "\n";

%%{
    machine aaa;

    # using disambiguation operator ** causes incorrect parse,
    # because some actions are removed while they are still needed
    #
    # without ** results are also incorrect due to action collision

    aaa = (([a]{5}|[a]{3}|[a]{2}) %{
            OUTS(s, p);
            OUTC('.');
            s = p;
        })** >{ s = p; }
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

} // namespace ragel_submatch_33__rep_alt_5_3_2
