#include "ragel/base.h"

namespace ragel_submatch_02__uri_rfc3986 {

const char *delim = "\n";

%%{
    machine uri;

    hexdigit    = [0-9a-fA-F];
    unreserved  = alpha | digit | [\-._~];
    pct_encoded = "%" hexdigit{2};
    sub_delims  = [!$&'()*+,;=];
    pchar       = unreserved | pct_encoded | sub_delims | [:@];

    scheme = (alpha (alpha | digit | [\-+.])*) >{
            s1 = u1 = h1 = h3 = h5 = r1 = p1 = p3 = q1 = f1 =
            s2 = u2 = h2 = h4 = h6 = r2 = p2 = p4 = q2 = f2 = NULL;
            s1 = p;
        }
        %{ s2 = p; };

    userinfo = (unreserved | pct_encoded | sub_delims | ":")*
        >{ u1 = p; }
        %{ u2 = p; };

    dec_octet
        = digit
        | [1-9] digit
        | "1" digit{2}
        | "2" [0-4] digit
        | "25" [0-5];
    ipv4address = dec_octet "." dec_octet "." dec_octet "." dec_octet;
    h16         = hexdigit{1,4};
    ls32        = h16 ":" h16 | ipv4address;
    ipv6address
        =                            (h16 ":"){6} ls32
        |                       "::" (h16 ":"){5} ls32
        | (               h16)? "::" (h16 ":"){4} ls32
        | ((h16 ":"){0,1} h16)? "::" (h16 ":"){3} ls32
        | ((h16 ":"){0,2} h16)? "::" (h16 ":"){2} ls32
        | ((h16 ":"){0,3} h16)? "::"  h16 ":"     ls32
        | ((h16 ":"){0,4} h16)? "::"              ls32
        | ((h16 ":"){0,5} h16)? "::"              h16
        | ((h16 ":"){0,6} h16)? "::";
    ipvfuture   = "v" hexdigit+ "." (unreserved | sub_delims | ":" )+;
    ip_literal  = "[" ( ipv6address | ipvfuture ) "]";
    reg_name    = (unreserved | pct_encoded | sub_delims)*;

    host1 = ip_literal  >{ h1 = p; } %{ h2 = p; };
    host2 = ipv4address >{ h3 = p; } %{ h4 = p; };
    host3 = reg_name    >{ h5 = p; } %{ h6 = p; };
    host  = host1 | host2 | host3;

    port = digit* >{ r1 = p; } %{ r2 = p; };

    authority = (userinfo "@")? host (":" port)?;

    path_abempty  = ("/" pchar*)*;
    path_absolute = "/" (pchar+ ("/" pchar*)*)?;
    path_rootless = pchar+ ("/" pchar*)*;
    path_empty    = "";
    path1         = path_abempty                                 >{ p1 = p; } %{ p2 = p; };
    path2         = (path_absolute | path_rootless | path_empty) >{ p3 = p; } %{ p4 = p; };

    hier_part = "//" authority path1 | path2;

    query    = (pchar | [/?])* >{ q1 = p; } %{ q2 = p; };
    fragment = (pchar | [/?])* >{ f1 = p; } %{ f2 = p; };

    uri = scheme ":" hier_part ("?" query)? ("#" fragment)? [\n]
    >{
        OUT("scheme: ", s1, s2);
        if (u2) OUT("user: ", u1, u2);
        if (h1) OUT("host-1: ", h1, h2);
        else if (h3) OUT("host-2: ", h3, h4);
        else if (h5) OUT("host-3: ", h5, h6);
        if (r2) OUT("port: ", r1, r2);
        if (p1) OUT("path-1: ", p1, p2);
        else if (p3) OUT("path-2: ", p3, p4);
        if (q1) OUT("query: ", q1, q2);
        if (f1) OUT("fragment: ", f1, f2);
        OUTC('\n');
    };

    main := uri*;
}%%

%% write data;

static int lex(Input *in, int count) {
    char *p = in->p;
    char *pe = in->pe;
    const char
        *s1, *u1, *h1, *h3, *h5, *r1, *p1, *p3, *q1, *f1,
        *s2, *u2, *h2, *h4, *h6, *r2, *p2, *p4, *q2, *f2;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;

    return count;
}

RAGEL_BENCH()
RAGEL_TEST()

} // namespace ragel_submatch_02__uri_rfc3986

