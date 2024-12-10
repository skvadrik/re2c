#include "ragel/base.h"

namespace ragel_submatch_06__email {

const char *delim = "\n";

%%{
    machine email;

    char      = [a-z0-9!#$%&'*+/=?^_`{|}~\-];
    before_at = char+ ([.] char+)*;
    az09      = [a-z0-9];
    az09dash  = [a-z0-9\-]* [a-z0-9];
    after_at  = (az09 az09dash? [.])+ az09 az09dash?;
    skip      = [^\n\0]*[\n];
    email     =
        before_at >{ p1 = p; } [@]
        after_at  >{ p2 = p; } [\n]
    >{
        OUTC(' ');
        OUTS(p1, p2 - 1);
        OUTC(' ');
        OUTS(p2, p);
        OUTC('\n');
    };

    main := (email | (skip - email))*;
}%%

%% write data;

static int lex(Input *in, int count) {
    char *p = in->p;
    char *pe = in->pe;
    char *p1, *p2;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;

    return count;
}

RAGEL_BENCH()
RAGEL_TEST()

} // namespace ragel_submatch_06__email
