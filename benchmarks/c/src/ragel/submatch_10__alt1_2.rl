#include "ragel/base.h"

namespace ragel_submatch_10__alt1_2 {

const char *delim = "\n";

%%{
    machine m;

    # 'a' has to go last because of the action collision on empty string

    ab =
        ( ([b]* >{ b1 = p; } %{ b2 = p; a1 = a2 = NULL; })
        | ([a]* >{ a1 = p; } %{ a2 = p; b1 = b2 = NULL; })
        )
        [\n] >{
            if (a1)      { OUTC('A'); OUTS(a1, a2); }
            else if (b1) { OUTC('B'); OUTS(b1, b2); }
            OUTC('\n');
        };

    main := ab*;
}%%

%% write data;

static int lex(Input *in, int count) {
    char *p = in->p;
    char *pe = in->pe;
    const char
        *a1, *b1,
        *a2, *b2;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;

    return count;
}

RAGEL_BENCH()
RAGEL_TEST()

} // namespace ragel_submatch_10__alt1_2
