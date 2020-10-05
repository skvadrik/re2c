#include "ragel/common.c"

const char *delim = "\n";

%%{
    machine email;

    estr     = [a-z0-9!#$%&'*+/=?^_`{|}~\-];
    beforeAt = estr+ ([.] estr+)*;
    az09     = [a-z0-9];
    az09dash = [a-z0-9\-]* [a-z0-9];
    part     = az09 az09dash? [.];
    afterAt  = part+ az09 az09dash?;
    fb       = [^\n]*[\n];

    email =
        beforeAt >{ p1 = p; }
        [@]
        afterAt  >{ p2 = p; }
        [\n]
    >{
        outc(out, ' ');
        outs(out, p1, p2 - 1);
        outc(out, ' ');
        outs(out, p2, p);
        outc(out, '\n');
    };

    main := (email | (fb - email))*;
}%%

%% write data;

static void prolog(Output *out) {}
static void epilog(Output *out) {}

static void lex(Input *in, Output *out)
{
    char *p = in->p;
    char *pe = in->pe;
    char *p1, *p2;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;
}
