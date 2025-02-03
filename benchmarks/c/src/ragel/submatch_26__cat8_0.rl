#include "ragel/common.c"

const char *delim = "\n";

%%{
    machine abcd;

    abcd =
        [a]* >{ a0 = p; } ([b]*) >{ b0 = p; }
        [a]* >{ a1 = p; } ([b]*) >{ b1 = p; }
        [a]* >{ a2 = p; } ([b]*) >{ b2 = p; }
        [a]* >{ a3 = p; } ([b]*) >{ b3 = p; }
        [a]* >{ a4 = p; } ([b]*) >{ b4 = p; }
        [a]* >{ a5 = p; } ([b]*) >{ b5 = p; }
        [a]* >{ a6 = p; } ([b]*) >{ b6 = p; }
        [a]* >{ a7 = p; } ([b]*) >{ b7 = p; }
        [\n] >{
            outs(out, a0, b0); outc(out, '.'); outs(out, b0, a1); outc(out, '.');
            outs(out, a1, b1); outc(out, '.'); outs(out, b1, a2); outc(out, '.');
            outs(out, a2, b2); outc(out, '.'); outs(out, b2, a3); outc(out, '.');
            outs(out, a3, b3); outc(out, '.'); outs(out, b3, a4); outc(out, '.');
            outs(out, a4, b4); outc(out, '.'); outs(out, b4, a5); outc(out, '.');
            outs(out, a5, b5); outc(out, '.'); outs(out, b5, a6); outc(out, '.');
            outs(out, a6, b6); outc(out, '.'); outs(out, b6, a7); outc(out, '.');
            outs(out, a7, b7); outc(out, '.'); outs(out, b7, p + 1);
        };

    main := abcd*;
}%%

%% write data;

static void lex(Input *in, Output *out)
{
    char *p = in->p;
    char *pe = in->pe;
    const char
        *a0, *a1, *a2, *a3, *a4, *a5, *a6, *a7,
        *b0, *b1, *b2, *b3, *b4, *b5, *b6, *b7;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;
}
