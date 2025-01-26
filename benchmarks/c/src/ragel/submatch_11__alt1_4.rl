#include "ragel/base.h"

namespace ragel_submatch_11__alt1_4 {

const char *delim = "\n";

%%{
    machine m;

    # 'a' has to go last because of the action collision on empty string

    abcd =
        ( ([b]* >{ b1 = p; } %{ b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; })
        | ([c]* >{ c1 = p; } %{ c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; })
        | ([d]* >{ d1 = p; } %{ d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; })
        | ([a]* >{ a1 = p; } %{ a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; })
        )
        [\n] >{
            if (a1)      { OUTC('A'); OUTS(a1, a2); }
            else if (b1) { OUTC('B'); OUTS(b1, b2); }
            else if (c1) { OUTC('C'); OUTS(c1, c2); }
            else if (d1) { OUTC('D'); OUTS(d1, d2); }
            OUTC('\n');
        };

    main := abcd*;
}%%

%% write data;

static int lex(Input *in, int count) {
    char *p = in->p;
    char *pe = in->pe;
    const char
        *a1, *b1, *c1, *d1,
        *a2, *b2, *c2, *d2;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;

    return count;
}

RAGEL_BENCH_AND_TEST()

} // namespace ragel_submatch_11__alt1_4
