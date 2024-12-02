#include <assert.h>
#include "ragel/common.c"

const char *delim = "\n";

%%{
    machine m;

    # 'a' has to go last because of the action collision on empty string

    ab =
        ( ([b]* >{ b1 = p; } %{ b2 = p; a1 = a2 = NULL; })
        | ([a]* >{ a1 = p; } %{ a2 = p; b1 = b2 = NULL; })
        )
        [\n] >{
            if (a1)      { outc(out, 'A'); outs(out, a1, a2); }
            else if (b1) { outc(out, 'B'); outs(out, b1, b2); }
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
        *a2, *b2;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;
}
