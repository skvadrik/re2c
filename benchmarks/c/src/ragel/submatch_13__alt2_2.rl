#include "ragel/base.h"

namespace ragel_submatch_13__alt2_2 {

const char *delim = "\n";

%%{
    machine m;

    # 'a' has to go last because of the action collision on empty string
    #
    # Use left-guarded concatenation <: because the usual concatenation results
    # in incorrect parse of 'aaa...abbb...b' (a1, a2 get overwritten (reset to
    # NULL) on transition to the second alternative).
    #
    # Note that this forces 'bbb...b' to be parsed as (b*)(a*) instead of
    # (a*)(b*) as it should by the leftmost criterion.

    ab =
        ( ([b]* >{ b1 = p; } %{ b2 = p; a1 = a2 = NULL; })
        | ([a]* >{ a1 = p; } %{ a2 = p; b1 = b2 = NULL; })
        )
        <:
        ( ([b]* >{ b3 = p; } %{ b4 = p; a3 = a4 = NULL; })
        | ([a]* >{ a3 = p; } %{ a4 = p; b3 = b4 = NULL; })
        )
        [\n] >{
            if (a1)      { OUTC('A'); OUTS(a1, a2); }
            else if (b1) { OUTC('B'); OUTS(b1, b2); }
            if (a3)      { OUTC('A'); OUTS(a3, a4); }
            else if (b3) { OUTC('B'); OUTS(b3, b4); }
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
        *a2, *b2,
        *a3, *b3,
        *a4, *b4;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;

    return count;
}

RAGEL_BENCH()
RAGEL_TEST()

} // namespace ragel_submatch_13__alt2_2
