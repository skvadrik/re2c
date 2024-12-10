#include "ragel/base.h"

namespace ragel_submatch_04__apache_log {

const char *delim = "\n";

%%{
    machine apache_log;

    sp        = [ \t]+;
    host      = [0-9.]+;
    userid    = [\-];
    authuser  = [\-];
    date      = "[" [^\n\]]+ "]";
    request   = ["] [^\n"]+ ["];
    status    = digit+;
    size      = (digit+ | '-');
    url       = ["] [^\n"]* ["];
    useragent = ["] [^\n"]* ["];
    line    =
        host      >{ h1 = p; } %{ h2 = p; } sp
        userid    >{ i1 = p; } %{ i2 = p; } sp
        authuser  >{ a1 = p; } %{ a2 = p; } sp
        date      >{ d1 = p; } %{ d2 = p; } sp
        request   >{ r1 = p; } %{ r2 = p; } sp
        status    >{ s1 = p; } %{ s2 = p; } sp
        size      >{ z1 = p; } %{ z2 = p; } sp
        url       >{ u1 = p; } %{ u2 = p; } sp
        useragent >{ g1 = p; } %{ g2 = p; } [\n]
    >{
        OUT("host: ",     h1, h2);
        OUT("userid: ",   i1, i2);
        OUT("authuser: ", a1, a2);
        OUT("date: ",     d1, d2);
        OUT("request: ",  r1, r2);
        OUT("status: ",   s1, s2);
        OUT("size: ",     z1, z2);
        OUT("url: ",      u1, u2);
        OUT("agent: ",    g1, g2);
        OUTC('\n');
    };

    main := line*;
}%%

%% write data;

static int lex(Input *in, int count) {
    char *p = in->p;
    char *pe = in->pe;
    const char
        *h1, *i1, *a1, *d1, *r1, *s1, *z1, *u1, *g1,
        *h2, *i2, *a2, *d2, *r2, *s2, *z2, *u2, *g2;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;

    return count;
}

RAGEL_BENCH()
RAGEL_TEST()

} // namespace ragel_submatch_04__apache_log
