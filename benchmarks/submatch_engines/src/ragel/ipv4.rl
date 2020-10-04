#include "ragel/common.c"

const char *delim = "\n";

%%{
    machine ipv4;

    action setptr { q = p; }
    action output { outs(out, q, p); }

    oct  = [0-9]{1,3};
    dot  = [.]  > { outc(out, ','); };
    nl   = [\n] > { outc(out, '\n'); };
    ipv4 =
        oct > setptr % output
        dot
        oct > setptr % output
        dot
        oct > setptr % output
        dot
        oct > setptr % output
        nl;

    main := ipv4*;
}%%

%% write data;

static void prolog(Output *out) {}
static void epilog(Output *out) {}

static void lex(Input *in, Output *out)
{
    char *p = in->p;
    char *pe = in->pe;
    char *q;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;
}
