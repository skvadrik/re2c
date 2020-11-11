/*!include:re2c "common.re" */

static void print_headers(Output *out, const char *tok,
    const taglist_t *h1, const taglist_t *h2, const taglist_t *h3, const taglist_t *h4)
{
    if (!h4) return;
    print_headers(out, tok, h1->pred, h2->pred, h3->pred, h4->pred);
    OUT("header: ", tok + h1->dist, tok + h2->dist);
    OUT("value: ", tok + h3->dist, tok + h4->dist);
}

static int lex(input_t *in, Output *out)
{
    const char *of, *au, *at,
        *hs1, *hs3, *m1, *p1, *p3, *p5, *q1, *q3,
        *hs2, *hs4, *m2, *p2, *p4, *p6, *q2, *q4,
        *r1, *r3, *rp1, *s1, *st1, *u1, *u3, *v1, *v3,
        *r2, *r4, *rp2, *s2, *st2, *u2, *u4, *v2, *v4;
    taglist_t *h1, *h2, *h3, *h4;

loop:
    in->tok = in->cur;
/*!use:re2c
    eol            = "\n";
    crlf           = eol;
    sp             = " ";
    htab           = "\t";
    ows            = (sp | htab)*;
    digit          = [0-9];
    alpha          = [a-zA-Z];
    hexdigit       = [0-9a-fA-F];
    unreserved     = alpha | digit | [-._~];
    pct_encoded    = "%" hexdigit{2};
    sub_delims     = [!$&'()*+,;=];
    pchar          = unreserved | pct_encoded | sub_delims | [:@];
    vchar          = [\x1f-\x7e];
    tchar          = [-!#$%&'*+.^_`|~] | digit | alpha;
    obs_fold       = crlf (sp | htab)+;
    obs_text       = [\x80-\xff];
    field_name     = tchar+;
    field_vchar    = vchar | obs_text;
    field_content  = field_vchar ((sp | htab)+ field_vchar)?;
    field_value    = (field_content | obs_fold)*;
    header_field   = #h1 field_name #h2 ":" ows #h3 field_value #h4 ows;
    scheme         = alpha (alpha | digit | [-+.])*;
    userinfo       = (unreserved | pct_encoded | sub_delims | ":")*;
    dec_octet
        = digit
        | [\x31-\x39] digit
        | "1" digit{2}
        | "2" [\x30-\x34] digit
        | "25" [\x30-\x35];
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
    absolute_uri   = @s1 scheme @s2 ":"
        ( "//" (@u1 userinfo @u2 "@")? @hs1 host @hs2 (":" @r1 port @r2)? @p1 path_abempty @p2
        | @p3 (path_absolute | path_rootless | path_empty) @p4
        ) ("?" @q1 query @q2)?;
    authority      = (@u3 userinfo @u4 "@")? @hs3 host @hs4 (":" @r3 port @r4)?;
    origin_form    = @p5 path_abempty @p6 ("?" @q3 query @q4)?;
    http_name      = "HTTP";
    http_version   = http_name "/" digit "." digit;
    request_target
        = @at authority
        | @au absolute_uri
        | @of origin_form
        | "*";
    method         = tchar+;
    request_line   = @m1 method @m2 sp request_target sp @v3 http_version @v4 crlf;
    status_code    = digit{3};
    reason_phrase  = (htab | sp | vchar | obs_text)*;
    status_line    = @v1 http_version @v2 sp @st1 status_code @st2 sp @rp1 reason_phrase @rp2 crlf;
    start_line     = (request_line | status_line);
    message_head   = start_line (header_field crlf)* crlf;

    *            { return 1; }
    message_head {
        if (st1) {
            OUT("version-1: ", v1, v2);
            OUT("status: ", st1, st2);
            OUT("reason: ", rp1, rp2);
        } else if (m1) {
            OUT("method: ", m1, m2);
            if (of) {
                OUT("path-3: ", p5, p6);
                if (q3) OUT("query-2: ", q3, q4);
            } else if (au) {
                if (p1) {
                    OUT("scheme: ", s1, s2);
                    if (u1) OUT("user-1: ", u1, u2);
                    OUT("host-1: ", hs1, hs2);
                    if (r1) OUT("port-1: ", r1, r2);
                    OUT("path-1: ", p1, p2);
                } else {
                    OUT("path-2: ", p3, p4);
                }
                if (q1) OUT("query-1: ", q1, q2);
            } else if (at) {
                if (u3) OUT("user-2: ", u3, u4);
                OUT("host-2: ", hs3, hs4);
                if (r3) OUT("port-2: ", r3, r4);
            } else {
                outc(out, '*');
            }
            OUT("version-2: ", v3, v4);
        }
        print_headers(out, in->tok, h1, h2, h3, h4);
        outc(out, '\n');

        taglistpool_clear(&in->tlp, in);
        goto loop;
    }
*/
}
