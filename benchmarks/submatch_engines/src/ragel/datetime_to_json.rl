#include "ragel/common.c"

%%{
    machine datetime;

    action setptr { q = p; }
    action output { outs(out, q, p); }

    year     = (([1-9][0-9]*)? [0-9]{4})                           > { outstr(out, "{'year'='"); };
    month    = ([1][0-2] | [0][1-9])                               > { outstr(out, "', 'month'='"); };
    day      = ([3][0-1] | [0][1-9] | [1-2][0-9])                  > { outstr(out, "', 'day'='"); };
    hours    = ([2][0-3] | [0-1][0-9])                             > { outstr(out, "', 'hours'='"); };
    minutes  = ([0-5][0-9])                                        > { outstr(out, "', 'minutes'='"); };
    seconds  = ([0-5][0-9])                                        > { outstr(out, "', 'seconds'='"); };
    timezone = ([Z] | [+\-] ([2][0-3] | [0-1][0-9]) [:][0-5][0-9]) > { outstr(out, "', 'tz'='"); };

    dateTime = year     > setptr % output '-'
               month    > setptr % output '-'
               day      > setptr % output 'T'
               hours    > setptr % output ':'
               minutes  > setptr % output ':'
               seconds  > setptr % output
               timezone > setptr % output
               [\n]     > { outstr(out, "'}\n"); };

    main := dateTime*;
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
