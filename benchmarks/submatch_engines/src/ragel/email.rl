#include "ragel/common.c"

const char *delim = "\n";

/* From the Ragel manual:
    "To guard against this kind of problem one must ensure that the machine
     specification is divided up using boundaries that do not allow 
     ambiguities from one portion of the machine to the next."
*/

%%{
    machine email;

    estr = /[a-z0-9!#$%&'*+/=?^_`{|}~\-]/;
    beforeAt = estr+ ('.' estr+)*;
    az09 = /[a-z0-9]/;
    az09dash = /[a-z0-9\-]*[a-z0-9]/;
    part = az09 az09dash? '.';
    afterAt = part+ az09 az09dash?;

    email =
        (beforeAt '@' afterAt) > { q = p; } % { outs(out, q, p); }
        [\n]                   > { outc(out, fc); }
        ;

    fb = /[^\n]*[\n]/;

    main := (email | (fb - email))* ;
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
