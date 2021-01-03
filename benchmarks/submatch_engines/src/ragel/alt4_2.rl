#include <assert.h>
#include "ragel/common.c"

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

    ab =
        ( ([b]* >{ b1 = p; } %{ b2 = p; a1 = a2 = NULL; })
        | ([a]* >{ a1 = p; } %{ a2 = p; b1 = b2 = NULL; })
        )
        <:
        ( ([b]* >{ b3 = p; } %{ b4 = p; a3 = a4 = NULL; })
        | ([a]* >{ a3 = p; } %{ a4 = p; b3 = b4 = NULL; })
        )
        <:
        ( ([b]* >{ b5 = p; } %{ b6 = p; a5 = a6 = NULL; })
        | ([a]* >{ a5 = p; } %{ a6 = p; b5 = b6 = NULL; })
        )
        <:
        ( ([b]* >{ b7 = p; } %{ b8 = p; a7 = a8 = NULL; })
        | ([a]* >{ a7 = p; } %{ a8 = p; b7 = b8 = NULL; })
        )
        [\n] >{
            if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
            else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
            if (a3)      { outc(out, 'A'); outs(out, a3, a4); }
            else if (b3) { outc(out, 'B'); outs(out, b3, b4); }
            if (a5)      { outc(out, 'A'); outs(out, a5, a6); }
            else if (b5) { outc(out, 'B'); outs(out, b5, b6); }
            if (a7)      { outc(out, 'A'); outs(out, a7, a8); }
            else if (b7) { outc(out, 'B'); outs(out, b7, b8); }
            outc(out, '\n');
        };

    main := ab*;
}%%

%% write data;

static void lex(Input *in, Output *out)
{
    char *p = in->p;
    char *pe = in->pe;
    const char
        *a1, *b1,
        *a2, *b2,
        *a3, *b3,
        *a4, *b4,
        *a5, *b5,
        *a6, *b6,
        *a7, *b7,
        *a8, *b8;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;
}
