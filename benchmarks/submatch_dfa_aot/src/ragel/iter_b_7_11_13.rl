#include "ragel/common.c"

const char *delim = "\n";

%%{
    machine aaa;

    # using disambiguation operator ** causes incorrect parse,
    # because some actions are removed while they are still needed
    #
    # without ** results are also incorrect due to action collision

    aaa = (([a]{13}|[a]{11}|[a]{7}) %{
            outs(out, s, p);
            outc(out, '.');
            s = p;
        })** >{ s = p; }
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
