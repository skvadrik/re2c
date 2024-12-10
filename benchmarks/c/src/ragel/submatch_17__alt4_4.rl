#include "ragel/base.h"

namespace ragel_submatch_17__alt4_4 {

const char *delim = "\n";

%%{
    machine m;

    # 'a' has to go last because of the action collision on empty string
    #
    # Use left-guarded concatenation <: because the usual concatenation results
    # in incorrect parse of 'aaa...abbb...baaa...abbb...b' (a1, a2 get
    # overwritten (reset to NULL) on transition to the second alternative), and
    # likewise with other tags.
    #
    # Note that this forces 'bbb...b' to be parsed as (b*)(a*)(a*)(a*) instead
    # of (a*)(a*)(a*)(b*) as it should by the leftmost criterion.

    abcd =
        ( ([b]* >{ b1 = p; } %{ b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = NULL; })
        | ([c]* >{ c1 = p; } %{ c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = NULL; })
        | ([d]* >{ d1 = p; } %{ d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = NULL; })
        | ([a]* >{ a1 = p; } %{ a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = NULL; })
        )
        <:
        ( ([b]* >{ b3 = p; } %{ b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = NULL; })
        | ([c]* >{ c3 = p; } %{ c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = NULL; })
        | ([d]* >{ d3 = p; } %{ d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = NULL; })
        | ([a]* >{ a3 = p; } %{ a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = NULL; })
        )
        <:
        ( ([b]* >{ b5 = p; } %{ b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = NULL; })
        | ([c]* >{ c5 = p; } %{ c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = NULL; })
        | ([d]* >{ d5 = p; } %{ d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = NULL; })
        | ([a]* >{ a5 = p; } %{ a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = NULL; })
        )
        <:
        ( ([b]* >{ b7 = p; } %{ b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = NULL; })
        | ([c]* >{ c7 = p; } %{ c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = NULL; })
        | ([d]* >{ d7 = p; } %{ d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = NULL; })
        | ([a]* >{ a7 = p; } %{ a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = NULL; })
        )
        [\n] >{
            if (a1)      { OUTC('A'); OUTS(a1, a2); }
            else if (b1) { OUTC('B'); OUTS(b1, b2); }
            else if (c1) { OUTC('C'); OUTS(c1, c2); }
            else if (d1) { OUTC('D'); OUTS(d1, d2); }
            if (a3)      { OUTC('A'); OUTS(a3, a4); }
            else if (b3) { OUTC('B'); OUTS(b3, b4); }
            else if (c3) { OUTC('C'); OUTS(c3, c4); }
            else if (d3) { OUTC('D'); OUTS(d3, d4); }
            if (a5)      { OUTC('A'); OUTS(a5, a6); }
            else if (b5) { OUTC('B'); OUTS(b5, b6); }
            else if (c5) { OUTC('C'); OUTS(c5, c6); }
            else if (d5) { OUTC('D'); OUTS(d5, d6); }
            if (a7)      { OUTC('A'); OUTS(a7, a8); }
            else if (b7) { OUTC('B'); OUTS(b7, b8); }
            else if (c7) { OUTC('C'); OUTS(c7, c8); }
            else if (d7) { OUTC('D'); OUTS(d7, d8); }
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
        *a2, *b2, *c2, *d2,
        *a3, *b3, *c3, *d3,
        *a4, *b4, *c4, *d4,
        *a5, *b5, *c5, *d5,
        *a6, *b6, *c6, *d6,
        *a7, *b7, *c7, *d7,
        *a8, *b8, *c8, *d8;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;

    return count;
}

RAGEL_BENCH()
RAGEL_TEST()

} // namespace ragel_submatch_17__alt4_4
