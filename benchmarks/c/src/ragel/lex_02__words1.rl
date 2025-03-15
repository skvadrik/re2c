#include "ragel/base.h"

namespace ragel_lex_02__words1 {

const char *delim = "\n";

%%{
    machine lex_words;

    word = ("Monday"
        | "Tuesday"
        | "Wednesday"
        | "Thursday"
        | "Friday"
        | "Saturday"
        | "Sunday"
    ) [\n];

    main := |* word { OUTS(ts, te); }; *|;
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

} // namespace ragel_lex_02__words1
