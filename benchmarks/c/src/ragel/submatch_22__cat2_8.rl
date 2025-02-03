#include "ragel/common.c"

const char *delim = "\n";

%%{
    machine abcd;

    abcd =
        [a]* >{ a0 = p; } ([a]{8}[b]*) >{ b0 = p; }
        [a]* >{ a1 = p; } ([a]{8}[b]*) >{ b1 = p; }
        [\n] >{
            outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
            outs(out, a1, b1); outc(out, '.'); outs(out, b1, p + 1);
        };

    main := abcd*;
}%%

%% write data;

static void lex(Input *in, Output *out)
{
    char *p = in->p;
    char *pe = in->pe;
    const char
        *a0, *a1,
        *b0, *b1;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;
}
