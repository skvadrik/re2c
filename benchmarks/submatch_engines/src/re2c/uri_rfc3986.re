/*!include:re2c "common.re" */

static int lex(input_t *in, Output *out)
{
    const char
        *s1, *u1, *h1, *h3, *h5, *r1, *p1, *p3, *q1, *f1,
        *s2, *u2, *h2, *h4, *h6, *r2, *p2, *p4, *q2, *f2;

loop:
    in->tok = in->cur;
/*!re2c
    end = "\x00";
    nl = "\n";

    alpha       = [a-zA-Z];
    digit       = [0-9];
    hexdigit    = [0-9a-fA-F];
    unreserved  = alpha | digit | [-._~];
    pct_encoded = "%" hexdigit{2};
    sub_delims  = [!$&'()*+,;=];
    pchar       = unreserved | pct_encoded | sub_delims | [:@];

    scheme = @s1 alpha (alpha | digit | [-+.])* @s2;
    userinfo = @u1 (unreserved | pct_encoded | sub_delims | ":")* @u2;
    dec_octet
        = digit
        | [\x31-\x39] digit
        | "1" digit{2}
        | "2" [\x30-\x34] digit
        | "25" [\x30-\x35];
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
    host
        = @h1 ip_literal  @h2
        | @h3 ipv4address @h4
        | @h5 reg_name    @h6;
    port      = @r1 digit* @r2;
    authority = (userinfo "@")? host (":" port)?;
    path_abempty  = ("/" pchar*)*;
    path_absolute = "/" (pchar+ ("/" pchar*)*)?;
    path_rootless = pchar+ ("/" pchar*)*;
    path_empty    = "";
    hier_part
        = "//" authority @p1 path_abempty @p2
        | @p3 (path_absolute | path_rootless | path_empty) @p4;
    query    = @q1 (pchar | [/?])* @q2;
    fragment = @f1 (pchar | [/?])* @f2;
    uri = scheme ":" hier_part ("?" query)? ("#" fragment)? nl;

    *   { return 1; }
    end { return 0; }
    uri {
        OUT("scheme: ", s1, s2);
        if (u1) OUT("user: ", u1, u2);
        if (h1) OUT("host-1: ", h1, h2);
        else if (h3) OUT("host-2: ", h3, h4);
        else if (h5) OUT("host-3: ", h5, h6);
        if (r1) OUT("port: ", r1, r2);
        if (p1) OUT("path-1: ", p1, p2);
        else if (p3) OUT("path-2: ", p3, p4);
        if (q1) OUT("query: ", q1, q2);
        if (f1) OUT("fragment: ", f1, f2);
        outc(out, '\n');
        goto loop;
    }
*/
}
