#include "ragel/common.c"

const char *delim = "\n\n";

%%{
    machine uri;

    eol            = [\n];
    sp             = [ ];
    htab           = [\t];
    ows            = (sp | htab)*;
    char           = [\-._~%!$&'()*+,;=a-zA-Z0-9];
    tchar          = [\-._~%!$&'*+#^`|a-zA-Z0-9];
    vchar          = extend - cntrl; # should be [\x1f-\x7e\x80-\xff]
    scheme         = [\-+.a-zA-Z0-9]+;
    userinfo       = (char | [:])+;
    host           = (char | [:[\]])+;
    port           = [0-9]*;
    path           = (char | [:@/])*;
    query          = (char | [:@?/])*;
    obs_fold       = eol (sp | htab)+;
    field_content  = vchar ((sp | htab)+ vchar)?;

    header_field =
        tchar+ >{ h1 = p; }
        [:]    >{ h2 = p; }
        ows (field_content | obs_fold)* ows >{ h3 = p; };

    authority      = (userinfo [@])? host ([:] port)?;
    absolute_uri   = scheme [:] ([/][/] (userinfo [@])? host ([:] port)?)? path ([?] query)?;
    origin_form    = [/] path ([?] query)?;
    http_version   = /HTTP\// [0-9] [.] [0-9];
    request_target = authority | absolute_uri | origin_form | [*];
    method         = tchar+;

    request_line =
        method         >{ m1 = p; } %{ m2 = p; }
        sp
        request_target >{ rt1 = p; } %{ rt2 = p; }
        sp
        http_version   >{ v3 = p; } %{ v4 = p; }
        eol;

    status_code    = [0-9]{3};
    reason_phrase  = (htab | sp | vchar)*;

    status_line =
        http_version  >{ v1 = p; } %{ v2 = p; }
        sp
        status_code   >{ s1 = p; } %{ s2 = p; }
        sp
        reason_phrase >{ rp1 = p; } %{ rp2 = p; }
        eol;

    start_line = (request_line | status_line) >{
        h1 = h2 = h3 =
            s1 = v1 = v3 = m1 = rp1 = rt1 =
            s2 = v2 = v4 = m2 = rp2 = rt2 = NULL;
    } %{
        if (s1 && s2) {
            OUT("version: ", v1, v2);
            OUT("status: ", s1, s2);
            OUT("reason: ", rp1, rp2);
        }
        if (m1 && m2) {
            OUT("method: ", m1, m2);
            OUT("request: ", rt1, rt2);
            OUT("version: ", v3, v4);
        }
    };

    field = header_field eol >{
        if (h3) {
            outstr(out, "header: ");
            outs(out, h1, h2);
            outc(out, ' ');
            outs(out, h2 + 1, h3);
            outc(out, '\n');
        }
        h1 = h2 = h3 = NULL;
    };

    message_head = start_line field* eol >{ outc(out, '\n'); };

    main := message_head*;
}%%

%% write data;

static void prolog(Output *out) {}
static void epilog(Output *out) {}

static void lex(Input *in, Output *out)
{
    char *p = in->p;
    char *pe = in->pe;
    const char *h1, *h2, *h3,
        *s1, *v1, *v3, *m1, *rp1, *rt1,
        *s2, *v2, *v4, *m2, *rp2, *rt2;
    int cs;

    %% write init;
    %% write exec;

    in->p = p;
    in->pe = pe;
}
