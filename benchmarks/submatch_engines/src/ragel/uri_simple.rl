#include "ragel/common.c"

const char *delim = "\n";

%%{
    machine uri;

    char     = [\-._~%!$&'()*+,;=a-zA-Z0-9];
    scheme   = [\-+.a-zA-Z0-9]+ >{
            s1 = u1 = h1 = r1 = p1 = q1 = f1 =
            s2 = u2 = h2 = r2 = p2 = q2 = f2 = NULL;
            s1 = p;
        }
        %{ s2 = p; };
    userinfo = (char | [:])+                    >{ u1 = p; } %{ u2 = p; };
    host     = (char | /\[/ (char | [:])* /]/)+ >{ h1 = p; } %{ h2 = p; };
    port     = [0-9]*                           >{ r1 = p; } %{ r2 = p; };
    path     = (char | [:@/])*                  >{ p1 = p; } %{ p2 = p; };
    query    = (char | [:@?/])*                 >{ q1 = p; } %{ q2 = p; };
    fragment = (char | [:@?/])*                 >{ f1 = p; } %{ f2 = p; };

    nl = [\n] >{
        OUT("scheme: ", s1, s2);
        if (u2 - u1 > 1) {
            OUT("user: ", u1, u2);
        }
        if (h1) {
            OUT("host: ", h1, h2);
        }
        if (r2 - r1 > 1) {
            OUT("port: ", r1, r2);
        }
        OUT("path: ", p1, p2);
        if (q1) {
            OUT("query: ", q1, q2);
        }
        if (f1) {
            OUT("fragment: ", f1, f2);
        }
        outc(out, '\n');
    };

    uri = scheme ":"
        ("//" (userinfo "@")? host (":" port)?)?
        path ("?" query)? ("#" fragment)? nl;

    main := uri*;
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

    const char
        *s1, *u1, *h1, *r1, *p1, *q1, *f1,
        *s2, *u2, *h2, *r2, *p2, *q2, *f2;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;
}
