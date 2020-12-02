#include "ragel/common.c"

const char *delim = "\n";

%%{
    machine aaa;

    aaa = ([a]{64} %{
            outs(out, s, p);
            outc(out, '.');
            s = p;
        })* >{ s = p; }
        [\n] >{ outc(out, '\n'); };

    main := aaa*;
}%%

%% write data;

static void lex(Input *in, Output *out)
{
    char *p = in->p;
    char *pe = in->pe;
    const char *s;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;
}
