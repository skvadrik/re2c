#include "ragel/common.c"

const char *delim = "\n";

%%{
    machine email;

    char      = [a-z0-9!#$%&'*+/=?^_`{|}~\-];
    before_at = char+ ([.] char+)*;
    az09      = [a-z0-9];
    az09dash  = [a-z0-9\-]* [a-z0-9];
    after_at  = (az09 az09dash? [.])+ az09 az09dash?;
    skip      = [^\n]*[\n];
    email     =
        before_at >{ p1 = p; } [@]
        after_at  >{ p2 = p; } [\n]
    >{
        outc(out, ' ');
        outs(out, p1, p2 - 1);
        outc(out, ' ');
        outs(out, p2, p);
        outc(out, '\n');
    };

    main := (email | (skip - email))*;
}%%

%% write data;

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
