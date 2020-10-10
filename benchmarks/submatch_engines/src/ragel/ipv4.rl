#include "ragel/common.c"

const char *delim = "\n";

%%{
    machine ipv4;

    oct  = [0-9]{1,3};
    dot  = [.];
    nl   = [\n];
    ipv4 =
        oct >{ p1 = p; } dot
        oct >{ p2 = p; } dot
        oct >{ p3 = p; } dot
        oct >{ p4 = p; } nl
    >{
        outs(out, p1, p2 - 1);
        outc(out, ',');
        outs(out, p2, p3 - 1);
        outc(out, ',');
        outs(out, p3, p4 - 1);
        outc(out, ',');
        outs(out, p4, p);
        outc(out, '\n');
    };

    main := ipv4*;
}%%

%% write data;

static void prolog(Output *out) {}
static void epilog(Output *out) {}

static void lex(Input *in, Output *out)
{
    char *p = in->p;
    char *pe = in->pe;
    const char *p1, *p2, *p3, *p4;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;
}
