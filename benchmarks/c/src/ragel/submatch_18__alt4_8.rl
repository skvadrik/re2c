#include "ragel/base.h"

namespace ragel_submatch_18__alt4_8 {

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

    abcdefgh =
        ( ([b]* >{ b1 = p; } %{ b2 = p; a1 = a2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; })
        | ([c]* >{ c1 = p; } %{ c2 = p; a1 = a2 = b1 = b2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; })
        | ([d]* >{ d1 = p; } %{ d2 = p; a1 = a2 = b1 = b2 = c1 = c2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; })
        | ([e]* >{ e1 = p; } %{ e2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; })
        | ([f]* >{ f1 = p; } %{ f2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = g1 = g2 = h1 = h2 = NULL; })
        | ([g]* >{ g1 = p; } %{ g2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = h1 = h2 = NULL; })
        | ([h]* >{ h1 = p; } %{ h2 = p; a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = NULL; })
        | ([a]* >{ a1 = p; } %{ a2 = p; b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = g1 = g2 = h1 = h2 = NULL; })
        )
        <:
        ( ([b]* >{ b3 = p; } %{ b4 = p; a3 = a4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; })
        | ([c]* >{ c3 = p; } %{ c4 = p; a3 = a4 = b3 = b4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; })
        | ([d]* >{ d3 = p; } %{ d4 = p; a3 = a4 = b3 = b4 = c3 = c4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; })
        | ([e]* >{ e3 = p; } %{ e4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; })
        | ([f]* >{ f3 = p; } %{ f4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = g3 = g4 = h3 = h4 = NULL; })
        | ([g]* >{ g3 = p; } %{ g4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = h3 = h4 = NULL; })
        | ([h]* >{ h3 = p; } %{ h4 = p; a3 = a4 = b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = NULL; })
        | ([a]* >{ a3 = p; } %{ a4 = p; b3 = b4 = c3 = c4 = d3 = d4 = e3 = e4 = f3 = f4 = g3 = g4 = h3 = h4 = NULL; })
        )
        <:
        ( ([b]* >{ b5 = p; } %{ b6 = p; a5 = a6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; })
        | ([c]* >{ c5 = p; } %{ c6 = p; a5 = a6 = b5 = b6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; })
        | ([d]* >{ d5 = p; } %{ d6 = p; a5 = a6 = b5 = b6 = c5 = c6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; })
        | ([e]* >{ e5 = p; } %{ e6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; })
        | ([f]* >{ f5 = p; } %{ f6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = g5 = g6 = h5 = h6 = NULL; })
        | ([g]* >{ g5 = p; } %{ g6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = h5 = h6 = NULL; })
        | ([h]* >{ h5 = p; } %{ h6 = p; a5 = a6 = b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = NULL; })
        | ([a]* >{ a5 = p; } %{ a6 = p; b5 = b6 = c5 = c6 = d5 = d6 = e5 = e6 = f5 = f6 = g5 = g6 = h5 = h6 = NULL; })
        )
        <:
        ( ([b]* >{ b7 = p; } %{ b8 = p; a7 = a8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; })
        | ([c]* >{ c7 = p; } %{ c8 = p; a7 = a8 = b7 = b8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; })
        | ([d]* >{ d7 = p; } %{ d8 = p; a7 = a8 = b7 = b8 = c7 = c8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; })
        | ([e]* >{ e7 = p; } %{ e8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; })
        | ([f]* >{ f7 = p; } %{ f8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = g7 = g8 = h7 = h8 = NULL; })
        | ([g]* >{ g7 = p; } %{ g8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = h7 = h8 = NULL; })
        | ([h]* >{ h7 = p; } %{ h8 = p; a7 = a8 = b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = NULL; })
        | ([a]* >{ a7 = p; } %{ a8 = p; b7 = b8 = c7 = c8 = d7 = d8 = e7 = e8 = f7 = f8 = g7 = g8 = h7 = h8 = NULL; })
        )
        [\n] >{
            if (a1)      { OUTC('A'); OUTS(a1, a2); }
            else if (b1) { OUTC('B'); OUTS(b1, b2); }
            else if (c1) { OUTC('C'); OUTS(c1, c2); }
            else if (d1) { OUTC('D'); OUTS(d1, d2); }
            else if (e1) { OUTC('E'); OUTS(e1, e2); }
            else if (f1) { OUTC('F'); OUTS(f1, f2); }
            else if (g1) { OUTC('G'); OUTS(g1, g2); }
            else if (h1) { OUTC('H'); OUTS(h1, h2); }
            if (a3)      { OUTC('A'); OUTS(a3, a4); }
            else if (b3) { OUTC('B'); OUTS(b3, b4); }
            else if (c3) { OUTC('C'); OUTS(c3, c4); }
            else if (d3) { OUTC('D'); OUTS(d3, d4); }
            else if (e3) { OUTC('E'); OUTS(e3, e4); }
            else if (f3) { OUTC('F'); OUTS(f3, f4); }
            else if (g3) { OUTC('G'); OUTS(g3, g4); }
            else if (h3) { OUTC('H'); OUTS(h3, h4); }
            if (a6)      { OUTC('A'); OUTS(a5, a6); }
            else if (b6) { OUTC('B'); OUTS(b5, b6); }
            else if (c6) { OUTC('C'); OUTS(c5, c6); }
            else if (d6) { OUTC('D'); OUTS(d5, d6); }
            else if (e6) { OUTC('E'); OUTS(e5, e6); }
            else if (f6) { OUTC('F'); OUTS(f5, f6); }
            else if (g6) { OUTC('G'); OUTS(g5, g6); }
            else if (h6) { OUTC('H'); OUTS(h5, h6); }
            if (a8)      { OUTC('A'); OUTS(a7, a8); }
            else if (b8) { OUTC('B'); OUTS(b7, b8); }
            else if (c8) { OUTC('C'); OUTS(c7, c8); }
            else if (d8) { OUTC('D'); OUTS(d7, d8); }
            else if (e8) { OUTC('E'); OUTS(e7, e8); }
            else if (f8) { OUTC('F'); OUTS(f7, f8); }
            else if (g8) { OUTC('G'); OUTS(g7, g8); }
            else if (h8) { OUTC('H'); OUTS(h7, h8); }
            OUTC('\n');
        };

    main := abcdefgh*;
}%%

%% write data;

static int lex(Input *in, int count) {
    char *p = in->p;
    char *pe = in->pe;
    const char
        *a1, *b1, *c1, *d1, *e1, *f1, *g1, *h1,
        *a2, *b2, *c2, *d2, *e2, *f2, *g2, *h2,
        *a3, *b3, *c3, *d3, *e3, *f3, *g3, *h3,
        *a4, *b4, *c4, *d4, *e4, *f4, *g4, *h4,
        *a5, *b5, *c5, *d5, *e5, *f5, *g5, *h5,
        *a6, *b6, *c6, *d6, *e6, *f6, *g6, *h6,
        *a7, *b7, *c7, *d7, *e7, *f7, *g7, *h7,
        *a8, *b8, *c8, *d8, *e8, *f8, *g8, *h8;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;

    return count;
}

RAGEL_BENCH()
RAGEL_TEST()

} // namespace ragel_submatch_18__alt4_8
