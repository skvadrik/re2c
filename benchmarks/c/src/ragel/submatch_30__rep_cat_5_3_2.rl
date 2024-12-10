#include "ragel/base.h"

namespace ragel_submatch_30__rep_cat_5_3_2 {

const char *delim = "\n";

%%{
    machine aaa;

    aaa = (
        [a]{5} %{
            OUTS(s, p);
            OUTC('.');
            s = p;
        }
        [a]{3} %{
            OUTS(s, p);
            OUTC('.');
            s = p;
        }
        [a]{2} %{
            OUTS(s, p);
            OUTC(';');
            s = p;
        }
    )*
    [\n] >{ OUTC('\n'); };

    main := aaa*;
}%%

%% write data;

static int lex(Input *in, int count) {
    char *p = in->p;
    char *pe = in->pe;
    const char *s = p;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;

    return count;
}

RAGEL_BENCH()
RAGEL_TEST()

} // namespace ragel_submatch_30__rep_cat_5_3_2
