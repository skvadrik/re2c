#include "ragel/common.c"

const char *delim = "\n";

%%{
    machine abcd;

    abcd =
        [a]* >{ a0 = p; } ([b]*) >{ b0 = p; }
        [a]* >{ a1 = p; } ([b]*) >{ b1 = p; }
        [a]* >{ a2 = p; } ([b]*) >{ b2 = p; }
        [a]* >{ a3 = p; } ([b]*) >{ b3 = p; }
        [\n] >{
            outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
            outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
            outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
            outs(out, a3, b3); outc(out, '.'); outs(out, b3, p + 1);
        };

    main := abcd*;
}%%

%% write data;

static void lex(Input *in, Output *out)
{
    char *p = in->p;
    char *pe = in->pe;
    const char
        *a0, *a1, *a2, *a3,
        *b0, *b1, *b2, *b3;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;
}
