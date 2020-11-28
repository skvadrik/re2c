#include <assert.h>
#include "ragel/common.c"

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
            if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
            else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
            else if (c1) { outc(out, 'C'); outs(out, c1, c2); }
            else if (d1) { outc(out, 'D'); outs(out, d1, d2); }
            outc(out, '\n');
        };

    main := abcd*;
}%%

%% write data;

static void lex(Input *in, Output *out)
{
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
}
