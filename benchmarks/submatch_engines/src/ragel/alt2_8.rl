#include <assert.h>
#include "ragel/common.c"

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
        [\n] >{
            if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
            else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
            else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
            else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
            else if (e1) { outc(out, 'E'); outs(out, e1, e2); }
            else if (f1) { outc(out, 'F'); outs(out, f1, f2); }
            else if (g1) { outc(out, 'G'); outs(out, g1, g2); }
            else if (h1) { outc(out, 'H'); outs(out, h1, h2); }
            if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
            else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
            else if (c3) { outc(out, 'C'); outs(out, c3, c4); }
            else if (d3) { outc(out, 'D'); outs(out, d3, d4); }
            else if (e3) { outc(out, 'E'); outs(out, e3, e4); }
            else if (f3) { outc(out, 'F'); outs(out, f3, f4); }
            else if (g3) { outc(out, 'G'); outs(out, g3, g4); }
            else if (h3) { outc(out, 'H'); outs(out, h3, h4); }
            outc(out, '\n');
        };

    main := abcdefgh*;
}%%

%% write data;

static void lex(Input *in, Output *out)
{
    char *p = in->p;
    char *pe = in->pe;
    const char
        *a1, *b1, *c1, *d1, *e1, *f1, *g1, *h1,
        *a2, *b2, *c2, *d2, *e2, *f2, *g2, *h2,
        *a3, *b3, *c3, *d3, *e3, *f3, *g3, *h3,
        *a4, *b4, *c4, *d4, *e4, *f4, *g4, *h4;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;
}
