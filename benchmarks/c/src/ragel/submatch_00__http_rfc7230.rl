#include "ragel/base.h"

namespace ragel_submatch_00__http_rfc7230 {

const char *delim = "\n\n";

%%{
    machine uri;

    eol            = "\n";
    crlf           = eol;
    sp             = " ";
    htab           = "\t";
    ows            = (sp | htab)*;
    hexdigit       = [0-9a-fA-F];
    unreserved     = alpha | digit | [\-._~];
    pct_encoded    = "%" hexdigit{2};
    sub_delims     = [!$&'()*+,;=];
    pchar          = unreserved | pct_encoded | sub_delims | [:@];
    vchar          = ascii - cntrl; # should be [\x1f-\x7e]
    tchar          = [\-!#$%&'*+.^_`|~] | digit | alpha;
    obs_fold       = crlf (sp | htab)+;
    obs_text       = extend - ascii;
    field_name     = tchar+;
    field_vchar    = vchar | obs_text;
    field_content  = field_vchar ((sp | htab)+ field_vchar)?;
    field_value    = (field_content | obs_fold)*;

    header_field =
        field_name  >{ h1 = p; }
        ":"         >{ h2 = p; }
        ows
        field_value >{ h3 = p; }
        ows         >{ h4 = p; };

    scheme         = alpha (alpha | digit | [\-+.])*;
    userinfo       = (unreserved | pct_encoded | sub_delims | ":")*;
    dec_octet
        = digit
        | [1-9] digit
        | "1" digit{2}
        | "2" [0-4] digit
        | "25" [0-5];
    ipv4address    = dec_octet "." dec_octet "." dec_octet "." dec_octet;
    h16            = hexdigit{1,4};
    ls32           = h16 ":" h16 | ipv4address;
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
    ipvfuture      = "v" hexdigit+ "." (unreserved | sub_delims | ":" )+;
    ip_literal     = "[" ( ipv6address | ipvfuture ) "]";
    reg_name       = (unreserved | pct_encoded | sub_delims)*;
    path_abempty   = ("/" pchar*)*;
    path_absolute  = "/" (pchar+ ("/" pchar*)*)?;
    path_rootless  = pchar+ ("/" pchar*)*;
    path_empty     = "";
    host           = ip_literal | ipv4address | reg_name;
    port           = digit*;
    query          = (pchar | [/?])*;

    authority_noactions = (userinfo "@")? host (":" port )?;
    authority =
        (userinfo  >{ u3 = p; }  %{ u4 = p; } "@")?
        host       >{ hs3 = p; } %{ hs4 = p; }
        (":" port  >{ r3 = p; }  %{ r4 = p; } )?;

    absolute_uri =
        scheme              >{ s1 = p; }  %{ s2 = p; }
        ":" ( "//"
            (userinfo       >{ u1 = p; }  %{ u2 = p; } "@")?
            host            >{ hs1 = p; } %{ hs2 = p; }
            (":" port       >{ r1 = p; }  %{ r2 = p; } )?
            path_abempty    >{ p1 = p; }  %{ p2 = p; }
        | ((path_absolute | path_rootless | path_empty) - authority_noactions)
                            >{ p3 = p; }  %{ p4 = p; }
        ) ("?" query        >{ q1 = p; }  %{ q2 = p; } )?;

    origin_form =
        path_abempty  >{ p5 = p; } %{ p6 = p; }
        ("?" query    >{ q3 = p; } %{ q4 = p; }
        )?;

    http_name    = "HTTP";
    http_version = http_name "/" digit "." digit;

    request_target
        = authority     %{ at = p; }
        | absolute_uri  %{ au = p; }
        | origin_form   %{ of = p; }
        | "*";

    method = tchar+;

    request_line =
        method                >{ m1 = p; } %{ m2 = p; } sp
        request_target                                  sp
        http_version          >{ v3 = p; } %{ v4 = p; } crlf;

    status_code    = digit{3};
    reason_phrase  = (htab | sp | vchar | obs_text)*;

    status_line =
        http_version   >{ v1 = p; }  %{ v2 = p; }  sp
        status_code    >{ st1 = p; } %{ st2 = p; } sp
        reason_phrase  >{ rp1 = p; } %{ rp2 = p; } crlf;

    start_line = (request_line | status_line) >{
        of = au = at =
            hs1 = hs3 = m1 = p1 = p3 = p5 = q1 = q3 =
            hs2 = hs4 = m2 = p2 = p4 = p6 = q2 = q4 =
            r1 = r3 = rp1 = s1 = st1 = u1 = u3 = v1 = v3 =
            r2 = r4 = rp2 = s2 = st2 = u2 = u4 = v2 = v4 =
            h1 = h2 = h3 = h4 = NULL;
    } %{
        if (st2) {
            OUT("version-1: ", v1, v2);
            OUT("status: ", st1, st2);
            OUT("reason: ", rp1, rp2);
        } else if (m2) {
            OUT("method: ", m1, m2);
            if (of) {
                OUT("path-3: ", p5, p6);
                if (q3) OUT("query-2: ", q3, q4);
            } else if (au) {
                if (p2) {
                    OUT("scheme: ", s1, s2);
                    if (u2) OUT("user-1: ", u1, u2);
                    OUT("host-1: ", hs1, hs2);
                    if (r2) OUT("port-1: ", r1, r2);
                    OUT("path-1: ", p1, p2);
                } else {
                    OUT("path-2: ", p3, p4);
                }
                if (q2) OUT("query-1: ", q1, q2);
            } else if (at) {
                if (u4) OUT("user-2: ", u3, u4);
                OUT("host-2: ", hs3, hs4);
                if (r4) OUT("port-2: ", r3, r4);
            } else {
                OUTC('*');
            }
            OUT("version-2: ", v3, v4);
        }
    };

    field = header_field crlf >{
        if (h4) {
            OUT("header: ", h1, h2);
            OUT("value: ", h3, h4);
        }
        h1 = h2 = h3 = h4 = NULL;
    };

    message_head = start_line field* crlf >{ OUTC('\n'); };

    main := message_head*;
}%%

%% write data;

static int lex(Input *in, int count) {
    char *p = in->p;
    char *pe = in->pe;
    const char *of, *au, *at,
        *hs1, *hs3, *m1, *p1, *p3, *p5, *q1, *q3,
        *hs2, *hs4, *m2, *p2, *p4, *p6, *q2, *q4,
        *r1, *r3, *rp1, *s1, *st1, *u1, *u3, *v1, *v3,
        *r2, *r4, *rp2, *s2, *st2, *u2, *u4, *v2, *v4,
        *h1, *h2, *h3, *h4;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;

    return count;
}

RAGEL_BENCH_AND_TEST()

} // namespace ragel_submatch_00__http_rfc7230
